#include "stdafx.h"
#include "Call.h"
#include "Md5.h"
#include "TPacket.h"
#include "TSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



#define LICENSE_INFO "Powered By Logisoft(로지 소프트) 서울 강남구 대치동 942-18 세풍빌딩,"\
					 "이소프트 웨어의 모든 권리는 로지소프트에 있습니다."\
					 "무단 배포나 임의 변경사용시 법적 처벌을 받을수 있습니다."
#define DIGESTLENGTH			16
#define CHALLENGESIZE32			32
#define PORT_NUM				4001

//BOOL CCall::m_bShutDown = FALSE;

CCall::CCall(void)
{
//	g_PhoneDlg.Create(NULL);

	m_hKillEvent = CreateEvent(NULL, FALSE, FALSE, NULL); 
	m_hExitEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hRecvEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	
	m_bMakeThread = FALSE;
	m_bUserClosed = FALSE;
	m_pSockSystem = new CTSocketSystem;
	m_pSocket     = new CTSocket;
	m_bShutDown	  = TRUE;
	m_bThreadEnd =	FALSE;

	m_nQueuePause = LINE_UNUSE_MODE;/*0 수신가능, 1 수신거부, 2 인터넷전화아님*/
	m_nMute = UNMUTE_MODE;
	m_nAnswerRecPlay = UNANSWER_RECPLAY_MODE;
	m_nBlindTransfer = UNBLINDTRANSFER_MODE;

	DWORD dwThreadID;
	//소켓 통신용 쓰레드 생성
	HANDLE  threadHandle1 =  ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) staticSocketRead, 
		(LPVOID) this, 0, &dwThreadID);
	::CloseHandle(threadHandle1);
}

CCall::~CCall(void)
{
	Close();

	m_bThreadEnd = TRUE;
	WaitForSingleObject(m_hExitEvent, 2000);

	if(m_pSockSystem) delete m_pSockSystem;
	if(m_pSocket    ) delete m_pSocket;

	CloseHandle(m_hKillEvent);
	CloseHandle(m_hExitEvent);
	CloseHandle(m_hRecvEvent);

}

void CCall::WaitForServerSignal(CTSocket& socket)
{
	int nRet;
	TPACKET *p = (TPACKET*)socket.ReadStream(nRet);	
	if(p) free(p);
}

BOOL CCall::IsConnected() 
{ 
	return m_pSocket->IsConnected(); 
}

BOOL CCall::Connect(CString sHost, CString sKeyPhoneID, const char* szName,int nType)
{
	if(!m_pSockSystem->Initialised()) 
	{
		return FALSE;
	}

	m_nClientType = nType;
	m_strHost = sHost;
	m_sKeyPhoneID = sKeyPhoneID;
	m_strName = szName;
	m_fVer = (float)0.1;

	m_bUserClosed = FALSE;
	m_pSocket->Close();
	m_bShutDown = FALSE;

	return TRUE;
}

void CCall::Close()
{
	if(FALSE == m_bShutDown)
	{
		m_bShutDown = TRUE;
		m_pSocket->Close();
	}
	m_bUserClosed = TRUE;
}

void CCall::onSetCallNumber(char* szPhoneNumber)
{

}

void CCall::onCallChange(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID)
{

}

void CCall::onRouteCallChange(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID,const char* szInfo)
{

}

void CCall::onCallInfoLog(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID,char* szOperator,char* szCustomer,char* szLastOperator)
{

}

void CCall::onMoniter(int nRing,int nAnswer,int nMissingCallCnt ,int nMissingCallPerMin)
{

}

void CCall::onMoniterLog(const char* szLog)
{

}

void CCall::onMoniterUserLog(const char* szLog)
{

}

void CCall::onSocketState(const char* szLog)
{

	return;
}

void CCall::onMoniterAnswerLinesChanged(const char* szKeyPhoneLines)
{

}

void CCall::onMoniterLinesChanged(const char* szAnswerLines,const char* szARSLines,const char* szNonPRILines,const char* szRouteLines)
{

}


void CCall::onConnected()
{

}
void CCall::onDisConnected()
{

}

void CCall::SetQueuePause(int nPause)
{

}

int	CCall::GetQueuePause()
{ 
	return m_nQueuePause;
}

int CCall::GetMuteState()
{
	return m_nMute;
}

int CCall::GetAnswerRecPlayState()
{
	return m_nAnswerRecPlay;
}

int CCall::GetBlindTransferState()
{
	return m_nBlindTransfer;
}

