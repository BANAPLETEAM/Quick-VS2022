// RiderReportOrderDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderReportOrderDlg.h"
#include "RcpView.h"

// CRiderReportOrderDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderReportOrderDlg, CMyDialog)
CRiderReportOrderDlg::CRiderReportOrderDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderReportOrderDlg::IDD, pParent)
{
}

CRiderReportOrderDlg::~CRiderReportOrderDlg()
{
}

void CRiderReportOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_ORDER_LIST, m_ReportOrderList);
}

void CRiderReportOrderDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	long nState = m_ReportOrderList.GetItemLong(nRow);
	long nTNo = _ttoi(m_ReportOrderList.GetItemText(nRow, 1));
	CString sOName = m_ReportOrderList.GetItemText(nRow, 3);
	
	CString sType = m_ReportOrderList.GetItemText(nRow, 10);

	if(sType.Find("타사") >= 0)
	{
		MessageBox("크로스 배차된 오더는 수정하실 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}
	
	
	LU->GetRcpView()->CreateRcpDlg(NULL, 
		sOName,
		nTNo, 
		nState);
}


BEGIN_MESSAGE_MAP(CRiderReportOrderDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_ORDER_LIST, OnReportItemDblClick)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CRiderReportOrderDlg 메시지 처리기입니다.

void CRiderReportOrderDlg::OnBnClickedRefreshBtn()
{
	m_ReportOrderList.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_dorder_for_fixed_depost_1");
 
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRiderCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRNo);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);

	CMkParameter *pMyCashApplyCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pOtherCashApplyCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pMyCreditApplyCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pOtherCreditApplyCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pMyOnlineApplyCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pOtherOnlineApplyChare = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(!pRs.Execute(&pCmd)) return;

	pMyCashApplyCharge->GetValue(m_nMyCashApplyCharge);
	pOtherCashApplyCharge->GetValue(m_nOtherCashApplyCharge);
	pMyCreditApplyCharge->GetValue(m_nMyCreditApplyCharge);
	pOtherCreditApplyCharge->GetValue(m_nOtherCreditApplyCharge);
	pMyOnlineApplyCharge->GetValue(m_nMyOnlineApplyCharge);
	pOtherOnlineApplyChare->GetValue(m_nOtherOnlineApplyChare);

	long nCompany, nState, nTNo, nChargeSum, nChargeTrans, nPayType, nShareCode1, nRiderShareCode1, nCouponCharge;
	COleDateTime dt1;
	CString sOName, sSName, sDName;
	char buffer[20];
	long nSSum = 0, nSTrans = 0, nSCoupon = 0;
	long nItem = 0;
	long nSCredit = 0, nSCreditCount = 0, nSCash = 0, nSCashCount = 0, nSOnline = 0, nSOnlineCount = 0;
	long nSACount = 0, nSACharge = 0, nSACoupon = 0, nSATrans = 0;
	long nSNCount = 0, nSNCharge = 0, nSNCoupon = 0, nSNTrans = 0;
	BOOL bGiveChargeToRider;
	
	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("nChargeSum", nChargeSum);
		pRs.GetFieldValue("nChargeTrans", nChargeTrans);
		pRs.GetFieldValue("nShareCode1", nShareCode1);
		pRs.GetFieldValue("nRiderShareCode1", nRiderShareCode1);
		pRs.GetFieldValue("dt1", dt1);
		pRs.GetFieldValue("sOName", sOName);
		pRs.GetFieldValue("sSName", sSName);
		pRs.GetFieldValue("sDName", sDName);
		pRs.GetFieldValue("nPayType", nPayType);
		pRs.GetFieldValue("nCouponCharge", nCouponCharge);
		pRs.GetFieldValue("bGiveChargeToRider", bGiveChargeToRider);

		nSSum += nChargeSum;
		nSTrans += nChargeTrans;
		nSCoupon += nCouponCharge;

		if(nPayType == 0 || nPayType == 1 || nPayType == 4)
		{
			nSCashCount++;
			nSCash += nChargeSum;
		}
		else if(nPayType == 2)
		{
			if(bGiveChargeToRider == FALSE)
			{
				nSCreditCount++;
				nSCredit += nChargeSum;
			}
		}
		else
		{
			if(bGiveChargeToRider == FALSE)
			{
				nSOnlineCount++;
				nSOnline += nChargeSum;
			}
		}

		m_ReportOrderList.InsertItem(nItem, m_ci.GetName(nCompany));
		m_ReportOrderList.SetItemText(nItem, 1, itoa(nTNo, buffer, 10));
		m_ReportOrderList.SetItemText(nItem, 2, dt1.Format("%m-%d %H:%M"));
		m_ReportOrderList.SetItemText(nItem, 3, sOName);
		m_ReportOrderList.SetItemText(nItem, 4, sSName);
		m_ReportOrderList.SetItemText(nItem, 5, sDName);
		m_ReportOrderList.SetItemText(nItem, 6, LF->GetMyNumberFormat(nChargeSum));
		m_ReportOrderList.SetItemText(nItem, 7, LF->GetMyNumberFormat(nCouponCharge));
		m_ReportOrderList.SetItemText(nItem, 8, LF->GetMyNumberFormat(nChargeTrans));
		m_ReportOrderList.SetItemText(nItem, 9, LF->GetPayTypeFromLong(nPayType, FALSE));
		m_ReportOrderList.SetItemText(nItem, 10, GetType(nShareCode1, nRiderShareCode1, nPayType));

		CString sType = GetApply(GetType(nShareCode1, nRiderShareCode1, nPayType), nChargeSum, bGiveChargeToRider);
		m_ReportOrderList.SetItemText(nItem, 11, sType);
        
		if(sType == "○")
		{
			nSACount++;
			nSACharge += nChargeSum;
			nSACoupon += nCouponCharge;
			nSATrans += nChargeTrans;
			m_ReportOrderList.SetItemText(nItem, 12, "");
		}
		else
		{
			nSNCount++;
			nSNCharge += nChargeSum;
			nSNCoupon += nCouponCharge;
			nSNTrans += nChargeTrans;

			if(bGiveChargeToRider == TRUE)
				m_ReportOrderList.SetItemText(nItem, 12, "이체함");
			else
				m_ReportOrderList.SetItemText(nItem, 12, "적용금액미달");
		}
        
		m_ReportOrderList.SetItemLong(nItem++, nState);

		pRs.MoveNext();
	}

	if(pRs.GetRecordCount() >= 0)
	{
		m_ReportOrderList.InsertItem(nItem, ""); 
		m_ReportOrderList.SetItemText(nItem, 5, " 합 계 :");
		m_ReportOrderList.SetItemText(nItem, 6, LF->GetMyNumberFormat(nSSum));
		m_ReportOrderList.SetItemText(nItem, 7, LF->GetMyNumberFormat(nSCoupon));
		m_ReportOrderList.SetItemText(nItem++, 8, LF->GetMyNumberFormat(nSTrans));

		m_ReportOrderList.InsertItem(nItem ++, "");

		m_ReportOrderList.InsertItem(nItem, ""); 
		m_ReportOrderList.SetItemText(nItem, 3, "현금");
		m_ReportOrderList.SetItemText(nItem, 4, "신용");
		m_ReportOrderList.SetItemText(nItem++, 5, "송금");


		m_ReportOrderList.InsertItem(nItem, "");
		m_ReportOrderList.SetItemText(nItem, 2, "지불 : ");

		m_ReportOrderList.SetItemText(nItem, 3, LF->GetMyNumberFormat(nSCashCount) + "/" + LF->GetMyNumberFormat(nSCash));
		m_ReportOrderList.SetItemText(nItem, 4, LF->GetMyNumberFormat(nSCreditCount) + "/" + LF->GetMyNumberFormat(nSCredit));
		m_ReportOrderList.SetItemText(nItem++, 5,  LF->GetMyNumberFormat(nSOnlineCount) + "/" + LF->GetMyNumberFormat(nSOnline));

		m_ReportOrderList.InsertItem(nItem++, "");

		m_ReportOrderList.InsertItem(nItem, "");
		m_ReportOrderList.SetItemText(nItem, 2, " 적용 : ");
		m_ReportOrderList.SetItemText(nItem, 3, LF->GetMyNumberFormat(nSACount) + "/" + LF->GetMyNumberFormat(nSACharge));
		m_ReportOrderList.SetItemText(nItem, 5, " 비적용 : ");
		m_ReportOrderList.SetItemText(nItem, 6, LF->GetMyNumberFormat(nSNCount) + "/" + LF->GetMyNumberFormat(nSNCharge));

	}

	m_ReportOrderList.Populate();
}

