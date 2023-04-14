#include "StdAfx.h"
#include "SearchPOI.h"
#include "POIDataNew.h"

const char *szH = "<StackPanel VerticalAlignment='Center' HorizontalAlignment='Left'><TextBlock>";
const char *szT = "</TextBlock></StackPanel>";
const char *szBH = "<Run Foreground='Green' FontWeight='Bold'>";
const char *szBT = "</Run>";

CSearchPOI::CSearchPOI(void)
{ 
	nKeywordPos = 0;
	nDataPos = 0;
	nLen = 0;
	nFullLen = 0;
	szKeyword[0] = 0;
	pPOI = NULL;
	nNewPos = NULL;
	nNewLen = 0;
	bMatchDongID = 0;
	bDongNearPOI = FALSE;
	bBasePOI = FALSE;
	bHasBasePOI = FALSE;
	pBasePOI = NULL;
	pNearPOI = NULL;
	nNearDistance = 0;
	nBasePOIAwayMeter = 0;
	bPOISepSecond = 0;
	pDongMatchPOI = 0;
	bPhoneMatch = 0;
	bAddressSearch = 0;
	nNewPosX = 0;
	nNewPosY = 0;
	nDongMatchType = 0;
	nCenterPosAwayMeter = 0;
	bFullMatch = 0;
	dDongAdvantagePoint = 0;
	pPrePOI = FALSE;
	bWebSearch = FALSE;
}

CSearchPOI::~CSearchPOI(void)
{
}

CString CSearchPOI::GetMarkupPOIName(BOOL bHasHead, BOOL bHasTail)
{
	if(pPOI == NULL) return "";

	CString strBody = bHasHead ? szH : "";
	int nComboCount = 0;
	BOOL bMatch = FALSE;
	WCHAR wszName[256];

	ReplaceTagBraket(pPOI->m_szName);
	ReplaceTagBraket(pPOI->m_szSubName);

	CPOIDataNew::A2U2(pPOI->m_szName, wszName, 256);
	int i = 0;
	for(i = 0; i < wcslen(wszName); i++)
	{
		int nOffset = 1 << (15 - i);
		if(nOffset & nDataPos)
		{
			if(bMatch) 
			{
				nComboCount++;
			}
			else 
			{
				strBody += GetMarkupPOINameBody(wszName, i, nComboCount, bMatch);
				nComboCount = 1;
				bMatch = TRUE;
			}
		}
		else
		{
			if(bMatch)
			{
				strBody += GetMarkupPOINameBody(wszName, i, nComboCount, bMatch);
				nComboCount = 1;
				bMatch = FALSE;
			}
			else
			{
				nComboCount++;
			}
		}
	}

	if(nComboCount > 0)
		strBody += GetMarkupPOINameBody(wszName, i, nComboCount, bMatch);

	CString strReturn = strBody + pPOI->GetPOISubName(TRUE) + (bHasTail ? szT : "");
	ReplaceSpecialWord(strReturn);
	return strReturn;
}

CString CSearchPOI::GetMarkupPOINameBody(WCHAR *pwszName, int nIndex, int nCount, BOOL bMatch)
{
	CString strTemp;
	WCHAR wszPart[256];
	const char *szMatch = "<Run Foreground='Green' FontWeight='Bold'>%s</Run>";
	int i = nIndex - nCount;

	if(nCount == 0)
		return "";

	if(bMatch)
	{
		wcsncpy(wszPart, &pwszName[i], nCount);
		wszPart[nCount] = 0;
		strTemp.Format(szMatch, CPOIDataNew::U2A(wszPart));
		return strTemp;
	}
	else
	{
		wcsncpy(wszPart, &pwszName[i], nCount);
		wszPart[nCount] = 0;
		return CPOIDataNew::U2A(wszPart);
	}
}

