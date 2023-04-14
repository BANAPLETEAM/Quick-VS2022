// CertificationRegiDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CertificationRegiDlg.h"


// CCertificationRegiDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCertificationRegiDlg, CMyDialog)

CCertificationRegiDlg::CCertificationRegiDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCertificationRegiDlg::IDD, pParent)
{
	m_bIntegrated = FALSE;
	m_nCompany  = 0;
}

CCertificationRegiDlg::~CCertificationRegiDlg()
{
}

void CCertificationRegiDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BUSINESS_NO_EDIT, m_sBusinessNO);
	DDX_Text(pDX, IDC_BUSINESS_NAME_EDIT, m_sBusinessName);
	DDX_Text(pDX, IDC_BUSINESS_PRESIDENT_EDIT, m_sBusinessPresident);
	DDX_Text(pDX, IDC_BUSINESS_ADDRESS_EDIT, m_sBusinessAddress);
	DDX_Text(pDX, IDC_BUSINESS__CONDITION_EDIT, m_sBusinessCondition);
	DDX_Text(pDX, IDC_BUSINESS_CATEGORY2_EDIT, m_sBusinessCategory);

	DDX_Text(pDX, IDC_BUSINESS_MANAGER_EDIT, m_sBusinessManager);
	DDX_Text(pDX, IDC_BUSINESS_EMAIL_EDIT, m_sBusinessEmail);
	DDX_Control(pDX, IDC_BILL_REGI_COMBO, m_cmbBillRegi);


	DDX_Control(pDX, IDC_ALL_BRANCH_CHECK, m_chkAllBranch);
	DDX_Control(pDX, IDC_COMBO1, m_cmbBranch);
}


BEGIN_MESSAGE_MAP(CCertificationRegiDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CERITFICATION_INSTALL_BTN, &CCertificationRegiDlg::OnBnClickedCeritficationInstallBtn)
	ON_BN_CLICKED(ID_MODIFY_BTN, &CCertificationRegiDlg::OnBnClickedModifyBtn)
	ON_BN_CLICKED(IDC_CERTIFICATION_REGISTER_BTN, &CCertificationRegiDlg::OnBnClickedCertificationRegisterBtn)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CCertificationRegiDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CCertificationRegiDlg 메시지 처리기입니다.

void CCertificationRegiDlg::OnBnClickedCeritficationInstallBtn()
{
	

	CString str, strForm;
	str = "C:\\Program Files\\Internet Explorer\\iexplore.exe";
	
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;

	//	if(!strArg.IsEmpty())

	strForm =" http://www.logisoft.co.kr/agentdownload.html";

	str += strForm;

	BOOL fSuccess = CreateProcess(NULL, (LPSTR)(LPCTSTR)str, NULL, NULL, 0, 
		CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);

	if(fSuccess) {
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);	


	}
}

void CCertificationRegiDlg::OnBnClickedModifyBtn()
{
	
	UpdateData();

	//long nIntegrationCode = ((CBranchInfo*)m_ba.GetAt(0))->nCompanyCode;
	long nCompany = 0;
	
	if(m_chkAllBranch.GetCheck())
		nCompany = m_cmbBranch.GetItemData(0) ;
	else
		nCompany = m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel() ) ;
	m_sBusinessNO.Replace("-","");
	BOOL bIntegrated = (m_cmbBranch.GetCount() > 1 && m_chkAllBranch.GetCheck() ) ?  TRUE : FALSE;
	
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_company_business_item3");
	pCmd.AddParameter(nCompany);
	pCmd.AddParameter( bIntegrated);

	pCmd.AddParameter(m_sBusinessNO);
	pCmd.AddParameter(m_sBusinessName); 
	pCmd.AddParameter(m_sBusinessPresident);
	pCmd.AddParameter(m_sBusinessAddress);
	pCmd.AddParameter(m_sBusinessCondition);
	pCmd.AddParameter(m_sBusinessCategory);
	pCmd.AddParameter(m_sBusinessManager);
	pCmd.AddParameter(m_sBusinessEmail);	
	pCmd.AddParameter(m_cmbBillRegi.GetCurSel());	
	pCmd.AddParameter(m_chkAllBranch.GetCheck());

	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	
	if(!pRs.Execute(&pCmd)) return;

	int nRegi = 0;
	pPar->GetValue(nRegi);
	if(nRegi == 0 && m_cmbBillRegi.GetCurSel())
		MessageBox("등록은 되어있으나 전자인증등록이 되어있지 않습니다.");
	else
		MessageBox("등록되었습니다.");




}

void CCertificationRegiDlg::LoadData()
{

	
	long nCompany = m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel());
	
	
	UpdateData();
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_corp_business_info2");
	pCmd.AddParameter(nCompany);
	
	if(!pRs.Execute(&pCmd)) return;

	int nLogiRegister = 0;
	pRs.GetFieldValue("sBusinessNo", m_sBusinessNO);
	pRs.GetFieldValue("sPresidentName", m_sBusinessPresident);
	pRs.GetFieldValue("sBusinessAddress", m_sBusinessAddress);
	pRs.GetFieldValue("sBusinessCondition", m_sBusinessCondition);
	pRs.GetFieldValue("sBusinessCategory", m_sBusinessCategory);
	pRs.GetFieldValue("sBusinessName", m_sBusinessName);

	pRs.GetFieldValue("sBusinessManager", m_sBusinessManager);
	pRs.GetFieldValue("sBusinessEmail", m_sBusinessEmail);
	pRs.GetFieldValue("nLogiRegister", nLogiRegister);
	
	m_cmbBillRegi.SetCurSel(nLogiRegister);
	
	pRs.Close();
	UpdateData(FALSE);

	

}
BOOL CCertificationRegiDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	int nCurSel = 0;
	if(m_bIntegrated)
	{
		for(int i = 0; i < m_ba.GetCount(); i++)
		{
			CBranchInfo	*pBi = m_ba.GetAt(i);
			m_cmbBranch.InsertString(i, pBi->strBranchName);
			m_cmbBranch.SetItemData(i, pBi->nCompanyCode);
			if(pBi->nCompanyCode == m_nCompany)
			{
				nCurSel = i;
			}

		}
		m_cmbBranch.SetCurSel(nCurSel);
	}
	else
	{
		
		CBranchInfo	*pBi = m_ba.GetAt(0);
		
		m_chkAllBranch.ShowWindow(SW_HIDE);
		m_cmbBranch.InsertString(0, pBi->strBranchName);
		m_cmbBranch.SetItemData(0, pBi->nCompanyCode);
		m_cmbBranch.SetCurSel(0);
	}
	

	LoadData();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCertificationRegiDlg::OnBnClickedCertificationRegisterBtn()
{
	UpdateData();

	if(m_sBusinessNO.GetLength() == 0)
	{
		MessageBox("사업자번호를 입력하세요 ", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_sBusinessName.GetLength() == 0)
	{
		MessageBox("법인명을 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CString str, strForm;
	str = "C:\\Program Files\\Internet Explorer\\iexplore.exe";
	
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;

	//	if(!strArg.IsEmpty())

	strForm.Format(" http://bill.logisoft.co.kr:10000/callSB/XXSB_DTI_CERT.asp?CERT_REGNO=%s&CERT_COMNAME=%s",
		m_sBusinessNO, m_sBusinessName);
		

	str += strForm;

	BOOL fSuccess = CreateProcess(NULL, (LPSTR)(LPCTSTR)str, NULL, NULL, 0, 
		CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);

	if(fSuccess) {
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);	
	}
}

void CCertificationRegiDlg::OnCbnSelchangeCombo1()
{
	
		LoadData();
}
