#include "StdAfx.h"
#include "CallPassFunc.h"

CCallPassFunc::CCallPassFunc()
{
	m_hForeground = NULL;
}


void CCallPassFunc::SendKey(CString strKey)
{
	int iLength = strKey.GetLength();

	for(int i = 0; i < iLength; i++)
	{
		keybd_event(strKey.GetAt(i), 0, 0, 0);
		keybd_event(strKey.GetAt(i), 0, KEYEVENTF_KEYUP, 0);
	}
}

void CCallPassFunc::SendKey(int iKey, int nLoop)
{
	for(int i = 0; i < nLoop; i++)
	{
		keybd_event(iKey, 0, 0, 0);
		keybd_event(iKey, 0, KEYEVENTF_KEYUP, 0);
		Sleep(0);
	}
}


void CCallPassFunc::SendKeyShift(BOOL bDown)
{
	if(bDown)
		keybd_event(VK_SHIFT, 0, 0, 0);
	else
		keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
}	


void CCallPassFunc::SendKeyToHandle(HWND hWnd, CString strKey)
{
	int iLength = strKey.GetLength();

	for(int i = 0; i < iLength; i++)
	{	
		BYTE ch = strKey.GetAt(i);


		if(ch >= 0xA0 && i != iLength)
		{
			BYTE ch2 = strKey.GetAt(i + 1);
			SendKeyToHandleIME(hWnd, ch << 8 | ch2);
			i++;
		}
		else
		{
			SendKeyToHandle(hWnd, ch);
		}
	}
}

void CCallPassFunc::SendKeyToHandle(HWND hWnd, int nKey)
{
	::SendMessage(hWnd, WM_KEYDOWN, nKey, 0);
	::SendMessage(hWnd, WM_CHAR, nKey, 0);
	::SendMessage(hWnd, WM_KEYUP, nKey, 0);
}

void CCallPassFunc::SendKeyToHandleIME(HWND hWnd, int nKey)
{
	::SendMessage(hWnd, WM_IME_CHAR, nKey, 1);
}


void CCallPassFunc::SendButtonClick(HWND hWnd)
{
	::SendMessage(hWnd, WM_LBUTTONDOWN, 0, 0);
	::SendMessage(hWnd, WM_LBUTTONUP, 0, 0);
}

BOOL CCallPassFunc::GetWindowList(HWND hWndChild, LPARAM lParam)
{
	CWindowList* pWindowList = (CWindowList*) lParam;
	pWindowList->AddTail(hWndChild);
	return TRUE;
}

BOOL CCallPassFunc::CloseWaitWindow(HWND hFindWnd , int nTimeOutMilSec)
{
	DWORD dwTick = GetTickCount();
	
	while(1)
	{
		HWND hWndDesktop;
		BOOL bExist = FALSE;

		m_WindowList.RemoveAll();
		hWndDesktop = ::GetDesktopWindow();
		::EnumChildWindows(hWndDesktop, GetWindowList, (LPARAM)&m_WindowList);//콜백 설정	

		POSITION pos = m_WindowList.GetHeadPosition();

		while(pos != NULL)
		{
			HWND hWnd = m_WindowList.GetNext(pos);

			if(hWnd == hFindWnd)
				bExist = TRUE;
		}

		if(!bExist)
			return TRUE;

		if(GetTickCount() - dwTick > nTimeOutMilSec)
			return FALSE;

		Sleep(50);
	}
}


