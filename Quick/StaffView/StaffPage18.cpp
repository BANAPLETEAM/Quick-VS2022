// Report3.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MainFrm.h"
#include "StaffPage18.h"

// CStaffPage18 대화 상자입니다.

IMPLEMENT_DYNCREATE(CStaffPage18, CMyFormView)
CStaffPage18::CStaffPage18()
: CMyFormView(CStaffPage18::IDD)
{
}

CStaffPage18::~CStaffPage18()
{

}

void CStaffPage18::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_REPORT, m_XTPList);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}


BEGIN_MESSAGE_MAP(CStaffPage18, CMyFormView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefresh)
END_MESSAGE_MAP()


// CStaffPage18 메시지 처리기입니다.


void CStaffPage18::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_edtSearch.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "사번/성명");

	m_XTPList.InsertColumn(0, "순번", LVCFMT_CENTER, 50);
	m_XTPList.InsertColumn(1,"삭제일",LVCFMT_LEFT, 70);
	m_XTPList.InsertColumn(2, "작업자", LVCFMT_LEFT, 60);
	m_XTPList.InsertColumn(3, "사번", LVCFMT_CENTER, 50);
	m_XTPList.InsertColumn(4, "소속", LVCFMT_LEFT, 70);
	m_XTPList.InsertColumn(5, "아이디", LVCFMT_LEFT, 70);
	m_XTPList.InsertColumn(6, "성명", LVCFMT_LEFT, 60);
	m_XTPList.InsertColumn(7, "전화번호", LVCFMT_LEFT, 70);
	m_XTPList.InsertColumn(8, "휴대폰", LVCFMT_LEFT, 70);
	m_XTPList.GetReportHeader()->AllowColumnReorder(FALSE);
	m_XTPList.Populate();

	SetResize(IDC_LIST_REPORT, sizingRightBottom);
}

void CStaffPage18::RefreshList()
{	
	CMyFormView::RefreshList();
	m_XTPList.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_delete_rider_log");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), GetCurBranchInfo()->bIntegrated);
	pCmd.Execute();
	
	if(!pRs.Execute(&pCmd))
		return;

	int nRecordCount = pRs.GetRecordCount();
	COleDateTime dtDate;
	CString strWName, strID, strName, strTel, strPhone;
	int nRNo, nCompany;
	nRNo = nCompany = 0;
	for(int i = 0; i < nRecordCount; i++)
	{
		pRs.GetFieldValue("dtChange", dtDate);
		pRs.GetFieldValue("sWName", strWName);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sID", strID);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("sTel", strTel);
		pRs.GetFieldValue("sHP", strPhone);

		m_XTPList.InsertItem(i, GetStringFromLong(i + 1));
		m_XTPList.SetItemText(i, 1, dtDate.Format("%Y-%m-%d"));
		m_XTPList.SetItemText(i, 2, strWName);
		m_XTPList.SetItemText(i, 3, GetStringFromLong(nRNo));
		m_XTPList.SetItemText(i, 4, m_ci.GetBranchName(nCompany));
		m_XTPList.SetItemText(i, 5, strID);
		m_XTPList.SetItemText(i, 6, strName);
		m_XTPList.SetItemText(i, 7, strTel);
		m_XTPList.SetItemText(i, 8, strPhone);

		pRs.MoveNext();
	}

	pRs.Close();
	m_XTPList.Populate();
}

void CStaffPage18::OnBnClickedRefresh()
{
	RefreshList();
}

void CStaffPage18::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_XTPList.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	int nItem = m_XTPList.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {
		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(2);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}
}

void CStaffPage18::OnViewExcel()
{
	if(!POWER_CHECK(5900, "엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nCompanyCode, 407, m_XTPList.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_XTPList);
}

void CStaffPage18::OnEnChangeSearchEdit()
{
	CString strSearch;
	m_edtSearch.GetWindowText(strSearch);

	if(strSearch.GetLength() == 0)
		m_XTPList.ShowAllRow();
	else
	{
		CXTPGridRecords *pRecords = m_XTPList.GetRecords();

		for(int i = 0; i < pRecords->GetCount(); i++)
		{
			BOOL bVisible = TRUE;
			CXTPGridRecord *pRecord = pRecords->GetAt(i);

			CString strRNo = m_XTPList.GetItemText(pRecord, 3);
			CString strName = m_XTPList.GetItemText(pRecord, 6);

			if(strRNo.Find(strSearch) == -1 && strName.Find(strName) == -1)
				bVisible = FALSE;

			pRecord->SetVisible(bVisible);
		}
	}

	m_XTPList.Populate();
}