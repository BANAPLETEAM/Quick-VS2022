// TransactionListDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TransactionListDlg.h"
#include "quick.h"
#include "CertificationRegiDlg.h"

// CTransactionListDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTransactionListDlg, CMyDialog)

CTransactionListDlg::CTransactionListDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CTransactionListDlg::IDD, pParent)
{

	m_nBillID = 0;
	m_sTNoList = "";
	m_nCorporationID = 0;
	m_nType = 0;
	m_bBillView = 0;
	m_nCompany = 0;
}

CTransactionListDlg::~CTransactionListDlg()
{
}

void CTransactionListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER, m_Explorer);
	DDX_Control(pDX, IDC_PRINT_CHECK, m_chkPrint);
	DDX_Control(pDX, IDC_TAX_DRAW_BTN, m_btnTaxDraw);
	
	
}


BEGIN_MESSAGE_MAP(CTransactionListDlg, CMyDialog)
	ON_BN_CLICKED(IDC_TAX_DRAW_BTN, OnBnClickedTaxDrawBtn)
	ON_BN_CLICKED(IDC_CANCEL, OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_CERTIFICATION_REGISTER_BTN, OnBnClickedCertificationRegisterBtn)

	
	
	
END_MESSAGE_MAP()


// CTransactionListDlg �޽��� ó�����Դϴ�.

