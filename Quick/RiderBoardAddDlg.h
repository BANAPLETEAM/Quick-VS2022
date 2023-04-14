#pragma once


// CRiderBoardAddDlg 대화 상자입니다.

class CRiderBoardAddDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderBoardAddDlg)

public:
	CRiderBoardAddDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderBoardAddDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_BOARD_ADD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	
public:
	CString m_strTitle;
	CString m_strMemo;
	BOOL m_bShow;
	long m_nIndex;
public:
	virtual BOOL OnInitDialog();
	void RefreshDlg();
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedCancelBtn();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
