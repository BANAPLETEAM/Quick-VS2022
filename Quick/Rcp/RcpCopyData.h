#pragma once

#define INSERT_RCP_DATA(x) data.InsertData(#x, x);
#define GET_RCP_DATA(x) pData->GetValue(#x, x);

typedef map<CString, CString> RCP_COPY_DATA_MAP;

class CRcpCopyData
{
public:
	CRcpCopyData(void);
	~CRcpCopyData(void);

	void InsertData(CString strKey, CString strData);
	void InsertData(CString strKey, int nData);
	void InsertData(CString strKey, UINT nData);
	void InsertData(CString strKey, COleDateTime dtDate);
	void InsertData(CString strKey, double fData);
	void InsertData(CString strKey, float fData);

	char* MakePacket();
	BOOL PacketToMap(char *szPacket);

	CString GetValue(CString strKey, CString &strData);
	int GetValue(CString strKey, int &nData);
	long GetValue(CString strKey, long &nData);
	COleDateTime GetValue(CString strKey, COleDateTime &dtDate);
	double GetValue(CString strKey, double &fData);
	float GetValue(CString strKey, float &fData);

protected:
	RCP_COPY_DATA_MAP m_mapRcpCopyData;
	char *m_pGlobalStack;

};
