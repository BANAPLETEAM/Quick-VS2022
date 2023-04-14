#pragma once


// CSimpleSearchDlg ��ȭ �����Դϴ�.

class CSimpleSearchDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSimpleSearchDlg)

public:
	CSimpleSearchDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSimpleSearchDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SIMPLESEARCH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	long m_nCompany;
	BOOL m_bIntegrated;
	CListCtrl m_List;
	CFlatEdit2 m_edtCompany;
	CFlatEdit2 m_edtManager;
	CFlatEdit2 m_edtStart;
	CFlatEdit2 m_edtDCompany;
	CFlatEdit2 m_edtRName;
	CFlatEdit2 m_edtDest;
	CFlatEdit2 m_edtNTNO;	

	CMyStatic m_stcBranch;
	CMyStatic m_stcCompany;
	CMyStatic m_stcManager;
	CMyStatic m_stcStart;
	CMyStatic m_stcDCompany;
	CMyStatic m_stcRName;
	CMyStatic m_stcDest;
	CMyStatic m_stcNTNO;
	

	CString m_sTNo;
	CString m_sCompany;
	CString m_sManager;
	CString m_sStart;
	CString m_sDCompany;
	CString m_sRName;
	CString m_sDest;
	virtual BOOL OnInitDialog();
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void RefreshList(int nSearch);
	CComboBox m_cmbBranch;
	afx_msg void OnBnClickedButton1();
	
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);

	long m_nTNo;
	long m_nState;
	CString m_sCName;
};
