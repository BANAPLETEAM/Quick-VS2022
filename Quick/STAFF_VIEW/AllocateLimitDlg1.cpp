// AllocateLimitDlg1.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AllocateLimitDlg1.h"



// CAllocateLimitDlg1 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAllocateLimitDlg1, CMyDialog)
CAllocateLimitDlg1::CAllocateLimitDlg1(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAllocateLimitDlg1::IDD, pParent)
{	
}

CAllocateLimitDlg1::~CAllocateLimitDlg1()
{
}

void CAllocateLimitDlg1::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_INSURANCE_3, m_stRiderAllocate.strInsuranceCompany);
	DDX_Text(pDX, IDC_EDIT_INSURANCE_4, m_stRiderAllocate.strInsuranceID);

	DDX_CBString(pDX, IDC_COMBO_ALLOCATELIMIT_1, m_stRiderAllocate.strLockTime);
	DDX_CBString(pDX, IDC_COMBO_ALLOCATELIMIT_2, m_stRiderAllocate.strLockCount);
	DDX_CBString(pDX, IDC_COMBO_OTHER_ORDER_ALLOCATELIMIT_1, m_stRiderAllocate.strLockTime4OCOrder);
	DDX_CBString(pDX, IDC_COMBO_OTHER_ORDER_ALLOCATELIMIT_2, m_stRiderAllocate.strLockCount4OCOrder);
	DDX_CBString(pDX, IDC_COMBO_MY_ORDER_ALLOCATELIMIT_1, m_stRiderAllocate.strLockTime4MyOrder);
	DDX_CBString(pDX, IDC_COMBO_MY_ORDER_ALLOCATELIMIT_2, m_stRiderAllocate.strLockCount4MyOrder);
	DDX_CBString(pDX, IDC_COMBO_TIMELIMIT_2, m_stRiderAllocate.strTimeAllocateRelease);

	DDX_DateTimeCtrl(pDX, IDC_DT_JOBSTART, m_stRiderAllocate.dtJobStart);
	DDX_DateTimeCtrl(pDX, IDC_DT_JOBEND, m_stRiderAllocate.dtJobEnd);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_SERVICESTOP, m_stRiderAllocate.dtJobStop);
	DDX_DateTimeCtrl(pDX, IDC_TIMELIMIT_1, m_stRiderAllocate.dtTimeAllocateDate);
	DDX_DateTimeCtrl(pDX, IDC_DT_INSURANCE_1, m_stRiderAllocate.dtInsuranceStart);
	DDX_DateTimeCtrl(pDX, IDC_DT_INSURANCE_2, m_stRiderAllocate.dtInsuranceEnd);	
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_stRiderAllocate.dtJobStopTime);	
	DDX_DateTimeCtrl(pDX, IDC_TIMELIMIT_0, m_stRiderAllocate.dtTimeAllocateTime);

	DDX_Control(pDX, IDC_CHECK_ALLOCATELIMIT, m_chkLock);
	DDX_Control(pDX, IDC_CHECK_SERVICESTOP, m_chkJobStop);
	DDX_Control(pDX, IDC_COMBO_ALLOCATELIMIT_1, m_cmbLockTime);
	DDX_Control(pDX, IDC_COMBO_ALLOCATELIMIT_2, m_cmbLockCount);
	DDX_Control(pDX, IDC_COMBO_OTHER_ORDER_ALLOCATELIMIT_1, m_cmbLockTime4OCOrder);
	DDX_Control(pDX, IDC_COMBO_OTHER_ORDER_ALLOCATELIMIT_2, m_cmbLockCount4OCOrder);
	DDX_Control(pDX, IDC_COMBO_MY_ORDER_ALLOCATELIMIT_1, m_cmbLockTime4MyOrder);
	DDX_Control(pDX, IDC_COMBO_MY_ORDER_ALLOCATELIMIT_2, m_cmbLockCount4MyOrder);
	DDX_Control(pDX, IDC_CHECK_TIMELIMIT, m_chkAllocate);
	DDX_Control(pDX, IDC_TIMELIMIT_1, m_dtpAllocateTime);
	DDX_Control(pDX, IDC_COMBO_TIMELIMIT_2, m_cmbAllocateRelease);
	DDX_Control(pDX, IDC_CHECK_INSURANCE, m_chkInsurance);
	DDX_Control(pDX, IDC_COMBO_SERVICESTOP, m_dtpJobStop);
	DDX_Control(pDX, IDC_DT_INSURANCE_1, m_dtpInsuranceStart);
	DDX_Control(pDX, IDC_DT_INSURANCE_2, m_dtpInsuranceEnd);
	DDX_Control(pDX, IDC_EDIT_INSURANCE_3, m_edtInsuranceCompany);
	DDX_Control(pDX, IDC_EDIT_INSURANCE_4, m_edtInsuranceID);
	DDX_Control(pDX, IDC_DT_JOBSTART, m_dtpJobStart);
	DDX_Control(pDX, IDC_DT_JOBEND, m_dtpJobEnd);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtpJobStopTime);
	DDX_Control(pDX, IDC_TIMELIMIT_0, m_dtpAllocateDate);
	DDX_Control(pDX, IDC_CHECK_SERVICERENT_LIMIT, m_chkServiceRentLimit);

	DDX_Check(pDX, IDC_CHECK_SERVICESTOP, m_stRiderAllocate.bJobStop);
	DDX_Check(pDX, IDC_CHECK_ALLOCATELIMIT, m_stRiderAllocate.bLock);
	DDX_Check(pDX, IDC_CHECK_MY_ORDER_ALLOCATELIMIT, m_stRiderAllocate.bMyOrderLock);
	DDX_Check(pDX, IDC_CHECK_OTHER_ORDER_ALLOCATELIMIT, m_stRiderAllocate.bOtherOrderLock);
	DDX_Check(pDX, IDC_CHECK_TIMELIMIT, m_stRiderAllocate.bTimeAllocate);
	DDX_Check(pDX, IDC_CHECK_INSURANCE, m_stRiderAllocate.bInsurance);
	DDX_Check(pDX, IDC_CHECK_SERVICERENT_LIMIT, m_stRiderAllocate.bServiceRentLimit);		

	DDX_Control(pDX, IDC_STATIC5, m_Static5);
	DDX_Control(pDX, IDC_STATIC6, m_Static6);
	DDX_Control(pDX, IDC_STATIC7, m_Static7);
	DDX_Control(pDX, IDC_STATIC8, m_Static8);
	DDX_Control(pDX, IDC_STATIC9, m_Static9);
	DDX_Control(pDX, IDC_STATIC10, m_Static10);
	DDX_Control(pDX, IDC_STATIC11, m_Static11);
	DDX_Control(pDX, IDC_STATIC12, m_Static12);
	DDX_Control(pDX, IDC_STATIC13, m_Static13);
	DDX_Control(pDX, IDC_STATIC14, m_Static14);
	DDX_Control(pDX, IDC_STATIC15, m_Static15);
	DDX_Control(pDX, IDC_STATIC21, m_Static21);
	DDX_Control(pDX, IDC_STATIC23, m_Static23);
	DDX_Control(pDX, IDC_STATIC24, m_Static24);
	DDX_Control(pDX, IDC_STATIC25, m_Static25);

	DDX_Control(pDX, IDC_WORKSTOP_MEMO_COMBO, m_cmbWorkStopMemo);
	DDX_Control(pDX, IDC_CHECK_OTHER_ORDER_ALLOCATELIMIT, m_chkLock4OCOrder);
	DDX_Control(pDX, IDC_CHECK_MY_ORDER_ALLOCATELIMIT, m_chkLock4MyOrder);
	DDX_Control(pDX, IDC_COMBO_SHARE_LIMIT, m_cmbShareLimit);
	DDX_Control(pDX, IDC_ELAPSE_LIMIT_ALLOCATE_LOCAL_COMBO, m_cmbElapseLimitAllocateLocal);
	DDX_Control(pDX, IDC_ELAPSE_LIMIT_PICKUP_LOCAL_COMBO, m_cmbElapseLimitPickupLocal);
	DDX_Control(pDX, IDC_ELAPSE_LIMIT_ALLOCATE_GLOBAL_COMBO, m_cmbElapseLimitAllocateGlobal);
	DDX_Control(pDX, IDC_ELAPSE_LIMIT_PICKUP_GLOBAL_COMBO, m_cmbElapseLimitPickupGlobal);

	DDX_Control(pDX, IDC_AUTO_CHK, m_chkAuto);
	DDX_Control(pDX, IDC_BIG_AUTO_CHK, m_chkBigAuto);
	DDX_Control(pDX, IDC_DAMA_CHK, m_chkDama);
	DDX_Control(pDX, IDC_RABO_CHK, m_chkRabo);
	DDX_Control(pDX, IDC_BAN_CHK, m_chkBan);
	DDX_Control(pDX, IDC_TRUCK_CHK, m_chkTruck);
	DDX_Control(pDX, IDC_ALL_CHK, m_chkAll);

	DDX_Check(pDX, IDC_AUTO_CHK, m_stRiderAllocate.bAutoShow);
	DDX_Check(pDX, IDC_BIG_AUTO_CHK, m_stRiderAllocate.bBigAutoShow);
	DDX_Check(pDX, IDC_DAMA_CHK, m_stRiderAllocate.bDamaShow);
	DDX_Check(pDX, IDC_RABO_CHK, m_stRiderAllocate.bRaboShow);
	DDX_Check(pDX, IDC_BAN_CHK, m_stRiderAllocate.bBanShow);
	DDX_Check(pDX, IDC_TRUCK_CHK, m_stRiderAllocate.bTruckShow);

	DDX_CBString(pDX, IDC_ELAPSE_LIMIT_ALLOCATE_LOCAL_COMBO, m_stRiderAllocate.strElapseLimitAllocateLocal);
	DDX_CBString(pDX, IDC_ELAPSE_LIMIT_PICKUP_LOCAL_COMBO, m_stRiderAllocate.strElapseLimitPickupLocal);
	DDX_CBString(pDX, IDC_ELAPSE_LIMIT_ALLOCATE_GLOBAL_COMBO, m_stRiderAllocate.strElapseLimitAllocateGlobal);
	DDX_CBString(pDX, IDC_ELAPSE_LIMIT_PICKUP_GLOBAL_COMBO, m_stRiderAllocate.strElapseLimitPickupGlobal);

	DDX_CBIndex(pDX, IDC_COMBO_SHARE_LIMIT, m_stRiderAllocate.nPanaltyTypeShowOrder);
}


