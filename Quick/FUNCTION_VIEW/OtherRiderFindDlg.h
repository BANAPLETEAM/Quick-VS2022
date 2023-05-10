#pragma once


// COtherRiderFindDlg 대화 상자입니다.

class COtherRiderFindDlg : public CDialog
{
	DECLARE_DYNAMIC(COtherRiderFindDlg)

public:
	COtherRiderFindDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COtherRiderFindDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_OTHER_RIDER_FIND_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	long m_nCompany;
	long m_nRNo;
	CString m_strName;
	CFlatEdit2 m_edtSearch;
	CXTPListCtrl2 m_lstReport;
	afx_msg void OnBnClickedSearchRiderBtn();
	afx_msg void OnBnClickedOkButton();
	afx_msg void OnBnClickedCancelButton();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
