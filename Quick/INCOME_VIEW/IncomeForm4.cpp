// StaffPage2.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "IncomeForm4.h"
#include "DepositRateDlg.h"
#include "RiderMsgDlg.h"
#include "OtherAccountDlg.h"
#include "RiderDepositDlg.h"
#include "RcpView.h"
#include "RiderDepositInfoDlg.h"

#include "DepositGroupDlg.h"



IMPLEMENT_DYNCREATE(CIncomeForm4, CMyFormView)
CIncomeForm4::CIncomeForm4()
: CMyFormView(CIncomeForm4::IDD)
{
	m_bServerTime = FALSE;
	m_nCurSel = 0;
}

CIncomeForm4::~CIncomeForm4()
{
	m_List.SaveReportOrder("CIncomeForm4", "m_List");
}

void CIncomeForm4::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_EXAMPLE_DATE_STATIC, m_ExampleStatic);
	//	DDX_Control(pDX, IDC_SEARCH_EDIT, m_SearchEdit);
	DDX_Control(pDX, IDC_SHOW_BTN, m_ShowBtn);
	DDX_Control(pDX, IDC_MAKE_JOB_BTN, m_MakeJobBtn);
	DDX_Control(pDX, IDC_XTPLISTCTRL_EDIT, m_SearchEdit);
	DDX_Control(pDX, IDC_WORK_TYPE, m_cmbWorkType);
	DDX_Control(pDX, IDC_MAKE_DEPOSIT_GROUP_BTN, m_btnMakeDepositGroup);
}


BEGIN_MESSAGE_MAP(CIncomeForm4, CMyFormView)
	ON_BN_CLICKED(IDC_ONE_DAY_BTN, OnBnClickedOneDayBtn)
	ON_BN_CLICKED(IDC_SHOW_BTN, OnBnClickedShowBtn)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_INCOME_OK, OnIncomeOk)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
	ON_COMMAND(ID_MENU_MSG, OnSendMsg)
	ON_BN_CLICKED(IDC_CLEAR_DEPOSIT_BTN, OnBnClickedClearDepositBtn)
	ON_COMMAND(ID_EDIT_OTHER_ACCOUNT, OnEditOtherAccount)
	ON_COMMAND(ID_RIDER_DEPOSIT_MENU, OnRiderDepositMenu)
	ON_CBN_SELCHANGE(IDC_XTPLISTCTRL_COMBO, OnCbnSelchangeXtplistctrlCombo)
	ON_EN_CHANGE(IDC_XTPLISTCTRL_EDIT, OnEnChangeXtplistctrlEdit)
	ON_CBN_SELCHANGE(IDC_XTPLISTCTRL_TYPE_COMBO, OnCbnSelchangeXtplistctrlTypeCombo)
	ON_CBN_SELCHANGE(IDC_WORK_TYPE, OnCbnSelchangeWorkType)
	ON_BN_CLICKED(IDC_MAKE_DEPOSIT_GROUP_BTN, OnBnClickedMakeDepositGroupBtn)
END_MESSAGE_MAP()


// CIncomeForm4 �޽��� ó�����Դϴ�.

