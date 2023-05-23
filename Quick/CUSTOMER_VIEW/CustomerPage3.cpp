// CustomerPage3.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CustomerPage3.h"
#include "MainFrm.h"
#include "NewCustomerSmsDlg.h"

// CCustomerPage3 대화 상자입니다.

IMPLEMENT_DYNCREATE(CCustomerPage3, CMyFormView)
CCustomerPage3::CCustomerPage3()
	: CMyFormView(CCustomerPage3::IDD)
{
	m_bIntegrated = FALSE;
}

CCustomerPage3::~CCustomerPage3()
{
}

void CCustomerPage3::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_REPORT, m_lcData);
	DDX_Control(pDX, IDC_DATE_STATIC, m_DateStatic);
	DDX_Control(pDX, IDC_TODAY_BTN, m_Btn0);
	DDX_Control(pDX, IDC_ONE_BEFORE_BTN, m_Btn1);
	DDX_Control(pDX, IDC_TWO_BEFORE_BTN, m_Btn2);
	DDX_Control(pDX, IDC_FIVE_BEFORE_BTN, m_Btn3);
	DDX_Control(pDX, IDC_TEN_BEFORE_BTN, m_Btn4);
	DDX_Control(pDX, IDC_TWELVE_BEFORE_BTN, m_Btn5);
	DDX_Control(pDX, IDC_MONTH_BEFORE_BTN, m_Btn6);
	DDX_Control(pDX, IDC_SEARCH_BTN, m_Btn7);
	DDX_Control(pDX, IDC_NO_GENERAL_CUSTOMER_CHECK, m_chkNoGeneralCustomer);
}


BEGIN_MESSAGE_MAP(CCustomerPage3, CMyFormView)
	ON_BN_CLICKED(IDC_TODAY_BTN, OnClickedTodayBtn)
	ON_BN_CLICKED(IDC_ONE_BEFORE_BTN, OnClickedOneBeforeBtn)
	ON_BN_CLICKED(IDC_TWO_BEFORE_BTN, OnClickedTwoBeforeBtn)
	ON_BN_CLICKED(IDC_FIVE_BEFORE_BTN, OnClickedFiveBeforeBtn)
	ON_BN_CLICKED(IDC_TEN_BEFORE_BTN, OnClickedTenBeforeBtn)
	ON_BN_CLICKED(IDC_TWELVE_BEFORE_BTN, OnClickedTwelveBeforeBtn)
	ON_BN_CLICKED(IDC_MONTH_BEFORE_BTN, OnClickedMonthBeforeBtn)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnClickedSearchBtn)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_COMMAND(ID_SEND_SMS, OnSendSMS)
END_MESSAGE_MAP()


// CCustomerPage3 메시지 처리기입니다.

void CCustomerPage3::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	CImageList m_ImageList; 
	m_ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_lcData.SetImageList(&m_ImageList,LVSIL_SMALL); 
	
	//m_ListFont.CreateFontIndirect(&m_listlogfont);
	//m_lcData.SetFont(&m_ListFont);
	m_lcData.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_lcData.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
				LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);

	m_lcData.InsertColumn(0,"번호",LVCFMT_LEFT,60);
	m_lcData.InsertColumn(1,"상호",LVCFMT_LEFT,140);
	m_lcData.InsertColumn(2,"부서",LVCFMT_LEFT,100);
	m_lcData.InsertColumn(3,"담당",LVCFMT_LEFT,80);
	m_lcData.InsertColumn(4,"전화번호",LVCFMT_LEFT,110);
	m_lcData.InsertColumn(5,"등록일자",LVCFMT_LEFT,80);
	m_lcData.InsertColumn(6,"기준동",LVCFMT_LEFT,90);
	m_lcData.InsertColumn(7,"우편번호",LVCFMT_LEFT,70);
	m_lcData.InsertColumn(8,"위치",LVCFMT_LEFT,280);
	m_lcData.InsertColumn(9,"신용",LVCFMT_LEFT,40);
	m_lcData.InsertColumn(10,"가산금",LVCFMT_LEFT,50);

	SetResize(IDC_REPORT, sizingRightBottom);

	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCustomerPage3::OnClickedTodayBtn()
{
	m_FromDT.SetTime(COleDateTime::GetCurrentTime());
	OnClickedSearchBtn();
}

void CCustomerPage3::OnClickedOneBeforeBtn()
{
	COleDateTimeSpan span(1,0,0,0);
	m_FromDT.SetTime(COleDateTime::GetCurrentTime() - span);
	OnClickedSearchBtn();
}

