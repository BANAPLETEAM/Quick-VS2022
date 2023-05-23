
#include "stdafx.h"
#include "Resource.h"
#include "GlobalXTPReportRecord.h"

#define COL_START	3
#define COL_DEST	4

CNearRecord::CNearRecord(BOOL bCheck,long nTNo,int nState,int nCarType, int nRunType, int nWayType,CString strBranchName,
						 CString strCName,CString strDelayTime,CString strStart, CString strDest,CString strEtc, COleDateTime dt1, 
						 int nRankType, BOOL nNearRiderOrder, long m_nOrderCompany)
{
	m_nTNo = nTNo;
	m_nRankType = nRankType;
	m_nState = nState;

	m_nCarType = nCarType;
	m_nRunType = nRunType;
	m_nWayType = nWayType;
	m_bNearRiderOrder = nNearRiderOrder;
	m_bCheck = bCheck;
	m_nCompany = m_nOrderCompany;

	CString strOption;
	if(nCarType > 0)
		strOption += CString("[") + LF->GetCarTypeFromLong(nCarType) + "]";

	if(nWayType > 0)
		strOption += CString("[") + LF->GetWayTypeFromLong(nWayType) + "]";

	if(nRunType > 0)
		strOption += CString("[") + LF->GetRunTypeFromLong(nRunType) + "]";

	AddItem(new CXTPGridRecordItemCheck(bCheck));
	AddItem(new CXTPGridRecordItemText(strCName)); 
	AddItem(new CXTPGridRecordItemText(strDelayTime)); 
	AddItem(new CXTPGridRecordItemText(strStart)); //3
	AddItem(new CXTPGridRecordItemText(strDest)); //4 <--
	AddItem(new CXTPGridRecordItemText(strOption)); //5 <--
}

void CNearRecord::GetItemMetrics (XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nRow = pDrawArgs->pRow->GetIndex();
	int nCount = pDrawArgs->pControl->GetRows()->GetCount();
	int nCol = pDrawArgs->pColumn->GetIndex();
	int nItemCol = pDrawArgs->pColumn->GetItemIndex();
	CString strEtc = "";
	CNearRecord *pNearRecord = (CNearRecord *)pDrawArgs->pRow->GetRecord();

	if(! pDrawArgs->pRow->IsItemsVisible() ) return;

	if(nCol == 0)
		pDrawArgs->pItem->SetIconIndex(LF->GetImageNumber(pNearRecord->m_nState));	

	pItemMetrics->clrForeground = OnColorText(pItemMetrics, nRow, nCol, nItemCol, pNearRecord->m_nRankType);
}

COLORREF CNearRecord::OnColorText(XTP_REPORTRECORDITEM_METRICS* pItemMetrics, int &nRow, int &nCol, int &nItemCol, int &nRankType)
{
	if(nRankType < 9 )
	{
		if(nRankType == 0 && (nCol == COL_START || nCol == COL_DEST) )
			return RGB(255, 0, 0);

		else if(nRankType == 1 && nCol == COL_START)
			return RGB(51, 0, 255);
		else if(nRankType == 1 && nCol == COL_DEST)
			return RGB(255, 0, 0);

		else if(nRankType == 2 && nCol == COL_START)
			return RGB(255, 0, 0);
		else if(nRankType == 2 && nCol == COL_DEST)
			return RGB(51, 0, 255);

		else if(nRankType == 3 && (nCol == COL_START || nCol == COL_DEST) )
			return RGB(51, 0, 255);

		else if(nRankType == 4 && nCol == COL_DEST)
			return RGB(255, 0, 0);

		else if(nRankType == 5 && nCol == COL_START)
			return RGB(255, 0, 0);

		else if(nRankType == 6 && nCol == COL_DEST)
			return RGB(51, 0, 255);

		else if(nRankType == 7 && nCol == COL_START)
			return RGB(51, 0, 255);		
		else
			return RGB(0, 0, 0);
	}	
	return RGB(0, 0, 0);
}

COLORREF CNearRecord::OnColorBack(XTP_REPORTRECORDITEM_METRICS* pItemMetrics, int &nRow, int &nCol, int &nItemCol, int &nTNo)
{
	return RGB(255,255,255);
}

