#pragma once
#include "afxwin.h"


// CWorkStopMemoDlg 대화 상자입니다.

class CWorkStopMemoDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CWorkStopMemoDlg)

public:
	CWorkStopMemoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWorkStopMemoDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_WORKSTOP_MEMO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedWorkstopButton();

	CString m_strWorkStopMemo;
	CString m_strContent;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CComboBox m_cmbWorkStopMemo;
	CEdit m_edtContent;
	afx_msg void OnBnClickedCancelButton();
	afx_msg void OnBnClickedWorkstopButton2();
};
