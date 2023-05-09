#include "stdafx.h"
#include "XTPReportRecordItemUniCode.h"


CXTPGridRecordItemUniCode::CXTPGridRecordItemUniCode()
{
}


CXTPGridRecordItemUniCode::~CXTPGridRecordItemUniCode()
{
}

void CXTPGridRecordItemUniCode::SetRecord(CXTPGridRecord* pReportRecord)
{
	m_pRecord = pReportRecord;
	ResetMarkupUIElement();
}

void CXTPGridRecordItemUniCode::ResetMarkupUIElement()
{
	XTPMarkupReleaseElement(m_pMarkupUIElement);


	USES_CONVERSION;
	LPWSTR lpszwMarkup A2W(m_strCaption);

	CXTPMarkupContext* pMarkupContext = m_pRecord ? m_pRecord->GetMarkupContext() : NULL;
	if (pMarkupContext)
		m_pMarkupUIElement = XTPMarkupParseText(pMarkupContext, lpszwMarkup);	// don't GetCaption()
}