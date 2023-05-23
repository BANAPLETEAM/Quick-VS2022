// LogonDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "LogonDlg.h"
#include "MainFrm.h"
#include "NewCertifyDlg.h"
#include "PoiData.h"
#include "MileageInfo.h"
#include "UserDongPos.h"
#include "RemoteAddrDlg.h" 

#define MAX_PASS			64
#define KEYLENGTH			0x00800000
#define ENCRYPT_BLOCK_SIZE  8

void EnCode1(CString &strID) 
{
	char key = 2;
	for(int i = 0; i < strID.GetLength(); i++)
		strID.SetAt(i, strID.GetAt(i) ^ key);
};



// CLogonDlg 대화 상자입니다.
IMPLEMENT_DYNAMIC(CLogonDlg, CMyDialog) 
CLogonDlg::CLogonDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CLogonDlg::IDD, pParent)
{
	m_bAuth = FALSE;
}

CLogonDlg::~CLogonDlg()
{
}

void CLogonDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ID_EDIT, m_strID);
	DDX_Text(pDX, IDC_PW_EDIT, m_strPW);
	DDX_Control(pDX, IDC_CLOSE_BTN, m_CloseBtn);
	DDX_Control(pDX, IDC_OK_BTN, m_OkBtn);
	DDX_Control(pDX, IDC_CANCEL_BTN, m_CancelBtn);
	DDX_Control(pDX, IDC_HPAUTH_BUTTON, m_HpAuthBtn);
	DDX_Control(pDX, IDC_REMOTE_BUTTON, m_RemoteBtn);
	DDX_Control(pDX, IDC_BACK_STATIC, m_BackStatic);
	DDX_Control(pDX, IDC_SAVE_ID_CHECK, m_chkSaveID);
	DDX_Control(pDX, IDC_MENT_STATIC, m_stcMent);
	DDX_Control(pDX, IDC_MENT_STATIC2, m_stcMent2);
	DDX_Control(pDX, IDC_VERSION_STATIC, m_stcVersion);
	DDX_Control(pDX, IDC_ID_EDIT, m_edtID);
	DDX_Control(pDX, IDC_PW_EDIT, m_edtPW);
}


BEGIN_MESSAGE_MAP(CLogonDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_REMOTE_BUTTON, OnBnClickedRemoteBtn)
	ON_BN_CLICKED(IDC_HPAUTH_BUTTON, OnBnClickedHpauthButton)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CLogonDlg 메시지 처리기입니다.

BOOL CLogonDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	SetForegroundWindow();
	RefreshMent();
	SetVersionInfo();

	SetWindowPos(&CWnd::wndTopMost, 0,0,0, 0, SWP_NOSIZE | SWP_NOMOVE);
	CenterWindow(GetDesktopWindow());

	m_edtID.SetUserOption(RGB(100, 100, 100), RGB(255, 255, 255), "ID",  FALSE);
	m_edtPW.SetUserOption(RGB(100, 100, 100), RGB(255, 255, 255), "PW", FALSE);
	m_edtID.SetMyFont("맑은 고딕", 19, FW_NORMAL);
	m_edtPW.SetMyFont("맑은 고딕", 19, FW_NORMAL);

	m_CloseBtn.LoadBitmaps(IDB_LOGIN_CLOSE_UP, IDB_LOGIN_CLOSE_DOWN);
	m_CloseBtn.SizeToContent();
	m_OkBtn.LoadBitmaps(IDB_LOGIN_OK_UP, IDB_LOGIN_OK_DOWN);
	m_OkBtn.SizeToContent();
	m_CancelBtn.LoadBitmaps(IDB_LOGIN_CANCEL_UP, IDB_LOGIN_CANCEL_DOWN);
	m_CancelBtn.SizeToContent();
	m_HpAuthBtn.LoadBitmaps(IDB_LOGIN_CELL_UP, IDB_LOGIN_CELL_DOWN);
	m_HpAuthBtn.SizeToContent();
	m_RemoteBtn.LoadBitmaps(IDB_LOGIN_REMOTE_UP, IDB_LOGIN_REMOTE_DOWN);
	m_RemoteBtn.SizeToContent();

	if(m_strID.GetLength() > 0)
	{
		OnOK();
		return TRUE;
	}

	CheckSaveID();

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CLogonDlg::CheckSaveID()
{
	BOOL bSaveID = AfxGetApp()->GetProfileInt("test", "test3211", 0);
	m_sPreID = AfxGetApp()->GetProfileString("test", "test321", "");

	//EnCode1(m_sPreID);

	if(m_sPreID != "")
	{
		if(bSaveID)
			((CEdit*)GetDlgItem(IDC_ID_EDIT))->SetWindowText(m_sPreID);

		GetDlgItem(IDC_PW_EDIT)->SetFocus();
	}

	m_chkSaveID.SetCheck(bSaveID);

	//by mksong (2010-05-16 오후 7:28) 
	//최종 릴리즈시에 아래주석 풀어야한다.
#ifdef _DEBUG		
	m_chkSaveID.SetCheck(1);
	if(!(GetKeyState(VK_CONTROL) & 0x8000))
		OnOK();
#endif

}
void CLogonDlg::SaveID()
{
	if(m_chkSaveID.GetCheck() == BST_CHECKED)
	{
		if(m_strID.GetLength() > 0)
		{
			CString sID = m_strID;
			//EnCode1(sID);

			AfxGetApp()->WriteProfileInt("test", "test3211", 1);
			AfxGetApp()->WriteProfileString("test", "test321", sID);
		}
		else
		{
			AfxGetApp()->GetProfileInt("test", "test3211", 0);
			AfxGetApp()->WriteProfileString("test", "test321", "");
		}
	}
	else
	{
		AfxGetApp()->GetProfileInt("test", "test3211", 0);
		AfxGetApp()->WriteProfileString("test", "test321", "");
	}
}

