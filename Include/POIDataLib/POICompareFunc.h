#pragma once


#include "POIBoundary.h"
#include <functional>		//sort
#define SHORT_LI_TYPE			13


template<typename T>
class AFX_EXT_CLASS PairKeyCompare { 
public:
	bool operator() (const T& lhs, const T& rhs) const
	{
		return keyLess(lhs.first, rhs.first);
	}

	bool operator() (const T& lhs, const UINT& k) const
	{
		return keyLess(lhs.first, k);
	}

	bool operator() (const UINT& k, const T& rhs) const
	{
		return keyLess(k, rhs.first);
	}

private:
	inline bool keyLess(const UINT& k1, const UINT& k2) const
	{
		return k1 < k2;
	}
};


class AFX_EXT_CLASS POIKeyCompare { 
public:
	bool operator() (const CPOIUnit& lhs, const CPOIUnit& rhs) const
	{
		return keyLess(lhs.m_nID, rhs.m_nID);
	}

	bool operator() (const CPOIUnit& lhs, const UINT& k) const
	{
		return keyLess(lhs.m_nID, k);
	}

	bool operator() (const UINT& k, const CPOIUnit& rhs) const
	{
		return keyLess(k, rhs.m_nID);
	}

private:
	inline bool keyLess(const UINT& k1, const UINT& k2) const
	{
		return k1 < k2;
	}

};

class AFX_EXT_CLASS PartPOIKeyCompare { 
public:
	bool operator() (const PART_POI_INFO& lhs, const PART_POI_INFO& rhs) const
	{
		return keyLess(lhs.nIndex, rhs.nIndex);
	}

	bool operator() (const PART_POI_INFO& lhs, const UINT& k) const
	{
		return keyLess(lhs.nIndex, k);
	}

	bool operator() (const UINT& k, const PART_POI_INFO& rhs) const
	{
		return keyLess(k, rhs.nIndex);
	}

private:
	inline bool keyLess(const UINT& k1, const UINT& k2) const
	{
		return k1 < k2;
	}
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



class SearchDataCompare 
{ 
public:
	bool operator() (const SEARCH_POI_PAIR& lhs, const SEARCH_POI_PAIR& rhs) const
	{
		return keyLess(lhs.second, rhs.second);
	}

	bool operator() (const SEARCH_POI_PAIR& lhs, const SEARCH_POI_PAIR::second_type& k) const
	{
		return keyLess(lhs.second, k);
	}

	bool operator() (const SEARCH_POI_PAIR::second_type& k, const SEARCH_POI_PAIR& rhs) const
	{
		return keyLess(k, rhs.second);
	}

private:
	inline bool keyLess(const SEARCH_POI_PAIR::second_type& k1, const SEARCH_POI_PAIR::second_type& k2) const
	{
		COMPARE_KEY_BEGIN(k1.bFullMatch, k2.bFullMatch)
		COMPARE_KEY_BEGIN(k1.bHasBasePOI, k2.bHasBasePOI)
		COMPARE_KEY_BEGIN(k1.bBasePOI, k2.bBasePOI)
		COMPARE_KEY_BEGIN(k1.nKeywordPos, k2.nKeywordPos)
		COMPARE_KEY_BEGIN(k1.nDataPos, k2.nDataPos)
		COMPARE_KEY_BEGIN(k1.pPOI->m_nPriority, k2.pPOI->m_nPriority)
		COMPARE_KEY_BEGIN_LESS(k1.nFullLen, k2.nFullLen)
		COMPARE_KEY_BEGIN_LESS(k1.nCenterPosAwayMeter, k2.nCenterPosAwayMeter)
		COMPARE_KEY_BEGIN(k1.dDongAdvantagePoint, k2.dDongAdvantagePoint)
		COMPARE_KEY_BEGIN(k1.nLen + (BYTE)k1.bDongNearPOI, k2.nLen + (BYTE)k2.bDongNearPOI)
		COMPARE_KEY_BEGIN_LESS(k1.bPOISepSecond, k2.bPOISepSecond)
		COMPARE_KEY_BEGIN(k1.pPOI->IsMobilePOI(), k2.pPOI->IsMobilePOI())
		COMPARE_KEY_BEGIN_LESS(k1.nBasePOIAwayMeter, k2.nBasePOIAwayMeter)
		long nNearDistance1 = k1.pNearPOI ? k1.nNearDistance : 0xFFFF;
		long nNearDistance2 = k2.pNearPOI ? k2.nNearDistance : 0xFFFF;
		COMPARE_KEY_FINAL_LESS(nNearDistance1, nNearDistance2)
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
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()

		//g_bana_log->Print("%s %s : RETURN FALSE\n", k1.pPOI->GetPOIName(), k2.pPOI->GetPOIName());
		return FALSE;
	}
};


class SearchDongDataCompare 
{ 
public:
	bool operator() (const SEARCH_POI_PAIR& lhs, const SEARCH_POI_PAIR& rhs) const
	{
		return keyLess(lhs.second, rhs.second);
	}

