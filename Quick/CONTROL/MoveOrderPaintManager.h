#pragma once

class CBranchStateRecordItem : public CXTPGridRecordItemText
{
public:
	CBranchStateRecordItem(CString strDummy):CXTPGridRecordItemText(strDummy)
	{
	}

public:
	CBranchInfo *pBi;
};

class CMoveOrderPaintManager : public CXTPGridThemeResource
{
public:
	CMoveOrderPaintManager();
	virtual ~CMoveOrderPaintManager(void);
public:
	int GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow);
	virtual void DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pMetrics);
};
