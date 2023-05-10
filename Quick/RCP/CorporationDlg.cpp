// TestDlg2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CorporationDlg.h"
//#include "GroupView.h"
#include "MyTestView.h"
#include "MyTestView1.h"
#include "MyTestView2.h"

#define WM_TAB_CLICK_EVENT WM_USER + 1000



//IMPLEMENT_DYNAMIC(CTabControl2, CXTPTabControl)

void CTabControl2::OnItemClick(CXTPTabManagerItem* pItem)
{
	CXTPTabControl::OnItemClick(pItem);

	GetParent()->PostMessage(WM_TAB_CLICK_EVENT,(WPARAM)NULL,(LPARAM)NULL);
	
}

IMPLEMENT_DYNAMIC(CCorporationDlg2, CXTResizeDialog)
CCorporationDlg2::CCorporationDlg2(CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CCorporationDlg2::IDD, pParent)
{
	m_nCustomerCompany = 0;
	m_bIntegrated = FALSE; 
	m_strSearch = "";
	m_nGNo = 0;
	m_bChild = FALSE;
	m_bPartView = FALSE;
	m_nCopyCNo = 0;
	m_nCopyGNo = 0;
	m_bReceipt = FALSE;
	m_nReceiptCNo = 0;
	m_bDragMode = FALSE;
	m_pPreRow = NULL;
	m_bBegin = FALSE;
}

CCorporationDlg2::~CCorporationDlg2()
{
}

void CCorporationDlg2::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_SEARCH_EDIT,m_strSearch);
	DDX_Control(pDX,IDC_SEARCH_EDIT,m_edtSearch);
	DDX_Control(pDX,IDC_GROUP_CUSTOM,m_GroupList);
	//DDX_Control(pDX,IDC_CUSTOMER_CUSTOM,m_MemberList);
	DDX_Control(pDX,IDC_REFERSH_BTN, m_btnServerRefresh);
	DDX_Control(pDX, IDC_STATIC_OPTION, m_stcOption);
}


BEGIN_MESSAGE_MAP(CCorporationDlg2, CXTResizeDialog)
	ON_NOTIFY(NM_CLICK,IDC_GROUP_CUSTOM,OnNMClickGroupList)
	//ON_NOTIFY(NM_CLICK,IDC_CUSTOMER_CUSTOM,OnNMClickMemberList)		
	ON_MESSAGE(WM_TAB_CLICK_EVENT, OnTabItemClick)	
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)	
	ON_COMMAND(ID_MEMBER_COPY, OnMenuClickedCopyBtn)
	ON_COMMAND(ID_MEMBER_PASTE, OnMenuClickedPasteColBtn)

	ON_COMMAND(ID_GROUP_OWNER, OnMenuClickedGroupOwnerBtn)
	ON_COMMAND(ID_RECEIPT, OnMenuClickedReceiptBtn)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_COPY_BTN, OnBnClickedCopyBtn)	
	ON_BN_CLICKED(IDC_PASTE_COL_BTN, OnBnClickedPasteColBtn)
	ON_BN_CLICKED(IDC_PASTE_ROW_BTN, OnBnClickedPasteRowBtn)
	ON_BN_CLICKED(IDC_MODIFY_BTN, OnBnClickedModifyBtn)
	ON_BN_CLICKED(IDC_RECEIPT_BTN, OnBnClickedReceiptBtn)
	ON_BN_CLICKED(IDC_GROUP_OWNER, OnBnClickedGroupOwner)
	ON_STN_CLICKED(IDC_SPLITTER1, OnStnClickedSplitter1)
	//ON_NOTIFY(IDC_GROUP_CUSTOM, OnLButtonUp)
	//ON_NOTIFY(LVN_BEGINDRAG, IDC_STATIC_OPTION, OnReportBeginDrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_NOTIFY(LVN_BEGINDRAG, IDC_GROUP_CUSTOM, OnReportBeginDrag)
END_MESSAGE_MAP()


// CTestDlg2 메시지 처리기입니다.

LONG CCorporationDlg2::OnTabItemClick(WPARAM wParam, LPARAM lParam)
{
	
	
	RefreshMember();	
	return 0;
}
BOOL CCorporationDlg2::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

		
	CRect rtSTATIC_OPTION;
	this->GetDlgItem(IDC_STATIC_OPTION)->GetWindowRect(rtSTATIC_OPTION);
	this->ScreenToClient(rtSTATIC_OPTION);
	this->GetDlgItem(IDC_STATIC_OPTION)->ShowWindow(SW_HIDE);

	LU->CreateFormViewTabControl(this, &m_wndTabControl, rtSTATIC_OPTION);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CMyTestView), "기본사항", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CMyTestView1), "위치/메모", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CMyTestView2), "정산(할인,마일)", 0);

	m_edtSearch.SetFontSize(14);
	CRect rc;
	CWnd* pWnd;

	pWnd = GetDlgItem(IDC_SPLITTER1);
	pWnd->GetWindowRect(rc);
	ScreenToClient(rc);
	m_wndSplitter1.Create(WS_CHILD | WS_VISIBLE, rc, this, IDC_SPLITTER1);
	m_wndSplitter1.SetRange(250, 250, -1);

	
	Refresh();
	if(m_bPartView)
		LocalRefeshGroup();
	
	SetResize(IDC_GROUP_CUSTOM, SZ_TOP_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_SPLITTER1, SZ_TOP_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_STATIC_OPTION, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_TABCONTROL,	SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	SetFlag(xtResizeNoClipChildren);
	m_edtSearch.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	
}

