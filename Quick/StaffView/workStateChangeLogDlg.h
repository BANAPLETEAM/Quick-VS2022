#pragma once


// CWorkStateChangeLogDlg 대화 상자입니다.

class CWorkStateChangeLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CWorkStateChangeLogDlg)

public:
	CWorkStateChangeLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWorkStateChangeLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WORK_STATE_CHANGE_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	long m_nRiderCompany;
	long m_nRNo;

	CXTPListCtrl2 m_lstReport;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;

	CDateButton m_btnDate;
	virtual BOOL OnInitDialog();
	void RefreshList(BOOL bAll);
	afx_msg void OnBnClickedRefreshAllBtn();
	afx_msg void OnEnChangeSearchEdit();
};
