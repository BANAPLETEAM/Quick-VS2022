// ChargeWorkDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargeWorkDlg.h"



// CChargeWorkDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChargeWorkDlg, CMyDialog)
CChargeWorkDlg::CChargeWorkDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChargeWorkDlg::IDD, pParent)
{
}

CChargeWorkDlg::~CChargeWorkDlg()
{
}

void CChargeWorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START_DO_COMBO, m_StartDoCmb);
	DDX_Control(pDX, IDC_START_SI_COMBO, m_StartSiCmb);
	DDX_Control(pDX, IDC_DEST_DO_COMBO, m_DestDoCmb);
	DDX_Control(pDX, IDC_DEST_SI_COMBO, m_DestSiCmb);
	DDX_Control(pDX, IDC_START_TYPE_COMBO, m_StartCmb);
	DDX_Control(pDX, IDC_DEST_TYPE_COMBO, m_DestCmb);
	DDX_Control(pDX, IDC_PLUS_COMBO, m_PlusCmb);
	DDX_Control(pDX, IDC_CHARGE_EDIT, m_ChargeEdt);
	DDX_Control(pDX, IDC_STATIC1, m_Stc1);
	DDX_Control(pDX, IDC_STATIC2, m_Stc2);
	DDX_Control(pDX, IDC_STATIC3, m_Stc3);
	DDX_Control(pDX, IDC_RIDER_TYPE_COMBO, m_RiderTypeCmb);
	DDX_Control(pDX, IDC_WAY_CHECK, m_chkWay);
	
}


BEGIN_MESSAGE_MAP(CChargeWorkDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BUTTON, OnBnClickedOkButton)
	ON_CBN_SELCHANGE(IDC_START_DO_COMBO, OnCbnSelchangeStartDoCombo)
	ON_CBN_SELCHANGE(IDC_START_SI_COMBO, OnCbnSelchangeStartSiCombo)
	ON_CBN_SELCHANGE(IDC_START_TYPE_COMBO, OnCbnSelchangeStartTypeCombo)
	ON_CBN_SELCHANGE(IDC_DEST_TYPE_COMBO, OnCbnSelchangeDestTypeCombo)
	ON_CBN_SELCHANGE(IDC_PLUS_COMBO, OnCbnSelchangePlusCombo)
	ON_EN_CHANGE(IDC_CHARGE_EDIT, OnEnChangeChargeEdit)
	ON_CBN_SELCHANGE(IDC_DEST_DO_COMBO, OnCbnSelchangeDestDoCombo)
	ON_CBN_SELCHANGE(IDC_DEST_SI_COMBO, OnCbnSelchangeDestSiCombo)
	ON_BN_CLICKED(IDC_CANCEL_BUTTON, OnBnClickedCancelButton)
	ON_CBN_SELCHANGE(IDC_RIDER_TYPE_COMBO, OnCbnSelchangeRiderTypeCombo)
END_MESSAGE_MAP()


// CChargeWorkDlg 메시지 처리기입니다.

