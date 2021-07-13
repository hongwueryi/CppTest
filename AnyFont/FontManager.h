#pragma once
typedef struct _LOGFONTEX
{
	bool result;
	LOGFONT font;
}LOGFONTEX;

class CFontManger
{
public:
	static CFontManger*Getinstance();

public:
	void GetActualFont();
	void GetFontMerics(LOGFONT font, NONCLIENTMETRICS& fontMetrics);
	void GetSpecifiedFontInfos(wchar_t* lfFaceName, LONG lfhight);
	bool SetSpecifiedFont(CString FontFile, wchar_t* lfFaceName, LONG lfhight);
	bool installFont(CString FontFile, CString fontName);
	bool BackUpDefaultFontInfo();

public:
	bool SetDefaultFont(wchar_t* lfFaceName, LONG lfhight);
	void LOGINFO(CString info);

private:
	CFontManger() {}
	
	NONCLIENTMETRICS m_metricsAll;
	LOGFONT m_iconFontAll;
};
