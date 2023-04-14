#pragma once



class CMkDatabase;


class CDebugReporter
{
public:
	CDebugReporter(CMkDatabase *pMkDb, CString strID, int nCompany);
	~CDebugReporter(void);

	BOOL FindDebugFileText(CString &strText);
	void Report();

protected:
	CMkDatabase *m_pDb;
	CString m_strID;
	int m_nCompany;

};
