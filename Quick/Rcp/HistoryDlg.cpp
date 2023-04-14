// UsageHistoryQuickDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "HistoryDlg.h"
#include "RcpDlg.h"
#include "RcpView.h"
#include "RcpPlaceInfo.h"
#include "MkLock.h"

#define CLASS_NAME			"HistoryDlg"

#define ID_SIZE_DOWN	100
#define ID_SIZE_UP		101

// CHistoryDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CHistoryDlg, CMyDialog)
CHistoryDlg::CHistoryDlg(UINT nResourceID, CWnd* pParent /*=NULL*/)
	: CMyDialog(nResourceID, pParent)
{
	m_nOGNo = 0;
	m_bLButtonDown = FALSE;
	m_pwndParent = pParent;
	m_bMoveDown = 0;	
	m_bShowAll = FALSE;
	m_bFirstLoad = FALSE;
}

CHistoryDlg::~CHistoryDlg()
{
	m_wndReport.SaveReportOrder("CHistoryDlg", "m_List_q");

	DeleteAllItems();
}

void CHistoryDlg::DeleteAllItems()
{	
	CMkLock lock(m_cs);

	for(int nItem = 0; nItem < m_wndReport.GetRecords()->GetCount(); nItem++)
	{
		CXTPGridRecord *pRecord = m_wndReport.GetRecords()->GetAt(nItem);

		ST_HISTORY_ITEM_INFO3 *pHis = (ST_HISTORY_ITEM_INFO3*)m_wndReport.GetItemData(pRecord);
		if(pHis)
			delete pHis;

	}

	m_wndReport.DeleteAllItems();
	m_wndReport.Populate();
}

void CHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_wndReport);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_btnRefresh);
	DDX_Control(pDX, IDC_CANCEL_BTN, m_btnCancel);
	DDX_Control(pDX, IDC_SEARCH_START_EDIT, m_edtSearchStart);
	DDX_Control(pDX, IDC_SEARCH_DEST_EDIT, m_edtSearchDest);
	DDX_Control(pDX, IDC_SEARCH_ETC_EDIT, m_edtSearchEtc);
	DDX_Control(pDX, IDC_SEARCH_MANAGER_EDIT, m_edtSearchManager);
}


BEGIN_MESSAGE_MAP(CHistoryDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_LIST, OnReportItemClick)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_WM_LBUTTONDOWN()
	ON_EN_CHANGE(IDC_SEARCH_START_EDIT, OnEnChangeSearchStartEdit)
	ON_EN_CHANGE(IDC_SEARCH_DEST_EDIT, OnEnChangeSearchDestEdit)
	ON_EN_CHANGE(IDC_SEARCH_ETC_EDIT, OnEnChangeSearchEtcEdit)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CUR_ORDER_STATE, OnCurOrderState)
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_SEARCH_MANAGER_EDIT, &CHistoryDlg::OnEnChangeSearchManagerEdit)
	ON_BN_CLICKED(IDC_REFRESH_BTN2, &CHistoryDlg::OnBnClickedRefreshBtn2)
	ON_NOTIFY(XTP_NM_GRID_COLUMNORDERCHANGED, IDC_REPORT_LIST, OnReportColumnChangeChanged)
	ON_BN_CLICKED(IDC_MOVE_DOWN_BTN, OnBnClickedMoveDownBtn)
	ON_COMMAND(ID_SIZE_DOWN, OnSizeDown)
	ON_COMMAND(ID_SIZE_UP, OnSizeUp)
	ON_COMMAND(ID_OPEN_RCP_DLG, OnOpenRcpDlg)	
	ON_COMMAND(ID_EXCEL, OnViewExcel)
	ON_COMMAND(ID_ADD_CALL, OnAddCall)
	ON_BN_CLICKED(IDC_MOVE_DOWN_BTN2, &CHistoryDlg::OnBnClickedShowAllHistory)
END_MESSAGE_MAP()


// CHistoryDlg 메시지 처리기입니다.

void CHistoryDlg::OnReportColumnChangeChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	if(m_bFirstLoad)
		m_wndReport.SaveReportOrder("CHistoryDlg", "m_List_q");
}

