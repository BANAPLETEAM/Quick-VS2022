#pragma once

#include "RiderSubInfo.h"
//#include "RecPlayerDlg.h"

class CTaskbarNotifier; 
class CNotifierContainer;
class CMyMkMessenger;
class CRcpView;
class CReportView;
class CReportRiderView;
class CCustomerView;
class CStaffView;
class CIncomeView; 
class CStatView;
class CHomeView;
class CDelayOrderDlg2;
class CEmptyCarDlg1;
class CAllocatePaneDlg;
class CRecvCidDlg;
class CShowRiderInfoDlg;
class CSimpleMapDlg;
class CRiderMapDlg;
class CAllocateBoardDlg;
class CAllocateBoardTRSDlg;
class CRiderShareBoardDlg;
class CRiderBoardDlg;
class CAllocateDlg;
class COtherRiderDlg;
class CCallPhoneDlg;
class CSearchPOIDlg;
class CRcpPlaceInfo;
class CChargeAdd;
class CLogiMapCns;
class CChargeHistoryMemDlg;
class CRcpDlgMapDlg;
class CRcpDlg;
class CChargeContainer;
class COrderProcessStateDlg;
class CConsignLinkDlg;
class CFunctionTableDlg;
class CConnListDlg2;
class CGroupChatDlg;
class CMakeGroupReportNewDlg;
class CTransInfoDlg;
class CLogiUtil
{
public:
	CLogiUtil(void);
	~CLogiUtil(void);

public:
	CRecPlayerDlg m_PlayerDlg;
	void AddCall(CString strName, long nTNo, long nState);
	BOOL Init();
	void CheckDpiRegistry(LPCSTR lpExeFileName);
	void CheckDebugLogMode();
	BOOL IsDebugMode();
	BOOL Logon(char *szID);
	void InstallMalgunFont();
	void SetSystemTimeLikeServer();
	BOOL ShowShareReportDlg();
	BOOL SetServerInfo();
	BOOL CheckCommandLine(char *szID, char *szLogiCode, char *szLogiNo);
	void CheckRegistryInfo();
	void SetClearType();
	void SetWindowTitleWithVersion();
	void StartMessenger(BOOL bIgnoreLogiMemberLogin = FALSE);
	void InitNofityContainer();
	void InitFieldChooser();
	CDialogBar* GetFieldChooser();
	void ShowBillDlg();
	CXTSplitterWnd *GetSplitterWnd();
	BOOL CreateSplitter(CWnd *pWnd, CCreateContext *pContext);
	void LoadSkinManager();
	void MakeRiderList();
	void MakeAllocateGroup();
	void MakeAllocateGroupCombo(CComboBox *pCombo, BOOL bAllInsert = FALSE);
	void FillCompanyChargeList(CComboBox *pCombo);
	
	void MakeChargeSectionType();
	int GetChargeSectionValue(long nBasicCharge, long nDiscountCouPhoneMileType, long nABCDType, long nSectionValue);
	void UpdateAllocateGroup(int nGNo, CString strName);
	void SetCurView(UINT nCurView);
	UINT GetCurView();
	void OpenAllocateDlg(long nTNo, long nState, CString sTitle = "", long nRNo = 0, long nDeposit = 0, long nCarType = 0, BOOL bToRcpView = TRUE,CWnd *pParent = NULL);
	void OpenOtherAllocateDlg(long nTNo, long nCompany, long nState, long nDeposit = 0, BOOL bToRcpView = TRUE,CWnd *pParent = NULL);
	void DestorySearchPoiDlg();
	void OpenTranDlg(long nTNo, long nCompany);
	CString GetCorpDomain();

	CRcpView* GetRcpView();

	CGroupChatDlg *GetGroupChatPane(){return m_pGroupChatPane;};
	CAllocatePaneDlg *GetAllocatePane(){return m_pAllocatePane;};
	CEmptyCarDlg1 *GetEmptyCarPane(){return m_pEmptyCarPane;};
	CDelayOrderDlg2 *GetDelayOrderPane(){return m_pDelayOrderPane;};
	CConsignLinkDlg *GetConsignLinkDlg(){return m_pConsignLinkDlg;};

	void SetRcpView(CRcpView *pRcpView)					{m_pRcpView = pRcpView;};
	void SetReportView(CReportView* pReportView)		{m_pReportView = pReportView;};
	void SetReportRiderView(CReportRiderView* pReportRiderView)		{m_pReportRiderView = pReportRiderView;};
	void SetCustomerView(CCustomerView* pCustomerView)	{m_pCustomerView = pCustomerView;};
	void SetStaffView(CStaffView* pStaffView)			{m_pStaffView = pStaffView;};
	void SetIncomeView(CIncomeView* pIncomeView)		{m_pIncomeView = pIncomeView;};
	void SetStatView(CStatView* pStatView)				{m_pStatView = pStatView;};
	void SetHomeView(CHomeView* pHomeView)				{m_pHomeView = pHomeView;};
	
