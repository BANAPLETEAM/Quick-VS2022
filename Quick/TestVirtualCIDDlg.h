#pragma once
#include "afxwin.h"


// CTestVirtualCIDDlg ��ȭ �����Դϴ�.

class CTestVirtualCIDDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CTestVirtualCIDDlg)

public:
	CTestVirtualCIDDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTestVirtualCIDDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TEST_VIRTUAL_CID_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	afx_msg void OnBnClickedOk();
};
