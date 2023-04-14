#pragma once
#include "afxdtctl.h"

// CDateSelectDlg ��ȭ �����Դϴ�.

class CDateSelectDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CDateSelectDlg)

public:
	CDateSelectDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDateSelectDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DATE_SELECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strTitle;
	BOOL m_bAllocate;
	COleDateTime m_dtLastAllocate;

	COleDateTime m_dtDateTime;

	CDateTimeCtrl m_ctpDt;
	CDateTimeCtrl m_ctpTime;
	COleDateTime m_dtDate;
	COleDateTime m_dtTime;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
};
