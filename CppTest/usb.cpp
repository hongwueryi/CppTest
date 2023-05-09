#include <windows.h>
#include <SetupAPI.h>
#include <cfgmgr32.h>
#include <regex>
#include <iostream>
#include <tchar.h>
#include <string>
#include "usb.h"
#include <locale.h>
#include <initguid.h>
#include <regex>
#pragma comment(lib, "Cfgmgr32.lib")
using namespace std;
DEFINE_GUID(GUID_CLASS_I82930_MIC, 0x877fc334, 0xf128, 0x47f4, 0x90, 0x50, 0x7c, 0x3e, 0x78, 0x25, 0x95, 0x2b);
//
DEFINE_GUID(GUID_CLASS_MONITOR, 0x4d36e96e, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

std::string ws2s(const std::wstring& ws)
{
    std::string curLocale = setlocale(LC_ALL, NULL);      // curLocale = "C";
    setlocale(LC_ALL, "chs");
    const wchar_t* _Source = ws.c_str();
    size_t _Dsize = 2 * ws.size() + 1;
    char* _Dest = new char[_Dsize];
    memset(_Dest, 0, _Dsize);
    wcstombs(_Dest, _Source, _Dsize);
    std::string result = _Dest;
    delete[]_Dest;
    setlocale(LC_ALL, curLocale.c_str());
    return result;
}

int dwGetCurDrvInfo(LPGUID pClsGuid, LPCTSTR lpEnumerator, TCHAR* psRegex[], int nRegexNum, DevDrvInfo* pInfo)
{
#if 0
    TCHAR* arrSpeakerHard[2] = { NULL, L"USB\\\\Vid_1d6b&Pid_0105&Rev_.{4}&MI_00" };
    wstring wstrHardid = L"USB\\Vid_1d6b&Pid_0105&Rev_0101&MI_00";
    wregex pattern(arrSpeakerHard[1]);
    wsmatch  matchResult;
    //wprintf(L"vidpid=%s\n", wstrHardid.c_str());
    if (regex_match(wstrHardid, matchResult, pattern))
    {
        int num = 0;
    }

#endif

    int nRet = ERR_DEVICE_NO_FOUND, iIndex = 0, i = 0;
    DWORD dwProblem = 0, dwDevState = 0;
    ULARGE_INTEGER DrvDate_Cur = { 0 };
    ULARGE_INTEGER DrvDate_New = { 0 };
    TCHAR szHardWareID[512] = { 0 };
    SP_DEVINFO_DATA DeviceInfoData;
    SP_DRVINFO_DATA DrvInfoData;
    wstring wstrVer;
    string strVer;
    string descrip;
    bool IsDisableable = false, IsDisabled = false;

    DevDrvInfo m_curDrvInfo;
    memset(&m_curDrvInfo, 0, sizeof(m_curDrvInfo));

    if (pInfo)
    {
        memset(pInfo, 0, sizeof(m_curDrvInfo));
    }

    if (0 == nRegexNum)
    {
        nRet = ERR_PARAM_ERROR;
        goto param_err;
    }

    HDEVINFO hDevInfo = SetupDiGetClassDevs(pClsGuid, lpEnumerator, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);

    if (hDevInfo == INVALID_HANDLE_VALUE)
    {
        printf("SetupDiGetClassDevs err, pClsGuid = %s\n", (char*)pClsGuid);
        nRet = ERR_PARAM_ERROR;
        goto param_err;
    }

    while (DEV_DETECT_UNKNOWN == m_curDrvInfo.uDevVendor)
    {
        memset(szHardWareID, sizeof(szHardWareID), 0);
        DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

        if (!SetupDiEnumDeviceInfo(hDevInfo, iIndex, &DeviceInfoData))
        {
            printf("dwGetCurDrvInfo::SetupDiEnumDeviceInfo err GetLastError:[0x%0x]\n", GetLastError());
            break;
        }

        DWORD dwStat = CM_Get_DevNode_Status(&dwDevState, &dwProblem, DeviceInfoData.DevInst, 0);
        printf("%d------hardid:[%s], dwDevState:[0x%0x], dwProblem:[0x%0x], nRet:%d\n", iIndex, ws2s(szHardWareID).c_str(), dwDevState, dwProblem, dwStat);
        if (!SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_HARDWAREID,
            NULL, (PBYTE)szHardWareID, sizeof(szHardWareID) - 2, NULL))
        {
            iIndex++;
            continue;
        }
        
        
        /*for (int j = 0; j <= SPDRP_MAXIMUM_PROPERTY; j++)
        {
        TCHAR tsInfo[2048] = {0};
        if (!SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, j,
        NULL, (PBYTE)tsInfo, sizeof(tsInfo) - 2, NULL))
        {
        continue;
        }
        LOG(INFO) << "SPDRP_I:[0x" << hex << setw(8) << j << "], tsInfo:[" << SysUtil::ws2s(tsInfo).c_str() << "]";
        }*/

        for (i = 1; i < nRegexNum; i++)
        {
            wstring wstrHardid = szHardWareID;
            wregex pattern(psRegex[i]);
            wsmatch  matchResult;
            wprintf(L"vidpid=%s\n", wstrHardid.c_str());
            if (regex_match(wstrHardid, matchResult, pattern))
            {
                m_curDrvInfo.uDevVendor = i;
                printf("input hardware regex:[%s], get sys:[%s], DevVendor:[%d]\n",
                    ws2s(psRegex[i]).c_str(),
                    ws2s(szHardWareID).c_str(), i);
                //break;
            }
        }

        iIndex++;
    }

    if (DEV_DETECT_UNKNOWN == m_curDrvInfo.uDevVendor)
    {
        m_curDrvInfo.uDrvDetectRet = DEV_DETECT_UNKNOWN;
        if (999 == nRegexNum)
        {
            nRet = ERR_DEVICE_NEED_REPAIR;
            m_curDrvInfo.uDrvDetectRet |= DEV_DETECT_DRV_DISABLE;
        }
        printf("detect driver err, drv type:%d, nRet:%d\n", m_curDrvInfo.uDevVendor, nRet);
        goto enum_err;
    }

    m_curDrvInfo.uDrvDetectRet |= DEV_DETECT_TYPE_KNOWN;
    nRet = DEVICE_NORMAL;

    DWORD dwStat = CM_Get_DevNode_Status(&dwDevState, &dwProblem, DeviceInfoData.DevInst, 0);
    printf("------dwDevState:[0x%0x], dwProblem:[0x%0x], nRet:%d\n", dwDevState, dwProblem, dwStat);
    if (dwStat != CR_SUCCESS || dwProblem != 0)
    {
        nRet = ERR_DEVICE_NEED_REPAIR;
        printf("abnormal dwDevState:[0x%0x], dwProblem:[0x%0x], nRet:%d\n", dwDevState, dwProblem, nRet);
        if (CM_PROB_DISABLED == dwProblem)
        {
            m_curDrvInfo.uDrvDetectRet |= DEV_DETECT_DRV_DISABLE;
        }
        else
        {
            m_curDrvInfo.uDrvDetectRet |= DEV_DETECT_DRV_NEED_REINSTALL;
        }
    }
    else
    {
        printf("normal dwDevState:[0x%0x], dwProblem:[0x%0x], nRet:%d\n", dwDevState, dwProblem, nRet);
    }

    ////////IsDisableable = ((dwDevState & DN_DISABLEABLE) && (dwProblem != CM_PROB_HARDWARE_DISABLED));
    ////////IsDisabled = ((dwDevState & DN_HAS_PROBLEM) && (dwProblem == CM_PROB_DISABLED));
    ////////LOG(INFO) << "IsDisableable:[" << IsDisableable << "], IsDisabled:[" << IsDisabled << "]";

    DrvInfoData.cbSize = sizeof(SP_DRVINFO_DATA);
    SetupDiBuildDriverInfoList(hDevInfo, &DeviceInfoData, SPDIT_COMPATDRIVER);

    if (!SetupDiEnumDriverInfo(hDevInfo, &DeviceInfoData, SPDIT_COMPATDRIVER, 0, &DrvInfoData))
    {
        printf("SetupDiEnumDriverInfo err:%0x", GetLastError());
        nRet = ERR_DEVICE_NEED_REPAIR;
        m_curDrvInfo.uDrvDetectRet |= DEV_DETECT_DRV_NEED_REINSTALL;
        goto enum_err;
    }

    m_curDrvInfo.uDrvTimeStamp.HighPart = DrvInfoData.DriverDate.dwHighDateTime;
    m_curDrvInfo.uDrvTimeStamp.LowPart = DrvInfoData.DriverDate.dwLowDateTime;
    _swprintf(m_curDrvInfo.tDrvVerDesc, L"%lu.%lu.%lu.%lu",
        (DWORD)(DrvInfoData.DriverVersion >> 48) & 0xFFFF,
        (DWORD)(DrvInfoData.DriverVersion >> 32) & 0xFFFF,
        (DWORD)(DrvInfoData.DriverVersion >> 16) & 0xFFFF,
        (DWORD)DrvInfoData.DriverVersion & 0xFFFF);
    m_curDrvInfo.uDrvDetectRet |= DEV_DETECT_DRV_KNOWN;
    wstrVer = m_curDrvInfo.tDrvVerDesc;
    strVer = ws2s(wstrVer);
    descrip = ws2s(DrvInfoData.Description);
    cout << "Driver type detected result, nRet:" << nRet
        << ", m_curDrvInfo.uDrvDetectRet:" << m_curDrvInfo.uDrvDetectRet
        << ", uDevVendor:" << m_curDrvInfo.uDevVendor
        << ", driver version:" << strVer.c_str() << ", llver:" << DrvInfoData.DriverVersion 
        << ", description:" << descrip
        << std::endl;

enum_err:

    if (pInfo)
    {
        memcpy(pInfo, &m_curDrvInfo, sizeof(m_curDrvInfo));
    }

    SetupDiDestroyDeviceInfoList(hDevInfo);
param_err:
    return nRet;
}

