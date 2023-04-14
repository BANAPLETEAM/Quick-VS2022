#pragma once
//#include "TSocket.h"
//#include "PhoneDlg.h"
#include "afxmt.h"

#define TYPE_TEL_CLIENT					0x00000001		//기존 텔클라이언트
#define TYPE_TEL_CLIENT_ALLMESSAGE		0x00000002		//모든 클라이언트의 메세지 받음
#define TYPE_TEL_SERVER_MONITER			0x00000004		//키폰 상태 RING ANSWER HANGUP 카운트
#define TYPE_TEL_SERVER_MONITER_LOG		0x00000008		//서버 모니터링
#define TYPE_TEL_CLIENT_CUSTOMER_INFO	0x00000010		//고객정보 비동기적


#define TYPE_TEL_CLIENT_2008		TYPE_TEL_CLIENT|TYPE_TEL_CLIENT_ALLMESSAGE
/*
#ifdef EXPORT_DLL
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport) 
#endif
*/

class CTSocket;
class CTSocketSystem;
class CCall
{
public:
	CCall(void);
	~CCall(void);

	CString GetHost()
	{
		return m_strHost;
	}
	void PutStatus(const char* format, ...);
	//void ReConnect();
	/*---Telserver에 접속---------------
		sHost			: 텔서버주소
		nKeyPhoneID		: 상담원 키폰 ID(상담원이 아닌경우 음수값을 주세요
		szName			: 상담원 성명
		nType			: 클라이언트 타입
	-----------------------------------*/
	BOOL Connect(CString sHost,CString sKeyPhoneID,const char* szName,int nType);
	void Close();
	BOOL IsShutDown() { return m_bShutDown; }
	BOOL IsConnected() ;

	/*---진상고객 등록---------------
		szDenialPhoneNumber		: 진상고객 전화번호
		nDenialDurationMinute	: 등록기간 - 단위는 분단임 값이 5라면 5분동안 해당 전화번호 전화 받지 않음(전화를 끓음)
		szName					: 진상고객 이름
		szDesc					: 설명
	-----------------------------------*/
	void DenialAnswer(const char* szDenialPhoneNumber,int nDenialDurationMinute,const char* szName,const char* szDesc);


	//--전화이벤트--//
	void Answer();
	void HangUp(const char* szKeyPhoneNumber = "");
	void MakeCall(const char *szPrintCID, const char* szDialNumber);
	void Redirect_Answer(const char* szFromKeyPhoneNumber);
	void MakeCallingOrTransfer(const char* szYourKeyPhoneNumber);

	void SetClientQueuePause(int nPause);
	//void RecPlayMyKeyphone(COleDateTime dtDate, CString sFile);
	void RecPlayMyKeyphone(CString sDate, CString sFile);
	void Mute(int nMute);
	void AnswerRecPlay(CString strFileName);
	void BlindTransfer(CString strTransPhoneNumber);
	void BlindTransferHangup(CString strTransPhoneNumber);
	void DIDRoute(int nSubType, CString strDID, CString strToLine = "", BOOL bUse = FALSE, CString strDesc = "");

	void OpPickUpCall(CString strYourKeyPhoneID);
	void OpTransferCall(CString strYourKeyPhoneID);

	int GetConnectClient(CString& sConnectClient);			//현재 텔서에 접속중인 클라이언트 정보

	int GetMoniterKeyPhones(CString& sMoniterKeyPhones);	//텔서버에 지정해 놓은 키폰들 [,]로 구분된다 예)2001,2002,2003
	int GetMoniterKeyPhones(CString& sAnswerLines,CString& sARSLines,CString& sNonPRILines,CString& sRouteLines);//텔서버에 지정해 놓은 키폰들 [,]로 구분된다 예)2001,2002,2003
	int SetMoniterKeyPhones(const char* szAnswerLines,const char* szARSLines,const char* szNonPRILines,const char* szRouteLines); //텔서버에 키폰들을 지정한다.

	virtual void SetQueuePause(int nPause);
	virtual int	 GetQueuePause();

	int GetDeviceInfo(CString& snfo);						//주장치 정보, 주장치명과 CTI사용여부
	int GetVersionInfo(CString& snfo);						//서버 Version
	int GetStaringTimeInfo(CString& snfo);					//서버 시작 시간

	void SetKey(CString sKey) { m_sKey = sKey;}
	BOOL IsOnlyRecvCustomerInfo() { return m_nClientType == TYPE_TEL_CLIENT_CUSTOMER_INFO; }
	int GetMuteState();
	int GetAnswerRecPlayState();
	int GetBlindTransferState();


//*********************가상함수*****************************************/

