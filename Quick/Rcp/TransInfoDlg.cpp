// TransInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "TransInfoDlg.h"
#include ".\transinfodlg.h"


// CTransInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTransInfoDlg, CMyDialog)
CTransInfoDlg::CTransInfoDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CTransInfoDlg::IDD, pParent)
{
	m_dtRegister = COleDateTime::GetCurrentTime();
	m_dtDeparture = COleDateTime::GetCurrentTime();
	m_dtArrival = COleDateTime::GetCurrentTime();

	m_sStart = "";
	m_sDest = "";
	m_sExpressName = "";
	m_sExpressNumber = "";
	m_sItemNo = "";
	m_sName = "";
	m_sEtc = "";

	m_nTNo = -1;
}

CTransInfoDlg::~CTransInfoDlg()
{
}

void CTransInfoDlg::DoDataExchange(CDataExchange* pDX)
{

	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REGISTER_DATE_DTP, m_RegisterDateDtp);
	DDX_Control(pDX, IDC_REGISTER_TIME_DTP, m_RegisterTimeDtp);
	DDX_Control(pDX, IDC_START_EDT, m_StartEdt);

	DDX_Control(pDX, IDC_DEST_EDT, m_DestEdt);
	DDX_Control(pDX, IDC_EXPRESS_NAME_EDT, m_ExpressNameEdt);
	DDX_Control(pDX, IDC_EXPRESS_NUMBER_EDT, m_ExpressNumberEdt);
	DDX_Control(pDX, IDC_ARRIVAL_DATE_DTP, m_ArrivalDateDtp);
	DDX_Control(pDX, IDC_ARRIVAL_TIME_DTP, m_ArrivalTimeDtp);
	DDX_Control(pDX, IDC_DEPARTURE_DATE_DTP, m_DepartureDateDtp);
	DDX_Control(pDX, IDC_DEPARTURE_TIME_DTP, m_DepartureTimeDtp);
	DDX_Control(pDX, IDC_ITEM_NO_EDT, m_ItemNoEdt);
	DDX_Control(pDX, IDC_NAME_EDT, m_NameEdt);
	DDX_Control(pDX, IDC_ETC_EDT, m_EtcEdt);
	DDX_Control(pDX, IDC_UPDATE_BTN, m_UpdateBtn);
	DDX_Control(pDX, IDC_CANCEL_BTN, m_ColseBtn);
	DDX_Control(pDX, IDC_STATIC1, m_Stc1);
	DDX_Control(pDX, IDC_STATIC2, m_Stc2);
	DDX_Control(pDX, IDC_STATIC3, m_Stc3);
	DDX_Control(pDX, IDC_STATIC4, m_Stc4);
	DDX_Control(pDX, IDC_STATIC5, m_Stc5);
	DDX_Control(pDX, IDC_STATIC6, m_Stc6);
	DDX_Control(pDX, IDC_STATIC7, m_Stc7);
	DDX_Control(pDX, IDC_STATIC8, m_Stc8);
	DDX_Control(pDX, IDC_STATIC9, m_Stc9);
	DDX_Control(pDX, IDC_STATIC10, m_Stc10);
}


BEGIN_MESSAGE_MAP(CTransInfoDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_UPDATE_BTN, OnBnClickedUpdateBtn)
END_MESSAGE_MAP()


// CTransInfoDlg 메시지 처리기입니다.

