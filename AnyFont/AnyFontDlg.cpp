
// AnyFontDlg.cpp : ʵ���ļ�
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


// CAnyFontDlg �Ի���
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


// CAnyFontDlg ��Ϣ�������

BOOL CAnyFontDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAnyFontDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	fontTest(L"Oz���������.ttf", L"Oz���������", 11);
	//EnableControl(TRUE);
}


void CAnyFontDlg::OnBnClickedBtnRecover()
{
	std::unique_lock<std::mutex>lock(g_mux);
	//EnableControl(FALSE);
	g_hWnd = theApp.GetMainWnd()->m_hWnd;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox(L"�����һ��Test", L"��ʾ", MB_OK);
	CFontManger::Getinstance()->SetDefaultFont(L"Microsoft YaHei UI", 9);
	//EnableControl(TRUE);
}
