// FontTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "FontManager.h"


bool fontTest(CString FontFile, CString fontName, LONG fontsize)
{
	printf("begin to backup windows default font metrics...\n");
	if (!CFontManger::Getinstance()->BackUpDefaultFontInfo())
	{
		printf("backup default fontinfo failed.\n");
	}

// 	printf("begin to install font...\n");
// 	if (!CFontManger::Getinstance()->installFont(FontFile, fontName))
// 	{
// 		printf("Install font failed.\n");
// 		return false;
// 	}
//	printf("begin to modify specified font...\n");

	if (!CFontManger::Getinstance()->SetSpecifiedFont(FontFile, fontName.GetBuffer(), fontsize))
	{
		printf("set specified font failed.\n");
		return false;
	}

	printf("set specified font sucessed!\n");
	return true;
}

int main()
{
	fontTest(L"Oz焦糖下午茶.ttf", L"Oz焦糖下午茶", 11);
	system("pause");
    return 0;
}

