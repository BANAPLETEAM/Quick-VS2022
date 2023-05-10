// ShareReportWantTransferDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareReportWantTransferDlg.h"

#include "ShareReportAuthPhoneDlg.h"


// CShareReportWantTransferDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CShareReportWantTransferDlg, CMyDialog)
CShareReportWantTransferDlg::CShareReportWantTransferDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CShareReportWantTransferDlg::IDD, pParent)
{
	m_nToCompany = 0;
	m_nSMSID = 0;
}

CShareReportWantTransferDlg::~CShareReportWantTransferDlg()
{
}

void CShareReportWantTransferDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEND_MONEY_EDIT, m_SendMoneyEdt);
	DDX_Control(pDX, IDC_MEMO_EDIT, m_MemoEdt);
	DDX_Control(pDX, IDC_SEND_MONEY_STC, m_SendMoneyStc);
	DDX_Control(pDX, IDC_COMPANY_NAME_EDIT, m_CompanyNameEdt);
}

BEGIN_MESSAGE_MAP(CShareReportWantTransferDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_EN_CHANGE(IDC_SEND_MONEY_EDIT, OnEnChangeSendMoneyEdit)
END_MESSAGE_MAP()


// CShareReportWantTransferDlg 메시지 처리기입니다.

void CShareReportWantTransferDlg::OnBnClickedOk()
{
	UpdateData(true);

	CString strAbilityMoney, strSendMoney;

	m_SendMoneyEdt.GetWindowText(strSendMoney);


	if(_ttoi(strSendMoney) > 300000)
	{
		MessageBox("삼십만원 이상 요청 할 수 없습니다", "확인", MB_ICONERROR);
		return;
	}

	CString sSendCharege, sMemo;
	

	m_SendMoneyEdt.GetWindowText(sSendCharege);

	m_MemoEdt.GetWindowText(sMemo);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_share_report_want_transfer");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeString, typeInput, m_ui.strID.GetLength(), m_ui.strID);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), _ttoi(sSendCharege));
	pCmd.AddParameter(typeString, typeInput, sMemo.GetLength(), sMemo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nToCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), 0); // 기사에게 선입금 충전 할건지 말건지
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), 0); // 충전할경우 nTNo
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(!pRs.Execute(&pCmd)) return;

	MessageBox("성공적으로 요청되었습니다", "확인" ,MB_ICONINFORMATION);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}

void CShareReportWantTransferDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}



void CShareReportWantTransferDlg::OnEnChangeSendMoneyEdit()
{
	CString sMoney;
	m_SendMoneyEdt.GetWindowText(sMoney);
	m_SendMoneyStc.SetWindowText(ReturnMoneyString(sMoney));
	// TODO:  RICHEDIT 컨트롤인 경우 이 컨트롤은
	// CMyDialog::마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여
	// CRichEditCtrl().SetEventMask()를 호출하도록 OnInitDialog() 함수를 재지정하지 않으면
	// 이 알림을 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


CString CShareReportWantTransferDlg::ReturnMoneyString(CString sMoney)
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
BOOL CShareReportWantTransferDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_SendMoneyEdt.SetLimitText(6);
	m_CompanyNameEdt.SetWindowText(m_ci.GetName(m_nToCompany));

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
