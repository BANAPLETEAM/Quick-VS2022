#pragma once
#include "RiderMapCtrl.h"


class CRiderMapNormalForm;
class CRiderMapTRSForm;
class CRcpView;
//class CRiderMapSearchForm;

#define MAX_SEARCH_RESULT 200
#define	WM_CLOSE_RIDER_MAP_DLG	WM_USER + 758


enum MAP_POPUP_MENU { MENU_RIDER_INFO = 1, 
MENU_RIDER_TRACE, 
MENU_RIDER_REALTIME_TRACE, 
MENU_RIDER_ALLOCATE , 
MENU_RIDER_WORK_LEAVE,
MENU_FIND_PROPER_ORDER,
MENU_CHANGE_RIDER_SECTOR,
MENU_RIDER_NOTICE,
MENU_ORDER_START_DEST, 
MENU_ORDER_INFO,
MENU_ORDER_LOG,
MENU_ORDER_ALLOCATE,
MENU_ORDER_ALLOCATE2,
MENU_RIDER_OPTION,
MENU_MAKE_CALL,
MENU_SHOW_SHUTTLE_INFO};

enum MAP_POPUP_SUB_MENU { MENU_SUB_TRACE_ALL_SHOW = 1000, 
MENU_SUB_TRACE_FAST_MOVE = 1001, 
MENU_SUB_TRACE_NORMAL_MOVE = 1002,
MENU_SUB_RIDER_REALTIME_TRACE = 1100,
MENU_SUB_RIDER_REALTIME_TRACE_WITH_RECENT_LOG = 1101};



// CRiderMapDlg 대화 상자입니다.

class CRiderMapDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderMapDlg)

public:
	CRiderMapDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderMapDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_MAP_DLG};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

public:
	CXTPTabControl m_wndTabControl;
	BOOL m_bHideListForm;
	CRiderMapCtrl m_wndLogiMap;
	CRiderMapNormalForm *m_pNormalForm;

	CRcpView *m_pRcpView;
	COleDateTime m_dtBase;
	long m_nForLongTime;
	CStatic m_RNoStc;
	CEdit m_RNoEdt;
	long m_nTraceTimerMSec;
	long m_nTRDType;
	CString m_strTRDName;
	CString m_strTRDVer;
	BOOL m_bOtherRiderMap;
	BOOL m_bChangeCursor;
	BOOL m_bMoveControl;
	HCURSOR m_hcVertical;
	HCURSOR m_hcArrow;
	BOOL m_bMustMoveControl;

	int m_nNormalFormWidth;
	BOOL m_bMaxmize;

protected:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	afx_msg void OnBnClickedRefreshMapBtn();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnPOIClickSmartmapx1(LPDISPATCH Poi);
	afx_msg void OnMouseUpSmartmapx1(long Button, long Shift, long X, long Y);
	afx_msg void OnPopupMenuSmartmapx1(long Index, LPCTSTR Caption, LPCTSTR Contents);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEnChangeRnoEdt();
	afx_msg void OnCbnSelchangeRefershTimerCombo();
	afx_msg void OnPOIClick(LPDISPATCH POI, long nFlag, long X, long Y);
	afx_msg LRESULT OnMapUIMouseUP(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void UpdateShowRiderCount(long nCount);
	void SetRiderConnState(long nCompany, long nRNo, long nState);
	void SetRiderPosRealTime(CRealTimeRiderPos &pos);

	CRiderMapCtrl *GetMap() { return &m_wndLogiMap; }
	void OffsetMoveWindow(CWnd *pWnd, int nOffset);
	void RefreshOrderState();
	BOOL GoRiderTrace(int nType, long nCompany, long nRNo, 
				COleDateTime dtBase = COleDateTime::GetCurrentTime(),
				long nForLongHour = 18);	//dtBase:기준시간, nForLongHour:기준시간에서 몇시간전부터 시작할지
	void AddTraceRiderHasOrder(BOOL bShowCurHasOrder, long nCompany, long nRNo, COleDateTime dtBase, long nForLongHour);
	void OnPopupMapMenu(CXPOIItem item, CPoint pt = CPoint(0, 0));
	CWnd* GetActiveForm();
	void OrderClickAutoMoveMap(long nPosX, long nPosY, long nRCompany, long nRNo, BOOL bNearRider = FALSE);
	void MoveClient(int cx, int cy);
	void ShowLeftForm(BOOL bShow);
	void MoveNormalForm(BOOL bOnlyMove = FALSE);
	BOOL IsOtherRiderMap() { return m_bOtherRiderMap;}
	void MoveControl();
	void SetShowOrderCount(BOOL bShow, long nShowCount);
};
