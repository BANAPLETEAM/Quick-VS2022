
#include "stdafx.h"
#include "poidata.h"
#include "math.h"

#define UNIQUE_OFFSET	10000
#define MATCH_PASS_RATE	60


/*
char *szKeyword[] = {"SK주유소", "GS주유소", "오일뱅크", "에쓰오일",
				"롯데리아", "버거킹", "KFC", "파파이스", "맥도날드",
				"도미노피자", "미스터피자", "프레스코", "피자헛",
				"신세계백화점", "롯데백화점", "갤러리아백화점", "애경백화점", "현대백화점", "그랜드백화점", "프라이비트",
				"GS마트", "세이브존", "월마트", "그랜드마트", "이마트", "까르푸", "코스트코",
				"롯데마트", "홈플러스", "삼성디지털프라자", "하이마트",
				"바이더웨이", "세븐일레븐", "GS25", "미니스톱", "훼미리마트", 
				"CGV", "메가박스", "롯데시네마", "메가라인", "씨너스", "프리머스시네마", //42
				"우체국",																	//43
				"삼성아파트", "대림아파트", "현대아파트", "주공아파트"};				//47

long nKeywordSize = 47;
*/

char *szLargeName[] = {"현대", "LG", "삼성", "농협", "한국", "기아", "새마을", "SK", "제일", "서울", 
					"중앙", "엘지", "우리", "대한", "국민", "에쓰오일", "하나", "GM", "대성", "동양",
					"부산", "쌍용", "그린서비스", "그린", "주공", "금호", "KTF", "신용", "세븐", "훼미리마트",
					"대우", "대구", "동부", "휴게소", "헤어", "일레븐", "미술", "고등학교", "충전소", "정형외과", 
					"경로당", "노래방", "노래", "어린이집", "소아과", "파크", "이비인후과", "천주", "성당", "치안센터", 
					"저수지", "어린이", "산부인과", "예식장", "피아노", "컴퓨터", "xx대학교", "웨딩홀", "수퍼", "횟집",
					"목욕탕", "화재", "마을", "생명", "사우나", "창고", "내과", "회관", "주차장", "유치원", 
					"치킨", "산업", "중학교", "금고", "우체국", "보건", "학원", "의원", "마트", "카센터", 
					"카센타", "파출소", "빌딩", "종합", "텔레콤", "식당", "숯불", "가든", "xxx카", "전자", 
					"한의원", "사무소", "치과", "여관", "모텔", "초교", "초등학교", "마을회관", "약국", "은행", 
					"주유소", "자동차", "교회", "아파트"};


double m_dMeterPerLattM = 1848.5;	//M = minute
double m_dMeterPerLongM = 1478.1;	//M = minute

enum { POI_SAME_NAME_DONG = 3, POI_GUGUN = 5, POI_SIDO = 10};


bool POI_greator(POI_MATCH_DATA *elem1, POI_MATCH_DATA *elem2)
{
	BOOL bComp1 = elem1->nMatchPoint > elem2->nMatchPoint;
	BOOL bSame1 = elem1->nMatchPoint == elem2->nMatchPoint;
	//BOOL bComp2 = elem1->pPOI->szGroup[0] > elem2->pPOI->szGroup[0];
	//BOOL bSame2 = elem1->pPOI->szGroup[0] == elem2->pPOI->szGroup[0];
	//BOOL bComp3 = elem1->pPOI->szGroup[1] > elem2->pPOI->szGroup[1];
	//BOOL bSame3 = elem1->pPOI->szGroup[1] == elem2->pPOI->szGroup[1];
	BOOL bComp2 = FALSE;
	BOOL bSame2 = TRUE;
	BOOL bComp3 = FALSE;
	BOOL bSame3 = TRUE;
	BOOL bComp4 = elem1->nDongMatchWordSize > elem2->nDongMatchWordSize;	//union 이라서 dongmatch로 넣어도 된다.
	BOOL bSame4 = elem1->nDongMatchWordSize == elem2->nDongMatchWordSize;
	BOOL bComp5 = elem1->pPOI->nClass < elem2->pPOI->nClass;
	BOOL bSame5 = elem1->pPOI->nClass == elem2->pPOI->nClass;
	BOOL bComp6 = elem1->pPOI->nBoundaryLevel < elem2->pPOI->nBoundaryLevel;
	BOOL bSame6 = elem1->pPOI->nBoundaryLevel == elem2->pPOI->nBoundaryLevel;
	BOOL bComp7 = elem1->pPOI->dKMFromCenter < elem2->pPOI->dKMFromCenter;

	return bComp1 || (bSame1 && bComp2) || 
			(bSame1 && bSame2 && bComp3) ||
			(bSame1 && bSame2 && bSame3 && bComp4) ||
			(bSame1 && bSame2 && bSame3 && bSame4 && bComp5) ||
			(bSame1 && bSame2 && bSame3 && bSame4 && bSame5 && bComp6) ||
			(bSame1 && bSame2 && bSame3 && bSame4 && bSame5 && bSame6 && bComp7); 
}


CPOIData::CPOIData(void)
{
	for(int i = 0; i < 104; i++) {
		m_poiLargeData.insert(POI_LARGE_DATA::value_type(szLargeName[i], szLargeName[i]));
	}

	m_nMatchPassRate = MATCH_PASS_RATE;
}

CPOIData::~CPOIData(void)
{
	POI_DATA_MAP::iterator iter;
	POI_DATA_DEPTH_MAP::iterator iterDepth;

	for(iter = m_poiDong.begin(); iter != m_poiDong.end(); iter++) {
		if((*iter).second)
			delete (POI_DATA*)(*iter).second;
	}

	for(iterDepth = m_poiName.begin(); iterDepth != m_poiName.end(); iterDepth++) {
		if((*iterDepth).second->nDepth == 1)
		{
			delete (*iterDepth).second->pData;
			(*iterDepth).second->pData = NULL;
		}
	
		delete (*iterDepth).second;
	}


	m_poiDong.clear();
	m_poiName.clear();
}

void CPOIData::SetCenterPos(long x, long y, long nID)
{
	m_dCenterPosX[nID] = x / 1000000.0;
	m_dCenterPosY[nID] = y / 1000000.0;
}


void CPOIData::Insert(POI_DATA *pPOI, long nID)
{
	pPOI->dKMFromCenter = GetDistanceKMeter(pPOI->dPosX, pPOI->dPosY, nID);

	if(pPOI->dKMFromCenter <= m_ci.m_bound.nBoundary1 || pPOI->nClass > 3) {
		pPOI->nBoundaryLevel = 1;
	}
	else {
		if(pPOI->dKMFromCenter <= m_ci.m_bound.nBoundary2) {
			pPOI->nBoundaryLevel = 2;
		}
		else {
			if(pPOI->dKMFromCenter <= m_ci.m_bound.nBoundary3) {
				pPOI->nBoundaryLevel = 3;
			}
			else {
				pPOI->nBoundaryLevel = 4;
			}
		}
	}


	if(pPOI->nUID == 0) {
		CString strPOIName = pPOI->szDong;

		if(pPOI->nClass == POI_SIDO) {
			if(strPOIName.Right(2) == "구" || strPOIName.Right(2) == "군")
				pPOI->nClass = POI_GUGUN;
		}

		if(strPOIName.GetLength() > 5 && pPOI->nClass != POI_SAME_NAME_DONG)
		{
			CString strRight = strPOIName.Right(2);
			if(pPOI->nClass == 0 && 
				strRight != "동" &&
				strRight != "면" &&
				strRight != "읍" &&
				strRight != "가")
			{
				//skip				
			}
			else
			{
				strPOIName.Delete(strPOIName.GetLength() - 2, 2);
			}
		}

		if(pPOI->nClass == POI_SAME_NAME_DONG)
			pPOI->nClass = 0;


		pPOI->pDong = pPOI;
		pPOI->bDongData = TRUE;

		m_poiDong.insert(POI_DATA_MAP::value_type((LPSTR)(LPCTSTR)strPOIName, pPOI));

		if(pPOI->nClass != POI_SAME_NAME_DONG  && pPOI->nBoundaryLevel <= 1)
			m_poiDongNear.insert(POI_DATA_MAP::value_type((LPSTR)(LPCTSTR)strPOIName, pPOI));

		m_poiDongID.insert(POI_DATA_ID_MAP::value_type(pPOI->nID, pPOI));
	}
	else {
		if(nID > 0)	//콜센터 중심이 2개인 경우에
			pPOI->nBoundaryLevel = 1;


		if(pPOI->nBoundaryLevel > 1)
		{
			delete pPOI;
			return;
		}

		if(pPOI->nFCnt > 0) {
			POI_DATA_DEPTH *poiDepth = new POI_DATA_DEPTH;
			poiDepth->pData = pPOI;
			poiDepth->nDepth = 0;
			m_poiName.insert(POI_DATA_DEPTH_MAP::value_type(pPOI->F1, poiDepth));
		}
		if(pPOI->nFCnt > 1) {
			POI_DATA_DEPTH *poiDepth = new POI_DATA_DEPTH;
			poiDepth->pData = pPOI;
			poiDepth->nDepth = 1;
			m_poiName.insert(POI_DATA_DEPTH_MAP::value_type(pPOI->F2, poiDepth));
		}
		if(pPOI->nFCnt > 2) {
			POI_DATA_DEPTH *poiDepth = new POI_DATA_DEPTH;
			poiDepth->pData = pPOI;
			poiDepth->nDepth = 2;
			m_poiName.insert(POI_DATA_DEPTH_MAP::value_type(pPOI->F3, poiDepth));
		}
		if(pPOI->nFCnt > 3) {
			POI_DATA_DEPTH *poiDepth = new POI_DATA_DEPTH;
			poiDepth->pData = pPOI;
			poiDepth->nDepth = 3;
			m_poiName.insert(POI_DATA_DEPTH_MAP::value_type(pPOI->F4, poiDepth));
		}
		if(pPOI->nFCnt > 4) {
			POI_DATA_DEPTH *poiDepth = new POI_DATA_DEPTH;
			poiDepth->pData = pPOI;
			poiDepth->nDepth = 4;
			m_poiName.insert(POI_DATA_DEPTH_MAP::value_type(pPOI->F5, poiDepth));
		}
	}
}


