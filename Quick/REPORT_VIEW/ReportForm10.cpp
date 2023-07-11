// ReportForm10.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm10.h"
#include "CommonDlg1.h"
#include "CommonDateDlg2.h"
#include "ReceiveMoneyDlg.h"
#include "StatForm6.h"
#include "OrderLogDetailDlg.h"
#include "RcpView.h"
#include "RcpDlgAdmin.h"

// CReportForm10

IMPLEMENT_DYNCREATE(CReportForm10, CMyFormView)

CReportForm10::CReportForm10()
: CMyFormView(CReportForm10::IDD)
, m_From(COleDateTime::GetCurrentTime())
, m_To(COleDateTime::GetCurrentTime())
{
}

CReportForm10::~CReportForm10()
{
	//m_wndReport.SaveReportOrder("CReportForm10", "m_wndReport");	
}

void CReportForm10::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_btnRefresh);
	DDX_Control(pDX, IDC_REPORT_LIST_NEW,m_wndReport);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_From);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_To);
	DDX_Control(pDX, IDC_TYPR_COMBO, m_cmbType);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_COMPLETE_BTN, m_btnComplete);
	DDX_Control(pDX, IDC_PERIOD_STATIC, m_stcPeriod);
	DDX_Control(pDX, IDC_PAY_TYPE_COMBO, m_cmbPayType);
	DDX_Control(pDX, IDC_STATIC1, m_stc1);
	DDX_Control(pDX, IDC_STATIC2, m_stc2);
	DDX_Control(pDX, IDC_COLUMN_COMBO, m_cmbColumn);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, ID_ALL_CHECK, m_chkAll);
	DDX_Control(pDX, IDC_INPUT_BTN, m_btnInput);
	DDX_Control(pDX, IDC_COLUMN_COMBO2, m_cmbColumn2);
	DDX_Control(pDX, IDC_SEARCH_EDIT2, m_edtSearch2);
	DDX_Control(pDX, ID_SHOW_SUM_CHECK, m_chkShowSum);
}

BEGIN_MESSAGE_MAP(CReportForm10, CMyFormView)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_LIST_NEW, OnReportItemClick)
	ON_BN_CLICKED(IDC_COMPLETE_BTN, OnBnClickedCompleteBtn)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
	ON_CBN_SELCHANGE(IDC_COLUMN_COMBO, OnCbnSelchangeColumnCombo)
	ON_NOTIFY(NM_RCLICK, IDC_REPORT_LIST_NEW, OnReportItemRClick)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(ID_ALL_CHECK, OnBnClickedAllCheck)
	ON_BN_CLICKED(IDC_INPUT_BTN, OnBnClickedInputBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_LIST_NEW, OnReportItemDblClick)
	ON_CBN_SELCHANGE(IDC_COLUMN_COMBO2, &CReportForm10::OnCbnSelchangeColumnCombo2)
	ON_EN_CHANGE(IDC_SEARCH_EDIT2, &CReportForm10::OnEnChangeSearchEdit2)
	ON_BN_CLICKED(ID_SHOW_SUM_CHECK, &CReportForm10::OnBnClickedShowSumCheck)
END_MESSAGE_MAP()


// CReportForm10 진단입니다.



// CReportForm10 메시지 처리기입니다.

void CReportForm10::OnBnClickedRefreshBtn()
{
	RefreshList();	
}

