#pragma once

#include "JSONDefs.h"
#include "KingoHttp.h"

class CSearchPOI;


typedef struct
{
	CString strKeyword;
	int nDebugPrintType;
	CWnd *pTarget;
	long nUID;	
	CString strCenterPosX;
	CString strCenterPosY;
	BOOL bPhoneSearch;
	BOOL bPhoneSearchAutoComplete;
	long nApiType;
} QUERY_INFO;

typedef struct  
{
	QUERY_INFO QI;
	CSearchPOI *pSearchPOI;
} PORTAR_RESULT_RECORD;

typedef struct {
	string name_val;
	string tel_val;
	string address_val;
	string x_val;
	string y_val;
} SEARCH_RESULT_INFO;

enum { DEBUG_PRINT_LAST = 1, DEBUG_PRINT_BODY = 2};
enum { NAVER = 0, DAUM = 1, GOOGLE = 2};

class CHttpParser
{
public:
	CHttpParser(void);
	virtual ~CHttpParser(void);

	void SetCenterPos(long nPosX = 37503102, long nPosY = 127050816);
	void ThreadRefresh(CString strKeyword, CWnd *pTarget, long nUID, 
		BOOL bSearchOnlyPhone = FALSE, BOOL bPrintWholeText = FALSE);

	virtual void Refresh2(QUERY_INFO &QI);
	virtual	void Analyze2(QUERY_INFO &QI, vector<SEARCH_RESULT_INFO>& vec);
	virtual BOOL AnalyzeDetail2(QUERY_INFO &QI, SEARCH_RESULT_INFO& st);
	virtual BOOL MakePortalRecord2(QUERY_INFO &QI,SEARCH_RESULT_INFO& st);

	static int staticQueryProc(CHttpParser *app)
	{ return app->QueryProc((LPVOID)app); }
	UINT QueryProc(LPVOID lParam);

	virtual void ParseJSON4NaverLocalValues(CString strHtml, vector<SEARCH_RESULT_INFO> *vec);
protected:
	CKingoHttp m_http;
	CString m_strCenterPosX;
	CString m_strCenterPosY;
	HANDLE m_hQueryHandle;
	HANDLE m_hExitHandle;
	HANDLE m_hThreadDiedHandle;
	BOOL m_bThreadLive;
	CCriticalSection m_cs;
	QUERY_INFO m_QueryInfo;
};
