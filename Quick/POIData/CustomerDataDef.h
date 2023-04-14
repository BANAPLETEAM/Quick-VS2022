
#pragma once


#pragma pack(push)
#pragma pack(1)


enum { IDX_PHONE_ONLY = 0, IDX_PHONE_NAME = 1, IDX_EMPTY_PHONE = 2};


class CUSTOMER_DATA
{
public:
	UINT nIndex;
	UINT nCNo;
	unsigned short int nCompany;
	char szCompany[40];
	char szDong[14];
	unsigned short int nUseExpiredDay;
	unsigned short int nUseCount;
	BYTE nState;
	BYTE bCredit;

public:
	BOOL DeletedCustomer()
	{
		return strncmp(szCompany, "(삭제)", 6) == 0;
	}
};


class CUSTOMER_PHONE
{
public:
	char szDDD[5];	
	UINT nPhone;
	UINT nIndex;
	long nID;
	BYTE nType;
	BYTE nMainPhone;
	unsigned short int nCompany;
	union
	{
		unsigned short int nExpiredDay;
		char szDepart[1];
		char szName[1];
	};

	CString GetPhone() 
	{
		CString strPhone;
		strPhone.Format("%s%d",szDDD, nPhone);
		return strPhone;
	}

};

class CUSTOMER_PHONE_NAME
{
public:
	char szDDD[5] ;	
	UINT nPhone;
	UINT nIndex;
	long nID;
	BYTE nType;
	BYTE nMainPhone;
	unsigned short int nCompany;
	unsigned short int nExpiredDay;
	char szDepart[21];
	char szName[21];

	CUSTOMER_PHONE_NAME::CUSTOMER_PHONE_NAME()
	{
		ZeroMemory(szDDD, sizeof(szDDD));
		ZeroMemory(szDepart, sizeof(szDepart));
		ZeroMemory(szName, sizeof(szName));
	}

	CString GetPhone() 
	{
		CString strPhone;
		if(nPhone != 0)
			strPhone.Format("%s%d",szDDD, nPhone);
		return strPhone;
	}

};

class COMPANY_INDEX
{
public:
	CUSTOMER_PHONE_NAME *pPhone;
	CUSTOMER_DATA *pCus;
	BYTE nPhoneType;

	long GetCompanyCode() { return pCus->nCompany; }
	char* GetCompany() { return pCus->szCompany; }
	char* GetDepart() { return nPhoneType != IDX_PHONE_NAME ? "" : pPhone->szDepart; }
	char* GetName() { return nPhoneType != IDX_PHONE_NAME ? "" : pPhone->szName; }
};

typedef struct 
{
	SHORT nPhoneFour;
	CUSTOMER_PHONE *pPhone;
} CUSTOMER_PHONE_FOUR;

typedef struct 
{
	SHORT nPhoneFour;
	CUSTOMER_PHONE_NAME *pPhone;
} CUSTOMER_PHONE_NAME_FOUR;


class SEARCH_CUS_DATA
{
public:
	CUSTOMER_DATA *pData;
	CString strPhone;
	CString strName;
	CString strDepart;
	long nPos;
	long nLen;
	BOOL bSecondCusData;
	BOOL nMainPhone;
	BOOL bHasParentOrChild;
	BOOL bHasPreMember;
	BOOL bHasNextMember;
	unsigned short int nPhoneExpiredDay;
	long nTelID;
	CString strSortCompany;

	CString GetSortCompany()
	{
		if(strSortCompany.IsEmpty())
		{
			strSortCompany = pData->szCompany;

			int nPos = strSortCompany.Find("/");
			if(nPos > 0 && strSortCompany[nPos + 1] >= '0' && strSortCompany[nPos + 1] <= '9')
				strSortCompany = strSortCompany.Left(nPos);
		}

		return strSortCompany;
	}
};


