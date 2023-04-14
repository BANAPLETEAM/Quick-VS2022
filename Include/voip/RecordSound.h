#pragma once

#include<mmsystem.h>
#include<mmreg.h>
//#include "gsm.h"

#define WM_RECORDSOUND_STARTRECORDING	WM_USER+500
#define WM_RECORDSOUND_STOPRECORDING	WM_USER+501
#define WM_RECORDSOUND_ENDTHREAD		WM_USER+502


#define SAMPLERSEC		8000
#define MAXRECBUFFER	1000
#define RECBUFFER		8000
//#define RECBUFFER		GSM_SAMPLES_PER_FRAME

// CRecordSound

class CWriteSound;
class CPlaySound;
//class CSoundStreamDlg;

class CRecordSound : public CWinThread
{
	DECLARE_DYNCREATE(CRecordSound)

//	CStdioFile		log; 
	CWnd*	pWnd4Msg;
	CWriteSound*	write; 
	CPlaySound*		play;
	CString         m_sFname;
	

	HWAVEIN m_hRecord;
	WAVEFORMATEX m_WaveFormatEx; 
	
	BOOL	m_brecording;
	int		m_isallocated;
	LPWAVEHDR rechead[MAXRECBUFFER];
	LPWAVEHDR out[MAXRECBUFFER];
	char*	  m_noise;
	int		  m_outIdx;
//	LPWAVEHDR noise;

	struct gsm_state*	m_gsm_state;
public:
	CRecordSound(CWnd* pWnd,CPlaySound* playsound,const char* sSaveFileName);           // 동적 만들기에 사용되는 protected 생성자입니다.
	CRecordSound();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CRecordSound();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	void displayError(int mmReturn,char errmsg[]);
	LPWAVEHDR  CreateWaveHeader();
	void GetDevProperty();
	void PreCreateHeader();
	BOOL IsRecording() {return m_brecording;}

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnStartRecording(WPARAM wp,LPARAM lp);
	afx_msg void OnStopRecording(WPARAM wp,LPARAM lp);
	afx_msg void OnEndThread(WPARAM wp,LPARAM lp);
	afx_msg void OnSoundData(WPARAM wParam, LPARAM lParam);
};


