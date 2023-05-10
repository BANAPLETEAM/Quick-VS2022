#pragma once
#include "afxwin.h"

// CPasswordDlg 대화 상자입니다.

class CPasswordDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CPasswordDlg)

public:
	CPasswordDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPasswordDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CFlatEdit2 m_edtOriPW;
	CFlatEdit2 m_edtNewPW;
	CFlatEdit2 m_edtPWEdit2;

	CString m_strOriPW;
	CString m_strNewPW1;
	CString m_strNewPW2;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
