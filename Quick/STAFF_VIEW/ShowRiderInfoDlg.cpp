// ShowRiderInfoDlg.cpp : ���� �����Դϴ�.
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

// CShowRiderInfoDlg ��ȭ �����Դϴ�.

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


// CShowRiderInfoDlg �޽��� ó�����Դϴ�.
void CShowRiderInfoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CMyDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
	DrawRiderInfo(&dc);
}

void CShowRiderInfoDlg::DrawRiderInfo(CDC *pDC)
{
	CXTPPenDC pen(*pDC, RGB(0, 0, 255));
	CXTPFontDC font(pDC, m_FontManager.GetFont("����ü", 13, FW_BOLD));
	pDC->SetBkMode(TRANSPARENT);

	CRect rc;
	m_stc1.GetClientRect(rc);
	rc.right = rc.left + 200;
	DrawInfoBox(pDC, rc);
	rc.DeflateRect(5, 5, 5, 5);
	PrintLine(pDC, rc, "ȸ���", m_strCompany);
	PrintLine(pDC, rc, "�����", m_strBranch);
	PrintLine(pDC, rc, "��", m_strCompanyPhone + "/" + m_strOfficePhone, TRUE);
	PrintLine(pDC, rc, "����", m_strRName, TRUE);
	m_rcDeviceID = rc; m_rcDeviceID.bottom = m_rcDeviceID.top + 18;
	PrintLine(pDC, rc, "�ܸ�ID", m_strDeviceID);
	PrintLine(pDC, rc, "�ܸ�����", m_strDeviceType);
	PrintLine(pDC, rc, "�ܸ�����", m_strDeviceVer, TRUE);
	m_rcPhone = rc; m_rcPhone.bottom = m_rcPhone.top + 18;
	PrintLine(pDC, rc, "�޴���", m_strPhone); 
	PrintLine(pDC, rc, "����ȭ", m_strHomePhone);
	PrintLine(pDC, rc, "�Ի���", m_strEnterDate); 

	m_stc1.GetClientRect(rc);
	rc.left += 201;
	rc.right = rc.left + 200;
	DrawInfoBox(pDC, rc);
	rc.DeflateRect(5, 5, 5, 5);
	PrintLine(pDC, rc, "�Աݹ��", m_strDepositType);
	PrintLine(pDC, rc, "���ϼ���", m_strTodayIncome, FALSE, RGB(200, 0, 0));
	PrintLine(pDC, rc, "��  ��", m_strBalance, FALSE, RGB(200, 0, 0));
	PrintLine(pDC, rc, "��������", m_strTodaySave, TRUE, RGB(200, 0, 0));
	PrintLine(pDC, rc, "��������", m_strWorkState);
	PrintLine(pDC, rc, "�Ǽ�����", m_strCountLimit);
	PrintLine(pDC, rc, "�ð�����", m_strTimeLimit, TRUE);
	PrintDualLine(pDC, rc, "��������", m_strInsInfo);
	PrintLine(pDC, rc, "���踸��", m_strInsExpDate);
	PrintLine(pDC, rc, "�������", m_strLicenseState, TRUE, m_bLicenseOK ? RGB(0, 0, 0) : RGB(200, 0, 0));

	m_stc1.GetClientRect(rc);
	rc.left += 402; 
	DrawInfoBox(pDC, rc);
	rc.DeflateRect(5, 5, 5, 5); 
	PrintLine(pDC, rc, "�����̷�", "");
	PrintLine(pDC, rc, "", "");
	PrintLine(pDC, rc, "����", m_strSumBlackMarks, TRUE, RGB(255, 0, 0)); 
	PrintLine(pDC, rc, "������ȣ", m_strCarNo, FALSE); 
	PrintLine(pDC, rc, "����������", m_strBusinessCar, FALSE); 
	PrintLine(pDC, rc, "����", m_strCarType, FALSE);
	PrintLine(pDC, rc, "���繰����", m_strLoadInsState, FALSE);

	if(m_strPhone.Find("*") >= 0) 
	{
		PrintLine(pDC, rc, "", "");
		PrintLine(pDC, rc, "", "");
		PrintLine(pDC, rc, "4�ð��������� Ÿ���� ���� ��ǥ�û���", FALSE, RGB(200, 0, 0));
	}

//	PrintLine(pDC, rc, "", "");
//	PrintLine(pDC, rc, "", "");
//	PrintLine(pDC, rc, "", "");
//	PrintLine(pDC, rc, "", "�˻���ư �����ø� ��������� ������ϴ�.", FALSE, RGB(255, 255, 255));
//	PrintLine(pDC, rc, "", "�ٽú��÷��� F8Ű �����ñ� �ٶ��ϴ�.", FALSE, RGB(255, 255, 255));
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
		m_OrderList.InsertItem(nItem++, "�հ�");
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
		m_OrderList.SetItemText(0, 1, CString(ltoa(nRecordCount, buffer, 10)) + "��");
		m_OrderList.SetItemText(0, 2, CString(ltoa(nSum, buffer, 10)) + "��");
		m_OrderList.SetItemText(0, 3, "���� : " + CString(itoa(nCashCount, buffer, 10)) + "/" + LF->GetMyNumberFormat(nCashSum));
		m_OrderList.SetItemText(0, 4, "�ſ� : " + CString(itoa(nCreditCount, buffer, 10)) + "/" + LF->GetMyNumberFormat(nCreditSum));
		m_OrderList.SetItemData(0, 0);
	}

	return nTodayIncome;
}

