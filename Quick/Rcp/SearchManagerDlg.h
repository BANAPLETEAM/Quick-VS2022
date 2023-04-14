#pragma once

class CRcpDlg;
// CSearchManagerDlg 대화 상자입니다.

class CSearchManagerDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSearchManagerDlg)

public:
	CSearchManagerDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSearchManagerDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SEARCH_MANAGER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl2 m_List;
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	virtual BOOL OnInitDialog();

	long m_nCompany;
	long m_nCNo;

	CRcpDlg *m_pRcpDlg;
};
