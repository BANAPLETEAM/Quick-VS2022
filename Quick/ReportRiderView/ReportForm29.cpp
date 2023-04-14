// ReportForm20.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm29.h"
#include "RequestDrawingDlg.h"

// CReportForm29

IMPLEMENT_DYNCREATE(CReportForm29, CMyFormView)

CReportForm29::CReportForm29()
: CMyFormView(CReportForm29::IDD)
{
	m_nRiderCompany = 0;
	m_nRNo = 0;
}

CReportForm29::~CReportForm29()
{
}

void CReportForm29::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_RIDER_REPORT, m_lstRider);
	DDX_Control(pDX, IDC_EACH_LOG_REPORT, m_lstEachLog);
	DDX_Control(pDX, IDC_ALL_LOG_REPORT, m_lstAllLog);
	DDX_Control(pDX, IDC_BANK_COMBO, m_cmbBank);
	DDX_Control(pDX, IDC_RIDER_NAME_EDIT, m_edtRiderName);
	DDX_Control(pDX, IDC_ACCOUNT_EDIT, m_edtAccount);
	DDX_Control(pDX, IDC_DEPOSIT_NAME_EDIT, m_edtDepositName);
	DDX_Control(pDX, IDC_SHARE_BALANCE_EDIT, m_edtShareBalance);
	DDX_Control(pDX, IDC_AMOUNT_EDIT, m_edtAMount);
	DDX_Control(pDX, IDC_PHONE_EDIT, m_edtPhone);
	DDX_Control(pDX, IDC_ETC_EDT, m_edtEtc);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_SEARCH_ETC_EDT, m_edtShEtc);
}

BEGIN_MESSAGE_MAP(CReportForm29, CMyFormView)
	ON_NOTIFY(XTP_NM_GRID_SELCHANGED, IDC_RIDER_REPORT, OnReportItemSelChanged)
	ON_NOTIFY(NM_CLICK, IDC_EACH_LOG_REPORT, OnReportItemEachClick)
	ON_NOTIFY(NM_CLICK, IDC_ALL_LOG_REPORT, OnReportItemAllClick)
	ON_BN_CLICKED(IDC_DRAWING_BTN, &CReportForm29::OnBnClickedDrawingBtn)
	ON_BN_CLICKED(IDC_REFRESH_BTN2, &CReportForm29::OnBnClickedRefreshBtn2)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CReportForm29::OnEnChangeSearchEdit)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CReportForm29::OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_SAVE_BTN, &CReportForm29::OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_REFRESH_LOG_BTN, &CReportForm29::OnBnClickedRefreshLogBtn)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_EN_CHANGE(IDC_SEARCH_ETC_EDT, &CReportForm29::OnEnChangeSearchEtcEdt)
END_MESSAGE_MAP()


// CReportForm29 �����Դϴ�.

#ifdef _DEBUG
void CReportForm29::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CReportForm29::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CReportForm29 �޽��� ó�����Դϴ�.

