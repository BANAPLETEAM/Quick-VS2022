#include "StdAfx.h"
#include "resource.h"
#include "Charge.h"
#include "POIDataNew.h"
#include "RcpDlg.h"
#include "RcpPlaceInfo.h"

#define  VIA_MAX_COUNT 3
#define  KM_PER 2


//CHARGE_DONG_EX_MAP2011 CCharge::m_mapChargeDongEx2011;

CCharge::CCharge(CWnd *pwndParent)
{
	SetNullData();
	m_pRcpDlg = (CRcpDlg*)pwndParent;
	
	m_bHasCharge = 0;
	m_nPreStartID = 0;
	m_nPreDestID = 0;
	m_nPreGNo = 0;
	m_bNoGroupCharge = FALSE;
	m_bChargeTypeCelChange = FALSE;
	m_bDefaultCharge = FALSE;
	m_bMinCharge = FALSE;
	m_bNotMemberCharge = FALSE;
	m_bMemChaNoGeneralData = FALSE;
	m_nMemCharge = 0;  // 히스토리요금
	m_nEmergency = 0;
	
}

CCharge::~CCharge(void)
{
}


void CCharge::SetNullData()
{
	
	m_pStartPoi = NULL;
	m_pDestPoi = NULL;
	
	m_nCharge = 0; 
	m_nExCharge = 0;

	m_bExCharge = FALSE; //확장요금
	m_bMinCharge = FALSE;
	m_bDefaultCharge = FALSE;	     // 기본요금
	m_bNewDongCharge = FALSE;  // 구간요금
	m_bDistanceCharge = FALSE;	// 거리요금
	m_bDistanceTypeCharge = FALSE;// 선택요금
	
	m_nDefaultCharge = 0;
	m_nMinCharge = 0;
	m_nDistanceCharge = 0;
	
	m_nMemCharge = 0;
	m_nEmergency = 0;
	m_bMemCharge = FALSE;
	m_bGroupCharge = FALSE;
	m_strInfoTotal = "";
	
	m_lfDistance = 0.0;
	m_pBi = NULL;
	m_nChargeType = 0;
	m_nCarType = 0;
	m_nGNo = 0;
	m_bNoGroupCharge = FALSE;
    m_bNotMemberCharge = FALSE;
	m_bCashCharge =  FALSE; // 캐쉬 차량타입, A, B,C,D 가져올때

	for(int nChargeType = 0; nChargeType < CHARGE_TYPE; nChargeType++ )
		for(int nCarType = 0; nCarType <CAR_TYPE; nCarType ++  )
		{
		//	m_nNewDongCharge[nChargeType][nCarType] = 0; // 구간요금

			CHARGE_GNO_MAP::iterator it = m_nNewDongCharge.find(make_pair(nChargeType, m_nCarType));

			if(it != m_nNewDongCharge.end())
			{
				it->second.nCharge = 0;
				it->second.nChargeRider = 0;
				it->second.nDiscount = 0;
			}

			m_nDistanceTypeCharge[nChargeType][nCarType] = 0; // 거리요금	
			m_strKmNameType.Empty();
			m_nAmountType = 0;
		}
}


CPOIUnit* CCharge::GetStartPoi()
{
	if(m_pStartPoi)
		return m_pStartPoi;
	else
		return NULL;
}


CPOIUnit* CCharge::GetDestPoi()
{
	if(m_pDestPoi)
		return m_pDestPoi;
	else
		return NULL;
}

void CCharge::InitBranchInfo(CWnd *pWnd, CBranchInfo *pBi)
{
	m_pBi = pBi;
	m_pRcpDlg = (CRcpDlg*)pWnd;

	if(m_pBi)
		m_bNotMemberCharge = m_pBi->bNotMemberCharge;
		
}

long CCharge::DefaultCharge(long nCharge)
{
	if( IsDefaultCharge(nCharge) )
	{
		m_bDefaultCharge = TRUE;			
		nCharge = m_nDefaultCharge =  GetBI()->nDefaultCharge;
	}
	else
	{
		m_bDefaultCharge = FALSE;			
	}

	return nCharge;
}

long CCharge::MinCharge(long nCharge)
{	
	if(	IsMinCharge(nCharge) )
	{
		m_bMinCharge = TRUE;			
		nCharge = m_nMinCharge =  GetBI()->nMinCharge;
	}
	else
		m_bMinCharge = FALSE;		

	return nCharge;
}


