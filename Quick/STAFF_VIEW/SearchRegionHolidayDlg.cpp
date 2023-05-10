// SearchRegionDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SearchRegionHolidayDlg.h"
#include "WinInet.h"
#include "tinyxml.h"
// CSearchRegionHolidayDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSearchRegionHolidayDlg, CMyDialog)
CSearchRegionHolidayDlg::CSearchRegionHolidayDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CSearchRegionHolidayDlg::IDD, pParent)
{
	m_bExpandLiData = FALSE;
	m_strLi = "";
	m_nDongID = 0;
	m_bAloneItemAutoClosed = TRUE;
	m_strDisplayDong = "";
	m_bReturnLiID = FALSE;
}

CSearchRegionHolidayDlg::~CSearchRegionHolidayDlg()
{
}

void CSearchRegionHolidayDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Text(pDX, IDC_SEARCH_EDIT, m_strSearch);
	DDX_Control(pDX, IDC_ADDRESS_EDIT, m_edtAddress);
	DDX_Control(pDX, IDC_DETAIL_EDIT, m_edtDetail);
	DDX_Control(pDX, IDC_RESULT_EDIT, m_edtResult);
}


BEGIN_MESSAGE_MAP(CSearchRegionHolidayDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	//ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnNMDblclkList1)
	ON_BN_CLICKED(IDC_SEAECH_BUTTON, &CSearchRegionHolidayDlg::OnBnClickedSeaechButton)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CSearchRegionHolidayDlg::OnEnChangeSearchEdit)
	ON_EN_CHANGE(IDC_DETAIL_EDIT, &CSearchRegionHolidayDlg::OnEnChangeDetailEdit)
END_MESSAGE_MAP()


// CSearchRegionHolidayDlg 메시지 처리기입니다.

