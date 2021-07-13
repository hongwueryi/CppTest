//空win32控制台程序

#include <vector>
#include <atlstr.h>
#include <string>
#include <memory>
#include <psapi.h>
#include <map>
#include <unordered_map>
#include "virtualkey.h"
#include <thread>
#include <Windows.h>
#include "ExceptionReport.h"

CExceptionReport report;
using namespace std;
typedef struct APP_INFOS {
    CString DisplayName;
    CString FullPath;
    __int64 last_time_;
    __int64 last_system_time_;
    int CPU_Usage;
}App_Infos;

FILE* fp = nullptr;
// 时间转换
static __int64 file_time_2_utc(const FILETIME* ftime)
{
    LARGE_INTEGER li;

    li.LowPart = ftime->dwLowDateTime;
    li.HighPart = ftime->dwHighDateTime;
    return li.QuadPart;
}

// 获得CPU的核数
static int get_processor_number()
{
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    return (int)info.dwNumberOfProcessors;
}

// 获取进程CPU占用
int get_cpu_usage(int pid)
{
    //cpu数量
    static int processor_count_ = -1;
    //上一次的时间
    static __int64 last_time_ = 0;
    static __int64 last_system_time_ = 0;

    FILETIME now;
    FILETIME creation_time;
    FILETIME exit_time;
    FILETIME kernel_time;
    FILETIME user_time;
    __int64 system_time;
    __int64 time;
    __int64 system_time_delta;
    __int64 time_delta;

    int cpu = -1;

    if (processor_count_ == -1)
    {
        processor_count_ = get_processor_number();
    }

    GetSystemTimeAsFileTime(&now);

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    if (!GetProcessTimes(hProcess, &creation_time, &exit_time, &kernel_time, &user_time))
    {
        return -1;
    }
    system_time = (file_time_2_utc(&kernel_time) + file_time_2_utc(&user_time)) / processor_count_;
    time = file_time_2_utc(&now);

    if ((last_system_time_ == 0) || (last_time_ == 0))
    {
        last_system_time_ = system_time;
        last_time_ = time;
        return -1;
    }

    system_time_delta = system_time - last_system_time_;
    time_delta = time - last_time_;

    if (time_delta == 0)
        return -1;

    cpu = (int)((system_time_delta * 100 + time_delta / 2) / time_delta);
    last_system_time_ = system_time;
    last_time_ = time;
    return cpu;
}

int get_cpu_usage(int pid, __int64& last_time_, __int64& last_system_time_)
{
    //cpu数量
    static int processor_count_ = -1;
    //上一次的时间
    //static __int64 last_time_ = 0;
    //static __int64 last_system_time_ = 0;

    FILETIME now;
    FILETIME creation_time;
    FILETIME exit_time;
    FILETIME kernel_time;
    FILETIME user_time;
    __int64 system_time;
    __int64 time;
    __int64 system_time_delta;
    __int64 time_delta;

    int cpu = -1;

    if (processor_count_ == -1)
    {
        processor_count_ = get_processor_number();
    }

    GetSystemTimeAsFileTime(&now);

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    if (!GetProcessTimes(hProcess, &creation_time, &exit_time, &kernel_time, &user_time))
    {
        return -1;
    }
    system_time = (file_time_2_utc(&kernel_time) + file_time_2_utc(&user_time)) / processor_count_;
    time = file_time_2_utc(&now);

    if ((last_system_time_ == 0) || (last_time_ == 0))
    {
        last_system_time_ = system_time;
        last_time_ = time;
        return -1;
    }

    system_time_delta = system_time - last_system_time_;
    time_delta = time - last_time_;

    if (time_delta == 0)
        return -1;

    cpu = (int)((system_time_delta * 100 + time_delta / 2) / time_delta);
    last_system_time_ = system_time;
    last_time_ = time;
    return cpu;
}

#include <tlhelp32.h>
std::map<int, App_Infos> ProcessList;
int testCPUUsage()
{
	HANDLE hSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnap)
		return 0;

	PROCESSENTRY32 processEntry = { sizeof(PROCESSENTRY32) };
	BOOL toContinue = ::Process32First(hSnap, &processEntry);
	HANDLE hProcess = INVALID_HANDLE_VALUE;


	while (toContinue)
	{
		DWORD pid = processEntry.th32ProcessID;
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, 0, pid);
		if (hProcess == INVALID_HANDLE_VALUE)
		{
			continue;
		}

		__int64 last_time_ = 0;
		__int64 last_system_time_ = 0;
		TCHAR fullPath[MAX_PATH];
		DWORD len = MAX_PATH;
		get_cpu_usage(pid, last_time_, last_system_time_);
		App_Infos TempInfos;
		TempInfos.last_time_ = last_time_;
		TempInfos.last_system_time_ = last_system_time_;
		if (QueryFullProcessImageName(hProcess, 0, fullPath, &len))
		{
			TempInfos.FullPath = fullPath;
		}
		TempInfos.DisplayName = processEntry.szExeFile;
		ProcessList.insert(std::make_pair(pid, TempInfos));

		CloseHandle(hProcess);
		toContinue = ::Process32Next(hSnap, &processEntry);
	}
	CloseHandle(hSnap);

	Sleep(1000);

	std::map<int, App_Infos>::iterator it;
	for (it = ProcessList.begin(); it != ProcessList.end(); ++it)
	{
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, 0, it->first);
		if (hProcess == INVALID_HANDLE_VALUE)
		{
			continue;
		}

		int percent = get_cpu_usage(it->first, it->second.last_time_, it->second.last_system_time_);
		it->second.CPU_Usage = percent;
		if ((percent != -1) && (percent != 0))
		{
			wprintf(L"pid=%d,percent=%d,name=%s\n\n", it->first, percent, it->second.DisplayName.GetBuffer(0));
			//fwprintf(fp, L"pid=%d,percent=%d,name=%s\n\n", it->first, percent, it->second.DisplayName.GetBuffer(0));
			it->second.DisplayName.ReleaseBuffer();
		}
	}

	return 0;
}

#if 0
int test()
{
    DWORD arrayPid[1024] = { 0 };
    DWORD needed = 0;
    if (0 == EnumProcesses(arrayPid, sizeof(arrayPid), &needed))
    {
        return 0;
    }

    DWORD NumProcess = needed / sizeof(DWORD);
    HANDLE hProcess = INVALID_HANDLE_VALUE;
    CString strFullPath;

    for (DWORD i = 0; i < NumProcess; i++)
    {
        DWORD pid = arrayPid[i];
        hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, 0, pid);
        if (hProcess == INVALID_HANDLE_VALUE)
        {
            continue;
        }

        __int64 last_time_ = 0;
        __int64 last_system_time_ = 0;
        get_cpu_usage(pid, last_time_, last_system_time_);
        App_Infos TempInfos;
        TempInfos.last_time_ = last_time_;
        TempInfos.last_system_time_ = last_system_time_;
        ProcessList.insert(std::make_pair(pid, TempInfos));      
    }

    Sleep(1000);

    std::map<int, App_Infos>::iterator it;
    for (it = ProcessList.begin(); it != ProcessList.end(); ++it)
    {
        hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, 0, it->first);
        if (hProcess == INVALID_HANDLE_VALUE)
        {
            continue;
        }

        int percent = get_cpu_usage(it->first, it->second.last_time_, it->second.last_system_time_);
        it->second.CPU_Usage = percent;
        if ((percent != -1) && (percent != 0))
        {
            printf("pid=%d,percent=%d\n\n", it->first, percent);
            fprintf(fp, "pid=%d,percent=%d\n\n", it->first, percent);
        }
    }

    return 0;
}
#endif


#include <algorithm>
int removeDuplicates(vector<int>& nums) {
	//std::unique 去除重复元素，返回最后一个元素的iterator
	//std::distance  获取vector的长度
	return std::distance(nums.begin(), std::unique(nums.begin(), nums.end()));
}
void testleet()
{
	vector<int>vec{ 1,1,2,1,1 };
	int len = removeDuplicates(vec);  //len = 3  
	vector<int>vec2(vec.begin(), unique(vec.begin(), vec.end()));

	vector<int>vec3{ 1,2,3,4,5 };
	auto vi = vec3.begin();
	//std::advance(vi, 3);
	auto nx = std::next(vi, 3);
	
	return;
}

