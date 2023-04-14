// GroupReportSettingDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "GroupReportSettingDlg.h"


// CGroupReportSettingDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGroupReportSettingDlg, CMyDialog)
CGroupReportSettingDlg::CGroupReportSettingDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CGroupReportSettingDlg::IDD, pParent)
	, m_strDiscount(_T(""))
	, m_bCashApply(FALSE)
	, m_nAddTaxApplyType(0)
	, m_nReportFirstDay(0)
	, m_nReportSecondDay(0)
	, m_bShowOrder(FALSE)
{
	m_nGNo = 0;
}

CGroupReportSettingDlg::~CGroupReportSettingDlg()
{
}

void CGroupReportSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DISCOUNT_EDT, m_edtDiscount);
	DDX_Control(pDX, IDC_CASH_APPLY_CHECK, m_chkCashApply);
	DDX_Control(pDX, IDC_CREDIT_APPLY_CHECK, m_chkCreditApply);
	DDX_Control(pDX, IDC_ONLINE_APPLY_CHECK, m_chkOnlineApply);
	DDX_Control(pDX, IDC_TRANS_APPLY_CHECK, m_chkTransApply);
	DDX_Control(pDX, IDC_REPORT_FIRST_DAY_COMBO, m_cmbReportFirstDay);
	DDX_Control(pDX, IDC_REPORT_SECOND_DAY_COMBO, m_cmbReportSecondDay);

	DDX_Text(pDX, IDC_DISCOUNT_EDT, m_strDiscount);
	DDX_Control(pDX, IDC_ADD_TAX_APPLY_TYPE_COMBO, m_cmbAddTaxApplyType);
	DDX_Check(pDX, IDC_CASH_APPLY_CHECK, m_bCashApply);
	DDX_Check(pDX, IDC_CREDIT_APPLY_CHECK, m_bCreditApply);
	DDX_Check(pDX, IDC_ONLINE_APPLY_CHECK, m_bOnlineApply);
	DDX_Check(pDX, IDC_TRANS_APPLY_CHECK, m_bTransApply);
	DDX_CBIndex(pDX, IDC_ADD_TAX_APPLY_TYPE_COMBO, m_nAddTaxApplyType);
	DDX_CBIndex(pDX, IDC_REPORT_FIRST_DAY_COMBO, m_nReportFirstDay);
	DDX_CBIndex(pDX, IDC_REPORT_SECOND_DAY_COMBO, m_nReportSecondDay);

	for(int i=0; i<COLUMN_COUNT; i++)
		DDX_Check(pDX, IDC_COLUMN_CHECK0 + i, m_bSelect[i]);
	DDX_Check(pDX, IDC_INCLUDE_ORDER_CHECK, m_bShowOrder);
	DDX_Control(pDX, IDC_INCLUDE_ORDER_CHECK, m_chkShowOrder);
	DDX_Control(pDX, IDC_NOT_INCLUDE_ORDER_CHECK, m_chkNotShowOrder);
	DDX_Control(pDX, IDC_NOT_SHOW_CASH_CHECK, m_chkNotShowCash);
	DDX_Check(pDX, IDC_NOT_SHOW_CASH_CHECK, m_bNotShowCash);
}


BEGIN_MESSAGE_MAP(CGroupReportSettingDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SAVE_BTN, OnBnClickedSaveBtn)
	ON_CBN_SELCHANGE(IDC_REPORT_FIRST_DAY_COMBO, OnCbnSelchangeReportFirstDayCombo)
	ON_CBN_SELCHANGE(IDC_REPORT_SECOND_DAY_COMBO, OnCbnSelchangeReportSecondDayCombo)
	ON_BN_CLICKED(IDC_INCLUDE_ORDER_CHECK, OnBnClickedIncludeOrderCheck)
	ON_BN_CLICKED(IDC_NOT_INCLUDE_ORDER_CHECK, OnBnClickedNotIncludeOrderCheck)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
END_MESSAGE_MAP()



