
#ifndef _QSOCKET_H_
#define _QSOCKET_H_


#include "QPacket.h"
#include <winsock2.h>


class CQSocket;



//General status
#define P_SUCCESS			0
#define P_SOCKET_ERROR		-1
#define P_FAILED			1

#define GRACEFUL_CLOSE	20000
#define WM_ASYNC_EVENT	(WM_USER + 101)

#define SOCKET UINT

// Create one or more QSocketSystem objects per application
class CQSocketSystem
{
public:
	CQSocketSystem();
	~CQSocketSystem();
	BOOL Initialised() {return m_bStatus;};
private:
	BOOL m_bStatus;
};

// The main socket class
class CQSocket
{
public:
	CQSocket();
	virtual ~CQSocket();

public:
	BOOL Create();
	BOOL Shutdown();
	BOOL Close();
	BOOL Bind(const UINT m_nPort);
	BOOL Connect(const CString address, const UINT m_nPort);
	BOOL Listen();
	CQSocket *Accept();
	char* GetPeerName();
	char* GetSockName();
	static LONG Resolve(const CString strName); //convert DNS name to IP address
	BOOL SetTimeOut(LONG nSecs);	//read/write timeout 
	void SetConnTimeOut(LONG nSecs) { m_nConnTimeOut = nSecs; }	//connect timeout
	BOOL IsDataTransferError(BOOL bReset = TRUE);

	//일반 Send/Read 함수
	virtual int Send(const char *szBuff, const UINT nBuffLen);
	virtual int Read(char *szBuff, const UINT nBuffLen);

	//확장 Send/Read 함수
	virtual BOOL SendExact(const char *buff, const UINT bufflen);
	virtual BOOL ReadExact(char *buff, const UINT bufflen);
	virtual char* ReadStream();	//패킷에서 사이즈를 추출해서 해당 사이즈만큼만 읽는 함수
	virtual char* ReadStream2(long &nRealRecvLen);	//패킷에서 사이즈를 추출해서 해당 사이즈만큼만 읽는 함수
	virtual BOOL SendCommand(UINT nType, UINT nSubType = 0);		//정의된 명령어를 보내는 함수
	virtual BOOL SendData(UINT nType, UINT nSubType, char* data);   //정의된 명령어+데이터를 보내는 함수
	virtual BOOL SendBinary(UINT nType, UINT nSubType, void* data, UINT nLen); //바이너리 데이터 전송 함수	
	virtual int WaitOK();		//응답을 기다리는 함수, [RET] OK : P_SUCESS


	void SetParentWnd(HWND hParent) { m_hParent = hParent;}
	BOOL IsConnected() { return m_bConnected;}

	BOOL AsyncSelect(UINT nEvent);
	SOCKET GetSocket() { return m_Socket;}
	BOOL IsValidSocket();

protected:
	SOCKET m_Socket;	      

	UINT m_nConnTimeOut;
	BOOL m_bConnTimeOut;		//connect timeout

	BOOL m_bConnected;
	HWND m_hParent;
	BOOL m_bDataTransferError;
};

#endif //_QSOCKET_H_
