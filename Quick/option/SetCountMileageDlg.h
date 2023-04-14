#pragma once
#include "afxwin.h"


// CSetCountMileageDlg ��ȭ �����Դϴ�.

class CSetCountMileageDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSetCountMileageDlg)

public:
	CSetCountMileageDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSetCountMileageDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SET_COUNT_MILEAGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edtCount;
	CEdit m_edtCharge;
	CEdit m_edtInterCount;
	CEdit m_edtInterCharge;

	long m_nCompany;

	virtual BOOL OnInitDialog();

	void RefreshEdit();
	afx_msg void OnBnClickedOkButton();
	afx_msg void OnBnClickedCancelButton();
};