CAfterReportRecord::CAfterReportRecord(long nGNo, CString strDate, long nCashCount, long nCashCharge, long nCreditCount, long nCreditCharge,
									   long nOnlineCount, long nOnlineCharge, long nTransCount, long nTransCharge)
{
	CString strFormat;

	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(strDate));
	strFormat.Format("%s건 / %s원", LF->GetMyNumberFormat(nCashCount), LF->GetMyNumberFormat(nCashCharge));
	AddItem(new CXTPGridRecordItemText(strFormat));
	strFormat.Format("%s건 / %s원", LF->GetMyNumberFormat(nCreditCount), LF->GetMyNumberFormat(nCreditCharge));
	AddItem(new CXTPGridRecordItemText(strFormat));
	strFormat.Format("%s건 / %s원", LF->GetMyNumberFormat(nOnlineCount), LF->GetMyNumberFormat(nOnlineCharge));
	AddItem(new CXTPGridRecordItemText(strFormat));
	strFormat.Format("%s건 / %s원", LF->GetMyNumberFormat(nTransCount), LF->GetMyNumberFormat(nTransCharge));
	AddItem(new CXTPGridRecordItemText(strFormat));
	strFormat.Format("%s건 / %s원", LF->GetMyNumberFormat(nCreditCount + nOnlineCount), LF->GetMyNumberFormat(nCreditCharge + nOnlineCharge + nTransCharge));
	AddItem(new CXTPGridRecordItemText(strFormat));
}

CAfterReportRecord::CAfterReportRecord(long nGNo)
{
	AddItem(new CXTPGridRecordItemText(m_cg.GetGroupData(nGNo)->strGroupName + "/" + m_cg.GetGroupData(nGNo)->strDept));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
}

CXTPGridCustomer::CXTPGridCustomer(BOOL bMain, ST_CUSTOMER_INFO *info)
{
	char buffer[10];

	AddItem(new CXTPGridRecordItemText(""));

	if(bMain) 
		AddItem(new CXTPGridRecordItemText(CString(itoa(info->nID, buffer, 10))));
	else
		AddItem(new CXTPGridRecordItemText(""));

	CString strTotalName;
	ST_CUSTOMER_GROUP_INFOMATION *groupinfo = m_cg.GetGroupData(info->nGNo);
	if(groupinfo != NULL)
		strTotalName = info->nGNo > 0 ? m_cg.GetGroupData(info->nGNo)->strTotalName : "";
	else
		strTotalName = "";

	AddItem(new CXTPGridRecordItemText(info->strCompany));
	AddItem(new CXTPGridRecordItemText(info->strName));
	AddItem(new CXTPGridRecordItemText(info->strDepart));
	AddItem(new CXTPGridRecordItemText(LF->GetDashPhoneNumber(info->strMobile)));

	CString strTemp = "";
	if(info->bCredit == 1) strTemp = "신용";
	else if(info->bCredit == 2) strTemp = "송금";
	else if(info->bCredit == 3) strTemp = "카드";

	AddItem(new CXTPGridRecordItemText(strTemp));
	AddItem(new CXTPGridRecordItemText(info->strUserID));
	AddItem(new CXTPGridRecordItemText(info->strLoginID));
	AddItem(new CXTPGridRecordItemText(info->strDong));
	AddItem(new CXTPGridRecordItemText(strTotalName));
	AddItem(new CXTPGridRecordItemText(info->strLocation));
	AddItem(new CXTPGridRecordItemText(CString(ltoa(info->nDiscount, buffer, 10))));

	info->bMain = bMain;
	m_info = info;
	m_dwData = (DWORD)info;
}

CGroupRecord::CGroupRecord(ST_CUSTOMER_GROUP_INFOMATION *st)
{
	CString sReportTerm, sReportTemp = "";
	if(st->nReportSecondDay > 0)
		sReportTerm.Format("%d,%d일", st->nReportFirstDay,st->nReportSecondDay);
	else
		sReportTerm.Format("%d일", st->nReportFirstDay);

	if(st->nReportFirstDay <= 0 && st->nReportSecondDay <= 0)
		sReportTerm = "";

	AddItem(new CXTPGridRecordItemText(st->strGroupName));
	AddItem(new CXTPGridRecordItemText(st->strDept));
	AddItem(new CXTPGridRecordItemText(sReportTerm));

	m_nGNo = st->nGNo;
	m_bSelect = FALSE;
	m_nActiveLevel = st->nActiveLevel;
	m_nCredit = st->nCredit;

	m_strSearchData = st->strGroupName + "%" + st->strDept + "%" + sReportTerm + "%";
}

void CGroupRecord::AddSearchData(ST_CUSTOMER_GROUP_INFOMATION *st)
{
	m_strSearchData += st->strGroupName + "%" + st->strDept + "%" + st->strName + "%";
}

void CGroupRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{ 
	CGroupRecord *pReocrd = (CGroupRecord*)pDrawArgs->pRow->GetRecord();

	if(pReocrd->m_nActiveLevel > 0)
		pItemMetrics->clrBackground = RGB(150, 150, 255);
	else
	{
		pItemMetrics->clrBackground = RGB(255, 255, 255);
	}

	if(pReocrd->m_nCredit > 0)
		pItemMetrics->clrForeground = RGB(255, 0, 0);
	else
		pItemMetrics->clrForeground = RGB(0, 0, 0);
}

CGroupReportRecord::CGroupReportRecord()
{
	m_strSearchData = "";
	m_strSearchDateData = "";
}

CGroupReportRecord::CGroupReportRecord(ST_CUSTOMER_GROUP_INFOMATION *st, BOOL bSumRecord)
{
	char buffer[10];
	AddItem(new CXTPGridRecordItemText(st->strGroupName));
	AddItem(new CXTPGridRecordItemText(st->strDept));
	AddItem(new CXTPGridRecordItemText(st->strName));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));

	m_nGNo = st->nGNo;
	m_bSumRecord = bSumRecord;
	m_strSearchData = st->strGroupName + "%" + st->strDept + "%" + st->strName + "%";
	m_strSearchDateData += "$" + (CString)itoa(st->nReportFirstDay, buffer, 10) + "%$" + (CString)itoa(st->nReportSecondDay, buffer, 10) + "%";

	//m_stGroup = m_cg.GetGroupData(st->nGNo);
	LF->InitGroupReportStruct(m_stGroup);
	m_stGroup.strGroupName = st->strGroupName;
	m_stGroup.strDept = st->strDept;
	m_stGroup.strName = st->strName;
	m_stGroup.nGNo = st->nGNo;
	m_bHasData = FALSE;

	//m_nReportTreeLevel = nReportTreeLevel;
}

CGroupReportRecord::CGroupReportRecord(GROUP_REPORT st, BOOL bSumRecord)
{
	LF->InitGroupReportStruct(m_stGroup);

	m_nGNo = st.nGNo;
	m_stGroup = st;
	m_stGroup.strGroupName = m_cg.GetGroupData(st.nGNo)->strGroupName;
	m_stGroup.strDept = m_cg.GetGroupData(st.nGNo)->strDept;
	m_stGroup.strName = m_cg.GetGroupData(st.nGNo)->strName;
	m_stGroup.nGNo = st.nGNo;
	m_bSumRecord = bSumRecord;
	m_bHasData = FALSE;		

	AddItem(new CXTPGridRecordItemText(m_stGroup.strGroupName));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
}

CGroupReportRecord::CGroupReportRecord(ST_GROUP_REPORT st)
{
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(st.nSumCount)));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(st.nCashCharge)));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(st.nCreditCharge)));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(st.nOnlineCharge)));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(st.nTransCharge)));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(st.nSumTotal)));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(st.nBillCollection)));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(st.nUnBillCollection)));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));

	m_nGNo = 0;
	m_nReportTreeLevel = 0;
	LF->InitGroupReportStruct(m_stGroup);
	m_bHasData = FALSE;
}

void CGroupReportRecord::AddSearchData(ST_CUSTOMER_GROUP_INFOMATION *st)
{
	char buffer[20];

	m_strSearchData += st->strGroupName + "%" + st->strDept + "%" + st->strName + "%";
	m_strSearchDateData += "$" + (CString)itoa(st->nReportFirstDay, buffer, 10) + "%$" + (CString)itoa(st->nReportSecondDay, buffer, 10) + "%";
}

void CGroupReportRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{ 
	CGroupReportRecord* pRecord = (CGroupReportRecord*)pDrawArgs->pRow->GetRecord();

	long nCol = pDrawArgs->pColumn->GetIndex();

	if(nCol == 12 || nCol == 16)
		pItemMetrics->clrForeground = RGB(0, 0 ,255);
	else if(nCol == 14 || nCol == 15)
		pItemMetrics->clrForeground = RGB(255, 0 ,0);
}

CSimpleGroupRecord::CSimpleGroupRecord(ST_CUSTOMER_GROUP_INFOMATION *st)
{
	CString sReportTerm;
	sReportTerm.Format("%d ~ %d", st->nReportFirstDay,st->nReportSecondDay);
	AddItem(new CXTPGridRecordItemText(st->strGroupName));
	AddItem(new CXTPGridRecordItemText(st->strDept));
	AddItem(new CXTPGridRecordItemText(st->strName));

	m_nGNo = st->nGNo;
	m_bSelect = FALSE;
	m_nActiveLevel = st->nActiveLevel;
	m_nCredit = st->nCredit;

	m_strSearchData = st->strGroupName + "%" + st->strDept + "%" + st->strName + "%";
}