#define LOG(INFO) cout
int GetDrvStatusByName(std::wstring FriendlyName)
{
    int nRet = 0;
    cout << "SetDrvStatusByName Enter  strDesName:" << ws2s(FriendlyName) << std::endl;
    HDEVINFO hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
    if (hDevInfo == INVALID_HANDLE_VALUE)
    {
        cout << "SetDrvStatusByName is Error" << endl;
        return nRet;
    }
    int iIndex = 0;
    TCHAR szDevDes[512] = { 0 };
    SP_DEVINFO_DATA DeviceInfoData;
    memset(szDevDes, sizeof(szDevDes), 0);
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    while (SetupDiEnumDeviceInfo(hDevInfo, iIndex, &DeviceInfoData))
    {
        if (!SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_FRIENDLYNAME,
            NULL, (PBYTE)szDevDes, sizeof(szDevDes) - 2, NULL))
        {
            iIndex++;
            continue;
        }
        std::wstring strDevDes = szDevDes;
        wsmatch  matchResult;
        wregex pattern(FriendlyName);
        if (std::regex_match(strDevDes, matchResult, pattern))
        {
            printf("-----%s----\n", ws2s(strDevDes).c_str());
        }
        if (strDevDes.find(FriendlyName) != std::wstring::npos)
        {
            nRet = 1;
            printf("%s\n", ws2s(strDevDes).c_str());
            //break;
        }
        iIndex++;
    }
    SetupDiDestroyDeviceInfoList(hDevInfo);
    cout << "SetDrvStatusByName End, isfind speaker=" << nRet << endl;
    return nRet;
}