void CReportForm29::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_btnDate.InitDateButton(&m_FromDT, &m_ToDT);
	m_btnDate.OnMenuMonthIncludeToday();

	m_edtShEtc.SetMyFont("���� ���", 15, FW_BOLD);
	m_edtShEtc.SetUserOption(RGB(0, 0, 255), RGB(255, 255, 255), "����");

	m_lstRider.InsertColumn(0, "�����", LVCFMT_LEFT, 90);
	m_lstRider.InsertColumn(1, "���", LVCFMT_LEFT, 50);
	m_lstRider.InsertColumn(2, "�̸�", LVCFMT_LEFT, 70);
	m_lstRider.InsertColumn(3, "�ܾ�", LVCFMT_RIGHT, 60);
	m_lstRider.InsertColumn(4, "����", LVCFMT_RIGHT, 50);
	m_lstRider.Populate();

	m_lstEachLog.InsertColumn(0, "�����", LVCFMT_LEFT, 90);
	m_lstEachLog.InsertColumn(1, "���", LVCFMT_LEFT, 50);
	m_lstEachLog.InsertColumn(2, "�̸�", LVCFMT_LEFT, 70);
	m_lstEachLog.InsertColumn(3, "����", LVCFMT_CENTER, 50);
	m_lstEachLog.InsertColumn(4, "��û�ݾ�", LVCFMT_RIGHT, 60);
	m_lstEachLog.InsertColumn(5, "��û����", LVCFMT_CENTER, 90);
	m_lstEachLog.InsertColumn(6, "����", LVCFMT_LEFT, 40);
	m_lstEachLog.InsertColumn(7, "����", LVCFMT_LEFT, 100);
	m_lstEachLog.InsertColumn(8, "������", LVCFMT_LEFT, 70);
	m_lstEachLog.InsertColumn(9, "����", LVCFMT_LEFT, 100);
	m_lstEachLog.InsertColumn(10, "�޴���", LVCFMT_LEFT, 100);
	m_lstEachLog.InsertColumn(11, "��û���", LVCFMT_LEFT, 100);
	m_lstEachLog.InsertColumn(12, "�۾���", LVCFMT_LEFT, 70);
	m_lstEachLog.Populate();

	m_lstAllLog.InsertColumn(0, "�����", LVCFMT_LEFT, 90);
	m_lstAllLog.InsertColumn(1, "���", LVCFMT_LEFT, 50);
	m_lstAllLog.InsertColumn(2, "�̸�", LVCFMT_LEFT, 70);
	m_lstAllLog.InsertColumn(3, "����", LVCFMT_CENTER, 50);
	m_lstAllLog.InsertColumn(4, "��û�ݾ�", LVCFMT_RIGHT, 60);
	m_lstAllLog.InsertColumn(5, "��û����", LVCFMT_CENTER, 90);
	m_lstAllLog.InsertColumn(6, "����", LVCFMT_LEFT, 40);
	m_lstAllLog.InsertColumn(7, "����", LVCFMT_LEFT, 100);
	m_lstAllLog.InsertColumn(8, "������", LVCFMT_LEFT, 70);
	m_lstAllLog.InsertColumn(9, "����", LVCFMT_LEFT, 100);
	m_lstAllLog.InsertColumn(10, "�޴���", LVCFMT_LEFT, 100);
	m_lstAllLog.InsertColumn(11, "��û���", LVCFMT_LEFT, 100);
	m_lstAllLog.InsertColumn(12, "�۾���", LVCFMT_LEFT, 70);
	m_lstAllLog.Populate();

	SetResize(IDC_RIDER_REPORT, sizingBottom);
	SetResize(IDC_EACH_LOG_REPORT, sizingRight);
	SetResize(IDC_ALL_LOG_REPORT, sizingRightBottom);

	FillBankCode(FALSE, &m_cmbBank);
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}

void CReportForm29::DeleteRiderList()
{
	CXTPGridRecords *pRecords = m_lstRider.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		ST_RIDER_ACCOUNT *st = (ST_RIDER_ACCOUNT*)m_lstRider.GetItemData(pRecords->GetAt(i));

		if(st)
		{
			delete st;
			st = NULL;
		}
	}
}

void CReportForm29::RefreshList()
{
	CMyFormView::RefreshList();

	//��� ����Ʈ ����

	char buffer[10];

	DeleteRiderList();
	m_lstRider.DeleteAllItems();
 
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_income_1");

	pCmd.AddParameter(GetCurBranchInfo(TRUE)->nCompanyCode);
	pCmd.AddParameter(GetCurBranchInfo(TRUE)->bIntegrated);

	if(!pRs.Execute(&pCmd)) 
		return;

	CString strTemp;
	BOOL bReject, bCompleted;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		ST_RIDER_ACCOUNT *st = new ST_RIDER_ACCOUNT;
 
		pRs.GetFieldValue("lCode", st->nCompany);
		pRs.GetFieldValue("nMNo", st->nRNo);
		pRs.GetFieldValue("sName", st->strName);
		pRs.GetFieldValue("nBankID", st->nBankID);  
		pRs.GetFieldValue("sBankAccount", st->strBankAccount);
		pRs.GetFieldValue("sBankAccountOwner", st->strBankOwner);
		pRs.GetFieldValue("nBalance", st->nCurCharge);
		pRs.GetFieldValue("bCompleted", bCompleted);
		pRs.GetFieldValue("bReject", bReject);

		m_lstRider.InsertItem(i, ::GetBranchInfo(st->nCompany)->strBranchName);
		m_lstRider.SetItemText(i, 1, itoa(st->nRNo, buffer, 10));
		m_lstRider.SetItemText(i, 2, st->strName);
		m_lstRider.SetItemText(i, 3, ::GetMyNumberFormat(st->nCurCharge));

		if(bReject == 1)
			strTemp == "����";
		else if(bCompleted == 1)
			strTemp == "";
		else
			strTemp == "���";

		m_lstRider.SetItemText(i, 4, strTemp);

		m_lstRider.SetItemData(i, (DWORD)st);

		pRs.MoveNext();
	}

	m_lstRider.Populate();
	RefreshAllList();
}

