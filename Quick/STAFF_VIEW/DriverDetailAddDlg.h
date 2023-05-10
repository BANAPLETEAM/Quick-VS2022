#pragma once


// CDriverDetailAddDlg 대화 상자입니다.

class CDriverDetailAddDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CDriverDetailAddDlg)

public:
	CDriverDetailAddDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDriverDetailAddDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DRIVER_DETAIL_NEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
