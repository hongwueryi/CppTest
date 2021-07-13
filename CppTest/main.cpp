#include <stdio.h>
#include "method.h"
#include <list>
#include <vector>
#include <algorithm>
#include <functional>
#include <windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
typedef void(*pcb)(char*);
void callback(char* param)
{
    printf("%s\n", param);
}

void testcall(pcb func)
{
    printf("call\n");
    func("this is callback");
}

int g_nSum = 0;
CRITICAL_SECTION sec;
unsigned __stdcall  threadproc1(void *pArguments)
{
    EnterCriticalSection(&sec);
    for (int iCount = 0; iCount < 20; iCount++) {
        g_nSum++;
        printf("threadproc1@第%d次，g_nSum = %d\n", iCount, g_nSum);
    }
    LeaveCriticalSection(&sec);

    return 0;
}

unsigned __stdcall  threadProc2(void *pArguments)
{
    EnterCriticalSection(&sec);
    for (int iCount = 0; iCount < 20; iCount++) {
        g_nSum++;
        printf("threadProc2@第%d次，g_nSum = %d\n", iCount, g_nSum);
    }
    LeaveCriticalSection(&sec);

    return 0;
}

bool isdigits(wchar_t c)
{
    if (c >= '0' && c <= '9')
        return true;
    return false;
}

bool isalphas(wchar_t c)
{
    if (c >= 'A' && c <= 'z')
        return true;
    return false;
}

//数字>字母>汉字顺序排序
bool CompareStr(CString strArgs1, CString strArgs2)
{
    if (strArgs1.IsEmpty() || strArgs2.IsEmpty())
        return 0;

    USES_CONVERSION;
    string str1 = W2A(strArgs1.GetBuffer(0));
    string str2 = W2A(strArgs2.GetBuffer(0)); 
    
    char c1 = str1[0];
    char c2 = str2[0];
    //int ret = strArgs1.CompareNoCase(strArgs2);
    int ret = strcmp(str1.c_str(), str2.c_str());
    ret = (ret == 1) ? false : true;
    return ret;

    if (isdigits(c1))
    {
        if (!isdigits(c2))
        {
            return true;
        }
        else
        {
            
            return ret; 
        }
    }
    else if (isalphas(c1))
    {
        if (isdigits(c2))
        {
            return false;
        }
        else if (isalphas(c2))
        {
            return ret;
        }
        else
        {
            return true;
        }
    }

    return ret;
}

CString GetAccuracy(double input, unsigned int accuracy)
{
#define buf_size 200
    //通过输入生成精度字符串 （%0.*f）
    wchar_t accuracyBuf[buf_size] = { 0 };
    swprintf_s(accuracyBuf, buf_size, L"%%0.%dlf", accuracy);

    //通过输入生成对应精度的float形打印输出
    wchar_t outputBuf[buf_size] = { 0 };
    swprintf_s(outputBuf, buf_size, accuracyBuf, input);

    //回转回float行数据
    // float output = atof(outputBuf);
    CString cstmp = outputBuf;
    return cstmp;
}

bool isPalindromeNumber(long x)
{
    int a = x, h = 1;
    if (a < 0) return false;
    while (a / h >= 10) {
        h = h * 10;
    }
    while (a > 0) {
        if (a / h != a % 10) return false;
        a = a % h;
        a = a / 10;
        h = h / 100;
}
    return true;

}

BOOL CopyDirectory(CString sourceFilePath, CString destFilePath)
{
    TCHAR src[MAX_PATH] = { 0 };
    TCHAR dst[MAX_PATH] = { 0 };
    _tcscpy_s(src, sourceFilePath);
    _tcscpy_s(dst, destFilePath);
    int len = _tcslen(src);
    if (len > 0 && src[len - 1] == '\\')
        src[len - 1] = '\0';
    len = _tcslen(dst);
    if (len > 0 && dst[len - 1] == '\\')
        dst[len - 1] = '\0';

    SHFILEOPSTRUCT FileOp;
    ZeroMemory(&FileOp, sizeof(SHFILEOPSTRUCT));
    FileOp.fFlags = FOF_SILENT | FOF_NOCONFIRMATION;//不显示对话框.
    FileOp.hNameMappings = NULL;
    FileOp.hwnd = NULL;
    FileOp.lpszProgressTitle = NULL;
    FileOp.pFrom = src;
    FileOp.pTo = dst;
    FileOp.wFunc = FO_COPY;
    return SHFileOperation(&FileOp) == 0;
}

