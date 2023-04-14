// RcpSearchTruckTypeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RcpSearchTruckTypeDlg.h"
#include "RcpView.h"

// CRcpSearchTruckTypeDlg 대화 상자입니다.

BOOL CRcpSearchTruckTypeDlg::m_bTruckType0 = TRUE;
BOOL CRcpSearchTruckTypeDlg::m_bTruckType1 = TRUE;
BOOL CRcpSearchTruckTypeDlg::m_bTruckType2 = TRUE;
BOOL CRcpSearchTruckTypeDlg::m_bTonType0 = TRUE;
BOOL CRcpSearchTruckTypeDlg::m_bTonType1 = TRUE;
BOOL CRcpSearchTruckTypeDlg::m_bTonType2 = TRUE;
BOOL CRcpSearchTruckTypeDlg::m_bTonType3 = TRUE; 
BOOL CRcpSearchTruckTypeDlg::m_bTonType4 = TRUE;
BOOL CRcpSearchTruckTypeDlg::m_bTonType5 = TRUE;
BOOL CRcpSearchTruckTypeDlg::m_bTonType6 = TRUE;


IMPLEMENT_DYNAMIC(CRcpSearchTruckTypeDlg, CMyDialog)

CRcpSearchTruckTypeDlg::CRcpSearchTruckTypeDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRcpSearchTruckTypeDlg::IDD, pParent)
{
	m_pRcpView = (CRcpView*)pParent;

	m_bTruckType0 = TRUE;
	m_bTruckType1 = TRUE;
	m_bTruckType2 = TRUE;
	m_bTonType0 = TRUE;
	m_bTonType1 = TRUE;
	m_bTonType2 = TRUE;
	m_bTonType3 = TRUE;
	m_bTonType4 = TRUE;
	m_bTonType5 = TRUE;
	m_bTonType6 = TRUE;
}

CRcpSearchTruckTypeDlg::~CRcpSearchTruckTypeDlg()
{
}

void CRcpSearchTruckTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	
	DDX_Check(pDX, IDC_SEARCH_TRUCK_TYPE_0_CHECK, m_bTruckType0);
	DDX_Check(pDX, IDC_SEARCH_TRUCK_TYPE_1_CHECK, m_bTruckType1);
	DDX_Check(pDX, IDC_SEARCH_TRUCK_TYPE_2_CHECK, m_bTruckType2);
	DDX_Check(pDX, IDC_SEARCH_TRUCK_TYPE_TON_10_CHECK, m_bTonType0);
	DDX_Check(pDX, IDC_SEARCH_TRUCK_TYPE_TON_14_CHECK, m_bTonType1);
	DDX_Check(pDX, IDC_SEARCH_TRUCK_TYPE_TON_25_CHECK, m_bTonType2);
	DDX_Check(pDX, IDC_SEARCH_TRUCK_TYPE_TON_35_CHECK, m_bTonType3);
	DDX_Check(pDX, IDC_SEARCH_TRUCK_TYPE_TON_45_CHECK, m_bTonType4);
	DDX_Check(pDX, IDC_SEARCH_TRUCK_TYPE_TON_50_CHECK, m_bTonType5);
	DDX_Check(pDX, IDC_SEARCH_TRUCK_TYPE_TON_110_CHECK, m_bTonType6);
}


BEGIN_MESSAGE_MAP(CRcpSearchTruckTypeDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SEARCH_TRUCK_TYPE_0_CHECK, &CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckType0Check)
	ON_BN_CLICKED(IDC_SEARCH_TRUCK_TYPE_1_CHECK, &CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckType1Check)
	ON_BN_CLICKED(IDC_SEARCH_TRUCK_TYPE_2_CHECK, &CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckType2Check)
	ON_BN_CLICKED(IDC_SEARCH_TRUCK_TYPE_TON_10_CHECK, &CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckTypeTon10Check)
	ON_BN_CLICKED(IDC_SEARCH_TRUCK_TYPE_TON_14_CHECK, &CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckTypeTon14Check)
	ON_BN_CLICKED(IDC_SEARCH_TRUCK_TYPE_TON_25_CHECK, &CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckTypeTon25Check)
	ON_BN_CLICKED(IDC_SEARCH_TRUCK_TYPE_TON_35_CHECK, &CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckTypeTon35Check)
	ON_BN_CLICKED(IDC_SEARCH_TRUCK_TYPE_TON_45_CHECK, &CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckTypeTon45Check)
	ON_BN_CLICKED(IDC_SEARCH_TRUCK_TYPE_TON_50_CHECK, &CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckTypeTon50Check)
	ON_BN_CLICKED(IDC_SEARCH_TRUCK_TYPE_TON_110_CHECK, &CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckTypeTon110Check)
	ON_BN_CLICKED(IDCANCEL, &CRcpSearchTruckTypeDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SELECT_3TON_UP_BTN, &CRcpSearchTruckTypeDlg::OnBnClickedSelect3tonUpBtn)
	ON_BN_CLICKED(IDC_SELECT_CAR_ALL_BTN, &CRcpSearchTruckTypeDlg::OnBnClickedSelectCarAllBtn)
	ON_WM_NCLBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_SELECT_TON_ALL_BTN, &CRcpSearchTruckTypeDlg::OnBnClickedSelectTonAllBtn)
	ON_BN_CLICKED(IDC_SELECT_3TON_DOWN_BTN, &CRcpSearchTruckTypeDlg::OnBnClickedSelect3tonDownBtn)
