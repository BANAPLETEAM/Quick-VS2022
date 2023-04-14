
 
class CTSocket;

/*
#ifndef _QSOCKET_H_
#define _QSOCKET_H_
*/


//General status
#define P_SUCCESS			0
#define P_SOCKET_ERROR		-1
#define P_FAILED			1

#define GRACEFUL_CLOSE	20000
#define WM_ASYNC_EVENT	(WM_USER + 101)

#define SOCKET UINT

// Create one or more QSocketSystem objects per application
class CTSocketSystem
{
public:
	CTSocketSystem();
	~CTSocketSystem();
	BOOL Initialised() {return m_bStatus;};
private:
	BOOL m_bStatus;
};

// The main socket class
class CTSocket
{
public:
	CTSocket();
	CTSocket(HWND hParent);
	virtual ~CTSocket();

public:
	BOOL Create();
	BOOL Shutdown();
	BOOL Close();
	BOOL Bind(const UINT m_nPort);
	BOOL Connect(const CString address, const UINT m_nPort);
	BOOL Listen();
	CTSocket *Accept();
	char* GetPeerName();
	char* GetSockName();
	static LONG Resolve(const CString strName); //convert DNS name to IP address
	BOOL SetTimeOut(LONG nSecs);	//read/write timeout 
	void SetConnTimeOut(LONG nSecs) { m_nConnTimeOut = nSecs; }	//connect timeout

	//일반 Send/Read 함수
	virtual int Send(const char *szBuff, const UINT nBuffLen);
	virtual int Read(char *szBuff, const UINT nBuffLen);

	//확장 Send/Read 함수
	virtual BOOL SendExact(const char *buff, const UINT bufflen);
	virtual BOOL ReadExact(char *buff, const UINT bufflen);

	char* ReadStream(int &nError);
	BOOL SendData(UINT nType, UINT nSubType, char* data);
	BOOL SendBinary(UINT nType, UINT nSubType, void* data, UINT nLen);
	BOOL IsClose();

	void SetParentWnd(HWND hParent) { m_hParent = hParent;}
	SOCKET GetSocket() { return m_Socket; }

	BOOL IsConnected() { return m_bConnected;}

protected:
	SOCKET m_Socket;	
	UINT m_nConnTimeOut;
	BOOL m_bConnTimeOut;		//connect timeout

	BOOL m_bConnected;
	
	HWND m_hParent;
};

//#endif //_QSOCKET_H_
