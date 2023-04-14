#pragma once
#include "afxwin.h"


// CJinsangTelRegDlg 대화 상자입니다.

class CJinsangTelRegDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CJinsangTelRegDlg)

public:
	CJinsangTelRegDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CJinsangTelRegDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_JINSANG_TEL_REG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
