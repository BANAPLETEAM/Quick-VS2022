#pragma once


// CSmsRegisterManagerDlg ��ȭ �����Դϴ�.

class CSmsRegisterManagerDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSmsRegisterManagerDlg)

public:
	CSmsRegisterManagerDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSmsRegisterManagerDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SMS_REGISTER_MANAGER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	CString m_strJobTitle;
	CString m_strNumber;
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedCancelBtn();
};