BOOL ListDeviceInstancePath(char* strVer)
{
    HDEVINFO hdev = INVALID_HANDLE_VALUE;
    DWORD idx = 0;
    GUID guid = GUID_CLASS_I82930_MIC;
    BOOL bRet = FALSE;
    BOOL nStatus;
    DWORD dwSize = 0;

    //获取由guid所指定类型的系统中已经安装的设备接口类集合的句柄
    hdev = SetupDiGetClassDevs(&guid,
        NULL,
        NULL,
        DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

    if (hdev == INVALID_HANDLE_VALUE)
    {
        LOG(ERROR) << "ERROR : Unable to enumerate device GetLastError is:" << hex << GetLastError();
        return FALSE;
    }

    SP_DEVICE_INTERFACE_DATA  DeviceInterfaceData;
    DeviceInterfaceData.cbSize = sizeof(DeviceInterfaceData);

    for (idx = 0; SetupDiEnumDeviceInterfaces(hdev, NULL, &guid, idx, &DeviceInterfaceData); idx++)
    {
        nStatus = SetupDiGetDeviceInterfaceDetail(hdev, &DeviceInterfaceData, NULL, 0, &dwSize, NULL);

        if (!dwSize)
        {
            bRet = FALSE;
            LOG(ERROR) << "SetupDiGetDeviceInterfaceDetail GetLastError:" << GetLastError();
            break;
        }

        PSP_DEVICE_INTERFACE_DETAIL_DATA_A pBuffer = (PSP_DEVICE_INTERFACE_DETAIL_DATA_A)malloc(dwSize);
        ZeroMemory(pBuffer, sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_A));
        pBuffer->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_A);

        SP_DEVINFO_DATA DeviceInfoData = { sizeof(SP_DEVINFO_DATA) };
        nStatus = SetupDiGetDeviceInterfaceDetailA(hdev, &DeviceInterfaceData, pBuffer, dwSize, &dwSize, &DeviceInfoData);

        LOG(INFO) << "DeviceInterfaceData.Flags:[" << DeviceInterfaceData.Flags << "]";

        if (!nStatus)
        {
            bRet = FALSE;
            free(pBuffer);
            LOG(ERROR) << "ERROR : SetupDiGetDeviceInterfaceDetailA fial, GetLastError:" << GetLastError();
            break;
        }

        //wprintf(L"%s\n", pBuffer->DevicePath);
        //strVer = pBuffer->DevicePath;
        bRet = TRUE;
        strcpy(strVer, pBuffer->DevicePath);
        printf("DevicePath:%s\n", strVer);
        free(pBuffer);
    }

    SetupDiDestroyDeviceInfoList(hdev);

    return bRet;
}

