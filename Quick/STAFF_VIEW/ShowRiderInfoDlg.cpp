// ShowRiderInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ShowRiderInfoDlg.h"
#include "RcpView.h"
#include "WorkStopMemoDlg.h"
#include "RiderMsgDlg.h"
#include "MakeRiderStat.h"
#include "RiderCancelLogDlg.h"
#include "AllocateGroupDlg.h"
#include "MainFrm.h"
#include "ShareOrderAllocate.h"
#include "RiderShareBoardDlg.h"
#include "RcpPageCTIForm.h"
#include "SendOtherRiderMsgDlg.h"
#include "OtherRiderTransferDlg.h"
#include "TRSRiderDlg.h"
#include "ChargeForRiderDlg.h"
#include "RiderAdviceDlg2010.h"

// CShowRiderInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CShowRiderInfoDlg, CMyDialog)
CShowRiderInfoDlg::CShowRiderInfoDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CShowRiderInfoDlg::IDD, pParent)
{
	m_bShowRiderInfo = FALSE;
	m_brush.CreateSolidBrush(RGB(255, 255, 255));
	m_nOrderCompany = -1;
	m_bLicenseOK = 0;
	m_strCarType = "";
	m_pParentView = NULL;
	m_strRealRName = "";
	m_strTodaySave = "";
	m_strTodayIncome = "";
	m_strLoadInsState = "";
	m_strSumBlackMarks = "";
	m_strBusinessCar = "";
	m_strCarNo = "";
}

CShowRiderInfoDlg::~CShowRiderInfoDlg()
{
}

void CShowRiderInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DRAW_STATIC, m_stc1);
	DDX_Control(pDX, IDC_OK_BTN, m_btnOk);
	DDX_Control(pDX, IDC_ORDER_LIST, m_OrderList);
	DDX_Control(pDX, IDC_CALL_BTN, m_btnCall);
	DDX_Control(pDX, IDC_WORK_STATE_BTN, m_btnWorkState);
	DDX_Control(pDX, IDC_SEND_MSG_BTN, m_btnSendMsg);
	DDX_Control(pDX, IDC_HISTORY_BTN, m_btnHistory);
	DDX_Control(pDX, IDC_CANCEL_STATE_BTN, m_btnCancelState);
	DDX_Control(pDX, IDC_RCP_STATE_BTN, m_btnRcpState);
	DDX_Control(pDX, IDC_LIMIT_SHARE_ORDER_BTN, m_btnLimitShareOrder);
	DDX_Control(pDX, IDC_RIDER_STAT_LIST, m_RiderStatList);
	DDX_Control(pDX, IDC_RIDER_CANCEL_LOG_BTN, m_btnRiderCancelLog);
	DDX_Control(pDX, IDC_TRANSFER_BTN, m_btnTransfer);
	DDX_Control(pDX, IDC_ATTEND_BTN, m_btnAttend);
	DDX_Control(pDX, IDC_RIDER_SHARE_BOARD_BTN, m_btnRiderShareBoard);
	DDX_Control(pDX, IDC_SHARE_REFUSAL_REPORT, m_lstShareRefusal);
	DDX_Control(pDX, IDC_INIT_BTN, m_btnCeritify);
	DDX_Control(pDX, IDC_OTHER_RIDER_TRANSFER_BTN, m_btnOtherRiderTransfer);
	DDX_Control(pDX, IDC_CHARGE_FOR_BTN, m_btnChargeFor);
}


BEGIN_MESSAGE_MAP(CShowRiderInfoDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CALL_BTN, OnBnClickedCallBtn)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_ORDER_LIST, OnNMDblclkOrderList)
	ON_BN_CLICKED(IDC_WORK_STATE_BTN, OnBnClickedWorkStateBtn)
	ON_BN_CLICKED(IDC_SEND_MSG_BTN, OnBnClickedSendMsgBtn)
	ON_BN_CLICKED(IDC_CANCEL_STATE_BTN, OnBnClickedCancelStateBtn)
	ON_BN_CLICKED(IDC_RCP_STATE_BTN, OnBnClickedRcpStateBtn)
	ON_BN_CLICKED(IDC_WAIT_STATE_BTN, OnBnClickedRcpWaitBtn)
	ON_BN_CLICKED(IDC_LIMIT_SHARE_ORDER_BTN, OnBnClickedLimitShareOrderBtn)
	ON_BN_CLICKED(IDC_RIDER_CANCEL_LOG_BTN, OnBnClickedRiderCancelLogBtn)
	ON_BN_CLICKED(IDC_TRANSFER_BTN, OnBnClickedTransferBtn)
	ON_BN_CLICKED(IDC_ATTEND_BTN, OnBnClickedAttendBtn)
	ON_BN_CLICKED(IDC_RIDER_SHARE_BOARD_BTN, &CShowRiderInfoDlg::OnBnClickedRiderShareBoardBtn)
	ON_BN_CLICKED(IDC_INIT_BTN, &CShowRiderInfoDlg::OnBnClickedInitBtn)
	ON_BN_CLICKED(IDC_OTHER_RIDER_TRANSFER_BTN, &CShowRiderInfoDlg::OnBnClickedOtherRiderTransferBtn)
	ON_BN_CLICKED(IDC_TRS_BTN, OnBnClickedTRSBtn)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_CHARGE_FOR_BTN, &CShowRiderInfoDlg::OnBnClickedChargeForBtn)
	ON_BN_CLICKED(IDC_RIDERID_ACCEPT_BTN, &CShowRiderInfoDlg::OnBnClickedRideridAcceptBtn)
	ON_BN_CLICKED(IDC_RIDERPHONE_ACCEPT_BTN, &CShowRiderInfoDlg::OnBnClickedRiderphoneAcceptBtn)
	ON_BN_CLICKED(IDC_CALL_ACCEPT_BTN, &CShowRiderInfoDlg::OnBnClickedCallAcceptBtn)
	ON_STN_CLICKED(IDC_DRAW_STATIC, &CShowRiderInfoDlg::OnStnClickedDrawStatic)
