#include "stdafx.h"
#include "MkRecordset.h"
#include "MkDatabase.h"
#include "MkType.h"
#include "oledb.h"
#include "d3des2.h"



#define INDEX(x, y) *(m_pIndex + m_nFieldCount * y + x)

void CMkRecordset::Initialize()
{
	m_pRs2 = NULL;
	m_pDatabase = NULL;
	m_pCommand = NULL;
	m_pChunk = NULL;
	m_pRecordset = NULL;
	m_pField = NULL;
	m_nSize = 0;
	m_nFieldCount = 0;
	m_nRecordCount = 0;
	m_pIndex = NULL;
	m_bDisplayError = FALSE;
	m_nCurRecord = 0;
	m_nPreTranslateField = 0;
}


CMkRecordset::CMkRecordset(void)
{
	Initialize();
}

CMkRecordset::CMkRecordset(CMkDatabase *pDatabase)
{
	Initialize();
	m_pDatabase = pDatabase;
}

CMkRecordset::CMkRecordset(CMkCommand *pCmd)
{
	Initialize();
	m_pCommand = pCmd;
}

CMkRecordset::~CMkRecordset(void)
{
	DeleteObject();
}



void CMkRecordset::MoveNext()
{
	m_nPreTranslateField = 0;
	if(IsSecondRecordset())
	{
		m_pRs2->MoveNext();
		m_nCurRecord++; 
	}
	else
	{
		m_nCurRecord++; 
	}
}

void CMkRecordset::MovePrev()
{
	m_nPreTranslateField = 0;
	if(IsSecondRecordset())
	{
		m_pRs2->MovePrev();
		m_nCurRecord--;
	}
	else
	{
		m_nCurRecord--;
	}

}

void CMkRecordset::MoveFirst()
{
	m_nPreTranslateField = 0;
	m_nCurRecord = 0;
	if(IsMultiRecordset())
		m_pRs2->MoveFirst();
}

void CMkRecordset::MoveLast()
{
	m_nPreTranslateField = 0;
	if(IsMultiRecordset())
	{
		m_pRs2->MoveLast();
		m_nCurRecord = m_nRecordCount + m_pRs2->m_nRecordCount - 1;
	}
	else
	{
		m_nCurRecord = m_nRecordCount - 1;
	}
}

BOOL CMkRecordset::IsBOF()
{
	return m_nCurRecord == -1;
}

BOOL CMkRecordset::IsEOF()
{
	if(IsSecondRecordset())
		return m_pRs2->IsEOF();
	else 
		return m_nCurRecord == m_nRecordCount;
}

int CMkRecordset::GetRecordCount()
{
	if(IsMultiRecordset())
		return m_nRecordCount + m_pRs2->GetRecordCount();
	else
		return m_nRecordCount;
}


BOOL CMkRecordset::IsMultiRecordset()
{
	return m_pRs2 ? TRUE : FALSE;
}

BOOL CMkRecordset::IsSecondRecordset()
{
	return m_pRs2 && m_nCurRecord >= m_nRecordCount;
}



void CMkRecordset::SetChunk(void* pChunk, int nSize)
{
	Close();

    m_pChunk = (char*)new char[nSize];
	memcpy(m_pChunk, pChunk, nSize);

	if(m_pDatabase)
		m_pDatabase->SetLastRecordsetChunk(m_pChunk, nSize);
	else if(m_pCommand)
	{
		if(m_pCommand->GetDatabase())
		{
			m_pCommand->GetDatabase()->SetLastRecordsetChunk(m_pChunk, nSize);
		}
	}

	if(m_pCommand->IsCypherPacket())
		MakePlainText(m_pChunk, nSize);
}

BOOL CMkRecordset::Execute(CMkCommand *pCmd, CString strDisplayText)
{	
	//FreeFieldNameBuffer();
	m_bDisplayError = FALSE;
	BOOL bRet = FALSE;

	if(pCmd->IsNoThreadMode())
	{
		m_pCommand = pCmd;
		bRet = NoThreadExecuteWithSEH();
	}
	else
	{
		m_pCommand = pCmd;
		pCmd->SetRecordset(this);
		bRet = pCmd->ExecuteThreadMode(strDisplayText);
	}

	return bRet;
}

BOOL CMkRecordset::NoThreadExecuteWithSEH()
{
	BOOL bRet = FALSE;

	__try
	{
		m_pCommand->SetRecordset(this);

		if(m_pCommand->Execute())
			bRet = Parser();
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		MessageBox(m_pDatabase->GetSafeHwnd(), "쿼리 실행중에 오류가 발생했습니다.\n재시도 하시기 바랍니다.", "확인", 
			MB_ICONINFORMATION);
		bRet = FALSE;
	}

	return bRet;
}

BOOL CMkRecordset::Execute(CMkCommand *pCmd1, CMkCommand *pCmd2, CString strDisplayText)
{
	//FreeFieldNameBuffer();

	if(m_pRs2)
		delete m_pRs2;
	
	m_pRs2 = new CMkRecordset(pCmd2);

	m_bDisplayError = FALSE;
	m_pCommand = pCmd1;
	pCmd1->SetRecordset(this);
	m_pRs2->SetCommand(pCmd2);
	pCmd2->SetRecordset(m_pRs2);

	return pCmd1->ExecuteThreadModeDual(pCmd2, strDisplayText);
}

BOOL CMkRecordset::ExecuteRecordsetOnly(UINT &nType, UINT &nSubType, UINT &nSize, char *szPacket)
{
	//FreeFieldNameBuffer();

	char *pRecord = (char*)m_pDatabase->ExecuteCommand(nType, nSubType, nSize, szPacket);

	if(pRecord)
	{
		DeleteObject();

		m_pChunk = (char*)new char[nSize];
		memcpy(m_pChunk, pRecord, nSize);

		free(pRecord);
		return Parser();
	}
	else 
		return FALSE;
}


