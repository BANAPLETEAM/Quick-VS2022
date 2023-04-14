// MkDatabase.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MkDatabase.h"
#include "QSocket.h"
#include "UploadingDlg.h"
#include "md5.h"
#include "process.h"
#include "QueryLogDlg.h"
#include "MkLock.h"

#define LICENSE_INFO "Our aim is to keep our cost as low as possible so that"\
				"we can economically provide mobile service for the community."\
				"better than the several program corporation "\
				"such as ICON, TECHNO, EASY, INSUNG, DAEYOUNG";
#define DIGESTLENGTH	16
#define CHALLENGESIZE32       32 


//#define LOCK()		EnterCriticalSection(&m_csLock)
//#define UNLOCK()	LeaveCriticalSection(&m_csLock)

#define CHALLENGESIZE	8
#define CONN_TEST_TIME		15000		//milisecond
#define	SLEEP_STATE_TIME	60000		//millsecond


BYTE fixedkey_xx[8] = {234,78,12,29,18,23,7,11};	//보안상 지우지 않음
BYTE fixedkey_yy[12] = {34,8,22,39,48,53,22,99,19,28,100,30};	//보안상 지우지 않음
BYTE serverkey[8] = {45,79,92,42,02,57,71,06};

CQueryLogDlg* CMkDatabase::m_pQueryLogDlg = NULL;
BOOL CMkDatabase::m_bSetExternalLog = FALSE;
volatile long CMkDatabase::m_nRefCount = 0;
CBanaLog* CMkDatabase::m_pLog = NULL;
CDisplayBarProgressInfo CMkDatabase::m_dbpiBasic("데이터 분석중입니다.", 1000);



COMMAND_MAP CMkDatabase::m_mapRefCommand;
CCriticalSection CMkDatabase::m_csRefCommand;

// CMkDatabase

IMPLEMENT_DYNAMIC(CMkDatabase, CWnd)

CMkDatabase::CMkDatabase(CBanaLog* pLog)
{
	InterlockedIncrement(&m_nRefCount);
	SetLog(pLog);

	Create(NULL, "", WS_CHILD, CRect(0,0,0,0), GetDesktopWindow(), 0);

	m_Socket = new CQSocket();
	m_bLiveThread = FALSE;
	m_hKillEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//InitializeCriticalSection(&m_csLock);
	//InitializeCriticalSection(&m_csQuery);

	m_nAsyncMode = FD_CLOSE;
	m_hParentWnd = NULL;
	m_bMessenger = FALSE;
	m_bShownErrorDialog = FALSE;
	m_nErrorMsgType = 0;

	m_dwActiveTime = GetTickCount();
	m_bEnableSleepMode = FALSE;
	m_bSleepState = FALSE;
	m_bDeveloperMode = FALSE;
	m_bTransferWithoutAck = FALSE;
	m_bAliveRunningThread = FALSE;
	m_bAliveUIThread = FALSE;
	m_hRunningEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hUIEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_bUserStop = FALSE;
	m_pEnteringCmd = NULL;
	m_pLastRecordsetChunk = NULL;
	m_nLastReccordsetSize = 0;

	MakeRandomByte(m_nXorKey);

	m_pDBT = (CDisplayBarThread*)AfxBeginThread(RUNTIME_CLASS(CDisplayBarThread), 0, 0, 0);
	m_pDBT->m_bAutoDelete = TRUE;
}

CMkDatabase::~CMkDatabase()
{
	m_pDBT->PostThreadMessage(WM_QUIT, 0, 0);
	WaitForSingleObject(m_pDBT->m_hThread, 5000);

	InterlockedDecrement(&m_nRefCount);
	SetEvent(m_hKillEvent);
	m_Socket->Close();
	CloseHandle(m_hRunningEvent);
	CloseHandle(m_hUIEvent);
	delete m_Socket;

	if(!m_bSetExternalLog && m_nRefCount == 0 && m_pLog)
	{
		delete m_pLog;
		m_pLog = NULL;
	}
}