END_MESSAGE_MAP()


// CShowRiderInfoDlg 메시지 처리기입니다.
void CShowRiderInfoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CMyDialog::OnPaint()을(를) 호출하지 마십시오.
	DrawRiderInfo(&dc);
}

void CShowRiderInfoDlg::DrawRiderInfo(CDC *pDC)
{
	CXTPPenDC pen(*pDC, RGB(0, 0, 255));
	CXTPFontDC font(pDC, m_FontManager.GetFont("돋움체", 13, FW_BOLD));
	pDC->SetBkMode(TRANSPARENT);

	CRect rc;
	m_stc1.GetClientRect(rc);
	rc.right = rc.left + 200;
	DrawInfoBox(pDC, rc);
	rc.DeflateRect(5, 5, 5, 5);
	PrintLine(pDC, rc, "회사명", m_strCompany);
	PrintLine(pDC, rc, "지사명", m_strBranch);
	PrintLine(pDC, rc, "☏", m_strCompanyPhone + "/" + m_strOfficePhone, TRUE);
	PrintLine(pDC, rc, "기사명", m_strRName, TRUE);
	m_rcDeviceID = rc; m_rcDeviceID.bottom = m_rcDeviceID.top + 18;
	PrintLine(pDC, rc, "단말ID", m_strDeviceID);
	PrintLine(pDC, rc, "단말기종", m_strDeviceType);
	PrintLine(pDC, rc, "단말버전", m_strDeviceVer, TRUE);
	m_rcPhone = rc; m_rcPhone.bottom = m_rcPhone.top + 18;
	PrintLine(pDC, rc, "휴대폰", m_strPhone); 
	PrintLine(pDC, rc, "집전화", m_strHomePhone);
	PrintLine(pDC, rc, "입사일", m_strEnterDate); 

	m_stc1.GetClientRect(rc);
	rc.left += 201;
	rc.right = rc.left + 200;
	DrawInfoBox(pDC, rc);
	rc.DeflateRect(5, 5, 5, 5);
	PrintLine(pDC, rc, "입금방식", m_strDepositType);
	PrintLine(pDC, rc, "금일수입", m_strTodayIncome, FALSE, RGB(200, 0, 0));
	PrintLine(pDC, rc, "잔  액", m_strBalance, FALSE, RGB(200, 0, 0));
	PrintLine(pDC, rc, "금일충전", m_strTodaySave, TRUE, RGB(200, 0, 0));
	PrintLine(pDC, rc, "업무상태", m_strWorkState);
	PrintLine(pDC, rc, "건수제한", m_strCountLimit);
	PrintLine(pDC, rc, "시간제한", m_strTimeLimit, TRUE);
	PrintDualLine(pDC, rc, "보험정보", m_strInsInfo);
	PrintLine(pDC, rc, "보험만료", m_strInsExpDate);
	PrintLine(pDC, rc, "면허상태", m_strLicenseState, TRUE, m_bLicenseOK ? RGB(0, 0, 0) : RGB(200, 0, 0));

	m_stc1.GetClientRect(rc);
	rc.left += 402; 
	DrawInfoBox(pDC, rc);
	rc.DeflateRect(5, 5, 5, 5); 
	PrintLine(pDC, rc, "과거이력", "");
	PrintLine(pDC, rc, "", "");
	PrintLine(pDC, rc, "벌점", m_strSumBlackMarks, TRUE, RGB(255, 0, 0)); 
	PrintLine(pDC, rc, "차량번호", m_strCarNo, FALSE); 
	PrintLine(pDC, rc, "영업용차량", m_strBusinessCar, FALSE); 
	PrintLine(pDC, rc, "차종", m_strCarType, FALSE);
	PrintLine(pDC, rc, "적재물보험", m_strLoadInsState, FALSE);

	if(m_strPhone.Find("*") >= 0) 
	{
		PrintLine(pDC, rc, "", "");
		PrintLine(pDC, rc, "", "");
		PrintLine(pDC, rc, "4시간지난오더 타사기사 전번 미표시상태", FALSE, RGB(200, 0, 0));
	}

//	PrintLine(pDC, rc, "", "");
//	PrintLine(pDC, rc, "", "");
//	PrintLine(pDC, rc, "", "");
//	PrintLine(pDC, rc, "", "검색버튼 누르시면 기사정보가 사라집니다.", FALSE, RGB(255, 255, 255));
//	PrintLine(pDC, rc, "", "다시보시려면 F8키 누르시기 바랍니다.", FALSE, RGB(255, 255, 255));
}

