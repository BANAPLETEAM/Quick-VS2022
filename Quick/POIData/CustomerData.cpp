#include "StdAfx.h"
#include "CustomerData.h"
#include "INI.h"



#define ENC_OFFSET_VALUE		99
#define CUSTOMER_FILE_NAME				"cn_xxx.cdt"
#define CUSTOMER_PHONE_FILE_NAME		"cp_xxx.cdt"
#define CUSTOMER_PHONE_NAME_FILE_NAME	"cpn_xxx.cdt"
#define CUSTOMER_PHONE_FOUR_FILE_NAME	"cp4_xxx.cdt"
#define CUSTOMER_PHONE_NAME_FOUR_FILE_NAME	"cpn4_xxx.cdt"
#define COMPANY_INDEX_FILE_NAME			"ci_xxx.cdt"
#define CUSTOMER_INI_FILE				"CUS.INI"
#define VALID_UPDATE_COUNT		1000
#define SHOW_COUNT				1000


CBanaLog CCustomerData::m_cuslog;


CCustomerData::CCustomerData()
{
	m_nCompanyCode = 0;
	m_bIsSecondCusData = TRUE;
	m_pcusNew = NULL;
	m_nPrePhonePointSub = 0;
	m_nPrePhoneNamePointSub = 0;
	m_nPreCustomerPointSub = 0;
	m_bCharOrdering = FALSE;
	m_nRefreshMiliSec = 0;
}

CCustomerData::~CCustomerData(void)
{
	P_CUSTOMER_VECTOR::iterator it;
	for(it = m_vecPCustomerEx.begin(); it != m_vecPCustomerEx.end(); it++)
		delete *it;

	m_vecCIdx.clear();
	m_vecCustomer.clear();
	m_vecPhone.clear();
	m_vecPhoneName.clear();
	m_vecPhoneFour.clear();
	m_vecPhoneNameFour.clear();
	m_vecPCustomerEx.clear();
	m_mapCIdx.clear();

	if(!IsSecond() && m_pcusNew)
		delete m_pcusNew;
}

void CCustomerData::SetMainCusData()
{
	m_bIsSecondCusData = FALSE;

	if(!m_pcusNew)
	{
		m_cuslog.Print("\n\n\n------------CCustomerData::Center-------------\n\n\n");

		m_pcusNew = new CCustomerData;
		m_pcusNew->m_pcusNew = this;
		m_cuslog.Print("\n\n\n------------CCustomerData::End1-------------\n\n\n");
	}

	m_cuslog.Print("\n\n\n------------CCustomerData::End2-------------\n\n\n");
}

template<typename MyVector, typename T>
void CCustomerData::EncVector(MyVector &vec, T &t)
{
	char *pChunk = (char*)&vec[0];
	DWORD dwSize = (DWORD)(vec.size() * sizeof(T));
	for(int i = 0; i < dwSize; i++)
		pChunk[i] = (pChunk[i] + ENC_OFFSET_VALUE) ^ (i % ENC_OFFSET_VALUE);
}

template<typename MyVector, typename T>
void CCustomerData::DecVector(MyVector &vec, T &t)
{
	char *pChunk = (char*)&vec[0];
	DWORD dwSize = (DWORD)(vec.size() * sizeof(T));
	for(int i = 0; i < dwSize; i++)
		pChunk[i] = (pChunk[i] ^ (i % ENC_OFFSET_VALUE)) - ENC_OFFSET_VALUE;
}


