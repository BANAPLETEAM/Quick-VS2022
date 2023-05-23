// LoadInsuranceDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "LoadInsuranceDlg.h"
#include "LoadInsurance.h"
#include "LoadInsuranceAgreeDlg.h"

// CLoadInsuranceDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CLoadInsuranceDlg, CMyDialog)

CLoadInsuranceDlg::CLoadInsuranceDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CLoadInsuranceDlg::IDD, pParent)
{

}

CLoadInsuranceDlg::~CLoadInsuranceDlg()
{
}

void CLoadInsuranceDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMPANY_NAME_EDIT, m_edtCompanyName);
	DDX_Control(pDX, IDC_RNO_EDIT, m_edtRNo);
	DDX_Control(pDX, IDC_NAME_EDIT, m_edtName);
	DDX_Control(pDX, IDC_SSN_EDIT, m_edtSSN);
	DDX_Control(pDX, IDC_SID_EDIT, m_edtSID);
	DDX_Control(pDX, IDC_INSURANCE_START_EDIT, m_edtInsuranceStart);
	DDX_Control(pDX, IDC_INSURANCE_COMPANY_EDIT, m_edtInsuranceCompany);
	DDX_Control(pDX, IDC_CAR_NUMBER_EDIT, m_edtCarNumber);
	DDX_Control(pDX, IDC_MONTHLY_PREMIUM_EDIT, m_edtMonthlyPremium);
	DDX_Control(pDX, IDC_DAILY_PREMIUM_EDIT, m_edtDailyPremium);
	DDX_Control(pDX, IDC_INSURANCE_ID_EDIT, m_edtInsuranceID);
	DDX_Control(pDX, IDC_CAR_TYPE_COMBO, m_cmbCarType);
	DDX_Control(pDX, IDC_HELP_STATIC, m_stcHelp);
}


BEGIN_MESSAGE_MAP(CLoadInsuranceDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &CLoadInsuranceDlg::OnBnClickedSaveButton)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, &CLoadInsuranceDlg::OnBnClickedCloseButton)
	ON_BN_CLICKED(IDC_RELEASE_BUTTON, &CLoadInsuranceDlg::OnBnClickedReleaseButton)
	ON_BN_CLICKED(IDC_CLAUSE_BUTTON, &CLoadInsuranceDlg::OnBnClickedClauseButton)
END_MESSAGE_MAP()


// CLoadInsuranceDlg 메시지 처리기입니다.