void CShowRiderInfoDlg::DrawInfoBox(CDC *pDC, CRect rc, BOOL bGreen)
{
	pDC->FillSolidRect(rc.left, rc.top, rc.Width(), rc.Height(), 
		bGreen ? RGB(119, 185, 147) : RGB(119, 147, 185)); 
}

void CShowRiderInfoDlg::PrintLine(CDC *pDC, CRect &rc, CString strTitle, CString strText, 
								 BOOL bNextSeparator, COLORREF clrText)
{
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->DrawText(strTitle, rc, DT_LEFT);
	pDC->SetTextColor(clrText);
	pDC->DrawText(strText, rc, DT_RIGHT);
	if(bNextSeparator)
		rc.top += 20;
	else
		rc.top += 15;
}

void CShowRiderInfoDlg::PrintDualLine(CDC *pDC, CRect &rc, CString strTitle, CString strText, 
									 BOOL bNextSeparator, COLORREF clrText)
{
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->DrawText(strTitle, rc, DT_LEFT);
	rc.top += 13;
	pDC->SetTextColor(clrText);
	pDC->DrawText(strText, rc, DT_LEFT);
	if(bNextSeparator)
		rc.top += 20;
	else
		rc.top += 15;
}

long CShowRiderInfoDlg::GetOtherRiderOrder()
{
	m_OrderList.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_order_2");
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(m_nRNo);

	if(!pRs.Execute(&pCmd))
		return 0;

	char buffer[10];
	long nSum = 0;
	long nTodayIncome = 0;

	long nTNo, nState, nChargeSum, nPayType, nFinalDepositRate;
	CString strName, strBranch, strSDong, strDDong;
	COleDateTime dt1, dt3, dtFinal;
	long nCashCount = 0, nCashSum = 0, nCreditCount = 0, nCreditSum = 0;

	long nRecordCount = pRs.GetRecordCount();
	long nItem = 0;

	if(nRecordCount > 0) {
		m_OrderList.InsertItem(nItem++, "합계");
	} 

	for(int i=ZERO; i<nRecordCount; i++)
	{
		CString strTime;
		COleDateTime dt1, dt3, dtFinal;
		long nCashCount = 0, nCashSum = 0, nCreditCount = 0, nCreditSum = 0;

		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("nChargeSum", nChargeSum);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("sBranchName", strBranch);
		pRs.GetFieldValue("sSDong", strSDong);
		pRs.GetFieldValue("sDDong", strDDong);
		pRs.GetFieldValue("dt1", dt1);
		pRs.GetFieldValue("dt3", dt3);
		pRs.GetFieldValue("dtFinal", dtFinal);
		pRs.GetFieldValue("nPayType", nPayType);
		pRs.GetFieldValue("nFinalDepositRate", nFinalDepositRate);

		m_OrderList.InsertItem(nItem, ltoa(nRecordCount - i, buffer, 10));
		m_OrderList.SetItemText(nItem, 1, LF->GetStateString(nState));
		m_OrderList.SetItemText(nItem, 2, strName + "/" + strBranch);
		m_OrderList.SetItemText(nItem, 3, strSDong);
		m_OrderList.SetItemText(nItem, 4, strDDong);
		m_OrderList.SetItemText(nItem, 5, dt1.Format("%H:%M"));
		m_OrderList.SetItemText(nItem, 6, dt3.Format("%H:%M"));
		m_OrderList.SetItemText(nItem, 7, dtFinal.Format("%H:%M"));
		m_OrderList.SetItemText(nItem, 8, ltoa(nChargeSum, buffer, 10));
		m_OrderList.SetItemData(nItem++, nTNo);

		if(nPayType == PAY_CREDIT || nPayType == PAY_ONLINE || nPayType == PAY_CARD)
		{
			nCreditCount++;
			nCreditSum += nChargeSum;
		}
		else
		{
			nCashCount++;
			nCashSum += nChargeSum;
		}
 
		nSum += nChargeSum;
		pRs.MoveNext();

		nTodayIncome += (nChargeSum - (nChargeSum * (nFinalDepositRate / 100)) );
	}


	if(nRecordCount > 0) {
		m_OrderList.SetItemText(0, 1, CString(ltoa(nRecordCount, buffer, 10)) + "건");
		m_OrderList.SetItemText(0, 2, CString(ltoa(nSum, buffer, 10)) + "원");
		m_OrderList.SetItemText(0, 3, "현금 : " + CString(itoa(nCashCount, buffer, 10)) + "/" + LF->GetMyNumberFormat(nCashSum));
		m_OrderList.SetItemText(0, 4, "신용 : " + CString(itoa(nCreditCount, buffer, 10)) + "/" + LF->GetMyNumberFormat(nCreditSum));
		m_OrderList.SetItemData(0, 0);
	}

	return nTodayIncome;
}

