#include "StdAfx.h"
#include "tinyxml.h"
#include "LoadInsurance.h"
#include "WinInet.h"
#include "UTF8Conv.h"


#define LOAD_INSRUANCE_URL "www.wingbody.kr"

#define GET_ELEMENT_TEXT(x, y) LF->UTF8ToANSI(x->FirstChildElement(y)->GetText());
#define GET_ELEMENT_INT(x, y) atoi(LF->UTF8ToANSI(x->FirstChildElement(y)->GetText()));

CLoadInsurance::CLoadInsurance(long nType, CLoadInsuranceData *st, CString strEtc)
{
	m_nType = nType;
	m_stLoadInsurance = st;
	//EnCodeStr() 안맞음

	if(m_nType == LOAD_INS_INSERT)
	{
		m_strUrl.Format("rogi/_rogiL.php?proc=rogi_&rogiCompanyNum=10&a1=%s&a2=%s&a3=%s&a4=%s&a5=%s&a6=&a7=&a8=&a9=%d&a10=%s&a11=%s",
			LF->ConvertStringToSendData(st->strCompanyName), LF->GetStringFromLong(st->nRNo), LF->ConvertStringToSendData(st->strRiderName), st->strSSN, st->strPhone, st->nCarType, LF->ConvertStringToSendData(st->strCarNo), "1");
	}
	else if(m_nType == LOAD_INS_DELETE)
	{
		m_strUrl.Format("rogi/_rogiL.php?proc=rogi_&rogiCompanyNum=10&a1=%s&a2=%s&a3=%s&a4=%s&a5=%s&a6=&a7=&a8=&a9=%d&a10=%s&a11=%s",
			LF->ConvertStringToSendData(st->strCompanyName), LF->GetStringFromLong(st->nRNo), LF->ConvertStringToSendData(st->strRiderName), st->strSSN, st->strPhone, st->nCarType, LF->ConvertStringToSendData(st->strCarNo), "2");
	}
	else if(m_nType == LOAD_INS_SEARCH)
	{
		m_strUrl.Format("rogi/_logiNameRead.php?proc=rogi_&a4=%s", st->strSSN);
	}
	
	m_strEtc = strEtc;
}
 
CLoadInsurance::~CLoadInsurance(void)
{
}