void BackUpDriverFiles(CString sourceFilePath, CString destFilePath)
{
    CString strSourceTemp = sourceFilePath;
    if (strSourceTemp[strSourceTemp.GetLength() - 1] != '\\')
    {
        strSourceTemp += L"\\";
    }

    CString strDestTemp = destFilePath;
    if (strDestTemp[strDestTemp.GetLength() - 1] != '\\')
    {
        strDestTemp += L"\\";
    }

    CString strpath = strSourceTemp;
    strSourceTemp.Append(L"*");

    WIN32_FIND_DATA fd;
    HANDLE hFindFile = FindFirstFile(strSourceTemp, &fd);
    if (hFindFile == INVALID_HANDLE_VALUE)
    {
        ::FindClose(hFindFile);
        return;
    }

    BOOL bIsDirectory = FALSE;
    BOOL bFinish = FALSE;

    while (!bFinish)
    {
        bIsDirectory = ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);

        //如果是.或..  
        if (bIsDirectory && (wcscmp(fd.cFileName, L".") == 0 || wcscmp(fd.cFileName, L"..") == 0))
        {
            bFinish = (FindNextFile(hFindFile, &fd) == FALSE);
            continue;
        }
        CString strTempSourceFullPath = strpath;
        strTempSourceFullPath += fd.cFileName;
        CString strTempDestFullPath = strDestTemp;
        strTempDestFullPath += fd.cFileName;
        ::MoveFile(strTempSourceFullPath, strTempDestFullPath);
        bFinish = (FindNextFile(hFindFile, &fd) == FALSE);
    }

    ::FindClose(hFindFile);
    return;
}

void bindfunc1(int a, int b, int c)
{
    printf("a = %d, b=%d, c=%d", a, b, c);
}

typedef struct process
{
    CString ProcessName;    //进程名
    CString ProcessPath;    //进程全路径
    CString Description;    //进程描述文字
    SIZE_T  WorkingSetSize; //内存占用率
}PROCESSINFO;

#pragma comment(lib, "version.lib")
bool GetFileInfo(CString filepath, CString& info)
{
    DWORD dwSize;
    dwSize = GetFileVersionInfoSize(filepath, NULL);
    if (0 == dwSize)
    {
        return false;
    }

    wchar_t *pBuf;
    pBuf = new TCHAR[dwSize + 1];
    if (nullptr == pBuf)
    {
        return false;
    }
    memset(pBuf, 0, dwSize + 1);

    if (!GetFileVersionInfo(filepath, 0, dwSize, pBuf))
    {
        delete pBuf;
        return false;
    }

    LPVOID lpBuffer = nullptr;
    UINT uLen = 0;
    DWORD ret = ::VerQueryValue(
        pBuf,
        TEXT("\\StringFileInfo\\080404b0\\FileDescription"),
        &lpBuffer,
        &uLen);
    if (0 == ret)
    {
        delete pBuf;
        return false;
    }

    CString des = (TCHAR*)lpBuffer;
    info = des;
    if (info.IsEmpty())
    {
        delete pBuf;
        return false;
    }

    delete pBuf;
    return true;
}

bool GetAllProcessInfo()
{
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(pe32);
    
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);  
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return false;
    }
    
    if (!Process32First(hProcessSnap, &pe32))
    {
        return false;
    }

    
    std::vector<PROCESSINFO>vec;
    while (Process32Next(hProcessSnap, &pe32))
    {
        PROCESSINFO pInfo;
        TCHAR filepath[MAX_PATH] = { 0 };
        CString scTmp = pe32.szExeFile;
        pInfo.ProcessName = scTmp;
        HANDLE hProcessHanlde = (HANDLE)OpenProcess(PROCESS_QUERY_INFORMATION |
            PROCESS_VM_READ, FALSE, pe32.th32ProcessID);
        if (hProcessHanlde == NULL)
        {
            continue;
        }

        GetModuleFileNameEx(hProcessHanlde, NULL, filepath, MAX_PATH);
        if (wcslen(filepath) == 0)
        {
            continue;
        }

        pInfo.ProcessPath = filepath;
        
        CString Description = L"";
        GetFileInfo(filepath, Description);
        pInfo.Description = Description;

        PROCESS_MEMORY_COUNTERS pMemory;
        pMemory.cb = sizeof(PROCESS_MEMORY_COUNTERS);
        if (GetProcessMemoryInfo(hProcessHanlde, &pMemory, sizeof(pMemory)))
        {
            pInfo.WorkingSetSize = pMemory.WorkingSetSize / 1024;
        }

        vec.push_back(pInfo);
    }
    
    return true;
}

