// MakeDepositJobDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MakeDepositJobNewDlg1.h"



#define NEW_MODE 1

IMPLEMENT_DYNAMIC(CMakeDepositJobNewDlg1, CMyDialog)
CMakeDepositJobNewDlg1::CMakeDepositJobNewDlg1(CWnd* pParent /*=NULL*/)
: CMyDialog(CMakeDepositJobNewDlg1::IDD, pParent)
, m_sDisplayName(_T(""))
, m_bUse(FALSE)
, m_sDeposit(_T(""))
, m_dtStart(COleDateTime::GetCurrentTime())
, m_sEtc(_T(""))
, m_bUseSms(FALSE)
, m_nMonthDay(0)
{
	m_nDlgType = 1;
	m_nCompany = 0;
	m_nID = 0;
	m_dtEnd = COleDateTime(2030, 1, 1, 0, 0, 0);
}



CMakeDepositJobNewDlg1::~CMakeDepositJobNewDlg1()
{

}

void CMakeDepositJobNewDlg1::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DISPLAY_NAME_EDIT, m_edtDisplayName);
	DDX_Text(pDX, IDC_DISPLAY_NAME_EDIT, m_sDisplayName);
	DDX_Check(pDX, IDC_USE_CHECK, m_bUse);
	DDX_Control(pDX, IDC_DAY_STATIC, m_stcDay);

	DDX_Control(pDX, IDC_DAY_CHECK, m_chkDay);
	DDX_Control(pDX, IDC_WEEK_CHECK, m_chkWeek);
	DDX_Control(pDX, IDC_MONTH_CHECK, m_chkMonth);

	DDX_Control(pDX, IDC_MONTH_DAY_CHECK, m_chkMonthDay);
	DDX_Control(pDX, IDC_MONTH_WEEK_CHECK, m_chkMonthWeek);

	DDX_Control(pDX, IDC_SUN_CHECK, m_chkSun);
	DDX_Check(pDX, IDC_SUN_CHECK, m_bSun);
	DDX_Control(pDX, IDC_MON_CHECK, m_chkMon);
	DDX_Check(pDX, IDC_MON_CHECK, m_bMon);
	DDX_Control(pDX, IDC_TUES_CHECK, m_chkTues);
	DDX_Check(pDX, IDC_TUES_CHECK, m_bTues);
	DDX_Control(pDX, IDC_WEDNES_CHECK, m_chkWednes);
	DDX_Check(pDX, IDC_WEDNES_CHECK, m_bWednes);
	DDX_Control(pDX, IDC_THURS_CHECK, m_chkThurs);
	DDX_Check(pDX, IDC_THURS_CHECK, m_bThurs);
	DDX_Control(pDX, IDC_FRI_CHECK, m_chkFri);
	DDX_Check(pDX, IDC_FRI_CHECK, m_bFri);
	DDX_Control(pDX, IDC_SATUR_CHECK, m_chkSatur);
	DDX_Check(pDX, IDC_SATUR_CHECK, m_bSatur);


	DDX_Control(pDX, IDC_MONTH_DAY_COMBO, m_cmbMonthDay);
	DDX_Control(pDX, IDC_MONTH_WEEK_COMBO, m_cmbMonthWeek);
	DDX_Control(pDX, IDC_MONTH_WEEKEND_COMBO, m_cmbMonthWeekend);
	DDX_CBIndex(pDX, IDC_MONTH_DAY_COMBO, m_nMonthDay);
	DDX_CBIndex(pDX, IDC_MONTH_WEEK_COMBO, m_nMonthWeek);
	DDX_CBIndex(pDX, IDC_MONTH_WEEKEND_COMBO, m_nMonthWeekend);

	DDX_Control(pDX, IDC_DEPOSIT_TYPE_COMBO, m_cmbDepositType);
	DDX_CBIndex(pDX, IDC_DEPOSIT_TYPE_COMBO, m_nDepositType);
	DDX_Control(pDX, IDC_DEPOSIT_EDIT, m_edtDeposit);
	DDX_Text(pDX, IDC_DEPOSIT_EDIT, m_sDeposit);
	DDX_Control(pDX, IDC_TERM_START_DT, m_ctlTermStart);
	DDX_DateTimeCtrl(pDX, IDC_TERM_START_DT, m_dtStart);
	DDX_Control(pDX, IDC_TERM_END_DT, m_ctlTermEnd);
	DDX_DateTimeCtrl(pDX, IDC_TERM_END_DT, m_dtEnd);
	DDX_Control(pDX, IDC_ETC_EDT, m_edtEtc);
	DDX_Text(pDX, IDC_ETC_EDT, m_sEtc);
	DDX_Check(pDX, IDC_SEND_SMS_CHECK, m_bUseSms);
	DDX_Control(pDX, IDC_SMS_PHONE_EDIT, m_edtSmsPhone);
	DDX_Text(pDX, IDC_SMS_PHONE_EDIT, m_sSmsPhone);

	DDX_Control(pDX, IDC_WORKER_APPLY_CHECK, m_chkWorkerApply);
	DDX_Check(pDX, IDC_WORKER_APPLY_CHECK, m_bWorkerApply);
	DDX_Control(pDX, IDC_NOT_WORKER_APPLY_CHECK, m_chkNotWorkerApply);
	DDX_Check(pDX, IDC_NOT_WORKER_APPLY_CHECK, m_bNotWorkerApply);
	DDX_Control(pDX, IDC_TYPE_STATIC, m_stcType);
	DDX_Control(pDX, ECK, m_chkCopy);
}


