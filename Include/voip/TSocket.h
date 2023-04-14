class CVTSocket;


#ifndef _TSOCKET_H_
#define _TSOCKET_H_


//General status
#define P_SUCCESS			0
#define P_SOCKET_ERROR		-1
#define P_FAILED			1

#define GRACEFUL_CLOSE	20000
#define WM_ASYNC_EVENT	(WM_USER + 101)

#define SOCKET UINT

typedef struct{
	CVTSocket* tSocket;
	UINT	nType;
	UINT	nSubType;
	CString data;
} TSOCKET_SEND_DATA;

/*
// Create one or more QSocketSystem objects per application
class CTSocketSystem
{
public:
	CTSocketSystem();
	~CTSocketSystem();
	BOOL Initialised() {return m_bStatus;};
//public:
private:
	BOOL m_bStatus;
};
*/

// The main socket class
class CVTSocket
{
public:
	CVTSocket();
	CVTSocket(HWND hParent);
	virtual ~CVTSocket();

public:
	BOOL Create();
	BOOL Shutdown();
	BOOL Close();
	BOOL Bind(const UINT m_nPort);
	BOOL Connect(const CString address, const UINT m_nPort);
	BOOL Listen();
	CVTSocket *Accept();
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
	virtual BOOL ReadExact(char *buff, const UINT bufflen,int &nError);

	char* ReadStream(int &nError);
	BOOL SendData(UINT ucCmd, UINT ucMsgType, const char* data);
	BOOL SendBinary(UINT ucCmd, UINT ucMsgType, void* data, UINT nLen); //바이너리 데이터 전송 함수	
	BOOL SendData(UINT ucCmd, UINT ucMsgType, const char* sToID,const char* data);
	BOOL SendBinary(UINT ucCmd, UINT ucMsgType, const char* sToID,void* data, UINT nLen); //바이너리 데이터 전송 함수	

	BOOL IsClose();
	BOOL IsConnected() { return m_bConnected;}

	void SetParentWnd(HWND hParent) { m_hParent = hParent;}
	SOCKET GetSocket() { return m_Socket; }

	unsigned char nPlainText32[33];

	void	SetID(CString sID) {m_sID = sID;}
	CString GetID() {return m_sID;}
	void	SetCompany(int nCompany) {m_nCompany = nCompany;}
	int		GetCompany() {return m_nCompany;}

	void	SetRNo(int nRNo) {m_nRNo = nRNo;}
	int		GetRNo() {return m_nRNo;}

	void	SetShareCode1(int nShareCode1) {m_nShareCode1 = nShareCode1;}
	int		GetShareCode1() {return m_nShareCode1;}


protected:
	SOCKET m_Socket;	
	UINT m_nConnTimeOut;
	BOOL m_bConnTimeOut;		//connect timeout
	BOOL m_bConnected;
	
	HWND m_hParent;
	CCriticalSection m_cs;

	CString m_sID;
	int		m_nCompany;
	int		m_nRNo;
	int		m_nShareCode1;
};

#endif //_QSOCKET_H_
