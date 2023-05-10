

#include "stdafx.h"
#include "resource.h"
#include "RiderMsgDlg.h"
#include "StaffForm13.h"
#include "AllocateLimitAllApplyDlg.h"
#include "WorkStopMemoDlg.h"
#include "AllocateLimitDlg1.h"
#include "RcpView.h"
#include "LockAllocateDlg.h"
#include "TimeLimitDlg.h"
#include "WorkTimeDlg.h"
#include "ElapseLimitDlg.h"
#include "InsuranceDateDlg.h"
#include "InsuranceInfoDlg.h"

//#include "AllocateLimitDlg.h"

// CStaffPage13 대화 상자입니다.

IMPLEMENT_DYNCREATE(CStaffPage13, CMyFormView)
CStaffPage13::CStaffPage13()	: CMyFormView(CStaffPage13::IDD)

, m_strRider(_T(""))
, m_sPenalty(_T(""))
, m_sMount(_T(""))
, m_sInsurance(_T(""))
{
	m_dtEnter = COleDateTime::GetCurrentTime();
	m_dtOut = COleDateTime::GetCurrentTime();
}

CStaffPage13::~CStaffPage13()
{

}

void CStaffPage13::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INFO_LIST, m_List);
	DDX_Control(pDX, IDC_EDIT_NAME, m_RiderEdit);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strRider);
	DDX_Text(pDX, IDC_PENALTY_STC, m_sPenalty);
	DDX_Text(pDX, IDC_MOUNT_STC, m_sMount);
	DDX_Text(pDX, IDC_INSURANCE_STC, m_sInsurance);
	DDX_Control(pDX, IDC_SEARCH_BTN, m_btnAllSearch);
	//	DDX_Control(pDX, IDC_MODIFY_BTN, m_btnModify);
	DDX_Control(pDX, IDC_ALLAPPLY_BTN, m_btnAllAppy);
	DDX_Control(pDX, IDC_RELEASE_BTN, m_btnLimittOff);
	DDX_Control(pDX, IDC_AMOUNT_STATIC, m_stcAmount);
	DDX_Control(pDX, IDC_INSURANCE_STATIC, m_stcInsurance);
	DDX_Control(pDX, IDC_CANCEL_COUNT_STATIC, m_stcCancelCount);
	DDX_Control(pDX, IDC_SEARCH_WORD_STATIC, m_stcSearchWord);
}

BEGIN_MESSAGE_MAP(CStaffPage13, CMyFormView)
	//ON_WM_SIZE()

	ON_COMMAND(ID_WORK_OK, OnWorkOk)
	ON_COMMAND(ID_WORK_STOP, OnWorkStop)
	ON_COMMAND(ID_WORK_TIME, OnWorkTime)
	ON_COMMAND(ID_ALLOC_PDA, OnAllocPDA)
	ON_COMMAND(ID_ALLOC_SMS, OnAllocSMS)
	ON_COMMAND(ID_SHARE_LIMIT_0, OnShareLimit0)
	ON_COMMAND(ID_SHARE_LIMIT_1, OnShareLimit1)
	ON_COMMAND(ID_SHARE_LIMIT_2, OnShareLimit2)
	ON_COMMAND(ID_LOCK_APPLY, OnLockApply)
	ON_COMMAND(ID_LOCK_NOT_APPLY, OnLockNotApply)
	ON_COMMAND(ID_TIME_LIMIT_APPLY, OnTimeLimitApply)
	ON_COMMAND(ID_TIME_LIMIT_NOT_APPLY, OnTimeLimitNotApply)
	ON_COMMAND(ID_SERVICE_RENT_LIMIT_APPLY, OnServiceRentLimitApply)
	ON_COMMAND(ID_SERVICE_RENT_LIMIT_NOT_APPLY, OnServiceRentLimitNotApply)
	ON_COMMAND(ID_ELAPSE_LIMIT_ALLOCATE_LOCAL_APPLY, OnElapseLimitAllocateLocalApply)
	ON_COMMAND(ID_ELAPSE_LIMIT_ALLOCATE_LOCAL_NOT_APPLY, OnElapseLimitAllocateLocalNotApply)
	ON_COMMAND(ID_ELAPSE_LIMIT_ALLOCATE_GLOBAL_APPLY, OnElapseLimitAllocateGlobalApply)
	ON_COMMAND(ID_ELAPSE_LIMIT_ALLOCATE_GLOBAL_NOT_APPLY, OnElapseLimitAllocateGlobalNotApply)
	ON_COMMAND(ID_INSURANCE_APPLY, OnInsuranceApply)
	ON_COMMAND(ID_INSURANCE_NOT_APPLY, OnInsuranceNotApply)
	ON_COMMAND(ID_INSURANCE_DATE, OnInsuranceDate)
	ON_COMMAND(ID_INSURANCE_COMPANY, OnInsuranceCompany)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_COMMAND(ID_MENU_MSG, OnMenuMsg)



	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_DBLCLK, IDC_INFO_LIST, OnNMDblclkList)	
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)	
	ON_BN_CLICKED(IDC_ALLAPPLY_BTN, OnBnClickedAllapplyBtn)
	ON_EN_CHANGE(IDC_EDIT_NAME, OnEnChangeEditName)
	ON_NOTIFY(NM_CLICK, IDC_INFO_LIST, OnNMClickList1)
	ON_NOTIFY(LVN_DELETEITEM, IDC_INFO_LIST, OnLvnDeleteitemList1)
	ON_WM_TIMER()
	//	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


