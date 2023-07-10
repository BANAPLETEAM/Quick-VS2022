#pragma once
#include "afxcmn.h"

#include "DateButton.h"
// CCVRRiderLogList 대화 상자입니다.

class CVRRiderLogListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CVRRiderLogListDlg)

public:
	CVRRiderLogListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVRRiderLogListDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_VRRIDER_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOnokBtn();
	virtual BOOL OnInitDialog();
	void RefreshList();
	CXTPListCtrl2 m_List;
	long m_nCompany;
	int m_nRNo;
	CString m_sAccount;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;	
	CDateButton m_DateBtn;
	CComboBox m_cmbRider;
	afx_msg void OnBnClickedRefreshBtn();
};
