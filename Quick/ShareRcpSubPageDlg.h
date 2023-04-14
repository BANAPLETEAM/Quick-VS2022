#pragma once

#include "VirtualRecord.h"

// CShareRcpSubPageDlg 폼 뷰입니다.
	
class CShareRcpSubPageDlg : public CMyFormView
{
	DECLARE_DYNCREATE(CShareRcpSubPageDlg)

protected:
	CShareRcpSubPageDlg();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CShareRcpSubPageDlg();

public:
	enum { IDD = IDD_SHARE_RCP_SUB_PAGE_DLG };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl30 m_lstReport;
	BOOL m_bTake;
	void Refresh();
	CString GetFooterData();
	void FilterList(long nIndex, CString sSearch);
	void InsertData(OrderRecord *record);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