BEGIN_MESSAGE_MAP(CAllocateLimitDlg1, CMyDialog)
	ON_BN_CLICKED(IDC_IDOK, OnBnClickedIdok)
	ON_BN_CLICKED(IDC_CHECK_SERVICESTOP, OnBnClickedCheckServicestop)
	ON_BN_CLICKED(IDC_CHECK_ALLOCATELIMIT, OnBnClickedCheckAllocatelimit)
	ON_BN_CLICKED(IDC_CHECK_TIMELIMIT, OnBnClickedCheckTimelimit)
	ON_BN_CLICKED(IDC_CHECK_INSURANCE, OnBnClickedCheckInsurance)	

	ON_BN_CLICKED(IDC_CHECK_OTHER_ORDER_ALLOCATELIMIT, OnBnClickedCheckOtherOrderAllocatelimit)
	ON_BN_CLICKED(IDC_CHECK_MY_ORDER_ALLOCATELIMIT, OnBnClickedCheckMyOrderAllocatelimit)
	ON_BN_CLICKED(IDC_IDCANCEL, OnBnClickedIdcancel)
	ON_BN_CLICKED(IDC_AUTO_CHK, OnBnClickedAutoChk)
	ON_BN_CLICKED(IDC_BIG_AUTO_CHK, OnBnClickedBigAutoChk)
	ON_BN_CLICKED(IDC_DAMA_CHK, OnBnClickedDamaChk)
	ON_BN_CLICKED(IDC_RABO_CHK, OnBnClickedRaboChk)
	ON_BN_CLICKED(IDC_BAN_CHK, OnBnClickedBanChk)
	ON_BN_CLICKED(IDC_TRUCK_CHK, OnBnClickedTruckChk)
	ON_BN_CLICKED(IDC_ALL_CHK, OnBnClickedAllChk)
