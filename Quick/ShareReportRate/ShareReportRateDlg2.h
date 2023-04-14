#pragma once


class CShareReportRateDlg2 : public CMyFormView
{
	DECLARE_DYNCREATE(CShareReportRateDlg2)

protected:
	CShareReportRateDlg2();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CShareReportRateDlg2();
	virtual void OnInitialUpdate();
	void	RefreshList();

public:
	enum { IDD = IDD_SHARE_REPORT_RATE_DLG2 };

	CXTPGridControl m_wndReport;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRefreshBtn();
public:
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	CButton m_TransferChk;
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnViewExcel();
public:
	CDateButton m_DateBtn;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;
	CComboBox m_cmbType;
};


