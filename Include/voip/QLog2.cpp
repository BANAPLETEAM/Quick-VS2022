#include "stdafx.h"
#include <io.h>
#include <wincon.h>
#include "QLog2.h"
#include "direct.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


const int CQLog2::ToDebug   =  1;
const int CQLog2::ToFile    =  2;
const int CQLog2::ToConsole =  4;

const static int LINE_BUFFER_SIZE = 1024;

CQLog2::CQLog2()
{
	m_lastLogTime = 0;
	m_filename = NULL;
	m_append = false;
    hlogfile = NULL;
    m_todebug = false;
    m_toconsole = false;
    m_tofile = false;
}

void CQLog2::SetMode(int mode) {

//Log기록을 하지 않는다.
//	return;
    if (mode & ToDebug)
        m_todebug = true;
    else
        m_todebug = false;

    if (mode & ToFile)  {
		if (!m_tofile)
			OpenFile();
	} else {
		CloseFile();
        m_tofile = false;
    }
    
    if (mode & ToConsole) {
        if (!m_toconsole) {
			AllocConsole();
			SetConsoleTitle("Tel Server");
			fclose(stdout);
            fclose(stderr);
            int fh = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), 0);
            _dup2(fh, 1);
            _dup2(fh, 2);
            _fdopen(1, "wt");
            _fdopen(2, "wt");
            fflush(stdout); 
        }

        m_toconsole = true;

    } else {
        m_toconsole = false;
    }
}


void CQLog2::SetLevel(int level) {
    m_level = level;
}

void CQLog2::SetFile(const char* filename, bool append) 
{
	if (m_filename != NULL)
		free(m_filename);

	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	char szFileName[MAX_PATH];
	strcpy(szFileName,filename);
	mkdir(filename);
	strcat(szFileName,  "\\");
	strcat(szFileName,  dtCur.Format("%Y_%m_%d"));
	strcat(szFileName,  ".TXT");

	m_filename = strdup(szFileName);
//	m_filename = strdup(filename);
	m_append = append;
	if (m_tofile)
		OpenFile();
}

void CQLog2::OpenFile()
{
	// Is there a file-name?
	if (m_filename == NULL)
	{
        m_todebug = true;
        m_tofile = false;
        Print(0, "Error opening qsLog file\n");
		return;
	}

    m_tofile  = true;
    
	// If there's an existing qsLog and we're not appending then move it
	if (!m_append)
	{
		// Build the backup filename
		char *backupfilename = new char[strlen(m_filename)+5];
		if (backupfilename)
		{
			strcpy(backupfilename, m_filename);
			strcat(backupfilename, ".bak");
			// Attempt the move and replace any existing backup
			// Note that failure is silent - where would we qsLog a message to? ;)
			MoveFileEx(m_filename, backupfilename, MOVEFILE_REPLACE_EXISTING);
			delete [] backupfilename;
		}
	}

	CloseFile();

    // If filename is NULL or invalid we should throw an exception here
    hlogfile = CreateFile(
        m_filename,  GENERIC_WRITE, FILE_SHARE_READ, NULL,
        OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL  );
    
    if (hlogfile == INVALID_HANDLE_VALUE) {
        // We should throw an exception here
        m_todebug = true;
        m_tofile = false;
        Print(0, "Error opening qsLog file %s\n", m_filename);
    }
    if (m_append) {
        SetFilePointer( hlogfile, 0, NULL, FILE_END );
    } else {
        SetEndOfFile( hlogfile );
    }
}

// if a qsLog file is open, close it now.
void CQLog2::CloseFile() {
    if (hlogfile != NULL) {
        CloseHandle(hlogfile);
        hlogfile = NULL;
    }
}

inline void CQLog2::ReallyPrintLine(const char* line) 
{
	HANDLE handle;

    if (m_todebug) OutputDebugString(line);
    if (m_toconsole) {
		DWORD byteswritten;

		if((handle = GetStdHandle(STD_OUTPUT_HANDLE)) != NULL)
			WriteConsole(handle, line, strlen(line), &byteswritten, NULL); 
    };
    if (m_tofile && (hlogfile != NULL)) {
        DWORD byteswritten;
        WriteFile(hlogfile, line, strlen(line), &byteswritten, NULL); 
    }
}

void CQLog2::ReallyPrint(const char* format, va_list ap) 
{
	CSingleLock myLock(&m_crtSec,TRUE);

	time_t current = time(0);
	if (current != m_lastLogTime) {
		m_lastLogTime = current;
		ReallyPrintLine(ctime(&m_lastLogTime));
	}

	// - Write the qsLog message, safely, limiting the output buffer size
	TCHAR line[LINE_BUFFER_SIZE];
    _vsnprintf(line, LINE_BUFFER_SIZE, format, ap);
	ReallyPrintLine(line);
}

CQLog2::~CQLog2()
{
	if (m_filename != NULL)
		free(m_filename);
    CloseFile();
}
