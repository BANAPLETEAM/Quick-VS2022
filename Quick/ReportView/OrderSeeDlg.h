#pragma once

// COrderSeeDlg ��ȭ �����Դϴ�.

class COrderSeeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(COrderSeeDlg)

public:
	COrderSeeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~COrderSeeDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ORDER_SEE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void RefreshList();

	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnExcel();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedPrintBtn();
	afx_msg void OnVisibleCol();

	CXTPListCtrl23 m_lstReport;

	CStatic m_stcDiscount;
	CComboBox m_cmbAddTaxApplyType;

	CButton m_chkCashApply;
	CButton m_chkCreditApply;
	CButton m_chkOnlineApply;
	CButton m_chkTransApply;

	long m_nID;
	long m_nGNo;
	CString m_strDate;
};
