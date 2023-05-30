// MakeGroupReportSendDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "MakeGroupReportSendDlg.h"



// CMakeGroupReportSendDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMakeGroupReportSendDlg, CDHtmlDialog)
CMakeGroupReportSendDlg::CMakeGroupReportSendDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CMakeGroupReportSendDlg::IDD,CMakeGroupReportSendDlg::IDH, pParent)
{
	m_nGroupReportID = 0;
	m_nGNo = 0;
	m_strEmail = "";
	m_nTest = FALSE;
	m_pDoc2 = NULL;
	m_dtBillCollection = COleDateTime::GetCurrentTime();
	m_dtPayMent = COleDateTime::GetCurrentTime();
	m_bPayMent = FALSE;
	m_bBillCollection = FALSE;
}

CMakeGroupReportSendDlg::~CMakeGroupReportSendDlg()
{
}

void CMakeGroupReportSendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);	
	//DDX_Control(pDX, IDC_EXPLORER, m_Explorer);
}


BEGIN_MESSAGE_MAP(CMakeGroupReportSendDlg, CDHtmlDialog)
	
	ON_WM_CONTEXTMENU()
	
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CMakeGroupReportSendDlg)
	
	DHTML_EVENT_ONCLICK(_T("HideDiv"),	OnHideClose)	
END_DHTML_EVENT_MAP()


// CMakeGroupReportSendDlg �޽��� ó�����Դϴ�.

