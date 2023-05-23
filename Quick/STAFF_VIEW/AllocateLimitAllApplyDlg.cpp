// AllocateLimitAllApplyDlg.cpp : 구현 파일입니다.
//



#include "stdafx.h"
#include "resource.h"
#include "AllocateLimitAllApplyDlg.h"

//#include "StaffPage12.h"


// CAllocateLimitAllApplyDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAllocateLimitAllApplyDlg, CMyDialog)
CAllocateLimitAllApplyDlg::CAllocateLimitAllApplyDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAllocateLimitAllApplyDlg::IDD, pParent)	
	
	, m_dtJobStart(COleDateTime::GetCurrentTime())
	, m_dtJobStop(COleDateTime::GetCurrentTime())	
	, m_sLockTime(_T(""))
	, m_sLockCount(_T(""))
	, m_dtAllocateDate(COleDateTime::GetCurrentTime())
	, m_dtAllocateTime(COleDateTime::GetCurrentTime())
	, m_sReleaseMin(_T(""))
	, m_dtInsuranceStart(COleDateTime::GetCurrentTime())
	, m_dtInsuranceEnd(COleDateTime::GetCurrentTime())
	, m_sInsuranceCompany(_T(""))
	, m_sInsuranceID(_T(""))		
	, m_nAllocate(0)
	, m_nLockTime(0)
	, m_nJobStop(0)
	, m_nSms(0)
	, m_nInsurance(0)
	, m_nServiceRentLimit(0)	
	, m_bSelectApply(FALSE)
	, m_bAllApply(false)	
	, m_dtJobStopTime(COleDateTime::GetCurrentTime())
{
	m_pkey = NULL;
	m_pParentWnd = pParent;
}

CAllocateLimitAllApplyDlg::~CAllocateLimitAllApplyDlg()
{
	if(m_pkey)
		delete m_pkey;
}

void CAllocateLimitAllApplyDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_APPLY_SMS, m_chkSms);

	DDX_Control(pDX, IDC_CHECK_WORKTIME, m_chkJobTime);
	DDX_Control(pDX, IDC_DT_JOBSTART, m_dtpJobStart);
	DDX_Control(pDX, IDC_DT_JOBEND, m_dtpJobEnd);
	DDX_DateTimeCtrl(pDX, IDC_DT_JOBSTART, m_dtJobStart);
	DDX_DateTimeCtrl(pDX, IDC_DT_JOBEND, m_dtJobEnd);

	DDX_Control(pDX, IDC_CHECK_SERVICESTOP, m_chkJobStop);
	DDX_Control(pDX, IDC_COMBO_SERVICESTOP, m_dtpJobStop);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_SERVICESTOP, m_dtJobStop);
	DDX_Control(pDX, IDC_WORKSTOP_MEMO_COMBO, m_cmbWorkStopMemo);

	DDX_Control(pDX, IDC_AUTO_CHK, m_chkAuto);
	DDX_Control(pDX, IDC_BIG_AUTO_CHK1, m_chkBigAuto);
	DDX_Control(pDX, IDC_DAMA_CHK, m_chkDama);
	DDX_Control(pDX, IDC_RABO_CHK, m_chkRabo);
	DDX_Control(pDX, IDC_BAN_CHK, m_chkBan);
	DDX_Control(pDX, IDC_TRUCK_CHK, m_chkTruck);
	DDX_Control(pDX, IDC_ALL_CHK, m_chkAll);

	DDX_Control(pDX, IDC_CHECK_ORDER, m_chkOrder);
	DDX_Control(pDX, IDC_CHECK_LOCK, m_chkLock);
	DDX_Control(pDX, IDC_CHECK_MY_ORDER_LOCK, m_chkMyOrderLock);
	DDX_Control(pDX, IDC_CHECK_OTHER_ORDER_LOCK, m_chkOtherOrderLock);
	DDX_Control(pDX, IDC_COMBO_ALLOCATELIMIT_1, m_cmbLockTime);
	DDX_Control(pDX, IDC_COMBO_ALLOCATELIMIT_2, m_cmbLockCount);
	DDX_CBString(pDX, IDC_COMBO_ALLOCATELIMIT_1, m_sLockTime);
	DDX_CBString(pDX, IDC_COMBO_ALLOCATELIMIT_2, m_sLockCount);

	DDX_Control(pDX, IDC_COMBO_MY_ORDER_ALLOCATELIMIT_1, m_cmbMyOrderLockTime);
	DDX_Control(pDX, IDC_COMBO_MY_ORDER_ALLOCATELIMIT_2, m_cmbMyOrderLockCount);
	DDX_CBString(pDX, IDC_COMBO_MY_ORDER_ALLOCATELIMIT_1, m_sMyOrderLockTime);
	DDX_CBString(pDX, IDC_COMBO_MY_ORDER_ALLOCATELIMIT_2, m_sMyOrderLockCount);

	DDX_Control(pDX, IDC_COMBO_OTHER_ORDER_ALLOCATELIMIT_1, m_cmbOtherOrderLockTime);
	DDX_Control(pDX, IDC_COMBO_OTHER_ORDER_ALLOCATELIMIT_2, m_cmbOtherOrderLockCount);
	DDX_CBString(pDX, IDC_COMBO_OTHER_ORDER_ALLOCATELIMIT_1, m_sOtherOrderLockTime);
	DDX_CBString(pDX, IDC_COMBO_OTHER_ORDER_ALLOCATELIMIT_2, m_sOtherOrderLockCount);


	DDX_Control(pDX, IDC_CHECK_TIMELIMIT, m_chkAllocate);
	DDX_Control(pDX, IDC_TIMELIMIT_2, m_dtpAllocateDate);
	DDX_Control(pDX, IDC_TIMELIMIT_1, m_dtpAllocateTime);
	DDX_Control(pDX, IDC_COMBO_TIMELIMIT_2, m_cmbReleaseMin);
	DDX_DateTimeCtrl(pDX, IDC_TIMELIMIT_2, m_dtAllocateDate);
	DDX_DateTimeCtrl(pDX, IDC_TIMELIMIT_1, m_dtAllocateTime);
	DDX_CBString(pDX, IDC_COMBO_TIMELIMIT_2, m_sReleaseMin);


	DDX_Control(pDX, IDC_CHECK_INSURANCE, m_chkInsurance);	
	DDX_Control(pDX, IDC_DT_INSURANCE_1, m_dtpInsuranceStart);
	DDX_Control(pDX, IDC_DT_INSURANCE_2, m_dtpInsuranceEnd);
	DDX_Control(pDX, IDC_EDIT_INSURANCE_3, m_edtInsuranceCompany);
	DDX_Control(pDX, IDC_EDIT_INSURANCE_4, m_edtInsuranceID);
	DDX_DateTimeCtrl(pDX, IDC_DT_INSURANCE_1, m_dtInsuranceStart);
	DDX_DateTimeCtrl(pDX, IDC_DT_INSURANCE_2, m_dtInsuranceEnd);
	DDX_Text(pDX, IDC_EDIT_INSURANCE_3, m_sInsuranceCompany);
	DDX_Text(pDX, IDC_EDIT_INSURANCE_4, m_sInsuranceID);	

	DDX_Control(pDX, IDC_RADIO_SMS_APPLY, m_rdoSmsApply);

	DDX_Control(pDX, IDC_RADIO_JOBSTOP, m_rdoJobStopApply);
	DDX_Control(pDX, IDC_RADIO_LOCKTIME_APPLY, m_rdoLockApply);
	DDX_Control(pDX, IDC_RADIO_MY_ORDER_LOCKTIME_APPLY, m_rdoMyOrderLockApply);
	DDX_Control(pDX, IDC_RADIO_OTHER_ORDER_LOCKTIME_APPLY, m_rdoOtherOrderLockApply);
	DDX_Control(pDX, IDC_RADIO_ALLOCATE_APPLY, m_rdoAllocateApply);
	DDX_Control(pDX, IDC_RADIO_INSURANCE_APPLY, m_rdoInsuranceApply);
	DDX_Control(pDX, IDC_RADIO_SELECT_APPLY, m_rdoSelectApply);


	DDX_Radio(pDX, IDC_RADIO_SELECT_APPLY, m_bSelectApply);
	DDX_Control(pDX, IDC_LIST, m_ListCtrl);
	DDX_Control(pDX, IDC_CHECK_SERVICE_RENT_LIMIT, m_chkServiceRentLimit);
	DDX_Control(pDX, IDC_RADIO_SERVICE_RENT_LIMIT_APPLY, m_rdoServiceRentLimit);
	DDX_Control(pDX, IDC_COMBO_SERVICESTOP2, m_dtpJobStopTime);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_SERVICESTOP2, m_dtJobStopTime);

	DDX_Control(pDX, IDC_TIME_LIMIT_CHECK, m_TimeLimitChk);
	DDX_Control(pDX, IDC_ELAPSE_LIMIT_ALLOCATE_LOCAL_COMBO, m_ElapseLimitAllocateLocalCmb);
	DDX_Control(pDX, IDC_ELAPSE_LIMIT_ALLOCATE_GLOBAL_COMBO, m_ElapseLimitAllocateGlobalCmb);
	DDX_Control(pDX, IDC_ELAPSE_LIMIT_PICKUP_LOCAL_COMBO, m_ElapseLimitPickupLocalCmb);
	DDX_Control(pDX, IDC_ELAPSE_LIMIT_PICKUP_GLOBAL_COMBO, m_ElapseLimitPickupGlobalCmb);
	DDX_Control(pDX, IDC_CHECK_SHARE_LIMIT, m_chkShareLimit);
	DDX_Control(pDX, IDC_COMBO_SHARE_LIMIT, m_cmbShareLimit);
}