typedef vector<CUSTOMER_DATA> CUSTOMER_VECTOR;
typedef vector<CUSTOMER_DATA*> P_CUSTOMER_VECTOR;
typedef vector<COMPANY_INDEX> COMPANY_INDEX_VECTOR;
typedef vector<CUSTOMER_PHONE> CUSTOMER_PHONE_VECTOR;
typedef vector<CUSTOMER_PHONE_NAME> CUSTOMER_PHONE_NAME_VECTOR;
typedef vector<CUSTOMER_PHONE_FOUR> CUSTOMER_PHONE_FOUR_VECTOR;
typedef vector<CUSTOMER_PHONE_NAME_FOUR> CUSTOMER_PHONE_NAME_FOUR_VECTOR;
typedef vector<SEARCH_CUS_DATA> SEARCH_CUS_VEC;

typedef COMPANY_INDEX_VECTOR::iterator CIDX_ITER;
typedef map<long, pair<CIDX_ITER, CIDX_ITER>> CIDX_ITER_MAP;
typedef pair<COMPANY_INDEX_VECTOR::iterator, COMPANY_INDEX_VECTOR::iterator> CIDX_ITER_PAIR;


enum { CTYPE_NEW = 1, CTYPE_OLD = 2, CTYPE_OK = 3};

class KeyCompare { 
public:
	bool operator() (const CUSTOMER_DATA& lhs, const CUSTOMER_DATA& rhs) const
	{
		return keyLess(lhs.nCNo, rhs.nCNo);
	}

	bool operator() (const CUSTOMER_DATA& lhs, const UINT& k) const
	{
		return keyLess(lhs.nCNo, k);
	}

	bool operator() (const UINT& k, const CUSTOMER_DATA& rhs) const
	{
		return keyLess(k, rhs.nCNo);
	}

private:
	inline bool keyLess(const UINT& k1, const UINT& k2) const
	{
		return k1 < k2;
	}
};

/*
class StringLengthCompareDesc { 
public:
	bool operator() (const COMPANY_INDEX& lhs, const COMPANY_INDEX& rhs) const
	{
		return keyLess(lhs.nLen, rhs.nLen);
	}

	bool operator() (const COMPANY_INDEX& lhs, const UINT& k) const
	{
		return keyLess(lhs.nLen, k);
	}

	bool operator() (const UINT& k, const COMPANY_INDEX& rhs) const
	{
		return keyLess(k, rhs.nLen);
	}

private:
	inline bool keyLess(const UINT& k1, const UINT& k2) const
	{
		return k1 > k2;
	}
};
*/

class CompanyIndexCompare { 
public:
	bool operator() (const COMPANY_INDEX& lhs, const COMPANY_INDEX& rhs) const
	{
		return lhs.pCus->nCompany < rhs.pCus->nCompany ||
				(lhs.pCus->nCompany == rhs.pCus->nCompany && 
				 lhs.pCus->nCNo < rhs.pCus->nCNo);
	}
};


class CompanyIndexCompareCNo { 
public:
	bool operator() (const COMPANY_INDEX& lhs, const COMPANY_INDEX& rhs) const
	{
		return keyLess(lhs.pCus->nCNo, rhs.pCus->nCNo);
	}

	bool operator() (const COMPANY_INDEX& lhs, const UINT& k) const
	{
		return keyLess(lhs.pCus->nCNo, k);
	}

	bool operator() (const UINT& k, const COMPANY_INDEX& rhs) const
	{
		return keyLess(k, rhs.pCus->nCNo);
	}

private:
	inline bool keyLess(const UINT& k1, const UINT& k2) const
	{
		return k1 < k2;
	}
};


class PhoneNumberCompare { 
public:
	bool operator() (const CUSTOMER_PHONE& lhs, const CUSTOMER_PHONE& rhs) const
	{
		return keyLess(lhs.nPhone, rhs.nPhone);
	}

	bool operator() (const CUSTOMER_PHONE& lhs, const UINT& k) const
	{
		return keyLess(lhs.nPhone, k);
	}

