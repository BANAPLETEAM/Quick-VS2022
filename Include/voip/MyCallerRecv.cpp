#include "StdAfx.h"
//#include "Sound.h"
#include "MyCallerRecv.h"
#include "PlaySound.h"
//#include "SoundDlg.h"

CMyCallerRecv::CMyCallerRecv(CWnd* pDlg)
{
	m_pDlg = pDlg;
	m_nRechead = -1;
	for(int i = 0 ;i < MAXRECBUFFER ; i++ ) m_Rechead[i] = CreateWaveHeader();

}

CMyCallerRecv::CMyCallerRecv(CWnd* pDlg, CPlaySound* play)
{
	m_pDlg = pDlg;
	m_play = play;
	m_nRechead = -1;
	for(int i = 0 ;i < MAXRECBUFFER ; i++ ) m_Rechead[i] = CreateWaveHeader();

}

CMyCallerRecv::~CMyCallerRecv(void)
{
	Close();
	LPWAVEHDR lpHdr;
	for(int i = 0 ;i < MAXRECBUFFER ; i++ )
	{
		lpHdr = (LPWAVEHDR) m_Rechead[i];
		if( lpHdr->lpData ) delete[] lpHdr->lpData;
		delete lpHdr;
	}
}

#define RECBUFFER4RECV 16000
void* CMyCallerRecv::CreateWaveHeader()
{
	LPWAVEHDR lpHdr = new WAVEHDR;
	
	if(lpHdr==NULL)
	{
		return NULL;
	}
	
	ZeroMemory(lpHdr, sizeof(WAVEHDR));
	char* lpByte = new char[RECBUFFER4RECV];//m_WaveFormatEx.nBlockAlign*SOUNDSAMPLES)];
	
	if(lpByte==NULL)
	{
		return NULL;
	}
	lpHdr->lpData =  lpByte;
	lpHdr->dwBufferLength =RECBUFFER4RECV;   // (m_WaveFormatEx.nBlockAlign*SOUNDSAMPLES);
	return lpHdr;
}

void CMyCallerRecv::onConnected()
{	
	m_pDlg->SendMessage(UM_CONNECTED,(WPARAM)MT_USAGE_RECV,(LPARAM)MT_USAGE_RECV);
//	m_pDlg->SetLog("CMyCallerRecv connected\r\n");
}
void CMyCallerRecv::onDisConnected()
{
	m_pDlg->SendMessage(UM_DISCONNECTED,(WPARAM)MT_USAGE_RECV,(LPARAM)MT_USAGE_RECV);
}
void CMyCallerRecv::onError(int nCode,CString sError)
{

}
void CMyCallerRecv::onTextData(LPVTMSG  p)
{
	
	m_pDlg->SendMessage(MM_TEXT_DATA,0,(LPARAM)p);

/*

*/
}

#ifdef __cplusplus
extern "C" {
#endif

extern int WINAPI uncompress (unsigned char *dest,   unsigned long *destLen,
                                   const unsigned char *source, unsigned long sourceLen);
#ifdef __cplusplus
}
#endif


void CMyCallerRecv::onVoiceData(LPVTMSG p)
{

/*
	CString sLog;
	sLog.Format("onVoiceData:m_sToID = %s,Len=%d\r\n",p->m_sToID,p->m_lLength);
	m_pDlg->SetLog(sLog);

	m_pDlg->SetCommUser(p->m_sToID);
*/
	m_pDlg->SendMessage(MM_VOICE_DATA,0,(LPARAM)p);

	m_nRechead = (m_nRechead+1) % MAXRECBUFFER;
	LPWAVEHDR lpHdr = (LPWAVEHDR)m_Rechead[m_nRechead];
	lpHdr->dwFlags	= 0;




	lpHdr->dwBufferLength = RECBUFFER4RECV;
	unsigned long lDest = lpHdr->dwBufferLength;
	DWORD dwTick = ::GetTickCount();
	int nRet  = uncompress((unsigned char*)lpHdr->lpData,&lDest,p->m_pData,p->m_lLength);
	long lgap = ::GetTickCount() - dwTick;
	lpHdr->dwBufferLength = lDest;

	
/*

	LPWAVEHDR lpHdr = new WAVEHDR;
	if(lpHdr==NULL)		return ;
	ZeroMemory(lpHdr, sizeof(WAVEHDR));

	char* lpByte = new char[p->m_lLength];
	lpHdr->lpData			= lpByte;
	memcpy(lpHdr->lpData,p->m_pData,p->m_lLength);
	lpHdr->dwBufferLength	= p->m_lLength;
	lpHdr->dwFlags			= 0;
*/
	m_play->PlaySound(lpHdr);

//	delete lpHdr;
}