BEGIN_MESSAGE_MAP(CAllocateLimitAllApplyDlg, CMyDialog)
	
	ON_BN_CLICKED(IDC_IDOK, OnBnClickedIdok)
	ON_BN_CLICKED(IDC_IDCANCEL, OnBnClickedIdcancel)	

	ON_BN_CLICKED(IDC_CHECK_APPLY_SMS, OnBnClickedCheckApplySms)
	ON_BN_CLICKED(IDC_CHECK_WORKTIME, OnBnClickedCheckWorktime)	
	ON_BN_CLICKED(IDC_CHECK_ORDER, OnBnClickedCheckOrder)
	ON_BN_CLICKED(IDC_CHECK_LOCK, OnBnClickedCheckLock)
	ON_BN_CLICKED(IDC_CHECK_MY_ORDER_LOCK, OnBnClickedCheckMyOrderLock)
	ON_BN_CLICKED(IDC_CHECK_OTHER_ORDER_LOCK, OnBnClickedCheckOtherOrderLock)
	ON_BN_CLICKED(IDC_CHECK_TIMELIMIT, OnBnClickedCheckTimelimit)
	ON_BN_CLICKED(IDC_CHECK_INSURANCE, OnBnClickedCheckInsurance)
	ON_BN_CLICKED(IDC_ALL_CHK, OnBnClickedCheckAll)
	
	
	ON_BN_CLICKED(IDC_CHECK_SERVICESTOP, OnBnClickedCheckServicestop)
	ON_BN_CLICKED(IDC_RADIO_JOBSTOP, OnBnClickedRadioJobstop)
	ON_BN_CLICKED(IDC_RADIO_LOCKTIME_APPLY, OnBnClickedRadioLocktimeApply)
	ON_BN_CLICKED(IDC_RADIO_MY_ORDER_LOCKTIME_APPLY, OnBnClickedRadioMyOrderLocktimeApply)
	ON_BN_CLICKED(IDC_RADIO_OTHER_ORDER_LOCKTIME_APPLY, OnBnClickedRadioOtherOrderLocktimeApply)
	ON_BN_CLICKED(IDC_RADIO_ALLOCATE_APPLY, OnBnClickedRadioAllocateApply)
	ON_BN_CLICKED(IDC_RADIO_INSURANCE_APPLY, OnBnClickedRadioInsuranceApply)
	ON_BN_CLICKED(IDC_RADIO_ALLOCATE_NOAPPLY, OnBnClickedRadioAllocateNoapply)
	ON_BN_CLICKED(IDC_RADIO_INSURANCE_NOAPPLY, OnBnClickedRadioInsuranceNoapply)
	ON_BN_CLICKED(IDC_RADIO_LOCKTIME_NOAPPLY, OnBnClickedRadioLocktimeNoapply)
	ON_BN_CLICKED(IDC_RADIO_MY_ORDER_LOCKTIME_NOAPPLY, OnBnClickedRadioMyOrderLocktimeNoapply)
	ON_BN_CLICKED(IDC_RADIO_OTHER_ORDER_LOCKTIME_NOAPPLY, OnBnClickedRadioOtherOrderLocktimeNoapply)
	ON_BN_CLICKED(IDC_RADIO_JOBING, OnBnClickedRadioJobing)
	ON_BN_CLICKED(IDC_RADIO_SMS_APPLY, OnBnClickedRadioSmsApply)
	ON_BN_CLICKED(IDC_RADIO_SMS_NOAPPLY, OnBnClickedRadioSmsNoapply)
	ON_BN_CLICKED(IDC_RADIO_SELECT_APPLY, OnBnClickedRadioSelectApply)
	ON_BN_CLICKED(IDC_RADIO_ALL_APPLY, OnBnClickedRadioAllApply)
	
	ON_BN_CLICKED(IDC_RADIO_SERVICE_RENT_LIMIT_APPLY, OnBnClickedRadioServiceRentLimitApply)
	ON_BN_CLICKED(IDC_RADIO_SERVICE_RENT_NOAPPLY, OnBnClickedRadioServiceRentNoapply)
	ON_BN_CLICKED(IDC_CHECK_SERVICE_RENT_LIMIT, OnBnClickedCheckServiceRentLimit)
	ON_NOTIFY(HDN_ITEMCLICK, 0, OnHdnItemclickList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)
	
	ON_BN_CLICKED(IDC_TIME_LIMIT_CHECK, OnBnClickedTimeLimitCheck)
	ON_BN_CLICKED(IDC_CHECK_SHARE_LIMIT, OnBnClickedCheckShareLimit)

	ON_BN_CLICKED(IDC_AUTO_CHK, OnBnClickedAutoChk)
	ON_BN_CLICKED(IDC_BIG_AUTO_CHK1, OnBnClickedBigAutoChk)
	ON_BN_CLICKED(IDC_DAMA_CHK, OnBnClickedDamaChk)
	ON_BN_CLICKED(IDC_RABO_CHK, OnBnClickedRaboChk)
	ON_BN_CLICKED(IDC_BAN_CHK, OnBnClickedBanChk)
	ON_BN_CLICKED(IDC_TRUCK_CHK, OnBnClickedTruckChk)
END_MESSAGE_MAP()


// CAllocateLimitAllApplyDlg 메시지 처리기입니다.


