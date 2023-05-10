// CompleteAfterEditDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "CompleteAfterEditDlg.h"

#include "OrderLogDetailDlg.h"
#include "VarietyDlg2.h"
#include "ShareTranferRequestDlg.h"
#include "ShareTansferMyRequest.h"

// CCompleteAfterEditDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCompleteAfterEditDlg, CMyDialog)
CCompleteAfterEditDlg::CCompleteAfterEditDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCompleteAfterEditDlg::IDD, pParent)
{
}

CCompleteAfterEditDlg::~CCompleteAfterEditDlg()
{
}

void CCompleteAfterEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFromCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CCompleteAfterEditDlg, CMyDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnReportItemClick)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnReportItemDblClick)	
	ON_BN_CLICKED(ID_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_REQUEST_BTN, &CCompleteAfterEditDlg::OnBnClickedRequestBtn)
	ON_BN_CLICKED(IDC_MY_REQUEST_BTN, &CCompleteAfterEditDlg::OnBnClickedMyRequestBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CCompleteAfterEditDlg::OnBnClickedCloseBtn)
END_MESSAGE_MAP()


// CCompleteAfterEditDlg �޽��� ó�����Դϴ�.

BOOL CCompleteAfterEditDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	CenterWindow();

	m_DateBtn.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_DateBtn.OnMenuMonth();

	InitColumn(FALSE);
	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CCompleteAfterEditDlg::InitColumn(BOOL bRequest)
{  
	int nColumnCount = m_List.GetColumns()->GetCount();
	for(int i=0;i < nColumnCount;i++)
	{
		CXTPGridColumns *pColums = m_List.GetColumns();
		pColums->Remove(pColums->GetAt(0));
	}

	m_List.GetRecords()->RemoveAll();  

	m_List.InsertColumn(0, "��û��ü", LVCFMT_LEFT, 80);
	m_List.InsertColumn(1, "�����ü", LVCFMT_LEFT, 80);
	m_List.InsertColumn(2, "��û��", LVCFMT_LEFT, 80);
	m_List.InsertColumn(3, "������ȣ", LVCFMT_LEFT, 80);
	m_List.InsertColumn(4, "�����", LVCFMT_LEFT, 90);
	m_List.InsertColumn(5, "������", LVCFMT_LEFT, 90);
	m_List.InsertColumn(6, "Ÿ��", LVCFMT_LEFT, 40);
	m_List.InsertColumn(7, "�������", LVCFMT_LEFT, 80);
	m_List.InsertColumn(8, "�����ð�", LVCFMT_LEFT, 50);
	m_List.InsertColumn(9, "����", LVCFMT_LEFT, 170);

	m_List.GetReportHeader()->SetAutoColumnSizing(FALSE);

	m_List.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_List.GetReportHeader()->AllowColumnRemove(FALSE);
	m_List.GetReportHeader()->AllowColumnReorder(FALSE);
	m_List.AllowEdit(FALSE);
	m_List.SetGridColor(RGB(222, 222, 222));
	m_List.GetPaintManager()->m_strNoItems = "ǥ���� ����� �������� ����";
	m_List.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	
	m_List.Populate();
}

void CCompleteAfterEditDlg::OnBnClickedRefreshBtn()
{
    RefreshList();   	
}


