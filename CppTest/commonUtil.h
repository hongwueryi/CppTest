#pragma once
#include <atlstr.h>
#include <string>
namespace CREG
{
    //��ȡע��������ת�ַ�������
    CAtlString ReadRegBinaryValue(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValue);
    //ע���8�ֽڶ�������������
    ULONGLONG ReadRegBinaryForSysTime(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValue);
}

namespace CUtils
{
    bool blCheckUdpPortListen(unsigned int nPort);
    BOOL ModifyFileExtension(std::wstring path, std::wstring srcType, std::wstring destType);
}