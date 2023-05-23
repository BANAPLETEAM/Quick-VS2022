// historyInsungDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "historyInsungDlg.h"
#include "RcpInsungDlg.h"

// ChistoryInsungDlg 대화 상자입니다.

#define  LIST_START_COL 3
#define  LIST_DEST_COL	5

IMPLEMENT_DYNAMIC(ChistoryInsungDlg, CDialog)


//ChistoryInsungDlg::ChistoryInsungDlg(CWnd* pParent /*=NULL*/)
//	: CDialog(ChistoryInsungDlg::IDD, pParent)
//{
//}

ChistoryInsungDlg::ChistoryInsungDlg(UINT nResourceID, CWnd* pParent)
: CDialog(nResourceID, pParent)
{
	m_bMoveDown = FALSE;
	m_pwndParent = pParent;
}

ChistoryInsungDlg::~ChistoryInsungDlg()
{
}

void ChistoryInsungDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SEARCH_START_EDIT, m_edtSearchStart);
	DDX_Control(pDX, IDC_SEARCH_DEST_EDIT, m_edtSearchDest);
	DDX_Control(pDX, IDC_SEARCH_ETC_EDIT, m_edtSearchEtc);

	DDX_Control(pDX, IDC_HISTORY_INSUNG_LIST, m_lstHistory);
}


BEGIN_MESSAGE_MAP(ChistoryInsungDlg, CDialog)

	ON_COMMAND(ID_TO_START, OnToStart)
	ON_COMMAND(ID_TO_DEST, OnToDest)
	ON_COMMAND(ID_RIDER_INFO, OnRiderInfo)
	ON_EN_CHANGE(IDC_SEARCH_START_EDIT, &ChistoryInsungDlg::OnEnChangeSearchStartEdit)
	ON_EN_CHANGE(IDC_SEARCH_DEST_EDIT, &ChistoryInsungDlg::OnEnChangeSearchDestEdit)
	ON_EN_CHANGE(IDC_SEARCH_ETC_EDIT, &ChistoryInsungDlg::OnEnChangeSearchEtcEdit)
	ON_NOTIFY(NM_RCLICK, IDC_HISTORY_INSUNG_LIST, OnNMRClickHistoryList)
	ON_NOTIFY(NM_CLICK, IDC_HISTORY_INSUNG_LIST, OnNMClickHistoryList)
	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_MOVE_DOWN_BTN, &ChistoryInsungDlg::OnBnClickedMoveDownBtn)
	ON_WM_SIZE()
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


// ChistoryInsungDlg 메시지 처리기입니다.

void ChistoryInsungDlg::OnEnChangeSearchStartEdit()
{
	CheckHistoryList();
}

void ChistoryInsungDlg::OnEnChangeSearchDestEdit()
{
	CheckHistoryList();
}

void ChistoryInsungDlg::OnEnChangeSearchEtcEdit()
{
	CheckHistoryList();
}


void ChistoryInsungDlg::OnNMClickHistoryList(NMHDR *pNMHDR, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM* pNMListView = (XTP_NM_REPORTRECORDITEM*)pNMHDR;

	if(!pNMListView->pRow)
		return;

	long nCol = pNMListView->pItem->GetIndex();
	

	if(nCol == 2 || nCol == 3 )
		OnToStart();
	else if(nCol == 4 || nCol == 5 )
		OnToDest();


}
void ChistoryInsungDlg::OnNMRClickHistoryList(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstHistory, pt);
}


