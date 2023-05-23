// RiderCancelLogDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderCancelLogDlg.h"

#include "ShowRiderInfoDlg.h"

// CRiderCancelLogDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRiderCancelLogDlg, CMyDialog)
CRiderCancelLogDlg::CRiderCancelLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderCancelLogDlg::IDD, pParent)
{
}

CRiderCancelLogDlg::~CRiderCancelLogDlg()
{
}

void CRiderCancelLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_CTRL, m_wndReport);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFromCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtToCtl);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
}


BEGIN_MESSAGE_MAP(CRiderCancelLogDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CRiderCancelLogDlg �޽��� ó�����Դϴ�.


void CRiderCancelLogDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CRiderCancelLogDlg::RefreshList()
{
	m_wndReport.DeleteAllItems();

	UpdateData(true);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_cancel_log_2");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_pParent->m_nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_pParent->m_nRNo);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);

	if(!pRs.Execute(&pCmd)) return;

	CString strNum, sType, sTNo, sPenalty, sStart, sDest, sCancel;
	COleDateTime dtLog;
	long nTNo, nPenaltyCharge, nPenaltyTime, nTCompany, nReason, nState2;

	m_ci.GetName(10);
 
	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("dtLog", dtLog);
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("nPenaltyCharge", nPenaltyCharge);
		pRs.GetFieldValue("nPenaltyTime", nPenaltyTime);
		pRs.GetFieldValue("sType", sType);
		pRs.GetFieldValue("sStart", sStart);
		pRs.GetFieldValue("sDest", sDest);
		pRs.GetFieldValue("sCancel", sCancel);
		pRs.GetFieldValue("nTCompany", nTCompany);
		pRs.GetFieldValue("nReason", nReason);
		pRs.GetFieldValue("nState2", nState2);
		pRs.GetFieldValue("nTNo", nTNo);

		strNum.Format("%d", i+1);
		m_wndReport.InsertItem(i, strNum);
		m_wndReport.SetItemText(i, 1, LF->GetStringFromLong(nTNo));
		m_wndReport.SetItemText(i, 2, m_ci.GetName(nTCompany));
		m_wndReport.SetItemText(i, 3, dtLog.Format("%y-%m-%d %H:%M:%S"));

		sTNo.Format("%d", nTNo);
		m_wndReport.SetItemText(i, 4, sStart);
		m_wndReport.SetItemText(i, 5, sDest);

		m_wndReport.SetItemText(i, 6, sType);

		if(sType == "����")
		{
			sPenalty.Format("");
		}
		else if(sType == "�ð�")
		{
			sPenalty.Format("%d��", nPenaltyTime);
		}
		else if(sType == "�ݾ�")
		{
			sPenalty.Format("%d��", nPenaltyCharge);
		}

		m_wndReport.SetItemText(i, 7, sPenalty);
		m_wndReport.SetItemText(i, 8, sCancel);
		m_wndReport.SetItemText(i, 9, LF->GetCancelReason(nReason));
		m_wndReport.SetItemText(i, 10, sCancel == "����" && nState2 >= 2 ? "�󼼹���â" : "������â");
	
		pRs.MoveNext();
	}

	m_wndReport.Populate();
}

BOOL CRiderCancelLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_wndReport.InsertColumn(0, "����", LVCFMT_LEFT, 40);
	m_wndReport.InsertColumn(1, "������ȣ", LVCFMT_CENTER, 70);
	m_wndReport.InsertColumn(2, "���ֻ�", LVCFMT_LEFT, 100);
	m_wndReport.InsertColumn(3, "��ҽð�", LVCFMT_LEFT, 90);
	//m_List.InsertColumn(2, "������ȣ", LVCFMT_LEFT, 70);
	m_wndReport.InsertColumn(4, "�����", LVCFMT_LEFT, 80);
	m_wndReport.InsertColumn(5, "������", LVCFMT_LEFT, 80);
	m_wndReport.InsertColumn(6, "Ÿ��", LVCFMT_LEFT, 40);
	m_wndReport.InsertColumn(7, "�г�Ƽ", LVCFMT_LEFT, 60);
	m_wndReport.InsertColumn(8, "���", LVCFMT_LEFT, 50);
	m_wndReport.InsertColumn(9, "����", LVCFMT_LEFT, 50);
	m_wndReport.InsertColumn(10, "�����ġ", LVCFMT_LEFT, 55);

	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(TRUE);
	m_wndReport.GetReportHeader()->AllowColumnSort(TRUE);
	m_wndReport.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_wndReport.GetPaintManager()->m_strNoItems = "ǥ���� ����� �������� ����";
	m_wndReport.AllowEdit(FALSE);
	m_wndReport.FocusSubItems(TRUE);

	m_wndReport.SetGridColor(RGB(180, 180, 200));
	m_wndReport.Populate();

	m_dtFromCtl.SetFormat("yyyy-MM-dd HH:00");
	m_dtToCtl.SetFormat("yyyy-MM-dd HH:00");

	m_DateBtn.InitDateButton((CDateTimeCtrl*)&m_dtFromCtl, (CDateTimeCtrl*)&m_dtToCtl);
	m_DateBtn.OnMenuToday();


	//Moving();

	RefreshList(); 


	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CRiderCancelLogDlg::Moving()
{
	/*
	CRect  rect;

	GetClientRect(&rect);

	MoveWindow(m_ParentRect.right, m_ParentRect.top, rect.Width(), rect.Height(), NULL);
	*/
}

void CRiderCancelLogDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(!m_wndReport.GetSafeHwnd())
		return;

	CRect rcDlg, rcList;
	GetClientRect(rcDlg);

	m_wndReport.GetWindowRect(rcList);
	ScreenToClient(rcList);

	rcList.right = rcDlg.right - 1;
	rcList.bottom = rcDlg.bottom - 1; 

	m_wndReport.MoveWindow(rcList);
}