BEGIN_MESSAGE_MAP(CMkDatabase, CWnd)
	ON_MESSAGE(WM_ASYNC_EVENT, OnAsyncEvent)
END_MESSAGE_MAP()



// CMkDatabase 메시지 처리기입니다.

#define PT_DATABASE3		888

BOOL CMkDatabase::ConnectServer(BOOL bSecondRun)
{
	g_bana_log->Print("LOGIDB::Try ConnectServer %s\n", bSecondRun ? "Second Run" : "");

	GetNextServerAddr();

	if(!bSecondRun)
	{
		if(!m_Socket->Create()) {
			return FALSE;
		}

		m_Socket->SetConnTimeOut(5);
	}

	DWORD dwTickCount = GetTickCount();

	if(m_Socket->Connect(m_strServerAddress, m_nHostPort))
	{
		m_Socket->SetTimeOut(30);

		QPACKET *p = NULL;
	
		m_Socket->SetParentWnd(this->GetSafeHwnd());
		m_Socket->AsyncSelect(FD_CLOSE);

		if(m_Socket->SendCommand(PT_DATABASE3, 0)) {
			if((p = (QPACKET*)m_Socket->ReadStream()) != NULL) {
				if(p->nType == PT_OK) {
					deskey(m_nServerKey, DE1);
                    des((BYTE*)p->data, (BYTE*)p->data);

					unsigned char* szkey = (unsigned char*)LICENSE_INFO;
					MD5_CTX ctx;
					unsigned char msgdigest[DIGESTLENGTH+CHALLENGESIZE32];
					MD5Init(&ctx);
					MD5Update(&ctx ,(unsigned char *)p->data, CHALLENGESIZE32);
					MD5Final(msgdigest, &ctx);
					int nXorPos  = p->data[28];
					int nXorPos2 = msgdigest[ p->data[27]%DIGESTLENGTH]%80;

					int i = 0;
					for(i = 0;i< DIGESTLENGTH;i++)
					{
						msgdigest[i] = msgdigest[i] ^ szkey[nXorPos+i];
					}

					int nLengthOfszkey = strlen((char*)szkey);
					for(i = 0;i< CHALLENGESIZE32;i++)
					{
						msgdigest[DIGESTLENGTH+i] = szkey[nXorPos2+i] ^ szkey[ (nXorPos+i)%nLengthOfszkey];
					}

					if(m_Socket->SendBinary(PT_DATABASE3, 1, msgdigest, DIGESTLENGTH+CHALLENGESIZE32))
					{
						if(P_SUCCESS == m_Socket->WaitOK())
						{
							g_bana_log->Print("CMkDatabase: Socket connected\n");
							free(p);

							BOOL bRet = TRUE;
							if(m_bMessenger) {
								bRet = MessengerLogin();
								if(bRet) {
									m_Socket->SetParentWnd(m_hParentWnd);
									m_Socket->AsyncSelect(m_nAsyncMode);
									::PostMessage(m_hParentWnd, WM_ASYNC_EVENT, m_Socket->GetSocket(), 0xFFFF);
								}
							}

							return bRet;
						}
					}
				}
			}
		}

		if(GetTickCount() - dwTickCount < 3000 && !bSecondRun)
		{
			Sleep(1000);
			m_Socket->AsyncSelect(NULL);
			return ConnectServer(TRUE);
		}

		if(p != NULL) free(p);
	}
	else
	{
		if(GetTickCount() - dwTickCount < 3000 && !bSecondRun)
		{
			Sleep(1000);
			return ConnectServer(TRUE);
		}
	}

	return FALSE;
}


