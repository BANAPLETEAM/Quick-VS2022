// MoveRiderNewDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "MoveRiderNewDlg.h"
#include "VarietyDlg.h"

#define EVENT_ID 1000
#define ID_MAKE_NUMBER 2000
#define ID_DELETE_MOVE_RIDER 2100


CMoveRiderRecord::CMoveRiderRecord(long nCompany, long nRNo, CString strRName)
{
	AddItem(new CXTPGridRecordItemText(LF->GetBranchInfo(nCompany)->strBranchName));
	AddItem(new CXTPGridRecordItemNumber(nRNo));
	AddItem(new CXTPGridRecordItemText(strRName));
	AddItem(new CXTPGridRecordItemText("->"));
	AddItem(new CXTPGridRecordItemText(LF->GetBranchInfo(nCompany)->strBranchName));
	CMoveRiderDirtyCheckNumber *pRecordItem = (CMoveRiderDirtyCheckNumber*)AddItem(new CMoveRiderDirtyCheckNumber(nRNo));
	pRecordItem->m_pMoveRiderRecord = this;

	AddItem(new CXTPGridRecordItemText(strRName));
	AddItem(new CXTPGridRecordItemText("사번 중복"));

	m_stMoveRider = new ST_MOVE_RIDER;

	m_stMoveRider->nFromCompany = nCompany;
	m_stMoveRider->nFromRNo = nRNo;
	m_stMoveRider->nToCompany = nCompany;
	m_stMoveRider->nToRNo = nRNo;
	m_stMoveRider->strRName = strRName;
}

CMoveRiderRecord::~CMoveRiderRecord()
{
	if(m_stMoveRider)
	{
		delete m_stMoveRider;
		m_stMoveRider = NULL;
	}
}



// CMoveRiderNewDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMoveRiderNewDlg, CMyDialog)

CMoveRiderNewDlg::CMoveRiderNewDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMoveRiderNewDlg::IDD, pParent)
{
	m_bDragMode = FALSE;
}

CMoveRiderNewDlg::~CMoveRiderNewDlg()
{
}

void CMoveRiderNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LEFT_LIST, m_lstLeft);
	DDX_Control(pDX, IDC_RIGHT_LIST, m_lstRight);
	DDX_Control(pDX, IDC_COMBO1, m_cmbBranch);
	DDX_Control(pDX, IDC_RIGHT_EDIT, m_edtRight);
	DDX_Control(pDX, IDC_LEFT_EDIT, m_edtLeft);
}


BEGIN_MESSAGE_MAP(CMoveRiderNewDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CHANGE_BTN, &CMoveRiderNewDlg::OnBnClickedChangeBtn)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LEFT_LIST, OnReportBeginDrag)
	ON_WM_LBUTTONUP()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMoveRiderNewDlg::OnCbnSelchangeCombo1)
	ON_COMMAND_RANGE(EVENT_ID, EVENT_ID + 100, OnChangeBranch)
	ON_COMMAND(ID_MAKE_NUMBER, OnMakeNumber)
	ON_COMMAND(ID_DELETE_MOVE_RIDER, OnDeleteMoveRider)
	ON_WM_CONTEXTMENU()
	ON_EN_CHANGE(IDC_RIGHT_EDIT, &CMoveRiderNewDlg::OnEnChangeRightEdit)
	ON_EN_CHANGE(IDC_LEFT_EDIT, &CMoveRiderNewDlg::OnEnChangeLeftEdit)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMoveRiderNewDlg 메시지 처리기입니다.

void CMoveRiderNewDlg::OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/)
{
	m_bDragMode = TRUE;
	::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	SetCapture();
}

long CMoveRiderNewDlg::GetValidCount()
{
	long nCount = 0;
	CXTPGridRows *pRows = m_lstRight.GetRows();
	
	for(int i=0; i<pRows->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
		CString strText = m_lstRight.GetItemText(pRecord, 7);

		if(strText.IsEmpty())
			nCount++;
	}

	return nCount;
}