void CPOIData::Insert2(POI_DATA *pPOI)
{
	if(pPOI->dKMFromCenter <= m_ci.m_bound.nBoundary1 || pPOI->nClass > 3) {
		pPOI->nBoundaryLevel = 1;
	}
	else {
		if(pPOI->dKMFromCenter <= m_ci.m_bound.nBoundary2) {
			pPOI->nBoundaryLevel = 2;
		}
		else {
			if(pPOI->dKMFromCenter <= m_ci.m_bound.nBoundary3) {
				pPOI->nBoundaryLevel = 3;
			}
			else {
				pPOI->nBoundaryLevel = 4;
			}
		}
	}


	if(pPOI->nUID == 0) {
		CString strPOIName = pPOI->szDong;

		if(pPOI->nClass == POI_SIDO) {
			if(strPOIName.Right(2) == "구" || strPOIName.Right(2) == "군")
				pPOI->nClass = POI_GUGUN;
		}

		if(strPOIName.GetLength() > 5 && pPOI->nClass != POI_SAME_NAME_DONG)
		{
			CString strRight = strPOIName.Right(2);
			if(pPOI->nClass == 0 && 
				strRight != "동" &&
				strRight != "면" &&
				strRight != "읍" &&
				strRight != "가")
			{
				//skip				
			}
			else
			{
				strPOIName.Delete(strPOIName.GetLength() - 2, 2);
			}
		}

		if(pPOI->nClass == POI_SAME_NAME_DONG)
			pPOI->nClass = 0;


		pPOI->pDong = pPOI;
		pPOI->bDongData = TRUE;

		m_poiDong.insert(POI_DATA_MAP::value_type((LPSTR)(LPCTSTR)strPOIName, pPOI));
		if(pPOI->nClass == 0 && pPOI->nBoundaryLevel <= 1)
			m_poiDongNear.insert(POI_DATA_MAP::value_type((LPSTR)(LPCTSTR)strPOIName, pPOI));

		m_poiDongID.insert(POI_DATA_ID_MAP::value_type(pPOI->nID, pPOI));
	}
	else {
		if(pPOI->nFCnt > 0) {
			POI_DATA_DEPTH *poiDepth = new POI_DATA_DEPTH;
			poiDepth->pData = pPOI;
			poiDepth->nDepth = 0;
			m_poiName.insert(POI_DATA_DEPTH_MAP::value_type(pPOI->F1, poiDepth));
		}
		if(pPOI->nFCnt > 1) {
			POI_DATA_DEPTH *poiDepth = new POI_DATA_DEPTH;
			poiDepth->pData = pPOI;
			poiDepth->nDepth = 1;
			m_poiName.insert(POI_DATA_DEPTH_MAP::value_type(pPOI->F2, poiDepth));
		}
		if(pPOI->nFCnt > 2) {
			POI_DATA_DEPTH *poiDepth = new POI_DATA_DEPTH;
			poiDepth->pData = pPOI;
			poiDepth->nDepth = 2;
			m_poiName.insert(POI_DATA_DEPTH_MAP::value_type(pPOI->F3, poiDepth));
		}
		if(pPOI->nFCnt > 3) {
			POI_DATA_DEPTH *poiDepth = new POI_DATA_DEPTH;
			poiDepth->pData = pPOI;
			poiDepth->nDepth = 3;
			m_poiName.insert(POI_DATA_DEPTH_MAP::value_type(pPOI->F4, poiDepth));
		}
		if(pPOI->nFCnt > 4) {
			POI_DATA_DEPTH *poiDepth = new POI_DATA_DEPTH;
			poiDepth->pData = pPOI;
			poiDepth->nDepth = 4;
			m_poiName.insert(POI_DATA_DEPTH_MAP::value_type(pPOI->F5, poiDepth));
		}
	}
}




void CPOIData::Insert3(POI_DATA *pPOI)
{
	if(pPOI->nFCnt > 0) {
		POI_DATA_DEPTH *poiDepth = new POI_DATA_DEPTH;
		poiDepth->pData = pPOI;
		poiDepth->nDepth = 0;
		m_poiName.insert(POI_DATA_DEPTH_MAP::value_type(pPOI->F1, poiDepth));
	}
	if(pPOI->nFCnt > 1) {
		POI_DATA_DEPTH *poiDepth = new POI_DATA_DEPTH;
		poiDepth->pData = pPOI;
		poiDepth->nDepth = 1;
		m_poiName.insert(POI_DATA_DEPTH_MAP::value_type(pPOI->F2, poiDepth));
	}
	if(pPOI->nFCnt > 2) {
		POI_DATA_DEPTH *poiDepth = new POI_DATA_DEPTH;
		poiDepth->pData = pPOI;
		poiDepth->nDepth = 2;
		m_poiName.insert(POI_DATA_DEPTH_MAP::value_type(pPOI->F3, poiDepth));
	}
	if(pPOI->nFCnt > 3) {
		POI_DATA_DEPTH *poiDepth = new POI_DATA_DEPTH;
		poiDepth->pData = pPOI;
		poiDepth->nDepth = 3;
		m_poiName.insert(POI_DATA_DEPTH_MAP::value_type(pPOI->F4, poiDepth));
	}
	if(pPOI->nFCnt > 4) {
		POI_DATA_DEPTH *poiDepth = new POI_DATA_DEPTH;
		poiDepth->pData = pPOI;
		poiDepth->nDepth = 4;
		m_poiName.insert(POI_DATA_DEPTH_MAP::value_type(pPOI->F5, poiDepth));
	}
}

void CPOIData::InsertDong(POI_DATA *pPOI)
{
	BOOL bUpdate = FALSE;
	POI_DATA_ID_MAP::iterator iterDong;

	if(pPOI->dKMFromCenter <= m_ci.m_bound.nBoundary1 || pPOI->nClass > 3) {
		pPOI->nBoundaryLevel = 1;
	}
	else {
		if(pPOI->dKMFromCenter <= m_ci.m_bound.nBoundary2) {
			pPOI->nBoundaryLevel = 2;
		}
		else {
			if(pPOI->dKMFromCenter <= m_ci.m_bound.nBoundary3) {
				pPOI->nBoundaryLevel = 3;
			}
			else {
				pPOI->nBoundaryLevel = 4;
			}
		}
	}

	iterDong = m_poiDongID.find(pPOI->nID);
	if(iterDong != m_poiDongID.end())
	{
		if(pPOI->dKMFromCenter < (*iterDong).second->dKMFromCenter)
		{
			(*iterDong).second->dKMFromCenter = pPOI->dKMFromCenter;
			(*iterDong).second->nBoundaryLevel = pPOI->nBoundaryLevel;
		}
	
		return;
	}

	CString strPOIName = pPOI->szDong;

	if(pPOI->nClass == POI_SIDO) {
		if(strPOIName.Right(2) == "구" || strPOIName.Right(2) == "군")
			pPOI->nClass = POI_GUGUN;
	}

	if(strPOIName.GetLength() > 5 && pPOI->nClass != POI_SAME_NAME_DONG)
	{
		CString strRight = strPOIName.Right(2);
		if(pPOI->nClass == 0 && 
			strRight != "동" &&
			strRight != "면" &&
			strRight != "읍" &&
			strRight != "가")
		{
			//skip				
		}
		else
		{
			strPOIName.Delete(strPOIName.GetLength() - 2, 2);
		}
	}

	if(pPOI->nClass == POI_SAME_NAME_DONG)
		pPOI->nClass = 0;


	pPOI->pDong = pPOI;
	pPOI->bDongData = TRUE;


	m_poiDong.insert(POI_DATA_MAP::value_type((LPSTR)(LPCTSTR)strPOIName, pPOI));
	if(pPOI->nClass == 0 && pPOI->nBoundaryLevel <= 1)
		m_poiDongNear.insert(POI_DATA_MAP::value_type((LPSTR)(LPCTSTR)strPOIName, pPOI));

	m_poiDongID.insert(POI_DATA_ID_MAP::value_type(pPOI->nID, pPOI));

	CString strSido = pPOI->szSido;
	CString strGugun = pPOI->szGugun;
	CString strGugun2 = pPOI->szGugun2;
	CString strDong = pPOI->szDong;

	strGugun.Delete(strGugun.GetLength() - 2, 2);
	if(strGugun2.GetLength() > 2)
		strGugun2.Delete(strGugun2.GetLength() - 2, 2);
	strDong.Delete(strDong.GetLength() - 2, 2);

	CString strLong = strSido + "-" + strGugun + "-" + 
		(strGugun2.GetLength() > 0 ? strGugun2 + "-": "") + 
		strDong;

	//g_bana_log->Print("strLong = %s\n", strLong);

	m_poiDongSearch.insert(POI_DATA_MAP::value_type((LPSTR)(LPCTSTR)strLong, pPOI));

}



void CPOIData::MakeJoinPOINameToDong()
{
	POI_DATA_DEPTH_MAP::iterator iter;
	POI_DATA_ID_MAP::iterator iterDong;

	for(iter = m_poiName.begin(); iter != m_poiName.end(); iter++) {
		iterDong = m_poiDongID.find(iter->second->pData->nID);
		if(iterDong != m_poiDongID.end())
			iter->second->pData->pDong = iterDong->second;
		else
		{
			g_bana_log->Print("dong join failed: UID=%d,nDongID=%d, %s %s %s %s %s\n", iter->second->pData->nUID, 
				iter->second->pData->nID,
				iter->second->pData->F1,
				iter->second->pData->F2,
				iter->second->pData->F3,
				iter->second->pData->F4,
				iter->second->pData->F5);

			iter->second->pData->pDong = NULL;
		}
	}
}

void CPOIData::MakeDongParent()
{
	POI_DATA_MAP::iterator iter;	
	POI_DATA_ID_MAP::iterator iterDong;

	for(iter = m_poiDong.begin(); iter != m_poiDong.end(); iter++) {
		long nParentID = (long)iter->second->pParent;

        iterDong = m_poiDongID.find(nParentID);
		if(iterDong != m_poiDongID.end())
			iter->second->pParent = iterDong->second;
		else
			iter->second->pParent = NULL;
	}
}


POI_DATA* CPOIData::FindDataFromID(long nUniqueID)
{
	if(nUniqueID > UNIQUE_OFFSET)	//POIName데이터
	{
		//이부분도 속도가 너무 느리다.
		POI_DATA_DEPTH_MAP::iterator iter;

//		nUniqueID -= UNIQUE_OFFSET;
		for(iter = m_poiName.begin(); iter != m_poiName.end(); iter++) {
			if(iter->second->pData->nUID == nUniqueID)
				return iter->second->pData;
		}
	}
	else
	{
		POI_DATA_ID_MAP::iterator iter;
		iter = m_poiDongID.find(nUniqueID);

		if(iter != m_poiDongID.end())
			return iter->second;

/*
		POI_DATA_MAP::iterator iter;
		for(iter = m_poiDong.begin(); iter != m_poiDong.end(); iter++) {
			if(iter->second->nID == nUniqueID && iter->second->nUID == 0)
				return iter->second;
		}
*/
	}

	return NULL;
}

void CPOIData::DeleteFromID(long nID)
{
	if(nID > UNIQUE_OFFSET)	//POIName데이터
	{
		POI_DATA_DEPTH_MAP::iterator iter;
		POI_DATA *pPOI = NULL;

		for(iter = m_poiName.begin(); iter != m_poiName.end();) {
			if(iter->second->pData->nUID == nID)
			{
				pPOI = iter->second->pData;
				iter = m_poiName.erase(iter);
				continue;
			}
			iter++;
		}

		if(pPOI)
		{
			delete pPOI;
			pPOI = NULL;
		}

	}

}