void CReportForm10::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_btnDate.InitDateButton(&m_dtFrom, &m_dtTo);
	m_btnDate.OnMenuMonth();

	CXTPGridColumn* pCol0 = m_wndReport.AddColumn(new CXTPGridColumn(0, _T("ⓒ"), 25));
	CXTPGridColumn *pCol1 = m_wndReport.AddColumn(new CXTPGridColumn(1, "오더번호", 100, TRUE));
	CXTPGridColumn *pCol2 = m_wndReport.AddColumn(new CXTPGridColumn(2, "접수회사", 120, TRUE));
	CXTPGridColumn *pCol3 = m_wndReport.AddColumn(new CXTPGridColumn(3, "접수시간", 120, TRUE));
	CXTPGridColumn *pCol4 = m_wndReport.AddColumn(new CXTPGridColumn(4, "의뢰자", 110, TRUE));
	CXTPGridColumn *pCol5 = m_wndReport.AddColumn(new CXTPGridColumn(5, "출발동", 110, TRUE));
	CXTPGridColumn *pCol6 = m_wndReport.AddColumn(new CXTPGridColumn(6, "도착동", 100, TRUE));
	CXTPGridColumn *pCol7 = m_wndReport.AddColumn(new CXTPGridColumn(7, "부서", 90, TRUE));
	CXTPGridColumn *pCol8 = m_wndReport.AddColumn(new CXTPGridColumn(8, "담당자", 90, TRUE));
	CXTPGridColumn *pCol9 = m_wndReport.AddColumn(new CXTPGridColumn(9, "탁송", 100, TRUE));
	CXTPGridColumn *pCol10 = m_wndReport.AddColumn(new CXTPGridColumn(10, "금액", 100, TRUE));
	CXTPGridColumn *pCol11 = m_wndReport.AddColumn(new CXTPGridColumn(11, "정산시DC금액", 100, TRUE));
	CXTPGridColumn *pCol12 = m_wndReport.AddColumn(new CXTPGridColumn(12, "입금", 80, TRUE));
	CXTPGridColumn *pCol13 = m_wndReport.AddColumn(new CXTPGridColumn(13, "입금일", 100, TRUE));
	CXTPGridColumn *pCol14 = m_wndReport.AddColumn(new CXTPGridColumn(14, "상태", 80, TRUE));
	CXTPGridColumn *pCol15 = m_wndReport.AddColumn(new CXTPGridColumn(15, "정산적요", 200, TRUE));
	CXTPGridColumn *pCol16 = m_wndReport.AddColumn(new CXTPGridColumn(16, "입금작업자", 120, TRUE));
	CXTPGridColumn *pCol17 = m_wndReport.AddColumn(new CXTPGridColumn(17, "오더적요", 200, TRUE));


	m_wndReport.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_wndReport.AllowEdit(FALSE);
	m_wndReport.SetGridColor(RGB(222, 222, 222));
	m_wndReport.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";

	m_wndReport.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnReorder(FALSE);
	m_wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_wndReport.AllowSort(FALSE);
	pCol0->SetSortable(FALSE);
	pCol1->SetSortable(FALSE);
	pCol2->SetSortable(FALSE);
	pCol3->SetSortable(FALSE);
	pCol4->SetSortable(FALSE);
	pCol5->SetSortable(FALSE);
	pCol6->SetSortable(FALSE);
	pCol7->SetSortable(FALSE);
	pCol8->SetSortable(FALSE);
	pCol9->SetSortable(FALSE);
	pCol10->SetSortable(FALSE);
	pCol11->SetSortable(FALSE);
	pCol12->SetSortable(FALSE);
	pCol13->SetSortable(FALSE);
	pCol14->SetSortable(FALSE);
	pCol15->SetSortable(FALSE);

	m_wndReport.Populate();

	m_cmbType.SetCurSel(AfxGetApp()->GetProfileInt("Report10", "Type", 0));
	m_cmbPayType.SetCurSel(AfxGetApp()->GetProfileInt("Report10", "PayType", 0));

	m_cmbColumn.SetCurSel(AfxGetApp()->GetProfileInt("Report10", "Column", 0));
	m_cmbColumn2.SetCurSel(AfxGetApp()->GetProfileInt("Report10", "Column1", 0));

	//m_wndReport.LoadReportOrder("CReportForm10", "m_wndReport");

	SetResize(IDC_REPORT_LIST_NEW, sizingRightBottom);
}

