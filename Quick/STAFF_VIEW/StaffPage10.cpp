// StaffForm9.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "StaffPage10.h"
#include "ShareOrderAllocate.h"
#include "ShareOrderAllocate3.h"
#include "RcpView.h"
#include "RiderAllocateDlg.h"
#include "RiderAdviceDlg2010.h"
#include "DateSelectDlg.h"
#include "ShareRefuseExtendLogDlg.h"

// CStaffPage10 대화 상자입니다.

IMPLEMENT_DYNCREATE(CStaffPage10, CMyFormView)
CStaffPage10::CStaffPage10()
: CMyFormView(CStaffPage10::IDD)
{
	m_nOtherCompanyCol = 0;
}

CStaffPage10::~CStaffPage10()
{
}

void CStaffPage10::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MYRIDER_LIST, m_MyList);
	DDX_Control(pDX, IDC_OTHERRIDER_LIST, m_OtherList);
	DDX_Control(pDX, IDC_REGISTER_BUTTON, m_RegisterBtn);
	DDX_Control(pDX, IDC_DELETE_BUTTON, m_DeleteBtn);
	DDX_Control(pDX, IDC_REFRESH_LIST_BUTTON, m_RefreshListBtn);
	DDX_Control(pDX, IDC_OTHER_RIDER_EDIT, m_edtOtherRider);
	DDX_Control(pDX, IDC_MY_RIDER_EDIT, m_edtMyRider);
}


BEGIN_MESSAGE_MAP(CStaffPage10, CMyFormView)
	ON_BN_CLICKED(IDC_REGISTER_BUTTON, OnBnClickedRegisterButton)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, OnBnClickedDeleteButton)
	ON_BN_CLICKED(IDC_MODIFY_BUTTON, OnBnClickedModifyButton)
	ON_BN_CLICKED(IDC_REFRESH_LIST_BUTTON, OnBnClickedRefreshListButton)
	ON_NOTIFY(NM_DBLCLK, IDC_OTHERRIDER_LIST, OnNMDblclkOtherriderList)
	ON_NOTIFY(NM_DBLCLK, IDC_MYRIDER_LIST, OnNMDblclkMyriderList)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_COMMAND(ID_VIEW_EXCEL2, OnViewExcel2)

	ON_COMMAND(ID_DELAY_ALLOCATE, OnDelayAllocate)
	ON_COMMAND(ID_DELAY_ALLOCATE_LOG, OnDelayAllocateLog)
	
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_CLICK, IDC_MYRIDER_LIST, OnNMClickMyriderList)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_OTHERRIDER_LIST, OnCustomdrawOtherList)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_MYRIDER_LIST, OnCustomdrawMyList)
	ON_EN_CHANGE(IDC_OTHER_RIDER_EDIT, OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_MY_RIDER_EDIT, OnEnChangeEdit2)

	ON_BN_CLICKED(IDC_REGISTER_BUTTON2, &CStaffPage10::OnBnClickedRegisterButton2)
END_MESSAGE_MAP()


// CStaffPage10 메시지 처리기입니다.
void CStaffPage10::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_OTHERRIDER_LIST, sizingBottom);
	InitControl();
}

void CStaffPage10::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect,rect2;
	rect = rect2 = NULL;
	m_OtherList.GetWindowRect(&rect);
	m_MyList.GetWindowRect(&rect2);

	if(rect.PtInRect(point))
	{
		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(35);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}
	else if(rect2.PtInRect(point))
	{
		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(10);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}
}

void CStaffPage10::OnBnClickedRegisterButton()
{
	CShareOrderAllocate3 dlg;
	dlg.m_nMode = 1;
	dlg.m_nID = -1;
	dlg.SetCompany(LF->GetCurBranchInfo()->nCompanyCode);
	if(dlg.DoModal() == IDOK)
		RefreshList();
}