CHARGE_GNO_MAP::iterator CCharge::GetGNoMapIterator(long nChargeType, long nCarType)
{
	CHARGE_GNO_MAP::iterator it = m_nNewDongCharge.find(make_pair(nChargeType, nCarType));

	if(it == m_nNewDongCharge.end())
	{
		CHARGE_GNO_STRUCT st;
		st.nCharge = 0;
		st.nChargeRider = 0;
		st.nDiscount = 0;
		m_nNewDongCharge.insert(CHARGE_GNO_MAP::value_type(make_pair(nChargeType, nCarType), st));

		it = m_nNewDongCharge.find(make_pair(nChargeType, nCarType));
	}

	return it;
}


void CCharge::NewDongCharge()
{

	if(!m_pStartPoi || !m_pDestPoi)
		return;
	
	int nS4 = 0, nS1 = 0, nS2 = 0, nS3 = 0;
	int nD4 = 0, nD1 = 0, nD2 = 0, nD3 = 0;
		

	
	m_pStartPoi->GetTreeID(nS1, nS2, nS3, nS4, !IsExceptionDetailDongUse(m_pStartPoi));
	m_pDestPoi->GetTreeID(nD1, nD2, nD3, nD4, !IsExceptionDetailDongUse(m_pDestPoi));
	//m_pStartPoi->GetTreeID(nS1, nS2, nS3, nS0, FALSE);
	//m_pDestPoi->GetTreeID(nD1, nD2, nD3, nD0, FALSE);

	/*if(!GetBI()->bDongPosLiUse)
		nS4 = nD4 = 0;*/

	long nGNoCharge[CAR_TYPE];
	for(int i = 0; i < CAR_TYPE; i++) 
		nGNoCharge[i] =  0;

	BOOL bSimpleOneRow = TRUE; long nOutValue = 0;
	long nGNoChargeNo = m_cg.GetGroupData(m_nGNo)->nCharge;
	
	//CMkCommand pCmd(m_pMkDb, "select_dong_charge_total_2015");
 	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_dong_charge_total_q3");	
	CMkParameter *pAuto, *pDama, *pRabo, *pBonggo ,*pTruck, *pSubWay;
	CMkParameter *pAutoRider, *pDamaRider, *pRaboRider, *pBonggoRider, *pTruckRider, *pSubWayRider;
	CMkParameter *pAutoDiscount, *pDamaDiscount, *pRaboDiscount, *pBonggoDiscount, *pTruckDiscount, *pSubWayDiscount;
	CMkParameter *pT2ton, *pT3ton, *pT5ton; 

	pCmd.SetHideWaitCursor(TRUE);	
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetBI()->nPayTable);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetBI()->nCustomerTable);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nS1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nS2);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nS3);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nS4);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nD1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nD2);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nD3);	
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nD4);	
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nChargeType);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nGNo); 

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nMemCharge);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_bNoGroupCharge);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nEmergency);
	pAuto = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	pDama = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	pRabo = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	pBonggo = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	pTruck = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);	
	pSubWay = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);	
	pAutoRider		= pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	pDamaRider		= pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	pRaboRider		= pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	pBonggoRider	= pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	pTruckRider		= pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);	
	pSubWayRider	= pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);	
	pAutoDiscount	= pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	pDamaDiscount	= pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	pRaboDiscount	= pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	pBonggoDiscount = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	pTruckDiscount	= pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);	
	pSubWayDiscount = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);	
	pT2ton			= pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);	
	pT3ton			= pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);	
	pT5ton			= pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);	

	if(!pRs.Execute(&pCmd)) return;

	m_nNewDongCharge.clear();


	m_bCashCharge = TRUE;  //디비에 한번검색되면
	long nTempCharge[CHARGE_TYPE][CAR_TYPE];
	for(int nChargeType = 0; nChargeType < CHARGE_TYPE; nChargeType++)
	{
		for(int nCarType = 0; nCarType < CAR_TYPE; nCarType++)
			nTempCharge[nChargeType][nCarType] = 0;		
	}

	CHARGE_GNO_MAP::iterator it = GetGNoMapIterator(TYPE_GNO, T_AUTO); 	
	pAuto->GetValue(it->second.nCharge); 
	pAutoRider->GetValue(it->second.nChargeRider); 
	pAutoDiscount->GetValue(it->second.nDiscount); 
	it = GetGNoMapIterator(TYPE_GNO, T_DAMA);   
	pDama->GetValue(it->second.nCharge);
	pDamaRider->GetValue(it->second.nChargeRider);
	pDamaDiscount->GetValue(it->second.nDiscount);
	it = GetGNoMapIterator(TYPE_GNO, T_RABO);   
	pRabo->GetValue(it->second.nCharge);
	pRaboRider->GetValue(it->second.nChargeRider);
	pRaboDiscount->GetValue(it->second.nDiscount);
	it = GetGNoMapIterator(TYPE_GNO, T_BAN);    
	pBonggo->GetValue(it->second.nCharge);
	pBonggoRider->GetValue(it->second.nChargeRider);
	pBonggoDiscount->GetValue(it->second.nDiscount);
	it = GetGNoMapIterator(TYPE_GNO, T_TRUCK);  
	pTruck->GetValue(it->second.nCharge);
	pTruckRider->GetValue(it->second.nChargeRider);
	pTruckDiscount->GetValue(it->second.nDiscount);
	it = GetGNoMapIterator(TYPE_GNO, T_SUBWAY); 
	pSubWay->GetValue(it->second.nCharge);
	pSubWayRider->GetValue(it->second.nChargeRider);
	pSubWayDiscount->GetValue(it->second.nDiscount);

	it = GetGNoMapIterator(TYPE_GNO, T_T2ton); 
	pT2ton->GetValue(it->second.nCharge);
	it = GetGNoMapIterator(TYPE_GNO, T_T3ton); 
	pT3ton->GetValue(it->second.nCharge);
	it = GetGNoMapIterator(TYPE_GNO, T_T5ton); 
	pT5ton->GetValue(it->second.nCharge);

	it = GetGNoMapIterator(TYPE_GNO, m_nCarType);

	if(m_nGNo > 0 && !m_bNoGroupCharge && it->second.nCharge > 0)
		m_bGroupCharge = TRUE;
	else if(m_nMemCharge > 0 && it->second.nCharge > 0)
	{
		if(!m_bNotMemberCharge)
			m_bMemCharge = TRUE;
	}

	if(pRs.GetRecordCount() == 0)
	{
		m_bNewDongCharge = FALSE;
	}
	else 
	{			
		
		BOOL bCustomerCharge = FALSE; int nChargeInput = 0;
		long nStartID = 0, nDestID = 0, nType = 0;
		for(int i = 0; i < pRs.GetRecordCount(); i++)
		{
			pRs.GetFieldValue("nType", nType);
			pRs.GetFieldValue("nStartID", nStartID);
			pRs.GetFieldValue("nDestID", nDestID);
			pRs.GetFieldValue("bCustomerCharge",	bCustomerCharge );
			pRs.GetFieldValue("nMotoChargeA",		nTempCharge[TYPE_A][T_AUTO]);
			pRs.GetFieldValue("nDamaChargeA",	   	nTempCharge[TYPE_A][T_DAMA]);
			pRs.GetFieldValue("nRaboChargeA",	   	nTempCharge[TYPE_A][T_RABO]);
			pRs.GetFieldValue("nBonggoChargeA",	   	nTempCharge[TYPE_A][T_BAN]);
			pRs.GetFieldValue("nTruckChargeA",	   	nTempCharge[TYPE_A][T_TRUCK]);
			pRs.GetFieldValue("nSubWayChargeA",	   	nTempCharge[TYPE_A][T_SUBWAY]);

			pRs.GetFieldValue("nMotoChargeB",       nTempCharge[TYPE_B][T_AUTO]);
			pRs.GetFieldValue("nDamaChargeB",	   	nTempCharge[TYPE_B][T_DAMA]);
			pRs.GetFieldValue("nRaboChargeB",	   	nTempCharge[TYPE_B][T_RABO]);
			pRs.GetFieldValue("nBonggoChargeB",	   	nTempCharge[TYPE_B][T_BAN]);
			pRs.GetFieldValue("nTruckChargeB",	   	nTempCharge[TYPE_B][T_TRUCK]);	
			pRs.GetFieldValue("nSubWayChargeB",	   	nTempCharge[TYPE_B][T_SUBWAY]);
				
			pRs.GetFieldValue("nMotoChargeC",		nTempCharge[TYPE_C][T_AUTO]);
			pRs.GetFieldValue("nDamaChargeC",       nTempCharge[TYPE_C][T_DAMA]);
			pRs.GetFieldValue("nRaboChargeC",       nTempCharge[TYPE_C][T_RABO]);
			pRs.GetFieldValue("nBonggoChargeC",    	nTempCharge[TYPE_C][T_BAN]);
			pRs.GetFieldValue("nTruckChargeC",      nTempCharge[TYPE_C][T_TRUCK]);
			pRs.GetFieldValue("nSubWayChargeC",     nTempCharge[TYPE_C][T_SUBWAY]);

			pRs.GetFieldValue("nMotoChargeD",       nTempCharge[TYPE_D][T_AUTO]);
			pRs.GetFieldValue("nDamaChargeD",	   	nTempCharge[TYPE_D][T_DAMA]);
			pRs.GetFieldValue("nRaboChargeD",	   	nTempCharge[TYPE_D][T_RABO]);
			pRs.GetFieldValue("nBonggoChargeD",	   	nTempCharge[TYPE_D][T_BAN]);
			pRs.GetFieldValue("nTruckChargeD",	   	nTempCharge[TYPE_D][T_TRUCK]);
			pRs.GetFieldValue("nSubWayChargeD",     nTempCharge[TYPE_D][T_SUBWAY]);

			for(int nChargeType = 0; nChargeType < CHARGE_TYPE; nChargeType++)
			{
				for(int nCarType = 0; nCarType < CAR_TYPE; nCarType++)
				{
					CHARGE_GNO_MAP::iterator itTemp = GetGNoMapIterator(nChargeType, nCarType);

					if(nTempCharge[nChargeType][nCarType] > 0 && itTemp->second.nCharge == 0)
					{	
						itTemp->second.nCharge = nTempCharge[nChargeType][nCarType];
						
						++nChargeInput;
						if(!m_bNewDongCharge)
							m_bNewDongCharge = TRUE;

						if(nChargeInput == (4 * 5) )
						{
							pRs.Close();
							return;
						}
					}
				}
			}		

			pRs.MoveNext();
		}		
		
		pRs.Close();

	}	
}



