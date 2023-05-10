#include "stdafx.h"
#include "FileSocket.h"
#include "CypherEncodeText.h"
#include "MkPacket.h"
#include "LogiFunc.h"
#include "StreamPacket.h"

static BYTE nKey[] = {0x6a,0x10,0x6a,0x00,0x8d,0x45,0xc4,0x50,0xe8,0xec,0x89,0xff,0xff,0x83,0xc4,0x0c};

CFileSocket::CFileSocket(void)
{
	//아래에 SetExternalKey 쓰면 메모리가 4바이트 밀리는 오류발생
	memcpy(&m_encode.m_ExternalKey[0], &nKey[0], sizeof(nKey));

#if defined(_LABEL) || defined(_SCHEDULE) || defined(_LABEL_MONITOR) || defined(_DUTCH) || defined(_BANA_STOCK) || defined(_BANA_HELP)
	m_strBasePath = GetModuleFullPath();
#else
	m_strBasePath = GetModuleFullPath() + "RecvFiles\\";
	CreateDirectory(m_strBasePath, NULL);
#endif
	m_pBuffer = NULL;
	m_hRecvFile = NULL;
	m_dwOverRead = 0;
	m_pOverRead = NULL;
	m_bFreePrevBuffer = FALSE;
	m_hSendFile = NULL;
}

CFileSocket::~CFileSocket(void)
{
	if(m_pBuffer && m_bFreePrevBuffer)
		delete[] m_pBuffer;

	if(m_hRecvFile)
		CloseHandle(m_hRecvFile);

	if(m_hSendFile)
		CloseHandle(m_hSendFile);
}

BOOL CFileSocket::RecvPacket(BOOL bFreeBuffer)
{
	BUFFER_MAP mapBuffer;
	DWORD dwTotalSize = 0;

	if(m_pBuffer && m_bFreePrevBuffer)
		delete[] m_pBuffer;

	m_bFreePrevBuffer = bFreeBuffer;

	while(1)
	{	
		m_pBuffer = CStreamSocket::RecvPacket(m_nType, m_nSubType, m_dwSize, m_nData, m_nPacketSeq, m_bHasNextPacket, m_dwOverRead, &m_pOverRead);
		if(m_nType == 0)
			break;

		m_RecvTranBps.IncreaseTranBytes(m_dwSize);

		if(m_nType == PT_CHECK_CONN)
		{
			delete[] m_pBuffer;
			continue;
		}

		mapBuffer.insert(BUFFER_MAP::value_type(m_nPacketSeq, make_pair(m_pBuffer, m_dwSize)));
		dwTotalSize += m_dwSize;

		if(!m_bHasNextPacket)
			break;
	} 

	if(mapBuffer.size() > 1)
	{
		BUFFER_MAP::iterator it;
		char *pBuffer = new CHAR[dwTotalSize];
		UINT nPos = 0;

		for(it = mapBuffer.begin(); it != mapBuffer.end(); it++)
		{
			memcpy(&pBuffer[nPos], it->second.first, it->second.second);
			nPos += it->second.second;
			delete[] it->second.first;
		}

		m_dwSize = dwTotalSize;
		m_pBuffer = pBuffer;
	}

	return (m_nType != 0);
}

BOOL CFileSocket::ConnectServer(CString strServerIP, UINT nServerPort)
{

	if(!Create()) 
		return FALSE;

	SetConnTimeOut(5);

	if(!Connect(strServerIP, nServerPort))
		return FALSE;

#ifdef _DEBUG
	SetTimeOut(100);
#else
	SetTimeOut(10);
#endif

	if(!RecvPacket())
		return FALSE;

	m_encode.EncodeAuthInfo((BYTE*)m_pBuffer, NULL, FALSE);
	if(!SendBinary(PT_AUTHENTICATION, 0, m_pBuffer, m_dwSize))
		return FALSE;

	if(!RecvPacket())
		return FALSE;

	//if(m_nSubType != PST_SUCCESS)
	//	mkLog.Print("인증 실패\n");

	return m_nSubType == PST_SUCCESS;
}

