#pragma once

// CEMailDlg ��ȭ �����Դϴ�.

class CEMailDlg : public CMyDialog
{ 
	DECLARE_DYNAMIC(CEMailDlg)

public:
	CEMailDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CEMailDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_EMAIL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	
	
public:
	CString m_strEMail;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
