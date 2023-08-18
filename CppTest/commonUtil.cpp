#include "commonUtil.h"
#include <iphlpapi.h>
#include <ws2tcpip.h>
#include <iostream>
#include <iomanip>
namespace CREG 
{
    // 解析注册表二进制类型的数据，处理还原成注册表中显示的16进制字符串

// 数字处理，注册表二进制数据解析
    void NumToHexStrW(DWORD dwNum, CAtlStringW& str)
    {
        UINT Temp = 0;
        UINT index = 0;
        while (dwNum > 0)
        {
            Temp = dwNum % 16;
            if (Temp < 10) {
                str.AppendChar(Temp + _T('0'));
            }
            else {
                str.AppendChar(_T('A') + Temp - 10);
            }
            dwNum = dwNum >> 4;
            index++;
        }
        // 补全字符串
        for (UINT j = 0; j < 4 - index; j++)
        {
            str.AppendChar(L'0');
        }

        str.MakeReverse();
        CAtlStringW aa = str.Mid(2, 3);
        CAtlStringW bb = str.Left(2);

        str.Format(L"%ws %ws", aa, bb);
    }

    // 还原注册表二进制数据类型格式
    CAtlStringW RegBinaryStrProcessingW(LPCWSTR lpszData, DWORD dwLength)
    {
        CAtlStringW strData;
        for (ULONG i = 0; i < dwLength; i++)
        {
            CAtlStringW str;
            NumToHexStrW(lpszData[i], str);
            strData.AppendFormat(L"%ws ", str);
        }
        return strData;
    }
    
    CAtlString ReadRegBinaryValue(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValue)
    {
        CAtlString strBinaryValue;

        DWORD dwFlags = REG_BINARY;
        HKEY hKeyResult;
        BOOL ret = RegOpenKeyEx(hKey, lpSubKey, 0, KEY_READ, &hKeyResult);

        if (ERROR_SUCCESS == ret)
        {
            DWORD dwLength = 0;

            // 获得读取键值有多少个字符
            RegQueryValueEx(hKeyResult, lpValue, NULL, &dwFlags, NULL, &dwLength);

            // 申请一段空间，并初始化为空
            TCHAR* BinaryInfo = new TCHAR[dwLength + 1];
            memset(BinaryInfo, 0, sizeof(TCHAR) * (dwLength + 1));

            if (ERROR_SUCCESS == RegQueryValueEx(hKeyResult, lpValue, NULL, &dwFlags, (LPBYTE)BinaryInfo, &dwLength))
            {
                // 解析还原成字符串
                strBinaryValue = RegBinaryStrProcessingW(BinaryInfo, dwLength + 1);
            }
            delete[] BinaryInfo;
        }
        RegCloseKey(hKeyResult);
        return strBinaryValue;
    }

    ULONGLONG ReadRegBinaryForSysTime(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValue)
    {
        ULONGLONG stamp = 0;
        DWORD dwFlags = REG_BINARY;
        HKEY hKeyResult;
        BOOL ret = RegOpenKeyEx(hKey, lpSubKey, 0, KEY_READ, &hKeyResult);

        if (ERROR_SUCCESS == ret)
        {
            DWORD dwLength = 0;

            // 获得读取键值有多少个字符
            RegQueryValueEx(hKeyResult, lpValue, NULL, &dwFlags, NULL, &dwLength);

            // 申请一段空间，并初始化为空
            TCHAR* BinaryInfo = new TCHAR[dwLength + 1];
            memset(BinaryInfo, 0, sizeof(TCHAR) * (dwLength + 1));

            ULARGE_INTEGER uDrvTimeStamp;
            if (ERROR_SUCCESS == RegQueryValueEx(hKeyResult, lpValue, NULL, &dwFlags, (LPBYTE)&uDrvTimeStamp.QuadPart, &dwLength))
            {
                stamp = uDrvTimeStamp.QuadPart;
                FILETIME fTime;
                SYSTEMTIME SysTime = { 0 };
                fTime.dwLowDateTime = uDrvTimeStamp.LowPart;
                fTime.dwHighDateTime = uDrvTimeStamp.HighPart;
                FileTimeToSystemTime(&fTime, &SysTime);
                printf("%02d-%02d-%02d\n", SysTime.wYear, SysTime.wMonth, SysTime.wDay);
            }
            delete[] BinaryInfo;
        }
        RegCloseKey(hKeyResult);
        return stamp;
    }

