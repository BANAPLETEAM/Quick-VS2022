#pragma once



// CReportForm33 �� ���Դϴ�.

class CReportForm33 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm33)

protected:
	CReportForm33();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CReportForm33();

public:
	enum { IDD = IDD_REPORT33 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	CXTPListCtrl2 m_lstReport;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtpFrom;
	CDateTimeCtrl m_dtpTo;
	CDateButton m_btnData;
	virtual void OnInitialUpdate();
	void RefreshList();
	afx_msg void OnViewExcel();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEnChangeRnoEdit();
	CFlatEdit2 m_edtRNo;
	void SearchFilter();
	afx_msg void OnCbnSelchangeStateCombo();
	CComboBox m_cmbState;
	void OnApproval();
};