long CPOIData::GetUniqueID(POI_DATA *pPOI)
{
	if(pPOI->nUID == 0)
		return pPOI->nID;
	else
//		return pPOI->nUID + UNIQUE_OFFSET;
		return pPOI->nUID;
}


BOOL CPOIData::SearchDongDataNew(CString &strWord, POI_MATCH_MAP &poiMatchMap, 
								CPtrArray &arrayDong, CUIntArray &arrayMatchEndPos)
{
	CPtrArray aDong, aGugun, aSido;
	POI_DATA_MAP::iterator it;
	int nPos, nPos2;

	for(it = m_poiDong.begin(); it != m_poiDong.end(); it++)
	{
		if((nPos = strWord.Find(it->first.c_str())) >= 0)
		{
			POI_DONG_SEARCH *pds = new POI_DONG_SEARCH;
			memset(pds, 0x00, sizeof(POI_DONG_SEARCH));

			if((nPos2 = strWord.Find(it->second->szDong)) >= 0)
			{
				pds->bFullMatch = TRUE;
				pds->nPos = nPos2;
				pds->nLength = (int)strlen(it->second->szDong);
			}
			else 
			{
				pds->nPos = nPos;
				pds->nLength = (int)strlen(it->first.c_str());
			}

			pds->pPOI = it->second;
			pds->nFullMatchLength = pds->nLength;
			pds->nFullMatchPos = pds->nPos;

			if(it->second->nClass == POI_SIDO)
				aSido.Add(pds);
			else if(it->second->nClass == POI_GUGUN)
				aGugun.Add(pds);
			else
				aDong.Add(pds);
		}
	}

	int n = 0;
	for(n = 0; n < aDong.GetCount(); n++)
	{
		POI_DONG_SEARCH *pdsDong = (POI_DONG_SEARCH*)aDong.GetAt(n);

		for(int k = 0; k < aGugun.GetCount(); k++)
		{
			POI_DONG_SEARCH *pdsGugun = (POI_DONG_SEARCH*)aGugun.GetAt(k);

			if(pdsDong->pPOI->pParent == pdsGugun->pPOI &&
				pdsDong->nPos >= pdsGugun->nPos + pdsGugun->nLength && 
				pdsDong->nPos <= pdsGugun->nPos + pdsGugun->nLength + 3)
			{
				for(int x = 0; x < aSido.GetCount(); x++)
				{
					POI_DONG_SEARCH *pdsSido = (POI_DONG_SEARCH*)aSido.GetAt(x);
					
					if(pdsGugun->pPOI->pParent == pdsSido->pPOI &&
						pdsGugun->nPos >= pdsSido->nPos + pdsSido->nLength && 
						pdsGugun->nPos <= pdsSido->nPos + pdsSido->nLength + 3)
					{
						//ex) 서울강남구역삼동
						pdsDong->bGugunMatch = TRUE;
						pdsDong->bSidoMatch = TRUE;
						pdsDong->nFullMatchLength = pdsDong->nLength + pdsGugun->nLength + pdsSido->nLength;
						pdsDong->nFullMatchPos = pdsSido->nPos;
						break;
					}
				}

				if(!pdsDong->bSidoMatch)
				{
					//ex) 강남역삼동
					pdsDong->bGugunMatch = TRUE;
					pdsDong->nFullMatchLength = pdsDong->nLength + pdsGugun->nLength;
					pdsDong->nFullMatchPos = pdsGugun->nPos;
				}
			}
	
		}

		if(!pdsDong->bGugunMatch)
		{
			for(int x = 0; x < aSido.GetCount(); x++)
			{
				POI_DONG_SEARCH *pdsSido = (POI_DONG_SEARCH*)aSido.GetAt(x);

				if((pdsDong->pPOI->pParent == pdsSido->pPOI || 
					pdsDong->pPOI->pParent->pParent == pdsSido->pPOI) &&
					pdsDong->nPos >= pdsSido->nPos + pdsSido->nLength && 
					pdsDong->nPos <= pdsSido->nPos + pdsSido->nLength + 3)
				{
					//ex) 서울역삼동
					pdsDong->bSidoMatch = TRUE;
					pdsDong->nFullMatchLength = pdsDong->nLength + pdsSido->nLength;
					pdsDong->nFullMatchPos = pdsSido->nPos;
					break;
				}
			}
		}
	}


	int nMaxMP = 0;

	for(n = 0; n < aDong.GetCount(); n++)
	{
		int nCurMP = 0;
		POI_DONG_SEARCH *pdsDong = (POI_DONG_SEARCH*)aDong.GetAt(n);
		
		if(pdsDong->bSidoMatch)
			nCurMP += 100;
		if(pdsDong->bGugunMatch)
			nCurMP += 100;
		if(pdsDong->bFullMatch)
			nCurMP += 100;
		nCurMP += (pdsDong->nFullMatchLength * 5);
		nCurMP -= (pdsDong->nFullMatchPos * 5);

		pdsDong->nMP = nCurMP;
		nMaxMP = max(nMaxMP, nCurMP);
	}


	if(nMaxMP > 100)
	{
		for(n = 0; n < aDong.GetCount(); n++)
		{
			POI_DONG_SEARCH *pdsDong = (POI_DONG_SEARCH*)aDong.GetAt(n);

			if(pdsDong->nMP == nMaxMP)
			{
				POI_MATCH_DATA *pMatch = new POI_MATCH_DATA;
				ZeroMemory(pMatch, sizeof(POI_MATCH_DATA));
				pMatch->pPOI = pdsDong->pPOI;
				poiMatchMap.insert(POI_MATCH_MAP::value_type(pMatch->pPOI, pMatch));

				//이전에 매치된 적이 있는 경우에, 더 긴 워드사이즈, 더 짧은 매치위치로 변경함
				pMatch->nDongMatchWordSize = pdsDong->nFullMatchLength;
				pMatch->nDongMatchPosition = pdsDong->nFullMatchPos;
				pMatch->bDongMatch = TRUE;

				//g_bana_log->Print("1DONG: %s (%d)\n", GetDisplayName(pdsDong->pPOI), nMaxMP);

				arrayMatchEndPos.Add(pdsDong->nPos + pdsDong->nLength);
				arrayDong.Add(pdsDong->pPOI);
			}
		}

//		return TRUE;
	}


	for(int k = 0; k < aGugun.GetCount(); k++)
	{
		POI_DONG_SEARCH *pdsGugun = (POI_DONG_SEARCH*)aGugun.GetAt(k);

		for(int x = 0; x < aSido.GetCount(); x++)
		{
			POI_DONG_SEARCH *pdsSido = (POI_DONG_SEARCH*)aSido.GetAt(x);

			if(pdsGugun->pPOI->pParent == pdsSido->pPOI &&
				pdsGugun->nPos >= pdsSido->nPos + pdsSido->nLength && 
				pdsGugun->nPos <= pdsSido->nPos + pdsSido->nLength + 3)
			{
				//ex) 서울강남구
				pdsGugun->bSidoMatch = TRUE;
				pdsGugun->nFullMatchLength = pdsGugun->nLength + pdsSido->nLength;
				pdsGugun->nFullMatchPos = pdsSido->nPos;
				break;
			}
		}
	}

	for(n = 0; n < aGugun.GetCount(); n++)
	{
		int nCurMP = 0;
		POI_DONG_SEARCH *pdsGugun = (POI_DONG_SEARCH*)aGugun.GetAt(n);

		if(pdsGugun->bSidoMatch)
			nCurMP += 100;
		if(pdsGugun->bFullMatch)
			nCurMP += 100;
		nCurMP += (pdsGugun->nFullMatchLength * 5);
		nCurMP -= (pdsGugun->nFullMatchPos * 5);

		pdsGugun->nMP = nCurMP;
		nMaxMP = max(nMaxMP, nCurMP);
	}
	
	if(nMaxMP > 100)
	{
		for(n = 0; n < aGugun.GetCount(); n++)
		{
			POI_DONG_SEARCH *pdsGugun = (POI_DONG_SEARCH*)aGugun.GetAt(n);

			if(pdsGugun->nMP == nMaxMP)
			{
				POI_MATCH_DATA *pMatch = new POI_MATCH_DATA;
				ZeroMemory(pMatch, sizeof(POI_MATCH_DATA));
				pMatch->pPOI = pdsGugun->pPOI;
				poiMatchMap.insert(POI_MATCH_MAP::value_type(pMatch->pPOI, pMatch));

				//이전에 매치된 적이 있는 경우에, 더 긴 워드사이즈, 더 짧은 매치위치로 변경함
				pMatch->nDongMatchWordSize = pdsGugun->nFullMatchLength;
				pMatch->nDongMatchPosition = pdsGugun->nFullMatchPos;
				pMatch->bDongMatch = TRUE;

				//g_bana_log->Print("2GUGUN: %s (%d)\n", GetDisplayName(pdsGugun->pPOI), nMaxMP);

				arrayMatchEndPos.Add(pdsGugun->nPos + pdsGugun->nLength);
				arrayDong.Add(pdsGugun->pPOI);
			}
		}

		return TRUE;
	}

	for(n = 0; n < aSido.GetCount(); n++)
	{
		int nCurMP = 0;
		POI_DONG_SEARCH *pdsSido = (POI_DONG_SEARCH*)aSido.GetAt(n);

		if(pdsSido->bFullMatch)
			nCurMP += 100;
		nCurMP += (pdsSido->nFullMatchLength * 5);
		nCurMP -= (pdsSido->nFullMatchPos * 5);

		pdsSido->nMP = nCurMP;
		nMaxMP = max(nMaxMP, nCurMP);
	}

	if(nMaxMP > 100)
	{
		for(n = 0; n < aSido.GetCount(); n++)
		{
			POI_DONG_SEARCH *pdsSido = (POI_DONG_SEARCH*)aSido.GetAt(n);

			if(pdsSido->nMP == nMaxMP)
			{
				POI_MATCH_DATA *pMatch = new POI_MATCH_DATA;
				ZeroMemory(pMatch, sizeof(POI_MATCH_DATA));
				pMatch->pPOI = pdsSido->pPOI;
				poiMatchMap.insert(POI_MATCH_MAP::value_type(pMatch->pPOI, pMatch));

				//이전에 매치된 적이 있는 경우에, 더 긴 워드사이즈, 더 짧은 매치위치로 변경함
				pMatch->nDongMatchWordSize = pdsSido->nFullMatchLength;
				pMatch->nDongMatchPosition = pdsSido->nFullMatchPos;
				pMatch->bDongMatch = TRUE;

				//g_bana_log->Print("3SIDO: %s (%d)\n", GetDisplayName(pdsSido->pPOI), nMaxMP);

				arrayMatchEndPos.Add(pdsSido->nPos + pdsSido->nLength);
				arrayDong.Add(pdsSido->pPOI);
			}
		}

		return TRUE;
	}



	for(n = 0; n < aDong.GetCount(); n++)
	{
		POI_DONG_SEARCH *pdsDong = (POI_DONG_SEARCH*)aDong.GetAt(n);

		if(pdsDong->nMP >= 30)	//3자리이상 앞에서 부터 매칭된 경우임
		{
			POI_MATCH_DATA *pMatch = new POI_MATCH_DATA;
			ZeroMemory(pMatch, sizeof(POI_MATCH_DATA));
			pMatch->pPOI = pdsDong->pPOI;
			poiMatchMap.insert(POI_MATCH_MAP::value_type(pMatch->pPOI, pMatch));

			//이전에 매치된 적이 있는 경우에, 더 긴 워드사이즈, 더 짧은 매치위치로 변경함
			pMatch->nDongMatchWordSize = pdsDong->nFullMatchLength;
			pMatch->nDongMatchPosition = pdsDong->nFullMatchPos;
			pMatch->bDongMatch = TRUE;

			//g_bana_log->Print("1-1DONG: %s (%d)\n", GetDisplayName(pdsDong->pPOI), pdsDong->nMP);

			arrayMatchEndPos.Add(pdsDong->nPos + pdsDong->nLength);
			arrayDong.Add(pdsDong->pPOI);			
		}
	}

	if(arrayDong.GetCount() == 0)
	{
		for(n = 0; n < aGugun.GetCount(); n++)
		{
			POI_DONG_SEARCH *pdsGugun = (POI_DONG_SEARCH*)aGugun.GetAt(n);

			if(pdsGugun->nMP >= 20)
			{
				POI_MATCH_DATA *pMatch = new POI_MATCH_DATA;
				ZeroMemory(pMatch, sizeof(POI_MATCH_DATA));
				pMatch->pPOI = pdsGugun->pPOI;
				poiMatchMap.insert(POI_MATCH_MAP::value_type(pMatch->pPOI, pMatch));

				//이전에 매치된 적이 있는 경우에, 더 긴 워드사이즈, 더 짧은 매치위치로 변경함
				pMatch->nDongMatchWordSize = pdsGugun->nFullMatchLength;
				pMatch->nDongMatchPosition = pdsGugun->nFullMatchPos;
				pMatch->bDongMatch = TRUE;

				//g_bana_log->Print("2-2GUGUN: %s (%d)\n", GetDisplayName(pdsGugun->pPOI), nMaxMP);

				arrayMatchEndPos.Add(pdsGugun->nPos + pdsGugun->nLength);
				arrayDong.Add(pdsGugun->pPOI);
			}
		}


		if(arrayDong.GetCount() == 0)
		{
			for(n = 0; n < aSido.GetCount(); n++)
			{
				POI_DONG_SEARCH *pdsSido = (POI_DONG_SEARCH*)aSido.GetAt(n);

				if(pdsSido->nMP >= 20)
				{
					POI_MATCH_DATA *pMatch = new POI_MATCH_DATA;
					ZeroMemory(pMatch, sizeof(POI_MATCH_DATA));
					pMatch->pPOI = pdsSido->pPOI;
					poiMatchMap.insert(POI_MATCH_MAP::value_type(pMatch->pPOI, pMatch));

					//이전에 매치된 적이 있는 경우에, 더 긴 워드사이즈, 더 짧은 매치위치로 변경함
					pMatch->nDongMatchWordSize = pdsSido->nFullMatchLength;
					pMatch->nDongMatchPosition = pdsSido->nFullMatchPos;
					pMatch->bDongMatch = TRUE;

					//g_bana_log->Print("3-3SIDO: %s (%d)\n", GetDisplayName(pdsSido->pPOI), nMaxMP);

					arrayMatchEndPos.Add(pdsSido->nPos + pdsSido->nLength);
					arrayDong.Add(pdsSido->pPOI);
				}
			}
		}
	}

	return FALSE;
}



