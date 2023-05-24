#pragma once

//#include "MainFrm.h"
#include "LogiMapNew.h"
#include "RiderMapCtrl.h"
#include "VirtualRecord.h"

class CRiderMapSetDlg;
class CRcpView;
class CRiderMapDlg;

#define WM_RIDER_POS_REAL_TIME	WM_USER + 0x432


// CRiderMapNormalForm 폼 뷰입니다.
class CRiderMapNormalForm : public CMyFormView
{
	DECLARE_DYNCREATE(CRiderMapNormalForm)

protected:
	CRiderMapNormalForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CRiderMapNormalForm();

public:
	enum { IDD = IDD_RIDER_MAP_NORMAL_FORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnEnChangeXtplistctrlEdit();
	afx_msg void OnCbnSelchangeXtplistctrlCombo();
	afx_msg void OnBnClickedRiderMapSetBtn();
	afx_msg void OnBnClickedDeleteTextBtn();
	afx_msg LONG OnRiderPosRealTime(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedRealtimeOtherRiderCheck();
	afx_msg void OnBnClickedOtherRiderWithMyOrderCheck();
	afx_msg void OnBnClickedOtherRiderCheck();
	afx_msg void OnBnClickedMyRiderCheck();

	BOOL IsUserCheckOrderCount(OrderRecord *p);

protected:
	BOOL m_bShowOrder;

public:
	COleDateTime m_dtLastRefresh;
	MAP_RIDER_POS_INFO m_mapRiderPos;
	ARRAY_RIDER_POS_OFFSET_INFO m_arrRiderPosOffset;
	VEC_RIDER_POS_INFO m_vecRiderPos;

	CRiderMapDlg *m_pRiderMapDlg;
	CRcpView *m_pRcpView;
	CRiderMapCtrl *m_pMap;
	CComboBox m_cmbEquipmentType;
	MAP_USER_SECTOR m_mapUserSector;
	ST_RIDER_MAP_SET_INFO m_setinfo;
	MAP_RIDER_MISC_INFO m_mapRiderMiscInfo;
	CRiderMapSetDlg *m_pRiderMapSetDlg;

	CXTPListCtrl2 m_wndReport;
	CXTPListCtrl2 m_lstOrder;

	int m_nPoint;
	int m_movecnt;
	int m_polyCnt;

	long m_tmX, m_tmY;
	long m_nTopIndex;
	long m_nSearchKeyword;

	CString m_strSearchKeyword;
	
	BOOL m_bInitCompleted;

	CFlatEdit2 m_edtSelectRNo;
	CFlatEdit2 m_edtInfo;

	long m_nSelectedRCompany;
	long m_nSelectedRNo;
	long m_nLastSelRiderCompany;
	long m_nLastSelRNo;	

	CButton m_chkShowLine;
	CButton m_chkMyRider;
	CButton m_chkRealtimeOtherRider;
	CButton m_chkOtherRiderWithMyOrder;
	CButton m_chkOtherRider;

	CStringList m_stInfo;
	CCriticalSection m_csInfo;
	CCriticalSection m_cs;

public:

	void UpdateRiderOrderCount(long nCompany, long nRNo);
	void StopSimul();
	void ClearSimulInfo();
	int GetCountBusRoute(long nCompany, CString strBUS);
	void RefreshOrderList(long nCompany, long nRNo);
	void POIAdd(int group,int id ,CString caption,CString hint,CString contents,CString imagename, long x, long y, int data,int type);
	void SetAction();
	void RefreshAllRider(BOOL bClear = FALSE);
	void DisplayPOIPos();
	void SetRiderPosRealTime(CRealTimeRiderPos &pos, BOOL bNotPopulate = FALSE);

	void GetDistanceAndDirection(long px, long py, long x, long y, long &nDistance, long &nDir);
	void RefreshOrderState();
	void CheckVisibleAllRider();
	void CheckVisibleRider(CRiderSubInfo &info, BOOL bReportPoplate = TRUE);

	void FindRNo(CString sRNo);
	void RefreshCustomerPOI();
	void AddOrderPOI(OrderRecord &order);
	CString GetOrderCaption(OrderRecord &order, BOOL bFull = FALSE);
	CString GetRiderCaption(long nCompany, long nRNo, CString strName, CString strCity, BOOL bFull = FALSE);
	CString GetRiderHint(CString &strRName, CString &strPhone, CString &strPOIName);

	void RefreshOrder();
	void MoveControl();
	void CheckRiderCaption();
	void RefreshFromSetupDlg();
	void SetMapInfo();
	static void AddRiderHaveOrderToList(CXTPListCtrl2 *pList, int nItem, COleDateTime dtState, 
		long nState, CString strCName, CString strStart, CString strDest, long nCharge);
	void SetEachRecordToRiderSubInfo();
	void InitGpsRider();
	BOOL IsRealTimeMode();
	void AddRiderPosInfo(CString strInfo);
	void RefreshCheckButton();
	afx_msg void OnBnClickedInitLocationBtn();
};