    BOOL ModifyRegSZHKEY(LPCWSTR lpKeyPath, LPCWSTR lpSubKey, LPCWSTR lpSubKeyItem, LPCWSTR lpItemValue, UINT32 uLen)
    {
        HKEY hKey = NULL, hSubKey = NULL;
        DWORD dwResOpen = 0;
        BOOL bRet = TRUE;

        if (ERROR_SUCCESS != RegCreateKeyEx(HKEY_LOCAL_MACHINE,
            lpKeyPath,
            NULL,
            NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            NULL,
            &hKey,
            &dwResOpen))
        {
            /*LOG(INFO) << "lpKeyPath :[" << SysUtil::ws2s(lpKeyPath).c_str()
                << "], lpSubKey:[" << SysUtil::ws2s(lpSubKey).c_str()
                << "], lpSubKeyItem:[" << SysUtil::ws2s(lpSubKeyItem).c_str()
                << "], lpItemValue:[" << SysUtil::ws2s(lpItemValue).c_str()
                << "], uLen:[" << uLen
                << "], RegCreateKeyEx  err 1";*/
            bRet = FALSE;
            return bRet;
        }

        if (ERROR_SUCCESS != RegCreateKeyEx(hKey,
            lpSubKey,
            NULL,
            NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            NULL,
            &hSubKey,
            &dwResOpen))
        {
            /*LOG(INFO) << "lpKeyPath :[" << SysUtil::ws2s(lpKeyPath).c_str()
                << "], lpSubKey:[" << SysUtil::ws2s(lpSubKey).c_str()
                << "], lpSubKeyItem:[" << SysUtil::ws2s(lpSubKeyItem).c_str()
                << "], lpItemValue:[" << SysUtil::ws2s(lpItemValue).c_str()
                << "], uLen:[" << uLen
                << "], RegCreateKeyEx  err 2";*/
            bRet = FALSE;
            goto reg_err;
        }

        if (ERROR_SUCCESS != ::RegSetValueEx(hSubKey, lpSubKeyItem, 0, REG_SZ, (CONST BYTE*) lpItemValue, uLen))
        {
            bRet = FALSE;
            /*LOG(INFO) << "lpKeyPath :[" << SysUtil::ws2s(lpKeyPath).c_str()
                << "], lpSubKey:[" << SysUtil::ws2s(lpSubKey).c_str()
                << "], lpSubKeyItem:[" << SysUtil::ws2s(lpSubKeyItem).c_str()
                << "], lpItemValue:[" << SysUtil::ws2s(lpItemValue).c_str()
                << "], uLen:[" << uLen
                << "], RegSetValueEx  err";*/
        }

        RegCloseKey(hSubKey);
    reg_err:
        RegCloseKey(hKey);
        return bRet;
    }

    DWORD EnumSubKeys(HKEY keyDomain, CString szRegKeyPath, std::vector<CString>& subKeys, bool bWow64)
    {
        subKeys.clear();
        DWORD dwRet = 0;
        HKEY hKey = NULL;
        dwRet = RegOpenKeyEx(keyDomain, szRegKeyPath, REG_NONE, bWow64 ? KEY_READ | KEY_WOW64_64KEY : KEY_READ, &hKey);
        if (dwRet == ERROR_SUCCESS)
        {
            //TCHAR achKey[MAX_PATH] = { 0 };
            DWORD nSubKeyCount = 0;
            DWORD nSize = 0;
            DWORD nMaxSubKeyLen = 0;
            dwRet = RegQueryInfoKey(hKey, 0, 0, 0, &nSubKeyCount, &nMaxSubKeyLen, 0, 0, 0, 0, 0, 0);
            if (dwRet == ERROR_SUCCESS)
            {
                nSize = nMaxSubKeyLen + 1;
                TCHAR* achKey = new TCHAR[nSize];
                if (!achKey)
                    return dwRet;
                size_t bufferLen = (nMaxSubKeyLen + 1) * sizeof(TCHAR);
                for (int index = 0; index < nSubKeyCount; ++index)
                {
                    ZeroMemory(achKey, bufferLen);
                    dwRet = ::RegEnumKey(hKey, index, achKey, nSize);
                    if (ERROR_SUCCESS == dwRet)
                        subKeys.push_back(achKey);
                }
                delete[] achKey;
            }
            RegCloseKey(hKey);
        }
        return dwRet;
    }

}

