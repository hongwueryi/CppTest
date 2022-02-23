#pragma once
#define DEV_DETECT_UNKNOWN				0		//0, unknown
#define DEVICE_NORMAL					1		//设备正常
#define ERR_DEVICE_NO_FOUND				-1		//没有发现设备
#define ERR_DEVICE_NEED_REPAIR			-2		//设备需要修复
#define ERR_PARAM_ERROR					-9		//参数错误

#define MAX_DEVICE_DRIVER_VERSION_DESC	64

#define DEV_DETECT_TYPE_KNOWN			1<<0	//1, get dev type
#define DEV_DETECT_DRV_KNOWN			1<<1	//2
#define DEV_DETECT_DRV_DISABLE			1<<4    //16 dev disabled
#define DEV_DETECT_DRV_NEED_REINSTALL	1<<5	//32, drv need reinstall
typedef struct
{
    UINT uDrvClass;
    UINT uDevVendor;
    UINT uDrvDetectRet;
    ULARGE_INTEGER uDrvTimeStamp;
    TCHAR tDrvVerDesc[MAX_DEVICE_DRIVER_VERSION_DESC];
} DevDrvInfo;
int dwGetCurDrvInfo(LPGUID pClsGuid, LPCTSTR lpEnumerator, TCHAR* psRegex[], int nRegexNum, DevDrvInfo* pInfo);

int GetDrvStatusByName(std::wstring FriendlyName);