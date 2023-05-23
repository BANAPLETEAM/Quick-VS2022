// Quick.h : Quick 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // 주 기호
//#include "QSocket.h"


// CQuickApp:
// 이 클래스의 구현에 대해서는 Quick.cpp을 참조하십시오.
//

#ifndef _DEBUG
	LONG WINAPI TheCrashHandlerFunction(EXCEPTION_POINTERS* pExPtrs);
	LONG WINAPI TheCrashHandlerNormalFunction(EXCEPTION_POINTERS* pExPtrs);
#endif

class CQuickApp : public CWinApp
{
public:
	CQuickApp();
	~CQuickApp();


// 재정의
public:
	virtual BOOL InitInstance();

// 구현
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();

};

extern CQuickApp theApp;
