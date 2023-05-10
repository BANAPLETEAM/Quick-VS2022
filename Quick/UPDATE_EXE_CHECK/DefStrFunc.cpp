#include "stdafx.h"
#include "DefStrFunc.h"




#ifdef _MKSERVER
extern CMkLog mkLog;
void __PrintLog(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	mkLog.ReallyPrint(format, ap);
	va_end(ap);
}
#else
void __PrintLog(const char* format, ...)
{

}
#endif