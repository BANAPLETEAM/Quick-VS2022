#include "StdAfx.h"
#include "ReceiptPrint.h"

CReceiptPrint::CReceiptPrint(void)
{
	m_bPrinterSetting = FALSE;
	m_phdcPrinter = NULL;
}

CReceiptPrint::~CReceiptPrint(void)
{
}


void CReceiptPrint::PrinterSetting()
{

	CPrintDialog Dlg(FALSE);
	if(Dlg.DoModal()!=IDOK)return;
	HDC hdc = Dlg.GetPrinterDC();
	CDC *pDC = CDC::FromHandle(hdc);
	CPrintDialog dlg(FALSE);
	dlg.GetDefaults();
	if(m_bPrinterSetting == NULL)
	{
		m_hdcPrinter = dlg.GetPrinterDC();
		//*m_phdcPrinter = dlg.GetPrinterDC();
		m_bPrinterSetting = TRUE;
	}
	else
	{
		m_hdcPrinter = dlg.GetPrinterDC();
	}
}

BOOL CReceiptPrint::IsPrinterSetting()
{
	return m_bPrinterSetting;
}

void CReceiptPrint::SetInputData(RECEIPT_INFO *pReceiptInfo)
{
	m_vecReceiptInfo.push_back(VEC_RECEIPT_INFO::value_type(pReceiptInfo));
}
void CReceiptPrint::Print()
{
	
	if(m_vecReceiptInfo.size() <= 0)
	{
		AfxMessageBox("프린트 할 데이터가 없습니다",  MB_ICONINFORMATION);
		return;
	}

	CDC dcPrinter;
	dcPrinter.Attach(m_hdcPrinter);

	// Call StartDoc() to begin printing.
	DOCINFO docinfo;
	memset(&docinfo, 0, sizeof(docinfo));
	docinfo.cbSize = sizeof(docinfo);
	docinfo.lpszDocName = _T("CDC::StartDoc() Code Fragment");

	// If it fails, complain and exit gracefully.
	if (dcPrinter.StartDoc(&docinfo) < 0)
	{
		AfxMessageBox(_T("Printer would not initalize"));
	}
	else
	{
		// Start a page.
		if (dcPrinter.StartPage() < 0)
		{
			AfxMessageBox(_T("Could not start page"));
			dcPrinter.AbortDoc();
		}
		else
		{
			CFont font;
			font.CreateFont(25,0,0,0,100,FALSE,FALSE,
				0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
				NULL,"돋움");

			
			RECT rt;
			SetRect(&rt,100,100,5000,7000);

			CGdiObject* pOldFont = dcPrinter.SelectStockObject(DEFAULT_PALETTE);   
			dcPrinter.SelectObject(&font);
			VEC_RECEIPT_INFO::iterator it;

			int i = 0;
			for(it = m_vecReceiptInfo.begin(); it != m_vecReceiptInfo.end(); ++ it)
			{

				if(i != 0)
					dcPrinter.StartPage();

				InnerPrintText(dcPrinter, *it);
				dcPrinter.EndPage();
				i++;
			}		


			dcPrinter.EndDoc();
			//dcPrinter.SelectObject(pOldFont);
			dcPrinter.Detach();
			//dcPrinter.DeleteDC();
			
			
			
			//dcPrinter.DeleteDC();
			dcPrinter.ReleaseOutputDC();
		}
	}
	AfxMessageBox("출력하였습니다." );
	if(m_vecReceiptInfo.size() > 0)
	{
		VEC_RECEIPT_INFO::iterator it;
		int i = 0;
		for(it = m_vecReceiptInfo.begin(); it != m_vecReceiptInfo.end(); ++ it)
		{		
			if(*it)
				delete (*it);			
		}		
		m_vecReceiptInfo.clear();
	}

}

