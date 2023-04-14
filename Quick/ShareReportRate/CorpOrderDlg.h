#pragma once
#include "afxcmn.h"


// CCorpOrderDlg ��ȭ �����Դϴ�.

class CCorpOrderDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCorpOrderDlg)

public:
	CCorpOrderDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCorpOrderDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CORP_ORDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	
	void RefreshList();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
};
