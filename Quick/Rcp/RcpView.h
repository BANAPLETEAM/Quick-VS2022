#pragma once

#include "RcpViewBase.h"


class COrderProcessStateDlg;
class CVirtualRecord;
class CMakeHtmlTable;
class CShowRiderInfoDlg;
class CWebOrderDlg;
class CNewRiderStateDlg;
class CRcpSearchTruckTypeDlg;
class CRcpSearchCarTypeDlg;
class CRcpSearchPayTypeDlg;
class CRcpMultiStateChange; 
class CReceiptPrint;

#include "InsungCallPass.h"
//#include "RecPlayerDlg.h"
#include "GdipCheckBtn.h"

class COrderRecordRiderSortFunc
{ 
public:
	bool operator() (const pair<UINT, UINT> &pairRider1, const pair<UINT, UINT> &pairRider2)
	{
		return ComparePhone(pairRider1, pairRider2);
	}

	bool operator() (const pair<UINT, UINT> &pairRider1, const OrderRecord* r2)
	{
		return ComparePhone(pairRider1, make_pair(r2->nRiderCompany, r2->nRNo));
	}

	bool operator() (const OrderRecord* r1, const pair<UINT, UINT> &pairRider2)
	{
		return ComparePhone(make_pair(r1->nRiderCompany, r1->nRNo), pairRider2);
	}

	bool ComparePhone(const pair<UINT, UINT> &pairRider1, const pair<UINT, UINT> &pairRider2)
	{
		if(pairRider1.first > pairRider2.first) return true;
		else if(pairRider1.first < pairRider2.first) return false;

		if(pairRider1.second > pairRider2.second) return true;
		else if(pairRider1.second < pairRider2.second) return false;

		return false; 	
	}

	bool operator() (const OrderRecord* r1, const OrderRecord* r2)
	{
		if(r1->nRiderCompany > r2->nRiderCompany) return true;
		else if(r1->nRiderCompany < r2->nRiderCompany) return false;

		if(r1->nRNo > r2->nRNo) return true;
		else if(r1->nRNo < r2->nRNo) return false;

		if(r1->dtFinal > r2->dtFinal) return true;
		else if(r1->dtFinal < r2->dtFinal) return false;

		return false;
	}
};


class COrderRecordRiderTimeSortFunc
{ 
public:
	bool operator() (const OrderRecord* r1, const OrderRecord* r2)
	{
		if(r1->dtFinal > r2->dtFinal) return true;
		else if(r1->dtFinal < r2->dtFinal) return false;

		return false;
	}
};


template<typename tPair> 
struct second_t_ptr { 
	typename tPair::second_type* operator()(tPair& p) { return &p.second; } 
}; 

template<typename tMap>  
second_t_ptr<typename tMap::value_type> second_ptr(const tMap& m) { return second_t_ptr<typename tMap::value_type>(); }

template<class _Arg,
	class _Result>
struct unary_function
{	// base class for unary functions
	typedef _Arg argument_type;
	typedef _Result result_type;
};

//struct IsNotMyAllocatedOrder: public unary_function <OrderRecord*, bool>
//{
//	bool operator() (OrderRecord* pOrder) const
//	{
//		return !(pOrder->bMyOrder && 
//			(pOrder->nState == STATE_ALLOCATED ||
//			pOrder->nState == STATE_OK_ONLY_MAN ||
//			pOrder->nState == STATE_FINISH));
//	}
//};

typedef map<long, long> DISTINCT_SHARE_CODE_MAP;

class CXTPButtonUniCode : public CXTPButton
{
public:
	void SetMarkupText(LPCTSTR lpszText)
	{
		m_bEnableMarkup = TRUE;
		XTPMarkupReleaseContext(m_pMarkupContext);

		if (m_bEnableMarkup)
		{
			m_pMarkupContext = XTPMarkupCreateContext(m_hWnd, TRUE);
		}

		USES_CONVERSION;
		LPWSTR lpszwMarkup A2W(lpszText);

		if (m_pMarkupContext)
		{
			XTPMarkupReleaseElement(m_pUIElement);
			m_pUIElement = XTPMarkupParseText(m_pMarkupContext, lpszwMarkup);
		}

		//SetWindowText(lpszText);
	}
};