BOOL CHistoryDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_bMoveDown = AfxGetApp()->GetProfileInt("HistoryDlg", "MoveDown", 0);

	m_wndReport.InsertColumn(0, "ⓝ", LVCFMT_LEFT,  20);
	m_wndReport.InsertColumn(1, "날짜", LVCFMT_LEFT,  82);
	m_wndReport.InsertColumn(2, "지사", LVCFMT_LEFT,  60);
	m_wndReport.InsertColumn(3, "상태", LVCFMT_CENTER, 35);
	m_wndReport.InsertColumn(4, "지불", LVCFMT_CENTER, 35);
	m_wndReport.InsertColumn(5, "담당자", LVCFMT_LEFT, 55);
	m_wndReport.InsertColumn(6, "출발동(고객)", LVCFMT_LEFT,  110);
	m_wndReport.InsertColumn(7, "도착동(고객)", LVCFMT_LEFT, 90);
	m_wndReport.InsertColumn(8, "기사(번호)", LVCFMT_LEFT,  70);
	m_wndReport.InsertColumn(9, "요금", LVCFMT_RIGHT, 45);
	m_wndReport.InsertColumn(10, "추가", LVCFMT_RIGHT, 45); 
	m_wndReport.InsertColumn(11, "할인", LVCFMT_RIGHT, 45);	
	m_wndReport.InsertColumn(12, "차량", LVCFMT_LEFT,  38);
	m_wndReport.InsertColumn(13, "적요", LVCFMT_LEFT,  110);
	m_wndReport.InsertColumn(14, "접수자", LVCFMT_LEFT,  60);

	m_wndReport.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
		LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE);

	m_wndReport.Populate();

	RefreshList();

	m_edtSearchStart.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtSearchDest.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtSearchEtc.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtSearchManager.SetMyFont("맑은 고딕", 15, FW_BOLD);

	m_edtSearchStart.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "출발지");
	m_edtSearchDest.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "도착지");
	m_edtSearchEtc.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "적 요");
	m_edtSearchManager.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "담 당");

	m_wndReport.LoadReportOrder("CHistoryDlg", "m_List_q");

	m_Magnetic.SetInfo(this, m_pwndParent, CLASS_NAME);
	m_Magnetic.AttachTo();

	ShowWindow(SW_SHOW);
	OnSize(0xFF, 0, 0);

	m_bFirstLoad = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CHistoryDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CHistoryDlg::Clear()
{
	m_mapCusCharge.clear();
	DeleteAllItems();
}

