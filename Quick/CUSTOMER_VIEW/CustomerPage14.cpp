// CustomerForm11.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "CustomerPage14.h"
#include "MainFrm.h"

#include "CustomerSmsDlg.h"
//#include "CustomerAddNoMapDlg.h"
#include "LogiUtil.h"

// CCustomerPage14 대화 상자입니다.



IMPLEMENT_DYNCREATE(CCustomerPage14, CMyFormView)
CCustomerPage14::CCustomerPage14()
: CMyFormView(CCustomerPage14::IDD)

{
}

CCustomerPage14::~CCustomerPage14()
{
}

void CCustomerPage14::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
					 
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_dtpFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER_REGISTER_FROM, m_dtpRegisterFrom);
	DDX_Control(pDX, IDC_DT_FROM, m_TermAfterFrom);
	DDX_Control(pDX, IDC_DT_TO, m_TermAfterTo);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_ONE_BTN, m_OneBtn);
	DDX_Control(pDX, IDC_TWO_BTN, m_TwoBtn);
	DDX_Control(pDX, IDC_THREE_BTN, m_ThreeBtn);
	DDX_Control(pDX, IDC_FOUR_BTN, m_FourBtn);
	DDX_Control(pDX, IDC_SEARCH_BTN, m_btnSearch);
	DDX_Control(pDX, IDC_AFTER_RADIO, m_rdoFromAfter);
	DDX_Control(pDX, IDC_TERM_RADIO, m_rdoFromTerm);

	DDX_Control(pDX, IDC_ONE_USE_CHK, m_chkOneUse);
	DDX_Control(pDX, IDC_TYPE_COMBO, m_cmbType);
	DDX_Control(pDX, IDC_PHONE_COMBO, m_PhoneCmb);
	DDX_Control(pDX, IDC_NOSMS_COMBO, m_NosmsCmb);
	DDX_Control(pDX, IDC_USE_COUNT_EDIT, m_editUseCount);
}

BEGIN_MESSAGE_MAP(CCustomerPage14, CMyFormView)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnClickedSearchBtn)

	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_COMMAND(ID_SEND_SMS, OnSendSms)
	ON_COMMAND(ID_DELETE, OnDeleteCustomer)
	ON_BN_CLICKED(IDC_ONE_BTN, OnBnClickedOneBtn)
	ON_BN_CLICKED(IDC_TWO_BTN, OnBnClickedTwoBtn)
	ON_BN_CLICKED(IDC_THREE_BTN, OnBnClickedThreeBtn)
	ON_BN_CLICKED(IDC_FOUR_BTN, OnBnClickedFourBtn)

	ON_CBN_SELCHANGE(IDC_TYPE_COMBO, OnCbnSelchangeTypeCombo)
	ON_CBN_SELCHANGE(IDC_PHONE_COMBO, OnCbnSelchangePhoneCombo)
	ON_CBN_SELCHANGE(IDC_NOSMS_COMBO, OnCbnSelchangeNosmsCombo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CCustomerPage14::OnNMDblclkList1)
END_MESSAGE_MAP()


// CCustomerPage14 메시지 처리기입니다.

