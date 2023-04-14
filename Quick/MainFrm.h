// MainFrm.h : CMainFrame 클래스의 인터페이스
//




typedef struct{
	long nTNo;
	long nState;
	CString sOName;
}TRANS_STRUCT;

typedef map<CXTPPopupItem*, TRANS_STRUCT*> TRANS_MAP;

#define ETC_REFRESH_TIMER_ID	8888
#define ETC_REFRESH_SEC			10000
#define UPLOAD_TIMER			10

class CMyCXTPopupItem : public CXTPPopupItem
{
public:
	void SetItemData(DWORD dwData) {m_dwData = dwData;};
	DWORD GetItemData() {return m_dwData;};
	//CXTPPopupControl* GetPopupControl(){return CXTPPopupItem::GetPopupControl();};

	DWORD m_dwData;
};

enum {
	ID_PANE_SEPARATOR = 0,
	ID_PANE_MESSENGER = 1,
	ID_PANE_INTERCALL = 2,
	ID_PANE_ALLOC = 3,
	ID_PANE_RECEPT = 4,
	ID_PANE_DATETIME = 5,
	ID_PANE_SHARE_BALANCE = 6
};

enum { HOME_VIEW = 1, RCP_VIEW, REPORT_CUSTOMER_VIEW, REPORT_RIDER_VIEW, STAFF_VIEW, CUSTOMER_VIEW, INCOME_VIEW, STAT_VIEW, FAQ_VIEW };

class CHomeView;
class CRcpView;
class CRcpDeliveryView;
class CReportView;
class CReportRiderView;
class CCustomerView;
class CStaffViewNew;
class CQuickView;
class CBranchView;
class CFAQHtmlView;
class CLogiMapDlg;
class CLogiMapRouteDlg;
class CCase1MapDlg;
class CIncomeView;
class CStatView;

class CDeliveryReportView;
class CDeliveryCustomerView;
class CDeliveryStaffView;

class CDelayOrderDlg1;
class CDelayOrderDlg2;
class CEmptyCarDlg1;
class CAllocatePaneDlg;

class CChargeDistanceDlg;
class CAllocateBoardTRSDlg;
class CScheduleOrderListDlg;

class CMkMessenger;
class CMkDatabase;
class CRecvCidDlg;
class CChargeDongDlg2;
class CChargeDongDlg3;
class CCorporationDlg2;
class CMyMkMessenger;
class CChargeDongUDlg;


 
#pragma once
class CMainFrame : public CXTPFrameWnd
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 재정의
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현
public:
	virtual ~CMainFrame(); 
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CReBar		m_wndReBar;
	CMenu		m_Menu;
	CImageList	m_toolList;

	CQSocket m_AllocSocket;
	//CLogiMapDlg *m_pLogiMapDlg;
	CLogiMapRouteDlg *m_pLogiMapRouteDlg;
	MAP_INTERCALL_CUSTOMER m_mapIC;

	long m_nOrderRequestCount;

public:
	//using to clear the statusbar
	UINT m_nStatusAccessTime;
	CMkDatabase *m_pMsgClient;

	CDialogBar m_wndFieldChooserCustomer; 
	CMap<UINT,UINT, CWnd* , CWnd*> m_mapPanes;
	CXTPTaskPanel *m_pwndTaskPanel;
	BOOL m_bApplicationInit;
	CChargeDistanceDlg *m_pChargeDistanceDlg;
	BOOL m_bNoQueryExit;
	CScheduleOrderListDlg *m_pScheduleOrderListDlg;
	BOOL m_bRcpPageInitCompleted;


protected:
	DECLARE_MESSAGE_MAP()
public:
	void GetOrderRequestCount();
	void SwitchView(int nView);
	void SwitchViewDv(int nView);
	//CLogiMapDlg *GetLogiMapDlg() { return m_pLogiMapDlg;}
	CLogiMapRouteDlg *GetLogiMapRouteDlg() { return m_pLogiMapRouteDlg;}
	//void ShowLogiMapDlg(double dPosX, double dPosY, CString strPOIName, CString strDisplayName, int nLevel = -1);
	void ShowLogiMapRouteDlg(double dPosX, double dPosY, CString strPOIName, CString strDisplayName, int nLevel = -1);
	void ShowLogiMapRouteDlg(long nRNo = -1);

public:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	void InitControl();
	void AllocReconnect();

	void OnAttend();
	void OnGetOff();
	void ShowTrasferSmsToShaerBalance();

	BOOL IsAttend();
	BOOL IsGetOff();
	void OnRunQ5();

	LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);
	LRESULT OnTaskPanelNotify(WPARAM wParam, LPARAM lParam);
	CXTPDockingPane* CreatePane(CRuntimeClass* pNewViewClass, 
		CString strFormat, 
		XTPDockingPaneDirection direction, 
		CXTPDockingPane* pNeighbour,
		long nID,
		CRect &rect);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	//{{AFX
	afx_msg LONG OnCloseRiderDlg(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnCloseShowRecvCidDlg(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnCloseRiderMapDlg(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewPay();
	afx_msg void OnProgShare();
	afx_msg void OnViewCar();
	afx_msg void OnViewCustomer();
	afx_msg void OnManager();
	afx_msg void OnViewStandard();
	afx_msg void OnViewDeliveryStandard();
	afx_msg void OnViewReportCustomer();
	afx_msg void OnViewReportRider();
	afx_msg void OnViewCid();
	afx_msg void OnViewIncome();
	afx_msg void OnViewStat();
	afx_msg void OnMessenger();
	afx_msg void OnCallCount();
	afx_msg void OnRemoteControlWeb();
	afx_msg void OnAllocateBoard();
	afx_msg void OnUpdateViewStandard(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewReportCustomer(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewReportRider(CCmdUI *pCmdUI);
	afx_msg void OnUpdateManager(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewCustomer(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewPay(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewIncome(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewStat(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMessenger(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCallCount(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAllocateBoard(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRiderMap(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOtherRegionBranch(CCmdUI *pCmdUI);
	afx_msg void OnLogout();
	afx_msg void OnMenuMsg();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg	void OnCbnSelchangeCondition();
	afx_msg void OnTcnSelchangeRcpTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnNMClickRcpTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickRcpTab(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnSendMac();
	afx_msg LRESULT OnTaskbarNotifierClicked(WPARAM wParam,LPARAM lParam);
	//afx_msg void OnShowNotice();
	afx_msg void OnCidGroup();
	afx_msg void OnAllocateGroup();
	afx_msg void OnMoveOrder();
	afx_msg void OnScheduleJob();
	afx_msg void OnShowSecurityLog();
	afx_msg LONG OnNotifierClicked(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnSetMsgState(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnSetIntercallState(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnSetAllocState(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnCloseMsgConnListDlg(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnCloseMsgDlg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnOption();
	afx_msg void OnRemoteControl(UINT nID);
	afx_msg void OnDebugMode();
	afx_msg void OnBill();
	afx_msg void OnIntercallNotice();
	afx_msg void OnNewRiderList();
	afx_msg void OnAccessControl();
	afx_msg void OnTestVirtualCid();
	afx_msg void OnViewHome();
	afx_msg void OnUpdateViewHome(CCmdUI *pCmdUI);
	afx_msg void OnAuthManage();
	afx_msg void OnAuthManageLog();
	afx_msg void OnAuthLog();
	afx_msg LONG OnQueryChargeResponse(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnRcpCopyData(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnRcpCopyDataDirect(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnGroupChatResonse(WPARAM wParam, LPARAM lParam);	
	afx_msg void OnShareReportRate();
	afx_msg void OnRunTelclient();
	afx_msg void OnScheduleOrder();
	afx_msg void OnCompleteAfterEdit();
	afx_msg void OnIntercallConnList();
	afx_msg void OnRiderMap();
	afx_msg void OnOtherRegionBranch();
	afx_msg LONG OnCloseTRSBoardDlg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBranchTransfer();
	afx_msg LRESULT OnPopUpNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTrsBoardDlg();
	afx_msg void OnShareReportBranchSet();
	afx_msg void OnDeletePoiFile();
	afx_msg void OnRiderShareBoard();
	afx_msg void OnRiderBoard();
	afx_msg void OnChargeForRider();
	afx_msg void OnMoveRider();
	afx_msg void OnMShowPreCharge();
	afx_msg void OnSendBulkSms();
	afx_msg LONG OnRecvCid(WPARAM wParam , LPARAM lParam);
	afx_msg int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);
	//}}AFX

public:
	UINT m_nCurDlg;
	CStringList m_CidList;
	BOOL m_bGroup;
	
	CChargeDongDlg3 *m_pChargeDongDlg3;	
	CChargeDongDlg2 *m_pChargeDongDlg;	
	CChargeDongUDlg *m_pChargeDongUDlg;
	CMyMkMessenger *m_pIntercall;
	CXTPPopupControl* m_pActivePopup;
	CList<CXTPPopupControl*, CXTPPopupControl*> m_lstPopupControl;
	CPoint m_ptPopup;
	BOOL m_bShowOrderChangePopup;
	TRANS_MAP m_TransMap;
	UINT m_nCurView;

public:

	void CheckChargeForRider();
	void OnOrderInsert();
	void OnGeneralRecepitRequest();
	void OnOrderRequest();
	void SetStatusAccessTime(UINT nTickCount) { m_nStatusAccessTime = nTickCount; }
	CStatusBar	*GetStatusBar() { return &m_wndStatusBar; }


	void EtcRefresh();
	void CopyFont(CString sfile);
	void RefreshIntercallConnList();
	long GetICCount() { return (long)m_mapIC.size(); }
	BOOL FindIC(long nCNo) { return m_mapIC.end() != m_mapIC.find(nCNo); }
	void ViewCharge();
	void SetInitCompleted(BOOL bCompleted) { m_bRcpPageInitCompleted = bCompleted;}
	void OnRecvEditOrderState(long nTNo, long nTickCount, long nState, CString strWName);
	void FindBestPosition(CSize szPopup);
	void SetPoputMsg();
	void EnableItems(BOOL bEnable);
	void ShowRecvCidDlg();
	void ShowTransInformationRequestPopup(long nTNo, CString sStart, CString sDest, CString sRName, long nRNo, 
				CString sOName,	long nState);
	void SetTransPopupMsg(long nTNo, CString sStart, CString sDest, CString sRName, long nRNo, CString sOName,long nState);
	CWnd* ReplaceView(CView **pView, CRuntimeClass *pClass);
	void InitRcpViewRelation();
	void CheckShareBasicRate();
	void OnOtherRiderIncome();
	void OnShowHolidayDelivery();
	afx_msg void OnFunctionTable();
	afx_msg void OnCalc();
	afx_msg void OnRemakeCustomerData();
	afx_msg void OnGeneralAppRegister();
	afx_msg void OnGeneralOpenAPIRegister();

	void ShowHolidayDeliveryDlg(BOOL bIgnoreInsert = TRUE);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};




