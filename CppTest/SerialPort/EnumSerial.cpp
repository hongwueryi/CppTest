/*************************************************************************
* Serial port enumeration routines
************************************************************************/

// The next 3 includes are needed for serial port enumeration
#include <Windows.h>
#include <vector>
#include "EnumSerial.h"
#include <objbase.h>
#include <initguid.h>
#include <Setupapi.h>
//#include "comm_util\SysUtil.h"

#include <iostream>
#include <string>
#include <atlstr.h>
// The following define is from ntddser.h in the DDK. It is also
// needed for serial port enumeration.
#ifndef GUID_CLASS_COMPORT
DEFINE_GUID( GUID_CLASS_COMPORT, 0x86e0d1e0L, 0x8089, 0x11d0, 0x9c, 0xe4, \
             0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73 );
#endif

//---------------------------------------------------------------
// Helpers for enumerating the available serial ports.
// These throw a CString on failure, describing the nature of
// the error that occurred.

std::string ws2string(const std::wstring& wstr)
{
    int ansiiLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    char* pAssii = (char*)malloc(sizeof(char) * ansiiLen);
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
    std::string ret_str = pAssii;
    free(pAssii);
    return ret_str;
}

void EnumPortsWdm( std::vector<SSerInfo> &vecSerInfo );
void EnumPortsWNt4( std::vector<SSerInfo> &vecSerInfo );
void EnumPortsW9x( std::vector<SSerInfo> &vecSerInfo );
void SearchPnpKeyW9x( HKEY hkPnp, BOOL bUsbDevice, std::vector<SSerInfo> &vecSerInfo );



//---------------------------------------------------------------
// Routine for enumerating the available serial ports.
// Throws a CString on failure, describing the error that
// occurred. If bIgnoreBusyPorts is TRUE, ports that can't
// be opened for read/write access are not included.

