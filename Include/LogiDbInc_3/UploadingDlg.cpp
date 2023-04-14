// UploadingDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "UploadingDlg.h"
#include "MkCommand.h"
#include "MkDatabase.h"
#include "MkType.h"
#include "resource.h"
#include "QSocket.h"

// CUploadingDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CUploadingDlg, CMyDialog)
CUploadingDlg::CUploadingDlg(BOOL* pbRet,CWnd* pParent, CMkDatabase *pDb, CString strFileName, char *pBuffer, DWORD dwLength)
: CMyDialog(CUploadingDlg::IDD, pParent)
{
	m_pbRet	= pbRet;
	m_pDb = pDb;
	m_strFileName = strFileName;
	m_pBuffer = pBuffer;
	m_dwLength = dwLength;
	
	m_hStopEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hEndDialog = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hThreadProcEnd = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_bDialogShow = FALSE;
	m_bUIThreadEnd = FALSE;
	//	AfxGetApp()->BeginWaitCursor();
}

CUploadingDlg::~CUploadingDlg()
{
	WaitForSingleObject(m_hThreadProcEnd, 2000);

	CloseHandle(m_hStopEvent);
	CloseHandle(m_hEndDialog);
	CloseHandle(m_hThreadProcEnd);
}

void CUploadingDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_INFO, m_InfoStatic);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgressBar);
}


BEGIN_MESSAGE_MAP(CUploadingDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

static LOGFONT lfBoldFont = {12,0,0,0,FW_BOLD,0,0,0,HANGUL_CHARSET,0,0,0,0,"����"};
static CFont *pBoldFont = NULL;
// CUploadingDlg �޽��� ó�����Դϴ�.
BOOL CUploadingDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_dwLastTickCount = GetTickCount();


	DWORD dwThreadID1;
	HANDLE hThread1=::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) staticProc, 
		(LPVOID) this, 0, &dwThreadID1);
	CloseHandle(hThread1);

	if(WAIT_OBJECT_0 == WaitForSingleObject(m_hEndDialog, 1000))
	{
		EndDialog(IDOK);
		WaitForSingleObject(m_hThreadProcEnd, 3000);
		return TRUE;
	}

	m_bDialogShow = TRUE;

	if(!pBoldFont) {
		pBoldFont = new CFont;
		pBoldFont->CreateFontIndirect(&lfBoldFont);
	}
	m_InfoStatic.SetFont(pBoldFont);
	m_ProgressBar.SendMessage(WM_SETTEXT, (WPARAM)0, (LPARAM)"ó����");

/*
	CRect rMyRect;
	this->GetWindowRect(rMyRect);
	this->SetWindowPos(&CWnd::wndTop,rMyRect.left+10000,rMyRect.top+10000,0,0,
		SWP_NOSIZE);
*/
	DWORD dwThreadID2;
	HANDLE hThread2=::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) staticProcIamLive, 
		(LPVOID) this, 0, &dwThreadID2);

	CloseHandle(hThread2);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

UINT CUploadingDlg::Proc(LPVOID lParam)
{
	m_ProgressBar.SetPos(0);

	*m_pbRet = m_pDb->UploadFile(m_strFileName, m_pBuffer, m_dwLength);

	SetEvent(m_hEndDialog);
	SetEvent(m_hStopEvent);

	if(m_bUIThreadEnd)
		PostMessage(WM_COMMAND,IDOK);

	SetEvent(m_hThreadProcEnd);

	return 0;
}

UINT CUploadingDlg::ProcIamLive(LPVOID lParam)
{
	int dwLastSecond    = m_dwLastTickCount;
	int dwInitSecond    = m_dwLastTickCount;
	CString sText;
	CString sText_Old;
	CRect rMyRect;
	char buffer[10];

	m_ProgressBar.SetRange(0, m_dwLength);


	BOOL bWindowVisible = FALSE;
	int iCnt = 0;
	while(WAIT_OBJECT_0 != WaitForSingleObject(m_hStopEvent, 100)) 
	{
		if(m_pDb->IsShownErrorDialog())
		{
			CRect rMyRect;
			this->GetWindowRect(rMyRect);
			this->SetWindowPos(&CWnd::wndTop,rMyRect.left+10000,rMyRect.top+10000,0,0,
				SWP_NOSIZE);

			m_bUIThreadEnd = TRUE;
			return 0;
		}

/*
		if(FALSE == bWindowVisible)
		{
			CRect rMyParentRect;
			CRect rMyRect;

			this->GetWindowRect(rMyRect);
			GetDesktopWindow()->GetClientRect(rMyParentRect);
			int left = (rMyParentRect.Width()-rMyRect.Width())/2;
			int top  = (rMyParentRect.Height()-rMyRect.Height())/2;
			if(left < 0) left = 0;
			if(top  < 0) top = 0;
			this->SetWindowPos(&CWnd::wndTopMost,left ,top,0,0,SWP_NOSIZE);
			bWindowVisible = TRUE;
			//			AfxGetApp()->EndWaitCursor();

		}
*/
		int dwGap = ::GetTickCount() - m_dwLastTickCount;
		m_ProgressBar.SetPos(m_pDb->GetSendSize());
		m_ProgressBar.SetWindowText(ltoa(m_pDb->GetSendSize() * 100 / m_dwLength, buffer, 10) + CString("%"));
		sText.Format("%d / %d byte", m_pDb->GetSendSize(), m_dwLength);
		m_InfoStatic.SetWindowText(sText);
	}


	PostMessage(WM_COMMAND,IDOK);

	return 0;
}

void CUploadingDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//	AfxGetApp()->EndWaitCursor();
	OnOK();	
}

void CUploadingDlg::OnBnClickedCancel()
{
	//	SetEvent(m_hStopEvent);
	m_pDb->SetUserStop();
	m_pDb->GetSocket()->Close();
}

int CUploadingDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMyDialog::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}


static HBRUSH* phBrush = NULL;
static HBRUSH* phBrush2 = NULL;

HBRUSH CUploadingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.


	if(!phBrush)
	{
		phBrush = new HBRUSH;
		*phBrush = CreateSolidBrush(RGB(118, 146, 185));
	}

	if(!phBrush2)
	{
		phBrush2 = new HBRUSH;
		*phBrush2 = CreateSolidBrush(RGB(119, 147, 185));
	}

	if( this == pWnd )
	{
		return *phBrush2;

	}

	if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));		
		return *phBrush;
	}


	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

