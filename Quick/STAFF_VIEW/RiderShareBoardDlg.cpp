// RiderShareBoardDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderShareBoardDlg.h"
#include "SmallTalkEditDlg.h"
#include "AddRiderShareInfoDlg.h"
#include "ShareOrderAllocate.h"
#include "RiderAdviceDlg2010.h"

// CRiderShareBoardDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderShareBoardDlg, CMyDialog)

CRiderShareBoardDlg::CRiderShareBoardDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderShareBoardDlg::IDD, pParent)
{
	m_pSmallTalkEditDlg = NULL;
	m_pAddRiderShareInfoDlg = NULL;
	m_nParentID = 0;
	m_nRiderCompany = 0;
	m_nRNo = 0;
	m_strRName = "";
}

CRiderShareBoardDlg::~CRiderShareBoardDlg()
{
	if(m_pSmallTalkEditDlg)
	{
		delete m_pSmallTalkEditDlg;
		m_pSmallTalkEditDlg = NULL;
	}

	if(m_pAddRiderShareInfoDlg)
	{
		delete m_pAddRiderShareInfoDlg;
		m_pAddRiderShareInfoDlg = NULL;
	}
}

void CRiderShareBoardDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TWI_REPORT, m_wndTwiReport);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_From);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_To);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
}


BEGIN_MESSAGE_MAP(CRiderShareBoardDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CRiderShareBoardDlg::OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_CLICK, IDC_TWI_REPORT, OnReportItemClick)
	ON_NOTIFY(NM_RCLICK, IDC_TWI_REPORT, OnReportItemRClick)
	ON_NOTIFY(NM_DBLCLK, IDC_TWI_REPORT, OnReportItemDblClick)
	ON_MESSAGE(WM_TWITTER_UPDATE, OnTwitterUpdate)
	ON_MESSAGE(WM_TWITTER_WRITE, OnTwitterWrite)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_TWITTER_UPDATE, OnUpdateTwitter)
	ON_COMMAND(ID_TWITTER_DELETE, OnDeleteTwitter)
	ON_COMMAND(ID_TWITTER_SEE, OnSeeTwitter)
	ON_BN_CLICKED(IDC_INSERT_BTN, &CRiderShareBoardDlg::OnBnClickedInsertBtn)
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CRiderShareBoardDlg 메시지 처리기입니다.