void CAllocateLimitAllApplyDlg::InitList(void)
{
	int nItem = 1;
	
	m_ListCtrl.InsertColumn(nItem, "사번", LVCFMT_LEFT,  55);

	if(LF->GetCurBranchInfo()->bIntegrated)
        m_ListCtrl.InsertColumn(nItem++, "소속", LVCFMT_LEFT,  40);

	m_ListCtrl.InsertColumn(nItem++, "아이디", LVCFMT_LEFT, 80);
	m_ListCtrl.InsertColumn(nItem++, "이름", LVCFMT_LEFT, 90);
	m_ListCtrl.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_dtpJobStart.SetFormat("tth:mm");
	m_dtpJobEnd.SetFormat("tth:mm");

	m_dtJobStart.SetTime(7,0,0);
	m_dtJobEnd.SetTime(17,0,0);
	m_dtpJobStop.SetFormat("yyyy-MM-dd");
	m_dtpJobStopTime.SetFormat("tth:mm");
	m_dtpAllocateDate.SetFormat("yyyy-MM-dd");
	m_dtpAllocateTime.SetFormat("tth:mm");
	
	
	//((CButton*)GetDlgItem(IDC_RADIO_ALL_APPLY))->SetCheck(1);

	CWaitCursor wait;
	char buffer[20];
	int nCurSel = 0;

	UpdateData(TRUE);
	m_ListCtrl.DeleteAllItems();	

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_driver_limit_1");

	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_ci.m_bRcpIntMode1 ?	MAKE_SHARE_CODE(m_ci.m_nShareCode1) : -1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int),
			m_ci.m_bRcpIntMode2 ?	MAKE_SHARE_CODE(m_ci.m_nShareCode2) : -1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_ci.m_bRcpIntMode3 ?	MAKE_SHARE_CODE(m_ci.m_nShareCode3) : -1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_ci.m_bRcpIntMode4 ?	MAKE_SHARE_CODE(m_ci.m_nShareCode4) : -1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_ci.m_bRcpIntMode5 ?	MAKE_SHARE_CODE(m_ci.m_nShareCode5) : -1);
		
	if(!pRs.Execute(&pCmd)) return;

	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		//m_pkey = new KEYDATA;
		long nMno,lCode; nMno = lCode = 0;
		CString sID, sName;  
		int nWorkState;	
		nWorkState = 0;		
		
			
		int nSubItem = 1;

		pRs.GetFieldValue("lCode", lCode);
		pRs.GetFieldValue("sID", sID);
		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("nMno", nMno);				
		pRs.GetFieldValue("nWorkState", nWorkState);		

		m_ListCtrl.InsertItem(i, ltoa(nMno, buffer, 10));
 
		if(LF->GetCurBranchInfo()->bIntegrated)
			m_ListCtrl.SetItemText(i, nSubItem++, m_ci.GetName(lCode));		
		m_ListCtrl.SetItemText(i, nSubItem++, sID);
		m_ListCtrl.SetItemText(i, nSubItem++, sName);
		m_ListCtrl.SetItemData(i,lCode);

		if(m_map.find(std::make_pair(lCode, nMno)) != m_map.end())
			m_ListCtrl.SetCheck(i, TRUE);
	
/*
		if(!nWorkState) {
			COLOR_STRUCT *pCS = new COLOR_STRUCT;
			pCS->crBk = RGB(255,255,255);
			pCS->crText = RGB(0,0,0);
			m_ListCtrl.SetItemData(i, (DWORD_PTR)pCS);
		}

		else if(nWorkState != 0) {
			COLOR_STRUCT *pCS = new COLOR_STRUCT;
			pCS->crBk = RGB(255,200,200);
			pCS->crText = RGB(0,0,0);
			m_ListCtrl.SetItemData(i, (DWORD_PTR)pCS);
		}		
*/		

		pRs.MoveNext();
	}

	pRs.Close();

}
BOOL CAllocateLimitAllApplyDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();

	InitList();	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAllocateLimitAllApplyDlg::OnBnClickedIdok()
{

	UpdateData();
	
	if(CheckData()== FALSE)
		return;
	else if(this->m_chkAllocate.GetCheck() == 0 &&
		this->m_chkInsurance.GetCheck() == 0 &&
		this->m_chkJobStop.GetCheck() == 0 &&
		this->m_chkJobTime.GetCheck() == 0 &&
		this->m_chkLock.GetCheck() == 0 &&
		this->m_chkServiceRentLimit.GetCheck() == 0 &&
		this->m_chkSms.GetCheck() == 0 &&
		this->m_TimeLimitChk.GetCheck() == 0 &&
		this->m_chkShareLimit.GetCheck() == 0 &&
		this->m_chkOrder.GetCheck() == 0 &&
		this->m_chkMyOrderLock.GetCheck() == 0 &&
		this->m_chkOtherOrderLock.GetCheck() == 0)
			MessageBox("선택적용을 한개라도 해주세요","확인",MB_ICONINFORMATION);
	else
	{

		if(m_rdoSelectApply.GetCheck())
            SelectModifyProcess();
		else
			ModifyProcess();
	}
	UpdateData(FALSE);
	
	OnOK();
}



void CAllocateLimitAllApplyDlg::OnBnClickedCheckApplySms()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	if(m_chkSms.GetCheck() == BST_CHECKED )
	{
		m_rdoSmsApply.EnableWindow(1);
		GetDlgItem(IDC_RADIO_SMS_NOAPPLY)->EnableWindow(1);
	}
	else
	{
		m_rdoSmsApply.EnableWindow(0);
		GetDlgItem(IDC_RADIO_SMS_NOAPPLY)->EnableWindow(0);
	}
}

void CAllocateLimitAllApplyDlg::OnBnClickedCheckWorktime()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_chkJobTime.GetCheck() == BST_CHECKED)
	{
		m_dtpJobStart.EnableWindow(1);
		m_dtpJobEnd.EnableWindow(1);		
	}
	else
	{
		m_dtpJobStart.EnableWindow(0);
		m_dtpJobEnd.EnableWindow(0);
	}
}

void CAllocateLimitAllApplyDlg::OnBnClickedAutoChk()
{
	CheckAll();
}

void CAllocateLimitAllApplyDlg::OnBnClickedBigAutoChk()
{
	CheckAll();
}

void CAllocateLimitAllApplyDlg::OnBnClickedDamaChk()
{
	CheckAll();
}

void CAllocateLimitAllApplyDlg::OnBnClickedRaboChk()
{
	CheckAll();
}

void CAllocateLimitAllApplyDlg::OnBnClickedBanChk()
{
	CheckAll();
}

void CAllocateLimitAllApplyDlg::OnBnClickedTruckChk()
{
	CheckAll();
}

void CAllocateLimitAllApplyDlg::OnBnClickedCheckAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL bCheck = m_chkAll.GetCheck();

	m_chkAuto.SetCheck(bCheck);
	m_chkBigAuto.SetCheck(bCheck);
	m_chkDama.SetCheck(bCheck);
	m_chkRabo.SetCheck(bCheck);
	m_chkBan.SetCheck(bCheck);
	m_chkTruck.SetCheck(bCheck);
}

void CAllocateLimitAllApplyDlg::CheckAll()
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


void CAllocateLimitAllApplyDlg::OnBnClickedCheckOrder()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_chkOrder.GetCheck() == BST_CHECKED)
	{
		m_chkAuto.EnableWindow(1);
		m_chkBigAuto.EnableWindow(1);
		m_chkDama.EnableWindow(1);
		m_chkRabo.EnableWindow(1);
		m_chkBan.EnableWindow(1);
		m_chkTruck.EnableWindow(1);
		m_chkAll.EnableWindow(1);
	}
	else
	{
		m_chkAuto.SetCheck(0);
		m_chkBigAuto.SetCheck(0);
		m_chkDama.SetCheck(0);
		m_chkRabo.SetCheck(0);
		m_chkBan.SetCheck(0);
		m_chkTruck.SetCheck(0);
		m_chkAll.SetCheck(0);

		m_chkAuto.EnableWindow(0);
		m_chkBigAuto.EnableWindow(0);
		m_chkDama.EnableWindow(0);
		m_chkRabo.EnableWindow(0);
		m_chkBan.EnableWindow(0);
		m_chkTruck.EnableWindow(0);
		m_chkAll.EnableWindow(0);
	}
}

