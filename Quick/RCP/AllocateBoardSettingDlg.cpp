// AllocateBoardSettingDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AllocateBoardSettingDlg.h"



// CAllocateBoardSettingDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAllocateBoardSettingDlg, CMyDialog)
CAllocateBoardSettingDlg::CAllocateBoardSettingDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAllocateBoardSettingDlg::IDD, pParent)
{
	m_bNeedRefresh = FALSE;
}

CAllocateBoardSettingDlg::~CAllocateBoardSettingDlg()
{
}

void CAllocateBoardSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AL_EDIT, m_edtAL);
	DDX_Control(pDX, IDC_PL_EDIT, m_edtPL);
	DDX_Control(pDX, IDC_AG_EDIT, m_edtAG);
	DDX_Control(pDX, IDC_PG_EDIT, m_edtPG);

	DDX_Control(pDX, IDC_AL_EDIT2, m_edtAL2);
	DDX_Control(pDX, IDC_PL_EDIT2, m_edtPL2);
	DDX_Control(pDX, IDC_AG_EDIT2, m_edtAG2);
	DDX_Control(pDX, IDC_PG_EDIT2, m_edtPG2);

	DDX_Control(pDX, IDC_DELAY_COLOR_STATIC, m_stcDelayColor);
	DDX_Control(pDX, IDC_OTHER_ORDER_COLOR_STATIC, m_stcOtherOrderColor);
	DDX_Control(pDX, IDC_FINISH_TEST_CHECK, m_chkFinishTest);
	DDX_Control(pDX, IDC_LINEAR_TYPE_CHECK, m_chkLinearType);

	DDX_Control(pDX, IDC_DELAY_BACK_COLOR_BTN, m_cpDelayBackColor);
	DDX_Control(pDX, IDC_OTHER_ORDER_TEXT_COLOR_BTN, m_cpOtherOrderTextColor);
	DDX_Control(pDX, IDC_OTHER_ORDER_BACK_COLOR_BTN, m_cpOtherOrderBackColor);

	DDX_Control(pDX, IDC_OTHER_RIDER_COLOR_STATIC, m_stcOtherRiderColor);
	DDX_Control(pDX, IDC_OTHER_RIDER_TEXT_COLOR_BTN, m_cpOtherRiderTextColor);
	DDX_Control(pDX, IDC_OTHER_RIDER_BACK_COLOR_BTN, m_cpOtherRiderBackColor);

	DDX_Control(pDX, IDC_OTHER_RIDER_HAVE_MY_ORDER_CHK, m_chkOtherOrderHaveMyOrder);
	DDX_Control(pDX, IDC_OTHER_RIDER_HAVE_MY_ORDER_SPLIT_SORT_CHK, m_chkOtherOrderHaveMyOrderSplitSort);
}


