#pragma once
#include "afxwin.h"

// CAddRiderBalanceDlg ��ȭ �����Դϴ�.

class CAddRiderBalanceDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAddRiderBalanceDlg)

public:
	CAddRiderBalanceDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAddRiderBalanceDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ADD_RIEDR_BALANCE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CMyXTPListCtrl_IF3 m_wndReport;

	BOOL m_bAdd;
	long m_nRiderCompany;
	long m_nRNo;

	CString m_strRName;
	CString m_strInputSave;

	CButton m_btnOk;
	CButton m_btnCancel;
	
	CMyStatic m_stcCurSave;
	CMyStatic m_stcAfterSave;

	CComboBox m_cmbInputSave;
	CComboBox m_cmbInputSaveType;

	CFlatEdit2 m_edtSaveEtc;

	CMyStatic m_stc1;
	CMyStatic m_stc2;
	CMyStatic m_stc3;
	CMyStatic m_stc4;

	void InitControl();
	void InitRider();
	void RefreshCharge(BOOL bClick = TRUE);
	void RefreshList();

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeInputSaveCombo();
	//afx_msg void OnEnChangeSaveEdit();
	afx_msg void OnCbnEditupdateInputSaveCombo();

};
