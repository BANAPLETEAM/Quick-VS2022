#pragma once

#define WM_PLAYSOUND_STARTPLAYING WM_USER+600
#define WM_PLAYSOUND_STOPPLAYING WM_USER+601
#define WM_PLAYSOUND_PLAYBLOCK WM_USER+602
#define WM_PLAYSOUND_ENDTHREAD  WM_USER+603

#define SOUNDSAMPLES 1000
#define PLAYBUFFER   2000
#define SAMPLEPSEC   8000


#include<afxmt.h>
#include<mmsystem.h>


// CPlaySound

class CPlaySound : public CWinThread
{
	DECLARE_DYNCREATE(CPlaySound)

public:
	CPlaySound();           // 동적 만들기에 사용되는 protected 생성자입니다.
	CPlaySound(CWnd* pWnd);
	virtual ~CPlaySound();

	WAVEFORMATEX m_WaveFormatEx;
	BOOL		m_bPlaying;
	HWAVEOUT	m_hPlay;
//	CStdioFile	log;
	CWnd*		m_pWnd4Msg;

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	void displayError(int code,char []);
	BOOL IsPlaying() {return m_bPlaying;}
//	void displayHeader(LPWAVEHDR lphdr);
//	LPWAVEHDR CreateWaveHeader(CString mesg);
//	void ProcessSoundData(short int *sound, DWORD dwSamples);

	void PlaySound(LPWAVEHDR lpHdr);
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnStartPlaying(WPARAM wParam, LPARAM lParam);
	afx_msg void OnStopPlaying(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEndPlaySoundData(WPARAM wParam, LPARAM lParam);
	afx_msg void OnWriteSoundData(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEndThread(WPARAM wParam, LPARAM lParam);

};


