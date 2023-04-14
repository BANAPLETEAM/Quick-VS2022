// CustomerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CustomerDlg.h"
#include "AddCustomerDlg.h"
#include "RcpView.h"
#include "RcpDlg.h"
#include "SumCnoDlg.h"
#include "POIData.h"
#include "BCMenu.h" 
#include "SearchGroupDlg.h"
#include "CorporationDlg.h"
#include "SumCustomerDlg.h"
#include "MainFrm.h"
#include "ChargeHistoryMemDlg.h"
#include "RcpPlaceInfo.h"
#include "SearchPOIDlg.h"
#include "CustomerSelectChangeDlg.h"
#include "ChargeMemberDlg.h"
#include "POIDataAddress.h"
#include <math.h>

#include "CustomerDlgSub1.h"
#include "CustomerDlgSub2.h"
#include "CustomerDlgSub3.h"
#include "CustomerData.h"
// CCustomerDlg 대화 상자입니다.

CFont CXTPListCtrl10::m_fontBold;

HBRUSH CCustomerDlg::m_hBrush1 = NULL;
HBRUSH CCustomerDlg::m_hBrush2;
HBRUSH CCustomerDlg::m_hBrush3;
HBRUSH CCustomerDlg::m_hBrush4;
HBRUSH CCustomerDlg::m_hBrush5;
HBRUSH CCustomerDlg::m_hBrush6;
HBRUSH CCustomerDlg::m_hBrush7;


IMPLEMENT_DYNAMIC(CCustomerDlg, CMyDialog)
CCustomerDlg::CCustomerDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CCustomerDlg::IDD /*IDD_CUSTOMER_DLG*/, pParent)
, m_strKeyword(_T(""))
, m_nItem(0)
, m_strData(_T(""))
, m_nReturnVal(0)
{
	m_bModalMode = FALSE;
	m_pSub1 = NULL;
	m_pSub2 = NULL;
	m_pSub3 = NULL;

	m_nCouponCharge = ZERO;

	m_nCompanyCode = m_ci.m_nCompanyCode;
	m_nDOrderTable = m_ci.m_nUseDOrderTable;
	m_nCustomerTable = m_ci.m_nUseCustomerTable;
	m_nPayTable = m_ci.m_nUsePayTable;
	m_bGroup = FALSE;
	m_bFocusInSearch = FALSE;

	m_nCNo = ZERO;
	m_nTempCNo = ZERO;
	m_pRcpDlg = NULL;
	m_bDirty = FALSE;
	m_nSearchType = ZERO;

	m_pDragImage = NULL;
	m_pDragWnd = NULL;

	if(!m_hBrush1)
	{
		m_hBrush1 = CreateSolidBrush(RGB(220,220,220));
		m_hBrush2 = CreateSolidBrush(RGB(200,200,255));
		m_hBrush3 = CreateSolidBrush(RGB(255,255,255));
		m_hBrush4 = CreateSolidBrush(RGB(210,210,255));
		m_hBrush5 = CreateSolidBrush(RGB(220,220,255));
		m_hBrush6 = CreateSolidBrush(RGB(230,230,255));
		m_hBrush7 = CreateSolidBrush(RGB(255,200,200));
	}
 
	m_bOnOk = FALSE;
	m_pCusInfo = NULL;
	m_bNoneItemAutoCanceled = FALSE;

	m_bHasDetailPos = FALSE;
	m_bDongFirst= FALSE;
	m_bFirst = TRUE;
	m_bNoDelay = FALSE;

	m_bDragMode = FALSE;
	m_bClicking = FALSE;

	m_nPriceGrade = ZERO;
	m_nDiscountType = ZERO;

	m_bCustomerTelInsert = FALSE;
	m_bCustomerAddressInsert = FALSE;
	m_nMileage = ZERO;
	m_nMileageType = ZERO;
	m_nMileageBalance = ZERO;
	m_nMainAddressID = ZERO;	
	m_nPcMainAddressID = ZERO;

	m_nPersonCopySrcCNo = ZERO;
	m_bOrderCustomerSearch = FALSE;
	m_bGroupChangeReady = FALSE;

	m_pPlace = new CRcpPlaceInfo(this, PLACE_TYPE_CUSTOMER);
	m_pAddCustomerDlg = NULL;
	m_bDoNotRefresh = FALSE;
	m_nFirstTelID = ZERO;
	m_nSecondTelID = ZERO;
	m_nThirdTelID = ZERO;
	m_nRefreshTelID = ZERO;

	m_nLastCNo = ZERO;
	m_strLastTel = "";
	m_bCopyMode = FALSE;
	m_bCIDSearch = FALSE;
	m_bCloseDlg = FALSE;
	m_bLoadList = TRUE;
}

CCustomerDlg::~CCustomerDlg()
{
	/*
	DeleteObject(m_hBrush1);
	DeleteObject(m_hBrush2);
	DeleteObject(m_hBrush3);
	DeleteObject(m_hBrush4);
	DeleteObject(m_hBrush5);
	DeleteObject(m_hBrush6);
	DeleteObject(m_hBrush7);
	*/
	DeleteListAllItems(); 
	DELETE_OBJECT(m_pAddCustomerDlg);

	m_List.SaveReportOrder("CCustomerDlg", "m_List");
	DELETE_OBJECT(m_pPlace);
	LU->DestorySearchPoiDlg();

	//CloseHandle(m_hcArrow);
	//CloseHandle(m_hcNo);
	//CloseHandle(m_hcMoveHold);

	//g_bana_log->Print("CCustomerDlg::Close\n");
}

//"지원되지 않는 작업을 시도하였습니다." 에러인 경우에 아래 주석을 풀고 로그를 보면 위치를 정확히 알수 있음
//#define DDX_Control(x, y, z) { g_bana_log->Print("DDX_Control: FILE = %s, LINE = %d\n", TEXT(__FILE__), TEXT(__LINE__));DDX_Control(x, y, z);}


void CCustomerDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	
	DDX_Text(pDX, IDC_DATA_EDIT, m_strData);
	
	DDX_Control(pDX, IDC_CUS_LIST_1, m_List);
	DDX_Control(pDX, IDC_DATA_EDIT, m_edtData);
	
	DDX_Control(pDX, IDC_NEW_BTN, m_btnNew);
	DDX_Control(pDX, IDC_COPY_CUSTOMER_BTN, m_btnCopyCustomer);
	DDX_Control(pDX, IDC_EDIT_BTN, m_btnEdit);
	DDX_Control(pDX, IDC_EDIT_GROUP_ALL_BTN, m_btnEditGroupAll);
	DDX_Control(pDX, IDC_EDIT_PERSON_BTN, m_btnEditPersonBatch);

	DDX_Control(pDX, IDC_DEL_BTN, m_btnDel);
	DDX_Control(pDX, IDC_OK_BTN, m_btnOK);
	DDX_Control(pDX, IDC_SEARCH_BTN, m_btnSearch);
	DDX_Control(pDX, IDC_CANCEL_BTN, m_btnCancel);
	
	DDX_Control(pDX, IDC_SEARCH_STATIC, m_stcSearch);
	DDX_Control(pDX, IDC_COPORATION_BTN, m_btnCoporation);
	
	DDX_Control(pDX, IDC_SUM_CUS_BTN, m_btnSumCus);
	//DDX_Control(pDX, IDC_SET_MILEAGE_ALL_BTN, m_chkSetMileageAll);
	//DDX_Control(pDX, IDC_MILEAGE_DISPLAY_EDIT, m_edtMileageDisplay);
	//DDX_Control(pDX, IDC_SET_MILEAGE_BTN, m_btnSetMileage);
	DDX_Control(pDX, IDC_SEARCH_GROUP_CHECK, m_chkSearchGroup);
	DDX_Control(pDX, IDC_ADDRESS_LIST, m_lstAddress);
	DDX_Control(pDX, IDC_ADDRESS_BTN, m_btnAddress);
	DDX_Control(pDX, IDC_ADDRESS_CLOSE_BTN, m_btnAddressClose);
	
	DDX_Control(pDX, IDC_MOVE_LIST_CHECK, m_chkMoveList);
	DDX_Control(pDX, IDC_SHOW_DELETE_CUSTOMER_CHECK, m_chkShowDeleteCustomer);	
}

BEGIN_MESSAGE_MAP(CCustomerDlg, CMyDialog)
	ON_NOTIFY(XTP_NM_GRID_COLUMNORDERCHANGED, IDC_CUS_LIST_1, OnReportColumnChangeChanged)
	ON_NOTIFY(NM_DBLCLK, IDC_CUS_LIST_1, OnNMDblclkList1)
	ON_NOTIFY(NM_CLICK, IDC_ADDRESS_LIST, OnNMlclkAddressList)
	ON_NOTIFY(NM_DBLCLK, IDC_ADDRESS_LIST, OnNMDblclkAddressList)
	ON_NOTIFY(XTP_NM_GRID_SELCHANGED, IDC_CUS_LIST_1, OnReportItemChange)
	
	ON_BN_CLICKED(IDC_NEW_BTN, OnBnClickedNewBtn)
	ON_BN_CLICKED(IDC_EDIT_BTN, OnBnClickedEditBtn)
	ON_BN_CLICKED(IDC_DEL_BTN, OnBnClickedDelBtn)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_MESSAGE(WM_FOCUS_ON_SEARCH_EVENT, OnFocusOnSearchEvent)
	ON_COMMAND(IDC_NEW_BTN, OnBnClickedNewBtn)
	ON_COMMAND(ID_CUSTOMER_RECOVER, OnCustomerRecover)	
	ON_EN_CHANGE(IDC_DONG_EDIT, OnEnChangeDongEdit)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_TEAM_COMBO, OnCbnSelchangeGroupCombo)
	ON_BN_CLICKED(IDC_COPY_CUSTOMER_BTN, OnBnClickedCopyCustomerBtn)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_CUS_LIST_1, OnReportBeginDrag)
	ON_WM_MOUSEMOVE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
	ON_EN_CHANGE(IDC_DISPLAY_DONG_EDIT, OnEnChangeDisplayDongEdit)

	ON_BN_CLICKED(IDC_COPORATION_BTN, OnBnClickedCoporationBtn)
	ON_EN_CHANGE(IDC_DATA_EDIT, OnEnChangeDataEdit)

	ON_BN_CLICKED(IDC_EDIT_GROUP_ALL_BTN, OnBnClickedEditGroupAllBtn)
	ON_WM_CONTEXTMENU()

	ON_COMMAND(ID_SET_GROUP_OWNER, OnSetGroupOwner)
	ON_COMMAND(ID_SET_RELEASE_GROUP_OWNER, OnSetReleaseGroupOwner)
	ON_COMMAND(ID_MAKE_NEW_CUSTOMER, OnMakeNewCustomer)


	ON_NOTIFY(NM_RCLICK, IDC_CUS_LIST_1, OnReportItemRClick)

	ON_BN_CLICKED(IDC_SUM_CUS_BTN, OnBnClickedSumCusBtn)

	ON_BN_CLICKED(IDC_SEARCH_GROUP_CHECK, OnBnClickedSearchGroupCheck)
	ON_BN_CLICKED(IDC_ADDRESS_BTN, OnBnClickedAddressBtn)

	ON_COMMAND(ID_MAKE_MAIN_ADDRESS, OnMakeMainAddress)
	ON_COMMAND(ID_DELETE_ADDRESS, OnDeleteAddress)
	ON_BN_CLICKED(IDC_ADDRESS_CLOSE_BTN, OnBnClickedAddressCloseBtn)
	ON_EN_CHANGE(IDC_ADDR_TITLE_EDIT, OnEnChangeAddrTitleEdit)
	ON_BN_CLICKED(IDC_EDIT_PERSON_BTN, OnBnClickedEditPersonBtn)

	ON_COMMAND(ID_DELETE_CALL, OnDeleteCall)
	ON_COMMAND(ID_MAKE_MAIN, OnMakeMain)

	ON_WM_MOVE()
END_MESSAGE_MAP()


void CCustomerDlg::ChangeTelDepartInfo()
{
	CXTPGridRecord *pRecord = m_List.GetFirstSelectedRecord();	
	if(pRecord == NULL) return;

	ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_List.GetItemData(pRecord);
	CString strManager = m_List.GetItemText(pRecord, 3);
	CString strDepart = m_List.GetItemText(pRecord, 4);
 
	m_nTelID = pc->nTelID;
	m_pSub1->m_edtName.SetWindowText(strManager);
	m_pSub1->m_edtDepart.SetWindowText(strDepart);

	CString strPhone1, strPhone2, strPhone3;
	GetCustomerPhoneNumber(pc->nTelID, strPhone1, strPhone2, strPhone3);
	m_pSub1->m_edtTel.SetWindowText(::GetDashPhoneNumber(strPhone1));
	m_pSub1->m_edtMobile.SetWindowText(::GetDashPhoneNumber(strPhone2));
	m_pSub1->m_edtSms.SetWindowText(::GetDashPhoneNumber(strPhone3));
}

void CCustomerDlg::GetCustomerPhoneNumber(long nTelID, CString &strPhone1, CString &strPhone2, CString &strPhone3)
{
	CXTPGridControl *pControl = &m_pSub1->m_lstTel;
	CXTPGridRecords *pRecords = pControl->GetRecords();
	
	for(int i=ZERO; i<pRecords->GetCount(); i++)
	{ 
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		ST_TEL *st = (ST_TEL*)((CXTPListCtrl2*)pControl)->GetItemData(pRecord);

		if(st->nTelType == TEL_TYPE_PHONE1)
		{
			strPhone1 = st->strTel;
			m_nFirstTelID = st->nTelID;
		}
		else if(st->nTelType == TEL_TYPE_PHONE2)
		{
			strPhone2 = st->strTel;
			m_nSecondTelID = st->nTelID;
		}
		else if(st->nTelType == TEL_TYPE_SMS)
		{
			strPhone3 = st->strTel;
			m_nThirdTelID = st->nTelID;
		}

		if(strPhone1.IsEmpty() == FALSE &&
			strPhone2.IsEmpty() == FALSE &&
			strPhone3.IsEmpty() == FALSE )
			break;
	}

	if(strPhone1.IsEmpty())
		m_nFirstTelID = 0;
	if(strPhone2.IsEmpty())
		m_nSecondTelID = 0;
	if(strPhone3.IsEmpty())
		m_nThirdTelID = 0;
}


void CCustomerDlg::OnReportColumnChangeChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	ASSERT(pItemNotify != NULL);

}

void CCustomerDlg::OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) return; 
	else if(pRows->GetCount() == ZERO) return;

	CXTPGridRow *pRow = pRows->GetAt(ZERO);

	SetCopyMode(FALSE);

	m_bCustomerTelInsert = FALSE;	

	CXTPGridRecord *pRecord = pRow->GetRecord();
	ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_List.GetItemData(pRecord);

	int nItem = pRecord->GetIndex();
	CString strTel;

	CString strName = pRecord->GetItem(0)->GetCaption(NULL);

	if((strName != "지명") && (pc->nCNo != LINE_ROW) && (pc->nCNo != GROUP_NAME_ROW))
	{
		GetCurInfo(pc); 

		UpdateData(FALSE);
		m_pSub1->UpdateData(FALSE);
		m_pSub2->UpdateData(FALSE);
		m_pSub3->RefreshDlg();
		m_bDirty = FALSE; 

		//고객전화번호 검색타이머
		//키패드를 움직인 후 0.5초가 지난후에 전화번호리스트를 불러들인다.
		//KillTimer(0);
		SetTimer(0, 500, NULL);

		InitControl(TRUE);
		RefreshTelList(m_nTelID);
		
		//OpenTelDlg();
	}
	else 
	{
		if(strName == "지명")
		{
			CPOIUnit *pc = (CPOIUnit*)m_List.GetItemData(nItem);
			GetCurDongInfo(pc);
		}
		UpdateData(FALSE);
		m_pSub1->UpdateData(FALSE);
		m_pSub2->UpdateData(FALSE);
		m_pSub3->RefreshDlg();

		InitControl(FALSE);		
	}
} 

