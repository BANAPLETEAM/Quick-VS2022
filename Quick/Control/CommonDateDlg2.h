#pragma once
#include "afxdtctl.h"
#include "atlcomtime.h"


// CCommonDateDlg2 대화 상자입니다.

class CCommonDateDlg2 : public CMyDialog
{
	DECLARE_DYNAMIC(CCommonDateDlg2)

public:
	CCommonDateDlg2(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCommonDateDlg2();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_COMMON_DATE_DLG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedOkBtn();
	CDateTimeCtrl m_DateCtrl;
	COleDateTime m_Date;
};
