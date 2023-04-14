#pragma once

// CColumnSelDlg 대화 상자입니다.

class CColumnSelDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CColumnSelDlg)

public:
	CColumnSelDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CColumnSelDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_COLUMN_SEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_sClass;
	CString m_sList;

	CXTPGridControl *m_plstReport;
	CXTPListCtrl2 m_lstColumn;
	virtual BOOL OnInitDialog();
	void RefreshList();
	afx_msg void OnBnClickedOk();
};
