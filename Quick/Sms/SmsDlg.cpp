// SmsDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SmsDlg.h"

#define PAGE_SIZE	80


// CSmsDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSmsDlg, CMyDialog)
CSmsDlg::CSmsDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSmsDlg::IDD, pParent)
{
	m_bOrderNum = TRUE;
	m_bCName = TRUE;
	m_bTotal = TRUE;
	m_bDis = TRUE;
	m_bPickup = FALSE;
	m_bPickupPhone = TRUE;
	m_bEtc = FALSE;
	m_bDT = TRUE;
	m_strDDD = "";

	m_ASI = NULL;
	m_bSendPDA = FALSE;
}

CSmsDlg::~CSmsDlg()
{
}

void CSmsDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_EDIT, m_edtMsg);
	DDX_Control(pDX, IDC_ONEPAGE_CHECK, m_chkOnePage);
	DDX_Control(pDX, IDC_SEND_BTN, m_btnSend);
	DDX_Control(pDX, IDC_INFO_STATIC, m_stcInfo);
	DDX_Control(pDX, IDC_ORDERNUM_CHECK, m_chkOrderNum);
	DDX_Control(pDX, IDC_CNAME_CHECK, m_chkCName);
	DDX_Control(pDX, IDC_TOTAL_CHECK, m_chkTotal);
	DDX_Control(pDX, IDC_DIS_CHECK, m_chkDis);
	DDX_Control(pDX, IDC_PICKUP_CHECK, m_chkPickup);
	DDX_Control(pDX, IDC_PICKUP_PHONE_CHECK, m_chkPickupPhone);
	DDX_Control(pDX, IDC_ETC_CHECK, m_chkEtc);
	DDX_Control(pDX, IDC_ONEPAGE_CHECK, m_chkOnePage);
	DDX_Control(pDX, IDC_SEND_BTN, m_btnSend);
	DDX_Control(pDX, IDC_INFO_STATIC2, m_stcInfo2);
	DDX_Control(pDX, IDC_INFO_STATIC3, m_stcInfo3);
	DDX_Control(pDX, IDC_INFO_STATIC4, m_stcInfo4);
	DDX_Control(pDX, IDC_INFO_STATIC5, m_stcInfo5);
	DDX_Control(pDX, IDC_INFO_STATIC6, m_stcInfo6);

	DDX_Check(pDX, IDC_ORDERNUM_CHECK, m_bOrderNum);
	DDX_Check(pDX, IDC_CNAME_CHECK, m_bCName);
	DDX_Check(pDX, IDC_TOTAL_CHECK, m_bTotal);
	DDX_Check(pDX, IDC_DIS_CHECK, m_bDis);
	DDX_Check(pDX, IDC_PICKUP_CHECK, m_bPickup);
	DDX_Check(pDX, IDC_PICKUP_PHONE_CHECK, m_bPickupPhone);
	DDX_Check(pDX, IDC_ETC_CHECK, m_bEtc);
	DDX_Check(pDX, IDC_DT_CHECK, m_bDT);
	DDX_Control(pDX, IDC_COMBO1, m_cmbSendType);
	DDX_Control(pDX, IDC_START_CHECK, m_chkStart);
	DDX_Control(pDX, IDC_DEST_CHECK, m_chkDest);

	DDX_Control(pDX, IDC_FIRST_STATIC, m_stcFirst);
	DDX_Control(pDX, IDC_SECOND_STATIC, m_stcSecond);
	DDX_Control(pDX, IDC_THIRD_STATIC, m_stcThird);
	DDX_Control(pDX, IDC_FIRST_PAGE_COMBO, m_cmbFirstPage);
	DDX_Control(pDX, IDC_SECOND_PAGE_COMBO, m_cmbSecondPage);
	DDX_Control(pDX, IDC_THIRD_PAGE_COMBO, m_cmbThirdPage);
}


