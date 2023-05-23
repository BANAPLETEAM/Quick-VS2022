// SearchPOIDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SearchPOIDlg.h"
#include "POIDataAddress.h"
#include "POIBoundary.h"
#include "SimpleMapDlg.h"
#include "CustomerData.h"
#include "RcpPlaceInfo.h"
#include "SearchPOISetupDlg.h"
#include "CustomerDlg.h"
#include "RoadAddress.h"
#include "JusoGoKr.h"

#ifndef _STANDALONE
	#include "LogiUtil.h"
#endif

#define WEB_DEBUG_PRINT_TYPE 0

CNaverHttpParser CSearchPOIDlg::m_Naver;
CDaumHttpParser CSearchPOIDlg::m_Kakao;

long CSearchPOIDlg::m_nNaverUID = 1;
// CSearchPOIDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSearchPOIDlg, CMyDialog)

CSearchPOIDlg::CSearchPOIDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSearchPOIDlg::IDD, pParent)
{
	m_pPOINew = NULL;
	m_pchkLock = NULL;
	m_pedtPlace = NULL;
	m_pNextFocus = NULL;
	m_pDb = NULL;
	m_bClosedByUser = FALSE;
	m_pParentWnd = pParent;
	m_bNoChangeMapPos = FALSE;
	m_bAutoCompleteOnce = FALSE;
	m_pCus = NULL;
	m_pLogiMap = NULL;
	m_pRcpPlace = NULL;
	m_nCustomerTable = 0;
	m_nDongListCount = 0;
	m_nCurNaverID = 0;	
}

CSearchPOIDlg::~CSearchPOIDlg()
{
	ClearWebPoi(&m_vecNaver);
	ClearWebPoi(&m_vecDaum);

	ResetContent();
	DeleteSearchPOIRecord();
}


void CSearchPOIDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DONG_LIST, m_wndDong);
	DDX_Control(pDX, IDC_POI_LIST, m_wndPOI);
	DDX_Control(pDX, IDC_CUSTOMER_LIST, m_wndCustomer);
	DDX_Control(pDX, IDC_SEARCH_SIDO_EDIT, m_edtSearchSido);
	DDX_Control(pDX, IDC_CENTER_SIDO_EDIT, m_edtCenterSido);
	DDX_Control(pDX, IDC_MAIN_DONG_CHECK, m_chkMainDong);
	DDX_Control(pDX, IDC_AUTO_COMPLETION_CHECK, m_chkAutoCompletion);
	DDX_Control(pDX, IDC_ALWAYS_SHOW_CHECK, m_chkAlwaysShow);
	DDX_Control(pDX, IDC_SEARCH_WEB_CHECK, m_chkSearchWeb);
	DDX_Control(pDX, IDC_USE_MAIN_POI_DISPLAY_DONG_CHECK, m_chkUseMainPOIDisplayDong);
	DDX_Control(pDX, IDC_REGISTER_PHONE_CUSTOMER_CHECK, m_chkRegisterPhoneCustomer);
	DDX_Control(pDX, IDC_CENTER_SIDO_STATIC, m_stcCenterSido);
	DDX_Control(pDX, IDC_CUSTOMER_CHAR_ORDER_CHECK, m_chkCustomerCharOrder);
	DDX_Control(pDX, IDC_NO_SHOW_SUB_CHECK, m_chkNoShowSub);
	DDX_Control(pDX, IDC_SEARCH_ROAD_CHECK, m_chkSearchRoadAddress);
	DDX_Control(pDX, IDC_WEB_POI_TO_DONG_CHECK, m_chkWebPoiToDong);
	DDX_Control(pDX, IDC_USE_DIRECT_DISTANCE_CHECK, m_chkUseDirectDistance);
	DDX_Control(pDX, IDC_ADDRESS_TO_DONG_CHECK, m_chkAddressToDong);
}


BEGIN_MESSAGE_MAP(CSearchPOIDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CSearchPOIDlg::OnBnClickedCloseBtn)
	ON_BN_CLICKED(IDC_SHOW_MAP_BTN, &CSearchPOIDlg::OnBnClickedShowMapBtn)
	ON_BN_CLICKED(IDC_SEARCH_ADDRESS_BTN, &CSearchPOIDlg::OnBnClickedSearchAddressBtn)
	ON_BN_CLICKED(IDC_CHANGE_SEARCH_SIDO_BTN, &CSearchPOIDlg::OnBnClickedChangeSearchSidoBtn)
	ON_BN_CLICKED(IDC_CHANGE_CENTER_SIDO_BTN, &CSearchPOIDlg::OnBnClickedChangeCenterSidoBtn)
	ON_BN_CLICKED(IDC_MAIN_DONG_CHECK, &CSearchPOIDlg::OnBnClickedMainDongCheck)
	ON_BN_CLICKED(IDC_AUTO_COMPLETION_CHECK, &CSearchPOIDlg::OnBnClickedAutoCompletionCheck)
	ON_BN_CLICKED(IDC_ALWAYS_SHOW_CHECK, &CSearchPOIDlg::OnBnClickedAlwaysShowCheck)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CSearchPOIDlg::OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOMER_LIST, OnCustomerReportItemClick)
	ON_NOTIFY(NM_CLICK, IDC_DONG_LIST, OnDongReportItemClick)
	ON_NOTIFY(NM_CLICK, IDC_POI_LIST, OnPOIReportItemClick)
	ON_MESSAGE(WM_SELECT_POI_ON_MAP, OnSelectPOIOnMap)
	ON_MESSAGE(WM_USER + 999, OnRecvWebRecord)
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_TIMER() 
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SETUP_BTN, &CSearchPOIDlg::OnBnClickedSetupBtn)
	ON_MESSAGE(WM_MY_STATIC_CLICK, OnMyStnClicked)
	ON_BN_CLICKED(IDC_NO_SHOW_SUB_CHECK, &CSearchPOIDlg::OnBnClickedNoShowSubCheck)
END_MESSAGE_MAP()


// CSearchPOIDlg 메시지 처리기입니다.

BOOL CSearchPOIDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	RefreshProfile(FALSE);

	m_Magnetic.SetInfo(this, m_pParentWnd, "SearchPOIDlg");
	m_Magnetic.AttachTo();

	m_pPOINew->SetMainSidoDongOnly(m_chkMainDong.GetCheck());
	LU->MakePoiAndCusData();
	
	InitReportControl();
	ResizeList();

	return FALSE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSearchPOIDlg::InitReportControl()
{
	LOGFONT lf = {12,0,0,0,FW_NORMAL,0,0,0,HANGUL_CHARSET,0,0,0,0,"맑은 고딕"};

	CXTPGridColumn* pColDong0 = m_wndDong.AddColumn(new CXTPGridColumn(0, _T("지명1"), 80));
	CXTPGridColumn* pColDong1 = m_wndDong.AddColumn(new CXTPGridColumn(1, _T("지명2"), 80));
	CXTPGridColumn* pColDong2 = m_wndDong.AddColumn(new CXTPGridColumn(2, _T("지명3"), 80));
	pColDong0->SetAlignment(DT_LEFT);
	m_wndDong.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);	
	m_wndDong.GetPaintManager()->m_strNoItems = "";
	m_wndDong.ShowHeader(FALSE);
	m_wndDong.AllowEdit(FALSE);
	m_wndDong.GetReportHeader()->AllowColumnSort(FALSE);
	m_wndDong.FocusSubItems(TRUE);
	m_wndDong.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_wndDong.SetGridColor(RGB(222, 222, 222));
	m_wndDong.GetPaintManager()->m_bHideSelection = TRUE;
	m_wndDong.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_wndDong.EnableMarkup(TRUE);
	m_wndDong.Populate();

	CXTPGridColumn* pCol0 = m_wndPOI.AddColumn(new CXTPGridColumn(0, _T("POI"), 110));
	CXTPGridColumn* pCol1 = m_wndPOI.AddColumn(new CXTPGridColumn(1, _T("지명"), 120));
	CXTPGridColumn* pCol2 = m_wndPOI.AddColumn(new CXTPGridColumn(2, _T("인근POI"), 100));
	CXTPGridColumn* pCol3 = m_wndPOI.AddColumn(new CXTPGridColumn(3, _T("거리(m)"), 40));
	CXTPGridColumn* pCol4 = m_wndPOI.AddColumn(new CXTPGridColumn(4, _T("전화번호"), 60));
	pCol0->SetAlignment(DT_LEFT);
	pCol1->SetAlignment(DT_LEFT);
	pCol2->SetAlignment(DT_LEFT);
	pCol3->SetAlignment(DT_LEFT);
	pCol4->SetAlignment(DT_LEFT);
	m_wndPOI.ShowHeader(TRUE);
	m_wndPOI.AllowEdit(FALSE);
	m_wndPOI.GetReportHeader()->AllowColumnSort(FALSE);
	m_wndPOI.FocusSubItems(FALSE);
	m_wndPOI.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_wndPOI.SetGridColor(RGB(222, 222, 222));
	m_wndPOI.GetPaintManager()->m_bHideSelection = TRUE;
	m_wndPOI.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);	
	m_wndPOI.GetPaintManager()->m_strNoItems = "웹 실시간 검색결과 입니다.\n";
	m_wndPOI.GetPaintManager()->m_strNoItems += "고객데이터와 달리 자동선택되지 않습니다. 클릭바람!";
	m_wndPOI.EnableMarkup(TRUE);
	m_wndPOI.GetPaintManager()->SetCaptionFont(lf);
	m_wndPOI.GetPaintManager()->SetHeaderHeight(12);
	m_wndPOI.Populate();

	CBitmap bmp;
	CImageList listIcons;
	listIcons.Create(11,11, ILC_COLOR24|ILC_MASK, 0, 1);
	bmp.LoadBitmap(IDB_PLUS_MINUS);
	listIcons.Add(&bmp, RGB(0,255,255));
	m_wndCustomer.SetImageList(&listIcons);

	pCol0 = m_wndCustomer.AddColumn(new CXTPGridColumn(0, _T(""), 13));
	pCol1 = m_wndCustomer.AddColumn(new CXTPGridColumn(1, _T("고객명"), 120));
	pCol2 = m_wndCustomer.AddColumn(new CXTPGridColumn(2, _T("부서"), 65));
	pCol3 = m_wndCustomer.AddColumn(new CXTPGridColumn(3, _T("담당"), 65));
	pCol4 = m_wndCustomer.AddColumn(new CXTPGridColumn(4, _T("전화번호"), 75));
	CXTPGridColumn *pCol5 = m_wndCustomer.AddColumn(new CXTPGridColumn(5, _T("지명"), 50));
	CXTPGridColumn *pCol6 = m_wndCustomer.AddColumn(new CXTPGridColumn(6, _T("최종"), 40));
	CXTPGridColumn *pCol7 = m_wndCustomer.AddColumn(new CXTPGridColumn(7, _T("사용"), 25));
	
	pCol0->SetVisible(m_chkNoShowSub.GetCheck());
	pCol0->SetAlignment(DT_CENTER);
	pCol1->SetAlignment(DT_LEFT);
	pCol2->SetAlignment(DT_LEFT);
	pCol3->SetAlignment(DT_LEFT);
	pCol4->SetAlignment(DT_LEFT);
	pCol5->SetAlignment(DT_LEFT);
	pCol6->SetAlignment(DT_CENTER);
	pCol7->SetAlignment(DT_CENTER);
	m_wndCustomer.ShowHeader(TRUE);
	m_wndCustomer.AllowEdit(FALSE);
	//m_wndCustomer.GetReportHeader()->AllowColumnSort(FALSE);
	m_wndCustomer.GetReportHeader()->AllowColumnSort(TRUE);
	m_wndCustomer.FocusSubItems(FALSE);
	m_wndCustomer.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_wndCustomer.SetGridColor(RGB(222, 222, 222));
	m_wndCustomer.GetPaintManager()->m_bHideSelection = TRUE;
	m_wndCustomer.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);	
	m_wndCustomer.GetPaintManager()->m_strNoItems = "검색된 고객이 없을시 최상위 지명이 자동선택됩니다.\n";
	m_wndCustomer.GetPaintManager()->m_strNoItems += "아래의 웹검색결과 선택은 키보드 UP/DOWN 방향키 이용바람";
	m_wndCustomer.GetPaintManager()->SetCaptionFont(lf);
	m_wndCustomer.GetPaintManager()->SetHeaderHeight(14);
	m_wndCustomer.EnableMarkup(TRUE);

	pCol0->SetTreeColumn(1);
	//pCol0->SetVisible(FALSE);
	m_wndCustomer.SetTreeIndent(0);

	m_wndCustomer.Populate();
}