BOOL CLoadInsurance::Open()
{
	//http://www.wingbody.kr/rogi/_rogiL.php?proc=rogi_&rogiCompanyNum=10&a1=소속업체명&a2=101&a3=최종철&a4=820218-1069017&a5=010-8720-4162&a6=2016-12-01&a7=종기일자&a8=보험사&a9=1&a10=ㅇㅀㅇㄹ&a11=1
	LPCTSTR accept[2]={ _T("*/*"), NULL };

	HINTERNET hInternet = InternetOpen( _T("HTTP"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );
 
	HINTERNET hConnect = InternetConnect( hInternet, LOAD_INSRUANCE_URL, INTERNET_DEFAULT_HTTP_PORT, 
																	 NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0 );

	HINTERNET hRequest = HttpOpenRequest( hConnect, _T("POST"),m_strUrl, NULL, NULL, accept, 
														   INTERNET_FLAG_DONT_CACHE, 0 );

	//HINTERNET hRequest = HttpOpenRequest( hConnect, _T("POST"),"rogi/_rogiL.php?proc=rogi_&rogiCompanyNum=10&a1=소속업체명&a2=101&a3=최종철&a4=820220-1069017&a5=010-8720-4162&a6=2016-12-01&a7=종기일자&a8=보험사&a9=1&a10=ㅇㅀㅇㄹ&a11=1", NULL, NULL, accept, 
	//																   INTERNET_FLAG_DONT_CACHE, 0 );
 
	HttpSendRequest( hRequest, NULL, 0, NULL, 0 );

	DWORD dwSize = 0; 
	BOOL bQuery = InternetQueryDataAvailable( hRequest, &dwSize, 0, 0 );

	CString strText;

	char* szXml;
	
	if ( bQuery && dwSize > 0 )
	{

		DWORD dwTotal = 0;
		char* pData = (char*)malloc( dwTotal + dwSize + 1 );
		while ( pData && dwSize ) 
		{ 
			DWORD dwRead = 0;
			InternetReadFile( hRequest, pData+dwTotal, dwSize, &dwRead );
			dwTotal += dwRead;
			pData[dwTotal] = NULL;
			InternetQueryDataAvailable( hRequest, &dwSize, 0, 0 );
			if ( dwSize > 0 )
			{ 
				pData = (char*)realloc( pData, dwTotal + dwSize+1 );
			}

			//szXml = UTF8ToANSI(pData);

			szXml = pData;
			
			//strText.Format("%s", pData);
			//UTF8Conv(pData);
		}
	}

	InternetCloseHandle( hRequest );
	InternetCloseHandle( hConnect );
	InternetCloseHandle( hInternet );

	if(m_nType == LOAD_INS_INSERT || m_nType == LOAD_INS_DELETE)
		return ParseXmlInsertDelete(szXml);
	else if(m_nType == LOAD_INS_SEARCH)
		return ParseXmlSearch(szXml);

	return FALSE;
}

BOOL CLoadInsurance::ParseXmlInsertDelete(char *sz)
{
	TiXmlDocument doc;
	doc.Parse(sz);

	TiXmlElement *pRoot = doc.FirstChildElement("values");
	if(!pRoot) 
	{
		m_stLoadInsurance->strErrorMsg = "보험사로부터 정보를 읽어어지 못했습니다";
		return FALSE;
	}

	TiXmlElement *pFirst = pRoot->FirstChildElement("item");
	if(!pFirst) 
	{
		m_stLoadInsurance->strErrorMsg = "보험사로부터 정보를 읽어어지 못했습니다";
		return FALSE;
	}

	m_stLoadInsurance->strCompanyName = GET_ELEMENT_TEXT(pFirst, "a1");
	m_stLoadInsurance->nRNo = GET_ELEMENT_INT(pFirst, "a2");
	m_stLoadInsurance->strRiderName = GET_ELEMENT_TEXT(pFirst, "a3");
	m_stLoadInsurance->strSSN = GET_ELEMENT_TEXT(pFirst, "a4");
	m_stLoadInsurance->strPhone = GET_ELEMENT_TEXT(pFirst, "a5");
	m_stLoadInsurance->strStartDate = GET_ELEMENT_TEXT(pFirst, "a6");
	//a7 종료일 필요없음
	m_stLoadInsurance->strInsuranceCompany = GET_ELEMENT_TEXT(pFirst, "a8");
	m_stLoadInsurance->nCarType = GET_ELEMENT_INT(pFirst, "a9");
	m_stLoadInsurance->strCarNo = GET_ELEMENT_TEXT(pFirst, "a10");
	m_stLoadInsurance->nWorkState = GET_ELEMENT_INT(pFirst, "a11");//수정해서 내려옴
	m_stLoadInsurance->inputWdate = GET_ELEMENT_TEXT(pFirst, "inputWdate");
	m_stLoadInsurance->rogiCerti = GET_ELEMENT_TEXT(pFirst, "rogiCerti");
	m_stLoadInsurance->message = GET_ELEMENT_TEXT(pFirst, "message");

	long nRet = GET_ELEMENT_INT(pFirst, "b1");

	//등록혹은 해지 시도했던 모든 로그를 남긴다.

	CMkCommand cmd(m_pMkDb, "insert_load_insurance_log");
	cmd.AddParameter(m_stLoadInsurance->strCompanyName);
	cmd.AddParameter(m_stLoadInsurance->nRiderCompany);
	cmd.AddParameter(m_stLoadInsurance->nRNo);
	cmd.AddParameter(m_stLoadInsurance->strRiderName);
	cmd.AddParameter(m_stLoadInsurance->strSSN);
	cmd.AddParameter(m_stLoadInsurance->strPhone);
	cmd.AddParameter(m_stLoadInsurance->strStartDate);
	cmd.AddParameter(m_stLoadInsurance->strInsuranceCompany);
	cmd.AddParameter(m_stLoadInsurance->nCarType);
	cmd.AddParameter(m_stLoadInsurance->nWorkState);
	cmd.AddParameter(m_stLoadInsurance->inputWdate);
	cmd.AddParameter(m_stLoadInsurance->rogiCerti);
	cmd.AddParameter(m_stLoadInsurance->message);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);
	cmd.AddParameter(m_strEtc);

	cmd.Execute();

	if(nRet != 1) //등록 혹은 해지 실패
	{ 
		m_stLoadInsurance->strErrorMsg = GET_ELEMENT_TEXT(pFirst, "message");
		return FALSE;
	}

	return TRUE;
}


