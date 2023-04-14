// RcpPageMemoForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RcpPageMemoForm.h"


// CRcpPageMemoForm

IMPLEMENT_DYNCREATE(CRcpPageMemoForm, CMyFormView)

CRcpPageMemoForm::CRcpPageMemoForm()
	: CMyFormView(CRcpPageMemoForm::IDD)
{
}

CRcpPageMemoForm::~CRcpPageMemoForm()
{
}

void CRcpPageMemoForm::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NOTEPAD_EDIT, m_edtNotePad);
	DDX_Control(pDX, IDC_OPEN_NOTEPAD_BTN, m_btnOpenNotePad);
	DDX_Control(pDX, IDC_SAVE_TEXT_BTN, m_btnSaveText);
	DDX_Control(pDX, IDC_LOAD_TEXT_BTN, m_btnLoadText);
}

BEGIN_MESSAGE_MAP(CRcpPageMemoForm, CMyFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_OPEN_NOTEPAD_BTN, OnBnClickedOpenNotepadBtn)
	ON_EN_KILLFOCUS(IDC_NOTEPAD_EDIT, OnEnKillfocusNotepadEdit)
	ON_BN_CLICKED(IDC_SAVE_TEXT_BTN, OnBnClickedSaveTextBtn)
	ON_BN_CLICKED(IDC_LOAD_TEXT_BTN, OnBnClickedLoadTextBtn)
END_MESSAGE_MAP()


// CRcpPageMemoForm 진단입니다.

#ifdef _DEBUG
void CRcpPageMemoForm::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CRcpPageMemoForm::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CRcpPageMemoForm 메시지 처리기입니다.

void CRcpPageMemoForm::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	//char buffer[20];
	//CString sNote = AfxGetApp()->GetProfileString("RcpPageInfoForm", (CString)itoa(m_ui.nCompany, buffer, 10) + (CString)itoa(m_ui.nWNo, buffer, 10), "");
	//m_edtNotePad.SetWindowText(sNote);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void CRcpPageMemoForm::OnSize(UINT nType, int cx, int cy)
{
	CMyFormView::OnSize(nType, cx, cy);

	if(m_edtNotePad.GetSafeHwnd())
	{
		
		CRect rc, rcEdt, rcOpenBtn, rcLoadBtn, rcSaveBtn; 
		GetClientRect(rc);
		m_edtNotePad.GetWindowRect(rcEdt);
		m_btnOpenNotePad.GetWindowRect(rcOpenBtn);
		m_btnLoadText.GetWindowRect(rcLoadBtn);
		m_btnSaveText.GetWindowRect(rcSaveBtn);
		ScreenToClient(rcEdt);
		ScreenToClient(rcOpenBtn);
		ScreenToClient(rcLoadBtn);
		ScreenToClient(rcSaveBtn);

		rcEdt.right = rcOpenBtn.left - 5;
		rcEdt.bottom = rc.bottom - 5;

		long nHeight = rcEdt.Height();

		rcSaveBtn.right = rc.right - 5;
		rcSaveBtn.left = rcSaveBtn.right - 90;
		rcSaveBtn.bottom = rcSaveBtn.top + (nHeight / 3) - 1;

		rcLoadBtn.right = rcSaveBtn.right;
		rcLoadBtn.left = rcSaveBtn.left;
		rcLoadBtn.top = rcSaveBtn.bottom + 1;
		rcLoadBtn.bottom = rcLoadBtn.top + (nHeight / 3) - 1;

		rcOpenBtn.right = rcSaveBtn.right;
		rcOpenBtn.left = rcSaveBtn.left; 
		rcOpenBtn.top = rcLoadBtn.bottom + 1;
		rcOpenBtn.bottom = rcEdt.bottom;

		//rcList.right = rc.right - 2;
		m_edtNotePad.MoveWindow(rcEdt);  
		m_btnOpenNotePad.MoveWindow(rcOpenBtn);
		m_btnLoadText.MoveWindow(rcLoadBtn);
		m_btnSaveText.MoveWindow(rcSaveBtn);
	}
}

void CRcpPageMemoForm::OnBnClickedOpenNotepadBtn()
{
	OpenNotePad();
}