void CStaffPage10::InitControl()
{
	CImageList ImageList,ImageList2;
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	ImageList2.Create(1,17,ILC_COLOR,1,1); 
	m_MyList.SetImageList(&ImageList,LVSIL_SMALL); 	

	m_MyList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_MyList.InsertColumn(0,"사번",LVCFMT_LEFT, 40);
	m_MyList.InsertColumn(1,"소속",LVCFMT_LEFT, 70);
	m_MyList.InsertColumn(2,"아이디",LVCFMT_LEFT, 80);	
	m_MyList.InsertColumn(3,"성명",LVCFMT_LEFT, 70);	
	m_MyList.InsertColumn(4,"등록회사",LVCFMT_LEFT, 90);
	m_MyList.InsertColumn(5,"대표번호",LVCFMT_LEFT, 90);
	m_MyList.InsertColumn(6,"상황실",LVCFMT_LEFT, 90);
	m_MyList.InsertColumn(7,"등록자",LVCFMT_LEFT, 60);
	m_MyList.InsertColumn(8,"등록일",LVCFMT_LEFT, 60);
	m_MyList.InsertColumn(9,"주민",LVCFMT_LEFT, 67);
	m_MyList.InsertColumn(10,"아이디",LVCFMT_LEFT, 60);
	m_MyList.InsertColumn(11,"사유",LVCFMT_LEFT, 200);	
	m_MyList.InsertColumn(12,"해제일",LVCFMT_LEFT, 90);	
	m_MyList.InsertColumn(13,"0",LVCFMT_LEFT, 0);	

	m_OtherList.SetImageList(&ImageList2,LVSIL_SMALL); 
	m_OtherList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_OtherList.InsertColumn(0,"등록회사",LVCFMT_LEFT, 80);
	m_OtherList.InsertColumn(1,"구분",LVCFMT_LEFT, 50);
	m_OtherList.InsertColumn(2,"사번",LVCFMT_LEFT, 43);	
	m_OtherList.InsertColumn(3,"타기사소속",LVCFMT_LEFT, 90);
	m_OtherList.InsertColumn(4,"성명",LVCFMT_LEFT, 56);	
	m_OtherList.InsertColumn(5,"등록일",LVCFMT_LEFT, 55);	
	m_OtherList.InsertColumn(6,"주민",LVCFMT_LEFT, 50);	
	m_OtherList.InsertColumn(7,"사유",LVCFMT_LEFT, 200);
	m_OtherList.InsertColumn(8,"해제일",LVCFMT_LEFT, 90);
	m_OtherList.InsertColumn(9,"접수자",LVCFMT_LEFT, 60);
	//m_OtherList.InsertColumn(10,"",LVCFMT_LEFT, 0);

}

