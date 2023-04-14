
#include "stdafx.h"
#include "resource.h"
#include <Iphlpapi.h>
#include "POIData.h"
#include "MakeRcpPower.h"
#include <imm.h> 
#include "MileageInfo.h"
#include "UserDongPos.h"
#include "POIDataNew.h"
#include "CustomerData.h"
#include "MainFrm.h"
#include "BillDlg.h"
#include "LogiMapCns.h"
#include "FakeDlg.h"
#include "CheckGroupReportDlg.h"
#include <math.h>
#include "Wql.h"


#pragma comment( lib, "imm32.lib" )
#pragma comment(lib, "iphlpapi.lib")

#define LINE_BUFFER_SIZE	2048
#define CHECK_TEL_BYPASS   0

ST_USER_INFO m_ui;
CCompanyInfo m_ci;
CSmsDefine m_sms;
ST_ETC_INFO m_ei;
ST_SERVER_INFO m_si;
ARRAY_BRANCH m_ba, m_ba2;

MAP_RIDER m_rm;
CPOIData m_poi;
ARRAY_CALL_ROUTE_SIDO	m_crs;
MAP_DEPOSIT_RATE m_dr;
VEC_CHARGE_SECTION_TYPE m_cst;
CCustomerGroup m_cg;
CMileageInfo m_mi;
CUserDongPos m_mapUDongPos;
MAP_CHARGE_TYPE_NAME m_mapChargeType;
MAP_MEMBER_CHARGE_CNO m_mapMemberCharge1;
MAP_BANK m_mapBank;
CStringArray m_saBranchName;
CMkDatabase *m_pMkDb		= NULL;
CMkDatabase *m_pMkDb2		= NULL;
CMkDatabase *m_pMkDb4DrvLic = NULL;
long m_nSearchPoiDlg = 0;
HINSTANCE m_hCommondll;
CEncProfile encProfile;
char m_szLogPath[512];
MAP_CHARGE2007 m_Charge2007Map;
CGlobalFontManager m_FontManager;
CGlobalHandleManager m_HandleManager;
CMakeRcpPower m_pi;
CLogiUtil *LU;
CLogiFunc *LF;
CBranchInfo *m_pbiCur = NULL;
MAP_LINE_GROUP m_LineGroup;
CPOIDataNew m_poiNew;
CCustomerData m_cus;
MAP_STATE_MENT m_mapStateMent;
COMPANY_APPLY_FROM_CITY_MAP3 m_mapConCitySetting;
MAP_CARD_VENDOR m_mapCardVendor;
MAP_SPECIAL_TRUCK_CHARGE g_special_truck_charge;

char* STR_PAY_TYPE[] = {"����", "����", "�ſ�", "�۱�", "����", "", "", "ī��"};
char* STR_CAR_TYPE[] = {"����", "������", "�ٸ�", "��", "3��", "Ʈ��", "", "", "6��", "1.4��", 
					"����ö", "", "", "", "", "", "", "", "", "",
					"�����ù�"};



BOOL POWER_CHECK(long nPower, CString strPowerName, BOOL bDisplayMsg)
{
	if(m_pi.GetPower(nPower))
		return TRUE;

	if(bDisplayMsg) {
		if(strPowerName.GetLength() > 0) {
			CString strMsg;
			strMsg.Format("[%s] ������ �����ϴ�.", strPowerName);
			AfxGetMainWnd()->MessageBox(strMsg, "���Ѿ���", MB_ICONINFORMATION);
		}
		else {
			AfxGetMainWnd()->MessageBox("���� ������ �����ϴ�.", "���Ѿ���", MB_ICONINFORMATION);
		}
	}
	return FALSE;
}

CString GetInternetReceiptType(int nReceiptType)
{
	if(nReceiptType <= 0)
		return "i";
	else if(nReceiptType == 1)
		return "w";
	else if(nReceiptType == 2)
		return "q";
	else
		return "i";
}

CString GetStateString(UINT nState) 
{
	if(nState == 10) return "����";
	else if(nState == 11) return "����";
	else if(nState == 15) return "�߼�";
	else if(nState == 20) return "����";
	else if(nState == 30) return "����";
	else if(nState == 31) return "�Ⱦ�";
	else if(nState == 35) return "�Ϸ�";
	else if(nState == 40) return "���";
	else if(nState == 60) return "����";
	else if(nState == 70) return "����";
	else if(nState == 72) return "��û";
	else if(nState == 80) return "��������";
	else if(nState == 81) return "������������";
	else if(nState == 90) return "�����˸�";
	else if(nState == 91) return "�����˸�����";
	else if(nState == 92) return "�ڵ���⼳��";
	else if(nState == 93) return "�ڵ��������";
	else if(nState == 2) return "���ͳ�";
	else if(nState == 3) return "����";
	else if(nState == 5) return "�̵�";
	else if(nState == 8) return "���";
	else if(nState == 9) return "����";
	else if(nState == 1) return "����";
	else if(nState == 100) return "����";
	else if(nState == 200) return "����";
	else if(nState == 300) return "�̵�";
	else if(nState == 400) return "���";
	else return "UNKNOWN";
} 

int GetStateFromString(CString sState) 
{
	if(sState == "����") return 10;
	else if(sState == "����") return 11;
	else if(sState == "�߼�") return 15;
	else if(sState == "����") return 20;
	else if(sState == "����") return 30;
	else if(sState == "�Ⱦ�") return 31;
	else if(sState == "�Ϸ�") return 35;
	else if(sState == "���") return 40;
	else if(sState == "����") return 60;
	else if(sState == "����") return 70;
	else if(sState == "��û") return 72;
	else if(sState == "���ͳ�") return 2;
	else if(sState == "����") return 3;
	else if(sState == "�̵�") return 5;
	else if(sState == "���") return 8;
	else if(sState == "����") return 9;
	else if(sState == "����") return 1;
	else if(sState == "����") return 100;
	else if(sState == "����") return 200;
	else if(sState == "�̵�") return 300;
	else if(sState == "���") return 400;

	return 0;
} 


CString GetCarChargeTypeString(long nCarType)
{
	CString sCarType = "";
	if(nCarType == 0 )
		sCarType = "����";
	else if(nCarType == 1 )
		sCarType = "�ٸ�";
	else if(nCarType == 2)
		sCarType = "��";
	else if(nCarType == 3)
		sCarType = "�¿�";
	else if(nCarType == 4)
		sCarType = "Ʈ��";

	return sCarType;
}

int GetCarTypeFromString(CString strCarType)
{
	if(strCarType == "����" || 
		strCarType == "") return 0;
	else if(strCarType == "������" ||
		strCarType == "�����̿������") return 1;
	else if(strCarType == "�ٸ�") return 2;
	else if(strCarType == "��") return 3;
	else if(strCarType == "��") return 4;
	else if(strCarType == "Ʈ��") return 5;
	else if(strCarType == "����ö") return 10;
	else if(strCarType == "�����ù�") return 20;
	else return -1; 
}

BOOL IsCarTypeTruck(long nCarType)
{
	if(nCarType == CAR_TRUCK ||
		nCarType == CAR_1_4_TON ||
		nCarType == CAR_2_5_TON ||
		nCarType == CAR_3_5_TON ||
		nCarType == CAR_5_TON ||
		nCarType == CAR_5_TON_PLUS ||
		nCarType == CAR_8_TON ||
		nCarType == CAR_11_TON ||
		nCarType == CAR_14_TON ||
		nCarType == CAR_15_TON ||
		nCarType == CAR_18_TON ||
		nCarType == CAR_25_TON)
		return TRUE;
	
	return FALSE;
}

CString GetCarTypeFromLong(long nCarType, BOOL bHideBaseType, long nTruckType, CString strTon)
{
	CString car_type = "�˼�����";
	if(nCarType == CAR_AUTO) car_type = bHideBaseType ? "" : "����";
	else if(nCarType == CAR_BIGBIKE) car_type = "������";
	else if(nCarType == CAR_DAMA) car_type = "�ٸ�";
	else if(nCarType == CAR_LABO) car_type = "��";
	else if(nCarType == CAR_VAN) car_type = "3��";
	else if(nCarType == CAR_TRUCK) car_type = "1��";
	else if(nCarType == CAR_1_4_TON) car_type = "1.4��";
	else if(nCarType == CAR_SUBWAY) car_type = "����ö";
	else if(nCarType == CAR_PS) car_type = "�����ù�";
	else if(nCarType == CAR_6VAN) car_type = "6��";		
	else if(nCarType == CAR_2_5_TON) car_type = "2.5��";
	else if(nCarType == CAR_3_5_TON) car_type = "3.5��";
	else if(nCarType == CAR_5_TON) car_type = "5��";
	else if(nCarType == CAR_11_TON) car_type = "11��";
	else if(nCarType == CAR_18_TON) car_type = "18��";
	else if(nCarType == CAR_25_TON) car_type = "25��";
	else if(nCarType == CAR_SEDAN) car_type = "�¿�";
	else if(nCarType == CAR_5_TON_PLUS) car_type = "5����";
	else if(nCarType == CAR_8_TON) car_type = "8��";
	else if(nCarType == CAR_14_TON) car_type = "14��";
	else if(nCarType == CAR_15_TON) car_type = "15��";

	if(nTruckType == CARGO_JABARA)	car_type += "(�ڹٶ�)";
	else if(nTruckType == CARGO_LIFT)	car_type += "(����Ʈ)";
	else if(nTruckType == CARGO_WING_BODY)	car_type += "(���ٵ�)";
	else if(nTruckType == CARGO_LIFT_WING)	car_type += "(����Ʈ��)";
	else if(nTruckType == CARGO_FREEZER)	car_type += "(�õ�)";

	return car_type;
}

CString GetWayTypeFromLong(long nWayType, BOOL bHideBaseType, long nLoadType)
{
	CString strWay;

	if(nWayType == 0)
		strWay = bHideBaseType ? "" : "��";
	else if(nWayType == 1)
		strWay = "�պ�";
	else if(nWayType == 2)
		strWay = "����";
	else
		return "�˼�����";

	if(nLoadType > 0)
	{
		if(strWay.GetLength() > 0)
			strWay = strWay.Left(2) + "/" + "ȥ";
		else
			strWay = "ȥ��";
	}

	return strWay;
}

int GetWayTypeFromString(CString strWayType)
{
	if(strWayType == "�պ�" ||
		strWayType == "��/ȥ")
		return 1;
	else if(strWayType == "����" ||
			strWayType == "��/ȥ")
		return 2;
	else 
		return 0;
}

CString GetPayTypeFromLong(long nPayType, BOOL bHideBaseType, long nCardState)
{
	if(nPayType == 0)
		return bHideBaseType ? "" : "����";
	else if(nPayType == 1)
		return "����";
	else if(nPayType == 2)
		return "�ſ�";
	else if(nPayType == 3)
		return "�۱�";
	else if(nPayType == 4)
		return "��������";
	else if(nPayType == 6)
		return "����";

	else if(nPayType == 7)
	{
		CString sCharge = "", sFaceCard = "";
		sCharge.Format("%d", nCardState);
		if(sCharge.Right(2).Compare("15") == 0)
			sFaceCard = "���";
			//sFaceCard = "(F)";

		if(nCardState < 10)
			return sFaceCard + "ī��";
		if(nCardState < 100)
			return sFaceCard +"ī��(�̰���)";
		if(nCardState > 100 && nCardState < 200)
			return sFaceCard +"ī��(����)";
		if(nCardState > 200 && nCardState < 300)
			return sFaceCard +"ī��(�������)";
	}
	else 
		return "�˼�����";

	return "�˼�����";
}

CString GetRunTypeFromLong(long nRunType, BOOL bHideBaseType)
{
	if(nRunType == ZERO)
		return bHideBaseType ? "" : "�Ϲ�";
	else if(nRunType == ONE)
		return "�ϱ�";
	else if(nRunType == TWO)
		return "���";
	else if(nRunType == FOUR)
		return "Ư��";
	else if(nRunType == EIGHT)
		return "����";
	else  
		return "�˼�����";
}

int GetRunTypeFromString(CString strRunType)
{
	if(strRunType == "�ϱ�")
		return ONE;
	else if(strRunType == "���")
		return TWO;
	else if(strRunType == "Ư���")
		return FOUR;
	else if(strRunType == "����")
		return EIGHT;
	else 
		return ZERO;
}


CString GetReportState(long nReportState)
{
	if(nReportState == 0)
		return "����Ϸ�";
	else if(nReportState == 10)
		return "�κ��Ա�";
	else if(nReportState == 20)
		return "�ԱݿϷ�";

	return "�˼�����";

}

CString GetLicenseStateString(int nType, BOOL *pbLicenseOK)
{
	switch(nType)
	{
	case 0: *pbLicenseOK = TRUE; return "����";
	case 2: *pbLicenseOK = TRUE; return "��ȸ�߿����߻�";
	case -4: *pbLicenseOK = TRUE; return "����(����нǻ���)";
	case -1: *pbLicenseOK = FALSE; return "�����̻�(����or���)";
	case -2: *pbLicenseOK = FALSE; return "�ֹι�ȣ�ͼ��� ����ġ";
	case -3: *pbLicenseOK = FALSE; return "�����ȣ ����";
	case -5: *pbLicenseOK = FALSE; return "���� ����";
	case -6: *pbLicenseOK = FALSE; return "�ֹι�ȣ ����";
	default: *pbLicenseOK = FALSE; return "�˼�����";
	}

	return "�˼�����";
}

UINT GetImageNumber(int nState, int nSubState, int nCTNo)
{
	if(nCTNo > 0)
	{
		if(nState == 8 || nState == 10)
			return 19;
	}

	if(nSubState != 0)
	{
		if(nState == 35 && nSubState == 10)
			return 18;
	}
	switch(nState)
	{
	case 2:	return 8;
	case 3: return 6;
	case 5: return 7;
	case 8: return 9;
	case 9: return 0;
	case 10:return 1;
	case 11:return 2;
	case 15:return 10;
	case 20:return 11;
	case 30:return 3;		
	case 31:return 15;      //�� �Ⱦ�
		//case 32:return 3;		//###�Ⱦ������� �ٸ������� ������
	case 35:return 4;
	case 40:return 5;
	case 60:return 12;
	case 70:return 13;
	case 100: return 14;
	case 101: return 20;
	}
	return 5;
}

BOOL ConnectDrvLicSvr()
{
	if(NULL == m_pMkDb4DrvLic)
	{
		m_pMkDb4DrvLic = new CMkDatabase(g_bana_log);
		BYTE nXorKey = (m_pMkDb4DrvLic->GetXorKey() + 3) % 128;
		BYTE des_key_new[] = {29,44,2,83,32,98,10,8};
		BYTE nXoredKey[8];

		for(int i = 0; i < 8; i++)
			nXoredKey[i] = des_key_new[i] ^ ((nXorKey + i) % 128);
		m_pMkDb4DrvLic->SetServerKey(nXoredKey);


		MSG_LOGIN_INFO info;
		ZeroMemory(&info, sizeof(MSG_LOGIN_INFO));
		info.nCompany = m_ci.m_nCompanyCode;
		info.nWNo = m_ui.nWNo;
		info.nShareCode1 = m_ci.m_nShareCode1;
		info.nShareCode2 = m_ci.m_nShareCode2;
		info.nShareCode3 = m_ci.m_nShareCode3;
		/*info.nShareCode4 = m_ci.m_nShareCode4;
		info.nShareCode5 = m_ci.m_nShareCode5;
		info.nShareCode6 = m_ci.m_nShareCode6;
		info.nShareCode7 = m_ci.m_nShareCode7;
		info.nShareCode8 = m_ci.m_nShareCode8;
		info.nShareCode9 = m_ci.m_nShareCode9;
		info.nShareCode10 = m_ci.m_nShareCode10;*/
		info.nMsgGroupCode = 0;
		strcpy(info.szCompanyName, m_ci.m_strName);
		//strcpy(info.szBranchName, m_ci.m_strBranchName);
		strcpy(info.szUserName, m_ci.m_strName);
		info.bIdle = 0;
		info.bManager =0;
		info.nDisplayType = 0;

		m_pMkDb4DrvLic->SetParentWnd(NULL);
		m_pMkDb4DrvLic->AsyncSelect(0);


		m_pMkDb4DrvLic->SetLoginInfo(&info);
		return m_pMkDb4DrvLic->Open("drvlic.logisoft.co.kr", 4600, TRUE);
		//		return m_pMkDb4DrvLic->Open("localhost", 4600, TRUE);
	}
	else
	{
		BOOL bRet = m_pMkDb4DrvLic->GetSocket()->IsConnected();
		if(FALSE == bRet) m_pMkDb4DrvLic->ConnectServer();
		return  bRet;
	}
}


CString GetMyNumberFormat(CString strNumber) 
{
	strNumber.Replace(",", "");
	CString strData;
	int i, j = 1;

	for(i = strNumber.GetLength(); i > 0 ; i--)
	{
		strData = strNumber.GetAt(i - 1) + strData;
		if((j % 3) == 0 && i > 1)
		{
			if(i == 2 && strNumber.GetAt(0) == '-')
				continue;

			strData = "," + strData;
		}
		j++;
	}   
	/*
	TCHAR szOut[20];
	const NUMBERFMT nFmt = { 0, 0, 3, ".", ",", 0 };
	GetNumberFormat(NULL, NULL, (LPCTSTR)strNumber, &nFmt, szOut, 32 );
	return CString(szOut);
	*/
	return strData;
}

CString GetWeekChartTitle(COleDateTime dtDate)
{
	COleDateTime dtTemp = dtDate;
	CString strTemp;
	if (dtTemp.GetDayOfWeek() == 1)
	{
		COleDateTimeSpan dtSpan(6, 0, 0, 0);
		COleDateTime dt = dtTemp + dtSpan;
		strTemp.Format("%d/%02d - %02d", dtTemp.GetMonth(), dtTemp.GetDay(), dt.GetDay());
	}
	else
	{
		COleDateTimeSpan dtSpan(1, 0, 0, 0);
		COleDateTime dt = dtTemp - dtSpan;
		while (dt.GetDayOfWeek() != 1)
		{
			dt = dt - dtSpan;
		}
		while (dtTemp.GetDayOfWeek() != 7)
		{
			dtTemp = dtTemp + dtSpan;
		}

		strTemp.Format("%d/%02d - %02d", dt.GetMonth(), dt.GetDay(), dtTemp.GetDay());
	}
	return strTemp;
}


CString GetMyNumberFormat(long nNumber)
{
	CString strNumber;
	strNumber.Format("%d", nNumber);
	return GetMyNumberFormat(strNumber);
}

long GetMyUnNumberFormat(CString strCharge)
{
	int nSub = 1;
	CString strTempCharge = "0", strSub = "";
	strTempCharge = strCharge;
	strTempCharge.Replace(",", "");
	strSub = strTempCharge.Left(1);
	if(strSub.Compare("-") == 0)
	{
			nSub = -1;
			strTempCharge.Replace("-","");
	}
	if(! IsStringDigit(strTempCharge))
		return 0;

	return atol(strTempCharge) * nSub;
}

long GetMyUnNumberFormatEdit(CWnd *pWnd)
{

	CString strEditValue = "";
	CEdit *pEdit = (CEdit*)pWnd;
	pEdit->GetWindowText(strEditValue);
	if(strEditValue.GetLength() <= 0)
		return 0;

	return GetMyUnNumberFormat(strEditValue);
}

CString GetMyNumberFormatEdit(CWnd *pWnd)
{
	CString strEditValue = "";
	CEdit *pEdit = (CEdit*)pWnd;
	pEdit->GetWindowText(strEditValue);
	if(strEditValue.GetLength() <= 0)
		return "";
	return GetMyNumberFormat(GetMyUnNumberFormat(strEditValue));	
}

CString GetEditString(CWnd *pWnd)
{
	CString strEditValue = "";
	CEdit *pEdit = (CEdit*)pWnd;
	pEdit->GetWindowText(strEditValue);
	if(strEditValue.GetLength() <= 0)
		return "";

	return strEditValue;
}

CString GetModuleFullPath()
{
	CString strFullPath;
	TCHAR szFullPath[MAX_PATH];
	if (GetModuleFileName(AfxGetInstanceHandle(), szFullPath, _MAX_PATH) > 0)
	{
		int nPos;
		strFullPath = szFullPath;
		if ((nPos = strFullPath.ReverseFind('\\')) != -1)
			strFullPath = strFullPath.Mid(0, ++nPos);
	}

	return strFullPath;
}

CString GetMyFileName()
{
	TCHAR szFullPath[MAX_PATH];
	if(GetModuleFileName(AfxGetInstanceHandle(), szFullPath, _MAX_PATH) > 0)
	{
		return szFullPath;
	}

	return "";
}

