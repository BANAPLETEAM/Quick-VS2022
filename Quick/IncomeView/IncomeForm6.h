#pragma once


// CIncomeForm6 폼 뷰입니다.

class CIncomeForm6 : public CMyFormView
{
	DECLARE_DYNCREATE(CIncomeForm6)

protected:
	CIncomeForm6();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CIncomeForm6();

public:
	enum { IDD = IDD_INCOME_PAGE6 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRefreshBtn();
	void OnClickList(NMHDR * pNotifyStruct, LRESULT * result);
	void OnDblClickList(NMHDR * pNotifyStruct, LRESULT * result);
public:
	CXTPListCtrl8 m_wndReport;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;
	CDateButton m_DateBtn;
	CEdit m_RNoEdit;

	void RefreshList();
	virtual void OnInitialUpdate();
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	afx_msg void OnMakeFixedDeposit();
	afx_msg void OnHalfInsertFixedDeposit();
	afx_msg void OnDeleteFixedDeposit();

	afx_msg void OnNotReport();
	afx_msg void OnReportComplete();
	afx_msg void OnIncomeComplete();
	afx_msg void OnViewExcel();

	CString GetIncomeState(BOOL bWeeklyDeposit, COleDateTime dtMainDate, long nRiderIncomeDay, BOOL bSameRiderIncomeDay);
	CComboBox m_cmbState;
	afx_msg void OnEnChangeRnoEdit();
	afx_msg void OnCbnSelchangeStateCombo();
	void RecordHide();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

};


