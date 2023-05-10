#pragma once


#include "DES.h"

#define CHALLENGESIZE32	32



class CCypherEncodeText
{
public:
	CCypherEncodeText(BYTE *pnKey = NULL);

	void Convert(char *pBuffer, long nSize, BOOL bEncode);
	void ConvertXOR(char *pBuffer, UINT nSize, BOOL bEncryption, BYTE nFirstPlus, BYTE nKey);
	void ConvertDES(char *pBuffer, UINT nSize, BOOL bEncryption, UINT nOffset = 0);
	void _ConvertDES(char *pBuffer, char *szPlain, BOOL bEncryption, UINT nOffset, UINT nCount, UINT nSampling);
	void EncodeAuthInfo(BYTE *pszSend, BYTE *pszSave, BOOL bEncode);
	void EncodeAuthInfo(BYTE *pszText, BOOL bEncode);

	void Initialize();
	void SetExternalKey(BYTE *pnKey);
	void MakeRandomBytes(BYTE *szWhere, UINT nSize);
	void ShakeBytes32(BYTE *szWhere, BOOL bReverse);

public:
	CCriticalSection m_cs;
	BOOL m_bInitDes; 
	BYTE m_ExternalKey[16];
	CDES m_des;
	static BYTE STANDARD_KEY[16];
};
