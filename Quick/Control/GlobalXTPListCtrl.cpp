
#include "stdafx.h"
#include "Quick.h"
#include "GlobalXTPListCtrl.h"

void CMyXTPListCtrl_1::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	switch(nCol)
	{
	case 0:
	case 1:
		pItemMetrics->clrForeground = RGB(0, 0, 255);
		break;

	case 4:
		pItemMetrics->clrForeground = RGB(0, 0, 0);
		pItemMetrics->clrBackground = RGB(200, 255, 200);
		break;

	case 5:
	case 6:
	case 7:
		pItemMetrics->clrForeground = RGB(0, 0, 0);
		pItemMetrics->clrBackground = RGB(255, 255, 230);
		break;

	case 8:
	case 9:
		pItemMetrics->clrForeground = RGB(0, 0, 0);
		pItemMetrics->clrBackground = RGB(255, 255, 200);
		break;
	case 10:
		if(GetItemLong(nRow) >= 0)
		{
			pItemMetrics->clrForeground = RGB(0, 0, 0);
			pItemMetrics->clrBackground = RGB(255, 255, 200);
		}
		else
		{
			pItemMetrics->clrForeground = RGB(255, 255, 255);
			pItemMetrics->clrBackground = RGB(255, 200, 200);
		}
		break;

	case 11: 
		if(GetItemText(nRow, nCol) != "")
		{
			pItemMetrics->clrForeground = RGB(255, 255, 255);
			pItemMetrics->clrBackground = RGB(255, 150, 150);
		}
		break;

	case 12:
		pItemMetrics->clrForeground = RGB(255, 0, 0);
		break;
	case 17:					
		pItemMetrics->clrForeground = RGB(0, 0, 255);
		break;

	default:
		pItemMetrics->clrForeground = RGB(0, 0, 0);
		pItemMetrics->clrBackground = RGB(255, 255, 255);
		break;
	}

	if(nCol <= 1 || nCol == 4)
		pItemMetrics->pFont = m_FontManager.GetFont("돋움", 12, FW_BOLD);
}

void CXTPListCtrl3::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nRow = pDrawArgs->pRow->GetIndex();
	int nCol = pDrawArgs->pColumn->GetIndex();

	CXTPGridColumn *pColumn = NULL;

	CString sItem = ((CXTPGridRecordItemText*)GetRecords()->GetAt(nRow)->GetItem(4))->GetCaption(pColumn);

	if(sItem == "없음")
		pItemMetrics->clrBackground = RGB(245,245,245);
	else if(sItem == "시간")
		pItemMetrics->clrBackground = RGB(245,245,200);
	else
		pItemMetrics->clrBackground = RGB(245,200,245);
}

void CXTPListCtrl4::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nRow = pDrawArgs->pRow->GetIndex();
	int nCol = pDrawArgs->pColumn->GetIndex();

	CXTPGridColumn *pColumn = NULL;

	CString sWeek = ((CXTPGridRecordItemText*)GetRecords()->GetAt(nRow)->GetItem(0))->GetCaption(pColumn);
	COleDateTime dtTime(_ttoi(sWeek.Left(4)), _ttoi(sWeek.Mid(5,2)), _ttoi(sWeek.Right(2)), 0, 0, 0);

	if(dtTime.GetDayOfWeek() == 7)
		pItemMetrics->clrForeground = RGB(0, 0, 255);
	else if(dtTime.GetDayOfWeek() == 1)
		pItemMetrics->clrForeground = RGB(255, 0, 0);

	CString sAbsence = ((CXTPGridRecordItemText*)GetRecords()->GetAt(nRow)->GetItem(2))->GetCaption(pColumn);

	if(sAbsence == "결 근")
		pItemMetrics->clrBackground = RGB(205, 205, 255);
	else
		pItemMetrics->clrBackground = RGB(205, 255, 205);
}

void CXTPListCtrl5::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	long nState = GetItemLong(nRow);

	switch(nState)
	{
	case 100: // "잔액수정" 주황색;
		pItemMetrics->clrBackground = RGB(250, 114, 123); 
		break;
	case 125: // "신규고객마일" 주황색;
		pItemMetrics->clrBackground = RGB(250, 114, 123); 
		break;
	case 101: //"초기화"   녹색;
		pItemMetrics->clrBackground = RGB(118, 250, 115);
		break;
	case 102: //"콜수정" ;
		pItemMetrics->clrBackground = RGB(100, 255, 80);
		break;
	case 103: //"개별마일" 보라색 ;
		pItemMetrics->clrBackground = RGB(252, 152, 244);
		break;
	case 104://  "회사마일" 남색;
		pItemMetrics->clrBackground = RGB(135, 60, 212);
		break;
	case 106: //"마일사용"  연두색;
		pItemMetrics->clrBackground = RGB(172, 251, 3);
		break;
	case 109: //"관리자 마일지급"  노란연두색;
		pItemMetrics->clrBackground = RGB(216, 252, 48);
		break;
	case 110: //"마일리지 사용안함"  회색;
		pItemMetrics->clrBackground = RGB(219, 220, 215);
		break;
	default:
		pItemMetrics->clrBackground = RGB(255, 255, 255);
		break;
	}
}					

