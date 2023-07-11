// RcpViewBase.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "RcpViewBase.h"
#include "RcpDlg.h"
#include "RcpPageCTIForm.h"
#include "RcpPageMemoForm.h"
#include "RcpPageMapForm.h"
#include "RcpPageInfoForm.h"
#include "MyReportPaintManager.h"
#include "SetRcpPageDlg.h"
#include "MkLock.h"
#include "MakePOIData.h"
#include "CustomerData.h"
#include "RcpPageRecordFileForm.h"
#include "RcpPageMissingCallForm.h"
#include "RcpInsungDlg.h"
#include "RcpPageWCountForm.h"
#include "RcpDlgAdmin.h"

// CRcpViewBase

IMPLEMENT_DYNCREATE(CRcpViewBase, CMyFormView)

CRcpViewBase::CRcpViewBase()
	: CMyFormView(IDD_RCP_VIEW)
{
	m_bDialogMode = FALSE;
	m_nSavedFormHegiht = 0;
	m_nFormHeight = AfxGetApp()->GetProfileInt("RcpPage", "FormHeight", TAB_FORM_HEIGHT);

	if (m_nFormHeight < 30 || m_nFormHeight > 500)
		m_nFormHeight = TAB_FORM_HEIGHT;

	m_pRecordFileForm = NULL;
	m_pMissingCallForm = NULL;
}

CRcpViewBase::~CRcpViewBase()
{
	if (LU->GetRcpView() && (CRcpView*)this == (CRcpView*)LU->GetRcpView())
	{
		CString strTemp; long nSize;
		SaveReportState(strTemp, nSize);
	}
}

BEGIN_MESSAGE_MAP(CRcpViewBase, CMyFormView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_NOTIFY(XTP_NM_GRID_HEADER_RCLICK, IDC_REPORT_LIST_RCPPAGE, OnReportColumnRClick)
END_MESSAGE_MAP()


// CRcpViewBase 메시지 처리기입니다.

void CRcpViewBase::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	AfxGetApp()->WriteProfileInt("POI", "LoadOnlyMainPOI", 1);

	LU->MakePoiAndCusData();

	
	m_bDialogMode = GetOwner()->GetRuntimeClass()->IsDerivedFrom(RUNTIME_CLASS(CDialog));

	if(!IsDialogMode())
		LU->SetRcpView((CRcpView*)this);

	if (XTThemeManager()->GetTheme() == xtThemeOfficeXP ||
		XTThemeManager()->GetTheme() == xtThemeOffice2003)
	{
		((CXTButtonThemeOfficeXP*)CXTButton::GetDefaultTheme())->UseWordTheme(TRUE);
		((CXTButtonThemeOfficeXP*)CXTButton::GetDefaultTheme())->SetBackPushedColor(RGB(200, 255, 200));
		((CXTButtonThemeOfficeXP*)CXTButton::GetDefaultTheme())->SetBackHiliteColor(RGB(200, 200, 255));
	}

	if(!IsDialogMode())
	{
		if (m_wndSubList.GetSafeHwnd() == NULL)
		{
			m_wndSubList.SubclassDlgItem(IDC_COLUMNLIST, LU->m_pwndFieldChooser);
			m_xList.GetColumns()->GetReportHeader()->SetSubListCtrl(&m_wndSubList);
		}
	}
}

void CRcpViewBase::SetFormHeightMax()
{
	if(m_nSavedFormHegiht == 0 && m_wndTabControl.GetSafeHwnd())
	{
		m_nSavedFormHegiht = m_nFormHeight;

		CRect rcForm;
		m_wndTabControl.GetWindowRect(rcForm);
		ScreenToClient(rcForm);
		m_nFormHeight = m_nSavedFormHegiht + rcForm.top - 5;

		ShowAllControl(FALSE, &m_wndTabControl);
		MoveClient();
	}
}

void CRcpViewBase::SetFormHeightRestore()
{
	if(m_nSavedFormHegiht > 0)
	{
		m_nFormHeight = m_nSavedFormHegiht;
		ShowAllControl(TRUE);
		MoveClient();
		m_nSavedFormHegiht = 0;
	}
}

