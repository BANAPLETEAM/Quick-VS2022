class CQLog2;

#ifndef _QLOG2_H_
#define _QLOG2_H_


#include "stdafx.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <afxmt.h>


class CQLog2  
{
public:
    // Logging mode flags:
    static const int ToDebug;
    static const int ToFile;
    static const int ToConsole;

	CQLog2();


    inline void Print(const char* format, ...) {
		
        va_list ap;
        va_start(ap, format);
        ReallyPrint(format, ap);
        va_end(ap);
    }


    inline void Print(int level, const char* format, ...) {

        if (level > m_level) return;
        va_list ap;
        va_start(ap, format);
        ReallyPrint(format, ap);
        va_end(ap);
    }

    // Change the qsLog level
    void SetLevel(int level);

    // Change the logging mode
    void SetMode(int mode);

    // Change or set the logging filename.  This only has an effect if
	// the qsLog mode includes ToFile
    void SetFile(const char* filename, bool append = false);

	virtual ~CQLog2();

//public:
private:
	void ReallyPrintLine(const char* line);
    void ReallyPrint(const char* format, va_list ap);
	void OpenFile();
    void CloseFile();
    bool m_tofile, m_todebug, m_toconsole;
    int m_level;
    HANDLE hlogfile;
	LPSTR m_filename;
	bool m_append;

	time_t m_lastLogTime;
	CCriticalSection m_crtSec;
};

#endif // _QLOG2_H_