BOOL ListDeviceInstancePath(wchar_t* strclass)
{
    HDEVINFO hdev = INVALID_HANDLE_VALUE;
    DWORD idx = 0;
    GUID guid = GUID_CLASS_MONITOR;
    BOOL bRet = FALSE;
    BOOL nStatus;
    DWORD dwSize = 0;

    //获取由guid所指定类型的系统中已经安装的设备接口类集合的句柄
    hdev = SetupDiGetClassDevs(&guid,
        NULL,
        NULL,
        DIGCF_PRESENT | DIGCF_ALLCLASSES);

    if (hdev == INVALID_HANDLE_VALUE)
    {
        LOG(ERROR) << "ERROR : Unable to enumerate device GetLastError is:" << hex << GetLastError();
        return FALSE;
    }

    SP_DEVICE_INTERFACE_DATA  DeviceInterfaceData;
    DeviceInterfaceData.cbSize = sizeof(DeviceInterfaceData);
    //{4d36e96e-e325-11ce-bfc1-08002be10318}
    for (idx = 0; SetupDiEnumDeviceInterfaces(hdev, NULL, NULL, idx, &DeviceInterfaceData); idx++)
    {
        nStatus = SetupDiGetDeviceInterfaceDetail(hdev, &DeviceInterfaceData, NULL, 0, &dwSize, NULL);

        if (!dwSize)
        {
            bRet = FALSE;
            LOG(ERROR) << "SetupDiGetDeviceInterfaceDetail GetLastError:" << GetLastError();
            break;
        }

        PSP_DEVICE_INTERFACE_DETAIL_DATA_A pBuffer = (PSP_DEVICE_INTERFACE_DETAIL_DATA_A)malloc(dwSize);
        ZeroMemory(pBuffer, sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_A));
        pBuffer->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_A);

        SP_DEVINFO_DATA DeviceInfoData = { sizeof(SP_DEVINFO_DATA) };
        nStatus = SetupDiGetDeviceInterfaceDetailA(hdev, &DeviceInterfaceData, pBuffer, dwSize, &dwSize, &DeviceInfoData);

        LOG(INFO) << "DeviceInterfaceData.Flags:[" << DeviceInterfaceData.Flags << "]";

        if (!nStatus)
        {
            bRet = FALSE;
            free(pBuffer);
            LOG(ERROR) << "ERROR : SetupDiGetDeviceInterfaceDetailA fial, GetLastError:" << GetLastError();
            break;
        }

        wprintf(L"%s\n", pBuffer->DevicePath);
        //strVer = pBuffer->DevicePath;
        bRet = TRUE;
        //strcpy(instancePath, pBuffer->DevicePath);
        //printf("DevicePath:%s\n", instancePath);
        free(pBuffer);
    }

    SetupDiDestroyDeviceInfoList(hdev);

    return bRet;
}

void ToUppercase(char* pData)
{
    if (NULL == pData || 0 == strlen(pData))
    {
        return;
    }

    int nLen = strlen(pData);

    for (size_t i = 0; i < nLen; i++)
    {
        if (pData[i] >= 'a' && pData[i] <= 'z')
        {
            pData[i] = pData[i] + ('A' - 'a');
        }
    }
}

BOOL ParseMicVer(char* pVer, char* pOut)
{
    BOOL bRet = FALSE;

    if (NULL == pVer || NULL == pOut)
    {
        return bRet;
    }

    do
    {
        ToUppercase(pVer);
        char* pTem1 = strstr(pVer, "UAC");

        if (NULL == pTem1)
        {
            break;
        }

        char* pTem2 = strstr(pTem1, "#");

        if (NULL == pTem2)
        {
            break;
        }

        strncpy(pOut, pTem1 + 3, pTem2 - pTem1 - strlen("UAC"));
        bRet = TRUE;
    } while (0);

    return bRet;
}

int getCurMicVer(char* pOutVer, int nBufLen)
{
    int nRet = DEVICE_NORMAL;
    char strCurVerInfo[MAX_PATH] = { 0 };

    if (!pOutVer || nBufLen < sizeof(strCurVerInfo))
    {
        return -1;
    }

    if (!ListDeviceInstancePath(strCurVerInfo))
    {
        printf("ListDeviceInstancePath failed.\n");
        return -1;
    }

    if (!ParseMicVer(strCurVerInfo, pOutVer))
    {
        printf("ParseMicVer failed.\n");
        return -1;
    }
    printf("pOutVer:%s\n", pOutVer);
    return nRet;
}

