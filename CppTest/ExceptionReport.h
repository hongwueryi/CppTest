
#pragma once
#pragma message("Using include dir's ExceptionReport")
#ifndef RSExecptionTString
#include <string>
typedef std::basic_string<TCHAR> RSExecptionTString;
#endif

class CExceptionReport
{
public:
	CExceptionReport();
	~CExceptionReport();

	static void SetDumpDir(LPCTSTR dir);
	static LONG WINAPI UnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo);

	//是否显示CrashReporter窗口，默认不显示, bigdata 表示是否上报大数据
	static void SetShowReporter(BOOL show, BOOL bigdata = TRUE);
private:

	static const RSExecptionTString FormatCurrentTimeString();

	static bool writeMiniDump(PEXCEPTION_POINTERS pExceptionInfo);

	static void SuspendThreads();


	static LPTOP_LEVEL_EXCEPTION_FILTER m_previousExceptionFilter;
	static TCHAR m_pDmpFileName[MAX_PATH];
	static HANDLE m_hDumpFile;
	static void InvalidParameterHandler(const wchar_t* expression,
		const wchar_t* function, 
		const wchar_t* file, 
		unsigned int line, 
		uintptr_t pReserved);

	
	static BOOL m_bFirstRun;
	static _invalid_parameter_handler s_fnInvalidParameterHandler;
};

#define EXCEPTION_REPORT_INIT(showReporter) CExceptionReport* ex_reporter = new CExceptionReport(); srand(GetTickCount()); ex_reporter->SetShowReporter(showReporter, (rand()%2)==0);





