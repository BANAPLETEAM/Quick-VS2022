// WebUploadDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "WebUploadDlg.h"
#include "tinyxml.h"


// CWebUploadDlg ��ȭ �����Դϴ�.

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


// CWebUploadDlg �޽��� ó�����Դϴ�.


BOOL CWebUploadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_explorer.Navigate(m_strURL, NULL, NULL, NULL, NULL);
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
BEGIN_EVENTSINK_MAP(CWebUploadDlg, CDialog)
	ON_EVENT(CWebUploadDlg, IDC_EXPLORER, 250, CWebUploadDlg::BeforeNavigate2Explorer, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
END_EVENTSINK_MAP()


void CWebUploadDlg::BeforeNavigate2Explorer(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel)
{
	CString strURL(URL->bstrVal);
	CString strXML(strURL.Right(strURL.GetLength()-6));
	strXML.Replace("%20", " ");

	//���� ����� URL�� ���ϵǴµ�, URL�̸� skip�Ѵ�.
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
