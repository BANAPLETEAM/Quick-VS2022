#include "stdafx.h"
#include "quick.h"
#include "LogiFunc.h"

//DWORD CLogiFunc::m_dwLastInput = GetTickCount();
//CArray<MONITORINFOEX, MONITORINFOEX> CLogiFunc::m_aryMonitors;


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



CString CLogiFunc::GetMyNumberFormat(long nNumber)
{
	CString strNumber;
	strNumber.Format("%d", nNumber);
	return GetMyNumberFormat(strNumber);
}

BOOL CLogiFunc::IsStringDigit(CString &strText)
{
	for(int i = 0; i < strText.GetLength() ; i++) 
		if(!isdigit((::byte)strText.GetAt(i))) 
			return FALSE;
	return TRUE;
}

BOOL CLogiFunc::IsPhoneNumber(CString &strText)
{
	for(int i = 0; i < strText.GetLength() ; i++) {
		if((::byte)strText.GetAt(i) != '-' && !isdigit((::byte)strText.GetAt(i))) {
			return FALSE;
		}
	}
	return TRUE;
}
CString CLogiFunc::GetNoneDashNumber(CString strPhoneNumber)
{
	strPhoneNumber.Remove('-');
	return strPhoneNumber;
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