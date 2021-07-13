
#include <windows.h>
#include <tchar.h>
#include <thread>
#include "stdio.h"
#include "atisdk/adl_sdk.h"
#include "wmi.h"
#include <atlstr.h>
#define AMDVENDORID             (1002)
bool bNvidia = false;
int nATIVersion = -1;
int nAdapterId = -1;
int nAmdGraphicNum = 0;
HINSTANCE hATIDll = NULL;
typedef int(*ADL_MAIN_CONTROL_CREATE)(ADL_MAIN_MALLOC_CALLBACK, int);
typedef int(*ADL_MAIN_CONTROL_DESTROY)();
typedef int(*ADL_ADAPTER_NUMBEROFADAPTERS_GET) (int*);
typedef int(*ADL_ADAPTER_ADAPTERINFO_GET) (LPAdapterInfo, int);
typedef int(*ADL_ADAPTER_ACTIVE_GET) (int, int*);
typedef int(*ADL_OVERDRIVE_CAPS) (int iAdapterIndex, int *iSupported, int *iEnabled, int *iVersion);

typedef int(*ADL_OVERDRIVE5_TEMPERATURE_GET) (int iAdapterIndex, int iThermalControllerIndex, ADLTemperature *lpTemperature);
typedef int(*ADL_OVERDRIVE6_TEMPERATURE_GET)(int iAdapterIndex, int *lpTemperature);

// Memory allocation function
void* __stdcall ADL_Main_Memory_Alloc(int iSize)
{
	void* lpBuffer = malloc(iSize);
	return lpBuffer;
}

bool InitATIController()
{
	HINSTANCE hDLL;		// Handle to DLL

	ADL_MAIN_CONTROL_CREATE					ADL_Main_Control_Create;
	ADL_MAIN_CONTROL_DESTROY				ADL_Main_Control_Destroy;
	ADL_ADAPTER_NUMBEROFADAPTERS_GET		ADL_Adapter_NumberOfAdapters_Get;
	ADL_ADAPTER_ADAPTERINFO_GET				ADL_Adapter_AdapterInfo_Get;
	ADL_ADAPTER_ACTIVE_GET					ADL_Adapter_Active_Get;
	ADL_OVERDRIVE_CAPS						ADL_Overdrive_Caps;
	LPAdapterInfo						    lpAdapterInfo = NULL;
	int  i;
	int  ADL_Err = ADL_ERR;
	int  iOverdriveSupported = 0;
	int  iOverdriveEnabled = 0;

	int	 iOverdriveVersion = 0;

	printf("Amd graphic initialize!\n");
	hDLL = LoadLibrary(_T("atiadlxx.dll"));
	if (hDLL == NULL)
		// A 32 bit calling application on 64 bit OS will fail to LoadLIbrary.
		// Try to load the 32 bit library (atiadlxy.dll) instead
		printf("atiadlxx.dll not found!");
	hDLL = LoadLibrary(_T("atiadlxy.dll"));

	if (NULL == hDLL)
	{
		printf("atiadlxy.dll not found!\n");
		return 0;
	}
	hATIDll = hDLL;
	ADL_Main_Control_Create = (ADL_MAIN_CONTROL_CREATE)GetProcAddress(hDLL, "ADL_Main_Control_Create");
	ADL_Main_Control_Destroy = (ADL_MAIN_CONTROL_DESTROY)GetProcAddress(hDLL, "ADL_Main_Control_Destroy");
	ADL_Adapter_NumberOfAdapters_Get = (ADL_ADAPTER_NUMBEROFADAPTERS_GET)GetProcAddress(hDLL, "ADL_Adapter_NumberOfAdapters_Get");
	ADL_Adapter_AdapterInfo_Get = (ADL_ADAPTER_ADAPTERINFO_GET)GetProcAddress(hDLL, "ADL_Adapter_AdapterInfo_Get");
	ADL_Adapter_Active_Get = (ADL_ADAPTER_ACTIVE_GET)GetProcAddress(hDLL, "ADL_Adapter_Active_Get");
	ADL_Overdrive_Caps = (ADL_OVERDRIVE_CAPS)GetProcAddress(hDLL, "ADL_Overdrive_Caps");

	if (NULL == ADL_Main_Control_Create ||
		NULL == ADL_Main_Control_Destroy ||
		NULL == ADL_Adapter_NumberOfAdapters_Get ||
		NULL == ADL_Adapter_AdapterInfo_Get ||
		NULL == ADL_Adapter_Active_Get ||
		NULL == ADL_Overdrive_Caps
		)
	{
		printf("ADL's API is missing!\n");
		return 0;
	}

	// Initialize ADL. The second parameter is 1, which means:
	// retrieve adapter information only for adapters that are physically present and enabled in the system
	printf("ADL_Main_Control_Create!\n");
	if (ADL_OK != (ADL_Err = ADL_Main_Control_Create(ADL_Main_Memory_Alloc, 1)))
	{
		printf("ADL Initialization Error,error = %d\n", ADL_Err);
		return 0;
	}
	printf("ADL_Main_Control_Create end!");

	// Obtain the number of adapters for the system
	if (ADL_OK != (ADL_Err = ADL_Adapter_NumberOfAdapters_Get(&nAmdGraphicNum)))
	{
		printf("Cannot get the number of adapters!,error = %d\n", ADL_Err);
		return 0;
	}

	printf("adapter number is %d\n", nAmdGraphicNum);
	if (0 < nAmdGraphicNum)
	{
		lpAdapterInfo = (LPAdapterInfo)malloc(sizeof(AdapterInfo) * nAmdGraphicNum);
		memset(lpAdapterInfo, '\0', sizeof(AdapterInfo) * nAmdGraphicNum);

		// Get the AdapterInfo structure for all adapters in the system
		ADL_Adapter_AdapterInfo_Get(lpAdapterInfo, sizeof(AdapterInfo) * nAmdGraphicNum);
	}

	// Looking for first present and active adapter in the system
	int adapterId = -1;
	for (i = 0; i < nAmdGraphicNum; i++)
	{
		int adapterActive = 0;
		AdapterInfo adapterInfo = lpAdapterInfo[i];
		ADL_Adapter_Active_Get(adapterInfo.iAdapterIndex, &adapterActive);
		if (/*adapterActive && */adapterInfo.iVendorID == AMDVENDORID)
		{
			adapterId = adapterInfo.iAdapterIndex;
			break;
		}
	}
	printf("adapterid=%d\n", adapterId);

	if (-1 == adapterId)
	{
		return false;
	}

	//Overdrive 5 APIs should be used if returned version indicates 5. Overdrive 6 APIs are used if 6 is returned.
	//Overdrive 5 is supported on legacy ASICs. Newer ASICs (CIK+) should report Overdrive 6
	int nRet = 0;
	if (ADL_OK != (nRet = ADL_Overdrive_Caps(adapterId, &iOverdriveSupported, &iOverdriveEnabled, &iOverdriveVersion)))
	{
		printf("Cannot get Overdrive capabilities,err is %d\n", nRet);
		//return 0;
	}

	if (!iOverdriveSupported)
	{
		printf("Overdrive is not supported,iOverdriveSupported=%d\n", iOverdriveSupported);
		//return 0;
	}
	printf("overdrive version is %d\n", iOverdriveVersion);
	nAdapterId = adapterId;
	if (iOverdriveVersion == 5)
		nATIVersion = 5;
	else  if (iOverdriveVersion == 6)
		nATIVersion = 6;
	else
		printf("Unsupported Overdrive version \n");
	return true;
}

