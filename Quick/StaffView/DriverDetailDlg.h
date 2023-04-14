#pragma once

// CDriverDetailDlg 대화 상자입니다.
typedef struct 
{
	int nID;
	int nCompany;
	COleDateTime dtRegister;
	int nRNo;
	CString sContent;
	CString sReward;
	int nRewardType;
}RIDER_DETAIL_INFO;

class CDriverDetailDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CDriverDetailDlg)

public:
	CDriverDetailDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDriverDetailDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DRIVER_DETAIL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strCompanyNum;
	CString m_strPart;
	CString m_strID;
	CString m_strName;
	CString m_strDailyMemo;
	int m_nDailyPay;
	CDateTimeCtrl m_Date;
	CDateTimeCtrl m_Time;
	
	CString m_strCustomer;
	CString m_strTitle;
	CString m_strContent;
	CListCtrl m_List;
	
	afx_msg void OnBnClickedIdok();
	virtual BOOL OnInitDialog();
	void InitControl(void);
	int m_nCompany;
	int m_nRNo;
	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnBnClickedIdcancel();
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	
	int m_nInsentiveEdit;
	void RefreshList();
	BOOL CheckData();
	COleDateTime m_dtTime;
	COleDateTime m_dtDate;
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonDelete();

	CComboBox m_cmbReward;
	CButton m_chkPersonApply;

	CButton m_btnOk;
	CButton m_btnCanCel;
	CButton m_btnNew;
	CButton m_btnModify;
	CButton m_btnDel;

	CMyStatic m_Static1;
	CMyStatic m_Static2;
	CMyStatic m_Static3;
	CMyStatic m_Static4;
	CMyStatic m_Static5;
	CMyStatic m_Static6;
	CMyStatic m_Static7;
	CMyStatic m_Static8;
	CMyStatic m_Static9;
	CMyStatic m_Static10;

	afx_msg void OnLvnDeleteallitemsList(NMHDR *pNMHDR, LRESULT *pResult);
};
