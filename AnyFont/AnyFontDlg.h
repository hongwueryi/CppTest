
// AnyFontDlg.h : ͷ�ļ�
//

#pragma once


// CAnyFontDlg �Ի���
class CAnyFontDlg : public CDialogEx
{
// ����
public:
	CAnyFontDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANYFONT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSetfont();
	afx_msg void OnBnClickedBtnRecover();
	void EnableControl(BOOL Enable);
};