void CReportForm10::RefreshList()
{
	CMyFormView::RefreshList();

	static BOOL bFirst = TRUE;

	if(bFirst == TRUE) 
	{
		bFirst = FALSE;
		return;
	}

	AfxGetApp()->WriteProfileInt("Report10", "Type", m_cmbType.GetCurSel());
	AfxGetApp()->WriteProfileInt("Report10", "PayType", m_cmbPayType.GetCurSel());
	AfxGetApp()->WriteProfileInt("Report10", "Column", m_cmbColumn.GetCurSel());
	AfxGetApp()->WriteProfileInt("Report10", "Column1", m_cmbColumn2.GetCurSel());

	CXTPGridRecords *pRecords = m_wndReport.GetRecords();
	long nCount = pRecords->GetCount();

	m_wndReport.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb); 
	CMkCommand pCmd(m_pMkDb, "select_credit_order_7");

	COleDateTime dtFrom, dtTo;

	m_dtFrom.GetTime(dtFrom);
	m_dtTo.GetTime(dtTo);

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtTo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_cmbType.GetCurSel());
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_cmbPayType.GetCurSel());

	if(!pRs.Execute(&pCmd))
		return;

	long nTNo, nCompany, nOCNo, nPayType, nChargeSum, nChargeTrans, nTransferState, nChargeDisAfter;
	CString sOName, sSDong, sDDong, sEtc, sODepart, sOManager, strWName, strOrderEtc;
	COleDateTime dt1, dtInput;
	long nPrevOCNo = 0, nInsertSum = 0;
	CString strPrevOName;

	long nChargeSumAll = 0;
	long nItem = 0;

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nOCNo", nOCNo);
		pRs.GetFieldValue("nPayType", nPayType);
		pRs.GetFieldValue("nChargeSum", nChargeSum);
		pRs.GetFieldValue("nChargeTrans", nChargeTrans);
		pRs.GetFieldValue("nTransferState", nTransferState);
		pRs.GetFieldValue("sOName", sOName);
		pRs.GetFieldValue("sSDong", sSDong);
		pRs.GetFieldValue("sDDong", sDDong);
		pRs.GetFieldValue("dt1", dt1);
		pRs.GetFieldValue("nChargeDisAfter", nChargeDisAfter);
		pRs.GetFieldValue("sEtc", sEtc);
		pRs.GetFieldValue("dtInput", dtInput);
		pRs.GetFieldValue("sODepart", sODepart);
		pRs.GetFieldValue("sOManager", sOManager);
		pRs.GetFieldValue("sWName", strWName);
		pRs.GetFieldValue("sOrderEtc", strOrderEtc);

		if(nPrevOCNo != 0 && nPrevOCNo != nOCNo)
		{
			m_wndReport.InsertItem(nItem, ""); 
			m_wndReport.SetItemText(nItem, 2, strPrevOName);
			m_wndReport.SetItemText(nItem, 9, "합계");
			m_wndReport.SetItemText(nItem, 10, LF->GetMyNumberFormat(nChargeSumAll));
			m_wndReport.SetItemLong(nItem,1);
			m_wndReport.SetItemNoSort(nItem, TRUE);
			m_wndReport.SetItemDataText(nItem++, "합계");
			nInsertSum = 0;
			nChargeSumAll = 0;
		}
		nChargeSumAll += nChargeSum;

		m_wndReport.InsertCheckItem(nItem, "", -1, FALSE);
		m_wndReport.SetItemText(nItem, 1, LF->GetStringFromLong(nTNo));
		m_wndReport.SetItemText(nItem, 2, m_ci.GetBranchName(nCompany));
		m_wndReport.SetItemText(nItem, 3, dt1.Format("%m-%d %H:%M"));
		m_wndReport.SetItemText(nItem, 4, sOName);
		m_wndReport.SetItemText(nItem, 5, sSDong);
		m_wndReport.SetItemText(nItem, 6, sDDong);
		m_wndReport.SetItemText(nItem, 7, sODepart);
		m_wndReport.SetItemText(nItem, 8, sOManager);
		m_wndReport.SetItemText(nItem, 9, LF->GetMyNumberFormat(nChargeTrans));
		m_wndReport.SetItemText(nItem, 10, LF->GetMyNumberFormat(nChargeSum));

		if(nChargeDisAfter == 0) 
			m_wndReport.SetItemText(nItem, 11, LF->GetMyNumberFormat(nChargeSum));
		else
			m_wndReport.SetItemText(nItem, 11, LF->GetMyNumberFormat(nChargeDisAfter));

		m_wndReport.SetItemText(nItem, 12, LF->GetPayTypeFromLong(nPayType));
		if(nTransferState == 0 || dtInput.m_status == 2)
			m_wndReport.SetItemText(nItem, 13, "");
		else
			m_wndReport.SetItemText(nItem, 13, dtInput.Format("%y-%m-%d %H:%M"));
		m_wndReport.SetItemText(nItem, 14, GetInputType(nTransferState));
		m_wndReport.SetItemText(nItem, 15, sEtc);
		m_wndReport.SetItemText(nItem, 16, strWName);
		m_wndReport.SetItemText(nItem, 17, strOrderEtc);

		m_wndReport.SetItemLong(nItem, nOCNo);
		m_wndReport.SetItemLong2(nItem, nTransferState);
		m_wndReport.SetItemLong3(nItem, nTNo);
		m_wndReport.SetItemData(nItem, nPayType);
		m_wndReport.SetItemNoSort(nItem++, FALSE);

		nPrevOCNo = nOCNo;
		strPrevOName = sOName;
		nInsertSum++;
 
		pRs.MoveNext();
	}

	if(nInsertSum > 0)
	{
		m_wndReport.InsertItem(nItem, "");
		m_wndReport.SetItemText(nItem, 2, strPrevOName);
		m_wndReport.SetItemText(nItem, 9, "합계");
		m_wndReport.SetItemText(nItem, 10, LF->GetMyNumberFormat(nChargeSumAll));
		m_wndReport.SetItemLong(nItem,1);
		m_wndReport.SetItemNoSort(nItem, TRUE);
		m_wndReport.SetItemDataText(nItem++, "합계");
		nChargeSumAll = 0;
	}

	OnEnChangeSearchEdit();
}

