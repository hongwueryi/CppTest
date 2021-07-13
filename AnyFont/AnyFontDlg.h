
// AnyFontDlg.h : 头文件
//

#pragma once


// CAnyFontDlg 对话框
class CAnyFontDlg : public CDialogEx
{
// 构造
public:
	CAnyFontDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANYFONT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSetfont();
	afx_msg void OnBnClickedBtnRecover();
	void EnableControl(BOOL Enable);
};
