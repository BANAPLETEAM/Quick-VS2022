// HolidayDeliveryInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "quick.h"
#include "HolidayDeliveryInfoDlg.h"
#include "LogiUtil.h"
#include "json.h"
BOOL CHolidayDeliveryInfoDlg::m_bHolidayCompany = FALSE;


// CHolidayDeliveryInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CHolidayDeliveryInfoDlg, CMyDialog)

CHolidayDeliveryInfoDlg::CHolidayDeliveryInfoDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CHolidayDeliveryInfoDlg::IDD, pParent)
{

}

CHolidayDeliveryInfoDlg::~CHolidayDeliveryInfoDlg()
{
	//	delete m_pPOINew;
	//	m_pPOINew = NULL;
}

void CHolidayDeliveryInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER, m_explorer);
}

BEGIN_MESSAGE_MAP(CHolidayDeliveryInfoDlg, CMyDialog)	
END_MESSAGE_MAP()


// CHolidayDeliveryInfoDlg 메시지 처리기입니다.

BOOL CHolidayDeliveryInfoDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	InitData();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CHolidayDeliveryInfoDlg::InitData()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_holiday_address");
	cmd.AddParameter(m_ui.nCompany);

	if(!rs.Execute(&cmd))
		return;

	m_strURL = "http://work.logisoft.co.kr:8000/address";

	if(rs.GetRecordCount() == 0)
	{		
		m_explorer.Navigate(m_strURL, NULL, NULL, NULL, NULL);
		return;
	}

	CString strBasicAddress; 
	CString strDetailAddress;
	CString strReceive; 
	CString strPhone1; 
	CString strPhone2; 
	CString strEtc; 
	long nAddressType;


	rs.GetFieldValue("sBasicAddress", strBasicAddress);
	rs.GetFieldValue("sDetailAddress", strDetailAddress);
	rs.GetFieldValue("sReceive", strReceive);
	rs.GetFieldValue("sPhone1", strPhone1);
	rs.GetFieldValue("sPhone2", strPhone2);
	rs.GetFieldValue("sEtc", strEtc);
	rs.GetFieldValue("nAddressType", nAddressType);

	m_strURL += "?basicAddress=" + strBasicAddress;
	m_strURL += "&detailAddress=" + strDetailAddress;
	m_strURL += "&receive=" + strReceive;
	m_strURL += "&phone1=" + strPhone1;
	m_strURL += "&phone2=" + strPhone2;
	m_strURL += "&addressType=" + LF->GetStringFromLong(nAddressType, TRUE);
	m_strURL += "&etc=" + strEtc;

	m_explorer.Navigate(m_strURL, NULL, NULL, NULL, NULL);
}

BOOL CHolidayDeliveryInfoDlg::IsHolidayCompany(BOOL bIgnoreInsert)
{ 	 
	BOOL bInsert; 	 

	COleDateTime dtCur = COleDateTime::GetCurrentTime();

	if(dtCur > COleDateTime(2023, 1, 9, 14, 0, 0)) 
		return FALSE;

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_holiday_company", 0, TRUE);
	cmd.AddParameter(m_ui.nCompany);
	CMkParameter *parHolidayCompany = cmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parInsert = cmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

	if(!rs.Execute(&cmd)) 
		return FALSE;

	parHolidayCompany->GetValue(m_bHolidayCompany);
	parInsert->GetValue(bInsert);

	if(m_bHolidayCompany && (!bInsert || bIgnoreInsert))
		return TRUE;

	return FALSE;
}

BEGIN_EVENTSINK_MAP(CHolidayDeliveryInfoDlg, CMyDialog)
	ON_EVENT(CHolidayDeliveryInfoDlg, IDC_EXPLORER, 250, CHolidayDeliveryInfoDlg::BeforeNavigate2Explorer, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
END_EVENTSINK_MAP()


void CHolidayDeliveryInfoDlg::BeforeNavigate2Explorer(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel)
{
	CString strURL(URL->bstrVal);
	CString strJson(strURL.Right(strURL.GetLength()-6));
	strJson.Replace("%20", " ");

	//최초 실행시 URL이 리턴되는데, URL이면 skip한다.
	if(strURL == m_strURL)
		*Cancel = FALSE;
	else
	{
		strJson.Replace("<element event='TestEvent'>", "");
		strJson.Replace("</element>", "");

		if(strJson == "1"){
			OnOK();
			return;
		}

		Json::Value root;
		Json::Reader reader;

		if (reader.parse(std::string(strJson), root)) {
			CString strBasicAddress = root["strBasicAddress"].asCString();
			CString strDetailAddress = root["strDetailAddress"].asCString();
			CString strReceive = root["strReceive"].asCString();
			CString strPhone1 = root["strPhone1"].asCString();
			CString strPhone2 = root["strPhone2"].asCString();
			CString strEtc = root["strEtc"].asCString();
			long nAddressType = root["nAddressType"].asInt();

			CMkCommand cmd(m_pMkDb, "insert_holiday_address_1");
			cmd.AddParameter(m_ui.nCompany);
			cmd.AddParameter(m_ui.nWNo);
			cmd.AddParameter(strBasicAddress);
			cmd.AddParameter(strDetailAddress);
			cmd.AddParameter(strReceive);
			cmd.AddParameter(strPhone1);
			cmd.AddParameter(strPhone2);
			cmd.AddParameter(strEtc);
			cmd.AddParameter(nAddressType);
			cmd.AddParameter(0);
			cmd.AddParameter(0);
			cmd.AddParameter(0);
			cmd.AddParameter(0);

			if(cmd.Execute()) {
				MessageBox("성공적으로 저장되었습니다.\r\n감사합니다", "확인", MB_ICONINFORMATION);
				OnOK();
			}	
		}

		*Cancel = TRUE;
	}
}


BOOL CHolidayDeliveryInfoDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->wParam == VK_RETURN)
		return FALSE;

	return CMyDialog::PreTranslateMessage(pMsg);
}
