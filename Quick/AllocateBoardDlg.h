#pragma once


// CAllocateBoardDlg 대화 상자입니다.

#include "AllocateReportPaintManager.h"
#include "PPTooltip.h"
#include "VirtualRecord.h"

class CXTPTRSReportControl : public CXTPGridControl
{
public:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

typedef map<std::pair<long,long>, ST_ARIDER> ALLOCATE_FLASH_RIDER_MAP;
typedef map<CWnd*, CWnd*> DYN_WND_MAP;
typedef map<std::pair<long,long>, ST_ARIDER> RIDER_LAST_ACTION_MAP;


class CAllocateBoardDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAllocateBoardDlg)

public:
	CAllocateBoardDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAllocateBoardDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ALLOCATE_BOARD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void RefreshListPredate();
	void RefreshList();
	void RefreshRiderList(CString strSearchKeyword = "");
	void GetRiderList(BOOL bShareRider = FALSE);
	void FillForm(CDC *pDC);
	void RefreshCommon(long nCompleteCount, long nCancelCount);
	void FlashRiderList();
	void FlashRider(ALLOCATE_BOARD_RIDER_INFO *pRiderInfo, BOOL bFindProperRider = FALSE, 
		CRect rcBase = CRect(0,0,0,0), CPoint rcOffset = CPoint(0, 0),
		BOOL bShareRider = FALSE, BOOL bFirstBox = FALSE);

	inline void AddMatchOrder(OrderRecord *pOrder, long &nCompleteCount, long &nCancelCount, 
		BOOL bStartOherOrder, COleDateTime &dtTomorrow, COleDateTime &dtMax,
		BOOL &bElapseLimitBike, BOOL &bElapseLimitCar);

