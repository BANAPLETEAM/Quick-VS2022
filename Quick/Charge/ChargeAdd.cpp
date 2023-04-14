#include "StdAfx.h"
#include "ChargeAdd.h"


// 수정시 intercall 도 함께 수정해야함.

CChargeAdd::CChargeAdd(void)
{
}

CChargeAdd::~CChargeAdd(void)
{
	MAP_CO_DAY_CHARGE_INFO::iterator itCompany;
	MAP_DAY_CHARGE_INFO::iterator  itmapDayChargeInfo;
	VEC_CHARGE_INFO::iterator itCharge;
	VEC_DAY_CHARGE_INFO::iterator itvecDayChargeList;

	for(itCompany = m_mapCoDayChargeInfo.begin(); itCompany != m_mapCoDayChargeInfo.end(); ++itCompany)
	{		
		VEC_DAY_CHARGE_INFO *pvecDayChargeInfo = m_mapCoDayChargeInfo[itCompany->first];	
		for(itvecDayChargeList = pvecDayChargeInfo->begin(); itvecDayChargeList != pvecDayChargeInfo->end(); ++ itvecDayChargeList)
		{		
			MAP_DAY_CHARGE_INFO *pmapDayChargeInfo = (*itvecDayChargeList);
			for(itmapDayChargeInfo = pmapDayChargeInfo->begin(); itmapDayChargeInfo != pmapDayChargeInfo->end(); ++ itmapDayChargeInfo)
			{
				VEC_CHARGE_INFO *pvecChargeList = itmapDayChargeInfo->second;
				for(itCharge = pvecChargeList->begin(); itCharge != pvecChargeList->end(); ++itCharge)
				{
					ADDCHARGE *pCharge = (*itCharge);
					if(pCharge) {	delete pCharge; pCharge = NULL;	}
				}
				if(pvecChargeList)	{	delete pvecChargeList;	pvecChargeList = NULL; 	}
			}

			if(pmapDayChargeInfo){	delete pmapDayChargeInfo; pmapDayChargeInfo = NULL;	}
		} 
		if(pvecDayChargeInfo) {	delete pvecDayChargeInfo; pvecDayChargeInfo = NULL;	}
	}
}


