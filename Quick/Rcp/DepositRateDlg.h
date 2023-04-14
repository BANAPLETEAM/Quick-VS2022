#pragma once

#include "ListCtrl.h"

// CDepositRateDlg ��ȭ �����Դϴ�.

class CDepositRateDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CDepositRateDlg)

public:
	CDepositRateDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDepositRateDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DEPOSIT_RATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	gxListCtrl m_List;
    BOOL FirstTime;
    BOOL Flush;

	int m_nItem;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();

	void RefreshList();
	afx_msg void OnBnClickedAutoGenerateBtn();
	afx_msg void OnBnClickedSaveAfterSortBtn();

	BOOL SaveDeposit();
	afx_msg void OnBnClickedRemoveAllBtn();
	afx_msg void OnBnClickedDeleteBtn();
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);


public:
	long m_nCompany;

};
