#pragma once


// COptionTipDlg 대화 상자입니다.

class COptionTipDlg : public CDialog
{
	DECLARE_DYNAMIC(COptionTipDlg)

public:
	COptionTipDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COptionTipDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_OPTION_TIP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
};
