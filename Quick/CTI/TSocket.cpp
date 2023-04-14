//QSocket.cpp

#include "stdafx.h"
//#include <iostream.h> 

#include <stdio.h>
#include <io.h>
#include <winsock2.h>
#include <sys/types.h>

#include "TSocket.h"
#include "TPacket.h"
//#include "g_bana_log->h"


#define READSTREAMLENGTH	4096
//#define READSTREAMLENGTH	16
#define EXPANDSIZE			2048
////////////////////////////////////////////////////////
// QSocket implementation


static WORD winsockVersion = 0;

CTSocketSystem::CTSocketSystem()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	
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

CTSocketSystem::~CTSocketSystem()
{
	if (m_bStatus)
	{
		WSACleanup();
	}
}



CTSocket::CTSocket()
{
	//Clear the socket
	m_Socket = -1;
	m_bConnTimeOut = FALSE;
	m_nConnTimeOut = 5000;
	m_hParent = NULL;
	m_bConnected = FALSE;
}

CTSocket::CTSocket(HWND hParent)
{
	//Clear the socket
	m_Socket = -1;
	m_bConnTimeOut = FALSE;
	m_nConnTimeOut = 5000;
	m_hParent = hParent;
}	


CTSocket::~CTSocket()
{
	//Close the socket
	Close();
}




BOOL CTSocket::Create()
{
	const int one = 1;
	
	//Check that the old socket was closed
	if ((int)m_Socket >= 0)
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


BOOL CTSocket::Close()
{
	if ((int)m_Socket >= 0)
    {
		linger lval;
		int		vlen;
		int		rc;

		lval.l_onoff	= 1;
		lval.l_linger	= 0;
		vlen = sizeof( lval );
		rc = setsockopt(m_Socket, SOL_SOCKET, SO_LINGER, (const char*) &lval, vlen );
		if ( rc != 0 ) return FALSE;

		closesocket(m_Socket);
		m_Socket = -1;
		m_bConnected = FALSE;

		//g_bana_log->Print("closing socket\n");
    }


	return true;
}


BOOL CTSocket::Shutdown()
{
	if ((int)m_Socket >= 0)
    {
//		g_bana_log->Print("shutdown socket\n");
		shutdown(m_Socket, SD_BOTH);
		m_bConnected = FALSE;
    }
	return true;
}



BOOL CTSocket::Bind(const UINT m_nPort)
{
	struct sockaddr_in addr;
	
	//Check that the socket is open!
	if ((int)m_Socket < 0)
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
BOOL CTSocket::Connect(const CString address, const UINT m_nPort)
{
	m_bConnTimeOut=FALSE;

	//Check the socket
	if ((int)m_Socket < 0)
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
	t.tv_sec = m_nConnTimeOut / 1000;
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
/*
	if(0 == m_hParent) return m_bConnected;

	UINT nEvent = FD_CLOSE | FD_READ;
	if(SOCKET_ERROR == WSAAsyncSelect(m_Socket, m_hParent, WM_ASYNC_EVENT, nEvent))
	{
		shutdown(m_Socket, SD_BOTH);
		closesocket(m_Socket);
		return FALSE;
	}
*/
	return m_bConnected;
}	


BOOL CTSocket::Listen()
{
	// Check socket
	if ((int)m_Socket < 0)
		return false;
	
	// Set it to listen
	if (listen(m_Socket, SOMAXCONN) < 0)
		return false;
	
	return true;
}


CTSocket *CTSocket::Accept()
{
	const int one = 1;
	
	int new_socket_id;
	CTSocket * new_socket;
	
	//Check this socket
	if ((int)m_Socket < 0)
		return NULL;
	
	//Accept an incoming connection
	if ((new_socket_id = accept(m_Socket, NULL, 0)) < 0)
		return NULL;
	
	//Create a new CTSocket and return it
	new_socket = new CTSocket(m_hParent);
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


char* CTSocket::GetPeerName()
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



char* CTSocket::GetSockName()
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



LONG CTSocket::Resolve(const CString address)
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



BOOL CTSocket::SetTimeOut(LONG secs)
{
	if (LOBYTE(winsockVersion) < 2)
		return false;
	int TimeOut=secs ;
	if (setsockopt(m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&TimeOut, sizeof(TimeOut)) == SOCKET_ERROR)
	{
		return false;
	}
	if (setsockopt(m_Socket, SOL_SOCKET, SO_SNDTIMEO, (char*)&TimeOut, sizeof(TimeOut)) == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}



int CTSocket::Send(const char *buff, const UINT bufflen)
{
	return send(m_Socket, buff, bufflen, 0);
}


BOOL CTSocket::SendExact(const char *buff, const UINT bufflen)
{
	int nSentLen = Send(buff, bufflen);
	return  nSentLen== (int)bufflen;
}



int CTSocket::Read(char *buff, const UINT bufflen)
{
	return recv(m_Socket, buff, bufflen, 0);
}

BOOL CTSocket::ReadExact(char *buff, const UINT bufflen)
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
//			g_bana_log->Print("zero bytes read\n");
			
			return false;
		} else {
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
//				g_bana_log->Print("socket error %d\n", WSAGetLastError());
				return false;
			}
		}
    }
	
	return true;
}