void CShowRiderInfoDlg::ShowRiderInfo(BOOL bShow)
{ 
	m_bShowRiderInfo = bShow;  
	if(m_strWorkState == "��������") m_btnWorkState.SetWindowText("��������");
	else m_btnWorkState.SetWindowText("��������");
 
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
		SetWindowText(CString("��� ����â ") + m_strCallBranch);
	else
		SetWindowText("��� ����â");

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

	m_strSumBlackMarks = LF->GetStringFromLong(nSumBlackMarks, TRUE) + "��";


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

		m_lstShareRefusal.InsertItem(0, nType == 0 ? "��������" : "�����Խ���");

		if(nType == 0)
		{
			if(nPenaltyDay == 9999)
				m_lstShareRefusal.SetItemText(i, 1, "�������� ������" );
			else
				m_lstShareRefusal.SetItemText(i, 1, "�������� " + LF->GetStringFromLong(nPenaltyDay) + "��");
		}
		else
		{
			m_lstShareRefusal.SetItemText(i, 1, "" );
		}		

		m_lstShareRefusal.SetItemText(i, 2, nBlackMarks == 0 ? "-" : LF->GetStringFromLong(nBlackMarks) + "��");
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
	m_OrderList.InsertColumn(1,"����",LVCFMT_LEFT,45);
	m_OrderList.InsertColumn(2,"�Ҽ�",LVCFMT_LEFT,120);
	m_OrderList.InsertColumn(3,"�����",LVCFMT_LEFT,115);
	m_OrderList.InsertColumn(4,"������",LVCFMT_LEFT,115);
	m_OrderList.InsertColumn(5,"����",LVCFMT_CENTER,50);
	m_OrderList.InsertColumn(6,"����",LVCFMT_CENTER,50);
	m_OrderList.InsertColumn(7,"�Ϸ�",LVCFMT_CENTER,50);
	m_OrderList.InsertColumn(8,"���",LVCFMT_RIGHT,55);

	m_lstShareRefusal.InsertColumn(0, "Ÿ��", LVCFMT_LEFT, 85);
	m_lstShareRefusal.InsertColumn(1, "����", LVCFMT_LEFT, 95);
	m_lstShareRefusal.InsertColumn(2, "����", LVCFMT_LEFT, 45);
	m_lstShareRefusal.InsertColumn(3, "�󼼻���", LVCFMT_LEFT, 180);	
	m_lstShareRefusal.InsertColumn(4, "�ð�", LVCFMT_LEFT, 85);
	m_lstShareRefusal.InsertColumn(5, "���ȸ��", LVCFMT_LEFT, 80);
	m_lstShareRefusal.InsertColumn(6, "��Ͻñٹ�ȸ��", LVCFMT_LEFT, 100);
	m_lstShareRefusal.InsertColumn(7, "���", LVCFMT_LEFT, 45);
	m_lstShareRefusal.Populate();

	int nCol = 0;
	m_RiderStatList.InsertColumn(nCol++, "Ÿ��", LVCFMT_LEFT, 45);
	m_RiderStatList.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_RiderStatList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);

	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	dtCur = dtCur - COleDateTimeSpan(0, 7, 0, 0);

	for(int i = 0 ; i < 14; i++)
	{
		dtCur = dtCur - COleDateTimeSpan(1, 0, 0, 0);

		CString strDay;
		strDay.Format("%d��", dtCur.GetDay());
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
		MessageBox("Ÿ���翡 ���ؼ�, ������ �� �����ϴ�.",
				"Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CWorkStopMemoDlg dlg;
	if(dlg.DoModal() == IDOK) {
		LF->ChangeRiderWorkState(m_nCompany, m_nRNo,
				FALSE,
				dlg.m_strWorkStopMemo,  
				dlg.m_strContent,
				m_strWorkState == "��������" ? 0 : 1);

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
	if(!LF->POWER_CHECK(1200, "������â ����", TRUE))
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

	m_RiderStatList.InsertItem(nItem++, "���ݼ�");
	m_RiderStatList.InsertItem(nItem++, "�����");

	int nCol = 0; 
	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	dtCur = dtCur - COleDateTimeSpan(1, 0, 0, 0); 

	for(int i = 1 ; i <= 14; i++) 
	{
		dtCur = dtCur - COleDateTimeSpan(1, 0, 0, 0);
		CString strDate = dtCur.Format("%Y%m%d");
		CString strCharge = ltoa(stat.GetCharge(strDate), buffer, 10);

		m_RiderStatList.SetItemText(0, i, LF->RemoveZero(ltoa(stat.GetAllocCount(strDate), buffer2, 10)));
		m_RiderStatList.SetItemText(1, i, strCharge == "0" ? "" : strCharge + "õ");
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
		MessageBox("��ü �ߺ� üũ�۾��� �����߽��ϴ�\r\n ���Ա� ������ Ȯ���Ͻñ� �ٶ��ϴ�");
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
		MessageBox("�̹� ��ü �Ͽ����ϴ�.",  "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	long nSendMoney = GetSendMoney();

	if(m_ci.GetShareCode1(m_nCompany) == m_ci.GetShareCode1(m_nOrderCompany)) // �ڻ����ϰ��
	{
		if((m_ci.IsUseBranchShareReport(m_nCompany) == FALSE) && 
			(m_ci.IsUseBranchShareReport(m_nOrderCompany) == FALSE)) // ��ȸ�� ��� ���簣 ������ �Ⱦ���
		{
			CString sMsg;
			sMsg.Format("��� %d�����Կ��� \r\n %d���� ���Ա� ������ �Ͻðڽ��ϱ�?", m_nRNo, nSendMoney);

			if(MessageBox(sMsg, "Ȯ��", MB_YESNO) == IDYES)
			{
				if(InsertCharge(nSendMoney)) //���Ա� ����
				{
					TransferOK();
				}
			}

			return;
		}
	}

	//������������������� Ÿ��� ��ü�� ���Ա� �����ϴ� �κ�(���簣 ��ü ����)

	long nOrderCompany;

	if(m_ci.IsUseBranchShareReport(m_nOrderCompany))	//�������� ���߸� �ڱⲬ�� ������
	{
		nOrderCompany = m_nOrderCompany;
	}
	else //�׷��� ������ ���粬�� ������
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
		MessageBox("��ü ���ɱݾ��� �����մϴ�", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	char buf[20];

	CString strMsg = "";
	strMsg += m_ci.GetName(nOrderCompany) + "(" + m_ci.GetBranchName(nOrderCompany) + ") ���� \r\n";
	strMsg += m_ci.GetBranchName(m_nCompany) + " ���" + CString(itoa(m_nRNo, buf, 10)) + "(" + strRName + ")�Կ��Է�\r\n";
	strMsg += CString(itoa(nCharge, buf, 10)) + "���� �Ա��մϴ�";

	if(MessageBox(strMsg, "Ȯ��", MB_OKCANCEL | MB_ICONINFORMATION) == IDOK)
	{
		strMsg += "\r\n\r\n�ٽ� �ѹ� Ȯ���ϼ���!!";

		if(MessageBox(strMsg, "Ȯ��", MB_OKCANCEL | MB_ICONINFORMATION) == IDOK)
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
		MessageBox("�ش� ������ ��� Ȥ�� ������ ����Ǿ����ϴ�. \r\n �Ҽ� �繫�Ƿ� �����Ͻñ� �ٶ��ϴ� \r\n",
			"��ü����", MB_ICONERROR);

		return;
	}

	if(nRet == 1000)
	{
		MessageBox("��ü �Ǿ����ϴ�. \r\n������ ���� ����â���� Ȯ���� �����մϴ� \r\n",
			"��ü����", MB_ICONINFORMATION);

	}
}


BOOL CShowRiderInfoDlg::InsertCharge(long nSendMoney)
{
	CString sEtc;
	sEtc.Format("�ſ���� ���Ա� ���� ������ȣ(%d)", m_nTNo);

	CMkCommand pCmd(m_pMkDb, "insert_rider_deposit_save3");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nRNo);
	pCmd.AddParameter(typeString, typeInput, m_strRName.GetLength(), m_strRName);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nSendMoney);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);
	pCmd.AddParameter(typeString, typeInput, sEtc.GetLength(), sEtc);

	if(pCmd.Execute())
	{
		MessageBox("���Ա��� �����Ͽ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		return TRUE;
	}
	else {
		MessageBox("���Ա� ������ �����Ͽ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);	
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
			throw("��� ó���� �Ǿ����ϴ�.");
		else if(nOUTPUT == 2000)
			throw("�̹� ��� ó���� �Ǿ� �ֽ��ϴ�.");
		else if(nOUTPUT == 3000)
			throw("��� ������ �����ϴ�.");
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
		MessageBox("����� ȸ���ڵ� ������ ��ġ���� ������ ��������Ʈ�� �����Ͽ� �ּ���", "Ȯ��", MB_ICONINFORMATION);
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

	MessageBox("������ �ʱ�ȭ �Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
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
	if(!LF->POWER_CHECK(1530, "Ÿ�������"))
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
			MessageBox("���������� û�� �Ǿ����ϴ�\r\n���� - ���û���������� Ȯ�� �Ͻ� �� �ֽ��ϴ�", "Ȯ��", MB_ICONINFORMATION);
	}	
}

void CShowRiderInfoDlg::OnBnClickedRideridAcceptBtn()
{
	LU->GetRcpView()->CreateRcpDlg(NULL, "�ű�", -1, 0, m_strDeviceID, FALSE, -10, GetTickCount());
}

void CShowRiderInfoDlg::OnBnClickedRiderphoneAcceptBtn()
{
	LU->GetRcpView()->CreateRcpDlg(NULL, "�ű�", -1, 0, m_strPhone, FALSE, -10, GetTickCount());
}

void CShowRiderInfoDlg::OnBnClickedCallAcceptBtn()
{
	LU->GetRcpView()->CreateRcpDlg(NULL, "�ű�", -1, 0, "", FALSE, -10, GetTickCount());
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
		CString strText = "�ܸ�ID�� Ŭ������� ����Ǿ����ϴ�.";
		MessageBox(strText, "Ȯ��", MB_ICONINFORMATION);
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
		CString strText = "�޴����� Ŭ������� ����Ǿ����ϴ�.";
		MessageBox(strText, "Ȯ��", MB_ICONINFORMATION);
	}
}
