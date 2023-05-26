#include "commonUtil.h"
#include <iphlpapi.h>


namespace CREG 
{
    // 解析注册表二进制类型的数据，处理还原成注册表中显示的16进制字符串

// 数字处理，注册表二进制数据解析
    void NumToHexStrW(DWORD dwNum, CAtlStringW& str)
    {
        UINT Temp = 0;
        UINT index = 0;
        while (dwNum > 0)
        {
            Temp = dwNum % 16;
            if (Temp < 10) {
                str.AppendChar(Temp + _T('0'));
            }
            else {
                str.AppendChar(_T('A') + Temp - 10);
            }
            dwNum = dwNum >> 4;
            index++;
        }
        // 补全字符串
        for (UINT j = 0; j < 4 - index; j++)
        {
            str.AppendChar(L'0');
        }

        str.MakeReverse();
        CAtlStringW aa = str.Mid(2, 3);
        CAtlStringW bb = str.Left(2);

        str.Format(L"%ws %ws", aa, bb);
    }

    // 还原注册表二进制数据类型格式
    CAtlStringW RegBinaryStrProcessingW(LPCWSTR lpszData, DWORD dwLength)
    {
        CAtlStringW strData;
        for (ULONG i = 0; i < dwLength; i++)
        {
            CAtlStringW str;
            NumToHexStrW(lpszData[i], str);
            strData.AppendFormat(L"%ws ", str);
        }
        return strData;
    }
    
    CAtlString ReadRegBinaryValue(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValue)
    {
        CAtlString strBinaryValue;

        DWORD dwFlags = REG_BINARY;
        HKEY hKeyResult;
        BOOL ret = RegOpenKeyEx(hKey, lpSubKey, 0, KEY_READ, &hKeyResult);

        if (ERROR_SUCCESS == ret)
        {
            DWORD dwLength = 0;

            // 获得读取键值有多少个字符
            RegQueryValueEx(hKeyResult, lpValue, NULL, &dwFlags, NULL, &dwLength);

            // 申请一段空间，并初始化为空
            TCHAR* BinaryInfo = new TCHAR[dwLength + 1];
            memset(BinaryInfo, 0, sizeof(TCHAR) * (dwLength + 1));

            if (ERROR_SUCCESS == RegQueryValueEx(hKeyResult, lpValue, NULL, &dwFlags, (LPBYTE)BinaryInfo, &dwLength))
            {
                // 解析还原成字符串
                strBinaryValue = RegBinaryStrProcessingW(BinaryInfo, dwLength + 1);
            }
            delete[] BinaryInfo;
        }
        RegCloseKey(hKeyResult);
        return strBinaryValue;
    }

    ULONGLONG ReadRegBinaryForSysTime(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValue)
    {
        ULONGLONG stamp = 0;
        DWORD dwFlags = REG_BINARY;
        HKEY hKeyResult;
        BOOL ret = RegOpenKeyEx(hKey, lpSubKey, 0, KEY_READ, &hKeyResult);

        if (ERROR_SUCCESS == ret)
        {
            DWORD dwLength = 0;

            // 获得读取键值有多少个字符
            RegQueryValueEx(hKeyResult, lpValue, NULL, &dwFlags, NULL, &dwLength);

            // 申请一段空间，并初始化为空
            TCHAR* BinaryInfo = new TCHAR[dwLength + 1];
            memset(BinaryInfo, 0, sizeof(TCHAR) * (dwLength + 1));

            ULARGE_INTEGER uDrvTimeStamp;
            if (ERROR_SUCCESS == RegQueryValueEx(hKeyResult, lpValue, NULL, &dwFlags, (LPBYTE)&uDrvTimeStamp.QuadPart, &dwLength))
            {
                stamp = uDrvTimeStamp.QuadPart;
                FILETIME fTime;
                SYSTEMTIME SysTime = { 0 };
                fTime.dwLowDateTime = uDrvTimeStamp.LowPart;
                fTime.dwHighDateTime = uDrvTimeStamp.HighPart;
                FileTimeToSystemTime(&fTime, &SysTime);
                printf("%02d-%02d-%02d\n", SysTime.wYear, SysTime.wMonth, SysTime.wDay);
            }
            delete[] BinaryInfo;
        }
        RegCloseKey(hKeyResult);
        return stamp;
    }