void CCall::PutStatus(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);

	TCHAR line[1024];
	_vsnprintf(line, 1024, format, ap);

	va_end(ap);
	onSocketState(line);
}
/*
BOOL CCall::ConnectSocket(CTSocket& tSocket)
{

	tSocket.Close();
	if(!tSocket.Create()) return -1;
	tSocket.SetConnTimeOut(2000);
	tSocket.SetTimeOut(2000);

	if(tSocket.Connect(m_strHost, PORT_NUM))
	{
		CString sConnStr;
		m_sKeyPhoneID.Replace("@", "");
		m_strName.Replace("@", "");
		sConnStr.Format("%s@%s@0.1@%d@%s",m_sKeyPhoneID,m_strName,m_nClientType,m_sKey);

		if(tSocket.SendData(PT_OK, NULL, (LPSTR)(LPCTSTR)sConnStr))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

void CCall::ReConnect()
{

	m_strHost.Trim();
	if(m_strHost.IsEmpty()) return;
	m_Socket.Close();

	PutStatus("접속 종료됨");

	if(!m_Socket.Create()) 
	{
		PutStatus("소켓 생성 실패");
		return;
	}

	m_Socket.SetConnTimeOut(1000);
	m_Socket.SetTimeOut(1000);

	if(m_Socket.Connect(m_strHost, PORT_NUM))
	{
		CString sConnStr;
		m_sKeyPhoneID.Replace("@", "");
		m_strName.Replace("@", "");
		sConnStr.Format("%s@%s@0.1@%d@%s",m_sKeyPhoneID,m_strName,m_nClientType,m_sKey);

		if(m_Socket.SendData(PT_OK, NULL, (LPSTR)(LPCTSTR)sConnStr))
		{
			//PutStatus("%s 서버에 접속됨", m_strHost);
			PutStatus("서버에 접속됨");
			onConnected();
		}
		else
		{
			PutStatus("서버에 키폰 전송 실패");
			m_Socket.Close();
			onDisConnected();
		}
	}
	else
	{
		PutStatus("서버에 접속 할 수 없습니다.");
		onDisConnected();
	}

}
*/

/*
BOOL CCall::ConnectSocket(CTSocket& tSocket, int nClientType, int nTryCount)
{
	static CString strError;
	if(nTryCount > 0)
	{		
		if(&tSocket == m_pSocket)	onError(0, strError);
		return FALSE;
	}
	else if(m_bShutDown)
		return FALSE;

	if(nClientType < 0)
		nClientType = m_nClientType;

	tSocket.Close();
	if(!tSocket.Create())
		return -1;
	tSocket.SetConnTimeOut(5000);
	tSocket.SetTimeOut(5000);

	if(tSocket.Connect(m_strHost, PORT_NUM))
	{
		int nError;
		TPACKET *p = (TPACKET*)tSocket.ReadStream(nError);
		if(NULL == p)
		{
			strError.Format("인증키 받기 실패!(%d)", nError);
			return ConnectSocket(tSocket, nClientType, nTryCount+1);
		}

		unsigned char* szkey = (unsigned char*)LICENSE_INFO;
		MD5_CTX ctx;
		unsigned char msgdigest[DIGESTLENGTH+CHALLENGESIZE32];
		MD5Init(&ctx);
		MD5Update(&ctx ,(unsigned char *)p->data, CHALLENGESIZE32);
		MD5Final(msgdigest, &ctx);
		int nXorPos  = p->data[28];
		int nXorPos2 = msgdigest[p->data[27]%DIGESTLENGTH]%80;
		if(p)
			free(p);

		for(int i = 0 ; i< DIGESTLENGTH ; i++)
		{
			msgdigest[i] = msgdigest[i] ^ szkey[nXorPos+i];
		}

		int nLengthOfszkey = strlen((char*)szkey);
		for(i = 0 ; i< CHALLENGESIZE32 ; i++)
		{
			msgdigest[DIGESTLENGTH+i] = szkey[nXorPos2+i] ^ szkey[ (nXorPos+i)%nLengthOfszkey];
		}

		if(!tSocket.SendBinary(PT_REQUEST, 0, msgdigest, DIGESTLENGTH+CHALLENGESIZE32))
		{
			strError = "인증키 전송 실패!!";
			return ConnectSocket(tSocket, nClientType, nTryCount+1);
		}

		p = (TPACKET*)tSocket.ReadStream(nError);
		if(NULL == p)
		{
			strError.Format("인증결과 받기 실패!(%d)", nError);
			return ConnectSocket(tSocket, nClientType, nTryCount+1);
		}

		int nType = p->nType;
		if(p)
			free(p);

		if( nType == PT_OK)
		{
			CString sConnStr;
			m_sKeyPhoneID.Replace("@", "");
			m_strName.Replace("@", "");


			sConnStr.Format("%s@%s@0.1@%d@%s@%s@%d", m_sKeyPhoneID, m_strName, nClientType, m_sKey, m_ui.strID, m_ui.nCompany);

			if(tSocket.SendData(PT_OK, NULL, (LPSTR)(LPCTSTR)sConnStr))
			{
				if(&tSocket == m_pSocket)
					onConnected();
				return TRUE;
			}
			else
			{
				tSocket.Close();
				if(&tSocket == m_pSocket)
					onDisConnected();
			}
		}

		tSocket.Close();
	}

//	if(!m_bShutDown && nClientType > 0)		onDisConnected(); 필요 없음 메인 소켓인 경우 Thread에 노출될것이고 그이왼 신경 안써도 됨
	return FALSE;
}
*/