HWND CCallPassFunc::FindOutWindow(CString strClassName, DWORD dwStyle, DWORD dwExStyle, 
				   int nNumOfChild, CString strFirstChild,
					CString strCaption, BOOL bNewHandle)
{
	HWND			hWndDesktop;
	HWND			hRtnWnd = NULL;
	char lpszText[256];
	int Count = 0;

	hWndDesktop = ::GetDesktopWindow();

	CWindowList OldWindowList;
	POSITION p = m_WindowList.GetHeadPosition();
	while(p)
	{
		HWND hTempWnd = m_WindowList.GetNext(p);
		if(hTempWnd)	
			OldWindowList.AddTail(hTempWnd);
	}

	m_WindowList.RemoveAll();
	::EnumChildWindows(hWndDesktop, GetWindowList, (LPARAM)&m_WindowList);//콜백 설정	

	POSITION pos = m_WindowList.GetHeadPosition();

	while(pos != NULL)
	{
		HWND hWnd = m_WindowList.GetNext(pos);
		CWnd *pWnd = CWnd::FromHandle(hWnd);
		
		BOOL rtn = TRUE;
		if(hWnd != NULL && ::IsWindow(hWnd)) 
		{
			if(bNewHandle)
				if(OldWindowList.Find(hWnd) != NULL)
					continue;

			::GetClassName(hWnd, lpszText, 255); //ClassName
			if(strcmp(strClassName, "*")) //클래스이름이 '*'이 아닐때 
				if(strcmp(strClassName, lpszText)) // 클래스 이름 불일치
					continue; //while문으로 돌아간다.

			::GetWindowText(hWnd, lpszText, 255);
			if(strcmp(strCaption, "*")) //클래스이름이 '*'이 아닐때 
				if(!strstr(lpszText, strCaption)) // 클래스 이름 불일치
					continue; //while문으로 돌아간다.

			
			if(dwStyle != 0) //기본 스타일이 0이면 검사 안함
				if(dwStyle != pWnd->GetStyle())
					continue;
			
			if(dwExStyle != 0) //확장 스타일이 0이면 검사 안함
				if(dwExStyle != pWnd->GetExStyle())
					continue;
				
			int nTotal;
			HWND hWndChild = NULL;
			hWndChild = FindOutControl(hWnd, 1, &nTotal);
						
			if(nNumOfChild != -1)
				if(nNumOfChild != nTotal)
					continue;

			::GetClassName(hWndChild, lpszText, 255);
			if(strcmp(strFirstChild, "*"))
				if(strcmp(strFirstChild, lpszText))
					continue;

			
			
		}
		
		if(rtn)
		{
			if(IsWindow(hWnd))
				return hWnd;
		}
	
	}

	return NULL;
}



HWND CCallPassFunc::FindOutControl(HWND hParentWnd, int nCount, int *pnTotal, BOOL bSkipInvisible)
{
	int curCount = 1, nTotal = 1;
	HWND hWndrtn = NULL;
	CWnd *pWnd = CWnd::FromHandle(hParentWnd);
	CWnd *pChildWnd = pWnd->GetWindow(GW_CHILD); //제일 위의 새끼를 검색한다.

	if(nCount > LAST_CHILD - 0xFF && pChildWnd)
	{
		while((pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT)) != NULL)
		{
			if(bSkipInvisible && !(pChildWnd->GetStyle() & WS_VISIBLE))
				continue;

			nTotal++;
		}

		nCount = nTotal + (nCount - LAST_CHILD);
	}

	pChildWnd = pWnd->GetWindow(GW_CHILD);

	while(pChildWnd != NULL)
	{
		if(bSkipInvisible && !(pChildWnd->GetStyle() & WS_VISIBLE))
		{
			pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT); //다음 컨트롤의 핸들을 구함
			continue;
		}

		if(curCount == nCount)
			hWndrtn = pChildWnd->GetSafeHwnd();
		
		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT); //다음 컨트롤의 핸들을 구함
		curCount++;
	}
	
	if(pnTotal)
		*pnTotal = --curCount;

	return hWndrtn;
}

