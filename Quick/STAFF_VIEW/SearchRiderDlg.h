#pragma once
// CSearchRiderDlg 대화 상자입니다.

class CSearchRiderDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSearchRiderDlg)

public:
	CSearchRiderDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSearchRiderDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SEARCH_RIDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	
	void RefreshList();
	void SaveItem();

	CXTPListCtrl2 m_lstReport;
	CFlatEdit2 m_edtRNo;

	long m_nRiderCompany;
	long m_nRNo;	

	CString m_strSearch;
	CString m_strRName;
};