void CSearchPOIDlg::ClearWebPoi(CSearchHttpPoi *vec)
{
	for(int i=0; i<vec->size(); i++)
	{
		CSearchPOI *p = vec->at(i);
		delete p;
	}

	vec->clear();
}

#define SHOW_COUNT 300

void CSearchPOIDlg::SearchPOI(CString strData, BOOL bSearchOnlyPhone, BOOL bChangeMapPos, int nSearchType, BOOL bWebPosAutoSelect)
{
	if(m_ci.m_bUseSearchPopup)
		return;

	strData.MakeLower();

	if(InitState() && (m_bAutoCompleteOnce || m_strPreData != strData))
	{
		if(m_wndDong.GetRecords()->GetCount() > 0 && CPOIDataAddress::CheckJibunSearch(strData))
		{
			OnBnClickedSearchAddressBtn(); 
			return;
		}

		BOOL bSearchRoadAddress = SearchRoadAddress();

		if(bSearchRoadAddress)
			return;

		bSearchRoadAddress = SearchRoadAddress2();

		if(bSearchRoadAddress)
		{
			ResetContent(POI_CUSTOMER);
			if(m_pCus)
			{
				int nCount = 0;
				SEARCH_CUS_VEC vecCus;
				SEARCH_CUS_VEC::iterator it;
				CXTPGridRecord *pRecord = NULL; 

				if(m_pCus->SearchCustomer(m_nCustomerTable, strData, vecCus))
				{
					for(it = vecCus.begin(); it != vecCus.end(); it++)
					{							
						pRecord = m_wndCustomer.AddRecord(new CSearchCusRecord(*it, m_strKeyword));
						if(++nCount == SHOW_COUNT)
							break;
					}
				}

				m_vecCus.swap(vecCus);
			}

			PopulateList();
			return;
		}

		ResetContent(POI_NORMAL | POI_DONG | POI_CUSTOMER);

		CString strTopOne, strTopOneNormal;
		CPlaceInfo place;

		if(strData.GetLength() > 2) 
		{
			if(m_chkSearchWeb.GetCheck())
			{
				m_strNaverData = strData;
				m_bNaverSearchOnlyPhone = bSearchOnlyPhone;
				m_bSearchRoadAddress = bSearchRoadAddress;

				ClearWebPoi(&m_vecNaver);
				ClearWebPoi(&m_vecDaum);

				SetTimer(2, 1000, NULL);

				//m_Naver.ThreadRefresh(strData, this, GetNextNaverUID(), bWebPosAutoSelect, WEB_DEBUG_PRINT_TYPE);
			}

			SEARCH_POI_VEC vecDong;
			SEARCH_POI_VEC::iterator it;
			BOOL bSearchDong = nSearchType & TYPE_DONG;
			BOOL bSearchPOI = nSearchType & TYPE_POI;
			BOOL bSearchCustomer = nSearchType & TYPE_CUSTOMER;
			BOOL bSearchPhone = nSearchType & TYPE_PHONE;

			if(bSearchDong || bSearchPOI || bSearchPhone)
			{
				SEARCH_POI_MAP mapTemp; 

				if(bSearchPOI)
					m_pPOINew->SearchPOIWithDong(strData, m_vecPOI, vecDong, FALSE, bSearchOnlyPhone);
				else if(bSearchDong)
					m_pPOINew->SearchDong(strData, vecDong, mapTemp);
				else if(bSearchPhone)
					m_pPOINew->SearchPOIWithDong(strData, m_vecPOI, vecDong, FALSE, TRUE);

				m_pPOINew->GetLastKeyword(m_strDongKeyword, m_strPOIKeyword);

				AddDongVectorToList(vecDong);

				int nCount = 0;
				CPOIUnit *pPrePOI = NULL;
				for(it = m_vecPOI.begin(); it != m_vecPOI.end(); it++)
				{
					it->second.pPrePOI = pPrePOI;
					m_wndPOI.AddRecord(new CSearchPOIRecord(&it->second));
					pPrePOI = it->second.pPOI;

					if(++nCount == SHOW_COUNT)
						break;
				}
			}

			if(bSearchCustomer || bSearchPhone)
			{ 
				BOOL bSkipSearchCustomer = FALSE;

				if(m_wndDong.GetRecords()->GetCount() > 0)
				{
					int nLen = wcslen(CPOIDataNew::A2U(strData));

					for(it = vecDong.begin(); it != vecDong.end(); it++)
					{
						if(it->second.nLen == nLen &&
							it->second.nDataPos == it->second.nKeywordPos)
						{
							//if(it->second.IsDongAndFullNameMatch())
							bSkipSearchCustomer = TRUE;
						}
					}
				}

				if(strData.Find("종로") >= 0)
					bSkipSearchCustomer = FALSE;

				if(m_pCus && !bSkipSearchCustomer)
				//if(m_pCus)
				{
					int nCount = 0;
					SEARCH_CUS_VEC vecCus;
					SEARCH_CUS_VEC::iterator it;
					CXTPGridRecord *pRecord = NULL; 

					//if(m_pCus->SearchCustomer(m_nCustomerTable, strData, vecCus, bFullName))
					if(m_pCus->SearchCustomer(m_nCustomerTable, strData, vecCus))
					{
						for(it = vecCus.begin(); it != vecCus.end(); it++)
						{							
							//if(it->bHasParentOrChild && pRecord != NULL)
							//{
							//	CXTPGridRecords* pRecords1 = (pRecord->GetChilds());								
							//	CXTPGridRecord *pTempRecord =pRecords1->Add(new CSearchCusRecord(*it, m_strKeyword));
							//	pRecord->SetExpanded(TRUE);		
								//pRecords1->EnableMarkup(TRUE);
								//pRecords1->EnableMarkup(TRUE);														
							//}
							//else
								pRecord = m_wndCustomer.AddRecord(new CSearchCusRecord(*it, m_strKeyword));

							if(++nCount == SHOW_COUNT)
								break;
						}
					}

					m_vecCus.swap(vecCus);
				}
			}
		}

		PopulateList();

		m_strPreData = strData;
		m_bAutoCompleteOnce = FALSE;

		if(bChangeMapPos && !m_bNoChangeMapPos)
		{
			SetTimer(1, 200, NULL);
			m_bNoChangeMapPos = FALSE;
		}
	}
}

void CSearchPOIDlg::RefreshListMarkupName()
{
	for(int i = 0; i < m_wndPOI.GetRecords()->GetCount(); i++)
		((CSearchPOIRecord*)(m_wndPOI.GetRecords()->GetAt(i)))->RedrawMarkupName();

	for(int i = 0; i < m_wndDong.GetRecords()->GetCount(); i++)
		((CSearchDongRecord*)(m_wndDong.GetRecords()->GetAt(i)))->RedrawMarkupName();

	for(int i = 0; i < m_wndCustomer.GetRecords()->GetCount(); i++)
		((CSearchCusRecord*)(m_wndCustomer.GetRecords()->GetAt(i)))->RedrawMarkupName();

	m_wndPOI.RedrawControl();
	m_wndDong.RedrawControl();
	m_wndCustomer.RedrawControl();
}

void CSearchPOIDlg::SearchPOIWithSetText(CString strData, BOOL bJustSearch, BOOL bChangeMapPos,
										int nSearchType, BOOL bWebPosAutoSelect) 
{	
	m_bClosedByUser = FALSE;
	if(m_strKeyword != strData)
	{
		m_bWebPosAutoSelect = bWebPosAutoSelect;
		m_strKeyword = strData;

		if(bJustSearch)
			SearchPOI(strData, 0, bChangeMapPos, nSearchType, bWebPosAutoSelect);
		else
		{
			m_bNoChangeMapPos = !bChangeMapPos;
			SetTimer(0, 100, NULL);
		}
	}
}

