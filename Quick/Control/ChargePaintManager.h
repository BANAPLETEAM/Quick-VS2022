#pragma once

#define ROW_COL_SIZE 25

class CChargePaintManager : public CXTPGridThemeResource
{
public:

	CChargePaintManager(void);
	~CChargePaintManager(void);

	long m_nFirstRowHeight;

	void SetFirstRowHeight(long nFirstRowHeight) {m_nFirstRowHeight = nFirstRowHeight;}

	int GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow);

	virtual void DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pMetrics);
};

