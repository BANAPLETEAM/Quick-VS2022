#pragma once

#include "DateButtonOneDay.h"

// CStatForm2 대화 상자입니다.
class CStatForm2 : public CMyFormView
{
	DECLARE_DYNCREATE(CStatForm2)

public:
	CStatForm2();   // 표준 생성자입니다.
	virtual ~CStatForm2();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_STAT_FORM2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();

	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewExcel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedRefreshBtn();

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl2 m_List;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;

	CDateTimeCtrl m_FromDT;
    CDateTimeCtrl m_ToDT;
	CDateButtonOneDay m_DateBtn;
	CButton m_RefreshBtn;

public:
	void RefreshList();
	afx_msg void OnDtnDatetimechangeDatetimepickerFrom(NMHDR *pNMHDR, LRESULT *pResult);
};
