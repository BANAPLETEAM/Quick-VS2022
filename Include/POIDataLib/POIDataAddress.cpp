#include "StdAfx.h"
#include "POIDataAddress.h"
#include "POIDataNew.h"
#include "MkRecordset.h"
#include "MkCommand.h"
#include "MkDatabase.h"


CPOIDataAddress::CPOIDataAddress(void)
{
	m_pPOIData = NULL;
	m_pDB = NULL;
}

CPOIDataAddress::CPOIDataAddress(CMkDatabase *pDB, CPOIDataNew *pData)
{
	m_pDB = pDB;
	m_pPOIData = pData;
}

CPOIDataAddress::~CPOIDataAddress(void)
{
}

void CPOIDataAddress::SetAddressText(CString strText)
{
	m_strJibun1.Empty();
	m_strJibun2.Empty();
	m_bSan = FALSE;
	m_strKeywordIncSpace = strText;
	m_strKeyword = strText;
	m_strKeyword.Remove(' ');
}

int CPOIDataAddress::GetAddressList(SEARCH_POI_VEC &vecAddress, BOOL bCheckValidate)
{
	SEARCH_POI_VEC v;
	SEARCH_POI_VEC::iterator it;
	SEARCH_POI_MAP m;
	CString strJibun;

	m_pPOIData->SearchDong(m_strKeyword, v, m);	

	//if(v.size() > 0)
	if(!v.empty())
		if(!bCheckValidate || CheckJibunSearch(m_strKeywordIncSpace, TRUE))
			if(ResolveJibunString(m_strKeywordIncSpace, m_strJibun1, m_strJibun2, m_bSan))
				return QueryJibun(v, vecAddress);

	return 0;
}

BOOL CPOIDataAddress::ResolveJibunString(CString strSrc, CString &strJibun1, CString &strJibun2, BOOL &bSan)
{
	BOOL bSecondPart = FALSE;
	long nLen =  min(strSrc.GetLength(), 20);

	for(int i = 0; i < nLen; i++)
	{
		BYTE cWord = strSrc.GetAt(i);

		if(isdigit(cWord))
		{
			if(strJibun1.GetLength() == 0 && i > 2)
			{
				CString strSan = strSrc.Mid(i - 2, 2);
				if(strSan == "산")
					bSan = TRUE;
			}

			if(bSecondPart)
				strJibun2 += cWord;
			else 
				strJibun1 += cWord;
		}
		else if(cWord == '-')
		{
			if(strJibun1.GetLength() > 0)
				bSecondPart = TRUE;
		}
		else if(strJibun1.GetLength() > 0)
		{
			if(i < strSrc.GetLength() - 1)
			{
				CString strTail = strSrc.Mid(i, 2);
				if(strTail == "동" ||
					strTail == "호" ||
					strTail == "층" ||
					strTail == "가" ||
					strTail == "차")
				{
					strJibun1.Empty();
					strJibun2.Empty();
					bSan = FALSE;
					bSecondPart = FALSE;
					continue;
				}
			}

			return TRUE;
		}
	}

	if(strJibun1.GetLength() > 0)
		return TRUE;

	strJibun2.Empty();
	return FALSE;
}

BOOL CPOIDataAddress::CheckJibunSearch(CString strData, BOOL bExceptResolve)
{
	CString strIncSpace = strData;
	strData.Remove(' ');

	if((strData.Find("번지") > 0 || strData.Find("-") >= 0) &&
		strData.GetLength() > 4)
	{
		CString strDigit, strPreDigit;
		for(int i = 4; i < strData.GetLength(); i++)
		{
			char szTemp = strData.GetAt(i);
			if(szTemp >= '0' && szTemp <= '9')
				strDigit += szTemp;
			else if(szTemp == '-')
				strDigit += szTemp;
			else 
			{
				if(strDigit.GetLength() > 0)
					strPreDigit = strDigit;
				strDigit = "";
			}
		}

		if(strPreDigit.GetLength() > strDigit.GetLength())
			strDigit = strPreDigit;

		if(strDigit.GetLength() > 1)
		{
			int nPos = strData.Find(strDigit);
			CString strHead = strData.Mid(nPos - 2, 2);
			if(strHead == "산")
				strHead = strData.Mid(nPos - 4, 2);

			if(strHead == "동" || strHead == "읍" || strHead == "면" || strHead == "리" || strHead == "가")
			{
				BOOL bSan;
				CString strJibun1, strJibun2;

				if(bExceptResolve || ResolveJibunString(strIncSpace, strJibun1, strJibun2, bSan))
					return TRUE;
			}
		}
	}
	return FALSE;
}

