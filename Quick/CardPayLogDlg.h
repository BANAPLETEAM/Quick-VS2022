#pragma once


// CCardPayLogDlg 대화 상자입니다.

class CCardPayLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCardPayLogDlg)

public:
	CCardPayLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCardPayLogDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_CARD_PAY_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	long m_nTNo;

	CXTPListCtrl2 m_lstReport;
	virtual BOOL OnInitDialog();

	void RefreshList();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
