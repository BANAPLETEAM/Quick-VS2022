#pragma once

class CStatTelserverRouteLog : public CMyFormView
{
	DECLARE_DYNCREATE(CStatTelserverRouteLog)

protected:
	CStatTelserverRouteLog();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