int _IsGPUSupport()
{
	int GpuSupport = -1;
	WMI wmi;
	if (!wmi.Initialize())
		return false;

	if (!wmi.ConnectServer(_bstr_t(L"ROOT\\CIMV2")))
		return false;

	if (!wmi.ExecuteQuery(_bstr_t("select * from Win32_VideoController")))
		return false;

	while (wmi.GetEnumerate())
	{
		VARIANT val;
		BSTR Bstr;
		wmi.GetResult(L"Name", val);
		Bstr = val.bstrVal;
		wprintf(L"NAME=%s\n", Bstr);
		if (Bstr != NULL)
		{
			CString strName(Bstr);
			printf("GPU name is %s", strName);
			strName = strName.MakeLower();
			if (strName.Find(L"nvidia") >= 0)
			{
				GpuSupport = 1;
				bNvidia = TRUE;
				//NvAPI_Initialize();
				printf("nvidia\n");
				break;
			}
			else if (strName.Find(L"advanced micro") >= 0 || strName.Find(L"amd") >= 0) {
				printf("GPU brand is amd\n");
				if (InitATIController())
					GpuSupport = 2;
				//break;
			}
		}
		printf("while end...\n");
		::SysFreeString(Bstr);
		printf("SysFreeString end...\n");
	}
	printf("gpu support is %d\n", GpuSupport);
	return GpuSupport;
}


void amdinit()
{
	_IsGPUSupport();
}

typedef int(*ADL_OVERDRIVE6_TEMPERATURE_GET)(int iAdapterIndex, int *lpTemperature);

int GetAMDThermal()
{
	int nThermal;
	int nAdl_err = ADL_ERR;
	ADL_OVERDRIVE6_TEMPERATURE_GET ADL_Overdrive6_Temperature_Get;
	int temperature = 0;
	ADL_Overdrive6_Temperature_Get = (ADL_OVERDRIVE6_TEMPERATURE_GET)GetProcAddress(hATIDll, "ADL_Overdrive6_Temperature_Get");
	for (nAdapterId = 0; nAdapterId < nAmdGraphicNum; nAdapterId++)
	{
		nAdl_err = ADL_Overdrive6_Temperature_Get(nAdapterId, &temperature);
		printf("ADL_Overdrive6_Temperature_Get adpterid is %d, error is %d\n", nAdapterId, nAdl_err);
		if (ADL_OK == nAdl_err)
		{
			nThermal = temperature / 1000; // The temperature is returned in millidegrees Celsius.
			printf("amd gpu version %d, gpu thermal %d\n", nATIVersion, nThermal);
			if (nThermal > 0)
			{
				break;
			}
		}
	}
	return nThermal;
}

int main1()
{
	_IsGPUSupport();
	GetAMDThermal();
	int i = 0;
	while (i++ < 10)
	{
		Sleep(4000);
		GetAMDThermal();
	}
	
	while (0)
	{
		Sleep(4000);
		std::thread tamd(amdinit);
		tamd.detach();
	}
	
	return 0;
}