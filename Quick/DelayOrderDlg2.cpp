// DelayOrderDlg2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "DelayOrderDlg2.h"
#include "RcpView.h"
#include "EmptyCarDlg1.h"
#include "AllocateDlg.h"
#include "RcpMultiStateChange.h"

// CDelayOrderDlg2
IMPLEMENT_DYNCREATE(CDelayOrderDlg2, CMyFormView)

CDelayOrderDlg2::CDelayOrderDlg2()
	: CMyFormView(CDelayOrderDlg2::IDD)
{
	LU->SetDelayOrderPane(this);
	m_bRcpPageRefresh = TRUE;
}

CDelayOrderDlg2::~CDelayOrderDlg2()
{
}

void CDelayOrderDlg2::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	for(int i=0; i<REPORT_COUNT; i++)
	{
		DDX_Control(pDX, IDC_ALLOCATE_REPORT + i, m_AllocateReport[i]);
		DDX_Control(pDX, IDC_PICKUP_REPORT + i, m_PickupReport[i]);
		DDX_Control(pDX, IDC_RCP_REPORT + i, m_RcpReport[i]);
	}
	DDX_Control(pDX, IDC_ALLOCATE_STC, m_AllocateStc);
	DDX_Control(pDX, IDC_PICKUP_STC, m_PickupStc);
	DDX_Control(pDX, IDC_RCP_STC, m_RcpStc);
	DDX_Control(pDX, IDC_AL_15_STC, m_Al15Stc);
	DDX_Control(pDX, IDC_AL_21_STC, m_Al21Stc);
	DDX_Control(pDX, IDC_AL_31_STC, m_Al31Stc);
	DDX_Control(pDX, IDC_AL_41_STC, m_Al41Stc);
	DDX_Control(pDX, IDC_PI_60_STC, m_Pi60Stc);
	DDX_Control(pDX, IDC_PI_91_STC, m_Pi91Stc);
	DDX_Control(pDX, IDC_PI_121_STC, m_Pi121Stc);
	DDX_Control(pDX, IDC_PI_151_STC, m_Pi151Stc);
	DDX_Control(pDX, IDC_AL_15_COUNT_STC, m_Al15CountStc);
	DDX_Control(pDX, IDC_AL_21_COUNT_STC, m_Al21CountStc);
	DDX_Control(pDX, IDC_AL_31_COUNT_STC, m_Al31CountStc);
	DDX_Control(pDX, IDC_AL_41_COUNT_STC, m_Al41CountStc);
	DDX_Control(pDX, IDC_PI_60_COUNT_STC, m_Pi60CountStc);
	DDX_Control(pDX, IDC_PI_91_COUNT_STC, m_Pi91CountStc);
	DDX_Control(pDX, IDC_PI_121_COUNT_STC, m_Pi121CountStc);
	DDX_Control(pDX, IDC_PI_151_COUNT_STC, m_Pi151CountStc);

	DDX_Control(pDX, IDC_RCP_STC, m_RcpStc);
	DDX_Control(pDX, IDC_RCP_5_COUNT_STC,  m_Rcp5CountStc);
	DDX_Control(pDX, IDC_RCP_11_COUNT_STC, m_Rcp11CountStc);
	DDX_Control(pDX, IDC_RCP_21_COUNT_STC, m_Rcp21CountStc);
	DDX_Control(pDX, IDC_RCP_31_COUNT_STC, m_Rcp31CountStc);
	DDX_Control(pDX, IDC_RCP_5_STC,  m_Rcp5Stc);
	DDX_Control(pDX, IDC_RCP_11_STC, m_Rcp11Stc);
	DDX_Control(pDX, IDC_RCP_21_STC, m_Rcp21Stc);
	DDX_Control(pDX, IDC_RCP_31_STC, m_Rcp31Stc);
}

