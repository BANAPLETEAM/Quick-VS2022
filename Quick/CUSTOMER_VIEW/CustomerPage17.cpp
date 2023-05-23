// CustomerPage15.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "CustomerPage17.h"


// CCustomerPage17

IMPLEMENT_DYNCREATE(CCustomerPage17, CMyFormView)

CCustomerPage17::CCustomerPage17()
	: CMyFormView(CCustomerPage17::IDD)
{
	m_bMainExcel = FALSE;
}

CCustomerPage17::~CCustomerPage17()
{
}

void CCustomerPage17::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CUSTOMER_LIST, m_lstMain);
	DDX_Control(pDX, IDC_CUSTOMER_LIST2, m_lstSub);

	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_dtpMainFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_dtpMainTo);
	DDX_Control(pDX, IDC_COUNT_COMBO1, m_cmbMainCount);
	DDX_Control(pDX, IDC_UP_DOWN_COMBO1, m_cmbMainUpDown);

	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM2, m_dtpSubFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO2, m_dtpSubTo);
	DDX_Control(pDX, IDC_COUNT_COMBO2, m_cmbSubCount);
	DDX_Control(pDX, IDC_UP_DOWN_COMBO2, m_cmbSubUpDown);
}

BEGIN_MESSAGE_MAP(CCustomerPage17, CMyFormView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_BN_CLICKED(IDC_REFRESH_BTN1, OnClickedRefreshBtn1)
	ON_BN_CLICKED(IDC_REFRESH_BTN2, OnClickedRefreshBtn2)
END_MESSAGE_MAP()


#ifdef _DEBUG
void CCustomerPage17::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCustomerPage17::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// CCustomerPage17 메시지 처리기입니다.

void CCustomerPage17::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_dtpMainFrom.SetTime(COleDateTime::GetCurrentTime() - COleDateTimeSpan(7, 0, 0, 0));
	m_dtpMainTo.SetTime(COleDateTime::GetCurrentTime());
	m_cmbMainCount.SetCurSel(0);
	m_cmbMainUpDown.SetCurSel(0);
	m_dtpSubFrom.SetTime(COleDateTime::GetCurrentTime() - COleDateTimeSpan(7, 0, 0, 0));
	m_dtpSubTo.SetTime(COleDateTime::GetCurrentTime());
	m_cmbSubCount.SetCurSel(0);
	m_cmbSubUpDown.SetCurSel(0);

	m_lstMain.InsertColumn(0,"고객번호",LVCFMT_LEFT,50);
	m_lstMain.InsertColumn(1,"상호",LVCFMT_LEFT,130);
	m_lstMain.InsertColumn(2,"전화",LVCFMT_LEFT,100);
	m_lstMain.InsertColumn(3,"등록일자",LVCFMT_LEFT,120);
	m_lstMain.InsertColumn(4,"최종이용일자",LVCFMT_LEFT,120);
	m_lstMain.InsertColumn(5,"검색기간건수",LVCFMT_CENTER,80);
	m_lstMain.InsertColumn(6,"위치",LVCFMT_LEFT,120);
	m_lstMain.InsertColumn(7,"주소",LVCFMT_LEFT,120);
	m_lstMain.Populate();

	m_lstSub.InsertColumn(0,"고객번호",LVCFMT_LEFT,50);
	m_lstSub.InsertColumn(1,"상호",LVCFMT_LEFT,130);
	m_lstSub.InsertColumn(2,"전화",LVCFMT_LEFT,100);
	m_lstSub.InsertColumn(3,"등록일자",LVCFMT_LEFT,120);
	m_lstSub.InsertColumn(4,"최종이용일자",LVCFMT_LEFT,120);
	m_lstSub.InsertColumn(5,"검색기간건수",LVCFMT_CENTER,80);
	m_lstSub.InsertColumn(6,"위치",LVCFMT_LEFT,120);
	m_lstSub.InsertColumn(7,"주소",LVCFMT_LEFT,120);
	m_lstSub.Populate();

	SetResize(IDC_CUSTOMER_LIST, sizingBottom);
	SetResize(IDC_CUSTOMER_LIST2, sizingRightBottom);
	SetResizeHori(IDC_CUSTOMER_LIST, IDC_CUSTOMER_LIST2);
}