CString CLogonDlg::GetLogiSessionKey()
{
	HKEY hKey;
	char szSession[30];
	memset(&szSession, 0, sizeof(szSession));
	DWORD size = sizeof(szSession);

	if(ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Logisoft\\Quick\\Quick", 0, KEY_ALL_ACCESS, &hKey))
	{
		if(ERROR_SUCCESS == RegQueryValueEx(hKey, "ProgValue", 0, NULL, (LPBYTE)&szSession, &size))
		{
			RegCloseKey(hKey);

			CString strTemp;
			strTemp.Format("%s", szSession);
			return strTemp;
		}

		RegCloseKey(hKey);		
	}
	else 
		return "";

	return "";
}


void CLogonDlg::OnOK()
{
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_ID_EDIT);

	if(pEdit->GetWindowTextLength() == 0)
		return;


	static int nTryCnt = 0;
	long nRetValue;
	CWaitCursor wait;
	UpdateData(TRUE);

	LF->GetMacAddress();

	CString strInternalIP = LF->GetHostName();
	CString strHddID = LF->GetHddId();
	CString sPower = "";

	CString strRegKey = AfxGetApp()->GetProfileString("manager2008", "test", "");
	if(strRegKey == "")
		strRegKey = AfxGetApp()->GetProfileString("manager2008", "test", "");

	m_ei.strMac1.Trim();
	m_ei.strMac2.Trim(); 
	strHddID.Trim(); 

	CString strLogiSession = GetLogiSessionKey();
	CString strLocalVer = LF->GetMyFileVersion();

    CMkRecordset pRs(m_pMkDb); 
	CMkCommand pCmd(m_pMkDb, "select_rcp_client_login_2011_13", TRUE);	
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(typeString, typeInput, m_strID.GetLength(), m_strID);
	pCmd.AddParameter(typeString, typeInput, m_strPW.GetLength(), m_strPW);
	pCmd.AddParameter(typeString, typeInput, m_ei.strMac1.GetLength(), m_ei.strMac1);
	pCmd.AddParameter(typeString, typeInput, m_ei.strMac2.GetLength(), m_ei.strMac2);
	pCmd.AddParameter(typeString, typeInput, strInternalIP.GetLength(), strInternalIP);
	pCmd.AddParameter(typeString, typeInput, strHddID.GetLength(), strHddID);
	pCmd.AddParameter(typeString, typeInput, strRegKey.GetLength(), strRegKey);
	pCmd.AddParameter(typeString, typeInput, strLocalVer.GetLength(), strLocalVer);
	pCmd.AddParameter(typeString, typeInput, strLogiSession.GetLength(), strLogiSession);
	CMkParameter *parServerAddr = pCmd.AddParameter(typeString, typeInputOutput, m_si.strRealMainServerAddr.GetLength(), m_si.strRealMainServerAddr);
	CMkParameter *parServerPort = pCmd.AddParameter(typeLong, typeInputOutput, sizeof(int), (int)m_si.nRealMainServerPort);
	CMkParameter *parIP = pCmd.AddParameter(typeString, typeInputOutput, (long)strlen(DB_SUBTYPE_IP), DB_SUBTYPE_IP);
	CMkParameter *parSessionKey = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parAuthRemainDay = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parPowerCode = pCmd.AddParameter(typeString, typeOutput,  2000, "");
	CMkParameter *parShareBalance = pCmd.AddParameter(typeLong, typeOutput,  sizeof(long), 0);
	CMkParameter *parDeveloper = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parCompany = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

	if(!pRs.Execute(&pCmd)) return;

	parRet->GetValue(nRetValue);
	
    if(nRetValue == 0) {
		Sleep(1000); //의도적으로 1초 지연시킴
		MessageBox("아이디와 비밀번호가 일치하지 않거나, 등록되지 않은 아이디 입니다.", 
				"로그인 실패", MB_ICONEXCLAMATION);
		if(nTryCnt++ >= 2) {
			AfxMessageBox("로그인 재시도 횟수를 초과했습니다.\n프로그램을 종료합니다.");
			pRs.Close();
			CMyDialog::OnCancel();
		}
		return;
	}
	if(nRetValue == 1) {
		Sleep(1000); //의도적으로 1초 지연시킴
		MessageBox("입력하신 아이디는 접수자가 아닙니다.\n접수자 아이디를 사용하시기 바랍니다.",
				"로그인 실패", MB_ICONINFORMATION);
		if(nTryCnt++ >= 2) {
			MessageBox("로그인 재시도 횟수를 초과했습니다.\n프로그램을 종료합니다.", 
				"로그인 실패", MB_ICONERROR);
			pRs.Close();
			CMyDialog::OnCancel();
		}
	}
	else if(nRetValue == 2) {
		MessageBox("승인되지 않은 컴퓨터입니다.\n인증받으시기 바랍니다..",
				"로그인 거부", MB_ICONEXCLAMATION);

		CNewCertifyDlg dlg;
		dlg.m_strID = m_strID;
		dlg.m_strPW = m_strPW;
		dlg.DoModal();
		return;
	}	
	else if(nRetValue == 3) {
		MessageBox("PC에 저장된 인증정보가 변경되었습니다.\n재인증 받으시기 바랍니다.",
			"로그인 거부", MB_ICONEXCLAMATION);

		CNewCertifyDlg dlg;
		dlg.m_strID = m_strID;
		dlg.m_strPW = m_strPW;
		dlg.DoModal();
		return;
	}	
	else if(nRetValue == 4) {
		MessageBox("인증이 만료되었습니다.\n재인증 받으시기 바랍니다.",
			"로그인 거부", MB_ICONEXCLAMATION);

		CNewCertifyDlg dlg;
		dlg.m_strID = m_strID;
		dlg.m_strPW = m_strPW;
		dlg.DoModal();
		return;
	}
	else if(nRetValue == 5) {
		MessageBox("일반인증모드에서는 관리자 로그인이 불가능합니다.\n재인증 받으시기 바랍니다.",
			"로그인 거부", MB_ICONEXCLAMATION);

		CNewCertifyDlg dlg;
		dlg.m_strID = m_strID;
		dlg.m_strPW = m_strPW;
		dlg.DoModal();
		return;
	}
	else if(nRetValue == 6) {
		MessageBox("단독모드에서는 통합ID로그인이 불가능합니다.\n재인증 받으시기 바랍니다.",
			"로그인 거부", MB_ICONEXCLAMATION);

		CNewCertifyDlg dlg;
		dlg.m_strID = m_strID;
		dlg.m_strPW = m_strPW;
		dlg.DoModal();
		return;
	}
	else if(nRetValue == 10) {
		parServerAddr->GetValue(m_si.strRealMainServerAddr);
		m_si.nRealMainServerPort = parServerPort->GetLong();

		m_pMkDb->Close();
		if(!m_pMkDb->Open(m_si.strRealMainServerAddr, m_si.nRealMainServerPort)) {
			MessageBox("재시도 하시기 바랍니다", "분산서버 연결 실패", MB_ICONERROR);
			CMyDialog::OnCancel();
			return;
		}

		AfxGetApp()->WriteProfileString("manager2008", "MyServerAddr", m_si.strRealMainServerAddr);
		AfxGetApp()->WriteProfileInt("manager2008", "MyServerPort", m_si.nRealMainServerPort);
		CLogonDlg::OnOK();
		return;
	}
	else {
		SaveID();

		if(parAuthRemainDay->GetLong() > 0) 
		{
			CString strMsg;
			strMsg.Format("인증만료시점이 %d일 남았습니다.\n만료되기전에 재인증 받으시기 바랍니다.\n\n"\
				"확인버튼을 누르시면 계속됩니다.", parAuthRemainDay->GetLong()); 
			MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		}

		m_ui.dtLoginTime = COleDateTime::GetCurrentTime();
		CString sCallBackNumber = "";
		CString sChargeSearchOrder = "";
		long nShareBalance;

		parDeveloper->GetValue(m_ui.bDeveloper);
		parShareBalance->GetValue(nShareBalance);

		//by mksong (2014-05-26 오전 11:05)
		//퀵 할성화 정책 때문에, 0원에서 -10000원으로 하향 조정함
		if(nShareBalance < -10000)
		{
			CString strAccount;
			CMkCommand pCmd(m_pMkDb, "select_share_account");
			pCmd.AddParameter(parCompany->GetLong());
			CMkParameter *parAccount = pCmd.AddParameter(typeString, typeOutput, 100, "");

			if(pCmd.Execute(m_pMkDb))
				strAccount = parAccount->GetString();

			CString strMsg;

			if(strAccount.IsEmpty())
				strMsg = "충전금이 -10000원 미만이어서 로그인 하실 수 없습니다.\r\n로지소프트로 문의 하세요";
			else
				strMsg.Format("충전금이 -10000원 미만이어서 로그인 하실 수 없습니다.\r\n[하나은행 계좌번호:%s]으로 계좌이체 충전바랍니다.", strAccount);

			MessageBox(strMsg, "확인", MB_ICONINFORMATION);
			return;
		}

		parIP->GetValue(m_ei.strExternalIP);
		parSessionKey->GetValue(m_ui.nSiteSessionKey);
		g_bana_log->Print("external ip = %s, session key = %d\n", m_ei.strExternalIP, m_ui.nSiteSessionKey);
		g_bana_log->Print("server ip = %s, server port = %d\n", m_si.strRealMainServerAddr, m_si.nRealMainServerPort);

		//pRs.GetFieldValue(0, m_ui.strPW);
		m_ui.strPW = m_strPW;
		m_ci.m_bAllocateWithPDA = TRUE;

		pRs.GetFieldValue(0, m_ci.m_bound.nPosX);
		pRs.GetFieldValue(1, m_ci.m_bound.nPosY);
		pRs.GetFieldValue(2, m_ci.m_bound.nBoundary1);
		pRs.GetFieldValue(3, m_ci.m_bound.nBoundary2);
		pRs.GetFieldValue(4, m_ci.m_bound.nBoundary3);
		pRs.GetFieldValue(5, m_ui.nRole);
		pRs.GetFieldValue(6, m_ci.m_nCompanyCode);
        pRs.GetFieldValue(7, m_ui.nWNo);
		pRs.GetFieldValue(8, m_ui.strName);
		pRs.GetFieldValue(9, m_ci.m_strName);
		pRs.GetFieldValue(10, m_ci.m_strBizNo);
		pRs.GetFieldValue(11, m_ci.m_strBizType1);
		pRs.GetFieldValue(12, m_ci.m_strBizType2);
		pRs.GetFieldValue(13, m_ci.m_strPhone);
		pRs.GetFieldValue(14, m_ci.m_strOwner);
		pRs.GetFieldValue(15, m_ci.m_strAddress);
		pRs.GetFieldValue(16, m_ci.m_strCity);
		pRs.GetFieldValue(17, m_ci.m_strDDD);
		pRs.GetFieldValue(18, m_ci.m_nUseCustomerTable);
		pRs.GetFieldValue(19, m_ci.m_nUsePayTable);
		pRs.GetFieldValue(20, m_ci.m_nUseDOrderTable);
		pRs.GetFieldValue(21, m_ci.m_nStateType);
		pRs.GetFieldValue(22, m_ci.m_bAllocateWithPDA);
		pRs.GetFieldValue(23, m_ci.m_bUseInterCall);
		pRs.GetFieldValue(24, m_ci.m_nCompanyWorking);
		pRs.GetFieldValue(25, m_ci.m_bUseSlowOrder);
		pRs.GetFieldValue(26, m_ci.m_nSlowCharge);
		pRs.GetFieldValue(27, m_ci.m_strSlowMsg);
		pRs.GetFieldValue(28, m_ci.m_nShareCode1);
		pRs.GetFieldValue(29, m_ci.m_nShareCode2);
		pRs.GetFieldValue(30, m_ci.m_nShareCode3);
		pRs.GetFieldValue(31, m_ci.m_nShareCode4);
		pRs.GetFieldValue(32, m_ci.m_nShareCode5);
		pRs.GetFieldValue(33, m_ci.m_bRcpIntMode1);
		pRs.GetFieldValue(34, m_ci.m_bRcpIntMode2);
		pRs.GetFieldValue(35, m_ci.m_bRcpIntMode3);
		pRs.GetFieldValue(36, m_ci.m_bRcpIntMode4);
		pRs.GetFieldValue(37, m_ci.m_bRcpIntMode5);
		pRs.GetFieldValue(38, m_ci.m_nShareStartTime1);
		pRs.GetFieldValue(39, m_ci.m_nShareStartTime2);
		pRs.GetFieldValue(40, m_ci.m_nShareStartTime3);
		pRs.GetFieldValue(41, m_ci.m_nShareStartTime4);
		pRs.GetFieldValue(42, m_ci.m_nShareStartTime5);
		pRs.GetFieldValue(43, m_ci.m_bClientIntMode1);
		pRs.GetFieldValue(44, m_ci.m_bClientIntMode2);
		pRs.GetFieldValue(45, m_ci.m_bClientIntMode3);
		pRs.GetFieldValue(46, m_ci.m_bClientIntMode4);
		pRs.GetFieldValue(47, m_ci.m_bClientIntMode5);
		pRs.GetFieldValue(48, m_ci.m_strOfficePhone);
		pRs.GetFieldValue(49, m_ci.m_bAlwaysIntegrate);
		pRs.GetFieldValue(50, m_ci.m_bCreditAfterDiscount);
		pRs.GetFieldValue(51, m_ci.m_bRcpNoHistory);
		pRs.GetFieldValue(52, m_ci.m_bRcpNoChargeHistory);
		pRs.GetFieldValue(53, m_ci.m_nRcpTimeColor);
		pRs.GetFieldValue(54, m_ci.m_nSMSAllocate);
		pRs.GetFieldValue(55, m_ci.m_nType); 		
		pRs.GetFieldValue(56, m_ci.m_bUseShareReport); 
		pRs.GetFieldValue(57, m_ci.m_bUseBranchShareReport); 
		pRs.GetFieldValue(58, m_ci.m_nAllocateSMSType); 
		pRs.GetFieldValue(59, m_ci.m_bSearchFourNumberWithUID); 
		pRs.GetFieldValue(60, m_ci.m_bSingleAllocate);
		pRs.GetFieldValue(61, m_ci.m_bSendOnePage);
		pRs.GetFieldValue(62, m_ci.m_bUseCidPool);
		pRs.GetFieldValue(63, m_ci.m_bDisableCreditBtn);
		pRs.GetFieldValue(64, m_ci.m_strAllocateSMSF);
		pRs.GetFieldValue(65, m_ci.m_bUseDaeriShare);
		pRs.GetFieldValue(66, m_ci.m_bUseCoaliShare);
		pRs.GetFieldValue(67, m_ci.m_bNotUseCNS);
		pRs.GetFieldValue(68, sCallBackNumber);
		pRs.GetFieldValue(69, sChargeSearchOrder);
		pRs.GetFieldValue(70, m_ci.m_bUseOrderChangeMent);
		pRs.GetFieldValue(71, m_ci.m_bUseDetailDong);
		pRs.GetFieldValue(72, m_ci.m_nPenaltyLevel);
		pRs.GetFieldValue(73, m_ci.m_bUseRTIDOnSpeedAllocate); // 빠른배차시 지사기사 다 끍어 오므로 branchinfo말고 요기에 넣음
		pRs.GetFieldValue(74, m_ui.strLogiStaffName);
		pRs.GetFieldValue(75, m_ci.m_nAutoHangupElapsedMin);
		pRs.GetFieldValue(76, m_ci.m_strUsePrgVersion);
		pRs.GetFieldValue(77, m_ci.m_bUseSearchPopup);
		m_ci.m_bUseSearchPopup = false;

		parPowerCode->GetValue(sPower);
		m_pi.SetPowerChunk(sPower, m_ui.nRole);

		pRs.GetFieldValue(76, m_ui.strTaxUseEmail);
		m_ui.nCompany = m_ci.m_nCompanyCode;
		m_ci.m_nFirstPage = atoi(sCallBackNumber.Left(1));
		m_ci.m_nSecondPage = atoi(sCallBackNumber.Mid(2, 1));
		m_ci.m_nThirdPage = atoi(sCallBackNumber.Mid(4, 1));

		m_ci.m_nChargeSearchOrder[0] = atoi(sChargeSearchOrder.Left(1));
		m_ci.m_nChargeSearchOrder[1] = atoi(sChargeSearchOrder.Mid(2, 1));
		m_ci.m_nChargeSearchOrder[2] = atoi(sChargeSearchOrder.Mid(4, 1));
		m_ci.m_nChargeSearchOrder[3] = atoi(sChargeSearchOrder.Mid(6, 1));

		UpdateRegionInfo();
		
		//by mksong (2010-09-23 오후 8:50)
		//m_poi.SetCenterPos(m_ci.m_bound.nPosX, m_ci.m_bound.nPosY);


		if(m_ci.m_nRcpTimeColor == 0)
			m_ci.m_nRcpTimeColor = (10 << 16) + (20 << 8) + 30; 

		m_ci.m_nRcpTimeColor1 = (BYTE)(m_ci.m_nRcpTimeColor >> 16);
		m_ci.m_nRcpTimeColor2 = (BYTE)(m_ci.m_nRcpTimeColor >> 8);
		m_ci.m_nRcpTimeColor3 = (BYTE)(m_ci.m_nRcpTimeColor);

		int nCompany, nBranchCode = 0;
		int nShareCode1, nShareCode2, nShareCode3, nShareCode4, nShareCode5;
		BOOL bUseBranchShareReport, bUsePayBonggoFromLabo = FALSE, bDongPosLiUse = FALSE, bRcpIntMode1;
		CString strName, strBranchName, strPhone, strOfficePhone, strCarTypeOrder, strPayTypeOrder;
		long nShareLevel = 0;
		CMkRecordset pRs2(m_pMkDb);
		CMkCommand pCmd2(m_pMkDb, "select_share_company_2011_33");
		pCmd2.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
		if(pRs2.Execute(&pCmd2))  
		{
			CMainFrame *pFrame = (CMainFrame*) AfxGetMainWnd();
			m_ba.RemoveAll();

			while(!pRs2.IsEOF()) {
				pRs2.GetFieldValue("nShareCode1", nShareCode1);
				pRs2.GetFieldValue("nShareCode2", nShareCode2);
				pRs2.GetFieldValue("nShareCode3", nShareCode3);
				pRs2.GetFieldValue("nShareCode4", nShareCode4);
				pRs2.GetFieldValue("nShareCode5", nShareCode5);
				pRs2.GetFieldValue("nID", nCompany);
				pRs2.GetFieldValue("sName", strName);
				pRs2.GetFieldValue("sBranchName", strBranchName);
				pRs2.GetFieldValue("sTel", strPhone);
				pRs2.GetFieldValue("sOfficePhone", strOfficePhone);
				pRs2.GetFieldValue("nShareLevel", nShareLevel);
				pRs2.GetFieldValue("bRcpIntMode1", bRcpIntMode1);

				if(nShareLevel == - 1)				
				{
					CBranchInfo *pBi = new CBranchInfo;
					pRs2.GetFieldValue("sCarTypeOrder", strCarTypeOrder);
					pRs2.GetFieldValue("sPayTypeOrder", strPayTypeOrder);					

					SetCarTypeOrder(pBi, strCarTypeOrder);
					SetPayTypeOrder(pBi, strPayTypeOrder);
					GetRsData(&pRs2, pBi);
					LoadConsignShare(pBi);						

				}
				else if((m_ci.m_nCompanyCode == nCompany) ||
					(m_ci.m_bRcpIntMode1 && m_ci.m_nShareCode1 == nShareCode1) ||
					(m_ci.m_bRcpIntMode2 && m_ci.m_nShareCode2 == nShareCode2) ||
					(m_ci.m_bRcpIntMode3 && m_ci.m_nShareCode3 == nShareCode3) ||
					(m_ci.m_bRcpIntMode4 && m_ci.m_nShareCode4 == nShareCode4) ||
					(m_ci.m_bRcpIntMode5 && m_ci.m_nShareCode5 == nShareCode5) )
				{ 
					CBranchInfo *pBi = new CBranchInfo;
					  
					
					pRs2.GetFieldValue("bUseBranchShareReport", bUseBranchShareReport);
					pRs2.GetFieldValue("sCarTypeOrder", strCarTypeOrder);
					pRs2.GetFieldValue("sPayTypeOrder", strPayTypeOrder);
					GetRsData(&pRs2, pBi);

					SetCarTypeOrder(pBi, strCarTypeOrder);
					SetPayTypeOrder(pBi, strPayTypeOrder);
					//pRs2.GetFieldValue("bDistancePointUse", pBi->bDistancePointUse);//by mksong (2011-02-01 오전 10:02)
					
					if(bUseBranchShareReport == -1) //1이 -1로 리턴??
						bUseBranchShareReport = TRUE;

					pBi->strLineGroup.Trim(' ');
					pBi->strLineGroup.Trim(",");
					pBi->strLineGroup = "," + pBi->strLineGroup + ",";
					pBi->strPhone = LF->GetDashPhoneNumber(pBi->strPhone);

					pBi->nShareCode1 = nShareCode1;
					pBi->nShareCode2 = nShareCode2;
					pBi->nShareCode3 = nShareCode3;
					pBi->nShareCode4 = nShareCode4;
					pBi->nShareCode5 = nShareCode5;
					pBi->bGroup = TRUE;
					pBi->nBranchCode = nBranchCode;

					if(pBi->nShareLevel ==  2) 
						pBi->strBranchName = CString("②") + pBi->strBranchName;
					else if(pBi->nShareLevel == 3)
						pBi->strBranchName = CString("③") + pBi->strBranchName;
					else if(pBi->nShareLevel == 4)
						pBi->strBranchName = CString("④") + pBi->strBranchName;
					else if(pBi->nShareLevel == 5)
						pBi->strBranchName = CString("⑤") + pBi->strBranchName;

				

					if(nBranchCode++ == 0) {
						CBranchInfo *pBi2		= new CBranchInfo;
						pBi2->nShareLevel		= pBi->nShareLevel;
						pBi2->nCompanyCode		= pBi->nCompanyCode;
						pBi2->nDOrderTable		= pBi->nDOrderTable;
						pBi2->nCustomerTable	= pBi->nCustomerTable;
						pBi2->nPayTable			= pBi->nPayTable;
						pBi2->nStateType		= pBi->nStateType;
						pBi2->nShareStartTime1 	= pBi->nShareStartTime1;
						pBi2->nShareStartTime2 	= pBi->nShareStartTime2;
						pBi2->nShareStartTime3 	= pBi->nShareStartTime3;
						pBi2->nShareStartTime4 	= pBi->nShareStartTime4;
						pBi2->nShareStartTime5 	= pBi->nShareStartTime5;
						pBi2->nSubDisplayGroup 	= pBi->nSubDisplayGroup;
						pBi2->nShareCode1		= pBi->nShareCode1;
						pBi2->nShareCode2 		= pBi->nShareCode2;
						pBi2->nShareCode3 		= pBi->nShareCode3;
						pBi2->nShareCode4 		= pBi->nShareCode4;
						pBi2->nShareCode5 		= pBi->nShareCode5;						
						pBi2->bGroup			= pBi->bGroup;
						pBi2->nBranchCode		= pBi->nBranchCode;
						pBi2->strBranchName		= "통합";
						pBi2->bIntegrated = TRUE;
						pBi2->strLineGroup = pBi->strLineGroup;
						pBi2->bCreditAfterDiscount = pBi->bCreditAfterDiscount;
						pBi2->nFinalSMSSend = pBi->nFinalSMSSend;						
						pBi2->strPhone = pBi->strPhone;
						pBi2->bUseChargeDong = pBi->bUseChargeDong;
						pBi2->nDefaultCharge = pBi->nDefaultCharge;
						pBi2->nDamasPay = pBi->nDamasPay;
						pBi2->nRaboPay = pBi->nRaboPay;
						pBi2->nTruckPay = pBi->nTruckPay;
						pBi2->nBonggoPay = pBi->nBonggoPay;
						pBi2->bUseNewRegion = pBi->bUseNewRegion;						
						
						pBi2->nRcpColor = pBi->nRcpColor;
						pBi2->nRcpTextColor = pBi->nRcpTextColor;
						pBi2->strMemo = pBi->strMemo;
						pBi2->nTankType = pBi->nTankType;

						pBi2->nMileageSettingCount = pBi->nMileageSettingCount;
						pBi2->nMileageSpan = pBi->nMileageSpan;

						//pBi->bUseBranchShareReport
						//pBi->bRcpIntMode1
						pBi2->strCallingLine = pBi->strCallingLine;

						pBi2->bUserIDSequence = pBi->bUserIDSequence;
						pBi2->nRevisitCustomerSendDay = pBi->nRevisitCustomerSendDay;
						pBi2->nRevisitCustomerSendCompany = pBi->nRevisitCustomerSendCompany;

						pBi2->bUseOnLine = pBi->bUseOnLine;
						pBi2->bUserDongPos = pBi->bUserDongPos;
						pBi2->nLaboChargeType = pBi->nLaboChargeType;
						pBi2->nTruckDeposit = pBi->nTruckDeposit;
						pBi2->nSmsChargeCompany = pBi->nSmsChargeCompany;
						pBi2->nBothCharge = pBi->nBothCharge;
						pBi2->nEmergencyCharge = pBi->nEmergencyCharge;

						pBi2->sEtcUserTitle1 = pBi->sEtcUserTitle1;
						pBi2->sEtcUserTitle2 = pBi->sEtcUserTitle2;
						pBi2->sEtcUserTitle3 = pBi->sEtcUserTitle3;
						pBi2->sEtcUserTitle4 = pBi->sEtcUserTitle4;
						pBi2->sEtcUserMemo1 = pBi->sEtcUserMemo1;
						pBi2->sEtcUserMemo2 = pBi->sEtcUserMemo2;
						pBi2->sEtcUserMemo3 = pBi->sEtcUserMemo3;
						pBi2->sEtcUserMemo4 = pBi->sEtcUserMemo4;

						pBi2->bDistanceCharge = pBi->bDistanceCharge;
						pBi2->nDistanceCharge = pBi->nDistanceCharge;
						pBi2->nMinCharge = pBi->nMinCharge;
						pBi2->bMemChaNoGeneralData = pBi->bMemChaNoGeneralData;
						

						pBi2->bUseCardTax = pBi->bUseCardTax;
						pBi2->bDistancePointUse = pBi->bDistancePointUse;
						pBi2->bUseCardTax = pBi->bUseCardTax;
						pBi2->strCity = pBi->strCity;
						pBi2->bUsageHistory = pBi->bUsageHistory;						
						pBi2->bNotUseEtcForCancel = pBi->bNotUseEtcForCancel;

						pBi2->nPayType1 = pBi->nPayType1;
						pBi2->nPayType2 = pBi->nPayType2;
						pBi2->nPayType3 = pBi->nPayType3;
						pBi2->nPayType4 = pBi->nPayType4;
						pBi2->nCarType1 = pBi->nCarType1;
						pBi2->nCarType2 = pBi->nCarType2;
						pBi2->nCarType3 = pBi->nCarType3;

						pBi2->nServiceType = pBi->nServiceType;
						pBi2->bMemoToEtc = pBi->bMemoToEtc;						
						pBi2->bRiderMemoToEtc = pBi->bRiderMemoToEtc;

						pBi2->bCallerIDToPhone1 = pBi->bCallerIDToPhone1;
						pBi2->bClearDestForAfterCopy = pBi->bClearDestForAfterCopy;						
						pBi2->bFocusToWaitBtn = pBi->bFocusToWaitBtn;				
						pBi2->bAutoShareOrder = pBi->bAutoShareOrder;

						pBi2->nAutoShareTime = pBi->nAutoShareTime;
						pBi2->bNoGroupCharge = pBi->bNoGroupCharge;
						pBi2->bAddDisChargeRound = pBi->bAddDisChargeRound;
						pBi2->nOtherCompany = pBi->nOtherCompany;
						pBi2->strOtherCompanyName = pBi->strOtherCompanyName;
						pBi2->nOtherCompanyCNo = pBi->nOtherCompanyCNo;
						pBi2->nOtherCompanyCNoTelID = pBi->nOtherCompanyCNoTelID;
						pBi2->nNowRate = pBi->nNowRate;
						pBi2->dtInitDay = pBi->dtInitDay;
						pBi2->dtAcceptApply = pBi->dtAcceptApply;
						pBi2->nConsignID = pBi->nConsignID;
						pBi2->bTodayDelete = pBi->bTodayDelete;
						pBi2->dtTodayDelete = pBi->dtTodayDelete;
						pBi2->bUseOrderBundle = pBi->bUseOrderBundle;
						pBi2->bCancelToInquiry = pBi->bCancelToInquiry;
						pBi2->bEtcAuto = pBi->bEtcAuto;
						pBi2->strEtcAuto = pBi->strEtcAuto;
						pBi2->bUseCardPay = pBi->bUseCardPay;
						pBi2->bNotMemberCharge = pBi->bNotMemberCharge;
						pBi2->bCancelReason = pBi->bCancelReason;
						pBi2->nPayType5 = pBi->nPayType5;
						pBi2->nCarType4 = pBi->nCarType4;
						pBi2->nCarType5 = pBi->nCarType5;
						pBi2->bInitDongInfo = pBi->bInitDongInfo;
						pBi2->bCreditListPopup = pBi->bCreditListPopup;
						pBi2->bIPPBXType = pBi->bIPPBXType;
						pBi2->bNoDestPoi = pBi->bNoDestPoi;
						pBi2->bNotClientPhone1 = pBi->bNotClientPhone1;
						pBi2->bNotCustomerAddCID = pBi->bNotCustomerAddCID;
						pBi2->bUseDirectDistance =  pBi->bUseDirectDistance;
						pBi2->bCustomerAutoInsert = pBi->bCustomerAutoInsert;
						pBi2->bFirstWaitTimePast = pBi->bFirstWaitTimePast;
						pBi2->nHistoryDetailAllView = pBi->nHistoryDetailAllView;
						pBi2->nUseUpChargeForNotAllocate = pBi->nUseUpChargeForNotAllocate;
						pBi2->nUpChargeForNotAllocate1	= pBi->nUpChargeForNotAllocate1;
						pBi2->nUpChargeForNotAllocate2	= pBi->nUpChargeForNotAllocate2;
						pBi2->nUpChargeForNotAllocate3	= pBi->nUpChargeForNotAllocate3;
						pBi2->bPopupFocus				= pBi->bPopupFocus;
						pBi2->bColorChange				= pBi->bColorChange;
						pBi2->bOnlyLoadInsRider			= pBi->bOnlyLoadInsRider;
						pBi2->nFeeType					= pBi->nFeeType;
						pBi2->nBranchDiscount			= pBi->nBranchDiscount;
						pBi2->strName					= pBi->strName;
						pBi2->bVRAccountNoRider			= pBi->bVRAccountNoRider;
						pBi2->strDDD					= pBi->strDDD;
						pBi2->bDongPosLiUse				= pBi->bDongPosLiUse;
						pBi2->nBikeAddWeather			= pBi->nBikeAddWeather;
						pBi2->nDamaAddWeather			= pBi->nDamaAddWeather;
						pBi2->nLaboAddWeather			= pBi->nLaboAddWeather;
						pBi2->nVanAddWeather			= pBi->nVanAddWeather;
						pBi2->nTruckAddWeather			= pBi->nTruckAddWeather;
						pBi2->bWeatherCharge			= pBi->bWeatherCharge;

						pBi2->nBikeAddWeatherSnow			= pBi->nBikeAddWeatherSnow;
						pBi2->nDamaAddWeatherSnow			= pBi->nDamaAddWeatherSnow;
						pBi2->nLaboAddWeatherSnow			= pBi->nLaboAddWeatherSnow;
						pBi2->nVanAddWeatherSnow			= pBi->nVanAddWeatherSnow;
						pBi2->nTruckAddWeatherSnow			= pBi->nTruckAddWeatherSnow;
						pBi2->bWeatherChargeSnow			= pBi->bWeatherChargeSnow;
						pBi2->nSlowDiscount					= pBi->nSlowDiscount;
						pBi2->nCnsSearchType1					= pBi->nCnsSearchType1;
						pBi2->nCnsSearchType2					= pBi->nCnsSearchType2;
						pBi2->nCnsSearchPaid					= pBi->nCnsSearchPaid;
						pBi2->init_dt1_state_to_rcp				= pBi->init_dt1_state_to_rcp;
							
						m_ci.CheckFirstMain(pBi2);
		
						m_ba.Add(pBi2);
						nBranchCode++;
					}

					m_ci.CheckFirstMain(pBi);

					ST_SHARE_COMPANY_INFO sinfo;
					sinfo.strBranchName = pBi->strBranchName;
					sinfo.strName = pBi->strBranchName;
					sinfo.nCompany = pBi->nCompanyCode;
					sinfo.nShareCode1 = nShareCode1;
					sinfo.nShareCode2 = nShareCode2;
					sinfo.nShareCode3 = nShareCode3;
					sinfo.nShareCode4 = nShareCode4;
					sinfo.nShareCode5 = nShareCode5;
					sinfo.bRcpIntMode1 = bRcpIntMode1;
					sinfo.strPhone = strPhone;
					sinfo.strOfficePhone = strOfficePhone;
					sinfo.bUseBranchShareReport = bUseBranchShareReport;
					sinfo.nCnsSearchType1 = pBi->nCnsSearchType1;
					sinfo.nCnsSearchType2 = pBi->nCnsSearchType2;
					sinfo.nCnsSearchPaid = pBi->nCnsSearchPaid; 
					m_ci.GetMap().insert(MAP_SHARED_COMPANY::value_type(pBi->nCompanyCode, sinfo));
					m_ci.m_ccm[nCompany] = nCompany;

					pBi->bIntegrated = FALSE;
					m_ba.Add(pBi);
				}
				else {
					if(m_ci.m_nShareCode1 == nShareCode1)
					{	
						CBranchInfo *pBi = new CBranchInfo;

						pRs2.GetFieldValue("bUseBranchShareReport", bUseBranchShareReport);
						pRs2.GetFieldValue("sCarTypeOrder", strCarTypeOrder);
						pRs2.GetFieldValue("sPayTypeOrder", strPayTypeOrder);
						GetRsData(&pRs2, pBi);


						if(bUseBranchShareReport == -1) //1이 -1로 리턴??
							bUseBranchShareReport = TRUE;

						pBi->strLineGroup += ",";
						pBi->strPhone = LF->GetDashPhoneNumber(pBi->strPhone);
						pBi->nShareCode1 = nShareCode1;
						pBi->nShareCode2 = nShareCode2;
						pBi->nShareCode3 = nShareCode3;
						pBi->nShareCode4 = nShareCode4;
						pBi->nShareCode5 = nShareCode5;
						pBi->bGroup = TRUE;
						pBi->nBranchCode = nBranchCode;
						

						if(pBi->nShareLevel ==  2) 
							pBi->strBranchName = CString("②") + pBi->strBranchName;
						else if(pBi->nShareLevel == 3)
							pBi->strBranchName = CString("③") + pBi->strBranchName;
						else if(pBi->nShareLevel == 4)
							pBi->strBranchName = CString("④") + pBi->strBranchName;
						else if(pBi->nShareLevel == 5)
							pBi->strBranchName = CString("⑤") + pBi->strBranchName;

						if(pBi->nShareLevel == -1)
						{
							LoadConsignShare(pBi);			
							continue;
						}

						pBi->bIntegrated = FALSE;
						m_ba2.Add(pBi);
					}

					ST_SHARE_COMPANY_INFO sinfo;
					sinfo.strBranchName = strBranchName;
					sinfo.strName = strName;
					sinfo.nCompany = nCompany;
					sinfo.nShareCode1 = nShareCode1;
					sinfo.nShareCode2 = nShareCode2;
					sinfo.nShareCode3 = nShareCode3;
					sinfo.nShareCode4 = nShareCode4;
					sinfo.nShareCode5 = nShareCode5;
					sinfo.strPhone = LF->GetDashPhoneNumber(strPhone);
					sinfo.strOfficePhone = LF->GetDashPhoneNumber(strOfficePhone);
					sinfo.bUseBranchShareReport = bUseBranchShareReport;
					m_ci.GetMap().insert(MAP_SHARED_COMPANY::value_type(nCompany, sinfo));
				}

				pRs2.MoveNext();
			}

			//본사/지사가 1개만 있는 경우 포함되어있는 '통합'정보를 제거한다.
			if(m_ba.GetCount() <= 2) {
				m_ba.SetAt(0, m_ba.GetAt(1));
				m_ba.RemoveAt(1);
			}
		}
		
		RefreshOnlyLoadGroup();  // 
		RefreshUserDongPos();// 사용자 정의 DongPos
		MakeLineGroupMap();
		LU->MakeDepositRate();
		LU->ChargeAddDataInitLoad();
		//LU->ShowMemberChargeDlg(  TRUE);
		//LU->LoadMemberCharge(TRUE);
		LU->MakeTransInfo();
		m_mi.FillData();  // 회사마일리지
		LF->LoadCardInfo();

		nTryCnt = 0;
		m_ui.strID = m_strID;
		m_bAuth = TRUE;
		pRs.Close();	

		m_ui.bUseWindow7 = LF->IsWindow7();

		if(m_ci.m_nPenaltyLevel >= 5)
		{
			MessageBox("회원사님 죄송합니다. 서비스가 중지되었습니다. \n",
				"서비스 중지됨",
				MB_ICONINFORMATION);
			m_bAuth = FALSE;
			CMyDialog::OnOK();
		}
		else 
		{
			CMyDialog::OnOK();
			LF->NotifyPenalty(1);
		}

		CMyDialog::OnOK();
	}
}
void CLogonDlg::GetRsData(CMkRecordset *pRs2, CBranchInfo *pBi)
{
	pRs2->GetFieldValue("nShareLevel", pBi->nShareLevel);
	pRs2->GetFieldValue("sBranchName", pBi->strBranchName);
	pRs2->GetFieldValue("sName", pBi->strName);
	pRs2->GetFieldValue("nID", pBi->nCompanyCode);
	pRs2->GetFieldValue("nUseDOrderTable", pBi->nDOrderTable);
	pRs2->GetFieldValue("nUseCustomerTable", pBi->nCustomerTable);
	pRs2->GetFieldValue("nUsePayTable", pBi->nPayTable); 
	pRs2->GetFieldValue("nStateType", pBi->nStateType);
	pRs2->GetFieldValue("nShareStartTime1", pBi->nShareStartTime1);
	pRs2->GetFieldValue("nShareStartTime2", pBi->nShareStartTime2);
	pRs2->GetFieldValue("nShareStartTime3", pBi->nShareStartTime3);
	pRs2->GetFieldValue("nShareStartTime4", pBi->nShareStartTime4);
	pRs2->GetFieldValue("nShareStartTime5", pBi->nShareStartTime5);
	pRs2->GetFieldValue("nSubDisplayGroup", pBi->nSubDisplayGroup);
	pRs2->GetFieldValue("sLineGroup", pBi->strLineGroup);
	pRs2->GetFieldValue("bCreditAfterDiscount", pBi->bCreditAfterDiscount);
	pRs2->GetFieldValue("nFinalSMSSend", pBi->nFinalSMSSend);
	pRs2->GetFieldValue("sTel", pBi->strPhone);
	pRs2->GetFieldValue("bUseChargeDong", pBi->bUseChargeDong);
	pRs2->GetFieldValue("nDefaultCharge", pBi->nDefaultCharge);
	pRs2->GetFieldValue("nDamasPay", pBi->nDamasPay);
	pRs2->GetFieldValue("nRaboPay", pBi->nRaboPay);
	pRs2->GetFieldValue("nTruckPay", pBi->nTruckPay);
	pRs2->GetFieldValue("nBonggoPay", pBi->nBonggoPay);
	pRs2->GetFieldValue("bUseNewRegion", pBi->bUseNewRegion);

	pRs2->GetFieldValue("nRcpColor", pBi->nRcpColor);
	pRs2->GetFieldValue("nRcpTextColor", pBi->nRcpTextColor);
	pRs2->GetFieldValue("sMemo", pBi->strMemo);
	pRs2->GetFieldValue("nTankType", pBi->nTankType);	

	pRs2->GetFieldValue("nMileageSettingCount", pBi->nMileageSettingCount);	
	pRs2->GetFieldValue("nMileageSpan", pBi->nMileageSpan);	
	pRs2->GetFieldValue("bUseBranchShareReport", pBi->bUseBranchShareReport);
	pRs2->GetFieldValue("bRcpIntMode1", pBi->bRcpIntMode1);
	pRs2->GetFieldValue("sCallingLine", pBi->strCallingLine);

	pRs2->GetFieldValue("bUserIDSequence", pBi->bUserIDSequence);
	pRs2->GetFieldValue("nRevisitCustomerSendDay", pBi->nRevisitCustomerSendDay);
	pRs2->GetFieldValue("nRevisitCustomerSendCompany", pBi->nRevisitCustomerSendCompany);

	pRs2->GetFieldValue("bUseOnLine", pBi->bUseOnLine);
	pRs2->GetFieldValue("bUserDongPos", pBi->bUserDongPos);
	pRs2->GetFieldValue("nLaboChargeType", pBi->nLaboChargeType);
	pRs2->GetFieldValue("nTruckDeposit", pBi->nTruckDeposit);
	pRs2->GetFieldValue("nSmsChargeCompany", pBi->nSmsChargeCompany);
	pRs2->GetFieldValue("nBothCharge", pBi->nBothCharge);
	pRs2->GetFieldValue("nEmergencyCharge", pBi->nEmergencyCharge);

	pRs2->GetFieldValue("sEtcUserTitle1", pBi->sEtcUserTitle1);
	pRs2->GetFieldValue("sEtcUserTitle2", pBi->sEtcUserTitle2);
	pRs2->GetFieldValue("sEtcUserTitle3", pBi->sEtcUserTitle3);
	pRs2->GetFieldValue("sEtcUserTitle4", pBi->sEtcUserTitle4);
	pRs2->GetFieldValue("sEtcUserMemo1", pBi->sEtcUserMemo1);
	pRs2->GetFieldValue("sEtcUserMemo2", pBi->sEtcUserMemo2);
	pRs2->GetFieldValue("sEtcUserMemo3", pBi->sEtcUserMemo3);
	pRs2->GetFieldValue("sEtcUserMemo4", pBi->sEtcUserMemo4);

	pRs2->GetFieldValue("bDistanceCharge", pBi->bDistanceCharge);
	pRs2->GetFieldValue("nDistanceCharge", pBi->nDistanceCharge);
	pRs2->GetFieldValue("bUseCardTax", pBi->bUseCardTax);
	pRs2->GetFieldValue("sCity", pBi->strCity);
	pRs2->GetFieldValue("bUsageHistory", pBi->bUsageHistory);
	pRs2->GetFieldValue("bNotUseEtcForCancel", pBi->bNotUseEtcForCancel);

	
	pRs2->GetFieldValue("nType", pBi->nServiceType);
	pRs2->GetFieldValue("bMemoToEtc", pBi->bMemoToEtc);
	pRs2->GetFieldValue("bRiderMemoToEtc", pBi->bRiderMemoToEtc);
	pRs2->GetFieldValue("bCallerIDToPhone1", pBi->bCallerIDToPhone1);
	pRs2->GetFieldValue("bClearDestForAfterCopy", pBi->bClearDestForAfterCopy);	
	pRs2->GetFieldValue("bFocusToWaitBtn", pBi->bFocusToWaitBtn);
	pRs2->GetFieldValue("bAutoShareOrder", pBi->bAutoShareOrder);
	pRs2->GetFieldValue("nAutoShareTime", pBi->nAutoShareTime);
	pRs2->GetFieldValue("bNoGroupCharge", pBi->bNoGroupCharge);
	pRs2->GetFieldValue("bAddDisChargeRound", pBi->bAddDisChargeRound);
	pRs2->GetFieldValue("nOtherCompany", pBi->nOtherCompany);
	pRs2->GetFieldValue("sOtherCompanyName", pBi->strOtherCompanyName);
	pRs2->GetFieldValue("nOtherCompanyCNo", pBi->nOtherCompanyCNo);
	pRs2->GetFieldValue("nOtherCompanyCNoTelID", pBi->nOtherCompanyCNoTelID);
	pRs2->GetFieldValue("nNowRate", pBi->nNowRate);
	pRs2->GetFieldValue("dtInitDay", pBi->dtInitDay);
	pRs2->GetFieldValue("dtAcceptApply", pBi->dtAcceptApply);
	pRs2->GetFieldValue("nConID", pBi->nConsignID);
	pRs2->GetFieldValue("bTodayDelete",				pBi->bTodayDelete);
	pRs2->GetFieldValue("dtTodayDelete",			pBi->dtTodayDelete);
	pRs2->GetFieldValue("bUseOrderBundle",			pBi->bUseOrderBundle);
	pRs2->GetFieldValue("bCancelToInquiry",			pBi->bCancelToInquiry);
	pRs2->GetFieldValue("bEtcAuto",					pBi->bEtcAuto);
	pRs2->GetFieldValue("sEtcAuto",					pBi->strEtcAuto);
	pRs2->GetFieldValue("bUseCardPay",				pBi->bUseCardPay);
	pRs2->GetFieldValue("nFeeType",					pBi->nFeeType);
	pRs2->GetFieldValue("bNotMemberCharge",			pBi->bNotMemberCharge);	
	pRs2->GetFieldValue("bCancelReason",			pBi->bCancelReason);
	pRs2->GetFieldValue("bInitDongInfo",			pBi->bInitDongInfo);
	pRs2->GetFieldValue("bIPPBXType",				pBi->bIPPBXType);
	pRs2->GetFieldValue("bCreditListPopup",			pBi->bCreditListPopup);
	pRs2->GetFieldValue("bNoDestPoi",				pBi->bNoDestPoi);
	pRs2->GetFieldValue("bNotClientPhone1",			pBi->bNotClientPhone1);
	pRs2->GetFieldValue("bNotCustomerAddCID",		pBi->bNotCustomerAddCID);
	pRs2->GetFieldValue("bUseDirectDistance",		pBi->bUseDirectDistance);

	pRs2->GetFieldValue("nMinCharge",				pBi->nMinCharge);
	pRs2->GetFieldValue("bMemChaNoGeneralData",		pBi->bMemChaNoGeneralData);
	pRs2->GetFieldValue("bCustomerAutoInsert",		pBi->bCustomerAutoInsert);
	pRs2->GetFieldValue("bFirstWaitTimePast",		pBi->bFirstWaitTimePast);
	pRs2->GetFieldValue("nHistoryDetailAllView",	pBi->nHistoryDetailAllView);

	pRs2->GetFieldValue("nUseUpChargeForNotAllocate", pBi->nUseUpChargeForNotAllocate);
	pRs2->GetFieldValue("nUpChargeForNotAllocate1", pBi->nUpChargeForNotAllocate1);
	pRs2->GetFieldValue("nUpChargeForNotAllocate2", pBi->nUpChargeForNotAllocate2);
	pRs2->GetFieldValue("nUpChargeForNotAllocate3", pBi->nUpChargeForNotAllocate3);
	pRs2->GetFieldValue("bPopupFocus",				pBi->bPopupFocus);
	pRs2->GetFieldValue("bColorChange",				pBi->bColorChange);
	pRs2->GetFieldValue("bOnlyLoadInsRider",		pBi->bOnlyLoadInsRider);
	pRs2->GetFieldValue("nBranchDiscount",			pBi->nBranchDiscount);
	pRs2->GetFieldValue("bVRAccountNoRider",		pBi->bVRAccountNoRider);
	pRs2->GetFieldValue("sDDD",						pBi->strDDD);
	pRs2->GetFieldValue("bDongPosLiUse",			pBi->bDongPosLiUse);

	pRs2->GetFieldValue("nBikeWeatherCharge",		pBi->nBikeAddWeather);
	pRs2->GetFieldValue("nDamaWeatherCharge",		pBi->nDamaAddWeather);
	pRs2->GetFieldValue("nLaboWeatherCharge",		pBi->nLaboAddWeather);
	pRs2->GetFieldValue("nVanWeatherCharge",		pBi->nVanAddWeather);
	pRs2->GetFieldValue("nTruckWeatherCharge",		pBi->nTruckAddWeather);
	pRs2->GetFieldValue("bWeatherCharge",		pBi->bWeatherCharge);

	pRs2->GetFieldValue("nBikeWeatherChargeSnow",		pBi->nBikeAddWeatherSnow);
	pRs2->GetFieldValue("nDamaWeatherChargeSnow",		pBi->nDamaAddWeatherSnow);
	pRs2->GetFieldValue("nLaboWeatherChargeSnow",		pBi->nLaboAddWeatherSnow);
	pRs2->GetFieldValue("nVanWeatherChargeSnow",		pBi->nVanAddWeatherSnow);
	pRs2->GetFieldValue("nTruckWeatherChargeSnow",		pBi->nTruckAddWeatherSnow);
	pRs2->GetFieldValue("bWeatherChargeSnow",		pBi->bWeatherChargeSnow);
	pRs2->GetFieldValue("nSlowDiscount",		pBi->nSlowDiscount);
	pRs2->GetFieldValue("nCnsSearchType1",		pBi->nCnsSearchType1);
	pRs2->GetFieldValue("nCnsSearchType2",		pBi->nCnsSearchType2);
	pRs2->GetFieldValue("nCnsSearchPaid",		pBi->nCnsSearchPaid);
	pRs2->GetFieldValue("init_dt1_state_to_rcp", pBi->init_dt1_state_to_rcp);
}

