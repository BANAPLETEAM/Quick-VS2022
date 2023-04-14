#pragma once



class CMyXTPTaskPanelPaintManager :
	public CXTPTaskPanelPaintManager
{
public:
	CMyXTPTaskPanelPaintManager(void);
	virtual ~CMyXTPTaskPanelPaintManager(void);
	virtual void DrawItemCaption(CDC* pDC, CXTPTaskPanelItem* pItem, CRect rcText, UINT nFormat);
	virtual CRect DrawGroupItem(CDC* pDC, CXTPTaskPanelGroupItem* pItem, CRect rc, BOOL bDraw);
	virtual CRect GetItemInnerMargins(const CXTPTaskPanelGroupItem* pItem);

protected:
	CRect DrawGroupItemImageWithText2(CDC* pDC, CXTPTaskPanelGroupItem* pItem, CRect rc, BOOL bDraw);
};
