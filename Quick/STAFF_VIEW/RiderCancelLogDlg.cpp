// RiderCancelLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderCancelLogDlg.h"

#include "ShowRiderInfoDlg.h"

// CRiderCancelLogDlg 대화 상자입니다.

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


// CRiderCancelLogDlg 메시지 처리기입니다.


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

		if(sType == "없음")
		{
			sPenalty.Format("");
		}
		else if(sType == "시간")
		{
			sPenalty.Format("%d분", nPenaltyTime);
		}
		else if(sType == "금액")
		{
			sPenalty.Format("%d원", nPenaltyCharge);
		}

		m_wndReport.SetItemText(i, 7, sPenalty);
		m_wndReport.SetItemText(i, 8, sCancel);
		m_wndReport.SetItemText(i, 9, LF->GetCancelReason(nReason));
		m_wndReport.SetItemText(i, 10, sCancel == "본인" && nState2 >= 2 ? "상세배차창" : "가배차창");
	
		pRs.MoveNext();
	}

	m_wndReport.Populate();
}

BOOL CRiderCancelLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_wndReport.InsertColumn(0, "순번", LVCFMT_LEFT, 40);
	m_wndReport.InsertColumn(1, "오더번호", LVCFMT_CENTER, 70);
	m_wndReport.InsertColumn(2, "발주사", LVCFMT_LEFT, 100);
	m_wndReport.InsertColumn(3, "취소시간", LVCFMT_LEFT, 90);
	//m_List.InsertColumn(2, "오더번호", LVCFMT_LEFT, 70);
	m_wndReport.InsertColumn(4, "출발지", LVCFMT_LEFT, 80);
	m_wndReport.InsertColumn(5, "도착지", LVCFMT_LEFT, 80);
	m_wndReport.InsertColumn(6, "타입", LVCFMT_LEFT, 40);
	m_wndReport.InsertColumn(7, "패널티", LVCFMT_LEFT, 60);
	m_wndReport.InsertColumn(8, "취소", LVCFMT_LEFT, 50);
	m_wndReport.InsertColumn(9, "적요", LVCFMT_LEFT, 50);
	m_wndReport.InsertColumn(10, "취소위치", LVCFMT_LEFT, 55);

	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(TRUE);
	m_wndReport.GetReportHeader()->AllowColumnSort(TRUE);
	m_wndReport.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_wndReport.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
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
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
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
