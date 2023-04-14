#pragma once


// CWebIDPWDDlg 대화 상자입니다.

class CWebIDPWDDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CWebIDPWDDlg)

public:
	//CWebIDPWDDlg();   // 표준 생성자입니다.
	CWebIDPWDDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWebIDPWDDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_NOMEMBER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
