#pragma once

#include "myreportpaintmanager.h"




class CRGSReportRecord : public CXTPGridRecord
{
public:
	CRGSReportRecord(long nCompany, long nRNo, CString strName)
	{
		m_nCompany = nCompany;
		m_nRNo = nRNo;

		AddItem(new CXTPGridRecordItemNumber(nRNo));
		AddItem(new CXTPGridRecordItemText(strName));
		AddItem(new CXTPGridRecordItemText(""));
	}	

public:
	long m_nCompany;
	long m_nRNo;
};



using namespace std;

typedef struct {
	COleDateTime dtMin;
	long nCount;
} SIGNAL_DATA;

typedef vector<SIGNAL_DATA> SIGNAL_VECTOR;
typedef map<pair<long, long>, SIGNAL_VECTOR> SIGNAL_MAP;



class CRGSPaintManager :
	public CMyReportPaintManager
{
public:
	CRGSPaintManager(void);
	virtual ~CRGSPaintManager(void);

	virtual void DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics);


public:
	SIGNAL_MAP m_mapSignal;

};
