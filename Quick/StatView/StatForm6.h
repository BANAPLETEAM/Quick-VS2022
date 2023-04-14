#pragma once

class CStatForm6 : public CMyFormView
{
	DECLARE_DYNCREATE(CStatForm6)

protected:
	CStatForm6();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CStatForm6();

public:
	enum { IDD = IDD_STAT_FORM6 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeTypeCombo();
	afx_msg void OnBnClickedRequestTransferBtn();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnViewExcel();
	virtual void OnInitialUpdate();

	void RefreshList();
	void CutEtc(CString sEtc, CString &sSCompany, CString &sSEtc);
	void Filter();
	void CheckType();
	long GetTNoFromText(CString strTNo);

	CXTPListCtrl34 m_lstReport;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo; 

	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;
	CDateButton m_btnDate;
	
	CComboBox m_cmbType;
	CFlatEdit2 m_edtSearch;

	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
};