//소켓 쓰레드
UINT CMkDatabase::ConnectTestProc(LPVOID lParam)
{
	m_bLiveThread = TRUE;

	if(!m_Socket->IsConnected()) 
		ConnectServer();

	DWORD dwTime = GetTickCount();

	while(1)
	{
		if(WAIT_OBJECT_0 == WaitForSingleObject(m_hKillEvent, 2000)) {
			//g_bana_log->Print(LL_DEBUG, "소켓 쓰레드 종료\n");
			break;			
		}
		else {
			if(m_bShownErrorDialog)
			{
				Sleep(1000);
				break;
			}

			int nTickCount = GetTickCount();

			if(m_bSleepState) continue;

			if(m_bEnableSleepMode &&
				nTickCount - m_dwActiveTime >= SLEEP_STATE_TIME)
			{
				m_bSleepState = TRUE;
				m_Socket->Close();
				g_bana_log->Print("in the sleep mode\n");
				continue;
			}

			if(m_Socket->IsConnected()) {
				if(nTickCount - dwTime >= CONN_TEST_TIME && 
					nTickCount - m_dwActiveTime >= CONN_TEST_TIME) {
						CMkLock lock(m_csLock);
						dwTime = GetTickCount();
						m_Socket->SetTimeOut(5);
						if(!m_Socket->SendData(PT_CONNTEST2, 0, (LPSTR)(LPCTSTR)m_strClientInfoPacket)) 
						{
							g_bana_log->Print("CMkDatabase: fail to send the PT_CONNTEST2\n");
							m_Socket->Close();
							ConnectServer();
						}
						m_Socket->SetTimeOut(30);
					}
			}
			else {
				ConnectServer();
			}
		}
	}

	m_bLiveThread = FALSE;
	return 0;
}

BOOL CMkDatabase::Open(CString strHostAddress, UINT nHostPort, BOOL bJustConnect)
{
	m_strServerAddress = strHostAddress;
	m_nHostPort = nHostPort;

	if(!m_bLiveThread) {
		DWORD dwThreadID;
		if(bJustConnect)
			if(!ConnectServer())
				return FALSE;
		HANDLE hHandle = ::CreateThread(NULL, 0, 
			(LPTHREAD_START_ROUTINE) staticConnectTestProc, 
			(LPVOID) this, 0, &dwThreadID);
		CloseHandle(hHandle);
	}
	else {
		if(bJustConnect)
			if(!ConnectServer())
				return FALSE;
	}

	return TRUE;
}


LONG CMkDatabase::OnAsyncEvent(SOCKET wSocket, LPARAM lParam)
{
	if(WSAGETSELECTERROR(lParam))
	{
		g_bana_log->Print("CMkDatabase: OnAsyncEvent Error(%d)\n", WSAGETSELECTERROR(lParam));
		//m_Socket->Close();
		return 0;
	}

	switch(WSAGETSELECTEVENT(lParam))
	{
		case FD_CLOSE:
			g_bana_log->Print("CMkDatabase: OnAsyncEvent FD_CLOSE\n");
			m_Socket->Close();
			break;
		
		case FD_READ:
			{
				QPACKET *p = (QPACKET*)m_Socket->ReadStream();
				if(p != NULL) {
					OnDataRead(p);
					free(p);
				}
			}	
			break;

	}
	return 0;
}


void CMkDatabase::OnDataRead(void *p)
{
}
/*
void CMkDatabase::OnDataRead(QPACKET *p)
{
}
*/