	bool operator() (const UINT& k, const CUSTOMER_PHONE& rhs) const
	{
		return keyLess(k, rhs.nPhone);
	}

private:
	inline bool keyLess(const UINT& k1, const UINT& k2) const
	{
		return k1 < k2;
	}
};


class PhoneNumberNameCompare { 
public:
	bool operator() (const CUSTOMER_PHONE_NAME& lhs, const CUSTOMER_PHONE_NAME& rhs) const
	{
		return keyLess(lhs.nPhone, rhs.nPhone);
	}

	bool operator() (const CUSTOMER_PHONE_NAME& lhs, const UINT& k) const
	{
		return keyLess(lhs.nPhone, k);
	}

	bool operator() (const UINT& k, const CUSTOMER_PHONE_NAME& rhs) const
	{
		return keyLess(k, rhs.nPhone);
	}

private:
	inline bool keyLess(const UINT& k1, const UINT& k2) const
	{
		return k1 < k2;
	}
};


class PhoneNumberFourCompare { 
public:
	bool operator() (const CUSTOMER_PHONE_FOUR& lhs, const CUSTOMER_PHONE_FOUR& rhs) const
	{
		return keyLess(lhs.nPhoneFour, rhs.nPhoneFour);
	}

	bool operator() (const CUSTOMER_PHONE_FOUR& lhs, const UINT& k) const
	{
		return keyLess(lhs.nPhoneFour, k);
	}

	bool operator() (const UINT& k, const CUSTOMER_PHONE_FOUR& rhs) const
	{
		return keyLess(k, rhs.nPhoneFour);
	}

private:
	inline bool keyLess(const UINT& k1, const UINT& k2) const
	{
		return k1 < k2;
	}
};

class PhoneNumberNameFourCompare { 
public:
	bool operator() (const CUSTOMER_PHONE_NAME_FOUR& lhs, const CUSTOMER_PHONE_NAME_FOUR& rhs) const
	{
		return keyLess(lhs.nPhoneFour, rhs.nPhoneFour);
	}

	bool operator() (const CUSTOMER_PHONE_NAME_FOUR& lhs, const UINT& k) const
	{
		return keyLess(lhs.nPhoneFour, k);
	}

	bool operator() (const UINT& k, const CUSTOMER_PHONE_NAME_FOUR& rhs) const
	{
		return keyLess(k, rhs.nPhoneFour);
	}

private:
	inline bool keyLess(const UINT& k1, const UINT& k2) const
	{
		return k1 < k2;
	}
};


class CMakeCustomerIndex
{
public:
	CMakeCustomerIndex(CUSTOMER_VECTOR &vecCustomer, CUSTOMER_PHONE *pcpEmpty, COMPANY_INDEX_VECTOR &vecCidx)
	{
		m_pvecCustomer = &vecCustomer;
		m_cpEmpty = pcpEmpty;
		m_pvecCidx = &vecCidx;
		m_nSize = vecCustomer.size();
	}

	void operator() (CUSTOMER_DATA& elem) const
	{
		if(strlen(elem.szCompany) >= 3)
		{
			COMPANY_INDEX cidx;
			cidx.pCus = &elem;
			cidx.pPhone = (CUSTOMER_PHONE_NAME*)m_cpEmpty;
			cidx.nPhoneType = IDX_EMPTY_PHONE;
			m_pvecCidx->push_back(cidx);
		}
	}

public:
	CUSTOMER_PHONE *m_cpEmpty;
	CUSTOMER_VECTOR *m_pvecCustomer;
	COMPANY_INDEX_VECTOR *m_pvecCidx;
	long m_nSize;
};


class CMakePhoneIndex
{
public:
	CMakePhoneIndex(CUSTOMER_PHONE_VECTOR &vecPhone, CUSTOMER_VECTOR &vecCustomer, COMPANY_INDEX_VECTOR &vecCidx)
	{
		m_pvecPhone = &vecPhone;
		m_pvecCustomer = &vecCustomer;
		m_pvecCidx = &vecCidx;
		m_nSize = vecCustomer.size();
	}

