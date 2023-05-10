#pragma once


#include "ShareReportRateDlg.h"
#include "PPTooltip.h"
#include "MakeHtmlTable.h"
#include "ShareReportTransferDlg.h"
#include "ShareReportWantTransferDlg.h"
#include "ShareTranferRequestDlg.h"
#include "ShareTansferMyRequest.h"
#include "CorpOrderDlg.h"


// CShareReportRateDlg1 폼 뷰입니다.

class CShareReportRateLogDlg;


class CShareReportRateDlg1 : public CMyFormView
{
	DECLARE_DYNCREATE(CShareReportRateDlg1)

protected:
	CShareReportRateDlg1();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CShareReportRateDlg1();
	virtual void OnInitialUpdate();
	int UpdateShareReportRate(long nShareCode1A, long nShareCode1B, CString strTCompany,
		long nRcpRate, long nWCompany, long nWNo, CString strName, BOOL bNoShareA);

	int UpdateShareTime(long nShareCode1A, long nShareCode1B, CString strTCompany, 
		long nShareTime, long nWCompany, long nWNo, CString strName);


public:
	enum { IDD = IDD_SHARE_REPORT_RATE_DLG1 };

	CXTPGridControl m_wndReport;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	afx_msg void OnBnClickedEditBtn();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRefreshBtn();

	BOOL CheckValidate();
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	bool IsRequest(int nCompany);
	void RefreshList();
	void OpenRequestBox();
	void RefreshMoney();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result);
	afx_msg void OnBnClickedRequestBtn();
	afx_msg void OnBnClickedMyRequestBtn();
	afx_msg void OnBnClickedShareTimeEdit();
	afx_msg void OnEnChangeSearchEdit();


protected:
	CPPToolTip m_tooltip;
	CEdit m_SearchEdit;
	BOOL m_bHasAlliancePower;
	CEdit m_edtRate, m_edtRate2;
	CButton m_btnEditShareReport;


public:
	void Filter(CString strData);
	void InsertCompany(CMyRecord *pMyRecord);

	afx_msg void OnBnClickedMyAllianceManagerBtn();
	afx_msg void OnBnClickedCorpBtn();
	afx_msg void OnBnClickedRequestDrawingBtn();
};


