#pragma once

#include "SearchPOI.h"
#include "POIReportControl.h"
#include "HttpParser.h"

#include "XTPReportRecordUniCode.h"
#include "XTPReportRecordItemUniCode.h"
#include "XTPReportRecordItemTextUniCode.h"

#define DONG_COL_COUNT 3

class CSearchDongRecord : public CXTPGridRecordUniCode
{
public:

	CSearchDongRecord()
	{
		m_nCount = 0;
		for(int i = 0; i < DONG_COL_COUNT; i++)
			m_pPOI[i] = NULL;
	}

	void AddRecordItem(CPOIUnit *pPOI, CString &strMarkup)
	{
		m_pPOI[m_nCount] = pPOI;
		m_strMarkupRegionName[m_nCount] = strMarkup.GetLength() > 0 ? 
strMarkup : pPOI->GetRegionName();
		AddItem(new CXTPGridRecordItemTextUniCode(m_strMarkupRegionName[m_nCount++]));
	}

	void AddDummyItem()
	{
		AddItem(new CXTPGridRecordItemTextUniCode(""));
	}

	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		int nCol = pDrawArgs->pColumn->GetItemIndex();

		if(pDrawArgs->pRow->IsFocused())
		{
			if(m_nCount == 1 && nCol == 0)
			{
				pItemMetrics->clrBackground = RGB(255, 220, 255);
				pItemMetrics->clrForeground= RGB(0, 0, 0);
			}
			else if(pDrawArgs->pControl->GetFocusedColumn()->GetItemIndex() == nCol)
			{
				if(!m_strMarkupRegionName[nCol].IsEmpty())
				{
					pItemMetrics->clrBackground = RGB(255, 220, 255);
					pItemMetrics->clrForeground= RGB(0, 0, 0);
				}
			}
		}
	}

	void RedrawMarkupName()
	{
		for(int i = 0; i < DONG_COL_COUNT; i++)
			GetItem(i)->SetCaption(m_strMarkupRegionName[i]);
	}

	CPOIUnit *m_pPOI[DONG_COL_COUNT];
	CString m_strMarkupRegionName[DONG_COL_COUNT];
	long m_nCount;
};



#define PARENT_RECORD() ((CSearchPOIRecord*)GetRecord())
#define SEARCHPOI() PARENT_RECORD()->m_pSearchPOI

class CSearchPOIRecord : public CXTPGridRecordUniCode
{
protected:
	class CPOIDataPhoneItem : public CXTPGridRecordItemUniCode
	{
	public:
		CPOIDataPhoneItem() : CXTPGridRecordItemUniCode()
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{

			if(SEARCHPOI()->pPOI)
				return SEARCHPOI()->pPOI->GetPhoneNumber();
			else
				return "";

			return "";
		}
	};


	class CPOIDataNearNameItem : public CXTPGridRecordItemUniCode
	{
	public:
		CPOIDataNearNameItem() : CXTPGridRecordItemUniCode()
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{

			if(SEARCHPOI()->pBasePOI)
				return SEARCHPOI()->pBasePOI->GetPOIName();
			else if(SEARCHPOI()->pDongMatchPOI && 
				!SEARCHPOI()->pPOI->IsSameDong(SEARCHPOI()->pDongMatchPOI))
				return SEARCHPOI()->pDongMatchPOI->m_szDong;
			else if(SEARCHPOI()->pNearPOI)
				return SEARCHPOI()->pNearPOI->GetPOIName();
			else
				return "";

			return "";
		}
	};

	class CPOIDataDistanceItem : public CXTPGridRecordItemUniCode
	{
	public:
		CPOIDataDistanceItem() : CXTPGridRecordItemUniCode()
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			CString strDistance;

