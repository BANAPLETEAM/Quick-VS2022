#pragma once

#include <vector>

typedef vector<USHORT> BOUNDARY_VEC;

class CPOIDataNew;
class CPOIUnit;

class AFX_EXT_CLASS CPOIBoundary
{
public:
	CPOIBoundary(CPOIDataNew *poiNew, BOOL bAutoDelete = FALSE, CString strSido = "", CString strsido2 = "",
			CString strSido3 = "", CString strSido4 = "", CString strSido5 = "");
	virtual ~CPOIBoundary(void);

	void AddSido(CString strSido, CString strSido2 = "", 
			CString strSido3 = "", CString strSido4 = "", CString strSido5 = "");
	BOOL Has(CPOIUnit *pPOI);
	BOOL Has(long nDongID);
	BOOL Has(CString strSido);
	void RemoveAll();
	void Save();
	BOOL Load();
	CString GetSido();
	BOOL IsAutoDelete();
	BOOL IsSameBoundary(CPOIBoundary *pPOIBoundary);
	CPOIBoundary& operator = (const CPOIBoundary &p);

public:
	BOUNDARY_VEC m_vecBoundary;

protected:
	void CheckSort();
	void AddSidoReal(CString strSido);

protected:
	CString m_strSido;
	CPOIDataNew *m_poiNew;
	BOOL m_bSort;
	BOOL m_bAutoDelete;

};
