// CustomerPage4.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CustomerPage4.h"


// CCustomerPage4 대화 상자입니다.

IMPLEMENT_DYNCREATE(CCustomerPage4, CMyFormView)
CCustomerPage4::CCustomerPage4()
	: CMyFormView(CCustomerPage4::IDD)
	, m_strMinCount(_T(""))
{
	m_bIntegrated = FALSE;
}

CCustomerPage4::~CCustomerPage4()
{

}

void CCustomerPage4::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MINCOUNT_COMBO, m_MinCountCombo);
	DDX_Control(pDX, IDC_LIST1, m_lcData);
	DDX_Control(pDX, IDC_DATE_COMBO, m_DateCombo);
	DDX_CBString(pDX, IDC_MINCOUNT_COMBO, m_strMinCount);
	DDX_Control(pDX, IDC_MINCOUNT_STATIC, m_MinCountStatic);
	DDX_Control(pDX, IDC_DATE_STATIC, m_DateStatic);
	DDX_Control(pDX, IDC_SEARCH_BTN, m_SearchBtn);
}


BEGIN_MESSAGE_MAP(CCustomerPage4, CMyFormView)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
END_MESSAGE_MAP()


// CCustomerPage4 메시지 처리기입니다.

void CCustomerPage4::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	CImageList m_ImageList; 
	m_ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_lcData.SetImageList(&m_ImageList,LVSIL_SMALL); 
	
	m_lcData.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_lcData.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
				LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);

	m_lcData.InsertColumn(0,"고객번호",LVCFMT_LEFT,80);
	m_lcData.InsertColumn(1,"상호",LVCFMT_LEFT,180);
	m_lcData.InsertColumn(2,"전화",LVCFMT_LEFT,150);
	m_lcData.InsertColumn(3,"등록일자",LVCFMT_LEFT,80);
	m_lcData.InsertColumn(4,"최종주문일자",LVCFMT_LEFT,100);
	m_lcData.InsertColumn(5,"기준기간 건수",LVCFMT_RIGHT,120);
	m_lcData.InsertColumn(6,"비고",LVCFMT_LEFT,140);
	m_lcData.InsertColumn(7,"위치",LVCFMT_LEFT,200);

	m_DateCombo.SetCurSel(1);
	m_MinCountCombo.SetCurSel(1);
	
	SetResize(IDC_LIST1, sizingRightBottom);
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCustomerPage4::RefreshList()
{
	CMyFormView::RefreshList();

	CWaitCursor wait;
	CString strMinCount, strCount;
	int index = 0;
	
	UpdateData(TRUE);
	m_lcData.DeleteAllItems();
	
	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	COleDateTimeSpan beforeSpan, afterSpan;

	switch(m_DateCombo.GetCurSel())
	{
	case 0:
		afterSpan.SetDateTimeSpan(7,0,0,0);
		beforeSpan.SetDateTimeSpan(7,0,0,0);
		break;
	case 1:
		afterSpan.SetDateTimeSpan(14,0,0,0);
		beforeSpan.SetDateTimeSpan(14,0,0,0);
		break;
	case 2:
		afterSpan.SetDateTimeSpan(30,0,0,0);
		beforeSpan.SetDateTimeSpan(30,0,0,0);
		break;
	case 3:
		afterSpan.SetDateTimeSpan(7,0,0,0);
		beforeSpan.SetDateTimeSpan(14,0,0,0);
		break;
	case 4:
		afterSpan.SetDateTimeSpan(7,0,0,0);
		beforeSpan.SetDateTimeSpan(30,0,0,0);
		break;
	default:
		AfxMessageBox("invalid row number");
	}

	m_MinCountCombo.GetWindowText(strMinCount);
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_bad_customer5");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), atol(strMinCount));
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtCur - afterSpan - beforeSpan);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtCur - afterSpan);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtCur - afterSpan);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtCur);

	if(!pRs.Execute(&pCmd)) return;

	if(pRs.IsEOF()) 
	{
		MessageBox("조건에 일치하는 데이터가 존재하지않습니다.", "확인", MB_ICONINFORMATION);
	}
	else
	{
		strCount.Format("%d명의 고객이 검색 되었습니다.", pRs.GetRecordCount());
		LF->StatusText(0, strCount);
	}


	long nCNo, nBeforeCnt, nID;
	CString strCompany, strTel;
	COleDateTime dtRegister, dtLast;
	char buffer[20];
	CString strEtc, strLocation;

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("lONo", nCNo);
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("sCompany", strCompany);
		pRs.GetFieldValue("sTel1", strTel);
		pRs.GetFieldValue("dtRegister", dtRegister);
		pRs.GetFieldValue("dtLast", dtLast);
		pRs.GetFieldValue("BeforeCount", nBeforeCnt);
		pRs.GetFieldValue("sLocation", strLocation);

		if(strTel.GetLength() > 4)
		{
			m_lcData.InsertItem(index, ltoa(nID, buffer, 10));
			m_lcData.SetItemText(index, 1, strCompany);
			m_lcData.SetItemText(index, 2, LF->GetDashPhoneNumber(strTel));
			m_lcData.SetItemText(index, 3, dtRegister.Format("%Y-%m-%d"));
			m_lcData.SetItemText(index, 4, dtLast.Format("%Y-%m-%d"));
			m_lcData.SetItemText(index, 5, ltoa(nBeforeCnt, buffer, 10));
//			m_lcData.SetItemData(index, nCNo);

			if(nBeforeCnt >= 6)
			{
				COLOR_STRUCT *pCS = new COLOR_STRUCT;

				pCS->crBk = RGB(255,200,200);
				pCS->crText = RGB(0,0,0);
				m_lcData.SetItemData(index, (DWORD_PTR)pCS);
				strEtc = "이용중단 가능성 높음";
			}
			else 
			{
				strEtc = "";
			}

			m_lcData.SetItemText(index, 6, strEtc);
			m_lcData.SetItemText(index++, 7, strLocation);
		}
		pRs.MoveNext();		
	}		
	
	m_lcData.Populate();
	pRs.Close();	
}

void CCustomerPage4::OnBnClickedSearchBtn()
{
	RefreshList();
}

void CCustomerPage4::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lcData.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CCustomerPage4::OnViewExcel()
{
	if(!LF->POWER_CHECK(6900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 204, m_ui.nWNo, m_lcData.GetItemCount());  
	CMyExcel::ToExcel(&m_lcData);
}
