// AllocatePaneDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AllocatePaneDlg.h"
#include "RcpView.h"
#include "MkLock.h"
#include "TestDlg.h"
#include "VirtualRecord.h"
#include "POIDataNew.h"
#include "RcpMultiStateChange.h"
//#include "MainFrm.h"


IMPLEMENT_DYNCREATE(CAllocatePaneDlg, CMyFormView)


CAllocatePaneDlg::CAllocatePaneDlg()
	: CMyFormView(CAllocatePaneDlg::IDD)
{
	LU->SetAllocatePane(this);
	m_nCount = 0;
	m_nTNo = -1;
	m_bAutoHide = FALSE;
	m_bShareOrder = FALSE;
	m_nShareCompany = 0;
	m_nRiderCompany = 0;
	m_nRNo = 0;
	m_bTodayOrder = FALSE;
	m_nSelectedRNo = 0;
	m_nSelectedRCompany = -1;
}

CAllocatePaneDlg::~CAllocatePaneDlg()
{
}

#ifdef _DEBUG
void CAllocatePaneDlg::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CAllocatePaneDlg::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG

void CAllocatePaneDlg::DoDataExchange(CDataExchange* pDX)
{

	CMyFormView::DoDataExchange(pDX);

	//"지원되지 않는 작업을 시도하였습니다." 에러인 경우에 아래 주석을 풀고 로그를 보면 위치를 정확히 알수 있음
	//#define DDX_Control(x, y, z) { g_bana_log->Print("DDX_Control: FILE = %s, LINE = %d\n", TEXT(__FILE__), TEXT(__LINE__));DDX_Control(x, y, z);}


	DDX_Control(pDX, IDC_CUSTOM1, m_List);
	DDX_Control(pDX, IDC_CUSTOM2, m_nearReport);

	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);

	DDX_Control(pDX, IDC_ODONG_EDIT, m_edtODONG);
	DDX_Control(pDX, IDC_ONAME_EDIT, m_edtOName);
	DDX_Control(pDX, IDC_OTEL_EDIT, m_edtOTel);
	DDX_Control(pDX, IDC_OETC_EDIT, m_edtOEtc);

	DDX_Control(pDX, IDC_SDONG_EDIT, m_edtSDONG);
	DDX_Control(pDX, IDC_SNAME_EDIT, m_edtSName);
	DDX_Control(pDX, IDC_STEL_EDIT, m_edtSTel);
	DDX_Control(pDX, IDC_SETC_EDIT, m_edtSEtc);

	DDX_Control(pDX, IDC_DDONG_EDIT, m_edtDDONG);
	DDX_Control(pDX, IDC_DNAME_EDIT, m_edtDName);
	DDX_Control(pDX, IDC_DTEL_EDIT, m_edtDTel);
	DDX_Control(pDX, IDC_DETC_EDIT, m_edtDEtc);

	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);

	DDX_Control(pDX, IDC_EDIT_TNO, m_edtTNo);
	DDX_Control(pDX, IDC_STATE_PICTURE, m_picState);
	DDX_Control(pDX, IDC_STATE_EDIT2, m_edtState);
	DDX_Control(pDX, IDC_EDIT_WNO, m_edtWNo);
	DDX_Control(pDX, IDC_EDIT_TIME, m_edtTime);

	DDX_Control(pDX, IDC_CHARGE_INFO_EDIT, m_edtChargeInfo);
	DDX_Control(pDX, IDC_CHARGESUM_EDIT, m_edtChargeSum);
	DDX_Control(pDX, IDC_DEPOSIT_EDIT, m_edtDeposit);
	DDX_Control(pDX, IDC_OMEMO_EDIT, m_edtOMemo);

	DDX_Control(pDX, IDC_ODETAIL_EDIT, m_edtODetail);
	DDX_Control(pDX, IDC_SDETAIL_EDIT, m_edtSDetail);
	DDX_Control(pDX, IDC_DDETAIL_EDIT, m_edtDDetail);

	DDX_Control(pDX, IDC_OSTATIC, m_stcOrder);
	DDX_Control(pDX, IDC_SSTATIC, m_stcStart);
	DDX_Control(pDX, IDC_DSTATIC, m_stcDest);
	DDX_Control(pDX, IDC_ETC_STATIC, m_stcEtc);
	DDX_Control(pDX, IDC_OPTION_STATIC, m_stcOption);
	DDX_Control(pDX, IDC_CHARGE_STATIC, m_stcCharge);
	DDX_Control(pDX, IDC_DEPOSIT_STATIC, m_stcDeposit);

	DDX_Control(pDX, IDC_NEAR_ALLOCATE_CHECK, m_chkNearAllocate);
	DDX_Control(pDX, IDC_START_COMBO, m_cmbStartKm);
	DDX_Control(pDX, IDC_DEST_COMBO, m_cmbDestKm);
	DDX_Control(pDX, IDC_RIDER_STATIC, m_RiderStatic);

	DDX_Control(pDX, IDC_OPTION_EDIT, m_edtOption);
	DDX_Control(pDX, IDC_SEARCH_STATIC, m_stcSearch);
	DDX_Control(pDX, IDC_ORDER_LIST, m_lstOrder);

	DDX_Control(pDX, IDC_NEAR_ORDER_STATIC, m_stcNearOrder);
	DDX_Control(pDX, IDC_NEAR_START_STATIC, m_stcNearStart);
	DDX_Control(pDX, IDC_NEAR_DEST_STATIC2, m_stcNearDest);
	DDX_Control(pDX, IDC_SHOW_COMPLETE_ORDER_CHECK, m_chkShowCompleteOrder);
}


BEGIN_MESSAGE_MAP(CAllocatePaneDlg, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM1, OnReportItemClick)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeXtplistctrlEdit)
	ON_EN_SETFOCUS(IDC_SEARCH_EDIT, OnEnSetfocusSearchEdit)
	ON_EN_KILLFOCUS(IDC_SEARCH_EDIT, OnEnKillfocusSearchEdit)
	ON_MESSAGE(WM_ALLOCATE, OnAllocate)
	ON_MESSAGE(WM_READY_ALLOCATE, OnReadyAllocate)	
	ON_BN_CLICKED(IDC_ALLOCATE_BTN, OnBnClickedAllocateBtn)	
	ON_BN_CLICKED(IDC_NEARORDER_BTN, OnBnClickedNearorderBtn)	
	ON_WM_PAINT()
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_NEAR_ALLOCATE_CHECK, OnBnClickedNearAllocateCheck)
	ON_BN_CLICKED(IDC_RIGHT_DOCKING_BTN, OnBnClickedRightDockingBtn)
	ON_BN_CLICKED(IDC_LEFT_DOCKING_BTN, OnBnClickedLeftDockingBtn)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_SHOW_COMPLETE_ORDER_CHECK, OnBnClickedShowCompleteOrderCheck)
