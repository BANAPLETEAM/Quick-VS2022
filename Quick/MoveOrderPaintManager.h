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

class CMoveOrderPaintManager : public CXTPGridPaintManager
{
public:
	CMoveOrderPaintManager();
	virtual ~CMoveOrderPaintManager(void);
public:
	int GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow);
	virtual void DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics);
};
