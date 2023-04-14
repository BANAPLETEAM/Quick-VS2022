//QSocket.cpp

#include "stdafx.h"
//#include <iostream.h>

#include <stdio.h>
#include <io.h>
#include <sys/types.h>

#include "QSocket.h"


//#define SD_BOTH         0x02

//1. readstramlength must be smaller than expandsize
//2. expandsize must be greater than one time sending filesize of server
//#define READSTREAMLENGTH	4096
//#define EXPANDSIZE			16384 

#define READSTREAMLENGTH	16383
#define EXPANDSIZE			163830 //16384 

////////////////////////////////////////////////////////
// QSocket implementation


static WORD winsockVersion = 0;

CQSocketSystem::CQSocketSystem()
{
	WORD wVersionRequested;
	WSADATA wsaData;

	//g_bana_log->SetMode(CQLog::ToConsole);
	
	wVersionRequested = MAKEWORD(2, 0);
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
	{
		m_bStatus = false;
		return;
	}
		
	winsockVersion = wsaData.wVersion;
	
	// If successful
	m_bStatus = true;
}

CQSocketSystem::~CQSocketSystem()
{
	if (m_bStatus)
	{
		//g_bana_log->Print("CQSocketSystem WSACleanup\n");
		WSACleanup();
	}
}



CQSocket::CQSocket()
{
	//Clear the socket
	m_Socket = -1;
	m_hParent = NULL;
	m_bConnected = FALSE;
	m_bDataTransferError = FALSE;
}



CQSocket::~CQSocket()
{
	//Close the socket
	Close();
}



BOOL CQSocket::Create()
{
	const int one = 1;
	
	//Check that the old socket was closed
	if (IsValidSocket())
		Close();
	
	//Create the socket
	if ((m_Socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
		return false;
    }
	
	if (setsockopt(m_Socket, IPPROTO_TCP, TCP_NODELAY, (char *)&one, sizeof(one)))
	{
		return false;
	}
	

	return true;
}


BOOL CQSocket::Close()
{
	g_bana_log->Print("socket close\n");


	if (IsValidSocket())
    {
		linger lval;
		int		vlen;
		int		rc;

		lval.l_onoff	= 1;
		lval.l_linger	= 2;
		vlen = sizeof( lval );
		rc = setsockopt(m_Socket, SOL_SOCKET, SO_LINGER, (const char*) &lval, vlen );
		if ( rc != 0 ) return FALSE;

		closesocket(m_Socket);
		m_Socket = -1;
		m_bConnected = FALSE;

		//g_bana_log->Print(LL_INTINFO, "closing socket\n");
    }

	return true;
}


BOOL CQSocket::Shutdown()
{
	if (IsValidSocket())
    {
		//g_bana_log->Print(LL_INTINFO, "shutdown socket\n");
		shutdown(m_Socket, SD_BOTH);
		m_bConnected = FALSE;
    }
	return true;
}



BOOL CQSocket::Bind(const UINT m_nPort)
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
BOOL CQSocket::Connect(const CString address, const UINT m_nPort)
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

BOOL CQSocket::Listen()
{
	// Check socket
	if (!IsValidSocket())
		return false;
	
	// Set it to listen
	if (listen(m_Socket, SOMAXCONN) < 0)
		return false;
	
	return true;
}



CQSocket *CQSocket::Accept()
{
	
	const int one = 1;
	
	int new_socket_id;
	CQSocket * new_socket;
	
	//Check this socket
	if (!IsValidSocket())
		return NULL;
	
	//Accept an incoming connection
	if ((new_socket_id = accept(m_Socket, NULL, 0)) < 0)
		return NULL;
	 
	//Create a new CQSocket and return it
	new_socket = new CQSocket;
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



char* CQSocket::GetPeerName()
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



char* CQSocket::GetSockName()
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




LONG CQSocket::Resolve(const CString address)
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



BOOL CQSocket::SetTimeOut(LONG millisecs)
{
	if (LOBYTE(winsockVersion) < 2)
		return false;
	

	int timeout=millisecs * 1000;
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



int CQSocket::Send(const char *buff, const UINT bufflen)
{
	return send(m_Socket, buff, bufflen, 0);
}


BOOL CQSocket::SendExact(const char *buff, const UINT bufflen)
{
	return Send(buff, bufflen) == (int)bufflen;
}



int CQSocket::Read(char *buff, const UINT bufflen)
{
	return recv(m_Socket, buff, bufflen, 0);
}

BOOL CQSocket::ReadExact(char *buff, const UINT bufflen)
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
			
		} else if (n == 0) {
		//	g_bana_log->Print(LL_INTWARN, "0 bytes read\n");
			
			return false;
		} else {
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				//g_bana_log->Print(LL_INTWARN, "socket error %d\n", WSAGetLastError());
				return false;
			}
		}
    }
	
	return true;
}