CString GetDashPhoneNumberRemoveDDD(CString strPhoneNumber)
{
	if(strPhoneNumber.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
		strPhoneNumber = strPhoneNumber.Right(strPhoneNumber.GetLength() - m_ci.m_strDDD.GetLength());

	return GetDashPhoneNumber(strPhoneNumber);
}



void MyTokenize(CString strInput, CString strDivide, BOOL bEpthyInsert, CStringArray &strArr)
{

	CString resToken;
	int curPos= 0;


	resToken= strInput.Tokenize(",",curPos);
	strArr.Add(resToken);
	while (resToken != "")
	{	
		CString strTemp = "";
		strTemp = strInput.Mid(curPos,1  );
		if(strTemp == "," && bEpthyInsert && strInput.Mid(curPos + 1).GetLength() > 0)
		{
			strArr.Add("");
			curPos += 1;
		}
		else
		{
			resToken = strInput.Tokenize(",",curPos);	
			if(strTemp == "" && resToken == "")
				break;
			else
				strArr.Add( resToken);
		}
	};


}


char* UTF8ToANSI(const char *pszCode)
{
	BSTR    bstrWide;
	char*   pszAnsi;
	int     nLength;

	nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, lstrlen(pszCode) + 1, NULL, NULL);
	bstrWide = SysAllocStringLen(NULL, nLength);

	MultiByteToWideChar(CP_UTF8, 0, pszCode, lstrlen(pszCode) + 1, bstrWide, nLength);

	nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
	pszAnsi = new char[nLength];

	WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
	SysFreeString(bstrWide);

	return pszAnsi;
} 

BOOL WriteRegistryInt(HKEY hKey, CString strSubKey, CString strValueKey, int nValue)
{
	CString strValue = _T("");
	HKEY hSubKey = NULL;

	if(::RegOpenKeyEx(hKey, (LPCSTR)strSubKey, 0, KEY_ALL_ACCESS, &hSubKey) == ERROR_SUCCESS)
	{
		::RegSetValueEx(hSubKey, (LPCSTR)strValueKey, NULL, REG_DWORD, (LPBYTE)&nValue, sizeof(int)); 
		::RegCloseKey(hSubKey);

		return TRUE;
	}
	return FALSE;
}

CString GetDashPhoneNumber(CString strPhoneNumber) 
{
	CString strNumber = strPhoneNumber;

	strNumber.Remove('-');

	if(strNumber.GetLength() > 6)
	{
		int nOffset = 0, nRightLen;

		if(strNumber.Left(2) == "02") {
			nOffset = 3;
			strNumber.Insert(2, "-");
		}
		else if(strNumber.GetAt(0) == '0') {
			nOffset = 4;
			strNumber.Insert(3, "-");
		}

		nRightLen = strNumber.FindOneOf("~,./") != -1 ? 
			strNumber.FindOneOf("~,./") : strNumber.GetLength();

		if(nRightLen > 4) strNumber.Insert(nRightLen - 4, "-");
	}		

	return strNumber;
}


CString GetSMSTelUse(int nState)
{
	CString strState = "";
	switch(nState)
	{
	case 0:
		strState = "";
		break;
	case 1:
		strState = "��";
		break;
	case 2:
		strState = "X";
		break;

	}
	return strState;
}

CString GetSMSTelCorp(int nState)
{
	CString strState = "";
	switch(nState)
	{
	case 0:
		strState = "";
		break;
	case 1:
		strState = "�����";
		break;
	case 2:
		strState = "����";
		break;

	}
	return strState;
}

CString GetSMSTelecomState(int nState)
{
	CString strState = "";
	switch(nState)
	{
	case 0:
		strState = "";
		break;
	case 1:
		strState = "����";
		break;
	case 2:
		strState = "����";
		break;

	}
	return strState;
}

CString GetSMSFileStateType(int nState, int nTelType)
{
	CString strState = "";
	switch(nState)
	{
	case 0:
		strState = "";
		break;
	case 1:
		strState = "�̽���";
		break;
	case 2:
		strState = "��������";
		break;
	case 3:
		if(nTelType == 3)
			strState = "-";
		else
			strState = "����";
		break;
	case 4:
		strState = "�ݷ�";
		break;
	case 5:
		strState = "";
		break;

	case 6:
		strState = "����";
		break;
	case 7:
		strState = "����";
		break;
	case 8:
		strState = "����";
		break;
	}
	return strState;
}

long GetStringLengthByAscII(CString strText)
{
	char *ch = (LPSTR)((LPCTSTR)strText);

	long i=0;
	float j=0;

	while(ch[i] != '\0')
	{
		if(ch[i] < 0)
			j+= 0.5;
		else
			j++;

		i++;
	}
	//while(c)
	return (long)j;
}

CString GetNoneDashNumberRemoveDDD(CString strPhoneNumber)
{
	CString strNumber = strPhoneNumber;
	strNumber.Remove('-');

	if(strNumber.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
	strNumber = strNumber.Right(strNumber.GetLength() - m_ci.m_strDDD.GetLength());

	return strNumber;
}

CString GetNoneDashNumber(CString strPhoneNumber)
{
	CString strNumber = strPhoneNumber;
	strNumber.Remove('-');
	return strNumber;
}

BOOL IsStringDigit(CString strText)
{
	for(int i = 0; i < strText.GetLength() ; i++) 
		if(!isdigit((::byte)strText.GetAt(i))) 
			return FALSE;

	return TRUE;
}

CString GetWebUploadUrl(CString strUseage, LONG nTNo)
{
	CMkCommand cmd(m_pMkDb, "OTPInfo_sid_select");
	cmd.AddParameter(m_ui.strID);
	cmd.AddParameter(strUseage);
	cmd.AddParameter(nTNo);
	CMkParameter *pOTP = cmd.AddParameter(typeString, typeOutput, 10, "");
	CMkParameter *pExecuteInfo = cmd.AddParameter(typeString, typeOutput, 300, "");
	CMkParameter *pOutReason = cmd.AddParameter(typeString, typeOutput, 300, "");

	if(!cmd.Execute())
		return "";

	CString strUrl;
	pExecuteInfo->GetValue(strUrl);
	return strUrl;
}


BOOL IsPhoneNumber(CString strText)
{
	for(int i = 0; i < strText.GetLength() ; i++) {
		if((::byte)strText.GetAt(i) != '-' && !isdigit((::byte)strText.GetAt(i))) {
			return FALSE;
		}
	}

	return TRUE;
}

BOOL IsSoftIce95()
{
	HANDLE hFile; 
	char fname[5];
	char fullname[10];

	// Form the text SICE without characters that the hacker could see. 
	fname[0] = 0x53;
	fname[1] = 0x49;
	fname[2] = 0x43;
	fname[3] = 0x45;
	fname[4] = 0x0;

	// "\\.\SICE"
	strcpy(fullname, "\\\\.\\");
	strcat(fullname, fname);

	// "\\.\SICE" without escape stuff
	hFile = CreateFile(fullname, 
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if( hFile != INVALID_HANDLE_VALUE )
	{
		CloseHandle(hFile);
		return TRUE;
	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////
//
// See if SoftICE version 3.x for Windows NT is loaded
//
BOOL IsSoftIceNT()
{
	HANDLE hFile; 
	char fname[6], fullname[10];

	fname[0] = 'N'; // 'N';
	fname[1] = 0x54;
	fname[2] = 0x49;
	fname[3] = 0x43;
	fname[4] = 0x45;
	fname[5] = 0x0;

	// "\\.\NTICE"
	strcpy(fullname, "\\\\.\\");
	strcat(fullname, fname);

	// "\\.\NTICE" without escape stuff
	hFile = CreateFile(fullname,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if( hFile != INVALID_HANDLE_VALUE )
	{
		CloseHandle(hFile);
		return TRUE;
	}
	return FALSE;
}

int AFXAPI MsgBox(CString strMsg, CString strCaption, UINT nType)
{
	return ::MessageBox(NULL, (LPCTSTR)strMsg, (LPCTSTR)strCaption, nType | MB_TOPMOST);
}

int AFXAPI MsgBox(UINT nIDPrompt, CString strCaption, UINT nType)
{
	CString string;
	if (!string.LoadString(nIDPrompt))
	{
		TRACE(traceAppMsg, 0, "Error: failed to load message box prompt string 0x%04x.\n",
			nIDPrompt);
		ASSERT(FALSE);
	}
	return ::MessageBox(NULL, (LPCTSTR)string, (LPCTSTR)strCaption, nType | MB_TOPMOST);
}

BOOL GetFileVersion(char *filename, VS_FIXEDFILEINFO *pvsf)
{
	DWORD dwHandle;
	DWORD cchver = GetFileVersionInfoSize(filename,&dwHandle);
	if (cchver == 0) 
		return FALSE;
	char* pver = new char[cchver];
	BOOL bret = GetFileVersionInfo(filename,dwHandle,cchver,pver);
	if (!bret) 
		return FALSE;
	UINT uLen;
	void *pbuf;
	bret = VerQueryValue(pver,"\\",&pbuf,&uLen);
	if (!bret) 
		return FALSE;
	memcpy(pvsf,pbuf,sizeof(VS_FIXEDFILEINFO));
	delete[] pver;
	return TRUE;
}

BOOL RunProgram(CString strFileName, CString strArg)
{
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;

	if(!strArg.IsEmpty())
		strFileName += " " + strArg;

	BOOL fSuccess = CreateProcess(NULL, (LPSTR)(LPCTSTR)strFileName, NULL, NULL, 0, 
		CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);

	if(fSuccess) {
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}
	return fSuccess;
}

void StatusText(UINT nPane, CString strMsg)
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	((CStatusBar*)pFrame->GetStatusBar())->SetPaneText(nPane, strMsg);
	pFrame->SetStatusAccessTime(GetTickCount());
}

void StatusText(UINT nPane, UINT nResource)
{
	CString string;
	if (!string.LoadString(nResource)) {
		TRACE(traceAppMsg, 0, 
			"Error: failed to load message box prompt string 0x%04x.\n", 
			nResource);
		ASSERT(FALSE);
	}
	StatusText(nPane, string);
}

char* MAKESTRING(UINT nResource)
{
	CString string;
	if (!string.LoadString(nResource)) {
		TRACE(traceAppMsg, 0, 
			"Error: failed to load message box prompt string 0x%04x.\n", 
			nResource);
		ASSERT(FALSE);
	}

	char *szMsg = new char[string.GetLength()];
	strcpy(szMsg, (LPSTR)(LPCTSTR)string);
	return szMsg;
}

/*
// Prints the MAC address stored in a 6 byte array to stdout
CString FormatMacAddress(unsigned char MACData[])
{
CString strTemp;
strTemp.Format("%02X-%02X-%02X-%02X-%02X-%02X", 
MACData[0], MACData[1], MACData[2], MACData[3], MACData[4], MACData[5]);
return strTemp;
}
*/
BOOL GetMacAddress(BOOL bShowMsg)
{
	m_ei.strMac1 = "";
	m_ei.strMac2 = "";

	DWORD sizeReq = 0 ;
	PMIB_IFTABLE pInfo = NULL;
	// Get size information
	::GetIfTable(NULL, &sizeReq, FALSE) ;

	// Allocate required memory
	pInfo = (PMIB_IFTABLE) new BYTE [sizeReq] ;
	memset (pInfo, 0, sizeReq) ;

	DWORD sizeToUse = sizeReq ;

	// Retrieve network interface information
	bool result = ( ::GetIfTable( (PMIB_IFTABLE)pInfo, 
		&sizeToUse, FALSE) == NO_ERROR );
	if( !result )
	{
		delete (PMIB_IFTABLE)pInfo;
		pInfo = NULL;
		//	printf(
		//	"Couldn't retrieve network interface information!");
		return false;
	}

	// Print all interface information 
	for( unsigned int index = 0; index < 
		((PMIB_IFTABLE)pInfo)->dwNumEntries; index ++ )
	{
		// Get interface description
		MIB_IFROW& details = ((PMIB_IFTABLE)pInfo)->table[index];

		if(details.dwType != IF_TYPE_ETHERNET_CSMACD &&
			details.dwType != IF_TYPE_IEEE80211)
			continue;

		// Format physical address
		char macStr[30], szDescript[MAX_PATH];
		DWORD j = 0, k = 0;
		for (j = 0 ; j < details.dwPhysAddrLen ; ++j)
		{
			sprintf( &macStr[j*3], "%02X-", details.bPhysAddr[j] );
		}

		for (k = 0 ; k < details.dwDescrLen ; k++)
		{
			sprintf(&szDescript[k], "%c", details.bDescr[k]);
		}
		if(j > 0 )
			macStr[j*3-1] = '\0';
		szDescript[k] = 0;

		if(bShowMsg)
		{
			CString strMsg;
			strMsg.Format("mac=%s, desc=%s\n\n", macStr, szDescript);
			AfxMessageBox(strMsg);		
		}

		CString strDesc = szDescript;

		if(strDesc.Find("QoS") >= 0)
		{
			continue;
		}

		strDesc.MakeUpper();
		if(strDesc.Find("WAN") >= 0 || 
			strDesc.Find("BLUETOOTH") >= 0)
		{
			continue;
		}

		g_bana_log->Print("%d)mac:%s, desc:%s, operstatus:%d, speed:%d, dwType:%d\n\n", index, macStr, szDescript, details.dwOperStatus, 
			details.dwSpeed, details.dwType);


		if(j > 0)
		{	 
			// Print out physical address
			if(m_ei.strMac1.IsEmpty())
				m_ei.strMac1 = macStr;
			else if(m_ei.strMac1 != macStr && m_ei.strMac2.IsEmpty())
				m_ei.strMac2 = macStr;
		}
	}

	delete (PMIB_IFTABLE)pInfo;
	return true;
}

BOOL IsExceptionDetailDongUse(CPOIUnit *pDong)
{
	if(pDong->IsDongPOI() && 
		( pDong->GetGugun().Compare("���α�") == 0 ||  pDong->GetGugun().Compare("�߱�") == 0))
	{
		return TRUE;
	}

	return FALSE;
}

CString GetHddId()
{
	std::map<CString, CString> m;

	CWql wql;
	BOOL bRet = TRUE;
	do
	{
		//bRet = wql.Open("SELECT SerialNumber,Partitions FROM Win32_DiskDrive");
		bRet = wql.Open("SELECT Tag, SerialNumber FROM Win32_PhysicalMedia");
		
		if (FALSE == bRet) {
			break;
		}
		

		while (TRUE) {
			bRet = wql.MoveNext();
			if (FALSE == bRet) {
				break;
			}

			CString sHDD_Serial;
			CString tag;
			BOOL read_serail = wql.GetValue("SerialNumber", sHDD_Serial);
			BOOL reag_tag = wql.GetValue("Tag", tag);

			if (read_serail && reag_tag){// && tag == "\\\\.\\PHYSICALDRIVE0") {
				sHDD_Serial.Replace(" ", "");
				m.insert(std::make_pair(tag, sHDD_Serial));
				//return sHDD_Serial;
			}
		}

	} while(0);

	if (m.size() > 0)  
		return m.begin()->second;

	return "";
}	

CString FormatString(const char* format, ...)
{
	TCHAR line[LINE_BUFFER_SIZE];

	va_list ap;
	va_start(ap, format);
	_vsnprintf(line, LINE_BUFFER_SIZE, format, ap);
	va_end(ap);
	return CString(line);
}

void AddSecurityLog(long nCompany, long nType, long nStaffNo, 
					CString strData1, CString strData2, CString strData3)
{
	CString strUserInfo = m_ui.strName + "/" + m_ui.strID;
	CString strHddId = GetHddId();
	CString strMacInfo = m_ei.strMac1 + "/" + m_ei.strMac2;
	CString strHostName = GetHostName();

	CMkCommand pCmd(m_pMkDb, "insert_security_log_1");
	pCmd.AddParameter(nCompany);
	pCmd.AddParameter(nType);
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(strUserInfo);
	pCmd.AddParameter(m_ci.m_strName);
	pCmd.AddParameter(strHddId);
	pCmd.AddParameter(m_ui.dtLoginTime);
	pCmd.AddParameter(strMacInfo);
	pCmd.AddParameter(strHostName);
	pCmd.AddParameter("");
	pCmd.AddParameter(m_ei.nPCNum);
	pCmd.AddParameter(strData1);
	pCmd.AddParameter(strData2);
	pCmd.AddParameter(strData3);
	pCmd.Execute();
}

void AddSecurityLog(long nCompany, long nType, long nStaffNo, long nData)
{
	char buffer[20];
	AddSecurityLog(nCompany, nType, nStaffNo, ltoa(nData, buffer, 10), "", "");
}

void AddSecurityLog(long nCompany, long nType, long nData)
{
	char buffer[20];
	AddSecurityLog(nCompany, nType, m_ui.nWNo, ltoa(nData, buffer, 10), "", "");
}

int CheckSum(void *buffer, int nLen)
{
	::byte *byBuffer = (::byte*) buffer;
	int nSum = 77;

	for(int i = 0; i < nLen; i++)
		nSum += (::byte)byBuffer[i];

	return nSum;
}

CString RemoveZero(long nData)
{
	char buffer[10];
	return RemoveZero(itoa(nData, buffer, 10));
}	

CString RemoveZero(CString strData)
{
	if(strData == "0") return "";
	else return strData;
}	

BOOL CreateShortcut(const CString Target, const CString LinkFileName)
{
	HRESULT hres;
	char szPath[MAX_PATH];
	CString Link;

	SHGetSpecialFolderPath(NULL, szPath, CSIDL_DESKTOP, FALSE);
	Link = szPath;
	Link += "\\";
	Link += LinkFileName;

	IShellLink* psl;
	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*) &psl);
	if (SUCCEEDED(hres))
	{
		IPersistFile* ppf;

		psl->SetPath(Target);
		hres = psl->QueryInterface( IID_IPersistFile, (LPVOID *) &ppf);

		if (SUCCEEDED(hres))
		{
			CString Temp = Link;
			Temp.MakeLower();
			if (Temp.Find(".lnk")==-1)
				Link += ".lnk";  // Important !!!
			WORD wsz[MAX_PATH];
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, Link, -1, (LPWSTR)wsz,MAX_PATH);

			hres = ppf->Save((LPCOLESTR)wsz, TRUE);

			ppf->Release();
		}
		psl->Release();
	}

	return hres;
}

BOOL IsBrokenHangul(CString &strText)
{
	int nCount = 0;
	for(int i = 0; i < strText.GetLength(); i++) {
		if(_istlead(strText.GetAt(i))) {
			nCount++;
		}
	}

	if(nCount % 2 == 0)
		return FALSE;
	else 
		return TRUE;
}

CString GetPDATypeString(int nType)
{
	switch(nType)
	{
	case PDA_V100:
		return "����V100";
	case PDA_XG:
		return "����XG";
	case PDA_MITS330:
		return "����330";
	case PDA_MITS3300: 
		return "����3300";
	case PDA_MITS400:
		return "����400";
	case PDA_MITS4000: 
		return "����4000";
	case PDA_POZ_SKT:
		return "����SKT";
	case PDA_POZ_KTF:
		return "����KTF";
	case PDA_X301: 
		return "����X301";
	case PDA_SC8000:
		return "SC8000";
	case PDA_M500:
		return "����500";
	case PHONE_SKT:
		return "SKT��";
	case PHONE_KTF:
		return "KTF��";
	case PHONE_LGT:
		return "LGT��";
	case PDA_KC8000_KTF:
		return "KC8000";
	case PDA_RW6100:
		return "RW6100";
	case PDA_AIV:
		return "AIV+";
	default:
		return "N/A";
	}
}

CBranchInfo* GetCurBranchInfo(BOOL bAllowVirtualCompany)
{
	if(m_pbiCur)
	{
//		if(bAllowVirtualCompany)
//			return m_pbiCur;
//		else
//			return IsVC(m_pbiCur->nVirtualCompany) ? 
//			m_pbiCur->pRealBranch : m_pbiCur;
		return m_pbiCur;
	}

	return m_ba.GetAt(0);
}

CBranchInfo* GetRB(CBranchInfo *pBi)
{
	//return IsVC(pBi->nVirtualCompany) ? pBi->pRealBranch : pBi;
	return pBi;
}

CString &StringMakeUpper(CString &str)
{
	char *p = (char*)str.GetBuffer();
	for(int i = 0; i < str.GetLength(); i++)
	{
		if(p[i] >= 'a' && p[i] <= 'z')
		{
			p[i] = p[i] - 32; 
		}
	}
	return str;
}

CString GetDepositTypeStringFromType(int nType)
{
	switch(nType)
	{
	case 20:
		return "����";
	case 30:
		return "�ֺ�";
	case 40:
		return "�Ϻ�";
	case 50:
		return "������";
	default:
		return "UNKNOWN";
	}
}

CString GetDepositAllocateTypeStringFromType(int nType)
{
	switch(nType)
	{
	case 0:
		return "���Ա�";
	case 10:
		return "���Ա�";
	default:
		return "UNKNOWN";
	}
}

CString GetDepositStateString(int nState)
{
	switch(nState)
	{
	case  5:
		return "(-)�������۾� �߻�";   //---- �̺κ��߰�
	case  7:
		return "(-)�̼��� ����";
	case 10:
		return "(-)�̼��� �߻�";
	case 15:
		return "***�̼��� ����***";
	case 20:
		return "(+)�̼��� �Ա�";
	case 11:
		return "(-)�������� �߻�";
	case 21:
		return "(+)�������� �Ա�";
	case 30:
		return "�Աݾ� ����";
	case 35:
		return "(+)�������۾� �߻�";   //---- �̺κ��߰�
	case 40:
		return "(+)���Ա�";
	case 45:
		return "***���Ա� ����***";
	case 50:
		return "***�Աݹ�� ����***";
	case 60:
		return "���Ա� ����";

	default:
		return "N/A";
	}
}

CString GetFixedDepositStateString(int nState)
{
	switch(nState)
	{
	case 10:
		return "(+)�ܾ�����";
	case 11:
		return "(+)�ܾ�����(�������)";
	case 12:
		return "(+)�ܾ�����(�Աݾ׺���)";
	case 13:
		return "(+)�ܾ�����(�ſ�����)";
	case 14: 
		return "(+)�ܾ�����(�������۾�)";
	case 15:
		return "(+)�ܾ�����(���ݼ��ɾ�)";
	case 16:
		return "(+)�ܾ�����(�¶����Ա�)";
	case 17:
		return "(+)�ܾ�����(����)";
	case 18:	
		return "(+)�ܾ�����(�������)";
	case 19:
		return "���Ա� ����";
	case 20:
		return "(+)�ܾ�����(���Ա�)";
	case 21:	
		return "(+)�ܾ�����(�����ſ��)";
	case 22:
		return "(+)�ܾ�����(�����Ա�)";
	case 23:
		return "(+)�ܾ�����(ȭ������)";
	case 24:
		return "(+)�ܾ�����(ȭ������,������)";
	case 25:
		return "(+)�ܾ�����(�������)";
	case 26:
		return "(+)�ܾ�����(�����δ��)";
	case 30:
		return "(+)�ܾ�����(��ȯ��)";
	case 31:
		return "(+)�ܾ�����(��ü�δ��)";
	case 32:
		return "(+)�ܾ�����(Ÿ����ü)";
	case 33:
		return "(+)�ܾ�����(�̺�Ʈ����)";
	

	case 40:
		return "(-)�ܾ�����";
	case 41:
		return "(-)�ܾ�����(����)";
	case 42:
		return "(-)�ܾ�����(��Ұ���)";
	case 43:
		return "(-)�ܾ�����(�Աݾ׺���)";
	case 44:
		return "(-)�ܾ�����(����)";
	case 45:
		return "(-)�ܾ�����(���·�)";
	case 46:
		return "(-)�ܾ�����(�������۾�)";
	case 47:
		return "(-)�ܾ�����(������ȯ��)";
	case 48:
		return "(-)�ܾ�����(��ٺ�)";
	case 49:
		return "(-)�ܾ�����(�������)";
	case 50:
		return "(-)�ܾ�����(���Ա�)";
	case 51:
		return "(-)�ܾ�����(�ſ�����)";
	case 52:
		return "(-)�ܾ�����(�������)";
	case 53:
		return "(-)�ܾ�����(ȭ������)";
	case 54:
		return "(-)�ܾ�����(ȭ������,������)";
	case 55:
		return "(-)�ܾ�����(Ÿ����ü)";
	case 56:
		return "(-)�ܾ�����(���Ա�����)";
	case 57:
		return "(-)�ܾ�����(�������)";
	case 59:
		return "(-)�ܾ�����(�Ϻ�����)";

	case 70:
		return "(-)�ܾ�����(��ȯ��)";
	case 71:
		return "(-)�ܾ�����(���繰����)";

	case 60:
		return "�����ĺ���";
	case 61: 
		return "�ܾ��ʱ�ȭ";
	case 62:
		return "(-)�ܾ�����(�����δ��)";
	case 63:
		return "(-)�ܾ�����(��ü�δ��)";

	case 100:
		return "(+)�ܾ�����(�����Ϸ�)";
	case 101:
		return "(+)�ܾ�����(�������)";
	case 200:
		return "(-)�ܾ�����(�����Ϸ�)";
	case 201:
		return "(-)�ܾ�����(�������)";

	default:
		return "N/A";
	}
}

int GetDepositTypeFromString(CString strType)
{
	if(strType == "" || strType == "�ĳ�")
		return 0;
	else if(strType == "���Ա�")
		return 10;
	else if(strType == "�ֳ�")
		return 20;
	else if(strType == "�ֳ�+������")
		return 25;
	else if(strType == "�ֳ�+������+����")
		return 25;
	else if(strType == "��/��/��")
		return 25;
	else if(strType == "�ֳ�+����")
		return 27;

	return 0;
}

int GetNoneCommaNumber(CString strNumber)
{
	strNumber.Remove(',');
	return atol(strNumber);
}

int GetChargeDongTypeInfo(long nDong)
{	
	CPOIUnit *pData = m_poiNew.GetDongPOI(nDong);
	
	//pData->m_nClass
	//POI_DATA *pData =
	if(pData <= NULL)
		return -10;
	
	if(pData->m_nClass == 10 && pData->m_bDongData)
		return 3;
	else if(pData->m_nClass == 10 && pData->m_bDongData == FALSE)
		return 2;
	else if(pData->m_nClass == 5 )
		return 2;
	else if(pData->m_nClass == 0 )
		return 1;
	else if(pData->m_nClass == 20)
		return -1;
	else
		return 0;
}

int GetChargeType(int nStartType, int nDestType)
{ 

	int nType = 1000;

	if(nStartType == 3 && nDestType == 3)
		nType = 8;
	else if(nStartType == 3 && nDestType == 2)
		nType = 7;
	else if(nStartType == 3 && nDestType == 1)
		nType = 6;
	else if(nStartType == 2 && nDestType == 3)
		nType = 5;
	else if(nStartType == 1 && nDestType == 3)
		nType = 4;
	else if(nStartType == 2 && nDestType == 2)
		nType = 3;
	else if(nStartType == 2 && nDestType == 1)
		nType = 2;
	else if(nStartType == 1 && nDestType == 2)
		nType = 1;
	else if(nStartType == 1 && nDestType == 1)
		nType = 0;

	else if(nStartType == 3 && nDestType == -1)
		nType = -1;
	else if(nStartType == 2 && nDestType == -1)
		nType = -2;
	else if(nStartType == 1 && nDestType == -1)
		nType = -3;
	else if(nStartType == -1 && nDestType == 3)
		nType = -4;
	else if(nStartType == -1 && nDestType == 2)
		nType = -5;
	else if(nStartType == -1 && nDestType == 1)
		nType = -6;
	else if(nStartType == -1 && nDestType == -1)
		nType = -7;

	return nType;
}

CString GetChargeType(long nType)
{ 
	CString strView;

	switch(nType)
	{
	case 0:
		strView = "��->��";
		break;
	case 1:
		strView = "��->��";
		break;
	case 2:
		strView = "��->��";
		break;
	case 3:
		strView = "��->��";
		break;
	case 4:
		strView = "��->��";
		break;
	case 5:
		strView = "��->��";
		break;
	case 6:
		strView = "��->��";
		break;
	case 7:
		strView = "��->��";
		break;
	case 8:
		strView = "��->��";
		break;
	default:
		strView = "�̻���";
		break;
	}

	return strView;
}

ST_SMS_INFO GetSMSBalance(long nCompany)
{
	long nBarance = 0;
	int	 nSMSType = 0;
	ST_SMS_INFO smsi;

	CMkCommand pCmd(m_pMkDb, "select_sms_get_barance");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
	CMkParameter *parBarance = pCmd.AddParameter(typeLong , typeOutput, sizeof(long), nBarance);
	CMkParameter *parBaranceType = pCmd.AddParameter(typeInt , typeOutput, sizeof(int), nSMSType);
	pCmd.Execute();

	parBarance->GetValue(nBarance);
	parBaranceType->GetValue(nSMSType);
	smsi.nSMSBarance = nBarance;
	smsi.nSMSType = nSMSType;

	return smsi;
} 

BOOL IsChildVirtualCompany(long nVirtualCompany, long nCompany)
{
//	CHILD_COMPANY_MAP::iterator it = m_vcm.find(nCompany);
//	if(it == m_vcm.end() || it->second != nVirtualCompany)
//		return FALSE;
//	else
//		return TRUE;
	return FALSE;
}

BOOL IsVC(long nVirtualCompany)
{
//	return nVirtualCompany >= 100000 ? TRUE : FALSE;
	return FALSE;
}

CBranchInfo * GetBranchInfo(long nCompany)
{
	//by mksong (2010-12-10 ���� 11:38)
	//m_ccm���� �����ؾ���

	CBranchInfo *pBi = NULL;
	if(nCompany < 0)
		return pBi;


	if(m_ba.GetCount() > 1)
	{
		for(int i = 0; i < m_ba.GetCount(); i++)
		{
			pBi = m_ba.GetAt(i);

			if(pBi->bIntegrated)
				continue;

			if(pBi->nCompanyCode == nCompany)
			{
				return pBi;
			}
		}
	}
	else
		pBi = m_ba.GetAt(0);

	return pBi;
}

long GetNowBranchCode()
{
	BOOL bIntegrated = FALSE;
	CBranchInfo *pBi = NULL;

	if(m_ba.GetCount() > 0)
	{	
		CBranchInfo *pBi = GetCurBranchInfo();
		return pBi->nCompanyCode;
	}
	else

		pBi = m_ba.GetAt(0);

	return pBi->nCompanyCode;
}

BOOL ChangeRiderWorkState(long nCompany, long nRNo, BOOL bIntegrated, CString strWorkTitle, CString strWorkMemo, BOOL bWorkStop)
{
	CMkCommand pCmd(m_pMkDb, "update_rider_workstate5_1");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), bIntegrated);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), bWorkStop);
	pCmd.AddParameter(typeString, typeInput, strWorkTitle.GetLength(), strWorkTitle);
	pCmd.AddParameter(typeString, typeInput, strWorkMemo.GetLength(), strWorkMemo);
	pCmd.AddParameter(typeString, typeInput, m_ui.strID.GetLength(), m_ui.strID );
	return pCmd.Execute();
}

