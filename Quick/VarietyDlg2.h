#pragma once
#include "afxwin.h"


// CVarietyDlg2 ��ȭ �����Դϴ�.

class CVarietyDlg2 : public CMyDialog
{
	DECLARE_DYNAMIC(CVarietyDlg2)

public:
	CVarietyDlg2(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CVarietyDlg2();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_VARIETY_DLG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edtEtc;
	CString m_sEtc;
	CString m_sTitle;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
