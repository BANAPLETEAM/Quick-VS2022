// ComboBranchListDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ComboBranchListDlg.h"
#include "MakeBranchCombo.h"
#include "GradientReportPaintManager.h"
//#include "chargedlg.h"

IMPLEMENT_DYNAMIC(CComboBranchListDlg, CMyDialog)

CComboBranchListDlg::CComboBranchListDlg(CWnd* pParent/*=NULL*/)
	: CMyDialog(CComboBranchListDlg::IDD, pParent)
{
}

CComboBranchListDlg::~CComboBranchListDlg()
{
}

void CComboBranchListDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX); 
	DDX_Control(pDX, IDC_BRANCH_LIST, m_lstBranch);
}


BEGIN_MESSAGE_MAP(CComboBranchListDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CComboBranchListDlg::OnBnClickedCloseBtn)
	ON_NOTIFY(NM_CLICK, IDC_BRANCH_LIST, OnReportItemClick)
END_MESSAGE_MAP()


// CComboBranchListDlg �޽��� ó�����Դϴ�.

BOOL CComboBranchListDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog(); 
 
	SetForegroundWindow();

	m_lstBranch.InsertColumn(0, "����", LVCFMT_LEFT, 105);
	m_lstBranch.ShowHeader(FALSE);
	m_lstBranch.SetPaintManager(new CGradientReportPaintManager);
	m_lstBranch.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_lstBranch.GetPaintManager()->m_strNoItems = "";
	m_lstBranch.Populate();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CComboBranchListDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if(!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	long nIndex = m_lstBranch.GetNextItem(-1, LVNI_SELECTED);
	ST_BRANCH_PANE_INFO *pBranchPaneInfo = (ST_BRANCH_PANE_INFO*)m_lstBranch.GetItemData(nIndex);
 	CString sBranch = m_lstBranch.GetItemText(nIndex, 0);

	m_pParent->ChangeSubSel(pBranchPaneInfo, sBranch, nIndex);	

	ShowWindow(FALSE);

}

void CComboBranchListDlg::RefreshList()
{
	m_lstBranch.DeleteAllItems();

	BRANCH_PANE_MAP::iterator it;
	long nItem = 0;
 
	for(it = m_pParent->m_mapBranchPane.begin(); it != m_pParent->m_mapBranchPane.end(); it++)
	{
		if(nItem == 0)
		{
			m_lstBranch.InsertItem(nItem, "- ��ü -"); 
			m_lstBranch.SetItemData(nItem++, (DWORD)it->second);

			if(m_pParent->m_mapBranchPane.size() > 1)
			{
				if(it->second->nVirtualCompany == 0)
				{
					m_lstBranch.InsertItem(nItem, it->second->pBi->strBranchName); 
					m_lstBranch.SetItemData(nItem++, (DWORD)it->second);
				}
			}

			continue;
		}
				
		m_lstBranch.InsertItem(nItem, it->second->pBi->strBranchName);
		m_lstBranch.SetItemData(nItem++, (DWORD)it->second);
	}

	m_lstBranch.Populate();
}
void CComboBranchListDlg::OnBnClickedCloseBtn()
{
	ShowWindow(FALSE);
}
