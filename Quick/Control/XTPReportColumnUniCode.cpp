#include "stdafx.h"
#include "XTPReportColumnUniCode.h"



CXTPGridColumnUniCode::CXTPGridColumnUniCode(int nItemIndex, LPCTSTR strName, int nWidth, BOOL bAutoSize, int nIconID, BOOL bSortable, BOOL bVisible)
	: CXTPGridColumn(nItemIndex, strName, nWidth, bAutoSize, nIconID, bSortable, bVisible)
{
}

CXTPGridColumnUniCode::CXTPGridColumnUniCode(int nItemIndex, LPCTSTR strDisplayName, LPCTSTR strInternalName, int nWidth, BOOL bAutoSize, int nIconID, BOOL bSortable, BOOL bVisible)
	: CXTPGridColumn(nItemIndex, strDisplayName, strInternalName, nWidth, bAutoSize, nIconID, bSortable, bVisible)
{
}

CXTPGridColumnUniCode::~CXTPGridColumnUniCode()
{
}

void CXTPGridColumnUniCode::ResetMarkupUIElement()
{
	XTPMarkupReleaseElement(m_pMarkupUIElement);

	//GetColumns()
	
	//CXTPGridControl* pControl = m_pColumns->m_pControl;
	//CXTPGridControl* pControl = GetColumns()->GetControl;
	CXTPGridControl* pControl = GetControl();
	if (pControl && pControl->GetMarkupContext())
	{
		USES_CONVERSION;
		LPWSTR lpszwMarkup A2W(m_strName);

		m_pMarkupUIElement = XTPMarkupParseText(pControl->GetMarkupContext(), lpszwMarkup);
		//m_pMarkupUIElement = XTPMarkupParseText(pControl->GetMarkupContext(), m_strName);
	}
}