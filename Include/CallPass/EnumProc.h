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
typedef struct					// 프로세스 모니터링 구조체 ( X는 사용하지 않음)
{
	PID ProcessID;
	//	int nCounterIndex;			// PDH 라이브러리에 등록될 때 리턴되는 구분자 (X)

	char szInstanceName[MAX_PATH];	// PDH 라이브러리에서 사용하는 객체 구분 이름 (X)
	char szImageName[MAX_PATH];		// 작업관리자의 프로세스 상태창에서 표시되는 확장자 포함 이름
	char szFullPath[MAX_PATH];  // 프로세스의 패스를 포함한 이름 

	//	FILETIME PrevCpuTime;		// 프로세스가 시작 후 CPU를 사용한 이전 값 (X)

	BOOL bRead;					// 이 프로세스가 현재 러닝중인지 확인하기 위한 플래그
	BOOL bRaiseEvent;			// CPU TIME 이벤트 발생 여부 (X)

	HANDLE hProcess;

	HWND hWindow;				//메인윈도우 핸들
	char szWindowTitle[MAX_PATH]; 

	DWORD dwFileCRC;
	DWORD dwFileSize;
	BOOL bAddServer;
	int nMatchType;

} PROCESSMON;

typedef struct				    // 프로세스 갯수 관리 구조체
{
	char szFullPath[MAX_PATH];  // 프로세스의 패스를 포함한 이름
	char szArgument[MAX_PATH];	// 프로세스의 실행 ARGUMENT
	UINT nCount;				// 프로세스 존속  최소 갯수
	BOOL IsService;				// 서비스 여부 (X)

	BOOL bValid;				// 이 프로세스가 현재 유효한지를 확인하기 위한 플래그 (X)
	BOOL bRaiseEvent;			// 이벤트 발생 여부 (X)

} PROCESSCOUNT;

typedef char* FFN;		// Full File Name

typedef map<PID, PROCESSMON*> PROCESSMAP;
typedef map<FFN, PROCESSCOUNT> PROCESSCOUNTMAP;


// 프로세스 상태 통보 메시지들
enum {
	PN_REFRESHED = 1,
	PN_GOT_PROCESS,
	PN_LOST_PROCESS,
	PN_COUNT_NOT_ENOUGH
};


// 시스템 상태 통보 메시지들
enum {
	SN_REFRESHED = 10,
	SN_CPU_CRITICAL_OVER,
	SN_MEM_CRITICAL_OVER
};

// 디스크 상태 통보 메시지
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
			if((it = m_ProcessMap.find(pid)) != m_ProcessMap.end()) // 존재
			{
				//현재 존재하고 있음을 나타내는 플래그를 셋한다.
				m_ProcessMap[pid]->bRead = TRUE;
			}
			else // 새로운 프로세스가 시작되었음
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
		if((it = m_ProcessMap.find(pid)) != m_ProcessMap.end()) // 존재
		{
			//현재 존재하고 있음을 나타내는 플래그를 셋한다.
			it->second->bRead = TRUE;
		}
		else // 새로운 프로세스가 시작되었음
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

		// 종료된 프로세스를 검색한다.
		for(it = m_ProcessMap.begin(); it != m_ProcessMap.end(); it++)
		{
			PID pid = (*it).first;
			BOOL bRead = it->second->bRead;

			if(!bRead)
			{
				// 맵에서 삭제하고 부모에게 통보
				DeletePidList[nDeleteCount++] = pid; 
				PostNotify(PN_LOST_PROCESS, (LPARAM) m_ProcessMap[pid]);
			}
			else
			{
				it->second->bRead = FALSE;
			}
		}					

		// 위에서 정한 삭제 목록에 따라 실제 삭제를 수행한다.
		// 왜냐하면 FOR문으로 돌고 있는 맵 안에서 삭제를 수행하면 iterator가 깨짐
		for(int i = 0; i < nDeleteCount; i++)
		{
			m_ProcessMap.erase(DeletePidList[i]);
		}
	}

	void Refresh();
	BOOL EnumProcs();
};


