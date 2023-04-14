#pragma once

// CBranchReportWantTransferDlg 폼 뷰입니다.
class CBranchReportWantTransferDlg : public CMyFormView
{
	DECLARE_DYNCREATE(CBranchReportWantTransferDlg)

protected:
	CBranchReportWantTransferDlg();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CBranchReportWantTransferDlg();

public:
	enum { IDD = IDD_BRANCH_REPORT_WANT_TRANSFER_DLG };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CXTPGridControl m_wndReport;

	CDateButton m_DateBtn;
	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	
	void RefreshList();
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	void OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * result);
};


