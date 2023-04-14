#pragma once


// CCustomerCacheInfoDlg 대화 상자입니다.

class CCustomerCacheInfoDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCustomerCacheInfoDlg)

public:
	CCustomerCacheInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCustomerCacheInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CUSTOMER_CACHE_INFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRemakeBtn();
};