CString CSearchPOI::GetMarkupRegionName(BOOL bReverseName, BOOL bHasHead, BOOL bHasTail)
{
	//g_bana_log->Print("nDongMatchType %d %d (%s)\n", nDongMatchType, pPOI->GetDongID(), pPOI->GetRegionName());

	switch(nDongMatchType)
	{
	case 1:
	case 2:
	case 3:
		return GetMarkupRegionNameBody(bReverseName, bHasHead, bHasTail, 0, 1, 1, 0, 0);

	case 4:
	case 5:
	case 30:
	case 31:
		return GetMarkupRegionNameBody(bReverseName, bHasHead, bHasTail, 0, 1, 0, 1, 0);

	case 6:
	case 7:
	case 8:
	case 9:
		return GetMarkupRegionNameBody(bReverseName, bHasHead, bHasTail, 0, 0, 1, 1, 0);

	case 10:
	case 11:
		return GetMarkupRegionNameBody(bReverseName, bHasHead, bHasTail, 0, 0, 0, 1, 0);

	case 13:
	case 14:
		return GetMarkupRegionNameBody(bReverseName, bHasHead, bHasTail, 0, 0, 0, 0, 1);

	case 15:
		return GetMarkupRegionNameBody(bReverseName, bHasHead, bHasTail, 0, 0, 0, 1, 1);

	case 16:
	case 17:
		return GetMarkupRegionNameBody(bReverseName, bHasHead, bHasTail, 0, 0, 1, 0, 1);

	case 100:
	case 101:
	case 102:
	case 103:
		return GetMarkupRegionNameBody(bReverseName, bHasHead, bHasTail, 0, 1, 1, 1, 1);

	case 200:
	case 201:
		return GetMarkupRegionNameDoDongBody(bReverseName, bHasHead, bHasTail);

	case 300:
	case 301:
		return GetMarkupRegionNameBody(bReverseName, bHasHead, bHasTail, 1, 1, 1, 1, 1);
	}

	return CString(bHasHead ? szH : "") + pPOI->GetRegionName(bReverseName) + CString(bHasTail ? szT : "");
}

//아래의 GetMarkupRegionNameBody은 도명을 표시하지 못한다. 그래서 전용함수를 추가했다.
CString CSearchPOI::GetMarkupRegionNameDoDongBody(BOOL bReverseName, BOOL bHasHead, BOOL bHasTail)
{
	CString strRegionName =  pPOI->GetRegionName(bReverseName);
	strRegionName.Replace(pPOI->GetSido(), CString(szBH) + pPOI->GetSido() + szBT);	
	strRegionName.Replace(pPOI->GetDong(), CString(szBH) + pPOI->GetDong() + szBT);	
	return CString(bHasHead ? szH : "") + strRegionName + (bHasTail ? szT : "");
}



CString CSearchPOI::GetMarkupRegionNameBody(BOOL bReverseName, BOOL bHasHead, BOOL bHasTail, 
							BOOL bDo, BOOL bSido, BOOL bGugun, BOOL bDong, BOOL bLi)
{
	CString strRegionName =  pPOI->GetRegionName(bReverseName);

	if(pPOI->IsValidGugun2())
	{
		if(bDo)
			strRegionName.Replace(pPOI->GetSido(), CString(szBH) + pPOI->GetSido() + szBT);	

		if(bSido)
			strRegionName.Replace(pPOI->GetGugun1Only(), CString(szBH) + pPOI->GetGugun1Only() + szBT);	

		if(bGugun)
			strRegionName.Replace(pPOI->GetGugun2Only(), CString(szBH) + pPOI->GetGugun2Only() + szBT);	
	}
	else
	{
		if(bSido)
			strRegionName.Replace(pPOI->GetSido(), CString(szBH) + pPOI->GetSido() + szBT);	

		if(bGugun)
			strRegionName.Replace(pPOI->GetGugun(), CString(szBH) + pPOI->GetGugun() + szBT);	
	}

	if(bDong)
		strRegionName.Replace(pPOI->GetDong(), CString(szBH) + pPOI->GetDong() + szBT);	

	if(bLi)
		strRegionName.Replace(pPOI->GetLi(), CString(szBH) + pPOI->GetLi() + szBT);	

	return CString(bHasHead ? szH : "") + strRegionName + (bHasTail ? szT : "");
}

CString CSearchPOI::GetMarkupNormalName(CPOIUnit *pPOI, BOOL bHasHead, BOOL bHasTail)
{
	return CString(bHasHead ? szH : "") + pPOI->GetPOIName() + (bHasTail ? szT : "");
}

CString CSearchPOI::GetMarkupNormalName(CString strBody, BOOL bHasHead, BOOL bHasTail)
{
	return CString(bHasHead ? szH : "") + strBody + (bHasTail ? szT : "");
}

CString CSearchPOI::GetMarkupNormalName(CPOIUnit *pRegion, CPOIUnit *pPOI, BOOL bReverse, BOOL bHasHead, BOOL bHasTail)
{
	if(pPOI->IsDongPOI())
		pPOI = NULL;

	if(bReverse)
	{
		return CString(bHasHead ? szH : "") + (pPOI ? pPOI->GetPOIName() : "") + " " + 
						pRegion->GetRegionName(bReverse) + (bHasTail ? szT : "");
	}
	else 
	{
		return CString(bHasHead ? szH : "") + pRegion->GetRegionName() + " " + 
					(pPOI ? pPOI->GetPOIName() : "") + (bHasTail ? szT : "");
	}
}