void CSearchPOIDlg::OnBnClickedShowMapBtn()
{
	ShowPOIMap(TRUE);
}

void CSearchPOIDlg::ShowPOIMap(BOOL bShow)
{
	CSimpleMapDlg *pSimpleMapDlg = LU->GetSimpleMap(bShow);
	CLogiMapNew *pLogiMap = pSimpleMapDlg->GetMap();

	for(int z = 0; z < m_arrPoint.GetCount(); z++)
		delete (CSearchPOIRecord*)(m_arrPoint.GetAt(z));

	m_arrPoint.RemoveAll();
	pLogiMap->ClearAllLayer();

/* POI클릭 적용시 아래 수정해서 활성화 바람
	if(m_nPlaceType == PLACE_TYPE_START)
		pSimpleMapDlg->SetSendPOISelect(TRUE, TRUE);
	if(m_nPlaceType == PLACE_TYPE_DEST)
		pSimpleMapDlg->SetSendPOISelect(TRUE, FALSE);
*/

	for(int i = 0; i < m_wndPOI.GetRows()->GetCount(); i++)
	{
		CXTPGridRow *pRow = m_wndPOI.GetRows()->GetAt(i);
		CSearchPOIRecord *pRecord = (CSearchPOIRecord*)pRow->GetRecord();
		AddPointToMapFromRecord(pLogiMap, pRecord, i, FALSE);
	}

}

void CSearchPOIDlg::AddPointToMapFromRecord(CLogiMapNew *pLogiMap, CSearchPOIRecord *pRecord, int nItem, BOOL bWebPOI)
{
	if(pRecord->m_pSearchPOI)
	{
		CSearchPOIRecord *pRecordDst = new CSearchPOIRecord(pRecord->m_pSearchPOI); 
		CPOIUnit *pPOI = pRecord->m_pSearchPOI->pPOI;
		CString strNumber;
		if(!pRecord->m_pSearchPOI->bAddressSearch)
			strNumber.Format("%s%d)", bWebPOI ? "웹" : "", nItem + 1);

		pLogiMap->AddPointPOI(nItem == 0, strNumber + pPOI->GetPOIName(), 
			pPOI->GetPosX(), pPOI->GetPosY(), "", "POINT", -1, POINT_POI, -1,
			(long)pRecordDst);

		m_arrPoint.Add((void*)pRecordDst);
	}
}

BOOL CSearchPOIDlg::InitState()
{
	if(m_pPOINew == NULL)
	{
		AfxMessageBox("POI데이터 초기화 실패");
		return FALSE;
	}

	return TRUE;
}

void CSearchPOIDlg::OnBnClickedSearchAddressBtn()
{
	if(InitState() && (m_bAutoCompleteOnce || m_strPreData != m_strKeyword))
	{
		ResetContent(POI_NORMAL);

		if(m_strKeyword.GetLength() > 0)
		{
			SEARCH_POI_VEC::iterator it;
			CPOIDataAddress pda(m_pDb, m_pPOINew);
			pda.SetAddressText(m_strKeyword);
			if(pda.GetAddressList(m_vecPOI))
			{
				int nCount = 0;
				CPOIUnit *pPrePOI = NULL;
				for(it = m_vecPOI.begin(); it != m_vecPOI.end(); it++)
				{
					//NewPOI로 생성된 POI는 포인터를 계속 사용할 수 없다. 
					//리스트가 갱신되거나 다이얼로그가 종료되면 할당된 메모리가 제거되고, 포인터는 소멸된다. 
					CPOIUnit *pPOI = m_pPOINew->NewPOI((UINT)this, it->second.pPOI, it->second.nNewPosX, 
						it->second.nNewPosY, it->second.szKeyword);

					it->second.pPOI = pPOI;
					it->second.pPrePOI = pPrePOI;

					CSearchPOIRecord *pRecord = (CSearchPOIRecord*)m_wndPOI.AddRecord(new CSearchPOIRecord(&it->second));

					//if(it == m_vecPOI.begin())
					//	OnSelectPOI(pRecord, TRUE);

					pPrePOI = pPOI;
				}
			}
		}

		PopulateList(POI_NORMAL);
		m_strPreData = m_strKeyword;	
	}
}

CPOIUnit* CSearchPOIDlg::SearchAddressResultOnly(CMkDatabase *pDb, CPOIDataNew *pPOINew, 
					CString strKeyword, long nDongID, 
					CString &strPOIMarkup, CString &strPOINormal)
{
	SEARCH_POI_VEC::iterator it;
	SEARCH_POI_VEC vec;
	CPOIDataAddress pda(pDb, pPOINew);
	pda.SetAddressText(pPOINew->GetDongPOI(nDongID)->GetDong() + strKeyword);
	if(pda.GetAddressList(vec, TRUE))
	{
		int nCount = 0;
		CPOIUnit *pPrePOI = NULL;
		for(it = vec.begin(); it != vec.end(); it++)
		{
			//NewPOI로 생성된 POI는 포인터를 계속 사용할 수 없다. 
			//리스트가 갱신되거나 다이얼로그가 종료되면 할당된 메모리가 제거되고, 포인터는 소멸된다. 
			if(it->second.pPOI->GetMainDongID() == nDongID || nDongID == 0)
			{
				CPOIUnit *pPOI = pPOINew->NewPOI((UINT)pPOINew, it->second.pPOI, it->second.nNewPosX, 
					it->second.nNewPosY, it->second.szKeyword);

				it->second.pPOI = pPOI;
				strPOIMarkup = it->second.GetMarkupFullName();
				strPOINormal = it->second.pPOI->GetFullName();
				return pPOI;
			}
		}
	}

	return 0;
}

void CSearchPOIDlg::OnBnClickedChangeSearchSidoBtn()
{
	m_pPOINew->SetSearchSido(new CPOIBoundary(m_pPOINew, TRUE, "서울", "인천"));
	SetSearchSido(m_pPOINew->GetSearchSido()->GetSido());
}

void CSearchPOIDlg::SetSearchSido(CString strSido)
{
	m_edtSearchSido.SetWindowText(strSido);
}

void CSearchPOIDlg::SetCenterSido(CString strSido)
{
	near_sido_.clear();
	near_sido_ = LF->GetNeighboringCity(strSido);
	center_sido_ = strSido;

	CString strPreSido;
	m_stcCenterSido.GetWindowText(strPreSido);
	if(strPreSido != strSido + "기준")
		m_stcCenterSido.SetWindowText(strSido + "기준");
}

void CSearchPOIDlg::OnBnClickedChangeCenterSidoBtn()
{
	m_pPOINew->SetCenterSido("인천");
	SetCenterSido(m_pPOINew->GetCenterSido());
}

void CSearchPOIDlg::OnBnClickedMainDongCheck()
{
	m_strPreData.Empty();
	m_pPOINew->SetMainSidoDongOnly(m_chkMainDong.GetCheck());
	SearchPOI(m_pPOINew->RemoveCache());

	AfxGetApp()->WriteProfileInt("SearchPOIDlg", "MainRegionDongOnly", m_chkMainDong.GetCheck());
}

void CSearchPOIDlg::OnBnClickedAutoCompletionCheck()
{
	AfxGetApp()->WriteProfileInt("SearchPOIDlg", "AutoCompletion", m_chkAutoCompletion.GetCheck());
}

void CSearchPOIDlg::SetRcpPlace(CRcpPlaceInfo *pPlace, CWnd *pwndNextFocus)
{
	m_pRcpPlace = pPlace;
	m_pNextFocus = pwndNextFocus;
}


void CSearchPOIDlg::SetNextFocus()
{
	if(m_pNextFocus)
	{
		m_pNextFocus->SetFocus();
		if(m_pNextFocus->IsKindOf(RUNTIME_CLASS(CEdit)))
			((CEdit*)m_pNextFocus)->SetSel(0, 0xFFFF, TRUE);
	}
}


void CSearchPOIDlg::OnCustomerReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	if(m_chkNoShowSub.GetCheck() && pItemNotify->pColumn->GetItemIndex() == 0)
		CheckSubItemVisible(TRUE, (CSearchCusRecord*)pItemNotify->pRow->GetRecord());
	else
		OnSelectCustomer((CSearchCusRecord*)pItemNotify->pRow->GetRecord());
}

BOOL CSearchPOIDlg::OnSelectCustomer(CSearchCusRecord *pItem, BOOL bFocusNotChange)
{
	if(pItem)
	{
		if(m_pRcpPlace->SearchCustomerCNo(pItem->GetCustomer()->nCNo, 1, 1, pItem->GetTelID()))
		{
			if(!bFocusNotChange)
				SetNextFocus();

			return TRUE;
		}
	}
	return FALSE;
}

void CSearchPOIDlg::OnDongReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	//g_bana_log->Print("row = %d, col = %d\n", (CSearchDongRecord*)pItemNotify->pRow->GetIndex(), pItemNotify->pColumn->GetItemIndex());
	OnSelectDong((CSearchDongRecord*)pItemNotify->pRow->GetRecord(), pItemNotify->pColumn->GetItemIndex(), 0);
}

BOOL CSearchPOIDlg::OnSelectDong(CSearchDongRecord *pItem, int nCol, BOOL bFocusNotChange)
{
	if(pItem && pItem->m_pPOI[nCol]) 
	{
		SaveCurPOI(POI_COMPLETE_EVENT, pItem->m_pPOI[nCol], NULL, 
			pItem->m_strMarkupRegionName[nCol], pItem->m_pPOI[nCol]->GetRegionName());

		if(!bFocusNotChange)
			SetNextFocus();

		return TRUE;
	}
	return FALSE;
}

void CSearchPOIDlg::OnPOIReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	OnSelectPOI((CSearchPOIRecord*)pItemNotify->pRow->GetRecord());
}

