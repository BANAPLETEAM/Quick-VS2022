#pragma once


// CChargeMemberDlg ��ȭ �����Դϴ�.

class CChargeMemberDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeMemberDlg)

public:
	CChargeMemberDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CChargeMemberDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHARGE_MEMER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedYes();
	afx_msg void OnBnClickedNo();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();

	CFlatEdit2 m_edtChargeName;

	int m_nReturn;
	CString m_strChargeName;
	CString m_strEtc;
};
