// ReportForm23.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "quick.h"
#include "ReportForm31.h"


// CReportForm31

IMPLEMENT_DYNCREATE(CReportForm31, CMyFormView)

CReportForm31::CReportForm31()
: CMyFormView(CReportForm31::IDD)
{

}

CReportForm31::~CReportForm31()
{
}

void CReportForm31::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtpFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtpTo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnData);
	DDX_Control(pDX, IDC_REPORT, m_lstReport);
	DDX_Control(pDX, IDC_RNO_EDIT, m_edtRNo);
	DDX_Control(pDX, IDC_TYPE_COMBO, m_cmbType);	
	DDX_Control(pDX, IDC_STATE_COMBO, m_cmbState);
}

BEGIN_MESSAGE_MAP(CReportForm31, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CReportForm31::OnBnClickedRefreshBtn)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_WM_CONTEXTMENU()
	ON_EN_CHANGE(IDC_RNO_EDIT, &CReportForm31::OnEnChangeRnoEdit)
	ON_CBN_SELCHANGE(IDC_STATE_COMBO, &CReportForm31::OnCbnSelchangeStateCombo)
END_MESSAGE_MAP()


// CReportForm31 진단입니다.

#ifdef _DEBUG
void CReportForm31::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CReportForm31::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CReportForm31 메시지 처리기입니다.