BEGIN_MESSAGE_MAP(CDelayOrderDlg2, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY_RANGE(NM_CLICK, IDC_ALLOCATE_REPORT, IDC_ALLOCATE_REPORT3, OnAllocateReportItemClick)
	ON_NOTIFY_RANGE(NM_CLICK, IDC_PICKUP_REPORT, IDC_PICKUP_REPORT3, OnPickupReportItemClick)
	ON_NOTIFY_RANGE(NM_CLICK, IDC_RCP_REPORT, IDC_RCP_REPORT3, OnRcpReportItemClick)

	ON_NOTIFY_RANGE(NM_DBLCLK, IDC_ALLOCATE_REPORT, IDC_ALLOCATE_REPORT3, OnAllocateReportItemDbClick)
	ON_NOTIFY_RANGE(NM_DBLCLK, IDC_PICKUP_REPORT, IDC_PICKUP_REPORT3, OnPickupReportItemDbClick)
	ON_NOTIFY_RANGE(NM_DBLCLK, IDC_RCP_REPORT, IDC_RCP_REPORT3, OnRcpReportItemDbClick)

	ON_MESSAGE(WM_REFRESH_DELAY_ORDER, OnRefreshList)
END_MESSAGE_MAP()


// CDelayOrderDlg2 진단입니다.

void CDelayOrderDlg2::OnAllocateReportItemClick(UINT nFlag, NMHDR * pNotifyStruct, LRESULT * result)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	long nIndex = m_AllocateReport[nFlag - IDC_ALLOCATE_REPORT].GetNextItem(-1, LVNI_SELECTED);
 
	if(nIndex == - 1) return;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	if(pItemNotify->pColumn->GetItemIndex() == 2)
	{
		ST_DELAY_ORDER *order = (ST_DELAY_ORDER*)m_AllocateReport[nFlag - IDC_ALLOCATE_REPORT].GetItemData(nIndex);

		if(LU->GetRcpView()->GetItemSecondCross(order->nCompany))
		{
			CString strMsg;
			strMsg = "크로스배차된 오더의 상태를 직접 변경하실 수 없습니다.\n";
			strMsg += "해당 회원사에게 전화하셔서 처리 하시기 바랍니다.";
			MessageBox(strMsg, "확인", MB_ICONINFORMATION);
			return;
		}

		//PDA배차를 이용하는 경우에 배차완료 설정, 아닌경우에 배차임
		if(m_ci.m_bAllocateWithPDA)
		{
			if(MessageBox("픽업완료 상태로 변경하시겠습니까?", "픽업", MB_YESNO | MB_ICONINFORMATION) == IDYES)
			{
				LU->GetRcpView()->GetStateChange()->PickupState(order->nCompany, order->nTNo, -1, order->nState);
			}
		}
		else 
		{
			CAllocateDlg dlg;

			dlg.m_nCompanyCode = order->nCompany;
			dlg.m_nDOrderTable = order->nCompany;
			dlg.m_nCarType = order->nCarType;
			
			if(dlg.DoModal() != IDOK) return;

			LU->GetRcpView()->GetStateChange()->PickupState(order->nCompany, order->nTNo, dlg.m_nRNo, order->nState);
		}
		
		LU->GetRcpView()->RefreshList();
		RefreshList();
	}	
}

void CDelayOrderDlg2::OnPickupReportItemClick(UINT nFlag, NMHDR * pNotifyStruct, LRESULT * result)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	long nIndex = m_PickupReport[nFlag - IDC_PICKUP_REPORT].GetNextItem(-1, LVNI_SELECTED);

	if(nIndex == - 1) return;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	if(pItemNotify->pColumn->GetItemIndex() == 2)
	{
		if(!POWER_CHECK(2002, "오더상태변경", TRUE))
			return;

		ST_DELAY_ORDER *order = (ST_DELAY_ORDER*)m_PickupReport[nFlag - IDC_PICKUP_REPORT].GetItemData(nIndex);

		if(LU->GetRcpView()->GetSecondCrossState(order->nCompany))
		{
			CString strMsg;
			strMsg = "크로스배차된 오더의 상태를 직접 변경하실 수 없습니다.\n";
			strMsg += "해당 회원사에게 전화하셔서 처리 하시기 바랍니다.";
			MessageBox(strMsg, "확인", MB_ICONINFORMATION);
			return;
		}

		//PDA배차를 이용하는 경우에 배차완료 설정, 아닌경우에 배차임
		if(MessageBox("오더완료 상태로 변경하시겠습니까?", "완료", MB_YESNO | MB_ICONINFORMATION) == IDYES)
		{
			LU->GetRcpView()->GetStateChange()->FinishState(order->nTNo, order->nState);
			LU->GetRcpView()->RefreshList();
			RefreshList();
		}

		//LU->GetRcpView()->CompleteState(order->nTNo, order->nRNo, order->nState);
	}
}

