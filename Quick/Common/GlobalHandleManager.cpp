#include "stdafx.h"
#include "GlobalHandleManager.h"
#include "MkLock.h"

CGlobalHandleManager::CGlobalHandleManager(void)
{
	m_hNullBrush = 0;
}

CGlobalHandleManager::~CGlobalHandleManager(void)
{
	CMkLock lock(&m_cs);

	GLOBAL_HANDLE_MAP::iterator it;
	for(it = m_mapHandle.begin(); it != m_mapHandle.end(); it++)
	{
        HANDLE hHandle = (*it).second;
		DeleteObject(hHandle);
	}
}

HPEN CGlobalHandleManager::GetPenObject(COLORREF cr, int nLine)
{
	CMkLock lock(&m_cs);
	GLOBAL_HANDLE_MAP::iterator it;
	it = m_mapHandle.find(make_pair(make_pair((long)cr, nLine), (long)HT_PEN));

	if(it != m_mapHandle.end())
	{
		return (HPEN)(*it).second;
	}

	HPEN hPen = CreatePen(PS_SOLID, nLine, cr);
	m_mapHandle.insert(GLOBAL_HANDLE_MAP::value_type(make_pair(make_pair((long)cr, nLine), (long)HT_PEN), hPen));

	g_bana_log->Print("CREATE PEN: LINE=%d, r=%d, g=%d, b=%d\n", nLine, GetRValue(cr), GetGValue(cr), GetBValue(cr));

	return hPen;
}

HBRUSH CGlobalHandleManager::GetBrushObject(COLORREF cr, BOOL bNullBrush)
{
	if(bNullBrush)
	{
		if(!m_hNullBrush)
			m_hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		return m_hNullBrush;
	}

	CMkLock lock(&m_cs);
	GLOBAL_HANDLE_MAP::iterator it;
	it = m_mapHandle.find(make_pair(make_pair((long)cr, 0), (long)HT_BRUSH));

	if(it != m_mapHandle.end())
	{
		return (HBRUSH)(*it).second;
	}

	HBRUSH hBrush = CreateSolidBrush(cr);
	m_mapHandle.insert(GLOBAL_HANDLE_MAP::value_type(make_pair(make_pair((long)cr, 0), (long)HT_BRUSH), hBrush));

	g_bana_log->Print("CREATE BRUSH: r=%d, g=%d, b=%d\n", GetRValue(cr), GetGValue(cr), GetBValue(cr));

	return hBrush;
}
