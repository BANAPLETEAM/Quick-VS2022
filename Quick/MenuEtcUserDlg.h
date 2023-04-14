#pragma once
#include "afxwin.h"


// CMenuEtcUserDlg 대화 상자입니다.

class CMenuEtcUserDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMenuEtcUserDlg)

public:
	CMenuEtcUserDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMenuEtcUserDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MENU_ETC_USER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CBranchInfo * m_pBi;
	CEdit m_EtcTitleEdt[5];
	CEdit m_EtcMemoEdt[5];

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedAllOkBtn();

	virtual BOOL OnInitDialog();
	BOOL SaveSetting(CBranchInfo *pBi);
	CButton m_chkFront;
};
