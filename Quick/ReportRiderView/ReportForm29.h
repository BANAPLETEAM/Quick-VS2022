#pragma once
#include "afxwin.h"


class CReportForm29 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm29)

protected:
	CReportForm29();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CReportForm29();

public:
	enum { IDD = IDD_REPORT29 };
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
	afx_msg void OnReportItemSelChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemEachClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemAllClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedDrawingBtn();
	afx_msg void OnBnClickedRefreshBtn2();
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedSaveBtn();

	virtual void OnInitialUpdate();

	void RefreshLogList(CXTPListCtrl2 *pList, BOOL bAll);
	void RefreshList();
	void DeleteRiderList();
	void RefreshEachList();
	void RefreshAllList();
	long GetRiderCurBalance(long nRiderCompany, long nRNo);

	CXTPListCtrl46 m_lstRider;
	CXTPListCtrl2 m_lstEachLog;
	CXTPListCtrl2 m_lstAllLog;

	long m_nRiderCompany;
	long m_nRNo;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;

	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;

	CDateButton m_btnDate;

	CComboBox m_cmbBank;

	BOOL m_bEachReport;

	CFlatEdit2 m_edtSearch;
	CFlatEdit2 m_edtRiderName;
	CFlatEdit2 m_edtAccount;
	CFlatEdit2 m_edtDepositName;
	CFlatEdit2 m_edtShareBalance;
	CFlatEdit2 m_edtAMount;
	CFlatEdit2 m_edtPhone;
	CFlatEdit2 m_edtEtc;
	afx_msg void OnViewExcel();
	afx_msg void OnBnClickedRefreshLogBtn();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);	
	CFlatEdit2 m_edtShEtc;
	afx_msg void OnEnChangeSearchEtcEdt();
};