BEGIN_MESSAGE_MAP(CSmsDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SEND_BTN, OnBnClickedSendBtn)
	ON_EN_CHANGE(IDC_MSG_EDIT, OnEnChangeMsgEdit)

	ON_BN_CLICKED(IDC_ORDERNUM_CHECK, OnBnClickedOrdernumCheck)
	ON_BN_CLICKED(IDC_CNAME_CHECK, OnBnClickedOrdernumCheck)
	ON_BN_CLICKED(IDC_TOTAL_CHECK, OnBnClickedOrdernumCheck)
	ON_BN_CLICKED(IDC_DIS_CHECK, OnBnClickedOrdernumCheck)
	ON_BN_CLICKED(IDC_PICKUP_CHECK, OnBnClickedOrdernumCheck)
	ON_BN_CLICKED(IDC_PICKUP_PHONE_CHECK, OnBnClickedOrdernumCheck)


	ON_BN_CLICKED(IDC_ETC_CHECK, OnBnClickedOrdernumCheck)	
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)	
	ON_BN_CLICKED(IDC_START_CHECK, OnBnClickedStartCheck)
	ON_BN_CLICKED(IDC_DEST_CHECK, OnBnClickedDestCheck)
	ON_CBN_SELCHANGE(IDC_FIRST_PAGE_COMBO, OnCbnSelchangeFirstPageCombo)
	ON_CBN_SELCHANGE(IDC_SECOND_PAGE_COMBO, OnCbnSelchangeSecondPageCombo)
	ON_CBN_SELCHANGE(IDC_THIRD_PAGE_COMBO, OnCbnSelchangeThirdPageCombo)
END_MESSAGE_MAP()


// CSmsDlg 메시지 처리기입니다.