void CReceiptPrint::InnerPrintText(CDC &dcPrint, RECEIPT_INFO *pReceiptInfo)
{
	RECT rt;
	//SetRect(&rt,0,0,5000,7000);
	SetRect(&rt,0,-100,5000,6800);

	/*CFont font;
	font.CreateFont(20,0,0,0,100,FALSE,FALSE,
		0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		NULL,"돋움");

	CFont font2;
	font.CreateFont(10,0,0,0,100,FALSE,FALSE,
		0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		NULL,"돋움");

	dcPrint.SelectObject(&font);*/


	CString sTNo =""; sTNo.Format("No.%ld", pReceiptInfo->nTNo);


	dcPrint.ExtTextOut(980,0,ETO_CLIPPED, &rt, pReceiptInfo->sDate, pReceiptInfo->sDate.GetLength(),NULL );
	dcPrint.ExtTextOut(1200,0,ETO_CLIPPED, &rt, sTNo, sTNo.GetLength(),NULL );

	dcPrint.ExtTextOut(260,	42,ETO_CLIPPED, &rt, pReceiptInfo->sCompany, pReceiptInfo->sCompany.GetLength(),NULL );
	dcPrint.ExtTextOut(670,	42,ETO_CLIPPED, &rt, GetDashPhoneNumber(pReceiptInfo->sTel), GetDashPhoneNumber(pReceiptInfo->sTel).GetLength(),NULL );
	dcPrint.ExtTextOut(1230,42,ETO_CLIPPED, &rt, GetMyNumberFormat(pReceiptInfo->nBasicCharge), GetMyNumberFormat(pReceiptInfo->nBasicCharge).GetLength(),NULL );	

	//부서
	dcPrint.ExtTextOut(260,92,ETO_CLIPPED, &rt, pReceiptInfo->sDept, pReceiptInfo->sDept.GetLength(),NULL );
	dcPrint.ExtTextOut(670,92,ETO_CLIPPED, &rt, pReceiptInfo->sName, pReceiptInfo->sName.GetLength(),NULL );
	dcPrint.ExtTextOut(1230,92,ETO_CLIPPED, &rt, GetMyNumberFormat(pReceiptInfo->nAddCharge), GetMyNumberFormat(pReceiptInfo->nAddCharge).GetLength(),NULL );

	//지명
	dcPrint.ExtTextOut(260,	132,ETO_CLIPPED, &rt, pReceiptInfo->sDestDong, pReceiptInfo->sDestDong.GetLength(),NULL );
	dcPrint.ExtTextOut(670,	132,ETO_CLIPPED, &rt, pReceiptInfo->sCarNameAndChargeType, pReceiptInfo->sCarNameAndChargeType.GetLength(),NULL );
	//dcPrint.ExtTextOut(1055,	145,ETO_CLIPPED, &rt, "0", 1,NULL );

	//상호
	dcPrint.ExtTextOut(260,	181,ETO_CLIPPED, &rt, pReceiptInfo->sDestCompany, pReceiptInfo->sDestCompany.GetLength(),NULL );
	dcPrint.ExtTextOut(670,	181,ETO_CLIPPED, &rt, GetDashPhoneNumber(pReceiptInfo->sDestTel), GetDashPhoneNumber(pReceiptInfo->sDestTel).GetLength(),NULL );
	if(pReceiptInfo->nTransCharge > 0)
		dcPrint.ExtTextOut(1230,181,ETO_CLIPPED, &rt, GetMyNumberFormat(pReceiptInfo->nTransCharge), GetMyNumberFormat(pReceiptInfo->nTransCharge).GetLength(),NULL );
	
    // 부서
	dcPrint.ExtTextOut(260,	220,ETO_CLIPPED, &rt, pReceiptInfo->sDestDept, pReceiptInfo->sDestDept.GetLength(),NULL );
	dcPrint.ExtTextOut(670,	220,ETO_CLIPPED, &rt, pReceiptInfo->sDestName, pReceiptInfo->sDestName.GetLength(),NULL );
	dcPrint.ExtTextOut(1230,220,ETO_CLIPPED, &rt, GetMyNumberFormat(pReceiptInfo->nTotalCharge), GetMyNumberFormat(pReceiptInfo->nTotalCharge).GetLength(),NULL );

	dcPrint.ExtTextOut(310,	265,ETO_CLIPPED, &rt, GetMyNumberFormat(pReceiptInfo->nRNo), GetMyNumberFormat(pReceiptInfo->nRNo).GetLength(),NULL );
	dcPrint.ExtTextOut(670,	265,ETO_CLIPPED, &rt, pReceiptInfo->sRName, pReceiptInfo->sRName.GetLength(),NULL );

	/*dcPrint.SelectObject(&font2);*/
	if(pReceiptInfo->sStartDetail.GetSize() > 0)
	{
		for(int i = 0; i <pReceiptInfo->sStartDetail.GetSize(); i++ )
		{
			dcPrint.ExtTextOut(160,	450 + (50 * i ) ,ETO_CLIPPED, &rt, pReceiptInfo->sStartDetail.GetAt(i), pReceiptInfo->sStartDetail.GetAt(i).GetLength(),NULL );
		}
	}

	//if(pReceiptInfo->sStartDetail.GetLength() > 400)
	//{
	//	CString sDetail1, sDetail2;
	//	sDetail1 = pReceiptInfo->sStartDetail.Left(400);
	//	sDetail2 = pReceiptInfo->sStartDetail.Mid(400,pReceiptInfo->sStartDetail.GetLength() );
	//	dcPrint.ExtTextOut(130,	430,ETO_CLIPPED, &rt, sDetail1, sDetail1.GetLength(),NULL );
	//	dcPrint.ExtTextOut(130,	480,ETO_CLIPPED, &rt, sDetail2, sDetail2.GetLength(),NULL );
	//}
	//else
	//	dcPrint.ExtTextOut(130,	430,ETO_CLIPPED, &rt, pReceiptInfo->sStartDetail, pReceiptInfo->sStartDetail.GetLength(),NULL );
}