template<typename MyVector, typename T>
BOOL CCustomerData::SaveVector(MyVector &vec, T &t, CString strFile, BOOL bDefaultPath)
{
	DWORD dwDriveList;
	HANDLE hFile = NULL;
	int nRecordSize = 0;
	CString strFileName = (bDefaultPath ? LF->GetModuleFullPath() : "") + strFile;

	if(vec.size() == 0)
		return FALSE;

	hFile = CreateFile(strFileName, 
		GENERIC_WRITE, FILE_SHARE_WRITE,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(INVALID_HANDLE_VALUE != (HANDLE)hFile) 
	{
#ifndef _DEBUG
		EncVector(vec, t);
#endif
		WriteFile((void*)hFile, 
			reinterpret_cast<const char*>(&vec[0]), 
			(DWORD)(vec.size() * sizeof(T)), 
			&dwDriveList, 
			NULL);
		CloseHandle(hFile);
#ifndef _DEBUG
		DecVector(vec, t);
#endif
		return TRUE;
	}

	return FALSE;
}

//reinterpret_cast<const char*>(&m_vecPartPOI[0]), 
//m_vecPartPOI.size() * sizeof(PART_POI_PAIR) , 


template<typename MyVector, typename T>
BOOL CCustomerData::LoadVector(MyVector &vec, T &t, CString strFile, BOOL bDefaultPath)
{
	HANDLE hFile, hFileMap;
	unsigned char *pBasePointer;
	DWORD dwSize;
	CString strFileName = (bDefaultPath ? LF->GetModuleFullPath() : "") + strFile;

	hFile = CreateFile(strFileName, GENERIC_READ, 
		FILE_SHARE_READ, NULL, 
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(INVALID_HANDLE_VALUE != hFile)
	{
		hFileMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
		dwSize = GetFileSize(hFile, 0);
		pBasePointer = (unsigned char*) MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, dwSize);

		long nVSize = dwSize / sizeof(T);
		if(nVSize > 0)
		{
			vec.assign(nVSize, t);
			memcpy(reinterpret_cast<char*>(&vec[0]), pBasePointer, nVSize * sizeof(T));
#ifndef _DEBUG
			DecVector(vec, t);
#endif
		}

		UnmapViewOfFile((LPVOID)pBasePointer);
		CloseHandle(hFileMap);
		CloseHandle(hFile);
		return nVSize > 0;
	}

	return FALSE;
}

CString CCustomerData::ExtractPhoneNumber(CString strText)
{
#define MIN_PHONE_LENGTH 7
#define MAX_PHONE_LENGTH 11
	char buffer[MAX_PHONE_LENGTH+10];
	int nCount = 0;
	int idx = 0;
	int nLen = strText.GetLength();

	for(int n = 0; n < nLen; n++)
	{
		if(strText.GetAt(n) >= '0' && strText.GetAt(n) <= '9')
		{
			if(idx > MAX_PHONE_LENGTH) 
				idx = 0;
			else
				buffer[idx++] = strText.GetAt(n);
		}
		else if(strText.GetAt(n) == '-')
		{
			continue;
		}
		else
		{
			if(idx >= MIN_PHONE_LENGTH)
			{
				buffer[idx] = 0;
				if(VerifyAvailblePhoneNumber(buffer))
					return buffer;
			}
			idx = 0;
		}
	}

	if(idx >= MIN_PHONE_LENGTH)
	{
		buffer[idx] = 0;
		if(VerifyAvailblePhoneNumber(buffer))
			return buffer;
	}


	return "";
}


BOOL CCustomerData::VerifyAvailblePhoneNumber(char *p)
{
	char szDDD[][20] = {"010", "011", "013", "016", "017", 
		"018", "019", "02", "031", "032", 
		"033", "041", "042", "043", "050", 
		"051", "052", "053", "054", "055",
		"061", "062", "063", "064", "070", 
		"080"};

	if(strlen(p) <= 8)
	{
		if(p[0] == '0')
			return FALSE;
		else
			return TRUE;
	}
	else 
	{
		if(p[0] != '0')		
			return FALSE;

		for(int i = 0; i < 26; i++)
		{
			if(strncmp(szDDD[i], p, strlen(szDDD[i])) == 0)
				return TRUE;
		}
	}
 
	return FALSE;
}

void CCustomerData::GetPhoneDivDDDBody(CString &strPhone, CString &strDDD, CString &strBody)
{
	if(strPhone.Left(2) == "01")
		GetPhoneDivBody(strPhone, 3, strDDD, strBody);
	else if(strPhone.Left(2) == "02")
		GetPhoneDivBody(strPhone, 2, strDDD, strBody);
	else if(strPhone.Left(3) == "050")
		GetPhoneDivBody(strPhone, 4, strDDD, strBody);
	else if(strPhone.Left(1) == "0")
		GetPhoneDivBody(strPhone, 3, strDDD, strBody);
	else
		strBody = strPhone;
}

void CCustomerData::GetPhoneDivBody(CString &strPhone, int nDDDLen, CString &strDDD, CString &strBody)
{
	strDDD = strPhone.Left(nDDDLen);
	strBody = strPhone.Right(strPhone.GetLength() - nDDDLen);
}

 
BOOL CCustomerData::MakeCustomerFromNetwork(long &nCount)
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_customer_list_all10");
	pCmd.AddParameter(m_nCompanyCode);
	pCmd.AddParameter(m_bIntegrated);
	pCmd.AddParameter(IsSecond());
	CMkParameter *parDate = pCmd.AddParameter(typeDate, typeOutput, sizeof(COleDateTime), m_dtLastRefresh);
	CMkParameter *parDateMiliSec = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), m_nRefreshMiliSec);
	CMkParameter *parDeletedCustomer = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parOutSchema = pCmd.AddParameter(typeString, typeOutput, 50, m_strSchemaVersion);

	if(!IsSecond())
		m_vecCustomer.clear();

	m_cuslog.Print("MakeCustomerFromNetwork::IsSecond = %d\n", IsSecond());

	if(pRs.Execute(&pCmd, "고객데이터를 가져오는 중입니다."))
	{
		CUSTOMER_DATA data;
		int nItem = 0;

		data.nIndex = 0;
		data.nState = 0;

		if(m_vecCustomer.size() == 0)
			m_vecCustomer.reserve(pRs.GetRecordCount() + 1);
		else
			data.nIndex = m_vecCustomer.size();

		while(!pRs.IsEOF())
		{
			pRs.GetFieldValue("nCNo", data.nCNo);
			pRs.GetFieldValue("nCompany", data.nCompany);
			pRs.GetFieldValue("sCompany", data.szCompany);
			//pRs.GetFieldValue("sName", data.szName);
			//pRs.GetFieldValue("sPhone", data.szPhone);
			pRs.GetFieldValue("sDong", data.szDong);
			pRs.GetFieldValue("nUseExpiredDay", data.nUseExpiredDay);
			pRs.GetFieldValue("nUseCount", data.nUseCount);
			pRs.GetFieldValue("bCredit", data.bCredit);


			if(IsSecond() && nItem++ < 20)
				g_bana_log->Print("REFRESH CUSTOMER: nCNo = %d, sCompany = %s\n", data.nCNo, data.szCompany);

			if(IsSecond())
				m_cuslog.Print("REFRESH CUSTOMER: nCNo = %d, sCompany = %s\n", data.nCNo, data.szCompany);

			if(IsSecond())
			{
				CIDX_ITER_PAIR itPair;
				if(SearchCustomerCNo(data.nCompany, data.nCNo, itPair))
				{
					CIDX_ITER it;
					for(it = itPair.first; it != itPair.second; it++)
					{
						strcpy(it->pCus->szCompany, data.szCompany);
						strcpy(it->pCus->szDong, data.szDong);
						it->pCus->nUseCount = data.nUseCount;
						it->pCus->nUseExpiredDay = data.nUseExpiredDay;
						it->pCus->bCredit = data.bCredit;

						//g_bana_log->Print("Old New Customer CNo를 0으로 처리함(%d)\n", it->pCus->nCNo);
						//it->pCus->nState = 1;
					}
					pRs.MoveNext();
					continue;
				}
			}
	
			m_vecCustomer.push_back(data);
			data.nIndex++;
			pRs.MoveNext();
		}

		nCount = pRs.GetRecordCount();
		m_cuslog.Print("m_vecCustomer = %d\n", m_vecCustomer.size());

		if(nCount > 0 && !IsSecond())
		{
			CUSTOMER_DATA t2;

			ZeroMemory(&t2, sizeof(CUSTOMER_DATA));
			m_vecCustomer.push_back(t2);

			CUSTOMER_DATA &t = m_vecCustomer.at(m_vecCustomer.size() - 1);
			t.nIndex = (UINT)&m_vecCustomer.at(m_vecCustomer.size() - 1);

			m_cuslog.Print("m_vecCustomer = %d\n", m_vecCustomer.size());

			SaveVector(m_vecCustomer, t, GetCodeFileName(CUSTOMER_FILE_NAME));
			m_vecCustomer.pop_back();

			m_pcusNew->m_dtLastRefresh = parDate->GetDate();
		}


		if(IsSecond() && parDeletedCustomer->GetLong())
			RefreshDeleteCustomer();

		m_strSchemaVersion = parOutSchema->GetString();
		m_dtLastRefresh = parDate->GetDate();
		m_nRefreshMiliSec = parDateMiliSec->GetLong();
		m_cuslog.Print("Refresh Time = %s, %d\n", m_dtLastRefresh.Format("%Y-%m-%d %H:%M:%S"), m_nRefreshMiliSec);

		return TRUE;

	}

	return FALSE;
}

void CCustomerData::RefreshDeleteCustomer()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_deleted_customer_list2");
	pCmd.AddParameter(m_nCompanyCode);
	pCmd.AddParameter(m_bIntegrated);
	pCmd.AddParameter(m_dtLastRefresh);
	pCmd.AddParameter(m_nRefreshMiliSec);
	if(pRs.Execute(&pCmd, "삭제된 고객을 체크중입니다."))
	{
		while(!pRs.IsEOF())
		{
			long nCNo, nCompany;

			pRs.GetFieldValue("nCNo", nCNo);
			pRs.GetFieldValue("nCompany", nCompany);

			CIDX_ITER_PAIR itPair;
			if(SearchCustomerCNo(nCompany, nCNo, itPair))
			{
				CIDX_ITER it;
				for(it = itPair.first; it != itPair.second; it++)
				{
					//g_bana_log->Print("Deleted Customer: %d, %s\n", it->pCus->nCNo, it->pCus->szCompany);
					m_cuslog.Print("Deleted Customer: %d, %s\n", it->pCus->nCNo, it->pCus->szCompany);
					it->pCus->nState = 1;
				}
			}

			//second의 m_pcusNew 는 메인 cus 인스턴스이다.
			if(m_pcusNew->SearchCustomerCNo(nCompany, nCNo, itPair))
			{
				CIDX_ITER it;
				for(it = itPair.first; it != itPair.second; it++)
				{
					//g_bana_log->Print("Deleted Customer(m_pcusNew): %d, %s\n", it->pCus->nCNo, it->pCus->szCompany);
					m_cuslog.Print("Deleted Customer: %d, %s\n", it->pCus->nCNo, it->pCus->szCompany);
					it->pCus->nState = 1;
				}
			}

			pRs.MoveNext();
		}
	}
}

