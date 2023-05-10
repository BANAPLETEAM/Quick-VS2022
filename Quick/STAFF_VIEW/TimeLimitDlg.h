#pragma once
#include "afxdtctl.h"
#include "afxwin.h"


// CTimeLimitDlg ��ȭ �����Դϴ�.

class CTimeLimitDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CTimeLimitDlg)

public:
	CTimeLimitDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTimeLimitDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TIME_LIMIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime m_dtLimitDate;
	COleDateTime m_dtLimitTime;
	COleDateTime m_dtDate;
	CComboBox m_cmbTimeLimit;
	CString m_sMinute;
	afx_msg void OnBnClickedOkBtn();
	virtual BOOL OnInitDialog();
};
