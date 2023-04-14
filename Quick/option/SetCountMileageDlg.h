#pragma once
#include "afxwin.h"


// CSetCountMileageDlg 대화 상자입니다.

class CSetCountMileageDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSetCountMileageDlg)

public:
	CSetCountMileageDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetCountMileageDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SET_COUNT_MILEAGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
