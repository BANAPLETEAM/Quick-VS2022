#pragma once

class CGradientReportPaintManager :
	public CXTPGridThemeResource
{
public:
	CGradientReportPaintManager(long nGradientScale = 20);
	virtual ~CGradientReportPaintManager(void);
	virtual void DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pMetrics);

protected:
	long m_nScale;
};
