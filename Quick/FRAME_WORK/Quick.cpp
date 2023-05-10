// Quick.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "MainFrm.h"

#include "QuickDoc.h"
#include "QuickView.h"
#include "DummyView.h"
#include "afxwin.h"
#include "LogonDlg.h"
#include "ShareReportRateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW 
#endif

// CQuickApp

BEGIN_MESSAGE_MAP(CQuickApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

// CQuickApp ����

CQuickApp::CQuickApp()
{
	m_pMkDb = NULL;
}

CQuickApp::~CQuickApp()
{
	delete LU;
}


// ������ CQuickApp ��ü�Դϴ�.

CQuickApp theApp;
ULONG_PTR m_gdiplusToken;

// CQuickApp �ʱ�ȭ
BOOL CQuickApp::InitInstance()
{
	// ���ø����̼� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�. 
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// OLE ���̺귯���� �ʱ�ȭ�մϴ�.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// RichEdit ��Ʈ���� ����Ϸ��� AfxInitRichEdit2()�� �־�� �մϴ�.
	AfxInitRichEdit2();

//	afxAmbientActCtx = FALSE;
	SetRegistryKey(_T("Logisoft"));
	LoadStdProfileSettings(4);  // MRU�� �����Ͽ� ǥ�� INI ���� �ɼ��� �ε��մϴ�.

	CXTPWinDwmWrapper().SetProcessDPIAware();

	LF = new CLogiFunc;

	LU = new CLogiUtil;
	LU->Init();
	LU->InstallMalgunFont();
	LU->LoadSkinManager();
	LU->CheckDebugLogMode();

	CString strSubKey = "Software\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_BROWSER_EMULATION";
	::WriteRegistryInt(HKEY_CURRENT_USER, strSubKey, "Quick.exe", 11000);

	if(!LU->SetServerInfo())
		return FALSE;

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	char szID[50] = { 0 };
	char szLogiCode[50] = { 0 };
	char szLogiNo[50] = { 0 };

	if(!LU->CheckCommandLine(szID, szLogiCode, szLogiNo))
		return FALSE;

	//CMkCommand pCmd(m_pMkDb, "test_test");
	//CMkParameter *pParOut = pCmd.AddParameter(typeInt, typeReturn, sizeof(int), 0);
	//pCmd.AddParameter(0);
	//if(pCmd.Execute())
	//{
	//	CString str;
	//	str.Format("RET=%d\n", pParOut->GetLong());
	//	MessageBox(NULL, str, str, MB_OK);
	//}

	//return FALSE;


	if(!LU->Logon(szID))
		return FALSE;

	LU->SetSystemTimeLikeServer();

#ifndef _DEBUG
//	if(m_ui.bBlankPassword)
//		SetCrashHandlerFilter(&TheCrashHandlerFunction);
//	else
		SetCrashHandlerFilter(&TheCrashHandlerNormalFunction);
#endif 

	if(!LU->ShowShareReportDlg())
		return FALSE;

#ifndef _DEBUG
	if(!m_ui.bDeveloper)
		LU->SetClearType();
#endif 

	LU->CheckRegistryInfo();

	// ���� ���α׷��� ���� ���ø��� ����մϴ�. ���� ���ø���
	// ����, ������ â �� �� ������ ���� ������ �մϴ�.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CQuickDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ������ â�Դϴ�.
		RUNTIME_CLASS(CQuickView));

	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// ����ٿ� ������ ����� ����ġ�մϴ�. ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
	if(!ProcessShellCommand(cmdInfo))
		return FALSE;
	// â �ϳ��� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.

	LU->ShowMemberChargeDlg(  TRUE);
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	// ���̻簡 ���� ��쿡�� DragAcceptFiles�� ȣ���մϴ�.
	// SDI ���� ���α׷������� ProcessShellCommand �Ŀ� �̷��� ȣ���� �߻��ؾ� �մϴ�.
	return TRUE;
}

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CMyDialog
{
public:
	CAboutDlg();

// ��ȭ ���� ������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����

// ����
protected:
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_VersionStatic;
	CString m_strVersion;
	afx_msg void OnBnClickedCrashBtn();
};

CAboutDlg::CAboutDlg() : CMyDialog(CAboutDlg::IDD)
{
}


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VERSION_STATIC, m_VersionStatic);
	DDX_Text(pDX, IDC_VERSION_STATIC, m_strVersion);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CRASH_BTN, &CAboutDlg::OnBnClickedCrashBtn)
END_MESSAGE_MAP()

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� ����Դϴ�.
void CQuickApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.m_strVersion.Format("��������Ʈ ����ƮQ ��%s", LF->GetMyFileVersion());
	aboutDlg.DoModal();
}

int CQuickApp::ExitInstance()
{
	DELETE_OBJECT(LU);

	Gdiplus::GdiplusShutdown(m_gdiplusToken);
	return CWinApp::ExitInstance();
}

void CAboutDlg::OnBnClickedCrashBtn()
{
	/*char *p = 0;
	*p = 1;*/
}
