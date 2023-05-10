

#pragma once



#include <stdarg.h>
#include "strsafe.h"

extern void __PrintLog(const char* format, ...);


//1. 리턴값이 0x8007007a[시스템 호출에 전달된 데이터 영역이 너무 작습니다.] 이면,
//	 지정된 사이즈 만큼은 복사하고 마지막에 NULL을 붙여놓은 상태이므로 에러를 던지지 않고, 그냥 진행한다.
//2. 다른 리턴값이면 복사가 안된것이므로, 진행하면 안되고 throw한다.

#define SStrCpy(x,n,y) \
		{	HRESULT hre; \
		if (FAILED(hre=StringCchCopy(x,n,y))) \
			{\
			__PrintLog(_T("FAILED(hr=0x%x) String=%s DestLen=%d, in %s at %d (%s), %s\n"), \
			hre,y,n, TEXT(__FILE__), TEXT(__LINE__), TEXT("SStrCpy"), TEXT(__TIMESTAMP__));\
			if(hre != 0x8007007a) throw "SStrCpy"; } \
		} //throw "strcpy"; 제외함


#define SStrCat(x,n,y) \
		{	HRESULT hre; \
		if (FAILED(hre=StringCchCat(x,n,y))) \
			{\
			__PrintLog(_T("FAILED(hr=0x%x) in %s at %d (%s), %s\n"), \
			hre, TEXT(__FILE__), TEXT(__LINE__), TEXT("SStrCat"), TEXT(__TIMESTAMP__));\
			if(hre != 0x8007007a) throw "SStrCat";} \
		} //throw "strcat"; 제외함

#define SStrNCpy(x,n,y,m)\
		{	HRESULT hre; \
		if (FAILED(hre=StringCchCopyN(x,n,y,m))) \
			{\
			__PrintLog(_T("FAILED(hr=0x%x) in %s at %d (%s), %s\n"), \
			hre, TEXT(__FILE__), TEXT(__LINE__), TEXT("SStrNCpy"), TEXT(__TIMESTAMP__)); \
			if(hre != 0x8007007a) throw "SStrNCpy";} \
		} //throw "strncpy"; 제외함

#define SStrNCat(x,n,y,m)\
		{	HRESULT hre; \
		if (FAILED(hre=StringCchCatN(x,n,y,m))) \
			{\
			__PrintLog(_T("FAILED(hr=0x%x) in %s at %d (%s), %s\n"), \
			hre, TEXT(__FILE__), TEXT(__LINE__), TEXT("SStrNCat"), TEXT(__TIMESTAMP__)); \
			if(hre != 0x8007007a) throw "SStrNCat";} \
		} //throw "strncat"; 제외함

//x는 DEST, y는 SOURCE
#define SStrCpy2(x,y)		SStrCpy(x, sizeof(x), y)
#define SStrCat2(x,y)		SStrCat(x, sizeof(x), y)
#define SStrNCpy2(x,y,m)	SStrNCpy(x, sizeof(x), y, m)
#define SStrNCat2(x,y,m)	SStrNCat(x, sizeof(x), y, m)
#define DELIMITER			"\30\0"
#define ROW_DELIMITER		"\31\0"
#define VL_END				"@#"



inline static void STRCAT(char *dst,int ndestlen ...)
{
	char *src;

	va_list vl;
	va_start(vl, ndestlen);

	while(strncmp((src = va_arg(vl, char*)), VL_END, strlen(VL_END)) != 0)
	{
		SStrNCat(dst, strlen(src), src, ndestlen);
		SStrNCat(dst, ndestlen, (const char*) DELIMITER, strlen((const char*) DELIMITER));
	}

	va_end(vl);

}


