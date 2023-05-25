#pragma once


#include "myreportpaintmanager.h"

typedef struct{
	long nCharge;
	long nTotalCount;
	long nCancelCount;
	long nTotalCountCarType0;
	long nCancelCountCarType0;
	long nTotalCountCarType2;
	long nCancelCountCarType2;
	long nTotalCountCarType4;
	long nCancelCountCarType4;
	long nTotalCountCarType5;
	long nCancelCountCarType5;
} ST_PROPER_CHARGE;

class CProperChargeReportRecord : public CXTPGridRecord
{
public:
	CProperChargeReportRecord(ST_PROPER_CHARGE *st)
	{
		m_st = st;
		AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(m_st->nCharge)));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
	}	

public:
	ST_PROPER_CHARGE *m_st;
};

using namespace std;



class CProperChargePaintManager :
	public CMyReportPaintManager
{
public:
	CProperChargePaintManager(void);
	virtual ~CProperChargePaintManager(void);

	virtual void DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pMetrics);
	virtual int GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow);

	void SetHilightCol(int nCol) { m_nHilightCol = nCol; }

public:
	long m_nHilightCol;
	long m_nCarType;

	CFont *m_pfntLarge;
	CFont *m_pfntSmall;
	CFont *m_pfntNormal;
};