BOOL CMkRecordset::OpenFromFile(CString strPath, BOOL bEncrypt, char *pDesKey)
{
	HANDLE hFile, hFileMap;
	unsigned char *pBasePointer;
	DWORD dwSize;
	BOOL bRet = FALSE;

	hFile = CreateFile((LPSTR)(LPCTSTR)strPath, GENERIC_READ, 
					FILE_SHARE_READ, NULL, 
					OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			
	if(INVALID_HANDLE_VALUE != hFile)
	{
		hFileMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
		dwSize = GetFileSize(hFile, 0);
		pBasePointer = (unsigned char*) MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, dwSize);

		DeleteObject();

		m_pChunk = new CHAR[dwSize + 1];
		memcpy(m_pChunk, pBasePointer, dwSize);

		if(bEncrypt) {
			MBYTE deskey[8] = {123,77,02,26,28,22, 0,17};

			//복호화하기
			if(pDesKey)
			{
				for(int i = 0; i < 8; i++)
					deskey[i] = pDesKey[i];
			}

			des_init(deskey, 0, false);
			for(int i = 0;i < dwSize - 8; i+=8)
				des_ecb(FALSE, (MBYTE*)m_pChunk, i, (MBYTE*)m_pChunk, i);
		}


		UnmapViewOfFile((LPVOID)pBasePointer);
		CloseHandle(hFileMap);
		bRet = Parser();
	}

	CloseHandle(hFile);
	return bRet;
}

void CMkRecordset::Close()
{
	DeleteObject();
}

void CMkRecordset::DeleteObject()
{
	if(m_pChunk)
		delete[] (char*)m_pChunk;

	if(m_pIndex)
		delete[] (char*)m_pIndex;

	m_pChunk = NULL;
	m_pIndex = NULL;
}

BOOL CMkRecordset::Parser()
{
	UINT nCursor = 0;
	m_nCurRecord = 0;
	m_nFieldCount = *((UINT*)m_pChunk);
	m_nRecordCount = *((UINT*)(m_pChunk + sizeof(UINT)));
	m_pField = (FIELD_STRUCT*)(m_pChunk + sizeof(UINT) * 2);
	m_pRecordset = (char*)(m_pField + m_nFieldCount);

	if(!m_pIndex) 
	{
		delete[] (char*)m_pIndex;
		m_pIndex = NULL;
	}

	m_pIndex = (DWORD*)new char[sizeof(UINT) * m_nFieldCount * m_nRecordCount];

	for(int n = 0; n < m_nRecordCount; n++) {
		for(int c = 0; c < m_nFieldCount; c++) {
			//g_bana_log->Print("m_pField[%d] = %d, %d, %s\n", c, m_pField[c].lSize, m_pField[c].nType, m_pField[c].szFieldName);

			if(m_pField[c].nType == typeLong) {
				INDEX(c, n) = (DWORD)(m_pRecordset + nCursor);
				nCursor += sizeof(UINT);
			}
			else if(m_pField[c].nType == typeDate) {
				INDEX(c, n) = (DWORD)(m_pRecordset + nCursor);

				if(*((DWORD*)INDEX(c, n)) == 0xFFFFFFFF) {
					INDEX(c, n) = NULL;
					nCursor += sizeof(long);
				}
				else {
					nCursor += sizeof(DBTIMESTAMP);
				}
			}
			else if(m_pField[c].nType == typeString ||
					m_pField[c].nType == typeWStr) {

				*(m_pIndex + m_nFieldCount * n + c) = (DWORD)(m_pRecordset + nCursor);
				DWORD nLen = *((long*)INDEX(c, n));
				if(nLen == NULL) {
					*(m_pIndex + m_nFieldCount * n + c) = NULL;
					nCursor += sizeof(long);
				}
				else {
					*(m_pIndex + m_nFieldCount * n + c) = (DWORD)(m_pRecordset + nCursor + sizeof(long));
					nCursor += sizeof(long) + nLen;
				}
			}
			else if(m_pField[c].nType == typeFloat) {
				INDEX(c, n) = (DWORD)(m_pRecordset + nCursor);
				nCursor += sizeof(double);
			}
			else {
				MessageBox(GetDesktopWindow(), "알수없는 타입", "데이터베이스 오류", MB_ICONERROR);
			}
		}
	}

	//MakeFieldNameMap();

	return TRUE;
}

/*
void CMkRecordset::MakeFieldNameMap()
{
	//for(int c = 0; c < m_nFieldCount; c++) 
	//	m_mapFieldName[m_pField[c].szFieldName] = c;

	FreeFieldNameBuffer();

	m_pszFieldName = new CHAR[m_nFieldCount * 100];

	for(int c = 0; c < m_nFieldCount; c++)
		strncpy(m_pszFieldName, m_pField[c].szFieldName, 99);
}
*/

void CMkRecordset::GetFieldValue(int nIndex, BYTE &cValue)
{
	cValue = (BYTE)*((int*)INDEX(nIndex, m_nCurRecord));
}

void CMkRecordset::GetFieldValue(int nIndex, bool &bValue)
{
	bValue = *((int*)INDEX(nIndex, m_nCurRecord)) ? TRUE : FALSE;
}

void CMkRecordset::GetFieldValue(int nIndex, unsigned short int &usValue)
{
	usValue = (unsigned short int)*((int*)INDEX(nIndex, m_nCurRecord));
}

void CMkRecordset::GetFieldValue(int nIndex, int &nValue)
{
	nValue = *((int*)INDEX(nIndex, m_nCurRecord));
}

void CMkRecordset::GetFieldValue(int nIndex, long &lValue)
{
	lValue = *((long*)INDEX(nIndex, m_nCurRecord));
}

void CMkRecordset::GetFieldValue(int nIndex, unsigned long &lValue)
{
	lValue = *((unsigned long*)INDEX(nIndex, m_nCurRecord));
}