void CAllocateLimitAllApplyDlg::OnBnClickedCheckLock()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_chkLock.GetCheck() == BST_CHECKED)
	{
		m_rdoLockApply.EnableWindow(1);
		GetDlgItem(IDC_RADIO_LOCKTIME_NOAPPLY)->EnableWindow(1);
		//m_cmbLockTime.EnableWindow(1);
		//m_cmbLockCount.EnableWindow(1);
	}
	else
	{
		m_rdoLockApply.EnableWindow(0);
		GetDlgItem(IDC_RADIO_LOCKTIME_NOAPPLY)->EnableWindow(0);
		m_cmbLockTime.EnableWindow(0);
		m_cmbLockCount.EnableWindow(0);

		m_rdoLockApply.SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO_LOCKTIME_NOAPPLY))->SetCheck(0);
	}
}

void CAllocateLimitAllApplyDlg::OnBnClickedCheckMyOrderLock()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_chkMyOrderLock.GetCheck() == BST_CHECKED)
	{
		m_rdoMyOrderLockApply.EnableWindow(1);
		GetDlgItem(IDC_RADIO_MY_ORDER_LOCKTIME_NOAPPLY)->EnableWindow(1);
		//m_cmbLockTime.EnableWindow(1);
		//m_cmbLockCount.EnableWindow(1);
	}
	else
	{
		m_rdoMyOrderLockApply.EnableWindow(0);
		GetDlgItem(IDC_RADIO_MY_ORDER_LOCKTIME_NOAPPLY)->EnableWindow(0);
		m_cmbMyOrderLockTime.EnableWindow(0);
		m_cmbMyOrderLockCount.EnableWindow(0);

		m_rdoMyOrderLockApply.SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO_MY_ORDER_LOCKTIME_NOAPPLY))->SetCheck(0);
	}
}

void CAllocateLimitAllApplyDlg::OnBnClickedCheckOtherOrderLock()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_chkOtherOrderLock.GetCheck() == BST_CHECKED)
	{
		m_rdoOtherOrderLockApply.EnableWindow(1);
		GetDlgItem(IDC_RADIO_OTHER_ORDER_LOCKTIME_NOAPPLY)->EnableWindow(1);
		//m_cmbLockTime.EnableWindow(1);
		//m_cmbLockCount.EnableWindow(1);
	}
	else
	{
		m_rdoOtherOrderLockApply.EnableWindow(0);
		GetDlgItem(IDC_RADIO_OTHER_ORDER_LOCKTIME_NOAPPLY)->EnableWindow(0);
		m_cmbOtherOrderLockTime.EnableWindow(0);
		m_cmbOtherOrderLockCount.EnableWindow(0);

		m_rdoOtherOrderLockApply.SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO_OTHER_ORDER_LOCKTIME_NOAPPLY))->SetCheck(0);
	}
}

void CAllocateLimitAllApplyDlg::OnBnClickedCheckTimelimit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_chkAllocate.GetCheck() == BST_CHECKED)
	{
		m_rdoAllocateApply.EnableWindow(1);
		GetDlgItem(IDC_RADIO_ALLOCATE_NOAPPLY)->EnableWindow(1);		
		
	}
	else
	{
		m_rdoAllocateApply.EnableWindow(0);
		GetDlgItem(IDC_RADIO_ALLOCATE_NOAPPLY)->EnableWindow(0);

		m_dtpAllocateDate.EnableWindow(0);
		m_dtpAllocateTime.EnableWindow(0);
		m_cmbReleaseMin.EnableWindow(0);

		m_rdoAllocateApply.SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO_ALLOCATE_NOAPPLY))->SetCheck(0);
	}

}

void CAllocateLimitAllApplyDlg::OnBnClickedCheckServiceRentLimit()
{
	if(m_chkServiceRentLimit.GetCheck() == BST_CHECKED)
	{
		m_rdoServiceRentLimit.EnableWindow(1);
		GetDlgItem(IDC_RADIO_SERVICE_RENT_NOAPPLY)->EnableWindow(1);
	}
	else
	{
		m_rdoServiceRentLimit.EnableWindow(0);
		GetDlgItem(IDC_RADIO_SERVICE_RENT_NOAPPLY)->EnableWindow(0);

		m_rdoServiceRentLimit.SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO_SERVICE_RENT_NOAPPLY))->SetCheck(0);

	}
}

void CAllocateLimitAllApplyDlg::OnBnClickedCheckInsurance()
{
	if(m_chkInsurance.GetCheck() == BST_CHECKED)
	{
		m_rdoInsuranceApply.EnableWindow(1);
		GetDlgItem(IDC_RADIO_INSURANCE_NOAPPLY)->EnableWindow(1);
	}
	else
	{
		m_rdoInsuranceApply.EnableWindow(0);
		GetDlgItem(IDC_RADIO_INSURANCE_NOAPPLY)->EnableWindow(0);	

		m_dtpInsuranceStart.EnableWindow(0);
		m_dtpInsuranceEnd.EnableWindow(0);
		m_edtInsuranceCompany.EnableWindow(0);
		m_edtInsuranceID.EnableWindow(0);

		m_rdoInsuranceApply.SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO_INSURANCE_NOAPPLY))->SetCheck(0);
	}
}

void CAllocateLimitAllApplyDlg::OnBnClickedIdcancel()
{
	OnCancel();
}


void CAllocateLimitAllApplyDlg::OnBnClickedCheckServicestop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_chkJobStop.GetCheck() == BST_CHECKED)
	{
		m_rdoJobStopApply.EnableWindow(1);
		GetDlgItem(IDC_RADIO_JOBING)->EnableWindow(1);	
		m_cmbWorkStopMemo.EnableWindow(1);
	}
	else
	{
		m_rdoJobStopApply.EnableWindow(0);
		GetDlgItem(IDC_RADIO_JOBING)->EnableWindow(0);
		m_dtpJobStop.EnableWindow(0);
		m_dtpJobStopTime.EnableWindow(0);

		m_rdoJobStopApply.SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO_JOBING))->SetCheck(0);
		m_cmbWorkStopMemo.EnableWindow(0);
	
	}

}
void CAllocateLimitAllApplyDlg::OnBnClickedRadioJobstop()
{
	
	if(m_rdoJobStopApply.GetCheck())
	{
		m_dtpJobStop.EnableWindow(1);
		m_nJobStop = 1;
		m_dtpJobStopTime.EnableWindow(1);
		m_cmbWorkStopMemo.EnableWindow(1);
		
	}
	else
	{
		m_dtpJobStop.EnableWindow(0);
		m_nJobStop = 2;
		m_dtpJobStopTime.EnableWindow(0);
		m_cmbWorkStopMemo.EnableWindow(0);
	}


}

void CAllocateLimitAllApplyDlg::OnBnClickedRadioLocktimeApply()
{
	if(m_rdoLockApply.GetCheck())
	{
		m_nLockTime = 1;
		m_cmbLockCount.EnableWindow(1);
		m_cmbLockTime.EnableWindow(1);
	}
	else
	{
		m_nLockTime = 2;
		m_cmbLockCount.EnableWindow(0);
		m_cmbLockTime.EnableWindow(0);
	}
}

void CAllocateLimitAllApplyDlg::OnBnClickedRadioMyOrderLocktimeApply()
{
	if(m_rdoMyOrderLockApply.GetCheck())
	{
		m_nMyOrderLockTime = 1;
		m_cmbMyOrderLockCount.EnableWindow(1);
		m_cmbMyOrderLockTime.EnableWindow(1);
	}
	else
	{
		m_nMyOrderLockTime = 2;
		m_cmbMyOrderLockCount.EnableWindow(0);
		m_cmbMyOrderLockTime.EnableWindow(0);
	}
}

void CAllocateLimitAllApplyDlg::OnBnClickedRadioOtherOrderLocktimeApply()
{
	if(m_rdoOtherOrderLockApply.GetCheck())
	{
		m_nOtherOrderLockTime = 1;
		m_cmbOtherOrderLockCount.EnableWindow(1);
		m_cmbOtherOrderLockTime.EnableWindow(1);
	}
	else
	{
		m_nOtherOrderLockTime = 2;
		m_cmbOtherOrderLockCount.EnableWindow(0);
		m_cmbOtherOrderLockTime.EnableWindow(0);
	}
}