void CDelayOrderDlg2::OnRcpReportItemClick(UINT nFlag, NMHDR * pNotifyStruct, LRESULT * result)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	long nIndex = m_RcpReport[nFlag - IDC_RCP_REPORT].GetNextItem(-1, LVNI_SELECTED);

	if(nIndex == - 1) return;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	if(pItemNotify->pColumn->GetItemIndex() == 2)
	{
		if(!POWER_CHECK(2002, "오더상태변경", TRUE) && !POWER_CHECK(2009, "개별배차", TRUE))
			return;

		ST_DELAY_ORDER *order = (ST_DELAY_ORDER*)m_RcpReport[nFlag - IDC_RCP_REPORT].GetItemData(nIndex);

		if(LU->GetRcpView()->GetSecondCrossState(order->nCompany))
		{
			CString strMsg;
			strMsg = "크로스배차된 오더의 상태를 직접 변경하실 수 없습니다.\n";
			strMsg += "해당 회원사에게 전화하셔서 처리 하시기 바랍니다.";
			MessageBox(strMsg, "확인", MB_ICONINFORMATION);
			return;
		}

		//PDA배차를 이용하는 경우에 배차완료 설정, 아닌경우에 배차임
		//LU->GetRcpView()->GetStateChange()->FinishState(order->nTNo, order->nState);

		LU->OpenAllocateDlg(order->nTNo, order->nState, "개별배차", ZERO, order->nDeposit, order->nCarType);
		//LU->GetRcpView()->GetStateChange->CompleteState(order->nTNo, order->nRNo, order->nState);
		LU->GetRcpView()->RefreshList();
		RefreshList();
	}
}

void CDelayOrderDlg2::OnAllocateReportItemDbClick(UINT nFlag, NMHDR * pNotifyStruct, LRESULT * result)
{
	long nIndex = m_AllocateReport[nFlag - IDC_ALLOCATE_REPORT].GetNextItem(-1, LVNI_SELECTED);

	if(nIndex == - 1) return;

	ST_DELAY_ORDER *order = (ST_DELAY_ORDER*)m_AllocateReport[nFlag - IDC_ALLOCATE_REPORT].GetItemData(nIndex);

	long nCompany = order->nCompany;
	long nTNo = order->nTNo;

	if(LU->GetRcpView()->GetSecondCrossState(order->nCompany))
	{
		CString strMsg;
		strMsg = "크로스배차된 오더를 직접 수정하실수 없습니다.\n";
		strMsg += "해당 회원사에게 전화하셔서 처리 하시기 바랍니다.";
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		return;
	}

	//아이템 번호를 넣어주면 수정모드로 시작한다.
	//(상태를 넘기는 이유는 상태변경된걸 알려주기 위해서다.)

	LU->GetRcpView()->CreateRcpDlg(NULL, 
		order->strOName, 
		order->nTNo, 
		order->nState);

}