void CReportForm10::RefreshCount()
{
 	CXTPGridRows *pRows = m_wndReport.GetRows();
	CXTPGridColumn *pColumn = NULL;

	CString strPrevOName;
	long nChargeTrans = 0, nChargeDisAfter = 0, nPayType = 0;

	ST_REPORT10_CHARGE stData, stTotalData;
	INIT_REPORT10_STRUCT(stData);
	INIT_REPORT10_STRUCT(stTotalData);

	long nRowCount = pRows->GetCount();
	for(int i = 0; i < pRows->GetCount(); i++)
	{
		CXTPGridRow *pRow = pRows->GetAt(i);
		CXTPGridRecord *pRecord = pRow->GetRecord();
		CString strRecordData = m_wndReport.GetItemDataText(pRecord);

		if(strRecordData.GetLength() > 0)
		{
			stTotalData.nOCNoCount += stData.nOCNoCount;
			stTotalData.nOCNoCountTrans += stData.nOCNoCountTrans;
			stTotalData.nOCNoChargeTrans += stData.nOCNoChargeTrans;
			stTotalData.nOCNoChargeSum += stData.nOCNoChargeSum;
			stTotalData.nOCNoChargeDisAfter += stData.nOCNoChargeDisAfter;
			stTotalData.nOCNoCountCredit += stData.nOCNoCountCredit;
			stTotalData.nOCNoChargeCredit += stData.nOCNoChargeCredit;
			stTotalData.nOCNoCountOnline += stData.nOCNoCountOnline;
			stTotalData.nOCNoChargeOnline += stData.nOCNoChargeOnline;
			stTotalData.nCompleteCount += stData.nCompleteCount;
			stTotalData.nNotCompleteCount += stData.nNotCompleteCount;

			m_wndReport.SetItemText(pRecord, 3, "건수 : " + LF->GetStringFromLong(stData.nOCNoCount));
			m_wndReport.SetItemText(pRecord, 4, "금액 : " + LF->GetMyNumberFormat(stData.nOCNoChargeSum));
			m_wndReport.SetItemText(pRecord, 5, "DC금액 : " + LF->GetMyNumberFormat(stData.nOCNoChargeDisAfter));
			m_wndReport.SetItemText(pRecord, 6, "탁송 " + LF->GetStringFromLong(stData.nOCNoCountTrans) + "건");
			m_wndReport.SetItemText(pRecord, 7, LF->GetMyNumberFormat(stData.nOCNoChargeTrans));
			m_wndReport.SetItemText(pRecord, 8, "신용 " + LF->GetStringFromLong(stData.nOCNoCountCredit) + "건");
			m_wndReport.SetItemText(pRecord, 9, LF->GetMyNumberFormat(stData.nOCNoChargeCredit));
			m_wndReport.SetItemText(pRecord, 10, "송금 " + LF->GetStringFromLong(stData.nOCNoCountOnline) + "건");
			m_wndReport.SetItemText(pRecord, 11, LF->GetMyNumberFormat(stData.nOCNoChargeOnline));
			m_wndReport.SetItemText(pRecord, 12, "입금 " + LF->GetStringFromLong(stData.nCompleteCount) + "건");
			m_wndReport.SetItemText(pRecord, 13, "미입금 " + LF->GetStringFromLong(stData.nNotCompleteCount) + "건");

			INIT_REPORT10_STRUCT(stData);
		}
		else
		{
			nPayType = m_wndReport.GetItemData(pRecord);

			stData.nOCNoCount++;
			stData.nOCNoChargeSum += LF->GetRemoveMyNumberFormat(m_wndReport.GetItemText(pRecord, 10));
			nChargeTrans = LF->GetRemoveMyNumberFormat(m_wndReport.GetItemText(pRecord, 9));
			stData.nOCNoChargeTrans += nChargeTrans;
			stData.nOCNoCountTrans += nChargeTrans == 0 ? 0 : 1;
			nChargeDisAfter = LF->GetRemoveMyNumberFormat(m_wndReport.GetItemText(pRecord, 11));
			stData.nOCNoChargeDisAfter += nChargeDisAfter;
			if(nPayType == 2)
			{
				stData.nOCNoChargeCredit += nChargeDisAfter;
				stData.nOCNoCountCredit++;
			}
			else
			{
				stData.nOCNoChargeOnline += nChargeDisAfter;
				stData.nOCNoCountOnline++;
			}

			if(m_wndReport.GetItemLong2(pRecord) == 1)
				stData.nCompleteCount++;
			else
				stData.nNotCompleteCount++;
		}
	}

	long nRecordCount = m_wndReport.GetRecords()->GetCount();

	if(stTotalData.nOCNoCount > 0)
	{
		CString sTrans; sTrans.Format("%s건 %s원", LF->GetMyNumberFormat(stTotalData.nOCNoCountTrans), LF->GetMyNumberFormat(stTotalData.nOCNoChargeTrans));
		CString sCredit; sCredit.Format("%s건 %s원", LF->GetMyNumberFormat(stTotalData.nOCNoCountCredit), LF->GetMyNumberFormat(stTotalData.nOCNoChargeCredit));
		CString sOnline; sOnline.Format("%s건 %s원", LF->GetMyNumberFormat(stTotalData.nOCNoCountOnline), LF->GetMyNumberFormat(stTotalData.nOCNoChargeOnline));
		CString sTransfetState; sTransfetState.Format("입금 : %s건 미입급 : %s건", LF->GetMyNumberFormat(stTotalData.nCompleteCount), LF->GetMyNumberFormat(stTotalData.nNotCompleteCount));

		m_wndReport.InsertItem(nRecordCount, "");
		m_wndReport.SetItemNoSort(nRecordCount++, TRUE);

		m_wndReport.InsertItem(nRecordCount, "");
		m_wndReport.SetItemText(nRecordCount, 3, "총건수");
		m_wndReport.SetItemText(nRecordCount, 4, "금액");
		m_wndReport.SetItemText(nRecordCount, 5, "정산시DC금액");
		m_wndReport.SetItemText(nRecordCount, 6, "탁송");
		m_wndReport.SetItemText(nRecordCount, 7, "신용");
		m_wndReport.SetItemText(nRecordCount, 8, "송금");
		m_wndReport.SetItemText(nRecordCount, 9, "입금");
		m_wndReport.SetItemText(nRecordCount, 10, "금액+탁송");
		m_wndReport.SetItemNoSort(nRecordCount++, TRUE);

		m_wndReport.InsertItem(nRecordCount, "");
		m_wndReport.SetItemText(nRecordCount, 3, LF->GetMyNumberFormat(stTotalData.nOCNoCount));
		m_wndReport.SetItemText(nRecordCount, 4, LF->GetMyNumberFormat(stTotalData.nOCNoChargeSum));
		m_wndReport.SetItemText(nRecordCount, 5, LF->GetMyNumberFormat(stTotalData.nOCNoChargeDisAfter));
		m_wndReport.SetItemText(nRecordCount, 6, sTrans);
		m_wndReport.SetItemText(nRecordCount, 7, sCredit);
		m_wndReport.SetItemText(nRecordCount, 8, sOnline);
		m_wndReport.SetItemText(nRecordCount, 9, sTransfetState);
		m_wndReport.SetItemText(nRecordCount, 10, LF->GetMyNumberFormat(stTotalData.nOCNoChargeSum + stTotalData.nOCNoChargeTrans));


		m_wndReport.SetItemNoSort(nRecordCount++, TRUE);

		m_wndReport.Populate();
	}
}