BOOL CLoadInsurance::ParseXmlSearch(char *sz)
{
	TiXmlDocument doc;
	doc.Parse(sz);

	TiXmlElement *pRoot = doc.FirstChildElement("values");
	if(!pRoot) 
	{
		m_stLoadInsurance->strErrorMsg = "보험사로부터 정보를 읽어어지 못했습니다";
		return FALSE;
	}

	TiXmlElement *pFirst = pRoot->FirstChildElement("item");
	if(!pFirst) 
	{
		m_stLoadInsurance->strErrorMsg = "적재물 보험에 가입 되어있지 않습니다";
		return FALSE; // 보험에 가입되어 있지않은거임
	}
	//#define SET_CHECK(x, y)  ((CButton*)GetDlgItem(x))->SetCheck(m_info.y);


	m_stLoadInsurance->strCompanyName = GET_ELEMENT_TEXT(pFirst, "a1");
	m_stLoadInsurance->nRNo = GET_ELEMENT_INT(pFirst, "a2");
	m_stLoadInsurance->strRiderName = GET_ELEMENT_TEXT(pFirst, "a3");
	m_stLoadInsurance->strSSN = GET_ELEMENT_TEXT(pFirst, "a4");
	m_stLoadInsurance->strPhone = GET_ELEMENT_TEXT(pFirst, "a5");
	m_stLoadInsurance->strStartDate = GET_ELEMENT_TEXT(pFirst, "a6");
	//a7 종료일 필요없음
	m_stLoadInsurance->strInsuranceCompany = GET_ELEMENT_TEXT(pFirst, "a8");
	m_stLoadInsurance->nCarType = GET_ELEMENT_INT(pFirst, "a9");
	m_stLoadInsurance->strCarNo = GET_ELEMENT_TEXT(pFirst, "a10");
	m_stLoadInsurance->nWorkState = GET_ELEMENT_INT(pFirst, "a11");

	m_stLoadInsurance->inputWdate = GET_ELEMENT_TEXT(pFirst, "inputWdate");
	m_stLoadInsurance->rogiCerti = GET_ELEMENT_TEXT(pFirst, "rogiCerti");
	m_stLoadInsurance->message = GET_ELEMENT_TEXT(pFirst, "message");
	
	return TRUE;
}

void CLoadInsurance::UTF8Conv(LPCTSTR lpsz)
{
	UTF8_CONVERSION;
	LPSTR utf8 = T2UTF8(lpsz);

	UTF8_CONVERSION_EX;
	LPSTR utf9 = T2UTF8_EX(lpsz);

	// Do something with utf8
	//...
}

CString CLoadInsurance::GetInsCarTypeString(long nCarType)
{
	if(nCarType == 1) return "오토바이";
	else if(nCarType == 2) return "소형화물";
	else if(nCarType == 3) return "지하철";

	return "N/A";
}

long CLoadInsurance::GetCarTypeForLoadIns(long nCarType)
{
	if(nCarType == CAR_AUTO || nCarType == CAR_BIGBIKE)
		return LOAD_INS_CAR_TYPE_BIKE;
	else if(nCarType == CAR_SUBWAY)
		return LOAD_INS_CAR_TYPE_SUBWAY;
	else
		return LOAD_INS_CAR_TYPE_CAR;
}

BOOL CLoadInsurance::IsAbleCarType(long nCarType)
{
	if(nCarType == CAR_AUTO ||
		nCarType == CAR_BIGBIKE ||
		nCarType == CAR_DAMA ||
		nCarType == CAR_LABO ||
		nCarType == CAR_VAN ||
		nCarType == CAR_SUBWAY ||
		nCarType == CAR_6VAN)
		return TRUE;
	else 
		return FALSE;
}

BOOL CLoadInsurance::IsForceLoadInsuranceRegister(long nCompany)
{
	CMkCommand cmd(m_pMkDb, "is_force_register_loadinsurance");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(nCompany);

	if(!cmd.Execute())
		return FALSE;

	long nRet;
	parRet->GetValue(nRet);

	if(nRet == 1) //강제 적용이 필요함
		return TRUE;

	return FALSE;
}

/*
	st.strCompanyName = m_ci.GetCompanyName(stRider->nCompany);
	st.nRNo = stRider->nRNo;
	st.strPhone = stRider->strPhone;
	st.strCarNo = st->strCarNo;
	st.strRiderName = stRider->strName;
	st.nRiderCompany = stRider->nCompany;
	st.nCarType = CLoadInsurance::GetCarTypeForLoadIns(nCarType);
*/

