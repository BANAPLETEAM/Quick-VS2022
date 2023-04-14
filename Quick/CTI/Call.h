#pragma once
//#include "TSocket.h"
//#include "PhoneDlg.h"
#include "afxmt.h"

#define TYPE_TEL_CLIENT					0x00000001		//���� ��Ŭ���̾�Ʈ
#define TYPE_TEL_CLIENT_ALLMESSAGE		0x00000002		//��� Ŭ���̾�Ʈ�� �޼��� ����
#define TYPE_TEL_SERVER_MONITER			0x00000004		//Ű�� ���� RING ANSWER HANGUP ī��Ʈ
#define TYPE_TEL_SERVER_MONITER_LOG		0x00000008		//���� ����͸�
#define TYPE_TEL_CLIENT_CUSTOMER_INFO	0x00000010		//������ �񵿱���


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
	/*---Telserver�� ����---------------
		sHost			: �ڼ����ּ�
		nKeyPhoneID		: ���� Ű�� ID(������ �ƴѰ�� �������� �ּ���
		szName			: ���� ����
		nType			: Ŭ���̾�Ʈ Ÿ��
	-----------------------------------*/
	BOOL Connect(CString sHost,CString sKeyPhoneID,const char* szName,int nType);
	void Close();
	BOOL IsShutDown() { return m_bShutDown; }
	BOOL IsConnected() ;

	/*---����� ���---------------
		szDenialPhoneNumber		: ����� ��ȭ��ȣ
		nDenialDurationMinute	: ��ϱⰣ - ������ �д��� ���� 5��� 5�е��� �ش� ��ȭ��ȣ ��ȭ ���� ����(��ȭ�� ����)
		szName					: ����� �̸�
		szDesc					: ����
	-----------------------------------*/
	void DenialAnswer(const char* szDenialPhoneNumber,int nDenialDurationMinute,const char* szName,const char* szDesc);


	//--��ȭ�̺�Ʈ--//
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

	int GetConnectClient(CString& sConnectClient);			//���� �ڼ��� �������� Ŭ���̾�Ʈ ����

	int GetMoniterKeyPhones(CString& sMoniterKeyPhones);	//�ڼ����� ������ ���� Ű���� [,]�� ���еȴ� ��)2001,2002,2003
	int GetMoniterKeyPhones(CString& sAnswerLines,CString& sARSLines,CString& sNonPRILines,CString& sRouteLines);//�ڼ����� ������ ���� Ű���� [,]�� ���еȴ� ��)2001,2002,2003
	int SetMoniterKeyPhones(const char* szAnswerLines,const char* szARSLines,const char* szNonPRILines,const char* szRouteLines); //�ڼ����� Ű������ �����Ѵ�.

	virtual void SetQueuePause(int nPause);
	virtual int	 GetQueuePause();

	int GetDeviceInfo(CString& snfo);						//����ġ ����, ����ġ��� CTI��뿩��
	int GetVersionInfo(CString& snfo);						//���� Version
	int GetStaringTimeInfo(CString& snfo);					//���� ���� �ð�

	void SetKey(CString sKey) { m_sKey = sKey;}
	BOOL IsOnlyRecvCustomerInfo() { return m_nClientType == TYPE_TEL_CLIENT_CUSTOMER_INFO; }
	int GetMuteState();
	int GetAnswerRecPlayState();
	int GetBlindTransferState();


//*********************�����Լ�*****************************************/

	/*---���� Ű�� ����---------------
		nType			: ��ȭ�� ���� ,PH_RING,PH_ANSWER,PH_HANGUP
		szPhoneNumber	: ��ȭ��ȣ
		szKeyPhoneID	: Ű�� ID
		szDID			: DID �Ǵ� ���� ��ȣ
	-----------------------------------*/
	virtual void onCallChange(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID);
	virtual void onRouteCallChange(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID,const char* szInfo);
	virtual void onSetCallNumber(char* szPhoneNumber);

	/*---����͸����� Ű�� ����---------------
	nType			: ��ȭ�� ���� ,PH_RING,PH_ANSWER,PH_HANGUP
	szPhoneNumber	: ��ȭ��ȣ
	szKeyPhoneID	: Ű�� ID
	szDID			: DID �Ǵ� ���� ��ȣ
	szOperator		: Ű�� ID ������
	szCustomer		: szPhoneNumber�� �ش��ϴ� ����
	szLastOperator	: szPhoneNumber�� ������ ��ȭ�� ������
	-----------------------------------*/
	virtual void onCallInfoLog(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID,char* szOperator,char* szCustomer,char* szLastOperator);


	virtual void onMoniter( int nRing,int nAnswer,int nMissingCallCnt ,int nMissingCallPerMin);
	virtual void onMoniterLog(const char* szLog);

	/*---���ϻ��� ---------------
	���� ���¿� ��ȭ�� ������ �߻�
	-----------------------------------*/
	virtual void onSocketState(const char* szLog);
	virtual void onMoniterUserLog(const char* szLog);
	virtual void onMoniterAnswerLinesChanged(const char* szKeyPhoneLines);
	virtual void onMoniterLinesChanged(const char* szAnswerLines,const char* szARSLines,const char* szNonPRILines,const char* szRouteLines);


	virtual void onConnected(); 		//������ �̷�� ������
	virtual void onDisConnected();		//������ ���������

	/*---ERROR �߻��� ---------------
	������ ���� ����  �߻�
	-----------------------------------*/
	virtual void onError(int nCode,CString strError){};

	/*--- ������---------------------
	Ring �߻��� �񵿱�������  �߻�
	-----------------------------------*/
	virtual void onCustomerInfo(const char* szPhoneNumber,const char* strCName, const char* sDesc){};

	/*---�ڼ������� Insert�� ----------
	�������� ���̺� Insert ID
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