LPVOID CMkDatabase::_Execute(int *pnType, LPVOID buf, UINT *pnSize, CString &strCommand, int &nErrorCode)
{
	m_dwTotalSize = 0;
	m_dwCurSize = 0;
	m_dwElapsedTime = 0;

	nErrorCode = 0;

	if(!m_Socket->IsConnected()) 
		if(!ConnectServer()) 
			return NULL;

	CMkLock lock(m_csLock);
	QPACKET *p = NULL;
	int nTotalSize, nCursor = 0;
	int nSubType = m_bTransferWithoutAck ? PST_EXECUTE_DB_WITHOUT_ACK : PST_EXECUTE_DB2;
	char *pBuffer = NULL;
	DWORD dwTick = 0;

	m_dwActiveTime = GetTickCount();
	m_bSleepState = FALSE;

	if(m_Socket->SendBinary(PT_OK, nSubType, buf, *pnSize)) {
		while((p = (QPACKET*)m_Socket->ReadStream()) != NULL) {
			if(p->nType == PT_OK) {
				*pnType = p->nSubType;
				*pnSize = p->nPacketSize - sizeof(QPACKET);
				pBuffer = new char[*pnSize + 1];
				memcpy(pBuffer, p->data, *pnSize);
				if(p != NULL) free(p);
				return pBuffer;
			}
			else if(p->nType == PT_NEXT) {
				if(!m_Socket->SendCommand(PT_OK)) 
					break;

				if(p->nSubType == PST_FILE_INFO) {
					dwTick = GetTickCount();
					nTotalSize = atol(p->data);
					pBuffer = new char[nTotalSize + 1];
					m_dwTotalSize = nTotalSize;
				}
				else {
					int nCurSize = p->nPacketSize - sizeof(QPACKET);
					memcpy(pBuffer + nCursor, p->data, nCurSize);
					nCursor += nCurSize;
				}

				if(p != NULL) free(p);
				m_dwCurSize = nCursor;
				m_dwElapsedTime = GetTickCount() - dwTick;
			}
			else if(p->nType == PT_END) {
				*pnType = p->nSubType;
				*pnSize = nTotalSize;
				if(p != NULL) free(p);
				return pBuffer;				
			}
			else if(p->nType == PT_ERROR) {
				m_pDBT->PostThreadMessage(WM_DISPLAY_BAR_HIDE, 0, 0);

				if(m_nErrorMsgType == EMT_NORMAL)
				{
					CString strMsg;
					strMsg = "개체 '" + strCommand + "' 를 실행중에 오류가 발생했습니다.\n";
					strMsg += p->data;
					strMsg += "\n\n지속적으로 발생시에 개체이름과 오류코드를 기억하시고,\n";
					strMsg += "로지소프트로 문의하시기 바랍니다.";
					m_bShownErrorDialog = TRUE;
					::MessageBox(NULL, strMsg, "데이터베이스 오류", MB_ICONERROR);
					m_bShownErrorDialog = FALSE;
				}
				else if(m_nErrorMsgType == EMT_SIMPLE) 
				{
					m_bShownErrorDialog = TRUE;
					::MessageBox(NULL, "데이터 통신중에 오류가 발생했습니다.\n재시도 하시기 바랍니다.",
								"데이터 통신 실패", 
								MB_ICONINFORMATION);
					m_bShownErrorDialog = FALSE;
				}
				else if(m_nErrorMsgType == EMT_NO_SHOW)
				{
					CString strMsg;
					strMsg = "개체 '" + strCommand + "' 를 실행중에 오류가 발생했습니다.\n";
					strMsg += p->data;
					strMsg += "\n\n지속적으로 발생시에 개체이름과 오류코드를 기억하시고,\n";
					strMsg += "로지소프트로 문의하시기 바랍니다.";
#ifdef _DEBUG
					m_bShownErrorDialog = TRUE;
					::MessageBox(NULL, strMsg, "데이터베이스 오류", MB_ICONERROR);
					m_bShownErrorDialog = FALSE;
#else
					g_bana_log->Print("%s\n", strMsg);
#endif
				}

				if(p != NULL) free(p);
				return NULL;
			}
		}
		if(p != NULL) free(p);
	}
	else {
		g_bana_log->Print("CMkDatabase: Execute send failed\n");
		nErrorCode = 1;
	}

	if(pBuffer != NULL) delete[] pBuffer;

	return NULL;
}

