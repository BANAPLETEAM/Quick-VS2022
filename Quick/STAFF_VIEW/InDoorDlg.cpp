// InDoorDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "InDoorDlg.h"
#include "PasswordDlg.h"
#include "StaffPage11.h"



// CInDoorDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CInDoorDlg, CMyDialog)
CInDoorDlg::CInDoorDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CInDoorDlg::IDD, pParent)
{
	m_bNewMode = FALSE;
	m_WNoPageRefresh = FALSE;
	m_pParentWnd = pParent;
	m_WNoPageRefresh = FALSE;
}

CInDoorDlg::~CInDoorDlg()
{
	//if(m_WNoPageRefresh)
	//	((CStaffPage11*)m_pParentWnd)->RefreshList();

}

void CInDoorDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ENTER_DT, m_EnterDT);
	DDX_Control(pDX, IDC_NAME_EDIT, m_NameEdt);
	DDX_Control(pDX, IDC_SSN_EDIT1, m_SSNEdt1);
	DDX_Control(pDX, IDC_SSN_EDIT2, m_SSNEdt2);
	DDX_Control(pDX, IDC_WORK_PART_COMBO, m_WorkPartCmb);
	DDX_Control(pDX, IDC_WNO_EDIT, m_WNoEdt);
	DDX_Control(pDX, IDC_BANK_NAME_EDIT, m_BankNameEdt);
	DDX_Control(pDX, IDC_POSITION_EDIT, m_PositionEdt);
	DDX_Control(pDX, IDC_MP_EDIT, m_MpEdt);
	DDX_Control(pDX, IDC_BANK_ACCOUNT_EDIT, m_BankAccountEdt);
	DDX_Control(pDX, IDC_ID_EDIT, m_IdEdt);
	DDX_Control(pDX, IDC_PHONE_EDIT, m_PhoneEdt);
	DDX_Control(pDX, IDC_BANK_OWNER_EDIT, m_BankOwnerEdt);
	DDX_Control(pDX, IDC_PW_EDIT, m_PwEdt);
	DDX_Control(pDX, IDC_ADDRESS_EDIT, m_AddressEdt);
	DDX_Control(pDX, IDC_MEMO_EDIT, m_MemoEdt);
	DDX_Control(pDX, IDC_WORK_STATE_COMBO, m_WorkStateCmb);
	DDX_Control(pDX, IDC_WORK_TYPE_COMBO1, m_WorkTypeCmb);
	DDX_Control(pDX, IDC_WAGES_TYPE_COMBO, m_WagesTypeCmb);
	DDX_Control(pDX, IDC_WAGES_BASIC_EDIT, m_WagesBasicEdt);
	DDX_Control(pDX, IDC_WAGES_AID_EDIT1, m_WagesAidEdt1); 
	DDX_Control(pDX, IDC_WAGES_AID_EDIT2, m_WagesAidEdt2);
	DDX_Control(pDX, IDC_WAGES_AID_EDIT3, m_WagesAidEdt3);
	DDX_Control(pDX, IDC_WAGES_AID_EDIT4, m_WagesAidEdt4);
	DDX_Control(pDX, IDC_WAGES_AID_CHARGE_EDIT1, m_WagesAidChargeEdt1); 
	DDX_Control(pDX, IDC_WAGES_AID_CHARGE_EDIT2, m_WagesAidChargeEdt2);
	DDX_Control(pDX, IDC_WAGES_AID_CHARGE_EDIT3, m_WagesAidChargeEdt3);
	DDX_Control(pDX, IDC_WAGES_AID_CHARGE_EDIT4, m_WagesAidChargeEdt4);
	DDX_Control(pDX, IDC_APPLY_INSURANCE_CHECK, m_ApplyInsuranceChk);
	DDX_Control(pDX, IDC_NOT_APPLY_INSURANCE_CHECK, m_NotApplyInsuranceChk);
	DDX_Control(pDX, IDC_DT_FEE_EDIT, m_DtFeeEdt);
	DDX_Control(pDX, IDC_KUKMIN_INS_CHECK, m_KukminInsChk);
	DDX_Control(pDX, IDC_KUKMIN_INS_EDIT, m_KukminInsEdt);

	DDX_Control(pDX, IDC_URYO_INS_CHECK, m_UryoInsChk);
	DDX_Control(pDX, IDC_URYO_INS_EDIT, m_UryoInsEdt);

	DDX_Control(pDX, IDC_SANJAE_INS_CHECK, m_SanjaeInsChk);
	DDX_Control(pDX, IDC_SANJAE_INS_EDIT, m_SanjaeInsEdt);

	DDX_Control(pDX, IDC_GOYONG_INS_CHECK, m_GoyongInsChk);
	DDX_Control(pDX, IDC_GOYONG_INS_EDIT, m_GoyongInsEdt);

	DDX_Control(pDX, IDC_GABKUN_INS_CHECK, m_GabkunInsChk);
	DDX_Control(pDX, IDC_GABKUN_INS_EDIT, m_GabkunInsEdt);

	DDX_Control(pDX, IDC_SODUC_INS_CHECK, m_SoducInsChk);
	DDX_Control(pDX, IDC_SODUC_INS_EDIT, m_SoducInsEdt);

	DDX_Control(pDX, IDC_JUMIN_INS_CHECK, m_JuminInsChk);
	DDX_Control(pDX, IDC_JUMIN_INS_EDIT, m_JuminInsEdt);

	DDX_Control(pDX, IDC_ETC_INS_EDIT, m_EtcInsEdt);
	DDX_Control(pDX, IDC_ETC_INS_FEE_EDIT, m_EtcInsFeeEdt);
	DDX_Control(pDX, IDC_IN_DOOR_MEMO_EDIT, m_InDoorMemo);
	DDX_Control(pDX, IDC_SAVE_BTN, m_SaveBtn);
	DDX_Control(pDX, IDC_INNER_MEMO_EDIT, m_edtInnerMemo);
	DDX_Control(pDX, IDC_AUTH_PHONE_EDIT, m_edtAuthPhone);
	DDX_Control(pDX, IDC_BRANCH_COMBO, m_cmbBranch);
}


