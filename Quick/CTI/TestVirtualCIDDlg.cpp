// TestVirtualCIDDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "TestVirtualCIDDlg.h"



// CTestVirtualCIDDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTestVirtualCIDDlg, CMyDialog)
CTestVirtualCIDDlg::CTestVirtualCIDDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CTestVirtualCIDDlg::IDD, pParent)
{
}

CTestVirtualCIDDlg::~CTestVirtualCIDDlg()
{
}

void CTestVirtualCIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestVirtualCIDDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CTestVirtualCIDDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTestVirtualCIDDlg �޽��� ó�����Դϴ�.

void CTestVirtualCIDDlg::OnOK()
{
	CEdit *pPhoneEdit = (CEdit*)GetDlgItem(IDC_PHONE_EDIT);
	CEdit *pLineEdit = (CEdit*)GetDlgItem(IDC_LINE_EDIT);

	CString strPhone, strLine;
	pPhoneEdit->GetWindowText(strPhone);
	pLineEdit->GetWindowText(strLine);

	if(strPhone.GetLength() == 0 || strLine.GetLength() == 0)
	{
		MessageBox("������ �Է��Ͻñ� �ٶ��ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}


	char data[1024];
	COPYDATASTRUCT *cds = new COPYDATASTRUCT;

	STRCPY(data, "E", "-1", strPhone, "-1", strLine, VL_END);
	cds->cbData = strlen(data);
	cds->lpData = (void*) data; 
	
	::SendMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_COPYDATA, (long)this->m_hWnd, (long)cds);

	delete cds;


	CMyDialog::OnOK();
}


void CTestVirtualCIDDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}