BOOL CSearchPOIDlg::OnSelectPOI(CSearchPOIRecord *pItem, BOOL bFocusNotChange)
{
	if(pItem)  
	{
		BOOL bAutoCompletionFullChange = FALSE;
		CSearchPOI *pSearchPOI = pItem->m_pSearchPOI;
		CPOIUnit *pPOI = NULL, *pDetailPOI = NULL;
		CString strMark, strNor, strDMark, strDNor, strCPOI, strDisplayDong;

		if(pSearchPOI->pPOI->IsTempPOI())
		{
			if(pSearchPOI->pNearPOI)
			{
				pPOI = pSearchPOI->pNearPOI;
				pDetailPOI = pSearchPOI->pPOI;
				strMark = CSearchPOI::GetMarkupNormalName(pSearchPOI->pPOI, pSearchPOI->pNearPOI);
				strNor = pSearchPOI->pNearPOI->GetPOIName();
				strDMark = pSearchPOI->GetMarkupFullName();
				strDNor = pSearchPOI->pPOI->GetPOIName();
			}
			else
			{
				pPOI = pSearchPOI->pPOI->GetDongPOI();
				pDetailPOI = pSearchPOI->pPOI;
				strMark = pSearchPOI->GetMarkupRegionName();
				strNor = pSearchPOI->pPOI->GetDongPOI()->GetDong();
				strDMark = pSearchPOI->GetMarkupFullName();
				strDNor = pSearchPOI->pPOI->GetPOIName();
			}
		}
		else
		{
			BOOL bIsBasePOI =  pSearchPOI->pBasePOI ? TRUE : FALSE;
			CPOIUnit *pHelpPOI = bIsBasePOI ? pSearchPOI->pBasePOI : pSearchPOI->pNearPOI;

			if(pHelpPOI)
			{
				pPOI = pHelpPOI;
				pDetailPOI = pSearchPOI->pPOI;
				strMark = CSearchPOI::GetMarkupNormalName(pSearchPOI->pPOI, pHelpPOI);
				strNor = pHelpPOI->GetPOIName();
				strDMark = pSearchPOI->GetMarkupFullName();
				strDNor = pSearchPOI->pPOI->GetPOIName();
			}
			else 
			{
				pPOI = pSearchPOI->pPOI;
				strMark = pSearchPOI->GetMarkupFullName();
				strNor = pSearchPOI->pPOI->GetPOIName();
			}
		}

		if(!pSearchPOI->pPOI->IsDongPOI())
		{
			long nDistance = 300;
			CPOIUnit *pStationPOI = m_pPOINew->GetNearStationPOI(pSearchPOI->pPOI, nDistance);
			if(pStationPOI)
			{				
				strDisplayDong = pStationPOI->GetPOIName(FALSE);

				if(!m_chkUseMainPOIDisplayDong.GetCheck()) //동으로 표시 되기 원하는 옵션
					strDisplayDong = "";
			}
		}


		if(m_chkWebPoiToDong.GetCheck())
		{
			if(pItem->m_pSearchPOI->bWebSearch)
			{
				strDisplayDong = pPOI->GetDong();
			}
		}

		if(m_chkAddressToDong.GetCheck())
		{
			if(pItem->m_pSearchPOI->bAddressSearch)
			{
				strDisplayDong = pItem->m_pSearchPOI->pPOI->GetDong();
				//strDisplayDong = pPOI->GetDong();
			}
		}			

		BOOL bDisplayDong = TRUE;

		if(pDetailPOI)
		{
			bDisplayDong = FALSE;

			if((pPOI == pDetailPOI || pPOI->IsSimilarName(pDetailPOI)) && !pDetailPOI->m_bHasPhone && !pDetailPOI->IsTempPOI())  //신주소 검색시 지번 사라지는 현상방지 20210304 choe
			{
				strCPOI = pDetailPOI->GetPOIName(FALSE);
				pDetailPOI = NULL;
				strDMark.Empty();
				strDNor.Empty();
			}
			else if(pPOI->IsDongPOI())
				strCPOI = pDetailPOI->GetPOIName(TRUE);
			else
				strCPOI = pPOI->GetPOIName(FALSE);
		}

		SaveCurPOI(POI_COMPLETE_EVENT, pPOI, pDetailPOI, strMark, strNor, strDMark, strDNor, pSearchPOI->strAddress, strDisplayDong);

		if(!bFocusNotChange)
			SetNextFocus();

		return TRUE;
	}
	return FALSE;
}

void CSearchPOIDlg::OnOK()
{
//	CMyDialog::OnOK();
}

void CSearchPOIDlg::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent);

	if(nIDEvent == 0)
	{
		SearchPOI(m_strKeyword);
	}
	else if(nIDEvent == 1)
	{
#ifndef _STANDALONE
		if(LU->GetSimpleMap(FALSE, TRUE)->GetSafeHwnd())
			if(LU->GetSimpleMap(FALSE, TRUE)->IsWindowVisible())
				ShowPOIMap(TRUE);
#endif
	}
	else if(nIDEvent == 2)
	{
		long nID = GetNextNaverUID();

		m_Naver.ThreadRefresh(m_strNaverData, this, nID, m_bNaverSearchOnlyPhone, WEB_DEBUG_PRINT_TYPE);
		m_Kakao.ThreadRefresh(m_strNaverData, this, nID, m_bNaverSearchOnlyPhone, WEB_DEBUG_PRINT_TYPE);
	}


	CMyDialog::OnTimer(nIDEvent);
}

BOOL CSearchPOIDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_DOWN || pMsg->wParam == VK_UP)
		{
			if(pMsg->hwnd != m_wndPOI.GetSafeHwnd() && 
				pMsg->hwnd != m_wndDong.GetSafeHwnd() &&
				pMsg->hwnd != m_wndCustomer.GetSafeHwnd())
			{
				if(m_wndCustomer.GetRecords()->GetCount() > 0)
					m_wndCustomer.SetFocus();
				else if(m_nDongListCount > 0)
					m_wndDong.SetFocus();
				else if(m_wndPOI.GetRecords()->GetCount() > 0)
					m_wndPOI.SetFocus();

				return FALSE;
			}
			else if(pMsg->hwnd == m_wndDong.GetSafeHwnd())
			{
				if(pMsg->wParam == VK_DOWN)
					ListKeyDownNextFocus(m_wndDong, m_wndCustomer, m_wndPOI, VK_DOWN);
				return FALSE;
			}
			else if(pMsg->hwnd == m_wndCustomer.GetSafeHwnd())
			{
				if(pMsg->wParam == VK_UP)
					ListKeyDownNextFocus(m_wndCustomer, m_wndDong, m_wndDong, VK_UP);
				else 
					ListKeyDownNextFocus(m_wndCustomer, m_wndPOI, m_wndPOI, VK_DOWN);
				return FALSE;
			}
			else if(pMsg->hwnd == m_wndPOI.GetSafeHwnd())
			{
				if(pMsg->wParam == VK_UP)
					ListKeyDownNextFocus(m_wndPOI, m_wndCustomer, m_wndDong, VK_UP);
				return FALSE;
			}
		}
		else if(pMsg->wParam == VK_RETURN)
		{
			if(pMsg->hwnd == m_wndCustomer.GetSafeHwnd())
			{
				if(OnAutoSelectEvent(TYPE_CUSTOMER))
					return FALSE;
			}
			else if(pMsg->hwnd == m_wndPOI.GetSafeHwnd())
			{
				if(OnAutoSelectEvent(TYPE_POI))
					return FALSE;	
			}
			else if(pMsg->hwnd == m_wndDong.GetSafeHwnd())
			{
				if(OnAutoSelectEvent(TYPE_DONG))
					return FALSE;
			}
		}
		else if(pMsg->wParam == VK_RIGHT && pMsg->hwnd != m_wndDong.GetSafeHwnd())
		{
			m_pRcpPlace->GetSearchEdit()->SetFocus();
			return FALSE;
		}

	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

BOOL CSearchPOIDlg::ListKeyDownNextFocus(CXTPGridControl &wndMe, CXTPGridControl &wndNext, 
										CXTPGridControl &wndNext2, int nKey)
{
	if(nKey == VK_UP)
	{
		CXTPGridRow *pRow = wndMe.GetFocusedRow();

		if(pRow == NULL)
			return FALSE;

		if(pRow->GetIndex() == 0 || wndMe.GetRecords()->GetCount() == 0)
		{
			if(wndNext.GetRows()->GetCount() > 0)
			{
				wndNext.SetFocus();				
				wndNext.SetFocusedRow(wndNext.GetRows()->GetAt(wndNext.GetRows()->GetCount() - 1));
				return TRUE;
			}
			else if(wndNext.GetSafeHwnd() != wndNext2.GetSafeHwnd())
			{
				if(wndNext2.GetRows()->GetCount() > 0)
				{
					wndNext2.SetFocus();				
					wndNext2.SetFocusedRow(wndNext2.GetRows()->GetAt(wndNext2.GetRows()->GetCount() - 1));
					return TRUE;
				}
			}
		}
	}
	else if(nKey == VK_DOWN) 
	{
		CXTPGridRow *pRow = wndMe.GetFocusedRow();

		if(pRow == NULL)
			return FALSE;

		if(wndMe.GetRows()->GetCount() - 1 == pRow->GetIndex())
		{
			if(wndNext.GetRows()->GetCount() > 0)
			{
				wndNext.SetFocus();	
				wndNext.SetFocusedRow(wndNext.GetRows()->GetAt(0));
				return TRUE;
			}
			else if(wndNext.GetSafeHwnd() != wndNext2.GetSafeHwnd())
			{
				if(wndNext2.GetRows()->GetCount() > 0)
				{
					wndNext2.SetFocus();	
					wndNext2.SetFocusedRow(wndNext.GetRows()->GetAt(0));
					return TRUE;
				}
			}
		}
	}
	
	return FALSE;
}

