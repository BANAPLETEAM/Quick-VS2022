// NewMsgDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "NewMsgDlg.h"
#include "MainFrm.h"
#include "MkMessenger.h"
#include "AddHotMsgDlg.h"


#define ID_MENU_MSG_BUSY		0xC000
#define ID_MENU_MSG_ADD			0xC001
#define ID_MENU_MSG				0xF000



// CNewMsgDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CNewMsgDlg, CMyDialog)
CNewMsgDlg::CNewMsgDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CNewMsgDlg::IDD, pParent)
{
	m_pParentWnd = pParent;
	m_nSendType = 0;
	m_bNoFocus = FALSE;
	m_pMainDb = NULL;

	m_dwLastTyping = 0;
	m_hTypeingHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hExitHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hThreadDiedHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
}

CNewMsgDlg::~CNewMsgDlg()
{
	SetEvent(m_hExitHandle);
	WaitForSingleObject(m_hThreadDiedHandle, 2000);

	CloseHandle(m_hTypeingHandle);
	CloseHandle(m_hExitHandle);
	CloseHandle(m_hThreadDiedHandle);
}

void CNewMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEND_EDIT, m_edtSend);
	DDX_Text(pDX, IDC_SEND_EDIT, m_strSend);
	DDV_MaxChars(pDX, m_strSend, 9000);
	DDX_Control(pDX, IDC_SHOW_JUST_POPUP_CHECK, m_chkShowJustPopup);
	DDX_Control(pDX, IDC_INFO_STATIC, m_stcInfo);
	DDX_Control(pDX, IDC_NO_CLOSE_CHECK, m_chkNoClose);
	DDX_Control(pDX, IDC_MSG_RICH_EDIT, m_edtMsgRich);
	DDX_Control(pDX, IDC_MENU_BTN, m_btnMenu);
}


BEGIN_MESSAGE_MAP(CNewMsgDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SEND_MSG_BTN, OnBnClickedSendMsgBtn)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SHOW_JUST_POPUP_CHECK, &CNewMsgDlg::OnBnClickedShowJustPopupCheck)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_SEND_EDIT, OnEnChangeSendEdit)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_NO_CLOSE_CHECK, &CNewMsgDlg::OnBnClickedNoCloseCheck)
	ON_COMMAND_RANGE(ID_MENU_MSG_BUSY, ID_MENU_MSG_BUSY, OnMenuHotMsg)
	ON_COMMAND_RANGE(ID_MENU_MSG_ADD, ID_MENU_MSG_ADD, OnMenuHotMsg)
	ON_COMMAND_RANGE(ID_MENU_MSG, ID_MENU_MSG + 100, OnMenuHotMsg)
	ON_COMMAND_RANGE(ID_MENU_MSG + 100,ID_MENU_MSG + 200, OnMenuHotMsg)
	ON_COMMAND_RANGE(ID_MENU_MSG + 200,ID_MENU_MSG + 300, OnMenuHotMsg)
	ON_COMMAND_RANGE(ID_MENU_MSG + 300,ID_MENU_MSG + 400, OnMenuHotMsg)
	ON_BN_CLICKED(IDC_MENU_BTN, &CNewMsgDlg::OnBnClickedMenuBtn)
END_MESSAGE_MAP()


// CNewMsgDlg 메시지 처리기입니다.

BOOL CNewMsgDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	//SetWindowPos(&CWnd::wndTopMost, 0,0,0, 0, SWP_NOSIZE | SWP_NOMOVE);

#ifdef _SYSMANAGER
	m_pMainDb = m_pSysmanager;
#else 
	m_pMainDb = m_pMkDb;
#endif

	DWORD dwThreadID1;
	HANDLE hThread1=::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) staticTypingProc, 
		(LPVOID) this, 0, &dwThreadID1);
	CloseHandle(hThread1);

	m_chkShowJustPopup.SetCheck( AfxGetApp()->GetProfileInt("Messenger", "ShowJustPopup", 0));
	m_chkNoClose.SetCheck(AfxGetApp()->GetProfileInt("Messenger", "NoClose", 0));

	PrintInfo(" 대화를 시작합니다.");

	m_edtMsgRich.SetAutoURLDetect(1);
	m_edtMsgRich.SetFont(m_FontManager.GetFont("돋움", 13, FW_NORMAL));

	if(m_nSendType > 0)
	{
		SetWindowText(m_nSendType == TYPE_COMPANY ? "전체대화(지사제외)" : "전체대화(지사포함)");
		CString strText= "전체대화를 시작합니다.\r\n\r\n";
		COLORREF crText = RGB(180, 180, 30);
		m_edtMsgRich.AddMsg(strText, crText);
	}