BOOL CRiderShareBoardDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	static BOOL bFirst = TRUE;

	if(bFirst == TRUE)
	{
		m_btnDate.InitDateButton(&m_From, &m_To);
		m_btnDate.OnMenuMonth();

		CXTPGridColumn* pCol10 = m_wndTwiReport.AddColumn(new CXTPGridColumn(0, _T("글번호"), 45, FALSE));
		CXTPGridColumn* pCol11 = m_wndTwiReport.AddColumn(new CXTPGridColumn(1, _T("시각"), 80, FALSE));
		CXTPGridColumn* pCol12 = m_wndTwiReport.AddColumn(new CXTPGridColumn(2, _T("등록자"), 100, FALSE));
		CXTPGridColumn* pCol13 = m_wndTwiReport.AddColumn(new CXTPGridColumn(3, _T("내용"), 300));
		CXTPGridColumn* pCol14 = m_wndTwiReport.AddColumn(new CXTPGridColumn(4, _T("기사"), 90, FALSE));
		CXTPGridColumn* pCol15 = m_wndTwiReport.AddColumn(new CXTPGridColumn(5, _T("답글"), 40, FALSE));
		CXTPGridColumn* pCol16 = m_wndTwiReport.AddColumn(new CXTPGridColumn(6, _T("배차제한"), 60, FALSE));

		pCol10->SetAlignment(DT_LEFT);
		pCol11->SetAlignment(DT_LEFT);
		pCol12->SetAlignment(DT_LEFT);
		pCol13->SetAlignment(DT_LEFT);
		pCol14->SetAlignment(DT_LEFT);
		pCol15->SetAlignment(DT_CENTER);
		pCol16->SetAlignment(DT_CENTER);

		//m_wndTwiReport.GetColumns()->SetSortColumn(pCol10, FALSE);

		m_wndTwiReport.GetPaintManager()->SetFixedRowHeight(FALSE);
		m_wndTwiReport.GetPaintManager()->m_bUseColumnTextAlignment = TRUE;
		m_wndTwiReport.GetPaintManager()->m_strNoItems = "";
		m_wndTwiReport.ShowHeader(TRUE);
		m_wndTwiReport.SetTreeIndent(10);
		m_wndTwiReport.AllowEdit(FALSE);
		m_wndTwiReport.FocusSubItems(FALSE);
		m_wndTwiReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
		m_wndTwiReport.SetGridColor(RGB(222, 222, 222));
		m_wndTwiReport.GetPaintManager()->m_bHideSelection = TRUE;
		m_wndTwiReport.EnableToolTips(TRUE);
		m_wndTwiReport.GetToolTipContext()->SetStyle(xtpToolTipOffice2007);
		m_wndTwiReport.Populate();

		m_wndTwiReport.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
		m_wndTwiReport.FocusSubItems(TRUE);

		RefreshList();

		bFirst = FALSE;
	}

	if(m_nRiderCompany > 0 && m_nRNo > 0)
		SetTimer(1000, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRiderShareBoardDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CRiderShareBoardDlg::RefreshList()
{
	UpdateData(TRUE);
	m_wndTwiReport.GetRecords()->RemoveAll();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_logi_twitter_new");
	pCmd.AddParameter(m_dtFrom);
	pCmd.AddParameter(m_dtTo);

	if(!pRs.Execute(&pCmd)) return;

	COleDateTime dtGenerate;
	long nWNo, nWCompany, nParentID, nTwiNo, nRiderCompany, nRNo;
	CString strWName, strMessage, strRName, strTemp;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		strTemp = ""; 

		pRs.GetFieldValue("nTwiNo", nTwiNo);
		pRs.GetFieldValue("dtGenerate", dtGenerate);
		pRs.GetFieldValue("nWNo", nWNo);
		pRs.GetFieldValue("nWCompany", nWCompany);
		pRs.GetFieldValue("nParentID", nParentID);
		pRs.GetFieldValue("sWName", strWName);
		pRs.GetFieldValue("sMessage", strMessage);
		pRs.GetFieldValue("nRiderCompany", nRiderCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sRName", strRName);

		if(nParentID == 0)
		{
		}
		else
		{
			if(nParentID > 0) strTemp += "   ";
			strMessage = strTemp + "┗" + strMessage;
		}

		m_wndTwiReport.AddRecord(new CSmallTalkRecord(nTwiNo, dtGenerate, nWNo, nWCompany, nParentID, strWName, strMessage, nRiderCompany, nRNo, strRName));
		pRs.MoveNext();
	}

	m_wndTwiReport.Populate(); 
}

void CRiderShareBoardDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CSmallTalkRecord *pRecord = (CSmallTalkRecord*)(pItemNotify->pRow->GetRecord());

	if( NULL == pRecord ) return;

	long nCol = pItemNotify->pColumn->GetItemIndex();
	CString strText = "";

	m_nParentID = pRecord->m_nTNo;

	if(nCol == 4)
	{ 
		if(pRecord->m_nRiderCompany > 0 && pRecord->m_nRNo > 0)
			LU->ShowRiderInfoDlg(pRecord->m_nRiderCompany, pRecord->m_nRNo);
	}
	else if(nCol == 5)// 답글
	{ 
		strText = pRecord->GetItem(5)->GetCaption(NULL);
		if(strText.IsEmpty()) return;

		OpenSmallTalkEdit(m_nParentID, "");
	}
	else if(nCol == 6)// 배차제한 
	{ 		
		strText = pRecord->GetItem(6)->GetCaption(NULL);

		if(strText.IsEmpty()) 
			return;

		CRiderAdviceDlg2010 dlg;
		dlg.m_nRiderCompany = pRecord->m_nRiderCompany;
		dlg.m_nRNo = pRecord->m_nRNo;
		dlg.m_nCompany = m_ci.m_nCompanyCode;
		dlg.DoModal();

	}
}

