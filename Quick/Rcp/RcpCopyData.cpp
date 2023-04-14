#include "StdAfx.h"
#include "resource.h"
#include "RcpCopyData.h"
#include "MkMessenger.h"

#define GLOBAL_STACK_SIZE 50000
#define COPY_DELIMETER	"%$"

CRcpCopyData::CRcpCopyData(void)
{
	m_pGlobalStack = new CHAR[GLOBAL_STACK_SIZE];
}

CRcpCopyData::~CRcpCopyData(void)
{
	if(m_pGlobalStack)
		delete m_pGlobalStack;
}


void CRcpCopyData::InsertData(CString strKey, CString strData)
{
	m_mapRcpCopyData[strKey] = strData;
}

void CRcpCopyData::InsertData(CString strKey, int nData)
{
	char buffer[30];
	m_mapRcpCopyData[strKey] = ltoa(nData, buffer, 10);
}

void CRcpCopyData::InsertData(CString strKey, UINT nData)
{
	char buffer[30];
	m_mapRcpCopyData[strKey] = ltoa(nData, buffer, 10);
}

void CRcpCopyData::InsertData(CString strKey, COleDateTime dtDate)
{
	if(dtDate.GetStatus() == COleDateTime::valid)
		m_mapRcpCopyData[strKey] = dtDate.Format("%Y%m%d%H%M%S");
	else 
		m_mapRcpCopyData[strKey] = "";
}

void CRcpCopyData::InsertData(CString strKey, double fData)
{
	CString strData;
	strData.Format("%f", fData);
	m_mapRcpCopyData[strKey] = strData;
}

void CRcpCopyData::InsertData(CString strKey, float fData)
{
	CString strData;
	strData.Format("%f", fData);
	m_mapRcpCopyData[strKey] = strData;
}


char* CRcpCopyData::MakePacket()
{
	if(m_mapRcpCopyData.size() == 0)
		return NULL;

	ZeroMemory(m_pGlobalStack, GLOBAL_STACK_SIZE);

	STRCAT2(COPY_DELIMETER, m_pGlobalStack, "$$%RCPCOPYDATA", VL_END);
	STRCAT2(COPY_DELIMETER, m_pGlobalStack, "VERSION", LF->GetMyFileVersion(), VL_END);

	RCP_COPY_DATA_MAP::iterator it;
	for(it = m_mapRcpCopyData.begin(); it != m_mapRcpCopyData.end(); it++)
	{
		STRCAT2(COPY_DELIMETER, m_pGlobalStack, (LPSTR)(LPCTSTR)it->first, (LPSTR)(LPCTSTR)it->second, VL_END);
	}

	return m_pGlobalStack;
}

BOOL CRcpCopyData::PacketToMap(char *szPacket)
{
	int nPos = 0;
	char szKey[512], szData[8192], szHead[100];
	m_mapRcpCopyData.clear();

	nPos = STRTOK2(COPY_DELIMETER, szPacket, nPos, szHead, VL_END);

	while(nPos > 0)
	{
		nPos = STRTOK2(COPY_DELIMETER, szPacket, nPos, szKey, szData, VL_END);
		if(nPos > 0)
			m_mapRcpCopyData[szKey] = szData;
	}
	
	return (m_mapRcpCopyData.size() > 0);
}



CString CRcpCopyData::GetValue(CString strKey, CString &strData)
{
	if(m_mapRcpCopyData.end() != m_mapRcpCopyData.find(strKey))
		strData = m_mapRcpCopyData[strKey];
	else
		strData = "";

	return strData;
}

int CRcpCopyData::GetValue(CString strKey, int &nData)
{
	if(m_mapRcpCopyData.end() != m_mapRcpCopyData.find(strKey))
		nData = atol(m_mapRcpCopyData[strKey]);
	else
		nData = 0;

	return nData;
}

long CRcpCopyData::GetValue(CString strKey, long &nData)
{
	if(m_mapRcpCopyData.end() != m_mapRcpCopyData.find(strKey))
		nData = atol(m_mapRcpCopyData[strKey]);
	else
		nData = 0;

	return nData;
}

COleDateTime CRcpCopyData::GetValue(CString strKey, COleDateTime &dtDate)
{
	if(m_mapRcpCopyData.end() != m_mapRcpCopyData.find(strKey))
	{
		CString strData = m_mapRcpCopyData[strKey];
		if(strData.IsEmpty())
			dtDate.SetStatus(COleDateTime::null);
		else
			dtDate.SetDateTime(atol(strData.Left(4)), atol(strData.Mid(4, 2)), atol(strData.Mid(6, 2)), 
						atol(strData.Mid(8, 2)), atol(strData.Mid(10, 2)), atol(strData.Mid(12, 2)));
	}
	else
		dtDate.SetStatus(COleDateTime::null);

	return dtDate;
}

double CRcpCopyData::GetValue(CString strKey, double &fData)
{
	if(m_mapRcpCopyData.end() != m_mapRcpCopyData.find(strKey))
	{
		fData = atof(m_mapRcpCopyData[strKey]);
	}
	else
		fData = 0.0;

	return fData;
}

float CRcpCopyData::GetValue(CString strKey, float &fData)
{
	if(m_mapRcpCopyData.end() != m_mapRcpCopyData.find(strKey))
	{
		fData = atof(m_mapRcpCopyData[strKey]);
	}
	else
		fData = 0.0;

	return fData;
}
