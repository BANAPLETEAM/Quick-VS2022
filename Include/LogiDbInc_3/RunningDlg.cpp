// RunningDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RunningDlg.h"
#include ".\runningdlg.h"
#include "MkCommand.h"
#include "MkDatabase.h"
#include "MkType.h"
#include "QSocket.h"

// CRunningDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRunningDlg, CMyDialog)
CRunningDlg::CRunningDlg(BOOL* pbRet,CMkCommand *pCmd,CWnd* pParent)
	: CMyDialog(CRunningDlg::IDD, pParent)
{
	m_pCmd	= pCmd;
	m_pbRet	= pbRet;
	m_hStopEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hEndDialog = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hThreadProcEnd = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_bDialogShow = FALSE;
	m_bUIThreadEnd = FALSE;
	//	AfxGetApp()->BeginWaitCursor();
}

CRunningDlg::~CRunningDlg()
{
	WaitForSingleObject(m_hThreadProcEnd, 2000);

	CloseHandle(m_hStopEvent);
	CloseHandle(m_hEndDialog);
	CloseHandle(m_hThreadProcEnd);
}

void CRunningDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ELASPED_SECOND, m_ElapsedSec);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgressBar);
}


BEGIN_MESSAGE_MAP(CRunningDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

static LOGFONT lfBoldFont = {12,0,0,0,FW_BOLD,0,0,0,HANGUL_CHARSET,0,0,0,0,"돋움"};
static CFont *pBoldFont = NULL;
// CRunningDlg 메시지 처리기입니다.
BOOL CRunningDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_dwLastTickCount = GetTickCount();
	

	DWORD dwThreadID1;
	HANDLE hThread1=::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) staticProc, 
		(LPVOID) this, 0, &dwThreadID1);
	CloseHandle(hThread1);

	if(WAIT_OBJECT_0 == WaitForSingleObject(m_hEndDialog, 3000))
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
	m_ElapsedSec.SetFont(pBoldFont);
	m_ProgressBar.SendMessage(WM_SETTEXT, (WPARAM)0, (LPARAM)"처리중");

	if(m_pCmd->IsPreventCancel())
	{
		m_btnCancel.EnableWindow(FALSE);
		m_btnCancel.SetWindowText("취소불가");
	}

	CRect rMyRect;
	this->GetWindowRect(rMyRect);
	this->SetWindowPos(&CWnd::wndTop,rMyRect.left+10000,rMyRect.top+10000,0,0,
		SWP_NOSIZE);

	DWORD dwThreadID2;
	HANDLE hThread2=::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) staticProcIamLive, 
		(LPVOID) this, 0, &dwThreadID2);

	CloseHandle(hThread2);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

UINT CRunningDlg::Proc(LPVOID lParam)
{
	m_ProgressBar.SetPos(0);
	*m_pbRet = m_pCmd->Execute();
	if(TRUE == *m_pbRet )
	{
		*m_pbRet = m_pCmd->GetRecordset()->Parser();
	}

/*
	if(TRUE == *m_pbRet )
	{
		CString sText;
		sText.Format( "완료=>후속작업중"  ) ;
		if(m_bDialogShow)
			m_ElapsedSec.SetWindowText(sText);
	}


	if(m_bDialogShow)
		m_ProgressBar.SetPos(100);
*/
	SetEvent(m_hEndDialog);
	SetEvent(m_hStopEvent);

	if(m_bUIThreadEnd)
		PostMessage(WM_COMMAND,IDOK);

	SetEvent(m_hThreadProcEnd);

	return 0;
}

UINT CRunningDlg::ProcIamLive(LPVOID lParam)
{
//	int m_dwLastTickCount = ::GetTickCount();
	int dwLastSecond    = m_dwLastTickCount;
	int dwInitSecond    = m_dwLastTickCount;
	CString sText;
	CString sText_Old;
	CRect rMyRect;

	
	BOOL bWindowVisible = FALSE;
	int iCnt = 0;
	while(WAIT_OBJECT_0 != WaitForSingleObject(m_hStopEvent, 100)) 
	{
		if(m_pCmd->GetDatabase()->IsShownErrorDialog())
		{
			CRect rMyRect;
			this->GetWindowRect(rMyRect);
			this->SetWindowPos(&CWnd::wndTop,rMyRect.left+10000,rMyRect.top+10000,0,0,
				SWP_NOSIZE);

			m_bUIThreadEnd = TRUE;
			return 0;
		}

		sText.Format("%d초 경과", (GetTickCount() - dwInitSecond) / 1000);
		m_ElapsedSec.SetWindowText(sText);

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

		int dwGap = ::GetTickCount() - m_dwLastTickCount;
		m_ProgressBar.SetPos( (dwGap % 10000)/100 );

		if( dwGap > 30*1000)
		{
			m_pCmd->GetDatabase()->GetSocket()->SendCommand(PT_CONNTEST);
			m_dwLastTickCount = ::GetTickCount();
		}
	}


	PostMessage(WM_COMMAND,IDOK);

	return 0;
}

void CRunningDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	AfxGetApp()->EndWaitCursor();
	OnOK();	
}

void CRunningDlg::OnBnClickedCancel()
{
//	SetEvent(m_hStopEvent);
	m_pCmd->GetDatabase()->SetUserStop();
	m_pCmd->GetDatabase()->GetSocket()->Close();
}

int CRunningDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMyDialog::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}


static HBRUSH* phBrush = NULL;
static HBRUSH* phBrush2 = NULL;

HBRUSH CRunningDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	

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
	

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

