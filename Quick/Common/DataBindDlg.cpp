// DataBindDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "DataBindDlg.h"
#include "MyReportPaintManager.h"

// CDataBindDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDataBindDlg, CMyResizeDialog)

CDataBindDlg::CDataBindDlg(CString strTitle, CString strProc, CMkParameter *pPar1,
						   CMkParameter *pPar2, CMkParameter *pPar3,
						   CMkParameter *pPar4, CMkParameter *pPar5,
						   CMkParameter *pPar6, CMkParameter *pPar7,
						   CMkParameter *pPar8, CMkParameter *pPar9,
						   CMkParameter *pPar10)
						   : CMyResizeDialog(CDataBindDlg::IDD, NULL)
{
	m_strTitle = strTitle;
	m_strProc = strProc;

	m_pParameter[0] = pPar1;
	m_pParameter[1] = pPar2;
	m_pParameter[2] = pPar3;
	m_pParameter[3] = pPar4;
	m_pParameter[4] = pPar5;
	m_pParameter[5] = pPar6;
	m_pParameter[6] = pPar7;
	m_pParameter[7] = pPar8;
	m_pParameter[8] = pPar9;
	m_pParameter[9] = pPar10;

	m_nHeight = 0;
	m_nWidth = 0;
}

CDataBindDlg::~CDataBindDlg()
{
	for(int i = 0; i < MAX_PAR_COUNT; i++) {
		if(m_pParameter[i]) {
			delete m_pParameter[i];
		}
	}
}

void CDataBindDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_CTRL, m_wndReport);
}