END_MESSAGE_MAP()


// CAllocatePaneDlg 메시지 처리기입니다.



void CAllocatePaneDlg::OnInitialUpdate()
{
	if(m_bInitialUpdateCalled) return;
	
	CMyFormView::OnInitialUpdate();

	//SetResize(IDC_CUSTOM2, sizingBottom);

	m_List.SetExternalControl(NULL,
		GetDlgItem(IDC_SEARCH_EDIT), NULL);			//SetExternalControl함수의 순서중요함

	m_List.GetPaintManager()->m_strNoItems = "";
	m_List.InsertColumn(0,"사번", LVCFMT_CENTER, 40);
	m_List.InsertColumn(1,"이름", LVCFMT_LEFT, 60);
	m_List.InsertColumn(2,"차량", LVCFMT_LEFT, 40);
	m_List.InsertColumn(3,"무전ID", LVCFMT_LEFT, 40);
	m_List.InsertSearchAllColumn(0);
	m_List.InsertSearchAllColumn(1);


	CBitmap bitmap;
	CImageList imageList;
	bitmap.LoadBitmap(IDB_LIST);
	imageList.Create(16,18,ILC_COLOR24 | ILC_MASK,1,1); 
	imageList.Add(&bitmap,RGB(0, 255, 255));
	m_lstOrder.SetImageList(&imageList,LVSIL_SMALL);
	m_lstOrder.GetPaintManager()->m_strNoItems = "";
	m_lstOrder.InsertColumn(0, "배차/완료",LVCFMT_LEFT, 60);
	m_lstOrder.InsertColumn(1, "의뢰인",LVCFMT_LEFT, 70);
	m_lstOrder.InsertColumn(2, "출발지",LVCFMT_LEFT, 70);
	m_lstOrder.InsertColumn(3, "도착지",LVCFMT_LEFT, 70);
	m_lstOrder.InsertColumn(4, "요금",LVCFMT_RIGHT, 50);


	m_nearReport.InsertColumn(0,"배차",DT_CENTER, 35,TRUE);
	m_nearReport.InsertColumn(1,"고객명",DT_LEFT, 60);
	m_nearReport.InsertColumn(2,"지연",DT_LEFT, 30);
	m_nearReport.InsertColumn(3,"출발지",DT_LEFT, 70);
	m_nearReport.InsertColumn(4,"도착지",DT_LEFT, 60);
	m_nearReport.InsertColumn(5,"기타",DT_LEFT, 50);
	
	m_nearReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_nearReport.GetReportHeader()->AllowColumnResize(FALSE);
	m_nearReport.GetReportHeader()->AllowColumnSort(TRUE);
	m_nearReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_nearReport.GetPaintManager()->m_strNoItems = "";
	m_nearReport.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_nearReport.SetGridStyle(TRUE, xtpGridSolid);
	m_nearReport.SetGridColor(RGB(212, 208, 200));
	m_nearReport.SetImageList(&imageList);


	//by mksong (2010-09-21 오후 7:51)
	//MAP복사하면 속도 느려짐, 수정필요함
	m_mapRider = LU->GetRcpView()->GetCurrentOrder()->m_mapRider;


	m_edtODONG.SetUserOption(RGB(0, 0, 0), RGB(255, 200, 255), "PDA표시동");
	m_edtODONG.SetMyFont("맑은 고딕", 17, FW_BOLD);
	m_edtOName.SetUserOption(RGB(0, 0, 255), RGB(200, 255, 155), "고객명/지명");
	m_edtOName.SetMyFont("맑은 고딕", 17, FW_BOLD);
	m_edtOTel.SetUserOption(RGB(0, 0, 255), RGB(200, 255, 155), "전화/휴대폰");
	m_edtOTel.SetMyFont("맑은 고딕", 17, FW_BOLD);
	m_edtOEtc.SetFontSize(13);
	m_edtOEtc.SetTitle("부서/담당");
	m_edtOMemo.SetFontSize(13);
	m_edtOMemo.SetTitle("고객메모");
	m_edtODetail.SetFontSize(13);
	m_edtODetail.SetTitle("상세위치");

	m_edtSDONG.SetUserOption(RGB(0, 0, 0), RGB(255, 200, 255), "PDA표시동");
	m_edtSDONG.SetMyFont("맑은 고딕", 17, FW_BOLD);
	m_edtSName.SetUserOption(RGB(0, 0, 255), RGB(200, 255, 155), "고객명/지명");
	m_edtSName.SetMyFont("맑은 고딕", 17, FW_BOLD);
	m_edtSTel.SetUserOption(RGB(0, 0, 255), RGB(200, 255, 155), "전화/휴대폰");
	m_edtSTel.SetMyFont("맑은 고딕", 17, FW_BOLD);
	m_edtSEtc.SetFontSize(13);
	m_edtSEtc.SetTitle("부서/담당");
	m_edtSDetail.SetFontSize(13);
	m_edtSDetail.SetTitle("상세위치");

	m_edtDDONG.SetUserOption(RGB(0, 0, 0), RGB(255, 200, 255), "PDA표시동");
	m_edtDDONG.SetMyFont("맑은 고딕", 17, FW_BOLD);
	m_edtDName.SetUserOption(RGB(0, 0, 255), RGB(200, 255, 155), "고객명/지명");
	m_edtDName.SetMyFont("맑은 고딕", 17, FW_BOLD);
	m_edtDTel.SetUserOption(RGB(0, 0, 255), RGB(200, 255, 155), "전화/휴대폰");
	m_edtDTel.SetMyFont("맑은 고딕", 17, FW_BOLD);
	m_edtDEtc.SetFontSize(13);
	m_edtDEtc.SetTitle("부서/담당");
	m_edtDDetail.SetFontSize(13);
	m_edtDDetail.SetTitle("상세위치");

	m_edtEtc.SetFontSize(13);
	m_edtDeposit.SetFontSize(13);
	m_edtTime.SetUserOption(RGB(0, 0, 255), RGB(240, 240, 240));
	m_edtOption.SetFontSize(13);
	m_edtChargeSum.SetUserOption(RGB(255, 0, 0), RGB(200, 255, 155));
	m_edtChargeInfo.SetFontSize(13);
	m_edtSearch.SetFont(m_FontManager.GetFont("맑은 고딕", 22, FW_BOLD));


	m_cmbStartKm.SetCurSel(4);
	m_cmbDestKm.SetCurSel(4);

	m_tooltip.Create(this, FALSE);
	m_tooltip.SetBehaviour(PPTOOLTIP_MULTIPLE_SHOW);
	m_tooltip.SetNotify();
	m_tooltip.SetImageList(IDB_LIST, 16, 18, 14, RGB(0,255,255));
	m_tooltip.SetTransparency(0);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_INITIAL, 100);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_AUTOPOP, 50000);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEIN, 10);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEOUT, 10);
	 
	InitRider();

	m_chkShowCompleteOrder.SetCheck(AfxGetApp()->GetProfileInt("AllocatePane", "bShowCompleteOrder", FALSE));

}



