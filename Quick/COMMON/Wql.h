#pragma once

#define _WIN32_DCOM
#include <iostream>
//using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
# pragma comment(lib, "wbemuuid.lib")

class CWql
{
public:
	CWql(void);
	CWql(BOOL bNoCoInitialize);
	~CWql(void);

	BOOL Open(const char* sWql);
	BOOL MoveNext();
	BOOL GetValue(const char* szColName, CString& sRet);
	BOOL GetValue(const char* szColName, int& nRet, int nDefaultVal = 0);

	CString GetError() { return m_sError; }
	int     GetErrorCode() { return m_nErrorCode; }

private:
	BOOL	m_bCoInitialize;
	CString	m_sError;
	int		m_nErrorCode;

	IWbemLocator* m_pLoc;
	IWbemServices* m_pSvc;
	IEnumWbemClassObject* m_pEnumerator;
	IWbemClassObject* m_pclsObj;
	int  Init();
	void UnInit();
};
