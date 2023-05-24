// CustomerPage7.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CustomerPage7.h"


// CCustomerPage7 대화 상자입니다.

IMPLEMENT_DYNCREATE(CCustomerPage7, CMyFormView)
CCustomerPage7::CCustomerPage7()
: CMyFormView(CCustomerPage7::IDD)
{
	COleDateTimeSpan span(30, 0,0,0);
	m_dtFrom = COleDateTime::GetCurrentTime() - span;
	m_dtTo = COleDateTime::GetCurrentTime();
	m_bIntegrated = FALSE;
}

CCustomerPage7::~CCustomerPage7()
{
}

void CCustomerPage7::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_MINCOUNT_COMBO, m_MinCountCombo);
	DDX_Control(pDX, IDC_LIST1, m_lcData);
	DDX_Control(pDX, IDC_MINCOUNT_STATIC, m_MinCountStatic);
	DDX_Control(pDX, IDC_DATE_STATIC, m_DateStatic);
	DDX_Control(pDX, IDC_TYPE_COMBO, m_TypeCombo);
	DDX_Control(pDX, IDC_TYPE_STATIC, m_TypeStatic);
}


BEGIN_MESSAGE_MAP(CCustomerPage7, CMyFormView)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_CBN_SELCHANGE(IDC_TYPE_COMBO, OnCbnSelchangeTypeCombo)
END_MESSAGE_MAP()


// CCustomerPage7 메시지 처리기입니다.

void CCustomerPage7::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	CImageList m_ImageList; 
	m_ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_lcData.SetImageList(&m_ImageList,LVSIL_SMALL); 

	//	m_ListFont.CreateFontIndirect(&m_listlogfont);
	//	m_lcData.SetFont(&m_ListFont);
	m_lcData.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_lcData.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
		LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);

	m_MinCountCombo.SetCurSel(0);
	m_TypeCombo.SetCurSel(0);
	InitColumn();

	SetResize(IDC_LIST1, sizingRightBottom);
}

void CCustomerPage7::InitColumn()
{
	int nType = m_TypeCombo.GetCurSel();

	for(int nColumnIndex = 0; nColumnIndex < kColumnsNameTotal; ++nColumnIndex)
	{
		m_lcData.GetColumns()->Remove(m_columnData[nColumnIndex]);
	}

	if(nType == 0 || nType == 1 || nType == 3)
	{
		const char *szDong[] = {"출발지동", "도착지동", "",  "의뢰지동"};

		m_columnData[kStartDong] = m_lcData.InsertColumn1(kStartDong ,szDong[nType],LVCFMT_LEFT, 150);
		m_columnData[kArrivalDong] = m_lcData.InsertColumn1(kArrivalDong,"도착지동",LVCFMT_LEFT, 0);
		m_columnData[kNumber] = m_lcData.InsertColumn1(kNumber,"건수",LVCFMT_LEFT,100);
		m_columnData[kAmount] = m_lcData.InsertColumn1(kAmount,"금액",LVCFMT_RIGHT,200);
	}
	else 
	{
		m_columnData[kStartDong] =m_lcData.InsertColumn1(kStartDong,"출발지동",LVCFMT_LEFT, 150);
		m_columnData[kArrivalDong] = m_lcData.InsertColumn1(kArrivalDong,"도착지동",LVCFMT_LEFT, 150);
		m_columnData[kNumber] = m_lcData.InsertColumn1(kNumber,"건수",LVCFMT_LEFT,100);
		m_columnData[kAmount] = m_lcData.InsertColumn1(kAmount,"금액",LVCFMT_RIGHT,200);
	}

	m_lcData.Populate();
}

void CCustomerPage7::RefreshList()
{
	CMyFormView::RefreshList();

	CWaitCursor wait;
	CString strMinCount, strCount;
	int index = 0;
	int nType = m_TypeCombo.GetCurSel();

	UpdateData(TRUE);
	m_lcData.DeleteAllItems();
	InitColumn();

	/**** 본사/지사 처리가 안되어 있음 ****/

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_analysis_dong4");
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), atol(strMinCount));
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nType);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);

	m_lcData.Populate();

	if(!pRs.Execute(&pCmd)) return;

	if(pRs.IsEOF()) 
	{
		MessageBox("조건에 일치하는 데이터가 존재하지않습니다.", "확인", MB_ICONINFORMATION);
	}
	else
	{
		strCount.Format("%d개의 통계데이타가 검색되었습니다.", pRs.GetRecordCount());
		LF->StatusText(0, strCount);
		m_lcData.Populate();
	}

	while(!pRs.IsEOF())
	{
		long nCount, nTotal;
		char buffer[20];
		CString strStart, strDest;

		pRs.GetFieldValue("sStart", strStart);
		pRs.GetFieldValue("sDest", strDest);
		pRs.GetFieldValue("nCount", nCount);
		pRs.GetFieldValue("nTotal", nTotal);

		m_lcData.InsertItem(index, strStart);
		m_lcData.SetItemText(index, kArrivalDong, strDest);
		m_lcData.SetItemText(index, kNumber, ltoa(nCount, buffer, 10));
		m_lcData.SetItemText(index++, kAmount , LF->GetMyNumberFormat(ltoa(nTotal, buffer, 10)));

		pRs.MoveNext();		
	}		

	m_lcData.Populate();
	pRs.Close();
	
}

void CCustomerPage7::OnBnClickedSearchBtn()
{
	RefreshList();
}

void CCustomerPage7::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lcData.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CCustomerPage7::OnViewExcel()
{
	if(!LF->POWER_CHECK(8900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 603, m_ui.nWNo, m_lcData.GetItemCount());  

	CMyExcel::ToExcel(&m_lcData);
}

void CCustomerPage7::OnCbnSelchangeTypeCombo()
{
	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 603, m_ui.nWNo, m_lcData.GetItemCount());  
	RefreshList();
}
