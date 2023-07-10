// MyTestView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MyTestView.h"
#include "CustomerDlg.h"
#include "CorporationDlg.h"


// CMyTestView

IMPLEMENT_DYNCREATE(CMyTestView, CK2ReportView)

CMyTestView::CMyTestView()
{
	m_bChild = FALSE;
	m_nGNo = 0;
	m_pPaintManager = NULL;
	for(int i = 0;  i < 10; i++)
		m_bSelectCol[i] = FALSE;

	m_pParentWnd = NULL;
}

CMyTestView::~CMyTestView()
{
}

BEGIN_MESSAGE_MAP(CMyTestView, CK2ReportView)
	ON_NOTIFY(NM_CLICK, XTP_ID_REPORT_CONTROL3, OnReportStartItemClick)	
	ON_NOTIFY(NM_RCLICK, XTP_ID_REPORT_CONTROL3, OnReportRClick)	
	ON_NOTIFY(NM_DBLCLK, XTP_ID_REPORT_CONTROL3, OnReportDblClick)
	ON_NOTIFY(LVN_BEGINDRAG, XTP_ID_REPORT_CONTROL3, OnReportBeginDrag)
END_MESSAGE_MAP()


// CMyTestView 그리기입니다.

void CMyTestView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CMyTestView 진단입니다.

#ifdef _DEBUG
void CMyTestView::AssertValid() const
{
	CK2ReportView::AssertValid();
}


void CMyTestView::Dump(CDumpContext& dc) const
{
	CK2ReportView::Dump(dc);
}
#endif //_DEBUG


// CMyTestView 메시지 처리기입니다.

void CMyTestView::OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/)
{
	((CCorporationDlg2*)m_pParentWnd)->m_bDragMode = TRUE;
	
	//m_bDragMode = TRUE;
	::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	//SetCapture();
}

void CMyTestView::SetWnd(CWnd *pWnd)
{
	this->m_pParentWnd = pWnd;
}	

void CMyTestView::Refresh()
{
	if(m_nGNo <= 0){
		MessageBox("그룹을 선택하여 주세요", "확인", MB_ICONINFORMATION);
		return;
	}		

	long nGNo,nCNo, nCompany,  nItem;
	CString	sPW, sCompany, sDepart, sTel1, sMobile, sName, sDong, sLocation, sEmail, sMemo, sUserID, sLoginID, sLoginPw;
	COleDateTime dtRegister;
	char buffer[10];
	BOOL bUseHomePage = FALSE;

	m_Data.DeleteAllItems();
	nItem = 0;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group_member_general3");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCustomerTable);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nGNo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_bChild);
	if(!pRs.Execute(&pCmd)) return;


	while(!pRs.IsEOF())
	{	
		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("sPW", sPW);
		pRs.GetFieldValue("sCompany", sCompany);
		pRs.GetFieldValue("sDepart", sDepart);
		pRs.GetFieldValue("sTel1", sTel1);
		pRs.GetFieldValue("sMobile", sMobile);
		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("sDong", sDong);					
		pRs.GetFieldValue("sEmail", sEmail);
		pRs.GetFieldValue("nGNo", nGNo);			
		pRs.GetFieldValue("sLoginID", sLoginID);		
		pRs.GetFieldValue("sLoginPw", sLoginPw);				
		pRs.GetFieldValue("bUseHomePage", bUseHomePage);				

		m_Data.InsertItem(nItem, CString(ltoa(nItem + 1,buffer,10)));
		m_Data.SetItemText(nItem, 1, sCompany);
		m_Data.SetItemText(nItem, 2, sDepart);
		m_Data.SetItemText(nItem, 3, sName);
		m_Data.SetItemText(nItem, 4, LF->GetDashPhoneNumber(sTel1));
		m_Data.SetItemText(nItem, 5, LF->GetDashPhoneNumber(sMobile));
		m_Data.SetItemText(nItem, 6, sLoginID);
		m_Data.SetItemText(nItem, 7, sLoginPw);
		m_Data.SetItemText(nItem, 8, bUseHomePage ? "X" : "0");
		m_Data.SetItemText(nItem, 9, sEmail);
		m_Data.SetItemLong(nItem, nCNo);
		m_Data.SetItemLong2(nItem, nGNo);

		pRs.MoveNext();
		nItem++;
	}
	pRs.Close();
	m_Data.Populate();
}


void CMyTestView::OnInitialUpdate()
{
	for(int i = 0; i < 10; i++)
		this->m_bSelectCol[i] = 0;


	if(m_pPaintManager == NULL)
		m_pPaintManager = new CGroupViewPaintManager();		

	SetPaintManager(m_pPaintManager);
	//m_Data.SetPaintManager(m_pPaintManager);
	m_pPaintManager->SetSelectCol(m_bSelectCol);	
	m_Data.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_Data.GetReportHeader()->AllowColumnRemove(FALSE);
	m_Data.GetReportHeader()->AllowColumnResize(TRUE);
	m_Data.GetReportHeader()->AllowColumnSort(TRUE);

	m_Data.InsertColumn(0, "No", DT_CENTER, 25);
	m_Data.InsertColumn(1, "상호명", DT_LEFT, 90);
	m_Data.InsertColumn(2, "부서명", DT_LEFT, 80);
	m_Data.InsertColumn(3, "담당자", DT_LEFT, 70);
	m_Data.InsertColumn(4, "전화", DT_LEFT, 90);
	m_Data.InsertColumn(5, "핸드폰", DT_LEFT, 90);
	m_Data.InsertColumn(6, "아이디", DT_LEFT, 80);
	m_Data.InsertColumn(7, "패스워드", DT_LEFT, 70);
	m_Data.InsertColumn(8, "홈페이지미사용", DT_CENTER, 45);
	m_Data.InsertColumn(9, "이메일", DT_LEFT, 150);
	m_Data.Populate();
}

void CMyTestView::ReportDblClick()
{
	if(m_Data.GetSelectedRows()->GetCount() < 0)
		return;

	long nCNo = m_Data.GetItemLong(m_Data.GetSelectedRows()->GetAt(0)->GetRecord());
	long nGNo = m_Data.GetItemLong2(m_Data.GetSelectedRows()->GetAt(0)->GetRecord());

	if(nCNo <= 0)
		return;

	CString sCNo;
	sCNo.Format("%ld", nCNo);

	CCustomerDlg dlg;
	dlg.m_strKeyword = sCNo;
	dlg.m_nSearchType = 4; //ST_CNO;
	dlg.m_bGroup = TRUE;	
	dlg.m_nTempCNo = nGNo > 0? nGNo : 0;
	dlg.m_bDongFirst = FALSE;
	dlg.DoModal();
}
void CMyTestView::OnReportDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	ReportDblClick();
}

void CMyTestView::OnReportRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow)// || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pItem->GetIndex();
	//SendMessage(WM_CONTEXTMENU,	(WPARAM)this->GetSafeHwnd(), (LPARAM)pItemNotify->pt);
	GetParent()->PostMessage(WM_CONTEXTMENU,	(WPARAM)this->GetSafeHwnd(),MAKELPARAM(pItemNotify->pt.x, pItemNotify->pt.y) );


}

void CMyTestView::OnReportStartItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pItem->GetIndex();

	if(nCol > 5)
	{
		if(m_bSelectCol[nCol])
			m_bSelectCol[nCol] = FALSE;
		else
			m_bSelectCol[nCol] = TRUE;		

		((CGroupViewPaintManager*)m_Data.GetPaintManager())->SetSelectCol(m_bSelectCol);

		//m_pPaintManager->SetSelectCol(m_bSelectCol);
		m_Data.Populate();
	}
}


