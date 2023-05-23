// ChargeForRiderDetailDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "ChargeForRiderDetailDlg.h"


// CChargeForRiderDetailDlg ��ȭ �����Դϴ�.

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


// CChargeForRiderDetailDlg �޽��� ó�����Դϴ�.


void CChargeForRiderDetailDlg::RefreshDlg()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_charge_for_ride_detail");
	cmd.AddParameter(m_nID);

	if(!rs.Execute(&cmd))
		return;

	if(rs.GetRecordCount() <= 0)
	{
		MessageBox("������ Ȯ�� �� �� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
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
	
	if(nTemp == 0) m_edtType.SetWindowText("��û��");
	else if(nTemp == 1) m_edtType.SetWindowText("��ü�Ϸ�");
	else if(nTemp == 2) m_edtType.SetWindowText("����");
	else if(nTemp == 3) m_edtType.SetWindowText("��û����");

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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CChargeForRiderDetailDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}