void CAllocateLimitAllApplyDlg::OnBnClickedRadioAllocateApply()
{
	if(m_rdoAllocateApply.GetCheck())
	{
		m_nAllocate = 1;
		m_dtpAllocateDate.EnableWindow(1);
		m_dtpAllocateTime.EnableWindow(1);
		m_cmbReleaseMin.EnableWindow(1);
	}
	else
	{
		m_nAllocate = 2;
		m_dtpAllocateDate.EnableWindow(0);
		m_dtpAllocateTime.EnableWindow(0);
		m_cmbReleaseMin.EnableWindow(0);
	}
}

void CAllocateLimitAllApplyDlg::OnBnClickedRadioInsuranceApply()
{
	if(m_rdoInsuranceApply.GetCheck())
	{
		m_nInsurance = 1;
		m_dtpInsuranceStart.EnableWindow(1);
		m_dtpInsuranceEnd.EnableWindow(1);
		m_edtInsuranceCompany.EnableWindow(1);
		m_edtInsuranceID.EnableWindow(1);
	}
	else
	{
		m_nInsurance = 2;
		m_dtpInsuranceStart.EnableWindow(0);
		m_dtpInsuranceEnd.EnableWindow(0);
		m_edtInsuranceCompany.EnableWindow(0);
		m_edtInsuranceID.EnableWindow(0);
	}
}

void CAllocateLimitAllApplyDlg::OnBnClickedRadioAllocateNoapply()
{
	m_dtpAllocateDate.EnableWindow(0);
	m_dtpAllocateTime.EnableWindow(0);
	m_cmbReleaseMin.EnableWindow(0);
	m_nAllocate =2;
}

void CAllocateLimitAllApplyDlg::OnBnClickedRadioInsuranceNoapply()
{
	m_dtpInsuranceStart.EnableWindow(0);
	m_dtpInsuranceEnd.EnableWindow(0);
	m_edtInsuranceCompany.EnableWindow(0);
	m_edtInsuranceID.EnableWindow(0);
	m_nInsurance = 2;
}

void CAllocateLimitAllApplyDlg::OnBnClickedRadioServiceRentLimitApply()
{
	m_nServiceRentLimit = 1;
}

void CAllocateLimitAllApplyDlg::OnBnClickedRadioServiceRentNoapply()
{
	m_nServiceRentLimit = 2;
}

void CAllocateLimitAllApplyDlg::OnBnClickedRadioLocktimeNoapply()
{
	m_cmbLockCount.EnableWindow(0);
	m_cmbLockTime.EnableWindow(0);
	m_nLockTime = 2;
}

void CAllocateLimitAllApplyDlg::OnBnClickedRadioMyOrderLocktimeNoapply()
{
	m_cmbMyOrderLockCount.EnableWindow(0);
	m_cmbMyOrderLockTime.EnableWindow(0);
	m_nMyOrderLockTime = 2;
}

void CAllocateLimitAllApplyDlg::OnBnClickedRadioOtherOrderLocktimeNoapply()
{
	m_cmbOtherOrderLockCount.EnableWindow(0);
	m_cmbOtherOrderLockTime.EnableWindow(0);
	m_nOtherOrderLockTime = 2;
}

void CAllocateLimitAllApplyDlg::OnBnClickedRadioJobing()
{
	m_dtpJobStop.EnableWindow(0);
	m_dtpJobStopTime.EnableWindow(0);
	m_nJobStop = 2;
	m_cmbWorkStopMemo.EnableWindow(0);
}

bool CAllocateLimitAllApplyDlg::CheckData(void)
{
	try{

		if(m_rdoSelectApply.GetCheck())
		{
			int nChkListNum = 0;
			for(int i=0; i< m_ListCtrl.GetItemCount(); i++)
			{
				if(m_ListCtrl.GetCheck(i))
					nChkListNum++;
			}
			if(nChkListNum == 0)
				throw "기사 리스트에 체크된 값이 없습니다.\n\n "\
				"전체적용을 체크하시면 전체직원에 적용됩니다";
		}

		if(m_chkShareLimit.GetCheck() == BST_CHECKED)
		{
			if(m_cmbShareLimit.GetCurSel() == -1)
				throw "공유제한 항목을 선택하세요";
		}

		if(m_chkLock.GetCheck() == BST_CHECKED && 
			m_rdoLockApply.GetCheck()==BST_CHECKED)
		{
			if(m_sLockCount == "" || m_sLockTime == "" ||
				m_sLockCount == "0" || m_sLockTime == "0" ) 
				throw "배차제한 항목에 값이 빠져있습니다";			
		}

		if(m_chkMyOrderLock.GetCheck() == BST_CHECKED && 
			m_rdoMyOrderLockApply.GetCheck()==BST_CHECKED)
		{
			if(m_sMyOrderLockCount == "" || m_sMyOrderLockTime == "" ||
				m_sMyOrderLockCount == "0" || m_sMyOrderLockTime == "0" ) 
				throw "자사오더 배차제한 항목에 값이 빠져있습니다";			
		}

		if(m_chkOtherOrderLock.GetCheck() == BST_CHECKED && 
			m_rdoOtherOrderLockApply.GetCheck()==BST_CHECKED)
		{
			if(m_sOtherOrderLockCount == "" || m_sOtherOrderLockTime == "" ||
				m_sOtherOrderLockCount == "0" || m_sOtherOrderLockTime == "0" ) 
				throw "타사오더 배차제한 항목에 값이 빠져있습니다";			
		}

		if(m_chkOrder.GetCheck() == BST_CHECKED && 
			(m_chkAuto.GetCheck() == FALSE && m_chkBigAuto.GetCheck() == FALSE &&
			m_chkDama.GetCheck() == FALSE && m_chkRabo.GetCheck() == FALSE &&
			m_chkBan.GetCheck() == FALSE && m_chkTruck.GetCheck() == FALSE))
			throw "오더 노출 항목을 하나 이상 선택하세요.";		

		if(m_chkAllocate.GetCheck())
		{
			if(m_rdoAllocateApply.GetCheck() == BST_UNCHECKED && 
				((CButton*)GetDlgItem(IDC_RADIO_ALLOCATE_NOAPPLY))->GetCheck() == BST_UNCHECKED)
				throw "시간제한 항목에 둘중하나를 선택해주세요";			
		}
		
		if(m_chkAllocate.GetCheck() == BST_CHECKED && 
			m_rdoAllocateApply.GetCheck() == BST_CHECKED)
		{

			COleDateTime dtDateTime;
			COleDateTimeSpan dtSpan,dtSpanTime;
			
			dtDateTime.SetDate(
				m_dtAllocateDate.GetYear(),
				m_dtAllocateDate.GetMonth(),
				m_dtAllocateDate.GetDay());

			dtSpanTime.SetDateTimeSpan(0,m_dtAllocateTime.GetHour(),
				m_dtAllocateTime.GetMinute(),m_dtAllocateTime.GetMinute());
			dtDateTime += dtSpanTime;
			dtSpan.SetDateTimeSpan(0,0,atoi(m_sReleaseMin),0);		

			dtDateTime += dtSpan;

			if(dtDateTime < COleDateTime::GetCurrentTime())
				throw "시간제한 세팅한 값이 현재시간보다 이전입니다."\
					"시간 세팅을 다시 해주세요";			
		}

		if(m_chkInsurance.GetCheck() == BST_CHECKED && 
			m_rdoInsuranceApply.GetCheck() ==BST_CHECKED)
		{
			if(m_sInsuranceCompany == "" || m_sInsuranceID == "")
				throw "보험관련 항목에 값이 빠져있습니다.";
							
			if(m_dtInsuranceStart >= m_dtInsuranceEnd  )
				throw "보험종료일이 보험시작일 보다 같거나 작습니다.";			
		}

		if(m_chkSms.GetCheck() == 1 && m_nSms == 0)
			throw "SMS 체크를 선택해주세요.";
			
		if(m_chkServiceRentLimit.GetCheck() == 1 && m_nServiceRentLimit == 0)
			throw "서비스 사용료 미납 체크를 선택해주세요.";
			
		if(m_chkJobStop.GetCheck() == 1 && m_nJobStop  == 0)
			throw "업무중지 체크를 선택해주세요.";
		
		if(m_chkLock.GetCheck() == 1 && m_nLockTime == 0)
			throw "배차제한 체크를 선택해주세요.";

		if(m_chkMyOrderLock.GetCheck() == 1 && m_nMyOrderLockTime == 0)
			throw "자사오더 배차제한 체크를 선택해주세요.";

		if(m_chkOtherOrderLock.GetCheck() == 1 && m_nOtherOrderLockTime == 0)
			throw "타사오더 배차제한 체크를 선택해주세요.";
			
		if(m_chkAllocate.GetCheck() == 1 && m_nAllocate  == 0)
			throw "시간제한 체크를 선택해주세요.";
			
		if(m_chkInsurance.GetCheck() == 1 && m_nInsurance == 0)
			throw "보험적용 체크를 선택해주세요.";			
	}
	catch(char *msg)
	{
		MessageBox(msg,"확인",MB_ICONINFORMATION);
		return FALSE;
	}
	
	return TRUE;	
}


