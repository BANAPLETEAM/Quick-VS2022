#pragma once

#include "CustomerDataDef.h"

class CCustomerData;


class CCustomerData
{
public:
	CCustomerData(void);
	virtual ~CCustomerData(void);

	template<typename MyVector, typename T>
	void EncVector(MyVector &vec, T &t);

	template<typename MyVector, typename T>
	void DecVector(MyVector &vec, T &t);

	template<typename MyVector, typename T>
	BOOL SaveVector(MyVector &vec, T &t, CString strFile, BOOL bDefaultPath = TRUE);

	template<typename MyVector, typename T>
	BOOL LoadVector(MyVector &vec, T &t, CString strFile, BOOL bDefaultPath = TRUE);

	void MakeCompanyNameIndex(BOOL bFromFile);
	BOOL MakeCustomerFromNetwork(long &nCount);
	BOOL MakeCustomerPhoneFromNetwork(COleDateTime dtPreRefresh, long nRefreshMiliSec);
	long CNoToVectorID(UINT nCNo);
	BOOL SearchCustomerSingle(long nCompany, CString strSearchCustomer, SEARCH_CUS_VEC &csdata, long nSearchCNo);
	BOOL SearchCustomer(long nCompany, CString strSearchCustomer, SEARCH_CUS_VEC &csdata, long nSearchCNo = 0);
	CString ExtractPhoneNumber(CString strText);
	BOOL VerifyAvailblePhoneNumber(char *p);
	void GetPhoneDivDDDBody(CString &strPhone, CString &strDDD, CString &strBody);
	static void GetPhoneDivBody(CString &strPhone, int nDDDLen, CString &strDDD, CString &strBody);
	BOOL IsDataLoadOK();
	BOOL CheckFileDate();
	BOOL MakeCustomerFromFile();
	BOOL MakeCustomerPhoneFromFile();
	BOOL MakeAllFromNetwork();
	BOOL MakeAllFromFile();
	BOOL AutoLoad();
	void SetCompanyCode(long nCompanyCode, BOOL bIntegrated);
	CString GetCodeFileName(CString strFileName);
	CString GetStringCompanyCode();
	void SaveFileDate(COleDateTime dtLastRefresh);
	BOOL GetNewCustomer();
	BOOL IsSecond();
	void SetMainCusData();

	template<typename T>
	CUSTOMER_DATA* GetCustomerFromPhone(T &p, long nCompany, BOOL bIfNotExistThenSkip = FALSE);

	BOOL GetFileDate(COleDateTime &dtFileTime);
	CString GetInfo();

	template<typename MyVector>
	void JoinPhoneWithCustomer(MyVector &vec);

	template<typename MyVector, typename MyVector2, typename T, typename T4, class CompareFunc>
	void MakePhoneFourVector(MyVector &vec, MyVector2 &vecFour, T &t, T4 &t4,
						CompareFunc _CompanyFunc, long &nPrePhonePointSub, BOOL bOnlyPointMatch = FALSE);

	template<typename MyVector, class CompareFunc>
	void SearchPhone(MyVector &vec, SEARCH_CUS_VEC &csdata,
					CString &strPhone, CString &strDDD, long &nCompany, CompareFunc &func,
					BOOL bPhoneName);

	template<typename MyVector, class CompareFunc>
	void SearchPhoneFour(MyVector &vec, SEARCH_CUS_VEC &csdata,
					CString &strPhone, long &nCompany, CompareFunc &func,
					BOOL bPhoneName);

	void SearchCustomerName(long nCompany, CString strSearchCustomer, SEARCH_CUS_VEC &csdata);

	BOOL SearchCustomerNameSub(COMPANY_INDEX *pIdx, char *szName, 
					CString &strKeyword, SEARCH_CUS_VEC &csdata,
					long nBasePos = 0, BOOL bKeyword2 = FALSE);

	void SearchCustomerCNo(long nCompany, long nCNo, SEARCH_CUS_VEC &csdata);
	BOOL SearchCustomerCNo(long nCompany, long nCNo, CIDX_ITER_PAIR &itPair);

	void UpdateSearchCusVec(SEARCH_CUS_VEC &csdata, long nSearchCNo);
	void ClearFileData();
	void DeleteOldCustomerData(long nCompany, SEARCH_CUS_VEC &csOld, SEARCH_CUS_VEC &csNew);
	BOOL HasCNo(long nCompany, long nCNo);
	void RefreshDeleteCustomer();
	void RemoveDeletedCustomer(SEARCH_CUS_VEC &csOld);
	void SetCharOrdering(BOOL bCharOrdering);
	CUSTOMER_PHONE* GetEmptyPhone();

public:
	CUSTOMER_VECTOR m_vecCustomer;
	P_CUSTOMER_VECTOR m_vecPCustomerEx;
	COMPANY_INDEX_VECTOR m_vecCIdx;
	CUSTOMER_PHONE_VECTOR m_vecPhone;
	CUSTOMER_PHONE_NAME_VECTOR m_vecPhoneName;
	CUSTOMER_PHONE_FOUR_VECTOR m_vecPhoneFour;
	CUSTOMER_PHONE_NAME_FOUR_VECTOR m_vecPhoneNameFour;
	//COMPANY_INDEX_VECTOR::iterator m_itLength[31];
	CIDX_ITER_MAP m_mapCIdx;
	UINT m_nGeneralNameCount;
	long m_nCompanyCode;
	BOOL m_bIntegrated;
	COleDateTime m_dtLastRefresh;
	long m_nRefreshMiliSec;
	CString m_strSchemaVersion;
	CCustomerData *m_pcusNew;
	BOOL m_bIsSecondCusData;
	long m_nPrePhonePointSub;
	long m_nPrePhoneNamePointSub;
	long m_nPreCustomerPointSub;
	BOOL m_bCharOrdering;
	static CBanaLog m_cuslog;
	CUSTOMER_PHONE m_cpEmpty;
};
