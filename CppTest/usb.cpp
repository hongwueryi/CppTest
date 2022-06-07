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
using namespace std;
DEFINE_GUID(GUID_CLASS_I82930_MIC, 0x877fc334, 0xf128, 0x47f4, 0x90, 0x50, 0x7c, 0x3e, 0x78, 0x25, 0x95, 0x2b);

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
                break;
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

    if (CM_Get_DevNode_Status(&dwDevState, &dwProblem, DeviceInfoData.DevInst, 0) != CR_SUCCESS || dwProblem != 0)
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
    LOG(INFO) << "SetDrvStatusByName Enter  strDesName:" << ws2s(FriendlyName);
    HDEVINFO hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
    if (hDevInfo == INVALID_HANDLE_VALUE)
    {
        LOG(ERROR) << "SetDrvStatusByName is Error";
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
        if (strDevDes.find(FriendlyName) != std::wstring::npos)
        {
            nRet = 1;

            break;
        }
        iIndex++;
    }
    SetupDiDestroyDeviceInfoList(hDevInfo);
    LOG(INFO) << "SetDrvStatusByName End, isfind speaker=" << nRet;
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