CString CSearchPOI::GetMarkupFullName(BOOL bReverse)
{
	if(bReverse)
		return GetMarkupPOIName(TRUE, FALSE) + " " + GetMarkupRegionName(FALSE, FALSE, TRUE);
	else
		return GetMarkupRegionName(FALSE, TRUE, FALSE) + " " + GetMarkupPOIName(FALSE, TRUE);
}

CString CSearchPOI::GetMarkupLastPartHilight(CString strPOI, BOOL bFirst)
{
	const char *szMatch = "<Run Foreground='Green' FontWeight='Bold'>%s</Run>";

	CheckWord(strPOI);

	int nPos = strPOI.ReverseFind(' ');

	if(bFirst)
		nPos = strPOI.Find(' ');

	if(nPos > 0)
	{
		if(bFirst)
		{
			CString strLastPart;
			strLastPart.Format(szMatch, strPOI.Left(nPos));
			return CString(szH) + strLastPart + " " + strPOI.Mid(nPos) + " " + szT;
		}
		else
		{
			CString strLastPart;
			strLastPart.Format(szMatch, strPOI.Mid(nPos));
			return CString(szH) + strPOI.Left(nPos) + " " + strLastPart + szT;
		}		
	}
	else
	{
		return CString(szH) + strPOI + szT;
	}
}

CString CSearchPOI::GetMarkupPlaceDetail(CPOIUnit *pPOI, CString strPOI)
{
	const char *szMatch = "<Run Foreground='Green' FontWeight='Bold'>%s</Run>";

	strPOI.Replace(pPOI->GetRegionName(), "");
	strPOI = pPOI->GetDongPOI()->GetDongLi() + " " + strPOI;

	CheckWord(strPOI);

	CString strLastPart;
	int nCount = 0, nPos2 = 0;
	int nPos = strPOI.ReverseFind(' ');

	if(nPos > 0)
	{
		if(strPOI.ReverseFind('[') > nPos)
		{
			CString strPOI2 = strPOI.Left(nPos);
			nPos2 = strPOI2.ReverseFind(' ');
		}

		if(nPos2 > 0)
		{
			strLastPart.Format(szMatch, strPOI.Mid(nPos2, nPos - nPos2));
			return CString(szH) + strPOI.Left(nPos2) + " " + strLastPart + strPOI.Mid(nPos) + szT;
		}
		else
		{
			strLastPart.Format(szMatch, strPOI.Mid(nPos));
			return CString(szH) + strPOI.Left(nPos) + " " + strLastPart + szT;
		}
	}
	else
	{
		return CString(szH) + strPOI + szT;
	}
}

CString CSearchPOI::GetMarkupLastPartHilight(CPOIUnit *pPOI)
{
	return GetMarkupLastPartHilight(pPOI->GetFullName());
}

CString CSearchPOI::GetMarkupReplaceWord(CString strPOI, CString strKeyword, BOOL bIfNotFoundReturnSrc)
{
	const char *szMatch = "<Run Foreground='Green' FontWeight='Bold'>%s</Run>";

	CheckWord(strPOI);
	CheckWord(strKeyword);

	int nPos = strPOI.Find(strKeyword);

	if(nPos >= 0)
	{
		CString strLastPart, strReturn;
		int nEndPos = nPos + strKeyword.GetLength();
		strLastPart.Format(szMatch, strKeyword);

		strReturn =  CString(szH) + 
			(nPos > 0 ? strPOI.Left(nPos) : "") 
			+ strLastPart + 
			((nEndPos < strPOI.GetLength()) ? strPOI.Mid(nEndPos) : "") + 
			szT;

		return strReturn;
	}
	else
	{
		return bIfNotFoundReturnSrc ? strPOI : (CString(szH) + strPOI + szT);
	}
}

