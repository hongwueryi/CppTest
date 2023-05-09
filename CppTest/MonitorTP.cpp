#include <Windows.h>
#include <Setupapi.h>
#include <hidsdi.h.>
#include <string>
#include <map>
//#include <dbt.h>
#include <cfgmgr32.h>
#include "MonitorTP.h"
#include "commonUtil.h"

//std::mutex g_mux_monitor;
std::map<int, std::wstring> g_MonitorMap;

CMonitorTP* CMonitorTP::GetInstance()
{
    static CMonitorTP pMonTP;
    return &pMonTP;
}

template <typename T>
std::basic_string<T> str_replace(const std::basic_string<T>& str, const std::basic_string<T>& old_value, const std::basic_string<T>& new_value) {

    std::basic_string<T> str_backup = str;
    for (typename std::basic_string<T>::size_type pos(0); pos != std::basic_string<T>::npos; pos += new_value.length()) {
        if ((pos = str_backup.find(old_value, pos)) != std::basic_string<T>::npos) {
            str_backup.replace(pos, old_value.length(), new_value);
        }
        else {
            break;
        }
    }
    return str_backup;
}

std::wstring Replace(const std::wstring& str, const std::wstring& old_value, const std::wstring& new_value) {
    return str_replace(str, old_value, new_value);
}

bool CMonitorTP::GetAllTouchInfo(std::map<int, std::wstring>& TouchMap)
{
    bool bRet = false;
    //LOG(INFO) << "GetAllTouchInfo Enter...";
    GUID guid;
    HidD_GetHidGuid(&guid);
    HDEVINFO hDevInfo = SetupDiGetClassDevs(&guid, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
    if (hDevInfo == INVALID_HANDLE_VALUE)
    {
        //LOG(ERROR) << "GetTouchInfo AssociateTPwithMonitor  SetupDiGetClassDevs is Error";
        return bRet;
    }

    int index = 0;
    DWORD nSize = 0;
    SP_DEVINFO_DATA DeviceInfoData;
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    TCHAR szLocalPath[1024] = { 0 };
    TCHAR szInstancePath[1024] = { 0 };
    TCHAR szDeviceDes[1024] = { 0 };
    std::map<std::wstring, int > InstanceidLocalPathMap; //localpath 
    std::map<std::wstring, std::wstring > InstanceidPathMap; //instanceidpath

    while (SetupDiEnumDeviceInfo(hDevInfo, index, &DeviceInfoData))
    {
        if (!SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DEVICEDESC,
            NULL, (PBYTE)szDeviceDes, sizeof(szDeviceDes) - 2, NULL))
        {
            index++;
            continue;
        }
        SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_LOCATION_PATHS, NULL, (PBYTE)szLocalPath, sizeof(szLocalPath) - 2, NULL);
        std::wstring strLocalPath = szLocalPath;

        std::wstring strDeviceDes = szDeviceDes;
        if ((strDeviceDes.find(L"DTEN USB Touch Device") != std::wstring::npos ||
            strDeviceDes.find(L"DTEN VTouch") != std::wstring::npos) &&
            !strLocalPath.empty())
        {
            std::wstring strInstancePath = L"";
            DEVINST hDevInfo = DeviceInfoData.DevInst;
            while (true)
            {
                DEVINST hChildDevInfo;

                CONFIGRET cr = CM_Get_Child(&hChildDevInfo, hDevInfo, 0);
                if (cr != CR_SUCCESS)
                {
                    break;
                }

                ULONG ulSize = sizeof(szDeviceDes);
                cr = CM_Get_DevNode_Registry_Property(hChildDevInfo, CM_DRP_DEVICEDESC, NULL, szDeviceDes, &ulSize, 0);
                if (cr != CR_SUCCESS)
                {
                    break;
                }
                std::wstring strDes = szDeviceDes;
                //LOG(INFO) << "GetTouchInfo CM_Get_DevNode_Registry_Property  strDes:" << SysUtil::ws2s(strDes).c_str();
                if (strDes.find(L"HID-compliant touch screen") != std::wstring::npos)
                {
                    cr = CM_Get_Device_ID(hChildDevInfo, szInstancePath, MAX_PATH, 0);
                    if (cr != CR_SUCCESS)
                    {
                        break;
                    }
                    strInstancePath = szInstancePath;
                    if (!strInstancePath.empty())
                    {
                        std::wstring InstancePath = Replace(strInstancePath.c_str(), L"\\", L"#");
                        InstancePath += L"#{4d1e55b2-f16f-11cf-88cb-001111000030}";
                        strInstancePath = L"20-\\\\?\\";
                        strInstancePath += InstancePath;
                        //LOG(INFO) << "GetTouchInfo new strInstancePath:" << SysUtil::ws2s(strInstancePath).c_str();
                        break;
                    }
                }
                hDevInfo = hChildDevInfo;
            }
            //LOG(INFO) << "LocalPath=" << SysUtil::ws2s(strLocalPath).c_str();
            if (strLocalPath.find(L"#USB(6)#") != std::wstring::npos)
            {
                TouchMap.insert(make_pair(0, strInstancePath));
                //LOG(INFO) << "0 GetTouchInfo new strInstancePath:" << SysUtil::ws2s(strInstancePath).c_str();
            }
            else
            {
                TouchMap.insert(make_pair(1, strInstancePath));
                //LOG(INFO) << "1 GetTouchInfo new strInstancePath:" << SysUtil::ws2s(strInstancePath).c_str();
            }
        }
        index++;
    }

    SetupDiDestroyDeviceInfoList(hDevInfo);
    //LOG(INFO) << "GetAllTouchInfo End...";
    return true;
}