void CCorporationDlg2::RefreshMember()
{

	int nCur = m_wndTabControl.GetCurSel();
	if(m_GroupList.GetRecords()->GetCount() == 0)
		return;

	

	if(m_nGNo == 0)
	{
		CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)m_GroupList.GetRows()->GetAt(0)->GetRecord();
		m_nGNo = pRecord->GetItemDataLong();
		if(m_nGNo == 0) return;
	}

	switch(nCur)
	{
	case 0:
		{
			CMyTestView *pView = (CMyTestView*)GetTabItem(nCur);
			pView->SetGNo(m_nGNo);
			pView->SetChild(m_bChild);			
			pView->SetWnd(this);
			pView->Refresh();
			
		}
		break;
	case 1:
		{
			CMyTestView1 *pView = (CMyTestView1 *)GetTabItem(nCur);
			pView->SetGNo(m_nGNo);
			pView->SetChild(m_bChild);
			//pView->SetWnd(this);
			pView->Refresh();

		}
		break;
	case 2:
		{
			CMyTestView2 *pView = (CMyTestView2 *)GetTabItem(nCur);
			pView->SetGNo(m_nGNo);
			pView->SetChild(m_bChild);
			//pView->SetWnd(this);
			pView->Refresh();

		}
	    break;
	case 3:
		{
			CMyTestView *pView = (CMyTestView *)GetTabItem(nCur);
			pView->SetGNo(m_nGNo);
			pView->SetChild(m_bChild);
			pView->Refresh();
			
		}
	    break;	
	default:
		return;
	}
}

int CCorporationDlg2::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return 0;
	return CXTResizeDialog::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CCorporationDlg2::LocalRefeshGroup()
{
	//long nGNo; //nMembers, nParentGNo, nDepositRate, , nTreeGNo
	CString strGroupName, strDetail,sID,  strPassword,  sDept, sMemberTel, sName, sChargeName;

	if(m_nGNo <= 0)
	{
		m_GroupList.ShowAllRow();
		return;
	}	
	long nGNoKey = m_cg.GetGroupData(m_nGNo)->nGNoKey;
	//CUSTOMER_GROUP_MAP custMap;
	//custMap = m_cg.SearchParentAllGroup(m_nGNo);

	for(int nRow = 0; nRow < m_GroupList.GetRecords()->GetCount(); nRow++)
	{
		CMyXTPGridRecord *pRecord = m_GroupList.GetRecordsGetAt(nRow);
		if(pRecord == NULL)
		{
			MsgBox("작업중 오류 로지소프트로 문의하세요");
			return;
		}
		
		
		if(nGNoKey == pRecord->m_nTreeParentNo)
			m_GroupList.ShowRecord(pRecord);	
		else
			m_GroupList.HideRecord(pRecord);

		
	}
	m_GroupList.Populate();
	/*
	CUSTOMER_GROUP_VEC::iterator it;
	CUSTOMER_GROUP_VEC *pVec;


	for(it = pVec->begin(); it != pVec->end(); ++ it)	
	{	

		nGNo = (*it)->nGNo;		

		m_GroupList.TreeChildAddItem(0,m_cg.GetGroupData(nGNo)->sGroupName,	"그룹이름", 110,FALSE,DT_LEFT);
		m_GroupList.MyAddItem(1,m_cg.GetGroupData(nGNo)->sDept,					"부서명",	60,FALSE,DT_LEFT);
		m_GroupList.MyAddItem(2,m_cg.GetGroupData(nGNo)->sChargeName,			"법인요금", 60,FALSE,DT_LEFT);				
		m_GroupList.SetItemDataLong(m_cg.GetGroupData(nGNo)->nGNo);
		m_GroupList.SetItemDataLong2(m_cg.GetGroupData(nGNo)->nGroupOwner);

		m_GroupList.EndItem();	

	}
	*/


}

void CCorporationDlg2::Refresh()
{
	m_GroupList.DeleteAllItem();

	CString strGroupName, strDetail,sID,  strPassword, strDept, strMemberTel, strName, strChargeName;

	long  nCharge = 0;

	//m_nSelGroupID = 0;
	
	m_GroupList.DeleteAllItem();
	MAP_CUSTOMER_GROUP::iterator it;

	for(it = m_cg.GetGroup()->begin(); it != m_cg.GetGroup()->end(); ++it)
	{
		if(it->second->strGroupName.GetLength() == 0)
			continue;

		m_GroupList.TreeChildDepthAddItem(0, it->second->strKeyRef, it->second->nGNoKey, it->second->strGroupName,"그룹이름", 140, FALSE, DT_LEFT);
		m_GroupList.MyCheckAddItem(1, FALSE,"All",30, DT_CENTER,it->second->strKeyRef.GetLength() == 0 ? TRUE : FALSE);
		m_GroupList.MyAddItem(2, it->second->strDept,"부서",80, FALSE, DT_LEFT);
		m_GroupList.MyAddItem(3, m_mapChargeType[it->second->nCharge].strChargeName, "법인요금", 90, FALSE, DT_LEFT);		
		m_GroupList.InsertItemDataLong(it->first);
		m_GroupList.InsertItemDataLong2(it->second->nGroupOwner);
		m_GroupList.EndItem();
	}

	m_GroupList.Populate();
	if(m_GroupList.GetRows()->GetCount() > 0)
	{
		m_GroupList.SetSelectedRow(0);
		RefreshMember();
	}
}

