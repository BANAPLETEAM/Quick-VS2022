#include "stdafx.h"
#include "EncProfile.h"


unsigned char fixedkey[8] = {45,77,234,56,78,12,29,199};

CEncProfile::CEncProfile(void)
{
	m_hKey = HKEY_LOCAL_MACHINE;
	m_strSubKeyBase = "Software\\Logisoft\\";
}

CEncProfile::~CEncProfile(void)
{
}

void CEncProfile::WriteInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue)
{
	CString strSubKey = m_strSubKeyBase + lpszSection;
	HKEY hSubKey;
	long nRet;	

	if(ERROR_SUCCESS != ::RegOpenKeyEx(m_hKey, strSubKey, 0, KEY_ALL_ACCESS, &hSubKey))
	{
		DWORD dwDisposition;
		
		//키 미존재시 생성
		nRet = RegCreateKeyEx(m_hKey,
							strSubKey,
							NULL, "",
							REG_OPTION_NON_VOLATILE,
							KEY_ALL_ACCESS,
							NULL,
							&hSubKey, (LPDWORD)&dwDisposition);

		ASSERT(nRet == ERROR_SUCCESS);
	}

	char buffer[8];
	ZeroMemory(buffer, 8);
	nValue++;
	memcpy(buffer, (void*)&nValue, sizeof(int));
	deskey(fixedkey, EN0);
	des((unsigned char*)buffer, (unsigned char*)buffer);

	nRet = ::RegSetValueEx(hSubKey, lpszEntry, 0, REG_BINARY, 
						(BYTE*)buffer, 8);


	RegCloseKey(hSubKey);
	ASSERT(nRet == ERROR_SUCCESS);
}

void CEncProfile::WriteString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue)
{
	CString strSubKey = m_strSubKeyBase + lpszSection;
	HKEY hSubKey;
	long nRet;	


	if(ERROR_SUCCESS != ::RegOpenKeyEx(m_hKey, strSubKey, 0, KEY_ALL_ACCESS, &hSubKey))
	{
		DWORD dwDisposition;
		
		//키 미존재시 생성
		nRet = RegCreateKeyEx(m_hKey,
							(LPCTSTR)strSubKey,
							NULL, "",
							REG_OPTION_NON_VOLATILE,
							KEY_ALL_ACCESS,
							NULL,
							&hSubKey, (LPDWORD)&dwDisposition);
		ASSERT(nRet == ERROR_SUCCESS);
	}

	int length = strlen(lpszValue) + 8 - (strlen(lpszValue) % 8) % 8;
	char *buffer = new char[length + 1];
	ZeroMemory(buffer, length + 1);
	memcpy(buffer, (void*)lpszValue, strlen(lpszValue));
	deskey(fixedkey, EN0);

	for(int i = 0; i < length; i+=8)
		des((unsigned char*)buffer, (unsigned char*)buffer);

	nRet = ::RegSetValueEx(hSubKey, lpszEntry, 0, REG_BINARY, 
						(BYTE*)buffer, length);

	delete buffer;
	RegCloseKey(hSubKey);
	ASSERT(nRet == ERROR_SUCCESS);
}

int	CEncProfile::GetInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault)
{
	HKEY hSubKey;
	long nRet;	

	DWORD dwType;
	DWORD dwBytes = 8;
	BYTE  buffer[8];
	CString strSubKey = m_strSubKeyBase + lpszSection;
	int nRetValue = nDefault;

	ZeroMemory(buffer, 8);
	//레지스트리 키 오픈
	nRet = ::RegOpenKeyEx(m_hKey, strSubKey, 0, KEY_ALL_ACCESS, &hSubKey);
	if(nRet == ERROR_SUCCESS) {
		nRet = ::RegQueryValueEx(hSubKey, lpszEntry, 0, &dwType, buffer, &dwBytes);
		if(nRet == ERROR_SUCCESS) {
			deskey(fixedkey, DE1);
			des((unsigned char*)buffer, (unsigned char*)buffer);
			nRetValue = *((int*)&buffer);
			nRetValue--;
		}
	}
	RegCloseKey(hSubKey);
	return nRetValue;
}

CString CEncProfile::GetString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault)
{
	HKEY hSubKey;
	long nRet;	

	DWORD dwType;
	DWORD dwBytes = 1024;
	BYTE  buffer[1024];
	CString strSubKey = m_strSubKeyBase + lpszSection;
	CString strRetValue = lpszDefault;
	
	ZeroMemory(buffer, 1024);
	//레지스트리 키 오픈
	nRet = ::RegOpenKeyEx(m_hKey, strSubKey, 0, KEY_ALL_ACCESS, &hSubKey);
	if(nRet == ERROR_SUCCESS) {
		nRet = ::RegQueryValueEx(hSubKey, lpszEntry, 0, &dwType, buffer, &dwBytes);
		if(nRet == ERROR_SUCCESS) {
			deskey(fixedkey, DE1);
			for(int i = 0; i < dwBytes; i+=8)
				des((unsigned char*)buffer, (unsigned char*)buffer);
			strRetValue = (LPCTSTR)buffer;
		}
	}
	RegCloseKey(hSubKey);
	return strRetValue;
}