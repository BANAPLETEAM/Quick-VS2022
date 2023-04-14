#pragma once
#include "basecaller.h"
class CPlaySound;
//class CSoundStreamDlg;

#define SAMPLERSEC		8000
#define MAXRECBUFFER	500
//#define RECBUFFER		800

#define MM_TEXT_DATA	WM_USER+801
#define MM_VOICE_DATA	WM_USER+802
class CMyCallerRecv :
	public CBaseCaller
{
public:
	CMyCallerRecv(CWnd* pDlg);
	~CMyCallerRecv(void);

	CMyCallerRecv(CWnd* pDlg,CPlaySound* play);

public:
	virtual void onConnected(); 		//접속이 이루어 졌을떄
	virtual void onDisConnected();		//접속이 끓겼을경우
	virtual void onError(int nCode,CString sError);
	virtual void onTextData(LPVTMSG  p);
	virtual void onVoiceData(LPVTMSG p);

	void*	CreateWaveHeader();
private:
	CWnd*		m_pDlg;
	CPlaySound* m_play;
	int			m_nRechead;
	void*		m_Rechead[MAXRECBUFFER];
};