void CStaffPage13::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	InitControl();
	SetResize(IDC_INFO_LIST, sizingRightBottom);

	//SetTimer(1000, 60000, NULL);

}

void CStaffPage13::InitControl()
{
	int nItem = 0;

	m_List.InsertColumn(nItem++, "소 속", LVCFMT_CENTER, 90);
	m_List.InsertColumn(nItem++, "사번", LVCFMT_CENTER, 50);
	m_List.InsertColumn(nItem++, "아이디",	LVCFMT_LEFT, 80);
	m_List.InsertColumn(nItem++, "성 명", LVCFMT_LEFT, 70);	
	m_List.InsertColumn(nItem++, "출근", LVCFMT_LEFT, 45);
	m_List.InsertColumn(nItem++, "퇴근", LVCFMT_LEFT, 45);
	m_List.InsertColumn(nItem++, "출근시", LVCFMT_CENTER, 50);
	m_List.InsertColumn(nItem++, "퇴근시", LVCFMT_CENTER, 50);
	m_List.InsertColumn(nItem++, "업무중지", LVCFMT_CENTER, 100);
	m_List.InsertColumn(nItem++, "락타임", LVCFMT_CENTER, 55);
	m_List.InsertColumn(nItem++, "카운트", LVCFMT_CENTER, 55);
	m_List.InsertColumn(nItem++, "자사락타임", LVCFMT_CENTER, 65);
	m_List.InsertColumn(nItem++, "자사카운트", LVCFMT_CENTER, 65);
	m_List.InsertColumn(nItem++, "타사락타임", LVCFMT_CENTER, 65);
	m_List.InsertColumn(nItem++, "타사카운트", LVCFMT_CENTER, 65);
	m_List.InsertColumn(nItem++, "보기", LVCFMT_LEFT, 80);
	m_List.InsertColumn(nItem++, "제한시각", LVCFMT_CENTER, 70);
	m_List.InsertColumn(nItem++, "정상(남음)", LVCFMT_CENTER, 70);
	m_List.InsertColumn(nItem++, "SMS", LVCFMT_CENTER, 50);	
	m_List.InsertColumn(nItem++, "이용료", LVCFMT_CENTER, 50);	
	m_List.InsertColumn(nItem++, "금일수입",LVCFMT_CENTER, 60);
	m_List.InsertColumn(nItem++, "보험시작", LVCFMT_CENTER,70);
	m_List.InsertColumn(nItem++, "보험종료", LVCFMT_CENTER, 70);
	m_List.InsertColumn(nItem++, "보험회사", LVCFMT_LEFT, 100);
	m_List.InsertColumn(nItem++, "증권번호", LVCFMT_LEFT, 300);
	m_List.Populate();
}

void CStaffPage13::RefreshList() 
{
	CMyFormView::RefreshList();

	UpdateData(TRUE);
	DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_driver_limit_new");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), GetCurBranchInfo()->bIntegrated);
 
	if(!pRs.Execute(&pCmd)) return;

	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		CXTPGridRecord *pRecord = m_List.InsertItem(i, "");
		RIDER_INFO_NEW *ri = NULL;
		RefreshListSub(&pRs, ri, pRecord);

		pRs.MoveNext();
	}

	//m_List.Populate();
	pRs.Close();

	OnEnChangeEditName();
}

void CStaffPage13::DeleteAllItems()
{
	CXTPGridRecords *pRecords = m_List.GetRecords();
	long nCount = pRecords->GetCount();

	for(int i=0; i<nCount; i++)
	{
		RIDER_INFO_NEW *ri = (RIDER_INFO_NEW*)m_List.GetItemData(pRecords->GetAt(i));

		if(ri)
		{
			delete ri;
			ri = NULL;
		}
	}

	m_List.DeleteAllItems();
}