void CDelayOrderDlg2::OnPickupReportItemDbClick(UINT nFlag, NMHDR * pNotifyStruct, LRESULT * result)
{
	long nIndex = m_PickupReport[nFlag - IDC_PICKUP_REPORT].GetNextItem(-1, LVNI_SELECTED);

	if(nIndex == - 1) return;

	ST_DELAY_ORDER *order = (ST_DELAY_ORDER*)m_PickupReport[nFlag - IDC_PICKUP_REPORT].GetItemData(nIndex);

	long nCompany = order->nCompany;
	long nTNo = order->nTNo;

	if(LU->GetRcpView()->GetSecondCrossState(order->nCompany))
	{
		CString strMsg;
		strMsg = "크로스배차된 오더를 직접 수정하실수 없습니다.\n";
		strMsg += "해당 회원사에게 전화하셔서 처리 하시기 바랍니다.";
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		return;
	}

	//아이템 번호를 넣어주면 수정모드로 시작한다.
	//(상태를 넘기는 이유는 상태변경된걸 알려주기 위해서다.)
	LU->GetRcpView()->CreateRcpDlg(NULL, 
		order->strOName,
		order->nTNo, 
		order->nState);
}

void CDelayOrderDlg2::OnRcpReportItemDbClick(UINT nFlag, NMHDR * pNotifyStruct, LRESULT * result)
{
	long nIndex = m_RcpReport[nFlag - IDC_RCP_REPORT].GetNextItem(-1, LVNI_SELECTED);

	if(nIndex == - 1) return;

	ST_DELAY_ORDER *order = (ST_DELAY_ORDER*)m_RcpReport[nFlag - IDC_RCP_REPORT].GetItemData(nIndex);

	long nCompany = order->nCompany;
	long nTNo = order->nTNo;

	if(LU->GetRcpView()->GetSecondCrossState(order->nCompany))
	{
		CString strMsg;
		strMsg = "크로스배차된 오더를 직접 수정하실수 없습니다.\n";
		strMsg += "해당 회원사에게 전화하셔서 처리 하시기 바랍니다.";
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		return;
	}

	//아이템 번호를 넣어주면 수정모드로 시작한다.
	//(상태를 넘기는 이유는 상태변경된걸 알려주기 위해서다.)
	LU->GetRcpView()->CreateRcpDlg(NULL, 
		order->strOName,
		order->nTNo, 
		order->nState);
}


#ifdef _DEBUG
void CDelayOrderDlg2::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CDelayOrderDlg2::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CDelayOrderDlg2 메시지 처리기입니다.