END_MESSAGE_MAP()


// CAllocateLimitDlg1 메시지 처리기입니다.

BOOL CAllocateLimitDlg1::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_dtpJobStart.SetFormat("tth:mm");
	m_dtpJobEnd.SetFormat("tth:mm");
	m_dtpJobStop.SetFormat("yyyy-MM-dd");
	m_dtpJobStopTime.SetFormat("tth:mm");
	m_dtpAllocateTime.SetFormat("tth:mm");

	InitData();
 

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAllocateLimitDlg1::OnBnClickedIdok()
{
	if(ModfiyProcess())
	{
		//MessageBox("저장완료", "확인", MB_ICONINFORMATION);
		OnOK();
		return;
	}
}

void CAllocateLimitDlg1::InitData()
{
	m_stRiderAllocate.nCompany = m_nRiderCompany;
	m_stRiderAllocate.nRNo = m_nRNo;

	char buffer[20];

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_allocate_limit_2008_1");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRiderCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRNo);

	CString strWorkStateMemo;
	long nLockTime, nLockCount, nReleaseMin, nLockTime4MyOrder, nLockCount4MyOrder, nLockTime4OCOrder, nLockCount4OCOrder;
	//BOOL bAllocateLimit;//, bInsurance;

	COleDateTime dtAllocateLimitDate;

	if(!pRs.Execute(&pCmd)) return;		

	if(pRs.GetRecordCount() == 0)
	{
		return;
	} 

	pRs.GetFieldValue("dtAttend", m_stRiderAllocate.dtJobStart);
	pRs.GetFieldValue("dtLeave", m_stRiderAllocate.dtJobEnd);
	pRs.GetFieldValue("nWorkState", m_stRiderAllocate.nWorkState);
	m_stRiderAllocate.bJobStop = m_stRiderAllocate.nWorkState;
	pRs.GetFieldValue("dtWorkStateDate", m_stRiderAllocate.dtJobStop);
	m_stRiderAllocate.dtJobStopTime = m_stRiderAllocate.dtJobStop;
	pRs.GetFieldValue("sWorkStateMemo", m_stRiderAllocate.strJobStopMemo);
	m_cmbWorkStopMemo.SetWindowText(m_stRiderAllocate.strJobStopMemo);

	if(!m_stRiderAllocate.bJobStop)
	{					
		m_stRiderAllocate.dtJobStop = COleDateTime::GetCurrentTime();
	}


	pRs.GetFieldValue("nLockTime", nLockTime);
	pRs.GetFieldValue("nLockCount", nLockCount);

	if(nLockTime == 0 || nLockCount >= 100)
	{
		m_stRiderAllocate.bLock = FALSE;
		m_stRiderAllocate.strLockTime = "";	
		m_stRiderAllocate.strLockCount = "무제한";
	}
	else
	{
		m_stRiderAllocate.bLock = TRUE;
		m_stRiderAllocate.strLockTime.Format("%d", nLockTime);
		m_stRiderAllocate.strLockCount.Format("%d", nLockCount);
	}

	pRs.GetFieldValue("nLockTime4MyOrder", nLockTime4MyOrder);
	pRs.GetFieldValue("nLockCount4MyOrder", nLockCount4MyOrder);

	if(nLockTime4MyOrder == 0 || nLockCount4MyOrder >= 100)
	{
		m_stRiderAllocate.bMyOrderLock = FALSE;
		m_stRiderAllocate.strLockTime4MyOrder = "";	
		m_stRiderAllocate.strLockCount4MyOrder = "무제한";
	}
	else
	{
		m_stRiderAllocate.bMyOrderLock = TRUE;
		m_stRiderAllocate.strLockTime4MyOrder.Format("%d", nLockTime4MyOrder);
		m_stRiderAllocate.strLockCount4MyOrder.Format("%d", nLockCount4MyOrder);
	}

	pRs.GetFieldValue("nLockTime4OCOrder", nLockTime4OCOrder);
	pRs.GetFieldValue("nLockCount4OCOrder", nLockCount4OCOrder);

	if(nLockTime4OCOrder == 0 || nLockCount4OCOrder >= 100)
	{
		m_stRiderAllocate.bOtherOrderLock = FALSE;
		m_stRiderAllocate.strLockTime4OCOrder = "";	
		m_stRiderAllocate.strLockCount4OCOrder = "무제한";
	}
	else
	{
		m_stRiderAllocate.bOtherOrderLock = TRUE;
		m_stRiderAllocate.strLockTime4OCOrder.Format("%d", nLockTime4OCOrder);
		m_stRiderAllocate.strLockCount4OCOrder.Format("%d", nLockCount4OCOrder);
	}

	pRs.GetFieldValue("bAllocateLimit", m_stRiderAllocate.bTimeAllocate);
	pRs.GetFieldValue("dtAllocateLimitDate", m_stRiderAllocate.dtTimeAllocateDate);
	pRs.GetFieldValue("nReleaseMin", nReleaseMin);

	m_stRiderAllocate.strTimeAllocateRelease = itoa(nReleaseMin, buffer, 10);

	m_stRiderAllocate.dtTimeAllocateTime = m_stRiderAllocate.dtTimeAllocateDate;

	if(!m_stRiderAllocate.bTimeAllocate)
	{
		m_stRiderAllocate.dtTimeAllocateDate = COleDateTime::GetCurrentTime();
		m_stRiderAllocate.dtTimeAllocateTime = COleDateTime::GetCurrentTime();		
		m_stRiderAllocate.strTimeAllocateRelease = "";
	}		
	else
	{
		//m_dtAllocateDate = dtAllocateLimitDate;
		//m_dtAllocateTime = dtAllocateLimitDate;
		m_stRiderAllocate.strTimeAllocateRelease.Format("%d", nReleaseMin);
	}

	pRs.GetFieldValue("bInsurance", m_stRiderAllocate.bInsurance);
	pRs.GetFieldValue("dtInsuranceStart", m_stRiderAllocate.dtInsuranceStart);
	pRs.GetFieldValue("dtInsuranceEnd", m_stRiderAllocate.dtInsuranceEnd);
	pRs.GetFieldValue("sInsuranceID", m_stRiderAllocate.strInsuranceID);
 
	if(!m_stRiderAllocate.bInsurance)
	{
		m_stRiderAllocate.bInsurance = FALSE;
		m_stRiderAllocate.dtInsuranceStart  = COleDateTime::GetCurrentTime();
		m_stRiderAllocate.dtInsuranceEnd = COleDateTime::GetCurrentTime();
	}
	else
	{
		long nFind = m_stRiderAllocate.strInsuranceID.Find("/");
		if(nFind > 0)
		{
			m_stRiderAllocate.strInsuranceCompany = m_stRiderAllocate.strInsuranceID.Left(nFind);
			m_stRiderAllocate.strInsuranceID = m_stRiderAllocate.strInsuranceID.Mid(nFind + 1, m_stRiderAllocate.strInsuranceID.GetLength() - 1);
		}
	}

	long nElapseLimitAllocateLocal;
	long nElapseLimitAllocateGlobal;
	long nElapseLimitPickupLocal;
	long nElapseLimitPickupGlobal;

	//pRs.GetFieldValue("bUseSMS", m_bSms);
	pRs.GetFieldValue("nPanaltyTypeShowOrder", m_stRiderAllocate.nPanaltyTypeShowOrder);
	pRs.GetFieldValue("nElapseLimitAllocateLocal", nElapseLimitAllocateLocal);
	pRs.GetFieldValue("nElapseLimitAllocateGlobal", nElapseLimitAllocateGlobal);
	pRs.GetFieldValue("nElapseLimitPickupLocal", nElapseLimitPickupLocal);
	pRs.GetFieldValue("nElapseLimitPickupGlobal", nElapseLimitPickupGlobal);

	m_stRiderAllocate.strElapseLimitAllocateLocal = itoa(nElapseLimitAllocateLocal, buffer, 10);
	m_stRiderAllocate.strElapseLimitAllocateGlobal = itoa(nElapseLimitAllocateGlobal, buffer, 10); 
	m_stRiderAllocate.strElapseLimitPickupLocal = itoa(nElapseLimitPickupLocal, buffer, 10);
	m_stRiderAllocate.strElapseLimitPickupGlobal = itoa(nElapseLimitPickupGlobal, buffer, 10);


	pRs.GetFieldValue("bAutoShow", m_stRiderAllocate.bAutoShow);
	pRs.GetFieldValue("bBigAutoShow", m_stRiderAllocate.bBigAutoShow);
	pRs.GetFieldValue("bDamaShow", m_stRiderAllocate.bDamaShow);
	pRs.GetFieldValue("bRaboShow", m_stRiderAllocate.bRaboShow);
	pRs.GetFieldValue("bBanShow", m_stRiderAllocate.bBanShow);
	pRs.GetFieldValue("bTruckShow", m_stRiderAllocate.bTruckShow);  

	m_stRiderAllocate.nAllocGroup = 0;
  
	UpdateData(FALSE);
	InitControl();
}

