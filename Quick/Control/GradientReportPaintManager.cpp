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

void CGradientReportPaintManager::DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics)
{
	COLORREF crBack = pMetrics->clrBackground;

//	if(!pDrawArgs->pRow->IsSelected())
	LF->FillGradient(pDrawArgs->pDC, crBack, pDrawArgs->rcItem, m_nScale);
	CXTPGridPaintManager::DrawItemCaption(pDrawArgs, pMetrics);
}
