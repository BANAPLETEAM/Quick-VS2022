#pragma once
#include "afxwin.h"


// COrderPassDlg 대화 상자입니다.

class COrderPassDlg : public CMyDialog
{
	DECLARE_DYNAMIC(COrderPassDlg)

public:
	COrderPassDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COrderPassDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ORDER_PASS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeRnoEdit();
	afx_msg void OnBnClickedAllocateBtn();
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnNMDblclkDuplicateList(NMHDR *pNMHDR, LRESULT *pResult);
	
	void InsertListData();

	CXTPListCtrl2 m_lstDuplicate;
	
	CFlatEdit2 m_edtRNo;

	long m_nRiderCompany;
	long m_nRNo;
};