int CCharge::DistanceTypeCharge()
{
	if(!m_pStartPoi || !m_pDestPoi)
	{
		SetNullData();
		return 0;
	}

	int nS4 = 0, nS1 = 0, nS2 = 0, nS3 = 0;
	int nD4 = 0, nD1 = 0, nD2 = 0, nD3 = 0;
	
	m_pStartPoi->GetTreeID(nS1, nS2, nS3, nS4, IsExceptionDetailDongUse(m_pStartPoi));
	m_pDestPoi->GetTreeID(nD1, nD2, nD3, nD4, IsExceptionDetailDongUse(m_pDestPoi));

	/*if(!GetBI()->bDongPosLiUse)
		nS4 = nD4 = 0;*/

	BOOL bSimpleOneRow = TRUE; long nOutValue = 0;

	float nRealDistance = 0.0;
	//if(! GetBI()->bDistancePointUse)
	//	nRealDistance = (int)m_lfDistance;
	//else
	//	nRealDistance = m_lfDistance;

	CString strD;
	int distance = m_lfDistance * 100;
	strD.Format("%.1f", (float)distance / 100);
	nRealDistance = _tstof(strD);

	CBranchInfo *pBi;	
	if(GetBI()->nPayTable > 0 && GetBI()->nPayTable != GetBI()->nCompanyCode)
		pBi =  pBi = GetBranchInfo(GetBI()->nPayTable) == NULL ? GetBI() : GetBranchInfo(GetBI()->nPayTable);
	else
		pBi = GetBI(); 

	CMkRecordset pRs(m_pMkDb);
	CMkParameter *pAuto, *pDama, *pBonggo ,*pTruck ;
	//CMkCommand pCmd(m_pMkDb, "select_new_distance_charge2011_1", FALSE, TRUE);
	CMkCommand pCmd(m_pMkDb, "distance_charge_query", FALSE, TRUE);
	pCmd.SetHideWaitCursor(TRUE);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetBI()->nPayTable); // m_pBi 가 맞음..
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nS1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nS2);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nS3);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nS4);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nD1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nD2);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nD3);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nD4);
	pCmd.AddParameter((int)nRealDistance);	
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nChargeType);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nGNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nMemCharge);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRealCarType);
	//pCmd.AddParameter(GetBI()->nDistanceCharge == 1 ? TRUE : FALSE);
	pCmd.AddParameter(GetBI()->nDistanceCharge > 0 ? TRUE : FALSE);
	pAuto = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0); 
	pDama = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	pBonggo = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0); 
	pTruck = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);	
	 
	if(pRs.Execute(&pCmd))   
	{			
		m_bCashCharge = TRUE;  //디비에 한번검색되면

		long nTempCharge[CHARGE_TYPE][CAR_TYPE];
		for(int nChargeType = 0; nChargeType < CHARGE_TYPE; nChargeType++)
		{
			for(int nCarType = 0; nCarType < CAR_TYPE; nCarType++)
				nTempCharge[nChargeType][nCarType] = 0;		
		}
	
		pAuto->GetValue(	m_nDistanceTypeCharge[TYPE_GNO][T_AUTO]);
		pDama->GetValue(	m_nDistanceTypeCharge	[TYPE_GNO][T_DAMA]);
		pBonggo->GetValue(m_nDistanceTypeCharge[TYPE_GNO][T_BAN]);
		pTruck->GetValue(	m_nDistanceTypeCharge	[TYPE_GNO][T_TRUCK]);

		if(m_nGNo > 0 && m_nDistanceTypeCharge[TYPE_GNO][m_nCarType] > 0)
			m_bGroupCharge = TRUE;
		else if(m_nMemCharge > 0 && m_nDistanceTypeCharge[TYPE_GNO][m_nCarType] > 0)
		{
			if(m_bNotMemberCharge)
				m_bMemCharge = TRUE;
		}


		if(pRs.GetRecordCount() == 0)
		{		
			m_bDistanceTypeCharge = FALSE;
			m_strKmNameType = "";
		}
		else 
		{
			pRs.GetFieldValue("type_name", m_strKmNameType);
			pRs.GetFieldValue("charge", m_nAmountType);
		}
	}

	return m_nAmountType;
}