void CSimpleGroupRecord::AddSearchData(ST_CUSTOMER_GROUP_INFOMATION *st)
{
	m_strSearchData += st->strGroupName + "%" + st->strDept + "%" + st->strName + "%";
}

void CSimpleGroupRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{ 
	CSimpleGroupRecord *pReocrd = (CSimpleGroupRecord*)pDrawArgs->pRow->GetRecord();

	if(pReocrd->m_nActiveLevel > 0)
		pItemMetrics->clrBackground = RGB(150, 150, 255);
	else
	{
		pItemMetrics->clrBackground = RGB(255, 255, 255);
	}

	if(pReocrd->m_nCredit > 0)
		pItemMetrics->clrForeground = RGB(255, 0, 0);
	else
		pItemMetrics->clrForeground = RGB(0, 0, 0);
}

CCustomerGroupRecord::CCustomerGroupRecord(ST_CUSTOMER_GROUP_INFOMATION *st)
{
	AddItem(new CXTPGridRecordItemText(st->strGroupName));
	AddItem(new CXTPGridRecordItemText(st->strDept));
	AddItem(new CXTPGridRecordItemText(st->strName));
	AddItem(new CXTPGridRecordItemNumber(st->nMembers));
	AddItem(new CXTPGridRecordItemText(st->strChargeName));

	AddItem(new CXTPGridRecordItemNumber(st->nUseCount));
	AddItem(new CXTPGridRecordItemNumber(st->nCancelCount));
	AddItem(new CXTPGridRecordItemText(st->dtLastUse.Format("%y-%m-%d")));
	AddItem(new CXTPGridRecordItemText(st->strEmail));
	AddItem(new CXTPGridRecordItemText(st->strDetail));

	char buffer[10];

	if(st->nAbleUseCharge > 0)
	{
		CString strTemp;
		strTemp.Format("%s / %d만원", LF->GetMyNumberFormat(st->nUseCharge), st->nAbleUseCharge);
		AddItem(new CXTPGridRecordItemText(strTemp));
		AddItem(new CXTPGridRecordItemText(CString(itoa(st->nInitDay, buffer, 10)) + "일"));
	}
	else
	{
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
	}

	//AddItem(new CXTPGridRecordItemText(st->sMemberTel))
	AddItem(new CXTPGridRecordItemText(st->strArea));
	m_nGNo = st->nGNo;
	m_nActiveLevel = st->nActiveLevel;
	m_nCredit = st->nCredit;

	AddSearchData(st);
}

void CCustomerGroupRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{ 
	CCustomerGroupRecord *pReocrd = (CCustomerGroupRecord*)pDrawArgs->pRow->GetRecord();

	if(pReocrd->m_nActiveLevel > 0)
		pItemMetrics->clrBackground = RGB(150, 150, 255);
	else
	{
		pItemMetrics->clrBackground = RGB(255, 255, 255);
	}

	if(pReocrd->m_nCredit > 0)
		pItemMetrics->clrForeground = RGB(255, 0, 0);
	else
		pItemMetrics->clrForeground = RGB(0, 0, 0);
}

void CCustomerGroupRecord::AddSearchData(ST_CUSTOMER_GROUP_INFOMATION *st)
{
	m_strSearchData += st->strGroupName + "%" + st->strDept + "%" + LF->GetMyNumberFormat(st->nReportFirstDay) + "%";
}

CGroupRecord24::CGroupRecord24(ST_CUSTOMER_GROUP_INFOMATION *st)
{
	CString strReportTerm;
	strReportTerm.Format("%d ~ %d", st->nReportFirstDay,st->nReportSecondDay);
	AddItem(new CXTPGridRecordItemText(st->strGroupName));
	AddItem(new CXTPGridRecordItemText(st->strDept));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(st->nReportFirstDay) + "일"));


	m_nGNo = st->nGNo;
	m_bSelect = FALSE;
	m_nActiveLevel = st->nActiveLevel;
	m_nCredit = st->nCredit;
	
	AddSearchData(st);
}

void CGroupRecord24::AddSearchData(ST_CUSTOMER_GROUP_INFOMATION *st)
{
	m_strSearchData += st->strGroupName + "%" + st->strDept + "%" + st->strName + "%";
}

