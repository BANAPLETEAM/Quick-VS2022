#pragma once

//#include "IncomeForm5.h"
#include "DepositStateButton.h"

class CRiderDepositInfoDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderDepositInfoDlg)

public:
	CRiderDepositInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderDepositInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_DEPOSIT_INFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeIncomeDayCombo1();
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnBnClickedMinusBtn();
	afx_msg void OnBnClickedClearDepositBtn();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedMakeFixedepositBtn();
	afx_msg void OnBnClickedDeleteFixedDepositBtn();
	afx_msg void OnBnClickedHalfInsertFixedepositBtn();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedIncomeCompleteBtn();
	afx_msg void OnBnClickedReportCompleteBtn();
	afx_msg void OnBnClickedNotReportBtn();
	afx_msg void OnCbnSelchangeDepositTypeCombo1();
	afx_msg void OnBnClickedRiderCreditBtn();
	afx_msg void OnBnClickedPercentRadio();
	afx_msg void OnBnClickedMonthRadio(); 
	afx_msg void OnCbnSelchangeDepositAllocateTypeCombo();
	afx_msg void OnBnClickedHelpBtn();
	afx_msg void OnBnClickedEditLogBtn();
	afx_msg void OnBnClickedMyCallRateTypeBtn();
	afx_msg void OnBnClickedOtherCallRateTypeBtn();
	afx_msg void OnBnClickedMycallCheck();
	afx_msg void OnBnClickedOthercallCheck();

	void InitRiderState();
	void RefreshFixedList();
	void OpenRiderReportDlg();
	void MakeFile(CString sHtml,CString sFileName);
	void SetEtcEdit(CString strEtc, CString strEtcCharge);
	void GetEtcEdit(CString &strEtc, CString &strEtcCharge);
	void InitControl();
	void DTChangeControl();

	ST_RIDER_INFO_INCOME m_stRiderInfo;
	CXTPListCtrl11 m_wndFixedReport;
	
	CDepositStateButton m_btnChange;

	CButton m_btnHalfInsertFixedDeposit;
	CButton m_btnMakeFixedDeposit;
	CButton m_btnDeleteFixedDeposit;
	CButton m_btnSave;
	CButton m_btnMinus;
	CButton m_btnClearDepositBtn;
	CButton m_btnEditlog;
	CButton m_btnMyCallRate;
	CButton m_btnOtherCallRate;
	CButton m_rdoPercent;
	CButton m_rdoMonth;
	
	CButton m_chkMyCall;
	CButton m_chkOtherCall;
	CButton m_chkUseSMS;
	CButton m_chkBranchAsOther;
	CButton m_chkPenalty;

	CFlatEdit2 m_edtFixDeposit;
	CFlatEdit2 m_edtDepositExpension;
	CFlatEdit2 m_edtCashFee;
	CFlatEdit2 m_edtMyCallCreditFee;
	CFlatEdit2 m_edtOtherCallCreditFee;
	CFlatEdit2 m_edtAllocMinCharge;
	CFlatEdit2 m_edtFee1;
	CFlatEdit2 m_edtFee2;
	CFlatEdit2 m_edtFee3;
	CFlatEdit2 m_edtFee4;
	CFlatEdit2 m_edtFee5;
	CFlatEdit2 m_edtFee6;
	CFlatEdit2 m_edtCharge1;
	CFlatEdit2 m_edtCharge2;
	CFlatEdit2 m_edtCharge3;
	CFlatEdit2 m_edtCharge4;
	CFlatEdit2 m_edtCharge5;
	CFlatEdit2 m_edtCharge6;
	CFlatEdit2 m_edtDTCashDeeMonth;
	CFlatEdit2 m_edtMyCallRateType;
	CFlatEdit2 m_edtOtherCallRateType;
	CFlatEdit2 m_edtEtcRe1;
	CFlatEdit2 m_edtEtcRe2;
	CFlatEdit2 m_edtEtcRe3;
	CFlatEdit2 m_edtEtcRe4;
	CFlatEdit2 m_edtEtcReCharge1;
	CFlatEdit2 m_edtEtcReCharge2;
	CFlatEdit2 m_edtEtcReCharge3;
	CFlatEdit2 m_edtEtcReCharge4;

	CComboBox m_cmbIncomeDay1;
	CComboBox m_cmbIncomeDay2;
	CComboBox m_cmbreditReportType;
	CComboBox m_cmbFeeType1;
	CComboBox m_cmbFeeType2;
	CComboBox m_cmbFeeType3;
	CComboBox m_cmbFeeType4;
	CComboBox m_cmbFeeType5;
	CComboBox m_cmbFeeType6;
	CComboBox m_cmbDepositType;
	CComboBox m_cmbDTCashType;
	CComboBox m_cmbDTCashWon;
	CComboBox m_cmbDTMyCallCreditType;
	CComboBox m_cmbDTMyCallCreditWon;
	CComboBox m_cmbDTOtherCallCreditType;
	CComboBox m_cmbDTOtherCallCreditWon;
	CComboBox m_cmbSmsDelayDay;
	CComboBox m_cmbDepositAllocateType;
	CComboBox m_cmbRiderIncomeDay1;
	CComboBox m_cmbRiderIncomeDay2;

	CStatic m_stcCurCharge;
	CStatic m_stcState;	
	
	long m_nPreDepositAllocateType;
	long m_nRiderCompany;
	long m_nRNo;

	CString m_strMyCallRateType;
	CString m_strOtherCallRateType;
	CString m_strFixedCharge;	
	CString m_strRName;
};