BOOL CCall::ConnectSocket(CTSocket& tSocket, int nClientType, int nTryCount )
{
	CString strError;
	if(m_bShutDown)
		return FALSE;

	if(nClientType < 0)
		nClientType = m_nClientType;

	tSocket.Close();
	if(!tSocket.Create())
		return -1;

	tSocket.SetConnTimeOut(5000);
	tSocket.SetTimeOut(5000);

	if(tSocket.Connect(m_strHost, PORT_NUM))
	{
		//AfxMessageBox("ConnectSocket OK");
		int nError;
		TPACKET *p = (TPACKET*)tSocket.ReadStream(nError);
		if(NULL == p)
		{
			strError.Format("인증키 받기 실패!(%d)", nError);
			if(&tSocket == m_pSocket)	onError(0, strError);
			return FALSE;
		}

		unsigned char* szkey = (unsigned char*)LICENSE_INFO;
		MD5_CTX ctx;
		unsigned char msgdigest[DIGESTLENGTH+CHALLENGESIZE32];
		MD5Init(&ctx);
		MD5Update(&ctx ,(unsigned char *)p->data, CHALLENGESIZE32);
		MD5Final(msgdigest, &ctx);
		int nXorPos  = p->data[28];
		int nXorPos2 = msgdigest[p->data[27]%DIGESTLENGTH]%80;
		if(p)
			free(p);

		for(int i = 0 ; i< DIGESTLENGTH ; i++)
		{
			msgdigest[i] = msgdigest[i] ^ szkey[nXorPos+i];
		}

		int nLengthOfszkey = strlen((char*)szkey);
		for(int i = 0 ; i< CHALLENGESIZE32 ; i++)
		{
			msgdigest[DIGESTLENGTH+i] = szkey[nXorPos2+i] ^ szkey[ (nXorPos+i)%nLengthOfszkey];
		}

		if(!tSocket.SendBinary(PT_REQUEST, 0, msgdigest, DIGESTLENGTH+CHALLENGESIZE32))
		{
			if(&tSocket == m_pSocket)	onError(0,"인증키 전송 실패!!");			
			return FALSE;
		}

		p = (TPACKET*)tSocket.ReadStream(nError);
		if(NULL == p)
		{
			strError.Format("인증결과 받기 실패!(%d)", nError);
			if(&tSocket == m_pSocket)	onError(0, strError);
			return FALSE;
		}

		int nType = p->nType;
		if(p)
			free(p);

		if( nType == PT_OK)
		{
			CString sConnStr;
			m_sKeyPhoneID.Replace("@", "");
			m_strName.Replace("@", "");
			//sConnStr.Format("%s@%s@0.1@%d@%s",m_sKeyPhoneID,m_strName,nClientType,m_sKey);
			sConnStr.Format("%s@%s@0.1@%d@%s@%s@%d@%s",m_sKeyPhoneID,m_strName,nClientType,m_sKey, m_ui.strID, m_ui.nCompany, m_ui.strPW);
			if(tSocket.SendData(PT_OK, NULL, (LPSTR)(LPCTSTR)sConnStr))
			{
				if(&tSocket == m_pSocket)
					onConnected();
				return TRUE;
			}
			else
			{
				tSocket.Close();
				if(&tSocket == m_pSocket)
					onDisConnected();
				return FALSE;
			}
		}
		tSocket.Close();
	}

//	AfxMessageBox("ConnectSocket FASLE");
//	if(!m_bShutDown && nClientType > 0)		onDisConnected(); 필요 없음 메인 소켓인 경우 Thread에 노출될것이고 그이왼 신경 안써도 됨
	return FALSE;
}

/*
//소켓 접속 함수
void CCall::ReConnect()
{

	m_strHost.Trim();
	if(m_strHost.IsEmpty()) return;
	m_Socket.Close();

	PutStatus("접속 종료됨");

	if(!m_Socket.Create()) 
	{
		PutStatus("소켓 생성 실패");
		return;
	}

	m_Socket.SetConnTimeOut(1000);
	m_Socket.SetTimeOut(1000);

	if(m_Socket.Connect(m_strHost, PORT_NUM))
	{
		CString sConnStr;
		m_sKeyPhoneID.Replace("@", "");
		m_strName.Replace("@", "");
		sConnStr.Format("%s@%s@0.1@%d@%s",m_sKeyPhoneID,m_strName,m_nClientType,m_sKey);

		if(m_Socket.SendData(PT_OK, NULL, (LPSTR)(LPCTSTR)sConnStr))
		{
			//PutStatus("%s 서버에 접속됨", m_strHost);
			PutStatus("서버에 접속됨");
			onConnected();
		}
		else
		{
			PutStatus("서버에 키폰 전송 실패");
			m_Socket.Close();
			onDisConnected();
		}
	}
	else
	{
		PutStatus("서버에 접속 할 수 없습니다.");
		onDisConnected();
	}

}
*/

