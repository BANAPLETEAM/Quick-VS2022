#pragma once

#include "VirtualRecord.h"

// CShareRcpSubPageDlg �� ���Դϴ�.
	
class CShareRcpSubPageDlg : public CMyFormView
{
	DECLARE_DYNCREATE(CShareRcpSubPageDlg)

protected:
	CShareRcpSubPageDlg();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CShareRcpSubPageDlg();

public:
	enum { IDD = IDD_SHARE_RCP_SUB_PAGE_DLG };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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