LPVOID CMkDatabase::Execute(int *pnType, LPVOID buf, UINT *pnSize, CString &strCommand)
{
	int nErrorCode = 0;
	LPVOID pBuffer = _Execute(pnType, buf, pnSize, strCommand, nErrorCode);

	if(pBuffer)
		return pBuffer;

	if(nErrorCode == 1)
	{
		m_Socket->Close();
		if(m_Socket->Create())
		{
			m_Socket->SetConnTimeOut(5);
			g_bana_log->Print("Second Excute\n");
			pBuffer = _Execute(pnType, buf, pnSize, strCommand, nErrorCode);
			if(pBuffer)
				return pBuffer;
		}
	}

	if(!IsUserStop())
	{
		m_pDBT->PostThreadMessage(WM_DISPLAY_BAR_HIDE, 0, 0);

		if(m_nErrorMsgType != EMT_NO_SHOW)
		{
			m_bShownErrorDialog = TRUE;
			AfxGetMainWnd()->MessageBox("인터넷 연결 상태가 좋지 않거나, 일시적인 서버 장애 입니다.\n다시 시도하시기 바랍니다." , 
				"인터넷 통신 실패", MB_ICONERROR);
			m_bShownErrorDialog = FALSE;
		}
#ifdef _DEBUG
		else
		{
			m_bShownErrorDialog = TRUE;
			AfxGetMainWnd()->MessageBox("인터넷 연결 상태가 좋지 않거나, 일시적인 서버 장애 입니다.\n다시 시도하시기 바랍니다." , 
				"인터넷 통신 실패", MB_ICONERROR);
			m_bShownErrorDialog = FALSE;
		}
#endif

	}

	SetUserStop(FALSE);	
	return NULL;
}


LPVOID CMkDatabase::_ExecuteCommand(UINT &nType, UINT &nSubType, UINT &nSize, char *szPacket, int &nErrorCode)
{
	nErrorCode = 0;

	if(!m_Socket->IsConnected()) 
		if(!ConnectServer()) 
			return NULL;

	QPACKET *p = NULL;
	int nTotalSize, nCursor = 0;
	char *pBuffer = NULL;

	if(m_Socket->SendData(nType, nSubType, szPacket)) {
		while((p = (QPACKET*)m_Socket->ReadStream()) != NULL) {
			if(p->nType == PT_OK) {
				nType = p->nType;
				nSubType = p->nSubType;
				nSize = p->nPacketSize - sizeof(QPACKET);
				pBuffer = new char[nSize + 1];
				memcpy(pBuffer, p->data, nSize);
				if(p != NULL) free(p);
				return pBuffer;
			}
			else if(p->nType == PT_NEXT) {
				if(p->nSubType == PST_FILE_INFO) {
					nTotalSize = atol(p->data);
					pBuffer = new char[nTotalSize + 1];
				}
				else {
					int nCurSize = p->nPacketSize - sizeof(QPACKET);
					memcpy(pBuffer + nCursor, p->data, nCurSize);
					nCursor += nCurSize;
				}

				if(p != NULL) free(p);
				if(!m_Socket->SendCommand(PT_OK)) {
					break;
				}
			}
			else if(p->nType == PT_END) {
				nType = p->nType;
				nSubType = p->nSubType;
				nSize = nTotalSize;
				if(p != NULL) free(p);
				return pBuffer;				
			}
			else if(p->nType == PT_ERROR) {
				g_bana_log->Print("error\n");
				if(p != NULL) free(p);
				return NULL;
			}
		}
		if(p != NULL) free(p);
	}
	else {
		g_bana_log->Print("CMkDatabase: ExecuteRecordsetOnly failed\n");
		nErrorCode = 1;
	}


	if(pBuffer != NULL) delete[] pBuffer;

	return NULL;
}

LPVOID CMkDatabase::ExecuteCommand(UINT &nType, UINT &nSubType, UINT &nSize, char *szPacket)
{
	int nErrorCode = 0;
	LPVOID pBuffer = _ExecuteCommand(nType, nSubType, nSize, szPacket, nErrorCode);

	if(pBuffer)
		return pBuffer;

	if(nErrorCode == 1)
	{
		m_Socket->Close();
		if(m_Socket->Create())
		{
			m_Socket->SetConnTimeOut(5);
			g_bana_log->Print("Second Excute\n");
			pBuffer = _ExecuteCommand(nType, nSubType, nSize, szPacket, nErrorCode);
			if(pBuffer)
				return pBuffer;
		}
	}

	return NULL;
}

