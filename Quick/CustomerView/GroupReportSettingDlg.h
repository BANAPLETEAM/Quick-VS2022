#pragma once
#include "afxwin.h"

#define COLUMN_COUNT 21

// CGroupReportSettingDlg ��ȭ �����Դϴ�.

class CGroupReportSettingDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CGroupReportSettingDlg)

public:
	CGroupReportSettingDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGroupReportSettingDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GROUP_REPORT_SETTING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnCbnSelchangeReportFirstDayCombo();
	afx_msg void OnCbnSelchangeReportSecondDayCombo();
	afx_msg void OnBnClickedIncludeOrderCheck();
	afx_msg void OnBnClickedNotIncludeOrderCheck();
	afx_msg void OnBnClickedCancelBtn();

	virtual BOOL OnInitDialog();

	BOOL m_bSelect[COLUMN_COUNT];
	void CheckCombo();
	void InitCheckBox(BOOL bEnable);
	
	long m_nGNo;

	CFlatEdit2 m_edtDiscount;

	CButton m_chkCashApply;
	CButton m_chkCreditApply;
	CButton m_chkOnlineApply;
	CButton m_chkTransApply;
	CButton m_chkShowOrder;	
	CButton m_chkNotShowOrder;
	CButton m_chkNotShowCash;

	CComboBox m_cmbReportFirstDay;
	CComboBox m_cmbReportSecondDay;
	CComboBox m_cmbAddTaxApplyType;

	BOOL m_bCashApply;
	BOOL m_bCreditApply;
	BOOL m_bOnlineApply;
	BOOL m_bTransApply;
	BOOL m_bNotShowCash;
	BOOL m_bShowOrder;	
	
	int m_nAddTaxApplyType;
	int m_nReportFirstDay;
	int m_nReportSecondDay;
		
	CString m_strDiscount;
	CStringArray m_strColumn;	

};