void CLogonDlg::RefreshUserDongPos()
{
	BOOL bUserDongPos = FALSE;

	for(int i = 0; i < m_ba.GetCount(); i++)
	{
		CBranchInfo *pBi = m_ba.GetAt(i);

		if(pBi->bIntegrated)
			continue;

		if(pBi->bUserDongPos)
		{
			bUserDongPos = TRUE;
			break;
		}
	}

	//by mksong (2010-12-10 오후 8:42) 메모리 크래시발생

	if(bUserDongPos)
		m_mapUDongPos.FillData(m_ci.m_nCompanyCode);
}
void CLogonDlg::LoadConsignShare(CBranchInfo *pBi)
{

	
	COMPANY_APPLY_FROM_CITY_MAP3::iterator it;
	it = m_mapConCitySetting.find(pBi->strCity);
	if(it == m_mapConCitySetting.end())
		m_mapConCitySetting.insert(COMPANY_APPLY_FROM_CITY_MAP3::value_type(pBi->strCity, pBi));

}
void CLogonDlg::RefreshOnlyLoadGroup()
{	
	m_cg.FillCharge();
	m_cg.FillData();
}

void CLogonDlg::OnBnClickedCloseBtn()
{
	CMyDialog::OnCancel();
}

void CLogonDlg::OnBnClickedOkBtn()
{
	OnOK();
}

