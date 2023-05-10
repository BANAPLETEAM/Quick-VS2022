#pragma once


// CEtcDlg 대화 상자입니다.

class CEtcDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CEtcDlg)

public:
	CEtcDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CEtcDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ETC_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strEtc;
	CString m_strTitle;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