void CIncomeForm4::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate(); 

	m_List.SetExternalControl(GetDlgItem(IDC_XTPLISTCTRL_COMBO),
		GetDlgItem(IDC_XTPLISTCTRL_EDIT),			//SetExternalControl�Լ��� �����߿���
		GetDlgItem(IDC_XTPLISTCTRL_TYPE_COMBO));	//�ݵ�� InsertColumn�տ� �־����

	m_List.InsertColumn(0,"����ȣ",LVCFMT_CENTER,60);
	m_List.InsertColumn(1,"����",LVCFMT_LEFT, 90);
	m_List.InsertColumn(2,"������",LVCFMT_RIGHT,65);
	m_List.InsertColumn(3,"�Աݾ�",LVCFMT_RIGHT,50);
	m_List.InsertColumn(4,"�������ܾ�",LVCFMT_RIGHT, 70);
	m_List.InsertColumn(5,"�ڻ���",LVCFMT_CENTER, 65);
	m_List.InsertColumn(6,"Ÿ����",LVCFMT_CENTER, 65);
	m_List.InsertColumn(7,"������",LVCFMT_CENTER, 45);
	m_List.InsertColumn(8,"�ٹ�����",LVCFMT_CENTER, 75);
	m_List.InsertColumn(9,"�Աݹ��",LVCFMT_CENTER, 60);
	m_List.InsertColumn(10,"���Աݾ�",LVCFMT_RIGHT, 60);
	m_List.InsertColumn(11,"���Ա���",LVCFMT_LEFT, 70);
	m_List.InsertColumn(12,"��������",LVCFMT_CENTER, 60);
	m_List.InsertColumn(13,"��������",LVCFMT_RIGHT, 65);
	m_List.InsertColumn(14,"������������",LVCFMT_RIGHT, 80);
	m_List.InsertColumn(15,"��������",LVCFMT_RIGHT, 65);
	m_List.InsertColumn(16,"�ڵ���������",LVCFMT_RIGHT, 80);
	m_List.InsertColumn(17,"�Ϻ�����",LVCFMT_RIGHT, 80);
	//m_List.InsertColumn(14,"�ſ�����",LVCFMT_LEFT, 65);/
	//m_List.InsertColumn(15,"�����ſ��",LVCFMT_LEFT, 75);
	//m_List.InsertColumn(16, "�����ݾ�(���Ա�-�ſ����)", LVCFMT_RIGHT, 160);
	//m_List.InsertColumn(17, "�ſ봩����", LVCFMT_RIGHT, 80);

	m_cmbWorkType.SetCurSel(1);
	
	//m_List.InsertSearchAllColumn(0);
	//m_List.InsertSearchAllColumn(1);
	//m_List.InsertSearchAllColumn(14);

	//m_List.InsertTypeList("��������", 12, " ");
	//m_List.InsertTypeList("��������", 12, "����");

	m_List.LoadReportOrder("CIncomeForm4", "m_List");

	SetResize(IDC_LIST1, sizingRightBottom);

}



void CIncomeForm4::OnBnClickedOneDayBtn()
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();
	COleDateTime dtTo = COleDateTime::GetCurrentTime();
	CString strDate;	

	if(dtFrom.GetHour() < BASE_HOUR) {
		dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtFrom = dtTo - COleDateTimeSpan(1, 0, 0, 0);
	}
	else {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtTo = dtFrom + COleDateTimeSpan(1, 0, 0, 0);
	}

	strDate.Format("(%d��%d�� %d:00 ~ %d��%d�� %d:00)", 
		dtFrom.GetMonth(), dtFrom.GetDay(), dtFrom.GetHour(),
		dtTo.GetMonth(), dtTo.GetDay(), dtTo.GetHour());

	m_dtFrom = dtFrom;
	m_dtTo = dtTo;
	m_ExampleStatic.SetWindowText(strDate);
}

void CIncomeForm4::OnBnClickedShowBtn()
{
	RefreshList();
}


CString CIncomeForm4::GetFixedDepositType(long nFixedDeposit, BOOL bWeeklyDeposit, long nPaymentDay)
{
	if(nFixedDeposit <= 0)
		return "";

	CString strType;
	char* strDay[] = {"��", "��", "ȭ", "��", "��", "��", "��"};

	if(bWeeklyDeposit) //�ִ���
		strType.Format("�ֺ�[%s����]", strDay[nPaymentDay]);
	else
		strType.Format("����[%d��]", nPaymentDay, nFixedDeposit);

	return strType;
}

CString CIncomeForm4::GetFixedDepositDayString(long nFixedDeposit, COleDateTime dtNextDeposit, long &nRemainDays)
{
	if(nFixedDeposit <= 0)
		return "";

	if(dtNextDeposit.GetStatus() == COleDateTime::null) 
		return "";

	
	CString strNextDeposit;
	COleDateTimeSpan span = dtNextDeposit - COleDateTime::GetCurrentTime();


	//span = dtNextDeposit - COleDateTime::GetCurrentTime();
	
	nRemainDays = (long)span.GetTotalDays();
	if(nRemainDays > 3)
		strNextDeposit = dtNextDeposit.Format("%m-%d");
	else if(nRemainDays > 0)
		strNextDeposit.Format("%d�� ��", nRemainDays+1);
	else if(nRemainDays == 0)
		strNextDeposit = "����";
	else 
		strNextDeposit.Format("%d�� �����", abs(nRemainDays));

	return strNextDeposit;
}