void CRcpViewBase::ShowAllControl(BOOL bShow, CWnd *pwndExcept)
{
	if(!bShow)
	{
		CWnd *pWnd = GetWindow(GW_CHILD);

		while(pWnd)
		{
			if(pWnd != pwndExcept && pWnd->IsWindowVisible() && pWnd->GetSafeHwnd())
			{
				m_arrSavedHideWnd.Add(pWnd->GetSafeHwnd());
				pWnd->ShowWindow(bShow);
			}

			pWnd = pWnd->GetNextWindow();
		}
	}
	else
	{
		CWnd *pWnd = 0;

		for(int i = 0; i < m_arrSavedHideWnd.GetCount(); i++)
		{
			CWnd *pWnd = CWnd::FromHandle((HWND)m_arrSavedHideWnd.GetAt(i));

			if(pWnd->GetSafeHwnd())
				pWnd->ShowWindow(bShow);
		}
		m_arrSavedHideWnd.RemoveAll();
	}
}


void CRcpViewBase::InitForm()
{
	if(IsDialogMode())
	{
		m_wndTabControl.Create(WS_CHILD, CRect(0, 0, 0, 0), this, 100);
		return;
	} 

	m_wndTabControl.Create(WS_CHILD|WS_VISIBLE, CRect(0, 0, 0, 0), this, 100);
	m_wndTabControl.GetPaintManager()->SetAppearance(xtpTabAppearancePropertyPage2003);
	m_wndTabControl.GetPaintManager()->m_bHotTracking = TRUE;
	m_wndTabControl.GetPaintManager()->m_bShowIcons = TRUE;
	m_wndTabControl.GetPaintManager()->DisableLunaColors(TRUE);
	m_wndTabControl.GetPaintManager()->SetPosition(xtpTabPositionTop);

	LU->GetRcpDlgAdmin()->m_pCTIForm = (CRcpPageCTIForm*)LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CRcpPageCTIForm), _T("콜리스트"), 0, CRcpPageCTIForm::IDD);
	LU->GetRcpDlgAdmin()->m_pInfoForm = (CRcpPageInfoForm*)LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CRcpPageInfoForm), _T("정보"), 0, CRcpPageInfoForm::IDD);
	LU->GetRcpDlgAdmin()->m_pMemoForm = (CRcpPageMemoForm*)LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CRcpPageMemoForm), _T("메모장"), 0, CRcpPageMemoForm::IDD);
	LU->GetRcpDlgAdmin()->m_pWCountForm = (CRcpPageWCountForm*)LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CRcpPageWCountForm), _T("접수자통계"), 0, CRcpPageWCountForm::IDD);
	
	///* 20221223
	if(AfxGetApp()->GetProfileInt("RcpMapSetup", "nNotCreateMapForm", 0) == 0)
		AddMapForm();
	//*/

	if(LF->GetCurBranchInfo()->bIPPBXType && LF->POWER_CHECK(1950, "녹취확인 탭", FALSE))
		m_pRecordFileForm = (CRcpPageRecordFileForm*)LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CRcpPageRecordFileForm), _T("녹취확인"));

	if(LF->GetCurBranchInfo()->bIPPBXType && LF->POWER_CHECK(1955, "미연결콜 탭", FALSE))
		m_pMissingCallForm = (CRcpPageMissingCallForm*)LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CRcpPageMissingCallForm), _T("미연결콜"));

	CRect rcView;
	GetClientRect(rcView);
	rcView.top = rcView.bottom - m_nFormHeight;
	m_wndTabControl.MoveWindow(rcView);
	MoveClient();
}

BOOL CRcpViewBase::RcpCreate(CRcpDlg* pDlg, UINT nServiceType)
{
	if (nServiceType == IDD_RCP_DLG)
		return pDlg->Create(IDD_RCP_DLG, this);
	else
		return ((CRcpInsungDlg*)pDlg)->Create(IDD_RCP_INSUNG_DLG, this);
}