LRESULT CALLBACK hookproc1(int nCode, WPARAM wParam, LPARAM lParam)
{
    printf("hookproc");
//     if (((DWORD)lParam & 0x40000000) && (HC_ACTION == nCode)) //有键按下
//     {
//         if ((wParam == VK_SPACE) || (wParam == VK_RETURN)) {
//             MessageBox(NULL, L"有按键按下;", 0, MB_OK);
//         }
//     }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}


// 让指定的进程加载DLL
BOOL LoadDll(DWORD dwProcessId, LPSTR lpszDllName)
{
    HANDLE	hProcess = NULL;
    HANDLE	hThread = NULL;
    PSTR	pszDllFile = NULL;


    // 打开进程
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
    if (hProcess == NULL)
    {
        printf("打开进程 %d 失败!\n\n", dwProcessId);
        return FALSE;
    }
    printf("打开进程 %d 成功!\n\n", dwProcessId);

    // 分配远程空间
    int cch = 1 + strlen(lpszDllName);
    pszDllFile = (PSTR)VirtualAllocEx(hProcess,
        NULL,
        cch,
        MEM_COMMIT,
        PAGE_READWRITE);
    if (pszDllFile == NULL)
        return FALSE;
    printf("分配远程空间成功!\n\n");

    // 把DLL的名字变量地址写入到远程空间中
    if ((WriteProcessMemory(hProcess,
        (PVOID)pszDllFile,
        (PVOID)lpszDllName,
        cch,
        NULL)) == FALSE)
    {
        return FALSE;
    }
    printf("写远程内存成功!\n\n");

    // 获取远程进程地址空间中LoadLibrary函数的地址
    PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32"), "LoadLibraryA");
    //因为在同一个系统中，这这LoadLibraryA地址是一样的，这下面这种都可行
    //PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE)LoadLibraryA;
    if (pfnThreadRtn == NULL)
        return FALSE;
    printf("获取LoadLibrary函数地址成功!\n\n");

    // 创建远程线程
    hThread = CreateRemoteThread(hProcess,
        NULL,
        0,
        pfnThreadRtn,
        (PVOID)pszDllFile,
        0,
        NULL);
    if (hThread == NULL)
        return FALSE;
    printf("创建远程线程成功!\n\n");
    // 等待远程线程执行结束，并非必要
    //system("pause");
    WaitForSingleObject(hThread, INFINITE);

    VirtualFreeEx(hProcess, (PVOID)pszDllFile, 0, MEM_RELEASE);
    CloseHandle(hThread);
    CloseHandle(hProcess);

    return TRUE;
}

#include <mmeapi.h>
#pragma comment(lib, "Winmm.lib")
void GetAudioInfo()
{
	UINT m_uMxId = 0; //mixer的ID
	HMIXER m_hmx; 
#define MAX_VOL_VALUE 65535
	if (MMSYSERR_NOERROR != mixerOpen(&m_hmx, m_uMxId, NULL, 0, CALLBACK_WINDOW))
	{
		return;
	}
	if (MMSYSERR_NOERROR != mixerGetID((HMIXEROBJ)m_hmx, &m_uMxId, MIXER_OBJECTF_HMIXER))
	{
		return;
	}
}

#include <iphlpapi.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#pragma comment(lib, "IPHLPAPI.lib")
BOOL IsLocalAdapter(const char *pAdapterName)
{
	BOOL ret_value = FALSE;
	char szDataBuf[MAX_PATH + 1];
	DWORD dwDataLen = MAX_PATH;
	DWORD dwType = REG_SZ;
	HKEY hNetKey = NULL;
	HKEY hLocalNet = NULL;

	if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SYSTEM\\CurrentControlSet\\Control\\Network\\{4D36E972-E325-11CE-BFC1-08002BE10318}"), 0, KEY_READ, &hNetKey))
		return FALSE;
	sprintf_s(szDataBuf, "%s\\Connection", pAdapterName);
	if (ERROR_SUCCESS != RegOpenKeyExA(hNetKey, szDataBuf, 0, KEY_READ, &hLocalNet))
	{
		RegCloseKey(hNetKey);
		return FALSE;
	}
	dwDataLen = MAX_PATH;
	if (ERROR_SUCCESS != RegQueryValueExA(hLocalNet, "PnpInstanceID", 0, &dwType, (BYTE *)szDataBuf, &dwDataLen))
	{
		goto ret;
	}
	if (strncmp(szDataBuf, "PCI", strlen("PCI")) == 0 || strncmp(szDataBuf, "USB", strlen("USB")) == 0)
		ret_value = TRUE;

ret:
	RegCloseKey(hLocalNet);
	RegCloseKey(hNetKey);

	return ret_value != 0;
}
using namespace std;
CString GetMacAdd()
{
	std::wstringstream ss;
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;
	ULONG it = 0;
	ULONG outBufLen = 15000;
	PIP_ADAPTER_ADDRESSES pAddresses = NULL, cAddr = NULL;

	do {
		//@wangyh26: 分配内存空间
		pAddresses = (IP_ADAPTER_ADDRESSES *)malloc(outBufLen);
		if (pAddresses == NULL) {
			printf("Memory allocation failed for IP_ADAPTER_ADDRESSES struct\n");
			exit(1);
		}
		//@wangyh26: AF_INET 只返回IPV4相关的适配器
		//@wangyh26: GAA_FLAG_INCLUDE_PREFIX 返回一系列的IP地址前缀
		dwRetVal = ::GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, NULL, pAddresses, &outBufLen);
		if (dwRetVal == ERROR_BUFFER_OVERFLOW) {
			free(pAddresses);
			pAddresses = NULL;
		}
		else {
			break;
		}
		it++;
	} while ((dwRetVal == ERROR_BUFFER_OVERFLOW) && (it < 3));

	//寻找第一个无线网
	cAddr = pAddresses;
	if (cAddr != NULL)
	{
		do {
			if (IsLocalAdapter(cAddr->AdapterName))
			{
				if (cAddr->IfType == IF_TYPE_IEEE80211)
					//if (IP_ADAPTER_IPV4_ENABLED == (cAddr->Flags & IP_ADAPTER_IPV4_ENABLED))
					break;
			}
		} while ((cAddr = cAddr->Next) != NULL);
	}

	//若第一次寻找失败，则寻找寻找第一个以太网
	if (NULL == cAddr)
	{
		cAddr = pAddresses;
		do {
			if (IsLocalAdapter(cAddr->AdapterName))
			{
				if (cAddr->IfType == IF_TYPE_ETHERNET_CSMACD)
					//if (IP_ADAPTER_IPV4_ENABLED == (cAddr->Flags & IP_ADAPTER_IPV4_ENABLED))
					break;
			}
		} while ((cAddr = cAddr->Next) != NULL);
	}

	//@wangyh26: 获取物理地址，设置网络状态
	if (cAddr != NULL)
	{
		for (UINT i = 0; i < cAddr->PhysicalAddressLength; i++) {
			ss << std::hex << std::setw(2) << std::setfill(_T('0')) << (UINT)cAddr->PhysicalAddress[i];
		}

		std::wstring adapterDesc;
#ifdef UNICODE
		adapterDesc.assign(cAddr->Description);
#else
		std::wstring tmp(cAddr->Description);
		adapterDesc.assign(tmp.begin(), tmp.end());
#endif
		//@wangyh26: 设置网络状态
		//if (cAddr->IfType == IF_TYPE_ETHERNET_CSMACD)
		//	NetworkStatus::setNetworkStatus(Network::STATUS_NOTCONCERN);
		//else
		//	NetworkStatus::setNetworkStatus(Network::STATUS_WIFI);

		cAddr->FirstUnicastAddress->Address.lpSockaddr;

		//g_log.i(_T("System::getMacAddressNew adapter: name=%s, mac=%s, ifType=%d"), adapterDesc.c_str(), ss.str().c_str(), cAddr->IfType);
	}
	else
	{
		//g_log.e(_T("System::getMacAddressNew not found available adapter"));
	}

	free(pAddresses);
	return ss.str().c_str();
}

//通过usb协议和hid设备通讯
#include <windows.h>
#include <setupapi.h>   
#include <devguid.h>   
#pragma comment(lib, "setupapi")   

extern "C"
{
#include <hidsdi.h>
}
#pragma comment(lib, "Hid.lib")
void GetDeviceInfo()
{
#if 0
	//得到设备信息集   
	GUID deviceId;
	HidD_GetHidGuid(&deviceId);

	HDEVINFO handle;
	handle = SetupDiGetClassDevs(&deviceId, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT); //Get only HID devices
	int Count = 0; //Total number of devices found
	DWORD strSize = 0, requiredSize = 0;
	ULONG DeviceInterfaceDetailDataSize;
	PSP_DEVICE_INTERFACE_DETAIL_DATA DeviceInterfaceDetailData;
	BOOL result1 = FALSE;
	do
	{
		SP_DEVINFO_DATA DeviceInfoData;
		SP_DEVICE_INTERFACE_DATA  DeviceInterfaceData;
		DeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
		result1 = SetupDiEnumDeviceInterfaces(
			handle,
			NULL, // IN PSP_DEVINFO_DATA  DeviceInfoData,  OPTIONAL
			&deviceId,
			Count,
			&DeviceInterfaceData
		);
		//获得设备详细数据（初步）
		SetupDiGetDeviceInterfaceDetail(handle,
			&DeviceInterfaceData,
			NULL,
			0,
			&strSize,
			NULL);
		requiredSize = strSize;
		DeviceInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(requiredSize);
		DeviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
		DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

		//再次获得详细数据
		BOOL result2 = SetupDiGetDeviceInterfaceDetail(handle,
			&DeviceInterfaceData,
			DeviceInterfaceDetailData,
			strSize,
			&requiredSize,
			&DeviceInfoData);
		USES_CONVERSION;
		//获得设备路径（最重要的部分）
		CString temp = DeviceInterfaceDetailData->DevicePath;
		HANDLE hDevice = CreateFile(
			temp,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			(LPSECURITY_ATTRIBUTES)NULL,
			OPEN_EXISTING,
			FILE_FLAG_OVERLAPPED,
			NULL);

		BOOL bRet = FALSE;
		if (hDevice != INVALID_HANDLE_VALUE)
		{
			
			DWORD dwError = 0;
			HIDD_ATTRIBUTES hid_attr;
			bRet = HidD_GetAttributes(hDevice, &hid_attr);
			//if (hid_attr.VendorID == 0x17EF && hid_attr.ProductID == 0x608C)
			{
				PHIDP_PREPARSED_DATA PreParseData;
				bRet = HidD_GetPreparsedData(hDevice, &PreParseData);
				HIDP_CAPS capabilities;
				//get device capabilities
				HidP_GetCaps(PreParseData, &capabilities);

				unsigned long nWriteBytes;
				char RecieveDataBuffer[32] = { 0 };
				bRet = ReadFile(hDevice, RecieveDataBuffer, capabilities.OutputReportByteLength, &nWriteBytes, NULL);
				dwError = GetLastError();
				bRet = HidD_GetFeature(hDevice, RecieveDataBuffer, capabilities.FeatureReportByteLength);
				dwError = GetLastError();
				wchar_t strProduct[MAX_PATH] = { 0 };
				bRet= HidD_GetProductString(hDevice, strProduct, MAX_PATH);
				printf("ProductString=%s\n", W2A(strProduct));
				dwError = GetLastError();
			}
			
			printf("Open File ok\n");
		}
		else
		{
			printf("Open File error\n");
		}


		printf("path%d = %s, handle=%d\n", Count, W2A(temp.GetBuffer()), hDevice);

		TCHAR szBuffer[MAX_PATH] = { 0 };
		//   得到设备类描述   
		if (SetupDiGetClassDescription(
			&DeviceInfoData.ClassGuid,
			szBuffer,
			MAX_PATH,
			NULL))
		{
			CString temppath = szBuffer;
			printf("\n%03d   :   设备类描述ClassDescription   =   %s\n", Count, W2A(temppath.GetBuffer()));
		}

		//   得到设备实例的唯一标识ID(由注册表路径组成)   
		if (SetupDiGetDeviceInstanceId(
			handle,
			&DeviceInfoData,
			szBuffer,
			MAX_PATH,
			NULL))
		{
			CString temppath = szBuffer;
			printf("%03d   :   唯一标识InstanceId   =   %s\n", Count, W2A(temppath.GetBuffer()));
		}

		//   得到设备名称   
		if (SetupDiGetDeviceRegistryProperty(
			handle,
			&DeviceInfoData,
			SPDRP_DEVICEDESC,
			NULL,
			(PBYTE)szBuffer,
			MAX_PATH,
			NULL))
		{
			CString temppath = szBuffer;
			printf("%03d   :   设备名称DeviceDesc   =   %s\n", Count, W2A(temppath.GetBuffer()));
		}

		//   得到设备型号   
		if (SetupDiGetDeviceRegistryProperty(
			handle,
			&DeviceInfoData,
			SPDRP_FRIENDLYNAME,
			NULL,
			(PBYTE)szBuffer,
			MAX_PATH,
			NULL))
		{
			CString temppath = szBuffer;
			printf("%03d   :   FriendName   =   %s\n", Count, W2A(temppath.GetBuffer()));
		}

		//   得到设备在注册表中的子路径   
		if (SetupDiGetDeviceRegistryProperty(
			handle,
			&DeviceInfoData,
			SPDRP_DRIVER,
			NULL,
			(PBYTE)szBuffer,
			MAX_PATH,
			NULL))
		{
			
			CString temppath = szBuffer;
			printf("%03d   :   设备在注册表中的子路径Regedit   Path   =   %s\n", Count, W2A(temppath.GetBuffer()));
		}
		printf("-----------------------------------------------\n");

		Count++;
	} while (result1);

	getchar();

	return;
#endif



    HDEVINFO hDevInfo = SetupDiGetClassDevs(
		(LPGUID)&GUID_DEVCLASS_USB,  /* (LPGUID)&GUID_DEVCLASS_DISPLAY,*/
        NULL,
        0,
        DIGCF_PRESENT);

    if (hDevInfo == INVALID_HANDLE_VALUE)
    {
        printf("Error!  SetupDiGetClassDevs()   return   %d\n", GetLastError());
        SetupDiDestroyDeviceInfoList(hDevInfo);
        return;
    }

    TCHAR szBuf[MAX_PATH];
    SP_DEVINFO_DATA spDevInfoData = { sizeof(SP_DEVINFO_DATA) };
	USES_CONVERSION;
    //   开始列举设备   
    for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &spDevInfoData); i++)
    {
        //   得到设备类描述   
        if (SetupDiGetClassDescription(
            &spDevInfoData.ClassGuid,
            szBuf,
            MAX_PATH,
            NULL))
        {
			CString temppath = szBuf;
            printf("\n%03d   :   ClassDescription   =   %s\n", i, W2A(temppath.GetBuffer()));
        }

        //   得到设备实例的唯一标识ID(由注册表路径组成)   
        if (SetupDiGetDeviceInstanceId(
            hDevInfo,
            &spDevInfoData,
            szBuf,
            MAX_PATH,
            NULL))
        {
			CString temppath = szBuf;
            printf("%03d   :   InstanceId   =   %s\n", i, W2A(temppath.GetBuffer()));
        }

        //   得到设备名称   
        if (SetupDiGetDeviceRegistryProperty(
            hDevInfo,
            &spDevInfoData,
            SPDRP_DEVICEDESC,
            NULL,
            (PBYTE)szBuf,
            MAX_PATH,
            NULL))
        {
			CString temppath = szBuf;
            printf("%03d   :   DeviceDesc   =   %s\n", i, W2A(temppath.GetBuffer()));
        }

        //   得到设备型号   
        if (SetupDiGetDeviceRegistryProperty(
            hDevInfo,
            &spDevInfoData,
            SPDRP_FRIENDLYNAME,
            NULL,
            (PBYTE)szBuf,
            MAX_PATH,
            NULL))
        {
			CString temppath = szBuf;
            printf("%03d   :   FriendName   =   %s\n", i, W2A(temppath.GetBuffer()));
        }
		
        //   得到设备在注册表中的子路径   
        if (SetupDiGetDeviceRegistryProperty(
            hDevInfo,
            &spDevInfoData,
            SPDRP_DRIVER,
            NULL,
            (PBYTE)szBuf,
            MAX_PATH,
            NULL))
        {
			
			CString temppath = szBuf;
            printf("%03d   :   Regedit   Path   =   %s\n", i, W2A(temppath.GetBuffer()));
        }
#if 0
		SP_DEVICE_INTERFACE_DATA  DeviceInterfaceData;
		DeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
		BOOL result1 = SetupDiEnumDeviceInterfaces(
			hDevInfo,
			NULL, // IN PSP_DEVINFO_DATA  DeviceInfoData,  OPTIONAL
			&spDevInfoData.ClassGuid,
			i,
			&DeviceInterfaceData
		);
		if (!result1)
			continue;

		DWORD length;
		DWORD required;
		SP_DEVICE_INTERFACE_DATA devInfoData;
		PSP_DEVICE_INTERFACE_DETAIL_DATA detailData = NULL;
		BOOL result = SetupDiGetDeviceInterfaceDetail(
			hDevInfo,
			&devInfoData,
			NULL,
			0,
			&length,
			NULL);

		detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(length);
		if (!detailData)
		{
			//printf("Device information allacation failed!");
			continue ;
		}
		detailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
		result = SetupDiGetDeviceInterfaceDetail(
			hDevInfo,
			&devInfoData,
			detailData,
			length,
			&required,
			NULL);
		if (!result)
		{
			//printf("Device information reallocation failed!"); 
			//return ;
		}
		HANDLE hDevice = CreateFile(
			detailData->DevicePath,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			(LPSECURITY_ATTRIBUTES)NULL,
			OPEN_EXISTING,
			FILE_FLAG_OVERLAPPED,
			NULL);
	
		if (hDevice == INVALID_HANDLE_VALUE)
		{
			printf("error");
		}
#endif
    }

    //printf("\nCdrom   count   =   %d\n", i);
    getchar();

    return;
}


