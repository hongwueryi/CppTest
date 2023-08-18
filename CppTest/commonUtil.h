#pragma once
#include <atlstr.h>
#include <string>
#include <vector>
namespace CREG
{
    //��ȡע��������ת�ַ�������
    CAtlString ReadRegBinaryValue(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValue);
    //ע���8�ֽڶ�������������
    ULONGLONG ReadRegBinaryForSysTime(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValue);
    BOOL ModifyRegSZHKEY(LPCWSTR lpKeyPath, LPCWSTR lpSubKey, LPCWSTR lpSubKeyItem, LPCWSTR lpItemValue, UINT32 uLen);
    DWORD EnumSubKeys(HKEY keyDomain, CString szRegKeyPath, std::vector<CString>& subKeys, bool bWow64);
}

namespace CUtils
{
    std::string UnicodeToUtf8(const std::wstring& wstr);
    std::string UnicodeToAscii(const std::wstring& wstr);
    std::wstring Utf8ToUnicode(const std::string& str);
    std::wstring AsciiToUnicode(const std::string& str);
    bool blCheckUdpPortListen(unsigned int nPort);
    BOOL ModifyFileExtension(std::wstring path, std::wstring srcType, std::wstring destType);
    BOOL ParseDomain(LPCTSTR pszDomain);
    int HostNameToIP(std::wstring hostname);
}