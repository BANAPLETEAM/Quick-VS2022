#pragma once


// CCallPhoneDlg ��ȭ �����Դϴ�.
class CRcpView;

class CCallPhoneDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCallPhoneDlg)

public:
	CCallPhoneDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCallPhoneDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CALL_PHONE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_List;
	CRcpView *m_pRcpView;

	CString m_strPhone;
	CString m_strDeviceID;
	CString m_strHomePhone;
	CString m_strCompanyPhone;
	CString m_strOfficePhone;
	long m_nOrderCompany;

public:
	void RefreshList();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
};