long CCharge::GetTotalCharge(long nMemCharge, CPOIUnit *pStartPoi, CPOIUnit *pDestPoi,long nGNo,
							 CBranchInfo *pBi, long &nChargeDriving, long &nDiscount, float nDistance , 
							 int nChargeType, int nCarType, BOOL bNoGroupCharge, int nEmergency, int nRealCarType )
{
	m_nCharge = 0; //초기화
	m_pStartPoi = pStartPoi;
	m_pDestPoi = pDestPoi;
	m_pBi = pBi;
	m_nChargeType = (nChargeType == 5) ? 0 : nChargeType ;
	m_nGNo = nGNo;
	m_nMemCharge = nMemCharge;
	m_nCarType = nCarType;
	m_bNoGroupCharge = bNoGroupCharge;
	m_nEmergency = nEmergency;
	m_nRealCarType = nRealCarType;
	nChargeDriving = 0;
	nDiscount = 0;

	//if( GetBI()->nDistanceCharge != 0  && GetBI()->bUseNewRegion)
	//	m_lfDistance = (int)nDistance;
	//else
		m_lfDistance = nDistance;

	if( IsOptionNewDongCharge() )  //0, 2    ex) 0  구간 ,1, 거리,  2    구간 + 거리
	{
		NewDongCharge();	
		m_nCharge += GetNewDongCharge();
	}

	if( IsOptionDistanceTypeCharge() )  //1 , 2   거리 ,  거리 + 구간 
	{			
		m_nCharge += DistanceTypeCharge();
		//m_nCharge += GetDistanceTypeCharge();	
	}	

	BOOL a = IsGroupChargeApply();
	BOOL b = IsMemberChargeApply();

	if( IsGroupChargeApply() || IsMemberChargeApply())
	{
		m_nCharge =  IsOptionDistanceTypeCharge() ? m_nDistanceTypeCharge[TYPE_GNO][m_nCarType] 
		: GetGNoMapIterator(TYPE_GNO, m_nCarType)->second.nCharge;
		//: m_nNewDongCharge[TYPE_GNO][m_nCarType];
		m_pRcpDlg->m_CMB_CHARGE_TYPE.pCombo->SetCurSel(TYPE_GNO);
		m_nChargeType = TYPE_GNO;

		if(!IsOptionDistanceTypeCharge())
		{
			nChargeDriving = GetGNoMapIterator(TYPE_GNO, m_nCarType)->second.nChargeRider;
			nDiscount = GetGNoMapIterator(TYPE_GNO, m_nCarType)->second.nDiscount;

			//if(nChargeDriving == 0)
			//	nChargeDriving = m_nCharge;
		}
		
		return m_nCharge;
	}		

	if(GetBI()->bDistanceCharge)
		m_nCharge = MinCharge(m_nCharge);

	m_nCharge = DefaultCharge(m_nCharge);


	return m_nCharge;

}



