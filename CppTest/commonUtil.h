#pragma once
#include <atlstr.h>
#include <string>
namespace CREG
{
    //读取注册表二进制转字符串数据
    CAtlString ReadRegBinaryValue(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValue);
    //注册表8字节二进制日期数据
    ULONGLONG ReadRegBinaryForSysTime(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValue);
    BOOL ModifyRegSZHKEY(LPCWSTR lpKeyPath, LPCWSTR lpSubKey, LPCWSTR lpSubKeyItem, LPCWSTR lpItemValue, UINT32 uLen);
}

namespace CUtils
{
    std::string UnicodeToUtf8(const std::wstring& wstr);
    std::string UnicodeToAscii(const std::wstring& wstr);
    std::wstring Utf8ToUnicode(const std::string& str);
    std::wstring AsciiToUnicode(const std::string& str);
    bool blCheckUdpPortListen(unsigned int nPort);
    BOOL ModifyFileExtension(std::wstring path, std::wstring srcType, std::wstring destType);
}