BEGIN_MESSAGE_MAP(CInDoorDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SAVE_BTN, OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_APPLY_INSURANCE_CHECK, OnBnClickedApplyInsuranceCheck)
	ON_BN_CLICKED(IDC_NOT_APPLY_INSURANCE_CHECK, OnBnClickedNotApplyInsuranceCheck)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, OnBnClickedCloseButton)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_PW_EDIT_BTN, &CInDoorDlg::OnBnClickedPwEditBtn)
END_MESSAGE_MAP()



BOOL CInDoorDlg::AddNewInDoor()
{
	COleDateTime dtEnter; m_EnterDT.GetTime(dtEnter);
	CString sName; m_NameEdt.GetWindowText(sName); 
	CString sSSN1; m_SSNEdt1.GetWindowText(sSSN1);
	CString sSSN2; m_SSNEdt2.GetWindowText(sSSN2);
	long nWorkPart = m_WorkPartCmb.GetCurSel();
	CString sWNo; m_WNoEdt.GetWindowText(sWNo);
	CString sBankName; m_BankNameEdt.GetWindowText(sBankName);
	CString sPosition; m_PositionEdt.GetWindowText(sPosition);
	CString sMp; m_MpEdt.GetWindowText(sMp);
	CString sBankAccount; m_BankAccountEdt.GetWindowText(sBankAccount);
	CString sID; m_IdEdt.GetWindowText(sID);
	CString sPhone; m_PhoneEdt.GetWindowText(sPhone);
	CString sBankOwner; m_BankOwnerEdt.GetWindowText(sBankOwner);
	CString sPw; m_PwEdt.GetWindowText(sPw);
	CString sAddress; m_AddressEdt.GetWindowText(sAddress);
	CString sMemo; m_MemoEdt.GetWindowText(sMemo);
	long nWorkState = m_WorkStateCmb.GetCurSel();	
	long nWorkType = m_WorkTypeCmb.GetCurSel();
	long nWagesType = m_WagesTypeCmb.GetCurSel();
	CString sWagesBasic; m_WagesBasicEdt.GetWindowText(sWagesBasic);
	sWagesBasic.Replace(",", "");
	CString strAuthPhone; m_edtAuthPhone.GetWindowText(strAuthPhone);

	CString sEtc, sEtcCharge = "";
	GetEtcEdit(sEtc, sEtcCharge);

	long bApplyIns = m_ApplyInsuranceChk.GetCheck();
	CString sDTFee; m_DtFeeEdt.GetWindowText(sDTFee);

	BOOL bKukmin = m_KukminInsChk.GetCheck();
	CString sKukmin; m_KukminInsEdt.GetWindowText(sKukmin);
	BOOL bUryo = m_UryoInsChk.GetCheck();
	CString sUryo; m_UryoInsEdt.GetWindowText(sUryo);
	BOOL bSanjae = m_SanjaeInsChk.GetCheck();
	CString sSanjae; m_SanjaeInsEdt.GetWindowText(sSanjae);
	BOOL bGoyong = m_GoyongInsChk.GetCheck();
	CString sGoyong; m_GoyongInsEdt.GetWindowText(sGoyong);
	BOOL bGabkun = m_GabkunInsChk.GetCheck();
	CString sGabkun; m_GabkunInsEdt.GetWindowText(sGabkun);
	BOOL bSoduc = m_SoducInsChk.GetCheck();
	CString sSoduc; m_SoducInsEdt.GetWindowText(sSoduc);
	BOOL bJumin = m_JuminInsChk.GetCheck();
	CString sJumin; m_JuminInsEdt.GetWindowText(sJumin);

	CString sEtcIns; m_EtcInsEdt.GetWindowText(sEtcIns);
	CString sEtcInsCharge; m_EtcInsEdt.GetWindowText(sEtcInsCharge);

	CString sIndoorMemo; m_InDoorMemo.GetWindowText(sIndoorMemo);

	if(sID == "")
	{
		MessageBox("아이디를 입력하세요", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	else if(sWNo == "")
	{
		MessageBox("사원번호를 입력하세요", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	else if(sID.Find("/") >= 0 || sID.Find(",") >= 0 || sID.Find("@") >= 0 || sID.Find(" ") >= 0)
	{
		MessageBox("아이디에 (/) (@) (,) (빈칸) 는 사용할수 없습니다.", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	else if(sName.Find("/") >= 0 || sName.Find(",") >= 0 || sName.Find("@") >= 0 || sName.Find(" ") >= 0)
	{
		MessageBox("성명에 (/) (@) (,) (빈칸) 는 사용할수 없습니다.", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	long nCompany = (long)m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel());

	CMkCommand pCmd(m_pMkDb, "insert_manager_indoor_admin_1");

	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	//pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtEnter);
	pCmd.AddParameter(typeString, typeInput, sName.GetLength(), sName);
	pCmd.AddParameter(typeString, typeInput, sSSN1.GetLength(), sSSN1);
	pCmd.AddParameter(typeString, typeInput, sSSN2.GetLength(), sSSN2);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nWorkPart);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), _ttoi(sWNo));
	pCmd.AddParameter(typeString, typeInput, sBankName.GetLength(), sBankName);
	pCmd.AddParameter(typeString, typeInput, sPosition.GetLength(), sPosition);
	pCmd.AddParameter(typeString, typeInput, sMp.GetLength(), sMp);
	pCmd.AddParameter(typeString, typeInput, sBankAccount.GetLength(), sBankAccount);
	pCmd.AddParameter(typeString, typeInput, sID.GetLength(), sID);
	pCmd.AddParameter(typeString, typeInput, sPhone.GetLength(), sPhone);
	pCmd.AddParameter(typeString, typeInput, sBankOwner.GetLength(), sBankOwner);
	pCmd.AddParameter(typeString, typeInput, sPw.GetLength(), sPw);
	pCmd.AddParameter(typeString, typeInput, sAddress.GetLength(), sAddress);
	pCmd.AddParameter(typeString, typeInput, sMemo.GetLength(), sMemo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nWorkState);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nWorkType);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nWagesType);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), _ttoi(sWagesBasic));
	pCmd.AddParameter(typeString, typeInput, sEtc.GetLength(), sEtc);
	pCmd.AddParameter(typeString, typeInput, sEtcCharge.GetLength(), sEtcCharge);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bApplyIns);
	pCmd.AddParameter(typeString, typeInput, sDTFee.GetLength(), sDTFee);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bKukmin);
	pCmd.AddParameter(typeString, typeInput, sKukmin.GetLength(), sKukmin);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bUryo);
	pCmd.AddParameter(typeString, typeInput, sUryo.GetLength(), sUryo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bSanjae);
	pCmd.AddParameter(typeString, typeInput, sSanjae.GetLength(), sSanjae);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bGoyong);
	pCmd.AddParameter(typeString, typeInput, sGoyong.GetLength(), sGoyong);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bGabkun);
	pCmd.AddParameter(typeString, typeInput, sGabkun.GetLength(), sGabkun);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bSoduc);
	pCmd.AddParameter(typeString, typeInput, sSoduc.GetLength(), sSoduc);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bJumin);
	pCmd.AddParameter(typeString, typeInput, sJumin.GetLength(), sJumin);
	pCmd.AddParameter(typeString, typeInput, sEtcIns.GetLength(), sEtcIns);
	pCmd.AddParameter(typeString, typeInput, sEtcInsCharge.GetLength(), sEtcInsCharge);
	pCmd.AddParameter(typeString, typeInput, sIndoorMemo.GetLength(), sIndoorMemo);
	pCmd.AddParameter(strAuthPhone);

	if(!pCmd.Execute()) return FALSE;

	long nRet;
	pPar->GetValue(nRet);

	if(nRet == 10)
	{
		MessageBox("아이디(PDA번호)가 중복됩니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	else if(nRet == 20)
	{
		MessageBox("사원번호가 중복됩니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	m_nANo= nRet;

    return TRUE;
}

BOOL CInDoorDlg::UpdateUser()
{
	COleDateTime dtEnter; m_EnterDT.GetTime(dtEnter);
	CString sName; m_NameEdt.GetWindowText(sName);
	CString sSSN1; m_SSNEdt1.GetWindowText(sSSN1);
	CString sSSN2; m_SSNEdt2.GetWindowText(sSSN2);
	long nWorkPart = m_WorkPartCmb.GetCurSel();
	CString sWNo; m_WNoEdt.GetWindowText(sWNo);
	CString sBankName; m_BankNameEdt.GetWindowText(sBankName);
	CString sPosition; m_PositionEdt.GetWindowText(sPosition);
	CString sMp; m_MpEdt.GetWindowText(sMp);
	CString sBankAccount; m_BankAccountEdt.GetWindowText(sBankAccount);
	CString sID; m_IdEdt.GetWindowText(sID);
	CString sPhone; m_PhoneEdt.GetWindowText(sPhone);
	CString sBankOwner; m_BankOwnerEdt.GetWindowText(sBankOwner);
	CString sPw; m_PwEdt.GetWindowText(sPw);
	CString sAddress; m_AddressEdt.GetWindowText(sAddress);
	CString sMemo; m_MemoEdt.GetWindowText(sMemo);
	long nWorkState = m_WorkStateCmb.GetCurSel();	
	long nWorkType = m_WorkTypeCmb.GetCurSel();
	long nWagesType = m_WagesTypeCmb.GetCurSel();
	CString sWagesBasic; m_WagesBasicEdt.GetWindowText(sWagesBasic);
	sWagesBasic.Replace(",", "");

	CString sEtc, sEtcCharge = "";
	GetEtcEdit(sEtc, sEtcCharge);

	long bApplyIns = m_ApplyInsuranceChk.GetCheck();
	CString sDTFee; m_DtFeeEdt.GetWindowText(sDTFee);

	BOOL bKukmin = m_KukminInsChk.GetCheck();
	CString sKukmin; m_KukminInsEdt.GetWindowText(sKukmin);
	BOOL bUryo = m_UryoInsChk.GetCheck();
	CString sUryo; m_UryoInsEdt.GetWindowText(sUryo);
	BOOL bSanjae = m_SanjaeInsChk.GetCheck();
	CString sSanjae; m_SanjaeInsEdt.GetWindowText(sSanjae);
	BOOL bGoyong = m_GoyongInsChk.GetCheck();
	CString sGoyong; m_GoyongInsEdt.GetWindowText(sGoyong);
	BOOL bGabkun = m_GabkunInsChk.GetCheck();
	CString sGabkun; m_GabkunInsEdt.GetWindowText(sGabkun);
	BOOL bSoduc = m_SoducInsChk.GetCheck();
	CString sSoduc; m_SoducInsEdt.GetWindowText(sSoduc);
	BOOL bJumin = m_JuminInsChk.GetCheck();
	CString sJumin; m_JuminInsEdt.GetWindowText(sJumin);

	CString sEtcIns; m_EtcInsEdt.GetWindowText(sEtcIns);
	CString sEtcInsCharge; m_EtcInsEdt.GetWindowText(sEtcInsCharge);

	CString sIndoorMemo; m_InDoorMemo.GetWindowText(sIndoorMemo);
	CString sInnerMemo; m_edtInnerMemo.GetWindowText(sInnerMemo);
	CString strAuthPhone; m_edtAuthPhone.GetWindowText(strAuthPhone);


	if(sID == "")
	{
		MessageBox("아이디를 입력하세요", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	else if(sWNo == "")
	{
		MessageBox("사원번호를 입력하세요", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	else if(sID.Find("/") >= 0 || sID.Find(",") >= 0 || sID.Find("@") >= 0 || sID.Find(" ") >= 0)
	{
		MessageBox("아이디에 (/) (@) (,) (빈칸) 는 사용할수 없습니다.", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	else if(sName.Find("/") >= 0 || sName.Find(",") >= 0 || sName.Find("@") >= 0 || sName.Find(" ") >= 0)
	{
		MessageBox("성명에 (/) (@) (,) (빈칸) 는 사용할수 없습니다.", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	CMkCommand pCmd(m_pMkDb, "update_manager_indoor_admin_2");

	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtEnter);
	pCmd.AddParameter(typeString, typeInput, sName.GetLength(), sName);
	pCmd.AddParameter(typeString, typeInput, sSSN1.GetLength(), sSSN1);
	pCmd.AddParameter(typeString, typeInput, sSSN2.GetLength(), sSSN2);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nWorkPart);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), _ttoi(sWNo));
	pCmd.AddParameter(typeString, typeInput, sBankName.GetLength(), sBankName);
	pCmd.AddParameter(typeString, typeInput, sPosition.GetLength(), sPosition);
	pCmd.AddParameter(typeString, typeInput, sMp.GetLength(), sMp);
	pCmd.AddParameter(typeString, typeInput, sBankAccount.GetLength(), sBankAccount);
	pCmd.AddParameter(typeString, typeInput, sID.GetLength(), sID);
	pCmd.AddParameter(typeString, typeInput, sPhone.GetLength(), sPhone);
	pCmd.AddParameter(typeString, typeInput, sBankOwner.GetLength(), sBankOwner);
	pCmd.AddParameter(typeString, typeInput, sPw.GetLength(), sPw);
	pCmd.AddParameter(typeString, typeInput, sAddress.GetLength(), sAddress);
	pCmd.AddParameter(typeString, typeInput, sMemo.GetLength(), sMemo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nWorkState);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nWorkType);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nWagesType);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), _ttoi(sWagesBasic));
	pCmd.AddParameter(typeString, typeInput, sEtc.GetLength(), sEtc);
	pCmd.AddParameter(typeString, typeInput, sEtcCharge.GetLength(), sEtcCharge);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bApplyIns);
	pCmd.AddParameter(typeString, typeInput, sDTFee.GetLength(), sDTFee);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bKukmin);
	pCmd.AddParameter(typeString, typeInput, sKukmin.GetLength(), sKukmin);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bUryo);
	pCmd.AddParameter(typeString, typeInput, sUryo.GetLength(), sUryo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bSanjae);
	pCmd.AddParameter(typeString, typeInput, sSanjae.GetLength(), sSanjae);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bGoyong);
	pCmd.AddParameter(typeString, typeInput, sGoyong.GetLength(), sGoyong);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bGabkun);
	pCmd.AddParameter(typeString, typeInput, sGabkun.GetLength(), sGabkun);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bSoduc);
	pCmd.AddParameter(typeString, typeInput, sSoduc.GetLength(), sSoduc);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bJumin);
	pCmd.AddParameter(typeString, typeInput, sJumin.GetLength(), sJumin);
	pCmd.AddParameter(typeString, typeInput, sEtcIns.GetLength(), sEtcIns);
	pCmd.AddParameter(typeString, typeInput, sEtcInsCharge.GetLength(), sEtcInsCharge);
	pCmd.AddParameter(typeString, typeInput, sIndoorMemo.GetLength(), sIndoorMemo);
	pCmd.AddParameter(typeString, typeInput, sInnerMemo.GetLength(), sInnerMemo); 
	pCmd.AddParameter(strAuthPhone); 
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nWorkState);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nANo);

	if(!pCmd.Execute()) return FALSE; 

	long nRet;
	pPar->GetValue(nRet);

	if(nRet == 10)
	{
		MessageBox("아이디(PDA번호)가 중복됩니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	else if(nRet == 20)
	{
		MessageBox("사원번호가 중복됩니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	return TRUE;
}

void CInDoorDlg::OnBnClickedSaveBtn()
{
	if(m_bNewMode)
	{
		if(AddNewInDoor())
		{
			m_bNewMode = FALSE;
			m_WNoPageRefresh = TRUE;
			m_nCompany = LF->GetCurBranchInfo()->nCompanyCode;
			m_nWorkState = 0;
			m_WNoEdt.EnableWindow(FALSE);
            MessageBox("저장완료", "확인", MB_ICONINFORMATION);
			InitData();
			((CStaffPage11*)m_pParentWnd)->RefreshList();
			OnOK();
		}
	}
	else
	{
		if(UpdateUser())
		{
			m_WNoPageRefresh = TRUE;
			MessageBox("수정완료", "확인", MB_ICONINFORMATION);
			((CStaffPage11*)m_pParentWnd)->RefreshList();
			OnOK();
		}
	}
}

void CInDoorDlg::GetEtcEdit(CString &sEtc, CString &sEtcCharge)
{
	for(int i=0; i<4; i++)
	{
		CString sEtc1, sEtcCharge1;
		CEdit *pEtcEdt = (CEdit*)GetDlgItem(IDC_WAGES_AID_EDIT1 + i);
		CEdit *pEtcChargeEdt = (CEdit*)GetDlgItem(IDC_WAGES_AID_CHARGE_EDIT1 + i);

		pEtcEdt->GetWindowText(sEtc1);
		sEtc += sEtc1 + ";";
		pEtcChargeEdt->GetWindowText(sEtcCharge1);
		sEtcCharge += sEtcCharge1 + ";";
	}
}

BOOL CInDoorDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();

	m_SSNEdt1.LimitText(6);
	m_SSNEdt2.LimitText(7);

	m_WorkPartCmb.SetCurSel(0);
	m_WorkStateCmb.SetCurSel(0);
	m_WorkTypeCmb.SetCurSel(0);
	m_WagesTypeCmb.SetCurSel(0);

	m_WagesAidEdt1;
	m_WagesAidEdt2;
	m_WagesAidEdt3;
	m_WagesAidEdt4;
	m_WagesAidChargeEdt1;
	m_WagesAidChargeEdt2;
	m_WagesAidChargeEdt3;
	m_WagesAidChargeEdt4;

	m_WagesAidEdt1.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_WagesAidEdt1.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 155), "보조금1", TRUE);
	m_WagesAidEdt2.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_WagesAidEdt2.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 155), "보조금2", TRUE);
	m_WagesAidEdt3.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_WagesAidEdt3.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 155), "보조금3", TRUE);
	m_WagesAidEdt4.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_WagesAidEdt4.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 155), "보조금4", TRUE);

	m_WagesAidChargeEdt1.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_WagesAidChargeEdt1.SetTitle("입력하세요", TRUE);
	m_WagesAidChargeEdt2.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_WagesAidChargeEdt2.SetTitle("입력하세요", TRUE);
	m_WagesAidChargeEdt3.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_WagesAidChargeEdt3.SetTitle("입력하세요", TRUE);
	m_WagesAidChargeEdt4.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	m_WagesAidChargeEdt4.SetTitle("입력하세요", TRUE);

	m_IdEdt.SetUserOption(RGB(0, 0, 0), RGB(200, 255, 155), "필수입력");
	m_NameEdt.SetUserOption(RGB(0, 0, 0), RGB(200, 255, 155), "필수입력");
	m_WNoEdt.SetUserOption(RGB(0, 0, 0), RGB(200, 255, 155), "필수입력");

	OnBnClickedApplyInsuranceCheck();

	if(m_ba.GetCount() > 1) {
		//m_BranchCombo.ShowWindow(SW_SHOW);
		//m_BranchStatic.ShowWindow(SW_SHOW);
		for(int i = 0; i < m_ba.GetCount(); i++) {
			CBranchInfo *pBi = m_ba.GetAt(i);
			if(pBi->strBranchName == "통합")
				continue;
			int nItem = m_cmbBranch.AddString(pBi->strBranchName);
			m_cmbBranch.SetItemData(nItem, pBi->nCompanyCode);

			if(!m_bNewMode)
			{
				if(pBi->nCompanyCode == m_nCompany)
					m_cmbBranch.SetCurSel(nItem);
			}
		}
	}
	else {
		m_cmbBranch.AddString(m_ci.m_strBranchName);
		m_cmbBranch.SetItemData(0, m_ci.m_nCompanyCode);
	} 

	if(m_cmbBranch.GetCurSel() < 0)
		m_cmbBranch.SetCurSel(0);

	if(!m_bNewMode)
	{ 
		InitData();		

		if(m_nWNo == 0)
		{
			m_IdEdt.EnableWindow(FALSE);
			m_WNoEdt.EnableWindow(FALSE);
		}

		m_cmbBranch.EnableWindow(FALSE);
		m_PwEdt.EnableWindow(FALSE);
		m_PwEdt.SetPasswordChar('*');
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CInDoorDlg::InitData()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_indoor_detail_2");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nANo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nWorkState);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nWNo);

	if(!pRs.Execute(&pCmd)) return;

	if(pRs.GetRecordCount() == 0) return;

	char buffer[20];

	long   nMNo, nRole;//lCode,nCarType,nRicenceType,lANo,
	CString sID, sPW, sName, sSSN1, sSSN2, sTel, sMp, sAddress, sEtc, sRicenceNumber, sBankName, sBankAccount, sBankAccountOwner;
	COleDateTime dtEnter;
	long nWorkPart,  nWorkType, nWagesType, nWagesBasic;//nWorkState,
	CString sPosition, sWagesAid, sWagesAidCharge, sDTFee;
	BOOL bApplyInsurance, bKukminIns, bUryoIns, bSanjaeIns, bGoyongIns, bGabkunIns, bSoducIns, bJuminIns;
	CString sKukminInsFee, sUryoInsFee, sSanjaeInsFee, sGoyongInsFee, sGabkunInsFee, sSoducInsFee, sJuminInsFee;
	CString sEtcIns, sEtcInsFee, sInDoorEtc, sInnerMemo, strAuthPhone;

	pRs.GetFieldValue("lANo", m_nANo);
	pRs.GetFieldValue("nMNo", nMNo);
	pRs.GetFieldValue("sID", sID);
	pRs.GetFieldValue("sPW", sPW);
	pRs.GetFieldValue("sName", sName);
	pRs.GetFieldValue("dtEnter", dtEnter);
	pRs.GetFieldValue("sSSN1", sSSN1);
	pRs.GetFieldValue("sSSN2", sSSN2);
	pRs.GetFieldValue("sTel", sTel);
	pRs.GetFieldValue("sHp", sMp);
	pRs.GetFieldValue("sAddress", sAddress);
	pRs.GetFieldValue("nRole", nRole);
	pRs.GetFieldValue("sEtc", sEtc);
	pRs.GetFieldValue("sBankName", sBankName);
	pRs.GetFieldValue("sBankAccount", sBankAccount);
	pRs.GetFieldValue("sBankAccountOwner", sBankAccountOwner);
	pRs.GetFieldValue("nWorkPart", nWorkPart);
	pRs.GetFieldValue("sPosition", sPosition);
	pRs.GetFieldValue("nWorkState", m_nWorkState);
	pRs.GetFieldValue("nWorkType", nWorkType);
	pRs.GetFieldValue("nWagesType", nWagesType);
	pRs.GetFieldValue("nWagesBasic", nWagesBasic);
	pRs.GetFieldValue("sWagesAid", sWagesAid);
	pRs.GetFieldValue("sWagesAidCharge", sWagesAidCharge);
	pRs.GetFieldValue("bApplyInsurance", bApplyInsurance);
	pRs.GetFieldValue("sDTFee", sDTFee);
	pRs.GetFieldValue("bKukminIns", bKukminIns);
	pRs.GetFieldValue("sKukminInsFee", sKukminInsFee);
	pRs.GetFieldValue("bUryoIns", bUryoIns);
	pRs.GetFieldValue("sUryoInsFee", sUryoInsFee);
	pRs.GetFieldValue("bSanjaeIns", bSanjaeIns);
	pRs.GetFieldValue("sSanjaeInsFee", sSanjaeInsFee);
	pRs.GetFieldValue("bGoyongIns", bGoyongIns);
	pRs.GetFieldValue("sGoyongInsFee", sGoyongInsFee);
	pRs.GetFieldValue("bGabkunIns", bGabkunIns);
	pRs.GetFieldValue("sGabkunInsFee", sGabkunInsFee);
	pRs.GetFieldValue("bSoducIns", bSoducIns);
	pRs.GetFieldValue("sSoducInsFee", sSoducInsFee);
	pRs.GetFieldValue("bJuminIns", bJuminIns);
	pRs.GetFieldValue("sJuminInsFee", sJuminInsFee);
	pRs.GetFieldValue("sEtcIns", sEtcIns);
	pRs.GetFieldValue("sEtcInsFee", sEtcInsFee);
	pRs.GetFieldValue("sInDoorEtc", sInDoorEtc);
	pRs.GetFieldValue("sInnerMemo", sInnerMemo);
	pRs.GetFieldValue("sAuthPhone", strAuthPhone);

	m_EnterDT.SetTime(dtEnter);
	m_NameEdt.SetWindowText(sName);
	m_SSNEdt1.SetWindowText(sSSN1);
	m_SSNEdt2.SetWindowText(sSSN2);
	m_edtInnerMemo.SetWindowText(sInnerMemo);
	m_WorkPartCmb.SetCurSel(nWorkPart);
	m_WNoEdt.SetWindowText(itoa(nMNo, buffer, 10));
	m_BankNameEdt.SetWindowText(sBankName);
	m_PositionEdt.SetWindowText(sPosition);
	m_MpEdt.SetWindowText(sMp);
	m_BankAccountEdt.SetWindowText(sBankAccount);
	m_IdEdt.SetWindowText(sID);
	m_PhoneEdt.SetWindowText(sTel);
	m_BankOwnerEdt.SetWindowText(sBankAccountOwner);
	m_PwEdt.SetWindowText(sPW);
	m_AddressEdt.SetWindowText(sAddress);
	m_MemoEdt.SetWindowText(sEtc);
	m_WorkStateCmb.SetCurSel(m_nWorkState);
	m_WorkTypeCmb.SetCurSel(nWorkType);
	m_WagesTypeCmb.SetCurSel(nWagesType);
	m_WagesBasicEdt.SetWindowText(LF->GetMyNumberFormat(nWagesBasic));
	m_strPW = sPW;

	SetEtcEdit(sWagesAid, sWagesAidCharge);

	if(bApplyInsurance)
		m_ApplyInsuranceChk.SetCheck(TRUE);
	else
		m_NotApplyInsuranceChk.SetCheck(TRUE);

	m_DtFeeEdt.SetWindowText(sDTFee);

	m_KukminInsChk.SetCheck(bKukminIns);
	m_KukminInsEdt.SetWindowText(sKukminInsFee);
	m_UryoInsChk.SetCheck(bUryoIns);
	m_UryoInsEdt.SetWindowText(sUryoInsFee);
	m_SanjaeInsChk.SetCheck(bSanjaeIns);
	m_SanjaeInsEdt.SetWindowText(sSanjaeInsFee);
	m_GoyongInsChk.SetCheck(bGoyongIns);
	m_GoyongInsEdt.SetWindowText(sGoyongInsFee);
	m_GabkunInsChk.SetCheck(bGabkunIns);
	m_GabkunInsEdt.SetWindowText(sGabkunInsFee);
	m_SoducInsChk.SetCheck(bSoducIns);
	m_SoducInsEdt.SetWindowText(sSoducInsFee);
	m_JuminInsChk.SetCheck(bJuminIns);
	m_JuminInsEdt.SetWindowText(sJuminInsFee);
	m_EtcInsEdt.SetWindowText(sEtcIns);
	m_EtcInsFeeEdt.SetWindowText(sEtcInsFee);
	m_InDoorMemo.SetWindowText(sInDoorEtc);
	m_edtAuthPhone.SetWindowText(LF->GetDashPhoneNumber(strAuthPhone));


	if(m_nWorkState != 2) // 퇴사자는 사번 경가능
		m_WNoEdt.EnableWindow(FALSE);

	OnBnClickedApplyInsuranceCheck();
}

