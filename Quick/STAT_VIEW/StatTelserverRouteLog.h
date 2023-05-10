#pragma once

class CStatTelserverRouteLog : public CMyFormView
{
	DECLARE_DYNCREATE(CStatTelserverRouteLog)

protected:
	CStatTelserverRouteLog();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CStatTelserverRouteLog();

public:
	enum { IDD = IDD_STAT_TELSERVER_ROUTE_FORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;
	CDateButton m_DateBtn;

	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnBnClickedDIDRoute();

	void RefreshList();
	void SearchRecord(BOOL bVisible);

	CXTPListCtrl2 m_lstReport;
	CFlatEdit2 m_edtSearch;
	CString m_strSearchNumber;
};
