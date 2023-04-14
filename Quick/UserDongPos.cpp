#include "stdafx.h"
#include "resource.h"
#include "UserDongPos.h"

#define DONG 1
#define GU	 2
#define SI	 3


CUserDongPos::CUserDongPos(void)
{
}

CUserDongPos::~CUserDongPos(void)
{

	COMPANY_USER_DONGPOS_MAP::iterator it;
	if(m_mapCoInUserDongPos.size() > 0)
	{
		for(it = m_mapCoInUserDongPos.begin(); it != m_mapCoInUserDongPos.end(); ++it)
			Clear(it->first, TRUE);		
	}
	m_mapCoInUserDongPos.clear();

	COMPANY_USER_DONGPOS_MATCH_MAP::iterator it2;
	if(m_mapCoInUserDongPosMatch.size() > 0)
	{
		for(it2 = m_mapCoInUserDongPosMatch.begin(); it2 != m_mapCoInUserDongPosMatch.end(); ++it2)
			ClearMatch(it2->first);		
	}
	m_mapCoInUserDongPosMatch.clear();


}

void CUserDongPos::Clear(long nCompany, BOOL bPOIInfoDataDelete)
{

	USER_DONGPOS_MAP *pMapInDongPos;
	USER_DONGPOS_MAP::iterator it;



	pMapInDongPos = m_mapCoInUserDongPos[nCompany];

	if(bPOIInfoDataDelete)
	{
		if(pMapInDongPos != NULL)
		{
			if(pMapInDongPos->size() > 0)
			{
				for(it = pMapInDongPos->begin(); it != pMapInDongPos->end(); ++it)
				{
					if(it->second)
						delete it->second;
				}

			}
		}
	}



	pMapInDongPos->clear();	
	if(pMapInDongPos)
		delete pMapInDongPos;



}

void CUserDongPos::ClearMatch(long nCompany)
{
	USER_DONGPOS_MATCH_MAP *pMapInDongPosMatch;
	USER_DONGPOS_MATCH_MAP::iterator itMatch;

	pMapInDongPosMatch = m_mapCoInUserDongPosMatch[nCompany];

	pMapInDongPosMatch->clear();
	if(pMapInDongPosMatch)
		delete pMapInDongPosMatch;

}


USER_DONGPOS_MAP * CUserDongPos::GetUserDongPos(long nCompany)
{
	return m_mapCoInUserDongPos[nCompany];

}

USER_DONGPOS_MATCH_MAP * CUserDongPos::GetUserDongPosMatch(long nCompany)
{
	return m_mapCoInUserDongPosMatch[nCompany];

}

void CUserDongPos::GetParentDepthInfoChild(CPOIInfo *pPOIInfo, BOOL bStart)
{	

	if(pPOIInfo != NULL)
	{
		if(bStart)
			m_DIStart.Insert(pPOIInfo->nDongID,pPOIInfo->nDongDepth);
		else
			m_DIDest.Insert(pPOIInfo->nDongID,pPOIInfo->nDongDepth);

		if(pPOIInfo->pParent)
			GetParentDepthInfoChild(pPOIInfo->pParent, bStart);	
	}	
}

long CUserDongPos::GetDongIDMatch(long nCompany, long nDongID)
{

	if( m_mapCoInUserDongPosMatch[nCompany])
	{
		USER_DONGPOS_MATCH_MAP *pMatchMap = m_mapCoInUserDongPosMatch[nCompany];
		USER_DONGPOS_MATCH_MAP::iterator it;
		it = pMatchMap->find(nDongID);
		if(it != pMatchMap->end())
		{
			return it->second;
		}

	}
	return -1000;

}


