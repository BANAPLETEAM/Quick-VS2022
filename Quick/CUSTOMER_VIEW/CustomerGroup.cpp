
#include "stdafx.h"
#include "resource.h"
#include "Customergroup.h"

CCustomerGroup::CCustomerGroup(void)
{ 
}

CCustomerGroup::~CCustomerGroup(void)
{
	if(m_mapGroup.size() > 0)
	{
		MAP_CUSTOMER_GROUP::iterator it;

		for(it = m_mapGroup.begin(); it != m_mapGroup.end(); ++it )
		{
			if(it->second)
				delete it->second;
		}
	}
}

ST_CUSTOMER_GROUP_INFOMATION * CCustomerGroup::GetGroupData(long nGNo)
{
	MAP_CUSTOMER_GROUP::iterator it = m_mapGroup.find(nGNo);
	m_stEmptyInfo.nGNo =0;
	m_stEmptyInfo.nCompany = 0;
	m_stEmptyInfo.strGroupName = "";
	m_stEmptyInfo.strDept = "";
	m_stEmptyInfo.strTotalName = "";	
	m_stEmptyInfo.nMembers = 0;
	m_stEmptyInfo.strDetail = "";
	m_stEmptyInfo.strPassword = "";
	m_stEmptyInfo.nCharge = 0;
	m_stEmptyInfo.strID = "";
	m_stEmptyInfo.nDepositRate = 0;
	m_stEmptyInfo.strName = "";
	m_stEmptyInfo.strMemberTel = "";
	m_stEmptyInfo.strChargeName = "";	
	m_stEmptyInfo.strPresident = "";
	m_stEmptyInfo.strBusinessNo = "";
	m_stEmptyInfo.strBusinessStatus = "";
	m_stEmptyInfo.strBusinessCategory = "";
	m_stEmptyInfo.strArea = "";
	m_stEmptyInfo.strEmail = "";
	m_stEmptyInfo.nReportFirstDay = 0;
	m_stEmptyInfo.nReportSecondDay = 0;
	m_stEmptyInfo.nGroupOwner = 0;
	m_stEmptyInfo.nParentGNo = 0;
	m_stEmptyInfo.nParentGNo2 = 0;
	m_stEmptyInfo.nParentGNo3 = 0;
	m_stEmptyInfo.nParentGNo4 = 0;
	m_stEmptyInfo.nParentGNo5 = 0;
	m_stEmptyInfo.nLevel = 0;
	m_stEmptyInfo.nGNoKey = 0;
	m_stEmptyInfo.strKeyRef = "";
	m_stEmptyInfo.strFullName = "";
	m_stEmptyInfo.pReocrd = NULL;
	m_stEmptyInfo.bNotShowCash = FALSE;

	if(it == m_mapGroup.end())
		return &m_stEmptyInfo;

	return it->second;
}