void CAllocateLimitAllApplyDlg::SelectModifyProcess(void)
{
	UpdateData();

	CWaitCursor wait;
	for(int i = 0; i< m_ListCtrl.GetItemCount(); i++)
	{
		if(m_ListCtrl.GetCheck(i) )
		{
				
			COleDateTime dtInitDate = COleDateTime(2004,1,1,0,0,0);
			COleDateTime dtJobStart, dtJobEnd; dtJobStart= dtJobEnd = dtInitDate;
			
			CMkCommand pCmd(m_pMkDb, "update_allocate_limit_rider_4");
			
			COleDateTimeSpan oSpan;		
			
			pCmd.AddParameter(typeLong,  typeInput, sizeof(long),(long)m_ListCtrl.GetItemData(i));
			pCmd.AddParameter(typeInt,  typeInput, sizeof(int),atoi(m_ListCtrl.GetItemText(i,0)) );
			
			
			if(m_chkJobTime.GetCheck() == BST_CHECKED)
			{
				pCmd.AddParameter(typeInt ,typeInput,sizeof(int),1);	
				
				oSpan.SetDateTimeSpan(0,m_dtJobStart.GetHour(),m_dtJobStart.GetMinute(),m_dtJobStart.GetSecond());
				dtJobStart += oSpan;	
				pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime),dtJobStart);
				
				oSpan.SetDateTimeSpan(0,m_dtJobEnd.GetHour(),m_dtJobEnd.GetMinute(),m_dtJobEnd.GetSecond() );
				dtJobEnd += oSpan;
				pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime),dtJobEnd);	

			}
			else
			{
				pCmd.AddParameter(typeInt ,typeInput,sizeof(int),2);	
				pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime),dtInitDate);
				pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime),dtInitDate);	
				
			}
			
			if(m_chkJobStop.GetCheck()== BST_CHECKED && m_rdoJobStopApply.GetCheck())
			{
				pCmd.AddParameter(typeInt , typeInput, sizeof(int), 1 );
				
				COleDateTime dtJobStopDate,dtJobStopTime;
				COleDateTimeSpan dtSpanTime;

				dtJobStopDate.SetDate(m_dtJobStop.GetYear(),m_dtJobStop.GetMonth(),m_dtJobStop.GetDay());

				dtSpanTime.SetDateTimeSpan(0,m_dtJobStopTime.GetHour(),m_dtJobStopTime.GetMinute(),0);

				dtJobStopDate += dtSpanTime;

				pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtJobStopDate);	
				
			}
			else if(m_chkJobStop.GetCheck() == BST_CHECKED && ((CButton*)GetDlgItem(IDC_RADIO_JOBING))->GetCheck())
			{
				pCmd.AddParameter(typeInt , typeInput, sizeof(int), 0 );
				pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtInitDate);			
			}
			else
			{
				pCmd.AddParameter(typeInt , typeInput, sizeof(int), 2 );
				pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtInitDate);			
			}

			
			if(m_chkLock.GetCheck() == BST_CHECKED && m_nLockTime == 1 )
			{
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 1);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), atoi(m_sLockTime));
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 
					(m_sLockCount == "무제한")? 100: atoi(m_sLockCount) );
			}
			else if(m_chkLock.GetCheck() == BST_CHECKED && m_nLockTime == 2 )
			{
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 100);
			}
			else
			{
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 2);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
			}

			if(m_chkAllocate.GetCheck() == BST_CHECKED && m_nAllocate == 1  )
			{
				pCmd.AddParameter(typeInt , typeInput, sizeof(int),1);
				
				COleDateTime dtAllocateDateTime(m_dtAllocateDate.GetYear(),
					m_dtAllocateDate.GetMonth(),m_dtAllocateDate.GetDay(),
					m_dtAllocateTime.GetHour(),m_dtAllocateTime.GetMinute(),
					m_dtAllocateTime.GetSecond());

				pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime),dtAllocateDateTime);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), atoi(m_sReleaseMin));
			}
			else if(m_chkAllocate.GetCheck() == BST_CHECKED && m_nAllocate == 2 )
			{
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), 0);					
				pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtInitDate);		
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
			}
			else
			{
				pCmd.AddParameter(typeInt, typeInput, sizeof(int),2);	
				pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtInitDate);				
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
			}

			if(m_chkSms.GetCheck() == BST_CHECKED && 
				m_rdoSmsApply.GetCheck()== BST_CHECKED )
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), 1);					
			else if(m_chkSms.GetCheck() == BST_CHECKED && 
				m_rdoSmsApply.GetCheck()== BST_UNCHECKED )
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), 0);				
			else
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), 2);	
		
			if(m_chkServiceRentLimit.GetCheck() == BST_CHECKED && 
				m_rdoServiceRentLimit.GetCheck() == BST_CHECKED )
			
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), 1);		
			else if(m_chkServiceRentLimit.GetCheck() == BST_CHECKED && 
				m_rdoServiceRentLimit.GetCheck()== BST_UNCHECKED )
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), 0);				
			else
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), 2);		
			

			if(m_chkInsurance.GetCheck() == BST_CHECKED && m_nInsurance == 1 )
			{
				COleDateTime dtStart,dtEnd;
				dtStart.SetDateTime(m_dtInsuranceStart.GetYear(),m_dtInsuranceStart.GetMonth(),
				m_dtInsuranceStart.GetDay(),0,0,0);
				dtEnd.SetDateTime(m_dtInsuranceEnd.GetYear(), m_dtInsuranceEnd.GetMonth(),
				m_dtInsuranceEnd.GetDay(),11,59,0);

				pCmd.AddParameter(typeInt, typeInput, sizeof(int), 1);
				pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtStart);			
				pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtEnd);		
				CString strInsuranceID = "";
				strInsuranceID =  m_sInsuranceCompany + "/" + m_sInsuranceID;
				pCmd.AddParameter(typeString,typeInput, strInsuranceID.GetLength(), strInsuranceID);
			}
			else if(m_chkInsurance.GetCheck() == BST_CHECKED && m_nInsurance == 2 )
			{
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), 0);
				pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtInitDate);
				pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtInitDate);		
				pCmd.AddParameter(typeString,typeInput, 1, "/");
			}
			else
			{
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), 2);
				pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtInitDate);
				pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtInitDate);		
				pCmd.AddParameter(typeString,typeInput, 0, "");

			}		

			if(m_TimeLimitChk.GetCheck() == TRUE)
			{ 
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), 2);
				CString str;
				//m_ElapseLimitAllocateLocalCmb.GetLBText(max(m_ElapseLimitAllocateLocalCmb.GetCurSel(),0), str);
				m_ElapseLimitAllocateLocalCmb.GetWindowText(str);
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), _ttoi(str));
				//m_ElapseLimitAllocateGlobalCmb.GetLBText(max(m_ElapseLimitAllocateGlobalCmb.GetCurSel(), 0), str);
				m_ElapseLimitAllocateGlobalCmb.GetWindowText(str);
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), _ttoi(str));
				//m_ElapseLimitPickupLocalCmb.GetLBText(max(m_ElapseLimitPickupLocalCmb.GetCurSel(), 0), str);
				m_ElapseLimitPickupLocalCmb.GetWindowText(str);
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), _ttoi(str));
				//m_ElapseLimitPickupGlobalCmb.GetLBText(max(m_ElapseLimitPickupGlobalCmb.GetCurSel(), 0), str);
				m_ElapseLimitPickupGlobalCmb.GetWindowText(str);
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), _ttoi(str));
			}
			else
			{
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), 0);
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), 0);
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), 0);
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), 0);
				pCmd.AddParameter(typeInt, typeInput, sizeof(int), 0);
			}

			if(m_chkShareLimit.GetCheck() == TRUE)
			{
				pCmd.AddParameter(2);
				pCmd.AddParameter(m_cmbShareLimit.GetCurSel());
			}
			else
			{
				pCmd.AddParameter(0);
				pCmd.AddParameter(0);
			}

			if(m_chkMyOrderLock.GetCheck() == BST_CHECKED && m_nMyOrderLockTime == 1 )
			{
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 1);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), atoi(m_sMyOrderLockTime));
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 
					(m_sMyOrderLockCount == "무제한")? 100: atoi(m_sMyOrderLockCount) );
			}
			else if(m_chkMyOrderLock.GetCheck() == BST_CHECKED && m_nMyOrderLockTime == 2 )
			{
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 100);
			}
			else
			{
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 2);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
			}

			if(m_chkOtherOrderLock.GetCheck() == BST_CHECKED && m_nOtherOrderLockTime == 1 )
			{
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 1);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), atoi(m_sOtherOrderLockTime));
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 
					(m_sOtherOrderLockCount == "무제한")? 100: atoi(m_sOtherOrderLockCount) );
			}
			else if(m_chkOtherOrderLock.GetCheck() == BST_CHECKED && m_nOtherOrderLockTime == 2 )
			{
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 100);
			}
			else
			{
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 2);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
			}

			if(m_chkOrder.GetCheck() == BST_CHECKED)
			{
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), m_chkOrder.GetCheck());
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), m_chkAuto.GetCheck());
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), m_chkBigAuto.GetCheck());
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), m_chkDama.GetCheck());
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), m_chkRabo.GetCheck());
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), m_chkBan.GetCheck());
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int), m_chkTruck.GetCheck());
			}
			else
			{
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int),0);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int),0);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int),0);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int),0);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int),0);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int),0);
				pCmd.AddParameter(typeInt,  typeInput, sizeof(int),0);
			}

			pCmd.Execute();

		}
	}

	UpdateData(false);
	
}