int dwGetCurDrvInfo1(LPGUID pClsGuid, LPCTSTR lpEnumerator, std::vector<wstring> psRegex, DevDrvInfo* pInfo, std::wstring strDriverName)
{
    int nRet = ERR_DEVICE_NO_FOUND, iIndex = 0, i = 1;
    DWORD dwProblem = 0, dwDevState = 0;
    ULARGE_INTEGER DrvDate_Cur = { 0 };
    ULARGE_INTEGER DrvDate_New = { 0 };
    TCHAR szHardWareID[512] = { 0 };
    SP_DEVINFO_DATA DeviceInfoData;
    SP_DRVINFO_DATA DrvInfoData;
    int uDevVendor = DEV_DETECT_UNKNOWN;
    wstring wstrVer;
    string strVer;
    std::vector<wstring>::iterator it;
    bool IsDisableable = false, IsDisabled = false;

    if (psRegex.empty())
    {
        nRet = ERR_PARAM_ERROR;
        LOG(ERROR) << "hardid psRegex is empty";
        return 0;
    }

    HDEVINFO hDevInfo = SetupDiGetClassDevs(pClsGuid, lpEnumerator, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);

    if (hDevInfo == INVALID_HANDLE_VALUE)
    {
        LOG(ERROR) << "SetupDiGetClassDevs err, pClsGuid = " << (char*)pClsGuid;
        nRet = ERR_PARAM_ERROR;
        return 0;
    }

    while (DEV_DETECT_UNKNOWN == uDevVendor)
    {
        memset(szHardWareID, sizeof(szHardWareID), 0);
        DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

        if (!SetupDiEnumDeviceInfo(hDevInfo, iIndex, &DeviceInfoData))
        {
            LOG(ERROR) << "dwGetCurDrvInfo::SetupDiEnumDeviceInfo err GetLastError:[0x" << hex << GetLastError() << "]";
            break;
        }

        if (!SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_HARDWAREID,
            NULL, (PBYTE)szHardWareID, sizeof(szHardWareID) - 2, NULL))
        {
            iIndex++;
            continue;
        }

        for (it = psRegex.begin(); it != psRegex.end(); ++it, i++)
        {
            wstring wstrHardid = szHardWareID;
            wregex pattern(*it);
            wsmatch  matchResult;
            printf("-----%s\n", ws2s(*it).c_str());
            //LOG(INFO) << "szHardWareID:" << ws2s(szHardWareID).c_str();
            //LOG(INFO) << "psRegex:" << SysUtil::ws2s(*it).c_str();
            if (regex_match(wstrHardid, matchResult, pattern))
            {
                LOG(INFO) << "szHardWareID:" << ws2s(szHardWareID).c_str();
                if (!strDriverName.empty())
                {
                    TCHAR szDesc[512] = { 0 };
                    //SPDRP_DEVICEDESC
                    if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_FRIENDLYNAME,
                        NULL, (PBYTE)szDesc, sizeof(szDesc) - 2, NULL))
                    {
                        wstring strDesc = szDesc;
                        LOG(INFO) << "SPDRP_FRIENDLYNAME:" << ws2s(strDesc).c_str() << ",strDriverInf:" << ws2s(strDriverName).c_str();
                        printf("\n");
                        if (strDesc.find(strDriverName) != std::wstring::npos)
                        {
                            //该值没有实际意义，只是为了退出循环，暂时先固定为 DEV_TYPE_CAM_SW，后续去掉该值，防止误导
                            //uDevVendor = 1;

                            LOG(INFO) << "strDriverInf input hardware regex:[" << ws2s(*it).c_str()
                                << "], get sys:[" << ws2s(szHardWareID).c_str()
                                << "], DevVendor:[" << i << "]";
                            break;
                        }
                    }
                    else
                    {
                        printf("not find\n");
                    }
                }
                else
                {
                    uDevVendor = 1;
                    LOG(INFO) << "input hardware regex:[" << ws2s(*it).c_str()
                        << "], get sys:[" << ws2s(szHardWareID).c_str()
                        << "], DevVendor:[" << i << "]";
                    break;
                }

            }
        }
        iIndex++;
    }
}

int dwGetCurDrvInfo2(LPGUID pClsGuid, LPCTSTR lpEnumerator, std::vector<wstring> psRegex, DevDrvInfo* pInfo, std::wstring strDriverName)
{
    int nRet = ERR_DEVICE_NO_FOUND, iIndex = 0, i = 1;
    DWORD dwProblem = 0, dwDevState = 0;
    ULARGE_INTEGER DrvDate_Cur = { 0 };
    ULARGE_INTEGER DrvDate_New = { 0 };
    TCHAR szHardWareID[512] = { 0 };
    SP_DEVINFO_DATA DeviceInfoData;
    SP_DRVINFO_DATA DrvInfoData;
    int uDevVendor = DEV_DETECT_UNKNOWN;
    wstring wstrVer;
    string strVer;
    std::vector<wstring>::iterator it;
    bool IsDisableable = false, IsDisabled = false;

    if (psRegex.empty())
    {
        nRet = ERR_PARAM_ERROR;
        LOG(ERROR) << "hardid psRegex is empty";
        return 0;
    }

    HDEVINFO hDevInfo = SetupDiGetClassDevs(pClsGuid, lpEnumerator, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);

    if (hDevInfo == INVALID_HANDLE_VALUE)
    {
        LOG(ERROR) << "SetupDiGetClassDevs err, pClsGuid = " << (char*)pClsGuid;
        nRet = ERR_PARAM_ERROR;
        return 0;
    }

    while (1)
    {
        memset(szHardWareID, sizeof(szHardWareID), 0);
        DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

        if (!SetupDiEnumDeviceInfo(hDevInfo, iIndex, &DeviceInfoData))
        {
            LOG(ERROR) << "dwGetCurDrvInfo::SetupDiEnumDeviceInfo err GetLastError:[0x" << hex << GetLastError() << "]";
            break;
        }

        if (!SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_HARDWAREID,
            NULL, (PBYTE)szHardWareID, sizeof(szHardWareID) - 2, NULL))
        {
            iIndex++;
            continue;
        }

        iIndex++;
    }
}

