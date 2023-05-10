// CustomerPage15.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "CustomerPage16.h"


// CCustomerPage16

IMPLEMENT_DYNCREATE(CCustomerPage16, CMyFormView)

CCustomerPage16::CCustomerPage16()
	: CMyFormView(CCustomerPage16::IDD)
{
}

CCustomerPage16::~CCustomerPage16()
{
}

void CCustomerPage16::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_MAIN, m_dtpMain);
	DDX_Control(pDX, IDC_DATE_COMBO1, m_cmbDate1);
	DDX_Control(pDX, IDC_COUNT_COMBO1, m_cmbCount1);
	DDX_Control(pDX, IDC_UP_DOWN_COMBO1, m_cmbUpDown1);
	DDX_Control(pDX, IDC_REFRESH_BTN1, m_btnRefresh1);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_dtpFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_dtpTo);
	DDX_Control(pDX, IDC_COUNT_COMBO2, m_cmbCount2);
	DDX_Control(pDX, IDC_UP_DOWN_COMBO2, m_cmbUpDown2);
	DDX_Control(pDX, IDC_REFRESH_BTN2, m_btnRefresh2);

	DDX_Control(pDX, IDC_CUSTOMER_LIST, m_lstCustomer);
	
}

BEGIN_MESSAGE_MAP(CCustomerPage16, CMyFormView)

	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_BN_CLICKED(IDC_REFRESH_BTN1, OnClickedRefreshBtn1)
	ON_BN_CLICKED(IDC_REFRESH_BTN2, OnClickedRefreshBtn2)
END_MESSAGE_MAP()


#ifdef _DEBUG
void CCustomerPage16::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCustomerPage16::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CCustomerPage16::RefreshData(CMkRecordset *pRs)
{
	m_lstCustomer.DeleteAllItems();

	long nCNo, nID, nCount;
	CString  strCompany, strTel1, strLocation, strMemo;
	COleDateTime dtRegister, dtLastUse;

	for(int i=0; i<pRs->GetRecordCount(); i++)
	{
		pRs->GetFieldValue("nCNo", nCNo); 
		pRs->GetFieldValue("nID", nID);
		pRs->GetFieldValue("nCount", nCount);
		pRs->GetFieldValue("sCompany", strCompany);
		pRs->GetFieldValue("sTel1", strTel1);
		pRs->GetFieldValue("sLocation", strLocation);
		pRs->GetFieldValue("dtRegister", dtRegister);
		pRs->GetFieldValue("dtLastUse", dtLastUse);
		pRs->GetFieldValue("sMemo", strMemo);

		m_lstCustomer.InsertItem(i, ::GetStringFromLong(nID));
		m_lstCustomer.SetItemText(i, 1, strCompany);
		m_lstCustomer.SetItemText(i, 2, ::GetDashPhoneNumber(strTel1));
		m_lstCustomer.SetItemText(i, 3, dtRegister.Format("%Y-%m-%d %H:%M:%S"));
		m_lstCustomer.SetItemText(i, 4, dtLastUse.Format("%Y-%m-%d %H:%M:%S"));
		m_lstCustomer.SetItemText(i, 5, ::GetMyNumberFormat(nCount));
		m_lstCustomer.SetItemText(i, 6, strMemo);
		m_lstCustomer.SetItemText(i, 7, strLocation);

		pRs->MoveNext();

	}
	
	m_lstCustomer.Populate();
}

void CCustomerPage16::OnClickedRefreshBtn1()
{	
	COleDateTime dtDate; m_dtpMain.GetTime(dtDate);

	long nCount = ::GetLongFromEdit(&m_cmbCount1);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_customer_report_compare");
	cmd.AddParameter(::GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(dtDate);
	cmd.AddParameter(m_cmbDate1.GetCurSel());
	cmd.AddParameter(nCount);
	cmd.AddParameter(m_cmbUpDown1.GetCurSel());

	if(!rs.Execute(&cmd))
		return;

	RefreshData(&rs);
}

void CCustomerPage16::OnClickedRefreshBtn2()
{
	COleDateTime dtFrom; m_dtpFrom.GetTime(dtFrom);
	COleDateTime dtTo; m_dtpTo.GetTime(dtTo);

	long nCount = ::GetLongFromEdit(&m_cmbCount2);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_customer_report_main");
	cmd.AddParameter(::GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(dtFrom);
	cmd.AddParameter(dtTo);
	cmd.AddParameter(nCount);
	cmd.AddParameter(m_cmbUpDown2.GetCurSel());

	if(!rs.Execute(&cmd))
		return;

	RefreshData(&rs);
}


// CCustomerPage16 메시지 처리기입니다.

void CCustomerPage16::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_CUSTOMER_LIST, sizingRightBottom);

	m_dtpMain.SetTime(COleDateTime::GetCurrentTime());
	m_cmbDate1.SetCurSel(0);
	m_cmbCount1.SetCurSel(0);
	m_cmbUpDown1.SetCurSel(0);
	m_dtpFrom.SetTime(COleDateTime::GetCurrentTime() - COleDateTimeSpan(7, 0, 0, 0));
	m_dtpTo.SetTime(COleDateTime::GetCurrentTime());
	m_cmbCount2.SetCurSel(0);
	m_cmbUpDown2.SetCurSel(0);

	m_lstCustomer.InsertColumn(0,"고객번호",LVCFMT_LEFT,50);
	m_lstCustomer.InsertColumn(1,"상호",LVCFMT_LEFT,130);
	m_lstCustomer.InsertColumn(2,"전화",LVCFMT_LEFT,100);
	m_lstCustomer.InsertColumn(3,"등록일자",LVCFMT_LEFT,120);
	m_lstCustomer.InsertColumn(4,"최종주문일자",LVCFMT_LEFT,120);
	m_lstCustomer.InsertColumn(5,"검색기간건수",LVCFMT_RIGHT,80);
	m_lstCustomer.InsertColumn(6,"비고",LVCFMT_LEFT,140);
	m_lstCustomer.InsertColumn(7,"위치",LVCFMT_LEFT,200);
	m_lstCustomer.Populate();
}

void CCustomerPage16::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstCustomer.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CCustomerPage16::OnViewExcel()
{
	if(!POWER_CHECK(6900, "고객 엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nCustomerTable, 213, m_lstCustomer.GetItemCount());  
	CMyExcel::ToExcel(&m_lstCustomer);
}

