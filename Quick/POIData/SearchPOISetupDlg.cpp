// SearchPOISetupDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "SearchPOISetupDlg.h"
#include "SearchPOIDlg.h"


// CSearchPOISetupDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSearchPOISetupDlg, CMyDialog)

CSearchPOISetupDlg::CSearchPOISetupDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSearchPOISetupDlg::IDD, pParent)
{

}

CSearchPOISetupDlg::~CSearchPOISetupDlg()
{
}

void CSearchPOISetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USE_DIRECT_DISTANCE_CHECK, m_chkUseDirectDistance);
}


BEGIN_MESSAGE_MAP(CSearchPOISetupDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CSearchPOISetupDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSearchPOISetupDlg �޽��� ó�����Դϴ�.

BOOL CSearchPOISetupDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CSearchPOIDlg *pOwner = (CSearchPOIDlg*)GetOwner();
	CWnd *pWnd = GetWindow(GW_CHILD);

	while(pWnd)
	{
		int nID = pWnd->GetDlgCtrlID();

		if(nID != IDOK && nID != IDCANCEL)
		{
			CButton *pBtn = (CButton*)pOwner->GetDlgItem(nID);					
			((CButton*)pWnd)->SetCheck(pBtn->GetCheck());
		}

		pWnd = pWnd->GetNextWindow();
	}

	return FALSE;  // return TRUE unless you set the focus to a control
}

void CSearchPOISetupDlg::OnBnClickedOk()
{
	CSearchPOIDlg *pOwner = (CSearchPOIDlg*)GetOwner();
	CWnd *pWnd = GetWindow(GW_CHILD);

	while(pWnd)
	{
		int nID = pWnd->GetDlgCtrlID();

		if(nID != IDOK && nID != IDCANCEL)
		{
			CButton *pBtn = (CButton*)pOwner->GetDlgItem(nID);					
			pBtn->SetCheck(((CButton*)pWnd)->GetCheck());
		}

		pWnd = pWnd->GetNextWindow();
	}

	OnOK();
}

