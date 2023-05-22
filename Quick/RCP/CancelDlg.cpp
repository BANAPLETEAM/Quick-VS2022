// CancelDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CancelDlg.h"
#include "RiderSmSDlg.h"
#include "PenaltySetDlg.h"
#include "CusSmsDlg.h"

// CCancelDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCancelDlg, CMyDialog)
CCancelDlg::CCancelDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(IDD_CANCEL_DLG, pParent)
	, m_strEtc(_T(""))
{
	m_nCancelType = 0;
	m_bSendCustomer = false;
}

CCancelDlg::~CCancelDlg()
{
}

void CCancelDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Radio(pDX, IDC_RADIO1, m_nCancelType);
	DDX_Text(pDX, IDC_ETC_EDIT, m_strEtc);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);
	DDX_Control(pDX, IDC_SMS_BTN, m_btnSms);
	DDX_Control(pDX, IDC_ALLOCATE_LIMIT_CHECK, m_chkAllocateLimit);
	DDX_Control(pDX, IDC_PENALTY_MIN_EDIT, m_edtPenaltyMin);
	DDX_Control(pDX, IDC_PENALTY_CHARGE_EDIT, m_edtPenaltyFee);
	DDX_Control(pDX, IDC_CANCEL_PENALTY_CHARGE_CHECK, m_chkCancelPenaltyCharge);
	DDX_Text(pDX, IDC_PENALTY_MIN_EDIT, m_strPenaltyMin);
	DDX_Check(pDX, IDC_CANCEL_PENALTY_CHARGE_CHECK, m_bCancelPenaltyCharge);
	DDX_Check(pDX, IDC_ALLOCATE_LIMIT_CHECK, m_bAllocateLimit);
	DDX_Text(pDX, IDC_PENALTY_CHARGE_EDIT, m_strPenaltyCharge);
	DDX_Control(pDX, IDC_RIDER_INFO_STATIC, m_stcRiderInfo);
	
	DDX_Control(pDX, IDC_CUS_CANCEL_TEXT_EDIT, m_edtCusCancelText);
	DDX_Control(pDX, IDC_CUS_CANCEL_CALLBACK_EDIT, m_edtCusCancelCallBack);

	DDX_Control(pDX, IDC_SMS_CUSTOMER_BTN, m_btnSmsCustomer);
	DDX_Control(pDX, IDC_SMS_CUSTOMER_BTN2, m_btnRiderShotageSms);
	DDX_Control(pDX, IDC_RIDER_SHOTAGE_TEXT_EDIT, m_edtRiderShotageText);
	DDX_Control(pDX, IDC_RIDER_SHOTAGE_CALLBACK_EDIT, m_edtRiderShotageCallBack);

	DDX_Control(pDX, IDC_CHANGE_TO_WAIT_CHECK, m_chkChangeToWait);
	DDX_Check(pDX, IDC_CHANGE_TO_WAIT_CHECK, m_bChangeToWait);

	
	CMyDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCancelDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_EN_CHANGE(IDC_ETC_EDIT, OnEnChangeEtcEdit)
	ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO10, OnBnClickedRadio10)
	ON_BN_CLICKED(IDC_RADIO11, OnBnClickedRadio11)
	ON_BN_CLICKED(IDC_RADIO12, OnBnClickedRadio12)
	ON_BN_CLICKED(IDC_RADIO9, OnBnClickedRadio9)
	ON_BN_CLICKED(IDC_MENT_BTN, OnBnClickedMentBtn)	
	ON_BN_CLICKED(IDC_MENT_BTN2, OnBnClickedMentBtn2)
	ON_BN_CLICKED(IDC_SMS_CUSTOMER_BTN, OnBnClickedSmsCustomerBtn)
	ON_BN_CLICKED(IDC_SMS_CUSTOMER_BTN2, OnBnClickedSmsCustomerBtn2)
END_MESSAGE_MAP()


// CCancelDlg 메시지 처리기입니다.


void CCancelDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	if(m_nCancelType == 12) 
	{
		MessageBox("취소사유를 필히 선택하시기 바랍니다.", "확인", MB_ICONINFORMATION);
		return;
	}
	

	if(m_btnSmsCustomer.GetCheck())
	{
		CString strOfficePhone, strText, strEtc;
		m_edtCusCancelCallBack.GetWindowText(strOfficePhone);
		m_edtCusCancelText.GetWindowText(strText);

		if(m_strCustomerPhone.Left(1) == "0" && strText.GetLength() > 0)
		{ 			
			SendSmsNew(m_nCompany, 777, m_strCustomerPhone, strOfficePhone, strText, "접수프로그램(취소)", "", ""); 
		}
	}
	if(m_btnRiderShotageSms.GetCheck())
	{
		CString strOfficePhone, strText, strEtc;
		m_edtRiderShotageCallBack.GetWindowText(strOfficePhone);
		m_edtRiderShotageText.GetWindowText(strText);

		if(m_strCustomerPhone.Left(1) == "0" && strText.GetLength() > 0)
		{
			SendSmsNew(m_nCompany, 777, m_strCustomerPhone, strOfficePhone, strText, "접수프로그램(취소)", "", "");
		}
	}
	if(m_btnSms.GetCheck())
	{
		long nOrderCompany = 0;

		CMkCommand pCmd(m_pMkDb, "select_order_cancel_sms_info2");
		CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), (int)0);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nTNo);
		CMkParameter *parStart = pCmd.AddParameter(typeString, typeOutput, 100, CString(""));
		CMkParameter *parDest = pCmd.AddParameter(typeString, typeOutput, 100, CString(""));
		CMkParameter *parRiderPhone = pCmd.AddParameter(typeString, typeOutput, 50, CString(""));
		CMkParameter *parOrderCompany = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
		
		if(pCmd.Execute())
		{
			CString strStart, strDest, strPhone;
			parStart->GetValue(strStart);
			parDest->GetValue(strDest);
			parRiderPhone->GetValue(strPhone);
			parOrderCompany->GetValue(nOrderCompany);

			strPhone.Remove('-');

			if(parRet->GetLong() < 11) {
				MessageBox("배차 상태가 아니기 때문에, SMS전송을 하실 수 없습니다."\
							"전송체크를 하지마시기 바랍니다.", 
							"확인", MB_ICONINFORMATION);
				return;
			}

			if(strPhone.IsEmpty() || strPhone.Left(2) != "01") 
			{
				MessageBox("기사 전화번호가 존재하지 않거나, 휴대폰 번호가 아닙니다.", 
							"확인", MB_ICONINFORMATION);
				return;
			}

			CString strCancel;

			if(m_nCancelType >= 11)
			{
				if(m_strEtc.GetLength() > 0)			
					strCancel = "[취소:" + m_strEtc + "]";
				else 
					strCancel = "[취소:기타]";

				m_nCancelType = 11;
			}
			else 
			{
				strCancel = m_psaCancel->GetAt(m_nCancelType);
			}

			CString strOfficePhone = "";
			strOfficePhone = m_ci.GetPhone(nOrderCompany, TRUE);
			if(strOfficePhone.GetLength() <= 0)
			{
				strOfficePhone = m_ci.GetPhone(nOrderCompany);
				if(strOfficePhone.GetLength() <= 0)
					strOfficePhone = m_ci.m_strOfficePhone;
			}
		
			CRiderSMSDlg dlg;
			dlg.m_nCompany = m_nOrderCompany;
			dlg.m_strRiderPN = strPhone;
			dlg.m_strMsg.Format("[콜취소] %s->%s (사유:%s)", 
					strStart, strDest, strCancel);

			if(IDOK == dlg.DoModal())
			{
				dlg.m_strRecvPhone = GetNoneDashNumber(dlg.m_strRecvPhone);
				dlg.m_strRiderPN = GetNoneDashNumber(dlg.m_strRiderPN);

				SendSmsNew(m_nCompany, 777, dlg.m_strRiderPN, dlg.m_strRecvPhone, dlg.m_strMsg, "접수프로그램(취소)", "", "");				

				OnOK();
				return;
			}
		}
		return;
	}
	OnOK();
}

void CCancelDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}

void CCancelDlg::OnEnChangeEtcEdit()
{
	UpdateData(TRUE);
	m_nCancelType = 11;
	UpdateData(FALSE);
}


BOOL CCancelDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CButton *pRadio1 = (CButton*)GetDlgItem(IDC_RADIO1);
	CButton *pRadio13 = (CButton*)GetDlgItem(IDC_RADIO13);
	pRadio1->SetCheck(FALSE);
	pRadio13->SetCheck(TRUE);
	m_nCancelType = 12;

	m_chkAllocateLimit.SetCheck(TRUE);
	m_chkCancelPenaltyCharge.SetCheck(TRUE);



/*
	char buffer[10];
	MakePenaltyMin();
	m_edtPenaltyMin.SetWindowText(ltoa(m_nPenaltyMin[0], buffer, 10));

	if(atol(m_strPenaltyCharge) > 0)
		m_chkAllocateLimit.EnableWindow(FALSE);
	else
		m_chkCancelPenaltyCharge.EnableWindow(FALSE);
*/

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

