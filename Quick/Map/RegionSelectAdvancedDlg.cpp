// RegionSelectAdvancedDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RegionSelectAdvancedDlg.h"
#include "LogiMapBase.h"
#include "POIDataNew.h"
#include "MakePOIData.h"
#include "SearchRegionSimpleDlg.h"

// CRegionSelectAdvancedDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRegionSelectAdvancedDlg, CMyDialog)

CRegionSelectAdvancedDlg::CRegionSelectAdvancedDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRegionSelectAdvancedDlg::IDD, pParent)
{
	m_pMap = NULL;
	m_pSearchRegionDlg = NULL;
}

CRegionSelectAdvancedDlg::~CRegionSelectAdvancedDlg()
{
	if(m_pSearchRegionDlg)
	{
		delete m_pSearchRegionDlg;
		m_pSearchRegionDlg = NULL;
	}

}

void CRegionSelectAdvancedDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SIDO_COMBO, m_cmbSido);
	DDX_Control(pDX, IDC_GUGUN_COMBO, m_cmbGugun);
	DDX_Control(pDX, IDC_DONG_COMBO, m_cmbDong);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}


BEGIN_MESSAGE_MAP(CRegionSelectAdvancedDlg, CMyDialog)
	ON_CBN_SELCHANGE(IDC_SIDO_COMBO, &CRegionSelectAdvancedDlg::OnCbnSelchangeSidoCombo)
	ON_CBN_SELCHANGE(IDC_GUGUN_COMBO, &CRegionSelectAdvancedDlg::OnCbnSelchangeGugunCombo)
	ON_CBN_SELCHANGE(IDC_DONG_COMBO, &CRegionSelectAdvancedDlg::OnCbnSelchangeDongCombo)
	ON_WM_LBUTTONDOWN()
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CRegionSelectAdvancedDlg::OnEnChangeSearchEdit)
	ON_COMMAND(1000, OnSelectPOI)
END_MESSAGE_MAP()


// CRegionSelectAdvancedDlg 메시지 처리기입니다.

BOOL CRegionSelectAdvancedDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	//m_poiNew.SetLog(&mkLog);

	if(!m_poiNew.IsDataLoadOK())
	{
//		CMakePOIData poi(&m_poiNew, m_pMkDb, m_ci.m_strCity, m_si.bServer3);
		CMakePOIData poi(&m_poiNew, m_pMkDb, m_ci.m_strCity, m_ci.m_bCapitalArea, FALSE, TRUE);
		poi.AutoLoad(TRUE);
	}

	m_pMap->RefreshAdminInfo(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CRegionSelectAdvancedDlg::OnCbnSelchangeSidoCombo()
{
	char buffer[10];
	int nCode = m_cmbSido.GetItemData(m_cmbSido.GetCurSel());
	m_pMap->MoveMapFormCode(ltoa(nCode, buffer, 10), 1);
}

void CRegionSelectAdvancedDlg::OnCbnSelchangeGugunCombo()
{
	char buffer[10];
	int nSidoCode = m_cmbSido.GetItemData(m_cmbSido.GetCurSel());
	int nGugunCode = m_cmbGugun.GetItemData(m_cmbGugun.GetCurSel());
	sprintf(buffer, "%d%d", nSidoCode, nGugunCode);
	m_pMap->MoveMapFormCode(buffer, 2);
}

void CRegionSelectAdvancedDlg::OnCbnSelchangeDongCombo()
{
	char buffer[20];
	int nSidoCode = m_cmbSido.GetItemData(m_cmbSido.GetCurSel());
	int nGugunCode = m_cmbGugun.GetItemData(m_cmbGugun.GetCurSel());
	int nDongCode = m_cmbDong.GetItemData(m_cmbDong.GetCurSel());
	sprintf(buffer, "%d%d%d", nSidoCode, nGugunCode, nDongCode);
	m_pMap->MoveMapFormCode(buffer, 3);
}

void CRegionSelectAdvancedDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CMyDialog::OnLButtonDown(nFlags, point);
}


void CRegionSelectAdvancedDlg::OnEnChangeSearchEdit()
{
	if(!m_pSearchRegionDlg)
	{
		m_pSearchRegionDlg = new CSearchRegionSimpleDlg(this);
		m_pSearchRegionDlg->Create(IDD_SEARCH_REGION_SIMPLE_DLG, this);

		CRect rc, rc2;
		GetWindowRect(rc);
		m_pSearchRegionDlg->GetWindowRect(rc2);
		rc2.OffsetRect(rc.left - rc2.left, rc.bottom - rc2.top);
		m_pSearchRegionDlg->MoveWindow(rc2);
	}
	
	if(!m_pSearchRegionDlg->IsWindowVisible())
		m_pSearchRegionDlg->ShowWindow(SW_SHOWNA);

	CString strSearch;
	m_edtSearch.GetWindowText(strSearch);
	m_pSearchRegionDlg->Search(strSearch);
}

void CRegionSelectAdvancedDlg::OnSelectPOI()
{
	m_pMap->MoveMap(m_pSearchRegionDlg->m_pPOI);
}

BOOL CRegionSelectAdvancedDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->hwnd == m_edtSearch.GetSafeHwnd())
	{
		if(pMsg->message == WM_KEYDOWN)
		{
			if(pMsg->wParam == VK_RETURN || 
				pMsg->wParam == VK_DOWN ||
				pMsg->wParam == VK_UP)
			{
				if(m_pSearchRegionDlg)
				{
					m_pSearchRegionDlg->PostMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
					return FALSE;
				}
			}
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}


void CRegionSelectAdvancedDlg::OnOK()
{
	if(m_pSearchRegionDlg)
		m_pSearchRegionDlg->ShowWindow(SW_HIDE);
	CMyDialog::OnOK();
}

