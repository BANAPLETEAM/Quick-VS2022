#pragma once

#include "afxtempl.h"

typedef CList<HWND, HWND> CWindowList;

#define LAST_CHILD 0xFFFF

class CCallPassFunc
{
public:
	CCallPassFunc();

	void SendKey(CString strKey);
	void SendKey(int iKey, int nLoop = 1); 
	void SendKeyToHandle(HWND hWnd, CString strKey);
	void SendKeyToHandle(HWND hWnd, int nKey); 
	void SendKeyToHandleIME(HWND hWnd, int nKey);

	HWND FindOutWindow(CString strClassName, DWORD dwStyle = 0, DWORD dwExStyle = 0,
					   int nNumOfChild = -1, CString strFirstChild = "*",
						CString strCaption = "*", BOOL bNewHandle = FALSE); 
	HWND FindOutControl(HWND hParentWnd, int nCount, int *pnTotal = NULL, BOOL bSkipInvisible = FALSE);
	HWND FindOutControl(HWND hParentWnd, CString strCaption, int nOffsetCount = 0, int *pnTotal = NULL, int *pnCount = NULL);
	void SendButtonClick(HWND hWnd);
	static BOOL CALLBACK GetWindowList(HWND hWndChild, LPARAM lParam);

	void TypingMessage(CString Message);
	void TypingMessage(WCHAR* Message);
	void TypingMessage(int nMessage);
	void TypingMessage(CHAR* Message);
	void SendKeyShift(BOOL bDown);
	void SetForegroundHwnd(HWND hWnd) { m_hForeground = hWnd; }
	BOOL CloseWaitWindow(HWND hFindWnd , int nTimeOutMilSec = 20000);

protected:
	void TypingEnglish(WCHAR* Message);
	WCHAR* ReplacementHangulFragment(WCHAR Character);
	LPWSTR A2U(LPCSTR lpData);

	CWindowList m_WindowList;
	WCHAR m_lpwstr[MAX_PATH];
	HWND m_hForeground;

};