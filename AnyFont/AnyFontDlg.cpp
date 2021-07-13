
// AnyFontDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AnyFont.h"
#include "AnyFontDlg.h"
#include "afxdialogex.h"
#include "FontManager.h"
#include <mutex>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAnyFontDlg 对话框
HWND g_hWnd = nullptr;


CAnyFontDlg::CAnyFontDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ANYFONT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAnyFontDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAnyFontDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SETFONT, &CAnyFontDlg::OnBnClickedBtnSetfont)
	ON_BN_CLICKED(IDC_BTN_RECOVER, &CAnyFontDlg::OnBnClickedBtnRecover)
END_MESSAGE_MAP()


// CAnyFontDlg 消息处理程序

BOOL CAnyFontDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAnyFontDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAnyFontDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool fontTest(CString FontFile, CString fontName, LONG fontsize)
{
	if (!CFontManger::Getinstance()->BackUpDefaultFontInfo())
	{
		//printf("backup default fontinfo failed.\n");
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
		CFontManger::Getinstance()->LOGINFO(L"set specified font failed...");
		return false;
	}

	CFontManger::Getinstance()->LOGINFO(L"set specified font Sucessed...");
	return true;
}

void CAnyFontDlg::EnableControl(BOOL Enable)
{
	GetDlgItem(IDC_BTN_RECOVER)->EnableWindow(Enable);
	GetDlgItem(IDC_BTN_SETFONT)->EnableWindow(Enable);
}
std::mutex g_mux;
void CAnyFontDlg::OnBnClickedBtnSetfont()
{
	std::unique_lock<std::mutex>lock(g_mux);
	//EnableControl(FALSE);
	g_hWnd = theApp.GetMainWnd()->m_hWnd;
	// TODO: 在此添加控件通知处理程序代码
	fontTest(L"Oz焦糖下午茶.ttf", L"Oz焦糖下午茶", 11);
	//EnableControl(TRUE);
}


void CAnyFontDlg::OnBnClickedBtnRecover()
{
	std::unique_lock<std::mutex>lock(g_mux);
	//EnableControl(FALSE);
	g_hWnd = theApp.GetMainWnd()->m_hWnd;
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(L"这就是一个Test", L"提示", MB_OK);
	CFontManger::Getinstance()->SetDefaultFont(L"Microsoft YaHei UI", 9);
	//EnableControl(TRUE);
}
