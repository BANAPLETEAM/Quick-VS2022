#include "StdAfx.h"
#include "GradientReportPaintManager.h"
#include "LogiFunc.h"

CGradientReportPaintManager::CGradientReportPaintManager(long nGradientScale)
{
	m_nScale = nGradientScale;
}

CGradientReportPaintManager::~CGradientReportPaintManager(void)
{
}

void CGradientReportPaintManager::DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pMetrics)
{
	COLORREF crBack = pMetrics->clrBackground;

//	if(!pDrawArgs->pRow->IsSelected())
	LF->FillGradient(pDrawArgs->pDC, crBack, pDrawArgs->rcItem, m_nScale);
	CXTPGridPaintManager::DrawItemCaption(pDrawArgs, pMetrics);
}
