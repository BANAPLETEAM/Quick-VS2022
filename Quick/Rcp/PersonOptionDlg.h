#pragma once
#include "afxwin.h"


// CPersonOptionDlg ��ȭ �����Դϴ�.

class CPersonOptionDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CPersonOptionDlg)

public:
	CPersonOptionDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPersonOptionDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PERSON_OPTION_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOrderFinishCheck();
	CButton m_chkAutoFinish;
	
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedButton1();
	CButton m_chkAutoAllocate;
	afx_msg void OnBnClickedAutoAlocateCheck();
};
