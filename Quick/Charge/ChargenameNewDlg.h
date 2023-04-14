#pragma once


// CChargeNameNewDlg 대화 상자입니다.

class CChargeNameNewDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeNameNewDlg)

public:
	CChargeNameNewDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChargeNameNewDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHARGE_NAMENEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strChargeName;
	CString m_strChargeEtc;

	afx_msg void OnBnClickedOnokBtn();
	afx_msg void OnBnClickedCancelBtn();
};
