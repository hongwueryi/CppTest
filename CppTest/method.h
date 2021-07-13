#pragma once
//C++ʵ�������洴������Ŀ�ݷ�ʽ

#include <ShlObj.h>
#include <atlstr.h>
#include <vector>
using namespace std;

bool EnumDeskTopLnkPath(LPCWSTR pszLnkName)
{
    bool ret = false;
    WCHAR szPath[MAX_PATH] = { 0 };
    SHGetSpecialFolderPathW(NULL, szPath, CSIDL_DESKTOPDIRECTORY, 0);

    IShellFolder* pShell = NULL;
    if (FAILED(SHGetDesktopFolder(&pShell)))
    {
        return ret;
    }
    IShellFolder* pFolder = NULL;
    ITEMIDLIST* pItem = NULL;
    if (FAILED(pShell->ParseDisplayName(NULL, NULL, szPath, NULL, &pItem, NULL)))
    {
        return ret;
    }
    if (FAILED(pShell->BindToObject(pItem, NULL, IID_IShellFolder, (LPVOID*)&pFolder)))
    {
        return ret;
    }
    pShell->Release();

    if (NULL == pFolder)
    {
        return ret;
    }

    IEnumIDList* pEnum = NULL;
    if (FAILED(pFolder->EnumObjects(NULL, SHCONTF_NONFOLDERS, &pEnum)))
    {
        return ret;
    }
    pItem = NULL;
    ULONG ulFetched = 0;

    WCHAR szLnkPath[MAX_PATH] = { 0 };
    WCHAR szLnkName[MAX_PATH] = { 0 };
    //LPCWSTR pszLnkName(L".lnk");
    WIN32_FIND_DATAW fd = { 0 };

    while (S_OK == pEnum->Next(1, &pItem, &ulFetched))
    {

        SHGetDataFromIDListW(pFolder, pItem, SHGDFIL_FINDDATA, &fd, sizeof(fd));
        swprintf_s(szLnkName, L"%s", fd.cFileName);
        if (0 == wcscmp(szLnkName, pszLnkName))
        {
            ret = true;
        }
    }

    pEnum->Release();
    pFolder->Release();
    return ret;
}

/*
szPath: ��ݷ�ʽ��Ŀ��Ӧ�ó�����
szLink: ��ݷ�ʽ�������ļ���(*.lnk
*/
BOOL CreatLinkToStartMenu(LPCTSTR szPath, LPCTSTR szLink) 
{   
    HRESULT hres;
    IShellLink * psl = nullptr;
    IPersistFile* ppf = nullptr;

    if (EnumDeskTopLnkPath(szLink))
        return TRUE;  //�����Ѿ����ڸÿ�ݷ�ʽ

    //����һ��IShellLinkʵ��
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr))
        return FALSE;

    hres = CoCreateInstance(CLSID_ShellLink, NULL,
        CLSCTX_INPROC_SERVER, IID_IShellLink,
        (void **)&psl);

    if (FAILED(hres))
        return FALSE;

    //����Ŀ��Ӧ�ó���
    psl->SetPath(szPath);

    //���ÿ�ݼ�(�˴���ΪShift+Ctrl+'R')
    psl->SetHotkey(MAKEWORD('R', HOTKEYF_SHIFT | HOTKEYF_CONTROL));

    //��IShellLink��ȡ��IPersistFile�ӿ�
    //���ڱ����ݷ�ʽ�������ļ� (*.lnk)
    hres = psl->QueryInterface(IID_IPersistFile, (void**)&ppf);

    if (FAILED(hres))
        return FALSE;

    wchar_t szStartPath[MAX_PATH] = { 0 };
    SHGetSpecialFolderPath(NULL, szStartPath, CSIDL_DESKTOP, 0);
    wcscat_s(szStartPath, L"\\");
    wcscat_s(szStartPath, szLink);

    USES_CONVERSION;
    LPCOLESTR oleLnks = CT2COLE(szStartPath);
    // ȷ�������ļ���ΪANSI��ʽ
    //MultiByteToWideChar(CP_ACP, 0, szLink, -1, wsz, MAX_PATH);

    //����IPersistFile::Save
    //�����ݷ�ʽ�������ļ� (*.lnk)
    hres = ppf->Save(oleLnks, FALSE);
    if (FAILED(hres))
        return FALSE;

    //�ͷ�IPersistFile��IShellLink�ӿ�
    ppf->Release();
    psl->Release();

    CoUninitialize();
    return TRUE;
}

class Cobj
{
public:
    friend class CFriend;  //��Ԫ�࣬CFrined���Է���Cobj��˽�г�Ա��˽�з���
private:
    int add() { return m_x + m_y; }
    int m_x;
    int m_y;
};

class CFriend
{
public:
    CFriend(int x, int y)
    {
        obj.m_x = x;
        obj.m_y = y;
    }

    int CFAdd()
    {
        return obj.add();
    }
private:
    Cobj obj;
};

//��ȡ���ش���������Ϣ
size_t GetDriverNames(vector<std::wstring>& driverNames)
{
    //��ȡ�������ַ�����Ϣ����ʽ�磺 ������A:\NULLB:\NULLC:\NULL
    int DSLength = GetLogicalDriveStrings(0, NULL);
    TCHAR* DStr = new TCHAR[DSLength];
    GetLogicalDriveStrings(DSLength, DStr);

    int si = 0;
    int driverType;

    for (int i = 0; i < DSLength / 4; ++i)
    {
        TCHAR dir[4] = { DStr[si],':','\\' ,'\0' };
        driverType = GetDriveType(dir);

        if (driverType == DRIVE_FIXED)// ֻ���ܴ������͵�
        {
            driverNames.push_back(dir);
        }

        si += 4;
    }

    delete[] DStr;

    return driverNames.size();
}

#include <tlhelp32.h>
int test2()
{
    HANDLE hSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnap)
        return 0;

    PROCESSENTRY32 processEntry = { sizeof(PROCESSENTRY32) };
    BOOL toBeContinue = ::Process32First(hSnap, &processEntry);
    while (toBeContinue)
    {
        DWORD processID_ = processEntry.th32ProcessID;
        HANDLE hP = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processEntry.th32ProcessID);
        if (hP)
        {
            TCHAR fullPath[MAX_PATH];
            DWORD len = MAX_PATH;
            if (QueryFullProcessImageName(hP, 0, fullPath, &len))
            {
                CString displayName_ = processEntry.szExeFile;
                CString fullPath_ = fullPath;

                displayName_.MakeLower();
                fullPath_.MakeLower();
            }
            CloseHandle(hP);
        }
        toBeContinue = ::Process32Next(hSnap, &processEntry);
    }
    CloseHandle(hSnap);
}