int GetPhType(char aEF)
{
	switch(aEF)
	{
	case 'A' :return PH_ANSWER;
		break;
	case 'B' :return PH_RING;
		break;
	case 'C' :return PH_HANG_UP;
		break;
	case 'O' :return PH_OUT_BOUND_CALL;
		break;
	}

	return PH_RING;
}

int CCall::GetDeviceInfo(CString& snfo)
{

//	CSingleLock MyLock(&m_csSocket,TRUE);

//	if(FALSE == IsConnected() ) return -1;
//	m_pSocket


	CTSocket tSocket;
	if(FALSE == ConnectSocket(tSocket, 0) ) return -1;

	int nRet=0;

	if(FALSE == tSocket.SendData(PT_MONITER, PT_SUB_KEYPHONE_INFO, "1234") ) return -1;

	TPACKET *p = (TPACKET*)tSocket.ReadStream(nRet);

	if(0 == nRet || WSAETIMEDOUT == nRet || WSAEWOULDBLOCK == nRet)
	{
	}
	else 
	{
		TRACE("Error = %d\r\n",nRet);
		tSocket.Close();
		if(p) free(p);
		return nRet;
	}

	if(p != NULL)
	{
		CString sData(p->data);

		if(PT_SUB_KEYPHONE_INFO == p->nSubType && PT_MONITER == p->nType)
		{
			snfo = sData;
			if(p) free(p);
			return 0;
		}
	}
	if(p) free(p);
	return -1;
}

int CCall::GetVersionInfo(CString& snfo)						//서버 Version
{

	CTSocket tSocket;
	if(FALSE == ConnectSocket(tSocket, 0)) return -1;

	int nRet = 0;

	if(FALSE == tSocket.SendData(PT_MONITER,PT_SUB_MONITER_VERSION,"")) return -1;

	TPACKET *p = (TPACKET*)tSocket.ReadStream(nRet);

	if(0 == nRet || WSAETIMEDOUT == nRet || WSAEWOULDBLOCK == nRet)
	{
	}
	else 
	{
		TRACE("Error = %d\r\n", nRet);
		tSocket.Close();
		if(p) free(p);
		return nRet;
	}

	if(p != NULL)
	{
		snfo = p->data;
		if(p) free(p);
		return 0;		
	}
	if(p) free(p);
	return -1;
}
int CCall::GetStaringTimeInfo(CString& snfo)					//서버 시작 시간
{

	CTSocket tSocket;
	if(FALSE == ConnectSocket(tSocket, 0)) return -1;

	int nRet=0;

	if(FALSE == tSocket.SendData(PT_MONITER,PT_SUB_MONITER_STARTING_TIME,"")) return -1;

	TPACKET *p = (TPACKET*)tSocket.ReadStream(nRet);

	if(0 == nRet || WSAETIMEDOUT == nRet || WSAEWOULDBLOCK == nRet)
	{

	}
	else 
	{
		TRACE("Error = %d\r\n", nRet);
		tSocket.Close();
		if(p) free(p);
		return nRet;
	}

	if(p != NULL)
	{
		snfo = p->data;
		if(p) free(p);
		return 0;		
	}
	if(p) free(p);
	return -1;
}

int CCall::GetConnectClient(CString& sConnectClient)
{
	CTSocket tSocket;
	if(FALSE == ConnectSocket(tSocket,0)) return -1;


	int nRet=0;
	if(FALSE == tSocket.SendData(PT_MONITER,PT_SUB_MONITER_USER,"")) return -1;

	TPACKET *p = (TPACKET*)tSocket.ReadStream(nRet);

	if(0 == nRet || WSAETIMEDOUT == nRet || WSAEWOULDBLOCK == nRet)
	{
	}
	else 
	{
		if(p) free(p);
		tSocket.Close();		
		return nRet;
	}

	if(p != NULL)
	{
		CString sData(p->data);
		sData.Replace("@@", "\r\n");

		if(PT_SUB_MONITER_USER == p->nSubType && PT_MONITER == p->nType)
		{
			sConnectClient = sData;
			tSocket.Close();
			if(p) free(p);
			return 0;
		}
		if(p) free(p);
	}
	tSocket.Close();		
	return -1;
}

