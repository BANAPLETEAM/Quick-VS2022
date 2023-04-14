#pragma once
#include "afxwin.h"


class CCustomerDlg;

// CCustomerPage15 폼 뷰입니다.

class CCustomerPage15 : public CMyFormView
{
	DECLARE_DYNCREATE(CCustomerPage15)

protected:
	CCustomerPage15();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CCustomerPage15();

public:
	enum { IDD = IDD_CUSTOMER_PAGE15 };
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
	CCustomerDlg *m_pCustomerDlg;
	CXTPListCtrl2 m_lstCustomer;
	void RefreshList();
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnCustomerReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	CFlatEdit2 m_edtSearch;
	HCURSOR m_hcArrow;
	HCURSOR m_hcNo;
	HCURSOR m_hcMoveHold;
	POINT m_DragStartPoint;

	POINT m_ptDrag;
	BOOL m_bDragMode;
	BOOL m_bClicking;
	BOOL SumCustomer(CPoint pt);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnReportBeginDrag(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewExcel();
};


