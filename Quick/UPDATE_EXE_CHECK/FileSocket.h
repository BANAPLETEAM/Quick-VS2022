#pragma once

#include "StreamSocket.h"
#include "UpdateDef.h"
#include "CypherEncodeText.h"

typedef map<UINT, pair<char*, UINT>> BUFFER_MAP;

class CFileSocket : public CStreamSocket
{
public:
	CFileSocket(void);
	~CFileSocket(void);

	BOOL ConnectServer(CString strServerIP, UINT nServerPort);
	BOOL RecvFile(CString strServerPath, CString strLocalPath = "");
	BOOL SendFile(CString strLocalPath, CString strServerPath = "");
	BOOL SendFile(char *szData, DWORD dwDataSize, CString strServerPath);


	UINT GetType() { return m_nType;}
	UINT GetSubType() { return m_nSubType; }
	UINT GetNData() { return m_nData; }
	char* GetBuffer() { return m_pBuffer; }
	UINT GetDataSize() { return m_dwSize; }

	DWORD GetRecvFileCurSize() { return m_dwRecvFileCurSize; }
	DWORD GetRecvFileTotalSize() { return m_dwRecvFileTotalSize; }
	DWORD GetSendFileCurSize() { return m_dwSendFileCurSize; }
	DWORD GetSendFileTotalSize() { return m_dwSendFileTotalSize; }

	BOOL RecvPacket(BOOL bFreeBuffer = TRUE);
	CCypherEncodeText m_encode;

protected:
	void ResetRecvFileHandle();
	void ResetSendFileHandle();
	BOOL CreateRecvFile(CString &strLocalPath);
	BOOL CreateSendFile(CString &strLocalPath);
	BOOL WriteRecvFile();
	BOOL IsRecvCompleted() { return m_dwRecvFileTotalSize <= m_dwRecvFileCurSize;}
	BOOL IsSendCompleted() { return m_dwSendFileTotalSize <= m_dwSendFileCurSize;}
	virtual void OnRecvFile() { }
	virtual void OnSendFile() { } 

	CString m_strBasePath;
	UINT m_nType;
	UINT m_nSubType;
	UINT m_nPacketSeq;
	BOOL m_bHasNextPacket;
	UINT m_nData;
	DWORD m_dwSize;
	DWORD m_dwOverRead;
	DWORD m_dwRecvFileTotalSize;
	DWORD m_dwRecvFileCurSize;
	char *m_pOverRead;
	char *m_pBuffer;
	HANDLE m_hRecvFile;
	BUFFER_MAP m_mapFileBuffer;
	BOOL m_bFreePrevBuffer;
	UINT m_nDesiredFileSequence;
	HANDLE m_hSendFile;
	DWORD m_dwSendFileTotalSize;
	DWORD m_dwSendFileCurSize;
	CSpeedMeter m_RecvTranBps;
};
