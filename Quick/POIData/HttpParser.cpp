#include "StdAfx.h"
#include "resource.h"
#include "NaverHttpParser.h"
#include "MkLock.h"
#include "SearchPOIDlg.h"
#include "SimpleMapDlg.h"
#include "LogiUtil.h"
#include "LogiMapNew.h"
#include "POIDataNew.h"
#include "libjson.h"
#include <wininet.h>
#include "afxinet.h"




CHttpParser::CHttpParser(void)
{
	m_hQueryHandle = NULL;
	m_hExitHandle = NULL;
	m_hThreadDiedHandle = NULL;
	m_bThreadLive = FALSE;
}

CHttpParser::~CHttpParser(void)
{
	if(m_hQueryHandle)
	{
		if(m_bThreadLive)
		{ 
			SetEvent(m_hExitHandle);
			WaitForSingleObject(m_hThreadDiedHandle, 2000);
		}

		if(m_hQueryHandle)
			CloseHandle(m_hQueryHandle);
		if(m_hExitHandle)
			CloseHandle(m_hExitHandle);
		if(m_hThreadDiedHandle)
			CloseHandle(m_hThreadDiedHandle);
	}
}

void CHttpParser::SetCenterPos(long nPosX, long nPosY)
{
	if(nPosY < 100000000)
	{
		nPosX = nPosX / 0.36;
		nPosY = nPosY / 0.36;
	}

	m_strCenterPosX.Format("%0.7f", (float)nPosX / 1000000.0);
	m_strCenterPosY.Format("%0.7f", (float)nPosY / 1000000.0);
}

void CHttpParser::ThreadRefresh(CString strKeyword, CWnd *pTarget, long nUID, BOOL bSearchPhone, int nDebugPrintType)
{
	if(!m_hQueryHandle)
	{
		m_hQueryHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
		m_hExitHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
		m_hThreadDiedHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
	}

	if(!m_bThreadLive)
	{
		m_bThreadLive = TRUE;

		DWORD dwThreadID1;
		HANDLE hThread1=::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) staticQueryProc,
			(LPVOID) this, 0, &dwThreadID1);
		CloseHandle(hThread1);
	}

	
	{
		CMkLock lock(&m_cs);
		m_QueryInfo.strKeyword = strKeyword;
		m_QueryInfo.nDebugPrintType = nDebugPrintType;
		m_QueryInfo.pTarget = pTarget;
		m_QueryInfo.nUID = nUID;
		m_QueryInfo.strCenterPosX = m_strCenterPosX;
		m_QueryInfo.strCenterPosY = m_strCenterPosY;
		m_QueryInfo.bPhoneSearchAutoComplete = bSearchPhone;
		m_QueryInfo.bPhoneSearch = bSearchPhone || LF->IsPhoneNumber(strKeyword);
	}
	
	SetEvent(m_hQueryHandle);
}

UINT CHttpParser::QueryProc(LPVOID lParam)
{
	HANDLE hWaitObject[2];
	hWaitObject[0] = m_hQueryHandle;
	hWaitObject[1] = m_hExitHandle;

	CHttpParser *pParser = (CHttpParser*)lParam;

	while(1)
	{
		DWORD dwWaitResult = WaitForMultipleObjects(2, hWaitObject, FALSE, 5000);

		if(dwWaitResult == WAIT_OBJECT_0)
		{
			QUERY_INFO QI;
	
			{
				CMkLock lock(&m_cs);
				QI = m_QueryInfo;
				m_QueryInfo.strKeyword.Empty();
			}

			if(!QI.strKeyword.IsEmpty())
				Refresh2(QI);
				//Refresh(QI);
		}
		else if(dwWaitResult == WAIT_OBJECT_0 + 1)
		{
			break;
		}
	}

	m_bThreadLive = FALSE;
	SetEvent(m_hThreadDiedHandle);
	return 0;
}

JSONNODE*	ParseJSON4NaverLocal(JSONNODE *n,const char* szNodeName);
void		ParseJSON4NaverLocalArray(JSONNODE *n,vector<SEARCH_RESULT_INFO>& vec );



void CHttpParser::Refresh2(QUERY_INFO &QI)
{
	
}


