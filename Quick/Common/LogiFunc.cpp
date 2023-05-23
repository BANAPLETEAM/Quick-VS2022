#include "stdafx.h"
#include "quick.h"
#include "LogiFunc.h"

#include "MainFrm.h"
#include "BillDlg.h"
#include "LogiMapCns.h"
#include "FakeDlg.h"
#include "CheckGroupReportDlg.h"
#include <math.h>
#include "Wql.h"

//DWORD CLogiFunc::m_dwLastInput = GetTickCount();
//CArray<MONITORINFOEX, MONITORINFOEX> CLogiFunc::m_aryMonitors;

#define LINE_BUFFER_SIZE	2048
#define CHECK_TEL_BYPASS   0

COLORREF crRiderColor[] = { 
	RGB(255,255, 255),	//WHITE
	RGB(110, 110, 255), //BLUE
	RGB(0, 255, 0),		//GREEN
	RGB(255, 70, 70),	//RED
	RGB(175, 50, 255),	//PURPLE
	RGB(255, 255, 0),	//YELLOW
	RGB(0, 255, 255),	//SKY
	RGB(0, 0, 1), 
	RGB(0x4B, 0, 0x82), 
	RGB(0xFF, 0x0C, 0xCB), 
	RGB(0x2F, 0x4F, 0x4F), 
	RGB(0x77, 0x88, 0x99), 
	RGB(0xD8, 0xBF, 0xD8), 
	RGB(0x19, 0x19, 0x70) 
};



CLogiFunc::CLogiFunc()
{
	m_dwLastInput = GetTickCount();
}

CLogiFunc::~CLogiFunc()
{
}



CString CLogiFunc::GetMyNumberFormat(CString strNumber) 
{
	//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString strData;
	int i, j = 1;

	strNumber.Remove(',');

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

	return strData;
}

void CLogiFunc::FillBackground(CDC *pDC, CWnd *pWnd, COLORREF clrTop, COLORREF clrBottom)
{
	CRect rc;
	pWnd->GetClientRect(rc);

	for(int i = rc.top + 1; i < rc.bottom; i+= 1)
	{ 
		pDC->FillSolidRect(rc.left, i, rc.Width(), 1,  
			XTPDrawHelpers()->BlendColors(clrTop, clrBottom, 
			(float)(1.0 - ((i - rc.top)) / (float)rc.Height())));
	}
}

COLORREF CLogiFunc::GetRiderColor(int nColorType)
{
	if(nColorType < RC_WHITE || nColorType > RC_MIDNIGHT)
		nColorType = 0; 

	return crRiderColor[nColorType];
}

CString CLogiFunc::GetRiderColorString(int nColorType)
{
	const char szRiderColorString[][255] = { "white", "blue", "green", "red", "magenta", "yellow", "sky"};
	if(nColorType < RC_WHITE || nColorType > RC_SKY)
		nColorType = 0; 

	return szRiderColorString[nColorType];
}

CString CLogiFunc::GetTwoToneMarkup(CString strMsg1, CString strMsg2, 
									BOOL bHasHead, BOOL bHasTail,
									CString strColor1, CString strColor2,
									BOOL bBold1, BOOL bBold2)
{
	const char *szH = "<StackPanel VerticalAlignment='top' HorizontalAlignment='Left'><TextBlock Padding='8' >";
	const char *szT = "</TextBlock></StackPanel>";
	const char *szBH = "<Run Foreground='%s' FontWeight='%s'>";
	const char *szBT = "</Run>";

	CString strSet1, strSet2, strBody;
	strSet1.Format(szBH, strColor1, bBold1 ? "Bold" : "Normal");
	strSet2.Format(szBH, strColor2, bBold2 ? "Bold" : "Normal");

	strBody.Format("%s%s%s%s%s%s", strSet1, strMsg1, szBT, strSet2, strMsg2, szBT);
	if(bHasHead)
		strBody = CString(szH) + strBody;
	if(bHasTail)
		strBody = strBody + szT;

	return strBody;
}

void CLogiFunc::GetAutoGradientColor(COLORREF crSrc, COLORREF &crDst1, COLORREF &crDst2, long nScale)
{
	crDst1 = XTPDrawHelpers()->LightenColor(nScale, crSrc);
	crDst2 = XTPDrawHelpers()->DarkenColor(nScale, crSrc);
}

void CLogiFunc::FillGradient(CDC *pDC, COLORREF crBack, CRect rcClient, long nScale)
{
	if(crBack != 0 && crBack < RGB(255, 255, 255))
	{
		COLORREF crG1, crG2;
		CLogiFunc::GetAutoGradientColor(crBack, crG1, crG2, nScale);
		XTPDrawHelpers()->GradientFill(pDC, rcClient, crG1, crG2, FALSE);
	}
	else if(crBack == RGB(255, 255, 255))
	{
		pDC->FillSolidRect(rcClient, crBack);
	}
}

CString CLogiFunc::GetModuleFullPath()
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

BOOL CLogiFunc::OnMyCtlColor(CDC* pDC, CWnd* pWnd, UINT &nCtlColor, HBRUSH &hRetBrush)
{ 
	TCHAR buf[16];
	GetClassName(pWnd->GetSafeHwnd(), buf, sizeof(buf) / sizeof(TCHAR));

	if(strcmp(buf, "Edit") && strcmp(buf, "ComboLBox"))
	{
		DWORD dwStyle = pWnd->GetStyle();

		if((dwStyle & (BS_AUTORADIOBUTTON | BS_RADIOBUTTON | BS_AUTOCHECKBOX | BS_CHECKBOX)))  
		{	
			pDC->SetBkMode(TRANSPARENT);

			CDC MemDC;
			CRect rc;
			COLORREF crBack;

			pWnd->GetWindowRect(&rc);
			CWnd *pParent = pWnd->GetParent();
			pParent->ScreenToClient(&rc);
			CDC *pParentDC = pParent->GetDC();
			crBack = pParentDC->GetPixel(rc.left - 1, rc.top + rc.Height() / 2);

			if((long)crBack < 0)
				crBack = pParentDC->GetPixel(rc.right + 1, rc.top + rc.Height() / 2);

			if((long)crBack < 0)
				crBack = pParentDC->GetPixel(rc.left + rc.Width(), rc.top - 1);

			pParent->ReleaseDC(pParentDC);

			if((long)crBack >= 0 && crBack != GetSysColor(COLOR_BTNFACE))
			{
				hRetBrush = m_HandleManager.GetBrushObject(crBack);
				return TRUE;
			}
		}  
		else if(nCtlColor == CTLCOLOR_STATIC)
		{
			pDC->SetBkMode(TRANSPARENT);
			hRetBrush = m_HandleManager.GetBrushObject(0, TRUE);;
			return TRUE;
		}
	}

	return FALSE;
}

CString CLogiFunc::GetMyFileVersion()
{
	CString strVersion;
	TCHAR szFullPath[MAX_PATH];
	if(GetModuleFileName(AfxGetInstanceHandle(), szFullPath, _MAX_PATH) > 0)
	{
		VS_FIXEDFILEINFO pvsf;

		PSTR sFileName = "C:\\SmartQ\\quick.exe"; //버젼올리기 비쥬얼 스튜디오에서 테스트 할려고 절대경로 넣엇습니다 choi

		if(GetFileVersion(sFileName, &pvsf))
			//if(GetFileVersion(szFullPath, &pvsf))
		{
			strVersion.Format("%d.%d%d",
				HIWORD(pvsf.dwFileVersionMS),
				LOWORD(pvsf.dwFileVersionMS),
				HIWORD(pvsf.dwFileVersionLS));
		}
	}
	return strVersion;
}


typedef HRESULT  (*RegServer)();

BOOL CLogiFunc::DllRegOcx(CString strPath)
{
	HINSTANCE hInstace = ::LoadLibrary(strPath);
	if(NULL != hInstace)
	{
		RegServer RegOcx = (RegServer)GetProcAddress(hInstace, "DllRegisterServer");
		HRESULT hr = RegOcx();
		if(FAILED(hr)) 
			return FALSE;
		return TRUE;
	}
	return FALSE;
}

BOOL CLogiFunc::IsAllocOrder(int nState, BOOL bIncludeFinishOrder)
{
	return nState >= 11 && nState <= (bIncludeFinishOrder ? 35 : 30);
}

void CLogiFunc::RepositionLogConsole()
{
	HWND hWnd = GetConsoleWindow();

	if(hWnd)
	{
		GetMonitorArray();

		if(m_aryMonitors.GetCount() >= 2)
		{
			for(int i = 0; i < m_aryMonitors.GetCount(); i++)
			{
				if(!(m_aryMonitors.GetAt(i).dwFlags & MONITORINFOF_PRIMARY))
				{
					CRect rc = m_aryMonitors.GetAt(i).rcWork;
					MoveWindow(hWnd, rc.left, rc.top, 700, rc.Height(), TRUE);
				}	
			}
		}
	}
}

BOOL CLogiFunc::GetHandleScreenSize(CWnd *pWnd, CRect &rcScreen)
{
	GetMonitorArray();

	CPoint ptWnd;
	CRect rcWnd;
	pWnd->GetWindowRect(rcWnd);
	ptWnd.x = (rcWnd.left + rcWnd.right) / 2;
	ptWnd.y = (rcWnd.top + rcWnd.bottom) / 2;

	if(m_aryMonitors.GetCount() >= 2)
	{
		for(int i = 0; i < m_aryMonitors.GetCount(); i++)
		{
			CRect rc(m_aryMonitors.GetAt(i).rcWork);

			if(rc.PtInRect(CPoint(ptWnd.x, ptWnd.y)))
			{
				rcScreen = rc;
				return TRUE;
			}	
		}
	}
	return FALSE;
}

BOOL CALLBACK MonitorEnumProc2(HMONITOR hMonitor,HDC hdcMonitor,LPRECT lprcMonitor,LPARAM dwData)
{
	MONITORINFOEX mi;
	CArray<MONITORINFOEX, MONITORINFOEX> *paryMonitors = (CArray<MONITORINFOEX, MONITORINFOEX>*)dwData;

	mi.cbSize=sizeof(MONITORINFOEX);
	GetMonitorInfo(hMonitor, (MONITORINFOEX*)&mi);
	paryMonitors->Add(mi);

	return TRUE;
}

void CLogiFunc::GetMonitorArray()
{
	HDC hDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	if(hDC)
	{
		m_aryMonitors.RemoveAll();
		::EnumDisplayMonitors(hDC,NULL,MonitorEnumProc2, (LPARAM)&m_aryMonitors);
		DeleteDC(hDC);
	}
}

CString CLogiFunc::GetZeroPadding(int nNumber, int nLen)
{
	CString strNumber;
	CString strFormat;
	strFormat.Format("%%0%dd", nLen);
	strNumber.Format(strFormat, nNumber);
	return strNumber;
}

CString CLogiFunc::GetElapsedTimeString(COleDateTimeSpan span, BOOL bRemoveSec)
{
	int nSec = (int)span.GetTotalSeconds();
	int nAbsSec = abs(nSec);
	CString strTime;

	if(bRemoveSec)
	{
		if(nAbsSec <= 30)
			strTime = "";
		else if(nAbsSec < 60)
			strTime.Format("%d초", nAbsSec);
	}
	else
	{
		if(nAbsSec <= 1)
			strTime = "-";
		else if(nAbsSec < 60)
			strTime.Format("%d초", nAbsSec);
		else if(nAbsSec < 600)
			strTime.Format("%d분%d초", nAbsSec / 60, nAbsSec % 60);
	}

	if(strTime.IsEmpty())
	{
		int nAbsMin = nAbsSec / 60;

		if(nAbsMin < 60)
			strTime.Format("%d분", nAbsMin);
		else if(nAbsMin < 60 * 4)
			strTime.Format("%d시간%d분", nAbsMin / 60, nAbsMin % 60);
		else if(nAbsMin < 60 * 24)
			strTime.Format("%d시간", nAbsMin / 60);
		else
			strTime.Format("%d일", nAbsMin / 60 / 24);
	}

	if(nSec > 0)
		strTime += "전";
	else 
		strTime += "후";

	return strTime;
}

void CLogiFunc::HideBehindControl(CWnd *pParent, CWnd *pWndInFrontOf, BOOL bHide, CPtrArray *ppaExceptWnd)
{
	CRect rcInFrontOf;

	CWnd *pWnd = pParent->GetWindow(GW_CHILD);
	pWndInFrontOf->GetWindowRect(rcInFrontOf);
	pParent->ScreenToClient(rcInFrontOf);

	while(pWnd)
	{
		if(ppaExceptWnd)
		{
			for(int i = 0; i < ppaExceptWnd->GetCount(); i++)
			{
				CWnd *pWndExcept = (CWnd*)ppaExceptWnd->GetAt(i);
				if(pWnd == pWndExcept)
				{
					pWnd = pWnd->GetNextWindow();
					continue;
				}
			}
		}

		if(pWnd != pWndInFrontOf)
		{
			CRect rc, rcIntersect;
			pWnd->GetWindowRect(rc);
			pParent->ScreenToClient(rc);

			rcIntersect.IntersectRect(rcInFrontOf, rc);

			if(!rcIntersect.IsRectEmpty())
				pWnd->ShowWindow(bHide ? SW_HIDE : SW_SHOW);
		}

		pWnd = pWnd->GetNextWindow();
	}
}

long CLogiFunc::GetControlDigit(CEdit *pEdit)
{
	CString strCharge;
	pEdit->GetWindowText(strCharge);
	strCharge.Remove(',');
	return atol(strCharge);
}

void CLogiFunc::MakeLineVertical(CDC *pDC, CWnd *pMain, CWnd *pLeftWnd, CWnd *pRightWnd, long nTopMargin, long nBottomMargin, long nSize, COLORREF rgb)
{
	CRect rc, rc1, rc2;
	pLeftWnd->GetWindowRect(rc1); pMain->ScreenToClient(rc1);
	pRightWnd->GetWindowRect(rc2); pMain->ScreenToClient(rc2);

	rc.top = rc1.top -  nTopMargin;
	rc.bottom = rc2.bottom + nBottomMargin;
	rc.left = rc1.right + ((rc2.left - rc1.right) / 2) - nSize / 2;
	rc.right = rc.left + nSize;
	pDC->FillSolidRect(rc, rgb);
}

void CLogiFunc::DrawRoundRect(CDC *pDC, CWnd *pMain, CWnd *pWnd1, CWnd *pWnd2, long nLeftMargin, long nTopMargin, long nRightMargin, long nBottomMargin, COLORREF rgb, BOOL bRound)
{
	CRect rc, rc1, rc2;
	pWnd1->GetWindowRect(rc1);
	pMain->ScreenToClient(rc1);

	rc.left = rc1.left;
	rc.top = rc1.top;

	if(pWnd2)
	{
		pWnd2->GetWindowRect(rc2); 
		pMain->ScreenToClient(rc2);

		rc.right = rc2.right;
		rc.bottom = rc2.bottom;
	}
	else
	{
		rc.right = rc1.right;
		rc.bottom = rc1.bottom;
	}

	DrawRoundRect(pDC, pMain, rc, nLeftMargin, nTopMargin, nRightMargin, nBottomMargin, rgb, bRound);
}

void CLogiFunc::DrawRoundRect(CDC *pDC, CWnd *pMain, CRect rc, long nLeftMargin, long nTopMargin, long nRightMargin, long nBottomMargin, COLORREF rgb, BOOL bRound)
{
	CPoint pt;
	pt.x = 18;    
	pt.y = 18;  

	rc.left = rc.left + nLeftMargin;
	rc.top = rc.top + nTopMargin;
	rc.right = rc.right + nRightMargin;
	rc.bottom = rc.bottom + nBottomMargin;

	CPen pen(PS_SOLID, 1, RGB(0xbb, 0xbb, 0xbb));
	CPen* pOldPen = pDC->SelectObject(&pen); 

	CBrush brush (rgb);  
	CBrush* pOldBrush; 
	pOldBrush = pDC->SelectObject(&brush);

	if(bRound)
		pDC->RoundRect(rc, pt);
	else  
	{
		pDC->FillSolidRect(rc, RGB(0xbb, 0xbb, 0xbb));
		rc.DeflateRect(1, 1, 1, 1);
		pDC->FillSolidRect(rc, rgb); 
	}

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush); 
}