char* CQSocket::ReadStream()
{
	char	stream[READSTREAMLENGTH+1];
	int		len;
	char*	buff = NULL;
	int		n_rcv = 0, curSize = 0;
	int		nPacketSize = 0xFFFF;
	BOOL	bFirstRead = TRUE;
	QPACKET	*p = NULL;

	//COleDateTime dtCurrent = COleDateTime::GetCurrentTime();

	while ( TRUE ) {
		//int nReadableSize = READSTREAMLENGTH;
		
		//if(nPacketSize != 0xFFFF)
		//	nReadableSize = min((nPacketSize - n_rcv), READSTREAMLENGTH);
		
		len = Read(stream, READSTREAMLENGTH);
		if (len < 0){
			int nError = WSAGetLastError();

			if (nError != WSAEWOULDBLOCK && nError != WSAEFAULT){
				g_bana_log->Print("socket error : %d\n", nError);
				if (buff){
					free(buff);
					buff = NULL;
				}
				return FALSE;
			}
			else if(nError == WSAEWOULDBLOCK)
			{
				u_long nonblocking = 1;
				if(ioctlsocket(m_Socket, FIONREAD , &nonblocking))
					return FALSE;

				fd_set fdread;
				struct timeval t;
				fdread.fd_count = 1;
				fdread.fd_array[0] = m_Socket;
				memset((char *)&t, 0, sizeof(t));
				t.tv_sec = 5;
				t.tv_usec = 0;
				int sr = select(0, &fdread, NULL, NULL, &t);

				nonblocking = 0;
				if(ioctlsocket(m_Socket, FIONREAD , &nonblocking))
					return FALSE;

			}
		} else if ( len == 0 ) {
			if(n_rcv >= 8)
			{
				p = (QPACKET*) buff;
				p->nType = ntohs(p->nType);
				p->nSubType = ntohs(p->nSubType);
			}

			//g_bana_log->Print("[len == 0] nType=%d, nSubType=%d, nSize =%d\n", p->nType, p->nSubType, p->nPacketSize);

			return buff;

		} else {
			stream[len] = '\0';
			if ( curSize <= n_rcv+len ) {
				curSize  += EXPANDSIZE;
				if(buff == NULL)
					buff = (char*)malloc(curSize);
				else
					buff = (char*)realloc( (void *)buff, curSize );
	
				if(buff == NULL) {
					break;
				}
			}
			memcpy((void*)(buff+n_rcv), (void*)stream, len );
			n_rcv += len;
 			buff[n_rcv] = '\0';

			//패킷헤더에 정의된 크기를 이용해서 완료한다.
			if(bFirstRead && n_rcv >= 8) 
			{
				p = (QPACKET*) buff;
			
				if(!memcmp(p->head, PACKET_STX, 2))
				{
					nPacketSize = p->nPacketSize = ntohs(p->nPacketSize);
					//g_bana_log->Print("nPacketSize = %d\n", nPacketSize);
					bFirstRead = FALSE;
				}
				else
				{
					//g_bana_log->Print(LL_DEBUG, ("데이터 무결성 오류\n")); 				
					break;
				}
			}

			if(nPacketSize <= n_rcv)
			{
				//패킷 읽기 성공
				p->nType = ntohs(p->nType);
				p->nSubType = ntohs(p->nSubType);

				//g_bana_log->Print("[nPacketSize <= n_rcv] nType=%d, nSubType=%d, nSize =%d\n", p->nType, p->nSubType, p->nPacketSize);
				return buff;
			}
		}
	}

	if(buff != NULL)
	{
		free(buff);
	}

	return NULL;
}