void CLogonDlg::OnBnClickedRemoteBtn()
{
	CRemoteAddrDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		LU->RunRemoteControl(dlg.m_nApplyRemote + 1);
	}
}

void CLogonDlg::OnBnClickedCancelBtn()
{
	CMyDialog::OnCancel();
}

BOOL CLogonDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->hwnd == m_BackStatic.GetSafeHwnd() ||
		pMsg->hwnd == this->GetSafeHwnd())
	{
		static BOOL bMouseDown = FALSE;
		static CPoint ptMouse;

		if(pMsg->message == WM_LBUTTONDOWN)
		{
			CRect rcClient;
			GetWindowRect(&rcClient);
			GetCursorPos(&ptMouse);
			if(rcClient.PtInRect(ptMouse))
			{
				SetCapture();
				bMouseDown = TRUE;
			}
		}
		else if(pMsg->message == WM_LBUTTONUP)
		{
			if(bMouseDown)
			{
				ReleaseCapture();
				bMouseDown = FALSE;
			}
		}
		else if(pMsg->message == WM_MOUSEMOVE)
		{
			if(bMouseDown)
			{
				CPoint ptMouse2;
				CRect rcClient;
				GetCursorPos(&ptMouse2);

				GetWindowRect(&rcClient);
				rcClient.OffsetRect(ptMouse2 - ptMouse);
				MoveWindow(rcClient);
				ptMouse = ptMouse2;
			}
		}
	}
	return CMyDialog::PreTranslateMessage(pMsg);
}

