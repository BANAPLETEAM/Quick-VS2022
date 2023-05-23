

#include "stdafx.h"
#include "jibundata.h"
#include "math.h"
#include "KingoHttp.h"

JIBUN_MAP CJibunData::m_JibunMap;

CJibunData::CJibunData(void)
{	
}

CJibunData::~CJibunData(void)
{
}

BOOL CJibunData::LoadJibunData()
{
	if(m_JibunMap.size() > 0)
		return TRUE;

	CMkRecordset pRs;
	if(pRs.OpenFromFile(LF->GetModuleFullPath() + "npoi_jb.dat", TRUE)) 
	{
		for(int i=0; i < pRs.GetRecordCount(); i++)
		{
			JIBUN_STRUCT *pJibun = new JIBUN_STRUCT;

			pRs.GetFieldValue("sSido", pJibun->sSido);
			pRs.GetFieldValue("sGuGun", pJibun->sGugun);
			pRs.GetFieldValue("sDong", pJibun->sDong);
			pRs.GetFieldValue("sSido_Code", pJibun->sSido_Code);
			pRs.GetFieldValue("sGuGun_Code", pJibun->sGugun_Code);
			pRs.GetFieldValue("sDong_Code", pJibun->sDong_Code);

			//if(pJibun->sDong.Find("1가") >= 0)
			//	qsLog.Print("%s%s%s\n", pJibun->sSido, pJibun->sGugun, pJibun->sDong);

			m_JibunMap.insert(JIBUN_MAP::value_type(
				(LPSTR)(LPCTSTR)(pJibun->sSido + pJibun->sGugun + pJibun->sDong), pJibun));
			pRs.MoveNext();
		}
	}

	return (m_JibunMap.size() > 0);
}

int CJibunData::GetJibunPoi(POI_DATA *pDongPoi, CString strLi, int nSan, CString strJibun, int &nX, int &nY)
{
	char buffer[10];
	if(!LoadJibunData())
	{
		return -1;
	}

	CString strFullName;
	strFullName = m_poi.GetDisplayName(pDongPoi);
	strFullName.Replace(" ", "");
	if(strLi.GetLength() > 0)
		strFullName += " " + strLi;

	//qsLog.Print("strFullName=%s\n", strFullName);

	JIBUN_MAP::iterator it = m_JibunMap.find((LPSTR)(LPCTSTR)strFullName);
	if(it == m_JibunMap.end())
	{
		strFullName = m_poi.GetDisplayName(pDongPoi);
		if(strFullName.Right(2) == "가")
		{
			if(LF->IsStringDigit(strFullName.Mid(strFullName.GetLength() - 4, 1)))
			{
				strFullName.Insert(strFullName.GetLength() - 4, "동");
			}
			else
			{
				strFullName.Insert(strFullName.GetLength() - 3, "동");
			}

			strFullName.Replace(" ", "");
			//qsLog.Print("strFullName2=%s\n", strFullName);
			it = m_JibunMap.find((LPSTR)(LPCTSTR)strFullName);
		}
	}


	if(it == m_JibunMap.end())
	{
		return -2;
	}

	return GetJibunPoi(it->second->sSido, it->second->sGugun, it->second->sDong, 
		ltoa(nSan, buffer, 10), strJibun, nX, nY);

	/*
	char buffer[10];
	return GetJibunPoi(it->second->sSido_Code, it->second->sGugun_Code, it->second->sDong_Code, 
	ltoa(nSan, buffer, 10), strJibun, nX, nY);
	*/

}

int CJibunData::GetJibunPoi(CString sAddr,int& nX,int& nY)
{
	nX = nY = 0;
	//http://map.naver.com/search2/local.nhn?query=%EC%84%9C%EC%9A%B8%EC%8B%9C%20%EC%9A%A9%EC%82%B0%EA%B5%AC%20%ED%95%9C%EA%B0%95%EB%A1%9C3%EA%B0%80%2065-228&menu=location

	CKingoHttp http;
	http.SetConnectInfo("map.naver.com",80,"search2/local.nhn",1); //IP,PORT,URL설정
	http.AddParamValue("query",sAddr);
	http.AddParamValue("menu", "location" );

	int  nRet = http.Call();
	if(nRet != 0) {
		//		sErrMsg = "인터넷 에러";
		return 2; //2
	}

	CString sFind("\"x\": \"");
	CString sInfo = (char*)http.GetResponse();

	int nIndex = sInfo.Find(sFind);
	if(nIndex < 0) return 1;	
	nIndex += sFind.GetLength();

	int nEnd = sInfo.Find("\"",nIndex + 1);
	CString sValX = sInfo.Mid(nIndex,nEnd-nIndex);

	sFind = "\"y\": \"";
	nIndex = sInfo.Find(sFind);
	if(nIndex < 0) return 1;	
	nIndex += sFind.GetLength();

	nEnd = sInfo.Find("\"",nIndex+1);
	CString sValY = sInfo.Mid(nIndex,nEnd-nIndex);

	nX = (atof(sValX) * 360000.0) + 773.568;//1000000;
	nY = (atof(sValY) * 360000.0) - 1013.264 ;//1000000;
	return 0;
}

int CJibunData::GetJibunPoi(CString Code_Si,CString Code_Gu,CString Code_Dong,CString nSan,CString sJibun,int& nX,int& nY)
{
	//CString sSan = ("1" == nSan) ? "산": "";
	CString sSan = ("2" == nSan) ? "산": "";
	return GetJibunPoi((Code_Si + " " + Code_Gu + " " + Code_Dong + " " + sSan  + " " +  sJibun ), nX, nY);

	/*
	CKingoHttp http;
	http.SetConnectInfo("www.smartmap.co.kr",80,"map/search_jibun.php",1); //IP,PORT,URL설정
	//http.SetConnectInfo("www.smartmap.co.kr",80,"map/search_list.php",1); //IP,PORT,URL설정
	http.AddParamValue("AdminDo",Code_Si);
	http.AddParamValue("AdminGu",Code_Gu);
	http.AddParamValue("AdminDong",Code_Dong);
	http.AddParamValue("a_san",nSan);
	http.AddParamValue("a_jibun",sJibun);

	int  nRet = http.Call();
	if(nRet != http.Call()) {
	//             sErrMsg = "인터넷 에러";
	return 2; //2
	}

	CString sFind("javascript:goMap(");
	CString sInfo = (char*)http.GetResponse();

	int nIndex = sInfo.Find(sFind);
	if(nIndex < 0) return 1;      

	nIndex += sFind.GetLength();

	int nEnd = sInfo.Find(")",nIndex);

	CString sVal = sInfo.Mid(nIndex,nEnd-nIndex);
	char szTemp1[100];
	char szTemp2[100];
	char szTemp3[100];
	char szTemp4[100]; //어느순간부터 지번도 같이 리턴된다. by mksong 090427
	sVal.Replace(',', ' ');

	sscanf(sVal,"%100s %100s %100s %100s %d %d",szTemp1,szTemp2,szTemp3,szTemp4, &nX,&nY);

	return 0;
	*/
}
