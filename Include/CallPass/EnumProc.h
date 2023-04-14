#pragma once


#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <vdmdbg.h>
#include <tchar.h>

#include <map>

#define SYSTEM_IDLE		0
#define SYSTEM			8
#define WM_POST_NOTIFY		(WM_USER+1000)
//#define WM_SYSTEM_NOTIFY	(WM_USER+1001)
//#define WM_DISK_NOTIFY		(WM_USER+1002)

using namespace std;


typedef int PID;
typedef struct					// ���μ��� ����͸� ����ü ( X�� ������� ����)
{
	PID ProcessID;
	//	int nCounterIndex;			// PDH ���̺귯���� ��ϵ� �� ���ϵǴ� ������ (X)

	char szInstanceName[MAX_PATH];	// PDH ���̺귯������ ����ϴ� ��ü ���� �̸� (X)
	char szImageName[MAX_PATH];		// �۾��������� ���μ��� ����â���� ǥ�õǴ� Ȯ���� ���� �̸�
	char szFullPath[MAX_PATH];  // ���μ����� �н��� ������ �̸� 

	//	FILETIME PrevCpuTime;		// ���μ����� ���� �� CPU�� ����� ���� �� (X)

	BOOL bRead;					// �� ���μ����� ���� ���������� Ȯ���ϱ� ���� �÷���
	BOOL bRaiseEvent;			// CPU TIME �̺�Ʈ �߻� ���� (X)

	HANDLE hProcess;

	HWND hWindow;				//���������� �ڵ�
	char szWindowTitle[MAX_PATH]; 

	DWORD dwFileCRC;
	DWORD dwFileSize;
	BOOL bAddServer;
	int nMatchType;

} PROCESSMON;

typedef struct				    // ���μ��� ���� ���� ����ü
{
	char szFullPath[MAX_PATH];  // ���μ����� �н��� ������ �̸�
	char szArgument[MAX_PATH];	// ���μ����� ���� ARGUMENT
	UINT nCount;				// ���μ��� ����  �ּ� ����
	BOOL IsService;				// ���� ���� (X)

	BOOL bValid;				// �� ���μ����� ���� ��ȿ������ Ȯ���ϱ� ���� �÷��� (X)
	BOOL bRaiseEvent;			// �̺�Ʈ �߻� ���� (X)

} PROCESSCOUNT;

typedef char* FFN;		// Full File Name

typedef map<PID, PROCESSMON*> PROCESSMAP;
typedef map<FFN, PROCESSCOUNT> PROCESSCOUNTMAP;


// ���μ��� ���� �뺸 �޽�����
enum {
	PN_REFRESHED = 1,
	PN_GOT_PROCESS,
	PN_LOST_PROCESS,
	PN_COUNT_NOT_ENOUGH
};


// �ý��� ���� �뺸 �޽�����
enum {
	SN_REFRESHED = 10,
	SN_CPU_CRITICAL_OVER,
	SN_MEM_CRITICAL_OVER
};

// ��ũ ���� �뺸 �޽���
enum {
	DN_DISK_CRITICAL_OVER = 20
};