/////////////////////////////////////////////////
namespace CUtils
{
    std::string UnicodeToUtf8(const std::wstring& wstr)
    {
        std::string ret_str = "";
        int ansiiLen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
        char* pAssii = (char*)malloc(sizeof(char) * ansiiLen);
        WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
        if (nullptr != pAssii)
        {
            ret_str = pAssii; 
        }
        free(pAssii);
        
        return ret_str;
    }

    std::string UnicodeToAscii(const std::wstring& wstr)
    {
        std::string ret_str = "";
        int ansiiLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
        char* pAssii = (char*)malloc(sizeof(char) * ansiiLen);
        WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
        if (nullptr != pAssii)
        {
            ret_str = pAssii;
        }
        free(pAssii);

        return ret_str;
    }

    std::wstring Utf8ToUnicode(const std::string& str)
    {
        std::wstring ret_str = L"";
        int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
        wchar_t* pUnicode = (wchar_t*)malloc(sizeof(wchar_t) * unicodeLen);
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, pUnicode, unicodeLen);
        if (nullptr != pUnicode)
        {
            ret_str = pUnicode;
        }
        
        free(pUnicode);
        return ret_str;
    }

    std::wstring AsciiToUnicode(const std::string& str)
    {
        std::wstring ret_str = L"";
        int unicodeLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
        wchar_t* pUnicode = (wchar_t*)malloc(sizeof(wchar_t) * unicodeLen);
        MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pUnicode, unicodeLen);
        if (nullptr != pUnicode)
        {
            ret_str = pUnicode;
        }

        free(pUnicode);
        return ret_str;
    }

    bool blCheckUdpPortListen(unsigned int nPort)
    {
        if (nPort < 1024 || nPort > 65000)
        {
            return false;
        }

        PMIB_UDPTABLE pudptable = NULL;
        DWORD dwSize = 0;

        if (GetUdpTable(pudptable, &dwSize, TRUE) == ERROR_INSUFFICIENT_BUFFER)
        {
            pudptable = new MIB_UDPTABLE[dwSize];

            if (GetUdpTable(pudptable, &dwSize, TRUE) == NO_ERROR)
            {
                for (UINT i = 0; i < pudptable->dwNumEntries; i++)
                {
                    if (nPort != ntohs(pudptable->table[i].dwLocalPort))
                    {
                        continue;
                    }

                    delete[] pudptable;
                    return true;
                }
            }
        }

        delete[] pudptable;
        return false;
    }

    BOOL ModifyFileExtension(std::wstring path, std::wstring srcType, std::wstring destType)
    {
        WIN32_FIND_DATA fd;
        std::wstring srcFiles = path + srcType;
        HANDLE hFindFile = FindFirstFile(srcFiles.c_str(), &fd);
        if (hFindFile == INVALID_HANDLE_VALUE)
        {
            ::FindClose(hFindFile);
            return FALSE;
        }

        BOOL bIsDirectory = FALSE;
        BOOL bFinish = FALSE;

        CString strSubDirPath;

        while (!bFinish)
        {
            bIsDirectory = ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);

            //如果是.或..  
            if (bIsDirectory && (wcscmp(fd.cFileName, L".") == 0 || wcscmp(fd.cFileName, L"..") == 0))
            {
                bFinish = (FindNextFile(hFindFile, &fd) == FALSE);
                continue;
            }
            std::wstring tempFile = path + fd.cFileName;
            std::wstring DestFile = tempFile + destType;
            MoveFile(tempFile.c_str(), DestFile.c_str());
            bFinish = (FindNextFile(hFindFile, &fd) == FALSE);
        }

        ::FindClose(hFindFile);

        return FALSE;
    }

    BOOL ParseDomain(LPCTSTR pszDomain)
    {
        BOOL bRet = TRUE;
        int iResult, i = 1, iRet = 0;
        DWORD dwRetval, dwNamespace = NS_ALL;
        LPGUID lpNspid = NULL;
        ADDRINFOEX* result = NULL;
        ADDRINFOEX* ptr = NULL;
        ADDRINFOEX hints;

        // LPSOCKADDR sockaddr_ip;
        struct sockaddr_in* sockaddr_ipv4;
        struct sockaddr_in6* sockaddr_ipv6;

        // DWORD ipbufferlength = 46;
        wchar_t ipstringbuffer[46];

        // variables needed to print namespace provider GUID
        WCHAR GuidString[40] = { 0 };

        //--------------------------------
        // Setup the hints address info structure
        // which is passed to the getaddrinfo() function
        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        dwNamespace = (DWORD)NS_ALL;

        //--------------------------------
        // Call getaddrinfoex(). If the call succeeds,
        // the result variable will hold a linked list
        // of addrinfo structures containing response
        // information
        dwRetval = GetAddrInfoEx(pszDomain, _T("0"), dwNamespace, lpNspid, &hints, &result,
            NULL, NULL, NULL, NULL);
        //WSAHOST_NOT_FOUND
        if (dwRetval != 0)
        {
            std::cout << "GetAddrInfoEx failed with error: [" << dwRetval << "]" << std::endl;
            bRet = FALSE;
            goto end_parse;
        }

        std::cout << "GetAddrInfoEx returned success" << std::endl;

        // Retrieve each address and print out the hex bytes
        for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
        {
            std::cout << "GetAddrInfoEx response :" << i++;
            std::cout << "Flags: 0x" << std::hex << ptr->ai_flags << std::endl;

            switch (ptr->ai_family)
            {
            case AF_UNSPEC:
                std::cout << "Family: " << "Unspecified" << std::endl;
                break;

            case AF_INET:
                std::cout << "Family: " << "AF_INET (IPv4)" << std::endl;
                // the InetNtop function is available on Windows Vista and later
                sockaddr_ipv4 = (struct sockaddr_in*)ptr->ai_addr;
                std::cout << "IPv4 address :" << UnicodeToUtf8(InetNtop(AF_INET, &sockaddr_ipv4->sin_addr, ipstringbuffer, 46)) << std::endl;

                // We could also use the WSAAddressToString function
                // sockaddr_ip = (LPSOCKADDR) ptr->ai_addr;
                // The buffer length is changed by each call to WSAAddresstoString
                // So we need to set it for each iteration through the loop for safety
                // ipbufferlength = 46;
                // iRetval = WSAAddressToString(sockaddr_ip, (DWORD) ptr->ai_addrlen, NULL,
                //    ipstringbuffer, &ipbufferlength );
                // if (iRetval)
                //    wprintf(L"WSAAddressToString failed with %u\n", WSAGetLastError() );
                // else
                //    wprintf(L"\tIPv4 address %ws\n", ipstringbuffer);
                break;

            case AF_INET6:
                std::cout << "AF_INET6 (IPv6)";
                // the InetNtop function is available on Windows Vista and later
                sockaddr_ipv6 = (struct sockaddr_in6*)ptr->ai_addr;
                std::cout << "IPv6 address :" << UnicodeToUtf8(InetNtop(AF_INET6, &sockaddr_ipv6->sin6_addr, ipstringbuffer, 46))<<std::endl;

                // We could also use WSAAddressToString which also returns the scope ID
                // sockaddr_ip = (LPSOCKADDR) ptr->ai_addr;
                // The buffer length is changed by each call to WSAAddresstoString
                // So we need to set it for each iteration through the loop for safety
                // ipbufferlength = 46;
                //iRetval = WSAAddressToString(sockaddr_ip, (DWORD) ptr->ai_addrlen, NULL,
                //    ipstringbuffer, &ipbufferlength );
                //if (iRetval)
                //    wprintf(L"WSAAddressToString failed with %u\n", WSAGetLastError() );
                //else
                //    wprintf(L"\tIPv6 address %ws\n", ipstringbuffer);
                break;

            default:
                std::cout << "Other :" << ptr->ai_family << std::endl;
                break;
            }
        }

        FreeAddrInfoEx(result);
    end_parse:
        std::cout << "end_parse, bRet:" << bRet << std::endl;
        return bRet;
    }

    typedef struct _QueryContext
    {
        OVERLAPPED      QueryOverlapped;
        PADDRINFOEX     QueryResults;
        HANDLE          CompleteEvent;
    }QUERY_CONTEXT, * PQUERY_CONTEXT;