void CGroupRecord24::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{ 
	CGroupRecord24 *pReocrd = (CGroupRecord24*)pDrawArgs->pRow->GetRecord();

	if(pReocrd->m_nActiveLevel > 0)
		pItemMetrics->clrBackground = RGB(150, 150, 255);
	else
		pItemMetrics->clrBackground = RGB(255, 255, 255);

	if(pReocrd->m_nCredit > 0)
		pItemMetrics->clrForeground = RGB(255, 0, 0);
	else
		pItemMetrics->clrForeground = RGB(0, 0, 0);
}

CGroupReportRecord24::CGroupReportRecord24()
{
	m_strSearchData = "";
	m_strSearchDateData = "";
}

CGroupReportRecord24::CGroupReportRecord24(ST_CUSTOMER_GROUP_INFOMATION *st, BOOL bSumRecord)
{
	char buffer[10];
	AddItem(new CXTPGridRecordItemText(st->strGroupName));
	AddItem(new CXTPGridRecordItemText(st->strDept));
	AddItem(new CXTPGridRecordItemText(st->strName));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));

	m_nGNo = st->nGNo;
	m_bSumRecord = bSumRecord;
	m_strSearchData = st->strGroupName + "%" + st->strDept + "%" + st->strName + "%";
	m_strSearchDateData += "$" + (CString)itoa(st->nReportFirstDay, buffer, 10) + "%$" + (CString)itoa(st->nReportSecondDay, buffer, 10) + "%";

	LF->InitGroupReportStruct(m_stGroup);
	m_stGroup.strGroupName = st->strGroupName;
	m_stGroup.strDept = st->strDept;
	m_stGroup.strName = st->strName;
	m_stGroup.nGNo = st->nGNo;
	m_bHasData = FALSE;
}

CGroupReportRecord24::CGroupReportRecord24(GROUP_REPORT st, BOOL bSumRecord)
{
	LF->InitGroupReportStruct(m_stGroup);

	m_nGNo = st.nGNo;
	m_stGroup = st;
	m_stGroup.strGroupName = m_cg.GetGroupData(st.nGNo)->strGroupName;
	m_stGroup.strDept = m_cg.GetGroupData(st.nGNo)->strDept;
	m_stGroup.strName = m_cg.GetGroupData(st.nGNo)->strName;
	m_stGroup.nGNo = st.nGNo;
	m_bSumRecord = bSumRecord;
	m_bHasData = FALSE;		

	AddItem(new CXTPGridRecordItemText(m_stGroup.strGroupName));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
}

CGroupReportRecord24::CGroupReportRecord24(ST_GROUP_REPORT st)
{
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(st.nSumCount)));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(st.nCashCharge)));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(st.nCreditCharge)));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(st.nOnlineCharge)));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(st.nTransCharge)));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(st.nSumTotal)));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(st.nBillCollection)));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(st.nUnBillCollection)));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));

	m_nGNo = 0;
	m_nReportTreeLevel = 0;
	LF->InitGroupReportStruct(m_stGroup);
	m_bHasData = FALSE;
}

void CGroupReportRecord24::AddSearchData(ST_CUSTOMER_GROUP_INFOMATION *st)
{
	char buffer[10];

	m_strSearchData += st->strGroupName + "%" + st->strDept + "%" + st->strName + "%";
	m_strSearchDateData += "$" + (CString)itoa(st->nReportFirstDay, buffer, 10) + "%$" + (CString)itoa(st->nReportSecondDay, buffer, 10) + "%";
}

void CGroupReportRecord24::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{  
	CGroupReportRecord24* pRecord = (CGroupReportRecord24*)pDrawArgs->pRow->GetRecord();

	long nCol = pDrawArgs->pColumn->GetIndex();

	if(pRecord == NULL) return;

	if(nCol == 6 || nCol == 7 || nCol == 8)
	{
		pItemMetrics->clrForeground = RGB(0, 0 ,255);
	}
	else if(nCol == 4 || nCol == 5)
	{
		pItemMetrics->clrForeground = RGB(255, 0 ,0);
	}
}

CMileageRecord::CMileageRecord()
{
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CMileageTelText(""));
	AddItem(new CMileageTelText(""));
	AddItem(new CXTPGridRecordItemText(""));	
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CMileageNumber(0));
	AddItem(new CXTPGridRecordItemText(""));		
}

