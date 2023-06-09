#pragma once


#include "POIDataNew.h"
#include "RcpDlgBase.h"
#include "afxwin.h"
#include "FlatEditInsung.h"
#include "FlatComboBoxInsung.h"
#include "FlatButton.h"
#include "FlatStatic.h"
#include "PPTooltip.h"

#define RCP_STATIC_COUNT 63
#define MAX_PHONE_NUMBER 10

class CRcpPlaceInfo;
class CCharge;
class CDisplayChargeInfo;
class CRcpView;
class CAllocateDlg3;
class CDelayOrderDlg2;
class CHistoryDlg;
class CRcpCopyData;
class COrderProcessStateDlg;
class CSearchPOIDlg;
class CReserveOrderDlg;
class CSearchManagerDlg;
class CConsignLinkDlg;
class CCreditHistoryDlg;
// CRcpDlg 폼 뷰입니다.

typedef struct{
	CEdit *pEdit;
	CFlatEdit2 edtFlatEdit2;
	CFlatEditInsung edtFlatEditInsung;
} ST_EDIT;

typedef struct{
	CButton *pButton;
	CButton button;
	CFlatButton buttonFlat;
} ST_BUTTON;

typedef struct{
	CStatic *pStatic;
	CFlatStatic stcFlat;
	CMarkupStatic stcMarkup;
} ST_STATIC;

enum { ID_MENU_RIDER_ALLOC_CANCEL = 0xFF20,
ID_MENU_RIDER_ALLOC,
ID_MENU_RIDER_ALLOC_OTHER,
ID_MENU_RIDER_CALL, 
ID_MENU_RIDER_POS,
ID_MENU_ST_RIDER_WORK_STATE_INFO_SHOW};

