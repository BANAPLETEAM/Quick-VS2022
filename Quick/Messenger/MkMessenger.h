#pragma once


typedef struct {
	UINT nCompanyCode;
	UINT nUserCode;
	CString strCompanyName;
	CString strBranchName;
	CString strUserName;
	UINT nShareCode1;
	UINT nShareCode2;
	UINT nShareCode3;
	UINT nShareCode4;
	UINT nShareCode5;
	UINT nShareCode6;
	UINT nShareCode7;
	UINT nShareCode8;
	UINT nShareCode9;
	UINT nShareCode10;
	UINT nMsgGroupCode;
	CString strMsgServerAddr;
	UINT nMsgServerPort;
	BOOL bIdle;
	BOOL bManager;
	long nDisplayType;
} MESSENGER_SET_INFO;


typedef struct 
{
	char szCompanyName[20];
	int nCompanyCode;
	int nMNo;
	char szName[20];
	int nShareCompanyCode;
	int nMsgGroupCode;
} MessengerInfo;


class CNewMsgDlg;

typedef struct 
{
	int nCompanyCode;
	int nMNo;
	int nType;
	int nSendType;
	CNewMsgDlg *pDlg;
} MSG_DLG_INFO;


typedef map<pair<pair<long, long>,long>, MSG_DLG_INFO> MSG_DLG_MAP;

#define WM_SET_MSG_STATE		WM_USER + 500
#define WM_SET_INTERCALL_STATE		WM_USER + 501

#define MAKE_MSG_KEY(nCompany, nMNo, nClientType) make_pair(make_pair(nCompany, nMNo), nClientType)
#define MySetState(msg)		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_SET_MSG_STATE, (WPARAM)msg, 0)
#define MySetStateNew(msg)		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_SET_MSG_STATE, (WPARAM)msg, 1)
#define MyIntercallState(msg)		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_SET_INTERCALL_STATE, (WPARAM)msg, 0)
#define MyIntercallStateNew(msg)		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_SET_INTERCALL_STATE, (WPARAM)msg, 1)


inline static void STRCAT2(char *delimiter, char *dst, ...)
{
	char *src;

	va_list vl;
	va_start(vl, dst);

	while(strncmp((src = va_arg(vl, char*)), VL_END, strlen(VL_END)) != 0)
	{
		strcat(dst, src);
		strcat(dst, delimiter);
	}

	va_end(vl);
}


inline static int STRTOK2(char *delimiter, char *src, int nStart, ...)
{
	char *dst;
	int pos = nStart;
	int len = (int)strlen(src);
	int i;

	va_list vl;
	va_start(vl, src);
	i = va_arg(vl, int);

	while(strncmp((dst = va_arg(vl, char*)), VL_END, strlen(VL_END)) != 0)
	{
		if(i == len) return 0;
		for(i = pos; i < len; i++)
		{
			if(!strncmp(&src[i], delimiter, strlen(delimiter)))
			{
				memcpy(dst, &src[pos], i - pos);
				dst[i - pos] = '\0';
				pos = i + strlen(delimiter);
				break;
			}
		}
	}

	va_end(vl);
	return pos == nStart ? 0 : pos ;
}

enum { TYPE_SINGLE = 0, TYPE_COMPANY, TYPE_SHARECODE };



class CNewConnListDlg;
class CMkDatabase;
class CNotifierContainer;
class CTaskbarNotifier;

	
// CMkMessenger

class CMkMessenger : public CWnd
{
	DECLARE_DYNAMIC(CMkMessenger)

public:
	CMkMessenger(CWnd *pParent);
	virtual ~CMkMessenger();

protected:
	DECLARE_MESSAGE_MAP()

	//{{AFX
	afx_msg LONG OnAsyncEvent(SOCKET wSocket, LPARAM lParam);
	//afx_msg LONG OnCloseMsgConnListDlg(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnCloseMsgDlg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX

protected:
	void OnMsgDataRead(QPACKET *p);

protected:
	CMkDatabase *m_pMsgClient;
	CNewConnListDlg *m_pNewConnListDlg;
	MSG_DLG_MAP m_MsgDlgMap; 
	int m_nCompanyCode;
	MESSENGER_SET_INFO *m_pmi;
	CNotifierContainer *m_pnfc;
	CTaskbarNotifier *m_pnfcAlloc;
	BOOL m_bRecvIntercall;
	BOOL m_bRecvAllocMsg;
	BOOL m_bRecvRiderPosMsg;
	CWnd *m_pwndAllocPost;
	DWORD *m_pdwInputTime;
	BOOL m_bSeatAwayState;
	BOOL m_bConnectState;


public:
	static int staticMessengerProc(CMkMessenger *app)
		{ return app->MessengerProc((LPVOID)app); }
	UINT MessengerProc(LPVOID lParam);

	void SetMessengerInfo(MESSENGER_SET_INFO *pmi) { m_pmi = pmi; }
	BOOL Connect();
	void ShowMsgConnList();
	CNewMsgDlg* ShowMsgDlg(CWnd *pParent, 
					CString strMsg, 
					CString strCompany, 
					CString strMNo, 
					CString strIntercall,
					CString strCompanyName,
					CString strName,
					BOOL bHide = FALSE,
					int nSendType = TYPE_SINGLE,
					BOOL bNoFocus = FALSE,
					BOOL bHideWithMsg = FALSE);

	void SetNotiferContainer(CNotifierContainer *pnfc) { m_pnfc = pnfc; }
	void Close();

	CMkDatabase *GetDatabase() { return m_pMsgClient;}
	long SetRecvIntercall(BOOL bRecv, BOOL bJustSend = TRUE);
	BOOL SetRecvAllocMsg(BOOL bRecv, BOOL bJustSend = TRUE);
	void SetRecvRiderPosMsg(BOOL bRecv, BOOL bJustSend = TRUE);
	CNewConnListDlg *GetConnListDlg() { return m_pNewConnListDlg; }

	void SetAllocPostHandle(CWnd *pWnd) { m_pwndAllocPost = pWnd; }

	MSG_DLG_MAP::iterator FindDlgMap(int nCompany, int nMNo, BOOL bIntercall, int nSendType);
	MSG_DLG_MAP::iterator FindDlgMap(char *szCompany, char *szMNo, char *szIntercall, int nSendType);
	BOOL CheckString(char *szMsg, char *szFind);
	void MyPlaySound(LPCSTR pszSound = "");
	BOOL GetRecvRiderPosMsg() { return m_bRecvRiderPosMsg; }
	void ClearMap();
	void SetInputTimeVar(DWORD *pdwInputTime) { m_pdwInputTime = pdwInputTime; }
	MESSENGER_SET_INFO* GetUserInfo() { return m_pmi;}

public:
	virtual BOOL OnRecvUserProtocol(long nCompany, long nMNo, BOOL bIntercall, 
					char *szCompanyName, char *szName, char *szMsg);
	virtual BOOL OnRecvOKProtocol(QPACKET *p);
	virtual BOOL SendInnerMsg(int nType, CString strMsg, long nTargetCompany, long nTargetRNo = 0);

};














