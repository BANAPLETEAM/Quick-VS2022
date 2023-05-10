#pragma once


class CGraph;

class CReportForm26 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm26)

protected:
	CReportForm26();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CReportForm26();

public:
	enum { IDD = IDD_REPORT26 };
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
	void RefreshList();
	afx_msg void OnBnClickedRefreshBtn();
public:
	CXTPListCtrl2 m_lstLeft;
	CXTPListCtrl38 m_lstRight;

	CStatic m_stcDraw;

	CFlatEdit2 m_edtSearch;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;
	CDateButton m_btnDate;

	BOOL m_bGraphComplete;

	CGraph* m_Graph;


	afx_msg void OnViewExcel();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPaint();
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemRightDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
};


