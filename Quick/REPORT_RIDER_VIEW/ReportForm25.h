#pragma once

// CReportForm25 폼 뷰입니다.

class CReportForm25 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm25)

protected:
	CReportForm25();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CReportForm25();

public:
	enum { IDD = IDD_REPORT25 };
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
	COleDateTime m_tmFrom;
	COleDateTime m_tmTo;
	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;

	CXTPListCtrl2 m_List;

	CDateButton m_btnDate;
	CFlatEdit2 m_edtSearch;
	CComboBox m_cmbDay;

	BOOL IsSendSmsOk(long nFinalCharge, CString sHp);
	CString GetSmsMent(long nFixDeposit, long nChargeSum, long nChargeFinal);
	void RefreshList();
	void FilterList();
	long GetSendCount();

	virtual void OnInitialUpdate();
	afx_msg void OnViewExcel();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnCbnSelchangeDayCombo();
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnBnClickedSendSmsBtn();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};