BOOL IsIntegrated(long nCompany)
{
	CBranchInfo *pBi = NULL;
	if(m_ba.GetCount() > 0)
		pBi = (CBranchInfo *)m_ba.GetAt(0);
	else
		return FALSE;

	if(pBi && nCompany == -1)
	{
		if(pBi->bIntegrated && m_ba.GetCount() > 1)
			return TRUE;
		else
			return FALSE;
	}
	else if (nCompany > 0 && m_ba.GetCount() > 1)
	{
		if(pBi->nCompanyCode == nCompany && pBi->bIntegrated)
			return TRUE;
		else
			return FALSE;
	}
	else
		return FALSE;
}

BOOL FileExistTest(CString strPath)
{
	BOOL bRet = FALSE;
	HANDLE hFile;
	hFile = CreateFile((LPSTR)(LPCTSTR)strPath, GENERIC_READ, 
		FILE_SHARE_READ, NULL, 
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(INVALID_HANDLE_VALUE != hFile) {
		bRet = TRUE;
		CloseHandle(hFile);
	}

	return bRet;
}

long GetCharCount(CString sCommaString, char ch)
{
	long nCount=0, index=0;

	while(1)
	{
		index = sCommaString.Find(ch, index + 1);

		if(index == -1) break;

		nCount++;
	}

	return nCount;
}

BOOL IsBranch(long nCompany)
{
	CBranchInfo *pBi = NULL;
	if(m_ba.GetCount() >= 0)
	{
		for(int i= 0; i < m_ba.GetCount(); i++)
		{
			pBi = (CBranchInfo *)m_ba.GetAt(i);
			if(pBi->nCompanyCode == nCompany)
				return TRUE;
		}
		return FALSE;
	}
	else
		return FALSE;
}

CString GetGeneralCountDisplay(long nCount)
{
	char buffer[20];

	if(nCount == 0)
		return "-";
	else 
		return CString(ltoa(nCount, buffer, 10)) + "��";
}

void SetHanEngMode(HWND hWnd, BOOL bHan) 
{ 
	HIMC hIMC = ImmGetContext(hWnd); 
	DWORD dwConv, dwSent; 
	DWORD dwTemp; 

	ImmGetConversionStatus(hIMC,&dwConv,&dwSent); 

	dwTemp = dwConv & ~IME_CMODE_LANGUAGE; 

	if(bHan)
		dwTemp |= IME_CMODE_NATIVE; 
	else
		dwTemp |= IME_CMODE_ALPHANUMERIC; 

	dwConv = dwTemp; 

	ImmSetConversionStatus(hIMC,dwConv,dwSent); 

	ImmReleaseContext(hWnd,hIMC); 
} 

long GetCommaCount(CString sCommaString)
{
	long nCount=0, index=0;

	while(1)
	{
		index = sCommaString.Find(";", index + 1);

		if(index == -1) break;

		nCount++;
	}

	return nCount;
}

long GetDepositTypeToComboSel(long nDepositType)
{
	if(nDepositType == 20)
		return 0;
	if(nDepositType == 30)
		return 1;
	if(nDepositType == 40)
		return 2;
	if(nDepositType == 50)
		return 3;

	return -1;
}

long GetDepositAllocateTypeToComboSel(long nDepositAllocateType)
{
	if(nDepositAllocateType == 0)
		return 0;
	if(nDepositAllocateType == 10)
		return 1;
	if(nDepositAllocateType == 20)
		return 2;

	return -1;
}

long GetDepositTypeFromComboSel(long nSel)
{
	if(nSel == 0)
		return 20;
	if(nSel == 1)
		return 30;
	if(nSel == 2)
		return 40;
	if(nSel == 3)
		return 50;

	return -1;
}

long GetDepositAllocateTypeFromComboSel(long nSel)
{
	if(nSel == 0)
		return 0;
	if(nSel == 1)
		return 10;

	return -1;
}

CString GetHostName()
{
	char szHostName[MAX_PATH];
	::gethostname(szHostName, MAX_PATH);
	return CString(szHostName);
}

void CreateDir(char* Path)
{
	char DirName[256];  //������ ���ʸ� �̸� 
	char* p = Path;     //���ڷ� ���� ���丮 
	char* q = DirName;   

	while(*p)
	{
		if (('\\' == *p) || ('/' == *p))   //��Ʈ���丮 Ȥ�� Sub���丮 
		{
			if (':' != *(p-1)) 
			{
				CreateDirectory(DirName, NULL);
			}
		}
		*q++ = *p++;
		*q = '\0';
	}

	CreateDirectory(DirName, NULL);  
}

#ifdef _DEBUG
#define ASSERT_VALID_STRING( str ) ASSERT( !IsBadStringPtr( str, 0xfffff ) )
#else	//	_DEBUG
#define ASSERT_VALID_STRING( str ) ( (void)0 )
#endif	//	_DEBUG

BOOL IsNumeric( LPCTSTR pszText )
{
	ASSERT_VALID_STRING( pszText );

	for( int i = 0; i < lstrlen( pszText ); i++ )
		if( !_istdigit( pszText[ i ] ) )
			return false;

	return true; 
}

BOOL SendSmsNew(long nCompany, long nTranID, CString sTranPhone, CString sTranCallback,
				CString sTranMsg, CString sSmsLogEtc, CString sEtc1, CString sEtc2, BOOL bMsgBox)
{
	sTranPhone.Replace("-", "");
	sTranCallback.Replace("-", "");

	if(sTranCallback.IsEmpty())
	{
		MessageBox(NULL, "ȸ�Ź�ȣ�� �Է��ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return FALSE;
	}

	if(!CheckTel(sTranCallback))
		return FALSE;

	//insert_mms_data_new mms�� ���ν��� ����

	CMkCommand pCmd(m_pMkDb, "insert_sms_data_new");
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long), 0);
	pCmd.AddParameter(nCompany);
	pCmd.AddParameter(nTranID);
	pCmd.AddParameter(typeString, typeInput, sTranPhone.GetLength(), sTranPhone);
	pCmd.AddParameter(typeString, typeInput, sTranCallback.GetLength(), sTranCallback);		
	pCmd.AddParameter(typeString, typeInput, sTranMsg.GetLength(), sTranMsg);
	pCmd.AddParameter(typeString, typeInput, sSmsLogEtc.GetLength(), sSmsLogEtc);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
	pCmd.AddParameter(typeString, typeInput, sEtc1.GetLength(), sEtc1);
	pCmd.AddParameter(typeString, typeInput, sEtc2.GetLength(), sEtc2);
	pCmd.AddParameter(0);

	if(!pCmd.Execute()) return FALSE;

	long nRet = 0; pPar->GetValue(nRet);

	if(nRet == 0)
	{
		MessageBox(NULL, "�ܾ��� �����Ͽ� ���� �Ͻ� �� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		return FALSE;
	}

	if(bMsgBox)
	{
		MessageBox(NULL, "���������� ���� �Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		return TRUE;
	}

	return TRUE;
}

BOOL SendSmsNewRev(long nCompany, long nTranID, CString sTranPhone, CString sTranCallback,
				CString sTranMsg, CString sSmsLogEtc, CString sEtc1, CString sEtc2, COleDateTime dtRev, BOOL bMsgBox)
{
	sTranPhone.Replace("-", "");
	sTranCallback.Replace("-", "");

	if(sTranCallback.IsEmpty())
	{
		MessageBox(NULL, "ȸ�Ź�ȣ�� �Է��ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return FALSE;
	}

	if(!CheckTel(sTranCallback))
		return FALSE;

	CMkCommand pCmd(m_pMkDb, "insert_sms_data_new_rev");
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long), 0);
	pCmd.AddParameter(nCompany);
	pCmd.AddParameter(nTranID);
	pCmd.AddParameter(typeString, typeInput, sTranPhone.GetLength(), sTranPhone);
	pCmd.AddParameter(typeString, typeInput, sTranCallback.GetLength(), sTranCallback);		
	pCmd.AddParameter(typeString, typeInput, sTranMsg.GetLength(), sTranMsg);
	pCmd.AddParameter(typeString, typeInput, sSmsLogEtc.GetLength(), sSmsLogEtc);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
	pCmd.AddParameter(typeString, typeInput, sEtc1.GetLength(), sEtc1);
	pCmd.AddParameter(typeString, typeInput, sEtc2.GetLength(), sEtc2);
	pCmd.AddParameter(0);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtRev);

	if(!pCmd.Execute()) return FALSE;

	long nRet = 0; pPar->GetValue(nRet);

	if(nRet == 0)
	{
		MessageBox(NULL, "�ܾ��� �����Ͽ� ���� �Ͻ� �� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		return FALSE;
	}

	if(bMsgBox)
	{
		MessageBox(NULL, "���������� ���� �Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		return FALSE;
	}

	return TRUE;
}

BOOL SendPDASimple(long nCompany, long nRiderCompany, long nRNo, CString sMsg)
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "edit_rider_msg4");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), 0);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRiderCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo);
	pCmd.AddParameter(typeString, typeInput, sMsg.GetLength(), sMsg);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);

	return pCmd.Execute();
}

BOOL NotifyPenalty(int nPenalty)
{
	if(m_ci.m_nPenaltyLevel >= nPenalty) {
		CString strTitle;
		strTitle.Format("��%s����, ���Ƽ ����%d �����ߡ�", 
			m_ci.m_dtPenaltyStart.Format("%m��%d�� "),
			m_ci.m_nPenaltyLevel);
		MessageBox(NULL, "ȸ������ ����� ��ü�Ǿ, ���Ƽ�� ����ǰ� �ֽ��ϴ�.\n"\
			"���� �� ����� �̿��� �� �����ϴ�. "\
			"����� ��� �ϳ��Ǳ����� ���Ƽ ������ �Ұ����ϸ�,\n"\
			"�κг����� ��쿡, ���Ƽ ���� 1�ܰ� �ٿ �����մϴ�.\n"\
			"������ ���� ���Ƽ ������ �Ʒ��� �����ϴ�.\n\n"\
			"�����Ƽ 1: ��������, ������, ���Ѽ��� ��� ������ѵ�\n"\
			"�����Ƽ 2: ���� ���� ���ѵ�                           <-- 3����\n"\
			"�����Ƽ 3: ������ ���� ���ѵ�                           <-- 6����\n"\
			"�����Ƽ 4: ����/�Ա��� ���� ���ѵ�                   <-- 9����\n"\
			"�����Ƽ 5: ����������                                   <-- 12����\n\n"\
			"���Ƽ ������ �ش�Ⱓ�� ��� �Ŀ�, �������� �ڵ� ���ǹǷ�,\n"\
			"������ ���⿡ �ذ��Ͻô°� �����Ͻʴϴ�.\n"\
			"���ϱ��� �ԱݿϷ��ϰڴٰ� ����Ͻô���, �׶����� ���Ƽ�� ���\n"\
			"����Ǵ°� ��Ģ�ΰ��� �����Ͻñ� �ٶ��ϴ�.\n"\
			"�ε����ϰ� ������ ����� �˼��մϴ�.\n"\
			"�����մϴ�.",
			strTitle,
			MB_ICONINFORMATION);

		CBillDlg dlg;
		COleDateTime dtDate;
		COleDateTime dtCurrent = COleDateTime::GetCurrentTime();
		if(dtCurrent.GetMonth() == 1)
			dtDate.SetDate(dtCurrent.GetYear() - 1, 11, 1);
		else if(dtCurrent.GetMonth() == 2)
			dtDate.SetDate(dtCurrent.GetYear() - 1, 12, 1);
		else
			dtDate.SetDate(dtCurrent.GetYear(), dtCurrent.GetMonth() - 2, 1);

		dlg.m_nCompanyCode = m_ci.m_nCompanyCode;
		dlg.m_dtDate = dtDate;
		dlg.DoModal();
		return FALSE;
	}

	return TRUE;
}


BOOL SendUpdateFile(CMkDatabase &db, CString strLocalPath, CString strServerPath)
{
	HANDLE hFile, hFileMap;
	unsigned char *pBasePointer;
	DWORD dwSize;
	BOOL bRet = FALSE;

	hFile = CreateFile((LPSTR)(LPCTSTR)strLocalPath, GENERIC_READ, 
		FILE_SHARE_READ, NULL, 
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(INVALID_HANDLE_VALUE != hFile)
	{
		hFileMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
		dwSize = GetFileSize(hFile, 0);
		pBasePointer = (unsigned char*) MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, dwSize);

		if(db.UploadFileWithDlg(strServerPath, (char*)pBasePointer, dwSize))
		{		
			bRet = TRUE;
		}

		UnmapViewOfFile((LPVOID)pBasePointer);
		CloseHandle(hFileMap);
	}

	CloseHandle(hFile);
	return bRet;
}

