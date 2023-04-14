// SMSDocViewDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SMSDocViewDlg.h"


// CSMSDocViewDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSMSDocViewDlg, CMyDialog)

CSMSDocViewDlg::CSMSDocViewDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CSMSDocViewDlg::IDD, pParent)
{
	m_strUrl = "";
}

CSMSDocViewDlg::~CSMSDocViewDlg()
{
}

void CSMSDocViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_Explorer);
}


BEGIN_MESSAGE_MAP(CSMSDocViewDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
	ON_BN_CLICKED(IDC_ZOOM_OUT_BTN, OnBnClickedZoomInBtn)
	ON_BN_CLICKED(IDC_ZOOM_IN_BTN, OnBnClickedZoomOutBtn)
END_MESSAGE_MAP()




BOOL CSMSDocViewDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	DocView();

	return TRUE;
}

void CSMSDocViewDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}



// CSMSDocViewDlg 메시지 처리기입니다.


void CSMSDocViewDlg::DocView()
{
	HRESULT hr;
	BSTR bstrURL = NULL, bstrHeaders = NULL;
	VARIANT vFlags = {0},vTargetFrameName = {0},vPostData = {0},vHeaders = {0};
	CString strUrl = m_strUrl; //"http://appweb.logisoft.co.kr:8000/default.asp";

	//InitControl();

	//_variant_t vtUrl(strUrl.AllocSysString());

	bstrHeaders = SysAllocString(L"Content-Type: application/x-www-form-urlencoded\r\n");
	V_VT(&vHeaders) = VT_BSTR;
	V_BSTR(&vHeaders) = bstrHeaders;

	CString strForm = "", strPostInfo = "";		
	/*strForm.Format("id_name=%s&sPWD=%s&strWName=%s&nWCompany=%ld&bIntegrated=%s&nSessionKey=%ld&sIP=%s&nIntroCompany=%d&nWriteMode=%d",
	UI()->strID, UI()->strPW,UI()->strName, CI()->GetCompanyCode(),CI()->GetRcpIntMode1() ? "1" : "0", 
	UI()->nSiteSessionKey, m_ei.strExternalIP, m_nID, 200);*/

	hr = GetPostData(strForm,&vPostData);	
	VARIANT vtTarget;

	CString str = "";

	vtTarget.bstrVal = str.AllocSysString();
	m_Explorer.Navigate((LPCTSTR)m_strUrl,&vFlags,&vtTarget,&vPostData,&vHeaders);
	//m_Explorer.Navigate((LPCTSTR)m_strUrl);


}

HRESULT CSMSDocViewDlg::GetPostData(CString strKey, LPVARIANT pvPostData)
{
	HRESULT hr;
	LPSAFEARRAY psa;
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


void CSMSDocViewDlg::OnBnClickedZoomInBtn()
{
	m_Explorer.SetFocus();
	m_Explorer.SetForegroundWindow();


	keybd_event(VK_CONTROL, 0x9d, 0, 0);          

	keybd_event(VkKeyScan('-'), 0x99, 0, 0);

	keybd_event(VkKeyScan('-'), 0x99, KEYEVENTF_KEYUP, 0);

	keybd_event(VK_CONTROL, 0x9d, KEYEVENTF_KEYUP, 0);



}
void CSMSDocViewDlg::OnBnClickedZoomOutBtn()
{
	m_Explorer.SetFocus();
	m_Explorer.SetForegroundWindow();

	keybd_event(VK_CONTROL, 0x9d, 0, 0);          

	keybd_event(VkKeyScan('='), 0x99, 0, 0);

	keybd_event(VkKeyScan('='), 0x99, KEYEVENTF_KEYUP, 0);

	keybd_event(VK_CONTROL, 0x9d, KEYEVENTF_KEYUP, 0);


}



BOOL CSMSDocViewDlg::PreTranslateMessage(MSG* pMsg)
{
	

	if(pMsg->message == WM_RBUTTONDOWN)
	{
		
			return TRUE;
	}
	


	return CMyDialog::PreTranslateMessage(pMsg);
}