bool CAllocateLimitAllApplyDlg::ModifyProcess(void)
{
	UpdateData();			
	
	CWaitCursor wait;
	COleDateTime dtInitDate = COleDateTime(2004,1,1,0,0,0);
	COleDateTime dtJobStart, dtJobEnd; dtJobStart= dtJobEnd = dtInitDate;
	
	CMkCommand pCmd(m_pMkDb, "update_allocate_limit_all_rider_4");
	
	COleDateTimeSpan oSpan;
	
	//pCmd.AddParameter(typeLong,  typeInput, sizeof(int),((CStaffPage12*)m_pParentWnd)->m_nCompanyCode);
	//pCmd.AddParameter(typeLong,  typeInput, sizeof(int),((CStaffPage12*)m_pParentWnd)->m_bIntegrated);

	pCmd.AddParameter(typeLong,  typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong,  typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
	
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_ci.m_bRcpIntMode1 ? MAKE_SHARE_CODE((m_ci.m_nShareCode1)) : -1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int),
			m_ci.m_bRcpIntMode2 ? MAKE_SHARE_CODE((m_ci.m_nShareCode2)) : -1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_ci.m_bRcpIntMode3 ? MAKE_SHARE_CODE((m_ci.m_nShareCode3)) : -1);

	if(m_chkJobTime.GetCheck() == BST_CHECKED)
	{
		pCmd.AddParameter(typeInt ,typeInput,sizeof(int),1);	
		
		oSpan.SetDateTimeSpan(0,m_dtJobStart.GetHour(),m_dtJobStart.GetMinute(),m_dtJobStart.GetSecond());
		dtJobStart += oSpan;	
		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime),dtJobStart);
		
		oSpan.SetDateTimeSpan(0,m_dtJobEnd.GetHour(),m_dtJobEnd.GetMinute(),m_dtJobEnd.GetSecond() );
		dtJobEnd += oSpan;
		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime),dtJobEnd);	

	}
	else
	{
		pCmd.AddParameter(typeInt ,typeInput,sizeof(int),2);	
		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime),dtInitDate);
		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime),dtInitDate);	
		
	}
	
	if(m_chkJobStop.GetCheck()== BST_CHECKED && m_rdoJobStopApply.GetCheck())
	{
		pCmd.AddParameter(typeInt , typeInput, sizeof(int), 1 );

		COleDateTime dtJobStopDate,dtJobStopTime;
		COleDateTimeSpan dtSpanTime;

		dtJobStopDate.SetDate(m_dtJobStop.GetYear(),m_dtJobStop.GetMonth(),m_dtJobStop.GetDay());

		dtSpanTime.SetDateTimeSpan(0,m_dtJobStopTime.GetHour(),m_dtJobStopTime.GetMinute(),0);

		dtJobStopDate += dtSpanTime;

		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtJobStopDate);	

	}
	else if(m_chkJobStop.GetCheck() == BST_CHECKED && ((CButton*)GetDlgItem(IDC_RADIO_JOBING))->GetCheck())
	{
		pCmd.AddParameter(typeInt , typeInput, sizeof(int), 0 );
		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtInitDate);			
	}
	else
	{
		pCmd.AddParameter(typeInt , typeInput, sizeof(int), 2 );
		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtInitDate);			
	}


	
	if(m_chkLock.GetCheck() == BST_CHECKED && m_nLockTime == 1 )
	{
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 1);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), atoi(m_sLockTime));
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 
			(m_sLockCount == "무제한")? 100: atoi(m_sLockCount) );
	}
	else if(m_chkLock.GetCheck() == BST_CHECKED && m_nLockTime == 2 )
	{
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 100);
	}
	else
	{
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 2);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
	}

	if(m_chkAllocate.GetCheck() == BST_CHECKED && m_nAllocate == 1  )
	{
		pCmd.AddParameter(typeInt , typeInput, sizeof(int),1);
		
		COleDateTime dtAllocateDateTime(m_dtAllocateDate.GetYear(),m_dtAllocateDate.GetMonth(),m_dtAllocateDate.GetDay(),
		m_dtAllocateTime.GetHour(),m_dtAllocateTime.GetMinute(),m_dtAllocateTime.GetSecond());
		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime),dtAllocateDateTime);

        pCmd.AddParameter(typeInt,  typeInput, sizeof(int), atoi(m_sReleaseMin));
	}
	else if(m_chkAllocate.GetCheck() == BST_CHECKED && m_nAllocate == 2 )
	{
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), 0);	
		
		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtInitDate);		
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
	}
	else
	{
		pCmd.AddParameter(typeInt, typeInput, sizeof(int),2);	
		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtInitDate);
		
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
	}

	if(m_chkSms.GetCheck() == BST_CHECKED && m_rdoSmsApply.GetCheck()== BST_CHECKED )
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), 1);			
	
	else if(m_chkSms.GetCheck() == BST_CHECKED && m_rdoSmsApply.GetCheck()== BST_UNCHECKED )
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), 0);			
	else
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), 2);		

	if(m_chkServiceRentLimit.GetCheck() == BST_CHECKED && m_rdoServiceRentLimit.GetCheck() == BST_CHECKED )
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), 1);		
	else if(m_chkServiceRentLimit.GetCheck() == BST_CHECKED && m_rdoServiceRentLimit.GetCheck()== BST_UNCHECKED )
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), 0);			
	else
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), 2);			
	

	if(m_chkInsurance.GetCheck() == BST_CHECKED && m_nInsurance == 1 )
	{
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), 1);

		COleDateTime dtStart, dtEnd;

		dtStart.SetDateTime(m_dtInsuranceStart.GetYear(),m_dtInsuranceStart.GetMonth(),
			m_dtInsuranceStart.GetDay(),0,0,0);
		dtEnd.SetDateTime(m_dtInsuranceEnd.GetYear(), m_dtInsuranceEnd.GetMonth(),
			m_dtInsuranceEnd.GetDay(),11,59,0);
		
		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtStart);		
		
		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtEnd);		
		CString strInsuranceID = "";
		strInsuranceID =  m_sInsuranceCompany + "/" + m_sInsuranceID;
		pCmd.AddParameter(typeString,typeInput, strInsuranceID.GetLength(), strInsuranceID);
	}
	else if(m_chkInsurance.GetCheck() == BST_CHECKED && m_nInsurance == 2 )
	{
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), 0);
		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtInitDate);
		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtInitDate);		
		pCmd.AddParameter(typeString,typeInput, 1, "/");
	}
	else
	{
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), 2);
		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtInitDate);
		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtInitDate);		
		pCmd.AddParameter(typeString,typeInput, 0, "");
	}	

	if(m_TimeLimitChk.GetCheck() == TRUE)
	{
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), 2);
		CString str;
		m_ElapseLimitAllocateLocalCmb.GetWindowText(str);
		//m_ElapseLimitAllocateLocalCmb.GetLBText(max(m_ElapseLimitAllocateLocalCmb.GetCurSel(), 0), str);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), _ttoi(str));
		//m_ElapseLimitAllocateGlobalCmb.GetLBText(max(m_ElapseLimitAllocateGlobalCmb.GetCurSel(), 0), str);
		m_ElapseLimitAllocateGlobalCmb.GetWindowText(str);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), _ttoi(str));
		//m_ElapseLimitPickupLocalCmb.GetLBText(max(m_ElapseLimitPickupLocalCmb.GetCurSel(), 0), str);
		m_ElapseLimitPickupLocalCmb.GetWindowText(str);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), _ttoi(str));
		//m_ElapseLimitPickupGlobalCmb.GetLBText(max(m_ElapseLimitPickupGlobalCmb.GetCurSel(), 0), str);
		m_ElapseLimitPickupGlobalCmb.GetWindowText(str);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), _ttoi(str));
	}
	else
	{
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), 0);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), 0);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), 0);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), 0);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), 0);
	}

	if(m_chkShareLimit.GetCheck() == TRUE)
	{
		pCmd.AddParameter(2);
		pCmd.AddParameter(m_cmbShareLimit.GetCurSel());
	}
	else
	{
		pCmd.AddParameter(0);
		pCmd.AddParameter(0);
	}

	if(m_chkMyOrderLock.GetCheck() == BST_CHECKED && m_nMyOrderLockTime == 1 )
	{
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 1);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), atoi(m_sMyOrderLockTime));
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 
			(m_sMyOrderLockCount == "무제한")? 100: atoi(m_sMyOrderLockCount) );
	}
	else if(m_chkMyOrderLock.GetCheck() == BST_CHECKED && m_nMyOrderLockTime == 2 )
	{
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 100);
	}
	else
	{
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 2);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
	}

	if(m_chkOtherOrderLock.GetCheck() == BST_CHECKED && m_nOtherOrderLockTime == 1 )
	{
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 1);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), atoi(m_sOtherOrderLockTime));
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 
			(m_sOtherOrderLockCount == "무제한")? 100: atoi(m_sOtherOrderLockCount) );
	}
	else if(m_chkOtherOrderLock.GetCheck() == BST_CHECKED && m_nOtherOrderLockTime == 2 )
	{
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 100);
	}
	else
	{
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 2);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), 0);
	}

	if(m_chkOrder.GetCheck() == BST_CHECKED)
	{
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), m_chkOrder.GetCheck());
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), m_chkAuto.GetCheck());
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), m_chkBigAuto.GetCheck());
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), m_chkDama.GetCheck());
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), m_chkRabo.GetCheck());
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), m_chkBan.GetCheck());
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int), m_chkTruck.GetCheck());
	}
	else
	{
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int),0);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int),0);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int),0);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int),0);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int),0);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int),0);
		pCmd.AddParameter(typeInt,  typeInput, sizeof(int),0);
	}


	pCmd.Execute();
	UpdateData(false);

	return true;
	
}

