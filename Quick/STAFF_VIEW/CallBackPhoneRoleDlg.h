#pragma once


// CCallBackPhoneRoleDlg ��ȭ �����Դϴ�.

class CCallBackPhoneRoleDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCallBackPhoneRoleDlg)

public:
	CCallBackPhoneRoleDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCallBackPhoneRoleDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CALL_BACK_PHONE_ROLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
