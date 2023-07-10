// StaffPage7.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "StaffPage7.h"
#include "RiderMsgDlg.h"
#include "DriverDetailDlg.h"
#include "WorkStopMemoDlg.h"
//#include "InsentiveDlg.h"
//#include "DailyPayDlg.h"
#include "MoveRiderDlg1.h"

// CStaffPage7 대화 상자입니다.

IMPLEMENT_DYNCREATE(CStaffPage7, CMyFormView)
CStaffPage7::CStaffPage7()
	: CMyFormView(CStaffPage7::IDD)	
{
	memset(m_columnData , NULL , sizeof(m_columnData));
}

CStaffPage7::~CStaffPage7()
{
}
	
void CStaffPage7::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_EDIT_NAME, m_RiderEdit);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strRider);
	DDX_Control(pDX, IDC_STATIC1, m_Static);
	DDX_Control(pDX, IDC_SEARCH_BTN, m_btnSearch);
	DDX_Control(pDX, IDC_MODIFY_BTN, m_btnModify);
	DDX_Control(pDX, IDC_RIDER_MOVE_BUTTON, m_btnRiderMove);
}


BEGIN_MESSAGE_MAP(CStaffPage7, CMyFormView)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_COMMAND(ID_MENU_MSG, OnMenuMsg)
	ON_COMMAND(ID_WORK_STOP, OnWorkStop)
	ON_COMMAND(ID_WORK_OK, OnWorkOk)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)	
	ON_BN_CLICKED(IDC_MODIFY_BTN, OnBnClickedModifyBtn)
	ON_EN_CHANGE(IDC_EDIT_NAME, OnEnChangeEditName)	
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST1, OnLvnDeleteitemList1)
	ON_BN_CLICKED(IDC_RIDER_MOVE_BUTTON, OnBnClickedRiderMoveButton)
END_MESSAGE_MAP()


// CStaffPage7 메시지 처리기입니다.
/////////////////////////////

void CStaffPage7::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();
	SetResize(IDC_LIST1, sizingRightBottom);
}

void CStaffPage7::InitControl()
{
	int nItem = 0;
	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 
	
	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
				LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);

	//칼럼 초기화
	for( int nColumnCount = 0;  nColumnCount < kColumsNameTotal; ++nColumnCount)
	{
		if(m_columnData[nColumnCount] )
		{
			m_List.GetColumns()->Remove(m_columnData[nColumnCount]);
			m_columnData[nColumnCount] = NULL;
		}
	}

	m_columnData[kStaffNumber] = m_List.InsertColumn(kStaffNumber, "사번", LVCFMT_CENTER, 50);
	m_columnData[kDepart] = m_List.InsertColumn(kDepart, "소 속", LVCFMT_CENTER, m_bIntegrated ? 50 : 0);
	m_columnData[kIdentify] = m_List.InsertColumn(kIdentify, "아이디",	LVCFMT_LEFT, 80);
	m_columnData[kName] = m_List.InsertColumn(kName, "성 명", LVCFMT_LEFT, 70);
	m_columnData[kWorkStop] = m_List.InsertColumn(kWorkStop, "업무중지", LVCFMT_LEFT, 100);
	m_columnData[kStopWarningRecommand] = m_List.InsertColumn(kStopWarningRecommand, "중지/주의/경고/추천",LVCFMT_CENTER, 140);
	m_columnData[kWorkMonth] = m_List.InsertColumn(kWorkMonth, "근무개월",LVCFMT_CENTER, 70);

	m_List.Populate();
}

	
void CStaffPage7::RefreshList()
{
	//pRecord로 수정
	CMyFormView::RefreshList();

	CWaitCursor wait;
	char buffer[20];
	int nCurSel = 0;

	int nPreRiderCompany = 0;
	int nPreRNo = 0;

	//셀렉트된 아이템으로 Something Do
	int nSelItem = m_List.GetNextItem(-1, LVNI_SELECTED);

	CXTPListCtrlRecord2* pRecord = static_cast<CXTPListCtrlRecord2* >(m_List.GetFirstSelectedRecord() );

	if(nSelItem >= 0) {
		ST_RIDER_INFO3 *pRi = (ST_RIDER_INFO3*)m_List.GetItemData(nSelItem);
		nPreRNo = pRi->nMNo;
		nPreRiderCompany = pRi->nCompany;
	}

	//m_List.SetIntegrated(m_bIntegrated);
	InitControl();

	UpdateData(TRUE);
	m_List.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_driver_manage3");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), m_bIntegrated);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_ci.m_bRcpIntMode1 ? MAKE_SHARE_CODE(m_ci.m_nShareCode1) : -1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int),
			m_ci.m_bRcpIntMode2 ? MAKE_SHARE_CODE(m_ci.m_nShareCode2) : -1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_ci.m_bRcpIntMode3 ? MAKE_SHARE_CODE(m_ci.m_nShareCode3) : -1);
		
	if(!pRs.Execute(&pCmd)) return;
	
	COleDateTime dtInitTime(2004,1,1,0,0,0);
	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		long nMNo,lCode,nInsentivePay;
		nInsentivePay = nMNo = lCode = 0;
		CString sID, sName, strDailyPayMemo,sHistory;  
		int nWorkState = 0;
		int nDailyPay = 0, nWorkingDay;
		COleDateTime dtWorkStateDate;

		int nSubItem = 1;
		pRs.GetFieldValue("lCode", lCode);
		pRs.GetFieldValue("sID", sID);
		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("nMno", nMNo);		
		pRs.GetFieldValue("nWorkState", nWorkState);
		pRs.GetFieldValue("dtWorkStateDate", dtWorkStateDate);
		pRs.GetFieldValue("sHistory", sHistory);
		pRs.GetFieldValue("nWorkingDay", nWorkingDay);

		if(nPreRiderCompany == lCode && nPreRNo == nMNo)
			nCurSel = i;

		m_List.InsertItem(i, ltoa(nMNo, buffer, 10));
