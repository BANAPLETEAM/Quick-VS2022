#pragma once
#include "afxwin.h"



// CReportForm1 대화 상자입니다.
class CReportForm1 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm1)

public:
	CReportForm1();   // 표준 생성자입니다.
	virtual ~CReportForm1();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_REPORT1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();
	virtual void OnCancel();
	virtual void OnOK();

	void RefreshList();
	
	void RefreshGroup();
	void InitColumn(BOOL bGroup);
	void OnPrint();
	void SearchCustomer(BOOL bClickGroup = FALSE);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportColumnRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportSelChange(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedVerifyBtn();
	afx_msg void OnBnClickedFindBtn();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedOneSearchBtn();
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedGroupSearch();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewExcel();
	afx_msg void OnVisibleCol();

	DECLARE_MESSAGE_MAP()

public:
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;

	CXTPListCtrl2 m_List;
	CXTPListCtrl2 m_CustomerList;

	CComboBox m_TypeCombo;
	CComboBox m_GroupCombo;

	CMyStatic m_CNoStatic;
	CFlatEdit2 m_SearchEdit;
	CDateButton m_DateBtn;

	CMyStatic m_Static1;
	CMyStatic m_Static2;
	CMyStatic m_Static3;
	CMyStatic m_Static4;
	CMyStatic m_Static5;
	CMyStatic m_Static6;

	CButton m_OneSearchBtn;
	CButton m_btnFind;
	CButton m_SearchBtn;
	CButton m_GroupSearchBtn;

	CFlatEdit2 m_edtCash;
	CFlatEdit2 m_edtCredit;
	CStatic m_ExplainStatic;

	CString m_strType;
	CString m_strSearch;
	CString m_strKeyword;

	UINT m_nSearchType;
	int m_nSearchNo;
	long m_nCNo;

	BOOL m_bGroup;
	int m_nOneRefresh;
	afx_msg void OnEnChangeSearchGroupEdit();
	CEdit m_edtSearchGroup;
	afx_msg void OnBnClickedWorkSearchBtn();
};