CWnd* CCorporationDlg2::GetTabItem(CString strCaption)
{
	CXTPTabPaintManager* pXTPTabPaintManager =  m_wndTabControl.GetPaintManager();
	int nTabCount = m_wndTabControl.GetItemCount();
	for(int nTab = 0;nTab < nTabCount;nTab++)
	{
		CXTPTabManagerItem* pXTPTabManagerItem =  m_wndTabControl.GetItem(nTab);
		if(strCaption ==  pXTPTabManagerItem->GetCaption() )
		{
			CWnd* pWnd =  FromHandle(pXTPTabManagerItem->GetHandle());
			return pWnd;
		}
	}

	return NULL;
}

CWnd* CCorporationDlg2::GetTabItem(int nTab)
{
	CXTPTabPaintManager* pXTPTabPaintManager =  m_wndTabControl.GetPaintManager();
	int nTabCount = m_wndTabControl.GetItemCount();
	if(nTab >= nTabCount) return NULL;

	CXTPTabManagerItem* pXTPTabManagerItem =  m_wndTabControl.GetItem(nTab);

	CWnd* pWnd =  FromHandle(pXTPTabManagerItem->GetHandle());
	return pWnd;
}


void CCorporationDlg2::OnNMClickGroupList(NMHDR *pNMHDR, LRESULT *pResult)
{

	XTP_NM_REPORTRECORDITEM* pNMListView = (XTP_NM_REPORTRECORDITEM*)pNMHDR;
	if (!pNMListView->pRow || !pNMListView->pColumn)
		return;

	int nCol = pNMListView->pColumn->GetIndex();

	if(m_GroupList.GetSelectedCount() == 0)
		return;

	int nItem = m_GroupList.GetSelectedRow()->GetIndex();
	if(nItem < 0)
		return;
	if(pNMListView->pRow == NULL)
		return;

	int nRow = pNMListView->pRow->GetIndex();
	if(nCol == 1)  // TotalColumn
	{
		BOOL bCheck = m_GroupList.GetItemCheck(nRow,nCol);
		
		for(int i = 0; i < m_GroupList.GetRecords()->GetCount(); i++)
		{
			/*CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)m_GroupList.GetRecords()->GetAt(i);
			long nGNo = pRecord->GetItemDataLong();
			if(nGNo ==  )*/

		}
	}

	m_nGNo = m_GroupList.GetItemDataLong(nItem);	
	CXTPGridRecordItem *pItem = m_GroupList.GetSelectedRecord()->GetItem(1);	
	m_bChild =  pItem->IsChecked() ? TRUE : FALSE;
		//>HasChildren() ? TRUE : FALSE;
	
	RefreshMember();
	*pResult = 0;
}





void CCorporationDlg2::OnEnChangeSearchEdit()
{
	
	CString strSearchWord = "";
	m_edtSearch.GetWindowText(strSearchWord);

	if(strSearchWord.GetLength() == 0)
	{
		m_GroupList.ShowAllRow();
		return;
	}
	
	CMyXTPGridRecord *pRecord = NULL;
	VEC_CUSTOMER_GROUP::iterator it;
		
	CUIntArray *pIntArray;
	pIntArray = m_cg.SearchParentAllGroup(strSearchWord,8);	
	if(pIntArray == NULL)
	{
		m_GroupList.ShowAllRow();
		return;
	}

	if(pIntArray->GetCount() == 0)
	{
		if(pIntArray)
		{
			delete pIntArray;
			return;
		}
	}

	for(int i = 0; i < m_GroupList.GetRecords()->GetCount(); i++)
	{
		pRecord = (CMyXTPGridRecord *)m_GroupList.GetRecords()->GetAt(i);			

		for(int j=0; j < pIntArray->GetCount(); j++)
		{
			
			if(pRecord->GetItemDataLong() == pIntArray->GetAt(j))
				pRecord->SetVisible(TRUE);						
			else
				pRecord->SetVisible(FALSE);
		}
	}
	if(pIntArray)
		delete pIntArray;

	m_GroupList.ExpandAll();
	m_GroupList.Populate();
}

void CCorporationDlg2::SetGNo(long nGNo)
{
	m_nGNo = nGNo;
}

//ON_COMMAND(ID_MEMBER_ALL_PASTE, OnMenuClickedPasteRowBtn)
void CCorporationDlg2::OnMenuClickedPasteColBtn()
{
	OnBnClickedPasteColBtn();
}
void CCorporationDlg2::OnMenuClickedCopyBtn()
{

	OnBnClickedCopyBtn();
}

void CCorporationDlg2::DoResize1(int delta)
{

	CSplitterControl::ChangeWidth(&m_GroupList, delta);
	//CSplitterControl::ChangeWidth(&m_stcOption, delta);

	
	CSplitterControl::ChangeWidth(&m_wndTabControl, -delta, CW_RIGHTALIGN);
		//GetDlgItem(IDC_TABCONTROL);
	CSplitterControl::ChangeWidth(&m_stcOption, -delta, CW_RIGHTALIGN);

	Invalidate();
	UpdateWindow();

}

LRESULT CCorporationDlg2::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_NOTIFY)
	{
		if (wParam == IDC_SPLITTER1)
		{	
			SPC_NMHDR* pHdr = (SPC_NMHDR*) lParam;
			DoResize1(pHdr->delta);
		}

	}

//	return 0L;
	return CXTResizeDialog::WindowProc(message, wParam, lParam);
}


void CCorporationDlg2::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;	

	if(m_wndTabControl.GetSafeHwnd() > 0)
	{
		
		if(pWnd->GetSafeHwnd() != m_wndTabControl.GetSafeHwnd() )
			return;

		CMenu rMenu;
		rMenu.LoadMenu(IDR_GROUP_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(1);


		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

	}

}