	bool operator() (const SEARCH_POI_PAIR& lhs, const SEARCH_POI_PAIR::second_type& k) const
	{
		return keyLess(lhs.second, k);
	}

	bool operator() (const SEARCH_POI_PAIR::second_type& k, const SEARCH_POI_PAIR& rhs) const
	{
		return keyLess(k, rhs.second);
	}

private:
	inline bool keyLess(const SEARCH_POI_PAIR::second_type& k1, const SEARCH_POI_PAIR::second_type& k2) const
	{
		BOOL bLi1 = k1.pPOI->IsLiPOI() && k1.nDongMatchType == SHORT_LI_TYPE;
		BOOL bLi2 = k2.pPOI->IsLiPOI() && k2.nDongMatchType == SHORT_LI_TYPE;

		COMPARE_KEY_BEGIN_LESS(bLi1, bLi2)
		COMPARE_KEY_BEGIN(k1.nLen, k2.nLen)
		COMPARE_KEY_BEGIN(k1.nKeywordPos, k2.nKeywordPos)
		COMPARE_KEY_BEGIN(k1.nDataPos, k2.nDataPos)
		COMPARE_KEY_FINAL_LESS(k1.nCenterPosAwayMeter, k2.nCenterPosAwayMeter)
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()

		return FALSE;
	}
};


class SearchDongDataCompareDongPriority
{ 
public:
	bool operator() (const SEARCH_POI_PAIR& lhs, const SEARCH_POI_PAIR& rhs) const
	{
		return keyLess(lhs.second, rhs.second);
	}

	bool operator() (const SEARCH_POI_PAIR& lhs, const SEARCH_POI_PAIR::second_type& k) const
	{
		return keyLess(lhs.second, k);
	}

