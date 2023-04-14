// Report4.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "HomeForm1.h"


// CHomeForm1 대화 상자입니다.



IMPLEMENT_DYNCREATE(CHomeForm1, CMyFormView)
CHomeForm1::CHomeForm1()
	: CMyFormView(CHomeForm1::IDD)
{
	 m_sBranchName = "";
	 m_sCompany= "";
}

CHomeForm1::~CHomeForm1()
{
}

void CHomeForm1::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER, m_Explorer);
	DDX_Control(pDX, IDC_REFRESH_BUTTON, m_RefeshBtn);
	DDX_Control(pDX, IDC_AFTER_BUTTON, m_ForwardBtn);
	DDX_Control(pDX, IDC_BACK_BUTTON, m_BackBtn);
	DDX_Control(pDX, IDC_TO_MAIN_BUTTON, m_btnChangeMainPage);
}


BEGIN_MESSAGE_MAP(CHomeForm1, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, OnBnClickedRefreshButton)
	ON_BN_CLICKED(IDC_AFTER_BUTTON, OnBnClickedAfterButton)
	ON_BN_CLICKED(IDC_BACK_BUTTON, OnBnClickedBackButton)
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_TO_MAIN_BUTTON, &CHomeForm1::OnBnClickedToMainButton)
END_MESSAGE_MAP()


// CHomeForm1 메시지 처리기입니다.



static unsigned int InitData(LPVOID dParameter)
{
	try
	{
		CString s;		
		CHomeForm1 *pWnd = NULL;
		pWnd = (CHomeForm1 *)dParameter;
		
		CoInitialize(NULL);  // 이부분 빠지면  에러남 

		HRESULT hr;
		BSTR bstrURL = NULL, bstrHeaders = NULL, bstrAddress = NULL;
		VARIANT vFlags = {0},vTargetFrameName = {0},vPostData = {0},vHeaders = {0}, vAddress = {0};
		CString strUrl = "http://appQuick2011.logisoft.co.kr:8000/default.asp";		
		bstrAddress = SysAllocString(strUrl.AllocSysString());
		V_VT(&vAddress) = VT_BSTR;
		V_BSTR(&vAddress) = bstrAddress;
		
		bstrHeaders = SysAllocString(L"Content-Type: application/x-www-form-urlencoded;charset=utf-8\r\n");
		V_VT(&vHeaders) = VT_BSTR;
		V_BSTR(&vHeaders) = bstrHeaders;


		CString strForm, strPostInfo,strBranchName = "", strCompany = "";		
		int nSum = 0;
		nSum = pWnd->GetSumIntegrated();
		CString strID = m_ui.strID, strName = m_ui.strName;
		
		strBranchName = pWnd->m_sBranchName;
		strCompany = pWnd->m_sCompany;
		strBranchName.Replace("&","＆");
		strCompany.Replace("&","＆");
		strID.Replace("&", "＆");
		strName.Replace("&", "＆");
		

		strForm.Format("sCompany=%s&sBranchName=%s&id_name=%s&sPWD=%s&sWName=%s&nWCompany=%ld&bIntegrated=%s&nSessionKey=%ld&sIP=%s&nLoginType=1",
			strCompany,strBranchName, strID, m_ui.strPW, strName, m_ci.m_nCompanyCode,nSum ? "1" : "0", 
			m_ui.nSiteSessionKey, m_ei.strExternalIP);

		hr = pWnd->GetPostData(strForm,&vPostData);	 
		
		
		if(pWnd)
			pWnd->m_Explorer.Navigate((LPCTSTR)strUrl,&vFlags,&vTargetFrameName,&vPostData,&vHeaders);
		
		CoUninitialize();

	}
	catch(char *szMsg)
	{
		AfxMessageBox(szMsg,MB_ICONINFORMATION);
		return 0;
	}

	return 0;

}


int CHomeForm1::GetSumIntegrated()
{
	int nSum = 0;
	nSum = m_ci.m_bRcpIntMode1 + m_ci.m_bRcpIntMode2 + m_ci.m_bRcpIntMode3 + m_ci.m_bRcpIntMode4 + m_ci.m_bRcpIntMode5;
		
	return nSum;
}

void CHomeForm1::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	UpdateData();
	

	SetResize(IDC_EXPLORER, sizingRightBottom);

	m_RefeshBtn.LoadBitmaps(IDB_WEB_REFRESH_1, IDB_WEB_REFRESH_2);
	m_ForwardBtn.LoadBitmaps(IDB_WEB_FORWARD_1, IDB_WEB_FORWARD_2);
	m_BackBtn.LoadBitmaps(IDB_WEB_BACK_1, IDB_WEB_BACK_2);

	m_RefeshBtn.SizeToContent();
	m_ForwardBtn.SizeToContent();
	m_BackBtn.SizeToContent();


	m_sBranchName = m_ci.GetBranchName(m_ui.nCompany);
	m_sCompany = m_ci.GetCompanyName(m_ui.nCompany);
	
	
	CRect rc;
	GetParent()->GetClientRect(rc);
	MoveWindow(0, 0, rc.Width(), rc.Height());
	m_hThreadCom = ::AfxBeginThread(InitData,this, 0, CREATE_SUSPENDED, NULL);    // 쓰레드로 처리 InitData()

	m_btnChangeMainPage.ShowWindow(AfxGetApp()->GetProfileInt("HomeForm", "MainPage", 0) == 0 ? SW_SHOW : SW_HIDE);
}

