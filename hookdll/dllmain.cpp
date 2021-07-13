// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
//#include "hookdll.h"
HINSTANCE g_hmoudle = NULL;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    g_hmoudle = (HINSTANCE)hModule;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
        //MessageBox(NULL, 0, 0, MB_OK);
        //EnableHook();
        //break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		//MessageBox(NULL, 0, 0, MB_OK);
		break;
	}
	return TRUE;
}