void CShowRiderInfoDlg::ShowRiderInfo(BOOL bShow)
{ 
	m_bShowRiderInfo = bShow;  
	if(m_strWorkState == "업무중지") m_btnWorkState.SetWindowText("업무가능");
	else m_btnWorkState.SetWindowText("업무중지");
 
	if(LF->GetCurBranchInfo()->nShareCode1 != m_ci.GetShareCode(m_nCompany))
	{
		m_strTodayIncome = LF->GetMyNumberFormat(GetOtherRiderOrder());
	}
	else
	{
		if(m_pParentView != NULL)
			m_strTodayIncome = LF->GetMyNumberFormat(m_pParentView->GetRiderOrder(m_OrderList, m_nCompany, m_nRNo));
	}

	RefreshRefusalList();

	if(m_ci.IsChildCompany(m_nCompany))
	{
		m_btnLimitShareOrder.EnableWindow(FALSE);
		m_btnWorkState.EnableWindow(TRUE);
		m_btnHistory.EnableWindow(TRUE);
		m_btnAttend.EnableWindow(TRUE);
		m_btnCeritify.ShowWindow(SW_SHOW);
		m_btnChargeFor.EnableWindow(FALSE);
	}
	else
	{
		m_btnLimitShareOrder.EnableWindow(TRUE);
		m_btnWorkState.EnableWindow(FALSE);
		m_btnHistory.EnableWindow(FALSE);
		m_btnAttend.EnableWindow(FALSE);
		m_btnCeritify.ShowWindow(FALSE);
		m_btnChargeFor.EnableWindow(TRUE);
	}

	if(m_strCallBranch.GetLength() > 0)
		SetWindowText(CString("기사 정보창 ") + m_strCallBranch);
	else
		SetWindowText("기사 정보창");

	Invalidate();
}

HBRUSH CShowRiderInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd == this || pWnd == GetDlgItem(IDC_RIDER_STAT_STATIC))
	{
		return m_brush;
	}

	return hbr;
}

void CShowRiderInfoDlg::OnBnClickedOkBtn()
{
	OnOK();
}

void CShowRiderInfoDlg::RefreshRefusalList()
{
	m_lstShareRefusal.DeleteAllItems();

	long nSumBlackMarks;

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_share_refusal_info_1");
	cmd.AddParameter(m_nCompany);
	cmd.AddParameter(m_nRNo);
	CMkParameter *pParBlakcMarks = cmd.AddParameter(typeLong, typeOutput,sizeof(long), 0);

	if(!rs.Execute(&cmd)) return;

	pParBlakcMarks->GetValue(nSumBlackMarks);	

	m_strSumBlackMarks = LF->GetStringFromLong(nSumBlackMarks, TRUE) + "점";


	COleDateTime dtPrevent;
	long nPenaltyDay, nBlackMarks, nID, nType;
	CString strTitle;
	long nCompany, nRiderCompany, nRNo, nWCompany;
	CString strEtc;
	int i = 0; 

	while( !rs.IsEOF() )
	{
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("nType", nType);
		rs.GetFieldValue("dtPrevent", dtPrevent);
		rs.GetFieldValue("nPenaltyDay", nPenaltyDay);
		rs.GetFieldValue("nBlackMarks", nBlackMarks); 
		rs.GetFieldValue("sTitle", strTitle);
		rs.GetFieldValue("nCompany", nCompany);
		rs.GetFieldValue("nRiderCompany", nRiderCompany);
		rs.GetFieldValue("nRNo", nRNo);
		rs.GetFieldValue("sMemo", strEtc); 
		rs.GetFieldValue("nWCompany", nWCompany);  

		m_lstShareRefusal.InsertItem(0, nType == 0 ? "배차제한" : "공유게시판");

		if(nType == 0)
		{
			if(nPenaltyDay == 9999)
				m_lstShareRefusal.SetItemText(i, 1, "배차제한 무제한" );
			else
				m_lstShareRefusal.SetItemText(i, 1, "배차제한 " + LF->GetStringFromLong(nPenaltyDay) + "일");
		}
		else
		{
			m_lstShareRefusal.SetItemText(i, 1, "" );
		}		

		m_lstShareRefusal.SetItemText(i, 2, nBlackMarks == 0 ? "-" : LF->GetStringFromLong(nBlackMarks) + "점");
		m_lstShareRefusal.SetItemText(i, 3, strEtc);
		m_lstShareRefusal.SetItemText(i, 4, dtPrevent.Format("%y-%m-%d %H:%M"));
		m_lstShareRefusal.SetItemText(i, 5, m_ci.GetShareCompanyName(nWCompany));
		m_lstShareRefusal.SetItemText(i, 6, m_ci.GetShareCompanyName(nRiderCompany));
		m_lstShareRefusal.SetItemText(i, 7, LF->GetStringFromLong(nRNo));		
		m_lstShareRefusal.SetItemLong(i, nID);
		m_lstShareRefusal.SetItemLong2(i, nType);

		rs.MoveNext();
		i++;
	}

	m_lstShareRefusal.Populate();
}

