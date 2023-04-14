#pragma once
#include "afxcmn.h"


// CCorpOrderDlg 대화 상자입니다.

class CCorpOrderDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCorpOrderDlg)

public:
	CCorpOrderDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCorpOrderDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CORP_ORDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	
	void RefreshList();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
};