BOOL CCustomerData::MakeCustomerPhoneFromNetwork(COleDateTime dtPreRefresh, long nRefreshMiliSec)
{
	CDisplayBarThreadText dbt(m_pMkDb->m_pDBT, "고객전화번호 데이터를 가져오는 중입니다.", TRUE);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_customer_tel_list_all9", 0, IsSecond());
	pCmd.AddParameter(m_nCompanyCode);
	pCmd.AddParameter(m_bIntegrated);
	pCmd.AddParameter(IsSecond());
	pCmd.AddParameter(dtPreRefresh);	//dtFrom
	pCmd.AddParameter(nRefreshMiliSec);	//dtFrom
	pCmd.AddParameter(m_dtLastRefresh);	//dtTo : 고객데이터를 업데이트한 시점만 고객전번을 가져옴
	pCmd.AddParameter(m_nRefreshMiliSec);	//dtTo : 고객데이터를 업데이트한 시점만 고객전번을 가져옴
	CMkParameter *pparCount = pCmd.AddParameter(0, typeOutput);

	if(!IsSecond())
	{
		m_vecPhone.clear();
		m_vecPhoneName.clear();
	}
 
	if(pRs.Execute(&pCmd, "고객전화번호 데이터를 가져오는 중입니다.") && 
		pRs.GetRecordCount() > 0)
	{
		CUSTOMER_PHONE_NAME phone;
	
		if(m_vecPhone.size() == 0)
		{
			int nRecordCount = pRs.GetRecordCount();
			int nPhoneOnlyCount = pparCount->GetLong();

			m_vecPhone.reserve(nPhoneOnlyCount + 100);
			m_vecPhoneName.reserve(nRecordCount - nPhoneOnlyCount + 100);
		}

		long nCNo;
		char szPhone[20] = "";
		long nItem = 0;

		if(pRs.GetRecordCount() > 0) //문제가 발생시 여기를 삭제함 choi test
			m_vecPhoneName.clear();

		while(!pRs.IsEOF())
		{
			pRs.GetFieldValue("nCNo", nCNo);
			pRs.GetFieldValue("sTel", szPhone);
			pRs.GetFieldValue("nCompany", phone.nCompany);
			pRs.GetFieldValue("sName", phone.szName);
			pRs.GetFieldValue("sDepart", phone.szDepart);
			pRs.GetFieldValue("nType", phone.nMainPhone);
			pRs.GetFieldValue("nExpiredDay", phone.nExpiredDay);
			pRs.GetFieldValue("nID", phone.nID);

			//if(phone.szName[0] == 0x20)
			//	phone.szName[0] = 0;

			//if(phone.szDepart[0] == 0x20)
			//	phone.szDepart[0] = 0;

			StrTrim(phone.szName, " ");
			StrTrim(phone.szDepart, " ");

			if(IsSecond() && nItem++ < 20)
				g_bana_log->Print("REFRESH PHONE: nCNo = %d, sTel = %s, nID = %d\n", nCNo, szPhone, phone.nID);

			int nLen = strlen(szPhone);
			//int nIndex = CNoToVectorID(nCNo);

			if(nCNo >= 0)
			{
				if(nCNo == 11356174)  ///
				{
					int a = 0;
				}

				phone.nIndex = nCNo;
				phone.nType = 0;
				phone.szDDD[0] = 0;
				phone.nPhone = 0;

				if(nLen > 6)
				{
					if(nLen <= 8)
					{
						strcpy(phone.szDDD, m_ci.m_strDDD);
						phone.nPhone = atol(szPhone);
					}
					else
					{
						if(szPhone[0] == '0')
						{
							if(szPhone[1] == '2')
							{
								strncpy(phone.szDDD, szPhone, 2);
								phone.szDDD[2] = 0;
								phone.nPhone = atol(&szPhone[2]);
							}
							else if(strncmp(szPhone, "050", 3) == 0)
							{
								strncpy(phone.szDDD, szPhone, 4);
								phone.szDDD[4] = 0;
								phone.nPhone = atol(&szPhone[4]);
							}
							else
							{
								strncpy(phone.szDDD, szPhone, 3);
								phone.szDDD[3] = 0;
								phone.nPhone = atol(&szPhone[3]);
							}
						}
					}
				}

				if(phone.szName[0] == 0 && phone.szDepart[0] == 0)
					m_vecPhone.push_back(*((CUSTOMER_PHONE*)&phone));
				else
					m_vecPhoneName.push_back(phone);
			}

			pRs.MoveNext();
		}

		CDisplayBarThreadText dbt(m_pMkDb->m_pDBT, "고객전화번호데이터를 고객데이터와 매칭중입니다.", TRUE);

		JoinPhoneWithCustomer(m_vecPhone);
		JoinPhoneWithCustomer(m_vecPhoneName);

		sort(m_vecPhone.begin(), m_vecPhone.end(), PhoneNumberCompare());
		sort(m_vecPhoneName.begin(), m_vecPhoneName.end(), PhoneNumberNameCompare());

		CUSTOMER_PHONE t;
		CUSTOMER_PHONE_NAME tn;
		CUSTOMER_PHONE_FOUR t4;
		CUSTOMER_PHONE_NAME_FOUR tn4;

		MakePhoneFourVector(m_vecPhone, m_vecPhoneFour, t, t4, PhoneNumberFourCompare(), m_nPrePhonePointSub);
		MakePhoneFourVector(m_vecPhoneName, m_vecPhoneNameFour, tn, tn4, PhoneNumberNameFourCompare(), m_nPrePhoneNamePointSub);

		MakeCompanyNameIndex(FALSE);

		if(!IsSecond())
		{
			//g_bana_log->Print("nPhoneOnlyCountReserve = %d, m_vecPhone = %d\n", nPhoneOnlyCountReserve, m_vecPhone.size());
			ZeroMemory(&t, sizeof(CUSTOMER_PHONE));
			ZeroMemory(&tn, sizeof(CUSTOMER_PHONE_NAME));
			m_vecPhone.push_back(t);
			m_vecPhoneName.push_back(tn);

			CUSTOMER_PHONE &t2 = m_vecPhone.at(m_vecPhone.size() - 1);
			t2.nIndex = (UINT)&m_vecPhone.at(m_vecPhone.size() - 1);

			CUSTOMER_PHONE_NAME &tn2 = m_vecPhoneName.at(m_vecPhoneName.size() - 1);
			tn2.nIndex = (UINT)&m_vecPhoneName.at(m_vecPhoneName.size() - 1);

			m_cuslog.Print("Phone SaveVector: P=%d PN=%d PF=%d PNF=%d\n", 
						m_vecPhone.size(),
						m_vecPhoneName.size(),
						m_vecPhoneFour.size(),
						m_vecPhoneNameFour.size());
			
			SaveVector(m_vecPhone, t, GetCodeFileName(CUSTOMER_PHONE_FILE_NAME));
			SaveVector(m_vecPhoneName, tn, GetCodeFileName(CUSTOMER_PHONE_NAME_FILE_NAME));
			SaveVector(m_vecPhoneFour, t4, GetCodeFileName(CUSTOMER_PHONE_FOUR_FILE_NAME));
			SaveVector(m_vecPhoneNameFour, tn4, GetCodeFileName(CUSTOMER_PHONE_NAME_FOUR_FILE_NAME));

			m_vecPhone.pop_back();
			m_vecPhoneName.pop_back();
		}

		return TRUE;
	}
	return FALSE;
}

