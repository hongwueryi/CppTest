#include "stdafx.h"
#include "Resource.h"
#include "FontManager.h"
#include "WinReg.hpp"
#include <ShlObj.h>
#include <thread>
#include <mutex>

using namespace std;
using namespace winreg;
#define USE_THREAD
mutex g_mutex;
condition_variable g_condition;
#define TIMEOUT_COUNT 5000
#define REG_PATH_FONT L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts"

LOGFONTEX g_logFont;
extern HWND g_hWnd;

CFontManger*CFontManger::Getinstance()
{
	static CFontManger pFont;
	return &pFont;
}

void CFontManger::GetActualFont()
{
	m_metricsAll.cbSize = sizeof(NONCLIENTMETRICS);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &m_metricsAll, 0);
	SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LOGFONT), &m_iconFontAll, 0);
	m_metricsAll.lfStatusFont = m_metricsAll.lfMenuFont;
	m_metricsAll.lfMessageFont = m_metricsAll.lfMenuFont;
	m_metricsAll.lfCaptionFont = m_metricsAll.lfMenuFont;
	m_metricsAll.lfSmCaptionFont = m_metricsAll.lfMenuFont;
	m_iconFontAll = m_metricsAll.lfMenuFont;
}

bool CFontManger::BackUpDefaultFontInfo()
{
	//¼ÆËã»ú\HKEY_CURRENT_USER\Control Panel\Desktop\WindowMetrics
	RegKey reg;
	RegKey regDest;
	RegResult result = regDest.TryOpen(HKEY_CURRENT_USER,
		L"Control Panel\\Desktop\\WindowMetrics_copy", KEY_ALL_ACCESS | KEY_WOW64_64KEY);
	if (result.IsOk())
		return true;

	LOGINFO(L"begin to backup windows default font metrics...");
	result = reg.TryOpen(HKEY_CURRENT_USER,
		L"Control Panel\\Desktop\\WindowMetrics", KEY_ALL_ACCESS | KEY_WOW64_64KEY);
	if (result.Failed())
	{
		LOGINFO(L"try open default fontinfo regedit failed.");
		return false;
	}

	result = regDest.TryCreate(HKEY_CURRENT_USER,
		L"Control Panel\\Desktop\\WindowMetrics_copy", KEY_ALL_ACCESS | KEY_WOW64_64KEY);
	if (result.Failed())
	{
		LOGINFO(L"try backup default font info to regedit failed.");
		return false;
	}
	
	result = reg.TryCopyTree(L"", regDest);
	if (result.Failed())
	{
		LOGINFO(L"try copy default font info failed.");
		return false;
	}

	return true;
}

bool CFontManger::installFont(CString FontFile, CString fontName)
{
	CString strPath;
	TCHAR* szBuffer = strPath.GetBuffer(MAX_PATH + 1);
	::GetModuleFileName(NULL, szBuffer, MAX_PATH);
	strPath.ReleaseBuffer();
	int nFind = strPath.ReverseFind('\\');
	CString FontPath = strPath.Left(nFind + 1);
	FontPath += FontFile;
	if (!::PathFileExists(FontPath))
	{
		CString strLog;
		strLog.Format(L"there are not exist source font file(%s).", FontPath);
		LOGINFO(strLog);
		return false;
	}

	CString destPath;
	::SHGetSpecialFolderPath(NULL, destPath.GetBuffer(MAX_PATH), CSIDL_WINDOWS, false);
	destPath.ReleaseBuffer();
	destPath += L"\\Fonts\\";
	destPath += FontFile;
	BOOL bRet = ::CopyFile(FontPath, destPath, FALSE);
	if (!::PathFileExists(destPath))
	{
		CString strLog;
		strLog.Format(L"Copy font file to destPath(%s) failed.err=%d.", destPath, GetLastError());
		LOGINFO(strLog);
		return false;
	}
	
	if (0 == AddFontResource(destPath))
	{
		CString strLog;
		strLog.Format(L"AddFontResource failed.err=%d.", GetLastError());
		LOGINFO(strLog);
	}

	RegKey reg;
	RegResult result = reg.TryOpen(HKEY_LOCAL_MACHINE, REG_PATH_FONT);
	if (result.Failed())
	{
		LOGINFO(L"try open regedit of windows font failed.");
		return false;
	}
		
	reg.TrySetStringValue(fontName.GetBuffer(), FontFile.GetBuffer());
	if (result.Failed())
	{
		LOGINFO(L"try add new font to regedit failed.");
		return false;
	}
		
	return true;
}