void CStaffPage10::RefreshList()
{
	CMyFormView::RefreshList();

	char buffer[20];
	//CWaitCursor wait;

	m_MyList.DeleteAllItems();
	m_OtherList.DeleteAllItems();

	long nTempMNo,nTemplCode;
	nTempMNo = nTemplCode = -1;
	CMkCommand pCmd(m_pMkDb, "select_share_order_my_allocate_list5", FALSE, TRUE);
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), LF->GetCurBranchInfo()->bIntegrated);
	if(!pRs.Execute(&pCmd))
		return;

	int nColumn;
	int nItem = 0;
	int nCount = 0;
	while(!pRs.IsEOF())
	{			
		long nMNo, nCompany,nWorkState,nID,nRiderCompany, nCount;
		nMNo = nCompany = nWorkState = nID = nRiderCompany = nCount = 0;
		COleDateTime dtPrevent,dtWorkStateDate, dtEnd;
		CString		strBranchName, strID, strName, strMemo, strJumin, strOtherWName, strOtherCompanyName, strOtherCompanyTel, strOtherCompanyOffice;

		pRs.GetFieldValue("nMNo", nMNo);

		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("sBranchName", strBranchName);
		pRs.GetFieldValue("sID", strID);
		pRs.GetFieldValue("sName", strName);
		//pRs.GetFieldValue("nWorkState", nWorkState);
		//pRs.GetFieldValue("dtWorkStateDate", dtWorkStateDate);
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nRiderCompany", nRiderCompany);		
		pRs.GetFieldValue("sMemo", strMemo);
		pRs.GetFieldValue("dtPrevent", dtPrevent);

		pRs.GetFieldValue("sjumin", strJumin);
		pRs.GetFieldValue("sID", strID);
		pRs.GetFieldValue("dtEnd", dtEnd);

		pRs.GetFieldValue("sOtherCompanyName", strOtherCompanyName);
		pRs.GetFieldValue("sOtherCompanyTel", strOtherCompanyTel);
		pRs.GetFieldValue("sOtherCompanyOffice", strOtherCompanyOffice);
		pRs.GetFieldValue("sOtherWName", strOtherWName);
		//pRs.GetFieldValue("bExtendPenaltyEnd", bExtendPenaltyEnd);

		CString strView;
		nColumn = 1;
		m_MyList.InsertItem(nItem, itoa(nMNo,buffer,10));
		m_MyList.SetItemText(nItem, nColumn++, strBranchName);

		m_MyList.SetItemText(nItem, nColumn++, strID);
		m_MyList.SetItemText(nItem, nColumn++, strName);

		m_MyList.SetItemText(nItem, nColumn++, strOtherCompanyName);
		m_MyList.SetItemText(nItem, nColumn++, strOtherCompanyTel);
		m_MyList.SetItemText(nItem, nColumn++, strOtherCompanyOffice);
		m_MyList.SetItemText(nItem, nColumn++, strOtherWName);

		m_MyList.SetItemText(nItem, nColumn++, dtPrevent.Format("%y-%m-%d"));
		m_MyList.SetItemText(nItem, nColumn++, strJumin.Left(6) );
		m_MyList.SetItemText(nItem, nColumn++, strID.GetLength() > 10 ? "등록" : "");
 
		m_MyList.SetItemText(nItem, nColumn++, strMemo);

		if(dtEnd.m_status != 2)
			m_MyList.SetItemText(nItem, nColumn++, dtEnd.Format("%y-%m-%d"));
		else
			m_MyList.SetItemText(nItem, nColumn++, "무제한");
		//m_MyList.SetItemText(nItem, nColumn++, ltoa(nRiderCompany, buffer, 10));
		m_MyList.SetItemData(nItem,nID);
		m_MyList.SetItemLong(nItem, nRiderCompany);
		m_MyList.SetItemString(nItem, strJumin);

		nItem++;
		nCount ++;
		pRs.MoveNext();
	}	
	pRs.Close();

	m_MyList.Populate();


	CMkCommand pCmd2(m_pMkDb, "select_share_order_other_allocate_list4", FALSE, TRUE);
	CMkRecordset pRs2(m_pMkDb);
	pCmd2.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd2.AddParameter(typeBool, typeInput, sizeof(BOOL), LF->GetCurBranchInfo()->bIntegrated);
	if(!pRs2.Execute(&pCmd2))
		return;

	nItem = 0;
	nCount = 0;
	while(!pRs2.IsEOF())
	{			
		BOOL bApplyAllShareCode1;
		long nRNo, nCompany,nWorkState,nID,nRiderCompany, nCount, nWNo;
		nRNo = nCompany = nWorkState = nID = nRiderCompany = nCount = 0;
		COleDateTime dtPrevent,dtWorkStateDate, dtEnd;
		CString		sBranchName, sID, sRName, sMemo, sJumin;
		BOOL bExtendPenaltyEnd;

		pRs2.GetFieldValue("nRNo", nRNo);
		pRs2.GetFieldValue("nCompany", nCompany);

		pRs2.GetFieldValue("bApplyAllShareCode1", bApplyAllShareCode1);
		pRs2.GetFieldValue("sRName", sRName);
		pRs2.GetFieldValue("nID", nID); 
		pRs2.GetFieldValue("nRiderCompany", nRiderCompany);		
		pRs2.GetFieldValue("sMemo", sMemo);
		pRs2.GetFieldValue("dtPrevent", dtPrevent);
		pRs2.GetFieldValue("sjumin", sJumin);
		pRs2.GetFieldValue("dtEnd", dtEnd);
		pRs2.GetFieldValue("nWNo", nWNo);
		pRs2.GetFieldValue("bExtendPenaltyEnd", bExtendPenaltyEnd);

		CString strView;
		strView.Format("%s",m_ci.GetName(nRiderCompany));
		CString strView1;
		strView1.Format("%s",m_ci.GetName(nCompany));
		CString strTemp = sJumin;

		nColumn = 1;

		if(sJumin.GetLength() > 10)
			sJumin = "**" + sJumin.Mid(2,4);
		m_OtherList.InsertItem(nItem, strView1);
		m_OtherList.SetItemText(nItem, nColumn++, bApplyAllShareCode1?"전지사" :"지사");
		m_OtherList.SetItemText(nItem, nColumn++,itoa(nRNo,buffer,10));
		m_OtherList.SetItemText(nItem, nColumn++, strView);					
		m_OtherList.SetItemText(nItem, nColumn++, sRName);					
		m_OtherList.SetItemText(nItem, nColumn++, dtPrevent.Format("%y-%m-%d") );		
		m_OtherList.SetItemText(nItem, nColumn++, sJumin);
		m_OtherList.SetItemText(nItem, nColumn++, sMemo );	
		if(dtEnd.m_status != 2)
			m_OtherList.SetItemText(nItem, nColumn++, dtEnd.Format("%y-%m-%d"));
		else
			m_OtherList.SetItemText(nItem, nColumn++, "무제한");

		m_nOtherCompanyCol = nColumn;
		m_OtherList.SetItemText(nItem, nColumn++, ltoa(nWNo, buffer,10) );
		//m_OtherList.SetItemText(nItem, nColumn++, ltoa(nCompany, buffer,10) );

		m_OtherList.SetItemData(nItem,nID);
		m_OtherList.SetItemLong(nItem, nCompany); 
		m_OtherList.SetItemLong2(nItem, nRNo);
		m_OtherList.SetItemLong3(nItem, bExtendPenaltyEnd);
		m_OtherList.SetItemString(nItem,strTemp); 
		m_OtherList.SetItemDate(nItem++, dtEnd);

		pRs2.MoveNext();
	}	

	m_OtherList.Populate();
}