CMileageRecord::CMileageRecord(CString strCName, CString strTel1, CString strTel2,long nCustomerGroup, int nType, long nUseCount, long nMileage, long nCNo, CString strMileageType)
{				
	CString strType = nType == 0  ? "일반" : "업소";

	AddItem(new CXTPGridRecordItemText(strCName));
	AddItem(new CMileageTelText(strTel1));
	AddItem(new CMileageTelText(strTel2));
	AddItem(new CXTPGridRecordItemText(m_cg.GetGroupData(nCustomerGroup)->strGroupName));	
	AddItem(new CXTPGridRecordItemText(strType));
	AddItem(new CMileageNumber(nUseCount));
	AddItem(new CMileageNumber(nMileage));	
	AddItem(new CXTPGridRecordItemText(strMileageType));	

	m_nCNo = nCNo;	
	m_bDirtyFlag = FALSE;
	m_strData[0] = strCName;
	m_strData[1] = LF->GetDashPhoneNumber(strTel1);
	m_strData[2] = LF->GetDashPhoneNumber(strTel2);
	m_strData[3] = m_cg.GetGroupData(nCustomerGroup)->strGroupName;
	m_strData[4] = strType;
	m_strData[5] = LF->GetMyNumberFormat(nUseCount);
	m_strData[6] = LF->GetMyNumberFormat(nMileage);		
	m_strData[7] = strMileageType;		
}

CUnBillRecord::CUnBillRecord(long nGNo, COleDateTime dtGenerate, long nID, long nAccount, long nBalance, CString strType,
	COleDateTime dtReportStart, COleDateTime dtReportEnd, COleDateTime dtBillCollEction, COleDateTime dtPayMent, COleDateTime dtInputDebit,
	CString sSendEmail,CString sWName,CString sEtc ,long nReceivableAmount, long nUnCollection,long nIndex,BOOL bCancel, BOOL bSUm)
{
	COleDateTime dtNow(COleDateTime::GetCurrentTime());
	COleDateTimeSpan dtSpan;
	CString strIncomeDate = "", strInputDebit = "";
	if(dtPayMent.GetStatus() == COleDateTime::valid && dtPayMent.m_dt > 0 )
	{
		dtSpan = dtPayMent - dtNow;
		if(dtSpan.GetDays() < 0)
			strIncomeDate.Format("%02d-%02d,(%d일)", dtPayMent.GetMonth(), dtPayMent.GetDay(),dtSpan.GetDays());
		else
			strIncomeDate.Format("%02d-%02d", dtPayMent.GetMonth(), dtPayMent.GetDay());

	}
	if(dtInputDebit.GetStatus() == COleDateTime::valid && dtInputDebit.m_dt > 0)
	{
		strInputDebit.Format("%02d-%02d", dtInputDebit.GetMonth(), dtInputDebit.GetDay());
	}


	if(bSUm)
	{
		CString strFormat= "";
		strFormat.Format("%s ~ %s", dtReportStart.Format("%m-%d"), dtReportEnd.Format("%m-%d"));
		
		AddItem(new CXTPGridRecordItemText(strFormat));
		AddItem(new CXTPGridRecordItemCheck(FALSE));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText("미수금액 :"));
		AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(nBalance))); 

		AddItem(new CXTPGridRecordItemText(strIncomeDate)); 
		AddItem(new CXTPGridRecordItemText(sSendEmail)); 
		AddItem(new CXTPGridRecordItemText(strInputDebit)); 
		AddItem(new CXTPGridRecordItemText(sWName)); 
		AddItem(new CXTPGridRecordItemText(sEtc)); 
		

		
		
		m_strDate.Format("%s ~ %s", dtReportStart.Format("%m-%d"), dtReportEnd.Format("%m-%d"));
	}
	else
	{
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(dtGenerate.Format("%m-%d %H:%M:%S")));		
		AddItem(new CXTPGridRecordItemText(strType));
		AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(nAccount)));
		AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(nBalance)));
		AddItem(new CXTPGridRecordItemText(""));  // strIncomeDate
		AddItem(new CXTPGridRecordItemText(""));  // sSendEmail
		AddItem(new CXTPGridRecordItemText("")); 
		AddItem(new CXTPGridRecordItemText(sWName)); 
		AddItem(new CXTPGridRecordItemText(sEtc)); 

		
	}
	m_nUnBill = nBalance;
	m_nID = nID;
	m_nIndex = nIndex;
	m_nGNo = nGNo;
	m_strEtc = sEtc;
	m_nReceivableAmount = nReceivableAmount;
	m_nUnCollection = nUnCollection;
	m_strType = strType;
	m_bCancel = bCancel;
}

