#include "StdAfx.h"
#include "resource.h"
#include "BranchSel.h"
#include "BranchMainListDlg.h"
#include "BranchSubListDlg.h"
#include "BranchListDlg.h"

#define MAIN_LIST m_pMainListDlg->m_lst
#define SUB_LIST m_pSubListDlg->m_lst
#define ALL_LIST m_pBranchListDlg->m_lst

#define SCROLL_SIZE 18

CBranchSel::CBranchSel()
{ 
	m_pBi = NULL;
	m_pMainListDlg = NULL;
	m_pSubListDlg = NULL;
	m_pBranchListDlg = NULL;
	m_bOneSite = FALSE;
}

CBranchSel::~CBranchSel(void)
{
	if(m_pMainListDlg != NULL)
	{
		delete m_pMainListDlg;
		m_pMainListDlg = NULL;
	}

	if(m_pSubListDlg != NULL)
	{
		delete m_pSubListDlg;
		m_pSubListDlg = NULL;
	}

	if(m_pBranchListDlg != NULL)
	{
		delete m_pBranchListDlg;
		m_pBranchListDlg = NULL;
	}
}

void CBranchSel::MakeDialog()
{
	if(m_pMainListDlg == NULL)
	{
		m_pMainListDlg = new CBranchMainListDlg;
		m_pMainListDlg->Create(IDD_BRANCH_MAIN_LIST_DLG);
		m_pMainListDlg->m_pBranchSel = this;
		MAIN_LIST.SetItemLongHasBranchInfo();
		MAIN_LIST.ShowScrollBar(SB_HORZ, FALSE);
	}

	if(m_pSubListDlg == NULL)
	{
		m_pSubListDlg = new CBranchSubListDlg;
		m_pSubListDlg->Create(IDD_BRANCH_SUB_LIST_DLG);
		m_pSubListDlg->m_pBranchSel = this;
		SUB_LIST.ShowScrollBar(SB_HORZ, FALSE);
	}

	if(m_pBranchListDlg == NULL)
	{
		m_pBranchListDlg = new CBranchListDlg;
		m_pBranchListDlg->Create(IDD_BRANCH_LIST_DLG);
		m_pBranchListDlg->m_pBranchSel = this;
		ALL_LIST.ShowScrollBar(SB_HORZ, FALSE);
	}
}

void CBranchSel::InitData(CEdit *pMainEdt, CEdit *pSubEdt, CButton *pMainBtn, CButton *pSubBtn, CEdit *pSearchEdt)
{
	MakeDialog();

	m_btnMain = (CBranchMainBtn*)pMainBtn; 
	m_btnMain->m_pParent = this;
	m_btnSub = (CBranchSubBtn*)pSubBtn; 
	m_btnSub->m_pParent = this;

	m_edtMain = (CFlatMainEdit*)pMainEdt; 
	m_edtMain->m_pParent = this;

	m_edtSub = (CFlatSubEdit*)pSubEdt; 
	m_edtSub->m_pParent = this;
	m_pSearchEdt = (CFlatBranchEdit*)pSearchEdt;

	m_edtMain->SetGradientBK(TRUE, 30);
	m_edtSub->SetGradientBK(TRUE, 30);
	
	if(m_pSearchEdt != NULL)
	{
		m_pSearchEdt->m_pParent = this; 
		m_pSearchEdt->SetGradientBK(TRUE);
	}

	m_edtMain->SetMyFont("맑은 고딕", 17, FW_NORMAL);  
	m_edtSub->SetMyFont("맑은 고딕", 15, FW_NORMAL);  

	m_map.clear();
	long nCount = 0;

	if(LU->GetTaskPanel())
	{
		nCount = LU->GetTaskPanel()->GetGroupCount(); 
		CXTPTaskPanelItems *pItems = NULL;
		pItems = LU->GetTaskPanel()->GetGroups();

		long nItem = 0;

		for(int i=0; i<nCount; i++) 
		{   
			CXTPTaskPanelItem *pItem = pItems->GetAt(i); 

			if(pItem) 
			{
				ST_BRANCH_INFO st;
				st.nCount = 0;

				CXTPTaskPanelGroup *pGroup = pItem->GetItemGroup();

				for(int i=0; i<pGroup->GetItemCount(); i++)
				{
					CXTPTaskPanelGroupItem* pSubItem = pGroup->GetAt(i);
					ST_BRANCH_PANE_INFO *pData = (ST_BRANCH_PANE_INFO*)pSubItem->GetItemData();

					if(pData->pBi->bIntegrated)
						continue;

					//if(pData->pBi->nVirtualCompany > 100000)
					//	continue;

					st.pBiPane[st.nCount++] = pData;

					if(m_pSearchEdt == NULL)
						ALL_LIST.InsertItem(nItem, pData->pBi->strBranchName);
					else
						ALL_LIST.InsertItem(nItem, pData->pBi->strBranchName + " (" + LF->GetDashPhoneNumber(pData->pBi->strPhone) + ")");

					ALL_LIST.SetItemData(nItem++, (DWORD)pData->pBi);				
				}

				m_map[pItem] = st;
			}
		}
	}
	else
	{
		
	}

	ALL_LIST.Populate();

	if(nCount == 0)
	{ 
		m_pBi = LF->GetCurBranchInfo();

		if(m_bSendParentBranchChangeInfo)
			SendChangeBranchInfToParent();
	}

	if(nCount <= 1)
	{
		m_bOneSite = TRUE;
		ReLocateControl();
	}

	InsertMainData();
}