CString CIncomeForm4::GetMyPercentString(long nPercent, BOOL bRemoveZero)
{
	CString strValue;
	if(bRemoveZero && nPercent == 0) 
		return "";

	strValue.Format("%d%%", nPercent);
	return strValue;
}

CString CIncomeForm4::GetCreditReportType(long nType)
{
	switch(nType)
	{
		case 1: 
			return "��������";
		case 2:
			return "���Ա�����";
		default:
			return "";
	}
}


void CIncomeForm4::RefreshList()
{
	CMyFormView::RefreshList();

	CString strText;
	int nSearchRNo = -1; 
	CString strSearchName;
	m_SearchEdit.GetWindowText(strText);

	UpdateData(TRUE);
	m_List.DeleteAllItems();

	typedef map<UINT, UINT> DEPOSIT_RATE;
	DEPOSIT_RATE deposit;

	if(!m_bServerTime)
	{
		CMkCommand pCmd(m_pMkDb, "select_server_time3");
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 0);
		CMkRecordset pRs(m_pMkDb);
		if(pRs.Execute(&pCmd))
		{
			pRs.GetFieldValue("curtime", m_dtCurrent);
			m_dtFrom = m_dtCurrent;
			pRs.Close();
			OnBnClickedOneDayBtn();
		}
		else {
			MessageBox("�����ð��� �о���� ���߽��ϴ�. ��� �� �ٽ� �õ��Ͻñ� �ٶ��ϴ�.", "�ð�üũ ����", MB_OK);
			m_bServerTime = TRUE;
			return;
		}
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_income_report_new12");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_cmbWorkType.GetCurSel());
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);
	if(!pRs.Execute(&pCmd)) return;

	long nCompany, nRNo, nCount, nDeposit, nRiderDeposit, nBalance, nCreditReportType;
	long nTodaySave, nCharge,  nCreditOrderSum; 
	long nCreditBalance;
	CString strRName;
	COleDateTime dtNextDeposit;
	char buffer[20];

	long nFixedDeposit;
	BOOL bWeeklyDeposit, bPenaltyCharge, bBranchAsOtherCall;
	long nPaymentDay, nWorkState, nDepositAllocateType;
	long nDepositType, nTodayDeposit, nTodayScheduleDeposit, nTodayCashSave, nDailyDepositCharge;
	CString sMyCallRateType, sOtherCallRateType;
	//nFixedDeposit �� 0���� ũ�� ���� Ȥ�� �ֺ�
	long nTodaySaveS = 0, nTodayDepositS = 0, nTodayScheduleDepositS = 0, nTodayCashSaveS = 0;
	long nChargeS = 0, nRiderDepositS = 0, nBalanceS = 0;
	int nItem = 0;
	for(nItem = 0; nItem < pRs.GetRecordCount(); nItem++)
	{
		long nRemainDays = 999;

		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sRName", strRName);
		pRs.GetFieldValue("nCount", nCount);
		pRs.GetFieldValue("nCharge", nCharge);
		pRs.GetFieldValue("nDeposit", nDeposit);
		pRs.GetFieldValue("nRiderDeposit", nRiderDeposit);
		pRs.GetFieldValue("nBalance", nBalance);
		pRs.GetFieldValue("nTodaySave", nTodaySave);
        pRs.GetFieldValue("dtNextDeposit", dtNextDeposit);
		pRs.GetFieldValue("nFixedDeposit", nFixedDeposit);
		pRs.GetFieldValue("bWeeklyDeposit", bWeeklyDeposit);
		pRs.GetFieldValue("nPaymentDay", nPaymentDay);
		pRs.GetFieldValue("bPenaltyCharge", bPenaltyCharge);
		pRs.GetFieldValue("bBranchAsOtherCall", bBranchAsOtherCall);
		pRs.GetFieldValue("nWorkState", nWorkState);
		pRs.GetFieldValue("nCreditReportType", nCreditReportType);
		pRs.GetFieldValue("nCreditOrderSum", nCreditOrderSum);
		pRs.GetFieldValue("nCreditBalance", nCreditBalance);	
		pRs.GetFieldValue("nDepositType", nDepositType);	
		pRs.GetFieldValue("nDepositAllocateType", nDepositAllocateType);
		pRs.GetFieldValue("sMyCallRateType", sMyCallRateType);	
		pRs.GetFieldValue("sOtherCallRateType", sOtherCallRateType);
		pRs.GetFieldValue("nTodayDeposit", nTodayDeposit);
		pRs.GetFieldValue("nTodayScheduleDeposit", nTodayScheduleDeposit);
		pRs.GetFieldValue("nTodayCashSave", nTodayCashSave);
		pRs.GetFieldValue("nDailyDepositCharge", nDailyDepositCharge);
		
		BOOL bRealTime = GetRealTime(nDepositType, nDepositAllocateType);

        m_List.InsertItem(nItem, ltoa(nRNo, buffer, 10), -1, 0); 
		m_List.SetItemText(nItem, 1, strRName);
		m_List.SetItemText(nItem, 2, LF->GetMyNumberFormat(nCharge));
		m_List.SetItemText(nItem, 3, LF->GetMyNumberFormat(nRiderDeposit));
		m_List.SetItemText(nItem, 4, LF->GetMyNumberFormat(nBalance)); 

		if(bRealTime)
		{
			m_List.SetItemText(nItem, 5, sMyCallRateType); 
			m_List.SetItemText(nItem, 6, sOtherCallRateType);
		}
		else
		{
			m_List.SetItemText(nItem, 5, "");
			m_List.SetItemText(nItem, 6, "");
		}
		
		m_List.SetItemText(nItem, 7, bRealTime == TRUE ? (bBranchAsOtherCall ? "Ÿ��" : "my") : ""); 
		m_List.SetItemText(nItem, 8, nDepositType < 50 ? GetFixedDepositType(nFixedDeposit, bWeeklyDeposit, nPaymentDay): "������");
		m_List.SetItemText(nItem, 9, nDepositAllocateType == 0 ? "���Ա�" : "");
		m_List.SetItemText(nItem, 10, nDepositType >= 20 ? (nFixedDeposit == 0 ? "" : 
			 		CString(LF->GetMyNumberFormat(nFixedDeposit / 10000)) + "����") : "");
		m_List.SetItemText(nItem, 11, nDepositType < 50 ? GetFixedDepositDayString(nFixedDeposit, dtNextDeposit, nRemainDays) : "");
		m_List.SetItemText(nItem, 12, nWorkState != 0 ? "����" : ""); 
		m_List.SetItemText(nItem, 13, LF->GetMyNumberFormat(nTodaySave));
		m_List.SetItemText(nItem, 14, LF->GetMyNumberFormat(nTodayCashSave));
		m_List.SetItemText(nItem, 15, LF->GetMyNumberFormat(nTodayDeposit));
		m_List.SetItemText(nItem, 16, LF->GetMyNumberFormat(nTodayScheduleDeposit));
		m_List.SetItemText(nItem, 17, LF->GetMyNumberFormat(nDailyDepositCharge));
		
		/*
		m_List.SetItemText(nItem, 14, GetCreditReportType(nCreditReportType));
		m_List.SetItemText(nItem, 15, nDepositType >= 20 ? (nCreditReportType == 2 ? LF->GetMyNumberFormat(nCreditOrderSum) : "") : "");
	
		long nTotal = 0;
		if(nFixedDeposit != 0)
		{
			if(nCreditReportType == 2)
				nTotal = nFixedDeposit - nCreditOrderSum;
			else
				nTotal = nFixedDeposit;
		}

		if(nTotal % 10000 == 0)
			m_List.SetItemText(nItem, 16, nDepositType >= 20 ? (nTotal == 0 ? "" : CString(LF->GetMyNumberFormat(nTotal / 10000)) + "����") : "");        
		else
			m_List.SetItemText(nItem, 16, nDepositType >= 20 ? (nTotal == 0 ? "" : CString(LF->GetMyNumberFormat(nTotal / 10000)) + "�� " + CString(LF->GetMyNumberFormat(nTotal % 10000)) + "��") : "");        

		m_List.SetItemText(nItem, 17, nCreditBalance == 0 ? "" : LF->GetMyNumberFormat(nCreditBalance));
*/
		m_List.SetItemData(nItem, (long)nCompany);
		m_List.SetItemLong(nItem, (long)nRemainDays);

		nTodayCashSaveS += nTodayCashSave;
		nTodaySaveS += nTodaySave, nTodayDepositS += nTodayDeposit, nTodayScheduleDepositS += nTodayScheduleDeposit;
		nChargeS += nCharge, nRiderDepositS += nRiderDeposit, nBalanceS += nBalance;

		pRs.MoveNext();
	}

	nItem = m_List.GetItemCount();

	m_List.InsertItem(nItem, "");
	m_List.SetItemText(nItem, 2, LF->GetMyNumberFormat(nChargeS));
	m_List.SetItemText(nItem, 3, LF->GetMyNumberFormat(nRiderDepositS));
	m_List.SetItemText(nItem, 4, LF->GetMyNumberFormat(nBalanceS));
	m_List.SetItemText(nItem, 13, LF->GetMyNumberFormat(nTodaySaveS));
	m_List.SetItemText(nItem, 14, LF->GetMyNumberFormat(nTodayCashSaveS));
	m_List.SetItemText(nItem, 15, LF->GetMyNumberFormat(nTodayDepositS));
	m_List.SetItemText(nItem, 16, LF->GetMyNumberFormat(nTodayScheduleDepositS));

	m_List.Populate();
	//m_List.EnsureVisibleEx(m_nCurSel);
	pRs.Close();
}

