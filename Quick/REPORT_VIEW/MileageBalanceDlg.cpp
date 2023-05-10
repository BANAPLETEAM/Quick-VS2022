// MileageBalanceDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "quick.h"
#include "MileageBalanceDlg.h"
#include ".\mileagebalancedlg.h"


// CMileageBalanceDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMileageBalanceDlg, CMyDialog)
CMileageBalanceDlg::CMileageBalanceDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMileageBalanceDlg::IDD, pParent)
	, m_sCharge(_T(""))
	, m_sEtc(_T(""))
	, m_nType(0)
{
	m_nMileageBalance = 0;
	m_nCNo = 0;
}

CMileageBalanceDlg::~CMileageBalanceDlg()
{
}

void CMileageBalanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BEFORE_STATIC, m_stcBefore);
	DDX_Control(pDX, IDC_AFTER_STATIC, m_stcAfter);
	DDX_Control(pDX, IDC_CHARGE_EDIT, m_edtCharge);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);
	DDX_Text(pDX, IDC_CHARGE_EDIT, m_sCharge);
	DDX_Control(pDX, IDC_COMBO1, m_cmbType);
	DDX_Text(pDX, IDC_ETC_EDIT, m_sEtc);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nType);
}


BEGIN_MESSAGE_MAP(CMileageBalanceDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_EN_CHANGE(IDC_CHARGE_EDIT, OnEnChangeChargeEdit)
END_MESSAGE_MAP()


// CMileageBalanceDlg 메시지 처리기입니다.

void CMileageBalanceDlg::OnBnClickedOkBtn()
{
	UpdateData(TRUE);

	if(atoi(m_sCharge) <= 0)
	{
        MessageBox("수정금액을 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	/*
	long nCharge = atol(m_sCharge);
	if(nCharge < 0 || nCharge > 1000000)
	{
		MessageBox("금액이 0원이하이거나 1,000,000 이상입니다. 금액을 다시 수정하여주세요" , 
			"확인", MB_ICONINFORMATION);
		OnCancel();
		return;
	}
	*/
	m_nType = m_cmbType.GetCurSel();
	OnOK();
}

void CMileageBalanceDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CMileageBalanceDlg::OnEnChangeChargeEdit()
{
	CString sBalance; m_edtCharge.GetWindowText(sBalance);
	long nBalance = atoi(sBalance);

	if(m_cmbType.GetCurSel() != 0)
		nBalance = nBalance * -1;

	m_stcAfter.SetWindowText(::GetMyNumberFormat(m_nMileageBalance + nBalance) + "원");
}

BOOL CMileageBalanceDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
 
	m_cmbType.SetCurSel(0);
	

	

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_get_mile");	
	pCmd.AddParameter(m_nCNo);
	CMkParameter *pParMileage = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	if(!pRs.Execute(&pCmd))
		MessageBox("인터넷연결이 실패되었습니다.", "확인", MB_ICONINFORMATION);
	else
	{
		long nMileageBalance = 0;
		pParMileage->GetValue(nMileageBalance);
		m_nMileageBalance = nMileageBalance;
		m_stcBefore.SetWindowText(::GetMyNumberFormat(nMileageBalance) + "원");
		m_stcAfter.SetWindowText(::GetMyNumberFormat(nMileageBalance) + "원");
		//m_stcBefore.SetWindowText(GetMyNumberFormat(nMileageBalance));
	}

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
