#pragma once


// CSmsRegisterManagerDlg 대화 상자입니다.

class CSmsRegisterManagerDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSmsRegisterManagerDlg)

public:
	CSmsRegisterManagerDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSmsRegisterManagerDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SMS_REGISTER_MANAGER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	CString m_strJobTitle;
	CString m_strNumber;
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedCancelBtn();
};
