#pragma once
#include "afxwin.h"


// CCustomMyAfxMessgagebox 대화 상자입니다.

class CCustomMyAfxMessgagebox : public CMyDialog
{
	DECLARE_DYNAMIC(CCustomMyAfxMessgagebox)

public:
	CCustomMyAfxMessgagebox(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCustomMyAfxMessgagebox();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CUSTOM_AXFMESSAGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedYesBtn();
	afx_msg void OnBnClickedNoBtn();
	afx_msg void OnBnClickedCancleBtn();
	void SetTitle(CString strTitle);
	void SetFirstDesc(CString strText);
	void SetSecondDesc(CString strText);

	CString m_strTitle;
	CString m_strFirstDesc;
	CString m_strSecondDesc;
	BOOL m_bCustomMode;

	long m_nType;
	void CCustomMyAfxMessgagebox::SetCustomMode(BOOL bMode = TRUE) { m_bCustomMode = bMode; }
	CStatic m_stcTitle;
	afx_msg void OnStnClickedDescStc();
	CStatic m_stcDescription1;
	CStatic m_stcDescription2;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