BOOL CSearchPOIDlg::OnAutoSelectEvent(int nType, BOOL bFocusNotChange, BOOL bSelectWhenSingleResult)
{
	if(nType == TYPE_AUTO)
	{
		if(m_wndCustomer.GetRows()->GetCount() > 0)
			nType = TYPE_CUSTOMER;
		else if(m_wndPOI.GetRows()->GetCount() > 0 && 
			((CSearchPOIRecord*)m_wndPOI.GetSelectedRows()->GetAt(0)->GetRecord())->m_pSearchPOI->bAddressSearch)
			nType = TYPE_POI;
		else if(m_wndDong.GetRows()->GetCount() > 0)
			nType = TYPE_DONG;
		else 
		{
			if(m_pRcpPlace->m_nPlaceType == PLACE_TYPE_ORDER)
			{
				m_pRcpPlace->Clear();
				m_pRcpPlace->InitDiscountInfo();
			}
			
			return FALSE;
		}
	}

	if((nType == TYPE_CUSTOMER || nType == TYPE_PHONE) && m_wndCustomer.GetRows()->GetCount() > 0)
	{
		if(!bSelectWhenSingleResult || m_wndCustomer.GetRows()->GetCount() == 1)
		{
			if(m_wndCustomer.GetSelectedRows()->GetCount() > 0)
			{
				OnSelectCustomer((CSearchCusRecord*)m_wndCustomer.GetSelectedRows()->GetAt(0)->GetRecord(), bFocusNotChange);
				return TRUE;
			}
			else
			{
				OnSelectCustomer((CSearchCusRecord*)m_wndCustomer.GetRows()->GetAt(0)->GetRecord(), bFocusNotChange);
				return TRUE;
			}
		}
	}
	else if(nType == TYPE_POI && m_wndPOI.GetRows()->GetCount() > 0)
	{
		if(!bSelectWhenSingleResult || m_wndPOI.GetRows()->GetCount() == 1)
		{
			if(m_wndPOI.GetSelectedRows()->GetCount() > 0)
			{
				OnSelectPOI((CSearchPOIRecord*)m_wndPOI.GetSelectedRows()->GetAt(0)->GetRecord(), bFocusNotChange);
				return TRUE;
			}
			else
			{
				OnSelectPOI((CSearchPOIRecord*)m_wndPOI.GetRows()->GetAt(0)->GetRecord(), bFocusNotChange);
				return TRUE;
			}
		}
	}
	else if(nType == TYPE_DONG && m_wndDong.GetRows()->GetCount() > 0)
	{
		if(!bSelectWhenSingleResult || m_wndDong.GetRows()->GetCount() == 1)
		{
			g_bana_log->Print("m_wndDong = %d, %X, %X\n", 
						m_wndDong.GetSelectedRows()->GetCount() , 
						m_wndDong.GetSafeHwnd(),
						GetFocus()->GetSafeHwnd());

			if(m_wndDong.GetSelectedRows()->GetCount() > 0 && m_wndDong.GetSafeHwnd() == GetFocus()->GetSafeHwnd())
			{
				//g_bana_log->Print("m_wndDong.GetFocusedColumn()->GetItemIndex()= %d\n", m_wndDong.GetFocusedColumn()->GetItemIndex());

				OnSelectDong((CSearchDongRecord*)m_wndDong.GetSelectedRows()->GetAt(0)->GetRecord(), 
					m_wndDong.GetFocusedColumn()->GetItemIndex(),
					bFocusNotChange);
				return TRUE;
			}
			else
			{
				OnSelectDong((CSearchDongRecord*)m_wndDong.GetRows()->GetAt(0)->GetRecord(), 
					0,
					bFocusNotChange);
				return TRUE;
			}
		}
	}
	return FALSE;
}


void CSearchPOIDlg::SetDatabase(CMkDatabase *pDb)
{
	m_pDb = pDb;
}

void CSearchPOIDlg::SearchPOIJust(CString strKeyword)
{
	KillTimer(0);

	if(!strKeyword.IsEmpty())
		m_strKeyword = strKeyword;
	SearchPOI(m_strKeyword);
}

void CSearchPOIDlg::SaveCurPOI(long nType, CPOIUnit *pPOI, CPOIUnit *pDetailPOI,
							   CString strMarkupPOI, CString strNormalPOI,
							   CString strMarkupDetail, CString strNormalDetail,
							   CString strAddress, CString strDisplayDong)
{
	CPlaceInfo *pInfo = NULL;

	if(m_pRcpPlace == NULL)
		return; 

	if(m_pRcpPlace->GetPlaceType() == PLACE_TYPE_ORDER)		pInfo = &m_order;
	else if(m_pRcpPlace->GetPlaceType() == PLACE_TYPE_START) pInfo = &m_start;
	else if(m_pRcpPlace->GetPlaceType() == PLACE_TYPE_DEST)	pInfo = &m_dest; 
	else if(m_pRcpPlace->GetPlaceType() == PLACE_TYPE_CUSTOMER)	pInfo = &m_customer; 

	pInfo->m_pPOI = pPOI;
	pInfo->m_pDetailPOI = pDetailPOI;
	pInfo->m_pBasePOI = NULL;
 
	if(pInfo->m_pDetailPOI && pInfo->m_pDetailPOI->m_nClass == PN_TEMP)	//주소와 웹POI
	{  
		//문덕환이 삭제하라고해서 삭제하고 업데이트 했는데 다시 삭제하지람말고함 choi 2011-08-05
		CBranchInfo *pBi = LF->GetBranchInfo(m_nCustomerTable);
		if(pBi->bInitDongInfo && (m_pRcpPlace->GetPlaceType() == PLACE_TYPE_START || m_pRcpPlace->GetPlaceType() == PLACE_TYPE_DEST))
			m_pRcpPlace->Clear();

		CString strRegion = pInfo->m_pDetailPOI->GetRegionName();

		if(!strAddress.IsEmpty())
		{
			int nPos = strMarkupDetail.Find(strRegion);
			if(nPos >= 0)
			{
				strMarkupDetail.Insert(nPos + strRegion.GetLength(), " " + strAddress);
				strNormalDetail = strAddress + " " + strNormalDetail;
			}
		}

		if(strNormalDetail.Find(strRegion) < 0)
			strNormalDetail = strRegion + " " + strNormalDetail;

		m_pRcpPlace->SetAddress(strMarkupDetail, strNormalDetail);
		m_pRcpPlace->SetPOI(pInfo->m_pDetailPOI->GetDongPOI(FALSE));
		m_pRcpPlace->SetDetailPos(pInfo->m_pDetailPOI->GetPosX(), pInfo->m_pDetailPOI->GetPosY());
	
		if(pInfo->m_pDetailPOI->m_bHasPhone && m_chkRegisterPhoneCustomer.GetCheck())
		{
			CString strPhone = pInfo->m_pDetailPOI->GetPhoneNumber();

			//if(m_pRcpPlace->GetPhone().IsEmpty())
				m_pRcpPlace->SetPhone(strPhone);

			//if(m_pRcpPlace->GetCompany().IsEmpty())
				m_pRcpPlace->SetCompany(pInfo->m_pDetailPOI->GetPOIName());
		}


		MoveMap(pInfo->m_pDetailPOI);
	}
	else if(!pInfo->m_pDetailPOI && pInfo->m_pPOI->IsDongPOI())	//동
	{
		//문덕환이 삭제하라고해서 삭제하고 업데이트 했는데 다시 삭제하지람말고함 choi 2011-08-05
		CBranchInfo *pBi = LF->GetBranchInfo(m_nCustomerTable);
		if(pBi->bInitDongInfo && (m_pRcpPlace->GetPlaceType() == PLACE_TYPE_START || m_pRcpPlace->GetPlaceType() == PLACE_TYPE_DEST))
			m_pRcpPlace->Clear();

		CString strDAddress =  strAddress.GetLength() != 0 ? strAddress : pInfo->m_pPOI->GetRegionName();
		CString strPOI =  strAddress.GetLength() != 0 ? strAddress : pInfo->m_pPOI->GetRegionName();
		m_pRcpPlace->SetAddress( strAddress.GetLength() != 0 ? CSearchPOI::GetMarkupLastPartHilight(strDAddress) : CSearchPOI::GetMarkupLastPartHilight(pPOI->GetFullName()), strDAddress);
		m_pRcpPlace->SetPOI(pInfo->m_pPOI->GetDongPOI(FALSE));
		m_pRcpPlace->SetDetailPos(0, 0);
		MoveMap(pInfo->m_pPOI);
	}
	else	//실제POI
	{
		long nDongID;
		CPOIUnit *pPOI = pInfo->m_pDetailPOI ? pInfo->m_pDetailPOI : pInfo->m_pPOI;
		
		if(pPOI->IsMainPOI() || pPOI->IsMobilePOI())
		{
			CString strFullAddr = pInfo->m_pPOI->GetRegionName() + " " + pInfo->m_pPOI->GetPOIName();
			m_pRcpPlace->SetAddress(CSearchPOI::GetMarkupLastPartHilight(strFullAddr), strFullAddr);
			m_pRcpPlace->SetPOI(pInfo->m_pPOI->GetDongPOI(FALSE));
			m_pRcpPlace->SetDetailPos(pInfo->m_pPOI->GetPosX(), pInfo->m_pPOI->GetPosY());
			MoveMap(pPOI);
		}
		else if(CPOIDataAddress::GetNearAddress(m_pDb, pPOI->m_nPosX, pPOI->m_nPosY, nDongID, strAddress))
		{
			if(pPOI->GetDongID() != nDongID)
			{
				CString strFullAddr = pPOI->GetRegionName() + " " + pPOI->GetPOIName();
				m_pRcpPlace->SetAddress(CSearchPOI::GetMarkupLastPartHilight(strFullAddr), strFullAddr);
				m_pRcpPlace->SetPOI(pPOI->GetDongPOI(FALSE));
				m_pRcpPlace->SetDetailPos(pPOI->GetPosX(), pPOI->GetPosY());
				MoveMap(pPOI);
			}
			else
			{
				CString strFullAddr = strAddress + " " + pPOI->GetPOIName();
				CMarkupStatic *p = m_pRcpPlace->GetAddressStatic();
				m_pRcpPlace->SetAddress(CSearchPOI::GetMarkupLastPartHilight(strFullAddr), strFullAddr);
				m_pRcpPlace->SetPOI(pPOI->GetDongPOI(FALSE));
				m_pRcpPlace->SetDetailPos(pPOI->GetPosX(), pPOI->GetPosY());
				MoveMap(pPOI);
			}			
		}
	}

	if(strDisplayDong.GetLength() > 0)
		m_pRcpPlace->SetDisplayDong(strDisplayDong);
	else if(m_chkUseMainPOIDisplayDong.GetCheck() && pInfo->m_pDetailPOI && !pInfo->m_pPOI->IsDongPOI())
		m_pRcpPlace->SetDisplayDong(pInfo->m_pPOI->GetPOIName());
	else
		m_pRcpPlace->SetDisplayDong();

	m_pRcpPlace->CheckDelType();

	if(m_pRcpPlace->GetPlaceType() == PLACE_TYPE_CUSTOMER && m_pParentWnd)
		((CCustomerDlg*)m_pParentWnd)->SetDisplayAddrEdt();
 
	//GetParentWnd()->SendMessage(WM_CHANGE_POI, nType | m_pRcpPlace->GetPlaceType(), (LPARAM)pInfo);
	GetParentWnd()->SendMessage(WM_CHANGE_POI, (WPARAM)NULL, (LPARAM)NULL);

}

