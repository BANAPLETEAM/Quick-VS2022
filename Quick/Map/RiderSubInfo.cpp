#include "StdAfx.h"
#include "resource.h"
#include "RiderSubInfo.h"
#include <math.h>

CRiderSubInfo::CRiderSubInfo(void)
{
	bOtherRider = FALSE;
	bRealtimeOtherRider = FALSE;
	m_bSkipPrePos = FALSE;
	m_pRecord = NULL;
	m_nTailPloygonID = -1;
	m_nTailIndex = -1;
	m_bGpsSignalError = FALSE;
	ZeroMemory(tail, RIDER_TAIL_COUNT * sizeof(RIDER_TAIL_INFO));
}

CRiderSubInfo::~CRiderSubInfo(void)
{
}

void CRiderSubInfo::AddPos(long nPosX, long nPosY)
{
	nTmX = nPosX;
	nTmY = nPosY;

	m_nTailIndex = GetTailIndex(m_nTailIndex);
	tail[m_nTailIndex].nPosX = nPosX;
	tail[m_nTailIndex].nPosY = nPosY;
	tail[m_nTailIndex].dwTick = GetTickCount();
}

BOOL CRiderSubInfo::GetPrevPos(long &nPosX, long &nPosY, long nSteps, long nMaxElapsedSec)
{
	if(m_nTailIndex >= 0)
	{
		long nIndex = GetPrevStepIndex(nSteps);

//		if(nRNo == 50)
//			g_bana_log->Print("357: idx=%d, stp=%d, %d, %d, tick=%d\n", nIndex, nSteps, 
//						tail[nIndex].nPosX, tail[nIndex].nPosY, GetTickCount() - tail[nIndex].dwTick);

		if(GetTickCount() - tail[nIndex].dwTick < nMaxElapsedSec * 1000)
		{
			nPosX = tail[nIndex].nPosX;
			nPosY = tail[nIndex].nPosY;
			return TRUE;
		}
	}

	nPosX = 0;
	nPosY = 0;
	return FALSE;
}

long CRiderSubInfo::GetPrevStepIndex(long nSteps)
{
	long nIndex = m_nTailIndex;
	while(nSteps-- > 0)
		nIndex = GetTailIndex(nIndex, FALSE);

	return nIndex;
}

long CRiderSubInfo::GetTailIndex(long nIndex, BOOL bNext)
{
	if(bNext)
	{
		if(++nIndex >= RIDER_TAIL_COUNT)
			nIndex = 0;
	}
	else
	{
		if(--nIndex < 0)
			nIndex = RIDER_TAIL_COUNT - 1;
	}

	return nIndex;
}

void CRiderSubInfo::SetTailPloygonID(long nPloygonID)
{
	m_nTailPloygonID = nPloygonID;
}

long CRiderSubInfo::GetTailPolygonID()
{
	return m_nTailPloygonID;
}

BOOL CRiderSubInfo::SetRecordVisible(BOOL bVisible)
{
	if(m_pRecord)
	{
		if(m_pRecord->IsVisible() != bVisible)
		{
			m_pRecord->SetVisible(bVisible);
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CRiderSubInfo::IsGpsSignalError()
{
	return m_bGpsSignalError;

/*
	long nPosX, nPosY;
	long nPosX2, nPosY2;
	long nCount = 1;

	GetPrevPos(nPosX, nPosY, 0, 10);

	while(nCount < RIDER_TAIL_COUNT - 1)
	{
		if(!GetPrevPos(nPosX2, nPosY2, nCount++, 20))
			return (nCount > 2);

		//��ġ�� �����ϸ� ��ȣ�� �������� ������ �����ߴµ�, 
		//�ܸ��⿡�� ��������̵ǵ�, ������ ��ġ�� ��������� ������ ������, 
		//���������� ���� �ʾƼ�, �ּ�ó���� //by mksong (2011-06-24 ���� 1:31)
		//if(nPosX != nPosX2 || nPosY != nPosY2)
		//	return FALSE;
	}
	
	return FALSE;
*/
}


int CRiderSubInfo::IsFaraway(long nPosX, long nPosY, long nPosX2, long nPosY2, int nAboutValue, int nFarMeter)
{
	if(abs(nPosX - nPosX2) > nAboutValue ||
		abs(nPosY - nPosY2) > nAboutValue)
	{
		int nMeter = LF->GetDistanceMeter(nPosX, nPosY, nPosX2, nPosY2);
		if(nMeter > nFarMeter)
			return nMeter;
	}

	return 0;
}

BOOL CRiderSubInfo::IsSkipPos(long nPosX, long nPosY)
{
	if(!m_bSkipPrePos)
	{
		if(nPosX == 0)	//���� ��ġ�� 0�̸� skip//by mksong (2011-06-24 ���� 1:31)
		{
			m_bGpsSignalError = TRUE;
			return TRUE;	
		}

		long nPosX2, nPosY2;
		if(GetPrevPos(nPosX2, nPosY2, 0, 5))
		{
			if(nPosX2 == 0)		//���� ��ġ�� 0�̰�, ���� ��ġ�� 0�� �ƴϸ� skip ����//by mksong (2011-06-24 ���� 1:31)
				return FALSE;

			//���� ��ġ�� ���� ��ġ�� ���۽����� 500���� �̻� ���̰� ���� skip��
			int nMeter = IsFaraway(nPosX, nPosY, nPosX2, nPosY2, 500, 200);
			if(nMeter > 0)
			{
				g_bana_log->Print("skip pos %d�� = %d, %d, (meter=%d)\n", nRNo, nPosX2 - nPosX, nPosY2 - nPosY, nMeter);
				m_bSkipPrePos = TRUE;
				return TRUE;
			}
		}
	}
	else
		m_bSkipPrePos = FALSE;

	m_bGpsSignalError = FALSE;
	return FALSE;
}