
#include "stdafx.h"
#include "CypherEncodeText.h"
#include "md5.h"
#include "process.h"
#include "MKLock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define	XOR_KEY1_1			78
#define XOR_KEY1_2			12
#define XOR_KEY2_1			29
#define XOR_KEY2_2			18
#define DES_CHALLENGE_BYTE	8
#define DES_SECOND_OFFSET	4
#define DES_SMAPLING_GAP	8	//이 값으로 CPU부하를 조정할 수 있음


BYTE CCypherEncodeText::STANDARD_KEY[16] = {0x6a,0x10,0x6a,0x00,0x8d,0x45,0xc4,0x50,0xe8,0xec,0x89,0xff,0xff,0x83,0xc4,0x0c};


CCypherEncodeText::CCypherEncodeText(BYTE *pnKey)
{
	m_bInitDes = FALSE;

	if(pnKey && pnKey[0] > 0 && pnKey[1] > 0)
	{
		memcpy(m_ExternalKey, pnKey, sizeof(m_ExternalKey));	
	}
	else
	{
#ifdef _MKSERVER 
		memcpy(m_ExternalKey, STANDARD_KEY, sizeof(m_ExternalKey));
#else
		ZeroMemory(m_ExternalKey, sizeof(m_ExternalKey));
#endif
	}

}


void CCypherEncodeText::SetExternalKey(BYTE *pnKey)
{
	if(pnKey && pnKey[0] > 0 && pnKey[1] > 0)
	{
		m_bInitDes = FALSE;
		memcpy(m_ExternalKey, pnKey, sizeof(m_ExternalKey));	
		Initialize();
	}
}

void CCypherEncodeText::Initialize()
{
	CMkLock lock(m_cs);

	if(!m_bInitDes)
	{
		MD5_CTX ctx;
		BYTE result[16];
		BYTE data_key[] = 
		{
			0x83,0xc4,0x0c,0xc7,0x05,0x3c,0x46,0x3a,0x01,0x01,0x00,0x00,0x00,0xb9,0x40,0x46,	//마지막 반복
			0x8d,0x85,0x64,0xff,0xff,0xff,0x50,0xe8,0x31,0x5e,0xff,0xff,0x83,0xc4,0x04,0x6a,
			0x10,0x8d,0x45,0xdc,0x50,0x8d,0x8d,0x64,0xff,0xff,0xff,0x51,0xe8,0x18,0x6c,0xff,
			0xff,0x83,0xc4,0x0c,0x8d,0x85,0x64,0xff,0xff,0xff,0x50,0x8d,0x4d,0xc4,0x51,0xe8,
			0x6f,0x66,0xff,0xff,0x83,0xc4,0x08,0x83,0x3d,0x3c,0x46,0x3a,0x01,0x00,0x75,0x37,
			0xb9,0x40,0x46,0x3a,0x01,0xe8,0x56,0x73,0xff,0xff,0x83,0x3d,0x3c,0x46,0x3a,0x01,
			0x00,0x75,0x1a,0x6a,0x00,0x6a,0x00,0x8d,0x45,0xdc,0x50,0xe8,0xc5,0x75,0xff,0xff,
			0x83,0xc4,0x0c,0xc7,0x05,0x3c,0x46,0x3a,0x01,0x01,0x00,0x00,0x00,0xb9,0x40,0x46,
		};

		memcpy(data_key, m_ExternalKey, sizeof(m_ExternalKey));

		MD5Init(&ctx);
		MD5Update(&ctx , data_key, sizeof(data_key));
		MD5Final(result, &ctx);

		result[7] = result[5] ^ result[1];
		result[1] = result[11] ^ result[3];
		result[3] = result[9] ^ result[10];
		result[5] = result[7] ^ result[8];

		m_des.Init((CHAR*)result, 0, false);
		m_bInitDes = TRUE;
	}
}

void CCypherEncodeText::Convert(char *pBuffer, long nSize, BOOL bEncode)
{
	Initialize();

	if(bEncode)
	{
		ConvertXOR(pBuffer, nSize, TRUE, XOR_KEY1_1, XOR_KEY1_2);
		ConvertDES(pBuffer, nSize, TRUE);
		ConvertXOR(pBuffer, nSize, TRUE, XOR_KEY2_1, XOR_KEY2_2);
		ConvertDES(pBuffer, nSize, FALSE, DES_SECOND_OFFSET);
	}
	else
	{
		ConvertDES(pBuffer, nSize, TRUE, DES_SECOND_OFFSET);
		ConvertXOR(pBuffer, nSize, FALSE, XOR_KEY2_1, XOR_KEY2_2);
		ConvertDES(pBuffer, nSize, FALSE);
		ConvertXOR(pBuffer, nSize, FALSE, XOR_KEY1_1, XOR_KEY1_2);
	}
}

void CCypherEncodeText::ConvertXOR(char *pBuffer, UINT nSize, BOOL bEncryption, BYTE nFirstPlus, BYTE nKey)
{
	char szPre, szPre2;

	if(bEncryption)
	{
		szPre = pBuffer[0];
		pBuffer[0] = (pBuffer[0] + nFirstPlus) ^ nKey;

		for(int i = 1; i < nSize; i++)
		{
			szPre2 = pBuffer[i];
			pBuffer[i] = pBuffer[i] ^ (szPre + i);
			szPre = szPre2;
		}
	}
	else
	{
		pBuffer[0] = (pBuffer[0] ^ nKey) - nFirstPlus;

		for(int i = 1; i < nSize; i++)
			pBuffer[i] = pBuffer[i] ^ (pBuffer[i-1] + i);
	}
}