#define STATE_BTN_COUNT 10
// CRcpView 폼 뷰입니다.
class CRcpView : public CRcpViewBase 
{
	DECLARE_DYNCREATE(CRcpView)

public: 
	CRcpView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CRcpView();

public:
	enum { IDD = IDD_RCP_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	afx_msg LONG OnBranchClickEvent(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnRecvCid(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnReserveOrder(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnRefreshList(WPARAM wParam, LPARAM lParam);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

public:
	afx_msg LRESULT OnSaveRcpList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLoadRcpList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSaveCtiList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLoadCtiList(WPARAM wParam, LPARAM lParam);

	RECV_PHONE_LIST_MAP m_mapRecvPhoneList;
	CPtrArray m_paGroupPage;
	BOOL m_bGroup;
	UINT m_nCurBranch;
	BOOL m_bFirstBranchClick;
	BOOL m_bMove; // MAIN_RCP_DLG가 이동을 했는지 여부
	BOOL m_bFirstLocation; // MAIN_RCP_DLG가 처음 위치로 갈껀지
	BOOL m_bUseCardOkNumberAddColumn;
	CRcpSearchTruckTypeDlg *m_pRcpShTruckDlg;
	CRcpSearchCarTypeDlg *m_pRcpShCarDlg;
	CRcpSearchPayTypeDlg *m_pRcpShPayDlg;

	CRcpMultiStateChange *m_pStateChange;

	long m_nTodayIncome;
	CString m_strSort;
	CString m_strCID;
	UINT m_CurTab;
	MAP_RIDER m_RiderMap;

	CRcpDlg *m_pLastSelRcpDlg;
	CImageList m_listIcons;


	void RemoveSearch(BOOL bSearchFilter);
	void RefreshStateSecondSort();

	//CDelayOrderDlg2 *m_pDelayOrderPane;
	//CEmptyCarDlg1 *m_pEmptyCarPane;
	//CAllocatePaneDlg *m_pAllocatePane;


	BOOL m_bMultiSelectRefreshStop;

	//{{AFX(only use to print)
	CString m_strO1;
	CString m_strO2;
	CString m_strO3;
	CString m_strS1;
	CString m_strS2;
	CString m_strS3;
	CString m_strT1;
	CString m_strT2;
	CString m_strT3;
	CString m_strEtc;
	CString m_strPS;
	CString m_strPA;
	CString m_strPD;
	CString m_strPT;
	CString m_strPTotal;
	CString m_strRider;
	CString m_strS4;
	CString m_strT4;

	CString m_strW1;
	CString m_strW2;

	CString m_strW3;
	CString m_strO5;
	CString m_strO4;
	CString m_strS5;
	CString m_strT5;
	CString m_dt0;
	CString m_dt2;
	CString m_dt3;
	CString m_sFind;
	CString m_strTNo;
	//}}AFX(only use to print)

	//{{AFX
	CDateTimeCtrl m_dtODate;
	CStatic m_PeriodStatic;

	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;

	CButton m_btnNew;
	CButton m_btnNew2;
	CButton m_btnSearch;

	CDateButton m_DateBtn;
	CFlatComboBox m_RefreshCombo;

	//}}AFX

	CButton m_btnStateAll;
	CButton m_btnStateRcp;
	CButton m_btnStateWait;
	CButton m_btnStateReserved;
	CButton m_btnStateOnlyMan;
	CButton m_btnStateAlloc;
	CButton m_btnStatePickup;
	CButton m_btnStateFinish;
	CButton m_btnStateCancel;
	CButton m_btnStateEtc;

	int m_nHWidth[MAX_COLUMN];
	int m_nHOrder[MAX_COLUMN];
	UINT m_nColumnCount;

	CQSocket m_Socket;
	CRcpView *m_pRcpView;
	CString m_strCidNumber;
	BOOL m_bCreateRcpDlg;
	BOOL m_bTooltipNoUse;

	CString m_strInfoEditSearch;
	CString m_strInfoCheckSearch;
	CString m_strInfoCount;

	BOOL m_bAutoChangeMapForm;
	BOOL m_bAllCheck;

public:

	BOOL RefreshListCardOkNumber();
	void MakeBranchPage();
	void CheckBranch();
	void MakeDepositRate();
	void FirstRefresh();
	void DisplaySearchInfo();
	void ChangeSearchFilter();
	BOOL IsLeftTodayOrder();
	void InsertTodayOrder(OrderRecordList &order, OrderIndex &index, BOOL &bInsertTodayOrder);

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnBnClickedUseNewDlgChk();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedNewBtn();
	afx_msg void OnBnClickedAllocateBtn();
	afx_msg void OnBnClickedAllocateBtn2();
	afx_msg void OnBnClickedCancelABtn();
	afx_msg void OnBnClickedCancelOBtn();
	afx_msg void OnBnClickedCompleteBtn();
	afx_msg void OnBnClickedInquiryBtn();
	afx_msg void OnBnClickedPrintInvoiceBtn();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedEditBtn();
	afx_msg void OnChangeStateSite();
	afx_msg void OnChangeStateCarry();
	afx_msg void OnChangeWaitState();
	afx_msg void OnMoveOrderBranch();
	afx_msg void OnMakeNewRcpDlg();
	
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	void MakeContextMenuUpCharge(long nState, BCMenu *pRMenu);
	afx_msg void OnCbnSelchangeConditionCombo();
	afx_msg void OnViewExcel();
	afx_msg void OnPrinterSetting();
	afx_msg void OnReceiptPrint();
	afx_msg void OnReceiptTaxPrint();
	afx_msg void OnShowOrderLog();
	void DaeriShare(BOOL bShare);
	afx_msg void OnDaeriShare();
	afx_msg void OnDaeriShareRelease();
	afx_msg void OnReceiptTaxPrintView();
	afx_msg void OnReceiptGeneralPrintView();

	BOOL UpChange(long nCharge);
	afx_msg void OnUseUpCharge1();
	afx_msg void OnUseUpCharge2();
	afx_msg void OnUseUpCharge3();
	afx_msg void OnUseUpChargeRelease();

	afx_msg LONG OnRiderAllocate(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnRiderAllocate2(WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedPrintOrderBtn();
	afx_msg void OnBnClickedFinishBtn();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCbnSelchangeConditionKCombo();
	afx_msg void OnCbnSelchangeRefreshCombo();
	afx_msg void OnNewRiderList();
	afx_msg void OnBnClickedShowNoticeBtn();
	afx_msg void OnMoveOrder();
	afx_msg void OnBnClickedShareOrder();
	afx_msg void OnBnClickedCopyOrder();
	afx_msg void OnBnClickedAddOrder();
	afx_msg void OnBnClickedTransInfo();			
	afx_msg void OnReportItemSelChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportSortOrderChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportColumnChangeChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportColumnWidthChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnBnClickedStateAllBtn();
	afx_msg void OnBnClickedStateRcpBtn();
	afx_msg void OnBnClickedStateWaitBtn();
	afx_msg void OnBnClickedStateOnlyManBtn();
	afx_msg void OnBnClickedStateReservedBtn();
	afx_msg void OnBnClickedStateAllocBtn();
	afx_msg void OnBnClickedStatePickupBtn();
	afx_msg void OnBnClickedStateFinishBtn();
	afx_msg void OnBnClickedStateCancelBtn();
	afx_msg void OnBnClickedStateEtcBtn();
	afx_msg void NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result);
	afx_msg void OnBnClickedPickupBtn();
	afx_msg void OnBnClickedInitSearchBtn();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnCbnSelchangeFontCombo();
	afx_msg void OnBnClickedStateStateReservedBtn();
	afx_msg void OnBnClickedSetInitSearchBtn();
	afx_msg void OnEnChangeSearchStartEdit();
	afx_msg void OnEnChangeSearchDestEdit();
	afx_msg void OnEnChangeSearchRiderEdit();
	afx_msg void OnEnChangeSearchCustomerEdit();
	afx_msg void OnMenuSendSms();
	afx_msg void OnMenuAllocateSendSms();
	afx_msg void OnOtherAllocate();
	afx_msg void OnBnClickedShowCrossCallCheck();
	afx_msg void OnShowRiderPosBtn();
	afx_msg void OnNMSetfocusDatefrom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeSearchEtcEdit();
	afx_msg void OnBnClickedDeleteSearchTextBtn();
	afx_msg void OnBnClickedShareSearchBtn();
	afx_msg void OnBnClickedMyCallCheck();
	afx_msg void OnBnClickedHideCrossCallCheck();
	afx_msg void OnBnClickedScheduleOrderCheck();
	afx_msg void OnBnClickedWebOrderCheck();
	afx_msg void OnBnClickedWebOrderBtn();
	afx_msg void OnBnClickedRefreshIcBtn();
	afx_msg void OnBnClickedInterorderCheck();
	afx_msg void OnBnClickedSearchMyRiderCheck();
	afx_msg void OnEnChangeSearchTnoEdit();
	afx_msg void OnEnChangeSearchDepartEdit();
	afx_msg void OnEnChangeSearchManagerEdit();
	afx_msg void OnEnChangeSearchCustomerIDEdit();
	afx_msg void OnEnChangeSearchGroupEdit();
	afx_msg void OnEnChangeSearchGroupDepartEdit();
	afx_msg void OnEnChangeSearchRiderNoEdit();
	afx_msg void OnEnChangeSearchWNoEdit();
	afx_msg void OnEnChangeSearchStartRegionEdit();
	afx_msg void OnSetDepositZero();
	afx_msg void OnCallPass();
	afx_msg void OnBnClickedGetAllocCheck();
	afx_msg void OnBnClickedGetMsgCheck();
	afx_msg void OnEnChangeShowRiderInfoEdit();
	afx_msg void OnDtnDatetimechangeDatefrom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDateto(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOpenSearchBtn();
	afx_msg void OnBnClickedClearAllCheckBtn();
	afx_msg void OnBnClickedConnectMessengerForLogiBtn();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnEnChangeSearchCidEdit();
	afx_msg void OnBnClickedNewRcpDlgBtn();
	afx_msg void OnBnClickedDeleteEditBtn(); 
	afx_msg void OnBnClickedCargoNewBtn();
	afx_msg void OnBnClickedShowMyCallCountBtn();
	//}}AFX

public:

	int m_nKind;
	int m_kPay;
	BOOL m_nKDel;
	int m_nKDoc;
	long lTemp;
	BOOL m_bR;

	BOOL m_bAppRunFirst;
	CFont m_ListFont;
	//CImageList m_imgList;
	int m_nLastSelItemNo;
	int m_nLastSelItemNoCondition;
	int m_nCurSel;
	int m_nCurCol;
	BOOL m_bColAsc;
	CString m_sAllocateRNo;

	enum { ORDER_LIST = 0, RIDER_LIST = 1};

	POINT		m_ptDrag;
	BOOL		m_bDragMode;	
	CWnd* m_pDragWnd;
	CImageList* m_pDragImage;
	HCURSOR m_hcArrow;
	HCURSOR m_hcNo;
	HCURSOR m_hcMoveHold;
	HCURSOR m_hcMiddle;

	CString m_strSortField;
	COleDateTime m_dtLastRefresh;
	CString m_strFilter;
	BOOL m_bPartRefresh;
	BOOL m_bPrePartRefresh;
	CString m_strPreCondition;
	long m_nLastSearchCNo;
	BOOL m_bCopyDlg;

	long m_nDiscountSec;
	COleDateTime m_dtLastForLimit;
	BOOL m_bRefreshOK;
	BOOL m_bRefreshWithCID;

	CVirtualRecord *m_vrOrder;
	CVirtualRecord *m_vrShareOrder;
	CVirtualRecord *m_vrPreDate;
	CVirtualRecord *m_vrCur;
	OrderRecordList m_mapOtherOrder;

	BOOL m_bLoadReportState;
	CString m_strPreRecvRiderCID;
	BOOL m_bFirstRefresh;
	long m_nReserveShowCount;
	BOOL m_bStateSecondSort;
	BOOL m_bGetCustomerMemo;
	CWebOrderDlg *m_pWebOrderDlg;

	BOOL m_bBigUnderForm;
	CButton m_chkPreOrder;
	CString m_sYear;
	HACCEL  m_hAccel;
	
	CReceiptPrint *m_pReceiptPrint;

	BOOL m_bIsSaveState;
	BOOL m_bSaveState[STATE_BTN_COUNT];

	BOOL m_bIgnoreCheckState;
	BOOL m_bRemoveSearch;
	BOOL m_bAddTacksongCharge;
	BOOL m_bAddTacksongDrivingCharge;
	BOOL m_bSearchWithNoWName;

public:
	BOOL m_bShareOrderRefresh;

	CMarkupStatic m_stcPayType;
	CMarkupStatic m_stcCarType;
	CMarkupStatic m_stcDisplay2;
	CMyStatic m_stc1;
	CButton m_btnWebOrder;
	CButton m_btnRefreshIC;

	CXTPButton m_chkShMyRider;
	CXTPButton m_chkMyCall;
	CXTPButton m_chkHideCrossCall;
	CXTPButton m_chkShowCrossCall;
	CXTPButton m_chkScheduleOrder;
	CXTPButton m_chkInterOrder;
	CXTPButton m_chkShWebOrder;

	CFlatEdit2 m_edtShowRiderInfo;
	CFlatEdit2 m_edtShTNo;
	CFlatEdit2 m_edtShCustomer;
	CFlatEdit2 m_edtShDepart;
	CFlatEdit2 m_edtShManager;
	CFlatEdit2 m_edtShCustomerID;
	CFlatEdit2 m_edtShGroup;
	CFlatEdit2 m_edtShGroupDepart;
	CFlatEdit2 m_edtShCID;
	CFlatEdit2 m_edtShWNo;
	CFlatEdit2 m_edtShEtc;
	CFlatEdit2 m_edtShStart;
	CFlatEdit2 m_edtShDest;
	CFlatEdit2 m_edtShRider;
	CFlatEdit2 m_edtShRiderNo;
	CFlatEdit2 m_edtShRegionStart;
	CFlatEdit2 m_edtShRegionDest;
	CFlatEdit2 m_edtShCustomerMemo;
	CFlatEdit2 m_edtShCustomerInnerMemo;

	CString m_strShPreCustomerID;
	CString m_strShPreCustomerMemo;

	CString m_strShTNo;
	CString m_strShCustomer;
	CString m_strShDepart;
	CString m_strShManager;
	CString m_strShCustomerID;
	CString m_strShGroup;
	CString m_strShGroupDepart;
	CString m_strShCID;
	CString m_strShWNo;
	CString m_strShEtc;
	CString m_strShStart;
	CString m_strShDest;
	CString m_strShRider;
	CString m_strShRiderNo;
	CString m_strShRegionStart;
	CString m_strShRegionDest;
	CString m_strShCustomerMemo;
	CString m_strShCustomerInnerMemo;
	CString m_strShowRiderInfo;

	BOOL m_bSearchMode;

	CButton m_chkGetAlloc;
	CButton m_chkGetMsg;
	CButton m_btnInitSearch;
	CButton m_btnShareSearch;

	CButton m_btnClearAllCheck;
	CButton m_btnDeleteSearchText;

	CMarkupStatic m_stcDisplay;

	int m_nStateAll;
	int m_nStateWait;
	int m_nStateReserved;
	int m_nStateRcp;
	int m_nStateAlloc;
	int m_nStateOnlyMan;
	int m_nStateCancelWait;
	int m_nStateFinish;
	int m_nStateCancel;
	int m_nStateEtc;
	int m_nStatePickup;
	COleDateTime m_dtLastGetCustomerInfo;
	COleDateTime m_dtLastRemove;
	COleDateTime m_dt1;
	DISTINCT_SHARE_CODE_MAP m_mapDistinctShareCode;
	long m_nOnceSelectedTNo;
	CInsungCallPass m_cp;
	CRecPlayerDlg m_PlayerDlg;

	CButton m_chkUseNewDlg;
	CGdipCheckBtn m_btnAutoScroll;
	BOOL m_bAutoScroll;


protected:

	void LoadListInfo();
	void SaveListInfo();
	void InitListItem();
	void SetAutoScroll(BOOL bAutoScroll, BOOL bChangeImage = TRUE);

	void ShowRefreshSec(int nSec, BOOL bStopState = FALSE, BOOL bRefresh = FALSE);
public:
	int GetItemState(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->nState;
	}

	BOOL GetItemShare(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->bShareOrder;
	}

	BOOL GetItemIsParentOrder(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->bParentOrder;
	}

	int GetItemDeposit(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->nDeposit;
	}

	int GetItemCharge(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->nCharge;
	}

	int GetItemPayType(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->nPayType;
	}

	int GetItemRunType(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->nRunType;
	}

	int GetItemWayType(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->nWayType;
	}

	int GetItemCarType(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->nCarType;
	}

	long GetItemTNo(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->nTNo;
	}

	BOOL GetItemAutoWait(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->bAutoWait;
	}

	long GetItemTNoSet(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->nTNoSet;
	}
	long GetItemConsignTNo(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->nConsignTNo;
	}
	CString GetItemConsignDestSido(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->sConsignDestSido;
	}
	long GetItemConsignWayID(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->nConsignWayID;
	}
	
	CString GetItemPhone(int nItem)
	{ return m_vrCur->GetOrderRecord(nItem)->strOPhone.c_str();}

	CString GetItemCName(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->strCName.c_str();
	}

	COleDateTime GetItemDtRcp(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->dtRcp;
	}

	/*
	long GetItemChargeLogi(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->nChargeLogi;
	}
	*/

	long GetItemChargeCompany(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->nChargeCompany;
	}

	BOOL GetItemCross(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->bCross;
	}

	BOOL GetItemSecondCross(int nItem) {
		long nCompany =  m_vrCur->GetOrderRecord(nItem)->nCompany;
		return GetSecondCrossState(nCompany);
	}
	BOOL GetItemTodayOrder(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->bTodayOrder;
	}
	long GetItemCNo(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->nCNo;
	}
	
	int GetItemRowFromTNo(long nTNo)
	{
		return m_vrCur->GetItemRowFromTNo(nTNo);
	}

	COleDateTime GetItemCNameDtRcp(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->dtRcp;
	}

	CString GetItemStartDetail(int nItem)
	{ return m_vrCur->GetOrderRecord(nItem)->strSDetail.c_str();}

	CString GetItemDestDetail(int nItem)
	{ return m_vrCur->GetOrderRecord(nItem)->strDDetail.c_str();}

	CString GetItemStart(int nItem)
	{ return m_vrCur->GetOrderRecord(nItem)->strStart.c_str();}

	CString GetItemDest(int nItem)
	{ return m_vrCur->GetOrderRecord(nItem)->strDest.c_str();}

	BOOL GetSecondCrossState(int nCompany) {
		return !m_ci.IsChildCompany(nCompany);
		//return m_ccm[nCompany] < 1; || 
		//(!m_pBi->bIntegrated && m_pBi->nCompanyCode != nCompany);
	}

	inline long GetItemCreditCardType(int nItem)
	{ return m_vrCur->GetOrderRecord(nItem)->nCreditCardType; }

//protected:
	int GetItemCompany(int nItem) 
	{ return m_vrCur->GetOrderRecord(nItem)->nCompany; }

	int GetItemRNo(int nItem) 
	{ return m_vrCur->GetOrderRecord(nItem)->nRNo; }

	int GetItemRiderCompany(int nItem) 
	{ return m_vrCur->GetOrderRecord(nItem)->nRiderCompany; }

	long GetItemWNo(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->nWNo;
	}

	long GetItemWCompany(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->nWCompany;
	}

	CString GetItemWName(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->strWName.c_str();
	}

	CString GetItemRName(int nItem) {
		return m_vrCur->GetOrderRecord(nItem)->strRName.c_str();
	}

	long GetItemRiderAllocate(int nItem){
		return m_vrCur->GetOrderRecord(nItem)->nRiderAllocate;
	}

public:
	BOOL m_bMoveControl;
	BOOL m_bChangeCursor;
	CVirtualRecord * GetCurrentOrder() {return m_vrOrder;};

	void SetItemSelectFromTNo(long nTNo)
	{

		int nRow = m_vrCur->GetItemRowFromTNo(nTNo);
		CXTPGridRows *pRows = m_xList.GetRows();
		CXTPGridRow *pRow = pRows->GetAt(min(nRow + 15, pRows->GetCount() - 1));
		m_xList.EnsureVisible(pRow);
		pRow = pRows->GetAt(nRow);
		m_xList.GetSelectedRows()->Select(pRow);
	}

	long GetItemSelectFromTNo(long nTNo)
	{
		int nRow = m_vrCur->GetItemRowFromTNo(nTNo);
		return nRow;
	}
		
	CImageList *GetImageList() { return &m_listIcons; }

	void SetRefreshStop();
	void SetRefreshStart();
	CString GetPaddingString(CString strData, UINT nLen);
	void GetRiderOrder(CString& strOrder, long nCompany, long nRNo);
	void GetRiderOrder(CWnd *pWnd, long nCompany, long nRNo);

	void AddRcpNotice(long nTNo, COleDateTime dt, CString strUser, CString strNotice, BOOL bReqeustEditOrder = FALSE);
	void SimpleSearch();
	void EditOrder(BOOL bAddCall = FALSE);

	void InitControl(void);
	void InitOrderList(void);
	void InitOrderListRider(void);
	void OnCID(void);

	void AutoList(CString strSql);
	BOOL AppRunFirst()	{
		if(m_bAppRunFirst) {
			m_bAppRunFirst = FALSE;
			return TRUE; 
		}
		return FALSE;
	}      

	CString GetRiderDeposit(long nChargeDriving, long nRiderDeposit);
	long RefreshList(CString strRecvCID = "", CString strCallBranch = "", CBranchInfo *pBI = NULL, BOOL bShareOrder = FALSE, BOOL bScrollTopOnce = TRUE, long nRefreshRiderCompany = ZERO, long nRefreshRNo = ZERO, BOOL bFromOrderChange = FALSE);
	void RefreshFilterOnly(BOOL bStateCheck = FALSE);

	long CheckFilter(BOOL *bUseFilter, OrderRecordList &order, OrderIndex &index, OrderIndex &filter);
	long CheckCustomerFilter(CString &strData, BOOL *bUseFilter, 
		OrderRecordList &order, OrderIndex &index, OrderIndex &filter);
	long CheckRiderFilter(long nRCompany, long nRNo, BOOL *bUseFilter, OrderRecordList &order, 
		OrderIndex &index, OrderIndex &filter);

	//이전오더 조회시 동기반정보 매칭검색이 DB서버에서 부하문제로 힘들어, 이부분만 프로그램적으로 처리한다.
	long CheckFilterPredateDedicated(BOOL *bUseFilter, OrderRecordList &order, OrderIndex &index, OrderIndex &filter);
	//오더조회후에 조건비교시 필요한 데이터를 미리 만들어 놓는다.

	void ShowCustomerInfoToMainList();
	void RemoveNoneCrossOrder();
	void MakeDistinctShareCodeMap();

	BOOL CheckCrossOrder();
	BOOL IsTodaySearch();
	void UpdateOrderCount();
	void ShowCustomerInfoInList(BOOL bUseFilter, CString strRecvCID);
	void ChangeBranch(CBranchInfo *pBi, BOOL bNotRefresh = FALSE);

	BOOL MakeCall(int nCompany, CString strPhone, long nType = CALL_TO_CUSTOMER);
	long GetRiderOrder(CListCtrl &list, long nCompany, long nRNo);
	void GetReceptCount(long &nCallCount, long &nReceiveCount, long &nRcpCount, long &nAllocCount, long &nCompleteCount, long &nCancelCount, long &nAllCount);
	void EditOrderFromTNo(long nTNo);
	void CancelOrderFromTNo(long nTNo);
	void RcpStateFromTNo(long nTNo);
	void InitBranchInfo();
	//void SetLastSelItemNo(long nLastSelItemNo){m_nLastSelItemNo = nLastSelItemNo;};
	//long GetLastSelItemNo(){return m_nLastSelItemNo;};
	void AllRefresh(BOOL bFromOrderChange = FALSE);
	CString GetSearchText(CString sTitle, CString sEtc);
	CString CheckOXCheckBox(long nState, CString sTitle);

	CVirtualRecord *GetTodayOrder() { return m_vrOrder;}

	void GetCompanyInfoToolTip(CMakeHtmlTable *pTable, long nCompany);
	BOOL GetRiderInfoToolTip(CMakeHtmlTable *pTable, long nCompany, long nRNo, long nTNo, BOOL bTodayOrder);
	BOOL GetRiderOrderHtmlTable(CMakeHtmlTable *pTable, long nCompany, long nRNo);
	inline void GetRiderOrderHtmlTableSubRoutine(OrderRecord &order, CMakeHtmlTable *pTable,
		long nCompany, long nRNo, long &nCount, long nSum);


	BOOL GetOrderInfoHtmlTable(CMakeHtmlTable *pTable, long nTNo);
	void MoveOrder(CBranchInfo *pBi, BOOL bCopy);
	BOOL MakeTransInfo(CMakeHtmlTable *table, long nIndex);

	void SendSms(long nCompany, CString sPhone, bool bAllocate = false);
	void OnCloseWebOrder();
	void InitSearch(BOOL bNoCondition = FALSE);
	void ShowRcpPopupControl(CString strText, CString strWriter, COleDateTime dtTime);
	BOOL GetBigUnderFormToggle() { m_bBigUnderForm = !m_bBigUnderForm; return m_bBigUnderForm;}

	void SaveCallingLog(CString sPhone, long nType);
	void MakeContextMenu(BOOL bMenuFromRcpDlg = FALSE, long nTNo = -1);
	void CopyOrder(long nSelItem, long nState);

	long m_nShareRcpCount;
	long m_nShareAllocateCount;
	long m_nShareCompleteCount;
	long m_nShareCancelCount;
	long m_nShareEtcCount;
	long m_nShareAllCount;

	long m_nRefreshType;
	void UpdateShareCallCount();
	COleDateTime m_dtLastRefreshByShareCall;
	CRect GetAllocatePaneRect();
	void SaveAllocatePaneLocation();

	OrderRecordList &GetOtherOrder() 
	{ return m_mapOtherOrder; }	
	void OnCurOrderState();
		
	long m_nShareBalance;
	long m_nSmsBalance;

	void CheckOfficeAllocateOnly(long nType, BOOL &bRiderOkOnlyMan, BOOL &bOfficeOkOnlyMan);
	void OrderClickAutoMoveMap(long nPosX, long nPosY, long nRCompany, long nRNo, BOOL bNearRider = FALSE);

	BOOL HasSearchCondition();
	void SetLastSelItemNo(long nItem);
	long GetLastSelItemNo(); 
	CString GetColorTo0x(long nColor);
	
	void ShowShTruckTypeDlg();
	void ShowShCarTypeDlg();
	void ShowShPayTypeDlg();
	void MakeRcpShTruckDlg();
	void MakeRcpShCarDlg();
	void MakeRcpShPayDlg();

	void SaveStateRegForCheckFilter();
	void LoadStateRegForCheckFilter();

	long m_nShMyRider;
	long m_nShMyCall;
	long m_nShHideCrossCall;
	long m_nShShowCrossCall;
	long m_nShScheduleOrder;
	long m_nShInterOrder;
	int m_nSelectedRegionStartDongID[MAX_REGION_SELECT_COUNT];
	int m_nSelectedRegionDestDongID[MAX_REGION_SELECT_COUNT];
	long m_nRefreshTNoForStateChange;

	BOOL CheckFilterSubState(OrderRecord *order, BOOL &bHideCompleteOrder,  
		BOOL &bAll, BOOL &bRcp, BOOL &bWait, BOOL &bReserved, BOOL &bOnlyMan, BOOL &bAlloc, 
		BOOL &bFinish, BOOL &bCancel, BOOL &bPickup, BOOL &bEtc);
	BOOL CheckFilterSubEditBox(OrderRecord *order, CString strCNo, CString strSearchMemoCNo); 
	BOOL CheckFilterSubCheckBox(OrderRecord *order);
	BOOL IsCheckEditBox();
	BOOL IsCheckCheckBox();
	void SetAllocCheck(BOOL bMsgBox = TRUE);
	void SetMsgCheck(BOOL bMsgBox = TRUE);
	void ShowSearchMode(BOOL bSearchMode);
	void CheckCarTypeCheckBox();
	void CheckPayTypeCheckBox();
	void ClickSeachCheckBox(UINT nFlag, long &nState, CString sTitle);
	CString GetPayTypeDisplay(BOOL bAllDisplay);
	CString GetCarTypeDisplay(BOOL bAllDisplay);
	void OpenRegionDlg(BOOL bStart);
	void SetRegionText();
	CString GetSearchCustomerID();
	CString GetSearchCustomerMemo();
	CString GetSearchGroupGNo();
	void FindCustomerFromPhone(CString strPhone, CString strDID, BOOL bPopupLastOrder = FALSE);
	void OnHyperlinkClick(CXTPMarkupObject* pSender, CXTPMarkupRoutedEventArgs* pArgs);
	void InsertOrderToTree(long nParTNo);
	BOOL InsertOrderToTreeSub(long nSrcTNo, long nDrcTNo);
	void InsertOrderToTreeFree();
	void ShowOrderLogDetailDlgFromTNo(long nTNo, long nState, BOOL bCrossOrder, BOOL bFullSearch);
	void SearchCondition(BOOL bSave);
	long SelectRowFromTNo(long nTNo);
	void AlllocateFromTNo(long nTNo, long nCompany = ZERO, long nRNo = ZERO);
	void* GetTodayOrderRecord(long nTNo);
	void HideSearchDlg();
	void TaxPrint(BOOL bView = FALSE);
	CString GetShareCallCount();
	CString GetShareCallBalance();
	void SearchRiderInfo();
	CMyReportControl* GetReportControl(){return &m_xList;};
	void RefreshMapForm(OrderRecord *pOrder, BOOL bCIDPopup = FALSE);
	OrderRecord* GetLastTimeOrderInVisibleRows();
	CRcpMultiStateChange *GetStateChange() {return m_pStateChange;};
	void InitMessengerInfo();
	void ChangeOrderRider(long nTNo, long nState, long nRiderCompany, long nRNo);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnEnChangeSearchInnerMemoEdit();
	afx_msg void OnEnChangeSearchMemoEdit();
	void OnRecPlayer();
	void OnRecDownload();
	void PlayRecordFile(CString strDate, CString strFile);
	afx_msg void OnBnClickedAutoScrollBtn();
	void SaveReportEnsureVisible(vector<UINT> &vecTNo, BOOL bFromOrderChange);
	void LoadReportEnsureVisible(vector<UINT> &vecTNo, int &nSortCol, BOOL &bAsc, BOOL bFromOrderChange);
	BOOL IsNeedAutoScroll(int nSortCol);
	void OnJinsangCallingDeny();

	BOOL m_bReportReadyToPopulate;

	afx_msg void OnReportVScroll(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnDelayNotice();
	afx_msg void OnDelayNoticeRelesae();
	afx_msg void OnAutoWait();

	void ChangeDelayNoticeState(BOOL bSetting);
	long GetRiderAndInsertOperatorLog(long nCallCompany, CString strCID, long &nRiderCompany, long &nRNo);
	void SearchAllocatedRiderFromOrder(CMkRecordset &rs, long &nRiderCompany, long &nRNo);
};


