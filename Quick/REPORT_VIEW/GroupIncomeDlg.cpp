// GroupIncomeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "GroupIncomeDlg.h"



// CGroupIncomeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGroupIncomeDlg, CMyDialog)
CGroupIncomeDlg::CGroupIncomeDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CGroupIncomeDlg::IDD, pParent)
{
	m_sRet = "";
	m_dtReIncome = COleDateTime::GetCurrentTime();
	m_nAllIncome = 0;
	m_strInputEtc = "";
	m_nUnCollection = 0;
}

CGroupIncomeDlg::~CGroupIncomeDlg()
{
}

void CGroupIncomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TYPE_COMBO, m_cmbType);
	DDX_Control(pDX, IDC_MONEY_EDIT, m_EdtMoney);
	DDX_Control(pDX, IDC_TITLE_STATIC, m_stcTitle);
	DDX_Control(pDX, IDC_DATE, m_DateCtl);
	DDX_Control(pDX, IDC_ETC, m_edtEtc);
	DDX_Control(pDX, IDC_DATE_REINCOME, m_dtpReIncome);
	DDX_DateTimeCtrl(pDX, IDC_DATE_REINCOME, m_dtReIncome);
	DDX_Control(pDX, IDC_REINCOM_CHECK, m_chkReIncome);
	DDX_Control(pDX, IDC_BALANCE_STATIC, m_stcBalance); 
}


BEGIN_MESSAGE_MAP(CGroupIncomeDlg, CMyDialog)
	ON_EN_CHANGE(IDC_MONEY_EDIT, OnEnChangeMoneyEdit)
	ON_BN_CLICKED(IDC_INCOME_BTN, OnBnClickedIncomeBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_CBN_SELCHANGE(IDC_TYPE_COMBO, &CGroupIncomeDlg::OnCbnSelchangeTypeCombo)
	ON_BN_CLICKED(IDC_REINCOM_CHECK, &CGroupIncomeDlg::OnBnClickedReincomCheck)
END_MESSAGE_MAP()


// CGroupIncomeDlg 메시지 처리기입니다.

BOOL CGroupIncomeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_stcTitle.SetWindowText(m_sDate + " " + "미수금액 : "+ ::GetMyNumberFormat(m_nDebit));

	m_cmbType.SetCurSel(0);
	m_dtReIncome += 7;

	m_edtEtc.SetWindowText(m_strInputEtc);

	m_dtpReIncome.EnableWindow(FALSE);
	if(m_nAllIncome == 2)
	{
		AllIncome();
	}
	else
	{
		m_cmbType.SetCurSel(m_nAllIncome);

		OnCbnSelchangeTypeCombo();		
	}

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CGroupIncomeDlg::OnEnChangeMoneyEdit()
{
	CString sCharge; m_EdtMoney.GetWindowText(sCharge);
	sCharge.Replace(",", "");

	if(!IsNumeric(sCharge))
	{
		MessageBox("숫자를 입력하세요");
		m_EdtMoney.SetWindowText("");
		return;
	}

	long nInputCharge = 0;
	

	nInputCharge = atol(sCharge);

	if(m_cmbType.GetCurSel() == 0)
	{
		if(nInputCharge > m_nDebit && m_nDebit > 0)
		{
			MessageBox("미수금액보다 많은 금액을 입력할 수 없습니다", "확인", MB_ICONINFORMATION);
			m_cmbType.SetCurSel(0);
			m_EdtMoney.SetWindowText(sCharge.Left(sCharge.GetLength() - 1));
			return;
		}	
		
		if(atol(sCharge) >= m_nDebit )
		{
			m_cmbType.SetCurSel(2);
			m_chkReIncome.SetCheck(FALSE);
			m_dtpReIncome.EnableWindow(FALSE);
			m_EdtMoney.SetWindowText(GetMyNumberFormat(m_nDebit));
		}

		m_stcBalance.ShowWindow(SW_HIDE);
		m_stcBalance.SetWindowText(GetMyNumberFormat(m_nDebit - nInputCharge));
		m_stcBalance.ShowWindow(SW_SHOW);
	}
	else if(m_cmbType.GetCurSel() == 1)
	{
						  
		if(nInputCharge > m_nUnCollection)
		{
			MessageBox("정산금보다 많은 금액을 입력할 수 없습니다", "확인", MB_ICONINFORMATION);			
			m_EdtMoney.SetWindowText(sCharge.Left(sCharge.GetLength() - 1));
			return;
		}	


		m_stcBalance.ShowWindow(SW_HIDE);
		m_stcBalance.SetWindowText(GetMyNumberFormat(m_nDebit + nInputCharge));
		m_stcBalance.ShowWindow(SW_SHOW);

	}	
	
}

void CGroupIncomeDlg::OnBnClickedIncomeBtn()
{
	CString sCharge; m_EdtMoney.GetWindowText(sCharge);
	sCharge.Replace(",", "");

	if(atoi(sCharge) <= 0)
	{
		MessageBox("0원 이상으로 입력해 주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CString sType; m_cmbType.GetLBText(m_cmbType.GetCurSel(), sType);
	CString sEtc; m_edtEtc.GetWindowText(sEtc);
	COleDateTime dtTime; m_DateCtl.GetTime(dtTime);	



	CMkCommand pCmd(m_pMkDb, "update_group_unbill_4"); 
	pCmd.AddParameter(m_nID);
	pCmd.AddParameter(atoi(sCharge));
	pCmd.AddParameter(sType);
	pCmd.AddParameter(m_cmbType.GetCurSel());
	pCmd.AddParameter(dtTime);
	pCmd.AddParameter(sEtc);	
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_chkReIncome.GetCheck() ? m_dtReIncome : NULL);
	pCmd.AddParameter(m_ui.strName);
	CMkParameter *pPar = pCmd.AddParameter(typeString, typeOutput, 100, "");

	if(pCmd.Execute())
	{
		pPar->GetValue(m_sRet);
		MessageBox("입금되었습니다", "확인", MB_ICONINFORMATION);
		OnOK();
	}
}

void CGroupIncomeDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CGroupIncomeDlg::AllIncome()
{

	m_cmbType.SetCurSel(2);
	m_chkReIncome.SetCheck(FALSE);
	m_chkReIncome.EnableWindow(FALSE);
	m_dtpReIncome.EnableWindow(FALSE);
	m_stcBalance.SetWindowText("0");
	m_EdtMoney.SetWindowText(GetMyNumberFormat(m_nDebit));

}

void CGroupIncomeDlg::OnCbnSelchangeTypeCombo()
{
	if( m_cmbType.GetCurSel() == 0 ||  m_cmbType.GetCurSel() == 1)
	{
		m_chkReIncome.SetCheck(FALSE);
		m_chkReIncome.EnableWindow(TRUE);
		m_dtpReIncome.EnableWindow(FALSE);
		m_EdtMoney.SetWindowText("");
	}
	else if(m_cmbType.GetCurSel() == 2)
	{
		m_chkReIncome.SetCheck(FALSE);
		m_chkReIncome.EnableWindow(FALSE);
		m_dtpReIncome.EnableWindow(FALSE);
		m_EdtMoney.SetWindowText(GetMyNumberFormat(m_nDebit));
		m_stcBalance.SetWindowText("0");
	}
}

void CGroupIncomeDlg::OnBnClickedReincomCheck()
{
	if(m_chkReIncome.GetCheck())
		m_dtpReIncome.EnableWindow(TRUE);	
	else
		m_dtpReIncome.EnableWindow(FALSE);
}