void CXTPListCtrl6::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics) 
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	CString strCallType = pItemMetrics->strText;

	if(nCol == 13) //글자
	{
		if(strCallType == "선입금")
			pItemMetrics->clrForeground = RGB(0, 0, 255);
		else
			pItemMetrics->clrForeground = RGB(255, 0, 0);
	}
}

void CXTPListCtrl7::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics) 
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	long nItem = GetItemLong(nRow);

	pItemMetrics->pFont = &pDrawArgs->pControl->GetPaintManager()->m_fontBoldText;

	if(nItem < GIVEROW)
		pItemMetrics->clrBackground = RGB(200, 255, 200); //
	else
		pItemMetrics->clrBackground = RGB(200, 200, 255);

	if(nItem == TAKETOTALROW)
	{
		pItemMetrics->clrForeground = RGB(255, 0, 0);
//		pItemMetrics->pFont = m_fontSmall;
	}
	else if(nItem == TAKEALLTOTALROW)
	{
		pItemMetrics->clrForeground = RGB(0, 0, 255);
//		pItemMetrics->pFont = m_fontBig;
	}
	else if(nItem == GIVETOTALROW)
	{
		pItemMetrics->clrForeground = RGB(255, 0, 0);
//		pItemMetrics->pFont = m_fontSmall;
	}
	else if(nItem == GIVEALLTOTALROW)
	{
		pItemMetrics->clrForeground = RGB(0, 255, 0);
//		pItemMetrics->pFont = m_fontBig;
	}
}

void CXTPListCtrl8::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	long nData = GetItemLong2(nRow);

	if(nData > 0)     
	{
		pItemMetrics->clrBackground = RGB(210, 210, 230);
	}

	if(nCol == 9)
	{
		if(pItemMetrics->strText == "미정산")
			pItemMetrics->clrForeground = RGB(255, 0, 0);
		else if(pItemMetrics->strText == "정산완료")
			pItemMetrics->clrForeground = RGB(0, 255, 0);
		else if(pItemMetrics->strText == "입금완료")
			pItemMetrics->clrForeground = RGB(0, 0, 255);
		else 
			pItemMetrics->clrForeground = RGB(0, 0, 0);
	}

	if(nCol == 4)
	{
		if(pItemMetrics->strText == "주납")
			pItemMetrics->clrBackground = RGB(190, 255, 220);
		else
			pItemMetrics->clrBackground = RGB(220, 255, 190);
	}

	if(nCol == 10)
	{
		if(pItemMetrics->strText.Find("경과") >= 0)
			pItemMetrics->clrBackground = RGB(255, 200, 200);
		else if(pItemMetrics->strText.Find("남음") >= 0)
			pItemMetrics->clrBackground = RGB(200, 200, 255);
	}

	if((m_nRow == nRow) && (m_nCol == nCol))
	{
		pItemMetrics->clrBackground = RGB(0, 0, 255);
	}
}

void CXTPListCtrl9::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	ST_HISTORY_ITEM_INFO3 *pItem = (ST_HISTORY_ITEM_INFO3*)GetItemData(nRow);

	if(pItem->dt1 > m_ei.dtTodayBound)
	{
		pItemMetrics->clrForeground = RGB(0,0,0);
		pItemMetrics->clrBackground = RGB(180,255,180);
	}

	if(nCol == 6 || nCol == 7)
	{
		pItemMetrics->clrForeground= RGB(0, 0, 255);
	}

	if(nCol <= 3)
	{
		if(pItem->nState == 40)
			pItemMetrics->clrForeground = RGB(150, 0, 0);
		else if(pItem->nState == 35)
			pItemMetrics->clrForeground = RGB(0, 150, 0);
	}
}

void CXTPListCtrl10::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics) 
{
	if((pDrawArgs->pColumn->GetIndex() == 1) ||
		(pDrawArgs->pColumn->GetIndex() == 2) ||
		(pDrawArgs->pColumn->GetIndex() == 3) ||
		(pDrawArgs->pColumn->GetIndex() == 4) ||
		(pDrawArgs->pColumn->GetIndex() == 5) ||
		(pDrawArgs->pColumn->GetIndex() == 6) ||
		(pDrawArgs->pColumn->GetIndex() == 8) )
	{
		if(pItemMetrics->strText.Find(m_strSearchData) >=0 && m_strSearchData != "")
			pItemMetrics->clrForeground = RGB(0, 0, 255);		
		else
			pItemMetrics->clrForeground = RGB(0, 0, 0);	
	}

	long nRow = pDrawArgs->pRow->GetIndex();
	long nCol = pDrawArgs->pColumn->GetItemIndex();
	ST_CUSTOMER_INFO *pCustomer = (ST_CUSTOMER_INFO*)GetItemData(nRow);

	if(GetItemText(nRow, 0) != "지명" && pCustomer->bMain == TRUE)
	{
		if (!m_fontBold.GetSafeHandle())
		{
			LOGFONT lf;
			pDrawArgs->pControl->GetPaintManager()->m_fontText.GetLogFont(&lf);
			lf.lfWeight = FW_BOLD;

			m_fontBold.CreateFontIndirect(&lf);
		}

		if(pCustomer->bGroupOwner)
			pItemMetrics->clrForeground = RGB(0, 200, 0);

		pItemMetrics->pFont = &m_fontBold;
	}


	if(GetItemText(nRow, 0) == "지명")
		pItemMetrics->clrBackground = RGB(200, 255, 200);
	else
	{
		if(pCustomer->nDongID == NULL) 
			pItemMetrics->clrBackground = pCustomer->bGorupSelect ? RGB(218, 225, 166) :  RGB(248, 255, 166);
		else
			pItemMetrics->clrBackground = pCustomer->bGorupSelect ? RGB(230, 230, 230) : RGB(255, 255, 255);
	}

	if((pCustomer->nCNo == LINE_ROW) || (pCustomer->nCNo == GROUP_NAME_ROW))
	{
		if(pCustomer->nCNo == LINE_ROW)
			pItemMetrics->clrForeground = pCustomer->bGorupSelect ? RGB(225, 96, 178) : RGB(255, 126, 208);
		else if(pCustomer->nCNo == GROUP_NAME_ROW)
			pItemMetrics->clrForeground = pCustomer->bGorupSelect ? RGB(66, 148, 225) : RGB(96, 178, 255);

		if(nCol == 0) 
			pItemMetrics->strText = "";
	}
}

