#pragma once
#include "afxwin.h"


// CJinsangTelRegDlg ��ȭ �����Դϴ�.

class CJinsangTelRegDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CJinsangTelRegDlg)

public:
	CJinsangTelRegDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CJinsangTelRegDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_JINSANG_TEL_REG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboDuration();
	virtual BOOL OnInitDialog();
	CString m_sTelNumber;
	CString m_sName;
	int m_nDuration;
	CString m_sDesc;
	CComboBox m_cComboDuration;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