void CFontManger::GetFontMerics(LOGFONT font, NONCLIENTMETRICS& fontMetrics)
{
	fontMetrics.cbSize = sizeof(NONCLIENTMETRICS);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &fontMetrics, 0);
	fontMetrics.lfStatusFont = font;
	fontMetrics.lfMessageFont = font;
	fontMetrics.lfCaptionFont = font;
	fontMetrics.lfSmCaptionFont = font;
	fontMetrics.lfMenuFont = font;
}

INT CALLBACK NEnumFontNameProc(LOGFONT *plf, TEXTMETRIC* /*ptm*/, INT /*nFontType*/, LPARAM lParam/**/)
{
	wchar_t* sysFonts = (wchar_t*) lParam;
	if (sysFonts != NULL)
	{
		//_tLOGINFO(LL"%s\n", plf->lfFaceName);
		if (0 == wcscmp(sysFonts, plf->lfFaceName))
		{
			g_logFont.result = true;
			g_logFont.font = *plf;
			return FALSE;
		}
	}

	return TRUE;
}

void CFontManger::GetSpecifiedFontInfos(wchar_t* lfFaceName, LONG lfhight)
{
	g_logFont.result = false;
	HDC hdc = ::GetDC(nullptr);
	::EnumFontFamilies(hdc, (LPTSTR)NULL, (FONTENUMPROC)NEnumFontNameProc, (LPARAM)lfFaceName);
	if (g_logFont.result)
	{
		//1pt=1/72Ó¢´ç
		g_logFont.result = true;
		g_logFont.font.lfHeight = -MulDiv(lfhight, GetDeviceCaps(hdc, LOGPIXELSY), 72);
		g_logFont.font.lfWidth = 0;
	}
	::ReleaseDC(nullptr, hdc);
}

UINT WINAPI tTitleFontProc(void* param)
{
	LOGFONT* font = (LOGFONT*)param;
	if (nullptr == font)
		return 0;
	DWORD_PTR ptr;
	LRESULT messageResult;
	SystemParametersInfo(SPI_SETICONTITLELOGFONT,
		sizeof(LOGFONT),
		font,
		SPIF_UPDATEINIFILE);
	return 0;
}

UINT WINAPI tClientFontProc(void* param)
{
	DWORD_PTR ptr;
	LRESULT messageResult;
	NONCLIENTMETRICS* fontMetrics = (NONCLIENTMETRICS*)param;
	SystemParametersInfo(SPI_SETNONCLIENTMETRICS,
		sizeof(NONCLIENTMETRICS),
		&fontMetrics,
		SPIF_UPDATEINIFILE);
	return 0;
}

