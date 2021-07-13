#pragma once
//#include <winable.h>
#include <atlconv.h>
//ǰ����SendInput����Ҫ�õ����������ַ���ת����ʱ��Ҫ�õ���
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
//Ϊ����ʹ�ã��������������װ��ǰ����������

void SendKeys(CString msg)
{
    short vk;
    BOOL shift;
    USES_CONVERSION;
    wchar_t* data = T2W(msg.GetBuffer(0));
    int len = wcslen(data);
    for (int i = 0; i < len; i++)
    {
        if (data[i] >= 0 && data[i] < 256) //ascii�ַ�
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
        else //unicode�ַ�
        {
            SendUnicode(data[i]);
        }
    }
}

//ֱ�ӵ���SendKeys�����Ϳ����ڵ�ǰ����λ���Զ�����ָ�����ַ����������������ʾ������Զ��򿪼��±���������һ�λ���
void OnVirtualKeyTest()
{
    ShellExecuteA(NULL, NULL, "notepad.exe", NULL, NULL, SW_SHOWNORMAL);

    Sleep(500); //Ϊ��ȷ�����±��������ϣ��Ե�Ƭ��
    HWND pWnd = FindWindowA(NULL, "�ޱ��� - ���±�");
    if (pWnd)
    {
        SetForegroundWindow(pWnd);
        //SendKeys(L"����sway���Ұ��й���\nI love China! \b\b");
        INPUT m_InPut[2] = { 0 };
        //�����Ϣ���轫type��ΪINPUT_MOUSE������Ǽ�����Ϣ,��type��ΪINPUT_KEYBOARD��
        m_InPut[0].type = m_InPut[1].type = INPUT_MOUSE;
        //��type��Ϊ�����Ϣ����INPUT�ṹ�е�mi�ṹ�ǿ���ʹ�õģ�hi��ki�ṹ����ʹ��
        m_InPut[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
        m_InPut[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
        SendInput(sizeof(m_InPut) / sizeof(m_InPut[0]), m_InPut, sizeof(INPUT));
    }
}