void CHistoryDlg::RefreshList(BOOL bOCNoSearch)
{
	DeleteAllItems();
	m_wndReport.Populate();

	if(m_nOCNo < 1) return;
  
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, m_bShowAll == TRUE ? "select_usage_history_all_1" : "select_usage_history_2014_1");
	//pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nOGNo == 0 ? m_nOCNo : m_nOGNo);
	//pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCompany);
	//pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nOGNo == 0 ? FALSE : TRUE);
	//pCmd.AddParameter(bOCNoSearch);

	pCmd.AddParameter(m_nOCNo);
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(m_nOGNo);
	pCmd.AddParameter(bOCNoSearch);

	
	if(!pRs.Execute(&pCmd)) { 
		return;
	}

	COleDateTime dt;
	CString strCompany, strPhone, strDepart, strName, strDong, strLocation,sOManager;
	long nItem = 0;
	char buffer[10];
	CUSTOMER_CHARGE_MAP::iterator it;
	if(pRs.IsEOF()) return;

	const char *dayofweek[] = {"일", "월", "화", "수", "목", "금", "토"};

	while(!pRs.IsEOF())
	{
		COleDateTime dt1;
		CString strSName, strSDong, strDName, strDDong, strRName;
		long nSNo, nDNo, nState, nRNo, nTNo, nStartDongID, nDestDongID;
		CString strSLocation, strDLocation, sChargeBet, strEtc;
		long nChargeAdd, nChargeBasic, nChargeTrans, nChargeDis, nCarType, nDeposit, nChargeSum;
		long nRCompany, nStartPosX, nStartPosY, nDestPosX, nDestPosY, nPayType;
		CString sOPhone, sODepart, strSPhone, strDPhone, strWName;
		long nOTelID, nSTelID, nDTelID, nOCNo, nCompany;
		CString strSAddress, strDAddress;

		pRs.GetFieldValue("dt1", dt1);
		pRs.GetFieldValue("sSName", strSName);
		pRs.GetFieldValue("sSDong", strSDong);
		pRs.GetFieldValue("nSCNo", nSNo);
		pRs.GetFieldValue("sDName", strDName);
		pRs.GetFieldValue("sDDong", strDDong);
		pRs.GetFieldValue("nDCNo", nDNo);
		pRs.GetFieldValue("sRName", strRName);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("sSDetail", strSLocation);
		pRs.GetFieldValue("sDDetail", strDLocation);
		pRs.GetFieldValue("sSPhone", strSPhone);
		pRs.GetFieldValue("sDPhone", strDPhone);

		pRs.GetFieldValue("nStartDongID", nStartDongID);
		pRs.GetFieldValue("nDestDongID", nDestDongID);

		pRs.GetFieldValue("nChargeSum", nChargeSum);
		pRs.GetFieldValue("sChargeBet", sChargeBet);
		pRs.GetFieldValue("nChargeAdd", nChargeAdd);
		pRs.GetFieldValue("nChargeBasic", nChargeBasic);
		pRs.GetFieldValue("nChargeTrans", nChargeTrans);
		pRs.GetFieldValue("nChargeDis", nChargeDis);
		pRs.GetFieldValue("nCarType", nCarType);
		pRs.GetFieldValue("nDeposit", nDeposit);
		pRs.GetFieldValue("sEtc", strEtc);
		pRs.GetFieldValue("nRCompany", nRCompany);
		pRs.GetFieldValue("sOManager", sOManager);

		pRs.GetFieldValue("nStartPosX", nStartPosX);
		pRs.GetFieldValue("nStartPosY", nStartPosY);
		pRs.GetFieldValue("nDestPosX", nDestPosX);
		pRs.GetFieldValue("nDestPosY", nDestPosY);

		pRs.GetFieldValue("nPayType", nPayType);
		pRs.GetFieldValue("sOPhone", sOPhone);
		pRs.GetFieldValue("sODepart", sODepart);
		
		pRs.GetFieldValue("nOTelID", nOTelID);
		pRs.GetFieldValue("nSTelID", nSTelID);
		pRs.GetFieldValue("nDTelID", nDTelID);

		pRs.GetFieldValue("nOCNo", nOCNo);
		pRs.GetFieldValue("sWName", strWName); 
		pRs.GetFieldValue("sSAddress", strSAddress);
		pRs.GetFieldValue("sDAddress", strDAddress);
		pRs.GetFieldValue("nCompany", nCompany);
				
		if(dt1 == NULL) dt1 = COleDateTime::GetCurrentTime();
	
		ST_HISTORY_ITEM_INFO3 *pItem = new ST_HISTORY_ITEM_INFO3;
		pItem->nOCNo = nOCNo;
		pItem->nSNo = nSNo;
		pItem->nDNo = nDNo;
		pItem->nTNo = nTNo;
		pItem->nStartDongID = nStartDongID;
		pItem->nDestDongID = nDestDongID;
		pItem->strChargeBet = sChargeBet;
		pItem->nCarType = nCarType;
		pItem->nChargeAdd = nChargeAdd;
		pItem->nChargeBasic = nChargeBasic;
		pItem->nChargeTrans = nChargeTrans;
		pItem->nChargeDis = nChargeDis;
		pItem->nChargeSum = nChargeSum;
		pItem->nDeposit = nDeposit;
		pItem->nState = nState;
		pItem->strEtc = strEtc;
		pItem->nRNo = nRNo;
		pItem->nRCompany = nRCompany;
		pItem->dt1 = dt1;
		pItem->nStartPosX = nStartPosX;
		pItem->nStartPosY = nStartPosY;
		pItem->nDestPosX = nDestPosX;
		pItem->nDestPosY = nDestPosY;
		pItem->nPayType = nPayType;
		pItem->strOPhone = sOPhone;
		pItem->strODepart = sODepart;
		pItem->nOTelID = nOTelID;
		pItem->nSTelID = nSTelID;
		pItem->nDTelID = nDTelID;
		
		pItem->strSName = strSName;		
		pItem->strSPhone = strSPhone;
		pItem->strSDetail = strSLocation;
		pItem->strSDong = strSDong;

		pItem->strDName = strDName;
		pItem->strDPhone = strDPhone;		
		pItem->strDDetail = strDLocation;		
		pItem->strDDong = strDDong;

		pItem->strSAddress = strSAddress;
		pItem->strDAddress = strDAddress;

	
		CString strSTemp, strDTemp;
		if(nSNo != 0)
			strSTemp = strSDong + "(" + strSName +")";
		else {
			strSTemp = strSDong;
		}

		if(nDNo != 0)
			strDTemp = strDDong + "(" + strDName + ")";
		else {
			strDTemp = strDDong;
		}
		
		BOOL bSpecialDate, bViewNotMile = FALSE;		

		CString strMyDate = GetMyDateString(pItem->dt1, FALSE, &bSpecialDate);
		strMyDate += bSpecialDate ? pItem->dt1.Format("  %H:%M") : pItem->dt1.Format(" %H:%M");
		strMyDate += "(" + CString(dayofweek[pItem->dt1.GetDayOfWeek() - 1]) + ")";

		m_wndReport.InsertItem(nItem, ltoa(nItem + 1, buffer, 10), -1, 0);
		m_wndReport.SetItemText(nItem, 1, strMyDate);
		m_wndReport.SetItemText(nItem, 2, m_ci.GetBranchName(nCompany));
		m_wndReport.SetItemText(nItem, 3, GetStateString(nState));
		m_wndReport.SetItemText(nItem, 4, GetPayTypeFromLong(nPayType, TRUE));
		m_wndReport.SetItemText(nItem, 5, sOManager);
		m_wndReport.SetItemText(nItem, 6, strSTemp);
		m_wndReport.SetItemText(nItem, 7, strDTemp);

		if(m_ci.GetShareCode1(nRCompany) != m_ci.m_nShareCode1)
			strRName = "ⓒ" + strRName + "(" + ltoa(nRNo, buffer, 10) + ")";
		else
			strRName = strRName + "(" + ltoa(nRNo, buffer, 10) + ")";

		m_wndReport.SetItemText(nItem, 8, strRName);
		m_wndReport.SetItemText(nItem, 9, GetMyNumberFormat(nChargeSum));
		m_wndReport.SetItemText(nItem, 10, GetMyNumberFormat(nChargeAdd));
		m_wndReport.SetItemText(nItem, 11, GetMyNumberFormat(nChargeDis));
		m_wndReport.SetItemText(nItem, 12, ::GetCarTypeFromLong(nCarType));
		m_wndReport.SetItemText(nItem, 13, strEtc);
		m_wndReport.SetItemText(nItem, 14, strWName);
		m_wndReport.SetItemData(nItem++, (DWORD_PTR)pItem);

		pRs.MoveNext();
	}

	pRs.Close();
	m_wndReport.Populate();

	ListFilter();
}

void CHistoryDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int index = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	if(index == -1) return;

	ST_HISTORY_ITEM_INFO3 *pItem = NULL;//new HISTORY_ITEM_INFO2;

	pItem = (ST_HISTORY_ITEM_INFO3*)m_wndReport.GetItemData(index);

	if(pItem == NULL)
		return;

	if(!(nCol == LIST_START_COL || nCol == LIST_DEST_COL || 
			nCol == LIST_ETC_COL || nCol == LIST_RIDER_COL || nCol == LIST_ALL_COL))
		return;

	CString strStartDong = m_wndReport.GetItemText(index, LIST_START_COL);
	CString strDestDong = m_wndReport.GetItemText(index, LIST_DEST_COL);

	strStartDong.Replace("(", "");
	strStartDong.Replace(")", "");
	strDestDong.Replace("(", "");
	strDestDong.Replace(")", "");

	if(nCol == LIST_ALL_COL)
	{
		SetPlaceInfoFromCol(LIST_START_COL, pItem);
		SetPlaceInfoFromCol(LIST_DEST_COL, pItem);
		
		//m_pRcpDlg->m_cmbCarType.SetCurSel(pItem->nCarType);
		m_pRcpDlg->SetCarTypeNew(pItem->nCarType);
		m_pRcpDlg->m_EDT_CHARGE_SUM.pEdit->SetWindowText(::GetMyNumberFormat(pItem->nChargeSum));
		m_pRcpDlg->m_EDT_CHARGE_BASIC.pEdit->SetWindowText(::GetMyNumberFormat(pItem->nChargeBasic));
		m_pRcpDlg->m_EDT_CHARGE_ADD.pEdit->SetWindowText(::GetMyNumberFormat(pItem->nChargeAdd));
		m_pRcpDlg->m_EDT_CHARGE_TRANS.pEdit->SetWindowText(::GetMyNumberFormat(pItem->nChargeTrans));
		m_pRcpDlg->m_EDT_CHARGE_DIS.pEdit->SetWindowText(::GetMyNumberFormat(pItem->nChargeDis));
		m_pRcpDlg->m_edtDeposit.SetWindowText(::GetMyNumberFormat(pItem->nDeposit));
		m_pRcpDlg->m_EDT_ETC.pEdit->SetWindowText(pItem->strEtc);
		m_pRcpDlg->m_EDT_ETC.pEdit->SetFocus();
		m_pRcpDlg->GetSectionCharge(FALSE,  (m_pRcpDlg->m_nInitItem > 0) ? m_pRcpDlg->m_nModifyPoiConfirmCharge : FALSE);
	}
	else if(nCol == LIST_START_COL || nCol == LIST_DEST_COL)
	{
		if(nCol == LIST_START_COL)
			SetPlaceInfoFromCol(LIST_START_COL, pItem); 
		else
			SetPlaceInfoFromCol(LIST_DEST_COL, pItem);
	
		m_pRcpDlg->m_EDT_DEST.pEdit->SetFocus();
		m_pRcpDlg->GetSectionCharge(FALSE,  (m_pRcpDlg->m_nInitItem > 0) ? m_pRcpDlg->m_nModifyPoiConfirmCharge : FALSE);
	}
	else if(nCol == LIST_ETC_COL)
	{
		m_pRcpDlg->m_EDT_ETC.pEdit->SetWindowText(pItem->strEtc);
	}
	else if(nCol == LIST_RIDER_COL)
	{
		ST_HISTORY_ITEM_INFO3 *pItem = (ST_HISTORY_ITEM_INFO3*)m_wndReport.GetItemData(index);
		LU->ShowRiderInfoDlg(pItem->nRCompany, pItem->nRNo, -1, -1, "");
	}
}