template<typename MyVector>
void CCustomerData::JoinPhoneWithCustomer(MyVector &vec)
{
	if(m_vecCustomer.size() == 0)
		return;

	if(!IsSecond())
	{
		MyVector::iterator it;
		CUSTOMER_VECTOR::iterator itMain = m_vecCustomer.begin();
		long nCurCNo = itMain->nCNo;

		for(it = vec.begin(); it != vec.end();)
		{
			if(it->nType == 0)
			{
				if(itMain != m_vecCustomer.end())
				{
					if(it->nIndex > itMain->nCNo)
					{
						itMain++;
						continue;
					}

					if(it->nIndex == itMain->nCNo && itMain->nState != 1)
					{
						it->nType = CTYPE_OK;
						it->nIndex = itMain->nIndex;
					}
					else 
						it->nType = CTYPE_NEW;
				}
				else
					it->nType = CTYPE_NEW;
			}

			it++;
		}
	}
	else
	{
		//new cus 인 경우에, 순서대로 정렬되어 있지 않아, 전체 검색을 해야한다.
		MyVector::iterator it;
		CUSTOMER_VECTOR::iterator itMain;

		for(it = vec.begin(); it != vec.end(); it++)
		{
			if(it->nType == 0)
			{
				for(itMain = m_vecCustomer.begin(); itMain != m_vecCustomer.end(); itMain++)
				{
					if(it->nIndex == itMain->nCNo && itMain->nState != 1)
					{
						it->nType = CTYPE_OK;
						it->nIndex = itMain->nIndex;
						break;
					}
				}

				if(it->nType == 0)
					it->nType = CTYPE_NEW;
			}
		}
	}
}

template<typename MyVector, typename MyVector2, typename T, typename T4, class ComplareFunc>
void CCustomerData::MakePhoneFourVector(MyVector &vec, MyVector2 &vecFour, 
										T &t, T4 &t4,
										ComplareFunc _ComplareFunc,
										long &nPrePhonePointSub,
										BOOL bOnlyPointMatch)
{
	if(bOnlyPointMatch)
	{
		if(vecFour.size() > 0)
		{
			UINT nOldPOIPoint = vec.at(vec.size() - 1).nIndex;
			UINT nNewPOIPoint = (UINT)&vec.at(vec.size() - 1);

			if(nOldPOIPoint > 0 && nNewPOIPoint > 0)
			{
				nPrePhonePointSub = nNewPOIPoint - nOldPOIPoint;

				MyVector2::iterator it;
				for(it = vecFour.begin(); it != vecFour.end(); it++)
					it->pPhone = (T*)((long)it->pPhone + nPrePhonePointSub);

				if(vecFour.size() > 0)
					vecFour.pop_back();
			}
		}
	}
	else
	{
		vecFour.clear();
		vecFour.reserve(vec.size());

		MyVector::iterator it;
		for(it = vec.begin(); it != vec.end(); it++)
		{
			t4.nPhoneFour = it->nPhone % 10000;
			t4.pPhone = &(*it);
			vecFour.push_back(t4);
		}

		sort(vecFour.begin(), vecFour.end(), _ComplareFunc);
	}
}

AFX_INLINE long CCustomerData::CNoToVectorID(UINT nCNo)
{
	CUSTOMER_VECTOR::iterator it = lower_bound(m_vecCustomer.begin(), m_vecCustomer.end(), nCNo, KeyCompare());
	if(it != m_vecCustomer.end() && it->nCNo == nCNo)
		return it->nIndex;

	return -1;
}

void CCustomerData::MakeCompanyNameIndex(BOOL bFromFile)
{
	CDisplayBarThreadText dbt(m_pMkDb->m_pDBT, "고객데이터를 최적화 중입니다.", TRUE);
	m_vecCIdx.clear();

	if(bFromFile)
	{
		COMPANY_INDEX t;
		if(LoadVector(m_vecCIdx, t, GetCodeFileName(COMPANY_INDEX_FILE_NAME)))
		{
			m_cuslog.Print("MakeCompanyNameIndex: LoadVector: m_vecCIdx=%d\n", m_vecCIdx.size());

			COMPANY_INDEX_VECTOR::iterator it;
			for(it = m_vecCIdx.begin(); it != m_vecCIdx.end(); it++)
			{
				if(it->nPhoneType == IDX_PHONE_ONLY)
				{
					it->pPhone = (CUSTOMER_PHONE_NAME*)((long)it->pPhone + m_nPrePhonePointSub);
					//g_bana_log->Print("%s\n", it->pPhone->GetPhone());
				}
				else if(it->nPhoneType == IDX_PHONE_NAME)
					it->pPhone = (CUSTOMER_PHONE_NAME*)((long)it->pPhone + m_nPrePhoneNamePointSub);
				else if(it->nPhoneType == IDX_EMPTY_PHONE)
					it->pPhone = (CUSTOMER_PHONE_NAME*)GetEmptyPhone();
				else 
					it->pPhone = NULL;

				it->pCus = (CUSTOMER_DATA*)((long)it->pCus + m_nPreCustomerPointSub);
			}
		}
		else
		{
			bFromFile = FALSE;
		}
	}

	if(!bFromFile)
	{
		m_vecCIdx.reserve(m_vecPhone.size() + m_vecPhoneName.size() + m_vecCustomer.size());
		for_each(m_vecCustomer.begin(), m_vecCustomer.end(), CMakeCustomerIndex(m_vecCustomer, GetEmptyPhone(), m_vecCIdx));
		for_each(m_vecPhone.begin(), m_vecPhone.end(), CMakePhoneIndex(m_vecPhone, m_vecCustomer, m_vecCIdx));
		for_each(m_vecPhoneName.begin(), m_vecPhoneName.end(), CMakePhoneNameIndex(m_vecPhoneName, m_vecCustomer, m_vecCIdx));
		sort(m_vecCIdx.begin(), m_vecCIdx.end(), CompanyIndexCompare());

		m_cuslog.Print("MakeCompanyNameIndex: m_vecCidx=%d, m_vecCustomer = %d, m_vecPhone=%d, m_vecPhoneName=%d\n", 
							m_vecCIdx.size(), m_vecCustomer.size(), m_vecPhone.size(), m_vecPhoneName.size());

		if(m_vecCIdx.size() > 0 && !IsSecond())
		{
			COMPANY_INDEX t;
			SaveVector(m_vecCIdx, t, GetCodeFileName(COMPANY_INDEX_FILE_NAME));
		}

		if(m_vecCIdx.size() == 0 && 
			m_vecPhone.size() > 0 &&
			m_vecPhoneName.size() > 0 &&
			!IsSecond())
		{
			m_cuslog.Print("인덱스생성 실패입니다.\n프로그램 재시작바랍니다.");
			MessageBox(NULL, "인덱스생성 실패입니다.\n프로그램 재시작바랍니다.", "CIDX에러", MB_OK);
			ClearFileData();
		}
	}

	CIDX_ITER it;
	CIDX_ITER itStart = m_vecCIdx.begin();
	m_mapCIdx.clear();
	for(it = m_vecCIdx.begin(); it !=  m_vecCIdx.end(); it++)
	{
		if(itStart->GetCompanyCode() != it->GetCompanyCode())
		{
			CIDX_ITER it2 = it;
			it2--;
			g_bana_log->Print("nCompany = %d, %d, %d\n", itStart->GetCompanyCode(), it2->pCus->nCNo, it->pCus->nCNo);
			m_mapCIdx.insert(CIDX_ITER_MAP::value_type(itStart->GetCompanyCode(), make_pair(itStart, it)));
			itStart = it;
		}
	}


	if(itStart != m_vecCIdx.end())
		m_mapCIdx.insert(CIDX_ITER_MAP::value_type(itStart->GetCompanyCode(), make_pair(itStart, it)));
}

AFX_INLINE CUSTOMER_PHONE* CCustomerData::GetEmptyPhone()
{
	ZeroMemory(&m_cpEmpty, sizeof(CUSTOMER_PHONE));
	m_cpEmpty.nIndex = 0;
	m_cpEmpty.nExpiredDay = 0xFFFF;
	return &m_cpEmpty;
}

