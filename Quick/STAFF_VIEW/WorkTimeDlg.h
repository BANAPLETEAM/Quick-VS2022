#pragma once
#include "afxdtctl.h"


// CWorkTimeDlg ��ȭ �����Դϴ�.

class CWorkTimeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CWorkTimeDlg)

public:
	CWorkTimeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CWorkTimeDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_WORK_TIME_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	COleDateTime m_dtStartTime;
	COleDateTime m_dtEndTime;
	afx_msg void OnBnClickedCancel();
};
