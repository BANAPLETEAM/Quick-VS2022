#pragma once


// CCustomerCacheInfoDlg ��ȭ �����Դϴ�.

class CCustomerCacheInfoDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCustomerCacheInfoDlg)

public:
	CCustomerCacheInfoDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCustomerCacheInfoDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CUSTOMER_CACHE_INFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRemakeBtn();
};