#define WM_GET_ALLOCATE_RIDER WM_USER + 100
#define MAX_VIA_COUNT 3
class CRcpDlg : public CRcpDlgBase
{
	DECLARE_DYNAMIC(CRcpDlg)

public:
	CRcpDlg();  
	virtual ~CRcpDlg();

public:
	enum { IDD = IDD_RCP_DLG };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PostNcDestroy();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCloseBtn();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnPaint();
	afx_msg void OnCbnSelchangeBranchCombo();
	afx_msg void OnBnClickedNewBtn();
	afx_msg virtual void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedWaitBtn();	
	afx_msg void OnBnClickedNewAfterCopyBtn();
	afx_msg void OnBnClickedWaitAfterCopyBtn();
	afx_msg void OnBnClickedUpdateBtn();
	afx_msg void OnBnClickedStartMapBtn();
	afx_msg void OnBnClickedDestMapBtn();
	afx_msg void OnCbnSelchangeCouponTypeCombo();
	afx_msg void OnEnChangeChargeBasicEdit();
	afx_msg void OnEnChangeChargeAddEdit();
	afx_msg void OnEnChangeChargeDisEdit();
	afx_msg void OnEnChangeChargeSumEdit();
	afx_msg void OnBnClickedQueryChargeBtn();
	afx_msg void NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result);
	afx_msg void OnPhoneControl(UINT nFlag);
	afx_msg void OnPhoneControlSMS(UINT nFlag);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnBnClickedOrderMapBtn();
	afx_msg void OnBnClickedInquiryBtn();
	afx_msg void OnBnClickedNoticeBtn();
	afx_msg void OnBnClickedLogBtn();
	afx_msg void OnCbnSelchangeChargeTypeBombo();
	afx_msg void OnHdnItemclickHistoryList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnEditchangeCouponChargeCombo();
	afx_msg void OnBnClickedInputChargeNewBtn();
	afx_msg void OnBnClickedQueryChargeBtn2();
	afx_msg void OnBnClickedConsignBtn();
	afx_msg void OnBnClickedShowRiderPosBtn();
	afx_msg void OnEnKillfocusChargeBasicEdit();
	afx_msg void OnEnKillfocusChargeSumEdit();
	afx_msg void OnEnKillfocusChargeTransEdit();
	afx_msg void OnBnClickedRiderAutoChargeChk();
	afx_msg void OnLvnItemchangedChargeList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusRiderAutoChargeEdit();
	afx_msg void OnBnClickedJinsangBtn();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnMenuContextFunc(UINT nFlag);
	afx_msg void OnMenuContextItem(UINT nFlag);
	afx_msg void OnMenuContextMileage(UINT nFlag);
	afx_msg void OnMenuContextPlace(UINT nFlag);
	afx_msg void OnMenuContextEtc(UINT nFlag);
	afx_msg	void OnMenuContextCharge(UINT nFlag);
	afx_msg	void OnSpecialTrcukSelect(UINT nFlag);
	
	afx_msg void OnEnChangeOrderEdit();
	afx_msg void OnEnChangeStartEdit();
	afx_msg void OnEnChangeDestEdit();
	afx_msg void OnEnSetfocusOrderEdit();
	afx_msg void OnEnSetfocusStartEdit();
	afx_msg void OnEnSetfocusDestEdit();
	afx_msg void OnEnSetfocusCIDEdit();
	afx_msg void OnBnClickedOrderCustomerDlgBtn();
	afx_msg void OnBnClickedStartCustomerDlgBtn();
	afx_msg void OnBnClickedDestCustomerDlgBtn();

	afx_msg void OnBnClickedOrderMoveBtn();
	afx_msg void OnBnClickedStartMoveBtn();
	afx_msg void OnBnClickedDestMoveBtn();
	afx_msg void OnNMClickLogList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeDelTypeCombo();
	afx_msg void OnBnClickedPayTypePreBtn();
	afx_msg void OnBnClickedPayTypeAfterBtn();
	afx_msg void OnBnClickedPayTypeCreditBtn();
	afx_msg void OnBnClickedCarTypeBtn();
	afx_msg void OnBnClickedCarTypeBtn2();
	afx_msg void OnBnClickedCarTypeBtn3();
	afx_msg void OnCbnSelchangeCarTypeCombo();
	afx_msg void OnCbnSelchangePayTypeCombo();
	afx_msg void OnBnClickedContextChargeBtn();
	afx_msg void OnBnClickedReserveBtn();
	afx_msg void OnBnClickedCidMenuBtn();
	afx_msg void OnCbnSelchangeWayTypeCombo();
	afx_msg void OnCbnSelchangeRunTypeCombo();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedRiderMenuBtn();
	afx_msg void ShowSetupDlg();
	afx_msg void OnBnClickedEtcBtn();
	afx_msg void OnBnClickedContextMileageBtn();
	afx_msg void OnBnClickedRouteMenuBtn();
	afx_msg void OnBnClickedRcpCopyBtn();
	afx_msg void OnEnChangeChargeTransEdit();
	afx_msg void OnBnClickedHistoryBtn();
	afx_msg void OnBnClickedItemMenuBtn();
	afx_msg void OnBnClickedStateMenuBtn();
	afx_msg void OnBnClickedOrderPhoneBtn();
	afx_msg void OnBnClickedOrderPhoneBtn2();
	afx_msg void OnBnClickedStartPhoneBtn();
	afx_msg void OnBnClickedStartPhoneBtn2();
	afx_msg void OnBnClickedDestPhoneBtn();
	afx_msg void OnBnClickedDestPhoneBtn2();
	afx_msg void OnBnClickedEditOrderCheck();
	afx_msg void OnBnClickedEditStartCheck();
	afx_msg void OnBnClickedEditDestCheck();
	afx_msg void OnEnChangeCidEdit();
	afx_msg void OnStnClickedRcpStatic52();
	afx_msg void OnShowOrderLog();
	afx_msg void OnCurOrderState();
	afx_msg void OnEnSetfocusStartDepartEdit();
	afx_msg void OnEnSetfocusChargeBasicEdit();
	afx_msg void OnBnClickedSaveChargeCheck();
	afx_msg void OnBnClickedFoodOrderCheck();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnEnSetfocusOrderDepartEdit();
	afx_msg void OnEnSetfocusDestDepartEdit();
	afx_msg void OnEnKillfocusOrderDepartEdit();
	afx_msg void OnEnKillfocusStartDepartEdit();
	afx_msg void OnEnKillfocusDestDepartEdit();
	afx_msg void OnStnClickedReserveDisplayStatic();
	afx_msg void OnBnClickedShowRouteBtn();
	afx_msg void OnBnClickedEtcMenuBtn1();
	afx_msg void OnBnClickedEtcMenuBtn2();
	afx_msg void OnStnClickedStartAddressStatic();
	afx_msg void OnStnClickedDestAddressStatic();
	afx_msg void OnEnKillfocusOrderAddressEdit();
	afx_msg void OnEnKillfocusStartAddressEdit();
	afx_msg void OnEnKillfocusDestAddressEdit();
	afx_msg void OnEnKillfocusChargeDrivingEdit();

	afx_msg void OnBnClickedAutoShareOrderCheck();
	afx_msg void OnBnClickedUpdateAndNewBtn();
	afx_msg void OnBnClickedOrderDestSameBtn();
	afx_msg void OnBnClickedOrderStartSameBtn();
	afx_msg void OnBnClickedOrderDifferentBtn();
	afx_msg void OnEnChangeCommissionEdit();
	afx_msg void OnBnClickedPayTypeOnlineBtn();
	afx_msg void OnEnChangeChargeDrivingEdit();
	afx_msg void OnBnClickedNotSendCompleteSmsCheck();
	afx_msg void OnBnClickedShowOrderLogBtn();
	afx_msg void OnStnClickedOrderAddressStatic();
	afx_msg void OnBnClickedSmsBtn();	
	afx_msg void OnBnClickedConsignViewBtn();
	afx_msg void OnBnClickedZeroIncomeBtn();
	afx_msg void OnBnClickedUpdateCancelBtn();
	afx_msg void OnBnClickedPayTypeOnlineBtn2();
	afx_msg void OnBnClickedCarTypeBtn4();
	afx_msg void OnBnClickedCarTypeBtn5();
	afx_msg void OnBnClickedWayTypeBtn();
	afx_msg void OnBnClickedWayTypeBtn2();
	afx_msg void OnBnClickedWayTypeBtn3();
	afx_msg void OnBnClickedRunTypeBtn();
	afx_msg void OnBnClickedRunTypeBtn2();
	afx_msg void OnBnClickedRunTypeBtn3();
	afx_msg void OnBnClickedRunTypeBtn4();
	afx_msg void OnBnClickedStartClearBtn();
	afx_msg void OnBnClickedDestClearBtn();
	afx_msg void OnBnClickedRiderSearchBtn();
	afx_msg void OnBnClickedRiderSMSBtn();
	afx_msg void OnBnClickedOrderClearBtn();

