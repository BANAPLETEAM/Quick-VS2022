#include "StdAfx.h"
#include "resource.h"
#include "MakeBranchCombo.h"
#include "MainFrm.h"
#include "ComboBranchListDlg.h"

CMakeBranchCombo::CMakeBranchCombo(void)
{
	m_pDlg = NULL;
	m_pParent = NULL;
}

CMakeBranchCombo::~CMakeBranchCombo(void)
{
	if(m_pDlg != NULL)
	{
		delete m_pDlg;
		m_pDlg = NULL;
	}
}

void CMakeBranchCombo::InitBranchCombo(CMainBranchCombo *pMainCombo, CEdit *pEdtBranch, CButton *pBtn)
{
	m_cmbMain = pMainCombo;
	m_edtSub = (CFlatEdit2*)pEdtBranch;
	m_btnSel = pBtn;

	m_cmbMain->SetParent(this);

	CXTPTaskPanel *pTaskPane = LU->GetTaskPanel();

	if(pTaskPane)
	{
		m_cmbMain->ResetContent();
		m_cmbMain->InsertString(0, "- 전체 -");

		m_edtSub->SetWindowText("- 전체 -");
		m_edtSub->SetMyFont("돋움", 13, FW_NORMAL); 
		m_edtSub->SetGradientBK();

		long nCount = pTaskPane->GetGroupCount(); 

		CXTPTaskPanelItems *pItems = NULL;
		pItems = pTaskPane->GetGroups();

		long nItem = 1;

		for(int i=0; i<nCount; i++) 
		{   
			CXTPTaskPanelItem *pItem = pItems->GetAt(i); 

			if(pItem)
			{
				CXTPTaskPanelGroupItem* pSubItem = pItem->GetItemGroup()->GetAt(0);
				m_cmbMain->InsertString(nItem, pItem->GetCaption());
				m_cmbMain->SetItemData(nItem++, (DWORD)pItem);
			}
		}

		m_cmbMain->SetCurSel(0);
	}
}

void CMakeBranchCombo::OnMainSelChange()
{
	m_mapBranchPane.clear();

	long nIndex = m_cmbMain->GetCurSel();

	if(nIndex < 0) return; 

	CXTPTaskPanelItem* pItem = (CXTPTaskPanelItem*)m_cmbMain->GetItemData(nIndex);

	if(pItem) 
	{ 
		long nItem = 0; 

		CXTPTaskPanelGroup *pGroup = pItem->GetItemGroup();

		for(int i=0; i<pGroup->GetItemCount(); i++)
		{ 
			CXTPTaskPanelGroupItem* pSubItem = pGroup->GetAt(i);
			ST_BRANCH_PANE_INFO *pData = (ST_BRANCH_PANE_INFO*)pSubItem->GetItemData();

			if(pData->pBi->bIntegrated)
				continue;

			m_mapBranchPane[nItem++] = pData;
 		}
	} 

	ChangeSubSel(m_mapBranchPane[0], "- 전체 -", 0);

	if(m_pDlg != NULL)
		m_pDlg->ShowWindow(FALSE);
}

void CMakeBranchCombo::GetVirtualCode(long &nVirtualCompany, BOOL &bIntegrated, CString &sCodeList)
{
	if(m_cmbMain->GetCurSel() <= 0)
	{
		nVirtualCompany = m_ci.m_nCompanyCode;
		bIntegrated = TRUE;
		return;
	}

	nVirtualCompany = m_BranchPaneInfo->nVirtualCompany == 0 ? 
			m_BranchPaneInfo->pBi->nCompanyCode : m_BranchPaneInfo->nVirtualCompany;

	if(nVirtualCompany > 100000 || m_nSelIndex == 0)
		bIntegrated = TRUE;
	else
		bIntegrated = FALSE;


	//if(nVirtualCompany > 100000) // || nVirtualCompany == m_ci.m_nCompanyCode)
	//	bIntegrated = TRUE;
	//else
	//	bIntegrated = FALSE;

	sCodeList = m_BranchPaneInfo->pBi->strCodeList;
} 

void CMakeBranchCombo::CloseBranchDlg()
{
	if(m_pDlg)
		m_pDlg->OnBnClickedCloseBtn();
}

void CMakeBranchCombo::OpenBranchDlg(const CWnd *pwndZOrder)
{
	if(m_pDlg == NULL) 
	{
		m_pDlg = new CComboBranchListDlg();
		m_pDlg->Create(IDD_COMBO_BRANCH_LIST_DLG);
		m_pDlg->m_pParent = this;
	}

	CRect rcDlg, rcCombo, rcBtn;

	m_edtSub->GetWindowRect(rcCombo);
	m_pDlg->GetWindowRect(rcDlg);
	m_btnSel->GetWindowRect(rcBtn);

	long nSize = m_mapBranchPane.size();

	if(m_cmbMain->GetCount() == 2) //2개로 불리 안된업체
		nSize++;
 
	rcDlg.top = rcCombo.bottom + 1; 
	rcDlg.left = rcCombo.left;
	rcDlg.right = rcBtn.right;  
	rcDlg.bottom = rcDlg.top +  (nSize * 19) + 25;

	if(rcDlg.bottom - rcDlg.top > 600)
		rcDlg.bottom = rcDlg.top + 600;

	m_pDlg->MoveWindow(rcDlg);
	rcDlg.DeflateRect(1, 1);
	m_pDlg->ScreenToClient(rcDlg);
	rcDlg.top += 20;
	m_pDlg->m_lstBranch.MoveWindow(rcDlg);
	m_pDlg->Invalidate();

	m_pDlg->RefreshList();
 
	m_pDlg->SetForegroundWindow();
	m_pDlg->ShowWindow(SW_SHOW);

	if(pwndZOrder != NULL)
		m_pDlg->SetWindowPos(pwndZOrder, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}

void CMakeBranchCombo::ChangeSubSel(ST_BRANCH_PANE_INFO *pInfo, CString sBranchName, long nIndex)
{
	if(pInfo != NULL)
	{
		m_nSelIndex = nIndex;
		m_BranchPaneInfo = pInfo;
		m_edtSub->SetWindowText(sBranchName);

		long nTextColor = pInfo->pBi->nRcpTextColor;
		long nGroundColor = pInfo->pBi->nRcpColor;

		if(nTextColor == nGroundColor)
		{
			nGroundColor = RGB(255 - nGroundColor, 255 - nGroundColor, 255 - nGroundColor);
		}

		m_edtSub->SetUserOption(RGB(GetRValue(nTextColor), GetGValue(nTextColor), GetBValue(nTextColor)),
			RGB(GetRValue(nGroundColor), GetGValue(nGroundColor), GetBValue(nGroundColor)));
	}
	else
	{
		m_edtSub->SetWindowText(sBranchName);
		m_edtSub->SetUserOption(RGB(0, 0,0), RGB(255, 255, 255));
	}

	if(m_pParent != NULL)
	{
		m_pParent->SendMessage(WM_CHANGE_BRANCH_ALL_CODE, (WPARAM)0, (LPARAM)0);
	}	
}
