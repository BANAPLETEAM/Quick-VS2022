#pragma once

#include "ColorListCtrl.h"

// CSecurityLogDlg 대화 상자입니다.

class CSecurityLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSecurityLogDlg)

public:
	CSecurityLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSecurityLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SECURITY_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	CColorListCtrl m_List;
	CFont m_ListFont;
	CStringArray m_saList;
	CStatic m_BarStatic;

public:
	void RefreshList();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString GetSecurityLog(long nType, CString strData1, CString strData2, CString strData3);
	CString GetSecurityType(long nType);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
