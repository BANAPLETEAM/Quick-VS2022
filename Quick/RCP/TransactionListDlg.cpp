// TransactionListDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TransactionListDlg.h"
#include "quick.h"
#include "CertificationRegiDlg.h"

// CTransactionListDlg 대화 상자입니다.

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


// CTransactionListDlg 메시지 처리기입니다.

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
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.

}

void CTransactionListDlg::OnBnClickedTaxDrawBtn()
{
	if(MessageBox("계산서 발행및 기사에게 입금을 하시겠습니까? ", "확인", MB_YESNO) ==IDNO)
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
		MessageBox("종료되지 않은 오더가 있습니다. 확인하세요", "확인", MB_ICONINFORMATION);
		return;
	}
	else if(nReturn == 200)
	{
		MessageBox("오더중 일부처리가 되지않은 오더가있습니다.. 확인하세요", "확인", MB_ICONINFORMATION);
		return;
	}
	else if(nReturn == 10)
	{
		MessageBox("성공적으로 발행됬습니다.", "확인", MB_ICONINFORMATION);

		if(m_chkPrint.GetCheck())
		{

			// 프린트 작업
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
		CoInitialize(NULL);  // 이부분 빠지면  에러남 
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
		MessageBox(szMsg,"확인", MB_ICONINFORMATION);
		return;
	}

}

void CTransactionListDlg::BillDraw()
{
	UpdateData();

	try
	{
		int nSum = 0;
		CoInitialize(NULL);  // 이부분 빠지면  에러남
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
		MessageBox(szMsg,"확인", MB_ICONINFORMATION);
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