void CUserDongPos::GetParentDepthInfo(long nCompany, long nStartID, long nDestID, CString &sStartList, CString &sDestList)
{	

	if(m_mapCoInUserDongPos[nCompany])
	{



		m_DIStart.Clear();
		m_DIDest.Clear();

		USER_DONGPOS_MAP *pDongPosMap;
		USER_DONGPOS_MAP::iterator itStart, itDest;
		char buffer[10];

		pDongPosMap = m_mapCoInUserDongPos[nCompany];


		long nUserDongPosStartID = GetDongIDMatch(nCompany,nStartID);

		itStart = pDongPosMap->find(nUserDongPosStartID);
		if(itStart != pDongPosMap->end())
		{

			m_DIStart.Insert( itStart->second->nDongID, itStart->second->nDongDepth);
			if(itStart->second->pParent != NULL)
				GetParentDepthInfoChild(itStart->second->pParent, TRUE);	
		}


		long nUserDongPosDestID = GetDongIDMatch(nCompany,nDestID);
		itDest = pDongPosMap->find(nUserDongPosDestID);
		if(itDest != pDongPosMap->end())
		{

			m_DIDest.Insert(itDest->second->nDongID,itDest->second->nDongDepth);							

			if(itDest->second->pParent != NULL)
				GetParentDepthInfoChild(itDest->second->pParent, FALSE);

		}

		int  nStartCount = 0, nDestCount = 0, nDepthStartCount = 0, nDepthDestCount = 0;
		nDepthStartCount = (m_DIStart.GetDepthCount() <= 0) ? 0 : m_DIStart.GetDepthCount();
		nDepthDestCount = (m_DIDest.GetDepthCount() <= 0) ? 0 : m_DIDest.GetDepthCount();

		sStartList = sDestList = "";
		if(nDepthDestCount == 0 || nDepthStartCount == 0)
		{
			sStartList = ltoa(nStartID, buffer,10);
			sDestList = ltoa(nDestID, buffer, 10)	;
			return;
		}

		for(int i = 0; i < nDepthStartCount; i++)
		{
			if(i == 0 )
				sStartList += m_DIStart.GetDeptDongID_str(i);
			else
				sStartList += "," + m_DIStart.GetDeptDongID_str(i);
		}
		for(int i = 0; i < nDepthDestCount; i++)
		{
			if(i == 0 )
				sDestList += m_DIDest.GetDeptDongID_str(i);
			else
				sDestList += "," + m_DIDest.GetDeptDongID_str(i);
		}

		/*
		m_DeptInfoValue.Clear();
		for(nStartCount = 0; nStartCount < nDepthStartCount; nStartCount++ )
		{
		for(nDestCount = 0; nDestCount < nDepthDestCount; nDestCount++)
		{


		if(m_DIStart.GetDeptDongGuSi(nStartCount) == DONG &&
		m_DIDest.GetDeptDongGuSi(nDestCount) == DONG)  // 출발,도착 두개다 동이라면
		{
		m_DeptInfoValue.insert(m_DIStart.GetDeptDongID(nStartCount), m_DIDest.GetDeptDongID(nDestCount));
		}

		//	m_DeptInfoStart.sStart[nDepthStartCount] = ltoa(m_DeptInfoStart.GetDeptDongID(nDepthStartCount), buffer,10);


		//	nDepthStartCount++; 
		//	nDepthDestCount++;
		//}
		//else if(m_DeptInfoStart.GetDeptDongGuSi(nDepthStartCount) == DONG &&
		//	m_DeptInfoDest.GetDeptDongGuSi(nDepthDestCount) == GU	)
		//{

		//}
		//else if(m_DeptInfoStart.GetDeptDongGuSi(nDepthStartCount) == GU &&
		//	m_DeptInfoDest.GetDeptDongGuSi(nDepthDestCount) == DONG	)
		//{

		//}


		}

		}
		*/

	}

}

/*
void CUserDongPos::InsertData(long nCompany)
{
this->m_MileageMap[nCompany];//->nCompany = nCompany;
MILEAGE_INFORMATION *Info = new MILEAGE_INFORMATION;
Info->nCompany = nCompany;
Info->nMileageSettingCount = 0;
Info->nMileageSpan = 0;
//i
//info->nClass = 0;
for(int j=0; j < 4; j++)
{
for(int i = 0; i < 30; i++)
{
Info->nAmount[j][i] = 0;
Info->nEndAmount[j][i] = 0;	
Info->nStartAmount[j][i] = 0;
}
}
m_MileageMap[nCompany] = Info;



}
*/