void CReportForm10::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	CXTPGridRecord *pRecord = (CXTPGridRecord*)pItemNotify->pRow->GetRecord();
	if(m_wndReport.GetItemNoSort(pRecord))
		return;

	if(nCol == TRANSFER_STATE_COL) 
	{
		nRow = pRecord->GetIndex();

		long nTNo = m_wndReport.GetItemLong3(pRecord);
		long nTransferState = m_wndReport.GetItemLong2(pRecord);

		CString sMsg;

		long nRet = 0;

		if(nTransferState == 0)
		{
			nRet = MessageBox("입금/미입금 상태 변경!!\r\n[   예   ] 입금\r\n[아니요] 부분입금", "확인", MB_YESNOCANCEL);
			if(nRet == IDYES){nRet = 1;} else if(nRet == IDNO){nRet = 2;} else nRet = 3;
		}
		else if(nTransferState == 1)
		{
			nRet = MessageBox("입금/미입금 상태 변경!!\r\n[   예   ] 부분입금\r\n[아니요] 미입금", "확인", MB_YESNOCANCEL);
			if(nRet == IDYES){nRet = 2;} else if(nRet == IDNO){nRet = 0;} else nRet = 3;
		}
		else if(nTransferState == 2)
		{
			nRet = MessageBox("입금/미입금 상태 변경!!\r\n[   예   ] 입금\r\n[아니요] 미입금", "확인", MB_YESNOCANCEL);
			if(nRet == IDYES){nRet = 1;} else if(nRet == IDNO){nRet = 0;} else nRet = 3;
		}

		if(nRet == 3) return;

		IncomeComplete(nTNo, pRecord, nRet);
		m_wndReport.Populate();
	}
	else if(nCol == TRANSFER_ETC_COL)
	{ 
		long nTNo = m_wndReport.GetItemLong3(pRecord);
		CString sEtc = m_wndReport.GetItemText(pRecord, TRANSFER_ETC_COL);


		CCommonDlg1 dlg;
		dlg.m_strEdit = sEtc;

		if(dlg.DoModal() == IDOK)
		{
			CMkCommand pCmd(m_pMkDb, "update_transfer_etc");
			pCmd.AddParameter(nTNo);
			pCmd.AddParameter(dlg.m_strEdit);

			if(pCmd.Execute())
			{
				m_wndReport.SetItemText(pRecord, TRANSFER_ETC_COL, dlg.m_strEdit);
				m_wndReport.Populate();
			}
		}
	}
	else if(nCol == TRANSFER_DATE_COL)
	{
		long nTNo = m_wndReport.GetItemLong3(pRecord);
		CString sDate = m_wndReport.GetItemText(pRecord, TRANSFER_DATE_COL);

		COleDateTime dtDate(atoi(sDate.Left(4)), atoi(sDate.Mid(5, 2)), atoi(sDate.Mid(8, 2)), 0, 0, 0);

		CCommonDateDlg2 dlg;
		dlg.m_Date = dtDate;

		if(dlg.DoModal() == IDOK)
		{
			CMkCommand pCmd(m_pMkDb, "update_transfer_income_date");
			pCmd.AddParameter(nTNo);
			pCmd.AddParameter(dlg.m_Date);

			if(pCmd.Execute())
			{
				CString sDate = dlg.m_Date.Format("%y-%m-%d %H:%M");
				m_wndReport.SetItemText(pRecord, TRANSFER_DATE_COL, sDate);

				m_wndReport.Populate();
			}
		}

	}

}

