#pragma once


#define WM_MY_CALL_MESSAGE (WM_USER + 100)

class CRcpPageCTIForm;

class CMyCallMessage
{
public:
	enum 
	{ 
		SET_CALL_NUMBER = 0,
		CALL_CHANGE,
		SET_CALL_LIST,
		CUSTOMER_INFO,
		REFRESH_QUEUE,
		INTERNAL_CALL_POPUP
	};

	CMyCallMessage(CRcpPageCTIForm *pDlg);
	~CMyCallMessage();

	CRcpPageCTIForm *m_pDlg;
	int m_nType;
	char *m_szPhoneNumber;
	char *m_szKeyPhoneID;
	char *m_szDID;
	char *m_szOperator;
	char *m_szCustomer;
	char *m_szDesc;
	COleDateTime m_dtCur;
	BOOL m_bRedraw;

	void CallChange(int nType, char* szPhoneNumber, char* szKeyPhoneID, char* szDID);
	void SetCallNumber(char *szPhoneNumber);
	void SearchRecvCID(char *szPhoneNumber);
	void PopupRcpDlg(char *szPhoneNumber, char *szKeyPhoneID, char *szDID);
	void ClearRecvCIDFilter();
	void SetCallList(int nType, char* szPhoneNumber, char* szKeyPhoneID,
					char* szDID, char* szOperator, char* szCustomer,
					COleDateTime dtCur,
					BOOL bRedraw);
	void CustomerInfo(char* szPhoneNumber, char* strCName, char* sDesc);
	void RefreshQueueState();
	void InternalCallPopup(char* szPhoneNumber, char* szOperator, char* szKeyPhoneID);
	LRESULT Process(UINT nMsg);

protected:
	LRESULT SendMessage(UINT nMsg);
};

