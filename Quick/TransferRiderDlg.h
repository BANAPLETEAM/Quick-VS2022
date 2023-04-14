#pragma once
#include "afxwin.h"


// CTransferRiderDlg ��ȭ �����Դϴ�.

class CTransferRiderDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CTransferRiderDlg)

public:
	CTransferRiderDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTransferRiderDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TRANFER_RIDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl2 m_lstReport;
	CFlatEdit2 m_edtRNo;
	CFlatEdit2 m_edtRName;
	CFlatEdit2 m_edtCompany;
	CFlatEdit2 m_edtEtc;
	
	long m_nRiderCompany;
	long m_nRNo;
	CString m_strRiderName;
	CString m_strCompanyName;

	void RefreshList();
	afx_msg void OnBnClickedTransButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedSearchRiderBtn();

	LONG OnGetAllocateRider(WPARAM wParam, LPARAM lParam);
	CFlatEdit2 m_edtCharge;

	CString ReturnType(int nType);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CButton m_btnRefresh;
	CButton m_btnClose;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCloseBtn();
};
