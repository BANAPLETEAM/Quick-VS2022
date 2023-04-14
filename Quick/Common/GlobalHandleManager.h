#pragma once


enum { HT_BRUSH = 0, HT_PEN = 1};

typedef map<pair<pair<long, long>,long>, HANDLE> GLOBAL_HANDLE_MAP;

class CGlobalHandleManager
{
public:
	CGlobalHandleManager(void);
	virtual ~CGlobalHandleManager(void);

protected:
	GLOBAL_HANDLE_MAP m_mapHandle;
	CCriticalSection m_cs;
	HBRUSH m_hNullBrush;

public:
	HPEN GetPenObject(COLORREF cr, int nLine);
	HBRUSH GetBrushObject(COLORREF cr, BOOL bNullBrush = FALSE);

};