/*
GUID_DEVCLASS_FDC软盘控制器

GUID_DEVCLASS_DISPLAY显示卡

GUID_DEVCLASS_CDROM光驱

GUID_DEVCLASS_KEYBOARD键盘

GUID_DEVCLASS_COMPUTER计算机

GUID_DEVCLASS_SYSTEM系统

GUID_DEVCLASS_DISKDRIVE磁盘驱动器

GUID_DEVCLASS_MEDIA声音、视频和游戏控制器

GUID_DEVCLASS_MODEMMODEM

GUID_DEVCLASS_MOUSE鼠标和其他指针设备

GUID_DEVCLASS_NET网络设备器

GUID_DEVCLASS_USB通用串行总线控制器

GUID_DEVCLASS_FLOPPYDISK软盘驱动器

GUID_DEVCLASS_UNKNOWN未知设备

GUID_DEVCLASS_SCSIADAPTERSCSI 和 RAID 控制器

GUID_DEVCLASS_HDCIDE ATA/ATAPI 控制器

GUID_DEVCLASS_PORTS端口（COM 和 LPT）

GUID_DEVCLASS_MONITOR监视器


*/

typedef struct _BlurProfileData {
    unsigned int mode : 3;
    unsigned int ctrl : 1;
    unsigned int cap : 1;
    unsigned int reserved : 28;
}BlurProfileData;

void SendVirtualKey3()
{
	Sleep(3000);
	INPUT input[6];  
	//win+alt+R
	input[0].type = input[1].type = input[2].type =
		input[3].type = input[4].type = input[5].type = INPUT_KEYBOARD;
	input[0].ki.wVk = input[5].ki.wVk = VK_LWIN;
	input[1].ki.wVk = input[4].ki.wVk = VK_MENU;
	input[2].ki.wVk = input[3].ki.wVk = 'R';
	input[3].ki.dwFlags = input[4].ki.dwFlags = input[5].ki.dwFlags = KEYEVENTF_KEYUP;
	int ret = SendInput(6, input, sizeof(INPUT));
	
}
void SendVirtualKey1()
{
	INPUT input[6];
	memset(input, 0, sizeof(input));
	//win+alt+R   //VK_LWIN  VK_MENU
	input[0].type = input[1].type = input[2].type =
		input[3].type = input[4].type = input[5].type = INPUT_KEYBOARD;
	input[0].ki.wVk = input[5].ki.wVk = VK_SHIFT;
	input[1].ki.wVk = input[4].ki.wVk = VK_CONTROL;
	input[2].ki.wVk = input[3].ki.wVk = VK_F22;
	input[3].ki.dwFlags = input[4].ki.dwFlags = input[5].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(6, input, sizeof(INPUT));
	int er = SendInput(6, input, sizeof(INPUT));
	int num = GetLastError();
	Sleep(1000);
}
void SendVirtualKey2()
{
	INPUT input[4];
	memset(input, 0, sizeof(input));

#if 0
	input[0].type = input[1].type = input[2].type =
		input[3].type = input[4].type = input[5].type = INPUT_KEYBOARD;
	input[0].ki.wVk = input[5].ki.wVk = VK_CONTROL;
	input[1].ki.wVk = input[4].ki.wVk = VK_SHIFT;
	input[2].ki.wVk = input[3].ki.wVk = VK_F22;
	input[3].ki.dwFlags = input[4].ki.dwFlags = input[5].ki.dwFlags = KEYEVENTF_KEYUP;
#endif

#if 1
	//模拟win+D

	input[0].type = input[1].type = input[2].type = input[3].type = INPUT_KEYBOARD;  //设置键盘模式  
	input[0].ki.wVk = input[3].ki.wVk = VK_SHIFT;
	input[1].ki.wVk = input[2].ki.wVk = VK_F22;
	input[2].ki.dwFlags = input[3].ki.dwFlags = KEYEVENTF_KEYUP;
	UINT Ruint = SendInput(4, input, sizeof(INPUT));
	int num = GetLastError();
	int d = 0;
#endif
#if 0
	//win+alt+R
	input[0].type = input[1].type = input[2].type =
		input[3].type = input[4].type = input[5].type = INPUT_KEYBOARD;
	input[0].ki.wVk = input[5].ki.wVk = VK_LWIN;
	input[1].ki.wVk = input[4].ki.wVk = VK_MENU;
	input[2].ki.wVk = input[3].ki.wVk = 'R';
	input[3].ki.dwFlags = input[4].ki.dwFlags = input[5].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(6, input, sizeof(INPUT));
#endif
}

void recordscreen()
{
	INPUT input[3];
	memset(input, 0, sizeof(input));
	//win+alt+R
	input[0].type = input[1].type = input[2].type = INPUT_KEYBOARD;
	input[0].ki.wVk = VK_LWIN;
	input[1].ki.wVk = VK_MENU;
	input[2].ki.wVk = 'R';
	SendInput(3, input, sizeof(INPUT));
	Sleep(100);
	input[0].ki.dwFlags = input[1].ki.dwFlags = input[2].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(3, input, sizeof(INPUT));
}

void installtest()
{
	TCHAR dir[MAX_PATH];
	TCHAR *ptr;
	GetModuleFileName(NULL, dir, MAX_PATH);
	if ((ptr = _tcsrchr(dir, '\\')) != NULL)
	{
		*ptr = '\0';
	}

	CString MsiPath = dir;
	MsiPath += _T("\\Setup.msi");
	
	CString Msiexec = _T("msiexec.exe ");
	CString mode = _T("\" /quiet");
	CString cmdUninstall = _T("/uninstall \"");
	cmdUninstall += MsiPath;
	cmdUninstall += mode;
	wprintf(L"uninstall = %s\n", cmdUninstall);
	CString cmdInstall = _T("/i \"");
	cmdInstall += MsiPath;
	cmdInstall += mode;
	wprintf(L"install = %s\n", cmdInstall);

	if (!cmdUninstall.IsEmpty() && !cmdInstall.IsEmpty())
	{
		int ret = (int)ShellExecute(NULL, L"open", Msiexec, cmdUninstall, NULL, SW_HIDE);
		wprintf(L"uninstall intel driver ret = %d\n", ret);
		if (ret < 32)
		{
			wprintf(L"uninstall intel driver failed\n");
		}

		ret = (int)ShellExecute(NULL, L"open", Msiexec, cmdInstall, NULL, SW_HIDE);
		wprintf(L"install intel driver ret = %d\n", ret);
		if (ret < 32)
		{
			wprintf(L"install intel driver failed\n");
			return;
		}
	}

}

UINT WINAPI Thread_Proc(LPVOID param)
{
	while (true)
	{
		printf("thread 1...");
		Sleep(1000);
	}
	return 0;
}

CString ConvertIconToFile(CString strIcon)
{
	if (strIcon.IsEmpty())
	{
		return L"";
	}

	int nPos = strIcon.Find(L",");
	if (nPos > 0)
	{
		strIcon = strIcon.Left(nPos);
	}

	nPos = strIcon.Find(L"\"");
	if (nPos >= 0)
	{
		strIcon.Replace(L"\"", L"");
	}

	nPos = strIcon.Find(L".ico");
	if (nPos > 0)
	{

	}

	return "";
}

enum enumtest {
	enum_0 = 0,
	enum_1,
	enum_2 = 1,
};

__int64 GetFolderSize(const std::wstring& strDir)
{
	if (strDir.length() < 3)
	{
		return 0;
	}

	__int64 nSize = 0;
	std::wstring strRootPath = strDir + L"\\";
	std::wstring strRoot = strRootPath + L"*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(strRoot.c_str(), &fd);

	if (INVALID_HANDLE_VALUE == hFind)
		return nSize;

	while (FindNextFile(hFind, &fd))
	{
		if (wcscmp(fd.cFileName, L".") == 0 || wcscmp(fd.cFileName, L"..") == 0)
			continue;
		std::wstring strPath = strRootPath + fd.cFileName;
		printf("strPath=%s", strPath.c_str());
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			nSize += GetFolderSize(strPath);
		}
		else
		{
			HANDLE hFile = CreateFile(strPath.c_str(), GENERIC_READ,
				FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

			if (INVALID_HANDLE_VALUE == hFile)
				continue;
			LARGE_INTEGER size;

			if (::GetFileSizeEx(hFile, &size))
			{
				nSize += size.QuadPart;
			}

			CloseHandle(hFile);
		}
	}
	FindClose(hFind);
	return nSize;
}

UINT64 CalcSoftSize(CString displayIcon)
{
	UINT64 dwValue = 0;
	if (-1 != displayIcon.Find(L".exe"))
	{
		std::wstring file_name = L"";
		std::wstring tempPrameter = L"";

		
		file_name = displayIcon.GetBuffer();


		if (0 == file_name.find_first_of(L"\""))
		{
			tempPrameter = file_name.substr(1,
				file_name.find_last_of(L"\\")).c_str();
		}
		else
		{
			tempPrameter = file_name.substr(0,
				file_name.find_last_of(L"\\")).c_str();
		}

		if (0 != tempPrameter.length())
		{
			dwValue = GetFolderSize(tempPrameter) / 1024;
		}
	}

	UINT64 size = dwValue * 1024;
	return size;
}


