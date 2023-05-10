#pragma once

// CStatForm7 �� ���Դϴ�.

class CStatForm7 : public CMyFormView
{
	DECLARE_DYNCREATE(CStatForm7)

protected:
	CStatForm7();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CStatForm7();

public:
	enum { IDD = IDD_STAT_FORM7 };
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
	BOOL m_bFirst;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo; 
	BOOL m_bLeftList;

	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;
	CDateButton m_DateBtn;

	CMyStatic m_stcHelp;
	CXTPListCtrl2 m_lstReport;
	CXTPListCtrl35 m_lstSubReport;

	void OnViewExcel();
	void SetHelpText(long nBalance);
	void RefreshList();
	void RefreshSubList();
	CString GetBetweenDate(CString sDate);
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	virtual void OnInitialUpdate();
	CMyStatic m_stcHelp2;
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEnChangeSearchEdit();
};