void CSearchPOIDlg::OnClose()
{
	m_bClosedByUser = TRUE;
	ShowWindow(SW_HIDE);
}

void CSearchPOIDlg::SetParentWnd(CWnd *pWnd)
{
	m_pParentWnd = pWnd;
}

CWnd* CSearchPOIDlg::GetParentWnd()
{
	return m_pParentWnd ? m_pParentWnd : GetParent();
}

void CSearchPOIDlg::DeleteSearchPOIRecord()
{
	CSearchPOIRecordVector::iterator it;

	for(it = m_vecSearchPOIRecord.begin(); it != m_vecSearchPOIRecord.end(); it++)
		delete (*it);

	m_vecSearchPOIRecord.clear();
}

LONG CSearchPOIDlg::OnSelectPOIOnMap(WPARAM wParam, LPARAM lParam)
{
	OnSelectPOI((CSearchPOIRecord*)wParam);
	return 0;
}

void CSearchPOIDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CMyDialog::OnLButtonDown(nFlags, point);
}

void CSearchPOIDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CMyDialog::OnWindowPosChanging(lpwndpos);
	m_Magnetic.PosChanging(lpwndpos);
}

void CSearchPOIDlg::OnBnClickedCloseBtn()
{
	OnClose();
}

void CSearchPOIDlg::SetLogiMap(CLogiMapNew *pLogiMap)
{
	m_pLogiMap = pLogiMap;
}

void CSearchPOIDlg::MoveMap(long nPosX, long nPosY)
{
	if(m_pLogiMap)
		m_pLogiMap->AddPointPOI(TRUE, 
							m_pRcpPlace->GetPlaceName() + ": " + m_pRcpPlace->GetAddress(),
							nPosX, nPosY, "", "POINT",
							-1, POINT_POI, m_pRcpPlace->GetPlaceType());
}

void CSearchPOIDlg::MoveMap(CPOIUnit *pPOI)
{
	if(m_pLogiMap)
		m_pLogiMap->AddPointPOI(TRUE, 
							m_pRcpPlace->GetPlaceName() + ": " + m_pRcpPlace->GetAddress(), 
							pPOI->m_nPosX, pPOI->m_nPosY, "", "POINT",
							-1, POINT_POI, m_pRcpPlace->GetPlaceType());
}

void CSearchPOIDlg::SetCustomerTable(long nCompany)
{
	m_nCustomerTable = nCompany;
}

void CSearchPOIDlg::OnBnClickedAlwaysShowCheck()
{
	AfxGetApp()->WriteProfileInt("SearchPOIDlg", "AlwaysShow", m_chkAlwaysShow.GetCheck());
}

void CSearchPOIDlg::OnBnClickedRefreshBtn()
{
	m_cus.GetNewCustomer();
}

void CSearchPOIDlg::AddDongVectorToList(SEARCH_POI_VEC &vecDong)
{
	SEARCH_POI_VEC::iterator it;
	CSearchDongRecord *pRecord = NULL;
	long i = 0;
	long nCol = 0;

	for(it = vecDong.begin(); it != vecDong.end(); it++)
	{
		nCol = i % DONG_COL_COUNT;

		if(nCol == 0)
			pRecord = new CSearchDongRecord;

		pRecord->AddRecordItem(it->second.pPOI, it->second.GetMarkupRegionName());

		if(nCol == DONG_COL_COUNT - 1)
		{
			m_wndDong.AddRecord(pRecord);
			pRecord = NULL;
		}

		i++;
	}

	if(pRecord)
	{
		for(int k = nCol; k < DONG_COL_COUNT;  k++)
			pRecord->AddDummyItem();

		m_wndDong.AddRecord(pRecord);
	}

	m_nDongListCount = vecDong.size();
}

CPOIUnit* CSearchPOIDlg::GetDongListInfo(int nItem, CString &strMarkup)
{
	CXTPGridRow *pRow = m_wndDong.GetRows()->GetAt(nItem / DONG_COL_COUNT);
	if(pRow)
	{
		CSearchDongRecord *pRecord = (CSearchDongRecord*)pRow->GetRecord();
		if(pRecord)
		{
			strMarkup = pRecord->m_strMarkupRegionName[nItem % DONG_COL_COUNT];
			return pRecord->m_pPOI[nItem % DONG_COL_COUNT];
		}
	}

	strMarkup.Empty();
	return NULL;
}

void CSearchPOIDlg::ResetContent(int nPOIType)
{
	if(nPOIType & POI_NORMAL)
	{
		m_vecPOI.clear();
		m_pPOINew->DeletePOIGroup((UINT)this);
		m_pPOINew->DeletePOIGroup(m_nCurNaverID - 1);

		/*
		for(int i = 0; i < m_wndPOI.GetRecords()->GetCount(); i++)
		{
			CSearchPOIRecord *pRecord = (CSearchPOIRecord*)m_wndPOI.GetRecords()->GetAt(i);
			if(pRecord->m_pSearchPOI)
			{
				if(pRecord->m_pSearchPOI->bWebSearch)
					delete pRecord->m_pSearchPOI;
			}			
		}
		*/

		m_wndPOI.ResetContent(FALSE);
	}

	if(nPOIType & POI_DONG)
	{
		m_nDongListCount = 0;
		m_wndDong.ResetContent(FALSE);
	}

	if(nPOIType & POI_CUSTOMER)
	{
		m_wndCustomer.ResetContent();
	}

	if(nPOIType & POI_WEB)
	{		
		long nIndex = 0;
		long nCount = m_wndPOI.GetRecords()->GetCount();

		for(int i = 0; i < nCount; i++)
		{
			BOOL bDelete = FALSE;
			CSearchPOIRecord *pRecord = (CSearchPOIRecord*)m_wndPOI.GetRecords()->GetAt(nIndex);

			if(pRecord->m_pSearchPOI)
			{
				if(pRecord->m_pSearchPOI->bWebSearch)
				{
					m_wndPOI.RemoveRecordEx(pRecord, FALSE);
					bDelete = TRUE;
				}				
			}

			if(bDelete == FALSE)
				nIndex++;

			m_wndPOI.Populate();
		}
	}
}

void CSearchPOIDlg::PopulateList(int nPOIType)
{
	if(nPOIType & POI_NORMAL)
	{
		m_wndPOI.Populate();
		for(int i = 0; i < m_wndPOI.GetRecords()->GetCount(); i++)
			((CSearchPOIRecord*)(m_wndPOI.GetRecords()->GetAt(i)))->RedrawMarkupName();
		m_wndPOI.RedrawControl();
	}

	if(nPOIType & POI_DONG)
	{
		m_wndDong.Populate();
		for(int i = 0; i < m_wndDong.GetRecords()->GetCount(); i++)
			((CSearchDongRecord*)(m_wndDong.GetRecords()->GetAt(i)))->RedrawMarkupName();
		m_wndDong.RedrawControl();
	}

	if(nPOIType & POI_CUSTOMER)
	{
		CheckSubItemVisible(FALSE);
		m_wndCustomer.Populate();
		for(int i = 0; i < m_wndCustomer.GetRecords()->GetCount(); i++)
			((CSearchCusRecord*)(m_wndCustomer.GetRecords()->GetAt(i)))->RedrawMarkupName();
		m_wndCustomer.RedrawControl();
	}

	ResizeList();
}

/*
void CSearchPOIDlg::AutoSelectPOI(int nPOIType)
{
	if(m_wndCustomer.GetRecords()->GetCount() > 0 && (nPOIType & POI_CUSTOMER))
		OnSelectCustomer((CSearchCusRecord*)m_wndCustomer.GetRows()->GetAt(0)->GetRecord());
	else if(m_wndPOI.GetRecords()->GetCount() > 0 && (nPOIType & POI_NORMAL))
		OnSelectPOI((CSearchPOIRecord*)m_wndPOI.GetRows()->GetAt(0)->GetRecord());
	else if(m_wndDong.GetRecords()->GetCount() > 0 && (nPOIType & POI_DONG))
		OnSelectDong((CSearchDongRecord*)m_wndDong.GetRows()->GetAt(0)->GetRecord(), 0);
}
*/

CHttpParser *CSearchPOIDlg::GetNaver()
{
	return &m_Naver;
}