long  CCharge::GetCashCharge(long nMemCharge, CPOIUnit *pStartPoi, CPOIUnit *pDestPoi,long nGNo,
							 CBranchInfo *pBi, long &nChargeDriving, long &nDiscount, float nDistance , int nChargeType, int nCarType,BOOL bChargeTypeCelChange )
{
	nChargeDriving = 0;
	nDiscount = 0;
	
	if(m_nMemCharge == nMemCharge && m_pStartPoi == pStartPoi && m_pDestPoi == pDestPoi 
		&& m_nGNo == nGNo && GetBI() == pBi )
	{

		float fTempDistance = 0.0;
		if(GetBI()->bDistancePointUse)
			fTempDistance = int(nDistance);
		else
			fTempDistance = nDistance;

		if(GetBI()->bDistanceCharge && fTempDistance != m_lfDistance && fTempDistance > 0)  // 거리요금제 인데.. 거리가 틀릴시
			return GetTotalCharge(nMemCharge, pStartPoi, pDestPoi, nGNo, pBi, nChargeDriving, 
			nDiscount, nDistance, nChargeType, nCarType, m_bNoGroupCharge, m_nEmergency);
		else if(GetBI()->bDistanceCharge && fTempDistance <= 0 )
			return 0;
		else
		{
			m_nChargeType = nChargeType;
			m_nCarType = nCarType;
			m_bChargeTypeCelChange = bChargeTypeCelChange;
			m_nCharge = 0;

			if(IsOptionNewDongCharge())
			{
				// 캐쉬데이터 안에서 개별및 그룹요금 부터 적용한다
				// LableView 적용	
			

				if(! m_bChargeTypeCelChange && m_nMemCharge > 0 && GetGNoMapIterator(TYPE_GNO, m_nCarType)->second.nCharge > 0)
				{
					m_nCharge = GetGNoMapIterator(TYPE_GNO, m_nCarType)->second.nCharge;
					nChargeDriving = GetGNoMapIterator(TYPE_GNO, m_nCarType)->second.nChargeRider;
					m_pRcpDlg->m_CMB_CHARGE_TYPE.pCombo->SetCurSel(TYPE_GNO);
				}
				else if(!m_bChargeTypeCelChange && IsGNo() && GetGNoMapIterator(TYPE_GNO, m_nCarType)->second.nCharge > 0)
				{
					m_nCharge = GetGNoMapIterator(TYPE_GNO, m_nCarType)->second.nCharge;
					nChargeDriving = GetGNoMapIterator(TYPE_GNO, m_nCarType)->second.nChargeRider;
					m_pRcpDlg->m_CMB_CHARGE_TYPE.pCombo->SetCurSel(TYPE_GNO);
				}
				else
				{					
					m_nCharge = GetGNoMapIterator(m_nChargeType, m_nCarType)->second.nCharge;
					nChargeDriving = GetGNoMapIterator(TYPE_GNO, m_nCarType)->second.nChargeRider;
				}

				//if(nChargeDriving == 0)
				//	nChargeDriving = m_nCharge;
					//m_nCharge = m_nNewDongCharge[m_nChargeType][m_nCarType];

			}

			if(IsOptionDistanceTypeCharge())
			{
				if(IsOptionOnlyDistanceCharge())
					m_nCharge = m_nDistanceTypeCharge[m_nChargeType][m_nCarType];
				else
					m_nCharge += m_nDistanceTypeCharge[m_nChargeType][m_nCarType];
			}

			if(GetBI()->bDistanceCharge)
				m_nCharge = MinCharge(m_nCharge);

			m_nCharge = DefaultCharge(m_nCharge);
			return m_nCharge;
		}
	}
	return m_nCharge;		
	
	
}



