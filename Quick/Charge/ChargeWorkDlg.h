#pragma once
#include "afxwin.h"

typedef struct{
	CString sDo;
	CString sSi[50];
	long nCount;
}SITY_STRUCT;

typedef map<long, SITY_STRUCT> SITY_MAP;

class CChargeWorkDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeWorkDlg)

public:
	CChargeWorkDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChargeWorkDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHARGE_WORK_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_StartDoCmb;
	CComboBox m_StartSiCmb;
	CComboBox m_DestDoCmb;
	CComboBox m_DestSiCmb;

	CComboBox m_StartCmb;
	CComboBox m_DestCmb;
	CComboBox m_PlusCmb;
	CEdit m_ChargeEdt;
	CStatic m_Stc1;
	CStatic m_Stc2;
	CStatic m_Stc3;
	CButton m_chkWay;
		
	long m_nCompany;

	SITY_MAP m_map;

	void InitStruct();
	void InitDoCombo();
	void ReWriteStc();
	void EmptyStruct(SITY_STRUCT* st);
	CString GetRiderType(long index);
	afx_msg void OnBnClickedOkButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeStartDoCombo();
	afx_msg void OnCbnSelchangeStartSiCombo();
	afx_msg void OnCbnSelchangeStartTypeCombo();
	afx_msg void OnCbnSelchangeDestTypeCombo();
	afx_msg void OnCbnSelchangePlusCombo();
	afx_msg void OnEnChangeChargeEdit();
	CComboBox m_RiderTypeCmb;
	afx_msg void OnCbnSelchangeDestDoCombo();
	afx_msg void OnCbnSelchangeDestSiCombo();
	afx_msg void OnBnClickedCancelButton();
	afx_msg void OnCbnSelchangeRiderTypeCombo();
};