//		if(m_bIntegrated)
		m_List.SetItemText(i, nSubItem++, m_ci.GetName(lCode));		
		//다 넣습니다

		m_List.SetItemText(i, nSubItem++, sID);
		m_List.SetItemText(i, nSubItem++, sName);
		if(nWorkState == 1)
		{
			if(dtWorkStateDate.m_dt == 0)
                m_List.SetItemText(i, nSubItem++, "업무중지");
			else
				m_List.SetItemText(i, nSubItem++, dtWorkStateDate.Format("%y/%m/%d %H:%M"));
		}
		else
			nSubItem++;

		if(sHistory != "")
			m_List.SetItemText(i,nSubItem++, sHistory);
		else
			m_List.SetItemText(i,nSubItem++, "");


		if(nWorkingDay > 0)
			m_List.SetItemText(i,nSubItem++, ltoa(nWorkingDay, buffer, 10));

		ST_RIDER_INFO3 *ri = new ST_RIDER_INFO3;
		ri->nCompany = lCode;
		ri->nMNo = nMNo;
		ri->strID = sID;
		ri->strName = sName;
		ri->strPart =  m_ci.GetName(lCode);
		ri->nWorkState = nWorkState;		
		ri->dtWorkStateDate = dtWorkStateDate;

		m_List.SetItemData(i, (DWORD_PTR)ri);

		if(LF->IsStringDigit(m_strRider)) {
			if(atol(m_strRider) == nMNo)
				nCurSel = i; 
		}
		else if(m_strRider == sName) {
            nCurSel = i;
		}		

		pRs.MoveNext();
	}
	
	//이전에 선택된 셀이 중간에 오도록 한다.
	CRect rcClient, rcItem;
	int nItemPerPage;

	m_List.GetClientRect(&rcClient);
	nItemPerPage = (int) (rcClient.Height() / (rcItem.Height() + 1));
	pRs.Close();
	m_List.Populate();
}


#define ID_MENU_MSG2 455

void CStaffPage7::OnMenuMsg()
{
	if(!LF->POWER_CHECK(1200, "기사공지창 보기", TRUE))
		return;

	int nSelItem = m_List.GetNextItem(-1, LVNI_SELECTED);

	CRiderMsgDlg dlg;
	dlg.m_nRNo = atol(m_List.GetItemText(nSelItem, 0));
	dlg.DoModal();
}

void CStaffPage7::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {
		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(3);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}	
}