void CRcpViewBase::AddMapForm(BOOL bActive)
{
	if(!LU->GetRcpDlgAdmin()->m_pMapForm)
		LU->GetRcpDlgAdmin()->m_pMapForm = (CRcpPageMapForm*)LU->AddView(this, &m_wndTabControl,
					RUNTIME_CLASS(CRcpPageMapForm), _T("지도"), 0, 
					CRcpPageMapForm::IDD, 1, bActive);
}

void CRcpViewBase::MoveClient()
{
	if(!m_xList.GetSafeHwnd())
		return;

	if(IsDialogMode())
	{
		CRect rcList, rcView, rcDst, rcSrc;

		GetWindowRect(&rcView);
		m_xList.GetWindowRect(&rcList);
		rcView.left = rcView.left + 2;
		rcView.top = rcList.top;
		rcView.right = rcView.right - 4;
		rcView.bottom = rcView.bottom - 2;
		ScreenToClient(&rcView);
		m_xList.MoveWindow(&rcView);
	}
	else
	{
		CRect rcForm, rcList, rcTab, rcSrc, rcDst, rcRcp, rcSht;

		GetWindowRect(&rcSht);
		m_xList.GetWindowRect(&rcList);

		rcList.right = rcSht.right - 4;
		rcList.bottom = rcSht.bottom - m_nFormHeight - 2;
		ScreenToClient(&rcList);
		m_xList.MoveWindow(&rcList);

		GetWindowRect(rcForm);
		ScreenToClient(rcForm);
		rcForm.top = rcForm.bottom - m_nFormHeight;
		m_wndTabControl.MoveWindow(rcForm);

		if(m_nSavedFormHegiht == 0)
			AfxGetApp()->WriteProfileInt("RcpPage", "FormHeight", m_nFormHeight);
	}
}


void CRcpViewBase::OnSize(UINT nType, int cx, int cy)
{
	//CMyFormView::OnSize(nType, cx, cy);
	SetScaleToFitSize(CSize(cx, cy));
	MoveClient();
}

int CRcpViewBase::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMyFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	RefreshStateColor();
	return 0;
}


void CRcpViewBase::LoadReportState()
{

	if(!LF->IsThisCompany("올바로"))
		m_xList.GetColumns()->GetAt(RCP_ALL_BARO_COL)->SetVisible(FALSE);

#ifdef XML_STATE
	CXTPPropExchangeXMLNode px(TRUE, 0, _T("ReportControl"));
	if (!px.LoadFromFile(_T("c:\\ReportControl.xml")))
		return;

	m_xList.DoPropExchange(&px);

#else	
	UINT nBytes = 0;
	LPBYTE pData = 0;

	if (!AfxGetApp()->GetProfileBinary(_T("ReportControl"), _T("State"), &pData, &nBytes))
		return;

	CMemFile memFile(pData, nBytes);
	CArchive ar (&memFile,CArchive::load);

	try
	{
		m_xList.SerializeState(ar);

	}
	catch (COleException* pEx)
	{
		pEx->Delete ();
	}
	catch (CArchiveException* pEx)
	{
		pEx->Delete ();
	}

	ar.Close();
	memFile.Close();
	delete[] pData;

	if(!LF->IsThisCompany("올바로"))
		m_xList.GetColumns()->GetAt(RCP_ALL_BARO_COL)->SetVisible(FALSE);
#endif
}


void CRcpViewBase::SaveReportState(CString &strSave, long &nSize)
{
#ifdef XML_STATE

	CXTPPropExchangeXMLNode px(FALSE, 0, _T("ReportControl"));
	m_xLIst.DoPropExchange(&px);
	px.SaveToFile(_T("c:\\ReportControl.xml"));

#else
	CMemFile memFile;
	CArchive ar (&memFile,CArchive::store);

	m_xList.SerializeState(ar);

	ar.Flush();

	DWORD nBytes = (DWORD)memFile.GetPosition();
	LPBYTE pData = memFile.Detach();

	AfxGetApp()->WriteProfileBinary(_T("ReportControl"), _T("State"), pData, nBytes);

	char szData[10000];
	for(int i = 0; i < (int)nBytes; i++) 
		sprintf(&szData[i * 2], "%02X", (BYTE)pData[i]);

	CString strTemp(szData);

	strSave = strTemp;
	nSize = nBytes;

	ar.Close();
	memFile.Close();
	free(pData);
#endif

}

