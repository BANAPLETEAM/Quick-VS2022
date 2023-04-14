#pragma once



#ifndef _DEBUG
extern LONG WINAPI TheCrashHandlerFunction(EXCEPTION_POINTERS * pExPtrs);
extern LONG WINAPI TheCrashHandlerNormalFunction(EXCEPTION_POINTERS * pExPtrs);
#endif

extern BOOL UploadExceptionErrorData(CString strFaultReason, BOOL bDumpOK, CString strDumpPath, CString strDumpFileName, CString strVersion);
extern void WriteErrorLogFile(CString &strErrorLog, CString strPath);