void CCorporationDlg2::OnBnClickedCopyBtn()
{


	try
	{
		int nCur = m_wndTabControl.GetCurSel();
		CDataBox m_Data;
		switch(nCur)
		{
		case 0:
			{
				CMyTestView *pView1 = (CMyTestView *)GetTabItem(nCur);
				CDataBox &m_Data = pView1->GetDataCtrl();
				if(pView1->GetDataCtrl().GetSelectedCount() == 0)
					throw("복사하실 행을 선택하세요");	
				if(m_Data.GetSelectedCount() == 0)
				{
					MessageBox("복사하실 행을 선택하세요", "확인", MB_ICONINFORMATION);
					return;
				}
				m_nCopyCNo = m_Data.GetItemDataLong(m_Data.GetSelectedRecord()->GetIndex());
				m_nCopyGNo = m_Data.GetItemDataLong2(m_Data.GetSelectedRecord()->GetIndex());
			}					
			break;
		case 1:
			{
				CMyTestView1 *pView2 = (CMyTestView1 *)GetTabItem(nCur);
				CDataBox &m_Data = pView2->GetDataCtrl();
				if(m_Data.GetSelectedCount() == 0)
				{
					MessageBox("복사하실 행을 선택하세요", "확인", MB_ICONINFORMATION);
					return;
				}
				m_nCopyCNo = m_Data.GetItemDataLong(m_Data.GetSelectedRecord()->GetIndex());
				m_nCopyGNo = m_Data.GetItemDataLong2(m_Data.GetSelectedRecord()->GetIndex());
			}
			
			break;
		case 2:
			{
				CMyTestView2 *pView3 = (CMyTestView2 *)GetTabItem(nCur);
				CDataBox &m_Data = pView3->GetDataCtrl();
				if(m_Data.GetSelectedCount() == 0)
				{
					MessageBox("복사하실 행을 선택하세요", "확인", MB_ICONINFORMATION);
					return;
				}
				m_nCopyCNo = m_Data.GetItemDataLong(m_Data.GetSelectedRecord()->GetIndex());
				m_nCopyGNo = m_Data.GetItemDataLong2(m_Data.GetSelectedRecord()->GetIndex());
			}
			
			break;
		case 3:
			{
				CMyTestView *pView4 = (CMyTestView *)GetTabItem(nCur);
				CDataBox &m_Data = pView4->GetDataCtrl();
				if(m_Data.GetSelectedCount() == 0)
				{
					MessageBox("복사하실 행을 선택하세요", "확인", MB_ICONINFORMATION);
					return;
				}
				m_nCopyCNo = m_Data.GetItemDataLong(m_Data.GetSelectedRecord()->GetIndex());
				m_nCopyGNo = m_Data.GetItemDataLong2(m_Data.GetSelectedRecord()->GetIndex());
			}			
			break;

		}

		CXTPGridRow *pRow = m_Data.GetSelectedRow();
		if(pRow)
			pRow->SetSelected(FALSE);

		throw("복사하였습니다.");
			
	}
	catch (char* e)
	{
		MessageBox(e, "확인", MB_ICONINFORMATION);
	}
	



}


void CCorporationDlg2::OnBnClickedPasteColBtn()
{
	BatchWork(FALSE);
}