BOOL CCustomerGroup::SetGroupData(long nGNo, ST_CUSTOMER_GROUP_INFOMATION *newST)
{
	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "update_group_2008_3");	
	pCmd2.AddParameter(nGNo);	
	pCmd2.AddParameter(newST->strGroupName);	
	pCmd2.AddParameter(newST->strDept);
	pCmd2.AddParameter(newST->strName);
	pCmd2.AddParameter(newST->strMemberTel);
	pCmd2.AddParameter(newST->strID);
	pCmd2.AddParameter(newST->strPassword);
	pCmd2.AddParameter(newST->strEmail);
	pCmd2.AddParameter(newST->nCharge);
	pCmd2.AddParameter(newST->nDepositRate);		
	pCmd2.AddParameter(newST->strDetail);
	pCmd2.AddParameter(newST->strPresident);
	pCmd2.AddParameter(newST->strBusinessStatus);
	pCmd2.AddParameter(newST->strBusinessCategory);
	pCmd2.AddParameter(newST->strArea);
	pCmd2.AddParameter(newST->strBusinessNo);
	pCmd2.AddParameter(newST->nReportFirstDay);
	pCmd2.AddParameter(newST->nReportSecondDay);
	pCmd2.AddParameter(newST->nCredit);
	pCmd2.AddParameter(newST->nDiscount);
	pCmd2.AddParameter(newST->bNotShowCash);
	
	if(!pRs2.Execute(&pCmd2))
		return FALSE;

	MAP_CUSTOMER_GROUP::iterator itMap;
	VEC_CUSTOMER_GROUP::iterator itVec;

	m_mapGroup[nGNo] = newST;

	long nItem = 0;
	for(itVec = m_vecGroup.begin(); itVec != m_vecGroup.end(); itVec++) 
	{
		ST_CUSTOMER_GROUP_INFOMATION *st = (*itVec);

		if(st->nGNo == nGNo)
		{
			st->strTotalName = newST->strDept.GetLength() > 0 ? newST->strGroupName + "/" + newST->strDept : newST->strGroupName;
			st = newST;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CCustomerGroup::SetGroupReportData(long nGNo, ST_CUSTOMER_GROUP_INFOMATION *newST, BOOL bInCludeTree)
{
	if(bInCludeTree)
	{
		if(MessageBox(NULL, "하위항목도 모두 적용 하시겠습니까?", "확인", MB_OKCANCEL) != IDOK)
			bInCludeTree = FALSE;
	}

	//if(MessageBox(NULL, "재정산하시겠습니까?\r\n새벽정산시 재정산이 일어납니다", "확인", MB_OKCANCEL) == IDOK)
	//{
	//	CMkCommand pCmd(m_pMkDb, "update_need_rereport_1");
	//	pCmd.AddParameter(nGNo);
	//	pCmd.AddParameter(bInCludeTree);

	//	if(!pCmd.Execute()) return FALSE;
	//}

	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "update_group_report_data_2");	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long),nGNo);	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), newST->nReportFirstDay);
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), newST->nReportSecondDay);
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), newST->nDiscount);
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), newST->nAddTaxApplyType);
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), newST->bCashApply);
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), newST->bCreditApply);
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), newST->bOnlineApply);
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), newST->bTransApply);
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), newST->bShowOrder);
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), bInCludeTree);

	CString sColumn = "";

	for(int i=0; i<21; i++)
		sColumn += newST->strColumnChk.GetAt(i) + ";";

	pCmd2.AddParameter(typeString, typeInput, sColumn.GetLength(), sColumn);


	if(!pRs2.Execute(&pCmd2))
		return FALSE;

	MAP_CUSTOMER_GROUP::iterator itMap;
	VEC_CUSTOMER_GROUP::iterator itVec;

	m_mapGroup[nGNo] = newST;

	long nItem = 0;
	for(itVec = m_vecGroup.begin(); itVec != m_vecGroup.end(); itVec++) 
	{
		ST_CUSTOMER_GROUP_INFOMATION *st = (*itVec);

		if(st->nGNo == nGNo)
		{
			st->strTotalName = newST->strDept.GetLength() > 0 ? newST->strGroupName + "/" + newST->strDept : newST->strGroupName;
			st = newST;

			if(bInCludeTree == FALSE)
				return TRUE;
		}

		if(bInCludeTree == TRUE && st->nParentGNo == nGNo)
			st = newST;
	}


	return TRUE;
}

void CCustomerGroup::Clear()
{
	
	if(m_mapGroup.size() > 0)
	{
		MAP_CUSTOMER_GROUP::iterator it;

		for(it = m_mapGroup.begin(); it != m_mapGroup.end(); ++it )
		{
			if(it->second)
				delete it->second;
		}
	}

	m_mapGroup.clear();	
	m_vecGroup.clear();
}