BOOL CSmsDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	if(m_bSendPDA)
	{
		this->SetWindowText("PDA 배차공지 전송 (*주의: 이미 배차된 상태임, 과금안됨)");
		m_stcInfo6.SetWindowText("PDA로 전송됨");

		CEdit *pEdit = (CEdit*)GetDlgItem(IDC_SEND_BTN);
		pEdit->SetWindowText("PDA 발 송(&S)");
	}

	m_cmbSendType.SetCurSel(m_ci.m_nAllocateSMSType);

	m_chkOnePage.SetCheck(m_ci.m_bSendOnePage);
	
	m_chkEtc.SetCheck(1);
	m_chkStart.SetCheck(1);
	m_chkDest.SetCheck(0);
	m_chkDest.EnableWindow(0);

	long nOCNo, nSCNo, nDCNo;
	CString strBranchName, strRiderName;

	CMkCommand pCmd(m_pMkDb, "select_dorder_for_sms7");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nTNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRCompany);

    if(!pRs.Execute(&pCmd)) return FALSE;
	if(pRs.GetRecordCount() > 0) {

		m_AllocateSMSFSettingDlg.FillMap(&pRs);
		m_ASI = new ST_ALLOCATE_SMS;

		pRs.GetFieldValue("F11", m_ASI->strOName);
		pRs.GetFieldValue("F12", m_ASI->strOPhone);
		pRs.GetFieldValue("F13", m_ASI->strOMobile);
		pRs.GetFieldValue("F14", m_ASI->strODepart);
		pRs.GetFieldValue("F15", m_ASI->strOManager);
		pRs.GetFieldValue("F16", m_ASI->strODong);
		pRs.GetFieldValue("F17", m_ASI->strODetail);
		pRs.GetFieldValue("F18", m_ASI->strOMemo);

		pRs.GetFieldValue("F21", m_ASI->strSName);
		pRs.GetFieldValue("F22", m_ASI->strSPhone);
		pRs.GetFieldValue("F23", m_ASI->strSMobile);
		pRs.GetFieldValue("F24", m_ASI->strSDepart);
		pRs.GetFieldValue("F25", m_ASI->strSManager);
		pRs.GetFieldValue("F26", m_ASI->strSDong);
		pRs.GetFieldValue("F27", m_ASI->strSDetail);

		pRs.GetFieldValue("F31", m_ASI->strDName);
		pRs.GetFieldValue("F32", m_ASI->strDPhone);
		pRs.GetFieldValue("F33", m_ASI->strDMobile);
		pRs.GetFieldValue("F34", m_ASI->strDDepart);
		pRs.GetFieldValue("F35", m_ASI->strDManager);
		pRs.GetFieldValue("F36", m_ASI->strDDong);
		pRs.GetFieldValue("F37", m_ASI->strDDetail);

		pRs.GetFieldValue("F41", m_ASI->strDt1);
		pRs.GetFieldValue("F42", m_ASI->strEtc);
		pRs.GetFieldValue("F43", m_ASI->strItemType);
		pRs.GetFieldValue("F44", m_ASI->strIntercallEtc);
		pRs.GetFieldValue("F45", m_ASI->strPayType);
		pRs.GetFieldValue("F46", m_ASI->strCarType);
		pRs.GetFieldValue("F47", m_ASI->strWayType);
		pRs.GetFieldValue("F48", m_ASI->strRunType);
		pRs.GetFieldValue("F49", m_ASI->strChargeSum);
		pRs.GetFieldValue("F50", m_ASI->strChargeSum4);
		pRs.GetFieldValue("F51", m_ASI->strChargeSum3);
		pRs.GetFieldValue("F52", m_ASI->strChargeTrans);
		pRs.GetFieldValue("F53", m_ASI->strChargeTrans4);
		pRs.GetFieldValue("F54", m_ASI->strChargeTrans3);

		pRs.GetFieldValue("sDDD", m_strDDD);
		pRs.GetFieldValue("sBranchName", strBranchName);
		pRs.GetFieldValue("sRiderName", strRiderName);
		pRs.GetFieldValue("nNumOrder", m_nNumOrder);
		pRs.GetFieldValue("nRemainCount", m_nRemainCount);
		pRs.GetFieldValue("sRiderPhone", m_strRiderPhone);

		pRs.GetFieldValue("nOCNo", nOCNo);
		pRs.GetFieldValue("nSCNo", nSCNo);
		pRs.GetFieldValue("nDCNo", nDCNo);

		MakeCallBackPhone();
				
		if(m_strRiderPhone.GetLength() < 1) {
			CString strMsg;
			strMsg = "해당기사를 찾을 수 없거나, 휴대폰번호가 설정되어 있지 않습니다.";
			MessageBox(strMsg);
			pRs.Close();
 			OnCancel();
			return TRUE;
		}
		CString strInfoStatic2,strInfoStatic3,strInfoStatic4,strInfoStatic5;
		strInfoStatic2.Format("지사명: %s", strBranchName);
		strInfoStatic3.Format("기사명: %s", strRiderName);
		strInfoStatic4.Format("전화번호: %s",LF->GetDashPhoneNumber(m_strRiderPhone));
		strInfoStatic5.Format("사번: %d",m_nRNo);
		
		m_stcInfo2.SetWindowText(strInfoStatic2);			
		m_stcInfo3.SetWindowText(strInfoStatic3);			
		m_stcInfo4.SetWindowText(strInfoStatic4);			
		m_stcInfo5.SetWindowText(strInfoStatic5);			
		m_edtMsg.SetWindowText(MakeMsg());
		
		pRs.Close();

		CString sTitle;
		this->GetWindowText(sTitle);

		if(nOCNo == nSCNo)
			sTitle += " [의뢰지 = 출발지]";
		else if(nOCNo == nDCNo)
			sTitle += " [의뢰지 = 도착지]";

		this->SetWindowText(sTitle);

	}

	m_cmbFirstPage.SetCurSel(m_ci.m_nFirstPage);
	m_cmbSecondPage.SetCurSel(m_ci.m_nSecondPage);
	m_cmbThirdPage.SetCurSel(m_ci.m_nThirdPage);

	OnCbnSelchangeCombo1();
	//OnEnChangeMsgEdit();
	SetStatic();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

CString CSmsDlg::GetManager(long nPage)
{
	if(nPage == 0)
		return "출발지 담당자";
	if(nPage == 1)
		return "도착지 담당자";
	if(nPage == 2)
		return "의뢰지 담당자";

	return "";
}

