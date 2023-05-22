#pragma once




class CPOIDataNew;
class CMkDatabase;
class CDisplayBarThread;


class AFX_EXT_CLASS CMakePOIData
{
public:
	CMakePOIData(CPOIDataNew *pPOINew, CMkDatabase *pMkDb = NULL, 
				CString strCity = "", BOOL bCapitalArea = FALSE,
				BOOL bUpdatePOINameForUserPOI = TRUE,
				BOOL bNotUseParitalUpdate = FALSE, long nSystemCode = 3);

	virtual ~CMakePOIData(void);

	BOOL MakeDongDataFromFile();
	BOOL MakeDongDataFromNetwork();
	BOOL MakePOIDataFromFile();
	int MakePOIDataFromNetwork(BOOL bOnlyChanged = FALSE);
	BOOL MakeAllFromNetwork(BOOL bDongOnly = FALSE);
	BOOL MakeAllFromFile(BOOL bDongOnly = FALSE);
	BOOL AutoLoad(BOOL bDongOnly = FALSE);
	void SetCity(CString strCity);
	CString GetRegionFileName(CString strFileName = "");
	void MakeBoundaryInfo(BOOL bFromFile = FALSE);
	BOOL CheckPOIVersion();
	BOOL StringDateToDate(CString strDate, COleDateTime &dtFileTime);
	CString DateToStringDate(COleDateTime dtFileTime);
	void FillDaeriDong(map<long, long> *pMap);

protected:
	CPOIDataNew *m_pPOINew;
	CMkDatabase *m_pMkDb;
	CString m_strCity;
	BOOL m_bCapitalArea;
	CString m_strNewPOIVersion;
	BOOL m_bUpdatePOINameForUserPOI;
	COleDateTime m_dtLastRefresh;
	BOOL m_bNotUseParitalUpdate;
	CDisplayBarThread *m_pDBT;
	long m_nSystemCode;
};
