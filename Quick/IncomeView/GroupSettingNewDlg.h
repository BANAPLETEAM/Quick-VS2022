#pragma once

class CGroupSettingNewDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CGroupSettingNewDlg)

public:
	CGroupSettingNewDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGroupSettingNewDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GROUP_SETTING_NEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:

	CXTPListCtrl2 	m_lstJob;
	CXTPListCtrl31 	m_lstInclude;
	CXTPListCtrl31 	m_lstNotInclude;

	int	m_nCompany;
	int m_bIntegrated;	
	long m_nScheduleID;

	BOOL m_bFirst;
public:
	void RefreshJobList();
	void RefreshIncludeList();
	void RefreshNotIncludeList();
	afx_msg void OnReportItemClick(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnBnClickedGroupInButton();
	afx_msg void OnBnClickedGroupOutButton();
	afx_msg void OnBnClickedCancelButton();
};
