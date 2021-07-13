// hookdll.cpp : 定义 DLL 应用程序的导出函数。
//
//全局键盘钩子注入库实现
#include "stdafx.h"
#define EXPORTFLAG
#include "hookdll.h"
#include "stdlib.h"
extern HINSTANCE g_hmoudle;
//HHOOK hook = NULL;

//VK_MENU 代表alt键
void SendVirtualKey()
{
	//MessageBox(NULL, L"win+alt+r", L"send", MB_OK);
    INPUT input[6];
    memset(input, 0, sizeof(input));


    input[0].type = input[1].type = input[2].type = 
    input[3].type = input[4].type = input[5].type = INPUT_KEYBOARD;  //设置键盘模式  

    //模拟win+D
    //input[0].ki.wVk = input[3].ki.wVk = VK_LWIN;
    //input[1].ki.wVk = input[2].ki.wVk = 'D';

    //模拟atl+D
//     input[0].ki.wVk = input[3].ki.wVk = VK_MENU;
//     input[1].ki.wVk = input[2].ki.wVk = 'D';
//     input[2].ki.dwFlags = input[3].ki.dwFlags = KEYEVENTF_KEYUP;

    //模拟ctrl+alt+A
    /*input[0].ki.wVk = input[5].ki.wVk = VK_CONTROL;
    input[1].ki.wVk = input[4].ki.wVk = VK_MENU;
    input[2].ki.wVk = input[3].ki.wVk = 'A';
    input[3].ki.dwFlags = input[4].ki.dwFlags = input[5].ki.dwFlags = KEYEVENTF_KEYUP;*/

	//win+alt+r
	input[0].ki.wVk = input[5].ki.wVk = VK_LWIN;
	input[1].ki.wVk = input[4].ki.wVk = VK_MENU;
	input[2].ki.wVk = input[3].ki.wVk = 'R';
	input[3].ki.dwFlags = input[4].ki.dwFlags = input[5].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(6, input, sizeof(INPUT));
}


void recordscreen()
{
	INPUT input[6];
	memset(input, 0, sizeof(input));
	//win+alt+R
	input[0].type = input[1].type = input[2].type =
		input[3].type = input[4].type = input[5].type = INPUT_KEYBOARD;
	input[0].ki.wVk = input[5].ki.wVk = VK_LWIN;
	input[1].ki.wVk = input[4].ki.wVk = VK_MENU;
	input[2].ki.wVk = input[3].ki.wVk = 'R';
	input[3].ki.dwFlags = input[4].ki.dwFlags = input[5].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(6, input, sizeof(INPUT));
}

DWORD g_Time1 = 0;
DWORD g_Time2 = 0;
LRESULT CALLBACK hookproc_ll(int nCode, WPARAM wParam, LPARAM lParam)
{
    PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
    if (nCode == HC_ACTION)
    {
        int vKey = LOBYTE(p->vkCode);
		char buffer[10] = { 0 };
		_itoa_s(vKey, buffer, 10);
		//MessageBoxA(NULL, buffer, 0, MB_OK);
        //如果为键盘消息
		
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)   //只响应一次消息
        {
            switch (vKey)
            {
            case 'd':
            case 'D':
            {
                //如果用户按下了ctrl + q键盘消息
                if (::GetKeyState(VK_LWIN) < 0)
                {
                    MessageBox(NULL, L"lWin+d", L"ok", MB_OK);
                }
            }
            break;
            case 0x70:  //F1+shift+ctrl
            {
                if (::GetKeyState(VK_CONTROL) < 0 && ::GetKeyState(VK_SHIFT) < 0)
                {
					//g_Time = GetTickCount();
                    //MessageBox(NULL, L"shift+ctrl+f1", L"ok", MB_OK);
                }
            }
            break;
            case VK_F22:    //F22+shift+ctrl
            {
                if (::GetKeyState(VK_CONTROL) < 0 && ::GetKeyState(VK_SHIFT) < 0)
                {
                    MessageBox(NULL, L"shift+ctrl+f22", L"down", MB_OK);
					//recordscreen();
					g_Time2 = GetTickCount();
                }
				else
				{
					g_Time1 = GetTickCount();
					MessageBox(NULL, L"f22", L"down", MB_OK);
				}
            }
            break;
            }
        }
		else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
		{
			switch (vKey)
			{
			case VK_F22:  //F1+shift+ctrl
			{
				if (::GetKeyState(VK_CONTROL) < 0 && ::GetKeyState(VK_SHIFT) < 0)
				{
					g_Time2 = GetTickCount() - g_Time2;
					char buffer1[1001] = { 0 };
					_itoa_s(g_Time1, buffer1, 10);
					char buffer2[100] = { 0 };
					_itoa_s(g_Time2, buffer2, 10);
					MessageBoxA(NULL, buffer2, buffer1, MB_OK);
				}
				else
				{
					g_Time1 = GetTickCount() - g_Time1;
					MessageBox(NULL, L"f22", L"up", MB_OK);
				}
			}
			break;
			case 0x70:  //F1+shift+ctrl
			{
				if (::GetKeyState(VK_CONTROL) < 0 && ::GetKeyState(VK_SHIFT) < 0)
				{
					//g_Time = GetTickCount();
					MessageBox(NULL, L"shift+ctrl+f1", L"up", MB_OK);
				}
				else
				{
					MessageBox(NULL, L"f1", L"up", MB_OK);
				}
			}
			break;
			}		 
		}
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK hookproc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (((DWORD)lParam & 0x40000000) && (HC_ACTION == nCode)) //有键按下
    {      
        if ((wParam == VK_SPACE) || (wParam == VK_RETURN)) {
            SendVirtualKey();
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

EXPORTFUNC void EnableHook()
{
    //HHOOK hook = SetWindowsHookEx(WH_KEYBOARD, hookproc, g_hmoudle, 0);
    HHOOK hook_ll = SetWindowsHookEx(WH_KEYBOARD_LL, hookproc_ll, g_hmoudle, 0);
    if (/*NULL == hook || */NULL == hook_ll)
    {
        MessageBox(NULL, 0, 0, MB_OK);
    }
}