void CCypherEncodeText::ConvertDES(char *pBuffer, UINT nSize, BOOL bEncryption, UINT nOffset)
{
	UINT nPos = 0;
	UINT m_nPreIdx = 0;
	char szPlain[8];

	if(nSize - nOffset <= DES_CHALLENGE_BYTE)
		return;

	for(int i = nOffset; i < nSize; i += DES_SMAPLING_GAP)
	{
		szPlain[nPos] = pBuffer[i];

		if(++nPos == DES_CHALLENGE_BYTE)
		{
			_ConvertDES(pBuffer, szPlain, bEncryption, i, nPos, DES_SMAPLING_GAP);
			nPos = 0;
			m_nPreIdx = i;
		}
	}
  
	if(nPos > 0)
	{
		UINT nRemainCount = nSize - m_nPreIdx - 1;
		UINT nSampling = nRemainCount / 8;
		UINT nFillCount = DES_CHALLENGE_BYTE - nPos;
		UINT nPos2 = 0;
		int k = 0;

		for(k = nSize - nRemainCount; k < nSize; k += nSampling)
		{
			szPlain[nPos2] = pBuffer[k];
			if(++nPos2 == DES_CHALLENGE_BYTE) break;
		}

		_ConvertDES(pBuffer, szPlain, bEncryption, k, nPos2, nSampling);
	}
}

void CCypherEncodeText::_ConvertDES(char *pBuffer, char *szPlain, BOOL bEncryption, UINT nOffset, UINT nCount, UINT nSampling)
{
	m_des.Ecb(bEncryption, szPlain, 0, szPlain, 0);

	for(int c = DES_CHALLENGE_BYTE - nCount; c < DES_CHALLENGE_BYTE; c++)
		pBuffer[nOffset - c * nSampling] = szPlain[DES_CHALLENGE_BYTE -1 - c];
}

void CCypherEncodeText::MakeRandomBytes(unsigned char *szWhere, UINT nSize)
{
	int i;
	static unsigned int seed;
	seed += (unsigned int) time(0) + _getpid() + _getpid() * 987654;

	srand(seed);
	for(i = 0; i < nSize; i++) 
		szWhere[i] = (char)(rand() % 128);
}

void CCypherEncodeText::ShakeBytes32(BYTE *szWhere, BOOL bReverse)
{
	BYTE nShuffle[] = {	 1, 31,  8, 17,  7, 27,  5,  3, 18, 30,
						11, 29, 13, 23, 25, 16,  4,  9, 19, 22,
						21, 20, 14, 28, 15, 26,  6, 24, 12, 10,
						2,  0};
	if(bReverse)
	{
		for(int i = 0; i < CHALLENGESIZE32 / 2; i++)
		{
			BYTE nTemp = nShuffle[i];
			nShuffle[i] = nShuffle[CHALLENGESIZE32 - i - 1];
			nShuffle[CHALLENGESIZE32 - i - 1] = nTemp;
		}
	}

	BYTE nFirst = szWhere[nShuffle[0]];

	int i = 0;
	for(i = 1; i < CHALLENGESIZE32; i++) 
		szWhere[nShuffle[i - 1]] = szWhere[nShuffle[i]];

	szWhere[nShuffle[i - 1]] = nFirst;
}

void CCypherEncodeText::EncodeAuthInfo(BYTE *pszSend, BYTE *pszSave, BOOL bEncode)
{
	//pszSend의 변화
	//서버에서 ENC, 클라이언트에서 DEC, DEC  -> 결국 DEC된 상태에서 서버로 돌아옴
	//pszSave의 변화
	//서버에서 원래값을 DEC해서 저장하고 pszSend의 DEC된 값과 비교

	if(bEncode)
	{
		//1. 랜덤바이트 생성후에, 암호화후에 클라이언트로 전송함
		MakeRandomBytes(pszSend, CHALLENGESIZE32);
		memcpy(pszSave, pszSend, CHALLENGESIZE32);
		Convert((char*)pszSend, CHALLENGESIZE32, TRUE);

		//3. 저장된 PLAIN TEXT를 복호화 한다.
		ShakeBytes32(pszSave, TRUE);
		Convert((char*)pszSave, CHALLENGESIZE32, FALSE);
	}
	else
	{
		//2. 클라언트에서 복호화를 아래와 같이 시도함
		Convert((char*)pszSend, CHALLENGESIZE32, FALSE);
		ShakeBytes32(pszSend, TRUE);
		Convert((char*)pszSend, CHALLENGESIZE32, FALSE);
	}
}

void CCypherEncodeText::EncodeAuthInfo(BYTE *pszText, BOOL bEncode)
{
	if(bEncode)
	{
		Convert((char*)pszText, CHALLENGESIZE32, TRUE);
		ShakeBytes32(pszText, TRUE);
		Convert((char*)pszText, CHALLENGESIZE32, TRUE);
	}
	else
	{
		//2. 클라언트에서 복호화를 아래와 같이 시도함
		Convert((char*)pszText, CHALLENGESIZE32, FALSE);
		ShakeBytes32(pszText, FALSE);
		Convert((char*)pszText, CHALLENGESIZE32, FALSE);
	}
}

