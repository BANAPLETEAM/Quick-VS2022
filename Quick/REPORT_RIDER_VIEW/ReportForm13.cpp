// ReportForm13.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ReportForm13.h"

// CReportForm13

IMPLEMENT_DYNCREATE(CReportForm13, CMyFormView)

CReportForm13::CReportForm13()
	: CMyFormView(CReportForm13::IDD)
	, m_dtFrom(COleDateTime::GetCurrentTime())
	, m_dtTo(COleDateTime::GetCurrentTime())
{
}

CReportForm13::~CReportForm13()
{
	m_wndReport.SaveReportOrder("CReportForm13", "m_wndReport");
}

void CReportForm13::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_wndReport);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFromCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_RefreshBtn);
}

BEGIN_MESSAGE_MAP(CReportForm13, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_LIST, OnReportItemClick)

	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_RCLICK, IDC_REPORT_LIST, OnReportItemRClick)

	
END_MESSAGE_MAP()


// CReportForm13 �����Դϴ�.

#ifdef _DEBUG
void CReportForm13::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CReportForm13::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CReportForm13 �޽��� ó�����Դϴ�.

void CReportForm13::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CReportForm13::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_REPORT_LIST, sizingRightBottom);

	m_DateBtn.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_DateBtn.OnMenuWeek();

	m_wndReport.InsertColumn(0, "����", LVCFMT_LEFT, 40);
	m_wndReport.InsertColumn(1, "������ȣ", LVCFMT_LEFT, 80);
	m_wndReport.InsertColumn(2, "���ֻ�", LVCFMT_LEFT, 100);
	m_wndReport.InsertColumn(3, "�����ð�", LVCFMT_LEFT, 100);
	m_wndReport.InsertColumn(4, "�����", LVCFMT_LEFT, 110);
	m_wndReport.InsertColumn(5, "������", LVCFMT_LEFT, 110);
	m_wndReport.InsertColumn(6, "����", LVCFMT_LEFT, 50);
	m_wndReport.InsertColumn(7, "���Ÿ��", LVCFMT_LEFT, 60); //���Ÿ��
	m_wndReport.InsertColumn(8, "���", LVCFMT_LEFT, 50);
	m_wndReport.InsertColumn(9, "����", LVCFMT_LEFT, 60);
	m_wndReport.InsertColumn(10, "���Ҽ�ȸ��", LVCFMT_LEFT, 80);
	//m_wndReport.InsertColumn(10, "Ÿ��", LVCFMT_LEFT, 100); //�ڻ�, ����(���簣��ü), Ÿ��
	m_wndReport.InsertColumn(11, "Ź��", LVCFMT_LEFT, 70); //�ڻ�, ����(���簣��ü), Ÿ��
	m_wndReport.InsertColumn(12, "�ݾ�", LVCFMT_LEFT, 70);
	m_wndReport.InsertColumn(13, "���Ա�", LVCFMT_LEFT, 70); //�Ա� �Ϸ� Ȥ�� ���Ա� Ȥ�� û����û

	m_wndReport.Populate();

	m_wndReport.LoadReportOrder("CReportForm13", "m_wndReport");
}

void CReportForm13::RefreshList()
{
	CMyFormView::RefreshList();

	UpdateData(true);

	m_wndReport.GetRecords()->RemoveAll();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_deferred_order_1");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);

	if(!pRs.Execute(&pCmd)) return;

	char buffer[20];
	
	for(int i=0; i<pRs.GetRecordCount(); i++) 
	{ 
		
		CREDIT_STRUCT *st = new CREDIT_STRUCT; 

		pRs.GetFieldValue("nTNo", st->nTNo);	
		pRs.GetFieldValue("nCompany", st->nCompany);
		pRs.GetFieldValue("sOName", st->sOName);
		pRs.GetFieldValue("sSName", st->sSName);
		pRs.GetFieldValue("sDName", st->sDName);
		pRs.GetFieldValue("dt1", st->dt1);
		pRs.GetFieldValue("nPayType", st->nPayType);
		pRs.GetFieldValue("nRiderCompany", st->nRiderCompany);
		pRs.GetFieldValue("nRNo", st->nRNo);
		pRs.GetFieldValue("sRName", st->sRName);
		pRs.GetFieldValue("nChargeSum", st->nChargeSum);
		pRs.GetFieldValue("nChargeTrans", st->nChargeTrans);
		pRs.GetFieldValue("nState", st->nState);
		pRs.GetFieldValue("bGiveChargeToRider", st->bGiveChargeToRider);

		
		m_wndReport.InsertItem(i, itoa(i, buffer, 10));
		m_wndReport.SetItemText(i, 1, itoa(st->nTNo, buffer, 10));
		m_wndReport.SetItemText(i, 2, m_ci.GetBranchName(st->nCompany));
		m_wndReport.SetItemText(i, 3, st->dt1.Format("%m/%d %H:%M"));
		m_wndReport.SetItemText(i, 4, st->sSName);
		m_wndReport.SetItemText(i, 5, st->sDName);
		m_wndReport.SetItemText(i, 6, ::GetStateString(st->nState));
		m_wndReport.SetItemText(i, 7, ::GetPayTypeFromLong(st->nPayType));
		m_wndReport.SetItemText(i, 8, itoa(st->nRNo, buffer, 10));
		m_wndReport.SetItemText(i, 9, st->sRName);
		m_wndReport.SetItemText(i, 10, m_ci.GetBranchName(st->nRiderCompany));
		//m_wndReport.SetItemText(i, 10, GetOrderShareType(st) + "/" + GetRiderShareType(st));
		m_wndReport.SetItemText(i, 11, ::GetMyNumberFormat(st->nChargeTrans));
		m_wndReport.SetItemText(i, 12, ::GetMyNumberFormat(st->nChargeSum));
		m_wndReport.SetItemText(i, 13, st->bGiveChargeToRider == TRUE ? "�ԱݿϷ�" : "���Ա�");
		//m_wndReport.SetItemText(i, 12, GetTransferState(GetOrderShareType(st), GetRiderShareType(st), st->bGiveChargeToRider));

		m_wndReport.SetItemData(i, (DWORD_PTR)st);
		
		pRs.MoveNext();
	}

	m_wndReport.Populate();
   
}
 