void CLogonDlg::OnBnClickedHpauthButton()
{
	UpdateData(TRUE);

	CNewCertifyDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_strID = dlg.m_strID;
		m_strPW = "";
	}
}

void CLogonDlg::SetVersionInfo()
{
	m_stcVersion.SetWindowText(LF->GetMyFileVersion());
}

void CLogonDlg::RefreshMent()
{
#ifndef _LOGIDB2012
	m_stcMent.SetWindowText("SmartQ with Cargo\n");
	m_stcMent2.SetWindowText("There are 3 things inevitable in life: death, tax and software bugs");
#else 
	m_stcMent.SetWindowText("새로운 업데이트 서버와 DB모듈 적용 버전입니다.");
	m_stcMent2.SetWindowText("have a good time!");
#endif

}

void CLogonDlg::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == 0)
	{
		KillTimer(nIDEvent);

		m_ei.nPCNum = AfxGetApp()->GetProfileInt("Daeri", "ClientNo", 0);
		if(m_ei.nPCNum <= 0)
		{
			MessageBox("인증되지 않은 PC입니다.\n\n"\
				"확인버튼을 누르시면 인증메뉴로 넘어갑니다.", 
				"미인증상태", MB_ICONINFORMATION);

			OnBnClickedHpauthButton();
		}
	}

	CMyDialog::OnTimer(nIDEvent);
}

