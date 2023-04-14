#pragma once

#include "Graph.h"

typedef struct {
	UINT nData;
	COleDateTime dt;
	int nDayOfWeek;
} GRAPH_DATA7;

// CStatForm3 대화 상자입니다.

class CStatForm3 : public CMyFormView
{
	DECLARE_DYNCREATE(CStatForm3)

public:
	CStatForm3();   // 표준 생성자입니다.
	virtual ~CStatForm3();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_STAT_FORM3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();

	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewExcel();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedTodayBtn();
	afx_msg void OnBnClickedWeekBtn();
	afx_msg void OnBnClickedMonthBtn();
	afx_msg void OnBnClickedExactMonthBtn();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRefreshBtn();

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl2 m_lcData;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CStatic m_GraphStatic;

	CGraph* m_Graph;
	BOOL m_bGraphComplete;

	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;
	CDateButton m_DateBtn;
	CButton m_PhoneBaseCheck;
	CButton m_RefreshBtn;

public:
	void DrawGraph(GRAPH_DATA7 *pGraphData, UINT nMaxTotal, int nCount);
	void RefreshList();
	void RefreshListByCallingCount();
	void ChangeColumnTitle();

};