void CAllocatePaneDlg::RefreshList()
{

}

void CAllocatePaneDlg::OnBnClickedRefreshBtn()
{

}


int CAllocatePaneDlg::GetNearType(long nStartX1,long nStartY1, long nStartRealDongID,
								  long nOrderStartX1, long nOrderStartY1, long nOrderStartRealDongID, 
								  long nDestX2, long nDestY2, long nDestRealDongID, 
								  long nOrderDestX2, long nOrderDestY2,long nOrderDestRealDongID,
								  int nStartScope , int nDestScope)
{

	double nStartDistanceKm = -1, nDestDistanceKm = -1;
	nStartDistanceKm = m_poiNew.GetDistanceMeter(nStartX1, nStartY1, nOrderStartX1, nOrderStartY1) / 1000;
	nDestDistanceKm = m_poiNew.GetDistanceMeter(nDestX2, nDestY2, nOrderDestX2, nOrderDestY2) / 1000;
	int nStartType = -100, nDestType = -100;
	if(nStartRealDongID > 0 && nOrderStartRealDongID > 0 && nStartRealDongID == nOrderStartRealDongID)
		nStartType = 0;
	else if(nStartDistanceKm >= 0 && nStartDistanceKm <= 2)
		nStartType = 0;
	else if(nStartDistanceKm > 0 && nStartDistanceKm <= nStartScope)
		nStartType = 1;
	else
		nStartType = 4;

	if(nDestRealDongID > 0 && nOrderDestRealDongID > 0 && nDestRealDongID == nOrderDestRealDongID)
		nDestType = 0;
	else if(nDestDistanceKm >= 0 && nDestDistanceKm <= 2)
		nDestType = 0;
	else if(nDestDistanceKm > 0 && nDestDistanceKm <= nDestScope)
		nDestType = 2;
	else
		nDestType = 5;

	if(nStartType == 1 && nDestType == 5)
		return 7;
	else
		return nStartType + nDestType;
	//0 = 0, 0
	//2 = 0, 2
	//5 = 0, 5
	//1 = 1, 0
	//3 = 1, 2
	//7 = 1, 5
	//4 = 4, 0
	//6 = 4, 2
	//9 = 4, 5

	//0 = 0, 0
	//1 = 1, 0
	//2 = 0, 2
	//3 = 1, 2
	//4 = 4, 0
	//5 = 0, 5	
	//6 = 4, 2	
	//7 = 1, 5	
	//9 = 4, 5
	

}