BOOL CMkDatabase::MessengerLogin()
{
	try {
		if(!m_Socket->SendBinary(PT_REQUEST, PST_START_MSG5, &m_LoginInfo, sizeof(MSG_LOGIN_INFO)))
			throw "데이터 전송중 오류 발생";

		if(m_Socket->WaitOK() != P_SUCCESS)
			throw "데이터 수신중 오류 발생";

		return TRUE;

	}
	catch(char *szMsg)
	{
		UNUSED_ALWAYS(szMsg);
		return FALSE;
	}
}

void CMkDatabase::Close() 
{ 
	m_Socket->Close();
	SetEvent(m_hKillEvent); 
}

void CMkDatabase::SetSeatAway(BOOL bEmpty)
{
	if(m_Socket->IsConnected())
		m_Socket->SendCommand(PT_REQUEST, bEmpty ? PST_SEAT_EMPTY : PST_SEAT_OCCUPIED);

}


UINT CMkDatabase::AsyncSelect(UINT nMode, BOOL bJustRun) 
{ 
	long nPreMode = m_nAsyncMode;
	m_nAsyncMode = nMode; 
	if(bJustRun)
		m_Socket->AsyncSelect(nMode);
	return nPreMode;
}

BOOL CMkDatabase::UploadFile(CString strFileName, char *pBuffer, long nLength)
{
	#define SEND_PACKET_SIZE	4096


	CMkLock lock(m_csLock);

	char buffer[MAX_PATH];
	char szLength[MAX_PATH];

	STRCPY(buffer, ltoa(nLength, szLength, 10), VL_END);
	STRCAT(buffer, (LPSTR)(LPCTSTR)strFileName, VL_END);
	
	if(m_Socket->SendData(PT_FILE, 0, buffer))
	{
		m_nSend = 0;

		while(m_nSend < nLength)
		{
			int nPacketSize = min(nLength - m_nSend, SEND_PACKET_SIZE);
			if(!m_Socket->SendBinary(PT_FILE, 1, (pBuffer + m_nSend), nPacketSize))
				return FALSE;

			m_nSend += nPacketSize;


			QPACKET *p = NULL;
			if((p = (QPACKET*)m_Socket->ReadStream()) != NULL) 
			{
				if(p->nType == PT_ERROR)
				{
					g_bana_log->Print("file send error: %d\n", p->nSubType);
					return FALSE;
				}
			}
			g_bana_log->Print("size = %d\n", m_nSend);
		}
	
		if(m_nSend == nLength)
			return TRUE;
	}

	return FALSE;

}

BOOL CMkDatabase::UploadFileWithDlg(CString strFileName, char *pBuffer, DWORD nLength)
{
	BOOL bRet;
	CUploadingDlg  dlg(&bRet, this, this, strFileName, pBuffer, nLength);
	dlg.DoModal();
	return bRet;
}


void CMkDatabase::SetClientInfo(long nCompanyCode, long nWNo, BOOL bDeveloper)
{
	char buffer[50], szCompany[20], szWNo[20], szDeveloper[20];
	ltoa(nCompanyCode, szCompany, 10);
	ltoa(nWNo, szWNo, 10);
	ltoa(bDeveloper, szDeveloper, 10);

	STRCPY(buffer, szCompany, szWNo, szDeveloper, VL_END);

	m_strClientInfoPacket = buffer;
}

void CMkDatabase::MakeRandomByte(BYTE &nByte)
{
	static unsigned int seed;
	seed += (unsigned int) time(0) + getpid() + getpid() * 987654;

	srand(seed);
	nByte = (char)(rand() % 128);
}

