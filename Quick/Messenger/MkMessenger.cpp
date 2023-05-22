// MkMessenger.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MkMessenger.h"
#include "mmsystem.h"
#include "NewMsgDlg.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <Mmsystem.h>
#include "NewConnListDlg.h"
#include "StartbarNotifier.h"
#include "NotifierContainer.h"
#include "LogiUtil.h"

#pragma comment(lib, "winmm.lib")
#define MAX_BUFFER_SEND	30000

char *MSG_CONNECTED	=	"메신저 온라인";
char *MSG_CONNECTED_SEAT_AWAY	=	"메신저 자리비움";
char *MSG_CONTROL_OK	=	"메신저 제어권획득";
char *MSG_DISCONNECTED =	"메신저 연결끊김";
char *MSG_INIT_FAILED	=	"네트워크 초기화 실패";
char *MSG_CONNECT_FAILED = "메신저 연결실패";
char *CONTROL_REQUEST_FAIL =	"제어권 요청실패";
char *CONTROL_LOSE		=	"제어권 상실됨";
char *CONTROL_GET_FAIL	=	"제어권 획득실패";


// CMkMessenger
IMPLEMENT_DYNAMIC(CMkMessenger, CWnd)
CMkMessenger::CMkMessenger(CWnd *pParent)
{
	Create(NULL, "", WS_CHILD, CRect(0,0,0,0), GetDesktopWindow(), 0);

	m_pNewConnListDlg = NULL;
	m_pmi = NULL;
	m_bRecvIntercall = FALSE;
	m_bRecvAllocMsg = FALSE;
	m_bRecvRiderPosMsg = FALSE;
	m_pwndAllocPost = NULL;
	m_pdwInputTime = NULL;
	m_bSeatAwayState = FALSE;
	m_bConnectState = FALSE;

	m_pMsgClient = new CMkDatabase(g_bana_log);
	BYTE nXorKey = (m_pMsgClient->GetXorKey() + 3) % 128;
	BYTE des_key_new[] = {29,44,2,83,32,98,10,8};
	BYTE nXoredKey[8];

	for(int i = 0; i < 8; i++)
		nXoredKey[i] = des_key_new[i] ^ ((nXorKey + i) % 128);
	m_pMsgClient->SetServerKey(nXoredKey);
}

CMkMessenger::~CMkMessenger()
{
	MSG_DLG_MAP::iterator it;
	for(it = m_MsgDlgMap.begin(); it != m_MsgDlgMap.end(); it++)
		delete it->second.pDlg;

	if(m_pNewConnListDlg != NULL)
	{
		delete m_pNewConnListDlg;
		m_pNewConnListDlg = NULL;
	}

	if(m_pMsgClient != NULL)
	{
		delete m_pMsgClient;
		m_pMsgClient = NULL;
	}

	if(m_pmi != NULL)
	{
		delete m_pmi;
		m_pmi=  NULL;
	}
}


BEGIN_MESSAGE_MAP(CMkMessenger, CWnd)
	ON_MESSAGE(WM_ASYNC_EVENT, OnAsyncEvent)
	//ON_MESSAGE(WM_CLOSE_MSG_CONN_LIST_DLG, OnCloseMsgConnListDlg)
	ON_MESSAGE(WM_CLOSE_MSG_DLG, OnCloseMsgDlg)
	ON_WM_TIMER()
END_MESSAGE_MAP()


BOOL CMkMessenger::CheckString(char *szMsg, char *szFind)
{
	return (strncmp(szMsg, szFind, strlen(szFind)) == 0);
}

MSG_DLG_MAP::iterator CMkMessenger::FindDlgMap(int nCompany, int nMNo, BOOL bIntercall, int nSendType)
{
	return (nSendType > 0) ? 
			m_MsgDlgMap.find(MAKE_MSG_KEY(0, nSendType, 0)) : 
			m_MsgDlgMap.find(MAKE_MSG_KEY(nCompany, nMNo, bIntercall));
}

MSG_DLG_MAP::iterator CMkMessenger::FindDlgMap(char *szCompany, char *szMNo, char *szIntercall, int nSendType)
{
	return FindDlgMap(atol(szCompany), atol(szMNo), atol(szIntercall), nSendType);
}