void CAllocateLimitAllApplyDlg::OnBnClickedRadioSmsApply()
{
	m_nSms = 1;
}

void CAllocateLimitAllApplyDlg::OnBnClickedRadioSmsNoapply()
{	
	m_nSms = 2;
}

void CAllocateLimitAllApplyDlg::OnBnClickedRadioSelectApply()
{
	if(m_rdoSelectApply.GetCheck())
		m_ListCtrl.EnableWindow(TRUE);	
}

void CAllocateLimitAllApplyDlg::OnBnClickedRadioAllApply()
{
	if(((CButton*)GetDlgItem(IDC_RADIO_ALL_APPLY))->GetCheck())
		m_ListCtrl.EnableWindow(FALSE);	
}

void CAllocateLimitAllApplyDlg::OnHdnItemclickList(NMHDR *pNMHDR, LRESULT *pResult)
{	
	UpdateData();
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	//if(pNMListView->>uNewState & LVIS_SELECTED) {
		int nItem = pNMListView->iItem;
		m_ListCtrl.SetCheck(nItem,1);
	//	m_nSelectedCNo = m_CustomerList.GetItemData(nItem);
		UpdateData(FALSE);
	*pResult = 0;
}

void CAllocateLimitAllApplyDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	//if(pNMListView->>uNewState & LVIS_SELECTED) {
		int nItem = pNMListView->iItem;
		//m_ListCtrl.SetCheck(nItem,1);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CAllocateLimitAllApplyDlg::OnBnClickedTimeLimitCheck()
{
	if(m_TimeLimitChk.GetCheck() == TRUE)
	{
		m_ElapseLimitAllocateLocalCmb.EnableWindow(TRUE);
		m_ElapseLimitAllocateGlobalCmb.EnableWindow(TRUE);
		m_ElapseLimitPickupLocalCmb.EnableWindow(TRUE);
		m_ElapseLimitPickupGlobalCmb.EnableWindow(TRUE);
	}
	else
	{
		m_ElapseLimitAllocateLocalCmb.EnableWindow(FALSE);
		m_ElapseLimitAllocateGlobalCmb.EnableWindow(FALSE);
		m_ElapseLimitPickupLocalCmb.EnableWindow(FALSE);
		m_ElapseLimitPickupGlobalCmb.EnableWindow(FALSE);
	}
}

void CAllocateLimitAllApplyDlg::OnBnClickedCheckShareLimit()
{
	if(m_chkShareLimit.GetCheck() == BST_CHECKED)
	{
		m_cmbShareLimit.EnableWindow(TRUE);
		m_cmbShareLimit.SetCurSel(0);
	}
	else
	{
		m_cmbShareLimit.EnableWindow(FALSE);
		m_cmbShareLimit.SetCurSel(-1);
	}
}