#ifdef _SYSMANAGER
	else if(m_strCompanyCode == "200")
	{
		SetWindowText(m_strName + "/" + m_strCompanyName);
		CString strText= m_strCompanyName + "/" + m_strName + 
						" 님과의 대화를 시작합니다.\r\n\r\n";
		COLORREF crText = RGB(0, 90, 0);
		m_edtMsgRich.AddMsg(strText, crText);
	}
	else
	{
		SetWindowText(m_strName + "/" + m_strCompanyName);
		CString strText= m_strCompanyName + "/" + m_strName + "\r\n코드: " + m_strCompanyCode + 
			" , 사번: " + m_strMNo + " , 관리자ID: " + GetAdminID() +
			"\r\n님과의 대화를 시작합니다.\r\n\r\n";
		COLORREF crText = RGB(0, 00, 90);
		m_edtMsgRich.AddMsg(strText, crText);
	}
#else
	else
	{
		SetWindowText(m_strName + "/" + m_strCompanyName);
		CString strText= m_strCompanyName + "/" + m_strName + 
			" 님과의 대화를 시작합니다.\r\n\r\n";
		COLORREF crText = RGB(0, 90, 0);
		m_edtMsgRich.AddMsg(strText, crText);
	}
#endif

	MoveClient();

	if(m_bNoFocus)
		return FALSE;
	else
	{
		m_edtSend.SetFocus();
		return TRUE; 
	}
}

#ifdef _SYSMANAGER
CString CNewMsgDlg::GetAdminID()
{
	CMkCommand pCmd(m_pMkDbDaeri1, "select_admin_id");
	pCmd.AddParameter(typeLong , typeInput, sizeof(long), atol(m_strCompanyCode));	
	CMkParameter *parID = pCmd.AddParameter(typeString, typeOutput, 50, "");	
	if(pCmd.Execute())
		return parID->GetString();

	return "N/A";
}
#endif

void CNewMsgDlg::OnBnClickedSendMsgBtn()
{
	m_edtSend.GetWindowText(m_strSend);
	SendMsg(m_strSend);
	m_strSend = "";
	m_edtSend.SetWindowText(m_strSend);
	m_edtSend.SetFocus();
}