BOOL CALLBACK EnumMonitorProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
    //LOG(INFO) << "Monitorenumproc...";
    MONITORINFOEX infoEx;
    memset(&infoEx, 0, sizeof(infoEx));
    infoEx.cbSize = sizeof(infoEx);
    if (GetMonitorInfo(hMonitor, &infoEx))
    {
        std::wstring wstrDeviceID = L"";
        DISPLAY_DEVICE pDev;
        memset(&pDev, 0, sizeof(DISPLAY_DEVICE));
        pDev.cb = sizeof(DISPLAY_DEVICE);
        if (EnumDisplayDevices(infoEx.szDevice, 0, &pDev, EDD_GET_DEVICE_INTERFACE_NAME))
        {
            wstrDeviceID = pDev.DeviceID;
            //LOG(INFO) << "monitor info:" << (infoEx.dwFlags == MONITORINFOF_PRIMARY ? _T("Primary") : _T("Slave")) << ", DeviceID=" << SysUtil::ws2s(wstrDeviceID).c_str();
        }
        else
        {
            //LOG(INFO) << "EnumDisplayDevices failed=" << GetLastError();
        }

        if (!wstrDeviceID.empty())
        {
            if (infoEx.dwFlags == MONITORINFOF_PRIMARY)
            {
                g_MonitorMap[0] = wstrDeviceID;
            }
            else
            {
                g_MonitorMap[1] = wstrDeviceID;
            }
        }
        //LOG(INFO) << "OK";
    }
    else
    {
        //LOG(INFO) << "failed=" << GetLastError();
    }
    return TRUE;
}

#define REG_SYS_TOUC_MONITOR_CTRL				_T("SOFTWARE\\Microsoft\\Wisp\\Pen")
#define STR_DIGIMON							    _T("Digimon")
#define REG_SYS_TOUC_MONITOR_DIGI_CTRL			_T("SOFTWARE\\Microsoft\\Wisp\\Pen\\Digimon")

int CMonitorTP::SetDrvStatusByName(std::wstring strDesName, bool bSetAll)
{
    int nRet = 0;
    //LOG(INFO) << "SetDrvStatusByName Enter  strDesName:" << SysUtil::ws2s(strDesName);
    HDEVINFO hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
    if (hDevInfo == INVALID_HANDLE_VALUE)
    {
        //LOG(ERROR) << "SetDrvStatusByName is Error";
        return nRet;
    }
    int iIndex = 0;
    TCHAR szDevDes[512] = { 0 };
    SP_DEVINFO_DATA DeviceInfoData;
    memset(szDevDes, sizeof(szDevDes), 0);
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    while (SetupDiEnumDeviceInfo(hDevInfo, iIndex, &DeviceInfoData))
    {
        if (!SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DEVICEDESC,
            NULL, (PBYTE)szDevDes, sizeof(szDevDes) - 2, NULL))
        {
            iIndex++;
            continue;
        }
        std::wstring strDevDes = szDevDes;
        if (strDevDes.find(strDesName) != std::wstring::npos)
        {
            SP_PROPCHANGE_PARAMS PropChangeParams = { 0 };
            PropChangeParams.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
            PropChangeParams.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
            PropChangeParams.Scope = DICS_FLAG_GLOBAL;
            PropChangeParams.StateChange = DICS_DISABLE;
            DWORD dwProblem = 0, dwDevState = 0;
            SetupDiSetClassInstallParams(hDevInfo, &DeviceInfoData, &(PropChangeParams.ClassInstallHeader), sizeof(PropChangeParams));
            SetupDiChangeState(hDevInfo, &DeviceInfoData);
            if (bSetAll)
            {
                SP_PROPCHANGE_PARAMS PropChangeParams = { 0 };
                PropChangeParams.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
                PropChangeParams.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
                PropChangeParams.Scope = DICS_FLAG_GLOBAL;
                PropChangeParams.StateChange = DICS_ENABLE;
                DWORD dwProblem = 0, dwDevState = 0;
                SetupDiSetClassInstallParams(hDevInfo, &DeviceInfoData, &(PropChangeParams.ClassInstallHeader), sizeof(PropChangeParams));
                SetupDiChangeState(hDevInfo, &DeviceInfoData);
                //LOG(INFO) << "Reset SetDrvStatusByName ........";
            }
            else
            {
                //LOG(INFO) << "Disable SetDrvStatusByName ........";
                break;
            }
        }
        iIndex++;
    }
    SetupDiDestroyDeviceInfoList(hDevInfo);
    //LOG(INFO) << "SetDrvStatusByName End  .........";
    return nRet;
}

bool CMonitorTP::AssociateTPwithMonitor()
{
    bool bRet = false;
    std::map<int, std::wstring> TouchMap;
    GetAllTouchInfo(TouchMap);
    g_MonitorMap.clear();
    EnumDisplayMonitors(NULL, NULL, EnumMonitorProc, 0);
    
    if (2 != g_MonitorMap.size() || 2 != TouchMap.size())
    {
        return false;
    }

    for (int i = 0; i < 2; i++)
    {
        CREG::ModifyRegSZHKEY(REG_SYS_TOUC_MONITOR_CTRL, STR_DIGIMON,
            TouchMap[i].c_str(),
            g_MonitorMap[i].c_str(),
            g_MonitorMap[i].size() * 2);
    }
    
    SetDrvStatusByName(L"HID-compliant touch screen", true);
    
    //LOG(INFO) << "AssociateTPwithMonitor End.................................";
    return true;
}