void CCustomerDlg::InitControl(BOOL bEnable)
{
	m_pSub1->m_edtUserID.SetReadOnly(!bEnable); 
	m_pSub1->m_edtCompany.SetReadOnly(!bEnable);
	m_pSub1->m_edtDepart.SetReadOnly(!bEnable); 
	m_pSub1->m_edtName.SetReadOnly(!bEnable);
	m_pSub1->m_edtTel.SetReadOnly(!bEnable);
	m_pSub1->m_edtMobile.SetReadOnly(!bEnable);
	m_pSub1->m_edtLocate.SetReadOnly(!bEnable);
	m_pSub1->m_edtMemo.SetReadOnly(!bEnable);
	m_pSub1->m_edtRiderMemo.SetReadOnly(!bEnable);
	m_pSub1->m_edtAddrDong.SetReadOnly(!bEnable);
	m_pSub1->m_edtDisplayDong.SetReadOnly(!bEnable);
	m_pSub1->m_edtTelAdd.SetReadOnly(!bEnable);
	m_pSub1->m_btnTelAdd.EnableWindow(bEnable);
	m_pSub1->m_btnTelDel.EnableWindow(bEnable);
	m_pSub1->m_lstTel.EnableWindow(bEnable);
	m_pSub1->m_chkCredit.EnableWindow(bEnable);
	m_pSub1->m_btnGroupRefresh.EnableWindow(bEnable);
	m_pSub1->m_btnChangeGroup.EnableWindow(bEnable);
	m_pSub1->m_btnNoGroup.EnableWindow(bEnable);
	m_pSub1->m_btnShowMap.EnableWindow(bEnable);
	
	//m_pSub1->m_editAddrTitle.EnableWindow(FALSE);
	m_pSub2->m_chkSendStateChangeSMS.EnableWindow(bEnable);
	m_pSub2->m_chkICMapDisplayType.EnableWindow(bEnable);
	m_pSub2->m_chkUseHomePage.EnableWindow(bEnable);
	m_pSub2->m_chkPreventPosUpdate.EnableWindow(bEnable);
	m_pSub2->m_cmbPriceGrade.EnableWindow(bEnable);
	m_pSub2->m_cmbCoupon.EnableWindow(bEnable);
	m_pSub2->m_edtCoupon.EnableWindow(bEnable);
	m_pSub2->m_btnSetCoupon.EnableWindow(bEnable);
	m_pSub2->m_cmbDiscount.EnableWindow(bEnable);
	m_pSub2->m_edtDiscount.EnableWindow(bEnable);
	m_pSub2->m_btnSetDiscount.EnableWindow(bEnable);
	m_pSub2->m_cmbMileage.EnableWindow(bEnable);
	m_pSub2->m_edtMileage.EnableWindow(bEnable);
	m_pSub2->m_btnSetMileage.EnableWindow(bEnable);
	m_pSub2->m_edtLoginID.EnableWindow(bEnable);
	m_pSub2->m_edtLoginPW.EnableWindow(bEnable);
	m_pSub2->m_cmbCustomerGrade.EnableWindow(bEnable);
	m_pSub2->m_cmbAllocGroup.EnableWindow(bEnable);
	m_pSub2->m_cmbSalesTeam.EnableWindow(bEnable);
	m_pSub2->m_dtpSalesTime.EnableWindow(bEnable);

	if(bEnable ==TRUE)
		m_pSub2->OnCbnSelchangeSalesTeamCombo();

	m_pSub2->m_edtDiscount.SetReadOnly(!bEnable);

	m_btnCopyCustomer.EnableWindow(bEnable);
	m_btnEdit.EnableWindow(bEnable); 
	m_btnDel.EnableWindow(bEnable);
	m_btnEditGroupAll.EnableWindow(bEnable);
	m_btnEditPersonBatch.EnableWindow(bEnable);

}
// CCustomerDlg 메시지 처리기입니다.

BOOL CCustomerDlg::OnInitDialog()
{ 
	CMyDialog::OnInitDialog();

	//SetForegroundWindow();
	//SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);

	CXTPGridColumn *pCol0 = m_List.InsertColumnReturn(0, "번호", LVCFMT_LEFT, 30);
	CXTPGridColumn *pCol1 = m_List.InsertColumnReturn(1, "번호", LVCFMT_LEFT, 50);
	m_List.InsertColumn(2, "회사", LVCFMT_LEFT, 135);
	m_List.InsertColumn(3, "담당", LVCFMT_LEFT, 75);
	m_List.InsertColumn(4, "부서", LVCFMT_LEFT, 95);	
	m_List.InsertColumn(5, "전화번호", LVCFMT_LEFT, 100);
	m_List.InsertColumn(6, "신용", LVCFMT_LEFT, 40);
	m_List.InsertColumn(7, "검색코드", LVCFMT_LEFT, 60);
	m_List.InsertColumn(8, "고객ID", LVCFMT_LEFT, 60);
	m_List.InsertColumn(9, "기준동", LVCFMT_LEFT, 70);
	m_List.InsertColumn(10, "그룹명", LVCFMT_LEFT, 95);
	m_List.InsertColumn(11, "위치", LVCFMT_LEFT, 280);
	m_List.InsertColumn(12, "가산금", LVCFMT_LEFT, 40);

	m_List.GetReportHeader()->AllowColumnSort(TRUE);
	m_List.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_List.GetReportHeader()->AllowColumnResize(TRUE);

	pCol0->SetTreeColumn(1);
	pCol0->SetVisible(FALSE);

	m_List.SetTreeIndent(0);

	m_List.Populate();

	m_lstAddress.InsertColumn(0, "주소타이틀", LVCFMT_LEFT, 100);
	m_lstAddress.InsertColumn(1, "상세위치", LVCFMT_LEFT, 450);
	m_lstAddress.ShowHeader(FALSE);
	m_lstAddress.Populate();
	m_lstAddress.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_lstAddress.GetPaintManager()->m_strNoItems = "";
	m_lstAddress.Populate();


	CRect rtSTATIC_OPTION;
	this->GetDlgItem(IDC_STATIC_OPTION)->GetWindowRect(rtSTATIC_OPTION);
	this->ScreenToClient(rtSTATIC_OPTION);
	this->GetDlgItem(IDC_STATIC_OPTION)->ShowWindow(SW_HIDE);

	LU->CreateFormViewTabControl(this, &m_wndTabControl, rtSTATIC_OPTION, xtpTabPositionRight);

	//순서 바뀌면 안됨
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCustomerDlgSub1), "일반", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCustomerDlgSub2), "요금/기타", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCustomerDlgSub3), "프린터출력", 0);

	m_pSub1 = (CCustomerDlgSub1*)GetTabItem(0); m_pSub1->m_pCustomerDlg = this;
	m_pSub2 = (CCustomerDlgSub2*)GetTabItem(1); m_pSub2->m_pCustomerDlg = this;
	m_pSub3 = (CCustomerDlgSub3*)GetTabItem(2); m_pSub3->m_pCustomerDlg = this;

	LU->MakeAllocateGroupCombo(&m_pSub2->m_cmbAllocGroup);
	LU->FillCompanyChargeList(&m_pSub2->m_cmbCompanyCharge);
 	//InitDialog();

	return TRUE;
}


void CCustomerDlg::ClearCustomerDlg()
{	
	m_pCusInfo = NULL;
	m_nCNo = ZERO;
	m_nID = ZERO;
	m_nGNo = ZERO;
	m_pSub1->m_strID = "";
	m_pSub1->m_strCompany = "";
	m_pSub1->m_strDepart = "";
	m_pSub1->m_strName = "";
	m_pSub1->m_strTel = "";
	m_pSub1->m_strDisplayDong = "";
	m_pSub1->m_strLocation = "";
	m_pSub1->m_bCredit = FALSE;
	m_pSub2->m_strDiscount = "";
	m_pSub2->m_cmbAllocGroup.SetCurSel(ZERO);
	m_pSub2->m_strCoupon = "";
	m_pSub1->m_strMobile = "";
	m_pSub1->m_strMemo = "";
	m_pSub1->m_strCustomerType = "일반고객";
	m_pSub1->m_strFirstUse = "";
	m_pSub1->m_strLastUse = "";
	m_pSub1->m_strUseCount = "";
	m_pSub1->m_strRiderMemo = "";
	m_pSub1->m_strAddress = "";
	m_nDongID = ZERO;
	m_pSub2->m_strEMail = "";
	m_nPosX = ZERO;
	m_nPosY = ZERO;

	m_pSub2->m_nSalesCompany = ZERO;
	m_pSub2->m_nSalesWNo = ZERO;
	m_pSub2->m_dtSalesTime = COleDateTime::GetCurrentTime();

	m_pSub1->m_strAddrDong = "";

	m_nUseCount = ZERO;
	m_nCancelCount = ZERO;
	m_dtRegister = COleDateTime::GetCurrentTime();
	m_dtLast = COleDateTime::GetCurrentTime();

	m_nCreditCount = ZERO;
	m_nCreditCharge = ZERO;
	m_pSub1->m_strUserID = "";
	m_pSub2->m_nSendStateChangeSMS = ONE;
	m_pSub2->m_bPreventPosUpdate = TRUE;
	m_pSub2->m_strLoginID = "";
	m_pSub2->m_strLoginPW = "";
	m_pSub2->m_bUseHomepage = FALSE;
	m_pSub2->m_cmbCustomerGrade.SetCurSel(2);
	m_pSub2->m_cmbPriceGrade.SetCurSel(ZERO);  

	m_pSub2->m_cmbMileage.SetCurSel(ZERO);
	m_nMileage = ZERO;
	m_nMileageType = ZERO;
	m_nMileageBalance = ZERO;
	m_nMainAddressID = ZERO;
	m_nPcMainAddressID = ZERO;
	m_pSub2->m_nICMapDisplayType = ZERO;
	m_bHasDetailPos = ZERO;

	m_pSub1->m_strAddrTitle = "대표주소";
	m_pSub2->m_cmbMileage.SetCurSel(3);  // 10 마일리지 개별적용 안함

	m_pSub2->m_edtMileage.EnableWindow(TRUE);
	m_pSub2->m_strMileage = "0";
	m_pSub2->m_edtMileage.SetWindowText("");

	m_pSub2->m_cmbDiscount.SetCurSel(ZERO);
	m_pSub2->m_cmbCoupon.SetCurSel(ZERO);
	m_pSub1->m_strGroupName = "N/A";

	m_pSub1->UpdateData(FALSE); 
	m_pSub2->UpdateData(FALSE); 
	m_pSub2->SelChangeOption();
	SetAddressInfo();
	m_pPlace->SetData(ZERO, ZERO, ZERO, FALSE, "");

	m_pSub1->m_lstTel.GetRecords()->RemoveAll();
	m_pSub1->m_lstTel.Populate();

	m_pSub2->m_cmbCompanyCharge.SetCurSel(0);
}

