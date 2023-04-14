#pragma once

#include "Explorer.h"
#include "afxwin.h"

// CHomeForm1 대화 상자입니다.
class CHomeForm1 : public CMyFormView
{
	DECLARE_DYNCREATE(CHomeForm1)

public:
	CHomeForm1();   // 표준 생성자입니다.
	virtual ~CHomeForm1();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_HOME_FORM1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();

	DECLARE_MESSAGE_MAP()

public:
	void RefreshList();

protected:
	
public:
	CBitmapButton m_RefeshBtn;
	CBitmapButton m_ForwardBtn;
	CBitmapButton m_BackBtn;
	CButton m_btnChangeMainPage;
	CString m_sBranchName;
	CString m_sCompany;

	HRESULT GetPostData(CString strKey, LPVARIANT pvPostData);
	afx_msg void OnBnClickedRefreshButton();
	afx_msg void OnBnClickedAfterButton();
	afx_msg void OnBnClickedBackButton();
	DECLARE_EVENTSINK_MAP()
	void CommandStateChangeExplorer(long Command, BOOL Enable);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	CWinThread* m_hThreadCom;
public:
	int GetSumIntegrated();
	CExplorer m_Explorer;
	afx_msg void OnBnClickedToMainButton();
};
