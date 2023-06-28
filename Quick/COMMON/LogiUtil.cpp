#include "StdAfx.h"
#include "resource.h"
#include "LogiUtil.h"
#include "ShareReportRateDlg.h"
#include "LogonDlg.h"
#include "MyMkMessenger.h"
#include "TaskbarNotifier.h"
#include "NotifierContainer.h"
#include "GlobalDef.h"
#include "BillDlg.h"
#include "HomeView.h"
#include "DummyView.h"
#include "AllocatePaneDlg.h"
#include "RecvCidDlg.h"
#include "RcpView.h"
#include "VirtualRecord.h"
#include "MyXTPTaskPanelPaintManager.h"
#include "ChangeColorDlg.h" 
#include "MakeRiderStat.h"
#include "ShowRiderInfoDlg.h"
#include "SimpleMapDlg.h"
#include "RcpDlgMapDlg.h"
#include "AllocateBoardDlg.h"
#include "AllocateBoardTRSDlg.h"
#include "RiderMapDlg.h"
#include "POIDataNew.h"
#include "RiderShareBoardDlg.h"
#include "AllocateDlg.h"
#include "OtherRiderDlg.h"
#include "CallPhoneDlg.h"
#include "SearchPOIDlg.h"
#include "RcpPlaceInfo.h"
#include "POIDataNew.h"
#include "POIBoundary.h"
#include "ChargeAdd.h"
#include "LogiMapCns.h"
#include "SecurityLogDlg.h"
#include "ChargeHistoryMemDlg.h"
#include "ChargeContainer.h"
#include "OrderProcessStateDlg.h"
#include "MakePOIData.h"
#include "CustomerData.h"
#include "ConsignLinkDlg.h"
#include "FunctionTableDlg.h"
#include "ConnListDlg2.h"
#include "GroupChatDlg.h"
#include "MakeGroupReportNewDlg.h"
#include "RoadAddress.h"
#include "TransInfoDlg.h"
#include "RiderBoardDlg.h"
#include "ChargeForRiderLogDlg.h"
#include "afxinet.h"
#include "CSmtp.h"


CLogiUtil::CLogiUtil(void)
{
	m_nTodayCompleteCount = 0;
	m_nYesterDayCompleteCount = 0;

	m_pFrameWnd = NULL;
	m_pMsg = NULL;
	m_bDebugMode = FALSE;
	m_pwndNotifierContainer = NULL;
	m_pwndTaskbarNotifier = NULL;
	m_pwndSplitter = NULL;
	m_pwndFieldChooser = NULL;
	m_nTimeOfCheckNotice = 0;

	m_pRcpView = NULL;
	m_pReportView = NULL;
	m_pReportRiderView = NULL;
	m_pCustomerView = NULL;
	m_pStaffView = NULL;
	m_pIncomeView = NULL;
	m_pStatView = NULL;
	m_pHomeView = NULL;
	
	m_pEmptyCarPane = NULL;
	m_pDelayOrderPane = NULL;
	m_pAllocatePane = NULL;

	m_pwndPaneNetwork = NULL;
	m_pwndPane2 = NULL;
	m_pwndPane3 = NULL; 
	m_pwndPane4 = NULL;
	m_pwndPane5 = NULL;
	m_pwndPane6 = NULL;
	m_pwndPane7 = NULL;
	m_nCurView = 0;
	m_pRecvCidDlg = NULL;
	m_bRecvRiderPosMsg = FALSE;
	m_pwndTaskPanel = NULL;
	m_pwndCur = NULL;
	m_pRiderInfoDlg = NULL;
	m_pSimpleMapDlg = NULL;
	m_pRcpDlgMapDlg = NULL;
	m_pRiderMapDlg = NULL;
	m_pRiderMapDlg2 = NULL;
	m_pAllocateBoardDlg = NULL;
	m_pAllocateBoardTRSDlg = NULL;
	m_pRiderShareBoardDlg = NULL;
	m_pRiderBoardDlg = NULL;
	m_pAllocateDlg = NULL;
	m_pOtherRiderDlg = NULL;
	m_pCallPhoneDlg = NULL;
	m_pSearchPOIDlg = NULL;
	m_pLogiMapCns = NULL;
	m_pChargeHistoryMemDlg = NULL;
	m_pChargeAdd = NULL;
	m_pChargeContainer = NULL;
	m_pOrderProcessStateDlg = NULL;
	m_dtCur = COleDateTime::GetCurrentTime();
	m_pConsignLinkDlg		= NULL;
	m_pTransInfoDlg			= NULL;
	for(int i = 0; i < 5; i++)
		m_pMakeGroupReportNewDlg[i] = NULL;

	m_pFunctionTableDlg= NULL;
	m_pConnListPane = NULL;
	m_pGroupChatPane = NULL;
	m_ei.dwProgramStartTick = GetTickCount();
}

CLogiUtil::~CLogiUtil(void)
{
	//여기 호출시점이, CMainFrame이 종료된 후라서, 인스탄스 소멸 문제로 종료시 에러발생할 수 있음
	//그래서 Destroy를 CMainFrame OnClose에서 먼저 호출함
	Destroy();
}

void CLogiUtil::Destroy()
{
	AddSpecialLog("프로그램종료중 CLogiUtil::Destroy()");
	XTPSkinManager()->LoadSkin(NULL); //꼭 있어야함 없으면 종료시 에러 choe

	DELETE_OBJECT(m_pMsg);
	DELETE_OBJECT(m_pRecvCidDlg);
	DELETE_OBJECT(m_pRiderInfoDlg);
	DELETE_OBJECT(m_pSimpleMapDlg);	
	DELETE_OBJECT(m_pRcpDlgMapDlg);	
	DELETE_OBJECT(m_pwndNotifierContainer);
	DELETE_OBJECT(m_pwndTaskbarNotifier);
	DELETE_OBJECT(m_pwndSplitter);
	DELETE_OBJECT(m_pwndFieldChooser);
	DELETE_OBJECT(m_pRecvCidDlg);
	DELETE_OBJECT(m_pwndTaskPanel);
	DELETE_OBJECT(m_pRiderMapDlg);
	DELETE_OBJECT(m_pRiderMapDlg2);
	DELETE_OBJECT(m_pAllocateBoardDlg);
	DELETE_OBJECT(m_pAllocateBoardTRSDlg);
	DELETE_OBJECT(m_pRiderShareBoardDlg);
	DELETE_OBJECT(m_pRiderBoardDlg);
	DELETE_OBJECT(m_pAllocateDlg);
	DELETE_OBJECT(m_pOtherRiderDlg);
	DELETE_OBJECT(m_pCallPhoneDlg);
	DELETE_OBJECT(m_pChargeHistoryMemDlg);
	DELETE_OBJECT(m_pChargeContainer);
	DELETE_OBJECT(m_pOrderProcessStateDlg);
	DELETE_OBJECT(m_pConsignLinkDlg);
	//DELETE_OBJECT(m_pMakeGroupReportNewDlg);
	DELETE_OBJECT(m_pFunctionTableDlg);
	DELETE_OBJECT(m_pTransInfoDlg);
	
	m_pMakeGroupReportNewDlg;
}

BOOL CLogiUtil::Init()
{
	//SoftICE로 해킹중인지 확인
	if(LF->IsSoftIce95() || LF->IsSoftIceNT())	return FALSE;
	CheckDpiRegistry(LF->GetMyFileName());


	//소켓 초기화
	if(!m_SockSystem.Initialised()) 
	{
		AfxMessageBox("네트워크 초기화 실패(관리자에게 문의 바람!!)", MB_ICONERROR);
		return FALSE;
	}

	CLogiMapBase::RegisterMapDll();

	return TRUE;
}

void CLogiUtil::CheckDpiRegistry(LPCSTR lpExeFileName)
{
	HKEY hKey;
	LONG lRes; 

	lRes = RegOpenKeyEx(
		HKEY_CURRENT_USER,
		"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers",
		0, KEY_WRITE,
		&hKey);

	if (lRes != ERROR_SUCCESS) {
		lRes = RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers", 0, "", 0,
			KEY_READ | KEY_WRITE, NULL, &hKey, 0);
	}

	CString strDpiData = "~ PERPROCESSSYSTEMDPIFORCEOFF";
	LONG nSize = strDpiData.GetLength();
	char szData[50] = { 0x00, };
	strncpy_s(szData, _countof(szData), strDpiData, strDpiData.GetLength());


	lRes = RegSetValueEx(hKey,
		lpExeFileName,
		0,
		REG_SZ,
		(CONST BYTE*)(LPCTSTR)szData,
		nSize + 1);

	RegCloseKey(hKey);

	if (lRes != ERROR_SUCCESS)
		return;
}

void CLogiUtil::CheckDebugLogMode()
{
	m_bDebugMode = AfxGetApp()->GetProfileInt("Quick", "DebugMode", 0) == 91;

	if(m_bDebugMode)
	{
		g_bana_log = new CBanaLog;
		g_bana_log->SetFile(LF->GetModuleFullPath() + "LOG.TXT", true);
		g_bana_log->SetMode(CBanaLog::TO_CONSOLE | CBanaLog::TO_FILE);
		LF->RepositionLogConsole();
	}
}

BOOL CLogiUtil::IsDebugMode()
{
	return m_bDebugMode;
}

void CLogiUtil::InstallMalgunFont()
{
	CXTFontList& fontList = CXTFontEnum::Get().GetFontList();

	BOOL bExist = FALSE;
	POSITION pos;
	for (pos = fontList.GetHeadPosition(); pos; fontList.GetNext(pos))
	{
		CXTLogFont& lf = fontList.GetAt(pos);
		if(0 == strcmp(lf.lfFaceName, "맑은 고딕"))
		{
			bExist = TRUE;			
			return;
		}
	}

	if(!bExist)
	{
		if(AddFontResource(LF->GetModuleFullPath() + "MALGUN.TTF"))
		{
			AddFontResource(LF->GetModuleFullPath() + "MALGUNBD.TTF");
		}
	}
}

BOOL CLogiUtil::Logon(char *szID)
{
	CLogonDlg dlg;
	dlg.m_strID = szID;
	dlg.m_strID.Replace("/", "");

	if(IDOK != dlg.DoModal() || !dlg.m_bAuth)
	{
		if(m_pMkDb)
			delete m_pMkDb;

		return FALSE;
	}

	if(dlg.m_strPW.IsEmpty()) 
		m_ui.bBlankPassword = TRUE; 

	char buffer[10];
	m_pMkDb->SetClientCode(ltoa(m_ci.m_nCompanyCode, buffer, 10));
	m_pMkDb->SetClientInfo(m_ci.m_nCompanyCode, m_ui.nWNo, m_ui.bDeveloper);


#ifdef _DEBUG
	m_pMkDb->SetDeveloperMode(1);
#else 
	m_pMkDb->SetDeveloperMode(m_ui.bDeveloper);
#endif 

	return TRUE;
}

void CLogiUtil::LogOutRestore()
{
	if(AfxGetMainWnd() && m_pMkDb->GetSafeHwnd() && m_pMkDb->GetSocket()->IsConnected())
	{
		BOOL bLogiMember = m_ui.bDeveloper || m_ui.bBlankPassword;
		CString strLocalVer = LF->GetMyFileVersion();

		CMkCommand cmd(m_pMkDb, "update_wno_log_out_restore");
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ci.GetShareCode1());
		cmd.AddParameter(strLocalVer);
		cmd.AddParameter(bLogiMember);
		cmd.Execute();
	}
}

void CLogiUtil::SaveLogOut(BOOL bRuntimeError)
{
	//static BOOL bOnce = FALSE;

	//if(bOnce == TRUE)
	//	return;

	//bOnce = TRUE;

	if(AfxGetMainWnd() && m_pMkDb->GetSafeHwnd() && m_pMkDb->GetSocket()->IsConnected())
	{
		BOOL bLogiMember = m_ui.bDeveloper || m_ui.bBlankPassword;
		CString strLocalVer = LF->GetMyFileVersion();

		CMkCommand cmd(m_pMkDb, "update_wno_log_out2");
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ci.GetShareCode1());
		cmd.AddParameter(bRuntimeError);
		cmd.AddParameter(strLocalVer);
		cmd.AddParameter(bLogiMember);
		cmd.Execute();
	}
}

BOOL CLogiUtil::ShowShareReportDlg()
{
#ifndef _STANDALONE
	if(m_ci.m_bUseShareReport)
	{
		if(m_ci.m_bRcpIntMode1 && LF->POWER_CHECK(1760, "공유콜 정산"))
		{
			if(!CShareReportRateDlg::IsNoShow())
			{
				CShareReportRateDlg dlgShareRate;
				dlgShareRate.m_bInitializing = TRUE;
				dlgShareRate.DoModal();
				if(dlgShareRate.m_bExitPrg)
					return FALSE;
			}
		} 
	}
#endif
	return TRUE;
}


BOOL CLogiUtil::SetServerInfo()
{
	//m_si.strRealMainServerAddr = "211.172.242.189"; // L4 3500 서비스 
	m_si.strRealMainServerAddr = "121.254.252.14"; // L4 3500 서비스 	
	m_si.nRealMainServerPort = 3500;


	m_ui.bBlankPassword = FALSE;
	m_si.strMsgServerAddr = "211.172.242.182"; //추후 아래로 바꿔야함 20230410 choe
	//m_si.strMsgServerAddr = "121.254.252.26"; 
	m_si.nMsgServerPort = 5510;

	m_pMkDb = new CMkDatabase(g_bana_log);
	//m_pMkDb->AddDisServer(m_si.strRealMainServerAddr, 3500);  // l4 죽을시 직접붙게 추가
	//m_pMkDb->AddDisServer("121.254.252.6", 3500);  // l4 죽을시 직접붙게
	//m_pMkDb->AddDisServer("121.254.252.26", 3500);  // l4 죽을시 직접붙게 추가


	BYTE nXorKey = (m_pMkDb->GetXorKey() + 3) % 128;
	BYTE des_key_new[] = { 29,44,2,83,32,98,10,8 };
	BYTE nXoredKey[8];

	for (int i = 0; i < 8; i++)
		nXoredKey[i] = des_key_new[i] ^ ((nXorKey + i) % 128);
	m_pMkDb->SetServerKey(nXoredKey);

	if (!m_pMkDb->Open(m_si.strRealMainServerAddr, m_si.nRealMainServerPort)) {
		g_bana_log->Print("database 연결실패(%s,%d)\n", m_pMkDb->GetCurServerAddr(), m_pMkDb->GetCurServerPort());
		AfxMessageBox("데이터베이스 연결 실패", MB_ICONERROR);

		delete m_pMkDb;
		return FALSE;
	}
	else
	{

		g_bana_log->Print("database 연결됨(%s,%d)\n", m_pMkDb->GetCurServerAddr(), m_pMkDb->GetCurServerPort());
	}

	CMakeRcpPower::GetPower();

	m_pMkDb2 = new CMkDatabase(g_bana_log);
	nXorKey = (m_pMkDb2->GetXorKey() + 3) % 128;
	for (int i = 0; i < 8; i++)
		nXoredKey[i] = des_key_new[i] ^ ((nXorKey + i) % 128);
	m_pMkDb2->SetServerKey(nXoredKey);


	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_messenger_ip");
	CMkParameter* pParIp = pCmd.AddParameter(typeString, typeOutput, 100, 0);
	CMkParameter* pParPort = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if (pRs.Execute(&pCmd)) {
		pParIp->GetValue(m_si.strMsgServerAddr);
		int port = 0;
		pParPort->GetValue(port);
		m_si.nMsgServerPort = port;
	}


	return TRUE;
}

BOOL CLogiUtil::CheckCommandLine(char *szID, char *szLogiCode, char *szLogiNo)
{
	int nArgc = 0;

	LPCTSTR ppArgv = (LPCTSTR)GetCommandLine();

	if(strstr(ppArgv, "/run") == NULL)
	{
#ifndef _DEBUG
		if(!IsDebugMode())
		{
			CString strPath = LF->GetModuleFullPath();
			strPath += "update.exe";
			if(!LF->RunProgram(strPath, "/run"))
				MessageBox("업데이트 프로그램을 찾을 수 없습니다.\n업데이트 체크없이 프로그램을 시작합니다.",
				"업데이트 실패", MB_ICONERROR);
			else
				return FALSE;
		}
#endif
	}
	else {
		char szFileName[MAX_PATH] = { 0 };
		char szRun[50] = { 0 };	

		sscanf(ppArgv, "%s %s %s %s %s", szFileName, szRun, szID, szLogiCode, szLogiNo);
		g_bana_log->Print("%s %s %s %s %s", szFileName, szRun, szID, szLogiCode, szLogiNo);
	}

	return TRUE;
}

void CLogiUtil::CheckRegistryInfo()
{
	FILETIME ft;
	m_ei.nGlobalMsgVer = AfxGetApp()->GetProfileInt("SimpleInfo", "GlobalMsgVer", -1);
	m_ei.nLocalMsgVer = AfxGetApp()->GetProfileInt("SimpleInfo", "LocalMsgVer", -1);
	ft.dwHighDateTime =  AfxGetApp()->GetProfileInt("Quick", "ForceExitHigh", 0);
	ft.dwLowDateTime =  AfxGetApp()->GetProfileInt("Quick", "ForceExitLow", 0);

	if(ft.dwHighDateTime == 0)
		m_ei.dtForceExitTime = COleDateTime::GetCurrentTime() + COleDateTimeSpan(100, 0, 0, 0);
	else
		m_ei.dtForceExitTime = COleDateTime(ft);

}

#define SPI_SETFONTSMOOTHINGTYPE            0x200B
#define FE_FONTSMOOTHINGCLEARTYPE           0x0002
#define SPI_SETFONTSMOOTHINGCONTRAST           0x200D