void ChistoryInsungDlg::InsertListColumn()
{
	m_lstHistory.InsertColumn(0, "상태", LVCFMT_LEFT, 40);
	m_lstHistory.InsertColumn(1, "접수시간", LVCFMT_LEFT, 80);
	m_lstHistory.InsertColumn(2, "출발지", LVCFMT_LEFT, 80);
	m_lstHistory.InsertColumn(3, "출발동", LVCFMT_LEFT, 50);
	m_lstHistory.InsertColumn(4, "도착위치", LVCFMT_LEFT, 80);
	m_lstHistory.InsertColumn(5, "도착동", LVCFMT_LEFT, 50);
	m_lstHistory.InsertColumn(6, "차량", LVCFMT_LEFT, 40);
	m_lstHistory.InsertColumn(7, "형태", LVCFMT_LEFT, 40);
	m_lstHistory.InsertColumn(8, "요금", LVCFMT_LEFT, 50);
	m_lstHistory.InsertColumn(9, "처리비", LVCFMT_LEFT, 50);
	m_lstHistory.InsertColumn(10, "기사", LVCFMT_LEFT, 40);
	m_lstHistory.InsertColumn(11, "접수처", LVCFMT_LEFT, 70);
	m_lstHistory.InsertColumn(12, "접수자", LVCFMT_LEFT, 50); 
	m_lstHistory.InsertColumn(13, "적요", LVCFMT_LEFT, 120);
	m_lstHistory.InsertColumn(14, "추가", LVCFMT_LEFT, 50);
	m_lstHistory.InsertColumn(15, "할인", LVCFMT_LEFT, 50);
	m_lstHistory.InsertColumn(16, "탁송", LVCFMT_LEFT, 50); 
	m_lstHistory.Populate();  

	m_lstHistory.GetPaintManager()->SetColumnStyle(xtpReportColumnFlat); 
	m_lstHistory.SetGridColor(RGB(0xF0, 0xF0, 0xF0));

}


void ChistoryInsungDlg::DeleteHistoryList()
{
	CXTPGridRecords *pRecords = m_lstHistory.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		ST_HISTORY_ITEM_INFO3 *pItem = (ST_HISTORY_ITEM_INFO3*)m_lstHistory.GetItemData(pRecord);

		if(pItem != NULL)
		{
			delete pItem;
			pItem = NULL;
		}
	}

	m_lstHistory.DeleteAllItems();
}