void CStaffPage13::RefreshListSub(CMkRecordset *pRs, RIDER_INFO_NEW *ri, CXTPGridRecord *pRecord)
{
	long nMNo,lCode,nTodayCharge; nTodayCharge = nMNo = lCode = 0;
	CString sID, sName,sInsuranceID;  
	int nWorkState, nLockTime, nLockCount,nLockTime4MyOrder, nLockCount4MyOrder,nLockTime4OCOrder, nLockCount4OCOrder, nReleaseMin,nCancelCount, nPanaltyTypeShowOrder;	
	nWorkState = nLockTime = nLockCount = nReleaseMin = nCancelCount = 0;
	BOOL bAllocateLimit, bContentsPayLimit,bInsurance,bWorkReport;
	COleDateTime dtAttend,dtLeave,dtWorkStateDate,dtAllocateLimitDate,dtInsuranceStart,dtInsuranceEnd,dtWorkReport, dtWorkReportEnd;
	BOOL bCheckInsurance, bEnableCancel, blimitTodayCharge;
	long nElapseLimitAllocateLocal;
	long nElapseLimitPickupLocal;
	long nElapseLimitAllocateGlobal; 
	long nElapseLimitPickupGlobal;
	long nAllocType, nWorkReportState;
	char buffer[10];

	int nSubItem = 0;

	pRs->GetFieldValue("lCode", lCode);
	pRs->GetFieldValue("sID", sID);
	pRs->GetFieldValue("sName", sName);
	pRs->GetFieldValue("nMno", nMNo);
	pRs->GetFieldValue("dtAttend", dtAttend);
	pRs->GetFieldValue("dtLeave", dtLeave);

	pRs->GetFieldValue("bWorkReport", bWorkReport);
	pRs->GetFieldValue("dtWorkReport", dtWorkReport);
	pRs->GetFieldValue("dtWorkReportEnd", dtWorkReportEnd);
	
	pRs->GetFieldValue("nWorkState", nWorkState);
	pRs->GetFieldValue("dtWorkStateDate", dtWorkStateDate);
	pRs->GetFieldValue("nWorkReportState", nWorkReportState);
	
	pRs->GetFieldValue("nLockTime", nLockTime);
	pRs->GetFieldValue("nLockCount", nLockCount);
	pRs->GetFieldValue("nLockTime4MyOrder", nLockTime4MyOrder);
	pRs->GetFieldValue("nLockCount4MyOrder", nLockCount4MyOrder);
	pRs->GetFieldValue("nLockTime4OCOrder", nLockTime4OCOrder);
	pRs->GetFieldValue("nLockCount4OCOrder", nLockCount4OCOrder);

	pRs->GetFieldValue("bAllocateLimit", bAllocateLimit);
	pRs->GetFieldValue("dtAllocateLimitDate", dtAllocateLimitDate);			
	pRs->GetFieldValue("nReleaseMin", nReleaseMin);
	//pRs->GetFieldValue("bUseSMS", bUseSMS);	
	pRs->GetFieldValue("nAllocType", nAllocType);	
	pRs->GetFieldValue("bContentsPayLimit",bContentsPayLimit);

	pRs->GetFieldValue("nTodayCharge", nTodayCharge);	

	pRs->GetFieldValue("bInsurance",bInsurance);
	pRs->GetFieldValue("dtInsuranceStart",dtInsuranceStart);
	pRs->GetFieldValue("dtInsuranceEnd",dtInsuranceEnd);
	pRs->GetFieldValue("sInsuranceID",sInsuranceID);

	pRs->GetFieldValue("nPanaltyTypeShowOrder", nPanaltyTypeShowOrder);

	pRs->GetFieldValue("bCheckInsurance", bCheckInsurance);
	pRs->GetFieldValue("bEnableCancel", bEnableCancel);
	pRs->GetFieldValue("blimitTodayCharge", blimitTodayCharge);

	pRs->GetFieldValue("nElapseLimitAllocateLocal", nElapseLimitAllocateLocal);
	pRs->GetFieldValue("nElapseLimitPickupLocal", nElapseLimitPickupLocal);
	pRs->GetFieldValue("nElapseLimitAllocateGlobal", nElapseLimitAllocateGlobal);
	pRs->GetFieldValue("nElapseLimitPickupGlobal", nElapseLimitPickupGlobal);

	CString sPanaltyTypeShowOrder; 

	if(nPanaltyTypeShowOrder == 0) sPanaltyTypeShowOrder = "공유오더";
	else if(nPanaltyTypeShowOrder == 1) sPanaltyTypeShowOrder = "자사오더";
	else if(nPanaltyTypeShowOrder == 2) sPanaltyTypeShowOrder = "소속오더";
	else sPanaltyTypeShowOrder = "알수없음";

	m_List.SetItemText(pRecord, nSubItem++, m_ci.GetName(lCode));
	m_List.SetItemText(pRecord, nSubItem++, ltoa(nMNo, buffer, 10));
	m_List.SetItemText(pRecord, nSubItem++, sID);
	m_List.SetItemText(pRecord, nSubItem++, sName);
	m_List.SetItemText(pRecord, nSubItem++, dtAttend.Format("%H:%M"));
	m_List.SetItemText(pRecord, nSubItem++, dtLeave.Format("%H:%M"));
	m_List.SetItemText(pRecord, nSubItem++, bWorkReport ? dtWorkReport.Format("%H:%M") :"X");
	m_List.SetItemText(pRecord, nSubItem++, (nWorkReportState == 2 || nWorkReportState == 3) && dtWorkReportEnd.m_status != 2 ? dtWorkReportEnd.Format("%H:%M") :"X");

	if(nWorkState  == 0)
	{
		m_List.SetItemText(pRecord,nSubItem++,"");
	}
	else
	{
		if(dtWorkStateDate.m_dt == 0 )
			m_List.SetItemText(pRecord, nSubItem++, "업무중지");
		else
			m_List.SetItemText(pRecord, nSubItem++, dtWorkStateDate.Format("%m월%d일 %H:%M"));
	}

	CString strLockTime, strLockCount;			
	CString strLockTime4MyOrder, strLockCount4MyOrder;
	CString strLockTime4OCOrder, strLockCount4OCOrder;

	if(nLockTime == 0 || nLockCount >= 100)
	{
		m_List.SetItemText(pRecord, nSubItem++, "");
		m_List.SetItemText(pRecord, nSubItem++, "");
	}
	else
	{
		strLockTime.Format("%d분", nLockTime);
		m_List.SetItemText(pRecord, nSubItem++, strLockTime);
		strLockCount.Format("%d건", nLockCount);
		m_List.SetItemText(pRecord, nSubItem++, strLockCount);
	}
/*
	if(ri->bAllocateLimit)
	{
		COleDateTimeSpan span = COleDateTime::GetCurrentTime() - ri->dtAllocateLimitDate;
		int nRemain = (long)(ri->nReleaseMin - span.GetTotalMinutes());
		if(nRemain > 0)
		{
			CString strTemp;
			strTemp.Format("%d(%d)분", ri->nReleaseMin, nRemain);
			m_List.SetItemText(i, 10, strTemp);
		}
		else {
			ri->bAllocateLimit = FALSE;
			m_List.SetItemText(i, 10, "");
			m_List.SetItemText(i, 11, "");
		}
	}
	*/

	if(nLockTime4MyOrder == 0 || nLockCount4MyOrder >= 100)
	{
		m_List.SetItemText(pRecord, nSubItem++, "");
		m_List.SetItemText(pRecord, nSubItem++, "");
	}
	else
	{
		strLockTime4MyOrder.Format("%d분", nLockTime4MyOrder);
		m_List.SetItemText(pRecord, nSubItem++, strLockTime4MyOrder);
		strLockCount4MyOrder.Format("%d건", nLockCount4MyOrder);
		m_List.SetItemText(pRecord, nSubItem++, strLockCount4MyOrder);
	}

	if(nLockTime4OCOrder == 0 || nLockCount4OCOrder >= 100)
	{
		m_List.SetItemText(pRecord, nSubItem++, "");
		m_List.SetItemText(pRecord, nSubItem++, "");
	}
	else
	{
		strLockTime4OCOrder.Format("%d분", nLockTime4OCOrder);
		m_List.SetItemText(pRecord, nSubItem++, strLockTime4OCOrder);
		strLockCount4OCOrder.Format("%d건", nLockCount4OCOrder);
		m_List.SetItemText(pRecord, nSubItem++, strLockCount4OCOrder);
	}

	m_List.SetItemText(pRecord, nSubItem++, sPanaltyTypeShowOrder);


	if(bAllocateLimit == FALSE)
		m_List.SetItemText(pRecord,nSubItem++,"");
	else
		m_List.SetItemText(pRecord, nSubItem++, dtAllocateLimitDate.Format("%H시%M분") );

	if(bAllocateLimit == FALSE)
		m_List.SetItemText(pRecord, nSubItem++, "");			
	else
	{
		CString sTempString;sTempString.Format("%d",nReleaseMin);

		m_List.SetItemText(pRecord, nSubItem++,sTempString );
	}			

	m_List.SetItemText(pRecord, nSubItem++, nAllocType == 2 ? "PDA" : nAllocType == 1 ? "SMS" : "");

	m_List.SetItemText(pRecord,nSubItem++, bContentsPayLimit? "미납" : "");



	m_List.SetItemText(pRecord, nSubItem++, GetMyNumberFormat(ltoa(nTodayCharge,buffer,10)) =="0"	?
		"" : GetMyNumberFormat(ltoa(nTodayCharge,buffer,10)));

	if(bInsurance == 0)
		m_List.SetItemText(pRecord, nSubItem++,"");
	else
		m_List.SetItemText(pRecord, nSubItem++,dtInsuranceStart.Format("%m월%d일")  );

	if(bInsurance == 0)
		m_List.SetItemText(pRecord, nSubItem++,"");
	else
		m_List.SetItemText(pRecord, nSubItem++,dtInsuranceEnd.Format("%m월%d일")  );

	if(bInsurance == 0)
	{
		m_List.SetItemText(pRecord, nSubItem++,"");
		m_List.SetItemText(pRecord, nSubItem++,"");
	}
	else
	{
		int nFind = sInsuranceID.Find("/",0);
		CString sInsuranceCompany, sInsuranceNum;
		sInsuranceCompany = sInsuranceID.Mid(0,nFind);
		sInsuranceNum = sInsuranceID.Mid(nFind+1, sInsuranceID.GetAllocLength());
		m_List.SetItemText(pRecord, nSubItem++, sInsuranceCompany);
		m_List.SetItemText(pRecord, nSubItem++, sInsuranceNum);
	}		

	if(ri == NULL)
		ri = new RIDER_INFO_NEW;

	ri->nCompany = lCode;
	ri->nMNo = nMNo;
	ri->nWorkState = nWorkState;
	ri->dtAttend = dtAttend;
	ri->dtLeave = dtLeave;
	ri->dtWorkStateDate = dtWorkStateDate;
	ri->dtAllocateLimitDate = dtAllocateLimitDate;
	ri->dtInsuranceStart = dtInsuranceStart;
	ri->dtInsuranceEnd = dtInsuranceEnd;
	ri->nLockTime = nLockTime;
	ri->nLockCount = nLockCount;
	ri->nLockTime4MyOrder = nLockTime4MyOrder;
	ri->nLockCount4MyOrder = nLockCount4MyOrder;
	ri->nLockTime4OCOrder = nLockTime4OCOrder;
	ri->nLockCount4OCOrder = nLockCount4OCOrder;
	ri->nReleaseMin = nReleaseMin;
	ri->bInsurance = bInsurance;
	ri->bAllocateLimit = bAllocateLimit;
	ri->nPanaltyTypeShowOrder = nPanaltyTypeShowOrder;
	ri->bCheckInsurance = bCheckInsurance;
	ri->bEnableCancel = bEnableCancel;
	ri->blimitTodayCharge = blimitTodayCharge;
	ri->nElapseLimitAllocateLocal = nElapseLimitAllocateLocal;
	ri->nElapseLimitPickupLocal = nElapseLimitPickupLocal;
	ri->nElapseLimitAllocateGlobal = nElapseLimitAllocateGlobal;
	ri->nElapseLimitPickupGlobal = nElapseLimitPickupGlobal;

	m_List.SetItemData(pRecord, (DWORD_PTR)ri);
}

