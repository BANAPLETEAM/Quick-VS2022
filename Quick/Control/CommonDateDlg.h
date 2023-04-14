#pragma once
#include "afxdtctl.h"
#include "afxwin.h"
#include "atlcomtime.h"


// CCommonDateDlg ��ȭ �����Դϴ�.

class CCommonDateDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCommonDateDlg)

public:
	CCommonDateDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCommonDateDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COMMON_DATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