void ConvertCString(CString& newstr, bool removeexe = false)
{
	if (newstr.IsEmpty())
		return;
	UINT nPos = newstr.Find(L"\"");
	if (nPos != -1)
	{
		newstr.Replace(L"\"", L"");
	}

	nPos = newstr.Find(L",");
	if (nPos != -1)
	{
		newstr = newstr.Left(nPos);
}

	if (removeexe)
	{
		nPos = newstr.Find(L".exe");
		if (nPos != -1)
		{
			newstr = newstr.Left(newstr.ReverseFind('\\') + 1);
			return;
		}
		nPos = newstr.Find(L".dll");
		if (nPos != -1)
		{
			newstr = newstr.Left(newstr.ReverseFind('\\') + 1);
			return;
		}
	}

	if (newstr.ReverseFind('\\') != newstr.GetLength())
	{
		newstr += L"\\";
	}
}


typedef struct stest {
	int num;
	std::string st;
}STET;

stest* sfun(int num, std::string str)
{
	static stest t;
	t.num = num;
	t.st = str;
	return &t;
}

UINT WINAPI threadproc(LPVOID param)
{
	
	char* str = (char*)param;
	printf("%s-%d\n", str, GetCurrentThreadId());
	Sleep(2000);
	printf("%s-%d\n", str, GetCurrentThreadId());
	return 0;
}
void threadtest(char* param)
{
	_beginthreadex(NULL, 0, threadproc, param, 0, nullptr);
}

int addr = 100;
int *paddr = &addr;

UINT WINAPI testaddrporc(LPVOID param)
{
	while (1)
	{

		int * testa = (int *)param;
		int b = *testa;
		int num = 0;
	}
}


/////////////////////////////////////设置为主显示器//////////////////////////////////////////
//只针对双显示器的，多个显示器需要优化代码
void GetMainDisplayer(BOOL SetMain = FALSE)
{
	USES_CONVERSION;
	int devId = 0;
	bool ret = false;
	bool isPrimary = false;
	DWORD PrimaryDisplayID = 0;
	//list all DisplayDevices (Monitors)
	CString Display1;
	DEVMODE DisplayMode1;
	CString Display2;
	DEVMODE DisplayMode2;
	do {
		DISPLAY_DEVICE displayDevice;
		ZeroMemory(&displayDevice, sizeof(DISPLAY_DEVICE));
		displayDevice.cb = sizeof(displayDevice);

		ret = EnumDisplayDevices(NULL, devId, &displayDevice, 0);
		if (ret == true)
		{
			if ((displayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) == DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)
			{
			
				isPrimary = ((displayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) == DISPLAY_DEVICE_PRIMARY_DEVICE);
				printf("isPrimary=%d\n", isPrimary ? 1 : 0);
				printf("StateFlags=%d\n", displayDevice.StateFlags);
				printf("DeviceName=%s\n DeviceString=%s\n", W2A(displayDevice.DeviceName), W2A(displayDevice.DeviceString));
				printf("DeviceID=%s\n DeviceKey=%s\n", W2A(displayDevice.DeviceID), W2A(displayDevice.DeviceKey));
				if (SetMain)
				{
					printf("开始设置...\n");
					if (isPrimary)
					{
						PrimaryDisplayID = devId;
						DEVMODE deviceMode;
						deviceMode.dmSize = sizeof(DEVMODE);
						deviceMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_POSITION | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS; // | DM_DISPLAYORIENTATION;

						BOOL bRet = EnumDisplaySettings(displayDevice.DeviceName, (int)ENUM_REGISTRY_SETTINGS, &deviceMode);
						if (bRet)
						{
							Display1 = displayDevice.DeviceName;
							DisplayMode1 = deviceMode;
							//int ret = ChangeDisplaySettingsEx(displayDevice.DeviceName, &deviceMode, NULL, CDS_UPDATEREGISTRY | CDS_NORESET, NULL);
							//printf("ret=%d\n", ret);
						}
						
					}
					else
					{
						DEVMODE deviceMode;
						deviceMode.dmSize = sizeof(DEVMODE);
						deviceMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_POSITION | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS; // | DM_DISPLAYORIENTATION;

						BOOL bRet = EnumDisplaySettings(displayDevice.DeviceName, (int)ENUM_REGISTRY_SETTINGS, &deviceMode);
						if (bRet)
						{
							Display2 = displayDevice.DeviceName;
							DisplayMode2 = deviceMode;
							//int ret = ChangeDisplaySettingsEx(displayDevice.DeviceName, &deviceMode, NULL, CDS_SET_PRIMARY | CDS_UPDATEREGISTRY | CDS_NORESET, NULL);
							//printf("ret=%d\n", ret);
						}
					}
					//ChangeDisplaySettingsEx(NULL, NULL, NULL, 0, NULL);
				}
			}
		}
		devId++;
	} while (ret);

	if (SetMain)
	{
		DEVMODE deviceMode;
		deviceMode.dmSize = sizeof(DEVMODE);
		deviceMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_POSITION | DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS; // | DM_DISPLAYORIENTATION;
		int ret = ChangeDisplaySettingsEx(Display2, &DisplayMode1, NULL, CDS_SET_PRIMARY | CDS_UPDATEREGISTRY | CDS_NORESET, NULL);
		printf("ret=%d, name=%s\n", ret, W2A(Display2.GetBuffer()));
		ret = ChangeDisplaySettingsEx(Display1, &DisplayMode2, NULL, CDS_UPDATEREGISTRY | CDS_NORESET, NULL);
		printf("ret=%d, name=%s\n", ret, W2A(Display1.GetBuffer()));
		ChangeDisplaySettingsEx(NULL, NULL, NULL, 0, NULL);
		
	}
	printf("-----------------------------\n");
}

/*
EnumDisplayMonitors( ) 　该函数对当前用户系统中所包含的显示器进行枚举。应用程序就是通过与该函数交流得知,当前用户系统中所拥有的显示器个数以及其名称。
MonitorInfoex 和MonitorInfo 。在这两个结构中保存着相应显示器的相关信息,如坐标、是否为主显示器等。
GetMonitorInfo ( ) 　取得指定显示器的相关信息,如物理显示区大小等。
MonitorFromPoint ( ) 　取得指定点所在的显示器句柄。
MonitorFromRect ( ) 　取得指定矩形所在的显示器句柄。
MonitorFromWindow( ) 　取得指定窗口所在的显示器句柄
*/
//获取所有显示器坐标

BOOL CALLBACK Monitorenumproc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	static int iCount = 0;
	printf("monitor: { %ld, %ld, %ld, %ld }\n", lprcMonitor->left, lprcMonitor->top, lprcMonitor->right, lprcMonitor->bottom);
	MONITORINFOEX infoEx;
	memset(&infoEx, 0, sizeof(infoEx));
	infoEx.cbSize = sizeof(infoEx);
	if (GetMonitorInfo(hMonitor, &infoEx))
	{
		//RECT rcMonitor; //物理显示坐标
		//RECT rcWork; //工作显示坐标
		wprintf(L"[%p] [%s] [%s] rcMonitor(l=%d t=%d r=%d b=%d) rcWork(l=%d t=%d r=%d b=%d)\n",
			hMonitor,
			infoEx.szDevice,
			infoEx.dwFlags == MONITORINFOF_PRIMARY ? _T("Primary") : _T("Slave"),
			infoEx.rcMonitor.left, infoEx.rcMonitor.top, infoEx.rcMonitor.right, infoEx.rcMonitor.bottom,
			infoEx.rcWork.left, infoEx.rcWork.top, infoEx.rcWork.right, infoEx.rcWork.bottom);
	}
	if (iCount++ > 2)
		return FALSE;
	return TRUE;  //继续枚举
}


#include <iostream>
#include <fstream>
bool ReadCsvFile(LPCSTR filepath, void* content)
{
	ifstream iFile(filepath, ios::in);
	string linestr;
	while (getline(iFile, linestr))
	{

	}

	return true;
}

#include <regex>
#include <string>


class staiccls
{
public:
	staiccls()
	{
		printf("constructure.\n");
	}
	~staiccls() {}

	void run()
	{
		printf("run...\n");
	}
};
///////////////////////////////////////////////////////////////////////////////////////////
staiccls* staictest()
{
	static staiccls cls;
	return &cls;
}

tm* GetCurrentDatetimeTM()
{
	struct tm timeinfo = { 0 };
	time_t currentTime = time(0);
	//tm* currentTimeTM = localtime(&currentTime);
	int erno = localtime_s(&timeinfo, &currentTime);
	return &timeinfo;
}

//获取音量（貌似有问题）
int GetMixerValue()
{
	HMIXER m_hmx;
	unsigned long err;
	CString str;
	err = mixerOpen(&m_hmx, 0, 0, 0, 0);
	if (err)
	{
		printf("ERROR:Can’t open Mixer Device!");
		return 0;
	}

	unsigned long iNumDevs, i;
	// 获取系统中混音器设备个数  
	iNumDevs = mixerGetNumDevs();
	MIXERCAPS mixcaps;
	// 遍历所有的混音器并显示它们的ID和名称  
	for (i = 0; i < iNumDevs; i++)
	{
		// 获取下一个混音器设备的信息  
		if (!mixerGetDevCaps(i, &mixcaps, sizeof(MIXERCAPS)))
		{
			// 显示ID和名称  
			wprintf(L"Device ID #%u: %s\n", i, mixcaps.szPname);
		}
	}

	MIXERCONTROLDETAILS_SIGNED volStruct;

	//初始化MIXERLINE结构体  
	MIXERLINE mxl;
	ZeroMemory(&mxl, sizeof(mxl));
	mxl.cbStruct = sizeof(mxl);
	// 指出需要获取的通道，扬声器用MIXERLINE_COMPONENTTYPE_DST_SPEAKERS  
	mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
	if (mixerGetLineInfo((HMIXEROBJ)m_hmx, &mxl,
		MIXER_GETLINEINFOF_COMPONENTTYPE))
	{
		printf("Couldn’t get the mixer line!");
		return 0;
	}
	// 取得控制器.  
	MIXERLINECONTROLS mxlc;
	MIXERCONTROL mxc;
	ZeroMemory(&mxlc, sizeof(mxlc));
	mxlc.cbStruct = sizeof(mxlc);
	mxlc.dwLineID = mxl.dwLineID;
	mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
	mxlc.cControls = 1;
	mxlc.cbmxctrl = sizeof(mxc);
	mxlc.pamxctrl = &mxc;
	ZeroMemory(&mxc, sizeof(mxc));
	mxc.cbStruct = sizeof(mxc);
	if (mixerGetLineControls((HMIXEROBJ)m_hmx, &mxlc,
		MIXER_GETLINECONTROLSF_ONEBYTYPE))
	{
		printf("取得控制器失败!");
		return 0;
	}
	// 获取控制器中的值的音量范围：mxc.Bounds.lMinimum到mxc.Bounds.lMaximum.  

	// 初始化MIXERCONTROLDETAILS结构体  
	MIXERCONTROLDETAILS mxcd;
	ZeroMemory(&mxcd, sizeof(mxcd));
	mxcd.cbStruct = sizeof(mxcd);
	mxcd.cbDetails = sizeof(volStruct);
	mxcd.dwControlID = mxc.dwControlID;
	mxcd.paDetails = &volStruct;
	mxcd.cChannels = 1;

	// 获得音量值  
	if (mixerGetControlDetails((HMIXEROBJ)m_hmx, &mxcd,
		MIXER_GETCONTROLDETAILSF_VALUE))
	{
		printf("无法获得音量");
		return 0;
	}
	
	printf("%d %d %d\n",mxc.Bounds.dwMinimum,mxc.Bounds.dwMaximum,volStruct.lValue);  
 
	unsigned long mixerID;
	err = mixerGetID((struct HMIXEROBJ__ *)m_hmx, (unsigned int *)&mixerID, MIXER_OBJECTF_HMIXER);
	if (err)
	{
		printf("ERROR: Can’t get Mixer Device ID!\n");
	}
	else
	{
		printf("Mixer Device ID = %d\n", mixerID);
	}
	return 0;
}

