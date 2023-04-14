#pragma once

#include <vector>
#include "json.h"// json.h,  jsoncpp.cpp, json-forwards.h 3개파일 경로가 맞아야함

using namespace std;

class CINaviPathSearch
{
public:
	CINaviPathSearch(BOOL bOnlyDistance, CPoint ptStart, CPoint ptEnd, CString strOption = "recommendation1");
	CINaviPathSearch(BOOL bOnlyDistance, LONG nStartPosX, LONG nStartPosY, LONG nEndPosX, LONG nEndPosY, CString strOption = "recommendation1");
	~CINaviPathSearch(void);

private:
	BOOL m_bParse;
	BOOL m_bOnlyDistance;
	CPoint m_ptStartPos;
	CPoint m_ptEndPos;
	CString m_strOption; 
	vector<CPoint> m_vecVia;
	Json::Value m_jsonRoot;	

	class CINaviPathSection *m_cINaviPathSection;

private:
	BOOL ParseJson();
	BOOL GetBodyJson(Json::Value &value);
	CString GetParameter();
	CString RouteStart(CString strUrl);
	CString GetStringFloat(float f);	
	virtual CString GetUrl();

public:
	void AddVia(CPoint ptVia);
	void AddVia(LONG nPosX, LONG nPosY);
	LONG GetViaCount() { return m_vecVia.size(); }
	LONG GetRouteDistance();
	LONG GetRouteDistance(vector<CPoint> &vec);
	LONG GetRouteDistanceVia(long nIndex);
	void SetOption(CString strOption) { m_strOption = strOption; }
};

class CINaviPathSection : public CINaviPathSearch
{
public:
	CINaviPathSection(BOOL bOnlyDistance, CPoint ptStart, CPoint ptEnd, CString strOption) : CINaviPathSearch( bOnlyDistance, ptStart, ptEnd, strOption) {} ;
	CINaviPathSection::~CINaviPathSection() {};

private:
	virtual CString GetUrl() { return "maps/v3.0/appkeys/SaENtIlAgnLuS0ru/route-normal-summary?"; };
};