void CChargeAdd::LoadChargeAddData(long nCompany, BOOL bIntegrted)
{

	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "select_time_add_charge2");	
	pCmd2.AddParameter(nCompany);			
	pCmd2.AddParameter(bIntegrted);			


	MAP_CO_DAY_CHARGE_INFO::iterator pmapCoDayChargeInfo;
	MAP_DAY_CHARGE_INFO::iterator itDayChargeInfo;

	MAP_DAY_CHARGE_INFO *pmapDayChargeInfo;
	VEC_DAY_CHARGE_INFO *pvecDayChargeList;
	
	VEC_CHARGE_INFO *pvecChargeList;
	
	long nPreCompany = -1, nPreDayType = 0, nInit = 0;
	
	if(!pRs2.Execute(&pCmd2)) return;
	
	ADDCHARGE *pLoopAddCharge = NULL;
	
	for(int nRow = 0; nRow < pRs2.GetRecordCount(); nRow++)
	{
		long nDayType, nMotoCharge, nDamaCharge, nLaboCharge, nBonggoCharge, nTruckCharge;
		//CString strGroupName, strDetail ,sID, strPassword, sPresident, sBusinessNo, sBusinessStatus, 
		//	sBusinessCategory,sArea, sDept, sEmail,sName, sMemberTel;
		COleDateTime dtFrom , dtTo;		COleDateTimeSpan dtSecondSpan(0, 0, 0 ,59), dtTommorowSpan(0, 24,0,0);
		int nStartDay = 0, nEndDay = 0;

		pRs2.GetFieldValue("nCompany", nCompany);
		pRs2.GetFieldValue("nDayType", nDayType);
		pRs2.GetFieldValue("sFromTime", dtFrom);
		pRs2.GetFieldValue("sToTime", dtTo);
		pRs2.GetFieldValue("nMotoCharge", nMotoCharge);
		pRs2.GetFieldValue("nDamaCharge", nDamaCharge);
		pRs2.GetFieldValue("nLaboCharge", nLaboCharge);
		pRs2.GetFieldValue("nBonggoCharge", nBonggoCharge);
		pRs2.GetFieldValue("nTruckCharge", nTruckCharge);

		ADDCHARGE *pAddCharge = new ADDCHARGE;
		dtTo += dtSecondSpan;		
		pAddCharge->dtFrom.SetTime(dtFrom.GetHour(), dtFrom.GetMinute(), dtFrom.GetSecond());
		pAddCharge->dtTo.SetTime(dtTo.GetHour() , dtTo.GetMinute(), dtTo.GetSecond());		

		// 회사가 변하고  첫줄의 00:00 는 당일로 봄
		// 두
		/*
		if(dtFrom.GetHour() >= 0 && dtFrom.GetHour() <= 8)
		{
			if(nCompany == nPreCompany)  // 첫줄은 00 이전 시작은 하루를(익일) 처리 안함.  00:00 ~ 23:59 
				 pAddCharge->dtFrom += dtTommorowSpan;
		}
		
			
		if(dtTo.GetHour() >= 0 && dtTo.GetHour() <= 8)
			pAddCharge->dtTo += dtTommorowSpan;			
		*/

		pAddCharge->nMotoCharge = nMotoCharge;
		pAddCharge->nDamaCharge = nDamaCharge;
		pAddCharge->nLaboCharge = nLaboCharge;
		pAddCharge->nBonggoCharge = nBonggoCharge;
		pAddCharge->nTruckCharge = nTruckCharge;
		
		if(nDayType == 9 || nDayType == 8)
		{
			if(nDayType == 9) {	nStartDay = 1; nEndDay = 8;	}
			else					{ nStartDay = 2; nEndDay = 7;	}

			int nInitCount = 0;

			for(int i = nStartDay; i < nEndDay; i++)
			{						
				
				if(!IsMapCompanyDay(nCompany, i))
				{
					pvecChargeList = new VEC_CHARGE_INFO;
					pvecChargeList->push_back(nInitCount >0 ? pLoopAddCharge : pAddCharge);
					
					pmapDayChargeInfo = new MAP_DAY_CHARGE_INFO;
					pmapDayChargeInfo->insert(MAP_DAY_CHARGE_INFO::value_type(i, pvecChargeList));

					pvecDayChargeList = new VEC_DAY_CHARGE_INFO;
					pvecDayChargeList->push_back(pmapDayChargeInfo);

					if(!IsMapCompany(nCompany))
						m_mapCoDayChargeInfo.insert(MAP_CO_DAY_CHARGE_INFO::value_type(nCompany, pvecDayChargeList));
					else
					{
						pvecDayChargeList = m_mapCoDayChargeInfo[nCompany];			
						pvecDayChargeList->push_back(pmapDayChargeInfo);
					}
				}
				else
				{
					pvecChargeList = GetCompanyDayChargeVector(nCompany, i);
					pvecChargeList->push_back(nInitCount >0 ? pLoopAddCharge : pAddCharge);				
				}
				nInitCount ++;
				pLoopAddCharge = new ADDCHARGE;
				*pLoopAddCharge = *pAddCharge;
			}
		}		
		else
		{
			if(!IsMapCompanyDay(nCompany, nDayType))
			{
				pvecChargeList = new VEC_CHARGE_INFO;
				pvecChargeList->push_back(pAddCharge);

				pmapDayChargeInfo = new MAP_DAY_CHARGE_INFO;
				pmapDayChargeInfo->insert(MAP_DAY_CHARGE_INFO::value_type(nDayType, pvecChargeList));

				pvecDayChargeList = new VEC_DAY_CHARGE_INFO;
				pvecDayChargeList->push_back(pmapDayChargeInfo);

				if(!IsMapCompany(nCompany))
					m_mapCoDayChargeInfo.insert(MAP_CO_DAY_CHARGE_INFO::value_type(nCompany, pvecDayChargeList));
				else
				{
					pvecDayChargeList = m_mapCoDayChargeInfo[nCompany];			
					pvecDayChargeList->push_back(pmapDayChargeInfo);
				}
				
			}
			else{
				pvecChargeList = GetCompanyDayChargeVector(nCompany, nDayType);
				pvecChargeList->push_back(pAddCharge);			
			}

		}
		nPreCompany = nCompany;
		pRs2.MoveNext();

	}	
	
	pRs2.Close();


	LoadHolidayInfo();
}

