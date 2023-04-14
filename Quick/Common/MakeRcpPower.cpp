#include "stdafx.h"
#include "MakeRcpPower.h"

long CMakeRcpPower::m_nPowerCodeList[1000];
long CMakeRcpPower::m_nPowerCount = 0;


CMakeRcpPower::CMakeRcpPower(void)
{
	m_bHaveAllPowers = FALSE;
}

CMakeRcpPower::~CMakeRcpPower(void)
{
}

void CMakeRcpPower::GetPower()
{
	if(m_nPowerCount == 0)
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_rcp_power_code_all");
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 0);

		if(pRs.Execute(&pCmd))
		{
			int i = 0;
			for(i = 0; i < pRs.GetRecordCount(); i++)
			{
				long nCode;
				pRs.GetFieldValue("nCode", nCode);
				m_nPowerCodeList[i] = nCode;
				pRs.MoveNext();
			}
			m_nPowerCount = i;
		}
	}
}


void CMakeRcpPower::SetPowerChunk(CString strPower, long nRole, CString strBranchName, CString strID, CString strName, 
								  long nCompany, long nMNo, BOOL bPreventLogin)
{
	m_strBranchName = strBranchName;
	m_strID = strID;
	m_strName = strName;
	m_nCompany = nCompany;
	m_nMNo = nMNo;
	m_bPreventLogin = bPreventLogin;
	m_nRole = nRole;

	if(m_nRole == 0 && strPower == "")
	{
		for(int i = 0; i < m_nPowerCount; i++)
		{
			char buffer[10];
			strPower += ltoa(m_nPowerCodeList[i], buffer, 10);
			strPower += ",";
		}

		//m_bHaveAllPowers = TRUE;
	}

	ParseChunk(strPower);
}


void CMakeRcpPower::ParseChunk(CString strChunk)
{
	int idx = 0;

	for(int i = 0; i < strChunk.GetLength(); i++)
	{
		static long nCount = 0;

		if(strChunk.GetAt(i) == ',')
		{
			m_rpm[atol(strChunk.Mid(idx, i - idx))] = 1;
			idx = i + 1;
		}
	}
}

long CMakeRcpPower::GetPower(long nPowerType)
{
	return m_bHaveAllPowers || m_rpm[nPowerType];
}

long CMakeRcpPower::GetPowerPreview(long nPowerType)
{
	int nCount = 0, nHasCount = 0;

	for(long n = 0; n < m_nPowerCount; n++)
	{
		if(m_nPowerCodeList[n] >= nPowerType && m_nPowerCodeList[n] < nPowerType + 1000)
		{
			nCount++;
			if(m_rpm[m_nPowerCodeList[n]])
				nHasCount++;
		}
	}

	if(nCount == nHasCount || m_bHaveAllPowers)
		return POWER_ALL;
	else if(nHasCount == 0)
		return POWER_NONE;
	else 
		return POWER_PART;
}

long CMakeRcpPower::GetMonitorPower()
{
	return GetPowerPreview(MONITOR_POWER_CODE);
}

long CMakeRcpPower::GetRcpPower()
{
	return GetPowerPreview(RCP_POWER_CODE);
}

long CMakeRcpPower::GetReportCustomerPower()
{
	return GetPowerPreview(REPORT_CUSTOMER_POWER_CODE);
}

long CMakeRcpPower::GetReportRiderPower()
{
	return GetPowerPreview(REPORT_RIDER_POWER_CODE);
}

long CMakeRcpPower::GetStaffPower()
{
	return GetPowerPreview(STAFF_POWER_CODE);
}

long CMakeRcpPower::GetCustomerPower()
{
	return GetPowerPreview(CUSTOMER_POWER_CODE);
}

long CMakeRcpPower::GetIncomePower()
{
	return GetPowerPreview(INCOME_POWER_CODE);
}

long CMakeRcpPower::GetStatPower()
{
	return GetPowerPreview(STAT_POWER_CODE);
}

void CMakeRcpPower::ChangePower(long nPowerType, long nValue)
{
	for(long n = 0; n < m_nPowerCount; n++)
	{
		if(m_nPowerCodeList[n] >= nPowerType && m_nPowerCodeList[n] < nPowerType + 1000)
		{
			if(nValue == POWER_ALL)
				m_rpm[m_nPowerCodeList[n]] = 1;
			else if(nValue == POWER_NONE)
				m_rpm[m_nPowerCodeList[n]] = 0;
		}
	}
}

CString CMakeRcpPower::AndPower(CMakeRcpPower *power)
{
	CString strPower;
	char buffer[10];

	for(long n = 0; n < m_nPowerCount; n++)
	{
		if(power->GetPower(m_nPowerCodeList[n]) && GetPower(m_nPowerCodeList[n]))
		{
			strPower += ltoa(m_nPowerCodeList[n], buffer, 10);
			strPower += ",";
		}
		else
		{
			m_rpm[m_nPowerCodeList[n]] = 0;
		}
	}

	return strPower;
}