BOOL CTransInfoDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	this->SetWindowText(m_sTitle);

	m_StartEdt.SetWindowText(m_sStart);
	m_DestEdt.SetWindowText(m_sDest);
	m_ExpressNameEdt.SetWindowText(m_sExpressName);
	m_ExpressNumberEdt.SetWindowText(m_sExpressNumber);
	m_ItemNoEdt.SetWindowText(m_sItemNo);
	m_NameEdt.SetWindowText(m_sName);
	m_EtcEdt.SetWindowText(m_sEtc);

	m_RegisterDateDtp.SetTime(m_dtRegister);
	m_RegisterTimeDtp.SetTime(m_dtRegister);
	m_DepartureDateDtp.SetTime(m_dtDeparture);
	m_DepartureTimeDtp.SetTime(m_dtDeparture);
	m_ArrivalDateDtp.SetTime(m_dtArrival);
	m_ArrivalTimeDtp.SetTime(m_dtArrival);	

	if(m_bNew)
	{
		m_UpdateBtn.SetWindowText("등 록");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTransInfoDlg::Clear()
{
	m_sStart = "";
	m_sDest = "";
	m_sExpressName = "";
	m_sExpressNumber = "";
	m_sItemNo = "";
	m_sName = "";
	m_sEtc = "";

	m_nTNo = -1;

	m_StartEdt.SetWindowText("");
	m_DestEdt.SetWindowText("");
	m_ExpressNameEdt.SetWindowText("");
	m_ExpressNumberEdt.SetWindowText("");
	m_ItemNoEdt.SetWindowText("");
	m_NameEdt.SetWindowText("");
	m_EtcEdt.SetWindowText("");

	COleDateTime dt(COleDateTime::GetCurrentTime());

	m_RegisterDateDtp.SetTime(dt);
	m_RegisterTimeDtp.SetTime(dt);
	m_DepartureDateDtp.SetTime(dt);
	m_DepartureTimeDtp.SetTime(dt);
	m_ArrivalDateDtp.SetTime(dt);
	m_ArrivalTimeDtp.SetTime(dt);	

	if(m_bNew)
	{
		m_UpdateBtn.SetWindowText("등 록");
	}
	else
		m_UpdateBtn.SetWindowText("수 정");


}
void CTransInfoDlg::SetData()
{
	

	m_StartEdt.SetWindowText(m_sStart);
	m_DestEdt.SetWindowText(m_sDest);
	m_ExpressNameEdt.SetWindowText(m_sExpressName);
	m_ExpressNumberEdt.SetWindowText(m_sExpressNumber);
	m_ItemNoEdt.SetWindowText(m_sItemNo);
	m_NameEdt.SetWindowText(m_sName);
	m_EtcEdt.SetWindowText(m_sEtc);

	m_RegisterDateDtp.SetTime(m_dtRegister);
	m_RegisterTimeDtp.SetTime(m_dtRegister);
	m_DepartureDateDtp.SetTime(m_dtDeparture);
	m_DepartureTimeDtp.SetTime(m_dtDeparture);
	m_ArrivalDateDtp.SetTime(m_dtArrival);
	m_ArrivalTimeDtp.SetTime(m_dtArrival);	

	SetWindowText(m_sTitle);
	

}
void CTransInfoDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CTransInfoDlg::OnBnClickedUpdateBtn()
{
	CString sStart;
	CString sDest;
	CString sExpressName;
	CString sExpressNumber;
	CString sItemNo;
	CString sName;
	CString sEtc;

	long nReturn = 0;

	m_StartEdt.GetWindowText(sStart);
	m_DestEdt.GetWindowText(sDest);
	m_ExpressNameEdt.GetWindowText(sExpressName);
	m_ExpressNumberEdt.GetWindowText(sExpressNumber);
	m_ItemNoEdt.GetWindowText(sItemNo);
	m_EtcEdt.GetWindowText(sEtc);

	COleDateTime dtDepartDate; m_DepartureDateDtp.GetTime(dtDepartDate);
	COleDateTime dtDepartTime; m_DepartureTimeDtp.GetTime(dtDepartTime);
	COleDateTime dtArrivalDate; m_ArrivalDateDtp.GetTime(dtArrivalDate);
	COleDateTime dtArrivalTime; m_ArrivalTimeDtp.GetTime(dtArrivalTime);


	COleDateTime dtDeparture(dtDepartDate.GetYear(), dtDepartDate.GetMonth(), dtDepartDate.GetDay(),
						dtDepartTime.GetHour(),	dtDepartTime.GetMinute(), dtDepartTime.GetSecond());

	COleDateTime dtArrival(dtArrivalDate.GetYear(), dtArrivalDate.GetMonth(), dtArrivalDate.GetDay(),
						dtArrivalTime.GetHour(), dtArrivalTime.GetMinute(), dtArrivalTime.GetSecond());
	
	if(m_bNew)
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "insert_transinfo");

		CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, 0);

		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nTNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
		pCmd.AddParameter(typeDate,typeInput, sizeof(COleDateTime), dtDeparture);
		pCmd.AddParameter(typeDate,typeInput, sizeof(COleDateTime), dtArrival);
		pCmd.AddParameter(typeString, typeInput, sStart.GetLength(), sStart);
		pCmd.AddParameter(typeString, typeInput, sDest.GetLength(), sDest);
		pCmd.AddParameter(typeString, typeInput, sExpressName.GetLength(), sExpressName);
		pCmd.AddParameter(typeString, typeInput, sExpressNumber.GetLength(), sExpressNumber);
		pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
		pCmd.AddParameter(typeString, typeInput, sItemNo.GetLength(), sItemNo);
		pCmd.AddParameter(typeString, typeInput, sEtc.GetLength(), sEtc);

		if(!pRs.Execute(&pCmd)) return;

		pPar->GetValue(m_nReturn);				

		OnOK();
	}
	else
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "update_transinfo");

		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nTNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
		pCmd.AddParameter(typeDate,typeInput, sizeof(COleDateTime), dtDeparture);
		pCmd.AddParameter(typeDate,typeInput, sizeof(COleDateTime), dtArrival);
		pCmd.AddParameter(typeString, typeInput, sStart.GetLength(), sStart);
		pCmd.AddParameter(typeString, typeInput, sDest.GetLength(), sDest);
		pCmd.AddParameter(typeString, typeInput, sExpressName.GetLength(), sExpressName);
		pCmd.AddParameter(typeString, typeInput, sExpressNumber.GetLength(), sExpressNumber);
		pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), sName);
		pCmd.AddParameter(typeString, typeInput, sItemNo.GetLength(), sItemNo);
		pCmd.AddParameter(typeString, typeInput, sEtc.GetLength(), sEtc);
 
		if(!pRs.Execute(&pCmd)) return;

		OnOK();
	}
}



CString CTransInfoDlg::GetStart()
{

	CString strStart = "";
	m_StartEdt.GetWindowText(strStart);
	return strStart;

}
BOOL CTransInfoDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN)
		{
			if(::GetDlgCtrlID(pMsg->hwnd) == IDC_START_EDT)
			{
				m_DestEdt.SetFocus();
				return TRUE;
			}
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_DEST_EDT)
			{
				m_ExpressNameEdt.SetFocus();
				return TRUE;
			}
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_EXPRESS_NAME_EDT)
			{
				m_ExpressNumberEdt.SetFocus();
				return TRUE;
			}
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_EXPRESS_NUMBER_EDT)
			{
				m_ItemNoEdt.SetFocus();
				return TRUE;
			}
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_ITEM_NO_EDT)
			{
				m_EtcEdt.SetFocus();
				return TRUE;
			}
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_ETC_EDT)
			{
				m_UpdateBtn.SetFocus();
				return TRUE;
			}
			else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_UPDATE_BTN)
			{
				OnBnClickedUpdateBtn();
				return TRUE;
			}
			else 
				return TRUE;
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}
