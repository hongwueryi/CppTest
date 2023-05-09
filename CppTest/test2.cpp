﻿#include <stdlib.h>
#include "udp.h"
#include <thread>
#include <string>
#include <map>
#include "ExceptionReport.h"
#include <vector>
#include <string>
#include <tchar.h>
#include "udpprxoy.h"
#include <sstream>
#include "tcpprxoy.h"
#include <mutex>
#include "commonUtil.h"
#include "factory.h"
#include "decoratormode.h"
#include "observe.h"
#include <hidsdi.h>
#include "cpu.h"
#include "wifi.h"
#define SET_COMMAND(x,y)			 x = (((x) & 0x7FFFFFFF) | ((y) << 31))
bool g_need = false;
std::once_flag g_once_flag;
#include <fstream>
#include "usb.h"
#include <source_location>
void WriteFile_My(std::string message,
    std::string logfile = "log.log",
    const std::source_location location = std::source_location::current())
{
    std::ofstream ofile;
    SYSTEMTIME systime;
    GetLocalTime(&systime);
    char buffer[MAX_PATH] = { 0 };
    sprintf_s(buffer, "[%04d-%02d-%02d %02d:%02d:%02d] ",
        systime.wYear, systime.wMonth, systime.wDay,
        systime.wHour, systime.wMinute, systime.wSecond);
    std::string strbuffer = buffer;
    strbuffer += "[";
    strbuffer += location.file_name();
    strbuffer += "] [";
    strbuffer += std::to_string(location.line());
    strbuffer += ":";
    strbuffer += std::to_string(location.column());
    strbuffer += "] [";
    strbuffer += location.function_name();
    strbuffer += "] ";
    strbuffer += message;
    ofile.open(logfile.c_str(), std::ios::app);
    ofile << strbuffer.c_str() << std::endl;
    ofile.close();
}

BOOL CALLBACK Monitorenumproc1(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
    Sleep(1000);
    static int iCount = 0;
    printf("monitor: { %ld, %ld, %ld, %ld }\n", lprcMonitor->left, lprcMonitor->top, lprcMonitor->right, lprcMonitor->bottom);
    WriteFile_My("1");
    MONITORINFOEX infoEx;
    memset(&infoEx, 0, sizeof(infoEx));
    infoEx.cbSize = sizeof(infoEx);
    if (GetMonitorInfo(hMonitor, &infoEx))
    {
        WriteFile_My("2");
        //RECT rcMonitor; //物理显示坐标
        //RECT rcWork; //工作显示坐标
        wprintf(L"[%p] [%s] [%s] rcMonitor(l=%d t=%d r=%d b=%d) rcWork(l=%d t=%d r=%d b=%d)\n",
            hMonitor,
            infoEx.szDevice,
            infoEx.dwFlags == MONITORINFOF_PRIMARY ? _T("Primary") : _T("Slave"),
            infoEx.rcMonitor.left, infoEx.rcMonitor.top, infoEx.rcMonitor.right, infoEx.rcMonitor.bottom,
            infoEx.rcWork.left, infoEx.rcWork.top, infoEx.rcWork.right, infoEx.rcWork.bottom);

        DISPLAY_DEVICE pDev;
        ZeroMemory(&pDev, sizeof(DISPLAY_DEVICE));
        pDev.cb = sizeof(DISPLAY_DEVICE);
        if (EnumDisplayDevices(infoEx.szDevice, 0, &pDev, EDD_GET_DEVICE_INTERFACE_NAME))
        {
            wprintf(L"%s\n", pDev.DeviceID);
            WriteFile_My("3");
            WriteFile_My(ws2s(pDev.DeviceID));
        }
    
    }
    return TRUE;  //继续枚举
}

BOOL DeleteReg(LPCWSTR lpSubKey, LPCWSTR lpItem)
{
    HKEY hkResult = NULL;
    HKEY hKey = NULL;
    LSTATUS nRet = -1;

    nRet = RegOpenKeyExW(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE | KEY_SET_VALUE, &hKey);
    if (nRet == ERROR_SUCCESS)
    {
        nRet = RegDeleteValueW(hKey, lpItem);

        RegCloseKey(hKey);

        if (nRet != ERROR_SUCCESS)
        {
            cout << "delete : failed" << endl;
        }
    }

    return nRet == ERROR_SUCCESS ? TRUE : FALSE;
}

const char* teststr()
{
    string strTest = "1234";
    return strTest.c_str();
}

bool GetTouchVerEx(const char* pInfo, char* pVer, int nBufLen)
{
    const char* pTemp = strstr(pInfo, "REV_");
    if (NULL == pTemp)
    {
        return false;
    }
    const char* pTemp1 = strstr(pTemp, "&");
    if (NULL == pTemp || NULL == pTemp1)
    {
        return false;
    }
    int nOffset = strlen("REV_");
    int nLen = pTemp1 - pTemp - nOffset;

    strncpy_s(pVer, nBufLen, pTemp + nOffset, nLen);
    return true;
}


class MyClass
{
public:
    MyClass(int i = 0)
    {
        printf("%d", i);
    }
    MyClass(const MyClass& x)	//拷贝构造
    {
        printf("拷贝构造\n");;
    }
    MyClass& operator=(const MyClass& x) 	//赋值拷贝构造
    {
        printf("赋值拷贝构造\n");
        return *this;
    }
    ~MyClass()
    {
        printf("~");
    }
};

void test_once(int param)
{
    printf("only one:%d\n", param);
}

DWORD WINAPI ProcessRecvMsgThread(LPVOID param)
{
    Sleep(4000);
    return 0;
}

void ParseUrlAndMd5(string srcData, string& url, string& md5, string falg=";;")
{
    if (srcData.empty())
        return;
    size_t nPos = srcData.find(falg);
    if (nPos != std::string::npos)
    {
        url = srcData.substr(0, nPos);
        md5 = srcData.substr(nPos + falg.length());
    }
    else
    {
        url = srcData;
        md5 = "";
    }
}

void ByForce(bool& bNeedReboot)
{
    for (int i = 0; i < 3; i++)
    {
        if (!bNeedReboot)
        {
            int iRet = i;
            bNeedReboot = (iRet == 1 ? true : false);
        }
        Sleep(1000);
    }
}


std::mutex g_testmu;
int g_num = 0;
std::vector<int> vi;

using namespace std;
char* pBuf = nullptr;

typedef int(FUN)(int i);
class fcall
{
public:
    int fun1(FUN f, int i)
    {
        return f(i);
    }
};

int print(int i)
{
    printf("callback\n");
    return i;
}