void CXTPListCtrl11::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	if(nCol == 7)
	{
		if(pItemMetrics->strText == "미정산")
			pItemMetrics->clrForeground = RGB(255, 0, 0);
		else if(pItemMetrics->strText == "정산완료")
			pItemMetrics->clrForeground = RGB(0, 255, 0);
		else if(pItemMetrics->strText == "입금완료")
			pItemMetrics->clrForeground = RGB(0, 0, 255);
		else 
			pItemMetrics->clrForeground = RGB(0, 0, 0);
	}

	if(nCol == 2)
	{
		if(pItemMetrics->strText == "주납")
			pItemMetrics->clrBackground = RGB(190, 255, 220);
		else
			pItemMetrics->clrBackground = RGB(220, 255, 190);
	}
}

void CXTPListCtrl13::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	if(GetItemLong(nRow) == 1)
	{
		pItemMetrics->clrBackground = RGB(220, 230, 220);
		pItemMetrics->clrForeground = RGB(0, 0, 255);
	}
}

void CXTPListCtrl15::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	long nRow = pDrawArgs->pRow->GetIndex();
	long nColumn = pDrawArgs->pColumn->GetIndex();

	if(nColumn == 1)
	{
		if(GetItemText(nRow, nColumn) == "미정산")
			pItemMetrics->clrForeground = RGB(255, 0, 0);
		else if(GetItemText(nRow, nColumn)  == "정산완료")
			pItemMetrics->clrForeground = RGB(0, 255, 0);
		else if(GetItemText(nRow, nColumn)  == "입금완료")
			pItemMetrics->clrForeground = RGB(0, 0, 255);
	}
}

void CXTPListCtrl16::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	long nRow = pDrawArgs->pRow->GetIndex();
	long nColumn = pDrawArgs->pColumn->GetIndex();

	if(nColumn == 2)
	{
		pItemMetrics->clrForeground = RGB(0, 255, 0);
	}

	if(nColumn == 3)
	{
		pItemMetrics->clrForeground = RGB(0, 0, 255);
	}
}

void CXTPListCtrl17::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	if(nCol == 7)
	{
		if(pItemMetrics->strText == "미정산")
			pItemMetrics->clrForeground = RGB(255, 0, 0);
		else if(pItemMetrics->strText == "정산완료")
			pItemMetrics->clrForeground = RGB(0, 255, 0);
		else if(pItemMetrics->strText == "입금완료")
			pItemMetrics->clrForeground = RGB(0, 0, 255);
		else 
			pItemMetrics->clrForeground = RGB(0, 0, 0);
	}

	if(nCol == 2)
	{
		if(pItemMetrics->strText == "주납")
			pItemMetrics->clrBackground = RGB(190, 255, 220);
		else
			pItemMetrics->clrBackground = RGB(220, 255, 190);
	}
}

void CMyXTPListCtrl_IF3::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	int nState = GetItemData(nRow);

	if((nState >= 40 && nState <= 63) || nState == 61 || nState == 70 || nState == 71
		|| nState == 200 || nState == 201)  
	{
		pItemMetrics->clrBackground = RGB(235, 235, 255);
		pItemMetrics->clrForeground = RGB(0,0,0);
	}
	else 
	{
		pItemMetrics->clrBackground = RGB(255, 235, 235);
		pItemMetrics->clrForeground = RGB(0,0,0);
	}

	if(nCol == 3 || nCol == 7)
	{
		if(pItemMetrics->strText == "-")
			pDrawArgs->nTextAlign = DT_CENTER;
	}

	if(nCol == 10 || nCol == 11)
		pItemMetrics->clrForeground = RGB(0, 0, 255);

}

