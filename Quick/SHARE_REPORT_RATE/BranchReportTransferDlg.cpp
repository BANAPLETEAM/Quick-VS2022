// BranchReportTransferDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "BranchReportTransferDlg.h"
#include "BranchReportMainDlg.h"
#include "ShareReportTransferDlg.h"

#include "ShareReportWantTransferDlg.h"
#include "ShareTranferRequestDlg.h"


#define TRANSFRER 4
#define WANT_TRANSFER 5
#define SR_INTRO_COL 6
// CBranchReportTransferDlg 대화 상자입니다.

IMPLEMENT_DYNCREATE(CBranchReportTransferDlg, CMyFormView)

CBranchRecord::CBranchRecord(long nCompany, CString sTel, CString sOfficePhone, bool bIsAllianceHead)
{
    m_nCompany = nCompany;
	m_bIsAllianceHead = bIsAllianceHead;

	AddItem(new CXTPGridRecordItemMyNumber(nCompany));
	AddItem(new CXTPGridRecordItemMyNumber1(nCompany));
	AddItem(new CXTPGridRecordItemText(sTel));
	AddItem(new CXTPGridRecordItemText(sOfficePhone));
	AddItem(new CXTPGridRecordItemText("이체"));
	AddItem(new CXTPGridRecordItemText("청구"));
	AddItem(new CXTPGridRecordItemText("소개"));
}


void CBranchRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nRow = this->GetIndex();
	int nCol = pDrawArgs->pColumn->GetItemIndex();

	CXTPGridColumn *pColumn = NULL;

	if(nCol >= TRANSFRER)
		pItemMetrics->clrForeground = RGB(0, 0, 255);

	if(nRow %2 == 0)
		pItemMetrics->clrBackground = RGB(235, 235, 255);
	else
		pItemMetrics->clrBackground = RGB(255, 255, 255);
}


CBranchReportTransferDlg::CBranchReportTransferDlg()
: CMyFormView(CBranchReportTransferDlg::IDD)
{
}

CBranchReportTransferDlg::~CBranchReportTransferDlg()
{
}

void CBranchReportTransferDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_CTRL, m_wndReport);
	
}

BEGIN_MESSAGE_MAP(CBranchReportTransferDlg, CMyFormView)
	ON_WM_MOUSEACTIVATE()
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_CTRL, OnReportItemClick)
	ON_BN_CLICKED(IDC_TRANSFER_BTN, OnBnClickedTransferBtn)
END_MESSAGE_MAP()




UINT OpenRequest (LPVOID arg)
{
	CBranchReportTransferDlg * pArg = (CBranchReportTransferDlg*) arg;

	pArg->MakeRequestWindow(FALSE);

	return 0;
}

void CBranchReportTransferDlg::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS);

	CXTPGridColumn *pCol0 = m_wndReport.AddColumn(new CXTPGridColumn(0, "회사명", 80, FALSE));
	CXTPGridColumn *pCol1 = m_wndReport.AddColumn(new CXTPGridColumn(1, "지사명", 80, FALSE));
	CXTPGridColumn *pCol2 = m_wndReport.AddColumn(new CXTPGridColumn(2, "대표번호", 90, FALSE));
	CXTPGridColumn *pCol3 = m_wndReport.AddColumn(new CXTPGridColumn(3, "상황실폰", 90, FALSE));
	CXTPGridColumn *pCol4 = m_wndReport.AddColumn(new CXTPGridColumn(4, "이체", 35, FALSE));
	CXTPGridColumn *pCol5 = m_wndReport.AddColumn(new CXTPGridColumn(5, "청구", 35, FALSE));
	CXTPGridColumn *pCol6 = m_wndReport.AddColumn(new CXTPGridColumn(6, "소개", 35, FALSE));

	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol0->SetAlignment(DT_RIGHT);	
	pCol1->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol1->SetAlignment(DT_RIGHT);
	pCol2->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol2->SetAlignment(DT_RIGHT);
	pCol3->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol3->SetAlignment(DT_CENTER);
	pCol4->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol4->SetAlignment(DT_CENTER);
	pCol5->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol5->SetAlignment(DT_CENTER);

	m_wndReport.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_wndReport.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(TRUE);
	m_wndReport.GetReportHeader()->AllowColumnSort(TRUE);
	m_wndReport.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_wndReport.AllowEdit(TRUE);
	m_wndReport.FocusSubItems(TRUE);
	m_wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_wndReport.SetGridColor(RGB(180, 180, 200));

	m_wndReport.Populate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void CBranchReportTransferDlg::RefreshList()
{
	m_wndReport.GetRecords()->RemoveAll();

	CBranchReportMainDlg* pBranchReportMainDlg = (CBranchReportMainDlg*)(GetParent()->GetParent());

	long nBalance = 0;
	long nBasicRate = 0;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_use_branchsharereport_company");

    pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nShareCode1);
	CMkParameter * pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), nBalance);
	CMkParameter * parBasicRate = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), nBasicRate);

	if(!pRs.Execute(&pCmd)) return;

	pPar->GetValue(nBalance);
	parBasicRate->GetValue(nBasicRate);

	CString str = CString(LF->GetMyNumberFormat(nBalance - nBasicRate)) + "원";
    
	pBranchReportMainDlg->m_MoneyEdt.SetWindowText(str);

	long nCompany;
	CString sTel, sOfficePhone;
	int bIsAllianceHead;

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("nID", nCompany);
		pRs.GetFieldValue("sTel", sTel);
		pRs.GetFieldValue("sOfficePhone", sOfficePhone);
		pRs.GetFieldValue("bIsAllianceHead", bIsAllianceHead);

        m_wndReport.AddRecord(new CBranchRecord(nCompany, sTel, sOfficePhone, FALSE));

		pRs.MoveNext();
	}

	m_wndReport.Populate();

	//AfxBeginThread(OpenRequest, (LPVOID)this);
}