void CSmsDlg::SetStatic()
{
	CString strStc;
	strStc.Format("에게 전화가 갑니다.  [%s]", m_strTel[0]);
	m_stcFirst.SetWindowText(strStc);
	strStc.Format("에게 전화가 갑니다.  [%s]", m_strTel[1]);
	m_stcSecond.SetWindowText(strStc);
	strStc.Format("에게 전화가 갑니다.  [%s]", m_strTel[2]);
	m_stcThird.SetWindowText(strStc);	
}

CString CSmsDlg::MsgMake(ST_ALLOCATE_SMS *m_ASI)
{
	return "";
}

void CSmsDlg::OnEnChangeMsgEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우 이 컨트롤은
	// CMyDialog::마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여
	// CRichEditCtrl().SetEventMask()를 호출하도록 OnInitDialog() 함수를 재지정하지 않으면
	// 이 알림을 보내지 않습니다.

	CString strMsg, strInfo, strHead, strTemp,sSendType;
	int nLen;
	m_edtMsg.GetWindowText(strMsg);
	
	strHead.Format("[%d]", m_nNumOrder); 
	nLen = strHead.GetAllocLength();
	nLen += strMsg.GetAllocLength();

	if(nLen / PAGE_SIZE > 0) {
		nLen += 1+ strHead.GetAllocLength() + 1;
		if(nLen / PAGE_SIZE > 1) {
			nLen += strHead.GetAllocLength() + 1;
			if(nLen / PAGE_SIZE > 2) {
				nLen += strHead.GetAllocLength() + 1;
				if(nLen / PAGE_SIZE > 3) {
					nLen += strHead.GetAllocLength() + 1;
				}
			}
		}
	}
  
	strTemp.Format("%d자(영문기준)/총%d페이지", nLen, nLen / 80 + 1);
	m_stcInfo.SetWindowText(strTemp);
}

void CSmsDlg::RefreshDisplay()
{
}

void CSmsDlg::SendPda(CStringArray &saMsg)
{
	CString str;

	for(int i=0; i<saMsg.GetSize(); i++)
	{
		str += saMsg.GetAt(i);
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "edit_rider_msg4");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), 0);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nRCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nRNo);
	pCmd.AddParameter(typeString, typeInput, str.GetLength(), str);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nCompany);

	if(!pCmd.Execute()) return;
}