int CCall::GetMoniterKeyPhones(CString& sMoniterKeyPhones)
{
	int nRet = 0;
	do 
	{
		CTSocket tSocket;
		if(FALSE == ConnectSocket(tSocket, 0) ) return -1;


		nRet = GetMoniterKeyPhones_Send(tSocket);
		if(0 != nRet) break;
		nRet = GetMoniterKeyPhones_Receive(tSocket, sMoniterKeyPhones);
		if(0 != nRet) break;
	} while(0);
	
	return nRet;
}

int CCall::GetMoniterKeyPhones_Send(CTSocket& tSocket)
{
	if(FALSE == tSocket.SendData(PT_MONITER, PT_SUB_MONITER_GET_ANSWER_CALL_LINE, "")) return -1;
	return 0;
}

int CCall::GetMoniterKeyPhones_Receive(CTSocket& tSocket, CString& sMoniterKeyPhones)
{
	int nRet=0;
	
	TPACKET *p = (TPACKET*)tSocket.ReadStream(nRet);
	if(0 == nRet || WSAETIMEDOUT == nRet || WSAEWOULDBLOCK == nRet)
	{
	}
	else 
	{
		TRACE("Error = %d\r\n", nRet);
		tSocket.Close();
		if(p) free(p);
		return nRet;
	}

	if(p != NULL)
	{
		CString sData(p->data);
		sData.Replace("@@", "\r\n");

		sMoniterKeyPhones = sData;
		if(p) free(p);
		return 0;
		
	}
	if(p) free(p);
	return -1;
}


int CCall::SetMoniterKeyPhones(const char* szAnswerLines, const char* szARSLines, const char* szNonPRILines, const char* szRouteLines)
{
	CTSocket tSocket;
	if(FALSE == ConnectSocket(tSocket, 0)) return -1;

	char szdata[4096] = {0, };
	STRCPY(szdata, szAnswerLines);
	STRCAT(szdata, szARSLines);
	STRCAT(szdata, szNonPRILines);
	STRCAT(szdata, szRouteLines);

//	CSingleLock MyLock(&m_csSocket,TRUE);
	if(FALSE == tSocket.SendData(PT_MONITER, PT_SUB_MONITER_SET_ALL_CALL_LINE, szdata))return -1;
	WaitForServerSignal(tSocket);

	return 0;
}

int CCall::GetMoniterKeyPhones(CString& sAnswerLines, CString& sARSLines, CString& sNonPRILines, CString& sRouteLines)
{
	CTSocket tSocket;
	if(FALSE == ConnectSocket(tSocket, 0)) return -1;

	char szdata[4096] = {0, };
	char szAnswerLines[2000] = {0, };
	char szARSLines[2000] = {0, };
	char szNonPRILines[2000] = {0, };
	char szRouteLines[2000] = {0, };

//	CSingleLock MyLock(&m_csSocket,TRUE);
	int nError;
	if(FALSE == tSocket.SendData(PT_MONITER, PT_SUB_MONITER_SET_ALL_CALL_LINE, szdata)) return -1;	
	TPACKET *p = (TPACKET*)tSocket.ReadStream(nError);
	if(p != NULL)
	{
		STRTOK(p->data, 0, szAnswerLines, szARSLines, szNonPRILines, szRouteLines, VL_END);
		sAnswerLines = szAnswerLines;
		sARSLines	 = szARSLines;
		sNonPRILines = szNonPRILines;
		sRouteLines	= szRouteLines ;
		if(p) free(p);
		return 0;
	}
	return -1;
}

void CCall::DenialAnswer(const char* szDenialPhoneNumber, int nDenialDurationMinute, const char* szName, const char* szDesc)
{
	if(FALSE == IsConnected() ) return ;

	char data[2048] = {0, };
	char szBuffer[20] = {0, };

	STRCPY(data, "B");
	STRCAT(data, szDenialPhoneNumber);
	STRCAT(data, ltoa(nDenialDurationMinute,szBuffer,10));
	STRCAT(data, szName);
	STRCAT(data, szDesc);
	STRCAT(data, ltoa(m_ui.nCompany, szBuffer, 10));
	STRCAT(data, ltoa(m_ui.nWNo, szBuffer, 10));
	STRCAT(data, m_ui.strName);

	m_pSocket->SendData(PT_PHONE, PT_SUB_DENYAL_ANSWER, data) ;

/*
	CTSocket tSocket;
	if(FALSE == ConnectSocket(tSocket, 0) ) return ;
//	CSingleLock MyLock(&m_csSocket,TRUE);

	if( FALSE == tSocket.SendData(PT_PHONE,PT_SUB_DENYAL_ANSWER,data) ) return ;
	WaitForServerSignal(tSocket);
*/

}

