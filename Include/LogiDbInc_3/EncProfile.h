#pragma once


extern "C" {
#include "d3des.h"
}

class CEncProfile
{
public:
	CEncProfile(void);
	virtual ~CEncProfile(void);

public:
	void SetRegKey(HKEY hKey, CString strSubKeyBase) {
		m_hKey = hKey;
		m_strSubKeyBase = "\\Software\\";
		m_strSubKeyBase += strSubKeyBase;
		m_strSubKeyBase += "\\";
	}

	void WriteInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue);
	void WriteString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue);
	int	GetInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault);
	CString GetString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue);

protected:
	HKEY m_hKey;
	CString m_strSubKeyBase;

};
