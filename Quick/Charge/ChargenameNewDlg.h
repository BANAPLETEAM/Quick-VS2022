#pragma once


// CChargeNameNewDlg ��ȭ �����Դϴ�.

class CChargeNameNewDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeNameNewDlg)

public:
	CChargeNameNewDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CChargeNameNewDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHARGE_NAMENEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strChargeName;
	CString m_strChargeEtc;

	afx_msg void OnBnClickedOnokBtn();
	afx_msg void OnBnClickedCancelBtn();
};
