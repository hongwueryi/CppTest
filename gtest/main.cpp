#include "gtest/gtest.h"
#include <windows.h>
#include <atlstr.h>

BOOL AddEnvironmentVariable(const ATL::CStringW path)
{
	if (path.IsEmpty())
		return FALSE;
	DWORD length = GetEnvironmentVariableW(L"PATH", NULL, NULL);
	if (0 == length)
		return FALSE;

	length++;
	wchar_t* enviromentPath = new wchar_t[length];
	::ZeroMemory(enviromentPath, length * sizeof(wchar_t));

	::GetEnvironmentVariableW(L"PATH", enviromentPath, length);
	ATL::CStringW myPath = path + L";" + enviromentPath;
	delete[] enviromentPath;
	return ::SetEnvironmentVariableW(L"PATH", myPath);
}


class MyEnviroment : public testing::Environment{
public:
	virtual void SetUp()
	{
		//添加自身的环境变量
		EXPECT_TRUE(AddEnvironmentVariable(L"")) << "添加环境变量失败";
	}
};
int main(int argc, char*argv[])
{
	testing::AddGlobalTestEnvironment(new MyEnviroment);
	testing::InitGoogleTest(&argc, argv);
	int iRet = RUN_ALL_TESTS();
	getchar();
	return iRet;
}