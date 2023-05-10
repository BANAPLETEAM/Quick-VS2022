#pragma once

#include "afxwin.h"

// CSearchRegionDlg ��ȭ �����Դϴ�.

class CSearchRegionDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSearchRegionDlg)

public:
	CSearchRegionDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSearchRegionDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SEARCH_REGION_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSeaechButton();

	DECLARE_MESSAGE_MAP()
public:
	void RefreshList();
	void SelectUp();
	void SelectDown();

	CFlatEdit2 m_edtSearch;
	CXTPListCtrl2 m_List;

	CString m_strDisplayDong;
	CString m_strSearch;
	CString m_strLi;

	int m_nDongID;

	BOOL m_bAloneItemAutoClosed;
	BOOL m_bExpandLiData;
	BOOL m_bReturnLiID;
	afx_msg void OnEnChangeSearchEdit();
};
