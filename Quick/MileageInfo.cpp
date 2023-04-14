#include "stdafx.h"
#include "MileageInfo.h"


#define  NO_MILEAGE_PERSON 10
#define  MILEAGE_PERSON_PERSENT 1
#define  MILEAGE_PERSON_AMOUNT 2
#define SECTION_MILEAGE 100000
#define COUNT_MILEAGE 200000

CMileageInfo::CMileageInfo(void)
{
	m_bFillData = FALSE;
}

CMileageInfo::~CMileageInfo(void)
{
	if(m_MileageMap.size() > 0)
	{
		MILEAGE_INFORMATION_MAP::iterator it;

		for(it = m_MileageMap.begin(); it != m_MileageMap.end(); ++it )
		{
			if(it->second)
				delete it->second;
		}
	}
}


MILEAGE_INFORMATION info;	

MILEAGE_INFORMATION * CMileageInfo::GetMileData(long nCompany)
{
	MILEAGE_INFORMATION_MAP::iterator it;
	it = m_MileageMap.find(nCompany);

	if(it != m_MileageMap.end())
	{
		if(it->second)
			return it->second;
	}

	ZeroMemory(&info, sizeof(MILEAGE_INFORMATION));
	return &info;
}
void CMileageInfo::Clear()
{
	
	if(m_MileageMap.size() > 0)
	{
		MILEAGE_INFORMATION_MAP::iterator it;

		for(it = m_MileageMap.begin(); it != m_MileageMap.end(); ++it )
		{
			if(it->second)
				delete it->second;
		}
	}
	m_MileageMap.clear();
	
	
}
void CMileageInfo::InsertData(long nCompany)
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
void CMileageInfo::FillData()
{
	Clear();
	m_bFillData = FALSE;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_company_mileage_info4");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	
	if(!pRs.Execute(&pCmd)) return;
	if(pRs.GetRecordCount() <= 0) return;
	
	long nInitCompany = 0;
	long nPreCompany = -1,nCompany = 0, nStartAmount = 0 , nEndAmount =0, nAmount = 0, 
		nMileageSpan = 0, nMileageSettingCount = 0, nCount = 0;

	MILEAGE_INFORMATION *st = new MILEAGE_INFORMATION;
	pRs.GetFieldValue("nCompany",  nInitCompany);
	m_MileageMap[nInitCompany] = st;
	BOOL bOne = TRUE;
	long nClass = -1, nCarType = -1, nPreCarType = -1;
	for(int i=0; i<pRs.GetRecordCount(); i++)
	{		
		
		pRs.GetFieldValue("nCompany",  nCompany);
		if(nCompany != nPreCompany )
		{	
			
			if(!bOne)
			{
				st = new MILEAGE_INFORMATION;	
				m_MileageMap[nCompany] = st;
			}
				
			bOne = FALSE;
			nCount = 0;
		}

		
			
		pRs.GetFieldValue("nCompany",  st->nCompany);		
		pRs.GetFieldValue("nMileageSettingCount", st->nMileageSettingCount);
		pRs.GetFieldValue("nMileageSettingCountTruck", st->nMileageSettingCountTruck);		
		pRs.GetFieldValue("nMileageSpan", st->nMileageSpan);		
		pRs.GetFieldValue("nClass", st->nClass);		
		pRs.GetFieldValue("nCarType", nCarType);		
		if(nPreCarType != nCarType)
			nCount = 0;

		pRs.GetFieldValue("nStartValue", st->nStartAmount[nCarType][nCount] );
		pRs.GetFieldValue("nEndValue", st->nEndAmount[nCarType][nCount]);
		pRs.GetFieldValue("nAmount", st->nAmount[nCarType][nCount]);		
		st->nTermCount[nCarType] = nCount + 1;
		

		nPreCarType = nCarType;
		nClass = st->nClass;
		nCount++;
	
		nPreCompany = nCompany;
		pRs.MoveNext();
		
	}
	if(pRs.GetRecordCount() > 0)
		m_bFillData = TRUE;
	pRs.Close();
	

}