void CMkRecordset::GetFieldValue(int nIndex, unsigned int &lValue)
{
	lValue = *((unsigned int*)INDEX(nIndex, m_nCurRecord));
}

void CMkRecordset::GetFieldValue(int nIndex, float &fValue)
{
	fValue = (float)*((double*)INDEX(nIndex, m_nCurRecord));
}

void CMkRecordset::GetFieldValue(int nIndex, double &dValue)
{
	dValue = *((double*)INDEX(nIndex, m_nCurRecord));
}

void CMkRecordset::GetFieldValue(int nIndex, COleDateTime &dtValue)
{
	if(INDEX(nIndex, m_nCurRecord) != NULL) {
		DBTIMESTAMP *pts = (DBTIMESTAMP*)INDEX(nIndex, m_nCurRecord);
		dtValue.SetDateTime(pts->year, pts->month, pts->day, pts->hour, pts->minute, pts->second);
	}
	else
		dtValue.SetStatus(COleDateTime::null);
}

void CMkRecordset::GetFieldValue(int nIndex, CString &strValue)
{
	if(INDEX(nIndex, m_nCurRecord) != NULL) {
		if(m_pField[nIndex].nType == typeWStr)
			strValue = (BSTR)INDEX(nIndex, m_nCurRecord);
		else
			strValue = (char*)INDEX(nIndex, m_nCurRecord);
	}
	else
		strValue.Empty();
}

void CMkRecordset::GetFieldValue(int nIndex, char *szValue)
{
	if(INDEX(nIndex, m_nCurRecord) != NULL) {
		if(m_pField[nIndex].nType == typeWStr)
			ASSERT(0);
		else
			strcpy(szValue, (char*)INDEX(nIndex, m_nCurRecord));
	}
	else
		szValue[0] = 0;
}

void CMkRecordset::GetFieldValue(int nIndex, WCHAR *wszValue)
{
	if(INDEX(nIndex, m_nCurRecord) != NULL) {
		if(m_pField[nIndex].nType == typeWStr)
			wcscpy(wszValue, (BSTR)INDEX(nIndex, m_nCurRecord));
		else
			ASSERT(0);
	}
	else
		wszValue[0] = 0;
}


void CMkRecordset::GetFieldValue(int nIndex, void **pValue, int &nSize)
{
	nSize = m_pField[nIndex].lSize;

	if(nSize == 0)
	{
		pValue = NULL;
	}
	else
	{
		*pValue = new CHAR[nSize];
		memcpy(*pValue, (void*)INDEX(nIndex, m_nCurRecord), nSize);
	}
}

BOOL CMkRecordset::TranslateFieldName(LPCTSTR lpFieldName, int &nCol)
{
	if(m_nPreTranslateField >= m_nFieldCount - 1)
		m_nPreTranslateField = 0;

	int k = 0;
	for(k = m_nPreTranslateField; k < m_nFieldCount; k++)
	{
		if(0 == strcmp(m_pField[k].szFieldName, lpFieldName))
		{
			m_nPreTranslateField = k + 1;
			nCol = k;
			return TRUE;
		}
	}

	for(k = 0; k < m_nPreTranslateField; k++)
	{
		if(0 == strcmp(m_pField[k].szFieldName, lpFieldName))
		{
			m_nPreTranslateField = k + 1;
			nCol = k;
			return TRUE;
		}
	}

	return FALSE;	
/*
	STRING_MAP::iterator it = m_mapFieldName.find(lpFieldName);
	if(it == m_mapFieldName.end())
		return FALSE;

	nCol = it->second;
	return TRUE;
*/
}

void CMkRecordset::DisplayFieldNameError(LPCTSTR lpFieldName)
{
	if(!m_bDisplayError)
	{
		m_bDisplayError = TRUE;
		CString strMsg;
		strMsg.Format("[GetFieldValue] '%s' 필드가 존재하지 않습니다.", lpFieldName);
		MessageBox(GetActiveWindow(), strMsg, "Recordset Error", MB_ICONERROR);
	}
}
/*
template<typename C> void CMkRecordset::GetFieldValue(LPCTSTR lpFieldName, C &cvalue)
{
	int nIndex;
	if(!TranslateFieldName(lpFieldName, nIndex))
		DisplayFieldNameError(lpFieldName);
	else
		GetFieldValue(nIndex, cvalue);
}
*/


void CMkRecordset::GetFieldValue(LPCTSTR lpFieldName, void **pValue, int &nSize)
{
	int nIndex;
	if(!TranslateFieldName(lpFieldName, nIndex))
		DisplayFieldNameError(lpFieldName);
	else
		GetFieldValue(nIndex, pValue, nSize);
}


void CMkRecordset::GetFieldValueS(int nIndex, void **pValue, int &nSize)
{
	if(IsSecondRecordset())
		m_pRs2->GetFieldValue(nIndex, pValue, nSize);
	else
		GetFieldValue(nIndex, pValue, nSize);
}


void CMkRecordset::GetFieldValueS(LPCTSTR lpFieldName, void **pValue, int &nSize)
{
	if(IsSecondRecordset())
		m_pRs2->GetFieldValue(lpFieldName, pValue, nSize);
	else
		GetFieldValue(lpFieldName, pValue, nSize);
}


//비표준 확장
int CMkRecordset::GetFieldInt(int nIndex)
{
	return *((short*)INDEX(nIndex, m_nCurRecord));
}

int CMkRecordset::GetFieldInt(LPCTSTR lpFieldName)
{
	int nIndex;
	if(!TranslateFieldName(lpFieldName, nIndex))
		return 0;
	else
		return GetFieldInt(nIndex);
}

long CMkRecordset::GetFieldLong(int nIndex)
{
	return *((long*)INDEX(nIndex, m_nCurRecord));
}

long CMkRecordset::GetFieldLong(LPCTSTR lpFieldName)
{
	int nIndex;
	if(!TranslateFieldName(lpFieldName, nIndex))
		return 0;
	else
		return GetFieldLong(nIndex);
}

