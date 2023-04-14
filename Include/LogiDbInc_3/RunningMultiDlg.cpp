// RunningDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "RunningMultiDlg.h"
#include "MkCommand.h"
#include "MkDatabase.h"
#include "MkType.h"
#include "QSocket.h"

// CRunningMultiDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRunningMultiDlg, CMyDialog)
CRunningMultiDlg::CRunningMultiDlg(BOOL* pbRet,CMkCommand *pCmd1,CMkCommand *pCmd2, CWnd* pParent)
	: CMyDialog(CRunningMultiDlg::IDD, pParent)
{
	m_pCmd1	= pCmd1;
	m_pCmd2 = pCmd2;
	m_pbRet	= pbRet;
	m_hStopEvent[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hStopEvent[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hEndDialog[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hEndDialog[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hThreadProcEnd[0] = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hThreadProcEnd[1] = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_bDialogShow = FALSE;
	m_bUIThreadEnd = FALSE;
	//	AfxGetApp()->BeginWaitCursor();
}

CRunningMultiDlg::~CRunningMultiDlg()
{
	WaitForMultipleObjects(2, m_hThreadProcEnd, TRUE, 2000);

	CloseHandle(m_hStopEvent[0]);
	CloseHandle(m_hStopEvent[1]);
	CloseHandle(m_hEndDialog[0]);
	CloseHandle(m_hEndDialog[1]);
	CloseHandle(m_hThreadProcEnd[0]);
	CloseHandle(m_hThreadProcEnd[1]);
}

void CRunningMultiDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ELASPED_SECOND, m_ElapsedSec);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgressBar);
}


BEGIN_MESSAGE_MAP(CRunningMultiDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

static LOGFONT lfBoldFont = {12,0,0,0,FW_BOLD,0,0,0,HANGUL_CHARSET,0,0,0,0,"����"};
static CFont *pBoldFont = NULL;
// CRunningMultiDlg �޽��� ó�����Դϴ�.
BOOL CRunningMultiDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_dwLastTickCount = GetTickCount();
	

	DWORD dwThreadID1;
	HANDLE hThread1=::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) staticProc, 
		(LPVOID) this, 0, &dwThreadID1);
	CloseHandle(hThread1);

	HANDLE hThread2=::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) staticProc2, 
		(LPVOID) this, 0, &dwThreadID1);
	CloseHandle(hThread2);

	

	if(WAIT_OBJECT_0 == WaitForMultipleObjects(2, m_hEndDialog, TRUE, 3000))
	{
		EndDialog(IDOK);
		WaitForMultipleObjects(2, m_hThreadProcEnd, TRUE, 3000);
		return TRUE;
	}

	m_bDialogShow = TRUE;

	if(!pBoldFont) {
		pBoldFont = new CFont;
		pBoldFont->CreateFontIndirect(&lfBoldFont);
	}
	m_ElapsedSec.SetFont(pBoldFont);
	m_ProgressBar.SendMessage(WM_SETTEXT, (WPARAM)0, (LPARAM)"ó����");

	if(m_pCmd1->IsPreventCancel())
	{
		m_btnCancel.EnableWindow(FALSE);
		m_btnCancel.SetWindowText("��ҺҰ�");
	}

	CRect rMyRect;
	this->GetWindowRect(rMyRect);
	this->SetWindowPos(&CWnd::wndTop,rMyRect.left+10000,rMyRect.top+10000,0,0,
		SWP_NOSIZE);

	DWORD dwThreadID2;
	HANDLE hThread3=::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) staticProcIamLive, 
		(LPVOID) this, 0, &dwThreadID2);

	CloseHandle(hThread3);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

UINT CRunningMultiDlg::Proc(LPVOID lParam)
{
	m_ProgressBar.SetPos(0);
	*m_pbRet = m_pCmd1->Execute();
	if(TRUE == *m_pbRet )
	{
		*m_pbRet = m_pCmd1->GetRecordset()->Parser();
	}

/*
	if(TRUE == *m_pbRet )
	{
		CString sText;
		sText.Format( "�Ϸ�=>�ļ��۾���"  ) ;
		if(m_bDialogShow)
			m_ElapsedSec.SetWindowText(sText);
	}


	if(m_bDialogShow)
		m_ProgressBar.SetPos(100);
*/
	SetEvent(m_hEndDialog[0]);
	SetEvent(m_hStopEvent[0]);

	if(m_bUIThreadEnd)
		PostMessage(WM_COMMAND,IDOK);

	SetEvent(m_hThreadProcEnd[0]);

	return 0;
}

UINT CRunningMultiDlg::Proc2(LPVOID lParam)
{
	m_ProgressBar.SetPos(0);
	*m_pbRet = m_pCmd2->Execute();
	if(TRUE == *m_pbRet )
	{
		*m_pbRet = m_pCmd2->GetRecordset()->Parser();
	}

	/*
	if(TRUE == *m_pbRet )
	{
	CString sText;
	sText.Format( "�Ϸ�=>�ļ��۾���"  ) ;
	if(m_bDialogShow)
	m_ElapsedSec.SetWindowText(sText);
	}


	if(m_bDialogShow)
	m_ProgressBar.SetPos(100);
	*/
	SetEvent(m_hEndDialog[1]);
	SetEvent(m_hStopEvent[1]);

	if(m_bUIThreadEnd)
		PostMessage(WM_COMMAND,IDOK);

	SetEvent(m_hThreadProcEnd[1]);

	return 0;
}




UINT CRunningMultiDlg::ProcIamLive(LPVOID lParam)
{
//	int m_dwLastTickCount = ::GetTickCount();
	int dwLastSecond    = m_dwLastTickCount;
	int dwInitSecond    = m_dwLastTickCount;
	CString sText;
	CString sText_Old;
	CRect rMyRect;

	
	BOOL bWindowVisible = FALSE;
	int iCnt = 0;
	while(WAIT_OBJECT_0 != WaitForMultipleObjects(2, m_hStopEvent, TRUE, 100)) 
	{
		if(m_pCmd1->GetDatabase()->IsShownErrorDialog() ||
			m_pCmd2->GetDatabase()->IsShownErrorDialog())
		{
			CRect rMyRect;
			this->GetWindowRect(rMyRect);
			this->SetWindowPos(&CWnd::wndTop,rMyRect.left+10000,rMyRect.top+10000,0,0,
				SWP_NOSIZE);

			m_bUIThreadEnd = TRUE;
			return 0;
		}

		sText.Format("%d�� ���", (GetTickCount() - dwInitSecond) / 1000);
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
			m_pCmd1->GetDatabase()->GetSocket()->SendCommand(PT_CONNTEST);
			m_pCmd2->GetDatabase()->GetSocket()->SendCommand(PT_CONNTEST);
			m_dwLastTickCount = ::GetTickCount();
		}
	}


	PostMessage(WM_COMMAND,IDOK);

	return 0;
}

void CRunningMultiDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
//	AfxGetApp()->EndWaitCursor();
	OnOK();	
}

void CRunningMultiDlg::OnBnClickedCancel()
{
	m_pCmd1->GetDatabase()->SetUserStop();
	m_pCmd1->GetDatabase()->GetSocket()->Close();
	m_pCmd2->GetDatabase()->GetSocket()->Close();
}

int CRunningMultiDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMyDialog::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}


static HBRUSH* phBrush = NULL;
static HBRUSH* phBrush2 = NULL;

HBRUSH CRunningMultiDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