void CXTPListCtrl18::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{ 
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	if((long)GetItemData(nRow) == 2)
	{
		pItemMetrics->clrBackground = RGB(255,200,200);
		pItemMetrics->clrForeground = RGB(0,0,0);
	}
	else if((long)GetItemData(nRow) == 3)
	{
		pItemMetrics->clrBackground = RGB(100,100,100);
		pItemMetrics->clrForeground = RGB(255,255,255);
	}

	if(LF->GetCurBranchInfo()->bIntegrated)
	{
		if((pDrawArgs->pColumn->GetIndex() == 1) ||
			(pDrawArgs->pColumn->GetIndex() == 3) ||
			(pDrawArgs->pColumn->GetIndex() == 4)  )
		{
			if(pItemMetrics->strText.Find(m_strSearchData) >=0 && m_strSearchData != "")
				pItemMetrics->clrForeground = RGB(0, 0, 255);		
			else
				pItemMetrics->clrForeground = RGB(0, 0, 0);	
		}
	}
	else
	{
		if((pDrawArgs->pColumn->GetIndex() == 1) ||
			(pDrawArgs->pColumn->GetIndex() == 2) ||
			(pDrawArgs->pColumn->GetIndex() == 3)  )
		{
			if(pItemMetrics->strText.Find(m_strSearchData) >=0 && m_strSearchData != "")
				pItemMetrics->clrForeground = RGB(0, 0, 255);		
			else
				pItemMetrics->clrForeground = RGB(0, 0, 0);	
		}
	}
}

void CXTPListCtrl19::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS *pDrawArgs, XTP_REPORTRECORDITEM_METRICS *pItemMetrics)
{
	int nRow = pDrawArgs->pRow->GetIndex();
	int nCol = pDrawArgs->pColumn->GetIndex();
	int nItemCol = pDrawArgs->pColumn->GetItemIndex();

	if(GetItemLong(nRow) == 1)
		pItemMetrics->clrForeground = RGB(0, 0, 255);
}

void CXTPListCtrl20::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	long nReportState = GetItemLong(pDrawArgs->pRow->GetIndex());

	if(nReportState == 0)
		pItemMetrics->clrForeground = RGB(0, 0, 255);
	else
		pItemMetrics->clrForeground = RGB(255, 0, 0);
}

void CXTPListCtrl21::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{		
	int nCol = pDrawArgs->pColumn->GetIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	int nReportState = GetItemData(nRow);

	if(nReportState == 10 || nReportState == 20)
		pItemMetrics->clrForeground= RGB(255, 0, 0);
	else
		pItemMetrics->clrForeground= RGB(0, 0, 255);
}

void CXTPListCtrl22::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	long nItem = GetItemLong(pDrawArgs->pRow->GetIndex());

	if(nItem == 0)
	{
		pItemMetrics->clrBackground = RGB(255, 235, 235);
		pItemMetrics->clrForeground = RGB(0,0,0);
	}
	else
	{
		pItemMetrics->clrBackground = RGB(235, 235, 255);
		pItemMetrics->clrForeground = RGB(0,0,0);
	}
}

void CXTPListCtrl23::GetItemMetrics (XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nRow = pDrawArgs->pRow->GetIndex();
	int nCol = pDrawArgs->pColumn->GetIndex();

	CString str = pItemMetrics->strText;

	if(str.Left(1) == "l" || str.Left(1) == "r" || str.Left(1) == "c")
	{
		str = str.Mid(1, str.GetLength() - 1);
	}

	if(str.Right(1) == "r" || str.Right(1) == "g" || str.Right(1) == "b")
	{
		if(str.Right(1) == "r")
			pItemMetrics->clrForeground = RGB(255, 0, 0);
		if(str.Right(1) == "g")
			pItemMetrics->clrForeground = RGB(0, 255, 0);
		if(str.Right(1) == "b")
			pItemMetrics->clrForeground = RGB(0, 0, 255);

		str = str.Left(str.GetLength() -1);
	}

	pItemMetrics->strText = str;
}

void CXTPListCtrl24::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	long nRow = pDrawArgs->pRow->GetIndex();
	long nCol = pDrawArgs->pColumn->GetIndex();

	long nPayType = (long)GetItemData(nRow);

	if(nPayType == 2 || nPayType == 3)
	{
		if(nCol == 4 || nCol == 10)
			pItemMetrics->clrForeground = RGB(255, 0, 0);
	}
}

void CXTPListCtrl25::GetItemMetrics (XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nItemCol = pDrawArgs->pColumn->GetItemIndex();

	CXTPGridColumn *pColumn = GetColumns()->GetAt(nItemCol);
	CString sColumn = pColumn->GetCaption();

	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	dtCur.SetDate(dtCur.GetYear(), atoi(sColumn.Left(2)), atoi(sColumn.Right(2)));

	if(dtCur.GetDayOfWeek() == 1) //일요일
	{
		pItemMetrics->clrBackground = RGB(255, 70, 70);
	}
	else if(dtCur.GetDayOfWeek() == 7) //토요일
	{
		pItemMetrics->clrBackground = RGB(70, 70, 255);
	}
}

void CXTPListCtrl26::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{		
	int nCol = pDrawArgs->pColumn->GetIndex();
	int nRow = pDrawArgs->pRow->GetRecord()->GetIndex();

	ST_DEPOSIT *pDeposit = (ST_DEPOSIT*)GetItemData(pDrawArgs->pRow->GetRecord()); 

	if((nCol >= 10) && (nCol <= 13))
		pItemMetrics->clrForeground= RGB(0, 0, 255);

	if(nCol == 4)
	{
		if(pDeposit->nState == 0)
			pItemMetrics->clrForeground = RGB(255, 0, 0);
		else if(pDeposit->nState == 1)
			pItemMetrics->clrForeground = RGB(0, 255, 0);
		else if(pDeposit->nState == 2) 
			pItemMetrics->clrForeground = RGB(0, 0, 255);
		else
			pItemMetrics->clrForeground = RGB(0, 0, 0);
	}

	if((m_nRow == nRow) && (m_nCol == nCol))
	{
		pItemMetrics->clrBackground = RGB(180, 170, 255);
	}
}