	void SetGroupChatPane(CGroupChatDlg* pGroupChatDlg){m_pGroupChatPane = pGroupChatDlg;};
	void SetAllocatePane(CAllocatePaneDlg* pAllocatePane){m_pAllocatePane = pAllocatePane;};
	void SetEmptyCarPane(CEmptyCarDlg1* pEmptyCarPane){m_pEmptyCarPane = pEmptyCarPane;};
	void SetDelayOrderPane(CDelayOrderDlg2* pDelayOrderPane){m_pDelayOrderPane = pDelayOrderPane;};

	BOOL GetRightOfMessenger(BOOL bMsgBox = TRUE);
	BOOL ReleaseRightOfMessenger();
	void GetRightOfAllocation(BOOL bMsgBox = TRUE);
	void ReleaseRightOfAllocation();
	CBranchInfo* SearchLineGroup(char *szLine);
	void SendCIDInfo(char *szData);
	void ShowRecvCidDlg();
	void CloseRecvCidDlg();
	BOOL SendCopyDataToTelClient(char *szBuff, long nType = 30, BOOL bInsert = TRUE); // 30이 고객, 40이 기사
	void ShowMessenger();
	void RunRemoteControl(int nType);
	BOOL ChangeBranchItemInTaskPanel(CXTPTaskPanel *pTaskPanel, CBranchInfo *pBi, CXTPDockingPane *pwndPane);
	BOOL CreateToolBox(CXTPTaskPanel **pTaskPanel, CWnd *pOwner);
	void ResetToolboxItems(CXTPTaskPanel *pwndTaskPanel);
	void SetTaskPanel(CXTPTaskPanel *pTaskPanel);
	CXTPTaskPanel* GetTaskPanel();
	void SetTitlePrint(CString strText);
	LRESULT OnTaskPanelNotify(WPARAM wParam, LPARAM lParam, CXTPDockingPane *pwndPane, 
				CXTPDockingPaneManager *pwndManager, CWnd *pwndCurView);
	void InitPaneManager(CXTPDockingPaneManager *paneManager, CWnd *pwndOwner);
	void MakeNetworkPane(CXTPDockingPaneManager *pwndPaneManager, CXTPDockingPane **pwndPaneNetwork, 
			CXTPTaskPanel *pwndTaskPanel, long nStartBranchID);
	CWnd* AddView(CWnd *pThis, CXTPTabControl *pTabCtrl, CRuntimeClass* pViewClass, 
				LPCTSTR lpszTitle, int nIcon = 0,int nID = 0, BOOL bInitailUpdate = TRUE,
				BOOL bActive = FALSE);
	void MakeDepositRate();
	long GetDepositRate(UINT nCompany, UINT nCharge);
	void UpdateDepositRate(UINT nCompany, UINT nCharge, UINT nDeposit);
	void ShowRiderInfoDlg(long nCompany, long nRNo, long nOrderCompany = -1, 
			long nTNo = -1, CString strCallBranch = "", long nState = -1, long nPayType = -1, CString strRiderCIDPhone = "");
	void CreateFormViewTabControl(CWnd *pParent, CXTPTabControl *pTabCtrl, CRect rc = CRect(0, 0, 0, 0), XTPTabPosition nPosition = xtpTabPositionTop);
	CSimpleMapDlg* GetSimpleMap(BOOL bShow = FALSE, BOOL bIfExists = FALSE);
	CRcpDlgMapDlg* GetRcpDlgMap(CRcpDlg *pRcpDlg, BOOL bShow = FALSE, BOOL bIfExists = FALSE);
	BOOL ForceLeavingWork(long nCompany, long nRNo);
	CRiderMapDlg* CreateRiderMapDlg();
	CRiderMapDlg* CreateRiderMapDlg2();
	CRiderMapDlg* _CreateRiderMapDlg(CRiderMapDlg **pRiderMapDlg, BOOL bOtherRiderMap);
	CRiderShareBoardDlg* CreateRiderShareBoardDlg(long nCompany = 0, long nRNo = 0, CString strRealRName = "");
	CRiderBoardDlg* CreateRiderBoardDlg();
	CAllocateBoardDlg* CreateAllocateBoardDlg();
	CAllocateBoardTRSDlg* CreateAllocateBoardTRSDlg();
	CRiderMapDlg* GetRiderMapDlg();
	CRiderMapDlg* GetRiderMapDlg2();
	CAllocateBoardDlg* GetAllocateBoardDlg();
	void CreateChargeForRiderLogDlg();
	void CloseRiderMapDlg();
	void CloseAllocateBoardDlg();
	void CloseAllocateBoardTRSDlg();
	void Destroy();
	BOOL IsDetailPos(long nDongID, long nPosX, long nPosY);
	ST_ALLOC_RIDER* GetAllocRider(long nCompany, long nRNo);
	BOOL UpdateRiderInfoForReserveOrder(long nTNo, long nRiderCompany, long nRNo);
	long GetShareBalance(long nCompany);
	BOOL IsOtherShareBalanceOk(long nDeposit, long nRiderCompany);
	void ShowCallPhoneRiderDlg(long nRiderCompany, long nRNo, long nOrderCompany, BOOL bDaeriRider);
	void ShowSearchPOIDlg(CString strKeyword, CRcpPlaceInfo *pPlace, long nCompany, 
								 CWnd *pParent, CWnd *pPositionWnd = NULL, CWnd *pNextWnd = NULL, BOOL bGetEvent = TRUE);
	void ChargeAddDataInitLoad();
	BOOL IsTimeChargeCompany(long nCompany);
	BOOL LoadMemberCharge(BOOL bInit = FALSE);
	void ShowMemberChargeDlg( BOOL bOnlyCreate = FALSE);
	CChargeHistoryMemDlg * GetMemberChargeDlg();
	CLogiMapCns* GetLogiMapCns();
	void ShowSecurityLogDlg();	
	void AddRiderPos(CRealTimeRiderPos &pos, COleDateTime dtUpdate = COleDateTime::GetCurrentTime());
	CRiderSubInfo* GetRiderPos(long nCompany, long nRNo);
	void OnAutoSelectEvent(int nType, BOOL bJustRefresh, BOOL bFocusNotChange, BOOL bSelectWhenSingleResult);
	CMyMkMessenger *GetMessenger() { return m_pMsg; }
	CSearchPOIDlg* GetSearchPOIDlg() {return m_pSearchPOIDlg;};
	void HideSearchPOIDlg();
	void ChargeContainerShow();
	void PlayRecFile(COleDateTime dtDate, CString strFolderDate, CString strKeyPhoneID, CString strTellNumber, CString strFileName, long nBound);
	void InitChargeContainer(CWnd *pWnd);
	void GpsPosRevision(long &nPosX, long &nPosY, long nDeviceType, CString strDeviceName, CString strVersion);
	void OpenCurOrderState(long nTNo);
	void MakePoiAndCusData();
	CBranchInfo* GetConsignMakeBranchInfo(CString sCity);
	long GetConsignCustomerCNo(CString sCity);
	long GetConsignCustomerCNoTelID(CString sCity);		
	BOOL IsConsignCity(CString sCity);
	CConsignLinkDlg* OpenConsignLinkDlg(long nTNo,long nCompany, CRcpPlaceInfo *pStartPoi, 
		CRcpPlaceInfo *pDestPoi, long nConsignTNo,long nTerminalWayID,
		CString sConsignCity,CRcpDlg *pWnd, BOOL bRcpViewShow = FALSE);

	
	CMakeGroupReportNewDlg* OpenGroupReportDlg(CWnd *pWnd,long nReportNo,long nGNo, int nNewMode, COleDateTime dtFrom, COleDateTime dtTo,
		CString strGNoList, long nCalculateCount, long nCalculateSum,long nCalculateTrans);
	void CreateRcpDlg(CString strName, long nTNo, long nState);
	CString GetCustomerName(long nCNo);
	void MakeFunctionTable();
	CString GetSpecialLog() { return m_strSpecialLog; }
	void AddSpecialLog(const char* format, ...);
	BOOL SendGcmMsgForSmartQ2(long nTNo);
	CString GetRecordFileServerIP(COleDateTime dtDate);
	CString GetAllocateGroup(int nCurGroup);
	BOOL IsShareInfoShowOk();
	void SetTodayCompleteCount(long nCount) {m_nTodayCompleteCount = nCount;}
	void SetYesterDayCompleteCount();
	BOOL IsSSNOk(CString strSSN);
	BOOL IsOtherCompanyRegist(CString strSSN, long nCompany, long nRNo);