void CMkDatabase::SetServerKey(BYTE nServerKey[8], BOOL bPlain)
{
	if(!bPlain)
	{
		BYTE nXorKey = (m_nXorKey + 3) % 128;
		for(int i = 0; i < 8; i++)
			m_nServerKey[i] = nServerKey[i] ^ ((nXorKey + i) % 128);
	}
	else
	{
		for(int i = 0; i < 8; i++)
			m_nServerKey[i] = nServerKey[i];
	}
}


void CMkDatabase::ShowQueryLog()
{
	if(GetDeveloperMode())
	{
		if(m_pQueryLogDlg == NULL)
		{
			m_pQueryLogDlg = new CQueryLogDlg(this);
			m_pQueryLogDlg->Create(IDD_QUERY_LOG_DLG, this);
		}
		m_pQueryLogDlg->ShowWindow(SW_SHOWNA);
	}

}

void CMkDatabase::AddDisServer(CString strServerAddr, UINT nServerPort)
{
	SERVER_ADDR_INFO si;
	si.strServerAddr = strServerAddr;
	si.nServerPort = nServerPort;
	m_sl.Add(si);
}

void CMkDatabase::GetNextServerAddr()
{
	int nListCount = m_sl.GetCount();

	if(nListCount > 0)
	{
		static unsigned int seed;
		seed += (unsigned int) time(0) + getpid() + getpid() * 987654;
		srand(seed);

		int nServerIndex = AfxGetApp()->GetProfileInt("DisServer", m_strServerName, -1);
		if(nServerIndex < 0 || nServerIndex >= nListCount)
		{
			nServerIndex = rand() % (nListCount);
		}
		else
		{
			if(rand() % 2 == 0)
				nServerIndex--;
			else 
				nServerIndex++;
			
			if(nServerIndex >= nListCount)
				nServerIndex = 0;
			else if(nServerIndex < 0)
				nServerIndex = nListCount - 1;
		}

		SERVER_ADDR_INFO sai = m_sl.GetAt(nServerIndex);
		m_strServerAddress = sai.strServerAddr;
		m_nHostPort = sai.nServerPort;

		AfxGetApp()->WriteProfileInt("DisServer", m_strServerName, nServerIndex);
		g_bana_log->Print("** DisServer Change: %s, %d\n", m_strServerAddress, m_nHostPort);
	}
}


UINT CMkDatabase::RunningProc(LPVOID lParam)
{
	m_bAliveRunningThread = TRUE;

	HANDLE hEvent[2];

	hEvent[0] = m_hRunningEvent;
	hEvent[1] = m_hKillEvent;

	while(1)
	{
		DWORD dwResult = WaitForMultipleObjects(2, hEvent, FALSE, 500);

		if(dwResult == WAIT_OBJECT_0 + 1)
			break;

		while(GetCommandCount() > 0)
		{
			//GetHead로 가져왔다가, CMD가 그 사이에 종료를 하면, 리스트에서 제외된다.
			CMkCommand *pCmd = GetHeadCommand();

			if(pCmd && HasRefCommand(pCmd))
			{		
				__try
				{
					BOOL bRet = pCmd->Execute(this);
					if(bRet)
					{
						m_pDBT->PostThreadMessage(WM_DISPLAY_BAR_PROGRESS, (WPARAM)&m_dbpiBasic, 1);
						bRet = pCmd->GetRecordset()->Parser();
					}

					pCmd->SetThreadRunningResult(bRet);
				}
				__except(EXCEPTION_EXECUTE_HANDLER)
				{
					m_bShownErrorDialog = TRUE;
					m_pDBT->PostThreadMessage(WM_DISPLAY_BAR_HIDE, (WPARAM)&m_dbpiBasic, 1);
					MessageBox("쿼리 실행중에 오류가 발생했습니다.\n재시도 하시기 바랍니다.", "확인", 
								MB_ICONINFORMATION);
					m_bShownErrorDialog = FALSE;

					//실행중에 CMD가 종료되는지를 확인하여, 살아 있으면 리턴처리하고, 아니면 그냥 둔다. 
					if(HasRefCommand(pCmd))
						pCmd->SetThreadRunningResult(FALSE);
				}
			}

			//실행이 완료된 CMD를 삭제한다. 
			if(this)
				RemoveHeadCommand();
		}
	}

	m_bAliveRunningThread = FALSE;

	return 0;
}