	bool operator() (const SEARCH_POI_PAIR::second_type& k, const SEARCH_POI_PAIR& rhs) const
	{
		return keyLess(k, rhs.second);
	}

private:
	inline bool keyLess(const SEARCH_POI_PAIR::second_type& k1, const SEARCH_POI_PAIR::second_type& k2) const
	{
		BOOL bLi1 = k1.pPOI->IsLiPOI() && k1.nDongMatchType == SHORT_LI_TYPE;
		BOOL bLi2 = k2.pPOI->IsLiPOI() && k2.nDongMatchType == SHORT_LI_TYPE;

		BOOL bDong1 = k1.pPOI->m_nClass <= PN_SAME_NAME_DONG;
		BOOL bDong2 = k2.pPOI->m_nClass <= PN_SAME_NAME_DONG;


		//g_bana_log->Print("%s : %s, %d:%d, %d:%d, %d:%d, %d:%d, %d:%d\n", 
		//				k1.pPOI->GetRegionName(),
		//				k2.pPOI->GetRegionName(),
		//				k1.nLen, k2.nLen, 
		//				k1.nKeywordPos, k2.nKeywordPos, 
		//				k1.nDataPos, k2.nDataPos, 
		//				k1.nCenterPosAwayMeter, k2.nCenterPosAwayMeter,
		//				bDong1, bDong2);

		//by mksong (2014-06-26 오전 1:31)
		//안산이 안산동보다 먼저 나오게 SORT를 변경하였다, 아래는 이전 세팅
		//COMPARE_KEY_BEGIN_LESS(bLi1, bLi2)
		//COMPARE_KEY_BEGIN(k1.nLen, k2.nLen)
		//COMPARE_KEY_BEGIN(k1.nKeywordPos, k2.nKeywordPos)
		//COMPARE_KEY_BEGIN(k1.nDataPos, k2.nDataPos)
		//COMPARE_KEY_BEGIN(k1.nCenterPosAwayMeter, k2.nCenterPosAwayMeter)
		//COMPARE_KEY_FINAL(bDong1, bDong2)
		//COMPARE_KEY_END()
		//COMPARE_KEY_END()
		//COMPARE_KEY_END()
		//COMPARE_KEY_END()
		//COMPARE_KEY_END()


		COMPARE_KEY_BEGIN_LESS(bLi1, bLi2)
		COMPARE_KEY_BEGIN(k1.nLen, k2.nLen)
		COMPARE_KEY_BEGIN(k1.nKeywordPos, k2.nKeywordPos)
		COMPARE_KEY_BEGIN(k1.nDataPos, k2.nDataPos)
		COMPARE_KEY_BEGIN_LESS(bDong1, bDong2)
		COMPARE_KEY_FINAL_LESS(k1.nCenterPosAwayMeter, k2.nCenterPosAwayMeter)
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()

		return FALSE;
	}
};



class SearchDongKeyCompare { 
public:
	bool operator() (const SEARCH_DONG& lhs, const SEARCH_DONG& rhs) const
	{
		return keyLess(lhs.wszKeyword[0], rhs.wszKeyword[0]);
	}

	bool operator() (const SEARCH_DONG& lhs, const WCHAR &k) const
	{
		return keyLess(lhs.wszKeyword[0], k);
	}

	bool operator() (const WCHAR &k, const SEARCH_DONG& rhs) const
	{
		return keyLess(k, rhs.wszKeyword[0]);
	}

private:
	inline bool keyLess(const WCHAR &k1, const WCHAR &k2) const
	{
		return wcscmp(&k1, &k2) < 0;
	}
};



class PhoneIndexCompare { 
public:
	bool operator() (const PHONE_INDEX& lhs, const PHONE_INDEX& rhs) const
	{
		return keyLess(lhs.nPhone, rhs.nPhone);
	}

	bool operator() (const PHONE_INDEX& lhs, const UINT& k) const
	{
		return keyLess(lhs.nPhone, k);
	}

	bool operator() (const UINT& k, const PHONE_INDEX& rhs) const
	{
		return keyLess(k, rhs.nPhone);
	}

private:
	inline bool keyLess(const UINT& k1, const UINT& k2) const
	{
		return k1 < k2;
	}
};



class POIIDIndexCompare { 
public:
	bool operator() (const POIID_INDEX& lhs, const POIID_INDEX& rhs) const
	{
		return keyLess(lhs.nPOIID, rhs.nPOIID);
	}

	bool operator() (const POIID_INDEX& lhs, const UINT& k) const
	{
		return keyLess(lhs.nPOIID, k);
	}

