#pragma once


// CWebIDPWDDlg ��ȭ �����Դϴ�.

class CWebIDPWDDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CWebIDPWDDlg)

public:
	//CWebIDPWDDlg();   // ǥ�� �������Դϴ�.
	CWebIDPWDDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CWebIDPWDDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_NOMEMBER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	
public:
	long		m_nTNo;
	int			m_nType;
	long		m_nCNo;
	long		m_nCompany;	
	CString		m_strWebID;
	CString		m_strWebPWD;
	CString		m_strPhone;
	CString		m_strWebAddress;
	
	CFlatEdit2	m_edtTNo;
	CFlatEdit2  m_edtWebID;
	CFlatEdit2  m_edtWebPWD;

	virtual BOOL OnInitDialog();
	void GetOrderData(long nTNo, long nCompany);
	afx_msg void OnBnClickedWebSiteWindow();
	afx_msg void OnBnClickedNomemberSendSMS();
	afx_msg void OnBnClickedCancel();

	void Clear();
	BOOL CheckData();
};