BOOL CShowRiderInfoDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_OrderList.SetImageList(&ImageList,LVSIL_SMALL); 

	m_OrderList.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_OrderList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);

	m_OrderList.InsertColumn(0,"No.",LVCFMT_RIGHT,40);
	m_OrderList.InsertColumn(1,"상태",LVCFMT_LEFT,45);
	m_OrderList.InsertColumn(2,"소속",LVCFMT_LEFT,120);
	m_OrderList.InsertColumn(3,"출발지",LVCFMT_LEFT,115);
	m_OrderList.InsertColumn(4,"도착지",LVCFMT_LEFT,115);
	m_OrderList.InsertColumn(5,"접수",LVCFMT_CENTER,50);
	m_OrderList.InsertColumn(6,"배차",LVCFMT_CENTER,50);
	m_OrderList.InsertColumn(7,"완료",LVCFMT_CENTER,50);
	m_OrderList.InsertColumn(8,"요금",LVCFMT_RIGHT,55);

	m_lstShareRefusal.InsertColumn(0, "타입", LVCFMT_LEFT, 85);
	m_lstShareRefusal.InsertColumn(1, "적용", LVCFMT_LEFT, 95);
	m_lstShareRefusal.InsertColumn(2, "벌점", LVCFMT_LEFT, 45);
	m_lstShareRefusal.InsertColumn(3, "상세사유", LVCFMT_LEFT, 180);	
	m_lstShareRefusal.InsertColumn(4, "시각", LVCFMT_LEFT, 85);
	m_lstShareRefusal.InsertColumn(5, "등록회사", LVCFMT_LEFT, 80);
	m_lstShareRefusal.InsertColumn(6, "등록시근무회사", LVCFMT_LEFT, 100);
	m_lstShareRefusal.InsertColumn(7, "사번", LVCFMT_LEFT, 45);
	m_lstShareRefusal.Populate();

	int nCol = 0;
	m_RiderStatList.InsertColumn(nCol++, "타입", LVCFMT_LEFT, 45);
	m_RiderStatList.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_RiderStatList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);

	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	dtCur = dtCur - COleDateTimeSpan(0, 7, 0, 0);

	for(int i = 0 ; i < 14; i++)
	{
		dtCur = dtCur - COleDateTimeSpan(1, 0, 0, 0);

		CString strDay;
		strDay.Format("%d일", dtCur.GetDay());
		m_RiderStatList.InsertColumn(nCol++, strDay, LVCFMT_CENTER, 43);
	}

	return TRUE;
}

void CShowRiderInfoDlg::OnNMDblclkOrderList(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nItem = m_OrderList.GetNextItem(-1, LVNI_SELECTED);
	long nTNo = (long)m_OrderList.GetItemData(nItem);
	if(nTNo > 0)
	{
		m_pParentView->EditOrderFromTNo(nTNo);
		LU->ShowRiderInfoDlg(m_nCompany, m_nRNo);
	}
	*pResult = 0;
}


void CShowRiderInfoDlg::OnBnClickedCallBtn()
{
	LU->ShowCallPhoneRiderDlg(m_nCompany, m_nRNo, m_nOrderCompany, m_bDaeriRider);
}

void CShowRiderInfoDlg::OnBnClickedWorkStateBtn()
{

	if(!m_ci.IsChildCompany(m_nCompany)) {
		MessageBox("타사기사에 대해서, 적용할 수 없습니다.",
				"확인", MB_ICONINFORMATION);
		return;
	}

	CWorkStopMemoDlg dlg;
	if(dlg.DoModal() == IDOK) {
		LF->ChangeRiderWorkState(m_nCompany, m_nRNo,
				FALSE,
				dlg.m_strWorkStopMemo,  
				dlg.m_strContent,
				m_strWorkState == "업무중지" ? 0 : 1);

		LU->ShowRiderInfoDlg(m_nCompany, m_nRNo);
	}
}

void CShowRiderInfoDlg::SendOtherRiderMsg()
{
	CSendOtherRiderMsgDlg dlg;
	dlg.m_nRiderCompany = m_nCompany;
	dlg.m_nRNo = m_nRNo;

	dlg.DoModal();
}

void CShowRiderInfoDlg::OnBnClickedSendMsgBtn()
{
	if(!LF->POWER_CHECK(1200, "기사공지창 보기", TRUE))
		return;

	if(!m_ci.IsChildCompany(m_nCompany)) 
	{
		SendOtherRiderMsg();
		return;
	}

	MSG_RIDER_INFO *pInfo = new MSG_RIDER_INFO;
	CRiderMsgDlg dlg;
	dlg.SetIntegrated(m_ba.GetCount() > 2);
	dlg.SetCompanyCode(m_ci.m_nCompanyCode);
	pInfo->nCompany = m_nCompany;
	pInfo->nRNo = m_nRNo;
	dlg.m_paSelected.Add((MSG_RIDER_INFO*)pInfo);
	dlg.DoModal();
	delete pInfo;

}

void CShowRiderInfoDlg::OnBnClickedCancelStateBtn()
{
	int nItem = m_OrderList.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0)
	{
		long nTNo = (long)m_OrderList.GetItemData(nItem);
		if(nTNo > 0)
		{
			m_pParentView->CancelOrderFromTNo(nTNo);
			LU->ShowRiderInfoDlg(m_nCompany, m_nRNo);
		}
	}
}

void CShowRiderInfoDlg::OnBnClickedRcpStateBtn()
{
	int nItem = m_OrderList.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0)
	{
		long nTNo = (long)m_OrderList.GetItemData(nItem);
		if(nTNo > 0)
		{
			m_pParentView->RcpStateFromTNo(nTNo);
			LU->ShowRiderInfoDlg(m_nCompany, m_nRNo);
		}
	}
}

