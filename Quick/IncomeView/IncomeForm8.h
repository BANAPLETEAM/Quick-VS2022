#pragma once

// CIncomeForm8 폼 뷰입니다.

class CIncomeForm8 : public CMyFormView
{
	DECLARE_DYNCREATE(CIncomeForm8)

protected:
	CIncomeForm8();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CIncomeForm8();

public:
	enum { IDD = IDD_INCOME_PAGE8 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRefreshBtn();
	virtual void OnInitialUpdate();
	void RefreshList();
	void RecordHide();

	CXTPListCtrl26 m_wndReport;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;
	CDateButton m_DateBtn;
	CEdit m_RNoEdit;
	CButton m_chkNotReport;
	CButton m_chkReport;
	CButton m_chkIncomeComplete;
	CButton m_chkOutputComplete;
	afx_msg void OnEnChangeRnoEdit();
	afx_msg void OnBnClickedNotReportCheck();
	afx_msg void OnBnClickedReportCheck();
	afx_msg void OnBnClickedIncomeCompleteCheck();
	afx_msg void OnBnClickedOutputCompleteCheck();
	void OnDblClickList(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	void OnClickList(NMHDR * pNotifyStruct, LRESULT * result);
	BOOL CompleteIncome(long nID);
	CString GetSMSMsg(ST_DEPOSIT *pDeposit);

	afx_msg void OnMakeFixedDeposit();
	afx_msg void OnHalfInsertFixedDeposit();
	afx_msg void OnDeleteFixedDeposit();

	afx_msg void OnNotReport();
	afx_msg void OnReportComplete();
	afx_msg void OnIncomeComplete();
	afx_msg void OnViewExcel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CStatic m_stcGive;
	CStatic m_stcTake;
};