void CInDoorDlg::SetEtcEdit(CString sEtc, CString sEtcCharge)
{
	long nStartEtcPos = 0;
	long nDestEtcPos = 0;

	long nStartEtcChargePos = 0;
	long nDestEtcChargePos = 0;

	long nItem = 0;

	while(1)
	{
		nDestEtcPos = sEtc.Find(";", nStartEtcPos);
		nDestEtcChargePos = sEtcCharge.Find(";", nStartEtcChargePos);

		if(nDestEtcPos == -1) break;

		CString sEtcPart = sEtc.Mid(nStartEtcPos, nDestEtcPos - nStartEtcPos);
		CString sEtcChargePart = sEtcCharge.Mid(nStartEtcChargePos, nDestEtcChargePos - nStartEtcChargePos);

		CEdit *pEtcEdt = (CEdit*)GetDlgItem(IDC_WAGES_AID_EDIT1 + nItem);
		CEdit *pEtcChargeEdt = (CEdit*)GetDlgItem(IDC_WAGES_AID_CHARGE_EDIT1 + nItem);

		pEtcEdt->SetWindowText(sEtcPart);
		pEtcChargeEdt->SetWindowText(sEtcChargePart);


		nItem++;

		nStartEtcPos = nDestEtcPos + 1;
		nStartEtcChargePos = nDestEtcChargePos + 1;
	}
}