BEGIN_MESSAGE_MAP(CAllocateBoardSettingDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_CPN_XT_SELENDOK(IDC_DELAY_BACK_COLOR_BTN, OnSelEndColor)
	ON_CPN_XT_SELENDOK(IDC_OTHER_ORDER_TEXT_COLOR_BTN, OnSelEndColor)
	ON_CPN_XT_SELENDOK(IDC_OTHER_ORDER_BACK_COLOR_BTN, OnSelEndColor)
	ON_CPN_XT_SELENDOK(IDC_OTHER_RIDER_TEXT_COLOR_BTN, OnSelEndColor)
	ON_CPN_XT_SELENDOK(IDC_OTHER_RIDER_BACK_COLOR_BTN, OnSelEndColor)
	ON_BN_CLICKED(IDC_OTHER_RIDER_HAVE_MY_ORDER_CHK, OnBnClickedOtherRiderHaveMyOrderChk)
	ON_BN_CLICKED(IDC_OTHER_RIDER_HAVE_MY_ORDER_SPLIT_SORT_CHK, OnBnClickedOtherRiderHaveMyOrderSplitSortChk)
END_MESSAGE_MAP()


// CAllocateBoardSettingDlg 메시지 처리기입니다.

BOOL CAllocateBoardSettingDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_edtAL.SetWindowText(AfxGetApp()->GetProfileString("AllocateBoardDlg", "AL", ""));
	m_edtPL.SetWindowText(AfxGetApp()->GetProfileString("AllocateBoardDlg", "PL", ""));
	m_edtAG.SetWindowText(AfxGetApp()->GetProfileString("AllocateBoardDlg", "AG", ""));
	m_edtPG.SetWindowText(AfxGetApp()->GetProfileString("AllocateBoardDlg", "PG", ""));

	m_edtAL2.SetWindowText(AfxGetApp()->GetProfileString("AllocateBoardDlg", "AL2", ""));
	m_edtPL2.SetWindowText(AfxGetApp()->GetProfileString("AllocateBoardDlg", "PL2", ""));
	m_edtAG2.SetWindowText(AfxGetApp()->GetProfileString("AllocateBoardDlg", "AG2", ""));
	m_edtPG2.SetWindowText(AfxGetApp()->GetProfileString("AllocateBoardDlg", "PG2", ""));


	m_chkFinishTest.SetCheck(AfxGetApp()->GetProfileInt("AllocateBoardDlg", "FinishTest", 0));
	m_chkLinearType.SetCheck(AfxGetApp()->GetProfileInt("AllocateBoardDlg", "LinearType", 0));
	m_chkOtherOrderHaveMyOrder.SetCheck(AfxGetApp()->GetProfileInt("AllocateBoardDlg", "HaveMyOrder", m_ci.HasShareCompany()));
	m_chkOtherOrderHaveMyOrderSplitSort.SetCheck(AfxGetApp()->GetProfileInt("AllocateBoardDlg", "HaveMyOrderSplitSort", m_ci.HasShareCompany()));

	if(!m_chkOtherOrderHaveMyOrder.GetCheck())
		m_chkOtherOrderHaveMyOrderSplitSort.EnableWindow(FALSE);


	COLORREF crText, crBack;
	crBack = AfxGetApp()->GetProfileInt("AllocateBoardDlg", "DelayBackColor", RGB(255, 200, 200));
	m_cpDelayBackColor.SetColor(crBack);	
	m_stcDelayColor.SetBkColor(crBack);
	m_stcDelayColor.SetWindowText("");

	crText = AfxGetApp()->GetProfileInt("AllocateBoardDlg", "OtherOrderTextColor", RGB(0, 0, 0));
	crBack = AfxGetApp()->GetProfileInt("AllocateBoardDlg", "OtherOrderBackColor", RGB(255, 255, 255));
	m_cpOtherOrderTextColor.SetColor(crText);
	m_cpOtherOrderBackColor.SetColor(crBack);
	m_stcOtherOrderColor.SetTextColor(crText);
	m_stcOtherOrderColor.SetBkColor(crBack);
	m_stcOtherOrderColor.SetWindowText("서울 -> 부산");

	crText = AfxGetApp()->GetProfileInt("AllocateBoardDlg", "OtherRiderTextColor", RGB(255, 255, 255));
	crBack = AfxGetApp()->GetProfileInt("AllocateBoardDlg", "OtherRiderBackColor", RGB(102, 102, 153));
	m_cpOtherRiderTextColor.SetColor(crText);
	m_cpOtherRiderBackColor.SetColor(crBack);
	m_stcOtherRiderColor.SetTextColor(crText);
	m_stcOtherRiderColor.SetBkColor(crBack);
	m_stcOtherRiderColor.SetWindowText("로지)100/매니저");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAllocateBoardSettingDlg::OnBnClickedOk()
{
	CString strAL, strPL, strAG, strPG;
	CString strAL2, strPL2, strAG2, strPG2;

	m_edtAL.GetWindowText(strAL);
	m_edtPL.GetWindowText(strPL);
	m_edtAG.GetWindowText(strAG);
	m_edtPG.GetWindowText(strPG);

	m_edtAL2.GetWindowText(strAL2);
	m_edtPL2.GetWindowText(strPL2);
	m_edtAG2.GetWindowText(strAG2);
	m_edtPG2.GetWindowText(strPG2);

	AfxGetApp()->WriteProfileString("AllocateBoardDlg", "AL", strAL);
	AfxGetApp()->WriteProfileString("AllocateBoardDlg", "PL", strPL);
	AfxGetApp()->WriteProfileString("AllocateBoardDlg", "AG", strAG);
	AfxGetApp()->WriteProfileString("AllocateBoardDlg", "PG", strPG);

	AfxGetApp()->WriteProfileString("AllocateBoardDlg", "AL2", strAL2);
	AfxGetApp()->WriteProfileString("AllocateBoardDlg", "PL2", strPL2);
	AfxGetApp()->WriteProfileString("AllocateBoardDlg", "AG2", strAG2);
	AfxGetApp()->WriteProfileString("AllocateBoardDlg", "PG2", strPG2);

	AfxGetApp()->WriteProfileInt("AllocateBoardDlg", "FinishTest", m_chkFinishTest.GetCheck());
	AfxGetApp()->WriteProfileInt("AllocateBoardDlg", "LinearType", m_chkLinearType.GetCheck());
	AfxGetApp()->WriteProfileInt("AllocateBoardDlg", "HaveMyOrder", m_chkOtherOrderHaveMyOrder.GetCheck());
	AfxGetApp()->WriteProfileInt("AllocateBoardDlg", "HaveMyOrderSplitSort", m_chkOtherOrderHaveMyOrderSplitSort.GetCheck());

	AfxGetApp()->WriteProfileInt("AllocateBoardDlg", "DelayBackColor", m_cpDelayBackColor.GetColor());
	AfxGetApp()->WriteProfileInt("AllocateBoardDlg", "OtherOrderTextColor", m_cpOtherOrderTextColor.GetColor());
	AfxGetApp()->WriteProfileInt("AllocateBoardDlg", "OtherOrderBackColor", m_cpOtherOrderBackColor.GetColor());
	
	AfxGetApp()->WriteProfileInt("AllocateBoardDlg", "OtherRiderTextColor", m_cpOtherRiderTextColor.GetColor());
	AfxGetApp()->WriteProfileInt("AllocateBoardDlg", "OtherRiderBackColor", m_cpOtherRiderBackColor.GetColor());

	OnOK();
}

void CAllocateBoardSettingDlg::OnSelEndColor()
{
	m_stcDelayColor.SetBkColor(m_cpDelayBackColor.GetColor());
	m_stcOtherOrderColor.SetTextColor(m_cpOtherOrderTextColor.GetColor());
	m_stcOtherOrderColor.SetBkColor(m_cpOtherOrderBackColor.GetColor());
	m_stcOtherRiderColor.SetTextColor(m_cpOtherRiderTextColor.GetColor());
	m_stcOtherRiderColor.SetBkColor(m_cpOtherRiderBackColor.GetColor());
}

void CAllocateBoardSettingDlg::OnBnClickedOtherRiderHaveMyOrderChk()
{
	m_chkOtherOrderHaveMyOrderSplitSort.EnableWindow(m_chkOtherOrderHaveMyOrder.GetCheck());
	m_bNeedRefresh = TRUE;
}

void CAllocateBoardSettingDlg::OnBnClickedOtherRiderHaveMyOrderSplitSortChk()
{
	m_bNeedRefresh = TRUE;
}
