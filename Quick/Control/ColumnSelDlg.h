#pragma once

// CColumnSelDlg ��ȭ �����Դϴ�.

class CColumnSelDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CColumnSelDlg)

public:
	CColumnSelDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CColumnSelDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COLUMN_SEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
