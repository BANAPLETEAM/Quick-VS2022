#pragma once

// CEMailDlg 대화 상자입니다.

class CEMailDlg : public CMyDialog
{ 
	DECLARE_DYNAMIC(CEMailDlg)

public:
	CEMailDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CEMailDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_EMAIL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	
	
public:
	CString m_strEMail;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