void CMoveRiderNewDlg::OnBnClickedChangeBtn()
{	
	if(MessageBox("기사이동 후 이동하신 기사님의 자사콜, 타사콜 입금액을 반드시 확인하세요", "확인", MB_OKCANCEL) != IDOK)
		return;

	long nCount = GetValidCount();
 
	if(nCount == ZERO)
	{
		MessageBox("이동하실 기사님을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	} 

	CString strTemp = "";
	strTemp.Format("%d명의 기사님에게 적용하시겠습니까?\r\n\r\n명수가 많을경우 멈춤 현상이 있을 수 있습니다.\r\n프로그램을 종료하지마세요.", nCount);

	if(MessageBox(strTemp, "확인", MB_OKCANCEL) != IDOK)
		return;

	CXTPGridRows *pRows = m_lstRight.GetRows();
 
	for(int i=0; i<pRows->GetCount(); i++)
	{
		CMoveRiderRecord *pRecord = (CMoveRiderRecord*)pRows->GetAt(i)->GetRecord();

		CString strText = m_lstRight.GetItemText(pRecord, 7);

		if(!strText.IsEmpty())
			continue;

		ST_MOVE_RIDER *st = pRecord->GetMoveRiderSturct();

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "driver_move_process");
		pCmd.AddParameter(st->nFromCompany);
		pCmd.AddParameter(st->nFromRNo );
		pCmd.AddParameter(st->nToCompany);
		pCmd.AddParameter(st->nToRNo);
		pCmd.AddParameter(m_ui.strID + "/" + LF->GetStringFromLong(m_ui.nCompany));	
		CMkParameter *parRet = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

		if(!pCmd.Execute()) 
			return;
		else
			pRecord->Delete();
	}

	MessageBox("성공적으로 이동되었습니다", "확인", MB_ICONINFORMATION);

	m_lstRight.Populate();
	RefreshRiderList();
}

BOOL CMoveRiderNewDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_cmbBranch.ModifyStyle(0, CBS_DROPDOWNLIST | CBS_SORT);

	for(int i = 0; i < m_ba.GetCount(); i++) 
	{
		if(i == 0 && m_ba.GetCount() > ONE)
			continue;

		CBranchInfo *pBi = m_ba.GetAt(i);

		int nIndex = m_cmbBranch.AddString(pBi->strBranchName + "(" + pBi->strPhone + ")");
		m_cmbBranch.SetItemData(nIndex, pBi->nCompanyCode);
		m_cmbBranch.SetCurSel(0);
	}

	m_lstLeft.InsertColumn(0, "소속", LVCFMT_LEFT, 90);
	m_lstLeft.InsertColumn(1, "사번", LVCFMT_CENTER, 45);
	m_lstLeft.InsertColumn(2, "이름", LVCFMT_LEFT, 70);

	m_lstLeft.Populate();

	CXTPGridColumn *pCol0 = m_lstRight.AddColumn(new CXTPGridColumn(0, "소속", 100, FALSE));
	CXTPGridColumn *pCol1 = m_lstRight.AddColumn(new CXTPGridColumn(1, "사번", 45, FALSE));
	CXTPGridColumn *pCol2 = m_lstRight.AddColumn(new CXTPGridColumn(2, "이름", 70, FALSE));
	CXTPGridColumn *pCol3 = m_lstRight.AddColumn(new CXTPGridColumn(3, "", 40, FALSE));
	CXTPGridColumn *pCol4 = m_lstRight.AddColumn(new CXTPGridColumn(4, "소속", 100, FALSE));
	CXTPGridColumn *pCol5 = m_lstRight.AddColumn(new CXTPGridColumn(5, "사번", 45, FALSE));
	CXTPGridColumn *pCol6 = m_lstRight.AddColumn(new CXTPGridColumn(6, "이름", 70, FALSE));
	CXTPGridColumn *pCol7 = m_lstRight.AddColumn(new CXTPGridColumn(7, "상태", 150, FALSE));

	m_lstRight.AllowEdit(TRUE);

	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol1->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol2->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol3->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol4->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol6->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol7->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol1->SetAlignment(DT_CENTER);
	pCol3->SetAlignment(DT_CENTER);
	pCol5->GetEditOptions()->m_bAllowEdit = TRUE;
	pCol5->SetAlignment(DT_CENTER);

	m_lstRight.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);
	m_lstRight.GetReportHeader()->AllowColumnResize(TRUE);
	m_lstRight.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_lstRight.GetReportHeader()->AllowColumnSort(TRUE);
	m_lstRight.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstRight.SetPaintManager(new CMyReportPaintManager());
	m_lstRight.GetPaintManager()->m_strNoItems = "";
	m_lstRight.SetGridStyle(TRUE, xtpGridSolid);
	m_lstRight.SetGridColor(RGB(212, 208, 200));
	
	m_lstRight.Populate();

	RefreshRiderList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMoveRiderNewDlg::RefreshRiderList()
{
	m_lstLeft.DeleteAllItems();

	long nIdex = m_cmbBranch.GetCurSel();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_list_for_move_rider");
	pCmd.AddParameter((long)m_cmbBranch.GetItemData(nIdex));
	pCmd.AddParameter(nIdex == ZERO ? TRUE : FALSE);

	if(!pRs.Execute(&pCmd))
		return;

	long nCompany, nRNo, nWorkState;
	CString sName;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("nWorkState", nWorkState);
		pRs.GetFieldValue("sName", sName);

		m_lstLeft.InsertItem(i, LF->GetBranchInfo(nCompany)->strBranchName);
		m_lstLeft.SetItemText(i, 1, LF->GetStringFromLong(nRNo));
		m_lstLeft.SetItemText(i, 2, sName);

		m_lstLeft.SetItemLong(i, nCompany);
		m_lstLeft.SetItemLong3(i, nRNo);
		m_lstLeft.SetItemLong2(i, nWorkState);

		pRs.MoveNext();
	}

	m_lstLeft.Populate();
}

void CMoveRiderNewDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(TRUE == m_bDragMode)
	{
		CRect rect;
		m_lstRight.GetWindowRect(&rect);
		ScreenToClient(rect);

		if(rect.PtInRect(point))
		{
			CXTPGridSelectedRows *pRows = m_lstLeft.GetSelectedRows();

			if(pRows == NULL) return;
			if(pRows->GetCount() == 0) return;

			for(int i=0; i<pRows->GetCount(); i++)
			{
				CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();

				if(pRecord)
				{
					CString strRName = m_lstLeft.GetItemText(pRecord, 2);
					InsertRightList(m_lstLeft.GetItemLong(pRecord), m_lstLeft.GetItemLong3(pRecord), strRName);			
				}

			}
		}
	}

	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	::ReleaseCapture();
	m_bDragMode  = FALSE;  //순서에 주의 할것

	CMyDialog::OnLButtonUp(nFlags, point);
}

BOOL CMoveRiderNewDlg::CheckRightListLocal(long nCompany, long nRNo)
{
	CXTPGridRows *pRows = m_lstRight.GetRows();

	for(int i=0; i<pRows->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();

		ST_MOVE_RIDER *st = (ST_MOVE_RIDER*)m_lstRight.GetItemData(pRecord);

		if(st->nFromCompany == nCompany && st->nFromRNo == nRNo)
			return FALSE;
	}

	return TRUE;
}

void CMoveRiderNewDlg::InsertRightList(long nCompany, long nRNo, CString strRName)
{
	if(CheckRightListLocal(nCompany, nRNo) == FALSE)
		return;

	m_lstRight.AddRecord(new CMoveRiderRecord(nCompany, nRNo, strRName));

	CheckFilterRight();
}

void CMoveRiderNewDlg::CheckFilterRight()
{
	CString strSearch; m_edtRight.GetWindowText(strSearch);

	CXTPGridRows *pRows = m_lstRight.GetRows();

	for(int i=0; i<pRows->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();

		ST_MOVE_RIDER *st = (ST_MOVE_RIDER*)m_lstRight.GetItemData(pRecord);

		long nFromRNo = st->nFromRNo;
		long nToRNo = st->nToRNo;
		CString strRName = st->strRName;

		if(nFromRNo == atoi(strSearch) ||
			nToRNo == atoi(strSearch) ||
			strRName.Find(strSearch) > -1)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstRight.Populate();
}

void CMoveRiderNewDlg::OnEnChangeLeftEdit2()
{
	CheckFilterRight();
}

void CMoveRiderNewDlg::OnCbnSelchangeCombo1()
{
	RefreshRiderList();
}

void CMoveRiderNewDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;  
	m_lstRight.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->AppendMenu(MF_BYCOMMAND | MF_SEPARATOR, 0, "");

	CMenu *pSubMenu = new CMenu;
	pSubMenu->CreatePopupMenu();

	pRMenu->InsertMenu(2, MF_BYPOSITION | MF_POPUP, (UINT)pSubMenu->m_hMenu, "지사변경");

	long nCount = m_cmbBranch.GetCount();

	for(int i=0; i<nCount; i++)
	{
		CString strBranch;
		m_cmbBranch.GetLBText(i, strBranch);

		pSubMenu->AppendMenu(MF_BYCOMMAND, EVENT_ID + i, strBranch);
	}

	pRMenu->AppendMenu(MF_STRING, ID_MAKE_NUMBER, "연속번호생성");
	pRMenu->AppendMenu(MF_STRING, ID_DELETE_MOVE_RIDER, "삭제");

	//menu.AppendMenu(MF_STRING,		ID_NO_FROZEN_COL,		"고정행렬 사용안함")
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	

	delete pSubMenu;
	pSubMenu = NULL;
}