public:
	static BOOL MakeSearchQuery(CString strSource, CString &strKeyword, UINT *pnType);

	virtual BOOL JustInsertNewCustomer(int nCtrl = 0);
	virtual void ShowUsageHistory(BOOL bRefresh = FALSE, BOOL bRcpDlgForceSizing = FALSE);
	virtual void RequestCharge(BOOL bClose = FALSE, long nCompany = TRUE, long nRNo = TRUE);
	virtual CString GetCustomerTypeString(long nCNo, long nID, CString strUserID = "");
	virtual void CopyPoiData(CPOIUnit **pDst, CPOIUnit *pSrc, long nPosX = 0, long nPosY = 0);
	virtual void GetPhoneNumberByServer(BCMenu* pRMenu, long nCNo);
	virtual void GetPhoneNumberByClient(BCMenu* pRMenu, UINT nFlagPhone, UINT nFlagMP);
	virtual void GetPhoneNumberByRider(BCMenu *pRMenu);
	virtual void OnRecvEditOrderState(long nTNo, long nTickCount, long nState, CString strWName);
	virtual BOOL GetAddressInfo(BCMenu* pRMenu, long nCNo);
	virtual CString GetJibunFromFullName(CString sFullName);
	virtual BOOL SaveCustomerAddress(long nCNo, long nDongID, CString sDong, CString sAddress);
	virtual long GetGroupTodayUseCharge();
	virtual void SaveCurInfo(ST_EDIT_HISTORY &st);
	virtual CString GetSaveMent(ST_EDIT_HISTORY stPre, ST_EDIT_HISTORY stCur);
	virtual long RequestOrder(ST_EDIT_HISTORY stCur);

	virtual CBranchInfo* GetBranchComboToBranchInfo();
	virtual CString GetDisplayDongAndAddress(long nDongID, CString strDong, CString strAddress);
	virtual long AddNewOrder(BOOL bWait, BOOL bSMS = FALSE, BOOL bAfterCopy = FALSE, long  nConsignLinkTNo = FALSE, BOOL bInserForCard = FALSE);
	virtual BOOL EditOrder(BOOL bWait = FALSE, BOOL bAfterCopy = FALSE, BOOL bAfterRcp = FALSE);

	virtual long GetPayTypeNew();
	virtual long GetWayTypeNew();
	virtual long GetRunTypeNew();
	virtual long GetCarTypeNew();

	virtual void ChangeDistance();

	virtual void SetPayTypeNew(long nPayType);
	virtual void SetRunTypeNew(long nRunType);
	virtual void SetWayTypeNew(long nWayType);
	virtual void SetCarTypeNew(long nType);

	virtual BOOL IsCarType(int nCarType);
	virtual BOOL IsPayType(int nPayType);
	virtual BOOL IsWayType(int nWayType);
	virtual BOOL IsRunType(int nRunType);

	virtual BOOL GetCreditCount(long &nCreditCount, long &nCreditCharge);

	virtual void OnCancel();
	virtual LONG OnGetCnsInfo(WPARAM wParam, LPARAM lParam);
	virtual LONG OnHistoryChargeApply(WPARAM wParam, LPARAM lParam);	
	virtual LONG OnChangePoi(WPARAM wParam, LPARAM lParam);
	virtual LONG OnPreChargeInit(WPARAM wParam, LPARAM lParam);

	virtual void OnNotCompanyMileage(); 
	virtual void OnNotOrderMileage();
	virtual void OnUseOrderMileage();
	virtual void OnUserMileage();
	virtual void OnMileagePopupWindow();
	virtual void OnMenuCountMileageLog();	
	virtual void OnMenuMileageMode();
	virtual void OnMenuConsignMode();	

	virtual void InitControl();
	virtual void ReInitControl();
	virtual void InitControlAfterGetData();
	virtual void InitCommon();
	virtual void InitData();
	virtual long GetMatchCmb(UINT nFlag);
	virtual long RefreshCharge(BOOL bApplyChargeSum = TRUE, BOOL bApplyAddCharge = TRUE);
	virtual void SetMileageData(int nAutoCharge , int nMileageValue, BOOL bRefreshCharge=FALSE);

	virtual void ShowChargeBet(long nIndex);
	virtual BOOL GetBitmapFromImageList(CImageList *imglist,int nIndex,CBitmap &bmp);

	virtual void ChangeChargeFromQuery(long nCharge);
	virtual BOOL IsRequesting();

	virtual void CheckCustomerUsageCharge(long nBasicCharge);
	virtual void InsertCharge(BOOL bShuttle);
	virtual BOOL MileageUse(long nOrderCNo);
	virtual void OnRcpCopyData(CRcpCopyData *pData);
	virtual BOOL IsGroupInsertOk();
	virtual long CheckAddOptionCharge();
	virtual void SetDiscountType(long nGNo, long nDiscountType, long nDiscount );
	virtual long CheckAddDisCharge(long nChargeInputBasic = 0);
	virtual void CheckOrderAfterChange(long nDeposit, CString sEtc);
	virtual long GetRiderRealDeposit(ST_EDIT_HISTORY *pStruct);

	virtual BOOL IsOrderAfterChange(long &nFinalDeposit, CString &sEtc);
	virtual BOOL IsOrderAfterChangeDetail(long &nFinalDeposit, CString &sEtc);

	virtual void ReLocationAddCustomerBtn();
	virtual void AddEtcOK();
	virtual void ShowSearchPOIDlg(CString strKeyword, CRcpPlaceInfo *pPlace, BOOL bFromGetFocus, CWnd *pNextFocus, 
		BOOL bJustSearch = FALSE, BOOL bChangeMapPos = TRUE, int nSearchType = TYPE_AUTO);
	virtual CRcpPlaceInfo* GetPlaceInfo(int nID);
	virtual void GotoNextFocus(int nID);
	virtual void SetDiscountInfoInit();
	virtual void SetDiscountInfo(BOOL bCreditAfterDis, long nDiscount, long nDiscountType, long nDiscountRange, BOOL bDiscountApplyOnlyCredit);
	virtual void SetMileageInfo(long nMileageType, long nMileageValue, long nMileageBalance, long nCNo,  long nMemCNo);
	virtual void SetChargeOrCouponInfo(long bCredit, BOOL nPriceGrade, int nCouponCharge, int nCouponType);
	virtual int SearchEditVK_RETURN(int nID, BOOL bSelectWhenSingleResult = FALSE);
	virtual void ShowPlaceMenu(int nSubMenu);
	virtual BOOL SearchCID();
	virtual void HideSearchPOIDlg();
	virtual void UserCNSClose();
	virtual void OnMenuSetSms(UINT nID);

	//* 요금관련 부분
	virtual long GetNowChargeControlAmount();
	virtual BOOL ChangePOIConfirmString(int nModifyPoiConfirmCharge, long nOldCharge, long nNewCharge);
	virtual BOOL IsPreChangePOI();
	virtual long GetSectionCharge(BOOL bMustApply = FALSE, int nModifyPoiConfirmCharge = 0,  BOOL bCashCharge = FALSE, BOOL bTypeCelChange = FALSE);
	virtual BOOL IsStartDestPoi();
	virtual long GetRcpBasicCharge();
	virtual long GetStringChargeToNumber(CString strCharge);
	virtual CString GetChargeBet();
	virtual BOOL IsNoGroupCharge(long nGNo = 0);
	// 탁송관련
	virtual BOOL IsConsignApply(BOOL bConsignButton = FALSE);		 

	virtual void SetConsignMode(BOOL bConsignMode);
	virtual void SetConsignInit();
	virtual void SetConsignViewInfo(long nConsignTNo,long nConsignCommission,long nBackOrderChargeSum);

	virtual void RefreshOrderLog(int nTNo);
	virtual void MakeRectangle(CDC *pDC, long nLeftID, long nRightID, 
		BOOL bRightControlToHeight = FALSE,
		CRect rcMargin = CRect(4, 4, 6, 4),
		COLORREF clrTopLine = RGB(180, 180, 180), 
		COLORREF clrBottomLine = RGB(150, 150, 150), 
		COLORREF clrLeftLine = RGB(180, 180, 180), 
		COLORREF clrRightLine = RGB(150, 150, 150), long nBorder = 1, long nColSpan = 0);
	virtual void MakeLine(CDC *pDC, long nLeftID, long nTopID, long nRightID, long nBottomID,
		long nLeftOfffset = 0, long nRightOffset = 0, 
		COLORREF clrLine = RGB(180, 180, 180));

	// 마일작업
	virtual BOOL IsSpanMile();
	virtual long CRcpDlg::GetMileageControlAmount();
	virtual long CRcpDlg::GetRiderAutoChargeControlAmount();
	virtual void CRcpDlg::OnEnChangeRiderAutoChargeEdit();

	virtual void DisplayReserveInfo();
	virtual void DisplayRiderInfo();
	virtual void MakeReserveDlg();
	virtual void MakeSearchManagerDlg();
	virtual void ShowReserveDlg();
	virtual void ShowSearchManagerDlg(BOOL bMoveOnly = FALSE);
	virtual void ShowPlaceCustomerDlgBtn(CRcpPlaceInfo *pPlace, BOOL bSearchCustomer = FALSE);
	virtual void OnMenuContextCID(UINT nID);
	virtual void OnMenuContextRider(UINT nID);
	virtual void Construct(BOOL bFirstInit);
	virtual void AllocateRider(long nTNo, long nState, long nDeposit);
	virtual BOOL CheckDeposit();
	virtual BOOL CheckChargeRound();
	virtual void CheckMileage(long &nMileageSetting, long &nMileageAutoCharge);	
	virtual void OnPassData();
	virtual void CheckDrivingChargeChange();
	virtual void ShowNameSearch(CEdit *edtName, CEdit *edt);
	virtual void DisplayChargeInfo(BOOL bHasData = FALSE);
	virtual void CheckCardTax();
	virtual long GetDeposit(long nTotal);
	virtual LONG OnGetAllocateRider(WPARAM wParam, LPARAM lParam);
	virtual BOOL GetRouteDistance(BOOL bShowMap, BOOL bViaApply,BOOL bChargeCalculate, int  nModifyPoiConfirmCharge);
	virtual BOOL IsUseDirectDistance();
	virtual BOOL OnPretransMessageWM_KEYUP(MSG *pMsg);
	virtual void ReSetItemCombo();
	virtual void OnMenuCall(UINT nID);
	virtual void ShowAutoEditMsg(CButton *pBtn, CString strPlace);
	virtual void SetButtonShowHide();
	virtual void OpenManagerSearchDlg();
	virtual void ChangeRcpDlgSize(BOOL bOriginal, BOOL bForceChange = FALSE);
	virtual void HideReserveBehindControl(BOOL bHide, BOOL bConstruct = FALSE);
	virtual BOOL IsEditMode() { return m_nInitItem > 0; }
	virtual void RepositionAddressControl(CFlatEdit2 &edt, CStatic &stc, CRcpPlaceInfo *pPlace = NULL, BOOL bShowEdit = FALSE);
	virtual void OnInitialUpdate();
	virtual void AddStringToEtc(CString strAdd, BOOL bFront = TRUE);
	virtual void ShowSearchPOIDlgForAddressEdit(CFlatEdit2 *pEdit, CRcpPlaceInfo *pPlace, CWnd *pNextFocus);
	virtual void GetCompanyCodeForRevisitCustomer(long &nCompany, long &nLastDay, long &nCNo);
	virtual void UpdateRevisitCustomerInfo(long nTNo);
	virtual BOOL CheckAutoSave();
	virtual BOOL CheckAutoSaveServer(CString strCID);
	virtual void RefreshConsignCharge();
	virtual double round( double value, int pos );
	virtual void OnOpenRcpDlg();
	virtual long InsertRevisitCustomerLog(BOOL bChangeBranch, BOOL bInnerCallCenter, long nOriginalCNo, long nPreCompany);
	virtual BOOL IsCreditOrderInsertOk();
	virtual long GetCardPayVaild();
	virtual void RefreshRcpDlg(long nState = 0);
	virtual BOOL IsCardPayed() {return m_nCardProcess == NICE_CARD_COMPLETE || m_nCardProcess == NICE_CARD_COMPLETE_QUICKCALL;}
	virtual void ShowCardPayInfo();
	virtual BOOL CheckChangeOk();
	virtual void InsertChargeChangeRequest();
	virtual long UserDefineEmergencyQuickCall(long nBasicCharge);
	virtual long UserDefineEmergencyCharge(long nBasicCharge, long nAddWayCharge);
	virtual long UserDefineBothCharge(long nBasicCharge);
	virtual long UserDefinenBothQuickCall(long nBasicCharge);
	void SendMsgForReserve();
	BOOL SearchRegion(UINT nCtrl, BOOL bMustCheckDongSearch = FALSE, BOOL bExpandLiData = FALSE);
	BOOL IsDongSearch(CString strDong);
	void MakeSearchPOIDlgForSerchPopup();
	virtual void ShowCreditHistory(BOOL bRefresh);
	virtual void HideSubHistoryDlgExeMe();
	void ShowSign();
	char* GetInsertData(CRcpCopyData &data); 

	void DeleteBillkey();
	void AllocRiderInfo();

	virtual void ShowCustomerInnerMemo(CString strMemo);
	virtual void AddTran();
	virtual void InitEtcCombo();
	virtual BOOL IsReserve();
	virtual BOOL ReserveCheck();
	virtual long GetReleaseStateDB();
	virtual COleDateTime GetReserveTime();
	virtual long GetReleaseMin();
	virtual BOOL IsReleaseAfterWait();
	virtual void SetReserveState(COleDateTime dtReserve, long nReserveAfter, long nReserveReleaseMin);
	virtual void InitReserveState() {};

	CString GetReserveTimeString();
	void RefreshProperCharge();
	long GetCarTypeChargeTemp();
	BOOL IsNeedRequest();
	void InsertCnsLog(long nTNo, long nDistance);
	void InitRiderInfo();
	BOOL ReserveOption();
	BOOL CheckCompanyEmp();
	int GetSpecialTruckType();
	void SetSpecialTruckType(int special_truck_type);
	
