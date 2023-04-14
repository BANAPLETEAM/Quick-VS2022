// TestVirtualCIDDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "TestVirtualCIDDlg.h"



// CTestVirtualCIDDlg 대화 상자입니다.

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


// CTestVirtualCIDDlg 메시지 처리기입니다.

void CTestVirtualCIDDlg::OnOK()
{
	CEdit *pPhoneEdit = (CEdit*)GetDlgItem(IDC_PHONE_EDIT);
	CEdit *pLineEdit = (CEdit*)GetDlgItem(IDC_LINE_EDIT);

	CString strPhone, strLine;
	pPhoneEdit->GetWindowText(strPhone);
	pLineEdit->GetWindowText(strLine);

	if(strPhone.GetLength() == 0 || strLine.GetLength() == 0)
	{
		MessageBox("정보를 입력하시기 바랍니다.", "확인", MB_ICONINFORMATION);
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}