void CDelayOrderDlg2::OnInitialUpdate()
{
	if(m_bInitialUpdateCalled) return;

	CMyFormView::OnInitialUpdate();

	m_Al15Stc.SetTextColor(RGB(0, 0, 255));
	m_Al21Stc.SetTextColor(RGB(100, 100, 255));
	m_Al31Stc.SetTextColor(RGB(255, 100, 100));
	m_Al41Stc.SetTextColor(RGB(255, 0, 0));
	m_Pi60Stc.SetTextColor(RGB(0, 0, 255));
	m_Pi91Stc.SetTextColor(RGB(100, 100, 255));
	m_Pi121Stc.SetTextColor(RGB(255, 100, 100));
	m_Pi151Stc.SetTextColor(RGB(255, 0, 0));
	m_Rcp5Stc.SetTextColor(RGB(0, 0, 255));
	m_Rcp11Stc.SetTextColor(RGB(100, 100, 255));
	m_Rcp21Stc.SetTextColor(RGB(255, 100, 100));
	m_Rcp31Stc.SetTextColor(RGB(255, 0, 0));

	m_Al15CountStc.SetBackGroundColor(RGB(0, 0, 255));
	m_Al21CountStc.SetBackGroundColor(RGB(100, 100, 255));
	m_Al31CountStc.SetBackGroundColor(RGB(255, 100, 100));
	m_Al41CountStc.SetBackGroundColor(RGB(255, 0, 0));
	m_Pi60CountStc.SetBackGroundColor(RGB(0, 0, 255));
	m_Pi91CountStc.SetBackGroundColor(RGB(100, 100, 255));
	m_Pi121CountStc.SetBackGroundColor(RGB(255, 100, 100));
	m_Pi151CountStc.SetBackGroundColor(RGB(255, 0, 0));
	m_Rcp5CountStc.SetBackGroundColor(RGB(0, 0, 255));
	m_Rcp11CountStc.SetBackGroundColor(RGB(100, 100, 255));
	m_Rcp21CountStc.SetBackGroundColor(RGB(255, 100, 100));
	m_Rcp31CountStc.SetBackGroundColor(RGB(255, 0, 0));


	for(int i=0; i<REPORT_COUNT; i++)
	{
		m_AllocateReport[i].InsertColumn(0, "출발동", LVCFMT_LEFT, 80);
		m_AllocateReport[i].InsertColumn(1, "도착동", LVCFMT_LEFT, 80);
		m_AllocateReport[i].InsertColumn(2, "상태", LVCFMT_LEFT, 50);
		m_AllocateReport[i].InsertColumn(3, "라이더", LVCFMT_LEFT, 70);
		m_AllocateReport[i].InsertColumn(4, "지연시간", LVCFMT_LEFT, 60);

		m_PickupReport[i].InsertColumn(0, "출발동", LVCFMT_LEFT, 80);
		m_PickupReport[i].InsertColumn(1, "도착동", LVCFMT_LEFT, 80);
		m_PickupReport[i].InsertColumn(2, "상태", LVCFMT_LEFT, 50);
		m_PickupReport[i].InsertColumn(3, "라이더", LVCFMT_LEFT, 70);
		m_PickupReport[i].InsertColumn(4, "지연시간", LVCFMT_LEFT, 60);

		m_RcpReport[i].InsertColumn(0, "출발동", LVCFMT_LEFT, 80);
		m_RcpReport[i].InsertColumn(1, "도착동", LVCFMT_LEFT, 80);
		m_RcpReport[i].InsertColumn(2, "상태", LVCFMT_LEFT, 50);
		m_RcpReport[i].InsertColumn(3, "라이더", LVCFMT_LEFT, 70);
		m_RcpReport[i].InsertColumn(4, "지연시간", LVCFMT_LEFT, 60);

		m_AllocateReport[i].GetPaintManager()->m_strNoItems = "";
		m_PickupReport[i].GetPaintManager()->m_strNoItems = "";
		m_RcpReport[i].GetPaintManager()->m_strNoItems = "";

		m_AllocateReport[i].Populate();
		m_PickupReport[i].Populate();
		m_RcpReport[i].Populate();
	}
	
	LU->GetRcpView()->RefreshList();
	RefreshList();
}



void CDelayOrderDlg2::InitOrder()
{
	m_OrderVec.clear();

	OrderRecordList &order = LU->GetRcpView()->GetTodayOrder()->GetOrderRecordList();
	OrderRecordList::iterator it;

	for(it = order.begin(); it != order.end(); it++)
	{
		long nState1 = (it->second.bShareOrder && it->second.nState == 10 && it->second.bClientShare5) ? 100 : it->second.nState;

		if((it->second.nState >= 30 || it->second.nState <= 31) && it->second.nRNo != 0)
		{
			ST_DELAY_ORDER *pItem = new ST_DELAY_ORDER;

			pItem->nDistanceKM = it->second.nDistanceKM;
			pItem->nState = it->second.nState;
			pItem->strStart = it->second.strStart.c_str();
			pItem->strDest = it->second.strDest.c_str();
			pItem->dtDate = it->second.dtState;
			pItem->nRNo = it->second.nRNo;
			pItem->strRName = it->second.info[18].c_str()	;
			pItem->nTNo = it->second.nTNo;
			pItem->strOName = it->second.strCName.c_str();
			pItem->nCompany = it->second.nCompany;
			pItem->nRiderCompany = it->second.nRiderCompany;
			pItem->nCarType = it->second.nCarType;

			COleDateTimeSpan span = COleDateTime::GetCurrentTime() - it->second.dtState;
			long nDelayTime = span.GetHours();
			long nDelay = span.GetMinutes();

			pItem->nDelay = (nDelayTime * 60) + nDelay;
			m_OrderVec.push_back(pItem);
		}
		else if(it->second.nState == 10 && it->second.nRNo == 0)
		{
			ST_DELAY_ORDER *pItem = new ST_DELAY_ORDER;

			pItem->nDistanceKM = it->second.nDistanceKM;
			pItem->nState = it->second.nState;
			pItem->strStart = it->second.strStart.c_str();
			pItem->strDest = it->second.strDest.c_str();
			pItem->dtDate = it->second.dtState;
			pItem->nRNo = it->second.nRNo;
			pItem->strRName = it->second.info[18].c_str()	;
			pItem->nTNo = it->second.nTNo;
			pItem->strOName = it->second.strCName.c_str();
			pItem->nCompany = it->second.nCompany;
			pItem->nRiderCompany = it->second.nRiderCompany;
			pItem->nCarType = it->second.nCarType;
			pItem->nDeposit = it->second.nDeposit;

			COleDateTimeSpan span = COleDateTime::GetCurrentTime() - it->second.dtState;
			long nDelayTime = span.GetHours();
			long nDelay = span.GetMinutes();

			pItem->nDelay = (nDelayTime * 60) + nDelay;
			m_OrderVec.push_back(pItem);
		}
	}

}