void CRiderShareBoardDlg::OpenSmallTalkEdit(long nParentID, CString strText)
{
	if(m_pSmallTalkEditDlg == NULL)
	{
		m_pSmallTalkEditDlg = new CSmallTalkEditDlg(this);
		m_pSmallTalkEditDlg->Create(IDD_SMALL_TALK_EDIT_DLG, this);
	}
	else
	{
		WINDOWPLACEMENT wndpl;
		wndpl.length = sizeof(WINDOWPLACEMENT);
		m_pSmallTalkEditDlg->GetWindowPlacement(&wndpl);
		m_pSmallTalkEditDlg->SetForegroundWindow();
		m_pSmallTalkEditDlg->SetFocus();
	}

	m_pSmallTalkEditDlg->m_nParentID = nParentID;
	m_pSmallTalkEditDlg->m_edtText.SetWindowText(strText);
	m_pSmallTalkEditDlg->ShowWindow(TRUE);

	if(strText.IsEmpty())//댓글
	{
		m_pSmallTalkEditDlg->m_bUpdate = FALSE;
		m_pSmallTalkEditDlg->m_btnInsert.SetWindowText("덧글입력");
		MoveTalkEdit(FALSE);
		SetCrystal(m_pSmallTalkEditDlg, 220);
	}
	else
	{
		m_pSmallTalkEditDlg->m_bUpdate = TRUE;
		m_pSmallTalkEditDlg->m_btnInsert.SetWindowText("수 정");
		MoveTalkEdit(TRUE);
		SetCrystal(m_pSmallTalkEditDlg, 255); 
	}
	
	m_pSmallTalkEditDlg->m_edtText.SetSel(strText.GetLength(), strText.GetLength());
	m_pSmallTalkEditDlg->m_edtText.SetFocus();
}

LONG CRiderShareBoardDlg::OnTwitterUpdate(WPARAM wParam, LPARAM lParam)
{	
	BOOL bRet = (BOOL)wParam;

	if(bRet)
	{
		RefreshList();
		//m_edtMsg.SetWindowText("");
	}

	return 0;
}

LONG CRiderShareBoardDlg::OnTwitterWrite(WPARAM wParam, LPARAM lParam)
{	
	BOOL bRet = (BOOL)wParam;

	if(bRet)
		RefreshList();

	return 0;
}

void CRiderShareBoardDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_wndTwiReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(25);

	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CRiderShareBoardDlg::OnSeeTwitter()
{
	CXTPGridSelectedRows *pRows = m_wndTwiReport.GetSelectedRows();
	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	CSmallTalkRecord *pRecord = (CSmallTalkRecord*)(pRows->GetAt(0)->GetRecord());
	//m_nParentID = pRecord->m_nTNo;

	CString strMent = pRecord->GetItem(3)->GetCaption(NULL);
	strMent.Replace("┗", "");
	strMent.TrimLeft();
	OpenSmallTalkEdit(-1, strMent);
}

