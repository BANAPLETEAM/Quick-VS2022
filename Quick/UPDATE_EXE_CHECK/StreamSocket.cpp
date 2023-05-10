//CStreamSocket.cpp

#include "stdafx.h"
#include <stdio.h>
#include <io.h>
#include <sys/types.h>

#include "StreamSocket.h"
#include "StreamPacket.h"
#include "LogiFunc.h"

#ifndef _APPCLIENT
#include "UpdateDef.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define READSTREAMLENGTH	16383
#define EXPANDSIZE			163830 //16384 

////////////////////////////////////////////////////////
// CStreamSocket implementation


static WORD winsockVersion = 0;

CStreamSocketSystem::CStreamSocketSystem()
{
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 0);
	if(WSAStartup(wVersionRequested, &wsaData) != 0)
	{
		m_bStatus = false;
		return;
	}
		
	winsockVersion = wsaData.wVersion;
	m_bStatus = true;
}

CStreamSocketSystem::~CStreamSocketSystem()
{
	if(m_bStatus)
		WSACleanup();
}



CStreamSocket::CStreamSocket()
{
	m_Socket = -1;
	m_hParent = NULL;
	m_bConnected = FALSE;
	m_bDataTransferError = FALSE;
	m_nTranID = 0;
}



CStreamSocket::~CStreamSocket()
{
	Close();
}



