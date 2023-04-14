// RcpSearchCarTypeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "quick.h"
#include "RcpSearchCarTypeDlg.h"
#include "RcpView.h"

BOOL CRcpSearchCarTypeDlg::m_bCarType0 = TRUE;
BOOL CRcpSearchCarTypeDlg::m_bCarType1 = TRUE;
BOOL CRcpSearchCarTypeDlg::m_bCarType2 = TRUE;
BOOL CRcpSearchCarTypeDlg::m_bCarType3 = TRUE;
BOOL CRcpSearchCarTypeDlg::m_bCarType4 = TRUE;
BOOL CRcpSearchCarTypeDlg::m_bCarType5 = TRUE;
BOOL CRcpSearchCarTypeDlg::m_bCarType6 = TRUE;
BOOL CRcpSearchCarTypeDlg::m_bCarType7 = TRUE;
BOOL CRcpSearchCarTypeDlg::m_bCarType8 = TRUE;
BOOL CRcpSearchCarTypeDlg::m_bCarType9 = TRUE;
BOOL CRcpSearchCarTypeDlg::m_bCarType10 = TRUE;
BOOL CRcpSearchCarTypeDlg::m_bCarType11 = TRUE;
BOOL CRcpSearchCarTypeDlg::m_bCarType12 = TRUE;
BOOL CRcpSearchCarTypeDlg::m_bCarType13 = TRUE;
BOOL CRcpSearchCarTypeDlg::m_bCarType14 = TRUE;
BOOL CRcpSearchCarTypeDlg::m_bCarType15 = TRUE;


// CRcpSearchCarTypeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRcpSearchCarTypeDlg, CMyDialog)

CRcpSearchCarTypeDlg::CRcpSearchCarTypeDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRcpSearchCarTypeDlg::IDD, pParent)
{
	m_pRcpView = (CRcpView*)pParent;

	m_bCarType0 = TRUE;
	m_bCarType1 = TRUE;
	m_bCarType2 = TRUE;
	m_bCarType3 = TRUE;
	m_bCarType4 = TRUE;
	m_bCarType5 = TRUE;
	m_bCarType6 = TRUE;
	m_bCarType7 = TRUE;
	m_bCarType8 = TRUE;
	m_bCarType9 = TRUE;
	m_bCarType10 = TRUE;
	m_bCarType11 = TRUE;
	m_bCarType12 = TRUE;
	m_bCarType13 = TRUE;
	m_bCarType14 = TRUE;
	m_bCarType15 = TRUE;
}

CRcpSearchCarTypeDlg::~CRcpSearchCarTypeDlg()
{
}

void CRcpSearchCarTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Check(pDX, IDC_SEARCH_CAR_TYPE_0_CHECK, m_bCarType0);
	DDX_Check(pDX, IDC_SEARCH_CAR_TYPE_1_CHECK, m_bCarType1);
	DDX_Check(pDX, IDC_SEARCH_CAR_TYPE_2_CHECK, m_bCarType2);
	DDX_Check(pDX, IDC_SEARCH_CAR_TYPE_3_CHECK, m_bCarType3);
	DDX_Check(pDX, IDC_SEARCH_CAR_TYPE_4_CHECK, m_bCarType4);
	DDX_Check(pDX, IDC_SEARCH_CAR_TYPE_5_CHECK, m_bCarType5);
	DDX_Check(pDX, IDC_SEARCH_CAR_TYPE_6_CHECK, m_bCarType6);
	DDX_Check(pDX, IDC_SEARCH_CAR_TYPE_7_CHECK, m_bCarType7);
	DDX_Check(pDX, IDC_SEARCH_CAR_TYPE_8_CHECK, m_bCarType8);
	DDX_Check(pDX, IDC_SEARCH_CAR_TYPE_9_CHECK, m_bCarType9);
	DDX_Check(pDX, IDC_SEARCH_CAR_TYPE_10_CHECK, m_bCarType10);
	DDX_Check(pDX, IDC_SEARCH_CAR_TYPE_11_CHECK, m_bCarType11);
	DDX_Check(pDX, IDC_SEARCH_CAR_TYPE_12_CHECK, m_bCarType12);
	DDX_Check(pDX, IDC_SEARCH_CAR_TYPE_13_CHECK, m_bCarType13);
	DDX_Check(pDX, IDC_SEARCH_CAR_TYPE_14_CHECK, m_bCarType14);
	DDX_Check(pDX, IDC_SEARCH_CAR_TYPE_15_CHECK, m_bCarType15);
}


