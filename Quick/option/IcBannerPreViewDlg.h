#pragma once
#include "explorer.h"


// CIcBannerPreViewDlg 대화 상자입니다.

class CIcBannerPreViewDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CIcBannerPreViewDlg)

public:
	CIcBannerPreViewDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CIcBannerPreViewDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_IC_BANNER_PRE_VIEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_sBanner;
	CExplorer m_Explorer;
	afx_msg void OnBnClickedButton1();
};