void CNewMsgDlg::SendMsg(CString strMsg, BOOL bNoShow)
{
	char buffer[10000], temp[12];

	if(!m_pSocket->IsConnected())
	{
		MessageBox("현재 연결되어있지 않습니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	STRCPY(buffer, m_strCompanyCode, m_strMNo, strMsg, m_strIntercall, 
		ltoa(m_nSendType, temp, 10), VL_END);

	if(!bNoShow)
	{
		UpdateData(TRUE);
		CString strName;
		COLORREF crColor = RGB(130, 130, 130);
		strName.Format("%s:\r\n", 
			m_strMyName);

		m_edtMsgRich.AddName(strName, crColor);
		crColor = RGB(0, 0, 255);
		m_edtMsgRich.AddText(strMsg + "\r\n", crColor);	
	}

	if(!m_pSocket->SendData(PT_REQUEST, PST_SEND_MSG3, buffer))
	{
		if(!bNoShow)
		{
			CString strMsg = "아래메시지를 전달 하지 못했습니다.\r\n" + strMsg + "\r\n";
			COLORREF crMsg =  RGB(255, 0, 0);
			m_edtMsgRich.AddMsg(strMsg, crMsg, 0, 1); 
			UpdateData(FALSE);
		}
	}

	m_dwLastTyping = 0;
}


BOOL CNewMsgDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN)		
		{
			switch(::GetDlgCtrlID(pMsg->hwnd))
			{
				case IDC_SEND_EDIT:
				{
					if(!(GetKeyState(VK_CONTROL) & 0x8000))
					{
						OnBnClickedSendMsgBtn();
						return TRUE;
					}
				}
			}
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CNewMsgDlg::OnContextMenu()
{
	CPoint pt; 
	GetCursorPos(&pt);

	CMenu *pMainMenu = new CMenu;
	pMainMenu->CreatePopupMenu();
	pMainMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_MSG_BUSY, "통화중");
	pMainMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_MSG_ADD, "메모리 추가");

	CMkRecordset pRs(m_pMainDb);
	CMkCommand pCmd(m_pMainDb, "select_hot_msg");	
	pCmd.AddParameter(m_ci.m_nCompanyCode);					
	pCmd.AddParameter(m_ui.nWNo);					
	pCmd.AddParameter(MESSENGER_HOT_MSG);					
	if(pRs.Execute(&pCmd))
	{		
		CString strTitle, strMsg;
		CString strMenuText;
		m_saHotMsg.RemoveAll();
		m_saHotMsgTitle.RemoveAll();

		CMenu *pEditMenu = new CMenu;
		CMenu *pDeleteMenu = new CMenu;
		CMenu *pNotSendMenu = 0;
		pEditMenu->CreatePopupMenu();
		pDeleteMenu->CreatePopupMenu();

		//pRMenu->SetMenuDrawMode(TRUE);
		pMainMenu->InsertMenu(2, MF_BYPOSITION | MF_POPUP, (UINT)pEditMenu->m_hMenu, "메모리 수정");
		pMainMenu->InsertMenu(3, MF_BYPOSITION | MF_POPUP, (UINT)pDeleteMenu->m_hMenu, "메모리 삭제");

		if(pRs.GetRecordCount() > 0)
		{
			pNotSendMenu = new CMenu;
			pNotSendMenu->CreatePopupMenu();
			pMainMenu->InsertMenu(4, MF_BYPOSITION | MF_POPUP, (UINT)pNotSendMenu->m_hMenu, "단순출력(미전송)");
		}

		pMainMenu->AppendMenu(MF_BYCOMMAND | MF_SEPARATOR, 0, "");

		for(int i = 0; i < pRs.GetRecordCount(); i++)
		{
			pRs.GetFieldValue("sTitle", strTitle);
			pRs.GetFieldValue("sMsg", strMsg);

			m_saHotMsg.Add(strMsg);
			m_saHotMsgTitle.Add(strTitle);

			UINT nID = ID_MENU_MSG + i;
			pMainMenu->AppendMenu(MF_BYCOMMAND, nID, strTitle);
			pEditMenu->AppendMenu(MF_BYCOMMAND, nID + 100, strTitle);
			pDeleteMenu->AppendMenu(MF_BYCOMMAND, nID + 200, strTitle);
			pNotSendMenu->AppendMenu(MF_BYCOMMAND, nID + 300, strTitle);

			pRs.MoveNext();
		}
	}

	pMainMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
}

void CNewMsgDlg::OnMenuHotMsg(UINT nID)
{
	if(nID == ID_MENU_MSG_ADD)
	{
		CREATE_MODALESS(CAddHotMsgDlg, this);
		pDlg->m_pMyDb = m_pMainDb;
		SHOW_MODALESS(CAddHotMsgDlg, this);
	}
	else if(nID == ID_MENU_MSG_BUSY)
	{
		SendMsg("통화중입니다.\r\n잠시만 기다려주세요");
	}
	else if(nID >= ID_MENU_MSG && nID < ID_MENU_MSG + 100)
	{
		long nOffset = nID - ID_MENU_MSG;
		if(nOffset  < m_saHotMsg.GetCount())
		{
			SendMsg(m_saHotMsg.GetAt(nOffset));
		}
	}
	else if(nID >= ID_MENU_MSG + 100 && nID < ID_MENU_MSG + 200)
	{
		long nOffset = nID - ID_MENU_MSG - 100;
		if(nOffset < m_saHotMsg.GetCount())
		{
			CREATE_MODALESS(CAddHotMsgDlg, this);
			pDlg->m_pMyDb = m_pMainDb;
			pDlg->m_strTitle = m_saHotMsgTitle.GetAt(nOffset);
			pDlg->m_strMsg = m_saHotMsg.GetAt(nOffset);
			SHOW_MODALESS(CAddHotMsgDlg, this);
		}
	}
	else if(nID >= ID_MENU_MSG + 200 && nID < ID_MENU_MSG + 300)
	{
		long nOffset = nID - ID_MENU_MSG - 200;
		if(nOffset < m_saHotMsg.GetCount())
		{
			CString strTitle = m_saHotMsgTitle.GetAt(nOffset);
			if(IDYES == MessageBox(strTitle + " 을 삭제 하시겠습니까?", "확인", MB_ICONQUESTION | MB_YESNO))
			{
				CMkCommand pCmd(m_pMainDb, "delete_hot_msg");
				pCmd.AddParameter(m_ci.m_nCompanyCode);
				pCmd.AddParameter(m_ui.nWNo);
				pCmd.AddParameter(MESSENGER_HOT_MSG);
				pCmd.AddParameter(strTitle);
				if(pCmd.Execute())
				{
					MessageBox("삭제되었습니다.", "확인", MB_ICONINFORMATION);
				}
			}
		}
	}
	else if(nID >= ID_MENU_MSG + 300 && nID < ID_MENU_MSG + 400)
	{
		long nOffset = nID - ID_MENU_MSG - 300;
		if(nOffset  < m_saHotMsg.GetCount())
		{
			m_edtSend.SetWindowText(m_saHotMsg.GetAt(nOffset));
		}
	}
}