void CCompleteAfterEditDlg::RefreshList()
{
	UpdateData(TRUE);
	m_List.DeleteAllItems();

	char buffer[10];
	long nTNo, nFromCompany, nToCompany, nDeposit, nType, nResult;
	COleDateTime dtGenerate;
	CString sEtc, sStart, sDest;
	COleDateTime dtResult;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_transfer_for_order_change");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(m_dtFrom);
	pCmd.AddParameter(m_dtTo);

	if(!pRs.Execute(&pCmd)) return;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("nFromCompany", nFromCompany);
		pRs.GetFieldValue("nToCompany", nToCompany);
		pRs.GetFieldValue("nDeposit", nDeposit);
		pRs.GetFieldValue("nType", nType);
		pRs.GetFieldValue("nResult", nResult);
		pRs.GetFieldValue("dtGenerate", dtGenerate);
		pRs.GetFieldValue("sEtc", sEtc);
		pRs.GetFieldValue("dtResult", dtResult);
		pRs.GetFieldValue("sStart", sStart);
		pRs.GetFieldValue("sDest", sDest);

		m_List.InsertItem(i, m_ci.GetName(nFromCompany));
		m_List.SetItemText(i, 1, m_ci.GetName(nToCompany));
		m_List.SetItemText(i, 2, dtGenerate.Format("%m-%d %H:%M"));
		m_List.SetItemText(i, 3, itoa(nTNo, buffer, 10));
		m_List.SetItemText(i, 4, sStart);
		m_List.SetItemText(i, 5, sDest);
		m_List.SetItemText(i, 6, nType == 0 ? "��ü" : "û��");
		m_List.SetItemText(i, 7, GetRequestState(nResult));
		m_List.SetItemText(i, 8, nResult == 0 ? GetLeftDate(dtGenerate) : "");
		m_List.SetItemText(i, 9, sEtc);
		m_List.SetItemLong(i, nType);
		m_List.SetItemLong2(i, nResult);

		pRs.MoveNext();
	}

	m_List.Populate();
}

CString CCompleteAfterEditDlg::GetLeftDate(COleDateTime dtDate)
{
	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	COleDateTime dtTwoDay = dtDate + COleDateTimeSpan(2, 0, 0, 0);

	COleDateTimeSpan span = dtTwoDay - dtCur;

	long nHour = span.GetTotalHours();

	CString sTemp = "";
	sTemp.Format("%d�ð�", nHour);

	return sTemp;
}

BOOL CCompleteAfterEditDlg::IsDifferentPayType(long nPrePayType, long nPayType)
{
	long nPre, nCur;

	if((nPrePayType == 0) || (nPrePayType == 1) || (nPrePayType == 4))
		nPre = 0;
	else
		nPre = 1;

	if((nPayType == 0) || (nPayType == 1) || (nPayType == 4))
		nCur = 0;
	else
		nCur = 1;

    if(nPre == nCur)
		return TRUE;
	else
		return FALSE;
}

BOOL CCompleteAfterEditDlg::IsDifferentState(long nPreState, long nState)
{
	long nPre, nCur;

	if((nPreState == 11) || (nPreState == 30) || (nPreState == 31) || (nPreState == 35))
		nPre = 0;
	else
		nPre = 1;

	if(LF->IsAllocOrder(nState))
		nCur = 0;
	else
		nCur = 1;

	if(nPre == nCur)
		return TRUE;
	else
		return FALSE;
	
}

CString CCompleteAfterEditDlg::GetRequestState(long nRequestState)
{
	if(nRequestState == 0)
		return "û����";
	if(nRequestState == 1)
		return "��ü����";
	if(nRequestState == 2)
		return "����Ϸ�";
	if(nRequestState == 3)
		return "�ð�����Ϸ�";

	return "�˼�����";
}

void CCompleteAfterEditDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CXTPGridRow *pRow = m_List.GetSelectedRows()->GetAt(0);
 
	if(pRow == NULL)
		return;

	CXTPGridRecord *pRecord = pRow->GetRecord();
	CString sTNo = ((CXTPGridRecordItemText*)(pRecord->GetItem(3)))->GetCaption(NULL);


	COrderLogDetailDlg DetailLog;
	DetailLog.m_nTNo = atoi(sTNo);
	DetailLog.m_bCross = TRUE;
	DetailLog.DoModal();
}



void CCompleteAfterEditDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	long nCol = pItemNotify->pColumn->GetIndex();

	CXTPGridRow *pRow = m_List.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	CXTPGridRecord *pRecord = pRow->GetRecord();
	CString sText = ((CXTPGridRecordItemText*)(pRecord->GetItem(nCol)))->GetCaption(NULL);
	long nID = m_List.GetItemData(pRecord);

	if(nCol == 7) // ����
	{
		if(sText == "����")
		{
			CVarietyDlg2 dlg;
			dlg.m_sTitle = "���� ������ �Է��ϼ���";

			if(dlg.DoModal() == IDOK)
			{
                CMkCommand pCmd(m_pMkDb, "rereport_share_account");
				pCmd.AddParameter(nID);
				pCmd.AddParameter(m_ui.nCompany);
				pCmd.AddParameter(m_ui.nWNo);
				pCmd.AddParameter(m_ui.strName);
				pCmd.AddParameter(dlg.m_sEtc);

				if(pCmd.Execute())
				{
					MessageBox("�����Ͽ����ϴ�\r\n����������â���� ���곻���� Ȯ�� �ϽǼ� �ֽ��ϴ�", "Ȯ��", MB_ICONINFORMATION);
					RefreshList();
				}
			}
		}
	}

	if(nCol == 8) //����
	{ 
		if(sText == "����")
		{
			CVarietyDlg2 dlg;
			dlg.m_sTitle = "���� ������ �Է��ϼ���";
			if(dlg.DoModal() == IDOK)
			{
				CMkCommand pCmd(m_pMkDb, "share_account_not_agree");
				pCmd.AddParameter(nID);
				pCmd.AddParameter(m_ui.nCompany);
				pCmd.AddParameter(m_ui.nWNo);
				pCmd.AddParameter(m_ui.strName);
				pCmd.AddParameter(dlg.m_sEtc);

				if(pCmd.Execute())
				{
					MessageBox("�����Ͽ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
					RefreshList();
				}
			}
		}
	}
}

BOOL CCompleteAfterEditDlg::IsCash(long nPayType)
{	
	if((nPayType == 0) || (nPayType == 1) || (nPayType == 4))
		return TRUE;
	else
		return FALSE;
}
void CCompleteAfterEditDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(m_List.GetSafeHwnd() == NULL ||
		this->GetSafeHwnd() == NULL)
		return;

	CRect rcDlg, rcList;
	GetWindowRect(rcDlg);
	m_List.GetWindowRect(rcList);
	ScreenToClient(rcDlg);
	ScreenToClient(rcList);

	rcList.right = rcDlg.right - 3;
	rcList.bottom = rcDlg.bottom - 3;

	m_List.MoveWindow(rcList);
}

void CCompleteAfterEditDlg::OnBnClickedRequestBtn()
{
	CShareTranferRequestDlg dlg;

	//CShareReportRateDlg* pShareReportRateDlg = (CShareReportRateDlg*)(GetParent()->GetParent());
	//CString sBalance, sMinBalance;
	//pShareReportRateDlg->m_BalanceEdit.GetWindowText(sBalance);
	//pShareReportRateDlg->m_BasicRateEdit.GetWindowText(sMinBalance);
	//sBalance.Replace(",", "");
	//sBalance.Replace("��", "");
	//sMinBalance.Replace(",", "");
	//sMinBalance.Replace("��", "");

	int nAbilityMoney = 0;//_ttoi(sBalance) - _ttoi(sMinBalance);

	dlg.m_nAbilityMoney = GetAbilMoney();
//	dlg.m_pShareReportRateDlg1 = this;
	dlg.m_sSql = "select_transfer_request_1";

	dlg.DoModal();		
}

long CCompleteAfterEditDlg::GetAbilMoney()
{
	CMkCommand pCmd(m_pMkDb, "select_get_abil_money");

	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(m_ci.m_nCompanyCode);

	if(!pCmd.Execute()) return 0;

	long nRet = 0; pPar->GetValue(nRet);

	return nRet;
}

void CCompleteAfterEditDlg::OnBnClickedMyRequestBtn()
{
	CShareTansferMyRequest pDlg;
	pDlg.DoModal();
}

void CCompleteAfterEditDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}
