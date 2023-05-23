// ShareReportRateDlg2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareReportRateDlg2.h"

#include "ShareReportRateDlg.h"
//#include "WebDownLoadDlg.h"




IMPLEMENT_DYNCREATE(CShareReportRateDlg2, CMyFormView)

CShareReportRateDlg2::CShareReportRateDlg2()
	: CMyFormView(CShareReportRateDlg2::IDD)
{
}

CShareReportRateDlg2::~CShareReportRateDlg2()
{
}

void CShareReportRateDlg2::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	DDX_Control(pDX, IDC_TRANSFER_CHECK, m_TransferChk);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_TYPE_COMBO, m_cmbType);
}

BEGIN_MESSAGE_MAP(CShareReportRateDlg2, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_CLICK, IDC_REPORT, OnReportItemClick)
	ON_WM_MOUSEACTIVATE()
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_RCLICK, IDC_REPORT, OnReportItemRClick)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)	
END_MESSAGE_MAP()


// CShareReportRateDlg2 진단입니다.

#ifdef _DEBUG
void CShareReportRateDlg2::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CShareReportRateDlg2::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


void CShareReportRateDlg2::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;


	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_wndReport, pt);

}

// CShareReportRateDlg2 메시지 처리기입니다.

void CShareReportRateDlg2::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuWeek();

	m_cmbType.SetCurSel(0);

	m_wndReport.GetImageManager()->SetIcons(IDB_BMREPORT, 0, 0, CSize(16, 16));
	CXTPGridColumn* pCol0 = m_wndReport.AddColumn(new CXTPGridColumn(0, _T("일자"), 120, FALSE));
	CXTPGridColumn* pCol1 = m_wndReport.AddColumn(new CXTPGridColumn(1, _T("상태"), 100, FALSE));
	CXTPGridColumn* pCol2 = m_wndReport.AddColumn(new CXTPGridColumn(2, _T("입/출금액"), 80, FALSE));
	CXTPGridColumn* pCol3 = m_wndReport.AddColumn(new CXTPGridColumn(3, _T("현재잔액"), 80, FALSE));
	CXTPGridColumn* pCol4 = m_wndReport.AddColumn(new CXTPGridColumn(4, _T("설명"), 400, FALSE));
	CXTPGridColumn* pCol5 = m_wndReport.AddColumn(new CXTPGridColumn(5, _T("고지서보기"), 75, FALSE));

	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol1->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol2->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol3->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol4->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol5->GetEditOptions()->m_bAllowEdit = FALSE;

	pCol2->SetAlignment(DT_RIGHT);
	pCol3->SetAlignment(DT_RIGHT);

	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(TRUE);
	m_wndReport.AllowEdit(TRUE);
	m_wndReport.FocusSubItems(TRUE);
	m_wndReport.Populate();
	m_wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_wndReport.GetPaintManager()->m_strNoItems = "정보갱신 버튼을 누르시기 바랍니다.";
	m_wndReport.SetPaintManager(new CMyReportPaintManager());

}

void CShareReportRateDlg2::RefreshList()
{
	UpdateData(TRUE);
	CString strSql;

	//if(m_TransferChk.GetCheck() == BST_CHECKED)
	//	strSql = "select_ShareAccountLog_Transfer";
	//else
	
	strSql = "select_ShareAccountLog_new";


	CShareReportRateDlg* pShareReportRateDlg = (CShareReportRateDlg*)(GetParent()->GetParent());

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, strSql);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_cmbType.GetCurSel());
	pCmd.AddParameter(m_dtFrom);
	pCmd.AddParameter(m_dtTo);


	//long nBalance, nBasicRate;
	CString strAccount;
	

	m_wndReport.GetRecords()->RemoveAll();

	if(pRs.Execute(&pCmd))
	{
		long nDeposit,nBalance, nTrafficPenalty;
		CString sState,sEtc;
		COleDateTime dtGenerate;


		while(!pRs.IsEOF())
		{
			pRs.GetFieldValue("dtGenerate", dtGenerate);
			pRs.GetFieldValue("sState", sState);
			pRs.GetFieldValue("nDeposit", nDeposit);
			pRs.GetFieldValue("nBalance", nBalance);
			pRs.GetFieldValue("sEtc", sEtc);
			pRs.GetFieldValue("nTrafficPenalty", nTrafficPenalty);

			m_wndReport.AddRecord(new CMyRecord(dtGenerate, sState, nDeposit, nBalance, sEtc, nTrafficPenalty) );

			pRs.MoveNext();
		}

		m_wndReport.Populate();
	}
}

//정보 갱신
void CShareReportRateDlg2::OnBnClickedRefreshBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	RefreshList();
}

int CShareReportRateDlg2::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return 0;
	return CMyFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void CShareReportRateDlg2::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{

	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	CXTPGridRecords *pRecords = m_wndReport.GetRecords();

	CMyRecord *pRecord = (CMyRecord *)pItemNotify->pRow->GetRecord();
	
	/*
	if(nCol == 5)
	{
		CWebDownLoadDlg dlg;
		dlg.m_nID = pRecord->m_nTrafficPenalty;		
		dlg.DoModal();
	}
	*/
	
}

void CShareReportRateDlg2::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_wndReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CShareReportRateDlg2::OnViewExcel()
{
	if(!LF->POWER_CHECK(2010, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 102, m_ui.nWNo, m_wndReport.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_wndReport);
}