HBRUSH CLogonDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd == &m_stcMent2)
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		return m_HandleManager.GetBrushObject(0, TRUE);
	}
	else if(pWnd == &m_stcMent)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(m_FontManager.GetFont("맑은 고딕", 16, FW_BOLD));
		return m_HandleManager.GetBrushObject(0, TRUE);
	}
	else if(pWnd == &m_stcVersion)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(m_FontManager.GetFont("맑은 고딕", 14, FW_BOLD));
		return m_HandleManager.GetBrushObject(0, TRUE);
	}

	return hbr;
}

void CLogonDlg::MakeLineGroupMap()
{
	for(int i = 0; i < m_ba.GetCount(); i++)
	{
		CBranchInfo *pBi = m_ba.GetAt(i);
		if(pBi->bIntegrated)
			continue;

		CString strLineGroup = pBi->strLineGroup + ",";

		long nStartPos = 0;

		for(int n = 0; n < strLineGroup.GetLength(); n++)
		{
			if(strLineGroup.GetAt(n) == ',')
			{
				if(n - nStartPos > 0)
				{
					CString strPart = strLineGroup.Mid(nStartPos, n - nStartPos);
					int nDashPos;
					if((nDashPos = strPart.Find("~")) <= 0)
					{
						m_LineGroup[strPart] = m_ba.GetAt(min(max(i, 1), m_ba.GetCount()-1));
						//g_bana_log->Print("%d = %s (a)\n", max(i, 1), strPart);
					}
					else
					{
						int nFrom = atol(strPart.Left(nDashPos));
						int nTo = atol(strPart.Right(strPart.GetLength() - nDashPos - 1));

						for(int k = nFrom; k <= nTo; k++)
						{
							CString strLine;
							strLine.Format("%d", k);

							if(m_LineGroup.find(strLine) == m_LineGroup.end())
							{
								m_LineGroup[strLine] = m_ba.GetAt(min(max(i, 1), m_ba.GetCount()-1));
								//g_bana_log->Print("%d = %s (b)\n", max(i, 1), strLine);
							}
						}
					}
				}
				nStartPos = n+1;
			}
		}
	}
}

