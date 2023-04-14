#pragma once
#include "afxwin.h"


// CRiderSelectDlg ��ȭ �����Դϴ�.

class CRiderSelectDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderSelectDlg)

public:
	CRiderSelectDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRiderSelectDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RIDER_SELECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CXTPListCtrl2 m_lstRider;
	void RefreshList();
	CEdit m_edtSearch;
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnBnClickedOk();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	long m_nCompany;
	long m_nRNo;
protected:
	virtual void OnOK();

public:
	afx_msg void OnBnClickedCancel();
};
