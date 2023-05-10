#pragma once

#include "FlatEdit2.h"
#include "DataBox.h"
#include "DateButton.h"
// CConsignSettingDlg ��ȭ �����Դϴ�.

class CConsignSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CConsignSettingDlg)

public:
	CConsignSettingDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CConsignSettingDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CONSIGN_SETTING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	BOOL m_bNew;
	long m_nShareCode1;

	CString m_sOtherCompanyName;
	long	m_nOtherCompany;
	long m_nModifyID;
	CFlatEdit2 m_edtOtherCompanyName;
	CFlatEdit2 m_edtNowApplyRate;
	CFlatEdit2 m_edtNowApplyDate;

	CComboBox m_cmbChangeRate;
	CComboBox m_cmbReserved;

	
	CDateTimeCtrl m_dtpReserveDate;

	COleDateTime m_dtReserveDate;
	
	CDataBox m_SettingReport;
	CButton m_btnConfirm;
	CButton m_btnModify;
	CButton m_btnCancelRequest;
	CDateButton m_DateBtn;
	CEdit m_edtSearch;
	CButton m_chkAlllog;
	void DataInput();
	void LogList();
	void InitControl();
	afx_msg void OnCbnSelchangeReserveCombo();
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedModifyBtn();	
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedRequestCancelBtn();
	afx_msg void OnBnClickedSearchBtn();

	CDateTimeCtrl m_dtFrom;
	CDateTimeCtrl m_dtTo;
	COleDateTime m_From;
	COleDateTime m_To;
	CString m_sOtherCity;

	void EditChaeckData();
	void NewCheckData();
	void DeleteCheckData();
	COleDateTime GetReserveTime();
	static CString GetLogType(int nType);

	
	afx_msg void OnEnChangeInnerSearchEdit();
};