//
//void CUserDongPos::GetStartDestTree(nCompany,nStartDongID,nDestDongID, &sStartDongList,&sDestDongList)
//{
//
//	USER_DONGPOS_MAP *pMapInDongPos = m_mapCoInDongPos[nCompany];
//	if(pMapInDongPos)
//	{
//		
//	}
//	
//	
//}

void CUserDongPos::FillData(long nCompany)
{


	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "select_charge_user_define_dong3");	 
	pCmd2.AddParameter(nCompany);		
	pCmd2.AddParameter(TRUE);	

	long nDongID = 0, nDepth = 0,  i = 0, nPre1Dept = 0, nPOIID = 0, nID = 0, nDongDepth = 0;	
	CString sDong, sAllName;
	BOOL bFactPOI;
	if(pRs2.Execute(&pCmd2))
	{
		USER_DONGPOS_MAP *pMapInUserDongPos = new USER_DONGPOS_MAP;
		USER_DONGPOS_MATCH_MAP *pMatchMap = new USER_DONGPOS_MATCH_MAP;
		//DONGPOS_MAP *pMapInDongPos =  new DONGPOS_MAP;
		CPOIInfo *pPReAll[20];
		CPOIInfo *pPOI, *pOldPOI;

		int nPreDepth = 0;
		while(!pRs2.IsEOF())
		{	

			pRs2.GetFieldValue("nID", nID);		
			pRs2.GetFieldValue("nDepth", nDepth);			
			pRs2.GetFieldValue("sDong", sDong);
			pRs2.GetFieldValue("sAllName", sAllName);
			pRs2.GetFieldValue("bFactPOI", bFactPOI);
			pRs2.GetFieldValue("nDongID", nDongID);
			pRs2.GetFieldValue("nDongDepth", nDongDepth);

			pPOI = new CPOIInfo;
			pOldPOI = pPOI;

			pPOI->nPOIID = nID;			
			pPOI->nDepth = nDepth;
			pPOI->nDongID = nDongID;
			pPOI->sAllName = sAllName;
			pPOI->sName = sDong;
			pPOI->bFactPOI = bFactPOI;
			pPOI->nDongDepth = nDongDepth;

			if(sAllName.Compare("삼성동") == 0)
			{
				int i = 0;
			}
			if(nDepth == 1)
			{
				pPOI->pParent = NULL;				
				pPReAll[1] = pPOI;								
			}
			else
			{
				pPOI->pParent = pPReAll[nDepth-1];
				pPReAll[nDepth] = pPOI;		
			}			
			pMapInUserDongPos->insert(USER_DONGPOS_MAP::value_type(nID, pPOI));  // 일단 유저는 안만들거라서 
			pMatchMap->insert(USER_DONGPOS_MATCH_MAP::value_type(nDongID, nID ));
			/*
			pMapInUserDongPos->insert(USER_DONGPOS_MAP::value_type(nID, pPOI));
			if(bFactPOI)
			pMapInDongPos->insert(DONGPOS_MAP::value_type(nDongID, pPOI));
			*/

			pRs2.MoveNext();
		}
		pRs2.Close();
		m_mapCoInUserDongPos[nCompany] = pMapInUserDongPos;
		m_mapCoInUserDongPosMatch[nCompany] = pMatchMap;
		//m_mapCoInDongPos[nCompany] = pMapInDongPos;

	}
}

void CUserDongPos::SetUserDongMatch(long nCompany,USER_DONGPOS_MATCH_MAP *pMap)
{
	m_mapCoInUserDongPosMatch[nCompany] = pMap;

}

void CUserDongPos::SetUserDong(long nCompany,USER_DONGPOS_MAP *pMap)
{
	m_mapCoInUserDongPos[nCompany] = pMap;
}