BOOL CFileSocket::RecvFile(CString strServerPath, CString strLocalPath)
{
	if(!SendData(PT_FILE_UPDATE, PST_REQUEST_FILE_NO_HANDLE, (LPSTR)(LPCTSTR)strServerPath, 0, 0, 0))
		return FALSE;

	if(!RecvPacket())
		return FALSE;

	if(GetSubType() == PST_ERROR)
		return FALSE;

	if(!CreateRecvFile(strLocalPath))
		return FALSE;

	while(!IsRecvCompleted())
	{
		if(!RecvPacket(FALSE))
			return FALSE;

		m_dwRecvFileCurSize += m_dwSize;

		//mkLog.Print("%d\n", m_dwRecvFileCurSize);

		if(!WriteRecvFile())
			return FALSE;

		OnRecvFile();
	}

	ResetRecvFileHandle();

	return TRUE;
}

BOOL CFileSocket::WriteRecvFile()
{
	DWORD dwWritten;
	BUFFER_MAP::iterator it;

	m_mapFileBuffer.insert(BUFFER_MAP::value_type(m_nPacketSeq, make_pair(m_pBuffer, m_dwSize)));

	//100개씩 한번에 쓰기
	if(!IsRecvCompleted() && m_mapFileBuffer.size() < 100)
		return TRUE;

	for(it = m_mapFileBuffer.begin(); it != m_mapFileBuffer.end();)
	{
		//스퀀스가 맞을 때까지만 루프를 돈다.
		if(it->first != m_nDesiredFileSequence)
			break;

		if(!WriteFile(m_hRecvFile, it->second.first, it->second.second, &dwWritten, NULL))
			return FALSE;

		delete[] it->second.first;
		it = m_mapFileBuffer.erase(it);
		m_nDesiredFileSequence++;
	}

	return TRUE;
}

void CFileSocket::ResetRecvFileHandle()
{
	if(m_hRecvFile)
	{
		CloseHandle(m_hRecvFile);
		m_hRecvFile = INVALID_HANDLE_VALUE;
	}

	for(BUFFER_MAP::iterator it = m_mapFileBuffer.begin(); it != m_mapFileBuffer.end(); it++)
		delete[] it->second.first;

	m_mapFileBuffer.clear();
	m_nDesiredFileSequence = 1;
}