CString EnCodeStr(CString ToCode)
{
	CString RetStr,AddStr;
	int i,max;
	unsigned short asc;
	unsigned char c;
	max = (unsigned int)ToCode.GetLength();
	for(i=0;i<max;i++)
	{
		c = ToCode[i];
		asc = c;//(unsigned int)c;
		if(asc>47 && asc<58)
		{
			RetStr+=c;//Interim[(int)i];
		}
		else if(asc>64 && asc<91)
		{
			RetStr+=c;//Interim[(int)i];
		}
		else if(asc>96 && asc<123)
		{
			RetStr+=c;//Interim[(int)i];
		}
		else if(asc==32)
		{
			RetStr+="+";
		}
		else
		{
			AddStr.Format("%%%2x",asc);
			int iv = (int)AddStr.GetAt(1);
			if((int)AddStr.GetAt(1)==32)
			{
				AddStr.SetAt(1,'0');
			}
			RetStr+=AddStr;
		}
	}
	return RetStr;
}

CString DeCodeStr(CString ToCode)
{
	CString RetStr,AddStr;
	int i,max;
	unsigned short asc;
	unsigned char c;
	max = (unsigned int)ToCode.GetLength();
	for(i=0;i<max;)
	{
		c = ToCode[i];
		asc = c;//(unsigned int)c;
		if(asc==37)
		{
			AddStr=ToCode.Mid(i+1,2);
			i+=3;
			sscanf((LPCTSTR)AddStr,"%2x",&asc);
			RetStr+=(char)asc;
		}
		else if(asc==43)
		{
			RetStr += ' ';
			i++;
		}
		else
		{
			RetStr += c;
			i++;
		}
	}
	return RetStr;
}


typedef BOOL (WINAPI *SetLayer)(HWND hWnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
#define LWA_COLORKEY            0x01
#define LWA_ALPHA               0x02

void SetCrystal(CWnd *pWnd, int index)
{
	HMODULE hUser32 = GetModuleHandle(_T("USER32.DLL"));

	SetLayer pSetLayer = (SetLayer)GetProcAddress(hUser32, "SetLayeredWindowAttributes");

	if(pSetLayer == NULL)
	{
		//MessageBox("win2000 �̻�");
		return;
	}

	char chAlpha = index; //���� ���� 0 ~ 255
	SetWindowLong(pWnd->m_hWnd, GWL_EXSTYLE, GetWindowLong(pWnd->m_hWnd, GWL_EXSTYLE) | 0x80000);
	pSetLayer(pWnd->m_hWnd, 0,chAlpha, LWA_ALPHA);
}

void SetEditText(CEdit *pEdit, CString strText, BOOL bFront)
{
	CString strEdit;
	pEdit->GetWindowText(strEdit);

	if(bFront)
		pEdit->SetWindowText(strText + strEdit);
	else
		pEdit->SetWindowText(strEdit + strText);
}

void FillVaildRiderData()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_able_allocate_rider_1");

	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(TRUE);

	if(!pRs.Execute(&pCmd)) return;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		ST_RIDER_WORK_STATE_INFO st;

		pRs.GetFieldValue("lCode", st.nCompany);
		pRs.GetFieldValue("nMNo", st.nRNo);
		pRs.GetFieldValue("sName", st.strName);
		pRs.GetFieldValue("nWorkState", st.nWorkState);

		m_rm[m_rm.size()] = st;

		pRs.MoveNext();
	}
}

long GetCarTypeForCharge(long nCarType)
{
	long nChargeCarType = 0;

	switch(nCarType)
	{
	case CAR_AUTO:
	case CAR_BIGBIKE:
		nChargeCarType = 0;
		break;
	case CAR_DAMA:
		nChargeCarType = 1;
		break;
	case CAR_LABO:
		nChargeCarType = 2;
		break;
	case CAR_SEDAN:
		nChargeCarType = 3;
		break;
		/*
	case CAR_VAN:
	case CAR_6VAN:
		nChargeCarType = 3;
		break;
		*/
	case CAR_TRUCK:
	case CAR_1_4_TON:
	case CAR_2_5_TON:
	case CAR_3_5_TON: 
	case CAR_5_TON:
	case CAR_11_TON: 
	case CAR_18_TON: 
	case CAR_25_TON:
	case CAR_5_TON_PLUS:
	case CAR_8_TON:
	case CAR_14_TON: 
	case CAR_15_TON:
		nChargeCarType = 4;

	default:
		break;
	}

	return nChargeCarType;
}

BOOL AddCustomerTel(long nCompany, long nCNo, long nTelID, CString strPhone)
{
	if(nCNo <= 0)
	{
		AfxMessageBox("����� �� ��ȭ��ȣ�� �߰��ϼ���", MB_OK);
		return FALSE;
	}

	strPhone = GetNoneDashNumberRemoveDDD(strPhone);

	CMkCommand pCmd(m_pMkDb, "insert_customer_phone_1");
	pCmd.AddParameter(nCompany);
	pCmd.AddParameter(nCNo);
	pCmd.AddParameter(nTelID);
	pCmd.AddParameter(strPhone);

	return pCmd.Execute();
}

void GetItemCommaToArray(CString strItem, CStringArray &arryItem)
{
	long nStartPos = 0;
	long nDestPos = 0;
	long nCount = 0;

	while(1)
	{
		if(nCount > 100)
			break;

		nDestPos = strItem.Find(";", nStartPos);

		if(nDestPos == -1)
			break;

		CString sItem = strItem.Mid(nStartPos, nDestPos - nStartPos);

		if(sItem.IsEmpty() == FALSE)
			arryItem.Add(sItem);

		nStartPos = nDestPos + 1;

		nCount++;
	}
}

CString GetRemoveDDDNumber(CString strPhone, long nCompany) 
{
	//strDDD�� �� �־����
	CString strDDD = nCompany == 0 ? m_ci.m_strDDD : GetBranchInfo(nCompany)->strDDD;

	strPhone.Replace("-", "");

	if(strPhone.Left(strDDD.GetLength()) == strDDD)
		strPhone = strPhone.Right(strPhone.GetLength() - strDDD.GetLength());

	return strPhone;
}

void GetOnlyDistance(long nStartPosX, long nStartPosY, long nDestPosX, long nDestPosY, CWnd* pReturnMsgWnd)
{
	CPoint s, d, v;
	CLogiMapCns *pCNS = LU->GetLogiMapCns();
	pCNS->ClearPos();
	pCNS->AddPos(nStartPosX, nStartPosY);
	pCNS->AddPos(nDestPosX, nDestPosY);
	//pCNS->GetRouteDistanceThread1(pReturnMsgWnd, FALSE, 0,0, 0);


	pCNS->GetRouteDistance(pReturnMsgWnd, FALSE, 0,0, 0);
} 

CString GetCancelReason(long nReason)
{
	if(nReason == 0) return "��ȭ����";
	else if(nReason == 1) return "�ð�����";
	else if(nReason == 2) return "������̻�";
	else if(nReason == 3) return "����ũ��ҷ�";
	else if(nReason == 4) return "��޺Ұ��Ұ�";
	else if(nReason == 5) return "������";
	else if(nReason == 6) return "�Ϻ����";
	else if(nReason == 7) return "������";
	else if(nReason == 8) return "��������";
	else if(nReason == 9) return "�������";
	else if(nReason == 10) return "�����Ǽ�";

	return "N/A";
}

BOOL IsCash(long nPayType)
{	
	if(nPayType == PAY_PRE ||
		nPayType == PAY_AFTER ||
		nPayType == PAY_DIRECT)
		return TRUE;
	else
		return FALSE;
}
 
CString GetPrice(long nPrice)
{
	if(nPrice == 0)
		return "A���";
	if(nPrice == 1)
		return "B���";
	if(nPrice == 2)
		return "C���";
	if(nPrice == 3)
		return "D���";
	return "A���";
}

 CString GetGrade(long nGrade, BOOL bShowDefault)
{
	if(nGrade == 0)
		return bShowDefault ? "����" : "";

	if(nGrade == 1)
		return "���";

	if(nGrade == 2)
		return "�ֿ��";

	if(nGrade == 3)
		return "�ҷ�";

	return bShowDefault ? "����" : "";
}

int GetGradeColor(long nGrade)
{
	 if(nGrade == 0)
		 return RGB(107, 205, 90);
	 if(nGrade == 1)
		 return RGB(0, 255, 255);
	 if(nGrade == 2)
		 return RGB(100,100,255);
	 if(nGrade == 3)
		 return RGB(255,100,100);
	 return RGB(107, 205, 90);
}

 CString GetDiscountType(long nDiscount)
{
	if(nDiscount == 0)
		return "�ۼ�Ʈ(%)";
	if(nDiscount == 1)
		return "�ݾ�(��)";
	if(nDiscount == 2)
		return "AŸ��";
	if(nDiscount == 3)
		return "BŸ��";
	if(nDiscount == 4)
		return "CŸ��";
	if(nDiscount == 5)
		return "DŸ��";
	return "�ۼ�Ʈ(%)";
}

BOOL IsThisCompany(CString strCompanyName, long nCompany, long nShareCode1)
{
	if(strCompanyName == "��������_����")
		return nCompany == 2904 || nCompany == 2907 || nCompany == 2920 || nCompany == 2931;
	else if(strCompanyName == "��������_2904")
		return nCompany == 2904;
	else if(strCompanyName == "��������_2920")
		return nCompany == 2920;
	else if(strCompanyName == "��������_2931")
		return nCompany == 2931;
	else if(strCompanyName == "��������_2907")
		return nCompany == 2907;	
	else if(strCompanyName == "�̷���") 
		return m_ci.m_nShareCode1 == 15775;
	else if(strCompanyName == "����Ư��")
		return m_ci.m_nShareCode1 == 16300;
	else if(strCompanyName == "����")
		return m_ci.m_nShareCode1 == 7700;
	else if(strCompanyName == "�ɹ���Ϲ���")
		return m_ci.m_nShareCode1 == 28361;	
	else if(strCompanyName == "�ڸ��ƹ���ũ")
		return m_ci.m_nShareCode1 == 7010;
	else if(strCompanyName == "����")
		return m_ci.m_nShareCode1 == 7100;
	else if(strCompanyName == "�뱸����")
		return m_ci.m_nShareCode5 == 7640;
	else if(strCompanyName == "������")
		return m_ci.m_nShareCode1 == 7330;
	else if(strCompanyName == "�����")
		return m_ci.m_nShareCode1 == 14476;
	else if(strCompanyName == "����������")
		return m_ci.m_nShareCode1 == 5290;	
	else if(strCompanyName == "�ֽ�ȸ��뱸����")
		return m_ci.m_nShareCode1 == 8380;	
	else if(strCompanyName == "�ϳ�����")
		return m_ci.m_nShareCode1 == 15219;
	else if(strCompanyName == "��¯")
		return m_ci.m_nShareCode1 == 14420 || nCompany == 14276;
	else if(strCompanyName == "�ѹݵ�������") 
		return m_ci.m_nShareCode1 == 15475;
	else if(strCompanyName == "�����ڸ�����")
		return m_ci.m_nShareCode1 == 12080;
	else if(strCompanyName == "����������")
		return m_ci.m_nShareCode1 == 28490;
	else if(strCompanyName == "���ֿ���")
		return m_ci.m_nShareCode3 == 12079;
	else if(strCompanyName == "����_���̽�")
		return m_ci.m_nShareCode1 == 6050;
	else if(strCompanyName == "�ùٷ�")
		return m_ci.m_nShareCode1 == 12450;
	else if(strCompanyName == "����")
		return m_ci.m_nCompanyCode <= 100;	
	else if(strCompanyName == "��õ��")
		return nCompany == 7476;	
	else if(strCompanyName == "����������")
		return m_ci.m_nCompanyCode == 2010;	
	else if(strCompanyName == "����������")
		return m_ci.m_nCompanyCode == 16135;	
	else
	{
		//MessageBox(GetDesktopWindow(), CString("�˼����� ȸ�籸�� �ڵ� ") + strCompanyName,
		//	"Ȯ��",
		//	MB_ICONINFORMATION);
	}

	return FALSE;
} 

BOOL IsCustomerHasOrder(long nCNo)
{
	CMkCommand pCmd(m_pMkDb, "select_cno_history");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(nCNo);

	if(pCmd.Execute() == FALSE) return FALSE;
	
	long nRet; parRet->GetValue(nRet);

	return nRet;
}

CString GetLicenceTypeFromLong(long nLicenceType)
{
	if(nLicenceType == ZERO) return "";
	else if(nLicenceType == ONE) return "1������";
	else if(nLicenceType == 2) return "1������";
	else if(nLicenceType == 3) return "2������";
	else if(nLicenceType == 4) return "��Ÿ";
	else if(nLicenceType == 5) return "������";
	else if(nLicenceType == 6) return "������";
	else if(nLicenceType == 7) return "2������";

	return "";
}

CString GetDateTimeToString(COleDateTime dtDate,int nType,BOOL bShowDay)
{
	if(dtDate.m_status == 2)
		return "";

	CString strDate = "";  
	switch (nType)
	{
		case ONE:
		strDate = dtDate.Format(_T("%Y-%m-%d"));
		break;  
		case TWO:
		strDate = dtDate.Format(_T("%Y-%m-%d %H")); 
		break;  
		case THREE:
		strDate = dtDate.Format(_T("%Y-%m-%d %H:%M")); 
		break;
		case FOUR:
		strDate = dtDate.Format(_T("%Y-%m-%d %H:%M:%S")); 
		break;
	}

	if(bShowDay)
	{
		const char *dayofweek[] = {"��", "��", "ȭ", "��", "��", "��", "��"};
		strDate.Format("%s(%s)", strDate, dayofweek[dtDate.GetDayOfWeek() - 1]);
	} 

	return strDate;
}

CString GetMyDateString(COleDateTime dt, BOOL bDisplayCentury, BOOL *pbSpecialDate)
{
	static COleDateTime dtTomorrow;
	static COleDateTime dtYesterday;
	static BOOL bInit = FALSE;

	if(!bInit)
	{
		dtTomorrow = m_ei.dtTodayBound + COleDateTimeSpan(1, 0, 0, 0);
		dtYesterday = m_ei.dtTodayBound - COleDateTimeSpan(1, 0, 0, 0);
		bInit = TRUE;
	}

	if(dt < dtTomorrow && dt > m_ei.dtTodayBound)
	{
		if(pbSpecialDate)
			*pbSpecialDate = TRUE;
		return "����";
	}
	else if(dt > dtYesterday && dt < dtTomorrow)
	{
		if(pbSpecialDate)
			*pbSpecialDate = TRUE;
		return "����";
	}
	else 
	{
		if(pbSpecialDate)
			*pbSpecialDate = FALSE;
		return bDisplayCentury ? dt.Format("%Y-%m-%d") : dt.Format("%y-%m-%d");
	}
}

CString GetValueByArg(CString& strDataSet, CString strArg)
{
	strArg = _T("<") + strArg + _T("=");
	strArg.MakeUpper();

	int nFind1 = strDataSet.Find(strArg);
	if(nFind1 < 0 ) return _T("");

	int nFind2 = strDataSet.Find(_T(">"),nFind1);
	if(nFind2 < 0 ) return _T("");

	CString sRetVal = strDataSet.Mid(nFind1 + strArg.GetLength(), nFind2-(nFind1 +strArg.GetLength() ) );
	return sRetVal;
}

BOOL IsKoreaWord(CString strWord)
{
	CStringW strDataW(strWord);
	CStringW strCharW(strDataW.Right(1));

	//if( sCharW >= (CStringW("��") ) && sCharW <= CStringW("��") ) return FALSE;
	if( strCharW >= (CStringW("��") ) && strCharW <= CStringW("Ş") )
	{
		if(strCharW >= (CStringW("��") ) && strCharW <= CStringW("Ş")) 
			return TRUE;
		else 	
			return FALSE;
	}

	return TRUE;
}

CString GetTwoPhone(CString strPhone1, CString strPhone2)
{
	if(strPhone1.IsEmpty() && strPhone1.IsEmpty())
		return "";

	if(strPhone1.IsEmpty())
		return ::GetDashPhoneNumber(strPhone2);

	if(strPhone2.IsEmpty())
		return ::GetDashPhoneNumber(strPhone1);

	return ::GetDashPhoneNumber(strPhone1) + "/" + ::GetDashPhoneNumber(strPhone2);
}

CString GetTwoPhoneAsterisk(CString strPhone1, CString strPhone2)
{
	if(strPhone1.IsEmpty() && strPhone1.IsEmpty())
		return "";

	if(strPhone1.IsEmpty())
		return ::GetAsteriskPhoneNumber(strPhone2);

	if(strPhone2.IsEmpty())
		return ::GetAsteriskPhoneNumber(strPhone1);

	return ::GetAsteriskPhoneNumber(strPhone1) + "/" + ::GetAsteriskPhoneNumber(strPhone2);
}

void MakeModaless()
{
	CFakeDlg dlg;
	dlg.DoModal();
}

BOOL LengthCheck(HWND hwnd, long nApplyID, long nLengthStaticID, int nLength, CString strControlName)
{
	CString strApply = "", strTemp = "";

	int nApplyControlLength = 0;
	CWnd * pWnd = CWnd::FromHandle(GetDlgItem(hwnd, nApplyID)); 
	pWnd->GetWindowText(strApply);

	nApplyControlLength = GetStringLengthByAscII(strApply);

	if(nApplyControlLength > nLength)
	{
		strTemp.Format("%s  �� ���ڼ��� ������ �ͺ��� Ů�ϴ�", strControlName);
		MessageBox(hwnd, strTemp, "Ȯ��", MB_ICONINFORMATION);
		strApply = strApply.Mid(0, strApply.GetLength() - 2);
		pWnd->SetFocus();
		pWnd->SetWindowText(strApply);
		((CEdit*)pWnd)->SetSel(strApply.GetLength(), strApply.GetLength());

		return FALSE;
	}
	else
	{
		strApply.Format("%ld/%ld", nApplyControlLength , nLength);
		strApply = strControlName + " " + strApply;

		CWnd * pWnd1 = CWnd::FromHandle(GetDlgItem(hwnd, nLengthStaticID)); 
		pWnd1->ShowWindow(SW_HIDE);
		pWnd1->SetWindowText(strApply);
		pWnd1->ShowWindow(SW_SHOW);
	}

	return TRUE;
}

BOOL ChangeFixedDepositState(long nID, long nState)
{
	CMkCommand pCmd(m_pMkDb, "update_fixed_deposit_state");

	pCmd.AddParameter(nID);
	pCmd.AddParameter(nState);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);

	return pCmd.Execute();
}

COleDateTime GetCompareDate(BOOL bWeeklyDeposit, COleDateTime dtMaindDate, long nRiderIncomeDay, BOOL bSameRiderIncomeDay)
{
	COleDateTime dtTemp = dtMaindDate;

	if(bWeeklyDeposit) //�ֳ�
	{
		if(bSameRiderIncomeDay == TRUE) // ������
		{
			COleDateTimeSpan span(7, 0, 0, 0);
			dtTemp = dtMaindDate + span;
		}

		while(1) // �Ͽ���ã��
		{
			if(dtTemp.GetDayOfWeek() == 1)
				break;

			COleDateTimeSpan span(1, 0, 0, 0);
			dtTemp = dtTemp - span;

		} 

		nRiderIncomeDay ++; //�ִ� 1������� ������ ����

		while(1)
		{
			if(dtTemp.GetDayOfWeek() == nRiderIncomeDay)
				break;

			COleDateTimeSpan span(1, 0, 0, 0);
			dtTemp = dtTemp + span;
		}
	}
	else //����
	{
		if(nRiderIncomeDay == 0)
			return dtTemp;

		if(bSameRiderIncomeDay == FALSE) // ������
		{			
			long nYear = dtMaindDate.GetYear();
			long nMonth = dtMaindDate.GetMonth();
			long nDay = GetAbilityDay(nRiderIncomeDay, dtMaindDate.GetYear(), dtMaindDate.GetMonth());
			dtTemp.SetDateTime(dtMaindDate.GetYear(), dtMaindDate.GetMonth(), GetAbilityDay(nRiderIncomeDay, dtMaindDate.GetYear(), dtMaindDate.GetMonth()), 0, 0, 0);
		}
		else
		{
			long nNextMonth = dtMaindDate.GetMonth() == 12 ? 1 : dtMaindDate.GetMonth() + 1;
			long nNextYear = dtMaindDate.GetMonth() == 12 ? dtMaindDate.GetYear() + 1 : dtMaindDate.GetYear();

			dtTemp.SetDateTime(nNextYear, nNextMonth, GetAbilityDay(nRiderIncomeDay, nNextYear, nNextMonth), 0, 0, 0);
		}
	}

	return dtTemp;
}

long GetAbilityDay(long nDay, long nYear, long nMonth)
{
	long nNextMonth = nMonth == 12 ? 1 : nMonth + 1;
	long nNextYear = nMonth == 12 ? nYear + 1 : nYear;

	COleDateTime dtDate(nNextYear, nNextMonth, 1, 0, 0, 0);
	COleDateTimeSpan span(1, 0, 0, 0);
	dtDate = dtDate - span;

	long nLastDay = dtDate.GetDay();

	if(nDay <= nLastDay)
		return nDay;
	else 
		return nLastDay;
}