void CCorporationDlg2::BatchWork(BOOL bAll)
{

	try
	{
		int nCur = m_wndTabControl.GetCurSel();
		long nPasteCNo = 0, nPasteGNo = 0;


		switch(nCur)
		{
		case 0:
			{
				CMyTestView *pView1 = (CMyTestView *)GetTabItem(nCur);
				CDataBox &m_Data = pView1->GetDataCtrl();				

				if(m_Data.GetSelectedCount() <= 0)
					throw("붙여넣으실 행을 선택하세요");	

				for(int i = 0; i < m_Data.GetSelectedCount(); i++)
				{
					CXTPGridRecord *pRecord = m_Data.GetSelectedRows()->GetAt(i)->GetRecord();
					nPasteCNo = m_Data.GetItemDataLong(pRecord->GetIndex());
					nPasteGNo = m_Data.GetItemDataLong2(pRecord->GetIndex());

					BOOL bCheckID = FALSE, bCheckPwd = FALSE, bCheckHome = FALSE, bCheckEmail = FALSE;
					bCheckID = pView1->m_bSelectCol[6];
					bCheckPwd = pView1->m_bSelectCol[7];
					bCheckHome	= pView1->m_bSelectCol[8];
					bCheckEmail = pView1->m_bSelectCol[9];				

					if(!bAll)
					{
						if(bCheckID == 0 && bCheckPwd ==  0 && bCheckHome == 0 && bCheckEmail == 0)
							throw("한개라도 체크되어야 저장됩니다.");

						if(i == 0 )
						{
							CString sMsg = "";
							if(bCheckID)
								sMsg += "아이디 ";
							if(bCheckPwd)
								sMsg += "패스워드 ";
							if(bCheckHome)
								sMsg += "홈페이지미사용 ";
							if(bCheckEmail)
								sMsg += "이메일 ";

							if(sMsg.GetLength() == 0)
								return;
							sMsg += " 만 수정하시는게 맞습니까?  ";
							if(IDNO ==MessageBox(sMsg,"확인",MB_ICONINFORMATION | MB_YESNO) )
								return;
						}
					}
					else
					{

						CString sMsg = " 선택하신 행들을 수정하시는게 맞습니까?   ";
						if(IDNO ==MessageBox(sMsg,"확인",MB_ICONINFORMATION | MB_YESNO) )
							return;
					}					


					CMkCommand pCmd(m_pMkDb, "update_customer_group_general2");
					CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
					pCmd.AddParameter(m_nCopyCNo);
					pCmd.AddParameter(m_nCopyGNo);
					pCmd.AddParameter(nPasteCNo);
					pCmd.AddParameter(m_ci.m_nCompanyCode);
					pCmd.AddParameter(bAll);
					pCmd.AddParameter(bCheckID);
					pCmd.AddParameter(bCheckPwd);
					pCmd.AddParameter(bCheckHome);
					pCmd.AddParameter(bCheckEmail);
					pCmd.AddParameter(this->m_bChild);

					if(!pCmd.Execute())
						throw("업데이트중 실패하였습니다. 다시시도하여주세요");

				}


			}	
			break;
		case 1:
			{
				CMyTestView1 *pView2 = (CMyTestView1*)GetTabItem(nCur);
				CDataBox &m_Data = pView2->GetDataCtrl();				

				if(m_Data.GetSelectedCount() <= 0)
					throw("붙여넣으실 행을 선택하세요");	

				for(int i = 0; i < m_Data.GetSelectedCount(); i++)
				{
					CXTPGridRecord *pRecord = m_Data.GetSelectedRows()->GetAt(i)->GetRecord();
					nPasteCNo = m_Data.GetItemDataLong(pRecord->GetIndex());
					nPasteGNo = m_Data.GetItemDataLong2(pRecord->GetIndex());

					BOOL bCheckDong = FALSE, bCheckAddress = FALSE, bCheckLocation = FALSE, bCheckMemo = FALSE, bCheckRiderMemo = FALSE;
					bCheckDong = pView2->m_bSelectCol[2];
					bCheckAddress = pView2->m_bSelectCol[3];
					bCheckLocation	= pView2->m_bSelectCol[4];
					bCheckMemo = pView2->m_bSelectCol[5];				
					bCheckRiderMemo = pView2->m_bSelectCol[6];				

					if(i == 0 )
					{
						if(!bAll)
						{
							if(bCheckDong == 0 && bCheckAddress ==  0 && bCheckLocation == 0 && bCheckMemo == 0 && bCheckRiderMemo == 0)
								throw("한개라도 체크되어야 저장됩니다.");
							
							CString sMsg = "";
							if(bCheckDong)
								sMsg += "해당동 ";
							if(bCheckAddress)
								sMsg += "번지 ";
							if(bCheckLocation)
								sMsg += "위치 ";
							if(bCheckMemo)
								sMsg += "메모 ";
							if(bCheckRiderMemo)
								sMsg += "기사메모 ";

							if(sMsg.GetLength() == 0)
								return;
							sMsg += " 가(등이) 선택되었고 수정하시는게 맞습니까?    ";
							if(IDNO ==MessageBox(sMsg,"확인",MB_ICONINFORMATION | MB_YESNO) )
								return;
							
						}
						else
						{
							
							CString sMsg = "  선택하신 행들을 수정하시는게 맞습니까?  ";
							if(IDNO ==MessageBox(sMsg,"확인",MB_ICONINFORMATION | MB_YESNO) )
								return;
						}
					}


					CMkCommand pCmd(m_pMkDb, "update_customer_group_etc2");
					CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
					pCmd.AddParameter(m_nCopyCNo);
					pCmd.AddParameter(m_nCopyGNo);
					pCmd.AddParameter(nPasteCNo);
					pCmd.AddParameter(m_ci.m_nCompanyCode);
					pCmd.AddParameter(bAll);
					pCmd.AddParameter(bCheckDong);
					pCmd.AddParameter(bCheckAddress);
					pCmd.AddParameter(bCheckLocation);
					pCmd.AddParameter(bCheckMemo);
					pCmd.AddParameter(bCheckRiderMemo);
					pCmd.AddParameter(this->m_bChild);
					if(!pCmd.Execute())
						throw("업데이트중 실패하였습니다. 다시시도하여주세요");

				}

			}

			break;
		case 2:
			{
				CMyTestView2 *pView3 = (CMyTestView2 *)GetTabItem(nCur);
				CDataBox &m_Data = pView3->GetDataCtrl();
				if(m_Data.GetSelectedCount() == 0)
					throw("복사하실 행을 선택하세요");

				for(int i = 0; i < m_Data.GetSelectedCount(); i++)
				{
					CXTPGridRecord *pRecord = m_Data.GetSelectedRows()->GetAt(i)->GetRecord();
					nPasteCNo = m_Data.GetItemDataLong(pRecord->GetIndex());
					nPasteGNo = m_Data.GetItemDataLong2(pRecord->GetIndex());				

					BOOL bCredit = FALSE, bCoupon = FALSE, bCouponCharge = FALSE, bCreditAfterDiscount = FALSE, 
						bPriceGrade = FALSE, bMileageType = FALSE, bReportStartDay = FALSE, bReportEndDay = FALSE, 
						bIssueTaxBillDay = FALSE, bPayableDay = FALSE, bUncollectedAmount = FALSE;

					bCredit			= pView3->m_bSelectCol[2];
					bCoupon			= pView3->m_bSelectCol[3];
					bCouponCharge	= pView3->m_bSelectCol[4];
					//bCouponType		= pView3->m_bSelectCol[5];				
					bCreditAfterDiscount = pView3->m_bSelectCol[5];				
					bPriceGrade		= pView3->m_bSelectCol[6];
					bMileageType	= pView3->m_bSelectCol[7];
					//bMileageValue	= pView3->m_bSelectCol[9];
					bReportStartDay = pView3->m_bSelectCol[8];
					bReportEndDay	= pView3->m_bSelectCol[9];
					bIssueTaxBillDay = pView3->m_bSelectCol[10];
					bPayableDay = pView3->m_bSelectCol[11];
					bUncollectedAmount = pView3->m_bSelectCol[12];
					if(i == 0 )
					{
						if(!bAll)
						{
							if(bCredit == 0 && bCoupon ==  0 && bCouponCharge == 0 && bCreditAfterDiscount == 0 && 
								bPriceGrade == 0 && bMileageType ==  0 && bReportStartDay == 0 && bReportEndDay == 0 && 
								bIssueTaxBillDay == 0 && bPayableDay ==  0 && bUncollectedAmount == 0)
								throw("한개라도 체크되어야 저장됩니다.");

							
							CString sMsg = "";
							if(bCredit)
								sMsg += "신용 ";
							if(bCoupon)
								sMsg += "쿠폰 ";
							if(bCouponCharge)
								sMsg += "쿠폰타입 ";

							if(bPriceGrade)
								sMsg += "후정산 ";
							if(bPriceGrade)
								sMsg += "할인 ";

							if(bMileageType)
								sMsg += "마일리지 ";
							if(bReportStartDay)
								sMsg += "정산1 ";
							if(bReportEndDay)
								sMsg += "정산2 ";
							if(bPriceGrade)
								sMsg += "계산서 ";
							if(bCreditAfterDiscount)
								sMsg += "입금일 ";
							if(bPriceGrade)
								sMsg += "미수금 ";

							if(sMsg.GetLength() == 0)
								return;
							sMsg += " 가(등이) 선택되었고 수정하시는게 맞습니까?   ";
							if(IDNO ==MessageBox(sMsg,"확인",MB_ICONINFORMATION | MB_YESNO) )
								return;
						}	
						else
						{
							CString sMsg = " 선택하신 행들을 수정하시는게 맞습니까?  ";
							if(IDNO ==MessageBox(sMsg,"확인",MB_ICONINFORMATION | MB_YESNO) )
								return;
						}
					}
				


					CMkCommand pCmd(m_pMkDb, "update_customer_group_calc2");
					CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
					pCmd.AddParameter(m_nCopyCNo);
					pCmd.AddParameter(m_nCopyGNo);
					pCmd.AddParameter(nPasteCNo);
					pCmd.AddParameter(m_ci.m_nCompanyCode);
					pCmd.AddParameter(bAll);				

					pCmd.AddParameter(bCredit);
					pCmd.AddParameter(bCoupon);
					pCmd.AddParameter(bCouponCharge);
					pCmd.AddParameter(bCreditAfterDiscount);
					pCmd.AddParameter(bPriceGrade);
					pCmd.AddParameter(bMileageType);
					pCmd.AddParameter(bReportStartDay);
					pCmd.AddParameter(bReportEndDay);
					pCmd.AddParameter(bIssueTaxBillDay);
					pCmd.AddParameter(bPayableDay);
					pCmd.AddParameter(bUncollectedAmount);
					pCmd.AddParameter(this->m_bChild);

					if(!pCmd.Execute())
						throw("업데이트중 실패하였습니다. 다시시도하여주세요");

				}
			}

			break;
		case 3:
			{
				CMyTestView *pView4 = (CMyTestView *)GetTabItem(nCur);
				CDataBox &m_Data = pView4->GetDataCtrl();
				if(m_Data.GetSelectedCount() == 0)
				{
					MessageBox("복사하실 행을 선택하세요", "확인", MB_ICONINFORMATION);
					return;
				}
				m_nCopyCNo = m_Data.GetItemDataLong(m_Data.GetSelectedRecord()->GetIndex());
				m_nCopyGNo = m_Data.GetItemDataLong2(m_Data.GetSelectedRecord()->GetIndex());
			}

			break;

		}
		RefreshMember();
		


	}
	catch (char* e)
	{
		MessageBox(e, "확인", MB_ICONINFORMATION);
	}

}
void CCorporationDlg2::OnBnClickedPasteRowBtn()
{
	BatchWork(TRUE);

}


