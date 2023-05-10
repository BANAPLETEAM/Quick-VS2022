#pragma once


// CChangeHistoryNameDlg 대화 상자입니다.

class CChangeHistoryNameDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChangeHistoryNameDlg)

public:
	CChangeHistoryNameDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChangeHistoryNameDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHANGE_HISTORY_NAME_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()


	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedCancelBtn();
public:
	CString m_sChargeName;
	CString m_sChargeEtc;
};