BOOL CLoadInsuranceDlg::RiderInsInfo(CLoadInsuranceData *st, BOOL bInsert)
{
	m_edtCompanyName.GetWindowText(st->strCompanyName);
	st->nRNo = m_nRNo;
	m_edtSSN.GetWindowText(st->strSSN);
	st->strSSN = m_strSSN;
	st->strSSN.Replace("-", "");
	m_edtSID.GetWindowText(st->strPhone);
	st->strPhone.Replace("-", "");
	m_edtCarNumber.GetWindowText(st->strCarNo);
	m_edtName.GetWindowText(st->strRiderName);
	st->nRiderCompany = m_nCompany;

	if(m_cmbCarType.GetCurSel() == 0) st->nCarType = LOAD_INS_CAR_TYPE_BIKE;
	else if(m_cmbCarType.GetCurSel() == 1) st->nCarType = LOAD_INS_CAR_TYPE_CAR;
	else st->nCarType = LOAD_INS_CAR_TYPE_SUBWAY;
	
	if(!LU->IsSSNOk(st->strSSN) && bInsert == TRUE)
	{
		MessageBox("주민번호가 유효하지 않습니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	return TRUE;
}

void CLoadInsuranceDlg::OnBnClickedSaveButton()
{
	CLoadInsuranceData st;

	if(!RiderInsInfo(&st, TRUE))
		return;

	CLoadInsurance d(LOAD_INS_INSERT, &st, "사용자수정");

	if(d.Open())
	{
		RefreshDlg(&st);
		MessageBox("등록되었습니다.", "확인", MB_ICONINFORMATION);
	}
	else
	{
		MessageBox(st.strErrorMsg, "확인", MB_ICONINFORMATION);
	}
}

BOOL CLoadInsuranceDlg::IsLoadInsuranceRegister(CString strSSN, CLoadInsuranceData *st)
{
	CLoadInsurance d(LOAD_INS_SEARCH, st, "조회");
	return d.Open();
}

void CLoadInsuranceDlg::RefreshDlg(CLoadInsuranceData *st)
{
	m_edtCompanyName.SetWindowText(st->strCompanyName);
	m_edtRNo.SetWindowText(LF->GetStringFromLong(st->nRNo));

	if(st->strSSN.GetLength() == 13)
		m_edtSSN.SetWindowText(st->strSSN.Left(6) + "-" + st->strSSN.Right(7));
	else
		m_edtSSN.SetWindowText(st->strSSN);

	m_edtCarNumber.SetWindowText(st->strCarNo);
	m_edtName.SetWindowText(st->strRiderName);
	m_edtSID.SetWindowText(st->strPhone);
	m_edtInsuranceCompany.SetWindowText(st->strInsuranceCompany);
	m_edtInsuranceID.SetWindowText(st->rogiCerti);
	m_edtInsuranceStart.SetWindowText(st->strStartDate);

	if(st->nWorkState == LOAD_INS_WORK_STATE_NORMAL)
	{
		COleDateTime dt = COleDateTime::GetCurrentTime();
		CString strTemp = dt.Format("%Y-%m-%d");

		if(st->strStartDate == strTemp)
			m_stcHelp.SetWindowText("보험이 정상적으로 등록되어 있지만, 금일 24시 이후로 보험이 적용됩니다,");
		else
			m_stcHelp.SetWindowText("보험이 정상적으로 등록되어 있습니다.");
	}	
	else
		m_stcHelp.SetWindowText("보험이 정상적으로 등록되어 있지만, 금일 24시 이후로 보험이 적용되지 않습니다.");
}

void CLoadInsuranceDlg::GetLoadInsurancePremiun(long nCarType)
{
	CMkCommand cmd(m_pMkDb, "select_load_insurance_premium");
	cmd.AddParameter(nCarType);
	CMkParameter *pParDay = cmd.AddParameter(typeLong,typeOutput, sizeof(long), 0);
	CMkParameter *pParMonth = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);	

	if(!cmd.Execute())
		return;

	long nDay; pParDay->GetValue(nDay);
	long nMonth; pParMonth->GetValue(nMonth);

	m_edtDailyPremium.SetWindowText(LF->GetMyNumberFormat(nDay));
	m_edtMonthlyPremium.SetWindowText(LF->GetMyNumberFormat(nMonth)); 
}

BOOL CLoadInsuranceDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	long nTempCarType = 0;

	if(m_nCarType == CAR_AUTO || m_nCarType == CAR_BIGBIKE)
		nTempCarType = LOAD_INS_CAR_TYPE_BIKE; 
	else if(m_nCarType == CAR_SUBWAY)
		nTempCarType = LOAD_INS_CAR_TYPE_SUBWAY;
	else
		nTempCarType = LOAD_INS_CAR_TYPE_CAR;

	CLoadInsuranceData st;
	st.strSSN = m_strSSN;
	st.strSSN.Replace("-", "");

	//등록여부 조회

	if(IsLoadInsuranceRegister(m_strSSN, &st)) //등록일경우 안에서 상태변경함
	{
		RefreshDlg(&st);
		nTempCarType = st.nCarType;		
	}
	else
	{
		m_edtCompanyName.SetWindowText(m_ci.GetShareCompanyName(m_nCompany));
		m_edtRNo.SetWindowText(LF->GetStringFromLong(m_nRNo));
		m_edtSSN.SetWindowText(m_strSSN);
		m_edtCarNumber.SetWindowText(m_strCarNo);
		m_edtName.SetWindowText(m_strName);
		m_edtSID.SetWindowText(m_strSID);

		m_stcHelp.SetWindowText("적재물보험에 등록되어 있지 않습니다.");
	}

	if(nTempCarType == LOAD_INS_CAR_TYPE_BIKE) m_cmbCarType.SetCurSel(0);
	else if(nTempCarType == LOAD_INS_CAR_TYPE_CAR) m_cmbCarType.SetCurSel(1);
	else if(nTempCarType == LOAD_INS_CAR_TYPE_SUBWAY) m_cmbCarType.SetCurSel(2);

	GetLoadInsurancePremiun(nTempCarType);
	
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CLoadInsuranceDlg::OnBnClickedCloseButton()
{
	OnCancel();
}

void CLoadInsuranceDlg::OnBnClickedReleaseButton()
{
	CLoadInsuranceData st;

	if(!RiderInsInfo(&st))
		return;

	CLoadInsurance d(LOAD_INS_DELETE, &st, "사용자수정");

	if(d.Open())
	{
		if(IsLoadInsuranceRegister(m_strSSN, &st)) //등록일경우 안에서 상태변경함
		{
			RefreshDlg(&st);
			MessageBox("해지되었습니다. 당일 24시 이후로 보험적용이 되지 않습니다.", "확인", MB_ICONINFORMATION);
		}
		else
		{
			MessageBox("해지되었습니다", "확인", MB_ICONINFORMATION);
			m_stcHelp.SetWindowText("적재물보험에 등록되어 있지 않습니다.");
		}			
	}
	else
	{
		MessageBox(st.strErrorMsg, "확인", MB_ICONINFORMATION);
	}
}

void CLoadInsuranceDlg::OnBnClickedClauseButton()
{
	CLoadInsuranceAgreeDlg dlg;
	dlg.DoModal();
}
