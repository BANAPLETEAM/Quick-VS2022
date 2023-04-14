#pragma once

#include "afxtempl.h"
#include "MkType.h"

class CMkDatabase;
class CMkRecordset;
class CDisplayBar;


class CMkParameter;
class AFX_EXT_CLASS CMkCommand
{
public:
	CMkCommand(void);
	CMkCommand(CMkDatabase *pDatabase, BOOL bPreventCancel = FALSE, BOOL bNoThreadMode = FALSE);
	CMkCommand(CMkDatabase *pDatabase, CString strCommandText, BOOL bPreventCancel = FALSE, BOOL bNoThreadMode = FALSE);
	virtual ~CMkCommand(void);


protected:
	static CDisplayBarProgressInfo m_dbpiBasic;
	CString m_strQueryDebugInfo;
	CArray<CMkParameter*, CMkParameter*> m_Parameter;
	CString m_strCommandText;
	CMkDatabase *m_pDatabase;
	UINT m_nParameterSize;

	CMkRecordset *m_pRecordset;
	BOOL m_bPreventCancel;
	BOOL m_bNoThreadMode;
	BOOL m_bHideWaitCursor;
	BOOL m_bThreadRunningResult;
	HANDLE m_hRunningThread;
	HANDLE m_hUserStopEvent;
	DWORD m_dwProgressSize;
	CString& RemakeDisplayText(CString &strDisplayText);
	void RedrawProgressBar(CDisplayBarThread *pBar, CMkCommand *pCmd = NULL);
	void MsgInvalidStringParameter();


public:
	static CStringArray m_saExecute;

public:
	CMkParameter* AddParameter(CMkParameter *pParameter);
	CMkParameter* AddParameter(int nValue, enum cmkDir nDirection = typeInput);
	CMkParameter* AddParameter(UINT nValue, enum cmkDir nDirection = typeInput);
	CMkParameter* AddParameter(long nValue, enum cmkDir nDirection = typeInput);
	CMkParameter* AddParameter(double fValue, enum cmkDir nDirection = typeInput);
	CMkParameter* AddParameter(CString strValue, enum cmkDir nDirection = typeInput);
	CMkParameter* AddParameter(CString strValue, long nSize, enum cmkDir nDirection = typeInput);
	CMkParameter* AddParameter(COleDateTime dtValue, enum cmkDir nDirection = typeInput);

	CMkParameter* AddParameterRef(int &nValue, enum cmkDir nDirection = typeInput, BOOL bRefOutput = FALSE);
	CMkParameter* AddParameterRef(long &nValue, enum cmkDir nDirection = typeInput, BOOL bRefOutput = FALSE);
	CMkParameter* AddParameterRef(double &fValue, enum cmkDir nDirection = typeInput, BOOL bRefOutput = FALSE);
	CMkParameter* AddParameterRef(CString &strValue, enum cmkDir nDirection = typeInput, BOOL bRefOutput = FALSE);
	CMkParameter* AddParameterRef(COleDateTime &dtValue, enum cmkDir nDirection = typeInput, BOOL bRefOutput = FALSE);
	CMkParameter* AddParameterRef(CString &strValue, long nSize, enum cmkDir nDirection = typeInput, BOOL bRefOutput = FALSE);

	template<typename C> CMkParameter* AddParameterRefOutput(C &c, enum cmkDir nDirection = typeOutput);
	CMkParameter* AddParameterRefOutput(CString &strValue , long nSize);
	template<typename C> CMkParameter* AddParameterRefReturn(C &c);

	CMkParameter* AddParameter(enum cmkVT nType, enum cmkDir nDirection, long lSize);
	CMkParameter* AddParameter(enum cmkVT nType, enum cmkDir nDirection, long lSize, int nValue);
	CMkParameter* AddParameter(enum cmkVT nType, enum cmkDir nDirection, long lSize, long lValue);
	CMkParameter* AddParameter(enum cmkVT nType, enum cmkDir nDirection, long lSize, double fValue);
	CMkParameter* AddParameter(enum cmkVT nType, enum cmkDir nDirection, long lSize, CString strValue);
	CMkParameter* AddParameter(enum cmkVT nType, enum cmkDir nDirection, long lSize, COleDateTime time);
	CMkParameter* AddParameter(enum cmkVT nType, enum cmkDir nDirection, long lSize, void *pValue);