int CBranchReportTransferDlg::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;

	//return CMyFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CBranchReportTransferDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CBranchReportTransferDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	 XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CBranchReportMainDlg* pBranchReportMainDlg = (CBranchReportMainDlg*)(GetParent()->GetParent());

	//int nRow = pItemNotify->pRow->GetIndex();
	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	CXTPGridRecords *pRecords = m_wndReport.GetRecords();
	CXTPGridRecord *pRecord = pItemNotify->pRow->GetRecord();

	long nCompany = m_ci.m_nShareCode1;
	long nShareCode1B = ((CBranchRecord*)pRecord)->m_nCompany;

	nRow = pRecord->GetIndex();

	if(nCol == TRANSFRER) 
	{
		CShareReportTransferDlg dlg;
		dlg.m_nToCompany = nShareCode1B;

///		long nBalance;

		//dlg.m_pShareReportRateDlg1 = this;

		CString sAbilityMoney;
		pBranchReportMainDlg->m_MoneyEdt.GetWindowText(sAbilityMoney);
		sAbilityMoney.Replace("원", "");
		sAbilityMoney.Replace(",", "");
        
		dlg.m_nAbilityMoney = atoi(sAbilityMoney);

		if(dlg.DoModal() == IDOK)
			RefreshMoney();

	}
	else if(nCol == WANT_TRANSFER)
	{
		CShareReportWantTransferDlg dlg;
		dlg.m_nToCompany = nShareCode1B;
		dlg.DoModal();	
	}
	else if(nCol == SR_INTRO_COL)
	{
		/*
		if(!((CBranchRecord*)pRecord)->m_bIsAllianceHead )
		{
			CCompanyIntroDlg dlg;
			dlg.m_nIntroCompany = nShareCode1B;
			dlg.m_nWriteMode = 0;
			dlg.DoModal();
		}
		*/
	}
}


bool CBranchReportTransferDlg::IsRequest(int nCompany)
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_transfer_request_branch");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);

	if(!pRs.Execute(&pCmd)) return false;

	if(pRs.GetRecordCount() > 0)
		return true;
	else
		return false;

}

void CBranchReportTransferDlg::OnBnClickedTransferBtn()
{
	MakeRequestWindow(TRUE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CBranchReportTransferDlg::MakeRequestWindow(bool bMake)
{
	if(IsRequest(m_ci.m_nCompanyCode))
	{
		CShareTranferRequestDlg dlg;

		CBranchReportMainDlg* pBranchReportMainDlg = (CBranchReportMainDlg*)(GetParent()->GetParent());

		CString sAbilityMoney;
		pBranchReportMainDlg->m_MoneyEdt.GetWindowText(sAbilityMoney);
		sAbilityMoney.Replace("원", "");
		sAbilityMoney.Replace(",", "");

		dlg.m_nAbilityMoney = _ttoi(sAbilityMoney);
		dlg.m_pBranchReportTransferDlg = this;
		dlg.m_sSql = "select_transfer_request_branch_1";

		if(dlg.DoModal() == IDOK)
			RefreshMoney();

	}else if(bMake)
		MessageBox("타사에서의 요청이 없습니다", "확인", MB_ICONERROR);
}

void CBranchReportTransferDlg::RefreshMoney()
{
	CBranchReportMainDlg* pBranchReportMainDlg = (CBranchReportMainDlg*)(GetParent()->GetParent());

	long nBalance = 0;
	long nBasicRate = 0;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_use_branchsharereport_company");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nShareCode1);
	CMkParameter * pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), nBalance);
	CMkParameter * parBasicRate = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), nBasicRate);

	if(!pRs.Execute(&pCmd)) return;

	pPar->GetValue(nBalance);
	parBasicRate->GetValue(nBasicRate);

	CString str = CString(LF->GetMyNumberFormat(nBalance - nBasicRate)) + "원";

	pBranchReportMainDlg->m_MoneyEdt.SetWindowText(str);
}
