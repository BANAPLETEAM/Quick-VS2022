#pragma once
#include "afxwin.h"



// CReportForm27 폼 뷰입니다.

class CReportForm27 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm27)

protected:
	CReportForm27();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CReportForm27();

public:
	enum { IDD = IDD_REPORT27 };
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
	BOOL m_bDragMode;

	CXTPListCtrl2 m_lstLeft;
	CXTPListCtrl2 m_lstRight;
	CStatic m_stcDraw;

	CFlatEdit2 m_edtSearch;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;
	CDateButton m_DateBtn;

	void RefreshCustomerList(BOOL bAll);
	virtual void OnInitialUpdate();

	CString GetSelectedCNo();
	void RefreshList();

	afx_msg void OnViewExcel();
	afx_msg void OnVisibleCol();
	afx_msg void OnReportColumnRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedSearchAllBtn();
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};


