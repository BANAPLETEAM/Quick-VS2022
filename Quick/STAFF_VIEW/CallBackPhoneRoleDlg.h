#pragma once


// CCallBackPhoneRoleDlg 대화 상자입니다.

class CCallBackPhoneRoleDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCallBackPhoneRoleDlg)

public:
	CCallBackPhoneRoleDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCallBackPhoneRoleDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CALL_BACK_PHONE_ROLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
