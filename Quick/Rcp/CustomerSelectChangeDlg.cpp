// CustomerSelectChangeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CustomerSelectChangeDlg.h"


// CCustomerSelectChangeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCustomerSelectChangeDlg, CMyDialog)

CCustomerSelectChangeDlg::CCustomerSelectChangeDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCustomerSelectChangeDlg::IDD, pParent)
{
	m_bCNo = TRUE;
	m_bCompany = TRUE;
	m_bDepart = TRUE;
	m_bManager = TRUE;
	m_bTel = TRUE;
	m_bMobile = TRUE;
	m_bRiderMemo = TRUE;
	m_bMemo = TRUE;
	m_bGrade = TRUE;
	m_bAllocGroup = TRUE;
	m_bDetailAddress = TRUE;
	m_bLocation = TRUE;
	m_bDisplay = TRUE;
	m_bCredit = TRUE;
	m_bSendStateChangeSms = TRUE;
	m_bICMapDisplayType = TRUE;
	m_bUseHomepage = TRUE;
	m_bPreventPosUpdate = TRUE;
	m_bPriceGrade = TRUE;
	m_bDiscount = TRUE;
	m_bCoupon = TRUE;
	m_bMileage = TRUE;
	m_bEMail = TRUE;
}

CCustomerSelectChangeDlg::~CCustomerSelectChangeDlg()
{
}

void CCustomerSelectChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CNO_CHECK, m_bCNo);
	DDX_Check(pDX, IDC_COMPANY_CHECK, m_bCompany);
	DDX_Check(pDX, IDC_DEPART_CHECK, m_bDepart);
	DDX_Check(pDX, IDC_MANAGER_CHECK, m_bManager);
	DDX_Check(pDX, IDC_TEL_CHECK, m_bTel);
	DDX_Check(pDX, IDC_MOBILE_CHECK, m_bMobile);
	DDX_Check(pDX, IDC_RIDER_MEMO_CHECK, m_bRiderMemo);
	DDX_Check(pDX, IDC_MEMO_CHECK, m_bMemo);
	DDX_Check(pDX, IDC_GRADE_CHECK, m_bGrade);
	DDX_Check(pDX, IDC_ALLOC_GROUP_CHECK, m_bAllocGroup);
	DDX_Check(pDX, IDC_DETAIL_ADDRESS_CHECK, m_bDetailAddress);
	DDX_Check(pDX, IDC_LOCATION_CHECK, m_bLocation);
	DDX_Check(pDX, IDC_DISPLAY_CHECK, m_bDisplay);
	DDX_Check(pDX, IDC_CREDIT_CHECK, m_bCredit);
	DDX_Check(pDX, IDC_SEND_STATE_CHANGE_SMS_CHECK, m_bSendStateChangeSms);
	DDX_Check(pDX, IDC_IC_MAP_DISPLAY_TYPE_CHK, m_bICMapDisplayType);
	DDX_Check(pDX, IDC_USE_HOMEPAGE_CHECK, m_bUseHomepage);
	DDX_Check(pDX, IDC_PREVENT_POS_UPDATE_CHECK, m_bPreventPosUpdate);
	DDX_Check(pDX, IDC_PRICE_GRADE_CHECK, m_bPriceGrade);
	DDX_Check(pDX, IDC_DISCOUNT_CHECK, m_bDiscount);
	DDX_Check(pDX, IDC_COUPON_CHECK, m_bCoupon);
	DDX_Check(pDX, IDC_MILEAGE_CHECK, m_bMileage);
	DDX_Check(pDX, IDC_EMAIL_CHECK, m_bEMail);
}


BEGIN_MESSAGE_MAP(CCustomerSelectChangeDlg, CMyDialog)
	ON_BN_CLICKED(IDC_ALL_SELECT_BTN2, &CCustomerSelectChangeDlg::OnBnClickedAllSelectBtn2)
	ON_BN_CLICKED(IDC_ALL_SELECT_BTN, &CCustomerSelectChangeDlg::OnBnClickedAllSelectBtn)
	ON_BN_CLICKED(IDC_NOT_SELECT_BTN, &CCustomerSelectChangeDlg::OnBnClickedNotSelectBtn)
	ON_BN_CLICKED(IDC_NOT_SELECT_BTN2, &CCustomerSelectChangeDlg::OnBnClickedNotSelectBtn2)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CCustomerSelectChangeDlg::OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_OK_BTN, &CCustomerSelectChangeDlg::OnBnClickedOkBtn)
END_MESSAGE_MAP()


// CCustomerSelectChangeDlg 메시지 처리기입니다.

void CCustomerSelectChangeDlg::OnBnClickedAllSelectBtn2()
{
	m_bCredit = TRUE;
	m_bSendStateChangeSms = TRUE;
	m_bICMapDisplayType = TRUE;
	m_bUseHomepage = TRUE;
	m_bPreventPosUpdate = TRUE;
	m_bPriceGrade = TRUE;
	m_bDiscount = TRUE;
	m_bCoupon = TRUE;
	m_bMileage = TRUE;
	m_bEMail = TRUE;

	UpdateData(FALSE);
}

void CCustomerSelectChangeDlg::OnBnClickedAllSelectBtn()
{
	m_bCNo = TRUE;
	m_bCompany = TRUE;
	m_bDepart = TRUE;
	m_bManager = TRUE;
	m_bTel = TRUE;
	m_bMobile = TRUE;
	m_bRiderMemo = TRUE;
	m_bMemo = TRUE;
	m_bGrade = TRUE;
	m_bAllocGroup = TRUE;
	m_bDetailAddress = TRUE;
	m_bLocation = TRUE;
	m_bDisplay = TRUE;

	UpdateData(FALSE);
}

BOOL CCustomerSelectChangeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCustomerSelectChangeDlg::OnBnClickedNotSelectBtn()
{
	m_bCNo = FALSE;
	m_bCompany = FALSE;
	m_bDepart = FALSE;
	m_bManager = FALSE;
	m_bTel = FALSE;
	m_bMobile = FALSE;
	m_bRiderMemo = FALSE;
	m_bMemo = FALSE;
	m_bGrade = FALSE;
	m_bAllocGroup = FALSE;
	m_bDetailAddress = FALSE;
	m_bLocation = FALSE;
	m_bDisplay = FALSE;

	UpdateData(FALSE);
}

void CCustomerSelectChangeDlg::OnBnClickedNotSelectBtn2()
{
	m_bCredit = FALSE;
	m_bSendStateChangeSms = FALSE;
	m_bICMapDisplayType = FALSE;
	m_bUseHomepage = FALSE;
	m_bPreventPosUpdate = FALSE;
	m_bPriceGrade = FALSE;
	m_bDiscount = FALSE;
	m_bCoupon = FALSE;
	m_bMileage = FALSE;
	m_bEMail = FALSE;

	UpdateData(FALSE);
}

void CCustomerSelectChangeDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CCustomerSelectChangeDlg::OnBnClickedOkBtn()
{
	OnOK();
}