bool CPOIData::LikeSearch(CString strWord, POI_MATCH_VECTOR &poiMatchVector)
{
	POI_MATCH_MAP poiMatchMap;
	POI_MATCH_MAP::iterator iter, iter2;
	POI_LARGE_DATA poiFoundLargeData;
	POI_LARGE_DATA::iterator poiLargeDataIter;
	CPtrArray arrayDong;
	CUIntArray arrayMatchEndPos;
	WCHAR wChar[255];
	char szData[255];

	if(strWord.GetLength() < 2) 
		return FALSE;

	arrayMatchEndPos.Add(0);
	SearchDongDataNew(strWord, poiMatchMap, arrayDong, arrayMatchEndPos);
	ReplacePeseudoWord(strWord);


	//명칭검색
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strWord, -1, wChar, 255);

	for(int k = 2; k <= (int)wcslen(wChar); k++)
	{
		for(int i = 0; i + k <= (int)wcslen(wChar); i++)
		{
			int nLen;
			nLen = WideCharToMultiByte(CP_ACP, 0, &wChar[i], k, szData, 255, NULL, NULL);
			szData[nLen] = 0;
			
			//DWORD dwTick = GetTickCount();
			//SearchDongData(strWord, szData, poiMatchMap);
			//g_bana_log->Print("SearchDongData tick: %s, %d\n", szData, GetTickCount() - dwTick);
			//dwTick = GetTickCount();


			//수를 많이 가지고 있는 POI부분 명칭에 대해서, 그 이외의 단어로 검색된 결과값에 대해서 재검색한다.
			if(m_poiLargeData.find(szData) == m_poiLargeData.end()) {
				SearchNameData(strWord, szData, poiMatchMap);
				//g_bana_log->Print("SearchNameData tick: %s, %d\n", szData, GetTickCount() - dwTick);
			}
			else {
				poiFoundLargeData.insert(POI_LARGE_DATA::value_type(szData, szData));
			}
		}
	}


	//검색된 LARGE DATA에 대해서 매칭여부를 판단한다.
	if(poiFoundLargeData.size() > 0)
	{
		POI_LARGE_DATA::iterator iterLargeData;
		for(iter = poiMatchMap.begin(); iter != poiMatchMap.end(); iter++) 
		{
			POI_DATA *pPOI = (*iter).second->pPOI;

			if(pPOI->nFCnt > 0)
			{
				iterLargeData = poiFoundLargeData.find(pPOI->F1);
				if(iterLargeData != poiFoundLargeData.end())
				{
					if(!(*iter).second->bFMatch[0]) {
						(*iter).second->bFMatch[0] = TRUE;
						(*iter).second->nFMatchWordSize += (int)(*iterLargeData).first.length();
					}
				}
			}

			if(pPOI->nFCnt > 1)
			{
				iterLargeData = poiFoundLargeData.find(pPOI->F2);
				if(iterLargeData != poiFoundLargeData.end())
				{
					if(!(*iter).second->bFMatch[1]) {
						(*iter).second->bFMatch[1] = TRUE;
						(*iter).second->nFMatchWordSize += (int)(*iterLargeData).first.length();
					}
				}
			}

			if(pPOI->nFCnt > 2)
			{
				iterLargeData = poiFoundLargeData.find(pPOI->F3);
				if(iterLargeData != poiFoundLargeData.end())
				{
					if(!(*iter).second->bFMatch[2]) {
						(*iter).second->bFMatch[2] = TRUE;
						(*iter).second->nFMatchWordSize += (int)(*iterLargeData).first.length();
					}
				}
			}

			if(pPOI->nFCnt > 3)
			{
				iterLargeData = poiFoundLargeData.find(pPOI->F4);
				if(iterLargeData != poiFoundLargeData.end())
				{
					if(!(*iter).second->bFMatch[3]) {
						(*iter).second->bFMatch[3] = TRUE;
						(*iter).second->nFMatchWordSize += (int)(*iterLargeData).first.length();
					}
				}
			}
			
			if(pPOI->nFCnt > 4)
			{
				iterLargeData = poiFoundLargeData.find(pPOI->F5);
				if(iterLargeData != poiFoundLargeData.end())
				{
					if(!(*iter).second->bFMatch[4]) {
						(*iter).second->bFMatch[4] = TRUE;
						(*iter).second->nFMatchWordSize += (int)(*iterLargeData).first.length();
					}
				}
			}
		}
	}




	//FName에서 매치율이 기준을 넘지 못한 경우에 제외시킴
	for(iter = poiMatchMap.begin(); iter != poiMatchMap.end();) {
		int nMatchCount = 0;
		POI_MATCH_DATA *pMatch = (*iter).second;

		if(pMatch->pPOI->nFCnt > 0)
		{
			for(int i = 0; i < pMatch->pPOI->nFCnt; i++)
			{
				if(pMatch->bFMatch[i])
					nMatchCount++;
			}

			pMatch->nMatchRate = (short)(nMatchCount * 100 / pMatch->pPOI->nFCnt);


			//매치율 검사
			if(pMatch->nMatchRate < m_nMatchPassRate)
			{
				//단순히 FName 매칭이 있는 경우만 배제시킴
				if(!pMatch->bDongMatch)
				{
					delete (*iter).second;
					iter = poiMatchMap.erase(iter);
					continue;
				}
			}
			else
			{
				pMatch->bValidFMatch = TRUE;
			}
		}

		iter++;
	}