#define ID_MENU_MSG2 455

void CStaffPage13::OnMenuMsg()
{
	if(!POWER_CHECK(1200, "기사공지창 보기", TRUE))
		return;

	int nSelItem = m_List.GetNextItem(-1, LVNI_SELECTED);

	CRiderMsgDlg dlg;
	dlg.m_nRNo = atol(m_List.GetItemText(nSelItem, 0));
	dlg.DoModal();
}
void CStaffPage13::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {
		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(23); //13
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}	
}

void CStaffPage13::OnViewExcel()
{
	if(!POWER_CHECK(5900, "엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nCompanyCode, 402, m_ui.nWNo, m_List.GetItemCount());  
	CMyExcel::ToExcel(&m_List);
}


BOOL CStaffPage13::PreTranslateMessage(MSG* pMsg)
{
	if(::GetDlgCtrlID(pMsg->hwnd) == IDC_RIDER_EDIT)
	{
		if(pMsg->message == WM_KEYDOWN)
		{
			switch(pMsg->wParam)
			{
			case VK_RETURN:
				RefreshList();
				break;
			}
		}
	}
	return CMyFormView::PreTranslateMessage(pMsg);
}


void CStaffPage13::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	ModifyPopup();
	*pResult = 0;
}


void CStaffPage13::ModifyPopup()
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	RIDER_INFO_NEW *ri = (RIDER_INFO_NEW*)m_List.GetItemData(pRows->GetAt(0)->GetRecord());

	CAllocateLimitDlg1 dlg;
	dlg.m_nRiderCompany = ri->nCompany;
	dlg.m_nRNo = ri->nMNo;
	dlg.DoModal();
}

