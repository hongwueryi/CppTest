//空win32工程项目
#include <windows.h>

LRESULT CALLBACK hookproc(int nCode, WPARAM wParam, LPARAM lParam)
{
    MessageBox(NULL, L"hookproc;", 0, MB_OK);
    //     if (((DWORD)lParam & 0x40000000) && (HC_ACTION == nCode)) //有键按下
    //     {
    //         if ((wParam == VK_SPACE) || (wParam == VK_RETURN)) {
    //             MessageBox(NULL, L"有按键按下;", 0, MB_OK);
    //         }
    //     }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    while (1)
    {

    }
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD, hookproc, 0, GetCurrentThreadId());
    if (NULL == hook)
    {
        MessageBox(NULL, L"error", 0, MB_OK);
    }   
    int num = GetLastError();
    Sleep(1000 * 10 * 6);

    return 0;
}