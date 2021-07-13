#include "stdafx.h"
#include "FontManager.h"
#include "WinReg.hpp"
#include <ShlObj.h>
using namespace std;
using namespace winreg;
#define TIMEOUT_COUNT 5000
#define REG_PATH_FONT L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts"

LOGFONTEX g_logFont;

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

	result = reg.TryOpen(HKEY_CURRENT_USER,
		L"Control Panel\\Desktop\\WindowMetrics", KEY_ALL_ACCESS | KEY_WOW64_64KEY);
	if (result.Failed())
	{
		printf("try open default fontinfo regedit failed.\n");
		return false;
	}

	result = regDest.TryCreate(HKEY_CURRENT_USER,
		L"Control Panel\\Desktop\\WindowMetrics_copy", KEY_ALL_ACCESS | KEY_WOW64_64KEY);
	if (result.Failed())
	{
		printf("try backup default font info to regedit failed.\n");
		return false;
	}
	
	result = reg.TryCopyTree(L"", regDest);
	if (result.Failed())
	{
		printf("try copy default font info failed.\n");
		return false;
	}

	return true;
}

bool CFontManger::installFont(CString FontFile, CString fontName)
{
	ATL::CString strPath;
	TCHAR* szBuffer = strPath.GetBuffer(MAX_PATH + 1);
	::GetModuleFileName(NULL, szBuffer, MAX_PATH);
	strPath.ReleaseBuffer();
	int nFind = strPath.ReverseFind('\\');
	CString FontPath = strPath.Left(nFind + 1);
	FontPath += FontFile;
	if (!::PathFileExists(FontPath))
	{
		printf("there are not exist source font file(%s).\n", FontPath);
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
		printf("Copy font file to destPath failed.\n");
		return false;
	}
	
	if (0 == AddFontResource(destPath))
	{
		printf("AddFontResource failed.err=%d\n", GetLastError());
	}

	RegKey reg;
	RegResult result = reg.TryOpen(HKEY_LOCAL_MACHINE, REG_PATH_FONT);
	if (result.Failed())
	{
		printf("try open regedit of windows font failed.\n");
		return false;
	}
		
	reg.TrySetStringValue(fontName.GetBuffer(), FontFile.GetBuffer());
	if (result.Failed())
	{
		printf("try add new font to regedit failed.\n");
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
		//_tprintf(L"%s\n", plf->lfFaceName);
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

bool CFontManger::SetSpecifiedFont(CString FontFile, wchar_t* lfFaceName, LONG lfhight)
{
	CFontManger::Getinstance()->GetSpecifiedFontInfos(lfFaceName, lfhight);
 	if (!g_logFont.result)
 	{
		printf("begin to install font...\n");
		if (!CFontManger::Getinstance()->installFont(FontFile, lfFaceName))
		{
			printf("Install font failed.\n");
			return false;
		}
		else
		{
			CFontManger::Getinstance()->GetSpecifiedFontInfos(lfFaceName, lfhight);
			if (!g_logFont.result)
			{
				printf("The font is not recognized.\n");
				return false;
			}
		}
	}
	
	printf("begin to modify specified font...\n");
	DWORD_PTR ptr;
	LRESULT messageResult;
	SystemParametersInfo(SPI_SETICONTITLELOGFONT,
		sizeof(LOGFONT),
		&g_logFont.font,
		SPIF_UPDATEINIFILE);
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
			printf("SendMessage SPI_SETICONTITLELOGFONT timeout.\n");
		}
	}

	NONCLIENTMETRICS fontMetrics;
	GetFontMerics(g_logFont.font, fontMetrics);
	SystemParametersInfo(SPI_SETNONCLIENTMETRICS,
		sizeof(NONCLIENTMETRICS),
		&fontMetrics,
		SPIF_UPDATEINIFILE);
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
			printf("SendMessage SPI_SETNONCLIENTMETRICS timeout\n");
		}
	}

	return true;
}