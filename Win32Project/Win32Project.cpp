// Win32Project.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Win32Project.h"
#include <string>
#define MAX_LOADSTRING 100
#include <thread>

// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HWND hWnd;
void recordscreen()
{
	Sleep(2000);
	INPUT input[6];
	memset(input, 0, sizeof(input));
	//win+alt+R
	input[0].type = input[1].type = input[2].type =
		input[3].type = input[4].type = input[5].type = INPUT_KEYBOARD;
	input[0].ki.wVk = input[5].ki.wVk = VK_LWIN;
	input[1].ki.wVk = input[4].ki.wVk = VK_MENU;
	input[2].ki.wVk = input[3].ki.wVk = 'R';
	input[3].ki.dwFlags = input[4].ki.dwFlags = input[5].ki.dwFlags = KEYEVENTF_KEYUP;
	int err = SendInput(6, input, sizeof(INPUT));
	{
		if (err == 0)
		{
			MessageBoxA(NULL, 0, 0, MB_OK);
		}
	}
}


void recordscreen1()
{
#if 0
	INPUT input[3];
	memset(input, 0, sizeof(input));
	//win+alt+R
	input[0].type = input[1].type = input[2].type = INPUT_KEYBOARD;
	input[0].ki.wVk = VK_LWIN;
	input[1].ki.wVk = VK_MENU;
	input[2].ki.wVk = 'R';
	SendInput(3, input, sizeof(INPUT));
	Sleep(100);
	input[0].ki.dwFlags = input[1].ki.dwFlags = input[2].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(3, input, sizeof(INPUT));
#endif
	Sleep(2000);
	INPUT input[4];
	memset(input, 0, sizeof(input));
	input[0].type = input[1].type = input[2].type = input[3].type = INPUT_KEYBOARD;  //���ü���ģʽ  
	input[0].ki.wVk = input[3].ki.wVk = VK_LWIN;
	input[1].ki.wVk = input[2].ki.wVk = 'D';
	input[2].ki.dwFlags = input[3].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(4, input, sizeof(INPUT));
}

HHOOK hook_ll = NULL;
LRESULT CALLBACK hookproc_ll(int nCode, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
	if (nCode == HC_ACTION)
	{
		int vKey = LOBYTE(p->vkCode);
		char buffer[10] = { 0 };
		_itoa_s(vKey, buffer, 10);
		//MessageBoxA(NULL, buffer, 0, MB_OK);
		//���Ϊ������Ϣ

		if (wParam == WM_KEYDOWN)   //ֻ��Ӧһ����Ϣ
		{
			switch (vKey)
			{
			case 'q':
			case 'Q':
			{
				DestroyWindow(hWnd);
				break;
			}
			case 'd':
			case 'D':
			{
				MessageBox(NULL, L"lWin+d", L"ok", MB_OK);
				//����û�������ctrl + q������Ϣ
				if (::GetKeyState(VK_LWIN) < 0)
				{
					//MessageBox(NULL, L"lWin+d", L"ok", MB_OK);
				}
			}
			break;
			case 0x70:  //F1+shift+ctrl
			{
				if (::GetKeyState(VK_CONTROL) < 0 && ::GetKeyState(VK_SHIFT) < 0)
				{
					MessageBox(NULL, L"shift+ctrl+f1", L"ok", MB_OK);
				}
			}
			break;
			case VK_F22:    //F22+shift+ctrl
			{
				if (::GetKeyState(VK_CONTROL) < 0 && ::GetKeyState(VK_SHIFT) < 0)
				{
					//MessageBox(NULL, L"shift+ctrl+f22", L"ok", MB_OK);
					//PostMessage(hWnd, WM_USER + 1024, 0, 0);
					//Sleep(200);
					//recordscreen();
				}
				else
				{
					//MessageBox(NULL, L"f22", L"ok", MB_OK);
				}
			}
			break;
			default:
				break;
			}
		}
	}

	return CallNextHookEx(hook_ll, nCode, wParam, lParam);
}

