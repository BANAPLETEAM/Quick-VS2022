#pragma once

class CSimpleMapDlg;

class CLogiMapCns
{
public:
	CLogiMapCns(CSimpleMapDlg *pMap);
	virtual ~CLogiMapCns(void);

protected:
	HANDLE m_hRoutingHandle;
	HANDLE m_hExitHandle;
	HANDLE m_hThreadDiedHandle;
	CCriticalSection m_cs;

	CString m_strStart;
	CString m_strDest;
	long m_nSID;
	long m_nSUID;
	long m_nDID;
	long m_nDUID;
	long m_nViaCount;
	long m_nCompany;

	CWnd *m_pwndTarget;
	CLogiMapNew *m_pOnceUseMap;
	CPoint m_ptCenter;

	long m_nCnsSearchType1; 
	long m_nCnsSearchType2;
	long m_nCnsSearchPaid;

	static long m_nLastCnsTick;	

public:
	CPoint m_ptCnsS;
	CPoint m_ptCnsD;
	long m_nCnsDistance;
	CNS_POINT_ARRAY m_aryCNSPoint;
	CSimpleMapDlg* m_pSimpleMapDlg;
	BOOL m_bRoutingThreadLive;
	BOOL m_bCNSShowMap;
	BOOL m_bCNSApplyVia;

	int m_nModifyPoiConfirmCharge;
	BOOL m_bChargeCalulate;
	BOOL m_bBicycle;
	
public:
	static int staticRoutingProc(CLogiMapCns *app)
	{ return app->RoutingProc((LPVOID)app); }
	UINT RoutingProc(LPVOID lParam); 

	BOOL m_bShowImage;
	void Close();
	BOOL GetRouteDistance(CWnd *pwndTarget, BOOL bShowMap, BOOL bViaApply, BOOL bChargeCalulate, int  nModifyPoiConfirmCharge, BOOL bShowImage = TRUE, long nCompany = 0, BOOL m_bBicycle = FALSE);	
	BOOL GetRouteDistanceThreadEksys(BOOL bShowMap,  BOOL bViaApply, BOOL bChargeCalculate = FALSE, int bControlChargeApply = FALSE);

	void ClearPos();
	void AddPos(long x, long y);

	void SetDebugInfo(CString strStart, CString strDest, 
		long nSID, long nSUID, long nDID, long nDUID, long nViaCount, 
		long nCompany);

	void SetClearTarget(CWnd *pWnd);
	void SetOnceShowMap(CLogiMapNew *pMap);

};