BOOL CCustomerData::SearchCustomer(long nCompany, CString strSearchCustomer, SEARCH_CUS_VEC &csdata,
								   long nSearchCNo)
{
	if(m_pcusNew->m_vecCustomer.size() == 0)
	{
		SearchCustomerSingle(nCompany, strSearchCustomer, csdata, nSearchCNo);
		RemoveDeletedCustomer(csdata);
	}
	else
	{
		SEARCH_CUS_VEC csdata2;
		SearchCustomerSingle(nCompany, strSearchCustomer, csdata, nSearchCNo);
		m_pcusNew->SearchCustomerSingle(nCompany, strSearchCustomer, csdata2, nSearchCNo); // choe
		DeleteOldCustomerData(nCompany, csdata, csdata2);
	}
	if(m_bCharOrdering)
	{
		sort(csdata.begin(), csdata.end(), SearchCustomerCompareABC());
		UpdateSearchCusVec(csdata, nSearchCNo);
	}
	else
	{
		sort(csdata.begin(), csdata.end(), SearchCustomerCompare());
		UpdateSearchCusVec(csdata, nSearchCNo);
		if(nSearchCNo == 0)
			sort(csdata.begin(), csdata.end(), SearchCustomerCompare2());
	}

	return TRUE;
}

void CCustomerData::RemoveDeletedCustomer(SEARCH_CUS_VEC &csOld)
{
	SEARCH_CUS_VEC::iterator it;
	
	for(it = csOld.begin(); it != csOld.end();)
	{
		if(it->pData->nState == 1)
		{
			g_bana_log->Print("RemoveDeletedCustomer: %d, %s\n", it->pData->nCNo, it->pData->szCompany);
			it = csOld.erase(it);
		}
		else
			it++;
	}
}

void CCustomerData::DeleteOldCustomerData(long nCompany, SEARCH_CUS_VEC &csOld, SEARCH_CUS_VEC &csNew)
{
	SEARCH_CUS_VEC::iterator it, it2;
	CIDX_ITER_PAIR itPair;

	RemoveDeletedCustomer(csOld);

	if(csNew.size() > 0)
	{
		for(it = csOld.begin(); it != csOld.end();)
		{
			if(m_pcusNew->SearchCustomerCNo(nCompany, it->pData->nCNo, itPair))
			{
				//g_bana_log->Print("New Customer 벡터에 해당 CNO가 존재하여 OLD데이터를 삭제함(%d)\n", it->pData->nCNo);
				//g_bana_log->Print("DeleteOldCustomerData: %d, %s\n", it->pData->nCNo, it->pData->szCompany);
				it = csOld.erase(it);
			}
			else
				it++;
		}

		for(it = csNew.begin(); it != csNew.end(); it++)
		{
			if(it->pData->nState != 1)
				csOld.push_back(*it);
			else
				g_bana_log->Print("nState == 1: %d %s\n", it->pData->nCNo, it->pData->szCompany);
		}

		for(it = csOld.begin(); it != csOld.end();)
		{
			BOOL bErased = FALSE;
			it2 = it;
			it2++;

			for(; it2 != csOld.end(); it2++)
			{
				if(it->pData->nCNo == it2->pData->nCNo && 
					it->strPhone == it2->strPhone)
				{
					//g_bana_log->Print("DeleteOldCustomerData2: %d, %s\n", it->pData->nCNo, it->pData->szCompany);
					it = csOld.erase(it);
					bErased = TRUE;
					break;
				}
			}

			if(!bErased)
				it++;
		}
	}
}

void CCustomerData::UpdateSearchCusVec(SEARCH_CUS_VEC &csdata, long nSearchCNo)
{
	long nPreCNo = 0;
	SEARCH_CUS_VEC::iterator it;
	SEARCH_CUS_VEC::iterator itPre = csdata.end();
	for(it = csdata.begin(); it != csdata.end();)
	{
		if(nSearchCNo == 0)
		{
			if(itPre != csdata.end())
			{
				if(nPreCNo == it->pData->nCNo)
				{
					if(it->strName.IsEmpty() && it->strDepart.IsEmpty() ||
					///if(
						it->strDepart == itPre->strDepart && it->strName == itPre->strName)
					{
						//g_bana_log->Print("Erase1: %s\t%s\t%s\n", it->strDepart, it->strName, it->strPhone);
						it = csdata.erase(it);
						continue;
					}

					if(itPre->strName.IsEmpty() && itPre->strDepart.IsEmpty())
					{
						//g_bana_log->Print("Erase2: %s\t%s\t%s\n", it->strDepart, it->strName, it->strPhone);
						it = csdata.erase(itPre);
						nPreCNo = 0;
					}
				}
			}
		}

		if(nPreCNo == it->pData->nCNo)
		{
			if(itPre != csdata.end())
			{
				itPre->bHasParentOrChild = TRUE;
				itPre->bHasNextMember = TRUE;
				it->bHasPreMember = TRUE;
			}

			it->bHasParentOrChild = TRUE;
		}
		else
		{
			it->bHasNextMember = FALSE;
			it->bHasPreMember = FALSE;
			it->bHasParentOrChild = FALSE;
		}

		nPreCNo = it->pData->nCNo;
		itPre = it;
		it++;
	}
}

BOOL CCustomerData::SearchCustomerSingle(long nCompany, CString strSearchCustomer,SEARCH_CUS_VEC &csdata,
										long nSearchCNo)
{
	if(nSearchCNo > 0)
	{
		SearchCustomerCNo(nCompany, nSearchCNo, csdata);
	}
	else
	{
		int nLen = strSearchCustomer.GetLength();

		CString strPhone = ExtractPhoneNumber(strSearchCustomer);

		if(strPhone.GetLength() > 0)
		{
			CString strDDD, strBody;
			GetPhoneDivDDDBody(strPhone, strDDD, strBody);

			SearchPhone(m_vecPhone, csdata, strBody, strDDD, nCompany, PhoneNumberCompare(), FALSE);
			SearchPhone(m_vecPhoneName, csdata, strBody, strDDD, nCompany, PhoneNumberNameCompare(), TRUE);
		}
		else if(nLen >= 3)
		{
			if(nLen == 4 && LF->IsStringDigit(strSearchCustomer))
			{
				SearchPhoneFour(m_vecPhoneFour, csdata, strSearchCustomer, nCompany, PhoneNumberFourCompare(), FALSE);
				SearchPhoneFour(m_vecPhoneNameFour, csdata, strSearchCustomer, nCompany, PhoneNumberNameFourCompare(), TRUE);
			}

			SearchCustomerName(nCompany, strSearchCustomer, csdata);
		}
	}

	return TRUE;
}

BOOL CCustomerData::SearchCustomerCNo(long nCompany, long nCNo, CIDX_ITER_PAIR &itPair)
{
	CIDX_ITER_MAP::iterator itMap = m_mapCIdx.find(nCompany);
	if(itMap != m_mapCIdx.end())
	{
		itPair = equal_range(itMap->second.first, itMap->second.second, nCNo, CompanyIndexCompareCNo());

		if(itPair.first != itPair.second)
			return TRUE;
	}

	return FALSE;
}