char* CQSocket::ReadStream2(long &nRealRecvLen)
{
	char	stream[READSTREAMLENGTH+1];
	int		len;
	char*	buff = NULL;
	int		n_rcv = 0, curSize = 0;
	int		nPacketSize = 0xFFFF;
	BOOL	bFirstRead = TRUE;
	QPACKET* p = NULL;;

	while ( TRUE ) {

		len = Read(stream, READSTREAMLENGTH);
		if (len < 0){
			int nError = WSAGetLastError();

			if (nError != WSAEWOULDBLOCK && nError != WSAEFAULT){
				//g_bana_log->Print(LL_DEBUG, "socket error : %d\n", nError);
				if (buff){
					free(buff);
					buff = NULL;
				}
				return FALSE;
			}
			else if(nError == WSAEWOULDBLOCK)
			{
				u_long nonblocking = 1;
				if(ioctlsocket(m_Socket, FIONREAD , &nonblocking))
					return FALSE;

				fd_set fdread;
				struct timeval t;
				fdread.fd_count = 1;
				fdread.fd_array[0] = m_Socket;
				memset((char *)&t, 0, sizeof(t));
				t.tv_sec = 5;
				t.tv_usec = 0;
				int sr = select(0, &fdread, NULL, NULL, &t);

				nonblocking = 0;
				if(ioctlsocket(m_Socket, FIONREAD , &nonblocking))
					return FALSE;

			}
		} else if ( len == 0 ) {
			if(n_rcv >= 8)
			{
				p = (QPACKET*) buff;
				p->nType = ntohs(p->nType);
				p->nSubType = ntohs(p->nSubType);
				nRealRecvLen = n_rcv;
			}

			return buff;

		} else {
			stream[len] = '\0';
			if ( curSize <= n_rcv+len ) {
				curSize  += EXPANDSIZE;
				if(buff == NULL)
					buff = (char*)malloc(curSize);
				else
					buff = (char*)realloc( (void *)buff, curSize );

				if(buff == NULL) {
					break;
				}
			}
			memcpy((void*)(buff+n_rcv), (void*)stream, len );
			n_rcv += len;
			buff[n_rcv] = '\0';

			//패킷헤더에 정의된 크기를 이용해서 완료한다.
			if(bFirstRead && n_rcv >= 8) 
			{
				p = (QPACKET*) buff;

				if(!memcmp(p->head, PACKET_STX, 2))
				{
					nPacketSize = p->nPacketSize = ntohs(p->nPacketSize);
					//g_bana_log->Print("nPacketSize = %d\n", nPacketSize);
					bFirstRead = FALSE;
				}
				else
				{
					g_bana_log->Print("데이터 무결성 오류\n"); 
					break;
				}
			}

			if(nPacketSize <= n_rcv)
			{
				//패킷 읽기 성공
				p->nType = ntohs(p->nType);
				p->nSubType = ntohs(p->nSubType);
				nRealRecvLen = n_rcv;
				//g_bana_log->Print("[nPacketSize <= n_rcv] nType=%d, nSubType=%d, nSize =%d\n", p->nType, p->nSubType, p->nPacketSize);
				return buff;
			}
		}
	}

	if(buff != NULL)
	{
		free(buff);
	}

	return NULL;
}



BOOL CQSocket::SendCommand(UINT nType, UINT nSubType)
{
	QPACKET send;
	
	MAKE_STX(send.head);
	send.nPacketSize = htons(sizeof(QPACKET));
	send.nType = htons(nType);
	send.nSubType = htons(nSubType);
	
	//send the packet
	return SendExact((char*)&send,sizeof(QPACKET));
}

BOOL CQSocket::SendData(UINT nType, UINT nSubType, char* data)
{
	QPACKET *send = (QPACKET*) new char[HEADER_SIZE + strlen(data) + 1];
	
	MAKE_STX(send->head);
	send->nPacketSize = htons(HEADER_SIZE + strlen(data));
	send->nType = htons(nType);
	send->nSubType = htons(nSubType);
	strcpy(send->data, data);
	
	//send the packet
	if(!SendExact((char*)send, HEADER_SIZE + strlen(data)))
	{
		m_bDataTransferError = TRUE;
		g_bana_log->Print("data transfer error\n");
		
		delete[] (char*)send; 
		return FALSE;
	}
	
	delete[] (char*)send;
	return TRUE;
}

BOOL CQSocket::SendBinary(UINT nType, UINT nSubType, void* data, UINT nLen)
{
	QPACKET *send = (QPACKET*) new char[HEADER_SIZE + nLen + 1];
	
	MAKE_STX(send->head);
	send->nPacketSize = htons(HEADER_SIZE + nLen);
	send->nType = htons(nType);
	send->nSubType = htons(nSubType);
	memcpy(send->data, data, nLen);
	
	//send the packet
	if(!SendExact((char*)send, HEADER_SIZE + nLen))
	{
		m_bDataTransferError = TRUE;
		//g_bana_log->Print(LL_INTWARN, "data transfer error\n");
		
		delete[] (char*)send; 
		return FALSE;
	}
	
	delete[] (char*)send;
	return TRUE;
}


int CQSocket::WaitOK()
{
	int nRet;
	QPACKET *p = NULL;
	
	if((p = (QPACKET*)ReadStream()) == NULL)
	{
		if(p != NULL) free(p);
		nRet = P_SOCKET_ERROR;
	}
	else
	{
		if(p->nType == PT_OK)
			nRet = P_SUCCESS;
		else
			nRet = P_FAILED;
	}
	
	if(p != NULL) free(p);
	return nRet;
}


BOOL CQSocket::AsyncSelect(UINT nEvent)
{
	if(SOCKET_ERROR == WSAAsyncSelect(m_Socket, m_hParent, WM_ASYNC_EVENT, nEvent))
		return FALSE;
	return TRUE;
}


BOOL CQSocket::IsDataTransferError(BOOL bReset)
{
	if(m_bDataTransferError)
	{
		if(bReset)
			m_bDataTransferError = FALSE;
		return TRUE;
	}
	return m_bDataTransferError;
}

BOOL CQSocket::IsValidSocket()
{
	return ((int)m_Socket >= 0);
}