void CReportForm29::OnReportItemSelChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	CXTPGridRecord *pRecord = m_lstRider.GetFirstSelectedRecord();

	if(pRecord != NULL)
	{
		ST_RIDER_ACCOUNT *st = (ST_RIDER_ACCOUNT*)m_lstRider.GetItemData(pRecord);

		m_edtRiderName.SetWindowText(st->strName);
		m_edtShareBalance.SetWindowText(::GetMyNumberFormat(st->nCurCharge));

		m_nRiderCompany = st->nCompany;
		m_nRNo = st->nRNo; 

		m_edtAccount.SetWindowText(st->strBankAccount);
		m_edtDepositName.SetWindowText(st->strBankOwner);
		m_edtAMount.SetWindowText("");
		m_edtEtc.SetWindowText("");
		m_edtPhone.SetWindowText("");

		for(int i = 0; i < m_cmbBank.GetCount(); i++) {
			if(m_cmbBank.GetItemData(i) == st->nBankID)
				m_cmbBank.SetCurSel(i);
		}

		RefreshEachList();
	}	
}

void CReportForm29::RefreshEachList()
{
	RefreshLogList(&m_lstEachLog, FALSE);
}

void CReportForm29::RefreshAllList()
{
	RefreshLogList(&m_lstAllLog, TRUE);
}