void CLogiUtil::SetClearType()
{
	SystemParametersInfo(SPI_SETFONTSMOOTHING,
		TRUE,
		0,
		SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
	SystemParametersInfo(SPI_SETFONTSMOOTHINGTYPE,
		FE_FONTSMOOTHINGCLEARTYPE,
		0,
		SPIF_UPDATEINIFILE | SPIF_SENDCHANGE); 

	SystemParametersInfo(SPI_SETFONTSMOOTHINGCONTRAST,
		1600,
		0,
		SPIF_UPDATEINIFILE | SPIF_SENDCHANGE); 
}

void CLogiUtil::SetSystemTimeLikeServer()
{
	COleDateTime curtime;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_server_time4", TRUE);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), 0);
	if(!pRs.Execute(&pCmd)) return;
	pRs.GetFieldValue("utc", curtime);
	pRs.GetFieldValue("std", m_ei.dtServerTime);

	SYSTEMTIME st;
	curtime.GetAsSystemTime(st);
	SetSystemTime(&st);
	pRs.Close();
}

void CLogiUtil::SetWindowTitleWithVersion()
{
	CString strVersion;
	strVersion.Format("로지소프트 스마트Q ⓥ%s(%s)  %s",
		LF->GetMyFileVersion(),
		m_ci.m_strUsePrgVersion,
		m_ci.m_strName);

	m_pFrameWnd->SetWindowText(strVersion);
	m_strOriginalWindowTitle = strVersion;
	m_ei.strProgramVersion.Format("ⓥ%s", LF->GetMyFileVersion());
}

void CLogiUtil::StartMessenger(BOOL bIgnoreLogiMemberLogin)
{
	CMyMkMessenger *pOldMsg = m_pMsg;

	MESSENGER_SET_INFO *pmi = new MESSENGER_SET_INFO;

	if(!m_ui.bBlankPassword || bIgnoreLogiMemberLogin)
	{
		pmi->nCompanyCode = m_ci.m_nCompanyCode;
		pmi->nUserCode = m_ui.nWNo;
		pmi->strCompanyName = m_ci.m_strName;
		pmi->strBranchName = m_ci.m_strBranchName;
		pmi->strUserName = m_ui.strName;
		pmi->nShareCode1 = m_ci.m_nShareCode1;
		pmi->nShareCode2 = m_ci.m_nShareCode2;
		pmi->nShareCode3 = m_ci.m_nShareCode3;
		pmi->nShareCode4 = m_ci.m_nShareCode4;
		pmi->nShareCode5 = m_ci.m_nShareCode5;
		pmi->nShareCode6 = -1;
		pmi->nShareCode7 = -1; 
		pmi->nShareCode8 = -1;
		pmi->nShareCode9 = -1;
		pmi->nShareCode10 = -1;
	}
	else
	{
		srand((unsigned)time(NULL));
		pmi->nCompanyCode = 1 + rand() % 999;
		g_bana_log->Print("Messenger Random id: %d\n", pmi->nCompanyCode);
		pmi->nUserCode = m_ci.m_nCompanyCode;
		pmi->strCompanyName = "로지소프트";
		pmi->strBranchName = "로지소프트";
		pmi->strUserName = "테스트";
		pmi->nShareCode1 = 383;
		pmi->nShareCode2 = -1;
		pmi->nShareCode3 = -1;
		pmi->nShareCode4 = -1;
		pmi->nShareCode5 = -1;
		pmi->nShareCode6 = -1;
		pmi->nShareCode7 = -1;
		pmi->nShareCode8 = -1;
		pmi->nShareCode9 = -1;
		pmi->nShareCode10 = -1;
	}

	pmi->nMsgGroupCode = 0;
	pmi->bManager = 0;
	pmi->bIdle = 0;
	pmi->nDisplayType = 0;
	pmi->strMsgServerAddr = m_si.strMsgServerAddr;
	pmi->nMsgServerPort = m_si.nMsgServerPort;

	m_pMsg = new CMyMkMessenger(m_pFrameWnd);

	m_pMsg->SetRecvIntercall(AfxGetApp()->GetProfileInt("RcpPage", "RecvIntercall", 0), 0);
	m_pMsg->SetRecvAllocMsg(AfxGetApp()->GetProfileInt("RcpPage", "RecvAllocMsg", 0), 0);

	m_pMsg->SetNotiferContainer(m_pwndNotifierContainer);
	m_pMsg->SetMessengerInfo(pmi);
	m_pMsg->SetInputTimeVar(&LF->m_dwLastInput);
	
	if(pOldMsg)
	{
		m_pMsg->SetRecvRiderPosMsg(pOldMsg->GetRecvRiderPosMsg(), FALSE);
		pOldMsg->CopyRecvRiderPosArray(m_pMsg);
		DELETE_OBJECT(pOldMsg);
	}

	m_pMsg->Connect();
}

void CLogiUtil::InitNofityContainer()
{
	//메신저 박스 설정
	m_pwndTaskbarNotifier = new CTaskbarNotifier;
	m_pwndTaskbarNotifier->Create(m_pFrameWnd);
	m_pwndTaskbarNotifier->SetSkin(IDB_SKIN_NOTICE);
	m_pwndTaskbarNotifier->SetTextFont("Arial",90,TN_TEXT_NORMAL,TN_TEXT_UNDERLINE);
	m_pwndTaskbarNotifier->SetTextColor(RGB(0,0,0),RGB(0,0,200));
	m_pwndTaskbarNotifier->SetTextRect(CRect(10, 40,
		m_pwndTaskbarNotifier->m_nSkinWidth - 10,
		m_pwndTaskbarNotifier->m_nSkinHeight - 25));

	m_pwndNotifierContainer = new CNotifierContainer;
	m_pwndNotifierContainer->Create(m_pFrameWnd);
}

void CLogiUtil::InitFieldChooser()
{
#ifndef _STANDALONE
	if(!m_pwndFieldChooser)
	{
		m_pwndFieldChooser = new CDialogBar;

		if(!m_pwndFieldChooser->Create(m_pFrameWnd, IDD_COL_SELECT_DLG,
			CBRS_LEFT|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE, ID_TEST_FIELDCHOOSER))
			return;      // fail to create

		m_pwndFieldChooser->EnableDocking(0);
		m_pwndFieldChooser->SetWindowText(_T("컬럼 선택창"));

		((CFrameWnd*)m_pFrameWnd)->ShowControlBar(GetFieldChooser(), FALSE, FALSE);
		((CFrameWnd*)m_pFrameWnd)->FloatControlBar(GetFieldChooser(), 
			CPoint(100, GetSystemMetrics(SM_CYSCREEN) / 3));

	}
#else
	AfxMessageBox("STANDALONE 모드에서 [m_pwndFieldChooser]를 사용할 수 없습니다.");
#endif
}

CDialogBar* CLogiUtil::GetFieldChooser()
{
	return m_pwndFieldChooser;
}

void CLogiUtil::ShowBillDlg()
{
	if(!LF->POWER_CHECK(1750, "서비스 이용료 보기", TRUE))
		return;

	if(m_ci.m_nCompanyCode < 1000)
	{
		m_pFrameWnd->MessageBox("데모버전에서는 볼 수 없습니다.", "권한없음", MB_ICONINFORMATION);
		return;

	}

	CBillDlg dlg;
	COleDateTime dtDate;
	COleDateTime dtCurrent = COleDateTime::GetCurrentTime();
	if(dtCurrent.GetMonth() == 1)
		dtDate.SetDate(dtCurrent.GetYear() - 1, 12, 1);
	else
		dtDate.SetDate(dtCurrent.GetYear(), dtCurrent.GetMonth() - 1, 1);

	dlg.m_nCompanyCode = m_ci.m_nCompanyCode;
	dlg.m_dtDate = dtDate;
	dlg.DoModal();
}

void CLogiUtil::ShowSecurityLogDlg()
{
	if(!LF->POWER_CHECK(1770, "보안로그 보기", TRUE))
		return;

	CSecurityLogDlg dlg;
	dlg.DoModal();
}

CXTSplitterWnd* CLogiUtil::GetSplitterWnd() 
{ 
	return m_pwndSplitter; 
}

BOOL CLogiUtil::CreateSplitter(CWnd *pWnd, CCreateContext *pContext)
{
#ifndef _STANDALONE
	m_pFrameWnd = pWnd;

	if(!m_pwndSplitter)
	{
		m_pwndSplitter = new CXTSplitterWnd;

		if (!m_pwndSplitter->CreateStatic(pWnd,1,2, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS))
			return FALSE;

		m_pwndSplitter->CreateView(0, 0, RUNTIME_CLASS(CHomeView), CSize(0, 0), pContext);
		m_pwndSplitter->CreateView(0, 1, RUNTIME_CLASS(CDummyView), CSize(0, 0), pContext);
		SetHomeView((CHomeView*)m_pwndSplitter->GetPane(0, 0));
		m_pwndSplitter->SetActivePane(0,0);
		m_pwndSplitter->SetColumnInfo( 1, 0, 0 );
		m_pwndSplitter->HideColumn(1);
		m_pwndSplitter->RecalcLayout();
		m_pwndSplitter->ModifyStyle(WS_BORDER, 0);
		m_pwndSplitter->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
	}
#endif
	return TRUE;
}

void CLogiUtil::LoadSkinManager()
{
	XTPSkinManager()->SetApplyOptions(xtpSkinApplyFrame | xtpSkinApplyColors | xtpSkinApplyMetrics);
	XTPSkinManager()->LoadSkin(LF->GetModuleFullPath() + _T("Styles\\LE5_3.cjstyles"), _T("NormalBlueC.ini"));
	XTPSkinManager()->SetAutoApplyNewThreads(FALSE);
}

void CLogiUtil::MakeRiderList()
{
	m_mapAllocateRider.clear();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_alloc_rider_list5");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), LF->GetCurBranchInfo()->bIntegrated);

	if(!pRs.Execute(&pCmd)) return;

	long lCode =0, nDeposit = 0;
	CString strHp = "", strBranchName = "", strName = "", strID = "";
	int nDepositType, nReleaseMin =0,  nMNo =0, nCarType = 0,nAllocGroup = 0,nLockTime= 0,nLockCount = 0,nWorkState=0;
	int nPanaltyTypeShowOrder = 0,nLockTime4MyOrder = 0,nLockCount4MyOrder=0,nLockTime4OCOrder=0, nLockCount4OCOrder =0 ; 
	COleDateTime dtEnter, dtWorkStateDate,dtAllocateLimitDate ;
	BOOL bGPSUsage = FALSE, bConnection = FALSE, bAllocateLimit = FALSE, bUseSMS = FALSE;
	long nAllocType = 0;
	CString strRTID;

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("sBranchName", strBranchName);
		pRs.GetFieldValue("lCode", lCode);
		pRs.GetFieldValue("nMNo", nMNo);	
		pRs.GetFieldValue("sName", strName);	
		pRs.GetFieldValue("dtEnter", dtEnter);	
		pRs.GetFieldValue("sID", strID);	
		pRs.GetFieldValue("sHp", strHp);
		pRs.GetFieldValue("nCarType", nCarType);
		//	pRs.GetFieldValue("nAllocGroup", nAllocGroup);
		pRs.GetFieldValue("nDepositType", nDepositType);
		pRs.GetFieldValue("nDeposit", nDeposit);	
		pRs.GetFieldValue("nLockTime", nLockTime);	
		pRs.GetFieldValue("nLockCount", nLockCount);	
		pRs.GetFieldValue("nWorkState", nWorkState);	
		pRs.GetFieldValue("dtWorkStateDate", dtWorkStateDate);	
		pRs.GetFieldValue("bAllocateLimit", bAllocateLimit);	
		pRs.GetFieldValue("dtAllocateLimitDate", dtAllocateLimitDate);	

		pRs.GetFieldValue("nReleaseMin", nReleaseMin);	
		pRs.GetFieldValue("nPanaltyTypeShowOrder", nPanaltyTypeShowOrder);	
		pRs.GetFieldValue("nLockTime4MyOrder",	nLockTime4MyOrder);	
		pRs.GetFieldValue("nLockCount4MyOrder", nLockCount4MyOrder);	
		pRs.GetFieldValue("nLockTime4OCOrder",	nLockTime4OCOrder);	
		pRs.GetFieldValue("nLockCount4OCOrder", nLockCount4OCOrder);	
		//pRs.GetFieldValue("bUseSMS", bUseSMS);	
		pRs.GetFieldValue("nAllocType", nAllocType);
		pRs.GetFieldValue("sRTID", strRTID);

		ST_ALLOC_RIDER *pRider = GetAllocRider(lCode, nMNo);

		if(pRider == NULL)
			return;

		pRider->strBranchName = strBranchName;
		pRider->lCode = lCode;
		pRider->nMNo = nMNo;
		pRider->strName = strName;
		pRider->dtEnter = dtEnter;
		pRider->strID = strID;
		pRider->strHp = strHp;
		pRider->nCarType = nCarType;
		pRider->nAllocGroup = nAllocGroup;
		pRider->nDepositType = nDepositType;
		pRider->nDeposit = nDeposit;
		pRider->nLockTime = nLockTime;
		pRider->nLockCount = nLockCount;
		pRider->nWorkState = nWorkState;
		pRider->dtWorkStateDate = dtWorkStateDate;
		pRider->bAllocateLimit = bAllocateLimit;
		pRider->dtAllocateLimitDate = dtAllocateLimitDate;
		pRider->nReleaseMin = nReleaseMin;
		pRider->nPanaltyTypeShowOrder = nPanaltyTypeShowOrder;
		pRider->nLockCount4MyOrder = nLockCount4MyOrder;
		pRider->nLockTime4MyOrder = nLockTime4MyOrder;
		pRider->nLockTime4OCOrder = nLockTime4OCOrder;
		pRider->nLockCount4OCOrder = nLockCount4OCOrder;
		pRider->strRTID = strRTID;
		pRider->nAllocType = nAllocType;	

		pRs.MoveNext();
	}

	if(m_pAllocatePane != NULL)
		m_pAllocatePane->InitRider();
}

void CLogiUtil::MakeAllocateGroup()
{
	m_mapAllocateGroup.clear();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_allocate_group");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	if(!pRs.Execute(&pCmd)) return;

	while(!pRs.IsEOF())
	{
		int nGNo;
		CString strName;

		pRs.GetFieldValue("nGNo", nGNo);
		pRs.GetFieldValue("sName", strName);
		m_mapAllocateGroup.insert(MAP_ALLOCATE_GROUP::value_type(nGNo, strName));
		pRs.MoveNext();
	}
	pRs.Close();
}


void CLogiUtil::MakeAllocateGroupCombo(CComboBox *pCombo, BOOL bAllInsert)
{
	pCombo->ResetContent();

	if(bAllInsert)
	{
		int nItem = pCombo->AddString("전체");
		pCombo->SetItemData(nItem, -1);
	}

	MAP_ALLOCATE_GROUP::iterator it;

	for(it = m_mapAllocateGroup.begin(); it != m_mapAllocateGroup.end(); it++)
	{
		int nItem = pCombo->AddString(it->second);
		pCombo->SetItemData(nItem, it->first);
	}
}

CString CLogiUtil::GetAllocateGroup(int nCurGroup)
{
	MAP_ALLOCATE_GROUP::iterator it = m_mapAllocateGroup.find(nCurGroup);

	for(it = m_mapAllocateGroup.begin(); it != m_mapAllocateGroup.end(); it++)
	{
		return it->second;
	}
	return "없는그룹";
}

void CLogiUtil::FillCompanyChargeList(CComboBox *pCombo)
{
	int nItem = 0, nCurItem = 0;
	long nOldMemCNo = 0;
	if(pCombo->GetCount() > 0)
		nOldMemCNo = pCombo->GetItemData(pCombo->GetCurSel());
	
	/*  의미없는 작업. ChargeDongCusMember 테이블에 bView가 대부분 NULL
	if(m_mapMemberCharge.size() > 0)
	{		
		pCombo->ResetContent();
		pCombo->InsertString(nItem, "적용안함");
		pCombo->SetItemData(nItem++, 0);
		MAP_MEMBER_CHARGE_CNO::iterator it;
		for(it = m_mapMemberCharge.begin(); it != m_mapMemberCharge.end(); ++it)
		{
			if(it->second->bView)
			{
				if(it->second->nMemCNo == nOldMemCNo)
					nCurItem = nItem;
				pCombo->InsertString(nItem, it->second->strMemCompany);
				pCombo->SetItemData(nItem++, it->second->nMemCNo);

			}
		}		
	}
	*/

	if(pCombo->GetCount() <= 1 )
	{
		pCombo->InsertString(nItem, "즐겨찾기미설정");
		
		pCombo->SetItemData(nItem++, -1);
		pCombo->PostMessage(CBN_SELCHANGE, 1,1);
		//pCombo->SetCurSel(1);
		return;
	}

	if(nOldMemCNo > 0 && nCurItem > 0)
		pCombo->SetCurSel(nCurItem);		
	else
		pCombo->SetCurSel(0);		
}


void CLogiUtil::UpdateAllocateGroup(int nGNo, CString strName)
{
	MAP_ALLOCATE_GROUP allocateMap;
	allocateMap.clear();
	MAP_ALLOCATE_GROUP::iterator it;

	for(it = m_mapAllocateGroup.begin(); it != m_mapAllocateGroup.end(); it++)
	{
		if(it->first==(long)nGNo)
			allocateMap.insert(MAP_ALLOCATE_GROUP::value_type(it->first, strName));
		else
			allocateMap.insert(MAP_ALLOCATE_GROUP::value_type(it->first, it->second));
	}
	m_mapAllocateGroup = allocateMap;
}

void CLogiUtil::MakeChargeSectionType()
{
	m_cst.clear();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_charge_section_type_all");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	if(!pRs.Execute(&pCmd)) return;

	while(!pRs.IsEOF())
	{
		CString strName;

		ST_CHARGE_SECTION_VALUE csv;

		pRs.GetFieldValue("nValueType", csv.nValueType);
		pRs.GetFieldValue("nClass", csv.nClass);
		pRs.GetFieldValue("nStartValue", csv.nStart);
		pRs.GetFieldValue("nEndValue", csv.nEnd);
		pRs.GetFieldValue("nAmount", csv.nAmount);

		m_cst.push_back(csv);

		pRs.MoveNext();
	}
	pRs.Close();
}