void CCall::Answer()
{
	m_pSocket->SendData(PT_PHONE, PT_SUB_ANSWER, "");

/*
	CTSocket tSocket;
	if(FALSE == ConnectSocket(tSocket, 0) ) return ;
//	CSingleLock MyLock(&m_csSocket,TRUE);
	if(FALSE== tSocket.SendData(PT_PHONE,PT_SUB_ANSWER,"") ) return ;
	WaitForServerSignal(tSocket);
*/

}
void CCall::HangUp(const char* szKeyPhoneNumber)
{

//	CTSocket tSocket;
//	if(FALSE == ConnectSocket(tSocket, 0) ) return ;

	char data[1024] = {0, };
//	CSingleLock MyLock(&m_csSocket,TRUE);

	STRCPY(data, "D");

	if(strlen(szKeyPhoneNumber) >= 3)
		STRCAT(data, szKeyPhoneNumber);

	m_pSocket->SendData(PT_PHONE, PT_SUB_HANGUP, data);

//	if(FALSE== tSocket.SendData(PT_PHONE,PT_SUB_HANGUP,data) ) return;
//	WaitForServerSignal(tSocket);
}

void CCall::MakeCall(const char *szPrintCID, const char* szDialNumber)
{
//	CTSocket tSocket;
//	if(FALSE == ConnectSocket(tSocket, 0) ) return ;

	char data[1024] = {0, };
//	CSingleLock MyLock(&m_csSocket,TRUE);
	STRCPY(data, "C");
	STRCAT(data, szPrintCID);
	STRCAT(data, szDialNumber);

	m_pSocket->SendData(PT_PHONE, PT_SUB_CALL, data);

	/*char szPhone[24] = {0, };
	strcpy(szPhone, szDialNumberOriginal);

	onSetCallNumber(szPhone);*/

//	tSocket.SendData(PT_PHONE,PT_SUB_CALL,data);	
//	WaitForServerSignal(tSocket);
}

void CCall::Redirect_Answer(const char* szFromKeyPhoneNumber)
{
//	CTSocket tSocket;
//	if(FALSE == ConnectSocket(tSocket, 0) ) return ;

	char data[1024] = {0, };
//	CSingleLock MyLock(&m_csSocket,TRUE);
	STRCPY(data, szFromKeyPhoneNumber);

	m_pSocket->SendData(PT_PHONE, PT_SUB_REDIRECT_ANSWER, data);	
//	tSocket.SendData(PT_PHONE,PT_SUB_REDIRECT_ANSWER,data);	
//	WaitForServerSignal(tSocket);
}

void CCall::MakeCallingOrTransfer(const char* szYourKeyPhoneNumber)
{
//	CTSocket tSocket;
//	if(FALSE == ConnectSocket(tSocket, 0) ) return ;

	char data[1024] = {0, };
	//	CSingleLock MyLock(&m_csSocket,TRUE);
	STRCPY(data, szYourKeyPhoneNumber);
	m_pSocket->SendData(PT_PHONE, PT_SUB_MAKE_CALLING_OR_TRANSFER, data);	

//	tSocket.SendData(PT_PHONE,PT_SUB_MAKE_CALLING_OR_TRANSFER,data);	
//	WaitForServerSignal(tSocket);
}

void CCall::SetClientQueuePause(int nPause)
{
	char data[1024] = {0, };
	char szBuffer[20] = {0, };
	STRCPY(data, ltoa(nPause, szBuffer, 10));

	m_pSocket->SendData(PT_PHONE, PT_SUB_QUEUE_PAUSE, data);	
}

/*void CCall::RecPlayMyKeyphone(COleDateTime dtDate, CString sFile)
{
	char data[1024] = {0, };
	char szBuffer[10] = {0, };
	STRCPY(data, ltoa(dtDate.GetYear(), szBuffer, 10));
	STRCAT(data, ltoa(dtDate.GetMonth(), szBuffer, 10));
	STRCAT(data, ltoa(dtDate.GetDay(), szBuffer, 10));
	STRCAT(data, sFile);

	m_pSocket->SendData(PT_PHONE, PT_SUB_RECORD_PLAY, data);
}*/

void CCall::RecPlayMyKeyphone(CString sDate, CString sFile)
{
	char data[1024] = {0, };
	STRCPY(data, sDate.Left(4));
	STRCAT(data, sDate.Mid(5, 2));
	STRCAT(data, sDate.Right(2));
	STRCAT(data, sFile);

	m_pSocket->SendData(PT_PHONE, PT_SUB_RECORD_PLAY, data);
}

void CCall::Mute(int nMute)
{
	char data[1024] = {0, };
	char szBuffer[20] = {0, };
	STRCPY(data, ltoa(nMute, szBuffer, 10));

	m_pSocket->SendData(PT_PHONE, PT_SUB_MUTE, data);
}

void CCall::OpTransferCall(CString strYourKeyPhoneNumber)
{
	char data[1024] = {0, };
	STRCPY(data, strYourKeyPhoneNumber);
	m_pSocket->SendData(PT_PHONE, PT_SUB_OP_TRANSFER, data);
}