public:
	COrderProcessStateDlg *m_pOrderProcessStateDlg;

	CRcpPlaceInfo *m_pOrder;
	CRcpPlaceInfo *m_pStart;
	CRcpPlaceInfo *m_pDest;
	CRcpPlaceInfo *m_pMenuSelPlace;

	CRcpPlaceInfo *m_pCNSCheckStart;
	CRcpPlaceInfo *m_pCNSCheckDest;

	ST_EDIT_HISTORY m_stPreInfo;
	CDelayOrderDlg2 *m_pDelayOrderPane;

	DWORD m_dwAnswerTick;

	CCharge * m_pCharge;
	CDisplayChargeInfo *m_pDisplayChargeInfo; // 요금툴팁..
	CSearchPOIDlg *m_pSearchPOIDlg;
	CSearchManagerDlg *m_pSearchManagerDlg;
	CReserveOrderDlg *m_pReserveOrderDlg;
	CConsignLinkDlg *m_pConsignLinkDlg;
	CHistoryDlg *m_pHistoryDlg;
	CCreditHistoryDlg *m_pCreditHistoryDlg;

	CXTPListCtrl2 m_lstOrderLog;

	CBitmap bitmap;	
	CBitmap m_bmpOK, m_bmpX, m_bmpTemp;
	ST_ADDRESS m_stAddress[10];

	CFlatEdit2 m_edtCNS;	
	CFlatEdit2 m_edtDestMP;	
	CFlatEdit2 m_edtOrderCNo;	
	CFlatEdit2 m_edtOrderDetail;

	CFlatEdit2 m_edtOrderMemo;
	CFlatEdit2 m_edtOrderMP;
	CFlatEdit2 m_edtIntercallEtc;
	CFlatEdit2 m_edtSmsPhone;
	
	CFlatEdit2 m_edtStartMP;

	ST_EDIT m_EDT_CID;
	ST_EDIT m_EDT_TNO;
	ST_EDIT m_EDT_STATE;
	ST_EDIT m_EDT_WNAME;
	ST_EDIT m_EDT_ETC;

	ST_EDIT m_EDT_ORDER_PHONE;
	ST_EDIT m_EDT_ORDER_NAME;
	ST_EDIT m_EDT_ORDER_DEPART;
	ST_EDIT m_EDT_ORDER_MANAGER;

	ST_EDIT m_EDT_START;
	ST_EDIT m_EDT_START_NAME;
	ST_EDIT m_EDT_START_DEPART;
	ST_EDIT m_EDT_START_MANAGER;
	ST_EDIT m_EDT_START_DONG;
	ST_EDIT m_EDT_START_PHONE;
	ST_EDIT m_EDT_START_DETAIL;

	ST_EDIT m_EDT_DEST;
	ST_EDIT m_EDT_DEST_NAME;
	ST_EDIT m_EDT_DEST_DEPART;
	ST_EDIT m_EDT_DEST_MANAGER;
	ST_EDIT m_EDT_DEST_PHONE;
	ST_EDIT m_EDT_DEST_DONG;
	ST_EDIT m_EDT_DEST_DETAIL;

	ST_EDIT m_EDT_CHARGE_DRIVING;
	ST_EDIT m_EDT_CHARGE_ADD;
	ST_EDIT m_EDT_CHARGE_BASIC;
	ST_EDIT m_EDT_CHARGE_DIS;
	ST_EDIT m_EDT_CHARGE_SUM;
	ST_EDIT m_EDT_CHARGE_TRANS;

	ST_STATIC m_STC_START_ADDERSS;
	ST_STATIC m_STC_DEST_ADDERSS;

	CFlatEdit2 m_edtStartCNo;
	CFlatEdit2 m_edtDestCNo;
	CFlatEdit2 m_edtOrderDong;
	CFlatEdit2 m_edtDeposit;
	CFlatEdit2 m_edtMileageBalance;
	CFlatEdit2 m_edtAutoCharge;
	CFlatEdit2 m_edtValueAdd;
	CFlatEdit2 m_edtOrder;
		
	CFlatEdit2 m_edtConBackOrderCharge;
	CFlatEdit2 m_edtConCommissionCharge;
	CFlatEdit2 m_edtConTotalCharge;
	CFlatEdit2 m_edtChargeSumTotal;
	CFlatEdit2 m_edtOrderAddress;
	CFlatEdit2 m_edtStartAddress;
	CFlatEdit2 m_edtDestAddress;
	CFlatEdit2 m_edtMileReserve;

	CFlatEdit2 m_edtChargeReturn;

	CComboBox m_cmbCouponCharge;
	CComboBox m_cmbCouponType;	
	CFlatComboBoxInsung m_cmbItemType;

	CButton m_btnOrderDestSame;
	CButton m_btnOrderStartSame;
	CButton m_btnOrderDifferent;
	CButton m_btnPayType1;
	CButton m_btnPayType2;
	CButton m_btnPayType3;
	CButton m_btnPayType4;
	CButton m_btnCarType1;
	CButton m_btnCarType2;
	CButton m_btnCarType3;
	CButton m_btnContextCharge;
	CButton m_btnDestMap;
	CButton m_btnNewAfterCopy;
	CButton m_btnNew;
	CButton m_btnOrderMap;
	CButton m_btnQueryCharge;
	CButton m_btnQueryCharge2;
	CButton m_btnRcpCopy;
	CButton m_btnRiderCall;
	CButton m_btnShowRiderPos;
	CButton m_btnStartMap;
	CButton m_btnWaitAfterCopy;
	CButton m_btnWait;
	CButton m_btnContextMileage;
	CButton m_btnConsignView;
	CButton m_btnNotice;
	CButton m_btnInquiry;
	CButton m_btnUpdate;
	CButton m_btnUpdateAndNew;
	CButton m_btnUpdateCancel;
	CButton m_btnInputNewCharge;
	CButton m_btnClose;
	CButton m_btnConsign;
	CButton m_btnConsignLink;
	CButton m_btnEtc;
	CButton m_chkAutoCharge;
	CButton m_chkSaveCharge;

	ST_BUTTON m_BTN_AUTO_SHARE_ORDER;
	ST_BUTTON m_BTN_NOT_SEND_COMPLETE_SMS;

	CStatic m_stcPicState;
	CStatic m_stcConBackOrderCharge;
	CStatic m_stcConCommissionCharge;
	CStatic m_stcConTotalCharge;
	CStatic m_stcOrder;
	CStatic m_stcStart;
	CStatic m_stcDest;
	CMyStatic m_stcRcp[RCP_STATIC_COUNT];
	
	CMarkupStatic m_stcChargeViaBet;
	CMarkupStatic m_stcReserveDisplay;
	CMarkupStatic m_stcOrderAddress;
	CMarkupStatic m_stcRiderInfo;

	CButton m_btnPayType5;
	CButton m_btnCarType4;
	CButton m_btnCarType5;
	CButton m_btnWayType1;
	CButton m_btnWayType2;
	CButton m_btnWayType3;
	CButton m_btnRunType1;
	CButton m_btnRunType2;
	CButton m_btnRunType3;
	CButton m_btnRunType4;

	CMarkupStatic m_stcRiderCompany;
	CMarkupStatic m_stcRiderPhone;
	CButton m_btnRiderSearch;
	CButton m_btnRiderSmsSend;
	CButton m_btnNiceCard;

