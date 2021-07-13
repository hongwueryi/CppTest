#pragma once
//#include <winable.h>
#include <atlconv.h>
//前者是SendInput函数要用到，后者是字符串转换的时候要用到。
#include <atlstr.h>
void SendAscii(wchar_t data, BOOL shift)
{
    INPUT input[2];
    memset(input, 0, 2 * sizeof(INPUT));

    if (shift)
    {
        input[0].type = INPUT_KEYBOARD;
        input[0].ki.wVk = VK_SHIFT;
        SendInput(1, input, sizeof(INPUT));
    }
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = data;
    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = data;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(2, input, sizeof(INPUT));
    if (shift)
    {
        input[0].type = INPUT_KEYBOARD;
        input[0].ki.wVk = VK_SHIFT;
        input[0].ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, input, sizeof(INPUT));
    }
}

void SendUnicode(wchar_t data)
{
    INPUT input[2];
    memset(input, 0, 2 * sizeof(INPUT));

    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = 0;
    input[0].ki.wScan = data;
    input[0].ki.dwFlags = 0x4;//KEYEVENTF_UNICODE;

    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = 0;
    input[1].ki.wScan = data;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP | 0x4;//KEYEVENTF_UNICODE;

    SendInput(2, input, sizeof(INPUT));
}
//为方便使用，下面这个函数包装了前两个函数。

void SendKeys(CString msg)
{
    short vk;
    BOOL shift;
    USES_CONVERSION;
    wchar_t* data = T2W(msg.GetBuffer(0));
    int len = wcslen(data);
    for (int i = 0; i < len; i++)
    {
        if (data[i] >= 0 && data[i] < 256) //ascii字符
        {
            vk = VkKeyScanW(data[i]);
            if (vk == -1)
            {
                SendUnicode(data[i]);
            }
            else
            {
                if (vk < 0)
                {
                    vk = ~vk + 0x1;
                }

                shift = vk >> 8 & 0x1;

                if (GetKeyState(VK_CAPITAL) & 0x1)
                {
                    if (data[i] >= 'a' && data[i] <= 'z' || data[i] >= 'A' && data[i] <= 'Z')
                    {
                        shift = !shift;
                    }
                }
                SendAscii(vk & 0xFF, shift);
            }
        }
        else //unicode字符
        {
            SendUnicode(data[i]);
        }
    }
}

//直接调用SendKeys函数就可以在当前光标的位置自动输入指定的字符串，下面的例子演示了如何自动打开记事本程序并输入一段话：
void OnVirtualKeyTest()
{
    ShellExecuteA(NULL, NULL, "notepad.exe", NULL, NULL, SW_SHOWNORMAL);

    Sleep(500); //为了确保记事本程序打开完毕，稍等片刻
    HWND pWnd = FindWindowA(NULL, "无标题 - 记事本");
    if (pWnd)
    {
        SetForegroundWindow(pWnd);
        //SendKeys(L"我是sway，我爱中国！\nI love China! \b\b");
        INPUT m_InPut[2] = { 0 };
        //鼠标消息，需将type置为INPUT_MOUSE，如果是键盘消息,将type置为INPUT_KEYBOARD。
        m_InPut[0].type = m_InPut[1].type = INPUT_MOUSE;
        //将type置为鼠标消息后，其INPUT结构中的mi结构是可以使用的，hi、ki结构不可使用
        m_InPut[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
        m_InPut[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
        SendInput(sizeof(m_InPut) / sizeof(m_InPut[0]), m_InPut, sizeof(INPUT));
    }
}