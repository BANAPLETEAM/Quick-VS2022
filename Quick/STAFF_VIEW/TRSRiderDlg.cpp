#include "stdafx.h"
#include "resource.h"
#include "TRSRiderDlg.h"
#include "TRSRiderMsgDlg.h"
// CTRSRiderDlg 대화 상자입니다.

#define ID_TRS_RIDER_DELETE 1000

IMPLEMENT_DYNAMIC(CTRSRiderDlg, CMyDialog)
CTRSRiderDlg::CTRSRiderDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CTRSRiderDlg::IDD, pParent)
{
	
}

CTRSRiderDlg::~CTRSRiderDlg()
{
}

void CTRSRiderDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RIDER_REPORT, m_lstRider);
	DDX_Control(pDX, IDC_NEAR_RIDER_REPORT, m_lstNearRider);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtRiderSearch);
}


BEGIN_MESSAGE_MAP(CTRSRiderDlg, CMyDialog)
	ON_NOTIFY(NM_CLICK, IDC_RIDER_REPORT, OnRiderReportItemClick)
	ON_NOTIFY(NM_RCLICK, IDC_RIDER_REPORT, OnRiderReportItemRClick)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefresh)
	ON_BN_CLICKED(IDC_TRS_RIDER_BTN, OnBnClickedTRSMsg)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
END_MESSAGE_MAP()

BOOL CTRSRiderDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_lstRider.InsertColumn(0, "소속회사", LVCFMT_LEFT, 100);
	m_lstRider.InsertColumn(1, "기사번호", LVCFMT_CENTER, 50);
	m_lstRider.InsertColumn(2, "기사이름", LVCFMT_LEFT, 70);
	m_lstRider.InsertColumn(3, "내선번호", LVCFMT_LEFT, 60);
	m_lstRider.InsertColumn(4, "전화번호", LVCFMT_LEFT, 100);
	m_lstRider.InsertColumn(5, "비밀번호", LVCFMT_LEFT, 70);
	m_lstRider.InsertColumn(6, "등록일", LVCFMT_CENTER, 120);
	m_lstRider.InsertColumn(7, "등록자", LVCFMT_LEFT, 70);
	m_lstRider.InsertColumn(8, "변경예약", LVCFMT_CENTER, 70);
	m_lstRider.Populate();

	m_lstNearRider.InsertColumn(0, "소속회사", LVCFMT_LEFT, 120);
	m_lstNearRider.InsertColumn(1, "기사번호", LVCFMT_CENTER, 120);
	m_lstNearRider.InsertColumn(2, "기사이름", LVCFMT_LEFT, 70);
	//m_lstNearRider.InsertColumn(3, "사유", LVCFMT_LEFT, 310);
	m_lstNearRider.Populate();

	m_edtRiderSearch.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtRiderSearch.SetUserOption(RGB(0, 0, 0), RGB(245, 245, 245), "검 색");

	RefreshList();
	
	return TRUE;
}

void CTRSRiderDlg::RefreshList()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_trs_rider");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);

	if(!rs.Execute(&cmd))
		return;

	m_lstRider.GetRecords()->RemoveAll();
	
	int nIndex = 0, nRCompany, nRNo;
	CString strRName, strExten, strPhone, strPW, strWName;
	COleDateTime dtRegister, dtUpdate;
	for (int nRecordCount = 0 ; nRecordCount < rs.GetRecordCount() ; nRecordCount++)
	{
		rs.GetFieldValue("nRCompany", nRCompany);
		rs.GetFieldValue("nRNo", nRNo);
		rs.GetFieldValue("sName", strRName);
		rs.GetFieldValue("sExten", strExten);
		rs.GetFieldValue("sPhone", strPhone);
		rs.GetFieldValue("sPW", strPW);
		rs.GetFieldValue("dtRegister", dtRegister);
		rs.GetFieldValue("sWName", strWName);
		rs.GetFieldValue("dtUpdate", dtUpdate);

		if(dtRegister.GetStatus() == COleDateTime::null)
		{
			rs.MoveNext();
			continue;
		}

		m_lstRider.InsertItem(nIndex, LF->GetBranchInfo(nRCompany)->strBranchName);
		m_lstRider.SetItemText(nIndex, 1, LF->GetStringFromLong(nRNo));
		m_lstRider.SetItemText(nIndex, 2, strRName);
		m_lstRider.SetItemText(nIndex, 3, strExten);
		m_lstRider.SetItemText(nIndex, 4, strPhone);
		m_lstRider.SetItemText(nIndex, 5, strPW);
		m_lstRider.SetItemText(nIndex, 6, dtRegister.Format("%Y-%m-%d %H:%M"));
		m_lstRider.SetItemText(nIndex, 7, strWName);
		m_lstRider.SetItemText(nIndex, 8, dtUpdate.GetStatus() != COleDateTime::null ? "ㅇ" : "");

		rs.MoveNext();
		nIndex++;
	}

	rs.Close();

	SearchRecord();
}


void CTRSRiderDlg::OnRiderReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();
}



void CTRSRiderDlg::OnRiderReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstRider, pt);
}

void CTRSRiderDlg::OnBnClickedRefresh()
{
	RefreshList();
}

void CTRSRiderDlg::OnBnClickedTRSMsg()
{
	CTRSRiderMsgDlg dlg;
	dlg.DoModal();
}

void CTRSRiderDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect, rcAddressList;
	m_lstRider.GetWindowRect(&rect);

	if(rect.PtInRect(point))
	{
		CXTPGridSelectedRows *pRows = m_lstRider.GetSelectedRows();

		if(pRows == NULL)
			return; 
		else if(pRows->GetCount() == ZERO)
			return;

		CXTPGridRecord *pRecord = (CXTPGridRecord*)pRows->GetAt(ZERO)->GetRecord();

		if(pRecord == NULL)
			return;

		CString strRName = m_lstRider.GetItemText(pRecord, 2);

		CMenu *pMenu = new CMenu;
		pMenu->CreatePopupMenu();
		pMenu->AppendMenu(MF_BYCOMMAND, ID_TRS_RIDER_DELETE, strRName + " TRS 삭제");
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}
}

void CTRSRiderDlg::OnEnChangeSearchEdit()
{
	SearchRecord();
}

void CTRSRiderDlg::SearchRecord()
{
	CString strSearch;
	m_edtRiderSearch.GetWindowText(strSearch);

	CXTPGridRecord* pRecord;
	for(int i = 0; i < m_lstRider.GetRecords()->GetCount(); i++)
	{
		pRecord = m_lstRider.GetRecords()->GetAt(i);

		CString strRNo = m_lstRider.GetItemText(pRecord, 1);
		CString strRName =  m_lstRider.GetItemText(pRecord, 2);
		CString strExten =  m_lstRider.GetItemText(pRecord, 3);
		CString strPhone =  m_lstRider.GetItemText(pRecord, 4);
		CString strWName =  m_lstRider.GetItemText(pRecord, 7);

		if(strRNo.Find(strSearch) < 0 && strRName.Find(strSearch) < 0 && strExten.Find(strSearch) < 0
			&& strPhone.Find(strSearch) < 0 && strWName.Find(strSearch))
			pRecord->SetVisible(FALSE);
		else
			pRecord->SetVisible(TRUE);
	}

	m_lstRider.Populate();
}