bool CFontManger::SetDefaultFont(wchar_t* lfFaceName, LONG lfhight)
{
	LOGINFO(L"begin to recover to default font...");
	LOGFONT font;
	if (!g_logFont.result)
	{
		CFontManger::Getinstance()->GetSpecifiedFontInfos(lfFaceName, lfhight);
		if (!g_logFont.result)
		{
			LOGINFO(L"get default font failed...");
			return false;
		}
	}
	
	font = g_logFont.font;
	HDC hdc = ::GetDC(nullptr);
	wcscpy_s(font.lfFaceName, 32, lfFaceName);
	font.lfHeight = -MulDiv(lfhight, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	DWORD_PTR ptr;
	LRESULT messageResult;
#ifdef USE_THREAD
	HANDLE tHandle = (HANDLE)_beginthreadex(nullptr, 0, tTitleFontProc, &font, 0, nullptr);
	DWORD waitResult = WaitForSingleObject(tHandle, 3000);
	if (waitResult == WAIT_TIMEOUT)
		TerminateThread(tHandle, 0);
	CloseHandle(tHandle);
#else
	SystemParametersInfo(SPI_SETICONTITLELOGFONT,
		sizeof(LOGFONT),
		&font,
		SPIF_UPDATEINIFILE);
#endif
	messageResult = SendMessageTimeout(
		HWND_BROADCAST,
		WM_SETTINGCHANGE,
		SPI_SETICONTITLELOGFONT,
		0,
		SMTO_ABORTIFHUNG,
		TIMEOUT_COUNT,
		&ptr);
	if (messageResult == 0) {
		if (GetLastError() == ERROR_TIMEOUT) {
			LOGINFO(L"SendMessage SPI_SETICONTITLELOGFONT timeout.");
		}
	}

	NONCLIENTMETRICS fontMetrics;
	GetFontMerics(font, fontMetrics); 
#ifdef USE_THREAD
	tHandle = (HANDLE)_beginthreadex(nullptr, 0, tClientFontProc, &fontMetrics, 0, nullptr);
	waitResult = WaitForSingleObject(tHandle, 3000);
	if (waitResult == WAIT_TIMEOUT)
		TerminateThread(tHandle, 0);
	CloseHandle(tHandle);
#else
	SystemParametersInfo(SPI_SETNONCLIENTMETRICS,
		sizeof(NONCLIENTMETRICS),
		&fontMetrics,
		SPIF_UPDATEINIFILE);
#endif
	messageResult = SendMessageTimeout(
		HWND_BROADCAST,
		WM_SETTINGCHANGE,
		SPI_SETNONCLIENTMETRICS,
		(LPARAM)_T("WindowMetrics"),
		SMTO_ABORTIFHUNG,
		TIMEOUT_COUNT,
		&ptr);
	if (messageResult == 0) {
		if (GetLastError() == ERROR_TIMEOUT) {
			LOGINFO(L"SendMessage SPI_SETNONCLIENTMETRICS timeout.");
		}
	}

	::ReleaseDC(nullptr, hdc);
	LOGINFO(L"Recover defaut font sucessed!");
	return true;
}

bool CFontManger::SetSpecifiedFont(CString FontFile, wchar_t* lfFaceName, LONG lfhight)
{
	CFontManger::Getinstance()->GetSpecifiedFontInfos(lfFaceName, lfhight);
 	if (!g_logFont.result)
 	{
		LOGINFO(L"begin to install font...\n");
		if (!CFontManger::Getinstance()->installFont(FontFile, lfFaceName))
		{
			LOGINFO(L"Install font failed.\n");
			return false;
		}
		else
		{
			CFontManger::Getinstance()->GetSpecifiedFontInfos(lfFaceName, lfhight);
			if (!g_logFont.result)
			{
				LOGINFO(L"The font is not recognized.");
				return false;
			}
		}
	}
	LOGINFO(L"begin to modify specified font...");

#ifdef USE_THREAD
	HANDLE tHandle = (HANDLE)_beginthreadex(nullptr, 0, tTitleFontProc, &g_logFont.font, 0, nullptr);
	DWORD waitResult = WaitForSingleObject(tHandle, 3000);
	if (waitResult == WAIT_TIMEOUT)
		TerminateThread(tHandle, 0);
	CloseHandle(tHandle);
#else
	SystemParametersInfo(SPI_SETICONTITLELOGFONT,
		sizeof(LOGFONT),
		&g_logFont.font,
		SPIF_UPDATEINIFILE);
#endif
	DWORD_PTR ptr;
	LRESULT messageResult = SendMessageTimeout(
		HWND_BROADCAST,
		WM_SETTINGCHANGE,
		SPI_SETICONTITLELOGFONT,
		0,
		SMTO_ABORTIFHUNG,
		TIMEOUT_COUNT,
		&ptr);
	if (messageResult == 0) {
		if (GetLastError() == ERROR_TIMEOUT) {
			LOGINFO(L"SendMessage SPI_SETICONTITLELOGFONT timeout.");
		}
	}

	NONCLIENTMETRICS fontMetrics;
	GetFontMerics(g_logFont.font, fontMetrics);
#if 0
	tHandle = (HANDLE)_beginthreadex(nullptr, 0, tClientFontProc, &fontMetrics, 0, nullptr);
	waitResult = WaitForSingleObject(tHandle, 3000);
	if (waitResult == WAIT_TIMEOUT)
		TerminateThread(tHandle, 0);
	CloseHandle(tHandle);
#else
	SystemParametersInfo(SPI_SETNONCLIENTMETRICS,
		sizeof(NONCLIENTMETRICS),
		&fontMetrics,
		SPIF_UPDATEINIFILE);
#endif
	messageResult = SendMessageTimeout(
		HWND_BROADCAST,
		WM_SETTINGCHANGE,
		SPI_SETNONCLIENTMETRICS,
		(LPARAM)_T("WindowMetrics"),
		SMTO_ABORTIFHUNG,
		TIMEOUT_COUNT,
		&ptr);
	if (messageResult == 0) {
		if (GetLastError() == ERROR_TIMEOUT) {
			LOGINFO(L"SendMessage SPI_SETNONCLIENTMETRICS timeout.");
		}
	}

	return true;
}

void CFontManger::LOGINFO(CString info)
{
	wchar_t buffer[1024] = { 0 };
	int sz = GetDlgItemText(g_hWnd, IDC_LOG, buffer, 1024);
	CString strBuffer = buffer;
	CString log;
	if (!strBuffer.IsEmpty())
		log = (strBuffer + L"\r\n");
	log += info;
	SetDlgItemText(g_hWnd, IDC_LOG, log);
}
