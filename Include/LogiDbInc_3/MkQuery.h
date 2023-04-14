#pragma once

#include "MkType.h"


class CMkDatabase;
class CMkParameter;

class AFX_EXT_CLASS CMkQuery
{
public:
	CMkQuery(CMkDatabase *pMkDb, CString strQuery, BOOL bPreventCancel = FALSE, BOOL bNoThreadMode = FALSE);
	virtual ~CMkQuery(void);

	template<typename T> CMkParameter* AddParam(T t);
	template<typename T> CMkParameter* AddOutParam(T t, enum cmkDir nDir = typeOutput);
	template<typename T> CMkParameter* AddRetParam(T t);
	template<typename T> CMkParameter* AddOutParamRef(T &t, enum cmkDir nDir = typeOutput);
	template<typename T> CMkParameter* AddRetParamRef(T &t);
	CMkParameter* AddOutParam(CString strValue, long nSize);
	CMkParameter* AddOutParamRef(CString &strValue, long nSize);
	BOOL Execute();

	CMkRecordset *GetRS();
	void MoveNext();
	void MovePrev();
	void MoveFirst();
	void MoveLast();
	BOOL IsBOF();
	BOOL IsEOF();
	int GetRecordCount();
	BOOL IsMultiRecordset();
	BOOL IsSecondRecordset();
	template<typename C> void GetFieldValue(LPCTSTR lpFieldName, C &cvalue);
	template<typename C> void GetFieldValueS(int nIndex, C &cValue);
	template<typename C> void GetFieldValueS(LPCTSTR lpFieldName, C &cValue);

protected:
	CMkDatabase *m_pMkDb;
	CMkCommand *m_pCmd;
	CMkRecordset *m_pRs;

};


template<typename T> AFX_INLINE CMkParameter* CMkQuery::AddParam(T t) 
{ return m_pCmd->AddParameter(t);}

template<typename T> AFX_INLINE CMkParameter* CMkQuery::AddOutParam(T t, enum cmkDir nDir) 
{ return m_pCmd->AddParameter(t, nDir);}

template<typename T> AFX_INLINE CMkParameter* CMkQuery::AddOutParamRef(T &t, enum cmkDir nDir) 
{ return m_pCmd->AddParameterRefOutput(t);}

AFX_INLINE CMkParameter* CMkQuery::AddOutParam(CString strValue, long nSize) 
{ return m_pCmd->AddParameter(strValue, nSize, typeOutput);}

AFX_INLINE CMkParameter* CMkQuery::AddOutParamRef(CString &strValue, long nSize) 
{ return m_pCmd->AddParameterRefOutput(strValue, nSize); }

AFX_INLINE CMkRecordset *CMkQuery::GetRS() { return m_pRs; }

template<typename T> AFX_INLINE CMkParameter* CMkQuery::AddRetParam(T t)
{ return m_pCmd->AddParameter(t, typeReturn);}

template<typename T> AFX_INLINE CMkParameter* CMkQuery::AddRetParamRef(T &t)
{ return m_pCmd->AddParameterRefReturn(t);}


AFX_INLINE void CMkQuery::MoveNext() { m_pRs->MoveNext();}
AFX_INLINE void CMkQuery::MovePrev() { m_pRs->MovePrev();}
AFX_INLINE void CMkQuery::MoveFirst() { m_pRs->MoveFirst();}
AFX_INLINE void CMkQuery::MoveLast() { m_pRs->MoveLast();}
AFX_INLINE BOOL CMkQuery::IsBOF() { return m_pRs->IsBOF();}
AFX_INLINE BOOL CMkQuery::IsEOF() { return m_pRs->IsEOF();}
AFX_INLINE int CMkQuery::GetRecordCount() { return m_pRs->GetRecordCount();}
AFX_INLINE BOOL CMkQuery::IsMultiRecordset() { return m_pRs->IsMultiRecordset();}
AFX_INLINE BOOL CMkQuery::IsSecondRecordset() { return m_pRs->IsSecondRecordset();}

template<typename T> AFX_INLINE void CMkQuery::GetFieldValue(LPCTSTR lpFieldName, T &t)
{ m_pRs->GetFieldValue(lpFieldName, t);}

template<typename T> AFX_INLINE void CMkQuery::GetFieldValueS(int nIndex, T &t)
{ m_pRs->GetFieldValueS(nIndex, t);}

template<typename T> AFX_INLINE void CMkQuery::GetFieldValueS(LPCTSTR lpFieldName, T &t)
{ m_pRs->GetFieldValue(lpFieldName, t);}
