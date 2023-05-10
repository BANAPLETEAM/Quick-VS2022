// BranchReportLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "BranchReportLogDlg.h"

//#include "MyReportPaintManager.h"

CAccountRecord::CAccountRecord(COleDateTime dtGenerate,CString sState,long nDeposit,long nBalance,CString sEtc)
{
	AddItem(new CMyDateRecordItem(dtGenerate));
	AddItem(new CXTPGridRecordItemText(sState));
	AddItem(new CXTPGridRecordItemText(::GetMyNumberFormat(nDeposit)));
	AddItem(new CXTPGridRecordItemText(::GetMyNumberFormat(nBalance)));
	AddItem(new CXTPGridRecordItemText(sEtc));
}

void CAccountRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	long lVal = (long)((CXTPGridRecordItemNumber*)GetItem(2))->GetValue();
	if( lVal < 0)
	{
		pItemMetrics->clrForeground = RGB(0, 0, 0);
		pItemMetrics->clrBackground = RGB(255, 232, 232);
	}
	else
	{
		pItemMetrics->clrForeground = RGB(0, 0, 0);
		pItemMetrics->clrBackground = RGB(232, 232, 255);
	}

	int nCol = pDrawArgs->pColumn->GetIndex();
	if(nCol == 2 || nCol == 3)
	{
		pDrawArgs->nTextAlign = 2;
	}

		return;
}

// CBranchReportLogDlg

IMPLEMENT_DYNCREATE(CBranchReportLogDlg, CMyFormView)

CBranchReportLogDlg::CBranchReportLogDlg()
	: CMyFormView(CBranchReportLogDlg::IDD)
{
}

CBranchReportLogDlg::~CBranchReportLogDlg()
{
}

void CBranchReportLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TRANSFER_CHECK, m_TransferChk);
	DDX_Control(pDX, IDC_REPORT_CTRL, m_wndReport);
}

BEGIN_MESSAGE_MAP(CBranchReportLogDlg, CMyFormView)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_WM_MOUSEACTIVATE()
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CBranchReportLogDlg 진단입니다.

#ifdef _DEBUG
void CBranchReportLogDlg::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CBranchReportLogDlg::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CBranchReportLogDlg 메시지 처리기입니다.

void CBranchReportLogDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CBranchReportLogDlg::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_wndReport.GetImageManager()->SetIcons(IDB_BMREPORT, 0, 0, CSize(16, 16));
	CXTPGridColumn* pCol0 = m_wndReport.AddColumn(new CXTPGridColumn(0, _T("일자"), 120, TRUE));
	CXTPGridColumn* pCol1 = m_wndReport.AddColumn(new CXTPGridColumn(1, _T("상태"), 100, TRUE));
	CXTPGridColumn* pCol2 = m_wndReport.AddColumn(new CXTPGridColumn(2, _T("입/출금액"), 80, TRUE));
	CXTPGridColumn* pCol3 = m_wndReport.AddColumn(new CXTPGridColumn(3, _T("현재잔액"), 80, TRUE));
	CXTPGridColumn* pCol4 = m_wndReport.AddColumn(new CXTPGridColumn(4, _T("설명"), 250, TRUE));

	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol1->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol2->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol3->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol4->GetEditOptions()->m_bAllowEdit = FALSE;

	pCol2->SetAlignment(DT_RIGHT);
	pCol3->SetAlignment(DT_RIGHT);

	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(TRUE);
	m_wndReport.AllowEdit(TRUE);
	m_wndReport.FocusSubItems(TRUE);
	m_wndReport.Populate();
	m_wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_wndReport.GetPaintManager()->m_strNoItems = "정보갱신 버튼을 누르시기 바랍니다.";

	m_wndReport.Populate();
//	m_wndReport.SetPaintManager(new CMyReportPaintManager());
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CBranchReportLogDlg::RefreshList()
{
	CString strSql;

	if(m_TransferChk.GetCheck() == BST_CHECKED)
		strSql = "select_ShareAccountLog_Transfer";
	else
		strSql = "select_ShareAccountLog";


	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, strSql);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);


//	long nBalance, nBasicRate;
	CString strAccount;
//	char buffer[10];

	m_wndReport.GetRecords()->RemoveAll();

	if(pRs.Execute(&pCmd))
	{
		long nDeposit,nBalance;
		CString sState,sEtc;
		COleDateTime dtGenerate;


		while(!pRs.IsEOF())
		{
			pRs.GetFieldValue("dtGenerate", dtGenerate);
			pRs.GetFieldValue("sState", sState);
			pRs.GetFieldValue("nDeposit", nDeposit);
			pRs.GetFieldValue("nBalance", nBalance);
			pRs.GetFieldValue("sEtc", sEtc);

			m_wndReport.AddRecord(new CAccountRecord(dtGenerate, sState, nDeposit, nBalance, sEtc) );

			pRs.MoveNext();
		}

		m_wndReport.Populate();
	}
}

int CBranchReportLogDlg::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;

	//return CMyFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CBranchReportLogDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CBranchReportLogDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_wndReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}


void CBranchReportLogDlg::OnViewExcel()
{
	if(!POWER_CHECK(2010, "엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nCompanyCode, 102, m_ui.nWNo, m_wndReport.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_wndReport);
}