void CReportForm29::RefreshLogList(CXTPListCtrl2 *pList, BOOL bAll)
{
	UpdateData(TRUE);
	pList->DeleteAllItems();

	long nPaRiderCompany = 0;
	long nPaRNo = 0;

	if(bAll == FALSE)
	{
		CXTPGridRecord *pRecord = m_lstRider.GetFirstSelectedRecord();

		if(pRecord)
		{
			ST_RIDER_ACCOUNT *st = (ST_RIDER_ACCOUNT*)m_lstRider.GetItemData(pRecord);

			nPaRiderCompany = st->nCompany;
			nPaRNo = st->nRNo;
		}
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_drawing_log_1");
	pCmd.AddParameter(bAll);
	pCmd.AddParameter(::GetCurBranchInfo(TRUE)->nCompanyCode);
	pCmd.AddParameter(::GetCurBranchInfo(TRUE)->bIntegrated);
	pCmd.AddParameter(nPaRiderCompany);
	pCmd.AddParameter(nPaRNo);
	pCmd.AddParameter(m_dtFrom);
	pCmd.AddParameter(m_dtTo);

	if(!pRs.Execute(&pCmd))
		return;

	long nCompany, nRNo, nWIthDrawMoney, nBankCode, nProcessStatus;
	CString strRName, strAccount, strOwnerAccount, strEtc, strResult, strPhoneNumber, strWName, strTemp;
	COleDateTime dtReqSendMoney;
	char buffer [10];
	const char *dayofweek[] = {"��", "��", "ȭ", "��", "��", "��", "��"};

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("nProcessStatus", nProcessStatus);
		pRs.GetFieldValue("sRName", strRName);
		pRs.GetFieldValue("nWIthDrawMoney", nWIthDrawMoney);
		pRs.GetFieldValue("nBankCode", nBankCode);
		pRs.GetFieldValue("sAccount", strAccount);
		pRs.GetFieldValue("sOwnerAccount", strOwnerAccount);
		pRs.GetFieldValue("sEtc", strEtc);
		pRs.GetFieldValue("sResult", strResult);
		pRs.GetFieldValue("dtReqSendMoney", dtReqSendMoney);
		pRs.GetFieldValue("sPhoneNumber", strPhoneNumber);
		pRs.GetFieldValue("sWName", strWName);

		pList->InsertItem(i, GetBranchInfo(nCompany)->strBranchName);
		pList->SetItemText(i, 1, itoa(nRNo, buffer, 10));
		pList->SetItemText(i, 2, strRName);
		pList->SetItemText(i, 3, nProcessStatus != 5100 ? "����" : "");
		pList->SetItemText(i, 4, ::GetMyNumberFormat(nWIthDrawMoney));

		if(dtReqSendMoney.m_status != COleDateTime::null)
			strTemp.Format("%s(%s)", dtReqSendMoney.Format("%m/%d %H:%M"), dayofweek[dtReqSendMoney.GetDayOfWeek() - 1]);
		else
			strTemp = "";
		pList->SetItemText(i, 5, strTemp);
		pList->SetItemText(i, 6, ::GetBankName(nBankCode));
		pList->SetItemText(i, 7, strAccount);
		pList->SetItemText(i, 8, strOwnerAccount);
		pList->SetItemText(i, 9, strEtc);
		pList->SetItemText(i, 10, strPhoneNumber);
		pList->SetItemText(i, 11, strResult);
		pList->SetItemText(i, 12, strWName);
		pList->SetItemLong(i, nBankCode);

		pRs.MoveNext();
	}

	pList->Populate();

	/*
	if(bAll == FALSE)
	{
	if(pList->GetItemCount() > 0)
	{
	CXTPGridRow *pRow = pList->GetRows()->GetAt(0);
	pList->GetSelectedRows()->Select(pRow);
	}

	OnReportItemEachClick(NULL, NULL);
	}
	*/
}


void CReportForm29::OnReportItemEachClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CXTPGridRecord *pRecord = m_lstEachLog.GetFirstSelectedRecord();

	if(pRecord == NULL)
	{
		m_edtAccount.SetWindowText("");
		m_edtDepositName.SetWindowText("");
		m_edtAMount.SetWindowText("");
		m_edtEtc.SetWindowText("");
		m_edtPhone.SetWindowText("");
		return;
	}

	CString strAccount = m_lstEachLog.GetItemText(pRecord, 7);
	CString strOwnerAccount = m_lstEachLog.GetItemText(pRecord, 8);
	CString strCharge = m_lstEachLog.GetItemText(pRecord, 4);
	CString strEtc = m_lstEachLog.GetItemText(pRecord, 9);
	CString strPhone = m_lstEachLog.GetItemText(pRecord, 10);
	long nBankCode = m_lstEachLog.GetItemLong(pRecord);

	m_edtAccount.SetWindowText(strAccount);
	m_edtDepositName.SetWindowText(strOwnerAccount);
	m_edtAMount.SetWindowText(strCharge);
	m_edtEtc.SetWindowText(strEtc);
	m_edtPhone.SetWindowText(strPhone);

	for(int i = 0; i < m_cmbBank.GetCount(); i++) {
		if(m_cmbBank.GetItemData(i) == nBankCode)
			m_cmbBank.SetCurSel(i);
	}
}

