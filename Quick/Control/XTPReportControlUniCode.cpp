#include "stdafx.h"
#include "XTPReportControlUniCode.h"
#include "XTPReportColumnUniCode.h"
#include "XTPReportRecordUniCode.h"


IMPLEMENT_DYNAMIC(CXTPReportControlUniCode, CXTPGridControl)

CXTPReportControlUniCode::CXTPReportControlUniCode()
{
}


CXTPReportControlUniCode::~CXTPReportControlUniCode()
{
}


void CXTPReportControlUniCode::EnableMarkup(BOOL bEnable)
{
	if (m_bMarkupEnabled == bEnable)
		return;

	m_bMarkupEnabled = bEnable;

	XTPMarkupReleaseContext(m_pMarkupContext);

	if (bEnable)
	{
		m_pMarkupContext = XTPMarkupCreateContext(m_hWnd);
	}

	m_pSections->SetMarkupContext(m_pMarkupContext);

	// Reset Markup UI Elements
	CXTPGridColumns *pColumns = GetColumns();
	int nColumnsCount = pColumns->GetCount();
	for (int nColumn = 0; nColumn<nColumnsCount; nColumn++)
	{
		//CXTPGridColumn *pColumn = pColumns->GetAt(nColumn);
		CXTPGridColumnUniCode *pColumn = (CXTPGridColumnUniCode*)pColumns->GetAt(nColumn);
		
		if (pColumn)
			pColumn->ResetMarkupUIElement();
	}

	for (int nSection = 0; nSection<m_pSections->GetSize(); nSection++)
	{
		CXTPGridSection* pSection = m_pSections->GetAt(nSection);
		if (pSection == NULL)
			continue;

		CXTPGridRows* pRows = pSection->GetRows();
		if (pRows)
		{
			for (int nRow = 0; nRow<pRows->GetCount(); nRow++)
			{
				CXTPGridRow* pRow = pRows->GetAt(nRow);
				if (pRow && pRow->IsGroupRow())
				{
					((CXTPGridGroupRow*)pRow)->ResetMarkupUIElement();
				}
			}
		}

		CXTPGridRecords* pRecords = pSection->GetRecords();
		if (pRecords)
		{
			for (int nRecord = 0; nRecord<pRecords->GetCount(); nRecord++)
			{
				CXTPGridRecord* pRecord = pRecords->GetAt(nRecord);
				if (pRecord == NULL)
					continue;

				int nItemsCount = pRecord->GetItemCount();
				for (int nItem = 0; nItem<nItemsCount; nItem++)
				{
					CXTPGridRecordItem* pRecordItem = pRecord->GetItem(nItem);
					if (pRecordItem)
						pRecordItem->ResetMarkupUIElement();
				}
			}
		}
	}//for (sections)

	AdjustScrollBars();
}

CXTPGridColumn* CXTPReportControlUniCode::InsertColumn(int nItemIndex, LPCTSTR strName, int nWidth)
{
	CXTPGridColumnUniCode *pColumn = new CXTPGridColumnUniCode(nItemIndex, strName, nWidth);
	CXTPGridColumn* pColumn1 = (CXTPGridColumn*)pColumn;
	return AddColumn(pColumn1);
}

CXTPGridRecord* CXTPReportControlUniCode::AddRecord(CXTPGridRecordUniCode*pRecord)
{
	return m_pSectionBody->AddRecord((CXTPGridRecord*)pRecord);
}


void CXTPReportControlUniCode::DrawNoItems(CDC* pDC, const CRect& rcClient)
{
	pDC->SetTextColor(GetPaintManager()->m_clrWindowText);
	CString strNoItems = GetPaintManager()->m_strNoItems;

	if (!strNoItems.IsEmpty())
	{
		CRect rcText(rcClient);
		rcText.DeflateRect(5, 5, 5, 5);
		CXTPFontDC font(pDC, &GetPaintManager()->m_fontText);
		UINT uFlags = DT_CENTER | DT_TOP | DT_NOPREFIX | DT_WORDBREAK |
			DT_WORD_ELLIPSIS | DT_END_ELLIPSIS | DT_EDITCONTROL;
		
		XTPMarkupDrawText(GetMarkupContext(), pDC->GetSafeHdc(), strNoItems, rcText, uFlags);
	}
}

void CXTPReportControlUniCode::XTPMarkupDrawText(CXTPMarkupContext* pContext, HDC hDC, LPCTSTR lpszText, LPRECT lpRect, UINT nFormat)
{
	USES_CONVERSION;
	LPWSTR lpszwMarkup = A2W(lpszText);

	CXTPMarkupUIElement* pElement = pContext ? XTPMarkupParseText(pContext, lpszwMarkup) : NULL;

	if (pElement)
	{
		XTPMarkupSetDefaultFont(pContext, (HFONT)::GetCurrentObject(hDC, OBJ_FONT), ::GetTextColor(hDC));

		CSize sz = XTPMarkupMeasureElement(pElement, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top);

		int nLeft = lpRect->left;
		int nTop = lpRect->top;

		if (nFormat & DT_CENTER)
			nLeft = (lpRect->right + lpRect->left - sz.cx) / 2;
		else if (nFormat & DT_RIGHT)
			nLeft = lpRect->right - sz.cx;

		if (nFormat & DT_VCENTER)
			nTop = (lpRect->top + lpRect->bottom - sz.cy) / 2;
		else if (nFormat & DT_BOTTOM)
			nTop = lpRect->bottom - sz.cy;

		XTPMarkupRenderElement(pElement, hDC, CRect(nLeft, nTop, nLeft + sz.cx, nTop + sz.cy));


		XTPMarkupReleaseElement(pElement);
	}
	else
	{
		::DrawText(hDC, lpszText, (int)_tcslen(lpszText), lpRect, nFormat);
	}
}

BEGIN_MESSAGE_MAP(CXTPReportControlUniCode, CXTPGridControl)
ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


void CXTPReportControlUniCode::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
