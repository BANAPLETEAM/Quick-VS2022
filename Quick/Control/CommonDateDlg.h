#pragma once
#include "afxdtctl.h"
#include "afxwin.h"
#include "atlcomtime.h"


// CCommonDateDlg 대화 상자입니다.

class CCommonDateDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCommonDateDlg)

public:
	CCommonDateDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCommonDateDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_COMMON_DATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOkBtn();
	virtual BOOL OnInitDialog();

	CButton m_chk1;
	CButton m_chk2;
	COleDateTime m_dtDate;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCancelBtn();
	CDateTimeCtrl m_DateDtp;
};
