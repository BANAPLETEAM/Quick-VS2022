#pragma once

#define SOCKET UINT

class CStreamSocketSystem
{
public:
	CStreamSocketSystem();
	~CStreamSocketSystem();
	BOOL Initialised() {return m_bStatus;};
private:
	BOOL m_bStatus;
};

// The main socket class
class CStreamSocket
{
public:
	CStreamSocket();
	virtual ~CStreamSocket();

public:
	BOOL Create();
	BOOL Shutdown();
	BOOL Close();
	BOOL Bind(const UINT m_nPort);
	BOOL Connect(const CString address, const UINT m_nPort);
	BOOL Listen();
	CStreamSocket *Accept();
	char* GetPeerName();
	char* GetSockName();
	static LONG Resolve(const CString strName); //convert DNS name to IP address
	BOOL SetTimeOut(int nSecs);	//read/write timeout 
	void SetConnTimeOut(LONG nSecs) { m_nConnTimeOut = nSecs; }	//connect timeout
	BOOL IsDataTransferError(BOOL bReset = TRUE);

	virtual int Send(const char *szBuff, const UINT nBuffLen);
	virtual int Read(char *szBuff, const UINT nBuffLen);
	virtual BOOL SendCommand(UINT nType, UINT nSubType = 0, UINT nData = 0, UINT nPacketSeq = 0, BYTE nTranID = 0);		//정의된 명령어를 보내는 함수
	virtual BOOL SendData(UINT nType, UINT nSubType, char* data, UINT nData = 0, UINT nPacketSeq = 0, BYTE nTranID = 0);   //정의된 명령어+데이터를 보내는 함수
	virtual BOOL SendBinary(UINT nType, UINT nSubType, void* data, UINT nLen, UINT nData = 0, UINT nPacketSeq = 0, BYTE nTranID = 0, BOOL bHasNextPacket = 0); //바이너리 데이터 전송 함수	
	virtual char* RecvPacket(UINT &nType, UINT &nSubType, DWORD &dwSize, UINT &nData, UINT &nPacketSeq, 
							BOOL &bHasNextPacket, DWORD &dwOverRead, char **pOverRead, BYTE *pnTranID = NULL);

	BOOL SendExact(const char *buff, const UINT bufflen);
	BOOL ReadExact(char *buff, const UINT bufflen);
	void SetParentWnd(HWND hParent) { m_hParent = hParent;}
	BOOL IsConnected() { return m_bConnected;}
	BOOL AsyncSelect(UINT nEvent);
	SOCKET GetSocket() { return m_Socket;}
	BOOL IsValidSocket();
	BOOL SendStream(class CStreamPacket *pso);
	BOOL SendStream(UINT nType, UINT nSubType, char *szData, UINT nData, UINT nTranID);

	CString GetErrorMessage(DWORD dwError);
	CString WSAErrorCode2Text(DWORD dw);

protected:
	BOOL WaitWouldBlock();
	UINT GetTranID();

	SOCKET m_Socket;	      
	UINT m_nConnTimeOut;
	BOOL m_bConnTimeOut;		//connect timeout
	BOOL m_bConnected;
	HWND m_hParent;
	BOOL m_bDataTransferError;
	volatile LONG m_nTranID;
};