public:	
	CString m_strExtraTitle;
	BOOL m_bAddCall;
	BOOL m_bTempCNo;
	BOOL m_bInsertCidPhone;
	BOOL m_bNotOrderMileage;    // 마일리지 사용안함
	BOOL m_bOrderSpecialMileage;  // 비정상적 마일리지
	BOOL m_bCopyDlg;
	BOOL m_bCnsServerError;// CNS Server가 에러인경우
	BOOL m_bSearchCNS;
	BOOL m_bInquiryOrder; // 문의오더
	BOOL m_bNoticeOrder; // 공지오더
	BOOL m_bScheduleOrder;
	BOOL m_bDirtyBasicCharge;
	BOOL m_bOrderOK;
	BOOL m_bStartOK;
	BOOL m_bDestOK;
	BOOL m_bSkipChangeDelType;
	BOOL m_bReadyToReuse;
	BOOL m_bAllocRider;
	BOOL m_bAllocRiderMyRider;
	BOOL m_bChangeDrivingCharge;
	long m_bAllocRiderChangeTime; //-1 : 설정 안됨, 0 : 바로배차, 1 : 예약시간 후 배차
	BOOL m_bHistoryMoveDown;
	BOOL m_bInternet;
	BOOL m_bDepositMessage;
	BOOL m_bConsignLink;  //탁송연계오더인지여부	
	BOOL m_bNoSMS;	
	BOOL m_bCoupon;
	BOOL m_bFlashPayEdit;
	BOOL m_bTodayOrder;
	BOOL m_bPOIAutoCompleteOnce;
	BOOL m_bIgnoreEnChangeEvent;
	BOOL m_bCreditAfterDis;
	BOOL m_bEditExampleDlg;
	BOOL m_bOrderUpdated;
	BOOL m_bRiderSmsSend;
	BOOL m_bLoadInit;

	long m_nRevisitCustomer;
	long m_nLastDepartFocus;	
	long m_nOriginalCompany;
	long m_nConsignTNo;
	long m_nTerminalWayID;
	long m_nQueryChargeUniqueID;
	long m_nTransID;
	long m_nRiderCompany;
	long m_nRNo;
	long m_nWebID;
	long m_nToCallingType;
	long m_nLineID;
	long m_nTempCNo;
	long m_nPriceGrade;
	long m_nPersonMileage; 
	long m_nMileageBalance;
	long m_nLoadMileage;
	long m_nLoadChargeRiderAuto;
	long m_nOperatorID; // 수신전화 목록의 등록된f 아이디
	long m_nPayType;
	long m_nWayType;
	long m_nRunType;
	long m_nChargeMemCNo;
	long m_nLoadChargeBasic;
	long m_nDiscountRange;
	long m_nConsignCompany;
	long m_nPreRiderAutoCharge;
	long m_nPreCharge;

	long m_nChargeAdd;	
	long m_nChargeDis;

	int m_nCardProcess;

	int m_nDistance;
	int	m_nModifyPoiConfirmCharge;
	int m_nPersonMileageType;
	int m_nState;
	int m_nPreState;
	int m_nAllocGroup;
	int m_nDiscountType;
	int m_nDiscountValue;
	UINT m_nProcessCns;  //CNS 단계 0:NORNAL 1:역경로 2이상:위치 바꾸기
	long m_nOrderSpecialMileage;
	float m_fDirectDistance;

	COleDateTime m_dt0;
	COleDateTime m_dt1;

	CComboBox m_cmbDelType;
	CComboBox m_cmbPayType;
	CComboBox m_cmbWayType;
	CComboBox m_cmbCarType;
	CComboBox m_cmbRunType;

	ST_COMBO m_CMB_ALLOC_GROUP;
	ST_COMBO m_CMB_CHARGE_TYPE;

	//CComboBox m_cmbAllocGroup;
	//CComboBox m_cmbChargeType;

	CString m_strRiderName;
	CString m_strChargeAddOption;
	CString m_strChargeGeneralOption;
	CString m_strCID;
	CString	m_strTempCompany;
	CString m_strTempDong;
	CString m_strTempTel;
	CString m_strTempDepart;
	CString m_strTempName;
	CString m_strTempLocation;
	CString m_sMileageBalance;
	CString m_strChargeAdd;
	CString m_strChargeBasic;
	CString m_strChargeDis;
	CString m_strChargeSum;
	CString m_strChargeTrans;
	CString m_strChargeDriving;
	CString m_strValueAdd;
	CString m_strMileageAutoCharge;	
	CString m_strCNS;
	CString m_strEtc;
	CString m_strState;
	CString m_strTNo;
	CString m_strWName;
	CString m_strItemType;
	CString m_strDeposit;
	CString m_strCouponCharge;
	CString m_strAllocateGroup;
	CString m_strOldRiderNo;
	CString m_strOldRiderName;
	CString m_strIntercallEtc;
	CString m_strSmsPhone;
	CString m_strYear;
	CString m_strAutoSearchOrderName;
	CString m_strChargeBet;
	CString m_strOMan;
	CString m_strOTel;
	CString m_strDistanceInfo;
	CString m_strConBackOrderCharge;
	CString m_strConTotalCharge;
	CString m_sConCommissionCharge;
	CString m_strConsignCity;
	CString m_strMileReserve;
	CString m_strCallPhone[MAX_PHONE_NUMBER];
	CStringArray m_arryPhone;
	CButton m_chkSameCarTypeOnly;
	afx_msg void OnBnClickedNiceCardBtn();
	CButton m_btnZeroIncome;
	CMarkupStatic m_stcCardState;
	CString m_strChargeReturn;
	CString m_strRPhone;

	afx_msg void OnBnClickedNewRcpDlgBtn();
	CFlatEdit2 m_edtChargeLogi;
	CFlatEdit2 m_edtProperCharge1;
	CFlatEdit2 m_edtProperCharge2;
	afx_msg void OnBnClickedProPerBtn();

	long m_nCNoChargeDriving;
	long m_nCNoDiscount;
	CFlatButton m_chkClientShareOrder;
	long m_nPrePayType;

	CButton m_chkShowPhoneTypeOrder;
	CButton m_chkShowPhoneTypeStart;
	CButton m_chkShowPhoneTypeDest;
	afx_msg void OnBnClickedRunTypeBtn5();
	CFlatEdit2 m_edtChargeCompany;

	void OnPayCash();
	void OnReSendEMail();

	CButton m_chkAbleAllocLoadIns;
	CButton m_chkFoodOrder;
	CButton m_chkDirectDistance;

	BOOL m_bPreFoodOrder;
	COleDateTime m_dtPreFoodComplete;

	CPPToolTip m_tooltip;
	afx_msg void OnBnClickedDirectDistanceCheck();
	afx_msg void OnEnChangeChargeCompanyEdit();

	long CheckAllbaroRoound(long nCharge);

	BOOL m_nReserveAfter;
	CFlatEdit2 m_edtChargeRevision;
	CString m_strChargeRevision;
	afx_msg void OnEnChangeTnoEdit();
	void SelectBranchCombo();
	afx_msg void OnBnClickedCallPassBtn();
	void ChangeCargoControl();
	CButton m_btnCallPass; 

	CButton m_chkCargoJabara;
	CButton m_chkCargoLift;
	CButton m_chkCargoWingBody;
	CButton m_chkCargoLiftWing;
	CButton m_chkCargoFreezer;
};