/*
char* CTSocket::ReadStream(int &nError)
{
	char	stream[READSTREAMLENGTH+1];
	int		len;
	char*	buff = NULL;
	int		n_rcv = 0, curSize = 0;
	int		nPacketSize = 0xFFFF;
	BOOL	bFirstRead = TRUE;
	TPACKET	*p;

	nError = 0;

	while ( TRUE ) 
	{
		len = Read(stream, READSTREAMLENGTH);
 
		if (SOCKET_ERROR == len )
		{
			nError = WSAGetLastError();

			//it raise periodically error because of the low speed of PDA
			if (nError != WSAEWOULDBLOCK){
				g_bana_log->Print(LL_DEBUG, LOG("socket error : %d\n"), nError);
				if (buff){
					delete[] buff;
					buff = NULL;
				}

				return NULL;
			}
		} else if ( len == 0 ) {
			if(n_rcv >= 8)
			{
				p = (TPACKET*) buff;
				p->nType = ntohl(p->nType);
				p->nSubType = ntohl(p->nSubType);
			}
			nError = GRACEFUL_CLOSE;
			return NULL;

		} else {
			stream[len] = '\0';
			if ( curSize <= n_rcv+len ) {
				curSize  += EXPANDSIZE;
				buff = (char*)realloc( (void *)buff, curSize );
				if ( buff == NULL ) {
					break;
				}
			}
			memcpy((void*)(buff+n_rcv), (void*)stream, len );
			n_rcv += len;
 			buff[n_rcv] = '\0';

			//패킷헤더에 정의된 크기를 이용해서 완료한다.
            if(bFirstRead && n_rcv >= 8) 
			{
				p = (TPACKET*) buff;
			
				if(!memcmp(p->head, PACKET_STX_T, 4))
				{
					nPacketSize = p->nPacketSize = ntohl(p->nPacketSize);
					bFirstRead = FALSE;
				}
				else
				{
					g_bana_log->Print(LL_DEBUG, ("데이터 무결성 오류\n")); 
					break;
				}
			}

			if(nPacketSize <= n_rcv)
			{
				//패킷 읽기 성공
				p->nType = ntohl(p->nType);
				p->nSubType = ntohl(p->nSubType);
				return buff;
			}
		}
	}

	if(buff != NULL)
	{
		delete[] buff;
	}
	return NULL;
}
*/


