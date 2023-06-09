/*	
*/

#include "stdafx.h"

#include "bytes.h"


#define conv_bin2ascii(a)	(data_bin2ascii[(a)&0x3f])
#define conv_ascii2bin(a)	(data_ascii2bin[(a)&0x7f])

/* 64 char lines
 * pad input with 0
 * left over chars are set to =
 * 1 byte  => xx==
 * 2 bytes => xxx=
 * 3 bytes => xxxx
 */
#define BIN_PER_LINE    (64/4*3)
#define CHUNKS_PER_LINE (64/4)
#define CHAR_PER_LINE   (64+1)

static unsigned char data_bin2ascii[65]="ABCDEFGHIJKLMNOPQRSTUVWXYZ\
abcdefghijklmnopqrstuvwxyz0123456789+/";

/* 0xF0 is a EOLN
 * 0xF1 is ignore but next needs to be 0xF0 (for \r\n processing).
 * 0xF2 is EOF
 * 0xE0 is ignore at start of line.
 * 0xFF is error
 */

#define B64_EOLN		0xF0
#define B64_CR			0xF1
#define B64_EOF			0xF2
#define B64_WS			0xE0
#define B64_ERROR       	0xFF
#define B64_NOT_BASE64(a)	(((a)|0x13) == 0xF3)

static unsigned char data_ascii2bin[128]={
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xE0,0xF0,0xFF,0xFF,0xF1,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xE0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0x3E,0xFF,0xF2,0xFF,0x3F,
	0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,
	0x3C,0x3D,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,
	0xFF,0x00,0x01,0x02,0x03,0x04,0x05,0x06,
	0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,
	0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,
	0x17,0x18,0x19,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,
	0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,
	0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,
	0x31,0x32,0x33,0xFF,0xFF,0xFF,0xFF,0xFF,
	};


int EVP_EncodeBlock(unsigned char *t, unsigned char *f, int dlen)
{
	int i,ret=0;
	unsigned long l;

	for (i=dlen; i > 0; i-=3)
		{
		if (i >= 3)
			{
			l=	(((unsigned long)f[0])<<16L)|
				(((unsigned long)f[1])<< 8L)|f[2];
			*(t++)=conv_bin2ascii(l>>18L);
			*(t++)=conv_bin2ascii(l>>12L);
			*(t++)=conv_bin2ascii(l>> 6L);
			*(t++)=conv_bin2ascii(l     );
			}
		else
			{
			l=((unsigned long)f[0])<<16L;
			if (i == 2) l|=((unsigned long)f[1]<<8L);

			*(t++)=conv_bin2ascii(l>>18L);
			*(t++)=conv_bin2ascii(l>>12L);
			*(t++)=(i == 1)?'=':conv_bin2ascii(l>> 6L);
			*(t++)='=';
			}
		ret+=4;
		f+=3;
		}

	*t='\0';
	return(ret);
}

int EVP_DecodeBlock(unsigned char *t, unsigned char *f, int n)
{
	int i,ret=0,a,b,c,d;
	unsigned long l;

	/* trim white space from the start of the line. */
	while ((conv_ascii2bin(*f) == B64_WS) && (n > 0))
		{
		f++;
		n--;
		}

	/* strip off stuff at the end of the line
	 * ascii2bin values B64_WS, B64_EOLN, B64_EOLN and B64_EOF */
	while ((n > 3) && (B64_NOT_BASE64(conv_ascii2bin(f[n-1]))))
		n--;

	if (n%4 != 0) return(-1);

	for (i=0; i<n; i+=4)
		{
		a=conv_ascii2bin(*(f++));
		b=conv_ascii2bin(*(f++));
		c=conv_ascii2bin(*(f++));
		d=conv_ascii2bin(*(f++));
		if (	(a & 0x80) || (b & 0x80) ||
			(c & 0x80) || (d & 0x80))
			return(-1);
		l=(	(((unsigned long)a)<<18L)|
			(((unsigned long)b)<<12L)|
			(((unsigned long)c)<< 6L)|
			(((unsigned long)d)     ));
		*(t++)=(unsigned char)(l>>16L)&0xff;
		*(t++)=(unsigned char)(l>> 8L)&0xff;
		*(t++)=(unsigned char)(l     )&0xff;
		ret+=3;
		}
	return(ret);
}

int MakeEncode(unsigned char* lpszInMsg, int nInMsgLen, unsigned char** lpszOutMsg, int* pnOutMsgLen)
{
	int nRtn;


	if (!nInMsgLen)
	nInMsgLen = lstrlen((LPCTSTR) lpszInMsg);
	unsigned char* byteDest = new unsigned char [(nInMsgLen + 4) * 2 ];

	nRtn = EVP_EncodeBlock((unsigned char *) byteDest, lpszInMsg, nInMsgLen);

	*pnOutMsgLen = lstrlen((LPCTSTR) byteDest);
	*lpszOutMsg = new unsigned char [*pnOutMsgLen+1];
	memset(*lpszOutMsg,0,*pnOutMsgLen+1);
	memcpy((LPTSTR) *lpszOutMsg, (LPCTSTR) byteDest,*pnOutMsgLen);

	delete [] byteDest;

	return nRtn;
}

