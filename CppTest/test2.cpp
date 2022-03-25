#include <stdlib.h>
#include "udp.h"
#include <thread>
#include <string>
#include <map>
#include "ExceptionReport.h"
#include <vector>
#include <string>
#include <tchar.h>
#include "udpprxoy.h"

using namespace std;

BOOL ModifyRegMultiSZ(LPCWSTR lpKeyPath, LPCWSTR lpItem, LPCTSTR dwValue, int len)
{
    HKEY hKey = NULL, hSubKey = NULL;
    DWORD dwResOpen = 0;
    BOOL bRet = TRUE;

#if 1
    if (ERROR_SUCCESS != RegCreateKeyEx(HKEY_LOCAL_MACHINE,
        lpKeyPath,
        NULL,
        NULL,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
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

	wstring wstr = L"";
	DWORD dwType, dwSize;
	vector<wstring> vec;
    // 获取类型、长度
    if (RegQueryValueEx(hKey, lpItem, NULL, &dwType, NULL, &dwSize) != ERROR_SUCCESS)
    {
        goto toerr;
    }
	TCHAR* pChValue = new TCHAR[dwSize + 1]{ 0 };
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

int main()
{
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
		memmove_s(dest, 2, src+pos, 2);
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
	while (pstoken != nullptr )
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
	CUDPCnt::GetInstance()->run(callback_parse_udp_data);
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
#if 1
    WCHAR szItemValue[] = L"Chinese\0english\0中文";
    int len = sizeof(szItemValue);
	ModifyRegMultiSZ(L"SOFTWARE\\TEST", L"item", szItemValue, sizeof(szItemValue));
#endif

	return 0;
}