void CStaffPage7::OnViewExcel()
{
	if(!LF->POWER_CHECK(5900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 403, m_ui.nWNo, m_List.GetItemCount());  
	CMyExcel::ToExcel(&m_List);
}

void CStaffPage7::ModifyPopup(CXTPListCtrlRecord2* pRecord)
{
	CDriverDetailDlg dlg;

	int nColumn = 0;
	char buffer[20];

	ST_RIDER_INFO3 *ri = (ST_RIDER_INFO3*)m_List.GetItemData(pRecord);

	if(ri)
	{
		dlg.m_strCompanyNum = itoa(ri->nMNo,buffer,10);
		dlg.m_nRNo = ri->nMNo;

		if(m_bIntegrated == 1)
			dlg.m_strPart = ri->strPart;
		else
			dlg.m_strPart = "";		

		dlg.m_strName = ri->strName;
		//dlg.m_strDailyMemo = ri->strDailyPayMemo;
		//dlg.m_nDailyPay = ri->nDailyPay;
		dlg.m_nCompany = ri->nCompany;

		//dlg.m_nDailyPay = ri->nDailyPay;
		//dlg.m_nInsentiveEdit = ri->nInsentivePay;
		dlg.m_strDailyMemo = ri->strDailyPayMemo;

		if(dlg.DoModal() == IDOK)
		{
			RefreshList();
		}
	}
}

void CStaffPage7::ModifyPopup(int nItem)
{	
	CDriverDetailDlg dlg;

	int nColumn = 0;
	char buffer[20];
	
	ST_RIDER_INFO3 *ri = (ST_RIDER_INFO3*)m_List.GetItemData(nItem);

	if(ri)
	{
		dlg.m_strCompanyNum = itoa(ri->nMNo,buffer,10);
		dlg.m_nRNo = ri->nMNo;

		if(m_bIntegrated == 1)
			dlg.m_strPart = ri->strPart;
		else
			dlg.m_strPart = "";		

		dlg.m_strName = ri->strName;
		//dlg.m_strDailyMemo = ri->strDailyPayMemo;
		//dlg.m_nDailyPay = ri->nDailyPay;
		dlg.m_nCompany = ri->nCompany;

		//dlg.m_nDailyPay = ri->nDailyPay;
		//dlg.m_nInsentiveEdit = ri->nInsentivePay;
		dlg.m_strDailyMemo = ri->strDailyPayMemo;
		
		if(dlg.DoModal() == IDOK)
		{
			RefreshList();
		}
	}
}

void CStaffPage7::OnBnClickedSearchBtn()
{
	RefreshList();
}
void CStaffPage7::OnBnClickedModifyBtn()
{	
	if(m_List.GetSelectedRows()->GetCount() == 0 )
		MessageBox("선택이 잘못된것 같습니다. 다시 선택해주세요","",MB_ICONERROR);
	else
		ModifyPopup(static_cast<CXTPListCtrlRecord2*>(m_List.GetFirstSelectedRecord() ) );	

}


void CStaffPage7::OnEnChangeEditName()
{
	m_RiderEdit.GetWindowText(m_strRider);
	if(m_strRider.GetLength() == 0) return;
		int nCurSel = -1;

	for(int i = 0; i < m_List.GetItemCount(); i++)
	{
		
		CString strRNo, strName , strID;
		
		strRNo = m_List.GetItemText(i,0);
		if(m_bIntegrated)
			strID = m_List.GetItemText(i,2);
		else
			strID = m_List.GetItemText(i,1);

		if(m_bIntegrated)
			strName = m_List.GetItemText(i, 3);
		else 
			strName = m_List.GetItemText(i, 2);
		
		if(m_strRider == strRNo.Left(min(m_strRider.GetLength(), strRNo.GetLength()))) 
			nCurSel = i; 
		else if(m_strRider.MakeUpper() == strID.Left(min(m_strRider.GetLength(), strID.GetLength())).MakeUpper() ) 
		     nCurSel = i;
		else if(m_strRider.MakeUpper() == strName.Left(min(m_strRider.GetLength(), strName.GetLength())).MakeUpper())
		     nCurSel = i;
		

		if(nCurSel >= 0)
		{
			//이전에 선택된 셀이 중간에 오도록 한다.
			CRect rcClient, rcItem;
			int nItemPerPage;

			m_List.GetClientRect(&rcClient);
			nItemPerPage = (int) (rcClient.Height() / (rcItem.Height() + 1));

			return;
		}
	}
}

void CStaffPage7::OnWorkStop()
{
	UINT i, uSelectedCount = m_List.GetSelectedRows()->GetCount();
	int  nItem = -1;

	// Update all of the selected items.
	if(uSelectedCount > 0)
    {
		CString strWorkMemo;
		CWorkStopMemoDlg dlg;
		if(dlg.DoModal() == IDOK)
		{
			strWorkMemo = dlg.m_strWorkStopMemo;

			for (i = 0;i < uSelectedCount; i++)
			{
				nItem = m_List.GetNextItem(nItem, LVNI_SELECTED);
				if(nItem < 0) break;
				
				ST_RIDER_INFO3 *ri = (ST_RIDER_INFO3*)m_List.GetItemData(nItem);

				CWaitCursor wait;
				CMkCommand pCmd(m_pMkDb, "update_rider_workstate4");
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nCompany);
				pCmd.AddParameter(typeBool, typeInput, sizeof(int), m_bIntegrated);
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
						m_ci.m_bRcpIntMode1 ? MAKE_SHARE_CODE(m_ci.m_nShareCode1) : -1);
				pCmd.AddParameter(typeLong, typeInput, sizeof(int),
						m_ci.m_bRcpIntMode2 ? MAKE_SHARE_CODE(m_ci.m_nShareCode2) : -1);
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
						m_ci.m_bRcpIntMode3 ? MAKE_SHARE_CODE(m_ci.m_nShareCode3) : -1);
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), atol(m_List.GetItemText(nItem, 0)));
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), 1);
				pCmd.AddParameter(typeString, typeInput, strWorkMemo.GetLength(), strWorkMemo);
				pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
				pCmd.Execute();
			}
		}
	}
	else {
		MessageBox("직원을 선택하십시오!", "확인", MB_ICONINFORMATION);
	}

	RefreshList();
}

