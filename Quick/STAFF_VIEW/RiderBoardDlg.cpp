// VarietyDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderBoardDlg.h"
#include "RiderBoardAddDlg.h"


// CRiderBoardDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderBoardDlg, CMyDialog)
CRiderBoardDlg::CRiderBoardDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderBoardDlg::IDD, pParent)
{
}

CRiderBoardDlg::~CRiderBoardDlg()
{
}

void CRiderBoardDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_BOARD, m_lstReport);
	DDX_Control(pDX, IDC_STATE_COMBO, m_cmbState);
}


BEGIN_MESSAGE_MAP(CRiderBoardDlg, CMyDialog)
	ON_CBN_SELCHANGE(IDC_STATE_COMBO, &CRiderBoardDlg::OnCbnSelchangeStateCombo)
	ON_BN_CLICKED(IDC_ADD_BTN, &CRiderBoardDlg::OnBnClickedAddBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_BOARD, OnReportItemDblClick)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CRiderBoardDlg::OnBnClickedSearchBtn)
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CRiderBoardDlg::OnDelete()
{
	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(!pRecord)
		return;

	if(MessageBox("삭제 하시겠습니까?", "확인", MB_OKCANCEL) != IDOK)
		return;

	CMkCommand cmd(m_pMkDb, "delete_rider_board");
	cmd.AddParameter(m_lstReport.GetItemLong(pRecord));

	if(cmd.Execute())
	{
		MessageBox("삭제되었습니다", "확인", MB_ICONINFORMATION);
		RefreshList();
	}
}

void CRiderBoardDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(!pRecord)
		return;

	CRiderBoardAddDlg dlg;
	dlg.m_nIndex = m_lstReport.GetItemLong(pRecord);

	if(dlg.DoModal() == IDOK)
		RefreshList();

}

BOOL CRiderBoardDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_cmbState.SetCurSel(0);

	m_lstReport.InsertColumn(0, "등록일", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(1, "제목", LVCFMT_LEFT, 150);
	m_lstReport.InsertColumn(2, "내용", LVCFMT_LEFT, 250);
	m_lstReport.InsertColumn(3, "보임", LVCFMT_CENTER, 50);
	m_lstReport.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRiderBoardDlg::RefreshList()
{
	m_lstReport.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rider_board");
	cmd.AddParameter(m_ci.m_nShareCode1);

	if(!rs.Execute(&cmd))
		return;

	long nIndex;
	COleDateTime dtGenerate;
	CString strTitle, strMemo;
	BOOL bShow;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nIndex", nIndex);
		rs.GetFieldValue("dtGenerate", dtGenerate);
		rs.GetFieldValue("sTitle", strTitle);
		rs.GetFieldValue("sMemo", strMemo);
		rs.GetFieldValue("bShow", bShow);

		m_lstReport.InsertItem(i, dtGenerate.Format("%y-%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 1, strTitle);
		m_lstReport.SetItemText(i, 2, strMemo);
		m_lstReport.SetItemText(i, 3, bShow ? "ㅇ" : "");
		m_lstReport.SetItemLong(i, nIndex);
		m_lstReport.SetItemLong2(i, bShow);

		rs.MoveNext();
	}

	OnCbnSelchangeStateCombo();
}

void CRiderBoardDlg::OnCbnSelchangeStateCombo()
{
	long nIndex = m_cmbState.GetCurSel();

	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		BOOL bShow = m_lstReport.GetItemLong2(pRecord);

		if((nIndex == 0) ||
			(nIndex == 1 && bShow == TRUE) ||
			(nIndex == 2 && bShow == FALSE))
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstReport.Populate();	
}

void CRiderBoardDlg::OnBnClickedAddBtn()
{
	CRiderBoardAddDlg dlg;
	dlg.m_nIndex = 0;

	if(dlg.DoModal() == IDOK)
		RefreshList();
}

void CRiderBoardDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU_1);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CRiderBoardDlg::OnBnClickedSearchBtn()
{
	RefreshList();
}

void CRiderBoardDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(m_lstReport.GetSafeHwnd())
	{
		CRect rcForm, rcList;
		GetClientRect(rcForm);
		m_lstReport.GetWindowRect(rcList);
		ScreenToClient(rcList);

		rcList.right = rcForm.right - 2;
		rcList.bottom = rcForm.bottom - 2;
		m_lstReport.MoveWindow(rcList);
	}
}
