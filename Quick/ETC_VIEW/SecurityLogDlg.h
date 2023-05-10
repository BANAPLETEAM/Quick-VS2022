#pragma once

#include "ColorListCtrl.h"

// CSecurityLogDlg ��ȭ �����Դϴ�.

class CSecurityLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSecurityLogDlg)

public:
	CSecurityLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSecurityLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SECURITY_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