/*

dcPrint.ExtTextOut(980,	10,ETO_CLIPPED, &rt, pReceiptInfo->sDate, pReceiptInfo->sDate.GetLength(),NULL );
dcPrint.ExtTextOut(1180,10,ETO_CLIPPED, &rt, sTNo, sTNo.GetLength(),NULL );

dcPrint.ExtTextOut(239,	52,ETO_CLIPPED, &rt, pReceiptInfo->sCompany, pReceiptInfo->sCompany.GetLength(),NULL );
dcPrint.ExtTextOut(649,	52,ETO_CLIPPED, &rt, GetDashPhoneNumber(pReceiptInfo->sTel), GetDashPhoneNumber(pReceiptInfo->sTel).GetLength(),NULL );
dcPrint.ExtTextOut(1210,52,ETO_CLIPPED, &rt, GetMyNumberFormat(pReceiptInfo->nBasicCharge), GetMyNumberFormat(pReceiptInfo->nBasicCharge).GetLength(),NULL );	

dcPrint.ExtTextOut(239,102,ETO_CLIPPED, &rt, pReceiptInfo->sDept, pReceiptInfo->sDept.GetLength(),NULL );
dcPrint.ExtTextOut(649,102,ETO_CLIPPED, &rt, pReceiptInfo->sName, pReceiptInfo->sName.GetLength(),NULL );
dcPrint.ExtTextOut(1210,102,ETO_CLIPPED, &rt, GetMyNumberFormat(pReceiptInfo->nAddCharge), GetMyNumberFormat(pReceiptInfo->nAddCharge).GetLength(),NULL );

dcPrint.ExtTextOut(239,	142,ETO_CLIPPED, &rt, pReceiptInfo->sDestDong, pReceiptInfo->sDestDong.GetLength(),NULL );
dcPrint.ExtTextOut(649,	142,ETO_CLIPPED, &rt, pReceiptInfo->sCarNameAndChargeType, pReceiptInfo->sCarNameAndChargeType.GetLength(),NULL );
//dcPrint.ExtTextOut(1055,	145,ETO_CLIPPED, &rt, "0", 1,NULL );


dcPrint.ExtTextOut(239,	191,ETO_CLIPPED, &rt, pReceiptInfo->sDestCompany, pReceiptInfo->sDestCompany.GetLength(),NULL );
dcPrint.ExtTextOut(649,	191,ETO_CLIPPED, &rt, GetDashPhoneNumber(pReceiptInfo->sDestTel), GetDashPhoneNumber(pReceiptInfo->sDestTel).GetLength(),NULL );
if(pReceiptInfo->nTransCharge > 0)
dcPrint.ExtTextOut(1210,191,ETO_CLIPPED, &rt, GetMyNumberFormat(pReceiptInfo->nTransCharge), GetMyNumberFormat(pReceiptInfo->nTransCharge).GetLength(),NULL );


dcPrint.ExtTextOut(239,	230,ETO_CLIPPED, &rt, pReceiptInfo->sDestDept, pReceiptInfo->sDestDept.GetLength(),NULL );
dcPrint.ExtTextOut(649,	230,ETO_CLIPPED, &rt, pReceiptInfo->sDestName, pReceiptInfo->sDestName.GetLength(),NULL );
dcPrint.ExtTextOut(1210,230,ETO_CLIPPED, &rt, GetMyNumberFormat(pReceiptInfo->nTotalCharge), GetMyNumberFormat(pReceiptInfo->nTotalCharge).GetLength(),NULL );

dcPrint.ExtTextOut(290,	275,ETO_CLIPPED, &rt, GetMyNumberFormat(pReceiptInfo->nRNo), GetMyNumberFormat(pReceiptInfo->nRNo).GetLength(),NULL );
dcPrint.ExtTextOut(649,	275,ETO_CLIPPED, &rt, pReceiptInfo->sRName, pReceiptInfo->sRName.GetLength(),NULL );


if(pReceiptInfo->sStartDetail.GetSize() > 0)
{
	for(int i = 0; i <pReceiptInfo->sStartDetail.GetSize(); i++ )
	{
		dcPrint.ExtTextOut(140,	460 + (50 * i ) ,ETO_CLIPPED, &rt, pReceiptInfo->sStartDetail.GetAt(i), pReceiptInfo->sStartDetail.GetAt(i).GetLength(),NULL );
	}
}





dcPrint.ExtTextOut(970,	0,ETO_CLIPPED, &rt, pReceiptInfo->sDate, pReceiptInfo->sDate.GetLength(),NULL );
dcPrint.ExtTextOut(1170,	0,ETO_CLIPPED, &rt, sTNo, sTNo.GetLength(),NULL );

dcPrint.ExtTextOut(229,	42,ETO_CLIPPED, &rt, pReceiptInfo->sCompany, pReceiptInfo->sCompany.GetLength(),NULL );
dcPrint.ExtTextOut(639,	42,ETO_CLIPPED, &rt, GetDashPhoneNumber(pReceiptInfo->sTel), GetDashPhoneNumber(pReceiptInfo->sTel).GetLength(),NULL );
dcPrint.ExtTextOut(1200,	42,ETO_CLIPPED, &rt, GetMyNumberFormat(pReceiptInfo->nBasicCharge), GetMyNumberFormat(pReceiptInfo->nBasicCharge).GetLength(),NULL );
//dcPrint.ExtTextOut(1055,	42,ETO_CLIPPED, &rt, GetMyNumberFormat(pReceiptInfo->nBasicCharge), GetMyNumberFormat(pReceiptInfo->nBasicCharge).GetLength(),NULL );

dcPrint.ExtTextOut(229,	92,ETO_CLIPPED, &rt, pReceiptInfo->sDept, pReceiptInfo->sDept.GetLength(),NULL );
dcPrint.ExtTextOut(639,	92,ETO_CLIPPED, &rt, pReceiptInfo->sName, pReceiptInfo->sName.GetLength(),NULL );
dcPrint.ExtTextOut(1200,	92,ETO_CLIPPED, &rt, GetMyNumberFormat(pReceiptInfo->nAddCharge), GetMyNumberFormat(pReceiptInfo->nAddCharge).GetLength(),NULL );

dcPrint.ExtTextOut(229,	132,ETO_CLIPPED, &rt, pReceiptInfo->sDestDong, pReceiptInfo->sDestDong.GetLength(),NULL );
dcPrint.ExtTextOut(639,	132,ETO_CLIPPED, &rt, pReceiptInfo->sCarNameAndChargeType, pReceiptInfo->sCarNameAndChargeType.GetLength(),NULL );
//dcPrint.ExtTextOut(1055,	145,ETO_CLIPPED, &rt, "0", 1,NULL );


dcPrint.ExtTextOut(229,	181,ETO_CLIPPED, &rt, pReceiptInfo->sDestCompany, pReceiptInfo->sDestCompany.GetLength(),NULL );
dcPrint.ExtTextOut(639,	181,ETO_CLIPPED, &rt, GetDashPhoneNumber(pReceiptInfo->sDestTel), GetDashPhoneNumber(pReceiptInfo->sDestTel).GetLength(),NULL );
if(pReceiptInfo->nTransCharge > 0)
dcPrint.ExtTextOut(1200,	181,ETO_CLIPPED, &rt, GetMyNumberFormat(pReceiptInfo->nTransCharge), GetMyNumberFormat(pReceiptInfo->nTransCharge).GetLength(),NULL );


dcPrint.ExtTextOut(229,	220,ETO_CLIPPED, &rt, pReceiptInfo->sDestDept, pReceiptInfo->sDestDept.GetLength(),NULL );
dcPrint.ExtTextOut(639,	220,ETO_CLIPPED, &rt, pReceiptInfo->sDestName, pReceiptInfo->sDestName.GetLength(),NULL );
dcPrint.ExtTextOut(1200,	220,ETO_CLIPPED, &rt, GetMyNumberFormat(pReceiptInfo->nTotalCharge), GetMyNumberFormat(pReceiptInfo->nTotalCharge).GetLength(),NULL );

dcPrint.ExtTextOut(280,	265,ETO_CLIPPED, &rt, GetMyNumberFormat(pReceiptInfo->nRNo), GetMyNumberFormat(pReceiptInfo->nRNo).GetLength(),NULL );
dcPrint.ExtTextOut(639,	265,ETO_CLIPPED, &rt, pReceiptInfo->sRName, pReceiptInfo->sRName.GetLength(),NULL );


if(pReceiptInfo->sStartDetail.GetSize() > 0)
{
	for(int i = 0; i <pReceiptInfo->sStartDetail.GetSize(); i++ )
	{
		dcPrint.ExtTextOut(130,	450 + (50 * i ) ,ETO_CLIPPED, &rt, pReceiptInfo->sStartDetail.GetAt(i), pReceiptInfo->sStartDetail.GetAt(i).GetLength(),NULL );
	}
}



*/