void GetAllProcessInfo2()
{
    // Get the list of process identifiers.
    DWORD ProcessesList[1024], cbNeeded, ProcessesCounts;
    std::vector<PROCESSINFO>vec;
    if (!EnumProcesses(ProcessesList, sizeof(ProcessesList), &cbNeeded))
    {
        return;
    }

    // Calculate how many process identifiers were returned.
    ProcessesCounts = cbNeeded / sizeof(DWORD);

    // Print the name and process identifier for each process.
    for (int i = 0; i < ProcessesCounts; i++)
    {
        if (ProcessesList[i] != 0)
        {
            PROCESSINFO pInfo;
            TCHAR szProcessName[MAX_PATH] = { 0 };
            TCHAR szFullPath[MAX_PATH] = { 0 };
            HANDLE hProcessHanlde = OpenProcess(PROCESS_QUERY_INFORMATION |
                PROCESS_VM_READ, FALSE, ProcessesList[i]);

            if (NULL == hProcessHanlde)
            {
                continue;
            }

            HMODULE hMod;
            DWORD cbNeeded;
            if (EnumProcessModules(hProcessHanlde, &hMod, sizeof(hMod), &cbNeeded))
            {
                GetModuleBaseName(hProcessHanlde, hMod, szProcessName,
                    sizeof(szProcessName) / sizeof(TCHAR));
            }
            pInfo.ProcessName = szProcessName;
            GetModuleFileNameEx(hProcessHanlde, NULL, szFullPath, MAX_PATH);
            CString cstrFilePath = szFullPath;
            if (cstrFilePath.IsEmpty())
            {
                continue;
            }

            pInfo.ProcessPath = szFullPath;

            CString Description = L"";
            GetFileInfo(szFullPath, Description);
            pInfo.Description = Description;

            PROCESS_MEMORY_COUNTERS pMemory;
            pMemory.cb = sizeof(PROCESS_MEMORY_COUNTERS);
            if (GetProcessMemoryInfo(hProcessHanlde, &pMemory, sizeof(pMemory)))
            {
                pInfo.WorkingSetSize = pMemory.WorkingSetSize / 1024;
            }

            vec.push_back(pInfo);

            CloseHandle(hProcessHanlde);
        }
    }

    return;
}

char* UnicodeToUtf8(const wchar_t* unicode)
{
    int len;
    len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
    char *szUtf8 = (char*)malloc(len + 1);
    memset(szUtf8, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, unicode, -1, szUtf8, len, NULL, NULL);
    return szUtf8;
}

wchar_t* Utf8ToUnicode(const char* utf, size_t *unicode_number)
{
    if (!utf || !strlen(utf))
    {
        *unicode_number = 0;
        return NULL;
    }
    int dwUnicodeLen = MultiByteToWideChar(CP_UTF8, 0, utf, -1, NULL, 0);
    size_t num = dwUnicodeLen * sizeof(wchar_t);
    wchar_t *pwText = (wchar_t*)malloc(num);
    memset(pwText, 0, num);
    MultiByteToWideChar(CP_UTF8, 0, utf, -1, pwText, dwUnicodeLen);
    *unicode_number = dwUnicodeLen - 1;
    return pwText;
}

wstring AsciiToUnicode(const string& str) 
{   
    int unicodeLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);   
    wchar_t *pUnicode = (wchar_t*)malloc(sizeof(wchar_t)*unicodeLen);    
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pUnicode, unicodeLen);
    wstring ret_str = pUnicode;
    free(pUnicode);
    return ret_str;
}
string UnicodeToAscii(const wstring& wstr) 
{    
    int ansiiLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);   
    char *pAssii = (char*)malloc(sizeof(char)*ansiiLen);    
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
    string ret_str = pAssii;
    free(pAssii);
    return ret_str;
}

wstring Utf8ToUnicode(const string& str)
{   
    int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);   
    wchar_t *pUnicode = (wchar_t*)malloc(sizeof(wchar_t)*unicodeLen);   
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, pUnicode, unicodeLen);
    wstring ret_str = pUnicode;
    free(pUnicode);
    return ret_str;
}

string UnicodeToUtf8(const wstring& wstr)
{    
    int ansiiLen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);    
    char *pAssii = (char*)malloc(sizeof(char)*ansiiLen);    
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
    string ret_str = pAssii;
    free(pAssii);
    return ret_str;
}

typedef void(FUN)();
class fcall
{
public:
    void fun1(FUN f)
    {
        f();
    }   
};