void CCorporationDlg2::OnBnClickedModifyBtn()
{
	try
	{

		int nCur = m_wndTabControl.GetCurSel();
		long nCNo = -1;
		switch(nCur)
		{
		case 0:
			{
				CMyTestView *pView1 = (CMyTestView *)GetTabItem(nCur);
				CDataBox &m_Data = pView1->GetDataCtrl();
				
				if(m_Data.GetSelectedCount() == 0)
				{
					MessageBox("수정하실 행을 선택하세요", "확인", MB_ICONINFORMATION);
					return;
				}				
				pView1->ReportDblClick();
				
			}					
			break;
		case 1:
			{
				CMyTestView1 *pView2 = (CMyTestView1 *)GetTabItem(nCur);
				CDataBox &m_Data = pView2->GetDataCtrl();
				if(m_Data.GetSelectedCount() == 0)
				{
					MessageBox("수정하실 행을 선택하세요", "확인", MB_ICONINFORMATION);
					return;
				}
				pView2->ReportDblClick();
			}

			break;
		case 2:
			{
				CMyTestView2 *pView3 = (CMyTestView2 *)GetTabItem(nCur);
				CDataBox &m_Data = pView3->GetDataCtrl();
				if(m_Data.GetSelectedCount() == 0)
				{
					MessageBox("수정하실 행을 선택하세요", "확인", MB_ICONINFORMATION);
					return;
				}
				pView3->ReportDblClick();
			}

			break;
		case 3:
			{
				/*CMyTestView *pView4 = (CMyTestView *)GetTabItem(nCur);
				CDataBox &m_Data = pView4->GetDataCtrl();
				if(m_Data.GetSelectedCount() == 0)
				{
					MessageBox("복사하실 행을 선택하세요", "확인", MB_ICONINFORMATION);
					return;
				}
				m_nCopyCNo = m_Data.GetItemDataLong(m_Data.GetSelectedRecord()->GetIndex());
				m_nCopyGNo = m_Data.GetItemDataLong2(m_Data.GetSelectedRecord()->GetIndex());*/
			}			
			break;

		}

		

	}
	catch (char* e)
	{
		MessageBox(e, "확인", MB_ICONINFORMATION);
	}
}