std::wstring GetDevcieProperty(HDEVINFO Devs, PSP_DEVINFO_DATA DevInfo, DWORD Prop)
{
    std::wstring Buffer;

    DWORD reqSize = 0;
    DWORD dataType = 0;;

    do
    {
        SetupDiGetDeviceRegistryProperty(Devs, DevInfo, Prop, &dataType, NULL, NULL, &reqSize);
        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
        {
            break;
        }

        Buffer.resize(reqSize);
        SetupDiGetDeviceRegistryProperty(Devs, DevInfo, Prop, &dataType, (LPBYTE)&Buffer.at(0), reqSize, &reqSize);

    } while (0);

    return Buffer;

}

BOOL GetDeviDriverInfo(wstring hwid, std::wstring& info)
{
    HDEVINFO devs = INVALID_HANDLE_VALUE;

    do
    {
        //获取某类设备集合
        devs = SetupDiGetClassDevsEx(NULL,
            NULL,
            NULL,
            DIGCF_ALLCLASSES | DIGCF_PRESENT,
            NULL,
            NULL,
            NULL);
        if (devs == INVALID_HANDLE_VALUE)
        {
            break;
        }


        SP_DEVINFO_LIST_DETAIL_DATA devInfoListDetail;
        devInfoListDetail.cbSize = sizeof(devInfoListDetail);
        if (!SetupDiGetDeviceInfoListDetail(devs, &devInfoListDetail))
        {
            break;
        }

        SP_DEVINFO_DATA devInfo;
        devInfo.cbSize = sizeof(devInfo);
        for (DWORD devIndex = 0; SetupDiEnumDeviceInfo(devs, devIndex, &devInfo); devIndex++)
        {
            //获取硬件ID
            std::wstring HardId = GetDevcieProperty(devs, &devInfo, SPDRP_HARDWAREID);
            if (HardId.empty())
            {
                continue;
            }
            //printf("%d %ws\n", devIndex, HardId.c_str());
            if (HardId.find(hwid) != std::wstring::npos)
            {
                printf("%d %ws\n", devIndex, HardId.c_str());
                printf("---------------\n\n\n");
                //break;
                SP_DEVINSTALL_PARAMS deviceInstallParams;
                {
                    HKEY hKey = SetupDiOpenDevRegKey(devs, &devInfo,
                        DICS_FLAG_GLOBAL,
                        0,
                        DIREG_DRV,
                        KEY_READ);
                    if (hKey == INVALID_HANDLE_VALUE)
                    {
                        RegCloseKey(hKey);
                        return FALSE;
                    }

                    TCHAR buff[512] = { 0 };
                    DWORD RegDataType;
                    DWORD RegDataLength = sizeof(buff); // bytes!!!
                    long regerr = RegQueryValueEx(hKey,
                        TEXT("InfPath"),
                        NULL,
                        &RegDataType,
                        (PBYTE)buff,
                        &RegDataLength
                    );
                    if ((regerr != ERROR_SUCCESS) || (RegDataType != REG_SZ))
                    {
                        RegCloseKey(hKey);
                        return FALSE;
                    }
                    printf("InfPath:%S\n", buff);
                    info = buff;

                    RegDataLength = sizeof(buff);
                    regerr = RegQueryValueEx(hKey,
                        TEXT("DriverDesc"),
                        NULL,
                        &RegDataType,
                        (PBYTE)buff,
                        &RegDataLength
                    );
                    if ((regerr != ERROR_SUCCESS) || (RegDataType != REG_SZ))
                    {
                        RegCloseKey(hKey);
                        return FALSE;
                    }
                    printf("DriverDesc:%S\n", buff);

                    RegDataLength = sizeof(buff);
                    regerr = RegQueryValueEx(hKey,
                        TEXT("DriverDate"),
                        NULL,
                        &RegDataType,
                        (PBYTE)buff,
                        &RegDataLength
                    );
                    if ((regerr != ERROR_SUCCESS) || (RegDataType != REG_SZ))
                    {
                        RegCloseKey(hKey);
                        return FALSE;
                    }
                    printf("DriverDate:%S\n", buff);

                    RegDataLength = sizeof(buff);
                    regerr = RegQueryValueEx(hKey,
                        TEXT("DriverVersion"),
                        NULL,
                        &RegDataType,
                        (PBYTE)buff,
                        &RegDataLength
                    );
                    if ((regerr != ERROR_SUCCESS) || (RegDataType != REG_SZ))
                    {
                        RegCloseKey(hKey);
                        return FALSE;
                    }
                    printf("DriverVersion:%S\n", buff);
                    RegCloseKey(hKey);
                }


                //ZeroMemory(&deviceInstallParams, sizeof(deviceInstallParams));
                //deviceInstallParams.cbSize = sizeof(SP_DEVINSTALL_PARAMS);
                //if (!SetupDiGetDeviceInstallParams(devs, &devInfo, &deviceInstallParams))
                //{
                //	break;
                //}
                //deviceInstallParams.FlagsEx |= DI_FLAGSEX_ALLOWEXCLUDEDDRVS;
                //if (!SetupDiSetDeviceInstallParams(devs, &devInfo, &deviceInstallParams))
                //{
                //	break;
                //}

                //if (SetupDiBuildDriverInfoList(devs, &devInfo, SPDIT_COMPATDRIVER))
                //{
                //	ULONG index = 0;
                //	SP_DRVINFO_DATA driverInfoData;
                //	ZeroMemory(&driverInfoData, sizeof(driverInfoData));
                //	driverInfoData.cbSize = sizeof(SP_DRVINFO_DATA);
                //	while (SetupDiEnumDriverInfo(devs, &devInfo, SPDIT_COMPATDRIVER, index, &driverInfoData))
                //	{
                //		SP_DRVINFO_DETAIL_DATA driverInfoDetail;
                //		driverInfoDetail.cbSize = sizeof(SP_DRVINFO_DETAIL_DATA);
                //		if (SetupDiGetDriverInfoDetail(devs, &devInfo, &driverInfoData, &driverInfoDetail, sizeof(SP_DRVINFO_DETAIL_DATA), NULL))
                //		{
                //			index = index;
                //		}
                //		printf("driverInfoData.ProviderName:%S\n", driverInfoData.ProviderName);
                //		printf("driverInfoData.MfgName:%S\n", driverInfoData.MfgName);
                //		printf("driverInfoDetail.InfFileName:%S\n", driverInfoDetail.InfFileName);

                //		SYSTEMTIME SystemTime;
                //		if (FileTimeToSystemTime(&driverInfoData.DriverDate, &SystemTime)) 
                //		{
                //			TCHAR Buffer[MAX_PATH];
                //			if (GetDateFormat(LOCALE_USER_DEFAULT,
                //				DATE_SHORTDATE,
                //				&SystemTime,
                //				NULL,
                //				Buffer,
                //				sizeof(Buffer) / sizeof(TCHAR)
                //			) != 0) 
                //			{
                //				printf("driverInfoData.DriverDate:%S\n", Buffer);
                //			}
                //		}
                //		ULARGE_INTEGER Version;
                //		Version.QuadPart = driverInfoData.DriverVersion;
                //		printf("Version:%d.%d.%d.%d\n",
                //			HIWORD(Version.HighPart),
                //			LOWORD(Version.HighPart),
                //			HIWORD(Version.LowPart),
                //			LOWORD(Version.LowPart)
                //		);
                //		DWORD e = GetLastError();
                //		e = e;
                //		index++;
                //	}
                //}


            }
        }

    } while (0);

    if (devs != INVALID_HANDLE_VALUE)
    {
        SetupDiDestroyDeviceInfoList(devs);
    }

    return TRUE;
}
#include <Devpkey.h>
int PrintDevicesInfo()
{
    // 得到所有设备 HDEVINFO    
    HDEVINFO hDevInfo;
    hDevInfo = SetupDiGetClassDevs(NULL, 0, 0, DIGCF_PRESENT | DIGCF_ALLCLASSES);
    if (hDevInfo == INVALID_HANDLE_VALUE)
    {
        wprintf(L"SetupDiGetClassDevs Err:%d", GetLastError());
        return -1;
    };

    // 循环列举   
    SP_DEVINFO_DATA DeviceInfoData;
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++)
    {
        wstring hardid;
        WCHAR   szHardID[MAX_PATH] = { 0 };
        WCHAR   szClassBuf[MAX_PATH] = { 0 };
        WCHAR   szDescBuf[MAX_PATH] = { 0 };
        WCHAR   locinfo[MAX_PATH] = { 0 };
        WCHAR   friendName[MAX_PATH] = { 0 };
        if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_HARDWAREID, NULL, (PBYTE)szHardID, MAX_PATH - 1, NULL))
        {
            //printf("hardid:%s\n", ws2s(szClassBuf).c_str());
            hardid = szHardID;
        }
        // 获取类名  
        if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_CLASS, NULL, (PBYTE)szClassBuf, MAX_PATH - 1, NULL))
        {
            //printf("Class:%s\n", ws2s(szClassBuf).c_str());
        }
        //获取设备描述信息
        if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)szDescBuf, MAX_PATH - 1, NULL))
        {
            //printf("nDesc:%s\n", ws2s(szDescBuf).c_str());
        }
        if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_LOCATION_INFORMATION, NULL, (PBYTE)locinfo, sizeof(locinfo), NULL))
        {
            //printf("locinfo:%s\n", ws2s(locinfo).c_str());
        }
        if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_FRIENDLYNAME, NULL, (PBYTE)friendName, sizeof(friendName), NULL))
        {
            //printf("friendName:%s\n", ws2s(friendName).c_str());
        }

        bool test = true;
        if (hardid.find(L"USB\\VID_351E&PID_00C9") != std::wstring::npos ||
            hardid.find(L"USB\\VID_1D6B&PID_0100") != std::wstring::npos ||
            test)
        {
            WCHAR bufferHardID[MAX_PATH] = { 0 };
            DEVPROPTYPE HardIDtype;
            ULONG HardIDLen = 0;
            CM_Get_DevNode_Property(DeviceInfoData.DevInst,
                &DEVPKEY_Device_HardwareIds,
                &HardIDtype, nullptr, &HardIDLen, 0);

            CONFIGRET cRet1 = CM_Get_DevNode_Property(DeviceInfoData.DevInst,
                &DEVPKEY_Device_HardwareIds,
                &HardIDtype, (PBYTE)bufferHardID, &HardIDLen, 0);

            printf("cRet:%d, code:%d, hardid:%s\n", cRet1, HardIDtype, ws2s(bufferHardID).c_str());
            ULONG code = 0;
            DEVPROPTYPE CODE = 0;
            ULONG Len = sizeof(DEVPKEY_Device_ProblemCode);
            CONFIGRET cRet = CM_Get_DevNode_Property(DeviceInfoData.DevInst,
                &DEVPKEY_Device_ProblemCode,
                &CODE, (PBYTE)&code, &Len, 0);
            
            printf("cRet:%d, code:%d, ProblemCode=%d\n", cRet, CODE, code);

            wchar_t DeviceDesc[MAX_PATH] = { 0 };
            DEVPROPTYPE CODE1 = 0;
            ULONG Len1 = sizeof(DEVPKEY_Device_DeviceDesc);
            CM_Get_DevNode_Property(DeviceInfoData.DevInst,
                &DEVPKEY_Device_DeviceDesc,
                &CODE1, (PBYTE)DeviceDesc, &Len1, 0);
            printf("code:%d, DeviceDesc=%s\n", CODE1, ws2s(DeviceDesc).c_str());

            printf("%d---------------------------------------\n", i);
        }
        
    }

    //  释放     
    SetupDiDestroyDeviceInfoList(hDevInfo);
    return 0;
}