void CAllocatePaneDlg::NearOrderRefresh(long nTNo)
{
	CString sStartKm, sDestKm;
	long dStartKm = 2.0, dDestKm = 2.0;
	
	//CComboBox a; a.GetWindowText().GetLBText()
	m_cmbStartKm.GetWindowText(sStartKm);
	m_cmbDestKm.GetWindowText(sDestKm);

	dStartKm = sStartKm.GetLength() > 0 ? atol(sStartKm) : dStartKm;
	dDestKm = sDestKm.GetLength() > 0 ? atol(sDestKm) : dDestKm;

	
	OrderRecordList orders = LU->GetRcpView()->GetCurrentOrder()->GetOrderRecordList();
	OrderRecordList::iterator it;

	m_nearReport.GetRecords()->RemoveAll();
	double nDistanceKm =0;
	for(it = orders.begin(); it != orders.end(); ++it)
	{
		if(it->second.nState == STATE_WAIT ||it->second.nState == STATE_RESERVED 
			|| it->second.nState == STATE_OK)
		{
			if(orders[nTNo].nTNo == it->second.nTNo)
				continue;

			if(it->second.nState == STATE_RESERVED &&
				it->second.dtState - COleDateTimeSpan(0, 0, 30, 0) > COleDateTime::GetCurrentTime())
			{
				continue;
			}

			int nRankType = -1;
			nRankType = GetNearType(orders[nTNo].nStartPosX,orders[nTNo].nStartPosY,orders[nTNo].nStartRealDongID,
						it->second.nStartPosX, it->second.nStartPosY,it->second.nStartRealDongID,
						orders[nTNo].nDestPosX, orders[nTNo].nDestPosY, orders[nTNo].nDestRealDongID,
						it->second.nDestPosX, it->second.nDestPosY, it->second.nDestRealDongID,dStartKm,dDestKm);				
			
			if(nRankType < 9)
			{
				CString sEtc = "";	
				m_nearReport.AddRecord(
					new CNearRecord(FALSE,it->first,it->second.nState,it->second.nCarType,it->second.nRunType,
					it->second.nWayType, m_ci.GetBranchName(it->second.nCompany),
					it->second.strCName.c_str(),it->second.info[11].c_str(),it->second.strStart.c_str(),
					it->second.strDest.c_str(),sEtc,it->second.dtRcp, nRankType, FALSE,it->second.nCompany));
			}
			
			
		}
	}
	m_nearReport.Populate();

}
void CAllocatePaneDlg::SetCustomerRefresh()
{
	long nTNo = GetTNo();
	
	m_edtSearch.SetWindowText("");

	int Seltem = LU->GetRcpView()->m_xList.GetSelectedItem();
	m_nState = LU->GetRcpView()->GetItemState(Seltem);
	long nOID, nSID, nDID;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_dorder_row_detail_a1");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_bShareOrder ? m_nShareCompany : m_ci.m_nCompanyCode);

	CMkParameter *parOID = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parSID = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parDID = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(!pRs.Execute(&pCmd)) return;
	
	if(pRs.IsEOF() || parRet->GetLong() == 0) {
		MessageBox("해당 데이터가 DB에 존재하지 않습니다.", "확인", MB_ICONERROR);
		pRs.Close();
		return;
	}

	nOID = parOID->GetLong();
	nSID = parSID->GetLong();
	nDID = parDID->GetLong();

	char buffer[20];
	long nStartDongID, nDestDongID, nDistanceKM, nReserveReleaseMin, nCompany;
	long nChargeAdd, nChargeBasic, nChargeTrans, nChargeDis, nChargeSum, nDeposit, nCouponCharge;
	long nRNo, nRiderCompany, nAllocateGroup, nPayType, nCarType, nWayType, nRunType;
	BOOL bCoupon;

	CString strWName,strOrderName, strOrderPhone, strOrderMP, strOrderDepart,strOrderManager,strOrderAddress;
	CString strOrderDetail,strOrderMemo, strOrderDong, strStartName, strStartPhone,strStartMP,strStartDepart ;
	CString strStartManager,strStartAddress,strStartDetail, strStartDong, strDestName , strDestPhone,strDestMP,strChargeBet ;
	CString  strDestDepart, strDestManager, strDestAddress, strDestDetail, strDestDong, strEtc, strRiderMP,strRiderName,strItemType;
	long nState, nOCNo,nSCNo, nDCNo;
	COleDateTime dt1, dtReserve;
	CString strChargeAdd,strChargeBasic ,strChargeTrans ,strChargeDis ,strChargeSum ,strDeposit;


	pRs.GetFieldValue("sWName", strWName);
	pRs.GetFieldValue("nState", nState);
	pRs.GetFieldValue("dt1", dt1);	
	pRs.GetFieldValue("dtReserve", dtReserve);
	pRs.GetFieldValue("nCompany", nCompany);

	pRs.GetFieldValue("nOCNo", nOCNo);
	pRs.GetFieldValue("sOName", strOrderName);
	pRs.GetFieldValue("sOPhone", strOrderPhone);
	pRs.GetFieldValue("sOMobile", strOrderMP);
	pRs.GetFieldValue("sODepart", strOrderDepart);
	pRs.GetFieldValue("sOManager", strOrderManager);
	pRs.GetFieldValue("sOAddress", strOrderAddress);
	pRs.GetFieldValue("sODetail", strOrderDetail);
	pRs.GetFieldValue("sOMemo", strOrderMemo);
	pRs.GetFieldValue("sODong", strOrderDong);

	pRs.GetFieldValue("nSCNo", nSCNo);
	pRs.GetFieldValue("sSName", strStartName);
	pRs.GetFieldValue("sSPhone", strStartPhone);
	pRs.GetFieldValue("sSMobile", strStartMP);
	pRs.GetFieldValue("sSDepart", strStartDepart);
	pRs.GetFieldValue("sSManager", strStartManager);
	pRs.GetFieldValue("sSAddress", strStartAddress);
	pRs.GetFieldValue("sSDetail", strStartDetail);
	pRs.GetFieldValue("sSDong", strStartDong);

	pRs.GetFieldValue("nDCNo", nDCNo);
	pRs.GetFieldValue("sDName", strDestName);
	pRs.GetFieldValue("sDPhone", strDestPhone);
	pRs.GetFieldValue("sDMobile", strDestMP);
	pRs.GetFieldValue("sDDepart", strDestDepart);
	pRs.GetFieldValue("sDManager", strDestManager);
	pRs.GetFieldValue("sDAddress", strDestAddress);
	pRs.GetFieldValue("sDDetail", strDestDetail);
	pRs.GetFieldValue("sDDong", strDestDong);

	pRs.GetFieldValue("nStartDongID", nStartDongID);
	pRs.GetFieldValue("nDestDongID", nDestDongID);

	pRs.GetFieldValue("sEtc", strEtc);
	pRs.GetFieldValue("nReserveReleaseMin", nReserveReleaseMin);
	//pRs.GetFieldValue("nFinalSMSSend", bFinalSendSMS);
	pRs.GetFieldValue("sItemType", strItemType);
	pRs.GetFieldValue("nPayType", nPayType);
	pRs.GetFieldValue("nCarType", nCarType);
	pRs.GetFieldValue("nWayType", nWayType);
	pRs.GetFieldValue("nRunType", nRunType);

	pRs.GetFieldValue("nChargeAdd", nChargeAdd );
	pRs.GetFieldValue("nChargeBasic", nChargeBasic);
	pRs.GetFieldValue("nChargeTrans", nChargeTrans);
	pRs.GetFieldValue("nChargeDis", nChargeDis);
	pRs.GetFieldValue("nChargeSum", nChargeSum);
	pRs.GetFieldValue("nDeposit", nDeposit);
	pRs.GetFieldValue("sChargeBet", strChargeBet);

	pRs.GetFieldValue("nDistanceKM", nDistanceKM);

	pRs.GetFieldValue("nRiderCompany", nRiderCompany);
	pRs.GetFieldValue("nRNo", nRNo);
	pRs.GetFieldValue("sRMobile", strRiderMP);
	pRs.GetFieldValue("sRName", strRiderName);
	pRs.GetFieldValue("nAllocGroup", nAllocateGroup);
	pRs.GetFieldValue("bCoupon", bCoupon);
	pRs.GetFieldValue("nCouponCharge", nCouponCharge);	
	if(nState != m_nState)
	{
		CString strMsg;
		strMsg = "해당 아이템의 상태가 다른 사람에 의해서 변경되었습니다.\n";
		strMsg += "확인 하시기 바랍니다.\n\n\n상태: ";
		strMsg += GetStateString(m_nState);
		strMsg += " --> ";
		strMsg += GetStateString(nState);
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		LU->GetRcpView()->RefreshList("", "", NULL, LU->GetRcpView()->m_nRefreshType);
		LU->m_pwndPane5->Hide();
	}

	m_nState = nState;

	m_edtTNo.SetWindowText(itoa(nTNo, buffer, 10));
	m_edtState.SetWindowText(GetStateString(nState));
	m_edtWNo.SetWindowText(strWName);
	m_edtTime.SetWindowText(dt1.Format("%H:%M:%S"));

	CBitmap bitmap;
	GetBitmapFromImageList(LU->GetRcpView()->GetImageList(), GetImageNumber(nState), bitmap);
	m_picState.SetBitmap((HBITMAP)bitmap.GetSafeHandle());


	//의뢰지 관련

	m_edtODONG.SetWindowText(strOrderDong);
	m_edtOName.SetWindowText(m_bShareOrder ? "N/A" : strOrderName);	
	m_edtOTel.SetWindowText(m_bShareOrder ? "N/A" : 
		BetweenSetSlash(GetDashPhoneNumber(strOrderPhone), GetDashPhoneNumber(strOrderMP)));

	m_edtOMemo.SetWindowText(strOrderMemo);	
	m_edtOEtc.SetWindowText(m_bShareOrder ? "N/A" : BetweenSetSlash(strOrderDepart, strOrderManager));
	m_edtODetail.SetWindowText(strOrderDetail);

	m_strOrderCNo = (itoa(nOCNo, buffer, 10));
	

	//출발지 관련
	m_strStartCNo = nSCNo == 0 ? "" : (itoa(nSCNo, buffer, 10));

	m_edtSDONG.SetWindowText(strStartDong);
	m_edtSName.SetWindowText(m_bShareOrder ? "N/A" : strStartName);	
	m_edtSTel.SetWindowText(m_bShareOrder ? "N/A" : 
		BetweenSetSlash(GetDashPhoneNumber(strStartPhone), GetDashPhoneNumber(strStartMP)));	
	m_edtSEtc.SetWindowText(m_bShareOrder ? "N/A" : BetweenSetSlash(strStartDepart,strStartManager) );
	m_edtSDetail.SetWindowText(strStartDetail);

	
	//도착지 관련
	m_strDestCNo = itoa(nDCNo, buffer, 10);

	m_edtDDONG.SetWindowText(strDestDong);
	m_edtDName.SetWindowText(m_bShareOrder ? "N/A" : strDestName);
	m_edtDTel.SetWindowText(m_bShareOrder ? "N/A" : 
		BetweenSetSlash(GetDashPhoneNumber(strDestPhone), GetDashPhoneNumber(strDestMP)));	
	m_edtDEtc.SetWindowText(m_bShareOrder ? "N/A" : BetweenSetSlash(strDestDepart,strDestManager));
	m_edtDDetail.SetWindowText(strDestDetail);	
	
	//적요
	m_edtEtc.SetWindowText(strEtc);

	//요금관련
	strChargeAdd = ::GetMyNumberFormat(nChargeAdd);
	strChargeBasic = ::GetMyNumberFormat(nChargeBasic);
	strChargeTrans = ::GetMyNumberFormat(nChargeTrans);
	strChargeDis = ::GetMyNumberFormat(nChargeDis);
	strChargeSum = ::GetMyNumberFormat(nChargeSum);
	CString strPay;
	if(nChargeBasic > 0) strPay = "기본:" + strChargeBasic;
	if(nChargeAdd > 0) strPay += " +추가:" + strChargeAdd;
	if(nChargeDis > 0) strPay += " -할인:" + strChargeDis;
	if(nChargeTrans > 0) strPay += " +탁송:" + strChargeTrans;

	m_edtChargeInfo.SetWindowText(strPay);
	m_edtChargeSum.SetWindowText(strChargeSum);
	m_edtDeposit.SetWindowText(::GetMyNumberFormat(nDeposit));	

	 
	CString strOption;
	if(nPayType > 0)
		strOption += CString("[") + GetPayTypeFromLong(nPayType) + "]";

	if(nCarType > 0)
		strOption += CString("[") + GetCarTypeFromLong(nCarType) + "]";

	if(nWayType > 0)
		strOption += CString("[") + GetWayTypeFromLong(nWayType) + "]";

	if(nRunType > 0)
		strOption += CString("[") + GetRunTypeFromLong(nRunType) + "]";

	if(nAllocateGroup > 0)
		strOption += CString("[배차") + itoa(nAllocateGroup, buffer, 10) + "그룹]";

	if(strItemType.GetLength() > 0)
		strOption += CString(" ") + strItemType;

	if(nChargeTrans > 0) 
		strOption += "[탁송:" + strChargeTrans + "]";

	m_edtOption.SetWindowText(strOption);
	
}