int CCustomerDlg::InitDialog()
{ 
	m_bCloseDlg = FALSE;
	m_pPlace->SetControl(&m_pSub1->m_edtAddrDong, &m_pSub1->m_stcAddressDisplay, NULL, &m_pSub1->m_edtLocate,
		&m_pSub1->m_edtCompany, &m_pSub1->m_edtTel, &m_pSub1->m_edtMobile, &m_pSub1->m_edtDisplayDong);
		 
	m_chkSearchGroup.SetCheck(AfxGetApp()->GetProfileInt("CCustomerDlg", "GroupSearch", 0));
	
	SetWindowText(m_strBranchName);

	/*
	if(m_bGroup) {
	CString strTitle;
	GetWindowText(strTitle);
	SetWindowText(m_strBranchName + " - " + strTitle);
	}
	*/
 
	if(m_bFocusInSearch)
		PostMessage(WM_FOCUS_ON_SEARCH_EVENT);

	InitList(m_bDongFirst);

	//long nCount = m_List.GetItemCount();
	//신규고객창을 바로 띄움..
	if(m_List.GetItemCount() == ZERO)// &&   
		//(!m_strSearchName.IsEmpty() || !m_strSearchPhone.IsEmpty()))
	{
		if(m_bCIDSearch == TRUE)
		{			
			m_pRcpDlg->m_EDT_ORDER_PHONE.pEdit->SetWindowText(m_strSearchPhone);
			m_pRcpDlg->m_EDT_START.pEdit->SetFocus();
			m_bCloseDlg = TRUE;
			return TRUE;
		}

		if(m_bOrderCustomerSearch == FALSE)
		{
			ClearCustomerDlg();
			ShowWindow(SW_SHOW);	
			PostMessage(WM_COMMAND, IDC_NEW_BTN, 0L);
		}
		else
			OnCancel();
	}
	else if(m_bCIDSearch == TRUE && m_List.GetItemCount() == ONE)
	{		
		m_List.GetSelectedRows()->Select(m_List.GetRows()->GetAt(ZERO));
		OnBnClickedOk();
		m_bCloseDlg = TRUE;
		return TRUE;
	}


	m_hcArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_hcNo = AfxGetApp()->LoadStandardCursor(IDC_NO);
	m_hcMoveHold = AfxGetApp()->LoadCursor(IDC_MOVEHOLD);

	/*
	m_stcCNo.EnableClick(TRUE);
	m_stcCompany.EnableClick(TRUE);
	m_stcDepart.EnableClick(TRUE);
	m_stcManager.EnableClick(TRUE);
	m_stcTel.EnableClick(TRUE);
	m_stcMobile.EnableClick(TRUE);
	m_stcLocate.EnableClick(TRUE);
	m_stcMemo.EnableClick(TRUE);
	m_stcRiderMemo.EnableClick(TRUE);
	m_stcAddress.EnableClick(TRUE);
	m_stcBaseDong.EnableClick(TRUE);
	m_stcAllocGroup.EnableClick(TRUE);
	m_pSub2->m_stcPriceGrade.EnableClick(TRUE);
	m_pSub2->m_stcDiscount.EnableClick(TRUE);
	m_pSub2->m_stcCoupon.EnableClick(TRUE);
	m_pSub2->m_stcMileage.EnableClick(TRUE);
	*/

	m_List.LoadReportOrder("CCustomerDlg", "m_List");
	m_bLoadList = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCustomerDlg::InitList(BOOL bDongFirst)
{ 
	int nItem = 0;
	CString strGNo; 

	//std::list<long> GROUP_GNO_TOT;
	//std::list<long>::iterator it;
	//GROUP_GNO_TOT.clear();

	DeleteListAllItems();
	GetCustomerInfo(nItem, strGNo, 0);

	if(m_chkSearchGroup.GetCheck() && strGNo.GetLength() > 0)
		SearchGroupData(strGNo.Right(strGNo.GetLength() - 1));

	m_bDirty = FALSE;
	//m_List.Populate();
}

void CCustomerDlg::SetCompanyApplyCharge(long nMemCNo)
{
	if(m_pCusInfo)
	{
		if(m_pCusInfo->nCNo > 0)
		{
			CMkCommand pCmd(m_pMkDb, "update_customer_company_charge");	
			pCmd.AddParameter(m_nCustomerTable);
			pCmd.AddParameter(m_pCusInfo->nCNo);
			pCmd.AddParameter(nMemCNo); 
			pCmd.Execute();
		}
		
	}

}

void CCustomerDlg::OnBnClickedNewBtn()
{
	if(m_pAddCustomerDlg == NULL)
	{
		m_pAddCustomerDlg = new CAddCustomerDlg(this);
		m_pAddCustomerDlg->Create(IDD_ADD_CUSTOMER_DLG, this);
	}
	m_pAddCustomerDlg->m_nCustomerTable = m_nCustomerTable;
	m_pAddCustomerDlg->m_pCustomerDlg = this;

	if(m_pRcpDlg && (m_nTempCNo > 0 || m_pRcpDlg->m_bInternet == TRUE))
	{
		m_pAddCustomerDlg->m_strCompany = m_strTempCompany;
		m_pAddCustomerDlg->m_strAddrDong = m_strTempDong;
		m_pAddCustomerDlg->m_strTel = m_strTempTel;
		m_pAddCustomerDlg->m_strMobile = m_strTempMobile;		
		m_pAddCustomerDlg->m_strDepart = m_strTempDepart;
		m_pAddCustomerDlg->m_strName = m_strTempName;
		m_pAddCustomerDlg->m_strLocation = m_strTempLocation;
		m_pAddCustomerDlg->m_nTempCNo = m_nTempCNo;
		m_pAddCustomerDlg->m_bInternet = m_pRcpDlg->m_bInternet;
	}
	else 
	{
		if(m_strSearchName.Left(1) == "-")
		{
			m_pAddCustomerDlg->m_strUserID = m_strSearchName;
			m_pAddCustomerDlg->m_strUserID.Replace("-", "");
		}
		else
			m_pAddCustomerDlg->m_strCompany = m_strSearchName;

		if(m_pRcpDlg)
		{
			//if(!m_pRcpDlg->m_pBi->bNotCustomerAddCID)
			m_pAddCustomerDlg->m_strTel = m_strSearchPhone;	
		}
		
	}

	m_pAddCustomerDlg->UpdateData(FALSE);
	m_pAddCustomerDlg->ShowWindow(SW_SHOW);
}

void CCustomerDlg::OnBnClickedCopyCustomerBtn()
{

	if(m_nCNo <= 0)
	{
		MessageBox("복사할 고객을 선택하여 주시기 바랍니다.", "확인", MB_ICONEXCLAMATION);
		return;
	}

	if(m_pSub1->m_strCustomerType == "지명")
	{
		MessageBox("지명은 복사하실 수 없습니다.", "확인", MB_ICONEXCLAMATION);
		return;
	}

	if(IsCopyMode() == FALSE)
	{
		SetCopyMode(TRUE); 

		//m_pSub1->m_edtDepart.SetWindowText("");
		m_pSub1->m_edtName.SetWindowText("");
		m_pSub1->m_edtTel.SetWindowText("");
		m_pSub1->m_edtMobile.SetWindowText("");
		m_pSub1->m_edtSms.SetWindowText("");
		m_pSub1->m_lstTel.DeleteAllItems();

		MessageBox("해당고객의 부서, 담당자, 전화번호등의 정보를 입력 후\r\n[복사완료] 버튼을 클릭 후 고객복사를 완료하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	m_pSub1->UpdateData(TRUE);
	m_pSub2->UpdateData(TRUE);

	BOOL bUserIDSequence = FALSE;
	if(m_pRcpDlg->m_pBi->bUserIDSequence)
	{
		if(MessageBox("복사하는 고객에 대하여 고객번호를 증가시키겠습니까?",
			"확인", MB_ICONINFORMATION | MB_YESNO) == IDYES)
		{
			bUserIDSequence = TRUE;
		}
	}

	CString strTel; m_pSub1->m_edtTel.GetWindowText(strTel);
	CString strMobile; m_pSub1->m_edtMobile.GetWindowText(strMobile);

	CMkCommand pCmd(m_pMkDb, "insert_copy_customer_2011_5");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(m_nCustomerTable);
	pCmd.AddParameter(m_nCNo);
	pCmd.AddParameter(bUserIDSequence); 
	pCmd.AddParameter(m_pSub1->m_strDepart);
	pCmd.AddParameter(m_pSub1->m_strName);
	pCmd.AddParameter(strTel);
	pCmd.AddParameter(strMobile);
	pCmd.AddParameter(m_pSub1->m_strSms);
	pCmd.AddParameter(m_pSub1->m_strCompany); 
	pCmd.AddParameter(m_pSub1->m_strMemo);
	pCmd.AddParameter(m_pSub1->m_strRiderMemo);
	pCmd.AddParameter(m_pSub1->m_strLocation);
	pCmd.AddParameter(m_pSub1->m_strDisplayDong);
	pCmd.AddParameter(m_pSub1->m_stcAddressDisplay.GetNormalText());
	//pCmd.AddParameter(m_pSub1->m_strAddress); 
	pCmd.AddParameter(m_nDongID);
	pCmd.AddParameter(m_nPosX);
	pCmd.AddParameter(m_nPosY);

	pCmd.AddParameter(m_pSub1->GetCreditType());
	pCmd.AddParameter(m_pSub1->m_bNotAutoShareOrder);



	if(pCmd.Execute())
	{
		long nCopyCNo = parRet->GetLong();
		if(nCopyCNo > 0)
		{
			m_nCNo = nCopyCNo;
			m_strKeyword.Format("%d ", nCopyCNo);
			m_nSearchType = ST_CNO;
			m_pSub1->Invalidate();
			InitList();
			SetCopyMode(FALSE);

			MessageBox("고객을 복사하였습니다.", "확인", MB_ICONINFORMATION);
		}
	}
	

	/*

	m_bNoneItemAutoCanceled = FALSE;

	BOOL bUserIDSequence = FALSE;
	if(m_pRcpDlg->m_pBi->bUserIDSequence)
	{
		if(MessageBox("복사하는 고객에 대하여 고객번호를 증가시키겠습니까?",
			"확인", MB_ICONINFORMATION | MB_YESNO) == IDYES)
		{
			bUserIDSequence = TRUE;
		}
	}
 
	CMkCommand pCmd(m_pMkDb, "insert_copy_customer_2011_3");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(m_nCustomerTable);
	pCmd.AddParameter(m_nCNo);
	pCmd.AddParameter(bUserIDSequence); 
	pCmd.AddParameter(m_pSub1->m_strDepart);
	pCmd.AddParameter(m_pSub1->m_strName);
	//pCmd.AddParameter(m_nTelID);

	if(pCmd.Execute())
	{
		long nCopyCNo = parRet->GetLong();
		if(nCopyCNo > 0)
		{
			m_nCNo = nCopyCNo;
			m_strKeyword.Format("%d ", nCopyCNo);
			m_nSearchType = ST_CNO;
			m_pSub1->Invalidate();
			InitList();

			MessageBox("고객을 복사하였습니다.\n원하시는 정보를 수정하시기 바랍니다.", "확인", MB_ICONINFORMATION);
		}
	}
	*/

}



void CCustomerDlg::OnBnClickedEditBtn()
{
	if(EditCustomer())
	{
		m_bDirty = FALSE;
		m_btnOK.SetFocus();
	}
}

BOOL CCustomerDlg::EditCustomer()
{ 
	if((CXTPGridRecord*)m_List.GetFirstSelectedRecord() == NULL)
	{
		MessageBox("수정하려는 고객을 선택하세요", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	if(MessageBox("변경된 내용을 저장하시겠습니까?", "확인", MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		//CWaitCursor wait;
		CString strPhone1, strPhone2, strPhone3, sDiscountRange = "";
		long nDiscountRange = 0;
		UpdateData(TRUE);
		m_pSub1->UpdateData(TRUE);
		m_pSub2->UpdateData(TRUE);

		m_pSub1->m_edtTel.GetWindowText(strPhone1);
		m_pSub1->m_edtMobile.GetWindowText(strPhone2);
		m_pSub1->m_edtSms.GetWindowText(strPhone3);
		m_pSub2->m_edtDiscountRange.GetWindowText(sDiscountRange);
		m_pSub2->m_strMileage.Replace(",","");

		nDiscountRange = GetMyUnNumberFormat(sDiscountRange);

		if(!IsPhoneNumber(strPhone1) || !IsPhoneNumber(strPhone2))
		{
			MessageBox("전화번호에 숫자/대쉬 이외의 문자는 사용하실수 없습니다.",
				"조건확인", MB_ICONINFORMATION);
			return FALSE;
		}

		if(strPhone1.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
			strPhone1 = strPhone1.Right(strPhone1.GetLength() - m_ci.m_strDDD.GetLength());

		if(strPhone2.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
			strPhone2 = strPhone2.Right(strPhone2.GetLength() - m_ci.m_strDDD.GetLength());


		if(m_pSub1->m_strCompany.GetLength() < 2) 
		{
			MessageBox("상호명을 입력하여 주시기바랍니다.", 
				"조건확인", MB_ICONINFORMATION);
			return FALSE;
		}

		if(m_pSub2->m_strLoginID.GetLength() > 0 &&
			m_pSub2->m_strLoginPW.GetLength() == 0) 
		{
			MessageBox("비밀번호를 입력하세요", 
				"조건확인", MB_ICONINFORMATION);
			return FALSE;
		}

		if(m_pSub2->m_strLoginID != "")
		{
			if(CheckLoginID() == FALSE)
			{
				MessageBox("고객ID가 중복됩니다.", 
					"조건확인", MB_ICONINFORMATION);
				return FALSE;
			}
		}
		
	
		m_strAddress = m_pSub1->m_stcAddressDisplay.GetNormalText();

		CMkCommand pCmd(m_pMkDb, "edit_customer_new_2011_16"); 
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCNo);
		pCmd.AddParameter(typeString, typeInput, m_pSub1->m_strUserID.GetLength(), m_pSub1->m_strUserID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCustomerTable);
		pCmd.AddParameter(typeString, typeInput, m_pSub1->m_strCompany.GetLength(), m_pSub1->m_strCompany);
		pCmd.AddParameter(typeString, typeInput, m_pSub1->m_strDepart.GetLength(),m_pSub1-> m_strDepart);
		pCmd.AddParameter(typeString, typeInput, m_pSub1->m_strName.GetLength(), m_pSub1->m_strName);
		pCmd.AddParameter(typeString, typeInput, m_pSub1->m_strDisplayDong.GetLength(), m_pSub1->m_strDisplayDong);
		pCmd.AddParameter(typeString, typeInput, m_pSub1->m_strLocation.GetLength(), m_pSub1->m_strLocation);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_pSub1->GetCreditType());
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), atol(m_pSub2->m_strDiscount));
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 0);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			(int)m_pSub2->m_cmbAllocGroup.GetItemData(m_pSub2->m_cmbAllocGroup.GetCurSel()));
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), atol(m_pSub2->m_strCoupon));
		pCmd.AddParameter(typeString, typeInput, m_pSub1->m_strMemo.GetLength(), m_pSub1->m_strMemo);
		pCmd.AddParameter(typeString, typeInput, m_pSub1->m_strRiderMemo.GetLength(), m_pSub1->m_strRiderMemo);
		pCmd.AddParameter(typeString, typeInput, m_pSub2->m_strEMail.GetLength(), m_pSub2->m_strEMail);
		pCmd.AddParameter(typeString, typeInput, m_strAddress.GetLength(), m_strAddress);
		pCmd.AddParameter(m_nDongID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nPosX);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nPosY);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_pSub2->m_nSendStateChangeSMS);
		pCmd.AddParameter(typeBool, typeInput, sizeof(long), m_pSub2->m_bPreventPosUpdate);
		pCmd.AddParameter(typeBool, typeInput, sizeof(long), 0);
		pCmd.AddParameter(max(0, m_pSub2->m_cmbCustomerGrade.GetCurSel()));
		pCmd.AddParameter(m_pSub2->m_bUseHomepage);
		pCmd.AddParameter(m_pSub2->m_strLoginID);
		pCmd.AddParameter(m_pSub2->m_strLoginPW);
		pCmd.AddParameter(max(0, m_pSub2->m_cmbPriceGrade.GetCurSel()));
		pCmd.AddParameter(atol(m_pSub2->m_strMileage));
		pCmd.AddParameter(max(0, m_pSub2->m_cmbMileage.GetCurSel()));
		pCmd.AddParameter(max(0, m_pSub2->m_cmbDiscount.GetCurSel()));
		pCmd.AddParameter(max(0, m_pSub2->m_cmbCoupon.GetCurSel()));

		//if(m_dtPRDate < COleDateTime(2000, 1, 1, 0, 0, 0))
		//	m_dtPRDate = COleDateTime(2000, 1, 1, 0, 0, 0);
		pCmd.AddParameter(COleDateTime(1999,1,1,0,0,0));

		pCmd.AddParameter(m_nMainAddressID);
		pCmd.AddParameter(m_pSub1->m_strAddrTitle);
		pCmd.AddParameter(m_pSub2->m_chkICMapDisplayType.GetCheck());
		pCmd.AddParameter(m_ci.m_nCompanyCode);
		pCmd.AddParameter(m_ci.m_strName);
		pCmd.AddParameter(m_pSub2->m_nSalesCompany);
		pCmd.AddParameter(m_pSub2->m_nSalesWNo);
		pCmd.AddParameter(m_pSub2->m_dtSalesTime);
		pCmd.AddParameter(m_nFirstTelID);
		pCmd.AddParameter(m_nSecondTelID);

		CXTPGridRecord *pRecord = (CXTPGridRecord*)m_List.GetFirstSelectedRecord();
		ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_List.GetItemData(pRecord);
		long nCustomerColor = m_pSub1->m_edtCompany.GetUserTextColor(), nMemoColor = m_pSub1->m_edtMemo.GetUserTextColor();
		pCmd.AddParameter(pc->strName);
		pCmd.AddParameter(pc->strDepart);
		pCmd.AddParameter(::GetRemoveDDDNumber(strPhone1));
		pCmd.AddParameter(::GetRemoveDDDNumber(strPhone2));
		pCmd.AddParameter(::GetRemoveDDDNumber(strPhone3));
		pCmd.AddParameter(m_pSub1->m_bNotAutoShareOrder);
		pCmd.AddParameter(m_pSub2->m_strFax);
		pCmd.AddParameter(nDiscountRange);
		pCmd.AddParameter(m_pSub2->m_bDiscountApplyOnlyCredit);
		pCmd.AddParameter(nCustomerColor);
		pCmd.AddParameter(nMemoColor);
		pCmd.AddParameter(m_pSub1->m_chkPopupCustomerDlg.GetCheck());
		pCmd.AddParameter(m_pSub1->m_chkShowPhoneType.GetCheck());

		pCmd.AddParameter(m_pSub2->m_bOnlinePopup);
		pCmd.AddParameter(::GetLongFromEdit(&m_pSub2->m_edtOnlinePopupCharge));
		pCmd.AddParameter(m_ui.nCompany);
		pCmd.AddParameter(m_ui.nWNo);
		pCmd.AddParameter(m_ui.strName);

		if(!pCmd.Execute()) return FALSE;
		//AddPhoneNumber(strPhone1, strPhone2, TRUE);

		m_pSub3->UpdatePBizInfo();

		m_strLastTel = ::GetRemoveDDDNumber(::GetRemoveDDDNumber(strPhone1));
		InitOneList();
		m_cus.GetNewCustomer();
		//RefreshTelList(m_nTelID);

		return TRUE; 
	}

	return FALSE;
}

void CCustomerDlg::InitOneList()
{
	int nItem = 0;
	CString strGNo = "";
	GetCustomerInfo(nItem, strGNo, 0);
	m_List.Populate();
}

