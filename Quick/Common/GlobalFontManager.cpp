#include "stdafx.h"
#include "globalfontmanager.h"
#include "MkLock.h"

CGlobalFontManager::CGlobalFontManager(void)
{
}

CGlobalFontManager::~CGlobalFontManager(void)
{
	CMkLock lock(&m_cs);

	GLOBAL_FONT_MAP::iterator it;
	for(it = m_mapFont.begin(); it != m_mapFont.end(); ++it)
	{
        CFont *pFont = (*it).second;
		//if(pFont)
			//delete pFont; //Á¶¼ºÀÏ 
	}
}

CFont* CGlobalFontManager::GetFont(CString strFaceName, int nSize, int nWeight)
{
	CMkLock lock(&m_cs);
	GLOBAL_FONT_MAP::iterator it;
	it = m_mapFont.find(make_pair(make_pair(nSize, nWeight), string(strFaceName)));

	if(it != m_mapFont.end())
	{
		CFont *pFont = (*it).second;
		if(pFont)
			return pFont;
		else
			m_mapFont.erase(it);
	}

	LOGFONT lf = {15,0,0,0,FW_BOLD,0,0,0,HANGUL_CHARSET,0,0,0,0,"¸¼Àº °íµñ"};
	lf.lfHeight = nSize;
	lf.lfWeight = nWeight;
	lf.lfQuality = 5;
	strcpy(lf.lfFaceName, strFaceName);
	
	CFont *pNewFont = new CFont;
	pNewFont->CreateFontIndirect(&lf);

	m_mapFont.insert(GLOBAL_FONT_MAP::value_type(make_pair(make_pair(nSize, nWeight), string(strFaceName)), pNewFont));

	g_bana_log->Print("CREATE_FONT: %s, %d, BOLD:%d\n", strFaceName, nSize, nWeight);

	return pNewFont;

}

LOGFONT* CGlobalFontManager::GetLogFont(CString strFaceName, int nSize, int nWeight)
{
	ZeroMemory(&m_lfTemp, sizeof(LOGFONT));
	m_lfTemp.lfHeight = nSize;
	m_lfTemp.lfWeight = nWeight;
	m_lfTemp.lfQuality = 5;
	m_lfTemp.lfCharSet = HANGUL_CHARSET;
	strcpy(m_lfTemp.lfFaceName, strFaceName);
	return &m_lfTemp;
}