void CDelayOrderDlg2::RefreshList()
{
	InitOrder();

	long nAllpcateReportCount[REPORT_COUNT] = {0,};
	long nPickupReportCount[REPORT_COUNT] = {0,};
	long nRcpReportCount[REPORT_COUNT] = {0,};

	for(int i=0; i<REPORT_COUNT; i++)
	{
		m_AllocateReport[i].GetRows()->Clear();
		m_AllocateReport[i].GetRecords()->RemoveAll();

		m_PickupReport[i].GetRows()->Clear();
		m_PickupReport[i].GetRecords()->RemoveAll();

		m_RcpReport[i].GetRows()->Clear();
		m_RcpReport[i].GetRecords()->RemoveAll();

		m_AllocateReport[i].Populate();
		m_PickupReport[i].Populate();
		m_RcpReport[i].Populate();
	}

	DELAY_ORDER_VECTOR2::iterator it;

	for(it = m_OrderVec.begin(); it != m_OrderVec.end(); it++)
	{
        ST_DELAY_ORDER *order = *it;

		if(order->nState == 30)
		{
			if(order->nDelay >= 15 && order->nDelay <= 20)
			{
				InsertReport(&m_AllocateReport[0], order, nAllpcateReportCount[0]);
            }
			else if(order->nDelay >= 21 && order->nDelay <= 30)
			{
				InsertReport(&m_AllocateReport[1], order, nAllpcateReportCount[1]);
			}
			else if(order->nDelay >= 31 && order->nDelay <= 40)
			{
				InsertReport(&m_AllocateReport[2], order, nAllpcateReportCount[2]);
			}
			else if(order->nDelay >= 41)
			{
				InsertReport(&m_AllocateReport[3], order, nAllpcateReportCount[3]);
			}
		}
		else if(order->nState == 31)
		{
			if(order->nDelay >= 60 && order->nDelay <= 90)
			{
				InsertReport(&m_PickupReport[0], order, nPickupReportCount[0]);
			}
			else if(order->nDelay >= 91 && order->nDelay <= 120)
			{
				InsertReport(&m_PickupReport[1], order, nPickupReportCount[1]);
			}
			else if(order->nDelay >= 121 && order->nDelay <= 150)
			{
				InsertReport(&m_PickupReport[2], order, nPickupReportCount[2]);
			}
			else if(order->nDelay >= 151)
			{
				InsertReport(&m_PickupReport[3], order, nPickupReportCount[3]);
			}
		}
		else if(order->nState == 10)
		{
			if(order->nDelay >= 5 && order->nDelay <= 10)
			{
				InsertReport(&m_RcpReport[0], order, nRcpReportCount[0]);
			}
			else if(order->nDelay >= 11 && order->nDelay <= 20)
			{
				InsertReport(&m_RcpReport[1], order, nRcpReportCount[1]);
			}
			else if(order->nDelay >= 21 && order->nDelay <= 30)
			{
				InsertReport(&m_RcpReport[2], order, nRcpReportCount[2]);
			}
			else if(order->nDelay >= 31)
			{
				InsertReport(&m_RcpReport[3], order, nRcpReportCount[3]);
			}
		}
	}

	for(int i=0; i<REPORT_COUNT; i++)
	{
		m_AllocateReport[i].Populate();
		m_PickupReport[i].Populate();
		m_RcpReport[i].Populate();
	}

	char buffer[20];

	m_Al15CountStc.SetWindowText("총 : ( " + CString(itoa(nAllpcateReportCount[0], buffer,10)) + " ) 건");
	m_Al21CountStc.SetWindowText("총 : ( " + CString(itoa(nAllpcateReportCount[1], buffer,10)) + " ) 건");
	m_Al31CountStc.SetWindowText("총 : ( " + CString(itoa(nAllpcateReportCount[2], buffer,10)) + " ) 건");
	m_Al41CountStc.SetWindowText("총 : ( " + CString(itoa(nAllpcateReportCount[3], buffer,10)) + " ) 건");

	m_Pi60CountStc.SetWindowText("총 : ( " + CString(itoa(nPickupReportCount[0], buffer,10)) + " ) 건");
	m_Pi91CountStc.SetWindowText("총 : ( " + CString(itoa(nPickupReportCount[1], buffer,10)) + " ) 건");
	m_Pi121CountStc.SetWindowText("총 : ( " + CString(itoa(nPickupReportCount[2], buffer,10)) + " ) 건");
	m_Pi151CountStc.SetWindowText("총 : ( " + CString(itoa(nPickupReportCount[3], buffer,10)) + " ) 건");

	m_Rcp5CountStc.SetWindowText("총 : ( " + CString(itoa(nRcpReportCount[0], buffer,10)) + " ) 건");
	m_Rcp11CountStc.SetWindowText("총 : ( " + CString(itoa(nRcpReportCount[1], buffer,10)) + " ) 건");
	m_Rcp21CountStc.SetWindowText("총 : ( " + CString(itoa(nRcpReportCount[2], buffer,10)) + " ) 건");
	m_Rcp31CountStc.SetWindowText("총 : ( " + CString(itoa(nRcpReportCount[3], buffer,10)) + " ) 건");
}

