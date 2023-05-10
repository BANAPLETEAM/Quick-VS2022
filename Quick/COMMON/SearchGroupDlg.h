#pragma once


enum { SG_GROUP = 0, SG_DISCOUNT_COMPANY = 1};

// CSearchGroupDlg ��ȭ �����Դϴ�.

class CSearchGroupDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSearchGroupDlg)

public:
	CSearchGroupDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSearchGroupDlg();

	// ��ȭ ���� �������Դϴ�.
	//enum { IDD = IDD_SEARCH_GROUP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

protected:
	CXTPListCtrl2 m_List;
	CXTFlatEdit m_SearchEdit;
	//CString m_strSearch;
	CComboBox m_cmbSearchType;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeXtplistctrlCombo();
	afx_msg void OnEnChangeXtplistctrlEdit();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);

	void RefreshList();
protected:
	virtual void OnOK();

public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedServerRefreshBtn();

	CString m_strGroupName;
	CString m_strDeptName;
	CString m_strChargeName;
	CString m_strSearch;

	long m_nAutoSearch;
	long m_nGNo;
	int m_nDataType;
	int m_nCompany;
	int m_nChargeID;
};
