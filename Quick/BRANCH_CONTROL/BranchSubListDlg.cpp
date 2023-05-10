// BranchSubListDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"

#include "BranchSubListDlg.h"
#include "BranchSel.h"
#include "GradientReportPaintManager.h"

// CBranchSubListDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CBranchSubListDlg, CMyDialog)

CBranchSubListDlg::CBranchSubListDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CBranchSubListDlg::IDD, pParent)
{
	m_pBranchSel = NULL;
}

CBranchSubListDlg::~CBranchSubListDlg()
{
}

void CBranchSubListDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BRANCH_LIST, m_lst);
	DDX_Control(pDX, IDC_CLOSE_BTN, m_btnClose);
}


BEGIN_MESSAGE_MAP(CBranchSubListDlg, CMyDialog)
	ON_NOTIFY(NM_CLICK, IDC_BRANCH_LIST, OnReportItemClick)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CBranchSubListDlg::OnBnClickedCloseBtn)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


// CBranchSubListDlg �޽��� ó�����Դϴ�.

BOOL CBranchSubListDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	SetForegroundWindow();

	m_lst.InsertColumn(0, "����", LVCFMT_LEFT, 105);
	m_lst.ShowHeader(FALSE);
	m_lst.Populate();
	m_lst.SetPaintManager(new CGradientReportPaintManager);
	m_lst.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_lst.GetPaintManager()->m_strNoItems = "";

	m_lst.Populate();
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CBranchSubListDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if(!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	m_pBranchSel->ChangeSubBranch();	

	ShowWindow(FALSE);

}
void CBranchSubListDlg::OnBnClickedCloseBtn()
{
	ShowWindow(FALSE);
}

void CBranchSubListDlg::OnKillFocus(CWnd* pNewWnd)
{
	CMyDialog::OnKillFocus(pNewWnd);
}
