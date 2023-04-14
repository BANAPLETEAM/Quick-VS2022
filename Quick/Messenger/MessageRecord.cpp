// MessageRecord.cpp: implementation of the CMessageRecord class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "MessageRecord.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMessageRecord::CMessageRecord(long nShareCode1, long nCompany, long nMNo, 
					CString strCompany, CString strBranch, CString strName, 
					COleDateTime dtTime, int nStatus, int nClientType)
{
	if(nClientType == 0)
	{
		AddItem(new CXTPGridRecordItemText(strBranch));
		AddItem(new CXTPGridRecordItemNumber(nShareCode1 == 200 || nClientType >= 1 ? 0 : nMNo));
		AddItem(new CXTPGridRecordItemText(strName));
		//AddItem(new CXTPGridRecordItemText(nStatus > 0 ? "오프" : "온라인"));
	}
	else
	{
		CString strTemp = strBranch;
		if(strName.GetLength() > 0)
			strTemp = strBranch + "/" + strName;

		AddItem(new CXTPGridRecordItemText(strCompany));
		AddItem(new CXTPGridRecordItemNumber(nShareCode1 == 200 || nClientType >= 1 ? 0 : nMNo));
		AddItem(new CXTPGridRecordItemText(strTemp));
		//AddItem(new CXTPGridRecordItemText(nStatus > 0 ? "오프" : "온라인"));
	}


	CStatusRecordItem *pStatus = (CStatusRecordItem*)AddItem(new CStatusRecordItem(nStatus));
	pStatus->SetStatus(nStatus);

	m_nShareCode1 = nShareCode1;
	m_strCompanyName = strCompany;
	m_strBranchName = strBranch;
	m_strName = strName;
	m_nCompany = nCompany;
	m_nMNo = nMNo;
	m_nStatus = nStatus;
	m_bExistFlag = TRUE;
#ifdef _QUICK
	m_nClientType = nClientType;
#else 
	m_nClientType = 0;
#endif
}

CMessageRecord::~CMessageRecord()
{

}

void CMessageRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	CXTPGridRecord::GetItemMetrics(pDrawArgs, pItemMetrics);
}



CMessageTitleRecord::CMessageTitleRecord(long nShareCode1, CString strCompany, int nClientType)
{
	AddItem(new CXTPGridRecordItemText(strCompany));
	AddItem(new CCountRecordItem("0"));
	m_nShareCode1 = nShareCode1;
	m_strCompanyName = strCompany;
#ifdef _QUICK
	m_nClientType = nClientType;
#else 
	m_nClientType = 0;
#endif
}

CMessageTitleRecord::~CMessageTitleRecord()
{

}

void CMessageTitleRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	CXTPGridRecord::GetItemMetrics(pDrawArgs, pItemMetrics);
}

