#pragma once


// CRiderInitLogDlg 대화 상자입니다.

class CRiderInitLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderInitLogDlg)

public:
	CRiderInitLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderInitLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_INIT_LOG_DLG };

protected:
	BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl2 m_lstReport;
	void RefreshList();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	long m_nCompany;
	long m_nRNo;

};