void CStaffPage10::OnBnClickedDeleteButton()
{
	CXTPGridSelectedRows *pRows = m_OtherList.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == ZERO) return;

	CXTPGridRecord *pRecord = pRows->GetAt(ZERO)->GetRecord();

	int nID = (int)m_OtherList.GetItemData(pRecord);
	CString strCompanyName = m_OtherList.GetItemText(pRecord,0);
	int nRNo = atoi(m_OtherList.GetItemText(pRecord,1));


	if(LF->GetCurBranchInfo()->bIntegrated == 0)
	{
		if(m_ci.GetName(LF->GetCurBranchInfo()->nCompanyCode) != strCompanyName)
		{
			MessageBox("같은 소속회사만이 지울 수 있습니다.", "삭제확인", MB_ICONINFORMATION);
			return;
		}
	}


	CMkCommand pCmd(m_pMkDb, "delete_share_refusal_rider");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nID);
	pCmd.AddParameter(1);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.strName);
	//pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	//pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
	if(!pRs.Execute(&pCmd))
		return;

	RefreshList();
}

void CStaffPage10::OnBnClickedModifyButton()
{
	CXTPGridSelectedRows *pRows = m_OtherList.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == ZERO) return;

	CXTPGridRecord *pRecord = pRows->GetAt(ZERO)->GetRecord();

	long nRecordID = (long)m_OtherList.GetItemData(pRecord);
	//long nCompany = atol(m_OtherList.GetItemText(pRecord, m_nOtherCompanyCol));
	long nCompany = m_OtherList.GetItemLong(pRecord);
	if(nCompany == LF->GetCurBranchInfo()->nCompanyCode || 
		(LF->IsIntegrated() && LF->IsBranch(nCompany) ) 	)
	{
		CShareOrderAllocate3 dlg;
		dlg.m_nMode = 0;
		dlg.m_nID = nRecordID;
		dlg.m_ModifyButtonEnable = TRUE;
		dlg.SetCompany(LF->GetCurBranchInfo()->nCompanyCode);
		if(dlg.DoModal() == IDOK)
			RefreshList();
	}
	else
	{
		MessageBox("전지사는 통합에서만이 수정 권한이 있습니다.", "확인" , MB_ICONINFORMATION);
	}



}

void CStaffPage10::OnBnClickedRefreshListButton()
{
	RefreshList();
}

void CStaffPage10::OnNMDblclkOtherriderList(NMHDR *pNMHDR, LRESULT *pResult)
{
	CXTPGridRecord *pRecord = m_OtherList.GetFirstSelectedRecord();

	if(!pRecord)
		return;

	long nID = m_OtherList.GetItemData(pRecord);
	long nRiderCompany = m_OtherList.GetItemLong(pRecord);
	long nRNo = m_OtherList.GetItemLong2(pRecord);

	CRiderAdviceDlg2010 dlg;
	dlg.m_nRiderCompany = nRiderCompany;
	dlg.m_nRNo = nRNo;
	dlg.m_nCompany = m_ci.m_nCompanyCode;
	dlg.m_nModifyID = nID;

	if(dlg.DoModal() == IDOK)
		RefreshList();
	*pResult = 0;
}

void CStaffPage10::OnNMDblclkMyriderList(NMHDR *pNMHDR, LRESULT *pResult)
{
	CXTPGridSelectedRows *pRows = m_MyList.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == ZERO) return;

	CXTPGridRecord *pRecord = pRows->GetAt(ZERO)->GetRecord();

	int nID = (int)m_MyList.GetItemData(pRecord);
	CShareOrderAllocate dlg;
	dlg.m_nMode = 0;
	dlg.m_nID = nID;
	dlg.m_ModifyButtonEnable = FALSE;
	dlg.SetCompany(-1);
	if(dlg.DoModal() == IDOK)
		RefreshList();
	*pResult = 0;
}

