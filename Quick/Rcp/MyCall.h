#pragma once

#include "Call.h"

typedef map<long, CString> KEY_PHONE_ID_MAP;

class CRcpPageCTIForm;
class CTelserverDIDRouteDlg;

class CMyCall : public CCall
{
public:
	CMyCall(void);
	~CMyCall(void);

	virtual void onError(int nCode,CString strError);
	virtual void onCallChange(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID);
	virtual void onCallInfoLog(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID,
		char* szOperator,char* szCustomer,char* szLastOperator);
	virtual void onMoniter( int nRing,int nAnswer,int nMissingCallCnt ,int nMissingCallPerMin);
	virtual void onMoniterLog(const char* szLog);
	virtual void onMoniterUserLog(const char* szLog);
	virtual void onSocketState(const char* szLog);
	virtual void onConnected();
	virtual void onDisConnected();
	virtual void onMoniterAnswerLinesChanged(const char* szKeyPhoneLines);
	virtual void onCustomerInfo(const char* szPhoneNumber,const char* strCName, const char* sDesc);
	virtual void onRecordFileNameInsertID(CString strKeyPhoneID, CString strPhoneNumber, int nInsertID);
	virtual void onDIDRouteChange(int nSubType, const char* szDID, const char* szToLine, int nUseType, const char* szDesc);

	virtual void SetQueuePause(int nPause);/*0 수신가능, 1 수신거부, 2 인터넷전화아님*/
	virtual int	 GetQueuePause();

public:
	BOOL IsValidState();
	void SetDlg(CRcpPageCTIForm* pCTIForm) {m_pDlg = pCTIForm;}
	void SetDIDRouteDlg(CTelserverDIDRouteDlg *pDlg) { m_pDIDRouteDlg = pDlg; }
	void CallInfoLog(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID,
		char* szOperator,char* szCustomer,char* szLastOperator,
		COleDateTime dtCur = COleDateTime::GetCurrentTime(),
		BOOL bRedraw = TRUE);

#ifdef _SYSMANAGER
	static void MakeOpLineMapping();
	static KEY_PHONE_ID_MAP m_mapOPLineMapping;
	CString FindOpLineMapping(CString strLine);
#endif

private:
	CRcpPageCTIForm* m_pDlg;
	CTelserverDIDRouteDlg* m_pDIDRouteDlg;
};