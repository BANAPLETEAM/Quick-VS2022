
#include "stdafx.h"
#include "resource.h"
#include "virtualrecord.h"
#include "MyReportControl.h"
#include "MainFrm.h"

long CVirtualRecord::m_nSelectRow = 0;
long CVirtualRecord::m_nCompanyCode = 0;
long CVirtualRecord::m_nDOrderCompany = 0;
long CVirtualRecord::m_bIntegrated = FALSE;
long CVirtualRecord::m_nRcpTimeCol = 0; 
long CVirtualRecord::m_nStartCol = 0;
long CVirtualRecord::m_nRcpTimeColor1 = 0;
long CVirtualRecord::m_nRcpTimeColor2 = 0;
long CVirtualRecord::m_nRcpTimeColor3 = 0;
long CVirtualRecord::m_nUseCountCol = 0;
BOOL CVirtualRecord::m_bUseNewRegion = FALSE;
long CVirtualRecord::m_nPayTypeCol = 0;
CMyReportControl *CVirtualRecord::m_pMyControl = NULL;
 
long CVirtualRecord::m_crStateText1;
long CVirtualRecord::m_crStateText2;
long CVirtualRecord::m_crStateText3;
long CVirtualRecord::m_crStateText4;
long CVirtualRecord::m_crStateText5;
long CVirtualRecord::m_crStateText6;
long CVirtualRecord::m_crStateText7;
long CVirtualRecord::m_crStateText8;
long CVirtualRecord::m_crStateText9;
long CVirtualRecord::m_crStateText10;
long CVirtualRecord::m_crStateTextA;
long CVirtualRecord::m_crStateBack1;
long CVirtualRecord::m_crStateBack2;
long CVirtualRecord::m_crStateBack3;
long CVirtualRecord::m_crStateBack4;
long CVirtualRecord::m_crStateBack5;
long CVirtualRecord::m_crStateBack6;
long CVirtualRecord::m_crStateBack7;
long CVirtualRecord::m_crStateBack8;
long CVirtualRecord::m_crStateBack9;
long CVirtualRecord::m_crStateBack10;
long CVirtualRecord::m_crStateBack12;
long CVirtualRecord::m_crStateBack15;
BOOL CVirtualRecord::m_bUsePickupNot;
MAP_ORDER_STATE_SECOND_SORT_MAP CVirtualRecord::m_mapSecondSort;

bool compare_state(long nState1, long nState2, long nTNo1, long nTNo2)
{
	MAP_ORDER_STATE_SECOND_SORT_MAP::iterator it1 = CVirtualRecord::m_mapSecondSort.find(nState1);
	MAP_ORDER_STATE_SECOND_SORT_MAP::iterator it2 = CVirtualRecord::m_mapSecondSort.find(nState2);

	long nStateTemp1 = 0;
	long nStateTemp2 = 0; 

	if(it1 == CVirtualRecord::m_mapSecondSort.end()) //설정 안된애들은 뒤로
		nStateTemp1 = nState1 + 1000;
	else
		nStateTemp1 = it1->second;

	if(it2 == CVirtualRecord::m_mapSecondSort.end())
		nStateTemp2 = nState2 + 1000;
	else
		nStateTemp2 = it2->second;

	//if(nStateTemp1 == nStateTemp2)
	//	return nTNo1 < nTNo2;

	return nStateTemp1 < nStateTemp2;
}

bool string_compare_greator(ArrangeIndex elem1, ArrangeIndex elem2)
{
	BOOL bComp1 = elem1.bStateSecondSort && compare_state(elem1.nState, elem2.nState, elem1.nTNo, elem2.nTNo);
	BOOL bSame1 = (!elem1.bStateSecondSort || elem1.nState == elem2.nState);

	if(bSame1 && strcmp(elem1.pszData, elem2.pszData) == 0)
		return elem1.nTNo < elem2.nTNo;

	return (bComp1 || bSame1 && (strcmp(elem1.pszData, elem2.pszData) > 0));
}

bool string_compare_less(ArrangeIndex elem1, ArrangeIndex elem2)
{
	BOOL bComp1 = elem1.bStateSecondSort && compare_state(elem1.nState, elem2.nState, elem1.nTNo, elem2.nTNo);
	BOOL bSame1 = (!elem1.bStateSecondSort || elem1.nState == elem2.nState);

	if(bSame1 && strcmp(elem1.pszData, elem2.pszData) == 0)
		return elem1.nTNo > elem2.nTNo;

	return (bComp1 || bSame1 && (strcmp(elem1.pszData, elem2.pszData) < 0));
}