long CMileageInfo::GetMileageVal(long nCompany, int nUiCarType, int nPersonMileageType, 
			long nPersonMileage,long nChargeSum, int nRcpCarType)
{
	long nMileageValue = 0;

	//if(bAutoCharge) return 0;
	if(nCompany <= 0) return 0;
	if(!m_bFillData ) return 0;

	if(nPersonMileageType == NO_MILEAGE_PERSON)
		return -1;

	if(nPersonMileageType == 1)
		nMileageValue = nChargeSum * (nPersonMileage /100.0);	
	else if(nPersonMileageType == 2)
		nMileageValue = nPersonMileage;	
	else
	{
		if(m_mi.GetMileData(nCompany)->nMileageSettingCount == 0)
			return 0;

		if(::IsCarTypeTruck(nRcpCarType) == TRUE && m_mi.GetMileData(nCompany)->nMileageSettingCountTruck != 0)
		{
			if(m_mi.GetMileData(nCompany)->nMileageSettingCountTruck > -100 && 
				m_mi.GetMileData(nCompany)->nMileageSettingCountTruck  < -1)
			{
				nMileageValue = nChargeSum * (m_mi.GetMileData(nCompany)->nMileageSettingCountTruck  * -1  / 100.0);
				return nMileageValue;
			}
			else
			{
				nMileageValue = m_mi.GetMileData(nCompany)->nMileageSettingCountTruck;
				return nMileageValue;
			}
		}
		else if(m_mi.GetMileData(nCompany)->nMileageSettingCount == SECTION_MILEAGE ||
			m_mi.GetMileData(nCompany)->nMileageSettingCount == COUNT_MILEAGE)  // 구간당
		{
			int nCarType = GetCarTypeForCharge(nUiCarType);
			long nTermCount = m_mi.GetMileData(nCompany)->nTermCount[nCarType];
			long nStartAmount, nDestAmount;
			for(int i = 0; i < nTermCount; i++)
			{							
				nStartAmount = m_mi.GetMileData(nCompany)->nStartAmount[nCarType][i];
				nDestAmount = m_mi.GetMileData(nCompany)->nEndAmount[nCarType][i];

				if(nStartAmount <= nChargeSum && nChargeSum <= nDestAmount)
				{
					nMileageValue = m_mi.GetMileData(nCompany)->nAmount[nCarType][i];
					return nMileageValue;
				}

			}
		}
		else
		{	
			if(m_mi.GetMileData(nCompany)->nMileageSettingCount > -100 && 
				m_mi.GetMileData(nCompany)->nMileageSettingCount  < -1)
			{
				nMileageValue = nChargeSum * (m_mi.GetMileData(nCompany)->nMileageSettingCount  * -1  / 100.0);
				return nMileageValue;
			}
			else
			{
				nMileageValue = m_mi.GetMileData(nCompany)->nMileageSettingCount;
				return nMileageValue;
			}	
		}
	}

	return nMileageValue;
}


long CMileageInfo::GetCarTypeForCharge(long nCarType)
{
	long nChargeCarType = 0;

	switch(nCarType)
	{
	case CAR_AUTO:
	case CAR_BIGBIKE:
		nChargeCarType = 0;
		break;
	case CAR_DAMA:
	case CAR_LABO:
		nChargeCarType = 1;
		break;
	case CAR_VAN:
		nChargeCarType = 2;
		break;
	case CAR_TRUCK:
		nChargeCarType = 3;
		break;
	default:
		break;
	}

	return nChargeCarType;
	
}




BOOL CMileageInfo::IsBranchUseMile(long nCompany, int nMilegeType)
{

	if(nMilegeType == NO_MILEAGE_PERSON)
		return FALSE;

	if(nMilegeType ==MILEAGE_PERSON_PERSENT || nMilegeType == MILEAGE_PERSON_AMOUNT  )
		return TRUE;
	

	if(nCompany > 0)
	{
		MILEAGE_INFORMATION_MAP::iterator it;
		it = m_MileageMap.find(nCompany);
		if(it == m_MileageMap.end())
			return FALSE;
		else
			return TRUE;
	}


	return FALSE;
}



BOOL CMileageInfo::IsMileageUseSpanCheck(long nCNo , long nSpanMile, long nEditTNo)
{

	if(nCNo <= NULL)
	{
		AfxMessageBox("고객의 데이터가 없습니다. 다시시도 하세요");
		return FALSE;
	}
	if(nSpanMile <=0 )
	{
		AfxMessageBox("사용할 마일이 없습니다  금액을 다시입력 하세요");
		return FALSE;
	}

	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "select_is_mileage_span2", FALSE, TRUE);		
	pCmd2.AddParameter(nCNo);	
	pCmd2.AddParameter(nSpanMile);	
	pCmd2.AddParameter(nEditTNo);
	if(!pRs2.Execute(&pCmd2)) return FALSE;

	if(pRs2.GetRecordCount() <= 0 )
	{
		AfxMessageBox("해당 고객의 데이터가 없습니다.");
		return FALSE;
	}

	long nTotalSpan = 0, nMileBalance = 0;
	pRs2.GetFieldValue("nTotalSpan", nTotalSpan);
	pRs2.GetFieldValue("nMileBalance", nMileBalance);

	if(nEditTNo > 0)
	{
		if( nMileBalance + nTotalSpan >= nSpanMile && nMileBalance >= 0) 
			return TRUE;

	}
	else
	{
		if(nMileBalance >= nSpanMile  && nMileBalance >= 0)
			return TRUE;
	}




	return FALSE;

}


long CMileageInfo::GetNowMileageBalance(long nCNo,  long nEditTNo)
{
	if(nCNo == NULL)
	{
		//AfxMessageBox("고객의 데이터가 없습니다. 다시시도 하세요");
		return 0;
	}

	if(nEditTNo <=0 )
		nEditTNo = -1;

	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "select_is_mileage_span2", FALSE, TRUE);		
	pCmd2.AddParameter(nCNo);	
	pCmd2.AddParameter(0);	
	pCmd2.AddParameter(nEditTNo);
	if(!pRs2.Execute(&pCmd2)) return FALSE;

	if(pRs2.GetRecordCount() <= 0 )
	{
		AfxMessageBox("해당 고객의 데이터가 없습니다.");
		return 0;
	}

	long nTotalSpan = 0, nMileBalance = 0;
	//pRs2.GetFieldValue("nTotalSpan", nTotalSpan);
	pRs2.GetFieldValue("nMileBalance", nMileBalance);


	return nMileBalance;



}