COleDateTime CMkRecordset::GetFieldDate(int nIndex) 
{
	COleDateTime dtValue;

	if(INDEX(nIndex, m_nCurRecord) != NULL) {
		DBTIMESTAMP *pts = (DBTIMESTAMP*)INDEX(nIndex, m_nCurRecord);
		dtValue.SetDateTime(pts->year, pts->month, pts->day, pts->hour, pts->minute, pts->second);
	}
	else {
		dtValue.SetStatus(COleDateTime::null);
	}
	return dtValue;
}

COleDateTime CMkRecordset::GetFieldDate(LPCTSTR lpFieldName)
{
	int nIndex;
	if(!TranslateFieldName(lpFieldName, nIndex))
	{
		COleDateTime dt;
		dt.SetStatus(COleDateTime::null);
		return dt;
	}
	else
	{
		return GetFieldDate(nIndex);
	}
}

CString CMkRecordset::GetFieldString(int nIndex) 
{
	CString strValue;

	if(INDEX(nIndex, m_nCurRecord) != NULL) {
		if(m_pField[nIndex].nType == typeWStr)
			strValue = (BSTR)INDEX(nIndex, m_nCurRecord);
		else
            strValue = (char*)INDEX(nIndex, m_nCurRecord);
	}
	else
		strValue.Empty();

	return strValue;
}

CString CMkRecordset::GetFieldString(LPCTSTR lpFieldName)
{
	int nIndex;
	if(!TranslateFieldName(lpFieldName, nIndex))
		return CString("");
	else
		return GetFieldString(nIndex);
}

CString CMkRecordset::GetFieldName(int nIndex)
{
	return m_pField[nIndex].szFieldName;
/*
	STRING_MAP::iterator it;
	for(it = m_mapFieldName.begin(); it != m_mapFieldName.end(); it++)
	{
		if(nIndex == it->second)
			return it->first.c_str();
	}
	return "";
*/
}

void CMkRecordset::SetFieldName(int nIndex, CString strFieldName)
{
	if(nIndex < m_nFieldCount)
		strncpy(m_pField[nIndex].szFieldName, (LPSTR)(LPCTSTR)strFieldName, 29);
}

int CMkRecordset::GetFieldType(int nIndex) 
{
	return m_pField[nIndex].nType;
}

CString CMkRecordset::GetFieldValueToString(int nIndex)
{
	CString strText;

	switch(m_pField[nIndex].nType)
	{
		case typeInt:
			strText.Format("%d", *((short*)INDEX(nIndex, m_nCurRecord)));
			break;

		case typeLong:
			strText.Format("%d", *((long*)INDEX(nIndex, m_nCurRecord)));
			break;

		case typeBool:
			strText.Format("%d", *((long*)INDEX(nIndex, m_nCurRecord)) ? 1 : 0);
			break;

		case typeDate:
			{
				COleDateTime dtValue;

				if(INDEX(nIndex, m_nCurRecord) != NULL) {
					DBTIMESTAMP *pts = (DBTIMESTAMP*)INDEX(nIndex, m_nCurRecord);
					dtValue.SetDateTime(pts->year, pts->month, pts->day, pts->hour, pts->minute, pts->second);
				}
				else {
					dtValue.SetStatus(COleDateTime::null);
				}

				strText = dtValue.Format("%Y-%m-%d %H:%M");
			}
			break;

		case typeString:
		case typeWStr:
			{
				CString strValue;

				if(INDEX(nIndex, m_nCurRecord) != NULL) {
					if(m_pField[nIndex].nType == typeWStr)
						strValue = (BSTR)INDEX(nIndex, m_nCurRecord);
					else
						strValue = (char*)INDEX(nIndex, m_nCurRecord);
				}
				else
					strValue.Empty();

				strText = strValue;
			}
			break;
	}

	return strText;
}

void CMkRecordset::SetSort(int nColumn, BOOL bAscending)
{
	m_nSortedColumn = nColumn;
	m_bSortAscending = bAscending;

	switch(m_pField[nColumn].nType) 
	{
	case typeInt:
	case typeLong:
		QsortInt(m_pIndex, m_nRecordCount, m_nFieldCount * sizeof(DWORD));
		break;

	case typeDate:
		QsortDate(m_pIndex, m_nRecordCount, m_nFieldCount * sizeof(DWORD));
		break;

	case typeString:
		QsortString(m_pIndex, m_nRecordCount, m_nFieldCount * sizeof(DWORD));
		break;

	case typeWStr:
		QsortStringW(m_pIndex, m_nRecordCount, m_nFieldCount * sizeof(DWORD));
		break;
	}
}

void CMkRecordset::SetSort(LPCTSTR lpFieldName, BOOL bAscending)
{
	int nIndex;
	if(TranslateFieldName(lpFieldName, nIndex))
		SetSort(nIndex, bAscending);
}


int CMkRecordset::CompareInt(const void* pData1, const void* pData2)
{
	int &nValue1 = *((int*)*((DWORD*)pData1 + m_nSortedColumn));
	int &nValue2 = *((int*)*((DWORD*)pData2 + m_nSortedColumn));

	if(m_bSortAscending)
	{
		if(nValue1 > nValue2)
			return 1;
		else if(nValue1 < nValue2)
			return -1;
	}
	else {
		if(nValue1 < nValue2)
			return 1;
		else if(nValue1 > nValue2)
			return -1;
	}
	return 0;
}


int CMkRecordset::CompareString(const void* pData1, const void* pData2)
{
	char *szValue1 = (char*)*((DWORD*)pData1 + m_nSortedColumn);
	char *szValue2 = (char*)*((DWORD*)pData2 + m_nSortedColumn);

	if(szValue1 == NULL)
		return -1;
	else if(szValue2 == NULL)
		return 1;

	return m_bSortAscending ? strcmp(szValue1, szValue2) : strcmp(szValue2, szValue1);
}

