
#include "StdAfx.h"
#include "resource.h"
#include "LogiMapCns.h"
#include "SimpleMapDlg.h"
#include "MkLock.h"
#include "INaviPathSearch.h"
#include "EksysPath.h"


#define DEPTH_DISTANCE	200

long CLogiMapCns::m_nLastCnsTick = 0;


CLogiMapCns::CLogiMapCns(CSimpleMapDlg *pMap)
{
	m_pSimpleMapDlg = pMap;

	m_hRoutingHandle = NULL;
	m_hExitHandle = NULL;
	m_hThreadDiedHandle = NULL;

	m_ptCnsS = CPoint(0, 0);
	m_ptCnsD = CPoint(0, 0);
	m_nCnsDistance = 0;
	m_bRoutingThreadLive = FALSE;
	m_bCNSShowMap = FALSE;
	m_bCNSApplyVia = FALSE;
	m_pwndTarget = NULL;
	m_nModifyPoiConfirmCharge = FALSE;
	m_bChargeCalulate = FALSE;
	m_pOnceUseMap = NULL;
	m_nCnsSearchType1 = 0; 
	m_nCnsSearchType2 = 0;
	m_nCnsSearchPaid = 0;
}

CLogiMapCns::~CLogiMapCns(void)
{
	Close();
}

void CLogiMapCns::Close()
{
	if(m_hRoutingHandle)
	{
		if(m_bRoutingThreadLive)
		{
			SetEvent(m_hExitHandle);
			WaitForSingleObject(m_hThreadDiedHandle, 2000);
		}

		if(m_hRoutingHandle)
			CloseHandle(m_hRoutingHandle);
		if(m_hExitHandle)
			CloseHandle(m_hExitHandle);
		if(m_hThreadDiedHandle)
			CloseHandle(m_hThreadDiedHandle);
	}
}


BOOL CLogiMapCns::GetRouteDistance(CWnd *pwndTarget, BOOL bShowMap, BOOL bViaApply,BOOL bChargeCalulate, int nModifyPoiConfirmCharge, BOOL bShowImage, long nCompany, BOOL bBicycle)
{
	if(!m_hRoutingHandle)
	{  
		m_hRoutingHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
		m_hExitHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
		m_hThreadDiedHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
	}

	this->m_nModifyPoiConfirmCharge = nModifyPoiConfirmCharge; 
	this->m_bChargeCalulate = bChargeCalulate;
	this->m_bShowImage = bShowImage; 
	this->m_bBicycle = bBicycle; 

	m_ci.GetCNsInfo(nCompany, m_nCnsSearchType1, m_nCnsSearchType2, m_nCnsSearchPaid);

	if(!m_bRoutingThreadLive)
	{
		m_bRoutingThreadLive = TRUE;	


		DWORD dwThreadID1;
		HANDLE hThread1=::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) staticRoutingProc,
			(LPVOID) this, 0, &dwThreadID1);
		CloseHandle(hThread1);
	}

	CMkLock lock(m_cs);
	m_pwndTarget = pwndTarget;
	if(m_aryCNSPoint.GetCount() >= 2)
	{
		m_bCNSShowMap = bShowMap;
		m_bCNSApplyVia = bViaApply;
		SetEvent(m_hRoutingHandle);
		return TRUE;
	}

	return FALSE;
}

UINT CLogiMapCns::RoutingProc(LPVOID lParam)
{
	HANDLE hWaitObject[2];
	hWaitObject[0] = m_hRoutingHandle;
	hWaitObject[1] = m_hExitHandle;


	CLogiMapCns *pLogiMapCNS = (CLogiMapCns *)lParam;

	while(1)
	{
		DWORD dwWaitResult = WaitForMultipleObjects(2, hWaitObject, FALSE, 5000);

		if(dwWaitResult == WAIT_OBJECT_0)
		{
			if(pLogiMapCNS)
			{
				GetRouteDistanceThreadEksys(m_bCNSShowMap, m_bCNSApplyVia, pLogiMapCNS->m_bChargeCalulate,
					pLogiMapCNS->m_nModifyPoiConfirmCharge);
			}			
		}
		else if(dwWaitResult == WAIT_OBJECT_0 + 1)
		{
			break;
		}
	}

	m_bRoutingThreadLive = FALSE;
	SetEvent(m_hThreadDiedHandle);
	return 0;
}


