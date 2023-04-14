// LineDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "LineDlg.h"



// CLineDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CLineDlg, CMyDialog)
CLineDlg::CLineDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CLineDlg::IDD, pParent)
{
}

CLineDlg::~CLineDlg()
{
}

void CLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REGION_COMBO, m_RegionCmb);
	DDX_Control(pDX, IDC_REPORT_LIST, m_wndReport);
	DDX_Control(pDX, IDC_SEARCH_START_EDIT, m_SearchStartEdt);
	DDX_Control(pDX, IDC_SEARCH_DEST_EDIT, m_SearchDestEdt);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_RefreshBtn);
	DDX_Control(pDX, IDC_SAVE_BTN, m_SaveBtn);
}


BEGIN_MESSAGE_MAP(CLineDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SAVE_BTN, OnBnClickedSaveBtn)
	ON_CBN_SELCHANGE(IDC_REGION_COMBO, OnCbnSelchangeRegionCombo)
	ON_EN_CHANGE(IDC_SEARCH_START_EDIT, OnEnChangeSearchStartEdit)
	ON_EN_CHANGE(IDC_SEARCH_DEST_EDIT, OnEnChangeSearchDestEdit)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
END_MESSAGE_MAP()


// CLineDlg 메시지 처리기입니다.

void CLineDlg::OnBnClickedSaveBtn()
{
	CString sAddType = "";
	CString sAddCharge = "";

	char buffer[20];



	for(int i=0; i<m_wndReport.GetRows()->GetCount(); i++)
	{
		long nType = 0;
		long nCharge = 0;

		CXTPGridRecords *pRecords = m_wndReport.GetRecords();
		CXTPGridRow *pRow = (CXTPGridRow*)m_wndReport.GetRows()->GetAt(i);
		CLineReport *pRecord = (CLineReport*)pRow->GetRecord();

		nType = ((CLineReport*)pRecord)->m_nType;	
		nCharge = (long)((CXTPGridRecordItemNumber*)m_wndReport.GetRecords()->GetAt(i)->GetItem(2))->GetValue();
				
		sAddType += (CString)itoa(nType, buffer, 10) + ";";
		sAddCharge += (CString)itoa(nCharge, buffer, 10) + ";";
	}

	CMkCommand pCmd(m_pMkDb, "update_terminal_charge");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
	pCmd.AddParameter(typeLong, typeInput, sAddType.GetLength(), sAddType);
	pCmd.AddParameter(typeLong, typeInput, sAddCharge.GetLength(), sAddCharge);
	
	if(!pCmd.Execute())
	{
		MessageBox("저장중 오류 발생!! 다시 시도하세요" ,"확인", MB_ICONINFORMATION);
		return;
	}
    
}

BOOL CLineDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

    InitCombo();

	CXTPGridColumn * pCol0 = m_wndReport.AddColumn(new CXTPGridColumn(0, "출발지", 130, FALSE));
	CXTPGridColumn * pCol1 = m_wndReport.AddColumn(new CXTPGridColumn(1, "도착지", 130, FALSE));
	CXTPGridColumn * pCol2 = m_wndReport.AddColumn(new CXTPGridColumn(2, "요금", 90, FALSE));

	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol1->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol2->GetEditOptions()->m_bAllowEdit = TRUE;

	pCol0->SetAlignment(DT_LEFT);
	pCol1->SetAlignment(DT_LEFT);
	pCol2->SetAlignment(DT_RIGHT);

	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(TRUE);
	m_wndReport.GetReportHeader()->AllowColumnSort(TRUE);
	m_wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_wndReport.GetPaintManager()->m_strNoItems = "";
	m_wndReport.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_wndReport.AllowEdit(TRUE);
	m_wndReport.FocusSubItems(TRUE);
	m_wndReport.SetGridColor(RGB(180, 180, 200));
	m_wndReport.Populate();
	
	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CLineDlg::InitCombo()
{
	CString sTerminalRegion = AfxGetApp()->GetProfileString("sTerminalRegion", "sTerminalRegion", "");	
	    
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_start_rerminal");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), 0);
	CString sStart;

	if(!pRs.Execute(&pCmd)) return;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
        pRs.GetFieldValue("sStart", sStart);
		m_RegionCmb.InsertString(i, sStart);

		if(sTerminalRegion == sStart)
			m_RegionCmb.SetCurSel(i);

		pRs.MoveNext();
	}

	if(m_RegionCmb.GetCurSel() == -1)
		m_RegionCmb.SetCurSel(0);
}

void CLineDlg::OnCbnSelchangeRegionCombo()
{
	long index = m_RegionCmb.GetCurSel();

	CString sTerminalRegion;
	m_RegionCmb.GetLBText(index, sTerminalRegion);

	AfxGetApp()->WriteProfileString("sTerminalRegion", "sTerminalRegion", sTerminalRegion);	

	RefreshList();
}

void CLineDlg::RefreshList()
{
	m_wndReport.GetRecords()->RemoveAll();

	long index = m_RegionCmb.GetCurSel();

	CString sTerminalRegion;
	m_RegionCmb.GetLBText(index, sTerminalRegion);

    CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_terminal_charge");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
	pCmd.AddParameter(typeString, typeInput, sTerminalRegion.GetLength(), sTerminalRegion);

	if(!pRs.Execute(&pCmd)) return;

	CString sDest;
	long nCharge, nType;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
        pRs.GetFieldValue("sDest", sDest);
		pRs.GetFieldValue("nCharge", nCharge);
		pRs.GetFieldValue("nID", nType);

		m_wndReport.AddRecord(new CLineReport(sTerminalRegion ,sDest, nType, nCharge));

		pRs.MoveNext();
	}

	m_wndReport.Populate();	
}

void CLineDlg::OnEnChangeSearchStartEdit()
{
	CString str, strCmb; 
	m_SearchStartEdt.GetWindowText(str);

	if(str.GetLength() < 1) return;

	for(int i=0; i<m_RegionCmb.GetCount(); i++)
	{
		m_RegionCmb.GetLBText(i, strCmb);

		if(strCmb.Find(str) >=0)
		{
			m_RegionCmb.SetCurSel(i);
			RefreshList();
			return;
		}
	}
	
}

void CLineDlg::OnEnChangeSearchDestEdit()
{
	CString str, strReport;
	m_SearchDestEdt.GetWindowText(str);
	
	if(str.GetLength() < 1) return;

	for(int i=0; i<m_wndReport.GetRows()->GetCount(); i++) 
	{
		CXTPGridColumn *pColumn = NULL;
		CXTPGridRow *pRow = m_wndReport.GetRows()->GetAt(i);

		strReport = ((CXTPGridRecordItemText*)m_wndReport.GetRecords()->GetAt(i)->GetItem(1))->GetCaption(pColumn);

		if(strReport.Find(str) >=0)
		{
			m_wndReport.GetSelectedRows()->Select(pRow);
			return;
		}
	}
}

void CLineDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

BOOL CLineDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}