uint8_t UVCHeader[12] =
{
    0x0C,                           /* Header Length */
    0x0C,                           /* Bit field header field */
    0x00,0x00,0x00,0x00,            /* Presentation time stamp field */
    0x00,0x00,0x00,0x00,0x00,0x00   /* Source clock reference field */
};
const static uint8_t UVC_HEADER_EOF = (uint8_t)(1 << 1);            /* End of frame indication */
const static uint8_t UVC_HEADER_FRAME_ID = (uint8_t)(1 << 0);       /* Frame ID toggle bit */
#define UVC_MAX_HEADER 12
void add_UVCHeader(uint8_t* buf, bool eof)
{
    /* Copy header to buffer */
    memcpy((uint8_t*)buf, (uint8_t*)UVCHeader, UVC_MAX_HEADER);

    /* Check if last packet of the frame. */
    if (eof)
    {
        /* Modify UVC header to toggle Frame ID */
        UVCHeader[1] ^= UVC_HEADER_FRAME_ID;

        /* Indicate End of Frame in the buffer */
        buf[1] |= UVC_HEADER_EOF;
    }

}

int getDataFromConsole() 
{
    HANDLE hRead, hWrite;    //管道的读写句柄
    SECURITY_ATTRIBUTES sa; //管道安全属性相关结构体

    sa.nLength = sizeof(SECURITY_ATTRIBUTES); //结构体长度赋值
    sa.lpSecurityDescriptor = NULL;           //NULL管道默认安全描述符,管道的安全属性将继承与父程序
    sa.bInheritHandle = TRUE;                 //一个布尔值，指定在创建新进程时是否继承返回的句柄。如果此成员为TRUE，则新进程将继承该句柄。

    if (!::CreatePipe(&hRead, &hWrite, &sa, 0)) {  //尝试创建管道，失败则弹出提示并退出
        printf("Error on CreateProcess\n");
        return 1;
    }

    STARTUPINFO si;         //启动信息结构体
    PROCESS_INFORMATION pi; //进程信息结构体
    si.cb = sizeof(STARTUPINFO);  //初始化启动信息结构体大小
    ::GetStartupInfo(&si);        //获取父进程的启动信息，利用这个函数我们可以只需要修改较少的参数值
    si.hStdError = hWrite;        //重定向错误信息输出到管道
    si.hStdOutput = hWrite;       //重定向标准输出新信息到管道
    si.wShowWindow = SW_HIDE;     //设定子进程窗体是否隐藏
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES; //wShowWindow成员将包含其他信息；hStdInput，hStdOutput和hStdError成员包含其他信息。
    if (!::CreateProcess(
        L"E:\\Dten\\other demo\\CppTest\\x64\\Debug\\C11Test.exe",
        nullptr,
        NULL, NULL,
        TRUE,                   //新进程继承父进程相关权限
        NULL, NULL, NULL,
        &si,
        &pi)
        ) {
        printf("Error on CreateProcess, err=%d\n", GetLastError());
        return 1;
    }

    ::CloseHandle(pi.hThread);
    ::CloseHandle(pi.hProcess);
    ::CloseHandle(hWrite);    //关闭管道写入句柄

    std::string result;
    char buffer[1025] = { 0 };
    DWORD bytesRead;
    while (true) {   //读取管道内的数据
        memset(buffer, 0, 1025);
        if (::ReadFile(hRead, buffer, 1024, &bytesRead, NULL) == NULL) break;
        result += buffer;
        ::Sleep(100);
    }

    printf("\n\n%s\n", result.c_str());
    return 0;
}

BOOL EnablePrivilege()
{
    LUID PrivilegeRequired;
    DWORD dwLen = 0, iCount = 0;
    BOOL bRes = FALSE;
    HANDLE hToken = NULL;
    BYTE* pBuffer = NULL;
    TOKEN_PRIVILEGES* pPrivs = NULL;

    bRes = LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &PrivilegeRequired);
    if (!bRes) return FALSE;

    bRes = OpenThreadToken(GetCurrentThread(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, TRUE, &hToken);
    if (!bRes)
    {
        printf("%d\n", GetLastError());
        return FALSE;
    }

    bRes = GetTokenInformation(hToken, TokenPrivileges, NULL, 0, &dwLen);
    if (TRUE == bRes)
    {
        CloseHandle(hToken);
        return FALSE;
    }
    pBuffer = (BYTE*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwLen);
    if (NULL == pBuffer) return FALSE;

    if (!GetTokenInformation(hToken, TokenPrivileges, pBuffer, dwLen, &dwLen))
    {
        CloseHandle(hToken);
        HeapFree(GetProcessHeap(), 0, pBuffer);
        return FALSE;
    }

    // Iterate through all the privileges and enable the one required
    bRes = FALSE;
    pPrivs = (TOKEN_PRIVILEGES*)pBuffer;
    for (iCount = 0; iCount < pPrivs->PrivilegeCount; iCount++)
    {
        if (pPrivs->Privileges[iCount].Luid.LowPart == PrivilegeRequired.LowPart &&
            pPrivs->Privileges[iCount].Luid.HighPart == PrivilegeRequired.HighPart)
        {
            pPrivs->Privileges[iCount].Attributes |= SE_PRIVILEGE_ENABLED;
            // here it's found
            bRes = AdjustTokenPrivileges(hToken, FALSE, pPrivs, dwLen, NULL, NULL);
            break;
        }
    }

    CloseHandle(hToken);
    HeapFree(GetProcessHeap(), 0, pBuffer);
    return bRes;
}

std::vector<std::string> util_strsplit2(const std::string& str, const char c)
{
    //类似与Pyhon的 , string.split("c")
    std::vector<std::string> v;								//输入 string  "a*b**c****d******e***********f"
    //输出 vector  ('a','b','c','d','e','f');

    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(c, 0);
    // Find first "non-delimiter".
    std::string::size_type pos = str.find_first_of(c, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        v.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(c, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(c, lastPos);
    }

    return v;

}

BOOL ModifyRegMultiSZ(LPCWSTR lpKeyPath, LPCWSTR lpItem, LPCTSTR dwValue, int len)
{
    HKEY hKey = NULL, hSubKey = NULL;
    DWORD dwResOpen = 0;
    BOOL bRet = TRUE;
    wstring wstr = L"";
    DWORD dwType, dwSize;
    vector<wstring> vec;
    TCHAR* pChValue = new TCHAR[dwSize + 1]{ 0 };
#if 1
    if (ERROR_SUCCESS != RegCreateKeyEx(HKEY_LOCAL_MACHINE,
        lpKeyPath,
        NULL,
        NULL,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS | KEY_WOW64_64KEY,
        NULL,
        &hKey,
        0))
    {
        return bRet;
    }

#else
	if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpKeyPath, 0, KEY_ALL_ACCESS, &hKey))
	{
        return FALSE;
	}
#endif
    if (ERROR_SUCCESS != ::RegSetValueEx(hKey, lpItem, 0, REG_MULTI_SZ, (CONST BYTE*)dwValue, len))
    {
        bRet = FALSE;
    }

	
    // 获取类型、长度
    if (RegQueryValueEx(hKey, lpItem, NULL, &dwType, NULL, &dwSize) != ERROR_SUCCESS)
    {
        goto toerr;
    }
	
    // 读取数据
   
    // 此函数无需调用RegOpenKeyEx，仅在VISTA及以上版本系统可用，XP系统以下系统不可用，XP系统用RegQueryValueEx
    // _WIN32_WINNT >= 0x0600 则可用，Win10: 0x0A00。
    //RegGetValue(HKEY_LOCAL_MACHINE, lpKeyPath, lpItem, RRF_RT_REG_MULTI_SZ, nullptr, pChValue, &dwSize);
	if (RegQueryValueEx(hKey, lpItem, NULL, &dwType, (LPBYTE)pChValue, &dwSize) != ERROR_SUCCESS)
	{
		goto toerr;
	}

	for (int i = 0; i < dwSize/sizeof(wchar_t); i++)
	{
        if (pChValue[i] == '\0')
        {
			wprintf(L"%s\n", wstr.c_str());
            vec.push_back(wstr);
            wstr = L"";
        }
        else
        {
            wstr.append(1, pChValue[i]);

        }
	}
	delete[] pChValue;
 
