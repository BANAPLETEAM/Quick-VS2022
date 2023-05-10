#pragma once


// CSmsRegisterLogDlg 대화 상자입니다.

class CSmsRegisterLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSmsRegisterLogDlg)

public:
	CSmsRegisterLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSmsRegisterLogDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SMS_REGISTER_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	CXTPListCtrl2 m_lstLogList;

public:
	virtual BOOL OnInitDialog();
	void RefreshLogList();

	long m_nCompany;
	long m_nTelNo;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
