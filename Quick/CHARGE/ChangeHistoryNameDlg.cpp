// ChangeHistoryNameDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "ChangeHistoryNameDlg.h"


// CChangeHistoryNameDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CChangeHistoryNameDlg, CMyDialog)

CChangeHistoryNameDlg::CChangeHistoryNameDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChangeHistoryNameDlg::IDD, pParent)
{
	m_sChargeName = "";
	m_sChargeEtc = "";

}

CChangeHistoryNameDlg::~CChangeHistoryNameDlg()
{
}

void CChangeHistoryNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ADD_CHARGE_EDIT,m_sChargeName );
	DDX_Text(pDX, IDC_ETC_EDIT,m_sChargeEtc );
}


BEGIN_MESSAGE_MAP(CChangeHistoryNameDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, &CChangeHistoryNameDlg::OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CChangeHistoryNameDlg::OnBnClickedCancelBtn)
	
END_MESSAGE_MAP()


BOOL CChangeHistoryNameDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	return TRUE;
}


void CChangeHistoryNameDlg::OnBnClickedOkBtn()
{
	UpdateData();
	if(m_sChargeName.GetLength() <= 0)
	{
		MessageBox("������� �̸��� �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	OnOK();
}

void CChangeHistoryNameDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}
