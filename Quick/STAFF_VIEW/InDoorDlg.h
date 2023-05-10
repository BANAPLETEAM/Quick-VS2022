#pragma once
#include "afxwin.h"


class CInDoorDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CInDoorDlg)

public:
	CInDoorDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CInDoorDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_IN_DOOR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnBnClickedApplyInsuranceCheck();
	afx_msg void OnBnClickedNotApplyInsuranceCheck();
	afx_msg void OnBnClickedCloseButton();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedPwEditBtn();

	BOOL AddNewInDoor();
	BOOL UpdateUser();
	void InitData();
	void GetEtcEdit(CString &sEtc, CString &sEtcCharge);
	void SetEtcEdit(CString sEtc, CString sEtcCharge);
	BOOL CheckChangePw(BOOL bEdit = FALSE);

public:
	long m_nCompany;
	long m_nWNo;
	long m_nANo;

	CDateTimeCtrl m_EnterDT;
	CFlatEdit2 m_NameEdt;
	CFlatEdit2 m_SSNEdt1;
	CFlatEdit2 m_SSNEdt2;
	CComboBox m_WorkPartCmb;
	CFlatEdit2 m_WNoEdt;
	CFlatEdit2 m_BankNameEdt;
	CFlatEdit2 m_MpEdt;
	CFlatEdit2 m_BankAccountEdt;
	CFlatEdit2 m_IdEdt;
	CFlatEdit2 m_PhoneEdt;
	CFlatEdit2 m_BankOwnerEdt;
	CFlatEdit2 m_PwEdt;
	CFlatEdit2 m_AddressEdt;
	CFlatEdit2 m_MemoEdt;
	CComboBox m_WorkStateCmb;
	CComboBox m_WorkTypeCmb;
	CComboBox m_WagesTypeCmb;
	CFlatEdit2 m_WagesBasicEdt;
	CFlatEdit2 m_WagesAidEdt1;
	CFlatEdit2 m_WagesAidEdt2;
	CFlatEdit2 m_WagesAidEdt3;
	CFlatEdit2 m_WagesAidEdt4;
	CFlatEdit2 m_WagesAidChargeEdt1;
	CFlatEdit2 m_WagesAidChargeEdt2;
	CFlatEdit2 m_WagesAidChargeEdt3;
	CFlatEdit2 m_WagesAidChargeEdt4;
	CButton m_ApplyInsuranceChk;
	CButton m_NotApplyInsuranceChk;

	CButton m_KukminInsChk;
	CFlatEdit2 m_KukminInsEdt;
	CButton m_UryoInsChk;
	CFlatEdit2 m_UryoInsEdt;
	CButton m_SanjaeInsChk;
	CFlatEdit2 m_SanjaeInsEdt;
	CButton m_GoyongInsChk;
	CFlatEdit2 m_GoyongInsEdt;
	CButton m_GabkunInsChk;
	CFlatEdit2 m_GabkunInsEdt;
	CButton m_SoducInsChk;
	CFlatEdit2 m_SoducInsEdt;
	CButton m_JuminInsChk;
	CFlatEdit2 m_JuminInsEdt;
	CButton m_EtcInsEdt;
	CFlatEdit2 m_EtcInsFeeEdt;
	CFlatEdit2 m_InDoorMemo;
	CFlatEdit2 m_PositionEdt;
	CFlatEdit2 m_DtFeeEdt;
	BOOL m_bNewMode;

	BOOL m_WNoPageRefresh;
	long m_nWorkState;

	CButton m_SaveBtn;
	CFlatEdit2 m_edtInnerMemo;
	CFlatEdit2 m_edtAuthPhone;
	CComboBox m_cmbBranch;
	CString m_strPW;
};
