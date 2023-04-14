#pragma once

#include "POIData.h"

typedef struct{
	CString sSido;
	CString sGugun;
	CString sDong;
	CString sSido_Code;
	CString sGugun_Code;
	CString sDong_Code;
} JIBUN_STRUCT;

typedef map<string, JIBUN_STRUCT*> JIBUN_MAP;

class CJibunData
{
public:
	CJibunData(void);
	~CJibunData(void);

public:
	static JIBUN_MAP m_JibunMap;

public:
	void Insert(CString strFullName, JIBUN_STRUCT *pJibun);
	int GetJibunPoi(POI_DATA *pDongPoi, CString strLi, int nSan, CString strJibun, int &nX, int &nY);
	int GetJibunPoi(CString Code_Si,CString Code_Gu,CString Code_Dong,CString nSan,CString sJibun,int& nX,int& nY);
	int GetJibunPoi(CString sAddr,int& nX,int& nY);
	BOOL GetCount() { return (long)m_JibunMap.size(); }
	static BOOL LoadJibunData();
};