void CRcpViewBase::LoadListFont(BOOL bRedraw)
{
	CString strFontName = AfxGetApp()->GetProfileString("RcpPage", "FontName", "맑은 고딕");
	CString strFontSize = AfxGetApp()->GetProfileString("RcpPage", "FontHeight", "15");
	LOGFONT lf;
	memset(&lf, 0x00, sizeof(LOGFONT));
	strcpy(lf.lfFaceName, (LPSTR)(LPCTSTR)strFontName);
	lf.lfHeight = atol(strFontSize);
	lf.lfWeight = AfxGetApp()->GetProfileInt("RcpPage", "FontBold", 1) ? FW_BOLD : FW_NORMAL;
	m_xList.GetPaintManager()->SetTextFont(lf);

	CString strColHeight = AfxGetApp()->GetProfileString("RcpPage", "ColHeight", "15");
	long bApplyHeight = AfxGetApp()->GetProfileInt("RcpPage", "ApplyHeight", 0);

	((CMyReportPaintManager*)m_xList.GetPaintManager())->SetRowHeight(bApplyHeight, atoi(strColHeight));

	if(bRedraw)
		m_xList.Populate();
}

void CRcpViewBase::RefreshStateColor()
{
	CVirtualRecord::m_crStateText1 = AfxGetApp()->GetProfileInt("RcpPage", "TextColor1", STATE_COLOR_TX1);
	CVirtualRecord::m_crStateText2 = AfxGetApp()->GetProfileInt("RcpPage", "TextColor2", STATE_COLOR_TX2);
	CVirtualRecord::m_crStateText3 = AfxGetApp()->GetProfileInt("RcpPage", "TextColor3", STATE_COLOR_TX3);
	CVirtualRecord::m_crStateText4 = AfxGetApp()->GetProfileInt("RcpPage", "TextColor4", STATE_COLOR_TX4);
	CVirtualRecord::m_crStateText5 = AfxGetApp()->GetProfileInt("RcpPage", "TextColor5", STATE_COLOR_TX5);
	CVirtualRecord::m_crStateText6 = AfxGetApp()->GetProfileInt("RcpPage", "TextColor6", STATE_COLOR_TX6);
	CVirtualRecord::m_crStateText7 = AfxGetApp()->GetProfileInt("RcpPage", "TextColor7", STATE_COLOR_TX7);
	CVirtualRecord::m_crStateText8 = AfxGetApp()->GetProfileInt("RcpPage", "TextColor8", STATE_COLOR_TX8);
	CVirtualRecord::m_crStateText9 = AfxGetApp()->GetProfileInt("RcpPage", "TextColor9", STATE_COLOR_TX9);
	CVirtualRecord::m_crStateText10 = AfxGetApp()->GetProfileInt("RcpPage", "TextColor10", STATE_COLOR_TX10);
	CVirtualRecord::m_crStateTextA = AfxGetApp()->GetProfileInt("RcpPage", "TextColorA", STATE_COLOR_TXA);

	CVirtualRecord::m_crStateBack1 = AfxGetApp()->GetProfileInt("RcpPage", "BackColor1", STATE_COLOR_BK1);
	CVirtualRecord::m_crStateBack2 = AfxGetApp()->GetProfileInt("RcpPage", "BackColor2", STATE_COLOR_BK2);
	CVirtualRecord::m_crStateBack3 = AfxGetApp()->GetProfileInt("RcpPage", "BackColor3", STATE_COLOR_BK3);
	CVirtualRecord::m_crStateBack4 = AfxGetApp()->GetProfileInt("RcpPage", "BackColor4", STATE_COLOR_BK4);
	CVirtualRecord::m_crStateBack5 = AfxGetApp()->GetProfileInt("RcpPage", "BackColor5", STATE_COLOR_BK5);
	CVirtualRecord::m_crStateBack6 = AfxGetApp()->GetProfileInt("RcpPage", "BackColor6", STATE_COLOR_BK6);
	CVirtualRecord::m_crStateBack7 = AfxGetApp()->GetProfileInt("RcpPage", "BackColor7", STATE_COLOR_BK7);
	CVirtualRecord::m_crStateBack8 = AfxGetApp()->GetProfileInt("RcpPage", "BackColor8", STATE_COLOR_BK8);
	CVirtualRecord::m_crStateBack9 = AfxGetApp()->GetProfileInt("RcpPage", "BackColor9", STATE_COLOR_BK9);
	CVirtualRecord::m_crStateBack10 = AfxGetApp()->GetProfileInt("RcpPage", "BackColor10", STATE_COLOR_BK10);

	CVirtualRecord::m_crStateBack12 = AfxGetApp()->GetProfileInt("RcpPage", "BackColor12", STATE_COLOR_BK12);

	CVirtualRecord::m_crStateBack15 = AfxGetApp()->GetProfileInt("RcpPage", "BackColor15", STATE_COLOR_BK12);
	CVirtualRecord::m_bUsePickupNot = AfxGetApp()->GetProfileInt("RcpPage", "UsePickupNot", 0);
	
	m_xList.SetSelectedColor(CVirtualRecord::m_crStateBack12);
}




