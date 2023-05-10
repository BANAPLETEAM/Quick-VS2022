#pragma once


// CAllocateBoardTRSDlg 대화 상자입니다.

#include "AllocateTRSReportPaintManager.h"
#include "PPTooltip.h"
#include "afxwin.h"


#define WM_REFRESH_LIST			WM_USER + 102
#define	WM_CLOSE_TRS_BOARD_DLG	WM_USER + 772
#define WM_RIDER_ALLOCATE2		WM_USER + 1101


typedef map<std::pair<long,long>, ST_ARIDER> RIDER_LAST_ACTION_MAP2;


class CQSocket;

class CAllocateBoardTRSDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAllocateBoardTRSDlg)

public:
	CAllocateBoardTRSDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAllocateBoardTRSDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ALLOCATE_BOARD_TRS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnClose();
	afx_msg LONG OnRefreshList(WPARAM wParam, LPARAM lParam);
	afx_msg void NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result);
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedTestBtn();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);


	void RefreshList();
	void RefreshRiderList(CString strSearchKeyword = "");
	void SetRiderAck(long nTRSID);
	void LoadOption();
	void GetRiderInfo(long nRNo);
	CXTPGridRecordItem* GetCursorRecordItem();

	static int staticSocketRead(CAllocateBoardTRSDlg *app)
	{ return app->SocketRead((LPVOID)app); }
	UINT SocketRead(LPVOID lParam);

	void OnAllocateLimit(UINT nID);
	void OnAllocateLimitLevel(UINT nID);
	void OnRiderInfo();

	CXTPGridControl m_wndReport;
	long m_nOneWidth;
	CAllocateTRSReportPaintManager *m_pRPM;
	CPPToolTip m_tooltip;
	int	m_nTopIndex;
	int m_nWorkStateRiderCount;
	RIDER_LAST_ACTION_MAP2 m_mapRiderLastAction;
	long m_nOfficeLine1;
	long m_nOfficeLine2;
	long m_nOfficeLine3;
	long m_nOfficeLine4;
	long m_nShowType;
	CString m_strServerIP;
	long m_nServerPort;
	BOOL m_bShutDown;
	long m_nIndex; 
	CQSocket *m_pSocket;
	CXTPGridRecordItem *m_pSelectedRecordItem;

	COLORREF m_crPenalty1;
	COLORREF m_crPenalty2;
	COLORREF m_crPenalty3;
	COLORREF m_crPenalty4;
	COLORREF m_crPenalty5;

	long m_nPenaltyMin1;
	long m_nPenaltyMin2;
	long m_nPenaltyMin3;
	long m_nPenaltyMin4;
	long m_nPenaltyMin5;
};
