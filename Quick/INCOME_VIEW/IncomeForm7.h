#pragma once

class CRiderReportDlg;
class CRiderReportOrderDlg;

class CIncomeForm7 : public CMyFormView
{
	DECLARE_DYNCREATE(CIncomeForm7)

public:
	CIncomeForm7();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CIncomeForm7();

public:
	enum { IDD = IDD_INCOME_PAGE7 };
//#ifdef _DEBUG
//	virtual void AssertValid() const;
//	virtual void Dump(CDumpContext& dc) const;
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedRefreshBtn();
	void RefreshList();
	void OpenDepositDlg();
	void RefreshDepositList();
	void DeleteDepositReport();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnDepositReportItemlClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnDepositReportItemlRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	CRiderReportDlg *m_pRiderReportDlg;

	CXTPListCtrl2 m_lstRider;
	CXTPListCtrl15 m_lstDeposit;
	afx_msg void OnTimer(UINT nIDEvent);
	CEdit m_SearchEdt;
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint point);

	void OnMakeFixedDeposit();
	void OnHalfInsertFixedDeposit();
	void OnDeleteFixedDeposit();
	void OnNotReport();
	void OnReportComplete();
	void OnIncomeComplete();
	void OnViewExcel();
};


