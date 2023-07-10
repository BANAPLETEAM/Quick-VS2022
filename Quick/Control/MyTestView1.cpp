// MyTestView1.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MyTestView1.h"
#include "CustomerDlg.h"


// CMyTestView1

IMPLEMENT_DYNCREATE(CMyTestView1, CK2ReportView)

CMyTestView1::CMyTestView1()
{
	m_bChild = FALSE;
	m_nGNo = 0;
	m_pPaintManager = NULL;
	for(int i = 0;  i < 20; i++)
		m_bSelectCol[i] = FALSE;
}

CMyTestView1::~CMyTestView1()
{
}

BEGIN_MESSAGE_MAP(CMyTestView1, CK2ReportView)
	ON_NOTIFY(NM_CLICK, XTP_ID_REPORT_CONTROL3, OnReportStartItemClick)	
	ON_NOTIFY(NM_RCLICK, XTP_ID_REPORT_CONTROL3, OnReportRClick)	
	ON_NOTIFY(NM_DBLCLK, XTP_ID_REPORT_CONTROL3, OnReportDblClick)
END_MESSAGE_MAP()


// CMyTestView1 그리기입니다.

void CMyTestView1::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CMyTestView1 진단입니다.

#ifdef _DEBUG
void CMyTestView1::AssertValid() const
{
	CK2ReportView::AssertValid();
}


void CMyTestView1::Dump(CDumpContext& dc) const
{
	CK2ReportView::Dump(dc);
}
#endif //_DEBUG


// CMyTestView1 메시지 처리기입니다.

void CMyTestView1::Refresh()
{
	if(m_nGNo <= 0){
		MessageBox("그룹을 선택하여 주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	long	nGNo,nCNo, nCompany,  nItem;
	CString	sPW, sCompany, sDepart, sTel1, sMobile, sName, sDong, sLocation, sRiderMemo, sMemo, sAddress;
	BOOL bGroupOwner;
	char buffer[10];	

	m_Data.DeleteAllItems();
	nItem = 1;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group_member_etc");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCustomerTable);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nGNo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_bChild);
	if(!pRs.Execute(&pCmd)) return;

	

	while(!pRs.IsEOF())
	{	
		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("nGNo", nGNo);			

		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("bGroupOwner", bGroupOwner);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("sDong", sDong);
		pRs.GetFieldValue("sAddress", sAddress);
		pRs.GetFieldValue("sLocation", sLocation);		
		pRs.GetFieldValue("sMemo", sMemo);			
		pRs.GetFieldValue("sRiderMemo", sRiderMemo);

		m_Data.InsertItem(nItem, CString(ltoa(nItem, buffer, 10)));
		m_Data.SetItemText(nItem, 1, sName);
		m_Data.SetItemText(nItem, 2, sDong);
		m_Data.SetItemText(nItem, 3, sAddress);
		m_Data.SetItemText(nItem, 4, sLocation);
		m_Data.SetItemText(nItem, 5, sMemo);
		m_Data.SetItemText(nItem, 6, sRiderMemo);
		m_Data.SetItemLong(nItem, nCNo);
		m_Data.SetItemLong2(nItem++, nGNo);

		pRs.MoveNext();
	}

	pRs.Close();
	m_Data.Populate();
}


void CMyTestView1::OnInitialUpdate()
{
	for(int i = 0; i < 20; i++)
		this->m_bSelectCol[i] = 0;


	if(m_pPaintManager == NULL)
		m_pPaintManager = new CGroupView1PaintManager();		

	SetPaintManager(m_pPaintManager);	
	m_pPaintManager->SetSelectCol(m_bSelectCol);	
	m_Data.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_Data.GetReportHeader()->AllowColumnRemove(FALSE);
	m_Data.GetReportHeader()->AllowColumnResize(TRUE);
	m_Data.GetReportHeader()->AllowColumnSort(TRUE);
	m_Data.AllowEdit(TRUE);

}

void CMyTestView1::ReportDblClick()
{
	if(m_Data.GetSelectedRows()->GetCount() < 0)
		return;

	long nCNo = m_Data.GetItemLong(m_Data.GetFirstSelectedRecord());
	long nGNo = m_Data.GetItemLong2(m_Data.GetFirstSelectedRecord());


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

void CMyTestView1::OnReportDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;


	ReportDblClick();

}

void CMyTestView1::OnReportRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pItem->GetIndex();
	//SendMessage(WM_CONTEXTMENU,	(WPARAM)this->GetSafeHwnd(), (LPARAM)pItemNotify->pt);
	GetParent()->PostMessage(WM_CONTEXTMENU,	(WPARAM)this->GetSafeHwnd(),MAKELPARAM(pItemNotify->pt.x, pItemNotify->pt.y) );


}

void CMyTestView1::OnReportStartItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pItem->GetIndex();

	if(nCol > 1)
	{
		if(m_bSelectCol[nCol])
			m_bSelectCol[nCol] = FALSE;
		else
			m_bSelectCol[nCol] = TRUE;		

		((CGroupView1PaintManager*)m_Data.GetPaintManager())->SetSelectCol(m_bSelectCol);
		//m_pPaintManager->SetSelectCol(m_bSelectCol);
		m_Data.Populate();
		//m_Data.RedrawControl();
	}
}