void CHistoryDlg::SetPlaceInfoFromCol(int nCol,  ST_HISTORY_ITEM_INFO3 *pItem)
{
	if(nCol == LIST_START_COL)
	{
		if(pItem->nSNo > 0)
			if(m_pRcpDlg->m_pStart->SearchCustomerCNo(pItem->nSNo, TRUE, TRUE, pItem->nSTelID))
				return;

		if(pItem->nStartDongID > 0)
		{
			BOOL bDetailPos = LU->IsDetailPos(pItem->nStartDongID, pItem->nStartPosX, pItem->nStartPosY);

			m_pRcpDlg->m_pStart->SetData(pItem->nStartDongID, pItem->nStartPosX, pItem->nStartPosY, 
						"", "",  // 부서 담당 히스토리에 없어 일단 보류
						(IsDetailAddressName(nCol, pItem) ) ? pItem->strSPhone : "", 
						(IsDetailAddressName(nCol, pItem) ) ? pItem->strSDetail : "", 
						pItem->nSNo ,0, "", 0,  "" , "",  // CNo, CustomerID, strUserID, nGNo, strMemo,strMobile
						pItem->strSDong,				  // 	
						(IsDetailAddressName(nCol, pItem) ) ? pItem->strSName	: "",
						bDetailPos ,					  // BOOL bHasDetailPos, CString strAddress, long nTelID,
						pItem->strSAddress,
						pItem->nSTelID, 
						0, 0, 0, 0, 0);  // nUsecount, nCancelCount,, nMileageBalance, bTempCNo, bEditMode						
						
		}
		else
			m_pRcpDlg->m_pStart->SetDataOnlyText(pItem->strSName, pItem->strSDong);
	}
	else if(nCol == LIST_DEST_COL)
	{
		if(pItem->nDNo > 0)
			if(m_pRcpDlg->m_pDest->SearchCustomerCNo(pItem->nDNo, TRUE, TRUE, pItem->nDTelID))
				return;

		if(pItem->nDestDongID > 0)
		{
			BOOL bDetailPos = LU->IsDetailPos(pItem->nDestDongID, pItem->nDestPosX, pItem->nDestPosY);

			m_pRcpDlg->m_pDest->SetData(pItem->nDestDongID, pItem->nDestPosX, pItem->nDestPosY, 
					"", "",  // 부서 담당 히스토리에 없어 일단 보류
					(IsDetailAddressName(nCol, pItem) ) ? pItem->strDPhone : "", 
					(IsDetailAddressName(nCol, pItem) ) ? pItem->strDDetail : "", 
					pItem->nDNo ,0, "", 0,  "" , "",  // CNo, CustomerID, strUserID, nGNo, strMemo,strMobile
					pItem->strDDong,				  // 	
					(IsDetailAddressName(nCol, pItem) ) ? pItem->strDName	: "",
					bDetailPos ,					  // BOOL bHasDetailPos, CString strAddress, long nTelID,
					pItem->strDAddress,
					pItem->nDTelID, 
					0, 0, 0, 0, 0);  // nUsecount, nCancelCount,, nMileageBalance, bTempCNo, bEditMode	

			//m_pRcpDlg->m_pDest->SetData(pItem->nDestDongID, pItem->nDestPosX, pItem->nDestPosY, 
			//			"", "", 
			//			pItem->strSPhone, pItem->strDDetail, pItem->nDNo,
			//			0 , // CustomerID     // 퀵라인 수정요청
			//			"", // userID
			//			0,  // nGNo
			//			"", // strMemo
			//			"",  // strPhone2
			//			pItem->strDDong, // 	
			//			pItem->strDName, //strAddress,
			//			bDetailPos , // pItem->nSTelID, // nTelID
			//			 "",
			//			pItem->nDTelID, // bCredit,
			//			0,0,0,0);  // nUsecount, nCancelCount,, nMileageBalance, bTempCNo, bEditMode
						/*"", "", "", "", pItem->nDNo, 0, "", 0, "", "", pItem->strDDong, "", bDetailPos, 
						"", pItem->nDTelID, 0, 0, 0, 0);*/
		}
		else
			m_pRcpDlg->m_pDest->SetDataOnlyText(pItem->strDName, pItem->strDDong);
	}
}