bool number_compare_greator(ArrangeIndex elem1, ArrangeIndex elem2)
{
	//BOOL bComp1 = elem1.bStateSecondSort && elem1.nState < elem2.nState;
	BOOL bComp1 = elem1.bStateSecondSort && compare_state(elem1.nState, elem2.nState, elem1.nTNo, elem2.nTNo);
	BOOL bSame1 = !elem1.bStateSecondSort || elem1.nState == elem2.nState;

	if(bSame1 && elem1.nData == elem2.nData)
		return elem1.nTNo < elem2.nTNo;

	return (bComp1 || bSame1 && (elem1.nData >= elem2.nData));
}

bool number_compare_less(ArrangeIndex elem1, ArrangeIndex elem2)
{
	BOOL bComp1 = elem1.bStateSecondSort && compare_state(elem1.nState, elem2.nState, elem1.nTNo, elem2.nTNo);
	BOOL bSame1 = !elem1.bStateSecondSort || elem1.nState == elem2.nState;

	if(bSame1 && elem1.nData == elem2.nData)
		return elem1.nTNo > elem2.nTNo;

	return (bComp1 || bSame1 && (elem1.nData <= elem2.nData));	
}

bool date_compare_greator(ArrangeIndex elem1, ArrangeIndex elem2)
{
	BOOL bComp1 = elem1.bStateSecondSort && compare_state(elem1.nState, elem2.nState, elem1.nTNo, elem2.nTNo);
	BOOL bSame1 = !elem1.bStateSecondSort || elem1.nState == elem2.nState;

	if(bSame1 && (*(elem1.pdtData) == *(elem2.pdtData)))
		return elem1.nTNo < elem2.nTNo;

	return (bComp1 || bSame1 && (*(elem1.pdtData) > *(elem2.pdtData)));
}

bool date_compare_less(ArrangeIndex elem1, ArrangeIndex elem2)
{
	BOOL bComp1 = elem1.bStateSecondSort && compare_state(elem1.nState, elem2.nState, elem1.nTNo, elem2.nTNo);
	BOOL bSame1 = !elem1.bStateSecondSort || elem1.nState == elem2.nState;
	
	if(bSame1 && (*(elem1.pdtData) == *(elem2.pdtData)))
		return elem1.nTNo > elem2.nTNo;
	
	return (bComp1 || bSame1 && (*(elem1.pdtData) < *(elem2.pdtData)));
}



CVirtualRecord::CVirtualRecord(void)
{
	m_bUseFilter = FALSE;
	m_bParentSearch = TRUE;

	for(int i = 0; i < MAX_COLUMN; i++)
	{
		CXTPGridRecordItem *pItem = new CXTPGridRecordItem();
		if(i == RIDER_NO_COL || i == RIDER_NAME_COL || i == WNO_COL || i == TRANS_COL ||  i == CONSIGN_SUM_COL)
			pItem->AddHyperlink(new CXTPGridHyperlink(0, 0xFFFF));
		AddItem(pItem);
	}
}


CVirtualRecord::~CVirtualRecord(void)
{
}