void CXTPListCtrl27::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	long nColor = GetItemLong(nRow);

	if((nColor == 9999) || (GetColumns()->GetCount() -1 == nCol))
	{
		pItemMetrics->clrBackground = RGB(245, 180, 180);
	}
	else
	{
		if(nColor % 2 == 0)
			pItemMetrics->clrBackground = RGB(180, 245, 180);
		else
			pItemMetrics->clrBackground = RGB(180, 180, 245);
	}
}

void CXTPListCtrl28::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics) 
{
	int nCol = pDrawArgs->pColumn->GetItemIndex(); 
	int nRow = pDrawArgs->pRow->GetIndex(); 
	CString sText = pItemMetrics->strText;		 	

	if((sText == "○") && (nCol == 11))
		pItemMetrics->clrForeground = RGB(0, 0, 255);
	else if(nCol == 12 && sText.GetLength() > 0)
		pItemMetrics->clrForeground = RGB(255, 0, 0);
	else if((nCol == 9 || nCol == 10) && (sText.Find("송금") >= 0 || sText.Find("신용") >= 0))
		pItemMetrics->clrForeground = RGB(255, 0, 0);
}

void CXTPListCtrl29::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics) 
{
	int nCol = pDrawArgs->pColumn->GetItemIndex(); 
	int nRow = pDrawArgs->pRow->GetIndex(); 
	long bRiderAllocate = GetItemLong(nRow); 

	if(bRiderAllocate)
		pItemMetrics->clrBackground = RGB(180, 150, 255);
}

void CXTPListCtrl30::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	long nState = GetItemLong(pDrawArgs->pRow->GetRecord());

	switch(nState)
	{
	case STATE_INTERNET: 
		pItemMetrics->clrBackground = RGB(255, 230, 230);
		break;
	case STATE_SITE:
		pItemMetrics->clrBackground = RGB(230, 255, 230);
		break;
	case STATE_CARRY:
		pItemMetrics->clrBackground = RGB(200, 255, 200);
		break;
	case STATE_WAIT:
		pItemMetrics->clrBackground = RGB(255, 255, 200);
		break;
	case STATE_RESERVED:
		pItemMetrics->clrBackground = RGB(255, 255, 150);
		break;
	case STATE_OK:
		pItemMetrics->clrBackground = RGB(200, 200, 200);
		break;
	case STATE_OK_ONLY_MAN:
		pItemMetrics->clrBackground = RGB(230, 255, 230);
		break;
	case STATE_ALLOCATED:
		pItemMetrics->clrBackground = RGB(255, 255, 255);
		break;
	case STATE_PICKUP:
		pItemMetrics->clrBackground = RGB(100, 100, 255);		
		break;
	case STATE_FINISH:
		pItemMetrics->clrBackground = RGB(255, 255, 255);
		break;
	case STATE_CANCELED:
		pItemMetrics->clrBackground = RGB(230, 230, 255);
		break;
	case STATE_RECALL:
		pItemMetrics->clrBackground = RGB(255, 100,100);
		break;
	case STATE_RIDER_CALL:
		pItemMetrics->clrBackground = RGB(100,100, 255);
		break;
	case STATE_INQUIRY:
		pItemMetrics->clrBackground = RGB(200, 200, 255);
		break;
	case STATE_NOTICE:
		pItemMetrics->clrBackground = RGB(100,100,100);
		break;
	default:
		pItemMetrics->clrBackground = CLR_DEFAULT;
		break;
	}
}

void CXTPListCtrl31::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	long nWorkState = GetItemLong2(pDrawArgs->pRow->GetRecord());

	if(nWorkState == 1)
		pItemMetrics->clrBackground = RGB(255, 220, 220);
}

void CXTPListCtrl32::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	long nRow = pDrawArgs->pRow->GetIndex();
	long nCol = pDrawArgs->pColumn->GetIndex();

	long nWorkState = GetItemLong2(pDrawArgs->pRow->GetRecord());

	if(nCol == 2 && pItemMetrics->strText == "사용안함")
		pItemMetrics->clrBackground = RGB(255, 220, 220);
}

void CXTPListCtrl34::GetItemMetrics (XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	if(GetItemLong(pDrawArgs->pRow->GetRecord()))
		pItemMetrics->clrBackground = RGB(242, 242, 255);
	else 
		pItemMetrics->clrBackground = RGB(255, 242, 242);

	int nCol = pDrawArgs->pColumn->GetItemIndex(); 

	if(nCol == 6 || nCol == 8)
		pItemMetrics->clrForeground = RGB(0, 0, 255);

	pItemMetrics->pFont = m_FontManager.GetFont("맑은 고딕", 18, FW_NORMAL);
}
 
void CXTPListCtrl35::GetItemMetrics (XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	long nType = GetItemLong(pDrawArgs->pRow->GetRecord());
	if(nType == 10)
		pItemMetrics->clrBackground = RGB(222, 222, 255);
	else if(nType == 20)
		pItemMetrics->clrBackground = RGB(255, 222, 222);
}