END_MESSAGE_MAP()


// CRcpSearchTruckTypeDlg 메시지 처리기입니다.

void CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckType0Check()
{
	UpdateData(TRUE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckType1Check()
{
	UpdateData(TRUE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckType2Check()
{
	UpdateData(TRUE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckTypeTon10Check()
{
	UpdateData(TRUE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckTypeTon14Check()
{
	UpdateData(TRUE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckTypeTon25Check()
{
	UpdateData(TRUE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckTypeTon35Check()
{
	UpdateData(TRUE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckTypeTon45Check()
{
	UpdateData(TRUE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckTypeTon50Check()
{
	UpdateData(TRUE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchTruckTypeDlg::OnBnClickedSearchTruckTypeTon110Check()
{
	UpdateData(TRUE);
	m_pRcpView->ChangeSearchFilter();
}

BOOL CRcpSearchTruckTypeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRcpSearchTruckTypeDlg::OnBnClickedCancel()
{
	ShowWindow(FALSE);
}

void CRcpSearchTruckTypeDlg::OnBnClickedSelect3tonUpBtn()
{
	m_bTonType0 = FALSE;
	m_bTonType1 = FALSE;
	m_bTonType2 = FALSE;
	m_bTonType3 = TRUE;
	m_bTonType4 = TRUE;
	m_bTonType5 = TRUE;
	m_bTonType6 = TRUE;

	UpdateData(FALSE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchTruckTypeDlg::OnBnClickedSelectCarAllBtn()
{
	if(m_bTruckType0 && m_bTruckType1 && m_bTruckType2)
	{
		m_bTruckType0 = FALSE;
		m_bTruckType1 = FALSE;
		m_bTruckType2 = FALSE;
	}
	else
	{
		m_bTruckType0 = TRUE;
		m_bTruckType1 = TRUE;
		m_bTruckType2 = TRUE;
	}

	UpdateData(FALSE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchTruckTypeDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CMyDialog::OnLButtonDown(nFlags, point);
}

BOOL CRcpSearchTruckTypeDlg::IsUseTruckSearchFilter()
{
	if(m_bTruckType0 == TRUE &&
		m_bTruckType1 == TRUE &&
		m_bTruckType2 == TRUE)
		return FALSE;
	else
		return TRUE;
}

BOOL CRcpSearchTruckTypeDlg::IsUseTonSearchFilter()
{
	if(	m_bTonType0 == TRUE &&
		m_bTonType1 == TRUE &&
		m_bTonType2 == TRUE &&
		m_bTonType3 == TRUE &&
		m_bTonType4 == TRUE &&
		m_bTonType5 == TRUE &&
		m_bTonType6 == TRUE)
		return FALSE;
	else
		return TRUE;
}

void CRcpSearchTruckTypeDlg::OnBnClickedSelectTonAllBtn()
{
	if(m_bTonType0 && m_bTonType1 && m_bTonType2 && m_bTonType3 && m_bTonType4 && m_bTonType5 && m_bTonType6)
	{
		m_bTonType0 = FALSE;
		m_bTonType1 = FALSE;
		m_bTonType2 = FALSE;
		m_bTonType3 = FALSE;
		m_bTonType4 = FALSE;
		m_bTonType5 = FALSE;
		m_bTonType6 = FALSE;
	}
	else
	{
		m_bTonType0 = TRUE;
		m_bTonType1 = TRUE;
		m_bTonType2 = TRUE;
		m_bTonType3 = TRUE;
		m_bTonType4 = TRUE;
		m_bTonType5 = TRUE;
		m_bTonType6 = TRUE;
	}

	UpdateData(FALSE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchTruckTypeDlg::OnBnClickedSelect3tonDownBtn()
{
	m_bTonType0 = TRUE;
	m_bTonType1 = TRUE;
	m_bTonType2 = TRUE;
	m_bTonType3 = FALSE;
	m_bTonType4 = FALSE;
	m_bTonType5 = FALSE;
	m_bTonType6 = FALSE;

	UpdateData(FALSE);
	m_pRcpView->ChangeSearchFilter();
}
