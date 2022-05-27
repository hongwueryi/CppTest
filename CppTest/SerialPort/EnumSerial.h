#pragma once
#ifndef __DTEN_DEVICE_ENUM_SERIALPORT_H__
#define __DTEN_DEVICE_ENUM_SERIALPORT_H__

//#include "comm_util\commondef.h"
#define DEV_DESC_LEN 512

// Struct used when enumerating the available serial ports
// Holds information about an individual serial port.

//struct SSerInfo {
//	SSerInfo() : bUsbDevice(FALSE) {}
//	wstring strDevPath;          // Device path for use with CreateFile()
//	wstring strPortName;         // Simple name (i.e. COM1)
//	wstring strFriendlyName;     // Full name to be displayed to a user
//	BOOL bUsbDevice;             // Provided through a USB connection?
//	wstring strPortDesc;         // friendly name without the COMx
//};
struct SSerInfo {
	SSerInfo() : bUsbDevice(FALSE) {}
	TCHAR stDevPath[DEV_DESC_LEN];          // Device path for use with CreateFile()
	TCHAR stPortName[DEV_DESC_LEN];         // Simple name (i.e. COM1)
	TCHAR stFriendlyName[DEV_DESC_LEN];     // Full name to be displayed to a user
	BOOL bUsbDevice;             // Provided through a USB connection?
	TCHAR stPortDesc[DEV_DESC_LEN];         // friendly name without the COMx
};

// Routine for enumerating the available serial ports. Throws a CString on
// failure, describing the error that occurred. If bIgnoreBusyPorts is TRUE,
// ports that can't be opened for read/write access are not included.
bool EnumSerialPorts(std::vector<SSerInfo> &vecSerInfo, BOOL bIgnoreBusyPorts = TRUE);

#endif // !__DTEN_DEVICE_ENUM_SERIALPORT_H__