			if(SEARCHPOI()->pBasePOI)
			{
				int nMeter = SEARCHPOI()->pPOI->IsNearPOI(SEARCHPOI()->pBasePOI);
				GetMeterDisplay("→", strDistance, nMeter);
			}
			else if(SEARCHPOI()->pDongMatchPOI &&
				!SEARCHPOI()->pPOI->IsSameDong(SEARCHPOI()->pDongMatchPOI))
			{
				int nMeter = SEARCHPOI()->pPOI->IsNearPOI(SEARCHPOI()->pDongMatchPOI);
				GetMeterDisplay("→", strDistance, nMeter);
			}
			else if(SEARCHPOI()->pNearPOI)
			{
				int nMeter = SEARCHPOI()->pPOI->IsNearPOI(SEARCHPOI()->pNearPOI);
				GetMeterDisplay("→", strDistance, nMeter);
			}
			else if(SEARCHPOI()->pPrePOI)
			{
				int nMeter = SEARCHPOI()->pPOI->IsNearPOI(SEARCHPOI()->pPrePOI);
				GetMeterDisplay("↑", strDistance, nMeter);
			}

			return strDistance;
		}

		void GetMeterDisplay(CString strSymbol, CString &strDistance, int &nMeter)
		{
			if(nMeter == 0)
				strDistance = strSymbol;
			else if(nMeter == 1)
				strDistance = strSymbol + " 일치";
			else 
				strDistance.Format("%s %d", strSymbol, nMeter);
		}
	};



public:

	CSearchPOIRecord(CSearchPOI *pSearchPOI, long nApiType = 0)
	{
		if(!pSearchPOI)
			return;

		m_pSearchPOI = pSearchPOI;
		AddItem(new CXTPGridRecordItemTextUniCode(m_pSearchPOI->GetMarkupPOIName()));
		AddItem(new CXTPGridRecordItemTextUniCode(m_pSearchPOI->GetMarkupRegionName()));
		AddItem(new CPOIDataNearNameItem());
		AddItem(new CPOIDataDistanceItem());
		AddItem(new CPOIDataPhoneItem()); 
		m_nApiType = nApiType;	
	}


	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		int nCol = pDrawArgs->pColumn->GetIndex();

		if(nCol == 2 && m_pSearchPOI->pBasePOI)
		{
			pItemMetrics->clrBackground = RGB(255, 255, 255);
			pItemMetrics->clrForeground= RGB(0, 150, 0);

		}
		else if(m_pSearchPOI->bAddressSearch)
		{
			pItemMetrics->clrBackground = RGB(255, 255, 220);
			pItemMetrics->clrForeground= RGB(0, 0, 0);
		}
		else if(m_pSearchPOI->bWebSearch)
		{
			if(m_nApiType == NAVER)
				pItemMetrics->clrBackground = RGB(220, 255, 220);
			else if(m_nApiType == DAUM)
				pItemMetrics->clrBackground = RGB(255, 255, 220);
			else if(m_nApiType == GOOGLE)
				pItemMetrics->clrBackground = RGB(220, 255, 255);

			pItemMetrics->clrForeground= RGB(0, 0, 0);
			//pItemMetrics->clrBackground = RGB(220, 255, 220);
			//pItemMetrics->clrForeground= RGB(0, 0, 0);
		}

		if(nCol == 4 && m_pSearchPOI->bPhoneMatch)
		{
			pItemMetrics->clrBackground = RGB(255, 220, 255);
			pItemMetrics->clrForeground= RGB(0, 0, 0);
		}

	}

	void RedrawMarkupName()
	{
		GetItem(0)->SetCaption(m_pSearchPOI->GetMarkupPOIName());
		GetItem(1)->SetCaption(m_pSearchPOI->GetMarkupRegionName());
	}

	CSearchPOI *m_pSearchPOI;
	long m_nApiType;
};

class CSearchCusRecord : public CXTPGridRecord
{
public:

	CSearchCusRecord(SEARCH_CUS_DATA &data, CString &strKeyword)
	{
		m_bExpanded = FALSE;
		m_pscus = &data;
		m_strKeyword = strKeyword;
		CXTPGridRecordItem *pItem = AddItem(new CXTPGridRecordItem);
		pItem->SetIconIndex(IsParent() ? GetIconIndex() : XTP_GRID_NOICON);
		AddItem(new CXTPGridRecordItemTextUniCode(GetCompanyMU()));
		AddItem(new CXTPGridRecordItemTextUniCode(GetDepartMU()));
		AddItem(new CXTPGridRecordItemTextUniCode(GetManagerMU()));
		AddItem(new CXTPGridRecordItemTextUniCode(GetPhoneMU()));
		AddItem(new CXTPGridRecordItemTextUniCode(m_pscus->pData->szDong));
		AddItem(new CXTPGridRecordItemTextUniCode(GetUseExpiredDayString()));
		AddItem(new CXTPGridRecordItemTextUniCode(GetUseCountString()));

	}

	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		int nCol = pDrawArgs->pColumn->GetIndex(); 