void CIncomeForm4::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {
		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(6);

		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}
}

void CIncomeForm4::OnIncomeOk()
{
	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {
		CRiderDepositInfoDlg dlg;
		dlg.m_nRiderCompany = (long)m_List.GetItemData(nItem);
		dlg.m_nRNo = atol(m_List.GetItemText(nItem, 0));
		dlg.m_strRName = m_List.GetItemText(nItem, 1);

		if(dlg.DoModal() == IDOK)
		{
			MessageBox("����Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
			RefreshList();
		}
	}
}

void CIncomeForm4::OnViewExcel()
{
	if(!LF->POWER_CHECK(7900, "������ȯ", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 501, m_List.GetItemCount());  
	m_List.ToExcel("�Ա�����");
}

void CIncomeForm4::OnNMDblclkList1(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	OnIncomeOk();
}

void CIncomeForm4::OnSendMsg()
{
	//if(!LF->POWER_CHECK(1200, "������â ����", TRUE))
	//	return;

	int nSelItem = m_List.GetNextItem(-1, LVNI_SELECTED);

	if(nSelItem >= 0) {
		CRiderMsgDlg dlg;
		CString strRName = m_List.GetItemText(nSelItem, 1);
		int nDebtSum = LF->GetNoneCommaNumber(m_List.GetItemText(nSelItem, 4)) +
			LF->GetNoneCommaNumber(m_List.GetItemText(nSelItem, 6));
		int nPreDeposit = LF->GetNoneCommaNumber(m_List.GetItemText(nSelItem, 5));
		CString strDepositType = m_List.GetItemText(nSelItem, 9);

		dlg.m_nRNo = atol(m_List.GetItemText(nSelItem, 0));
		dlg.SetCompanyCode(m_List.GetItemData(nSelItem));
		dlg.m_strMsg.Format("%s ����, ���� ������ �ܾ��� %s�� �Դϴ�. �߰� �Աݹٶ��ϴ�.", 
			strRName, LF->GetMyNumberFormat(m_List.GetItemText(nSelItem, 4)));

		dlg.DoModal();	
	}
}

BOOL CIncomeForm4::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{	
		if(pMsg->hwnd == m_SearchEdit.GetSafeHwnd()) {
			RefreshList();
		}
	}

	return CMyFormView::PreTranslateMessage(pMsg);
}

void CIncomeForm4::OnBnClickedClearDepositBtn()
{
	if(IDYES == MessageBox("�̼��ݳ������� ���Աݿ��� �����մϴ�.\n"\
		"��, ���Ա��� ������ ��쿡 �������� �ʽ��ϴ�."\
		"�����Ͻðڽ��ϱ�?", "������ �̼��� �ڵ�����",
		MB_ICONINFORMATION | MB_YESNO))
	{
		//CWaitCursor wait;
		CMkCommand pCmd(m_pMkDb, "request_clear_company_deposit_1");
		CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
		pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_ci.m_bRcpIntMode1 ? MAKE_SHARE_CODE(m_ci.m_nShareCode1) : -1);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int),
			m_ci.m_bRcpIntMode2 ? MAKE_SHARE_CODE(m_ci.m_nShareCode2) : -1);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_ci.m_bRcpIntMode3 ? MAKE_SHARE_CODE(m_ci.m_nShareCode3) : -1);

		if(pCmd.Execute())
		{
			if(parRet->GetLong() == 10)
			{
				MessageBox("�̼��� �ڵ����� ���ɽð��� ���� 10�ú��� - ���� 7�ñ��� �Դϴ�.\n"\
					"������ ���ϰ� ���� �ɸ��� �����, �����ð����� ����ϽǼ� �����ϴ�.\n",
					"���� ����", MB_ICONINFORMATION);
			}
			else
			{
				MessageBox("�������� �̼��� ������û�� �Ͽ����ϴ�.\n"\
					"��׶��� �۾����� ������ �������Դϴ�.(�ִ�1���Ŀ� ���۵�)\n"\
					"��ϱ�簡 ���� ��쿡�� ��ʺб��� �ɸ��� �ֽ��ϴ�.\n"\
					"�˻���ư�� �����ż� ������ �Ϸ�Ǿ����� Ȯ���Ͻð�\n"\
					"�Աݰ��� �ٸ� �۾��� �����Ͻñ� �ٶ��ϴ�.",
					"���� ����",
					MB_ICONINFORMATION);
			}
		}
	}
}