class fcall2
{
public:
    static void print()
    {
        printf("callback\n");
    }
    
    void fun()
    {
        fcall f1;
        f1.fun1(print);
    }
}

int main()
{
    std::vector<int> st;
    st.push_back(0);
    int test = 0;
//     int endd = *(st.end()-1);
//     int endd2 = *(st.rbegin());
//     int endd3 = st.back();
    //st.clear();
 
    fcall2 f2;
    f2.fun();

#if 0
    wstring unico = L"中国D1";
    string utf = UnicodeToUtf8(unico);
    unico = Utf8ToUnicode(utf);
    string asc = UnicodeToAscii(unico);
    unico = AsciiToUnicode(asc);
    int test = 0;
#endif
#if 0
    //GetAllProcessInfo();
    HWND hWnd = ::FindWindow(NULL, L"BaseWnd");
    if (hWnd)
    {
        if (::IsWindowVisible(hWnd))
        {
            SendMessage(hWnd, WM_USER + 1024, 0, 0);
        }
        else
        {
            printf("not visible!\n");
        }
    }
    else
    {
        printf("PrivilegeHideWin hwnd=null");
    }
    system("pause");
    return 0;
#endif

#if 0
    std::string strn = "test\n";
    char c = strn.at(strn.length() - 1);
    if (strn.at(strn.length() - 1) == '\n')
    {
        strn.erase(strn.length() - 1, 1);
    }
    std::string strn2 = strn;
    return 0;
#endif
#if 0
    std::string strtest = "123456";
    std::string str1 = strtest.substr(0, strtest.find('&'));
    std::string str2 = strtest.substr(strtest.find('&') + 1);
    int test = 0;
#endif
#if 0
    CString regsoftid = L"123,456,789,";
    int curPos = 0;
    CString str = L"";
    while ((str = regsoftid.Tokenize(L",", curPos)) != _T(""))
    {
        int num = 0;
    }
#endif

#if 0
    std::function<void (int, int)> bindfunc2 = std::bind(bindfunc1, std::placeholders::_1, std::placeholders::_2, 10);
    bindfunc2(4, 5);
    //BackUpDriverFiles(L"C:\\LenovoDrivers\\Drivers", L"E:\\33");
#endif
#if 0
    if (isPalindromeNumber(1))
    {
        printf("ok!\n");
    }
#endif

#if 0
    DWORD ret = GetFileAttributes(L"C:\\LenovoQMDownload");
    printf("%x\n", ret);
    printf("%d", ret);
    if (ret == (FILE_ATTRIBUTE_REPARSE_POINT | FILE_ATTRIBUTE_DIRECTORY))
    {
        printf("ok!");
        getchar();
    }
#endif

#if 0
    CString szFilePath = L"C:\\L代码\\trunk\\bin\\x86\\Debug";
    szFilePath = szFilePath.Left(szFilePath.Find('\\'));

    DWORD64 qwFreeBytes, qwFreeBytesToCaller, qwTotalBytes;
    BOOL bResult = GetDiskFreeSpaceEx(L"E:",
        (PULARGE_INTEGER)&qwFreeBytesToCaller,
        (PULARGE_INTEGER)&qwTotalBytes,
        (PULARGE_INTEGER)&qwFreeBytes);
    if (bResult) {
        printf("使用GetDiskFreeSpaceEx函数获取磁盘空间信息\n");
        printf("磁盘总容量: %I64d \n" , qwTotalBytes );
        printf("可用的磁盘空闲容量:  %I64d \n", qwFreeBytes);
        printf("磁盘空闲容量: %I64d \n" , qwFreeBytesToCaller);
        printf("GB:%d \n", qwFreeBytesToCaller / 1024 / 1024);
        printf("GB:%.4f\n", (double)qwFreeBytesToCaller / 1024 / 1024);
        printf("GB:%.2f", (double)qwFreeBytesToCaller / 1024 / 1024);
    }

    CString FreeBytesAvailable;
    //DWORD SpaceMB = qwFreeBytesToCaller / 1024 / 1024;
    DWORD SpaceMB = qwFreeBytes / 1024 / 1024;
    if (SpaceMB > 1024)
    {
        //GB
        FreeBytesAvailable.Format(L"%.2fGB", (double)SpaceMB / 1024);
    }
    else
    {
        //MB
        FreeBytesAvailable.Format(L"%dMB", SpaceMB);
    }
#endif
    //system("ipconfig");
    //system("mklink /D E:\linktest1 C:\LenovoQMDownload\SoftMgr");
    //WinExec("ipconfig", SW_SHOW);
    //WinExec("mklink", SW_SHOWNORMAL);
    //int ret = WinExec("mklink /D E:\linktest C:\LenovoQMDownload\SoftMgr", SW_SHOWNORMAL);
    //ShellExecute(NULL, _T("open"), _T("C:\\Windows\\System32\\cmd.exe"), _T("mklink /D E:\linktest C:\LenovoQMDownload\SoftMgr"), NULL, SW_SHOWNORMAL);
    //ShellExecute(NULL, _T("open"), _T("C:\\Windows\\System32\\cmd.exe"), _T("ipconfig"), NULL, SW_SHOWNORMAL);
    //BOOL Ret = CreateSymbolicLink(_T("C:\LenovoQMDownload\SoftMgr"), _T("E:\linktest"), 0);
    //WinExec("cmd.exe /k mklink /D E:\\linktest1 C:\\LenovoQMDownload\\SoftMgr", SW_HIDE);
    int num = GetLastError();
    //int test = 0;
    
    
#if 0
    TCHAR szFilePath[1024] = { 0 };   // 所选择的文件最终的路径
    BROWSEINFO bi;
    ZeroMemory(&bi, sizeof(BROWSEINFO));
    bi.hwndOwner = NULL;
    bi.pszDisplayName = szFilePath;
    bi.lpszTitle = L"从下面选择文件或文件夹:";
    bi.ulFlags = BIF_BROWSEINCLUDEFILES;
    LPITEMIDLIST idl = SHBrowseForFolder(&bi);
    if (NULL == idl)
    {
        return 0;
    }
    SHGetPathFromIDList(idl, szFilePath);
    MessageBox(NULL, szFilePath, 0, MB_OK);
#endif
#if 0
    char ac[3][5];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            char c;
            scanf_s(" %c", &c, 1);
            ac[i][j] = c;
        }
       
    }

    int k;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int s = 0; s < 4; s++)
            {
                if (ac[i][s] > ac[i][s + 1])
                {
                    k = ac[i][s + 1];
                    ac[i][s + 1] = ac[i][s];
                    ac[i][s] = k;
                }
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
            printf("%5c", ac[i][j]);
        printf("\n");
    }