void CCorporationDlg2::OnMenuClickedGroupOwnerBtn()
{
	OnBnClickedGroupOwner();
}
void CCorporationDlg2::OnMenuClickedReceiptBtn()
{
	OnBnClickedReceiptBtn();
}
void CCorporationDlg2::OnBnClickedReceiptBtn()
{
	try
	{

		int nCur = m_wndTabControl.GetCurSel();
		
		switch(nCur)
		{
		case 0:
			{
				CMyTestView *pView1 = (CMyTestView *)GetTabItem(nCur);
				CDataBox &m_Data = pView1->GetDataCtrl();

				if(m_Data.GetSelectedCount() == 0)
				{
					MessageBox("수정하실 행을 선택하세요", "확인", MB_ICONINFORMATION);
					return;
				}				
				if(m_Data.GetSelectedCount() <= 0)
					return;

				m_nReceiptCNo = (long)m_Data.GetItemDataLong(m_Data.GetSelectedRecord()->GetIndex());



			}					
			break;
		case 1:
			{
				CMyTestView1 *pView2 = (CMyTestView1 *)GetTabItem(nCur);
				CDataBox &m_Data = pView2->GetDataCtrl();
				if(m_Data.GetSelectedCount() == 0)
				{
					MessageBox("수정하실 행을 선택하세요", "확인", MB_ICONINFORMATION);
					return;
				}				
				if(m_Data.GetSelectedCount() <= 0)
					return;

				m_nReceiptCNo = m_Data.GetItemDataLong(m_Data.GetSelectedRecord()->GetIndex());

			}

			break;
		case 2:
			{
				CMyTestView2 *pView3 = (CMyTestView2 *)GetTabItem(nCur);
				CDataBox &m_Data = pView3->GetDataCtrl();
				if(m_Data.GetSelectedCount() == 0)
				{
					MessageBox("수정하실 행을 선택하세요", "확인", MB_ICONINFORMATION);
					return;
				}
				
				if(m_Data.GetSelectedCount() <= 0)
					return;

				m_nReceiptCNo = m_Data.GetItemDataLong(m_Data.GetSelectedRecord()->GetIndex());

			}

			break;
		case 3:
			{
				/*CMyTestView *pView4 = (CMyTestView *)GetTabItem(nCur);
				CDataBox &m_Data = pView4->GetDataCtrl();
				if(m_Data.GetSelectedCount() == 0)
				{
				MessageBox("복사하실 행을 선택하세요", "확인", MB_ICONINFORMATION);
				return;
				}
				m_nCopyCNo = m_Data.GetItemDataLong(m_Data.GetSelectedRecord()->GetIndex());
				m_nCopyGNo = m_Data.GetItemDataLong2(m_Data.GetSelectedRecord()->GetIndex());*/
			}			
			break;

		}

		if(m_nReceiptCNo <= 0)
			throw("고객 선택을 다시하여주세요");
		else
		{
			m_bReceipt = TRUE;
			OnOK();		
		}


	}
	catch (char* e)
	{
		MessageBox(e, "확인", MB_ICONINFORMATION);
	}
}



