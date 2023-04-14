#pragma once
#include "afxwin.h"


// CCommonDlg1 대화 상자입니다.

class CCommonDlg1 : public CMyDialog
{
	DECLARE_DYNAMIC(CCommonDlg1)

public:
	CCommonDlg1(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCommonDlg1();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_COMMON_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CFlatEdit2 m_edtEdit;
	CString m_strEdit;
	virtual BOOL OnInitDialog();
};