void CCustomerPage17::OnClickedRefreshBtn1()
{
	m_lstMain.DeleteAllItems();

	COleDateTime dtFrom, dtTo;
	m_dtpMainFrom.GetTime(dtFrom);
	m_dtpMainTo.GetTime(dtTo);

	long nUseCount = LF->GetLongFromEdit(&m_cmbMainCount);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_bad_customer_main");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(dtFrom);
	cmd.AddParameter(dtTo);
	cmd.AddParameter(nUseCount);
	cmd.AddParameter(m_cmbMainUpDown.GetCurSel());

	if(!rs.Execute(&cmd))
		return;

	long nCNo, nID, nCount;
	CString  strCompany, strTel1, strLocation, strAddressNew;
	COleDateTime dtRegister, dtLastUse;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nCNo", nCNo);
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("sCompany", strCompany);
		rs.GetFieldValue("sTel1", strTel1);
		rs.GetFieldValue("nCount", nCount);
		rs.GetFieldValue("dtLastUse", dtLastUse);
		rs.GetFieldValue("dtRegister", dtRegister);
		rs.GetFieldValue("sLocation", strLocation);
		rs.GetFieldValue("sAddressNew", strAddressNew);

		m_lstMain.InsertItem(i, LF->GetStringFromLong(nID));
		m_lstMain.SetItemText(i, 1, strCompany);
		m_lstMain.SetItemText(i, 2, LF->GetDashPhoneNumber(strTel1));
		m_lstMain.SetItemText(i, 3, dtRegister.Format("%Y-%m-%d %H:%M:%S"));
		m_lstMain.SetItemText(i, 4, dtLastUse.Format("%Y-%m-%d %H:%M:%S"));
		m_lstMain.SetItemText(i, 5, LF->GetMyNumberFormat(nCount));
		m_lstMain.SetItemText(i, 6, strLocation);
		m_lstMain.SetItemText(i, 7, strAddressNew);

		rs.MoveNext();
	}

	m_lstMain.Populate();
}

void CCustomerPage17::OnClickedRefreshBtn2()
{
	OnClickedRefreshBtn1();

	m_lstSub.DeleteAllItems();

	COleDateTime dtFrom, dtTo, dtSubFrom, dtSubTo;
	m_dtpMainFrom.GetTime(dtFrom);
	m_dtpMainTo.GetTime(dtTo);
	m_dtpSubFrom.GetTime(dtSubFrom);
	m_dtpSubTo.GetTime(dtSubTo);

	long nUseCount, nSubUseCount;
	nUseCount = LF->GetLongFromEdit(&m_cmbMainCount);
	nSubUseCount = LF->GetLongFromEdit(&m_cmbSubCount);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_bad_customer_sub");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(dtFrom);
	cmd.AddParameter(dtTo);
	cmd.AddParameter(nUseCount);
	cmd.AddParameter(m_cmbMainUpDown.GetCurSel());
	cmd.AddParameter(dtSubFrom);
	cmd.AddParameter(dtSubTo);
	cmd.AddParameter(nSubUseCount);
	cmd.AddParameter(m_cmbSubUpDown.GetCurSel());

	if(!rs.Execute(&cmd))
		return;

	long nCNo, nID, nCount;
	CString  strCompany, strTel1, strLocation, strAddressNew;
	COleDateTime dtRegister, dtLastUse;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nCNo", nCNo);
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("sCompany", strCompany);
		rs.GetFieldValue("sTel1", strTel1);
		rs.GetFieldValue("nCount", nCount);
		rs.GetFieldValue("dtLastUse", dtLastUse);
		rs.GetFieldValue("dtRegister", dtRegister);
		rs.GetFieldValue("sLocation", strLocation);
		rs.GetFieldValue("sAddressNew", strAddressNew);

		m_lstSub.InsertItem(i, LF->GetStringFromLong(nID));
		m_lstSub.SetItemText(i, 1, strCompany);
		m_lstSub.SetItemText(i, 2, LF->GetDashPhoneNumber(strTel1));
		m_lstSub.SetItemText(i, 3, dtRegister.Format("%Y-%m-%d %H:%M:%S"));
		m_lstSub.SetItemText(i, 4, dtLastUse.Format("%Y-%m-%d %H:%M:%S"));
		m_lstSub.SetItemText(i, 5, LF->GetMyNumberFormat(nCount));
		m_lstSub.SetItemText(i, 6, strLocation);
		m_lstSub.SetItemText(i, 7, strAddressNew);

		rs.MoveNext();
	}

	m_lstSub.Populate();
}

void CCustomerPage17::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect, rect2;
	m_lstMain.GetWindowRect(&rect);
	m_lstSub.GetWindowRect(&rect2);

	if(rect.PtInRect(point))
		m_bMainExcel = TRUE;
	else if(rect2.PtInRect(point))
		m_bMainExcel = FALSE;
	else
		return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu = rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CCustomerPage17::OnViewExcel()
{
	if(!LF->POWER_CHECK(6900, "고객 엑셀변환", TRUE))
		return;

	if(m_bMainExcel)
	{
		LF->AddSecurityLog(LF->GetCurBranchInfo()->nCustomerTable, 214, m_lstMain.GetItemCount());  
		CMyExcel::ToExcel(&m_lstMain);
	}
	else
	{
		LF->AddSecurityLog(LF->GetCurBranchInfo()->nCustomerTable, 214, m_lstSub.GetItemCount());  
		CMyExcel::ToExcel(&m_lstSub);
	}
}