BOOL CFileSocket::CreateRecvFile(CString &strLocalPath)
{
	UINT nPostID = 0;
	CString strPath, strExt;
	CString strFileName;

	ResetRecvFileHandle();

	if(strLocalPath.GetLength() > 0)
	{
		if(strLocalPath.Find(":") < 0)
		{
			strPath = GetModuleFullPath() + strLocalPath;
			strPath.Replace("\\\\", "\\");
		}
		else
			strPath = strLocalPath;

		UINT nPos = strPath.ReverseFind('\\');
		if(nPos > 0)
			CreateDirectory(strPath.Left(nPos), NULL);

		m_hRecvFile = CreateFile(strPath, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	else
	{
		(char*)&m_pBuffer[1];

		UINT nPos = strFileName.ReverseFind('\\');
		if(nPos > 0)
			strFileName = strFileName.Mid(nPos + 1);

		nPos = strFileName.ReverseFind('.');
		if(nPos > 0)
		{
			strExt = strFileName.Mid(nPos);
			strFileName = strFileName.Left(nPos);
		}

		while(1)
		{
			if(nPostID == 0)
				strPath = m_strBasePath + strFileName + strExt;
			else 
				strPath.Format("%s%s(%d)%s", m_strBasePath, strFileName, nPostID, strExt);

			m_hRecvFile = CreateFile(strPath, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

			if(INVALID_HANDLE_VALUE == m_hRecvFile) 
			{
				DWORD dwLastError = GetLastError();
				if(dwLastError == ERROR_FILE_EXISTS)
				{
					nPostID++;
					continue;
				}
				//mkLog.Print("CreateFile failed: GetLastError = %d\n", dwLastError);
			}
			break;
		}
	}

	//mkLog.Print("CreateRecvFIle: %s\n", strPath);
	m_dwRecvFileTotalSize = m_nData;
	m_dwRecvFileCurSize = 0;
	return m_hRecvFile != INVALID_HANDLE_VALUE;
}

BOOL CFileSocket::SendFile(CString strLocalPath, CString strServerPath)
{
	ResetSendFileHandle();

	if(!CreateSendFile(strLocalPath))
		return FALSE;

	m_dwSendFileTotalSize = GetFileSize(m_hSendFile, NULL);

	if(strServerPath.IsEmpty())
		strServerPath = strLocalPath;

	char szBuffer[MAX_PATH];
	szBuffer[0] = 0;
	strcpy(&szBuffer[1], (LPSTR)(LPCTSTR)strServerPath);	

	if(!SendBinary(PT_FILE_UPDATE, PST_FILE_TRAN, szBuffer, strServerPath.GetLength() + 2, m_dwSendFileTotalSize))
		return FALSE;

	UINT nPacketSeq = 1;

	while(!IsSendCompleted())
	{
		DWORD dwSize = 0;
		char szBuffer[STREAM_BUFFER];
		if(!ReadFile(m_hSendFile, szBuffer, STREAM_BUFFER, (LPDWORD)&dwSize, NULL))
			return FALSE;

		m_dwSendFileCurSize += dwSize;

		if(!SendBinary(PT_FILE_UPDATE, PST_FILE_DATA, szBuffer, dwSize, 0, nPacketSeq++))
			return FALSE;

		OnSendFile();
	}

	ResetSendFileHandle();

	if(!RecvPacket())
		return FALSE;

	return m_nSubType == PST_FILE_TRAN_END;
}

BOOL CFileSocket::SendFile(char *szData, DWORD dwDataSize, CString strServerPath)
{
	ResetSendFileHandle();

	m_dwSendFileTotalSize = dwDataSize;

	char szBuffer[MAX_PATH];
	szBuffer[0] = 0;
	strcpy(&szBuffer[1], (LPSTR)(LPCTSTR)strServerPath);	

	if(!SendBinary(PT_FILE_UPDATE, PST_FILE_TRAN, szBuffer, strServerPath.GetLength() + 2, m_dwSendFileTotalSize))
		return FALSE;

	UINT nPacketSeq = 1;

	while(!IsSendCompleted())
	{
		DWORD dwCurSize = min(STREAM_BUFFER, dwDataSize - m_dwSendFileCurSize);

		if(!SendBinary(PT_FILE_UPDATE, PST_FILE_DATA, &szData[m_dwSendFileCurSize], dwCurSize, 0, nPacketSeq++))
			return FALSE;

		m_dwSendFileCurSize += dwCurSize;

		OnSendFile();
	}

	ResetSendFileHandle();

	if(!RecvPacket())
		return FALSE;

	return m_nSubType == PST_FILE_TRAN_END;
}

BOOL CFileSocket::CreateSendFile(CString &strLocalPath)
{
	m_hSendFile = CreateFile(strLocalPath, GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(m_hSendFile == INVALID_HANDLE_VALUE)
	{
		//mkLog.Print("SendFile(%s): 파일 핸들 오류 입니다.\n", strLocalPath);
		return FALSE;
	}

	return TRUE;
}

void CFileSocket::ResetSendFileHandle()
{
	if(m_hSendFile)
	{
		CloseHandle(m_hSendFile);
		m_hSendFile = INVALID_HANDLE_VALUE;
	}

	m_dwSendFileCurSize = 0;
}