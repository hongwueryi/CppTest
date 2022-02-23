#include <windows.h>
#include <SetupAPI.h>
#include <cfgmgr32.h>
#include <regex>
#include <iostream>
#include <tchar.h>
#include <string>
#include "usb.h"
#include <locale.h>
using namespace std;
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
    TCHAR* arrSpeakerHard[2] = { NULL, L"USB\\\\Vid_1d6b&Pid_0105&Rev_.{4}&MI_00" };
    wstring wstrHardid = L"USB\\Vid_1d6b&Pid_0105&Rev_0101&MI_00";
    wregex pattern(arrSpeakerHard[1]);
    wsmatch  matchResult;
    //wprintf(L"vidpid=%s\n", wstrHardid.c_str());
    if (regex_match(wstrHardid, matchResult, pattern))
    {
        int num = 0;
    }

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