BOOL CAllocatePaneDlg::GetBitmapFromImageList(CImageList *imglist,int nIndex,CBitmap &bmp)
{
	IMAGEINFO pImageInfo;
	imglist->GetImageInfo(0, &pImageInfo);
	int nWidth = pImageInfo.rcImage.right - pImageInfo.rcImage.left;
	int nHeight = pImageInfo.rcImage.bottom - pImageInfo.rcImage.top;

	CDC dc, *pDC = GetDC();
	HICON hIcon = imglist->ExtractIcon(nIndex);

	dc.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, nWidth, nHeight);
	CBitmap* pOldBmp = dc.SelectObject(&bmp);
	CBrush brush ;
	COLORREF m_newclrBack;
	m_newclrBack=GetSysColor(COLOR_3DFACE);
	brush.CreateSolidBrush(m_newclrBack);
	::DrawIconEx(
		dc.GetSafeHdc(),
		0,
		0,
		hIcon,
		nWidth,
		nHeight,
		0,
		(HBRUSH)brush,
		DI_NORMAL);

	dc.SelectObject(pOldBmp);
	dc.DeleteDC();
	// the icon is not longer needed
	::DestroyIcon(hIcon);

	ReleaseDC(pDC);
	return(TRUE);
}
CString CAllocatePaneDlg::BetweenSetSlash(CString s1,CString s2)
{
	CString strTemp = "";
	int nResult1 = 0, nResult2 = 0;
	if(s1.GetLength() > 0)	nResult1++;
	if(s2.GetLength() > 0)	nResult2++;

	if(nResult1 + nResult2 > 1)
		strTemp = s1 + "/" + s2;
	else if(nResult1 == 1)
		strTemp = s1;
	else if(nResult2 == 1)
		strTemp = s2;
	else 
		strTemp = "";

	return strTemp;		
}

void CAllocatePaneDlg::InitRider()
{
	if(!m_List.GetSafeHwnd())
		return;

	m_List.DeleteAllItems();

	char buffer[10];
	long nItem = 0;
	MAP_ALLOC_RIDER::iterator itRider;
	for(itRider = LU->m_mapAllocateRider.begin(); itRider != LU->m_mapAllocateRider.end(); ++itRider)
	{
		if(::IsThisCompany("한반도로지넷"))
		{
			if(m_ci.GetShareCode1(itRider->second.lCode) != 15475)
				return;
		}
		else
		{
			if(m_ci.IsChildCompany(itRider->second.lCode) == FALSE)
				return;
		}
		
		m_List.InsertItem(nItem, ltoa(itRider->second.nMNo, buffer, 10), -1, 0);
		m_List.SetItemText(nItem, 1, itRider->second.strName);
		m_List.SetItemText(nItem, 2, GetCarTypeFromLong(itRider->second.nCarType));

		CString sRTID = itRider->second.strRTID;
		m_List.SetItemText(nItem, 3, itRider->second.strRTID);
		m_List.SetItemLong(nItem, itRider->second.lCode);
		m_List.SetItemData(nItem, itRider->second.nMNo);	 
		nItem++;
	}

	m_List.Populate();
}

