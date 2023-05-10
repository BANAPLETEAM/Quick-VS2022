#include "stdafx.h"
#include "UpdateSocket.h"
#include "MkPacket.h"

//using namespace mklib;

CUpdateSocket::CUpdateSocket(void)
{
	m_pwndRecvEvent = NULL;
	m_dwTotalSize = 0;
}

CUpdateSocket::~CUpdateSocket(void)
{
}

BOOL CUpdateSocket::SendDataList(UINT nType, UINT nSubType, CDataList &datalist, UINT nData, UINT nPacketSeq, BYTE nTranID)
{
	return SendBinary(nType, nSubType, datalist.GetDataPtr(), datalist.GetSize(), nData, nPacketSeq, nTranID);
}

BOOL CUpdateSocket::CheckUpdateEXE(CString strUpdateEXE)
{
	CDataList datalist(strUpdateEXE);
	if(!SendDataList(PT_UPDATE, PST_CHECK_UPDATE_EXE, datalist))
		return FALSE;

	if(!RecvPacket())
		return FALSE;

	if(datalist.GetString(0) == "0.0")
	{
		//mkLog.Print("서버에 %s파일이 존재하지 않습니다.", strUpdateEXE);
		return FALSE;
	}

	return TRUE;
}

void CUpdateSocket::OnRecvFile()
{
	if(m_pwndRecvEvent)
	{
		m_dwRemainTotal -= m_dwSize;
		m_pwndRecvEvent->PostMessage(WM_UPDATE_SOCKET_EVENT, (WPARAM)this, NULL);
	}
}

void CUpdateSocket::OnSendFile()
{
	if(m_pwndRecvEvent)
	{
		m_pwndRecvEvent->PostMessage(WM_UPDATE_SOCKET_EVENT, (WPARAM)this, 1);
	}
}

void CUpdateSocket::SetSendRecvEvent(CWnd *pWnd, DWORD dwTotalSize)
{
	m_pwndRecvEvent = pWnd;
	m_dwRemainTotal = m_dwTotalSize = dwTotalSize;
}