BOOL CTransactionListDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();


	if(m_nType == 0) 
		BillDraw();		
	else
		TransactionList();
		

	if(m_bBillView ) 
	{
		m_btnTaxDraw.EnableWindow(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.

}

void CTransactionListDlg::OnBnClickedTaxDrawBtn()
{
	if(MessageBox("��꼭 ����� ��翡�� �Ա��� �Ͻðڽ��ϱ�? ", "Ȯ��", MB_YESNO) ==IDNO)
		return;
	
	int nReturn = 0;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "insert_bill_draw");
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long), ZERO);
	pCmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(m_sTNoList);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.nWNo);	
	pRs.Execute(&pCmd);

	pPar->GetValue(nReturn);
	if(nReturn == 100)
	{
		MessageBox("������� ���� ������ �ֽ��ϴ�. Ȯ���ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}
	else if(nReturn == 200)
	{
		MessageBox("������ �Ϻ�ó���� �������� �������ֽ��ϴ�.. Ȯ���ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}
	else if(nReturn == 10)
	{
		MessageBox("���������� ��������ϴ�.", "Ȯ��", MB_ICONINFORMATION);

		if(m_chkPrint.GetCheck())
		{

			// ����Ʈ �۾�
		}
	}
	OnOK();
	

}

void CTransactionListDlg::OnBnClickedCancelBtn()
{
	OnCancel();


}



void CTransactionListDlg::OnBnClickedCertificationRegisterBtn()
{
	CREATE_MODALESS(CCertificationRegiDlg, this);
	pDlg->m_bIntegrated = m_ba.GetCount() > 1 ? TRUE :FALSE;
	pDlg->m_nCompany = LF->GetCurBranchInfo()->nCompanyCode;
	SHOW_MODALESS(CCertificationRegiDlg, this);
}

void CTransactionListDlg::TransactionList()
{
	UpdateData();

	try
	{
		int nSum = 0;
		CoInitialize(NULL);  // �̺κ� ������  ������ 
		HRESULT hr;
		BSTR bstrURL = NULL, bstrHeaders = NULL;
		VARIANT vFlags = {0},vTargetFrameName = {0},vPostData = {0},vHeaders = {0};
		CString strUrl = "http://quick3.logisoft.co.kr/Calcu/transaction.asp";
		//_variant_t vtUrl(strUrl.AllocSysString());

		bstrHeaders = SysAllocString(L"Content-Type: application/x-www-form-urlencoded\r\n");
		V_VT(&vHeaders) = VT_BSTR;
		V_BSTR(&vHeaders) = bstrHeaders;
		CString strForm, strPostInfo;		

		nSum = m_ci.m_bRcpIntMode1+ m_ci.m_bRcpIntMode2 + m_ci.m_bRcpIntMode3 + m_ci.m_bRcpIntMode4 + m_ci.m_bRcpIntMode5;		


		strForm.Format("id_name=%s&sPWD=%s&sWName=%s&nWCompany=%ld&bIntegrated=%s&nSessionKey=%ld&sIP=%s&sTNoList=%s&nCompany=%ld",
			m_ui.strID, m_ui.strPW,m_ui.strName, m_nCompany, nSum,
			m_ui.nSiteSessionKey, m_ei.strExternalIP, 	m_sTNoList, LF->GetCurBranchInfo()->nCompanyCode );


		hr = GetPostData(strForm,&vPostData);	
		m_Explorer.Navigate((LPCTSTR)strUrl,&vFlags,&vTargetFrameName,&vPostData,&vHeaders);

		CoUninitialize();
		
	}
	catch(char *szMsg)
	{
		MessageBox(szMsg,"Ȯ��", MB_ICONINFORMATION);
		return;
	}

}

void CTransactionListDlg::BillDraw()
{
	UpdateData();

	try
	{
		int nSum = 0;
		CoInitialize(NULL);  // �̺κ� ������  ������
		HRESULT hr;
		BSTR bstrURL = NULL, bstrHeaders = NULL;
		VARIANT vFlags = {0},vTargetFrameName = {0},vPostData = {0},vHeaders = {0};
		CString strUrl = "http://quick3.logisoft.co.kr/Calcu/Bill.asp";
		//_variant_t vtUrl(strUrl.AllocSysString());

		bstrHeaders = SysAllocString(L"Content-Type: application/x-www-form-urlencoded\r\n");
		V_VT(&vHeaders) = VT_BSTR;
		V_BSTR(&vHeaders) = bstrHeaders;
		CString strForm, strPostInfo;		

		nSum = m_ci.m_bRcpIntMode1+ m_ci.m_bRcpIntMode2 + m_ci.m_bRcpIntMode3 + m_ci.m_bRcpIntMode4 + m_ci.m_bRcpIntMode5;		
		strForm.Format("id_name=%s&sPWD=%s&sWName=%s&nWCompany=%ld&bIntegrated=%d&nSessionKey=%ld&sIP=%s&sTNoList=%s&nCompany=%ld",
			m_ui.strID, m_ui.strPW,m_ui.strName, m_ci.m_nCompanyCode, nSum,
			m_ui.nSiteSessionKey, m_ei.strExternalIP, 	m_sTNoList, m_nCompany );

		hr = GetPostData(strForm,&vPostData);	
		m_Explorer.Navigate((LPCTSTR)strUrl,&vFlags,&vTargetFrameName,&vPostData,&vHeaders);
		CoUninitialize();
	}
	catch(char *szMsg)
	{
		MessageBox(szMsg,"Ȯ��", MB_ICONINFORMATION);
		return;
	}
		
}


HRESULT CTransactionListDlg::GetPostData(CString strKey, LPVARIANT pvPostData)
{
	HRESULT hr;
	LPSAFEARRAY psa;

	//	LPCTSTR cszPostData = "id=mania&Flavor=Mocha+Chip";

	//m_CtrlID.GetWindowText(m_strUserID);
	//m_CtrlPassWord.GetWindowText(m_strPassWord);


	CString PostInfo= strKey;
	LPCTSTR cszPostData = (LPCTSTR)PostInfo;
	UINT cElems = lstrlen(cszPostData);
	LPSTR pPostData;

	if (!pvPostData)
	{
		return E_POINTER;
	}

	VariantInit(pvPostData);

	psa = SafeArrayCreateVector(VT_UI1, 0, cElems);
	if (!psa)
	{
		return E_OUTOFMEMORY;
	}

	hr = SafeArrayAccessData(psa, (LPVOID*)&pPostData);
	memcpy(pPostData, cszPostData, cElems);
	hr = SafeArrayUnaccessData(psa);

	V_VT(pvPostData) = VT_ARRAY | VT_UI1;
	V_ARRAY(pvPostData) = psa;
	return NOERROR;
}