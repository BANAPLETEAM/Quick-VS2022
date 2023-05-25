// ShareReportBranchSetDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareReportBranchSetDlg.h"

#include "DataBindDlg.h"
#include "RequestDrawingDlg.h"

// CShareReportBranchSetDlg 대화 상자입니다.

#define EVENT_ID 1000
#define ID_CARD_INFO_DELETE 2000

CShareReportBranchRecord::CShareReportBranchRecord(long nCompany, CString strBranchName, CString strPhone, BOOL bUseBranchShareReport, long nType,
			 long nAutoCharge, long nBigAuto, long nDamaCharge, long nRaboCharge, long nBanCharge, long nTruckCharge, long nSubwayCharge, long nRiderCallCharge,
			 long nBalance, int nAccountDue, CString strInAccounts, CString strOutAccounts,  CString strReportHistory, BOOL bRiderVRDepositToMain, CString strMID)
{
	m_nCompany = nCompany;
	m_strInAccounts = strInAccounts;
		
	AddItem(new CXTPGridRecordItemText(strBranchName));
	AddItem(new CXTPGridRecordItemText(strPhone));
	AddItem(new CCallUseRecordItem(bUseBranchShareReport));
	//AddItem(new CXTPGridRecordItemText(bUseBranchShareReport == TRUE ? "ㅇ" : "X"));
	AddItem(new CCallTypeRecordItem(nType));
	AddItem(new CCallChargeRecordItem(nAutoCharge));
	AddItem(new CCallChargeRecordItem(nBigAuto));
	AddItem(new CCallChargeRecordItem(nDamaCharge));
	AddItem(new CCallChargeRecordItem(nRaboCharge));
	AddItem(new CCallChargeRecordItem(nBanCharge));	
	AddItem(new CCallChargeRecordItem(nTruckCharge));
	AddItem(new CCallChargeRecordItem(nSubwayCharge));
	AddItem(new CCallChargeRecordItem(nRiderCallCharge));
	AddItem(new CXTPGridRecordItemNumber(nBalance));
	//AddItem(new CXTPGridRecordItemNumber(nAccountDue));
	AddItem(new CXTPGridRecordItemText(strInAccounts));
	AddItem(new CXTPGridRecordItemText(strOutAccounts));
	CXTPGridRecordItem *pItem = AddItem(new CXTPGridRecordItemText(strReportHistory));
	pItem->AddHyperlink(new CXTPGridHyperlink(0, 0xFFFF));
	AddItem(new CRiderVRBalancePushTypeRecordItem(bRiderVRDepositToMain));
	AddItem(new CXTPGridRecordItemText(strMID));
}


void CShareReportBranchRecord::GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
{
	CXTPGridRecord::GetItemMetrics(pDrawArgs, pItemMetrics);

	int nCol = pDrawArgs->pColumn->GetIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	long nCallChargeType = ((CCallChargeRecordItem*)GetItem(2))->GetValue();

	if(nCol < 2)
	{
		pItemMetrics->clrBackground = RGB(100, 220, 100);
		pItemMetrics->clrForeground= RGB(255, 255, 255);
		pItemMetrics->pFont = &pDrawArgs->pControl->GetPaintManager()->m_fontBoldText;
	}
	else if(nCol == 2)
	{
		pItemMetrics->clrBackground = RGB(200, 255, 200);
		pItemMetrics->clrForeground= RGB(0, 0, 0);
		pItemMetrics->pFont = &pDrawArgs->pControl->GetPaintManager()->m_fontBoldText;
	}

	if(nCol == 3)
	{
		pDrawArgs->nTextAlign = DT_RIGHT;
	}


}



IMPLEMENT_DYNAMIC(CShareReportBranchSetDlg, CMyDialog)
CShareReportBranchSetDlg::CShareReportBranchSetDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CShareReportBranchSetDlg::IDD, pParent)
{
}

CShareReportBranchSetDlg::~CShareReportBranchSetDlg()
{
}

void CShareReportBranchSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	DDX_Control(pDX, IDC_ACCOUNT_EDIT, m_edtAccount);
	DDX_Control(pDX, IDC_DRAWING_BTN, m_btnDrawing);
}


BEGIN_MESSAGE_MAP(CShareReportBranchSetDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SAVE_BTN, OnBnClickedSaveBtn)
	ON_NOTIFY(NM_CLICK, IDC_REPORT, OnReportItemClick)
	ON_BN_CLICKED(IDC_DRAWING_BTN, OnBnClickedDrawingBtn)
	ON_BN_CLICKED(IDC_ISSUE_BTN, OnBnClickedIssueBtn)
	ON_WM_CONTEXTMENU()
	ON_COMMAND_RANGE(EVENT_ID, EVENT_ID + 100, OnCardInfoInsert)
	ON_COMMAND(ID_CARD_INFO_DELETE, OnCardInfoDelete)
	ON_NOTIFY(NM_RCLICK, IDC_REPORT, OnReportItemRClick)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
END_MESSAGE_MAP()


void CShareReportBranchSetDlg::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_wndReport, pt);
}



void CShareReportBranchSetDlg::OnCardInfoDelete()
{
	CXTPGridSelectedRows *pRows = m_wndReport.GetSelectedRows(); 

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	for(int i=0; i<pRows->GetCount(); i++)
	{
		CShareReportBranchRecord *pRecord = (CShareReportBranchRecord*)pRows->GetAt(i)->GetRecord();
		long nToCompany = pRecord->m_nCompany;

		CMkCommand cmd(m_pMkDb, "delete_card_info_to_branch");
		cmd.AddParameter(nToCompany);
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ui.strName);

		if(!cmd.Execute())
		{
			MessageBox("카드결제 정보 삭제중 에러가 발생했습니다", "확인", MB_ICONINFORMATION);
			return;
		}
	}

	RefreshList();
}

void CShareReportBranchSetDlg::OnCardInfoInsert(UINT nFlag)
{
	long nFromCompany = m_nCompanyArry[nFlag - EVENT_ID];

	CXTPGridSelectedRows *pRows = m_wndReport.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	for(int i=0; i<pRows->GetCount(); i++)
	{
		CShareReportBranchRecord *pRecord = (CShareReportBranchRecord*)pRows->GetAt(i)->GetRecord();
		long nToCompany = pRecord->m_nCompany;

		CMkCommand cmd(m_pMkDb, "insert_card_info_to_branch");
		cmd.AddParameter(nFromCompany);
		cmd.AddParameter(nToCompany);
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ui.strName);

		if(!cmd.Execute())
		{
			MessageBox("카드결제 정보 복사중 에러가 발생했습니다", "확인", MB_ICONINFORMATION);
			return;
		}
	}

	RefreshList();
}

// CShareReportBranchSetDlg 메시지 처리기입니다.