int CMkRecordset::CompareStringW(const void* pData1, const void* pData2)
{
	WCHAR *szValue1 = (WCHAR*)*((DWORD*)pData1 + m_nSortedColumn);
	WCHAR *szValue2 = (WCHAR*)*((DWORD*)pData2 + m_nSortedColumn);

	if(szValue1 == NULL)
		return -1;
	else if(szValue2 == NULL)
		return 1;

	return m_bSortAscending ? wcscmp(szValue1, szValue2) : wcscmp(szValue2, szValue1);
}



int CMkRecordset::CompareDate(const void* pData1, const void* pData2)
{
	DBTIMESTAMP *pts1 = (DBTIMESTAMP*)*((DWORD*)pData1 + m_nSortedColumn);
	DBTIMESTAMP *pts2 = (DBTIMESTAMP*)*((DWORD*)pData2 + m_nSortedColumn);

	if(pts1 == NULL)
		return m_bSortAscending ? -1 : 1;
	else if(pts2 == NULL)
		return m_bSortAscending ? 1 : -1;

	COleDateTime dt1(pts1->year, pts1->month, pts1->day, pts1->hour, pts1->minute, pts1->second);
	COleDateTime dt2(pts2->year, pts2->month, pts2->day, pts2->hour, pts2->minute, pts2->second);

	if(m_bSortAscending)
	{
		if(dt1 > dt2)
			return 1;
		else if(dt1 < dt2)
			return -1;
	}
	else
	{
		if(dt1 < dt2)
			return 1;
		else if(dt1 > dt2)
			return -1;
	}
	return 0;
}

void CMkRecordset::QsortInt(void *base, unsigned num, unsigned width)
{
    char *lo, *hi;
    char *mid;
    char *loguy, *higuy;
    unsigned size;
    char *lostk[30], *histk[30];
    int stkptr;

    if (num < 2 || width == 0)
    {
        return;
    }

    stkptr = 0;

    lo = (char*)base;
    hi = (char *)base + width * (num-1);

recurse:

    size = (hi - lo) / width + 1;

    if (size > CUTOFF)
    {
        mid = lo + (size / 2) * width;

		{
			int w2 = width;

            if (w2 < 4)
            {
                do
			    {
                    char    tmp;

                    w2 --;
				    tmp = mid[w2];
				    mid[w2] = lo[w2];
				    lo[w2] = tmp;
			    } while (w2 > 0);
            }
            else
            {
				int tmp;
                
                tmp = *(int*)(&mid[w2-4]);
				*(int*)(&mid[w2-4]) = *(int*)(&lo[w2-4]);
				*(int*)(&lo[w2-4]) = tmp;
                w2--;
                w2 &= -4;
			    while (w2 >= 4)
			    {
				    w2 -= 4;
				    tmp = *(int*)(&mid[w2]);
				    *(int*)(&mid[w2]) = *(int*)(&lo[w2]);
				    *(int*)(&lo[w2]) = tmp;
			    }
            }
		}

        loguy = lo;
        higuy = hi + width;

        for (;;)
		{
            do  {
                loguy += width;
            } while (loguy <= hi && CompareInt(loguy, lo) < 0);  // <=

            do  {
                higuy -= width;
            } while (higuy > lo && CompareInt(higuy, lo) > 0);   // >=

            if (higuy < loguy)
			{
                break;
			}

			{
				 int w2 = width;

                if (w2 < 4)
                {
                    do
				    {
                        char    tmp;

                        w2 --;
					    tmp = loguy[w2];
					    loguy[w2] = higuy[w2];
					    higuy[w2] = tmp;
				    } while (w2 > 0);
                }
                else
                {
					int tmp;
                    
                    tmp = *(int*)(&loguy[w2-4]);
					*(int*)(&loguy[w2-4]) = *(int*)(&higuy[w2-4]);
					*(int*)(&higuy[w2-4]) = tmp;
                    w2--;
                    w2 &= -4;
				    while (w2 >= 4)
				    {
					    w2 -= 4;
					    tmp = *(int*)(&loguy[w2]);
					    *(int*)(&loguy[w2]) = *(int*)(&higuy[w2]);
					    *(int*)(&higuy[w2]) = tmp;
				    }
                }
			}
        }

		{
			int w2 = width;

            if (w2 < 4)
            {
                do
			    {
                    char    tmp;
                    w2 --;
				    tmp = lo[w2];
				    lo[w2] = higuy[w2];
				    higuy[w2] = tmp;
			    } while (w2 > 0);
            }
            else
            {
                int tmp;

				tmp = *(int*)(&lo[w2-4]);
				*(int*)(&lo[w2-4]) = *(int*)(&higuy[w2-4]);
				*(int*)(&higuy[w2-4]) = tmp;
                w2--;
                w2 &= -4;
			    while (w2 >= 4)
			    {
				    w2 -= 4;
				    int tmp = *(int*)(&lo[w2]);
				    *(int*)(&lo[w2]) = *(int*)(&higuy[w2]);
				    *(int*)(&higuy[w2]) = tmp;
			    }
            }
		}

        if ( higuy - 1 - lo >= hi - loguy )
		{
            if (lo + width < higuy)
			{
                lostk[stkptr] = lo;
                histk[stkptr] = higuy - width;
                ++stkptr;
            }

            if (loguy < hi)
			{
                lo = loguy;
                goto recurse;
            }
        }
        else
		{
            if (loguy < hi)
			{
                lostk[stkptr] = loguy;
                histk[stkptr] = hi;
                ++stkptr;
            }

            if (lo + width < higuy)
			{
                hi = higuy - width;
                goto recurse;
            }
        }
    }
    else
    {
		char *p, *max;

		while (hi > lo)
        {
			max = lo;
			for (p = lo+width; p <= hi; p += width)
            {
				if (CompareInt(p, max) > 0)
                {
					max = p;
				}
			}

			if ( max != hi )
			{
				 int w2 = width;

				if (w2 < 4)
				{
					do {
                        char tmp;

                        w2 --;
						tmp = max[w2];
						max[w2] = hi[w2];
						hi[w2] = tmp;
					} while (w2 > 0);
				}
				else
				{
					int tmp;
                    
					tmp = *(int*)(&max[w2-4]);
					*(int*)(&max[w2-4]) = *(int*)(&hi[w2-4]);
					*(int*)(&hi[w2-4]) = tmp;
                    w2--;
                    w2 &= -4;
				    while (w2 >= 4)
				    {
					    w2 -= 4;
					    tmp = *(int*)(&max[w2]);
					    *(int*)(&max[w2]) = *(int*)(&hi[w2]);
					    *(int*)(&hi[w2]) = tmp;
				    }
				}
			}

			hi -= width;
		}
    }


    --stkptr;
    if (stkptr >= 0)
	{
        lo = lostk[stkptr];
        hi = histk[stkptr];
        goto recurse;
    }

	return;
}