void CReportForm29::OnReportItemAllClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{

}
void CReportForm29::OnBnClickedDrawingBtn()
{
	if(!POWER_CHECK(1040, "��ݿ�û", TRUE))
		return;

	long nBankCode = m_cmbBank.GetItemData(m_cmbBank.GetCurSel()); //nID��
	CString strAccount, strDepositName, strPhone, strAmount, strShareBalance;
	CString strEtc;

	m_edtAccount.GetWindowText(strAccount);
	m_edtDepositName.GetWindowText(strDepositName);
	m_edtPhone.GetWindowText(strPhone);
	m_edtAMount.GetWindowText(strAmount);
	m_edtShareBalance.GetWindowText(strShareBalance);
	m_edtEtc.GetWindowText(strEtc);

	int nAmount = 0, nShareBalance = 0;

	try {
		if(nBankCode < 0)
			throw "������ �����ϼ���.";

		if(strAccount.GetLength() < 7)
			throw "���¹�ȣ�� �Է��ϼ���.";

		if(strDepositName.GetLength() < 2)
			throw "�����ָ� �Է��Ͻñ� �ٶ��ϴ�.";

		if(strPhone.GetLength() < 8)
			throw "SMS���� ������ �޴�����ȣ�� �Է��ϼ���.";

		nAmount = GetNoneCommaNumber(strAmount);

		if(nAmount < 10000 || nAmount > 50000000)
			throw "1ȸ ��� ���ɱݾ��� 1����~5000�����Դϴ�.";

		//nShareBalance = GetNoneCommaNumber(strShareBalance);
		nShareBalance = GetRiderCurBalance(m_nRiderCompany, m_nRNo);

		if(nShareBalance < nAmount)
			throw "�ܾ��� �����մϴ�. ��ݿ�û�ݾ��� �ٿ��ֽñ� �ٶ��ϴ�.";
	}
	catch(char *msg)
	{
		MessageBox(msg, "Ȯ��", MB_ICONINFORMATION);
		return;
	} 
 
	CMkCommand pCmd(m_pMkDb, "insert_rider_balance_drawing_info_by_op2");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(m_nRiderCompany);
	pCmd.AddParameter(m_nRNo); 
	pCmd.AddParameter(nBankCode);
	pCmd.AddParameter(strAccount);
	pCmd.AddParameter(strDepositName);
	pCmd.AddParameter(strPhone);
	pCmd.AddParameter(nAmount);
	pCmd.AddParameter(strEtc);
	CMkParameter *pParError = pCmd.AddParameter(typeString, typeOutput, 200, "");
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ei.strMac1);
	pCmd.AddParameter(GetHddId().TrimLeft());

	if(!pCmd.Execute())
	{
		MessageBox("��ݿ�û�� ���еǾ����ϴ�. ��õ� �Ͻñ� �ٶ��ϴ�.", "����", MB_ICONERROR);
	}
	else
	{
		if(parRet->GetLong() == 9)
		{
			MessageBox("�̹� ��ݿ�û�� �Ͻ� �����Դϴ�.\n\n����Ŀ� ���û���ֽñ� �ٶ��ϴ�.", 
				"Ȯ��",
				MB_ICONINFORMATION);
		}
		else if(parRet->GetLong() == 10)
		{
			MessageBox("���� ��������� �������� �����, ��ݿ�û�� �ϽǼ� �����ϴ�.\n\n"\
				"�ִ� 30�� ���� �ɸ� �����Դϴ�. ������ ����� �˼��մϴ�.", 
				"Ȯ��",
				MB_ICONINFORMATION);
		}
		else if(parRet->GetLong() == 11)
		{
			MessageBox("��û�Ͻűݾ��� ����Ͻ� �� �����ϴ�.", 
				"Ȯ��",
				MB_ICONINFORMATION);
		}
		else if(parRet->GetLong() == 12)
		{
			CString strTemp = "";
			CString strError; pParError->GetValue(strError);

			strTemp.Format("��� ��û ó���� ������ �߻��Ͽ����ϴ�.\n\n������ �Ʒ��� �����ϴ�.\r\n\r\n%s", strError);

			MessageBox(strTemp, "Ȯ��",	MB_ICONINFORMATION);
		}
		else
		{
			RefreshEachList();
			RefreshAllList();
			MessageBox("���������� ��ݿ�û�Ǿ����ϴ�.\n\n[�ش��� �����Ȳ] �� ���Ź�ư�� Ŭ���Ͽ� ��ü ����� Ȯ���ϼ���", "Ȯ��", MB_ICONINFORMATION);
		}
	}
}

