// stdafx.cpp : 표준 포함 파일을 포함하는 소스 파일입니다.
// Quick.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj는 미리 컴파일된 형식 정보를 포함합니다.

#include "stdafx.h"
 
BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	MONITORINFOEX mi;
	CDisplayBar* pBar = (CDisplayBar*)dwData;

	mi.cbSize = sizeof(MONITORINFOEX);
	GetMonitorInfo(hMonitor, (MONITORINFOEX*)&mi);
	pBar->m_aryMonitors.Add(mi);
	return TRUE;
}