int g_alpha = 0;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    std::wstring cmd = lpCmdLine;
    if (cmd.find(L"255") != std::string::npos)
    {
        g_alpha = 255;
    }
	//Sleep(5000);
    // TODO: �ڴ˷��ô��롣
    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
	BOOL bRet = LockSetForegroundWindow(LSFW_LOCK);
#if 0
    typedef void (WINAPI*FUNTEST)();
    HMODULE hModule = LoadLibraryA("hookdll.dll");
    if (NULL == hModule)
    {
        return 0;
    }

    FUNTEST funtest = (FUNTEST)GetProcAddress(hModule, "EnableHook");
    //funtest();
#endif
#if 1
	hook_ll = SetWindowsHookEx(WH_KEYBOARD_LL, hookproc_ll, NULL, 0);
	int num = 0;
	if (NULL == hook_ll)
	{
		num = GetLastError();
	}
#endif
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT));

    MSG msg;

    // ����Ϣѭ��: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      0, 0, 600, 300, nullptr, nullptr, hInstance, nullptr);

//    HWND hWnd2 = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW|WS_CHILD,
// 	   0, 0, 300, 200, hWnd, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, SW_SHOW);
   UpdateWindow(hWnd);
   SetWindowPos(hWnd,
       HWND_TOPMOST,
       0,
	   0,
       1920,
       1080,
       SWP_NOACTIVATE);
//    ShowWindow(hWnd2, SW_SHOW);
//    UpdateWindow(hWnd2);
   LONG nRet = ::GetWindowLong(hWnd, GWL_EXSTYLE);
   nRet = nRet | WS_EX_LAYERED;
   ::SetWindowLong(hWnd, GWL_EXSTYLE, nRet);
   ::SetLayeredWindowAttributes(hWnd, 0, g_alpha, LWA_ALPHA);    // 255���ò�͸��  0����͸��
   std::thread tSend([]() {
       //MessageBox(NULL, 0, 0, MB_OK);
       Sleep(10000);
       LONG dx = 97 * (65535 / 1920);
       LONG dy = 1018 * (65535 / 1080);
       INPUT m_InPut[2] = { 0 };
       m_InPut[0].type = m_InPut[1].type = INPUT_MOUSE;
       m_InPut[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
       m_InPut[0].mi.dx = m_InPut[1].mi.dx = dx;
       m_InPut[0].mi.dy = m_InPut[1].mi.dy = dy;
       m_InPut[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
       SendInput(sizeof(m_InPut) / sizeof(m_InPut[0]), m_InPut, sizeof(INPUT));
       });
   tSend.detach();
   return TRUE;
}
#include <shellapi.h>
//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �����˵�ѡ��: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
	{
		BOOL bRet = LockSetForegroundWindow(LSFW_UNLOCK);
		UnhookWindowsHookEx(hook_ll);
		PostQuitMessage(0);
	}
		
        break;
	case WM_CHAR:
	{
		static int flag = true;
		if (flag)
			//ShellExecute(NULL, L"open", L"H:\\test\\maxwnd.exe", NULL, NULL, SW_SHOW);
		flag = false;
		//MessageBox(NULL, L"WM_CHAR", L"ok", MB_OK);
	}
		//MessageBox(NULL, L"WM_CHAR", L"ok", MB_OK);
		
		break;
	case WM_USER + 1024:
		//MessageBox(NULL, L"shift+ctrl+f22", L"ok", MB_OK);
		recordscreen();
		break;
	case WM_DPICHANGED:
	{
		int dpi = HIWORD(wParam);
		int low = LOWORD(wParam);
		//UpdateDpiDependentFontsAndResources();
		RECT* const prcNewWindow = (RECT*)lParam;
		int w = prcNewWindow->right - prcNewWindow->left;
		int h = prcNewWindow->bottom - prcNewWindow->top;
		SetWindowPos(hWnd,
			HWND_TOPMOST,
			prcNewWindow->left,
			prcNewWindow->top,
			600,
			300,
			SWP_NOZORDER | SWP_NOACTIVATE);
	}
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
