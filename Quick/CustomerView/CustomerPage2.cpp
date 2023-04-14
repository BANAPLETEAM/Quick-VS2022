// CustomerPage2.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "CustomerPage2.h"
#include "MainFrm.h"


// CCustomerPage2 ��ȭ �����Դϴ�.

IMPLEMENT_DYNCREATE(CCustomerPage2, CMyFormView)
CCustomerPage2::CCustomerPage2()
	: CMyFormView(CCustomerPage2::IDD)
{
	COleDateTimeSpan span(30, 0,0,0);
	m_dtFrom = COleDateTime::GetCurrentTime() - span;
	m_dtTo = COleDateTime::GetCurrentTime();
	m_bIntegrated = FALSE;
}

CCustomerPage2::~CCustomerPage2()
{
}

void CCustomerPage2::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_MINCOUNT_COMBO, m_MinCountCombo);
	DDX_Control(pDX, IDC_LIST1, m_lcData);
	DDX_Control(pDX, IDC_MINCOUNT_STATIC, m_MinCountStatic);
	DDX_Control(pDX, IDC_DATE_STATIC, m_DateStatic);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
}


BEGIN_MESSAGE_MAP(CCustomerPage2, CMyFormView)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_BN_CLICKED(IDC_DATE_BTN, OnBnClickedDateBtn)
END_MESSAGE_MAP()




// CCustomerPage2 �޽��� ó�����Դϴ�.

void CCustomerPage2::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	CImageList m_ImageList; 
	m_ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_lcData.SetImageList(&m_ImageList,LVSIL_SMALL); 
	
	m_lcData.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_lcData.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
				LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);

	m_lcData.InsertColumn(0,"����ȣ",LVCFMT_LEFT,80);
	m_lcData.InsertColumn(1,"��ȣ",LVCFMT_LEFT,250);
	m_lcData.InsertColumn(2,"��ȭ",LVCFMT_LEFT,200);
	m_lcData.InsertColumn(3,"�Ǽ�",LVCFMT_RIGHT,60);
	m_lcData.InsertColumn(4,"�ݾ�",LVCFMT_RIGHT,100);
	m_lcData.InsertColumn(5,"�ּ�",LVCFMT_LEFT,200);
	m_MinCountCombo.SetCurSel(0);

	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuToday();

	SetResize(IDC_LIST1, sizingRightBottom);

	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CCustomerPage2::RefreshList()
{
	CMyFormView::RefreshList();

	CWaitCursor wait;
	CString strMinCount, strCount, strLocation;
	int index = 0;

	UpdateData(TRUE);
	m_lcData.DeleteAllItems();
	
	m_MinCountCombo.GetWindowText(strMinCount);
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_excellent_customer5");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), ::GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), atol(strMinCount));
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);

	if(!pRs.Execute(&pCmd)) return;

	if(pRs.IsEOF()) 
	{
		MessageBox("���ǿ� ��ġ�ϴ� �����Ͱ� ���������ʽ��ϴ�.", "Ȯ��", MB_ICONINFORMATION);
	}
	else if(pRs.GetRecordCount() >= 2000) 
	{
		StatusText(0, "�����Ͱ� �� ����������, �ִ� 2000���� ǥ�õ˴ϴ�.");
	}
	else
	{
		strCount.Format("%d���� ���� �˻��Ǿ����ϴ�.", pRs.GetRecordCount());
		StatusText(0, strCount);
	}

	while(!pRs.IsEOF())
	{
		long nCNo, cnt, total, nID;
		CString strCompany, strTel;
		char buffer[20];

		pRs.GetFieldValue("lONo", nCNo);
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("sCompany", strCompany);
		pRs.GetFieldValue("sTel1", strTel);
		pRs.GetFieldValue("cnt", cnt);
		pRs.GetFieldValue("total", total);
		pRs.GetFieldValue("sLocation", strLocation);

		if(strTel.GetLength() > 4)
		{
			m_lcData.InsertItem(index, ltoa(nID, buffer, 10));
			m_lcData.SetItemText(index, 1, strCompany);
			m_lcData.SetItemText(index, 2, GetDashPhoneNumber(strTel));
			m_lcData.SetItemText(index, 3, ltoa(cnt, buffer, 10));
			m_lcData.SetItemText(index, 4, GetMyNumberFormat(ltoa(total, buffer, 10)));
			m_lcData.SetItemText(index, 5, strLocation);
			m_lcData.SetItemData(index++, nCNo);
		}
		pRs.MoveNext();		
	}		

	m_lcData.Populate();
	pRs.Close();
}

void CCustomerPage2::OnBnClickedSearchBtn()
{ 
	RefreshList();
}

void CCustomerPage2::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lcData.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CCustomerPage2::OnViewExcel()
{
	if(!POWER_CHECK(6900, "������ȯ", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nCompanyCode, 202, m_ui.nWNo, m_lcData.GetItemCount());  
	CMyExcel::ToExcel(&m_lcData);
}


void CCustomerPage2::OnBnClickedDateBtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
