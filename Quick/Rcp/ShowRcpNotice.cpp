// ShowRcpNotice.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "quick.h"
#include "ShowRcpNotice.h"
#include ".\showrcpnotice.h"
#include "AddRcpNoticeDlg.h"

// CShowRcpNotice 대화 상자입니다.

IMPLEMENT_DYNAMIC(CShowRcpNotice, CMyDialog)
CShowRcpNotice::CShowRcpNotice(CWnd* pParent /*=NULL*/)
: CMyDialog(CShowRcpNotice::IDD, pParent)
, m_dtFrom(COleDateTime::GetCurrentTime())
, m_dtTo(COleDateTime::GetCurrentTime())
{
}

CShowRcpNotice::~CShowRcpNotice()
{
}

void CShowRcpNotice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_dtpFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_dtpTo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnData);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_btnRefresh);
}


BEGIN_MESSAGE_MAP(CShowRcpNotice, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnLvnItemchangedList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMClickList1)
	ON_BN_CLICKED(IDC_EDIT_BTN, OnBnClickedEditBtn)
	ON_BN_CLICKED(IDC_ADD_BTN, OnBnClickedAddBtn)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CShowRcpNotice::OnBnClickedRefreshBtn)
	ON_COMMAND(ID_REV_RELEASE, OnRevRelease)
	ON_COMMAND(ID_REV_DELETE, OnRevDelete)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnReportItemRClick)
END_MESSAGE_MAP()


// CShowRcpNotice 메시지 처리기입니다.

BOOL CShowRcpNotice::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 
	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_FLATSB);

	long nCol = 0; 

	m_List.InsertColumn(nCol++, "예약", LVCFMT_CENTER, 35);
	m_List.InsertColumn(nCol++, "일시", LVCFMT_LEFT, 150);
	m_List.InsertColumn(nCol++, "등록자", LVCFMT_LEFT, 80);
	if(m_bIntegrated)
		m_List.InsertColumn(nCol++, "소속", LVCFMT_LEFT, 80);
	m_List.InsertColumn(nCol++, "내용", LVCFMT_LEFT, 500);

	m_List.Populate();

	m_btnData.InitDateButton(&m_dtpFrom, &m_dtpTo);
	//m_btnData.SetIncludeToday(TRUE);
	m_btnData.OnMenuWeekIncludeToday(); 
	UpdateData(TRUE); 

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CShowRcpNotice::RefreshList()
{
	m_List.DeleteAllItems();

	//m_dtTo.SetDateTime(m_dtTo.GetYear(), m_dtTo.GetMonth(), m_dtTo.GetDay(),23,59,59);
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rcp_notice_new");
	cmd.AddParameter(m_nCompanyCode); 
	cmd.AddParameter(m_bIntegrated);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);

	if(!rs.Execute(&cmd)) return;

	long nTNo, nCompany;
	COleDateTime dt;
	CString strUser, strNotice;
	BOOL bRev;
	long nItem = 0;

	while(!rs.IsEOF())
	{
		rs.GetFieldValue("nCompany", nCompany);
		rs.GetFieldValue("nTNo", nTNo);
		rs.GetFieldValue("dt0", dt);
		rs.GetFieldValue("sCName", strUser);
		rs.GetFieldValue("sEtc", strNotice);
		rs.GetFieldValue("bRev", bRev);

		int nCol = 1;

		m_List.InsertItem(nItem, bRev == TRUE ? "ㅇ" : "");
		CString strUser2 = "(" + strUser + ")";
		m_List.SetItemText(nItem, nCol++, dt.Format("%Y-%m-%d [%H:%M:%S]"));
		m_List.SetItemText(nItem, nCol++, strUser2);
		if(m_bIntegrated)
			m_List.SetItemText(nItem, nCol++, m_ci.GetCompanyName(nCompany));
		m_List.SetItemText(nItem, nCol++, strNotice);
		m_List.SetItemData(nItem, nTNo);	
		m_List.SetItemLong(nItem++, bRev);

		rs.MoveNext();
	}

	m_List.Populate();
}


void CShowRcpNotice::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}

void CShowRcpNotice::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

void CShowRcpNotice::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{/*
 LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
 if(pNMLV->iItem >= 0)
 MessageBox(m_List.GetItemText(pNMLV->iItem, 2), m_List.GetItemText(pNMLV->iItem, 0), MB_ICONINFORMATION);
 */
	OnBnClickedEditBtn();
	*pResult = 0;
}