void CIncomeForm4::OnEditOtherAccount()
{
	//if(!LF->POWER_CHECK(7012, "�Ա����� ��������", TRUE))
	//	return;

	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {

		COtherAccountDlg dlg;
		dlg.m_strAccount = m_List.GetItemText(nItem, 14);
		if(IDOK == dlg.DoModal())
		{
			long nCompany = m_List.GetItemData(nItem);
			long nRNo = atol(m_List.GetItemText(nItem, 0));

			CMkCommand pCmd(m_pMkDb, "update_other_account_info");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo);
			pCmd.AddParameter(typeString, typeInput, dlg.m_strAccount.GetLength(), dlg.m_strAccount);
			if(!pCmd.Execute())
			{
				MessageBox("����������", "����������", MB_ICONINFORMATION);
			}
		}
	}
}

void CIncomeForm4::OnRiderDepositMenu()
{
	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {

		CRiderDepositDlg dlg;
		dlg.m_strDeposit = m_List.GetItemText(nItem, 13);
		if(IDOK == dlg.DoModal())
		{
			long nCompany = m_List.GetItemLong(nItem);
			long nRNo = atol(m_List.GetItemText(nItem, 0));
			long nDepositCharge = LF->GetNoneCommaNumber(dlg.m_strDeposit);

			CMkCommand pCmd(m_pMkDb, "update_deposit_of_a_rider");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nDepositCharge);
			if(!pCmd.Execute())
			{
				MessageBox("����������", "����������", MB_ICONINFORMATION);
			}
		}
	}
}

