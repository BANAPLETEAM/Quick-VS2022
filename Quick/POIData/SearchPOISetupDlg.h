#pragma once
#include "afxwin.h"


// CSearchPOISetupDlg ��ȭ �����Դϴ�.

class CSearchPOISetupDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSearchPOISetupDlg)

public:
	CSearchPOISetupDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSearchPOISetupDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SEARCH_POI_SETUP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CButton m_chkUseDirectDistance;
};
