// BranchMainListDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "BranchMainListDlg.h"
#include "GradientReportPaintManager.h"
#include "BranchSel.h"


// CBranchMainListDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CBranchMainListDlg, CMyDialog)

CBranchMainListDlg::CBranchMainListDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CBranchMainListDlg::IDD, pParent)
{
	m_pBranchSel = NULL;
}

CBranchMainListDlg::~CBranchMainListDlg()
{
}

void CBranchMainListDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BRANCH_LIST, m_lst);
	DDX_Control(pDX, IDC_CLOSE_BTN, m_btnClose);
}


BEGIN_MESSAGE_MAP(CBranchMainListDlg, CMyDialog)
	ON_NOTIFY(NM_CLICK, IDC_BRANCH_LIST, OnReportItemClick)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CBranchMainListDlg::OnBnClickedCloseBtn)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_NOTIFY(NM_SETFOCUS, IDC_BRANCH_LIST, OnBranchListFocus)
	ON_NOTIFY(NM_KILLFOCUS, IDC_BRANCH_LIST, OnBranchKillFocus)
END_MESSAGE_MAP()


// CBranchMainListDlg 메시지 처리기입니다.

void CBranchMainListDlg::OnBranchListFocus(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	int a = 0;
	int nb = 0;
}


void CBranchMainListDlg::OnBranchKillFocus(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	int a = 0;
	int nb = 0;
}

BOOL CBranchMainListDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	SetForegroundWindow();

	m_lst.InsertColumn(0, "지사", LVCFMT_LEFT, 105);
	m_lst.ShowHeader(FALSE);
	m_lst.Populate();
	m_lst.SetPaintManager(new CGradientReportPaintManager);
	m_lst.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_lst.GetPaintManager()->m_strNoItems = "";

	m_lst.Populate();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CBranchMainListDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if(!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	long nIndex = m_lst.GetNextItem(-1, LVNI_SELECTED);
	CXTPTaskPanelItem *pItem = (CXTPTaskPanelItem*)m_lst.GetItemData(nIndex);

	m_pBranchSel->ChangeMainBranch(pItem);	

	ShowWindow(FALSE);
}

void CBranchMainListDlg::OnBnClickedCloseBtn()
{
	ShowWindow(FALSE);
}

void CBranchMainListDlg::OnKillFocus(CWnd* pNewWnd)
{
	CMyDialog::OnKillFocus(pNewWnd);

	this->ShowWindow(FALSE);
}

void CBranchMainListDlg::OnSetFocus(CWnd* pOldWnd)
{
	int a = 0;
	int b = 0;
	CMyDialog::OnSetFocus(pOldWnd);
	//this->ShowWindow(TRUE);
}

BOOL CBranchMainListDlg::PreTranslateMessage(MSG* pMsg)
{
	if(::GetDlgCtrlID(pMsg->hwnd) == IDC_BRANCH_LIST)
	{
		if(pMsg->message == WM_KILLFOCUS)
		{
			this->ShowWindow(FALSE);
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}
