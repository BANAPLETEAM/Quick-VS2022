// stdafx.cpp : ǥ�� ���� ������ �����ϴ� �ҽ� �����Դϴ�.
// Quick.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj�� �̸� �����ϵ� ���� ������ �����մϴ�.

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