void CReportForm10::IncomeComplete(long nTNo, CXTPGridRecord *pRecord, long nTransferState)
{
	long nRet = 0;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_creditorder_transfer_state_3");

	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long), 0);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTransferState);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.strName);


	if(!pRs.Execute(&pCmd)) return;

	pPar->GetValue(nRet);

	m_wndReport.SetItemLong2(pRecord, nTransferState);

	if(nTransferState == 1 || nTransferState == 2) 
	{
		COleDateTime dtDate = COleDateTime::GetCurrentTime();
		m_wndReport.SetItemText(pRecord, TRANSFER_DATE_COL, dtDate.Format("%y-%m-%d %H:%M"));

		CString sTemp = nTransferState == 1 ? "입금완료" : "부분입금";
		m_wndReport.SetItemText(pRecord, TRANSFER_STATE_COL, sTemp);
	}
	else
	{
		m_wndReport.SetItemText(pRecord, TRANSFER_STATE_COL, "미입금");
		m_wndReport.SetItemText(pRecord, TRANSFER_DATE_COL, "");
	}

	m_wndReport.Populate();
};

void CReportForm10::OnBnClickedCompleteBtn() 
{
	//m_wndReport.LoadReportOrder("CReportForm10", "m_wndReport");
	long nCount = m_wndReport.GetRecords()->GetCount();

	CXTPGridRows *pRows = m_wndReport.GetRows();

	for(int i=0; i<nCount; i++) 
	{
		CXTPGridRecord *pRecord = (CXTPGridRecord*)m_wndReport.GetRecords()->GetAt(i);

		if((pRecord->IsVisible()) &&
			(m_wndReport.GetChecked(pRecord, 0) == TRUE) &&
			!pRecord->GetItem(1)->GetCaption(NULL).IsEmpty())
		{
			long nTNo = m_wndReport.GetItemLong3(pRecord);
			long nTransferState = m_wndReport.GetItemLong2(pRecord);
			IncomeComplete(nTNo, pRecord, 1);
		}
	}

	m_wndReport.Populate();
}

