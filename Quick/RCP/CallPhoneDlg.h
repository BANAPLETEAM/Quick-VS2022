#pragma once


// CCallPhoneDlg 대화 상자입니다.
class CRcpView;

class CCallPhoneDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCallPhoneDlg)

public:
	CCallPhoneDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCallPhoneDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CALL_PHONE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