// CMkMessenger 메시지 처리기입니다.


LONG CMkMessenger::OnAsyncEvent(SOCKET wSocket, LPARAM lParam)
{

	if(m_pMsgClient != NULL)
	{
		if(lParam == 0xFFFF)
		{
			MySetState(MSG_CONNECTED);
			return 0;
		}

		if(WSAGETSELECTERROR(lParam))
		{
			m_pMsgClient->GetSocket()->Close();
			MySetState(MSG_DISCONNECTED);
			return 0;
		}

		switch(WSAGETSELECTEVENT(lParam))
		{
		case FD_CLOSE:
			m_pMsgClient->GetSocket()->Close();
			MySetState(MSG_DISCONNECTED);
			break;

		case FD_READ:
			{					
				long nRealRecvLen;
				m_pMsgClient->GetSocket()->AsyncSelect(FD_CLOSE);
				QPACKET *p = (QPACKET*)m_pMsgClient->GetSocket()->ReadStream2(nRealRecvLen);

				if(p != NULL) {
					long nSize = 0;

					while(nSize < nRealRecvLen)
					{
						if(nSize == 0)
						{
							OnMsgDataRead(p);
							nSize = p->nPacketSize;
						}
						else 
						{
							if(nRealRecvLen - nSize <= 8)
								break;

							char *pBase = (char*)p;
							QPACKET *p2 = (QPACKET*)&pBase[nSize];
							p2->nType = ntohs(p2->nType);
							p2->nSubType = ntohs(p2->nSubType);
							p2->nPacketSize = ntohs(p2->nPacketSize);

							if(p2->nPacketSize == 0)
							{
								char *p3 = (char*)p2;
								for(int i = 0; i < 50; i++)
									g_bana_log->Print("%c", p3[i]);
								break;
							}

							if(nRealRecvLen - nSize >= p2->nPacketSize)
								OnMsgDataRead(p2);

							nSize += p2->nPacketSize;
						}
					}

					free(p);
				}
				m_pMsgClient->GetSocket()->AsyncSelect(FD_CLOSE | FD_READ);
			}	
			break;
		}
	}

	return 0;
}

BOOL CMkMessenger::Connect()
{
	if(m_pmi == NULL)
		return FALSE;

	m_pMsgClient->SetParentWnd(this->GetSafeHwnd());
	m_pMsgClient->AsyncSelect(FD_READ | FD_CLOSE);
	m_pMsgClient->ClientType(TRUE);
	m_pMsgClient->SetErrorMsgType(EMT_NO_SHOW);

	MSG_LOGIN_INFO info;
	ZeroMemory(&info, sizeof(MSG_LOGIN_INFO));
	info.nCompany = m_pmi->nCompanyCode;
	info.nWNo = m_pmi->nUserCode;
	info.nShareCode1 = m_pmi->nShareCode1;
	info.nShareCode2 = m_pmi->nShareCode2;
	info.nShareCode3 = m_pmi->nShareCode3;
	info.nShareCode4 = m_pmi->nShareCode4;
	info.nShareCode5 = m_pmi->nShareCode5;
	info.nShareCode6 = m_pmi->nShareCode6;
	info.nShareCode7 = m_pmi->nShareCode7;
	info.nShareCode8 = m_pmi->nShareCode8;
	info.nShareCode9 = m_pmi->nShareCode9;
	info.nShareCode10 = m_pmi->nShareCode10;
	info.nMsgGroupCode = m_pmi->nMsgGroupCode;
	strcpy(info.szCompanyName, m_pmi->strCompanyName);
	strcpy(info.szBranchName, m_pmi->strBranchName);
	strcpy(info.szUserName, m_pmi->strUserName);
	info.bIdle = m_pmi->bIdle;
	info.bManager = m_pmi->bManager;
	info.nDisplayType = m_pmi->nDisplayType;
	info.etc2 = m_bRecvIntercall;
	info.etc3 = m_bRecvAllocMsg;
	info.etc4 = m_bRecvRiderPosMsg;
	m_pMsgClient->SetLoginInfo(&info);

	SetTimer(0, 2000, NULL);

	return m_pMsgClient->Open(m_pmi->strMsgServerAddr, m_pmi->nMsgServerPort, FALSE);
}