void CChargeAdd::LoadHolidayInfo()
{
	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "select_holiday_info");	
	pCmd2.AddParameter(0);		

	if(!pRs2.Execute(&pCmd2)) return;

	for(int nRow = 0; nRow < pRs2.GetRecordCount(); nRow++)
	{
		COleDateTime dtHoliday;
		CString strDesc;

		pRs2.GetFieldValue("dtHoliday", dtHoliday);
		pRs2.GetFieldValue("sDesc", strDesc);
		m_mapHoliday[dtHoliday] = strDesc;

		pRs2.MoveNext();
	}
}

BOOL CChargeAdd::IsHoliday(COleDateTime dtDate)
{
	dtDate.SetDateTime(dtDate.GetYear(), dtDate.GetMonth(), dtDate.GetDay(), 0, 0, 0);
	return m_mapHoliday.find(dtDate) != m_mapHoliday.end();
}

long CChargeAdd::GetChargeAdd(long nCompany,int  nDay,int nCar,long  nCharge, COleDateTime dtOrderInputTime)
{	
	if((long)m_mapCoDayChargeInfo.size() <= 0 )
		return 0;  
   
	long nRoundCharge = 0;
	COleDateTimeSpan dt24TimeSpan; dt24TimeSpan.SetDateTimeSpan(0, 24,0,0);
	COleDateTime dtNow ;//		dtTemp(COleDateTime::GetCurrentTime());
	COleDateTime dtTemp(dtOrderInputTime);
	if(dtTemp.GetHour() >= 0 && dtTemp.GetHour() <= 6)
	{
		dtNow.SetTime(dtTemp.GetHour() , dtTemp.GetMinute(), dtTemp.GetSecond() );
		dtNow += dt24TimeSpan;
	}
	else
		dtNow.SetTime(dtTemp.GetHour(), dtTemp.GetMinute(), dtTemp.GetSecond() );

	if(IsHoliday(dtOrderInputTime))
		nDay = 1;

	MAP_CO_DAY_CHARGE_INFO::iterator itCompany;
	MAP_DAY_CHARGE_INFO::iterator  itmapDayChargeInfo;
	VEC_CHARGE_INFO::iterator itCharge;
	VEC_DAY_CHARGE_INFO::iterator itvecDayChargeList;

	itCompany = m_mapCoDayChargeInfo.find(nCompany);

	if(itCompany == m_mapCoDayChargeInfo.end())
		return 0;

	VEC_DAY_CHARGE_INFO *pvecDayChargeInfo = m_mapCoDayChargeInfo[nCompany];	
	for(itvecDayChargeList = pvecDayChargeInfo->begin(); itvecDayChargeList != pvecDayChargeInfo->end(); ++ itvecDayChargeList)
	{		
		MAP_DAY_CHARGE_INFO *pmapDayChargeInfo = (*itvecDayChargeList);
		MAP_DAY_CHARGE_INFO::iterator it_mapChargeInfo = pmapDayChargeInfo->find(nDay);
		//if( (*itvecDayChargeList)->first == nDay)
		if(it_mapChargeInfo  != pmapDayChargeInfo->end())
		{
			VEC_CHARGE_INFO *pvecChargeList = it_mapChargeInfo->second	;
	
			for(itCharge = pvecChargeList->begin(); itCharge != pvecChargeList->end(); ++ itCharge)
			{
				ADDCHARGE * pAddCharge = (*itCharge);				
				if(	 pAddCharge->dtFrom <= dtNow && dtNow <= pAddCharge->dtTo ) 
				{
					switch(nCar)
					{
					case 0 :
					
						if(pAddCharge->nMotoCharge > 300 )
							return pAddCharge->nMotoCharge;
						else if(pAddCharge->nMotoCharge < -300 )
							return pAddCharge->nMotoCharge ;
						else
						{
							nCharge =  int( nCharge * pAddCharge->nMotoCharge /100);
							/*nRoundCharge = int(nCharge / 1000.0) * 1000;
							return (nCharge - nRoundCharge >= 500) ? nRoundCharge + 1000 : nRoundCharge;*/
							return nCharge;
						}
						break;
					case 1: 
						if(pAddCharge->nDamaCharge > 300 )
							return pAddCharge->nDamaCharge;
						else if(pAddCharge->nDamaCharge < -300 )
							return pAddCharge->nDamaCharge;	
						else
						{
							nCharge =  int( nCharge * pAddCharge->nDamaCharge /100);
							/*nRoundCharge = int(nCharge / 1000.0) * 1000;
							return (nCharge - nRoundCharge >= 500) ? nRoundCharge + 1000 : nRoundCharge;*/
							return nCharge;
						}
						break;
					case 2: 
						if(pAddCharge->nLaboCharge > 300 )
							return pAddCharge->nLaboCharge;
						else if(pAddCharge->nLaboCharge < -300 )
							return pAddCharge->nLaboCharge;	
						else
						{
							nCharge =  int( nCharge * pAddCharge->nDamaCharge /100);
							/*nRoundCharge = int(nCharge / 1000.0) * 1000;
							return (nCharge - nRoundCharge >= 500) ? nRoundCharge + 1000 : nRoundCharge;*/
							return nCharge;
						}
						break;
					case 3 :					
						if(pAddCharge->nBonggoCharge > 300 )
							return pAddCharge->nBonggoCharge;
						else if(pAddCharge->nBonggoCharge < -300 )
							return pAddCharge->nBonggoCharge;
						else					 
						{
							nCharge =  int( nCharge * pAddCharge->nBonggoCharge /100);
							/*nRoundCharge = int(nCharge / 1000.0) * 1000;
							return (nCharge - nRoundCharge >= 500) ? nRoundCharge + 1000 : nRoundCharge;*/
							return nCharge;
						}
						break;
					case 4 :
					
					
						if(pAddCharge->nTruckCharge > 300 )
							return pAddCharge->nTruckCharge;
						else if(pAddCharge->nTruckCharge < 300)
							return pAddCharge->nTruckCharge;
						else
						{
							nCharge =  int( nCharge * pAddCharge->nTruckCharge /100);
							/*nRoundCharge = int(nCharge / 1000.0) * 1000;
							return (nCharge - nRoundCharge >= 500) ? nRoundCharge + 1000 : nRoundCharge;*/
							return nCharge;
						}
						break;
				   default :
						return 0;
					} //switch
				} // if				
			} //for
			
		}// if
	} // for
	return 0;
}