void InitGroupReportStruct(GROUP_REPORT &stSum)
{
	stSum.stData[0].nCashCount = 0;
	stSum.stData[0].nCreditCount = 0;
	stSum.stData[0].nOnlineCount = 0;
	stSum.stData[0].nTransCount = 0;
	stSum.stData[0].nCashCharge = 0;
	stSum.stData[0].nCreditCharge = 0;
	stSum.stData[0].nOnlineCharge = 0;
	stSum.stData[0].nTransCharge = 0;

	stSum.stData[0].nSumCount = 0;
	stSum.stData[0].nSumTotal = 0;
	stSum.stData[0].nBillCollection = 0;
	stSum.stData[0].nUnBillCollection = 0;
	stSum.stData[0].nTax = 0;

	stSum.stData[1].nCashCount = 0;
	stSum.stData[1].nCreditCount = 0;
	stSum.stData[1].nOnlineCount = 0;
	stSum.stData[1].nTransCount = 0;
	stSum.stData[1].nCashCharge = 0;
	stSum.stData[1].nCreditCharge = 0;
	stSum.stData[1].nOnlineCharge = 0;
	stSum.stData[1].nTransCharge = 0;

	stSum.stData[1].nSumCount = 0;
	stSum.stData[1].nSumTotal = 0;
	stSum.stData[1].nBillCollection = 0;
	stSum.stData[1].nUnBillCollection = 0;
	stSum.stData[1].nTax = 0;

	stSum.stData[0].dtReportStart.SetStatus(COleDateTime::DateTimeStatus(2));//m_status = 0;
	stSum.stData[1].dtReportStart.SetStatus(COleDateTime::DateTimeStatus(2));

	stSum.nBalance = 0;
	stSum.nInComeSum = 0;
	stSum.nGNo = 0;
	stSum.nReportRow = 0;
	stSum.strDept = "";
	stSum.strGroupName = "";
	stSum.strName = "";
}

CString GetGroupReportText(GROUP_REPORT st, long nCol, long nSel, BOOL bSumrecord)
{		
	CString strText;

	switch(nCol)
	{
	case 0:
		strText = st.strGroupName;
		break;
	case 1:
		strText = st.strDept;
		break;
	case 2:
		strText = st.strName;
		break;
	case 3:
		if(bSumrecord)
			strText = "";
		else
		{
			if(st.stData[nSel].dtReportStart.m_status != 2)
				strText = st.stData[nSel].dtReportStart.Format("%m-%d") + " ~ " + st.stData[nSel].dtReportEnd.Format("%m-%d");
			else
				strText = "";
		}
		break;
	case 4:
		if(bSumrecord)
			strText = ::GetMyNumberFormat(st.stData[nSel].nSumCount);
		else
			strText = ::GetMyNumberFormat(st.stData[nSel].nCashCount + st.stData[nSel].nCreditCount + st.stData[nSel].nOnlineCount);
		break;
	case 5:
		strText = ::GetMyNumberFormat(st.stData[nSel].nCashCharge);
		break;
	case 6:
		strText = ::GetMyNumberFormat(st.stData[nSel].nCreditCharge);
		break;
	case 7:
		strText = ::GetMyNumberFormat(st.stData[nSel].nOnlineCharge);
		break;
	case 8:
		strText = ::GetMyNumberFormat(st.stData[nSel].nTransCharge);
		break;
	case 9:
		strText = ::GetMyNumberFormat(st.stData[nSel].nTax);
		break;
	case 10:
		if(bSumrecord)
			strText =  ::GetMyNumberFormat(st.stData[nSel].nSumTotal);
		strText = ::GetMyNumberFormat(st.stData[nSel].nCashCharge + st.stData[nSel].nCreditCharge + st.stData[nSel].nOnlineCharge);
		break;
	case 11:
		if(bSumrecord)
			strText = "";
		else
		{
			if(st.stData[nSel].nReportState == 0)
				strText = "����Ϸ�";
			else if(st.stData[nSel].nReportState == 10)
				strText = "�κ��Ա�";
			else if(st.stData[nSel].nReportState == 20)
				strText = "�ԱݿϷ�";
		}
		break;
	case 12:
		strText = ::GetMyNumberFormat(st.stData[nSel].nBillCollection);
		break;
	case 13:
		if(bSumrecord)
			strText = "";
		else
		{
			if(st.stData[nSel].dtBillCollection.m_status != 2)
				strText = st.stData[nSel].dtBillCollection.Format("%m-%d");
			else
				strText = "";
		}				
		break;
	case 14:
		strText = ::GetMyNumberFormat(st.stData[nSel].nUnBillCollection);
		break;
	case 15:
		strText = ::GetMyNumberFormat(st.nBalance);
		break;
	case 16:
		strText = ::GetMyNumberFormat(st.nInComeSum);
		break;
	case 17:
		strText = st.stData[nSel].bPressBill == TRUE ? "��" : "";
		break;
	case 18:
		strText = st.stData[nSel].strEtc;
		break;
	}

	return strText;
}

CString GetGroupReportText1(GROUP_REPORT st, long nCol, long nSel, BOOL bSumrecord)
{		
	CString strText;

	switch(nCol)
	{
	case 0:
		strText = st.strGroupName;
		break;
	case 1:
		strText = st.strDept;
		break;
	case 2:
		strText = st.strName;
		break;
	case 3:
		if(bSumrecord)
			strText = "";
		else
		{
			if(st.stData[nSel].dtReportStart.m_status != 2)
				strText = st.stData[nSel].dtReportStart.Format("%m-%d") + " ~ " + st.stData[nSel].dtReportEnd.Format("%m-%d");
			else
				strText = "";
		}
		break;
	case 4:
		strText = ::GetMyNumberFormat(st.stData[nSel].nUnBillCollection);
		break;
	case 5:
		strText = ::GetMyNumberFormat(st.nBalance);
		break;
	case 6:
		strText = ::GetMyNumberFormat(st.stData[nSel].nBillCollection);
		break;
	case 7:
		if(bSumrecord)
			strText = "";
		else
		{
			if(st.stData[nSel].dtBillCollection.m_status != 2)
				strText = st.stData[nSel].dtBillCollection.Format("%m-%d");
			else
				strText = "";
		}				
		break;		
	case 8:
		strText = ::GetMyNumberFormat(st.nInComeSum);
		break;
	case 9:
		strText = st.stData[nSel].bPressBill == TRUE ? "��" : "";
		break;
	case 10:
		strText = st.stData[nSel].strEtc;
		break;
	case 11:
		if(bSumrecord)
			strText = ::GetMyNumberFormat(st.stData[nSel].nSumCount);
		else
			strText = ::GetMyNumberFormat(st.stData[nSel].nCashCount + st.stData[nSel].nCreditCount + st.stData[nSel].nOnlineCount);
		break;
	case 12:
		strText = ::GetMyNumberFormat(st.stData[nSel].nCashCharge);
		break;
	case 13:
		strText = ::GetMyNumberFormat(st.stData[nSel].nCreditCharge);
		break;
	case 14:
		strText = ::GetMyNumberFormat(st.stData[nSel].nOnlineCharge);
		break;
	case 15:
		strText = ::GetMyNumberFormat(st.stData[nSel].nTransCharge);
		break;
	case 16:
		strText = ::GetMyNumberFormat(st.stData[nSel].nTax);
		break;
	case 17:
		if(bSumrecord)
			strText =  ::GetMyNumberFormat(st.stData[nSel].nSumTotal);
		strText = ::GetMyNumberFormat(st.stData[nSel].nCashCharge + st.stData[nSel].nCreditCharge + st.stData[nSel].nOnlineCharge);
		break;
	case 18: 
		if(bSumrecord)
			strText = "";
		else
		{
			if(st.stData[nSel].nReportState == 0)
				strText = "����Ϸ�";
			else if(st.stData[nSel].nReportState == 10)
				strText = "�κ��Ա�";
			else if(st.stData[nSel].nReportState == 20)
				strText = "�ԱݿϷ�";
		}
		break;
	}

	return strText;
}


BOOL SaveAllocateInfo(ST_RIDER_INFO_ALLOCATE *pAllocate, BOOL pSimpleMode)
{
	CWaitCursor wait;
	COleDateTime dtInitDate = COleDateTime(2004,1,1,0,0,0);
	COleDateTime dtJobStart, dtJobEnd; 
	dtJobStart= dtJobEnd = dtInitDate;

	CMkCommand pCmd(m_pMkDb, "update_allocate_limit_2008_2");

	COleDateTimeSpan oSpan;

	oSpan.SetDateTimeSpan(0,pAllocate->dtJobStart.GetHour(),pAllocate->dtJobStart.GetMinute(),pAllocate->dtJobStart.GetSecond());
	dtJobStart += oSpan;	
	pCmd.AddParameter(dtJobStart);

	oSpan.SetDateTimeSpan(0,pAllocate->dtJobEnd.GetHour(),pAllocate->dtJobEnd.GetMinute(),pAllocate->dtJobEnd.GetSecond() );
	dtJobEnd += oSpan;
	pCmd.AddParameter(dtJobEnd);
	pCmd.AddParameter(max(pAllocate->nWorkState, 0));

	if(pAllocate->nWorkState == 1) //1�� �������� 0�� ���� 2�����(deploy) 
	{
		COleDateTime dtTemp;
		CString strWorkMemo;
		dtTemp.SetDateTime(pAllocate->dtJobStop.GetYear(),pAllocate->dtJobStop.GetMonth(), pAllocate->dtJobStop.GetDay(),
			pAllocate->dtJobStop.GetHour(),pAllocate->dtJobStop.GetMinute(),pAllocate->dtJobStop.GetSecond());

		if(pAllocate->strJobStopMemo.GetLength() > 50)
			pAllocate->strJobStopMemo += pAllocate->strJobStopMemo.Mid(0,50);

		pCmd.AddParameter(dtTemp);
		pCmd.AddParameter(pAllocate->strJobStopMemo);
	}
	else
	{
		pCmd.AddParameter(dtInitDate);		
		pCmd.AddParameter("");		
	}

	if(pAllocate->bLock)
	{
		pCmd.AddParameter(atoi(pAllocate->strLockTime));
		pCmd.AddParameter((pAllocate->strLockCount == "������")? 100 : atoi(pAllocate->strLockCount) );
	}
	else
	{
		pCmd.AddParameter(0);
		pCmd.AddParameter(100);
	}

	if(pAllocate->bMyOrderLock)
	{
		pCmd.AddParameter(atoi(pAllocate->strLockTime4MyOrder));
		pCmd.AddParameter((pAllocate->strLockCount4MyOrder == "������")? 100 : atoi(pAllocate->strLockCount4MyOrder) );
	}
	else
	{
		pCmd.AddParameter(0);
		pCmd.AddParameter(100);
	}

	if(pAllocate->bOtherOrderLock)
	{
		pCmd.AddParameter(atoi(pAllocate->strLockTime4OCOrder));
		pCmd.AddParameter((pAllocate->strLockCount4OCOrder == "������")? 100 : atoi(pAllocate->strLockCount4OCOrder) );
	}
	else
	{
		pCmd.AddParameter(0);
		pCmd.AddParameter(100);
	}

	if(pAllocate->bTimeAllocate)
	{
		pCmd.AddParameter(TRUE);	
		COleDateTime dtAllocateDateTime(pAllocate->dtTimeAllocateDate.GetYear(),pAllocate->dtTimeAllocateDate.GetMonth(),pAllocate->dtTimeAllocateDate.GetDay(),
			pAllocate->dtTimeAllocateDate.GetHour(),pAllocate->dtTimeAllocateDate.GetMinute(),pAllocate->dtTimeAllocateDate.GetSecond());
		pCmd.AddParameter(max(dtInitDate, pAllocate->dtTimeAllocateDate) );
		pCmd.AddParameter(atoi(pAllocate->strTimeAllocateRelease));

	}
	else
	{
		pCmd.AddParameter(0);	
		pCmd.AddParameter(dtInitDate);
		pCmd.AddParameter(0);
	}

	//pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), 
	//	(m_chkSms.GetCheck() )? TRUE : FALSE);

	pCmd.AddParameter(max(pAllocate->bServiceRentLimit, 0));
	pCmd.AddParameter(max(pAllocate->bInsurance, 0));

	COleDateTime dtTempStart;COleDateTimeSpan dtSpanStart;
	dtSpanStart.SetDateTimeSpan(0,0,1,0);
	dtTempStart.SetDate(pAllocate->dtInsuranceStart.GetYear(),pAllocate->dtInsuranceStart.GetMonth(),pAllocate->dtInsuranceStart.GetDay());
	dtTempStart += dtSpanStart;


	pCmd.AddParameter((pAllocate->bInsurance) ? max(dtInitDate, dtTempStart) : dtInitDate);

	COleDateTime dtTemp;COleDateTimeSpan dtSpan;
	dtSpan.SetDateTimeSpan(0,11,59,0);
	dtTemp.SetDate(pAllocate->dtInsuranceEnd.GetYear(),pAllocate->dtInsuranceEnd.GetMonth(),pAllocate->dtInsuranceEnd.GetDay());
	dtTemp += dtSpan;


	pCmd.AddParameter((pAllocate->bInsurance) ? max(dtTemp, dtInitDate) : dtInitDate);

	CString strInsuranceID = "";
	if( pAllocate->bInsurance)
		strInsuranceID =  pAllocate->strInsuranceCompany + "/" + pAllocate->strInsuranceID;

	pCmd.AddParameter(strInsuranceID);	
	pCmd.AddParameter(pAllocate->nPanaltyTypeShowOrder);
	pCmd.AddParameter(_ttoi(pAllocate->strElapseLimitAllocateLocal));
	pCmd.AddParameter(_ttoi(pAllocate->strElapseLimitPickupLocal));
	pCmd.AddParameter(_ttoi(pAllocate->strElapseLimitAllocateGlobal));
	pCmd.AddParameter(_ttoi(pAllocate->strElapseLimitPickupGlobal));
	pCmd.AddParameter(pAllocate->bAutoShow);
	pCmd.AddParameter(pAllocate->bBigAutoShow);
	pCmd.AddParameter(pAllocate->bDamaShow);
	pCmd.AddParameter(pAllocate->bRaboShow);
	pCmd.AddParameter(pAllocate->bBanShow);
	pCmd.AddParameter(pAllocate->bTruckShow);
	pCmd.AddParameter(pAllocate->nAllocGroup);
	pCmd.AddParameter(pAllocate->nCompany);
	pCmd.AddParameter(pAllocate->nRNo);
	pCmd.AddParameter(pSimpleMode);

	pCmd.Execute();

	//	((CStaffPage5*)m_pParentWnd)->RefreshList();
	return TRUE;
}

BOOL CheckGroupReport(CString strGNo, long nDstGNo, COleDateTime dtDate, long nMemberCount, CString &strNeedReReportID)
{
	CCheckGroupReportDlg dlg;
	dlg.m_strGNo = strGNo;
	dlg.m_nDstGNo = nDstGNo;
	dlg.m_dtDate = dtDate;
	dlg.m_nMemberCount = nMemberCount;

	if(dlg.DoModal() == IDOK)
	{
		strNeedReReportID = dlg.m_strNeedReReportID;
		return TRUE;
	}

	return FALSE;
}

BOOL ReReport(CString strNeedReReport)
{
	CString strEtc = "�׷��̵�";

	CMkCommand pCmd(m_pMkDb, "rereport_group_2");
	pCmd.AddParameter(strNeedReReport);
	pCmd.AddParameter(strEtc);
	pCmd.AddParameter(0);

	return pCmd.Execute();
}

BOOL SaveIncomeInfo(ST_RIDER_INFO_INCOME *pIncome,  BOOL bSimpleMode)
{ 
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_rider_deposit_info_2008_9");

	pCmd.AddParameter(pIncome->nCompany); 
	pCmd.AddParameter(pIncome->nRNo);
	pCmd.AddParameter(pIncome->nDepositType);
	pCmd.AddParameter(pIncome->nDepositAllocateType);
	pCmd.AddParameter(pIncome->nFixedDeposit); // ��/�� ���Ա�
	pCmd.AddParameter(pIncome->bWeeklyDeposit); //���� �ֳ�
	pCmd.AddParameter(max(pIncome->nPayMentDay, 0));
	pCmd.AddParameter(max(pIncome->nRiderIncomeDay, 0));
	pCmd.AddParameter(max(pIncome->nSameRiderIncomeDay, 0));

	pCmd.AddParameter(max(pIncome->nMyCallRateType, 0));
	pCmd.AddParameter(max(pIncome->nOtherCallRateType, 0));
	pCmd.AddParameter(max(pIncome->nDepositExtensionDay, 0)); //�ǵ��� ��� ����
	pCmd.AddParameter(max(pIncome->nCreditReportType, 0)); //�ܻ����� Ÿ�� // 0 ������ 1���� 2// ����
	pCmd.AddParameter(max(pIncome->bUseSmsNotify, 0)); // SMS -> �߼�
	pCmd.AddParameter(max(pIncome->nSMSDealyDay, 0)); // SMS -> �߼�
	pCmd.AddParameter(max(pIncome->bBranchAsOtherCall, 0)); // �ڻ� -> Ÿ��
	pCmd.AddParameter(max(pIncome->bPenaltyCharge, 0));//����

	pCmd.AddParameter(max(pIncome->bUseDTPercent, 0));
	pCmd.AddParameter(max(pIncome->nDT, 0));

	pCmd.AddParameter(max(pIncome->nCashDTType, 0));
	pCmd.AddParameter(max(pIncome->nCashDTWon, 0));
	pCmd.AddParameter(pIncome->strCashDTFee);
	pCmd.AddParameter(max(pIncome->nMyCallDTType, 0));
	pCmd.AddParameter(max(pIncome->nMyCallDTWon, 0));
	pCmd.AddParameter(pIncome->strMyCallDTFee);
	pCmd.AddParameter(max(pIncome->nOtherCallDTType, 0));
	pCmd.AddParameter(max(pIncome->nOtherCallDTWon, 0));
	pCmd.AddParameter(pIncome->strOtherCallDTFee);

	pCmd.AddParameter(max(pIncome->nMyCallCashWon, 0));
	pCmd.AddParameter(max(pIncome->nMyCallCash, 0));
	pCmd.AddParameter(max(pIncome->nMyCashApplyCharge, 0));
	pCmd.AddParameter(max(pIncome->nOtherCallCashWon, 0));
	pCmd.AddParameter(max(pIncome->nOtherCallCash, 0));
	pCmd.AddParameter(max(pIncome->nOtherCashApplyCharge, 0));
	pCmd.AddParameter(max(pIncome->nMyCallCreditWon, 0));
	pCmd.AddParameter(max(pIncome->nMyCallCredit, 0));
	pCmd.AddParameter(max(pIncome->nMyCreditApplyCharge, 0));
	pCmd.AddParameter(max(pIncome->nOtherCallCreditWon, 0));
	pCmd.AddParameter(max(pIncome->nOtherCallCredit, 0));
	pCmd.AddParameter(max(pIncome->nOtherCreditApplyCharge, 0));
	pCmd.AddParameter(max(pIncome->nMyCallOnlineWon, 0));
	pCmd.AddParameter(max(pIncome->nMyCallOnline, 0));
	pCmd.AddParameter(max(pIncome->nMyOnlineApplyCharge, 0));
	pCmd.AddParameter(max(pIncome->nOtherCallOnlineWon, 0));
	pCmd.AddParameter(max(pIncome->nOtherCallOnline, 0));
	pCmd.AddParameter(max(pIncome->nOtherOnlineApplyCharge, 0));

	pCmd.AddParameter(pIncome->strEtc);
	pCmd.AddParameter(pIncome->strEtcCharge);
	pCmd.AddParameter(max(pIncome->nAllocMinCharge, 0));

	pCmd.AddParameter(bSimpleMode);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.strName);

	if(!pRs.Execute(&pCmd)) return FALSE;

	return TRUE;
}

void InitRiderIncomeStruct(ST_RIDER_INFO_INCOME *st)
{	
	st->nDepositType = 0;
	st->nFixedDeposit = 0;
	st->bWeeklyDeposit = 0;
	st->nPayMentDay = 0;
	st->nAddBalance = 0;

	st->nCashDTType = 0;
	st->nCashDTWon = 0;
	st->strCashDTFee = "";

	st->nMyCallDTType = 0;
	st->nMyCallDTWon = 0;
	st->strMyCallDTFee = "";

	st->nOtherCallDTType = 0;
	st->nOtherCallDTWon = 0;
	st->strOtherCallDTFee = "";

	st->bUseDTPercent = 0;
	st->nDT = 0;  // �⺻����
	st->bBranchAsOtherCall = 0;
	st->bPenaltyCharge = 0;
	st->nCreditReportType = 0;
	st->nDepositExtensionDay = 0;
	st->bUseSmsNotify = 0;
	st->nSMSDealyDay = 0;
	st->nMyCallCashWon = 0;
	st->nMyCallCash = 0;
	st->nOtherCallCashWon = 0;
	st->nOtherCallCash = 0;
	st->nMyCallCreditWon = 0;
	st->nMyCallCredit = 0;
	st->nOtherCallCreditWon = 0;
	st->nOtherCallCredit = 0;
	st->nMyCallOnlineWon = 0;
	st->nMyCallOnline = 0;
	st->nOtherCallOnlineWon = 0;
	st->nOtherCallOnline = 0;
	st->nMyCashApplyCharge = 0;
	st->nOtherCashApplyCharge = 0;
	st->nMyCreditApplyCharge = 0;
	st->nOtherCreditApplyCharge = 0;
	st->nMyOnlineApplyCharge = 0;
	st->nOtherOnlineApplyCharge = 0;
	st->strEtc = "";
	st->strEtcCharge = "";
	st->nDepositAllocateType = 0;

	st->nRiderIncomeDay = 0;
	st->nSameRiderIncomeDay = 0;

	st->nAllocMinCharge = 0;
	st->nMyCallRateType = 0;
	st->nOtherCallRateType = 0;
}