void CStaffPage13::OnBnClickedSearchBtn()
{
	RefreshList();
}


void CStaffPage13::OnBnClickedAllapplyBtn()
{
	CAllocateLimitAllApplyDlg dlg(this);
	RIDER_NO_MAP *pMap = &dlg.m_map;

	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	for(int i=0; i<pRows->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
		RIDER_INFO_NEW *ri = (RIDER_INFO_NEW*)m_List.GetItemData(pRecord);
		pMap->insert(RIDER_NO_MAP::value_type(std::make_pair(ri->nCompany, ri->nMNo), i));
	}

	dlg.DoModal();

}

void CStaffPage13::OnEnChangeEditName()
{  
	CString sSearch, sRNo, sID, sName; m_RiderEdit.GetWindowText(sSearch);

	CXTPGridRecords *pRecords = m_List.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
	
		sRNo = m_List.GetItemText(pRecord, 1);
		sID = m_List.GetItemText(pRecord, 2);
		sName = m_List.GetItemText(pRecord, 3);

		if(sRNo.Find(sSearch) >= 0 ||
			sID.Find(sSearch) >= 0 ||
			sName.Find(sSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_List.Populate();
}

void CStaffPage13::OnWorkStop()
{
	UpdateWorkState(FALSE);
}

void CStaffPage13::OnWorkOk()
{
	UpdateWorkState(TRUE);
}

BOOL CStaffPage13::UpdateShareLimit_sub(RIDER_INFO_NEW *ri, long nPanaltyTypeShowOrder)
{
	CMkCommand pCmd(m_pMkDb, "update_rider_share_limit");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)ri->nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nMNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nPanaltyTypeShowOrder); 

	//오더전체오픈 0
	//1차 1
	//지사 2

	return pCmd.Execute();
}

void CStaffPage13::UpdateWorkState(BOOL bWorkState)
{
	CXTPGridSelectedRows *pRows = GetSelectRiderRows();
	if(pRows == NULL) return;

	CString strWorkMemo;
	CWorkStopMemoDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		strWorkMemo = dlg.m_strWorkStopMemo;

		if(!ReConFirm(pRows->GetCount()))
			return;
	}
	else
		return; 

	long nCount = pRows->GetCount();

	for (int i = 0;i < nCount; i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
		RIDER_INFO_NEW *ri = (RIDER_INFO_NEW*)m_List.GetItemData(pRecord);

		if(UpdateWorkState_sub(ri, strWorkMemo, bWorkState))
			RefreshListOne(ri, pRecord);
	}
}

BOOL CStaffPage13::UpdateWorkState_sub(RIDER_INFO_NEW *ri, CString sWorkMemo, BOOL bWorkState)
{
	CMkCommand pCmd(m_pMkDb, "update_rider_workstate_new");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)ri->nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nMNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), !bWorkState); //nWoekState 1 이 업무중지
	pCmd.AddParameter(typeString, typeInput, sWorkMemo.GetLength(), sWorkMemo);
	pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);

	return pCmd.Execute();
}