	void SaveLogOut(BOOL bRunTimeError = FALSE);
	void LogOutRestore();
	BOOL IsSystemFile(CString strFileName);
	void InsertINaviCnsLog(BOOL bSuccess, CString strParameter, CString strResult, CString strLocation);
	CString SendEMailCardResult(int tno, CString send_customer_email, bool re_send = false);

	CString GetReplaceChar(CString strInput, CString strSendTel, CString strReceiveTel, CString strRiderPhone);
	void ConvChar(CString& input, CString keyword, CString conv);

protected:
	int MessageBox(CString strMsg, CString strCaption = "", UINT nType = MB_OK | MB_ICONINFORMATION);
	void ModifyRecord(ST_MEMBER_CHARGE_CNO* stNew);
	BOOL GetGcmIDForSmartQ2(long nTNo, CString& strGcmID, CString& strText);
	CString GetFileExtension(CString strFileName);
	CString CheckCardEmailResend(int tno, CString send_customer_email);
	CString GetEncodeForEMail(CString content);
	CString GetCardEmailBody(CString body_url);
	std::string ChangeMultiByteToUtf8(CString content);
	std::string base64_encode(const std::string& in);
	void InsertCardEmailResendLog(int tno, CString send_customer_email);
	void MakeRiderInfoDlg();
	COleDateTime  m_dtCur;

protected:
	CString m_strSpecialLog;
	CWnd *m_pFrameWnd;
	CQSocketSystem m_SockSystem;
	BOOL m_bDebugMode;
	CTaskbarNotifier *m_pwndTaskbarNotifier;
	CNotifierContainer *m_pwndNotifierContainer;
	CXTSplitterWnd* m_pwndSplitter;
	UINT m_nCurView;
	CRiderMapDlg *m_pRiderMapDlg;
	CRiderMapDlg *m_pRiderMapDlg2;
	CAllocateBoardDlg *m_pAllocateBoardDlg;
	CAllocateBoardTRSDlg *m_pAllocateBoardTRSDlg;
	CRiderShareBoardDlg *m_pRiderShareBoardDlg;
	CRiderBoardDlg *m_pRiderBoardDlg;
	CAllocateDlg *m_pAllocateDlg;
	COtherRiderDlg *m_pOtherRiderDlg;
	CCallPhoneDlg *m_pCallPhoneDlg;
	CSearchPOIDlg *m_pSearchPOIDlg;
	CChargeHistoryMemDlg* m_pChargeHistoryMemDlg;
	CChargeContainer *m_pChargeContainer;
	COrderProcessStateDlg	*m_pOrderProcessStateDlg;
	CString m_strOriginalWindowTitle;
	CConsignLinkDlg			* m_pConsignLinkDlg;
	CMakeGroupReportNewDlg	* m_pMakeGroupReportNewDlg[5];
	CTransInfoDlg			* m_pTransInfoDlg;

public:

