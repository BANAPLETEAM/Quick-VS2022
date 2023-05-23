#include "stdafx.h"
#include "UpdateExeCheck.h"
#include "afxsock.h"

CUpdateExeCheck::CUpdateExeCheck()
{
	//Start();
}

void CUpdateExeCheck::Start()
{ 
	DWORD dwThreadID;
	HANDLE hHandle = CreateThread(NULL, 0, 
		(LPTHREAD_START_ROUTINE)staticUpdateThread,
		(LPVOID)this, 0, &dwThreadID);
	CloseHandle(hHandle);
 
	//UpdateThread(this);
}
 
UINT CUpdateExeCheck::UpdateThread(LPVOID lParam)
{	
	if (!update_socket_.ConnectServer(SERVER_IP, SERVER_PORT))
		return 0;

	if (update_socket_.CheckUpdateEXE(SERVER_UPDATE_NAME)) {
		CString local_ver = GetUpdateExeVersion(UPDATE_PROCESS_NAME);
		CString server_ver = update_socket_.GetBuffer();

		if (local_ver != server_ver) {
			CString exit_file = GetUpdateExeName(UPDATE_PROCESS_NAME);
			CString temp_file = exit_file + "_";

			if (update_socket_.RecvFile(CString(UPDATE_FILES) + SERVER_UPDATE_NAME, temp_file)) {
				CopyFile(temp_file, exit_file, FALSE);
				DeleteFile(temp_file);				
			}	
		}
	}  
	 
	update_socket_.Close();
	return 0;
}

CString CUpdateExeCheck::GetUpdateExeName(CString exe)
{
	char Path[_MAX_PATH];
	GetModuleFileName(NULL, Path, MAX_PATH);
	PathRemoveFileSpec(Path);

	return CString(Path) + "\\" + exe;
}

CString CUpdateExeCheck::GetUpdateExeVersion(CString exe)
{
	CString fileName = GetUpdateExeName(exe);
	VS_FIXEDFILEINFO pvsf;

	if (LF->GetFileVersion((LPSTR)(LPCTSTR)fileName, &pvsf))
	{
		CString strVersion;
		strVersion.Format("%d.%d%d",
			HIWORD(pvsf.dwFileVersionMS),
			LOWORD(pvsf.dwFileVersionMS),
			HIWORD(pvsf.dwFileVersionLS));

		return strVersion;
	}

	return "0.0";
}