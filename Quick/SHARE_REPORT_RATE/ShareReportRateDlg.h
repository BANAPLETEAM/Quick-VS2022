#pragma once

#include  "ShareTranferRequestDlg.h"
#include "afxwin.h"

// CShareReportRateDlg 대화 상자입니다.
class CShareReportRateTabControl : public CXTPTabControl
{
protected:
	virtual void OnItemClick(CXTPTabManagerItem* pItem);
};

class CShareReportRateDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CShareReportRateDlg)

public:
	CShareReportRateDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CShareReportRateDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SHARE_REPORT_RATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnReportHyperlinkClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CWnd* GetTabItem(CString sCaption);
	CWnd* GetTabItem(int nTab);


public:
	BOOL m_bInitializing;

	CShareReportRateTabControl m_wndTabControl;
		
	CEdit m_BalanceEdit;
	CEdit m_BasicRateEdit;
	CEdit m_AccountEdit;
	CEdit m_AccountEdit2;
	CEdit m_YesterdayEdit;

	CXTHyperLink m_HelpStatic;

	long m_nBalance;
	long m_nBasicRate;

	BOOL IsRequest(int nCompany);
	void OpenRequestBox1();

	BOOL m_bExitPrg;
	CButton m_chkNoShowShareReport;

protected:
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStnClickedStaticOption();
	afx_msg void OnBnClickedButton1();
	CEdit m_GlobalShareTimeEdt;
	
	afx_msg void OnBnClickedIntroMyCompanyBtn();
	afx_msg void OnBnClickedExitPrgBtn();

	static BOOL IsNoShow();
	afx_msg void OnBnClickedNoShowCheck();
	CButton m_btnTest;
	afx_msg void OnBnClickedTestBtn();
};
