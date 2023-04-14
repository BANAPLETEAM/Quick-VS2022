#pragma once
#include "afxwin.h"



class CStaffForm27 : public CMyFormView
{
	DECLARE_DYNCREATE(CStaffForm27)

protected:
	CStaffForm27();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CStaffForm27();

public: 
	enum { IDD = IDD_STAFF_PAGE27 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	CXTPListCtrl2 m_lstReport;
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnNMClickListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblClickListReport(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSendSmsBtn();
};