void CRiderShareBoardDlg::OnUpdateTwitter()
{
	CXTPGridSelectedRows *pRows = m_wndTwiReport.GetSelectedRows();
	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	CSmallTalkRecord *pRecord = (CSmallTalkRecord*)(pRows->GetAt(0)->GetRecord());
	m_nParentID = pRecord->m_nTNo;
	//CString strText = pRecord->GetItem(3)->GetCaption(NULL);
	//if(strText.IsEmpty()) return;

	if(m_ui.nWNo != pRecord->m_nWNo || m_ui.nCompany != pRecord->m_nWCompany)
	{
		MessageBox("자신이 작성한 글만 수정 가능합니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strMent = pRecord->GetItem(3)->GetCaption(NULL);
	strMent.Replace("┗", "");
	strMent.TrimLeft();
	OpenSmallTalkEdit(m_nParentID, strMent);
}

void CRiderShareBoardDlg::OnDeleteTwitter()
{
	CXTPGridSelectedRows *pRows = m_wndTwiReport.GetSelectedRows();
	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	CSmallTalkRecord *pRecord = (CSmallTalkRecord*)(pRows->GetAt(0)->GetRecord());
	m_nParentID = pRecord->m_nTNo;

	if(m_ui.nWNo != pRecord->m_nWNo || m_ui.nCompany != pRecord->m_nWCompany)
	{
		MessageBox("자신이 작석한 글만 삭제 가능합니다", "확인", MB_ICONINFORMATION);
		return;
	}

	if(MessageBox("삭제 하시겠습니까?\r\n하위에 달린 모든 글이 삭제됩니다..", "확인", MB_OKCANCEL) == IDOK)
	{
		if(pRecord == NULL) return;

		CString strName = pRecord->GetItem(1)->GetCaption(NULL);

		if(DeleteTwitter(m_nParentID))
		{
		//	m_edtMsg.SetWindowText("");
			RefreshList();
		}
	}
}


BOOL CRiderShareBoardDlg::UpdateTwitter(long nParentID, CString strMsg)
{
	CMkCommand pCmd(m_pMkDb, "update_twitter");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(nParentID);
	pCmd.AddParameter(strMsg);

	if(pCmd.Execute())
	{
		long nRet; parRet->GetValue(nRet);

		if(nRet == 10)
		{
			AfxMessageBox("해당 게시물은 삭제 되었습니다", MB_ICONINFORMATION);
			return TRUE;
		}
		return TRUE;
	}

	return FALSE;
}


BOOL CRiderShareBoardDlg::WriteTwitter(long nParentID,CString strMsg, long nRiderCompany, long nRNo, CString strRName)
{
	/*
	if(strMsg.GetLength() < 5)
	{
		AfxMessageBox("5자이상으로 입력하여 주세요", MB_ICONINFORMATION);
		return FALSE;
	}
	*/

	CMkCommand pCmd(m_pMkDb, "insert_twitter_new");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(nParentID);
	pCmd.AddParameter(strMsg);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ci.GetName(m_ui.nCompany) + "/" + m_ui.strName);
	pCmd.AddParameter(m_ui.strID);
	pCmd.AddParameter(nRiderCompany);
	pCmd.AddParameter(nRNo);
	pCmd.AddParameter(strRName);

	//pCmd.AddParameter(m_ui.sLogiStaffName);

	if(pCmd.Execute())
	{
		long nRet; parRet->GetValue(nRet);

		if(nRet == 10)
		{
			AfxMessageBox("해당 게시물은 삭제 되었습니다", MB_ICONINFORMATION);
			return TRUE;
		}

		return TRUE;
	}

	return FALSE;
}

void CRiderShareBoardDlg::MoveTalkEdit(BOOL bUpdate)
{
	if(m_pSmallTalkEditDlg == NULL)
		return;

	CXTPGridSelectedRows *pRows = m_wndTwiReport.GetSelectedRows();
	CXTPGridRow *pRow = pRows->GetAt(0);
	CXTPGridRecord *pRecord = pRow->GetRecord();

	CRect rcRow, rcDlg;
	//rcRow = pRow->GetRect();
	rcRow = pRow->GetItemRect(pRecord->GetItem(3));
	m_wndTwiReport.ClientToScreen(rcRow);

	m_pSmallTalkEditDlg->GetWindowRect(rcDlg);
	ScreenToClient(rcDlg);
	rcDlg.left = rcRow.left;
	rcDlg.right = rcRow.right;

	long nHeight = rcDlg.Height();

	if(bUpdate == FALSE)
		rcDlg.top = rcRow.bottom;
	else
		rcDlg.top = rcRow.top;

	rcDlg.bottom = rcDlg.top + nHeight;

	m_pSmallTalkEditDlg->MoveWindow(rcDlg);
	m_pSmallTalkEditDlg->MoveControl();
}

BOOL CRiderShareBoardDlg::DeleteTwitter(long nParent)
{
	if(nParent == 0)
	{
		AfxMessageBox("삭제 할 메세지를 선택하세요", MB_ICONINFORMATION);
		return FALSE;
	}
 
	CMkCommand pCmd(m_pMkDb, "delete_twitter");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(nParent);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ci.GetName(m_ui.nCompany) + "/" + m_ui.strName);

	if(pCmd.Execute())
	{
		long nRet; parRet->GetValue(nRet);

		if(nRet == 10)
		{
			AfxMessageBox("해당 게시물은 삭제 되었습니다", MB_ICONINFORMATION);
			return TRUE;
		}

		return TRUE;
	} 

	return FALSE;
}

void CRiderShareBoardDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	OnSeeTwitter();
}

void CRiderShareBoardDlg::OnBnClickedInsertBtn()
{
	OpenAddRiderShareInfoDlg();
}

void CRiderShareBoardDlg::OpenAddRiderShareInfoDlg(long nRiderCompany, long nRNo, CString strRName)
{
	if(m_pAddRiderShareInfoDlg == NULL)
	{
		m_pAddRiderShareInfoDlg = new CAddRiderShareInfoDlg(this);
		m_pAddRiderShareInfoDlg->Create(IDD_ADD_RIDER_SHARE_INFO_DLG, this);
	}
	else
	{
		WINDOWPLACEMENT wndpl;
		wndpl.length = sizeof(WINDOWPLACEMENT);
		m_pAddRiderShareInfoDlg->GetWindowPlacement(&wndpl);
		m_pAddRiderShareInfoDlg->SetForegroundWindow();
		m_pAddRiderShareInfoDlg->SetFocus();
	}

	m_pAddRiderShareInfoDlg->m_nRiderCompany = nRiderCompany;
	m_pAddRiderShareInfoDlg->m_nRNo = nRNo;
	m_pAddRiderShareInfoDlg->m_strRName = strRName;
	m_pAddRiderShareInfoDlg->ShowWindow(TRUE);

	/*
	CAddRiderShareInfoDlg dlg;
	dlg.m_nRiderCompany = nRiderCompany;
	dlg.m_nRNo = nRNo;
	dlg.m_strRName = strRName;

	if(dlg.DoModal() == IDOK)
	{
		m_nRiderCompany = dlg.m_nRiderCompany;
		m_nRNo = dlg.m_nRNo;
		m_strRName = dlg.m_strRName;
		
		if(WriteTwitter(0, dlg.m_strMsg, m_nRiderCompany, m_nRNo, m_strRName))
		{
			RefreshList();
		}
	}
	*/
}

void CRiderShareBoardDlg::AddRiderInfo()
{
	if(m_pAddRiderShareInfoDlg == NULL)
		return;

	m_nRiderCompany = m_pAddRiderShareInfoDlg->m_nRiderCompany;
	m_nRNo = m_pAddRiderShareInfoDlg->m_nRNo;
	m_strRName = m_pAddRiderShareInfoDlg->m_strRName;
		
	if(WriteTwitter(0, m_pAddRiderShareInfoDlg->m_strMsg, m_nRiderCompany, m_nRNo, m_strRName))
		RefreshList();
}

void CRiderShareBoardDlg::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	m_wndTwiReport.GetSelectedRows()->Select(pItemNotify->pRow);

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_wndTwiReport, pt);
}
void CRiderShareBoardDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(m_wndTwiReport.GetSafeHwnd())
		m_wndTwiReport.SetWindowPos(NULL, 0, 0/*MAP_TOP*/, cx, cy, SWP_NOZORDER);
}

void CRiderShareBoardDlg::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent);
	OpenAddRiderShareInfoDlg(m_nRiderCompany, m_nRNo, m_strRName);

	CMyDialog::OnTimer(nIDEvent);
}
