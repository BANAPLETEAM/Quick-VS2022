#pragma once

#include "MkPacket.h"
#include "VMemPool.h"
#include <vector>
#include <queue>
#include <map>
#include <utility>
#include "IocpHandler.h"
#include "MkLock.h"
#include "DefStrFunc.h"

#define SERVER_IP			"121.254.252.26" //BANA_UPDATE랑 맞춰야함
#define SERVER_PORT			4130
#define UPDATE_FILES	"update files\\"
#define UNIT_SIZE		100

#define MAIN_PROCESS_NAME		"QUICK.EXE"
#define APP_NAME				"SmartQ"
#define MAIN_DIR				"c:\\SmartQ\\"
#define SERVER_UPDATE_NAME		"SmartQ.exe"
#define UL_FILE_NAME			"SmartQ.INI"
#define UPDATE_PROCESS_NAME		"update.exe"

#define PT_AUTHENTICATION 3
#define PT_CHECK_CONN 8  
#define PT_UPDATE 9
#define PST_CHECK_UPDATE_EXE 10
#define PT_FILE_UPDATE 6

#define PST_SUCCESS 1
#define PST_ERROR 5
#define PST_FILE_TRAN_END 21
#define PST_REQUEST_FILE_NO_HANDLE 22

#define MAX_TRAN_COUNT			64
#define PST_FILE_TRAN 10
#define PST_FILE_DATA 11

///////////////////////////////////// CPacketData  /////////////////////////////////////////////////

class CPacketData
{
public:
	CPacketData() { nData = 0; }
	CPacketData(char* _szData) { SStrCpy2(szData, _szData); }
	CPacketData(int _nData) { nData = _nData; }

	union
	{
		char szData[UNIT_SIZE];
		int nData;
	};
};

///////////////////////////////////// CDataList  /////////////////////////////////////////////////

typedef vector<CPacketData> DATA_VECTOR;

class CDataList
{
public:
	CDataList() { }

	DATA_VECTOR vecData;

	void AddData(CString& strData)
	{
		AddData((LPSTR)(LPCTSTR)strData);
	}

	void AddData(char* szData)
	{
		vecData.push_back(CPacketData(szData));
	}

	void AddData(int nData)
	{
		vecData.push_back(CPacketData(nData));
	}

	UINT GetCount() { return vecData.size(); }
	UINT GetSize() { return vecData.size() * UNIT_SIZE; }
	char* GetDataPtr() { return (char*)&vecData[0]; }
	void SetData(char* pBuffer, DWORD dwSize)
	{
		DATA_VECTOR::iterator it;
		CPacketData data;

		vecData.assign(dwSize / UNIT_SIZE, data);
		memcpy(reinterpret_cast<char*>(&vecData[0]), pBuffer, dwSize);

		for (it = vecData.begin(); it != vecData.end(); it++)
			it->szData[UNIT_SIZE - 1] = 0;
	}

	const char* GetString(UINT n)
	{
		if (vecData.size() <= n)
			return "";

		return vecData.at(n).szData;
	}

	int GetInt(UINT n)
	{
		if (vecData.size() <= n)
			return 0;

		return vecData.at(n).nData;
	}

	template<typename T> CDataList(T t)
	{
		AddData(t);
	}

	template<typename T1, typename T2> CDataList(T1 t1, T2 t2)
	{
		AddData(t1); AddData(t2);
	}

	template<typename T1, typename T2, typename T3> CDataList(T1 t1, T2 t2, T3 t3)
	{
		AddData(t1); AddData(t2); AddData(t3);
	}

	template<typename T1, typename T2, typename T3, typename T4> CDataList(T1 t1, T2 t2, T3 t3, T4 t4)
	{
		AddData(t1); AddData(t2); AddData(t3); AddData(t4);
	}

	template<typename T1, typename T2, typename T3, typename T4, typename T5> CDataList(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
	{
		AddData(t1); AddData(t2); AddData(t3); AddData(t4); AddData(t5);
	}
};

///////////////////////////////////// CSpeedMeter  /////////////////////////////////////////////////

class CSpeedMeter
{
public:
	CSpeedMeter(void)
	{
		ZeroMemory(&m_dwTranBytes[0], sizeof(DWORD) * 10);
	}

	DWORD m_dwTranBytes[10];
	CCriticalSection m_cs;

	void IncreaseTranBytes(DWORD dwTranBytes)
	{
		//시간을 슬라이스해서 저장한다.
		CMkLock lock(m_cs);
		BYTE nIndex = (GetTickCount() % 1000) / 100;
		m_dwTranBytes[nIndex] += dwTranBytes;
		m_dwTranBytes[(nIndex + 1) % 10] = 0;
	}

	DWORD GetTranBps()
	{
		CMkLock lock(m_cs);
		DWORD dwBytes = 0;

		for (int i = 0; i < 10; i++)
			dwBytes += m_dwTranBytes[i];

		//slice 하나는 항상 0이다.
		return dwBytes * 10 / 9;
	}
};