void CReportForm10::SearchData(CString sData, long nColumn, CString sData2, long nColumn2)
{
	CXTPGridRecords *pRecords = m_wndReport.GetRecords();
	CXTPGridColumn *pColumn = NULL;

	long nRecord = pRecords->GetCount();
	long nItem = 0;
	BOOL bFindItem = FALSE;

	for(int i=0; i<nRecord; i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(nItem);

		if(m_wndReport.GetItemNoSort(pRecord))
		{
			CString strDataText = m_wndReport.GetItemDataText(pRecord);
			long bChargeSum = m_wndReport.GetItemLong(pRecord);
			if(strDataText.GetLength() == 0 && bChargeSum == 0)
				m_wndReport.GetRecords()->RemoveAt(nItem);
			else if(!bFindItem)
			{
				pRecord->SetVisible(FALSE);
				nItem++;
			}
			else
			{
				pRecord->SetVisible(TRUE);
				bFindItem = FALSE;
				nItem++;
			}

			continue;
		}

		CString sItem = ((CXTPGridRecordItemText*)pRecord->GetItem(nColumn))->GetCaption(NULL);
		CString sItem2 = ((CXTPGridRecordItemText*)pRecord->GetItem(nColumn2))->GetCaption(NULL);

		if(sItem.Find(sData) >= 0 && sItem2.Find(sData2) >= 0)
		{
			pRecord->SetVisible(TRUE);
			bFindItem = TRUE;
		}
		else
			pRecord->SetVisible(FALSE);

		nItem++;
	}

	m_wndReport.Populate();
}

void CReportForm10::OnEnChangeSearchEdit()
{
	FIlterData();
}

void CReportForm10::FIlterData()
{
	long nIndex = m_cmbColumn.GetCurSel();
	long nIndex2 = m_cmbColumn2.GetCurSel();

	CString str; m_edtSearch.GetWindowText(str);
	CString str2; m_edtSearch2.GetWindowText(str2);

	if(nIndex == 5) nIndex = 1;
	else nIndex = nIndex + 4;

	if(nIndex2 == 5) nIndex2 = 1;
	else nIndex2 = nIndex2 + 4;

	SearchData(str, nIndex, str2, nIndex2);

	RefreshCount();
}

void CReportForm10::OnCbnSelchangeColumnCombo()
{
	FIlterData();
}

void CReportForm10::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_wndReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CReportForm10::OnViewExcel()
{
	if(!LF->POWER_CHECK(3900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 310, m_ui.nWNo, m_wndReport.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_wndReport);
}

void CReportForm10::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_wndReport, pt);

}


