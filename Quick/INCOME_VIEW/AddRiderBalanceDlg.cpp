// AddRiderBalanceDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AddRiderBalanceDlg.h"



// CAddRiderBalanceDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAddRiderBalanceDlg, CMyDialog)
CAddRiderBalanceDlg::CAddRiderBalanceDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAddRiderBalanceDlg::IDD, pParent)
	, m_strInputSave(_T(""))
{
	m_bAdd = TRUE;
}

CAddRiderBalanceDlg::~CAddRiderBalanceDlg()
{
}

void CAddRiderBalanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUR_SAVE_STATIC, m_stcCurSave);
	DDX_Control(pDX, IDC_AFTER_SAVE_STATIC, m_stcAfterSave);
	DDX_Control(pDX, IDC_INPUT_SAVE_COMBO, m_cmbInputSave);
	DDX_Control(pDX, IDC_INPUT_SAVE_TYPE_COMBO, m_cmbInputSaveType);
	DDX_Control(pDX, IDC_SAVE_ETC_EDIT, m_edtSaveEtc);
	DDX_Control(pDX, IDC_STATIC1, m_stc1);
	DDX_Control(pDX, IDC_STATIC2, m_stc2);
	DDX_Control(pDX, IDC_STATIC3, m_stc3);
	DDX_Control(pDX, IDC_REPORT_LIST, m_wndReport);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_CBString(pDX, IDC_INPUT_SAVE_COMBO, m_strInputSave);
}


BEGIN_MESSAGE_MAP(CAddRiderBalanceDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_INPUT_SAVE_COMBO, OnCbnSelchangeInputSaveCombo)
	//ON_EN_CHANGE(IDC_SAVE_EDIT, OnEnChangeSaveEdit)
	ON_CBN_EDITUPDATE(IDC_INPUT_SAVE_COMBO, OnCbnEditupdateInputSaveCombo)
END_MESSAGE_MAP()


void CAddRiderBalanceDlg::RefreshCharge(BOOL bClick)
{
	CString strCur, strPlus;
	m_stcCurSave.GetWindowText(strCur);
	strCur.Replace(",", "");

	if(bClick)
		m_cmbInputSave.GetLBText(m_cmbInputSave.GetCurSel(), strPlus);
	else
		m_cmbInputSave.GetWindowText(strPlus);

	if(m_bAdd)
		m_stcAfterSave.SetWindowText(LF->GetMyNumberFormat(_ttoi(strCur) + _ttoi(strPlus)));
	else
		m_stcAfterSave.SetWindowText(LF->GetMyNumberFormat(_ttoi(strCur) - _ttoi(strPlus)));
}

void CAddRiderBalanceDlg::OnBnClickedOk()
{
	if(!LF->POWER_CHECK(7031, "선입금충전전용",TRUE))
		return;

	long nReturn;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_rider_deposit_balance_today");

    CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(m_nRiderCompany);
	pCmd.AddParameter(m_nRNo);
	pCmd.AddParameter(m_strRName);

	long nIndex = m_cmbInputSaveType.GetCurSel();
	pCmd.AddParameter((long)m_cmbInputSaveType.GetItemData(nIndex));

	CString strAmount;
	m_cmbInputSave.GetWindowText(strAmount); 
	//nIndex = m_cmbInputSave.GetCurSel();

	//if(nIndex == -1)
	//{
	//	MessageBox("입금액을 입력하세요", "확인", MB_ICONINFORMATION);
	//	return;
	//}


	if(strAmount == "" || strAmount == "0")
	{
		MessageBox("입금액을 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	pCmd.AddParameter(_ttoi(strAmount));
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);

	m_edtSaveEtc.GetWindowText(strAmount);
	pCmd.AddParameter(strAmount); //사유

	if(!pRs.Execute(&pCmd)) return;

	pPar->GetValue(nReturn);

	if(nReturn == -1)
		MessageBox("잔액이 부족합니다", "확인", MB_ICONINFORMATION);

	MessageBox("적용되었습니다", "확인", MB_ICONINFORMATION);

	OnOK();
}

BOOL CAddRiderBalanceDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();

	m_wndReport.InsertColumn(0, "날짜", LVCFMT_LEFT, 70);
	m_wndReport.InsertColumn(1, "상태", LVCFMT_LEFT, 100);
	m_wndReport.InsertColumn(2, "금액", LVCFMT_LEFT, 50);
	m_wndReport.InsertColumn(3, "잔액", LVCFMT_LEFT, 50);
	m_wndReport.InsertColumn(4, "적요", LVCFMT_LEFT, 80);
	m_wndReport.Populate();

	InitRider();
	InitControl();

	m_cmbInputSave.SetCurSel(0);
	
	RefreshCharge();
	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAddRiderBalanceDlg::InitControl()
{
	if(m_bAdd)
	{
		this->SetWindowText("잔액 충전");

		m_cmbInputSaveType.InsertString(0, "(+)잔액충전(현금)");
		m_cmbInputSaveType.SetItemData(0, 17);
		m_cmbInputSaveType.InsertString(1, "(+)잔액충전(온라인입금)");
		m_cmbInputSaveType.SetItemData(1, 16);
	}
	else
	{
		this->SetWindowText("잔액 차감");
		m_stc1.SetWindowText("차감금액");
		m_stc1.SetWindowText("차감내용");
		m_stc1.SetWindowText("차감종류");

		m_cmbInputSaveType.InsertString(0, "(-)잔액차감");
		m_cmbInputSaveType.SetItemData(0, 40);
		m_cmbInputSaveType.InsertString(1, "(-)잔액차감(충전취소)");
		m_cmbInputSaveType.SetItemData(1, 49);
	}

	m_cmbInputSaveType.SetCurSel(0);
}

void CAddRiderBalanceDlg::InitRider()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_deposit_info");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRiderCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRNo);

	if(!pRs.Execute(&pCmd))  return;

	long nBalance;
	
	pRs.GetFieldValue("nBalance", nBalance);

	m_stcCurSave.SetWindowText(LF->GetMyNumberFormat(nBalance));
}

void CAddRiderBalanceDlg::OnCbnSelchangeInputSaveCombo()
{
	RefreshCharge();
}

/*
void CAddRiderBalanceDlg::OnEnChangeSaveEdit()
{
	RefreshCharge();
}
*/

void CAddRiderBalanceDlg::RefreshList()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_fixed_deposit_not_allocate");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRiderCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRNo);

	if(!pRs.Execute(&pCmd)) return;

	COleDateTime dtGenerate;
	long nState, nAmount, nBalance;
	CString sEtc;
	
	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("dtGenerate", dtGenerate);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("nAmount", nAmount);
		pRs.GetFieldValue("nBalance", nBalance);
		pRs.GetFieldValue("sEtc", sEtc);

		m_wndReport.InsertItem(i, dtGenerate.Format("%m-%d %H:%M"));
		m_wndReport.SetItemText(i, 1, LF->GetFixedDepositStateString(nState));
		m_wndReport.SetItemText(i, 2, LF->GetMyNumberFormat(nAmount));
		m_wndReport.SetItemText(i, 3, LF->GetMyNumberFormat(nBalance));
		m_wndReport.SetItemText(i, 4, sEtc);

		m_wndReport.SetItemData(i, nState);

		pRs.MoveNext();
	}

	m_wndReport.Populate();
}


void CAddRiderBalanceDlg::OnCbnEditupdateInputSaveCombo()
{
	RefreshCharge(FALSE);
}