//조성일
void CVirtualRecord::GetItemMetrics (XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	CXTPGridColumnOrder* pSortOrder = pDrawArgs->pControl->GetColumns()->GetSortOrder();

	//BOOL bDecreasing = pSortOrder->GetCount() > 0 && pSortOrder->GetAt(0)->IsSortedDecreasing();

	//CString strColumn = pDrawArgs->pColumn->GetCaption();
	int nRow = pDrawArgs->pRow->GetIndex();
	int nCount = pDrawArgs->pControl->GetRows()->GetCount();
	int nCol = pDrawArgs->pColumn->GetIndex();
	int nItemCol = pDrawArgs->pColumn->GetItemIndex();
	int nTNo = m_bUseFilter ? m_Index[m_filter[m_arrange[nRow]]] : m_Index[m_arrange[nRow]];
	OrderRecordList::iterator itOrder = m_order.find(nTNo);
	int nState = itOrder->second.nState;
	int nDaeriCode = itOrder->second.nDaeriCode;
	int nCTNo = itOrder->second.nCTNo;

	//pDrawArgs->nTextAlign = header_align[nItemCol];
	pItemMetrics->nColumnAlignment = header_align[nItemCol];

	if(nItemCol == RCP_NO)
	{
		CString strTemp = ""; strTemp.Format("%d", nRow + 1);
		itOrder->second.info[pDrawArgs->pColumn->GetItemIndex()] = strTemp;
	}
	if(nItemCol == RCP_COMPANY_COL)  
	{
		long nState1 = (itOrder->second.bShareOrder && nState == 10 && itOrder->second.bClientShare5) ? 100 : nState;
		//long nState1 = (itOrder->second.bShareOrder && nState == 10) ? 100 : nState;
		long nSubState1 = (GetBranchInfo(itOrder->second.nCompany)->IsCargo() && itOrder->second.nBillDraw > 0) ? itOrder->second.nBillDraw : 0;


		if(itOrder->second.nState == STATE_ALLOCATED)
		{
			COleDateTimeSpan span = COleDateTime::GetCurrentTime() - itOrder->second.dt3;

			if(span.GetTotalSeconds() <= 30)
				nState1 = 101; 			
		}
		
		pDrawArgs->pItem->SetIconIndex(GetImageNumber(nState1, nSubState1, nCTNo));		
	}
	else if(nItemCol == RCP_CUSTOMER_COL)
	{
		if(((CMainFrame*)AfxGetMainWnd())->GetICCount() > 0)
		{
			if(((CMainFrame*)AfxGetMainWnd())->FindIC(itOrder->second.nCNo))
				pDrawArgs->pItem->SetIconIndex(17);
			else
				pDrawArgs->pItem->SetIconIndex(16);
		}
	}
	else if(nItemCol == RCP_ELAPSED_COL)
	{
		//char buffer[10]; 
		COleDateTimeSpan span = 0; 
		CString strTime = "";
		//if(itOrder->second.dtState.m_status != 2)  // DateTimeStatus.null
		//{ 
		//	if(itOrder->second.nState == STATE_OK && itOrder->second.nReserveAfter == 0)
		//		span = COleDateTime::GetCurrentTime() - itOrder->second.dt0;  // dtState; 업체에서 접수후 시간이 안맞느다하여 수정함 //dt0에서 변경 문제시 다시 dt0으로
		//	else
		//		span = COleDateTime::GetCurrentTime() - itOrder->second.dtState;
		//}

		//if(nState == STATE_OK ||
		//	nState == STATE_OK_ONLY_MAN ||
		//	nState == STATE_ALLOCATED ||
		//	nState == STATE_PICKUP)
		//{
		//	itOrder->second.info[pDrawArgs->pColumn->GetItemIndex()] = ltoa(span.GetTotalMinutes(), buffer, 10);
		//}
		//else
		//{
		//	itOrder->second.info[pDrawArgs->pColumn->GetItemIndex()] = "";
		//}

		
		if(itOrder->second.dt0.m_status != 2)
		{			
			if(nState ==  STATE_OK ||  
				nState ==  STATE_WAIT ||  
				nState == STATE_INTERNET ||
					nState == STATE_OK_ONLY_MAN ||
					nState == STATE_ALLOCATED ||
					nState == STATE_PICKUP)
			{	
				COleDateTimeSpan span = 0, spanTemp = 0; 
				if(itOrder->second.bReserved ||  itOrder->second.bStartWaitInquiryReceipt )  // DateTimeStatus.null
					span = COleDateTime::GetCurrentTime() - itOrder->second.dtRcp;
				else
				{
					//if(::IsThisCompany("엔콜") || ::IsThisCompany("올바로"))
					if (GetBranchInfo(itOrder->second.nCompany)->init_dt1_state_to_rcp)
						span = COleDateTime::GetCurrentTime() - itOrder->second.dtRcp;
					else
						span = COleDateTime::GetCurrentTime() - itOrder->second.dt0;
				}
					
				

				strTime.Format("%d", (long)span.GetTotalMinutes());								
				
				itOrder->second.info[pDrawArgs->pColumn->GetItemIndex()] = strTime;

			}			
		}
		

	}
	else if(nItemCol == ALLOC_ELAPSED_COL)
	{
		char buffer[10];
		COleDateTimeSpan span = 0;
		if(itOrder->second.dt3.m_status  != 2)  // DateTimeStatus.null
			span = COleDateTime::GetCurrentTime() - itOrder->second.dt3;
		if(nState == STATE_ALLOCATED ||
			nState == STATE_PICKUP)
		{
			itOrder->second.info[pDrawArgs->pColumn->GetItemIndex()] = ltoa(span.GetTotalMinutes(), buffer, 10);
		}
		else
		{
			itOrder->second.info[pDrawArgs->pColumn->GetItemIndex()] = "";
		}		
	}
	else if(nItemCol == START_DONG_COL || nItemCol == DEST_DONG_COL)
	{
		if(itOrder->second.nState == STATE_WAIT ||
			itOrder->second.nState == STATE_OK)
		pItemMetrics->pFont = &pDrawArgs->pControl->GetPaintManager()->m_fontBoldText;
	}
	else  if(nItemCol == RESERVE_COL)
	{ 
		CString strTemp = "";
 
		long nState = itOrder->second.nState;
		long nReserveAfter = itOrder->second.nReserveAfter;
   
		if(itOrder->second.nState == STATE_RESERVED)// || itOrder->second.nReserveAfter > 0)
		{
			COleDateTime dtCur = COleDateTime::GetCurrentTime();
			COleDateTimeSpan span = itOrder->second.dtReserve - dtCur;
			long nSpanDay = span.GetTotalDays();

			if(nSpanDay == 0)		strTemp = "오늘 " + CString(itOrder->second.dtReserve.Format("%H:%M"));
			else if(nSpanDay == 1)	strTemp = "내일 " + CString(itOrder->second.dtReserve.Format("%H:%M"));
			else if(nSpanDay < 4)	
			{ 
				strTemp.Format("%d일후 ", nSpanDay);
				strTemp += CString(itOrder->second.dtReserve.Format("%H:%M"));
			}
			else
				strTemp = itOrder->second.dtReserve.Format("%m-%d %H:%M");
		}
		else
			strTemp = "";	

		itOrder->second.info[pDrawArgs->pColumn->GetItemIndex()] = strTemp;
	} 

	if(nItemCol == START_DONG_COL)
	{
		if(itOrder->second.nState == STATE_OK && itOrder->second.bFoodOrder)
		{
			COleDateTime dtCur = COleDateTime::GetCurrentTime(); 
			COleDateTimeSpan span = itOrder->second.dtFoodComplete - dtCur;

			long nMinute = span.GetTotalMinutes() + 1;
 
			CString strItem = ::GetStringFromLong(nMinute) + "분)" + itOrder->second.strStart.c_str();
			itOrder->second.info[pDrawArgs->pColumn->GetItemIndex()] = strItem;
		}		
		else
		{
			itOrder->second.info[pDrawArgs->pColumn->GetItemIndex()] = itOrder->second.strStart;
		}
	}

	pItemMetrics->strText = itOrder->second.info[pDrawArgs->pColumn->GetItemIndex()].c_str();

	

	if((nItemCol == RCP_COMPANY_COL) &&
		(itOrder->second.bParentOrder == FALSE) &&
		(itOrder->second.nTNo != itOrder->second.nTNoSet))
	{ 
		if(m_arrangeTNoSet.find(m_arrange[nRow]) != m_arrangeTNoSet.end())
			pItemMetrics->strText = " ━ " + pItemMetrics->strText;
		else
			pItemMetrics->strText = " ┗ " + pItemMetrics->strText;
	}

	pItemMetrics->clrForeground = OnColorText(pItemMetrics, nRow, nCol, nItemCol, itOrder);

	//long nItem = pDrawArgs->pRow->GetIndex();
	//if(pDrawArgs->pRow->IsSelected()) 
	//	pItemMetrics->clrBackground = RGB(255, 0, 0);
	//else 
		pItemMetrics->clrBackground = OnColorBack(pItemMetrics, nRow, nCol, nItemCol, itOrder);
}

