// MyReportControl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MyReportControl.h"

// CMyReportControl

IMPLEMENT_DYNAMIC(CMyReportControl, CXTPGridControl)
CMyReportControl::CMyReportControl()
{
	m_nColumnCount = MAX_COLUMN;
	m_bShowRiderInfo = FALSE;
	m_bShowCustomerInfo = FALSE;
	m_bShowShareOrder = FALSE;	
}

CMyReportControl::~CMyReportControl()
{
}


BEGIN_MESSAGE_MAP(CMyReportControl, CXTPGridControl)
END_MESSAGE_MAP()



// CMyReportControl 메시지 처리기입니다.

void CMyReportControl::LoadListInfo()
{
	try {
		int *buffer;

		UINT pBytes = sizeof(buffer);
		CWinApp *app = (CWinApp*) AfxGetApp();
		if(!app->GetProfileBinary("control", "rcp_list2", (LPBYTE*)&buffer, &pBytes))
			throw "rcp_list2";

		int nItemSize = sizeof(m_nHWidth) + sizeof(m_nHOrder) + sizeof(m_nColumnCount);
		if(pBytes != (nItemSize + sizeof(int))) throw "size not match";
		int nSum = CheckSum((void*)buffer, nItemSize);
		if(nSum != (int)buffer[nItemSize / sizeof(int)]) throw "check sum error";	

		memcpy((void*)&m_nHWidth, (void*)buffer, sizeof(m_nHWidth));
		memcpy((void*)&m_nHOrder, (void*)&buffer[sizeof(m_nHWidth) / sizeof(int)], sizeof(m_nHOrder));
		memcpy((void*)&m_nColumnCount, (void*)&buffer[(sizeof(m_nHWidth) + sizeof(m_nHOrder)) / sizeof(int)], sizeof(int));

	} catch(char *szMsg) {
		g_bana_log->Print("CMyReportControl:%s\n", szMsg);
		m_nColumnCount = MAX_COLUMN;	
		for(int i = 0; i < MAX_COLUMN; i++)	{
			m_nHWidth[i] = header_width[i];		
			m_nHOrder[i] = i;
		}
	}
}

void CMyReportControl::SaveListInfo()
{
	int buffer[100];
	int nBytes = sizeof(m_nHWidth) + sizeof(m_nHOrder) + sizeof(m_nColumnCount);

	int nColCount =  GetColumns()->GetCount();

	for(int i=0;i < nColCount;i++) 
		m_nHWidth[m_nHOrder[i]] = GetColumns()->GetAt(i)->GetWidth();

	memcpy((void*)&buffer, (void*)&m_nHWidth, sizeof(m_nHWidth));
	memcpy((void*)&buffer[sizeof(m_nHWidth) / sizeof(int)], (void*)&m_nHOrder, sizeof(m_nHOrder));
	memcpy((void*)&buffer[(sizeof(m_nHWidth) + sizeof(m_nHOrder)) / sizeof(int)], (void*)&m_nColumnCount, sizeof(int));
	int nCheckSum = CheckSum((void*)&buffer, nBytes);
	memcpy((void*)&buffer[nBytes / sizeof(int)], (void*)&nCheckSum, sizeof(int));

	nBytes += sizeof(int);

	CWinApp *app = (CWinApp*) AfxGetApp();
	app->WriteProfileBinary("control", "rcp_list2", (LPBYTE)&buffer, nBytes);
}

void CMyReportControl::SetSelectedColor(COLORREF clrSelected)
{
	CXTPGridPaintManager *pPaint = (CXTPGridPaintManager*)GetPaintManager();
	pPaint->m_clrSelectedRow.SetCustomValue(clrSelected);
	pPaint->m_clrSelectedRow.SetStandardValue(clrSelected);
	pPaint->m_clrHighlight.SetCustomValue(clrSelected);
	pPaint->m_clrHighlight.SetStandardValue(clrSelected);

	//by mksong (2011-09-14 오후 1:14), 선택행의 글자색에 반전색 적용함
	COLORREF crInverted = RGB(
		(255 - GetRValue(clrSelected)), 
		(255 - GetGValue(clrSelected)), 
		(255 - GetBValue(clrSelected)));

	pPaint->m_clrSelectedRowText.SetCustomValue(crInverted);
	pPaint->m_clrSelectedRowText.SetStandardValue(crInverted);
	pPaint->m_clrHighlightText.SetCustomValue(crInverted);
	pPaint->m_clrHighlightText.SetStandardValue(crInverted);
}

