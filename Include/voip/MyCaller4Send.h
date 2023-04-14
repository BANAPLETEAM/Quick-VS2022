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
	virtual void onConnected(); 		//������ �̷�� ������
	virtual void onDisConnected();		//������ ���������
	virtual void onError(int nCode,CString sError);
	virtual void onTextData(LPVTMSG  p);
	virtual void onVoiceData(LPVTMSG p);

private:
	CWnd* m_pDlg;
};
