#pragma once
#include "afxwin.h"



// CIncomeForm10 폼 뷰입니다.

class CIncomeForm10 : public CMyFormView
{
	DECLARE_DYNCREATE(CIncomeForm10)

protected:
	CIncomeForm10();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CIncomeForm10();

public:
	enum { IDD = IDD_INCOME_PAGE10 };
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
	virtual void OnInitialUpdate();
	void ChangeAbleRechargeState(BOOL bActive);

	void RefreshList();
	CXTPListCtrl2 m_lstCard;
	CXTPListCtrl2 m_lstLog;
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedInsertCardBtn();
	CXTMaskEdit m_edtCardNumber;
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRechargeOn();
	afx_msg void OnRechargeOff();
	afx_msg void OnCardGive();
	afx_msg void OnCardTake();
	afx_msg void OnCardRecharge();

	afx_msg void OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtpFrom;
	CDateTimeCtrl m_dtpTo;
	CDateButton m_btnData;

	BOOL ChargeCardRiderState(CXTPGridRecord *pRecord, long nCompany, long nRNo);
	afx_msg void OnBnClickedRefreshLogBtn();
	void RefreshLogList(BOOL bAll);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeSearchEdit();
	CEdit m_edtSearch;
};