BOOL CHistoryDlg::IsDetailAddressName(int nCol ,ST_HISTORY_ITEM_INFO3 *pItem)
{

	return TRUE;

	if(m_pRcpDlg)
		if(m_pRcpDlg->m_pBi->nHistoryDetailAllView)  // 무조건 다보여주기
			return TRUE;

	if(nCol == LIST_START_COL)
	{
		if(pItem->strSName.GetLength() > 0 && pItem->strSPhone.GetLength() > 0 && pItem->strSDetail.GetLength() > 0)
			return TRUE;
	}
	else
	{
		if(pItem->strDName.GetLength() > 0 && pItem->strDPhone.GetLength() > 0 && pItem->strDDetail.GetLength() > 0)
			return TRUE;

	}
	return FALSE;

}

void CHistoryDlg::OnBnClickedCancelBtn()
{
	this->ShowWindow(SW_HIDE);
}

void CHistoryDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CMyDialog::OnLButtonDown(nFlags, point);
}

void CHistoryDlg::OnEnChangeSearchStartEdit()
{
	ListFilter();
}

void CHistoryDlg::OnEnChangeSearchDestEdit()
{
	ListFilter();
}

void CHistoryDlg::OnEnChangeSearchEtcEdit()
{
	ListFilter();
}

void CHistoryDlg::ListFilter()
{ 
	CString strSearchStart; m_edtSearchStart.GetWindowText(strSearchStart);
	CString strSearchDest; m_edtSearchDest.GetWindowText(strSearchDest);
	CString strSearchEtc; m_edtSearchEtc.GetWindowText(strSearchEtc);
	CString strSearchManager; m_edtSearchManager.GetWindowText(strSearchManager);

	CXTPGridColumn *pColumn = NULL;
	CXTPGridRecords *pRecords = m_wndReport.GetRecords();
	CString sStartGugun = "", sDestGugun = "";
	for(int i=0; i<pRecords->GetCount(); i++)
	{
	    CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString strStart = pRecord->GetItem(LIST_START_COL)->GetCaption(pColumn);
		CString strDest = pRecord->GetItem(LIST_DEST_COL)->GetCaption(pColumn);
		CString strEtc = pRecord->GetItem(LIST_ETC_COL)->GetCaption(pColumn);
		CString strManager = pRecord->GetItem(LIST_MANAGER_COL)->GetCaption(pColumn);

		BOOL bVisible = TRUE;

		if((strStart.Find(strSearchStart) < 0) && (strSearchStart != "") )
			bVisible = FALSE;

		if((strDest.Find(strSearchDest) < 0) && (strSearchDest != "") )
			bVisible = FALSE;

		if((strEtc.Find(strSearchEtc) < 0) && (strSearchEtc != ""))
			bVisible = FALSE;

		if((strManager.Find(strSearchManager) < 0) && (strSearchManager != ""))
			bVisible = FALSE;

		pRecord->SetVisible(bVisible);
	}

	m_wndReport.Populate();
}


void CHistoryDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	CPoint pt;
	GetCursorPos(&pt);

	CRect rtReport;
	m_wndReport.GetWindowRect(&rtReport);

	if(rtReport.PtInRect(pt))
	{
		BCMenu rMenu;
		rMenu.LoadMenu(IDR_PHONE_MENU);

		BCMenu* pRMenu = (BCMenu*)rMenu.GetSubMenu(1);
		pRMenu->AppendMenu(MF_BYCOMMAND, IDC_MOVE_DOWN_BTN, m_bMoveDown ? "접수창 옆으로 이동" : "접수창 아래에 붙이기");

		if(m_bMoveDown)
		{
			pRMenu->AppendMenu(MF_BYCOMMAND, ID_SIZE_DOWN, "(-) 리스트 높이 한칸 줄이기");
			pRMenu->AppendMenu(MF_BYCOMMAND, ID_SIZE_UP, "(+) 리스트 높이 한칸 늘리기");
		}

		pRMenu->AppendMenu(MF_BYCOMMAND, ID_EXCEL, "엑셀로 보기");
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);	
	}
}

void CHistoryDlg::OnCurOrderState()
{
	long nSel = m_wndReport.GetNextItem(-1, LVNI_SELECTED);
	if(nSel == -1) return;

	ST_HISTORY_ITEM_INFO3 *pItem = NULL;//new HISTORY_ITEM_INFO2;
	pItem = (ST_HISTORY_ITEM_INFO3*)m_wndReport.GetItemData(nSel);

	COleDateTime dtCur = COleDateTime::GetCurrentTime();

	if((pItem->dt1.GetYear() == dtCur.GetYear()) &&
		(pItem->dt1.GetMonth() == dtCur.GetMonth()) &&
		(pItem->dt1.GetDay() == dtCur.GetDay()))
		LU->OpenCurOrderState(pItem->nTNo);
	else
		MessageBox("금일오더만 확인 하실수 있습니다", "확인", MB_ICONINFORMATION);
}

BOOL CHistoryDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->hwnd == this->GetSafeHwnd())
	{
		if(pMsg->message == WM_LBUTTONDOWN)
			m_bLButtonDown = TRUE;
		else if(pMsg->message == WM_LBUTTONUP)
			m_bLButtonDown = FALSE;
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CHistoryDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CMyDialog::OnWindowPosChanging(lpwndpos);
	m_Magnetic.PosChanging(lpwndpos);
}