    BOOL ModifyRegSZHKEY(LPCWSTR lpKeyPath, LPCWSTR lpSubKey, LPCWSTR lpSubKeyItem, LPCWSTR lpItemValue, UINT32 uLen)
    {
        HKEY hKey = NULL, hSubKey = NULL;
        DWORD dwResOpen = 0;
        BOOL bRet = TRUE;

        if (ERROR_SUCCESS != RegCreateKeyEx(HKEY_LOCAL_MACHINE,
            lpKeyPath,
            NULL,
            NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            NULL,
            &hKey,
            &dwResOpen))
        {
            /*LOG(INFO) << "lpKeyPath :[" << SysUtil::ws2s(lpKeyPath).c_str()
                << "], lpSubKey:[" << SysUtil::ws2s(lpSubKey).c_str()
                << "], lpSubKeyItem:[" << SysUtil::ws2s(lpSubKeyItem).c_str()
                << "], lpItemValue:[" << SysUtil::ws2s(lpItemValue).c_str()
                << "], uLen:[" << uLen
                << "], RegCreateKeyEx  err 1";*/
            bRet = FALSE;
            return bRet;
        }

        if (ERROR_SUCCESS != RegCreateKeyEx(hKey,
            lpSubKey,
            NULL,
            NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            NULL,
            &hSubKey,
            &dwResOpen))
        {
            /*LOG(INFO) << "lpKeyPath :[" << SysUtil::ws2s(lpKeyPath).c_str()
                << "], lpSubKey:[" << SysUtil::ws2s(lpSubKey).c_str()
                << "], lpSubKeyItem:[" << SysUtil::ws2s(lpSubKeyItem).c_str()
                << "], lpItemValue:[" << SysUtil::ws2s(lpItemValue).c_str()
                << "], uLen:[" << uLen
                << "], RegCreateKeyEx  err 2";*/
            bRet = FALSE;
            goto reg_err;
        }

        if (ERROR_SUCCESS != ::RegSetValueEx(hSubKey, lpSubKeyItem, 0, REG_SZ, (CONST BYTE*) lpItemValue, uLen))
        {
            bRet = FALSE;
            /*LOG(INFO) << "lpKeyPath :[" << SysUtil::ws2s(lpKeyPath).c_str()
                << "], lpSubKey:[" << SysUtil::ws2s(lpSubKey).c_str()
                << "], lpSubKeyItem:[" << SysUtil::ws2s(lpSubKeyItem).c_str()
                << "], lpItemValue:[" << SysUtil::ws2s(lpItemValue).c_str()
                << "], uLen:[" << uLen
                << "], RegSetValueEx  err";*/
        }

        RegCloseKey(hSubKey);
    reg_err:
        RegCloseKey(hKey);
        return bRet;
    }
}

/////////////////////////////////////////////////
namespace CUtils
{
    std::string UnicodeToUtf8(const std::wstring& wstr)
    {
        std::string ret_str = "";
        int ansiiLen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
        char* pAssii = (char*)malloc(sizeof(char) * ansiiLen);
        WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
        if (nullptr != pAssii)
        {
            ret_str = pAssii; 
        }
        free(pAssii);
        
        return ret_str;
    }

    std::string UnicodeToAscii(const std::wstring& wstr)
    {
        std::string ret_str = "";
        int ansiiLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
        char* pAssii = (char*)malloc(sizeof(char) * ansiiLen);
        WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
        if (nullptr != pAssii)
        {
            ret_str = pAssii;
        }
        free(pAssii);

        return ret_str;
    }

    std::wstring Utf8ToUnicode(const std::string& str)
    {
        std::wstring ret_str = L"";
        int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
        wchar_t* pUnicode = (wchar_t*)malloc(sizeof(wchar_t) * unicodeLen);
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, pUnicode, unicodeLen);
        if (nullptr != pUnicode)
        {
            ret_str = pUnicode;
        }
        
        free(pUnicode);
        return ret_str;
    }

    std::wstring AsciiToUnicode(const std::string& str)
    {
        std::wstring ret_str = L"";
        int unicodeLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
        wchar_t* pUnicode = (wchar_t*)malloc(sizeof(wchar_t) * unicodeLen);
        MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pUnicode, unicodeLen);
        if (nullptr != pUnicode)
        {
            ret_str = pUnicode;
        }

        free(pUnicode);
        return ret_str;
    }

    bool blCheckUdpPortListen(unsigned int nPort)
    {
        if (nPort < 1024 || nPort > 65000)
        {
            return false;
        }

        PMIB_UDPTABLE pudptable = NULL;
        DWORD dwSize = 0;

        if (GetUdpTable(pudptable, &dwSize, TRUE) == ERROR_INSUFFICIENT_BUFFER)
        {
            pudptable = new MIB_UDPTABLE[dwSize];

            if (GetUdpTable(pudptable, &dwSize, TRUE) == NO_ERROR)
            {
                for (UINT i = 0; i < pudptable->dwNumEntries; i++)
                {
                    if (nPort != ntohs(pudptable->table[i].dwLocalPort))
                    {
                        continue;
                    }

                    delete[] pudptable;
                    return true;
                }
            }
        }

        delete[] pudptable;
        return false;
    }

    BOOL ModifyFileExtension(std::wstring path, std::wstring srcType, std::wstring destType)
    {
        WIN32_FIND_DATA fd;
        std::wstring srcFiles = path + srcType;
        HANDLE hFindFile = FindFirstFile(srcFiles.c_str(), &fd);
        if (hFindFile == INVALID_HANDLE_VALUE)
        {
            ::FindClose(hFindFile);
            return FALSE;
        }

        BOOL bIsDirectory = FALSE;
        BOOL bFinish = FALSE;

        CString strSubDirPath;

        while (!bFinish)
        {
            bIsDirectory = ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);

            //如果是.或..  
            if (bIsDirectory && (wcscmp(fd.cFileName, L".") == 0 || wcscmp(fd.cFileName, L"..") == 0))
            {
                bFinish = (FindNextFile(hFindFile, &fd) == FALSE);
                continue;
            }
            std::wstring tempFile = path + fd.cFileName;
            std::wstring DestFile = tempFile + destType;
            MoveFile(tempFile.c_str(), DestFile.c_str());
            bFinish = (FindNextFile(hFindFile, &fd) == FALSE);
        }

        ::FindClose(hFindFile);

        return FALSE;
    }
}
