// StaffPage19.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "StaffPage19.h"
#include "WorkStopMemoDlg.h"
#include "RiderMsgDlg.h"

IMPLEMENT_DYNCREATE(CStaffPage19, CMyFormView)
CStaffPage19::CStaffPage19()
	: CMyFormView(CStaffPage19::IDD)
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

CStaffPage19::~CStaffPage19()
{
}

void CStaffPage19::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DateDT);
	DDX_Control(pDX, IDC_LIST_REPORT, m_List);
	DDX_Control(pDX, IDC_CHARGE_STATIC, m_ChargeStatic);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_SearchEdit);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_RefreshBtn);
	DDX_Control(pDX, IDC_INFO_STATIC, m_stcInfo);
}


BEGIN_MESSAGE_MAP(CStaffPage19, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_WM_CONTEXTMENU()	
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_COMMAND(ID_MENU_MSG, OnMenuMsg)
	ON_COMMAND(ID_WORK_STOP, OnWorkStop)
	ON_COMMAND(ID_WORK_OK, OnWorkOk)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
END_MESSAGE_MAP()


// CStaffPage19 메시지 처리기입니다.

void CStaffPage19::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	CString strInfo = "- 요금은 한달단위로 정산합니다.(최종배차일 - 최초배차일이 20일을 초과하면 한달기준으로 과금되며, 20일 이내는 일할 계산됨)";
	m_stcInfo.SetWindowText(strInfo);

	m_List.InsertColumn(0, "기사번호", LVCFMT_LEFT, 80);
	m_List.InsertColumn(1, "최초배차일", LVCFMT_LEFT, 100);
	m_List.InsertColumn(2, "최종배차일", LVCFMT_LEFT, 100);
	m_List.InsertColumn(3, "이용일수", LVCFMT_LEFT, 80);
	m_List.InsertColumn(4, "요금(원)", LVCFMT_RIGHT, 100);
	m_List.Populate();

	m_DateDT.SetFormat("yyyy년 MM월");

	SetResize(IDC_LIST_REPORT, sizingRightBottom);
}

void CStaffPage19::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CStaffPage19::RefreshList()
{
	CMyFormView::RefreshList();

	CWaitCursor wait;
	COleDateTime dtFrom, dtTo;
	long nPDAFee, nDiscount, nUsingTerm;
	char buffer[10];
	int nItem = 0, nRNo;
	int nCount = 0, nTotal = 0;
	int nWorkState = 0;
	COleDateTime dtFirst, dtLast;

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

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_pay_allocate_new5");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(dtFrom), dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(dtTo), dtTo);
	CMkParameter *parPDAFee = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parDiscount = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

	if(pRs.Execute(&pCmd))
	{
		CString strCharge;
		parPDAFee->GetValue(nPDAFee);
		parDiscount->GetValue(nDiscount);

		strCharge.Format("서비스이용료 %d원/월", nPDAFee * (100 - nDiscount) / 100);
		if(nDiscount > 0) {
			strCharge += "(";
			strCharge += ltoa(nDiscount, buffer, 10);
			strCharge += "%할인)";
		}

		m_ChargeStatic.SetWindowText(strCharge);

		while(!pRs.IsEOF())
		{
			pRs.GetFieldValue("nRNo", nRNo);
			pRs.GetFieldValue("dtFirst", dtFirst);
			pRs.GetFieldValue("dtLast", dtLast);
			pRs.GetFieldValue("nUsingTerm", nUsingTerm);
			pRs.GetFieldValue("nPDAFee", nPDAFee);
			//pRs.GetFieldValue("nWorkState", nWorkState);
			nWorkState = 0;

			m_List.InsertItem(nItem, ltoa(nRNo, buffer, 10)); 
			m_List.SetItemText(nItem, 1, dtFirst.Format("%m-%d")); 
			m_List.SetItemText(nItem, 2, dtLast.Format("%m-%d")); 
			m_List.SetItemText(nItem, 3, ltoa(nUsingTerm, buffer, 10)); 
			m_List.SetItemText(nItem, 4, LF->GetMyNumberFormat(nPDAFee)); 

			m_List.SetItemData(nItem++, (DWORD_PTR)nWorkState);

			nCount++;
			nTotal += nPDAFee;
			pRs.MoveNext();
		}

		if(pRs.GetRecordCount() > 1)
		{
			m_List.InsertItem(nItem++, "");
			m_List.InsertItem(nItem, "");
			m_List.SetItemText(nItem, 1, "총건수(건)"); 
			m_List.SetItemText(nItem, 2, ltoa(nCount, buffer, 10)); 
			m_List.SetItemText(nItem, 3, "총합계(원)"); 
			m_List.SetItemText(nItem++, 4, LF->GetMyNumberFormat(nTotal)); 
		}
	}
	m_List.Populate();
}

void CStaffPage19::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(5);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CStaffPage19::OnMenuMsg()
{
	if(!LF->POWER_CHECK(1200, "기사공지창 보기", TRUE))
		return;

	int nSelItem = m_List.GetNextItem(-1, LVNI_SELECTED);

	CRiderMsgDlg dlg;
	dlg.m_nRNo = atol(m_List.GetItemText(nSelItem, 0));
	dlg.DoModal();
}

void CStaffPage19::OnWorkStop()
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

void CStaffPage19::OnWorkOk()
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

void CStaffPage19::OnViewExcel()
{
	if(!LF->POWER_CHECK(5900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 404, m_ui.nWNo, m_List.GetItemCount());  
	CMyExcel::ToExcel(&m_List);
}


void CStaffPage19::OnEnChangeSearchEdit()
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