BOOL IsCrossOrder(long nTNo, CString &sCName, long &nState)
{
	CMkCommand pCmd(m_pMkDb, "select_tno_info");
	pCmd.AddParameter(nTNo);
	CMkParameter *pParName = pCmd.AddParameter(typeString, typeOutput, 100, "");
	CMkParameter *pParState = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), "");
	CMkParameter *pParShareCode1 = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), "");

	if(!pCmd.Execute())
		return FALSE;

	long nShareCode1;

	pParName->GetValue(sCName);
	pParState->GetValue(nState);
	pParShareCode1->GetValue(nShareCode1);

	return m_ci.m_nShareCode1 != nShareCode1;
}

void FillBankCode(BOOL bRefresh, CComboBox *pCmb, long nBankID)
{
	if(pCmb)
		pCmb->SetCurSel(GetIndexFromBankID(pCmb, nBankID));

	if(bRefresh == FALSE && m_mapBank.size() > ZERO)
	{
		if(pCmb)
		{
			if(pCmb->GetCount() != 0)
				return;
		}		
	}

	m_mapBank.clear();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_bank_list");
	pCmd.AddParameter(0);

	if(!pRs.Execute(&pCmd))
		return;

	for(int i=ZERO; i<pRs.GetRecordCount(); i++)
	{
		ST_BANK st;

		pRs.GetFieldValue("nID", st.nID);
		pRs.GetFieldValue("sBankName", st.strBankName);
		pRs.GetFieldValue("nBankCode", st.strBankCode);

		m_mapBank.insert(MAP_BANK::value_type(st.nID, st));
		pRs.MoveNext();
	}

	if(pCmb)
	{
		long nItem = ZERO;
		pCmb->ResetContent();
		nItem = pCmb->AddString("���þ���");
		pCmb->SetItemData(nItem, ZERO);

		for(MAP_BANK::iterator it = m_mapBank.begin(); it != m_mapBank.end(); it++)
		{
			nItem = pCmb->AddString(it->second.strBankName);
			pCmb->SetItemData(nItem, it->second.nID);
		}

		pCmb->SetCurSel(GetIndexFromBankID(pCmb, nBankID));
	}
}

long GetIndexFromBankID(CComboBox *pCmb, long nBankID)
{
	for(int i=0; i<pCmb->GetCount(); i++)
	{
		if(nBankID == (long)pCmb->GetItemData(i))
			return i;
	}

	return ZERO;
}

CString GetBankName(long nBankID)
{
	if(m_mapBank.size() == 0)
		FillBankCode(TRUE);

	MAP_BANK::iterator it = m_mapBank.find(nBankID);

	if(it != m_mapBank.end())
		return it->second.strBankName;

	return "";
}

long GetWindowTextLong(CWnd *pEdit)
{
	CString strTemp;
	pEdit->GetWindowText(strTemp);
	strTemp.Replace(",", "");
	return atoi(strTemp);
}

void FillStateMent()
{
	m_mapStateMent.clear();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_order_state_ment");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(1);

	if(!pRs.Execute(&pCmd)) return;

	for(int i=ZERO; i<pRs.GetRecordCount(); i++)
	{
		ST_STATE_MENT st;
		pRs.GetFieldValue("nID", st.nID);
		pRs.GetFieldValue("nCompany", st.nCompany);
		pRs.GetFieldValue("nType", st.nType);
		pRs.GetFieldValue("sMent", st.strMent);

		m_mapStateMent.insert(MAP_STATE_MENT::value_type(st.nID, st));
		pRs.MoveNext();
	}
}


#define LOAD_FROM_REG(y, x) info.x = AfxGetApp()->GetProfileInt("RiderMapSet", #x, y);
#define SAVE_TO_REG(x) AfxGetApp()->WriteProfileInt("RiderMapSet", #x, info.x);

void LoadFromReg(ST_RIDER_MAP_SET_INFO &info)
{
	info.nRiderAlloc = AfxGetApp()->GetProfileInt("RiderMapSet", "nRiderAlloc", 0);
	LOAD_FROM_REG(0, nRiderAlloc)
	LOAD_FROM_REG(0, nRiderPickup)
	LOAD_FROM_REG(0, nRiderBefore1)
	LOAD_FROM_REG(0, nRiderBefore10)
	LOAD_FROM_REG(0, nRiderBefore30)
	LOAD_FROM_REG(0, nRiderAfter30)
	LOAD_FROM_REG(1, nRiderCaptionRNo)
	LOAD_FROM_REG(0, nRiderCaptionName)
	LOAD_FROM_REG(0, nRiderCaptionCompany)
	LOAD_FROM_REG(1, nOrderBefore10)
	LOAD_FROM_REG(1, nOrderBefore20)
	LOAD_FROM_REG(1, nOrderBefore30)
	LOAD_FROM_REG(1, nOrderBefore60)
	LOAD_FROM_REG(1, nOrderAfter60)
	LOAD_FROM_REG(1, nOrderCaptionTime)
	LOAD_FROM_REG(0, nOrderCaptionStart)
	LOAD_FROM_REG(0, nOrderCaptionDest)
	LOAD_FROM_REG(1, nOrderAutoRefresh)
	LOAD_FROM_REG(0, nNearRiderLevel)
	LOAD_FROM_REG(0, nShowSectorList)
	LOAD_FROM_REG(1, nHoverShowRiderHaveOrder)
	LOAD_FROM_REG(0, nShowSectorList)
	LOAD_FROM_REG(0, nShowCompleteOrder)
	LOAD_FROM_REG(0, nShowCancelOrder)
	LOAD_FROM_REG(1, nOrderClickAutoMove)
	LOAD_FROM_REG(1, nOrderClickRiderMove)
	LOAD_FROM_REG(0, nShowRiderHasColor)
	LOAD_FROM_REG(0, nShowCompayAll)
	LOAD_FROM_REG(8, nShowRiderCaptionLevel)
	LOAD_FROM_REG(4, nRiderTailShowTime)
	LOAD_FROM_REG(0, bLocateRight);	
	LOAD_FROM_REG(1, nGpsRiderOnly);
	LOAD_FROM_REG(0, bShowOrderCount);
	LOAD_FROM_REG(0, bOrderCount8);
	LOAD_FROM_REG(0, bOrderCount10);
	LOAD_FROM_REG(0, bOrderCount11);
	LOAD_FROM_REG(0, bOrderCount30);
	LOAD_FROM_REG(0, bOrderCount31);
	LOAD_FROM_REG(0, bOrderCount35);
}

void SaveToReg(ST_RIDER_MAP_SET_INFO &info)
{
	AfxGetApp()->WriteProfileInt("RiderMapSet", "nRiderAlloc", info.nRiderAlloc);
	SAVE_TO_REG(nRiderAlloc)
	SAVE_TO_REG(nRiderPickup)
	SAVE_TO_REG(nRiderBefore1)
	SAVE_TO_REG(nRiderBefore10)
	SAVE_TO_REG(nRiderBefore30)
	SAVE_TO_REG(nRiderAfter30)
	SAVE_TO_REG(nRiderCaptionRNo)
	SAVE_TO_REG(nRiderCaptionName)
	SAVE_TO_REG(nRiderCaptionCompany)
	SAVE_TO_REG(nOrderBefore10)
	SAVE_TO_REG(nOrderBefore20)
	SAVE_TO_REG(nOrderBefore30)
	SAVE_TO_REG(nOrderBefore60)
	SAVE_TO_REG(nOrderAfter60)
	SAVE_TO_REG(nOrderCaptionTime)
	SAVE_TO_REG(nOrderCaptionStart)
	SAVE_TO_REG(nOrderCaptionDest)
	SAVE_TO_REG(nOrderAutoRefresh)
	SAVE_TO_REG(nNearRiderLevel)
	SAVE_TO_REG(nShowSectorList)
	SAVE_TO_REG(nHoverShowRiderHaveOrder)
	SAVE_TO_REG(nShowSectorList)
	SAVE_TO_REG(nShowCompleteOrder)
	SAVE_TO_REG(nShowCancelOrder)
	SAVE_TO_REG(nOrderClickAutoMove)
	SAVE_TO_REG(nShowRiderHasColor)
	SAVE_TO_REG(nShowCompayAll)
	SAVE_TO_REG(nShowRiderCaptionLevel)
	SAVE_TO_REG(nOrderClickRiderMove)
	SAVE_TO_REG(nRiderTailShowTime)
	SAVE_TO_REG(bLocateRight);
	SAVE_TO_REG(nGpsRiderOnly);
	SAVE_TO_REG(bShowOrderCount);
	SAVE_TO_REG(bOrderCount8);
	SAVE_TO_REG(bOrderCount10);
	SAVE_TO_REG(bOrderCount11);
	SAVE_TO_REG(bOrderCount30);
	SAVE_TO_REG(bOrderCount31);
	SAVE_TO_REG(bOrderCount35);
}

void LoadFromReg(ST_RCP_DLG_SET_INFO &info)
{
	LOAD_FROM_REG(1, nReplacePhone1WithCID);
	LOAD_FROM_REG(1, nReplacePhone2WithPhone1);
	LOAD_FROM_REG(0, nIncreaseDetailControlAlways);
	LOAD_FROM_REG(0, nCopyDestCreditCustomer);
	LOAD_FROM_REG(0, nStartDontAutoCopy);
	LOAD_FROM_REG(0, nManualAddCustomer);
}

void SaveToReg(ST_RCP_DLG_SET_INFO &info)
{
	SAVE_TO_REG(nReplacePhone1WithCID);
	SAVE_TO_REG(nReplacePhone2WithPhone1);
	SAVE_TO_REG(nIncreaseDetailControlAlways);
	SAVE_TO_REG(nCopyDestCreditCustomer);
	SAVE_TO_REG(nStartDontAutoCopy);
	SAVE_TO_REG(nManualAddCustomer);
}

void LoadFromReg(ST_RCP_MAP_SET_INFO &info)
{
	LOAD_FROM_REG(1, nRcpMoveMap)
	LOAD_FROM_REG(1, nRcpDlgMoveMap)
	LOAD_FROM_REG(0, nNotCreateMapForm)
	LOAD_FROM_REG(1, nJoinWithCID)
}

void SaveToReg(ST_RCP_MAP_SET_INFO &info)
{
	SAVE_TO_REG(nRcpMoveMap)
	SAVE_TO_REG(nRcpDlgMoveMap)
	SAVE_TO_REG(nNotCreateMapForm)
	SAVE_TO_REG(nJoinWithCID)
}

long GetTailShowTimeFromIndex(long nIndex)
{
	int nTime[] = {0, 15, 30, 45, 60, 90, 120, 180};
	return nTime[nIndex];
}

CString GetStringFromLong(long nLong, BOOL bReturnZero)
{
	if(nLong == 0)
		return bReturnZero == TRUE ? "0" : "";

	char buffer[10];
	return CString(itoa(nLong, buffer, 10));
}

CString GetRcpType(long nRcpType, BOOL bInterNet)
{
	if(nRcpType == 0 && bInterNet == FALSE) //����ƮQ
		return "����ƮQ";
	else if(nRcpType == 1)
		return "����ƮQ��";
	else if (nRcpType == 3)
		return "����Ʈ��";
	else if (nRcpType == 4)
		return "������";
	else if (nRcpType == 5) //Q5
		return "Q5";
	else if (nRcpType == 6) //�� API
		return ""; 
	else if(bInterNet == TRUE)
		return "���ͳ�";

	return "N/A";
}

BOOL IsWindow7()
{   
	OSVERSIONINFO ver;
	ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&ver);
	printf("MajorVersion: %X\n",ver.dwMajorVersion);
	printf("MinorVersion: %X\n",ver.dwMinorVersion);
	printf("BuildNumber: %X\n",ver.dwBuildNumber);
	printf("PlatformId: %X\n",ver.dwPlatformId);
	printf("Version: %s\n",ver.szCSDVersion);

	CString strTemp; strTemp.Format("%X.%X", ver.dwMajorVersion, ver.dwMinorVersion);

	/*
	dwMajorVersion + dwMinorVersion

	Windows 7					6.1
	Windows Server "Longhorn"	6.0
	Windows Vista				6.0
	Windows Server 2003 R2		5.2
	Windows Server 2003			5.2
	Windows XP					5.1
	Windows 2000				5.0
	Windows Me					4.90
	Windows 98					4.10
	Windows NT 4.0				4.0
	Windows 95					4.0
	*/

	return strTemp == "6.1";
}   


BOOL IsWindowXP()
{
	OSVERSIONINFO ver;
	ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&ver);
	printf("MajorVersion: %X\n",ver.dwMajorVersion);
	printf("MinorVersion: %X\n",ver.dwMinorVersion);
	printf("BuildNumber: %X\n",ver.dwBuildNumber);
	printf("PlatformId: %X\n",ver.dwPlatformId);
	printf("Version: %s\n",ver.szCSDVersion);

	CString strTemp; strTemp.Format("%X.%X", ver.dwMajorVersion, ver.dwMinorVersion);

	/*
	dwMajorVersion + dwMinorVersion

	Windows 7					6.1
	Windows Server "Longhorn"	6.0
	Windows Vista				6.0
	Windows Server 2003 R2		5.2
	Windows Server 2003			5.2
	Windows XP					5.1
	Windows 2000				5.0
	Windows Me					4.90
	Windows 98					4.10
	Windows NT 4.0				4.0
	Windows 95					4.0
	*/

	return strTemp == "5.1";
}

CString IsMoveRiderOk(long nCompany, long nRNo)
{
	if(nRNo == 0)
		return "0�� ������";

	CMkCommand pCmd(m_pMkDb, "select_is_move_rider_ok");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(nCompany);
	pCmd.AddParameter(nRNo);

	if(!pCmd.Execute())
		return FALSE;

	long nRet; parRet->GetValue(nRet);

	if(nRet == 0)
		return "��� �ߺ�";

	return  "";
}


void MakeCarTypeCombo(CComboBox *pCmbBox) 
{
	pCmbBox->ResetContent();

	pCmbBox->SetItemData(pCmbBox->AddString("�������"), CAR_AUTO); //0
	pCmbBox->SetItemData(pCmbBox->AddString("������"), CAR_BIGBIKE); //0
	pCmbBox->SetItemData(pCmbBox->AddString("�¿�"), CAR_SEDAN);
	pCmbBox->SetItemData(pCmbBox->AddString("�ٸ���"), CAR_DAMA);
	pCmbBox->SetItemData(pCmbBox->AddString("��"), CAR_LABO);
	pCmbBox->SetItemData(pCmbBox->AddString("����ö"), CAR_SUBWAY);
	pCmbBox->SetItemData(pCmbBox->AddString("1��"), CAR_TRUCK); //4
	pCmbBox->SetItemData(pCmbBox->AddString("1.4��"), CAR_1_4_TON); 
	pCmbBox->SetItemData(pCmbBox->AddString("2.5��"), CAR_2_5_TON);
	pCmbBox->SetItemData(pCmbBox->AddString("3.5��"), CAR_3_5_TON);
	pCmbBox->SetItemData(pCmbBox->AddString("5��"), CAR_5_TON);
	pCmbBox->SetItemData(pCmbBox->AddString("5������"), CAR_5_TON_PLUS); //9
	pCmbBox->SetItemData(pCmbBox->AddString("8��"), CAR_8_TON);
	pCmbBox->SetItemData(pCmbBox->AddString("11��"), CAR_11_TON);
	pCmbBox->SetItemData(pCmbBox->AddString("14��"), CAR_14_TON);
	pCmbBox->SetItemData(pCmbBox->AddString("15��"), CAR_15_TON);
	pCmbBox->SetItemData(pCmbBox->AddString("18��"), CAR_18_TON);//14
	pCmbBox->SetItemData(pCmbBox->AddString("25��"), CAR_25_TON);//15
}
	

void SetCarType(CComboBox *pCmbBox, long nCarType) 
{
	
	if(nCarType == CAR_AUTO)			pCmbBox->SetCurSel(0);
	else if(nCarType == CAR_BIGBIKE)	pCmbBox->SetCurSel(1);	
	else if(nCarType == CAR_SEDAN)		pCmbBox->SetCurSel(2);
	else if(nCarType == CAR_DAMA)		pCmbBox->SetCurSel(3);
	else if(nCarType == CAR_LABO)		pCmbBox->SetCurSel(4);
	else if(nCarType == CAR_SUBWAY)		pCmbBox->SetCurSel(5);
	else if(nCarType == CAR_TRUCK)		pCmbBox->SetCurSel(6);
	else if(nCarType == CAR_1_4_TON)	pCmbBox->SetCurSel(7);
	else if(nCarType == CAR_2_5_TON)	pCmbBox->SetCurSel(8);
	else if(nCarType == CAR_3_5_TON)	pCmbBox->SetCurSel(9);
	else if(nCarType == CAR_5_TON)		pCmbBox->SetCurSel(10);
	else if(nCarType == CAR_5_TON_PLUS)	pCmbBox->SetCurSel(11);
	else if(nCarType == CAR_8_TON)		pCmbBox->SetCurSel(12);
	else if(nCarType == CAR_11_TON)		pCmbBox->SetCurSel(13);
	else if(nCarType == CAR_14_TON)		pCmbBox->SetCurSel(14);
	else if(nCarType == CAR_15_TON)		pCmbBox->SetCurSel(15);
	else if(nCarType == CAR_18_TON)		pCmbBox->SetCurSel(16);
	else if(nCarType == CAR_25_TON)		pCmbBox->SetCurSel(17);
	else
		pCmbBox->SetCurSel(0);	
	
	/*
	if(nCarType == CAR_6VAN)
		pCmbBox->SetCurSel(5);
	else if(nCarType == CAR_TRUCK)
		pCmbBox->SetCurSel(6);
	else if(nCarType == CAR_1_4_TON)
		pCmbBox->SetCurSel(7);
	else if(nCarType == CAR_SUBWAY)
		pCmbBox->SetCurSel(8);
	else if(nCarType == CAR_PS)
		pCmbBox->SetCurSel(9);
	else if(nCarType == CAR_2_5_TON)
		pCmbBox->SetCurSel(10);
	else if(nCarType == CAR_3_5_TON)
		pCmbBox->SetCurSel(11);
	else if(nCarType == CAR_5_TON)
		pCmbBox->SetCurSel(12);
	else if(nCarType == CAR_11_TON)
		pCmbBox->SetCurSel(13);
	else if(nCarType == CAR_18_TON)
		pCmbBox->SetCurSel(14);
	else if(nCarType == CAR_25_TON)
		pCmbBox->SetCurSel(15);
	else
		pCmbBox->SetCurSel(nCarType);	
		*/
}


long GetCarType(CComboBox *pCmbBox) 
{	
	return pCmbBox->GetItemData(pCmbBox->GetCurSel());
	/*
	long nIndex = pCmbBox->GetCurSel();

	if(nIndex == 5)
		return CAR_6VAN;
	if(nIndex == 6)
		return CAR_TRUCK;
	if(nIndex == 7)
		return CAR_1_4_TON;
	if(nIndex == 8)
		return CAR_SUBWAY;
	if(nIndex == 9)
		return CAR_PS;
	if(nIndex == 10)
		return CAR_2_5_TON;
	if(nIndex == 11)
		return CAR_3_5_TON;
	if(nIndex == 12)
		return CAR_5_TON;
	if(nIndex == 13)
		return CAR_11_TON;
	if(nIndex == 14)
		return CAR_18_TON;
	if(nIndex == 15)
		return CAR_25_TON;

	return nIndex;
	*/
}


int GetCarChargeType(long nCarType)
{

	if(nCarType == CAR_AUTO || nCarType == CAR_BIGBIKE)
		return 0;
	else if(nCarType == CAR_DAMA)
		return 1;
	else if(nCarType == CAR_LABO)
		return 2;
	else if(nCarType == CAR_VAN || nCarType == CAR_6VAN)
		return 3;
	else if(nCarType == CAR_TRUCK || nCarType == CAR_TRUCK || nCarType == CAR_1_4_TON
		|| nCarType == CAR_2_5_TON || nCarType == CAR_3_5_TON || nCarType == CAR_5_TON  )
		return 4;
	else if(nCarType == CAR_SUBWAY)
		return 5;
	else if(nCarType == CAR_2_5_TON)
		return 6;
	else if(nCarType == CAR_3_5_TON)
		return 7;
	else if(nCarType == CAR_5_TON)
		return 8;

	return -1;
}
BOOL IsRequestOver15Day(int nCompany)
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_transfer_request_over_15day");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);

	if(!pRs.Execute(&pCmd)) return false;

	if(pRs.GetRecordCount() > 0)
		return TRUE;
	else
		return FALSE;
}

