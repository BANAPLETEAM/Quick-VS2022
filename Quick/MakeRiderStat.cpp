
#include "stdafx.h"
#include "MakeRiderStat.h"


CMakeRiderStat::CMakeRiderStat(void)
{
	m_rsiSum.nAllocCount = 0;
	m_rsiSum.nPenaltyCount = 0;
	m_rsiSum.nMyCallCount = 0;
	m_rsiSum.nCrossCallCount = 0;
	m_rsiSum.nCharge = 0;
}

CMakeRiderStat::~CMakeRiderStat(void)
{
}

void CMakeRiderStat::SetMonthlyChunk(CString strDate, long nRiderCompany, long nRNo, 
					 CString strAllocChunk, CString strPenaltyChunk, CString strMyCallChunk, 
					 CString strCrossCallChunk, CString strChargeChunk,
					 CString strBranch, CString strRiderName)
{
	m_nRiderCompany = nRiderCompany;
	m_nRNo = nRNo;
	m_strBranch = strBranch;
	m_strRiderName = strRiderName;

	COleDateTime dtCur;
	dtCur.SetDateTime(atol(strDate.Left(4)), atol(strDate.Right(2)), 1, 0, 0, 0);
	long nMonth = atol(strDate.Right(2));
	
	long nAllocCount[32];
	long nPenaltyCount[32];
	long nMyCallCount[32];
	long nCrossCallCount[32];
	long nCharge[32];

	ParseChunk(&nAllocCount[0], strAllocChunk);
	ParseChunk(&nPenaltyCount[0], strPenaltyChunk);
	ParseChunk(&nMyCallCount[0], strMyCallChunk);
	ParseChunk(&nCrossCallCount[0], strCrossCallChunk);
	ParseChunk(&nCharge[0], strChargeChunk);

	for(int i = 1;  dtCur.GetMonth() == nMonth ; i++)
	{
		RIDER_STAT_INFO rsi;
		rsi.strDate = dtCur.Format("%Y%m%d");
		rsi.nAllocCount = nAllocCount[i];
		rsi.nPenaltyCount = nPenaltyCount[i];
		rsi.nMyCallCount = nMyCallCount[i];
		rsi.nCrossCallCount = nCrossCallCount[i];
		rsi.nCharge = nCharge[i];

		m_rsiSum.nAllocCount += rsi.nAllocCount;
		m_rsiSum.nPenaltyCount += rsi.nPenaltyCount;
		m_rsiSum.nMyCallCount += rsi.nMyCallCount;
		m_rsiSum.nCrossCallCount += rsi.nCrossCallCount;
		m_rsiSum.nCharge += rsi.nCharge;

		m_rsm.insert(RIDER_STAT_MAP::value_type(dtCur.Format("%Y%m%d"), rsi));
		dtCur = dtCur + COleDateTimeSpan(1, 0, 0, 0);
	}
}

void CMakeRiderStat::ParseChunk(long *pnData, CString strChunk)
{
	int idx = 0;

	memset(pnData, 0x00, sizeof(long) * 32);

	for(int i = 0; i < strChunk.GetLength(); i++)
	{
		static long nDay = 0;
		static long nCount = 0;

		if(strChunk.GetAt(i) == ':')
		{
			nDay = atol(strChunk.Mid(idx, i - idx));
			idx = i + 1;
		}
		else if(strChunk.GetAt(i) == ',')
		{
			nCount = atol(strChunk.Mid(idx, i - idx));
			idx = i + 1;

			if(nDay >= 1)
			{
				pnData[nDay] = nCount;
				nDay = -1;
				nCount = -1;
			}
		}
	}
}


long CMakeRiderStat::GetAllocCount(CString &strDate) 
{ 
	RIDER_STAT_MAP::iterator it;
	it = m_rsm.find(strDate);
	return (it == m_rsm.end()) ? 0 : it->second.nAllocCount;
}

long CMakeRiderStat::GetPenaltyCount(CString &strDate) 
{ 
	RIDER_STAT_MAP::iterator it;
	it = m_rsm.find(strDate);
	return (it == m_rsm.end()) ? 0 : it->second.nPenaltyCount;
}

long CMakeRiderStat::GetMyCallCount(CString &strDate) 
{ 
	RIDER_STAT_MAP::iterator it;
	it = m_rsm.find(strDate);
	return (it == m_rsm.end()) ? 0 : it->second.nMyCallCount;
}

long CMakeRiderStat::GetCrossCallCount(CString &strDate) 
{ 
	RIDER_STAT_MAP::iterator it;
	it = m_rsm.find(strDate);
	return (it == m_rsm.end()) ? 0 : it->second.nCrossCallCount;	
}

long CMakeRiderStat::GetCharge(CString &strDate) 
{ 
	RIDER_STAT_MAP::iterator it;
	it = m_rsm.find(strDate);
	return (it == m_rsm.end()) ? 0 : it->second.nCharge;	
}