void CSmsDlg::OnBnClickedSendBtn()
{
	CStringArray saMsg;
	CString strMsg, strHead, strPage;
	int nCount = 0;
	int nLen;
	int nCursor = 0;

	m_edtMsg.GetWindowText(strMsg);
	nLen = strMsg.GetLength();

	strHead.Format("[%d]", m_nNumOrder);
	if(strHead.GetLength() + nLen > PAGE_SIZE) {
		if(m_chkOnePage.GetCheck()) {
			//strHead.Format("[%d]", m_nNumOrder); 한페이지 전송
			nCursor = PAGE_SIZE - strHead.GetAllocLength();
			//strPage = strHead + strMsg.Mid(0, nCursor);
			strPage = strMsg.Mid(0, nCursor);
			if(LF->IsBrokenHangul(strPage)) {
				strPage = strPage.Left(PAGE_SIZE - 1);
				nCursor--;
			}
			saMsg.Add(strPage);
		}
		else {
			//일단 한페이지 만들고 
			strHead.Format("[%dA]", m_nNumOrder);
			nCursor = PAGE_SIZE - strHead.GetLength();

			if(m_ci.m_nCompanyCode == 2660) //퀵맨에서 앞에 붙는 번호가 빠지길 원함.
				strPage = strMsg.Mid(0, nCursor);
			else
				strPage = strHead + strMsg.Mid(0, nCursor);

			if(LF->IsBrokenHangul(strPage)) {
				strPage = strPage.Left(PAGE_SIZE - 1);
				nCursor--;
			}
			saMsg.Add(strPage);

			//두번째 페이지 생성
			if(nLen - nCursor - strHead.GetLength() > PAGE_SIZE)
			{
				strHead.Format("[%dB]", m_nNumOrder);

				if(m_ci.m_nCompanyCode == 2660)
					strPage = strMsg.Mid(nCursor, PAGE_SIZE - strHead.GetLength());
				else
					strPage = strHead + strMsg.Mid(nCursor, PAGE_SIZE - strHead.GetLength());

				nCursor += PAGE_SIZE - strHead.GetLength(); 
				if(LF->IsBrokenHangul(strPage)) {
					strPage = strPage.Left(PAGE_SIZE - 1);
					nCursor--;
				}
				saMsg.Add(strPage);

				if(nLen - nCursor - strHead.GetLength() > PAGE_SIZE)
				{
					strHead.Format("[%dC]", m_nNumOrder);

					if(m_ci.m_nCompanyCode == 2660)
						strPage = strMsg.Mid(nCursor, PAGE_SIZE - strHead.GetLength());
					else
						strPage = strHead + strMsg.Mid(nCursor, PAGE_SIZE - strHead.GetLength());

					if(LF->IsBrokenHangul(strPage)) {
						strPage = strPage.Left(PAGE_SIZE - 1);
						nCursor--;
					}
					saMsg.Add(strPage);
					MessageBox("동시에 최대 3페이지까지만 전송됩니다.", "확인", MB_ICONINFORMATION);
				}
				else {
					strHead.Format("[%dC]", m_nNumOrder);
					strPage = strHead + strMsg.Mid(nCursor, nLen - nCursor);
					saMsg.Add(strPage);
				}
			}
			else 
			{
				strHead.Format("[%dB]", m_nNumOrder);
				strPage = strHead + strMsg.Mid(nCursor, nLen - nCursor);
				saMsg.Add(strPage);
			}
		}
	}
	else {	//총길이가 80자 이하인 경우
		strPage.Format("%s", strMsg);
		//strPage.Format("[%d]%s", m_nNumOrder, strMsg);

		saMsg.Add(strPage);
	}

	if(m_bSendPDA)
	{
		SendPda(saMsg);
		OnOK();
		return;
	}

	CString strCustomer = "";
	for(int i = 0; i < saMsg.GetCount(); i++)
	{		 
        if(!LF->SendSmsNew(m_nRCompany, m_nTNo, m_strRiderPhone, m_strTel[i], saMsg.GetAt(i), "배차(접수프로그램)", "", "", FALSE)) return;
	}
	
	OnOK();
}

CString CSmsDlg::SearchFindTelNumber(CString str)
{
	CString strTemp,strTel;
	strTemp = strTel = "";
	int nTelNum = 0;
	

	str.Replace("-","");
	str.Replace("(","");
	str.Replace(")","");
	for(int i =0; i < str.GetLength(); i++)
	{			
		strTemp = str.Mid(i,1);
		if(str.Mid(i,1) == "0")
		{
			nTelNum ++;
			strTel += strTemp;
		}
		else
		{			
			int nResult = atoi(strTemp);
			if( 9 >= nResult && nResult >= 1 )
			{
				nTelNum ++;
				strTel += strTemp;		
			}
			else
			{
				if(	nTelNum > 6 && 11 >= nTelNum)
				{
					if(nTelNum > 8  && strTel.Mid(0,1) == "0" )
						return 	strTel;				
					else
					{
						if( (nTelNum == 7 || nTelNum == 8) && strTel.Mid(0,1) != "0")
								return 	strTel;				

					}
				}
				nTelNum = 0;
				strTel = "";
			}
		}
		
	}

	if(	nTelNum > 6 && 11 >= nTelNum)
	{
		if(nTelNum > 8  && strTel.Mid(0,1) == "0" )
			return 	strTel;				
		else
		{
			if( (nTelNum == 7 || nTelNum == 8) && strTel.Mid(0,1) != "0")
					return 	strTel;				

		}
	}
	return "FAIL";

}


