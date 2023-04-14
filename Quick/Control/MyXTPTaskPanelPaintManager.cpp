
#include "StdAfx.h"
#include "MainFrm.h"
//#include "BranchSel.h"
#include "myxtptaskpanelpaintmanager.h"



CMyXTPTaskPanelPaintManager::CMyXTPTaskPanelPaintManager(void)
{
}

CMyXTPTaskPanelPaintManager::~CMyXTPTaskPanelPaintManager(void)
{
}

void CMyXTPTaskPanelPaintManager::DrawItemCaption(CDC* pDC, CXTPTaskPanelItem* pItem, CRect rcText, UINT nFormat)
{
	if (!pItem->IsGroup())
	{
		XTPTaskPanelHotTrackStyle hotTrackStyle = pItem->GetTaskPanel()->GetHotTrackStyle();

		CXTPTaskPanelGroup* pGroup = pItem->GetItemGroup();
		XTP_TASKPANEL_GROUPCOLORS* pGroupColors = GetGroupColors(pGroup);

		pDC->SetBkMode(TRANSPARENT);

		if (m_bEmbossedDisabledText && !pItem->GetEnabled())
		{
			pDC->SetTextColor(GetXtremeColor(COLOR_3DHIGHLIGHT));
			pItem->DrawCaptionText(pDC, rcText + CPoint(1, 1), nFormat);
		}
		COLORREF clrNormal = ((CXTPTaskPanelGroupItem*)pItem)->GetTextColor();
		if (clrNormal == COLORREF_NULL)
			clrNormal = pItem->GetType() == xtpTaskItemTypeLink ? pGroupColors->clrClientLink : pGroupColors->clrClientText;

		pDC->SetTextColor(!pItem->GetEnabled() ? GetXtremeColor(COLOR_GRAYTEXT) : pItem->GetType() == xtpTaskItemTypeLink ?
			(pItem->IsItemHot() && (hotTrackStyle == xtpTaskPanelHighlightText || pGroupColors->clrClientLinkHot.IsCustomValue()) ? pGroupColors->clrClientLinkHot :
		(hotTrackStyle == xtpTaskPanelHighlightItem) && (((CXTPTaskPanelGroupItem*)pItem)->IsItemSelected() || (pItem->IsItemHot())) ? pGroupColors->clrClientLinkSelected :
		clrNormal) : clrNormal);

		if(!pItem->IsItemHot() && !((CXTPTaskPanelGroupItem*)pItem)->IsItemSelected())
		{
		}
	}

	pItem->DrawCaptionText(pDC, rcText, nFormat);
	pItem->SetTextRect(pDC, rcText, nFormat);
}

CRect CMyXTPTaskPanelPaintManager::DrawGroupItem(CDC* pDC, CXTPTaskPanelGroupItem* pItem, CRect rc, BOOL bDraw)
{
	XTPTaskPanelItemLayout itemLayout = pItem->GetItemGroup()->GetItemLayout();

	CRect rcItem = itemLayout == xtpTaskItemLayoutImagesWithTextBelow ? DrawGroupItemImageWithTextBelow(pDC, pItem, rc, bDraw) :
		itemLayout == xtpTaskItemLayoutImages ? DrawGroupItemImage(pDC, pItem, rc, bDraw) :  DrawGroupItemImageWithText2(pDC, pItem, rc, bDraw);

	if (bDraw && pItem->IsItemDragOver() && !pItem->IsItemDragging())
	{
		DrawDragArrow(pDC, pItem, rc);
	}
	if (bDraw && pItem->GetItemGroup()->IsItemDragOver() &&
		pItem->GetParentItems()->GetLastVisibleItem() == pItem)
	{
		DrawDragArrow(pDC, pItem, rc, TRUE);
	}

	return rcItem;
}

