#include "stdafx.h"
#include "XTPReportRecordItemTextUniCode.h"


CXTPGridRecordItemTextUniCode::CXTPGridRecordItemTextUniCode()
{
}


CXTPGridRecordItemTextUniCode::~CXTPGridRecordItemTextUniCode()
{
}

void CXTPGridRecordItemTextUniCode::SetRecord(CXTPGridRecord* pReportRecord)
{
	m_pRecord = pReportRecord;
	ResetMarkupUIElement();
}

void CXTPGridRecordItemTextUniCode::ResetMarkupUIElement()
{
	XTPMarkupReleaseElement(m_pMarkupUIElement);


	USES_CONVERSION;
	LPWSTR lpszwMarkup A2W(m_strCaption);

	CXTPMarkupContext* pMarkupContext = m_pRecord ? m_pRecord->GetMarkupContext() : NULL;
	if (pMarkupContext)
		m_pMarkupUIElement = XTPMarkupParseText(pMarkupContext, lpszwMarkup);	// don't GetCaption()
}