void CShowRiderInfoDlg::OnBnClickedRcpWaitBtn()
{
	int nItem = m_OrderList.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0)
	{
		long nTNo = (long)m_OrderList.GetItemData(nItem);
		if(nTNo > 0)
		{
			m_pParentView->RcpStateFromTNo(nTNo);
			LU->ShowRiderInfoDlg(m_nCompany, m_nRNo);
		}
	}
}

void CShowRiderInfoDlg::OnBnClickedLimitShareOrderBtn()
{
	CRiderAdviceDlg2010 dlg;
	dlg.m_nRiderCompany = m_nCompany;
	dlg.m_nRNo = m_nRNo;
	dlg.m_nCompany = m_ci.m_nCompanyCode;
	dlg.DoModal();
}

void CShowRiderInfoDlg::ShowRiderStatInfo(CMakeRiderStat &stat)
{
	m_RiderStatList.DeleteAllItems();

	if(!m_ci.IsChildCompany(m_nCompany)) {
		return;
	}
	
	long nItem = 0;
	char buffer[20], buffer2[20];

	m_RiderStatList.InsertItem(nItem++, "총콜수");
	m_RiderStatList.InsertItem(nItem++, "운행료");

	int nCol = 0; 
	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	dtCur = dtCur - COleDateTimeSpan(1, 0, 0, 0); 

	for(int i = 1 ; i <= 14; i++) 
	{
		dtCur = dtCur - COleDateTimeSpan(1, 0, 0, 0);
		CString strDate = dtCur.Format("%Y%m%d");
		CString strCharge = ltoa(stat.GetCharge(strDate), buffer, 10);

		m_RiderStatList.SetItemText(0, i, LF->RemoveZero(ltoa(stat.GetAllocCount(strDate), buffer2, 10)));
		m_RiderStatList.SetItemText(1, i, strCharge == "0" ? "" : strCharge + "천");
	}
}

void CShowRiderInfoDlg::OnBnClickedRiderCancelLogBtn()
{
	CRect rect;

	m_btnRiderCancelLog.GetClientRect(&rect);
	m_btnRiderCancelLog.ClientToScreen(&rect);

	CRiderCancelLogDlg pDlg;
	pDlg.m_pParent = this;
	pDlg.m_ParentRect = rect;
	pDlg.DoModal();    	
}

long CShowRiderInfoDlg::GetSendMoney()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_tno_charge");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nTNo);

	if(!pRs.Execute(&pCmd))
		return -1;

	long nChargeSum;
	pRs.GetFieldValue("nChargeSum", nChargeSum);

	pRs.Close();

	return nChargeSum;
}

void CShowRiderInfoDlg::TransferOK()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb,"insert_transfer_ok");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nTNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.strName);

	if(!pRs.Execute(&pCmd))
	{
		MessageBox("이체 중복 체크작업이 실패했습니다\r\n 선입금 내역을 확인하시기 바랍니다");
		return;
	}
}

void CShowRiderInfoDlg::OnBnClickedTransferBtn()
{
	TransferReal();
}

void CShowRiderInfoDlg::TransferReal()
{
	if(IsTransfer())
	{
		MessageBox("이미 이체 하였습니다.",  "확인", MB_ICONINFORMATION);
		return;
	}

	long nSendMoney = GetSendMoney();

	if(m_ci.GetShareCode1(m_nCompany) == m_ci.GetShareCode1(m_nOrderCompany)) // 자사기사일경우
	{
		if((m_ci.IsUseBranchShareReport(m_nCompany) == FALSE) && 
			(m_ci.IsUseBranchShareReport(m_nOrderCompany) == FALSE)) // 두회사 모두 지사간 정산을 안쓸때
		{
			CString sMsg;
			sMsg.Format("사번 %d번기사님에게 \r\n %d원을 선입금 충전을 하시겠습니까?", m_nRNo, nSendMoney);

			if(MessageBox(sMsg, "확인", MB_YESNO) == IDYES)
			{
				if(InsertCharge(nSendMoney)) //선입금 해줌
				{
					TransferOK();
				}
			}

			return;
		}
	}

	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ 타사로 이체후 선입금 생성하는 부분(지사간 이체 포함)

	long nOrderCompany;

	if(m_ci.IsUseBranchShareReport(m_nOrderCompany))	//지사기능을 갖추면 자기껄루 빠지구
	{
		nOrderCompany = m_nOrderCompany;
	}
	else //그렇지 않으면 본사껄루 빠지게
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_main_site");

		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nOrderCompany);

		if(!pRs.Execute(&pCmd)) return;

		pRs.GetFieldValue("nID", nOrderCompany);

		pRs.Close();
	}

	long nCharge = 0;
	long nDeposit = 0;
	CString strRName = "";

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_share_balance");

	pCmd.AddParameter(nOrderCompany);
	pCmd.AddParameter(m_nTNo);
	CMkParameter *parCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parDeposit = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parRName = pCmd.AddParameter(typeString, typeOutput, strRName.GetLength(), "");

	if(!pRs.Execute(&pCmd))
		return;

	long nAbilityMoney = 0;
	pRs.GetFieldValue("nAbility", nAbilityMoney);

	parCharge->GetValue(nCharge);
	parDeposit->GetValue(nDeposit);
	parRName->GetValue(strRName);

	pRs.Close();

	if(nAbilityMoney < nCharge)
	{
		MessageBox("이체 가능금액이 부족합니다", "확인", MB_ICONINFORMATION);
		return;
	}

	char buf[20];

	CString strMsg = "";
	strMsg += m_ci.GetName(nOrderCompany) + "(" + m_ci.GetBranchName(nOrderCompany) + ") 에서 \r\n";
	strMsg += m_ci.GetBranchName(m_nCompany) + " 사번" + CString(itoa(m_nRNo, buf, 10)) + "(" + strRName + ")님에게로\r\n";
	strMsg += CString(itoa(nCharge, buf, 10)) + "원을 입금합니다";

	if(MessageBox(strMsg, "확인", MB_OKCANCEL | MB_ICONINFORMATION) == IDOK)
	{
		strMsg += "\r\n\r\n다시 한번 확인하세요!!";

		if(MessageBox(strMsg, "확인", MB_OKCANCEL | MB_ICONINFORMATION) == IDOK)
			TransferPayLater(m_nTNo, m_nCompany, m_nRNo, strRName, nCharge);
	}
}