BOOL CStreamSocket::Create()
{
	const int one = 1;
	
	//Check that the old socket was closed
	if(IsValidSocket())
		Close();
	
	//Create the socket
	if((m_Socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return false;
	
	if(setsockopt(m_Socket, IPPROTO_TCP, TCP_NODELAY, (char *)&one, sizeof(one)))
		return false;

	return true;
}


BOOL CStreamSocket::Close()
{
	//mkLog.Print("socket close\n");

	if(IsValidSocket())
    {
		linger lval;
		int	vlen;
		int	rc;

		lval.l_onoff	= 1;
		lval.l_linger	= 2;
		vlen = sizeof( lval );
		rc = setsockopt(m_Socket, SOL_SOCKET, SO_LINGER, (const char*) &lval, vlen );
		if ( rc != 0 ) return FALSE;

		closesocket(m_Socket);
		m_Socket = -1;
		m_bConnected = FALSE;

		//mkLog.Print("closing socket\n");
    }

	return true;
}


BOOL CStreamSocket::Shutdown()
{
	if(IsValidSocket())
    {
		
		//mkLog.Print("shutdown socket\n");
		shutdown(m_Socket, SD_BOTH);
		m_bConnected = FALSE;
    }

	return true;
}



BOOL CStreamSocket::Bind(const UINT m_nPort)
{
	struct sockaddr_in addr;
	
	//Check that the socket is open!
	if (!IsValidSocket())
		return false;
	
	//Set up the address to bind the socket to
	addr.sin_family = AF_INET;
	addr.sin_port = htons(m_nPort);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	// And do the binding
	if (::bind(m_Socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		return false;
	
	return true;
}


//TimeOut connect
BOOL CStreamSocket::Connect(const CString address, const UINT m_nPort)
{
	m_bConnTimeOut=FALSE;

	//Check the socket
	if (!IsValidSocket())
		return false;
	
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(address);
		
	//Was the string a valid IP address?
	if (addr.sin_addr.s_addr == -1)
    {
		struct hostent *pHost;
		pHost = gethostbyname(address);
		if (pHost != NULL)
		{
			if (pHost->h_addr == NULL)
				return false;
			addr.sin_addr.s_addr = ((struct in_addr *)pHost->h_addr)->s_addr;
		}
		else
			return false;
    }
	
	addr.sin_port = htons(m_nPort);

	//Nonblocking 모드로 세팅한다.
	u_long nonblocking = 1;

	if(ioctlsocket(m_Socket, FIONBIO, &nonblocking))
		return FALSE;

	fd_set fdwrite;
	struct timeval t;
	fdwrite.fd_count = 1;
	fdwrite.fd_array[0] = m_Socket;
	memset((char *)&t, 0, sizeof(t));
	t.tv_sec = m_nConnTimeOut;
	t.tv_usec = 0;

	m_bConnected = FALSE;
	if(SOCKET_ERROR == connect(m_Socket, (struct sockaddr *)&addr, sizeof addr))
	{
		if(WSAGetLastError() == WSAEWOULDBLOCK)
		{
			int sr = select(0, NULL, &fdwrite, NULL, &t);
			if(sr == 1) m_bConnected = TRUE;
			else m_bConnTimeOut = TRUE;
		}
		else 
		{
			shutdown(m_Socket, SD_BOTH);
			closesocket(m_Socket);
		}
	}
	else
	{
		m_bConnected = TRUE;
	}

	nonblocking = 0;
	if(ioctlsocket(m_Socket, FIONBIO, &nonblocking))
	{
		shutdown(m_Socket, SD_BOTH);
		closesocket(m_Socket);
		return FALSE;
	}

	DWORD TimeOut = 5000;
	setsockopt(m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&TimeOut, sizeof(TimeOut));

/*
	if(m_hParent != NULL)
		AsyncSelect(FD_CLOSE | FD_READ | FD_CONNECT);
*/

	return m_bConnected;
}	


CString CStreamSocket::WSAErrorCode2Text(DWORD dw)
{
	CString error = "";
	// Put your own common error text here (give more explaination etc..) 
	switch (dw)
	{
	case WSAEFAULT:
		error = "WSAEFAULT	The buf parameter is not completely contained in a valid part of the user address space.";
		break;
	case WSAENOTCONN:
		error = "WSAENOTCONN	The socket is not connected.";
		break;
	case WSAEINTR:
		error = "WSAEINTR	The (blocking) call was canceled through WSACancelBlockingCall.	";
		break;
	case WSAENOTSOCK:
		error = " WSAENOTSOCK	The descriptor s is not a socket.";
		break;
	case WSANOTINITIALISED:
		error = "WSANOTINITIALISED: A successful WSAStartup call must occur before using this function.";
		break;
	case WSAENETDOWN:
		error = "WSAENETDOWN	The network subsystem has failed.";
		break;
	case WSAEINPROGRESS:
		error = "WSAEINPROGRESS	A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.";
		break;
	case WSAENETRESET:
		error = " WSAENETRESET	The connection has been broken due to the keep-alive activity detecting a failure while the operation was in progress.";
		break;
	case WSAEOPNOTSUPP:
		error = "WSAEOPNOTSUPP	MSG_OOB was specified, but the socket is not stream-style such as type SOCK_STREAM, OOB data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only send operations.	";
		break;
	case WSAESHUTDOWN:
		error = "WSAESHUTDOWN	The socket has been shut down; it is not possible to receive on a socket after shutdown has been invoked with how set to SD_RECEIVE or SD_BOTH.";
		break;
	case WSAEWOULDBLOCK:
		error = " WSAEWOULDBLOCK	The socket is marked as nonblocking and the receive operation would block.	";
		break;
	case WSAEMSGSIZE:
		error = " WSAENOTSOCK		The message was too large to fit into the specified buffer and was truncated.";
		break;
	case WSAEINVAL:
		error = "WSAEINVAL	The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled or (for byte stream sockets only) len was zero or negative.	";
	case WSAECONNABORTED:
		error = " 	WSAECONNABORTED	The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable.";
		break;
	case WSAETIMEDOUT:
		error = "WSAETIMEDOUT	The connection has been dropped because of a network failure or because the peer system failed to respond.	";
		break;
	case WSAECONNRESET:
		//error="WSAECONNRESET	The virtual circuit was reset by the remote side executing a hard or abortive close."; 
		error = "WSAECONNRESET Connection dropped..";
		break;

	default:
		error = "";
		break;
	}

	// Use system format..  
	if (error.IsEmpty())
		return GetErrorMessage(dw);

	return error;
}


CString CStreamSocket::GetErrorMessage(DWORD dwError)
{
	CString strError;
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		dwError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	if (lpMsgBuf)
	{
		strError.Format("%s", lpMsgBuf);
		LocalFree(lpMsgBuf);
	}
	else
	{
		strError = "알수없는에러";
	}

	return strError;
}

BOOL CStreamSocket::Listen()
{
	// Check socket
	if (!IsValidSocket())
		return false;
	
	// Set it to listen
	if (listen(m_Socket, SOMAXCONN) < 0)
		return false;
	
	return true;
}



CStreamSocket *CStreamSocket::Accept()
{
	
	const int one = 1;
	
	int new_socket_id;
	CStreamSocket * new_socket;
	
	//Check this socket
	if (!IsValidSocket())
		return NULL;
	
	//Accept an incoming connection
	if ((new_socket_id = accept(m_Socket, NULL, 0)) < 0)
		return NULL;
	 
	//Create a new CStreamSocket and return it
	new_socket = new CStreamSocket;
	if (new_socket != NULL)
    {
		new_socket->m_Socket = new_socket_id;
    }
	else
    {
		shutdown(new_socket_id, SD_BOTH);
		closesocket(new_socket_id);
    }
	
	//Attempt to set the new socket's options
	if(SOCKET_ERROR == setsockopt(new_socket->m_Socket, IPPROTO_TCP, TCP_NODELAY, (char *)&one, sizeof(one)))
	{
		shutdown(new_socket_id, SD_BOTH);
		closesocket(new_socket_id);
		return NULL;
	}

/*
	if(SOCKET_ERROR == WSAAsyncSelect(new_socket_id, m_hParent, WM_ASYNC_EVENT, FD_CLOSE))
	{
		shutdown(new_socket_id, SD_BOTH);
		closesocket(new_socket_id);
		return NULL;
	}
*/
	return new_socket;
}

char* CStreamSocket::GetPeerName()
{
	struct sockaddr_in	sockinfo;
	struct in_addr		address;
	int					sockinfosize = sizeof(sockinfo);
	char *name;
	
	//Get the peer address for the client socket
	getpeername(m_Socket, (struct sockaddr *)&sockinfo, &sockinfosize);
	memcpy(&address, &sockinfo.sin_addr, sizeof(address));
	
	name = inet_ntoa(address);
	if (name == NULL)
		return "<unavailable>";
	else
		return name;
}

char* CStreamSocket::GetSockName()
{
	struct sockaddr_in	sockinfo;
	struct in_addr		address;
	int					sockinfosize = sizeof(sockinfo);
	char *name;
	
	//Get the peer address for the client socket
	getsockname(m_Socket, (struct sockaddr *)&sockinfo, &sockinfosize);
	memcpy(&address, &sockinfo.sin_addr, sizeof(address));
	
	name = inet_ntoa(address);
	if (name == NULL)
		return "<unavailable>";
	else
		return name;
}

LONG CStreamSocket::Resolve(const CString address)
{
	LONG addr;
	
	//Try converting the address as IP
	addr = inet_addr(address);
	
	//Was it a valid IP address?
	if (addr == 0xffffffff)
    {
		//No, so get the actual IP address of the host name specified
		struct hostent *pHost;
		pHost = gethostbyname(address);
		if (pHost != NULL)
		{
			if (pHost->h_addr == NULL)
				return 0;
			addr = ((struct in_addr *)pHost->h_addr)->s_addr;
		}
		else
			return 0;
    }
	
	return addr;
}



BOOL CStreamSocket::SetTimeOut(int nSecs)
{
	if (LOBYTE(winsockVersion) < 2)
		return false;
	
	int timeout=nSecs * 1000;
	if (setsockopt(m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) == SOCKET_ERROR)
	{
		return false;
	}
	if (setsockopt(m_Socket, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout)) == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}



int CStreamSocket::Send(const char *buff, const UINT bufflen)
{
	int nRet = send(m_Socket, buff, bufflen, 0);
	//if(nRet < 0)
	//	mkLog.Print("Send: %s\n", WSAErrorCode2Text(WSAGetLastError()));
	
	return nRet;
}

BOOL CStreamSocket::SendExact(const char *buff, const UINT bufflen)
{
	return Send(buff, bufflen) == (int)bufflen;
}

int CStreamSocket::Read(char *buff, const UINT bufflen)
{
	return recv(m_Socket, buff, bufflen, 0);
}

BOOL CStreamSocket::ReadExact(char *buff, const UINT bufflen)
{
	int n;
	UINT currlen = bufflen;

	while (currlen > 0)
	{
		// Try to read some data in
		n = Read(buff, currlen);

		if (n > 0)
		{
			// Adjust the buffer position and size
			buff += n;
			currlen -= n;
		} 
		else if (n == 0) 
		{
			//mkLog.Print("zero bytes read\n");
			return false;
		} 
		else 
		{
			if(WSAGetLastError() != WSAEWOULDBLOCK)
			{
				//mkLog.Print("%s\n", WSAErrorCode2Text(WSAGetLastError()));
				return false;
			}
		}
	}

	return true;
}


char* CStreamSocket::RecvPacket(UINT &nType, UINT &nSubType, DWORD &dwSize, UINT &nData, UINT &nPacketSeq, 
								BOOL &bHasNextPacket, DWORD &dwOverRead, char **pOverRead, BYTE *pnTranID)
{
	char *pbuffer = *pOverRead ? *pOverRead : new char[READ_SIZE];
	UINT nReadSize = READ_SIZE;
	DWORD dwRead;
	int len = dwOverRead;
	BOOL bReadSkipOnce = FALSE;
	BYTE nTranID;

	try 
	{
		nType = dwRead = nSubType = nData = nPacketSeq = 0;
		dwSize = 0xFFFF;	//처음에 WOULDBLOCK 걸리는 경우, 루프 탈출방지

		if(dwOverRead >= STREAM_HEAD_SIZE)
		{
			bReadSkipOnce = TRUE;
			dwOverRead = 0;
			*pOverRead = NULL;
		}
		else if(dwOverRead > 0)
		{
			dwRead = dwOverRead;
			nReadSize = READ_SIZE - dwRead;
			dwOverRead = 0;
			*pOverRead = NULL;
		}

		do
		{
			if(bReadSkipOnce)
				bReadSkipOnce = FALSE;
			else
				len = Read(&pbuffer[dwRead], nReadSize);

			if(len < 0)
			{
				DWORD dwError = WSAGetLastError();
				if(dwError == WSAEWOULDBLOCK)
				{
					WaitWouldBlock();
					continue;
				}

				if(dwError == WSAETIMEDOUT)
					continue;

				//mkLog.Print("%s\n", WSAErrorCode2Text(dwError));
				//throw "read loop ERROR";
				nType = 0;
				delete[] pbuffer;
				return NULL;
			}

			dwRead += len;

			if(nType == 0)
			{
				UINT nHeadSize;

				if(len < STREAM_HEAD_SIZE)
				{
					nReadSize -= len;
					continue;
				}

				if(!(pbuffer[0] == 'Q' && pbuffer[1] == '\1'))
					throw "INVALID packet header";

				CStreamPacket *pso = (CStreamPacket*)pbuffer;
				dwSize = pso->m_nPacketSize;
				nType = pso->m_nType;
				nSubType = pso->m_nSubType;
				nData = pso->m_nData;
				nPacketSeq = pso->m_nPacketSeq;
				bHasNextPacket = pso->m_bHasNextPacket;
				nTranID = pso->m_nTranID;
				nHeadSize = STREAM_HEAD_SIZE;

				if(dwSize == 0)
				{
					dwRead -= nHeadSize;
					break;
				}
				else if(dwSize > READ_SIZE)
				{	
					char *pbuffer2 = new char[dwSize - nHeadSize];
					if(!pbuffer2) 
						throw "FAILED memory allocation";

					memcpy(pbuffer2, &pbuffer[nHeadSize], dwRead - nHeadSize);
					delete[] pbuffer;
					pbuffer = pbuffer2;
				}
				else
				{
					memcpy(pbuffer, &pbuffer[nHeadSize], dwRead - nHeadSize);
				}

				dwRead -= nHeadSize;
				dwSize -= nHeadSize;
			}

			nReadSize = min(dwSize - dwRead, READ_SIZE);

		} while(dwRead < dwSize);


		if(dwRead > dwSize)
		{		
			//붙어서 들어온 패킷 저장
			dwOverRead = dwRead - dwSize;
			*pOverRead = new char[READ_SIZE];
			memcpy(*pOverRead, &pbuffer[dwSize], dwOverRead);
		}

		if(pnTranID)
			*pnTranID = nTranID;

		return pbuffer;
	}
	catch(char *msg)
	{
		//mkLog.Print("RecvPacket: %s\n", msg);
		nType = 0;
	}

	//mkLog.Print("RecvPacket: return NULL\n");
	delete[] pbuffer;
	return NULL;
}

BOOL CStreamSocket::WaitWouldBlock()
{
	fd_set fdread;
	struct timeval t;
	fdread.fd_count = 1;
	fdread.fd_array[0] = m_Socket;
	memset((char *)&t, 0, sizeof(t));
	t.tv_sec = 1;
	t.tv_usec = 0;
	if(select(0, &fdread, NULL, NULL, &t) < 0)
		return FALSE;

	return TRUE;
}


BOOL CStreamSocket::SendCommand(UINT nType, UINT nSubType, UINT nData, UINT nPacketSeq, BYTE nTranID)
{
	CStreamPacket so;
	so.m_nPacketSize = sizeof(CStreamPacket);
	so.m_nType = nType;
	so.m_nSubType = nSubType;
	so.m_nTranID = nTranID;
	so.m_nData = nData;
	so.m_nPacketSeq = nPacketSeq;
	return SendExact((char*)&so,sizeof(CStreamPacket));
}

BOOL CStreamSocket::SendData(UINT nType, UINT nSubType, char* data, UINT nData, UINT nPacketSeq, BYTE nTranID)
{
	UINT nLen = strlen(data) + 1;

	CStreamPacket *pso = (CStreamPacket*)new char[sizeof(CStreamPacket) + nLen];
	pso->Init();	//new char 할당으로 하면 생성자 호출이 안되기 때문에 Init을 수동으로함
	pso->m_nPacketSize = sizeof(CStreamPacket) + nLen;
	pso->m_nType = nType;
	pso->m_nSubType = nSubType;
	pso->m_nTranID = nTranID;
	pso->m_nData = nData;
	pso->m_nPacketSeq = nPacketSeq;
	strcpy(pso->m_szData, data);

	//send the packet
	if(!SendExact((char*)pso, sizeof(CStreamPacket) + nLen))
	{
		m_bDataTransferError = TRUE;
		delete[] (char*)pso; 
		return FALSE;
	}

	delete[] (char*)pso;

	return TRUE;
}

BOOL CStreamSocket::SendBinary(UINT nType, UINT nSubType, void* data, UINT nLen, UINT nData, UINT nPacketSeq, BYTE nTranID, BOOL bHasNextPacket)
{
	CStreamPacket *pso = (CStreamPacket*)new char[sizeof(CStreamPacket) + nLen];
	pso->Init();	//new char 할당으로 하면 생성자 호출이 안되기 때문에 Init을 수동으로함
	pso->m_nPacketSize = sizeof(CStreamPacket) + nLen;
	pso->m_nType = nType;
	pso->m_nSubType = nSubType;
	pso->m_nTranID = nTranID;
	pso->m_nData = nData;
	pso->m_nPacketSeq = nPacketSeq;
	pso->m_bHasNextPacket = bHasNextPacket;
	memcpy(pso->m_szData, data, nLen);

	if(!SendExact((char*)pso, sizeof(CStreamPacket) + nLen))
	{
		m_bDataTransferError = TRUE;
		delete[] (char*)pso; 
		return FALSE;
	}

	delete[] (char*)pso;
	return TRUE;
}

BOOL CStreamSocket::AsyncSelect(UINT nEvent)
{
	if(SOCKET_ERROR == WSAAsyncSelect(m_Socket, m_hParent, WM_ASYNC_EVENT, nEvent))
		return FALSE;
	return TRUE;
}

BOOL CStreamSocket::IsDataTransferError(BOOL bReset)
{
	if(m_bDataTransferError)
	{
		if(bReset)
			m_bDataTransferError = FALSE;
		return TRUE;
	}
	return m_bDataTransferError;
}

BOOL CStreamSocket::IsValidSocket()
{
	return ((int)m_Socket >= 0);
}

UINT CStreamSocket::GetTranID()
{
	return InterlockedIncrement(&m_nTranID) % MAX_TRAN_COUNT;
}

BOOL CStreamSocket::SendStream(CStreamPacket *pso)
{
	UINT nLen = pso->m_nPacketSize - sizeof(CStreamPacket);

	if(nLen <= STREAM_BUFFER)
	{
		if(!SendExact((char*)pso,  pso->m_nPacketSize))
		{
			m_bDataTransferError = TRUE;
			delete[] (char*)pso; 
			return FALSE;
		}
	}
	else
	{
		UINT nPacketSeq = 1;	//1부터 시작해야한다. 
		UINT nSentSize = 0;
		BOOL bHasNextPacket;

		while(nSentSize < nLen)
		{
			UINT nCurSize = min((nLen - nSentSize), STREAM_BUFFER);
			bHasNextPacket = (nSentSize + nCurSize) < nLen;

			if(!SendBinary(pso->m_nType, pso->m_nSubType, &pso->m_szData[nSentSize], nCurSize, pso->m_nData, nPacketSeq++, pso->m_nTranID, bHasNextPacket))
			{
				m_bDataTransferError = TRUE;
				delete[] (char*)pso; 
				return FALSE;
			}

			nSentSize += nCurSize;
		}
	}

	delete[] (char*)pso;
	return TRUE;
}

BOOL CStreamSocket::SendStream(UINT nType, UINT nSubType, char *szData, UINT nData, UINT nTranID)
{
	UINT nLen = strlen(szData) + 1;

	if(nLen <= STREAM_BUFFER)
	{
		return SendData(nType, nSubType, szData, nData, 0, nTranID);
	}
	else
	{
		UINT nPacketSeq = 1;	//1부터 시작해야한다. 
		UINT nSentSize = 0;
		BOOL bHasNextPacket;

		while(nSentSize < nLen)
		{
			UINT nCurSize = min((nLen - nSentSize), STREAM_BUFFER);
			bHasNextPacket = (nSentSize + nCurSize) < nLen;

			if(!SendBinary(nType, nSubType, &szData[nSentSize], nCurSize, nData, nPacketSeq++, nTranID, bHasNextPacket))
				return FALSE;

			nSentSize += nCurSize;
		}
	}

	return TRUE;
}