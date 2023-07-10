#pragma once
#include "afxcmn.h"

#include "DateButton.h"
// CCVRRiderLogList ��ȭ �����Դϴ�.

class CVRRiderLogListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CVRRiderLogListDlg)

public:
	CVRRiderLogListDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CVRRiderLogListDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_VRRIDER_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