class CEnumProc
{
public:
	CEnumProc(HWND hParentWnd)
	{
		m_hParentWnd = hParentWnd;
	}

public:
	static HWND m_hParentWnd;
	static PROCESSMAP m_ProcessMap;
	static BOOL m_bWin98;


public:
	static BOOL OnProcess(LPCTSTR lpszFileName, DWORD pid)
	{
		if(m_bWin98)
		{
			PROCESSMAP::iterator it;
			if((it = m_ProcessMap.find(pid)) != m_ProcessMap.end()) // ����
			{
				//���� �����ϰ� ������ ��Ÿ���� �÷��׸� ���Ѵ�.
				m_ProcessMap[pid]->bRead = TRUE;
			}
			else // ���ο� ���μ����� ���۵Ǿ���
			{
				PROCESSMON *pProcessMon = new PROCESSMON;
				ZeroMemory(pProcessMon, sizeof(PROCESSMON));
				pProcessMon->bRead = TRUE;

				strcpy(pProcessMon->szImageName, lpszFileName);
				strcpy(pProcessMon->szFullPath, lpszFileName);
				pProcessMon->ProcessID = pid;

				m_ProcessMap.insert(PROCESSMAP::value_type(pid, pProcessMon));
				PostNotify(PN_GOT_PROCESS, (LPARAM)pProcessMon);
			}		

			return TRUE;
		}

		typedef HANDLE (WINAPI *CREATESNAPSHOT)(
			DWORD dwFlags, 
			DWORD th32ProcessID
			); 

		typedef BOOL (WINAPI *PROCESSWALK)(
			HANDLE hSnapshot,    
			LPPROCESSENTRY32 lppe
			);

		typedef BOOL (WINAPI *MODULEWALK)(
			HANDLE hSnapshot,
			LPMODULEENTRY32 lpme
			);

		HINSTANCE modKERNEL = GetModuleHandle(_T("KERNEL32.DLL"));

		CREATESNAPSHOT CreateToolhelp32Snapshot; 
		MODULEWALK pModule32First; 
		MODULEWALK pModule32Next; 

		CreateToolhelp32Snapshot = (CREATESNAPSHOT)GetProcAddress(modKERNEL, "CreateToolhelp32Snapshot"); 
		pModule32First = (MODULEWALK)GetProcAddress(modKERNEL, "Module32First"); 
		pModule32Next  = (MODULEWALK)GetProcAddress(modKERNEL, "Module32Next"); 

		if (
			NULL == CreateToolhelp32Snapshot	|| 
			NULL == pModule32First				||
			NULL == pModule32Next)
			return FALSE;

		MODULEENTRY32 module;
		module.dwSize = sizeof(module);

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
		/* Now that we have a snapshot of the system state, we simply
		* walk the list it represents by calling Process32First once,
		* then call Proces32Next repeatedly until we get to the end 
		* of the list.
		*/
		pModule32First(snapshot, &module);
		//HANDLE process = OpenProcess(PROCESS_TERMINATE, FALSE, pid);

		if(pid == SYSTEM_IDLE || pid == SYSTEM) 
		{
			FreeLibrary(modKERNEL);
			CloseHandle(snapshot);
			return TRUE;
		}

		PROCESSMAP::iterator it;
		if((it = m_ProcessMap.find(pid)) != m_ProcessMap.end()) // ����
		{
			//���� �����ϰ� ������ ��Ÿ���� �÷��׸� ���Ѵ�.
			it->second->bRead = TRUE;
		}
		else // ���ο� ���μ����� ���۵Ǿ���
		{
			PROCESSMON *pProcessMon = new PROCESSMON;
			ZeroMemory(pProcessMon, sizeof(PROCESSMON));
			pProcessMon->bRead = TRUE;

			strcpy(pProcessMon->szImageName, module.szExePath);
			strcpy(pProcessMon->szFullPath, module.szExePath);
			pProcessMon->ProcessID = pid;

			m_ProcessMap.insert(PROCESSMAP::value_type(pid, pProcessMon));
			PostNotify(PN_GOT_PROCESS, (LPARAM)pProcessMon);
		}		

		FreeLibrary(modKERNEL);
		CloseHandle(snapshot);
		return TRUE;
	}




	static void PostNotify(UINT nMessage, LPARAM lParam)		
	{PostMessage(m_hParentWnd, WM_POST_NOTIFY, (WPARAM)nMessage, lParam);};

	void RemoveDownProcess()
	{
		PROCESSMAP::iterator it;
		int DeletePidList[500];
		int nDeleteCount = 0;

		// ����� ���μ����� �˻��Ѵ�.
		for(it = m_ProcessMap.begin(); it != m_ProcessMap.end(); it++)
		{
			PID pid = (*it).first;
			BOOL bRead = it->second->bRead;

			if(!bRead)
			{
				// �ʿ��� �����ϰ� �θ𿡰� �뺸
				DeletePidList[nDeleteCount++] = pid; 
				PostNotify(PN_LOST_PROCESS, (LPARAM) m_ProcessMap[pid]);
			}
			else
			{
				it->second->bRead = FALSE;
			}
		}					

		// ������ ���� ���� ��Ͽ� ���� ���� ������ �����Ѵ�.
		// �ֳ��ϸ� FOR������ ���� �ִ� �� �ȿ��� ������ �����ϸ� iterator�� ����
		for(int i = 0; i < nDeleteCount; i++)
		{
			m_ProcessMap.erase(DeletePidList[i]);
		}
	}

	void Refresh();
	BOOL EnumProcs();
};