void CStaffPage13::OnLvnDeleteitemList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	*pResult = 0;
}

void CStaffPage13::OnTimer(UINT nIDEvent)
{
	CMyFormView::OnTimer(nIDEvent);
}

void CStaffPage13::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNMHDR;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return; 

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	RIDER_INFO_NEW *ri = (RIDER_INFO_NEW*)m_List.GetItemData(nRow);

	if(nCol>1 || nRow == -1) //굵은 글씨 이상
		return;

	long nCompany = ri->nCompany;
	long nRNo = ri->nMNo;

	LU->ShowRiderInfoDlg(nCompany, nRNo);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

CXTPGridSelectedRows* CStaffPage13::GetSelectRiderRows()
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) {MessageBox("기사님을 선택하세요", "확인", MB_ICONINFORMATION); return NULL;};
	if(pRows->GetCount() == 0) {MessageBox("기사님을 선택하세요", "확인", MB_ICONINFORMATION); return NULL;};
	return pRows;
}

void CStaffPage13::UpdateShareLimit(long nPanaltyTypeShowOrder)
{
	CXTPGridSelectedRows *pRows = GetSelectRiderRows();
	if(pRows == NULL) return;

	if(!ReConFirm(pRows->GetCount()))
		return;

	long nCount = pRows->GetCount();

	for (int i = 0;i < nCount; i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
		RIDER_INFO_NEW *ri = (RIDER_INFO_NEW*)m_List.GetItemData(pRecord);

		if(UpdateShareLimit_sub(ri, nPanaltyTypeShowOrder))
			RefreshListOne(ri, pRecord);
	}

	//m_List.Populate();
}

BOOL CStaffPage13::ReConFirm(long nCount)
{
	CString sTemp = "";
	sTemp.Format("%d명의 기사님에게 적용하시겠습니까?", nCount);

	if(MessageBox(sTemp, "확인", MB_OKCANCEL) != IDOK)
		return FALSE;

	return TRUE;
}

void CStaffPage13::OnShareLimit0()
{
	UpdateShareLimit(0);
}

void CStaffPage13::OnShareLimit1()
{
	UpdateShareLimit(1);
}
void CStaffPage13::OnShareLimit2()
{
	UpdateShareLimit(2);
}

void CStaffPage13::OnLockApply()
{
	UpdateLockLimit(TRUE);
}

void CStaffPage13::OnLockNotApply()
{
	UpdateLockLimit(FALSE);
}

void CStaffPage13::UpdateLockLimit(BOOL bApply)
{
	CXTPGridSelectedRows *pRows = GetSelectRiderRows();
	if(pRows == NULL) return;

	CString sLock = "", sCount = "";

	if(bApply)
	{
		CLockAllocateDlg dlg;
		if(dlg.DoModal() != IDOK)
			return;

		sLock = dlg.m_sMinute;
		sCount = dlg.m_sCount;
	}

	if(!ReConFirm(pRows->GetCount()))
		return;

	long nCount = pRows->GetCount();

	for(int i = 0;i < nCount; i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
		RIDER_INFO_NEW *ri = (RIDER_INFO_NEW*)m_List.GetItemData(pRecord);

		if(UpdateLockLimit_sub(ri, atoi(sLock), atoi(sCount)))
			RefreshListOne(ri, pRecord);
	}

	//m_List.Populate();
}

BOOL CStaffPage13::UpdateLockLimit_sub(RIDER_INFO_NEW *ri, long nLock, long nCount)
{
	CMkCommand pCmd(m_pMkDb, "update_lock_limit");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)ri->nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nMNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nLock);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCount);

	return pCmd.Execute();	
}

void CStaffPage13::OnTimeLimitApply()
{
	UpdateTimeLimit(TRUE);
}

void CStaffPage13::OnTimeLimitNotApply()
{
	UpdateTimeLimit(FALSE);
}

void CStaffPage13::UpdateTimeLimit(BOOL bApply)
{
	CXTPGridSelectedRows *pRows = GetSelectRiderRows();
	if(pRows == NULL) return;

	COleDateTime dtDate(2010, 1, 1, 0, 0, 0);
	CString sMinute = "";

	if(bApply)
	{
		CTimeLimitDlg dlg;
		if(dlg.DoModal() != IDOK)
			return;

		dtDate = dlg.m_dtDate;
		sMinute = dlg.m_sMinute;
	}

	if(!ReConFirm(pRows->GetCount()))
		return;

	long nCount = pRows->GetCount();

	for(int i = 0;i < nCount; i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
		RIDER_INFO_NEW *ri = (RIDER_INFO_NEW*)m_List.GetItemData(pRecord);

		if(UpdateTimeLimit_sub(ri, dtDate, atoi(sMinute), bApply))
			RefreshListOne(ri, pRecord);
	}

	//m_List.Populate();
}

BOOL CStaffPage13::UpdateTimeLimit_sub(RIDER_INFO_NEW *ri, COleDateTime dtDate, long nMinute, BOOL bApply)
{
	CMkCommand pCmd(m_pMkDb, "update_rider_time_limit");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)ri->nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nMNo);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtDate);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nMinute);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bApply);

	return pCmd.Execute();
}

void CStaffPage13::OnServiceRentLimitApply()
{
	MessageBox("준비중입니다", "확인", MB_ICONINFORMATION);
	return;

	UpdateServiceRentLimit(TRUE);
}

