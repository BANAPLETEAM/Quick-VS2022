#pragma once
#include "afxwin.h"

class CShareTranferRequestDlg;
// CShareTransferCancelDlg 대화 상자입니다.

class CShareTransferCancelDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CShareTransferCancelDlg)

public:
	CShareTransferCancelDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CShareTransferCancelDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SHARE_TRANSFER_CANCEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CShareTranferRequestDlg * m_pParent;		 
	int m_nID;
	CEdit m_MemoEdt;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