	/*---본인 키폰 상태---------------
		nType			: 전화기 상태 ,PH_RING,PH_ANSWER,PH_HANGUP
		szPhoneNumber	: 전화번호
		szKeyPhoneID	: 키폰 ID
		szDID			: DID 또는 국선 번호
	-----------------------------------*/
	virtual void onCallChange(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID);
	virtual void onRouteCallChange(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID,const char* szInfo);
	virtual void onSetCallNumber(char* szPhoneNumber);

	/*---모니터링중인 키폰 상태---------------
	nType			: 전화기 상태 ,PH_RING,PH_ANSWER,PH_HANGUP
	szPhoneNumber	: 전화번호
	szKeyPhoneID	: 키폰 ID
	szDID			: DID 또는 국선 번호
	szOperator		: 키폰 ID 접수자
	szCustomer		: szPhoneNumber에 해당하는 고객명
	szLastOperator	: szPhoneNumber와 마지막 통화한 접수자
	-----------------------------------*/
	virtual void onCallInfoLog(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID,char* szOperator,char* szCustomer,char* szLastOperator);


	virtual void onMoniter( int nRing,int nAnswer,int nMissingCallCnt ,int nMissingCallPerMin);
	virtual void onMoniterLog(const char* szLog);

	/*---소켓상태 ---------------
	소켓 상태에 변화가 있을떄 발생
	-----------------------------------*/
	virtual void onSocketState(const char* szLog);
	virtual void onMoniterUserLog(const char* szLog);
	virtual void onMoniterAnswerLinesChanged(const char* szKeyPhoneLines);
	virtual void onMoniterLinesChanged(const char* szAnswerLines,const char* szARSLines,const char* szNonPRILines,const char* szRouteLines);


	virtual void onConnected(); 		//접속이 이루어 졌을떄
	virtual void onDisConnected();		//접속이 끓겼을경우

	/*---ERROR 발생시 ---------------
	에러나 정보 경고시  발생
	-----------------------------------*/
	virtual void onError(int nCode,CString strError){};

	/*--- 고개정보---------------------
	Ring 발생시 비동기적으로  발생
	-----------------------------------*/
	virtual void onCustomerInfo(const char* szPhoneNumber,const char* strCName, const char* sDesc){};

	/*---텔서버에서 Insert된 ----------
	녹취파일 테이블 Insert ID
	-----------------------------------*/
	virtual void onRecordFileNameInsertID(CString strKeyPhoneID, CString strPhoneNumber, int nInsertID){};

	virtual void onMuteState(int nMute){};
	virtual void onAnswerRecPlay(int nRecPlay){};
	virtual void onBlindTransfer(int nBlindTransfer){};
	virtual void onDIDRouteChange(int nSubType, const char* szDID, const char* szToLine, int nUseType, const char* szDesc){};


	//socket thread
	static int staticSocketRead(CCall *app)
	{ return app->SocketRead((LPVOID)app); }
	UINT SocketRead(LPVOID lParam);
	void SocketReadImpl();

/*
	static int staticSocketProc(CCall *app)
	{ return app->SocketProc((LPVOID)app); }
	UINT SocketProc(LPVOID lParam);
*/

	int	m_nQueuePause;
	int m_nMute;
	int m_nAnswerRecPlay;
	int m_nBlindTransfer;

protected:
	HANDLE m_hKillEvent;
	HANDLE m_hExitEvent;
	HANDLE m_hRecvEvent;

private:
	CCriticalSection m_csSocket;
	//CPhoneDlg		m_PhoneDlg;
	CTSocketSystem*	m_pSockSystem;
	CTSocket* m_pSocket;

	CString	m_sKey;
	HWND	m_hParent;

	int		m_nClientType;
	CString m_strHost;
	CString	m_sKeyPhoneID;
	CString m_strName;

	float   m_fVer;
	CString m_strCTIID;

	int		m_nPhoneState;

	BOOL	m_bShutDown;
	BOOL	m_bMakeThread;
	BOOL	m_bUserClosed;
	BOOL	m_bThreadEnd;


	BOOL ConnectSocket(CTSocket& tSocket, int nClientType, int nTryCount = 0);
	int  GetMoniterKeyPhones_Send(CTSocket& tSocket);
	int  GetMoniterKeyPhones_Receive(CTSocket& tSocket,CString& sMoniterKeyPhones);
	void WaitForServerSignal(CTSocket& socket);
};