CUnBillRecord::CUnBillRecord(long nGNo)
{
	AddItem(new CXTPGridRecordItemText(m_cg.GetGroupData(nGNo)->strGroupName + "/" + m_cg.GetGroupData(nGNo)->strDept));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));

	m_nID = 0;
	m_nGNo = nGNo;
	m_strType = "";
	m_nIndex = 0;
	m_bCancel = FALSE;
}

CRiderRecord::CRiderRecord(CString strDate, CString strWeather, CString strWorkTime, 
						   CString strChargeType, CString strCreditType, CString strAllCount, BOOL bAbsence)
{
	AddItem(new CXTPGridRecordItemText(strDate));
	AddItem(new CXTPGridRecordItemText(strWeather));

	if(bAbsence)
	{
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));

	}
	else
	{
		AddItem(new CXTPGridRecordItemText(strWorkTime));
		AddItem(new CXTPGridRecordItemText(strChargeType));
		AddItem(new CXTPGridRecordItemText(strCreditType));
		AddItem(new CXTPGridRecordItemText(strAllCount));
	}	

	m_strWorkTime = strWorkTime;
	m_strChargeType = strChargeType;
	m_strCreditType = strCreditType;
	m_strAllCount = strAllCount;
}



CUpdateBoardRecord::CUpdateBoardRecord(long nTNo, 
		COleDateTime dtGenerate,
		long nWNo,
		long nWCompany,
		long nParentID,
		CString strWName,
		CString strMessage,
		CString strLogiStaffName)
{
	char buffer[10];
	m_nTNo = nTNo;
	m_dt = dtGenerate;
	m_nWNo = nWNo;
	m_nWCompany = nWCompany;
	m_nTNo = nTNo;
	m_nParentID = nParentID;

	if(nParentID == 0)
		AddItem(new CXTPGridRecordItemText(itoa(nTNo, buffer, 10)));
	else
		AddItem(new CXTPGridRecordItemText(""));

	AddItem(new CXTPGridRecordItemText(dtGenerate.Format("%m-%d %H:%M:%S")));

	if(strLogiStaffName.GetLength() > 0)
		AddItem(new CXTPGridRecordItemText("로지소프트"));
	else
		AddItem(new CXTPGridRecordItemText(strWName));

	AddItem(new CXTPGridRecordItemText(strMessage));

	if(nParentID == 0)
		AddItem(new CXTPGridRecordItemText("답글"));
	else
		AddItem(new CXTPGridRecordItemText(""));
}

void CUpdateBoardRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{  
	if(pDrawArgs->pColumn && pDrawArgs->pRow)
	{
		int nCol = pDrawArgs->pColumn->GetItemIndex();
		int nRow = pDrawArgs->pRow->GetIndex();
		CUpdateBoardRecord *pRecord = ((CUpdateBoardRecord*)pDrawArgs->pRow->GetRecord());

		COleDateTime dtCur = COleDateTime::GetCurrentTime();
		COleDateTimeSpan span = dtCur - pRecord->m_dt;

		long nHour = span.GetTotalHours();
		long nMinute = span.GetTotalMinutes(); 
		long nSecond = span.GetTotalSeconds(); 

		if(dtCur.GetYear() == pRecord->m_dt.GetYear() &&
			dtCur.GetMonth() == pRecord->m_dt.GetMonth() &&
			dtCur.GetDay() == pRecord->m_dt.GetDay()) //같은날
		{
			if(nCol == 1)
			{ 
				if(nSecond < 60)
					pItemMetrics->strText.Format("%d초전", nSecond);
				else if(nMinute < 60)
					pItemMetrics->strText.Format("%d분전", nMinute);
				else if(nHour < 12)
					pItemMetrics->strText.Format("%d시간전", nHour);
				else
					pItemMetrics->strText = pRecord->m_dt.Format("%m-%d %H:%M");
			}		

			CString strTemp = pRecord->GetItem(3)->GetCaption(NULL);

			if(strTemp.Find("┗") > 0)
				pItemMetrics->clrBackground = RGB(0xFF, 0xFF, 0x99); 
			else
				pItemMetrics->clrBackground = RGB(230, 255, 230);

			pItemMetrics->pFont = &pDrawArgs->pControl->GetPaintManager()->m_fontBoldText;

		}
		else
		{  
			if(nCol == 1)
				pItemMetrics->strText = pRecord->m_dt.Format("%m-%d %H:%M");
		}

		if(nCol == 4)
			pItemMetrics->clrForeground = RGB(0, 0, 255);

		if(nCol == 3 && pItemMetrics->strText == "로지소프트")
			pItemMetrics->clrForeground = RGB(0, 0, 255);
	}
}

