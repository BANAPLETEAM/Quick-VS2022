// ScheduleOrderDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ScheduleOrderDlg.h"



// CScheduleOrderDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CScheduleOrderDlg, CMyDialog)
CScheduleOrderDlg::CScheduleOrderDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CScheduleOrderDlg::IDD, pParent)
{
	m_dtReserveTime = COleDateTime::GetCurrentTime();
	m_dtEndDate = COleDateTime::GetCurrentTime() + COleDateTimeSpan(365, 0, 0, 0);
	m_bEdit = FALSE;
	
}

CScheduleOrderDlg::~CScheduleOrderDlg()
{
}

void CScheduleOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_bDay1);
	DDX_Check(pDX, IDC_CHECK2, m_bDay2);
	DDX_Check(pDX, IDC_CHECK3, m_bDay3);
	DDX_Check(pDX, IDC_CHECK4, m_bDay4);
	DDX_Check(pDX, IDC_CHECK5, m_bDay5);
	DDX_Check(pDX, IDC_CHECK6, m_bDay6);
	DDX_Check(pDX, IDC_CHECK7, m_bDay7);
	DDX_Check(pDX, IDC_PAUSE_CHECK, m_bPause);
	DDX_Check(pDX, IDC_NEXT_WEEK_ADVENCE_CHECK, m_nNextWeekAdvance);
	DDX_Control(pDX, IDC_NEXT_WEEK_ADVENCE_CHECK, m_btnNextWeekAdvance);

	DDX_DateTimeCtrl(pDX, IDC_RESERVE_TIME_DT, m_dtReserveTime);
	DDX_DateTimeCtrl(pDX, IDC_END_DATE_DT, m_dtEndDate);
	DDX_Control(pDX, IDC_RESERVE_TO_RCP_CHECK, m_chkReserveToRcp);
}


BEGIN_MESSAGE_MAP(CScheduleOrderDlg, CMyDialog)
	ON_BN_CLICKED(IDC_DELETE_BTN, OnBnClickedDeleteBtn)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CScheduleOrderDlg 메시지 처리기입니다.
BOOL CScheduleOrderDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	long nReserveToRcp;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_schedule_order");
	pCmd.AddParameter(m_nSrcTNo);
	pCmd.AddParameter(m_nCompany);
	if(pRs.Execute(&pCmd))
	{
		if(!pRs.IsEOF())		
		{
			pRs.GetFieldValue("nSrcTNo", m_nSrcTNo);
			pRs.GetFieldValue("dtReserveTime", m_dtReserveTime);
			pRs.GetFieldValue("bDay1", m_bDay1);
			pRs.GetFieldValue("bDay2", m_bDay2);
			pRs.GetFieldValue("bDay3", m_bDay3);
			pRs.GetFieldValue("bDay4", m_bDay4);
			pRs.GetFieldValue("bDay5", m_bDay5);
			pRs.GetFieldValue("bDay6", m_bDay6);
			pRs.GetFieldValue("bDay7", m_bDay7);
			pRs.GetFieldValue("bUse", m_bPause);
			pRs.GetFieldValue("nNextWeekAdvance", m_nNextWeekAdvance);
									
			pRs.GetFieldValue("dtEndDate", m_dtEndDate);
			pRs.GetFieldValue("nReserveToRcp", nReserveToRcp);

			m_chkReserveToRcp.SetCheck(nReserveToRcp);

			m_bPause = !m_bPause;
			m_btnNextWeekAdvance.SetCheck(m_nNextWeekAdvance > 0 ? TRUE : FALSE);
			
			UpdateData(FALSE);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CScheduleOrderDlg::OnBnClickedDeleteBtn()
{
	CMkCommand pCmd(m_pMkDb, "delete_schedule_order");
	pCmd.AddParameter(m_nSrcTNo);
	if(pCmd.Execute())
	{
		MessageBox("해당 정기작업이 삭제되었습니다.", "확인", MB_ICONINFORMATION);
		OnOK();
	}
}

void CScheduleOrderDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	CMkCommand pCmd(m_pMkDb, "update_schedule_order3");
	pCmd.AddParameter(m_nSrcTNo);
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(m_dtReserveTime.Format("%H:%M:%S"));
	pCmd.AddParameter(m_bDay1);
	pCmd.AddParameter(m_bDay2);
	pCmd.AddParameter(m_bDay3);
	pCmd.AddParameter(m_bDay4);
	pCmd.AddParameter(m_bDay5);
	pCmd.AddParameter(m_bDay6);
	pCmd.AddParameter(m_bDay7);
	pCmd.AddParameter(1);
	pCmd.AddParameter(!m_bPause);
	pCmd.AddParameter(m_btnNextWeekAdvance.GetCheck());
	pCmd.AddParameter(m_dtEndDate);
	pCmd.AddParameter(m_chkReserveToRcp.GetCheck());
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(m_ui.nWNo);
	if(pCmd.Execute())
	{
		MessageBox("수정되었습니다.", "확인", MB_ICONINFORMATION);
		OnOK();
	}
}

