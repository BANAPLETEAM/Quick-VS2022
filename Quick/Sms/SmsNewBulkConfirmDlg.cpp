// SmsNewBulkConfirmDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "SmsNewBulkConfirmDlg.h"
#include "Excel.h"


// CSmsNewBulkConfirmDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSmsNewBulkConfirmDlg, CMyDialog)

CSmsNewBulkConfirmDlg::CSmsNewBulkConfirmDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CSmsNewBulkConfirmDlg::IDD, pParent)
{
}

CSmsNewBulkConfirmDlg::~CSmsNewBulkConfirmDlg()
{
}

void CSmsNewBulkConfirmDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_dtpFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_dtpTo);	
	DDX_Control(pDX, IDC_DATE_BTN, m_btnData);

	DDX_Control(pDX, IDC_BULK_REPORT, m_lstBulk);
	DDX_Control(pDX, IDC_SMS_CHECK, m_chkSms);
	DDX_Control(pDX, IDC_LMS_CHECK, m_chkLms);
	DDX_Control(pDX, IDC_MMS_CHECK, m_chkMms);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}


BEGIN_MESSAGE_MAP(CSmsNewBulkConfirmDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_LIST_BTN, &CSmsNewBulkConfirmDlg::OnBnClickedRefreshListBtn)
	ON_NOTIFY(NM_CLICK, IDC_BULK_REPORT, OnBulkReportItemClick)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CANCAL_BULK, OnCancelBulk)
	ON_BN_CLICKED(IDC_SMS_CHECK, &CSmsNewBulkConfirmDlg::OnBnClickedSmsCheck)
	ON_BN_CLICKED(IDC_LMS_CHECK, &CSmsNewBulkConfirmDlg::OnBnClickedLmsCheck)
	ON_BN_CLICKED(IDC_MMS_CHECK, &CSmsNewBulkConfirmDlg::OnBnClickedMmsCheck)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CANCEL_REV_BTN, &CSmsNewBulkConfirmDlg::OnBnClickedCancelRevBtn)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CSmsNewBulkConfirmDlg::OnEnChangeSearchEdit)
END_MESSAGE_MAP()


