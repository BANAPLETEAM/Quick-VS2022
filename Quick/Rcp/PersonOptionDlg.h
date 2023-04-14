#pragma once
#include "afxwin.h"


// CPersonOptionDlg 대화 상자입니다.

class CPersonOptionDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CPersonOptionDlg)

public:
	CPersonOptionDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPersonOptionDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PERSON_OPTION_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOrderFinishCheck();
	CButton m_chkAutoFinish;
	
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedButton1();
	CButton m_chkAutoAllocate;
	afx_msg void OnBnClickedAutoAlocateCheck();
};
