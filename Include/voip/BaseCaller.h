#pragma once
class CVTSocket;
//class CTSocketSystem;

#include "VoicePacket.h"
BOOL GetOptionString(CString sOptionSet,CString sOption,CString& sRetVal);

class CBaseCaller
{
public:
	CBaseCaller(void);
	~CBaseCaller(void);

public:
	CString GetHost()
	{
		return m_strHost;
	}

	BOOL Connect(CString sHost,UINT uPort,CString sArg,int nType);
	BOOL ConnectSocket(CVTSocket& tSocket,CString sHost, UINT uPort,CString sArg,int nType);
	void Close();
	BOOL IsShutDown() { return m_bShutDown; }
	BOOL IsConnected() ;

	virtual void onConnected()=0; 		//접속이 이루어 졌을떄
	virtual void onDisConnected()=0;		//접속이 끓겼을경우
	virtual void onError(int nCode,CString sError)=0;
	virtual void onTextData(LPVTMSG  p)=0;
	virtual void onVoiceData(LPVTMSG p)=0;

	//socket thread
	static int staticSocketRead(CBaseCaller *app)
	{ return app->SocketRead((LPVOID)app); }
	UINT SocketRead(LPVOID lParam);
	void SocketReadImpl();

	BOOL SendData(UINT ucCmd, UINT ucMsgType, const char* data);
	BOOL SendBinary(UINT ucCmd, UINT ucMsgType, void* data, UINT nLen);
	BOOL SendData(UINT ucCmd, UINT ucMsgType,const char* szTo, const char* data);
	BOOL SendBinary(UINT ucCmd, UINT ucMsgType,const char* szTo, void* data, UINT nLen);


protected:
	HANDLE m_hKillEvent;
	HANDLE m_hCloseEvent;
	HANDLE m_hRecvEvent;
	DWORD  m_dwThreadID;

private:
	CString		m_strHost;
	UINT		m_uPort;
	CString		m_sArg;
	int			m_nType;
	BOOL		m_bShutDown;
	CVTSocket*	m_pSocket;

	void WaitForServerSignal(CVTSocket& socket);
};