BOOL CSmsNewBulkConfirmDlg::OnInitDialog()
{ 
	CMyDialog::OnInitDialog();

	m_chkSms.SetCheck(TRUE);
	m_chkLms.SetCheck(TRUE);
	m_chkMms.SetCheck(TRUE);

	m_btnData.InitDateButton(&m_dtpFrom, &m_dtpTo);
	m_btnData.OnMenuMonthIncludeToday();

	m_lstBulk.InsertColumn(0, "�����", LVCFMT_LEFT, 100);
	m_lstBulk.InsertColumn(1, "���۽ð�", LVCFMT_CENTER, 120);
	m_lstBulk.InsertColumn(2, "����", LVCFMT_CENTER, 60);
	m_lstBulk.InsertColumn(3, "�ѰǼ�", LVCFMT_RIGHT, 60);
	m_lstBulk.InsertColumn(4, "�����Ǽ�", LVCFMT_RIGHT, 60); 
	m_lstBulk.InsertColumn(5, "���аǼ�", LVCFMT_RIGHT, 60);
	m_lstBulk.InsertColumn(6, "������", LVCFMT_RIGHT, 60);
	m_lstBulk.InsertColumn(7, "�������", LVCFMT_CENTER, 60);
	m_lstBulk.InsertColumn(8, "����", LVCFMT_LEFT, 70);
	m_lstBulk.InsertColumn(9, "�ٿ�ޱ�", LVCFMT_CENTER, 55);
	m_lstBulk.InsertColumn(10, "�ٿ�ޱ�", LVCFMT_CENTER, 55);
	m_lstBulk.InsertColumn(11, "�ٿ�ޱ�", LVCFMT_CENTER, 55);
	m_lstBulk.InsertColumn(12, "�ٿ�ޱ�", LVCFMT_CENTER, 55);
	m_lstBulk.InsertColumn(13, "�߼ۿ�û��", LVCFMT_CENTER, 120);
	m_lstBulk.InsertColumn(14, "������ҽð�", LVCFMT_CENTER, 120);
	m_lstBulk.InsertColumn(15, "�۾���", LVCFMT_LEFT, 80);
	m_lstBulk.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CSmsNewBulkConfirmDlg::RefreshList()
{
	UpdateData(TRUE);

	m_lstBulk.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_bulk_send_log_1");
	cmd.AddParameter(m_ci.m_nCompanyCode);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);

	if(!rs.Execute(&cmd))
		return;

	long nID, nCount, nSuccessCount, nFailCount, nResultWaitCount, nDeleteWCompany, nCompany;
	CString strType, strEtc, strWorker, strDeleteName, strName;
	COleDateTime dtSend, dtRegister, dtDelete;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("nCompany", nCompany);
		rs.GetFieldValue("sType", strType);
		rs.GetFieldValue("nCount", nCount);
		rs.GetFieldValue("nSuccessCount", nSuccessCount);
		rs.GetFieldValue("nFailCount", nFailCount);
		rs.GetFieldValue("nResultWaitCount", nResultWaitCount);
		rs.GetFieldValue("dtSend", dtSend);
		rs.GetFieldValue("nDeleteWCompany", nDeleteWCompany);
		rs.GetFieldValue("sEtc", strEtc);
		rs.GetFieldValue("dtRegister", dtRegister);
		rs.GetFieldValue("dtDelete", dtDelete);
		rs.GetFieldValue("sDeleteName", strDeleteName);
		rs.GetFieldValue("sName", strName);

		m_lstBulk.InsertItem(i, m_ci.GetBranchName(nCompany));
		m_lstBulk.SetItemText(i, 1, LF->GetDateTimeToString(dtSend, 3, TRUE)); 
		m_lstBulk.SetItemText(i, 2, strType);
		m_lstBulk.SetItemText(i, 3, LF->GetMyNumberFormat(nCount));
		m_lstBulk.SetItemText(i, 4, LF->GetMyNumberFormat(nSuccessCount));
		m_lstBulk.SetItemText(i, 5, LF->GetMyNumberFormat(nFailCount));
		m_lstBulk.SetItemText(i, 6, LF->GetMyNumberFormat(nResultWaitCount));
		m_lstBulk.SetItemText(i, 7, nDeleteWCompany > 0 ? "��" : "");
		m_lstBulk.SetItemText(i, 8, strEtc);
		m_lstBulk.SetItemText(i, 9, "�ѰǼ�");
		m_lstBulk.SetItemText(i, 10, "����");
		m_lstBulk.SetItemText(i, 11, "����");
		m_lstBulk.SetItemText(i, 12, "���");
		m_lstBulk.SetItemText(i, 13, LF->GetDateTimeToString(dtRegister, 3, TRUE)); 
		m_lstBulk.SetItemText(i, 14, LF->GetDateTimeToString(dtDelete, 3, TRUE));
		m_lstBulk.SetItemText(i, 15, strDeleteName.GetLength() > 0 ? strName + "(" + strDeleteName + ")" : strName);
		m_lstBulk.SetItemLong(i, nID);

		m_lstBulk.ChangeItemTextColor(i, 9, RGB(0, 0, 255));
		m_lstBulk.ChangeItemTextColor(i, 10, RGB(0, 0, 255));
		m_lstBulk.ChangeItemTextColor(i, 11, RGB(0, 0, 255));
		m_lstBulk.ChangeItemTextColor(i, 12, RGB(0, 0, 255));

		rs.MoveNext();
	}

	CheckFilter();
}

void CSmsNewBulkConfirmDlg::OnBnClickedRefreshListBtn()
{
	RefreshList();
}

