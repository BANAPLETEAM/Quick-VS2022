#pragma once
#include "afxwin.h"


// CTransferRiderDlg 대화 상자입니다.

class CTransferRiderDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CTransferRiderDlg)

public:
	CTransferRiderDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTransferRiderDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TRANFER_RIDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