void CMkRecordset::QsortString(void *base, unsigned num, unsigned width)
{
    char *lo, *hi;
    char *mid;
    char *loguy, *higuy;
    unsigned size;
    char *lostk[30], *histk[30];
    int stkptr;

    if (num < 2 || width == 0)
    {
        return;
    }

    stkptr = 0;

    lo = (char*)base;
    hi = (char *)base + width * (num-1);

recurse:

    size = (hi - lo) / width + 1;

    if (size > CUTOFF)
    {
        mid = lo + (size / 2) * width;

		{
			 int w2 = width;

            if (w2 < 4)
            {
                do
			    {
                    char    tmp;

                    w2 --;
				    tmp = mid[w2];
				    mid[w2] = lo[w2];
				    lo[w2] = tmp;
			    } while (w2 > 0);
            }
            else
            {
				int tmp;
                
                tmp = *(int*)(&mid[w2-4]);
				*(int*)(&mid[w2-4]) = *(int*)(&lo[w2-4]);
				*(int*)(&lo[w2-4]) = tmp;
                w2--;
                w2 &= -4;
			    while (w2 >= 4)
			    {
				    w2 -= 4;
				    tmp = *(int*)(&mid[w2]);
				    *(int*)(&mid[w2]) = *(int*)(&lo[w2]);
				    *(int*)(&lo[w2]) = tmp;
			    }
            }
		}

        loguy = lo;
        higuy = hi + width;

        for (;;)
		{
            do  {
                loguy += width;
            } while (loguy <= hi && CompareString(loguy, lo) < 0);  // <=

            do  {
                higuy -= width;
            } while (higuy > lo && CompareString(higuy, lo) > 0);   // >=

            if (higuy < loguy)
			{
                break;
			}

			{
				 int w2 = width;

                if (w2 < 4)
                {
                    do
				    {
                        char    tmp;

                        w2 --;
					    tmp = loguy[w2];
					    loguy[w2] = higuy[w2];
					    higuy[w2] = tmp;
				    } while (w2 > 0);
                }
                else
                {
					int tmp;
                    
                    tmp = *(int*)(&loguy[w2-4]);
					*(int*)(&loguy[w2-4]) = *(int*)(&higuy[w2-4]);
					*(int*)(&higuy[w2-4]) = tmp;
                    w2--;
                    w2 &= -4;
				    while (w2 >= 4)
				    {
					    w2 -= 4;
					    tmp = *(int*)(&loguy[w2]);
					    *(int*)(&loguy[w2]) = *(int*)(&higuy[w2]);
					    *(int*)(&higuy[w2]) = tmp;
				    }
                }
			}
        }

		{
			 int w2 = width;

            if (w2 < 4)
            {
                do
			    {
                    char    tmp;
                    w2 --;
				    tmp = lo[w2];
				    lo[w2] = higuy[w2];
				    higuy[w2] = tmp;
			    } while (w2 > 0);
            }
            else
            {
                int tmp;

				tmp = *(int*)(&lo[w2-4]);
				*(int*)(&lo[w2-4]) = *(int*)(&higuy[w2-4]);
				*(int*)(&higuy[w2-4]) = tmp;
                w2--;
                w2 &= -4;
			    while (w2 >= 4)
			    {
				    w2 -= 4;
				    int tmp = *(int*)(&lo[w2]);
				    *(int*)(&lo[w2]) = *(int*)(&higuy[w2]);
				    *(int*)(&higuy[w2]) = tmp;
			    }
            }
		}

        if ( higuy - 1 - lo >= hi - loguy )
		{
            if (lo + width < higuy)
			{
                lostk[stkptr] = lo;
                histk[stkptr] = higuy - width;
                ++stkptr;
            }

            if (loguy < hi)
			{
                lo = loguy;
                goto recurse;
            }
        }
        else
		{
            if (loguy < hi)
			{
                lostk[stkptr] = loguy;
                histk[stkptr] = hi;
                ++stkptr;
            }

            if (lo + width < higuy)
			{
                hi = higuy - width;
                goto recurse;
            }
        }
    }
    else
    {
		char *p, *max;

		while (hi > lo)
        {
			max = lo;
			for (p = lo+width; p <= hi; p += width)
            {
				if (CompareString(p, max) > 0)
                {
					max = p;
				}
			}

			if ( max != hi )
			{
				 int w2 = width;

				if (w2 < 4)
				{
					do {
                        char tmp;

                        w2 --;
						tmp = max[w2];
						max[w2] = hi[w2];
						hi[w2] = tmp;
					} while (w2 > 0);
				}
				else
				{
					int tmp;
                    
					tmp = *(int*)(&max[w2-4]);
					*(int*)(&max[w2-4]) = *(int*)(&hi[w2-4]);
					*(int*)(&hi[w2-4]) = tmp;
                    w2--;
                    w2 &= -4;
				    while (w2 >= 4)
				    {
					    w2 -= 4;
					    tmp = *(int*)(&max[w2]);
					    *(int*)(&max[w2]) = *(int*)(&hi[w2]);
					    *(int*)(&hi[w2]) = tmp;
				    }
				}
			}

			hi -= width;
		}
    }


    --stkptr;
    if (stkptr >= 0)
	{
        lo = lostk[stkptr];
        hi = histk[stkptr];
        goto recurse;
    }

	return;
}