void CCall::OpPickUpCall(CString strYourKeyPhoneNumber)
{
	char data[1024] = {0, };
	STRCPY(data, strYourKeyPhoneNumber);
	m_pSocket->SendData(PT_PHONE, PT_SUB_OP_PICKUP, data);
}

void CCall::AnswerRecPlay(CString strFileName)
{
	char data[1024] = {0, };
	STRCPY(data, strFileName);

	m_pSocket->SendData(PT_PHONE, PT_SUB_ANSWER_REC_PLAY, data);
}

void CCall::BlindTransfer(CString strTransPhoneNumber)
{
	char data[1024] = {0, };
	STRCPY(data, strTransPhoneNumber);

	m_pSocket->SendData(PT_PHONE, PT_SUB_BLIND_TRANSFER, data);
}

void CCall::BlindTransferHangup(CString strTransPhoneNumber)
{
	char data[1024] = {0, };
	STRCPY(data, strTransPhoneNumber);

	m_pSocket->SendData(PT_PHONE, PT_SUB_BLIND_TRANSFER_HANGUP, data);
}


void CCall::DIDRoute(int nSubType, CString strDID, CString strToLine, BOOL bUse, CString strDesc)
{
	char data[1024] = {0, };
	char szBuffer[20] = {0, };
	STRCPY(data, strDID);
	STRCAT(data, strToLine);
	STRCAT(data, ltoa(bUse, szBuffer, 10));
	STRCAT(data, strDesc);

	m_pSocket->SendData(PT_DID_ROUTE, nSubType, data);
}

void CCall::SocketReadImpl()
{
	int nRet=0;
	TPACKET *p = (TPACKET*)m_pSocket->ReadStream(nRet);

	if(0 == nRet || WSAETIMEDOUT == nRet || WSAEWOULDBLOCK == nRet)
	{
	}
	else 
	{
		m_pSocket->Close();
		onDisConnected();
		Sleep(10);
		if(p) free(p);
		if(m_bShutDown)	return;
	}

	if(p != NULL)
	{
		CString sData(p->data);
		sData.Replace("@@", "\r\n");
		switch(p->nType)
		{
		case PT_OK    :
		case PT_PHONE :
			{
				char szEF[10] = {0, };
				char szGroup[10] = {0, };
				char szPhoneNumber[20] = {0, };
				char szCurKeyPhoneID[20] = {0, };
				char szDID[20] = {0,};
				char szIsCTI[5] = {0,};

				STRTOK(sData, 0, szEF, szGroup, szPhoneNumber, szCurKeyPhoneID, szDID, VL_END);
				onCallChange(GetPhType(szEF[0]), szPhoneNumber, szCurKeyPhoneID, szDID);
			}
			break;
		case PT_PHONE_INFO_TAPI :
		case PT_PHONE_INFO_SMDR :
			{
				char szEF[10] = {0, };
				char szGroup[10] = {0, };
				char szPhoneNumber[20] = {0, };
				char szCurKeyPhoneID[20] = {0, };
				char szDID[20] = {0, };
				char szOPerateName[100] = {0, };
				char szCustomerName[100] = {0, };
				char szLastOPerateName[100] = {0, };

				STRTOK(sData, 0, szEF, szGroup, szPhoneNumber, szCurKeyPhoneID, szDID, szOPerateName, szCustomerName, szLastOPerateName, VL_END);
				onCallInfoLog(GetPhType(szEF[0]), szPhoneNumber, szCurKeyPhoneID, szDID, szOPerateName, szCustomerName, szLastOPerateName);
			}
			break;
		case PT_MONITER :
			{
				if(PT_SUB_MONITER_CALL == p->nSubType)
				{
					char szRing[10] = {0, };
					char szAnswer[10] = {0, };
					char szMissingCallCnt[10] = {0, };
					char szMissingCallPerMin[10] = {0, };

					STRTOK(sData, 0, szRing, szAnswer, szMissingCallCnt, szMissingCallPerMin, VL_END);

					onMoniter(atoi(szRing), atoi(szAnswer), atoi(szMissingCallCnt), atoi(szMissingCallPerMin) );
				}
				else if(PT_SUB_MONITER_LOG == p->nSubType)
				{
					onMoniterLog(sData);
				}
				else if(PT_SUB_MONITER_USER == p->nSubType)
				{
					onMoniterUserLog(sData);
				}
				else if(PT_SUB_MONITER_GET_ANSWER_CALL_LINE == p->nSubType)
				{
					onMoniterAnswerLinesChanged(sData);
				}
				else if(PT_SUB_MONITER_GET_ALL_CALL_LINE == p->nSubType)
				{
					char szAnswerLines[2000];
					char szARSLines[2000];
					char szNonPRILines[2000];
					char szRouteLines[2000];
					STRTOK(sData, 0, szAnswerLines, szNonPRILines, szRouteLines);

					onMoniterLinesChanged(szAnswerLines, szARSLines, szNonPRILines, szRouteLines);
				}
				else if(PT_SUB_MONITER_ROUTE ==  p->nSubType)
				{
					char szEF[10] = {0, };
					char szGroup[10] = {0, };
					char szPhoneNumber[20] = {0, };
					char szCurKeyPhoneID[20] = {0, };
					char szDID[20] = {0, };
					char szIsCTI[5] = {0, };
					char szInfo[100] = {0, };

					STRTOK(sData, 0,szEF, szGroup, szPhoneNumber, szCurKeyPhoneID, szDID, szIsCTI, szInfo, VL_END);
					onRouteCallChange(GetPhType(szEF[0]), szPhoneNumber, szCurKeyPhoneID, szDID, szInfo);

				}
				else if (PT_SUB_QUEUE_PAUSE == p->nSubType)
				{
					char szQueuePause[10] = {0, };

					STRTOK(sData, 0, szQueuePause, VL_END);
					SetQueuePause(atoi(szQueuePause));
				}
				else if(PT_SUB_RECORDFILE_ID == p->nSubType)
				{
					char szKeyPhoneID[10] = {0, };
					char szPhoneNumber[20] = {0, };
					char szInsertID[10] = {0, };

					STRTOK(sData, 0, szKeyPhoneID, szPhoneNumber, szInsertID, VL_END);
					onRecordFileNameInsertID(szKeyPhoneID, szPhoneNumber, atoi(szInsertID));
				}
				else if(PT_SUB_MUTE == p->nSubType)
				{
					char szMute[10] = {0, };

					STRTOK(sData, 0, szMute, VL_END);
					onMuteState(atoi(szMute));
				}
				else if(PT_SUB_ANSWER_REC_PLAY == p->nSubType)
				{
					char szAnswerRecPlay[10] = {0, };

					STRTOK(sData, 0, szAnswerRecPlay, VL_END);
					onAnswerRecPlay(atoi(szAnswerRecPlay));
				}
				else if(PT_SUB_BLIND_TRANSFER ==  p->nSubType)
				{
					char szBlindTrnasfer[10] = {0, };

					STRTOK(sData, 0, szBlindTrnasfer, VL_END);
					onBlindTransfer(atoi(szBlindTrnasfer));
				}
			}
			break;
		case PT_DID_ROUTE:
			{
				char szDIDRouteDID[20];
				char szDIDRouteLine[20];
				char szDIDRouteUse[10];
				char szDIDRouteDesc[200];

				STRTOK(p->data, 0, szDIDRouteDID, szDIDRouteLine, szDIDRouteUse, szDIDRouteDesc, VL_END);

				onDIDRouteChange(p->nSubType, szDIDRouteDID, szDIDRouteLine, atoi(szDIDRouteUse), szDIDRouteDesc);
			}
		case PT_PHONENUMER_INFO:
			{
				char szPhoneNumber[20] = {0, };
				char szCName[300] = {0, };
				char szDesc[3000] = {0, };

				STRTOK(sData, 0, szPhoneNumber, szCName, szDesc, VL_END);
				onCustomerInfo(szPhoneNumber, szCName, szDesc);
			}
			break;
		case PT_ERROR:
			onError(p->nSubType,sData);
			break;
		}

		//수신 버퍼 초기화
		if(p) free(p);
	}
}