	bool operator() (const long& k, const POIID_INDEX& rhs) const
	{
		return keyLess(k, rhs.nPOIID);
	}

private:
	inline bool keyLess(const long& k1, const long& k2) const
	{
		return k1 < k2;
	}
};

struct PPOITempRemove: public binary_function <pair<UINT, CPOIUnit*>, UINT, bool>
{
	bool operator() (const pair<UINT, CPOIUnit*> &poipair, const UINT &poiRemove) const
	{
		return (UINT)poipair.second == poiRemove;
	}
};

struct PPOITempRemoveGroup: public binary_function <pair<UINT, CPOIUnit*>, UINT, bool>
{
	bool operator() (const pair<UINT, CPOIUnit*> &poipair, const UINT &nGroupID) const
	{
		return poipair.first == nGroupID;
	}
};


struct PPOIDeleteNotMainSidoDong: public binary_function <SEARCH_POI_PAIR, CPOIBoundary, bool>
{
	bool operator() (const SEARCH_POI_PAIR &poipair, const CPOIBoundary &pSearchSido) const
	{
		return ((CPOIBoundary)pSearchSido).Has(poipair.second.pPOI) == FALSE;
	}
};


template<typename InputIterator, 
typename OutputIterator, 
typename Predicate>
OutputIterator copy_if(InputIterator begin, 
					   InputIterator end,
					   OutputIterator destBegin, 
					   Predicate p)
{
	while(begin != end) {
		if(p(*begin)) *destBegin++ = *begin;
		++begin;
	}
	return destBegin;
}

template<typename InputIterator, 
typename OutputIterator, 
typename Predicate,
typename PARAM>
OutputIterator copy_if2(InputIterator begin, 
						InputIterator end,
						OutputIterator destBegin, 
						Predicate p,
						PARAM &q)
{
	while(begin != end) {
		if(p(*begin, q)) *destBegin++ = *begin;
		++begin;
	}
	return destBegin;
}

template<typename InputIterator, 
typename OutputIterator, 
typename Predicate,
typename PARAM1,
typename PARAM2>
OutputIterator copy_if3(InputIterator begin, 
						InputIterator end,
						OutputIterator destBegin, 
						Predicate p,
						PARAM1 &q,
						PARAM2 &r)
{
	while(begin != end) {
		if(p(*begin, q, r)) *destBegin++ = *begin;
		++begin;
	}
	return destBegin;
}

template<typename InputIterator, 
typename OutputIterator, 
typename Predicate,
typename PARAM1,
typename PARAM2,
typename PARAM3>
OutputIterator copy_if4(InputIterator begin, 
						InputIterator end,
						OutputIterator destBegin, 
						Predicate p,
						PARAM1 &q,
						PARAM2 &r,
						PARAM3 &s)
{
	while(begin != end) {
		if(p(*begin, q, r, s)) *destBegin++ = *begin;
		++begin;
	}
	return destBegin;
}


class SearchDataCompareSimple
{ 
public:
	bool operator() (const SEARCH_POI_PAIR& lhs, const SEARCH_POI_PAIR& rhs) const
	{
		return keyLess(lhs.second, rhs.second);
	}

	bool operator() (const SEARCH_POI_PAIR& lhs, const SEARCH_POI_PAIR::second_type& k) const
	{
		return keyLess(lhs.second, k);
	}

	bool operator() (const SEARCH_POI_PAIR::second_type& k, const SEARCH_POI_PAIR& rhs) const
	{
		return keyLess(k, rhs.second);
	}

private:
	inline bool keyLess(const SEARCH_POI_PAIR::second_type& k1, const SEARCH_POI_PAIR::second_type& k2) const
	{
		int nTopID1 = k1.pPOI->GetTopPOI()->GetID();
		int nTopID2 = k2.pPOI->GetTopPOI()->GetID();
		
		COMPARE_KEY_BEGIN(k1.nKeywordPos, k2.nKeywordPos)
		COMPARE_KEY_BEGIN(k1.nDataPos, k2.nDataPos)
		COMPARE_KEY_BEGIN_LESS(k1.nFullLen, k2.nFullLen)
		COMPARE_KEY_BEGIN(k1.nLen, k2.nLen)
		COMPARE_KEY_BEGIN(nTopID1, nTopID2)
		COMPARE_KEY_FINAL(k1.pPOI->GetID(), k2.pPOI->GetID())
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()
		COMPARE_KEY_END()

		return FALSE;
	}
};


