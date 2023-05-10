// BranchReportMainDlg.cpp : 구현 파일입니다.
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
// CBranchReportMainDlg 대화 상자입니다.

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


// CBranchReportMainDlg 메시지 처리기입니다.

BOOL CBranchReportMainDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	CRect rtSTATIC_OPTION;
	this->GetDlgItem(IDC_STATIC_BRANCH)->GetWindowRect(rtSTATIC_OPTION);
	this->ScreenToClient(rtSTATIC_OPTION);
	this->GetDlgItem(IDC_STATIC_BRANCH)->ShowWindow(SW_HIDE);

	LU->CreateFormViewTabControl(this, &m_wndTabControl, rtSTATIC_OPTION);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CBranchReportTransferDlg), "이체/청구", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CBranchReportLogDlg), "입출금내역", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CBranchReportWantTransferDlg), "청구내역", 0);

	((CBranchReportTransferDlg*)GetTabItem(0))->RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CBranchReportMainDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

int CBranchReportMainDlg::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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

