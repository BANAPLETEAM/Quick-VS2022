#pragma once
#include "afxwin.h"


// CVarietyDlg2 대화 상자입니다.

class CVarietyDlg2 : public CMyDialog
{
	DECLARE_DYNAMIC(CVarietyDlg2)

public:
	CVarietyDlg2(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVarietyDlg2();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_VARIETY_DLG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edtEtc;
	CString m_sEtc;
	CString m_sTitle;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