void CSmsDlg::OnCbnSelchangeCombo1()
{

	if(m_cmbSendType.GetCurSel() == 0)
	{
		m_chkDest.SetCheck(0);
		m_chkDest.EnableWindow(0);
		m_chkStart.EnableWindow(0);
	}
	else if((m_cmbSendType.GetCurSel() == 1) || (m_cmbSendType.GetCurSel() == 2))
	{		
		m_chkDest.SetCheck(1);
		m_chkDest.EnableWindow(1);
		m_chkStart.EnableWindow(1);
	}
	else
	{
		m_chkStart.SetCheck(0);
		m_chkStart.EnableWindow(0);
		m_chkDest.SetCheck(0);
		m_chkDest.EnableWindow(0);
	}

	m_edtMsg.SetWindowText("");	
	//m_edtMsg.SetWindowText(MsgMake(m_ASI));
	m_edtMsg.SetWindowText(MakeMsg());
	OnEnChangeMsgEdit();
}


void CSmsDlg::OnBnClickedOrdernumCheck()
{
	if(m_chkEtc.GetCheck())
		m_chkEtc.SetCheck(1);
	else
		m_chkEtc.SetCheck(0);
	
	m_edtMsg.SetWindowText("");
	m_edtMsg.SetWindowText(MakeMsg());
	OnEnChangeMsgEdit();
}


void CSmsDlg::OnBnClickedStartCheck()
{
	if(m_chkStart.GetCheck())
		m_chkStart.SetCheck(1);
	else
		m_chkStart.SetCheck(0);
	
	m_edtMsg.SetWindowText("");
	m_edtMsg.SetWindowText(MakeMsg());
	OnEnChangeMsgEdit();
}

void CSmsDlg::OnBnClickedDestCheck()
{
	if(m_chkDest.GetCheck())
		m_chkDest.SetCheck(1);
	else
		m_chkDest.SetCheck(0);
	m_edtMsg.SetWindowText("");
	m_edtMsg.SetWindowText(MakeMsg());
	OnEnChangeMsgEdit();
}

BOOL CSmsDlg::DestroyWindow()
{
	if(m_ASI != NULL)
		delete m_ASI;
	
	m_ASI= NULL;

	return CMyDialog::DestroyWindow();
}

void CSmsDlg::MakeCallBackPhone()
{
	//0 출발지, 1 도착지, 2 의뢰지
	if(m_cmbFirstPage.GetCurSel() == 0)
		m_strTel[0] = GetRealNumber(m_ASI->strSMobile, m_ASI->strSPhone);
	else if(m_cmbFirstPage.GetCurSel() == 1)
		m_strTel[0] = GetRealNumber(m_ASI->strDMobile, m_ASI->strDPhone);
	else if(m_cmbFirstPage.GetCurSel() == 2)
		m_strTel[0] = GetRealNumber(m_ASI->strOMobile, m_ASI->strOPhone);
	else
		m_strTel[0] = GetRealNumber(m_ASI->strSMobile, m_ASI->strSPhone);

	if(m_cmbSecondPage.GetCurSel() == 0)
		m_strTel[1] = GetRealNumber(m_ASI->strSMobile, m_ASI->strSPhone);
	else if(m_cmbSecondPage.GetCurSel() == 1)
		m_strTel[1] = GetRealNumber(m_ASI->strDMobile, m_ASI->strDPhone);
	else if(m_cmbSecondPage.GetCurSel() == 2)
		m_strTel[1] = GetRealNumber(m_ASI->strOMobile, m_ASI->strOPhone);
	else
		m_strTel[1] = GetRealNumber(m_ASI->strDMobile, m_ASI->strDPhone);

	if(m_cmbThirdPage.GetCurSel() == 0)
		m_strTel[2] = GetRealNumber(m_ASI->strSMobile, m_ASI->strSPhone);
	else if(m_cmbThirdPage.GetCurSel() == 1)
		m_strTel[2] = GetRealNumber(m_ASI->strDMobile, m_ASI->strDPhone);
	else if(m_cmbThirdPage.GetCurSel() == 2)
		m_strTel[2] = GetRealNumber(m_ASI->strOMobile, m_ASI->strOPhone);
	else
		m_strTel[2] = GetRealNumber(m_ASI->strOMobile, m_ASI->strOPhone);

	SetStatic();

	/*
	if(!sSMobile.IsEmpty())
		m_ASI->sTel[0] = sSMobile;

	CString strCustomer;
	if(m_ASI->sTel[0].GetLength() < 7)
	{
		strCustomer = SearchFindTelNumber(m_ASI->sEtc);
		if(strCustomer != "FAIL")
		{
			if(strCustomer.Left(1) != "0")
				strCustomer = m_sDDD + strCustomer;

			m_strTel[0] = strCustomer;
		}
	}
	else
		m_strTel[0] = m_ASI->sTel[0];
	*/
}