COLORREF CVirtualRecord::OnColorText(XTP_REPORTRECORDITEM_METRICS* pItemMetrics, int &nRow, int &nCol, int &nItemCol, 
									 OrderRecordList::iterator &itOrder)
{
	

	if(nItemCol == RCP_CUSTOMER_COL)  
	{   
		if(itOrder->second.nPayType == PAY_CREDIT)
			return RGB(255, 0, 0); 
		else if(itOrder->second.nPayType == PAY_ONLINE)   
			return RGB(0x99, 0, 0x99); 
		else if(itOrder->second.nPayType == PAY_CARD) 
			return RGB(0x33, 0x99, 0x99);
		else if(itOrder->second.nPayType == PAY_IMSI2)
			return RGB(0, 0, 255);
	}

	if(nItemCol == START_DONG_COL || nItemCol == DEST_DONG_COL)
	{
		if(itOrder->second.nState == 8 || itOrder->second.nState == 9 || itOrder->second.nState == 10)
			return m_crStateTextA;
	}

	if(nItemCol == CHARGE_COL)
	{
		if(itOrder->second.nCreditCardType == NICE_CARD_COMPLETE || itOrder->second.nCreditCardType == NICE_CARD_COMPLETE_QUICKCALL)
		{
			if(itOrder->second.nCardOkAmt > 0)
				return RGB(0, 0, 255);
		}
		//else
		//	return RGB(255, 0, 0);
	}


	if(!m_bIntegrated) {
		if(nCol < 2) {
			if(itOrder->second.nCompany != itOrder->second.nRiderCompany && 
				itOrder->second.nRiderCompany > 0 && 
				itOrder->second.nState > 10 && itOrder->second.nState < 40) {
					if(itOrder->second.nRiderCompany == m_nDOrderCompany)
						return RGB(255, 255, 255);
					else 
						return RGB(255, 255, 255);
				}
		}
	}

	if(itOrder->second.nReserveAfter > 0 &&
		nItemCol == RCP_RESERVE_COL)
	{
		return RGB(255, 0, 0);
	}

	if(itOrder->second.nConsignTNo > 0 && itOrder->second.nConsignTNo < 5500000  && nItemCol == DEST_COMPANY_COL)
		return RGB(0, 0,255);
	else if(itOrder->second.nConsignTNo > 0 && itOrder->second.nConsignTNo > 5500000  && nItemCol == DEST_COMPANY_COL)
		return RGB(255, 0,0);


	if(itOrder->second.nState == STATE_OK &&
		nCol == m_nUseCountCol)
	{
		int nLevel = itOrder->second.nUseCount * 5;
		nLevel = min(nLevel, 255);

		if(nLevel < 125)
			return RGB(0, 0, 0);
		else
			return RGB(255, 255, 255);
	}
	else if(itOrder->second.nState >= 11 && itOrder->second.nState <= 35)
	{
		if(nItemCol == RIDER_NO_COL || nItemCol == RIDER_NAME_COL)
		{
			if(itOrder->second.bCross)
			{
				return RGB(0, 255, 0);
			}
			else
			{
				return RGB(0, 0, 255);
			}
		}
	}

	if(itOrder->second.nPayType >= PAY_CREDIT &&
		nItemCol == PAY_TYPE_COL)
	{
		if(itOrder->second.nPayType == PAY_CARD &&
			itOrder->second.nCreditCardType < 100)
			return RGB(0, 0, 255); //결제안된카드

		return RGB(255, 0, 0);
	}
	
	if(nItemCol == CHARGE_REVISION_COL)
		return RGB(255, 0, 0);


	switch(itOrder->second.nState)
	{
	case STATE_OK:
		return m_crStateText1;
	case STATE_WAIT:
		return m_crStateText2;
	case STATE_RESERVED:
		return m_crStateText3;
	case STATE_OK_ONLY_MAN:
		return m_crStateText4;
	case STATE_ALLOCATED:
		return m_crStateText5;
	case STATE_PICKUP:
		return m_crStateText6;
	case STATE_FINISH:
		return m_crStateText7;
	case STATE_CANCELED:
		return m_crStateText8;
	case STATE_INQUIRY:
		return m_crStateText9;
	case STATE_INTERNET:
		return m_crStateText10;
	case STATE_RECALL:
		return RGB(255,255,255);
	case STATE_RIDER_CALL:
		return RGB(255,255,255);	
	case STATE_NOTICE:
		return RGB(255,255,255);
	default:
		return RGB(0, 0, 0);
	}

	return RGB(0, 0, 0);
}