void CRcpPageMemoForm::OpenNotePad()
{
	DWORD dwProcessID; 
	RunProgram("notepad", "", dwProcessID); 

	BOOL bRead = EnumWindows(MyEnumProc,(LPARAM)&dwProcessID);
	HWND hWnd = (HWND)dwProcessID; 

	long nCount = 0;

	if(bRead == TRUE)
	{
		while(1)
		{
			Sleep(100);

			if(nCount > 3)
				break;

			if(bRead == FALSE)
			{
				hWnd = (HWND)dwProcessID;
				break;
			}

			bRead = EnumWindows(MyEnumProc,(LPARAM)&dwProcessID);
			nCount++;
		}
	}

	if(bRead == TRUE)
	{
		MessageBox("메모장 텍스트 정보 읽기에 실패했습니다", "확인", MB_ICONINFORMATION);
		return;
	}


	//HWND hWnd = ::FindWindow("Notepad",NULL);

	if(IsWindow(hWnd)) {
		HWND hFindHwd = ::FindWindowEx(hWnd,NULL,"Edit",NULL);

		if(hFindHwd)
		{
			SendToNotePad(hFindHwd);
		}
		else
		{
			MessageBox("메모장 텍스트 정보 읽기에 실패했습니다", "확인", MB_ICONINFORMATION);
		}			
	}
}

BOOL CRcpPageMemoForm::SendToNotePad(HWND hFindHwd)
{
	CString sNote; m_edtNotePad.GetWindowText(sNote);
	char* chBuf = LPSTR(LPCTSTR(sNote)); 

	char buf[1000]={0};	
	::SendMessage(hFindHwd,WM_SETTEXT,1000,(LPARAM)buf);	

	if(buf[0]!=0)
		sNote += CString(buf) + "\r\n" + sNote;

	::SendMessage(hFindHwd,WM_SETTEXT,0,(LPARAM)(LPCTSTR)sNote);

	return TRUE;

}

HANDLE CRcpPageMemoForm::RunProgram(CString strFileName, CString strArg, DWORD &pID)
{
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;

	if(!strArg.IsEmpty())
		strFileName += " " + strArg;

	BOOL fSuccess = CreateProcess(NULL, (LPSTR)(LPCTSTR)strFileName, NULL, NULL, 0, 
		CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);

	if(fSuccess) {
		pID = pi.dwProcessId;
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}
	return pi.hProcess;
}

static BOOL CALLBACK MyEnumProc(HWND hwnd, LPARAM lParam)
{
	DWORD *pDWord = (DWORD*)lParam;
	DWORD dwTargetProcessId = *pDWord;
	DWORD dwProcessID = 0;

	if(GetWindowThreadProcessId(hwnd, &dwProcessID))
	{
		if(dwProcessID == dwTargetProcessId)
		{
			*pDWord = (DWORD)hwnd;	
			return FALSE;
		}
	}
	return TRUE;
}

void CRcpPageMemoForm::OnEnKillfocusNotepadEdit()
{
	//char buffer[20];
	//CString sNote; m_edtNotePad.GetWindowText(sNote);
	//AfxGetApp()->WriteProfileString("RcpPageInfoForm", (CString)itoa(m_ui.nCompany, buffer, 10) + (CString)itoa(m_ui.nWNo, buffer, 10), sNote);
}

void CRcpPageMemoForm::LoadText()
{
	CString sMemo = "";

	CMkCommand pCmd(m_pMkDb, "user_text_load");
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.nWNo);
	CMkParameter *pPar = pCmd.AddParameter(typeString, typeOutput, 300, "");

	if(pCmd.Execute())
	{
		pPar->GetValue(sMemo);
		m_edtNotePad.SetWindowText(sMemo);
	}
}

void CRcpPageMemoForm::SaveText()
{
	 CString sMemo; m_edtNotePad.GetWindowText(sMemo); 
	
	 CMkCommand pCmd(m_pMkDb, "user_text_save");
	 pCmd.AddParameter(m_ui.nCompany);
	 pCmd.AddParameter(m_ui.nWNo);
	 pCmd.AddParameter(sMemo);

	 pCmd.Execute();

}

void CRcpPageMemoForm::OnBnClickedSaveTextBtn()
{
	SaveText();
}

void CRcpPageMemoForm::OnBnClickedLoadTextBtn()
{
	LoadText();
}