public:
	int m_nRefreshSecond;
	long m_nNowAddTime;
	CMkDatabase *m_pDb;
	CXTPTRSReportControl m_wndReport;
	long m_nOneWidth;
	CAllocateReportPaintManager *m_pRPM;
	CButton m_chkOrderEmpty;
	CComboBox m_cmbSort;
	CComboBox m_cmbLine;
	CButton m_chkElapsed;
	CComboBox m_cmbState;
	CButton m_chkShowRiderPhone;
	long m_nTopIndex;
	HBRUSH m_hNullBrush;
	HBRUSH m_hBrushGreen;

	CMyStatic m_stcTotalCount;
	CMyStatic m_stcCompleteCount;
	CMyStatic m_stcCancelCount;
	CMyStatic m_stcRegRider;
	CMyStatic m_stcWorkRider;
	CEdit m_edtRefresh;
	CEdit m_edtSearchRider;
	CDateTimeCtrl m_dtpShow;
	CComboBox m_cmbBranch;
	CPPToolTip m_tooltip;
	CButton m_chkCarShowType;
	COleDateTime m_dtLastRefresh;
	ALLOCATE_FLASH_RIDER_MAP m_mapFlashRider;
	BOOL m_bFirstRefresh;
	CComboBox m_cmbRefresh;
	CButton m_btnRefresh;
	CButton m_chkShowDyn;
	CComboBox m_cmbRiderGroup;
	CButton m_chkShowRiderPos;
	CButton m_chkShowWorkingRider;
	CButton m_chkFindProperRider;
	ALLOCATE_RIDER_VECTOR m_vecProperRider;
	DYN_WND_MAP m_mapDynWnd;
	BOOL m_bChkWorkReport;
	RIDER_LAST_ACTION_MAP m_mapRiderLastAction;
	ALLOCATE_RIDER_MAP m_mapShareRider;
	OrderRecordList m_mapShareRiderOrder;
	CButton m_chkShowOnlyConnRider;
	CButton m_chkNotifyConnRider;

	CRect m_rcFPBase;
	long m_nFPTNo;
	long m_nFPCarType;
	long m_nFPStartPosX;
	long m_nFPStartPosY;
	long m_nFPDestPosX;
	long m_nFPDestPosY;
	CPoint m_ptMoved;


	BOOL m_bFinishTest;
	BOOL m_bLinearType;
	BOOL m_bOtherRiderHaveMyOrder;
	BOOL m_bOtherRiderHaveMyOrderSplitSort;
	long m_nAL;	//시내오더 배차경과 시간
	long m_nPL; //시내오더 픽업경과 시간
	long m_nAG; //시외오더 배차경과 시간
	long m_nPG; //시외오더 픽업경과 시간
	long m_nAL2;	//시내오더 배차경과 시간
	long m_nPL2; //시내오더 픽업경과 시간
	long m_nAG2; //시외오더 배차경과 시간
	long m_nPG2; //시외오더 픽업경과 시간
	COLORREF m_crDelayRiderBack;
	COLORREF m_crOtherOrderText;
	COLORREF m_crOtherOrderBack;
	COLORREF m_crOtherRiderText;
	COLORREF m_crOtherRiderBack;

	long m_nContextMenuLastOrder;
	long m_nContextMenuLastState;
	long m_nContextMenuLastCompany;
	long m_nContextMenuLastRNo;

	CCriticalSection m_cs;

	CMyStatic m_stc1;
	CMyStatic m_stc2;
	CMyStatic m_stc3;
	CMyStatic m_stc4;
	CMyStatic m_stc5;
	CMyStatic m_stc6;
	CMyStatic m_stc7;
	CMyStatic m_stc8;


	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedOrderEmptyChk();
	afx_msg void OnCbnSelchangeSortCombo();
	afx_msg void OnCbnSelchangeLineCombo();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnBnClickedElapsedChk();
	afx_msg void OnCbnSelchangeStateCombo();
	afx_msg void OnBnClickedShowRiderPhoneChk();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeSearchRiderEdit();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCbnSelchangeBranchCombo2();
	afx_msg void OnClose();
	afx_msg LONG OnRefreshList(WPARAM wParam, LPARAM lParam);
	afx_msg void NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result);
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg LONG OnCloseAllocateBoardDyn(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedCarShowTypeChk();
	afx_msg void OnCbnSelchangeRefreshCombo();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnCbnSelchangeRiderGroupCombo();
	afx_msg void OnUpdateColor();
	afx_msg void OnShowRiderPos();
	afx_msg void OnSetWorking();
	afx_msg void OnSetLeave();
	afx_msg void OnShowRiderInfo();
	afx_msg void OnBnClickedShowRiderPosCheck();
	afx_msg void OnBnClickedShowWorkingRiderCheck();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSMSAllocate();
	afx_msg void OnPDAAllocate();
	afx_msg void OnBnClickedAdditionalSettingBtn();
	afx_msg void OnBnClickedShowOnlyConnRider();
	afx_msg void OnAllocateState();
	afx_msg void OnFinishState();
	afx_msg void OnWaitState();
	afx_msg void OnRcpState();
	afx_msg void OnEditOrder();
	afx_msg void OnPickupState();
	afx_msg void OnCancelState();

protected:
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	void SetRiderPosRealTime(CRealTimeRiderPos &pos);

	CXTPGridRecordItem *m_pSelectedRecordItem;

	void UpdateRiderState();
	static BOOL ForceLeavingWork(long nCompany, long nRNo);
	//void FindProperRider(CRect rcBase, long nTNo, long nCarType, long nStartPosX, long nStartPosY, long nDestPosX, long nDestPosY,
	//	BOOL bShareRider = FALSE);
	void FindProperRiderLinearType(CRect rcBase, long nTNo, long nCarType, long nStartPosX, long nStartPosY, 
		long nDestPosX, long nDestPosY,	BOOL bShareRider = FALSE);


	void DeleteAllDynWnd();
	void GetAdditionalSetting();
	void GetShareRiderOrderList();
	void ShowProperRider(long nType);
	void SetRiderWorkReport(long nCompany, long nRNo, int nState);
	void SetRiderConnState(long nCompany, long nRNo, int nState);

	afx_msg void OnShowAll();
	afx_msg void OnShowShareCode();
	afx_msg void OnShowBranch();
	afx_msg void OnSendMsg();

	void ChangeShowType(long nType);

	CButton m_chkOnlyAuto;
	BOOL m_bOnlyAuto;

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};