void ChistoryInsungDlg::RefreshList()
{
	DeleteHistoryList();

	if(m_pRcpInsungDlg->m_pOrder->GetCNo() == 0)
		return;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_usage_history_2014");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_pRcpInsungDlg->m_pOrder->GetGNo() == 0 ? m_pRcpInsungDlg->m_pOrder->GetCNo() : m_pRcpInsungDlg->m_pOrder->GetGNo());
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_pRcpInsungDlg->m_pBi->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_pRcpInsungDlg->m_pOrder->GetGNo() == 0 ? FALSE : TRUE);
	pCmd.AddParameter(TRUE);

	if(!pRs.Execute(&pCmd)) {
		return;
	}

	COleDateTime dt;
	CString strCompany, strPhone, strDepart, strName, strDong, strLocation,sOManager;
	long nItem = 0;
	if(pRs.IsEOF()) return;

	while(!pRs.IsEOF())
	{
		COleDateTime dt1;
		CString strSName, strSDong, strDName, strDDong, strRName;
		long nSNo, nDNo, nState, nRNo, nTNo, nStartDongID, nDestDongID;
		CString strSLocation, strDLocation, sChargeBet, strEtc;
		long nChargeAdd, nChargeBasic, nChargeTrans, nChargeDis, nCarType, nDeposit, nChargeSum;
		long nRCompany, nStartPosX, nStartPosY, nDestPosX, nDestPosY, nPayType;
		CString sOPhone, sODepart, strWName,strSPhone, strDPhone;
		long nOTelID, nSTelID, nDTelID, nOCNo, nCompany, nWayType;

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
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nWayType", nWayType);
		pRs.GetFieldValue("sWName", strWName);


		pRs.GetFieldValue("nOCNo", nOCNo);

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
		pItem->strSDong = strSDong;
		pItem->strSPhone = strSPhone;
		pItem->strSDetail = strSLocation;

		pItem->strDName = strDName;
		pItem->strDDong = strDDong;
		pItem->strDPhone = strDPhone;
		pItem->strDDetail = strDLocation;

		CString strData =  dt1.Format("%m:%d %H:%M(%a)");

		m_lstHistory.InsertItem(nItem, LF->GetStateString(nState));
		m_lstHistory.SetItemText(nItem, 1, strData);
		m_lstHistory.SetItemText(nItem, 2, strSName);
		m_lstHistory.SetItemText(nItem, 3, strSDong);
		m_lstHistory.SetItemText(nItem, 4, strDName);
		m_lstHistory.SetItemText(nItem, 5, strDDong);
		m_lstHistory.SetItemText(nItem, 6, LF->GetCarTypeFromLong(nCarType));
		m_lstHistory.SetItemText(nItem, 7, LF->GetWayTypeFromLong(nWayType));
		m_lstHistory.SetItemText(nItem, 8, LF->GetMyNumberFormat(nChargeSum));
		m_lstHistory.SetItemText(nItem, 9, LF->GetMyNumberFormat(nDeposit));

		CString strTemp = "";

		if(nRCompany == 0) strTemp = "";
		else if(m_ci.IsChildCompany(nRCompany))
			strTemp = LF->GetStringFromLong(nRNo);
		else
			strTemp = "ⓒ" + LF->GetStringFromLong(nRNo);

		m_lstHistory.SetItemText(nItem, 10, strTemp);
		m_lstHistory.SetItemText(nItem, 11, m_ci.GetCompanyName(nCompany));
		m_lstHistory.SetItemText(nItem, 12, strWName);
		m_lstHistory.SetItemText(nItem, 13, strEtc);
		m_lstHistory.SetItemText(nItem, 14, LF->GetMyNumberFormat(nChargeBasic));
		m_lstHistory.SetItemText(nItem, 15, LF->GetMyNumberFormat(nChargeAdd));
		m_lstHistory.SetItemText(nItem, 16, LF->GetMyNumberFormat(nChargeTrans));
		m_lstHistory.SetItemLong(nItem, nState);
		m_lstHistory.SetItemData(nItem++, (DWORD)pItem);

		pRs.MoveNext();
	}

	pRs.Close();
	m_lstHistory.Populate();
}

void ChistoryInsungDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if(pWnd->GetSafeHwnd() == m_lstHistory.GetSafeHwnd())
	{
		//ClientToScreen(&point);

		CPoint pt = point;

		m_lstHistory.ScreenToClient(&point);

		CXTPGridRow * pRow = m_lstHistory.HitTest(point);

		if(pRow == NULL)
			return;

		CRect rcCol; 

		CXTPGridColumn *pCol = NULL;
		pRow->HitTest(point, &rcCol, &pCol);

		if(pCol == NULL)
			return;

		if(pCol->GetIndex() == 2 ||
			pCol->GetIndex() == 3)
		{
			//m_nFromSource = 0;
			//ToOrder(TRUE);
		}
		else if(pCol->GetIndex() == 4 ||
			pCol->GetIndex() == 5)
		{
			//m_nFromSource = 1;
			//ToOrder(FALSE);
		}
		else
			return; 

		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU_1);
		CMenu *pRMenu=rMenu.GetSubMenu(4);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);	
	}
}


void ChistoryInsungDlg::OnToStart()
{
	ToOrder(TRUE);
}

void ChistoryInsungDlg::OnToDest()
{
	ToOrder(FALSE);
}