void CLogonDlg::UpdateRegionInfo()
{
	//if(m_ci.m_nShareCode5 == 9999)
	//	m_ci.m_bCapitalArea = TRUE;
	//else 
	if(m_ci.m_strCity == "서울" ||
		m_ci.m_strCity == "경기" || 
		m_ci.m_strCity == "인천" ||
		m_ci.m_strCity == "수원" || 
		m_ci.m_strCity == "용인" ||
		m_ci.m_strCity == "고양" ||
		m_ci.m_strCity == "일산" ||
		m_ci.m_strCity == "분당" ||
		m_ci.m_strCity == "성남" ||
		m_ci.m_strCity == "이천" ||
		m_ci.m_strCity == "구리" ||
		m_ci.m_strCity == "파주" ||
		m_ci.m_strCity == "안양" ||
		m_ci.m_strCity == "안산" ||
		m_ci.m_strCity == "시흥" ||
		m_ci.m_strCity == "화성" ||
		m_ci.m_strCity == "천안" ||
		m_ci.m_strCity == "의정부") 
	{
		m_ci.m_bCapitalArea = TRUE;
	}
	else
		m_ci.m_bCapitalArea = FALSE;
}

void CLogonDlg::SetCarTypeOrder(CBranchInfo* pBi, CString strCarTypeOrder)
{
	if(LF->GetCommaCount(strCarTypeOrder) == 5)// && strCarTypeOrder.GetLength() == 10)
	{ 
		long nCarType = ZERO;
		long nFirstFind = ZERO;
		long nSecondFind = ZERO; 
		long nNewVisible = ZERO;

		for(int i = ZERO; i < 5; i++)
		{
			nSecondFind = strCarTypeOrder.Find(";", nFirstFind);
			nCarType = _ttoi(strCarTypeOrder.Mid(nFirstFind, nSecondFind - nFirstFind));

			if(i == ZERO)
				pBi->nCarType1 = nCarType;
			else if(i == ONE)
				pBi->nCarType2 = nCarType;
			else if(i == 2)
				pBi->nCarType3 = nCarType;
			else if(i == 3)
				pBi->nCarType4 = nCarType;
			else if(i == 4)
				pBi->nCarType5 = nCarType;

			nFirstFind = nSecondFind + 1;
		}
	}
	else if(LF->GetCommaCount(strCarTypeOrder) == 3)// && strCarTypeOrder.GetLength() == 6)
	{
		long nCarType = ZERO;
		long nFirstFind = ZERO;
		long nSecondFind = ZERO; 
		long nNewVisible = ZERO;

		for(int i=ZERO; i<3; i++)
		{
			nSecondFind = strCarTypeOrder.Find(";", nFirstFind);
			nCarType = _ttoi(strCarTypeOrder.Mid(nFirstFind, nSecondFind - nFirstFind));

			if(i == ZERO)
				pBi->nCarType1 = nCarType;
			else if(i == ONE)
				pBi->nCarType2 = nCarType;
			else if(i == 2)
				pBi->nCarType3 = nCarType;

			nFirstFind = nSecondFind + 1;
		}

		BOOL bFindCarType4 = FALSE;
		CString strTemp;
		for(int i = 0; i < 5; i++)
		{
			strTemp.Format("%d", i);
			if(strCarTypeOrder.Find(strTemp) == -1)
			{
				if(bFindCarType4 == FALSE)
				{
					pBi->nCarType4 = i;
					bFindCarType4 = TRUE;
				}
				else
				{
					pBi->nCarType5 = i;
					break;
				}
			}
		}
	}
	else
	{
		pBi->nCarType1 = CAR_AUTO;
		pBi->nCarType2 = CAR_DAMA;
		pBi->nCarType3 = CAR_LABO;
		pBi->nCarType4 = CAR_BIGBIKE;
		pBi->nCarType5 = CAR_TRUCK;
	}
}

