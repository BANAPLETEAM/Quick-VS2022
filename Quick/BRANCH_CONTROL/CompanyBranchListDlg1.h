#pragma once

class CMoveOrderPaintManager;


// CCompanyBranchListDlg1 ��ȭ �����Դϴ�.

class CCompanyBranchListDlg1 : public CMyDialog
{
	DECLARE_DYNAMIC(CCompanyBranchListDlg1)

public:
	CCompanyBranchListDlg1(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCompanyBranchListDlg1();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COMPANY_BRANCH_LIST_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CMoveOrderPaintManager *m_MyPaintManager;
	CXTPGridControl m_Report;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOk();

	void RefreshList();
	long GetColumnCount();
	long m_nOneColumnAbleCount;
	long m_nRowCount;
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	BOOL m_bCopy;
	CBranchInfo *m_pBi;
	CButton m_chkCopy;
	BOOL m_bCorpOrder;
};