BOOL CAllocateLimitDlg1::ModfiyProcess(void)
{
	UpdateData();

	if(CheckData() == FALSE)
	{	
		return	FALSE;
	}

	if(SaveAllocateInfo(&m_stRiderAllocate, FALSE))
	{
		//UpdateData(FALSE);
		return TRUE;
	}

	return FALSE;
}



void CAllocateLimitDlg1::OnBnClickedCheckServicestop()
{

	if(m_chkJobStop.GetCheck() == BST_CHECKED )
	{
		m_dtpJobStop.EnableWindow(TRUE);
		m_dtpJobStopTime.EnableWindow(TRUE);
	}
	else
	{
		m_dtpJobStop.EnableWindow(FALSE);
		m_dtpJobStopTime.EnableWindow(FALSE);
	}

}

void CAllocateLimitDlg1::OnBnClickedCheckAllocatelimit()
{

	if(m_chkLock.GetCheck() == BST_CHECKED )
	{		
		m_cmbLockCount.EnableWindow(TRUE);
		m_cmbLockTime.EnableWindow(TRUE);
	}
	else
	{
		m_cmbLockCount.EnableWindow(FALSE);
		m_cmbLockTime.EnableWindow(FALSE);
	}		
}

void CAllocateLimitDlg1::OnBnClickedCheckTimelimit()
{

	if(m_chkAllocate.GetCheck() ==	BST_CHECKED)
	{
		m_dtpAllocateDate.EnableWindow(TRUE);
		m_dtpAllocateTime.EnableWindow(TRUE);
		m_cmbAllocateRelease.EnableWindow(TRUE);
	}
	else
	{
		m_dtpAllocateDate.EnableWindow(FALSE);
		m_dtpAllocateTime.EnableWindow(FALSE);
		m_cmbAllocateRelease.EnableWindow(FALSE);
	}
}

