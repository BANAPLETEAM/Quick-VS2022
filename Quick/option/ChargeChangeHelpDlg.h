#pragma once


// CChargeChangeHelpDlg ��ȭ �����Դϴ�.

class CChargeChangeHelpDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeChangeHelpDlg)

public:
	CChargeChangeHelpDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CChargeChangeHelpDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHARGE_CHANGE_HELP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOkBtn();
	virtual BOOL OnInitDialog();

};
