// SignDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RecPlayerDlg.h"
#include <WinInet.h>
#include <afxinet.h>
#include "LogiUtil.h"

// CSignDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRecPlayerDlg, CMyDialog)
CRecPlayerDlg::CRecPlayerDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CRecPlayerDlg::IDD, pParent)
{
	m_dtDate.SetStatus(COleDateTime::null);
}

CRecPlayerDlg::~CRecPlayerDlg()
{
}

void CRecPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER, m_Explorer);
}


BEGIN_MESSAGE_MAP(CRecPlayerDlg, CMyDialog)
	ON_WM_SIZE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CSignDlg 메시지 처리기입니다.

BOOL CRecPlayerDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRecPlayerDlg::Navigate()
{
	try
	{
		CoInitialize(NULL);
		HRESULT hr;
		BSTR bstrURL = NULL, bstrHeaders = NULL;
		VARIANT vFlags = {0},vTargetFrameName = {0},vPostData = {0},vHeaders = {0};
		//CString strUrl = "http://192.168.1.15:8080/m_player.php?";
		if(m_dtDate.GetStatus() == COleDateTime::null)
			m_dtDate = COleDateTime::GetCurrentTime();

		CString strUrl;
		strUrl.Format("http://%s/m_player.php?", LU->GetRecordFileServerIP(m_dtDate));

		bstrHeaders = SysAllocString(L"Content-Type: application/x-www-form-urlencoded\r\n");
		V_VT(&vHeaders) = VT_BSTR;
		V_BSTR(&vHeaders) = bstrHeaders;

		CString strForm, strPostInfo;		
		strForm = GetPostFormData();

		g_bana_log->Print("\n RecordFileServer URL %s \n Form %s \r\n", strUrl, strForm);

		hr = GetPostData(strForm,&vPostData);	
		m_Explorer.Navigate((LPCTSTR)strUrl,&vFlags,&vTargetFrameName,&vPostData,&vHeaders);
		CoUninitialize();

	}
	catch(char *szMsg)
	{
		MessageBox(szMsg,"확인", MB_ICONINFORMATION);
	}
}


HRESULT CRecPlayerDlg::GetPostData(CString strKey, LPVARIANT pvPostData)
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

void CRecPlayerDlg::InitPostFormData(COleDateTime date, CString strFolderDate, CString strKeyPhoenID, CString strTellNumber, CString strFileName, int nBound)
{
	RemovePostFormData();
	m_dtDate = date;
	m_strDate.Format("%d-%02d-%02d %02d:%02d:%02d", date.GetYear(), date.GetMonth(), date.GetDay(), date.GetHour(), date.GetMinute(), date.GetSecond());
	m_strKeyPhoenID = strKeyPhoenID;
	m_strTellNumber = strTellNumber;
	m_strFileName = strFileName;
	m_strBound.Format("%d", nBound);
	m_strYY = strFolderDate.Left(4);
	m_strMM = strFolderDate.Mid(4, 2);
	m_strDD = strFolderDate.Right(2);
}

void CRecPlayerDlg::AddPostFormData(COleDateTime date, CString strFolderDate, CString strKeyPhoenID, CString strTellNumber, CString strFileName, int nBound)
{
	CString strTemp;
	strTemp.Format("%d-%02d-%02d %02d:%02d:%02d", date.GetYear(), date.GetMonth(), date.GetDay(), date.GetHour(), date.GetMinute(), date.GetSecond());
	m_strDate += "," + strTemp;
	m_strKeyPhoenID += "," + strKeyPhoenID;
	m_strTellNumber += "," + strTellNumber;
	m_strFileName += "," + strFileName;
	strTemp.Format("%d", nBound);				m_strBound += "," + strTemp;
	m_strYY += "," + strFolderDate.Left(4);
	m_strMM += "," + strFolderDate.Mid(4, 2);
	m_strDD += "," + strFolderDate.Right(2);
}

void CRecPlayerDlg::RemovePostFormData()
{
	m_dtDate.SetStatus(COleDateTime::null);
	m_strDate = "";
	m_strKeyPhoenID = "";
	m_strTellNumber = "";
	m_strFileName = "";
	m_strBound = "";
	m_strYY = "";
	m_strMM = "";
	m_strDD = "";
}

CString CRecPlayerDlg::GetPostFormData()
{
	CString strForm;
	strForm.Format("REGDATE=%s&YY=%s&MM=%s&DD=%s&sFileName=%s&sTel=%s&phone=%s&bound=%s"
		, m_strDate, m_strYY, m_strMM, m_strDD, m_strFileName, m_strTellNumber, m_strKeyPhoenID, m_strBound);
	return strForm;
}

BOOL CRecPlayerDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_RBUTTONDOWN)
	{
		CRect rect;
		m_Explorer.GetClientRect(&rect);

		CPoint pt;
		GetCursorPos(&pt);

		m_Explorer.ScreenToClient(&pt);

		if(rect.PtInRect(pt))
			return TRUE;
		if(::GetDlgCtrlID(pMsg->hwnd) == IDC_EXPLORER)
		{		
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CRecPlayerDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);
	if(m_Explorer.GetSafeHwnd())
	{
		m_Explorer.SetWindowPos(NULL, 0, 0/*MAP_TOP*/, cx, cy, SWP_NOZORDER);
	}
}

void CRecPlayerDlg::OnClose()
{
	DestroyWindow();
}