void CHomeForm1::RefreshList()
{
	
	CMyFormView::RefreshList();
}

HRESULT CHomeForm1::GetPostData(CString strKey, LPVARIANT pvPostData)
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

void CHomeForm1::OnBnClickedRefreshButton()
{
	CoInitialize(NULL); 
	HRESULT hr;
	int nSum = 0;
	BSTR bstrURL = NULL, bstrHeaders = NULL;
	VARIANT vFlags = {0},vTargetFrameName = {0},vPostData = {0},vHeaders = {0};
	CString strUrl = "http://appQuick2011.logisoft.co.kr:8000/default.asp";
	//_variant_t vtUrl(strUrl.AllocSysString());

	bstrHeaders = SysAllocString(L"Content-Type: application/x-www-form-urlencoded;charset=utf-8\r\n");
	V_VT(&vHeaders) = VT_BSTR;
	V_BSTR(&vHeaders) = bstrHeaders;
	CString strForm, strPostInfo;			
	nSum = m_ci.m_bRcpIntMode1 + m_ci.m_bRcpIntMode2 + m_ci.m_bRcpIntMode3 + m_ci.m_bRcpIntMode4 + m_ci.m_bRcpIntMode5;
			
	CString strBranchName = m_sBranchName, strCompany = m_sCompany;		
	CString strID = m_ui.strID, strName = m_ui.strName;

	strBranchName.Replace("&","＆");
	strCompany.Replace("&","＆");
	strID.Replace("&", "＆");
	strName.Replace("&", "＆");

	strForm.Format("sCompany=%s&sBranchName=%s&id_name=%s&sPWD=%s&sWName=%s&nWCompany=%ld&bIntegrated=%s&nSessionKey=%ld&sIP=%s&nLoginType=1",
		strCompany, strBranchName, strID, m_ui.strPW, strName, m_ci.m_nCompanyCode,nSum ? "1" : "0", 
		m_ui.nSiteSessionKey, m_ei.strExternalIP);

	//strForm.Format("id_name=love7310&sWName=김형석");

	hr = GetPostData(strForm,&vPostData);	

	if(m_Explorer.GetSafeHwnd())
		m_Explorer.Navigate((LPCTSTR)strUrl,&vFlags,&vTargetFrameName,&vPostData,&vHeaders);
		
	CoUninitialize();
}




void CHomeForm1::OnBnClickedAfterButton()
{


	try {
		m_Explorer.GoForward();
	} catch (CException *e) {
		e->Delete();
	}

	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CHomeForm1::OnBnClickedBackButton()
{
	try {
		m_Explorer.GoBack();
	} catch (CException *e) {
		e->Delete();
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

BEGIN_EVENTSINK_MAP(CHomeForm1, CMyFormView)
	ON_EVENT(CHomeForm1, IDC_EXPLORER, 105, CommandStateChangeExplorer, VTS_I4 VTS_BOOL)
END_EVENTSINK_MAP()

void CHomeForm1::CommandStateChangeExplorer(long Command, BOOL Enable)
{

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

BOOL CHomeForm1::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nHitTest == HTCLIENT)
	{
		CRect rectRefresh, rectForward, rectBack;
		m_RefeshBtn.GetWindowRect(&rectRefresh);
		m_ForwardBtn.GetWindowRect(&rectForward);
		m_BackBtn.GetWindowRect(&rectBack);

		CPoint point;
		GetCursorPos(&point);

		if(rectRefresh.PtInRect(point))
			::SetCursor(AfxGetApp()->LoadCursor(IDC_HOLD_CURSOR));
		else if(rectForward.PtInRect(point))
			::SetCursor(AfxGetApp()->LoadCursor(IDC_HOLD_CURSOR));
		else if(rectBack.PtInRect(point))
			::SetCursor(AfxGetApp()->LoadCursor(IDC_HOLD_CURSOR));
		else
			::SetCursor(AfxGetApp()->LoadCursor(IDC_ARROW));
	}




	return CMyFormView::OnSetCursor(pWnd, nHitTest, message);
}

void CHomeForm1::OnBnClickedToMainButton()
{
	AfxGetApp()->WriteProfileInt("HomeForm", "MainPage", 1);
	MessageBox("다음 로그인시에는 게시판이 메인페이지로 설정됩니다.", "확인", MB_ICONINFORMATION);
}
