#pragma once
#include "afxdtctl.h"
#include "afxwin.h"


// CShowRcpNotice ��ȭ �����Դϴ�.

class CXTPListCtrlNotice : public CXTPListCtrl2
{
public:
	void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		CXTPGridRecord *pRecord = pDrawArgs->pRow->GetRecord();
		BOOL bRev = GetItemLong(pRecord);

		if(bRev)
			pItemMetrics->clrBackground = RGB(220, 255, 180);

	}
};

class CShowRcpNotice : public CMyDialog
{
	DECLARE_DYNAMIC(CShowRcpNotice)

public:
	CShowRcpNotice(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CShowRcpNotice();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SHOW_RCP_NOTICE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	CXTPListCtrlNotice m_List;

public:
	long m_nCompanyCode;
	BOOL m_bIntegrated;

public:
	virtual BOOL OnInitDialog();
	void RefreshList();

	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedEditBtn();
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnRevRelease();
	afx_msg void OnRevDelete();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	CDateTimeCtrl m_dtpFrom;
	CDateTimeCtrl m_dtpTo;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;

	CDateButton m_btnData;
	CButton m_btnRefresh;
};