void CBranchSel::ReLocateControl()
{
	CRect rcMainEdt, rcSubEdt; 

	m_edtMain->GetWindowRect(rcMainEdt);
	m_edtSub->GetWindowRect(rcSubEdt);
	m_pParent->ScreenToClient(rcMainEdt);
	m_pParent->ScreenToClient(rcSubEdt);

	m_edtMain->ShowWindow(FALSE);
	m_btnMain->ShowWindow(FALSE);

	rcSubEdt.left = rcMainEdt.left;

	m_edtSub->MoveWindow(rcSubEdt);

}

void CBranchSel::InsertMainData()
{
	MAP_BRANCH::iterator it;
	long nItem = 0;
	
	for(it = m_map.begin(); it != m_map.end(); it++)
	{
		MAIN_LIST.InsertItem(nItem, it->first->GetCaption());
		MAIN_LIST.SetItemData(nItem, (DWORD)it->first);
		MAIN_LIST.SetItemLong(nItem, (DWORD)it->second.pBiPane[0]->pBi);

		if(nItem++ == 0)
		{
			ChangeMainBranch(it->first);
			m_edtMain->SetWindowText(it->first->GetCaption());
		}
	}

	MAIN_LIST.Populate();
}

void CBranchSel::ChangeMainBranch(CXTPTaskPanelItem *pItem, BOOL bFirstSelect)
{
	if(pItem) 
	{
		SUB_LIST.DeleteAllItems();

		for(int i=0; i<m_map[pItem].nCount; i++)
		{
			CBranchInfo *pBi = m_map[pItem].pBiPane[i]->pBi;

			if(m_pSearchEdt == NULL)
				SUB_LIST.InsertItem(i, pBi->strBranchName);
			else
				SUB_LIST.InsertItem(i, pBi->strBranchName + " (" + LF->GetDashPhoneNumber(pBi->strPhone) + ")");

			SUB_LIST.SetItemData(i, (DWORD)pBi);

			if(bFirstSelect == TRUE)
			{
				if(i==0)
				{
					m_pBi = pBi;
					SetEditTextColor();

					if(m_bSendParentBranchChangeInfo)
						SendChangeBranchInfToParent();
				}
			}
		}

		SUB_LIST.Populate();
	}	

	CBranchInfo *pBi = m_map[pItem].pBiPane[0]->pBi;
	m_edtMain->SetWindowText(pItem->GetCaption());
	if(pBi)
		m_edtMain->SetUserOption(pBi->nRcpTextColor, pBi->nRcpColor, pItem->GetCaption());
}

void CBranchSel::SetEditTextColor() 
{
	long nTextColor = m_pBi->nRcpTextColor;
	long nGroundColor = m_pBi->nRcpColor; 

	if(nTextColor == nGroundColor)
		nGroundColor = RGB(255 - nGroundColor, 255 - nGroundColor, 255 - nGroundColor);

	m_edtSub->SetWindowText(m_pBi->strBranchName + " (" + LF->GetDashPhoneNumber(m_pBi->strPhone) + ")");
	m_edtSub->SetUserOption(RGB(GetRValue(nTextColor), GetGValue(nTextColor), GetBValue(nTextColor)),
		RGB(GetRValue(nGroundColor), GetGValue(nGroundColor), GetBValue(nGroundColor)));
}