#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
void GetExtendedTcpTableEx()
{
	PMIB_TCPTABLE_OWNER_PID pTcpTable = NULL;
	DWORD dwSize = 0;
	if (GetExtendedTcpTable(pTcpTable, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0) == ERROR_INSUFFICIENT_BUFFER)
	{
		pTcpTable = (MIB_TCPTABLE_OWNER_PID*) new char[dwSize];
		if (GetExtendedTcpTable(pTcpTable, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0) != NO_ERROR)
		{
			delete[]pTcpTable;
			return;
		}

		int iNum = pTcpTable->dwNumEntries;
		for (int i = 0; i < iNum; i++)
		{
			char localbuf[20] = { 0 };
			char remotebuf[20] = { 0 };
			inet_ntop(AF_INET, &pTcpTable->table[i].dwLocalAddr, localbuf, 20);
			inet_ntop(AF_INET, &pTcpTable->table[i].dwRemoteAddr, remotebuf, 20);
			printf("本地地址：%s:%d  远程地址：%s:%d  状态：%d  进程ID:%d\n",
				localbuf,//inet_ntoa(*(in_addr*)& pTcpTable->table[i].dwLocalAddr), //本地IP 地址
				htons(pTcpTable->table[i].dwLocalPort), //本地端口
				remotebuf,//inet_ntoa(*(in_addr*)& pTcpTable->table[i].dwRemoteAddr), //远程IP地址
				htons(pTcpTable->table[i].dwRemotePort), //远程端口
				pTcpTable->table[i].dwState, //状态
				pTcpTable->table[i].dwOwningPid); //所属进程PID
		}
		delete[]pTcpTable;
		return;
	}	
}

#include <Pdh.h>
#include <PdhMsg.h>
#pragma comment(lib,"pdh.lib")
//cpu使用率测试 Performance Data Helper （PDH），性能数据助手
int GetCpuUsage()
{
	HQUERY query;
	PDH_STATUS status = PdhOpenQuery(NULL, NULL, &query);

	if (status != ERROR_SUCCESS)
		printf("Open Query Error\n");

	HCOUNTER counter;
	counter = (HCOUNTER *)GlobalAlloc(GPTR, sizeof(HCOUNTER));
	status = PdhAddCounter(query, L"\\Processor Information(_Total)\\% Processor Time", NULL, &counter);
	if (status != ERROR_SUCCESS)
		printf("Add Counter Error\n");

	PdhCollectQueryData(query);
	Sleep(1000);
	PdhCollectQueryData(query);

	PDH_FMT_COUNTERVALUE pdhValue;
	DWORD dwValue;
	status = PdhGetFormattedCounterValue(counter, PDH_FMT_DOUBLE, &dwValue, &pdhValue);
	if (status != ERROR_SUCCESS)
		printf("Get Value Error\n");

	printf("value=%.2f\n", pdhValue.doubleValue);
	printf("usage=%f\n", ceil(pdhValue.doubleValue));
	PdhCloseQuery(query);

	return 0;
}

float ConverIntToFloat(int iNum)
{
	union UnionType
	{
		float f;
		int i;
	};

	UnionType UType;
	UType.i = iNum;
	return UType.f;
}

union MyUnion
{
	float f;
	int i;
};

BOOL GetRegistryValue(HKEY hKey, CString szRegKeyPath, CString szRegKeyName, CString& szRegValue)
{
	DWORD mdwDataType;
	DWORD mdwSize;
	HKEY  mhCtrlNwKey;
	bool bStaus = FALSE;
	mdwDataType = REG_SZ;
	mdwSize = 1024 * sizeof(TCHAR);
	try
	{
		CString strMsg;
		TCHAR  *szValue = new TCHAR[1024];
		if (szValue)
		{
			memset(szValue, 0, 1024 * sizeof(TCHAR));

			if (RegOpenKeyEx(hKey, szRegKeyPath, 0, KEY_READ | KEY_QUERY_VALUE | KEY_WOW64_64KEY, &mhCtrlNwKey) == ERROR_SUCCESS)
			{
				if (RegQueryValueEx(mhCtrlNwKey, szRegKeyName, NULL, &mdwDataType, (LPBYTE)szValue, &mdwSize) == ERROR_SUCCESS)
				{
					szRegValue = szValue;
					bStaus = TRUE;
				}

				RegCloseKey(mhCtrlNwKey);
			}//end of if RegOpenKeyEx
			 //DWORD dwError = GetLastError();
			delete[] szValue;
		}
	}
	catch (std::bad_alloc)
	{

	}
	return bStaus;
}


BOOL SetRegistryValue(HKEY hKey, CString szRegKeyPath, CString szRegKeyName, double dwRegValue)
{
	DWORD mdwDataType;
	HKEY  mhCtrlNwKey;
	bool bStaus = FALSE;
	mdwDataType = REG_BINARY;

	DWORD dwOption = KEY_ALL_ACCESS;

	if (RegCreateKeyEx(hKey, szRegKeyPath, 0, NULL, REG_OPTION_NON_VOLATILE, dwOption, NULL, &mhCtrlNwKey, NULL) == ERROR_SUCCESS)
	{
		if (RegSetValueEx(mhCtrlNwKey, szRegKeyName, NULL, mdwDataType, (PUCHAR)&dwRegValue, sizeof(dwRegValue)) == ERROR_SUCCESS)
		{
			bStaus = TRUE;
			RegFlushKey(mhCtrlNwKey);
		}
		RegCloseKey(mhCtrlNwKey);
	}//end of if RegOpenKeyEx
	return bStaus;
}

BOOL GetRegistryValue(HKEY hKey, CString szRegKeyPath, CString szRegKeyName, double& dwRegValue)
{
	DWORD mdwDataType;
	DWORD mdwSize = sizeof(DWORD);
	HKEY  mhCtrlNwKey;
	bool bStaus = FALSE;
	mdwDataType = REG_BINARY;

	if (RegOpenKeyEx(hKey, szRegKeyPath, 0, KEY_READ | KEY_QUERY_VALUE | KEY_WOW64_64KEY, &mhCtrlNwKey) == ERROR_SUCCESS)
	{
		if (RegQueryValueEx(mhCtrlNwKey, szRegKeyName, NULL, &mdwDataType, (LPBYTE)&dwRegValue, &mdwSize) == ERROR_SUCCESS)
		{
			bStaus = TRUE;
		}

		RegCloseKey(mhCtrlNwKey);
	}//end of if RegOpenKeyEx
	return bStaus;
}
const int g_tt = 1024 * 1024;


#include <vector>
typedef struct structtest {
	int id;
	int name;
};

void ftest(int id, int name, std::vector<structtest>& data)
{
	structtest item;
	item.id = id;
	item.name = name;
	data.push_back(item);
}

HANDLE g_eve = nullptr;
UINT WINAPI ThreadEventProc(LPVOID parameters)
{
	printf("thread start...\n");
	WaitForSingleObject(g_eve, INFINITE);
	ResetEvent(g_eve); //如果手动置位不调用该接口，则一直处于触发状态
	printf("wait over...\n");
	return 0;
}

//自定义结构体

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	printf("exec...\n");
	if (hwnd)
	{
		char classname[MAX_PATH] = { 0 };
		GetClassNameA(hwnd, classname, MAX_PATH);
		CStringA strname = classname;

		char windowname[MAX_PATH] = { 0 };
		GetWindowTextA(hwnd, windowname, MAX_PATH);
		CStringA strname2 = windowname;
		printf("classname=%s, windowname=%s\n", strname, strname2);
	}
		printf("hwnd\n");
	return true;
}

bool GetScreenSaverSecurity(bool &enable)
{
	bool result = false;
	BOOL enable11 = FALSE;
	try
	{
		BOOL bActive = TRUE;
		BOOL ret = SystemParametersInfoW(SPI_GETSCREENSAVESECURE, NULL, &enable11, 0);
		if (ret)
		{
			enable = (enable11 == TRUE ? true : false);
			result = true;
		}
	}
	catch (...)
	{
		result = false;
	}
	return result;
}

bool SetScreenSaverSecurity(bool enable)
{
	bool result = false;
	BOOL enable11 = enable ? TRUE : FALSE;
	try
	{
		BOOL ret2 = SystemParametersInfoW(SPI_SETSCREENSAVESECURE, enable11, NULL, SPIF_SENDWININICHANGE | SPIF_UPDATEINIFILE);
		if (ret2)
			result = true;
	}
	catch (...)
	{
		;
	}
	return result;
}

#include<thread>
#define COUNT 5
#include<regex>

class emptycls {
	void mm(){
		printf("%d", sizeof(emptycls));
	}
};
#if 0
#include <atlfile.h>
#include <functional>
#define ENCRYPT_SIZE 512u
UINT64 GetFileSize(CString filePath)
{
	CAtlFile file;
	HRESULT ret = file.Create(filePath, FILE_READ_ATTRIBUTES, FILE_SHARE_READ, OPEN_EXISTING);

	if (!SUCCEEDED(ret))
		return 0;

	UINT64 size;
	if (file.GetSize(size) == S_OK)
		return size;
	else
		return 0;
}

