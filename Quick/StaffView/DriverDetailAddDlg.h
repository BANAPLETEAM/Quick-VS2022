#pragma once


// CDriverDetailAddDlg ��ȭ �����Դϴ�.

class CDriverDetailAddDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CDriverDetailAddDlg)

public:
	CDriverDetailAddDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDriverDetailAddDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DRIVER_DETAIL_NEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime m_dtDate;
	COleDateTime m_dtTime;
	
	CString		m_strCustomer;
	CComboBox m_cmbReward;
	CComboBox	m_FixedCombo;
	
	CString		m_strTitle;
	CString		m_strContent;

	CMyStatic m_Static1;
	CMyStatic m_Static2;
	CMyStatic m_Static3;
	CMyStatic m_Static4;
	CMyStatic m_Static5;

	CFlatEdit2 m_edtCustomer;
	CFlatEdit2 m_edtContent;

	CButton m_btnConfirm;
	CButton m_btnCancel;

	int m_nCompany;
	int m_nRNo;
	afx_msg void OnBnClickedConfirmButton();
	virtual BOOL OnInitDialog();
	BOOL CheckData(void);
	
	long m_nCustomerNO;
		
	afx_msg void OnBnClickedCancelButton();
		
	CDateTimeCtrl m_dtpTime;
	
};