COLORREF CVirtualRecord::OnColorBack(XTP_REPORTRECORDITEM_METRICS* pItemMetrics, int &nRow, int &nCol, int &nItemCol,
									OrderRecordList::iterator &itOrder)
{
	//if(m_pMyControl->GetXListSelectedRecord() == this)
	//	return RGB(255, 0, 0); 

	//if(m_nSelectRow == nRow)
	//	return RGB(255, 0, 0);
	
	if(!m_bIntegrated) {
		if(nCol < 2) {
			if(itOrder->second.nCompany != itOrder->second.nRiderCompany && 
				itOrder->second.nRiderCompany > 0 && 
				itOrder->second.nState > 10 && itOrder->second.nState < 40) {
					if(itOrder->second.nRiderCompany == m_nDOrderCompany)
						return RGB(100, 255, 100);
					else 
						return RGB(100, 100, 255);
				}
		}
	} 

	if((nItemCol == RCP_COMPANY_COL) &&
		(itOrder->second.bParentOrder == TRUE))
		return RGB(255, 100, 100);

	if(itOrder->second.bScheduleOrder &&
		nItemCol == RCP_CUSTOMER_COL)
	{
		return RGB(255, 255, 200);
	}

	if(nItemCol == START_DONG_COL || nItemCol == DEST_DONG_COL)
	{
		if(!(itOrder->second.nState == 8 || itOrder->second.nState == 9 || itOrder->second.nState == 10))
		{
			if(nItemCol == START_DONG_COL && 
				(itOrder->second.nSignType == 1 || itOrder->second.nSignType == 3))
			{
				return RGB(255, 255, 200);
			}
			else if(nItemCol == DEST_DONG_COL && 
				(itOrder->second.nSignType == 2 || itOrder->second.nSignType == 3))
			{
				return RGB(255, 255, 200);
			}
		}
	}
 
	if(nItemCol == START_GUGUN_COL)   
	{
		if((itOrder->second.nSCNo != 0) &&
			(CString(itOrder->second.strSAddress.c_str()).Find("번지") == -1 &&
			CString(itOrder->second.strSAddress.c_str()).Find("-") == -1) )
			return RGB(255, 200, 255);

	}

	if(nItemCol == DEST_GUGUN_COL)   
	{
		if((itOrder->second.nDCNo != 0) &&
			(CString(itOrder->second.strDAddress.c_str()).Find("번지") == -1 &&
			CString(itOrder->second.strDAddress.c_str()).Find("-") == -1) )
			return RGB(255, 200, 255);
	}

	if(nItemCol == RUN_TYPE_COL)// 긴급
	{
		if(itOrder->second.nRunType == RUN_VERY_FAST) //특급
			return RGB(254, 0, 0);
		else if(itOrder->second.nRunType == RUN_FAST) //긴급
			return RGB(239, 87, 83);
		else if(itOrder->second.nRunType == RUN_SLOW) //완급
			return RGB(255, 182, 68);
	}

	if(itOrder->second.nState == STATE_OK &&
		nItemCol == RCP_ELAPSED_COL)
	{
		COleDateTimeSpan dtSpan = COleDateTime::GetCurrentTime() - itOrder->second.dtRcp;
		int nDelayMinutes = (long)dtSpan.GetTotalMinutes();
		if(nDelayMinutes >= m_nRcpTimeColor3)
			return RGB(255, 170, 170);
		else if(nDelayMinutes >= m_nRcpTimeColor2)
			return RGB(255, 255, 170);
		else if(nDelayMinutes >= m_nRcpTimeColor1)
			return RGB(170, 255, 170);
	}

	if(itOrder->second.nState == STATE_OK &&
		nCol == m_nUseCountCol)
	{
		int nLevel = itOrder->second.nUseCount * 5;
		nLevel = min(nLevel, 255);
		return RGB(255 - nLevel, 255 - nLevel, 255);
	}

	if(
		(nItemCol == RCP_GNO_COL || nItemCol == RCP_GNO_DEPT_COL ) &&
		itOrder->second.nGNo > 0
	)
	{
		return RGB(0xFF, 0xFF, 0);
	}

	if((nItemCol == TRANS_COL) &&
		(itOrder->second.nTransOrder == 1))
	{
		return RGB(245, 215, 180);
	}

	if(nItemCol == RIDER_ALLOCATE_COL && itOrder->second.bCross == FALSE)
	{
		if(itOrder->second.bRiderOkOnlyMan == 1)
			return RGB(150, 255, 150);
		else if(itOrder->second.bOfficeOkOnlyMan == 1)
			return RGB(255, 150, 150);

	}

	if(itOrder->second.nState == STATE_ALLOCATED && m_bUsePickupNot)
	{
		COleDateTimeSpan span = COleDateTime::GetCurrentTime() - itOrder->second.dt3;

		if(span.GetTotalMinutes() >= 20)
			return m_crStateBack15;
	}

	/*
	if(nItemCol == USE_COUNT_COL)
	{
		if(itOrder->second.nUseCount > 200)
			return RGB(0xFF, 50, 50);
		else if(itOrder->second.nUseCount > 100)
			return RGB(0xFF, 100, 100);
		else if(itOrder->second.nUseCount > 50)
			return RGB(0xFF, 150, 150);
	}
	*/


	switch(itOrder->second.nState)
	{
	case STATE_INTERNET:
		return m_crStateBack10;
	case STATE_SITE:
		return RGB(230, 255, 230);
	case STATE_CARRY:
		return RGB(200, 255, 200);
	case STATE_WAIT:
		return m_crStateBack2;
	case STATE_RESERVED:
		return m_crStateBack3;
	case STATE_OK:
		{
			if(!m_bUseNewRegion)
			{
				if(itOrder->second.nStartSection == 0 &&
					nCol == m_nStartCol)
					return RGB(200, 200, 200);
				else
					return m_crStateBack1;
			}
			else
			{
				if(itOrder->second.nStartRealDongID == 0 &&
					nCol == m_nStartCol)
					return RGB(200, 200, 200);
				else
					return m_crStateBack1;
			}
		}

	case STATE_OK_ONLY_MAN:
		return m_crStateBack4;
	case STATE_ALLOCATED:
		return m_crStateBack5;
	case STATE_PICKUP:
		return m_crStateBack6;		
	case STATE_FINISH:
		return m_crStateBack7;
	case STATE_CANCELED:
		return m_crStateBack8;
	case STATE_RECALL:
		return RGB(255, 100,100);
	case STATE_RIDER_CALL:
		return RGB(100,100, 255);
	case STATE_INQUIRY:
		return m_crStateBack9;
	case STATE_NOTICE:
		return RGB(100,100,100);
	default:
		return CLR_DEFAULT;
	}

	return RGB(255,255,255);
}


