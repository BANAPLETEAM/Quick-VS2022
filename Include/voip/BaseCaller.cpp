#include "StdAfx.h"
#include "BaseCaller.h"
#include "TSocket.h"
#include "voicepacket.h"

CBaseCaller::CBaseCaller(void)
{
//	m_hKillEvent;
//	m_hExitEvent;
//	m_hRecvEvent;

	m_hCloseEvent = CreateEvent(NULL, FALSE, FALSE, "");

	m_pSocket     = new CVTSocket;
	m_bShutDown	  = TRUE;
	m_dwThreadID  = 0;
}

CBaseCaller::~CBaseCaller(void)
{
	Close();	
	if(m_pSocket) delete m_pSocket;
}

void CBaseCaller::WaitForServerSignal(CVTSocket& socket)
{
	int nRet;
	LPVTMSG p = (LPVTMSG)socket.ReadStream(nRet);	
	if(p) free(p);
}

BOOL CBaseCaller::IsConnected() 
{ 
	return m_pSocket->IsConnected(); 
}

BOOL CBaseCaller::Connect(CString sHost,UINT uPort,CString sArg,int nType)
{


	m_strHost = sHost;
	m_uPort	  = uPort;
	m_sArg	  = sArg;
	m_nType	  = nType;

	m_pSocket->Close();
	m_bShutDown	 = TRUE;



	if(0 == m_dwThreadID)
	{
		//소켓 통신용 쓰레드 생성
		HANDLE  threadHandle1 =  ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) staticSocketRead, 
			(LPVOID) this, 0, &m_dwThreadID);
		::CloseHandle(threadHandle1);
	}

	return TRUE;
}

BOOL CBaseCaller::ConnectSocket(CVTSocket& tSocket,CString sHost, UINT uPort,CString sArg,int nType)
{

	tSocket.Close();
	if(!tSocket.Create()) return FALSE;
	tSocket.SetConnTimeOut(5000);
	tSocket.SetTimeOut(5000);

	if(FALSE == tSocket.Connect(sHost, uPort)) return FALSE;
	if(FALSE == tSocket.SendData(PST_LOGIN, nType/*MT_USAGE_SEND*/,sArg) ) return FALSE;
	

//	if(!m_bShutDown && nClientType > 0)		onDisConnected(); 필요 없음 메인 소켓인 경우 Thread에 노출될것이고 그이왼 신경 안써도 됨
	onConnected();
	return TRUE;
}


void CBaseCaller::Close()
{
	m_bShutDown = TRUE;
	::SetEvent(m_hCloseEvent);
	Sleep(1000);

/*
	if(FALSE ==m_bShutDown)
	{		
		::SetEvent(m_hCloseEvent);
//		WaitForSingleObject(m_hExitEvent,INFINITE);
		
	}
*/
	m_pSocket->Close();

}

UINT CBaseCaller::SocketRead(LPVOID lParam)
{

	m_bShutDown = FALSE;
	while(!m_bShutDown)
	{
		DWORD nRet = WaitForSingleObject(m_hCloseEvent,10);
		if(WAIT_OBJECT_0 == nRet)
		{
			break;
		}

		if(FALSE == m_pSocket->IsConnected()) 
		{
			if(FALSE ==  ConnectSocket(*m_pSocket,m_strHost, m_uPort,m_sArg,m_nType) ) 		continue;
		}

		SocketReadImpl();
	}

	return 0;
}

void CBaseCaller::SocketReadImpl()
{
	int nRet=0;
	LPVTMSG p = (LPVTMSG)m_pSocket->ReadStream(nRet);

	if(0 == nRet || WSAETIMEDOUT == nRet || WSAEWOULDBLOCK == nRet)
	{
		TRACE("OK\r\n");
	}
	else 
	{
		m_pSocket->Close();
		onDisConnected();
		return;
	}

	if(p == NULL) return;
			
	if		(PST_ERROR		==  p->m_ucCmd ) onError(p->m_ucCmd,(char*)p->m_pData);
	else
	{
		
		if		(VT_WAVE1M08	==  (p->m_ucMsgType&VT_WAVE1M08)  ) onVoiceData(p);
		else if	(VT_TEXT		==  (p->m_ucMsgType&VT_TEXT)	  ) onTextData(p); 
	}
	//수신 버퍼 초기화
	if(p) free(p);
}

BOOL CBaseCaller::SendData(UINT ucCmd, UINT ucMsgType, const char* data)
{
	return SendData( ucCmd,  ucMsgType,"",  data);
}

BOOL CBaseCaller::SendData(UINT ucCmd, UINT ucMsgType,const char* szTo, const char* data)
{
	return m_pSocket->SendData( ucCmd,  ucMsgType,szTo,  data);
}

BOOL CBaseCaller::SendBinary(UINT ucCmd, UINT ucMsgType, void* data, UINT nLen)
{
	return SendBinary( ucCmd,  ucMsgType,"", data, nLen);
}

BOOL CBaseCaller::SendBinary(UINT ucCmd, UINT ucMsgType,const char* sToID, void* data, UINT nLen)
{
	return m_pSocket->SendBinary( ucCmd,  ucMsgType, sToID, data ,nLen);
}

BOOL GetOptionString(CString sOptionSet,CString sOption,CString& sRetVal)
{
	sOption = "<"+sOption +"=";
	sOption.MakeUpper();

	int nFind1 = sOptionSet.Find(sOption);
	if(nFind1 < 0 ) return FALSE;

	int nFind2 = sOptionSet.Find("/>",nFind1);
	if(nFind2 < 0 ) return FALSE;

	sRetVal = sOptionSet.Mid(nFind1+ sOption.GetLength(), nFind2-(nFind1+ sOption.GetLength() ) );

	sRetVal.Trim();
	return TRUE;
}