void CInDoorDlg::OnBnClickedApplyInsuranceCheck()
{
	BOOL bCheck = m_ApplyInsuranceChk.GetCheck();

	m_KukminInsChk.EnableWindow(bCheck);
	m_KukminInsEdt.EnableWindow(bCheck);
	m_UryoInsChk.EnableWindow(bCheck);
	m_UryoInsEdt.EnableWindow(bCheck);
	m_SanjaeInsChk.EnableWindow(bCheck);
	m_SanjaeInsEdt.EnableWindow(bCheck);
	m_GoyongInsChk.EnableWindow(bCheck);
	m_GoyongInsEdt.EnableWindow(bCheck);
	m_GabkunInsChk.EnableWindow(bCheck);
	m_GabkunInsEdt.EnableWindow(bCheck);
	m_SoducInsChk.EnableWindow(bCheck);
	m_SoducInsEdt.EnableWindow(bCheck);
	m_JuminInsChk.EnableWindow(bCheck);
	m_JuminInsEdt.EnableWindow(bCheck);
	m_EtcInsEdt.EnableWindow(bCheck);
	m_EtcInsFeeEdt.EnableWindow(bCheck);

	m_NotApplyInsuranceChk.SetCheck(!bCheck);
	m_DtFeeEdt.EnableWindow(!bCheck);
}

