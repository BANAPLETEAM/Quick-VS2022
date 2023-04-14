#pragma once


// COtherAccountDlg 대화 상자입니다.

class COtherAccountDlg : public CMyDialog
{
	DECLARE_DYNAMIC(COtherAccountDlg)

public:
	COtherAccountDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COtherAccountDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_INPUT_OTHER_ACCOUNT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CString m_strAccount;

};