void CXTPListCtrl36::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	int nState = GetItemData(nRow);
	if(nState >= 40) {
		pItemMetrics->clrBackground = RGB(235, 235, 255);
		pItemMetrics->clrForeground = RGB(0,0,0);
	}
	else if(nState <= 30) {
		pItemMetrics->clrBackground = RGB(255, 235, 235);
		pItemMetrics->clrForeground = RGB(0,0,0);
	}
}

void CXTPListCtrl37::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	long nType = GetItemLong(pDrawArgs->pRow->GetRecord());
	long nResult = GetItemLong2(pDrawArgs->pRow->GetRecord());

	if(nCol == 6) {
		if(nType == 0)
			pItemMetrics->clrForeground = RGB(255, 0, 0);
		else
			pItemMetrics->clrForeground = RGB(0, 0, 255);
	}

	if(nResult == 0) 
		pItemMetrics->clrBackground = RGB(100, 255, 100);
	else
	{
		if(nCol == 7)
		{
			if(nResult == 1)
				pItemMetrics->clrForeground = RGB(255, 0, 0);
			else if(nResult == 2 || nResult == 3)
				pItemMetrics->clrForeground = RGB(0, 0, 255);
		}
	}
}

void CXTPListCtrl38::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	if(GetItemLong2(nRow))
	{
		pItemMetrics->clrBackground = RGB(220, 230, 220);
		pItemMetrics->clrForeground = RGB(0, 0, 255);
	}
}

void CXTPListCtrl39::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	pItemMetrics->pFont = &pDrawArgs->pControl->GetPaintManager()->m_fontBoldText;
}

void CXTPListCtrl40::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics) 
{
	int nCol = pDrawArgs->pColumn->GetItemIndex(); 
	int nRow = pDrawArgs->pRow->GetIndex(); 
	long bRiderAllocate = GetItemLong(nRow); 

	long nTNo = GetItemLong(nRow);
	long nPayType = GetItemLong2(nRow);


	if(nTNo == MINUS_ONE)
		pItemMetrics->pFont = &pDrawArgs->pControl->GetPaintManager()->m_fontBoldText;

	if(nCol == 5 && LF->IsCash(nPayType) == FALSE)
		pItemMetrics->clrBackground = RGB(255, 0, 0);
}

void CXTPListCtrl41::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics) 
{
	int nCol = pDrawArgs->pColumn->GetItemIndex(); 
	int nRow = pDrawArgs->pRow->GetIndex(); 
	long bRiderAllocate = GetItemLong(nRow); 

	long nState = GetItemLong2(nRow);

	if(nCol == 8 && nState == 10)
		pItemMetrics->clrForeground = RGB(0, 0, 255);	
}

void CXTPListCtrl42::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{ 
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	BOOL bAdmin = GetItemLong2(nRow);
	long nWorkState = (long)GetItemData(nRow);
	long nRiderColor = GetItemLong3(nRow);

	if(pDrawArgs->pColumn->GetIndex() <= 4)
	{
		pItemMetrics->pFont = m_pfntBold;
	}

	if(bAdmin == FALSE)
	{
		pItemMetrics->clrBackground = RGB(0xE8, 0xD9, 0xFF);
	}
	else
	{
		if(nWorkState == ONE)
		{
			pItemMetrics->clrBackground = RGB(255,200,200);			
		}

		if(nCol == 4) 
		{
			if(nRiderColor == 0)
				pItemMetrics->clrBackground = RGB(255, 255, 255);
			else
				pItemMetrics->clrBackground = nRiderColor;
		}
		else if(nCol == 10) {
			if(GetItemDataText(nRow) == "1") {
				pItemMetrics->clrBackground = RGB(255, 0, 0);
				pItemMetrics->clrForeground = RGB(255, 255, 255);
			}
		}
	}
}

void CXTPListCtrl43::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{ 
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	if(GetItemLong(nRow) == FALSE)
		pItemMetrics->clrBackground = RGB(255,200,200);
}

void CXTPListCtrl44::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics) 
{
	CXTPGridRecord * pRecord = pDrawArgs->pRow->GetRecord();

	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	long nTNo = GetItemLong3(pRecord);
	CString strOCNoTotal = GetItemDataText(pRecord);

	if(strOCNoTotal == "합계")
	{
		pItemMetrics->clrForeground = RGB(0,0,255);
	}
	else if(nCol == TRANSFER_STATE_COL && nTNo != -1)
	{
		long nTransferState = GetItemLong2(pRecord);

		if(nTransferState == 0)
			pItemMetrics->clrForeground = RGB(255,0,0);
		else
			pItemMetrics->clrForeground = RGB(0,0,255);
	}

	if(nTNo == -1)
		pDrawArgs->nTextAlign = DT_CENTER;	
}

void CXTPListCtrl45::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	CBranchInfo* pBranchInfo = (CBranchInfo*)GetItemData(nRow);

	if(pBranchInfo == NULL)
		return;

	if(pBranchInfo->nRcpTextColor == pBranchInfo->nRcpColor)
	{
		pBranchInfo->nRcpColor = RGB(255 -GetRValue(pBranchInfo->nRcpColor), 
			255 - GetGValue(pBranchInfo->nRcpColor), 
			255 - GetBValue(pBranchInfo->nRcpColor));
	}

	pItemMetrics->clrForeground = RGB(GetRValue(pBranchInfo->nRcpTextColor), GetGValue(pBranchInfo->nRcpTextColor), GetBValue(pBranchInfo->nRcpTextColor));
	pItemMetrics->clrBackground = RGB(GetRValue(pBranchInfo->nRcpColor), GetGValue(pBranchInfo->nRcpColor), GetBValue(pBranchInfo->nRcpColor));
} 

