#pragma once

#include "POIDataNew.h"

class CMkDatabase;

class AFX_EXT_CLASS CPOIDataAddress
{
public:
	CPOIDataAddress(void);
	CPOIDataAddress(CMkDatabase *pDB, CPOIDataNew *pData);
	~CPOIDataAddress(void);

protected:
	int QueryJibun(SEARCH_POI_VEC &v, SEARCH_POI_VEC &vecAddress);

public:
	CPOIDataNew *m_pPOIData;
	CString m_strKeyword;
	CString m_strKeywordIncSpace;
	CString m_strJibun1;
	CString m_strJibun2;
	BOOL m_bSan;
	CMkDatabase *m_pDB;

	void SetAddressText(CString strText);
	void SetDatabase(CMkDatabase *pDB);
	void SetPOIDataNew(CPOIDataNew *pData);
	int GetAddressList(SEARCH_POI_VEC &vecAddress, BOOL bCheckValidate = FALSE);
	CString MakeJibunString(BOOL bSan, int nJibun1, int nJibun2);
	static BOOL ResolveJibunString(CString strSrc, CString &strJibun1, CString &strJibun2, BOOL &bSan);
	static BOOL CheckJibunSearch(CString strSrc, BOOL bExceptResolve = FALSE);
	static BOOL GetNearAddress(CMkDatabase *pDb, long nPosX, long nPosY, long &nDongID, CString &strAddress);

};

AFX_INLINE void CPOIDataAddress::SetDatabase(CMkDatabase *pDB)
{
	m_pDB = pDB;
}

AFX_INLINE void CPOIDataAddress::SetPOIDataNew(CPOIDataNew *pData)
{
	m_pPOIData = pData;
}