BOOL CChargeAdd::IsMapCompany(long nCompany)
{
	MAP_CO_DAY_CHARGE_INFO::iterator it;
	it = m_mapCoDayChargeInfo.find(nCompany);
	if(it == m_mapCoDayChargeInfo.end())
		return FALSE;
	else
		return TRUE;

}

VEC_CHARGE_INFO* CChargeAdd::GetCompanyDayChargeVector(long nCompany, long nDayType	 )
{
	MAP_CO_DAY_CHARGE_INFO::iterator itCompany;
	MAP_DAY_CHARGE_INFO::iterator itDay;

	VEC_DAY_CHARGE_INFO::iterator itVecDayChargeinfo;

	itCompany = m_mapCoDayChargeInfo.find(nCompany);
	if(itCompany == m_mapCoDayChargeInfo.end())
		return NULL;
	else
	{		
		VEC_DAY_CHARGE_INFO *pvecDayChargeInfo = itCompany->second;
		for(itVecDayChargeinfo = pvecDayChargeInfo->begin(); itVecDayChargeinfo != pvecDayChargeInfo->end(); ++ itVecDayChargeinfo)
		{
			itDay = (*itVecDayChargeinfo)->find(nDayType);
			if(itDay != (*itVecDayChargeinfo)->end())
				return itDay->second;	
		}
		return NULL;
	}
	return NULL;

}

BOOL CChargeAdd::IsMapCompanyDay(long nCompany, long nDayType)
{

	MAP_CO_DAY_CHARGE_INFO::iterator itCompany;
	MAP_DAY_CHARGE_INFO::iterator itDay;
	VEC_DAY_CHARGE_INFO::iterator itVecDayChargeinfo;

	itCompany = m_mapCoDayChargeInfo.find(nCompany);
	if(itCompany == m_mapCoDayChargeInfo.end())
		return FALSE;
	else
	{
		VEC_DAY_CHARGE_INFO *pvecDayChargeInfo = itCompany->second;
		for(itVecDayChargeinfo = pvecDayChargeInfo->begin(); itVecDayChargeinfo != pvecDayChargeInfo->end(); ++ itVecDayChargeinfo)
		{
			itDay = (*itVecDayChargeinfo)->find(nDayType);
			if(itDay != (*itVecDayChargeinfo)->end())
				return TRUE;
				
		}
		return FALSE;
	}
	return FALSE;

}