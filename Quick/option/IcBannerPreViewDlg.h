#pragma once
#include "explorer.h"


// CIcBannerPreViewDlg ��ȭ �����Դϴ�.

class CIcBannerPreViewDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CIcBannerPreViewDlg)

public:
	CIcBannerPreViewDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CIcBannerPreViewDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_IC_BANNER_PRE_VIEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_sBanner;
	CExplorer m_Explorer;
	afx_msg void OnBnClickedButton1();
};