CWantTransferRecord::CWantTransferRecord(long nID, long nToCompany, CString sMemo, long nState, COleDateTime dtRequest,
										 long nRequestCharge, COleDateTime dtReceive, long nReceiveCharge, CString strReceiveMessage)
{
	m_nState = nState;

	AddItem(new CXTPGridRecordItemNumber(nID));
	AddItem(new CXTPGridRecordItemCompanyNumber(nToCompany));
	AddItem(new CXTPGridRecordItemText(sMemo));
	AddItem(new CXTPGridRecordItemStateNumber(nState));
	AddItem(new CXTPGridRecordItemMyDate(dtRequest));
	AddItem(new CXTPGridRecordItemChargeNumber(nRequestCharge));
	AddItem(new CXTPGridRecordItemMyDate(dtReceive));
	AddItem(new CXTPGridRecordItemChargeNumber(nReceiveCharge));
	AddItem(new CXTPGridRecordItemText(strReceiveMessage));
}

void CWantTransferRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nRow = this->GetIndex();
	int nCol = pDrawArgs->pColumn->GetItemIndex();

	CXTPGridRecord *pRecord = pDrawArgs->pRow->GetRecord();	
	long nState = ((CWantTransferRecord*)pRecord)->m_nState;

	if(nState == 1)
		pItemMetrics->clrBackground = RGB(245, 245, 230);
	else if(nState == 3 || nState == 4)
		pItemMetrics->clrBackground = RGB(245, 230, 245);
	else
		pItemMetrics->clrBackground = RGB(230, 245, 245);
}


CAllianceRecord::CAllianceRecord(long nAllianceID, CString strAllianceName)
{
	AddItem(new CXTPGridRecordItemText(strAllianceName));
	AddItem(new CCountRecordItem("0"));
	m_nAllianceID = nAllianceID;
	m_strAllianceName = strAllianceName;
}

BOOL CMyRecord::GetDirtyFlag()
{
	CRcpRateRecordItem *pRecordItem = (CRcpRateRecordItem*)GetItem(4);
	return pRecordItem->m_bDirtyFlag;
}

BOOL CMyRecord::GetShareTimeDirtyFlag()
{
	CShareTimeRecordItem *pRecordItem = (CShareTimeRecordItem*)GetItem(7);
	return pRecordItem->m_bDirtyFlag;
}

long CMyRecord::GetShareTimeA()
{
	CShareTimeRecordItem *pRecordItem = (CShareTimeRecordItem*)GetItem(7);
	return pRecordItem->GetValue();
}

BOOL CMyRecord::CheckAllianceID(long nAllianceID)
{
	return (m_nAllianceID == nAllianceID);
}

long CMyRecord::GetRcpRate()
{
	CRcpRateRecordItem *pRecordItem = (CRcpRateRecordItem*)GetItem(4);
	return pRecordItem->GetValue();
}

CMyRecord::CMyRecord(COleDateTime dtGenerate,CString sState,long nDeposit,long nBalance,CString sEtc, long nTrafficPenalty)
{
	m_nShareReportTabIdx = 1;
	AddItem(new CMyDateRecordItem(dtGenerate));
	AddItem(new CXTPGridRecordItemText(sState));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(nDeposit)));
	AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(nBalance)));
	AddItem(new CXTPGridRecordItemText(sEtc));

	m_nTrafficPenalty = nTrafficPenalty;
	if(nTrafficPenalty > 0)
	{
		CXTPGridRecordItem *pItem = AddItem(new CXTPGridRecordItemText("첨부클릭"));
		pItem->AddHyperlink(new CXTPGridHyperlink(0,0xFFFF));
	}
	else
	{
		AddItem(new CXTPGridRecordItemText(""));
	}
}

void CMyRecord::GetItemMetrics_1(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	if(1 == m_nShareReportTabIdx)
	{
		CString strItem = GetItem(2)->GetCaption(NULL);
		strItem.Replace(",", "");
		long lVal = atol(strItem); 
		//long lVal = (long)((CXTPGridRecordItemNumber*)GetItem(2))->GetValue();
		if( lVal < 0)
		{
			pItemMetrics->clrForeground = RGB(0, 0, 0);
			pItemMetrics->clrBackground = RGB(255, 222, 222);
		}
		else
		{
			pItemMetrics->clrForeground = RGB(0, 0, 0);
			pItemMetrics->clrBackground = RGB(222, 222, 255);
		}

		int nCol = pDrawArgs->pColumn->GetIndex();
		if(nCol == 2 || nCol == 3)
		{
			pDrawArgs->nTextAlign = 2;
		}

		return;
	}
}