void CReportForm31::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	int nCol;
	SetResize(IDC_REPORT, sizingRightBottom);

	m_btnData.InitDateButton(&m_dtpFrom, &m_dtpTo);
	m_btnData.OnMenuMonth();

	m_cmbType.SetCurSel(0);
	m_cmbState.SetCurSel(0);

	nCol = 0;
	m_lstReport.InsertColumn(nCol++, "순번", LVCFMT_CENTER, 35);
	m_lstReport.InsertColumn(nCol++, "지사명", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(nCol++, "오더번호", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(nCol++, "날짜", LVCFMT_LEFT, 85);
	

	m_lstReport.InsertColumn(nCol++, "의뢰지", LVCFMT_LEFT, 130);
	m_lstReport.InsertColumn(nCol++, "부서/담당", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(nCol++, "출발지", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(nCol++, "도착지", LVCFMT_LEFT, 100);

	m_lstReport.InsertColumn(nCol++, "상태", LVCFMT_CENTER,	45);
	m_lstReport.InsertColumn(nCol++, "기사명", LVCFMT_CENTER,	60);
	m_lstReport.InsertColumn(nCol++, "사번", LVCFMT_RIGHT,	40);

	m_lstReport.InsertColumn(nCol++, "기본", LVCFMT_RIGHT,	60);
	m_lstReport.InsertColumn(nCol++, "추가", LVCFMT_RIGHT,	50);
	m_lstReport.InsertColumn(nCol++, "할인", LVCFMT_RIGHT,	50);
	m_lstReport.InsertColumn(nCol++, "합계", LVCFMT_RIGHT,	70);
	m_lstReport.InsertColumn(nCol++, "카드금액", LVCFMT_RIGHT,	70);
	m_lstReport.InsertColumn(nCol++, "탁송료", LVCFMT_RIGHT, 65);

	m_lstReport.InsertColumn(nCol++, "기사금액", LVCFMT_RIGHT, 70);	
	m_lstReport.InsertColumn(nCol++, "입금액", LVCFMT_RIGHT, 70);
	
	m_lstReport.InsertColumn(nCol++, "승인번호", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(nCol++, "결제종류", LVCFMT_RIGHT, 90);
	
	m_lstReport.SetFreezeColumnsCount(5);
	m_lstReport.SetOrderIndexCol(0);
	m_lstReport.Populate();
}

void CReportForm31::RefreshList()
{
	CMyFormView::RefreshList();
	UpdateData(TRUE);

	m_lstReport.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_card_rider_tax_case_by_case_4");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);
	cmd.AddParameter(m_cmbType.GetCurSel());
	cmd.AddParameter(m_cmbState.GetCurSel());	

	if(!rs.Execute(&cmd))
		return;


	CString strSSN, strRName, strSName, strDName, strSDong, strDDong,strBranchName,
		strOkNumber,sBCCardTranNumber, strOName, strManager;
	long nTNo, nDeposit,  nState, 
		nCardPayCompany, nCardCharge, nChargeDriving, nRNo;
	COleDateTime dt1;
	long nChargeRealS = 0, nChargeS = 0, nDepositS = 0, nTaxSoducS = 0, nTaxJuminS = 0, nTaxS = 0, nOrgAmtS = 0; 
	long nCreditCardType,nPayType,nChargeBasic, nChargeAdd, nChargeDis, nChargeSum, nChargeTrans;		
	int nCol;
	int i = 0;
	for(i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nTNo", nTNo);
		
		rs.GetFieldValue("sOName", strOName);
		rs.GetFieldValue("sManager", strManager);
		rs.GetFieldValue("nState", nState);
		rs.GetFieldValue("nPayType", nPayType);
		rs.GetFieldValue("dt1", dt1);		
		rs.GetFieldValue("sSName", strSName);
		rs.GetFieldValue("sSDong", strSDong);
		rs.GetFieldValue("sDName", strDName);
		rs.GetFieldValue("sDDong", strDDong);
		rs.GetFieldValue("sRName", strRName);
		rs.GetFieldValue("nRNo", nRNo);

		rs.GetFieldValue("nChargeBasic", nChargeBasic);
		rs.GetFieldValue("nChargeAdd", nChargeAdd);
		rs.GetFieldValue("nChargeDis", nChargeDis);
		rs.GetFieldValue("nChargeSum", nChargeSum);
		rs.GetFieldValue("nChargeTrans", nChargeTrans);
		rs.GetFieldValue("nChargeDriving", nChargeDriving);	
		rs.GetFieldValue("nDeposit", nDeposit);		
		rs.GetFieldValue("nCreditCardType", nCreditCardType);
		rs.GetFieldValue("nCardCharge", nCardCharge);

		rs.GetFieldValue("sBCCardTranNumber", sBCCardTranNumber);
		rs.GetFieldValue("nCardPayCompany", nCardPayCompany);
		rs.GetFieldValue("sBranchName", strBranchName);


			
		

		if(strSName != strSDong)
			strSName = strSName + "(" + strSDong + ")";

		if(strDName != strDDong)
			strDName = strDName + "(" + strDDong + ")";
		nCol = 1;

		m_lstReport.InsertItem(i, "");
		m_lstReport.SetItemText(i, nCol++, strBranchName);
		m_lstReport.SetItemText(i, nCol++, LF->GetStringFromLong(nTNo));
		m_lstReport.SetItemText(i, nCol++, dt1.Format("%y-%m-%d %H:%M"));
	
		m_lstReport.SetItemText(i, nCol++, strOName);
		m_lstReport.SetItemText(i, nCol++, strManager);
		m_lstReport.SetItemText(i, nCol++, strSName);
		m_lstReport.SetItemText(i, nCol++, strDName);		
		m_lstReport.SetItemText(i, nCol++, LF->GetStateString(nState));
		m_lstReport.SetItemText(i, nCol++, strRName);
		m_lstReport.SetItemText(i, nCol++, LF->GetMyNumberFormat(nRNo));

		m_lstReport.SetItemText(i, nCol++, LF->GetMyNumberFormat(nChargeBasic));
		m_lstReport.SetItemText(i, nCol++, LF->GetMyNumberFormat(nChargeAdd));
		m_lstReport.SetItemText(i, nCol++, LF->GetMyNumberFormat(nChargeDis));
		m_lstReport.SetItemText(i, nCol++, LF->GetMyNumberFormat(nChargeSum));
		m_lstReport.SetItemText(i, nCol++, LF->GetMyNumberFormat(nCardCharge));
		
		m_lstReport.SetItemText(i, nCol++, LF->GetMyNumberFormat(nChargeTrans));
		m_lstReport.SetItemText(i, nCol++, LF->GetMyNumberFormat(nChargeDriving));
		
		m_lstReport.SetItemText(i, nCol++, LF->GetMyNumberFormat(nDeposit));

		m_lstReport.SetItemText(i, nCol++, sBCCardTranNumber);
		m_lstReport.SetItemText(i, nCol++, GetCardClassType(nCardPayCompany));		
		m_lstReport.SetItemLong(i, nState);

		

		/*nChargeS += nCharge;
		nDepositS += nDeposit;
		nOrgAmtS += nOrgAmt;*/

		rs.MoveNext();
	}

	long nRecordCount = rs.GetRecordCount();

	if(nRecordCount > 0)
	{
		m_lstReport.InsertItem(nRecordCount, "");
		m_lstReport.SetItemText(i, 6, LF->GetMyNumberFormat(nChargeS));
		m_lstReport.SetItemText(i, 7, LF->GetMyNumberFormat(nDepositS));
		m_lstReport.SetItemText(i, 8, LF->GetMyNumberFormat(nOrgAmtS));
	}

	SearchFilter();
	//m_lstReport.Populate();
}



CString CReportForm31::GetCardClassType(long nClasCardType)
{

	CString strType = "";
	switch (nClasCardType)
	{
	case 0:
		strType = "";
		break;
	case 1:
		strType = "로지수기결제";
		break;
	case 2:
		strType = "대면결제";
		break;
	case 3:
		strType = "웹(온라인)결제";
		break;
	}
	return "N/A";

}
void CReportForm31::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CReportForm31::OnViewExcel()
{
	if(!LF->POWER_CHECK(3900, "정산 엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 324, m_lstReport.GetItemCount());  
	CMyExcel::ToExcel(&m_lstReport);
}
void CReportForm31::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CReportForm31::OnEnChangeRnoEdit()
{
	SearchFilter();
	/*
	CString strSearch; m_edtRNo.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString strSSN = m_lstReport.GetItemText(pRecord, 11);
		CString strRName = m_lstReport.GetItemText(pRecord, 12);
		strSSN.Replace("-", "");

		if(strSSN.Find(strSearch) >= 0 ||
			strRName.Find(strSearch) >= 0)
		{
			pRecord->SetVisible(TRUE);
		}
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstReport.Populate();
	*/
}


void CReportForm31::SearchFilter()
{
	long nIndex = m_cmbState.GetCurSel();
	CString strSearch; m_edtRNo.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString strSSN = m_lstReport.GetItemText(pRecord, 9);
		//CString strRName = m_lstReport.GetItemText(pRecord, 12);
		strSSN.Replace("-", "");

		BOOL bShow = FALSE;

		if(strSSN.Find(strSearch) >= 0)
		{
			bShow = TRUE;
		}

		if(bShow && nIndex > 0)
		{
			long nState = m_lstReport.GetItemLong(pRecord);

			if(nIndex == 1)
			{
				if(nState != STATE_ALLOCATED && nState != STATE_ALLOCATED && nState != STATE_FINISH)
					bShow = FALSE;
			}
			else if(nIndex == 2)
			{
				if(nState == STATE_OK_ONLY_MAN || nState == STATE_ALLOCATED || nState == STATE_FINISH)
					bShow = FALSE;
			}
		}

		pRecord->SetVisible(bShow);		
	}

	m_lstReport.Populate();
}

void CReportForm31::OnCbnSelchangeStateCombo()
{
	SearchFilter();
}