void CLogonDlg::SetPayTypeOrder(CBranchInfo* pBi, CString strPayTypeOrder)
{
	if(LF->GetCommaCount(strPayTypeOrder) == 5 && strPayTypeOrder.GetLength() == 10)
	{ 
		long nPayType = ZERO;
		long nFirstFind = ZERO;
		long nSecondFind = ZERO; 
		long nNewVisible = ZERO;

		for(int i = ZERO; i < 5; i++)
		{
			nSecondFind = strPayTypeOrder.Find(";", nFirstFind);
			nPayType = _ttoi(strPayTypeOrder.Mid(nFirstFind, nSecondFind - nFirstFind));

			if(i == ZERO)
				pBi->nPayType1 = nPayType;
			else if(i == ONE)
				pBi->nPayType2 = nPayType;
			else if(i == 2)
				pBi->nPayType3 = nPayType;
			else if(i == 3)
				pBi->nPayType4 = nPayType;
			else if(i == 4)
				pBi->nPayType5 = nPayType;

			nFirstFind = nSecondFind + 1;
		}
	}
	else if(LF->GetCommaCount(strPayTypeOrder) == 4 && strPayTypeOrder.GetLength() == 8)
	{
		long nPayType = ZERO;
		long nFirstFind = ZERO;
		long nSecondFind = ZERO; 
		long nNewVisible = ZERO;

		for(int i = ZERO; i < 4; i++)
		{
			nSecondFind = strPayTypeOrder.Find(";", nFirstFind);
			nPayType = _ttoi(strPayTypeOrder.Mid(nFirstFind, nSecondFind - nFirstFind));

			if(i == ZERO)
				pBi->nPayType1 = nPayType;
			else if(i == ONE)
				pBi->nPayType2 = nPayType;
			else if(i == 2)
				pBi->nPayType3 = nPayType;
			else if(i == 3)
				pBi->nPayType4 = nPayType;

			nFirstFind = nSecondFind + 1;
		}

		CString strTemp;
		for(int i = 0; i < 5; i++)
		{
			strTemp.Format("%d", i);
			if(strPayTypeOrder.Find(strTemp) == -1)
			{
				pBi->nPayType5 = i;
				break;
			}
		}
	}
	else
	{
		pBi->nPayType1 = PAY_PRE;
		pBi->nPayType2 = PAY_AFTER;
		pBi->nPayType3 = PAY_CREDIT;
		pBi->nPayType4 = PAY_ONLINE;
		pBi->nPayType5 = PAY_CARD;
	}
}
						