void CAllocatePaneDlg::OnEnChangeXtplistctrlEdit()
{
	LU->GetRcpView()->SaveAllocatePaneLocation();

	m_nSelectedRCompany = -1;
	m_nSelectedRNo = -1;

	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_SEARCH_EDIT);

	CString strText;
	pEdit->GetWindowText(strText);
	strText.Trim();

	if(m_ci.m_bUseRTIDOnSpeedAllocate)
		m_List.Filter(strText, 4); 
	else
	{
		strText = RemoveLeftZero(strText);
		m_List.Filter(strText, 0);
	}

	if(m_List.GetVisibleItemCount() > 0 && strText.GetLength() > 0)
	{
		m_nSelectedRNo = m_List.GetItemData(0);
		m_nSelectedRCompany = m_List.GetItemLong(0);
	}

	CRect rc;
	m_RiderStatic.GetWindowRect(rc);
	ScreenToClient(rc);
	InvalidateRect(rc, FALSE);
	RefreshOrderList();
}

void CAllocatePaneDlg::OnReportItemClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM* pNMListView = (XTP_NM_REPORTRECORDITEM*)pNMHDR;

	if(!pNMListView->pRow)
		return;

	long nRow = pNMListView->pRow->GetIndex();

	if(m_List.GetVisibleItemCount() > 0)
	{
		m_nSelectedRNo = m_List.GetItemData(nRow);
		m_nSelectedRCompany = m_List.GetItemLong(nRow);

		CRect rc;
		m_RiderStatic.GetWindowRect(rc);
		ScreenToClient(rc);
		InvalidateRect(rc, FALSE);
		RefreshOrderList();
	}
}


BOOL CAllocatePaneDlg::PreTranslateMessage(MSG* pMsg)
{
	//m_tooltip.RelayEvent(pMsg);
	if(pMsg->hwnd == m_edtSearch.GetSafeHwnd()   )
	{
		if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN )
		{
			this->PostMessage(WM_ALLOCATE,0,0);
		}
		else if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_DOWN )
		{
			m_List.SetFocus();
			m_List.EnsureVisibleEx(0);
		}		
		else if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		{
			LU->m_paneManager.ClosePane(LU->m_pwndPane5);
		}
	}
	return CMyFormView::PreTranslateMessage(pMsg);
}

void CAllocatePaneDlg::OnEnSetfocusSearchEdit()
{
	LU->GetRcpView()->SetRefreshStop();	
}

void CAllocatePaneDlg::OnEnKillfocusSearchEdit()
{	
	LU->GetRcpView()->SetRefreshStart();	
}


LONG CAllocatePaneDlg::OnAllocate(WPARAM wParam, LPARAM lParam)
{
	OnBnClickedAllocateBtn();
	return 0;
}
LONG CAllocatePaneDlg::OnReadyAllocate(WPARAM wParam, LPARAM lParam)
{
	int nPaneOpenAllocate = (int)lParam;
	if(nPaneOpenAllocate)
	{
		if(wParam == VK_RETURN)
		{
			OnBnClickedAllocateBtn();
			return 0;
		}

		if(wParam >= 96)
			wParam -= 48;

		m_edtSearch.SendMessage(WM_KEYDOWN, wParam, 0);
		m_edtSearch.SendMessage(WM_CHAR, wParam, 0);
		m_edtSearch.SendMessage(WM_KEYUP, wParam, 0);

		if(GetFocus() != (CWnd*)&m_edtSearch)
		{
			m_edtSearch.SetFocus();
		}
	}
	else
	{
		m_edtSearch.SetFocus();
		CString strData;
		m_edtSearch.GetWindowText(strData);
		m_edtSearch.SetSel(0,strData.GetLength());
	}
	
	
	return 0;

}