void CStaffPage10::OnViewExcel()
{
	if(!LF->POWER_CHECK(5900, "직원 엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 409, m_OtherList.GetItemCount());  
	CMyExcel::ToExcel(&m_OtherList);
}

void CStaffPage10::OnViewExcel2()
{
	if(!LF->POWER_CHECK(5900, "직원 엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 409, m_MyList.GetItemCount());  
	CMyExcel::ToExcel(&m_MyList);
}

void CStaffPage10::OnDelayAllocate()
{
	CXTPGridSelectedRows *pRows = m_OtherList.GetSelectedRows();

	long nCount = pRows->GetCount();

	if(nCount == 0)
	{
		MessageBox("연장하려는 기사를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	//CMyXTPGridRecord *pRecord = (CMyXTPGridRecord*) pRows->GetAt(0)->GetRecord();

	CXTPGridRecord *pRecordOne =  pRows->GetAt(0)->GetRecord();

	CDateSelectDlg dlg;
	dlg.m_strTitle = "날짜선택";
	dlg.m_bAllocate = TRUE;
	dlg.m_dtLastAllocate = m_OtherList.GetItemDate(pRecordOne); 

	if(dlg.DoModal() != IDOK)
		return;

	long nUpdateCount = 0;

	for(int i=0; i<nCount; i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
		long nID = m_OtherList.GetItemData(pRecord);

		CMkCommand cmd(m_pMkDb, "update_rider_share_refuse_date_extend");
		cmd.AddParameter(nID);
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ui.strName);
		cmd.AddParameter(dlg.m_dtDateTime);

		cmd.Execute();
		nUpdateCount++;
	}

	if(nUpdateCount > 0)
	{
		CString strTemp;
		strTemp.Format("%d명에게 적용되었습니다", nUpdateCount);

		MessageBox(strTemp, "확인", MB_ICONINFORMATION);
		RefreshList();
	}
}

void CStaffPage10::OnDelayAllocateLog()
{
	CXTPGridSelectedRows *pRows = m_OtherList.GetSelectedRows();

	if(pRows->GetCount() == 0) 
	{
		MessageBox("기사를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CXTPGridRecord *pRecord = (CXTPGridRecord*) pRows->GetAt(0)->GetRecord();

	long nID = m_OtherList.GetItemData(pRecord);
	BOOL bExtendPenaltyEnd = m_OtherList.GetItemLong3(pRecord);

	if(!bExtendPenaltyEnd)
	{
		MessageBox("연장 기록이 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CShareRefuseExtendLogDlg dlg;
	dlg.m_nID = nID;
	dlg.DoModal();
}	

void CStaffPage10::OnCustomdrawOtherList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
	//CListCtrl plist = reinterpret_cast<CListCtrl*>pNMHDR;


	// Take the default processing unless we set this to something else below.
	*pResult = 0;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.

	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		// This is the notification message for an item.  We'll request
		// notifications before each subitem's prepaint stage.

		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{
		// This is the prepaint stage for a subitem. Here's where we set the
		// item's text and background colors. Our return value will tell 
		// Windows to draw the subitem itself, but it will use the new colors
		// we set here.
		// The text color will cycle through red, green, and light blue.
		// The background color will be light blue for column 0, red for
		// column 1, and black for column 2.

		//if(pLVCD->iSubItem  == 0 || pLVCD->iSubItem  == 1 || pLVCD->iSubItem  == 2 || pLVCD->iSubItem  == 3)
		//{
		//	m_font.DeleteObject();
		//	LOGFONT accesscontrol_static_lfont = {13,0,0,0,FW_BOLD,0,0,0,HANGUL_CHARSET,0,0,0,0,"돋움"};
		//	m_font.CreateFontIndirect(&accesscontrol_static_lfont);
		//	SelectObject(pLVCD->nmcd.hdc, m_font);
		//	//	pLVCD->clrText = RGB(255,0,0);
		//	SelectObject( pLVCD->nmcd.hdc, m_font );
		//}
		//else
		//{
		//	m_font.DeleteObject();
		//	LOGFONT accesscontrol_static_lfont = {12,0,0,0,NULL,0,0,0,HANGUL_CHARSET,0,0,0,0,"돋움"};
		//	m_font.CreateFontIndirect(&accesscontrol_static_lfont);
		//	//	pLVCD->clrText = RGB(0,255,0);
		//	SelectObject( pLVCD->nmcd.hdc, m_font );
		//}

		// Tell Windows to paint the control itself.
		*pResult = CDRF_DODEFAULT;
	}

}

void CStaffPage10::OnCustomdrawMyList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
	//CListCtrl plist = reinterpret_cast<CListCtrl*>pNMHDR;


	// Take the default processing unless we set this to something else below.
	*pResult = 0;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.

	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		// This is the notification message for an item.  We'll request
		// notifications before each subitem's prepaint stage.

		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{
		// This is the prepaint stage for a subitem. Here's where we set the
		// item's text and background colors. Our return value will tell 
		// Windows to draw the subitem itself, but it will use the new colors
		// we set here.
		// The text color will cycle through red, green, and light blue.
		// The background color will be light blue for column 0, red for
		// column 1, and black for column 2.

		if(pLVCD->iSubItem  == 0 || pLVCD->iSubItem  == 1)
		{
			m_font.DeleteObject();
			LOGFONT accesscontrol_static_lfont = {13,0,0,0,FW_BOLD,0,0,0,HANGUL_CHARSET,0,0,0,0,"돋움"};
			m_font.CreateFontIndirect(&accesscontrol_static_lfont);
			SelectObject(pLVCD->nmcd.hdc, m_font);
			//	pLVCD->clrText = RGB(255,0,0);
			SelectObject( pLVCD->nmcd.hdc, m_font );
		}
		else
		{
			m_font.DeleteObject();
			LOGFONT accesscontrol_static_lfont = {12,0,0,0,NULL,0,0,0,HANGUL_CHARSET,0,0,0,0,"돋움"};
			m_font.CreateFontIndirect(&accesscontrol_static_lfont);
			//	pLVCD->clrText = RGB(0,255,0);
			SelectObject( pLVCD->nmcd.hdc, m_font );
		}

		// Tell Windows to paint the control itself.
		*pResult = CDRF_DODEFAULT;
	}
}

void CStaffPage10::OnNMClickMyriderList(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	if(!pItemNotify->pRow || !pItemNotify->pColumn)
		return;
 
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CXTPGridRecord *pRecord = m_MyList.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	int nColumn = pItemNotify->pColumn->GetIndex();

	int nCompany = m_MyList.GetItemLong(pRecord);
	int nRNo = _ttoi(m_MyList.GetItemText(pRecord, 0));

	if(nColumn <1)
		LU->ShowRiderInfoDlg(nCompany, nRNo);	
}

void CStaffPage10::OnEnChangeEdit1()
{
	CString strSearch; m_edtOtherRider.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_OtherList.GetRecords();

	for(int i=ZERO; i<pRecords->GetCount(); i++)
	{ 
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString strRNo = pRecord->GetItem(TWO)->GetCaption(NULL);
		CString strRName = pRecord->GetItem(FOUR)->GetCaption(NULL);
		CString strJumin = m_OtherList.GetItemString(pRecord);

		if(strRNo.Find(strSearch) >= ZERO ||
			strRName.Find(strSearch) >= ZERO ||
			strJumin.Find(strSearch) >= ZERO)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_OtherList.Populate();		
}

void CStaffPage10::OnEnChangeEdit2()
{
	CString strSearch; m_edtMyRider.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_MyList.GetRecords();

	for(int i=ZERO; i<pRecords->GetCount(); i++)
	{ 
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString strRNo = pRecord->GetItem(ZERO)->GetCaption(NULL);
		CString strRName = pRecord->GetItem(THREE)->GetCaption(NULL);
		CString strID = pRecord->GetItem(TWO)->GetCaption(NULL);
		CString strJumin = m_MyList.GetItemString(pRecord);

		if(strRNo.Find(strSearch) >= ZERO ||
			strRName.Find(strSearch) >= ZERO ||
			strID.Find(strSearch) >= ZERO ||
			strJumin.Find(strSearch) >= ZERO)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_MyList.Populate();		
}

void CStaffPage10::OnBnClickedRegisterButton2()
{
	CRiderAllocateDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		CRiderAdviceDlg2010 dlg1;
		dlg1.m_nRiderCompany = dlg.m_nGetRiderCompany;
		dlg1.m_nRNo = dlg.m_nGetRNo;
		dlg1.m_nCompany = m_ci.m_nCompanyCode;

		if(dlg1.DoModal() == IDOK)
		{
			RefreshList();
		}
		//RefreshList();

	}
}
