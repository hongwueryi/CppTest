#include <stdlib.h>
#include "udp.h"
#include <thread>
#include <string>
#include <map>
using namespace std;

void Socket_udp_test()
{
	std::thread tUdp_s([] {
		DtenUdp::GetInstance()->Run();
		});

	std::thread tUdp_c([] {
		DtenUdp::GetInstance()->SendTOServer();
		});
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

#include <filesystem>
int main()
{
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
	system("pause");
	return 0;
}