HWND CCallPassFunc::FindOutControl(HWND hParentWnd, CString strCaption, int nOffsetCount, int *pnTotal, int *pnCount)
{
	int curCount = 1, nItemCount = 0;
	HWND hWndrtn = NULL;
	CWnd *pWnd = CWnd::FromHandle(hParentWnd);
	CWnd *pChildWnd = pWnd->GetWindow(GW_CHILD); //제일 위의 새끼를 검색한다.

	while(pChildWnd != NULL)
	{
		char lpszText[256];
		::GetWindowText(pChildWnd->GetSafeHwnd(), lpszText, 255);
		if(strstr(lpszText, strCaption)) // caption
		{
			nItemCount = curCount;
			hWndrtn = pChildWnd->GetSafeHwnd(); 
		}

		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT); //다음 컨트롤의 핸들을 구함
		curCount++;
	}

	if(nOffsetCount > 0)
		return FindOutControl(hParentWnd, nItemCount + nOffsetCount, pnTotal);
	
	if(pnTotal)
		*pnTotal = --curCount;

	if(pnCount)
		*pnCount = nItemCount;

	return hWndrtn;
}

void CCallPassFunc::TypingEnglish(WCHAR* Message)
{
	WCHAR NumSpecialChar[11]=L")!@#$%^&*(";
	WCHAR SpecialChar[12]=L"`-=\\[];',./";
	WCHAR ShiftSpecialChar[12]=L"~_+|{}:\"<>?";
	BYTE SpecialCharCode[11]={0xC0, 0xBD, 0xBB, 0xDC, 0xDB, 0xDD, 0xBA, 0xDE, 0xBC, 0xBE, 0xBF};

	int Length=wcslen(Message);

	for(int i=0; i<Length; i++)
	{
		if( Message[i] >= L'a' && Message[i] <= L'z' )
		{
			keybd_event((BYTE)Message[i]-L'a'+L'A', 0, 0, 0);
			keybd_event((BYTE)Message[i]-L'a'+L'A', 0, KEYEVENTF_KEYUP, 0);
		}
		else if( Message[i] >= L'A' && Message[i] <= L'Z' )
		{
			keybd_event(VK_SHIFT, 0, 0, 0);
			keybd_event((BYTE)Message[i], 0, 0, 0);
			keybd_event((BYTE)Message[i], 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
		}
		else if( Message[i] >= L'0' && Message[i] <= L'9' )
		{
			keybd_event((BYTE)Message[i], 0, 0, 0);
			keybd_event((BYTE)Message[i], 0, KEYEVENTF_KEYUP, 0);
		}
		else if( Message[i] == L' ' )
		{
			keybd_event((BYTE)Message[i], 0, 0, 0);
			keybd_event((BYTE)Message[i], 0, KEYEVENTF_KEYUP, 0);
		}
		else
		{
			for(int j=0; j<10; j++)
			{
				if( Message[i] == NumSpecialChar[j] )
				{
					keybd_event(VK_SHIFT, 0, 0, 0);
					keybd_event(L'0'+j, 0, 0, 0);
					keybd_event(L'0'+j, 0, KEYEVENTF_KEYUP, 0);
					keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
					break;
				}
				if( j == 9 )
				{
					for(int k=0; k<11; k++)
					{
						if( Message[i] == SpecialChar[k] )
						{
							keybd_event(SpecialCharCode[k], 0, 0, 0);
							keybd_event(SpecialCharCode[k], 0, KEYEVENTF_KEYUP, 0);
							break;
						}
						else if( Message[i] == ShiftSpecialChar[k] )
						{
							keybd_event(VK_SHIFT, 0, 0, 0);
							keybd_event(SpecialCharCode[k], 0, 0, 0);
							keybd_event(SpecialCharCode[k], 0, KEYEVENTF_KEYUP, 0);
							keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
							break;
						}
					}
				}
			}
		}
	}
}

void CCallPassFunc::TypingMessage(CString Message)
{
	TypingMessage(A2U((LPSTR)(LPCTSTR)Message));
}

void CCallPassFunc::TypingMessage(CHAR* Message)
{
	TypingMessage(A2U(Message));
}


void CCallPassFunc::TypingMessage(int nMessage)
{
	CHAR szTemp[MAX_PATH];
	sprintf(szTemp, "%d", nMessage);
	TypingMessage(A2U(szTemp));
}


void CCallPassFunc::TypingMessage(WCHAR* Message)
{
	static WCHAR Buf[10];
	int Length=wcslen(Message);

	for(int i=0; i<Length; i++)
	{
		if(m_hForeground && m_hForeground != ::GetForegroundWindow())
			::SetForegroundWindow(m_hForeground);

		if( Message[i] >= 0xAC00 && Message[i] <= 0xD7A3 )
		{
			wcscpy(Buf, ReplacementHangulFragment(Message[i]));
			TypingEnglish(Buf);
		}
		else
		{
			Buf[0] = Message[i];
			Buf[1] = L'\0';
			keybd_event(VK_HANGEUL, MapVirtualKey(VK_HANGEUL, 0), 0, 0);
			keybd_event(VK_HANGEUL, MapVirtualKey(VK_HANGEUL, 0), KEYEVENTF_KEYUP, 0);
			TypingEnglish(Buf);
			keybd_event(VK_HANGEUL, MapVirtualKey(VK_HANGEUL, 0), 0, 0);
			keybd_event(VK_HANGEUL, MapVirtualKey(VK_HANGEUL, 0), KEYEVENTF_KEYUP, 0);
		}
	}
}

WCHAR* CCallPassFunc::ReplacementHangulFragment(WCHAR Character)
{
	static const WCHAR Chosung[19][3]={{L"r"}, {L"R"}, {L"s"}, {L"e"}, {L"E"}, {L"f"}, {L"a"}, {L"q"}, {L"Q"}, {L"t"}, {L"T"}, {L"d"}, {L"w"}, {L"W"}, {L"c"}, {L"z"}, {L"x"}, {L"v"}, {L"g"}};
	static const WCHAR Joongsung[21][3]={{L"k"}, {L"o"}, {L"i"}, {L"O"}, {L"j"}, {L"p"}, {L"u"}, {L"P"}, {L"h"}, {L"hk"}, {L"ho"}, {L"hl"}, {L"y"}, {L"n"}, {L"nj"}, {L"np"}, {L"nl"}, {L"b"}, {L"m"}, {L"ml"}, {L"l"}};
	static const WCHAR Jongsung[28][3]={{L" "}, {L"r"}, {L"R"}, {L"rt"}, {L"s"}, {L"sw"}, {L"sg"}, {L"e"}, {L"f"}, {L"fr"}, {L"fa"}, {L"fq"}, {L"ft"}, {L"fx"}, {L"fv"}, {L"fg"}, {L"a"}, {L"q"}, {L"qt"}, {L"t"}, {L"T"}, {L"d"}, {L"w"}, {L"c"}, {L"z"}, {L"x"}, {L"v"}, {L"g"}};
	const int CommonNumber=Character-0xAC00;
	static WCHAR ReplacementFragment[10];

	int ChosungIndex=(int)(CommonNumber/(28*21));
	int JoongsungIndex=(int)((CommonNumber%(28*21))/28);
	int JongsungIndex=(int)(CommonNumber%28);

	wcscpy(ReplacementFragment, Chosung[ChosungIndex]);
	wcscat(ReplacementFragment, Joongsung[JoongsungIndex]);
	if( JongsungIndex != 0 )
	{
		wcscat(ReplacementFragment, Jongsung[JongsungIndex]);
	}

	return ReplacementFragment;
}

LPWSTR CCallPassFunc::A2U(LPCSTR lpData)
{
	m_lpwstr[0] = 0;
	MultiByteToWideChar(949, MB_COMPOSITE, lpData, -1, m_lpwstr, sizeof(m_lpwstr) / sizeof(m_lpwstr[0])); 
	return m_lpwstr;
} 