void CAllocateLimitDlg1::OnBnClickedCheckInsurance()
{

	if(m_chkInsurance.GetCheck() ==	BST_CHECKED)
	{	
		m_dtpInsuranceStart.EnableWindow(TRUE);
		m_dtpInsuranceEnd.EnableWindow(TRUE);
		m_edtInsuranceCompany.EnableWindow(TRUE);
		m_edtInsuranceID.EnableWindow(TRUE);
	}
	else
	{
		m_dtpInsuranceStart.EnableWindow(FALSE);
		m_dtpInsuranceEnd.EnableWindow(FALSE);
		m_edtInsuranceCompany.EnableWindow(FALSE);
		m_edtInsuranceID.EnableWindow(FALSE);
	}

}


void CAllocateLimitDlg1::InitControl(void)
{
	if(m_stRiderAllocate.bJobStop ==TRUE)
	{
		m_chkJobStop.SetCheck(BST_CHECKED);
		UpdateData();
		m_cmbWorkStopMemo.SetWindowText(m_stRiderAllocate.strJobStopMemo);
		UpdateData(FALSE);
	}

	if(m_stRiderAllocate.bTimeAllocate == TRUE)
		m_chkAllocate.SetCheck(BST_CHECKED);

	if(m_stRiderAllocate.bServiceRentLimit == TRUE)
		m_chkServiceRentLimit.SetCheck(BST_CHECKED);

	if(m_stRiderAllocate.bInsurance ==TRUE)
		m_chkInsurance.SetCheck(BST_CHECKED);

	if(m_stRiderAllocate.bLock ==TRUE)
		m_chkLock.SetCheck(BST_CHECKED);

	if(m_stRiderAllocate.bMyOrderLock ==TRUE)
		m_chkLock4MyOrder.SetCheck(BST_CHECKED);

	if(m_stRiderAllocate.bOtherOrderLock ==TRUE)
		m_chkLock4OCOrder.SetCheck(BST_CHECKED);

	m_cmbShareLimit.SetCurSel(m_stRiderAllocate.nPanaltyTypeShowOrder);

	m_cmbElapseLimitAllocateLocal.SetWindowText(m_stRiderAllocate.strElapseLimitAllocateLocal);
	m_cmbElapseLimitPickupLocal.SetWindowText(m_stRiderAllocate.strElapseLimitPickupLocal);
	m_cmbElapseLimitAllocateGlobal.SetWindowText(m_stRiderAllocate.strElapseLimitAllocateGlobal);
	m_cmbElapseLimitPickupGlobal.SetWindowText(m_stRiderAllocate.strElapseLimitPickupGlobal);

	if(m_stRiderAllocate.bAutoShow && m_stRiderAllocate.bBigAutoShow && m_stRiderAllocate.bDamaShow && 
		m_stRiderAllocate.bRaboShow && m_stRiderAllocate.bBanShow && m_stRiderAllocate.bTruckShow)
		m_chkAll.SetCheck(TRUE);

	OnBnClickedCheckServicestop();
	OnBnClickedCheckAllocatelimit();
	OnBnClickedCheckOtherOrderAllocatelimit();
	OnBnClickedCheckMyOrderAllocatelimit();
	OnBnClickedCheckTimelimit();
	OnBnClickedCheckInsurance();
	//UpdateData(FALSE);
}

