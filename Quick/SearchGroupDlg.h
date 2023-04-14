#pragma once


enum { SG_GROUP = 0, SG_DISCOUNT_COMPANY = 1};

// CSearchGroupDlg 대화 상자입니다.

class CSearchGroupDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSearchGroupDlg)

public:
	CSearchGroupDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSearchGroupDlg();

	// 대화 상자 데이터입니다.
	//enum { IDD = IDD_SEARCH_GROUP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
