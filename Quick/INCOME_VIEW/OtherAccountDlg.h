#pragma once


// COtherAccountDlg ��ȭ �����Դϴ�.

class COtherAccountDlg : public CMyDialog
{
	DECLARE_DYNAMIC(COtherAccountDlg)

public:
	COtherAccountDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~COtherAccountDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_INPUT_OTHER_ACCOUNT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	CString m_strAccount;

};
