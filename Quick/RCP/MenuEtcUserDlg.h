#pragma once
#include "afxwin.h"


// CMenuEtcUserDlg ��ȭ �����Դϴ�.

class CMenuEtcUserDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMenuEtcUserDlg)

public:
	CMenuEtcUserDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMenuEtcUserDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MENU_ETC_USER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
