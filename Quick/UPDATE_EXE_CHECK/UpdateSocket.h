#pragma once

#include "FileSocket.h"
#include "UpdateDef.h"

#define WM_UPDATE_SOCKET_EVENT	(WM_USER + 1)

class CUpdateSocket : public CFileSocket
{
public:

	CUpdateSocket(void);
	~CUpdateSocket(void);

	BOOL SendDataList(UINT nType, UINT nSubType, CDataList &datalist, UINT nData = 0, UINT nPacketSeq = 0, BYTE nTranID = 0);
	BOOL CheckUpdateEXE(CString strUpdateEXE);
	void SetSendRecvEvent(CWnd *pWnd, DWORD dwTotalSize = 0);
	DWORD GetTotalFileSize() { return m_dwTotalSize; }
	DWORD GetRemainTotalSize() { return m_dwRemainTotal; }
	DWORD GetRecvTranBps() { return m_RecvTranBps.GetTranBps(); }

protected:
	virtual void OnRecvFile();
	virtual void OnSendFile();

	CDataList m_datalist;
	DWORD m_dwTotalSize;
	DWORD m_dwRemainTotal;
	CWnd *m_pwndRecvEvent;

};