void CCustomerDlg::OnBnClickedDelBtn()
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) return; 
	if(pRows->GetCount() == ZERO) return;

	CXTPGridRecord *pRecord = (CXTPGridRecord*)pRows->GetAt(ZERO)->GetRecord();

	if(pRecord == NULL)
		return;

	ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_List.GetItemData(pRecord);
	
	if(pc->bMain == FALSE)
	{
		MessageBox("대표번호만 삭제 하실 수 있습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	if(pc->bDelete == TRUE)
	{ 
		MessageBox("이미 삭제된 고객입니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	//if(IsCustomerHasOrder(m_nCNo) == TRUE)
	//{
	//	MessageBox("접수 내역이 있는 고객을 삭제 하 실수 없습니다", "확인", MB_ICONINFORMATION);
	//	return;
	//}

	if(MessageBox("해당 고객을 정말 삭제하시겠습니까?\r\n종속된 모든 번호가 삭제됩니다", 
		"확인", MB_YESNO | MB_ICONINFORMATION) == IDYES)
	{

		//CWaitCursor wait;
		UpdateData(TRUE);
		CMkCommand pCmd(m_pMkDb, "delete_customer_1");
		pCmd.AddParameter(m_nCNo);
		pCmd.AddParameter(m_nCustomerTable);
		pCmd.AddParameter(m_ui.nWNo);
		pCmd.AddParameter(m_ui.nCompany);

		CString strEtc = "고객창 삭제";
		pCmd.AddParameter(strEtc);

		pCmd.Execute();
		InitList();
		m_cus.RefreshDeleteCustomer();
	}
}

void CCustomerDlg::OnBnClickedSearchBtn()
{
	UINT nType;

	UpdateData(TRUE);
	m_edtData.GetWindowText(m_strData);

	if(m_strData.IsEmpty()) return;
	if(!CRcpDlg::MakeSearchQuery(m_strData, m_strKeyword, &nType)) return;
	m_nSearchType = nType;
	InitList();		
}

void CCustomerDlg::OnBnClickedOk()
{
	m_pSub1->UpdateData(TRUE);
	m_pSub2->UpdateData(TRUE);
	UpdateData(TRUE);

	m_bOnOk = TRUE;
	if(m_bDirty)
	{
		if(!EditCustomer())
			return;
	}

	if(GetCurBranchInfo()->bUseChargeDong && m_nDongID <= 0)
	{
		MessageBox("동기반배차방식에서는, 주소에서 반드시 동을 선택하셔야 합니다.", 
			"확인", 
			MB_ICONEXCLAMATION);
		return;
	}

	CString strCouponCharge, sDiscountRangeCharge;
	m_nAllocGroup = (long)m_pSub2->m_cmbAllocGroup.GetItemData(m_pSub2->m_cmbAllocGroup.GetCurSel());
	m_nCouponCharge = atol(m_pSub2->m_strCoupon);
	m_nPriceGrade = m_pSub2->m_cmbPriceGrade.GetCurSel();
	m_nDiscountType = m_pSub2->m_cmbDiscount.GetCurSel();
	m_pSub2->m_edtDiscountRange.GetWindowText(sDiscountRangeCharge);

	if(m_pRcpDlg)
	{
		m_pRcpDlg->m_nDiscountRange = GetMyUnNumberFormat(sDiscountRangeCharge);
		m_pParent->SearchCustomerCNo(m_nCNo, TRUE, TRUE, m_nTelID);
		m_pRcpDlg->GotoNextFocus(m_pParent->m_nPlaceType);
		LU->DestorySearchPoiDlg();
	}

	OnOK();
}

void CCustomerDlg::OnOK()
{
	m_List.SaveReportOrder("CCustomerDlg", "m_List");

	if(m_bModalMode)
		CMyDialog::OnOK();
	else
		ShowWindow(FALSE);
}

void CCustomerDlg::OnCancel()
{
	m_List.SaveReportOrder("CCustomerDlg", "m_List");
	//OnBnClickedOk(); //고객정보 수정후 확인을 누르지 않을경우 접수창에 적용 안됨.

	if(m_bModalMode)
		CMyDialog::OnCancel();
	else
		ShowWindow(FALSE);	
}

LONG CCustomerDlg::OnFocusOnSearchEvent(WPARAM wParam, LPARAM lParam)
{
	m_edtData.SetFocus();
	return 0;
}

BOOL CCustomerDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{	
		if(pMsg->hwnd == m_edtData.GetSafeHwnd()) {
			if(m_edtData.GetWindowTextLength() <= 0)
				OnBnClickedOk();
			else
			{
				OnBnClickedSearchBtn();
				m_edtData.SetFocus();
			}
			return TRUE;
		}
		/*
		else if(pMsg->hwnd == m_cmbAllocGroup.GetSafeHwnd() ||
			::GetParent(pMsg->hwnd) == m_cmbAllocGroup.GetSafeHwnd()) {
				EditCustomer();
				return TRUE;
			}
		else if(pMsg->hwnd == m_edtTelAdd.GetSafeHwnd()) {
			OnBnClickedTelAddBtn();
			return TRUE;
		}
		*/
	}

	if(pMsg->wParam == VK_DOWN && pMsg->hwnd == m_edtData.GetSafeHwnd())
	{
		m_List.SetFocus();

		if(m_List.GetRows()->GetCount() > 0)
		{
			CXTPGridRows *pRows = m_List.GetRows();
			CXTPGridRow *pRow = pRows->GetAt(0);
			m_List.GetSelectedRows()->Select(pRow);
			OnReportItemChange(NULL, NULL);
		}

		return TRUE;
	}

	if(pMsg->wParam == VK_UP && 
		pMsg->message == WM_KEYDOWN &&
		pMsg->hwnd == m_List.GetSafeHwnd()	)
	{  
		if(m_List.GetNextItem(-1, LVNI_SELECTED) == 0)
		{			
			m_edtData.SetFocus();
			m_List.GetSelectedRows()->Select(NULL);
			return TRUE;
		}
	}

	if(pMsg->message == WM_LBUTTONUP )
	{
		if(m_bDragMode)  
		{
			//CRect rect;
			//m_List.GetWindowRect(&rect);
 
			CPoint pt;
			::GetCursorPos(&pt);

			//if(!SumCustomer(pt))
			//	MessageBox("고객이 선택되지 않았습니다", "확인", MB_ICONINFORMATION);
			long nStartPoint , nNowPoint = pt.y, nDistance = 0;
			nStartPoint = (m_DragStartPoint.y  < 0) ? m_DragStartPoint.y * -1 : m_DragStartPoint.y;
			nNowPoint = (nNowPoint < 0 ) ? nNowPoint * -1 : nNowPoint;
			nDistance = nStartPoint - nNowPoint;
			nDistance = nDistance < 0 ? nDistance * -1 : nDistance;

			if(nDistance > 8 && m_DragStartPoint.x > 0 && m_DragStartPoint.y > 0)
			{
				SumCustomer(pt);
			}
			else
			{
				SetCursor(m_hcArrow);
				m_bDragMode = FALSE; //순서에 주의 할것 - 참고 OnLButtonUp에서도 m_bRefreshOK = TRUE를 설정한다.
				m_bClicking = FALSE;
				::ReleaseCapture();
				return FALSE;
			}
			m_DragStartPoint.x = m_DragStartPoint.y = 0;


			return TRUE;
		}
		else
		{
			m_bClicking = FALSE; 
			m_bDragMode = FALSE;

			return CMyDialog::PreTranslateMessage(pMsg); 
		}
	}

	if(pMsg->message == WM_LBUTTONDOWN && pMsg->hwnd == m_List.GetSafeHwnd())
	{
		m_DragStartPoint = pMsg->pt;
		m_bClicking = TRUE;
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}



void CCustomerDlg::OnEnChangeDongEdit()
{
	m_bDirty = TRUE;
}

void CCustomerDlg::OnCbnSelchangeGroupCombo()
{
	m_bDirty = TRUE;
}



void CCustomerDlg::OnTimer(UINT nIDEvent)
{
	if(1 == nIDEvent )
	{ 
		if(TRUE == IsWindowVisible())
		{
			KillTimer(nIDEvent);
			InitDialog();
		}
		return;
	}
	else if(TIMER_TEL_LIST == nIDEvent)
	{
		KillTimer(nIDEvent);

		if(m_nCNo != 0) 
		{
			if(m_bDoNotRefresh == TRUE)
			{
				m_bDoNotRefresh = FALSE;
				return;
			}

			RefreshTelList();
		}
	}

	CMyDialog::OnTimer(nIDEvent);
}


void CCustomerDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedOk();
	*pResult = 0;
}

void CCustomerDlg::OnNMDblclkAddressList(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_lstAddress.ShowWindow(FALSE);
	ShowControl(TRUE);
}

void CCustomerDlg::OnNMlclkAddressList(NMHDR *pNMHDR, LRESULT *pResult)
{
	CXTPGridSelectedRows *pRows = m_lstAddress.GetSelectedRows();

	if(pRows == NULL)
		return;
	else if(pRows->GetCount() == ZERO)
		return;

	ST_ADDRESS *st = (ST_ADDRESS*)m_lstAddress.GetItemData(pRows->GetAt(0)->GetRecord());

	m_nMainAddressID = st->nID;
	m_pSub1->m_strLocation = st->strLocation;
	//m_strAddressDetail = st->sAddress;
	m_nDongID = st->nDongID;
	//m_strAddress = m_poiNew.GetPOI(st->nDongID)->GetRegionName() + " " + m_strAddressDetail;
	m_nPosX = st->nPosX;
	m_nPosY = st->nPosY;
	m_pSub1->m_strDisplayDong = st->strDong;

	if(m_nDongID > 0)
		m_pSub1->m_strAddrDong = m_poiNew.GetDongPOI(m_nDongID)->GetDong();
	else 
		m_pSub1->m_strAddrDong = "";

	m_pSub1->m_strAddrTitle = st->strAddressTitle;

	UpdateData(FALSE);
	//m_lstAddress.ShowWindow(FALSE);
	//ShowControl(TRUE);

	if(st->strAddressTitle != "대표주소")
		m_pSub1->m_editAddrTitle.EnableWindow(TRUE);
	else
		m_pSub1->m_editAddrTitle.EnableWindow(FALSE);



	*pResult = 0;
}

void CCustomerDlg::OnReportBeginDrag(NMHDR * pNotifyStruct, LRESULT * result)
{
	if(m_bClicking)
	{
		m_bDragMode = TRUE;
		m_ptDrag.x = -1;
		m_ptDrag.y = -1;
		SetCursor( m_hcMoveHold );
		SetCapture();

	}

}

void CCustomerDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if(TRUE == m_bDragMode)
	{
		SetCursor( m_hcMoveHold );

		if(m_ptDrag.x == -1)
		{
			m_ptDrag.x = point.x;
			m_ptDrag.y = point.y;
		}

		double lDistance = (m_ptDrag.x-point.x)*(m_ptDrag.x-point.x)  + (m_ptDrag.y-point.y)*(m_ptDrag.y-point.y);

		if( sqrt( lDistance  ) > 250.0)
		{
			SetCursor(m_hcArrow);
			m_bDragMode = FALSE; //순서에 주의 할것 - 참고 OnLButtonUp에서도 m_bRefreshOK = TRUE를 설정한다.
			m_bClicking = FALSE;
			::ReleaseCapture();
		}
	}

	CMyDialog::OnMouseMove(nFlags, point);
}

BOOL CCustomerDlg::SumCustomer(CPoint pt)
{
	if (m_bDragMode) // In Drag&Drop mode ?
	{
		m_bDragMode = FALSE;
		m_bClicking = FALSE;

		//UINT uFlags;
		m_List.ScreenToClient(&pt);
		//int nHoverItem = m_List.HitTest(pt, &uFlags);
		CXTPGridRow *pRow = m_List.HitTest(pt);

		if(pRow == NULL)
		{
			MessageBox("고객이 선택되지 않았습니다", "확인", MB_ICONINFORMATION);			
			return FALSE;
		}

		int nHoverItem = pRow->GetIndex();
		int nSelItem = m_List.GetNextItem(-1, LVNI_SELECTED);

		char buffer[10];

		//if(nHoverItem != nSelItem) 
		//{

		ST_CUSTOMER_INFO *SrcPc = (ST_CUSTOMER_INFO*)m_List.GetItemData(nSelItem);
		ST_CUSTOMER_INFO *DstCNo = (ST_CUSTOMER_INFO*)m_List.GetItemData(nHoverItem);

		if(SrcPc->nCNo == DstCNo->nCNo)
		{
			MessageBox("합치려는 고객이 같습니다", "확인", MB_ICONINFORMATION);
			return FALSE;
		}

		if(SrcPc->bMain == FALSE || 
			DstCNo->bMain == FALSE )
		{ 
			MessageBox("대표전화번호만 통합하실 수 있습니다", "확인", MB_ICONINFORMATION);
			return FALSE;
		}

		CSumCnoDlg dlg;
		dlg.m_strCNo1 = CString("고객번호 ") + itoa(SrcPc->nID, buffer, 10);
		dlg.m_strCNo2 = CString("고객번호 ") + itoa(DstCNo->nID, buffer, 10);
		dlg.m_strCNo3 =CString("고객번호 ") +  itoa(DstCNo->nID, buffer, 10);
		if(IDOK == dlg.DoModal())
		{
			//CWaitCursor wait;		
			CString strDeleteEtc = "고객통합[고객창] 삭제";
			CMkCommand pCmd(m_pMkDb, "Integrated_customer_alone_1");
			pCmd.AddParameter(m_nCustomerTable);		//nCompany
			pCmd.AddParameter(SrcPc->nCNo);
			pCmd.AddParameter(DstCNo->nCNo);
			pCmd.AddParameter(m_ui.nWNo);
			pCmd.AddParameter(m_ui.nCompany);						
			pCmd.AddParameter(strDeleteEtc);

			pCmd.Execute();

			InitOneList();
			//m_List.GetRecords()->RemoveAt(nSelItem);
			//m_List.Populate();
			m_cus.GetNewCustomer();

			return TRUE;
		}
		//}
	}

	return FALSE;
}


HBRUSH CCustomerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	return hbr;
}


void CCustomerDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CCustomerDlg::OnBnClickedOkBtn()
{
	OnBnClickedOk();
}


void CCustomerDlg::ChangeGroup( long nOldGNo, long nNewGNo, BOOL bChange, CXTPGridRecord *pRecord)
{

	if(pRecord )
	{
		ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO *)m_List.GetItemData(pRecord);
		if(pc)
		{
			
			for(int i = 0; i < m_List.GetColumns()->GetCount(); i++)
			{
				CXTPGridColumn *pCol = m_List.GetColumns()->GetAt(i);
				if(pCol)
				{
					if(pCol->GetCaption().Compare("그룹명") == 0 )
					{						
						pc->nGNo = bChange ?  nNewGNo : 0;

						CString strChangeGroupName;
						if(bChange)
							strChangeGroupName.Format("%s", m_cg.GetGroupData(nNewGNo)->strGroupName);
						else
							strChangeGroupName = "";
								
						m_List.SetItemText(pRecord, i, strChangeGroupName);
						m_List.Populate();
						return;
					}
				}
			}
			


		}
	}


}



void CCustomerDlg::GetCurInfo(ST_CUSTOMER_INFO *pc)
{
	//UpdateData();
	char buffer[20];

	m_pCusInfo = pc;
	m_nCNo = pc->nCNo;
	m_nID = pc->nID;
	m_nGNo = pc->nGNo;
	m_pSub1->m_strID = ltoa(pc->nID, buffer, 10);
	m_pSub1->m_strCompany = pc->strCompany;
	m_pSub1->m_strDepart = pc->strDepart;
	m_pSub1->m_strName = pc->strName;
	//m_pSub1->m_strTel = GetDashPhoneNumber(pc->strTel1);
	m_pSub1->m_strDisplayDong = pc->strDong;
	m_pSub1->m_strLocation = pc->strLocation;
	//m_pSub1->m_bCredit = pc->bCredit != 0 ? TRUE : FALSE;
	m_pSub1->SetCreditCheck(pc->bCredit);
	m_pSub2->m_strDiscount.Format("%d", pc->nDiscount);
	m_pSub2->m_cmbAllocGroup.SetCurSel(pc->nAllocGroup);
	m_pSub2->m_strCoupon.Format("%d", pc->nCouponCharge);
	//m_pSub1->m_strMobile = GetDashPhoneNumber(pc->strMobile);
	m_pSub1->m_strMemo = pc->strMemo;
	m_pSub1->m_strCustomerType = pc->nCustomerType == 0 ? "거래처" : "일반고객";
	m_pSub1->m_strFirstUse = pc->dtRegister.Format("%y-%m-%d %H:%M");
	m_pSub1->m_strLastUse = pc->dtLastUse.Format("%y-%m-%d %H:%M");
	m_pSub1->m_strUseCount = ltoa(pc->nUseCount, buffer, 10);
	m_pSub1->m_strCancelCount = ltoa(pc->nCancelCount, buffer, 10);
	m_pSub1->m_strRiderMemo = pc->strRiderMemo;
	m_pSub1->m_strAddress = pc->strAddress;
	m_nDongID = pc->nDongID;
	//m_strAddress = m_poiNew.GetPOI(pc->nDongID)->GetRegionName() + " " + m_strAddressDetail;
	m_pSub2->m_strEMail = pc->strEMail;
	m_nPosX = pc->nPosX;
	m_nPosY = pc->nPosY;
	
	m_pSub2->m_nSalesCompany = pc->nSalesCompany;
	m_pSub2->m_nSalesWNo = pc->nSalesWNo;
	m_pSub2->m_dtSalesTime = pc->dtSales;
	

	if(m_nDongID > 0)
		m_pSub1->m_strAddrDong = m_poiNew.GetPOI(pc->nDongID)->GetDong();
	else 
		m_pSub1->m_strAddrDong = "";

	m_nUseCount = pc->nUseCount;
	m_nCancelCount = pc->nCancelCount;
	m_dtRegister = pc->dtRegister;
	m_dtLast = pc->dtLastUse;

	m_nCreditCount = pc->nCreditCount;
	m_nCreditCharge = pc->nCreditCharge;
	m_pSub1->m_strUserID = pc->strUserID;
	m_pSub1->m_bNotAutoShareOrder = pc->bNotAutoShareOrder;
	m_pSub2->m_nSendStateChangeSMS = pc->nSendStateChangeSMS;
	m_pSub2->m_bPreventPosUpdate = pc->bPreventPosUpdate ? TRUE : FALSE;
	m_pSub2->m_strLoginID = pc->strLoginID;
	m_pSub2->m_strLoginPW = pc->strLoginPW;
	m_pSub2->m_bUseHomepage = pc->bUseHomepage;
	m_pSub2->m_cmbCustomerGrade.SetCurSel(pc->nCustomerGrade);
	m_pSub2->m_cmbPriceGrade.SetCurSel(pc->nPriceGrade);  
	m_pSub2->SetCompanyCharge(pc->nMemCNo);
	m_pSub2->m_cmbMileage.SetCurSel(pc->nMileageType);
	m_nMileage = pc->nMileageValue;
	m_nMileageType = pc->nMileageType;
	m_nMileageBalance = pc->nMileageBalance;
	m_nMainAddressID = pc->nMainAddressID;
	m_nPcMainAddressID = pc->nMainAddressID;
	m_pSub2->m_nICMapDisplayType = pc->nICMapDisplayType;
	m_pSub2->m_strFax = pc->strFax;
	m_pSub2->m_bDiscountApplyOnlyCredit = pc->bDiscountApplyOnlyCredit;
	m_bHasDetailPos = pc->bHasDetailPos;

	m_pSub1->m_strAddrTitle = "대표주소";
	if(m_nMileageType <= 2)  // 개별 마일리지 or 적용안함.
		m_pSub2->m_cmbMileage.SetCurSel(m_nMileageType);
	else
		m_pSub2->m_cmbMileage.SetCurSel(3);  // 10 마일리지 개별적용 안함


	if(m_nMileageType == 0 || m_nMileageType == 10)
	{
		m_pSub2->m_edtMileage.EnableWindow(TRUE);
		m_pSub2->m_strMileage = "0";
		m_pSub2->m_edtMileage.SetWindowText(m_pSub2->m_strMileage);
	}
	else
	{
		m_pSub2->m_strMileage = GetMyNumberFormat(m_nMileage);
		m_pSub2->m_edtMileage.SetWindowText(m_pSub2->m_strMileage);
		m_pSub2->m_edtMileage.EnableWindow(FALSE);
	}

	m_pSub1->m_chkShowPhoneType.SetCheck(pc->nShowPhoneType);
	m_pSub1->m_chkPopupCustomerDlg.SetCheck(pc->bPopupCustomerDlg);

	m_pSub2->m_cmbDiscount.SetCurSel(pc->nDiscountType);
	m_pSub2->m_edtDiscount.SetWindowText(GetMyNumberFormat(pc->nDiscount));
	m_pSub2->m_edtDiscountRange.SetWindowText(GetMyNumberFormat(pc->nDiscountRange));

	m_pSub2->m_cmbCoupon.SetCurSel(pc->nCouponType);

	ST_CUSTOMER_GROUP_INFOMATION *info = NULL;
	info = m_cg.GetGroupData(pc->nGNo);
	if(info != NULL)
		m_pSub1->m_strGroupName = pc->nGNo > 0 ? m_cg.GetGroupData(pc->nGNo)->strTotalName : "N/A";		 
	else
		m_pSub1->m_strGroupName = "N/A";

	//m_strGroupName = pc->nGNo > 0 ? m_cg.GetGroupData(pc->nGNo)->sTotalName : "N/A";

	m_pSub2->UpdateData(FALSE); 
	m_pSub2->SelChangeOption();
 	SetAddressInfo();
	m_pPlace->SetData(m_nDongID, m_nPosX, m_nPosY, m_bHasDetailPos, m_pSub1->m_strAddress);

	m_nTelID =pc->nTelID; 

	//m_pSub1->m_edtCompany.SetUserTextColor(pc->nCustomerColor);
	m_pSub1->m_edtMemo.SetUserTextColor(pc->nMemoColor);

	m_nLastCNo = pc->nCNo;
	m_strLastTel = pc->strMobile;

	m_pSub2->m_bOnlinePopup = pc->bOnlinePopup;
	m_pSub2->m_strOnlinePopupCharge = ::GetMyNumberFormat(pc->nOnlinePopupCharge);

	m_pSub1->ShowUseCount();
}