void CMkRecordset::QsortStringW(void *base, unsigned num, unsigned width)
{
    char *lo, *hi;
    char *mid;
    char *loguy, *higuy;
    unsigned size;
    char *lostk[30], *histk[30];
    int stkptr;

    if (num < 2 || width == 0)
    {
        return;
    }

    stkptr = 0;

    lo = (char*)base;
    hi = (char *)base + width * (num-1);

recurse:

    size = (hi - lo) / width + 1;

    if (size > CUTOFF)
    {
        mid = lo + (size / 2) * width;

		{
			 int w2 = width;

            if (w2 < 4)
            {
                do
			    {
                    char    tmp;

                    w2 --;
				    tmp = mid[w2];
				    mid[w2] = lo[w2];
				    lo[w2] = tmp;
			    } while (w2 > 0);
            }
            else
            {
				int tmp;
                
                tmp = *(int*)(&mid[w2-4]);
				*(int*)(&mid[w2-4]) = *(int*)(&lo[w2-4]);
				*(int*)(&lo[w2-4]) = tmp;
                w2--;
                w2 &= -4;
			    while (w2 >= 4)
			    {
				    w2 -= 4;
				    tmp = *(int*)(&mid[w2]);
				    *(int*)(&mid[w2]) = *(int*)(&lo[w2]);
				    *(int*)(&lo[w2]) = tmp;
			    }
            }
		}

        loguy = lo;
        higuy = hi + width;

        for (;;)
		{
            do  {
                loguy += width;
            } while (loguy <= hi && CompareStringW(loguy, lo) < 0);  // <=

            do  {
                higuy -= width;
            } while (higuy > lo && CompareStringW(higuy, lo) > 0);   // >=

            if (higuy < loguy)
			{
                break;
			}

			{
				 int w2 = width;

                if (w2 < 4)
                {
                    do
				    {
                        char    tmp;

                        w2 --;
					    tmp = loguy[w2];
					    loguy[w2] = higuy[w2];
					    higuy[w2] = tmp;
				    } while (w2 > 0);
                }
                else
                {
					int tmp;
                    
                    tmp = *(int*)(&loguy[w2-4]);
					*(int*)(&loguy[w2-4]) = *(int*)(&higuy[w2-4]);
					*(int*)(&higuy[w2-4]) = tmp;
                    w2--;
                    w2 &= -4;
				    while (w2 >= 4)
				    {
					    w2 -= 4;
					    tmp = *(int*)(&loguy[w2]);
					    *(int*)(&loguy[w2]) = *(int*)(&higuy[w2]);
					    *(int*)(&higuy[w2]) = tmp;
				    }
                }
			}
        }

		{
			 int w2 = width;

            if (w2 < 4)
            {
                do
			    {
                    char    tmp;
                    w2 --;
				    tmp = lo[w2];
				    lo[w2] = higuy[w2];
				    higuy[w2] = tmp;
			    } while (w2 > 0);
            }
            else
            {
                int tmp;

				tmp = *(int*)(&lo[w2-4]);
				*(int*)(&lo[w2-4]) = *(int*)(&higuy[w2-4]);
				*(int*)(&higuy[w2-4]) = tmp;
                w2--;
                w2 &= -4;
			    while (w2 >= 4)
			    {
				    w2 -= 4;
				    int tmp = *(int*)(&lo[w2]);
				    *(int*)(&lo[w2]) = *(int*)(&higuy[w2]);
				    *(int*)(&higuy[w2]) = tmp;
			    }
            }
		}

        if ( higuy - 1 - lo >= hi - loguy )
		{
            if (lo + width < higuy)
			{
                lostk[stkptr] = lo;
                histk[stkptr] = higuy - width;
                ++stkptr;
            }

            if (loguy < hi)
			{
                lo = loguy;
                goto recurse;
            }
        }
        else
		{
            if (loguy < hi)
			{
                lostk[stkptr] = loguy;
                histk[stkptr] = hi;
                ++stkptr;
            }

            if (lo + width < higuy)
			{
                hi = higuy - width;
                goto recurse;
            }
        }
    }
    else
    {
		char *p, *max;

		while (hi > lo)
        {
			max = lo;
			for (p = lo+width; p <= hi; p += width)
            {
				if (CompareStringW(p, max) > 0)
                {
					max = p;
				}
			}

			if ( max != hi )
			{
				 int w2 = width;

				if (w2 < 4)
				{
					do {
                        char tmp;

                        w2 --;
						tmp = max[w2];
						max[w2] = hi[w2];
						hi[w2] = tmp;
					} while (w2 > 0);
				}
				else
				{
					int tmp;
                    
					tmp = *(int*)(&max[w2-4]);
					*(int*)(&max[w2-4]) = *(int*)(&hi[w2-4]);
					*(int*)(&hi[w2-4]) = tmp;
                    w2--;
                    w2 &= -4;
				    while (w2 >= 4)
				    {
					    w2 -= 4;
					    tmp = *(int*)(&max[w2]);
					    *(int*)(&max[w2]) = *(int*)(&hi[w2]);
					    *(int*)(&hi[w2]) = tmp;
				    }
				}
			}

			hi -= width;
		}
    }


    --stkptr;
    if (stkptr >= 0)
	{
        lo = lostk[stkptr];
        hi = histk[stkptr];
        goto recurse;
    }

	return;
}



