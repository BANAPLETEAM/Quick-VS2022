#pragma once
#include "afxdtctl.h"
#include "atlcomtime.h"


// CCommonDateDlg2 ��ȭ �����Դϴ�.

class CCommonDateDlg2 : public CMyDialog
{
	DECLARE_DYNAMIC(CCommonDateDlg2)

public:
	CCommonDateDlg2(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCommonDateDlg2();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COMMON_DATE_DLG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedOkBtn();
	CDateTimeCtrl m_DateCtrl;
	COleDateTime m_Date;
};