void CMkDatabase::RunThread(CMkCommand *pCmd)
{
	if(!m_bAliveRunningThread)
	{
		DWORD dwThreadID;
		HANDLE hHandle = ::CreateThread(NULL, 0, 
			(LPTHREAD_START_ROUTINE) staticRunningProc, 
			(LPVOID) this, 0, &dwThreadID);
		CloseHandle(hHandle);
	}

	AddCommand(pCmd);
	SetEvent(m_hRunningEvent);
}


void CMkDatabase::SetLog(CBanaLog* pLog)
{
	if(pLog)
	{
		if(!m_bSetExternalLog)
		{
			if(m_pLog)
				delete m_pLog;
		}

		m_pLog = pLog;
		m_bSetExternalLog = TRUE;
	}
	else
	{
		if(!m_pLog)
			m_pLog = new CBanaLog;
	}
}

BOOL CMkDatabase::CopyDatabase(CMkDatabase **pMkDb, BOOL bJustConnect)
{
	(*pMkDb) = new CMkDatabase(m_pLog);
	(*pMkDb)->SetServerKey(m_nServerKey, TRUE);
	(*pMkDb)->SetDeveloperMode(m_bDeveloperMode);

	for(int i = 0; i < m_sl.GetCount(); i++)
	{
		SERVER_ADDR_INFO info = m_sl.GetAt(i);
		(*pMkDb)->AddDisServer(info.strServerAddr, info.nServerPort);
	}

	return bJustConnect ? (*pMkDb)->Open(m_strServerAddress, m_nHostPort, TRUE) : TRUE;
}

void CMkDatabase::SetEnteringCmd(CMkCommand *pCmd)
{
	CMkLock lock(m_csEnteringCmd);
	m_pEnteringCmd = pCmd;
}

CMkCommand* CMkDatabase::GetEnteringCmd()
{
	CMkLock lock(m_csEnteringCmd);
	return m_pEnteringCmd;
}

void CMkDatabase::SetLastRecordsetChunk(CHAR* pChunk, UINT nSize)
{
	m_pLastRecordsetChunk = pChunk;
	m_nLastReccordsetSize = nSize;
}

CMkCommand *CMkDatabase::GetHeadCommand()
{
	CMkLock lock(m_csCommand);

	if(m_lstCommand.GetCount() > 0)
		return m_lstCommand.GetHead();
	else 
		return NULL;
}

void CMkDatabase::RemoveHeadCommand()
{
	CMkLock lock(m_csCommand);
	m_lstCommand.RemoveHead();
}

void CMkDatabase::AddCommand(CMkCommand *pCmd)
{
	CMkLock lock(m_csCommand);
	m_lstCommand.AddTail(pCmd);
}

int CMkDatabase::GetCommandCount() 
{
	CMkLock lock(m_csCommand);
	return m_lstCommand.GetCount();
}

void CMkDatabase::RemoveRefCommand(CMkCommand *pCmd)
{
	CMkLock lock(m_csRefCommand);
	m_mapRefCommand.erase(pCmd);
}

void CMkDatabase::AddRefCommand(CMkCommand *pCmd)
{
	CMkLock lock(m_csRefCommand);
	m_mapRefCommand[pCmd] = pCmd;
}

BOOL CMkDatabase::HasRefCommand(CMkCommand *pCmd)
{
	CMkLock lock(m_csRefCommand);
	COMMAND_MAP::iterator it = m_mapRefCommand.find(pCmd);
	return it != m_mapRefCommand.end();
}