void CChargeWorkDlg::OnBnClickedOkButton()
{
	if(m_ChargeEdt.GetWindowTextLength() <= 0)
	{
		MessageBox("금액을 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_charge_type2");

	CString sStartDo, sStartSi, sDestDo, sDestSi, sStartType, sDestType, sPlus, sRiderType, sCharge;
	m_StartDoCmb.GetLBText(m_StartDoCmb.GetCurSel(), sStartDo);
	m_StartSiCmb.GetLBText(m_StartSiCmb.GetCurSel(), sStartSi);
	m_DestDoCmb.GetLBText(m_DestDoCmb.GetCurSel(), sDestDo);
	m_DestSiCmb.GetLBText(m_DestSiCmb.GetCurSel(), sDestSi);
	m_StartCmb.GetLBText(m_StartCmb.GetCurSel(), sStartType);
	m_DestCmb.GetLBText(m_DestCmb.GetCurSel(), sDestType);
	m_PlusCmb.GetLBText(m_PlusCmb.GetCurSel(), sPlus);
	m_RiderTypeCmb.GetLBText(m_RiderTypeCmb.GetCurSel(), sRiderType);
	m_ChargeEdt.GetWindowText(sCharge);
	
	sStartType.Replace("타입", "");
	sDestType.Replace("타입", "");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
	pCmd.AddParameter(typeString, typeInput, sStartDo.GetLength(), sStartDo);
	pCmd.AddParameter(typeString, typeInput, sStartSi.GetLength(), sStartSi);
	pCmd.AddParameter(typeString, typeInput, sDestDo.GetLength(), sDestDo);
	pCmd.AddParameter(typeString, typeInput, sDestSi.GetLength(), sDestSi);
	pCmd.AddParameter(typeString, typeInput, sStartType.GetLength(), sStartType);
	pCmd.AddParameter(typeString, typeInput, sDestType.GetLength(), sDestType);
	pCmd.AddParameter(typeString, typeInput, sRiderType.GetLength(), sRiderType);
	pCmd.AddParameter(typeString, typeInput, sPlus.GetLength(), sPlus);
	pCmd.AddParameter(typeString, typeInput, sCharge.GetLength(), sCharge);
	pCmd.AddParameter(m_chkWay.GetCheck());
	if(!pRs.Execute(&pCmd)) return;

	MessageBox("적용 되었습니다", "확인", MB_ICONINFORMATION);
	OnOK();
}

BOOL CChargeWorkDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	SetForegroundWindow();

	CString sTitle;
	this->GetWindowText(sTitle);
	sTitle += " - " + m_ci.GetBranchName(m_nCompany);
	this->SetWindowText(sTitle);

	InitStruct();
	InitDoCombo();

	m_StartDoCmb.SetCurSel(0);
	m_DestDoCmb.SetCurSel(0);
	m_StartCmb.SetCurSel(0);
	m_DestCmb.SetCurSel(0);
	m_PlusCmb.SetCurSel(0);
	m_RiderTypeCmb.SetCurSel(0);
	m_RiderTypeCmb.SetCurSel(0);

	m_chkWay.SetCheck(TRUE);

	OnCbnSelchangeStartDoCombo();
	OnCbnSelchangeDestDoCombo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CChargeWorkDlg::InitDoCombo()
{
	SITY_MAP::iterator it; 
	long nItem = 0; 

	for(it = m_map.begin(); it != m_map.end(); it++)
	{		
		m_StartDoCmb.InsertString(nItem, it->second.sDo);
		m_DestDoCmb.InsertString(nItem++, it->second.sDo);
	}
}

void CChargeWorkDlg::InitStruct()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_work_dong_pos_all");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), 1);

	if(!pRs.Execute(&pCmd)) return;

	CString sMainDo, sMainSi;
	sMainDo = sMainSi = "전체";

	long nItem = 0;
	long nDo = 0;
	long nSi = 1;

	SITY_STRUCT sity;
	sity.sDo = sMainDo;
	sity.sSi[0] = sMainSi;

	while(!pRs.IsEOF())
	{
		CString sDo, sSi;
		pRs.GetFieldValue("sSido", sDo);
		pRs.GetFieldValue("sGugun", sSi);

		if(sMainDo != sDo)
		{
			sity.nCount = nSi;
			m_map[nItem++] = sity;
			EmptyStruct(&sity);
			sMainDo = sDo;
			sity.sDo = sDo;
			sity.sSi[0] = sMainSi;
			sity.sSi[1] = sSi;
			nSi = 2;
		}
		else
		{
			sity.sSi[nSi++] = sSi;
		}

		pRs.MoveNext();
	}
}

void CChargeWorkDlg::EmptyStruct(SITY_STRUCT* st)
{
    for(int i=0; i<50; i++)	
		st->sSi[i] = "";
}

