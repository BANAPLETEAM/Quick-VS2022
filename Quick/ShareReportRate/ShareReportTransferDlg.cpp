// ShareReportTransferDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareReportTransferDlg.h"

#include "ShareReportAuthPhoneDlg.h"
#include "ShareTranferRequestDlg.h"
#include "ShareReportRateDlg1.h"


// CShareReportTransferDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CShareReportTransferDlg, CMyDialog)
CShareReportTransferDlg::CShareReportTransferDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CShareReportTransferDlg::IDD, pParent)
{
	m_nAbilityMoney = 0;
    m_nSMSID = 0;	
	m_pShareTransferRequestDlg = NULL;
	m_sMoneyR = "";
	m_sMemoR = "";
}

CShareReportTransferDlg::~CShareReportTransferDlg()
{
	m_pShareTransferRequestDlg = NULL;
}

void CShareReportTransferDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEND_MONEY_STC, m_SendMoneyStc);
	DDX_Control(pDX, IDC_SEND_MONEY_EDIT, m_SendMoneyEdt);
	DDX_Control(pDX, IDC_MEMO_EDT, m_MemoEdt);
	DDX_Control(pDX, IDC_SMS_NUMBER_EDIT, m_SmsNumberEdt);
	DDX_Control(pDX, IDC_ABILITY_MONEY_EDIT, m_AbilityMoneyEdt);
	DDX_Control(pDX, DC_COMPANY_NAME_EDIT, m_CompanyNameEdt);
}


BEGIN_MESSAGE_MAP(CShareReportTransferDlg, CMyDialog)
	ON_BN_CLICKED(IDC_AUTH_BTN, OnBnClickedAuthBtn)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_EN_CHANGE(IDC_SEND_MONEY_EDIT, OnEnChangeSendMoneyEdit)
END_MESSAGE_MAP()


// CShareReportTransferDlg 메시지 처리기입니다.



BOOL CShareReportTransferDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_SendMoneyEdt.SetLimitText(6);

	CString str;
	str.Format("%d", m_nAbilityMoney);

	m_AbilityMoneyEdt.SetWindowText(str);
	m_CompanyNameEdt.SetWindowText(m_ci.GetName(m_nToCompany));

	m_SendMoneyEdt.SetWindowText(m_sMoneyR);
	m_MemoEdt.SetWindowText(m_sMemoR);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CShareReportTransferDlg::OnBnClickedAuthBtn()
{
	CShareReportAuthPhoneDlg pDlg;
	pDlg.m_pShareReportTransferDlg = this;
	pDlg.DoModal();
}
void CShareReportTransferDlg::OnBnClickedOk()
{
	UpdateData(true);

	CString strAbilityMoney, strSendMoney;

	m_AbilityMoneyEdt.GetWindowText(strAbilityMoney);
	m_SendMoneyEdt.GetWindowText(strSendMoney);

	strAbilityMoney.Replace("원",",");

	if(_ttoi(strSendMoney) > _ttoi(strAbilityMoney))
	{
		MessageBox("이체 가능 금액보다 많이 보낼수 없습니다.", "확인", MB_ICONERROR);
		return;
	}

	if(_ttoi(strSendMoney) > 300000)
	{
		MessageBox("삼십만원 이상 보낼 수 없습니다", "확인", MB_ICONERROR);
		return;
	} 
	
	if(_ttoi(strSendMoney) < 0)
	{
		MessageBox("0원 이하는 보낼 수 없습니다", "확인", MB_ICONERROR);
		return;
	} 	

	if(m_nSMSID == 0)
	{
		MessageBox("이체 승인 요청버튼을 눌려 승인을 받으세요", "확인", MB_ICONERROR);
		return;
	}
	
	CString sSendCharege, sMemo, sSMSNumber;
	int nReturn;

	m_SendMoneyEdt.GetWindowText(sSendCharege);

	m_MemoEdt.GetWindowText(sMemo);
	m_SmsNumberEdt.GetWindowText(sSMSNumber);

	if(sMemo.GetLength() > 100)
	{
		MessageBox("이체 내용은 100자 이하로 해주세요.", "확인", MB_ICONERROR);
		return;
	}


	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_share_report_transfer");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nSMSID);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeString, typeInput, m_ui.strID.GetLength(), m_ui.strID);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), atoi(sSendCharege));
	pCmd.AddParameter(typeString, typeInput, sMemo.GetLength(), sMemo);
	pCmd.AddParameter(typeString, typeInput, sSMSNumber.GetLength(), sSMSNumber);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nToCompany);
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(!pRs.Execute(&pCmd)) return;

	pPar->GetValue(nReturn);
	if(nReturn == 111)
	{
		if(m_pShareTransferRequestDlg != NULL) //이체 요청에의헤 호출되었을경우
		{
			m_pShareTransferRequestDlg->FinishRequest(_ttoi(sSendCharege), sMemo);
		}

		MessageBox("성공적으로 이체되었습니다", "확인" ,MB_ICONINFORMATION);
	}
	else if(nReturn == 222)
		MessageBox("3분이 초과되었습니다", "확인" ,MB_ICONERROR);
	else if(nReturn == 333)
		MessageBox("인증번호가 틀립니다", "확인" ,MB_ICONERROR);
	else if(nReturn == 444)
		MessageBox("이미 전송되었습니다", "확인" ,MB_ICONINFORMATION);

	//111성공 222 3분초과 333인증번호 틀림
	
	//m_pShareReportRateDlg1->RefreshList();

	OnOK();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}

void CShareReportTransferDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}

CString CShareReportTransferDlg::ReturnMoneyString(CString sMoney)
{
	CString strReturn;
	CString sNumber[10] = {"영", "일", "이", "삼", "사", "오", "육", "칠", "팔", "구"};
	CString sUnit[6] = {"영", "십", "백","천", "만", "십"};

	int nLen = sMoney.GetLength();

	if(nLen == 0)
		return "";


	for(int i=0; i<nLen; i++)
	{
		if(sMoney.Mid(i, 1) == "0")
			continue;
		else
			strReturn = strReturn + sNumber[_ttoi(sMoney.Mid(i, 1))] + sUnit[nLen-i-1];
	}
	strReturn.Replace("영","");
	strReturn += "원";

	if(nLen == 6)
	{
		//	MessageBox(strReturn);
		if(sMoney.Mid(1,1) == "0")
		{
			CString str;
			strReturn.Replace("십", "십만");

			if(strReturn.GetLength() == 8)
				return strReturn;

			strReturn.Replace("십만원", "십원");
			//MessageBox(strReturn, "확인", MB_ICONINFORMATION);

			return strReturn;
		}
	}


	return strReturn;

}


void CShareReportTransferDlg::OnEnChangeSendMoneyEdit()
{
	UpdateData(true);

	CString sMoney;
	m_SendMoneyEdt.GetWindowText(sMoney);
	m_SendMoneyStc.SetWindowText(ReturnMoneyString(sMoney));
	// TODO:  RICHEDIT 컨트롤인 경우 이 컨트롤은
	// CMyDialog::마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여
	// CRichEditCtrl().SetEventMask()를 호출하도록 OnInitDialog() 함수를 재지정하지 않으면
	// 이 알림을 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