void CCorporationDlg2::OnBnClickedGroupOwner()
{
	try
	{

		int nCur = m_wndTabControl.GetCurSel();
		long nGroupOwnerCNo = 0;
		switch(nCur)
		{
		case 0:
			{
				CMyTestView *pView1 = (CMyTestView *)GetTabItem(nCur);
				CDataBox &m_Data = pView1->GetDataCtrl();

				if(m_Data.GetSelectedCount() <= 0)
					throw("수정하실 행을 선택하세요");
					
				if(m_Data.GetSelectedCount() > 1)
					throw("1개 이상을 그룹오너로 수정하실수 없습니다.");

				nGroupOwnerCNo = (long)m_Data.GetItemDataLong(m_Data.GetSelectedRecord()->GetIndex());
				long nGNo = m_Data.GetItemDataLong2(m_Data.GetSelectedRecord()->GetIndex());
				if(nGroupOwnerCNo <= 0)
					throw("고객 선택을 다시하여주세요");
				else
				{
					GroupOwnerSelect(nGroupOwnerCNo);

					m_cg.GetGroupData(nGNo)->nGroupOwner = nGroupOwnerCNo;
					m_GroupList.Populate();
					m_Data.Populate();
				}
				
			


			}					
			break;
		case 1:
			{
				CMyTestView1 *pView2 = (CMyTestView1 *)GetTabItem(nCur);
				CDataBox &m_Data = pView2->GetDataCtrl();
				if(m_Data.GetSelectedCount() == 0)
				{
					MessageBox("수정하실 행을 선택하세요", "확인", MB_ICONINFORMATION);
					return;
				}				
				if(m_Data.GetSelectedCount() <= 0)
					return;

				nGroupOwnerCNo = (long)m_Data.GetItemDataLong(m_Data.GetSelectedRecord()->GetIndex());
				long nGNo = m_Data.GetItemDataLong2(m_Data.GetSelectedRecord()->GetIndex());
				if(nGroupOwnerCNo <= 0)
					throw("고객 선택을 다시하여주세요");
				else
				{
					GroupOwnerSelect(nGroupOwnerCNo);

					m_cg.GetGroupData(nGNo)->nGroupOwner = nGroupOwnerCNo;
					m_GroupList.Populate();
					m_Data.Populate();
				}

			}

			break;
		case 2:
			{
				CMyTestView2 *pView3 = (CMyTestView2 *)GetTabItem(nCur);
				CDataBox &m_Data = pView3->GetDataCtrl();
				if(m_Data.GetSelectedCount() == 0)
				{
					MessageBox("수정하실 행을 선택하세요", "확인", MB_ICONINFORMATION);
					return;
				}

				if(m_Data.GetSelectedCount() <= 0)
					return;

				nGroupOwnerCNo = (long)m_Data.GetItemDataLong(m_Data.GetSelectedRecord()->GetIndex());
				long nGNo = m_Data.GetItemDataLong2(m_Data.GetSelectedRecord()->GetIndex());
				if(nGroupOwnerCNo <= 0)
					throw("고객 선택을 다시하여주세요");
				else
				{
					GroupOwnerSelect(nGroupOwnerCNo);

					m_cg.GetGroupData(nGNo)->nGroupOwner = nGroupOwnerCNo;
					m_GroupList.Populate();
					m_Data.Populate();
				}
				
				
			}

			break;
		case 3:
			{
				/*CMyTestView *pView4 = (CMyTestView *)GetTabItem(nCur);
				CDataBox &m_Data = pView4->GetDataCtrl();
				if(m_Data.GetSelectedCount() == 0)
				{
				MessageBox("복사하실 행을 선택하세요", "확인", MB_ICONINFORMATION);
				return;
				}
				m_nCopyCNo = m_Data.GetItemDataLong(m_Data.GetSelectedRecord()->GetIndex());
				m_nCopyGNo = m_Data.GetItemDataLong2(m_Data.GetSelectedRecord()->GetIndex());*/
			}			
			break;

		}

		


	}
	catch (char* e)
	{
		MessageBox(e, "확인", MB_ICONINFORMATION);
	}
}
void CCorporationDlg2::GroupOwnerSelect(long nGroupOwnerCNo )
{

	CMkCommand pCmd(m_pMkDb, "update_customer_group_owner");
	pCmd.AddParameter(m_nCustomerCompany);
	pCmd.AddParameter(nGroupOwnerCNo);
	if(pCmd.Execute())
	{
		MessageBox("해당고객을 그룹오너로 설정하였습니다.\n"\
			"다른고객을 그룹오너로 설정하시면, 해당고객은 그룹오너에서 자동해제됩니다.",
			"확인",
			MB_ICONINFORMATION);		
	}
}


void CCorporationDlg2::OnStnClickedSplitter1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



//void CCorporationDlg2::OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/)
//{
//	m_bDragMode = TRUE;
//	::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
//	SetCapture();
//}



void CCorporationDlg2::OnMouseMove(UINT nFlags, CPoint point)
{
	
	if(TRUE == m_bDragMode)
	{
		if(m_bBegin)
			SendMessage(LVN_BEGINDRAG,NULL, NULL);

		::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
		
		CRect rect;
		m_GroupList.GetWindowRect(&rect);
		g_bana_log->Print("그룹박스안");
		if(rect.PtInRect(point) )
		{
			for(int i = 0; i < m_GroupList.GetRows()->GetCount(); i++)
			{
				CRect rowRect = m_GroupList.GetRows()->GetAt(i)->GetRect();
				CXTPGridRow *pRow = m_GroupList.GetRows()->GetAt(i);
				if(rowRect.PtInRect(point) )
				{
					g_bana_log->Print("아이템안");
					if(m_pPreRow == NULL)
						m_pPreRow = pRow;
					
					m_pPreRow->SetSelected(FALSE);
					
					pRow->SetSelected(TRUE);
				}
				
			}

		}
	}


	CXTResizeDialog::OnMouseMove(nFlags, point);
}


void CCorporationDlg2::OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/)
{
	
	::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	SetCapture();
}
//B CCorporationDlg2::OnGroupLButtonUp(WPARAM wParam, LPARAM lParam)
//{
//
//
//	return 0;
//
//}

void CCorporationDlg2::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(TRUE == m_bDragMode)
	{		
		::ReleaseCapture();

		CRect rect;
		m_GroupList.GetWindowRect(&rect);
		ScreenToClient(rect);

		if(rect.PtInRect(point))
		{
			CXTPGridRow *pRow = m_GroupList.GetSelectedRows()->GetAt(0);

			if(pRow == NULL)
				return;

			CMyXTPGridRecord *pRecord = (CMyXTPGridRecord*)pRow->GetRecord();

			long nGNo = pRecord->GetItemDataLong();
			CString strGroupName = m_cg.GetGroupData(pRecord->GetItemDataLong())->strGroupName;

			//if(m_cg.GetGroupData(pRecord->GetItemDataLong())->nLevel != 0) // 최상위 그룹을 가져온다
			//	nGNo = m_cg.GetGroupData(pRecord->m_nGNo)->nParentGNo;//
			//else
			//	nGNo = pRecord->m_nGNo;

			//MakeListTree(nGNo);
			//GetData(nGNo);
		}
	}

	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	::ReleaseCapture();
	m_bDragMode  = FALSE;  //순서에 주의 할것

	CXTResizeDialog::OnLButtonUp(nFlags, point);
}
