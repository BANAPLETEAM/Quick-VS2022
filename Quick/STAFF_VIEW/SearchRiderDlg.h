#pragma once
// CSearchRiderDlg ��ȭ �����Դϴ�.

class CSearchRiderDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSearchRiderDlg)

public:
	CSearchRiderDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSearchRiderDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SEARCH_RIDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
