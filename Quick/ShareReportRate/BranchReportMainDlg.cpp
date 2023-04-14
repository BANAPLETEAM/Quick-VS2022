// BranchReportMainDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "BranchReportMainDlg.h"
#include "BranchReportTransferDlg.h"
#include "BranchReportLogDlg.h"
#include "BranchReportWantTransferDlg.h"



void CBranchTabControl::OnItemClick(CXTPTabManagerItem* pItem)
{
	CXTPTabControl::OnItemClick( pItem);
	HWND hWnd = pItem->GetHandle();
}
// CBranchReportMainDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CBranchReportMainDlg, CMyDialog)
CBranchReportMainDlg::CBranchReportMainDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CBranchReportMainDlg::IDD, pParent)
{
	m_bRequest = FALSE;
}

CBranchReportMainDlg::~CBranchReportMainDlg()
{
}

void CBranchReportMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MONEY_EDT, m_MoneyEdt);
}


BEGIN_MESSAGE_MAP(CBranchReportMainDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CBranchReportMainDlg �޽��� ó�����Դϴ�.

BOOL CBranchReportMainDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	CRect rtSTATIC_OPTION;
	this->GetDlgItem(IDC_STATIC_BRANCH)->GetWindowRect(rtSTATIC_OPTION);
	this->ScreenToClient(rtSTATIC_OPTION);
	this->GetDlgItem(IDC_STATIC_BRANCH)->ShowWindow(SW_HIDE);

	LU->CreateFormViewTabControl(this, &m_wndTabControl, rtSTATIC_OPTION);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CBranchReportTransferDlg), "��ü/û��", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CBranchReportLogDlg), "����ݳ���", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CBranchReportWantTransferDlg), "û������", 0);

	((CBranchReportTransferDlg*)GetTabItem(0))->RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CBranchReportMainDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

int CBranchReportMainDlg::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CMyDialog::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

CWnd* CBranchReportMainDlg::GetTabItem(int nTab)
{
	CXTPTabPaintManager* pXTPTabPaintManager =  m_wndTabControl.GetPaintManager();
	int nTabCount = m_wndTabControl.GetItemCount();
	if(nTab >= nTabCount) return NULL;

	CXTPTabManagerItem* pXTPTabManagerItem =  m_wndTabControl.GetItem(nTab);

	CWnd* pWnd =  FromHandle(pXTPTabManagerItem->GetHandle());
	return pWnd;
}

