// WebUploadDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "WebUploadDlg.h"
#include "tinyxml.h"


// CWebUploadDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CWebUploadDlg, CDialog)

CWebUploadDlg::CWebUploadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWebUploadDlg::IDD, pParent)
{
	m_bAutoSelect = TRUE;
}

CWebUploadDlg::~CWebUploadDlg()
{
}

void CWebUploadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER, m_explorer);

}


BEGIN_MESSAGE_MAP(CWebUploadDlg, CDialog)
END_MESSAGE_MAP()


// CWebUploadDlg 메시지 처리기입니다.


BOOL CWebUploadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_explorer.Navigate(m_strURL, NULL, NULL, NULL, NULL);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
BEGIN_EVENTSINK_MAP(CWebUploadDlg, CDialog)
	ON_EVENT(CWebUploadDlg, IDC_EXPLORER, 250, CWebUploadDlg::BeforeNavigate2Explorer, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
END_EVENTSINK_MAP()


void CWebUploadDlg::BeforeNavigate2Explorer(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel)
{
	CString strURL(URL->bstrVal);
	CString strXML(strURL.Right(strURL.GetLength()-6));
	strXML.Replace("%20", " ");

	//최초 실행시 URL이 리턴되는데, URL이면 skip한다.
	if(strURL == m_strURL)
		*Cancel = FALSE;
	else
	{
		*Cancel = TRUE;
		TiXmlDocument doc;
		doc.Parse(strXML);

		TiXmlElement *pRoot = doc.FirstChildElement("element");
		if(pRoot) {
			m_strResult = pRoot->GetText();			
			OnOK();
		}		
	}
}
