#pragma once


typedef map<long, long> RCP_POWER_MAP;



extern long nPowerCodeList[1000];
extern long nPowerCount;


#define	MONITOR_POWER_CODE	1000
#define	RCP_POWER_CODE		2000
#define	REPORT_CUSTOMER_POWER_CODE	3000
#define	REPORT_RIDER_POWER_CODE	4000
#define	STAFF_POWER_CODE	5000
#define	CUSTOMER_POWER_CODE	6000
#define	INCOME_POWER_CODE	7000
#define	STAT_POWER_CODE		8000



enum { POWER_NONE = 0, 
POWER_PART = 1, 
POWER_ALL = 2};

class CMakeRcpPower
{
public:
	CMakeRcpPower(void);
	~CMakeRcpPower(void);

protected:
	RCP_POWER_MAP m_rpm;
	CString m_strBranchName;
	CString m_strID;
	CString m_strName;
	long m_nCompany;
	long m_nMNo;
	long m_nRole;
	BOOL m_bPreventLogin;

	BOOL m_bHaveAllPowers;

	void ParseChunk(CString strChunk);
	long GetPowerPreview(long nPowerType);


public:
	static long m_nPowerCodeList[1000];
	static long m_nPowerCount;

	static void GetPower();
	void SetPowerChunk(CString strPower, long nRole, 
		CString strBranchName = "", CString strID = "", 
		CString strName = "", long nCompany = 0, long nMNo = 0, 
		BOOL bPreventLogin = FALSE);

	CString GetBranchName() { return m_strBranchName;}
	CString GetID() { return m_strID;}
	CString GetName() { return m_strName;}
	long GetCompany() { return m_nCompany;}
	long GetMNo() { return m_nMNo;}
	BOOL GetPreventLogin() { return m_bPreventLogin;}

	long GetMonitorPower();
	long GetRcpPower();
	long GetReportCustomerPower();
	long GetReportRiderPower();
	long GetStaffPower();
	long GetCustomerPower();
	long GetIncomePower();
	long GetStatPower();

	long GetPower(long nPowerType);
	void ChangePower(long nPowertype, long nValue);

	CString AndPower(CMakeRcpPower *power);


};




