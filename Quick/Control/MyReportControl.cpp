// MyReportControl.cpp : ���� �����Դϴ�.
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



// CMyReportControl �޽��� ó�����Դϴ�.

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

	//by mksong (2011-09-14 ���� 1:14), �������� ���ڻ��� ������ ������
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
	//	PrintLine(pDC, rc, "����ȭ", m_bConfirmCall ? 
	//			CString("Ȯ����ȭ/") + m_strRecvCID : CString("�ű���ȭ/") + m_strRecvCID);
	//	font.SetFont(&m_fontLarge);
	//	PrintLine(pDC, rc, "", m_strCurBranch, TRUE);
	//	PrintLine(pDC, rc, "", "", TRUE);
	//	font.SetFont(&GetPaintManager()->m_fontText);
	PrintLine(pDC, rc, m_strRecvCID + " ����� ���� ���븸 ǥ����, �˻���ư �����ø� ��ü�� �����ֽ��ϴ�.", "", FALSE, RGB(255, 255, 255));


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
	PrintLine(pDC, rc, "ȸ���", m_strCompany);
	PrintLine(pDC, rc, "�����", m_strBranch);
	PrintLine(pDC, rc, "��", m_strCompanyPhone + "/" + m_strOfficePhone, TRUE);
	PrintLine(pDC, rc, "����", m_strRName);
	PrintLine(pDC, rc, "�ܸ�ID", m_strDeviceID);
	PrintLine(pDC, rc, "�ܸ�����", m_strDeviceType);
	PrintLine(pDC, rc, "�ܸ�����", m_strDeviceVer, TRUE);
	PrintLine(pDC, rc, "�޴���", m_strPhone);
	PrintLine(pDC, rc, "����ȭ", m_strHomePhone);
	PrintLine(pDC, rc, "�Ի���", m_strEnterDate);


	GetClientRect(rc);
	rc.left += 220;
	rc.right = rc.left + 200;
	rc.top += 310;
	rc.bottom -= 5;
	DrawInfoBox(pDC, rc);
	rc.DeflateRect(5, 5, 5, 5);
	PrintLine(pDC, rc, "�Աݹ��", m_strDepositType);
	PrintLine(pDC, rc, "���ϼ���", m_strTodayIncome, FALSE, RGB(200, 0, 0));
	PrintLine(pDC, rc, "��  ��", m_strBalance, FALSE, RGB(200, 0, 0));
	PrintLine(pDC, rc, "��������", m_strTodayCharge, TRUE, RGB(200, 0, 0));
	PrintLine(pDC, rc, "��������", m_strWorkState);
	PrintLine(pDC, rc, "�Ǽ�����", m_strCountLimit);
	PrintLine(pDC, rc, "�ð�����", m_strTimeLimit, TRUE);
	PrintDualLine(pDC, rc, "��������", m_strInsInfo);
	PrintLine(pDC, rc, "���踸��", m_strInsExpDate);

	if(m_strHistory.GetLength() > 0)
	{
		GetClientRect(rc);
		rc.left += 430;
		rc.right = rc.left + 530;
		rc.top += 310;
		rc.bottom -= 5;
		DrawInfoBox(pDC, rc);
		rc.DeflateRect(5, 5, 5, 5);
		PrintLine(pDC, rc, "�����̷�", "");
		PrintLine(pDC, rc, "", "");
		font.SetFont(&GetPaintManager()->m_fontText);
		PrintLine(pDC, rc, m_strHistory, "", FALSE, RGB(255, 255, 255));
		PrintLine(pDC, rc, "", "");
		PrintLine(pDC, rc, "", "");
		PrintLine(pDC, rc, "", "");
		PrintLine(pDC, rc, "", "�˻���ư �����ø� ��������� ������ϴ�.", FALSE, RGB(255, 255, 255));
		PrintLine(pDC, rc, "", "�ٽú��÷��� F8Ű �����ñ� �ٶ��ϴ�.", FALSE, RGB(255, 255, 255));
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
	PrintLine(pDC, rc, " �����ݸ� �˻����Դϴ�.", "", FALSE, RGB(255, 255, 255));
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
//	PrintLine(pDC, rc, "����ȭ", m_bConfirmCall ? 
//			CString("Ȯ����ȭ/") + m_strRecvCID : CString("�ű���ȭ/") + m_strRecvCID);
//	font.SetFont(&m_fontLarge);
//	PrintLine(pDC, rc, "", m_strCurBranch, TRUE);
//	PrintLine(pDC, rc, "", "", TRUE);
//	font.SetFont(&GetPaintManager()->m_fontText);
	PrintLine(pDC, rc, m_strRecvCID + " ���� ���� ���븸 ǥ����, �˻���ư �����ø� ��ü�� �����ֽ��ϴ�.", "", FALSE, RGB(255, 255, 255));
}







