#pragma once
#include "afxwin.h"


// CGroupSearchDlg ��ȭ �����Դϴ�.

class CGroupSearchDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CGroupSearchDlg)

public:
	CGroupSearchDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGroupSearchDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GROUP_SEARCH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CWnd *m_pParent;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedUnactiveOptionCheck();
	afx_msg void OnBnClickedCloseBtn();
	CButton m_chkCashOption;
	CButton m_chkCreditOption;
	CButton m_chkActiveOption;
	CButton m_chkUnActiveOption;
	CComboBox m_cmbReportDay;
	CComboBox m_cmbNotReport;
	CComboBox m_cmbNotReport2;
	afx_msg void OnBnClickedCashOptionCheck();
	afx_msg void OnBnClickedCreditOptionCheck();
	afx_msg void OnCbnSelchangeReportDayCombo();
	afx_msg void OnCbnSelchangeNotReportCombo();
	afx_msg void OnBnClickedActiveOptionCheck();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCbnSelchangeNotReportCombo2();
};