bool EnumSerialPorts( std::vector<SSerInfo> &vecSerInfo, BOOL bIgnoreBusyPorts )
{
    // Clear the output array
    vecSerInfo.clear();

    // Use different techniques to enumerate the available serial
    // ports, depending on the OS we're using
    OSVERSIONINFO vi;
    vi.dwOSVersionInfoSize = sizeof( vi );

    if ( !::GetVersionEx( &vi ) )
    {
        return false;
    }

    // Handle windows 9x and NT4 specially
    if ( vi.dwMajorVersion < 5 )
    {
        if ( vi.dwPlatformId == VER_PLATFORM_WIN32_NT )
        { EnumPortsWNt4( vecSerInfo ); }
        else
        { EnumPortsW9x( vecSerInfo ); }
    }
    else
    {
        // Win2k and later support a standard API for
        // enumerating hardware devices.
        EnumPortsWdm( vecSerInfo );
    }

    //WriteLogD("EnumSerialPorts::+0 Begin");
    std::vector<SSerInfo>::iterator iter = vecSerInfo.begin();

    while ( iter != vecSerInfo.end() )
    {
        //SSerInfo& rsi = asi[ii];
        if ( bIgnoreBusyPorts )
        {
            // Only display ports that can be opened for read/write
            //WriteLogD("EnumSerialPorts::+1 Begin CreateFile strDevPath:[%s]", SysUtil::ws2string(iter->strDevPath).c_str());
            std::cout << "EnumSerialPorts:: + 1 Begin CreateFile strDevPath : " << ws2string( iter->stDevPath ).c_str();
            HANDLE hCom = ::CreateFile( iter->stDevPath,
                                        GENERIC_READ | GENERIC_WRITE,
                                        0,    /* comm devices must be opened w/exclusive-access */
                                        NULL, /* no security attrs */
                                        OPEN_EXISTING, /* comm devices must use OPEN_EXISTING */
                                        0,    /* not overlapped I/O */
                                        NULL  /* hTemplate must be NULL for comm devices */
                                      );
            //WriteLogD("EnumSerialPorts::+2 End CreateFile strDevPath:[%s]", SysUtil::ws2string(iter->strDevPath).c_str());
            std::cout << "EnumSerialPorts::+2 End CreateFile strDevPath: " << ws2string( iter->stDevPath ).c_str();

            if ( hCom == INVALID_HANDLE_VALUE )
            {
                // It can't be opened; remove it.
                iter = vecSerInfo.erase( iter );
                //WriteLogD("EnumSerialPorts::+3 INVALID_HANDLE_VALUE strDevPath:[%s]", SysUtil::ws2string(iter->strDevPath).c_str());
                std::cout << "EnumSerialPorts::+3 INVALID_HANDLE_VALUE strDevPath: " << ws2string( iter->stDevPath ).c_str();
                continue;
            }
            else
            {
                // It can be opened! Close it and add it to the list
                ::CloseHandle( hCom );
                //WriteLogD("EnumSerialPorts::+4 CloseHandle strDevPath:[%s]", SysUtil::ws2string(iter->strDevPath).c_str());
                std::cout << "EnumSerialPorts::+4 CloseHandle strDevPath: " << ws2string( iter->stDevPath ).c_str();
            }
        }

        // Come up with a name for the device.
        // If there is no friendly name, use the port name.
        if ( CString( iter->stFriendlyName ).IsEmpty() )
        {
            //iter->strFriendlyName = iter->strPortName;
            memset( iter->stFriendlyName, 0, sizeof( iter->stFriendlyName ) );
            _tcscpy_s( iter->stFriendlyName, DEV_DESC_LEN - 1, iter->stPortName );
        }

        // If there is no description, try to make one up from
        // the friendly name.
        if ( CString( iter->stPortDesc ).IsEmpty() )
        {
            // If the port name is of the form "ACME Port (COM3)"
            // then strip off the " (COM3)"
            /* iter->strPortDesc = iter->strFriendlyName;
             int startdex = iter->strPortDesc.find( L" (" );
             int enddex = iter->strPortDesc.find( L")" );

             if ( startdex > 0 && enddex ==
                  ( iter->strPortDesc.length() - 1 ) )
             { iter->strPortDesc = iter->strPortDesc.at( startdex ); }*/
            _tcscpy_s( iter->stPortDesc, DEV_DESC_LEN - 1, iter->stFriendlyName );
            CString strPortDesc = iter->stPortDesc;
            int startdex = strPortDesc.Find( L" (" );
            int enddex = strPortDesc.Find( L")" );

            if ( startdex > 0 && enddex ==
                 ( strPortDesc.GetLength() - 1 ) )
            {
                //iter->strPortDesc = iter->strPortDesc.at(startdex);
                CString strPortDesc2 = CString( iter->stPortDesc ).GetAt( startdex );
                _tcscpy_s( iter->stPortDesc, DEV_DESC_LEN - 1, strPortDesc2.GetBuffer( 0 ) );
            }
        }

        iter++;
    }

    //WriteLogD("EnumSerialPorts::+5 End");
    return true;
}