char* CTSocket::ReadStream(int &nError)
{
	char	stream[READSTREAMLENGTH+1];
	int		len;
	char*	buff = NULL;
	int		n_rcv = 0, curSize = 0, nLeftSize = 0;
	int		nPacketSize = 0xFFFF;
	BOOL	bFirstRead = TRUE;
	TPACKET	*p;

	nError = 0;

	while ( TRUE ) 
	{
		if(TRUE == bFirstRead )
		{
			nLeftSize = HEADER_SIZE_T;
		}
		len = Read(stream, nLeftSize);

		if (SOCKET_ERROR == len )
		{
			nError = WSAGetLastError();

			//it raise periodically error because of the low speed of PDA
			if (nError != WSAEWOULDBLOCK){
				//g_bana_log->Print("socket error : %d\n", nError);
				if (buff){
					delete[] buff;
					buff = NULL; 
				}
				return NULL;
			}
			else if(nError == WSAEWOULDBLOCK)
			{
				Sleep(1);
			}
		} else if ( len == 0 ) {
			if(n_rcv >= 8)
			{
				p = (TPACKET*) buff;
				p->nType = ntohl(p->nType);
				p->nSubType = ntohl(p->nSubType);
			}
			nError = GRACEFUL_CLOSE;
			return NULL;

		} else {
			stream[len] = '\0';
			if ( curSize <= n_rcv+len ) {
				curSize  += EXPANDSIZE;
				buff = (char*)realloc( (void *)buff, curSize );
				if ( buff == NULL ) {
					break;
				}
			}
			memcpy((void*)(buff+n_rcv), (void*)stream, len );
			n_rcv += len;
			buff[n_rcv] = '\0';

			nLeftSize = nLeftSize-len;
			
			//패킷헤더에 정의된 크기를 이용해서 완료한다.
			if(bFirstRead && nLeftSize == 0) 
			{
				p = (TPACKET*) buff;

				if(!memcmp(p->head, PACKET_STX_T, 4))
				{
					nPacketSize = p->nPacketSize = ntohl(p->nPacketSize);
					bFirstRead  = FALSE;
					nLeftSize   = nPacketSize - HEADER_SIZE_T;
				}
				else
				{
//					g_bana_log->Print("데이터 무결성 오류\n"); 
					break;
				}
			}

			if(nPacketSize <= n_rcv)
			{
				//패킷 읽기 성공
				p->nType = ntohl(p->nType);
				p->nSubType = ntohl(p->nSubType);
				return buff;
			}
		}
	}

	if(buff != NULL)
	{
		delete[] buff;
	}
	return NULL;
}

BOOL CTSocket::SendData(UINT nType, UINT nSubType, char* data)
{
	TPACKET *send = (TPACKET*) new char[HEADER_SIZE_T + strlen(data) + 1];
	
	MAKE_STX_T(send->head);
	send->nPacketSize = htonl(HEADER_SIZE_T + strlen(data));
	send->nType = htonl(nType);
	send->nSubType = htonl(nSubType);
	strcpy(send->data, data);
	
	//send the packet
	if(!SendExact((char*)send, HEADER_SIZE_T + strlen(data)))
	{
//		g_bana_log->Print("data transfer error\n");
		
		delete send; 
		return FALSE;
	}
	
	delete send;
	return TRUE;
}

BOOL CTSocket::SendBinary(UINT nType, UINT nSubType, void* data, UINT nLen)
{
	TPACKET *send = (TPACKET*) new char[HEADER_SIZE_T + nLen + 1];

	MAKE_STX_T(send->head);
	send->nPacketSize = htonl(HEADER_SIZE_T + nLen);
	send->nType = htonl(nType);
	send->nSubType = htonl(nSubType);
	memcpy(send->data, data, nLen);

	//send the packet
	if(!SendExact((char*)send, HEADER_SIZE_T + nLen))
	{
//		g_bana_log->Print("data transfer error\n");

		delete send; 
		return FALSE;
	}

	delete send;
	return TRUE;
}

BOOL CTSocket::IsClose()
{
	char buff[2];
	int nRet;

	//Nonblocking 모드로 세팅한다.
	u_long nonblocking = 1;
	if(ioctlsocket(m_Socket, FIONBIO, &nonblocking))
		return FALSE;

	nRet = recv(m_Socket, buff, 1, 0);

	__try {
		if(nRet == 0) 
		{
//			g_bana_log->Print("graceful close\n");
			return TRUE;
		}
		else if(nRet == SOCKET_ERROR)
		{
			if(WSAGetLastError() != WSAEWOULDBLOCK)	return TRUE;
		}
	}
	__finally {
		nonblocking = 0;
		ioctlsocket(m_Socket, FIONBIO, &nonblocking);
	}

	return FALSE;
}