void CAllocateLimitDlg1::CheckAll()
{
	if(m_chkAuto.GetCheck() &&
		m_chkBigAuto.GetCheck() &&
		m_chkDama.GetCheck() &&
		m_chkRabo.GetCheck() &&
		m_chkBan.GetCheck() &&
		m_chkTruck.GetCheck())
		m_chkAll.SetCheck(TRUE);
	else
		m_chkAll.SetCheck(FALSE);
}

BOOL CAllocateLimitDlg1::CheckData(void)
{
	try{
		if(m_chkLock.GetCheck() == BST_CHECKED)
		{
			if(m_stRiderAllocate.strLockCount == "" || m_stRiderAllocate.strLockTime == "" || 
				m_stRiderAllocate.strLockCount == "0" || m_stRiderAllocate.strLockTime == "0") 
				throw "배차제한 항목에 값이 빠져있습니다";
		}

		if(m_chkAllocate.GetCheck() == BST_CHECKED)
		{
			if(m_stRiderAllocate.strTimeAllocateRelease == "" || m_stRiderAllocate.strTimeAllocateRelease == "0")
				throw "시간제한 항목에 0값이나 비어있으면 안됩니다.";

		}

		if(m_chkAllocate.GetCheck() == BST_CHECKED)
		{
			COleDateTime dtDateTime;
			COleDateTimeSpan dtSpan;
			dtSpan.SetDateTimeSpan(0,0,atoi(m_stRiderAllocate.strTimeAllocateRelease),0);
			dtDateTime = m_stRiderAllocate.dtTimeAllocateDate;
			dtDateTime += dtSpan;

			if(dtDateTime < COleDateTime::GetCurrentTime())
				throw "시간제한 세팅한 값이 현재시간보다 이전입니다. 시간 세팅을 다시 해주세요";
		}

		if(m_chkInsurance.GetCheck() == BST_CHECKED)
		{
			if(m_stRiderAllocate.strInsuranceCompany == "" || m_stRiderAllocate.strInsuranceID == "")
				throw "보험관련 항목에 값이 빠져있습니다.";

			if(m_stRiderAllocate.dtInsuranceStart >= m_stRiderAllocate.dtInsuranceEnd )
				throw "보험종료일이 보험시작일 보다 같거나 작습니다.";			
		}
	}
	catch(char *msg)
	{
		MessageBox(msg, "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	return TRUE;	
}



void CAllocateLimitDlg1::OnBnClickedCheckOtherOrderAllocatelimit()
{
	if(m_chkLock4OCOrder.GetCheck() == BST_CHECKED )
	{		
		m_cmbLockCount4OCOrder.EnableWindow(TRUE);
		m_cmbLockTime4OCOrder.EnableWindow(TRUE);
	}
	else
	{
		m_cmbLockCount4OCOrder.EnableWindow(FALSE);
		m_cmbLockTime4OCOrder.EnableWindow(FALSE);
	}		
}

void CAllocateLimitDlg1::OnBnClickedCheckMyOrderAllocatelimit()
{
	if(m_chkLock4MyOrder.GetCheck() == BST_CHECKED )
	{		
		m_cmbLockCount4MyOrder.EnableWindow(TRUE);
		m_cmbLockTime4MyOrder.EnableWindow(TRUE);
	}
	else
	{
		m_cmbLockCount4MyOrder.EnableWindow(FALSE);
		m_cmbLockTime4MyOrder.EnableWindow(FALSE);
	}	
}



void CAllocateLimitDlg1::OnBnClickedIdcancel()
{
	OnCancel();
}

void CAllocateLimitDlg1::OnBnClickedAutoChk()
{
	CheckAll();
}

void CAllocateLimitDlg1::OnBnClickedBigAutoChk()
{
	CheckAll();
}

void CAllocateLimitDlg1::OnBnClickedDamaChk()
{
	CheckAll();
}

void CAllocateLimitDlg1::OnBnClickedRaboChk()
{
	CheckAll();
}

void CAllocateLimitDlg1::OnBnClickedBanChk()
{
	CheckAll();
}

void CAllocateLimitDlg1::OnBnClickedTruckChk()
{
	CheckAll();
}

void CAllocateLimitDlg1::OnBnClickedAllChk()
{
	BOOL bCheck = m_chkAll.GetCheck();

	m_chkAuto.SetCheck(bCheck);
	m_chkBigAuto.SetCheck(bCheck);
	m_chkDama.SetCheck(bCheck);
	m_chkRabo.SetCheck(bCheck);
	m_chkBan.SetCheck(bCheck);
	m_chkTruck.SetCheck(bCheck);
}
