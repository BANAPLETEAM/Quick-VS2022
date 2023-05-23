// MyTestView2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MyTestView2.h"
#include "CustomerDlg.h"


// CMyTestView2

IMPLEMENT_DYNCREATE(CMyTestView2, CK2ReportView)

CMyTestView2::CMyTestView2()
{
	m_bChild = FALSE;
	m_nGNo = 0;
	m_pPaintManager = NULL;
	for(int i = 0;  i < 20; i++)
		m_bSelectCol[i] = FALSE;
}

CMyTestView2::~CMyTestView2()
{
}

BEGIN_MESSAGE_MAP(CMyTestView2, CK2ReportView)
	ON_NOTIFY(NM_CLICK, XTP_ID_REPORT_CONTROL3, OnReportStartItemClick)	
	ON_NOTIFY(NM_RCLICK, XTP_ID_REPORT_CONTROL3, OnReportRClick)	
	ON_NOTIFY(NM_DBLCLK, XTP_ID_REPORT_CONTROL3, OnReportDblClick)
END_MESSAGE_MAP()


// CMyTestView2 그리기입니다.

void CMyTestView2::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CMyTestView2 진단입니다.

#ifdef _DEBUG
void CMyTestView2::AssertValid() const
{
	CK2ReportView::AssertValid();
}


void CMyTestView2::Dump(CDumpContext& dc) const
{
	CK2ReportView::Dump(dc);
}
#endif //_DEBUG


// CMyTestView2 메시지 처리기입니다.

void CMyTestView2::Refresh()
{
	if(m_nGNo <= 0){
		MessageBox("그룹을 선택하여 주세요", "확인", MB_ICONINFORMATION);
		return;
	}
	long	nGNo,nCNo,   nItem,nUncollectedAmount,nCouponCharge, nCouponType,nPriceGrade,nMileageType,nMileageValue;
	long	nReportStartDay,nReportEndDay,nIssueTaxBillDay,nPayableDay;
	CString	sPW, sCompany, sDepart, sTel1, sMobile, sName, sDong, sLocation, sEmail, sMemo, sUserID, sLoginID, sLoginPw;
	COleDateTime dtRegister;
	char buffer[10];
	BOOL bCoupon,  bGroupOwner,bCredit, bCreditAfterDiscount;

	//	BOOL bChild = (m_GroupList.GetSelectedRecord()->HasChildren()) ?  TRUE : FALSE;

	m_Data.DeleteAllItem();
	nItem = 1;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group_member_calc");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCustomerTable);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nGNo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_bChild);
	if(!pRs.Execute(&pCmd)) return;

	CString sCoupon, sCouponValue, sPriceGrade, sMile, sMileValue;

	while(!pRs.IsEOF())
	{	
		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("nGNo", nGNo);			

		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("bGroupOwner", bGroupOwner);

		pRs.GetFieldValue("bCredit", bCredit);
		pRs.GetFieldValue("bCoupon", bCoupon);
		pRs.GetFieldValue("nCouponCharge", nCouponCharge);
		pRs.GetFieldValue("nCouponType", nCouponType);

		pRs.GetFieldValue("bCreditAfterDiscount", bCreditAfterDiscount);
		pRs.GetFieldValue("nPriceGrade", nPriceGrade);
		pRs.GetFieldValue("nMileageType", nMileageType);		
		pRs.GetFieldValue("nMileageValue", nMileageValue);

		pRs.GetFieldValue("nReportStartDay", nReportStartDay);
		pRs.GetFieldValue("nReportEndDay", nReportEndDay);
		pRs.GetFieldValue("nIssueTaxBillDay", nIssueTaxBillDay);
		pRs.GetFieldValue("nPayableDay", nPayableDay);
		pRs.GetFieldValue("nUncollectedAmount", nUncollectedAmount);		

		CString sCredit = bCredit ? "O" : "X";
		CString sIsCoupon = bCoupon ? "O" : "X";

		switch(nCouponType)
		{
		case 0:				
			sCouponValue = LF->GetMyNumberFormat(nCouponCharge);
			sCoupon = " %";
			break;
		case 1:				
			sCouponValue = LF->GetMyNumberFormat(nCouponCharge);
			sCoupon = " 원";
			break;
		case 2:
			sCouponValue = "A";
			sCoupon = "타입";
			break;
		case 3:
			sCouponValue = "B";
			sCoupon = "타입";
			break;
		case 4:
			sCouponValue = "C";
			sCoupon = "타입";
			break;
		case 5:
			sCouponValue = "D";
			sCoupon = "타입";
			break;			
		default:
			sCouponValue = "N/A";
			sCoupon = "";
			break;
		}
		CString sCreditAfer = bCreditAfterDiscount? "O" : "X";
		switch(nPriceGrade)
		{
		case 0:				
			sPriceGrade = "A";
			break;
		case 1:				
			sPriceGrade = "B";
			break;
		case 2:
			sPriceGrade = "C";
			break;
		case 3:
			sPriceGrade = "D";
			break;
		}
		switch(nMileageType)
		{
		case 0:				
			sMileValue = LF->GetMyNumberFormat(nCouponCharge);
			sMile = " %";
			break;
		case 1:				
			sMileValue = LF->GetMyNumberFormat(nCouponCharge);
			sMile = " 원";
			break;
		case 2:
			sMileValue = "A";
			sMile = "타입";
			break;
		case 3:
			sMileValue = "B";
			sMile = "타입";
			break;
		case 4:
			sMileValue = "C";
			sMile = "타입";
			break;
		case 5:
			sMileValue = "D";
			sMile = "타입";
			break;			
		default:
			sMileValue = "N/A";
			sMile = "";
			break;
		}


		m_Data.MyAddItem(0,CString(ltoa(nItem,buffer,10)),"No",30,FALSE, DT_CENTER);
		m_Data.MyAddItem(1,sName,				"담당자",	80,FALSE,DT_LEFT);	
		m_Data.MyAddItem(2,sCredit,				"신용",		50,FALSE,DT_CENTER);		
		m_Data.MyAddItem(3,sIsCoupon,			"쿠폰",		50,FALSE,DT_CENTER);		
		m_Data.MyAddItem(4,sCouponValue + sCoupon,"쿠폰타입",70,FALSE,DT_CENTER);					
		m_Data.MyAddItem(5,sCreditAfer,				"후정산",		55,FALSE,DT_CENTER);		
		m_Data.MyAddItem(6,sPriceGrade + "타입",		"할인타입",		70,FALSE,DT_CENTER);			
		m_Data.MyAddItem(7,sMileValue +sMile,		"마일리지",	60,FALSE,DT_LEFT);					
		m_Data.MyAddItem(8,nReportStartDay,		"정산1",		50,FALSE,DT_RIGHT);		
		m_Data.MyAddItem(9,nReportEndDay,		"정산2",	50,FALSE,DT_RIGHT);		
		m_Data.MyAddItem(10,nIssueTaxBillDay,		"계산서",		50,FALSE,DT_RIGHT);		
		m_Data.MyAddItem(11,nPayableDay,		"입금일",		50,FALSE,DT_RIGHT);					
		m_Data.MyAddItem(12,LF->GetMyNumberFormat(nUncollectedAmount),"미수금",	70,FALSE,DT_RIGHT);				

		m_Data.InsertItemDataLong(nCNo);	
		m_Data.InsertItemDataLong2(nGNo);			
		m_Data.EndItem();	

		pRs.MoveNext();
		nItem++;
	}
	pRs.Close();
	m_Data.Populate();
}
	