// Helpers for EnumSerialPorts
void EnumPortsWdm( std::vector<SSerInfo> &vecSerInfo )
{
    std::wstring strErr;
    // Create a device information set that will be the container for
    // the device interfaces.
    GUID *guidDev = ( GUID * )&GUID_CLASS_COMPORT;

    HDEVINFO hDevInfo = INVALID_HANDLE_VALUE;
    SP_DEVICE_INTERFACE_DETAIL_DATA *pDetData = NULL;
    std::cout << "1 Enter";

    hDevInfo = SetupDiGetClassDevs( guidDev,
                                    NULL,
                                    NULL,
                                    DIGCF_PRESENT | DIGCF_DEVICEINTERFACE
                                  );

    if ( hDevInfo == INVALID_HANDLE_VALUE )
    {
        std::cout << " 1-1 hDevInfo == INVALID_HANDLE_VALUE" << std::endl;
        return;
    }

    std::cout << "2 get hDevInfo";

    // Enumerate the serial ports
    BOOL bOk = TRUE;
    SP_DEVICE_INTERFACE_DATA ifcData;
    DWORD dwDetDataSize = sizeof( SP_DEVICE_INTERFACE_DETAIL_DATA ) + DEV_DESC_LEN;
    pDetData = ( SP_DEVICE_INTERFACE_DETAIL_DATA * ) new char[dwDetDataSize];
    // This is required, according to the documentation. Yes,
    // it's weird.
    ifcData.cbSize = sizeof( SP_DEVICE_INTERFACE_DATA );
    pDetData->cbSize = sizeof( SP_DEVICE_INTERFACE_DETAIL_DATA );

    for ( int ii = 0; bOk; ii++ )
    {
        bOk = SetupDiEnumDeviceInterfaces( hDevInfo, NULL, guidDev, ii, &ifcData );
        std::cout << "3 SetupDiEnumDeviceInterfaces bOk: " << bOk << std::endl;

        if ( bOk )
        {
            // Got a device. Get the details.
            SP_DEVINFO_DATA devdata = { sizeof( SP_DEVINFO_DATA ) };
            bOk = SetupDiGetDeviceInterfaceDetail( hDevInfo,
                                                   &ifcData, pDetData, dwDetDataSize, NULL, &devdata );

            std::cout << "4 SetupDiGetDeviceInterfaceDetail bOk:: " << bOk
                        << ", pDetData->DevicePath" << ws2string( pDetData->DevicePath ).c_str() << std::endl;

            if ( bOk )
            {
                std::wstring strDevPath( pDetData->DevicePath );

                // Got a path to the device. Try to get some more info.
                TCHAR fname[DEV_DESC_LEN] = {0};
                TCHAR desc[DEV_DESC_LEN] = {0};
                BOOL bSuccess = SetupDiGetDeviceRegistryProperty(
                                    hDevInfo, &devdata, SPDRP_FRIENDLYNAME, NULL,
                                    ( PBYTE )fname, sizeof( fname ), NULL );
                std::cout << "5 SetupDiGetDeviceInterfaceDetail bSuccess: " << bSuccess
                            << ", fname: " << ws2string( fname ).c_str() << std::endl;
                bSuccess = bSuccess && SetupDiGetDeviceRegistryProperty(
                               hDevInfo, &devdata, SPDRP_DEVICEDESC, NULL,
                               ( PBYTE )desc, sizeof( desc ), NULL );
                std::cout << "6 SetupDiGetDeviceInterfaceDetail bSuccess: " << bSuccess
                            << ", desc: " << ws2string( desc ).c_str() << std::endl;
                BOOL bUsbDevice = FALSE;
                TCHAR hwId[MAX_PATH] = {0};

                //status = CM_Get_Device_ID(DeviceInfoData.DevInst, locinfo, MAX_PATH, 0)
                if ( SetupDiGetDeviceRegistryProperty(
                         hDevInfo, &devdata, SPDRP_HARDWAREID, NULL,
                         ( PBYTE )hwId, sizeof( hwId ), NULL ) )
                {
                    // Just check the first three characters to determine
                    // if the port is connected to the USB bus. This isn't
                    // an infallible method; it would be better to use the
                    // BUS GUID. Currently, Windows doesn't let you query
                    // that though (SPDRP_BUSTYPEGUID seems to exist in
                    // documentation only).
                    std::cout << "7 SetupDiGetDeviceInterfaceDetail hwId: " << ws2string( hwId ).c_str() << std::endl;
                    bUsbDevice = !( _tcsstr( hwId, L"USB" ) == nullptr );
                }

                if ( bSuccess )
                {
                    // Add an entry to the array
                    SSerInfo si;
                    //si.strDevPath = strDevPath;
                    //si.strFriendlyName = fname;
                    //si.strPortDesc = desc;
                    //si.strPortName = si.strFriendlyName.substr( si.strFriendlyName.find_last_of( L'(' ) + 1, si.strFriendlyName.find_last_of( L')' ) - si.strFriendlyName.find_last_of( L'(' ) - 1 );
                    //si.bUsbDevice = bUsbDevice;

                    _tcscpy_s( si.stDevPath, DEV_DESC_LEN - 1, strDevPath.c_str() );
                    _tcscpy_s( si.stFriendlyName, DEV_DESC_LEN - 1, fname );
                    _tcscpy_s( si.stPortDesc, DEV_DESC_LEN - 1, desc );
                    std::wstring strFriName = si.stFriendlyName;
                    std::wstring strPortName = strFriName.substr( strFriName.find_last_of( L'(' ) + 1, strFriName.find_last_of( L')' ) - strFriName.find_last_of( L'(' ) - 1 );
                    _tcscpy_s( si.stPortName, DEV_DESC_LEN - 1, strPortName.c_str() );
                    si.bUsbDevice = bUsbDevice;
                    vecSerInfo.push_back( si );
                    //LOG( INFO ) << "8 SetupDiGetDeviceInterfaceDetail si.stPortName:: " << SysUtil::ws2string( si.stPortName ).c_str();
                }
            }
            else
            {
                std::cout << "9 SetupDiGetDeviceInterfaceDetail" << std::endl;
                break;
            }
        }
        else
        {
            std::cout << "10 SetupDiGetDeviceInterfaceDetail" << std::endl;
            break;
        }
    }

    if ( pDetData != NULL )
    {
        delete[]( char * )pDetData;
    }

    if ( hDevInfo != INVALID_HANDLE_VALUE )
    {
        SetupDiDestroyDeviceInfoList( hDevInfo );
    }

end_enum_port:
    //WriteLogD("EnumPortsWdm::11 Leave");
    std::cout << "EnumPortsWdm::11 Leave" << std::endl;
    return;
}