void CLoadInsurance::CheckRiderStateChange(ST_RIDER_INFO *stRider, long bAdminTable, CString strSSN, long nCarType, CString strCarNo)
{
	CLoadInsuranceData stPreSSN;
	stPreSSN.strSSN = stRider->strSSN1 + stRider->strSSN2;
	CLoadInsurance dPreSSN(LOAD_INS_SEARCH, &stPreSSN, "조회");

	BOOL IsRegister = dPreSSN.Open();

	BOOL bOtherCompanyRegister = LU->IsOtherCompanyRegist(stRider->strSSN1 + stRider->strSSN2, stRider->nCompany, stRider->nRNo);

	if(bAdminTable == FALSE) //퇴사시킬때
	{
		if(IsRegister == FALSE || stPreSSN.nWorkState == LOAD_INS_WORK_STATE_CANCEL) //보험등록아님
		{
		}
		else
		{
			if(!LU->IsOtherCompanyRegist(stRider->strSSN1 + stRider->strSSN2, stRider->nCompany, stRider->nRNo))
			{
				CLoadInsurance d(LOAD_INS_DELETE, &stPreSSN, "기사정보수정 재직->퇴사");

				if(d.Open())
					MessageBox(NULL, "기사정보 수정(퇴직)으로 적재물 보험에 해지되었습니다.", "확인", MB_ICONINFORMATION);
				else				
					MessageBox(NULL, stPreSSN.strErrorMsg, "확인", MB_ICONINFORMATION);
			}
		}
	}
	else
	{
		CString strTemp = "";

		BOOL bNeedPreSSNRelease = FALSE;
		BOOL bNeedNewSSNRegister = FALSE;

		if(stRider->strSSN1 + stRider->strSSN2 != strSSN) 
		{
			bNeedPreSSNRelease = TRUE;
			bNeedNewSSNRegister = TRUE;
			strTemp += "주민번호변경,";
		}
		else if(stPreSSN.nCarType != GetCarTypeForLoadIns(nCarType))
		{
			bNeedPreSSNRelease = TRUE;

			if(IsAbleCarType(nCarType) == TRUE)
				bNeedNewSSNRegister = TRUE;

			strTemp += "차량타입변경,";
		}
		else if(stPreSSN.strCarNo != strCarNo)
		{
			bNeedPreSSNRelease = TRUE;
			bNeedNewSSNRegister = TRUE;		
			strTemp += "차량번호변경,";
		}

		if(IsRegister == FALSE || stPreSSN.nWorkState == LOAD_INS_WORK_STATE_CANCEL) 
		{
			bNeedPreSSNRelease = FALSE;
		}

		BOOL bActionRelease = FALSE;
		BOOL bActionRegister = FALSE;

		if(bNeedPreSSNRelease)
		{
			if(!LU->IsOtherCompanyRegist(stRider->strSSN1 + stRider->strSSN2, stRider->nCompany, stRider->nRNo))
			{
				CLoadInsuranceData stNewSSN;
				stNewSSN.strSSN = stRider->strSSN1 + stRider->strSSN2;
				CLoadInsurance d(LOAD_INS_DELETE, &stNewSSN, "기사정보수정 " + strTemp);
				d.Open();

				bActionRelease = TRUE;
			}			
		}

		if(LU->IsSSNOk(strSSN) == FALSE)
		{
			bNeedNewSSNRegister = FALSE;
		}

		if(bNeedNewSSNRegister)
		{
			if(IsAbleCarType(nCarType))
			{
				CLoadInsuranceData stNewSSN;
				stNewSSN.strSSN = strSSN;
				stNewSSN.strCompanyName = m_ci.GetCompanyName(stRider->nCompany);
				stNewSSN.nRNo = stRider->nRNo;
				stNewSSN.strRiderName = stRider->strName;
				stNewSSN.strPhone = stRider->strID;
				stNewSSN.nCarType = GetCarTypeForLoadIns(nCarType);
				stNewSSN.strCarNo = strCarNo;

				CLoadInsurance d(LOAD_INS_INSERT, &stNewSSN, "기사정보수정 " + strTemp);
				d.Open();

				bActionRegister = TRUE;
			}			
		}		

		if(bActionRelease == TRUE && bActionRegister == TRUE)
			MessageBox(NULL, "기사정보 수정으로 적재물 보험에 해지후 재가입되었습니다", "확인", MB_ICONINFORMATION);
		else if(bActionRelease)
			MessageBox(NULL, "기사정보 수정으로 적재물 보험에 해지 되었습니다", "확인", MB_ICONINFORMATION);
		else if(bActionRegister)
			MessageBox(NULL, "기사정보 수정으로 적재물 보험에 가입 되었습니다", "확인", MB_ICONINFORMATION);

	}
}