#define ID_REMOVE_ITEM  1
#define ID_SORT_ASC     2
#define ID_SORT_DESC        3
#define ID_GROUP_BYTHIS 4
#define ID_SHOW_GROUPBOX        5
#define ID_SHOW_FIELDCHOOSER 6
#define ID_COLUMN_BESTFIT       7
#define ID_COLUMN_ARRANGEBY 100
#define ID_COLUMN_ALIGMENT  200
#define ID_COLUMN_ALIGMENT_LEFT ID_COLUMN_ALIGMENT + 1
#define ID_COLUMN_ALIGMENT_RIGHT    ID_COLUMN_ALIGMENT + 2
#define ID_COLUMN_ALIGMENT_CENTER   ID_COLUMN_ALIGMENT + 3
#define ID_COLUMN_SHOW      500

void CRcpViewBase::OnReportColumnRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CMkLock lock(&m_csOrder);

	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	ASSERT(pItemNotify->pColumn);
	CPoint ptClick = pItemNotify->pt;

	CMenu menu;
	VERIFY(menu.CreatePopupMenu());

	// create main menu items
	menu.AppendMenu(MF_STRING, ID_SORT_ASC, "순방향 정렬");
	menu.AppendMenu(MF_STRING, ID_SORT_DESC, "역방향 정렬");
	menu.AppendMenu(MF_SEPARATOR, (UINT)-1, (LPCTSTR)NULL);
	menu.AppendMenu(MF_SEPARATOR, (UINT)-1, (LPCTSTR)NULL);
	menu.AppendMenu(MF_STRING, ID_REMOVE_ITEM, "해당 컬럼 표시하지 않음");
	menu.AppendMenu(MF_STRING, ID_SHOW_FIELDCHOOSER, "컬럼 선택창");
	menu.AppendMenu(MF_SEPARATOR, (UINT)-1, (LPCTSTR)NULL);
	menu.AppendMenu(MF_STRING, ID_COLUMN_BESTFIT, "자동 컬럼 크기 조정");

	CXTPGridColumns* pColumns = m_xList.GetColumns();
	CXTPGridColumn* pColumn = pItemNotify->pColumn;

	// create arrange by items
	CMenu menuArrange;
	VERIFY(menuArrange.CreatePopupMenu());
	int nColumnCount = pColumns->GetCount();
	int nColumn = 0;
	for (nColumn = 0; nColumn < nColumnCount; nColumn++)
	{
		CXTPGridColumn* pCol = pColumns->GetAt(nColumn);
		if (pCol && pCol->IsVisible())
		{
			CString sCaption = pCol->GetCaption();
			if (!sCaption.IsEmpty())
				menuArrange.AppendMenu(MF_STRING, ID_COLUMN_ARRANGEBY + nColumn, sCaption);
		}
	}

	menuArrange.AppendMenu(MF_SEPARATOR, 60, (LPCTSTR)NULL);
	menu.InsertMenu(0, MF_BYPOSITION | MF_POPUP, (UINT_PTR) menuArrange.m_hMenu, "정렬 기준");

	// create columns items
	CMenu menuColumns;
	VERIFY(menuColumns.CreatePopupMenu());
	for (nColumn = 0; nColumn < nColumnCount; nColumn++)
	{
		CXTPGridColumn* pCol = pColumns->GetAt(nColumn);
		CString sCaption = pCol->GetCaption();
		//if (!sCaption.IsEmpty())
		menuColumns.AppendMenu(MF_STRING, ID_COLUMN_SHOW + nColumn, sCaption);
		menuColumns.CheckMenuItem(ID_COLUMN_SHOW + nColumn,
			MF_BYCOMMAND | (pCol->IsVisible() ? MF_CHECKED : MF_UNCHECKED) );
	}

	menu.InsertMenu(0, MF_BYPOSITION | MF_POPUP, (UINT_PTR) menuColumns.m_hMenu, "컬럼");


	// track menu
