#pragma once


// CChargeChangeHelpDlg 대화 상자입니다.

class CChargeChangeHelpDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeChangeHelpDlg)

public:
	CChargeChangeHelpDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChargeChangeHelpDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHARGE_CHANGE_HELP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOkBtn();
	virtual BOOL OnInitDialog();

};