void ChistoryInsungDlg::ToOrder(BOOL bToStart)
{
	CXTPGridRecord *pRecord = m_lstHistory.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	ST_HISTORY_ITEM_INFO3 *pItem = NULL;//new HISTORY_ITEM_INFO2;

	pItem = (ST_HISTORY_ITEM_INFO3*)m_lstHistory.GetItemData(pRecord);

	if(pItem == NULL)
		return;

	CRcpPlaceInfo *pPlace = bToStart == TRUE ? m_pRcpInsungDlg->m_pStart : m_pRcpInsungDlg->m_pDest;
	int nCol = bToStart ? LIST_START_COL : LIST_DEST_COL;

	if(bToStart)
	{
		if(pItem->nSNo > 0)
			if(pPlace->SearchCustomerCNo(pItem->nSNo, TRUE, TRUE, pItem->nSTelID))
				return;

		if(pItem->nStartDongID > 0)
		{
			BOOL bDetailPos = LU->IsDetailPos(pItem->nStartDongID, pItem->nStartPosX, pItem->nStartPosY);
			/*pPlace->SetData(pItem->nStartDongID, pItem->nStartPosX, pItem->nStartPosY, 
				"", "", "", "", pItem->nSNo, 0, "", 0, "", "", pItem->strSDong, "", bDetailPos,
				"", pItem->nSTelID, 0, 0, 0, 0);*/
			pPlace->SetData(
			pItem->nStartDongID, pItem->nStartPosX, pItem->nStartPosY, 
				"", "",  // 부서 담당 히스토리에 없어 일단 보류
				(IsDetailAddressName(nCol, pItem) ) ? pItem->strSPhone : "", 
				(IsDetailAddressName(nCol, pItem) ) ? pItem->strSDetail : "", 
				pItem->nSNo ,0, "", 0,  "" , "",  // CNo, CustomerID, strUserID, nGNo, strMemo,strMobile
				pItem->strSDong,				  // 	
				(IsDetailAddressName(nCol, pItem) ) ? pItem->strSName	: "",
				bDetailPos ,					  // BOOL bHasDetailPos, CString strAddress, long nTelID,
				(IsDetailAddressName(nCol, pItem) ) ? m_pRcpInsungDlg->GetDisplayDongAndAddress(pItem->nStartDongID, pItem->strSDong, "") : "",
				pItem->nSTelID, 
				0, 0, 0, 0, 0);

		}
		else
			pPlace->SetDataOnlyText(pItem->strSName, pItem->strSDong);
	}
	else
	{
		if(pItem->nDNo > 0)
			if(pPlace->SearchCustomerCNo(pItem->nDNo, TRUE, TRUE, pItem->nDTelID))
				return;

		if(pItem->nDestDongID > 0)
		{
			BOOL bDetailPos = LU->IsDetailPos(pItem->nDestDongID, pItem->nDestPosX, pItem->nDestPosY);
			/*pPlace->SetData(pItem->nDestDongID, pItem->nDestPosX, pItem->nDestPosY, 
				"", "", "", "", pItem->nDNo, 0, "", 0, "", "", pItem->strDDong, "", bDetailPos, 
				"", pItem->nDTelID, 0, 0, 0, 0);*/
			pPlace->SetData(
			pItem->nDestDongID, pItem->nDestPosX, pItem->nDestPosY, 
				"", "",  // 부서 담당 히스토리에 없어 일단 보류
				(IsDetailAddressName(nCol, pItem) ) ? pItem->strDPhone : "", 
				(IsDetailAddressName(nCol, pItem) ) ? pItem->strDDetail : "", 
				pItem->nDNo ,0, "", 0,  "" , "",  // CNo, CustomerID, strUserID, nGNo, strMemo,strMobile
				pItem->strDDong,				  // 	
				(IsDetailAddressName(nCol, pItem) ) ? pItem->strDName	: "",
				bDetailPos ,					  // BOOL bHasDetailPos, CString strAddress, long nTelID,
				(IsDetailAddressName(nCol, pItem) ) ? m_pRcpInsungDlg->GetDisplayDongAndAddress(pItem->nDestDongID, pItem->strDDong, "") : "",
				pItem->nDTelID, 
				0, 0, 0, 0, 0);
		}
		else
			pPlace->SetDataOnlyText(pItem->strDName, pItem->strDDong);

	}

}