BOOL CReportForm10::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_LBUTTONUP)
	{ 
		CRect rc;
		m_wndReport.GetWindowRect(rc);

		CPoint pt; ::GetCursorPos(&pt);

		if(rc.PtInRect(pt))
		{
			long nSelCount = m_wndReport.GetSelectedRows()->GetCount();

			if(nSelCount > 1)
			{
				//				OnReportItemClick(NULL, NULL);
				CXTPGridSelectedRows * pRows = m_wndReport.GetSelectedRows();

				for(int i=0; i<nSelCount; i++) 
				{
					CXTPGridRow *pRow = pRows->GetAt(i);
					CXTPGridRecord* pRecord = pRow->GetRecord();

					BOOL bCheck = m_wndReport.GetChecked(pRecord, 0);
					m_wndReport.SetChecked(pRecord, 0, !bCheck);

					//m_wndReport.Populate();
				}

				m_wndReport.Populate();
				return TRUE;
			}

		}
	}
	return CMyFormView::PreTranslateMessage(pMsg);
}

void CReportForm10::OnBnClickedAllCheck()
{
	BOOL bCheck = m_chkAll.GetCheck();

	long nCount = m_wndReport.GetRecords()->GetCount();

	for(int i=0; i<nCount; i++)
	{
		CXTPGridRecord *pRecord = m_wndReport.GetRecords()->GetAt(i);

		if(pRecord->IsVisible())
			m_wndReport.SetChecked(pRecord, 0, bCheck);
	}

	m_wndReport.Populate();

}

void CReportForm10::OnBnClickedInputBtn()
{
	CReceiveMoneyDlg dlg;
	dlg.m_bIntegrated = m_ba.GetCount() > 1 ? TRUE : FALSE;	
	dlg.m_nCompany = LF->GetCurBranchInfo()->nCompanyCode;
	dlg.DoModal();
}

CString CReportForm10::GetInputType(long nType)
{
	if(nType == 0) //미입금
		return "미입금";
	else if(nType == 1) 
		return "입금완료";
	else if(nType == 2) 
		return "부분입금";
	else
		return "알수없음";
}

void CReportForm10::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridSelectedRows *pRows = m_wndReport.GetSelectedRows();

	if(pRows == NULL){MessageBox("해당 로우를 선택하세요", "확인", MB_ICONINFORMATION); return;};
	if(pRows->GetCount() == 0){MessageBox("해당 로우를 선택하세요", "확인", MB_ICONINFORMATION); return;};

	CString strTNo = m_wndReport.GetItemText(pRows->GetAt(0)->GetRecord(), 1);
	strTNo.Replace("오더 " , "");

	if(!LF->IsNumeric(strTNo)) return;
	if(atoi(strTNo) < 100000) return;

	CString strCName; long nState;

	if(LF->IsCrossOrder(atoi(strTNo), strCName, nState))
	{ 
		COrderLogDetailDlg DetailLog;
		//DetailLog.m_pCurDb = IsSecondServerOrder(nSelItem) ? m_pMkSecondDb : m_pMkDb;
		DetailLog.m_nTNo = atoi(strTNo);
		DetailLog.m_bCross = TRUE;
		DetailLog.DoModal();

		return;
	}

	if(!LF->POWER_CHECK(2001, "접수창 열기", TRUE))
		return;

	if(!LU->GetRcpView()) {
		MessageBox("접수탭으로 이동한 후 다시 시도하세요", "확인", MB_ICONINFORMATION); 
		return;
	}

	LU->GetRcpDlgAdmin()->CreateRcpDlg(NULL,
		strCName,
		atoi(strTNo), 
		nState, "", FALSE, -1, 0, 0, FALSE, "");
}

void CReportForm10::OnCbnSelchangeColumnCombo2()
{
	FIlterData();
}

void CReportForm10::OnEnChangeSearchEdit2()
{
	FIlterData();
}

void CReportForm10::OnBnClickedShowSumCheck()
{
	CXTPGridRecords *pRecords = m_wndReport.GetRecords();
	BOOL bShowSum = m_chkShowSum.GetCheck();

	long nRecord = pRecords->GetCount();

	for(int i=0; i<nRecord; i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		if(bShowSum && m_wndReport.GetItemNoSort(pRecord) == FALSE)
			pRecord->SetVisible(FALSE);
		else
			pRecord->SetVisible(TRUE);
	}

	m_wndReport.Populate();
	
}
