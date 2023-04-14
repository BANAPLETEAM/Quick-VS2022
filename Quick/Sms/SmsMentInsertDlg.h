#pragma once

class CEmoticonDlg;
// CSmsMentInsertDlg 대화 상자입니다.

class CSmsMentInsertDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSmsMentInsertDlg)

public:
	CSmsMentInsertDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSmsMentInsertDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SMS_MENT_INSERT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedMent1Btn();
	afx_msg void OnBnClickedMent2Btn();
	afx_msg void OnBnClickedMent3Btn();
	afx_msg void OnBnClickedMent4Btn();
	afx_msg void OnBnClickedMent5Btn();
	afx_msg void OnBnClickedMent6Btn();
	afx_msg void OnBnClickedMent7Btn();
	afx_msg void OnBnClickedMent8Btn();
	afx_msg void OnBnClickedMent9Btn();
	afx_msg void OnBnClickedMent10Btn();

	afx_msg void OnBnClickedSpecialCharBtn();
	afx_msg void OnBnClickedEmoticonBtn();
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnBnClickedCloseBtn();

	afx_msg LONG OnSendEmoticon(UINT nBranch, LPARAM lParam);
	afx_msg	void OnEnChangeMentEdit();
public:
	CEmoticonDlg *m_pEmoticonDlg;
	long m_nType;
	CEdit m_edtMent;
	CBitmapButton m_btnSmsMms;
	CMyStatic m_stcByte;
	CString m_strMent;

	void DisplayByte();
	void AddText(UINT nFlag, CString strAddText = "");
};