void CCustomerData::SearchCustomerCNo(long nCompany, long nCNo, SEARCH_CUS_VEC &csdata)
{
	CIDX_ITER_PAIR itPair;

	if(SearchCustomerCNo(nCompany, nCNo, itPair))
	{
		COMPANY_INDEX_VECTOR::iterator it;
		for(it = itPair.first; it != itPair.second; it++)
		{
			if(!it->pCus->DeletedCustomer())
			{
				SEARCH_CUS_DATA scus;

				scus.pData = it->pCus;
				scus.strPhone = it->pPhone->GetPhone();
				scus.nPos = 0;
				if(scus.nPos < 0) scus.nPos = 0xFFFF;
				scus.nLen = 0;
				scus.bSecondCusData = IsSecond();
				scus.nMainPhone = it->pPhone->nMainPhone;
				scus.bHasParentOrChild = 0;
				scus.bHasPreMember = 0;
				scus.bHasNextMember = 0;
				scus.nPhoneExpiredDay = it->pPhone->nExpiredDay;
				scus.nTelID = it->pPhone->nID;

				if(it->nPhoneType == IDX_PHONE_NAME)
				{
					scus.strDepart = it->GetDepart();
					scus.strName = it->GetName();
				}

				csdata.push_back(scus);
			}
		}
	}
}

void CCustomerData::SearchCustomerName(long nCompany, CString strSearchCustomer, SEARCH_CUS_VEC &csdata)
{
	CString strKeyword = strSearchCustomer;
	CString strKeyword2;
	BOOL bKeyword2 = FALSE;
	BOOL bOnlyDepartManager = FALSE;
//	long nBreakCNo = 12562765;

	int nPos = strSearchCustomer.Find("/");

	if(nPos > 3 && strSearchCustomer.GetLength() - nPos >= 1)
	{
		strKeyword = strSearchCustomer.Left(nPos);
		strKeyword2 = strSearchCustomer.Mid(nPos + 1);
		bKeyword2 = TRUE;
	}
	else if(nPos == 0)
	{
		bOnlyDepartManager = TRUE;
		strKeyword.Remove('/');
	}
	else
	{
		strKeyword.Remove('/');
	}

	CIDX_ITER_MAP::iterator itMap = m_mapCIdx.find(nCompany);
	if(itMap != m_mapCIdx.end())
	{
		CIDX_ITER it;
		int nCount = 0;

		for(it = itMap->second.first; it != itMap->second.second; it++)
		{
			COMPANY_INDEX *pIdx = &(*it);

//			if(it->pCus->nCNo == nBreakCNo)
//				g_bana_log->Print("BREAK POINT\n");

			if(csdata.size() >= SHOW_COUNT)
			{
				g_bana_log->Print("CUSTOMER_DATA: SHOW_COUNT를 초과했습니다.\n");
				break;
			}

			if(pIdx->pCus->DeletedCustomer())
				continue;

			//if(strstr(it->GetCompany(), "아모스") > 0)
			//	g_bana_log->Print("%s, %s, %s\r\n", pIdx->GetCompany(), pIdx->GetDepart(), pIdx->GetName());
			if(bOnlyDepartManager || !SearchCustomerNameSub(pIdx, pIdx->GetCompany(), strKeyword, csdata))
			{
				long nCompanyLen = strlen(pIdx->GetCompany());
				CString str = pIdx->GetDepart();
				if(!SearchCustomerNameSub(pIdx, pIdx->GetDepart(), strKeyword, csdata, nCompanyLen))
				{
					long nDepartLen = strlen(pIdx->GetDepart());
					if(!SearchCustomerNameSub(pIdx, pIdx->GetName(), strKeyword, csdata, nCompanyLen + nDepartLen))
					{
						continue;
					}
				}
			}
		
			if(bKeyword2)
			{
				if(bOnlyDepartManager || !SearchCustomerNameSub(pIdx, pIdx->GetCompany(), strKeyword2, csdata, 0, 1))
				{
					long nCompanyLen = strlen(pIdx->GetCompany());
					if(!SearchCustomerNameSub(pIdx, pIdx->GetDepart(), strKeyword2, csdata, nCompanyLen, 1)) 
					{
						long nDepartLen = strlen(pIdx->GetDepart());
						if(!SearchCustomerNameSub(pIdx, pIdx->GetName(), strKeyword2, csdata, nCompanyLen + nDepartLen, 1))
						{
							csdata.pop_back();
							continue;
						}
					}
				}
			}
		}
	}
}

AFX_INLINE BOOL CCustomerData::SearchCustomerNameSub(COMPANY_INDEX *pIdx, char *szName, 
										CString &strKeyword, SEARCH_CUS_VEC &csdata,
										long nBasePos, BOOL bKeyword2)
{
	char szNameTemp[50];
	strcpy(szNameTemp, szName);
	strlwr(szNameTemp);


	if(szName[0] != 0 && strstr(szNameTemp, (LPSTR)(LPCTSTR)strKeyword) != 0)
	//if(szName[0] != 0 && strstr(szName, (LPSTR)(LPCTSTR)strKeyword) != 0)
	{
		if(!bKeyword2)
		{
			SEARCH_CUS_DATA scus;

			scus.pData = pIdx->pCus;

			if(!pIdx->pPhone)
				return FALSE;

			scus.strPhone = pIdx->pPhone->GetPhone();
			scus.nPos = nBasePos + CString(szName).Find(strKeyword);
			if(scus.nPos < 0) scus.nPos = 0xFFFF;
			scus.nLen = strlen(strKeyword);
			scus.bSecondCusData = IsSecond();
			scus.nMainPhone = pIdx->pPhone->nMainPhone;
			scus.bHasParentOrChild = 0;
			scus.bHasPreMember = 0;
			scus.bHasNextMember = 0;
			scus.nPhoneExpiredDay = pIdx->pPhone->nExpiredDay;
			scus.nTelID = pIdx->pPhone->nID;
			
			if(pIdx->nPhoneType == IDX_PHONE_NAME)
			{
				scus.strDepart = pIdx->GetDepart();
				scus.strName = pIdx->GetName();
			}

			csdata.push_back(scus);
		}
		else
		{
			long nPos2 = nBasePos + CString(szName).Find(strKeyword);

			SEARCH_CUS_DATA &scus = csdata.at(csdata.size() - 1);
			scus.nLen += strlen(strKeyword);
			scus.nPos = min(nPos2, scus.nPos);
		}

		return TRUE;
	}	

	return FALSE;
}


template<typename MyVector, class CompareFunc>
void CCustomerData::SearchPhone(MyVector &vec, SEARCH_CUS_VEC &csdata,
								CString &strPhone, CString &strDDD, long &nCompany, CompareFunc &func,
								BOOL bPhoneName)
{
	pair<MyVector::iterator, MyVector::iterator> itPhonePair 
		= equal_range(vec.begin(), vec.end(), atol(strPhone), func);

	if(itPhonePair.first != itPhonePair.second)
	{
		MyVector::iterator it;
		for(it = itPhonePair.first; it != itPhonePair.second; it++)
		{
			if(it->nCompany == nCompany)
			{
				if(strDDD.IsEmpty() || strDDD == it->szDDD)
				{
					SEARCH_CUS_DATA scus;
					CUSTOMER_DATA *pData = GetCustomerFromPhone(*it, nCompany);
					if(pData && !pData->DeletedCustomer())
					{
						scus.pData = pData;
						scus.strPhone = it->GetPhone();
						scus.nPos = 0;
						scus.nLen = 0;
						scus.bSecondCusData = IsSecond();
						scus.nMainPhone = it->nMainPhone;
						scus.bHasParentOrChild = 0;
						scus.bHasPreMember = 0;
						scus.bHasNextMember = 0;
						scus.nPhoneExpiredDay = it->nExpiredDay;
						scus.nTelID = it->nID;

						if(bPhoneName)
						{
							scus.strDepart = it->szDepart;
							scus.strName = it->szName;
						}

						csdata.push_back(scus);
					}
				}
			}
		}
	}
}