void CXTPListCtrl46::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	ST_RIDER_ACCOUNT *st = (ST_RIDER_ACCOUNT*)GetItemData(pDrawArgs->pRow->GetRecord());

	if(st->nCurCharge < 0)
		pItemMetrics->clrBackground = RGB(255, 230, 230); 
}

void CXTPListCtrl47::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	if(nCol == 5)
		pItemMetrics->clrForeground = RGB(0, 0, 255);
	else if(GetItemLong(nRow) > 0 && nCol == 1)
	{
		pItemMetrics->clrBackground = RGB(200, 255, 200);
	}
}

void CXTPListCtrl48::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	switch(nCol)
	{
	case 3:
		pItemMetrics->clrForeground = RGB(0, 0, 255);
		break;
	case 4:
	case 6:
		pItemMetrics->clrForeground = RGB(255, 0, 0);
		break;
	case 5:
		pItemMetrics->clrForeground = RGB(0, 0, 255);
		break;
	case 7: 
		{
			if(atol(GetItemText(nRow, nCol)) >= 0)
				pItemMetrics->clrForeground = RGB(0, 0, 255);
			else 
				pItemMetrics->clrForeground = RGB(255, 0, 0);
		}
		break;
	case 8:
		pItemMetrics->clrForeground = RGB(0, 200, 0);
		break;
	default:
		pItemMetrics->clrForeground = RGB(0, 0, 0);
		break;
	}

	if(GetItemData(nRow) == 1)
		pItemMetrics->clrBackground = RGB(235, 235, 255);
	else
		pItemMetrics->clrBackground = RGB(255, 255, 255);

	if(nCol <= 1)
	{
		//pItemMetrics->pFont = m_pfntBold;
	}
}

void CXTPListCtrl49::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	int nState = GetItemData(nRow);
	if(nState >= 20) {
		pItemMetrics->clrBackground = RGB(235, 235, 255);
		pItemMetrics->clrForeground = RGB(0,0,0);
	}
	else if(nState <= 11) {
		pItemMetrics->clrBackground = RGB(255, 235, 235);
		pItemMetrics->clrForeground = RGB(0,0,0);
	}
	//pItemMetrics->pFont = m_pfntBold;
}

void CXTPListCtrl50::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	CString strText = GetItemText(nRow, 7);

	if(!strText.IsEmpty()) 
		pItemMetrics->clrBackground = RGB(255, 235, 235);
	
	//pItemMetrics->pFont = m_pfntBold;
}

void CCustomerGroupList::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{ 
	CCustomerGroupList *pReport = (CCustomerGroupList *)pDrawArgs->pControl;
	long nGroupOwner = pReport->GetItemLong2(pDrawArgs->pRow->GetRecord());		

	if(nGroupOwner !=  0)
		pItemMetrics->clrForeground = RGB(0, 200, 0);
}

void CGroupListReport24::SetGroupData(long nGNo, GROUP_REPORT st, BOOL bSumReport)
{
	for(int i=0; i<GetRows()->GetCount(); i++)
	{
		CGroupReportRecord24 * pRecord = (CGroupReportRecord24*)GetRows()->GetAt(i)->GetRecord();

		if(pRecord->m_nGNo == nGNo && pRecord->m_bSumRecord == bSumReport)
		{ 
			pRecord->m_stGroup = st;
			pRecord->m_bHasData = TRUE;
			break; 
		} 
	}
}

void CGroupList24::SetSelected(long nGNo, BOOL bSelect)
{
	for(int i=0; i<GetRows()->GetCount(); i++)
	{
		CGroupRecord24 * pRecord = (CGroupRecord24*)GetRows()->GetAt(i)->GetRecord();

		if(pRecord->m_nGNo == nGNo)
		{
			pRecord->m_bSelect = bSelect;
			break;
		}
	}
}

void CXTPGridControl12::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	CUnBillRecord * pReocord = (CUnBillRecord*)pDrawArgs->pRow->GetRecord();

	if(pReocord->GetChilds()->GetCount() > 0)
		pItemMetrics->clrBackground = RGB(230, 255,150);

	CRect rc = pDrawArgs->rcItem;

	if(pDrawArgs->pDC)
	{
		CPen Pen;    
		Pen.CreatePen(PS_SOLID, 1, RGB(222, 222, 222));
		CPen *pOldPen = pDrawArgs->pDC->SelectObject(&Pen);

		pDrawArgs->pDC->MoveTo(rc.right -1, rc.top); 
		pDrawArgs->pDC->LineTo(rc.right -1, rc.bottom); 

		pDrawArgs->pDC->SelectObject(pOldPen);
	}
}

void CGroupList1::SetSelected(long nGNo, BOOL bSelect)
{
	for(int i=0; i<GetRows()->GetCount(); i++)
	{
		CGroupRecord * pRecord = (CGroupRecord*)GetRows()->GetAt(i)->GetRecord();

		if(pRecord->m_nGNo == nGNo)
		{
			pRecord->m_bSelect = bSelect;
			break;
		}
	}
}