bool EasyEncryptFile(const CString &file)
{
	UINT64 fileSize = GetFileSize(file);
	if (!fileSize)
		return false;

	bool result = true;
	UINT64 encrySize = (fileSize >= ENCRYPT_SIZE ? ENCRYPT_SIZE : fileSize);
	HANDLE hF = INVALID_HANDLE_VALUE;
	HANDLE hFM = NULL;
	byte *data = NULL;
	do
	{
		hF = CreateFileW(file.GetString(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hF == INVALID_HANDLE_VALUE)
			break;

		DWORD lowDword = (DWORD)(encrySize & 0xFFFFFFFF);
		DWORD higDword = (DWORD)(encrySize >> 32);
		hFM = CreateFileMappingW(hF, NULL, PAGE_READWRITE, higDword, lowDword, NULL);
		if (!hFM)
			break;

		data = (byte*)::MapViewOfFile(hFM, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, lowDword);
		if (!data)
			break;

		byte key = 'm';
		for (DWORD index = 0; index < lowDword; ++index)
		{
			data[index] ^= key;
		}
		FlushViewOfFile(data, lowDword);

		result = true;
	} while (false);
	if (data)
		::UnmapViewOfFile(data);
	if (hFM)
		CloseHandle(hFM);
	if (hF != INVALID_HANDLE_VALUE)
		CloseHandle(hF);

	return result;
}
typedef enum _OPERATION_SYSTEM
{
	OS_OTHERS = 0,
	OS_WIN7,
	OS_WIN10_EarlierVersion,//以前的版本
	OS_WIN10_RS1,//1607(14393)
	OS_WIN10_RS2,//1703(15063)
	OS_WIN10_RS3,//1709(16299)
	OS_WIN10_RS4,//1803(17134)
	OS_WIN10_RS5, //1809(17763)
	OS_WIN10_1903,//18362
	OS_WIN10_1909,//18363
	OS_WIN10_NEW
} OPERATION_SYSTEM;

bool GetOsType(int &osType)
{
	HMODULE ModuleHandle = NULL;
	std::Function RtlGetNtVersionNumbers = NULL;
	DWORD MajorVersion = 0;
	DWORD MinorVersion = 0;
	DWORD BuildNumber = 0;

	ModuleHandle = LoadLibrary(TEXT("ntdll.dll"));

	if (!ModuleHandle)
	{
		return false;
	}

	RtlGetNtVersionNumbers = (Function)GetProcAddress(ModuleHandle, "RtlGetNtVersionNumbers");

	FreeLibrary(ModuleHandle);

	if (!RtlGetNtVersionNumbers)
	{
		return false;
	}

	RtlGetNtVersionNumbers(&MajorVersion, &MinorVersion, &BuildNumber);
	BuildNumber = LOWORD(BuildNumber);

	if (MajorVersion == 10)//win10 build跟代号有对应关系
	{
		//OutputString(TEXT("Win10 build%u"), BuildNumber);
		if (BuildNumber <= 10586)
			osType = OS_WIN10_EarlierVersion;
		else if (BuildNumber <= 14393)
			osType = OS_WIN10_RS1;
		else if (BuildNumber <= 15063)
			osType = OS_WIN10_RS2;
		else if (BuildNumber <= 16299)
			osType = OS_WIN10_RS3;
		else if (BuildNumber <= 17134)
			osType = OS_WIN10_RS4;
		else if (BuildNumber <= 17763)
			osType = OS_WIN10_RS5;
		else if (BuildNumber <= 18362)
			osType = OS_WIN10_1903;
		else if (BuildNumber <= 18363)
			osType = OS_WIN10_1909;
		else
			osType = OS_WIN10_NEW;
		return TRUE;
	}
	else if ((MajorVersion == 6) && (MinorVersion == 1))
	{
		//OutputString(TEXT("Win7"));
		osType = OS_WIN7;
		return true;
	}
	else
	{
		//OutputString(TEXT("Others"));
		osType = OS_OTHERS;
		return false;
	}
}
#endif

HANDLE G_mux;
UINT WINAPI threadtest(LPVOID PARAM)
{
	G_mux = CreateMutex(NULL, FALSE, NULL);
	while (true)
	{
		Sleep(1000);
		WaitForSingleObject(G_mux, INFINITE);
		printf("get %d\n\n", 1);
		ReleaseMutex(G_mux);
	}

	//ReleaseMutex(G_mux);
	return 0;
}

UINT WINAPI threadtest2(LPVOID PARAM)
{
	while (true)
	{
		Sleep(1000);
		WaitForSingleObject(G_mux, INFINITE);
		printf("get2 %d\n", 1);
		ReleaseMutex(G_mux);
		//ReleaseMutex(G_mux);
	}
	
	return 0;
}

#include <powerbase.h>
#include <winerror.h>
#pragma comment(lib, "PowrProf.lib")

#include <mutex>
std::mutex g_mutex;
class singleton
{
public:
	static singleton*Getinstance()
	{
		g_mutex.lock();
		if (nullptr == sin)
		{
			sin = new singleton();
		}
		g_mutex.unlock();
		return sin;
	}
	void print()
	{
		printf("print\n");
	}
private:
	class MyClass
	{
	public:
		~MyClass()
		{
			printf("print1 MyClass destructor\n");
			if (nullptr != singleton::sin)
			{
				delete sin;
				singleton::sin = nullptr;
				printf("print MyClass destructor\n");
			}
		}
		MyClass()
		{
			printf("print MyClass constructor\n");
		}
	};

	static MyClass myc;
	static singleton* sin;
	singleton() {
		printf("print singleton constructor\n");
	}
};

singleton* singleton::sin = nullptr;

singleton::MyClass singleton::myc;

void singletonTest()
{
	singleton::Getinstance()->print();
	singleton::Getinstance()->print();
}

class parent
{
public:
	parent()
	{

	}
	/*virtual*/ ~parent()
	{
		print();
		printf("parent destructod\n");
	}

public:
	virtual void print()
	{
		printf("parent print\n");
	}
};

class child :public parent
{
public:
	child()
	{

	}
	~child()
	{
		print();
		printf("child destructod\n");
	}

	virtual void print()
	{
		printf("child print\n");
	}
private:

};

void MyClass2Test()
{
	parent*pa = new child();
	delete pa;
}

union MyUnion1
{
	int x;
	char arr[2];
};

typedef union NODE
{
	int i;
	char c;
}Node;

class Aa
{
public:
	Aa(int x) { y = x + 1; }
	~Aa() {}
	Aa(Aa&aother) { printf("&\n"); }
	Aa& operator=(Aa&aother) { printf("\n"); }
	void print() { printf("%d\n", y); }
private:
	int y;
};

/*考虑有重叠区的情况下必须分别处理*/
char *Mystrcpy(char *dst, const char *src)
{
	if (dst == NULL || src == NULL)
		return NULL;
	if (dst == src)
		return dst;

	int size = strlen(src) + 1;

	if (dst < src || src + size <= dst)
	{
		char* d = dst;
		const char* s = src;

		while (size--)
			*d++ = *s++;
	}
	else
	{
		char* d = dst + size - 1;
		const char* s = src + size - 1;

		while (size--)
			*d-- = *s--;
	}
	return dst;
}

std::mutex g_mutex2;
std::mutex g_mutex3;
void ThreadPoolTest()
{
	for (int i = 0; i < 3; i++)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::unique_lock<std::mutex>locker(g_mutex2);
		std::cout << "testFunc() [" << i << "] at thread [ " << std::this_thread::get_id() << "] output" << std::endl;
	}
}

void ThreadPoolTest2()
{
	for (int i = 3; i < 5; i++)
	{
		std::this_thread::sleep_for(std::chrono::seconds(3));
		std::unique_lock<std::mutex>locker(g_mutex3);
		std::cout << "testFunc2() [" << i << "] at thread [ " << std::this_thread::get_id() << "] output" << std::endl;
	}
}

#include "ThreadPool.h"
#include <Windows.h>
CRITICAL_SECTION g_cs_;
int counter = 0;
void doit(void* arg)
{
	int i, val;
	for (i = 0; i < 10; i++)
	{
		//递归锁：同一个线程在不解锁的情况下，可以多次获取锁定同一个递归锁，而且不会产生死锁；
		//互斥量和临界区（关键段）是递归锁
		EnterCriticalSection(&g_cs_);
		EnterCriticalSection(&g_cs_);
		val = counter;
		printf("thread %d : %d\n", int(arg), val + 1);
		counter = val + 1;
		LeaveCriticalSection(&g_cs_);
		LeaveCriticalSection(&g_cs_);
	}
}

int mainTT()
{
	//std::mem_fn(&std::thread::join);
#if 0
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
	_CrtMemState s1, s2, s3;

	void GetMemory(char *p, int num)
	{
		p = (char*)malloc(sizeof(char) * num);
	}
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtMemCheckpoint(&s1);
	char *str = NULL;
	GetMemory(str, 100);
	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s1, &s2))
		_CrtMemDumpStatistics(&s3);
	cout << "Memory leak test!" << endl;
	//_CrtDumpMemoryLeaks();
#endif		

#if 0
	InitializeCriticalSection(&g_cs_);
	HANDLE hThrea = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)doit, (void*)1, 0, NULL);
	HANDLE hTrehad2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)doit, (void*)2, 0, NULL);
	WaitForSingleObject(hThrea, INFINITE);
	WaitForSingleObject(hTrehad2, INFINITE);
	DeleteCriticalSection(&g_cs_);
#endif

#if 0
	vector<int>myv = {1,5,2,1,3,4};
	myv.erase(std::remove(myv.begin(), myv.end(), 1), myv.end()); //{5,2,3,4}
	int nnn = 0;
#endif
#if 0
	CThreadPool tpool(3);
	for (int i = 0; i < 5; i++)
	{
		tpool.AddTask(ThreadPoolTest);
		tpool.AddTask(ThreadPoolTest2);
	}
#endif
#if 0
	char pdes[5];
	char psrc[5] = "1234";
	strcpy_s(psrc + 1, 1, psrc);  //测试奔溃抓取dump文件
	Mystrcpy(psrc + 1, psrc);
	Mystrcpy(pdes, psrc+1);
	printf("%s\n", psrc);

	Aa aa = 0;
	Aa bb(aa);
	bb.print();  //1
	//大端模式：指数据的高字节保存在内存的低地址
	//小端模式：指数据的高字节保存在内存的高地址
	Node node;
	node.i = 0x12345678;
	if (0x78 == node.c)
	{
		printf("小端\n"); //输出小端
	}
	else
	{
		printf("大端\n");
	}

	MyUnion1 myU;
	myU.x = 0;
	myU.arr[0] = 1;
	myU.arr[1] = 2;
	printf("%x, %x,%x\n", &myU.x, &myU.arr[0], &myU.arr[1]);
	int myUx = myU.x;
	printf("%x\n", myUx);//0x0201
	printf("%f\n", 101.10011);
	MyClass2Test();
#endif

#if 0
 	singletonTest();
	SYSTEM_POWER_CAPABILITIES sys;
	NTSTATUS  lRet = CallNtPowerInformation(SystemPowerCapabilities, NULL, 0, &sys, sizeof(sys));
	int numllll = 0;
#endif
// 	if (lRet == STATUS_SUCCESS)
// 	{
// 		STATUS_BUFFER_TOO_SMALL
// 	}