#ifndef _XTP_INCLUDE_COMMANDBARS
	int nMenuResult = menu.TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN |TPM_RIGHTBUTTON, ptClick.x, ptClick.y, this, NULL);
#else
	int nMenuResult = CXTPCommandBars::TrackPopupMenu(&menu, TPM_NONOTIFY | TPM_RETURNCMD | TPM_LEFTALIGN |TPM_RIGHTBUTTON, ptClick.x, ptClick.y, this, NULL);
#endif

	// arrange by items
	if (nMenuResult >= ID_COLUMN_ARRANGEBY && nMenuResult < ID_COLUMN_ALIGMENT)
	{
		for (int nColumn = 0; nColumn < nColumnCount; nColumn++)
		{
			CXTPGridColumn* pCol = pColumns->GetAt(nColumn);
			if (pCol && pCol->IsVisible())
			{
				if (nMenuResult == ID_COLUMN_ARRANGEBY + nColumn)
				{
					nMenuResult = ID_SORT_ASC;
					pColumn = pCol;
					break;
				}
			}
		}
	}

	// process column selection item
	if (nMenuResult >= ID_COLUMN_SHOW)
	{
		CXTPGridColumn* pCol = pColumns->GetAt(nMenuResult - ID_COLUMN_SHOW);
		if (pCol)
		{
			pCol->SetVisible(!pCol->IsVisible());
		}
	}

	// other general items
	switch (nMenuResult)
	{
	case ID_REMOVE_ITEM:
		pColumn->SetVisible(FALSE);
		m_xList.Populate();
		break;
	case ID_SORT_ASC:
	case ID_SORT_DESC:
		if (pColumn && pColumn->IsSortable())
		{
			pColumns->SetSortColumn(pColumn, nMenuResult == ID_SORT_ASC);
			m_xList.Populate();
		}
		break;

	case ID_SHOW_FIELDCHOOSER:
		OnShowFieldChooser();
		break;
	case ID_COLUMN_BESTFIT:
		m_xList.GetColumns()->GetReportHeader()->BestFit(pColumn);
		break;
	}
}

void CRcpViewBase::OnShowFieldChooser()
{
	CMkLock lock(&m_csOrder);

	BOOL bShow = !LU->GetFieldChooser()->IsVisible();
	((CFrameWnd*)AfxGetMainWnd())->ShowControlBar(LU->GetFieldChooser(), bShow, FALSE);
}