	BOOL Execute(CMkDatabase *pDatabase, CString strCommandText);
	BOOL Execute(CString strCommandText);
	BOOL Execute(CMkDatabase *pDatabase = NULL);
	BOOL ExecuteThreadMode(CString strDisplayText = "");
	BOOL ExecuteThreadModeDual(CMkCommand *pCmd2, CString strDisplayText = "");

	CMkDatabase *GetDatabase()	 { return m_pDatabase; }
	void SetRecordset(CMkRecordset *pRecordset) { m_pRecordset = pRecordset; }
	CMkRecordset *GetRecordset() { return m_pRecordset; }
	BOOL IsCypherPacket() { return m_strCommandText.Left(1) == "@";}
	BOOL IsPreventCancel() { return m_bPreventCancel;}
	BOOL IsNoThreadMode() { return m_bNoThreadMode; }
	void SetHideWaitCursor(BOOL bHideWaitCursor) { m_bHideWaitCursor = bHideWaitCursor;}
	BOOL IsHideWaitCursor() { return m_bHideWaitCursor;}


	void SetMkCommand(CMkDatabase *pDatabase, CString strCommandText, BOOL bPreventCancel = FALSE, BOOL bNoThreadMode = FALSE);
	void SetThreadRunningResult(BOOL bRet);
	HANDLE GetRunningEvent();
	CDisplayBarThread* ExecuteDisplay();
	CString GetQueryDebugInfo() { return m_strQueryDebugInfo;}
	void SetDatabase(CMkDatabase *pDatabase);
};


AFX_INLINE HANDLE CMkCommand::GetRunningEvent()
{
	return m_hRunningThread;	
}




class AFX_EXT_CLASS CMkParameter
{
public:
	CMkParameter(void);
	CMkParameter(int &nValue, enum cmkDir nDirection = typeInput, BOOL bRefOutput = FALSE);
	CMkParameter(UINT &nValue, enum cmkDir nDirection = typeInput, BOOL bRefOutput = FALSE);
	CMkParameter(long &nValue, enum cmkDir nDirection = typeInput, BOOL bRefOutput = FALSE);
	CMkParameter(double &fValue, enum cmkDir nDirection = typeInput, BOOL bRefOutput = FALSE);
	CMkParameter(CString &strValue, enum cmkDir nDirection = typeInput, BOOL bRefOutput = FALSE);
	CMkParameter(CString &strValue, long nSize, enum cmkDir nDirection = typeInput, BOOL bRefOutput = FALSE);
	CMkParameter(COleDateTime &dtValue, enum cmkDir nDirection = typeInput, BOOL bRefOutput = FALSE);
	CMkParameter(enum cmkVT nType, enum cmkDir nDirection, long lSize, void *pValue);
	virtual ~CMkParameter(void);

protected:
	PARAMETER_STRUCT *m_pParameter;
	void *m_pRefValue;

public:
	void InitParameter();
	int  SetParameter(enum cmkVT nType, enum cmkDir nDirection, long lSize, void *pValue = NULL, BOOL bRefOutput = FALSE);
	long GetValueSize() { return m_pParameter->lSize; }
	int  SetValue(long lSize, void *pValue);
	void SetValue(int nValue);
	int	 GetDirection() { return m_pParameter->nDirection; }

	BOOL GetValue(int &nValue);
	BOOL GetValue(long &lValue);
	BOOL GetValue(double &fValue);
	BOOL GetValue(COleDateTime &dtValue);
	BOOL GetValue(CString &strValue);

	int	GetInt();
	long GetLong();
	COleDateTime GetDate();
	CString GetString();
	double GetFloat();

	PARAMETER_STRUCT* GetParameter() { return m_pParameter; }

};

template<typename C> AFX_INLINE CMkParameter* CMkCommand::AddParameterRefOutput(C &c, enum cmkDir nDirection)
{
	return AddParameterRef(c, nDirection, TRUE);
}
template<typename C> AFX_INLINE CMkParameter* CMkCommand::AddParameterRefReturn(C &c)
{
	return AddParameterRef(c, typeReturn, TRUE);
}