	long m_nTodayCompleteCount;
	long m_nYesterDayCompleteCount;

	BOOL m_bRecvRiderPosMsg;
	CXTPTaskPanel *m_pwndTaskPanel;
	CMyMkMessenger *m_pMsg;	
	CRecvCidDlg *m_pRecvCidDlg;
	CDialogBar* m_pwndFieldChooser; 
	CRcpView *m_pRcpView;
	CReportView *m_pReportView;
	CReportRiderView *m_pReportRiderView;
	CCustomerView *m_pCustomerView;
	CStaffView *m_pStaffView;
	CIncomeView *m_pIncomeView;
	CStatView *m_pStatView;
	CHomeView *m_pHomeView;
	UINT m_nTimeOfCheckNotice;
	MAP_ALLOC_RIDER m_mapAllocateRider;	
	MAP_ALLOCATE_GROUP m_mapAllocateGroup;;
	CDelayOrderDlg2 *m_pDelayOrderPane;
	CEmptyCarDlg1 *m_pEmptyCarPane; //m_pwndPane4
	CAllocatePaneDlg *m_pAllocatePane; //m_pwndPane5
	CGroupChatDlg *m_pGroupChatPane;
	CConnListDlg2 *m_pConnListPane; //m_pwndPane5
	CXTPDockingPaneManager m_paneManager;
	CXTPDockingPane *m_pwndPaneNetwork;
	CXTPDockingPane *m_pwndPane2;
	CXTPDockingPane *m_pwndPane3;
	CXTPDockingPane *m_pwndPane4;
	CXTPDockingPane *m_pwndPane5;
	CXTPDockingPane *m_pwndPane6;
	CXTPDockingPane *m_pwndPane7;
	CWnd* m_pwndCur;
	CShowRiderInfoDlg *m_pRiderInfoDlg;
	CSimpleMapDlg *m_pSimpleMapDlg;
	CRcpDlgMapDlg *m_pRcpDlgMapDlg;
	CChargeAdd *m_pChargeAdd;
	CLogiMapCns *m_pLogiMapCns;
	CRiderSubInfoMap m_mapRiderSub;
	CFunctionTableDlg * m_pFunctionTableDlg;	

	long m_nCopyFormViewCnt = 0;

	class CRcpDlgAdmin* m_pRcpDlgAdmin = nullptr;
	CRcpDlgAdmin* GetRcpDlgAdmin() { return m_pRcpDlgAdmin; }

};