void CMyTestView2::OnInitialUpdate()
{
	for(int i = 0; i < 20; i++)
		this->m_bSelectCol[i] = 0;

	

	if(m_pPaintManager == NULL)
		m_pPaintManager = new CGroupView1PaintManager();		

	SetPaintManager(m_pPaintManager);
	//m_Data.SetPaintManager(m_pPaintManager);
	m_pPaintManager->SetSelectCol(m_bSelectCol);
	
	m_Data.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_Data.GetReportHeader()->AllowColumnRemove(FALSE);
	m_Data.GetReportHeader()->AllowColumnResize(TRUE);
	m_Data.GetReportHeader()->AllowColumnSort(TRUE);


}
void CMyTestView2::ReportDblClick()
{
	if(m_Data.GetSelectedCount() < 0)
		return;

	long nCNo = m_Data.GetItemDataLong(m_Data.GetSelectedRow()->GetIndex());
	long nGNo = m_Data.GetItemDataLong2(m_Data.GetSelectedRow()->GetIndex());


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


void CMyTestView2::OnReportDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{


	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow)// || !pItemNotify->pColumn)
		return;

	ReportDblClick();


}

void CMyTestView2::OnReportRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow)// || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pItem->GetIndex();
	//SendMessage(WM_CONTEXTMENU,	(WPARAM)this->GetSafeHwnd(), (LPARAM)pItemNotify->pt);
	GetParent()->PostMessage(WM_CONTEXTMENU,	(WPARAM)this->GetSafeHwnd(),MAKELPARAM(pItemNotify->pt.x, pItemNotify->pt.y) );


}

void CMyTestView2::OnReportStartItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
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
	}
}


