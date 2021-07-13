#pragma once
//C++实现在桌面创建程序的快捷方式

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
szPath: 快捷方式的目标应用程序名
szLink: 快捷方式的数据文件名(*.lnk
*/
BOOL CreatLinkToStartMenu(LPCTSTR szPath, LPCTSTR szLink) 
{   
    HRESULT hres;
    IShellLink * psl = nullptr;
    IPersistFile* ppf = nullptr;

    if (EnumDeskTopLnkPath(szLink))
        return TRUE;  //桌面已经存在该快捷方式

    //创建一个IShellLink实例
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr))
        return FALSE;

    hres = CoCreateInstance(CLSID_ShellLink, NULL,
        CLSCTX_INPROC_SERVER, IID_IShellLink,
        (void **)&psl);

    if (FAILED(hres))
        return FALSE;

    //设置目标应用程序
    psl->SetPath(szPath);

    //设置快捷键(此处设为Shift+Ctrl+'R')
    psl->SetHotkey(MAKEWORD('R', HOTKEYF_SHIFT | HOTKEYF_CONTROL));

    //从IShellLink获取其IPersistFile接口
    //用于保存快捷方式的数据文件 (*.lnk)
    hres = psl->QueryInterface(IID_IPersistFile, (void**)&ppf);

    if (FAILED(hres))
        return FALSE;

    wchar_t szStartPath[MAX_PATH] = { 0 };
    SHGetSpecialFolderPath(NULL, szStartPath, CSIDL_DESKTOP, 0);
    wcscat_s(szStartPath, L"\\");
    wcscat_s(szStartPath, szLink);

    USES_CONVERSION;
    LPCOLESTR oleLnks = CT2COLE(szStartPath);
    // 确保数据文件名为ANSI格式
    //MultiByteToWideChar(CP_ACP, 0, szLink, -1, wsz, MAX_PATH);

    //调用IPersistFile::Save
    //保存快捷方式的数据文件 (*.lnk)
    hres = ppf->Save(oleLnks, FALSE);
    if (FAILED(hres))
        return FALSE;

    //释放IPersistFile和IShellLink接口
    ppf->Release();
    psl->Release();

    CoUninitialize();
    return TRUE;
}

class Cobj
{
public:
    friend class CFriend;  //友元类，CFrined可以访问Cobj的私有成员和私有方法
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

//获取本地磁盘驱动信息
size_t GetDriverNames(vector<std::wstring>& driverNames)
{
    //获取驱动器字符串信息，格式如： 数据是A:\NULLB:\NULLC:\NULL
    int DSLength = GetLogicalDriveStrings(0, NULL);
    TCHAR* DStr = new TCHAR[DSLength];
    GetLogicalDriveStrings(DSLength, DStr);

    int si = 0;
    int driverType;

    for (int i = 0; i < DSLength / 4; ++i)
    {
        TCHAR dir[4] = { DStr[si],':','\\' ,'\0' };
        driverType = GetDriveType(dir);

        if (driverType == DRIVE_FIXED)// 只接受磁盘类型的
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