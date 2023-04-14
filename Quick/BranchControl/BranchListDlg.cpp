// BranchListDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "BranchListDlg.h"
#include "RcpDlg.h"
#include "BranchSel.h"

// CBranchListDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CBranchListDlg, CMyDialog)
CBranchListDlg::CBranchListDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CBranchListDlg::IDD, pParent)
{
}

CBranchListDlg::~CBranchListDlg()
{
}

void CBranchListDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BRANCH_LIST, m_lst);
	DDX_Control(pDX, IDC_CLOSE_BTN, m_btnClose);
}


BEGIN_MESSAGE_MAP(CBranchListDlg, CMyDialog)
	ON_NOTIFY(NM_CLICK, IDC_BRANCH_LIST, OnReportItemClick)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
	ON_WM_CTLCOLOR()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


// CBranchListDlg 메시지 처리기입니다.

BOOL CBranchListDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();

	m_lst.InsertColumn(0, "지사", LVCFMT_LEFT, 130);
	//m_lst.InsertColumn(1, "전화번호", LVCFMT_LEFT, 100);
	m_lst.ShowHeader(FALSE);
	m_lst.Populate();
	m_lst.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_lst.GetPaintManager()->m_strNoItems = "";
	m_lst.InsertSearchAllColumn(0);
	m_lst.InsertSearchAllColumn(1); 
 
	m_lst.GetPaintManager()->m_bHideSelection = TRUE;
 
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CBranchListDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if(!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridSelectedRows *pRows = m_lst.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

	CBranchInfo *info = (CBranchInfo*)m_lst.GetItemData(pRecord);

	m_pBranchSel->SetCompany(info->nCompanyCode);
	m_pBranchSel->SendChangeBranchInfToParent();
	OnBnClickedCloseBtn();
}

void CBranchListDlg::OnBnClickedCloseBtn()
{
	ShowWindow(FALSE);
}

HBRUSH CBranchListDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd == this)
	{
		return m_HandleManager.GetBrushObject(RGB(255, 255, 255));
	}
	
	if(pWnd->GetDlgCtrlID() == IDC_BRANCH_SELECT_STATIC)
		pDC->SetBkColor(RGB(255, 255, 255));

	return hbr;
}

void CBranchListDlg::OnSetFocus(CWnd* pOldWnd)
{
	CMyDialog::OnSetFocus(pOldWnd);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