BEGIN_MESSAGE_MAP(CRcpSearchCarTypeDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SELECT_ALL_BTN, &CRcpSearchCarTypeDlg::OnBnClickedSelectAllBtn)
	ON_BN_CLICKED(IDC_NOT_SELECT_ALL_BTN, &CRcpSearchCarTypeDlg::OnBnClickedNotSelectAllBtn)

	ON_BN_CLICKED(IDCANCEL, &CRcpSearchCarTypeDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SELECT_TWO_BTN, &CRcpSearchCarTypeDlg::OnBnClickedSelectTwoBtn)
	ON_BN_CLICKED(IDC_SELECT_FOUR_BTN, &CRcpSearchCarTypeDlg::OnBnClickedSelectFourBtn)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_SEARCH_CAR_TYPE_0_CHECK, &CRcpSearchCarTypeDlg::OnBnClickedSearchCarTypeCheck)
	ON_BN_CLICKED(IDC_SEARCH_CAR_TYPE_1_CHECK, &CRcpSearchCarTypeDlg::OnBnClickedSearchCarTypeCheck)
	ON_BN_CLICKED(IDC_SEARCH_CAR_TYPE_2_CHECK, &CRcpSearchCarTypeDlg::OnBnClickedSearchCarTypeCheck)
	ON_BN_CLICKED(IDC_SEARCH_CAR_TYPE_3_CHECK, &CRcpSearchCarTypeDlg::OnBnClickedSearchCarTypeCheck)
	ON_BN_CLICKED(IDC_SEARCH_CAR_TYPE_4_CHECK, &CRcpSearchCarTypeDlg::OnBnClickedSearchCarTypeCheck)
	ON_BN_CLICKED(IDC_SEARCH_CAR_TYPE_5_CHECK, &CRcpSearchCarTypeDlg::OnBnClickedSearchCarTypeCheck)
	ON_BN_CLICKED(IDC_SEARCH_CAR_TYPE_6_CHECK, &CRcpSearchCarTypeDlg::OnBnClickedSearchCarTypeCheck)
	ON_BN_CLICKED(IDC_SEARCH_CAR_TYPE_7_CHECK, &CRcpSearchCarTypeDlg::OnBnClickedSearchCarTypeCheck)
	ON_BN_CLICKED(IDC_SEARCH_CAR_TYPE_8_CHECK, &CRcpSearchCarTypeDlg::OnBnClickedSearchCarTypeCheck)
	ON_BN_CLICKED(IDC_SEARCH_CAR_TYPE_9_CHECK, &CRcpSearchCarTypeDlg::OnBnClickedSearchCarTypeCheck)
	ON_BN_CLICKED(IDC_SEARCH_CAR_TYPE_10_CHECK, &CRcpSearchCarTypeDlg::OnBnClickedSearchCarTypeCheck)
	ON_BN_CLICKED(IDC_SEARCH_CAR_TYPE_11_CHECK, &CRcpSearchCarTypeDlg::OnBnClickedSearchCarTypeCheck)
	ON_BN_CLICKED(IDC_SEARCH_CAR_TYPE_12_CHECK, &CRcpSearchCarTypeDlg::OnBnClickedSearchCarTypeCheck)
	ON_BN_CLICKED(IDC_SEARCH_CAR_TYPE_13_CHECK, &CRcpSearchCarTypeDlg::OnBnClickedSearchCarTypeCheck)
	ON_BN_CLICKED(IDC_SEARCH_CAR_TYPE_14_CHECK, &CRcpSearchCarTypeDlg::OnBnClickedSearchCarTypeCheck)
	ON_BN_CLICKED(IDC_SEARCH_CAR_TYPE_15_CHECK, &CRcpSearchCarTypeDlg::OnBnClickedSearchCarTypeCheck)

	ON_BN_CLICKED(IDC_SELECT_NOT_QUICK_BTN, &CRcpSearchCarTypeDlg::OnBnClickedSelectNotQuickBtn)
END_MESSAGE_MAP()