void CCustomerGroup::FillCharge()
{
	m_mapChargeType.clear();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_chargetypename");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(1);

	if(!pRs.Execute(&pCmd)) return;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		ST_CHARGE_TYPE_NAME_INFO st;

		pRs.GetFieldValue("nID", st.nID);
		pRs.GetFieldValue("nCompany", st.nCompany);
		pRs.GetFieldValue("sChargeName", st.strChargeName);
		pRs.GetFieldValue("sEtc", st.strEtc);

		m_mapChargeType[st.nID] = st;

		pRs.MoveNext();
	}
	pRs.Close();


}
void CCustomerGroup::FillData()
{
	Clear();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group4");

	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(1);

	if(!pRs.Execute(&pCmd)) return;
	long nGNoKey = 0;
	CString strGNoKeyRef;
	int nPreLevel = 0;
	CString strColumnChk;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		ST_CUSTOMER_GROUP_INFOMATION *st = new ST_CUSTOMER_GROUP_INFOMATION;

		pRs.GetFieldValue("nCompany", st->nCompany);
		pRs.GetFieldValue("nGNo", st->nGNo);
		pRs.GetFieldValue("strGroupName", st->strGroupName);
		pRs.GetFieldValue("nMembers", st->nMembers);
		pRs.GetFieldValue("strDetail", st->strDetail);
		pRs.GetFieldValue("strPassword", st->strPassword);
		pRs.GetFieldValue("nCharge", st->nCharge);
		pRs.GetFieldValue("sID", st->strID);
		pRs.GetFieldValue("sMemberTel", st->strMemberTel);
		pRs.GetFieldValue("sManageHP", st->strManagerHP);
		pRs.GetFieldValue("sPresident", st->strPresident);
		pRs.GetFieldValue("sBusinessNo", st->strBusinessNo);
		pRs.GetFieldValue("sBusinessStatus", st->strBusinessStatus);
		pRs.GetFieldValue("sBusinessCategory", st->strBusinessCategory);
		pRs.GetFieldValue("sArea", st->strArea);
		pRs.GetFieldValue("sDept", st->strDept);
		pRs.GetFieldValue("sEmail", st->strEmail);
		pRs.GetFieldValue("nParentGNo", st->nParentGNo);
		pRs.GetFieldValue("nDepositRate", st->nDepositRate);
		pRs.GetFieldValue("sName", st->strName);
		pRs.GetFieldValue("nReportFirstDay", st->nReportFirstDay);
		pRs.GetFieldValue("nReportSecondDay", st->nReportSecondDay);
		pRs.GetFieldValue("nParentGNo", st->nParentGNo);
		pRs.GetFieldValue("nParentGNo", st->nParentGNo);
		pRs.GetFieldValue("nParentGNo2", st->nParentGNo2);
		pRs.GetFieldValue("nParentGNo3", st->nParentGNo3);
		pRs.GetFieldValue("nParentGNo4", st->nParentGNo4);
		pRs.GetFieldValue("nParentGNo5", st->nParentGNo5);
		pRs.GetFieldValue("nCompany", st->nCompany);
		pRs.GetFieldValue("nActiveLevel", st->nActiveLevel);
		pRs.GetFieldValue("nUseCount", st->nUseCount);
		pRs.GetFieldValue("nCancelCount", st->nCancelCount);
		pRs.GetFieldValue("dtLastUse", st->dtLastUse);
		pRs.GetFieldValue("dtLastInput", st->dtLastInput);
		pRs.GetFieldValue("nBalance", st->nBalance);
		pRs.GetFieldValue("nActiveGroupLevel", st->nActiveGroupLevel);
		pRs.GetFieldValue("nCredit", st->nCredit);
		pRs.GetFieldValue("nGroupCredit", st->nGroupCredit);
		pRs.GetFieldValue("nDiscount", st->nDiscount);
		pRs.GetFieldValue("nAddTaxApplyType", st->nAddTaxApplyType);
		pRs.GetFieldValue("bCashApply", st->bCashApply);
		pRs.GetFieldValue("bCreditApply", st->bCreditApply);
		pRs.GetFieldValue("bOnlineApply", st->bOnlineApply);
		pRs.GetFieldValue("bTransApply", st->bTransApply);
		pRs.GetFieldValue("bShowOrder", st->bShowOrder);
		pRs.GetFieldValue("sColumnChk", strColumnChk);
		pRs.GetFieldValue("bNotShowCash", st->bNotShowCash);
		pRs.GetFieldValue("nInitDay", st->nInitDay);
		pRs.GetFieldValue("nAbleUseCharge", st->nAbleUseCharge);
		pRs.GetFieldValue("nUseCharge", st->nUseCharge);
		pRs.GetFieldValue("sNotIncomeMonth", st->strNotIncomeMonth);
		pRs.GetFieldValue("bIntercallNotViewAmount", st->nInterCallNotViewAmount);
		pRs.GetFieldValue("nDirectDiscountType", st->nDirectDiscountType);
		pRs.GetFieldValue("nDirectDiscount", st->nDirectDiscount);
		pRs.GetFieldValue("nDirectDiscountRange", st->nDirectDiscountRange);
		pRs.GetFieldValue("bManagerIsOrderInput", st->bManagerIsOrderInput);
		pRs.GetFieldValue("nAutoCalculate", st->nAutoCalculate);
		pRs.GetFieldValue("nElectronicTaxType", st->nElectronicTaxType);
		pRs.GetFieldValue("nBillCollectionDay", st->nBillCollectionAdd);
		pRs.GetFieldValue("nPayMentDay", st->nPayMentAdd);
		pRs.GetFieldValue("sGNoList", st->strGNoList);
		pRs.GetFieldValue("nGNoListType", st->nGNoListType);
		pRs.GetFieldValue("bIntercallGroupOwner", st->bIntercallGroupOwner);
		st->nGroupCount = 0;
		st->bNoGroupCharge = FALSE;
		st->strFullName = st->strGroupName;
		st->strFullName += st->strDept == "" ? "" : "/" + st->strDept;
		st->strFullName += st->strName == "" ? "" : "/" + st->strName;

		if(strColumnChk == "")
		{
			for(int i=0; i<21; i++)
				st->strColumnChk.Add("0");
		}
		else
		{
			long nStartEtcPos = 0;
			long nDestEtcPos = 0;
	
			while(1)
			{
				nDestEtcPos = strColumnChk.Find(";", nStartEtcPos);

				if(nDestEtcPos == -1)
					break;

				CString sItem = strColumnChk.Mid(nStartEtcPos, nDestEtcPos - nStartEtcPos);

				st->strColumnChk.Add(sItem);

				nStartEtcPos = nDestEtcPos + 1;
			}
		}
		
		st->pReocrd = NULL;		
		st->strChargeName =(st->nCharge <= 0 ) ? "" : m_mapChargeType[st->nCharge].strChargeName;
		st->strTotalName = st->strDept.GetLength() > 0 ? st->strGroupName + "/" + st->strDept : st->strGroupName;

		st->nLevel = GetLevel(st);
		
		if(st->nGNo > 0 && st->nParentGNo == 0)
		{
			nGNoKey = st->nGNo;
			strGNoKeyRef = "";
			nPreLevel = 0;
		}
		else
		{
			if(nPreLevel > st->nLevel)
			{
				strGNoKeyRef = strGNoKeyRef.Left(st->nLevel);
				CString strAlpha = strGNoKeyRef.Right(1);
				int nAscii = __toascii(strAlpha.GetAt(0));
				strGNoKeyRef.Format("%s%c",strGNoKeyRef.Left(st->nLevel - 1), ++nAscii );
			}
			else if(nPreLevel == st->nLevel)
			{
				CString strAlpha = strGNoKeyRef.Right(1);
				int nAscii = __toascii(strAlpha.GetAt(0));			
				int nLen = strGNoKeyRef.GetLength() - 1;
				if(nLen < 0) nLen = 0;
				strGNoKeyRef.Format("%s%c", strGNoKeyRef.Left(nLen), ++nAscii );
			}
			else
			{
				strGNoKeyRef.Format("%s%c", strGNoKeyRef, 97); // 97 -> a
				
			}
			nPreLevel = st->nLevel;
			strGNoKeyRef = strGNoKeyRef;
		}

		st->nGNoKey = nGNoKey;
		st->strKeyRef = strGNoKeyRef;

		m_vecGroup.push_back(st);
		m_mapGroup[st->nGNo] = st;

		pRs.MoveNext();
		//m_Group.insert(CRiderPosMap::value_type(std::make_pair(st->nCompany, st->nGNo), st));
	}
	pRs.Close();

	//CUSTOMER_GROUP_INFOMATION *st = new CUSTOMER_GROUP_INFOMATION;
	//st->sGroupName = "";
	//m_mapGroup[0] = st;

    UpdateGroupCount();
}

