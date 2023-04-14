#pragma once
#include "afxwin.h"


// CSearchPOISetupDlg 대화 상자입니다.

class CSearchPOISetupDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSearchPOISetupDlg)

public:
	CSearchPOISetupDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSearchPOISetupDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SEARCH_POI_SETUP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CButton m_chkUseDirectDistance;
};
