// Quick.h : Quick ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // �� ��ȣ
//#include "QSocket.h"


// CQuickApp:
// �� Ŭ������ ������ ���ؼ��� Quick.cpp�� �����Ͻʽÿ�.
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


// ������
public:
	virtual BOOL InitInstance();

// ����
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();

};

extern CQuickApp theApp;