CString CReportForm13::GetTransferState(CString sOrder, CString sRider, BOOL  bSuccess)
{
	if(bSuccess == TRUE)
		return "�ԱݿϷ�";

	if(sOrder == "�ڻ���" && sRider == "�ڻ���")
		return "���Ա�";
	else if(sOrder == "�ڻ���" && sRider == "������")
		return "��ü(���Ա�)";
	else if(sOrder == "�ڻ���" && sRider == "Ÿ���")
		return "��ü(���Ա�)";
	else if(sOrder == "������" && sRider == "�ڻ���")
		return "û��";
	else if(sOrder == "������" && sRider == "������")
		return "";
	else if(sOrder == "������" && sRider == "Ÿ���")
		return "";
	else if(sOrder == "Ÿ����" && sRider == "�ڻ���")
		return "û��";
	else if(sOrder == "Ÿ����" && sRider == "������")
		return "";
	else if(sOrder == "Ÿ����" && sRider == "Ÿ���") //���ü� ���� ���
		return "";
	else 
		return "";


} 

void CReportForm13::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	if(nCol != 13) return;

	CREDIT_STRUCT *st = (CREDIT_STRUCT*)m_wndReport.GetItemData(nRow);

	if(st->bGiveChargeToRider)
	{
		MessageBox("�̹� �Ա�ó�� �Ǿ����ϴ�", "Ȯ��" ,MB_ICONINFORMATION);
		return;
	}

	CString sMsg;
	sMsg.Format("��� %d�����Կ��� \r\n %d���� ���Ա� ������ �Ͻðڽ��ϱ�?", st->nRNo, st->nChargeSum + st->nChargeTrans);

	if(MessageBox(sMsg, "Ȯ��", MB_YESNO) == IDYES)
	{
		if(InsertCharge(st->nChargeSum + st->nChargeTrans, st->nTNo, st->nRiderCompany, st->nRNo, st->sRName))
		{
			CMkCommand pCmd(m_pMkDb, "update_credit_state_for_give_to_rider");
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), st->nTNo);

			if(pCmd.Execute())
			{
				st->bGiveChargeToRider = 1;
				m_wndReport.SetItemText(nRow, 13, "�ԱݿϷ�");
			}

		}
	}
}



CString CReportForm13::GetOrderShareType(CREDIT_STRUCT *st)
{
	CString sReturn = "";
 
	if(m_ci.GetShareCode1(m_ci.m_nCompanyCode) == m_ci.GetShareCode1(st->nCompany)) // �ڻ��� OR ������
	{
		if((m_ci.IsUseBranchShareReport(st->nCompany) == TRUE) && 
			(m_ci.m_nCompanyCode != st->nCompany)) // ������
		{
            sReturn = "������";
		}
		else
		{
			sReturn = "�ڻ���";
		}
	}
	else
		sReturn = "Ÿ����";

	return sReturn;
}

CString CReportForm13::GetRiderShareType(CREDIT_STRUCT *st)
{
	CString sReturn = "";

	if(m_ci.GetShareCode1(m_ci.m_nCompanyCode) == m_ci.GetShareCode1(st->nRiderCompany)) // �ڻ��� OR ������
	{
		BOOL a= m_ci.IsUseBranchShareReport(st->nRiderCompany);
		if((m_ci.IsUseBranchShareReport(st->nRiderCompany) == TRUE) && 
			(m_ci.m_nCompanyCode != st->nRiderCompany)) // ������
		{
			sReturn = "������";
		}
		else
		{
			sReturn = "�ڻ���";
		}
	}
	else
		sReturn = "Ÿ���";

	return sReturn;
}


BOOL CReportForm13::InsertCharge(long nSendMoney, long nTNo, long nRiderCompay, long nRNo, CString sRName)
{
	CString sEtc;
	sEtc.Format("�ſ���� ���Ա����� ������ȣ(%d)", nTNo);

	long nReturn;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_rider_deposit_balance_today");

	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nRiderCompay);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nRNo);
	pCmd.AddParameter(typeString, typeInput, sRName.GetLength(), sRName);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), 13); // �ſ�����


	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nSendMoney);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
	
	pCmd.AddParameter(typeString, typeInput, sEtc.GetLength(), sEtc); //����

	if(!pRs.Execute(&pCmd)) return FALSE;

	pPar->GetValue(nReturn);

	return TRUE;
}

void CReportForm13::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_wndReport, pt);

}

void CReportForm13::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_wndReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CReportForm13::OnViewExcel()
{
	if(!POWER_CHECK(4900, "������ȯ", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nDOrderTable, 312, m_ui.nWNo, m_wndReport.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_wndReport);
}