BOOL ChistoryInsungDlg::IsDetailAddressName(int nCol ,ST_HISTORY_ITEM_INFO3 *pItem)
{

	if(nCol == LIST_START_COL)
	{
		if(pItem->strSName.GetLength() > 0 && pItem->strSPhone.GetLength() && pItem->strSDetail.GetLength() > 0)
			return TRUE;
	}
	else
	{
		if(pItem->strDName.GetLength() > 0 && pItem->strDPhone.GetLength() && pItem->strDDetail.GetLength() > 0)
			return TRUE;

	}
	return FALSE;

}


void ChistoryInsungDlg::OnRiderInfo()
{
	CXTPGridRecord *pRecord = m_lstHistory.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	ST_HISTORY_ITEM_INFO3 *pItem = (ST_HISTORY_ITEM_INFO3*)m_lstHistory.GetItemData(pRecord);

	if(pItem->nRNo > 0 && pItem->nRCompany > 0)
		LU->ShowRiderInfoDlg(pItem->nRCompany, pItem->nRNo);
}


void ChistoryInsungDlg::CheckHistoryList()
{
	CString strStartSearch; m_edtSearchStart.GetWindowText(strStartSearch);
	CString strDestSearch; m_edtSearchDest.GetWindowText(strDestSearch);
	CString strEtcSearch; m_edtSearchEtc.GetWindowText(strEtcSearch);

	CXTPGridRecords *pRecords = m_lstHistory.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strSName = pRecord->GetItem(2)->GetCaption(NULL);
		CString strSDong = pRecord->GetItem(3)->GetCaption(NULL);
		CString strDDong = pRecord->GetItem(5)->GetCaption(NULL);
		CString strEtc = pRecord->GetItem(13)->GetCaption(NULL);

		BOOL bVisible = TRUE;

		if(((strSName.Find(strStartSearch) < 0) && (strStartSearch != "")) &&
			((strSDong.Find(strStartSearch) < 0) && (strStartSearch != "")) )
			bVisible = FALSE;

		if((strDDong.Find(strDestSearch) < 0) && (strDestSearch != "") )
			bVisible = FALSE;

		if((strEtc.Find(strEtcSearch) < 0) && (strEtcSearch != ""))
			bVisible = FALSE;

		pRecord->SetVisible(bVisible);
	}

	m_lstHistory.Populate();
}
BOOL ChistoryInsungDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InsertListColumn();

	m_Magnetic.SetInfo(this, m_pwndParent, "ChistoryInsungDlg");
	m_Magnetic.AttachTo();

	m_bMoveDown = AfxGetApp()->GetProfileInt("HistoryDlg", "MoveDown", 0);

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void ChistoryInsungDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(!m_pRcpInsungDlg->m_bHistoryMoveDown)
		PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
 
	CDialog::OnLButtonDown(nFlags, point);
}

void ChistoryInsungDlg::OnBnClickedMoveDownBtn()
{
	m_bMoveDown = !m_bMoveDown;
	AfxGetApp()->WriteProfileInt("HistoryDlg", "MoveDown", m_bMoveDown);
	m_pRcpInsungDlg->m_pHistoryInsung = NULL;
	m_pRcpInsungDlg->m_bHistoryMoveDown = m_bMoveDown;
	m_pRcpInsungDlg->ShowUsageHistory();
	delete this;
}

void ChistoryInsungDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if(m_lstHistory.GetSafeHwnd())
	{
		CRect rcForm, rcList;
		GetClientRect(rcForm);
		m_lstHistory.GetWindowRect(rcList);
		ScreenToClient(rcList);

		rcList.right = rcForm.right - 1;
		rcList.bottom = rcForm.bottom - 1;
		m_lstHistory.MoveWindow(rcList);
	}
}

void ChistoryInsungDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CDialog::OnWindowPosChanging(lpwndpos);

	m_Magnetic.PosChanging(lpwndpos);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
