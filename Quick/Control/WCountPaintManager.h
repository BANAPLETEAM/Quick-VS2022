#pragma once

#include "atlImage.h"

class CWcountRecordItem : public CXTPGridRecordItemText
{
public:
	CWcountRecordItem(CString strDummy):CXTPGridRecordItemText(strDummy)
	{
	}
	
public:
	ST_WCOUNT m_st;
};


class CWCountPaintManager : public CXTPGridPaintManager
{
public:
	CWCountPaintManager();
	virtual ~CWCountPaintManager(void);
public:
	virtual void DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics);

public:
	BOOL m_bLoadRabkImage;
	void LoadRankImage(CDC *pDC);
	void DrawCountInfo(long nStartPos, CDC *pDC, CRect rc, long nRank);
	void DrawRankInfo( CDC *pDC, CRect rc, long nRank, long nPreRank);
	CImageList m_imgCount;
	CBitmap m_imgUp;
	CBitmap m_imgDown;
	CBitmap m_imgStay;
	CBitmap m_imgNew;
};