void CHistoryDlg::OnSize(UINT nType, int cx, int cy)
{  
	if(nType != 0xFF)
		CMyDialog::OnSize(nType, cx, cy);

	if(IsWindow(m_wndReport.GetSafeHwnd()))
	{
		CRect rcDlg, rcList;
		GetClientRect(rcDlg);
		m_wndReport.GetWindowRect(rcList);
		ScreenToClient(rcList);

		if(m_bMoveDown)
			rcList = rcDlg;
		else
		{
			rcList.right = rcDlg.right - 1;
			rcList.bottom = rcDlg.bottom - 1; 
		}

		m_wndReport.MoveWindow(rcList);
	}
}

void CHistoryDlg::OnEnChangeSearchManagerEdit()
{
	ListFilter();
}

void CHistoryDlg::OnBnClickedRefreshBtn2()
{
	RefreshList(FALSE);
}

void CHistoryDlg::OnBnClickedMoveDownBtn()
{
	m_bMoveDown = !m_bMoveDown;
	AfxGetApp()->WriteProfileInt("HistoryDlg", "MoveDown", m_bMoveDown);
	m_pRcpDlg->m_pHistoryDlg = NULL;
	m_pRcpDlg->m_bHistoryMoveDown = m_bMoveDown;
	m_pRcpDlg->ShowUsageHistory();
	delete this;
}

void CHistoryDlg::OnSizeDown()
{
	int nHeight = AfxGetApp()->GetProfileInt("HistoryDlg", "Height", 200);
	nHeight = max(nHeight - 25, 120);
	AfxGetApp()->WriteProfileInt("HistoryDlg", "Height", nHeight);
	m_pRcpDlg->m_pHistoryDlg = NULL;
	m_pRcpDlg->ShowUsageHistory(FALSE , TRUE);
	delete this;
}

void CHistoryDlg::OnSizeUp()
{
	int nHeight = AfxGetApp()->GetProfileInt("HistoryDlg", "Height", 200);
	nHeight = min(nHeight + 25, 500);
	AfxGetApp()->WriteProfileInt("HistoryDlg", "Height", nHeight);
	m_pRcpDlg->m_pHistoryDlg = NULL;
	m_pRcpDlg->ShowUsageHistory(FALSE, TRUE);
	delete this;
}

void CHistoryDlg::OnOpenRcpDlg()
{
	CXTPGridRecord *pRecord = m_wndReport.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	ST_HISTORY_ITEM_INFO3 *pItem = (ST_HISTORY_ITEM_INFO3*)m_wndReport.GetItemData(pRecord);

	if(pItem == NULL)
		return;

	CString strsOName = m_pRcpDlg->m_pOrder->GetCompany();

	if(m_nOCNo != pItem->nOCNo)
		strsOName = LU->GetCustomerName(pItem->nOCNo);

	LU->CreateRcpDlg(strsOName, pItem->nTNo, pItem->nState);
}

void CHistoryDlg::OnAddCall()
{
	CXTPGridRecord *pRecord = m_wndReport.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	ST_HISTORY_ITEM_INFO3 *pItem = (ST_HISTORY_ITEM_INFO3*)m_wndReport.GetItemData(pRecord);

	if(pItem == NULL)
		return;

	CString strsOName = m_pRcpDlg->m_pOrder->GetCompany();

	if(m_nOCNo != pItem->nOCNo)
		strsOName = LU->GetCustomerName(pItem->nOCNo);

	LU->AddCall(strsOName, pItem->nTNo, pItem->nState);
}

void CHistoryDlg::OnViewExcel()
{
	if(!POWER_CHECK(1900, "상황 엑셀변환", TRUE))
		return;

	CMyExcel::ToExcel(&m_wndReport);
}	

void CHistoryDlg::OnBnClickedShowAllHistory()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bShowAll = TRUE;
	RefreshList();
	m_bShowAll = FALSE;
}