	void operator() (CUSTOMER_PHONE& elem) const
	{
		if(elem.nIndex < m_nSize)
		{
			CUSTOMER_DATA &cdata = m_pvecCustomer->at(elem.nIndex);

			if(strlen(cdata.szCompany) >= 3)
			{
				COMPANY_INDEX cidx;
				cidx.pCus = &cdata;
				cidx.pPhone = (CUSTOMER_PHONE_NAME*)&elem;
				//g_bana_log->Print("%X\r\n", cidx.pPhone);
				cidx.nPhoneType = IDX_PHONE_ONLY;
				m_pvecCidx->push_back(cidx);
			}
		}
	}

public:
	CUSTOMER_PHONE_VECTOR *m_pvecPhone;
	CUSTOMER_VECTOR *m_pvecCustomer;
	COMPANY_INDEX_VECTOR *m_pvecCidx;
	long m_nSize;
};


class CMakePhoneNameIndex
{
public:
	CMakePhoneNameIndex(CUSTOMER_PHONE_NAME_VECTOR &vecPhone, CUSTOMER_VECTOR &vecCustomer, COMPANY_INDEX_VECTOR &vecCidx)
	{
		m_pvecPhone = &vecPhone;
		m_pvecCustomer = &vecCustomer;
		m_pvecCidx = &vecCidx;
		m_nSize = vecCustomer.size();
	}

	void operator() (CUSTOMER_PHONE_NAME& elem) const
	{
		if(elem.nIndex < m_nSize)
		{
			CUSTOMER_DATA &cdata = m_pvecCustomer->at(elem.nIndex);

			if(strlen(cdata.szCompany) >= 3)
			{
				COMPANY_INDEX cidx;
				cidx.pCus = &cdata;
				cidx.pPhone = (CUSTOMER_PHONE_NAME*)&elem;
				cidx.nPhoneType = IDX_PHONE_NAME;
				m_pvecCidx->push_back(cidx);
			}
		}
	}

public:
	CUSTOMER_PHONE_NAME_VECTOR *m_pvecPhone;
	CUSTOMER_VECTOR *m_pvecCustomer;
	COMPANY_INDEX_VECTOR *m_pvecCidx;
	long m_nSize;
};