void CLogiFunc::LoadRiderPhone()
{
	static bool bLoadRiderPhone = FALSE;

	if(bLoadRiderPhone)
		return;

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rider_phone_list");
	cmd.AddParameter(0);

	if(!rs.Execute(&cmd))
		return;

	CString strPhone;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("sTel", strPhone);
		m_mapRiderPhone.insert(MAP_PHONE::value_type(atoi(strPhone), strPhone));
		rs.MoveNext();
	}

	bLoadRiderPhone = TRUE;
}

void CLogiFunc::LoadNoSmsPhone(long nCompany)
{
	MAP_VEC_PHONE::iterator it = m_mapNosmsPhone.find(nCompany);

	if(it == m_mapNosmsPhone.end())
	{
		MAP_PHONE mapTemp;
		m_mapNosmsPhone.insert(MAP_VEC_PHONE::value_type(nCompany, mapTemp));
		it = m_mapNosmsPhone.find(nCompany);
	}
	else
		return;

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_no_sms_customer");
	cmd.AddParameter(nCompany);

	if(!rs.Execute(&cmd))
		return;

	CString strPhone;
	MAP_PHONE *mapTemp = &it->second;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("sTel", strPhone);
		mapTemp->insert(MAP_PHONE::value_type(atoi(strPhone), strPhone));
		rs.MoveNext();
	}
}

void CLogiFunc::FillEmotioconMap()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_emoticon");
	cmd.AddParameter(0);

	if(!rs.Execute(&cmd))
		return;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		ST_EMOTICON st;
		rs.GetFieldValue("nType", st.nType);
		rs.GetFieldValue("sChar", st.strEmoticon);

		m_mapEmoticon.insert(MAP_EMOTICON::value_type(i, st));

		rs.MoveNext();
	}
}

//////////////
//global
//////////////

BOOL CLogiFunc::POWER_CHECK(long nPower, CString strPowerName, BOOL bDisplayMsg)
{
	if (m_pi.GetPower(nPower))
		return TRUE;

	if (bDisplayMsg) {
		if (strPowerName.GetLength() > 0) {
			CString strMsg;
			strMsg.Format("[%s] 권한이 없습니다.", strPowerName);
			AfxGetMainWnd()->MessageBox(strMsg, "권한없음", MB_ICONINFORMATION);
		}
		else {
			AfxGetMainWnd()->MessageBox("접근 권한이 없습니다.", "권한없음", MB_ICONINFORMATION);
		}
	}
	return FALSE;
}

CString CLogiFunc::GetInternetReceiptType(int nReceiptType)
{
	if (nReceiptType <= 0)
		return "i";
	else if (nReceiptType == 1)
		return "w";
	else if (nReceiptType == 2)
		return "q";
	else
		return "i";
}



BOOL CLogiFunc::ConnectDrvLicSvr()
{
	if (NULL == m_pMkDb4DrvLic)
	{
		m_pMkDb4DrvLic = new CMkDatabase(g_bana_log);
		BYTE nXorKey = (m_pMkDb4DrvLic->GetXorKey() + 3) % 128;
		BYTE des_key_new[] = { 29,44,2,83,32,98,10,8 };
		BYTE nXoredKey[8];

		for (int i = 0; i < 8; i++)
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
		info.bManager = 0;
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
		if (FALSE == bRet) m_pMkDb4DrvLic->ConnectServer();
		return  bRet;
	}
}

CString CLogiFunc::GetWeekChartTitle(COleDateTime dtDate)
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


CString CLogiFunc::GetMyNumberFormat(long nNumber)
{
	CString strNumber;
	strNumber.Format("%d", nNumber);
	return GetMyNumberFormat(strNumber);
}







CString CLogiFunc::GetMyFileName()
{
	TCHAR szFullPath[MAX_PATH];
	if (GetModuleFileName(AfxGetInstanceHandle(), szFullPath, _MAX_PATH) > 0)
	{
		return szFullPath;
	}

	return "";
}




void CLogiFunc::MyTokenize(CString strInput, CString strDivide, BOOL bEpthyInsert, CStringArray& strArr)
{

	CString resToken;
	int curPos = 0;


	resToken = strInput.Tokenize(",", curPos);
	strArr.Add(resToken);
	while (resToken != "")
	{
		CString strTemp = "";
		strTemp = strInput.Mid(curPos, 1);
		if (strTemp == "," && bEpthyInsert && strInput.Mid(curPos + 1).GetLength() > 0)
		{
			strArr.Add("");
			curPos += 1;
		}
		else
		{
			resToken = strInput.Tokenize(",", curPos);
			if (strTemp == "" && resToken == "")
				break;
			else
				strArr.Add(resToken);
		}
	};


}


char* CLogiFunc::UTF8ToANSI(const char* pszCode)
{
	BSTR    bstrWide;
	char* pszAnsi;
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





CString CLogiFunc::GetSMSTelUse(int nState)
{
	CString strState = "";
	switch (nState)
	{
	case 0:
		strState = "";
		break;
	case 1:
		strState = "ㅇ";
		break;
	case 2:
		strState = "X";
		break;

	}
	return strState;
}

CString CLogiFunc::GetSMSTelCorp(int nState)
{
	CString strState = "";
	switch (nState)
	{
	case 0:
		strState = "";
		break;
	case 1:
		strState = "사업자";
		break;
	case 2:
		strState = "개인";
		break;

	}
	return strState;
}

CString CLogiFunc::GetSMSTelecomState(int nState)
{
	CString strState = "";
	switch (nState)
	{
	case 0:
		strState = "";
		break;
	case 1:
		strState = "법인";
		break;
	case 2:
		strState = "개인";
		break;

	}
	return strState;
}

CString CLogiFunc::GetSMSFileStateType(int nState, int nTelType)
{
	CString strState = "";
	switch (nState)
	{
	case 0:
		strState = "";
		break;
	case 1:
		strState = "미승인";
		break;
	case 2:
		strState = "로지진행";
		break;
	case 3:
		if (nTelType == 3)
			strState = "-";
		else
			strState = "승인";
		break;
	case 4:
		strState = "반려";
		break;
	case 5:
		strState = "";
		break;

	case 6:
		strState = "보류";
		break;
	case 7:
		strState = "에러";
		break;
	case 8:
		strState = "재등록";
		break;
	}
	return strState;
}

long CLogiFunc::GetStringLengthByAscII(CString strText)
{
	char* ch = (LPSTR)((LPCTSTR)strText);

	long i = 0;
	float j = 0;

	while (ch[i] != '\0')
	{
		if (ch[i] < 0)
			j += 0.5;
		else
			j++;

		i++;
	}
	//while(c)
	return (long)j;
}



CString CLogiFunc::GetNoneDashNumber(CString strPhoneNumber)
{
	CString strNumber = strPhoneNumber;
	strNumber.Remove('-');
	return strNumber;
}



CString CLogiFunc::GetWebUploadUrl(CString strUseage, LONG nTNo)
{
	CMkCommand cmd(m_pMkDb, "OTPInfo_sid_select");
	cmd.AddParameter(m_ui.strID);
	cmd.AddParameter(strUseage);
	cmd.AddParameter(nTNo);
	CMkParameter* pOTP = cmd.AddParameter(typeString, typeOutput, 10, "");
	CMkParameter* pExecuteInfo = cmd.AddParameter(typeString, typeOutput, 300, "");
	CMkParameter* pOutReason = cmd.AddParameter(typeString, typeOutput, 300, "");

	if (!cmd.Execute())
		return "";

	CString strUrl;
	pExecuteInfo->GetValue(strUrl);
	return strUrl;
}


BOOL CLogiFunc::IsSoftIce95()
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

	if (hFile != INVALID_HANDLE_VALUE)
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
BOOL CLogiFunc::IsSoftIceNT()
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

	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		return TRUE;
	}
	return FALSE;
}

int AFXAPI CLogiFunc::MsgBox(CString strMsg, CString strCaption, UINT nType)
{
	return ::MessageBox(NULL, (LPCTSTR)strMsg, (LPCTSTR)strCaption, nType | MB_TOPMOST);
}

int AFXAPI CLogiFunc::MsgBox(UINT nIDPrompt, CString strCaption, UINT nType)
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

BOOL CLogiFunc::GetFileVersion(char* filename, VS_FIXEDFILEINFO* pvsf)
{
	DWORD dwHandle;
	DWORD cchver = GetFileVersionInfoSize(filename, &dwHandle);
	if (cchver == 0)
		return FALSE;
	char* pver = new char[cchver];
	BOOL bret = GetFileVersionInfo(filename, dwHandle, cchver, pver);
	if (!bret)
		return FALSE;
	UINT uLen;
	void* pbuf;
	bret = VerQueryValue(pver, "\\", &pbuf, &uLen);
	if (!bret)
		return FALSE;
	memcpy(pvsf, pbuf, sizeof(VS_FIXEDFILEINFO));
	delete[] pver;
	return TRUE;
}

BOOL CLogiFunc::RunProgram(CString strFileName, CString strArg)
{
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi;

	if (!strArg.IsEmpty())
		strFileName += " " + strArg;

	BOOL fSuccess = CreateProcess(NULL, (LPSTR)(LPCTSTR)strFileName, NULL, NULL, 0,
		CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);

	if (fSuccess) {
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}
	return fSuccess;
}

void CLogiFunc::StatusText(UINT nPane, CString strMsg)
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	((CStatusBar*)pFrame->GetStatusBar())->SetPaneText(nPane, strMsg);
	pFrame->SetStatusAccessTime(GetTickCount());
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
BOOL CLogiFunc::GetMacAddress(BOOL bShowMsg)
{
	m_ei.strMac1 = "";
	m_ei.strMac2 = "";

	DWORD sizeReq = 0;
	PMIB_IFTABLE pInfo = NULL;
	// Get size information
	::GetIfTable(NULL, &sizeReq, FALSE);

	// Allocate required memory
	pInfo = (PMIB_IFTABLE) new BYTE[sizeReq];
	memset(pInfo, 0, sizeReq);

	DWORD sizeToUse = sizeReq;

	// Retrieve network interface information
	bool result = (::GetIfTable((PMIB_IFTABLE)pInfo,
		&sizeToUse, FALSE) == NO_ERROR);
	if (!result)
	{
		delete (PMIB_IFTABLE)pInfo;
		pInfo = NULL;
		//	printf(
		//	"Couldn't retrieve network interface information!");
		return false;
	}

	// Print all interface information 
	for (unsigned int index = 0; index <
		((PMIB_IFTABLE)pInfo)->dwNumEntries; index++)
	{
		// Get interface description
		MIB_IFROW& details = ((PMIB_IFTABLE)pInfo)->table[index];

		if (details.dwType != IF_TYPE_ETHERNET_CSMACD &&
			details.dwType != IF_TYPE_IEEE80211)
			continue;

		// Format physical address
		char macStr[30], szDescript[MAX_PATH];
		DWORD j = 0, k = 0;
		for (j = 0; j < details.dwPhysAddrLen; ++j)
		{
			sprintf(&macStr[j * 3], "%02X-", details.bPhysAddr[j]);
		}

		for (k = 0; k < details.dwDescrLen; k++)
		{
			sprintf(&szDescript[k], "%c", details.bDescr[k]);
		}
		if (j > 0)
			macStr[j * 3 - 1] = '\0';
		szDescript[k] = 0;

		if (bShowMsg)
		{
			CString strMsg;
			strMsg.Format("mac=%s, desc=%s\n\n", macStr, szDescript);
			AfxMessageBox(strMsg);
		}

		CString strDesc = szDescript;

		if (strDesc.Find("QoS") >= 0)
		{
			continue;
		}

		strDesc.MakeUpper();
		if (strDesc.Find("WAN") >= 0 ||
			strDesc.Find("BLUETOOTH") >= 0)
		{
			continue;
		}

		g_bana_log->Print("%d)mac:%s, desc:%s, operstatus:%d, speed:%d, dwType:%d\n\n", index, macStr, szDescript, details.dwOperStatus,
			details.dwSpeed, details.dwType);


		if (j > 0)
		{
			// Print out physical address
			if (m_ei.strMac1.IsEmpty())
				m_ei.strMac1 = macStr;
			else if (m_ei.strMac1 != macStr && m_ei.strMac2.IsEmpty())
				m_ei.strMac2 = macStr;
		}
	}

	delete (PMIB_IFTABLE)pInfo;
	return true;
}

BOOL CLogiFunc::IsExceptionDetailDongUse(CPOIUnit* pDong)
{
	if (pDong->IsDongPOI() &&
		(pDong->GetGugun().Compare("종로구") == 0 || pDong->GetGugun().Compare("중구") == 0))
	{
		return TRUE;
	}

	return FALSE;
}

CString CLogiFunc::GetHddId()
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

			if (read_serail && reag_tag) {// && tag == "\\\\.\\PHYSICALDRIVE0") {
				sHDD_Serial.Replace(" ", "");
				m.insert(std::make_pair(tag, sHDD_Serial));
				//return sHDD_Serial;
			}
		}

	} while (0);

	if (m.size() > 0)
		return m.begin()->second;

	return "";
}

CString CLogiFunc::FormatString(const char* format, ...)
{
	TCHAR line[LINE_BUFFER_SIZE];

	va_list ap;
	va_start(ap, format);
	_vsnprintf(line, LINE_BUFFER_SIZE, format, ap);
	va_end(ap);
	return CString(line);
}