long GetCardVendor(long nCompany)
{
	MAP_CARD_VENDOR::iterator it = m_mapCardVendor.find(nCompany);

	if(it == m_mapCardVendor.end())
		return 0;

	return it->second.nVendorCode;
}


void LoadCardInfo()
{
	m_mapCardVendor.clear();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_card_vendor_list");
	cmd.AddParameter(0);

	if(!rs.Execute(&cmd))	
		return;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		ST_CARD_VENDOR st;
		rs.GetFieldValue("nCompany", st.nCompany);
		rs.GetFieldValue("sVendor", st.strVendor);
		rs.GetFieldValue("nVendorCode", st.nVendorCode);

		m_mapCardVendor.insert(MAP_CARD_VENDOR::value_type(st.nCompany, st));
		rs.MoveNext();
	}
}

BOOL CheckCardPayCondition(long nTNo, long nCharge, long nDeposit, CString &strError)
{
	CMkCommand cmd(m_pMkDb, "check_card_pay_condition_ok");
	CMkParameter *pParRet = cmd.AddParameter(typeLong, typeReturn, 0);
	cmd.AddParameter(nTNo);
	cmd.AddParameter(nCharge);
	cmd.AddParameter(nDeposit);
	CMkParameter *parError = cmd.AddParameter(typeString, typeOutput, 300, "");

	if(!cmd.Execute())
		return FALSE;

	long nRet; pParRet->GetValue(nRet);
	parError->GetValue(strError);

	if(nRet == 100)
		return TRUE;

	return FALSE;
}
 
BOOL GetCardPayType(ST_CARD_INFO &st, BOOL bUseForTranCance)
{ 
	CMkCommand cmd(m_pMkDb, "select_card_tran_info3"); 
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(st.nTNo); 
	CMkParameter *parCardType = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parCardProcess = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parCharge = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parDisplayCharge = cmd.AddParameter(typeString, typeOutput, 100, "");
	CMkParameter *parTID = cmd.AddParameter(typeString, typeOutput, 50, "");
	CMkParameter *parMID = cmd.AddParameter(typeString, typeOutput, 50, "");
	CMkParameter *parSessionKey = cmd.AddParameter(typeString, typeOutput, 100, "");
	CMkParameter *parCardServerAddr = cmd.AddParameter(typeString, typeOutput, 50, "");
	CMkParameter *parCardServerPort = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parLogiServerAddr = cmd.AddParameter(typeString, typeOutput, 50, "");
	CMkParameter *parLogiServerPort = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	cmd.AddParameter(bUseForTranCance);
	CMkParameter *parFeeType = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parError = cmd.AddParameter(typeString, typeOutput, 200, "");
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);

	if(!cmd.Execute())
		return FALSE;

	long nRet; parRet->GetValue(nRet);
	parCardType->GetValue(st.nCardType);
	parCardProcess->GetValue(st.nCardProcess);
	parCharge->GetValue(st.nCharge);
	parDisplayCharge->GetValue(st.strDisplayCharge);
	parTID->GetValue(st.strTID);
	parMID->GetValue(st.strMID);
	parSessionKey->GetValue(st.strSessionKey);
	parCardServerAddr->GetValue(st.strCardServerAddr);
	parCardServerPort->GetValue(st.uCardServerPort);
	parLogiServerAddr->GetValue(st.strLogiServerAddr);
	parLogiServerPort->GetValue(st.uLogiServerPort);
	parFeeType->GetValue(st.nFeeType);	
	parError->GetValue(st.strError);

	return TRUE;
}

CString GetMyCardNumber(CString strCardNumber)
{
	CString strNew;

	if(strCardNumber.GetLength() == 0)
		return LITERAL_CARD_NUMBER;
	else
	{
		strNew.Format("%s-%s-%s-%s", GetMyNumberFadding(strCardNumber.Left(4)),
			GetMyNumberFadding(strCardNumber.Mid(4, 4)), 
			GetMyNumberFadding(strCardNumber.Mid(8, 4)),
			GetMyNumberFadding(strCardNumber.Mid(12, 4)));

		return strNew;
	}
}

BOOL SendNiceCardPay(CMkDatabase* pMkCardDb, int nTranType, int nTNo, int nBillkey, CString strCardNumber, CString strMM, CString strYY, CString strWCompany, CString strWNo, CString& strMsg, BOOL bSendSms)
{
	if(pMkCardDb == NULL)
	{
		MessageBox(NULL, "ī�弭���� ������ ������ �������� �ʾҽ��ϴ�", "Ȯ��", MB_ICONINFORMATION);
		return FALSE;
	}

	strCardNumber.Replace("-", "");
	//	szID,int nTNo,const char* szCardnumber,const char* szCardexpy,const char* szCardexpm
	QPACKET *rcv = NULL;
	char data[300];

	BOOL bRet = FALSE;
	int nSubType = PST_NICE_REQUSET_OK;

	if( nTranType == 0 )  
		nSubType = PST_NICE_REQUSET_CANCEL;

	//		ShowDlgBox(DETAIL_INFO_RECVING);
	//CShowDlgBox ShowDlgBox(nTranType == 1 ? L"ī�� ���� ��ȸ��" : L"ī�� ������� ��û��");
	char szPhoneNumber[20];
	//strcpy(szPhoneNumber, m_si.szPhoneNumber);
	strcpy(szPhoneNumber, m_ui.strID);
	STRCPY(data, szPhoneNumber,  VL_END);
	STRCAT(data, strWCompany, VL_END);
	STRCAT(data, strWNo, VL_END);
	STRCAT(data, ::GetStringFromLong(nTNo), VL_END);
	STRCAT(data, ::GetStringFromLong(nBillkey), VL_END);
	STRCAT(data, strCardNumber, VL_END);
	STRCAT(data, strMM, VL_END);
	STRCAT(data, strYY, VL_END);
	STRCAT(data, ::GetStringFromLong(bSendSms, TRUE), VL_END);

	if(!pMkCardDb->GetSocket()->SendData(PT_REQUEST, nSubType, data)) 
	{
		MessageBox(NULL, "ī��������� ���� ����\r\n�ٽýõ��ϼ���", "Ȯ��", MB_ICONERROR);
		return FALSE;
	}

	//if(!Socket->SendData(PT_REQUEST, nSubType, data))
	//	THROW("���۽���");

	rcv = (QPACKET*)pMkCardDb->GetSocket()->ReadStream();

	if(rcv == NULL)
	{
		MessageBox(NULL, "ī����� ��û ����\r\n�ٽýõ��ϼ���", "Ȯ��", MB_ICONERROR);
		return FALSE;
	}

	if(rcv != NULL) 
	{
		if(PT_OK == rcv->nType)
		{
			free(rcv);
			return TRUE;
		}
		else
		{
			int nRet = rcv->nSubType;
			strMsg = rcv->data;
			free(rcv);
			return FALSE;
		}
	}

	strMsg = rcv->data;
	if(rcv->nType == PT_OK) bRet=  TRUE;
	else bRet =  FALSE;

	if(rcv != NULL)
		free(rcv);

	return bRet;

	return FALSE;
}

CString GetMyNumberFadding(CString strNumber, int nLen)
{
	if(nLen < strNumber.GetLength())
		return strNumber;
	else
	{
		while(nLen < strNumber.GetLength())
			strNumber = "0" + strNumber;
		return strNumber;
	}
}

CString GetDay(COleDateTime dt)
{
	char *szDayOfWeek[] = {"��", "��", "ȭ", "��", "��", "��", "��"};

	CString strDayOfWeek;
	strDayOfWeek.Format("%s", szDayOfWeek[dt.GetDayOfWeek() - 1]);

	return strDayOfWeek;
}

BOOL IsCardCheckState(long nState, long nCancelType)
{
	if(nState == STATE_CANCELED && nCancelType == 10)
		return TRUE;

	if(nState == STATE_WAIT ||
		nState == STATE_OK ||
		nState == STATE_OK_ONLY_MAN ||
		nState == STATE_ALLOCATED ||
		nState == STATE_FINISH)
		return TRUE;
	else
		return FALSE;
}

long GetCardRealPay(long nTNo) 
{
	CMkCommand cmd(m_pMkDb, "select_card_original_pay");
	CMkParameter *pParCharge = cmd.AddParameter(typeLong, typeReturn, 0);
	cmd.AddParameter(nTNo);

	if(!cmd.Execute())
		return 0;

	long nCharge;
	pParCharge->GetValue(nCharge);

	return nCharge;
}

CString GetShareAccountType(long nType)
{
	CString strTemp = "";
	switch(nType)
	{
	case 1:
		strTemp = "(*)�����ü�Ϸ�";
	case 2:
		strTemp = "(*)��������ü�Ϸ�";
	case 3:
		strTemp = "(*)�����������";
	case 4:
		strTemp = "(*)�����������";
	case 5:
		strTemp = "(*)��Ÿ";
	case 6:
		strTemp = "(*)��ݿ�û����";
	case 7:
		strTemp = "(*)�ܾ׺�����ü����";

	case 30:
		strTemp = "(-)��ü";
	case 31:
		strTemp = "(-)����";
	case 32:
		strTemp = "(-)�������";
	case 33:
		strTemp = "(-)�Աݾ׼���";
	case 34:
		strTemp = "(-)�ܻ�����";
	case 35:
		strTemp = "(-)�ܻ��������";
	case 36:
		strTemp = "(-)�ܻ��������";
	case 37:
		strTemp = "(-)��ݿ�û��";
	case 38:
		strTemp = "(-)�����δ��";
	case 39:
		strTemp = "(-)����������";

	case 100:
		strTemp = "(-)��Ÿ";


	case 130:
		strTemp = "(+)��ü";
	case 131:
		strTemp = "(+)����";
	case 132:
		strTemp = "(+)�������";
	case 133:
		strTemp = "(+)�Աݾ׼���";
	case 134:
		strTemp = "(+)�ܻ�����";
	case 135:
		strTemp = "(+)�ܻ��������";
	case 136:
		strTemp = "(+)�ܻ��������";
	case 137:
		strTemp = "(+)������";
	case 138:
		strTemp = "(+)�����δ��";
	case 139:
		strTemp = "(+)����������";


	case 200:
		strTemp = "(+)��Ÿ";

	}

	return strTemp;
}

long GetShareLevel(long nShareCode1, long nShareCode2, long nShareCode3, long nShareCode4, long nShareCode5)
{
	if(m_ci.m_nShareCode1 == nShareCode1 && nShareCode1 != 0)
		return 1;
	else if(m_ci.m_nShareCode2 == nShareCode2 && nShareCode2 != 0)
		return 2;
	else if(m_ci.m_nShareCode3 == nShareCode3 && nShareCode3 != 0)
		return 3;
	else if(m_ci.m_nShareCode4 == nShareCode4 && nShareCode4 != 0)
		return 4;
	else if(m_ci.m_nShareCode5 == nShareCode5 && nShareCode5 != 0)
		return 5;

	return 6;
}

CString ChangeStringFromExcel(VARIANT varValue)
{
	CString strVal= "";
	if(varValue.vt == VT_BSTR)
		strVal = varValue.bstrVal;
	else if(varValue.vt == VT_EMPTY)
		strVal = "";
	else if(varValue.vt == VT_NULL)
		strVal = "NULL";
	else if(varValue.vt == VT_BOOL) // *    VARIANT_BOOL   VT_BOOL
		strVal.Format("%b", varValue.boolVal);

	else if(varValue.vt == VT_I2)
		strVal.Format("%d",(int)varValue.iVal);	
	else if(varValue.vt == VT_I4)
		strVal.Format("%d",(int)varValue.lVal);
	else if(varValue.vt == VT_R4) // *    FLOAT          VT_R4
		strVal.Format("%2lf", (double)varValue.fltVal);
	else if(varValue.vt == VT_R8)
		strVal.Format("%ld",(long)varValue.dblVal);		
	else if(varValue.vt == VT_DATE) // *    DATE           VT_DATE
	{
		COleDateTime dtOle(varValue.date);	
		strVal =dtOle.Format("%Y-%m-%d %H:%M:%S");
	}
	else if(varValue.vt == VT_INT) // *    INT            VT_INT
		strVal.Format("%d", varValue.intVal);
	else if(varValue.vt == VT_I1) // *    CHAR           VT_I1
		strVal.Format("%c", varValue.cVal);

	return strVal;
}

CString GetFolderDate(CString strFileName)
{
	int nIndex = 0;
	for(int i = 0; i < 3; i++)
	{
		if(strFileName.Find("-", nIndex + 1) != -1 
			&& strFileName.Find("-", strFileName.Find("-", nIndex + 1)) != -1)
			nIndex = strFileName.Find("-", strFileName.Find("-", nIndex + 1));
	}

	CString strDate = strFileName.Mid(nIndex + 1, 8);

	if(nIndex == 0 || strDate.GetLength() != 8)
		return "";

	return strDate;
}

long GetRemoveMyNumberFormat(CString strNumber)
{
	strNumber.Replace(",", "");
	return atoi(strNumber);
}

void MoveFocus(CWnd *pWnd)
{
	pWnd->SetFocus();
}

BOOL IsUseNewDlg()
{
	return AfxGetApp()->GetProfileInt("RcpPage", "bUseNewRcpDlg", 0);
}

CString RemoveComma(CString strNumber)
{
	strNumber.Remove(',');
	return strNumber;
}
        
CString GetStringFromEdit(CWnd *pEdit)
{
	if(pEdit == NULL)
		return 0;

	CString strTemp;
	pEdit->GetWindowText(strTemp);
	return strTemp;
};

long GetLongFromEdit(CWnd *pEdit)
{
	if(pEdit == NULL)
		return 0;

	CString strTemp;
	pEdit->GetWindowText(strTemp);
	strTemp.Replace(",", "");
	return atoi(strTemp);
};

CString GetRemoveLastDong(CString strDong)
{
	if(strDong.GetLength() <= 4)
		return strDong;

	if(strDong.Right(2) == "��")
		return strDong.Left(strDong.GetLength() - 2);

	return strDong;
}

BOOL IsDate(CString strTemp)
{
	if(strTemp.Find("/") >= 0 || strTemp.Find(":") >= 0 || strTemp.Find("-") >= 0)
	{ 
		BOOL bFindA = strTemp.Replace("/", "");
		BOOL bFindB = strTemp.Replace(":", ""); 
		BOOL bFindC = strTemp.Replace("-", "");
		strTemp.Replace(" ", "");

		if(::IsStringDigit(strTemp))  
		{
			if((strTemp.Left(2) = "01") && 
				((strTemp.GetLength() == 10 || strTemp.GetLength() == 11) && bFindB == FALSE)) //�޴���
				return FALSE;
			else if((strTemp.GetLength() == 7 || strTemp.GetLength() == 8) && bFindB == FALSE)//�Ϲ���ȭ
				return FALSE;
			else
				return TRUE;
		}
		else
			return FALSE;
	}
	else
		return FALSE;

}

CString GetRiderPhone(long nRiderCompany, long nRNo)
{
	if (nRiderCompany == 0 || nRNo == 0)
		return "";

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_phone");

	pCmd.AddParameter(nRiderCompany);
	pCmd.AddParameter(nRNo);

	CString strPhone = "";

	if(pRs.Execute(&pCmd))
		pRs.GetFieldValue("sHp", strPhone);

	return strPhone;
}

CString GetDashCardNumber(CString strCardNumber)
{
	CString strNumber = strCardNumber;

	strNumber.Remove('-');

	if(strNumber.GetLength() > 6)
	{
		CString strTemp = "";

		for(int i=0; i<strNumber.GetLength(); i++)
		{
			strTemp += strNumber.GetAt(i);
  
			if(i%4 == 3) 
				strTemp += "-";
		}

		if(strTemp.Right(1) == "-")
			strTemp = strTemp.Left(strTemp.GetLength() - 1);

		strNumber = strTemp;
	}		

	return strNumber;
}

BOOL UpdateRiderCardState(CString strCardNumber, long nCompany, long nRNo, CString &strRName)
{
	CMkCommand cmd(m_pMkDb, "VRCardRider_update_1");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);

	cmd.AddParameter(strCardNumber);
	cmd.AddParameter(nCompany);
	cmd.AddParameter(nRNo);
	cmd.AddParameter(0);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);
	CMkParameter *parOut = cmd.AddParameter(typeString, typeOutput, 200, "");
	CMkParameter *parRName = cmd.AddParameter(typeString, typeOutput, 50, "");

	if(!cmd.Execute())
		return FALSE;

	long nRet; parRet->GetValue(nRet);
	CString strError; parOut->GetValue(strError);
	parRName->GetValue(strRName);

	if(nRet == 0)
	{
		MessageBox(NULL, strError, "Ȯ��", MB_ICONINFORMATION);
		return FALSE;
	}

	return TRUE;
}

BOOL InsertNewCard(CString strCardNumber, long nCompany, long nRNo)
{
	CMkCommand cmd(m_pMkDb, "VRCardRider_Insert_1");
	cmd.AddParameter(m_ci.m_nShareCode1);
	cmd.AddParameter(nCompany);
	cmd.AddParameter(nRNo);
	cmd.AddParameter(strCardNumber);
	cmd.AddParameter(1);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);
	cmd.AddParameter("");
	CMkParameter *parError = cmd.AddParameter(typeString, typeOutput, 200, "");

	if(!cmd.Execute())
		return FALSE;

	CString strError; parError->GetValue(strError);

	if(!strError.IsEmpty())
	{
		MessageBox(NULL, strError, "Ȯ��", MB_ICONINFORMATION);
		return FALSE;
	}

	return TRUE;
}

int GetDistanceMeter(long nPosX, long nPosY, long nPosX2, long nPosY2)
{
	double dx = (nPosY2 - nPosY) * 0.30918467038935;
	double dy = (nPosX2 - nPosX) * cos((nPosY2 + nPosY) * 0.000000024240661) * 0.30918467038935;
	return sqrt(dx*dx + dy*dy);
}

BOOL MakeShareOrder(long nTNo, BOOL bShare)
{
	CMkCommand pCmd(m_pMkDb, "make_shared_order_3"); 
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(bShare);
	pCmd.AddParameter(m_ui.strName);

	return pCmd.Execute();
}

DWORD HexStrToInt(CString aStr)
{
	DWORD        i;
	char         * string, * stopstring;

	string = (char *)(LPCTSTR)aStr;
	strtod(string, &stopstring);
	i = (DWORD)strtoul(string, &stopstring, 16);
	return i;
}

CString GetCustomerEMail(long nCNo)
{
	CString strEMail = "";

	CMkCommand cmd(m_pMkDb, "select_customer_email");
	cmd.AddParameter(nCNo);
	CMkParameter *parID = cmd.AddParameter(typeString, typeOutput, 100, "");	

	if(!cmd.Execute())
		return "";

	parID->GetValue(strEMail);

	return strEMail;
}

BOOL IsMobilePhoneNumber(CString strText)
{
	if(strText.Left(2) == "01" && IsStringDigit(strText) && (strText.GetLength() == 10 || strText.GetLength() == 11))
		return TRUE;

	return FALSE;
}

BOOL IsNumber(LPCTSTR pszText)
{
	ASSERT_VALID_STRING( pszText );

	for( int i = 0; i < lstrlen( pszText ); i++ )
		if( !_istdigit( pszText[ i ] ) )
			return false;

	return true;
}

void AddTextMiddle(CString strText, CEdit *pEdit)
{
	CString strInput; pEdit->GetWindowText(strInput);

	CStringW strTextW(strText); 
	CStringW sInputW(strInput);

	int nStartSel, nDestSel; 

	pEdit->GetSel(nStartSel, nDestSel);

	if(nStartSel == -1) return; 

	CString sResult = CString(strInput.Left(nStartSel)) + CString(strTextW) + CString(strInput.Right(strInput.GetLength() - nDestSel));
	pEdit->SetWindowText(sResult);

	pEdit->SetFocus();
	pEdit->SetSel(nStartSel + strText.GetLength(), nStartSel + strText.GetLength());
}

BOOL UpdateSaveMent(long nID, CString strMent)
{
	CMkCommand cmd(m_pMkDb, "update_save_sms_ment");
	cmd.AddParameter(nID);
	cmd.AddParameter(strMent);

	return cmd.Execute();
}

BOOL InsertSaveMent(long nCompany, long nType, CString strMent)
{
	CMkCommand cmd(m_pMkDb, "insert_save_sms_ment");
	cmd.AddParameter(nCompany);
	cmd.AddParameter(nType);
	cmd.AddParameter(strMent);

	return cmd.Execute();
}

BOOL SendSmsBulkTest(long nCompany, long nTranID, CString strRecvPhone, CString strCallBackPhone,
								CString strMsg, CString strEtc)
{
	strRecvPhone.Replace("-", "");
	strCallBackPhone.Replace("-", "");

	CMkCommand cmd(m_pMkDb, "insert_sms_data_for_bulk_test");
	cmd.AddParameter(nCompany);
	cmd.AddParameter(nTranID);
	cmd.AddParameter(strRecvPhone);
	cmd.AddParameter(strCallBackPhone);
	cmd.AddParameter(strMsg);
	cmd.AddParameter(strEtc);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);

	return cmd.Execute();
}

BOOL DeleteSaveMent(long nID)
{
	CMkCommand cmd(m_pMkDb, "delete_save_sms_ment");
	cmd.AddParameter(nID);

	return cmd.Execute();
}