BOOL CLogiMapCns::GetRouteDistanceThreadEksys(BOOL bShowMap,  BOOL bViaApply, 
											  BOOL bChargeCalculate, int  nModifyPoiConfirmCharge)
{
	CLogiMapNew *pMap = m_pOnceUseMap ? m_pOnceUseMap : m_pSimpleMapDlg->GetMap();
	CWnd *pwndStartTarget = NULL;

	CMkLock lock(m_cs);
	pwndStartTarget = m_pwndTarget;

	if(m_aryCNSPoint.GetSize() < 2) {
		return FALSE;
	}

	CEksysPath c(!bShowMap);

	for(int i = 0; i<(int)m_aryCNSPoint.GetSize(); i++)
	{
		long nViaX = m_aryCNSPoint.GetAt(i).x / 0.36;
		long nViaY = m_aryCNSPoint.GetAt(i).y / 0.36;

		// X, Y 좌표가 바뀌어서 나오는 경우 있음...
		if (nViaX < nViaY) {
			swap(nViaX, nViaY);
		}

		pMap->BesselToWGS84(nViaX, nViaY);
		c.AddPos(nViaX, nViaY);
	}

	if(m_bBicycle || LF->IsThisCompany("퀵짱", m_nCompany))
		c.SetRouteType("Shortest");

	BOOL bSuccess = FALSE;
	float fDistance = 0;

	if(bShowMap == TRUE) //지도보기
	{
		vector<CPoint> vec;
		long nDistance = c.GetRouteDistance(vec);

		if(nDistance > 0)
			bSuccess = TRUE;

		fDistance = nDistance / 1000.0;

		if(bSuccess)
		{
			if(m_pOnceUseMap)
			{ 
				//m_pOnceUseMap->MoveMap(m_ptCenter.x, m_ptCenter.y);
				//m_pOnceUseMap->SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
			}
			else
			{
				m_pSimpleMapDlg->ShowWindow(SW_SHOW);
				m_pSimpleMapDlg->SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
				pMap->DrawRouteInfo(&vec, &m_aryCNSPoint);
			}
		}		
	}
	else
	{
		long nDistance = c.GetRouteDistance();

		if(nDistance > 0)
			bSuccess = TRUE;

		fDistance = nDistance / 1000.0;
	}

	m_pOnceUseMap = NULL;

	double* pfDistance = new double;
	*pfDistance = fDistance;

	if(m_pwndTarget && m_pwndTarget == pwndStartTarget)
	{
		if(!bChargeCalculate )
			nModifyPoiConfirmCharge += 10; // 거리계산만

		m_pwndTarget->PostMessage(bViaApply ? (WM_USER + 5656) : (WM_USER + 6000), (WPARAM)pfDistance,(LPARAM)nModifyPoiConfirmCharge);
	}
	else
	{
		delete pfDistance;
		pfDistance = NULL;
	}

	return bSuccess;
}

void CLogiMapCns::SetDebugInfo(CString strStart, CString strDest, 
								long nSID, long nSUID, long nDID, long nDUID, long nViaCount, 
								long nCompany)
{
	CMkLock lock(m_cs);
	m_strStart = strStart;
	m_strDest = strDest;
	m_nSID = nSID;
	m_nSUID = nSUID;
	m_nDID = nDID;
	m_nDUID = nDUID;
	m_nViaCount = nViaCount;
	m_nCompany = nCompany;
}

void CLogiMapCns::ClearPos() 
{ 
	CMkLock lock(m_cs);
	m_aryCNSPoint.RemoveAll();
}

void CLogiMapCns::AddPos(long x, long y) 
{ 
	CMkLock lock(m_cs);
	m_aryCNSPoint.Add(CPoint(x, y)); 
}

void CLogiMapCns::SetClearTarget(CWnd *pWnd)
{
	CMkLock lock(m_cs);
	if(pWnd == m_pwndTarget)
	{
		m_pwndTarget = NULL;
	}
}

void CLogiMapCns::SetOnceShowMap(CLogiMapNew *pMap)
{
	pMap->GetCenterPos(m_ptCenter.x, m_ptCenter.y);
	m_pOnceUseMap = pMap;
}