void CBranchSel::ChangeSubBranch()
{
	CXTPGridSelectedRows *pRows = SUB_LIST.GetSelectedRows();
	
	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

	m_pBi = (CBranchInfo*)SUB_LIST.GetItemData(pRecord);

	SetEditTextColor();

	if(m_bSendParentBranchChangeInfo)
		SendChangeBranchInfToParent();

	m_pSubListDlg->ShowWindow(FALSE);
}

void CBranchSel::OpenMainListDlg()
{
	if(m_pMainListDlg == NULL)  
		return; 

	m_pSubListDlg->ShowWindow(FALSE);
	m_pBranchListDlg->ShowWindow(FALSE);
   
	CRect rcDlg, rcMainEdt, rcMainBtn;

	m_pMainListDlg->GetWindowRect(rcDlg);
	m_edtMain->GetWindowRect(rcMainEdt);
	m_btnMain->GetWindowRect(rcMainBtn);

	long nSize = MAIN_LIST.GetVisibleItemCount();

	rcDlg.top = rcMainEdt.bottom + 1; 
	rcDlg.left = rcMainEdt.left; 
	rcDlg.right = rcMainBtn.right;  
	rcDlg.bottom = rcDlg.top +  ((nSize + 1) * 19) + 25; //메인브렌치는 왼쪽 스크롤 절대 못생기게

	if(rcDlg.bottom - rcDlg.top > 600)
		rcDlg.bottom = rcDlg.top + 600;

	m_pMainListDlg->MoveWindow(rcDlg);
	rcDlg.DeflateRect(1, 1);
	m_pMainListDlg->ScreenToClient(rcDlg);
	rcDlg.top += 20;
	MAIN_LIST.MoveWindow(rcDlg); 

	CXTPGridColumn *pColumn = MAIN_LIST.GetColumns()->GetAt(0);
	pColumn->SetWidth(rcDlg.Width());
	
	CRect rcBtn;
	m_pMainListDlg->m_btnClose.GetWindowRect(rcBtn);
	m_pMainListDlg->ScreenToClient(rcBtn);

	long nBtnWidth = rcBtn.Width();
	rcBtn.right = rcDlg.right;
	rcBtn.left = rcBtn.right - nBtnWidth;
	m_pMainListDlg->m_btnClose.MoveWindow(rcBtn);
 
	m_pMainListDlg->Invalidate();    
	m_pMainListDlg->SetForegroundWindow(); 
	m_pMainListDlg->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	m_pMainListDlg->SetFocus(); 
	m_pMainListDlg->ShowWindow(SW_SHOW);  
	//MAIN_LIST.SetFocus(); 
}

void CBranchSel::OpenSubListDlg()
{
	if(m_pSubListDlg == NULL)
		return;

	m_pMainListDlg->ShowWindow(FALSE);
	m_pBranchListDlg->ShowWindow(FALSE);

	CRect rcDlg, rcSubEdt, rcSubBtn, rcSearchEdt;

	m_pSubListDlg->GetWindowRect(rcDlg);
	m_edtSub->GetWindowRect(rcSubEdt);
	m_btnSub->GetWindowRect(rcSubBtn);

	if(m_pSearchEdt != NULL) 
		m_pSearchEdt->GetWindowRect(rcSearchEdt);

	long nSize = SUB_LIST.GetVisibleItemCount();

	rcDlg.top = rcSubEdt.bottom + 1; 
	rcDlg.left = rcSubEdt.left;
	rcDlg.right = rcSubBtn.right;  
	rcDlg.bottom = rcDlg.top +  (nSize * 19) + 25;
  
	if((m_pSearchEdt != NULL) && (m_bOneSite == FALSE)) 
		rcDlg.right = rcSearchEdt.right;//검색버튼 있으면 박스를 더 크게 연다

	if(rcDlg.bottom - rcDlg.top > 600)
	{
		rcDlg.bottom = rcDlg.top + 600;
	} 

	m_pSubListDlg->MoveWindow(rcDlg);
	rcDlg.DeflateRect(1, 1); 
	m_pSubListDlg->ScreenToClient(rcDlg);
	rcDlg.top += 20;
	SUB_LIST.MoveWindow(rcDlg);

	CXTPGridColumn *pColumn = SUB_LIST.GetColumns()->GetAt(0);
	pColumn->SetWidth(rcDlg.Width() - SCROLL_SIZE);
  
	
	CRect rcBtn;
	m_pSubListDlg->m_btnClose.GetWindowRect(rcBtn);
	m_pSubListDlg->ScreenToClient(rcBtn);

	long nBtnWidth = rcBtn.Width();
	rcBtn.right = rcDlg.right;
	rcBtn.left = rcBtn.right - nBtnWidth;
	m_pSubListDlg->m_btnClose.MoveWindow(rcBtn);

	m_pSubListDlg->Invalidate();    
	m_pSubListDlg->SetForegroundWindow(); 
	m_pSubListDlg->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	m_pSubListDlg->SetFocus(); 
	m_pSubListDlg->ShowWindow(SW_SHOW);  
	//m_pSubListDlg->SetFocus();
}