void CNewMsgDlg::OnClose()
{
	if(m_chkNoClose.GetCheck())
	{
		ShowWindow(SW_HIDE);
	}
	else
	{
		MSG_DLG_INFO *pmdi = new MSG_DLG_INFO;
		if(m_nSendType > 0)
		{
			pmdi->nCompanyCode = 0;
			pmdi->nMNo = m_nSendType;
			pmdi->nType = 0;
		}
		else
		{
			pmdi->nCompanyCode = atol(m_strCompanyCode);
			pmdi->nMNo = atol(m_strMNo);
			pmdi->nType = atol(m_strIntercall);
		}

		m_pParentWnd->PostMessage(WM_CLOSE_MSG_DLG, (WPARAM)pmdi, 0);
		CDialog::OnCancel();
	}
}

void CNewMsgDlg::OnOK()
{
	OnClose();
}

void CNewMsgDlg::OnCancel()
{
	OnClose();
}

void CNewMsgDlg::MoveClient()
{
	if(m_edtMsgRich.GetSafeHwnd())
	{
		CRect rc, rcClient, rcMsgEdit, rcSendEdit, rcInfo, rcMenu;

		GetClientRect(rcClient);
		rcClient.DeflateRect(1, 1, 1, 1);

		m_edtMsgRich.GetWindowRect(rcMsgEdit);
		m_edtSend.GetWindowRect(rcSendEdit);
		m_stcInfo.GetWindowRect(rcInfo);
		m_btnMenu.GetWindowRect(rcMenu);

		ScreenToClient(rcMsgEdit);
		ScreenToClient(rcSendEdit);
		ScreenToClient(rcInfo);
		ScreenToClient(rcMenu);

		int nInfoHeight = rcInfo.Height();
		int nMenuHeight = rcMenu.Height();

		rcSendEdit.bottom = rcClient.bottom - nInfoHeight - 1;
		rcSendEdit.top = rcClient.bottom - 60 - nInfoHeight;
		rcSendEdit.right = rcClient.right;
		rcSendEdit.left = rcClient.left;

		rcMsgEdit.left = rcClient.left;
		rcMsgEdit.right = rcClient.right;
		rcMsgEdit.bottom = rcSendEdit.top - 5;

		rcInfo.bottom = rcClient.bottom;
		rcInfo.top = rcInfo.bottom  - nInfoHeight;
		rcInfo.left = rcClient.left;
		rcInfo.right = rcClient.right - rcMenu.Width() - 1;

		rcMenu.bottom = rcClient.bottom;
		rcMenu.top = rcMenu.bottom  - nMenuHeight;
		rcMenu.left = rcInfo.right + 1;
		rcMenu.right = rcClient.right;

		m_edtMsgRich.MoveWindow(rcMsgEdit);
		m_edtSend.MoveWindow(rcSendEdit);
		m_stcInfo.MoveWindow(rcInfo);
		m_btnMenu.MoveWindow(rcMenu);

		m_edtMsgRich.GetClientRect(&rc);
		rc.DeflateRect(2, 3);
		m_edtMsgRich.SetRect(rc);

		m_edtSend.GetClientRect(&rc);
		rc.DeflateRect(2, 3);
		m_edtSend.SetRect(rc);

		InvalidateRect(rcInfo);
	}	    
}

void CNewMsgDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);
	MoveClient();
}

void CNewMsgDlg::OnDestroy()
{
	CDialog::OnDestroy();
}

void CNewMsgDlg::OnBnClickedShowJustPopupCheck()
{	
	AfxGetApp()->WriteProfileInt("Messenger", "ShowJustPopup", m_chkShowJustPopup.GetCheck());
	if(m_chkShowJustPopup.GetCheck())
	{
		MessageBox("상대방으로 부터 메시지를 수신하면, 대화창이 즉시 팝업됩니다.", 
					"대화창 즉시 팝업 설정", MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("상대방으로 부터 메시지를 수신하면, 오른쪽 하단에 노란색 알림창이 팝업되고\n"\
					"알림창 클릭시에 대화창이 팝업됩니다.", 
					"알림창 클릭시 대화창 팝업 설정", MB_ICONINFORMATION);
	}
}

void CNewMsgDlg::MsgTyping()
{
	PrintInfo(" 상대방이 메시지를 입력하고 있습니다.");
	SetTimer(0, 2000, NULL);
}

void CNewMsgDlg::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(0);
	PrintInfo(m_strLastRecvTime);
	CMyDialog::OnTimer(nIDEvent);
}

void CNewMsgDlg::OnEnChangeSendEdit()
{
	if(GetTickCount() - m_dwLastTyping > 2000)
	{
		SetEvent(m_hTypeingHandle);
		m_dwLastTyping = GetTickCount();
	}
}

UINT CNewMsgDlg::TypingProc(LPVOID lParam)
{
	HANDLE hWaitObject[2];
	hWaitObject[0] = m_hTypeingHandle;
	hWaitObject[1] = m_hExitHandle;

	while(1)
	{
		DWORD dwWaitResult = WaitForMultipleObjects(2, hWaitObject, FALSE, 5000);

		if(dwWaitResult == WAIT_OBJECT_0)
		{
			char data[1024];

			STRCPY(data, (LPSTR)(LPCTSTR)m_strCompanyCode, 
				(LPSTR)(LPCTSTR)m_strMNo, 
				"$$%MSG_TYPING", "0", "0", VL_END);

			if(m_pSocket->IsConnected())
				m_pSocket->SendData(PT_REQUEST, PST_SEND_MSG3, data);
		}
		else if(dwWaitResult == WAIT_OBJECT_0 + 1)
		{
			break;
		}
	}

	SetEvent(m_hThreadDiedHandle);
	return 0;
}

void CNewMsgDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rc;
	GetClientRect(rc);
	dc.FillSolidRect(rc, RGB(220, 235, 255));

	m_stcInfo.GetWindowRect(rc);
	ScreenToClient(rc);
	dc.SelectObject(m_FontManager.GetFont("맑은 고딕", 14));
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(120, 120, 120));
	dc.DrawText(m_strInfo, rc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}

void CNewMsgDlg::SetLastRecvTime(CString strTime)
{
	m_strLastRecvTime = strTime;
	PrintInfo(m_strLastRecvTime);
}

void CNewMsgDlg::OnBnClickedNoCloseCheck()
{
	AfxGetApp()->WriteProfileInt("Messenger", "NoClose", m_chkNoClose.GetCheck());
	if(m_chkNoClose.GetCheck())
	{
		MessageBox("대화창 닫은 후, 다시 팝업시에 대화 내용이 남아 있습니다.\n"
					"프로그램 종료시에 사라지며, 히스토리에서 확인이 가능합니다.", 
			"창 닫을 시 대화내용 저장함", MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("대화창 닫은 후, 다시 팝업시에 대화 내용이 초기화 되어 있습니다.\n"\
					"내용은 히스토리에서 확인 가능합니다.", 
			"창 닫을 시 대화내용 저장안함", MB_ICONINFORMATION);
	}
}
void CNewMsgDlg::OnBnClickedMenuBtn()
{
	OnContextMenu();
}

void CNewMsgDlg::PrintInfo(CString strMsg)
{
	CRect rc;
	m_strInfo = strMsg;
	m_stcInfo.GetWindowRect(rc);
	ScreenToClient(rc);
	InvalidateRect(rc);
}