void CAllocatePaneDlg::OnBnClickedAllocateBtn()
{
	if(m_edtSearch.GetWindowTextLength() == 0 || m_nSelectedRCompany < 0)
	{
		MessageBox("배차할 기사님을 선택하여 주세요", "확인", MB_ICONINFORMATION);
		m_edtSearch.SetFocus();
		return;
	}

	int nOrderSelectedCount = LU->GetRcpView()->m_xList.GetSelectedRows()->GetCount();
	if(nOrderSelectedCount <= 0)
	{
		MessageBox("메인리스트에서 오더를 한건이상 선택하여 주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_nState == STATE_RESERVED)
	{
		CString strMsg = "예약오더 입니다.\r\n\r\n";
		strMsg += "[   예   ] 현재시간에 해당기사에게 개별배차함\r\n";
		strMsg += "[아니요] 예약시간에 해당기사에게 개별배차함\r\n";
				
		long nRet = MessageBox(strMsg, "확인", MB_YESNO);

		if(nRet == IDNO)
		{
			if(UpdateRiderInfoForReserved(m_nTNo, m_nSelectedRCompany, m_nSelectedRNo))
			{
				LU->GetRcpView()->RefreshList();
				MessageBox("예약시간에 해당기사에게 개별배차됩니다", "확인", MB_ICONINFORMATION);
				return;
			}
			else
			{
				MessageBox("다시 시도하여 주시기 바랍니다", "확인", MB_ICONINFORMATION);
				return;
			}
			
		}
	}

	if(m_ci.m_bSingleAllocate)
	{
		if(IDYES != MessageBox("개별배차하시겠습니까?", "배차확인", MB_YESNO))
		{
			return;
		}
	}

	int nOrderSelIectedItem = -1;
	int nRiderItem = -1;

	
	long nRiderCompany = m_nSelectedRCompany;
	long nRNo = m_nSelectedRNo;
	ST_ALLOC_RIDER *pc = LU->GetAllocRider(m_nSelectedRCompany, m_nSelectedRNo);
	if(pc == NULL)
		return;
	long nWorkState = pc->nWorkState;

	if(nWorkState == 1)
	{
		MessageBox("휴직상태 기사님입니다", "확인", MB_ICONINFORMATION);
		return;
	}

	if(!CheckAllocateData())
		return;


	if(LF->IsAllocOrder(m_nState))
	{
		if(IDYES != MessageBox("이미 배차된 오더입니다. 재배차 하시겠습니까?", "배차확인", MB_YESNO))
		{
			return;
		}
	}
	
	//LU->GetRcpView()->Allocate(m_nTNo, nRNo, m_nState, nRiderCompany);
	LU->GetRcpView()->GetStateChange()->ChangeItemStateAllocate(m_nTNo, nRNo, nRiderCompany);

	if(!GetPaneDocking())
	{
		LU->m_paneManager.ClosePane(LU->m_pwndPane5);
	}

	if(m_bAutoHide)
	{
		LU->m_paneManager.HidePane(LU->m_pwndPane5);
		m_bAutoHide = FALSE;
	}
}

BOOL CAllocatePaneDlg::CheckAllocateData()
{
	int nSelItem = 0, nSelectedCount = LU->GetRcpView()->m_xList.GetSelectedRows()->GetCount();
	CXTPGridRow *pRow = NULL;
	for(nSelItem =0; nSelItem < nSelectedCount; nSelItem++)
	{
		pRow = LU->GetRcpView()->m_xList.GetSelectedRows()->GetAt(nSelItem);
	
		if(nSelItem < 0) {
			MsgBox(IDS_INVALID_ITEM);
			return FALSE;
		}

		long nSelItemItem = pRow->GetIndex();

		if(LU->GetRcpView()->GetItemState(nSelItemItem) == STATE_INTERNET) {
			MessageBox("인터넷 접수오더는 정상접수하신 후에, 배차하십시오!", 
				"확인", MB_ICONINFORMATION);
			return FALSE;
		}

		if(!m_bShareOrder && LU->GetRcpView()->GetItemSecondCross(nSelItemItem))
		{

			char buffer[10];
			CString strMsg = CString(ltoa(nSelItem, buffer,10)) + "번째 선택하신 아이템은\n\r ";
			strMsg = "크로스배차된 오더의 상태를 직접 변경하실 수 없습니다.\n";
			strMsg += "해당 회원사에게 전화하셔서 처리 하시기 바랍니다.";
			MessageBox(strMsg, "확인", MB_ICONINFORMATION);
			
			return FALSE;
		}


	}
	return TRUE;
}




void CAllocatePaneDlg::OnBnClickedNearorderBtn()
{
	CTestDlg d;
	d.DoModal();
}



void CAllocatePaneDlg::DrawInfoBox(CDC *pDC, CRect rc, BOOL bGreen)
{
	pDC->FillSolidRect(rc, RGB(0, 0, 0));
	rc.DeflateRect(1, 1, 1, 1);
	pDC->FillSolidRect(rc, RGB(200,200,255));
//	pDC->FillSolidRect(rc.left, rc.top, rc.Width(), rc.Height(), 
//		bGreen ? RGB(119, 185, 147) : RGB(230, 246 , 253)); 
}



void CAllocatePaneDlg::PrintLine(CDC *pDC, CRect &rc, CString strTitle, CString strText,BOOL bNextSeparator, COLORREF clrText)
{
	pDC->SetTextColor(RGB(50, 50, 50));
	pDC->DrawText(strTitle, rc, DT_LEFT);
	pDC->SetTextColor(clrText);
	pDC->DrawText(strText, rc, DT_RIGHT);
	if(bNextSeparator)
		rc.top += 20;
	else
		rc.top += 15;
}


void CAllocatePaneDlg::DrawRiderInfo(CDC *pDC)
{
	char buffer[10];
	if(m_nSelectedRCompany < 0)
		return;

	ST_ALLOC_RIDER *pRider = LU->GetAllocRider(m_nSelectedRCompany, m_nSelectedRNo);

	if(pRider == NULL)
		return;

	CXTPPenDC pen(*pDC, RGB(0, 0, 0));
	CXTPFontDC font(pDC, m_FontManager.GetFont("맑은 고딕", 16, FW_BOLD));
	pDC->SetBkMode(TRANSPARENT);
	
	CString strPanaltyTypeShowOrder = "", strLockType = "제한없음", strWorkState = "없음";
	CString strAllocateLimite = "", strLockOCType= "", strLockMYType= "";

	CRect rc;
	m_RiderStatic.GetClientRect(rc);	
	 
	DrawInfoBox(pDC, rc);
	rc.DeflateRect(5, 5, 5, 5);
	
	PrintLine(pDC, rc, "성명/기사번호",  pRider->strName + "/" +
			ltoa(pRider->nMNo, buffer, 10), TRUE, RGB(0, 150, 0));
	PrintLine(pDC, rc, "아이디",  GetDashPhoneNumber(pRider->strID), FALSE, RGB(50, 50, 200));
	PrintLine(pDC, rc, "휴대폰",  GetDashPhoneNumber(pRider->strHp), FALSE, RGB(50, 50, 200));
	//PrintLine(pDC, rc, "입사일",  pRider->dtEnter.Format("%y-%m-%d"), FALSE, RGB(50, 50, 200));

	CString strAllocType = "";
	if(pRider->nAllocType == 2)
		strAllocType = "PDA";
	else if(pRider->nAllocType == 1)
		strAllocType = "SMS";
	else
		strAllocType = "사용안함";
 
	PrintLine(pDC, rc, "배차방식", strAllocType, TRUE,RGB(50, 50, 200));
	PrintLine(pDC, rc, "현재위치", pRider->strCurDong, FALSE,RGB(0, 150, 0));
	PrintLine(pDC, rc, "", pRider->strCurLocation, FALSE,RGB(0, 150, 0));
	//PrintLine(pDC, rc, "업무중지", pRider->nWorkState > 0 ? 
	//	pRider->dtWorkStateDate.Format("%y-%m-%d") : sWorkState, FALSE, RGB(50, 50, 200));
	
}


void CAllocatePaneDlg::DrawEmptyInfo(CDC *pDC)
{
	CXTPPenDC pen(*pDC, RGB(0, 0, 255));
	CXTPFontDC font(pDC, m_FontManager.GetFont("맑은 고딕", 16, FW_BOLD));
	pDC->SetBkMode(TRANSPARENT);
	CRect rc;
	m_RiderStatic.GetClientRect(rc);

	DrawInfoBox(pDC, rc);
	rc.DeflateRect(5, 5, 5, 5);

	pDC->SetTextColor(RGB(50, 50, 200));
	pDC->DrawText("TIP!\n"\
				  "오른쪽 메인리스트에서\n"\
				  "오더선택후에 기사번호를\n"\
				  "입력하시면 자동으로\n"\
				  "빠른배차창이 나타납니다.\n"\
				  "그때 ENTER만 치시면 배차됨", rc, DT_CENTER | DT_VCENTER);
}


void CAllocatePaneDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	LF->FillBackground(&dc, this);  

	/*
	CRect rc;
	GetClientRect(&rc);
	dc.FillSolidRect(rc.left, rc.top, rc.Width(), rc.Height(), RGB(200,200,255)); 
	
	m_List.GetWindowRect(rc);
	ScreenToClient(rc);
	rc.InflateRect(1,1, 1,1);
	dc.Rectangle(rc);
*/
	CDC *pDC1 = m_RiderStatic.GetDC();
	if(m_List.GetVisibleItemCount() > 0 && m_edtSearch.GetWindowTextLength() > 0)
		DrawRiderInfo(pDC1);
	else
		DrawEmptyInfo(pDC1);

//	ReleaseDC(pDC1);
}

void CAllocatePaneDlg::OnMove(int x, int y)
{
	CMyFormView::OnMove(x, y);
	
}

void CAllocatePaneDlg::OnBnClickedNearAllocateCheck()
{
	NearAllocate();
}

void CAllocatePaneDlg::NearAllocate()
{
	if(m_edtSearch.GetWindowTextLength() == 0 || m_nSelectedRCompany < 0)
	{
		m_lstOrder.DeleteAllItems();
		return;
	}

	long nRiderCompany = m_nSelectedRCompany;
	long nRNo = m_nSelectedRNo;

	for(int i = 0; i < m_nearReport.GetRecords()->GetCount(); i++)
	{
		if(m_nearReport.GetRecords()->GetAt(i)->GetItem(0)->IsChecked())
		{
			CNearRecord *pRecord =  (CNearRecord *)m_nearReport.GetRecords()->GetAt(i);

            if(pRecord->m_nState == STATE_INTERNET) {
				MessageBox("인터넷 접수오더는 정상접수하신 후에, 배차하십시오!", 
					"확인", MB_ICONINFORMATION);
				return;
			}
			else if(LU->GetRcpView()->GetSecondCrossState(pRecord->m_nCompany))
			{
				char buffer[10];
				CString strMsg = CString(ltoa(i+1, buffer,10)) + "번째 선택하신 아이템은\n\r ";
				strMsg = "크로스배차된 오더의 상태를 직접 변경하실 수 없습니다.\n";
				strMsg += "해당 회원사에게 전화하셔서 처리 하시기 바랍니다.";
				MessageBox(strMsg, "확인", MB_ICONINFORMATION);

				return;
			}
			int nRet = LU->GetRcpView()->GetStateChange()->Allocate(pRecord->m_nTNo, nRNo, pRecord->m_nState, nRiderCompany);
			if(nRet == 1 || nRet == 10 || nRet == STATE_OK_ONLY_MAN)
				pRecord->m_nState = STATE_OK_ONLY_MAN;
			
		}
	}
	m_nearReport.Populate();
}


void CAllocatePaneDlg::RefreshOrderList()
{
	if(m_edtSearch.GetWindowTextLength() == 0 || m_nSelectedRCompany < 0)
	{
		m_lstOrder.DeleteAllItems();
		return;
	}

	long nCompany = m_nSelectedRCompany;
	long nRNo = m_nSelectedRNo;
	int index = 0;

	m_lstOrder.DeleteAllItems();
	OrderRecordList &order = LU->GetRcpView()->GetTodayOrder()->GetOrderRecordList();
	OrderRecordList::reverse_iterator it;

	for(it = order.rbegin(); it != order.rend(); it++)
	{
		if(it->second.nRiderCompany == nCompany && it->second.nRNo == nRNo)
		{
			if(it->second.nState < 11 || it->second.nState > 35) continue;

			COleDateTimeSpan span = 0;

			if(it->second.dtState.m_status != 2)  // DateTimeStatus.null
				span = COleDateTime::GetCurrentTime() - it->second.dtState;

	
			if(it->second.nState == STATE_FINISH)
			{
				if(m_chkShowCompleteOrder.GetCheck())
				{
					m_lstOrder.InsertItem(index, it->second.dtState.Format("%H:%M"), GetImageNumber(it->second.nState));
				}
				else
					continue;
			}
			else
			{
				char buffer[10];
				m_lstOrder.InsertItem(index, CString("+") + ltoa(span.GetTotalMinutes(), buffer, 10), 
					GetImageNumber(it->second.nState));
			}
			
			if(m_ci.IsChildCompany(it->second.nCompany))
				m_lstOrder.SetItemText(index, 1, it->second.strCName.c_str());
			else 
				m_lstOrder.SetItemText(index, 1, CString("[타]") + it->second.strCName.c_str());
			m_lstOrder.SetItemText(index, 2, it->second.strStart.c_str());
			m_lstOrder.SetItemText(index, 3, it->second.strDest.c_str());
			m_lstOrder.SetItemText(index, 4, GetMyNumberFormat(it->second.nCharge));
			m_lstOrder.SetItemLong(index++, it->second.bRiderOkOnlyMan);
		}
	}
	m_lstOrder.Populate();

}


void CAllocatePaneDlg::OnBnClickedRightDockingBtn()
{
	LU->m_pAllocatePane->SetPaneDocking(FALSE);
	LU->m_pwndPane5->Select();
	LU->m_paneManager.DockPane(LU->m_pwndPane5, xtpPaneDockRight);
}

void CAllocatePaneDlg::OnBnClickedLeftDockingBtn()
{
	LU->m_pAllocatePane->SetPaneDocking(FALSE);
	LU->m_pwndPane5->Select();
	LU->m_paneManager.DockPane(LU->m_pwndPane5, xtpPaneDockLeft);
}

void CAllocatePaneDlg::OnSize(UINT nType, int cx, int cy)
{
	if(m_nearReport.GetSafeHwnd())
	{
		CRect rcClient, rcNearOrder, rcOrderList, rcChk;  
		GetWindowRect(rcClient);
		m_nearReport.GetWindowRect(rcNearOrder); 
		m_lstOrder.GetWindowRect(rcOrderList);
		m_chkShowCompleteOrder.GetWindowRect(rcChk);

		ScreenToClient(rcClient);
		ScreenToClient(rcNearOrder);
		ScreenToClient(rcOrderList);
		ScreenToClient(rcChk);

		long nChkHeight = rcChk.Height();

		rcOrderList.bottom = rcClient.bottom - 5;
		rcOrderList.top = rcOrderList.bottom - 140;

		rcChk.bottom = rcOrderList.top - 4;
		rcChk.top = rcChk.bottom - nChkHeight;

		rcNearOrder.bottom = rcChk.top - 4;

		m_nearReport.MoveWindow(rcNearOrder);
		m_lstOrder.MoveWindow(rcOrderList);
		m_chkShowCompleteOrder.MoveWindow(rcChk);
	}

	CMyFormView::OnSize(nType, cx, cy);

}

void CAllocatePaneDlg::SetTNo(long nTNo, BOOL bShareOrder, long nShareCompany, long nRiderCompany, long nRNo, BOOL bTodayOrder)
{
	m_nTNo = nTNo; 
	m_bShareOrder = bShareOrder;
	m_nShareCompany = nShareCompany;
	m_nRiderCompany = nRiderCompany;
	m_nRNo = nRNo;
	m_bTodayOrder = bTodayOrder;
}

void CAllocatePaneDlg::OnBnClickedShowCompleteOrderCheck()
{
	AfxGetApp()->WriteProfileInt("AllocatePane", "bShowCompleteOrder", m_chkShowCompleteOrder.GetCheck());

	RefreshOrderList();
}

CString CAllocatePaneDlg::RemoveLeftZero(CString strText)
{
	while(TRUE)
	{
		if(strText.Left(1) != "0")
			break;

		strText = strText.Right(strText.GetLength() - 1);

	}

	return strText;
}