CString CCharge::GetDistanceLableView()
{	
	CString strinfo2 = "";

	CString strKm = ""; 
	strKm.Format("%.1f", m_lfDistance );
	CString strInfoTotal  = "", strInfoDistance = "", strInfoDefault = "", strInfoVia ="";

	g_bana_log->Print("IsDefaultChargeApply = %d, IsMinChargeApply = %d GetBI()->bDistanceCharge = %d GetBI()->nMinCharge = %d, GetBI()->nCompany = %d\n", IsDefaultChargeApply() , IsMinChargeApply(), IsMinChargeApply(), GetBI()->nMinCharge, GetBI()->nCompanyCode);

	// 동기반에서  
	if(IsDefaultChargeApply() || IsMinChargeApply())
	{
		if(IsMinChargeApply() && GetBI()->bDistanceCharge)
		{
			strInfoTotal = "거리최저요금 :" + GetMyNumberFormat(GetBI()->nMinCharge);
			return strInfoTotal;
		}

		if(IsDefaultChargeApply())
			strInfoTotal = "구간기본요금:" + GetMyNumberFormat(GetBI()->nDefaultCharge);

	}
	else
	{
		CString strGroupOrMemeber  = "", strChargeType = ""; long nCharge = 0;

		if(IsOptionOnlyDistanceCharge() )
		{			
			nCharge = m_nAmountType;
			strInfoTotal = strGroupOrMemeber +  GetMyNumberFormat(nCharge) + 
				"(" + m_strKmNameType + "," +  ::GetCarTypeFromLong(m_nRealCarType) + ")";
			return strInfoTotal;
		}
		
		if(IsOptionNewDongCharge())
		{
			if(m_nGNo > 0 && m_nMemCharge > 0 && !m_bNoGroupCharge)
				strGroupOrMemeber = "그룹";
			else if(m_nMemCharge > 0 && !m_bNotMemberCharge)
				strGroupOrMemeber = "업체";
			else
				strGroupOrMemeber = "일반";
			
			if(!m_bChargeTypeCelChange && IsGNo() && GetGNoMapIterator(TYPE_GNO, m_nCarType)->second.nCharge > 0)
			{
				//nCharge = m_nNewDongCharge[TYPE_GNO][m_nCarType];
				nCharge = GetGNoMapIterator(TYPE_GNO, m_nCarType)->second.nCharge;
				strChargeType = m_cg.GetGroupData(m_nGNo)->strName;
			}			
			else if(!m_bChargeTypeCelChange && m_nMemCharge > 0 && GetGNoMapIterator(TYPE_GNO, m_nCarType)->second.nCharge > 0)
			{
				nCharge = GetGNoMapIterator(TYPE_GNO, m_nCarType)->second.nCharge;
				strChargeType = "개별";
			}
			else
			{
				nCharge = GetGNoMapIterator(m_nChargeType, m_nCarType)->second.nCharge;//m_nNewDongCharge[m_nChargeType][m_nCarType];
				strChargeType = "구간" + GetChargeTypeString();
			}

			//nCharge = m_nNewDongCharge[m_nChargeType][m_nCarType];
			strInfoDefault = strGroupOrMemeber + ": " +  GetMyNumberFormat(nCharge) + 
				"(" + strChargeType + ", " +  ::GetCarChargeTypeString(m_nCarType) + ")";
			//return strInfoTotal;
			//nCharge = GetNewDongCharge();
		}				
		
		if(IsOptionDistanceTypeCharge())
		{
			nCharge = GetDistanceTypeCharge();

			if(strInfoDefault.GetLength() > 0)
				strInfoDefault += " + ";


			CString strTemp = "";
			
			if(m_pBi)
				strTemp = m_pBi->bUseDirectDistance == TRUE ? "직선" : "";
			else if(m_pRcpDlg->m_pBi)
				strTemp = m_pRcpDlg->m_pBi->bUseDirectDistance == TRUE ? "직선" : "";

			strInfoDistance += GetMyNumberFormat(nCharge) + "(" + 
				GetDistanceTypeString(0, m_strKmNameType) + "," +
				strTemp +
				strKm +  "Km, "	+ GetChargeTypeString() + ")";
		}
		strInfoTotal = strInfoDefault + strInfoDistance;

	}		
	return strInfoTotal;
}