void CStaffPage7::OnWorkOk()
{
	UINT i, uSelectedCount = m_List.GetSelectedRows()->GetCount();
	int  nItem = -1;

	// Update all of the selected items.
	if(uSelectedCount > 0)
	{
		CString strWorkMemo;
		CWorkStopMemoDlg dlg;
		if(dlg.DoModal() == IDOK)
			strWorkMemo = dlg.m_strWorkStopMemo;
		else
			return;

		for (i = 0;i < uSelectedCount; i++)
		{
			nItem = m_List.GetNextItem(nItem, LVNI_SELECTED);
			if(nItem < 0) break;
			
			ST_RIDER_INFO3 *ri = (ST_RIDER_INFO3*)m_List.GetItemData(nItem);

			CWaitCursor wait;
			CMkCommand pCmd(m_pMkDb, "update_rider_workstate3");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)ri->nCompany);
			pCmd.AddParameter(typeBool, typeInput, sizeof(int), m_bIntegrated);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
					m_ci.m_bRcpIntMode1 ? MAKE_SHARE_CODE(m_ci.m_nShareCode1) : -1);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int),
					m_ci.m_bRcpIntMode2 ? MAKE_SHARE_CODE(m_ci.m_nShareCode2) : -1);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
					m_ci.m_bRcpIntMode3 ? MAKE_SHARE_CODE(m_ci.m_nShareCode3) : -1);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), atol(m_List.GetItemText(nItem, 0)));
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), 0);
			pCmd.AddParameter(typeString, typeInput, strWorkMemo.GetLength(), strWorkMemo);
			pCmd.Execute();
		}
	}
	else {
		MessageBox("직원을 선택하십시오!", "확인", MB_ICONINFORMATION);
	}

	RefreshList();
}


void CStaffPage7::OnLvnDeleteitemList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if((ST_RIDER_INFO3*)m_List.GetItemData(pNMListView->iItem) )
        delete (ST_RIDER_INFO3*)m_List.GetItemData(pNMListView->iItem);

	*pResult = 0;
}

BOOL CStaffPage7::PreTranslateMessage(MSG* pMsg)
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


void CStaffPage7::OnBnClickedRiderMoveButton()
{
	CMoveRiderDlg1 dlg;
	dlg.SetIntegrated(LF->GetCurBranchInfo()->bIntegrated);
	dlg.SetCompanyCode(LF->GetCurBranchInfo()->nCompanyCode);
	dlg.DoModal();	
}
