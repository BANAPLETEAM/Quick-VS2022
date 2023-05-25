#pragma once


// ChistoryInsungDlg 대화 상자입니다.
#include "FlatEditInsung.h"

#include "WindowMagnetic.h"
class CRcpInsungDlg;

class CXTPListCtrl54 : public CXTPListCtrl2
{
public:
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics) 
	{
		int nCol = pDrawArgs->pColumn->GetItemIndex();
		int nRow = pDrawArgs->pRow->GetIndex();
		int nState = GetItemLong(nRow);

		if(nCol == 3 || nCol == 5) 
			pItemMetrics->clrForeground = RGB(0, 0, 235);

		if(nState == STATE_RESERVED)
			pItemMetrics->clrBackground = RGB(0xF3, 0xCF, 0xCF); 
		else if(nState == STATE_OK)
			pItemMetrics->clrBackground = RGB(255, 240, 255);
		else if(nState == STATE_OK_ONLY_MAN)
			pItemMetrics->clrBackground = RGB(0xEF, 0xE1, 0xC3);
		else if(nState == STATE_ALLOCATED)
			pItemMetrics->clrBackground = RGB(201, 230, 233);
		else if(nState == STATE_PICKUP)
			pItemMetrics->clrBackground = RGB(201, 230, 233);
		else if(nState == STATE_FINISH)
			pItemMetrics->clrBackground = RGB(0xFF, 0xFF, 0xFF);
		else if(nState == STATE_CANCELED)
			pItemMetrics->clrBackground = RGB(0xC9, 0xE6, 0xE9);
		else
			pItemMetrics->clrBackground = RGB(0xF7, 0xFC, 0x98);

	}
};

class ChistoryInsungDlg : public CDialog
{
	DECLARE_DYNAMIC(ChistoryInsungDlg)

public:
	//ChistoryInsungDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.

	ChistoryInsungDlg(UINT nResourceID, CWnd* pParent);
	virtual ~ChistoryInsungDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_HISTORY_INSUNG_DLG };
	CWindowMagnetic m_Magnetic;
	CWnd *m_pwndParent;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	CXTPListCtrl54 m_lstHistory;

	BOOL m_bMoveDown;

	long m_nFromSource;

	CFlatEditInsung m_edtSearchStart;
	CFlatEditInsung m_edtSearchDest;
	CFlatEditInsung m_edtSearchEtc;

	void InsertListColumn();
	afx_msg void OnEnChangeSearchStartEdit();
	afx_msg void OnEnChangeSearchDestEdit();
	afx_msg void OnEnChangeSearchEtcEdit();
	void ToOrder(BOOL bToStart);

	afx_msg void OnNMRClickHistoryList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickHistoryList(NMHDR *pNMHDR, LRESULT *pResult);
public:
	void DeleteHistoryList();
	void RefreshList();
	void OnToStart();
	void OnToDest();
	void OnRiderInfo(); 
	void CheckHistoryList();
	BOOL IsDetailAddressName(int nCol ,ST_HISTORY_ITEM_INFO3 *pItem);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	CRcpInsungDlg *m_pRcpInsungDlg;
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedMoveDownBtn();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
};
