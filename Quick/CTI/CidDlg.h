#pragma once


// CCidDlg 대화 상자입니다.

class CCidDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCidDlg)

public:
	CCidDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCidDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CID_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CXTPListCtrl2 m_List;

	void OpenPreDlg();
	void OpenNewDlg();
	void RefreshList();
	BOOL SetClipboardText(const CString strData);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOpenPreBtn();
	afx_msg void OnBnClickedOpenNewBtn();
	afx_msg void OnEnChangeSearchEdit();
	CEdit m_edtSearch;
};