void CCustomerGroup::UpdateGroupCount()
{
	//여기서 SearchData도 생성
	VEC_CUSTOMER_GROUP::iterator itVec;

	long nItem = 0;
	char buffer[10];

	ST_CUSTOMER_GROUP_INFOMATION *stTop = NULL;

	for(itVec = m_vecGroup.begin(); itVec != m_vecGroup.end(); itVec++) 
	{
		ST_CUSTOMER_GROUP_INFOMATION *st = (*itVec);
		
		if(st->nLevel == 0)
		{
			stTop = (*itVec);
			stTop->nGroupCount++;

			stTop->strSearchData = st->strGroupName + "%" + st->strDept + "%" + st->strName + "%";
			stTop->strSearchDateData = "$" + (CString)itoa(st->nReportFirstDay, buffer, 10) + "%$" + (CString)itoa(st->nReportSecondDay, buffer, 10) + "%";
			stTop->strNotIncomeMonthData = st->strNotIncomeMonth;

			continue;
		}

		if(stTop->nGNo == st->nParentGNo)
		{
			stTop->nGroupCount++;
		}

		stTop->strSearchData += st->strGroupName + "%" + st->strDept + "%" + st->strName + "%";
		stTop->strSearchDateData += "$" + (CString)itoa(st->nReportFirstDay, buffer, 10) + "%$" + (CString)itoa(st->nReportSecondDay, buffer, 10) + "%";
		stTop->strNotIncomeMonthData += st->strNotIncomeMonth;
	}
}