/*
void CCancelDlg::MakePenaltyMin()
{
	for(int j = 0; j < MAX_CANCEL_COUNT; j++)
	{
		for(int i = 0; i < MAX_CANCEL_TYPE; i++)
		{
			m_nPenaltyMin[j][i] = atol(CANCEL_DEFAULT_TIME);
			m_nPenaltyFee[j][i] = 0;
		}
	}

	CMkCommand pCmd(m_pMkDb, "select_driver_cancel_settime2");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);	
	CMkRecordset pRs(m_pMkDb);
	pRs.Execute(&pCmd);

	int nCount = 0;
	char buffer[30];
	int nCancelType;
	int nPreCancelType = -1;

	if(pRs.GetRecordCount() > 0)
	{
		while(!pRs.IsEOF()) {

			long nCompany;
			int	nReleaseMin[5];
			int nForfeit[5];
			pRs.GetFieldValue("nCompany", nCompany);
			pRs.GetFieldValue("nCancelCount", nCancelType);
			pRs.GetFieldValue("nReleaseMin", nReleaseMin[0]);
			pRs.GetFieldValue("nReleaseMin2", nReleaseMin[1]);
			pRs.GetFieldValue("nReleaseMin3", nReleaseMin[2]);
			pRs.GetFieldValue("nReleaseMin4", nReleaseMin[3]);
			pRs.GetFieldValue("nReleaseMin5", nReleaseMin[4]);

			pRs.GetFieldValue("nForfeit",  nForfeit[0]);
			pRs.GetFieldValue("nForfeit2", nForfeit[1]);
			pRs.GetFieldValue("nForfeit3", nForfeit[2]);
			pRs.GetFieldValue("nForfeit4", nForfeit[3]);
			pRs.GetFieldValue("nForfeit5", nForfeit[4]);

			for(int i = 0; i < MAX_CANCEL_COUNT; i++) {
				m_nPenaltyMin[i][nCancelType] = nReleaseMin[i];
				m_nPenaltyFee[i][nCancelType] = nForfeit[i];
			}

			pRs.MoveNext();
		}
	}

	pRs.Close();
}
*/

/*
void CCancelDlg::MakeRiderCancelCount()
{
	CMkCommand pCmd(m_pMkDb, "select_rider_cancel_count");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nTNo);	
	CMkRecordset pRs(m_pMkDb);
	pRs.Execute(&pCmd);

	int nCount = 0;
	char buffer[30];
	int nCancelType;
	int nPreCancelType = -1;

	if(pRs.GetRecordCount() > 0)
	{
		while(!pRs.IsEOF()) {

			long nCompany;
			int	nReleaseMin[5];
			int nForfeit[5];
			pRs.GetFieldValue("nCompany", nCompany);
			pRs.GetFieldValue("nCancelCount", nCancelType);
			pRs.GetFieldValue("nReleaseMin", nReleaseMin[0]);
			pRs.GetFieldValue("nReleaseMin2", nReleaseMin[1]);
			pRs.GetFieldValue("nReleaseMin3", nReleaseMin[2]);
			pRs.GetFieldValue("nReleaseMin4", nReleaseMin[3]);
			pRs.GetFieldValue("nReleaseMin5", nReleaseMin[4]);

			pRs.GetFieldValue("nForfeit",  nForfeit[0]);
			pRs.GetFieldValue("nForfeit2", nForfeit[1]);
			pRs.GetFieldValue("nForfeit3", nForfeit[2]);
			pRs.GetFieldValue("nForfeit4", nForfeit[3]);
			pRs.GetFieldValue("nForfeit5", nForfeit[4]);

			for(int i = 0; i < MAX_CANCEL_COUNT; i++) {
				m_nPenaltyMin[i][nCancelType] = nReleaseMin[i];
				m_nPenaltyFee[i][nCancelType] = nForfeit[i];
			}

			pRs.MoveNext();
		}
	}
	
}
*/

void CCancelDlg::OnBnClickedRadio1()
{
	SetPenalty(1);
}

void CCancelDlg::OnBnClickedRadio2()
{
	SetPenalty(2);
}

void CCancelDlg::OnBnClickedRadio3()
{
	SetPenalty(3);
}

void CCancelDlg::OnBnClickedRadio4()
{
	SetPenalty(4);
}

void CCancelDlg::OnBnClickedRadio5()
{
	SetPenalty(5);
}

void CCancelDlg::OnBnClickedRadio6()
{
	SetPenalty(6);
}

void CCancelDlg::OnBnClickedRadio7()
{
	SetPenalty(7);
}

void CCancelDlg::OnBnClickedRadio8()
{
	SetPenalty(8);

	CButton *pBtn = (CButton*)GetDlgItem(IDC_RADIO8);
	if(pBtn->GetCheck())
		GetCusSMSInfo();
}

void CCancelDlg::OnBnClickedRadio9()
{
	SetPenalty(12);		//기타
}