void CCustomerPage14::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	CImageList m_ImageList; 
	m_ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&m_ImageList,LVSIL_SMALL); 

	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
		LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);

	m_List.InsertColumn(0,"번호",LVCFMT_LEFT,60);
	m_List.InsertColumn(1,"고객명",LVCFMT_LEFT,140);
	m_List.InsertColumn(2,"전화",LVCFMT_LEFT,110);
	m_List.InsertColumn(3,"등록일자",LVCFMT_LEFT,90);
	m_List.InsertColumn(4,"최종이용",LVCFMT_LEFT,90);
	m_List.InsertColumn(5,"고객주소",LVCFMT_LEFT,200);
	m_List.InsertColumn(6,"SMS거부",LVCFMT_CENTER,60);
	m_List.InsertColumn(7,"이용횟수",LVCFMT_RIGHT,60);

	m_cmbType.SetCurSel(0);
	m_PhoneCmb.SetCurSel(0);
	m_NosmsCmb.SetCurSel(0);

	m_rdoFromTerm.SetCheck(TRUE);
	SetResize(IDC_LIST1, sizingRightBottom);



}
void CCustomerPage14::FromAfterRefreshList()
{
	m_map.clear();
	m_List.DeleteAllItems();

	//CWaitCursor wait;
	COleDateTime dt, dt2, dtRegisterFrom;
	int nItem = 0;

	m_dtpRegisterFrom.GetTime(dtRegisterFrom);
	m_dtpFrom.GetTime(dt);
	CString strUseCount;
	m_editUseCount.GetWindowText(strUseCount);

	CMkRecordset rs(m_pMkDb); 
	CMkCommand cmd(m_pMkDb, "select_not_use_customer_1");
	cmd.AddParameter(GetCurBranchInfo()->nCustomerTable);
	cmd.AddParameter(GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(dt);
	cmd.AddParameter(dt2);
	cmd.AddParameter(FALSE);
	cmd.AddParameter(m_chkOneUse.GetCheck());
	cmd.AddParameter(strUseCount.GetLength() == 0 ? 0 : GetLongFromEdit(&m_editUseCount));
	cmd.AddParameter(dtRegisterFrom);

	if(!rs.Execute(&cmd)) return;

	//long nCNo, nID;
	//CString strCompany, strDepart, strName;
	//CString strTel1, strTel2;
	//CString strDong, strLocation, strPost;	
	//int  nType = 0, nAdvertCount = 0;
	//COleDateTime dtLastSentSMS, dtLastSentAdvertSMS;
	//BOOL bNoSMS;

	if(rs.IsEOF()) 		
		MessageBox("조건에 일치하는 데이터가 존재하지않습니다.", "확인", MB_ICONINFORMATION);

	long nCNo, nID, nUseCount;
	CString strCompany, strTel, strTelDepart, sTelManager, strLocation;
	COleDateTime dtRegister, dtLastUse;
	BOOL bNoSMS;
	long nPreID = -1;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{	
		rs.GetFieldValue("nCNo", nCNo);
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("sCompany", strCompany);
		rs.GetFieldValue("sTel", strTel);
		rs.GetFieldValue("sTelDepart", strTelDepart);
		rs.GetFieldValue("sTelManager", sTelManager);
		rs.GetFieldValue("sLocation", strLocation);
		rs.GetFieldValue("dtRegister", dtRegister);
		rs.GetFieldValue("dtLastUse", dtLastUse);
		rs.GetFieldValue("bNoSMS", bNoSMS);
		rs.GetFieldValue("nUseCount", nUseCount);

		if(nPreID != nID)
			m_List.InsertItem(i, GetStringFromLong(nID));
		else
			m_List.InsertItem(i, "");

		m_List.SetItemText(i, 1, strCompany);
		m_List.SetItemText(i, 2, ::GetDashPhoneNumber(strTel));
		m_List.SetItemText(i, 3, dtRegister.Format("%Y-%m-%d"));
		m_List.SetItemText(i, 4, dtLastUse.Format("%Y-%m-%d"));
		m_List.SetItemText(i, 5, strLocation);
		m_List.SetItemText(i, 6, bNoSMS == TRUE ? "거부" : "");
		m_List.SetItemText(i, 7, ::GetStringFromLong(nUseCount));
		m_List.SetItemData(i, nCNo);
		rs.MoveNext();

		nPreID = nID;
		//nItem++;
	}
	m_List.Populate();
	rs.Close();
}


void CCustomerPage14::TermAfterRefresh()
{
	m_map.clear();
	m_List.DeleteAllItems();

	//CWaitCursor wait;
	COleDateTime dt, dt2, dtRegisterFrom;
	int nItem = 0;
	m_dtpRegisterFrom.GetTime(dtRegisterFrom);
	m_TermAfterFrom.GetTime(dt);
	m_TermAfterTo.GetTime(dt2);
	CString strUseCount;
	m_editUseCount.GetWindowText(strUseCount); 

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_not_use_customer_1");
	cmd.AddParameter(GetCurBranchInfo()->nCustomerTable);
	cmd.AddParameter(GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(dt);
	cmd.AddParameter(dt2);
	cmd.AddParameter(TRUE);
	cmd.AddParameter(m_chkOneUse.GetCheck());
	cmd.AddParameter(strUseCount.GetLength() == 0 ? 0 : GetLongFromEdit(&m_editUseCount));
	cmd.AddParameter(dtRegisterFrom);

	if(!rs.Execute(&cmd)) return;

	//long nCNo, nID;
	//CString strCompany, strDepart, strName;
	//CString strTel1, strTel2;
	//CString strDong, strLocation, strPost;	
	//int  nType = 0, nAdvertCount = 0;
	//COleDateTime dtLastSentSMS, dtLastSentAdvertSMS;
	//BOOL bNoSMS;

	if(rs.IsEOF()) 		
		MessageBox("조건에 일치하는 데이터가 존재하지않습니다.", "확인", MB_ICONINFORMATION);

	long nCNo, nID, nUseCount;
	CString strCompany, strTel, strTelDepart, sTelManager, strLocation;
	COleDateTime dtRegister, dtLastUse;
	BOOL bNoSMS;
	long nPreID = -1;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{	
		rs.GetFieldValue("nCNo", nCNo);
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("sCompany", strCompany);
		rs.GetFieldValue("sTel", strTel);
		rs.GetFieldValue("sTelDepart", strTelDepart);
		rs.GetFieldValue("sTelManager", sTelManager);
		rs.GetFieldValue("sLocation", strLocation);
		rs.GetFieldValue("dtRegister", dtRegister);
		rs.GetFieldValue("dtLastUse", dtLastUse);
		rs.GetFieldValue("bNoSMS", bNoSMS);
		rs.GetFieldValue("nUseCount", nUseCount);

		if(nPreID != nID)
			m_List.InsertItem(i, GetStringFromLong(nID));
		else
			m_List.InsertItem(i, "");

		m_List.SetItemText(i, 1, strCompany);
		m_List.SetItemText(i, 2, strTel);
		m_List.SetItemText(i, 3, dtRegister.Format("%Y-%m-%d"));
		m_List.SetItemText(i, 4, dtLastUse.Format("%Y-%m-%d"));
		m_List.SetItemText(i, 5, strLocation);
		m_List.SetItemText(i, 6, bNoSMS == TRUE ? "거부" : "");
		m_List.SetItemText(i, 7, ::GetStringFromLong(nUseCount));
		rs.MoveNext();

		nPreID = nID;
		//nItem++;
	}
	m_List.Populate();
	rs.Close();
}

void CCustomerPage14::OnClickedSearchBtn()
{
	if(m_rdoFromTerm.GetCheck())	
		TermAfterRefresh();
	else
		FromAfterRefreshList();
}


void CCustomerPage14::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(29);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CCustomerPage14::OnViewExcel()
{
	if(!POWER_CHECK(6900, "고객 엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nCustomerTable, 211, m_List.GetItemCount());  
	CMyExcel::ToExcel(&m_List);
}


void CCustomerPage14::OnDeleteCustomer()
{
	if(MessageBox("선택된 고객을 정말 삭제하시겠습니까?", 
		"확인", MB_YESNO | MB_ICONINFORMATION) == IDYES)
	{
		CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

		for(int i = 0; i < pRows->GetCount(); i++) 
		{
			//m_lcData.Populate();
			CMkCommand pCmd(m_pMkDb, "delete_customer_1");
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), (long)m_List.GetItemData(pRows->GetAt(i)->GetIndex()));
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), ::GetCurBranchInfo()->nCompanyCode);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);

			CString sEtc = "고휴먼고객탭 삭제";
			pCmd.AddParameter(sEtc);

			pCmd.Execute();

		}

		OnClickedSearchBtn();
	}
}


