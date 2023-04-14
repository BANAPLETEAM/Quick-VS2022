#pragma once
#include "basecaller.h"
//class	CSoundStreamDlg;

class CMyCaller4Send :
	public CBaseCaller
{
public:
	CMyCaller4Send(CWnd* pDlg);
	~CMyCaller4Send(void);

public:
	virtual void onConnected(); 		//접속이 이루어 졌을떄
	virtual void onDisConnected();		//접속이 끓겼을경우
	virtual void onError(int nCode,CString sError);
	virtual void onTextData(LPVTMSG  p);
	virtual void onVoiceData(LPVTMSG p);

private:
	CWnd* m_pDlg;
};