int CLogiUtil::GetChargeSectionValue(long nBasicCharge, long nDiscountCouPhoneMileType, long nABCDType, long nSectionValue)
{
	VEC_CHARGE_SECTION_TYPE::iterator it;
	long nChargeAddDis = 0;

	/*SELECT * 
	FROM ChargeSectionType
	where nCompany = 10
	and nValueType = 0  0 할인 1 쿠폰 2 마일리지 
	and nClass = 1  -- a, b, c, d*/

	for(it = m_cst.begin(); it != m_cst.end(); it++)
	{
		if(it->nValueType == nDiscountCouPhoneMileType && 
			it->nClass == nABCDType &&
			it->nStart <= nBasicCharge &&
			it->nEnd >= nBasicCharge)
		{
			if(0 > it->nAmount  && it->nAmount > -100)
				nChargeAddDis = -1 * (nBasicCharge *  (it->nAmount * -1)  * 0.01 ) ;
			else if(it->nAmount < -100 )				
				nChargeAddDis = it->nAmount;
			else if(it->nAmount > 0 && it->nAmount <= 100)
                nChargeAddDis = nBasicCharge *  it->nAmount *  0.01 ;
			else if(it->nAmount > 100 )
				nChargeAddDis = it->nAmount;
				
				
			return nChargeAddDis;
		}
	}

	return 0;
}

void CLogiUtil::SetCurView(UINT nCurView)
{
	m_nCurView = nCurView;
}

UINT CLogiUtil::GetCurView()
{
	return m_nCurView;
}