void CShowRcpNotice::OnBnClickedEditBtn()
{
	int nSelItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nSelItem < 0) return;

	BOOL bRev =  m_List.GetItemLong(nSelItem);

	CAddRcpNoticeDlg dlg;
	dlg.m_bReadOnly = TRUE;
	dlg.m_strNotice = m_List.GetItemText(nSelItem,  m_bIntegrated ? 4 : 3);
	dlg.m_bRevNotice = bRev;

	if(dlg.m_bRevNotice)
	{ 
		CString strDate = m_List.GetItemText(nSelItem, 1);

		long nYear = atoi(strDate.Left(4));
		long nMonth = atoi(strDate.Mid(5, 2));
		long nDay = atoi(strDate.Mid(8, 2));
		long nHour = atoi(strDate.Mid(12, 2));
		long nMinute = atoi(strDate.Mid(15, 2));

		dlg.m_dtRevDate.SetDate(nYear, nMonth, nDay);
		dlg.m_dtRevTime.SetTime(nHour, nMinute, 0);
	}

	if(IDOK == dlg.DoModal())
	{
		CMkCommand cmd(m_pMkDb, "update_rcp_notice_new");
		CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(long));
		cmd.AddParameter((int)m_List.GetItemData(nSelItem));
		cmd.AddParameter(m_ui.nWNo); 
		cmd.AddParameter(m_ui.strName); 
		cmd.AddParameter(dlg.m_strNotice); 
		cmd.AddParameter(m_List.GetItemLong(nSelItem));
		cmd.AddParameter(dlg.m_dtRevDateTime);

		if(cmd.Execute())
		{
			m_List.SetItemText(nSelItem, 2, m_ui.strName);
			m_List.SetItemText(nSelItem, m_bIntegrated ? 4 : 3, dlg.m_strNotice);
			MessageBox("수정되었습니다.", "수정됨", MB_ICONINFORMATION);
		}
	}

}

void CShowRcpNotice::OnBnClickedAddBtn()
{
	CAddRcpNoticeDlg dlg;
	dlg.m_bReadOnly = FALSE;
	CString strDummy; 

	if(IDOK == dlg.DoModal())
	{
		//COleDateTime dtReserved = COleDateTime::GetCurrentTime();
		CMkCommand cmd(m_pMkDb, "insert_rcp_notice_new");
		CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(long));
		cmd.AddParameter(m_nCompanyCode);	
		cmd.AddParameter(m_ui.nWNo); 
		cmd.AddParameter(m_ui.strName); 
		cmd.AddParameter(dlg.m_strNotice);
		cmd.AddParameter(dlg.m_bRevNotice);
		cmd.AddParameter(dlg.m_dtRevDateTime);

		COleDateTime dt = COleDateTime::GetCurrentTime();
		//프로시져 실행
		if(cmd.Execute()){
			long nTNo;
			int nCol = 1;
			CString strUser = "(" + m_ui.strName + ")";
			parRet->GetValue(nTNo);
			m_List.InsertItem(0, dt.Format("[%H:%M:%S]"));
			m_List.SetItemText(0, nCol++, strUser);
			if(m_bIntegrated)
				m_List.SetItemText(0, nCol++, m_ci.GetCompanyName(m_nCompanyCode));
			m_List.SetItemText(0, nCol++, dlg.m_strNotice);
			m_List.SetItemData(0, nTNo);			
			MessageBox("등록되었습니다.", "등록됨", MB_ICONINFORMATION);
			RefreshList();
		}
	}
}

void CShowRcpNotice::OnBnClickedRefreshBtn()
{
	UpdateData(TRUE);
	RefreshList();
}

void CShowRcpNotice::OnRevRelease()
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

	BOOL bRev = m_List.GetItemLong(pRecord);

	if(bRev == FALSE)
	{
		MessageBox("예약 항목만 해제 하실 수 있습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	long nID = m_List.GetItemData(pRecord);

	CMkCommand cmd(m_pMkDb, "release_rev_notice");
	cmd.AddParameter(nID);

	if(cmd.Execute())
		RefreshList();

}

void CShowRcpNotice::OnRevDelete()
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

	BOOL bRev = m_List.GetItemLong(pRecord);

	if(bRev == FALSE)
	{
		MessageBox("예약 항목만 삭제 하실 수 있습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	long nID = m_List.GetItemData(pRecord);

	CMkCommand cmd(m_pMkDb, "delete_rev_notice");
	cmd.AddParameter(nID);

	if(cmd.Execute())
		RefreshList();

}

void CShowRcpNotice::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return; 

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(32);

	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}


void CShowRcpNotice::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	m_List.GetSelectedRows()->Select(pItemNotify->pRow);

	if(m_List.GetItemLong(pItemNotify->pRow->GetRecord()) == FALSE)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_List, pt);
}