// PlaySound.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include <afxwin.h>
#include <mmreg.h>
//#include "Sound.h"
#include "PlaySound.h"



// CPlaySound

IMPLEMENT_DYNCREATE(CPlaySound, CWinThread)

CPlaySound::CPlaySound()
{
}

CPlaySound::CPlaySound(CWnd* pWnd)
{
//	BOOL bRet = log.Open("playfile.txt",CFile::modeCreate | CFile::modeWrite);
	
	m_pWnd4Msg=pWnd;

	memset(&m_WaveFormatEx,0x00,sizeof(m_WaveFormatEx));
	m_WaveFormatEx.wFormatTag = WAVE_FORMAT_PCM;
	m_WaveFormatEx.nChannels = 1;
	m_WaveFormatEx.wBitsPerSample = 8;
	m_WaveFormatEx.cbSize = 0;
	m_WaveFormatEx.nSamplesPerSec = SAMPLEPSEC;
	m_WaveFormatEx.nAvgBytesPerSec = SAMPLEPSEC ;
	m_WaveFormatEx.nBlockAlign = 1;

	m_bPlaying = FALSE;
	
//	log.WriteString("\n In the constructor of Play sound");
}

CPlaySound::~CPlaySound()
{
//	log.Close();
}

BOOL CPlaySound::InitInstance()
{
	// TODO: 여기에서 각 스레드에 대한 초기화를 수행합니다.
	return TRUE;
}

int CPlaySound::ExitInstance()
{
	// TODO: 여기에서 각 스레드에 대한 정리를 수행합니다.
	return CWinThread::ExitInstance();
}

void CPlaySound::displayError(int code,char mesg[])
{
	char errorbuffer[MAX_PATH];
	char errorbuffer1[MAX_PATH];
	waveOutGetErrorText( code,errorbuffer,MAX_PATH);
	sprintf_s(errorbuffer1,sizeof(errorbuffer1),"PLAY : %s :%x:%s",mesg,code,errorbuffer);
	AfxMessageBox(errorbuffer1);  
}


BEGIN_MESSAGE_MAP(CPlaySound, CWinThread)
	ON_THREAD_MESSAGE(WM_PLAYSOUND_STARTPLAYING, OnStartPlaying)
	ON_THREAD_MESSAGE(WM_PLAYSOUND_STOPPLAYING, OnStopPlaying)
	ON_THREAD_MESSAGE(WM_PLAYSOUND_PLAYBLOCK, OnWriteSoundData)
	ON_THREAD_MESSAGE(MM_WOM_DONE, OnEndPlaySoundData)
	ON_THREAD_MESSAGE(WM_PLAYSOUND_ENDTHREAD,OnEndThread)
END_MESSAGE_MAP()


// CPlaySound 메시지 처리기입니다.

void CPlaySound::OnStartPlaying(WPARAM wParam, LPARAM lParam)
{
	MMRESULT mmReturn = 0;

	if(m_bPlaying==TRUE)		return ;

//	log.WriteString("\n Starting playing");
	
		// open wavein device
	 mmReturn = ::waveOutOpen( &m_hPlay, WAVE_MAPPER,
		&m_WaveFormatEx, ::GetCurrentThreadId(), 0, CALLBACK_THREAD);
		
	/*//For GSM compression use this code
		  mmReturn = ::waveOutOpen( &m_hPlay, WAVE_MAPPER,
			&m_WaveFormatEx.wfx, ::GetCurrentThreadId(), 0, CALLBACK_THREAD);
	*/	

	if(mmReturn )
	{
		displayError(mmReturn,"PlayStart");	
	}
	else
	{	
		m_bPlaying = TRUE;
		DWORD volume=0xffffffff;	//볼륨 최대 크기
		char str[100];
			
		if(!waveOutSetVolume(m_hPlay,volume))
		{
			volume=0;
			if(!waveOutGetVolume(m_hPlay,&volume))
			{
				wsprintf(str,"\n Volume is  %lx",volume);
//				log.WriteString(str);
			}						
		}	
	}					
	return ;
}

void CPlaySound::OnStopPlaying(WPARAM wParam, LPARAM lParam)
{
	
	MMRESULT mmReturn = 0;

	if(m_bPlaying==FALSE)	return ;
//    log.WriteString("\n Stop playing");
		
		
	mmReturn = ::waveOutReset(m_hPlay);	
	if(!mmReturn)
	{
		m_bPlaying = FALSE;
		Sleep(500);
		mmReturn = ::waveOutClose(m_hPlay);
	}
	return ;
}

void CPlaySound::OnEndPlaySoundData(WPARAM wParam, LPARAM lParam)
{
	LPWAVEHDR lpHdr = (LPWAVEHDR) lParam;
	
	if(lpHdr)
	{
		::waveOutUnprepareHeader(m_hPlay, lpHdr, sizeof(WAVEHDR));		
	}

	return;
}


////////////////////////////////////////////////////
//  Display calls this function using PostThreadMesssage
//  whenever voice data is received.....
//
void CPlaySound::PlaySound(LPWAVEHDR lpHdr)
{
	MMRESULT mmResult = 0;
//	log.WriteString("\n Playing data ");
	if(lpHdr==NULL)		return;
		
	if(m_bPlaying)
	{		
		mmResult = ::waveOutPrepareHeader(m_hPlay, lpHdr, sizeof(WAVEHDR));
				
		if(mmResult)
		{
//			log.WriteString("\nError while preparing header");
			return;
		}
	
		mmResult = ::waveOutWrite(m_hPlay, lpHdr, sizeof(WAVEHDR));
		
		if(mmResult)
		{
//			log.WriteString("\nError while writing to device");
			return;			
		}

		mmResult = ::waveOutUnprepareHeader(m_hPlay, lpHdr, sizeof(WAVEHDR));
	}

	return;
}

void CPlaySound::OnWriteSoundData(WPARAM wParam, LPARAM lParam)
{
	MMRESULT mmResult = 0;
	
	LPWAVEHDR lpHdr=(LPWAVEHDR)lParam;

	PlaySound(lpHdr);
}

///////////////////////////////
//  Quit the thread
//
//

void CPlaySound::OnEndThread(WPARAM wParam, LPARAM lParam)
{
	
	if(m_bPlaying==TRUE)
	OnStopPlaying(0,0);
	
//	log.WriteString("\nEnding the play device");

	::PostQuitMessage(0);
//	return TRUE;
	return;
}