BEGIN_MESSAGE_MAP(CMakeDepositJobNewDlg1, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_DAY_CHECK, OnBnClickedDayCheck)
	ON_BN_CLICKED(IDC_WEEK_CHECK, OnBnClickedWeekCheck)
	ON_BN_CLICKED(IDC_MONTH_CHECK, OnBnClickedMonthCheck)
	ON_BN_CLICKED(IDC_MONTH_DAY_CHECK, OnBnClickedMonthDayCheck)
	ON_BN_CLICKED(IDC_THURS_CHECK, OnBnClickedThursCheck)
	ON_BN_CLICKED(IDC_MONTH_WEEK_CHECK, OnBnClickedMonthWeekCheck)
	ON_BN_CLICKED(ECK, OnBnClickedEck)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CMakeDepositJobNewDlg1::OnBnClickedCancelBtn)
END_MESSAGE_MAP()


// CMakeDepositJobNewDlg1 메시지 처리기입니다.

BOOL CMakeDepositJobNewDlg1::OnInitDialog()
{
	CMyDialog::OnInitDialog();	

	CenterWindow();

	if(m_nDlgType == 0) //Edit
		InitData();
	else if(m_nDlgType == 1) //New
		InitControl();
	else //UpdateLog
	{
		GetDlgItem(IDC_OK_BTN)->ShowWindow(SW_HIDE);
		InitUpdateLog();

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMakeDepositJobNewDlg1::InitControl()
{
	m_bUse = TRUE;
	m_bMonthDay = TRUE;
	m_nMonthDay = 0;
	m_nMonthWeek = 0;
	m_nMonthWeekend = 0;
	m_nDepositType = 0;
	m_bMonthDay = TRUE;
	m_chkDay.SetCheck(TRUE);
	m_nMonthDay = 0;
	m_bWorkerApply = TRUE;
	m_bNotWorkerApply = TRUE;

	SetPlayType(0);
	SetMonthPlayType(0);

	UpdateData(FALSE);
	ChangeControl();
	ChangeSubControl();
}

void CMakeDepositJobNewDlg1::InitData()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_schedule_job_one");

	pCmd.AddParameter(m_nID);

	if(!pRs.Execute(&pCmd)) return;
	if(pRs.GetRecordCount() == 0) return;

	long nPlayType, nMonthPlayType, nDeposit;
	CString sSmsPhone;

	pRs.GetFieldValue("bUse", m_bUse);
	pRs.GetFieldValue("sDisplayName", m_sDisplayName);
	pRs.GetFieldValue("nPlayType", nPlayType);
	pRs.GetFieldValue("bSunDay", m_bSun);
	pRs.GetFieldValue("bMonDay", m_bMon);
	pRs.GetFieldValue("bTuesDay", m_bTues);
	pRs.GetFieldValue("bWednesDay", m_bWednes);
	pRs.GetFieldValue("bThursDay", m_bThurs);
	pRs.GetFieldValue("bFriDay", m_bFri);
	pRs.GetFieldValue("bSaturDay", m_bSatur);
	pRs.GetFieldValue("nMonthPlayType", nMonthPlayType);
	pRs.GetFieldValue("bUse", m_bUse);
	pRs.GetFieldValue("nMonthDay", m_nMonthDay); m_nMonthDay--; //하루 작음 콤보
	pRs.GetFieldValue("nMonthWeek", m_nMonthWeek);
	pRs.GetFieldValue("nMonthWeekend", m_nMonthWeekend); m_nMonthWeekend--; //SQL날짜로 들어가 있음
	pRs.GetFieldValue("nDepositType", m_nDepositType);
	pRs.GetFieldValue("nDeposit", nDeposit);
	pRs.GetFieldValue("dtStart", m_dtStart);
	pRs.GetFieldValue("dtEnd", m_dtEnd);
	pRs.GetFieldValue("sEtc", m_sEtc);
	pRs.GetFieldValue("bUseSms", m_bUseSms);
	pRs.GetFieldValue("sSmsPhone", sSmsPhone);
	pRs.GetFieldValue("bWorkerApply", m_bWorkerApply);
	pRs.GetFieldValue("bNotWorkerApply", m_bNotWorkerApply);

	COleDateTimeSpan dtSpan(1, 0, 0, 0);
	m_dtEnd = m_dtEnd - dtSpan;

	m_sDeposit = LF->GetMyNumberFormat(nDeposit);
	m_sSmsPhone = LF->GetDashPhoneNumber(sSmsPhone);

	SetPlayType(nPlayType);
	SetMonthPlayType(nMonthPlayType);

	UpdateData(FALSE);

	ChangeControl();
	ChangeSubControl();
}

void CMakeDepositJobNewDlg1::OnBnClickedOkBtn()
{
	UpdateData(TRUE);

	BOOL bResult = CheckControl();

	if(bResult == FALSE)
		return;

	if(m_nDlgType == 1)
		bResult = InsertJob();
	else if(m_nDlgType == 0)
		bResult = UpdateJob();

	if(bResult)
		OnOK();	
}

BOOL CMakeDepositJobNewDlg1::CheckControl()
{
	if(m_sDisplayName == "")
	{
		MessageBox("작업 이름을 입력하세요", "확인", MB_ICONINFORMATION);
		m_edtDisplayName.SetFocus(); return FALSE;
	}

	if(GetPlayType() == -1)
	{
		MessageBox("되풀이 방법을 선택 하세요", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	if(GetPlayType() == 1) //매주
	{
		if(m_bSun == FALSE && m_bMon == FALSE && m_bTues == FALSE && m_bWednes == FALSE	&&
			m_bThurs == FALSE && m_bFri == FALSE && m_bSatur== FALSE)
		{ 
			MessageBox("일 ~ 월요일중 최소한 하나 이상 체크하세요", "확인", MB_ICONINFORMATION);
			return FALSE;
		} 
	}

	if(GetPlayType() == 1) //매달
	{
		if(GetMonthPlayType() == -1)
		{
			MessageBox("[일], [기간] 중에 선택하세요", "확인", MB_ICONINFORMATION);
			return FALSE;
		}	
	}
	
	if(_ttoi(m_sDeposit) == 0)
	{
		MessageBox("금액을 입력하세요", "확인", MB_ICONINFORMATION);
		m_edtDeposit.SetFocus();
		return FALSE;
	}

	if(m_bWorkerApply == FALSE && m_bNotWorkerApply == FALSE)
	{
		MessageBox("업무가능, 업무중지에 체크 하세요", "확인", MB_ICONINFORMATION);
		return FALSE; 
	}

	if(m_sEtc == "")
	{
		MessageBox("적요 항목을 입력 하세요", "확인", MB_ICONINFORMATION);
		m_edtEtc.SetFocus();
		return FALSE;
	}

	if(m_bUseSms && m_sSmsPhone.Left(2) != "01")
	{
		MessageBox("SMS전송 받을 번호를 입력하세요.", "확인", MB_ICONINFORMATION);
		m_edtSmsPhone.SetFocus();
		return FALSE;
	}
	
	return TRUE;
}

void CMakeDepositJobNewDlg1::OnBnClickedDayCheck()
{
	m_chkDay.SetCheck(TRUE);
	m_chkWeek.SetCheck(FALSE);
	m_chkMonth.SetCheck(FALSE);
	m_stcType.SetWindowText("매일");
	ChangeControl();
}

void CMakeDepositJobNewDlg1::OnBnClickedWeekCheck()
{
	m_chkDay.SetCheck(FALSE);
	m_chkWeek.SetCheck(TRUE);
	m_chkMonth.SetCheck(FALSE);
	m_stcType.SetWindowText("매주");
	ChangeControl();
}

void CMakeDepositJobNewDlg1::OnBnClickedMonthCheck()
{
	m_chkDay.SetCheck(FALSE);
	m_chkWeek.SetCheck(FALSE);
	m_chkMonth.SetCheck(TRUE);
	m_stcType.SetWindowText("매달");
	ChangeControl();
}

void CMakeDepositJobNewDlg1::ChangeControl()
{
	if(m_chkDay.GetCheck())
	{
		m_stcDay.ShowWindow(TRUE);

		m_chkSun.ShowWindow(FALSE);
		m_chkMon.ShowWindow(FALSE);
		m_chkTues.ShowWindow(FALSE);
		m_chkWednes.ShowWindow(FALSE);
		m_chkThurs.ShowWindow(FALSE);
		m_chkFri.ShowWindow(FALSE);
		m_chkSatur.ShowWindow(FALSE);

		m_chkMonthDay.ShowWindow(FALSE);
		m_cmbMonthDay.ShowWindow(FALSE);
		m_chkMonthWeek.ShowWindow(FALSE);
		m_cmbMonthWeek.ShowWindow(FALSE);
		m_cmbMonthWeekend.ShowWindow(FALSE);
	}
	else if(m_chkWeek.GetCheck())
	{
		m_stcDay.ShowWindow(FALSE);

		m_chkSun.ShowWindow(TRUE);
		m_chkMon.ShowWindow(TRUE);
		m_chkTues.ShowWindow(TRUE);
		m_chkWednes.ShowWindow(TRUE);
		m_chkThurs.ShowWindow(TRUE);
		m_chkFri.ShowWindow(TRUE);
		m_chkSatur.ShowWindow(TRUE);

		m_chkMonthDay.ShowWindow(FALSE);
		m_cmbMonthDay.ShowWindow(FALSE);
		m_chkMonthWeek.ShowWindow(FALSE);
		m_cmbMonthWeek.ShowWindow(FALSE);
		m_cmbMonthWeekend.ShowWindow(FALSE);
	}
	else if(m_chkMonth.GetCheck())
	{
		m_stcDay.ShowWindow(FALSE);

		m_chkSun.ShowWindow(FALSE);
		m_chkMon.ShowWindow(FALSE);
		m_chkTues.ShowWindow(FALSE);
		m_chkWednes.ShowWindow(FALSE);
		m_chkThurs.ShowWindow(FALSE);
		m_chkFri.ShowWindow(FALSE);
		m_chkSatur.ShowWindow(FALSE);

		m_chkMonthDay.ShowWindow(TRUE);
		m_cmbMonthDay.ShowWindow(TRUE);
		m_chkMonthWeek.ShowWindow(TRUE);
		m_cmbMonthWeek.ShowWindow(TRUE);
		m_cmbMonthWeekend.ShowWindow(TRUE);

		ChangeSubControl();
	}
}

void CMakeDepositJobNewDlg1::ChangeSubControl()
{
	if(m_chkMonthDay.GetCheck())
	{
		m_cmbMonthDay.EnableWindow(TRUE);
		m_cmbMonthWeek.EnableWindow(FALSE);
		m_cmbMonthWeekend.EnableWindow(FALSE);
	}
	else if(m_chkMonthWeek.GetCheck())
	{
		m_cmbMonthDay.EnableWindow(FALSE);
		m_cmbMonthWeek.EnableWindow(TRUE);
		m_cmbMonthWeekend.EnableWindow(TRUE);

	}
}

long CMakeDepositJobNewDlg1::GetPlayType()
{
	if(m_chkDay.GetCheck())
		return 0;
	if(m_chkWeek.GetCheck())
		return 1;
	if(m_chkMonth.GetCheck())
		return 2;

	return -1;
}

void CMakeDepositJobNewDlg1::SetPlayType(long nType)
{
	if(nType == 0)
		m_chkDay.SetCheck(TRUE);
	else if(nType == 1)
		m_chkWeek.SetCheck(TRUE);
	else if(nType == 2)
		m_chkMonth.SetCheck(TRUE);
}

void CMakeDepositJobNewDlg1::SetMonthPlayType(long nType)
{
	if(nType == 0)
		m_chkMonthDay.SetCheck(TRUE);
	else if(nType == 1)
		m_chkMonthWeek.SetCheck(TRUE);
}


long CMakeDepositJobNewDlg1::GetMonthPlayType()
{
	if(m_chkMonthDay.GetCheck())
		return 0;
	if(m_chkMonthWeek.GetCheck())
		return 1;

	return -1;
}

COleDateTime CMakeDepositJobNewDlg1::GetStartDate()
{
	m_dtStart.SetDateTime(m_dtStart.GetYear(), m_dtStart.GetMonth(), m_dtStart.GetDay(), 0, 0, 0);
	return m_dtStart;
}

COleDateTime CMakeDepositJobNewDlg1::GetEndDate()
{
	m_dtEnd.SetDateTime(m_dtEnd.GetYear(), m_dtEnd.GetMonth(), m_dtEnd.GetDay(), 23, 59, 59);
	return m_dtEnd;
}

BOOL CMakeDepositJobNewDlg1::InsertJob()
{
	CMkCommand pCmd(m_pMkDb, "insert_schedule_job");
     
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(m_bUse);

	pCmd.AddParameter(m_sDisplayName);
	pCmd.AddParameter(GetPlayType());
	pCmd.AddParameter(m_bSun);
	pCmd.AddParameter(m_bMon);
	pCmd.AddParameter(m_bTues);
	pCmd.AddParameter(m_bWednes);
	pCmd.AddParameter(m_bThurs);
	pCmd.AddParameter(m_bFri);
	pCmd.AddParameter(m_bSatur);
	pCmd.AddParameter(GetMonthPlayType());
	pCmd.AddParameter(++m_nMonthDay);
	pCmd.AddParameter(m_nMonthWeek);
	pCmd.AddParameter(++m_nMonthWeekend);
	pCmd.AddParameter(m_nDepositType);
	pCmd.AddParameter(LF->GetNoneCommaNumber(m_sDeposit));
	pCmd.AddParameter(GetStartDate());
	pCmd.AddParameter(GetEndDate());
	pCmd.AddParameter(m_sEtc);
	pCmd.AddParameter(m_bUseSms);
	pCmd.AddParameter(LF->GetNoneDashNumber(m_sSmsPhone));
	pCmd.AddParameter(m_bWorkerApply);
	pCmd.AddParameter(m_bNotWorkerApply);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.strName);

	return pCmd.Execute();
}

BOOL CMakeDepositJobNewDlg1::UpdateJob()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_schedule_job_2");
 
	pCmd.AddParameter(m_nID);
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(m_bUse);
	pCmd.AddParameter(m_sDisplayName);
	pCmd.AddParameter(GetPlayType());
	pCmd.AddParameter(m_bSun);
	pCmd.AddParameter(m_bMon);
	pCmd.AddParameter(m_bTues);
	pCmd.AddParameter(m_bWednes);
	pCmd.AddParameter(m_bThurs);
	pCmd.AddParameter(m_bFri);
	pCmd.AddParameter(m_bSatur);
	pCmd.AddParameter(GetMonthPlayType());
	pCmd.AddParameter(++m_nMonthDay);
	pCmd.AddParameter(m_nMonthWeek);
	pCmd.AddParameter(++m_nMonthWeekend);
	pCmd.AddParameter(m_nDepositType);
	pCmd.AddParameter(LF->GetNoneCommaNumber(m_sDeposit));
	pCmd.AddParameter(GetStartDate());
	pCmd.AddParameter(GetEndDate());
	pCmd.AddParameter(m_sEtc);
	pCmd.AddParameter(m_bUseSms);
	pCmd.AddParameter(LF->GetNoneDashNumber(m_sSmsPhone));
	pCmd.AddParameter(m_bWorkerApply);
	pCmd.AddParameter(m_bNotWorkerApply);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.strName);
	
	return pCmd.Execute();
}