void CBranchSel::OpenAllBranchListDlg()
{
	if(m_pBranchListDlg == NULL)
		return;

	m_pMainListDlg->ShowWindow(FALSE);
	m_pSubListDlg->ShowWindow(FALSE);
	
	CRect rcDlg, rcMainEdt, rcSubBtn;

	m_pBranchListDlg->GetWindowRect(rcDlg);
	m_edtMain->GetWindowRect(rcMainEdt);
	m_btnSub->GetWindowRect(rcSubBtn);

	long nSize = ALL_LIST.GetRecords()->GetCount();

	rcDlg.top = rcMainEdt.bottom + 1; 
	rcDlg.left = rcMainEdt.left;
	rcDlg.right = rcSubBtn.right;  
	rcDlg.bottom = rcDlg.top +  (nSize * 19) + 25;

	if(rcDlg.bottom - rcDlg.top > 600)
		rcDlg.bottom = rcDlg.top + 600;

	m_pBranchListDlg->MoveWindow(rcDlg);
	rcDlg.DeflateRect(1, 1);
	m_pBranchListDlg->ScreenToClient(rcDlg);
	rcDlg.top += 20;
	ALL_LIST.MoveWindow(rcDlg);

	CXTPGridColumn *pColumn = ALL_LIST.GetColumns()->GetAt(0);
	pColumn->SetWidth(rcDlg.Width() - SCROLL_SIZE);

	CRect rcBtn;
	m_pBranchListDlg->m_btnClose.GetWindowRect(rcBtn);
	m_pBranchListDlg->ScreenToClient(rcBtn);

	long nBtnWidth = rcBtn.Width();
	rcBtn.right = rcDlg.right;
	rcBtn.left = rcBtn.right - nBtnWidth;
	m_pBranchListDlg->m_btnClose.MoveWindow(rcBtn);

	m_pBranchListDlg->Invalidate();    
	m_pBranchListDlg->SetForegroundWindow(); 
	m_pBranchListDlg->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	m_pBranchListDlg->SetFocus();  
	m_pBranchListDlg->ShowWindow(SW_SHOW);  
}  

void CBranchSel::CloseMainListDlg()
{
	if(m_pMainListDlg != NULL)
		m_pMainListDlg->ShowWindow(FALSE);
}


void CBranchSel::SendChangeBranchInfToParent()
{
	m_pParent->SendMessage(WM_CHANGE_BRANCH_CODE, (WPARAM)m_pBi, (LPARAM)0);
} 

CBranchInfo* CBranchSel::SetCompany(long nCompany)
{
	MAP_BRANCH::iterator it;
	long nItem = 0;

	for(it = m_map.begin(); it != m_map.end(); it++)
	{
		CXTPTaskPanelItem *pItem = it->first;
		ST_BRANCH_INFO st = it->second;

		for(int i=0; i<st.nCount; i++)
		{
			CBranchInfo *pInfo = st.pBiPane[i]->pBi;

			if(pInfo->nCompanyCode == nCompany) 
			{
				m_pBi = pInfo;
				m_edtMain->SetWindowText(pItem->GetCaption());
				SetEditTextColor();

				ChangeMainBranch(pItem, FALSE);

				//if(m_bSendParentBranchChangeInfo)
				//	SendChangeBranchInfToParent();

				return m_pBi;
			}
		}
	}

	return m_pBi;
}

void CBranchSel::SearchBranch(CString strSearch)
{
	CXTPGridRecords *pRecords = ALL_LIST.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++) 
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString strBranch = ALL_LIST.GetItemText(pRecord, 0);

		if(strBranch.Find(strSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	ALL_LIST.Populate(); 
	m_pSearchEdt->SetFocus();
}

BOOL CBranchSel::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_LBUTTONDOWN)
	{
		if(pMsg->hwnd == m_edtMain->GetSafeHwnd())
			OpenMainListDlg();
		else if(pMsg->hwnd == m_edtSub->GetSafeHwnd())
			OpenSubListDlg();
	}
	

	return CWnd::PreTranslateMessage(pMsg);
}