int CPOIDataAddress::QueryJibun(SEARCH_POI_VEC &v, SEARCH_POI_VEC &vecAddress)
{
	SEARCH_POI_VEC::iterator it;
	CMkRecordset rs(m_pDB);
	CMkCommand cmd(m_pDB, "select_address_list");

	it = v.begin();
	for(int n = 0; n < 5; n++)
	{
		if(it != v.end())
		{
			cmd.AddParameter((int)it->second.pPOI->GetDongID());
			it++;
		}
		else
			cmd.AddParameter(0);
	}

	cmd.AddParameter(m_bSan);
	cmd.AddParameter(atol(m_strJibun1));
	cmd.AddParameter(atol(m_strJibun2));

	if(rs.Execute(&cmd))
	{
		while(!rs.IsEOF())
		{
			long nDongID, nJibun1, nJibun2;
			BOOL bSan;
			CSearchPOI poi;

			rs.GetFieldValue("nDongID", nDongID);
			rs.GetFieldValue("bSan", bSan);
			rs.GetFieldValue("nJibun1", nJibun1);
			rs.GetFieldValue("nJibun2", nJibun2);
			rs.GetFieldValue("nPosX", poi.nNewPosX);
			rs.GetFieldValue("nPosY", poi.nNewPosY);

			poi.pPOI = m_pPOIData->GetDongPOI(nDongID, 0, 0); 

			if(!poi.pPOI)
			{
				rs.MoveNext();
				continue;
			}

			poi.bAddressSearch = TRUE;
			strcpy(poi.szKeyword, MakeJibunString(bSan, nJibun1, nJibun2));

			long nDistance = 3000;
			poi.pNearPOI = m_pPOIData->GetNearMainPOI(poi.nNewPosX,	poi.nNewPosY, nDistance);
			poi.nNearDistance = nDistance;

			if(!poi.pNearPOI)
			{
				poi.pNearPOI = m_pPOIData->GetDongPOI(nDongID);
				poi.nNearDistance = poi.pNearPOI->GetDistanceMeter(poi.nNewPosX, poi.nNewPosY);
			} 

			poi.nDataPos = 0xFFFF;

			vecAddress.push_back(make_pair(0, poi));
			//g_bana_log->Print("%d, %d, %d-%d, %d, %d, %s\n", nDongID, bSan, nJibun1, nJibun2, poi.nNewPosX, poi.nNewPosY, poi.pNearPOI->GetFullName());
			//g_bana_log->Print("%x %d, %s\n", poi.pNearPOI, poi.pNearPOI->GetID(), poi.pNearPOI->GetFullName());

			rs.MoveNext();
		}

		return rs.GetRecordCount();
	}

	return 0;
}

CString CPOIDataAddress::MakeJibunString(BOOL bSan, int nJibun1, int nJibun2)
{
	CString strFormat;
	if(nJibun2 == 0)
		strFormat.Format("%s %d번지", bSan ? "산" : "", nJibun1);
	else
		strFormat.Format("%s %d-%d", bSan ? "산" : "", nJibun1, nJibun2);
	return strFormat;
}


BOOL CPOIDataAddress::GetNearAddress(CMkDatabase *pDb, long nPosX, long nPosY, long &nDongID, CString &strAddress)
{
	CMkRecordset rs(pDb);
	CMkCommand cmd(pDb, "select_near_address");
	cmd.AddParameter(nPosX);
	cmd.AddParameter(nPosY);
	if(rs.Execute(&cmd))
	{
		if(rs.GetRecordCount() > 0)
		{
			rs.GetFieldValue("nDongID", nDongID);
			rs.GetFieldValue("sAddress", strAddress);
			return TRUE;
		}
	}
	return FALSE;
}
