#pragma once
#include "afxwin.h"

// CRemoteAddrDlg 대화 상자입니다.

class CRemoteAddrDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRemoteAddrDlg)

public:
	CRemoteAddrDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRemoteAddrDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_REMOTE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CComboBox m_cmbRemote;
	int m_nApplyRemote;
	afx_msg void OnBnClickedButton1();
};
