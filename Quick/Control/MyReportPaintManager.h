#pragma once


class CMyReportPaintManager : public CXTPGridThemeResource
{
	friend class CXTPGridControl;

public:
	CMyReportPaintManager();
	virtual ~CMyReportPaintManager();

public:
	BOOL m_bApplyHeight;
	long m_nHeight;

	void SetRowHeight(BOOL bApplyHeight, long nHeight);

	int GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow);
	virtual void DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pMetrics);

	void DrawTextLine(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, CString strText,
		CRect rcItem, int nFlag, int& nCharCounter, int& nHyperlikCounter);

	int DrawString(int* pnCurrDrawPos, CDC* pDC, CString strDraw, CRect rcDraw, UINT nFormat, UINT nAlign = DT_LEFT);

	int DrawLink(int* pnCurrDrawPos, XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, CXTPGridHyperlink* pHyperlink,
		CString strText, CRect rcLink, int nFlag);

};