void CCustomerPage14::OnSendSms()
{
	return;
	//if(!POWER_CHECK(5910, "SMS전송", TRUE))
	//	return;

	CREATE_MODALESS(CCustomerSmsDlg, this);
	pDlg->m_nType = 130;
	pDlg->m_nCompany = GetCurBranchInfo()->nCustomerTable;
	pDlg->m_pSourceList = &m_List;
	pDlg->m_nPhoneCol = 2;
	pDlg->m_nCTypeCol = 7;
	pDlg->m_nNotWantedCol = 8;
	pDlg->m_nLastSentCol = 9;
	pDlg->m_nNewCustomerCol = 4;
	pDlg->m_nDMLastSentCol = 10;
	pDlg->m_nDMCount = 11;
	SHOW_MODALESS(CCustomerSmsDlg, this);
}


void CCustomerPage14::OnBnClickedOneBtn()
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();

	if(dtFrom.GetHour() < BASE_HOUR) {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtFrom = dtFrom - COleDateTimeSpan(1, 0, 0, 0);
	}
	else {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
	}

	dtFrom = dtFrom - COleDateTimeSpan(30, 0, 0, 0);
	m_dtpFrom.SetTime(dtFrom);
}

void CCustomerPage14::OnBnClickedTwoBtn()
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();

	if(dtFrom.GetHour() < BASE_HOUR) {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtFrom = dtFrom - COleDateTimeSpan(1, 0, 0, 0);
	}
	else {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
	}

	dtFrom = dtFrom - COleDateTimeSpan(60, 0, 0, 0);
	m_dtpFrom.SetTime(dtFrom);
}