long CCustomerGroup::GetLevel(ST_CUSTOMER_GROUP_INFOMATION *st)
{
    if(st->nParentGNo == 0)
		return 0;
	else if(st->nParentGNo2 == 0)
		return 1;
	else if(st->nParentGNo3 == 0)
		return 2;
	else if(st->nParentGNo4 == 0)
		return 3;
	else if(st->nParentGNo5 == 0)
		return 4;
	else if(st->nParentGNo5 != 0)
		return 5;

	return -1;
}

MAP_CUSTOMER_GROUP * CCustomerGroup::SearchParentAllGroup(long nGNo)
{
	m_mapTemp.clear();

	MAP_CUSTOMER_GROUP::iterator it;	

	long nGroupKey = 0;
	nGroupKey = m_mapGroup[nGNo]->nGNoKey;

	for(it = m_mapGroup.begin(); it != m_mapGroup.end(); ++it)
	{
		if(it->second->nGNoKey == nGroupKey)
			m_mapTemp[it->first] = it->second;
	}

	return &m_mapTemp;

}
CUIntArray* CCustomerGroup::SearchParentAllGroup(CString strSearchGroupWord, int nOrginalSearchType)
{
	CUIntArray *pIntArray = NULL;
	if(strSearchGroupWord.GetLength() == 0)
		return pIntArray;

	MAP_CUSTOMER_GROUP::iterator it;
	CString strGroupName, strDept, strName;
	int nSearchType = 0;

	pIntArray = new CUIntArray();
	for(it = GetGroup()->begin(); it != GetGroup()->end(); ++it)
	{
		strGroupName = it->second->strGroupName;
		strDept		= it->second->strDept;
		strName		= it->second->strName;

		if(strGroupName.GetLength() == 0)
			continue;

		nSearchType = nOrginalSearchType;

		strGroupName.MakeUpper();
		strSearchGroupWord.MakeUpper();

		if(nSearchType >= 4)
		{
			if(strName.Find(strSearchGroupWord,0) >= 0 )
				pIntArray->Add(it->second->nGNoKey);
			nSearchType -= 4;
		}
		if(nSearchType >= 2)
		{
			if(strDept.Find(strSearchGroupWord,0) >= 0 )
				pIntArray->Add(it->second->nGNoKey);
			nSearchType -= 2;
		}
		if(nSearchType >= 1)
		{
			if(strGroupName.Find(strSearchGroupWord,0) >= 0 )
				pIntArray->Add(it->second->nGNoKey);			
		}		
	}
    if(pIntArray->GetCount() == 0)
	{
		if(pIntArray)
		{
			delete pIntArray;
			pIntArray = NULL;
			return pIntArray;
		}
	}
	
	return pIntArray;
}