		if(nCol == 1)
		{
			if(m_pscus->pData->bCredit == 1)
				pItemMetrics->clrBackground = RGB(255, 230, 230);
			else
				pItemMetrics->clrBackground = RGB(255, 255, 255);
		}
	}

	void RedrawMarkupName()
	{
		GetItem(1)->SetCaption(GetCompanyMU());
		GetItem(2)->SetCaption(GetDepartMU());
		GetItem(3)->SetCaption(GetManagerMU());
		GetItem(4)->SetCaption(GetPhoneMU());
	}

	CUSTOMER_DATA *GetCustomer()
	{
		return m_pscus->pData;
	}

	CString GetPhoneNumber() { return LF->GetNoneDashNumberRemoveDDD(m_pscus->strPhone); }
	long GetTelID() { return m_pscus->nTelID; }
	BOOL IsChild() { return m_pscus->bHasParentOrChild && m_pscus->nMainPhone == 0; }
	BOOL IsParent() { return m_pscus->bHasParentOrChild && m_pscus->nMainPhone != 0; }
	void SetExpand(BOOL bExpand) 
	{ 
		if(m_bExpanded != bExpand)
		{
			m_bExpanded = bExpand; 
			GetItem(0)->SetIconIndex(GetIconIndex());
		}
		else
		{
			m_bExpanded = bExpand; 
		}
	}

	int GetIconIndex() { return m_bExpanded ? 1 : 0; }

protected:
	CString GetUseExpiredDayString()
	{
		char buffer[20];

		long nExpired = m_pscus->nPhoneExpiredDay;

		if(nExpired == 0)
			return "오늘";
		else if(nExpired < 365)
			return CString(ltoa(nExpired, buffer, 10)) + "일";
		else if(nExpired < 730)
			return "1년+";
		else if(nExpired < 10000)
			return "2년+";
		else
			return "-";
	}

	CString GetUseCountString()
	{
		char buffer[20];
		if(m_pscus->pData->nUseCount == 0)
			return "-";
		else
			return ltoa(m_pscus->pData->nUseCount, buffer, 10);
	}

	CString GetCompanyMU()
	{
		CString strA = CSearchPOI::GetMarkupReplaceWordSlash(
			GetHeadSymbol() + 
			(m_pscus->pData->szCompany[0] == 0 ? "일반" : m_pscus->pData->szCompany), 
			m_strKeyword);

		/*
		if(!GetHeadSymbol().IsEmpty())
		{
			int a= 0;
		}

		CString T = CSearchPOI::GetMarkupReplaceWordSlash(
			GetHeadSymbol() +
			(m_pscus->pData->szCompany[0] == 0 ? "일반" : m_pscus->pData->szCompany),
			m_strKeyword);
		*/

		return CSearchPOI::GetMarkupReplaceWordSlash(
			GetHeadSymbol() + 
			(m_pscus->pData->szCompany[0] == 0 ? "일반" : m_pscus->pData->szCompany), 
			m_strKeyword);
	}

	CString GetDepartMU()
	{
		return CSearchPOI::GetMarkupReplaceWordSlash(m_pscus->strDepart, m_strKeyword);
	}

	CString GetManagerMU()
	{
		return CSearchPOI::GetMarkupReplaceWordSlash(m_pscus->strName, m_strKeyword);
	}

	CString GetPhoneMU()
	{
		return CSearchPOI::GetMarkupReplaceWordSlash(LF->GetDashPhoneNumber(m_pscus->strPhone), LF->GetDashPhoneNumber(m_strKeyword));
	}

	CString GetHeadSymbol()
	{
		if(m_pscus->bHasParentOrChild)
		{
			if(m_pscus->nMainPhone == 0)
			{
				if(m_pscus->bHasNextMember)
					return "├";
				else 
					return "└";
			}
		}

		return "";
	}


protected:
	SEARCH_CUS_DATA *m_pscus;
	CString m_strKeyword;
	BOOL m_bExpanded;
};

