#pragma once
#include "afxwin.h"


// CCustomMyAfxMessgagebox ��ȭ �����Դϴ�.

class CCustomMyAfxMessgagebox : public CMyDialog
{
	DECLARE_DYNAMIC(CCustomMyAfxMessgagebox)

public:
	CCustomMyAfxMessgagebox(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCustomMyAfxMessgagebox();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CUSTOM_AXFMESSAGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