void EnumPortsWNt4( std::vector<SSerInfo> &vecSerInfo )
{
    // NT4's driver model is totally different, and not that
    // many people use NT4 anymore. Just try all the COM ports
    // between 1 and 16
    SSerInfo si;

    for ( int ii = 1; ii <= 16; ii++ )
    {
        std::wstring strPort = L"COM" + std::to_wstring( ii );
        //si.strDevPath = L"\\\\.\\" + strPort;
        //si.strPortName = strPort;
        wsprintf( si.stDevPath, _T( "\\\\.\\%s" ), strPort.c_str() );
        wsprintf( si.stPortName, _T( "%s" ), strPort.c_str() );
        vecSerInfo.push_back( si );
    }
}

void EnumPortsW9x( std::vector<SSerInfo> &vecSerInfo )
{
    // Look at all keys in HKLM\Enum, searching for subkeys named
    // *PNP0500 and *PNP0501. Within these subkeys, search for
    // sub-subkeys containing value entries with the name "PORTNAME"
    // Search all subkeys of HKLM\Enum\USBPORTS for PORTNAME entries.

    // First, open HKLM\Enum
    HKEY hkEnum = NULL;
    HKEY hkSubEnum = NULL;
    HKEY hkSubSubEnum = NULL;

    if ( RegOpenKeyEx( HKEY_LOCAL_MACHINE, L"Enum", 0, KEY_READ,
                       &hkEnum ) != ERROR_SUCCESS )
    {
        printf( "Could not read from HKLM\\Enum\n" );
        return;
    }

    // Enumerate the subkeys of HKLM\Enum
    TCHAR acSubEnum[128];
    DWORD dwSubEnumIndex = 0;
    DWORD dwSize = sizeof( acSubEnum );

    while ( RegEnumKeyEx( hkEnum, dwSubEnumIndex++, acSubEnum, &dwSize,
                          NULL, NULL, NULL, NULL ) == ERROR_SUCCESS )
    {
        HKEY hkSubEnum = NULL;

        if ( RegOpenKeyEx( hkEnum, acSubEnum, 0, KEY_READ,
                           &hkSubEnum ) != ERROR_SUCCESS )
        {
            printf( "Could not read from HKLM\\Enum\\%S\n", acSubEnum );
            break;
        }

        // Enumerate the subkeys of HKLM\Enum\*\, looking for keys
        // named *PNP0500 and *PNP0501 (or anything in USBPORTS)
        BOOL bUsbDevice = !( _tcsstr( acSubEnum, L"USBPORTS" ) == nullptr );
        TCHAR acSubSubEnum[128];
        dwSize = sizeof( acSubSubEnum ); // set the buffer size
        DWORD dwSubSubEnumIndex = 0;

        while ( RegEnumKeyEx( hkSubEnum, dwSubSubEnumIndex++, acSubSubEnum,
                              &dwSize, NULL, NULL, NULL, NULL ) == ERROR_SUCCESS )
        {
            BOOL bMatch = ( _tcsstr( acSubSubEnum, L"*PNP0500" ) != nullptr ||
                            _tcsstr( acSubSubEnum, L"*PNP0501" ) != nullptr ||
                            bUsbDevice );

            if ( bMatch )
            {
                HKEY hkSubSubEnum = NULL;

                if ( RegOpenKeyEx( hkSubEnum, acSubSubEnum, 0, KEY_READ,
                                   &hkSubSubEnum ) != ERROR_SUCCESS )
                {
                    printf( "Could not read from HKLM\\Enum\\%S\n", acSubSubEnum );
                    break;
                }

                SearchPnpKeyW9x( hkSubSubEnum, bUsbDevice, vecSerInfo );
                RegCloseKey( hkSubSubEnum );
                hkSubSubEnum = NULL;
            }

            dwSize = sizeof( acSubSubEnum ); // restore the buffer size
        }

        RegCloseKey( hkSubEnum );
        hkSubEnum = NULL;
        dwSize = sizeof( acSubEnum ); // restore the buffer size
    }

    if ( hkSubSubEnum != NULL )
    { RegCloseKey( hkSubSubEnum ); }

    if ( hkSubEnum != NULL )
    { RegCloseKey( hkSubEnum ); }

    if ( hkEnum != NULL )
    { RegCloseKey( hkEnum ); }
}