void CRcpSearchCarTypeDlg::OnBnClickedSelectAllBtn()
{
	m_bCarType0 = TRUE;
	m_bCarType1 = TRUE;
	m_bCarType2 = TRUE;
	m_bCarType3 = TRUE;
	m_bCarType4 = TRUE;
	m_bCarType5 = TRUE;
	m_bCarType6 = TRUE;
	m_bCarType7 = TRUE;
	m_bCarType8 = TRUE;
	m_bCarType9 = TRUE;
	m_bCarType10 = TRUE;
	m_bCarType11 = TRUE;
	m_bCarType12 = TRUE;
	m_bCarType13 = TRUE;
	m_bCarType14 = TRUE;
	m_bCarType15 = TRUE;

	UpdateData(FALSE);
	m_pRcpView->RefreshFilterOnly();
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchCarTypeDlg::OnBnClickedNotSelectAllBtn()
{
	m_bCarType0 = FALSE;
	m_bCarType1 = FALSE;
	m_bCarType2 = FALSE;
	m_bCarType3 = FALSE;
	m_bCarType4 = FALSE;
	m_bCarType5 = FALSE;
	m_bCarType6 = FALSE;
	m_bCarType7 = FALSE;
	m_bCarType8 = FALSE;
	m_bCarType9 = FALSE;
	m_bCarType10 = FALSE;
	m_bCarType11 = FALSE;
	m_bCarType12 = FALSE;
	m_bCarType13 = FALSE;
	m_bCarType14 = FALSE;
	m_bCarType15 = FALSE;

	UpdateData(FALSE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchCarTypeDlg::OnBnClickedCancel()
{
	ShowWindow(SW_HIDE);
}

void CRcpSearchCarTypeDlg::OnBnClickedSelectTwoBtn()
{
	m_bCarType0 = TRUE;
	m_bCarType1 = TRUE;
	m_bCarType2 = FALSE;
	m_bCarType3 = FALSE;
	m_bCarType4 = FALSE;
	m_bCarType5 = FALSE;
	m_bCarType6 = FALSE;
	m_bCarType7 = FALSE;
	m_bCarType8 = FALSE;
	m_bCarType9 = FALSE;
	m_bCarType10 = FALSE;
	m_bCarType11 = FALSE;
	m_bCarType12 = FALSE;
	m_bCarType13 = FALSE;
	m_bCarType14 = FALSE;
	m_bCarType15 = FALSE;

	UpdateData(FALSE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchCarTypeDlg::OnBnClickedSelectFourBtn()
{
	m_bCarType0 = FALSE;
	m_bCarType1 = FALSE;
	m_bCarType2 = TRUE;
	m_bCarType3 = TRUE;
	m_bCarType4 = TRUE;
	m_bCarType5 = TRUE;
	m_bCarType6 = FALSE;
	m_bCarType7 = FALSE;
	m_bCarType8 = TRUE;
	m_bCarType9 = TRUE;
	m_bCarType10 = TRUE;
	m_bCarType11 = TRUE;
	m_bCarType12 = TRUE;
	m_bCarType13 = TRUE;
	m_bCarType14 = TRUE;
	m_bCarType15 = TRUE;

	UpdateData(FALSE);
	m_pRcpView->ChangeSearchFilter();
}

BOOL CRcpSearchCarTypeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRcpSearchCarTypeDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CMyDialog::OnLButtonDown(nFlags, point);
}

void CRcpSearchCarTypeDlg::OnBnClickedSearchCarTypeCheck()
{  
	UpdateData(TRUE);
	m_pRcpView->ChangeSearchFilter();
}
BOOL CRcpSearchCarTypeDlg::IsUseSearchFilter()
{
	if(m_bCarType0 == TRUE &&
		m_bCarType1 == TRUE &&
		m_bCarType2 == TRUE &&
		m_bCarType3 == TRUE &&
		m_bCarType4 == TRUE &&
		m_bCarType5 == TRUE &&
		m_bCarType6 == TRUE &&
		m_bCarType7 == TRUE &&
		m_bCarType8 == TRUE &&
		m_bCarType9 == TRUE &&
		m_bCarType10 == TRUE &&
		m_bCarType11 == TRUE &&
		m_bCarType12 == TRUE &&
		m_bCarType13 == TRUE &&
		m_bCarType14 == TRUE &&
		m_bCarType15 == TRUE
	)
		return FALSE; 
	else
		return TRUE;
}
void CRcpSearchCarTypeDlg::OnBnClickedSelectNotQuickBtn()
{
	m_bCarType0 = FALSE;
	m_bCarType1 = FALSE;
	m_bCarType2 = FALSE;
	m_bCarType3 = FALSE;
	m_bCarType4 = FALSE;
	m_bCarType5 = FALSE;
	m_bCarType6 = TRUE;
	m_bCarType7 = TRUE;
	m_bCarType8 = FALSE;
	m_bCarType9 = FALSE;

	UpdateData(FALSE);
	m_pRcpView->ChangeSearchFilter();
}