void CCustomerDlg::GetCurDongInfo(CPOIUnit *pc)
{
	CString strDongName, strGugunName;
	CString strDisplayName;

	strDisplayName = pc->GetRegionName();
	strDongName = pc->GetDong();
	strGugunName = pc->GetGugun();

	m_pCusInfo = NULL;
	m_nCNo = 0;
	m_nGNo = 0;
	m_pSub1->m_strID = "";
	m_pSub1->m_strCompany = pc->GetFullName();
	m_pSub1->m_strDepart = "";
	m_pSub1->m_strName = "";
	m_pSub1->m_strTel = "";
	m_pSub1->m_strDisplayDong = strDongName;
	m_pSub1->m_strLocation = "";
	m_pSub1->m_bCredit = FALSE;
	m_pSub2->m_cmbAllocGroup.SetCurSel(0);
	m_pSub1->m_strMobile = "";
	m_pSub1->m_strMemo = "";
	m_pSub1->m_strCustomerType = "지명";
	m_pSub1->m_strFirstUse = "";
	m_pSub1->m_strLastUse = "";
	m_pSub1->m_strUseCount = "";
	m_pSub1->m_strRiderMemo = "";
	m_pSub1->m_strAddress = "";
	m_pSub1->m_strAddress = strDisplayName;
	m_pSub2->m_strEMail = "";
	m_nPosX = pc->GetPosX();
	m_nPosY = pc->GetPosY();
	m_pSub1->m_strGroupName = "";
	m_nDongID = pc->GetDongID();
	//m_stcBaseDong.SetNotPoiDong(FALSE);
}

void CCustomerDlg::OnEnChangeDisplayDongEdit()
{
	m_bDirty = TRUE;
}

void CCustomerDlg::OnBnClickedCoporationBtn()
{
	CCorporationDlg2 dlg;
	BOOL bPartView = FALSE;
	//CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();

	int nItem = m_List.GetSelectedItem();
	if(nItem < 0)
	{
		dlg.m_bPartView = FALSE;
	}
	else if(m_List.GetSelectedRows()->GetCount() > 0)
	{

		ST_CUSTOMER_INFO *pCustomer = (ST_CUSTOMER_INFO *)m_List.GetItemData(nItem);
		if(pCustomer->nGNo <= 0)
			dlg.m_bPartView = FALSE;
		else
		{
			dlg.m_bPartView = TRUE;
			dlg.SetGNo(pCustomer->nGNo);
		}

	}

	dlg.DoModal();
	if(dlg.m_bReceipt)
	{
		int nItem = 0;
		m_nCNo = dlg.m_nReceiptCNo;
		CString strGNo = "";
		GetCustomerInfo(nItem, strGNo, dlg.m_bReceipt);
		OnBnClickedOk();

	}	
}

void CCustomerDlg::OnEnChangeDataEdit()
{
	m_edtData.GetWindowText(m_strData);
	SearchListDate(m_strData);
}

void CCustomerDlg::SearchListDate(CString strSearchData)
{
	CXTPGridRecords *pRecords = m_List.GetRecords();
	CXTPGridColumn *pColumn = NULL;

	CString strCompany, strDepart, strName, strUserID, strTel1, strDong, strLocation;

	m_List.m_strSearchData = strSearchData;

	
	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord* pRecord = (CXTPGridRecord*)pRecords->GetAt(i);

		if(pRecord->HasChildren())
		{
			CXTPGridRecords *pRecords1 = pRecord->GetChilds();

			BOOL bChildFind = FALSE;

			for(int j=0; j<pRecords1->GetCount(); j++)
			{
				CXTPGridRecord* pRecord1 = (CXTPGridRecord*)pRecords1->GetAt(j);
				CString str0 = pRecord1->GetItem(0)->GetCaption(NULL);
				CString str1 = pRecord1->GetItem(1)->GetCaption(NULL);
				CString str2 = pRecord1->GetItem(2)->GetCaption(NULL);
				CString str3 = pRecord1->GetItem(3)->GetCaption(NULL);
				CString str4 = pRecord1->GetItem(4)->GetCaption(NULL);
				CString str5 = pRecord1->GetItem(5)->GetCaption(NULL);
				CString str6 = pRecord1->GetItem(6)->GetCaption(NULL);
				CString str8 = pRecord1->GetItem(8)->GetCaption(NULL);


				if(str0.Find(strSearchData) >= 0 ||
					str1.Find(strSearchData) >= 0 ||
					str2.Find(strSearchData) >= 0 ||
					str3.Find(strSearchData) >= 0 ||
					str4.Find(strSearchData) >= 0 ||
					str5.Find(strSearchData) >= 0 ||
					str6.Find(strSearchData) >= 0 ||
					str8.Find(strSearchData) >= 0)
				{
					pRecord1->SetVisible(TRUE);
					bChildFind = TRUE;
				}
				else
					pRecord1->SetVisible(FALSE);

				pRecord->SetVisible(bChildFind);
			}
		}
		else
		{
			CString str0 = pRecord->GetItem(0)->GetCaption(NULL);
			CString str1 = pRecord->GetItem(1)->GetCaption(NULL);
			CString str2 = pRecord->GetItem(2)->GetCaption(NULL);
			CString str3 = pRecord->GetItem(3)->GetCaption(NULL);
			CString str4 = pRecord->GetItem(4)->GetCaption(NULL);
			CString str5 = pRecord->GetItem(5)->GetCaption(NULL);
			CString str6 = pRecord->GetItem(6)->GetCaption(NULL);
			CString str8 = pRecord->GetItem(8)->GetCaption(NULL);

	
			if(str0.Find(strSearchData) >= 0 ||
				str1.Find(strSearchData) >= 0 ||
				str2.Find(strSearchData) >= 0 ||
				str3.Find(strSearchData) >= 0 ||
				str4.Find(strSearchData) >= 0 ||
				str5.Find(strSearchData) >= 0 ||
				str6.Find(strSearchData) >= 0 ||
				str8.Find(strSearchData) >= 0)
			{
				pRecord->SetVisible(TRUE);
			}
			else
				pRecord->SetVisible(FALSE);		
		}
	}

	/*
	for(int i=0; i<m_List.GetRecords()->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		strCompany = ((CXTPGridRecordItemText*)m_List.GetRecords()->GetAt(i)->GetItem(1))->GetCaption(pColumn);
		strDepart = ((CXTPGridRecordItemText*)m_List.GetRecords()->GetAt(i)->GetItem(2))->GetCaption(pColumn);
		strName = ((CXTPGridRecordItemText*)m_List.GetRecords()->GetAt(i)->GetItem(3))->GetCaption(pColumn);
		strUserID = ((CXTPGridRecordItemText*)m_List.GetRecords()->GetAt(i)->GetItem(4))->GetCaption(pColumn);
		strTel1 = ((CXTPGridRecordItemText*)m_List.GetRecords()->GetAt(i)->GetItem(5))->GetCaption(pColumn);
		strDong = ((CXTPGridRecordItemText*)m_List.GetRecords()->GetAt(i)->GetItem(6))->GetCaption(pColumn);
		strLocation = ((CXTPGridRecordItemText*)m_List.GetRecords()->GetAt(i)->GetItem(8))->GetCaption(pColumn);

		if((strCompany.Find(strSearchData) >= 0) ||
			(strDepart.Find(strSearchData) >= 0) ||
			(strName.Find(strSearchData) >= 0) ||
			(strUserID.Find(strSearchData) >= 0) ||
			(strTel1.Find(strSearchData) >= 0) ||
			(strDong.Find(strSearchData) >= 0) ||
			(strLocation.Find(strSearchData) >= 0) )
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}
	*/

	m_List.Populate();
}

void CCustomerDlg::DeleteListAllItems()
{
	for(int nItem = 0; nItem < m_List.GetRecords()->GetCount(); nItem++)
	{
		CXTPGridRecord *pRecord = m_List.GetRecords()->GetAt(nItem);

		if(m_List.GetItemText(pRecord, 0) != "지명")
		{
			ST_CUSTOMER_INFO *pCusInfo = (ST_CUSTOMER_INFO*)m_List.GetItemData(pRecord);
			if(pCusInfo)
			{
				delete pCusInfo;
				pCusInfo = NULL;
			}
		}
	}

	m_List.DeleteAllItems();
}

BOOL CCustomerDlg::GetCustomerInfo(int &nItem, CString &sGNoSUM, int nCorporationDirectReceipt)
{
	//search_customer_new11 3, 7100, '''', 0
 
	char buffer[20];

	CString strCompany, strDepart, strName;
	CString strTel1, strDong, strLocation;
	CString strMobile, strMemo, strGroupTot;
	//long nCreditCount, nCreditCharge;
	COleDateTime dtPRDate(1900,1,1,0,0,0);
	//CString sGNoSUM = ";";

	long nLastSel = 0;
	long nLastTelID = 0;
	if(m_List.GetSelectedRows() != NULL && m_List.GetSelectedRows()->GetCount() > ZERO)
	{ 
		CXTPGridRecord *pRecord = m_List.GetSelectedRows()->GetAt(ZERO)->GetRecord();
		ST_CUSTOMER_INFO *pCusInfo = (ST_CUSTOMER_INFO*)m_List.GetItemData(pRecord);

		if(pCusInfo)
			nLastTelID = pCusInfo->nTelID;

		//nLastSel = m_List.GetSelectedRows()->GetAt(0)->GetIndex();;
	}

	if(m_nRefreshTelID > 0)
	{
		nLastTelID = m_nRefreshTelID;
		m_nRefreshTelID = 0;
	}
		
	DeleteListAllItems();

	CMkCommand pCmd(m_pMkDb, "search_customer_2011_14");
	CMkRecordset pRs(m_pMkDb);

	if(m_nSearchType == ST_CNO)
	{ 
		m_strKeyword.Format("%d", m_nCNo);	
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), ST_CNO);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCustomerTable);
		pCmd.AddParameter(typeString, typeInput, m_strKeyword.GetLength(), m_strKeyword);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_ci.m_bSearchFourNumberWithUID);
	}
	else if(nCorporationDirectReceipt > 0)   // 법인창에서 바로접수 
	{
		m_strKeyword.Format("%d", m_nCNo);	
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), ST_CNO);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCustomerTable);
		pCmd.AddParameter(typeString, typeInput, m_strKeyword.GetLength(), m_strKeyword);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_ci.m_bSearchFourNumberWithUID);
	}
	else
	{
		if(m_nSearchType == ST_COMPANY) m_nSearchType++;
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nSearchType);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCustomerTable);
		pCmd.AddParameter(typeString, typeInput, m_strKeyword.GetLength(), m_strKeyword);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_ci.m_bSearchFourNumberWithUID);
	}

	pCmd.AddParameter(m_chkShowDeleteCustomer.GetCheck());

	if(!pRs.Execute(&pCmd)) return FALSE;

	CString strPreMainTel = "";
	long nPreCNo = 0;

	//m_mapMainTel.clear();
	//m_mapSubTel.clear();

	m_mapTel.clear();

	CXTPGridRecord *pRecord = NULL;

	//g_bana_log->Print("쿼리성공11");

	while(!pRs.IsEOF())
	{	
		ST_CUSTOMER_INFO *pc = new ST_CUSTOMER_INFO;
		
		GetPcInfo(&pRs, pc, dtPRDate);
		pc->bGorupSelect = FALSE;

		if(m_pRcpDlg)
		{
			if(pc->nDiscount != m_pRcpDlg->m_nDiscountValue)
				m_pRcpDlg->SetDiscountType(pc->nGNo, pc->nDiscountType, pc->nDiscount); // pc->bCreditAfterDis 
				
			if(pc->nDiscountType != m_pRcpDlg->m_nDiscountType)
				m_pRcpDlg->SetDiscountType(pc->nGNo, pc->nDiscountType, pc->nDiscount);	// pc->bCreditAfterDis 

		}

		BOOL bMain = FALSE;

		if(pc->nCNo != nPreCNo)
		{
			pc->strTel1 = pc->strMobile; 
			bMain = TRUE;
		}
		else
			pc->strTel1 = strPreMainTel;

		ST_TEL stTel; 
		stTel.nCNo = pc->nCNo;
		stTel.strDepart = pc->strDepart;
		stTel.strManager = pc->strName;
		stTel.strTel = pc->strMobile;
		stTel.nTelID = pc->nTelID;
		stTel.nTelType = pc->nTelType;

		if((pc->nGNo > 0) && (sGNoSUM.Find((CString)itoa(pc->nGNo, buffer, 10)) == -1))
			sGNoSUM += (CString)itoa(pc->nGNo, buffer, 10) + ";";

		BOOL bInsertRow = TRUE;
		
		if(bMain == TRUE)
		{
			pRecord = m_List.AddRecord(new CXTPGridCustomer(TRUE, pc));
			pRecord->SetExpanded(TRUE);
			//m_List.SetItemNoSort(pRecord, FALSE);
		}
			//pRecord = m_List.InsertItem(nItem, ltoa(pc->nID, buffer, 10));
		else
		{
			if(IsDataHas(&stTel) == TRUE)
			{
				//pRecord->GetChilds()->Add(new CXTPGridCustomer(TRUE, pc);
				bInsertRow = FALSE;
			}
			else
			{
				CXTPGridRecord *pRecord1 =	pRecord->GetChilds()->Add(new CXTPGridCustomer(FALSE, pc));
				m_List.SetItemNoSort(pRecord1, FALSE);
				//pRecord = m_List.GetChilds()->Add(new CXTPGridCustomer(TRUE, pc);
				//pRecord = m_List.InsertItem(nItem, "");
			}
		}

		m_mapTel.insert(MAP_TEL::value_type(m_mapTel.size(), stTel));

		//if(nLastTelID == pc->nTelID)
		//	nLastSel = nItem;

		if(bInsertRow == FALSE)
		{			
			pRs.MoveNext();
			strPreMainTel = pc->strTel1;
			nPreCNo= pc->nCNo;
			continue;
		}		

		pRs.MoveNext();
		strPreMainTel = pc->strTel1;
		nPreCNo= pc->nCNo;
		nItem++;		
	}

	//g_bana_log->Print("쿼리성공12");

	pRs.Close();

	m_List.Populate();
	
	if(m_List.GetItemCount() < ONE)
		return FALSE ; //choi 작업계속

	CXTPGridRows *pRows = m_List.GetRows();
	if(pRows != NULL && pRows->GetCount() > 0)
	{
		long nSelRow = 0;
		if(m_strLastTel != "" && m_nLastCNo > 0)
			nSelRow = GetLastSelRow();

		CXTPGridRow *pRow = pRows->GetAt(nSelRow);
		m_List.EnsureVisible(pRow);
		m_List.GetSelectedRows()->Select(pRow);
		m_List.SetFocusedRow(pRow);

		ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_List.GetItemData(nSelRow);
		GetCurInfo(pc);
	}
	else
		ClearCustomerDlg();
	
	//g_bana_log->Print("쿼리성공13");
	
	UpdateData(FALSE);
	m_pSub1->UpdateData(FALSE);
	m_pSub2->UpdateData(FALSE);
	//SetTimer(0, 500, NULL);

	//g_bana_log->Print("쿼리성공14");

	return TRUE;
}

long CCustomerDlg::GetLastSelRow()
{
	CXTPGridRows *pRows = m_List.GetRows();

	for(int i=ZERO; i<pRows->GetCount(); i++)
	{
		CXTPGridRow *pRow = pRows->GetAt(i);
		CXTPGridCustomer *pRecord = (CXTPGridCustomer*)pRow->GetRecord();

		if(pRecord->m_info->nCNo == m_nLastCNo &&
			pRecord->m_info->strMobile == m_strLastTel)
			return pRow->GetIndex();
	}

	return 0;
}