int MakeDecode(unsigned char* lpszInMsg, int nInMsgLen, unsigned char** lpszOutMsg, int* pnOutMsgLen)
{
	if (!nInMsgLen)
		nInMsgLen = lstrlen((LPCTSTR) lpszInMsg);

	int end = 0;
	int ii=nInMsgLen;
	for (; ii > 0 ; ii--) 
	{
		if (lpszInMsg[ii - 1] == '=')
			end++;
	}

	*lpszOutMsg = new unsigned char[nInMsgLen];
	if ((nInMsgLen = EVP_DecodeBlock(*lpszOutMsg, lpszInMsg, nInMsgLen)) <= 0)
		return -1/*nInMsgLen*/;
	*pnOutMsgLen = nInMsgLen - end;
	(*lpszOutMsg)[*pnOutMsgLen] = 0x00;

	return *pnOutMsgLen;
}



CByte::CByte()
{
	m_pbyte   = NULL;
	m_nLength = 0;
}

CByte::CByte(CString sStr)
{
	CByte( (BYTE* )(LPCSTR)sStr,sStr.GetLength());
}

CByte::CByte(BYTE* pByte,int nLength)
{
	m_nLength = nLength;
	m_pbyte   = new BYTE[m_nLength];
	if(!m_pbyte)
	{
//		필요시 Exception 발생. 그러나 nLength가 정상적인 값이라면 메모리 할당에  실패할리는 없다. 
	}
	if(pByte) memcpy(m_pbyte,pByte,m_nLength);
}


CByte::CByte(const CByte& Byte)
{
	
	this->m_nLength = Byte.m_nLength;
	this->m_pbyte   = new BYTE[m_nLength];
	
	if(!m_pbyte)
	{
//		필요시 Exception 발생. 그러나 nLength가 정상적인 값이라면 메모리 할당에  실패할리는 없다. 
	}
	memcpy(m_pbyte,Byte.m_pbyte,m_nLength);
}

CByte::CByte(CByte* pByte)
{
	m_nLength = pByte->GetLength();
	m_pbyte   = new BYTE[m_nLength];
	
	if(!m_pbyte)
	{
//		필요시 Exception 발생. 그러나 nLength가 정상적인 값이라면 메모리 할당에  실패할리는 없다. 
	}
	memcpy(m_pbyte,pByte->GetByte(),m_nLength);
}

CByte::~CByte()
{
	if(m_pbyte) delete []m_pbyte;
	m_nLength  = 0;
}

BOOL CByte::SetByte(BYTE* pByte,int nLength) 
{
	if(nLength  == 0)
	{
		if(m_pbyte) delete []m_pbyte;
		m_pbyte   = NULL;
		m_nLength = 0;
		return TRUE;
	}
	
	if(m_pbyte) delete []m_pbyte;
	m_nLength = nLength;
	m_pbyte   = new BYTE[m_nLength];
	
	if(!m_pbyte)
	{
		return FALSE;
	}

	memset(m_pbyte,NULL,nLength);

	if(pByte) memcpy(m_pbyte,pByte,m_nLength);
	else 
	{
		return TRUE;
	}

	return TRUE;
}

BOOL CByte::SetByte(CByte Byte)
{
	m_nLength = Byte.GetLength();
	if(m_pbyte) delete []m_pbyte;

	m_pbyte   = new BYTE[m_nLength];
	
	if(!m_pbyte)
	{
		return FALSE;
	}
	memcpy(m_pbyte,Byte.GetByte(),m_nLength);
	
	return TRUE;
}

BOOL CByte::SetByte(CByte* pByte)
{
	if (pByte)
	{
		m_nLength = pByte->GetLength();
		if(m_pbyte) delete []m_pbyte;

		m_pbyte   = new BYTE[m_nLength];
		
		if(!m_pbyte)
		{
			return FALSE;
		}
		memcpy(m_pbyte,pByte->GetByte(),m_nLength);
	}
	else
	{
		m_nLength = 0;
		if (m_pbyte)
			delete [] m_pbyte;
		m_pbyte = NULL;
	}
	return TRUE;
}

BYTE* CByte::GetByte()
{
	return m_pbyte;
}

int CByte::GetLength()
{
	return m_nLength;
}

CByte CByte::operator+(const CByte& Byte)
{

	BYTE* pByte;
	pByte = new BYTE[m_nLength + Byte.m_nLength];
	memcpy( pByte          ,m_pbyte,m_nLength);
	memcpy( pByte+m_nLength,Byte.m_pbyte,Byte.m_nLength );
	CByte tempByte( pByte,m_nLength + Byte.m_nLength );
	delete []pByte;
	return tempByte;
}

CByte& CByte::operator=(const CByte& Byte)
{
	if(this == &Byte) return *this;

	if(this->m_pbyte) delete []this->m_pbyte;
	this->m_pbyte   = new BYTE[Byte.m_nLength];
	this->m_nLength = Byte.m_nLength;
	memcpy(this->m_pbyte,Byte.m_pbyte,Byte.m_nLength);
	return *this;
}

CByte& CByte::operator=(const CByte* Byte)
{
	if(this == Byte) return *this;

	if (Byte)
	{
		if(this->m_pbyte) delete []this->m_pbyte;
		this->m_pbyte   = new BYTE[Byte->m_nLength];
		this->m_nLength = Byte->m_nLength;
		memcpy(this->m_pbyte,Byte->m_pbyte,Byte->m_nLength);

	}
	else
	{
		m_nLength = 0;
		if (m_pbyte)
			delete [] m_pbyte;
		m_pbyte = NULL;
	}
	return *this;
}

