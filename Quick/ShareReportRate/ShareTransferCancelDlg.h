#pragma once
#include "afxwin.h"

class CShareTranferRequestDlg;
// CShareTransferCancelDlg ��ȭ �����Դϴ�.

class CShareTransferCancelDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CShareTransferCancelDlg)

public:
	CShareTransferCancelDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CShareTransferCancelDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SHARE_TRANSFER_CANCEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CShareTranferRequestDlg * m_pParent;		 
	int m_nID;
	CEdit m_MemoEdt;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
