#pragma once


typedef map<long, class CSearchPOI*> MAP_JUSO;

class CJusoGoKr
{
public:
	CJusoGoKr();
	~CJusoGoKr(void);
public:
	MAP_JUSO m_mapJuso;
	void SearchJuso(CString strSearch);
	BOOL ParseXml(char *sz);
	void GetPosXY(CString strBCode, CString strSan, CString strJibun1, CString strJibun2, class CRoadAddressData *data);

	MAP_JUSO *GetJusoMap() { return &m_mapJuso; }
};