void CVirtualRecord::SortRecord(int nCol, SORT_TYPE type, BOOL bAsc, BOOL bStateSecondSort)
{
	vector<ArrangeIndex> v;
	OrderIndex::iterator it;
	m_arrange.clear();
	m_arrangeTNoSet.clear();
	
	typedef map<long, TREE_ORDER_TYPE> ParentTNo; //자기 m_Index, ParentTNo
	ParentTNo ParentMap;
	long nItem = 0; 

	//m_bParentSearch = FALSE;
 
	if(m_bUseFilter)
	{
		for(it = m_filter.begin(); it != m_filter.end(); it++)
		{
			OrderRecordList::iterator itOrder = m_order.find(m_Index[(*it).second]);

			ArrangeIndex idx;
			idx.nIndex = (*it).first;
			idx.nTNo = itOrder->second.nTNo;

			if(m_bParentSearch)
			{
				if(itOrder->second.nTNoSet != itOrder->second.nTNo)
				{
					TREE_ORDER_TYPE st;
					st.nIndex = idx.nIndex;
					st.nTNoSet = itOrder->second.nTNoSet;
					ParentMap.insert(ParentTNo::value_type(itOrder->second.nTNo, st));
					continue;
				}
			}
			
			if(nCol == RCP_TNO_COL)
			{
				idx.nData = itOrder->second.nTNo;
			}
			else if(nCol == RCP_STATE_COL)
			{
				idx.nData = itOrder->second.nState;
			}
			else if(nCol == RCP_TIME_COL || nCol == RCP_TIME_COL+1)
			{
				idx.pdtData = &itOrder->second.dtSort;
				//idx.pdtData = &itOrder->second.dtRcp;
			}
			else if(nCol == RESERVE_COL)
			{
				idx.pdtData = &itOrder->second.dtReserve;
			}
			else if(nCol == RCP_DISTANCE_COL)
			{
				idx.nData = itOrder->second.nDistanceKM;
			}
			else if(nCol == RCP_ELAPSED_COL)
			{
				idx.nData = atol((char*)itOrder->second.info[nCol].c_str());

					/*if(itOrder->second.nState == STATE_OK ||
						itOrder->second.nState == STATE_OK_ONLY_MAN ||
						itOrder->second.nState == STATE_ALLOCATED ||
						itOrder->second.nState == STATE_PICKUP)
					{
						idx.nData = atol((char*)itOrder->second.info[nCol].c_str());
					}
					else
						idx.nData = 0;*/
			}
			else if(nCol == RCP_DT0)
			{
				idx.pdtData = &itOrder->second.dt0;				
			}
			else
			{
				switch(header_sort_type[nCol])
				{
					case STRING_SORT:
						idx.pszData = (char*)itOrder->second.info[nCol].c_str();
						break;

					case NUMBER_SORT:
						idx.nData = atol((char*)itOrder->second.info[nCol].c_str());
						break;
				}

			}

			idx.nState = itOrder->second.nState;
			idx.bStateSecondSort = bStateSecondSort;
			v.push_back(idx);
		}
	}
	else
	{
		for(it = m_Index.begin(); it != m_Index.end(); it++)
		{
			OrderRecordList::iterator itOrder = m_order.find((*it).second);

			ArrangeIndex idx;
			idx.nIndex = (*it).first;
			idx.nTNo = itOrder->second.nTNo;

			if(m_bParentSearch)
			{
				if(itOrder->second.nTNoSet != itOrder->second.nTNo)
				{
					TREE_ORDER_TYPE st;
					st.nIndex = idx.nIndex;
					st.nTNoSet = itOrder->second.nTNoSet;
					ParentMap.insert(ParentTNo::value_type(itOrder->second.nTNo, st));
					continue;
				}
			}
				
			if(nCol == RCP_TNO_COL)
			{
				idx.nData = itOrder->second.nTNo;
			}
			else if(nCol == RCP_STATE_COL)
			{
				idx.nData = itOrder->second.nState;
			}
			else if(nCol == RCP_TIME_COL || nCol == RCP_TIME_COL+1)
			{
				idx.pdtData = &itOrder->second.dtSort;				
				//idx.pdtData = &itOrder->second.dtRcp;
			}
			else if(nCol == RESERVE_COL)
			{
				idx.pdtData = &itOrder->second.dtReserve;
			}
			else if(nCol == RCP_DISTANCE_COL)
			{
				idx.nData = itOrder->second.nDistanceKM;
			}
			else if(nCol == RCP_ELAPSED_COL)
			{
				idx.nData = atol((char*)itOrder->second.info[nCol].c_str());


				/*if(itOrder->second.nState == STATE_OK ||
					itOrder->second.nState == STATE_OK_ONLY_MAN ||
					itOrder->second.nState == STATE_ALLOCATED ||
					itOrder->second.nState == STATE_PICKUP)
				{
					idx.nData = atol((char*)itOrder->second.info[nCol].c_str());
				}
				else
					idx.nData = 0;*/
			}
			else if(nCol == RCP_DT0)
			{
				idx.pdtData = &itOrder->second.dt0;				
			}
			else
			{
				switch(header_sort_type[nCol])
				{
				case STRING_SORT:
					idx.pszData = (char*)itOrder->second.info[nCol].c_str();
					break;

				case NUMBER_SORT:
					{
						CString strTemp = (char*)itOrder->second.info[nCol].c_str();
						strTemp.Replace(",","");
						idx.nData = atol(strTemp);
						//idx.nData = atol((char*)itOrder->second.info[nCol].c_str());
					}
					break;
				}

			}

			idx.nState = itOrder->second.nState;
			idx.bStateSecondSort = bStateSecondSort;
			v.push_back(idx);
		}
	}

	switch(header_sort_type[nCol])
	{
		case STRING_SORT:
			{
				if(bAsc)
				{
					std::sort(v.begin(), v.end(), string_compare_less);
				}
				else
					std::sort(v.begin(), v.end(), string_compare_greator);
			}
			break;
	
		case NUMBER_SORT:
			{
				if(bAsc)
					std::sort(v.begin(), v.end(), number_compare_less);
				else
					std::sort(v.begin(), v.end(), number_compare_greator);
			}
			break;

		case DATE_SORT:
			{
				if(bAsc)
					std::sort(v.begin(), v.end(), date_compare_less);
				else
					std::sort(v.begin(), v.end(), date_compare_greator);
			}
			break;
	}

	vector<ArrangeIndex>::iterator itv;

	/*
	if(v.size() == 0)
	{
		if(ParentMap.size() > 0)
		{
			ParentTNo::iterator it = ParentMap.begin();

			while(it != ParentMap.end())
			{		
				m_arrange.insert(OrderIndex::value_type((long)m_arrange.size(), it->second.nIndex));			
				it++;
			} //end while(it != ParentMap.end())
		}// end if(ParentMap.size() > 0)
	}
	*/

	for(itv = v.begin(); itv != v.end(); itv++) 
	{	
		m_arrange.insert(OrderIndex::value_type((long)m_arrange.size(), (*itv).nIndex));

		long nTNoSet = (*itv).nTNo;

		OrderRecordList::iterator itOrder = m_order.find(nTNoSet);
		BOOL bFind = FALSE;

		if(ParentMap.size() > 0)
		{
			ParentTNo::iterator it = ParentMap.begin();
			
			while(it != ParentMap.end())
			{
				OrderRecordList::iterator itOrderChild = m_order.find(it->first);
				itOrderChild->second.bParentOrder = FALSE;

				if(nTNoSet == it->second.nTNoSet)
				{				
					m_arrange.insert(OrderIndex::value_type((long)m_arrange.size(), it->second.nIndex));
					ParentTNo::iterator itPre = it;
					it++;
					ParentMap.erase(itPre);

					bFind = TRUE;
				}
				else
					it++;
			} //end while(it != ParentMap.end())
		}// end if(ParentMap.size() > 0)

		itOrder->second.bParentOrder = bFind;
	}

	if(ParentMap.size() > 0)
	{
		for(ParentTNo::iterator it = ParentMap.begin(); it != ParentMap.end(); it++)
		{			
			m_arrange.insert(OrderIndex::value_type((long)m_arrange.size(), it->second.nIndex));
			m_arrangeTNoSet.insert(OrderIndex::value_type(it->second.nIndex, 0));
		}
	}
}

int CVirtualRecord::GetItemRowFromTNo(long nTNo)
{
	OrderIndex::iterator it;

	for(it = m_arrange.begin(); it != m_arrange.end(); it++)
	{
		if(nTNo == GetOrderRecord((*it).first)->nTNo)
			return (*it).first;
	}

	return 0;
}

void CVirtualRecord::MakeReserveOrderSortNumber()
{
	vector<ArrangeIndex> v;
	OrderIndex::iterator it;

	for(it = m_Index.begin(); it != m_Index.end(); it++)
	{
		if(m_order[(*it).second].nState == STATE_RESERVED)
		{
			ArrangeIndex idx;
			idx.nIndex = (*it).first;
			idx.pdtData = &m_order[(*it).second].dtRcp;
			idx.bStateSecondSort = FALSE;
			v.push_back(idx);
		}
	}

	std::sort(v.begin(), v.end(), date_compare_less);

	long nCount = 1;
	vector<ArrangeIndex>::iterator itv;
	for(itv = v.begin(); itv != v.end(); itv++)
	{	
		m_order[m_Index[(*itv).nIndex]].nReserveSortNumber = nCount++;
	}
}