#define COMPARE_KEY_BEGIN(x, y) 		if(x > y)\
	return TRUE;\
										else if(x == y)\
{
#define COMPARE_KEY_BEGIN_LESS(x, y) 	if(x < y)\
	return TRUE;\
										else if(x == y)\
{
#define COMPARE_KEY_FINAL(x, y) 		if(x > y)\
	return TRUE;
#define COMPARE_KEY_FINAL_LESS(x, y) 	if(x < y)\
	return TRUE;
#define COMPARE_KEY_END()				}


//최종사용일 기준
class SearchCustomerCompare
{ 
public:
	bool operator() (const SEARCH_CUS_DATA& lhs, const SEARCH_CUS_DATA& rhs) const
	{
		BOOL bDepartL = lhs.strDepart.GetLength() ? 1 : 0;
		BOOL bDepartR = rhs.strDepart.GetLength() ? 1 : 0;
		BOOL bNameL = lhs.strName.GetLength() ? 1 : 0;
		BOOL bNameR = rhs.strName.GetLength() ? 1 : 0;

		COMPARE_KEY_BEGIN_LESS(lhs.nPos, rhs.nPos)
		COMPARE_KEY_BEGIN_LESS(lhs.nLen, rhs.nLen)
		COMPARE_KEY_BEGIN_LESS(lhs.pData->nUseExpiredDay, rhs.pData->nUseExpiredDay)
		COMPARE_KEY_BEGIN(lhs.pData->nUseCount, rhs.pData->nUseCount)
		COMPARE_KEY_BEGIN_LESS(lhs.pData->nCNo, rhs.pData->nCNo)
		COMPARE_KEY_BEGIN(lhs.nMainPhone, rhs.nMainPhone)
		COMPARE_KEY_BEGIN(bDepartL, bDepartR)
		COMPARE_KEY_BEGIN_LESS(lhs.strDepart, rhs.strDepart)
		COMPARE_KEY_BEGIN(bNameL, bNameR)
		COMPARE_KEY_BEGIN_LESS(lhs.strName, rhs.strName)
		COMPARE_KEY_FINAL_LESS(lhs.nPhoneExpiredDay, rhs.nPhoneExpiredDay)
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		return FALSE;
	}
};

//최종사용일 기준 + 하위전화번호의 최종사용일 기준
class SearchCustomerCompare2
{ 
public:
	bool operator() (const SEARCH_CUS_DATA& lhs, const SEARCH_CUS_DATA& rhs) const
	{
		BOOL bDepartL = lhs.strDepart.GetLength() ? 1 : 0;
		BOOL bDepartR = rhs.strDepart.GetLength() ? 1 : 0;
		BOOL bNameL = lhs.strName.GetLength() ? 1 : 0;
		BOOL bNameR = rhs.strName.GetLength() ? 1 : 0;

		COMPARE_KEY_BEGIN_LESS(lhs.nPos, rhs.nPos)
		COMPARE_KEY_BEGIN_LESS(lhs.nLen, rhs.nLen)
		COMPARE_KEY_BEGIN_LESS(lhs.pData->nUseExpiredDay, rhs.pData->nUseExpiredDay)
		COMPARE_KEY_BEGIN(lhs.pData->nUseCount, rhs.pData->nUseCount)
		COMPARE_KEY_BEGIN_LESS(lhs.pData->nCNo, rhs.pData->nCNo)
		COMPARE_KEY_BEGIN(lhs.nMainPhone, rhs.nMainPhone)
		COMPARE_KEY_BEGIN_LESS(lhs.nPhoneExpiredDay, rhs.nPhoneExpiredDay)
		COMPARE_KEY_BEGIN(bDepartL, bDepartR)
		COMPARE_KEY_BEGIN_LESS(lhs.strDepart, rhs.strDepart)
		COMPARE_KEY_BEGIN(bNameL, bNameR)
		COMPARE_KEY_FINAL_LESS(lhs.strName, rhs.strName)
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		return FALSE;
	}
};



//ㄱㄴ순 정렬
class SearchCustomerCompareABC
{ 
public:
	bool operator() (SEARCH_CUS_DATA& lhs, SEARCH_CUS_DATA& rhs) const
	{
		COMPARE_KEY_BEGIN_LESS(lhs.nPos, rhs.nPos)
		COMPARE_KEY_BEGIN_LESS(lhs.nLen, rhs.nLen)
		COMPARE_KEY_BEGIN_LESS(lhs.GetSortCompany(), rhs.GetSortCompany())
		COMPARE_KEY_BEGIN_LESS(lhs.strDepart, rhs.strDepart)
		COMPARE_KEY_BEGIN_LESS(lhs.strName, rhs.strName)
		COMPARE_KEY_BEGIN_LESS(lhs.pData->nUseExpiredDay, rhs.pData->nUseExpiredDay)
		COMPARE_KEY_BEGIN(lhs.pData->nUseCount, rhs.pData->nUseCount)
		COMPARE_KEY_BEGIN_LESS(lhs.pData->nCNo, rhs.pData->nCNo)
		COMPARE_KEY_BEGIN(lhs.nMainPhone, rhs.nMainPhone)
		COMPARE_KEY_BEGIN_LESS(lhs.nPhoneExpiredDay, rhs.nPhoneExpiredDay)
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		return FALSE;
	}
};



#pragma pack(pop)