void CHttpParser::Analyze2(QUERY_INFO &QI, vector<SEARCH_RESULT_INFO>& vec)
{
	g_bana_log->Print("%d nCount", vec.size());

	vector<SEARCH_RESULT_INFO>::iterator it = vec.begin();
	
	for(;it != vec.end() ; it++)
	{
		AnalyzeDetail2(QI, (*it)) ;

	}

	//if(vec.size() > 0)
	//{
		QUERY_INFO *pQI = new QUERY_INFO;
		*pQI = QI;
		QI.pTarget->PostMessage(WM_USER + 999, 0, (LPARAM)pQI);
	//} 
}

BOOL CHttpParser::AnalyzeDetail2(QUERY_INFO &QI, SEARCH_RESULT_INFO& st)
{

	CString strName = st.name_val.c_str();
	int len = strName.GetLength();
	if( len > 0)
	{
		if(len > 28) {
			CString temp = strName;
			while (len > 28) {
				CString i = temp.Right(2);
				if (!LF->IsHangul(i))
					temp = temp.Mid(0, len-1);
				else
					temp = temp.Mid(0, len-2);

				len = temp.GetLength();
			}

			st.name_val = temp;
		}

		if(QI.nDebugPrintType & DEBUG_PRINT_LAST)
		{
			//g_bana_log->Print("%s, %s\n%s, %s\n%s\n--------------------------------------\n", 
			//	st.name_val.c_str(), st.tel_val.c_str(), st.x_val.c_str(),st.y_val.c_str(),st.address_val.c_str() );
		}

		//해당 핸들이 실제 살아있는지 체크하는 맵이 있어야 런타임에러 안남
		if(QI.pTarget && QI.pTarget->GetSafeHwnd())
			return MakePortalRecord2(QI,st);
	}

	return FALSE;
}

BOOL CHttpParser::MakePortalRecord2(QUERY_INFO &QI,SEARCH_RESULT_INFO& st)
{
	CPOIUnit *pDong = m_poiNew.SearchDong(st.address_val.c_str());
	if(!pDong)
	{
		g_bana_log->Print("동인식안됨) %s, %s\n", st.name_val.c_str(),st.address_val.c_str());
		return FALSE;
	}

	CString strlon = st.x_val.c_str();
	CString strlat = st.y_val.c_str();

	//long nPosX = atof((LPSTR)(LPCSTR)lat.GetData()) * 1000000;
	//long nPosY = atof((LPSTR)(LPCSTR)lon.GetData()) * 1000000;

	long nPosX = atof((LPSTR)(LPCSTR)strlon) * 1000000;
	long nPosY = atof((LPSTR)(LPCSTR)strlat) * 1000000;

	CLogiMapNew *pMap = LU->GetSimpleMap()->GetMap();
	pMap->WGS84ToBessel(nPosX, nPosY); 
	pMap->IsPosUsable(nPosX, nPosY, 0, FALSE); 

	CString strAddress = st.address_val.c_str();
	m_poiNew.AddressExceptionReplace(strAddress);

	//g_bana_log->Print("%s <-> %s\n", m_poiNew.AddressToLongName(pDong->GetRegionName()), strAddress);
	strAddress.Replace(m_poiNew.AddressToLongName(pDong->GetRegionName()), "");
	strAddress.Replace(pDong->GetRegionName(), "");
	strAddress.Trim();

	CSearchPOI *pSearchPOI = new CSearchPOI;
	pSearchPOI->pPOI = m_poiNew.NewPOI(QI.nUID, pDong, nPosX, nPosY, st.name_val.c_str(), 
		LF->GetNoneDashNumber(st.tel_val.c_str()));
	pSearchPOI->pNearPOI = m_poiNew.GetNearMainPOI(pSearchPOI->pPOI);
	pSearchPOI->pDongMatchPOI = pDong;
	pSearchPOI->bPhoneMatch = QI.bPhoneSearch ? true : false;
	pSearchPOI->strAddress = strAddress;
	pSearchPOI->bWebSearch = TRUE;

	PORTAR_RESULT_RECORD *pRecord = new PORTAR_RESULT_RECORD;
	pRecord->QI = QI; 
	pRecord->pSearchPOI = pSearchPOI;
	QI.pTarget->PostMessage(WM_USER + 999, (WPARAM)pRecord);

	return TRUE;
}

void CHttpParser::ParseJSON4NaverLocalValues(CString strHtml, vector<SEARCH_RESULT_INFO> *vec)
{   
}