BOOL CShareReportBranchSetDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();

	if(!m_ci.m_bRcpIntMode1 && m_ci.m_bUseBranchShareReport)
		m_btnDrawing.ShowWindow(TRUE); 

	long nItem = 0;
	CXTPGridColumn* pCol0 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "지사명", 120, FALSE));
	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	CXTPGridColumn* pCol1 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "대표전화", 90, FALSE));
	pCol1->GetEditOptions()->m_bAllowEdit = FALSE;

	CXTPGridColumn* pCol2 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "사용", 40, FALSE));
	pCol2->GetEditOptions()->m_bAllowEdit = FALSE;
	CXTPGridColumn* pCol3 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "정산타입", 80, FALSE));
	CXTPGridColumn* pCol4 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "센터정산금(오토)", 100, FALSE));
	CXTPGridColumn* pCol5 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "짐받이오토", 80, FALSE));
	CXTPGridColumn* pCol6 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "다마스", 80, FALSE));
	CXTPGridColumn* pCol7 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "라보", 80, FALSE));
	CXTPGridColumn* pCol8 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "벤", 80, FALSE));
	CXTPGridColumn* pCol9 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "트럭", 80, FALSE));
	CXTPGridColumn* pCol10 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "지하철", 80, FALSE));
	CXTPGridColumn* pCol11 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "기사수행", 80, FALSE));



	if(!m_ci.m_bRcpIntMode1)
	{
		pCol3->GetEditOptions()->m_bAllowEdit = FALSE;
		pCol4->GetEditOptions()->m_bAllowEdit = FALSE;
		pCol5->GetEditOptions()->m_bAllowEdit = FALSE;
		pCol6->GetEditOptions()->m_bAllowEdit = FALSE;
		pCol7->GetEditOptions()->m_bAllowEdit = FALSE;
		pCol8->GetEditOptions()->m_bAllowEdit = FALSE;
		pCol9->GetEditOptions()->m_bAllowEdit = FALSE;
		pCol10->GetEditOptions()->m_bAllowEdit = FALSE;
	}

	CXTPGridColumn* pCol12 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "잔액", 60, FALSE));
	pCol12->GetEditOptions()->m_bAllowEdit = FALSE;
	//CXTPGridColumn* pCol12 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "본사미수금", 60, FALSE));
	//pCol12->GetEditOptions()->m_bAllowEdit = FALSE;
	CXTPGridColumn* pCol13 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "가상계좌번호", 150, FALSE));
	pCol13->GetEditOptions()->m_bAllowEdit = FALSE;
	CXTPGridColumn* pCol14 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "수령계좌번호", 150, FALSE));
	pCol14->GetEditOptions()->m_bAllowEdit = FALSE;
	CXTPGridColumn* pCol15 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "내역", 40, FALSE));
	pCol15->GetEditOptions()->m_bAllowEdit = FALSE;
	CXTPGridColumn* pCol16 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "기사잔액타입", 80, FALSE));
	pCol16->GetEditOptions()->m_bAllowEdit = FALSE;
	CXTPGridColumn* pCol17 = m_wndReport.AddColumn(new CXTPGridColumn(nItem++, "카드결제", 80, FALSE));
	pCol17->GetEditOptions()->m_bAllowEdit = FALSE;
 
 	pCol2->SetAlignment(DT_CENTER);

	m_wndReport.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_wndReport.SetTreeIndent(10);
	m_wndReport.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(FALSE);
	m_wndReport.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_wndReport.SetFreezeColumnsCount(2);
	m_wndReport.GetPaintManager()->SetFreezeColsDividerStyle(0);

	m_wndReport.AllowEdit(TRUE);
	m_wndReport.FocusSubItems(FALSE);
	m_wndReport.Populate();
	m_wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_wndReport.SetGridColor(RGB(222, 222, 222));

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CShareReportBranchSetDlg::RefreshList()
{
	m_wndReport.GetRecords()->RemoveAll();

	long nID, nBalance, nAccountDue = 0;
	long nAutoCharge, nType, nBigAutoCharge, nDamaCharge, nRaboCharge, nBanCharge, nTruckCharge, nSubwayCharge, nRiderCallCharge;
	CString strBranchName, strTel, strInAccounts, strOutAccounts, strMID;
	BOOL bUseBranchShareReport, bRiderVRDepositToMain;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_share_report_branch_info_new_3");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nShareCode1);
	CMkParameter *parAccount = pCmd.AddParameter(typeString, typeOutput, 50, "");
	CMkParameter *parReportRate = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

	if(pRs.Execute(&pCmd))
	{
		CString strAccount;
		long nReportRate;
		parAccount->GetValue(strAccount);
		m_edtAccount.SetWindowText(strAccount);
		parReportRate->GetValue(nReportRate);

		for(int i = 0; i < pRs.GetRecordCount(); i++)
		{	
			pRs.GetFieldValue("nID", nID);
			pRs.GetFieldValue("bUseBranchShareReport", bUseBranchShareReport);
			pRs.GetFieldValue("sBranchName", strBranchName);
			pRs.GetFieldValue("sTel", strTel);
			pRs.GetFieldValue("nType", nType);
			pRs.GetFieldValue("nAutoCharge", nAutoCharge);
			pRs.GetFieldValue("nBigAutoCharge", nBigAutoCharge);
			pRs.GetFieldValue("nDamaCharge", nDamaCharge);
			pRs.GetFieldValue("nRaboCharge", nRaboCharge);
			pRs.GetFieldValue("nBanCharge", nBanCharge);
			pRs.GetFieldValue("nTruckCharge", nTruckCharge);
			pRs.GetFieldValue("nSubwayCharge", nSubwayCharge);			
			pRs.GetFieldValue("nRiderCallCharge", nRiderCallCharge);
			pRs.GetFieldValue("nShareBalance", nBalance);
			pRs.GetFieldValue("sInAccounts", strInAccounts);
			pRs.GetFieldValue("sOutAccounts", strOutAccounts);
			pRs.GetFieldValue("bRiderVRDepositToMain", bRiderVRDepositToMain);
			pRs.GetFieldValue("sMID", strMID);

			m_wndReport.AddRecord(new CShareReportBranchRecord(nID, 
				strBranchName, strTel, bUseBranchShareReport, nType, nAutoCharge, nBigAutoCharge, nDamaCharge,
				nRaboCharge, nBanCharge, nTruckCharge, nSubwayCharge, nRiderCallCharge, nBalance, nAccountDue, strInAccounts, strOutAccounts, "내역", bRiderVRDepositToMain, strMID));

			pRs.MoveNext();
		}

		m_wndReport.Populate();
	}
}