void CCustomerDlg::BatchUpdateGetCustomerInfo(CString strCNoList)
{
	//search_customer_new11 3, 7100, '''', 0

	char buffer[20];

	CString strCompany, strDepart, strName;
	CString strTel1, strDong, strLocation;
	CString strMobile, strMemo, strGroupTot;	
	COleDateTime dtPRDate(1900,1,1,0,0,0);
	

//search_customer_new11
	CMkCommand pCmd(m_pMkDb, "batch_update_refresh");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter(strCNoList);
	pCmd.AddParameter(m_nCustomerTable);	
	if(!pRs.Execute(&pCmd)) return ;

	while(!pRs.IsEOF())
	{	
		ST_CUSTOMER_INFO *pc = new ST_CUSTOMER_INFO;

		GetPcInfo(&pRs, pc, dtPRDate);
		pc->bGorupSelect = FALSE;
		
		CXTPGridRecord *pRecord = NULL;
		
		for(int n = 0; n < m_List.GetRecords()->GetCount(); n++)
		{
			ST_CUSTOMER_INFO *pOldCustomerInfo = (ST_CUSTOMER_INFO*)m_List.GetItemData(m_List.GetRecords()->GetAt(n));
			if(pc->nCNo == pOldCustomerInfo->nCNo)
			{
				if(pOldCustomerInfo)
					delete pOldCustomerInfo;

				pRecord = m_List.GetRecords()->GetAt(n);
				m_List.SetItemData(pRecord,(DWORD)pc);					
				
				break;
				
			}
		}
		
		if(pRecord == NULL)
		{
			MessageBox("갱신중 오류가 났습니다" , "확인", MB_ICONINFORMATION);
			 return;

		}

		CString strTotalName = "";
		ST_CUSTOMER_GROUP_INFOMATION *info = NULL;
		info = m_cg.GetGroupData(pc->nGNo);
		if(info != NULL)
			strTotalName = pc->nGNo > 0 ? m_cg.GetGroupData(pc->nGNo)->strTotalName : "";
		else
			strTotalName = "";

		CString strTemp = "";
		if(pc->bCredit == 1) strTemp = "신용";
		else if(pc->bCredit == 2) strTemp = "송금";
		else if(pc->bCredit == 3) strTemp = "카드";

		m_List.SetItemText(pRecord, 1, strTemp);
		m_List.SetItemText(pRecord, 2, pc->strCompany);
		m_List.SetItemText(pRecord, 3, pc->strDepart);
		m_List.SetItemText(pRecord, 4, pc->strName);
		m_List.SetItemText(pRecord, 5, pc->strUserID);
		m_List.SetItemText(pRecord, 6, pc->strLoginID);
		m_List.SetItemText(pRecord, 7, GetDashPhoneNumber(pc->strTel1));
		m_List.SetItemText(pRecord, 8, pc->strDong);
		m_List.SetItemText(pRecord, 9, strTotalName);
		m_List.SetItemText(pRecord, 10, pc->strLocation);
		m_List.SetItemText(pRecord, 11, ltoa(pc->nDiscount, buffer, 10));
		m_List.SetItemData(pRecord, (DWORD_PTR)pc);

		
		//if(pc->nGNo > 0)
		//	GROUP_GNO_TOT.push_back(pc->nGNo);

		//if(nItem == 0) {
		//	//m_List.SetHotItem(0);
		//	CXTPGridRows *pRows = m_List.GetRows();
		//	CXTPGridRow *pRow = pRows->GetAt(0);

		//	m_List.GetSelectedRows()->Select(pRow);
		//	m_List.SetFocus();

		//	GetCurInfo(pc);
		//	UpdateData(FALSE);
		//	SetTimer(0, 500, NULL);
		//}

		pRs.MoveNext();
		
	}

	pRs.Close();

	m_List.Populate();
}

BOOL CCustomerDlg::SearchGroupData(CString strGNo, BOOL bOneGroup)
{
	if(strGNo.IsEmpty())
		return TRUE;

	char buffer[20];
	COleDateTime dtPRDate(1900,1,1,0,0,0);
	long nPreGNo = 0;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_gno_customer_2011_2");

	if(bOneGroup)
	{
		pCmd.SetMkCommand(m_pMkDb, "select_one_gno_all_2011_3");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCustomerTable);
		pCmd.AddParameter(atoi(strGNo));
	} 
	else
	{
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCustomerTable);
		pCmd.AddParameter(strGNo);
	}

	if(!pRs.Execute(&pCmd)) return FALSE;

	DeleteGroupItem();
	long nItem = m_List.GetRecords()->GetCount();
	InsertGroupStartLine();
	CXTPGridRecord * pRecord = NULL;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		ST_CUSTOMER_INFO *pc = new ST_CUSTOMER_INFO;

		GetPcInfo(&pRs, pc, dtPRDate);
		pc->bGorupSelect = TRUE;

		CString strTotalName = "";
		ST_CUSTOMER_GROUP_INFOMATION *info = NULL;
		info = m_cg.GetGroupData(pc->nGNo);
		if(info != NULL)
			strTotalName = pc->nGNo > 0 ? m_cg.GetGroupData(pc->nGNo)->strTotalName : "";
		else
			strTotalName = "";

		if((i == 0) || (nPreGNo != pc->nGNo))
		{
			ST_CUSTOMER_INFO *pcNew = new ST_CUSTOMER_INFO;
			pcNew->nCNo = GROUP_NAME_ROW;
			pcNew->bGorupSelect = TRUE;

			pRecord = m_List.InsertItem(nItem++, 0, -1, 0);
			m_List.SetItemText(pRecord, 2, strTotalName);
			//m_List.SetItemText(pRecord, 3, pc->strDepart);
			m_List.SetItemData(pRecord, (DWORD_PTR)pcNew);
		}

		pRecord = m_List.InsertItem(nItem++, ltoa(pc->nID, buffer, 10), -1, 0);

		CString strTemp = "";
		if(pc->bCredit == 1) strTemp = "신용";
		else if(pc->bCredit == 2) strTemp = "송금";
		else if(pc->bCredit == 3) strTemp = "카드";

		m_List.SetItemText(pRecord, 1, strTemp);
		m_List.SetItemText(pRecord, 2, pc->strCompany);
		m_List.SetItemText(pRecord, 3, pc->strDepart);
		m_List.SetItemText(pRecord, 4, pc->strName);
		m_List.SetItemText(pRecord, 5, pc->strUserID);
		m_List.SetItemText(pRecord, 6, pc->strLoginID);
		m_List.SetItemText(pRecord, 7, GetDashPhoneNumber(pc->strTel1));
		m_List.SetItemText(pRecord, 8, pc->strDong);
		m_List.SetItemText(pRecord, 9, strTotalName);
		m_List.SetItemText(pRecord, 10, pc->strLocation);
		m_List.SetItemText(pRecord, 11, ltoa(pc->nDiscount, buffer, 10));
		m_List.SetItemData(pRecord, (DWORD_PTR)pc);

		nPreGNo = pc->nGNo;

		pRs.MoveNext();
	}

	m_List.Populate();	

	return TRUE;
}


void CCustomerDlg::OnBnClickedEditGroupAllBtn()
{

	if(m_bDirty)
		OnBnClickedEditBtn();

	if(m_nGNo <= 0)
	{
		MessageBox("그룹 고객이 아닙니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_nCNo <= 0)
	{
		MessageBox("고객을 선택하시기 바랍니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	CCustomerSelectChangeDlg dlg;

	if(dlg.DoModal() != IDOK)
		return;

	CMkCommand pCmd(m_pMkDb, "update_customer_for_all_group_2011_2");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);

	pCmd.AddParameter(m_nCompanyCode);
	pCmd.AddParameter(m_nCNo);
	pCmd.AddParameter(m_nGNo);
	pCmd.AddParameter(dlg.m_bCNo);
	pCmd.AddParameter(dlg.m_bCompany);
	pCmd.AddParameter(dlg.m_bDepart);
	pCmd.AddParameter(dlg.m_bManager);
	pCmd.AddParameter(dlg.m_bTel);
	pCmd.AddParameter(dlg.m_bMobile);
	pCmd.AddParameter(dlg.m_bRiderMemo);
	pCmd.AddParameter(dlg.m_bMemo);
	pCmd.AddParameter(dlg.m_bGrade);
	pCmd.AddParameter(dlg.m_bAllocGroup);
	pCmd.AddParameter(dlg.m_bDetailAddress);
	pCmd.AddParameter(dlg.m_bLocation);
	pCmd.AddParameter(dlg.m_bDisplay);
	pCmd.AddParameter(dlg.m_bCredit);
	pCmd.AddParameter(dlg.m_bSendStateChangeSms);
	pCmd.AddParameter(dlg.m_bICMapDisplayType);
	pCmd.AddParameter(dlg.m_bUseHomepage);
	pCmd.AddParameter(dlg.m_bPreventPosUpdate);
	pCmd.AddParameter(dlg.m_bPriceGrade);
	pCmd.AddParameter(dlg.m_bDiscount);
	pCmd.AddParameter(dlg.m_bCoupon);
	pCmd.AddParameter(dlg.m_bMileage);
	pCmd.AddParameter(dlg.m_bEMail);
	pCmd.AddParameter(m_nTelID);

	if(pCmd.Execute())
	{
		if(parRet->GetLong() < 0)
		{
			MessageBox("고객번호가 잘못되었습니다.\n재검색후에 재시도 바랍니다.", "확인", MB_ICONEXCLAMATION);
		}
		else
		{
			m_strKeyword.Format("%d ", m_nGNo);
			m_nSearchType = ST_GROUP_NO;
			InitList();

			MessageBox("그룹전체 고객에 대해서 성공적으로 수정하였습니다.", "확인", MB_ICONINFORMATION);
		}
	}
}


void CCustomerDlg::OnBnClickedEditPersonBtn()
{
	if(m_List.GetItemCount() == 0)
		return;

	if(m_bDirty)
		OnBnClickedEditBtn();	

	if(!m_bGroupChangeReady)
	{
		CString strSourceCustomer = "";
		ST_CUSTOMER_INFO *pc = 
			(ST_CUSTOMER_INFO*)m_List.GetItemData(m_List.GetSelectedRows()->GetAt(0)->GetRecord());

		if(pc == NULL)
		{
			MsgBox("복사원본인 고객이 지정되지 않았습니다.");
			return;
		}
		
		if(pc->nCNo <= 0)
		{
			MessageBox("고객을 선택하시기 바랍니다.", "확인", MB_ICONINFORMATION);
			return;
		}

		strSourceCustomer.Format("선택하신 %s[%s]고객의 정보를 기준으로 삼겠습니까? ",pc->strCompany,pc->strName);
		if(MessageBox(strSourceCustomer,	"확인",  MB_ICONINFORMATION | MB_YESNO) == IDNO) 
			return;

		m_nPersonCopySrcCNo = pc->nCNo;
		m_bGroupChangeReady = TRUE;
	}
	else
	{
		
		long nDestCNo = 0;

		if(m_List.GetSelectedRows()->GetCount() == 0)
		{
			MsgBox("복사되어질 고객을 선택하여주세요");
			return;
		}	

		CCustomerSelectChangeDlg dlg;

		if(dlg.DoModal() != IDOK)
			return;

		CString strCNoList = "", strCNo = "";
		for(int i = 0; i < m_List.GetSelectedRows()->GetCount(); i++)
		{
			CXTPGridRow *pRow = m_List.GetSelectedRows()->GetAt(i);
			ST_CUSTOMER_INFO *pc =(ST_CUSTOMER_INFO *)m_List.GetItemData(pRow->GetRecord());
			if(pc == NULL)
			{
				MessageBox("복사하실 고객이 지정되지 않아 수정을 중지 합니다");
				return;
			}
			strCNo.Format("%ld,", pc->nCNo);
			strCNoList += strCNo;

			CMkCommand pCmd(m_pMkDb, "update_customer_for_person_customer_2011_1");
			CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
			pCmd.AddParameter(m_nCompanyCode);
			pCmd.AddParameter(m_nPersonCopySrcCNo);
			pCmd.AddParameter(pc->nCNo);
			pCmd.AddParameter(dlg.m_bCNo);
			pCmd.AddParameter(dlg.m_bCompany);
			pCmd.AddParameter(dlg.m_bDepart);
			pCmd.AddParameter(dlg.m_bManager);
			pCmd.AddParameter(dlg.m_bTel);
			pCmd.AddParameter(dlg.m_bMobile);
			pCmd.AddParameter(dlg.m_bRiderMemo);
			pCmd.AddParameter(dlg.m_bMemo);
			pCmd.AddParameter(dlg.m_bGrade);
			pCmd.AddParameter(dlg.m_bAllocGroup);
			pCmd.AddParameter(dlg.m_bDetailAddress);
			pCmd.AddParameter(dlg.m_bLocation);
			pCmd.AddParameter(dlg.m_bDisplay);
			pCmd.AddParameter(dlg.m_bCredit);
			pCmd.AddParameter(dlg.m_bSendStateChangeSms);
			pCmd.AddParameter(dlg.m_bICMapDisplayType);
			pCmd.AddParameter(dlg.m_bUseHomepage);
			pCmd.AddParameter(dlg.m_bPreventPosUpdate);
			pCmd.AddParameter(dlg.m_bPriceGrade);
			pCmd.AddParameter(dlg.m_bDiscount);
			pCmd.AddParameter(dlg.m_bCoupon);
			pCmd.AddParameter(dlg.m_bMileage);
			pCmd.AddParameter(dlg.m_bEMail);

			if(pCmd.Execute())
			{
				if(parRet->GetLong() < 0)
				{
					MessageBox("고객번호가 잘못되었습니다.\n재검색후에 재시도 바랍니다.", "확인", MB_ICONEXCLAMATION);
				}
			
			}
		}
		MessageBox("선택 고객에 대해서 성공적으로 수정하였습니다.", "확인", MB_ICONINFORMATION);
		m_bGroupChangeReady = FALSE;

		if(strCNoList.GetLength() > 0)
			BatchUpdateGetCustomerInfo(strCNoList); // 수정한 고객 리프레쉬
	}
}

void CCustomerDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect, rcAddressList;
	m_List.GetWindowRect(&rect);
	m_lstAddress.GetWindowRect(&rcAddressList);

	if(rect.PtInRect(point))
	{
		CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

		if(pRows == NULL) return; 
		else if(pRows->GetCount() == ZERO) return;

		CXTPGridRecord *pRecord = (CXTPGridRecord*)pRows->GetAt(ZERO)->GetRecord();

		if(pRecord == NULL)
			return;

		ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_List.GetItemData(pRecord);

		CMenu rMenu;
		CMenu *pRMenu;
	
		if(pc->bDelete == FALSE)
		{  
			rMenu.LoadMenu(IDR_CONTEXT_MENU);
			pRMenu=rMenu.GetSubMenu(9);
		}
		else
		{
			rMenu.LoadMenu(IDR_CONTEXT_MENU);
			pRMenu=rMenu.GetSubMenu(27);
		}

		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}

	/*
	if(rcAddressList.PtInRect(point))
	{
		int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
		if(nItem >= 0) {
			CMenu rMenu;
			rMenu.LoadMenu(IDR_CONTEXT_MENU);
			CMenu *pRMenu=rMenu.GetSubMenu(18);
			pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
		}
	}
	*/
}
void CCustomerDlg::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	m_List.GetSelectedRows()->Select(pItemNotify->pRow);

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_List, pt);

}

void CCustomerDlg::OnMakeNewCustomer()
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) return;
	else if(pRows->GetCount() == ZERO) return;

	CXTPGridRecord *pRecord = (CXTPGridRecord*)pRows->GetAt(ZERO)->GetRecord();

	if(pRecord == NULL)
		return;

	ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_List.GetItemData(pRecord);

	long nRet = IDCANCEL;

	if(pc->nTelType != ONE)
		nRet = MessageBox("고객생성후 해당 번호는 삭제하시겠습니까?\r\n", "확인", MB_OKCANCEL|| MB_ICONINFORMATION);

	CMkCommand pCmd(m_pMkDb, "make_customer_from_customertel");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(m_nCompanyCode);
	pCmd.AddParameter(pc->nCNo);
	pCmd.AddParameter(pc->nTelID);
	pCmd.AddParameter(nRet == IDOK ? ONE : ZERO);

	CString strGNo = "";
	int nItem = 0;
	//int nQueryRet = 0;

	if(pCmd.Execute())
	{
		parRet->GetValue(m_nCNo);
		m_nSearchType = ST_CNO;
		m_strKeyword.Format("%d", m_nCNo);
		GetCustomerInfo(nItem, strGNo, 0);
	}
}

