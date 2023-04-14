#pragma once


#include "PSListCtrl.h"
#include "afxwin.h"

class CChargeDistanceType : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeDistanceType)

public:
	CChargeDistanceType(CWnd* pParent, BOOL bTruck);   // ǥ�� �������Դϴ�.
	virtual ~CChargeDistanceType();
	
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHARGE_TYPE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedNewButton();
	afx_msg void OnBnClickedModifyButton();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnCbnSelchangeTypeNameCombo();
	afx_msg void OnBnClickedRowAddButton();
	afx_msg void OnBnClickedRowDeleteButton();
	afx_msg void OnBnClickedRegisterButton();
	afx_msg void OnBnClickedRowDeleteAllButton();
	afx_msg void OnBnClickedCloseButton();
	afx_msg void OnCbnSelendcancelCompanyCombo2();
	
	CPSListCtrl m_List;
	CComboBox m_cmbTypeName;
	CComboBox m_cmbCompany;
	
	void RefreshList();
	void InputComboList(int select_id = 0);
	void TypeNameInsert(int id);
	virtual BOOL OnInitDialog();

	BOOL CheckData();
	long m_nCompany;
	long m_nRegister2007ChargeCompany;
	
	CString m_sCompany;
	BOOL m_bIntegrated;
	CString m_sTypeName;
	BOOL m_bTruck;
};