#if 0
	BOOL fOK = FALSE;
	HANDLE hToken;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken)) //打开进程访问令牌  
	{
		//试图修改“调试”特权  
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
		fOK = (GetLastError() == ERROR_SUCCESS);
		CloseHandle(hToken);
	}

	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(pi));
	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	si.lpDesktop = _T("winsta0\\default");
	si.wShowWindow = SW_SHOWNORMAL;
	si.dwFlags = STARTF_USESHOWWINDOW;
	TCHAR AppName[] = TEXT("C:\Windows\\System32\\cmd.exe");
	TCHAR szCommandLine[] = TEXT("C:\\Program Files (x86)\\Lenovo\\PCManager\\3.0.60.10211\\LockScreenPlayer.exe {\"testUrl\":\"C:\\\\ProgramData\\\\Lenovo\\\\devicecenter\\\\LockScreen\\\\h5cache\\\\index.html\",\"test\":1,\"showLogo\":1,\"showLikeBtn\":1,\"showDislikeBtn\":1,\"showSetWallpaper\":1,\"clickTitle\":\"秋去东来小雪到 添衣保暖望安康！\", \"id\":100,\"h5zip\":\"E:\\\\锁屏相关\\\\h5_bg\\\\h5.zip\",\"bg\":\"C:\\\\ProgramData\\\\Lenovo\\\\devicecenter\\\\LockScreen\\\\h5cache\\\\assert\\\\bg.jpg\",\"h5md5\":\"D78CFEDC782A2BAD34F453689CA1F4F1\",\"clickX\":30,\"clickY\":40,\"clickUrl\":\"https://www.baidu.com\",\"clickReportUrl\":[\"http://www.baidu.com\"],\"clickDescription\":\"hover描述文字\",\"clickButton\":\"立即查看\",\"clickOpenWay\":\"2\",\"wallpaperId\":300}");
	CreateProcess(NULL, szCommandLine,
		 NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
	printf("%d", GetLastError());
	DWORD dwNUm = 0;
	DWORD dwNUm2 = --dwNUm;
#endif
#if 0
	
	//_beginthreadex(NULL, 0, threadtest, NULL, 0, NULL);

	HANDLE eve1 = CreateEvent(NULL, FALSE, FALSE, NULL);
	//SetEvent(eve1);
	//HANDLE eve2 = CreateEvent(NULL, FALSE, FALSE, NULL);
	 
	HANDLE arrh[2] = { eve1, G_mux };
	DWORD dwret = WaitForMultipleObjects(2, arrh, FALSE, 1*1000);
	if (dwret == WAIT_TIMEOUT)
	{
		printf("WAIT_TIMEOUT\n");
	}
	else if (dwret == WAIT_OBJECT_0)
	{
		printf("WAIT_OBJECT_0\n");
	}
	else if (dwret == WAIT_OBJECT_0 + 1)
	{
		printf("WAIT_OBJECT_0 +1 \n");
		//ReleaseMutex(G_mux);
	}

	//WaitForSingleObject(G_mux, INFINITE);
	printf("get mutext in main\n");
	_beginthreadex(NULL, 0, threadtest, NULL, 0, NULL);
	_beginthreadex(NULL, 0, threadtest2, NULL, 0, NULL);
	//WaitForSingleObject(G_mux, INFINITE);
#endif

// 	ShellExecute(NULL, L"open", L"C:\\Program Files (x86)\\Lenovo\\SLBrowser\\SLBrowser.exe",
// 		L"--url=http://www.baidu.com", NULL, SW_SHOWNORMAL);

#if 0
	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	si.lpDesktop = _T("winsta0\\default");
	si.wShowWindow = SW_SHOWNORMAL;
	si.dwFlags = STARTF_USESHOWWINDOW;
	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(pi));
	CString cmdline = L"C:\\Program Files (x86)\\Lenovo\\SLBrowser\\SLBrowser.exe --url=http://www.baidu.com";
	CreateProcess(NULL, cmdline.GetBuffer(),
		NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
#endif
#if 0
	bool bbRet = EasyEncryptFile(L"E:\\Mycode\\Demo\\CppTest\\Debug\\en1594265092177.jpg");

	printf("1 %d", sizeof(emptycls));
#endif
#if 0
	
	for (int i = 0; i < COUNT; i++)
	{
		//std::thread t1(threadtest, i);
		//t1.detach();
		//t1.join();
		_beginthreadex(NULL, 0, threadtest, NULL, 0, NULL);
		Sleep(3000);
	}

	system("pause");
	return 0;
#endif

#if 0
	while (1)
	{
		Sleep(1000);
		//EnumWindows(EnumWindowsProc, 0);
		HWND hWnd = FindWindowA("WIN32TestDpi", NULL);
		if (hWnd)
		{
			RECT rect = { 0,0,0,0 };
			GetWindowRect(hWnd, &rect);
			printf("%d,%d,%d,%d\n", rect.left, rect.top, rect.right, rect.bottom);
		}
		else
		{
			HWND hWnd = FindWindowA("{820A19EA-52FD-4574-A35C-404AB0576A11}_lockscreenv2", NULL);
			if (hWnd)
			{
				RECT rect = { 0,0,0,0 };
				GetWindowRect(hWnd, &rect);
				printf("%d,%d,%d,%d\n", rect.left, rect.top, rect.right, rect.bottom);
			}
			HWND hWnd2 = FindWindowA(NULL, "Chrome Legacy Window");
			if (hWnd2)
			{
				RECT rect = { 0,0,0,0 };
				GetWindowRect(hWnd2, &rect);
				printf("%d,%d,%d,%d\n", rect.left, rect.top, rect.right, rect.bottom);
			}
			
		}
		//break;
		
	}
	//EnumDisplayMonitors(GetWindowDC(NULL), NULL, Monitorenumproc, NULL);
#endif
#if 0
	bool enable = false;
	bool bRRet = GetScreenSaverSecurity(enable);
	bRRet = SetScreenSaverSecurity(!enable);
#endif
#if 0
	HANDLE h5MainThread = NULL;
	HANDLE h5PlayerMainThread_ = (HANDLE)_beginthreadex(NULL, 0, ThreadEventProc, NULL, 0, NULL);
	h5MainThread = h5PlayerMainThread_;
	//h5PlayerMainThread_ = NULL;
	if (h5MainThread)
	{
		CloseHandle(h5MainThread);
		h5MainThread = NULL;
	}
	int test = 0;
#endif
#if 0
	Sleep(3000);
	EnumWindows(EnumWindowsProc, 0);
#endif
#if 0
	LockWorkStation();
	while (1)
	{
		Sleep(1000);
		//HWND htop = GetForegroundWindow();
		HWND htop = GetTopWindow(NULL);
		if (!htop)
			continue;

		char className[MAX_PATH] = { 0 };
		memset(className, 0, MAX_PATH * 2);
		int ret1 = GetClassNameA(htop, className, MAX_PATH);

		char textName[MAX_PATH] = { 0 };
		memset(textName, 0, MAX_PATH * 2);
		int ret2 = GetWindowTextA(htop, textName, MAX_PATH);
		printf("window name=%s, class name=%s\n", textName, className);
		if (ret1 == 0 && ret2 == 0)
		{
			//OutputDebugStringW(L"all Name == 0");
			printf("1window name=%s, class name=%s\n", textName, className);
		}
	}
#endif
#if 0
	g_eve = CreateEvent(NULL, TRUE, FALSE, NULL);
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadEventProc, NULL, 0, NULL);
	Sleep(1000);
	printf("sleep over...\n");
	SetEvent(g_eve);
	WaitForSingleObject(hThread, INFINITE);
	printf("thread over...\n");
	WaitForSingleObject(g_eve, INFINITE);
	printf("EVENT over...\n");
#endif
#if 0
	std::vector<structtest> data1;
	ftest(1, 2, data1);
	ftest(2, 3, data1);
	ftest(3, 4, data1);
	ftest(5, 6, data1);
	ftest(7, 9, data1);
	int unum = 0;
#endif
#if 0
	//GetAudioInfo();
	GetDeviceInfo();
#endif
#if 0
	//SendVirtualKey1();
	SendVirtualKey3();
	//SendVirtualKey2();
#endif
#if 0
	float test = 0.01;
	BOOL bRet = FALSE;
	bRet = SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Lenovo\\PCManager\\OC", L"testbinary", 0.01);
	double test_d = 0;
	bRet = GetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Lenovo\\PCManager\\OC", L"testbinary", test_d);
	float test_f = test_d;
	printf("%f\n", test_f);
#endif
#if 0
	typedef struct game_gpu_oc_defaultinfo
	{
		UINT PStateID;
		UINT ClockID;
		UINT OCOrderid;
		UINT NOCOrderid;
		UINT Interval;
		int OCMaxOffset;
		int OCOffsetFreq;
		int OCMinOffset;
		int OCOffsetScale;
		int defaultvalue;
	}GAME_GPU_OC_DEFAULTINFO;

	HMODULE hMou = LoadLibrary(L"WrapPlugin.dll");
	if (NULL == hMou)
	{
		return 0;
	}

	typedef BOOL(*funGetDefaultGpuOCData)(std::vector<GAME_GPU_OC_DEFAULTINFO>& GpuOCDefaultData);
	funGetDefaultGpuOCData GetDefaultGpuOCData = (funGetDefaultGpuOCData)GetProcAddress(hMou, "GetDefaultGpuOCData");
	if (nullptr == GetDefaultGpuOCData)
	{
		printf("interface is null");
		system("pause");
		return 0;
	}
	std::vector<GAME_GPU_OC_DEFAULTINFO> GpuOCDefaultData;
	BOOL bRet = GetDefaultGpuOCData(GpuOCDefaultData);
	if (bRet)
	{
		printf("%d", GpuOCDefaultData.size());
	}
	//WinExec("cmd.exe E:\\hong\\U-Lenovo Media Player1.1.1.1.tkn", SW_SHOW);
	//ShellExecute(NULL, L"open", L"E:\\hong\\U-Lenovo Media Player1.1.1.1.tkn", NULL, NULL, SW_HIDE);
#endif
	
#if 0
	float f1 = ConverIntToFloat(1114636288);   //60.00
	float f2 = ConverIntToFloat(1065353216);   //1.00
	float f = ConverIntToFloat(1120403456);   //100.00
#endif
#if 0
	map<int, int> map_Test;
	map_Test.insert(std::pair<int, int>(5, 500));
	map_Test.insert(std::pair<int, int>(1, 100));
	map_Test.insert(std::pair<int, int>(0, 0));
	map_Test.insert(std::pair<int, int>(6, 600));

	map<int, int>::iterator itMap;
	for (itMap = map_Test.begin(); itMap != map_Test.end(); ++itMap)
	{
		printf("%d, %d\n", itMap->first, itMap->second);
	}

	unordered_map<string, int> unmap;
	unmap.insert(make_pair("5", 1));
	unmap.insert(std::pair<string, int>("ces", 2));
	unordered_map<string, int>::iterator itUnMap;
	for (itUnMap = unmap.begin(); itUnMap != unmap.end(); ++itUnMap)
	{
		string ss = itUnMap->first;
		printf("%s, %d\n", ss.c_str(), itUnMap->second);
	}

#endif
#if 0
	CString temp_Z3Color = "123";
	BOOL bRet = GetRegistryValue(HKEY_CURRENT_USER, L"Software\\Lenovo\\PcManager\\AccelBall", L"zone3Color", temp_Z3Color);
#endif
	int num = 0;
#if 0
	float ftest = ConverIntToFloat(1106247680);
	int itest = (int)ftest;
	printf("%d\n", itest);
#endif
#if 0
	MyUnion my;
	my.i = 1106352538;
	printf("my.f=%f\n", my.f);
	my.f = 30.2;
	printf("my.i=%d\n", my.i);
#endif

#if 0
	while (1)
	{
		std::thread t1(GetCpuUsage);
		t1.join();
		Sleep(1000);
	}


	CString tt = CString(to_wstring(-103).c_str());
	printf("tt=%s\n", tt);
#endif
	//GetExtendedTcpTableEx();
#if 0
	struct ABCD
	{
		int a;
		int b;
		int c;
		int d;
	};
	//CONTAINING_RECORD宏的作用就是根据结构体类型和结构体中成员变量地址和名称则可求出该变量所在结构体的指针
	ABCD Abcd = { 1, 2, 3,  };
	//假设我们知道ABCD结构体中b的地址和名称求整个b所在结构体ABCD的指针
	ABCD *pAbcd = CONTAINING_RECORD(&Abcd.b, ABCD, b);
	printf("求得ABCD中a:%d b:%d c:%d d:%d\n", pAbcd->a, pAbcd->b, pAbcd->c, pAbcd->d);
#endif
#if 0
	GetMixerValue();
#endif
#if 0
	tm* currentTimeTM = GetCurrentDatetimeTM();
	printf("123");
#endif
#if 0
	VARIANT var;
	var.vt = VT_UINT;
	var.uintVal = 3;

	VARIANT var2;
	BSTR bs = SysAllocString(L"bstr");
	V_VT(&var2) = VT_BSTR;
	V_BSTR(&var2) = bs;

	CString cs = var2.bstrVal;
	DWORD dw = var.uintVal;
	DWORD dw2 = var2.uintVal;
	wprintf(L"%d, %s\n", dw2, cs);
	SysFreeString(bs);
#endif
#if 0
	int index1 = 0x1 | 0x2 | 0x4;
	int someindex = (index1 & 0x4);
	printf("index1=%d, someindex=%d\n", index1, someindex);
#endif
#if 0
	PWSTR pszSlash;
	wchar_t szWinIoDriverPath[32768];
	if (!GetModuleFileName(GetModuleHandle(NULL), szWinIoDriverPath, sizeof(szWinIoDriverPath)))
		return false;

	pszSlash = wcsrchr(szWinIoDriverPath, '\\');   //strchr("123.456.7", '.') 返回第一次出现.的位置，即.456.7

	if (pszSlash)
		pszSlash[1] = 0;
	else
		return 0;

	wcscat_s(szWinIoDriverPath, L"winio64.sys");
#endif
#if 0
	staictest()->run();
	staictest()->run();
#endif
#if 0
	//十进制转二进制
	int iCount = 7;
	for (int i = 0; i <= 31; i++)
	{
		int iCount2 = ((iCount >> i) & 1);
		printf("%d\n", iCount2);
	}

#endif
#if 0
	DWORD dw = 7;
	if ((dw & 1) == 1)
	{
		printf("1\n");
	}
	if ((dw & 2) == 2)
	{
		printf("2\n");
	}
	if ((dw & 4) == 4)
	{
		printf("4\n");
	}
	if ((dw & 8) == 8)
	{
		printf("8\n");
	}

#endif
#if 0
	//获取DWORD的每一个字节的值
	//0x保留模式亮度索引
	DWORD dw = 0x040201;
	DWORD dw1 = dw >> 16;
	DWORD dw2 = (dw & 0xf00) >> 8;
	DWORD dw3 = dw & 0xf;
	printf("%d,%d,%d,%d\n", dw, dw1, dw2, dw3);

	DWORD dw5;
	dw5 = (dw1 << 16) | (dw2 << 8) | dw3;
	printf("%d，0x%x\n", dw5, dw5);
