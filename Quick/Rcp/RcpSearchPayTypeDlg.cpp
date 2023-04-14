// RcpSearchPayTypeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "RcpSearchPayTypeDlg.h"
#include "RcpView.h"

BOOL CRcpSearchPayTypeDlg::m_bPayType0 = TRUE;
BOOL CRcpSearchPayTypeDlg::m_bPayType1 = TRUE;
BOOL CRcpSearchPayTypeDlg::m_bPayType2 = TRUE;
BOOL CRcpSearchPayTypeDlg::m_bPayType3 = TRUE;
BOOL CRcpSearchPayTypeDlg::m_bPayType4 = TRUE;
BOOL CRcpSearchPayTypeDlg::m_bPayType7 = TRUE;
// CRcpSearchPayTypeDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRcpSearchPayTypeDlg, CMyDialog)

CRcpSearchPayTypeDlg::CRcpSearchPayTypeDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRcpSearchPayTypeDlg::IDD, pParent)
{
	m_pRcpView = (CRcpView*)pParent;

	m_bPayType0 = TRUE;
	m_bPayType1 = TRUE;
	m_bPayType2 = TRUE;
	m_bPayType3 = TRUE;
	m_bPayType4 = TRUE;
	m_bPayType7 = TRUE;
}

CRcpSearchPayTypeDlg::~CRcpSearchPayTypeDlg()
{
}

void CRcpSearchPayTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Check(pDX, IDC_SEARCH_PAY_TYPE_0_CHECK, m_bPayType0);
	DDX_Check(pDX, IDC_SEARCH_PAY_TYPE_1_CHECK, m_bPayType1);
	DDX_Check(pDX, IDC_SEARCH_PAY_TYPE_2_CHECK, m_bPayType2);
	DDX_Check(pDX, IDC_SEARCH_PAY_TYPE_3_CHECK, m_bPayType3);
	DDX_Check(pDX, IDC_SEARCH_PAY_TYPE_4_CHECK, m_bPayType4);
	DDX_Check(pDX, IDC_SEARCH_PAY_TYPE_7_CHECK, m_bPayType7);
}

 
BEGIN_MESSAGE_MAP(CRcpSearchPayTypeDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SELECT_ALL_BTN, &CRcpSearchPayTypeDlg::OnBnClickedSelectAllBtn)
	ON_BN_CLICKED(IDC_NOT_SELECT_ALL_BTN, &CRcpSearchPayTypeDlg::OnBnClickedNotSelectAllBtn)
	ON_BN_CLICKED(IDC_CASH_BTN, &CRcpSearchPayTypeDlg::OnBnClickedCashBtn)
	ON_BN_CLICKED(IDC_NONE_CASH_BTN, &CRcpSearchPayTypeDlg::OnBnClickedNoneCashBtn)
	ON_BN_CLICKED(IDCANCEL, &CRcpSearchPayTypeDlg::OnBnClickedCancel)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_SEARCH_PAY_TYPE_0_CHECK, &CRcpSearchPayTypeDlg::OnBnClickedSearchPayType0Check)
	ON_BN_CLICKED(IDC_SEARCH_PAY_TYPE_1_CHECK, &CRcpSearchPayTypeDlg::OnBnClickedSearchPayType1Check)
	ON_BN_CLICKED(IDC_SEARCH_PAY_TYPE_2_CHECK, &CRcpSearchPayTypeDlg::OnBnClickedSearchPayType2Check)
	ON_BN_CLICKED(IDC_SEARCH_PAY_TYPE_3_CHECK, &CRcpSearchPayTypeDlg::OnBnClickedSearchPayType3Check)
	ON_BN_CLICKED(IDC_SEARCH_PAY_TYPE_4_CHECK, &CRcpSearchPayTypeDlg::OnBnClickedSearchPayType4Check)
	ON_BN_CLICKED(IDC_SEARCH_PAY_TYPE_7_CHECK, &CRcpSearchPayTypeDlg::OnBnClickedSearchPayType7Check)

END_MESSAGE_MAP()


// CRcpSearchPayTypeDlg �޽��� ó�����Դϴ�.

void CRcpSearchPayTypeDlg::OnBnClickedSelectAllBtn()
{	
	m_bPayType0 = TRUE;
	m_bPayType1 = TRUE;
	m_bPayType2 = TRUE;
	m_bPayType3 = TRUE;
	m_bPayType4 = TRUE;
	m_bPayType7 = TRUE;

	UpdateData(FALSE);

	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchPayTypeDlg::OnBnClickedNotSelectAllBtn()
{
	m_bPayType0 = FALSE;
	m_bPayType1 = FALSE;
	m_bPayType2 = FALSE; 
	m_bPayType3 = FALSE;
	m_bPayType4 = FALSE;
	m_bPayType7 = FALSE;

	UpdateData(FALSE);

	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchPayTypeDlg::OnBnClickedCashBtn()
{
	m_bPayType0 = TRUE;
	m_bPayType1 = TRUE;
	m_bPayType2 = FALSE; 
	m_bPayType3 = FALSE;
	m_bPayType4 = FALSE;
	m_bPayType7 = FALSE;

	UpdateData(FALSE);

	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchPayTypeDlg::OnBnClickedNoneCashBtn()
{
	m_bPayType0 = FALSE;
	m_bPayType1 = FALSE;
	m_bPayType2 = TRUE; 
	m_bPayType3 = TRUE;
	m_bPayType4 = FALSE;
	m_bPayType7 = TRUE;

	UpdateData(FALSE);

	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchPayTypeDlg::OnBnClickedCancel()
{
	ShowWindow(FALSE);
}

BOOL CRcpSearchPayTypeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CRcpSearchPayTypeDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CMyDialog::OnLButtonDown(nFlags, point);
}

void CRcpSearchPayTypeDlg::OnBnClickedSearchPayType0Check()
{
	UpdateData(TRUE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchPayTypeDlg::OnBnClickedSearchPayType1Check()
{
	UpdateData(TRUE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchPayTypeDlg::OnBnClickedSearchPayType2Check()
{
	UpdateData(TRUE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchPayTypeDlg::OnBnClickedSearchPayType3Check()
{
	UpdateData(TRUE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchPayTypeDlg::OnBnClickedSearchPayType4Check()
{
	UpdateData(TRUE);
	m_pRcpView->ChangeSearchFilter();
}

void CRcpSearchPayTypeDlg::OnBnClickedSearchPayType7Check()
{
	UpdateData(TRUE);
	m_pRcpView->ChangeSearchFilter();
}

BOOL CRcpSearchPayTypeDlg::IsUseSearchFilter()
{
	if(m_bPayType0 == TRUE &&
		m_bPayType1 == TRUE &&
		m_bPayType2 == TRUE &&
		m_bPayType3 == TRUE &&
		m_bPayType4 == TRUE &&
		m_bPayType7 == TRUE)
		return FALSE;
	else
		return TRUE;
}