void CMyReportControl::GetSortCol(int *nCol, BOOL *bAsc)
{
	*nCol = 1;
	*bAsc = TRUE;

	CXTPGridColumns* pColumns = GetColumns();

	// create arrange by items
	CMenu menuArrange;
	VERIFY(menuArrange.CreatePopupMenu());
	int nColumnCount = pColumns->GetCount();
	for (int nColumn = 0; nColumn < nColumnCount; nColumn++)
	{
		CXTPGridColumn* pCol = pColumns->GetAt(nColumn);
		if(pCol->IsSorted())
		{
			*nCol = pCol->GetItemIndex();
			*bAsc = pCol->IsSortedIncreasing();
		}
	}
}

void CMyReportControl::OnDraw(CDC* pDC)
{
	CXTPGridControl::OnDraw(pDC);

	if(m_bShowRiderInfo)
		DrawRiderInfo(pDC);
	else if(m_bShowCustomerInfo)
		DrawCustomerInfo(pDC);
	else if(m_bShowShareOrder)
		DrawShareOrder(pDC);
}

void CMyReportControl::DrawRiderInfo(CDC *pDC)
{
	CXTPPenDC pen(*pDC, RGB(0, 255, 0));
	CXTPFontDC font(pDC, &GetPaintManager()->m_fontBoldText);

	CRect rc;
	GetClientRect(rc);
	rc.left += 10;
	rc.right = rc.left + 600;
	rc.bottom -= 5;
	rc.top = rc.bottom - 15;
	DrawInfoBox(pDC, rc, TRUE);
	//	rc.DeflateRect(5, 5, 5, 5);
	//	PrintLine(pDC, rc, "고객전화", m_bConfirmCall ? 
	//			CString("확인전화/") + m_strRecvCID : CString("신규전화/") + m_strRecvCID);
	//	font.SetFont(&m_fontLarge);
	//	PrintLine(pDC, rc, "", m_strCurBranch, TRUE);
	//	PrintLine(pDC, rc, "", "", TRUE);
	//	font.SetFont(&GetPaintManager()->m_fontText);
	PrintLine(pDC, rc, m_strRecvCID + " 기사의 오더 내용만 표시중, 검색버튼 누르시면 전체를 볼수있습니다.", "", FALSE, RGB(255, 255, 255));


/*
	CXTPPenDC pen(*pDC, RGB(0, 0, 255));
	CXTPFontDC font(pDC, &GetPaintManager()->m_fontBoldText);

	CRect rc;
	GetClientRect(rc);
	rc.left += 10;
	rc.right = rc.left + 200;
	rc.top += 310;
	rc.bottom -= 5;
	DrawInfoBox(pDC, rc);
	rc.DeflateRect(5, 5, 5, 5);
	PrintLine(pDC, rc, "회사명", m_strCompany);
	PrintLine(pDC, rc, "지사명", m_strBranch);
	PrintLine(pDC, rc, "☏", m_strCompanyPhone + "/" + m_strOfficePhone, TRUE);
	PrintLine(pDC, rc, "기사명", m_strRName);
	PrintLine(pDC, rc, "단말ID", m_strDeviceID);
	PrintLine(pDC, rc, "단말기종", m_strDeviceType);
	PrintLine(pDC, rc, "단말버전", m_strDeviceVer, TRUE);
	PrintLine(pDC, rc, "휴대폰", m_strPhone);
	PrintLine(pDC, rc, "집전화", m_strHomePhone);
	PrintLine(pDC, rc, "입사일", m_strEnterDate);


	GetClientRect(rc);
	rc.left += 220;
	rc.right = rc.left + 200;
	rc.top += 310;
	rc.bottom -= 5;
	DrawInfoBox(pDC, rc);
	rc.DeflateRect(5, 5, 5, 5);
	PrintLine(pDC, rc, "입금방식", m_strDepositType);
	PrintLine(pDC, rc, "금일수입", m_strTodayIncome, FALSE, RGB(200, 0, 0));
	PrintLine(pDC, rc, "잔  액", m_strBalance, FALSE, RGB(200, 0, 0));
	PrintLine(pDC, rc, "금일충전", m_strTodayCharge, TRUE, RGB(200, 0, 0));
	PrintLine(pDC, rc, "업무상태", m_strWorkState);
	PrintLine(pDC, rc, "건수제한", m_strCountLimit);
	PrintLine(pDC, rc, "시간제한", m_strTimeLimit, TRUE);
	PrintDualLine(pDC, rc, "보험정보", m_strInsInfo);
	PrintLine(pDC, rc, "보험만료", m_strInsExpDate);

	if(m_strHistory.GetLength() > 0)
	{
		GetClientRect(rc);
		rc.left += 430;
		rc.right = rc.left + 530;
		rc.top += 310;
		rc.bottom -= 5;
		DrawInfoBox(pDC, rc);
		rc.DeflateRect(5, 5, 5, 5);
		PrintLine(pDC, rc, "과거이력", "");
		PrintLine(pDC, rc, "", "");
		font.SetFont(&GetPaintManager()->m_fontText);
		PrintLine(pDC, rc, m_strHistory, "", FALSE, RGB(255, 255, 255));
		PrintLine(pDC, rc, "", "");
		PrintLine(pDC, rc, "", "");
		PrintLine(pDC, rc, "", "");
		PrintLine(pDC, rc, "", "검색버튼 누르시면 기사정보가 사라집니다.", FALSE, RGB(255, 255, 255));
		PrintLine(pDC, rc, "", "다시보시려면 F8키 누르시기 바랍니다.", FALSE, RGB(255, 255, 255));
	}
*/
}

