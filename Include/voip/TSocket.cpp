#include "stdafx.h"
//#include <iostream.h>

#include <stdio.h>
#include <io.h>
#include <winsock2.h>
#include <sys/types.h>

#include "TSocket.h"
#include "VoicePacket.h"


//매우 중요한 로그
#define LL_STATE	0
//클라이언트 관련 로그
#define LL_CLIENTS	1
//약간 중요한 로그
#define LL_INTERR	0
//중요한 로그
#define LL_INTWARN	3
//디버그
#define LL_DEBUG	5
//그냥 정보
#define LL_INTINFO	9
//모든 로그 
#define LL_ALL		10


//#define READSTREAMLENGTH	512
#define READSTREAMLENGTH	4096
#define EXPANDSIZE			2048


////////////////////////////////////////////////////////
// QSocket implementation


#include "QLog2.h"
CQLog2	qsLog2;
static WORD winsockVersion = 0;

/*
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
*/


CVTSocket::CVTSocket()
{
	//Clear the socket
	m_Socket = INVALID_SOCKET;
	m_bConnTimeOut = FALSE;
	m_nConnTimeOut = 5000;
	m_hParent = NULL;
	m_bConnected = FALSE;
}


CVTSocket::CVTSocket(HWND hParent)
{
	//Clear the socket
	m_Socket = INVALID_SOCKET;
	m_bConnTimeOut = FALSE;
	m_nConnTimeOut = 5000;
	m_hParent = hParent;
}	


CVTSocket::~CVTSocket()
{
	//Close the socket
	Close();
	m_bConnected = FALSE;
}




BOOL CVTSocket::Create()
{
	const int one = 1;
	
	//Check that the old socket was closed
	if (m_Socket != INVALID_SOCKET)	Close();
	
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


BOOL CVTSocket::Close()
{
	if (m_Socket != INVALID_SOCKET)
    {
		linger lval;
		int		vlen;
		int		rc;

		lval.l_onoff	= 1;
		lval.l_linger	= 0;
		vlen = sizeof( lval );
		rc = setsockopt(m_Socket, SOL_SOCKET, SO_LINGER, (const char*) &lval, vlen );
//		if ( rc != 0 ) return FALSE;

		closesocket(m_Socket);
		m_Socket = INVALID_SOCKET;

		qsLog2.Print(LL_INTINFO, LOG("closing socket\n"));
    }

	m_bConnected = FALSE;
	return true;
}


BOOL CVTSocket::Shutdown()
{
	if (m_Socket != INVALID_SOCKET)
    {
		qsLog2.Print(LL_INTINFO, LOG("shutdown socket\n"));
		shutdown(m_Socket, SD_BOTH);
		m_bConnected = FALSE;
    }
	return true;
}



BOOL CVTSocket::Bind(const UINT m_nPort)
{
	struct sockaddr_in addr;
	
	//Check that the socket is open!
	if (INVALID_SOCKET == m_Socket)
		return false;
	
	//Set up the address to bind the socket to
	addr.sin_family = AF_INET;
	addr.sin_port = htons(m_nPort);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	// And do the binding
	if (bind(m_Socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		return false;
	
	return true;
}


//TimeOut connect
BOOL CVTSocket::Connect(const CString address, const UINT m_nPort)
{
	m_bConnTimeOut=FALSE;

	//Check the socket
	if (INVALID_SOCKET == m_Socket)
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
//		m_bConnected = TRUE;
		if(WSAGetLastError() == WSAEWOULDBLOCK)
		{
			int sr = select(0, NULL, &fdwrite, NULL, &t);
			if(sr == 1) m_bConnected = TRUE;
			else m_bConnTimeOut = TRUE;
		}
	}
	else
	{
		m_bConnected = FALSE;
	}

	nonblocking = 0;
	ioctlsocket(m_Socket, FIONBIO, &nonblocking);

	return m_bConnected;
}	


BOOL CVTSocket::Listen()
{
	// Check socket
	if (INVALID_SOCKET == m_Socket )
		return false;
	
	// Set it to listen
	if (listen(m_Socket, SOMAXCONN) < 0)
		return false;
	
	return true;
}


CVTSocket *CVTSocket::Accept()
{
	const int one = 1;
	
	int new_socket_id;
	CVTSocket * new_socket;
	
	//Check this socket
	if (INVALID_SOCKET == m_Socket )
		return NULL;
	
	//Accept an incoming connection
	if ((new_socket_id = accept(m_Socket, NULL, 0)) < 0)
		return NULL;
	
	//Create a new CVTSocket and return it
	//new_socket = new CVTSocket(m_hParent);
	new_socket = new CVTSocket;
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

	return new_socket;
}


char* CVTSocket::GetPeerName()
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



char* CVTSocket::GetSockName()
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



LONG CVTSocket::Resolve(const CString address)
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



BOOL CVTSocket::SetTimeOut(LONG secs)
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



int CVTSocket::Send(const char *buff, const UINT bufflen)
{
//	CSingleLock Lock(&m_cs,TRUE);
	return send(m_Socket, buff, bufflen, 0);
}


BOOL CVTSocket::SendExact(const char *buff, const UINT bufflen)
{
	return Send(buff, bufflen) == (int)bufflen;
}



int CVTSocket::Read(char *buff, const UINT bufflen)
{
//	CSingleLock Lock(&m_cs,TRUE);
	return recv(m_Socket, buff, bufflen, 0);
}

BOOL CVTSocket::ReadExact(char *buff, const UINT bufflen,int &nError)
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
			qsLog2.Print(LL_INTWARN, LOG("zero bytes read\n"));
			Close();
			return false;
		} else 
		{
			nError = WSAGetLastError();
			if (nError != WSAEWOULDBLOCK)
			{
				qsLog2.Print(LL_INTWARN, LOG("socket error %d\n"), WSAGetLastError());
				Close();
				return false;
			}
		}
    }
	
	return true;
}