BOOL UpChargeForNotAllocate(long nTNo, long nCharge, CWnd *pMsgBox)
{
	CMkCommand cmd(m_pMkDb, "update_charge_for_not_allocate_1");
	CMkParameter *pParRet = cmd.AddParameter(typeLong, typeReturn, 0);
	cmd.AddParameter(nTNo);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.strName);
	cmd.AddParameter(nCharge);

	cmd.Execute();	

	long nRet; pParRet->GetValue(nRet);

	if(nRet == 1)
	{
		if(nCharge == -1)
		{
			if(pMsgBox)
				pMsgBox->MessageBox("����λ��� �����Ǿ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		}
		else
		{
			if(pMsgBox)
				pMsgBox->MessageBox("�ݾ��� �߰��Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		}

		return TRUE;
	}
	else
	{
		if(pMsgBox)
			pMsgBox->MessageBox("����λ� ����� ������� �ʰų� ������ �������� �ʽ��ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		return FALSE;
	}
}


CString GetSecondTimeString(int nSec, BOOL bRemoveSec)
{
	int nAbsSec = abs(nSec);
	CString strTime;

	if(bRemoveSec)
	{
		if(nAbsSec <= 30)
			strTime = "";
		else if(nAbsSec < 60)
			strTime.Format("%d��", nAbsSec);
	}
	else
	{
		if(nAbsSec <= 1)
			strTime = "-";
		else if(nAbsSec < 60)
			strTime.Format("%d��", nAbsSec);
		else
			strTime.Format("%d��%d��", nAbsSec / 60, nAbsSec % 60);
	}

	return strTime;
}

CString GetAsteriskPhoneNumber(CString strPhoneNumber)
{
	CString strNumber = GetDashPhoneNumber(strPhoneNumber);

	if(strPhoneNumber.GetLength() < 6)
		return strNumber; 

	long nIndex = strNumber.ReverseFind('-'); 

	if(nIndex < 0 )
		return strNumber;

	//strNumber = strNumber.Left(nIndex-1) + "*" + strNumber.Mid(nIndex, 3) + "**";
	strNumber = strNumber.Left(nIndex+1) + "****";

	return strNumber;
}

BOOL InsertAllocGroupCombo(CComboBox *pCombo, long nCompany)
{
	pCombo->ResetContent();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_alloc_group");

	cmd.AddParameter(nCompany);

	if(!rs.Execute(&cmd)) return FALSE;

	if(rs.GetRecordCount() != 10) return FALSE;

	long nItem = 0;

	pCombo->InsertString(nItem, "�׷��Ͼȵ�");
	pCombo->SetItemData(nItem++, 0);

	long nID, nGrade;
	CString strGroupName, strDisplay;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("nGrade", nGrade);
		rs.GetFieldValue("sGroupName", strGroupName);

		strDisplay.Format("%s [%d]���",strGroupName, nGrade);

		pCombo->InsertString(nItem, strDisplay);
		pCombo->SetItemData(nItem++, nGrade);
		//pCombo->SetItemData(nItem++, nID);

		rs.MoveNext();
	}

	pCombo->SetCurSel(0);
	return TRUE;
}

CString GetAutoDDDSetting(int nCompany, CString strCallingLine)
{
	CString strRet = strCallingLine;

	if(strRet == "")
		strRet = GetBranchInfo(nCompany)->strCallingLine;

	if(strRet == "")
		strRet = "9";

	if(strRet.Find("A") != -1)
	{
		CString strTemp = strRet.Left(1);
		if(strTemp != "0" && strTemp != "1")
			//strRet = GetBranchInfo(nCompany)->strDDD + strRet;
			strRet = m_ci.m_strDDD + strRet;
	}
	return strRet;
}

BOOL GetConnetcInfo(CString &strAddr, long &nPort)
{
	strAddr = "";
	nPort = 0;

	CMkCommand cmd(m_pMkDb, "select_card_tran_info_for_connect");
	cmd.AddParameter(m_ui.nCompany);
	CMkParameter *pParAddr = cmd.AddParameter(typeString, typeOutput, 100, "");
	CMkParameter *pParPort = cmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

	if(!cmd.Execute())
		return FALSE;

	pParAddr->GetValue(strAddr);
	pParPort->GetValue(nPort);

	if(!strAddr.IsEmpty() && nPort > 0)
		return TRUE;

	return FALSE;

}

BOOL IsDID(int nDID, CString strSearchDID)
{
	if(strSearchDID.Find(",XXXXXXXX,") >= 0)
		return TRUE;

	CString strFindDID;
	strFindDID.Format(",%d,", nDID);
	if(strSearchDID.Find(strFindDID) >= 0)
		return TRUE;
	else
		return FindNumber(9, strFindDID, strSearchDID);

	return FALSE;
}

BOOL FindNumber(int nMaxIndex, CString strNumber, CString strTotalNumber)
{
	int nIndex = 2;
	while(nIndex < nMaxIndex && nIndex < strNumber.GetLength() - 1)
	{
		CString strTemp;
		for(int i = 1; i < nIndex; i++)
			strTemp += "X";

		strNumber = strNumber.Left(strNumber.GetLength() - nIndex) + strTemp + ",";

		if(strTotalNumber.Find(strNumber) >= 0)
			return TRUE;

		nIndex++;
	}
	return FALSE;
}

BOOL UpdateRiderInfoForReserved(long nTNo, long nRiderCompany, long nRNo)
{
	CMkCommand cmd(m_pMkDb, "update_rider_for_reserved");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(nTNo);
	cmd.AddParameter(nRiderCompany);
	cmd.AddParameter(nRNo);

	if(!cmd.Execute())
		return FALSE;

	long nRet; parRet->GetValue(nRet);

	if(nRet == 1)
		return TRUE;
	
	return FALSE;



}

CString GetSMSCallBackLogState(int nState)
{
	CString strState = "";
	switch(nState)
	{
	case 0:
		strState = "";
		break;

	case 10:
		strState = "��Ż������ �ݷ�";
		break;
	case 11:
		strState = "��Ż������ �ݷ����";
		break;
	case 12:
		strState = "�����/���νź��� �ݷ�";
		break;
	case 13:
		strState = "�����/���νź��� �ݷ����";
		break;

	case 20:
		strState = "PBX ��ϼ��� �ݷ�";
		break;
	case 21:
		strState = "PBX ��ϼ��� �ݷ����";
		break;
	case 22:
		strState = "PBX ��ϼ��� ��������";
		break;
	case 23:
		strState = "PBX ��ϼ��� ��Ż� �ݼ�";
		break;
	case 24:
		strState = "PBX ��ϼ��� ��Ż����";
		break;




	case 30:
		strState = "��������";
		break;
	case 31:
		strState = "�����������";
		break;

	case 38:
		strState = "�����ź�";
		break;


	case 40:
		strState = "����";
		break;
	case 41:
		strState = "������� �����";
		break;
	case 42:
		strState = "������� ��������";
		break;

	case 51:
		strState = "��������";
		break;
	case 52:
		strState = "�����޸�";
		break;
	case 53:
		strState = "��ü�޸�";
		break;



	case 70:
		strState = "�������ǻ���";
		break;



	case 500:
		strState = "�������";
		break;
	case 501:
		strState = "��������";
		break;

	}
	return strState;
}

BOOL CheckTel(CString strTel)
{

	if(CHECK_TEL_BYPASS == TRUE) return TRUE;

	CString strTempTel = strTel;

	if(strTempTel.GetLength() <= 0 )
	{
		AfxMessageBox("�߽��ڹ�ȣ ���� ������ ����ϼ���", MB_ICONERROR);
		return FALSE;
	}


	strTempTel.Replace("-", "");
	if( !IsStringDigit( strTempTel ) )
	{
		AfxMessageBox("��ȭ��ȣ�� �����̾�߸� �մϴ�", MB_ICONERROR);
		return FALSE;
	}


	if(strTempTel.GetLength() < 8)
	{
		AfxMessageBox("��ȭ��ȣ�� 8�ڸ� �̻��̾�߸�(������ȣ����) �մϴ�", MB_ICONERROR);
		return FALSE;
	}

	if(strTempTel.GetLength() > 12)
	{
		AfxMessageBox("��ȭ��ȣ�� 12�ڸ� �����̾�߸� �մϴ�", MB_ICONERROR);
		return FALSE;
	}

	if(strTempTel.Left(1).Compare("0") != 0 &&  strTempTel.Left(1).Compare("1") != 0)
	{
		AfxMessageBox("��ȭ��ȣ�� ù��° �ڸ��� 0, 1 �̾��մϴ� (������ȣ �߰�) ", MB_ICONERROR);
		return FALSE;
	}


	if(strTempTel.Left(2) == "01")
	{

		if( !
			( 
			strTempTel.Left(3).Compare("010") == 0 || strTempTel.Left(3).Compare("011") == 0 || 
			strTempTel.Left(3).Compare("017") == 0 || strTempTel.Left(3).Compare("018") == 0 ||
			strTempTel.Left(3).Compare("016") == 0 
			) 
			)
		{
			AfxMessageBox("�ڵ��� ��ȣ�� ���Ŀ� ���� �ʽ��ϴ�. ", MB_ICONERROR);
			return FALSE;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	if(   strTempTel.Left(1).Compare("1") == 0 )
	{
		if(  strTempTel.GetLength() != 8  )
		{
			AfxMessageBox("��ȭ��ȣ�� ù��° �ڸ��� 1 �� ������ȣ�� 8�ڸ��̾�� �մϴ� ", MB_ICONERROR);
			return FALSE;
		}
		else
			return TRUE;

	}



	if(
		strTempTel.Left(3).Compare("010") == 0 || strTempTel.Left(3).Compare("011") == 0 || 
		strTempTel.Left(3).Compare("017") == 0 || strTempTel.Left(3).Compare("018") == 0 ||
		strTempTel.Left(3).Compare("016") == 0 
		) 
	{

		if(strTempTel.Mid(3, 1) == "0" ||
			strTempTel.Mid(3, 1) == "1")
		{
			AfxMessageBox("�̵���ȭ����� ��Ģ�� ���� �ʽ��ϴ�", MB_ICONERROR);
			return FALSE;
		}

		if( !( strTempTel.Mid(4).GetLength() == 7 || strTempTel.Mid(4).GetLength() == 8 )  )
		{
			AfxMessageBox("�ڵ��� ��ȣ�� ������ ���� 7 ~ 8�ڸ��̾�� �մϴ� ", MB_ICONERROR);
			return FALSE;
		}
		else
			return TRUE;
	}



	CString strRemoveDDD = "";
	BOOL bLocalNumber = IsLocalNumber(strTempTel, strRemoveDDD);

	if(bLocalNumber)
	{
		if(strRemoveDDD.GetLength() != 7 && 
			strRemoveDDD.GetLength() != 8)
		{
			AfxMessageBox("������ȣ�� DDD�� ���� 7 ~ 8�ڸ��̾�� �մϴ� ", MB_ICONERROR);
			return FALSE;
		}

		if(strRemoveDDD.Left(2) == "15" ||
			strRemoveDDD.Left(2) == "16" ||
			strRemoveDDD.Left(2) == "18")
		{
			AfxMessageBox("Ư����ȣ�� ������ȣ�� ���� �� �����ϴ�", MB_ICONERROR);
			return FALSE;
		}

		return TRUE;
	}


	// 050 060 070 080
	if( strTempTel.Left(3).Compare("050") == 0 || strTempTel.Left(3).Compare("060") == 0 || 
		strTempTel.Left(3).Compare("070") == 0 || strTempTel.Left(3).Compare("080") == 0 ||		
		strTempTel.Left(3).Compare("030") == 0
		) 	
	{
		if(strTempTel.Left(3).Compare("070") == 0 &&
			(strTempTel.Mid(3, 1) == "0" ||	strTempTel.Mid(3, 1) == "1") )
		{
			AfxMessageBox("�Ⱓ��Ż���� ��Ģ�� ���� �ʽ��ϴ�", MB_ICONERROR);
			return FALSE;
		}

		if( ! (strTempTel.Mid(3).GetLength() == 7 || strTempTel.Mid(3).GetLength() == 8 || strTempTel.Mid(3).GetLength() == 9) )
		{
			AfxMessageBox("050 060 070 080  ���� 7 ~ 9�ڸ��̾�� �մϴ� ", MB_ICONERROR);
			return FALSE;
		}
		else
			return TRUE;

	}

	/// �Ƚɹ�ȣ

	//�¼��ڷ���(���� 0503, 0504, 0507), KT(0502), LG���÷���(0503, 0505), SK��ε���(0506), SK�ڸ�ũ(0504)


	if( strTempTel.Left(4).Compare("0502") == 0 || strTempTel.Left(4).Compare("0503") == 0 || 
		strTempTel.Left(4).Compare("0504") == 0 || strTempTel.Left(4).Compare("0505") == 0 ||
		strTempTel.Left(4).Compare("0506") == 0 
		) 	
	{
		if( ! ( strTempTel.Mid(3).GetLength() == 7 || strTempTel.Mid(3).GetLength() == 8 ) )
		{
			AfxMessageBox("0502 ~ 6 �ȽŹ�ȣ�� ������ ���� 7 ~ 8�ڸ��̾�� �մϴ� ", MB_ICONERROR);
			return FALSE;
		}
		else
			return TRUE;

	}

	AfxMessageBox("�ش��ȣ�� ����� �� ���� ��ȣ �Դϴ�.  ", MB_ICONERROR);

	return FALSE;
}

BOOL IsLocalNumber(CString strPhone, CString &strRemoveDDD)
{
	CString str[] = {"02", "064", "051", "053", "032","062", "042",	"052", "044", "031", 
		"033", "043", "041", "063", "061", "054", "055"};

	long nCount = sizeof(str) / sizeof(str[0]);

	for(int i=0; i<nCount; i++)
	{
		CString strLocal = str[i];

		if(strPhone.Left(strLocal.GetLength()) == strLocal)
		{
			strRemoveDDD = strPhone.Right(strPhone.GetLength() - strLocal.GetLength());
			return TRUE;
		}		
	}

	return FALSE;
}

CString ConvertStringToSendData(CString strText)
{
	CByteArray msg;
	return ConvertStringToSendData(strText, msg);
}

CString ConvertStringToSendData(CByteArray *msg)
{
	CString strItemSum = "";
	CString strItem;
	//char szData[10000];

	for(int i = 0; i < (int)msg->GetSize(); i++) 
	{
		strItem.Format("%02X", (BYTE)msg->GetAt(i));
		strItemSum += "%" + strItem;
		//sprintf(&szData[i * 2], "%02X", (BYTE)msg->GetAt(i));
	}

	return strItemSum;
}

CString ConvertStringToSendData(const CString & s, CByteArray & msg)
{
	BOOL bSuccess = FALSE;
#ifdef _UNICODE
	int n = ::WideCharToMultiByte(CP_UTF8, 0, s, -1, NULL, 0, NULL, NULL);
	if(n == 0)
	{ /* failed */
		DWORD err = ::GetLastError();
		msg.SetSize(0);
		bSuccess = FALSE;
	} /* failed */
	else
	{ /* success */
		msg.SetSize(n);
		n = ::WideCharToMultiByte(CP_UTF8, 0, s, -1, (LPSTR)msg.GetData(), n, NULL, NULL);
		if(n == 0)
		{ /* conversion failed */
			DWORD err = ::GetLastError();
			msg.SetSize(0);
			bSuccess = FALSE;
		} /* conversion failed */
		else
		{ /* use multibyte string */
			msg.SetSize(n - 1);
			bSuccess = TRUE;
		} /* use multibyte string */
	} /* success */
#else // ANSI
	CArray<WCHAR, WCHAR> wc;

	int n = ::MultiByteToWideChar(CP_ACP, 0, s, -1, NULL, 0);
	if(n == 0)
	{ /* failed */
		DWORD err = ::GetLastError();
		msg.SetSize(0);
		bSuccess = FALSE;
	} /* failed */
	else
	{ /* success */
		wc.SetSize(n);
		n = ::MultiByteToWideChar(CP_ACP, 0, s, -1, wc.GetData(), n);
	} /* success */     

	n = ::WideCharToMultiByte(CP_UTF8, 0, wc.GetData(), -1, NULL, 0, NULL, NULL);
	if(n == 0)
	{ /* failed */
		DWORD err = ::GetLastError();
		msg.SetSize(0);
		bSuccess = FALSE;
	} /* failed */
	else
	{ /* success */
		msg.SetSize(n);
		n = ::WideCharToMultiByte(CP_UTF8, 0, wc.GetData(), -1, (LPSTR)msg.GetData(), n, NULL, NULL);
		if(n == 0)
		{ /* conversion failed */
			DWORD err = ::GetLastError();
			msg.SetSize(0);
			bSuccess = FALSE;
		} /* conversion failed */
		else
		{ /* use multibyte string */
			msg.SetSize(n - 1);
			bSuccess = TRUE;
		} /* use multibyte string */
	} /* success */
#endif

	if(bSuccess)
		return ConvertStringToSendData(&msg);

	return "";
}

void FillSpeicalTruckChage()
{
	g_special_truck_charge.clear();

	int company_code, car_type;

	CMkRecordset rs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "special_truck_charge_select");
	pCmd.AddParameter(m_ci.m_nCompanyCode);

	if(rs.Execute(&pCmd)) {
		while(!rs.IsEOF()) {
			rs.GetFieldValue("company_code", company_code);
			rs.GetFieldValue("car_type", car_type);

			MAP_SPECIAL_TRUCK_CHARGE::iterator it = g_special_truck_charge.find(make_pair(company_code, car_type));

			if(it == g_special_truck_charge.end()) {
				ST_SPECIAL_TRUCK_CHARGE st;
				g_special_truck_charge.insert(make_pair(make_pair(company_code, car_type), st));
				it = g_special_truck_charge.find(make_pair(company_code, car_type));
			}

			rs.GetFieldValue("jabara_add", it->second.jabara_add);
			rs.GetFieldValue("lift_add", it->second.lift_add);
			rs.GetFieldValue("wing_body_add", it->second.wing_body_add);
			rs.GetFieldValue("lift_wing_add", it->second.lift_wing_add);
			rs.GetFieldValue("freezer_add", it->second.freezer_add);

			rs.MoveNext();
		}
	}
}

BOOL IsCarTypeTruck(int car_type) 
{
	return car_type == CAR_TRUCK ||
		car_type == CAR_1_4_TON ||
		car_type == CAR_2_5_TON ||
		car_type == CAR_3_5_TON ||
		car_type == CAR_5_TON ||
		car_type == CAR_5_TON_PLUS ||
		car_type == CAR_8_TON ||
		car_type == CAR_11_TON ||
		car_type == CAR_14_TON ||
		car_type == CAR_15_TON ||
		car_type == CAR_18_TON ||
		car_type == CAR_25_TON;

}

bool IsHangul(const char* text)
{
	bool hangul = true;

	for (int i = 0; i < strlen(text); i++){
		if ((text[i] & 0x80) != 0x80)
			hangul = false;
	}

	return hangul;
}

std::vector<CString> GetNeighboringCity(CString sido)
{
	std::vector<CString> vec;
	if (sido == "����") {
		vec.push_back("����");
		vec.push_back("���");
		vec.push_back("��õ");
	}
	else if (sido == "��õ") {
		vec.push_back("��õ");
		vec.push_back("����");
		vec.push_back("���");
	}
	else if (sido == "���") {
		vec.push_back("���");
		vec.push_back("����");
		vec.push_back("��õ");
	}
	else if (sido == "����") {
		vec.push_back("����");
	}
	else if (sido == "���") {
		vec.push_back("���");
		vec.push_back("����");
		vec.push_back("����");
		vec.push_back("�泲");
	}
	else if (sido == "�泲") {
		vec.push_back("�泲");
		vec.push_back("����");
		vec.push_back("����");
		vec.push_back("���");
	}
	else if (sido == "����") {
		vec.push_back("����");
		vec.push_back("����");
		vec.push_back("�泲");
		vec.push_back("���");
	}
	else if (sido == "����") {
		vec.push_back("����");
		vec.push_back("����");
		vec.push_back("�泲");
		vec.push_back("���");
	}
	else if (sido == "����") {
		vec.push_back("����");
		vec.push_back("����");
		vec.push_back("����");
	}
	else if (sido == "����") {
		vec.push_back("����");
		vec.push_back("����");
		vec.push_back("����");
	}
	else if (sido == "����") {
		vec.push_back("����");
		vec.push_back("����");
		vec.push_back("����");
	}
	else if (sido == "���") {
		vec.push_back("���");
		vec.push_back("�뱸");
		vec.push_back("���");
		vec.push_back("�泲");
		vec.push_back("�λ�");
	}
	else if (sido == "�泲") {
		vec.push_back("�泲");
		vec.push_back("�뱸");
		vec.push_back("�λ�");
		vec.push_back("���");
		vec.push_back("���");
	}
	else if (sido == "�뱸") {
		vec.push_back("�뱸");
		vec.push_back("���");
		vec.push_back("�泲");
		vec.push_back("���");
		vec.push_back("�λ�");
	}
	else if (sido == "���") {
		vec.push_back("���");
		vec.push_back("�λ�");
		vec.push_back("���");
		vec.push_back("�泲");
		vec.push_back("�뱸");
	}
	else if (sido == "�λ�") {
		vec.push_back("�λ�");
		vec.push_back("�泲");
		vec.push_back("���");
		vec.push_back("�뱸");
		vec.push_back("���");
	}
	else if (sido == "����") {
		vec.push_back("����");
	}

	return vec;
}