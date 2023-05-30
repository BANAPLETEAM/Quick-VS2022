// SignDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "SignDlg.h"



// CSignDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSignDlg, CMyDialog)
CSignDlg::CSignDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSignDlg::IDD, pParent)
{
}

CSignDlg::~CSignDlg()
{
}

void CSignDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER, m_Explorer);
}


BEGIN_MESSAGE_MAP(CSignDlg, CMyDialog)
END_MESSAGE_MAP()


// CSignDlg �޽��� ó�����Դϴ�.

BOOL CSignDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CString sTNo = "";
	sTNo.Format("%d", m_nTNo);

 	this->SetWindowText("������ȣ - " + sTNo);
	// http://sign.logisoft.co.kr:83/logi_sign_display_quick.htm?sDBType=quick&nTNo=127000952&nCNo=16968989
	CString sUrl = "http://sign.logisoft.co.kr:83/logi_sign_display_quick.htm?sDBType=quick&nTNo=" + sTNo;
	sUrl += "&nCNo=" + LF->GetStringFromLong(m_nCNo);
	// + sTNo.Left(3) + "/";	
	//sUrl += "&sUrl2=" + sTNo + "_2.bmp";

	

	m_Explorer.Navigate(sUrl, NULL, NULL, NULL, NULL);

	
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

BOOL CSignDlg::PreTranslateMessage(MSG* pMsg)
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
		//if(::GetDlgCtrlID(pMsg->hwnd) == IDC_EXPLORER)
		//{		
		//	return TRUE;
		//}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}