void CShowRiderInfoDlg::TransferPayLater(long nTNo, long nRiderCompany, long nRNo, CString strRName, long nSendMoney)
{
	long nRet;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "send_pay_later_1");

	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);		

	pCmd.AddParameter(nTNo);
	pCmd.AddParameter(nRiderCompany);
	pCmd.AddParameter(nRNo);
	pCmd.AddParameter(strRName);
	pCmd.AddParameter(m_nOrderCompany);
	pCmd.AddParameter(nSendMoney);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.strName);

	if(!pRs.Execute(&pCmd))
		return;

	parRet->GetValue(nRet);

	if(nRet == 100)
	{
		MessageBox("해당 기사님이 퇴사 혹은 정보가 변경되었습니다. \r\n 소속 사무실로 문의하시길 바랍니다 \r\n",
			"이체실패", MB_ICONERROR);

		return;
	}

	if(nRet == 1000)
	{
		MessageBox("이체 되었습니다. \r\n공유콜 정산 비율창에서 확인이 가능합니다 \r\n",
			"이체성공", MB_ICONINFORMATION);

	}
}


BOOL CShowRiderInfoDlg::InsertCharge(long nSendMoney)
{
	CString sEtc;
	sEtc.Format("신용오더 선입금 충전 오더번호(%d)", m_nTNo);

	CMkCommand pCmd(m_pMkDb, "insert_rider_deposit_save3");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nRNo);
	pCmd.AddParameter(typeString, typeInput, m_strRName.GetLength(), m_strRName);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nSendMoney);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);
	pCmd.AddParameter(typeString, typeInput, sEtc.GetLength(), sEtc);

	if(pCmd.Execute())
	{
		MessageBox("선입금을 생성하였습니다.", "확인", MB_ICONINFORMATION);
		return TRUE;
	}
	else {
		MessageBox("선입금 생성을 실패하였습니다.", "확인", MB_ICONINFORMATION);	
		return FALSE;
	}
	return true;
}

BOOL CShowRiderInfoDlg::IsTransfer()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_DeferredOrder");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nTNo);

	if(!pRs.Execute(&pCmd))
		return FALSE;

	if(pRs.GetRecordCount() == 0)
		return FALSE;

	return TRUE;

}

void CShowRiderInfoDlg::RiderWorkReport()
{

	UpdateData();
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_rider_work_report");
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(m_nRNo);
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	if(!pCmd.Execute()) return;
	long nOUTPUT =-1;
	pPar->GetValue(nOUTPUT);
	try
	{
		if(nOUTPUT == 1000)
			throw("출근 처리가 되었습니다.");
		else if(nOUTPUT == 2000)
			throw("이미 출근 처리가 되어 있습니다.");
		else if(nOUTPUT == 3000)
			throw("기사 정보가 없습니다.");
	}
	catch (CString e)
	{
		LF->MsgBox(e);
	}
	catch (char *e)
	{
		LF->MsgBox(e);
	}
		
}
void CShowRiderInfoDlg::OnBnClickedAttendBtn()
{
	RiderWorkReport();
}

void CShowRiderInfoDlg::OnBnClickedRiderShareBoardBtn()
{
	LU->CreateRiderShareBoardDlg(m_nCompany, m_nRNo, m_strRealRName);
}

void CShowRiderInfoDlg::OnBnClickedInitBtn()
{
	if(m_nCompany <= 0 || m_nRNo <= 0 )
	{
		MessageBox("기사의 회사코드 설정이 일치하지 않으니 로지소프트로 문의하여 주세요", "확인", MB_ICONINFORMATION);
		return;
	}


	CMkCommand cmd(m_pMkDb, "update_init_rider_certify_sub_1");
	cmd.AddParameter(m_nCompany);
	cmd.AddParameter(m_nRNo);
	cmd.AddParameter(m_strRealRName);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);
	if(!cmd.Execute()) return;

	MessageBox("인증이 초기화 되었습니다", "확인", MB_ICONINFORMATION);
}

