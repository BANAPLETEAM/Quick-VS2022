// ChargeForRiderLogDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "ChargeForRiderLogDlg.h"
#include "VarietyDlg2.h"
#include "ChargeForRiderTransferDlg.h"
#include "ChargeForRiderDetailDlg.h"

// CChargeForRiderLogDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CChargeForRiderLogDlg, CMyDialog)

CChargeForRiderLogDlg::CChargeForRiderLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChargeForRiderLogDlg::IDD, pParent)
{

}

CChargeForRiderLogDlg::~CChargeForRiderLogDlg()
{
}

void CChargeForRiderLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_REPORT_LIST, m_lstReport);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFromCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);

	DDX_Control(pDX, IDC_TYPE_COMBO, m_cmbType);
}


BEGIN_MESSAGE_MAP(CChargeForRiderLogDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CChargeForRiderLogDlg::OnBnClickedRefreshBtn)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_TYPE_COMBO, &CChargeForRiderLogDlg::OnCbnSelchangeTypeCombo)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_REQUEST_STOP, OnRequestStop)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_LIST, OnReportItemClick)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_LIST, OnReportItemDblClick)
END_MESSAGE_MAP()

void CChargeForRiderLogDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(!pRecord)
		return;

	long nID = m_lstReport.GetItemLong(pRecord);

	CChargeForRiderDetailDlg dlg;
	dlg.m_nID = nID;
	dlg.DoModal();
}

void CChargeForRiderLogDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(!pRecord)
		return;

	long nID = m_lstReport.GetItemLong(pRecord);
	BOOL bMyRequest = m_lstReport.GetItemLong2(pRecord);
	long nType = m_lstReport.GetItemLong3(pRecord);
	
	//11 ��ü, 12 ����

	if(nCol == 11 || nCol == 12)
	{
		if(bMyRequest)
		{
			MessageBox("������ ��û�� ������ ��ü/���� �Ͻ� �� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
			return;
		}

		if(nType != 0)
		{
			MessageBox("��ü/������ �Ͻ� �� ���� �����Դϴ�", "Ȯ��", MB_ICONINFORMATION);
			return;
		}

		if(nCol == 11)
		{
			CChargeForRiderTransferDlg dlg;
			dlg.m_nID = nID;

			if(dlg.DoModal() == IDOK)
			{
				MessageBox("���������� ��ü �Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
				RefreshList();
			}								
		}
		else if(nCol == 12)
		{
			CVarietyDlg2 dlg;
			dlg.m_sTitle = "���� ������ �Է��ϼ���";

			if(dlg.DoModal() == IDOK)
			{
				CMkCommand cmd(m_pMkDb, "update_charge_for_rider_transfer_cancel");
				cmd.AddParameter(nID);
				cmd.AddParameter(dlg.m_sEtc);
				cmd.AddParameter(m_ui.nCompany);
				cmd.AddParameter(m_ui.nWNo);
				cmd.AddParameter(m_ui.strName);

				if(!cmd.Execute())
					return;

				MessageBox("���� �Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
				RefreshList();
			}
		}
	}
}

void CChargeForRiderLogDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

BOOL CChargeForRiderLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_btnDate.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_btnDate.OnMenuMonthIncludeToday();

	m_lstReport.InsertColumn(0, "����", LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(1, "��û�ð�", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(2, "��û��ü", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(3, "���Ҽ�", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(4, "�����", LVCFMT_RIGHT, 55);
	m_lstReport.InsertColumn(5, "����", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(6, "�ݾ�", LVCFMT_RIGHT, 60);
	m_lstReport.InsertColumn(7, "����", LVCFMT_CENTER, 50);
	m_lstReport.InsertColumn(8, "����", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(9, "ȸ�ų�¥", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(10, "ȸ���۾���", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(11, "��ü", LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(12, "����", LVCFMT_CENTER, 40);
	m_lstReport.SetOrderIndexCol(0);
	m_lstReport.Populate();

	m_cmbType.SetCurSel(0);

	RefreshList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CChargeForRiderLogDlg::RefreshList()
{
	UpdateData(TRUE);

	m_lstReport.DeleteAllItems();

	CMkRecordset rs(m_pMkDb); 
	CMkCommand cmd(m_pMkDb, "select_charge_for_rider");
	cmd.AddParameter(m_ci.m_nCompanyCode);
	cmd.AddParameter(m_cmbType.GetCurSel());
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);

	if(!rs.Execute(&cmd))
		return;

	long nID, nCompanyMainCode, nRiderMainCode, nRNo, nCharge, nType, nResultWNo;
	COleDateTime dtRequest, dtResult;
	CString strRName, strEtc, strResultWName;
	BOOL bMyRequest;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("dtRequest", dtRequest);		
		rs.GetFieldValue("nCompanyMainCode", nCompanyMainCode);
		rs.GetFieldValue("nRiderMainCode", nRiderMainCode);
		rs.GetFieldValue("nRNo", nRNo);
		rs.GetFieldValue("sRName", strRName);
		rs.GetFieldValue("nCharge", nCharge);
		rs.GetFieldValue("nType", nType);
		rs.GetFieldValue("sEtc", strEtc);
		rs.GetFieldValue("dtResult", dtResult);
		rs.GetFieldValue("nResultWNo", nResultWNo);
		rs.GetFieldValue("sResultWName", strResultWName);
		rs.GetFieldValue("bMyRequest", bMyRequest);

		m_lstReport.InsertItem(i, "");
		m_lstReport.SetItemText(i, 1, dtRequest.Format("%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 2, m_ci.GetShareCompanyName(nCompanyMainCode));
		m_lstReport.SetItemText(i, 3, m_ci.GetShareCompanyName(nRiderMainCode));
		m_lstReport.SetItemText(i, 4, LF->GetStringFromLong(nRNo));
		m_lstReport.SetItemText(i, 5, strRName);
		m_lstReport.SetItemText(i, 6, LF->GetMyNumberFormat(nCharge));

		CString strTemp = "";

		if(nType == 0) strTemp = "��û��";
		else if(nType == 1) strTemp = "��ü�Ϸ�";
		else if(nType == 2) strTemp = "����";
		else if(nType == 3) strTemp = "��û����";

		m_lstReport.SetItemText(i, 7, strTemp);
		m_lstReport.SetItemText(i, 8, strEtc);

		if(nType == 0) //�����������
		{
			m_lstReport.SetItemText(i, 9, "");
			m_lstReport.SetItemText(i, 10, "");

			if(bMyRequest)
			{
				m_lstReport.SetItemText(i, 11, "");
				m_lstReport.SetItemText(i, 12, "");
			}
			else
			{
				m_lstReport.SetItemText(i, 11, "��ü");
				m_lstReport.SetItemText(i, 12, "����");				
			}
		}
		else
		{
			m_lstReport.SetItemText(i, 9, dtResult.Format("%m-%d %H:%M"));
			m_lstReport.SetItemText(i, 10, LF->GetStringFromLong(nResultWNo) + "/" + strResultWName);
			m_lstReport.SetItemText(i, 11, "");
			m_lstReport.SetItemText(i, 12, "");
		}			

		m_lstReport.SetItemLong(i, nID);
		m_lstReport.SetItemLong2(i, bMyRequest);
		m_lstReport.SetItemLong3(i, nType);
					
		rs.MoveNext();
	}

	m_lstReport.Populate();
}

void CChargeForRiderLogDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(!m_lstReport.GetSafeHwnd())
		return;

	CRect rcDlg, rcList;
	GetWindowRect(rcDlg);
	m_lstReport.GetWindowRect(rcList);
	ScreenToClient(rcDlg);
	ScreenToClient(rcList);

	rcList.right = rcDlg.right - 5;
	rcList.bottom = rcDlg.bottom - 5;

	m_lstReport.MoveWindow(rcList);
}

void CChargeForRiderLogDlg::OnCbnSelchangeTypeCombo()
{
	RefreshList();
}

void CChargeForRiderLogDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rectMain = NULL, rectSub = NULL;

	m_lstReport.GetWindowRect(&rectMain);
	BCMenu rMenu;
	if(rectMain.PtInRect(point))
	{	
		rMenu.LoadMenu(IDR_CONTEXT_MENU_1);		
		BCMenu* pRMenu = (BCMenu*)rMenu.GetSubMenu(15);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

void CChargeForRiderLogDlg::OnRequestStop()
{
	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(!pRecord)
		return;

	long nID = m_lstReport.GetItemLong(pRecord);
	BOOL bMyRequest = m_lstReport.GetItemLong2(pRecord);
	long nType = m_lstReport.GetItemLong3(pRecord);
	
	if(!bMyRequest)
	{
		MessageBox("������ ��û�� ������ ��û������ �����մϴ�", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	if(nType != 0)
	{
		MessageBox("��û������ �� �� ���� �����Դϴ�", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CVarietyDlg2 dlg;
	dlg.m_sTitle = "��û���� ������ �Է��ϼ���";

	if(dlg.DoModal() == IDOK)
	{
		CMkCommand cmd(m_pMkDb, "update_charge_for_rider_request_cancel");
		cmd.AddParameter(nID);
		cmd.AddParameter(dlg.m_sEtc);
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ui.strName);

		if(!cmd.Execute())
			return;

		MessageBox("��û���� �Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);

	}
	
	return;
}
