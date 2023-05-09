#include "stdafx.h"
#include "XTPReportRecordUniCode.h"
#include "XTPReportRecordItemUniCode.h"
#include "XTPReportRecordItemTextUniCode.h"

CXTPGridRecordUniCode::CXTPGridRecordUniCode()
{
}


CXTPGridRecordUniCode::~CXTPGridRecordUniCode()
{
}

CXTPGridRecordItem* CXTPGridRecordUniCode::AddItem(CXTPGridRecordItemUniCode* pItem)
{
	m_arrItems.Add(pItem);
	pItem->SetControl(this->m_pControl);
	//pItem->m_pControl = this->m_pControl;
	pItem->SetRecord(this);
	return pItem;
}

CXTPGridRecordItem* CXTPGridRecordUniCode::AddItem(CXTPGridRecordItemTextUniCode* pItem)
{
	m_arrItems.Add(pItem);
	pItem->SetControl(this->m_pControl);
	//pItem->m_pControl = this->m_pControl;
	pItem->SetRecord(this);
	return pItem;
	//return AddItem(pItem);
	//return CXTPGridRecord::AddItem(pItem);
	/*
	m_arrItems.Add(pItem);
	//pItem->SetControl(this->m_pControl);
	pItem->m_pControl = this->m_pControl
	//pItem->m_pControl = this->m_pControl;
	pItem->SetRecord(this);
	return pItem;
	*/
}

void CXTPGridRecordUniCode::SetReportControl(CXTPGridControl* pReportControl)
{
	m_pControl = pReportControl;
	for (int nItem = 0; nItem < GetItemCount(); ++nItem)
	{
		CXTPGridRecordItemUniCode* pItem = (CXTPGridRecordItemUniCode*)m_arrItems.GetAt(nItem);
		if (pItem)
		{	
			//pItem->m_pControl = m_pControl;
			pItem->SetControl(m_pControl);
			pItem->ResetMarkupUIElement();
		}
	}
}

CXTPGridRecord* CXTPGridRecordUniCode::Add(CXTPGridRecord* pRecord)
{
	/*
	int nIndex = (int)m_arrRecords.Add(pRecord);

	if (m_bArray)
	{
		ASSERT(pRecord->m_pRecords);
	}
	else
	{
		pRecord->m_nIndex = nIndex;
		pRecord->m_pRecords = this;
		pRecord->SetReportControl(m_pControl);
	}
	*/
	return pRecord;
}