void CShowRiderInfoDlg::SendMsgCTIForm(CString strPhoneNumber)
{
	if(LU->GetRcpView())
	{
		CRcpPageCTIForm *pForm = LU->GetRcpView()->m_pCTIForm;

		if(pForm)
		{
			pForm->RemoveRecordFileNameInsertID(strPhoneNumber);

			if (pForm->GetQueueRcpPopup() == TRUE)
				pForm->QueueRecvModeSecond();
		}
	}
}

void CShowRiderInfoDlg::OnOK()
{
	if (m_strRecvCID.GetLength() > 0)
		SendMsgCTIForm(m_strRecvCID);

	CMyDialog::OnOK();
}

void CShowRiderInfoDlg::OnCancel()
{
	if (m_strRecvCID.GetLength() > 0)
		SendMsgCTIForm(m_strRecvCID);

	CMyDialog::OnCancel();
}

void CShowRiderInfoDlg::OnBnClickedOtherRiderTransferBtn()
{
	if(!LF->POWER_CHECK(1530, "타기사충전"))
		return;

	COtherRiderTransferDlg dlg;
	dlg.m_nRiderCompany = m_nCompany;
	dlg.m_nRNo = m_nRNo;
	dlg.DoModal();	
}

void CShowRiderInfoDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if(pWnd->GetSafeHwnd() != m_OrderList.GetSafeHwnd())
		return;

	CPoint pt; 
	GetCursorPos(&pt); 

	BCMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU_1); 
	BCMenu *pRMenu = (BCMenu*)rMenu.GetSubMenu(FOUR); 
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y,this);

}

void CShowRiderInfoDlg::OnBnClickedTRSBtn()
{
	CTRSRiderDlg dlg;
	dlg.DoModal();
}

void CShowRiderInfoDlg::OnBnClickedChargeForBtn()
{
	CChargeForRiderDlg dlg;
	dlg.m_strCompany = m_ci.GetShareCompanyName(m_nCompany);
	dlg.m_strRNo = LF->GetStringFromLong(m_nRNo);
	dlg.m_strName = m_strRealRName;

	if(dlg.DoModal() == IDOK)
	{
		CMkCommand cmd(m_pMkDb, "request_charge_for_rider");
		cmd.AddParameter(m_nCompany);
		cmd.AddParameter(m_nRNo);
		cmd.AddParameter(m_strRealRName);
		cmd.AddParameter(dlg.m_nCharge);
		cmd.AddParameter(dlg.m_strEtc);
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ui.strName);

		if(cmd.Execute())
			MessageBox("성공적으로 청구 되었습니다\r\n보기 - 기사청구내역에서 확인 하실 수 있습니다", "확인", MB_ICONINFORMATION);
	}	
}

void CShowRiderInfoDlg::OnBnClickedRideridAcceptBtn()
{
	LU->GetRcpView()->CreateRcpDlg(NULL, "신규", -1, 0, m_strDeviceID, FALSE, -10, GetTickCount());
}

void CShowRiderInfoDlg::OnBnClickedRiderphoneAcceptBtn()
{
	LU->GetRcpView()->CreateRcpDlg(NULL, "신규", -1, 0, m_strPhone, FALSE, -10, GetTickCount());
}

void CShowRiderInfoDlg::OnBnClickedCallAcceptBtn()
{
	LU->GetRcpView()->CreateRcpDlg(NULL, "신규", -1, 0, "", FALSE, -10, GetTickCount());
}

void CShowRiderInfoDlg::OnStnClickedDrawStatic()
{
	CPoint pt;
	::GetCursorPos(&pt);
	ScreenToClient(&pt);

	if(m_rcDeviceID.PtInRect(pt))
	{
		if(::OpenClipboard(GetSafeHwnd()))
		{
			HGLOBAL clipbuffer;
			char * buffer;
			::EmptyClipboard();
			clipbuffer = GlobalAlloc(GMEM_DDESHARE, m_strDeviceID.GetLength() + 1);
			buffer = (char*)GlobalLock(clipbuffer);
			strcpy(buffer, LPCSTR(m_strDeviceID));
			GlobalUnlock(clipbuffer);
			::SetClipboardData(CF_TEXT,clipbuffer); 
			::CloseClipboard(); 
		}
		CString strText = "단말ID가 클립보드로 복사되었습니다.";
		MessageBox(strText, "확인", MB_ICONINFORMATION);
	}

	if(m_rcPhone.PtInRect(pt))
	{
		if(::OpenClipboard(GetSafeHwnd()))
		{
			HGLOBAL clipbuffer;
			char * buffer;
			::EmptyClipboard();
			clipbuffer = GlobalAlloc(GMEM_DDESHARE, m_strPhone.GetLength() + 1);
			buffer = (char*)GlobalLock(clipbuffer);
			strcpy(buffer, LPCSTR(m_strPhone));
			GlobalUnlock(clipbuffer);
			::SetClipboardData(CF_TEXT,clipbuffer); 
			::CloseClipboard(); 
		}
		CString strText = "휴대폰이 클립보드로 복사되었습니다.";
		MessageBox(strText, "확인", MB_ICONINFORMATION);
	}
}
