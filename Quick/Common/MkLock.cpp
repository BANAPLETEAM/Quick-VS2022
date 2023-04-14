#include "stdafx.h"
#include "MkLock.h"

BOOL CMkLock::m_bPrintState = FALSE;

CMkLock::CMkLock()
{

}

CMkLock::CMkLock(CCriticalSection *pcs,BOOL bEnterCriticalSection ,BOOL bReleaseLock)
{
	SetLock(pcs, bEnterCriticalSection, bReleaseLock);
}

CMkLock::CMkLock(CCriticalSection &cs,BOOL bEnterCriticalSection,BOOL bReleaseLock)
{
	SetLock(&cs, bEnterCriticalSection, bReleaseLock);
}

CMkLock::CMkLock(CCriticalSection &cs, CString strFile, long nLine, BOOL bEnterCriticalSection ,BOOL bReleaseLock)
{
	m_strEnterFile = strFile;
	m_nEnterLine = nLine;
	if(m_bPrintState)
		g_bana_log->Print("LOCK ENTER: %s %d\n", strFile, nLine);
	SetLock(&cs);
}

CMkLock::~CMkLock(void)
{
	if(m_bPrintState && !m_strEnterFile.IsEmpty())
		g_bana_log->Print("UNLOCK ENTER: %s %d\n", m_strEnterFile, m_nEnterLine);

	if(TRUE == m_bReleaseLock && !m_bPreReleased)
	{
		m_pcs->Unlock();
	}
}

void CMkLock::SetLock(CCriticalSection *pcs,BOOL bEnterCriticalSection ,BOOL bReleaseLock)
{
	m_bPreReleased = FALSE;
	m_pcs = pcs;
	m_bReleaseLock = bReleaseLock;
	BOOL bRet = 0;
	if(TRUE == bEnterCriticalSection)
	{
		TRY
		{
			bRet = m_pcs->Lock();	
		}
		CATCH_ALL( e )
		{
			AfxMessageBox("Exception" /*+ e.GetErrorMessage()*/);
		}
		END_CATCH_ALL
	}
}

void CMkLock::SetStatePrint(BOOL bPrint)
{
	m_bPrintState = bPrint;
}

long CMkLock::GetLockCount()
{
	return m_pcs->m_sect.LockCount;
}

BOOL CMkLock::IsLocked()
{
	if(m_ui.bUseWindow7) //락 카운트가 -로 내려가는감 choi
	{
		if(m_pcs->m_sect.LockCount < -1) 
			return TRUE;
	}
	else
	{
		if(m_pcs->m_sect.LockCount >= 0) 
			return TRUE;
	}

	return FALSE;
}

void CMkLock::Release()
{
	m_bPreReleased = TRUE;
	m_pcs->Unlock();
}
