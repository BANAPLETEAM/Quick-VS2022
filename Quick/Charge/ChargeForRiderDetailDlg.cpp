// ChargeForRiderDetailDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "ChargeForRiderDetailDlg.h"


// CChargeForRiderDetailDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChargeForRiderDetailDlg, CMyDialog)

CChargeForRiderDetailDlg::CChargeForRiderDetailDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChargeForRiderDetailDlg::IDD, pParent)
{
	m_nID = 0;
}

CChargeForRiderDetailDlg::~CChargeForRiderDetailDlg()
{
}

void CChargeForRiderDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMPANY_NAME_EDIT, m_edtCompanyName);
	DDX_Control(pDX, IDC_COMPANY_TEL_EDIT, m_edtCompanyTel);
	DDX_Control(pDX, IDC_WNAME_EDIT, m_edtWName);
	DDX_Control(pDX, IDC_TYPE_EDIT, m_edtType);
	DDX_Control(pDX, IDC_REQUEST_TIME_EDIT, m_edtRequestTime);
	DDX_Control(pDX, IDC_REQUEST_ETC_EDIT, m_edtRequestEtc);
	DDX_Control(pDX, IDC_RIDER_COMPANY_NAME_EDIT, m_edtRiderCompanyName);
	DDX_Control(pDX, IDC_RIDER_COMPANY_TEL_EDIT, m_edtRiderCompanyTel);
	DDX_Control(pDX, IDC_RNAME_EDIT, m_edtRName);
	DDX_Control(pDX, IDC_RESULT_TIME_EDIT, m_edtResultTime);
	DDX_Control(pDX, IDC_RESULT_WNAME_EDIT, m_edtResultWName);
	DDX_Control(pDX, IDC_RESULT_ETC_EDIT, m_edtResultEtc);
}


BEGIN_MESSAGE_MAP(CChargeForRiderDetailDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CChargeForRiderDetailDlg::OnBnClickedCloseBtn)
END_MESSAGE_MAP()


// CChargeForRiderDetailDlg 메시지 처리기입니다.


void CChargeForRiderDetailDlg::RefreshDlg()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_charge_for_ride_detail");
	cmd.AddParameter(m_nID);

	if(!rs.Execute(&cmd))
		return;

	if(rs.GetRecordCount() <= 0)
	{
		MessageBox("내역을 확일 할 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	long nTemp;
	CString strTemp;
	COleDateTime dtTemp;
	
	rs.GetFieldValue("nCompanyMainCode", nTemp);
	m_edtCompanyName.SetWindowText(m_ci.GetShareCompanyName(nTemp));
	m_edtCompanyTel.SetWindowText(m_ci.GetShareCompanyPhone(nTemp));
	rs.GetFieldValue("nWNo", nTemp);
	rs.GetFieldValue("sWName", strTemp);
	m_edtWName.SetWindowText(LF->GetStringFromLong(nTemp) + "/" + strTemp);
	rs.GetFieldValue("nType", nTemp);
	
	if(nTemp == 0) m_edtType.SetWindowText("요청중");
	else if(nTemp == 1) m_edtType.SetWindowText("이체완료");
	else if(nTemp == 2) m_edtType.SetWindowText("거절");
	else if(nTemp == 3) m_edtType.SetWindowText("요청중지");

	rs.GetFieldValue("dtRequest", dtTemp);
	m_edtRequestTime.SetWindowText(dtTemp.Format("%Y-%m-%d %H:%M:%S"));
	rs.GetFieldValue("sEtc", strTemp);
	m_edtRequestEtc.SetWindowText(strTemp);
	rs.GetFieldValue("nRiderMainCode", nTemp);
	m_edtRiderCompanyName.SetWindowText(m_ci.GetShareCompanyName(nTemp));
	m_edtRiderCompanyTel.SetWindowText(m_ci.GetShareCompanyPhone(nTemp));
	rs.GetFieldValue("nRNo", nTemp);
	rs.GetFieldValue("sRName", strTemp);
	m_edtRName.SetWindowText(LF->GetStringFromLong(nTemp) + "/" + strTemp);
	rs.GetFieldValue("dtResult", dtTemp);
	m_edtResultTime.SetWindowText(dtTemp.Format("%Y-%m-%d %H:%M:%S"));
	rs.GetFieldValue("nResultWNo", nTemp);
	rs.GetFieldValue("sResultWName", strTemp);
	m_edtResultWName.SetWindowText(LF->GetStringFromLong(nTemp) + "/" + strTemp);
	rs.GetFieldValue("sResultEtc", strTemp);
	m_edtResultEtc.SetWindowText(strTemp);
}

BOOL CChargeForRiderDetailDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	RefreshDlg();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CChargeForRiderDetailDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}
