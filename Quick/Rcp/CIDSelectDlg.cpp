#include "stdafx.h"
#include "resource.h"
#include "CIDSelectDlg.h"
#include "LogiUtil.h"
#include "RcpView.h"
#include "RcpPageCTIForm.h"


IMPLEMENT_DYNAMIC(CCIDSelectDlg, CMyDialog)
CCIDSelectDlg::CCIDSelectDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CCIDSelectDlg::IDD, pParent)
{
}

CCIDSelectDlg::~CCIDSelectDlg()
{
}

void CCIDSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_EDIT, m_edtMain);
	DDX_Control(pDX, IDC_SUB_EDIT, m_edtSub);
	DDX_Control(pDX, IDC_MAIN_BUTTON, m_btnMain);
	DDX_Control(pDX, IDC_SUB_BUTTON, m_btnSub);
	DDX_Control(pDX, IDC_BRANCH_LIST, m_lstBranch);
	DDX_Control(pDX, IDC_SEARCH_EDT, m_edtSearch);
}


BEGIN_MESSAGE_MAP(CCIDSelectDlg, CMyDialog)
	ON_EN_CHANGE(IDC_SEARCH_EDT, OnEnChangeSearchEdt)
	//ON_MESSAGE(WM_CHANGE_BRANCH_CODE, OnChangeBrachCode)
END_MESSAGE_MAP()



BOOL CCIDSelectDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_edtSearch.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtSearch.SetUserOption(RGB(0, 0, 0), RGB(245, 245, 245), "검 색");

	m_cBranch.SetParent(this, TRUE);
	m_cBranch.InitData(&m_edtMain, &m_edtSub, &m_btnMain, &m_btnSub);
	
	m_lstBranch.SetMapData(&m_cBranch);
	m_lstBranch.GetColumns()->GetAt(0)->SetWidth(0);
	m_lstBranch.Populate();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

/*LONG CCIDSelectDlg::OnChangeBrachCode(WPARAM wParam, LPARAM lParam)
{	
	CBranchInfo *pBi = m_cBranch.GetBranchInfo();

	return 0;
}*/

void CCIDSelectDlg::OnEnChangeSearchEdt()
{
	CString strSearch; m_edtSearch.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstBranch.GetRecords(); 

	for(int i=0; i<pRecords->GetCount(); i++)
	{ 
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		pRecord->SetVisible(TRUE);

		CXTPGridRecords *pChildRecords = pRecord->GetChilds();

		if(pChildRecords)
		{
			for(int i=0; i<pChildRecords->GetCount(); i++)
			{
				CXTPGridRecord_Branch *pChildRecord = (CXTPGridRecord_Branch*)pChildRecords->GetAt(i);

				CBranchInfo *pInfo = (CBranchInfo*)m_lstBranch.GetItemData(pChildRecord);

				if(pInfo->strBranchName.Find(strSearch) >= 0)
					pChildRecord->SetVisible(TRUE);
				else
					pChildRecord->SetVisible(FALSE);
			}
		}
	}

	m_lstBranch.Populate();
}

void CCIDSelectDlg::OnOK()
{
	CBranchInfo *pBi = m_cBranch.GetBranchInfo();
	LU->GetRcpView()->m_pCTIForm->SelectCID(pBi);
	
	CMyDialog::OnOK();
}