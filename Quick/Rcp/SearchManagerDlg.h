#pragma once

class CRcpDlg;
// CSearchManagerDlg ��ȭ �����Դϴ�.

class CSearchManagerDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSearchManagerDlg)

public:
	CSearchManagerDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSearchManagerDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SEARCH_MANAGER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