void CCustomerPage14::OnBnClickedThreeBtn()
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();

	if(dtFrom.GetHour() < BASE_HOUR) {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtFrom = dtFrom - COleDateTimeSpan(1, 0, 0, 0);
	}
	else {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
	}

	dtFrom = dtFrom - COleDateTimeSpan(90, 0, 0, 0);
	m_dtpFrom.SetTime(dtFrom);
}

void CCustomerPage14::OnBnClickedFourBtn()
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();

	if(dtFrom.GetHour() < BASE_HOUR) {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtFrom = dtFrom - COleDateTimeSpan(1, 0, 0, 0);
	}
	else {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
	}

	dtFrom = dtFrom - COleDateTimeSpan(120, 0, 0, 0);
	m_dtpFrom.SetTime(dtFrom);
}



void CCustomerPage14::OnCbnSelchangeTypeCombo()
{
	RefreshList();
}

void CCustomerPage14::OnCbnSelchangePhoneCombo()
{
	RefreshList();
}

void CCustomerPage14::OnCbnSelchangeNosmsCombo()
{
	RefreshList();
}

void CCustomerPage14::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	/*
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem < 0)
		return;
	int nItem = m_List.GetSelectionMark();
	if(nItem < 0) 
	{
		MessageBox("아이템을 선택해주세요","확인",MB_ICONINFORMATION);
		return;
	}

	long nCNo = (long)m_List.GetItemData(nItem);
	if(nCNo < 0) return;

	CREATE_MODALESS(CCustomerAddNoMapDlg, this);
	pDlg->SetLoadMap(FALSE);
	pDlg->SetCompany(m_ci.GetCurBranchInfo()->nUseCustomerTable);
	pDlg->SetNewMode(FALSE);
	pDlg->SetCNo(nCNo);	
	pDlg->DoModal();
	SHOW_MODALESS(CCustomerAddNoMapDlg, this);
	*/

	*pResult = 0;
}