LONG CSearchPOIDlg::OnRecvWebRecord(WPARAM wParam, LPARAM lParam)
{
	if(wParam == 0)
	{
		//g_bana_log->Print(" OnRecvWebRecord 0"); 

		QUERY_INFO *pQI = (QUERY_INFO*)lParam;

		if(pQI->nUID == m_nCurNaverID && pQI->strKeyword == m_strPreData)
		{
			//PopulateList(POI_NORMAL);

			ResetContent(POI_WEB);

			CompareWebPoiSub(&m_vecDaum, &m_vecNaver);

			for(int i=0; i<m_vecDaum.size(); i++)
				m_wndPOI.AddRecord(new CSearchPOIRecord(m_vecDaum.at(i), DAUM));

			for(int i=0; i<m_vecNaver.size(); i++)
				m_wndPOI.AddRecord(new CSearchPOIRecord(m_vecNaver.at(i), NAVER));

			PopulateList(POI_NORMAL);

			if(pQI->bPhoneSearchAutoComplete)
				if(m_wndPOI.GetRecords()->GetCount() > 0)
					if(OnSelectPOI((CSearchPOIRecord*)m_wndPOI.GetRecords()->GetAt(m_wndPOI.GetRecords()->GetCount() - 1), TRUE))
						m_pParentWnd->PostMessage(WM_USER + 0x3333, (WPARAM)new CString(pQI->strKeyword), 0);
		}

		delete pQI;
	}
	else
	{
		//g_bana_log->Print(" OnRecvWebRecord 1");   

		PORTAR_RESULT_RECORD *pRecord = (PORTAR_RESULT_RECORD*)wParam;

		if(pRecord->QI.nUID == m_nCurNaverID && pRecord->QI.strKeyword == m_strPreData)
		{
			if(pRecord->QI.nApiType == NAVER)
				m_vecNaver.push_back(pRecord->pSearchPOI);
			else if(pRecord->QI.nApiType == DAUM)
				m_vecDaum.push_back(pRecord->pSearchPOI);

			
			//m_wndPOI.AddRecord(new CSearchPOIRecord(pRecord->pSearchPOI, pRecord->QI.nApiType));
			//PopulateList(POI_NORMAL);

			/*
			if(m_bWebPosAutoSelect)
			{
				CString strTemp = "";
				
				if(pRecord->pSearchPOI->pPOI)
					strTemp = pRecord->pSearchPOI->pPOI->GetPhoneNumber();

				if(m_ci.m_strDDD == strTemp.Left(m_ci.m_strDDD.GetLength()))
				{
					if(m_wndPOI.GetRecords()->GetCount() == 1 && 
						m_wndCustomer.GetRecords()->GetCount() == 0)
					{
						if(OnSelectPOI((CSearchPOIRecord*)m_wndPOI.GetRecords()->GetAt(m_wndPOI.GetRecords()->GetCount() - 1), TRUE))
							m_pParentWnd->PostMessage(WM_USER + 0x3333, (WPARAM)new CString(pRecord->QI.strKeyword), 0);
					}
				}				
			}
			*/
		}
		else
		{
			//g_bana_log->Print("RecvWeb SKIP: %s\n", pRecord->pSearchPOI->pPOI->GetPOIName());
			delete pRecord->pSearchPOI;
		}

		delete pRecord;
	}

	return 0;
}


#define PER_HEIGHT	19
#define HEADER_BASE	3
#define HEADER_HEIGHT 25

void CSearchPOIDlg::ResizeList()
{
	if(m_wndCustomer.GetSafeHwnd())
	{
		CRect rcDong, rcCustomer, rcPOI;

		m_wndDong.GetWindowRect(rcDong);
		m_wndCustomer.GetWindowRect(rcCustomer);
		m_wndPOI.GetWindowRect(rcPOI);

		ScreenToClient(rcDong);
		ScreenToClient(rcCustomer);
		ScreenToClient(rcPOI);

		if(m_lsDong.m_rcOri.Height() == 0)
		{			
			m_lsDong.Set(&m_wndDong, rcDong, 1, 2, PER_HEIGHT, HEADER_BASE);
			m_lsCustomer.Set(&m_wndCustomer, rcCustomer, 9, 11, PER_HEIGHT, HEADER_HEIGHT);
			m_lsPOI.Set(&m_wndPOI, rcPOI, 3, 10, PER_HEIGHT, HEADER_HEIGHT);
		}

		m_lsDong.SetCur(rcDong);
		m_lsCustomer.SetCur(rcCustomer);
		m_lsPOI.SetCur(rcPOI);

		if(!m_lsDong.NeedMove() && !m_lsCustomer.NeedMove() && !m_lsPOI.NeedMove())
		{
			m_lsDong.MoveOri();
			m_lsCustomer.MoveOri();
			m_lsPOI.MoveOri();
		}
		else
		{
			m_lsDong.MoveTo(m_lsCustomer, m_lsPOI);
			m_lsDong.Move();
			m_lsCustomer.Move();
			m_lsPOI.Move();
		}

		m_wndDong.GetWindowRect(rcDong);
		m_wndCustomer.GetWindowRect(rcCustomer);

		ScreenToClient(rcDong);
		ScreenToClient(rcCustomer);

		if(m_wndCustomer.IsVScrollBarVisible() && m_wndDong.GetRecords()->GetCount() == 0)
		{
			if(m_wndDong.IsWindowVisible())
				m_wndDong.ShowWindow(SW_HIDE);

			if(abs(m_lsCustomer.m_rcOri.top - rcCustomer.top) < 5)
			{
				rcCustomer.top = rcDong.top;
				m_wndCustomer.MoveWindow(rcCustomer);
			}
		}
		else
		{
			if(!m_wndDong.IsWindowVisible())
				m_wndDong.ShowWindow(SW_SHOW);
		}
	}
}

void CSearchPOIDlg::OnBnClickedSetupBtn()
{
	CSearchPOISetupDlg dlg;
	if(dlg.DoModal() == IDOK)
		RefreshProfile(TRUE);
}

void CSearchPOIDlg::RefreshProfile(BOOL bSave)
{
	if(bSave)
	{
		AfxGetApp()->WriteProfileInt("SearchPOIDlg", "AlwaysShow", m_chkAlwaysShow.GetCheck());
		AfxGetApp()->WriteProfileInt("SearchPOIDlg", "SearchWeb", m_chkSearchWeb.GetCheck());
		AfxGetApp()->WriteProfileInt("SearchPOIDlg", "UseMainPOIDisplayDong", m_chkUseMainPOIDisplayDong.GetCheck());
		AfxGetApp()->WriteProfileInt("SearchPOIDlg", "RegisterPhoneCustomer", m_chkRegisterPhoneCustomer.GetCheck());
		AfxGetApp()->WriteProfileInt("SearchPOIDlg", "CustomerCharOrder", m_chkCustomerCharOrder.GetCheck());
		AfxGetApp()->WriteProfileInt("SearchPOIDlg", "NoShowSub", m_chkNoShowSub.GetCheck());
		AfxGetApp()->WriteProfileInt("SearchPOIDlg", "SearchRoadAddress", m_chkSearchRoadAddress.GetCheck());
		AfxGetApp()->WriteProfileInt("SearchPOIDlg", "WebPoiToDong", m_chkWebPoiToDong.GetCheck());
		AfxGetApp()->WriteProfileInt("SearchPOIDlg", "UseDirectDistance", m_chkUseDirectDistance.GetCheck());
		AfxGetApp()->WriteProfileInt("SearchPOIDlg", "AddressToDong", m_chkAddressToDong.GetCheck());
	}
	else
	{
		m_chkAlwaysShow.SetCheck(AfxGetApp()->GetProfileInt("SearchPOIDlg", "AlwaysShow", 0));
		m_chkSearchWeb.SetCheck(AfxGetApp()->GetProfileInt("SearchPOIDlg", "SearchWeb", 1));
		m_chkUseMainPOIDisplayDong.SetCheck(AfxGetApp()->GetProfileInt("SearchPOIDlg", "UseMainPOIDisplayDong", 0));
		m_chkRegisterPhoneCustomer.SetCheck(AfxGetApp()->GetProfileInt("SearchPOIDlg", "RegisterPhoneCustomer", 1));
		m_chkCustomerCharOrder.SetCheck(AfxGetApp()->GetProfileInt("SearchPOIDlg", "CustomerCharOrder", 0));
		m_chkNoShowSub.SetCheck(AfxGetApp()->GetProfileInt("SearchPOIDlg", "NoShowSub", 0));
		m_chkSearchRoadAddress.SetCheck(AfxGetApp()->GetProfileInt("SearchPOIDlg", "SearchRoadAddress", 1));
		m_chkWebPoiToDong.SetCheck(AfxGetApp()->GetProfileInt("SearchPOIDlg", "WebPoiToDong", 0));
		m_chkUseDirectDistance.SetCheck(AfxGetApp()->GetProfileInt("SearchPOIDlg", "UseDirectDistance", 0));
		m_chkAddressToDong.SetCheck(AfxGetApp()->GetProfileInt("SearchPOIDlg", "AddressToDong", 0));
	}

	m_cus.SetCharOrdering(m_chkCustomerCharOrder.GetCheck());
}

LONG CSearchPOIDlg::OnMyStnClicked(WPARAM wParam, LPARAM lParam)
{
	CPoint pt;
	::GetCursorPos(&pt);	
	OnLButtonDown(0, pt);
	return 0;
}

void CSearchPOIDlg::CheckSubItemVisible(BOOL bPopulate, CSearchCusRecord *pCus)
{
	BOOL bFoundCus = FALSE;

	for(int i = 0; i < m_wndCustomer.GetRecords()->GetCount(); i++)
	{
		CSearchCusRecord *pRecord = (CSearchCusRecord*)m_wndCustomer.GetRecords()->GetAt(i);

		if(pCus)
		{
			if(bFoundCus)
			{
				if(pRecord->IsChild())
				{
					pCus->SetExpand(!pRecord->IsVisible());
					pRecord->SetVisible(!pRecord->IsVisible());
				}
				else
				{
					bFoundCus = FALSE;
					break;
				}
			}
			else if(pCus == pRecord)
			{
				bFoundCus = TRUE;
			}
		}
		else
		{
			pRecord->SetVisible(!m_chkNoShowSub.GetCheck() || !pRecord->IsChild());
		}
	}

	if(bPopulate)
		m_wndCustomer.Populate();
}

void CSearchPOIDlg::OnBnClickedNoShowSubCheck()
{
	CheckSubItemVisible();
	RefreshProfile(TRUE);
	m_wndCustomer.GetColumns()->GetAt(0)->SetVisible(m_chkNoShowSub.GetCheck());
}	