BEGIN_MESSAGE_MAP(CDataBindDlg, CMyResizeDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
END_MESSAGE_MAP()


// CDataBindDlg 메시지 처리기입니다.

BOOL CDataBindDlg::OnInitDialog()
{
	CMyResizeDialog::OnInitDialog();

//	if(m_nHeight > 0 && m_nWidth > 0)
//		SetWindowPos(NULL, 0, 0, m_nHeight, m_nWidth, SWP_NOMOVE | SWP_NOZORDER);

	ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);

	SetResize(IDC_REPORT_CTRL, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_REFRESH_BTN, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_OK_BTN, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);
	
	SetWindowText(m_strTitle);

	m_wndReport.GetReportHeader()->AllowColumnResize(TRUE);
	//m_wndReport.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_wndReport.GetReportHeader()->AllowColumnSort(TRUE);
	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.SetPaintManager(new CMyReportPaintManager());
	m_wndReport.GetPaintManager()->m_strNoItems = "";
	m_wndReport.SetGridStyle(TRUE, xtpGridSolid);
	m_wndReport.SetGridColor(RGB(212, 208, 200));
	m_wndReport.AllowEdit(FALSE);

	if(!MakeList()) 
	{
		PostMessage(WM_CLOSE, 0, 0);	
		return FALSE;
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CDataBindDlg::MakeList()
{
	m_wndReport.GetColumns()->Clear();
	m_wndReport.GetRecords()->RemoveAll();

	CMkCommand pCmd(m_pMkDb, m_strProc);

	for(int i = 0; i < MAX_PAR_COUNT; i++) {
		if(m_pParameter[i])	{
			PARAMETER_STRUCT *pPS = m_pParameter[i]->GetParameter();
			pCmd.AddParameter((cmkVT)pPS->nType, (cmkDir)pPS->nDirection, pPS->lSize, pPS->pValue);
		}
	}

	CMkRecordset pRs(m_pMkDb);
	if(!pRs.Execute(&pCmd)) return FALSE;

	for(int i = 0; i < pRs.GetFiledCount(); i++)
	{
		int nAlignment;
		CString strFieldName = pRs.GetFieldName(i);
		switch(pRs.GetFieldType(i))
		{
			case typeInt:
			case typeLong:
			case typeBool:
				nAlignment = DT_RIGHT;
				break;

			case typeDate:
				nAlignment = DT_CENTER;
				break;

			default:
				nAlignment = DT_LEFT;
				break;
		}

		if(strFieldName.GetLength() > 2 && strFieldName.Find("_") > 0)
		{
			BOOL bNoChange = FALSE;

			CString strRightPart = strFieldName.Right(2);
			if(strRightPart.CompareNoCase("_L") == 0)
				nAlignment = DT_LEFT;
			else if(strRightPart.CompareNoCase("_R") == 0)
				nAlignment = DT_RIGHT;
			else if(strRightPart.CompareNoCase("_C") == 0)
				nAlignment = DT_CENTER;
			else
				bNoChange = TRUE;

//			if(!bNoChange)
//			{
//				strFieldName.Delete(strFieldName.GetLength() - 3, 2);
//				strFieldName.SetFieldName(strFieldName);
//			}
		}

		CXTPGridColumn *p1 = m_wndReport.AddColumn(new CXTPGridColumn(i, strFieldName, 50, TRUE));
		p1->SetAlignment(nAlignment);
	}


	long nMaxTextExtend[MAX_PAR_COUNT];
	memset((char*)&nMaxTextExtend, 0, sizeof(long)*MAX_PAR_COUNT);

	for(int k = 0; k < pRs.GetRecordCount(); k++)
	{
		CXTPGridRecord *pRecord = new CXTPGridRecord;

		for(int i = 0; i < pRs.GetFiledCount(); i++)
		{
			switch(pRs.GetFieldType(i))
			{
				case typeInt:
				case typeLong:
				case typeBool:
					{
						long nValue;
						pRs.GetFieldValue(i, nValue);
						pRecord->AddItem(new CXTPGridRecordItemNumber(nValue));

						CString strText = pRs.GetFieldValueToString(i);
						CDC *pDC = m_wndReport.GetWindowDC();
						long cx = pDC->GetTextExtent(strText).cx;
						//g_bana_log->Print("cx = %d\n", cx);
						nMaxTextExtend[i] = max(nMaxTextExtend[i], cx);
					}
					break;

				default:
					{
						CString strText = pRs.GetFieldValueToString(i);
						pRecord->AddItem(new CXTPGridRecordItemText(strText));
						CDC *pDC = m_wndReport.GetWindowDC();
						long cx = pDC->GetTextExtent(strText).cx;
						//g_bana_log->Print("cx = %d\n", cx);
						nMaxTextExtend[i] = max(nMaxTextExtend[i], cx);
					}
					break;
			}
		}

		m_wndReport.AddRecord(pRecord);
		pRs.MoveNext();
	}

	for(int i = 0; i < pRs.GetFiledCount(); i++)
	{
		CString strText = pRs.GetFieldName(i);
		CDC *pDC = m_wndReport.GetWindowDC();
		long cx = pDC->GetTextExtent(strText).cx;
		nMaxTextExtend[i] = max(nMaxTextExtend[i], cx);
	}

	if(pRs.GetRecordCount() > 0)
	{
		long nWidth = 0;
		for(int x = 0; x < pRs.GetFiledCount(); x++)
		{
			CXTPGridColumn *pColumn = m_wndReport.GetColumns()->GetAt(x);
			//g_bana_log->Print("%d=%d\n", x, nMaxTextExtend[x]);
			nWidth += min(300, nMaxTextExtend[x]);
			pColumn->SetWidth(min(300, nMaxTextExtend[x] * 1.2));
		}

		CDC *pDC = m_wndReport.GetWindowDC();
		long nHeight = 24;

		nHeight = nHeight * pRs.GetRecordCount();

		nHeight = min(600, nHeight);
		nWidth = min(800, nWidth);


		CRect rc;
		GetWindowRect(rc);
		rc.right = rc.left + nWidth + 40;
		rc.bottom = rc.top + nHeight + 40;
		g_bana_log->Print("width = %d, nHeight = %d\n", rc.Width(), rc.Height());
		MoveWindow(rc);
	}

	m_wndReport.Populate();

	return TRUE;
}

void CDataBindDlg::OnBnClickedRefreshBtn()
{
	MakeList();
}

void CDataBindDlg::OnBnClickedOkBtn()
{
	OnOK();
}