void CDelayOrderDlg2::InsertReport(CXTPListCtrl2 *pReport, ST_DELAY_ORDER *order, long &nRecordCount)
{
	char buffer[20];
 
    pReport->InsertItem(nRecordCount, order->strStart);
	pReport->SetItemText(nRecordCount, 1, order->strDest);

	if(pReport->GetSafeHwnd() == m_AllocateReport[0].GetSafeHwnd() ||
		pReport->GetSafeHwnd() == m_AllocateReport[1].GetSafeHwnd() ||
		pReport->GetSafeHwnd() == m_AllocateReport[2].GetSafeHwnd() ||
		pReport->GetSafeHwnd() == m_AllocateReport[3].GetSafeHwnd())
		pReport->SetItemText(nRecordCount, 2, "배차");
	else if(pReport->GetSafeHwnd() == m_PickupReport[0].GetSafeHwnd() ||
		pReport->GetSafeHwnd() == m_PickupReport[1].GetSafeHwnd() ||
		pReport->GetSafeHwnd() == m_PickupReport[2].GetSafeHwnd() ||
		pReport->GetSafeHwnd() == m_PickupReport[3].GetSafeHwnd())
		pReport->SetItemText(nRecordCount, 2, "픽업");        
	else
		pReport->SetItemText(nRecordCount, 2, "접수");        

	pReport->SetItemText(nRecordCount, 3, CString(itoa(order->nRNo, buffer, 10)) + "/" + order->strRName);
	pReport->SetItemText(nRecordCount, 4, itoa(order->nDelay, buffer, 10));
	pReport->SetItemData(nRecordCount, (DWORD)order);

	nRecordCount++;
}

								  
void CDelayOrderDlg2::OnBnClickedRefreshBtn()
{
	LU->GetRcpView()->RefreshList();
	RefreshList();
}

LONG CDelayOrderDlg2::OnRefreshList(WPARAM wParam, LPARAM lParam)
{
	LU->GetRcpView()->RefreshList();
	RefreshList();
	return 0;
}