#pragma once



#include "UpdateSocket.h"


class CUpdateExeCheck : public CWnd
{
public:
    CUpdateExeCheck();

public:
	static int staticUpdateThread(CUpdateExeCheck* app)
	{
		return app->UpdateThread((LPVOID)app);
	}
		
	UINT CUpdateExeCheck::UpdateThread(LPVOID lParam);
	CUpdateSocket update_socket_;
	
	CString GetUpdateExeName(CString exe);
	CString GetUpdateExeVersion(CString exe);
	BOOL GetFileVersion(char* filename, VS_FIXEDFILEINFO* pvsf);

	void Start();
};