void CMakeDepositJobNewDlg1::OnBnClickedMonthDayCheck()
{
	m_chkMonthDay.SetCheck(TRUE);
	m_chkMonthWeek.SetCheck(FALSE);
	ChangeSubControl();
}

void CMakeDepositJobNewDlg1::OnBnClickedMonthWeekCheck()
{
	m_chkMonthWeek.SetCheck(TRUE);
	m_chkMonthDay.SetCheck(FALSE);
	ChangeSubControl();
}

void CMakeDepositJobNewDlg1::OnBnClickedThursCheck()
{
}



void CMakeDepositJobNewDlg1::OnBnClickedEck()
{
	if(m_chkCopy.GetCheck())
	{
		CString sEtc; m_edtDisplayName.GetWindowText(sEtc);
		m_edtEtc.SetWindowText(sEtc);
	}
}

void CMakeDepositJobNewDlg1::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CMakeDepositJobNewDlg1::InitUpdateLog()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_schedule_job_update_log_one");

	pCmd.AddParameter(m_nID);

	if(!pRs.Execute(&pCmd)) return;
	if(pRs.GetRecordCount() == 0) return;

	long nPlayType, nMonthPlayType, nDeposit;
	CString sSmsPhone;

	pRs.GetFieldValue("bUse", m_bUse);
	pRs.GetFieldValue("sDisplayName", m_sDisplayName);
	pRs.GetFieldValue("nPlayType", nPlayType);
	pRs.GetFieldValue("bSunDay", m_bSun);
	pRs.GetFieldValue("bMonDay", m_bMon);
	pRs.GetFieldValue("bTuesDay", m_bTues);
	pRs.GetFieldValue("bWednesDay", m_bWednes);
	pRs.GetFieldValue("bThursDay", m_bThurs);
	pRs.GetFieldValue("bFriDay", m_bFri);
	pRs.GetFieldValue("bSaturDay", m_bSatur);
	pRs.GetFieldValue("nMonthPlayType", nMonthPlayType);
	pRs.GetFieldValue("bUse", m_bUse);
	pRs.GetFieldValue("nMonthDay", m_nMonthDay); m_nMonthDay--; //하루 작음 콤보
	pRs.GetFieldValue("nMonthWeek", m_nMonthWeek);
	pRs.GetFieldValue("nMonthWeekend", m_nMonthWeekend); m_nMonthWeekend--; //SQL날짜로 들어가 있음
	pRs.GetFieldValue("nDepositType", m_nDepositType);
	pRs.GetFieldValue("nDeposit", nDeposit);
	pRs.GetFieldValue("dtStart", m_dtStart);
	pRs.GetFieldValue("dtEnd", m_dtEnd);
	pRs.GetFieldValue("sEtc", m_sEtc);
	pRs.GetFieldValue("bUseSms", m_bUseSms);
	pRs.GetFieldValue("sSmsPhone", sSmsPhone);
	pRs.GetFieldValue("bWorkerApply", m_bWorkerApply);
	pRs.GetFieldValue("bNotWorkerApply", m_bNotWorkerApply);

	m_sDeposit = LF->GetMyNumberFormat(nDeposit);
	m_sSmsPhone = LF->GetDashPhoneNumber(sSmsPhone);

	SetPlayType(nPlayType);
	SetMonthPlayType(nMonthPlayType);

	UpdateData(FALSE);

	ChangeControl();
	ChangeSubControl();
}