void CShareReportBranchSetDlg::OnBnClickedSaveBtn()
{
	if(!m_ci.m_bRcpIntMode1)
	{
		MessageBox("메인에서만 수정가능합니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	for(int i = 0; i < m_wndReport.GetRows()->GetCount(); i++)
	{
		CXTPGridRow *pRow = (CXTPGridRow*)m_wndReport.GetRows()->GetAt(i);
		CXTPGridRecord *pRecord = pRow->GetRecord();
		long nCompany = ((CShareReportBranchRecord*)pRecord)->m_nCompany;

		if(((CShareReportBranchRecord*)pRecord)->GetDirtyFlag())
		{
			CMkCommand pCmd(m_pMkDb, "update_share_report_branch_info_new_3");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
			pCmd.AddParameter(((CShareReportBranchRecord*)pRecord)->GetCallUse());
			pCmd.AddParameter(((CShareReportBranchRecord*)pRecord)->GetCallChargeType());
			pCmd.AddParameter(((CShareReportBranchRecord*)pRecord)->GetCallChargeAuto());
			pCmd.AddParameter(((CShareReportBranchRecord*)pRecord)->GetCallChargeBigAuto());
			pCmd.AddParameter(((CShareReportBranchRecord*)pRecord)->GetCallChargeDama());
			pCmd.AddParameter(((CShareReportBranchRecord*)pRecord)->GetCallChargeRabo());
			pCmd.AddParameter(((CShareReportBranchRecord*)pRecord)->GetCallChargeBan());
			pCmd.AddParameter(((CShareReportBranchRecord*)pRecord)->GetCallChargeTruck());
			pCmd.AddParameter(((CShareReportBranchRecord*)pRecord)->GetCallChargeSubway());
			pCmd.AddParameter(((CShareReportBranchRecord*)pRecord)->GetCallChargeRiderCall());
			pCmd.AddParameter(((CShareReportBranchRecord*)pRecord)->GetRiderVRAccountPushType());

			pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
			if(!pCmd.Execute())		
			{
				MessageBox("변경중 오류가 발생했습니다.", "확인", MB_ICONERROR);
				return;
			}

		}
	}

	MessageBox("변경되었습니다.", "확인", MB_ICONINFORMATION);
	RefreshList();
}



void CShareReportBranchSetDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;
 
	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();
	CString strAccount = "";
	CXTPGridRecords *pRecords = m_wndReport.GetRecords();

	CShareReportBranchRecord *pRecord = (CShareReportBranchRecord*)pItemNotify->pRow->GetRecord();
	long nCompany = pRecord->m_nCompany;

	if(nCol == 15)
	{ 
		CDataBindDlg dlg("변경내역", 
				"select_callcenter_charge_change_log",
				new CMkParameter(nCompany));
		dlg.DoModal();
	}
	strAccount = pRecord->GetVRAccount();

	m_edtAccount.SetWindowText(strAccount);

}

void CShareReportBranchSetDlg::OnBnClickedDrawingBtn()
{
	if(!LF->POWER_CHECK(1040, "출금요청", TRUE))
		return;

	CRequestDrawingDlg dlg;
	dlg.DoModal();

}

void CShareReportBranchSetDlg::OnBnClickedIssueBtn()
{
	CString strAccount;
	m_edtAccount.GetWindowText(strAccount);

	if(strAccount.GetLength() > 7)
	{
		MessageBox("이미 계좌를 발급받은 상태입니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	long nCompany = 0;
	CShareReportBranchRecord *pReocrd = NULL;
	CXTPGridRow *pSelectedRow = m_wndReport.GetSelectedRows()->GetAt(0);
	if( pSelectedRow)
	{
		CShareReportBranchRecord *pSeletedRecord = 
			(CShareReportBranchRecord *)pSelectedRow->GetRecord();
		nCompany = pSeletedRecord->m_nCompany;
		
	}
	else
		return;

	if(nCompany <= 0 )
	{
		MessageBox("지사를 선택하여 주세요", "확인",MB_ICONINFORMATION);
		return;

	}



	CString strName = "[대리]" + m_ui.strName;

	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "insert_vitual_account_for_share_report");	
	CMkParameter *parRet = pCmd2.AddParameter(typeInt, typeOutput, sizeof(int), 0);
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long),nCompany);	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), 0);	
	pCmd2.AddParameter(typeString, typeInput, strName.GetLength(), strName);	


	if(pRs2.Execute(&pCmd2))
	{
		int nOutput = -1;
		parRet->GetValue(nOutput);
		if(nOutput == 1)
		{
			RefreshList();
			MessageBox("정상적으로 입력되었습니다.", "확인",MB_ICONINFORMATION);
			return;
		}
	}

	MessageBox("로지소프트로 문의하세요", "확인", MB_ICONINFORMATION);
}



void CShareReportBranchSetDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;  
	m_wndReport.GetWindowRect(&rect);

	if(!rect.PtInRect(point))
		return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->AppendMenu(MF_BYCOMMAND | MF_SEPARATOR, 0, "");

	CMenu *pSubMenu = new CMenu;
	pSubMenu->CreatePopupMenu();

	pRMenu->InsertMenu(2, MF_BYPOSITION | MF_POPUP, (UINT)pSubMenu->m_hMenu, "카드가맹점복사");


	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_company_card_info");
	cmd.AddParameter(m_ci.GetShareCode1());

	if(!rs.Execute(&cmd))
		return;

	long nCompany;
	CString strMID; 

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nCompany", nCompany);
		rs.GetFieldValue("sMID", strMID);

		pSubMenu->AppendMenu(MF_BYCOMMAND, EVENT_ID + i, strMID);
		m_nCompanyArry[i] = nCompany;
		rs.MoveNext();
	}

	pRMenu->AppendMenu(MF_STRING, ID_CARD_INFO_DELETE, "카드가맹복삭제");

	//menu.AppendMenu(MF_STRING,		ID_NO_FROZEN_COL,		"고정행렬 사용안함")
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	

	delete pSubMenu;
	pSubMenu = NULL;
}

void CShareReportBranchSetDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}