BOOL CCustomerGroup::SetGroupDataFull(long nGNo, ST_CUSTOMER_GROUP_INFOMATION *newST, BOOL bInCludeTree)
{
	if(bInCludeTree)
	{
		if(MessageBox(NULL, "하위항목도 모두 적용 하시겠습니까?\r\n[그룹명][부서명][아이디][패스워드][그룹정산항목]을(를) 제외한 모든 항목에 적용됩니다.", "확인", MB_OKCANCEL) != IDOK)
			bInCludeTree = FALSE;
	}

	if(MessageBox(NULL, "재정산하시겠습니까?\r\n새벽정산시 재정산이 일어납니다", "확인", MB_OKCANCEL) == IDOK)
	{
		CMkCommand pCmd(m_pMkDb, "update_need_rereport_1");
		pCmd.AddParameter(nGNo);
		pCmd.AddParameter(bInCludeTree);

		if(!pCmd.Execute()) return FALSE;
	}

	CMkRecordset pRs2(m_pMkDb);
													 
	CMkCommand pCmd2(m_pMkDb, "update_group_full_data_2011_5");	
	//CMkCommand pCmd2(m_pMkDb, "update_group_full_data_2008_4");	
	pCmd2.AddParameter(nGNo);	
	pCmd2.AddParameter(newST->strGroupName);	
	pCmd2.AddParameter(newST->strDept);
	pCmd2.AddParameter(newST->strName);
	pCmd2.AddParameter(newST->strMemberTel);
	pCmd2.AddParameter(newST->strManagerHP);
	pCmd2.AddParameter(newST->strID);
	pCmd2.AddParameter(newST->strPassword);
	pCmd2.AddParameter(newST->strEmail);
	pCmd2.AddParameter(newST->nCharge);
	pCmd2.AddParameter(newST->nDepositRate);		
	pCmd2.AddParameter(newST->strDetail);
	pCmd2.AddParameter(newST->strPresident);
	pCmd2.AddParameter(newST->strBusinessStatus);
	pCmd2.AddParameter(newST->strBusinessCategory);
	pCmd2.AddParameter(newST->strArea);
	pCmd2.AddParameter(newST->strBusinessNo);
	pCmd2.AddParameter(newST->nReportFirstDay);
	pCmd2.AddParameter(newST->nReportSecondDay);
	pCmd2.AddParameter(newST->nCredit);
	pCmd2.AddParameter(newST->nDiscount);
	pCmd2.AddParameter(newST->nAddTaxApplyType);
	pCmd2.AddParameter(newST->bCashApply);
	pCmd2.AddParameter(newST->bCreditApply);
	pCmd2.AddParameter(newST->bOnlineApply);
	pCmd2.AddParameter(newST->bTransApply);
	pCmd2.AddParameter(newST->bNotShowCash);
	pCmd2.AddParameter(newST->nInitDay);
	pCmd2.AddParameter(newST->nAbleUseCharge);
	pCmd2.AddParameter(bInCludeTree);
	pCmd2.AddParameter(newST->nInterCallNotViewAmount);
	pCmd2.AddParameter(newST->nDirectDiscountType);
	pCmd2.AddParameter(newST->nDirectDiscount);
	pCmd2.AddParameter(newST->nDirectDiscountRange);

	pCmd2.AddParameter(newST->nElectronicTaxType);
	pCmd2.AddParameter(newST->nAutoCalculate);
	pCmd2.AddParameter(newST->nBillCollectionAdd);
	pCmd2.AddParameter(newST->nPayMentAdd);
	pCmd2.AddParameter(newST->strGNoList);
	pCmd2.AddParameter(newST->nGNoListType);
	pCmd2.AddParameter(newST->bIntercallGroupOwner);

	pCmd2.AddParameter(m_ui.nCompany);
	pCmd2.AddParameter(m_ui.nWNo);
	pCmd2.AddParameter(m_ui.strName);

	if(!pRs2.Execute(&pCmd2))
		return FALSE;

	MAP_CUSTOMER_GROUP::iterator itMap;
	VEC_CUSTOMER_GROUP::iterator itVec;

	m_mapGroup[nGNo] = newST;

	long nItem = 0;
	for(itVec = m_vecGroup.begin(); itVec != m_vecGroup.end(); itVec++) 
	{
		ST_CUSTOMER_GROUP_INFOMATION *st = (*itVec);

		if(st->nGNo == nGNo)
		{
			st->strTotalName = newST->strDept.GetLength() > 0 ? newST->strGroupName + "/" + newST->strDept : newST->strGroupName;
			st = newST;

			if(bInCludeTree == FALSE)
				return TRUE;
		}

		if(bInCludeTree == TRUE && st->nParentGNo == nGNo)
			st = newST;
	}

	return TRUE;
}

