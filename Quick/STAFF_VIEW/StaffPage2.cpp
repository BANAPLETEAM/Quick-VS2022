// StaffPage2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "StaffPage2.h"
#include "WorkStopMemoDlg.h"
#include "RiderMsgDlg.h"

IMPLEMENT_DYNCREATE(CStaffPage2, CMyFormView)
CStaffPage2::CStaffPage2()
	: CMyFormView(CStaffPage2::IDD)
{
	m_nCompanyCode = m_ci.m_nCompanyCode;
	m_bIntegrated = FALSE;
	COleDateTime dtCurrent = COleDateTime::GetCurrentTime();
	if(dtCurrent.GetMonth() == 1)
		m_dtDate.SetDateTime(dtCurrent.GetYear() -1, 12, 1, 0,0,0);
	else
		m_dtDate.SetDateTime(dtCurrent.GetYear(), dtCurrent.GetMonth() - 1, 1, 0,0,0);
	//m_dtDate = dtCurrent;
}

CStaffPage2::~CStaffPage2()
{
}

void CStaffPage2::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DateDT);
	DDX_Control(pDX, IDC_LIST_REPORT, m_List);
	DDX_Control(pDX, IDC_CHARGE_STATIC, m_ChargeStatic);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_SearchEdit);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_RefreshBtn);
}


BEGIN_MESSAGE_MAP(CStaffPage2, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_WM_CONTEXTMENU()	
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_COMMAND(ID_MENU_MSG, OnMenuMsg)
	ON_COMMAND(ID_WORK_STOP, OnWorkStop)
	ON_COMMAND(ID_WORK_OK, OnWorkOk)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
END_MESSAGE_MAP()


// CStaffPage2 메시지 처리기입니다.

void CStaffPage2::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_List.InsertColumn(0, "기사번호", LVCFMT_LEFT, 80);
	m_List.InsertColumn(1, "소속", LVCFMT_LEFT, 100);
	m_List.InsertColumn(2, "기사명", LVCFMT_LEFT, 100);
	m_List.InsertColumn(3, "최종접속일", LVCFMT_LEFT, 100);
	m_List.InsertColumn(4, "접속일수", LVCFMT_LEFT, 80);
	m_List.InsertColumn(5, "요금(원)", LVCFMT_RIGHT, 100);
	m_List.Populate();


	m_DateDT.SetFormat("yyyy년 MM월");

	SetResize(IDC_LIST_REPORT, sizingRightBottom);
	

	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CStaffPage2::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CStaffPage2::RefreshList()
{
	CMyFormView::RefreshList();

	CWaitCursor wait;
	COleDateTime dtFrom, dtTo;

	m_List.DeleteAllItems();
	UpdateData(TRUE);

#ifdef _DAERI
	dtFrom = COleDateTime(m_dtDate.GetYear(), m_dtDate.GetMonth(), 1, 7, 0, 0);
	if(m_dtDate.GetMonth() == 12)
		dtTo = COleDateTime(m_dtDate.GetYear() + 1, 1, 1, 7, 0, 0);
	else 
		dtTo = COleDateTime(m_dtDate.GetYear(), m_dtDate.GetMonth() + 1, 1, 7, 0, 0);
#else 
	dtFrom = COleDateTime(m_dtDate.GetYear(), m_dtDate.GetMonth(), 1, 0, 0, 0);
	if(m_dtDate.GetMonth() == 12)
		dtTo = COleDateTime(m_dtDate.GetYear() + 1, 1, 1, 0, 0, 0);
	else 
		dtTo = COleDateTime(m_dtDate.GetYear(), m_dtDate.GetMonth() + 1, 1, 0, 0, 0);
#endif

	int nItem = 0, nCompany = 0, nRNo = 0, nCount = 0, nTotal = 0, nWorkState = 0;
	COleDateTime dtLastLogin;
	CString strRName;
	int day_charge = 0 ;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_pay_allocate_new6_device_login_2");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(dtFrom), dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(dtTo), dtTo);
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(pRs.Execute(&pCmd))
	{
		pPar->GetValue(day_charge);
		while(!pRs.IsEOF())
		{
			pRs.GetFieldValue("nCompany", nCompany);
			pRs.GetFieldValue("nRNo", nRNo);
			pRs.GetFieldValue("sRName", strRName);
			pRs.GetFieldValue("dtLastLogin", dtLastLogin);
			pRs.GetFieldValue("nCount", nCount);
			pRs.GetFieldValue("nWorkState", nWorkState);

			m_List.InsertItem(nItem, LF->GetStringFromLong(nRNo)); 
			m_List.SetItemText(nItem, 1, m_ci.GetBranchName(nCompany)); 
			m_List.SetItemText(nItem, 2, strRName); 
			m_List.SetItemText(nItem, 3, dtLastLogin.Format("%m-%d")); 
			m_List.SetItemText(nItem, 4, LF->GetStringFromLong(nCount)); 
			m_List.SetItemText(nItem, 5, LF->GetMyNumberFormat(nCount * day_charge)); 

			m_List.SetItemLong2(nItem++, nWorkState);
			nTotal += nCount;

			pRs.MoveNext();
		}

		if(pRs.GetRecordCount() > 1)
		{
			m_List.InsertItem(nItem++, "");
			m_List.InsertItem(nItem, "합계");
			m_List.SetItemText(nItem, 1, "총건수(건)");
			m_List.SetItemText(nItem, 2, LF->GetStringFromLong(nItem - 1));
			m_List.SetItemText(nItem, 3, "총합계(원)"); 
			m_List.SetItemText(nItem, 4, LF->GetStringFromLong(nTotal)); 
			m_List.SetItemText(nItem, 5, LF->GetMyNumberFormat(nTotal * day_charge)); 

			m_List.SetItemLong2(nItem++, 0);
		}
	}

	m_List.Populate();
}

void CStaffPage2::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(5);
	//pRMenu->RemoveMenu(ID_CHANGE_RIDER_COLOR, MF_BYCOMMAND);
	//pRMenu->RemoveMenu(ID_WORK_STOP, MF_BYCOMMAND);
	//pRMenu->RemoveMenu(ID_WORK_OK, MF_BYCOMMAND);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}



void CStaffPage2::OnMenuMsg()
{
	if(!LF->POWER_CHECK(1200, "기사공지창 보기", TRUE))
		return;

	int nSelItem = m_List.GetNextItem(-1, LVNI_SELECTED);

	CRiderMsgDlg dlg;
	dlg.m_nRNo = atol(m_List.GetItemText(nSelItem, 0));
	dlg.DoModal();
}

void CStaffPage2::OnWorkStop()
{	
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();
	if(!pRows)
		return;
	
	if(pRows->GetCount() > 0)
    {
		CString strWorkMemo;
		CWorkStopMemoDlg dlg;
		if(dlg.DoModal() == IDOK)
		{
			strWorkMemo = dlg.m_strWorkStopMemo;
			
			CXTPGridRecord* pRecord = NULL;
			for (int i = 0; i < pRows->GetCount(); i++)
			{
				pRecord = pRows->GetAt(i)->GetRecord();
				if(!pRecord)
					continue;
				
				CWaitCursor wait;
				CMkCommand pCmd(m_pMkDb, "update_rider_workstate4");
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCompanyCode);
				pCmd.AddParameter(typeBool, typeInput, sizeof(int), m_bIntegrated);
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
						m_ci.m_bRcpIntMode1 ? MAKE_SHARE_CODE(m_ci.m_nShareCode1) : -1);
				pCmd.AddParameter(typeLong, typeInput, sizeof(int),
						m_ci.m_bRcpIntMode2 ? MAKE_SHARE_CODE(m_ci.m_nShareCode2) : -1);
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
						m_ci.m_bRcpIntMode3 ? MAKE_SHARE_CODE(m_ci.m_nShareCode3) : -1);
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), atol(m_List.GetItemText(pRecord, 0)));
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), 1);
				pCmd.AddParameter(typeString, typeInput, strWorkMemo.GetLength(), strWorkMemo);
				pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
				pCmd.Execute();
			}
		}
	}
	else
		MessageBox("직원을 선택하십시오!", "확인", MB_ICONINFORMATION);
	
	RefreshList();
}