#define MAX_ADDRESS_STRING_LENGTH   64
    //
// Callback function called by Winsock as part of asynchronous query complete
//

    VOID
        WINAPI
        QueryCompleteCallback(
            _In_ DWORD Error,
            _In_ DWORD Bytes,
            _In_ LPOVERLAPPED Overlapped
        )
    {
        PQUERY_CONTEXT  QueryContext = NULL;
        PADDRINFOEX     QueryResults = NULL;
        WCHAR           AddrString[MAX_ADDRESS_STRING_LENGTH];
        DWORD           AddressStringLength;

        UNREFERENCED_PARAMETER(Bytes);

        QueryContext = CONTAINING_RECORD(Overlapped,
            QUERY_CONTEXT,
            QueryOverlapped);

        if (Error != ERROR_SUCCESS)
        {
            wprintf(L"ResolveName failed with %d\n", Error);
            goto exit;
        }

        wprintf(L"ResolveName succeeded. Query Results:\n");

        QueryResults = QueryContext->QueryResults;

        while (QueryResults)
        {
            AddressStringLength = MAX_ADDRESS_STRING_LENGTH;

            WSAAddressToString(QueryResults->ai_addr,
                (DWORD)QueryResults->ai_addrlen,
                NULL,
                AddrString,
                &AddressStringLength);

            wprintf(L"Ip Address: %s\n", AddrString);
            QueryResults = QueryResults->ai_next;
        }

    exit:

        if (QueryContext->QueryResults)
        {
            FreeAddrInfoEx(QueryContext->QueryResults);
        }

        //
        //  Notify caller that the query completed
        //

        SetEvent(QueryContext->CompleteEvent);
        return;
    }

    int HostNameToIP(std::wstring hostname)
    {
        INT                 Error = ERROR_SUCCESS;
        WSADATA             wsaData;
        BOOL                IsWSAStartupCalled = FALSE;
        ADDRINFOEX          Hints;
        QUERY_CONTEXT       QueryContext;
        HANDLE              CancelHandle = NULL;
        DWORD               QueryTimeout = 5 * 1000; // 5 seconds

        ZeroMemory(&QueryContext, sizeof(QueryContext));       
        //
        //  All Winsock functions require WSAStartup() to be called first
        //

        Error = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (Error != 0)
        {
            wprintf(L"WSAStartup failed with %d\n", Error);
            goto exit;
        }

        IsWSAStartupCalled = TRUE;

        ZeroMemory(&Hints, sizeof(Hints));
        Hints.ai_family = AF_UNSPEC;

        //
        //  Note that this is a simple sample that waits/cancels a single
        //  asynchronous query. The reader may extend this to support
        //  multiple asynchronous queries.
        //

        QueryContext.CompleteEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

        if (QueryContext.CompleteEvent == NULL)
        {
            Error = GetLastError();
            wprintf(L"Failed to create completion event: Error %d\n", Error);
            goto exit;
        }

        //
        //  Initiate asynchronous GetAddrInfoExW.
        //
        //  Note GetAddrInfoEx can also be invoked asynchronously using an event
        //  in the overlapped object (Just set hEvent in the Overlapped object
        //  and set NULL as completion callback.)
        //
        //  This sample uses the completion callback method.
        //

        Error = GetAddrInfoExW(hostname.c_str(),
            NULL,
            NS_DNS,
            NULL,
            &Hints,
            &QueryContext.QueryResults,
            NULL,
            &QueryContext.QueryOverlapped,
            QueryCompleteCallback,
            &CancelHandle);

        //
        //  If GetAddrInfoExW() returns  WSA_IO_PENDING, GetAddrInfoExW will invoke
        //  the completion routine. If GetAddrInfoExW returned anything else we must
        //  invoke the completion directly.
        //

        if (Error != WSA_IO_PENDING)
        {
            QueryCompleteCallback(Error, 0, &QueryContext.QueryOverlapped);
            goto exit;
        }

        //
        //  Wait for query completion for 5 seconds and cancel the query if it has
        //  not yet completed.
        //

        if (WaitForSingleObject(QueryContext.CompleteEvent,
            QueryTimeout) == WAIT_TIMEOUT)
        {

            //
            //  Cancel the query: Note that the GetAddrInfoExCancelcancel call does
            //  not block, so we must wait for the completion routine to be invoked.
            //  If we fail to wait, WSACleanup() could be called while an
            //  asynchronous query is still in progress, possibly causing a crash.
            //

            wprintf(L"The query took longer than %d seconds to complete; "
                L"cancelling the query...\n", QueryTimeout / 1000);

            GetAddrInfoExCancel(&CancelHandle);

            WaitForSingleObject(QueryContext.CompleteEvent,
                INFINITE);
        }

    exit:

        if (IsWSAStartupCalled)
        {
            WSACleanup();
        }

        if (QueryContext.CompleteEvent)
        {
            CloseHandle(QueryContext.CompleteEvent);
        }

        return Error;
    }
}
