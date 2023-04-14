#pragma once

#include "stdafx.h"
#include "afxmt.h"

#define MKLOCK(x)	CMkLock lock(x, CString(__FILE__), __LINE__);
#define MKLOCK_RELEASE()	lock.Release();


class CMkLock
{
public:
	CMkLock();
	CMkLock(CCriticalSection *pcs,BOOL bEnterCriticalSection = TRUE,BOOL bReleaseLock = TRUE);
	CMkLock(CCriticalSection &cs,BOOL bEnterCriticalSection = TRUE,BOOL bReleaseLock = TRUE);
	CMkLock(CCriticalSection &cs, CString strFile, long nLine, BOOL bEnterCriticalSection = TRUE ,BOOL bReleaseLock = TRUE);
	~CMkLock(void);

	void CMkLock::SetLock(CCriticalSection *pcs,BOOL bEnterCriticalSection = TRUE ,BOOL bReleaseLock = TRUE);
	BOOL IsLocked();
	void Release();
	long GetLockCount();

	static void SetStatePrint(BOOL bPrint);
	static BOOL m_bPrintState;

protected:
	CCriticalSection  *m_pcs;
	BOOL m_bReleaseLock;
	CString m_strEnterFile;
	long m_nEnterLine;
	BOOL m_bPreReleased;
};
