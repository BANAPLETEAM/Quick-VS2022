#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CAddRcpNoticeDlg ��ȭ �����Դϴ�.

class CAddRcpNoticeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAddRcpNoticeDlg)

public:
	CAddRcpNoticeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAddRcpNoticeDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ADD_RCP_NOTICE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRevNoticeCheck();

public:
	CString m_strNotice;
	CButton m_chkRevNotice;

	BOOL m_bReadOnly;
	BOOL m_bRevNotice;

	CDateTimeCtrl m_dtpRevDate;
	CDateTimeCtrl m_dtpRevTime;
	COleDateTime m_dtRevDate;
	COleDateTime m_dtRevTime;

	COleDateTime m_dtRevDateTime;
	//CFlatEdit2 m_edtNotice;
	CEdit m_edtNotice;
};
