#pragma once


typedef map<pair<pair<long, long>,string>, CFont*> GLOBAL_FONT_MAP;


class CGlobalFontManager
{
public:
	CGlobalFontManager(void);
	virtual ~CGlobalFontManager(void);

protected:
	GLOBAL_FONT_MAP m_mapFont;
	CCriticalSection m_cs;
	LOGFONT m_lfTemp;

public:
	CFont *GetFont(CString strFaceName, int nSize, int nWeight = FW_NORMAL);
	LOGFONT* GetLogFont(CString strFaceName, int nSize, int nWeight = FW_NORMAL);

};
