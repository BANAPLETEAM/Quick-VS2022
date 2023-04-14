#pragma once
#include "afxwin.h"


// CEditItemDlg 대화 상자입니다.

class CEditItemDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CEditItemDlg)

public:
	CEditItemDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CEditItemDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_EDIT_ITEM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CXTPListCtrl2 m_lstItem;

	CFlatEdit2 m_edtAdd;
	CFlatEdit2 m_edtUpdate;

	CButton m_chkIntegrated;
	CButton m_chkIntercallView;	
		
	long m_nCompany;

	void LoadItem();
	afx_msg void OnDelete();
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnBnClickedUpdateBtn();
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnNMClickItemList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickItemList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);	
	afx_msg void OnBnClickedIntegratedCheck();
};
