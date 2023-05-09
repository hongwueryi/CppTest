#include "commonUtil.h"
#include <iphlpapi.h>


namespace CREG 
{
    // ����ע������������͵����ݣ�������ԭ��ע�������ʾ��16�����ַ���

// ���ִ�����ע������������ݽ���
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
        // ��ȫ�ַ���
        for (UINT j = 0; j < 4 - index; j++)
        {
            str.AppendChar(L'0');
        }

        str.MakeReverse();
        CAtlStringW aa = str.Mid(2, 3);
        CAtlStringW bb = str.Left(2);

        str.Format(L"%ws %ws", aa, bb);
    }

    // ��ԭע����������������͸�ʽ
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

            // ��ö�ȡ��ֵ�ж��ٸ��ַ�
            RegQueryValueEx(hKeyResult, lpValue, NULL, &dwFlags, NULL, &dwLength);

            // ����һ�οռ䣬����ʼ��Ϊ��
            TCHAR* BinaryInfo = new TCHAR[dwLength + 1];
            memset(BinaryInfo, 0, sizeof(TCHAR) * (dwLength + 1));

            if (ERROR_SUCCESS == RegQueryValueEx(hKeyResult, lpValue, NULL, &dwFlags, (LPBYTE)BinaryInfo, &dwLength))
            {
                // ������ԭ���ַ���
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

            // ��ö�ȡ��ֵ�ж��ٸ��ַ�
            RegQueryValueEx(hKeyResult, lpValue, NULL, &dwFlags, NULL, &dwLength);

            // ����һ�οռ䣬����ʼ��Ϊ��
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
}

/////////////////////////////////////////////////
namespace CUtils
{
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

            //�����.��..  
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