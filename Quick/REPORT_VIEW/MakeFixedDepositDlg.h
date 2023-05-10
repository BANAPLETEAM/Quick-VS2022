#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
//#include "MyRoundButton.h"

// CMakeFixedDepositDlg 대화 상자입니다.

class CMakeFixedDepositDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMakeFixedDepositDlg)

public:
	CMakeFixedDepositDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMakeFixedDepositDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MAKE_FIXED_DEPOSIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedCancelBtn();

	long m_nRiderCompany;
	long m_nRNo;
	CString m_strRName;

	CButton m_bntOk;
	CButton m_btnCancel;
	CFlatEdit2 m_edtEtc;
	CFlatEdit2 m_edtCharge;
	CDateTimeCtrl m_dtpDate;
};