void CCustomerPage3::OnClickedTwoBeforeBtn()
{
	COleDateTimeSpan span(2,0,0,0);
	m_FromDT.SetTime(COleDateTime::GetCurrentTime() - span);
	OnClickedSearchBtn();
}

void CCustomerPage3::OnClickedFiveBeforeBtn()
{
	COleDateTimeSpan span(5,0,0,0);
	m_FromDT.SetTime(COleDateTime::GetCurrentTime() - span);
	OnClickedSearchBtn();
}

void CCustomerPage3::OnClickedTenBeforeBtn()
{
	COleDateTimeSpan span(10,0,0,0);
	m_FromDT.SetTime(COleDateTime::GetCurrentTime() - span);
	OnClickedSearchBtn();
}

void CCustomerPage3::OnClickedTwelveBeforeBtn()
{
	COleDateTimeSpan span(20,0,0,0);
	m_FromDT.SetTime(COleDateTime::GetCurrentTime() - span);
	OnClickedSearchBtn();
}

void CCustomerPage3::OnClickedMonthBeforeBtn()
{
	COleDateTimeSpan span(30,0,0,0);
	m_FromDT.SetTime(COleDateTime::GetCurrentTime() - span);
	OnClickedSearchBtn();
}

void CCustomerPage3::OnClickedSearchBtn()
{
	CWaitCursor wait;
	COleDateTime dt;
	int nItem = 0;
	char buffer[20];

	m_lcData.DeleteAllItems();
	m_FromDT.GetTime(dt);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_new_customer4");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dt);
	pCmd.AddParameter(m_chkNoGeneralCustomer.GetCheck());
	

	if(!pRs.Execute(&pCmd)) return;

	long nCNo, nID, nPreCNo = 0;
	CString strCompany, strDepart, strName;
	CString strTel1, strDong, strLocation, strPost;
	BOOL bCredit;
	int nDiscount;

	if(pRs.IsEOF()) {
		MessageBox("조건에 일치하는 데이터가 존재하지않습니다.", "확인", MB_ICONINFORMATION);
	}
	else {
		CString strText;
		strText.Format("%d개의 고객데이터가 검색되었습니다.", pRs.GetRecordCount());
		LF->StatusText(0, strText);
	}

	while(!pRs.IsEOF())
	{	
		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("sCompany", strCompany);
		pRs.GetFieldValue("sDepart", strDepart);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("sTel1", strTel1);
		pRs.GetFieldValue("sDong", strDong);
		pRs.GetFieldValue("sPostCode", strPost);
		pRs.GetFieldValue("sLocation", strLocation);
		pRs.GetFieldValue("bCredit", bCredit);
		pRs.GetFieldValue("nDiscount", nDiscount);
		pRs.GetFieldValue("dtRegister", dt);

		if(nPreCNo != nCNo)
			m_lcData.InsertItem(nItem, ltoa(nID, buffer, 10));
		else
			m_lcData.InsertItem(nItem, "");
			
		m_lcData.SetItemText(nItem, 1, strCompany);
		m_lcData.SetItemText(nItem, 2, strDepart);
		m_lcData.SetItemText(nItem, 3, strName);
		m_lcData.SetItemText(nItem, 4, LF->GetDashPhoneNumber(strTel1));
		m_lcData.SetItemText(nItem, 5, dt.Format("%Y-%m-%d"));
		m_lcData.SetItemText(nItem, 6, strDong);
		m_lcData.SetItemText(nItem, 7, strPost);
		m_lcData.SetItemText(nItem, 8, strLocation);
		m_lcData.SetItemText(nItem, 9, bCredit ? "신용" : "");
		m_lcData.SetItemText(nItem, 10, ltoa(nDiscount, buffer, 10));
		m_lcData.SetItemData(nItem, nCNo);

		nPreCNo = nCNo;
		pRs.MoveNext();
		nItem++;
	}

	pRs.Close();
	m_lcData.Populate();
}



void CCustomerPage3::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lcData.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(16);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CCustomerPage3::OnViewExcel()
{
	if(!LF->POWER_CHECK(6900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 203, m_ui.nWNo, m_lcData.GetItemCount());  
	CMyExcel::ToExcel(&m_lcData);
}

void CCustomerPage3::OnSendSMS()
{
	CNewCustomerSmsDlg dlg;
	dlg.m_XTPGridRecords = m_lcData.GetRecords();
	dlg.DoModal();

}