void CMkMessenger::Close()
{
	m_pMsgClient->Close();
}

void CMkMessenger::OnMsgDataRead(QPACKET *p)
{
   	if(p->nType == PT_OK)
	{
		if(p->nSubType == PST_SEND_MSG) {
			CString strTitle;
			char identity[12], cname[30], msg[512];
			if(!STRTOK(p->data, 0, identity, cname, msg, VL_END)) return;
			strTitle.Format("상담 메시지(%s):", strlen(cname) > 0 ? cname : "알수없음");

			NOTIFIER_ITEM *pNItem = new NOTIFIER_ITEM;
			pNItem->type = NFI_RECV_MESSAGE;
			pNItem->strIdentity = identity;
			pNItem->strCName = strlen(cname) > 0 ? cname : "알수없음";
			pNItem->strMsg = msg;

			CStartbarNotifier *pNotifier = new CStartbarNotifier;
			pNotifier->Create(m_pnfc);
			pNotifier->DefaultSetting();
			pNotifier->Initailze(strTitle, msg, 0, 300000, 0, 2);
			pNotifier->SetItemData((void*)pNItem);
			m_pnfc->AddNotifier(pNotifier);
			MyPlaySound();
		}
		else if(p->nSubType == PST_SEND_MSG3)
		{
			int nPos = 0, nSendType = 0;
			CString strTitle;
			char szCompanyCode[10], szMNo[10], szMsg[9001];
			char szCompanyName[50], szName[50], szIntercall[20], szSendType[10];

			if((nPos = STRTOK(p->data, nPos, szCompanyCode, szMNo, szIntercall, szCompanyName, szName, szMsg, VL_END))) 
			{
				if(STRTOK(p->data, nPos, szSendType, VL_END))
					nSendType = atol(szSendType);

				BOOL bHandled = TRUE;

				if(CheckString(szMsg, "$$%MSG_TYPING"))
				{
					MSG_DLG_MAP::iterator it = FindDlgMap(szCompanyCode, szMNo, "0", 0);

					if(it != m_MsgDlgMap.end())
						(*it).second.pDlg->MsgTyping();
				} 
				else if(CheckString(szMsg, "$$%SEAT_STATUS"))
				{
					BOOL bSeatAway = TRUE;
					if(CheckString(szMsg, "$$%SEAT_STATUS_ON"))
						bSeatAway = FALSE;

					CString *pstrMsg = new CString;
					pstrMsg->Format("%s %s", szName, bSeatAway ? "자리비움" : "온라인");
					MySetStateNew(pstrMsg);

					if(m_pNewConnListDlg)
						m_pNewConnListDlg->UpdateUserStatus(atol(szCompanyCode), atol(szMNo), 0, bSeatAway);
				}
				else if(CheckString(szMsg, "$$%"))
				{
					bHandled = OnRecvUserProtocol(atol(szCompanyCode), atol(szMNo), atol(szIntercall), 
						szCompanyName, szName, szMsg);
				}
				else
				{
					bHandled = FALSE;
				}


				if(!bHandled)
				{
					MSG_DLG_MAP::iterator it = FindDlgMap(szCompanyCode, szMNo, szIntercall, nSendType);
					int nShowJustPopup = AfxGetApp()->GetProfileInt("Messenger", "ShowJustPopup", 0);

					if(it != m_MsgDlgMap.end())
					{
						ShowMsgDlg(AfxGetMainWnd(), szMsg, szCompanyCode, szMNo, szIntercall, szCompanyName, szName, FALSE, nSendType);
					}
					else if(nShowJustPopup)
					{
						ShowMsgDlg(AfxGetMainWnd(), szMsg, szCompanyCode, szMNo, szIntercall, szCompanyName, szName, FALSE, nSendType);
						MyPlaySound();
					}
					else
					{
						NOTIFIER_ITEM *pNItem = new NOTIFIER_ITEM;
						pNItem->type = NFI_RECV_MESSAGE2;
						pNItem->strCName.Format("%s/%s", szCompanyName, szName);
						pNItem->strMsg = szMsg;
						pNItem->strCompanyName = szCompanyName;
						pNItem->strName = szName;
						pNItem->nCompanyCode = atol(szCompanyCode);
						pNItem->nMNo = atol(szMNo);
						pNItem->nClientType = atol(szIntercall);
						pNItem->nSendType = nSendType;

						strTitle.Format("메시지(%s):", pNItem->strCName.GetLength() > 0 ? 
							pNItem->strCName : "알수없음");

						CStartbarNotifier *pNotifier = new CStartbarNotifier;
						pNotifier->Create(m_pnfc);
						pNotifier->DefaultSetting();
						pNotifier->Initailze(strTitle, szMsg, 0, 300000, 0, 2);
						pNotifier->SetItemData((void*)pNItem);
						m_pnfc->AddNotifier(pNotifier);
						MyPlaySound();
					}
				}
			}
		}
		else if(p->nSubType == PST_RESERVE_TRG) {
			CString strTitle, strMsg;
			char mycompany[10], mymno[10];
			char cno[12], cname[30], szStart[30], szDest[30];
			if(!STRTOK(p->data, 0, mycompany, mymno, cno, cname, szStart, szDest, VL_END)) return;

			strTitle.Format("인터넷 접수 (%s)", strlen(cname) > 0 ? cname : "알수없음");
			strMsg.Format("%s->%s(%s) 접수확인바람", szStart, szDest, cno);

			NOTIFIER_ITEM *pNItem = new NOTIFIER_ITEM;
			pNItem->type = NFI_RESERVE;
			pNItem->strIdentity = cno;
			pNItem->strCName = strlen(cname) > 0 ? cname : "알수없음";

			CStartbarNotifier *pNotifier = new CStartbarNotifier;
			pNotifier->Create(m_pnfc);
			pNotifier->DefaultSetting();
			pNotifier->Initailze(strTitle, strMsg, 0, 300000, 0, 2);
			pNotifier->SetItemData((void*)pNItem);
			m_pnfc->AddNotifier(pNotifier);
			PlaySound(MAKEINTRESOURCE(IDR_NOTIFY_WAV), AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		}
		else if(p->nSubType == PST_DISCONNECT)	//채팅 대상이 연결되어 있지 않은 경우
		{
			int nPos = 0, nSendType = 0;
			CString strTitle;
			char szCompanyCode[10], szMNo[10], szMsg[9001], szIntercall[10], szSendType[10];

			if(nPos = STRTOK(p->data, 0, szCompanyCode, szMNo, szMsg, szIntercall, VL_END)) 
			{
				if(!CheckString(szMsg, "$$%"))
				{
					if(STRTOK(p->data, nPos, szSendType, VL_END))
						nSendType = atol(szSendType);

					MSG_DLG_MAP::iterator it = FindDlgMap(szCompanyCode, szMNo, szIntercall, nSendType);
					if(it != m_MsgDlgMap.end())
					{
						CString strMsg;
						if(nSendType > 0)
							strMsg = "- 메시지 전달 실패:\r\n전체메시지를 받을 로그인된 상담원이 존재하지 않습니다.";
						else
							strMsg.Format("- 메시지 전달 실패:\r\n %s", szMsg);
						ShowMsgDlg(AfxGetMainWnd(), strMsg, szCompanyCode, szMNo, szIntercall, "", "", 0, nSendType);
					}
				}
			}
		}
		else if(p->nSubType == PST_LOSE_CONTROL) //동일한 아이디로 추가 접속이 발생했을 때
		{
			CString strLog;
			strLog.Format("m_pMsgClient = %X, m_pmi = %X\r\n", m_pMsgClient, m_pmi);
			//LU->AddSpecialLog(strLog);

			if(m_pMsgClient)
			{
				m_pMsgClient->Close();
				MessageBox("다른 컴퓨터에서 동일한 아이디로 메신저 서버에 접속하여,"\
						" 메신저 연결이 끊어졌습니다.", CONTROL_LOSE, MB_ICONINFORMATION);
				m_pMsgClient->Open(m_pmi->strMsgServerAddr, m_pmi->nMsgServerPort, FALSE);
				MySetState(MSG_DISCONNECTED);
			}
		}
		else if(p->nSubType == PST_SEND_ALLOC)
		{
			if(AfxGetApp()->GetProfileInt("RcpPage", "RecvAllocMsg", 0) == 1)
			{
				NOTIFIER_ITEM *pNItem = new NOTIFIER_ITEM;
				pNItem->type = NFI_ALLOC_MESSAGE;
				pNItem->strCName = "";
				pNItem->strMsg = p->data;

				PlaySound(MAKEINTRESOURCE(IDR_ALLOCATE_WAV), 
					AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);

				CStartbarNotifier *pNotifier = new CStartbarNotifier;
				pNotifier->Create(m_pnfc);
				pNotifier->SetSkin(IDB_SKIN_ALLOC_NOTICE);
				pNotifier->SetTextFont("돋움", 110,TN_TEXT_NORMAL,TN_TEXT_UNDERLINE);
				pNotifier->SetTitleTextColor(RGB(120, 170, 0));
				pNotifier->SetTextColor(RGB(120, 170, 0),RGB(0,0,200));
				pNotifier->SetTextRect(CRect(94,6, 295, 20));
				pNotifier->Initailze("", p->data, 0, 10000, 0, 2);
				pNotifier->SetItemData((void*)pNItem);
				m_pnfc->AddNotifier(pNotifier);
				if(m_pwndAllocPost)
					m_pwndAllocPost->PostMessage(WM_USER + 102, -1, 0);
			}			
		}

		//g_bana_log->Print(::GetStringFromLong(p->nSubType) + " subtype\r\n");
		OnRecvOKProtocol(p);
	}
	else if(p->nType == PT_ERROR)
	{
		if(p->nSubType == PST_SEND_MSG_RCP)
			MessageBox("해당 고객의 연결이 끊어진 상태입니다.", "전송 실패", MB_ICONEXCLAMATION);
	}
}


void CMkMessenger::ShowMsgConnList()
{
	if(m_pNewConnListDlg == NULL)
	{
		m_pNewConnListDlg = new CNewConnListDlg(this);
		if(m_pNewConnListDlg->GetMsgDatabase())
		{
			m_pNewConnListDlg->Create(IDD_NEW_CONN_LIST_DLG, this);
			m_pNewConnListDlg->ShowWindow(SW_SHOW);	
			m_pNewConnListDlg->SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);	
		}
		else
		{
			delete m_pNewConnListDlg;
			m_pNewConnListDlg = NULL;
		}
	}
	else
	{
		WINDOWPLACEMENT wndpl;
		wndpl.length = sizeof(WINDOWPLACEMENT);
		m_pNewConnListDlg->GetWindowPlacement(&wndpl);

		if(wndpl.showCmd == SW_SHOWMINIMIZED)
			m_pNewConnListDlg->ShowWindow(SW_RESTORE);
 
		m_pNewConnListDlg->ShowWindow(SW_SHOW);
		m_pNewConnListDlg->SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);	
		m_pNewConnListDlg->SetForegroundWindow();
		m_pNewConnListDlg->SetFocus();
	}
}