void CCustomerDlg::OnSetReleaseGroupOwner()
{
	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem == -1) 
	{
		MessageBox("고객을 선택하시기 바랍니다", "확인", MB_ICONINFORMATION);
		return;
	}

	ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_List.GetItemData(nItem);
	if(pc->nGNo <= 0)
	{
		MessageBox("해당고객은 그룹고객이 아닙니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	if(!pc->bGroupOwner)
	{
		MessageBox("해당고객은 그룹소유자가 아닙니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	if(MessageBox("그룹소유를 정말해지 하시겠습니까? ", "확인", MB_ICONINFORMATION | MB_YESNO) == IDNO)
		return;

	CMkCommand pCmd(m_pMkDb, "update_customer_group_owner2");
	pCmd.AddParameter(m_nCustomerTable);
	pCmd.AddParameter(pc->nCNo);
	pCmd.AddParameter(0);
	if(pCmd.Execute())
	{
		MessageBox("해당고객을 그룹오너로 해제하였습니다."	,"확인",MB_ICONINFORMATION);
		pc->bGroupOwner = FALSE;
		//InitList();
		m_List.RedrawControl();
	}
}
void CCustomerDlg::OnSetGroupOwner()
{
	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem == -1) 
	{
		MessageBox("고객을 선택하시기 바랍니다", "확인", MB_ICONINFORMATION);
		return;
	}

	ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_List.GetItemData(nItem);
	if(pc->nGNo <= 0)
	{
		MessageBox("해당고객은 그룹고객이 아닙니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkCommand pCmd(m_pMkDb, "update_customer_group_owner2");
	pCmd.AddParameter(m_nCustomerTable);
	pCmd.AddParameter(pc->nCNo);
	pCmd.AddParameter(1);
	if(pCmd.Execute())
	{
		MessageBox("해당고객을 그룹오너로 설정하였습니다.","확인",	MB_ICONINFORMATION);

		pc->bGroupOwner = TRUE;
		m_List.RedrawControl();

		//InitList();
	}
}

void CCustomerDlg::OnBnClickedSumCusBtn()
{
	MessageBox("준비중입니다", "확인", MB_ICONINFORMATION);
	return;

	CSumCustomerDlg dlg;
	dlg.m_CusReport = &m_List;
	dlg.m_nCompany = m_nCustomerTable;
	if(dlg.DoModal() == IDOK)
	{
		for(int i=0; i<dlg.m_ReportDel.GetItemCount(); i++)
		{
			long nSel = dlg.m_ReportDel.GetItemData(i);
			m_List.GetRecords()->RemoveAt(nSel);
		}

		m_List.Populate();
	}
}

void CCustomerDlg::DeleteGroupItem()
{
	long nDeleteCount = 0;

	CXTPGridRecords * pRecords = m_List.GetRecords();
	long nCount = pRecords->GetCount();

	for(int i=0; i<nCount; i++)
	{
		CXTPGridRecord *pRecord = NULL;
		pRecord = m_List.GetRecords()->GetAt(i - nDeleteCount);
		CString strName = pRecord->GetItem(0)->GetCaption(NULL);

		ST_CUSTOMER_INFO *pCusInfo = (ST_CUSTOMER_INFO*)m_List.GetItemData(pRecord);

		if(strName = "지명")
			continue;

		if(pCusInfo->bGorupSelect)
		{
			nDeleteCount++;
			if(pCusInfo)
				delete pCusInfo;

			pRecords->RemoveRecord(pRecord);
		}
	}

	m_List.Populate();
}


void CCustomerDlg::GetPcInfo(CMkRecordset *pRs, ST_CUSTOMER_INFO *pc, COleDateTime &dtPRDate, BOOL bInsungQuery)
{
	pRs->GetFieldValue("nCNo", pc->nCNo);
	pRs->GetFieldValue("nID", pc->nID);
	pRs->GetFieldValue("sCompany", pc->strCompany);
	pRs->GetFieldValue("sDepart", pc->strDepart);
	pRs->GetFieldValue("sName", pc->strName);
	pRs->GetFieldValue("sTel1", pc->strMobile);
	pRs->GetFieldValue("sDong", pc->strDong);
	pRs->GetFieldValue("sLocation", pc->strLocation);
	pRs->GetFieldValue("bCredit", pc->bCredit);
	pRs->GetFieldValue("nDiscount", pc->nDiscount);
	pRs->GetFieldValue("nGNo", pc->nGNo);
	pRs->GetFieldValue("nTeamNo", pc->nTeamNo);
	pRs->GetFieldValue("nAllocGroup", pc->nAllocGroup);
	pRs->GetFieldValue("nCouponCharge", pc->nCouponCharge);
	pRs->GetFieldValue("sMemo", pc->strMemo);
	//pRs->GetFieldValue("sMobile", pc->strMobile);
	pRs->GetFieldValue("nPosX", pc->nPosX);
	pRs->GetFieldValue("nPosY", pc->nPosY);
	pRs->GetFieldValue("nDongID", pc->nDongID);
	pRs->GetFieldValue("sAddress", pc->strAddress);
	pRs->GetFieldValue("nNodeID", pc->nNodeID);
	pRs->GetFieldValue("nType", pc->nCustomerType);
	pRs->GetFieldValue("sEMail", pc->strEMail);
	pRs->GetFieldValue("dtRegister", pc->dtRegister);
	pRs->GetFieldValue("dtLastUse", pc->dtLastUse);
	pRs->GetFieldValue("nUseCount", pc->nUseCount);
	pRs->GetFieldValue("nCancelCount", pc->nCancelCount);
	pRs->GetFieldValue("sRiderMemo", pc->strRiderMemo);
	//pRs->GetFieldValue("nCreditCount", pc->nCreditCount);
	//pRs->GetFieldValue("nCreditCharge", pc->nCreditCharge);
	pRs->GetFieldValue("sUserID", pc->strUserID);
	pRs->GetFieldValue("nSendStateChangeSMS", pc->nSendStateChangeSMS);
	pRs->GetFieldValue("bPreventPosUpdate", pc->bPreventPosUpdate);
	pRs->GetFieldValue("bCreditAfterDiscount", pc->bCreditAfterDiscount);
	pRs->GetFieldValue("sLoginID", pc->strLoginID);
	pRs->GetFieldValue("sLoginPW", pc->strLoginPW);
	pRs->GetFieldValue("bUseHomepage", pc->bUseHomepage);
	pRs->GetFieldValue("nCustomerGrade", pc->nCustomerGrade);
	pRs->GetFieldValue("nPriceGrade", pc->nPriceGrade);

	pRs->GetFieldValue("nReportStartDay", pc->nReportStartDay);
	pRs->GetFieldValue("nReportEndDay", pc->nReportEndDay);
	pRs->GetFieldValue("nIssueTaxBillDay", pc->nIssueTaxBillDay);
	pRs->GetFieldValue("nUncollectedAmount", pc->nUnCollectedAmount);
	//pRs->GetFieldValue("dtPRDate", pc->dtPRDate);
	pRs->GetFieldValue("dtPRDate", dtPRDate);

	pRs->GetFieldValue("nDiscountType", pc->nDiscountType);
	pRs->GetFieldValue("nMileageType", pc->nMileageType);
	pRs->GetFieldValue("nMileageValue", pc->nMileageValue);
	pRs->GetFieldValue("nCouponType", pc->nCouponType);
	pRs->GetFieldValue("bGroupOwner", pc->bGroupOwner);
	pRs->GetFieldValue("nMileageBalance", pc->nMileageBalance);
	pRs->GetFieldValue("nMainAddressID", pc->nMainAddressID);
	pRs->GetFieldValue("nICMapDisplayType", pc->nICMapDisplayType);
	pRs->GetFieldValue("bHasDetailPos", pc->bHasDetailPos);
	pRs->GetFieldValue("nSalesCompany", pc->nSalesCompany);
	pRs->GetFieldValue("nSalesWNo", pc->nSalesWNo);
	pRs->GetFieldValue("dtSales", pc->dtSales);
	pRs->GetFieldValue("nTelID", pc->nTelID);
	pRs->GetFieldValue("nTelType", pc->nTelType);
	pRs->GetFieldValue("bDelete", pc->bDelete);
	pRs->GetFieldValue("bNotAutoShareOrder", pc->bNotAutoShareOrder);
	pRs->GetFieldValue("sFax", pc->strFax);
	pRs->GetFieldValue("nCustDisplayCharge", pc->nMemCNo);
	pRs->GetFieldValue("nDiscountRange", pc->nDiscountRange);
	pRs->GetFieldValue("nCustomerColor", pc->nCustomerColor);
	pRs->GetFieldValue("nMemoColor", pc->nMemoColor);
	pRs->GetFieldValue("nShowPhoneType", pc->nShowPhoneType);
	pRs->GetFieldValue("bPopupCustomerDlg", pc->bPopupCustomerDlg);
	pRs->GetFieldValue("bOnlinePopup", pc->bOnlinePopup);
	pRs->GetFieldValue("nOnlinePopupCharge", pc->nOnlinePopupCharge);
	
	if(bInsungQuery)
		pRs->GetFieldValue("sTel2", pc->strTel2);
}
 
void CCustomerDlg::OnBnClickedSearchGroupCheck()
{
	AfxGetApp()->WriteProfileInt("CCustomerDlg", "GroupSearch", m_chkSearchGroup.GetCheck());
}

void CCustomerDlg::InsertGroupStartLine()
{
	ST_CUSTOMER_INFO *pc = new ST_CUSTOMER_INFO;
	pc->nCNo = LINE_ROW;

	long nItem = m_List.GetItemCount();
	CXTPGridRecord *pRecord = m_List.InsertItem(nItem++, 0, -1, 0);
	pc->bGorupSelect = TRUE;

	m_List.SetItemText(pRecord, 4, "아래는 그룹");
	m_List.SetItemText(pRecord, 5, "고객 검색");
	m_List.SetItemText(pRecord, 6, "결과입니다");

	m_List.SetItemData(pRecord, (DWORD_PTR)pc);
}

void CCustomerDlg::OnBnClickedAddressBtn()
{
	CString strCount; m_btnAddress.GetWindowText(strCount);
	strCount.Replace("건", "");
	if(atoi(strCount) > 1)
		ShowAddress();
	else
		MessageBox("추가동이 없습니다", "확인", MB_ICONINFORMATION);
}

void CCustomerDlg::ShowAddress()
{
	m_lstAddress.DeleteAllItems();

	CMkCommand pCmd(m_pMkDb, "select_customer_address");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCustomerTable);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCNo);

	pRs.Execute(&pCmd);

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		ST_ADDRESS *st = new ST_ADDRESS;

		pRs.GetFieldValue("nID", st->nID);
		pRs.GetFieldValue("nCNo", st->nCNo);
		pRs.GetFieldValue("nGNo", st->nGNo);
		pRs.GetFieldValue("nCompany", st->nCompany);
		pRs.GetFieldValue("sAddressTitle", st->strAddressTitle);
		pRs.GetFieldValue("sDong", st->strDong);
		pRs.GetFieldValue("sLocation", st->strLocation);
		pRs.GetFieldValue("nPosX", st->nPosX);
		pRs.GetFieldValue("nPosY", st->nPosY);
		pRs.GetFieldValue("nDongID", st->nDongID);
		pRs.GetFieldValue("sAddress", st->strAddress);

		if(m_nPcMainAddressID == st->nID) //대표주소
		{
			m_lstAddress.InsertItem(i, "대표주소");
			st->strAddressTitle = "대표주소";
		}
		else
			m_lstAddress.InsertItem(i, st->strAddressTitle);

		m_lstAddress.SetItemText(i, 1, m_poiNew.GetPOI(st->nDongID)->GetRegionName() + " " +st->strAddress);
		m_lstAddress.SetItemData(i, (DWORD)st);

		pRs.MoveNext();
	}

	m_lstAddress.Populate();
	/*
	CRect rcAddress;
	m_lstAddress.GetWindowRect(rcAddress);
	ScreenToClient(rcAddress);

	rcAddress.bottom = rcAddress.top + (pRs.GetRecordCount() * 20);

	m_lstAddress.MoveWindow(rcAddress);
	*/
	m_lstAddress.ShowWindow(TRUE);
	ShowControl(FALSE);
}

void CCustomerDlg::ShowControl(BOOL bShow)
{
	UINT nFlag[] = {IDC_RIDER_MEMO_EDIT, IDC_MEMO_EDIT};

	for(int i=0; i<2; i++)
	{
		CWnd *pWnd = GetDlgItem(nFlag[i]);
		pWnd->ShowWindow(bShow);
	}

	m_btnAddressClose.ShowWindow(!bShow);
}

void CCustomerDlg::OnMakeMainAddress()
{
	CXTPGridSelectedRows *pAddressRows = m_lstAddress.GetSelectedRows();
	CXTPGridSelectedRows *pCustomerRows = m_List.GetSelectedRows();

	if((pAddressRows == NULL) || (pCustomerRows == NULL))
		return;

	ST_ADDRESS *st = (ST_ADDRESS*)m_lstAddress.GetItemData(pAddressRows->GetAt(0)->GetRecord());
	ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_List.GetItemData(pCustomerRows->GetAt(0)->GetRecord());

	if(pc->nMainAddressID == st->nID)
	{
		MessageBox("이미 대표번주소로 지정되어 있습니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkCommand pCmd(m_pMkDb, "update_customer_poi_dong_main_address");
	pCmd.AddParameter(st->nID);
	pCmd.AddParameter(st->nCompany);
	pCmd.AddParameter(st->nCNo);

	if(pCmd.Execute())
	{
		m_nPcMainAddressID = st->nID;
		MessageBox("대표주소로 지정되었습니다" , "확인", MB_ICONINFORMATION);
		m_pSub1->m_editAddrTitle.SetWindowText("대표주소");
		OnBnClickedAddressCloseBtn();
		m_pSub1->m_editAddrTitle.EnableWindow(FALSE);

		pc->nPosX = st->nPosX;
		pc->nPosY = st->nPosY;
		pc->strAddress = st->strAddress;
		pc->strDong = st->strDong;
		pc->nDongID = st->nDongID;
		pc->nMainAddressID = st->nID;
		pc->strLocation = st->strLocation;
	}

	//	OnReportItemChange(NULL, NULL);
}

void CCustomerDlg::OnDeleteAddress()
{
	CXTPGridSelectedRows *pAddressRows = m_lstAddress.GetSelectedRows();
	CXTPGridSelectedRows *pCustomerRows = m_List.GetSelectedRows();

	if((pAddressRows == NULL) || (pCustomerRows == NULL))
		return;

	ST_ADDRESS *st = (ST_ADDRESS*)m_lstAddress.GetItemData(pAddressRows->GetAt(0)->GetRecord());
	ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_List.GetItemData(pCustomerRows->GetAt(0)->GetRecord());

	if(pc->nMainAddressID == st->nID)
	{
		MessageBox("대표주소는 삭제 하실수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkCommand pCmd(m_pMkDb, "delete_customer_poi_dong");
	pCmd.AddParameter(st->nID);
	pCmd.AddParameter(st->nCompany);
	pCmd.AddParameter(st->nCNo);

	if(pCmd.Execute())
	{ 
		m_lstAddress.GetRecords()->RemoveRecord(pAddressRows->GetAt(0)->GetRecord());
		m_lstAddress.Populate();
		OnReportItemChange(NULL, NULL);
		//m_lstAddress.ShowWindow(FALSE);
		//ShowControl(TRUE);
	}

}

void CCustomerDlg::OnBnClickedAddressCloseBtn()
{
	m_lstAddress.ShowWindow(FALSE);
	ShowControl(TRUE);
}

void CCustomerDlg::OnCbnSelchangePriceGradeCombo()
{
	m_bDirty = TRUE;

	if((CXTPGridRecord*)m_List.GetFirstSelectedRecord() == NULL)
	{
		MessageBox("수정하려는 고객을 선택하세요", "확인", MB_ICONINFORMATION);
		return ;
	}

	CXTPGridRow *pRow = m_List.GetSelectedRows()->GetAt(0);

	CXTPGridRecord *pRecord = pRow->GetRecord();
	ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_List.GetItemData(pRecord);

	if(pc->nPriceGrade == 4 && m_pSub2->m_cmbPriceGrade.GetCurSel() < 4)
	{
		HistoryChargeDelete(pc->nPriceGrade);
		
	}
	else if(pc->nPriceGrade != 4 && m_pSub2->m_cmbPriceGrade.GetCurSel()  == 4)
	{
		HistoryChargeAdd(pc->nPriceGrade);
		m_bDirty = FALSE; // 디비에 반영
	}

	
}

void CCustomerDlg::HistoryChargeDelete(int nOriginalCurSel)
{

	if( MessageBox("개별고객요금을 삭제하시겠습니까? ", "확인",  MB_YESNO) == IDNO)
	{
		m_pSub2->m_cmbPriceGrade.SetCurSel(nOriginalCurSel);
		return;
	}

	m_bDirty = FALSE; // 디비에 반영
	CXTPGridRow *pRow = m_List.GetSelectedRows()->GetAt(0);
	CXTPGridRecord *pRecord = pRow->GetRecord();
	ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_List.GetItemData(pRecord);

	CMkCommand pCmd(m_pMkDb, "	select_history_charge_member_sub_delete2");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter(m_nCNo);
	pCmd.AddParameter(GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(m_pSub2->m_cmbPriceGrade.GetCurSel());
	
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pParString = pCmd.AddParameter(typeString, typeOutput, 20, "");
	CMkParameter *pParMemCNo = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	pRs.Execute(&pCmd);
	int nOUTPUT = 0; CString strDeleteCompany = ""; long nMemCharge = 0;
	pPar->GetValue(nOUTPUT);
	pParString->GetValue(strDeleteCompany);
	pParMemCNo->GetValue(nMemCharge);
	if(nOUTPUT >= 1000 && strDeleteCompany.GetLength() > 0 )
	{
		CString strTemp = "선택하신 고객의 개별요금이 사용되는곳이 없어  요금도같이 삭제해야 합니다.\n\r 삭제하시겠습니까?";
		 
		if( MessageBox(strTemp, "확인", MB_ICONINFORMATION | MB_YESNO) == IDYES )
		{
			CMkCommand pCmd(m_pMkDb, "select_history_charge_member_person_all_data");
			CMkRecordset pRs(m_pMkDb);
			pCmd.AddParameter(m_nCNo);
			pCmd.AddParameter(m_nCompanyCode);
			pCmd.AddParameter(nMemCharge);			
			if(!pCmd.Execute())return;			

			MessageBox("관련 개별요금이 삭제되었으며 요금설정도 바뀌었습니다.", "확인", MB_ICONINFORMATION);
			pc->nPriceGrade = m_pSub2->m_cmbPriceGrade.GetCurSel();
			return;
		}
		else
		{
			MessageBox("데이터가 많아 속도및 관리하시기 불편하오니 나중에 삭제하시기를 부탁드립니다.", 
				"확인", MB_ICONINFORMATION  );
		}
		
	}	

	pc->nPriceGrade = m_pSub2->m_cmbPriceGrade.GetCurSel();
	pRs.Close();
	MessageBox("히스토리 요금설정이 삭제됬습니다.", "확인", MB_ICONINFORMATION);

}

void CCustomerDlg::HistoryChargeAdd(int nOriginalCurSel)
{

	if( MessageBox("개별고객요금을 등록하시겠습니까? ", "확인",  MB_YESNO) == IDNO)
	{
		m_pSub2->m_cmbPriceGrade.SetCurSel(nOriginalCurSel);
		return;
	}


	if(m_pSub2->m_cmbPriceGrade.GetCurSel() == 4)  // H등급이면
	{

		CMkCommand pCmd(m_pMkDb, "select_history_charge_is_member2");
		CMkRecordset pRs(m_pMkDb);
		pCmd.AddParameter(m_nCNo);
		pCmd.AddParameter(m_nCompanyCode);
		CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
		CMkParameter *pParChargeName = pCmd.AddParameter(typeString, typeOutput, 20, "");
		CMkParameter *pParCompanyName = pCmd.AddParameter(typeString, typeOutput, 20, "");
		CMkParameter *pParDept = pCmd.AddParameter(typeString, typeOutput, 20, "");
		CMkParameter *pParTel = pCmd.AddParameter(typeString, typeOutput, 20, "");
		pRs.Execute(&pCmd);

		long nOUTPUT = 0;
		CString strChargeName = "", strCompanyName = "", strDepart = "", strTel1 = "";
		pPar->GetValue(nOUTPUT);
		pParChargeName->GetValue(strChargeName);
		pParCompanyName->GetValue(strCompanyName);
		pParDept->GetValue(strDepart);
		pParTel->GetValue(strTel1);

		CString strMessage = "";
		
		CXTPGridRow *pRow = m_List.GetSelectedRows()->GetAt(0);
		CXTPGridRecord *pRecord = pRow->GetRecord();
		ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_List.GetItemData(pRecord);

		if(nOUTPUT == 1000)  // 등록된계 없다면
		{
			CChargeMemberDlg dlg;
			dlg.m_strChargeName = m_pSub1->m_strCompany;
			if( dlg.DoModal() == IDOK)
			{				
				if( dlg.m_nReturn == IDYES	)				
				{
					CString strChargeName = dlg.m_strChargeName;
					CString strEtc = dlg.m_strEtc;
					
					CMkCommand pCmd(m_pMkDb, "select_history_charge_member_insert2");
					CMkRecordset pRs(m_pMkDb);
					pCmd.AddParameter(m_nCNo);
					pCmd.AddParameter(m_nCompanyCode);
					pCmd.AddParameter(m_ci.m_strName);
					CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
					CMkParameter *pParString = pCmd.AddParameter(strChargeName);
					CMkParameter *pParStringEtc = pCmd.AddParameter(strEtc);					
					if(!pCmd.Execute())
					{
						m_pSub2->m_cmbPriceGrade.SetCurSel(nOriginalCurSel);
						return;			
					}	


					int nOUTPUT = 0;
					pPar->GetValue(nOUTPUT);
					if(nOUTPUT == 200)
					{
						pc->nPriceGrade = 4;
						MsgBox("등록 되었습니다.");
						m_pSub2->m_cmbPriceGrade.SetCurSel(4);
					}
				}
				else if( dlg.m_nReturn == IDNO)
				{
					CChargeHistoryMemDlg dlg;
					dlg.m_nCNo = this->m_nCNo;
					//dlg.m_sChargeName = m_pSub1->m_strCompany;
					dlg.m_nCompany = m_nCompanyCode;
					dlg.DoModal();
					if(dlg.m_nResult == REGISTER_CUSOMER)
					{
						pc->nPriceGrade = 4;
						m_pSub2->m_cmbPriceGrade.SetCurSel(4);
					}
					else
					{
						pc->nPriceGrade = 0;
						m_pSub2->m_cmbPriceGrade.SetCurSel(0);
					}

				}
				else if( dlg.m_nReturn == IDCANCEL)
				{
					m_pSub2->m_cmbPriceGrade.SetCurSel(nOriginalCurSel);
				}
			}		
		}
		else
		{
			char szTemp[] =  
				"요금제이름 : %s\n\r\n\r"				\
				"회사명 : %s\n\r\n\r"						\
				"부서명 : %s\n\r\n\r"						\
				"전화번호 : %s\n\r\n\r"					\
				"%s 되어있습니다 \n\r\n\r\n\r"		\
				"수정하시려면 예(Y)\n\r\n\r"			\
				"취소하시려면 아니로(N)를 눌러주세요";				
			
			strMessage.Format(szTemp, strChargeName, strCompanyName, strDepart, GetDashPhoneNumber(strTel1),
				nOUTPUT == 100 ? "메인으로 등록" : "그룹에 참가");
				
			if(MessageBox(strMessage, "확인",  MB_ICONINFORMATION | MB_YESNO) == IDYES	)
			{
				CChargeHistoryMemDlg dlg;
				dlg.m_nCNo = this->m_nCNo;
			//	dlg.m_sChargeName = m_pSub1->m_strCompany;
				dlg.m_nCompany = m_nCompanyCode;
				dlg.DoModal();
				if(dlg.m_nResult == DELETE_CUSOMER)
				{
					pc->nPriceGrade = 0;
					m_pSub2->m_cmbPriceGrade.SetCurSel(0); // 요금제창에서 삭제되면
					return;
				}				
			}
			pc->nPriceGrade = 4;
			m_pSub2->m_cmbPriceGrade.SetCurSel(4);
		}
		
	}
}

void CCustomerDlg::OnEnChangeAddrTitleEdit()
{
	m_bDirty = TRUE;
}

BOOL CCustomerDlg::CheckLoginID()
{
	CMkCommand pCmd(m_pMkDb, "check_login_id");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);

	pCmd.AddParameter(m_nCNo);
	pCmd.AddParameter(m_nCustomerTable);
	pCmd.AddParameter(m_pSub2->m_strLoginID);

	if(!pCmd.Execute()) return FALSE;

	long nRet; parRet->GetValue(nRet);
	
	if(nRet == 10) //중복된 아이디 존재
		return FALSE;

	return TRUE;
}

void CCustomerDlg::SetDisplayAddrEdt()
{
	m_bDirty = TRUE;
	CPOIUnit *pUnit = m_pPlace->GetPOI();
	
	if(pUnit != NULL)
	{
		//m_strAddress = m_stcAddressDisplay.GetNormalText();
		//CString strTemp = pUnit->GetFullName();
	
		//m_strAddress.Replace(strTemp, "");
		//m_strAddress.Replace(" ", "");

		m_strAddress = ""; //address를 입력할 필요가 없음 posx, posy로 자동가져옴

		m_nDongID = pUnit->GetDongID();
		m_nPosX = m_pPlace->GetDetailPosX();
		m_nPosY = m_pPlace->GetDetailPosY();
		m_bHasDetailPos = TRUE;

		if(m_nPosX == 0 || m_nPosY == 0)
		{
			m_nPosX = pUnit->GetPosX();
			m_nPosY = pUnit->GetPosY();
			m_bHasDetailPos = FALSE;
		}
	}
}

void CCustomerDlg::SetAddressInfo()
{	
	return;
	long nNewDongID;
	CString strNewAddress = "";

	if(m_bHasDetailPos == TRUE && m_nPosX > 0 && m_nPosY > 0) 
	{
		if(CPOIDataAddress::GetNearAddress(m_pMkDb, m_nPosX, m_nPosY, nNewDongID, strNewAddress))
		{			
			CString strTemp = CSearchPOI::GetMarkupLastPartHilight(m_strAddress.GetLength() > 0 ? m_strAddress : strNewAddress);
			m_pSub1->m_stcAddressDisplay.SetMarkupText(strTemp);			
		}
		else
		{
			m_pSub1->m_stcAddressDisplay.SetMarkupText("");
		}

	}
	else if(m_nDongID > 0)
	{
		CPOIUnit *pDongPOI = m_poiNew.GetDongPOI(m_nDongID);
		m_pSub1->m_stcAddressDisplay.SetMarkupText(CSearchPOI::GetMarkupLastPartHilight(pDongPOI), pDongPOI->GetRegionName());
	}
	else
		m_pSub1->m_stcAddressDisplay.SetMarkupText("");

}

void CCustomerDlg::InsertCustomerOk()
{
	m_nCNo = m_pAddCustomerDlg->m_nCNo;
	m_strKeyword.Format("%d ", m_pAddCustomerDlg->m_nCNo);
	m_nSearchType = ST_CNO;
	InitList();

	m_pAddCustomerDlg->ShowWindow(FALSE);

	delete m_pAddCustomerDlg;  
	m_pAddCustomerDlg = NULL;//창 삭제
}
 
bool sortString(ST_TEL *p1, ST_TEL *p2)
{ 
	if(p1->strTel.Left(2) == "01" && p2->strTel.Left(2) == "01")
		return p1->strTel < p2->strTel; 
	else if(p1->strTel.Left(2) != "01" && p2->strTel.Left(2) != "01")
		return p1->strTel < p2->strTel;
	else
		return p1->strTel > p2->strTel;
} 


void CCustomerDlg::RefreshTelList(long nTelID)
{	
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) return;
	else if(pRows->GetCount() == ZERO) return;

	CXTPGridRecord *pRecord = pRows->GetAt(ZERO)->GetRecord();
	ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_List.GetItemData(pRecord);

	MAP_TEL::iterator it;
	long nCount = ZERO; 

	m_pSub1->m_lstTel.DeleteAllItems();


	vector<ST_TEL*> vec;
 
	for(it = m_mapTel.begin(); it != m_mapTel.end(); it++)
	{
		if(pc->nCNo == it->second.nCNo && 
			pc->strDepart == it->second.strDepart && pc->strName == it->second.strManager)
		{ 
			CString strTemp = "";

			if(it->second.nTelType == TEL_TYPE_PHONE1)
				strTemp = "☏¹";
			else if(it->second.nTelType == TEL_TYPE_PHONE2)
				strTemp = "☏²"; 
			else  if(it->second.nTelType  == TEL_TYPE_SMS)
				strTemp = "☏ⁿ";
			else 
			{
				vec.push_back(&it->second);
				continue;
			}

			m_pSub1->m_lstTel.InsertItem(nCount, strTemp);
			m_pSub1->m_lstTel.SetItemText(nCount, ONE, ::GetDashPhoneNumber(it->second.strTel));
			m_pSub1->m_lstTel.SetItemData(nCount++, (DWORD_PTR)&it->second);
		} 
	}

	if(vec.size() > ZERO)
	{
		std::sort(vec.begin(), vec.end(), sortString);

		for(int i=ZERO; i<vec.size(); i++)
		{			
			ST_TEL *pInfo = vec.at(i);

			if(pInfo->nTelType  == TEL_TYPE_PHONE1)
				m_pSub1->m_lstTel.InsertItem(nCount, "☏¹");
			else if(pInfo->nTelType  == TEL_TYPE_PHONE2)
				m_pSub1->m_lstTel.InsertItem(nCount, "☏²");
			else  if(pInfo->nTelType  == TEL_TYPE_SMS)
				m_pSub1->m_lstTel.InsertItem(nCount, "☏ⁿ");
			else
				m_pSub1->m_lstTel.InsertItem(nCount, "");
		
			m_pSub1->m_lstTel.SetItemText(nCount, ONE, ::GetDashPhoneNumber(pInfo->strTel));
			m_pSub1->m_lstTel.SetItemData(nCount++, (DWORD_PTR)pInfo);
		}
	}

	m_pSub1->m_lstTel.Populate();

	ChangeTelDepartInfo();
}


CWnd* CCustomerDlg::GetTabItem(int nTab)
{
	CXTPTabPaintManager* pXTPTabPaintManager =  m_wndTabControl.GetPaintManager();
	int nTabCount = m_wndTabControl.GetItemCount();
	if(nTab >= nTabCount) return NULL;

	CXTPTabManagerItem* pXTPTabManagerItem =  m_wndTabControl.GetItem(nTab);

	CWnd* pWnd =  FromHandle(pXTPTabManagerItem->GetHandle());
	return pWnd;
}

void CCustomerDlg::OnDeleteCall()
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) return;
	else if(pRows->GetCount() == ZERO) return;

	CXTPGridRecord *pRecord = (CXTPGridRecord*)pRows->GetAt(ZERO)->GetRecord();

	if(pRecord == NULL)
		return;

	ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_List.GetItemData(pRecord);;


	if(pc->nTelType == ONE)
	{
		MessageBox("대표번호는 삭제 하실 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkCommand pCmd(m_pMkDb, "delete_customer_phone_with_manager");
	pCmd.AddParameter(m_nCNo);
	pCmd.AddParameter(m_nTelID);

	CString strGNo = "";
	int nItem = 0;

	if(pCmd.Execute())
		
		(nItem, strGNo, 0);
}

void CCustomerDlg::OnMakeMain()
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) return;
	else if(pRows->GetCount() == ZERO) return;

	CXTPGridRecord *pRecord = (CXTPGridRecord*)pRows->GetAt(ZERO)->GetRecord();

	if(pRecord == NULL)
		return;

	ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_List.GetItemData(pRecord);;
 
	CMkCommand pCmd(m_pMkDb, "change_customer_main_phone_1"); 
	pCmd.AddParameter(m_nCNo);
	pCmd.AddParameter(m_nTelID);
	pCmd.AddParameter(pc->strName);
	pCmd.AddParameter(pc->strDepart);
	pCmd.AddParameter(1);



	CString strGNo = "";
	int nItem = 0;

	if(pCmd.Execute())
		GetCustomerInfo(nItem, strGNo, 0);
}

BOOL CCustomerDlg::IsDataHas(ST_TEL *st)
{
	MAP_TEL::iterator it;

	for(it = m_mapTel.begin(); it != m_mapTel.end(); it++)
	{
		if(st->strDepart == it->second.strDepart &&
			st->strManager == it->second.strManager &&
			st->nCNo == it->second.nCNo)
			return TRUE;
	}

	return FALSE;
}

void CCustomerDlg::OnMove(int x, int y)
{
	CMyDialog::OnMove(x, y);
}

void CCustomerDlg::OnCustomerRecover()
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) return;
	else if(pRows->GetCount() == ZERO) return;

	CXTPGridRecord *pRecord = (CXTPGridRecord*)pRows->GetAt(ZERO)->GetRecord();

	if(pRecord == NULL)
		return;

	ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_List.GetItemData(pRecord);;

	CMkCommand pCmd(m_pMkDb, "recover_customer");
	pCmd.AddParameter(pc->nCNo);

	if(pCmd.Execute())
	{
		MessageBox("복구되었습니다", "확인", MB_ICONINFORMATION);
		OnBnClickedSearchBtn();
	}
}

void CCustomerDlg::SetCopyMode(BOOL bCopyMode)
{
	m_bCopyMode = bCopyMode;

	if(m_bCopyMode)
		m_btnCopyCustomer.SetWindowText("복사완료");
	else
		m_btnCopyCustomer.SetWindowText("복사(&S)");

	GetDlgItem(IDC_NEW_BTN)->EnableWindow(!bCopyMode);
	GetDlgItem(IDC_EDIT_BTN)->EnableWindow(!bCopyMode);	
	GetDlgItem(IDC_EDIT_GROUP_ALL_BTN)->EnableWindow(!bCopyMode);
	GetDlgItem(IDC_DEL_BTN)->EnableWindow(!bCopyMode);
	GetDlgItem(IDC_EDIT_PERSON_BTN)->EnableWindow(!bCopyMode);
	GetDlgItem(IDC_OK_BTN)->EnableWindow(!bCopyMode);
}

BOOL CCustomerDlg::IsCopyMode()
{
	return m_bCopyMode;
}