CString CSearchPOI::GetMarkupReplaceWordSlash(CString strPOI, CString strKeyword, BOOL bIfNotFoundReturnSrc)
{
	CheckWord(strPOI);
	CheckWord(strKeyword);

	CString strMain = strKeyword;
	CString strSub;
	BOOL bHasSub = FALSE;
	int nLen, nPos2 = -1;
	int nPos = strKeyword.Find("/");

	if(nPos > 3 && strKeyword.GetLength() - nPos >= 1)
	{
		strMain = strKeyword.Left(nPos);
		strSub = strKeyword.Mid(nPos + 1);
		bHasSub = TRUE;
		nLen = strMain.GetLength();
	}

	nPos = strPOI.Find(strMain);

	if(bHasSub)
		nPos2 = strPOI.Find(strSub);

	if(nPos >= 0 || nPos2 >= 0)
	{
		if(nPos2 >= 0)
		{
			int nLen2 = strSub.GetLength();

			if(nPos < 0)
			{
				nPos = nPos2;
				nLen = nLen2;
				strMain = strPOI.Mid(nPos, nLen);
			}
			else if(nPos + nLen >= nPos2 && nPos <= nPos2)
			{
				nLen = max(nPos + nLen, nPos2 + nLen2);								
				strMain = strPOI.Mid(nPos, nLen);
			}
			else if(nPos2 + nLen2 >= nPos && nPos2 <= nPos)
			{
				nPos = nPos2;
				nLen = max(nPos + nLen, nPos2 + nLen2);								
				strMain = strPOI.Mid(nPos, nLen);
			}
			else
			{
				CString strPOI1, strPOI2;
				CString strKey1, strKey2;

				if(nPos < nPos2)
				{
					strPOI1 = strPOI.Mid(nPos, nLen);
					strPOI2 = strPOI.Mid(nPos2, nLen2);
					strKey1 = strMain;
					strKey2 = strSub;
				}
				else
				{
					strPOI1 = strPOI.Mid(nPos, nLen);
					strPOI2 = strPOI.Mid(nPos2, nLen2);
					strKey1 = strMain;
					strKey2 = strSub;
				}

				CString str1 = GetMakrupReplaceSub(nPos < nPos2 ? strPOI.Left(nPos2) : strPOI.Left(nPos),
													nPos < nPos2 ? strKey1 : strKey2, TRUE, FALSE);
				CString str2 = GetMakrupReplaceSub(nPos > nPos2 ? strPOI.Mid(nPos) : strPOI.Mid(nPos2),
													nPos > nPos2 ? strKey1 : strKey2, FALSE, TRUE);
				return str1 + str2;
			}
		}

		return GetMakrupReplaceSub(strPOI, strMain, TRUE, TRUE);
	}
	else
	{
		return bIfNotFoundReturnSrc ? strPOI : (CString(szH) + strPOI + szT);
	}
}

CString CSearchPOI::GetMakrupReplaceSub(CString strPOI, CString strKeyword, BOOL bHasHead, BOOL bHasTail)
{
	const char *szMatch = "<Run Foreground='Green' FontWeight='Bold'>%s</Run>";

	CString strLastPart, strReturn;
	int nPos = strPOI.Find(strKeyword);
	int nEndPos = nPos + strKeyword.GetLength();
	strLastPart.Format(szMatch, strKeyword);

	strReturn =  (bHasHead ? CString(szH) : "") + 
		(nPos > 0 ? strPOI.Left(nPos) : "") 
		+ strLastPart + 
		((nEndPos < strPOI.GetLength()) ? strPOI.Mid(nEndPos) : "") + 
		(bHasTail ? szT : "");

	return strReturn;
}



void CSearchPOI::ReplaceTagBraket(char *pData)
{
	for(int i = 0; i < strlen(pData); i++)
	{
		if(pData[i] == '<')
			pData[i] = '(';
		else if(pData[i] == '>')
			pData[i] = ')';
	}
}

void CSearchPOI::ReplaceTagBraket(CString &strData)
{
	for(int i = 0; i < strData.GetLength(); i++)
	{
		if(strData.GetAt(i) == '<')
			strData.SetAt(i, '(');
		else if(strData.GetAt(i)  == '>')
			strData.SetAt(i, ')');
	}
}

void CSearchPOI::ReplaceSpecialWord(CString &strData)
{
	if(strData.Find("&amp;") < 0)
		strData.Replace("&", "&amp;");
}

void CSearchPOI::CheckWord(CString &strData)
{
	ReplaceTagBraket(strData);
	ReplaceSpecialWord(strData);
}

BOOL CSearchPOI::IsDongAndFullNameMatch()
{
	if(pPOI->IsDongPOI())
	{
		if(pPOI->m_nClass <= PN_SAME_NAME_DONG && nDongMatchType == 10 ||
			pPOI->m_nClass > PN_SAME_NAME_DONG)
		{
			return TRUE;
		}
	}

	return FALSE;
}