void CLogiFunc::AddSecurityLog(long nCompany, long nType, long nStaffNo,
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

void CLogiFunc::AddSecurityLog(long nCompany, long nType, long nStaffNo, long nData)
{
	char buffer[20];
	AddSecurityLog(nCompany, nType, nStaffNo, ltoa(nData, buffer, 10), "", "");
}

void CLogiFunc::AddSecurityLog(long nCompany, long nType, long nData)
{
	char buffer[20];
	AddSecurityLog(nCompany, nType, m_ui.nWNo, ltoa(nData, buffer, 10), "", "");
}

int CLogiFunc::CheckSum(void* buffer, int nLen)
{
	::byte* byBuffer = (::byte*)buffer;
	int nSum = 77;

	for (int i = 0; i < nLen; i++)
		nSum += (::byte)byBuffer[i];

	return nSum;
}

CString CLogiFunc::RemoveZero(long nData)
{
	char buffer[10];
	return RemoveZero(itoa(nData, buffer, 10));
}

CString CLogiFunc::RemoveZero(CString strData)
{
	if (strData == "0") return "";
	else return strData;
}

BOOL CLogiFunc::IsBrokenHangul(CString& strText)
{
	int nCount = 0;
	for (int i = 0; i < strText.GetLength(); i++) {
		if (_istlead(strText.GetAt(i))) {
			nCount++;
		}
	}

	if (nCount % 2 == 0)
		return FALSE;
	else
		return TRUE;
}

CBranchInfo* CLogiFunc::GetCurBranchInfo(BOOL bAllowVirtualCompany)
{
	if (m_pbiCur)
	{
		return m_pbiCur;
	}

	return m_ba.GetAt(0);
}

CString& CLogiFunc::StringMakeUpper(CString& str)
{
	char* p = (char*)str.GetBuffer();
	for (int i = 0; i < str.GetLength(); i++)
	{
		if (p[i] >= 'a' && p[i] <= 'z')
		{
			p[i] = p[i] - 32;
		}
	}
	return str;
}

CString CLogiFunc::GetDepositTypeStringFromType(int nType)
{
	switch (nType)
	{
	case 20:
		return "월비";
	case 30:
		return "주비";
	case 40:
		return "일비";
	case 50:
		return "프로제";
	default:
		return "UNKNOWN";
	}
}

CString CLogiFunc::GetDepositAllocateTypeStringFromType(int nType)
{
	switch (nType)
	{
	case 0:
		return "선입금";
	case 10:
		return "후입금";
	default:
		return "UNKNOWN";
	}
}

CString CLogiFunc::GetFixedDepositStateString(int nState)
{
	switch (nState)
	{
	case 10:
		return "(+)잔액충전";
	case 11:
		return "(+)잔액충전(배차취소)";
	case 12:
		return "(+)잔액충전(입금액변경)";
	case 13:
		return "(+)잔액충전(신용정산)";
	case 14:
		return "(+)잔액충전(스케줄작업)";
	case 15:
		return "(+)잔액충전(과금수령액)";
	case 16:
		return "(+)잔액충전(온라인입금)";
	case 17:
		return "(+)잔액충전(현금)";
	case 18:
		return "(+)잔액충전(가상계좌)";
	case 19:
		return "지입금 납입";
	case 20:
		return "(+)잔액충전(지입금)";
	case 21:
		return "(+)잔액충전(누적신용금)";
	case 22:
		return "(+)잔액충전(통장입금)";
	case 23:
		return "(+)잔액충전(화물정산)";
	case 24:
		return "(+)잔액충전(화물정산,공유콜)";
	case 25:
		return "(+)잔액충전(계좌출금)";
	case 26:
		return "(+)잔액충전(로지부담금)";
	case 30:
		return "(+)잔액충전(반환금)";
	case 31:
		return "(+)잔액충전(업체부담금)";
	case 32:
		return "(+)잔액충전(타사이체)";
	case 33:
		return "(+)잔액충전(이벤트오더)";


	case 40:
		return "(-)잔액차감";
	case 41:
		return "(-)잔액차감(배차)";
	case 42:
		return "(-)잔액차감(취소과금)";
	case 43:
		return "(-)잔액차감(입금액변경)";
	case 44:
		return "(-)잔액차감(가불)";
	case 45:
		return "(-)잔액차감(과태료)";
	case 46:
		return "(-)잔액차감(스케줄작업)";
	case 47:
		return "(-)잔액차감(충전금환급)";
	case 48:
		return "(-)잔액차감(출근비)";
	case 49:
		return "(-)잔액차감(충전취소)";
	case 50:
		return "(-)잔액차감(지입금)";
	case 51:
		return "(-)잔액차감(신용정산)";
	case 52:
		return "(-)잔액차감(통장출금)";
	case 53:
		return "(-)잔액차감(화물정산)";
	case 54:
		return "(-)잔액차감(화물정산,공유콜)";
	case 55:
		return "(-)잔액차감(타사이체)";
	case 56:
		return "(-)잔액차감(지입금차감)";
	case 57:
		return "(-)잔액차감(계좌출금)";
	case 59:
		return "(-)잔액차감(일비차감)";

	case 70:
		return "(-)잔액차감(반환금)";
	case 71:
		return "(-)잔액차감(적재물보험)";

	case 60:
		return "정산방식변경";
	case 61:
		return "잔액초기화";
	case 62:
		return "(-)잔액차감(로지부담금)";
	case 63:
		return "(-)잔액차감(업체부담금)";

	case 100:
		return "(+)잔액충전(오더완료)";
	case 101:
		return "(+)잔액충전(오더취소)";
	case 200:
		return "(-)잔액차감(오더완료)";
	case 201:
		return "(-)잔액차감(오더취소)";

	default:
		return "N/A";
	}
}

int CLogiFunc::GetNoneCommaNumber(CString strNumber)
{
	strNumber.Remove(',');
	return atol(strNumber);
}

int CLogiFunc::GetChargeDongTypeInfo(long nDong)
{
	CPOIUnit* pData = m_poiNew.GetDongPOI(nDong);

	//pData->m_nClass
	//POI_DATA *pData =
	if (pData <= NULL)
		return -10;

	if (pData->m_nClass == 10 && pData->m_bDongData)
		return 3;
	else if (pData->m_nClass == 10 && pData->m_bDongData == FALSE)
		return 2;
	else if (pData->m_nClass == 5)
		return 2;
	else if (pData->m_nClass == 0)
		return 1;
	else if (pData->m_nClass == 20)
		return -1;
	else
		return 0;
}

int CLogiFunc::GetChargeType(int nStartType, int nDestType)
{

	int nType = 1000;

	if (nStartType == 3 && nDestType == 3)
		nType = 8;
	else if (nStartType == 3 && nDestType == 2)
		nType = 7;
	else if (nStartType == 3 && nDestType == 1)
		nType = 6;
	else if (nStartType == 2 && nDestType == 3)
		nType = 5;
	else if (nStartType == 1 && nDestType == 3)
		nType = 4;
	else if (nStartType == 2 && nDestType == 2)
		nType = 3;
	else if (nStartType == 2 && nDestType == 1)
		nType = 2;
	else if (nStartType == 1 && nDestType == 2)
		nType = 1;
	else if (nStartType == 1 && nDestType == 1)
		nType = 0;

	else if (nStartType == 3 && nDestType == -1)
		nType = -1;
	else if (nStartType == 2 && nDestType == -1)
		nType = -2;
	else if (nStartType == 1 && nDestType == -1)
		nType = -3;
	else if (nStartType == -1 && nDestType == 3)
		nType = -4;
	else if (nStartType == -1 && nDestType == 2)
		nType = -5;
	else if (nStartType == -1 && nDestType == 1)
		nType = -6;
	else if (nStartType == -1 && nDestType == -1)
		nType = -7;

	return nType;
}

ST_SMS_INFO CLogiFunc::GetSMSBalance(long nCompany)
{
	long nBarance = 0;
	int	 nSMSType = 0;
	ST_SMS_INFO smsi;

	CMkCommand pCmd(m_pMkDb, "select_sms_get_barance");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
	CMkParameter* parBarance = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), nBarance);
	CMkParameter* parBaranceType = pCmd.AddParameter(typeInt, typeOutput, sizeof(int), nSMSType);
	pCmd.Execute();

	parBarance->GetValue(nBarance);
	parBaranceType->GetValue(nSMSType);
	smsi.nSMSBarance = nBarance;
	smsi.nSMSType = nSMSType;

	return smsi;
}

CBranchInfo* CLogiFunc::GetBranchInfo(long nCompany)
{
	//by mksong (2010-12-10 오전 11:38)
	//m_ccm으로 변경해야함

	CBranchInfo* pBi = NULL;
	if (nCompany < 0)
		return pBi;


	if (m_ba.GetCount() > 1)
	{
		for (int i = 0; i < m_ba.GetCount(); i++)
		{
			pBi = m_ba.GetAt(i);

			if (pBi->bIntegrated)
				continue;

			if (pBi->nCompanyCode == nCompany)
			{
				return pBi;
			}
		}
	}
	else
		pBi = m_ba.GetAt(0);

	return pBi;
}

long CLogiFunc::GetNowBranchCode()
{
	BOOL bIntegrated = FALSE;
	CBranchInfo* pBi = NULL;

	if (m_ba.GetCount() > 0)
	{
		CBranchInfo* pBi = GetCurBranchInfo();
		return pBi->nCompanyCode;
	}
	else

		pBi = m_ba.GetAt(0);

	return pBi->nCompanyCode;
}

BOOL CLogiFunc::ChangeRiderWorkState(long nCompany, long nRNo, BOOL bIntegrated, CString strWorkTitle, CString strWorkMemo, BOOL bWorkStop)
{
	CMkCommand pCmd(m_pMkDb, "update_rider_workstate5_1");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), bIntegrated);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), bWorkStop);
	pCmd.AddParameter(typeString, typeInput, strWorkTitle.GetLength(), strWorkTitle);
	pCmd.AddParameter(typeString, typeInput, strWorkMemo.GetLength(), strWorkMemo);
	pCmd.AddParameter(typeString, typeInput, m_ui.strID.GetLength(), m_ui.strID);
	return pCmd.Execute();
}

BOOL CLogiFunc::IsIntegrated(long nCompany)
{
	CBranchInfo* pBi = NULL;
	if (m_ba.GetCount() > 0)
		pBi = (CBranchInfo*)m_ba.GetAt(0);
	else
		return FALSE;

	if (pBi && nCompany == -1)
	{
		if (pBi->bIntegrated && m_ba.GetCount() > 1)
			return TRUE;
		else
			return FALSE;
	}
	else if (nCompany > 0 && m_ba.GetCount() > 1)
	{
		if (pBi->nCompanyCode == nCompany && pBi->bIntegrated)
			return TRUE;
		else
			return FALSE;
	}
	else
		return FALSE;
}

BOOL CLogiFunc::IsBranch(long nCompany)
{
	CBranchInfo* pBi = NULL;
	if (m_ba.GetCount() >= 0)
	{
		for (int i = 0; i < m_ba.GetCount(); i++)
		{
			pBi = (CBranchInfo*)m_ba.GetAt(i);
			if (pBi->nCompanyCode == nCompany)
				return TRUE;
		}
		return FALSE;
	}
	else
		return FALSE;
}

void CLogiFunc::SetHanEngMode(HWND hWnd, BOOL bHan)
{
	HIMC hIMC = ImmGetContext(hWnd);
	DWORD dwConv, dwSent;
	DWORD dwTemp;

	ImmGetConversionStatus(hIMC, &dwConv, &dwSent);

	dwTemp = dwConv & ~IME_CMODE_LANGUAGE;

	if (bHan)
		dwTemp |= IME_CMODE_NATIVE;
	else
		dwTemp |= IME_CMODE_ALPHANUMERIC;

	dwConv = dwTemp;

	ImmSetConversionStatus(hIMC, dwConv, dwSent);

	ImmReleaseContext(hWnd, hIMC);
}

long CLogiFunc::GetCommaCount(CString sCommaString)
{
	long nCount = 0, index = 0;

	while (1)
	{
		index = sCommaString.Find(";", index + 1);

		if (index == -1) break;

		nCount++;
	}

	return nCount;
}

long CLogiFunc::GetDepositTypeToComboSel(long nDepositType)
{
	if (nDepositType == 20)
		return 0;
	if (nDepositType == 30)
		return 1;
	if (nDepositType == 40)
		return 2;
	if (nDepositType == 50)
		return 3;

	return -1;
}

long CLogiFunc::GetDepositAllocateTypeToComboSel(long nDepositAllocateType)
{
	if (nDepositAllocateType == 0)
		return 0;
	if (nDepositAllocateType == 10)
		return 1;
	if (nDepositAllocateType == 20)
		return 2;

	return -1;
}

long CLogiFunc::GetDepositTypeFromComboSel(long nSel)
{
	if (nSel == 0)
		return 20;
	if (nSel == 1)
		return 30;
	if (nSel == 2)
		return 40;
	if (nSel == 3)
		return 50;

	return -1;
}

long CLogiFunc::GetDepositAllocateTypeFromComboSel(long nSel)
{
	if (nSel == 0)
		return 0;
	if (nSel == 1)
		return 10;

	return -1;
}

CString CLogiFunc::GetHostName()
{
	char szHostName[MAX_PATH];
	::gethostname(szHostName, MAX_PATH);
	return CString(szHostName);
}