CString CSmsDlg::GetRealNumber(CString strMobile, CString strPhone)
{
	if((strMobile.GetLength() > 0) && 
		(LF->IsNumeric(LF->GetNoneDashNumber(strMobile)) == TRUE))
	{
		if(strMobile.GetLength() >= 10)
		{
            return LF->GetNoneDashNumber(strMobile);
		}
		else if(strMobile.GetLength() >= 6)
			return m_ci.m_strDDD + strMobile;
	}

	if((strPhone.GetLength() > 0) && 
		(LF->IsNumeric(LF->GetNoneDashNumber(strPhone)) == TRUE))
	{
		if(strPhone.GetLength() >= 10)
		{
			return LF->GetNoneDashNumber(strPhone);
		}
		else
			return m_ci.m_strDDD + strPhone;
	}

	return "";
}

CString CSmsDlg::MakeMsg()
{
	long nSel = m_cmbSendType.GetCurSel();

	if(nSel == 0)
		return GetAType();
	if(nSel == 1)
		return GetBType();
	if(nSel == 2)
		return GetCType();
	if(nSel == 3)
		return GetDType();
	if(nSel == 4)
		return GetEType();
	if(nSel == 5)
		return GetFType();

	return "";
}

CString CSmsDlg::GetAType()
{
	CString strMsg = "";

	strMsg = "출";
	strMsg += "[" + m_ASI->strDt1 + "]";
	strMsg += m_ASI->strSDong + "→" + m_ASI->strDDong + ","; 
	strMsg += m_ASI->strChargeSum + ",";
	strMsg += m_ASI->strPayType.Left(2) + ",";
	strMsg += m_ASI->strWayType.Left(2) + ",";
	strMsg += "『" + m_ASI->strOName + ",";

	if(m_ASI->strSDepart.GetLength() > 0)
		strMsg += m_ASI->strSDepart + ",";

	if(m_ASI->strSManager.GetLength() > 0)
		strMsg += m_ASI->strSManager + ",";

	if(m_chkStart.GetCheck())
	{
		if(m_ASI->strSDetail.GetLength() > 0)
			strMsg += m_ASI->strSDetail + ",";
	}
		
	if(m_chkEtc.GetCheck())
	{
		if(m_ASI->strEtc.GetLength() >= 1)
			strMsg += m_ASI->strEtc;
	}	
	strMsg += "』";

	return strMsg;
}

CString CSmsDlg::GetBType()
{
	CString strMsg = "";
	CString strAType = GetAType();
	strMsg += "도" + strAType.Mid(2, strAType.GetLength() - 2);

	strMsg += "【";

	if((m_ASI->strDPhone.GetLength() > 0) && (m_ASI->strDMobile.GetLength() > 0))
	{
		if(LF->IsNumeric(LF->GetNoneDashNumber(m_ASI->strDMobile)) == TRUE)
			strMsg += "☎" + LF->GetDashPhoneNumber(m_ASI->strDMobile) + ",";
		else if(LF->IsNumeric(LF->GetNoneDashNumber(m_ASI->strDPhone)) == TRUE)
			strMsg += "☎" + LF->GetDashPhoneNumber(m_ASI->strDPhone) + ",";
	}

	if(m_ASI->strOName.GetLength() > 0)
		strMsg += m_ASI->strOName + ",";

	if(m_ASI->strODepart.GetLength() > 0)
		strMsg += m_ASI->strODepart + ",";

	if(m_ASI->strDManager.GetLength() > 0)
		strMsg += m_ASI->strDManager + ",";

	if(m_chkDest.GetCheck())
	{
		if(m_ASI->strDDetail.GetLength() > 0)
			strMsg += m_ASI->strDDetail;
	}
	
	strMsg += "】";

	return strMsg;
}