template<typename MyVector, class CompareFunc>
void CCustomerData::SearchPhoneFour(MyVector &vec, SEARCH_CUS_VEC &csdata,
								CString &strPhone, long &nCompany, CompareFunc &func,
								BOOL bPhoneName)
{
	pair<MyVector::iterator, MyVector::iterator> itPhonePair 
	= equal_range(vec.begin(), vec.end(), atol(strPhone), func);

	if(itPhonePair.first != itPhonePair.second)
	{
		MyVector::iterator it;
		for(it = itPhonePair.first; it != itPhonePair.second; it++)
		{
			//g_bana_log->Print("it->pPhone->nCompany = %d, nCompany = %d\n", it->pPhone->nCompany, nCompany);

			if(it->pPhone->nCompany == nCompany)
			{
				SEARCH_CUS_DATA scus;
				CUSTOMER_DATA *pData = GetCustomerFromPhone(*(it->pPhone), nCompany, TRUE);
				if(pData && !pData->DeletedCustomer())
				{
					scus.pData = pData;
					scus.strPhone = it->pPhone->GetPhone();
					scus.nPos = 0;
					scus.nLen = 0;
					scus.bSecondCusData = IsSecond();
					scus.nMainPhone = it->pPhone->nMainPhone;
					scus.bHasParentOrChild = 0;
					scus.bHasPreMember = 0;
					scus.bHasNextMember = 0;
					scus.nPhoneExpiredDay = it->pPhone->nExpiredDay;
					scus.nTelID = it->pPhone->nID;

					if(bPhoneName)
					{
						scus.strDepart = it->pPhone->szDepart;
						scus.strName = it->pPhone->szName;
					}

					csdata.push_back(scus);
				}
			}
		}
	}
}