BOOL CCustomerGroup::CheckGroup(long nFirst, long nSecond)
{
	if(m_mapGroup.find(nFirst) == m_mapGroup.end())
		return FALSE;
	if(m_mapGroup.find(nSecond) == m_mapGroup.end())
		return FALSE;

	if((m_mapGroup[nFirst]->nParentGNo == m_mapGroup[nSecond]->nParentGNo) &&
			(m_mapGroup[nFirst]->nParentGNo != 0))
			return TRUE;

	if(m_mapGroup[nFirst]->nParentGNo ==  nSecond)
		return TRUE;

	if(m_mapGroup[nSecond]->nParentGNo ==  nFirst)
		return TRUE;

	return FALSE;
};

void CCustomerGroup::SetDataNotIncomeMonth(long nGNo, CString strNotIncomeMonth)
{
	m_mapGroup[nGNo]->strNotIncomeMonth = strNotIncomeMonth;
	UpdateGroupCount();
}
void CCustomerGroup::GetTopLevelID_PWD(long nChildGNo, CString &strID, CString &strPWD)
{
	strID = "";
	strPWD = "";
	if(m_mapGroup.size()  <= 0 )
		return;

	MAP_CUSTOMER_GROUP::iterator it = m_mapGroup.find(nChildGNo);

	if(it == m_mapGroup.end())
		return;


	long nParentGNo = it->second->nParentGNo;
	if(nParentGNo > 0 )
	{
		MAP_CUSTOMER_GROUP::iterator itSecond = m_mapGroup.find(nParentGNo);

		if(itSecond == m_mapGroup.end())
			return;

		if(itSecond->second->nParentGNo == 0 && itSecond->first > 0 )
		{
			strID = itSecond->second->strID;
			strPWD = itSecond->second->strPassword;
			return;
		}

		
	}
	else if(nParentGNo <= 0)
	{
		strID = it->second->strID;
		strPWD = it->second->strPassword;
	}



}

CString CCustomerGroup::GetAllGNoListFromChildGNo(long nChildGNo)
{

	CString strGNoList = "";

	if(m_mapGroup.size()  <= 0 )
	{
		return "";

	}
	MAP_CUSTOMER_GROUP::iterator it = m_mapGroup.find(nChildGNo);

	if(it == m_mapGroup.end())
		return "";

	map<long,long> mapGNo;
	map<long,long>::iterator itGNoList;

	mapGNo.insert(map<long,long>::value_type(nChildGNo,nChildGNo));

	long nSearchParentGNo;
	if(it->second->nParentGNo == 0)
		nSearchParentGNo  =  it->first;
	else
		nSearchParentGNo  =  it->second->nParentGNo;

	/*nParentGNo[1]  =  it->second->nParentGNo2;
	nParentGNo[2]  =  it->second->nParentGNo3;
	nParentGNo[3]  =  it->second->nParentGNo4;
	nParentGNo[4]  =  it->second->nParentGNo5;*/

	for(it = m_mapGroup.begin();it != m_mapGroup.end(); ++it)
	{
		if(it->second->nParentGNo  == nSearchParentGNo && nSearchParentGNo > 0 && it->second->nParentGNo > 0)			
			mapGNo[it->first] = it->first;
	
	}

	if(mapGNo.size() > 0)
	{
		CString strGNo = "";
		for(itGNoList = mapGNo.begin();itGNoList != mapGNo.end(); ++itGNoList)
		{
			strGNo.Format("%ld", itGNoList->first);
			strGNoList += strGNo + ",";
		}
	}

	return strGNoList;

/*

if(it->second->nParentGNo2 == nParentGNo[1]  && nParentGNo[1] > 0 )
{
	mapGNo[it->first] = it->first;
	if( it->first != nParentGNo[1])
		mapGNo[it->first] = nParentGNo[1];
}

if(it->second->nParentGNo3 == nParentGNo[2]  && nParentGNo[2] > 0 )
{
	mapGNo[it->first] = it->first;
	if( it->first != nParentGNo[2])
		mapGNo[it->first] = nParentGNo[2];
}

if(it->second->nParentGNo4 == nParentGNo[3]  && nParentGNo[3] > 0 )
{
	mapGNo[it->first] = it->first;
	if( it->first != nParentGNo[3])
		mapGNo[it->first] = nParentGNo[3];
}

if(it->second->nParentGNo5 == nParentGNo[4]  && nParentGNo[4] > 0 )
{
	mapGNo[it->first] = it->first;
	if( it->first != nParentGNo[4])
		mapGNo[it->first] = nParentGNo[4];
}*/




}