char* CVTSocket::ReadStream(int &nError)
{
	char	stream[READSTREAMLENGTH+1];
	int		len;
	char*	buff = NULL;
	int		n_rcv = 0, curSize = 0, nLeftSize = 0;
	int		nPacketSize = 0xFFFF;
	BOOL	bFirstRead = TRUE;
	LPVTMSG	p = (LPVTMSG)stream;

	nError = 0;
	if(FALSE == ReadExact(stream, HEADER_SIZE,nError) ) return NULL;
	buff = (char*)malloc(p->m_lLength + HEADER_SIZE);
	if(NULL == buff) return NULL;
	
	nError = 0;
	memcpy(buff,stream,HEADER_SIZE);
	if(FALSE ==  ReadExact(buff+HEADER_SIZE,p->m_lLength,nError) )
	{
		free(buff);
		nError = 0;
		return NULL;
	}

	return buff;
}

BOOL CVTSocket::SendData(UINT ucCmd, UINT ucMsgType, const char* data)
{
	return SendData( ucCmd,  ucMsgType,"", data);
}

BOOL CVTSocket::SendData(UINT ucCmd, UINT ucMsgType,const char* szTo, const char* data)
{
	int nLen = strlen(data);
	char* pa = (char*) malloc(HEADER_SIZE + nLen + 1);
	LPVTMSG send = (LPVTMSG) pa;


	send->m_ucIdentity	= VT_IDENTITY;
	send->m_ucCmd		= ucCmd;
	send->m_ucMsgType	= ucMsgType;
	send->m_lLength		= nLen+1 ;
	strncpy(send->m_sToID,szTo,sizeof(send->m_sToID));
	memcpy(send->m_pData, data,send->m_lLength);



	if(!SendExact((char*)send, HEADER_SIZE + send->m_lLength ))
	{
		qsLog2.Print(LL_INTWARN, LOG("data transfer error\n"));
		
		free(pa); 
		return FALSE;
	}
	
	free( pa ); 
	return TRUE;

}
BOOL CVTSocket::SendBinary(UINT ucCmd, UINT ucMsgType, void* data, UINT nLen)
{
	return SendBinary( ucCmd,  ucMsgType,"", data, nLen);
}
BOOL CVTSocket::SendBinary(UINT ucCmd, UINT ucMsgType,const char* szToID, void* data, UINT nLen)
{ 
	LPVTMSG send = (LPVTMSG) new char[HEADER_SIZE + nLen];
	
	send->m_ucIdentity	= VT_IDENTITY;
	send->m_ucCmd		= ucCmd;
	send->m_ucMsgType	= ucMsgType;
	send->m_lLength		= nLen ;
	memcpy(send->m_sToID,szToID,sizeof(send->m_sToID));
	memcpy(send->m_pData, data,nLen);

	if(!SendExact((char*)send, HEADER_SIZE + nLen))
	{
		qsLog2.Print(LL_INTWARN, LOG("data transfer error\n"));
		
		delete[] (char*)send; 
		return FALSE;
	}
	
	delete[] (char*) send;
	return TRUE;
}


BOOL CVTSocket::IsClose()
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
			qsLog2.Print("graceful close\n");
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