void CSmsNewBulkConfirmDlg::OnBulkReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridRecord *pRecord = m_lstBulk.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	long nRow = pItemNotify->pRow->GetIndex();
	long nCol = pItemNotify->pColumn->GetItemIndex();

	if(nCol < 9 || 12 < nCol)
		return;

	long nID = m_lstBulk.GetItemLong(pRecord);
	CString strDate = m_lstBulk.GetItemText(pRecord, 0);
	CString strDownType = "";

	if(nCol == 9) strDownType = "�ѰǼ�";
	else if(nCol == 10) strDownType = "�����Ǽ�";
	else if(nCol == 11) strDownType = "���аǼ�";
	else if(nCol == 12) strDownType = "������";

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_bulk_sms_for_excel_1");
	cmd.AddParameter(nID);
	cmd.AddParameter(nCol);

	if(!rs.Execute(&cmd))
		return;

	if(rs.GetRecordCount() == 0)
	{
		MessageBox("������� Ȥ�� ��Ÿ ������ �����͸� ���� ���Ͽ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	LF->AddSecurityLog(m_ui.nCompany, 2000, m_ui.nWNo, LF->GetStringFromLong(rs.GetRecordCount()), strDate, strDownType);


	CMyExcel::ToExcel(&rs);
}

void CSmsNewBulkConfirmDlg::CheckFilter()
{
	CXTPGridRecords *pRecords = m_lstBulk.GetRecords();

	BOOL bSms = m_chkSms.GetCheck();
	BOOL bLms = m_chkLms.GetCheck();
	BOOL bMms = m_chkMms.GetCheck();

	CString strItem;
	m_edtSearch.GetWindowText(strItem);
	strItem.MakeUpper();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strType = m_lstBulk.GetItemText(pRecord, 2);

		CString strBranch = pRecord->GetItem(0)->GetCaption(NULL);
		strBranch.MakeUpper();

		if(bSms == FALSE && strType == "SMS")
			pRecord->SetVisible(FALSE);
		else if(bLms == FALSE && strType == "LMS")
			pRecord->SetVisible(FALSE);
		else if(bMms == FALSE && strType == "MMS")
			pRecord->SetVisible(FALSE);
		else if(strBranch.Find(strItem) == -1)
			pRecord->SetVisible(FALSE);
		else
			pRecord->SetVisible(TRUE);

		continue;
	}

	m_lstBulk.Populate();
}

void CSmsNewBulkConfirmDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstBulk.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return; 

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(33);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CSmsNewBulkConfirmDlg::OnCancelBulk()
{
	CXTPGridRecord *pRecord = m_lstBulk.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return; 

	if(MessageBox("���� ��� �Ͻðڽ��ϱ�?", "Ȯ��", MB_OKCANCEL) != IDOK)
		return;

	long nID = m_lstBulk.GetItemLong(pRecord);

	CMkCommand cmd(m_pMkDb, "cancel_bulk_sms");
	CMkParameter *pParRet = cmd.AddParameter(typeLong, typeReturn, 0);
	cmd.AddParameter(nID);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.strName);

	if(!cmd.Execute())
		return;

	long nRet; pParRet->GetValue(nRet);

	if(nRet == 1)
		MessageBox("������� ���� ȹ�濡 �����߽��ϴ�.", "Ȯ��", MB_ICONINFORMATION);
	else if(nRet == 2)
		MessageBox("����ð� 20������ ��� �Ұ��մϴ�.", "Ȯ��", MB_ICONINFORMATION);
	else if(nRet == 3)
		MessageBox("���۴��, ���ۿϷ���¿����� ��� �Ұ��մϴ�.", "Ȯ��", MB_ICONINFORMATION);
	else if(nRet == 4)
		MessageBox("SMS�ݾ� �������� ȹ�� �����߽��ϴ�.", "Ȯ��", MB_ICONINFORMATION);
	else if(nRet == 5)
		MessageBox("SMS�ݾ� ȯ�Կ� �����߽��ϴ�.", "Ȯ��", MB_ICONINFORMATION);
	else if(nRet == 6)
		MessageBox("�̹� ������ҵǾ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
	else if(nRet == 7)
		MessageBox("������ Ȥ�� ���ۿϷ�����Դϴ�.", "Ȯ��", MB_ICONINFORMATION);
	else
		MessageBox("��ҵǾ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);

	RefreshList();	
}
void CSmsNewBulkConfirmDlg::OnBnClickedSmsCheck()
{
	CheckFilter();
}

void CSmsNewBulkConfirmDlg::OnBnClickedLmsCheck()
{
	CheckFilter();
}

void CSmsNewBulkConfirmDlg::OnBnClickedMmsCheck()
{
	CheckFilter();
}

void CSmsNewBulkConfirmDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(!m_lstBulk.GetSafeHwnd())
		return;


	CRect rcDlg, rcLst;
	GetClientRect(rcDlg);
	m_lstBulk.GetWindowRect(rcLst);
	ScreenToClient(rcLst);

	rcLst.right = rcDlg.right - 4; 
	rcLst.bottom = rcDlg.bottom - 4; 

	m_lstBulk.MoveWindow(rcLst); 
}

void CSmsNewBulkConfirmDlg::OnBnClickedCancelRevBtn()
{
	OnCancelBulk();
}

void CSmsNewBulkConfirmDlg::OnEnChangeSearchEdit()
{
	CheckFilter();
}