BOOL CCustomerData::IsDataLoadOK()
{
	if(m_vecCustomer.size() > 0 &&
		m_vecCIdx.size() > 0 &&
		m_vecPhone.size() > 0 && 
		m_vecPhoneFour.size() > 0)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CCustomerData::MakeAllFromNetwork()
{
	long nCount = 0;

	COleDateTime dtPreRefresh = m_dtLastRefresh;
	long nRefreshMiliSec = m_nRefreshMiliSec;

	if(MakeCustomerFromNetwork(nCount))
	{
		if(!IsSecond())
			m_pcusNew->m_dtLastRefresh = m_dtLastRefresh;

		if(nCount == 0)	//고객데이터변경이 없으면 고객폰갱신이 필요없다.
			return TRUE;

		if(MakeCustomerPhoneFromNetwork(dtPreRefresh, nRefreshMiliSec))
		{
			if(!IsSecond())
				SaveFileDate(m_dtLastRefresh);
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CCustomerData::MakeAllFromFile()
{
	if(MakeCustomerFromFile() && MakeCustomerPhoneFromFile())
	{
		m_pcusNew->m_dtLastRefresh = m_dtLastRefresh;
		return TRUE;
	}

	return FALSE;
}

BOOL CCustomerData::MakeCustomerFromFile()
{
	CUSTOMER_DATA t;
	if(LoadVector(m_vecCustomer, t, GetCodeFileName(CUSTOMER_FILE_NAME)))
	{
		m_cuslog.Print("MakeCustomerFromFile: m_vecCustomer=%d\n", m_vecCustomer.size());

		UINT nOldPOIPoint = m_vecCustomer.at(m_vecCustomer.size() - 1).nIndex;
		UINT nNewPOIPoint = (UINT)&m_vecCustomer.at(m_vecCustomer.size() - 1);
		if(nOldPOIPoint > 0 && nNewPOIPoint > 0)
		{
			m_nPreCustomerPointSub = nNewPOIPoint - nOldPOIPoint;
			m_vecCustomer.pop_back();
			return TRUE;
		}

		m_vecCustomer.clear();
	}

	return FALSE;
}

BOOL CCustomerData::MakeCustomerPhoneFromFile()
{
	CUSTOMER_PHONE t;
	CUSTOMER_PHONE_FOUR t4;

	if(!LoadVector(m_vecPhone, t, GetCodeFileName(CUSTOMER_PHONE_FILE_NAME)))
		return FALSE;

	if(!LoadVector(m_vecPhoneFour, t4, GetCodeFileName(CUSTOMER_PHONE_FOUR_FILE_NAME)))
	{
		m_vecPhone.clear();
		return FALSE;
	}

	CUSTOMER_PHONE_NAME tn;
	CUSTOMER_PHONE_NAME_FOUR tn4;

	if(!LoadVector(m_vecPhoneName, tn, GetCodeFileName(CUSTOMER_PHONE_NAME_FILE_NAME)))
	{
		m_vecPhone.clear();
		m_vecPhoneFour.clear();
		return FALSE;
	}

	if(!LoadVector(m_vecPhoneNameFour, tn4, GetCodeFileName(CUSTOMER_PHONE_NAME_FOUR_FILE_NAME)))
	{
		m_vecPhone.clear();
		m_vecPhoneFour.clear();
		m_vecPhoneName.clear();
		return FALSE;
	}


	m_cuslog.Print("MakeCustomerPhoneFromFile: P=%d, PF=%d, PN=%d, PNF=%d\n", 
						m_vecPhone.size(), 
						m_vecPhoneFour.size(),
						m_vecPhoneName.size(),
						m_vecPhoneNameFour.size());

	MakePhoneFourVector(m_vecPhone, m_vecPhoneFour, t, t4, PhoneNumberFourCompare(), m_nPrePhonePointSub, TRUE);
	MakePhoneFourVector(m_vecPhoneName, m_vecPhoneNameFour, tn, tn4, PhoneNumberNameFourCompare(), m_nPrePhoneNamePointSub, TRUE);
	MakeCompanyNameIndex(TRUE);

	return TRUE;
}

BOOL CCustomerData::AutoLoad()
{
	if(!CheckFileDate() || !MakeAllFromFile())
		if(!MakeAllFromNetwork())
			return FALSE;

	RefreshDeleteCustomer();

	return TRUE;
}

void CCustomerData::SetCompanyCode(long nCompanyCode, BOOL bIntegrated)
{
	m_nCompanyCode = nCompanyCode;
	m_bIntegrated = bIntegrated;
}

CString CCustomerData::GetCodeFileName(CString strFileName)
{
	strFileName.Replace("xxx", GetStringCompanyCode());
	return strFileName;
}

BOOL CCustomerData::CheckFileDate()
{
	COleDateTime dtFileTime;

	if(GetFileDate(dtFileTime))
	{
		COleDateTime dtGenerate;
		CMkCommand pCmd(m_pMkDb, "select_updated_customer_count4");
		CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
		pCmd.AddParameter(m_nCompanyCode);
		pCmd.AddParameter(m_bIntegrated);
		pCmd.AddParameter(dtFileTime);
		CMkParameter *parOutSchema = pCmd.AddParameter(typeString, typeOutput, 50, m_strSchemaVersion);
		CMkParameter *parOut = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
		CMkParameter *parOutGenerate = pCmd.AddParameter(typeDate, typeOutput, sizeof(COleDateTime), dtGenerate);
		if(pCmd.Execute())
		{
			if(parRet->GetLong() == 0)
			{
				m_dtLastRefresh = dtFileTime;
				return TRUE;
			}
			else if(parRet->GetLong() == 1)
			{
				parOutGenerate->GetValue(dtGenerate);
				COleDateTimeSpan dtSpan = dtGenerate - dtFileTime;

				m_cuslog.Print("CUS UPDATE: 경과시간 %0.1fH, 변경된고객수 = %d, 갱신시각=%s\n", 
					dtSpan.GetTotalHours(), parOut->GetLong(), dtGenerate.Format("%Y-%m-%d %H:%M"));
			}
			else if(parRet->GetLong() == 2)
			{
				m_cuslog.Print("CUS UPDATE: 스키마버전 업데이트 %s -> %s\n", m_strSchemaVersion, parOutSchema->GetString());
				m_strSchemaVersion = parOutSchema->GetString();
			}
		}
	}

	ClearFileData();
	return FALSE;
}

BOOL CCustomerData::GetFileDate(COleDateTime &dtFileTime)
{
	CIniReader ini(LF->GetModuleFullPath() + CUSTOMER_INI_FILE);
	CString strDate = ini.getKeyValue("Date", GetStringCompanyCode());
	m_strSchemaVersion = ini.getKeyValue("SchemaVersion", GetStringCompanyCode());

	if(strDate.GetLength() > 0)
	{
		long nYear, nMonth, nDay, nHour, nMin, nSec;
		_stscanf((LPSTR)(LPCTSTR)strDate, _T("%d %d %d %d %d %d"),
			&nYear,&nMonth,&nDay,&nHour,&nMin,&nSec);
		dtFileTime.SetDateTime(nYear, nMonth, nDay, nHour, nMin, nSec);

		if(dtFileTime.GetStatus() != COleDateTime::invalid &&
			dtFileTime.GetStatus() != COleDateTime::null)
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CCustomerData::SaveFileDate(COleDateTime dtRefresh)
{
	CIniReader ini(LF->GetModuleFullPath() + CUSTOMER_INI_FILE);
	ini.setKey(dtRefresh.Format("%Y %m %d %H %M %S"), "Date", GetStringCompanyCode());
	ini.setKey(m_strSchemaVersion, "SchemaVersion", GetStringCompanyCode());
}

CString CCustomerData::GetStringCompanyCode()
{
	CString strCompanyCode;
	strCompanyCode.Format("%d", m_nCompanyCode);
	return strCompanyCode;
}

BOOL CCustomerData::IsSecond()
{
	return m_bIsSecondCusData;
}

BOOL CCustomerData::GetNewCustomer()
{
	if(m_pcusNew)
		m_pcusNew->SetCompanyCode(m_nCompanyCode, m_bIntegrated);
	else
		return FALSE;

	return m_pcusNew->MakeAllFromNetwork();
}


template<typename T>
CUSTOMER_DATA *CCustomerData::GetCustomerFromPhone(T &p, long nCompany, BOOL bIfNotExistThenSkip)
{
	if(p.nType == CTYPE_OLD)
		return m_vecPCustomerEx.at(p.nIndex);
	else if(p.nType == CTYPE_OK && p.nIndex < m_vecCustomer.size())
		return &m_vecCustomer.at(p.nIndex);
	else if(!bIfNotExistThenSkip)
	{
		CUSTOMER_DATA *pData = new CUSTOMER_DATA;
		pData->nCNo = 0;
		pData->nState = 0;

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_customer_one_for_customer_data_1");
		pCmd.AddParameter(p.nIndex);
		pCmd.AddParameter(nCompany);

		if(pRs.Execute(&pCmd, "고객데이터를 가져오는 중입니다."))
		{
			if(!pRs.IsEOF())
			{
				pRs.GetFieldValue("nCNo", pData->nCNo);
				pRs.GetFieldValue("nCompany", pData->nCompany);
				pRs.GetFieldValue("sCompany", pData->szCompany);
				pRs.GetFieldValue("sDong", pData->szDong);
				pRs.GetFieldValue("nUseExpiredDay", pData->nUseExpiredDay);
				pRs.GetFieldValue("nUseCount", pData->nUseCount);
				pRs.GetFieldValue("bCredit", pData->bCredit);

				if(strncmp(pData->szCompany, "일반", 4) == 0 ||
					strncmp(pData->szCompany, "고객", 4) == 0)
				{
					pData->szCompany[0] = 0;		
				}
			}
		}

		if(pData->nCNo == 0)
		{
			delete pData;
			return NULL;
		}

/* //by mksong (2011-12-08 오후 12:39)  OLD고객 보기 싫다고 해서 주석처리
		if(pData->nCNo == 0)
		{
			pData->nCNo = p.nIndex;
			strcpy(pData->szCompany, "[오래된고객]");
			pData->nCompany = nCompany;
			strcpy(pData->szDong, "");
			pData->nUseExpiredDay = -1;
			pData->nUseCount = 0;
		}
*/
		pData->nIndex = m_vecPCustomerEx.size();
		m_vecPCustomerEx.push_back(pData);

		m_cuslog.Print("GetCustomerFromPhone: Add: %d, %s\n", pData->nCNo, pData->szCompany);

		p.nType = CTYPE_OLD;
		p.nIndex = pData->nIndex;

		return m_vecPCustomerEx.at(pData->nIndex);
	}

	return NULL;
}

CString CCustomerData::GetInfo()
{
	CString strText;
	COleDateTime dtFileTime;

	if(GetFileDate(dtFileTime))
	{
		strText = "메인데이터 생성시점:\t";
		strText += dtFileTime.Format("%Y-%m-%d %H:%M:%S");
		strText += "\n";
		strText += "메인데이터 고객수:\t";
		strText += LF->GetMyNumberFormat(m_vecCustomer.size());
		strText += "\n";
		strText += "메인데이터 전화번호수:\t";
		strText += LF->GetMyNumberFormat(m_vecPhone.size() + m_vecPhoneName.size());
		strText += "\n";

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_customer_cache_info");
		pCmd.AddParameter(m_nCompanyCode);
		if(pRs.Execute(&pCmd))
		{
			if(!pRs.IsEOF())
			{
				COleDateTime dtFrom;
				pRs.GetFieldValue("dtFrom", dtFrom);

				strText += "메인데이터 기준일자:\t";
				strText += dtFrom.Format("%Y-%m-%d") + "일 이후 데이터만 가져옴\n"; 
				strText += "\t\t\t전화번호 데이터는 최근 3년 데이터\n";
			}
		}

		if(m_pcusNew)
		{
			strText += "\n증분데이터 고객수:\t";
			strText += LF->GetMyNumberFormat(m_pcusNew->m_vecCustomer.size());
			strText += "\n";
			strText += "증분데이터 전화번호수:\t";
			strText += LF->GetMyNumberFormat(m_pcusNew->m_vecPhone.size() + m_pcusNew->m_vecPhoneName.size());
			strText += "\n";
		}
	}
	else
	{
		strText = "고객데이터가 생성되지 않았습니다.";
	}

	return strText;
}

void CCustomerData::ClearFileData()
{
	m_cuslog.Print("ClearFileData\n");

	//DeleteFile(LF->GetModuleFullPath() + "cus.ini");
	DeleteFile(LF->GetModuleFullPath() + GetCodeFileName(CUSTOMER_FILE_NAME));
	DeleteFile(LF->GetModuleFullPath() + GetCodeFileName(CUSTOMER_PHONE_FILE_NAME));
	DeleteFile(LF->GetModuleFullPath() + GetCodeFileName(CUSTOMER_PHONE_NAME_FILE_NAME));
	DeleteFile(LF->GetModuleFullPath() + GetCodeFileName(CUSTOMER_PHONE_FOUR_FILE_NAME));
	DeleteFile(LF->GetModuleFullPath() + GetCodeFileName(CUSTOMER_PHONE_NAME_FOUR_FILE_NAME));
	DeleteFile(LF->GetModuleFullPath() + GetCodeFileName(COMPANY_INDEX_FILE_NAME));
}

void CCustomerData::SetCharOrdering(BOOL bCharOrdering)
{
	m_bCharOrdering = bCharOrdering;
}