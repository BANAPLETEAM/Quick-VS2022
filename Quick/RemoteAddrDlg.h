#pragma once
#include "afxwin.h"

// CRemoteAddrDlg ��ȭ �����Դϴ�.

class CRemoteAddrDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRemoteAddrDlg)

public:
	CRemoteAddrDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRemoteAddrDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_REMOTE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CComboBox m_cmbRemote;
	int m_nApplyRemote;
	afx_msg void OnBnClickedButton1();
};