void CMkRecordset::QsortDate(void *base, unsigned num, unsigned width)
{
    char *lo, *hi;
    char *mid;
    char *loguy, *higuy;
    unsigned size;
    char *lostk[30], *histk[30];
    int stkptr;

    if (num < 2 || width == 0)
    {
        return;
    }

    stkptr = 0;

    lo = (char*)base;
    hi = (char *)base + width * (num-1);

recurse:

    size = (hi - lo) / width + 1;

    if (size > CUTOFF)
    {
        mid = lo + (size / 2) * width;

		{
			 int w2 = width;

            if (w2 < 4)
            {
                do
			    {
                    char    tmp;

                    w2 --;
				    tmp = mid[w2];
				    mid[w2] = lo[w2];
				    lo[w2] = tmp;
			    } while (w2 > 0);
            }
            else
            {
				int tmp;
                
                tmp = *(int*)(&mid[w2-4]);
				*(int*)(&mid[w2-4]) = *(int*)(&lo[w2-4]);
				*(int*)(&lo[w2-4]) = tmp;
                w2--;
                w2 &= -4;
			    while (w2 >= 4)
			    {
				    w2 -= 4;
				    tmp = *(int*)(&mid[w2]);
				    *(int*)(&mid[w2]) = *(int*)(&lo[w2]);
				    *(int*)(&lo[w2]) = tmp;
			    }
            }
		}

        loguy = lo;
        higuy = hi + width;

        for (;;)
		{
            do  {
                loguy += width;
            } while (loguy <= hi && CompareDate(loguy, lo) < 0);  // <=

            do  {
                higuy -= width;
            } while (higuy > lo && CompareDate(higuy, lo) > 0);   // >=

            if (higuy < loguy)
			{
                break;
			}

			{
				 int w2 = width;

                if (w2 < 4)
                {
                    do
				    {
                        char    tmp;

                        w2 --;
					    tmp = loguy[w2];
					    loguy[w2] = higuy[w2];
					    higuy[w2] = tmp;
				    } while (w2 > 0);
                }
                else
                {
					int tmp;
                    
                    tmp = *(int*)(&loguy[w2-4]);
					*(int*)(&loguy[w2-4]) = *(int*)(&higuy[w2-4]);
					*(int*)(&higuy[w2-4]) = tmp;
                    w2--;
                    w2 &= -4;
				    while (w2 >= 4)
				    {
					    w2 -= 4;
					    tmp = *(int*)(&loguy[w2]);
					    *(int*)(&loguy[w2]) = *(int*)(&higuy[w2]);
					    *(int*)(&higuy[w2]) = tmp;
				    }
                }
			}
        }

		{
			 int w2 = width;

            if (w2 < 4)
            {
                do
			    {
                    char    tmp;
                    w2 --;
				    tmp = lo[w2];
				    lo[w2] = higuy[w2];
				    higuy[w2] = tmp;
			    } while (w2 > 0);
            }
            else
            {
                int tmp;

				tmp = *(int*)(&lo[w2-4]);
				*(int*)(&lo[w2-4]) = *(int*)(&higuy[w2-4]);
				*(int*)(&higuy[w2-4]) = tmp;
                w2--;
                w2 &= -4;
			    while (w2 >= 4)
			    {
				    w2 -= 4;
				    int tmp = *(int*)(&lo[w2]);
				    *(int*)(&lo[w2]) = *(int*)(&higuy[w2]);
				    *(int*)(&higuy[w2]) = tmp;
			    }
            }
		}

        if ( higuy - 1 - lo >= hi - loguy )
		{
            if (lo + width < higuy)
			{
                lostk[stkptr] = lo;
                histk[stkptr] = higuy - width;
                ++stkptr;
            }

            if (loguy < hi)
			{
                lo = loguy;
                goto recurse;
            }
        }
        else
		{
            if (loguy < hi)
			{
                lostk[stkptr] = loguy;
                histk[stkptr] = hi;
                ++stkptr;
            }

            if (lo + width < higuy)
			{
                hi = higuy - width;
                goto recurse;
            }
        }
    }
    else
    {
		char *p, *max;

		while (hi > lo)
        {
			max = lo;
			for (p = lo+width; p <= hi; p += width)
            {
				if (CompareDate(p, max) > 0)
                {
					max = p;
				}
			}

			if ( max != hi )
			{
				 int w2 = width;

				if (w2 < 4)
				{
					do {
                        char tmp;

                        w2 --;
						tmp = max[w2];
						max[w2] = hi[w2];
						hi[w2] = tmp;
					} while (w2 > 0);
				}
				else
				{
					int tmp;
                    
					tmp = *(int*)(&max[w2-4]);
					*(int*)(&max[w2-4]) = *(int*)(&hi[w2-4]);
					*(int*)(&hi[w2-4]) = tmp;
                    w2--;
                    w2 &= -4;
				    while (w2 >= 4)
				    {
					    w2 -= 4;
					    tmp = *(int*)(&max[w2]);
					    *(int*)(&max[w2]) = *(int*)(&hi[w2]);
					    *(int*)(&hi[w2]) = tmp;
				    }
				}
			}

			hi -= width;
		}
    }


    --stkptr;
    if (stkptr >= 0)
	{
        lo = lostk[stkptr];
        hi = histk[stkptr];
        goto recurse;
    }

	return;
}

BYTE data_key[8] = {45,79,92,42,02,57,71,06};


void CMkRecordset::MakePlainText(void* pChunk, int nSize)
{
	static BOOL bInitDes = FALSE;

	if(!bInitDes)
	{
		des_init((MBYTE*)data_key, 0, false);
		bInitDes = TRUE;
	}

	for(int i = 0;i < nSize - 8; i+=8)
		des_ecb(FALSE, (MBYTE*)pChunk, i, (MBYTE*)pChunk, i);

	g_bana_log->Print("Plain Data: %dkb\n", nSize / 1024);	
}