BOOL CCharge::IsGNo()
{
	if(m_nGNo > 0)
	{
		if( m_cg.GetGroupData(m_nGNo) != NULL)
		{
			if( m_cg.GetGroupData(m_nGNo)->nCharge > 0 )
				return TRUE;
		}

	}
	return FALSE;
}

CString CCharge::GetDistanceTypeString(int nAmountType, CString strDeistanceType )
{
	return strDeistanceType;
}

BOOL CCharge::IsSameRunType(int nRunType)
{
	if(m_nEmergency == nRunType)
		return TRUE;

	return FALSE;
}


CString CCharge::GetChargeTypeString(int nInputType)
{
	CString strChargeType = "";
	int nTempType = 0;

	if(nInputType < 0 )
		nTempType = m_nChargeType;
	else
		nTempType = nInputType;

	switch(nTempType)
	{

		case 0:
			strChargeType = "A";
			break;
		case 1:
			strChargeType = "B";
			break;
		case 2:
			strChargeType = "C";
			break;
		case 3:
			strChargeType = "D";
			break;			
		case 4:
			if(m_nGNo > 0)
				strChargeType = "그룹";
			else
				strChargeType = "개별";
			break;			

	}
	return strChargeType;
}

BOOL CCharge::IsOptionNewDongCharge()
{
	if(GetBI()->nDistanceCharge == 0 || GetBI()->nDistanceCharge == 2 )
		return TRUE;
	else
		return FALSE;

}


