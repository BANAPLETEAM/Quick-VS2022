#pragma once


// CNewCertifyDlg 대화 상자입니다.

class CNewCertifyDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CNewCertifyDlg)

public:
	CNewCertifyDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CNewCertifyDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_NEW_CERTIFY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRecvBtn();
	afx_msg void OnBnClickedCertifyBtn();

public:
	CEdit m_edtID;
	CEdit m_edtPW;
	CEdit m_edtRecvPhone;
	CButton m_chkManager;
	CEdit m_edtCertify;
	CButton m_btnCertify;
	CEdit m_edtPCNum;
	CButton m_btnRecv;

	CString m_strID;
	CString m_strPW;
	CString m_strRecvPhone;
	BOOL m_bManager;
	CString m_strCertify;
	CString m_strPCNum;

	long m_nLogNo;

	virtual BOOL OnInitDialog();
	void RefreshPCNum();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnOK();
};