void CLogiFunc::CreateDir(char* Path)
{
	char DirName[256];  //생성할 디렉초리 이름 
	char* p = Path;     //인자로 받은 디렉토리 
	char* q = DirName;

	while (*p)
	{
		if (('\\' == *p) || ('/' == *p))   //루트디렉토리 혹은 Sub디렉토리 
		{
			if (':' != *(p - 1))
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

BOOL CLogiFunc::IsNumeric(LPCTSTR pszText)
{
	ASSERT_VALID_STRING(pszText);

	for (int i = 0; i < lstrlen(pszText); i++)
		if (!_istdigit(pszText[i]))
			return false;

	return true;
}

BOOL CLogiFunc::SendSmsNew(long nCompany, long nTranID, CString sTranPhone, CString sTranCallback,
	CString sTranMsg, CString sSmsLogEtc, CString sEtc1, CString sEtc2, BOOL bMsgBox)
{
	sTranPhone.Replace("-", "");
	sTranCallback.Replace("-", "");

	if (sTranCallback.IsEmpty())
	{
		MessageBox(NULL, "회신번호를 입력하세요", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	if (!CheckTel(sTranCallback))
		return FALSE;

	//insert_mms_data_new mms로 프로시져 있음

	CMkCommand pCmd(m_pMkDb, "insert_sms_data_new");
	CMkParameter* pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long), 0);
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

	if (!pCmd.Execute()) return FALSE;

	long nRet = 0; pPar->GetValue(nRet);

	if (nRet == 0)
	{
		MessageBox(NULL, "잔액이 부족하여 전송 하실 수 없습니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	if (bMsgBox)
	{
		MessageBox(NULL, "성공적으로 전송 되었습니다", "확인", MB_ICONINFORMATION);
		return TRUE;
	}

	return TRUE;
}

BOOL CLogiFunc::SendSmsNewRev(long nCompany, long nTranID, CString sTranPhone, CString sTranCallback,
	CString sTranMsg, CString sSmsLogEtc, CString sEtc1, CString sEtc2, COleDateTime dtRev, BOOL bMsgBox)
{
	sTranPhone.Replace("-", "");
	sTranCallback.Replace("-", "");

	if (sTranCallback.IsEmpty())
	{
		MessageBox(NULL, "회신번호를 입력하세요", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	if (!CheckTel(sTranCallback))
		return FALSE;

	CMkCommand pCmd(m_pMkDb, "insert_sms_data_new_rev");
	CMkParameter* pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long), 0);
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

	if (!pCmd.Execute()) return FALSE;

	long nRet = 0; pPar->GetValue(nRet);

	if (nRet == 0)
	{
		MessageBox(NULL, "잔액이 부족하여 전송 하실 수 없습니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	if (bMsgBox)
	{
		MessageBox(NULL, "성공적으로 전송 되었습니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	return TRUE;
}

BOOL CLogiFunc::SendPDASimple(long nCompany, long nRiderCompany, long nRNo, CString sMsg)
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

BOOL CLogiFunc::NotifyPenalty(int nPenalty)
{
	if (m_ci.m_nPenaltyLevel >= nPenalty) {
		CString strTitle;
		strTitle.Format("★%s부터, 페널티 레벨%d 적용중★",
			m_ci.m_dtPenaltyStart.Format("%m월%d일 "),
			m_ci.m_nPenaltyLevel);
		MessageBox(NULL, "회원사의 요금이 연체되어서, 페널티가 적용되고 있습니다.\n"\
			"현재 이 기능을 이용할 수 없습니다. "\
			"요금이 모두 완납되기전에 페널티 해지가 불가능하며,\n"\
			"부분납입인 경우에, 페널티 레벨 1단계 다운만 가능합니다.\n"\
			"레벨에 따른 페널티 내용은 아래와 같습니다.\n\n"\
			"★페널티 1: 공지사항, 배차판, 권한설정 등등 기능제한됨\n"\
			"★페널티 2: 고객탭 접근 제한됨                           <-- 3일후\n"\
			"★페널티 3: 직원탭 접근 제한됨                           <-- 6일후\n"\
			"★페널티 4: 정산/입금탭 접근 제한됨                   <-- 9일후\n"\
			"★페널티 5: 서비스중지됨                                   <-- 12일후\n\n"\
			"페널티 레벨은 해당기간이 경과 후에, 서버에서 자동 업되므로,\n"\
			"문제를 조기에 해결하시는게 유리하십니다.\n"\
			"몇일까지 입금완료하겠다고 약속하시더라도, 그때까지 페널티는 계속\n"\
			"적용되는게 원칙인것을 인지하시기 바랍니다.\n"\
			"부득이하게 불편을 드려서 죄송합니다.\n"\
			"감사합니다.",
			strTitle,
			MB_ICONINFORMATION);

		CBillDlg dlg;
		COleDateTime dtDate;
		COleDateTime dtCurrent = COleDateTime::GetCurrentTime();
		if (dtCurrent.GetMonth() == 1)
			dtDate.SetDate(dtCurrent.GetYear() - 1, 11, 1);
		else if (dtCurrent.GetMonth() == 2)
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


BOOL CLogiFunc::SendUpdateFile(CMkDatabase& db, CString strLocalPath, CString strServerPath)
{
	HANDLE hFile, hFileMap;
	unsigned char* pBasePointer;
	DWORD dwSize;
	BOOL bRet = FALSE;

	hFile = CreateFile((LPSTR)(LPCTSTR)strLocalPath, GENERIC_READ,
		FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE != hFile)
	{
		hFileMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
		dwSize = GetFileSize(hFile, 0);
		pBasePointer = (unsigned char*)MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, dwSize);

		if (db.UploadFileWithDlg(strServerPath, (char*)pBasePointer, dwSize))
		{
			bRet = TRUE;
		}

		UnmapViewOfFile((LPVOID)pBasePointer);
		CloseHandle(hFileMap);
	}

	CloseHandle(hFile);
	return bRet;
}

CString CLogiFunc::EnCodeStr(CString ToCode)
{
	CString RetStr, AddStr;
	int i, max;
	unsigned short asc;
	unsigned char c;
	max = (unsigned int)ToCode.GetLength();
	for (i = 0; i < max; i++)
	{
		c = ToCode[i];
		asc = c;//(unsigned int)c;
		if (asc > 47 && asc < 58)
		{
			RetStr += c;//Interim[(int)i];
		}
		else if (asc > 64 && asc < 91)
		{
			RetStr += c;//Interim[(int)i];
		}
		else if (asc > 96 && asc < 123)
		{
			RetStr += c;//Interim[(int)i];
		}
		else if (asc == 32)
		{
			RetStr += "+";
		}
		else
		{
			AddStr.Format("%%%2x", asc);
			int iv = (int)AddStr.GetAt(1);
			if ((int)AddStr.GetAt(1) == 32)
			{
				AddStr.SetAt(1, '0');
			}
			RetStr += AddStr;
		}
	}
	return RetStr;
}

typedef BOOL(WINAPI* SetLayer)(HWND hWnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
#define LWA_COLORKEY            0x01
#define LWA_ALPHA               0x02

void CLogiFunc::SetCrystal(CWnd* pWnd, int index)
{
	HMODULE hUser32 = GetModuleHandle(_T("USER32.DLL"));

	SetLayer pSetLayer = (SetLayer)GetProcAddress(hUser32, "SetLayeredWindowAttributes");

	if (pSetLayer == NULL)
	{
		//MessageBox("win2000 이상");
		return;
	}

	char chAlpha = index; //투명도 설정 0 ~ 255
	SetWindowLong(pWnd->m_hWnd, GWL_EXSTYLE, GetWindowLong(pWnd->m_hWnd, GWL_EXSTYLE) | 0x80000);
	pSetLayer(pWnd->m_hWnd, 0, chAlpha, LWA_ALPHA);
}

void CLogiFunc::SetEditText(CEdit* pEdit, CString strText, BOOL bFront)
{
	CString strEdit;
	pEdit->GetWindowText(strEdit);

	if (bFront)
		pEdit->SetWindowText(strText + strEdit);
	else
		pEdit->SetWindowText(strEdit + strText);
}

void CLogiFunc::FillVaildRiderData()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_able_allocate_rider_1");

	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(TRUE);

	if (!pRs.Execute(&pCmd)) return;

	for (int i = 0; i < pRs.GetRecordCount(); i++)
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

long CLogiFunc::GetCarTypeForCharge(long nCarType)
{
	long nChargeCarType = 0;

	switch (nCarType)
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

BOOL CLogiFunc::AddCustomerTel(long nCompany, long nCNo, long nTelID, CString strPhone)
{
	if (nCNo <= 0)
	{
		AfxMessageBox("고객등록 후 전화번호를 추가하세요", MB_OK);
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

void CLogiFunc::GetItemCommaToArray(CString strItem, CStringArray& arryItem)
{
	long nStartPos = 0;
	long nDestPos = 0;
	long nCount = 0;

	while (1)
	{
		if (nCount > 100)
			break;

		nDestPos = strItem.Find(";", nStartPos);

		if (nDestPos == -1)
			break;

		CString sItem = strItem.Mid(nStartPos, nDestPos - nStartPos);

		if (sItem.IsEmpty() == FALSE)
			arryItem.Add(sItem);

		nStartPos = nDestPos + 1;

		nCount++;
	}
}

CString CLogiFunc::GetRemoveDDDNumber(CString strPhone, long nCompany)
{
	//strDDD에 값 넣어야함
	CString strDDD = nCompany == 0 ? m_ci.m_strDDD : GetBranchInfo(nCompany)->strDDD;

	strPhone.Replace("-", "");

	if (strPhone.Left(strDDD.GetLength()) == strDDD)
		strPhone = strPhone.Right(strPhone.GetLength() - strDDD.GetLength());

	return strPhone;
}

void CLogiFunc::GetOnlyDistance(long nStartPosX, long nStartPosY, long nDestPosX, long nDestPosY, CWnd* pReturnMsgWnd)
{
	CPoint s, d, v;
	CLogiMapCns* pCNS = LU->GetLogiMapCns();
	pCNS->ClearPos();
	pCNS->AddPos(nStartPosX, nStartPosY);
	pCNS->AddPos(nDestPosX, nDestPosY);
	//pCNS->GetRouteDistanceThread1(pReturnMsgWnd, FALSE, 0,0, 0);


	pCNS->GetRouteDistance(pReturnMsgWnd, FALSE, 0, 0, 0);
}

CString CLogiFunc::GetCancelReason(long nReason)
{
	if (nReason == 0) return "전화불통";
	else if (nReason == 1) return "시간지연";
	else if (nReason == 2) return "배달지이상";
	else if (nReason == 3) return "물건크기불량";
	else if (nReason == 4) return "취급불가불건";
	else if (nReason == 5) return "고객없음";
	else if (nReason == 6) return "일부취소";
	else if (nReason == 7) return "기사부족";
	else if (nReason == 8) return "연습오더";
	else if (nReason == 9) return "본인취소";
	else if (nReason == 10) return "배차실수";

	return "N/A";
}

BOOL CLogiFunc::IsCash(long nPayType)
{
	if (nPayType == PAY_PRE ||
		nPayType == PAY_AFTER ||
		nPayType == PAY_DIRECT)
		return TRUE;
	else
		return FALSE;
}

CString CLogiFunc::GetGrade(long nGrade, BOOL bShowDefault)
{
	if (nGrade == 0)
		return bShowDefault ? "보통" : "";

	if (nGrade == 1)
		return "우수";

	if (nGrade == 2)
		return "최우수";

	if (nGrade == 3)
		return "불량";

	return bShowDefault ? "보통" : "";
}

int CLogiFunc::GetGradeColor(long nGrade)
{
	if (nGrade == 0)
		return RGB(107, 205, 90);
	if (nGrade == 1)
		return RGB(0, 255, 255);
	if (nGrade == 2)
		return RGB(100, 100, 255);
	if (nGrade == 3)
		return RGB(255, 100, 100);
	return RGB(107, 205, 90);
}

CString CLogiFunc::GetDiscountType(long nDiscount)
{
	if (nDiscount == 0)
		return "퍼센트(%)";
	if (nDiscount == 1)
		return "금액(원)";
	if (nDiscount == 2)
		return "A타입";
	if (nDiscount == 3)
		return "B타입";
	if (nDiscount == 4)
		return "C타입";
	if (nDiscount == 5)
		return "D타입";
	return "퍼센트(%)";
}

BOOL CLogiFunc::IsThisCompany(CString strCompanyName, long nCompany, long nShareCode1)
{
	if (strCompanyName == "퀵오케이_적요")
		return nCompany == 2904 || nCompany == 2907 || nCompany == 2920 || nCompany == 2931;
	else if (strCompanyName == "퀵오케이_2904")
		return nCompany == 2904;
	else if (strCompanyName == "퀵오케이_2920")
		return nCompany == 2920;
	else if (strCompanyName == "퀵오케이_2931")
		return nCompany == 2931;
	else if (strCompanyName == "퀵오케이_2907")
		return nCompany == 2907;
	else if (strCompanyName == "이레퀵")
		return m_ci.m_nShareCode1 == 15775;
	else if (strCompanyName == "세븐특송")
		return m_ci.m_nShareCode1 == 16300;
	else if (strCompanyName == "퀵콜")
		return m_ci.m_nShareCode1 == 7700;
	else if (strCompanyName == "꽃배달일번지")
		return m_ci.m_nShareCode1 == 28361;
	else if (strCompanyName == "코리아바이크")
		return m_ci.m_nShareCode1 == 7010;
	else if (strCompanyName == "엔콜")
		return m_ci.m_nShareCode1 == 7100;
	else if (strCompanyName == "대구연합")
		return m_ci.m_nShareCode5 == 7640;
	else if (strCompanyName == "예스콜")
		return m_ci.m_nShareCode1 == 7330;
	else if (strCompanyName == "나우온")
		return m_ci.m_nShareCode1 == 14476;
	else if (strCompanyName == "빨간모자퀵")
		return m_ci.m_nShareCode1 == 5290;
	else if (strCompanyName == "주식회사대구조합")
		return m_ci.m_nShareCode1 == 8380;
	else if (strCompanyName == "하나로퀵")
		return m_ci.m_nShareCode1 == 15219;
	else if (strCompanyName == "퀵짱")
		return m_ci.m_nShareCode1 == 14420 || nCompany == 14276;
	else if (strCompanyName == "한반도로지넷")
		return m_ci.m_nShareCode1 == 15475;
	else if (strCompanyName == "월드코리아퀵")
		return m_ci.m_nShareCode1 == 12080;
	else if (strCompanyName == "대한퀵물류")
		return m_ci.m_nShareCode1 == 28490;
	else if (strCompanyName == "광주연합")
		return m_ci.m_nShareCode3 == 12079;
	else if (strCompanyName == "대전_나이스")
		return m_ci.m_nShareCode1 == 6050;
	else if (strCompanyName == "올바로")
		return m_ci.m_nShareCode1 == 12450;
	else if (strCompanyName == "로지")
		return m_ci.m_nCompanyCode <= 100;
	else if (strCompanyName == "사천퀵")
		return nCompany == 7476;
	else if (strCompanyName == "퀵오더관제")
		return m_ci.m_nCompanyCode == 2010;
	else if (strCompanyName == "전주퀵서비스")
		return m_ci.m_nCompanyCode == 16135;
	else
	{
		//MessageBox(GetDesktopWindow(), CString("알수없는 회사구분 코드 ") + strCompanyName,
		//	"확인",
		//	MB_ICONINFORMATION);
	}

	return FALSE;
}

CString CLogiFunc::GetDateTimeToString(COleDateTime dtDate, int nType, BOOL bShowDay)
{
	if (dtDate.m_status == 2)
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

	if (bShowDay)
	{
		const char* dayofweek[] = { "일", "월", "화", "수", "목", "금", "토" };
		strDate.Format("%s(%s)", strDate, dayofweek[dtDate.GetDayOfWeek() - 1]);
	}

	return strDate;
}

CString CLogiFunc::GetMyDateString(COleDateTime dt, BOOL bDisplayCentury, BOOL* pbSpecialDate)
{
	static COleDateTime dtTomorrow;
	static COleDateTime dtYesterday;
	static BOOL bInit = FALSE;

	if (!bInit)
	{
		dtTomorrow = m_ei.dtTodayBound + COleDateTimeSpan(1, 0, 0, 0);
		dtYesterday = m_ei.dtTodayBound - COleDateTimeSpan(1, 0, 0, 0);
		bInit = TRUE;
	}

	if (dt < dtTomorrow && dt > m_ei.dtTodayBound)
	{
		if (pbSpecialDate)
			*pbSpecialDate = TRUE;
		return "오늘";
	}
	else if (dt > dtYesterday && dt < dtTomorrow)
	{
		if (pbSpecialDate)
			*pbSpecialDate = TRUE;
		return "어제";
	}
	else
	{
		if (pbSpecialDate)
			*pbSpecialDate = FALSE;
		return bDisplayCentury ? dt.Format("%Y-%m-%d") : dt.Format("%y-%m-%d");
	}
}

CString CLogiFunc::GetValueByArg(CString& strDataSet, CString strArg)
{
	strArg = _T("<") + strArg + _T("=");
	strArg.MakeUpper();

	int nFind1 = strDataSet.Find(strArg);
	if (nFind1 < 0) return _T("");

	int nFind2 = strDataSet.Find(_T(">"), nFind1);
	if (nFind2 < 0) return _T("");

	CString sRetVal = strDataSet.Mid(nFind1 + strArg.GetLength(), nFind2 - (nFind1 + strArg.GetLength()));
	return sRetVal;
}

BOOL CLogiFunc::IsKoreaWord(CString strWord)
{
	CStringW strDataW(strWord);
	CStringW strCharW(strDataW.Right(1));

	//if( sCharW >= (CStringW("ㄱ") ) && sCharW <= CStringW("ㅎ") ) return FALSE;
	if (strCharW >= (CStringW("ㄱ")) && strCharW <= CStringW("힇"))
	{
		if (strCharW >= (CStringW("가")) && strCharW <= CStringW("힇"))
			return TRUE;
		else
			return FALSE;
	}

	return TRUE;
}

CString CLogiFunc::GetTwoPhone(CString strPhone1, CString strPhone2)
{
	if (strPhone1.IsEmpty() && strPhone1.IsEmpty())
		return "";

	if (strPhone1.IsEmpty())
		return GetDashPhoneNumber(strPhone2);

	if (strPhone2.IsEmpty())
		return GetDashPhoneNumber(strPhone1);

	return GetDashPhoneNumber(strPhone1) + "/" + GetDashPhoneNumber(strPhone2);
}

CString CLogiFunc::GetTwoPhoneAsterisk(CString strPhone1, CString strPhone2)
{
	if (strPhone1.IsEmpty() && strPhone1.IsEmpty())
		return "";

	if (strPhone1.IsEmpty())
		return GetAsteriskPhoneNumber(strPhone2);

	if (strPhone2.IsEmpty())
		return GetAsteriskPhoneNumber(strPhone1);

	return GetAsteriskPhoneNumber(strPhone1) + "/" + GetAsteriskPhoneNumber(strPhone2);
}

void CLogiFunc::MakeModaless()
{
	CFakeDlg dlg;
	dlg.DoModal();
}

BOOL CLogiFunc::LengthCheck(HWND hwnd, long nApplyID, long nLengthStaticID, int nLength, CString strControlName)
{
	CString strApply = "", strTemp = "";

	int nApplyControlLength = 0;
	CWnd* pWnd = CWnd::FromHandle(GetDlgItem(hwnd, nApplyID));
	pWnd->GetWindowText(strApply);

	nApplyControlLength = GetStringLengthByAscII(strApply);

	if (nApplyControlLength > nLength)
	{
		strTemp.Format("%s  의 글자수가 정해진 것보다 큽니다", strControlName);
		MessageBox(hwnd, strTemp, "확인", MB_ICONINFORMATION);
		strApply = strApply.Mid(0, strApply.GetLength() - 2);
		pWnd->SetFocus();
		pWnd->SetWindowText(strApply);
		((CEdit*)pWnd)->SetSel(strApply.GetLength(), strApply.GetLength());

		return FALSE;
	}
	else
	{
		strApply.Format("%ld/%ld", nApplyControlLength, nLength);
		strApply = strControlName + " " + strApply;

		CWnd* pWnd1 = CWnd::FromHandle(GetDlgItem(hwnd, nLengthStaticID));
		pWnd1->ShowWindow(SW_HIDE);
		pWnd1->SetWindowText(strApply);
		pWnd1->ShowWindow(SW_SHOW);
	}

	return TRUE;
}

BOOL CLogiFunc::ChangeFixedDepositState(long nID, long nState)
{
	CMkCommand pCmd(m_pMkDb, "update_fixed_deposit_state");

	pCmd.AddParameter(nID);
	pCmd.AddParameter(nState);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);

	return pCmd.Execute();
}

COleDateTime CLogiFunc::GetCompareDate(BOOL bWeeklyDeposit, COleDateTime dtMaindDate, long nRiderIncomeDay, BOOL bSameRiderIncomeDay)
{
	COleDateTime dtTemp = dtMaindDate;

	if (bWeeklyDeposit) //주납
	{
		if (bSameRiderIncomeDay == TRUE) // 다음주
		{
			COleDateTimeSpan span(7, 0, 0, 0);
			dtTemp = dtMaindDate + span;
		}

		while (1) // 일요일찾기
		{
			if (dtTemp.GetDayOfWeek() == 1)
				break;

			COleDateTimeSpan span(1, 0, 0, 0);
			dtTemp = dtTemp - span;

		}

		nRiderIncomeDay++; //주는 1더해줘야 요일이 맞음

		while (1)
		{
			if (dtTemp.GetDayOfWeek() == nRiderIncomeDay)
				break;

			COleDateTimeSpan span(1, 0, 0, 0);
			dtTemp = dtTemp + span;
		}
	}
	else //월납
	{
		if (nRiderIncomeDay == 0)
			return dtTemp;

		if (bSameRiderIncomeDay == FALSE) // 같은달
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

long CLogiFunc::GetAbilityDay(long nDay, long nYear, long nMonth)
{
	long nNextMonth = nMonth == 12 ? 1 : nMonth + 1;
	long nNextYear = nMonth == 12 ? nYear + 1 : nYear;

	COleDateTime dtDate(nNextYear, nNextMonth, 1, 0, 0, 0);
	COleDateTimeSpan span(1, 0, 0, 0);
	dtDate = dtDate - span;

	long nLastDay = dtDate.GetDay();

	if (nDay <= nLastDay)
		return nDay;
	else
		return nLastDay;
}

void CLogiFunc::InitGroupReportStruct(GROUP_REPORT& stSum)
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

CString CLogiFunc::GetGroupReportText(GROUP_REPORT st, long nCol, long nSel, BOOL bSumrecord)
{
	CString strText;

	switch (nCol)
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
		if (bSumrecord)
			strText = "";
		else
		{
			if (st.stData[nSel].dtReportStart.m_status != 2)
				strText = st.stData[nSel].dtReportStart.Format("%m-%d") + " ~ " + st.stData[nSel].dtReportEnd.Format("%m-%d");
			else
				strText = "";
		}
		break;
	case 4:
		if (bSumrecord)
			strText = GetMyNumberFormat(st.stData[nSel].nSumCount);
		else
			strText = GetMyNumberFormat(st.stData[nSel].nCashCount + st.stData[nSel].nCreditCount + st.stData[nSel].nOnlineCount);
		break;
	case 5:
		strText = GetMyNumberFormat(st.stData[nSel].nCashCharge);
		break;
	case 6:
		strText = GetMyNumberFormat(st.stData[nSel].nCreditCharge);
		break;
	case 7:
		strText = GetMyNumberFormat(st.stData[nSel].nOnlineCharge);
		break;
	case 8:
		strText = GetMyNumberFormat(st.stData[nSel].nTransCharge);
		break;
	case 9:
		strText = GetMyNumberFormat(st.stData[nSel].nTax);
		break;
	case 10:
		if (bSumrecord)
			strText = GetMyNumberFormat(st.stData[nSel].nSumTotal);
		strText = GetMyNumberFormat(st.stData[nSel].nCashCharge + st.stData[nSel].nCreditCharge + st.stData[nSel].nOnlineCharge);
		break;
	case 11:
		if (bSumrecord)
			strText = "";
		else
		{
			if (st.stData[nSel].nReportState == 0)
				strText = "정산완료";
			else if (st.stData[nSel].nReportState == 10)
				strText = "부분입금";
			else if (st.stData[nSel].nReportState == 20)
				strText = "입금완료";
		}
		break;
	case 12:
		strText = GetMyNumberFormat(st.stData[nSel].nBillCollection);
		break;
	case 13:
		if (bSumrecord)
			strText = "";
		else
		{
			if (st.stData[nSel].dtBillCollection.m_status != 2)
				strText = st.stData[nSel].dtBillCollection.Format("%m-%d");
			else
				strText = "";
		}
		break;
	case 14:
		strText = GetMyNumberFormat(st.stData[nSel].nUnBillCollection);
		break;
	case 15:
		strText = GetMyNumberFormat(st.nBalance);
		break;
	case 16:
		strText = GetMyNumberFormat(st.nInComeSum);
		break;
	case 17:
		strText = st.stData[nSel].bPressBill == TRUE ? "○" : "";
		break;
	case 18:
		strText = st.stData[nSel].strEtc;
		break;
	}

	return strText;
}

CString CLogiFunc::GetGroupReportText1(GROUP_REPORT st, long nCol, long nSel, BOOL bSumrecord)
{
	CString strText;

	switch (nCol)
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
		if (bSumrecord)
			strText = "";
		else
		{
			if (st.stData[nSel].dtReportStart.m_status != 2)
				strText = st.stData[nSel].dtReportStart.Format("%m-%d") + " ~ " + st.stData[nSel].dtReportEnd.Format("%m-%d");
			else
				strText = "";
		}
		break;
	case 4:
		strText = GetMyNumberFormat(st.stData[nSel].nUnBillCollection);
		break;
	case 5:
		strText = GetMyNumberFormat(st.nBalance);
		break;
	case 6:
		strText = GetMyNumberFormat(st.stData[nSel].nBillCollection);
		break;
	case 7:
		if (bSumrecord)
			strText = "";
		else
		{
			if (st.stData[nSel].dtBillCollection.m_status != 2)
				strText = st.stData[nSel].dtBillCollection.Format("%m-%d");
			else
				strText = "";
		}
		break;
	case 8:
		strText = GetMyNumberFormat(st.nInComeSum);
		break;
	case 9:
		strText = st.stData[nSel].bPressBill == TRUE ? "○" : "";
		break;
	case 10:
		strText = st.stData[nSel].strEtc;
		break;
	case 11:
		if (bSumrecord)
			strText = GetMyNumberFormat(st.stData[nSel].nSumCount);
		else
			strText = GetMyNumberFormat(st.stData[nSel].nCashCount + st.stData[nSel].nCreditCount + st.stData[nSel].nOnlineCount);
		break;
	case 12:
		strText = GetMyNumberFormat(st.stData[nSel].nCashCharge);
		break;
	case 13:
		strText = GetMyNumberFormat(st.stData[nSel].nCreditCharge);
		break;
	case 14:
		strText = GetMyNumberFormat(st.stData[nSel].nOnlineCharge);
		break;
	case 15:
		strText = GetMyNumberFormat(st.stData[nSel].nTransCharge);
		break;
	case 16:
		strText = GetMyNumberFormat(st.stData[nSel].nTax);
		break;
	case 17:
		if (bSumrecord)
			strText = GetMyNumberFormat(st.stData[nSel].nSumTotal);
		strText = GetMyNumberFormat(st.stData[nSel].nCashCharge + st.stData[nSel].nCreditCharge + st.stData[nSel].nOnlineCharge);
		break;
	case 18:
		if (bSumrecord)
			strText = "";
		else
		{
			if (st.stData[nSel].nReportState == 0)
				strText = "정산완료";
			else if (st.stData[nSel].nReportState == 10)
				strText = "부분입금";
			else if (st.stData[nSel].nReportState == 20)
				strText = "입금완료";
		}
		break;
	}

	return strText;
}


BOOL CLogiFunc::SaveAllocateInfo(ST_RIDER_INFO_ALLOCATE* pAllocate, BOOL pSimpleMode)
{
	CWaitCursor wait;
	COleDateTime dtInitDate = COleDateTime(2004, 1, 1, 0, 0, 0);
	COleDateTime dtJobStart, dtJobEnd;
	dtJobStart = dtJobEnd = dtInitDate;

	CMkCommand pCmd(m_pMkDb, "update_allocate_limit_2008_2");

	COleDateTimeSpan oSpan;

	oSpan.SetDateTimeSpan(0, pAllocate->dtJobStart.GetHour(), pAllocate->dtJobStart.GetMinute(), pAllocate->dtJobStart.GetSecond());
	dtJobStart += oSpan;
	pCmd.AddParameter(dtJobStart);

	oSpan.SetDateTimeSpan(0, pAllocate->dtJobEnd.GetHour(), pAllocate->dtJobEnd.GetMinute(), pAllocate->dtJobEnd.GetSecond());
	dtJobEnd += oSpan;
	pCmd.AddParameter(dtJobEnd);
	pCmd.AddParameter(max(pAllocate->nWorkState, 0));

	if (pAllocate->nWorkState == 1) //1이 업무중지 0은 재직 2는퇴사(deploy) 
	{
		COleDateTime dtTemp;
		CString strWorkMemo;
		dtTemp.SetDateTime(pAllocate->dtJobStop.GetYear(), pAllocate->dtJobStop.GetMonth(), pAllocate->dtJobStop.GetDay(),
			pAllocate->dtJobStop.GetHour(), pAllocate->dtJobStop.GetMinute(), pAllocate->dtJobStop.GetSecond());

		if (pAllocate->strJobStopMemo.GetLength() > 50)
			pAllocate->strJobStopMemo += pAllocate->strJobStopMemo.Mid(0, 50);

		pCmd.AddParameter(dtTemp);
		pCmd.AddParameter(pAllocate->strJobStopMemo);
	}
	else
	{
		pCmd.AddParameter(dtInitDate);
		pCmd.AddParameter("");
	}

	if (pAllocate->bLock)
	{
		pCmd.AddParameter(atoi(pAllocate->strLockTime));
		pCmd.AddParameter((pAllocate->strLockCount == "무제한") ? 100 : atoi(pAllocate->strLockCount));
	}
	else
	{
		pCmd.AddParameter(0);
		pCmd.AddParameter(100);
	}

	if (pAllocate->bMyOrderLock)
	{
		pCmd.AddParameter(atoi(pAllocate->strLockTime4MyOrder));
		pCmd.AddParameter((pAllocate->strLockCount4MyOrder == "무제한") ? 100 : atoi(pAllocate->strLockCount4MyOrder));
	}
	else
	{
		pCmd.AddParameter(0);
		pCmd.AddParameter(100);
	}

	if (pAllocate->bOtherOrderLock)
	{
		pCmd.AddParameter(atoi(pAllocate->strLockTime4OCOrder));
		pCmd.AddParameter((pAllocate->strLockCount4OCOrder == "무제한") ? 100 : atoi(pAllocate->strLockCount4OCOrder));
	}
	else
	{
		pCmd.AddParameter(0);
		pCmd.AddParameter(100);
	}

	if (pAllocate->bTimeAllocate)
	{
		pCmd.AddParameter(TRUE);
		COleDateTime dtAllocateDateTime(pAllocate->dtTimeAllocateDate.GetYear(), pAllocate->dtTimeAllocateDate.GetMonth(), pAllocate->dtTimeAllocateDate.GetDay(),
			pAllocate->dtTimeAllocateDate.GetHour(), pAllocate->dtTimeAllocateDate.GetMinute(), pAllocate->dtTimeAllocateDate.GetSecond());
		pCmd.AddParameter(max(dtInitDate, pAllocate->dtTimeAllocateDate));
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

	COleDateTime dtTempStart; COleDateTimeSpan dtSpanStart;
	dtSpanStart.SetDateTimeSpan(0, 0, 1, 0);
	dtTempStart.SetDate(pAllocate->dtInsuranceStart.GetYear(), pAllocate->dtInsuranceStart.GetMonth(), pAllocate->dtInsuranceStart.GetDay());
	dtTempStart += dtSpanStart;


	pCmd.AddParameter((pAllocate->bInsurance) ? max(dtInitDate, dtTempStart) : dtInitDate);

	COleDateTime dtTemp; COleDateTimeSpan dtSpan;
	dtSpan.SetDateTimeSpan(0, 11, 59, 0);
	dtTemp.SetDate(pAllocate->dtInsuranceEnd.GetYear(), pAllocate->dtInsuranceEnd.GetMonth(), pAllocate->dtInsuranceEnd.GetDay());
	dtTemp += dtSpan;


	pCmd.AddParameter((pAllocate->bInsurance) ? max(dtTemp, dtInitDate) : dtInitDate);

	CString strInsuranceID = "";
	if (pAllocate->bInsurance)
		strInsuranceID = pAllocate->strInsuranceCompany + "/" + pAllocate->strInsuranceID;

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

BOOL CLogiFunc::CheckGroupReport(CString strGNo, long nDstGNo, COleDateTime dtDate, long nMemberCount, CString& strNeedReReportID)
{
	CCheckGroupReportDlg dlg;
	dlg.m_strGNo = strGNo;
	dlg.m_nDstGNo = nDstGNo;
	dlg.m_dtDate = dtDate;
	dlg.m_nMemberCount = nMemberCount;

	if (dlg.DoModal() == IDOK)
	{
		strNeedReReportID = dlg.m_strNeedReReportID;
		return TRUE;
	}

	return FALSE;
}

BOOL CLogiFunc::ReReport(CString strNeedReReport)
{
	CString strEtc = "그룹이동";

	CMkCommand pCmd(m_pMkDb, "rereport_group_2");
	pCmd.AddParameter(strNeedReReport);
	pCmd.AddParameter(strEtc);
	pCmd.AddParameter(0);

	return pCmd.Execute();
}

BOOL CLogiFunc::SaveIncomeInfo(ST_RIDER_INFO_INCOME* pIncome, BOOL bSimpleMode)
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_rider_deposit_info_2008_9");

	pCmd.AddParameter(pIncome->nCompany);
	pCmd.AddParameter(pIncome->nRNo);
	pCmd.AddParameter(pIncome->nDepositType);
	pCmd.AddParameter(pIncome->nDepositAllocateType);
	pCmd.AddParameter(pIncome->nFixedDeposit); // 월/주 지입금
	pCmd.AddParameter(pIncome->bWeeklyDeposit); //월납 주납
	pCmd.AddParameter(max(pIncome->nPayMentDay, 0));
	pCmd.AddParameter(max(pIncome->nRiderIncomeDay, 0));
	pCmd.AddParameter(max(pIncome->nSameRiderIncomeDay, 0));

	pCmd.AddParameter(max(pIncome->nMyCallRateType, 0));
	pCmd.AddParameter(max(pIncome->nOtherCallRateType, 0));
	pCmd.AddParameter(max(pIncome->nDepositExtensionDay, 0)); //피디에이 잠금 지연
	pCmd.AddParameter(max(pIncome->nCreditReportType, 0)); //외사정산 타입 // 0 무정산 1익일 2// 월납
	pCmd.AddParameter(max(pIncome->bUseSmsNotify, 0)); // SMS -> 발송
	pCmd.AddParameter(max(pIncome->nSMSDealyDay, 0)); // SMS -> 발송
	pCmd.AddParameter(max(pIncome->bBranchAsOtherCall, 0)); // 자사 -> 타사
	pCmd.AddParameter(max(pIncome->bPenaltyCharge, 0));//과금

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

	if (!pRs.Execute(&pCmd)) return FALSE;

	return TRUE;
}

void CLogiFunc::InitRiderIncomeStruct(ST_RIDER_INFO_INCOME* st)
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
	st->nDT = 0;  // 기본정보
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

BOOL CLogiFunc::IsCrossOrder(long nTNo, CString& sCName, long& nState)
{
	CMkCommand pCmd(m_pMkDb, "select_tno_info");
	pCmd.AddParameter(nTNo);
	CMkParameter* pParName = pCmd.AddParameter(typeString, typeOutput, 100, "");
	CMkParameter* pParState = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), "");
	CMkParameter* pParShareCode1 = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), "");

	if (!pCmd.Execute())
		return FALSE;

	long nShareCode1;

	pParName->GetValue(sCName);
	pParState->GetValue(nState);
	pParShareCode1->GetValue(nShareCode1);

	return m_ci.m_nShareCode1 != nShareCode1;
}

void CLogiFunc::FillBankCode(BOOL bRefresh, CComboBox* pCmb, long nBankID)
{
	if (pCmb)
		pCmb->SetCurSel(GetIndexFromBankID(pCmb, nBankID));

	if (bRefresh == FALSE && m_mapBank.size() > ZERO)
	{
		if (pCmb)
		{
			if (pCmb->GetCount() != 0)
				return;
		}
	}

	m_mapBank.clear();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_bank_list");
	pCmd.AddParameter(0);

	if (!pRs.Execute(&pCmd))
		return;

	for (int i = ZERO; i < pRs.GetRecordCount(); i++)
	{
		ST_BANK st;

		pRs.GetFieldValue("nID", st.nID);
		pRs.GetFieldValue("sBankName", st.strBankName);
		pRs.GetFieldValue("nBankCode", st.strBankCode);

		m_mapBank.insert(MAP_BANK::value_type(st.nID, st));
		pRs.MoveNext();
	}

	if (pCmb)
	{
		long nItem = ZERO;
		pCmb->ResetContent();
		nItem = pCmb->AddString("선택안함");
		pCmb->SetItemData(nItem, ZERO);

		for (MAP_BANK::iterator it = m_mapBank.begin(); it != m_mapBank.end(); it++)
		{
			nItem = pCmb->AddString(it->second.strBankName);
			pCmb->SetItemData(nItem, it->second.nID);
		}

		pCmb->SetCurSel(GetIndexFromBankID(pCmb, nBankID));
	}
}

long CLogiFunc::GetIndexFromBankID(CComboBox* pCmb, long nBankID)
{
	for (int i = 0; i < pCmb->GetCount(); i++)
	{
		if (nBankID == (long)pCmb->GetItemData(i))
			return i;
	}

	return ZERO;
}

CString CLogiFunc::GetBankName(long nBankID)
{
	if (m_mapBank.size() == 0)
		FillBankCode(TRUE);

	MAP_BANK::iterator it = m_mapBank.find(nBankID);

	if (it != m_mapBank.end())
		return it->second.strBankName;

	return "";
}

long CLogiFunc::GetWindowTextLong(CWnd* pEdit)
{
	CString strTemp;
	pEdit->GetWindowText(strTemp);
	strTemp.Replace(",", "");
	return atoi(strTemp);
}

void CLogiFunc::FillStateMent()
{
	m_mapStateMent.clear();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_order_state_ment");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(1);

	if (!pRs.Execute(&pCmd)) return;

	for (int i = ZERO; i < pRs.GetRecordCount(); i++)
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

void CLogiFunc::LoadFromReg(ST_RIDER_MAP_SET_INFO& info)
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

void CLogiFunc::SaveToReg(ST_RIDER_MAP_SET_INFO& info)
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

void CLogiFunc::LoadFromReg(ST_RCP_DLG_SET_INFO& info)
{
	LOAD_FROM_REG(1, nReplacePhone1WithCID);
	LOAD_FROM_REG(1, nReplacePhone2WithPhone1);
	LOAD_FROM_REG(0, nIncreaseDetailControlAlways);
	LOAD_FROM_REG(0, nCopyDestCreditCustomer);
	LOAD_FROM_REG(0, nStartDontAutoCopy);
	LOAD_FROM_REG(0, nManualAddCustomer);
}

void CLogiFunc::SaveToReg(ST_RCP_DLG_SET_INFO& info)
{
	SAVE_TO_REG(nReplacePhone1WithCID);
	SAVE_TO_REG(nReplacePhone2WithPhone1);
	SAVE_TO_REG(nIncreaseDetailControlAlways);
	SAVE_TO_REG(nCopyDestCreditCustomer);
	SAVE_TO_REG(nStartDontAutoCopy);
	SAVE_TO_REG(nManualAddCustomer);
}

void CLogiFunc::LoadFromReg(ST_RCP_MAP_SET_INFO& info)
{
	LOAD_FROM_REG(1, nRcpMoveMap)
		LOAD_FROM_REG(1, nRcpDlgMoveMap)
		LOAD_FROM_REG(0, nNotCreateMapForm)
		LOAD_FROM_REG(1, nJoinWithCID)
}

void CLogiFunc::SaveToReg(ST_RCP_MAP_SET_INFO& info)
{
	SAVE_TO_REG(nRcpMoveMap)
		SAVE_TO_REG(nRcpDlgMoveMap)
		SAVE_TO_REG(nNotCreateMapForm)
		SAVE_TO_REG(nJoinWithCID)
}

long CLogiFunc::GetTailShowTimeFromIndex(long nIndex)
{
	int nTime[] = { 0, 15, 30, 45, 60, 90, 120, 180 };
	return nTime[nIndex];
}

CString CLogiFunc::GetStringFromLong(long nLong, BOOL bReturnZero)
{
	if (nLong == 0)
		return bReturnZero == TRUE ? "0" : "";

	char buffer[10];
	return CString(itoa(nLong, buffer, 10));
}

CString CLogiFunc::GetRcpType(long nRcpType, BOOL bInterNet)
{
	if (nRcpType == 0 && bInterNet == FALSE) //스마트Q
		return "스마트Q";
	else if (nRcpType == 1)
		return "스마트Q탭";
	else if (nRcpType == 3)
		return "스마트퀵";
	else if (nRcpType == 4)
		return "인터콜";
	else if (nRcpType == 5) //Q5
		return "Q5";
	else if (nRcpType == 6) //웹 API
		return "";
	else if (bInterNet == TRUE)
		return "인터넷";

	return "N/A";
}

BOOL CLogiFunc::IsWindow7()
{
	OSVERSIONINFO ver;
	ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&ver);
	printf("MajorVersion: %X\n", ver.dwMajorVersion);
	printf("MinorVersion: %X\n", ver.dwMinorVersion);
	printf("BuildNumber: %X\n", ver.dwBuildNumber);
	printf("PlatformId: %X\n", ver.dwPlatformId);
	printf("Version: %s\n", ver.szCSDVersion);

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


BOOL CLogiFunc::IsWindowXP()
{
	OSVERSIONINFO ver;
	ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&ver);
	printf("MajorVersion: %X\n", ver.dwMajorVersion);
	printf("MinorVersion: %X\n", ver.dwMinorVersion);
	printf("BuildNumber: %X\n", ver.dwBuildNumber);
	printf("PlatformId: %X\n", ver.dwPlatformId);
	printf("Version: %s\n", ver.szCSDVersion);

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

CString CLogiFunc::IsMoveRiderOk(long nCompany, long nRNo)
{
	if (nRNo == 0)
		return "0번 사용금지";

	CMkCommand pCmd(m_pMkDb, "select_is_move_rider_ok");
	CMkParameter* parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(nCompany);
	pCmd.AddParameter(nRNo);

	if (!pCmd.Execute())
		return FALSE;

	long nRet; parRet->GetValue(nRet);

	if (nRet == 0)
		return "사번 중복";

	return  "";
}


void CLogiFunc::MakeCarTypeCombo(CComboBox* pCmbBox)
{
	pCmbBox->ResetContent();

	pCmbBox->SetItemData(pCmbBox->AddString("오토바이"), CAR_AUTO); //0
	pCmbBox->SetItemData(pCmbBox->AddString("짐받이"), CAR_BIGBIKE); //0
	pCmbBox->SetItemData(pCmbBox->AddString("승용"), CAR_SEDAN);
	pCmbBox->SetItemData(pCmbBox->AddString("다마스"), CAR_DAMA);
	pCmbBox->SetItemData(pCmbBox->AddString("라보"), CAR_LABO);
	pCmbBox->SetItemData(pCmbBox->AddString("지하철"), CAR_SUBWAY);
	pCmbBox->SetItemData(pCmbBox->AddString("1톤"), CAR_TRUCK); //4
	pCmbBox->SetItemData(pCmbBox->AddString("1.4톤"), CAR_1_4_TON);
	pCmbBox->SetItemData(pCmbBox->AddString("2.5톤"), CAR_2_5_TON);
	pCmbBox->SetItemData(pCmbBox->AddString("3.5톤"), CAR_3_5_TON);
	pCmbBox->SetItemData(pCmbBox->AddString("5톤"), CAR_5_TON);
	pCmbBox->SetItemData(pCmbBox->AddString("5톤플축"), CAR_5_TON_PLUS); //9
	pCmbBox->SetItemData(pCmbBox->AddString("8톤"), CAR_8_TON);
	pCmbBox->SetItemData(pCmbBox->AddString("11톤"), CAR_11_TON);
	pCmbBox->SetItemData(pCmbBox->AddString("14톤"), CAR_14_TON);
	pCmbBox->SetItemData(pCmbBox->AddString("15톤"), CAR_15_TON);
	pCmbBox->SetItemData(pCmbBox->AddString("18톤"), CAR_18_TON);//14
	pCmbBox->SetItemData(pCmbBox->AddString("25톤"), CAR_25_TON);//15
}


void CLogiFunc::SetCarType(CComboBox* pCmbBox, long nCarType)
{

	if (nCarType == CAR_AUTO)			pCmbBox->SetCurSel(0);
	else if (nCarType == CAR_BIGBIKE)	pCmbBox->SetCurSel(1);
	else if (nCarType == CAR_SEDAN)		pCmbBox->SetCurSel(2);
	else if (nCarType == CAR_DAMA)		pCmbBox->SetCurSel(3);
	else if (nCarType == CAR_LABO)		pCmbBox->SetCurSel(4);
	else if (nCarType == CAR_SUBWAY)		pCmbBox->SetCurSel(5);
	else if (nCarType == CAR_TRUCK)		pCmbBox->SetCurSel(6);
	else if (nCarType == CAR_1_4_TON)	pCmbBox->SetCurSel(7);
	else if (nCarType == CAR_2_5_TON)	pCmbBox->SetCurSel(8);
	else if (nCarType == CAR_3_5_TON)	pCmbBox->SetCurSel(9);
	else if (nCarType == CAR_5_TON)		pCmbBox->SetCurSel(10);
	else if (nCarType == CAR_5_TON_PLUS)	pCmbBox->SetCurSel(11);
	else if (nCarType == CAR_8_TON)		pCmbBox->SetCurSel(12);
	else if (nCarType == CAR_11_TON)		pCmbBox->SetCurSel(13);
	else if (nCarType == CAR_14_TON)		pCmbBox->SetCurSel(14);
	else if (nCarType == CAR_15_TON)		pCmbBox->SetCurSel(15);
	else if (nCarType == CAR_18_TON)		pCmbBox->SetCurSel(16);
	else if (nCarType == CAR_25_TON)		pCmbBox->SetCurSel(17);
	else
		pCmbBox->SetCurSel(0);
}


long CLogiFunc::GetCarType(CComboBox* pCmbBox)
{
	return pCmbBox->GetItemData(pCmbBox->GetCurSel());
}

BOOL CLogiFunc::IsRequestOver15Day(int nCompany)
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_transfer_request_over_15day");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);

	if (!pRs.Execute(&pCmd)) return false;

	if (pRs.GetRecordCount() > 0)
		return TRUE;
	else
		return FALSE;
}

long CLogiFunc::GetCardVendor(long nCompany)
{
	MAP_CARD_VENDOR::iterator it = m_mapCardVendor.find(nCompany);

	if (it == m_mapCardVendor.end())
		return 0;

	return it->second.nVendorCode;
}


void CLogiFunc::LoadCardInfo()
{
	m_mapCardVendor.clear();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_card_vendor_list");
	cmd.AddParameter(0);

	if (!rs.Execute(&cmd))
		return;

	for (int i = 0; i < rs.GetRecordCount(); i++)
	{
		ST_CARD_VENDOR st;
		rs.GetFieldValue("nCompany", st.nCompany);
		rs.GetFieldValue("sVendor", st.strVendor);
		rs.GetFieldValue("nVendorCode", st.nVendorCode);

		m_mapCardVendor.insert(MAP_CARD_VENDOR::value_type(st.nCompany, st));
		rs.MoveNext();
	}
}

BOOL CLogiFunc::CheckCardPayCondition(long nTNo, long nCharge, long nDeposit, CString& strError)
{
	CMkCommand cmd(m_pMkDb, "check_card_pay_condition_ok");
	CMkParameter* pParRet = cmd.AddParameter(typeLong, typeReturn, 0);
	cmd.AddParameter(nTNo);
	cmd.AddParameter(nCharge);
	cmd.AddParameter(nDeposit);
	CMkParameter* parError = cmd.AddParameter(typeString, typeOutput, 300, "");

	if (!cmd.Execute())
		return FALSE;

	long nRet; pParRet->GetValue(nRet);
	parError->GetValue(strError);

	if (nRet == 100)
		return TRUE;

	return FALSE;
}

BOOL CLogiFunc::GetCardPayType(ST_CARD_INFO& st, BOOL bUseForTranCance)
{
	CMkCommand cmd(m_pMkDb, "select_card_tran_info3");
	CMkParameter* parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(st.nTNo);
	CMkParameter* parCardType = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter* parCardProcess = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter* parCharge = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter* parDisplayCharge = cmd.AddParameter(typeString, typeOutput, 100, "");
	CMkParameter* parTID = cmd.AddParameter(typeString, typeOutput, 50, "");
	CMkParameter* parMID = cmd.AddParameter(typeString, typeOutput, 50, "");
	CMkParameter* parSessionKey = cmd.AddParameter(typeString, typeOutput, 100, "");
	CMkParameter* parCardServerAddr = cmd.AddParameter(typeString, typeOutput, 50, "");
	CMkParameter* parCardServerPort = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter* parLogiServerAddr = cmd.AddParameter(typeString, typeOutput, 50, "");
	CMkParameter* parLogiServerPort = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	cmd.AddParameter(bUseForTranCance);
	CMkParameter* parFeeType = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter* parError = cmd.AddParameter(typeString, typeOutput, 200, "");
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);

	if (!cmd.Execute())
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

CString CLogiFunc::GetMyCardNumber(CString strCardNumber)
{
	CString strNew;

	if (strCardNumber.GetLength() == 0)
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

BOOL CLogiFunc::SendNiceCardPay(CMkDatabase* pMkCardDb, int nTranType, int nTNo, int nBillkey, CString strCardNumber, CString strMM, CString strYY, CString strWCompany, CString strWNo, CString& strMsg, BOOL bSendSms)
{
	if (pMkCardDb == NULL)
	{
		MessageBox(NULL, "카드서버에 연결할 소켓이 생성되지 않았습니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	strCardNumber.Replace("-", "");
	//	szID,int nTNo,const char* szCardnumber,const char* szCardexpy,const char* szCardexpm
	QPACKET* rcv = NULL;
	char data[300];

	BOOL bRet = FALSE;
	int nSubType = PST_NICE_REQUSET_OK;

	if (nTranType == 0)
		nSubType = PST_NICE_REQUSET_CANCEL;

	//		ShowDlgBox(DETAIL_INFO_RECVING);
	//CShowDlgBox ShowDlgBox(nTranType == 1 ? L"카드 결재 조회중" : L"카드 결재취소 요청중");
	char szPhoneNumber[20];
	//strcpy(szPhoneNumber, m_si.szPhoneNumber);
	strcpy(szPhoneNumber, m_ui.strID);
	STRCPY(data, szPhoneNumber, VL_END);
	STRCAT(data, strWCompany, VL_END);
	STRCAT(data, strWNo, VL_END);
	STRCAT(data, GetStringFromLong(nTNo), VL_END);
	STRCAT(data, GetStringFromLong(nBillkey), VL_END);
	STRCAT(data, strCardNumber, VL_END);
	STRCAT(data, strMM, VL_END);
	STRCAT(data, strYY, VL_END);
	STRCAT(data, GetStringFromLong(bSendSms, TRUE), VL_END);

	if (!pMkCardDb->GetSocket()->SendData(PT_REQUEST, nSubType, data))
	{
		MessageBox(NULL, "카드결제정보 전송 실패\r\n다시시도하세요", "확인", MB_ICONERROR);
		return FALSE;
	}

	//if(!Socket->SendData(PT_REQUEST, nSubType, data))
	//	THROW("전송실패");

	rcv = (QPACKET*)pMkCardDb->GetSocket()->ReadStream();

	if (rcv == NULL)
	{
		MessageBox(NULL, "카드결제 요청 실패\r\n다시시도하세요", "확인", MB_ICONERROR);
		return FALSE;
	}

	if (rcv != NULL)
	{
		if (PT_OK == rcv->nType)
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
	if (rcv->nType == PT_OK) bRet = TRUE;
	else bRet = FALSE;

	if (rcv != NULL)
		free(rcv);

	return bRet;

	return FALSE;
}

CString CLogiFunc::GetMyNumberFadding(CString strNumber, int nLen)
{
	if (nLen < strNumber.GetLength())
		return strNumber;
	else
	{
		while (nLen < strNumber.GetLength())
			strNumber = "0" + strNumber;
		return strNumber;
	}
}

CString CLogiFunc::GetDay(COleDateTime dt)
{
	char* szDayOfWeek[] = { "일", "월", "화", "수", "목", "금", "토" };

	CString strDayOfWeek;
	strDayOfWeek.Format("%s", szDayOfWeek[dt.GetDayOfWeek() - 1]);

	return strDayOfWeek;
}

BOOL CLogiFunc::IsCardCheckState(long nState, long nCancelType)
{
	if (nState == STATE_CANCELED && nCancelType == 10)
		return TRUE;

	if (nState == STATE_WAIT ||
		nState == STATE_OK ||
		nState == STATE_OK_ONLY_MAN ||
		nState == STATE_ALLOCATED ||
		nState == STATE_FINISH)
		return TRUE;
	else
		return FALSE;
}

long CLogiFunc::GetCardRealPay(long nTNo)
{
	CMkCommand cmd(m_pMkDb, "select_card_original_pay");
	CMkParameter* pParCharge = cmd.AddParameter(typeLong, typeReturn, 0);
	cmd.AddParameter(nTNo);

	if (!cmd.Execute())
		return 0;

	long nCharge;
	pParCharge->GetValue(nCharge);

	return nCharge;
}

long CLogiFunc::GetShareLevel(long nShareCode1, long nShareCode2, long nShareCode3, long nShareCode4, long nShareCode5)
{
	if (m_ci.m_nShareCode1 == nShareCode1 && nShareCode1 != 0)
		return 1;
	else if (m_ci.m_nShareCode2 == nShareCode2 && nShareCode2 != 0)
		return 2;
	else if (m_ci.m_nShareCode3 == nShareCode3 && nShareCode3 != 0)
		return 3;
	else if (m_ci.m_nShareCode4 == nShareCode4 && nShareCode4 != 0)
		return 4;
	else if (m_ci.m_nShareCode5 == nShareCode5 && nShareCode5 != 0)
		return 5;

	return 6;
}

CString CLogiFunc::ChangeStringFromExcel(VARIANT varValue)
{
	CString strVal = "";
	if (varValue.vt == VT_BSTR)
		strVal = varValue.bstrVal;
	else if (varValue.vt == VT_EMPTY)
		strVal = "";
	else if (varValue.vt == VT_NULL)
		strVal = "NULL";
	else if (varValue.vt == VT_BOOL) // *    VARIANT_BOOL   VT_BOOL
		strVal.Format("%b", varValue.boolVal);

	else if (varValue.vt == VT_I2)
		strVal.Format("%d", (int)varValue.iVal);
	else if (varValue.vt == VT_I4)
		strVal.Format("%d", (int)varValue.lVal);
	else if (varValue.vt == VT_R4) // *    FLOAT          VT_R4
		strVal.Format("%2lf", (double)varValue.fltVal);
	else if (varValue.vt == VT_R8)
		strVal.Format("%ld", (long)varValue.dblVal);
	else if (varValue.vt == VT_DATE) // *    DATE           VT_DATE
	{
		COleDateTime dtOle(varValue.date);
		strVal = dtOle.Format("%Y-%m-%d %H:%M:%S");
	}
	else if (varValue.vt == VT_INT) // *    INT            VT_INT
		strVal.Format("%d", varValue.intVal);
	else if (varValue.vt == VT_I1) // *    CHAR           VT_I1
		strVal.Format("%c", varValue.cVal);

	return strVal;
}

CString CLogiFunc::GetFolderDate(CString strFileName)
{
	int nIndex = 0;
	for (int i = 0; i < 3; i++)
	{
		if (strFileName.Find("-", nIndex + 1) != -1
			&& strFileName.Find("-", strFileName.Find("-", nIndex + 1)) != -1)
			nIndex = strFileName.Find("-", strFileName.Find("-", nIndex + 1));
	}

	CString strDate = strFileName.Mid(nIndex + 1, 8);

	if (nIndex == 0 || strDate.GetLength() != 8)
		return "";

	return strDate;
}

long CLogiFunc::GetRemoveMyNumberFormat(CString strNumber)
{
	strNumber.Replace(",", "");
	return atoi(strNumber);
}

void CLogiFunc::MoveFocus(CWnd* pWnd)
{
	pWnd->SetFocus();
}

BOOL CLogiFunc::IsUseNewDlg()
{
	return AfxGetApp()->GetProfileInt("RcpPage", "bUseNewRcpDlg", 0);
}

CString CLogiFunc::RemoveComma(CString strNumber)
{
	strNumber.Remove(',');
	return strNumber;
}

CString CLogiFunc::GetStringFromEdit(CWnd* pEdit)
{
	if (pEdit == NULL)
		return 0;

	CString strTemp;
	pEdit->GetWindowText(strTemp);
	return strTemp;
};

long CLogiFunc::GetLongFromEdit(CWnd* pEdit)
{
	if (pEdit == NULL)
		return 0;

	CString strTemp;
	pEdit->GetWindowText(strTemp);
	strTemp.Replace(",", "");
	return atoi(strTemp);
};

CString CLogiFunc::GetRemoveLastDong(CString strDong)
{
	if (strDong.GetLength() <= 4)
		return strDong;

	if (strDong.Right(2) == "동")
		return strDong.Left(strDong.GetLength() - 2);

	return strDong;
}

BOOL CLogiFunc::IsDate(CString strTemp)
{
	if (strTemp.Find("/") >= 0 || strTemp.Find(":") >= 0 || strTemp.Find("-") >= 0)
	{
		BOOL bFindA = strTemp.Replace("/", "");
		BOOL bFindB = strTemp.Replace(":", "");
		BOOL bFindC = strTemp.Replace("-", "");
		strTemp.Replace(" ", "");

		if (IsStringDigit(strTemp))
		{
			if ((strTemp.Left(2) = "01") &&
				((strTemp.GetLength() == 10 || strTemp.GetLength() == 11) && bFindB == FALSE)) //휴대폰
				return FALSE;
			else if ((strTemp.GetLength() == 7 || strTemp.GetLength() == 8) && bFindB == FALSE)//일반전화
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

CString CLogiFunc::GetRiderPhone(long nRiderCompany, long nRNo)
{
	if (nRiderCompany == 0 || nRNo == 0)
		return "";

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_phone");

	pCmd.AddParameter(nRiderCompany);
	pCmd.AddParameter(nRNo);

	CString strPhone = "";

	if (pRs.Execute(&pCmd))
		pRs.GetFieldValue("sHp", strPhone);

	return strPhone;
}

CString CLogiFunc::GetDashCardNumber(CString strCardNumber)
{
	CString strNumber = strCardNumber;

	strNumber.Remove('-');

	if (strNumber.GetLength() > 6)
	{
		CString strTemp = "";

		for (int i = 0; i < strNumber.GetLength(); i++)
		{
			strTemp += strNumber.GetAt(i);

			if (i % 4 == 3)
				strTemp += "-";
		}

		if (strTemp.Right(1) == "-")
			strTemp = strTemp.Left(strTemp.GetLength() - 1);

		strNumber = strTemp;
	}

	return strNumber;
}

BOOL CLogiFunc::UpdateRiderCardState(CString strCardNumber, long nCompany, long nRNo, CString& strRName)
{
	CMkCommand cmd(m_pMkDb, "VRCardRider_update_1");
	CMkParameter* parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);

	cmd.AddParameter(strCardNumber);
	cmd.AddParameter(nCompany);
	cmd.AddParameter(nRNo);
	cmd.AddParameter(0);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);
	CMkParameter* parOut = cmd.AddParameter(typeString, typeOutput, 200, "");
	CMkParameter* parRName = cmd.AddParameter(typeString, typeOutput, 50, "");

	if (!cmd.Execute())
		return FALSE;

	long nRet; parRet->GetValue(nRet);
	CString strError; parOut->GetValue(strError);
	parRName->GetValue(strRName);

	if (nRet == 0)
	{
		MessageBox(NULL, strError, "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	return TRUE;
}

BOOL CLogiFunc::InsertNewCard(CString strCardNumber, long nCompany, long nRNo)
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
	CMkParameter* parError = cmd.AddParameter(typeString, typeOutput, 200, "");

	if (!cmd.Execute())
		return FALSE;

	CString strError; parError->GetValue(strError);

	if (!strError.IsEmpty())
	{
		MessageBox(NULL, strError, "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	return TRUE;
}

int CLogiFunc::GetDistanceMeter(long nPosX, long nPosY, long nPosX2, long nPosY2)
{
	double dx = (nPosY2 - nPosY) * 0.30918467038935;
	double dy = (nPosX2 - nPosX) * cos((nPosY2 + nPosY) * 0.000000024240661) * 0.30918467038935;
	return sqrt(dx * dx + dy * dy);
}

BOOL CLogiFunc::MakeShareOrder(long nTNo, BOOL bShare)
{
	CMkCommand pCmd(m_pMkDb, "make_shared_order_3");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(bShare);
	pCmd.AddParameter(m_ui.strName);

	return pCmd.Execute();
}

DWORD CLogiFunc::HexStrToInt(CString aStr)
{
	DWORD        i;
	char* string, * stopstring;

	string = (char*)(LPCTSTR)aStr;
	strtod(string, &stopstring);
	i = (DWORD)strtoul(string, &stopstring, 16);
	return i;
}

CString CLogiFunc::GetCustomerEMail(long nCNo)
{
	CString strEMail = "";

	CMkCommand cmd(m_pMkDb, "select_customer_email");
	cmd.AddParameter(nCNo);
	CMkParameter* parID = cmd.AddParameter(typeString, typeOutput, 100, "");

	if (!cmd.Execute())
		return "";

	parID->GetValue(strEMail);

	return strEMail;
}

BOOL CLogiFunc::IsMobilePhoneNumber(CString strText)
{
	if (strText.Left(2) == "01" && IsStringDigit(strText) && (strText.GetLength() == 10 || strText.GetLength() == 11))
		return TRUE;

	return FALSE;
}

BOOL CLogiFunc::IsNumber(LPCTSTR pszText)
{
	ASSERT_VALID_STRING(pszText);

	for (int i = 0; i < lstrlen(pszText); i++)
		if (!_istdigit(pszText[i]))
			return false;

	return true;
}

void CLogiFunc::AddTextMiddle(CString strText, CEdit* pEdit)
{
	CString strInput; pEdit->GetWindowText(strInput);

	CStringW strTextW(strText);
	CStringW sInputW(strInput);

	int nStartSel, nDestSel;

	pEdit->GetSel(nStartSel, nDestSel);

	if (nStartSel == -1) return;

	CString sResult = CString(strInput.Left(nStartSel)) + CString(strTextW) + CString(strInput.Right(strInput.GetLength() - nDestSel));
	pEdit->SetWindowText(sResult);

	pEdit->SetFocus();
	pEdit->SetSel(nStartSel + strText.GetLength(), nStartSel + strText.GetLength());
}

BOOL CLogiFunc::UpdateSaveMent(long nID, CString strMent)
{
	CMkCommand cmd(m_pMkDb, "update_save_sms_ment");
	cmd.AddParameter(nID);
	cmd.AddParameter(strMent);

	return cmd.Execute();
}

BOOL CLogiFunc::InsertSaveMent(long nCompany, long nType, CString strMent)
{
	CMkCommand cmd(m_pMkDb, "insert_save_sms_ment");
	cmd.AddParameter(nCompany);
	cmd.AddParameter(nType);
	cmd.AddParameter(strMent);

	return cmd.Execute();
}

BOOL CLogiFunc::SendSmsBulkTest(long nCompany, long nTranID, CString strRecvPhone, CString strCallBackPhone,
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

BOOL CLogiFunc::DeleteSaveMent(long nID)
{
	CMkCommand cmd(m_pMkDb, "delete_save_sms_ment");
	cmd.AddParameter(nID);

	return cmd.Execute();
}

BOOL CLogiFunc::UpChargeForNotAllocate(long nTNo, long nCharge, CWnd* pMsgBox)
{
	CMkCommand cmd(m_pMkDb, "update_charge_for_not_allocate_1");
	CMkParameter* pParRet = cmd.AddParameter(typeLong, typeReturn, 0);
	cmd.AddParameter(nTNo);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.strName);
	cmd.AddParameter(nCharge);

	cmd.Execute();

	long nRet; pParRet->GetValue(nRet);

	if (nRet == 1)
	{
		if (nCharge == -1)
		{
			if (pMsgBox)
				pMsgBox->MessageBox("요금인상이 해지되었습니다.", "확인", MB_ICONINFORMATION);
		}
		else
		{
			if (pMsgBox)
				pMsgBox->MessageBox("금액이 추가되었습니다", "확인", MB_ICONINFORMATION);
		}

		return TRUE;
	}
	else
	{
		if (pMsgBox)
			pMsgBox->MessageBox("요금인상 기능을 사용하지 않거나 오더가 존재하지 않습니다.", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
}


CString CLogiFunc::GetSecondTimeString(int nSec, BOOL bRemoveSec)
{
	int nAbsSec = abs(nSec);
	CString strTime;

	if (bRemoveSec)
	{
		if (nAbsSec <= 30)
			strTime = "";
		else if (nAbsSec < 60)
			strTime.Format("%d초", nAbsSec);
	}
	else
	{
		if (nAbsSec <= 1)
			strTime = "-";
		else if (nAbsSec < 60)
			strTime.Format("%d초", nAbsSec);
		else
			strTime.Format("%d분%d초", nAbsSec / 60, nAbsSec % 60);
	}

	return strTime;
}

CString CLogiFunc::GetAsteriskPhoneNumber(CString strPhoneNumber)
{
	CString strNumber = GetDashPhoneNumber(strPhoneNumber);

	if (strPhoneNumber.GetLength() < 6)
		return strNumber;

	long nIndex = strNumber.ReverseFind('-');

	if (nIndex < 0)
		return strNumber;

	//strNumber = strNumber.Left(nIndex-1) + "*" + strNumber.Mid(nIndex, 3) + "**";
	strNumber = strNumber.Left(nIndex + 1) + "****";

	return strNumber;
}

BOOL CLogiFunc::InsertAllocGroupCombo(CComboBox* pCombo, long nCompany)
{
	pCombo->ResetContent();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_alloc_group");

	cmd.AddParameter(nCompany);

	if (!rs.Execute(&cmd)) return FALSE;

	if (rs.GetRecordCount() != 10) return FALSE;

	long nItem = 0;

	pCombo->InsertString(nItem, "그룹등록안됨");
	pCombo->SetItemData(nItem++, 0);

	long nID, nGrade;
	CString strGroupName, strDisplay;

	for (int i = 0; i < rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("nGrade", nGrade);
		rs.GetFieldValue("sGroupName", strGroupName);

		strDisplay.Format("%s [%d]등급", strGroupName, nGrade);

		pCombo->InsertString(nItem, strDisplay);
		pCombo->SetItemData(nItem++, nGrade);
		//pCombo->SetItemData(nItem++, nID);

		rs.MoveNext();
	}

	pCombo->SetCurSel(0);
	return TRUE;
}

CString CLogiFunc::GetAutoDDDSetting(int nCompany, CString strCallingLine)
{
	CString strRet = strCallingLine;

	if (strRet == "")
		strRet = GetBranchInfo(nCompany)->strCallingLine;

	if (strRet == "")
		strRet = "9";

	if (strRet.Find("A") != -1)
	{
		CString strTemp = strRet.Left(1);
		if (strTemp != "0" && strTemp != "1")
			//strRet = GetBranchInfo(nCompany)->strDDD + strRet;
			strRet = m_ci.m_strDDD + strRet;
	}
	return strRet;
}

BOOL CLogiFunc::GetConnetcInfo(CString& strAddr, long& nPort)
{
	strAddr = "";
	nPort = 0;

	CMkCommand cmd(m_pMkDb, "select_card_tran_info_for_connect");
	cmd.AddParameter(m_ui.nCompany);
	CMkParameter* pParAddr = cmd.AddParameter(typeString, typeOutput, 100, "");
	CMkParameter* pParPort = cmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

	if (!cmd.Execute())
		return FALSE;

	pParAddr->GetValue(strAddr);
	pParPort->GetValue(nPort);

	if (!strAddr.IsEmpty() && nPort > 0)
		return TRUE;

	return FALSE;

}

BOOL CLogiFunc::IsDID(int nDID, CString strSearchDID)
{
	if (strSearchDID.Find(",XXXXXXXX,") >= 0)
		return TRUE;

	CString strFindDID;
	strFindDID.Format(",%d,", nDID);
	if (strSearchDID.Find(strFindDID) >= 0)
		return TRUE;
	else
		return FindNumber(9, strFindDID, strSearchDID);

	return FALSE;
}

BOOL CLogiFunc::FindNumber(int nMaxIndex, CString strNumber, CString strTotalNumber)
{
	int nIndex = 2;
	while (nIndex < nMaxIndex && nIndex < strNumber.GetLength() - 1)
	{
		CString strTemp;
		for (int i = 1; i < nIndex; i++)
			strTemp += "X";

		strNumber = strNumber.Left(strNumber.GetLength() - nIndex) + strTemp + ",";

		if (strTotalNumber.Find(strNumber) >= 0)
			return TRUE;

		nIndex++;
	}
	return FALSE;
}

BOOL CLogiFunc::UpdateRiderInfoForReserved(long nTNo, long nRiderCompany, long nRNo)
{
	CMkCommand cmd(m_pMkDb, "update_rider_for_reserved");
	CMkParameter* parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(nTNo);
	cmd.AddParameter(nRiderCompany);
	cmd.AddParameter(nRNo);

	if (!cmd.Execute())
		return FALSE;

	long nRet; parRet->GetValue(nRet);

	if (nRet == 1)
		return TRUE;

	return FALSE;



}

CString CLogiFunc::GetSMSCallBackLogState(int nState)
{
	CString strState = "";
	switch (nState)
	{
	case 0:
		strState = "";
		break;

	case 10:
		strState = "통신사실증명 반려";
		break;
	case 11:
		strState = "통신사실증명 반려취소";
		break;
	case 12:
		strState = "사업자/개인신분증 반려";
		break;
	case 13:
		strState = "사업자/개인신분증 반려취소";
		break;

	case 20:
		strState = "PBX 등록서류 반려";
		break;
	case 21:
		strState = "PBX 등록서류 반려취소";
		break;
	case 22:
		strState = "PBX 등록서류 메일전송";
		break;
	case 23:
		strState = "PBX 등록서류 통신사 반송";
		break;
	case 24:
		strState = "PBX 등록서류 통신사승인";
		break;




	case 30:
		strState = "로지진행";
		break;
	case 31:
		strState = "로지진행취소";
		break;

	case 38:
		strState = "로지거부";
		break;


	case 40:
		strState = "승인";
		break;
	case 41:
		strState = "승인취소 등록중";
		break;
	case 42:
		strState = "승인취소 로지진행";
		break;

	case 51:
		strState = "로지거절";
		break;
	case 52:
		strState = "로지메모";
		break;
	case 53:
		strState = "업체메모";
		break;



	case 70:
		strState = "로지임의삭제";
		break;



	case 500:
		strState = "로지사용";
		break;
	case 501:
		strState = "로지정지";
		break;

	}
	return strState;
}

BOOL CLogiFunc::CheckTel(CString strTel)
{

	if (CHECK_TEL_BYPASS == TRUE) return TRUE;

	CString strTempTel = strTel;

	if (strTempTel.GetLength() <= 0)
	{
		AfxMessageBox("발신자번호 관련 서류를 등록하세요", MB_ICONERROR);
		return FALSE;
	}


	strTempTel.Replace("-", "");
	if (!IsStringDigit(strTempTel))
	{
		AfxMessageBox("전화번호는 숫자이어야만 합니다", MB_ICONERROR);
		return FALSE;
	}


	if (strTempTel.GetLength() < 8)
	{
		AfxMessageBox("전화번호는 8자리 이상이어야만(지역번호포함) 합니다", MB_ICONERROR);
		return FALSE;
	}

	if (strTempTel.GetLength() > 12)
	{
		AfxMessageBox("전화번호는 12자리 이하이어야만 합니다", MB_ICONERROR);
		return FALSE;
	}

	if (strTempTel.Left(1).Compare("0") != 0 && strTempTel.Left(1).Compare("1") != 0)
	{
		AfxMessageBox("전화번호는 첫번째 자리가 0, 1 이어합니다 (지역번호 추가) ", MB_ICONERROR);
		return FALSE;
	}


	if (strTempTel.Left(2) == "01")
	{

		if (!
			(
				strTempTel.Left(3).Compare("010") == 0 || strTempTel.Left(3).Compare("011") == 0 ||
				strTempTel.Left(3).Compare("017") == 0 || strTempTel.Left(3).Compare("018") == 0 ||
				strTempTel.Left(3).Compare("016") == 0
				)
			)
		{
			AfxMessageBox("핸드폰 번호의 형식에 맞지 않습니다. ", MB_ICONERROR);
			return FALSE;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	if (strTempTel.Left(1).Compare("1") == 0)
	{
		if (strTempTel.GetLength() != 8)
		{
			AfxMessageBox("전화번호는 첫번째 자리가 1 인 전국번호는 8자리이어야 합니다 ", MB_ICONERROR);
			return FALSE;
		}
		else
			return TRUE;

	}



	if (
		strTempTel.Left(3).Compare("010") == 0 || strTempTel.Left(3).Compare("011") == 0 ||
		strTempTel.Left(3).Compare("017") == 0 || strTempTel.Left(3).Compare("018") == 0 ||
		strTempTel.Left(3).Compare("016") == 0
		)
	{

		if (strTempTel.Mid(3, 1) == "0" ||
			strTempTel.Mid(3, 1) == "1")
		{
			AfxMessageBox("이동전화사업자 세칙에 맞지 않습니다", MB_ICONERROR);
			return FALSE;
		}

		if (!(strTempTel.Mid(4).GetLength() == 7 || strTempTel.Mid(4).GetLength() == 8))
		{
			AfxMessageBox("핸드폰 번호는 국선을 빼고 7 ~ 8자리이어야 합니다 ", MB_ICONERROR);
			return FALSE;
		}
		else
			return TRUE;
	}



	CString strRemoveDDD = "";
	BOOL bLocalNumber = IsLocalNumber(strTempTel, strRemoveDDD);

	if (bLocalNumber)
	{
		if (strRemoveDDD.GetLength() != 7 &&
			strRemoveDDD.GetLength() != 8)
		{
			AfxMessageBox("지역번호는 DDD를 빼고 7 ~ 8자리이어야 합니다 ", MB_ICONERROR);
			return FALSE;
		}

		if (strRemoveDDD.Left(2) == "15" ||
			strRemoveDDD.Left(2) == "16" ||
			strRemoveDDD.Left(2) == "18")
		{
			AfxMessageBox("특수번호는 지역번호를 붙힐 수 없습니다", MB_ICONERROR);
			return FALSE;
		}

		return TRUE;
	}


	// 050 060 070 080
	if (strTempTel.Left(3).Compare("050") == 0 || strTempTel.Left(3).Compare("060") == 0 ||
		strTempTel.Left(3).Compare("070") == 0 || strTempTel.Left(3).Compare("080") == 0 ||
		strTempTel.Left(3).Compare("030") == 0
		)
	{
		if (strTempTel.Left(3).Compare("070") == 0 &&
			(strTempTel.Mid(3, 1) == "0" || strTempTel.Mid(3, 1) == "1"))
		{
			AfxMessageBox("기간통신사업자 세칙에 맞지 않습니다", MB_ICONERROR);
			return FALSE;
		}

		if (!(strTempTel.Mid(3).GetLength() == 7 || strTempTel.Mid(3).GetLength() == 8 || strTempTel.Mid(3).GetLength() == 9))
		{
			AfxMessageBox("050 060 070 080  빼고 7 ~ 9자리이어야 합니다 ", MB_ICONERROR);
			return FALSE;
		}
		else
			return TRUE;

	}

	/// 안심번호

	//온세텔레콤(국번 0503, 0504, 0507), KT(0502), LG유플러스(0503, 0505), SK브로드밴드(0506), SK텔링크(0504)


	if (strTempTel.Left(4).Compare("0502") == 0 || strTempTel.Left(4).Compare("0503") == 0 ||
		strTempTel.Left(4).Compare("0504") == 0 || strTempTel.Left(4).Compare("0505") == 0 ||
		strTempTel.Left(4).Compare("0506") == 0
		)
	{
		if (!(strTempTel.Mid(3).GetLength() == 7 || strTempTel.Mid(3).GetLength() == 8))
		{
			AfxMessageBox("0502 ~ 6 안신번호는 국선을 빼고 7 ~ 8자리이어야 합니다 ", MB_ICONERROR);
			return FALSE;
		}
		else
			return TRUE;

	}

	AfxMessageBox("해당번호는 사용할 수 없는 번호 입니다.  ", MB_ICONERROR);

	return FALSE;
}

BOOL CLogiFunc::IsLocalNumber(CString strPhone, CString& strRemoveDDD)
{
	CString str[] = { "02", "064", "051", "053", "032","062", "042",	"052", "044", "031",
		"033", "043", "041", "063", "061", "054", "055" };

	long nCount = sizeof(str) / sizeof(str[0]);

	for (int i = 0; i < nCount; i++)
	{
		CString strLocal = str[i];

		if (strPhone.Left(strLocal.GetLength()) == strLocal)
		{
			strRemoveDDD = strPhone.Right(strPhone.GetLength() - strLocal.GetLength());
			return TRUE;
		}
	}

	return FALSE;
}

CString CLogiFunc::ConvertStringToSendData(CString strText)
{
	CByteArray msg;
	return ConvertStringToSendData(strText, msg);
}

CString CLogiFunc::ConvertStringToSendData(CByteArray* msg)
{
	CString strItemSum = "";
	CString strItem;
	//char szData[10000];

	for (int i = 0; i < (int)msg->GetSize(); i++)
	{
		strItem.Format("%02X", (BYTE)msg->GetAt(i));
		strItemSum += "%" + strItem;
		//sprintf(&szData[i * 2], "%02X", (BYTE)msg->GetAt(i));
	}

	return strItemSum;
}

CString CLogiFunc::ConvertStringToSendData(const CString& s, CByteArray& msg)
{
	BOOL bSuccess = FALSE;
#ifdef _UNICODE
	int n = ::WideCharToMultiByte(CP_UTF8, 0, s, -1, NULL, 0, NULL, NULL);
	if (n == 0)
	{ /* failed */
		DWORD err = ::GetLastError();
		msg.SetSize(0);
		bSuccess = FALSE;
	} /* failed */
	else
	{ /* success */
		msg.SetSize(n);
		n = ::WideCharToMultiByte(CP_UTF8, 0, s, -1, (LPSTR)msg.GetData(), n, NULL, NULL);
		if (n == 0)
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
	if (n == 0)
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
	if (n == 0)
	{ /* failed */
		DWORD err = ::GetLastError();
		msg.SetSize(0);
		bSuccess = FALSE;
	} /* failed */
	else
	{ /* success */
		msg.SetSize(n);
		n = ::WideCharToMultiByte(CP_UTF8, 0, wc.GetData(), -1, (LPSTR)msg.GetData(), n, NULL, NULL);
		if (n == 0)
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

	if (bSuccess)
		return ConvertStringToSendData(&msg);

	return "";
}

void CLogiFunc::FillSpeicalTruckChage()
{
	g_special_truck_charge.clear();

	int company_code, car_type;

	CMkRecordset rs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "special_truck_charge_select");
	pCmd.AddParameter(m_ci.m_nCompanyCode);

	if (rs.Execute(&pCmd)) {
		while (!rs.IsEOF()) {
			rs.GetFieldValue("company_code", company_code);
			rs.GetFieldValue("car_type", car_type);

			MAP_SPECIAL_TRUCK_CHARGE::iterator it = g_special_truck_charge.find(make_pair(company_code, car_type));

			if (it == g_special_truck_charge.end()) {
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

bool CLogiFunc::IsHangul(const char* text)
{
	bool hangul = true;

	for (int i = 0; i < strlen(text); i++) {
		if ((text[i] & 0x80) != 0x80)
			hangul = false;
	}

	return hangul;
}

bool CLogiFunc::IsEnglish(const char* text)
{
	for (int i = 0; i < (int)strlen(text); ++i) {
		if (isalpha(text[i]) <= 0 && text[i] != ' ')
			return false;
	}

	return true;
}

std::vector<CString> CLogiFunc::GetNeighboringCity(CString sido)
{
	std::vector<CString> vec;
	if (sido == "서울") {
		vec.push_back("서울");
		vec.push_back("경기");
		vec.push_back("인천");
	}
	else if (sido == "인천") {
		vec.push_back("인천");
		vec.push_back("서울");
		vec.push_back("경기");
	}
	else if (sido == "경기") {
		vec.push_back("경기");
		vec.push_back("서울");
		vec.push_back("인천");
	}
	else if (sido == "강원") {
		vec.push_back("강원");
	}
	else if (sido == "충북") {
		vec.push_back("충북");
		vec.push_back("세종");
		vec.push_back("대전");
		vec.push_back("충남");
	}
	else if (sido == "충남") {
		vec.push_back("충남");
		vec.push_back("세종");
		vec.push_back("대전");
		vec.push_back("충북");
	}
	else if (sido == "세종") {
		vec.push_back("세종");
		vec.push_back("대전");
		vec.push_back("충남");
		vec.push_back("충북");
	}
	else if (sido == "대전") {
		vec.push_back("대전");
		vec.push_back("세종");
		vec.push_back("충남");
		vec.push_back("충북");
	}
	else if (sido == "전남") {
		vec.push_back("전남");
		vec.push_back("광주");
		vec.push_back("전북");
	}
	else if (sido == "전북") {
		vec.push_back("전북");
		vec.push_back("광주");
		vec.push_back("전남");
	}
	else if (sido == "광주") {
		vec.push_back("광주");
		vec.push_back("전남");
		vec.push_back("전북");
	}
	else if (sido == "경북") {
		vec.push_back("경북");
		vec.push_back("대구");
		vec.push_back("울산");
		vec.push_back("경남");
		vec.push_back("부산");
	}
	else if (sido == "경남") {
		vec.push_back("경남");
		vec.push_back("대구");
		vec.push_back("부산");
		vec.push_back("울산");
		vec.push_back("경북");
	}
	else if (sido == "대구") {
		vec.push_back("대구");
		vec.push_back("경북");
		vec.push_back("경남");
		vec.push_back("울산");
		vec.push_back("부산");
	}
	else if (sido == "울산") {
		vec.push_back("울산");
		vec.push_back("부산");
		vec.push_back("경북");
		vec.push_back("경남");
		vec.push_back("대구");
	}
	else if (sido == "부산") {
		vec.push_back("부산");
		vec.push_back("경남");
		vec.push_back("울산");
		vec.push_back("대구");
		vec.push_back("경북");
	}
	else if (sido == "제주") {
		vec.push_back("제주");
	}

	return vec;
}

CString CLogiFunc::GetDashPhoneNumberRemoveDDD(CString strPhoneNumber)
{
	if (strPhoneNumber.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
		strPhoneNumber = strPhoneNumber.Right(strPhoneNumber.GetLength() - m_ci.m_strDDD.GetLength());

	return GetDashPhoneNumber(strPhoneNumber);
}

CString CLogiFunc::GetNoneDashNumberRemoveDDD(CString strPhoneNumber)
{
	CString strNumber = strPhoneNumber;
	strNumber.Remove('-');

	if (strNumber.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
		strNumber = strNumber.Right(strNumber.GetLength() - m_ci.m_strDDD.GetLength());

	return strNumber;
}