// KingoHttp.h: interface for the CKingoHttp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KINGOHTTP_H__6CC4EE56_48BC_4696_82DA_15BC7FB72F1D__INCLUDED_)
#define AFX_KINGOHTTP_H__6CC4EE56_48BC_4696_82DA_15BC7FB72F1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "bytes.h"
class CKingoHttp  
{
public:
	CKingoHttp();
	virtual ~CKingoHttp(); 

	BOOL GetResponse(BYTE** byteRet, int* nLen);
	BOOL GetResponse(BYTE** byteRet,int& nLen);
	BOOL GetResponse(CString& strRet);
	const char* GetResponse();

	CString GetError();
	CString GetError(DWORD& dwError);
	const char* GetError(DWORD* dwError);

	void SetError(CString sError, DWORD dwError=0);
	int Call();
	void Init();
	BOOL AddParamValue(CString sName,CString sValue);
	void SetConnectInfo( CString sServer,UINT uPort,CString sUrl,int nVerb=0,CString sUserName="",CString sUserPassWord="" );

	void SetSSL(BOOL bSSL) {m_bSSL= bSSL;}
	CString utf8_cp949(char* utf8);
	CString ansi_utf8(char* ansi); 

//public:
public:
	CByte m_byteRespone;

	CString	m_sError;
	DWORD   m_dwError;
	CString m_sServer;
	UINT	m_uPort;
	int		m_nVerb;
	CString m_sUrl;
	CString m_sParamData;

	CString m_sUserName;
	CString m_sUserPassWord;

	BOOL    m_bSSL;

};

#endif // !defined(AFX_KINGOHTTP_H__6CC4EE56_48BC_4696_82DA_15BC7FB72F1D__INCLUDED_)