BOOL CCharge::IsOptionOnlyDistanceCharge()
{
	if( GetBI()->bDistanceCharge && GetBI()->nDistanceCharge == 1)
		return TRUE;
	else
		return FALSE;
}

BOOL CCharge::IsOptionDistanceTypeCharge()
{
	if(GetBI()->bDistanceCharge || GetBI()->nDistanceCharge > 1)  // 선택 || 기본 + 경유
		return TRUE;
	else
		return FALSE;

}


BOOL CCharge::IsMinCharge(long nCharge)
{
	if(nCharge <  GetBI()->nMinCharge &&  GetBI()->nMinCharge > 0 && GetBI()->bDistanceCharge)
		return TRUE;
	else
		return FALSE;
}


BOOL CCharge::IsDefaultCharge(long nCharge)
{
	if(nCharge <  GetBI()->nDefaultCharge &&  GetBI()->nDefaultCharge> 0 )
		return TRUE;
	else
		return FALSE;
}


BOOL CCharge::RemoveAllData()
{

	SetNullData();
	return TRUE;
}
//--------------------------------------------------------------------------


CBranchInfo* CCharge::GetBI()
{
	return (m_pBi == NULL) ? m_ba.GetAt(0) : m_pBi;
}




//---------------------------------------------------------------------

CDisplayChargeInfo::~CDisplayChargeInfo(void)
{
}

CDisplayChargeInfo::CDisplayChargeInfo(CWnd *pwndParent)
{
	RemoveAllData();
	m_pRcpDlg = (CRcpDlg*)pwndParent;
}

void CDisplayChargeInfo::RemoveAllData()
{
	m_pRcpDlg = NULL;	
	m_pCharge = NULL;
 

}

CString CDisplayChargeInfo::GetDistance()
{
	CString strTemp = "";
	if(m_pRcpDlg->m_fDirectDistance <= 0)
		strTemp.Format("거리:검색중..");
	else
		strTemp.Format("거리:%.1f", m_pRcpDlg->m_fDirectDistance);	

	return strTemp;
}



CString CDisplayChargeInfo::GetStartDestInfo()
{	
	if(m_pRcpDlg->m_pStart->GetPOI() > 0 && m_pRcpDlg->m_pDest->GetPOI() > 0)
		return m_pRcpDlg->m_pStart->GetDisplayDong() + "->" + m_pRcpDlg->m_pDest->GetDisplayDong();
	else 
		return "";
}

CString CDisplayChargeInfo::GetCharge()
{
	if( m_pCharge->IsDefaultChargeApply() )
		return "기본요금";
	else if( m_pCharge->IsMinChargeApply() )
		return "최저요금";


	CString strTotalTemp ="", strTemp = "";
	if(m_pCharge->IsNewDongChargeApply() )
	{			 
		strTemp.Format("구간요금(%s,%s)",::GetMyNumberFormat( m_pCharge->GetNewDongCharge( )) ,
			m_pCharge->GetChargeTypeString() );
		strTotalTemp += strTemp;			
	}

	return strTotalTemp;
}