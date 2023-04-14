#pragma once

#include "MkType.h"

#include <map>

using namespace std;

typedef map<string, int> STRING_MAP;

typedef int (*GENERICCOMPAREFN)(const void * elem1, const void * elem2);

#define CUTOFF 8	/* testing shows that this is good value */


class CMkDatabase;
class CMkCommand;


class AFX_EXT_CLASS CMkRecordset
{
public:
	CMkRecordset(void);
	CMkRecordset(CMkDatabase *pDatabase);
	CMkRecordset(CMkCommand *pCmd);
	virtual ~CMkRecordset(void);

	void Initialize();

protected:
	CMkDatabase *m_pDatabase;
	CMkCommand *m_pCommand;
	CMkRecordset *m_pRs2;		//이중레코드셋

	char *m_pChunk;
	char *m_pRecordset;
	UINT m_nSize;		//chunk size


	FIELD_STRUCT *m_pField;
	DWORD *m_pIndex;	//index pointer
	UINT m_nFieldCount;
	UINT m_nRecordCount;
	int m_nCurRecord;

	int m_nSortedColumn;
	BOOL m_bSortAscending;

	enum ListOperatorType { 
		ELOT_LT = 0,    //  <   less than
		ELOT_GT,  //  >   greater than
		ELOT_LTE, //  <=  less than or equal
		ELOT_GTE, //  >=  greather than or equal
		ELOT_EQ   //  ==  equal
	};

	BOOL m_bDisplayError;
	long m_nPreTranslateField;

protected:
	//using with sorting
	inline void GetFieldValueSort(int nRecord, int &nValue);
	inline void GetFieldValueSort(int nRecord, COleDateTime &dtValue);
	inline void GetFieldValueSort(int nRecord, CString &strValue);

	int CompareInt(const void* pData1, const void* pData2);
	int CompareString(const void* pData1, const void* pData2);
	int CompareDate(const void* pData1, const void* pData2);
	int CompareStringW(const void* pData1, const void* pData2);

	void QsortInt(void *base, unsigned num, unsigned width);
	void QsortString(void *base, unsigned num, unsigned width);
	void QsortStringW(void* base, unsigned num, unsigned width);
	void QsortDate(void *base, unsigned num, unsigned width);
	void MakePlainText(void* pChunk, int nSize);
	void FreeFieldNameBuffer();
	void DeleteObject();
	BOOL NoThreadExecuteWithSEH();

public:

	void SetChunk(void* pChunk, int nSize);
	BOOL Execute(CMkCommand *pCmd, CString strDisplayText = "");
	BOOL Execute(CMkCommand *pCmd1, CMkCommand *pCmd2, CString strDisplayText = "");
	BOOL ExecuteRecordsetOnly(UINT &nType, UINT &nSubType, UINT &nSize, char *szPacket = NULL);
	void SetCommand(CMkCommand *pCmd) { m_pCommand = pCmd;}

	BOOL Parser();
	void Close();

	void MoveNext();
	void MovePrev();
	void MoveFirst();
	void MoveLast();
	BOOL IsBOF();
	BOOL IsEOF();
	int GetRecordCount();

	inline BOOL IsMultiRecordset();
	inline BOOL IsSecondRecordset();

	void GetFieldValue(int nIndex, BYTE &cValue);
	void GetFieldValue(int nIndex, bool &bValue);
	void GetFieldValue(int nIndex, unsigned short int &usValue);
	void GetFieldValue(int nIndex, int &nValue);
	void GetFieldValue(int nIndex, long &lValue);
	void GetFieldValue(int nIndex, unsigned long &lValue);
	void GetFieldValue(int nIndex, unsigned int &lValue);
	void GetFieldValue(int nIndex, float &fValue);
	void GetFieldValue(int nIndex, double &dValue);
	void GetFieldValue(int nIndex, COleDateTime &dtValue);
	void GetFieldValue(int nIndex, CString &strValue);
	void GetFieldValue(int nIndex, char *szValue);
	void GetFieldValue(int nIndex, WCHAR *wszValue);
	void GetFieldValue(int nIndex, void **pValue, int &nSize);


	template<typename C> void GetFieldValue(LPCTSTR lpFieldName, C &cvalue);
	template<typename C> void GetFieldValueS(int nIndex, C &cValue);
	template<typename C> void GetFieldValueS(LPCTSTR lpFieldName, C &cValue);

	void GetFieldValue(LPCTSTR lpFieldName, void **pValue, int &nSize);
	void GetFieldValueS(int nIndex, void **pValue, int &nSize);
	void GetFieldValueS(LPCTSTR lpFieldName, void **pValue, int &nSize);

	int  GetFieldInt(int nIndex);
    int  GetFieldInt(LPCTSTR lpFieldName);
	long GetFieldLong(int nIndex);
	long GetFieldLong(LPCTSTR lpFieldName);
	COleDateTime GetFieldDate(int nIndex);
	COleDateTime GetFieldDate(LPCTSTR lpFieldName) ;
	CString GetFieldString(int nIndex) ;
	CString GetFieldString(LPCTSTR lpFieldName) ;

	CString GetFieldName(int nIndex) ;
	void SetFieldName(int nIndex, CString strFiledName);
	int GetFiledCount() { return m_nFieldCount; }
	int GetFieldType(int nIndex);
	CString GetFieldValueToString(int nIndex) ;

	void SetSort(int nColumn, BOOL bAscending);
	void SetSort(LPCTSTR lpFieldName, BOOL bAscending);	
	BOOL OpenFromFile(CString strPath, BOOL bEncrypt = FALSE, char *deskey = NULL);

	CMkRecordset* GetSecondRecordset() { return m_pRs2;}
	int GetRecordsetIndex();
	inline BOOL TranslateFieldName(LPCTSTR lpFieldName, int &nCol);
	inline void DisplayFieldNameError(LPCTSTR lpFieldName);

};


template<typename T> 
AFX_INLINE void CMkRecordset::GetFieldValue(LPCTSTR lpFieldName, T &t)
{
	int nIndex;
	if(!TranslateFieldName(lpFieldName, nIndex))
		DisplayFieldNameError(lpFieldName);
	else
		GetFieldValue(nIndex, t);
}

template<typename T>
AFX_INLINE void CMkRecordset::GetFieldValueS(int nIndex, T &t)
{
	if(IsSecondRecordset())
		m_pRs2->GetFieldValue(nIndex, t);
	else
		GetFieldValue(nIndex, t);
}

template<typename T> 
AFX_INLINE void CMkRecordset::GetFieldValueS(LPCTSTR lpFieldName, T &t)
{
	if(IsSecondRecordset())
		m_pRs2->GetFieldValue(lpFieldName, t);
	else
		GetFieldValue(lpFieldName, t);
}
