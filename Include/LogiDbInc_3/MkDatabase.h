#pragma once


extern "C" {
#include "d3des.h"
}

extern BYTE serverkey[8];

#include "QPacket.h"
#include <afxtempl.h>
#include <Afxmt.h>
#include "DisplayBarThread.h"
#include <map>

using namespace std;

class CMkCommand;
class CBanaLog;

typedef struct 
{
	CString strServerAddr;
	UINT nServerPort = 0;
} SERVER_ADDR_INFO;

typedef CArray<SERVER_ADDR_INFO, SERVER_ADDR_INFO> SERVER_LIST;
typedef CList<CMkCommand*, CMkCommand*> COMMAND_LIST;
typedef map<CMkCommand*, CMkCommand*> COMMAND_MAP;


enum ERROR_MSG_TYPE { EMT_NORMAL = 0, EMT_SIMPLE = 1, EMT_NO_SHOW = 2};

class CQueryLogDlg;

// CMkDatabase
class CQSocket;
#define SOCKET UINT
class AFX_EXT_CLASS CMkDatabase : public CWnd
{
	DECLARE_DYNAMIC(CMkDatabase)

public:
	CMkDatabase(CBanaLog* pLog = NULL);
	virtual ~CMkDatabase();

	CQSocket *GetSocket();

protected:
	CQSocket* m_Socket;
	CString m_strServerAddress;
	UINT m_nHostPort;
	UINT m_bLiveThread;

	HANDLE m_hKillEvent;
	CCriticalSection m_csLock;

	CString m_strClientCode;
	CString m_strClientInfoPacket;

	UINT m_nAsyncMode;
	HWND m_hParentWnd;
	BOOL m_bMessenger;
	BOOL m_bShownErrorDialog;

	MSG_LOGIN_INFO m_LoginInfo;

	long m_nSend;
	int m_nErrorMsgType;

	DWORD m_dwActiveTime;
	BOOL m_bEnableSleepMode;
	BOOL m_bSleepState;
	BYTE m_nXorKey;
	BYTE m_nServerKey[8];
	BOOL m_bDeveloperMode; 
	SERVER_LIST m_sl;
	CString m_strServerName;
	BOOL m_bTransferWithoutAck;

	BOOL m_bAliveRunningThread;
	BOOL m_bAliveUIThread;
	HANDLE m_hRunningEvent;
	HANDLE m_hUIEvent;
	BOOL m_bUserStop;

	DWORD m_dwCurSize;
	DWORD m_dwElapsedTime;
	DWORD m_dwTotalSize;
	COMMAND_LIST m_lstCommand;
	CString m_strLastQueryInfo;
	CMkCommand *m_pEnteringCmd;
	CCriticalSection m_csEnteringCmd;
	CCriticalSection m_csCommand;
	CHAR *m_pLastRecordsetChunk;
	UINT m_nLastReccordsetSize;

public:
	CDisplayBarThread *m_pDBT;
	CCriticalSection m_csQuery;
	static CQueryLogDlg *m_pQueryLogDlg;
	static BOOL m_bSetExternalLog;
	static volatile long m_nRefCount;
	static CBanaLog* m_pLog;
	static CDisplayBarProgressInfo m_dbpiBasic;
	static COMMAND_MAP m_mapRefCommand;
	static CCriticalSection m_csRefCommand;

	BOOL m_bDisplayBarCreate;

protected:
	DECLARE_MESSAGE_MAP()

	LONG OnAsyncEvent(SOCKET wSocket, LPARAM lParam);
	void OnDataRead(void* p);

	static int staticConnectTestProc(CMkDatabase *app)
		{ return app->ConnectTestProc((LPVOID)app); }

	static int staticRunningProc(CMkDatabase *app)
	{ return app->RunningProc((LPVOID)app); }

	void GetNextServerAddr();
	LPVOID _Execute(int *pnType, LPVOID buf, UINT *pnSize, CString &strCommand, int &nErrorCode);
	LPVOID _ExecuteCommand(UINT &nType, UINT &nSubType, UINT &nSize, char *szPacket, int &nErrorCode);

	void ResetRefCommandDB();

public:
	void AddDisServer(CString strServerAddr, UINT nServerPort);
	void RemoveDisServer();
	void SetServerName(CString strServerName);
	BOOL ConnectServer(BOOL bSecondRun = FALSE);
	UINT ConnectTestProc(LPVOID lParam);
	BOOL Open(CString strHostAddress, UINT nHostPort, BOOL bJustConnect = TRUE);
	LPVOID Execute(int *pnType, LPVOID buf, UINT *pnSize, CString &strCommand);
	LPVOID ExecuteCommand(UINT &nType, UINT &nSubType, UINT &nSize, char *szPacket = NULL);

	void SetClientCode(CString strClientCode);
	void SetClientInfo(long nCompanyCode, long nWNo, BOOL bDeveloper);

	UINT AsyncSelect(UINT nMode, BOOL bJustRun = FALSE);
	void SetParentWnd(HWND hParentWnd);
	void ClientType(BOOL bMessenger);
	void SetLoginInfo(MSG_LOGIN_INFO *pInfo);

	BOOL MessengerLogin();
	void SetSeatAway(BOOL bEmpty);
	void Close(); 

	BOOL IsShownErrorDialog();
	BOOL UploadFile(CString strFileName, char *pBuffer, long nLength);
	long GetSendSize();
	BOOL UploadFileWithDlg(CString strFileName, char *pBuffer, DWORD nLength);