toerr:
	
    RegCloseKey(hKey);
    return bRet;
}

CExceptionReport report1;
void Socket_udp_test()
{
	std::thread tUdp_s([] {
		DtenUdp::GetInstance()->Run();
		});

#if 1
	std::thread tUdp_c([] {
		//DtenUdp::GetInstance()->SendTOServer();
		});
#endif
	tUdp_c.detach();
	tUdp_s.detach();
}

BOOL CALLBACK DeskEnum(LPWSTR desk, LPARAM lParam)
{
	int bun = 0;
	return TRUE;
}

BOOL CALLBACK WorkStationEnum(LPTSTR lpszWindowStation, _In_ LPARAM lParam)
{
	return TRUE;
}

#include <winnt.h>
UINT WINAPI threadproct(LPVOID param)
{
	printf("thread begin\n");
	Sleep(4000);
	printf("thread end\n");
	return 0;
}

class ptrTest
{
public:
	ptrTest(int* test1);
	~ptrTest();
	void test()
	{
		int* test2 = test_;
		*test2 = 100;
	}
	void print()
	{
		printf("%d\n", *test_);
	}
private:
	int* test_;
};

ptrTest::ptrTest(int* test1)
{
	test_ = test1;
}

ptrTest::~ptrTest()
{
}


std::vector<std::string> util_strsplit(const std::string& str, const char c)
{
    std::vector<std::string> v;

    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(c, 0);
    // Find first "non-delimiter".
    std::string::size_type pos = str.find_first_of(c, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        v.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(c, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(c, lastPos);
    }

    return v;

}

#include <filesystem>
void FileTimeToTime_t(const FILETIME* ft, time_t* t)
{
    ULARGE_INTEGER ui;
    ui.LowPart = ft->dwLowDateTime;
    ui.HighPart = ft->dwHighDateTime;
    *t = (DWORD)((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);
}

void Time_tToTm(time_t t, tm* _t)
{
    tm tt;
    localtime_s(&tt, &t);
    memcpy(_t, &tt, sizeof(tm));
}

void FileTimeToTm(const FILETIME* ft, tm* t)
{
    time_t tm;
    FileTimeToTime_t(ft, &tm);

	Time_tToTm(tm, t);
}

#include "usb.h"
#define STR_CAMERAL_HARDID_REGEX _T("USB\\\\VID_174F&PID_2440&REV_.{4}&MI_00")
#define STR_BUZ_HARDID_REGEX			_T("USB\\\\VID_10C4&PID_EA60&REV_.{4}")
#define STR_SPEAKER_HARDID_REGEX        _T("USB\\\\VID_1D6B&PID_0105&REV_.{4}&MI_00")

#define SPEAKER_PCIE	L"DTEN Board"

DWORD WINAPI  RunOrbitCmdThread(LPVOID lpParam)
{
    std::string strCmd = (char*)lpParam;
    printf("RunOrbitCmdThread strCmd:%s", strCmd.c_str());
    int nRet = system(strCmd.c_str());
    return nRet;
}


void callback_parse_udp_data(void* pData, unsigned int uDataLen)
{
	if (nullptr == pData)
		return;
	printf("%s\n", pData);
}

int CompareVersion(char* ReadVer, char* newVer)
{
    char oldVer[20] = { 0 };
    sprintf_s(oldVer, "%d.%d.%d", ReadVer[2], ReadVer[3], ReadVer[4]);
    istringstream isNewVer(newVer);
    istringstream isOldVer(oldVer);
    string string1;
    string string2;
    while (!isNewVer.eof() || !isOldVer.eof())
    {
        getline(isNewVer, string1, '.');
        getline(isOldVer, string2, '.');
        if (stoi(string1) > stoi(string2))
            return 1;
        if (stoi(string1) < stoi(string2))
            return -1;
        string1 = string2 = "0";
    }
    return 0;
}
const GUID SubCamClassGuid = { 0x6cfd2a07L, 0x7437, 0x42c7,  { 0x9f, 0x6e, 0x2c, 0x87, 0xfc, 0x19, 0xa6, 0x5c } };

#include <atlstr.h>
#pragma comment(lib, "Version.lib")
/*
可以测试的属性pszType:
CompanyName FileDescription FileVersion InternalName LegalCopyright OriginalFilename
ProductName ProductVersion Comments LegalTrademarks PrivateBuild SpecialBuild
*/
CString GetFileVerInfo(LPCTSTR  strFilePath, LPCTSTR pszType)
{
    DWORD dwSize;
    DWORD dwRtn;
    CString szVersion;
    if (strFilePath == NULL)
        return L"";

    dwSize = GetFileVersionInfoSize(strFilePath, NULL);
    if (dwSize == 0)
        return L"";

    CHAR* pBuf;
    pBuf = new CHAR[dwSize + 1];
    if (pBuf == NULL)
        return L"";

    memset(pBuf, 0, dwSize + 1);
    dwRtn = GetFileVersionInfo(strFilePath, NULL, dwSize, pBuf);
    if (dwRtn == 0)
        return L"";

    char* pVerValue = NULL;
    UINT nSize = 0;
    dwRtn = VerQueryValue(pBuf, TEXT("\\VarFileInfo\\Translation"), (LPVOID*)&pVerValue, &nSize);
    if (dwRtn == 0)
        return L"";
    CString strSubBlock, strTranslation, strTemp;
    strTemp.Format(L"%04x", *((unsigned short int*)pVerValue));
    strTranslation = strTemp;
    strTemp.Format(L"%04x", *((unsigned short int*) & pVerValue[2]));
    strTranslation += strTemp;
    //080404b0为中文，040904E4为英文

    strSubBlock.Format(L"\\StringFileInfo\\%ws\\%ws", strTranslation, pszType);
    dwRtn = VerQueryValue(pBuf, strSubBlock.GetBufferSetLength(256), (LPVOID*)&pVerValue, &nSize);
    strSubBlock.ReleaseBuffer();
    if (dwRtn == 0)
        return L"";

    szVersion = (TCHAR*)pVerValue;
    delete pBuf;
    return szVersion;
}

const GUID DtenMicClassGuid = { 0xC166523CL, 0xFE0C, 0x4A94,	{ 0xA5, 0x86, 0xF1, 0xA8, 0x0C, 0xFB, 0xBF, 0x3E } };
#include <regex>
#include <unordered_map>
#include <deque>
typedef struct _mmregdata {
    uint32_t addr;
    uint32_t data;
}MMRegData;

typedef struct _mmregdataex {
    uint32_t addr;
    uint32_t data[2];
}MMRegDataEx;

#include <future>

void dura(bool br)
{
    static bool bNeedRestart = false;
    static UINT64 dwStart = GetTickCount64();
    if (br)
    {
        if (bNeedRestart)
        {
            dwStart = GetTickCount64();
            bNeedRestart = false;
        }
        UINT64 duration = GetTickCount64() - dwStart;
        if (duration >= 30000)
        {
            
            printf("min keep idle statu, arrive standby.\n");

        }
    }
    else
    {
        bNeedRestart = true;
    }
}
#include <regex>
typedef struct
{
    unsigned char uCommand;					//请求指令
    unsigned char uMultiPackage : 1;		//是否拆分多包， 0-单包， 1-多包
    unsigned char uPackMark : 1;			//多包数据标志位， 默认单包0,   末尾包1
    unsigned char uStatus : 1;				//请求or响应	0-请求	1-响应
    unsigned char uDataLen : 5;				//有效数据长度,最大长度为24
    unsigned char uData[32];	//自定义数据，当拆分多包时，uData[0]为包序号，00~FF
} DTEN_UART_DATA_, * PDTEN_UART_DATA;

typedef union
{
    unsigned char uCommandData[32];
    unsigned char uUpgradeCmdData[32];
    DTEN_UART_DATA_ mUartCommandData;
    UCHAR uUpgradeDataLen;
} UDEV_COMM_DATA, * PUDEV_COMM_DATA;

int main()
{
#if 0
    UDEV_COMM_DATA mSenderData = { 0 };
    DTEN_UART_DATA_ data;
    data.uCommand = 0x31;
    data.uDataLen = 9;
    mSenderData.mUartCommandData = data;
    memcpy(mSenderData.uUpgradeCmdData, "1234567890abcdef", 15);

    printf("%d,%s\n", mSenderData.mUartCommandData.uDataLen, mSenderData.uUpgradeCmdData);

#endif

#if 0
    int itype = 0;
    printf("please input 0-8\n");
    scanf_s("%d", &itype);
    char buffer[MAX_PATH] = { 0 };
    DWORD namelen = MAX_PATH;
    BOOL bret = GetComputerNameExA((COMPUTER_NAME_FORMAT)itype, buffer, &namelen);
    //BOOL bret = GetComputerNameA(nullptr, &namelen);
    //BOOL bret = GetComputerNameA(buffer, &namelen);
    char namebuffer[MAX_PATH] = { 0 };  //ComputerNamePhysicalDnsHostname
    sprintf(namebuffer, "%d%s", itype, "-G3-DTEN-0123456789ABCDEFGHIGKLMNOPQRSTUVWXYZ");
    bret = SetComputerNameExA((COMPUTER_NAME_FORMAT)itype, namebuffer);//SetComputerNameA("test_dten");

    printf("%d-name:%s, len:%d\n", GetLastError(), buffer, namelen);
    //\\s(\d{ 2 }) :(\d{ 2 })
    string ws = "^\\d{4}-\\d{2}-\\d{2}\\s\\d{2}:\\d{2}$";
    std::regex pattern(ws);
    std::smatch  matchResult;
    std::string ontime = "202-09-00 08:02"; // 
    //LOG(INFO) << "szHardWareID:" << SysUtil::ws2s(szHardWareID).c_str();
    //LOG(INFO) << "psRegex:" << SysUtil::ws2s(*it).c_str();
    if (std::regex_match(ontime, matchResult, pattern))
    {
        printf("ok!");
    }
#endif
#if 0
    dura(0);
    Sleep(1000);
    dura(1);
    Sleep(1000);
    dura(0);
    Sleep(10000);
    dura(1);
    Sleep(10000);
    dura(1);
    Sleep(20000);
    dura(1);
    SYSTEMTIME syst;
    GetLocalTime(&syst);
    char buffer[32] = { 0 };
    sprintf(buffer, "%04d-%02d-%02d %02d:%02d", syst.wYear, syst.wMonth, syst.wDay, syst.wHour, syst.wMinute);
    string strCurTime = buffer;

    string offtime = "2022-09-16 16:00";
    string onTime = "2022-09-17 08:00";
    if (strcmp(strCurTime.c_str(), offtime.c_str()) >= 0 && strcmp(strCurTime.c_str(), onTime.c_str()) == -1)
    {
        printf("right time\n");
    }
    string onTime_day = onTime.substr(8, 2);
    string onTime_Hour = onTime.substr(11, 2);
    string onTime_Min = onTime.substr(14, 2);
    char param[32] = { 0 };
    sprintf_s(param, "2 %d %d %d 0", atoi(onTime_day.c_str()), atoi(onTime_Hour.c_str()), atoi(onTime_Min.c_str()));

#endif
    //PrintDevicesInfo();
#if 0
    //驱动安装和卸载
    int nRet = 0;
    char szParam[1024] = { 0 };
    sprintf_s(szParam, 1024 - 1, "%s %s", "C:\\DTEN\\HardWare\\Driver\\devcon64.exe", "rescan");
    //nRet = system(szParam);
    //Sleep(1500);
    //wstring haid = L"USB\\VID_2D95&PID_6002&REV_0409";
    wstring haid = L"USB\\VID_351E&PID_00C9";
    wstring infoo;
    GetDeviDriverInfo(haid, infoo);
    char uninstall[MAX_PATH] = { 0 };
    sprintf_s(uninstall, "pnputil /delete-driver %s /uninstall /force", ws2s(infoo).c_str());
    printf("cmd=%s\n", uninstall);
    int isys = system(uninstall);
    printf("uninstall down. isys=%d", isys);

    string infpath = "C:\\DTEN\\HardWare\\Driver\\dtensmart\\MutCamera.inf";
    char install[MAX_PATH] = { 0 };
    sprintf_s(install, "pnputil /add-driver %s /install", infpath.c_str());
    printf("cmd=%s\n", install);
    isys = system(install);
    printf("install down. isys=%d", isys);
#endif
#if 0
    string result;
    std::thread tlab([&result]() {
        Sleep(2000);
        result = "test2";
        int n = 0;
        });
    Sleep(3000);
    tlab.detach();
    MMRegDataEx _24_149Ghz = { 0x000099, 0x24B77333, 0x34B77333 };
    printf("0x%08x,0x%08x,0x%08x\n", _24_149Ghz.addr, _24_149Ghz.data[0], _24_149Ghz.data[1]);
    std::vector<MMRegData>vMMReg;
    vMMReg.push_back({ 0x00001F, 0x00000000 });
    vMMReg.push_back({ 0x00001E, 0x00000200 });
    vMMReg.push_back({ 0x000015, 0x11110100 });
    vMMReg.push_back({ 0x000016, 0x01000000 });
    vMMReg.push_back({ 0x000017, 0x00000000 });
    vMMReg.push_back({ 0x000018, 0x73100000 });
    vMMReg.push_back({ 0x000019, 0x73100000 });
    vMMReg.push_back({ 0x00003D, 0x00000000 });
    vMMReg.push_back({ 0x00003E, 0x00000000 });
    vMMReg.push_back({ 0x00003F, 0x00000000 });
    vMMReg.push_back({ 0x000040, 0x00000000 });
    vMMReg.push_back({ 0x000041, 0xFFFFFFF0 });
    vMMReg.push_back({ 0x000042, 0xFFFFFE2F });
    vMMReg.push_back({ 0x000043, 0xFFFFFFA4 });
    vMMReg.push_back({ 0x000002, 0x7FFD0000 });
    vMMReg.push_back({ 0x000003, 0x11111111 });
    vMMReg.push_back({ 0x000004, 0x0000FF87 });
    vMMReg.push_back({ 0x000032, 0x00000003 });
    vMMReg.push_back({ 0x000033, 0x22333333 });
    vMMReg.push_back({ 0x000034, 0x33322900 });
    vMMReg.push_back({ 0x000035, 0x03000030 });
    vMMReg.push_back({ 0x00001A, 0x13130000 });
    vMMReg.push_back({ 0x00001B, 0x03062000 });
    vMMReg.push_back({ 0x00001C, 0x0C0C8100 });
    vMMReg.push_back({ 0x00001D, 0xA0110500 });
    vMMReg.push_back({ 0x000020, 0x00011414 });
    vMMReg.push_back({ 0x00003B, 0x0000400C });
    vMMReg.push_back({ 0x00003C, 0x0000FF00 });
    vMMReg.push_back({ 0x000021, 0x00001000 });
    vMMReg.push_back({ 0x000022, 0x00010088 });
    vMMReg.push_back({ 0x000026, 0x00010088 });
    vMMReg.push_back({ 0x00002A, 0x00010088 });
    vMMReg.push_back({ 0x00002E, 0x00010088 });
    vMMReg.push_back({ 0x000021, 0x00010088 });
    vMMReg.push_back({ 0x00009B, 0x011FFE44 });
    vMMReg.push_back({ 0x0000B4, 0xFFFFFFFF });
    vMMReg.push_back({ 0x0000B5, 0xFFFFFFFF });
    vMMReg.push_back({ 0x0000AF, 0x00000001 });
    vMMReg.push_back({ 0x0000B5, 0x7FFFFFFF });
    vMMReg.push_back({ 0x0000AE, 0x0000040F });
    vMMReg.push_back({ 0x0000AF, 0x00007801 });
    vMMReg.push_back({ 0x0000B5, 0xFFFFFFFF });
    vMMReg.push_back({ 0x000005, 0x58885888 });
    vMMReg.push_back({ 0x000006, 0x00080000 });
    vMMReg.push_back({ 0x000007, 0x00002880 });
    vMMReg.push_back({ 0x000008, 0x00040647 });
    vMMReg.push_back({ 0x000009, 0x04000000 });
    vMMReg.push_back({ 0x00000A, 0x33005500 });
    vMMReg.push_back({ 0x00000B, 0x00031300 });
    vMMReg.push_back({ 0x00000C, 0x42500000 });
    vMMReg.push_back({ 0x00000D, 0x00000000 });
    vMMReg.push_back({ 0x00000E, 0x00002880 });
    vMMReg.push_back({ 0x00000F, 0x00040647 });
    vMMReg.push_back({ 0x000010, 0x04000000 });
    vMMReg.push_back({ 0x000011, 0x33005500 });
    vMMReg.push_back({ 0x000012, 0x00031300 });
    vMMReg.push_back({ 0x000013, 0x42500000 });
    vMMReg.push_back({ 0x000014, 0x00000000 });
    vMMReg.push_back({ 0x000000, 0x00131111 });
    vMMReg.push_back({ 0x000001, 0x00131111 });

    std::vector<MMRegData>::iterator it;
    for (it = vMMReg.begin(); it != vMMReg.end(); ++it)
    {
        uint32_t addr = it->addr;
        uint32_t data = it->data;
    }

    /* std::wstring strDevDes = L"1-MicrophoneDTEN Mic d7)";
     wsmatch  matchResult;
     wregex pattern(L".*Microphone.*DTEN Mic.*");
     if (std::regex_match(strDevDes, matchResult, pattern))
     {
         printf("---------\n");
     }*/
    std::vector<wstring> vecMicNode1;
    vecMicNode1.push_back(L"MMDEVAPI\\AudioEndpoints");
    dwGetCurDrvInfo1(NULL, NULL, vecMicNode1, nullptr, L"test12323213");
    GetDrvStatusByName(L".*Microphone.*DTEN Mic.*");
    //GetDrvStatusByName(L".*DTEN Board.*");

#endif
#if 0
    uint8_t newVer[10] = { 0 };
    string strVer = "1.1.20";
    char* token = strtok((char*)strVer.c_str(), ".");
    int i = 2;
    if (nullptr != token)
        newVer[i] = stoi(token, 0, 16);
    else
        return -1;
    while (token != nullptr)
    {
        i++;
        token = strtok(nullptr, ".");
        if (token != nullptr)
            newVer[i] = stoi(token, 0, 16);
    }

    wstring str = L"1234";
    if (str.find(L"35") != std::string::npos)
    {

        char szCur[MAX_PATH] = { 0 };
        getCurMicVer(szCur, MAX_PATH);
    }
#endif

#if 0
    CString vers = GetFileVerInfo(
        L"C:\\DTEN\\DTENServices\\DTENServices.exe", L"FileVersion");
    int nn = 0;
#endif
#if 0
    TCHAR* arrSpeakerHard2[1] = { _T("USB\\\\VID_351E&PID_00CD&REV_.{4}") };
    DevDrvInfo drvInfoD = { 0 };
    int nRetCD = dwGetCurDrvInfo(nullptr, nullptr, arrSpeakerHard2, 1, &drvInfoD);
#endif
#if 0
    string strVer = "1.9.8b";

    uint8_t newVer[128] = { 0 };
    char* token = strtok((char*)strVer.c_str(), ".");
    int i = 2;
    if (nullptr != token)
        newVer[i] = stoi(token, 0, 16);
    else
        return -1;
    while (token != nullptr) {
        i++;
        token = strtok(nullptr, ".");
        if (token != nullptr)
            newVer[i] = stoi(token, 0, 16);
    }
#endif
#if 0
    DWORD dwThreadId;
    string strCmd = "reg add \"HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\DTEN\" /f /v \"disable_hdmi_auto\" /t REG_DWORD /d \"1\"";
    HANDLE m_hThread = CreateThread(NULL, 0, RunOrbitCmdThread, (char*)strCmd.c_str(), 0, &dwThreadId);
#endif
#if 0
    std::wstring strDevDes = L"DTEN Board (Intel(R) Display Audio)";
    if (strDevDes.find(SPEAKER_PCIE) != std::wstring::npos)
    {
        int nRet = 1;
    }
    GetDrvStatusByName(SPEAKER_PCIE);
#endif
    //USB\VID_174F&PID_2440&REV_0014&MI_00
    //TCHAR* arrSpeakerHard[2] = { NULL, STR_CAMERAL_HARDID_REGEX };
#if 0
    printf("USB\\\\VID_1D6B&PID_0105&REV_.{4}&MI_00\n");
    TCHAR* arrSpeakerHard[2] = { NULL, STR_SPEAKER_HARDID_REGEX };
    dwGetCurDrvInfo(NULL, _T("USB"), arrSpeakerHard, 2, NULL);
    printf("\n---------------------\n");
    printf("USB\\\\VID_10C4&PID_EA60&REV_.{4}\n");
    TCHAR* arrSpeakerHard2[2] = { NULL, STR_BUZ_HARDID_REGEX };
    dwGetCurDrvInfo(NULL, _T("USB"), arrSpeakerHard2, 2, NULL);
#endif
#if 0
    HANDLE hFile = CreateFile(L"C:\\Windows\\MEMORY.DMP", GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_DELETE,
        NULL, OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS, NULL);
    FILETIME lpCreationTime;
    FILETIME lpLastAccessTime;
    FILETIME lpLastWriteTime;
    if (GetFileTime(hFile, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime))
    {
        time_t tt;
        tm tm_;
        SYSTEMTIME syst;
        FileTimeToTime_t(&lpCreationTime, &tt);
        FileTimeToTm(&lpCreationTime, &tm_);
        FileTimeToSystemTime(&lpCreationTime, &syst);
        chrono::system_clock::time_point now = chrono::system_clock::now();//当前时间time_point格式
        std::time_t nowTime_t = chrono::system_clock::to_time_t(now);//转换为 std::time_t 格式 
        LONGLONG duration = (nowTime_t - tt);
        LONGLONG duration1 = duration / 60 / 60 / 12;
        int num = 0;
    }

    chrono::system_clock::time_point now = chrono::system_clock::now();//当前时间time_point格式
    std::time_t nowTime_t = chrono::system_clock::to_time_t(now);//转换为 std::time_t 格式 
    std::put_time(std::localtime(&nowTime_t), "%Y-%m-%d %X"); //2021-6-24 14:44:47
    //chrono::system_clock::from_time_t()
#endif
#if 0
    std::string strTime = "19:30-23:30";
    std::vector<std::string> strValues = util_strsplit(strTime, '-');
    int iWaitTime = 0;
    int iStartTime = 0;
    int iEndTime = 0;
    if (strValues.size() >= 2)
    {
        std::string strStart = strValues[0];
        std::vector<std::string> strStartValue = util_strsplit(strStart, ':');
        if (strStartValue.size() >= 2)
        {
            int iStartHour = 0;
            int iStartMin = 0;
            iStartHour = atoi(strStartValue[0].c_str());
            iStartMin = atoi(strStartValue[1].c_str());
            iStartTime = iStartHour * 60 + iStartMin;
        }
        std::string strEnd = strValues[1];
        std::vector<std::string> strEndValue = util_strsplit(strEnd, ':');
        if (strEndValue.size() >= 2)
        {
            int iEndHour = 0;
            int iEndMin = 0;
            iEndHour = atoi(strEndValue[0].c_str());
            iEndMin = atoi(strEndValue[1].c_str());
            iEndTime = iEndHour * 60 + iEndMin;
        }
    }
    SYSTEMTIME stTime = { 0 };
    GetLocalTime(&stTime);

    int iCurTime = stTime.wHour * 60 + stTime.wMinute;

    int iWaiteTime = 0;
    if (iCurTime < iStartTime)
    {
        iWaiteTime = iStartTime - iCurTime;
    }
    else if (iCurTime >= iStartTime && iCurTime <= iEndTime)
    {
        iWaiteTime = 0;
    }
    else if (iCurTime > iEndTime)
    {
        iWaiteTime = 24 * 60 - iCurTime + iStartTime;
    }
    int num = 0;
#endif
#if 0
    ptrTest* pp = new ptrTest(&a1);
    pp->print();
    pp->test();
    pp->print();
#endif
#if 0
    std::filesystem::path p("c:\\windows");
    if (std::filesystem::exists(p))
    {
        if (std::filesystem::is_directory(p))
        {
            std::filesystem::path fi("c:\\DTEN\\Final_1.bin");
            uintmax_t filesize = std::filesystem::file_size(fi);
            return 0;
        }
    }
#endif
#if 0
    HANDLE hThread = (HANDLE)_beginthreadex(nullptr, 0, threadproct, nullptr, 0, NULL);
    DWORD dwRet = WaitForSingleObject(hThread, 3000);
    if (dwRet == WAIT_TIMEOUT)
    {
        TerminateThread(hThread, 0);
        printf("timeout\n");
    }
    else if (dwRet == WAIT_OBJECT_0)
    {
        printf("object 0\n");
    }
#endif // endif
#if 0
    char* src = "123456789";

    int pos = 0;
    while (pos < 9)
    {
        char dest[2] = { 0 };
        memmove_s(dest, 2, src + pos, 2);
        pos += 2;
    }
#endif
#if 0
    std::map<UINT, uint8_t*> mma;
    uint8_t a[] = { 0x1, 0x2 };
    uint8_t b[] = { 0x1, 0x2 };
    mma[0] = a;
    mma[1] = b;
    std::map<UINT, uint8_t*>::iterator it = mma.begin();
    for (; it != mma.end(); ++it)
    {
        UINT F = it->first;
        printf("f=%d", F);
        uint8_t* p = it->second;
        printf("%d", *p++);
        printf("%d\n", *p);

        int num = 0;
    }

    HCRYPTPROV hCryptProv;
    bool bRet = ::CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
#endif
#if 0
    IMAGE_DOS_SIGNATURE;
    IMAGE_DOS_HEADER dosHeader;
    IMAGE_NT_HEADERS ntHeader;
    IMAGE_FILE_HEADER fileHeader;
    IMAGE_OPTIONAL_HEADER optionalHeader;
    IMAGE_SECTION_HEADER sectionHeader;
#endif
#if 0
    TIME_ZONE_INFORMATION   tzi;
    GetTimeZoneInformation(&tzi);
    std::wstring   strStandName = tzi.StandardName;

    LANGID LangLCID = 0;
    char GeoData[MAX_PATH] = { 0 };
    GEOID GeoId = 0;
    LangLCID = GetUserDefaultLCID();
    GeoId = GetUserGeoID(GEOCLASS_NATION);
    std::string strGeoData = "";
    if (GetGeoInfoA(GeoId, GEO_ISO2, GeoData, MAX_PATH, LangLCID))
    {
        strGeoData = GeoData;
    }
    printf("LangLCID=%d, GeoId=%d, strGeoData=%s\n", LangLCID, GeoId, strGeoData.c_str());
#endif
#if 0
    char str[] = "abc, 12, de, ff";
    char* buf = nullptr;
    char* pstoken = nullptr;
    pstoken = strtok_s(str, ",", &buf);
    printf("%s\n", pstoken);
    while (pstoken != nullptr)
    {
        pstoken = strtok_s(NULL, ",", &buf);
        string st;
        st.assign(pstoken);
        if (pstoken != nullptr)
            printf("%s\n", pstoken);
    }
#endif
    //EnumWindowStations(WorkStationEnum, 0);
    //EnumDesktops(NULL, DeskEnum, 0);
    //Socket_udp_test();
#if 0
    //CUDPCnt::GetInstance()->run(callback_parse_udp_data);
    //CTCPCnt::GetInstance()->run(callback_parse_udp_data);
    CTCPCnt::GetInstance()->SendData(56336, (void*)"123", 3);
#endif
#if 0
    string sql = "UPDATE HEALTHCHECKCATEGORY_TRACKING SET ErrorId = '%s' WHERE errorId like '%s%%'";
    //string sql = "UPDATE HEALTHCHECKCATEGORY_TRACKING SET amount = %d WHERE ID = %d";
    string strErrorID = "h01230";
    char szCmd[1256];
    string f = strErrorID.substr(0, 1);
    sprintf_s(szCmd, sql.c_str(), strErrorID.c_str(), f.c_str());
    printf("%s\n", szCmd);
#endif
#if 0
    HKEY hk;
    LSTATUS lRet;
    wstring szSubKey = _T("SOFTWARE\\Microsoft\\SkypeRoomSystem");
    //wstring szSubKey = L"SOFTWARE\\Kingsoft";

    if ((lRet = ::RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\TEST", 0, KEY_READ, &hk)) != ERROR_SUCCESS)
    {
        int err = GetLastError();
        return 0;
    }

    wstring szItemName = _T("Oem Tracking");
    TCHAR szItemValue[] = _T("Chinese\0中文\0log和日志");
    //TCHAR szItemValue[] = _T("Chinese\r\n中文");
    if ((lRet = ::RegSetValueEx(hk, szItemName.c_str(), 0, REG_MULTI_SZ, (BYTE*)szItemValue, sizeof(szItemValue))) != ERROR_SUCCESS)
    {
        int err = GetLastError();
        RegCloseKey(hk);
        return 0;
    }
    //RegFlushKey(hk);
    RegCloseKey(hk);
#endif
#if 0
    WCHAR pChValue[] = L"1,2,3,44";
    wchar_t* token = nullptr;
    wchar_t* nexttoken = nullptr;
    const wchar_t* seps = L",";
    token = wcstok_s(pChValue, seps, &nexttoken);
    while (token != nullptr)
    {
        wprintf(L"%s\n", token);
        token = wcstok_s(nullptr, seps, &nexttoken);
    }
#endif
#if 0
    WCHAR szItemValue[] = L"DTAPServices_*.log\0 \
DTEN_DAEMON_PROCESS_*.log\0 \
中文\
abc\0efga";
    int len = sizeof(szItemValue);
    ModifyRegMultiSZ(L"SOFTWARE\\Microsoft\\SkypeRoomSystem", L"Oem-Tracking", szItemValue, sizeof(szItemValue));
    WCHAR szItemValue2[] = L"Chinese\0english\0中文";
    int len2 = sizeof(szItemValue2);
    //ModifyRegMultiSZ(L"SOFTWARE\\TEST", L"item", szItemValue2, sizeof(szItemValue2));
#endif
#if 0
    EnablePrivilege();

    HANDLE hMapFile = nullptr;
    #define BUF_SIZE 256
    TCHAR szName[] = TEXT("MyFileMappingObject");
    char szMsg[] = "Message from first process";
    if (nullptr == hMapFile)
        hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, szName);
    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%d).\n", GetLastError());
        return 1;
    }
    pBuf = (char*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
    if (pBuf == NULL) {
        printf("Could not map view of file (%d).\n",
            GetLastError());
        return 2;
    }
    CopyMemory((PVOID)pBuf, szMsg, strlen(szMsg));
    char* pBuf2 = (char*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
    if (pBuf2 == NULL) {
        printf("Could not map view of file (%d).\n",
            GetLastError());
        return 2;
    }

    CopyMemory((PVOID)pBuf, "1232455", strlen(szMsg));
    char* pBuf3 = (char*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
    if (pBuf3 == NULL) {
        printf("Could not map view of file (%d).\n",
            GetLastError());
        return 2;
    }
    
    CloseHandle(hMapFile);
#endif
#if 0
    std::thread t111([]() {
       
        return 0;
        });
    t111.detach();
    std::thread t1112([](int i) {
        HANDLE hMapFile;
        LPCTSTR pBuf;
        hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, szName);
        if (hMapFile == NULL) {
            printf("Could not open file mapping object (%d).\n", GetLastError());
            return 1;
        }
        pBuf = (LPTSTR)MapViewOfFile(hMapFile, // handle to map object
            FILE_MAP_ALL_ACCESS,  // read/write permission
            0,
            0,
            BUF_SIZE);
        if (pBuf == NULL) {
            printf("Could not map view of file (%d).\n",
                GetLastError());
            return 2;
        }
        MessageBox(NULL, pBuf, TEXT("Process2"), MB_OK);
        UnmapViewOfFile(pBuf);
        CloseHandle(hMapFile);
        return 0;
        });
    t1112.detach();
#endif
#if 0
    //getDataFromConsole();
    string result = "111111d\"1234567 89\"ns_netd000000";
    UINT nPosStart = result.find_first_of("\"");
    UINT nPosEnd = result.find_last_of("\"");
    if (nPosStart == std::string::npos || nPosEnd == std::string::npos)
    {
        
        return 0;
    }


    string dten_sn = result.substr(nPosStart+1, nPosEnd-nPosStart-1);

    wstring wlen = L"123";
    int len = wlen.length();
    int num = 0;
#endif
#if 0
    uint8_t buffer_0[12] = { 0 };
    uint8_t buffer_1[12] = { 0 };
    add_UVCHeader(buffer_0, false);
    add_UVCHeader(buffer_1, true);
    fcall f;
    printf("%d\n", f.fun1(print, 5));
#endif
#if 0
    {
        int nRet = 0;
        char szParam[1024] = { 0 };
        sprintf_s(szParam, 1024 - 1, "%s %s", "C:\\DTEN\\HardWare\\Driver\\devcon64.exe", "rescan");
        nRet = system(szParam);
        printf("devcon rescan done 0\n");
        Sleep(2000);
        printf("devcon update\n");
        memset(szParam, 0, sizeof(szParam));
        string strTemp = "\"USB\\VID_351E&PID_00C9\"";
        sprintf_s(szParam, 1024 - 1, "%s %s %s %s", "C:\\DTEN\\HardWare\\Driver\\devcon64.exe", "update", "C:\\DTEN\\HardWare\\Driver\\dtensmart\\MutCamera.inf", strTemp.c_str());
        printf("cmd param:[%s]\n", szParam);
        nRet = system(szParam);
        printf("install drv done, nRet:[%d], err=%d\n", nRet, GetLastError());
        memset(szParam, 0, sizeof(szParam));
        sprintf_s(szParam, 1024 - 1, "%s %s", "C:\\DTEN\\HardWare\\Driver\\devcon64.exe", "rescan");
        system(szParam);
        printf("devcon rescan done 1\n");
        Sleep(2000);
    }
#endif
#if 0
    //char* endptr = nullptr;
    //int _8 = strtol("08", &endptr, 16);
    std::wstring info;
    GetDeviDriverInfo(L"USB\\VID_351E&PID_00CF", info);
#endif
#if 0
    FILETIME FileDate = { 0 };
    SYSTEMTIME tm = { 0 };
    ULARGE_INTEGER uDrvTimeStamp;
    swscanf_s(L"1-5-2023", _T("%hu-%hu-%hu"), &tm.wMonth, &tm.wDay, &tm.wYear);
    SystemTimeToFileTime(&tm, &FileDate);
    uDrvTimeStamp.HighPart = FileDate.dwHighDateTime;
    uDrvTimeStamp.LowPart = FileDate.dwLowDateTime;
#endif
#if 0
    CAtlString strBinary = CREG::ReadRegBinaryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Class\\{36fc9e60-c465-11cf-8056-444553540000}\\0030", L"DriverDateData");
    ULONGLONG StampTime = CREG::ReadRegBinaryForSysTime(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Class\\{36fc9e60-c465-11cf-8056-444553540000}\\0030", L"DriverDateData");
#endif
#if 0
    ByForce(g_need);
#endif
    //testFactory();
    //decorator();
    //observerTest();
#if 0
    string strtemp1 = "111;;222";
    string strtemp2;
    string strtemp3;
    ParseUrlAndMd5(strtemp1, strtemp2, strtemp3);
    ULONG U1 = 0;
    ULONG U2 = 2;
    SET_COMMAND(U1, U2);
#endif
#if 0
    {
        MyClass obj1(0), obj2(9);
        MyClass obj3;
        obj3 = obj1;    		//对象obj3已经创建，所以调用复制拷贝构造
    }
    {
        MyClass obj1(1), obj2(2);
        MyClass obj3 = obj1;    //对象obj3还没有创建，所以调用拷贝构造
        system("pause");
        return 0;
    }
#endif

#if 0
    GUID HidGuid;
    HidD_GetHidGuid(&HidGuid);
    getalldevice((LPGUID)&HidGuid, NULL);
    printf("======================\n\n");

    const GUID ImageClassGuid = { 0x6bdd1fc6L, 0x810f, 0x11d0,	{ 0xbe, 0xc7, 0x08, 0x00, 0x2b, 0xe2, 0x09, 0x2f } };
    getalldevice((LPGUID)&ImageClassGuid, NULL);
#endif
    //bool bRet = CUtils::blCheckUdpPortListen(51452);
#if 0
    std::thread tCpu1([]() {
        while (true)
        {
            //CCPU::testCPUUsage();
            Sleep(3000);
            //printf("\n");
        }
    });
    tCpu1.detach();

    std::thread tCpu2([]() {
        //CCPU::getCpuUsage();
    });
    tCpu2.detach();
#endif
#if 0
#define FLAG_REV_ "REV_"
    string strhwid = "2333&Rev_8099";
    size_t nPost = strhwid.find("Rev_");
    string strRev = strhwid.substr(nPost + string(FLAG_REV_).length(), 14);
    string str = strhwid.substr(nPost + string(FLAG_REV_).length()+1, 1);
#endif
    //CUtils::ModifyFileExtension(L"f:\\log\\", L"*.csv", L".log");
#if 0
    //删除section所有数据
    BOOL br = WritePrivateProfileSection(L"section", 0, L"f:\\a.ini");
    //删除section下所有键值对，保留section项
    br = WritePrivateProfileSection(L"section", L"", L"f:\\a.ini");
#endif
#if 0
    connectwlan();
    //Wlan_GetAvailableNetworkList();
    //test_wifi();
#endif
#if 0
    while (true)
    {
        std::call_once(g_once_flag, test_once, 1);
        Sleep(2000);
    }
#endif
#if 0
    DWORD recvThreadId = -1;
    HANDLE m_recvThreadHandle = CreateThread(NULL, 0, ProcessRecvMsgThread, 0, 0, &recvThreadId);
    //CloseHandle(m_recvThreadHandle);
    // 创建处理数据线程
    DWORD sendThreadId = -1;
    HANDLE m_sendThreadHandle = CreateThread(NULL, 0, ProcessRecvMsgThread, 0, 0, &sendThreadId);
    //CloseHandle(m_sendThreadHandle);
    HANDLE hThreadHandle[2] = { m_sendThreadHandle, m_recvThreadHandle };
    DWORD dw = WaitForMultipleObjects(2, hThreadHandle, true, 3000);
#endif
#if 0
    TCHAR FullPath[MAX_PATH] = { 0 };
    GetModuleFileName(0, FullPath, MAX_PATH);
    ::PathRemoveExtension(FullPath);
    wstring curPath = FullPath;
#endif
#if 0
    string strT = teststr();
    char szVer[128] = { 0 };
    GetTouchVerEx("HID\VID_351E&PID_1194&REV_8110&MI_00&Col02", szVer, 128);
#endif
    //DeleteReg(L"SYSTEM\\CurrentControlSet\\Control\\DTEN", L"tp_detect");
#if 0
    ShellExecuteA(NULL, NULL, "notepad.exe", NULL, NULL, SW_SHOWMAXIMIZED);
    Sleep(1500);
    HWND pWnd = FindWindowA(NULL, "无标题 - 记事本");
    if (pWnd)
    {
        LONG dx = 112 * (65535 / 1920);
        LONG dy = 982 * (65535 / 1080);
        SetForegroundWindow(pWnd);
        INPUT m_InPut[2] = { 0 };
        m_InPut[0].type = m_InPut[1].type = INPUT_MOUSE;
        m_InPut[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
        m_InPut[0].mi.dx = m_InPut[1].mi.dx = dx;
        m_InPut[0].mi.dy = m_InPut[1].mi.dy = dy;
        m_InPut[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
        SendInput(sizeof(m_InPut) / sizeof(m_InPut[0]), m_InPut, sizeof(INPUT));
    }
#endif
#if 0
    int index = 0;
    while (1)
    {
        //\\?\DISPLAY#AUO203D#4&3754407d&0&UID8388688#{e6f07b5f-ee97-4a90-b076-33f57bf4eaa7}
        DISPLAY_DEVICEA pDev;
        ZeroMemory(&pDev, sizeof(DISPLAY_DEVICE));
        pDev.cb = sizeof(DISPLAY_DEVICE);
        if (!EnumDisplayDevicesA("\\\\.\\DISPLAY1", index, &pDev, EDD_GET_DEVICE_INTERFACE_NAME))
        {
            break;
        }
        if ((pDev.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) == DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)
        {
            //0x000000dc4b3afa18 L"PCI\\VEN_8086&DEV_9A49&SUBSYS_3F1917AA&REV_01"
            printf("%s\n", pDev.DeviceID);
        }
        else
        {
            printf("\\\\\n");
        }
        index++;
    }
#endif
#if 0
    EnumDisplayMonitors(NULL, NULL, Monitorenumproc1, 0);
    //ListDeviceInstancePath(L"Monitor");
#endif

    system("pause");
	return 0;
}
