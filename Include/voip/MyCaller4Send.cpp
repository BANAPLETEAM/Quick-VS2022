#include "StdAfx.h"
//#include "Sound.h"
#include "MyCaller4Send.h"
//#include "SoundDlg.h"



CMyCaller4Send::CMyCaller4Send(CWnd* pDlg)
{
	m_pDlg = pDlg;
}

CMyCaller4Send::~CMyCaller4Send(void)
{
	Close();
}

void CMyCaller4Send::onConnected()
{
//	m_pDlg->SetWindowText("Connected!!");
	m_pDlg->SendMessage(UM_CONNECTED,(WPARAM)MT_USAGE_SEND,(LPARAM)MT_USAGE_SEND);
	SendData(PST_LOGIN_LIST,VT_TEXT,"");
	
}
void CMyCaller4Send::onDisConnected()
{
	m_pDlg->SendMessage(UM_DISCONNECTED,(WPARAM)MT_USAGE_SEND,(LPARAM)MT_USAGE_SEND);
//	m_pDlg->SetWindowText("DisConnected!!");
}
void CMyCaller4Send::onError(int nCode,CString sError)
{

}
void CMyCaller4Send::onTextData(LPVTMSG  p)
{
	if( PST_LOGIN_LIST == p->m_ucCmd )
	{
		m_pDlg->SendMessage(UM_CONNLIST, (WPARAM)p->m_pData,(LPARAM)p->m_pData );
	}
	else if(PST_CONNECT_EVENT == p->m_ucCmd)
	{
		m_pDlg->SendMessage(UM_ADD_CONNUSER, (WPARAM)p->m_pData,(LPARAM)p->m_pData );

//		m_pDlg->AddConnUser((char*)p->m_pData);
	}
	else if(PST_DISCONNECT_EVENT == p->m_ucCmd)
	{
//		m_pDlg->RemoveConnUser((char*)p->m_pData);
		m_pDlg->SendMessage(UM_REM_CONNUSER, (WPARAM)p->m_pData,(LPARAM)p->m_pData );
	}

}

void CMyCaller4Send::onVoiceData(LPVTMSG p)
{

}