#pragma once


// CRiderInitLogDlg ��ȭ �����Դϴ�.

class CRiderInitLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderInitLogDlg)

public:
	CRiderInitLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRiderInitLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RIDER_INIT_LOG_DLG };

protected:
	BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl2 m_lstReport;
	void RefreshList();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	long m_nCompany;
	long m_nRNo;

};
