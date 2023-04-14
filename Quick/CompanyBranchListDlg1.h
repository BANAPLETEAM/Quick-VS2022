#pragma once

class CMoveOrderPaintManager;


// CCompanyBranchListDlg1 대화 상자입니다.

class CCompanyBranchListDlg1 : public CMyDialog
{
	DECLARE_DYNAMIC(CCompanyBranchListDlg1)

public:
	CCompanyBranchListDlg1(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCompanyBranchListDlg1();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_COMPANY_BRANCH_LIST_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