void CStaffPage13::OnServiceRentLimitNotApply()
{
	MessageBox("준비중입니다", "확인", MB_ICONINFORMATION);
	return;

	UpdateServiceRentLimit(FALSE);
}

void CStaffPage13::UpdateServiceRentLimit(BOOL bApply)
{
	CXTPGridSelectedRows *pRows = GetSelectRiderRows();
	if(pRows == NULL) return;

	if(!ReConFirm(pRows->GetCount()))
		return;

	long nCount = pRows->GetCount();

	for(int i = 0;i < nCount; i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
		RIDER_INFO_NEW *ri = (RIDER_INFO_NEW*)m_List.GetItemData(pRecord);

		if(UpdateServiceRentLimit_sub(ri, bApply))
			RefreshListOne(ri, pRecord);
	}

	//m_List.Populate();
}

BOOL CStaffPage13::UpdateServiceRentLimit_sub(RIDER_INFO_NEW *ri, BOOL bApply)
{
	CMkCommand pCmd(m_pMkDb, "update_rider_service_rent_limit");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)ri->nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nMNo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bApply);

	return pCmd.Execute();
}

void CStaffPage13::RefreshListOne(RIDER_INFO_NEW *ri, CXTPGridRecord *pRecord)
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_driver_limit_one");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nCompany);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), ri->nMNo);

	if(!pRs.Execute(&pCmd)) return;

	RefreshListSub(&pRs, ri, pRecord);	
}

void CStaffPage13::OnWorkTime()
{
	CXTPGridSelectedRows *pRows = GetSelectRiderRows();
	if(pRows == NULL) return;	

	CWorkTimeDlg dlg;

	if(dlg.DoModal() == IDOK)
	{
		if(!ReConFirm(pRows->GetCount()))
			return;

		long nCount = pRows->GetCount();

		for(int i = 0;i < nCount; i++)
		{
			CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
			RIDER_INFO_NEW *ri = (RIDER_INFO_NEW*)m_List.GetItemData(pRecord);

			if(UpdateWorkTime_Sub(ri, dlg.m_dtStartTime, dlg.m_dtEndTime))
				RefreshListOne(ri, pRecord);
		}

		//m_List.Populate();
	}
}

BOOL CStaffPage13::UpdateWorkTime_Sub(RIDER_INFO_NEW *ri, COleDateTime dtStart, COleDateTime dtEnd)
{
	CMkCommand pCmd(m_pMkDb, "update_rider_work_time");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)ri->nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nMNo);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtStart);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtEnd);

	return pCmd.Execute();
}

void CStaffPage13::OnAllocSMS()
{
	ChangeAllocType(1);
}

void CStaffPage13::OnAllocPDA()
{
	ChangeAllocType(2);
}

void CStaffPage13::ChangeAllocType(long nType)
{
	CXTPGridSelectedRows *pRows = GetSelectRiderRows();
	if(pRows == NULL) return;

	COleDateTime dtDate;
	CString sMinute = "";

	if(!ReConFirm(pRows->GetCount()))
		return;

	long nCount = pRows->GetCount();

	for(int i = 0;i < nCount; i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
		RIDER_INFO_NEW *ri = (RIDER_INFO_NEW*)m_List.GetItemData(pRecord);

		if(ChangeAllocType_sub(ri, nType))
			RefreshListOne(ri, pRecord);
	}

	//m_List.Populate();
}

BOOL CStaffPage13::ChangeAllocType_sub(RIDER_INFO_NEW *ri, long nType)
{
	CMkCommand pCmd(m_pMkDb, "update_rider_alloc_type_limit");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)ri->nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nMNo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), nType);

	return pCmd.Execute(); 
}

void CStaffPage13::OnElapseLimitAllocateLocalApply()
{
	UpdateElapseLimitLocal(TRUE);
}

void CStaffPage13::OnElapseLimitAllocateLocalNotApply()
{
	UpdateElapseLimitLocal(FALSE);
}

void CStaffPage13::UpdateElapseLimitLocal(BOOL bApply)
{
	CXTPGridSelectedRows *pRows = GetSelectRiderRows();
	if(pRows == NULL) return;

	CString sAllocate = "";
	CString sPickup = "";

	if(bApply)
	{
		CElapseLimitDlg dlg;
		dlg.m_sTitle = "시내오더";

		if(dlg.DoModal() == IDOK)
		{
			if(!ReConFirm(pRows->GetCount()))
				return;

			sAllocate = dlg.m_sElaspeLimitAllocate;
			sPickup = dlg.m_sElapseLimitPickup;
		}
	}

	long nCount = pRows->GetCount();

	for(int i = 0;i < nCount; i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
		RIDER_INFO_NEW *ri = (RIDER_INFO_NEW*)m_List.GetItemData(pRecord);

		if(UpdateElapseLimitLocal_sub(ri, atoi(sAllocate), atoi(sPickup)))
			RefreshListOne(ri, pRecord);
	}

	//m_List.Populate();
}

BOOL CStaffPage13::UpdateElapseLimitLocal_sub(RIDER_INFO_NEW *ri, long nAllocate, long nPickup)
{
	CMkCommand pCmd(m_pMkDb, "update_rider_elapse_limit_local");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)ri->nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nMNo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), nAllocate);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), nPickup);

	return pCmd.Execute();
}

