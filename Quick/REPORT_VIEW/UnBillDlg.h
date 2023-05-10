#pragma once


// CUnBillDlg 대화 상자입니다.

class CUnBillDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CUnBillDlg)

public:
	CUnBillDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUnBillDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_UNBILL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnTaxAccount();
	afx_msg void OnIncome();
	afx_msg void OnOrderSee();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedPrintBtn();
	afx_msg void OnBnClickedOpenTreeCheck();

	virtual BOOL OnInitDialog();
	void RefreshList();
	void OnReGroupReport();
	void OnDeleteGroupReport();
	void OnPayIncome();
	void OnPayCancel();
	void OnPayEnd();
	void OnReportDelete();
	void OnViewExcel();
	void OnPayInComeCancel();
	void OnPayEndCancel();
	void InputCancel(int nType );
	CXTPGridControl12 m_lstReport;

	CButton m_chkOpenTree;

	long m_nGNo;
	long m_nID;
	BOOL m_bAll;
	BOOL m_bChangeItem;	
	BOOL m_bAlone; //그룹 재정산,삭제, 추가 등에서 불러올때 끌려고 있는 맴버함수	
};