void CGroupListReport::SetGroupData(long nGNo, GROUP_REPORT st, BOOL bSumReport)
{
	for(int i=0; i<GetRows()->GetCount(); i++)
	{
		CGroupReportRecord * pRecord = (CGroupReportRecord*)GetRows()->GetAt(i)->GetRecord();

		if(pRecord->m_nGNo == nGNo && pRecord->m_bSumRecord == bSumReport)
		{ 
			pRecord->m_stGroup = st;
			pRecord->m_bHasData = TRUE;
			break; 
		} 
	}
}

void CGroupList::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS *pDrawArgs, XTP_REPORTRECORDITEM_METRICS *pMetrics )
{
	CString strColumn = pDrawArgs->pColumn->GetCaption();
	int nRow = pDrawArgs->pRow->GetIndex();
	int nCount = pDrawArgs->pControl->GetRows()->GetCount();
	int nCol = pDrawArgs->pColumn->GetIndex();
	int nItemCol = pDrawArgs->pColumn->GetItemIndex();

	if(nCol == 2)
	{
		char buffer[10];
		int nMember = atol(GetItemText(nRow,2));

		if(pDrawArgs->pRow->HasChildren())
		{
			CXTPGridRows *pRows = pDrawArgs->pRow->GetChilds();
			for(int i = 0; i < pRows->GetCount(); i++)
			{
				CXTPGridRow *pRow = pRows->GetAt(i);
				CXTPGridColumn *pColumn = NULL;
				CString strMembers= "";
				strMembers = pRow->GetRecord()->GetItem(2)->GetCaption(pColumn);
				nMember += atol(strMembers);
			}
			SetItemText(nRow,2,ltoa(nMember,buffer,10));	
		}
	}
}
void CustomerList::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS *pDrawArgs, XTP_REPORTRECORDITEM_METRICS *pMetrics )
{
	CString strColumn = pDrawArgs->pColumn->GetCaption();
	int nRow = pDrawArgs->pRow->GetIndex();
	int nCount = pDrawArgs->pControl->GetRows()->GetCount();
	int nCol = pDrawArgs->pColumn->GetIndex();
	int nItemCol = pDrawArgs->pColumn->GetItemIndex();

	if(GetItemText(nRow,1).GetLength() > 0 && nCol == 1)
		pMetrics->clrBackground = RGB(224,244,255);
}

void CMembers::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS *pDrawArgs, XTP_REPORTRECORDITEM_METRICS *pMetrics )
{
	CString strColumn = pDrawArgs->pColumn->GetCaption();
	int nRow = pDrawArgs->pRow->GetIndex();
	int nCount = pDrawArgs->pControl->GetRows()->GetCount();
	int nCol = pDrawArgs->pColumn->GetIndex();
	int nItemCol = pDrawArgs->pColumn->GetItemIndex();

	if(GetItemDataLong2(nRow) == m_nGNo)
		pMetrics->clrBackground = RGB(255,125,165);
}

void CGroupList2::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS *pDrawArgs, XTP_REPORTRECORDITEM_METRICS *pItemMetrics )
{
	CString strColumn = pDrawArgs->pColumn->GetCaption();
	int nRow = pDrawArgs->pRow->GetIndex();
	int nCount = pDrawArgs->pControl->GetRows()->GetCount();
	int nCol = pDrawArgs->pColumn->GetIndex();
	int nItemCol = pDrawArgs->pColumn->GetItemIndex();


	long nCNo = GetItemDataLong2(nRow);
	if(nCNo > 0)
	{	
		LOGFONT accesscontrol_static_lfont = {14,0,0,0,FW_BOLD,0,0,0,HANGUL_CHARSET,0,0,0,0,"돋움"};			
		pDrawArgs->pControl->GetPaintManager()->m_fontText.GetLogFont(&accesscontrol_static_lfont);
		pItemMetrics->clrForeground = RGB(0, 200, 0);
	}		
}

void ChargeList::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS *pDrawArgs, XTP_REPORTRECORDITEM_METRICS *pMetrics )
{
	CString strColumn = pDrawArgs->pColumn->GetCaption();
	int nRow = pDrawArgs->pRow->GetIndex();
	int nCount = pDrawArgs->pControl->GetRows()->GetCount();
	int nCol = pDrawArgs->pColumn->GetIndex();
	int nItemCol = pDrawArgs->pColumn->GetItemIndex();

	if( pDrawArgs->pControl->GetRecords()->GetCount() > 4)
	{
		if(nRow == 4 && nCol == m_nCarType + 1)
			pMetrics->clrBackground = RGB(230,193,7);
	}
	else
	{
		if(m_nChargeType  == nRow && nCol == m_nCarType + 1 )
			pMetrics->clrBackground = RGB(230,193,7);
	}
}

void CMyMileageReport::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nRow = pDrawArgs->pRow->GetIndex();
	int nCount = pDrawArgs->pControl->GetRows()->GetCount();
	int nCol = pDrawArgs->pColumn->GetIndex();
	int nItemCol = pDrawArgs->pColumn->GetItemIndex();

	if(nCol == 0)
		pDrawArgs->pItem->SetCaption(m_mapData[m_mapRow[nRow]].strCName);
}