long CReportForm29::GetRiderCurBalance(long nRiderCompany, long nRNo)
{
	CMkCommand cmd(m_pMkDb, "select_rider_cur_balance");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(nRiderCompany);
	cmd.AddParameter(nRNo);

	if(!cmd.Execute())
		return 0;

	return parRet->GetLong();
}

void CReportForm29::OnBnClickedRefreshBtn2()
{
	RefreshList();
}

void CReportForm29::OnEnChangeSearchEdit()
{
	CXTPGridRecords *pRecords = m_lstRider.GetRecords();

	CString strSearch; m_edtSearch.GetWindowText(strSearch);

	for(int i=0;i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strRNo = m_lstRider.GetItemText(pRecord, 1);
		CString strName = m_lstRider.GetItemText(pRecord, 2);

		if(strRNo.Find(strSearch) >= 0 ||
			strName.Find(strSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstRider.Populate();
}

void CReportForm29::OnBnClickedRefreshBtn()
{
	RefreshAllList();
}

void CReportForm29::OnBnClickedSaveBtn()
{
	long nBankCode = m_cmbBank.GetItemData(m_cmbBank.GetCurSel()); //nID��

	CString strAccount, strAccoutnOwner;
	m_edtAccount.GetWindowText(strAccount);
	m_edtDepositName.GetWindowText(strAccoutnOwner);

	if(strAccount.IsEmpty() || strAccoutnOwner.IsEmpty())
	{
		MessageBox("���������� Ȯ���ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CMkCommand pCmd(m_pMkDb, "update_rider_account_info");
	pCmd.AddParameter(m_nRiderCompany);
	pCmd.AddParameter(m_nRNo);
	pCmd.AddParameter(nBankCode);
	pCmd.AddParameter(strAccount);
	pCmd.AddParameter(strAccoutnOwner);

	if(pCmd.Execute())
	{
		CXTPGridRecord *pRecord = m_lstRider.GetFirstSelectedRecord();

		if(pRecord == NULL)
			return;

		ST_RIDER_ACCOUNT *st = (ST_RIDER_ACCOUNT*)m_lstRider.GetItemData(pRecord);
		st->nBankID = nBankCode;
		st->strBankAccount = strAccount;
		st->strBankOwner = strAccoutnOwner;

		MessageBox("����Ǿ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
	}

}

void CReportForm29::OnBnClickedRefreshLogBtn()
{
	OnReportItemSelChanged(NULL, NULL);
}

void CReportForm29::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect, rect1;
	m_lstEachLog.GetWindowRect(&rect);
	m_lstAllLog.GetWindowRect(&rect1);

	if(rect.PtInRect(point))
		m_bEachReport = TRUE;
	else if(rect1.PtInRect(point))
		m_bEachReport = FALSE;
	else 
		return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

}

void CReportForm29::OnViewExcel()
{
	if(!POWER_CHECK(4900, "������ȯ", TRUE))
		return;

	if(m_bEachReport)
	{
		AddSecurityLog(GetCurBranchInfo()->nCompanyCode, 325, m_ui.nWNo, m_lstEachLog.GetItemCount());  
		CMyExcel::ToExcel(&m_lstEachLog);
	}
	else
	{
		AddSecurityLog(GetCurBranchInfo()->nCompanyCode, 325, m_ui.nWNo, m_lstAllLog.GetItemCount());  
		CMyExcel::ToExcel(&m_lstAllLog);
	}
		
}
void CReportForm29::OnEnChangeSearchEtcEdt()
{
	CString strShEtc;

	m_edtShEtc.GetWindowText(strShEtc);

	for(long i = 0; i < m_lstAllLog.GetRecords()->GetCount(); i ++)
	{
		CXTPGridRecord* pRecord = m_lstAllLog.GetRecords()->GetAt(i);

		if(strShEtc.GetLength() == 0)
		{
			pRecord->SetVisible(TRUE);
			continue;
		}
		else
		{
			CString strEtc;
			
			strEtc = pRecord->GetItem(9)->GetCaption(NULL);
			
			if(strEtc.Find(strShEtc) >= 0)
				pRecord->SetVisible(TRUE);
			else
				pRecord->SetVisible(FALSE);
		}
	}

	m_lstAllLog.Populate();
}
