#pragma once

#include "ReportForm24.h"

// CGroupReportView 폼 뷰입니다.

class CGroupReportView : public CMyFormView
{
	DECLARE_DYNCREATE(CGroupReportView)

protected:
	CGroupReportView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CGroupReportView();

public:
	enum { IDD = IDD_GROUP_REPORT_DLG };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnVisibleCol();

	virtual void OnInitialUpdate();
	void MakeListResultTree(long nGNo);
	void GetData(CString sMainGNo, CMkRecordset &pRs);
	void CallChildReport(CXTPGridRecord *pRecord);
	void CallChildReportForCheckZero(CXTPGridRecord *pRecord);
	void OnMakeGroupReport();
	void OnDeleteGroupReport();
	void OnReGroupReport();
	void OnIncome();
	void OnAfterReport();
	void OnUnBill();
	void OnTaxAccount();
	void OnEtc();
	void OnExcel();
	void SetExcelData(COleSafeArray &sa, GROUP_REPORT st, BOOL bSumRecord, long &nItem, long nCol);
	void OnOrderSee();
	void OnDeleteAll();
	void OnDeleteGroup();
	void DeleteZeroRecord();
	void ShowCurLocation(long nGNo);
	void GetDataReal(CMkRecordset *pRs);

	CGroupListReport24 m_lstReport;

	BOOL m_bFirst;

	long m_nNotIncome;
	long m_nIncome;
	CBrush m_brush;  
};