void CIncomeForm4::OnCbnSelchangeXtplistctrlCombo()
{
	OnEnChangeXtplistctrlEdit();
}

void CIncomeForm4::OnEnChangeXtplistctrlEdit()
{
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_XTPLISTCTRL_COMBO);
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_XTPLISTCTRL_EDIT);
	CComboBox *pTypeCombo = (CComboBox*)GetDlgItem(IDC_XTPLISTCTRL_TYPE_COMBO);

	CString strText;
	pEdit->GetWindowText(strText);
	strText.Trim();

	int nTypeData;
	if(pTypeCombo == NULL)
		nTypeData = -1;
	else
		nTypeData = (int)pTypeCombo->GetItemData(pTypeCombo->GetCurSel());

	m_List.Filter(strText, pCombo->GetCurSel(), nTypeData);
}

void CIncomeForm4::OnCbnSelchangeXtplistctrlTypeCombo()
{
	OnEnChangeXtplistctrlEdit();
}


BOOL CIncomeForm4::GetRealTime(long nDepositType, long nDepositAllocateType)
{
	if(nDepositType == 20 || nDepositType == 30 || nDepositType == 40)
	{
		if(nDepositAllocateType == 0)
			return TRUE;

		if(nDepositAllocateType == 10)
			return FALSE;

	}
	else if(nDepositType  == 50)
		return TRUE;

	return FALSE;

}
void CIncomeForm4::OnCbnSelchangeWorkType()
{
	RefreshList();
}

void CIncomeForm4::OnBnClickedMakeDepositGroupBtn()
{
	CDepositGroupDlg dlg;
	dlg.DoModal();
}