CString CSmsDlg::GetCType()
{
	CString strMsg = ""; 
	CString strBType = GetBType();
	strMsg += "의" + strBType.Mid(2, strBType.GetLength() - 2);
	strMsg += "「";

	if((m_ASI->strOPhone.GetLength() > 0) && (m_ASI->strOMobile.GetLength() > 0))
	{
		if(LF->IsNumeric(LF->GetNoneDashNumber(m_ASI->strOMobile)) == TRUE)
			strMsg += "☏" + LF->GetDashPhoneNumber(m_ASI->strOMobile) + ",";
		else if(LF->IsNumeric(LF->GetNoneDashNumber(m_ASI->strOPhone)) == TRUE)
			strMsg += "☏" + LF->GetDashPhoneNumber(m_ASI->strOPhone) + ",";
	}

	if(m_ASI->strOName.GetLength() > 0)
		strMsg += m_ASI->strOName + ",";
	if(m_ASI->strODepart.GetLength() > 0)
		strMsg += m_ASI->strODepart + ",";
	if(m_ASI->strOManager.GetLength() > 0)
		strMsg += m_ASI->strOManager;			
	strMsg += + "」";
	
	return strMsg;
}

CString CSmsDlg::GetDType()
{
	CString	strMsg = "";
	strMsg += "【"; 
	strMsg +=	(m_ASI->strSDetail == "" ? m_ASI->strSDong : m_ASI->strSDetail);
	strMsg += " -> ";
	strMsg += (m_ASI->strDDetail == "" ? m_ASI->strDDong: m_ASI->strDDetail);
	strMsg += + "】";

	strMsg += m_ASI->strChargeSum + ",";
	strMsg += m_ASI->strPayType.Left(2) + ",";

	strMsg += m_ASI->strWayType.Left(2) + "『";
	strMsg += m_ASI->strSName + ",";

	if(m_ASI->strSDepart.GetLength() > 0)
		strMsg += m_ASI->strSDepart + ",";

	if(m_ASI->strSManager.GetLength() > 0)
		strMsg += m_ASI->strSManager + ",";

	if(m_chkEtc.GetCheck())
	{
		if(m_ASI->strEtc.GetLength() >= 1)
			strMsg += m_ASI->strEtc;
	}

	strMsg += "』";

	if(m_ASI->strDMobile.Left(2) == "01")
		strMsg += "[도:" + m_ASI->strDMobile + "]";
	else if(m_ASI->strDPhone.Left(2) == "01")
		strMsg += "[도:" + m_ASI->strDPhone + "]";

	return strMsg;
}

CString CSmsDlg::GetEType()
{
	CString strMsg = "";
	strMsg += m_ASI->strSDong.Left(4);
	strMsg += "-";
	strMsg +=	m_ASI->strDDong.Left(4);
	strMsg += "/";

	if(m_ASI->strPayType.Left(2) == "외")
		strMsg += m_ASI->strChargeSum + "/"; 
	else
		strMsg += m_ASI->strChargeSum.Left(2) + "/";

	strMsg += m_ASI->strPayType.Left(2) + "/";
	strMsg += m_ASI->strOName.Left(10) + "/";

	strMsg += m_ASI->strEtc + "/";
	strMsg += m_ASI->strSDetail;

	return strMsg;

}

CString CSmsDlg::GetFType()
{
	return m_AllocateSMSFSettingDlg.GetReplaceChar((CStringW)m_ci.m_strAllocateSMSF);
}
void CSmsDlg::OnCbnSelchangeFirstPageCombo()
{
	MakeCallBackPhone();
}

void CSmsDlg::OnCbnSelchangeSecondPageCombo()
{
	MakeCallBackPhone();
}

void CSmsDlg::OnCbnSelchangeThirdPageCombo()
{
	MakeCallBackPhone();
}