void CMyReportControl::DrawShareOrder(CDC *pDC)
{
	CXTPPenDC pen(*pDC, RGB(0, 255, 0));
	CXTPFontDC font(pDC, &GetPaintManager()->m_fontBoldText);

	CRect rc;
	GetClientRect(rc);
	rc.left += 10;
	rc.right = rc.left + 600;
	rc.bottom -= 5;
	rc.top = rc.bottom - 15;
	DrawInfoBox(pDC, rc, TRUE);
	PrintLine(pDC, rc, " 공유콜만 검색중입니다.", "", FALSE, RGB(255, 255, 255));
}


void CMyReportControl::DrawInfoBox(CDC *pDC, CRect rc, BOOL bGreen)
{
	pDC->FillSolidRect(rc.left, rc.top, rc.Width(), rc.Height(), 
			bGreen ? RGB(119, 185, 147) : RGB(119, 147, 185)); 

	for (int i = rc.top + 1; i < rc.bottom; i+= 3)
	{
		pDC->FillSolidRect(rc.left, i, rc.Width(), 1, 
			XTPDrawHelpers()->BlendColors(
				bGreen ? RGB(122, 187, 149) : RGB(122, 149, 187), 
				bGreen ? RGB(74, 165, 111) : RGB(74, 111, 165), 
			(float)(1.0 - ((i - rc.top)) / (float)rc.Height())));
	}
}


void CMyReportControl::PrintLine(CDC *pDC, CRect &rc, CString strTitle, CString strText, 
									BOOL bNextSeparator, COLORREF clrText)
{
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->DrawText(strTitle, rc, DT_LEFT);
	pDC->SetTextColor(clrText);
	pDC->DrawText(strText, rc, DT_RIGHT);
	if(bNextSeparator)
		rc.top += 20;
	else
		rc.top += 15;
}

void CMyReportControl::PrintDualLine(CDC *pDC, CRect &rc, CString strTitle, CString strText, 
								 BOOL bNextSeparator, COLORREF clrText)
{
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->DrawText(strTitle, rc, DT_LEFT);
	rc.top += 13;
	pDC->SetTextColor(clrText);
	pDC->DrawText(strText, rc, DT_LEFT);
	if(bNextSeparator)
		rc.top += 20;
	else
		rc.top += 15;
}

void CMyReportControl::ShowRiderInfo(BOOL bShow)
{ 
	m_bShowRiderInfo = bShow; 
	Invalidate();
}


void CMyReportControl::ShowCustomerInfo(BOOL bShow)
{
	m_bShowCustomerInfo = bShow;
	Invalidate();
}

void CMyReportControl::ShowShareOrder(BOOL bShow)
{
	m_bShowShareOrder = bShow;
	Invalidate();
}

void CMyReportControl::DrawCustomerInfo(CDC *pDC)
{
	CXTPPenDC pen(*pDC, RGB(0, 255, 0));
	CXTPFontDC font(pDC, &GetPaintManager()->m_fontBoldText);

	CRect rc;
	GetClientRect(rc);
	rc.left += 10;
	rc.right = rc.left + 600;
	rc.bottom -= 5;
	rc.top = rc.bottom - 15;
	DrawInfoBox(pDC, rc, TRUE);
//	rc.DeflateRect(5, 5, 5, 5);
//	PrintLine(pDC, rc, "고객전화", m_bConfirmCall ? 
//			CString("확인전화/") + m_strRecvCID : CString("신규전화/") + m_strRecvCID);
//	font.SetFont(&m_fontLarge);
//	PrintLine(pDC, rc, "", m_strCurBranch, TRUE);
//	PrintLine(pDC, rc, "", "", TRUE);
//	font.SetFont(&GetPaintManager()->m_fontText);
	PrintLine(pDC, rc, m_strRecvCID + " 고객의 오더 내용만 표시중, 검색버튼 누르시면 전체를 볼수있습니다.", "", FALSE, RGB(255, 255, 255));
}