CString CRiderReportOrderDlg::GetApply(CString sType, long nCharge, BOOL bGiveChargeToRider)
{
	BOOL bApply = FALSE;

	if(bGiveChargeToRider == TRUE)
	{
		bApply = FALSE;
	}
	else if(sType == "자사현금")
	{
		if(nCharge >= m_nMyCashApplyCharge)
			bApply = TRUE;
	}
	else if(sType == "자사신용")
	{
		if(nCharge >= m_nMyCreditApplyCharge)
			bApply = TRUE;
	}
	else if(sType == "자사송금")
	{
		if(nCharge >= m_nMyOnlineApplyCharge)
			bApply = TRUE;
	}
	else if(sType == "타사현금")
	{
		if(nCharge >= m_nOtherCashApplyCharge)
			bApply = TRUE;
	}
	else if(sType == "타사신용")
	{
		if(nCharge >= m_nOtherCreditApplyCharge)
			bApply = TRUE;
	}
	else if(sType == "타사송금")
	{
		if(nCharge >= m_nOtherOnlineApplyChare)
			bApply = TRUE;
	}

	if(bApply)
		return "○";
	else
		return "X";

}

CString CRiderReportOrderDlg::GetType(long nShareCode1, long nRiderShareCode1, long nPayType)
{
	if((nShareCode1 == nRiderShareCode1)  || nRiderShareCode1 == 0) // 자사
	{
		if(nPayType == 0 || nPayType == 1 || nPayType == 4)
			return "자사현금";

		if(nPayType == 2)
			return "자사신용";

		if(nPayType == 3)
			return "자사송금";
	}

	if((nShareCode1 != nRiderShareCode1)  && nRiderShareCode1 != 0)
	{
		if(nPayType == 0 || nPayType == 1 || nPayType == 4)
			return "타사현금";

		if(nPayType == 2)
			return "타사신용";

		if( nPayType == 3)
			return "타사송금";
	}

	return "알수없음";
}
BOOL CRiderReportOrderDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CString sTitle;
	sTitle.Format("%s(%d) [%s ~ %s]", m_sRName, m_nRNo, m_dtFrom.Format("%m-%d"), m_dtTo.Format("%m-%d"));

	this->SetWindowText(sTitle);

	m_ReportOrderList.InsertColumn(0, "발주사", LVCFMT_LEFT, 100);
	m_ReportOrderList.InsertColumn(1, "오더번호", LVCFMT_CENTER, 70);
	m_ReportOrderList.InsertColumn(2, "접수시간", LVCFMT_CENTER, 80);
	m_ReportOrderList.InsertColumn(3, "의뢰자", LVCFMT_CENTER, 100);
	m_ReportOrderList.InsertColumn(4, "출발지", LVCFMT_CENTER, 100);
	m_ReportOrderList.InsertColumn(5, "도착지", LVCFMT_CENTER, 100);
	m_ReportOrderList.InsertColumn(6, "금액", LVCFMT_LEFT, 60);
	m_ReportOrderList.InsertColumn(7, "쿠폰", LVCFMT_LEFT, 65);
	m_ReportOrderList.InsertColumn(8, "탁송", LVCFMT_LEFT, 55);
	m_ReportOrderList.InsertColumn(9, "지불", LVCFMT_CENTER, 50);
	m_ReportOrderList.InsertColumn(10, "구분", LVCFMT_CENTER, 70);
	m_ReportOrderList.InsertColumn(11, "적용", LVCFMT_CENTER, 50);
	m_ReportOrderList.InsertColumn(12, "비고", LVCFMT_CENTER, 110);

	m_ReportOrderList.Populate();

	OnBnClickedRefreshBtn();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRiderReportOrderDlg::OnBnClickedCloseBtn()
{
	ShowWindow(SW_HIDE);
}

void CRiderReportOrderDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
}

void CRiderReportOrderDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(m_ReportOrderList.GetSafeHwnd() == NULL ||
		this->GetSafeHwnd() == NULL)
		return;

	CRect rcDlg, rcList;
	GetWindowRect(rcDlg);
	m_ReportOrderList.GetWindowRect(rcList);
	ScreenToClient(rcDlg);
	ScreenToClient(rcList);

	rcList.right = rcDlg.right - 3;
	rcList.bottom = rcDlg.bottom - 3;

	m_ReportOrderList.MoveWindow(rcList);
}