/*
	//CName 매치 검사
	for(int k = 2; k <= wcslen(wChar); k++)
	{
		for(int i = 0; i + k <= wcslen(wChar); i++)
		{
			int nLen;
			nLen = WideCharToMultiByte(CP_ACP, 0, &wChar[i], k, szData, 255, NULL, NULL);
			szData[nLen] = 0;
			SearchCNameData(strWord, szData, poiMatchMap);
		}
	}
*/
/*
	//CName에서 매치율은 FName의 매치율과 연동되어 필터링한다.
	for(iter = poiMatchVector.begin(); iter != poiMatchVector.end();) {
		int nMatchCount = 0;
		POI_MATCH_DATA *pMatch = (*iter);

		if(pMatch->pPOI->nCCnt > 0)
		{		
			//CName 매치는 FName매치가 있어야 의미가 있음
			if(!pMatch->bValidFMatch)
			{
				delete (*iter);
				iter = poiMatchVector.erase(iter);
				continue;
			}

			for(int i = 0; i < pMatch->pPOI->nCCnt; i++)
			{
				if(pMatch->bCMatch[i])
					nMatchCount++;
			}

			//매치율 검사
			if(nMatchCount * 100 / pMatch->pPOI->nCCnt < MATCH_PASS_RATE)
			{
				pMatch->bValidCMatch = FALSE;
			}
			else
			{
				pMatch->bValidCMatch = TRUE;
			}
		}
		iter++;
	}
*/


	for(iter = poiMatchMap.begin(); iter != poiMatchMap.end(); iter++) 
	{
		POI_MATCH_DATA *pMatch = (*iter).second;

		if(pMatch->bDongMatch)
		{
			POI_DATA *pDong = (POI_DATA*)pMatch->pPOI;
			pMatch->nMatchPoint = 50;

			if(pDong->nClass == 0)		//동데이터중에서
			{
				if(pDong->nBoundaryLevel > 1)	//외곽지역이고
				{
					//검색된 시도데이터와 같은 시도구군인 경우에 가중치 부여함
					for(iter2 = poiMatchMap.begin(); iter2 != poiMatchMap.end(); iter2++)
					{
						POI_MATCH_DATA *pMatch2 = (*iter2).second;
						POI_DATA *pDong2 = (POI_DATA*)pMatch2->pPOI->pDong;

						if(pDong == pDong2)
							continue;

						if(pDong2->nClass > 3)
						{
							if(!strcmp(pDong->szSido, pDong2->szSido) &&
								!strcmp(pDong->szGugun, pDong2->szGugun) &&
								!strcmp(pDong->szGugun2, pDong2->szGugun2))
							{		
								pMatch->nMatchPoint = 70;
								//g_bana_log->Print("70MP: nUID=%d\n", pMatch2->pPOI->nUID);
								break;
							}
							else if(!strcmp(pDong->szSido, pDong2->szSido))
							{
								CString strGugun = pDong->szGugun;
								if(strGugun.Right(2) == "구" || 
									strGugun.Right(2) == "군")
								{
									pMatch->nMatchPoint = max(pMatch->nMatchPoint, 65);
									//g_bana_log->Print("65MP: nUID=%d\n", pMatch->pPOI->nUID);
								}
								else if(!strcmp(pDong->szGugun, pDong2->szGugun))
								{
									pMatch->nMatchPoint = max(pMatch->nMatchPoint, 60);
									//g_bana_log->Print("60aMP: nUID=%d\n", pMatch->pPOI->nUID);
								}
							}
						}
					}

					//검색된 시도가 없는 경우에 포인터를 낮춤
					if(pMatch->nMatchPoint <= 50)
						pMatch->nMatchPoint = 30;
				}
				else	//인근지역이지만 외곽일 수 있음
				{
					//검색된 시도데이터와 같은 시도구군인 경우에 가중치 부여함
					for(iter2 = poiMatchMap.begin(); iter2 != poiMatchMap.end(); iter2++)
					{
						POI_MATCH_DATA *pMatch2 = (*iter2).second;
						POI_DATA *pDong2 = (POI_DATA*)pMatch2->pPOI->pDong;

						if(pDong == pDong2)
							continue;

						if(pDong2->nClass > 3)
						{
							if(!strcmp(pDong->szSido, pDong2->szSido) &&
								!strcmp(pDong->szGugun, pDong2->szGugun) &&
								!strcmp(pDong->szGugun2, pDong2->szGugun2))
							{		
								//g_bana_log->Print("55MP: nUID=%d\n", pMatch->pPOI->nUID);
								pMatch->nMatchPoint = 55;
								break;
							}
							else if(!strcmp(pDong->szSido, pDong2->szSido))
							{
								CString strGugun = pDong->szGugun;
								if(strGugun.Right(2) == "구" || 
									strGugun.Right(2) == "군")
								{
									//g_bana_log->Print("51MP: nUID=%d\n", pMatch->pPOI->nUID);
									pMatch->nMatchPoint = max(pMatch->nMatchPoint, 51);
								}
								else if(!strcmp(pDong->szGugun, pDong2->szGugun))
								{
									//g_bana_log->Print("52MP: nUID=%d\n", pMatch->pPOI->nUID);
									pMatch->nMatchPoint = max(pMatch->nMatchPoint, 52);
								}
							}
						}
					}
				}

				//베스트드라이브인 경우에 동데이터가 POI데이터보다 앞서게 세팅해야 한다.
				if(m_ci.m_nCompanyCode == 12600 || 
					m_ci.m_nCompanyCode == 5000)
				{
					pMatch->nMatchPoint += 31;
				}
			}
		}
		else
		{
			POI_DATA *pDong = (POI_DATA*)pMatch->pPOI->pDong;	//원본 동데이터
			pMatch->nMatchPoint = 50;

			for(iter2 = poiMatchMap.begin(); iter2 != poiMatchMap.end(); iter2++)
			{
				POI_MATCH_DATA *pMatch2 = (*iter2).second;
				POI_DATA *pDong2 = (POI_DATA*)pMatch2->pPOI->pDong;

				if(pMatch2->bDongMatch)
				{
					//해당 POIName이 속해있는 동데이터가 검색된 경우 90점 부여
					if(pDong->nID == pDong2->nID)
					{
						//g_bana_log->Print("90MP: nUID=%d\n", pMatch2->pPOI->nUID);
						pMatch->nMatchPoint = 90;
						break;
					}
					else if((pDong->nID != 0 && pDong->nID == pDong2->nMainDongID) ||
						(pDong->nMainDongID != 0 && pDong->nMainDongID == pDong2->nID) ||
						(pDong->nMainDongID != 0 && pDong->nMainDongID == pDong2->nMainDongID))
					{
						//메인동이 같은 경우에 80점 
						//g_bana_log->Print("80MP: nUID=%d\n", pMatch->pPOI->nUID);
						pMatch->nMatchPoint = max(pMatch->nMatchPoint, 80);
					}
					else if(GetDistanceKMeter(pDong->dPosX, pDong->dPosY, pDong2->dPosX, pDong2->dPosY) < 5)	//2007-07-10 기존에 3km->5km
					{
						//거리차이가 30km이내인 경우에 60점(동매칭보다 앞섬)
						//g_bana_log->Print("60bMP: nUID=%d\n", pMatch->pPOI->nUID);
						pMatch->nMatchPoint = max(pMatch->nMatchPoint, 60);
					}
					else
					{	
						//기타사항도 고려해 볼수 있음
					}
				}
			}

			//CName으로도 검색된 경우에 2점 추가
			if(strlen(pMatch->pPOI->C1) > 2 && strWord.Find(pMatch->pPOI->C1) >= 0)
				pMatch->nMatchPoint += 2;		//2007-07-10 원래 5점->2점

			//단어파트에서 맞는 비율에 따라 가중치 부과함
			pMatch->nMatchPoint += (pMatch->nMatchRate / 10);
			//g_bana_log->Print("nMatchWordRate:+%dMP: nUID=%d\n", pMatch->nMatchRate / 10, pMatch->pPOI->nUID);


			//연속단어 일치에 따라서 가중치 부과함
			CString strFullName = MakeFullName(pMatch->pPOI);

			strWord.Remove(' ');

			if(strFullName == strWord)
			{
				//g_bana_log->Print("+15MP: nUID=%d\n", pMatch->pPOI->nUID);
				pMatch->nMatchPoint += 15;		//2007-07-10 원래 1점->15점
			}
			else
			{
				int nMatchWordCount = 0;

				for(int h = 0; h < arrayMatchEndPos.GetCount(); h++)
				{
					int nCurMatchWordCount = 0;
					UINT nEndPos = arrayMatchEndPos.GetAt(h);

					//g_bana_log->Print("EndPos: %d, %s\n", nEndPos, GetDisplayName(pMatch->pPOI));


					for(int b = 0; b < min(strFullName.GetLength(), strWord.GetLength()); b++)
					{
						if(strFullName.GetAt(b) == strWord.GetAt(b + nEndPos))
							nCurMatchWordCount++;
						else
							break;						
					}

					nMatchWordCount = max(nMatchWordCount, nCurMatchWordCount);
				}

				pMatch->nMatchPoint += nMatchWordCount;
				//g_bana_log->Print("nMatchWordCount:+%dMP: %s\n", nMatchWordCount, GetDisplayName(pMatch->pPOI));
			}


			//검색된 지역명이 존재하는 경우에, 해당지역 바운데리에 있지 않는 POI데이터는 제외함
			if(arrayDong.GetCount() > 0)
			{
				BOOL bInBoundary = FALSE;

				for(int k = 0; k < arrayDong.GetCount(); k++)
				{
					POI_DATA *pPOI = (POI_DATA*)arrayDong.GetAt(k);

					int nDistanceKM = (int)GetDistanceKMeter(pPOI->dPosX, pPOI->dPosY, pMatch->pPOI->dPosX, pMatch->pPOI->dPosY);

					if(pPOI->nClass == POI_SIDO)
					{
						if(nDistanceKM < 25)
							bInBoundary = TRUE;
					}
					else if(pPOI->nClass == POI_GUGUN)
					{
						if(nDistanceKM < 10)
							bInBoundary = TRUE;
					}
					else 
					{
						if(nDistanceKM < 5)
							bInBoundary = TRUE;
					}

					if(bInBoundary)
						break;
				}

				if(!bInBoundary)
				{
					pMatch->nMatchPoint = 40;
				}
			}

		}
	}


	
	if(poiMatchMap.size() > 0)
	{
		for(iter = poiMatchMap.begin(); iter != poiMatchMap.end(); iter++)
			poiMatchVector.push_back((*iter).second);

		poiMatchMap.clear();
		std::sort(poiMatchVector.begin(), poiMatchVector.end(), POI_greator);

/*
		int nCount = 1;
		POI_MATCH_VECTOR::iterator iterMatch;
		for(iterMatch = poiMatchVector.begin(); iterMatch != poiMatchVector.end(); iterMatch++) 
		{
			POI_MATCH_DATA *pMatch = (*iterMatch);
			CString strDisplayName;

			GetDisplayName(pMatch->pPOI, strDisplayName);
			g_bana_log->Print("%d)ID:%d, MP:%d, DP:%d, WS:%d, CL:%d, BL:%d, KM:%0.1f, %s\n", 
					nCount++,
					pMatch->pPOI->nUID,
					pMatch->nMatchPoint, 
					pMatch->bDongMatch,
					pMatch->nDongMatchWordSize,
					pMatch->pPOI->nClass,
					pMatch->pPOI->nBoundaryLevel,
					pMatch->pPOI->dKMFromCenter,
					strDisplayName);

		}
		g_bana_log->Print("--------------------------------------------\n");
*/

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}