void CMoveRiderNewDlg::OnChangeBranch(UINT nFlag)
{
	long nIndex = nFlag - EVENT_ID;
	long nCompany = (long)m_cmbBranch.GetItemData(nIndex);
	CString strBranch = LF->GetBranchInfo(nCompany)->strBranchName;

	CXTPGridSelectedRows *pRows = m_lstRight.GetSelectedRows();

	if(pRows == NULL)
		return;

	if(pRows->GetCount() == ZERO)
		return;

	long nCount = pRows->GetCount();

	for(int i=0; i<nCount; i++)
	{
		CMoveRiderRecord *pRecord = (CMoveRiderRecord*)pRows->GetAt(i)->GetRecord();
		pRecord->SetCompany(nCompany, strBranch);
		ST_MOVE_RIDER *st = pRecord->GetMoveRiderSturct();

		pRecord->SetValid(LF->IsMoveRiderOk(st->nToCompany, st->nToRNo));
	}

	m_lstRight.Populate();
}

void CMoveRiderNewDlg::OnMakeNumber()
{
	CVarietyDlg dlg;
	dlg.m_sTitleDlg = "시작 할 사번을 입력하세요";

	if(dlg.DoModal() != IDOK)
		return;

	long nItem = atoi(dlg.m_sValue);

	if(nItem == ZERO)
	{
		MessageBox("사번 0번은 사용 하실 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CXTPGridSelectedRows *pRows = m_lstRight.GetSelectedRows();

	if(pRows == NULL)
		return;

	if(pRows->GetCount() == ZERO)
		return;

	long nCount = pRows->GetCount();

	for(int i=0; i<nCount; i++)
	{
		CMoveRiderRecord *pRecord = (CMoveRiderRecord*)pRows->GetAt(i)->GetRecord();
		pRecord->SetRNo(nItem++);

		ST_MOVE_RIDER *st = pRecord->GetMoveRiderSturct();
		pRecord->SetValid(LF->IsMoveRiderOk(st->nToCompany, st->nToRNo));
	}
}

void CMoveRiderNewDlg::OnDeleteMoveRider()
{
	CXTPGridSelectedRows *pRows = m_lstRight.GetSelectedRows();

	if(pRows == NULL)
		return;

	if(pRows->GetCount() == ZERO)
		return;

	long nCount = pRows->GetCount();

	for(int i=0; i<nCount; i++)
	{
		CMoveRiderRecord *pRecord = (CMoveRiderRecord*)pRows->GetAt(i)->GetRecord();
		pRecord->Delete();
	}

	m_lstRight.Populate();
}

void CMoveRiderNewDlg::OnEnChangeRightEdit()
{
	CString strSearch; m_edtRight.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstRight.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strRNo = m_lstLeft.GetItemText(pRecord, 1);
		CString strRName = m_lstLeft.GetItemText(pRecord, 2);
		CString strRNo1 = m_lstLeft.GetItemText(pRecord, 5);
		CString strRName1 = m_lstLeft.GetItemText(pRecord, 6);

		if(strRNo.Find(strSearch) >= 0 ||
			strRName.Find(strSearch) >= 0 ||
			strRNo1.Find(strSearch) >= 0 ||
			strRName1.Find(strSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstRight.Populate();
}

void CMoveRiderNewDlg::OnEnChangeLeftEdit()
{
	CString strSearch; m_edtLeft.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstLeft.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strRNo = m_lstLeft.GetItemText(pRecord, 1);
		CString strRName = m_lstLeft.GetItemText(pRecord, 2);

		if(strRNo.Find(strSearch) >= 0 ||
			strRName.Find(strSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstLeft.Populate();
}

void CMoveRiderNewDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(!m_lstLeft.GetSafeHwnd())
		return;

	if(!m_lstRight.GetSafeHwnd())
		return;


	CRect rcDlg, rcLeft, rcRight;
	GetClientRect(rcDlg);
	m_lstLeft.GetWindowRect(rcLeft);
	ScreenToClient(rcLeft);
	m_lstRight.GetWindowRect(rcRight);
	ScreenToClient(rcRight);

	rcRight.right = rcDlg.right - 4; 
	rcRight.bottom = rcDlg.bottom - 4; 

	rcLeft.bottom = rcDlg.bottom - 4; 

	m_lstLeft.MoveWindow(rcLeft); 
	m_lstRight.MoveWindow(rcRight); 
}
