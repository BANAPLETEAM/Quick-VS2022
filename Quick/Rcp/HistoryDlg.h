#pragma once


#include "WindowMagnetic.h"

#define LIST_ALL_COL 1
#define LIST_MANAGER_COL 5
#define LIST_START_COL 6
#define LIST_DEST_COL 7
#define LIST_RIDER_COL 8
#define LIST_ETC_COL 13

typedef map<pair<pair<long, long>, long>, ST_HISTORY_ITEM_INFO3*> CUSTOMER_CHARGE_MAP;
class CRcpDlg;

class CHistoryDlg : public CMyDialog


{
	DECLARE_DYNAMIC(CHistoryDlg)

public:
	CHistoryDlg(UINT nResourceID, CWnd* pParent);   // 표준 생성자입니다.
	virtual ~CHistoryDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_HISTORY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEnChangeSearchStartEdit();
	afx_msg void OnEnChangeSearchDestEdit();
	afx_msg void OnEnChangeSearchEtcEdit();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnBnClickedMoveDownBtn();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnChangeSearchManagerEdit();
	afx_msg void OnBnClickedRefreshBtn2();
	afx_msg void OnViewExcel();
	afx_msg void OnAddCall();

	void OnReportColumnChangeChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	void RefreshList(BOOL bOCNoSearch = TRUE);
	void DeleteAllItems();
	void ListFilter();
	void OnCurOrderState();
	void Clear();
	void SetPlaceInfoFromCol(int nCol, ST_HISTORY_ITEM_INFO3 *pItem);
	void OnSizeDown();
	void OnSizeUp();
	void OnOpenRcpDlg();
	BOOL IsDetailAddressName(int nCol ,ST_HISTORY_ITEM_INFO3 *pItem);

	CRcpDlg *m_pRcpDlg;
	CWnd *m_pwndParent;
	CXTPListCtrl9 m_wndReport;

	CWindowMagnetic m_Magnetic;
	CUSTOMER_CHARGE_MAP m_mapCusCharge;

	BOOL m_bLButtonDown;
	BOOL m_bMoveDown;
	BOOL m_bShowAll;
	BOOL m_bFirstLoad;

	long m_nOCNo;
	long m_nOGNo;
	long m_nCompany;

	CButton m_btnRefresh;
	CButton m_btnCancel;

	CFlatEdit2 m_edtSearchStart;
	CFlatEdit2 m_edtSearchDest;
	CFlatEdit2 m_edtSearchEtc;
	CFlatEdit2 m_edtSearchManager;
	afx_msg void OnBnClickedShowAllHistory();

	CCriticalSection m_cs;
};
