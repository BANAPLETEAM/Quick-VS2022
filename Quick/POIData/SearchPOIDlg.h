#pragma once

// CSearchPOIDlg 대화 상자입니다.

#include "POIDataNew.h"
#include "WindowMagnetic.h"
#include "CustomerDataDef.h"
#include "SearchPOIRecord.h"
#include "NaverHttpParser.h"
#include "DaumHttpParser.h"
#include "ListSize.h"
#include "POIReportControl.h"
#include "afxwin.h"
#include "JusoGoKr.h"

class CMarkupStatic;
class CSearchDongRecord;
class CSearchPOIRecord;
class CMkDatabase;
class CPOIDataNew;
class CSimpleMapDlg;
class CCustomerData;
class CSearchCusRecord;
class CLogiMapNew;
class CRcpPlaceInfo;

enum { POI_NORMAL = 1, POI_DONG = 2, POI_WEB = 4, POI_CUSTOMER = 8, POI_ALL = 15};

typedef vector<CSearchPOIRecord*> CSearchPOIRecordVector;
typedef vector<CSearchPOI*> CSearchHttpPoi;


class CSearchPOIDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSearchPOIDlg)

public:
	CSearchPOIDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSearchPOIDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SEARCH_POI_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnBnClickedShowMapBtn();
	afx_msg void OnBnClickedSearchAddressBtn();
	afx_msg void OnBnClickedChangeSearchSidoBtn();
	afx_msg void OnBnClickedChangeCenterSidoBtn();
	afx_msg void OnBnClickedMainDongCheck();
	afx_msg void OnBnClickedAutoCompletionCheck();
	afx_msg void OnCustomerReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnDongReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnPOIReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg LONG OnSelectPOIOnMap(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnBnClickedAlwaysShowCheck();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg LONG OnRecvWebRecord(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnMyStnClicked(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedSetupBtn();
	afx_msg void OnStnClickedCenterSidoStatic();
	afx_msg void OnBnClickedNoShowSubCheck();

	CString m_strNaverData;
	BOOL m_bNaverSearchOnlyPhone;
	CPOIReportControl m_wndDong;
	CPOIReportControl m_wndPOI;
	CPOIReportControl m_wndCustomer;
	CEdit m_edtSearchSido;
	CEdit m_edtCenterSido;
	CPOIDataNew *m_pPOINew;
	CButton m_chkMainDong;
	CButton m_chkAutoCompletion;
	CString m_strPreData;
	CEdit *m_pedtPlace;
	CSearchHttpPoi m_vecNaver;
	CSearchHttpPoi m_vecDaum;

	BOOL m_bWebPosAutoSelect;

	CButton *m_pchkLock;
	CWnd *m_pNextFocus;
	CString m_strDongKeyword;
	CString m_strPOIKeyword;
	CString m_strAutoCompletion;
	CString m_strKeyword;
	CMkDatabase *m_pDb;
	CPlaceInfo m_order;
	CPlaceInfo m_start;
	CPlaceInfo m_dest;
	CPlaceInfo m_customer;
	BOOL m_bClosedByUser;
	CWnd *m_pParentWnd;
	CSearchPOIRecordVector m_vecSearchPOIRecord;
	CWindowMagnetic m_Magnetic;
	CPtrArray m_arrPoint;
	BOOL m_bNoChangeMapPos;
	BOOL m_bAutoCompleteOnce;
	CCustomerData *m_pCus;
	long m_nCustomerTable;

	CLogiMapNew *m_pLogiMap;
	CRcpPlaceInfo *m_pRcpPlace;
	CButton m_chkAlwaysShow;
	static CNaverHttpParser m_Naver;
	static CDaumHttpParser m_Kakao;
	static long m_nNaverUID;
	UINT m_nCurNaverID;
	CButton m_chkSearchWeb;
	CButton m_chkUseMainPOIDisplayDong;
	CButton m_chkRegisterPhoneCustomer;
	CMyStatic m_stcCenterSido;
	CButton m_chkCustomerCharOrder;
	CButton m_chkNoShowSub;
	CButton m_chkSearchRoadAddress;

	void SetPreData(CString strData) {m_strKeyword = strData;};
	void SetPOIDataNew(CPOIDataNew *pPOINew);
	void SearchPOI(CString strKeyword, BOOL bSearchOnlyPhone = FALSE, BOOL bChangeMapPos = TRUE,
		int nSearchType = TYPE_AUTO,  BOOL bWebPosAutoSelect = FALSE);
	void SearchPOIWithSetText(CString strData, BOOL bJustSearch = FALSE, BOOL bChangeMapPos = TRUE, 
		int nSearchType = TYPE_AUTO, BOOL bWebPosAutoSelect = FALSE);
	BOOL InitState();
	void RefreshListMarkupName();
	void SetSearchSido(CString strSido);
	void SetCenterSido(CString strSido);
	void SetRcpPlace(CRcpPlaceInfo *pPlace, CWnd *pwndNextFocus);
	BOOL CheckJibunSearch(CString strData);
	void PostKeyMessage(WPARAM wParam);
	BOOL OnSelectCustomer(CSearchCusRecord *pItem, BOOL bFocusNotChange = FALSE);
	BOOL OnSelectDong(CSearchDongRecord *pItem, int nCol, BOOL bFocusNotChange = FALSE);	
	BOOL OnSelectPOI(CSearchPOIRecord *pItem, BOOL bFocusNotChange = FALSE);
	void SetDatabase(CMkDatabase *pMkDb);
	void SearchPOIJust(CString strKeyword = "");
	BOOL OnAutoSelectEvent(int nType, BOOL bFocusNotChange = FALSE, BOOL bSelectWhenSingleResult = FALSE);
	void SaveCurPOI(long nType, CPOIUnit *pPOI = NULL, CPOIUnit *pDetailPOI = NULL,
		CString strMarkupPOI = "", CString strNormalPOI = "", 
		CString strMarkupDetail = "", CString strNormalDetail = "",
		CString strAddress = "", CString strDisplayDong = "");

	void ClearWebPoi(CSearchHttpPoi *vec);
	void SetParentWnd(CWnd *pWnd);
	CWnd* GetParentWnd();
	void SetNextFocus();
	void DeleteSearchPOIRecord();
	void SetCusData(CCustomerData *pCus);
	static BOOL GetNearAddress(CMkDatabase *pDb, long nPosX, long nPosY, long &nDongID, CString &strAddress);
	static CPOIUnit* SearchAddressResultOnly(CMkDatabase *pDb, CPOIDataNew *pPOINew, 
		CString strKeyword, long nDongID, 
		CString &strPOIMarkup, CString &strPOINormal);
	void SetLogiMap(CLogiMapNew *pLogiMap);
	void MoveMap(long nPosX, long nPosY);
	void MoveMap(CPOIUnit *pPOI);
	void SetCustomerTable(long nCompany);
	void InitReportControl();
	void ShowPOIMap(BOOL bShow);

	void AddPointToMapFromRecord(CLogiMapNew *pLogiMap, CSearchPOIRecord *pRecord, int nItem, BOOL bWebPOI);
	static CHttpParser *GetNaver();
	void RefreshProfile(BOOL bSave);
	UINT GetNextNaverUID();
	BOOL SearchRoadAddress();
	BOOL SearchRoadAddress2();
	BOOL IsExceptionAddress();
	void CompareWebPoiSub(CSearchHttpPoi *vecOriginal, CSearchHttpPoi *vecDelete);

protected:
	SEARCH_POI_VEC m_vecPOI;
	int m_nDongListCount;
	CListSize m_lsDong, m_lsCustomer, m_lsPOI;
	SEARCH_CUS_VEC m_vecCus;

	void AddDongVectorToList(SEARCH_POI_VEC &vecDong);
	CPOIUnit* GetDongListInfo(int nItem, CString &strMarkup);
	void PopulateList(int nPOIType = POI_ALL);
	void ResetContent(int nPOIType = POI_ALL);
	void ResizeList();
	BOOL ListKeyDownNextFocus(CXTPGridControl &wndMe, CXTPGridControl &wndNext, 
		CXTPGridControl &wndNext2, int nKey);
	void CheckSubItemVisible(BOOL bPopulate = TRUE, CSearchCusRecord *pCus = NULL);

	std::vector<CString> near_sido_;
	CString center_sido_;

	SEARCH_POI_VEC SortPoiByNearCity(SEARCH_POI_VEC vec_in);

public:
	CButton m_chkWebPoiToDong;
	CButton m_chkAddressToDong;
	CButton m_chkUseDirectDistance;
	BOOL m_bSearchRoadAddress;

	CJusoGoKr m_cJuso;
};


AFX_INLINE void CSearchPOIDlg::SetPOIDataNew(CPOIDataNew *pPOIDataNew)
{
	m_pPOINew = pPOIDataNew;
}

AFX_INLINE void CSearchPOIDlg::SetCusData(CCustomerData *pCus)
{
	m_pCus = pCus;
}
