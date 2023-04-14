#pragma once
#include "afxwin.h"


// CTestVirtualCIDDlg 대화 상자입니다.

class CTestVirtualCIDDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CTestVirtualCIDDlg)

public:
	CTestVirtualCIDDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTestVirtualCIDDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TEST_VIRTUAL_CID_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	afx_msg void OnBnClickedOk();
};