bool CPOIData::LikeSearchOld(CString strWord, POI_MATCH_VECTOR &poiMatchVector)
{
	POI_MATCH_MAP poiMatchMap;
	POI_MATCH_MAP::iterator iter, iter2;
	POI_LARGE_DATA poiFoundLargeData;
	POI_LARGE_DATA::iterator poiLargeDataIter;

	if(strWord.GetLength() < 2) 
		return FALSE;

	ReplacePeseudoWord(strWord);

	WCHAR wChar[255];
	char szData[255];

	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strWord, -1, wChar, 255);

	for(int k = 2; k <= (int)wcslen(wChar); k++)
	{
		for(int i = 0; i + k <= (int)wcslen(wChar); i++)
		{
			int nLen;
			nLen = WideCharToMultiByte(CP_ACP, 0, &wChar[i], k, szData, 255, NULL, NULL);
			szData[nLen] = 0;

			//DWORD dwTick = GetTickCount();
			SearchDongData(strWord, szData, poiMatchMap);
			//g_bana_log->Print("SearchDongData tick: %s, %d\n", szData, GetTickCount() - dwTick);
			//dwTick = GetTickCount();

			//수를 많이 가지고 있는 POI부분 명칭에 대해서, 그 이외의 단어로 검색된 결과값에 대해서 재검색한다.
			if(m_poiLargeData.find(szData) == m_poiLargeData.end()) {
				SearchNameData(strWord, szData, poiMatchMap);
				//g_bana_log->Print("SearchNameData tick: %s, %d\n", szData, GetTickCount() - dwTick);
			}
			else {
				poiFoundLargeData.insert(POI_LARGE_DATA::value_type(szData, szData));
			}
		}
	}


	//검색된 LARGE DATA에 대해서 매칭여부를 판단한다.
	if(poiFoundLargeData.size() > 0)
	{
		POI_LARGE_DATA::iterator iterLargeData;
		for(iter = poiMatchMap.begin(); iter != poiMatchMap.end(); iter++) 
		{
			POI_DATA *pPOI = (*iter).second->pPOI;

			if(pPOI->nFCnt > 0)
			{
				iterLargeData = poiFoundLargeData.find(pPOI->F1);
				if(iterLargeData != poiFoundLargeData.end())
				{
					if(!(*iter).second->bFMatch[0]) {
						(*iter).second->bFMatch[0] = TRUE;
						(*iter).second->nFMatchWordSize += (int)(*iterLargeData).first.length();
					}
				}
			}

			if(pPOI->nFCnt > 1)
			{
				iterLargeData = poiFoundLargeData.find(pPOI->F2);
				if(iterLargeData != poiFoundLargeData.end())
				{
					if(!(*iter).second->bFMatch[1]) {
						(*iter).second->bFMatch[1] = TRUE;
						(*iter).second->nFMatchWordSize += (int)(*iterLargeData).first.length();
					}
				}
			}

			if(pPOI->nFCnt > 2)
			{
				iterLargeData = poiFoundLargeData.find(pPOI->F3);
				if(iterLargeData != poiFoundLargeData.end())
				{
					if(!(*iter).second->bFMatch[2]) {
						(*iter).second->bFMatch[2] = TRUE;
						(*iter).second->nFMatchWordSize += (int)(*iterLargeData).first.length();
					}
				}
			}

			if(pPOI->nFCnt > 3)
			{
				iterLargeData = poiFoundLargeData.find(pPOI->F4);
				if(iterLargeData != poiFoundLargeData.end())
				{
					if(!(*iter).second->bFMatch[3]) {
						(*iter).second->bFMatch[3] = TRUE;
						(*iter).second->nFMatchWordSize += (int)(*iterLargeData).first.length();
					}
				}
			}

			if(pPOI->nFCnt > 4)
			{
				iterLargeData = poiFoundLargeData.find(pPOI->F5);
				if(iterLargeData != poiFoundLargeData.end())
				{
					if(!(*iter).second->bFMatch[4]) {
						(*iter).second->bFMatch[4] = TRUE;
						(*iter).second->nFMatchWordSize += (int)(*iterLargeData).first.length();
					}
				}
			}
		}
	}


	//FName에서 매치율이 기준을 넘지 못한 경우에 제외시킴
	for(iter = poiMatchMap.begin(); iter != poiMatchMap.end();) {
		int nMatchCount = 0;
		POI_MATCH_DATA *pMatch = (*iter).second;

		if(pMatch->pPOI->nFCnt > 0)
		{
			for(int i = 0; i < pMatch->pPOI->nFCnt; i++)
			{
				if(pMatch->bFMatch[i])
					nMatchCount++;
			}

			//매치율 검사
			if(nMatchCount * 100 / pMatch->pPOI->nFCnt < m_nMatchPassRate)
			{
				//단순히 FName 매칭이 있는 경우만 배제시킴
				if(!pMatch->bDongMatch)
				{
					delete (*iter).second;
					iter = poiMatchMap.erase(iter);
					continue;
				}
			}
			else
			{
				pMatch->bValidFMatch = TRUE;
			}
		}

		iter++;
	}

	/*
	//CName 매치 검사
	for(int k = 2; k <= wcslen(wChar); k++)
	{
	for(int i = 0; i + k <= wcslen(wChar); i++)
	{
	int nLen;
	nLen = WideCharToMultiByte(CP_ACP, 0, &wChar[i], k, szData, 255, NULL, NULL);
	szData[nLen] = 0;
	SearchCNameData(strWord, szData, poiMatchMap);
	}
	}
	*/
	/*
	//CName에서 매치율은 FName의 매치율과 연동되어 필터링한다.
	for(iter = poiMatchVector.begin(); iter != poiMatchVector.end();) {
	int nMatchCount = 0;
	POI_MATCH_DATA *pMatch = (*iter);

	if(pMatch->pPOI->nCCnt > 0)
	{		
	//CName 매치는 FName매치가 있어야 의미가 있음
	if(!pMatch->bValidFMatch)
	{
	delete (*iter);
	iter = poiMatchVector.erase(iter);
	continue;
	}

	for(int i = 0; i < pMatch->pPOI->nCCnt; i++)
	{
	if(pMatch->bCMatch[i])
	nMatchCount++;
	}

	//매치율 검사
	if(nMatchCount * 100 / pMatch->pPOI->nCCnt < MATCH_PASS_RATE)
	{
	pMatch->bValidCMatch = FALSE;
	}
	else
	{
	pMatch->bValidCMatch = TRUE;
	}
	}
	iter++;
	}
	*/


	for(iter = poiMatchMap.begin(); iter != poiMatchMap.end(); iter++) 
	{
		POI_MATCH_DATA *pMatch = (*iter).second;

		if(pMatch->bDongMatch)
		{
			POI_DATA *pDong = (POI_DATA*)pMatch->pPOI;
			pMatch->nMatchPoint = 50;

			if(pDong->nClass == 0)		//동데이터중에서
			{
				if(pDong->nBoundaryLevel > 1)	//외곽지역이고
				{
					//검색된 시도데이터와 같은 시도구군인 경우에 가중치 부여함
					for(iter2 = poiMatchMap.begin(); iter2 != poiMatchMap.end(); iter2++)
					{
						POI_MATCH_DATA *pMatch2 = (*iter2).second;
						POI_DATA *pDong2 = (POI_DATA*)pMatch2->pPOI->pDong;

						if(pDong == pDong2)
							continue;

						if(pDong2->nClass > 3)
						{
							if(!strcmp(pDong->szSido, pDong2->szSido) &&
								!strcmp(pDong->szGugun, pDong2->szGugun) &&
								!strcmp(pDong->szGugun2, pDong2->szGugun2))
							{		
								pMatch->nMatchPoint = 70;
								break;
							}
							else if(!strcmp(pDong->szSido, pDong2->szSido))
							{
								CString strGugun = pDong->szGugun;
								if(strGugun.Right(2) == "구" || 
									strGugun.Right(2) == "군")
								{
									pMatch->nMatchPoint = max(pMatch->nMatchPoint, 65);
								}
								else if(!strcmp(pDong->szGugun, pDong2->szGugun))
								{
									pMatch->nMatchPoint = max(pMatch->nMatchPoint, 60);
								}
							}
						}
					}

					//검색된 시도가 없는 경우에 포인터를 낮춤
					if(pMatch->nMatchPoint <= 50)
						pMatch->nMatchPoint = 30;
				}
				else	//인근지역이지만 외곽일 수 있음
				{
					//검색된 시도데이터와 같은 시도구군인 경우에 가중치 부여함
					for(iter2 = poiMatchMap.begin(); iter2 != poiMatchMap.end(); iter2++)
					{
						POI_MATCH_DATA *pMatch2 = (*iter2).second;
						POI_DATA *pDong2 = (POI_DATA*)pMatch2->pPOI->pDong;

						if(pDong == pDong2)
							continue;

						if(pDong2->nClass > 3)
						{
							if(!strcmp(pDong->szSido, pDong2->szSido) &&
								!strcmp(pDong->szGugun, pDong2->szGugun) &&
								!strcmp(pDong->szGugun2, pDong2->szGugun2))
							{		
								pMatch->nMatchPoint = 55;
								break;
							}
							else if(!strcmp(pDong->szSido, pDong2->szSido))
							{
								CString strGugun = pDong->szGugun;
								if(strGugun.Right(2) == "구" || 
									strGugun.Right(2) == "군")
								{
									pMatch->nMatchPoint = max(pMatch->nMatchPoint, 51);
								}
								else if(!strcmp(pDong->szGugun, pDong2->szGugun))
								{
									pMatch->nMatchPoint = max(pMatch->nMatchPoint, 52);
								}
							}
						}
					}
				}

				//베스트드라이브인 경우에 동데이터가 POI데이터보다 앞서게 세팅해야 한다.
				if(m_ci.m_nCompanyCode == 12600 || 
					m_ci.m_nCompanyCode == 5000)
				{
					pMatch->nMatchPoint += 31;
				}
			}
		}
		else
		{
			POI_DATA *pDong = (POI_DATA*)pMatch->pPOI->pDong;	//원본 동데이터
			pMatch->nMatchPoint = 50;

			for(iter2 = poiMatchMap.begin(); iter2 != poiMatchMap.end(); iter2++)
			{
				POI_MATCH_DATA *pMatch2 = (*iter2).second;
				POI_DATA *pDong2 = (POI_DATA*)pMatch2->pPOI->pDong;

				if(pMatch2->bDongMatch)
				{
					//해당 POIName이 속해있는 동데이터가 검색된 경우 90점 부여
					if(pDong->nID == pDong2->nID)
					{
						pMatch->nMatchPoint = 90;
						break;
					}
					else if((pDong->nID != 0 && pDong->nID == pDong2->nMainDongID) ||
						(pDong->nMainDongID != 0 && pDong->nMainDongID == pDong2->nID) ||
						(pDong->nMainDongID != 0 && pDong->nMainDongID == pDong2->nMainDongID))
					{
						//메인동이 같은 경우에 80점 
						pMatch->nMatchPoint = max(pMatch->nMatchPoint, 80);
					}
					else if(GetDistanceKMeter(pDong->dPosX, pDong->dPosY, pDong2->dPosX, pDong2->dPosY) < 3)
					{
						//거리차이가 1.5km이내인 경우에 60점(동매칭보다 앞섬)
						pMatch->nMatchPoint = max(pMatch->nMatchPoint, 60);
					}
					else
					{	
						//기타사항도 고려해 볼수 있음
					}
				}
			}

			//CName으로도 검색된 경우에 5점 추가
			if(pMatch->bValidCMatch)
				pMatch->nMatchPoint += 5;

			//전체단어 일치시 1점 추가
			if(MakeFullName(pMatch->pPOI).GetLength() == strWord.GetLength())
				pMatch->nMatchPoint += 1;
		}
	}


	if(poiMatchMap.size() > 0)
	{
		for(iter = poiMatchMap.begin(); iter != poiMatchMap.end(); iter++)
			poiMatchVector.push_back((*iter).second);

		poiMatchMap.clear();
		std::sort(poiMatchVector.begin(), poiMatchVector.end(), POI_greator);


		int nCount = 1;
		POI_MATCH_VECTOR::iterator iterMatch;
		for(iterMatch = poiMatchVector.begin(); iterMatch != poiMatchVector.end(); iterMatch++) 
		{
			POI_MATCH_DATA *pMatch = (*iterMatch);
			CString strDisplayName;
			GetDisplayName(pMatch->pPOI, strDisplayName);

			/*
			g_bana_log->Print("%d)MP:%d, DP:%d, WS:%d, CL:%d, BL:%d, KM:%0.1f, %s\n", 
			nCount++,
			pMatch->nMatchPoint, 
			pMatch->bDongMatch,
			pMatch->nDongMatchWordSize,
			pMatch->pPOI->nClass,
			pMatch->pPOI->nBoundaryLevel,
			pMatch->pPOI->dKMFromCenter,
			strDisplayName);
			*/
		}

		//		g_bana_log->Print("--------------------------------------------\n");


		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



BOOL CPOIData::SearchDongData(CString &strWord, char *szData, POI_MATCH_MAP &poiMatchMap)
{
	POI_MATCH_MAP::iterator iterMatch;
	POI_DATA_MAP::const_iterator iter;

	iter = m_poiDong.find(szData);
	while(iter != m_poiDong.end()) {
		if(iter->first.compare(szData) != 0)
			break;

		BOOL bMatchSido = FALSE;

		for(int i = 0; i < m_crs.GetCount(); i++) {
			if(m_crs.GetAt(i) == iter->second->szSido)
			{
				bMatchSido = TRUE;			
			}
		}

		if(!bMatchSido)
		{
			if(iter->second->nBoundaryLevel > 2) {
				iter++;
				continue;
			}
		}

		//동이름이 시도구군이름과 동일한 경우
		if((*iter).second->nClass == 3) {
			CString strDisplayName;
			GetDisplayName((*iter).second, strDisplayName);
			//'동'을 붙여서 비교해서 틀리면 제외함
			if(strcmp((*iter).second->szDong, szData)) {
				iter++;
				continue;
			}
		}

		POI_MATCH_DATA *pMatch = NULL;
		iterMatch = poiMatchMap.find((*iter).second);
		if(iterMatch == poiMatchMap.end())
		{
			pMatch = new POI_MATCH_DATA;
			ZeroMemory(pMatch, sizeof(POI_MATCH_DATA));
			pMatch->pPOI = iter->second;
			poiMatchMap.insert(POI_MATCH_MAP::value_type(pMatch->pPOI, pMatch));
		}
		else
		{
			pMatch = (*iterMatch).second;
		}

		//이전에 매치된 적이 있는 경우에, 더 긴 워드사이즈, 더 짧은 매치위치로 변경함
		pMatch->nDongMatchWordSize = max((int)strlen(szData), pMatch->nDongMatchWordSize);
		pMatch->nDongMatchPosition = min(strWord.Find(szData, 0), pMatch->nDongMatchPosition);
		pMatch->bDongMatch = TRUE;

		//동이름에서 동을 붙여서도 맞는지 검사함
		if(strWord.Find(pMatch->pPOI->szDong, 0) >= 0) {
			//동을 붙인 동이름도 매치되면 워드사이즈를 변경함
			pMatch->nDongMatchWordSize = max((int)strlen(pMatch->pPOI->szDong), pMatch->nDongMatchWordSize);
		}

		iter++;
	}

	return TRUE;
}

BOOL CPOIData::SearchNameData(CString &strWord, char *szData, POI_MATCH_MAP &poiMatchMap)
{
	POI_MATCH_MAP::iterator iterMatch;
	POI_DATA_DEPTH_MAP::const_iterator iter;
	POI_DATA_MAP *pPOIMap = NULL;


	iter = m_poiName.find(szData);
	while(iter != m_poiName.end()) {
		if(iter->first.compare(szData) != 0)
			break;

		if(iter->second->pData == NULL)
		{
			iter++;
			continue;
		}

		if(iter->second->pData->bHide) 	//2007-07-10 추가함..삭제대신 검색에서 안나오도록 함
		{
			iter++;
			continue;
		}
		
		if(iter->second->pData->nBoundaryLevel > 2) {
			iter++;
			continue;
		}

		POI_MATCH_DATA *pMatch = NULL;
		iterMatch = poiMatchMap.find((*iter).second->pData);
		if(iterMatch == poiMatchMap.end())
		{
			pMatch = new POI_MATCH_DATA;
			ZeroMemory(pMatch, sizeof(POI_MATCH_DATA));
			pMatch->pPOI = (*iter).second->pData;
			poiMatchMap.insert(POI_MATCH_MAP::value_type(pMatch->pPOI, pMatch));
		}
		else
		{
			pMatch = (*iterMatch).second;
		}

		//이전에 매치된 적이 없는 경우에, 매치사이즈를 추가함
		if(!pMatch->bFMatch[iter->second->nDepth]) {
			pMatch->bFMatch[iter->second->nDepth] = TRUE;
			pMatch->nFMatchWordSize += (int)strlen(szData);
		}

		iter++;
	}



	return TRUE;

}


double CPOIData::GetDistanceKMeter(double dPosX1, double dPosY1, double dPosX2, double dPosY2)
{
	//1도= pi / 180
	//double dx = (dPosY1 - dPosY2) / 360  * 2 * 6377.397 * 3.14159;
	//double dy = (dPosX1 - dPosX2) / 360  * 6377.397 * cos((dPosY1 + dPosY2) / 2 / 360 * 2 * 3.14159) * 3.14159;

	double dx = (dPosY1 - dPosY2) * 111.306481340166;
    double dy = (dPosX1 - dPosX2) * cos((dPosY1 + dPosY2) * 0.00872663800) * 111.306481340166;

    return sqrt(dx*dx + dy*dy);
}

double CPOIData::GetDistanceKMeter(double dPosX1, double dPosY1, long nID)
{
	double dx = (dPosY1 - m_dCenterPosY[nID]) * 111.306481340166;
    double dy = (dPosX1 - m_dCenterPosX[nID]) * cos((dPosY1 + m_dCenterPosY[nID]) * 0.00872663800) * 111.306481340166;

    return sqrt(dx*dx + dy*dy);
}



void CPOIData::GetDisplayName(POI_DATA *pPOI, CString &strDisplayName)
{
	strDisplayName = "";
	if(!pPOI) return;

	if(pPOI->nClass == POI_SIDO)
	{
		strDisplayName.Format("%s %s", pPOI->szSido,
				pPOI->szGugun);
	}
	else if(pPOI->nClass == POI_GUGUN)
	{
		if(strlen(pPOI->szGugun2) > 0)
		{
			strDisplayName.Format("%s %s %s", pPOI->szSido,
					pPOI->szGugun, pPOI->szGugun2);
		}
		else
		{
			strDisplayName.Format("%s %s", pPOI->szSido,
					pPOI->szGugun);
		}
	}
	else
	{
		if(pPOI->nUID > 0) {
			 POI_DATA *pDong = (POI_DATA*)pPOI->pDong;
			if(strlen(pDong->szGugun2) > 0) {
				strDisplayName.Format("%s %s %s %s",
						pDong->szGugun,
						pDong->szGugun2,
						pDong->szDong,
						MakeFullName(pPOI));
			}
			else
			{
				strDisplayName.Format("%s %s %s %s", pDong->szSido,
						pDong->szGugun,
						pDong->szDong,
						MakeFullName(pPOI));
			}

			if(strlen(pPOI->C1) > 0)
				strDisplayName += CString("(") + pPOI->C1 + ")";
		}
		else {
			if(strlen(pPOI->szGugun2) > 0)
			{
				strDisplayName.Format("%s %s %s",
						pPOI->szGugun,
						pPOI->szGugun2,
						pPOI->szDong);
			}
			else
			{
				strDisplayName.Format("%s %s %s", pPOI->szSido,
						pPOI->szGugun,
						pPOI->szDong);
			}
		}
	}
}


CString CPOIData::GetDisplayName(POI_DATA *pPOI)
{
	CString strName;
	GetDisplayName(pPOI, strName);
	return strName;
}

CString CPOIData::GetDisplayName(long nID)
{
	CString strName;
	GetDisplayName(FindDataFromID(nID), strName);
	return strName;
}


void CPOIData::GetGugunName(POI_DATA *pPOI, CString &strName)
{
	if(pPOI == NULL)
		strName = "";
	else if(strlen(pPOI->szGugun2) > 0)
		strName.Format("%s %s", pPOI->szGugun, pPOI->szGugun2);
	else
		strName.Format("%s", pPOI->szGugun);
}

CString CPOIData::GetGugunName(long nID)
{
	CString strName;
	GetGugunName(FindDataFromID(nID), strName);
	return strName;
}

void CPOIData::GetGugunSidoName(POI_DATA *pPOI, CString &strName)
{
	if(pPOI == NULL)
		strName = "";
	else if(strlen(pPOI->szGugun2) > 0)
		strName.Format("%s %s %s", pPOI->szGugun, pPOI->szGugun2, pPOI->szSido);
	else
		strName.Format("%s %s", pPOI->szGugun, pPOI->szSido);
}

CString CPOIData::GetGugunSidoName(long nID)
{
	CString strName;
	GetGugunSidoName(FindDataFromID(nID), strName);
	return strName;
}

CString CPOIData::GetSidoName(long nID)
{
	CString strName;
	GetSidoName(FindDataFromID(nID), strName);
	return strName;
}

void CPOIData::GetSidoName(POI_DATA *pPOI, CString &strName)
{
	if(pPOI == NULL)
		strName = "";
	else
		strName.Format("%s", pPOI->szSido);
}



void CPOIData::GetDongName(POI_DATA *pPOI, CString &strName)
{
	if(pPOI->nUID > 0)
		strName = pPOI->pDong->szDong;
	else
		strName = pPOI->szDong;
}

CString CPOIData::GetDongName(long nID)
{
	CString strName;
	GetDongName(FindDataFromID(nID), strName);
	return strName;
}


void CPOIData::GetDisplayNameReverse(POI_DATA *pPOI, CString &strDisplayName)
{
	strDisplayName = "";
	if(!pPOI) return;

	if(pPOI->nClass == POI_SIDO)
	{
		strDisplayName.Format("%s %s", pPOI->szGugun,
					pPOI->szSido);
	}
	else if(pPOI->nClass == POI_GUGUN)
	{
		if(strlen(pPOI->szGugun2) > 0)
		{
			strDisplayName.Format("%s %s %s", pPOI->szGugun2, 
					pPOI->szGugun, pPOI->szSido);
		}
		else
		{
			strDisplayName.Format("%s %s", pPOI->szGugun,
					pPOI->szSido);
		}
	}
	else
	{
		if(pPOI->nUID > 0) {
			 POI_DATA *pDong = (POI_DATA*)pPOI->pDong;
			if(strlen(pDong->szGugun2) > 0) {
				strDisplayName.Format("%s %s %s %s %s", MakeFullName(pPOI),
						pDong->szDong,
						pDong->szGugun2,
						pDong->szGugun,
						pDong->szSido);
			}
			else
			{
				strDisplayName.Format("%s %s %s %s", 
						MakeFullName(pPOI),
						pDong->szDong,
						pDong->szGugun,
						pDong->szSido);
			}
		}
		else {
			if(strlen(pPOI->szGugun2) > 0)
			{
				strDisplayName.Format("%s %s %s %s", pPOI->szDong,
						pPOI->szGugun2,
						pPOI->szGugun,
						pPOI->szSido);
			}
			else
			{
				strDisplayName.Format("%s %s %s", pPOI->szDong,
						pPOI->szGugun,
						pPOI->szSido);
			}
		}
	}
}

CString CPOIData::GetDisplayNameReverse(POI_DATA *pPOI)
{
	CString strName;
	GetDisplayNameReverse(pPOI, strName);
	return strName;
}

CString CPOIData::GetDisplayNameReverse(long nID)
{
	CString strName;
	GetDisplayNameReverse(FindDataFromID(nID), strName);
	return strName;
}


CString CPOIData::MakeGugunName(CString strGugun1, CString strGugun2)
{
	if(strGugun2.GetLength() > 0)
		return strGugun2;
	else
		return strGugun1 + " " + strGugun2;
}

void CPOIData::ReplacePeseudoWord(CString &strWord)
{
	StringMakeUpper(strWord);

	int nPos = strWord.Find(">", 0);
	if(nPos > 0) strWord = strWord.Left(nPos);

	nPos = strWord.Find(".", 0);
	if(nPos > 0) strWord = strWord.Left(nPos);

	ReplaceShortWord(strWord, "A", "아파트", TRUE);
	ReplaceShortWord(strWord, "@", "아파트", TRUE);
	ReplaceShortWord(strWord, "APT", "아파트", TRUE);
	ReplaceShortWord(strWord, "고교", "고등학교");
	ReplaceShortWord(strWord, "중교", "중학교");
	ReplaceShortWord(strWord, "초교", "초등학교");

	ReplaceShortWord(strWord, "에스케이주유소", "SK주유소");
	ReplaceShortWord(strWord, "LG주유소", "GS주유소");
	ReplaceShortWord(strWord, "엘지주유소", "GS주유소");
	ReplaceShortWord(strWord, "지에스주유소", "GS주유소");
	ReplaceShortWord(strWord, "S오일", "에쓰오일");
	ReplaceShortWord(strWord, "에스오일", "에쓰오일");

	//ReplaceShortWord(strWord, "LG마트", "GS마트");
	ReplaceShortWord(strWord, "엘지마트", "GS마트");
	ReplaceShortWord(strWord, "지에스마트", "GS마트");
	ReplaceShortWord(strWord, "E마트", "이마트");

	ReplaceShortWord(strWord, "BUY THE WAY", "바이더웨이");
	ReplaceShortWord(strWord, "패미리마트", "훼미리마트");
	ReplaceShortWord(strWord, "LG25", "GS25");
	ReplaceShortWord(strWord, "엘지25", "GS25");
	ReplaceShortWord(strWord, "지에스25", "GS25");

	ReplaceShortWord(strWord, "케이에프씨", "KFC");
	ReplaceShortWord(strWord, "씨지브이", "CGV");
	ReplaceShortWord(strWord, "에스케이", "SK");
	ReplaceShortWord(strWord, "케이티에프", "KTF");
	ReplaceShortWord(strWord, "엘지", "LG");		//이부분 서버의 값 정규화해야함(ex,엘지마트)
	ReplaceShortWord(strWord, "티지아이", "TGI");	

	ReplaceShortWord(strWord, "패리카나", "페리카나");
	ReplaceShortWord(strWord, "겔러리아", "갤러리아");
	ReplaceShortWord(strWord, "겔리리아", "갤러리아");

	ReplaceShortWord(strWord, "센타", "센터");

	ReplaceShortWord(strWord, "펠리스", "팰리스");
	ReplaceShortWord(strWord, "펠레스", "팰리스");
	ReplaceShortWord(strWord, "팰레스", "팰리스");

	ReplaceShortWord(strWord, "팰레스", "팰리스");
	ReplaceShortWord(strWord, "호탤", "호텔");

	ReplaceShortWord(strWord, "3", "삼거리", FALSE, TRUE);
	ReplaceShortWord(strWord, "4", "사거리", FALSE, TRUE);
	ReplaceShortWord(strWord, "5", "오거리", FALSE, TRUE);
	ReplaceShortWord(strWord, "로타리", "로터리");
	ReplaceShortWord(strWord, "에니", "애니");
	ReplaceShortWord(strWord, "싸이버", "사이버");

	//g_bana_log->Print("Replaced Text: [%s]\n", strWord);
}

void CPOIData::ReplaceShortWord(CString &strWord, CString strShort, CString strReplace, BOOL bCheckAlpha, BOOL bNumeric)
{
	if(bCheckAlpha)
	{
		int n = strWord.Find(strShort, 2);
		if(n > 0)
		{
			BOOL bCondition = FALSE;
			if(n == strWord.GetLength() - 1)	//마지막 글자
				bCondition = TRUE;
			else if(isalpha((BYTE)strWord.GetAt(n - 1)) == 0 &&	//이전단어와 다음단어가 알파벳이 아닌경우
					isalpha((BYTE)strWord.GetAt(n + 1)) == 0)
				bCondition = TRUE;

			if(bCondition)
				strWord.Replace(strShort, strReplace);
		}
	}
	else if(bNumeric)
	{
		int n = strWord.Find(strShort, 2);
		if(n > 0)
		{
			BOOL bCondition = FALSE;
			if(n == strWord.GetLength() - 1)	//마지막 글자
				bCondition = TRUE;
			else if(isdigit((BYTE)strWord.GetAt(n - 1)) == 0 &&	//이전단어와 다음단어가 숫자가 아닌경우
				isdigit((BYTE)strWord.GetAt(n + 1)) == 0 &&
				strWord.Mid(n+1, 2) != "가" &&
				strWord.Mid(n+1, 2) != "동" &&
				strWord.Mid(n+1, 2) != "차" &&
				strWord.Mid(n+1, 2) != "단" &&
				strWord.Mid(n+1, 2) != "사" &&
				strWord.Mid(n+1, 2) != "호" && 
				strWord.Mid(n+1, 2) != "번" && 
				strWord.Mid(n+1, 2) != "출" &&
				strWord.Mid(n+1, 2) != "분" &&
				strWord.Mid(n+1, 1) != "k" &&
				strWord.Mid(n+1, 1) != "K" &&
				strWord.Mid(n+1, 1) != "ⓚ")

				bCondition = TRUE;

			if(bCondition)	
				strWord.Replace(strShort, strReplace);
		}
	}
	else
	{
		strWord.Replace(strShort, strReplace);
	}
}

CString CPOIData::MakeFullName(POI_DATA *pPOI)
{
	if(pPOI->nUID > 0)
		return CString(pPOI->F1) + pPOI->F2 + pPOI->F3 + pPOI->F4 + pPOI->F5;
	else
		return CString(pPOI->szDong);
}

int CPOIData::GetDongParentID(int nDongID)
{
	POI_DATA *pPOI = m_poi.FindDataFromID(nDongID);

	if(pPOI == NULL)
		return -1;

	if(pPOI->pParent != NULL)
	{
		return ((POI_DATA*)pPOI->pParent)->nID;
	}
	else
	{
		return -1;
	}
}


POI_DATA* CPOIData::LikeSearchDongFor114(CString strLongName, CString &strRemainName, BOOL &bSan)
{
	POI_DATA_MAP::iterator it, itSelected;
	CString strFindMadeName, strMadeName, strGugun, strGugun2, strDong;
	UINT nFindLen = 0;

	strRemainName = strLongName;
	
	for(it = m_poiDong.begin(); it != m_poiDong.end(); it++)
	{
		if(it->second->nClass == 0)
		{
			strMadeName = it->second->szSido;
			strGugun = it->second->szGugun;
			strGugun2 = it->second->szGugun2;
			strDong = it->second->szDong;

			strMadeName += "-" + strGugun.Left(strGugun.GetLength() - 2);
			if(strGugun2.GetLength() > 0)
				strMadeName += "-" + strGugun2.Left(strGugun2.GetLength() - 2);
			strMadeName += "-" + strDong.Left(strDong.GetLength() - 2);

			if(strLongName.Find(strMadeName) >= 0 && 
				nFindLen < strMadeName.GetLength())
			{
				g_bana_log->Print("당첨 = %s\n", strMadeName);
				nFindLen = strMadeName.GetLength();
				strFindMadeName = strMadeName;
				itSelected = it; 
			}
		}
	}

	if(strFindMadeName.GetLength() > 0)
	{
		strRemainName.Replace(strFindMadeName, "");
		for(int n = 0; n < strRemainName.GetLength(); n++)
		{
			if(strRemainName.GetAt(n) == '-')
			{
				strRemainName = strRemainName.Mid(n+1);
				if(strRemainName.Find("(산)") >= 0)
				{
					bSan = TRUE;
					strRemainName.Replace("(산)", "");
				}
			
				if(!isdigit((BYTE)strRemainName.GetAt(0)))
				{
					for(int k = 0; k < strRemainName.GetLength(); k++)
					{
						if(isdigit((BYTE)strRemainName.GetAt(k)))
						{
							CString strLi = strRemainName.Left(k);
							CString strLi2 = strLi;
							strLi2.Remove('-');
							strRemainName.Replace(strLi, strLi2 + "리");
							break;
						}
					}
				}

				g_bana_log->Print("remain name = %s  san=%d)\n", strRemainName, bSan);
				return itSelected->second;
			}
		}
		return itSelected->second;
	}

	return 0;
}

CString CPOIData::GetFullName(POI_DATA *pPOI)
{
	return CString(pPOI->szSido) + pPOI->szGugun + pPOI->szGugun2 + pPOI->szDong;
}