BOOL CMakeGroupReportSendDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	SendKindReportWeb(1,FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

HRESULT CMakeGroupReportSendDlg::OnHideClose(IHTMLElement* pElement)
{		

	CDHtmlDialog::OnClose();
	this->OnOK();

	return S_OK;
}

void CMakeGroupReportSendDlg::OnDocumentComplete(LPDISPATCH pDisp, LPCTSTR szUrl)
{

	IDispatch *pLocalDisp = NULL;

	CoInitialize(NULL);
	HRESULT hr;

	hr = GetDHtmlDocument(&m_pDoc2);
	if(!SUCCEEDED(hr))
		return;

	if(m_pDoc2)
	{		
		BOOL bSetDoc = m_Js.SetDocument(m_pDoc2);
		if(bSetDoc )
		{
			
			//if(m_pRcpViewWeb)
			//{
			//	IHTMLDocument2Ptr spDoc(m_pRcpViewWeb->GetRcpPageWeb()->m_Explorer.GetDocument()); 
			//	//MSHTML::IHTMLDocument2Ptr spDoc(m_pRcpViewWeb->GetRcpPageWeb()->m_Explorer.GetDocument()); 
			//	LPDISPATCH dipatchDocument = m_pRcpViewWeb->GetRcpPageWeb()->m_Explorer.GetDocument();
			//	LPDISPATCH dipatchApplication = m_pRcpViewWeb->GetRcpPageWeb()->m_Explorer.GetApplication();

			//	//m_pRcpViewWeb->GetRcpPageWeb()->m_Explorer.GetW
			//	IHTMLDocument2 **pHtmlDoc = NULL;

			//	IUnknown* pUnkBrowser = NULL;

			//	//IHTMLDocument2Ptr pHtmlDoc( m_pRcpViewWeb->GetRcpPageWeb()->m_Explorer.GetDocument());


			//	/*
			//	HRESULT hr = CoCreateInstance(CLSID_InternetExplorer, NULL,
			//	CLSCTX_LOCAL_SERVER, IID_IWebBrowser2, (void**)&pBrowser);
			//	pBrowser->get_Application(&dipatchApplication);*/

			//	BOOL bTrue = m_Js.CallJScript("SetParentWindow", dipatchApplication);
			//	if(bTrue)
			//	{
			//		//m_pRcpViewWeb->GetRcpPageWeb()->m_Js.CallJScript("SetParentWindow", m_pDoc2, m_pBrowserApp);
			//		//m_pRcpViewWeb->GetRcpPageWeb()->m_Js.CallJScript("SetParentDocument", m_pDoc2, m_pBrowserApp);
			//	}


			//
			//}


			//m_bLoadAndSetBrowser = TRUE;
			return ;
		}
	}
	CoUninitialize();
}

void CMakeGroupReportSendDlg::SendKindReportWeb(int nSendType,  BOOL bReSend)
{
	CoInitialize(NULL); 
	int nSum = 0;
	BSTR bstrURL = NULL, bstrHeaders = NULL;
	VARIANT vFlags = {0},vTargetFrameName = {0},vPostData = {0},vHeaders = {0};
	CString strUrl = "",strEmail = "";
	if(nSendType == 1) 
		strUrl = "http://qu2.logisoft.co.kr/calculate?";
		//strUrl = "http://qu2.logisoft.co.kr/POP/N_CreateTax_form_Q.asp";
	//_variant_t vtUrl(strUrl.AllocSysString());

	bstrHeaders = SysAllocString(L"Content-Type: application/x-www-form-urlencoded;charset=utf-8\r\n");
	V_VT(&vHeaders) = VT_BSTR;
	V_BSTR(&vHeaders) = bstrHeaders;
	CString strForm, strPostInfo,strID = "", strPWD = "", strBillCollection = "", strPayMent = "";		
	long nCompany = 0;

	if(m_nGNo <= 0)
	{
		LF->MsgBox("�׷���̵� ����ֽ��ϴ�.");
		return;
	}
	if(m_nGroupReportID <= 0)
	{
		LF->MsgBox("�׷츮��Ʈ ���̵� ����ֽ��ϴ�.");
		return;
	}

	nCompany = m_cg.GetGroupData(m_nGNo)->nCompany;
	strID = m_cg.GetGroupData(m_nGNo)->strID;
	strPWD = m_cg.GetGroupData(m_nGNo)->strPassword;
	//m_edtEmail.GetWindowText(strEmail);

	if(strID.GetLength() <= 0 || strPWD.GetLength() <= 0)
	{
		LF->MsgBox("���̵�� �н����带 �׷쿡�� �Է��ϼ���");
		return;
	} 

	if(IsTimeValid(m_dtPayMent) && m_bPayMent)
		strPayMent.Format("%d-%02d-%02d",m_dtPayMent.GetYear(), m_dtPayMent.GetMonth(),m_dtPayMent.GetDay());
	if(IsTimeValid(m_dtBillCollection) && m_bBillCollection)
		strBillCollection.Format("%d-%02d-%02d",m_dtBillCollection.GetYear(), m_dtBillCollection.GetMonth(),m_dtBillCollection.GetDay());
	
	//bstrURL = strUrl.AllocSysString();
 
	/*
	strForm.Format("nID=%d&sID=%s&strPassword=%s&nCompany=%d&sEmail=%s&nTest=%d&dtPayMent=%s&dtBillCollection=%s", 
		m_nGroupReportID,strID, strPWD, nCompany, m_strEmail, m_nTest, strPayMent, strBillCollection);
	*/
	///calculate?nID=989742&sWID=������&nSessionKey=%d&sIP=106.247.248.10
	strForm.Format("nID=%d&sWID=%s&nSessionKey=%d&sIP=%s", 
		m_nGroupReportID, m_ui.strID, m_ui.nSiteSessionKey, m_ei.strExternalIP);

	
	strUrl += strForm;
	bstrURL = strUrl.AllocSysString();

	//hr = GetPostData(strForm,&vPostData);	

	CString lpszTargetFrameName = NULL;
	DWORD dwFlags = NULL;

	//Navigate(strUrl, dwFlags,vPostData, lpszTargetFrameName);

	m_pBrowserApp->Navigate(bstrURL,&vFlags,&vTargetFrameName,&vPostData,&vHeaders);
	
//	Navigate(strUrl, COleVariant((long) dwFlags, VT_I4), COleVariant(lpszTargetFrameName, VT_BSTR), 
//			vPostData, COleVariant(lpszHeaders, VT_BSTR));
	

	//if(m_Explorer.GetSafeHwnd())
	//	m_Explorer.Navigate((LPCTSTR)strUrl,&vFlags,&vTargetFrameName,&vPostData,&vHeaders);

	CoUninitialize();
}


BOOL CMakeGroupReportSendDlg::IsTimeValid(COleDateTime dt)
{

	if(dt.GetStatus() == COleDateTime::valid && dt.GetStatus() != COleDateTime::null)
		return TRUE;
	return FALSE;

}
void CMakeGroupReportSendDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{

	/*CRect rect;
	m_lstReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(15);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);*/	

}
