
#pragma once
#include "MyReportPaintManager.h"

class CRiderPaintManager : public CMyReportPaintManager
{
public:
	int CRiderPaintManager::GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow)
	{
		return m_nRowHeight;
	}

	void DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pMetrics);
};

class CGroupPaintManager : public CMyReportPaintManager
{
public:
	int GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow);
	void DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pMetrics);
};

class CGroupPaintManager24 : public CMyReportPaintManager
{
public:
	int GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow);
	virtual void DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs,	XTP_GRIDRECORDITEM_METRICS* pMetrics);

};

class CConsignDrawManager2 : public CMyReportPaintManager
{
public:
	virtual void DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pMetrics);
	virtual int GetRowHeight(CDC* pDC, CXTPGridRow* pRow);
};

class CEmptyPaintManager : public CMyReportPaintManager
{
public:
	virtual void DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pMetrics);
};

class CPaintManager : public CMyReportPaintManager
{
	int GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow);
	virtual void DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pMetrics);
};

class CReportForm14PaintManager : public CMyReportPaintManager
{
	int GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow);
};