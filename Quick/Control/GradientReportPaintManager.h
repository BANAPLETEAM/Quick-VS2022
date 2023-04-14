#pragma once

class CGradientReportPaintManager :
	public CXTPGridPaintManager
{
public:
	CGradientReportPaintManager(long nGradientScale = 20);
	virtual ~CGradientReportPaintManager(void);
	virtual void DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics);

protected:
	long m_nScale;
};