void CChargeWorkDlg::OnCbnSelchangeStartDoCombo()
{
	m_StartSiCmb.ResetContent();

	long nIndex = m_StartDoCmb.GetCurSel();

	for(int i=0; i<m_map[nIndex].nCount; i++)
	{
		CString s = m_map[nIndex].sSi[i];
		m_StartSiCmb.InsertString(i, m_map[nIndex].sSi[i]);
	}

	m_StartSiCmb.SetCurSel(0);

	if(m_DestSiCmb.GetCurSel() == -1)
		return;

	ReWriteStc();
}

void CChargeWorkDlg::ReWriteStc()
{
    CString sStartDo = "";
	CString sStartSi = "";
	CString sDestDo = "";
	CString sDestSi = "";
	CString sStartType = "";
	CString sDestType = "";
	CString sRiderType = "";
	CString sPlus = "";
	CString sCharge = "";
	CString sStr1 = "";
	CString sStr2 = "";
	CString sStr3 = "";

	m_StartDoCmb.GetLBText(m_StartDoCmb.GetCurSel(), sStartDo);
	m_StartSiCmb.GetLBText(m_StartSiCmb.GetCurSel(), sStartSi);
	m_DestDoCmb.GetLBText(m_DestDoCmb.GetCurSel(), sDestDo);
	m_DestSiCmb.GetLBText(m_DestSiCmb.GetCurSel(), sDestSi);
	m_StartCmb.GetLBText(m_StartCmb.GetCurSel(), sStartType);
	m_DestCmb.GetLBText(m_DestCmb.GetCurSel(), sDestType);
	m_PlusCmb.GetLBText(m_PlusCmb.GetCurSel(), sPlus);

	sRiderType = GetRiderType(m_RiderTypeCmb.GetCurSel());

	m_ChargeEdt.GetWindowText(sCharge);

	sStr1 += sStartDo + "(" + sStartSi + ")에서 " + sDestDo + "(" + sDestSi + ")로의";
	sStr2 += sStartType + " 금액을 " + sDestType + " 금액으로 " + sRiderType + "요금을";

	if(sPlus == "+")
		sStr3 += sStr3 + " " + sCharge == "" ? "0" : sCharge + "원 만큼 더해 줍니다";
	else if(sPlus == "-")
		sStr3 += sStr3 + " " + sCharge == "" ? "0" : sCharge + "원 만큼 빼 줍니다";

	m_Stc1.SetWindowText(sStr1);
	m_Stc2.SetWindowText(sStr2);
	m_Stc3.SetWindowText(sStr3);
}

CString CChargeWorkDlg::GetRiderType(long index)
{
	if(index == 0)
		return "전체";
	else if(index == 1)
		return "오토짐받이";
	else if(index == 2)
		return "다마라보";
	else if(index == 3)
		return "밴";
	else if(index == 4)
		return "트럭";
	else 
		return "알수없음";
}

void CChargeWorkDlg::OnCbnSelchangeStartSiCombo()
{
	ReWriteStc();
}

void CChargeWorkDlg::OnCbnSelchangeStartTypeCombo()
{
	ReWriteStc();
}

void CChargeWorkDlg::OnCbnSelchangeDestTypeCombo()
{
	ReWriteStc();
}

void CChargeWorkDlg::OnCbnSelchangePlusCombo()
{
	ReWriteStc();
}

void CChargeWorkDlg::OnEnChangeChargeEdit()
{
	ReWriteStc();
}

void CChargeWorkDlg::OnCbnSelchangeDestDoCombo()
{
	m_DestSiCmb.ResetContent();

	long nIndex = m_DestDoCmb.GetCurSel();

	for(int i=0; i<m_map[nIndex].nCount; i++)
	{
		m_DestSiCmb.InsertString(i, m_map[nIndex].sSi[i]);
	}

	m_DestSiCmb.SetCurSel(0);

	ReWriteStc();	
}

void CChargeWorkDlg::OnCbnSelchangeDestSiCombo()
{
	ReWriteStc();
}



void CChargeWorkDlg::OnBnClickedCancelButton()
{
	OnCancel();
}

void CChargeWorkDlg::OnCbnSelchangeRiderTypeCombo()
{
	ReWriteStc();
}
