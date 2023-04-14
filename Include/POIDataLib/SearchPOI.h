#pragma once

class CPOIUnit;

class AFX_EXT_CLASS CSearchPOI
{
public:
	CSearchPOI(void);
	virtual ~CSearchPOI(void);
	static CString GetMarkupNormalName(CPOIUnit *pRegion, CPOIUnit *pPOI, BOOL bReserve = FALSE, BOOL bHasHead = TRUE, BOOL bHasTail = TRUE);
	static CString GetMarkupNormalName(CPOIUnit *pPOI, BOOL bHasHead = TRUE, BOOL bHasTail = TRUE);
	static CString GetMarkupNormalName(CString strBody, BOOL bHasHead = TRUE, BOOL bHasTail = TRUE);
	static CString GetMarkupLastPartHilight(CString strPOI, BOOL bFirst = FALSE);
	static CString GetMarkupLastPartHilight(CPOIUnit *pPOI);
	static CString GetMarkupPlaceDetail(CPOIUnit *pPOI, CString strDetail);
	static CString GetMarkupReplaceWord(CString strPOI, CString strKeyword, BOOL bIfNotFoundReturnSrc = FALSE);
	static CString GetMarkupReplaceWordSlash(CString strPOI, CString strKeyword, BOOL bIfNotFoundReturnSrc = FALSE);
	static CString GetMakrupReplaceSub(CString strPOI, CString strKeyword, BOOL bHasHead = TRUE, BOOL bHasTail = TRUE);

	static void CSearchPOI::ReplaceTagBraket(char *pData);
	static void CSearchPOI::ReplaceTagBraket(CString &strData);
	static void CSearchPOI::ReplaceSpecialWord(CString &strData);
	static void CSearchPOI::CheckWord(CString &strData);

	CString GetMarkupPOIName(BOOL bHasHead = TRUE, BOOL bHasTail = TRUE);
	CString GetMarkupRegionName(BOOL bReverseName = FALSE, BOOL bHasHead = TRUE, BOOL bHasTail = TRUE);
	CString GetMarkupFullName(BOOL bReverse = FALSE);

	BOOL IsDongAndFullNameMatch();

protected:
	CString GetMarkupPOINameBody(WCHAR *pwszName, int nIndex, int nCount, BOOL bMatch);	
	CString GetMarkupRegionNameBody(BOOL bReverseName, BOOL bHasHead, BOOL bHasTail, BOOL bDo, BOOL bSido, BOOL bGugun, 
									BOOL bDong, BOOL bLi);
	CString GetMarkupRegionNameDoDongBody(BOOL bReverseName, BOOL bHasHead, BOOL bHasTail);


public:
	unsigned short int nKeywordPos;
	unsigned short int nDataPos;
	BYTE nLen;
	BYTE nFullLen;
	char szKeyword[50];
	CPOIUnit* pPOI;
	unsigned short int nNewPos;
	BYTE nNewLen;
	BYTE bMatchDongID;
	bool bDongNearPOI;
	bool bBasePOI;
	bool bHasBasePOI;
	CPOIUnit *pBasePOI;
	CPOIUnit *pNearPOI;
	long nNearDistance;
	UINT nBasePOIAwayMeter;
	bool bPOISepSecond;
	CPOIUnit *pDongMatchPOI;
	bool bPhoneMatch;
	bool bAddressSearch;
	long nNewPosX;
	long nNewPosY;
	int nDongMatchType;
	long nCenterPosAwayMeter;
	bool bFullMatch;
	double dDongAdvantagePoint;
	CString strAddress;
	CPOIUnit *pPrePOI;
	bool bWebSearch;
};
