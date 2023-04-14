#pragma once
#include "afxwin.h"


// CSaveMentDlg ��ȭ �����Դϴ�.

class CSaveMentDlg : public CDialog
{
	DECLARE_DYNAMIC(CSaveMentDlg)

public:
	CSaveMentDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSaveMentDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SAVE_MENT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	
	void RefreshList();

	CXTPListCtrl2 m_lstMent;
	CButton m_chkCustomer;
	CButton m_chkRider;

	CFlatEdit2 m_edtMent;

	afx_msg void OnBnClickedCustomerCheck();
	afx_msg void OnBnClickedRiderChk();
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnBnClickedUpdateBtn();
	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDelete();
	afx_msg void OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/);
};
