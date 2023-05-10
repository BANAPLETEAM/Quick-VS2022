#pragma once

#include "BranchSel.h"

#include "FlatMainEdit.h"
#include "FlatSubEdit.h"

#include "BranchMainBtn.h"
#include "BranchSubBtn.h"
#include "afxwin.h"


// COtherRiderTransferDlg 대화 상자입니다.

class COtherRiderTransferDlg : public CMyDialog
{
	DECLARE_DYNAMIC(COtherRiderTransferDlg)

public:
	COtherRiderTransferDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COtherRiderTransferDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_OTHER_RIDER_TRANSFER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:

	void RefreshRiderInfo();

	long m_nCompany;

	long m_nRiderCompany;
	long m_nRNo;

	CFlatEdit2 m_edtCompanyName;
	CFlatEdit2 m_edtBranchName;
	CFlatEdit2 m_edtRNo;
	CFlatEdit2 m_edtName;
	CFlatEdit2 m_edtID;
	CFlatEdit2 m_edtHp;
	CFlatEdit2 m_edtAbleCharge;
 
	CFlatEdit2 m_edtCharge;
	CFlatEdit2 m_edtEtc;

	CString m_strCompanyName;
	CString m_strBranchName;
	CString m_strRNo;
	CString m_strName;
	CString m_strID;
	CString m_strHp;
	CString m_strSSN;

	CString m_strAbleCharge;

	CString m_strCharge;
	CString m_strEtc;

	CMyStatic m_stc1;
	CMyStatic m_stc2;
	CMyStatic m_stc3;
	CMyStatic m_stc4;
	CMyStatic m_stc5;
	CMyStatic m_stc6;
	CMyStatic m_stc7;
	CMyStatic m_stc8;
	CMyStatic m_stc9;	

	BOOL m_bTransReady;
	long m_nTransReadyCompany;
	long m_nAbility;

	CComboBox m_cmbBranch;

	void OnCbnSelchangeBranchCombo();

	afx_msg void OnBnClickedSearchRider();
	afx_msg void OnBnClickedSaveButton();
	afx_msg void OnBnClickedCancelButton();
	virtual BOOL OnInitDialog();
	void SendPayLater(long nTransCharge);

	CButton m_btnRiderSearch;

	void GetBranchBalance();

	CButton m_btnAuth;

	CFlatEdit2 m_edtAbleBranchName;
	afx_msg void OnBnClickedShowLogDlg();
};