BOOL CLogiUtil::GetRightOfMessenger(BOOL bMsgBox)
{
	if(!m_ci.m_bUseInterCall)
	{
		if(bMsgBox)
			MessageBox("인터콜 미사용 상태입니다.\n로지소프트로 문의바랍니다.(1599-0707)", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	if(m_pMsg == NULL)
	{
		if(bMsgBox)
			MessageBox("메신저 미연결 상태입니다.", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

/* //by mksong (2011-07-28 오후 3:57)
	if(!m_pMsg->GetDatabase()->GetSocket()->SendData(PT_REQUEST, PST_INTERCALL_RECV, "1"))
	{
		MessageBox("인터콜 받기 설정 실패", "확인", MB_ICONINFORMATION);
		return FALSE;
	}


	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_receive_intercall");
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(TRUE);
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	if(!pCmd.Execute()) return FALSE;

	long nReturnValue = 0;
	pPar->GetValue(nReturnValue);

	if(nReturnValue < 0 )
	{
		MessageBox("인터콜및 메신져에 접수되어 있지 않습니다.", "확인", MB_ICONINFORMATION);
		return FALSE;
	}


	if(nReturnValue > 1)
	{
		if(MessageBox("인터콜 받는 메시지를 본인만 하시겠습니까?", "확인", MB_ICONINFORMATION || MB_YESNO) == IDYES)
		{
			CMkRecordset pRs(m_pMkDb);
			CMkCommand pCmd(m_pMkDb, "update_receive_intercall_alone");
			pCmd.AddParameter(m_ui.nCompany);
			pCmd.AddParameter(m_ui.nWNo);
			pCmd.Execute();
		}

	}
*/

	m_pMsg->SetRecvIntercall(TRUE);


	return TRUE;
}

BOOL CLogiUtil::ReleaseRightOfMessenger()
{
	if(!m_ci.m_bUseInterCall)
	{
		MessageBox("인터콜 미사용 상태입니다.\n로지소프트로 문의바랍니다.(1599-0707)", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	if(m_pMsg == NULL)
	{
		MessageBox("메신저 미연결 상태입니다.", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

/*//by mksong (2011-07-28 오후 4:07)
	if(!m_pMsg->GetDatabase()->GetSocket()->SendData(PT_REQUEST, PST_INTERCALL_RECV, "0"))
	{
		MessageBox("인터콜 받기 해제 실패", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_receive_intercall");
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(FALSE);
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	if(!pCmd.Execute()) return FALSE;

	long nReturnValue = 0;
	pPar->GetValue(nReturnValue);

	if(nReturnValue <= 1)
		MessageBox("인터콜 받는 접수자가 한분도 없습니다.", "확인", MB_ICONINFORMATION);
*/

	int nConnCount = m_pMsg->SetRecvIntercall(FALSE);

	if(nConnCount == 0)
		MessageBox("인터콜 오더접수 받는 분이 한분도 없습니다.", "확인", MB_ICONINFORMATION);
	
	g_bana_log->Print("nConnCount = %d\n", nConnCount);

	return TRUE;
}

void CLogiUtil::GetRightOfAllocation(BOOL bMsgBox)
{
	if(m_pMsg == NULL)
	{
		if(bMsgBox)
			MessageBox("메신저 미연결 상태입니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	if(!m_pMsg->SetRecvAllocMsg(TRUE))
	{
		if(bMsgBox)
			MessageBox("배차메시지 받기 설정 실패", "확인", MB_ICONINFORMATION);
	}
}

void CLogiUtil::ReleaseRightOfAllocation()
{
	if(m_pMsg == NULL)
		return;

	if(!m_pMsg->SetRecvAllocMsg(FALSE))
		MessageBox("배차메시지 받기 해제 실패", "확인", MB_ICONINFORMATION);
}

int CLogiUtil::MessageBox(CString strMsg, CString strCaption, UINT nType)
{
	return m_pFrameWnd->MessageBox(strMsg, strCaption, nType);
}

CBranchInfo* CLogiUtil::SearchLineGroup(char *szLine)
{
	MAP_LINE_GROUP::iterator it;
	it = m_LineGroup.find(szLine);
	if(it != m_LineGroup.end())
		return it->second;
	else
		return NULL;
}

void CLogiUtil::SendCIDInfo(char *szData)
{
	char szHead[10] = {0,}, szGroupID[10] = {0,}, szNumber[50] = {0,}, szChanel[10]={0,};
	char szLineID[20] = {0, };
	char szZipCode[50]= {0,};
	char szTemp[5] = {0,};
	BOOL bEnhancedMode = FALSE;
	CBranchInfo *pBi = NULL;

	if(szData[0] == 'F'|| szData[0] == 'B')
	{
		return;			
	}
	else if(szData[0] == 'E' || szData[0] == 'A' )
	{
		int nPos = 0;
		bEnhancedMode = TRUE;
		if(!(nPos = STRTOK(szData, 0, szHead, szGroupID, szNumber,szChanel, VL_END )))
		{				
			strcpy(szNumber, "");
			bEnhancedMode = FALSE;
		}
		else
		{
			if(!strcmp(szGroupID, "-1"))
				if(STRTOK(szData, nPos, szLineID, VL_END))
					pBi =  SearchLineGroup(szLineID);
		}
	}
	else if(szData[0] == 'D')  //발신자 리스트에서 삭제
	{
		if(!STRTOK(szData, 0, szHead, szNumber,szChanel, VL_END ))
		{
			strcpy(szNumber, "");
		}
		else
		{
			if(m_pRecvCidDlg)
			{
				m_pRecvCidDlg->RemoveRecvCid(szNumber, "NA",szChanel);
			}
		}

		return;
	}
	else if(szData[0] == 'R') //RF-Reader기에서 들어온 데이터
	{
		if(STRTOK(szData, 0, szHead, szNumber,szChanel, VL_END ))
		{	
			/*
			Beep(100, 100);
			SwitchView(SHUTTLE_VIEW);

			char *pszNumber = new CHAR[strlen(szNumber) + 1];
			strcpy(pszNumber, szNumber);
			m_pShuttleView->GetShuttleForm1()->PostMessage(
			WM_RECV_RFID, (WPARAM)pszNumber, 0);

			return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
			*/
		}
	}
	else {
		strcpy(szNumber, szData);
	}

	ST_CID_INFO *pCIDInfo = new ST_CID_INFO;
	pCIDInfo->dwTick = GetTickCount();
	pCIDInfo->nGroupID = atol(szGroupID);
	pCIDInfo->nLineID = atol(szLineID);
	pCIDInfo->strPhone = szNumber;
	pCIDInfo->pBi = (pBi == NULL) ? m_ba.GetAt(0) : pBi;	//by mksong (2011-03-22 오전 11:01)
	CString sPhone = szNumber;
	pCIDInfo->strZipCode = "";
	int nDeliMeter = pCIDInfo->strPhone.Find('@');
	if(nDeliMeter > 0 )
	{
		pCIDInfo->strPhone	= pCIDInfo->strPhone.Left(nDeliMeter);
		pCIDInfo->strZipCode= sPhone.Mid(nDeliMeter+1, 6);
	}


	if(m_ci.m_nCompanyCode == 15775 &&
		pCIDInfo->strPhone.GetLength() >= 7 &&
		pCIDInfo->strPhone.GetLength() <= 9 &&
		atol(pCIDInfo->strPhone.Left(2)) >= 3)
	{
		pCIDInfo->strPhone.Insert(1, '2');				
		g_bana_log->Print("이레퀵 키폰에러 수정\n");
	}


	if(m_ci.m_bUseCidPool)
	{
		ShowRecvCidDlg();

		pCIDInfo->strChannel = szChanel;
		m_pRecvCidDlg->AddRecvCid(szNumber, (DWORD)pCIDInfo);
	}
	else
	{
		COleDateTime dt = COleDateTime::GetCurrentTime();

		if(m_pRcpView != NULL)
		{
			WINDOWPLACEMENT wndpl;
			wndpl.length = sizeof(WINDOWPLACEMENT);
			m_pFrameWnd->GetWindowPlacement(&wndpl);

			if(wndpl.showCmd == SW_SHOWMINIMIZED)
				m_pFrameWnd->ShowWindow(SW_RESTORE);

			m_pFrameWnd->SetForegroundWindow();
			m_pFrameWnd->SetFocus();

			GetRcpView()->PostMessage(WM_RECV_CID, (WPARAM)pCIDInfo, 0);				
		}
		else
		{
			delete pCIDInfo;
		}
	}

}

void CLogiUtil::ShowRecvCidDlg()
{
	if(m_pRecvCidDlg == NULL)
	{
		m_pRecvCidDlg = new CRecvCidDlg(m_pFrameWnd);
		m_pRecvCidDlg->Create(IDD_RECV_CID_DLG, m_pFrameWnd);
		m_pRecvCidDlg->ShowWindow(SW_SHOW);
		//m_pRecvCidDlg->RefreshConnList();
	}
	else
	{
		WINDOWPLACEMENT wndpl;
		wndpl.length = sizeof(WINDOWPLACEMENT);
		m_pRecvCidDlg->GetWindowPlacement(&wndpl);

		if(wndpl.showCmd == SW_SHOWMINIMIZED)
			m_pRecvCidDlg->ShowWindow(SW_RESTORE);

		m_pRecvCidDlg->SetForegroundWindow();
		m_pRecvCidDlg->SetFocus();
		//		m_pRecvCidDlg->RefreshConnList();
	}
}

void CLogiUtil::CloseRecvCidDlg()
{
	delete m_pRecvCidDlg;
	m_pRecvCidDlg = NULL;
}

BOOL CLogiUtil::SendCopyDataToTelClient(char *szBuff, long nType, BOOL bInsert)
{
	HWND hWnd = ::FindWindow("TELCLIENT BY LOGISOFT",NULL);

	if(IsWindow(hWnd)) {
		COPYDATASTRUCT *cds = new COPYDATASTRUCT;
		cds->cbData = (long)strlen(szBuff);
		cds->lpData = (void*) szBuff;
		::SendMessage(hWnd, WM_COPYDATA, (long)m_pFrameWnd->m_hWnd, (long)cds);
		delete cds;
		return TRUE;
	}

	return FALSE;
}

CRcpView* CLogiUtil::GetRcpView()
{
	CWnd* pWnd = m_pwndCur;
	if (pWnd == NULL) {
		return NULL;
	}

	CRuntimeClass* p = pWnd->GetRuntimeClass();
	CString strClass(p->m_lpszClassName);

	if (strClass == "CRcpView") {
		return (CRcpView*)pWnd;
	}
	else {
		if (m_pRcpView->GetSafeHwnd()) {
			return m_pRcpView;
		}
	}

	return NULL;
}

void CLogiUtil::ShowMessenger()
{
	if(!LF->POWER_CHECK(1400, "메신저 접속리스트 보기", TRUE))
		return;


	if(GetMessenger() == NULL)
	{
		MessageBox("메신저 로그인이 되지 않은 상태입니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	GetMessenger()->ShowMsgConnList();
}

void CLogiUtil::RunRemoteControl(int nType)
{
	char buffer[10];
	CString strType = "RemoteControlServer";
	strType += ltoa(nType, buffer, 10);
	CString strParameter, strAddress, strPort;
	CMkCommand pCmd(m_pMkDb, "select_unique_value2");
	pCmd.AddParameter(typeString, typeInput, strType.GetLength(), strType);	
	CMkParameter *parOutValue = pCmd.AddParameter(typeString, typeOutput, 50, strAddress);	
	CMkParameter *parOutSubValue = pCmd.AddParameter(typeString, typeOutput, 50, strPort);	
	pCmd.Execute();
	parOutValue->GetValue(strAddress);
	parOutSubValue->GetValue(strPort);

	try {


		if(strAddress.GetLength() < 1) 
			throw "원격연결서버의 주소를 찾을 수 없습니다.";

		if(strPort.GetLength() < 1) 
			throw "원격연결서버의 주소를 찾을 수 없습니다.";

		CString strPath = LF->GetModuleFullPath();
		strPath += "remoteclient.exe";
		strParameter = strAddress + "/" + strPort + "/" + 
					m_ci.GetName() + "|" + m_ci.GetPhone() + "|" + m_ui.strName + "|" + m_ui.strID;

		if(!LF->RunProgram(strPath, strParameter))
			throw "원격연결 클라이언트 프로그램을 찾을 수 없습니다.";
	} catch(char *szMsg)
	{
		MessageBox(szMsg, "원격 연결오류", MB_ICONERROR); 	
		return;
	}

	MessageBox("원격 연결을 시작합니다.\n응답이 있을 때 까지 기다려 주십시오.", "원격 연결시작",
		MB_ICONINFORMATION);
}

BOOL CLogiUtil::ChangeBranchItemInTaskPanel(CXTPTaskPanel *pTaskPanel, CBranchInfo *pBi, CXTPDockingPane *pwndPane)
{
	if(m_ba.GetCount() < 2)
		return NULL;

	if(!pTaskPanel->GetSafeHwnd())
		return NULL;

	BOOL bFound = FALSE;
	BOOL bRet = FALSE;
	CXTPTaskPanelItems *pItems = pTaskPanel->GetGroups();

	for(int nGroup = 0; nGroup < pItems->GetCount(); nGroup++)
	{
		CXTPTaskPanelItem *pItem = pItems->GetAt(nGroup);
		CXTPTaskPanelGroup *pGroup = pItem->GetItemGroup();

		if(NULL == pGroup) continue;

		for(int i = 0; i < pGroup->GetItemCount(); i++)
		{
			CXTPTaskPanelGroupItem *pItemGroup = pGroup->FindItem(i);
			if(pItemGroup)
			{
				ST_BRANCH_PANE_INFO *pBPI = (ST_BRANCH_PANE_INFO*)pItemGroup->GetItemData();
				CBranchInfo *pBi2 = pBPI->pBi;
				if(pBi == pBi2)
				{
					pItemGroup->SetItemSelected(TRUE);
					pGroup->SetExpanded(TRUE);

					CString strTitle;
					strTitle.Format("네트웍(%s)", pItemGroup->GetCaption());
					if(pwndPane) 
					{
						pwndPane->SetTitle(strTitle);			
						bRet = TRUE;
					}
				}
				else
				{
					pItemGroup->SetItemSelected(FALSE);
				}
			}
		}	}

	return NULL;
}


void CLogiUtil::ResetToolboxItems(CXTPTaskPanel *pwndTaskPanel)
{
	pwndTaskPanel->GetGroups()->Clear(FALSE);
	m_pbiCur = m_ba.GetAt(0);

	if(m_ba.GetCount() > 1) 
	{
		CBranchInfo *pBi = m_ba.GetAt(0);
		CXTPTaskPanelGroup* pFolder = pwndTaskPanel->AddGroup(ID_TOOLBOX_FOLDER);
		CXTPTaskPanelGroup* pFolderMain = pFolder;
		pFolder->SetCaption("통합");
		pFolder->SetSpecialGroup(TRUE);

		ST_BRANCH_PANE_INFO *pInfo = new ST_BRANCH_PANE_INFO;
		pInfo->pBi = pBi;
		pInfo->nVirtualCompany = 0;
		pInfo->crBack = RGB(200, 200, 255);

		CXTPTaskPanelGroupItem* pPointer = pFolder->AddLinkItem(0, 5);
		pPointer->SetCaption(pBi->strBranchName);
		//###pPointer->SetTooltip(pBi->strPhone);
		pPointer->SetBold(FALSE);
		pPointer->SetItemSelected(TRUE);
		pPointer->AllowDrag(FALSE);
		pPointer->AllowDrop(FALSE);
		pPointer->SetItemData((DWORD)pInfo);

		int nSubCount = 1;

		typedef map<long, CXTPTaskPanelGroup*> SubDisplayGroup;
		SubDisplayGroup sdGroup;

		for(int n = 1; n < m_ba.GetCount(); n++)
		{
			pBi = m_ba.GetAt(n);
			sdGroup[pBi->nSubDisplayGroup] = (CXTPTaskPanelGroup*)0;
		}

		sdGroup[0] = pFolder;
		for(int i = 1; i < m_ba.GetCount(); i++)
		{
			pBi = m_ba.GetAt(i);

			if(sdGroup.size() > 2)
			{
				if(sdGroup[pBi->nSubDisplayGroup] == 0)
				{
					pFolder = pwndTaskPanel->AddGroup(ID_TOOLBOX_FOLDER + nSubCount++);
					pFolder->SetCaption(pBi->strBranchName);
					sdGroup[pBi->nSubDisplayGroup] = pFolder;
				}
				else
				{
					pFolder = sdGroup[pBi->nSubDisplayGroup];
				}
			}

			ST_BRANCH_PANE_INFO *pInfo2 = new ST_BRANCH_PANE_INFO;
			pInfo2->pBi = pBi;
			pInfo2->nVirtualCompany = 0;
			pInfo2->crBack = RGB(200, 200, 255);

			CXTPTaskPanelGroupItem *pPointer2 = pFolder->AddLinkItem(i, 2);
			pPointer2->SetCaption(pBi->strBranchName);
			pPointer2->SetBold(FALSE);
			pPointer2->SetItemSelected(TRUE);
			pPointer2->AllowDrag(FALSE);
			pPointer2->AllowDrop(FALSE);
			pPointer2->SetItemData((DWORD)pInfo2);
		}
	}	

}

BOOL CLogiUtil::CreateToolBox(CXTPTaskPanel **pTaskPanel, CWnd *pOwner)
{
	if(!(*pTaskPanel))
	{
		(*pTaskPanel) = new CXTPTaskPanel;

		if (!(*pTaskPanel)->Create(WS_CHILD|WS_VISIBLE, CRect(0, 0, 0, 0), pOwner, 0))
			return FALSE;

		(*pTaskPanel)->SetOwner(pOwner);
		(*pTaskPanel)->SetCustomTheme(new CMyXTPTaskPanelPaintManager());
		//(*pTaskPanel)->GetImageManager()->SetIcons(IDB_PANE_ICONS, 0, 7, CSize(16, 16));
		(*pTaskPanel)->SetBehaviour(xtpTaskPanelBehaviourToolbox);
		(*pTaskPanel)->SetSelectItemOnFocus(TRUE);
		(*pTaskPanel)->SetExpandable(TRUE);
		(*pTaskPanel)->AllowDrag(TRUE);	
		(*pTaskPanel)->SetMargins(1, 1, 1, 1, 1);
		(*pTaskPanel)->GetPaintManager()->m_rcGroupInnerMargins = CRect(1,1,1,1);
		(*pTaskPanel)->GetPaintManager()->m_rcGroupOuterMargins = CRect(0,0,0,0);
		(*pTaskPanel)->GetPaintManager()->m_rcItemInnerMargins = CRect(1,1,1,1);
		(*pTaskPanel)->GetPaintManager()->m_rcItemOuterMargins = CRect(0,0,0,0);

		if(m_pwndTaskPanel == NULL)
			m_pwndTaskPanel = (*pTaskPanel);
	}

	return TRUE;
}

CXTPTaskPanel* CLogiUtil::GetTaskPanel()
{
	return m_pwndTaskPanel;
}

void CLogiUtil::SetTaskPanel(CXTPTaskPanel *pTaskPanel)
{
	m_pwndTaskPanel = pTaskPanel;
}

void CLogiUtil::SetTitlePrint(CString strText)
{
	if(m_ui.bDeveloper)
	{
		if(m_strOriginalWindowTitle.GetLength() > 0)
			AfxGetMainWnd()->SetWindowText(strText + " [" + m_strOriginalWindowTitle + "]");
		else
			AfxGetMainWnd()->SetWindowText(strText);
	}
}


LRESULT CLogiUtil::OnTaskPanelNotify(WPARAM wParam, LPARAM lParam, CXTPDockingPane *pwndPane, 
							CXTPDockingPaneManager *pwndManager, CWnd *pwndCurView)
{
	switch(wParam)
	{
	case XTP_TPN_CLICK:
		{
			CXTPTaskPanelGroupItem* pItem = (CXTPTaskPanelGroupItem*)lParam;

			CString strTitle;
			strTitle.Format("네트웍(%s)", pItem->GetCaption());
			pwndPane->SetTitle(strTitle);
			pwndManager->RedrawPanes(); 
			m_pbiCur = m_ba.GetAt(pItem->GetID());

			if(pwndCurView != NULL) pwndCurView->PostMessage(WM_BRANCH_CLICK_EVENT, (WPARAM)m_pbiCur, 0);
		}
		return TRUE;

	case XTP_TPN_RCLICK:
		{
			CXTPTaskPanelGroupItem* pItem = (CXTPTaskPanelGroupItem*)lParam;

			CBranchInfo *pbi = NULL;
			pbi = (CBranchInfo *)m_ba.GetAt(pItem->GetID());
			if (pbi == NULL)
				return false;

			CChangeColorDlg dlg;
			dlg.m_nCompany =  pbi->nCompanyCode;
			dlg.m_pBi = pbi;
			dlg.DoModal();
		}
		return TRUE;
	}
	return 0;
}

void CLogiUtil::InitPaneManager(CXTPDockingPaneManager *paneManager, CWnd *pwndOwner)
{
	paneManager->InstallDockingPanes(pwndOwner);
	paneManager->SetTheme(xtpPaneThemeOffice2003);
	paneManager->SetFloatingFrameCaption(_T("팝업상태"));
	paneManager->SetThemedFloatingFrames(TRUE);
	paneManager->SetAnimationDelay(-1, 1, 1);

	int nIDIcons[] = {1, 2, 3, 4, 5, 6};
	paneManager->SetIcons(IDB_PANE_ICONS, nIDIcons, 7, RGB(255, 0, 255));
}

void CLogiUtil::MakeNetworkPane(CXTPDockingPaneManager *pwndPaneManager, CXTPDockingPane **pwndPaneNetwork, 
								CXTPTaskPanel *pwndTaskPanel, long nStartBranchID)
{
	(*pwndPaneNetwork) = pwndPaneManager->CreatePane(
		IDR_PANE_NETWORK, CRect(0, 0, 120, 100), xtpPaneDockLeft);
	(*pwndPaneNetwork)->Hide();
	(*pwndPaneNetwork)->SetIconID(3);

	if(m_ba.GetCount() > 1 && pwndPaneNetwork)
	{
		(*pwndPaneNetwork)->Select();
		m_pbiCur = m_ba.GetAt(nStartBranchID);
		if(ChangeBranchItemInTaskPanel(pwndTaskPanel, m_pbiCur, (*pwndPaneNetwork)))
			pwndPaneManager->RedrawPanes();
		(*pwndPaneNetwork)->Hide();
	}
}

CWnd* CLogiUtil::AddView(CWnd *pThis, CXTPTabControl *pTabCtrl, CRuntimeClass* pViewClass, 
						 LPCTSTR lpszTitle, int nIcon,int nID,
						 BOOL bInitialUpdate, BOOL bActive)
{
	CString sClassName = pViewClass->m_lpszClassName;
	sClassName.TrimLeft('C');

	CCreateContext contextT;
	contextT.m_pCurrentDoc     = NULL;
	contextT.m_pNewViewClass   = pViewClass;
	contextT.m_pNewDocTemplate = NULL;

	CWnd* pWnd;
	TRY
	{
		pWnd = (CWnd*)pViewClass->CreateObject();
		if (pWnd == NULL)
		{
			AfxThrowMemoryException();
		}
	}
	CATCH_ALL(e)
	{
		TRACE0( "Out of memory creating a view.\n" );
		// Note: DELETE_EXCEPTION(e) not required
		return FALSE;
	}
	END_CATCH_ALL

	DWORD dwStyle = AFX_WS_DEFAULT_VIEW;
	dwStyle &= ~WS_BORDER;

	int nTab = pTabCtrl->GetItemCount();

	// Create with the right size (wrong position)
	CRect rect(0,0,0,0);
	if (!pWnd->Create(NULL, NULL, dwStyle,
		rect, pTabCtrl, (AFX_IDW_PANE_FIRST + nTab), &contextT))
	{
		TRACE0( "Warning: couldn't create client tab for view.\n" );
		// pWnd will be cleaned up by PostNcDestroy
		return NULL;
	}

	pTabCtrl->InsertItem(nTab, lpszTitle, pWnd->GetSafeHwnd(), nIcon);
	pWnd->SetOwner(pThis);

	if(bInitialUpdate)
		pWnd->SendMessage(WM_INITIALUPDATE);

	if(bActive)
		pTabCtrl->SetCurSel(nTab);

	return pWnd;
}


void CLogiUtil::MakeDepositRate()
{
	//CWaitCursor wait;;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_deposit_rate_simple", TRUE);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), 1);

	if(pRs.Execute(&pCmd))
	{
		long nPay, nDeposit, nCompany;

		while(!pRs.IsEOF()) 
		{
			pRs.GetFieldValue("nCompany", nCompany);
			pRs.GetFieldValue("nPay", nPay);
			pRs.GetFieldValue("nDeposit", nDeposit);

			if(nCompany > 0 && nDeposit > 0)
			{
				m_dr.insert(MAP_DEPOSIT_RATE::value_type(std::make_pair(nCompany, nPay), nDeposit));
			}


			pRs.MoveNext();
		}
	}

	pRs.Close();

}
void CLogiUtil::UpdateDepositRate(UINT nCompany, UINT nCharge, UINT nDeposit)
{
	MAP_DEPOSIT_RATE::iterator it = m_dr.find(std::make_pair(nCompany, nCharge));
	if(it == m_dr.end())
		m_dr.insert(MAP_DEPOSIT_RATE::value_type(std::make_pair(nCompany, nCharge), nDeposit));
	else
		it->second = nDeposit;
}

void CLogiUtil::ShowRiderInfoDlg(long nCompany, long nRNo, long nOrderCompany, long nTNo, CString strCallBranch, long nState, long nPayType, CString strRiderCIDPhone)
{
#ifdef _RCPPROJ

	if(nCompany == 0 || nRNo == 0)
		return; 

	BOOL bMyRider = m_ci.IsChildCompany(nCompany);

	CMkCommand pCmd(m_pMkDb, "select_rcp_rider_info_5");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nTNo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bMyRider);
	CMkParameter *parRiderDate = pCmd.AddParameter(typeString, typeOutput, 10, "");
	CMkParameter *parAlloc = pCmd.AddParameter(typeString, typeOutput, 500, "");
	CMkParameter *parPenalty = pCmd.AddParameter(typeString, typeOutput, 500, "");
	CMkParameter *parCharge = pCmd.AddParameter(typeString, typeOutput, 500, "");
	CMkParameter *parMyCallCount = pCmd.AddParameter(typeString, typeOutput, 500, "");
	CMkParameter *parCrossCallCount = pCmd.AddParameter(typeString, typeOutput, 500, "");
	CMkRecordset pRs(m_pMkDb);	
	if(!pRs.Execute(&pCmd))
		return;

	CString strDate, strAlloc, strPenalty, strCharge, strMyCallCount, strCrossCallCount;
	parRiderDate->GetValue(strDate);
	parAlloc->GetValue(strAlloc);
	parPenalty->GetValue(strPenalty);
	parCharge->GetValue(strCharge);
	parMyCallCount->GetValue(strMyCallCount);
	parCrossCallCount->GetValue(strCrossCallCount);


	CMakeRiderStat stat;
	stat.SetMonthlyChunk(strDate, nCompany, nRNo, strAlloc, strPenalty, strMyCallCount, strCrossCallCount, strCharge); 

	if(!pRs.IsEOF())
	{	
		int nDepositType, nWorkState, nTodaySave, nBalance;
		int nLockTime, nLockCount, nReleaseMin;
		COleDateTime dtInsStart, dtInsEnd, dtEnter;
		BOOL bInsLimit, bTimeLimit, bWorkStop, bCountLimit, bBusinessCar;
		CString strRNo;
		CString strDeviceID, strRName, strRealRName, strPhone, strHomePhone, strInsInfo;
		CString strHistory, strDeviceType, strDeviceVer;
		CString strCountLimit, strTimeLimit;
		CString strInsExpDate, strDepositType, strTodayCharge, strBalance;
		CString strEnterDate, strCompany, strBranch;
		CString strCompanyPhone, strOfficePhone;
		CString strHp4Call;
		long nLicenseValid;
		int nInsState,nCarType, nRNoTemp, nRiderCompanyTemp;
		CString strHistory2, strCompanyName, strBranchName, strLoadInsState, strCarNo;
		BOOL bDaeriRider;


		pRs.GetFieldValue("sID", strDeviceID);
		pRs.GetFieldValue("sName", 	strRName);
		pRs.GetFieldValue("sHp", strPhone);
		pRs.GetFieldValue("sTel", strHomePhone);
		pRs.GetFieldValue("dtEnter", dtEnter);
		pRs.GetFieldValue("nDepositType", nDepositType);
		pRs.GetFieldValue("nWorkState", nWorkState);
		pRs.GetFieldValue("bAllocateLimit", bTimeLimit);
		pRs.GetFieldValue("nReleaseMin", nReleaseMin);
		pRs.GetFieldValue("bInsurance", bInsLimit);
		pRs.GetFieldValue("dtInsuranceStart", dtInsStart);
		pRs.GetFieldValue("dtInsuranceEnd", dtInsEnd);
		pRs.GetFieldValue("sInsuranceID", strInsInfo);
		pRs.GetFieldValue("nBalance", nBalance);
		pRs.GetFieldValue("nTodaySave", nTodaySave);
		pRs.GetFieldValue("nLockTime", nLockTime);
		pRs.GetFieldValue("nLockCount", nLockCount);
		pRs.GetFieldValue("sHistory", strHistory);
		pRs.GetFieldValue("sHistory2", strHistory2);
		pRs.GetFieldValue("sDeviceType", strDeviceType);
		pRs.GetFieldValue("sDeviceVersion", strDeviceVer);
		pRs.GetFieldValue("nLicenseValid", nLicenseValid);
		pRs.GetFieldValue("nInsState", nInsState);
		pRs.GetFieldValue("sHp4Call", strHp4Call);
		pRs.GetFieldValue("nCarType", nCarType);
		pRs.GetFieldValue("sCompanyName", strCompanyName);
		pRs.GetFieldValue("sBranchName", strBranchName);
		pRs.GetFieldValue("sCompanyPhone", strCompanyPhone);
		pRs.GetFieldValue("nRNo", nRNoTemp);
		pRs.GetFieldValue("nRiderCompany", nRiderCompanyTemp);
		pRs.GetFieldValue("bDaeriRider", bDaeriRider);
		pRs.GetFieldValue("sLoadInsState", strLoadInsState);
		pRs.GetFieldValue("bBusinessCar", bBusinessCar);
		pRs.GetFieldValue("sCarNo", strCarNo);

		strRNo.Format("%d번", nRNoTemp);
		//strCompany = m_ci.GetName(nCompany);
		//strBranch = m_ci.GetBranchName(nCompany);
		//strCompanyPhone = m_ci.GetPhone(nCompany);

		strCompany = strCompanyName;
		strBranch = strBranchName;
		strCompanyPhone = strCompanyPhone;

		strOfficePhone = "N/A";

		strRealRName = strRName;
		strRName += "(" + strRNo + ")";
		strPhone = LF->GetDashPhoneNumber(strPhone);
		strHomePhone = LF->GetDashPhoneNumber(strHomePhone);

		if(bTimeLimit) bTimeLimit = TRUE;
		if(bInsLimit) bInsLimit = TRUE;

		if(nLockTime == 0 || nLockCount >= 100)
		{
			strCountLimit = "";
			bCountLimit = FALSE;
		}
		else {
			strCountLimit.Format("%d분내 %d건이하",  nLockTime, nLockCount);
			bCountLimit = TRUE;
		}


		if(bTimeLimit)
			strTimeLimit.Format("%d분 동안", nReleaseMin);
		else
			strTimeLimit = "";


		if(bInsLimit)
		{
			strInsExpDate.Format("%s", dtInsEnd.Format("%Y-%m-%d"));
		}
		else {
			strInsExpDate = "";
		}

		strDepositType = LF->GetDepositTypeStringFromType(nDepositType);
		if(strDepositType.IsEmpty()) strDepositType = "후입금";
		bWorkStop = (nWorkState == 1) ? TRUE : FALSE;

		strEnterDate.Format("%s", dtEnter.Format("%Y-%m-%d"));


		MakeRiderInfoDlg();

		m_pRiderInfoDlg->UpdateData();
		m_pRiderInfoDlg->m_bDaeriRider = bDaeriRider;
		//m_pRiderInfoDlg->m_nCompany = nCompany;
		//m_pRiderInfoDlg->m_nRNo = nRNo;
		m_pRiderInfoDlg->m_nCompany = nRiderCompanyTemp;
		m_pRiderInfoDlg->m_nRNo = nRNoTemp;
		m_pRiderInfoDlg->m_nTNo = nTNo;
		m_pRiderInfoDlg->m_strCompany = strCompany;
		m_pRiderInfoDlg->m_strBranch = strBranch;
		m_pRiderInfoDlg->m_strCompanyPhone = strCompanyPhone;
		m_pRiderInfoDlg->m_strOfficePhone = strOfficePhone;
		m_pRiderInfoDlg->m_strRName = strRName;
		m_pRiderInfoDlg->m_strRealRName = strRealRName;
		m_pRiderInfoDlg->m_strDeviceID = strDeviceID;
		m_pRiderInfoDlg->m_strDeviceType = strDeviceType;
		m_pRiderInfoDlg->m_strDeviceVer = strDeviceVer;
		m_pRiderInfoDlg->m_strPhone = strPhone;
		m_pRiderInfoDlg->m_strHomePhone = strHomePhone;
		m_pRiderInfoDlg->m_strEnterDate = strEnterDate;
		m_pRiderInfoDlg->m_strDepositType = strDepositType;
		m_pRiderInfoDlg->m_strTodayIncome = "";
		m_pRiderInfoDlg->m_strBalance = strBalance;
		m_pRiderInfoDlg->m_strTodayCharge = strTodayCharge;
		m_pRiderInfoDlg->m_strWorkState = bWorkStop ? "업무중지" : "";
		m_pRiderInfoDlg->m_strCountLimit = strCountLimit;
		m_pRiderInfoDlg->m_strTimeLimit = strTimeLimit;
		m_pRiderInfoDlg->m_strInsInfo = strInsInfo;
		m_pRiderInfoDlg->m_strInsExpDate = strInsExpDate;
		m_pRiderInfoDlg->m_strHistory = strHistory;
		m_pRiderInfoDlg->m_strHistory2 = strHistory2;
		m_pRiderInfoDlg->m_nOrderCompany = nOrderCompany;
		m_pRiderInfoDlg->m_strLicenseState = "";//GetLicenseStateString(nLicenseValid, &(m_pRiderInfoDlg->m_bLicenseOK));
		m_pRiderInfoDlg->m_strInsState = "";//GetInsStateString(nInsState);
		m_pRiderInfoDlg->m_strCallBranch = strCallBranch;
		m_pRiderInfoDlg->m_strCarType = LF->GetCarTypeFromLong(nCarType);
		m_pRiderInfoDlg->m_strBalance = LF->GetMyNumberFormat(nBalance);
		m_pRiderInfoDlg->m_strTodaySave = LF->GetMyNumberFormat(nTodaySave);
		m_pRiderInfoDlg->m_strRecvCID = strRiderCIDPhone;
		m_pRiderInfoDlg->m_strCarNo = strCarNo;

		if(bBusinessCar == 0) m_pRiderInfoDlg->m_strBusinessCar = "";
		else if(bBusinessCar == 1) m_pRiderInfoDlg->m_strBusinessCar = "영업용";
		else if(bBusinessCar == 2) m_pRiderInfoDlg->m_strBusinessCar = "일반용";
		else if(bBusinessCar == 3) m_pRiderInfoDlg->m_strBusinessCar = "오토,짐받이";
				
		m_pRiderInfoDlg->m_btnTransfer.EnableWindow(TRUE);
		m_pRiderInfoDlg->m_strLoadInsState = strLoadInsState;

		if(nTNo == -1)
			m_pRiderInfoDlg->m_btnTransfer.EnableWindow(FALSE);

		if(nState != 35)
			m_pRiderInfoDlg->m_btnTransfer.EnableWindow(FALSE);

		if(!(nPayType == 2 || nPayType == 3)) //신용과 송금
			m_pRiderInfoDlg->m_btnTransfer.EnableWindow(FALSE);

		m_pRiderInfoDlg->m_btnOtherRiderTransfer.EnableWindow(!bMyRider);
		m_pRiderInfoDlg->ShowRiderStatInfo(stat);
		m_pRiderInfoDlg->ShowRiderInfo(TRUE);
		m_pRiderInfoDlg->ShowWindow(SW_SHOW);
		m_pRiderInfoDlg->CenterWindow(m_pRiderInfoDlg->GetDesktopWindow());
	}
	else
	{
		AfxGetMainWnd()->MessageBox("퇴사직원입니다", "확인", MB_ICONERROR);
	}

	pRs.Close();
#endif
}


void CLogiUtil::MakeRiderInfoDlg()
{
#ifdef _RCPPROJ
	if(m_pRiderInfoDlg == NULL)
	{
		m_pRiderInfoDlg = new CShowRiderInfoDlg(m_pFrameWnd);
		m_pRiderInfoDlg->Create(IDD_SHOW_RIDER_INFO_DLG, m_pFrameWnd);
		m_pRiderInfoDlg->SetParentView(m_pRcpView);
	}
	else
	{
		WINDOWPLACEMENT wndpl;
		wndpl.length = sizeof(WINDOWPLACEMENT);
		m_pRiderInfoDlg->GetWindowPlacement(&wndpl);
		m_pRiderInfoDlg->SetForegroundWindow();
		m_pRiderInfoDlg->SetFocus();
		m_pRiderInfoDlg->SetParentView(m_pRcpView);
	}
#else
	AfxMessageBox("RCPPROJ가 정의되지 않으면, [MakeRiderInfoDlg]를 사용할 수 없습니다.");
#endif
}


void CLogiUtil::CreateFormViewTabControl(CWnd *pParent, CXTPTabControl *pTabCtrl, CRect rc, XTPTabPosition nPosition)
{
	pTabCtrl->Create(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, rc, pParent, 100);
	pTabCtrl->GetPaintManager()->SetAppearance(xtpTabAppearancePropertyPage2003);
	pTabCtrl->GetPaintManager()->m_bHotTracking = TRUE;
	pTabCtrl->GetPaintManager()->m_bShowIcons = TRUE;
	pTabCtrl->GetPaintManager()->DisableLunaColors(TRUE);
	pTabCtrl->GetPaintManager()->SetPosition(nPosition);
}

CSimpleMapDlg* CLogiUtil::GetSimpleMap(BOOL bShow, BOOL bIfExists)
{
	//return  NULL; //20221223
	if(!bIfExists)
	{
		if(m_pSimpleMapDlg == NULL)	
		{ 
			//m_pSimpleMapDlg = new CSimpleMapDlg(CSimpleMapDlg::IDD, m_pFrameWnd);
			m_pSimpleMapDlg = new CSimpleMapDlg(IDD_SIMPLE_MAP_DLG, m_pFrameWnd);
			m_pSimpleMapDlg->m_bAutoDelete = FALSE;
			m_pSimpleMapDlg->CreateDlg(FALSE);
		}

		if(bShow)
		{
			m_pSimpleMapDlg->ShowWindow(SW_SHOWNA);
			m_pSimpleMapDlg->SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		}
	}

	return m_pSimpleMapDlg;
}

CRcpDlgMapDlg* CLogiUtil::GetRcpDlgMap(CRcpDlg *pRcpDlg, BOOL bShow, BOOL bIfExists)
{
	//return NULL; //20221223
	if(!bIfExists)
	{
		if(!m_pRcpDlgMapDlg)	
		{
			m_pRcpDlgMapDlg = new CRcpDlgMapDlg(m_pFrameWnd);
			m_pRcpDlgMapDlg->m_bAutoDelete = FALSE;
			m_pRcpDlgMapDlg->CreateDlg(FALSE);
		}

		if(bShow)
		{
			m_pRcpDlgMapDlg->ShowWindow(SW_SHOWNA);
			m_pSimpleMapDlg->SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		}
	}

	if(m_pRcpDlgMapDlg)
		m_pRcpDlgMapDlg->SetParentRcpDlg(pRcpDlg);

	return m_pRcpDlgMapDlg;
}


BOOL CLogiUtil::ForceLeavingWork(long nCompany, long nRNo)
{
	CMkCommand pCmd(m_pMkDb, "update_rider_attend_leave_state");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nRNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), 1);
	return pCmd.Execute();
}

void CLogiUtil::CreateChargeForRiderLogDlg()
{
	CREATE_MODALESS(CChargeForRiderLogDlg, m_pFrameWnd);	
	SHOW_MODALESS(CChargeForRiderLogDlg, m_pFrameWnd);
}

CRiderBoardDlg* CLogiUtil::CreateRiderBoardDlg()
{
	if(!LF->POWER_CHECK(1830, "기사게시판"))
		return NULL;

	if(m_pRiderBoardDlg == NULL)
	{
		m_pRiderBoardDlg = new CRiderBoardDlg(m_pFrameWnd);
		m_pRiderBoardDlg->Create(CRiderBoardDlg::IDD, m_pFrameWnd);
		m_pRiderBoardDlg->ShowWindow(SW_SHOW);
		m_pRiderBoardDlg->CenterWindow();
	}
	else
	{
		WINDOWPLACEMENT wndpl;
		wndpl.length = sizeof(WINDOWPLACEMENT);
		m_pRiderBoardDlg->GetWindowPlacement(&wndpl);

		if(wndpl.showCmd == SW_SHOWMINIMIZED)
			m_pRiderBoardDlg->ShowWindow(SW_RESTORE);
		m_pRiderBoardDlg->SetForegroundWindow();
		m_pRiderBoardDlg->SetFocus();
		m_pRiderBoardDlg->ShowWindow(SW_SHOW);
		//m_pRiderBoardDlg->SendMessage(WM_INITDIALOG);
	}

	return m_pRiderBoardDlg;
}

CRiderShareBoardDlg* CLogiUtil::CreateRiderShareBoardDlg(long nCompany, long nRNo, CString strRealRName)
{
	if(!LF->POWER_CHECK(1800, "기사정보 공유 게시판"))
		return NULL;

	if(m_pRiderShareBoardDlg == NULL)
	{
		m_pRiderShareBoardDlg = new CRiderShareBoardDlg(m_pFrameWnd);
		m_pRiderShareBoardDlg->m_nRiderCompany = nCompany;
		m_pRiderShareBoardDlg->m_nRNo = nRNo;
		m_pRiderShareBoardDlg->m_strRName = strRealRName;
		m_pRiderShareBoardDlg->Create(IDD_RIDER_SHARE_BOARD_DLG, m_pFrameWnd);
		m_pRiderShareBoardDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		WINDOWPLACEMENT wndpl;
		wndpl.length = sizeof(WINDOWPLACEMENT);
		m_pRiderShareBoardDlg->GetWindowPlacement(&wndpl);

		if(wndpl.showCmd == SW_SHOWMINIMIZED)
			m_pRiderShareBoardDlg->ShowWindow(SW_RESTORE);

		m_pRiderShareBoardDlg->m_nRiderCompany = nCompany;
		m_pRiderShareBoardDlg->m_nRNo = nRNo;
		m_pRiderShareBoardDlg->m_strRName = strRealRName;

		m_pRiderShareBoardDlg->SetForegroundWindow();
		m_pRiderShareBoardDlg->SetFocus();
		m_pRiderShareBoardDlg->ShowWindow(SW_SHOW);
		m_pRiderShareBoardDlg->SendMessage(WM_INITDIALOG);
	}

	return m_pRiderShareBoardDlg;
}

CRiderMapDlg* CLogiUtil::CreateRiderMapDlg()
{
	return _CreateRiderMapDlg(&m_pRiderMapDlg, FALSE);
}

CRiderMapDlg* CLogiUtil::CreateRiderMapDlg2()
{
	return _CreateRiderMapDlg(&m_pRiderMapDlg2, TRUE);
}

CRiderMapDlg* CLogiUtil::_CreateRiderMapDlg(CRiderMapDlg **pRiderMapDlg, BOOL bOtherRiderMap)
{
	if(!LF->POWER_CHECK(1030, "빠른배차&기사관제", TRUE))
		return NULL; 

	CRiderMapDlg *pMyRiderMapDlg = *pRiderMapDlg;

	if(GetRcpView())
	{
		if(pMyRiderMapDlg == NULL)
		{
			pMyRiderMapDlg = new CRiderMapDlg(m_pFrameWnd);
			pMyRiderMapDlg->m_bOtherRiderMap = bOtherRiderMap;
			pMyRiderMapDlg->m_pRcpView = GetRcpView();
			pMyRiderMapDlg->Create(IDD_RIDER_MAP_DLG, m_pFrameWnd);
		}
		else
		{
			WINDOWPLACEMENT wndpl;
			wndpl.length = sizeof(WINDOWPLACEMENT);
			pMyRiderMapDlg->GetWindowPlacement(&wndpl);

			if(wndpl.showCmd == SW_SHOWMINIMIZED)
				pMyRiderMapDlg->ShowWindow(SW_RESTORE);

			pMyRiderMapDlg->SetForegroundWindow();
			pMyRiderMapDlg->SetFocus();
		}

		CRect rc;

		if(m_pRiderMapDlg2)
		{
			long nPosX, nPosY;

			CLogiMapNew *pMapTarget = pMyRiderMapDlg->GetMap();
			CLogiMapNew *pMapSource = bOtherRiderMap ? m_pRiderMapDlg->GetMap() : m_pRiderMapDlg2->GetMap();
		
			pMapTarget->SetMapLevel(pMapSource->GetMapLevel());	
			pMapSource->GetCenterPos(nPosX, nPosY);
			pMapTarget->MoveMap(nPosX, nPosY);
		}

		if(!bOtherRiderMap && m_pRiderMapDlg2)
		{
			m_pRiderMapDlg2->GetWindowRect(rc);			
			pMyRiderMapDlg->MoveWindow(rc);

			WINDOWPLACEMENT wndpl, wndpl2;
			wndpl.length = sizeof(WINDOWPLACEMENT);
			wndpl2.length = sizeof(WINDOWPLACEMENT);

			pMyRiderMapDlg->GetWindowPlacement(&wndpl2);
			m_pRiderMapDlg2->GetWindowPlacement(&wndpl);

			if(wndpl.showCmd == SW_SHOWMINIMIZED || 
				wndpl.showCmd == SW_SHOWMAXIMIZED)
				pMyRiderMapDlg->ShowWindow(wndpl.showCmd);
			else
			{
				if(wndpl2.showCmd == SW_SHOWMINIMIZED ||
					wndpl2.showCmd == SW_SHOWMAXIMIZED) 
				{
					pMyRiderMapDlg->ShowWindow(SW_RESTORE);
				}

				pMyRiderMapDlg->ShowWindow(SW_SHOWNA);
			}

			pMyRiderMapDlg->MoveWindow(rc);
			pMyRiderMapDlg->MoveNormalForm(TRUE);
			m_pRiderMapDlg2->ShowWindow(SW_HIDE);
		}
		else if(bOtherRiderMap && m_pRiderMapDlg)
		{
			m_pRiderMapDlg->GetWindowRect(rc);			
			pMyRiderMapDlg->MoveWindow(rc);

			WINDOWPLACEMENT wndpl, wndpl2;
			wndpl.length = sizeof(WINDOWPLACEMENT);
			wndpl2.length = sizeof(WINDOWPLACEMENT);

			pMyRiderMapDlg->GetWindowPlacement(&wndpl2);
			m_pRiderMapDlg->GetWindowPlacement(&wndpl);

			if(wndpl.showCmd == SW_SHOWMINIMIZED || 
				wndpl.showCmd == SW_SHOWMAXIMIZED)
				pMyRiderMapDlg->ShowWindow(wndpl.showCmd);
			else
			{
				if(wndpl2.showCmd == SW_SHOWMINIMIZED ||
					wndpl2.showCmd == SW_SHOWMAXIMIZED) 
				{
					pMyRiderMapDlg->ShowWindow(SW_RESTORE);
				}

				pMyRiderMapDlg->ShowWindow(SW_SHOWNA);
			}

			pMyRiderMapDlg->MoveWindow(rc);
			pMyRiderMapDlg->MoveNormalForm(TRUE);
			m_pRiderMapDlg->ShowWindow(SW_HIDE);		
		}
		else
		{
			pMyRiderMapDlg->ShowWindow(SW_SHOW);
		}

		GetMessenger()->SetRecvRiderPosMsg(TRUE);
	}
	else
	{
		AfxGetMainWnd()->MessageBox(
					"접수페이지로 이동후에 기사관제를 다시 클릭하시기 바랍니다.", 
					"확인", MB_ICONINFORMATION);
	}

	*pRiderMapDlg = pMyRiderMapDlg;
	return pMyRiderMapDlg;
}

CRiderMapDlg* CLogiUtil::GetRiderMapDlg()
{
	return m_pRiderMapDlg;
}

CRiderMapDlg* CLogiUtil::GetRiderMapDlg2()
{
	return m_pRiderMapDlg2;
}

void CLogiUtil::CloseRiderMapDlg()
{
	DELETE_OBJECT(m_pRiderMapDlg);
}

CAllocateBoardDlg* CLogiUtil::CreateAllocateBoardDlg()
{
	if(!LF->POWER_CHECK(1600, "배차판 보기", TRUE))
		return NULL;

	if(GetRcpView())
	{
		if(m_pAllocateBoardDlg == NULL)
		{
			m_pAllocateBoardDlg = new CAllocateBoardDlg(m_pFrameWnd);
			m_pAllocateBoardDlg->Create(IDD_ALLOCATE_BOARD_DLG, m_pFrameWnd);
			m_pAllocateBoardDlg->m_bFirstRefresh = FALSE;
			m_pAllocateBoardDlg->GetRiderList();
			m_pAllocateBoardDlg->RefreshRiderList();
			m_pAllocateBoardDlg->RefreshList();
			m_pAllocateBoardDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			WINDOWPLACEMENT wndpl;
			wndpl.length = sizeof(WINDOWPLACEMENT);
			m_pAllocateBoardDlg->GetWindowPlacement(&wndpl);

			if(wndpl.showCmd == SW_SHOWMINIMIZED)
				m_pAllocateBoardDlg->ShowWindow(SW_RESTORE);

			m_pAllocateBoardDlg->m_bFirstRefresh = FALSE;
			m_pAllocateBoardDlg->ShowWindow(SW_SHOW);
			m_pAllocateBoardDlg->SetFocus();
		}
		GetMessenger()->SetRecvRiderPosMsg(TRUE);	
	}
	else
	{
		AfxGetMainWnd()->MessageBox("접수페이지로 이동후에 배차판을 다시 클릭하시기 바랍니다.", "확인", MB_ICONINFORMATION);
	}

	return m_pAllocateBoardDlg;
}

void CLogiUtil::CloseAllocateBoardDlg()
{
	DELETE_OBJECT(m_pAllocateBoardDlg);
}

CAllocateBoardDlg* CLogiUtil::GetAllocateBoardDlg()
{
	return m_pAllocateBoardDlg;
}

CAllocateBoardTRSDlg* CLogiUtil::CreateAllocateBoardTRSDlg()
{
	if(!(m_pRcpView))
	{
		MessageBox("접수창을 먼저 실행해주세요.", "확인", MB_ICONINFORMATION);
		return NULL;
	}

	if(m_pAllocateBoardTRSDlg == NULL)
	{
		m_pAllocateBoardTRSDlg = new CAllocateBoardTRSDlg(m_pFrameWnd);
		m_pAllocateBoardTRSDlg->Create(IDD_ALLOCATE_BOARD_TRS_DLG, m_pFrameWnd);
		m_pAllocateBoardTRSDlg->RefreshList();
		m_pAllocateBoardTRSDlg->RefreshRiderList();
		m_pAllocateBoardTRSDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		WINDOWPLACEMENT wndpl;
		wndpl.length = sizeof(WINDOWPLACEMENT);
		m_pAllocateBoardTRSDlg->GetWindowPlacement(&wndpl);

		if(wndpl.showCmd == SW_SHOWMINIMIZED)
			m_pAllocateBoardTRSDlg->ShowWindow(SW_RESTORE);

		m_pAllocateBoardTRSDlg->SetForegroundWindow();
		m_pAllocateBoardTRSDlg->SetFocus();
		m_pAllocateBoardTRSDlg->ShowWindow(SW_SHOW);
	}

	return m_pAllocateBoardTRSDlg;

}

void CLogiUtil::CloseAllocateBoardTRSDlg()
{
	DELETE_OBJECT(m_pAllocateBoardTRSDlg);
}

BOOL CLogiUtil::IsDetailPos(long nDongID, long nPosX, long nPosY)
{
	m_poiNew.IsPosUsable(nPosX, nPosY);

	if(nDongID > 0 && m_poiNew.GetDongPOI(nDongID)->GetDistanceMeter(nPosX, nPosY) > 10)
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_pos_is_detail_pos");
		pCmd.AddParameter(nDongID);
		pCmd.AddParameter(nPosX);
		pCmd.AddParameter(nPosY);
		if(pRs.Execute(&pCmd))
			if(pRs.GetRecordCount() > 0)
				return pRs.GetFieldLong("bHasDetailPos");
	}

	return FALSE;
}

ST_ALLOC_RIDER* CLogiUtil::GetAllocRider(long nCompany, long nRNo)
{
	MAP_ALLOC_RIDER::iterator it = m_mapAllocateRider.find(make_pair(nCompany, nRNo));
	if(it == m_mapAllocateRider.end())
	{
		ST_ALLOC_RIDER AllocRider;
		AllocRider.lCode = nCompany;
		AllocRider.nMNo = nRNo;
		AllocRider.strName = "신규추가";

		m_mapAllocateRider.insert(MAP_ALLOC_RIDER::value_type(make_pair(nCompany, nRNo), AllocRider));
		it = m_mapAllocateRider.find(make_pair(nCompany, nRNo));
	}

	return &it->second;
}

void CLogiUtil::OpenAllocateDlg(long nTNo, long nState, CString sTitle, long nRNo, long nDeposit, long nCarType, BOOL bToRcpView, CWnd *pParent)
{
	if(m_pAllocateDlg == NULL)
	{
		m_pAllocateDlg = new CAllocateDlg(m_pFrameWnd);
		m_pAllocateDlg->Create(IDD_ALLOCATE_DLG, m_pFrameWnd);
		m_pAllocateDlg->m_pRcpView = GetRcpView();
		m_pAllocateDlg->SetForegroundWindow();
	}

	char buffer[20];
	m_pAllocateDlg->m_bToRcpView = bToRcpView;
	m_pAllocateDlg->m_pParent = pParent;
	m_pAllocateDlg->m_strRNo = LF->RemoveZero((CString)itoa(nRNo, buffer, 10));
	m_pAllocateDlg->UpdateData(FALSE);
	m_pAllocateDlg->m_edtRNo.SetFocus();
	m_pAllocateDlg->m_edtRNo.SetSel(m_pAllocateDlg->m_strRNo.GetLength(), m_pAllocateDlg->m_strRNo.GetLength());
	m_pAllocateDlg->m_edtRNo.SetWindowText("");
	m_pAllocateDlg->OnEnChangeRnoEdit();

	m_pAllocateDlg->m_nTNo = nTNo;
	m_pAllocateDlg->m_nState = nState;
	//m_pAllocateDlg->m_nDeposit = nDeposit;

	m_pAllocateDlg->SetWindowText(sTitle);
	m_pAllocateDlg->ShowWindow(TRUE);
}

void CLogiUtil::OpenOtherAllocateDlg(long nTNo, long nCompany, long nState, long nDeposit, BOOL bToRcpView, CWnd *pParent)
{
	if(m_pOtherRiderDlg == NULL)
	{
		m_pOtherRiderDlg = new COtherRiderDlg(m_pFrameWnd);
		m_pOtherRiderDlg->Create(IDD_OTHER_RIDER_ALLOCATE_DLG, m_pFrameWnd);
		m_pOtherRiderDlg->m_pRcpView = GetRcpView();
		m_pOtherRiderDlg->SetForegroundWindow();
	}

	m_pOtherRiderDlg->m_bToRcpView = bToRcpView;
	m_pOtherRiderDlg->m_nTNo = nTNo;
	m_pOtherRiderDlg->m_nCompany = nCompany;
	m_pOtherRiderDlg->m_nState = nState;
	m_pOtherRiderDlg->m_nDeposit = nDeposit;
	m_pOtherRiderDlg->m_pParent = pParent;
	//m_pAllocateDlg->m_nDeposit = nDeposit;

	m_pOtherRiderDlg->SetWindowText("타기사개별배차");
	m_pOtherRiderDlg->ShowWindow(TRUE);
}

void CLogiUtil::OpenTranDlg(long nTNo, long nCompany)
{
	if(m_pTransInfoDlg == NULL)
	{
		m_pTransInfoDlg = new CTransInfoDlg(m_pFrameWnd);
		m_pTransInfoDlg->Create(IDD_TRANS_INFO, m_pFrameWnd);		
		m_pTransInfoDlg->SetForegroundWindow();
		m_pTransInfoDlg->CenterWindow();
	}
	
	m_pTransInfoDlg->Clear();

	m_pTransInfoDlg->m_nTNo = nTNo;
	m_pTransInfoDlg->m_nCompany = nCompany;
	if(nTNo > 0)
	{
		char buffer[20];
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_trans_info2");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);		
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);

		if(!pRs.Execute(&pCmd)) return;


		if(pRs.GetRecordCount() == 0 )
		{
			m_pTransInfoDlg->m_bNew = TRUE;
			//MessageBox("탁송정보가 없습니다", "확인", MB_ICONINFORMATION);
			
			//return;
		}

		if(pRs.GetRecordCount() != 0) 
		{
			CString sStart, sDest, sExpressName, sExpressNumber, sEtc, sName, sItemNo;
			COleDateTime dtDeparture, dtArrival, dtRegister;

			pRs.GetFieldValue("sStart", sStart);
			pRs.GetFieldValue("sDest", sDest);
			pRs.GetFieldValue("sExpressName", sExpressName);
			pRs.GetFieldValue("sExpressNumber", sExpressNumber);
			pRs.GetFieldValue("sEtc", sEtc);
			pRs.GetFieldValue("sName", sName);
			pRs.GetFieldValue("sItemNo", sItemNo);
			pRs.GetFieldValue("dtDeparture", dtDeparture);
			pRs.GetFieldValue("dtArrival", dtArrival);
			pRs.GetFieldValue("dtRegister", dtRegister);

			
			m_pTransInfoDlg->m_bNew = FALSE;

			m_pTransInfoDlg->m_sStart = sStart;
			
			m_pTransInfoDlg->m_sDest = sDest;
			m_pTransInfoDlg->m_sExpressName = sExpressName;
			m_pTransInfoDlg->m_sExpressNumber = sExpressNumber;
			m_pTransInfoDlg->m_sEtc = sEtc;
			m_pTransInfoDlg->m_sName = sName;
			m_pTransInfoDlg->m_sItemNo = sItemNo;
			m_pTransInfoDlg->m_dtDeparture = dtDeparture;
			m_pTransInfoDlg->m_dtArrival = dtArrival;
			m_pTransInfoDlg->m_dtRegister = dtRegister;

			m_pTransInfoDlg->m_sTitle = "탁송정보 - " + CString(itoa(nTNo, buffer, 10));
			m_pTransInfoDlg->SetData();
			
			
		}
		else 
			m_pTransInfoDlg->m_sTitle = "탁송정보";

		
		
	}	


	m_pTransInfoDlg->ShowWindow(SW_SHOW);

}

CConsignLinkDlg* CLogiUtil::OpenConsignLinkDlg(long nTNo,long nCompany, CRcpPlaceInfo *pStartPlaceInfo, 
								   CRcpPlaceInfo *pDestPlaceInfo, long nConsignTNo,long nTerminalWayID,
								   CString sConsignCity,CRcpDlg *pWnd, BOOL bRcpViewShow)
{


	if(m_pConsignLinkDlg == NULL)
	{
		m_pConsignLinkDlg = new CConsignLinkDlg((CWnd*)m_pFrameWnd);
		m_pConsignLinkDlg->Create(IDD_CONSIGN_LINK_DLG, (CWnd*)m_pFrameWnd);		
		//m_pConsignLinkDlg->SetForegroundWindow();
	}

	if(nConsignTNo <= 0)
	{
		m_pConsignLinkDlg->InitControl();		
		m_pConsignLinkDlg->m_nOrderTNo = nTNo;
		m_pConsignLinkDlg->m_pStartPlaceInfo = pStartPlaceInfo;
		m_pConsignLinkDlg->m_pDestPlaceInfo = pDestPlaceInfo;
		m_pConsignLinkDlg->m_pRcpDlgWndFront = pWnd;
		m_pConsignLinkDlg->m_nCompany = nCompany;
		m_pConsignLinkDlg->m_sDestSido = pDestPlaceInfo->GetPOI()->GetSido();
		m_pConsignLinkDlg->m_nConsignTNo = 0;
		m_pConsignLinkDlg->m_nTerminalWayID = 0;
		m_pConsignLinkDlg->m_nConCommissionCharge = 0;
		m_pConsignLinkDlg->NewRefreshOrder();		
		m_pConsignLinkDlg->CenterWindow();
		
		m_pConsignLinkDlg->ShowWindow(SW_SHOW);
		m_pConsignLinkDlg->SetForegroundWindow();
		
	}
	else if(bRcpViewShow)
	{
		m_pConsignLinkDlg->InitControl();
		m_pConsignLinkDlg->m_nOrderTNo = nTNo;
	/*	m_pConsignLinkDlg->m_pStartPlaceInfo = pStartPlaceInfo;
		m_pConsignLinkDlg->m_pDestPlaceInfo = pDestPlaceInfo;
		m_pConsignLinkDlg->m_pRcpDlgWndFront = pWnd;*/
		m_pConsignLinkDlg->m_nCompany = nCompany;
		m_pConsignLinkDlg->m_sDestSido = sConsignCity;
		m_pConsignLinkDlg->m_nConsignTNo = nConsignTNo;
		m_pConsignLinkDlg->m_nTerminalWayID = nTerminalWayID;

		/*m_pConsignLinkDlg->m_nOrderCharge = nOrderCharge;
		m_pConsignLinkDlg->m_nTransCharge = nTransCharge;
		m_pConsignLinkDlg->m_nOrderLinkCharge = nOrderLinkCharge;
		m_pConsignLinkDlg->m_nConCommissionCharge = nConCommissionCharge;*/
		m_pConsignLinkDlg->RcpViewShow();
		m_pConsignLinkDlg->CenterWindow();
		m_pConsignLinkDlg->ShowWindow(SW_SHOW);
m_pConsignLinkDlg->SetForegroundWindow();
	}
	else
	{
		m_pConsignLinkDlg->InitControl();
		m_pConsignLinkDlg->m_nOrderTNo = nTNo;
		m_pConsignLinkDlg->m_pStartPlaceInfo = pStartPlaceInfo;
		m_pConsignLinkDlg->m_pDestPlaceInfo = pDestPlaceInfo;
		m_pConsignLinkDlg->m_pRcpDlgWndFront = pWnd;
		m_pConsignLinkDlg->m_nCompany = nCompany;
		m_pConsignLinkDlg->m_sDestSido = sConsignCity;
		m_pConsignLinkDlg->m_nConsignTNo = nConsignTNo;
		m_pConsignLinkDlg->m_nTerminalWayID = nTerminalWayID;

		/*m_pConsignLinkDlg->m_nOrderCharge = nOrderCharge;
		m_pConsignLinkDlg->m_nTransCharge = nTransCharge;
		m_pConsignLinkDlg->m_nOrderLinkCharge = nOrderLinkCharge;
		m_pConsignLinkDlg->m_nConCommissionCharge = nConCommissionCharge;*/
		m_pConsignLinkDlg->EditRefreshOrder();
		m_pConsignLinkDlg->CenterWindow();
		m_pConsignLinkDlg->ShowWindow(SW_SHOW);
		m_pConsignLinkDlg->SetForegroundWindow();
	}
	
	return m_pConsignLinkDlg;
}

 
CMakeGroupReportNewDlg * CLogiUtil::OpenGroupReportDlg(CWnd *pWnd,long nReportNo, long nGNo,int nNewMode, COleDateTime dtFrom, COleDateTime dtTo,
		CString strGNoList, long nCalculateCount, long nCalculateSum,long nCalculateTrans)
{



	CREATE_MODALESS(CMakeGroupReportNewDlg, pWnd);	
	pDlg->m_nGNo = nGNo;
	pDlg->m_dtFrom = dtFrom;
	pDlg->m_dtTo = dtTo;
	pDlg->m_strGNoList = strGNoList;
	pDlg->m_nCalculateCount = nCalculateCount;
	pDlg->m_nCalculateSum = nCalculateSum;
	pDlg->m_nCalculateTrans = nCalculateTrans;
	pDlg->m_nNewMode = nNewMode;
	pDlg->m_nGroupReportID = nReportNo;
	SHOW_MODALESS(CMakeGroupReportNewDlg, pWnd);
	
	return pDlg;	

}

BOOL CLogiUtil::UpdateRiderInfoForReserveOrder(long nTNo, long nRiderCompany, long nRNo)
{
	CMkCommand pCmd(m_pMkDb, "update_rider_info_for_reserve_order_1");
	pCmd.AddParameter(nTNo);
	pCmd.AddParameter(nRiderCompany);
	pCmd.AddParameter(nRNo);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.nWNo);
	
	return pCmd.Execute();
}

long CLogiUtil::GetShareBalance(long nCompany)
{
	long nShareBalance = 0;

	CMkCommand pCmd(m_pMkDb, "select_share_balance_company");
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long), 0);
	pCmd.AddParameter(nCompany);

	if(!pCmd.Execute()) return nShareBalance;

	pPar->GetValue(nShareBalance);
	return nShareBalance;	
}

BOOL CLogiUtil::IsOtherShareBalanceOk(long nDeposit, long nRiderCompany)
{
	if(GetShareBalance(nRiderCompany) > nDeposit)
		return TRUE;

	return FALSE;
}

void CLogiUtil::ShowCallPhoneRiderDlg(long nRiderCompany, long nRNo, long nOrderCompany, BOOL bDaeriRider)
{
	if(nRiderCompany <= 0 || nRNo <= 0)
		return;

	if(m_pCallPhoneDlg == NULL)
	{
		m_pCallPhoneDlg = new CCallPhoneDlg(m_pFrameWnd);
		m_pCallPhoneDlg->Create(IDD_CALL_PHONE_DLG, m_pFrameWnd);
		m_pCallPhoneDlg->m_pRcpView = GetRcpView();
		m_pCallPhoneDlg->SetForegroundWindow();
	}
	
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_phone_info_1");
	pCmd.AddParameter(nRiderCompany);
	pCmd.AddParameter(nRNo);
	pCmd.AddParameter(bDaeriRider);

	if(!pRs.Execute(&pCmd))
		return;

	pRs.GetFieldValue("sPhone", m_pCallPhoneDlg->m_strPhone);
	pRs.GetFieldValue("sID", m_pCallPhoneDlg->m_strDeviceID);
	pRs.GetFieldValue("sTel", m_pCallPhoneDlg->m_strHomePhone);
	pRs.GetFieldValue("sCompanyPhone", m_pCallPhoneDlg->m_strCompanyPhone);
	pRs.GetFieldValue("sOfficePhone", m_pCallPhoneDlg->m_strOfficePhone);
	m_pCallPhoneDlg->m_nOrderCompany = nOrderCompany;

	m_pCallPhoneDlg->RefreshList();
	m_pCallPhoneDlg->ShowWindow(SW_SHOW);
} 

void CLogiUtil::ShowSearchPOIDlg(CString strKeyword, CRcpPlaceInfo *pPlace, long nCompany, 
								 CWnd *pParent, CWnd *pPositionWnd, CWnd *pNextWnd, BOOL bGetEvent)
{
	if(m_pSearchPOIDlg == NULL)
	{
		CRect rc, rcDlg, rcOrder, rcNew;

		if(bGetEvent)
			m_pSearchPOIDlg = new CSearchPOIDlg(pParent);
		else
			m_pSearchPOIDlg = new CSearchPOIDlg(NULL);

		m_pSearchPOIDlg->SetPOIDataNew(&m_poiNew);
		m_pSearchPOIDlg->SetCusData(&m_cus);
		m_pSearchPOIDlg->SetDatabase(m_pMkDb);
		m_pSearchPOIDlg->Create(IDD_SEARCH_POI_DLG, pParent);

		m_pSearchPOIDlg->GetWindowRect(rc);
		pParent->GetWindowRect(rcDlg);
		//m_edtOrder.GetWindowRect(rcOrder);

		if(pPositionWnd != NULL)
		{
			pPositionWnd->GetWindowRect(rcDlg);
		}

		rcNew.left = rcDlg.right + 2; 
		rcNew.right = rcNew.left + rc.Width();  
		rcNew.top = rcDlg.top - 300;
		rcNew.bottom = rcNew.top + rc.Height(); 
		m_pSearchPOIDlg->MoveWindow(rcNew);

		m_pSearchPOIDlg->ShowWindow(SW_SHOWNA);
		m_pSearchPOIDlg->SetSearchSido(m_poiNew.GetSearchSido()->GetSido());

	}
	else
	{
		m_pSearchPOIDlg->ShowWindow(SW_SHOWNA);
	}

	//m_pSearchPOIDlg->m_bAutoCompleteOnce = m_bPOIAutoCompleteOnce;
	//m_bPOIAutoCompleteOnce = FALSE;

	m_pSearchPOIDlg->SetRcpPlace(pPlace, pNextWnd);
	m_pSearchPOIDlg->SetCustomerTable(nCompany);
	m_pSearchPOIDlg->SearchPOIWithSetText(strKeyword, TRUE, FALSE, TYPE_DONG);
}

void CLogiUtil::OnAutoSelectEvent(int nType, BOOL bJustRefresh, BOOL bFocusNotChange, BOOL bSelectWhenSingleResult)
{
	if(m_pSearchPOIDlg)
	{
		if(bJustRefresh)
			m_pSearchPOIDlg->SearchPOIJust();
		m_pSearchPOIDlg->OnAutoSelectEvent(nType, 0, bSelectWhenSingleResult);
	}
}
			
void CLogiUtil::DestorySearchPoiDlg()
{
	DELETE_OBJECT(m_pSearchPOIDlg);
}

void CLogiUtil::ChargeAddDataInitLoad()
{
	if(m_pChargeAdd == NULL)
	{
		BOOL bRcpIntMode = FALSE;
		bRcpIntMode = (m_ci.m_bRcpIntMode1 + m_ci.m_bRcpIntMode2 + m_ci.m_bRcpIntMode3 + 
			m_ci.m_bRcpIntMode4 + m_ci.m_bRcpIntMode5 ) == 0 ? FALSE : TRUE;
		m_pChargeAdd = new CChargeAdd;
		m_pChargeAdd->LoadChargeAddData(m_ci.m_nCompanyCode, bRcpIntMode);
	}
}

BOOL CLogiUtil::IsTimeChargeCompany(long nCompany)
{

	if(m_pChargeAdd)
	{

		if(m_pChargeAdd->IsMapCompany(nCompany))
			return TRUE;
	}

	return FALSE;

}




CLogiMapCns* CLogiUtil::GetLogiMapCns()
{
	if(!m_pLogiMapCns)
	{
		CSimpleMapDlg *pMapDlg = GetSimpleMap();
		m_pLogiMapCns = new CLogiMapCns(pMapDlg);
	}

	return m_pLogiMapCns;
}

void CLogiUtil::ShowMemberChargeDlg(BOOL bOnlyCreate)
{
	if(m_pChargeHistoryMemDlg == NULL)
	{	
		CWnd *pWnd = AfxGetMainWnd();
		m_pChargeHistoryMemDlg = new CChargeHistoryMemDlg(pWnd);
		m_pChargeHistoryMemDlg->Create(IDD_CHARGE_HISTORY_MEMBER_DLG, pWnd);	
	}
	if(bOnlyCreate)
		return;

	if(!m_pChargeHistoryMemDlg->IsWindowVisible())
		m_pChargeHistoryMemDlg->ShowWindow(SW_SHOW);
}

CChargeHistoryMemDlg *  CLogiUtil::GetMemberChargeDlg( )
{
	return m_pChargeHistoryMemDlg != NULL ? m_pChargeHistoryMemDlg : NULL;
}


BOOL CLogiUtil::LoadMemberCharge( BOOL bInit)
{
	if(bInit)
		m_mapMemberCharge1.clear();

	BOOL bRcpIntMode = FALSE;
	BOOL bModify = FALSE;
	bRcpIntMode = (m_ci.m_bRcpIntMode1 + m_ci.m_bRcpIntMode2 + m_ci.m_bRcpIntMode3 + 
		m_ci.m_bRcpIntMode4 + m_ci.m_bRcpIntMode5 ) == 0 ? FALSE : TRUE;
	COleDateTime dtCur(COleDateTime::GetCurrentTime());

	CMkCommand pCmd(m_pMkDb, "select_history_charge_member2");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(bRcpIntMode);
	pCmd.AddParameter(bInit );
	pCmd.AddParameter(m_dtCur );

	pRs.Execute(&pCmd);
	m_dtCur = dtCur;
	MAP_MEMBER_CHARGE_CNO::iterator it;
	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		ST_MEMBER_CHARGE_CNO *st = new ST_MEMBER_CHARGE_CNO;
		
		pRs.GetFieldValue("nMemCNo", st->nMemCNo);
		pRs.GetFieldValue("sMemCompany", st->strMemCompany);	
		pRs.GetFieldValue("nCompany", st->nCompany);
		pRs.GetFieldValue("dtChange", st->dtChange);
		pRs.GetFieldValue("dtRegister",	st->dtRegister);
		pRs.GetFieldValue("bDelete",	st->bDelete);
		pRs.GetFieldValue("dtDelete",	st->dtDelete);
		pRs.GetFieldValue("sMemo",	st->strMemo);
		pRs.GetFieldValue("nCusCount",	st->nCusCount);		
		pRs.GetFieldValue("nChargeCount",	st->nChargeCount);		
		pRs.GetFieldValue("bView",	st->bView);		

		it = m_mapMemberCharge1.find(st->nMemCNo);
		if(it == m_mapMemberCharge1.end() )
		{
			if(st->bDelete)
			{
				if((*it).second)
					delete (*it).second;

				m_mapMemberCharge1.erase(it);
			}
			else
			{
				m_mapMemberCharge1.insert(MAP_MEMBER_CHARGE_CNO::value_type(st->nMemCNo,st ));
			}			
		}
		else
			ModifyRecord(st);	

		pRs.MoveNext();
		bModify = TRUE;
	}
	pRs.Close();
	return bModify;
}

void CLogiUtil:: ModifyRecord(ST_MEMBER_CHARGE_CNO *stNew )
{
	MAP_MEMBER_CHARGE_CNO::iterator it;
	it = m_mapMemberCharge1.find(stNew->nMemCNo);
	if(it != m_mapMemberCharge1.end())
	{
		if((*it).second)
			delete (*it).second;

		(*it).second = stNew;
	}	
}

void CLogiUtil::AddRiderPos(CRealTimeRiderPos &pos, COleDateTime dtUpdate)
{
	if(pos.nPosX == 0)
		return;

	if(dtUpdate.m_status == 2)
		dtUpdate = COleDateTime::GetCurrentTime();

	CPOIDataNew::IsPosUsable(pos.nPosX, pos.nPosY);

	CRiderSubInfoMap::iterator it = m_mapRiderSub.find(std::make_pair(pos.nCompany, pos.nRNo));
	if(it != m_mapRiderSub.end())
	{
		if((*it).second.dtUpdate <= dtUpdate)
		{
			(*it).second.AddPos(pos.nPosX, pos.nPosY);
			(*it).second.cartype = pos.cartype;
			(*it).second.dtUpdate = dtUpdate;
			(*it).second.strPosName = pos.strPosName;
			(*it).second.nPosX = pos.nPosX;
			(*it).second.nPosY = pos.nPosY;
		}
	}
	else
	{
		CRiderSubInfo rider;
		rider.nCompany = pos.nCompany;
		rider.nRNo = pos.nRNo;
		rider.dtUpdate = dtUpdate;
		rider.strName = pos.strName;
		rider.fAngle = 0;
		rider.fDistance = 0;
		rider.fArrowDistance = 0;
		rider.cartype = pos.cartype;
		rider.nHavingOrder = 0;
		rider.nCompleteOrder = 0;
		rider.nAllocOrderCount = 0;
		rider.nPickupOrderCount = 0; 
		rider.nChargeSum = 0;
		rider.strPosName = pos.strPosName;
		rider.strPhone = pos.strPhone;
		rider.strCity = pos.strCity;
		rider.nPosX = pos.nPosX;
		rider.nPosY = pos.nPosY;
		rider.bOtherRider = !m_ci.IsChildCompany(pos.nCompany);
		rider.bRealtimeOtherRider = rider.bOtherRider && m_ci.IsRealtimeShareRider(pos.nCompany);
		m_mapRiderSub.insert(CRiderSubInfoMap::value_type(std::make_pair(pos.nCompany, pos.nRNo), rider));
		it = m_mapRiderSub.find(std::make_pair(pos.nCompany, pos.nRNo));
		it->second.AddPos(pos.nPosX, pos.nPosY);
	}
}

CRiderSubInfo* CLogiUtil::GetRiderPos(long nCompany, long nRNo)
{
	CRiderSubInfoMap::iterator it;
	it = m_mapRiderSub.find(std::make_pair(nCompany, nRNo));
	if(it != m_mapRiderSub.end())
	{
		return &(it->second);
	}
	return NULL;
}

void CLogiUtil::HideSearchPOIDlg()
{
	m_pSearchPOIDlg->ShowWindow(SW_HIDE);
}

void CLogiUtil::InitChargeContainer(CWnd *pWnd)
{
	if(m_pChargeContainer == NULL)
		m_pChargeContainer = new CChargeContainer(pWnd);

}

void CLogiUtil::PlayRecFile(COleDateTime dtDate, CString strFolderDate, CString strKeyPhoneID, CString strTellNumber, CString strFileName, long nBound)
{
	if (m_PlayerDlg.GetSafeHwnd() == NULL)
	{
		m_PlayerDlg.Create(IDD_RECPLAYER_DLG);
		m_PlayerDlg.CenterWindow();
	}

	m_PlayerDlg.InitPostFormData(dtDate, strFolderDate, strKeyPhoneID, strTellNumber, strFileName, nBound);
	m_PlayerDlg.Navigate();
	m_PlayerDlg.ShowWindow(SW_SHOW);
}

void CLogiUtil::ChargeContainerShow()
{
	if(m_pChargeContainer != NULL)
		m_pChargeContainer->ChargeShow();
}

void CLogiUtil::GpsPosRevision(long &nPosX, long &nPosY, long nDeviceType, CString strDeviceName, CString strVersion)
{
	//by mksong (2011-06-27 오후 5:55)
	//서버 보정으로 변경함
/*
	if(nPosX > 0)
	{
		double fVersion = atof(strVersion);

		if(nDeviceType == 5500)
		{
			nPosX = nPosX + 1976;
			nPosY = nPosY - 2629;
		}
		else if(nDeviceType == 4000 && fVersion == 2.008)
		{
			nPosX = nPosX + 2102;
			nPosY = nPosY - 2808;
		}
	}
*/
} 

void CLogiUtil::OpenCurOrderState(long nTNo)
{
	if(m_pOrderProcessStateDlg == NULL)
	{
		m_pOrderProcessStateDlg = new COrderProcessStateDlg(m_pFrameWnd);
		m_pOrderProcessStateDlg->m_nTNo = nTNo;
		m_pOrderProcessStateDlg->Create(IDD_ORDER_PROCESS_STATE_DLG);
	}
	else
	{
		m_pOrderProcessStateDlg->m_nTNo = nTNo; 
	} 

	m_pOrderProcessStateDlg->FillData();
	m_pOrderProcessStateDlg->Refresh();
	m_pOrderProcessStateDlg->RefreshOrderList();
	m_pOrderProcessStateDlg->RefreshCombo(FALSE);

	CRect rcRcpDlg, rcOPSDlg; 

	m_pFrameWnd->GetWindowRect(rcRcpDlg);
	m_pOrderProcessStateDlg->GetWindowRect(rcOPSDlg);

	long nWidth = rcOPSDlg.Width();
	long nHeight = rcOPSDlg.Height(); 
	rcOPSDlg.left = rcRcpDlg.left + 40;
	rcOPSDlg.right = rcOPSDlg.left + nWidth;
	rcOPSDlg.top = rcRcpDlg.top + 100;
	rcOPSDlg.bottom = rcOPSDlg.top + nHeight;

	m_pOrderProcessStateDlg->MoveWindow(rcOPSDlg);
	m_pOrderProcessStateDlg->ShowWindow(SW_SHOW);
}

long CLogiUtil::GetDepositRate(UINT nCompany, UINT nCharge)
{
	if(nCharge == 0) return 0;

	MAP_DEPOSIT_RATE::iterator it = m_dr.find(std::make_pair(nCompany, nCharge));
	if(it != m_dr.end())
	{
		return it->second;		
	}
	else if(nCharge % 10 != 0)
	{
		return 0;	//임의로 0원을 만드는 경우다
	}
	else
	{
		long nDeposit = nCharge * 0.23;
		nDeposit = nDeposit - nDeposit % 10;
		return nDeposit;
	}
	return -1;
}

void CLogiUtil::MakePoiAndCusData()
{
	if(!m_poiNew.IsDataLoadOK()) 
	{
		//m_poiNew.SetLog(&mkLog); 
		m_poiNew.SetCompareDongPriority(TRUE);
		m_poiNew.SetHasStationPOI(TRUE);
		CMakePOIData poi(&m_poiNew, m_pMkDb, m_ci.m_strCity, m_ci.m_bCapitalArea, FALSE, TRUE, m_ci.m_bCapitalArea == TRUE ? 3 : 1);
		if(poi.AutoLoad())
		{
			CRoadAddress raddress(&m_poiNew);
			raddress.AutoLoad(m_pMkDb);
		}
	}

	if(m_ci.m_bUseSearchPopup)
		return;

	m_cus.SetMainCusData();
	if(!m_cus.IsDataLoadOK())
	{
		m_cus.SetCompanyCode(m_ci.m_nUseCustomerTable, m_ba.GetCount() < 2 ? FALSE : TRUE);
		if(m_cus.AutoLoad())
			m_cus.GetNewCustomer();
	}

};
BOOL CLogiUtil::IsConsignCity(CString sCity)
{
	COMPANY_APPLY_FROM_CITY_MAP3::iterator it;

	it = m_mapConCitySetting.find(sCity);
	if(it == m_mapConCitySetting.end())
		return FALSE;

	return TRUE;
}

CBranchInfo* CLogiUtil::GetConsignMakeBranchInfo(CString sCity)
{
	COMPANY_APPLY_FROM_CITY_MAP3::iterator it;

	it = m_mapConCitySetting.find(sCity);
	if(it == m_mapConCitySetting.end())
		return FALSE;
	
	return it->second;
}

long CLogiUtil::GetConsignCustomerCNo(CString sCity)
{
	COMPANY_APPLY_FROM_CITY_MAP3::iterator it;

	it = m_mapConCitySetting.find(sCity);
	if(it == m_mapConCitySetting.end())
		return 0;


	return it->second->nOtherCompanyCNo;
}

long CLogiUtil::GetConsignCustomerCNoTelID(CString sCity)
{
	COMPANY_APPLY_FROM_CITY_MAP3::iterator it;

	it = m_mapConCitySetting.find(sCity);
	if(it == m_mapConCitySetting.end())
		return 0;


	return it->second->nOtherCompanyCNoTelID;
}

void CLogiUtil::AddCall(CString strName, long nTNo, long nState)
{
	if(!LF->POWER_CHECK(2001, "접수창 열기", TRUE))
		return;

	GetRcpView()->CreateRcpDlg(NULL, 
		strName,
		nTNo, 
		nState, "", TRUE, -1, 0, 0, FALSE, "");
}

void CLogiUtil::CreateRcpDlg(CString strName, long nTNo, long nState)
{
	if(!LF->POWER_CHECK(2001, "접수창 열기", TRUE))
		return;

	GetRcpView()->CreateRcpDlg(NULL, 
		strName,
		nTNo, 
		nState, "", FALSE, -1, 0, 0, FALSE, "");
};

CString CLogiUtil::GetCustomerName(long nCNo)
{
	CMkCommand pCmd(m_pMkDb, "select_customer_name");
	pCmd.AddParameter(nCNo);
	CMkParameter *parOut = pCmd.AddParameter(typeString, typeOutput, 50, "");

	if(!pCmd.Execute())
		return "";

	CString strName; parOut->GetValue(strName);
	return strName;
}
 
void CLogiUtil::MakeFunctionTable()
{
	if(!LF->POWER_CHECK(1810, "기능페이지보기", TRUE))
		return;

	if(m_pFunctionTableDlg == NULL)
	{
		m_pFunctionTableDlg = new CFunctionTableDlg(m_pFrameWnd);
		m_pFunctionTableDlg->Create(CFunctionTableDlg::IDD, m_pFrameWnd);
		m_pFunctionTableDlg->SetForegroundWindow();
	}

	m_pFunctionTableDlg->ShowWindow(TRUE);
}

void CLogiUtil::AddSpecialLog(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);

	TCHAR line[8192];
	_vsnprintf(line, 8192, format, ap);

	va_end(ap);

	m_strSpecialLog += CString(line) + "\r\n";
}

BOOL CLogiUtil::GetGcmIDForSmartQ2(long nTNo, CString &strGcmID, CString &strText)
{
	CMkCommand cmd(m_pMkDb, "select_gcm_id_for_smartQ2");
	cmd.AddParameter(nTNo);
	CMkParameter *parGcmID = cmd.AddParameter(typeString, typeOutput, 500, "");
	CMkParameter *parText = cmd.AddParameter(typeString, typeOutput, 500, "");

	if(!cmd.Execute())
		return FALSE;

	parGcmID->GetValue(strGcmID);
	parText->GetValue(strText);

	return !strGcmID.IsEmpty();
}

BOOL CLogiUtil::SendGcmMsgForSmartQ2(long nTNo)
{
	CInternetSession session(NULL, 1, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, INTERNET_FLAG_DONT_CACHE);

	CString strGcmID = "", strText = "";
	
	if(GetGcmIDForSmartQ2(nTNo, strGcmID, strText) == FALSE)
		return FALSE;

	if(strGcmID == "")
		return FALSE;

	CString strUrl = "http://android.logisoft.co.kr/send_rcp_smartq2.asp?sText=";
	//strUrl += strText;
	strUrl += LF->EnCodeStr(strText);
	strUrl += "&sPhone=.";
	strUrl += "&sUserKey=" + strGcmID;
	strUrl += "&sTNo=" + LF->GetStringFromLong(nTNo);

	//http://android.logisoft.co.kr/send_rcp_smartq2.asp?sText=선릉역->대치동 개별배차가 배정되었습니다.&sPhone=15990000&sUserKey=APA91bFhWwZupnKfH5xxOzQnL4p6plOO7bGcLABIlWbV10KmBslh2UqxAcjv_mZgMZgaO1plJyeWLtE829xa4MXFh4IeiKFUmEoj8lbzY2HtgCUEoUwKiquQ9Y-jMKS9qHutQANtwR2YIDOmefHDU0WPXysP4jKQzQ&sTNo=449342485


	try 
	{
		CInternetFile *html = (CInternetFile *)session.OpenURL(strUrl);

		if(html == NULL)
			return FALSE;

		html->Close();
		delete html;
	}
	catch(CInternetException *)
	{
		return FALSE;
	}

	return TRUE;
}

CString CLogiUtil::GetRecordFileServerIP(COleDateTime dtDate)
{
	/*map<int, CString>::iterator it = m_mapRecordFileServerIP.find(m_ci.GetBranchInfo()->nCompany);
	if (it != m_mapRecordFileServerIP.end())
	{
	if(it->second.GetLength() > 0)
	return it->second;
	}*/

	CString strServerIP;
	CMkCommand cmd(m_pMkDb, "select_record_file_server_ip_1");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(dtDate);
	CMkParameter *parServerIP = cmd.AddParameter(typeString, typeOutput, 20, strServerIP);

	if(!cmd.Execute())
		return ""; 

	parServerIP->GetValue(strServerIP);
	//m_mapRecordFileServerIP[m_ci.GetBranchInfo()->nCompany] = strServerIP;

	return strServerIP;
}

BOOL CLogiUtil::IsShareInfoShowOk()
{
	if(m_nTodayCompleteCount >= 10 || 
		m_nYesterDayCompleteCount >= 10)
		return TRUE;

	return FALSE;

}

void CLogiUtil::SetYesterDayCompleteCount()
{
	CMkCommand cmd(m_pMkDb, "select_yesterday_complete_count");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(m_ui.nCompany);

	if(!cmd.Execute())
		return;

	parRet->GetValue(m_nYesterDayCompleteCount);
}

BOOL CLogiUtil::IsSSNOk(CString strSSN) //외국인번호 함께체크
{
	strSSN.Replace("-", "");
	BOOL isKorean = TRUE; 
	int check = 0; 

	if(strSSN.GetLength() != 13 ) 
		return FALSE; 

	long n6 = atoi(CString(strSSN.GetAt(6)));

	if(n6 > 4 && n6 < 9)
		isKorean = FALSE;
		
	for(int i=0; i<12; i++)
	{
		if(isKorean)
			check += (( i % 8 + 2 ) * atoi(CString(strSSN.GetAt(i)))); 
		else
			check += ( ( 9 - i % 8 ) * atoi(CString(strSSN.GetAt(i)))); 
	}

	if(isKorean)
	{
		check = 11 - ( check % 11 ); 
		check %= 10;
	}
	else
	{
		int remainder = check % 11; 
		if ( remainder == 0 ) check = 1; 
		else if ( remainder==10 ) check = 0; 
		else check = remainder; 

		int check2 = check + 2; 
		if ( check2 > 9 ) check = check2 - 10; 
		else check = check2; 	
	}


	if(check == atoi(CString(strSSN.GetAt(12)))) 
		return TRUE; 
	else 
		return FALSE; 
}

BOOL CLogiUtil::IsOtherCompanyRegist(CString strSSN, long nCompany, long nRNo)
{
	CMkCommand cmd(m_pMkDb, "select_is_other_company_register");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(strSSN);
	cmd.AddParameter(nCompany);
	cmd.AddParameter(nRNo);

	if(!cmd.Execute())
		return FALSE;

	long nRet; parRet->GetValue(nRet);

	if(nRet == 1)
		return TRUE;

	return FALSE;
}


CString CLogiUtil::GetCorpDomain()
{
    /// ieexplorer.exe| | 빈칸한칸 필요
	return " qu2.logisoft.co.kr";
}

CString CLogiUtil::GetFileExtension(CString strFileName)
{
	long nIndex = strFileName.ReverseFind('.');

	if(nIndex <= 0)
		return "";

	return strFileName.Right(strFileName.GetLength() - nIndex -1);
}

BOOL CLogiUtil::IsSystemFile(CString strFileName)
{	
	CString strExt = GetFileExtension(strFileName);
	strExt.MakeLower();

	if(strExt == "com" || strExt == "exe" || strExt == "bat" 
		|| strExt == "sys" || strExt == "ocx" ||strExt == "dll" 
		|| strExt == "jar" 
		)
	{
		AfxMessageBox("시스템 파일은 업로드를 하실수 없습니다.\r\n다시시도하세요", MB_ICONINFORMATION);
		return TRUE;
	}

	return FALSE;

}

void CLogiUtil::InsertINaviCnsLog(BOOL bSuccess, CString strParameter, CString strResult, CString strLocation)
{
	if(strParameter.GetLength() > 4000)
		strParameter = strParameter.Left(4000);

	if(strResult.GetLength() > 4000)
		strResult = strResult.Left(4000);

	long nDistance = 0;

	CMkCommand cmd(m_pMkDb, "insert_inavi_cns_search_log");
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(bSuccess);
	cmd.AddParameter(strParameter);
	cmd.AddParameter(strResult);
	cmd.AddParameter(strLocation);

	cmd.Execute();
}

CString CLogiUtil::SendEMailCardResult(int tno, CString customer_email, bool re_send)
{
    if(customer_email.IsEmpty())
        return "고객 이메일을 입력하세요";

    CMkRecordset rs(m_pMkDb);
    CMkCommand cmd(m_pMkDb, "select_card_mail_info_1");
    cmd.AddParameter(tno);

    if (!rs.Execute(&cmd) || rs.GetRecordCount() <= 0)
        return "카드 결제내역이 없습니다";

    CString customer_name, process_state, process_state_color, buyer_name, goods, date_title_string, date_string;
    CString order_number, card_company, amt, receipt_url;
    CString body_url, email_title, sender_email_name, sender_email;
    CString smtp_server, smtp_server_port, smtp_login_id, smtp_login_pw;

    rs.GetFieldValue("customer_name", customer_name);
    rs.GetFieldValue("process_state", process_state);
    rs.GetFieldValue("process_state_color", process_state_color);
    rs.GetFieldValue("buyer_name", buyer_name);
    rs.GetFieldValue("goods", goods);
    rs.GetFieldValue("date_title_string", date_title_string);
    rs.GetFieldValue("date_string", date_string);
    rs.GetFieldValue("order_number", order_number);
    rs.GetFieldValue("card_company", card_company);
    rs.GetFieldValue("amt", amt);
    rs.GetFieldValue("receipt_url", receipt_url);
    rs.GetFieldValue("body_url", body_url);
    rs.GetFieldValue("email_title", email_title);
    rs.GetFieldValue("sender_email_name", sender_email_name);
    rs.GetFieldValue("sender_email", sender_email);

    rs.GetFieldValue("smtp_server", smtp_server);
    rs.GetFieldValue("smtp_server_port", smtp_server_port);
    rs.GetFieldValue("smtp_login_id", smtp_login_id);
    rs.GetFieldValue("smtp_login_pw", smtp_login_pw);
    

    if (re_send) {
        CString re_check = CheckCardEmailResend(tno, customer_email);

		if(!re_check.IsEmpty())
            return re_check;
    }

    CString body_html = GetCardEmailBody(body_url);

    if (body_html.IsEmpty())
        return "결제 내역 확인에 실패 했습니다";

    body_html.Replace("$고객명$", customer_name);
    body_html.Replace("$결제여부$", process_state);
    body_html.Replace("$결제여부색상$", process_state_color);
    body_html.Replace("$구매자명$", buyer_name);
    body_html.Replace("$상품명$", goods);
    body_html.Replace("$결제일시제목$", date_title_string);
    body_html.Replace("$결제일시$", date_string);
    body_html.Replace("$주문번호$", order_number);
    body_html.Replace("$결제수단$", card_company);
    body_html.Replace("$결제금액$", amt);
    body_html.Replace("$영수증$", receipt_url);

   CString error;

    try
    {
        CSmtp mail;

        rs.GetFieldValue("smtp_server", smtp_server);
        rs.GetFieldValue("smtp_server_port", smtp_server_port);
        rs.GetFieldValue("smtp_login_id", smtp_login_id);
        rs.GetFieldValue("smtp_login_pw", smtp_login_pw);

		//unsigned short SrvPort
		short sdata;
		_stscanf(smtp_server_port, _T("%d"), (int*)(&sdata));

        //mail.SetSMTPServer(smtp_server, atoi(smtp_server_port)); // smtp 서버
		mail.SetSMTPServer(smtp_server, sdata); // smtp 서버
        mail.SetLogin(smtp_login_id); // 보내는 사람의 login 할 아이디 
        mail.SetPassword(smtp_login_pw); // 보내는 사람의 login password

        //CString item = base64_encode(std::string(email_title)).c_str();
        //item = "=?UTF-8?B?" + item + "?=";
        
        //CString item = GetURLencode(email_title);
        mail.SetSenderName(GetEncodeForEMail(sender_email_name)); // 보내는 사람 이름
        mail.SetSenderMail(sender_email); // 보내는 사람 이메일에 표시할 이메일
        mail.SetReplyTo(""); // 답장 받을 이메일 
        mail.SetSubject(GetEncodeForEMail(email_title)); // 메일의 제목 

        mail.AddRecipient(customer_email, ""); // 받는 사람 이메일 (여러명 추가가능) 
        mail.SetXPriority(XPRIORITY_NORMAL);
        mail.SetXMailer("The Bat! (v3.02) Professional");
        mail.m_bHTML = TRUE;
        mail.AddMsgLine(ChangeMultiByteToUtf8(body_html).c_str());
        mail.SetCharSet("utf-8");
        mail.Send();
    }
    catch (ECSmtp e)
    {
		
		g_bana_log->Print("SMTP: %d %s, %d, %s, %s\n", e.GetErrorNum(), smtp_server, smtp_server_port, smtp_login_id, smtp_login_pw);
		
        //std::cout << "Error: " << e.GetErrorText().c_str() << ".\n";
        error = e.GetErrorText().c_str();
    }

    if (error.IsEmpty())
        InsertCardEmailResendLog(tno, customer_email);

    return error;
}

CString CLogiUtil::CheckCardEmailResend(int tno, CString send_customer_email)
{
    CString alert, error;

    CMkCommand cmd(m_pMkDb, "select_card_pay_info_for_resend_1");
    cmd.AddParameter(tno);
    cmd.AddParameter(send_customer_email);
    CMkParameter* par_alert = cmd.AddParameter(typeString, typeOutput, 100, alert);
    CMkParameter* par_error = cmd.AddParameter(typeString, typeOutput, 100, error);

    if (cmd.Execute()) {
        par_alert->GetValue(alert);
        par_error->GetValue(error);

        if (!error.IsEmpty()) {
            return error;
        }

        if (!alert.IsEmpty()) {
			if (::MessageBox(NULL, alert, "확인", MB_OKCANCEL) != IDOK) {
                return "전송을 취소했습니다";
            }
        }

        return "";
    } 

    return "N/A";
}

void CLogiUtil::InsertCardEmailResendLog(int tno, CString send_customer_email)
{
    CMkCommand cmd(m_pMkDb, "insert_card_pay_resend_mail_log");
    cmd.AddParameter(tno);
    cmd.AddParameter(send_customer_email);
	cmd.AddParameter(m_ui.nCompany);
    cmd.AddParameter(m_ui.nWNo);
    cmd.Execute();
}

std::string CLogiUtil::ChangeMultiByteToUtf8(CString content)
{
    wstring str_uni = CA2W(content);
    string str_utf8 = CW2A(str_uni.c_str(), CP_UTF8);
    return str_utf8;
}

CString CLogiUtil::GetEncodeForEMail(CString content)
{
    if (content.IsEmpty())
        return "";

    CString result = CString(base64_encode(ChangeMultiByteToUtf8(content)).c_str());
    
    return "=?UTF-8?B?" + result + "?=";
}

std::string CLogiUtil::base64_encode(const std::string& in) {

    typedef unsigned char uchar;
    std::string out;

    int val = 0, valb = -6;
    //for (uchar c : in) {
	for (int i = 0; i < in.size(); i++) {
		uchar c = in.at(i);
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}

CString CLogiUtil::GetCardEmailBody(CString body_url)
{
    INTERNET_PORT dwPort;
    DWORD dwServiceType = 0;
    CString strServerName;
    CString strObject;

    if (!AfxParseURL((LPCTSTR)body_url, dwServiceType, strServerName, strObject, dwPort))
    {
        return "";
    }

    CString strJson;
    DWORD  dwFlags = INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE;
    HINTERNET hSession = InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, INTERNET_INVALID_PORT_NUMBER, 0);
    HINTERNET hConnect = InternetConnect(hSession, strServerName, INTERNET_INVALID_PORT_NUMBER, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    HINTERNET hHttpFile = HttpOpenRequest(hConnect, "GET", strObject, HTTP_VERSION, NULL, 0, dwFlags, 0);

    char szHeader[2048] = { 0 };

    if (::HttpSendRequest(hHttpFile, NULL, 0, 0, 0)) {
        char buffer[1025];
        DWORD dwReadByte = 0, dwErrorCount = 0;

        while (::InternetReadFile(hHttpFile, buffer, 1024, &dwReadByte)) {
            buffer[dwReadByte] = 0;
            strJson += buffer;

            if (dwReadByte < 1024) {
                dwErrorCount++;
                if (dwErrorCount > 10) break;
                //else ::WaitForSingleObject(m_hWaitRead, 10); // 50ms 지연
            }
            else dwErrorCount = 0;
        }

        ::InternetCloseHandle(hHttpFile);
    }
    ::InternetCloseHandle(hConnect);
    ::InternetCloseHandle(hSession);

   // return strJson;
	return LF->UTF8ToANSI(strJson);

}

void CLogiUtil::ConvChar(CString& input, CString keyword, CString conv)
{
	int cnt = 0;
	int pos = input.Find(keyword);
	int period = pos + keyword.GetLength();
	CString p = (CString)input.Mid(period, 1);
	if (p == ".") {
		CString sNum = (CString)input.Mid(period + 1, 1);
		if (LF->IsNumeric(sNum)) {
			cnt = _ttoi(sNum);
		}

		input.Delete(period, 2);
	}

	CStringW sInput, sConv, sKeyword;
	sInput = input; sConv = conv; sKeyword = keyword;

	if (cnt > 0)
		sInput.Replace(sKeyword, sConv.Left(cnt));
	else
		sInput.Replace(sKeyword, sConv);

	input = sInput;
}

CString CLogiUtil::GetReplaceChar(CString strInput, CString strSendTel, CString strReceiveTel, CString strRiderPhone)
{
	int nSelItem = GetRcpView()->m_xList.GetSelectedItem();
	CVirtualRecord *pRecord = (CVirtualRecord*)GetRcpView()->m_xList.GetSelectedRows()->GetAt(0)->GetRecord();
	OrderRecord *order = pRecord->GetOrderRecord(nSelItem);
	CString strOutput = strInput;

	if (strInput.Find("[@고객명]") >= 0) ConvChar(strOutput, "[@고객명]", order->strCName.c_str());
	if (strInput.Find("[@대표번호]") >= 0)	 ConvChar(strOutput, "[@대표번호]", strSendTel);
	if (strInput.Find("[@휴대폰]") >= 0) ConvChar(strOutput, "[@휴대폰]", strReceiveTel);
	if (strInput.Find("[@부서]") >= 0) ConvChar(strOutput, "[@부서]", order->info[6].c_str());
	if (strInput.Find("[@담당자]") >= 0) ConvChar(strOutput, "[@담당자]", order->info[39].c_str());
	if (strInput.Find("[@출발동]") >= 0) ConvChar(strOutput, "[@출발동]", order->strStart.c_str());
	if (strInput.Find("[@상세위치]") >= 0) ConvChar(strOutput, "[@상세위치]", order->strSDetail.c_str());
	if (strInput.Find("[@메모]") >= 0) ConvChar(strOutput, "[@메모]", order->strEtc.c_str());
	if (strInput.Find("[@마일리지]") >= 0) ConvChar(strOutput, "[@마일리지]", order->info[70].c_str());
	if (strInput.Find("[@고객명_출]") >= 0) ConvChar(strOutput, "[@고객명_출]", order->strSName.c_str());
	if (strInput.Find("[@대표번호_출]") >= 0) ConvChar(strOutput, "[@대표번호_출]", order->strSPhone.c_str());
	if (strInput.Find("[@휴대폰_출]") >= 0) ConvChar(strOutput, "[@휴대폰_출]", order->strSPhone.c_str());
	if (strInput.Find("[@부서_출]") >= 0) ConvChar(strOutput, "[@부서_출]", order->info[6].c_str());
	if (strInput.Find("[@담당자_출]") >= 0) ConvChar(strOutput, "[@담당자_출]", order->info[10].c_str());
	if (strInput.Find("[@출발동_출]") >= 0) ConvChar(strOutput, "[@출발동_출]", order->info[14].c_str());
	if (strInput.Find("[@상세위치_출]") >= 0) ConvChar(strOutput, "[@상세위치_출]", order->info[46].c_str());
	if (strInput.Find("[@고객명_도]") >= 0) ConvChar(strOutput, "[@고객명_도]", order->info[11].c_str());
	if (strInput.Find("[@대표번호_도]") >= 0) ConvChar(strOutput, "[@대표번호_도]", order->strDPhone.c_str());
	if (strInput.Find("[@휴대폰_도]") >= 0) ConvChar(strOutput, "[@휴대폰_도]", order->strDPhone.c_str());
	if (strInput.Find("[@부서_도]") >= 0) ConvChar(strOutput, "[@부서_도]", "");
	if (strInput.Find("[@담당자_도]") >= 0) ConvChar(strOutput, "[@담당자_도]", order->info[12].c_str());
	if (strInput.Find("[@도착동_도]") >= 0) ConvChar(strOutput, "[@도착동_도]", order->info[16].c_str());
	if (strInput.Find("[@상세위치_도]") >= 0) ConvChar(strOutput, "[@상세위치_도]", order->info[47].c_str());
	if (strInput.Find("[@접수시간]") >= 0) ConvChar(strOutput, "[@접수시간]", order->info[18].c_str());
	if (strInput.Find("[@적요]") >= 0) ConvChar(strOutput, "[@적요]", order->info[38].c_str());
	if (strInput.Find("[@물품]") >= 0) ConvChar(strOutput, "[@물품]", order->info[40].c_str());
	if (strInput.Find("[@인터콜]") >= 0) ConvChar(strOutput, "[@인터콜]", "");
	if (strInput.Find("[@지불]") >= 0) ConvChar(strOutput, "[@지불]", LF->GetPayTypeFromLong(order->nPayType));
	if (strInput.Find("[@차량]") >= 0) ConvChar(strOutput, "[@차량]", LF->GetCarTypeFromLong(order->nCarType));
	if (strInput.Find("[@운송]") >= 0) ConvChar(strOutput, "[@운송]", LF->GetWayTypeFromLong(order->nWayType));
	if (strInput.Find("[@급]") >= 0) ConvChar(strOutput, "[@급]", LF->GetRunTypeFromLong(order->nRunType));
	if (strInput.Find("[@합계]") >= 0) ConvChar(strOutput, "[@합계]", LF->GetStringFromLong(order->nCharge));
	if (strInput.Find("[@합계천]") >= 0) ConvChar(strOutput, "[@합계천]", LF->GetStringFromLong(order->nCharge / 1000));
	if (strInput.Find("[@합계백]") >= 0) ConvChar(strOutput, "[@합계백]", LF->GetStringFromLong(order->nCharge / 100));
	if (strInput.Find("[@탁송]") >= 0) ConvChar(strOutput, "[@탁송]", LF->GetStringFromLong(order->nChargeTrans));
	if (strInput.Find("[@탁송천]") >= 0) ConvChar(strOutput, "[@탁송천]", LF->GetStringFromLong(order->nChargeTrans / 1000));
	if (strInput.Find("[@탁송백]") >= 0) ConvChar(strOutput, "[@탁송백]", LF->GetStringFromLong(order->nChargeTrans / 100));
	if (strInput.Find("[@사번]") >= 0) ConvChar(strOutput, "[@사번]", LF->GetStringFromLong(order->nRNo));
	if (strInput.Find("[@기사명]") >= 0) ConvChar(strOutput, "[@기사명]", order->strRName.c_str());
	if (strInput.Find("[@기사전화번호]") >= 0) ConvChar(strOutput, "[@기사전화번호]", strRiderPhone);
	if (strInput.Find("[@기사위치URL]") >= 0) ConvChar(strOutput, "[@기사위치URL]", "");

	return strOutput;
}