#include <iomanip>
string UnicodeToAscii(const wstring& wstr)
{
    int ansiiLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    char* pAssii = (char*)malloc(sizeof(char) * ansiiLen);
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
    string ret_str = pAssii;
    free(pAssii);
    return ret_str;
}
int getalldevice(LPGUID pClsGuid, LPCTSTR lpEnumerator)
{
    int nRet = ERR_DEVICE_NO_FOUND, iIndex = 0, i = 1;
    DWORD dwProblem = 0, dwDevState = 0;
    ULARGE_INTEGER DrvDate_Cur = { 0 };
    ULARGE_INTEGER DrvDate_New = { 0 };
    TCHAR szHardWareID[512] = { 0 };
    SP_DEVINFO_DATA DeviceInfoData;
    SP_DRVINFO_DATA DrvInfoData;
    wstring wstrVer;
    string strVer;
    std::vector<wstring>::iterator it;
    bool IsDisableable = false, IsDisabled = false; 
    HDEVINFO hDevInfo = SetupDiGetClassDevs(pClsGuid, lpEnumerator, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);

    if (hDevInfo == INVALID_HANDLE_VALUE)
    {
        printf("SetupDiGetClassDevs err, pClsGuid =%s \n", (char*)pClsGuid);
        nRet = ERR_PARAM_ERROR;
        goto param_err;
    }

    while (1)
    {
        
        memset(szHardWareID, sizeof(szHardWareID), 0);
        DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

        if (!SetupDiEnumDeviceInfo(hDevInfo, iIndex, &DeviceInfoData))
        {
            std::cout << "dwGetCurDrvInfo::SetupDiEnumDeviceInfo err GetLastError:[0x" << hex << GetLastError() << "]" << std::endl;
            break;
        }

        if (!SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_HARDWAREID,
            NULL, (PBYTE)szHardWareID, sizeof(szHardWareID) - 2, NULL))
        {
            iIndex++;
            continue;
        }
        iIndex++;
        wstring wstrHardid = szHardWareID;
        printf("%s\n", UnicodeToAscii(wstrHardid).c_str());

        if (CM_Get_DevNode_Status(&dwDevState, &dwProblem, DeviceInfoData.DevInst, 0) != CR_SUCCESS || dwProblem != 0)
        {
            nRet = ERR_DEVICE_NEED_REPAIR;
            std::cout << "abnormal dwDevState:[0x" << setw(8) << hex << dwDevState
                << "], dwProblem:[0x" << setw(8) << dwProblem << "], nRet:" << nRet << std::endl;

            if (CM_PROB_DISABLED == dwProblem)
            {
                std::cout << "CM_PROB_DISABLED" << std::endl;
            }
            else
            {

                std::cout << "Need ReInstall, Error:" << GetLastError() << std::endl;
            }
        }
        else
        {
            std::cout << "normal dwDevState:[0x" << setw(8) << hex << dwDevState
                << "], dwProblem:[0x" << dwProblem << "], nRet:" << nRet << std::endl;
        }

        printf("----------------------------\n\n");
    }


    

param_err:
    return nRet;
}