void CStaffPage13::OnElapseLimitAllocateGlobalApply()
{
	UpdateElapseLimitGlobal(TRUE);
}

void CStaffPage13::OnElapseLimitAllocateGlobalNotApply()
{
	UpdateElapseLimitGlobal(FALSE);
}

void CStaffPage13::UpdateElapseLimitGlobal(BOOL bApply)
{
	CXTPGridSelectedRows *pRows = GetSelectRiderRows();
	if(pRows == NULL) return;

	CString sAllocate = "";
	CString sPickup = "";

	if(bApply)
	{
		CElapseLimitDlg dlg;
		dlg.m_sTitle = "시외오더";

		if(dlg.DoModal() == IDOK)
		{
			if(!ReConFirm(pRows->GetCount()))
				return;

			sAllocate = dlg.m_sElaspeLimitAllocate;
			sPickup = dlg.m_sElapseLimitPickup;
		}
	}

	long nCount = pRows->GetCount();

	for(int i = 0;i < nCount; i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
		RIDER_INFO_NEW *ri = (RIDER_INFO_NEW*)m_List.GetItemData(pRecord);

		if(UpdateElapseLimitGlobal_sub(ri, atoi(sAllocate), atoi(sPickup)))
			RefreshListOne(ri, pRecord);
	}

	//m_List.Populate();
}

BOOL CStaffPage13::UpdateElapseLimitGlobal_sub(RIDER_INFO_NEW *ri, long nAllocate, long nPickup)
{
	CMkCommand pCmd(m_pMkDb, "update_rider_elapse_limit_global");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)ri->nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nMNo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), nAllocate);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), nPickup);

	return pCmd.Execute();
}

void CStaffPage13::OnInsuranceApply()
{
	ApplyRiderInsurance(TRUE);
}

void CStaffPage13::OnInsuranceNotApply()
{
	ApplyRiderInsurance(FALSE);
}

void CStaffPage13::ApplyRiderInsurance(BOOL bApply)
{
	CXTPGridSelectedRows *pRows = GetSelectRiderRows();
	if(pRows == NULL) return;

	if(!ReConFirm(pRows->GetCount()))
		return;

	long nCount = pRows->GetCount();

	for (int i = 0;i < nCount; i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
		RIDER_INFO_NEW *ri = (RIDER_INFO_NEW*)m_List.GetItemData(pRecord);

		if(ApplyRiderInsurance_sub(ri, bApply))
			RefreshListOne(ri, pRecord);
	}

	//m_List.Populate();
}

BOOL CStaffPage13::ApplyRiderInsurance_sub(RIDER_INFO_NEW *ri, BOOL bApply)
{
	CMkCommand pCmd(m_pMkDb, "update_rider_Insurance");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)ri->nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nMNo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bApply);

	return pCmd.Execute();
}

void CStaffPage13::OnInsuranceDate()
{
	CXTPGridSelectedRows *pRows = GetSelectRiderRows();
	if(pRows == NULL) return;

	CInsuranceDateDlg dlg;

	if(dlg.DoModal() == IDOK)
	{
		if(!ReConFirm(pRows->GetCount()))
			return;

		long nCount = pRows->GetCount();

		for(int i = 0;i < nCount; i++)
		{
			CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
			RIDER_INFO_NEW *ri = (RIDER_INFO_NEW*)m_List.GetItemData(pRecord);

			if(UpdateInsuranceDate_sub(ri, dlg.m_dtStart, dlg.m_dtEnd))
				RefreshListOne(ri, pRecord);
		}
	}
	//m_List.Populate();
}

BOOL CStaffPage13::UpdateInsuranceDate_sub(RIDER_INFO_NEW *ri, COleDateTime dtStart, COleDateTime dtEnd)
{
	CMkCommand pCmd(m_pMkDb, "update_rider_Insurance_date");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)ri->nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nMNo);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtStart);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtEnd);

	return pCmd.Execute();
}

void CStaffPage13::OnInsuranceCompany()
{
	CXTPGridSelectedRows *pRows = GetSelectRiderRows();
	if(pRows == NULL) return;

	CInsuranceInfoDlg dlg;

	if(dlg.DoModal() == IDOK)
	{
		if(!ReConFirm(pRows->GetCount()))
			return;
	}

	long nCount = pRows->GetCount();

	for(int i = 0;i < nCount; i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
		RIDER_INFO_NEW *ri = (RIDER_INFO_NEW*)m_List.GetItemData(pRecord);

		if(UpdateInsuranceCompany_sub(ri, dlg.m_sInsCompany, dlg.m_sInsNumber))
			RefreshListOne(ri, pRecord);
	}

	//m_List.Populate();
}

BOOL CStaffPage13::UpdateInsuranceCompany_sub(RIDER_INFO_NEW *ri, CString sInsCompany, CString sInsNumber)
{
	CMkCommand pCmd(m_pMkDb, "update_rider_Insurance_comapny");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)ri->nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nMNo);
	pCmd.AddParameter(typeString, typeInput, sInsCompany.GetLength(), sInsCompany);
	pCmd.AddParameter(typeString, typeInput, sInsNumber.GetLength(), sInsNumber);

	return pCmd.Execute();
}
