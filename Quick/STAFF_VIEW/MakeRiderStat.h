#pragma once




typedef struct{
	CString strDate;
	long nAllocCount;
	long nPenaltyCount;
	long nMyCallCount;
	long nCrossCallCount;
	long nCharge;
} RIDER_STAT_INFO;

typedef map<CString, RIDER_STAT_INFO> RIDER_STAT_MAP;

class CMakeRiderStat
{
public:
	CMakeRiderStat(void);
	~CMakeRiderStat(void);


protected:
	RIDER_STAT_MAP m_rsm;
	RIDER_STAT_INFO m_rsiSum;
	long m_nRiderCompany;
	long m_nRNo;
	CString m_strBranch;
	CString m_strRiderName;

public:
	void SetMonthlyChunk(CString strDate, long nRiderCompany, long nRNo, 
			CString strAllocChunk, CString strPenaltyChunk, CString strMyCallChunk, 
			CString strCrossCallChunk, CString strChargeChunk,
			CString strBranch = "", CString strRiderName = "");

	void ParseChunk(long *pnData, CString strChunk);

	long GetRiderCompany() { return m_nRiderCompany;}
	long GetRNo() { return m_nRNo;}
	CString GetBranchName() { return m_strBranch; }
	CString GetRiderName() { return m_strRiderName; }

	long GetAllocCount(CString &strDate);
	long GetPenaltyCount(CString &strDate); 
	long GetMyCallCount(CString &strDate); 
	long GetCrossCallCount(CString &strDate);
	long GetCharge(CString &strDate); 

	long GetAllocCountSum() { return m_rsiSum.nAllocCount;}
	long GetPenaltyCountSum(){ return m_rsiSum.nPenaltyCount;} 
	long GetMyCallCountSum(){ return m_rsiSum.nMyCallCount;} 
	long GetCrossCallCountSum(){ return m_rsiSum.nCrossCallCount;}
	long GetChargeSum(){ return m_rsiSum.nCharge;} 

};