BOOL CSearchRegionHolidayDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	CenterWindow();

	m_List.InsertColumn(0, "신주소", LVCFMT_LEFT, 280);
	m_List.InsertColumn(1, "구주소", LVCFMT_LEFT, 260);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE);
	//m_List.ShowHeader(FALSE);

	if(m_strSearch.GetLength() > 0)
		RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSearchRegionHolidayDlg::RefreshList()
{
	m_List.DeleteAllItems();

	CString strSearch;
	m_edtSearch.GetWindowText(strSearch);

	LPCTSTR accept[2]={ _T("*/*"), NULL };

	HINTERNET hInternet = InternetOpen( _T("HTTP"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );
 
	HINTERNET hConnect = InternetConnect( hInternet, "www.juso.go.kr", 80, 
																	 NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0 );

	CString strUrl;
	strUrl.Format("addrlink/addrLinkApi.do?confmKey=U01TX0FVVEgyMDE4MDkwNTE5MTM0NjEwODE1OTE=&currentPage=1&countPerPage=10&keyword=%s", ConvertStringToSendData(strSearch));

	HINTERNET hRequest = HttpOpenRequest( hConnect, _T("POST"),strUrl, NULL, NULL, accept, 
														   INTERNET_FLAG_DONT_CACHE, 0 );


	//DWORD dwValue = 1000; 
	//BOOL bRet = InternetSetOption(hRequest, INTERNET_OPTION_CONNECT_TIMEOUT, &dwValue, sizeof(dwValue));
 
	HttpSendRequest( hRequest, NULL, 0, NULL, 0 );

	DWORD dwSize = 0; 
	BOOL bQuery = InternetQueryDataAvailable( hRequest, &dwSize, 0, 0 );

	CString strText;

	char* szXml = NULL;
	
	if ( bQuery && dwSize > 0 )
	{

		DWORD dwTotal = 0;
		char* pData = (char*)malloc( dwTotal + dwSize + 1 );
		while ( pData && dwSize ) 
		{ 
			DWORD dwRead = 0;
			InternetReadFile( hRequest, pData+dwTotal, dwSize, &dwRead );
			dwTotal += dwRead;
			pData[dwTotal] = NULL;
			InternetQueryDataAvailable( hRequest, &dwSize, 0, 0 );
			if ( dwSize > 0 )
			{ 
				pData = (char*)realloc( pData, dwTotal + dwSize+1 );
			}

			szXml = pData;
		}
	}

	InternetCloseHandle( hRequest );
	InternetCloseHandle( hConnect );
	InternetCloseHandle( hInternet );

	ParseXml(szXml);

}


void CSearchRegionHolidayDlg::OnBnClickedSearchBtn()
{
	RefreshList();
}

void CSearchRegionHolidayDlg::OnBnClickedOk()
{	
	CString s1; m_edtAddress.GetWindowText(s1);
	CString s2; m_edtDetail.GetWindowText(s2);
	CString s3; m_edtResult.GetWindowText(s3);

	if(s1.IsEmpty())
	{
		MessageBox("기본 주소를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(s2.IsEmpty())
	{
		MessageBox("상세 주소를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(s3.IsEmpty())
	{
		MessageBox("주소를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	m_strSearchResult = s3;

	//m_nDongID = m_List.GetItemData(nItem);
	OnOK();
	
}

void CSearchRegionHolidayDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	CXTPGridRecord *pRecord = m_List.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	CString s1 = m_List.GetItemText(pRecord, 0);
	m_strRoadPart1 = m_List.GetItemDataText(pRecord);
	m_strRoadPart2 = m_List.GetItemDataText2(pRecord);
	m_strZipNo = m_List.GetItemDataText3(pRecord);
	
	m_edtAddress.SetWindowText(s1);
	
	*pResult = 0;
}

BOOL CSearchRegionHolidayDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_UP)
		{
			SelectUp();
			return TRUE;
		}
		else if(pMsg->wParam == VK_DOWN)
		{
			SelectDown();
			return TRUE;
		}
		else if(pMsg->wParam == VK_RETURN)
		{
			if(::GetDlgCtrlID(pMsg->hwnd) == IDC_SEARCH_EDIT)
			{
				RefreshList();
				GetDlgItem(IDOK)->SetFocus();
			}
			else
				OnBnClickedOk(); 
			return FALSE;
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}


void CSearchRegionHolidayDlg::SelectUp()
{
	CXTPGridRow *pRow = NULL;
	CXTPGridRows *pRows = m_List.GetRows();
	CXTPGridSelectedRows *pSelRows = m_List.GetSelectedRows();
	CXTPGridRow *pSelRow = pSelRows->GetAt(0);

	if(pRows == NULL)
		pRow = pRows->GetAt(m_List.GetItemCount() - 1);
	else
		pRow = pRows->GetAt(max(pSelRow->GetIndex() -1, 0));

	m_List.GetSelectedRows()->Select(pRow);
}

void CSearchRegionHolidayDlg::SelectDown()
{
	CXTPGridRow *pRow = NULL;
	CXTPGridRows *pRows = m_List.GetRows();
	CXTPGridSelectedRows *pSelRows = m_List.GetSelectedRows();
	CXTPGridRow *pSelRow = pSelRows->GetAt(0);

	if(pRows == NULL)
		pRow = pRows->GetAt(0);
	else
		pRow = pRows->GetAt(min(pSelRow->GetIndex() + 1, m_List.GetItemCount()));

	m_List.GetSelectedRows()->Select(pRow);
}

void CSearchRegionHolidayDlg::OnBnClickedSeaechButton()
{
	RefreshList();
}

void CSearchRegionHolidayDlg::OnEnChangeSearchEdit()
{
	//RefreshList();
}

CString CSearchRegionHolidayDlg::ConvertStringToSendData(const CString & s, CByteArray & msg)
{
	BOOL bSuccess = FALSE;
#ifdef _UNICODE
	int n = ::WideCharToMultiByte(CP_UTF8, 0, s, -1, NULL, 0, NULL, NULL);
	if(n == 0)
	{ /* failed */
		DWORD err = ::GetLastError();
		msg.SetSize(0);
		bSuccess = FALSE;
	} /* failed */
	else
	{ /* success */
		msg.SetSize(n);
		n = ::WideCharToMultiByte(CP_UTF8, 0, s, -1, (LPSTR)msg.GetData(), n, NULL, NULL);
		if(n == 0)
		{ /* conversion failed */
			DWORD err = ::GetLastError();
			msg.SetSize(0);
			bSuccess = FALSE;
		} /* conversion failed */
		else
		{ /* use multibyte string */
			msg.SetSize(n - 1);
			bSuccess = TRUE;
		} /* use multibyte string */
	} /* success */
#else // ANSI
	CArray<WCHAR, WCHAR> wc;

	int n = ::MultiByteToWideChar(CP_ACP, 0, s, -1, NULL, 0);
	if(n == 0)
	{ /* failed */
		DWORD err = ::GetLastError();
		msg.SetSize(0);
		bSuccess = FALSE;
	} /* failed */
	else
	{ /* success */
		wc.SetSize(n);
		n = ::MultiByteToWideChar(CP_ACP, 0, s, -1, wc.GetData(), n);
	} /* success */     

	n = ::WideCharToMultiByte(CP_UTF8, 0, wc.GetData(), -1, NULL, 0, NULL, NULL);
	if(n == 0)
	{ /* failed */
		DWORD err = ::GetLastError();
		msg.SetSize(0);
		bSuccess = FALSE;
	} /* failed */
	else
	{ /* success */
		msg.SetSize(n);
		n = ::WideCharToMultiByte(CP_UTF8, 0, wc.GetData(), -1, (LPSTR)msg.GetData(), n, NULL, NULL);
		if(n == 0)
		{ /* conversion failed */
			DWORD err = ::GetLastError();
			msg.SetSize(0);
			bSuccess = FALSE;
		} /* conversion failed */
		else
		{ /* use multibyte string */
			msg.SetSize(n - 1);
			bSuccess = TRUE;
		} /* use multibyte string */
	} /* success */
#endif

	if(bSuccess)
		return ConvertStringToSendData(&msg);

	return "";
}

CString CSearchRegionHolidayDlg::ConvertStringToSendData(CString strText)
{
	CByteArray msg;
	return ConvertStringToSendData(strText, msg);
}

CString CSearchRegionHolidayDlg::ConvertStringToSendData(CByteArray *msg)
{
	CString strItemSum = "";
	CString strItem;
	//char szData[10000];

	for(int i = 0; i < (int)msg->GetSize(); i++) 
	{
		strItem.Format("%02X", (BYTE)msg->GetAt(i));
		strItemSum += "%" + strItem;
		//sprintf(&szData[i * 2], "%02X", (BYTE)msg->GetAt(i));
	}

	return strItemSum;
}

BOOL CSearchRegionHolidayDlg::ParseXml(char *sz)
{
	CString s = UTF8ToANSI(sz);
	#define GET_ELEMENT_TEXT(x, y) UTF8ToANSI(x->FirstChildElement(y)->GetText());

	if(!sz)
		return FALSE;

	TiXmlDocument doc;
	doc.Parse(sz);

	delete sz;

	TiXmlElement *pRoot = doc.FirstChildElement("results");

	if(!pRoot) 
		return FALSE;

	TiXmlElement *pCommon = pRoot->FirstChildElement("common");

	if(!pCommon) 
		return FALSE;

	CString strErrorCode = GET_ELEMENT_TEXT(pCommon, "errorCode");
	CString strTotalCount = GET_ELEMENT_TEXT(pCommon, "totalCount");

	if(strErrorCode != "0")
		return FALSE;
	
	TiXmlElement *pJuso = pRoot->FirstChildElement("juso");

	long nItem = 0;
	
	while(pJuso)
	{		
		CString strNewAddress = GET_ELEMENT_TEXT(pJuso, "roadAddr");
		CString strOldAddress = GET_ELEMENT_TEXT(pJuso, "jibunAddr");

		CString strroadPart1 = GET_ELEMENT_TEXT(pJuso, "roadAddrPart1");
		CString strroadPart2 = GET_ELEMENT_TEXT(pJuso, "roadAddrPart2");

		CString strZipNo = GET_ELEMENT_TEXT(pJuso, "zipNo");

		m_List.InsertItem(nItem, strNewAddress);
		m_List.SetItemText(nItem, 1, strOldAddress);
		m_List.SetItemDataText(nItem, strroadPart1);
		m_List.SetItemDataText2(nItem, strroadPart2);
		m_List.SetItemDataText3(nItem++, strZipNo);

		pJuso = pJuso->NextSiblingElement("juso");
	}	

	m_List.Populate();

	return TRUE;
}

char* CSearchRegionHolidayDlg::UTF8ToANSI(const char *pszCode)
{
	BSTR    bstrWide;
	char*   pszAnsi;
	int     nLength;

	nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, lstrlen(pszCode) + 1, NULL, NULL);
	bstrWide = SysAllocStringLen(NULL, nLength);

	MultiByteToWideChar(CP_UTF8, 0, pszCode, lstrlen(pszCode) + 1, bstrWide, nLength);

	nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
	pszAnsi = new char[nLength];

	WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
	SysFreeString(bstrWide);

	return pszAnsi;
} 

void CSearchRegionHolidayDlg::OnEnChangeDetailEdit()
{
	if(m_strRoadPart1.IsEmpty())
	{
		MessageBox("기본 주소를 리스트에서 선택하세요", "확인", MB_ICONINFORMATION);		
		return;
	}

	CString strDetail;
	m_edtDetail.GetWindowText(strDetail);

	m_edtResult.SetWindowText(m_strRoadPart1 + ", " + strDetail + " " + m_strRoadPart2);

}