/*
dcPrinter.TextOut(350, 350, _T("Text out"), 12);
DrawText(dcPrinter, strPrint, -1, &rt, DT_WORDBREAK);
//	dcPrinter.
CString sDestCompany = "로지소프트";
CString sTel = "1599-0707";
CString sEtc = "If nOptions is 0 and lpRect is NULL, the function writes text to the device context without using a rectangular region. By default, the current position is not used or ";
dcPrinter.ExtTextOut(150, 150, ETO_CLIPPED  , &rt,sDestCompany, sDestCompany.GetLength(),NULL );
dcPrinter.ExtTextOut(250, 150, ETO_CLIPPED  , &rt,sTel, sTel.GetLength(),NULL );
dcPrinter.ExtTextOut(150, 350, ETO_CLIPPED  , &rt,sEtc, sEtc.GetLength(),NULL );

dcPrinter.EndPage();

dcPrinter.StartPage();

dcPrinter.TextOut(350, 350, _T("Text out"), 12);
DrawText(dcPrinter, strPrint, -1, &rt, DT_WORDBREAK);
//	dcPrinter.
sDestCompany = "2로지소프트";
sTel = "2_1599-0707";
sEtc = "2If nOptions is 0 and lpRect is NULL, the function writes text to the device context without using a rectangular region. By default, the current position is not used or ";
dcPrinter.ExtTextOut(150, 150, ETO_CLIPPED  , &rt,sDestCompany, sDestCompany.GetLength(),NULL );
dcPrinter.ExtTextOut(250, 150, ETO_CLIPPED  , &rt,sTel, sTel.GetLength(),NULL );
dcPrinter.ExtTextOut(150, 350, ETO_CLIPPED  , &rt,sEtc, sEtc.GetLength(),NULL );
*/