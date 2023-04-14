#pragma once
#include "afxwin.h"


// CUpChargeSetDlg 대화 상자입니다.

class CUpChargeSetDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CUpChargeSetDlg)

public:
	CUpChargeSetDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUpChargeSetDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_UP_CHARGE_SET_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CButton m_chkUseTimeSet;

	long m_nCompany;
	void RefreshDlg();
	void SetCombo(long nTime, UINT nID);
	BOOL CheckControl();
	long GetCombo(UINT nID);
};