void SearchPnpKeyW9x( HKEY hkPnp, BOOL bUsbDevice, std::vector<SSerInfo> &vecSerInfo )
{
    // Enumerate the subkeys of HKLM\Enum\*\PNP050[01]
    TCHAR acSubPnp[128];
    DWORD dwSubPnpIndex = 0;
    DWORD dwSize = sizeof( acSubPnp );

    while ( RegEnumKeyEx( hkPnp, dwSubPnpIndex++, acSubPnp, &dwSize,
                          NULL, NULL, NULL, NULL ) == ERROR_SUCCESS )
    {
        HKEY hkSubPnp = NULL;

        if ( RegOpenKeyEx( hkPnp, acSubPnp, 0, KEY_READ,
                           &hkSubPnp ) != ERROR_SUCCESS )
        { printf( "Could not read from HKLM\\Enum\\...\\%S\n", acSubPnp ); }

        // Look for the PORTNAME value
        TCHAR acValue[128];
        dwSize = sizeof( acValue );

        if ( RegQueryValueEx( hkSubPnp, L"PORTNAME", NULL, NULL, ( BYTE * )acValue,
                              &dwSize ) == ERROR_SUCCESS )
        {
            std::wstring strPortName( acValue );

            // Got the portname value. Look for a friendly name.
            std::wstring strFriendlyName;
            dwSize = sizeof( acValue );

            if ( RegQueryValueEx( hkSubPnp, L"FRIENDLYNAME", NULL, NULL, ( BYTE * )acValue,
                                  &dwSize ) == ERROR_SUCCESS )
            { strFriendlyName = acValue; }

            // Prepare an entry for the output array.
            SSerInfo si;
            /*si.strDevPath = L"\\\\.\\" + strPortName;
            si.strPortName = strPortName;
            si.strFriendlyName = strFriendlyName;*/

            wsprintf( si.stDevPath, _T( "\\\\.\\%s" ), strPortName.c_str() );
            wsprintf( si.stPortName, _T( "%s" ), strPortName.c_str() );
            wsprintf( si.stFriendlyName, _T( "%s" ), strFriendlyName.c_str() );
            si.bUsbDevice = bUsbDevice;

            // Overwrite duplicates.
            BOOL bDup = FALSE;

            for ( std::vector<SSerInfo>::iterator iter = vecSerInfo.begin(); iter != vecSerInfo.end() && !bDup; iter++ )
            {
                if ( 0 == strPortName.compare( iter->stPortName ) )
                {
                    bDup = TRUE;
                    break;
                }
            }

            if ( !bDup )
            {
                // Add an entry to the array
                vecSerInfo.push_back( si );
            }
        }

        RegCloseKey( hkSubPnp );
        hkSubPnp = NULL;
        dwSize = sizeof( acSubPnp ); // restore the buffer size
    }

}