CRect CMyXTPTaskPanelPaintManager::DrawGroupItemImageWithText2(CDC* pDC, CXTPTaskPanelGroupItem* pItem, CRect rc, BOOL bDraw)
{
	CXTPTaskPanelGroup* pGroup = pItem->GetItemGroup();
	ASSERT(pGroup);
	if (!pGroup)
		return 0;

	XTPTaskPanelHotTrackStyle hotTrackStyle = pItem->GetTaskPanel()->GetHotTrackStyle();
	CSize szIcon = pGroup->GetItemIconSize();

	CXTPFontDC font(pDC, GetItemFont(pItem));

	CXTPImageManagerIcon* pImage = pItem->GetImage(szIcon.cx);
	BOOL bDrawIcon = pItem->GetType() != xtpTaskItemTypeControl && pImage;
	CRect rcInnerMargins = GetItemInnerMargins(pItem);

	if (bDraw)
	{
		if (hotTrackStyle == xtpTaskPanelHighlightItem)
		{
			DrawGroupItemFrame(pDC, pItem, rc);
		}
		rc.DeflateRect(rcInnerMargins.left, rcInnerMargins.top, rcInnerMargins.right, rcInnerMargins.bottom);

		CRect rcText(rc);

		if (hotTrackStyle == xtpTaskPanelHighlightItem)
			rcText.OffsetRect(GetHighlightOffset(pItem));

		CRect rcIconPadding(GetItemIconPadding(pItem));

		if (bDrawIcon)
		{
			if (hotTrackStyle == xtpTaskPanelHighlightImage)
			{
				CRect rcImage(rc.left - rcInnerMargins.left, rc.top - rcInnerMargins.top,
					rc.left + szIcon.cx + 2 + rcIconPadding.left + rcIconPadding.right,
					rc.top + szIcon.cy + 2 + rcIconPadding.top + rcIconPadding.bottom);
				DrawGroupItemFrame(pDC, pItem, rcImage);
			}
			CPoint ptIcon(rc.TopLeft());

			if (hotTrackStyle == xtpTaskPanelHighlightImage || hotTrackStyle == xtpTaskPanelHighlightItem)
				ptIcon.Offset(GetHighlightOffset(pItem));

			ptIcon.Offset(rcIconPadding.left, rcIconPadding.top);

			DrawItemImage(pDC, pItem, ptIcon, pImage, szIcon);
		}

		//if (bDrawIcon || pItem->GetType() == xtpTaskItemTypeLink)
		if (bDrawIcon)
		{
			rcText.left += szIcon.cx + 7 + rcIconPadding.left + rcIconPadding.right;
		}

		rcText.left += 2;
		rcText.right -= 1;

		if (rcText.Width() > 0)
		{
			DrawItemCaption(pDC, pItem, rcText, m_nItemTextFormat | DT_LEFT);
		}

		if (pItem->IsItemFocused() && pItem->GetTaskPanel()->IsDrawFocusRect())
		{
			DrawFocusRect(pDC, rc);
		}
		return 0;
	}
	else
	{
		CRect rcText(rc);
		rcText.bottom = rcText.top;
		rcText.DeflateRect(rcInnerMargins.left, 0, rcInnerMargins.right, 0);

		CRect rcIconPadding(GetItemIconPadding(pItem));

		//if (pItem->GetType() == xtpTaskItemTypeLink || bDrawIcon)
		if (bDrawIcon)
		{
			rcText.left += szIcon.cx + 7 + rcIconPadding.left + rcIconPadding.right;
		}

		rcText.left += 2;
		rcText.right -= 1;


		if (rcText.Width() > 0)
		{
			CSize szText = pItem->GetCaptionTextSize(pDC, rcText, (m_nItemTextFormat | DT_LEFT) & ~(DT_VCENTER | DT_CENTER));
			rcText.bottom = rcText.top + szText.cy;
			rcText.right = rcText.left + szText.cx;
		}
		int nImageHeight = bDrawIcon ? szIcon.cy + rcIconPadding.top + rcIconPadding.bottom : 0;

		return CRect(rc.left, rc.top, hotTrackStyle == xtpTaskPanelHighlightItem ? rc.right : min(rc.right, (rcText.right + rcInnerMargins.right)),
			rc.top + max(nImageHeight, rcText.Height()) + rcInnerMargins.top + rcInnerMargins.bottom);

	}
}

CRect CMyXTPTaskPanelPaintManager::GetItemInnerMargins(const CXTPTaskPanelGroupItem* pItem)
{
	return CRect(1, 1, 1, 1);
}