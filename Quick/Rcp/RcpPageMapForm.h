#pragma once

#include "RcpMapCtrl.h"
#include "RiderTraceCtrl.h"
#include "afxwin.h"

typedef map<pair<long, long>, ST_RCP_RIDER_POS> RCP_RIDER_POS_MAP;

enum { SHOW_TYPE_BOTH = 0, SHOW_TYPE_RIDER, SHOW_TYPE_ORDER};


// CRcpPageMapForm 폼 뷰입니다.

class CRcpPageMapForm : public CMyFormView
{
	DECLARE_DYNCREATE(CRcpPageMapForm)

protected:
	CRcpPageMapForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CRcpPageMapForm();

public:
	enum { IDD = IDD_RCP_PAGE_MAP_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedModeBtn();
	afx_msg void OnBnClickedSetupBtn();
	afx_msg LONG OnRefreshRiderPos(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedIncLevelBtn();
	afx_msg void OnBnClickedDecLevelBtn();
	afx_msg void OnBnClickedMovePageBtn();
	afx_msg void OnDestroy();

	void AddRiderPos(long nCompany, long nRNo, CString strRName, long nPosX, long nPosY,
		BOOL bUseGps, CCarType &cartype, CString strPOIName, CString strTime,
		COleDateTime dtPos = COleDateTime::GetCurrentTime(), BOOL bRealTime = TRUE);
	void MoveClient();
	void ShowClient();
	BOOL RefreshRiderPos();
	BOOL m_bRecvOrderDistance;

public:
	void RefreshShowType(int nType);
	void SetTraceRider(long nCompany, long nRNo, OrderRecord *pOrder = NULL);
	void AddStartPos(BOOL bMove, long nPosX, long nPosY, CString strName, CString strPos);
	void AddDestPos(BOOL bMove, long nPosX, long nPosY, CString strName, CString strPos);
	void DeleteDest();
	LONG OnGetCnsInfo(WPARAM wParam, LPARAM lParam);

public:
	CRiderTraceCtrl m_wndRiderMap;
	CRcpMapCtrl m_wndOrderMap;
	ST_RCP_MAP_SET_INFO m_setinfo;

	int m_nShowType;

	long m_nTraceCompany;
	long m_nTraceRNo;

	CButton m_btnMode;
	CButton m_btnSetup;
	CButton m_btnIncLevel;
	CButton m_btnDecLevel;
	CButton m_btnMovePage;

	CMyStatic m_stcDistance;
	CMyStatic m_stcTip;
	CStatic m_stcDistanceRider;
	CStatic m_stcTip2;
};


