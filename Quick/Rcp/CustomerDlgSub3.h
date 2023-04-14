#pragma once
#include "afxwin.h"

class CCustomerDlg;

// CCustomerDlgSub3 폼 뷰입니다.

class CCustomerDlgSub3 : public CMyFormView
{
	DECLARE_DYNCREATE(CCustomerDlgSub3)

protected:
	CCustomerDlgSub3();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CCustomerDlgSub3();

public:
	enum { IDD = IDD_CUSTOMER_DLG_SUB3 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void RefreshDlg();
	void RefreshDlgSub();
	BOOL UpdatePBizInfo();
	CCustomerDlg *m_pCustomerDlg;
	CEdit m_edtPBizNo;
	CEdit m_edtPBizAddress;
	CEdit m_edtPBizCorpName;
	CEdit m_edtPBizName;
	CEdit m_edtPBizType1;
	CEdit m_edtPBizType2;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