void CStaffPage2::OnWorkOk()
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();
	if(!pRows)
		return;

	if(pRows->GetCount() > 0)
	{
		CString strWorkMemo;
		CWorkStopMemoDlg dlg;
		if(dlg.DoModal() == IDOK)
			strWorkMemo = dlg.m_strWorkStopMemo;
		else
			return;

		CXTPGridRecord* pRecord = NULL;
		for (int i = 0; i < pRows->GetCount(); i++)
		{
			pRecord = pRows->GetAt(i)->GetRecord();
			if(!pRecord)
				continue;			

			CWaitCursor wait;
			CMkCommand pCmd(m_pMkDb, "update_rider_workstate4");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCompanyCode);
			pCmd.AddParameter(typeBool, typeInput, sizeof(int), m_bIntegrated);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
					m_ci.m_bRcpIntMode1 ? MAKE_SHARE_CODE(m_ci.m_nShareCode1) : -1);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int),
					m_ci.m_bRcpIntMode2 ? MAKE_SHARE_CODE(m_ci.m_nShareCode2) : -1);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
					m_ci.m_bRcpIntMode3 ? MAKE_SHARE_CODE(m_ci.m_nShareCode3) : -1);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), atol(m_List.GetItemText(pRecord, 0)));
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), 0);
			pCmd.AddParameter(typeString, typeInput, strWorkMemo.GetLength(), strWorkMemo);
			pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
			pCmd.Execute();
		}
	}
	else
		MessageBox("직원을 선택하십시오!", "확인", MB_ICONINFORMATION);

	RefreshList();
}

void CStaffPage2::OnViewExcel()
{
	if(!LF->POWER_CHECK(5900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 404, m_ui.nWNo, m_List.GetItemCount());  
	CMyExcel::ToExcel(&m_List);
}


void CStaffPage2::OnEnChangeSearchEdit()
{
	m_SearchEdit.GetWindowText(m_strSearch);
	
	CXTPGridRecord *pRecord = NULL;
	for(int i = 0; i < m_List.GetRecords()->GetCount(); i++)
	{
		BOOL bVisible = TRUE;
		pRecord = m_List.GetRecords()->GetAt(i);

		CString strName = m_List.GetItemText(pRecord, 2), strRNo = m_List.GetItemText(pRecord, 0);

		if(strRNo.Find(m_strSearch) == -1 && strName.Find(m_strSearch) == -1)
			bVisible = FALSE;

		pRecord->SetVisible(bVisible);
	}

	m_List.Populate();
}