#endif
#if 0
    std::list<int>ltest;
    ltest.push_back(1);
    ltest.push_back(2);
    ltest.push_back(3);
    ltest.push_back(4);
    std::list<int>::iterator it;
    for (it = ltest.begin(); it != ltest.end(); ++it)
    {
        if (*it == 2)
        {
            it = ltest.erase(it);
        }
        printf("%d %d\n", *it, ltest.size());
    }
#endif

#if 0
    testcall(callback);
    Sleep(5000);
#endif
#if 0
    vector<std::wstring> DriverNameVec;
    size_t count = GetDriverNames(DriverNameVec);
#endif
#if 0
	float f = 185.0672;
    DWORD dw = 12;
	printf("f = %.2f, dw= %d, dw=%f\n", f, dw,dw);
#endif
#if 0
    wchar_t * pszPeFileName = L"E:\\L代码\\trunk\\bin\\x86\\Debug\\LenovoAppStore.exe";
    //wchar_t * lnkFileName = L"LenovoAppStore.lnk";
    wchar_t * lnkFileName = L"联想软件商店.lnk";
    bool ret = CreatLinkToStartMenu(pszPeFileName, lnkFileName);
    if (ret)
    {
        wchar_t szStartPath[MAX_PATH] = { 0 };
        SHGetSpecialFolderPath(NULL, szStartPath, CSIDL_DESKTOP, 0);
        wcscat_s(szStartPath, L"\\");
        wcscat_s(szStartPath, lnkFileName);
        // 锁定程序到任务栏
        ShellExecute(NULL, TEXT("TaskbarPin"), szStartPath, NULL, NULL, SW_SHOW);
        printf("创建桌面快捷方式成功！\n");
    }
#endif

#if 0
    CFriend pf(1, 2);
    printf("%d\n", pf.CFAdd());
#endif

#if 0
    unsigned thread;
    unsigned thread2;
    InitializeCriticalSection(&sec);
    HANDLE pHandle[2];
    pHandle[0] = (HANDLE)_beginthreadex(NULL, 0, threadproc1, NULL, 0, &thread);
    pHandle[1] = (HANDLE)_beginthreadex(NULL, 0, threadProc2, NULL, 0, &thread2);
    WaitForMultipleObjects(2, pHandle, TRUE, INFINITE);
    DeleteCriticalSection(&sec);
#endif
    system("pause");
	return 0;
}