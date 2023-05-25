#pragma once
#include "afxwin.h"


class CCustomerMileageDlg; 
// CReportForm35 폼 뷰입니다.

class CXTPListCtrl58 : public CXTPListCtrl2
{
public:
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics) 
	{
		CXTPGridRecord *pRecord = pDrawArgs->pRow->GetRecord();
		long nCol = pDrawArgs->pColumn->GetItemIndex();

		if(GetItemLong(pRecord) == 0)
			pItemMetrics->clrBackground = RGB(200, 255, 255);
	
	}
};

class CReportForm35 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm35)

protected:
	CReportForm35();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CReportForm35();

public:
	enum { IDD = IDD_REPORT35 };
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
	CXTPListCtrl58 m_lstReport;
	void RefreshList();
	CCustomerMileageDlg *m_pCustomerMileageDlg;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtpFrom;
	CDateTimeCtrl m_dtpTo;
	CDateButton m_btnData;
	afx_msg void OnBnClickedRefreshButton();
	afx_msg void OnCbnSelchangeTypeCombo();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	CComboBox m_cmbType;
	CEdit m_edtSearch;

	afx_msg void OnWithdraw();
	afx_msg void OnWithdrawManual();
	afx_msg void OnWithdrawCancel();
	afx_msg void OnShowMileageLog();
	afx_msg void OnUpdateEtc();
	afx_msg void OnCheckItem();
	afx_msg void OnToExcel();
	void RefreshOne(CXTPGridRecord *pRecord, long nID);
	void GetRecordData(CXTPGridRecord *pRecord, CMkRecordset *rs);

	CXTPGridRecord *GetRecordItem(long &nID, long &nState);
	CString GetMileageWithdrawState(long nState);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEnChangeSearchEdit();
};