/*
LONG CMkMessenger::OnCloseMsgConnListDlg(WPARAM wParam, LPARAM lParam)
{
	delete m_pNewConnListDlg;
	m_pNewConnListDlg = NULL;
	return 0;
}
*/

CNewMsgDlg* CMkMessenger::ShowMsgDlg(CWnd *pParent, 
					CString strMsg, 
					CString strCompany, 
					CString strMNo, 
					CString strIntercall,
					CString strCompanyName,
					CString strName,
					BOOL bHide,
					int nSendType,
					BOOL bNoFocus,
					BOOL bHideWithMsg)
{	
	MSG_DLG_MAP::iterator it = FindDlgMap(atol(strCompany), atol(strMNo), atol(strIntercall), nSendType);
	if(it != m_MsgDlgMap.end())
	{
		//if((*it).second.pDlg == NULL)
		//	return NULL;

		if(bHide)
			return (*it).second.pDlg;

		WINDOWPLACEMENT wndpl;
		wndpl.length = sizeof(WINDOWPLACEMENT);
		(*it).second.pDlg->GetWindowPlacement(&wndpl);

		if(wndpl.showCmd == SW_SHOWMINIMIZED && !bHideWithMsg)
		{
			(*it).second.pDlg->ShowWindow(SW_RESTORE);
			(*it).second.pDlg->FlashWindow(TRUE);
			PlaySound(MAKEINTRESOURCE(IDR_NOTIFY_WAV), AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		}


		if(strMsg.GetLength() > 0) {
			CString strName2;
			COleDateTime dt = COleDateTime::GetCurrentTime();
			COLORREF crColor = RGB(84, 84, 84);
			strName2.Format("%s/%s 님의 말:\r\n", 
						strCompanyName, 
						strName);

			(*it).second.pDlg->m_edtMsgRich.AddName(strName2, crColor);
			crColor = RGB(128, 0, 128);
			CString strMsg2 = strMsg + "\r\n";
			(*it).second.pDlg->m_edtMsgRich.AddText(strMsg2, crColor);	
			(*it).second.pDlg->SetLastRecvTime(CString(" 마지막 메시지 받은시각:  ") + dt.Format("%H시%M분%S초"));
		}

		if(!bHideWithMsg)
		{
			(*it).second.pDlg->ShowWindow(SW_SHOWNA);
			(*it).second.pDlg->SetWindowPos(&CWnd::wndTopMost, 0,0,0,0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
		}

		return (*it).second.pDlg;
	}
	else
	{
		CNewMsgDlg *pMsgDlg;
		pMsgDlg = new CNewMsgDlg(this);
		pMsgDlg->SetSocket(m_pMsgClient->GetSocket());
		pMsgDlg->m_strMyName = m_ui.strName;
		pMsgDlg->m_strCompanyCode = strCompany;
		pMsgDlg->m_strMNo = strMNo;
		pMsgDlg->m_strIntercall = strIntercall;
		pMsgDlg->m_strCompanyName = strCompanyName;
		pMsgDlg->m_strName = strName;
		pMsgDlg->m_nSendType = nSendType;
		pMsgDlg->m_bNoFocus = bNoFocus;
		pMsgDlg->Create(IDD_NEW_MSG_DLG, pParent);

		if(bHide)
			return pMsgDlg;

		if(strMsg.GetLength() > 0) {
			CString strName2;
			COleDateTime dt = COleDateTime::GetCurrentTime();
			COLORREF crColor = RGB(130, 130, 130);
			strName2.Format("%s/%s 님의 말:\r\n", 
						strCompanyName, 
						strName);

			pMsgDlg->m_edtMsgRich.AddName(strName2, crColor);
			crColor = RGB(128, 0, 128);
			CString strMsg2 = strMsg + "\r\n";
			pMsgDlg->m_edtMsgRich.AddText(strMsg2, crColor);	
			pMsgDlg->SetLastRecvTime(CString(" 마지막 메시지 받은시각:  ") + dt.Format("%H시%M분%S초"));
		}

		MSG_DLG_INFO mdi;
		mdi.nCompanyCode = atol(strCompany);
		mdi.nMNo = atol(strMNo);
		mdi.nType = atol(strIntercall);
		mdi.nSendType = nSendType;

		mdi.pDlg = pMsgDlg;

		if(nSendType > 0)
			m_MsgDlgMap.insert(MSG_DLG_MAP::value_type(MAKE_MSG_KEY(0, mdi.nSendType, 0), mdi));
		else
			m_MsgDlgMap.insert(MSG_DLG_MAP::value_type(MAKE_MSG_KEY(mdi.nCompanyCode, mdi.nMNo, mdi.nType), mdi));


		if(!bHideWithMsg)
		{
			pMsgDlg->ShowWindow(SW_SHOWNA);
			pMsgDlg->SetWindowPos(&CWnd::wndTopMost, 0,0,0,0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
			pMsgDlg->FlashWindow(TRUE);
		}

		return pMsgDlg;
	}
}


LONG CMkMessenger::OnCloseMsgDlg(WPARAM wParam, LPARAM lParam)
{
	MSG_DLG_INFO *pmdi = (MSG_DLG_INFO*)wParam;
	m_MsgDlgMap.erase(MAKE_MSG_KEY(pmdi->nCompanyCode, pmdi->nMNo, pmdi->nType));
	delete pmdi;
	return 0;
}


BOOL CMkMessenger::OnRecvUserProtocol(long nCompany, long nMNo, BOOL bIntercall, 
								char *szCompanyName, char *szName, char *szMsg)
{
	return TRUE;
}

BOOL CMkMessenger::OnRecvOKProtocol(QPACKET *p)
{
	return TRUE;
}

void CMkMessenger::MyPlaySound(LPCSTR pszSound)
{
	if(strlen(pszSound) == 0)
		PlaySound(MAKEINTRESOURCE(IDR_NOTIFY_WAV), AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
	else
		PlaySound(pszSound, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
}

void CMkMessenger::OnTimer(UINT_PTR nIDEvent)
{
	if(m_pdwInputTime && *m_pdwInputTime > 0)
	{
		DWORD dwTick = (GetTickCount() - (*m_pdwInputTime)) / 1000;
		BOOL bCurSeatAway = dwTick > 60;

		if(m_bSeatAwayState != bCurSeatAway) 
		{
			//g_bana_log->Print("메신저 %s\n", bCurSeatAway ? "자리비움" : "자리 안비움");
			m_pMsgClient->SetSeatAway(bCurSeatAway);
			m_bSeatAwayState = bCurSeatAway;
		
			if(m_bConnectState)
			{
				CString strSeatStatus;
				strSeatStatus = CString("$$%SEAT_STATUS_") + (m_bSeatAwayState ? "OFF" : "ON");
				MySetState((m_bSeatAwayState ? MSG_CONNECTED_SEAT_AWAY : MSG_CONNECTED));		
				SendInnerMsg(TYPE_COMPANY, (LPSTR)(LPCTSTR)strSeatStatus, GetUserInfo()->nCompanyCode);
			}
		}
	}

	CWnd::OnTimer(nIDEvent);
}

BOOL CMkMessenger::SendInnerMsg(int nType, CString strMsg, long nTargetCompany, long nTargetRNo)
{
	if(GetDatabase()->GetSocket()->IsConnected())
	{
		char data[MAX_BUFFER_SEND + 1024];
		char szCompany[20], szRNo[20], szType[20], szIntercall[20];
		BOOL bIntercall = FALSE;

		STRCPY(data, ltoa(nTargetCompany, szCompany, 10), ltoa(nTargetRNo, szRNo, 10), 
			strMsg, ltoa(0, szIntercall, 10),
			ltoa(nType, szType, 10), VL_END);

		return GetDatabase()->GetSocket()->SendData(PT_REQUEST, PST_SEND_MSG3, data);
	}

	return FALSE;
}

#define PST_RIDER_POS_MSG_RECV			371		//기사위치메시지 메신저 받기

void CMkMessenger::SetRecvRiderPosMsg(BOOL bRecv, BOOL bJustSend)
{
	m_bRecvRiderPosMsg = bRecv;
	if(bJustSend)
		GetDatabase()->GetSocket()->SendData(PT_REQUEST, PST_RIDER_POS_MSG_RECV, bRecv ? "1": "0");
}

long CMkMessenger::SetRecvIntercall(BOOL bRecv, BOOL bJustSend) 
{ 
	long nConnCount = -1;

	m_bRecvIntercall = bRecv;
	if(bJustSend)
	{
		CQSocket *pSocket = GetDatabase()->GetSocket();
		pSocket->AsyncSelect(FD_CLOSE);
		pSocket->SetTimeOut(2);
		if(pSocket->SendData(PT_REQUEST, PST_INTERCALL_RECV2, bRecv ? "1": "0"))
		{
			if(!bRecv)
			{
				QPACKET *packet = (QPACKET*)pSocket->ReadStream();
				if(packet)
					nConnCount = atol(packet->data);
			}
		}
		pSocket->AsyncSelect(FD_CLOSE | FD_READ);
		pSocket->SetTimeOut(30);
	}

	return nConnCount;
}

BOOL CMkMessenger::SetRecvAllocMsg(BOOL bRecv, BOOL bJustSend) 
{ 
	m_bRecvAllocMsg = bRecv;
	if(bJustSend)
	{
		CQSocket *pSocket = GetDatabase()->GetSocket();
		pSocket->SetTimeOut(2);
		BOOL bRet = GetDatabase()->GetSocket()->SendData(PT_REQUEST, PST_START_ALLOC, bRecv ? "1": "0");
		pSocket->SetTimeOut(30);
		return bRet;
	}

	return TRUE;
}