UINT CSearchPOIDlg::GetNextNaverUID()
{
	m_nCurNaverID = (UINT)this + m_nNaverUID++;
	//m_nCurNaverID = m_nNaverUID++;
	return m_nCurNaverID;
}

// DB 주소 업데이트가 되지 않아 최근에 바뀐 행정구역에 대해 옛날 주소를 리턴하는 문제가 있어,
// 이러한 경우 Web 에서 검색할 수 있게 SearchRoadAddress() 를 FALSE 로 리턴시키는 함수
BOOL CSearchPOIDlg::IsExceptionAddress()
{
	CString keyword = m_strKeyword;
	if (keyword.Find("영통로") >= 0)
		return FALSE;

	return TRUE;
}

SEARCH_POI_VEC CSearchPOIDlg::SortPoiByNearCity(SEARCH_POI_VEC vec_in)
{
	SEARCH_POI_VEC vec_out;
	for (int j = 0; j < near_sido_.size(); j++) {
		for (int i = 0; i < vec_in.size();) {
			CPOIUnit* pPOI = vec_in[i].second.pPOI;
			if (!pPOI)
				continue;

			CString sido = pPOI->GetSido();
			CString center_sido = near_sido_[j];

			if (center_sido == sido) {
				vec_out.push_back(vec_in[i]);
				vec_in.erase(vec_in.begin() + i);
			} else {
				i++;
			}
		}
	}

	for (int i = 0; i < vec_in.size(); i++) {
		vec_out.push_back(vec_in[i]);
	}

	return vec_out;
}

BOOL CSearchPOIDlg::SearchRoadAddress()
{
	if(InitState() && m_chkSearchRoadAddress.GetCheck() && (m_bAutoCompleteOnce || m_strPreData != m_strKeyword))
	{
		if(m_strKeyword.GetLength() > 0 && IsExceptionAddress())
		{
			SEARCH_POI_VEC vecPOI;
			SEARCH_POI_VEC::iterator it;
			CRoadAddress ra(m_pPOINew);

			if(ra.SearchRoadAddress(m_strKeyword, vecPOI))
			{
				ResetContent(POI_NORMAL);
				m_vecPOI.swap(vecPOI);
				m_vecPOI = SortPoiByNearCity(m_vecPOI);

				int nCount = 0;
				CPOIUnit *pPrePOI = NULL;
				for(it = m_vecPOI.begin(); it != m_vecPOI.end(); it++)
				{
					CSearchPOI *pSearchPOI = &it->second;

					//NewPOI로 생성된 POI는 포인터를 계속 사용할 수 없다. 
					//리스트가 갱신되거나 다이얼로그가 종료되면 할당된 메모리가 제거되고, 포인터는 소멸된다. 
					CPOIUnit *pPOI = m_pPOINew->NewPOI((UINT)this, pSearchPOI->pPOI, pSearchPOI->nNewPosX, 
						pSearchPOI->nNewPosY, pSearchPOI->szKeyword);

					pSearchPOI->pPOI = pPOI;
					pSearchPOI->pPrePOI = pPrePOI;

					CSearchPOIRecord *pRecord = (CSearchPOIRecord*)m_wndPOI.AddRecord(new CSearchPOIRecord(pSearchPOI));

					//if(it == m_vecPOI.begin()  && !GetLockState())
					//	OnSelectPOI(pRecord, FALSE, FALSE);

					pPrePOI = pPOI;
				}

				PopulateList(POI_NORMAL);
				//AutoSelectPOI(POI_NORMAL);


				ResetContent(POI_DONG);
				SEARCH_POI_VEC vecDong, vecPOI;
				SEARCH_POI_VEC::iterator it;
				m_pPOINew->SearchPOIWithDong(m_strKeyword, vecPOI, vecDong, FALSE, FALSE);
				m_pPOINew->GetLastKeyword(m_strDongKeyword, m_strPOIKeyword);
				AddDongVectorToList(vecDong);
				PopulateList(POI_DONG);

				m_strPreData = m_strKeyword;	
				return TRUE;
			}
		}
	}

	return FALSE;
	/*
	if(InitState() && m_chkSearchRoadAddress.GetCheck() && (m_bAutoCompleteOnce || m_strPreData != m_strKeyword))
	{
		if(m_strKeyword.GetLength() > 0)
		{
			SEARCH_POI_VEC vecPOI;
			SEARCH_POI_VEC::iterator it;
			CRoadAddress ra(m_pPOINew);

			if(!ra.SearchRoadAddress(m_strKeyword, vecPOI))
				return FALSE;
			{
				ResetContent(POI_NORMAL);
				m_vecPOI.swap(vecPOI);

				int nCount = 0;
				CPOIUnit *pPrePOI = NULL;
				for(it = m_vecPOI.begin(); it != m_vecPOI.end(); it++)
				{
					CPOIUnit *pTemp = it->second.pPOI;

					//NewPOI로 생성된 POI는 포인터를 계속 사용할 수 없다. 
					//리스트가 갱신되거나 다이얼로그가 종료되면 할당된 메모리가 제거되고, 포인터는 소멸된다. 
					CPOIUnit *pPOI = m_pPOINew->NewPOI((UINT)this, it->second.pPOI, it->second.nNewPosX, 
						it->second.nNewPosY, it->second.szKeyword);

					it->second.pPOI = pPOI;
					it->second.pPrePOI = pPrePOI;

					CSearchPOIRecord *pRecord = (CSearchPOIRecord*)m_wndPOI.AddRecord(new CSearchPOIRecord(&it->second));

					//if(it == m_vecPOI.begin())
					//	OnSelectPOI(pRecord, TRUE);

					pPrePOI = pPOI;
				}

				PopulateList(POI_NORMAL);

				ResetContent(POI_DONG);
				SEARCH_POI_VEC vecDong, vecPOI;
				SEARCH_POI_VEC::iterator it;
				m_pPOINew->SearchPOIWithDong(m_strKeyword, vecPOI, vecDong, FALSE, FALSE);
				m_pPOINew->GetLastKeyword(m_strDongKeyword, m_strPOIKeyword);
				AddDongVectorToList(vecDong);
				PopulateList(POI_DONG);

				m_strPreData = m_strKeyword;	
				return TRUE;
			}
		}
	}

	return FALSE;
	*/
}

unsigned __stdcall TheadSearchAddress(void *arg)
{
	CSearchPOIDlg *pDlg = (CSearchPOIDlg*)arg;

	pDlg->m_cJuso.SearchJuso(pDlg->m_strKeyword);

	return 0;
}

BOOL CSearchPOIDlg::SearchRoadAddress2()
{
	HANDLE hThread;
	DWORD dwThreadID;

	if(InitState() && m_chkSearchRoadAddress.GetCheck() && (m_bAutoCompleteOnce || m_strPreData != m_strKeyword))
	{
		if(m_strKeyword.GetLength() > 0)
		{
			hThread = (HANDLE)_beginthreadex(NULL, 0, &TheadSearchAddress, (void*)this, 0, (unsigned*)&dwThreadID);

			DWORD dwRet = WaitForSingleObject(hThread, 1000);
			
			if(dwRet == WAIT_TIMEOUT)
				return FALSE;

			if(dwRet == WAIT_FAILED)
				return FALSE;

			//m_cJuso.SearchJuso(m_strKeyword);

			MAP_JUSO *pMap = m_cJuso.GetJusoMap();

			if(pMap->size() <= 0)
				return FALSE;

			CPOIUnit *pPrePOI = NULL;
			ResetContent(POI_NORMAL);

			for(MAP_JUSO::iterator it = pMap->begin(); it != pMap->end(); it++)
			{
				CSearchPOI *p = it->second;
				CPOIUnit *pTemp = it->second->pPOI;

				CPOIUnit *pPOI = m_pPOINew->NewPOI((UINT)this, p->pPOI, p->nNewPosX, 
					p->nNewPosY, p->szKeyword);

				it->second->pPOI = pPOI;
				it->second->pPrePOI = pPrePOI;

				CSearchPOIRecord *pRecord = (CSearchPOIRecord*)m_wndPOI.AddRecord(new CSearchPOIRecord(p)); 

				pPrePOI = pPOI;
			}

			PopulateList(POI_NORMAL);

			ResetContent(POI_DONG);
			SEARCH_POI_VEC vecDong, vecPOI;
			SEARCH_POI_VEC::iterator it;
			m_pPOINew->SearchPOIWithDong(m_strKeyword, vecPOI, vecDong, FALSE, FALSE);
			m_pPOINew->GetLastKeyword(m_strDongKeyword, m_strPOIKeyword);
			AddDongVectorToList(vecDong);
			PopulateList(POI_DONG);

			m_strPreData = m_strKeyword;	
			return TRUE; 

		}
	}

	return FALSE;
}

void CSearchPOIDlg::CompareWebPoiSub(CSearchHttpPoi *vecOriginal, CSearchHttpPoi *vecDelete)
{
	for(int i=0; i<vecOriginal->size(); i++)
	{
		CSearchPOI *pPoiNaver = vecOriginal->at(i);

		long nDaumCount = vecDelete->size();

		//for(int j=0; j<nDaumCount; j++)		
		for(CSearchHttpPoi::iterator it = vecDelete->begin(); it != vecDelete->end();)
		{
			CSearchPOI *pPoiDaum = (CSearchPOI*)(*it);	

			long nDistance = pPoiNaver->pPOI->GetDistanceMeter(pPoiDaum->pPOI);

			if(nDistance <= 50) //50미터이내 동일지명
			{
				delete pPoiDaum;
				vecDelete->erase(it);
			}
			else 
				it++;

			//GetLog()->Print("거리 %d\ 네이버 %s, 다음 %s, \r\n",nDistance, CString(pPoiNaver->pPOI->m_szName), CString(pPoiDaum->pPOI->m_szName));
		}

		//if(m_vecDaum.size()> 0)		
		//	CSearchPOI *pPoi1 = m_vecDaum.at(0);
	}
}