void CInDoorDlg::OnBnClickedNotApplyInsuranceCheck()
{
	BOOL bCheck = m_NotApplyInsuranceChk.GetCheck();

	m_KukminInsChk.EnableWindow(!bCheck);
	m_KukminInsEdt.EnableWindow(!bCheck);
	m_UryoInsChk.EnableWindow(!bCheck);
	m_UryoInsEdt.EnableWindow(!bCheck);
	m_SanjaeInsChk.EnableWindow(!bCheck);
	m_SanjaeInsEdt.EnableWindow(!bCheck);
	m_GoyongInsChk.EnableWindow(!bCheck);
	m_GoyongInsEdt.EnableWindow(!bCheck);
	m_GabkunInsChk.EnableWindow(!bCheck);
	m_GabkunInsEdt.EnableWindow(!bCheck);
	m_SoducInsChk.EnableWindow(!bCheck);
	m_SoducInsEdt.EnableWindow(!bCheck);
	m_JuminInsChk.EnableWindow(!bCheck);
	m_JuminInsEdt.EnableWindow(!bCheck);
	m_EtcInsEdt.EnableWindow(!bCheck);
	m_EtcInsFeeEdt.EnableWindow(!bCheck);

	m_ApplyInsuranceChk.SetCheck(!bCheck);
	m_DtFeeEdt.EnableWindow(bCheck);
}