UINT CCall::SocketRead(LPVOID lParam)
{
	while(FALSE == m_bThreadEnd)
	{
		if(m_bShutDown)	
		{
			Sleep(100);
			continue;
		}

		if(!m_pSocket->IsConnected()) 
		{
			ConnectSocket(*m_pSocket, m_nClientType);
			Sleep(100);
			continue;
		}

		SocketReadImpl();
		Sleep(1);
	}

	SetEvent(m_hExitEvent);
	return 0;
}

/*
//소켓 쓰레드
UINT CCall::SocketProc(LPVOID lParam)
{

	HANDLE	hEvent[2];
	CString strData;
	char data[255];

	hEvent[0] = m_hRecvEvent;
	hEvent[1] = m_hKillEvent;


	if(!m_Socket.IsConnected()) ConnectSocket(m_Socket);

	while(FALSE == m_bShutDown)
	{
		DWORD nRet = WaitForMultipleObjects(2, (HANDLE*)&hEvent,  FALSE, 1000);

		if(nRet == WAIT_OBJECT_0) {
			//서버에 접속되어 있지 않다면, 자신의 값도 보내지 않는다.
			
		}
		else if(nRet == WAIT_OBJECT_0 + 1) {
			GetLog()->Print(LL_DEBUG, "소켓 쓰레드 종료\n");
			break;			
		}
		else 
		{
			if(!m_bUserClosed)
			{
				if(!m_Socket.IsConnected())
				{
					ConnectSocket(m_Socket);
				}
			}
		}
	}

	m_Socket.Close();
	SetEvent(m_hExitEvent);

	return 0;
}
*/