void CCancelDlg::OnBnClickedRadio10()
{
	SetPenalty(9);
}

void CCancelDlg::OnBnClickedRadio11()
{
	SetPenalty(10);
}

void CCancelDlg::OnBnClickedRadio12()
{
	SetPenalty(11);
}

void CCancelDlg::SetPenalty(int nID)
{
	CString strText;
	char buffer[10];
	long nCompany, nRNo, nPenaltyMin, nPenaltyFee, nCount;
	CMkCommand pCmd(m_pMkDb, "select_rider_cancel_penalty");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nTNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nID - 1);
	CMkParameter *parCompany = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parRNo = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parPenaltyMin = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parPenaltyFee = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parCount = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

	if(!pCmd.Execute()) return;

    parCompany->GetValue(nCompany);
	parRNo->GetValue(nRNo);
	parPenaltyMin->GetValue(nPenaltyMin);
	parPenaltyFee->GetValue(nPenaltyFee);
	parCount->GetValue(nCount);

	m_edtPenaltyMin.SetWindowText(ltoa(nPenaltyMin, buffer, 10));
	m_edtPenaltyFee.SetWindowText(ltoa(nPenaltyFee, buffer, 10));
	strText.Format("%s소속, %d번 기사님, 해당사유 %d회차", 
			m_ci.GetName(nCompany),
			nRNo, nCount);
	m_stcRiderInfo.SetWindowText(strText);

	CRect rc;
	m_stcRiderInfo.GetWindowRect(rc);
	ScreenToClient(rc);

	InvalidateRect(rc);
}


void CCancelDlg::OnBnClickedMentBtn()
{
	CCusSmsDlg dlg;
	dlg.m_nCompany = m_nOrderCompany;
	if(IDOK == dlg.DoModal())
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "update_cus_cancel_sms_ment");

		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nOrderCompany);
		pCmd.AddParameter(typeString, typeInput, dlg.m_strPhone.GetLength(), dlg.m_strPhone);
		pCmd.AddParameter(typeString, typeInput, dlg.m_strText.GetLength(), dlg.m_strText);

        if(!pRs.Execute(&pCmd))
		{
			MessageBox("수정실패", "확인", MB_ICONERROR);
			return;
		}

		CButton *pBtn = (CButton*)GetDlgItem(IDC_RADIO8);
		if(pBtn->GetCheck())
			GetCusSMSInfo();
	}
}

void CCancelDlg::OnBnClickedMentBtn2()
{
	CCusSmsDlg dlg;
	dlg.m_nCompany = m_nOrderCompany;
	dlg.m_nRiderShotage = TRUE;
	if(IDOK == dlg.DoModal())
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "update_rider_shotage_sms_ment");

		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nOrderCompany);
		pCmd.AddParameter(typeString, typeInput, dlg.m_strPhone.GetLength(), dlg.m_strPhone);
		pCmd.AddParameter(typeString, typeInput, dlg.m_strText.GetLength(), dlg.m_strText);

		if(!pRs.Execute(&pCmd))
		{
			MessageBox("수정실패", "확인", MB_ICONERROR);
			return;
		}

		CButton *pBtn = (CButton*)GetDlgItem(IDC_RADIO8);
		if(pBtn->GetCheck())
			GetCusSMSInfo();
	}
}


void CCancelDlg::GetCusSMSInfo()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_cus_cancel_sms_ment2");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nOrderCompany);

	if(pRs.Execute(&pCmd))
	{
		CString strPhone, strText,sRiderShotageSMS,sRiderShotageCallBack;

		if(!pRs.IsEOF())
		{
			pRs.GetFieldValue("sCusCancelSMS", strText);
			pRs.GetFieldValue("sCusCancelCallBack", strPhone);
			pRs.GetFieldValue("sRiderShotageSMS", sRiderShotageSMS);
			pRs.GetFieldValue("sRiderShotageCallBack", sRiderShotageCallBack);

		}

		m_edtCusCancelText.SetWindowText(strText);
		m_edtCusCancelCallBack.SetWindowText(strPhone);
		m_edtRiderShotageText.SetWindowText(sRiderShotageSMS);
		m_edtRiderShotageCallBack.SetWindowText(sRiderShotageCallBack);
	}
}






void CCancelDlg::OnBnClickedSmsCustomerBtn()
{
	//CButton *pBtn = (CButton*)GetDlgItem(IDC_RADIO8);
	
	if( m_btnSmsCustomer.GetCheck())
		m_btnRiderShotageSms.SetCheck(FALSE);
	


}

void CCancelDlg::OnBnClickedSmsCustomerBtn2()
{
	if(m_btnRiderShotageSms.GetCheck())
		m_btnSmsCustomer.SetCheck(FALSE);
}		