BOOL CGroupReportSettingDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();

	CString strTitle = "";
	strTitle = m_cg.GetGroupData(m_nGNo)->strGroupName + "/" + m_cg.GetGroupData(m_nGNo)->strDept + "[" + m_cg.GetGroupData(m_nGNo)->strName + "]";

	this->SetWindowText(strTitle);

	char buffer[20];

	m_edtDiscount.SetWindowText(itoa(m_cg.GetGroupData(m_nGNo)->nDiscount, buffer, 10));
	m_cmbAddTaxApplyType.SetCurSel(m_cg.GetGroupData(m_nGNo)->nAddTaxApplyType);
	m_cmbReportFirstDay.SetCurSel(m_cg.GetGroupData(m_nGNo)->nReportFirstDay);
	m_cmbReportSecondDay.SetCurSel(m_cg.GetGroupData(m_nGNo)->nReportSecondDay);
	m_chkCashApply.SetCheck(m_cg.GetGroupData(m_nGNo)->bCashApply);
	m_chkCreditApply.SetCheck(m_cg.GetGroupData(m_nGNo)->bCreditApply);
	m_chkOnlineApply.SetCheck(m_cg.GetGroupData(m_nGNo)->bOnlineApply);
	m_chkTransApply.SetCheck(m_cg.GetGroupData(m_nGNo)->bTransApply);
	m_chkShowOrder.SetCheck(m_cg.GetGroupData(m_nGNo)->bShowOrder);
	m_chkNotShowOrder.SetCheck(m_cg.GetGroupData(m_nGNo)->bNotShowCash);

	for(int i=0; i<COLUMN_COUNT; i++)
	{
		BOOL bCheck = _ttoi(m_cg.GetGroupData(m_nGNo)->strColumnChk.GetAt(i));
		((CButton*)GetDlgItem(IDC_COLUMN_CHECK0 + i))->SetCheck(bCheck);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CGroupReportSettingDlg::OnBnClickedSaveBtn()
{
	UpdateData(TRUE);
	char buffer[20];

	for(int i=0; i<COLUMN_COUNT; i++)
		m_strColumn.Add(itoa(m_bSelect[i], buffer, 10));

	OnOK();
}


void CGroupReportSettingDlg::CheckCombo()
{
	long nFirstSel = m_cmbReportFirstDay.GetCurSel();
	long nSecondSel = m_cmbReportSecondDay.GetCurSel();

	if((nSecondSel < nFirstSel) &&
		nSecondSel != 0)
	{
		MessageBox("첫번째 정산일의 날짜가 두번째 정산일 날짜보다 큽니다", "확인", MB_ICONINFORMATION);
		m_cmbReportSecondDay.SetCurSel(0);
		return;
	}

	if((nSecondSel == nFirstSel) &&
		nFirstSel != 0)
	{
		MessageBox("첫번째 정산일과 두번째 정산일의 날짜가 같습니다", "확인", MB_ICONINFORMATION);
		m_cmbReportSecondDay.SetCurSel(0);
		return;
	}

	if(nFirstSel == 0 && nSecondSel > 0) 
	{
		MessageBox("첫번째 정산일로 설정해주세요", "확인", MB_ICONINFORMATION);
		m_cmbReportFirstDay.SetCurSel(m_cmbReportSecondDay.GetCurSel());
		m_cmbReportSecondDay.SetCurSel(0);
		return;
	}
}


void CGroupReportSettingDlg::OnCbnSelchangeReportFirstDayCombo()
{
	CheckCombo();
}

void CGroupReportSettingDlg::OnCbnSelchangeReportSecondDayCombo()
{
	CheckCombo();
}

void CGroupReportSettingDlg::OnBnClickedIncludeOrderCheck()
{
	if(m_chkShowOrder.GetCheck())
		m_chkNotShowOrder.SetCheck(FALSE);
	else
		m_chkNotShowOrder.SetCheck(TRUE);

	InitCheckBox(TRUE);
}

void CGroupReportSettingDlg::OnBnClickedNotIncludeOrderCheck()
{
	if(m_chkNotShowOrder.GetCheck())
		m_chkShowOrder.SetCheck(FALSE);
	else
		m_chkShowOrder.SetCheck(TRUE);

	InitCheckBox(FALSE);
}

void CGroupReportSettingDlg::InitCheckBox(BOOL bEnable)
{
	for(int i=0; i<COLUMN_COUNT; i++)
	{
		CButton *pButton = (CButton*)GetDlgItem(IDC_COLUMN_CHECK0 + i);
		pButton->EnableWindow(bEnable);
	}

}
void CGroupReportSettingDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}