	void SetErrorMsgType(int nType);
	void EnableSleepMode(BOOL bSleep);
	void MakeRandomByte(BYTE &nByte);
	BYTE GetXorKey() { return m_nXorKey;}
	void SetServerKey(BYTE nServerKey[8], BOOL bPlain = FALSE);
	void SetDeveloperMode(BOOL bDeveloperMode);
	BOOL GetDeveloperMode();
	void ShowQueryLog();
	CQueryLogDlg* GetQueryLogDlg();
	CString GetCurServerAddr();
	UINT GetCurServerPort();
	void SetTransferWithoutAck(BOOL bWithoutAck);
	void RunThread(CMkCommand *pCmd);
	UINT RunningProc(LPVOID lParam);
	UINT UIProc(LPVOID lParam);
	void SetUserStop(BOOL bUser = TRUE);
	BOOL IsUserStop();
	void SetUIEvent();
	void GetProgressInfo(DWORD &dwCurSize, DWORD &dwTotalSize, DWORD &dwElapsedTime);
	void SetLog(CBanaLog* pLog);
	CBanaLog* GetLog();
	CDisplayBarThread* GetDisplayBarThread();
	BOOL CopyDatabase(CMkDatabase **pMkDb, BOOL bJustConnect = TRUE);
	void SetLastQueryInfo(CString &strInfo);
	CString GetLastQueryInfo();
	void SetEnteringCmd(CMkCommand *pCmd);
	CMkCommand *GetEnteringCmd();
	void SetLastRecordsetChunk(CHAR* pChunk, UINT nSize);
	CHAR *GetLastRecordsetChunk() { return m_pLastRecordsetChunk; }
	UINT GetLastRecordsetSize() { return m_nLastReccordsetSize; }

	CMkCommand *GetHeadCommand();
	void RemoveHeadCommand();
	void AddCommand(CMkCommand *pCmd);
	int GetCommandCount();
	static void RemoveRefCommand(CMkCommand *pCmd);
	static void AddRefCommand(CMkCommand *pCmd);
	static BOOL HasRefCommand(CMkCommand *pCmd);
};



AFX_INLINE CQSocket* CMkDatabase::GetSocket() 
{ 
	return m_Socket; 
}

AFX_INLINE void CMkDatabase::SetClientCode(CString strClientCode)
{ 
	m_strClientCode = strClientCode; 
}

AFX_INLINE void CMkDatabase::SetParentWnd(HWND hParentWnd) 
{ 
	m_hParentWnd = hParentWnd; 
}

AFX_INLINE void CMkDatabase::ClientType(BOOL bMessenger) 
{ 
	m_bMessenger = bMessenger; 
}

AFX_INLINE void CMkDatabase::SetLoginInfo(MSG_LOGIN_INFO *pInfo) 
{ 
	memcpy(&m_LoginInfo, pInfo, sizeof(MSG_LOGIN_INFO));
}

AFX_INLINE void CMkDatabase::SetDeveloperMode(BOOL bDeveloperMode)
{
	m_bDeveloperMode = bDeveloperMode;
}

AFX_INLINE BOOL CMkDatabase::GetDeveloperMode()
{
	return m_bDeveloperMode;
}

AFX_INLINE BOOL CMkDatabase::IsShownErrorDialog() 
{ 
	return m_bShownErrorDialog;
}

AFX_INLINE long CMkDatabase::GetSendSize()
{
	return m_nSend; 
}

AFX_INLINE void CMkDatabase::SetErrorMsgType(int nType) 
{ 
	m_nErrorMsgType = nType; 
}

AFX_INLINE void CMkDatabase::EnableSleepMode(BOOL bSleep) 
{
	m_bEnableSleepMode = bSleep; 
}

AFX_INLINE CQueryLogDlg* CMkDatabase::GetQueryLogDlg()
{
	return m_pQueryLogDlg;
}

AFX_INLINE void CMkDatabase::SetServerName(CString strServerName)
{
	m_strServerName = strServerName;
}

AFX_INLINE void CMkDatabase::RemoveDisServer()
{
	m_sl.RemoveAll();
}

AFX_INLINE CString CMkDatabase::GetCurServerAddr()
{
	return m_strServerAddress;
}

AFX_INLINE UINT CMkDatabase::GetCurServerPort()
{
	return m_nHostPort;
}

AFX_INLINE void CMkDatabase::SetTransferWithoutAck(BOOL bWithoutAck)
{
	m_bTransferWithoutAck = bWithoutAck;
}

AFX_INLINE void CMkDatabase::SetUserStop(BOOL bUser)
{
	m_bUserStop = bUser;
}

AFX_INLINE BOOL CMkDatabase::IsUserStop()
{
	return m_bUserStop;
}

AFX_INLINE void CMkDatabase::SetUIEvent()
{
	SetEvent(m_hUIEvent);
}

AFX_INLINE void CMkDatabase::GetProgressInfo(DWORD &dwCurSize, DWORD &dwTotalSize, DWORD &dwElapsedTime)
{
	dwCurSize = m_dwCurSize;
	dwTotalSize = m_dwTotalSize;
	dwElapsedTime = m_dwElapsedTime;
}

AFX_INLINE CBanaLog* CMkDatabase::GetLog()
{
	return m_pLog;
}

AFX_INLINE CDisplayBarThread* CMkDatabase::GetDisplayBarThread()
{
	return m_pDBT;	
}
 
AFX_INLINE void CMkDatabase::SetLastQueryInfo(CString &strInfo)
{
	m_strLastQueryInfo = strInfo;
}

AFX_INLINE CString CMkDatabase::GetLastQueryInfo()
{
	return m_strLastQueryInfo;
}