#endif
#if 0
	typedef union NODE
	{
		int i;
		char c;
	}Node;

	//大端模式：指数据的高字节保存在内存的低地址
	//小端模式：指数据的高字节保存在内存的高地址
	Node node;
	node.i = 0x12345678;
	if (0x78 == node.c)
	{
		printf("小端\n");
	}
	else
	{
		printf("大端\n");
	}
#endif
#if 0			
	string Source = "123;";
	std::regex reg("1");
	string Dest = "0";
	bool ismatch = std::regex_match(Source, reg);
	ismatch = std::regex_search(Source, reg);
	std::regex_replace(Source, reg, Dest);   //有问题，没太懂
	int te = 0;
#endif
#if 0
	GetMainDisplayer();
	//GetMainDisplayer(TRUE);
	//GetMainDisplayer();
#endif
#if 0
	_beginthreadex(NULL, 0, testaddrporc, paddr, 0, NULL);
	Sleep(5000);
	*paddr = 10;
	Sleep(5000);
#endif
#if 0
	typedef BOOL(WINAPI* FUNLEDSET)();
	typedef int (*FUNGETLUDPMAC)(LPTSTR, int);
	HMODULE HM = LoadLibrary(L"WrapPlugin.dll");
	if (HM == nullptr) return 0;

	FUNGETLUDPMAC GetLUDPMac = (FUNGETLUDPMAC)GetProcAddress(HM, "GetLUDPMacAddress");
	TCHAR Buffer[100] = { 0 };
	int ret = GetLUDPMac(Buffer, 20);
	FUNLEDSET Fun = (FUNLEDSET)GetProcAddress(HM, "IsGameSeting");

	if (Fun())
	{
		printf("游戏机\n");
	}

	
	typedef BOOL(WINAPI* FUNINIT)();
	FUNINIT Init = (FUNINIT)GetProcAddress(HM, "ShowPCMGame");
	if (NULL == Init) return 0;
	if (Init())
	{
		printf("显示游戏模式\n");
	}
#endif
#if 0 
	double db = 2.000000;
	UINT uid = db;
	printf("%d", uid);
	
	HWND hWnd = ::FindWindow(L"LenovoPcManagerMainFrame", L"联想电脑管家");
	if (NULL != hWnd)
	{
		printf("find it");
	}
#endif
#if 0
	SC_HANDLE scManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (nullptr == scManager)
	{
		return 0;
	}

	SC_HANDLE scHandle = CreateService(scManager, L"XTU3SERVICE", L"XTU3SERVICE",
		SERVICE_ALL_ACCESS,
		SERVICE_WIN32_OWN_PROCESS,
		SERVICE_AUTO_START,
		SERVICE_ERROR_NORMAL,
		L"C:\\Driver\\XtuService.exe",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL);
	if (nullptr == scHandle)
	{
		int er = GetLastError();
		printf("err=%d", er);
		return 0;
	}
	printf("ok");
#endif
#if 0
	std::string str = NULL;
	HMODULE hModule = LoadLibraryEx(L"E:\\trunk\\bin\\x86\\Debug\\plugins\\WSAppStorePlugin.dll", NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	if (NULL == hModule)
	{
		int num = GetLastError();
		printf("%d", num);
		system("pause");
		return 0;
	}

	typedef bool (WINAPI*ENABLEHOOK) ();
	ENABLEHOOK EnableHook = (ENABLEHOOK)GetProcAddress(hModule, "DownLoadSoftPolicy");
	if (NULL == EnableHook)
	{
		return 0;
	}
	EnableHook();
#endif
#if 0
	threadtest("test1");
	threadtest("test2");
#endif
#if 0
	__int64 size6 = GetFolderSize(L"E:\\AppStore");
	__int64 size64 =  GetFolderSize(L"C:\\Program Files\\WindowsApps\\DolbyLaboratories.DolbyAtmosforGaming_3.20201.255.0_x64__rz1tebttyb220");
	stest* sres = sfun(1, "stest");
	stest* sres2 = sfun(2, "dfdf");
	CString cstTest = L"C:\\Program Files (x86)\\Netease\\CloudMusic\\cloudmusic.exe";
	ConvertCString(cstTest, true);
	int test = 0;
	//UINT64 size = CalcSoftSize(L"D:\\Program Files\\Foxmail 7.2\\Foxmail.exe");
	//printf("%lld", size);
#endif
#if 0
	double test = 0;
	if (test == 0)
	{
		double db = 4.0;
		double db2 = db / 2;
		double db3 = db / 2.0;
		double db4 = 4 / 2.0;
	}
#endif
#if 0
	DWORD  dwFilter = REG_NOTIFY_CHANGE_NAME |
		REG_NOTIFY_CHANGE_ATTRIBUTES |
		REG_NOTIFY_CHANGE_LAST_SET |
		REG_NOTIFY_CHANGE_SECURITY;

	HKEY key;
	LONG lErrorCode = RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS | KEY_WOW64_64KEY, &key);
	if (lErrorCode != ERROR_SUCCESS)
	{
		return 0;
	}

	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (hEvent == NULL)
	{
		_tprintf(TEXT("Error in CreateEvent (%d).\n"), GetLastError());
		return 0;
	}


	// Watch the registry key for a change of value.
	lErrorCode = RegNotifyChangeKeyValue(key,
		TRUE,	 //是否监测注册表项子项
		dwFilter,
		hEvent,
		TRUE);  //如果为FALSE，只有监测到变化，函数才会返回
	if (lErrorCode != ERROR_SUCCESS)
	{
		printf("Error in RegNotifyChangeKeyValue (%d).\n", lErrorCode);
		return 0;
	}


	// Wait for an event to occur.
	printf("Waiting for a change in the specified key...\n");
	if (WaitForSingleObject(hEvent, INFINITE) == WAIT_FAILED)
	{
		printf("Error in WaitForSingleObject (%d).\n", GetLastError());
		return 0;
	}
	else
	{
		printf("\nChange has occurred.\n");
	}
#endif
#if 0
	CString UnableUninstallList = L"1";
	CString Seperator = L";";
	int Position = 0;
	CString Token;
	Token = UnableUninstallList.Tokenize(Seperator, Position);
	while (!Token.IsEmpty())
	{
		// Get next token.
		Token = UnableUninstallList.Tokenize(Seperator, Position);
	}
	int n = 0;
#endif
	//CString strIcon = L"\"C:\\Users\\lenovo\\AppData\\Local\\SogouExplorer\\SogouExplorer.ico\",-1";
	//ConvertIconToFile(strIcon);
	//ShellExecuteA(NULL, "open", "rundll32.exe", "USER32,LockWorkStation", "", SW_SHOW);

	//SendVirtualKey2();
	//installtest();
#if 0
	int type = 0;
	printf("输入1代表win+alt+R，输入2代表ctrl+shift+f22");
	scanf_s("%d", &type);
	switch (type)
	{
	case 1:
		SendVirtualKey2();
		break;
	case 2:
		SendVirtualKey2();
		break;
	default:
		break;
	}
#endif
#if 0
	//int ret = WinExec("msiexec.exe /i C:\\Setup.msi /lvx* C:\\log.txt", SW_SHOW);
	int ret =(int) ShellExecute(NULL, L"open", L"msiexec.exe", L"/i C:\\Setup.msi", NULL, SW_SHOW);
	printf("%d,%d", ret, GetLastError());
	Sleep(1000*60);
#endif
#if 0
    typedef int(*FUNLEDSET)(int*);
    HMODULE HM = LoadLibrary(L"RtsBgBlur.dll");
    if (HM == nullptr) return 0;
    FUNLEDSET GetBlur = (FUNLEDSET)GetProcAddress(HM, "GetBlurProfile");
    if (NULL == GetBlur) return 0;
    typedef int(*FUNINIT)(int key, int value);
    FUNINIT SetBlur = (FUNINIT)GetProcAddress(HM, "SetBlurProfile");

    int ret;
    BlurProfileData data = { 0 };
    int *pdata = (int*)&data;
    // Get BgBlugProfile
    ret = GetBlur(pdata);
    printf("ret=0x%08X, data=0x%08d\n", ret, *pdata);
    //1 1 0 1 0

    *pdata = 26;
    int capibility = (26 >> 4) & 0x01;
    int state = (*pdata >> 3) & 0x01;
    int mode = (*pdata) % 8;

    // Set BgBlurCtrl
    data.ctrl = 1;
    ret = SetBlur(0, *pdata);
    printf("ret=0x%08X\n", ret);

    // Set BgBlurMode
    data.mode = 2;
    ret = SetBlur(1, *pdata);
    printf("ret=0x%08X\n", ret);
#endif
#if 0
    typedef BOOL(WINAPI* FUNLEDSET)();
    HMODULE HM = LoadLibrary(L"WrapPlugin.dll");
    if (HM == nullptr) return 0;
    FUNLEDSET Fun = (FUNLEDSET)GetProcAddress(HM, "CLedSetDefault");

    typedef BOOL(WINAPI* FUNINIT)();
    FUNINIT Init = (FUNINIT)GetProcAddress(HM, "InitGameZone");
    if (NULL == Init) return 0;
    Init();

    if (NULL == Fun) return 0;
    Fun();
#endif

#if 0
	USES_CONVERSION;
	CString ludpmac = GetMacAdd();
	printf("ludpmac=%s", W2A(ludpmac.GetBuffer()));
#endif
#if 1
#endif

#if 0
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD, hookproc1, 0, GetCurrentThreadId());
    if (NULL == hook)
    {
        printf("error");
    }
    int num = GetLastError();
    Sleep(1000 * 10);
#endif
#if 0
    OnVirtualKeyTest();
    system("pause");
    return 0;
#endif

#if 0
//模拟获取所有进程的cpu使用率
    int i = 0;
    fopen_s(&fp, "C:\\cputest.txt", "w+");
    if (nullptr == fp)
    {
        return 0;
    }
    while (i++ < 100)
    {
        printf("\n\n第%d次---------\n", i);
        fprintf(fp, "\n\n第%d次---------\n", i);
        test();
        ProcessList.clear();
        Sleep(1000 * 1);       
    }
    fclose(fp);
#endif

#if 0
	LoadDll(8684, "hookdll.dll");
#endif
#if 0
	HMODULE hModule = LoadLibrary(L"hookdll.dll");
	if (NULL == hModule)
	{
		return 0;
	}

	typedef void (WINAPI*ENABLEHOOK) ();
	ENABLEHOOK EnableHook = (ENABLEHOOK)GetProcAddress(hModule, "EnableHook");
	if (NULL == EnableHook)
	{
		return 0;
	}
	EnableHook();
#endif

#if 0
		std::string strtest[] = { "a.txt", "b.exe", "abc.txt", ".txt" };
		std::regex vregex("[a-z]+\\.txt");

		for (auto filename : strtest)
		{
			if (std::regex_match(filename, vregex))
				printf("%s\n", filename.c_str());
		}

		system("pause");
		return 0;

		
#endif
#if 0 //获取文件大小
		char *filepath = "E:\\L80048.zip";
		//方法一    

		HANDLE handle = CreateFileA(filepath, FILE_READ_EA, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
		if (handle != INVALID_HANDLE_VALUE)
		{
			int size = GetFileSize(handle, NULL);
			CloseHandle(handle);
		}

		CAtlFile file;
		wchar_t *filepath2 = L"E:\\L80048.zip";
		HRESULT ret = file.Create(filepath2, FILE_READ_ATTRIBUTES, FILE_SHARE_READ, OPEN_EXISTING);

		if (!SUCCEEDED(ret))
			return 0;

		UINT64 size;
		bool bret = file.GetSize(size);
#endif
#if 1
		//testleet();
#endif
    system("pause");
    return 0;
}