void CInDoorDlg::OnBnClickedCloseButton()
{
	OnOK();
}

void CInDoorDlg::OnBnClickedButton2()
{
	MessageBox("준비중입니다", "확인", MB_ICONINFORMATION);
}

BOOL CInDoorDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN) 
		{
			if(pMsg->hwnd == m_EnterDT.GetSafeHwnd())
				m_NameEdt.SetFocus();
			else if(pMsg->hwnd == m_NameEdt.GetSafeHwnd())
				m_SSNEdt1.SetFocus();
			else if(pMsg->hwnd == m_SSNEdt1.GetSafeHwnd())
				m_SSNEdt2.SetFocus();
			else if(pMsg->hwnd == m_SSNEdt2.GetSafeHwnd())
				m_WorkPartCmb.SetFocus();
			else if(pMsg->hwnd == m_WorkPartCmb.GetSafeHwnd())
				m_WNoEdt.SetFocus();
			else if(pMsg->hwnd == m_WNoEdt.GetSafeHwnd())
				m_BankNameEdt.SetFocus();
			else if(pMsg->hwnd == m_BankNameEdt.GetSafeHwnd())
				m_PositionEdt.SetFocus();
			else if(pMsg->hwnd == m_PositionEdt.GetSafeHwnd())
				m_MpEdt.SetFocus();
			else if(pMsg->hwnd == m_MpEdt.GetSafeHwnd())
				m_BankAccountEdt.SetFocus();
			else if(pMsg->hwnd == m_BankAccountEdt.GetSafeHwnd())
				m_IdEdt.SetFocus();
			else if(pMsg->hwnd == m_IdEdt.GetSafeHwnd())
				m_PhoneEdt.SetFocus();
			else if(pMsg->hwnd == m_PhoneEdt.GetSafeHwnd())
				m_BankOwnerEdt.SetFocus();
			else if(pMsg->hwnd == m_BankOwnerEdt.GetSafeHwnd())
				m_PwEdt.SetFocus();
			else if(pMsg->hwnd == m_PwEdt.GetSafeHwnd())
				m_AddressEdt.SetFocus();
			else if(pMsg->hwnd == m_AddressEdt.GetSafeHwnd())
				m_MemoEdt.SetFocus();
			else if(pMsg->hwnd == m_MemoEdt.GetSafeHwnd())
				m_WorkStateCmb.SetFocus();
			else if(pMsg->hwnd == m_WorkStateCmb.GetSafeHwnd())
				m_WorkTypeCmb.SetFocus();
			else if(pMsg->hwnd == m_WorkTypeCmb.GetSafeHwnd())
				m_WagesTypeCmb.SetFocus();
			else if(pMsg->hwnd == m_WagesTypeCmb.GetSafeHwnd())
				m_WagesBasicEdt.SetFocus();
			else if(pMsg->hwnd == m_WagesBasicEdt.GetSafeHwnd())
				m_WagesAidEdt1.SetFocus();
			else if(pMsg->hwnd == m_WagesAidEdt1.GetSafeHwnd())
				m_WagesAidChargeEdt1.SetFocus();
			else if(pMsg->hwnd == m_WagesAidChargeEdt1.GetSafeHwnd())
				m_WagesAidEdt2.SetFocus();
			else if(pMsg->hwnd == m_WagesAidEdt2.GetSafeHwnd())
				m_WagesAidChargeEdt2.SetFocus();
			else if(pMsg->hwnd == m_WagesAidChargeEdt2.GetSafeHwnd())
				m_WagesAidEdt3.SetFocus();
			else if(pMsg->hwnd == m_WagesAidEdt3.GetSafeHwnd())
				m_WagesAidChargeEdt3.SetFocus();
			else if(pMsg->hwnd == m_WagesAidChargeEdt3.GetSafeHwnd())
				m_WagesAidEdt4.SetFocus();
			else if(pMsg->hwnd == m_WagesAidEdt4.GetSafeHwnd())
				m_WagesAidChargeEdt4.SetFocus();
			else if(pMsg->hwnd == m_WagesAidChargeEdt4.GetSafeHwnd())
				m_ApplyInsuranceChk.SetFocus();
			else if(pMsg->hwnd == m_ApplyInsuranceChk.GetSafeHwnd())
			{
				m_SaveBtn.SetFocus();
				//m_NotApplyInsuranceChk.SetFocus();
			}
			else if(pMsg->hwnd == m_NotApplyInsuranceChk.GetSafeHwnd())
			{
				m_SaveBtn.SetFocus();
					//m_DtFeeEdt.SetFocus();
			}
			else if(pMsg->hwnd == m_DtFeeEdt.GetSafeHwnd())
				m_KukminInsChk.SetFocus();
			else if(pMsg->hwnd == m_KukminInsChk.GetSafeHwnd())
				m_KukminInsEdt.SetFocus();
			else if(pMsg->hwnd == m_KukminInsEdt.GetSafeHwnd())
				m_UryoInsChk.SetFocus();
			else if(pMsg->hwnd == m_UryoInsChk.GetSafeHwnd())
				m_UryoInsEdt.SetFocus();
			else if(pMsg->hwnd == m_UryoInsEdt.GetSafeHwnd())
				m_SanjaeInsChk.SetFocus();
			else if(pMsg->hwnd == m_SanjaeInsChk.GetSafeHwnd())
				m_SanjaeInsEdt.SetFocus();
			else if(pMsg->hwnd == m_SanjaeInsEdt.GetSafeHwnd())
				m_GoyongInsChk.SetFocus();
			else if(pMsg->hwnd == m_GoyongInsChk.GetSafeHwnd())
				m_GoyongInsEdt.SetFocus();
			else if(pMsg->hwnd == m_GoyongInsEdt.GetSafeHwnd())
				m_GabkunInsChk.SetFocus();
			else if(pMsg->hwnd == m_GabkunInsChk.GetSafeHwnd())
				m_GabkunInsEdt.SetFocus();
			else if(pMsg->hwnd == m_GabkunInsEdt.GetSafeHwnd())
				m_SoducInsChk.SetFocus();
			else if(pMsg->hwnd == m_SoducInsChk.GetSafeHwnd())
				m_SoducInsEdt.SetFocus();
			else if(pMsg->hwnd == m_SoducInsEdt.GetSafeHwnd())
				m_JuminInsChk.SetFocus();
			else if(pMsg->hwnd == m_JuminInsChk.GetSafeHwnd())
				m_JuminInsEdt.SetFocus();
			else if(pMsg->hwnd == m_JuminInsEdt.GetSafeHwnd())
				m_EtcInsEdt.SetFocus();
			else if(pMsg->hwnd == m_EtcInsEdt.GetSafeHwnd())
				m_EtcInsFeeEdt.SetFocus();
			else if(pMsg->hwnd == m_EtcInsFeeEdt.GetSafeHwnd())
				m_InDoorMemo.SetFocus();
			else if(pMsg->hwnd == m_InDoorMemo.GetSafeHwnd())
				m_SaveBtn.SetFocus();
			else if(pMsg->hwnd == m_SaveBtn.GetSafeHwnd())
				OnBnClickedSaveBtn();

			return TRUE;
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CInDoorDlg::OnBnClickedPwEditBtn()
{
	if(m_bNewMode)
	{
		MessageBox("신규 등록후 비밀번호를 수정하세요.", "확인", MB_ICONINFORMATION);
		return;
	}

	CheckChangePw(TRUE);
}

BOOL CInDoorDlg::CheckChangePw(BOOL bEdit)
{
	CPasswordDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		if(dlg.m_strOriPW != m_strPW && m_ui.nRole != 0)
			MessageBox("기존비밀번호가 일치하지 않습니다.", "확인", MB_ICONEXCLAMATION);
		else if(dlg.m_strNewPW1 != dlg.m_strNewPW2)
			MessageBox("신규비밀번호가 서로 다르게 입력되었습니다.", "확인", MB_ICONEXCLAMATION);
		else
		{
			m_PwEdt.SetWindowText(dlg.m_strNewPW1);
			m_strPW = dlg.m_strNewPW1;
			MessageBox("저장버튼을 눌러주세요.", "확인", MB_ICONEXCLAMATION);
			return TRUE;
		}
	}

	return FALSE;
}