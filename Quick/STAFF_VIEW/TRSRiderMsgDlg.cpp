#include "stdafx.h"
#include "resource.h"
#include "TRSRiderMsgDlg.h"
#include "TRSInsertRiderDlg.h"
// CTRSRiderMsgDlg 대화 상자입니다.

#define ID_TRS_RIDER_DELETE 1000

IMPLEMENT_DYNAMIC(CTRSRiderMsgDlg, CMyDialog)
CTRSRiderMsgDlg::CTRSRiderMsgDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CTRSRiderMsgDlg::IDD, pParent)
{
	
}

CTRSRiderMsgDlg::~CTRSRiderMsgDlg()
{
}

void CTRSRiderMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RIDER_REPORT, m_lstNonRegRider);
	DDX_Control(pDX, IDC_TRS_MSG_REPORT, m_lstTRSMsg);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtNonRegRiderSearch);
	DDX_Control(pDX, IDC_SEARCH_EDIT2, m_edtTRSMsgSearch);
}


BEGIN_MESSAGE_MAP(CTRSRiderMsgDlg, CMyDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_RIDER_REPORT, OnNonRegRiderReportItemDbClick)
	ON_NOTIFY(NM_RCLICK, IDC_TRS_MSG_REPORT, OnTRSReportItemRClick)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshNonRegRider)
	ON_BN_CLICKED(IDC_TRS_MSG_REFRESH_BTN, OnBnClickedRefreshTRSMsg)
	ON_COMMAND(ID_TRS_RIDER_DELETE, OnDeleteTRSRider)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeNonRegSearchEdit)
	ON_EN_CHANGE(IDC_SEARCH_EDIT2, OnEnChangeTRSMsgSearchEdit)
END_MESSAGE_MAP()

BOOL CTRSRiderMsgDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_lstNonRegRider.InsertColumn(0, "소속회사", LVCFMT_LEFT, 100);
	m_lstNonRegRider.InsertColumn(1, "기사번호", LVCFMT_CENTER, 50);
	m_lstNonRegRider.InsertColumn(2, "기사이름", LVCFMT_LEFT, 70);
	m_lstNonRegRider.Populate();

	m_lstTRSMsg.InsertColumn(0, "소속회사", LVCFMT_LEFT, 100);
	m_lstTRSMsg.InsertColumn(1, "기사번호", LVCFMT_CENTER, 50);
	m_lstTRSMsg.InsertColumn(2, "기사이름", LVCFMT_LEFT, 70);
	m_lstTRSMsg.InsertColumn(3, "내선번호", LVCFMT_LEFT, 60);
	m_lstTRSMsg.InsertColumn(4, "전화번호", LVCFMT_LEFT, 100);
	m_lstTRSMsg.InsertColumn(5, "비밀번호", LVCFMT_LEFT, 70);
	m_lstTRSMsg.InsertColumn(6, "요청일", LVCFMT_CENTER, 120);
	m_lstTRSMsg.InsertColumn(7, "요청자", LVCFMT_LEFT, 70);
	m_lstTRSMsg.InsertColumn(8, "등록여부", LVCFMT_LEFT, 70);
	m_lstTRSMsg.InsertColumn(9, "등록자", LVCFMT_CENTER, 70);
	m_lstTRSMsg.Populate();

	RefreshNonRegRiderList();
	RefreshTRSMsgList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CTRSRiderMsgDlg::RefreshNonRegRiderList()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_trs_non_register_rider");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);

	if(!rs.Execute(&cmd))
		return;

	m_lstNonRegRider.GetRecords()->RemoveAll();
	
	int nRCompany, nRNo;
	CString sRName;
	for (int nIndex = 0 ; nIndex < rs.GetRecordCount() ; nIndex++)
	{
		rs.GetFieldValue("nRCompany", nRCompany);
		rs.GetFieldValue("nRNo", nRNo);
		rs.GetFieldValue("sName", sRName);;

		m_lstNonRegRider.InsertItem(nIndex, LF->GetBranchInfo(nRCompany)->strBranchName);
		m_lstNonRegRider.SetItemText(nIndex, 1, LF->GetStringFromLong(nRNo));
		m_lstNonRegRider.SetItemText(nIndex, 2, sRName);
		m_lstNonRegRider.SetItemLong(nIndex, nRCompany);
		m_lstNonRegRider.SetItemLong2(nIndex, nRNo);

		rs.MoveNext();
	}

	rs.Close();

	NonRegSearchRecord();
}

void CTRSRiderMsgDlg::RefreshTRSMsgList()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_trs_rider");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);

	if(!rs.Execute(&cmd))
		return;

	m_lstTRSMsg.GetRecords()->RemoveAll();

	int nIndex = 0, nRCompany, nRNo;
	CString strRName, strExten, strPhone, strPW, strWName;
	CString strUpdateExten, strUpdatePhone, strUpdatePW, strUpdateWName;
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
		rs.GetFieldValue("sUpdateExten", strUpdateExten);
		rs.GetFieldValue("sUpdatePhone", strUpdatePhone);
		rs.GetFieldValue("sUpdatePW", strUpdatePW);
		rs.GetFieldValue("sUpdateWName", strUpdateWName);

		if(dtUpdate.GetStatus() == COleDateTime::null)
		{
			rs.MoveNext();
			continue;
		}

		m_lstTRSMsg.InsertItem(nIndex, LF->GetBranchInfo(nRCompany)->strBranchName);
		m_lstTRSMsg.SetItemText(nIndex, 1, LF->GetStringFromLong(nRNo));
		m_lstTRSMsg.SetItemText(nIndex, 2, strRName);
		m_lstTRSMsg.SetItemText(nIndex, 3, strUpdateExten.GetLength() == 0 ? "삭제요청" : strUpdateExten);
		m_lstTRSMsg.SetItemText(nIndex, 4, strUpdatePhone.GetLength() == 0 ? "삭제요청" : strUpdatePhone);
		m_lstTRSMsg.SetItemText(nIndex, 5, strUpdatePW.GetLength() == 0 ? "삭제요청" : strUpdatePW);
		m_lstTRSMsg.SetItemText(nIndex, 6, dtUpdate.Format("%Y-%m-%d %H:%M"));
		m_lstTRSMsg.SetItemText(nIndex, 7, strUpdateWName);
		m_lstTRSMsg.SetItemText(nIndex, 8, dtRegister.GetStatus() != COleDateTime::null ? "ㅇ" : "");
		m_lstTRSMsg.SetItemText(nIndex, 9, strWName);
		m_lstTRSMsg.SetItemLong(nIndex, nRCompany);
		m_lstTRSMsg.SetItemLong2(nIndex, nRNo);

		rs.MoveNext();
		nIndex++;
	}

	rs.Close();

	TRSMsgSearchRecord();
}

void CTRSRiderMsgDlg::OnNonRegRiderReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	CXTPGridRecord *pRecord = pItemNotify->pRow->GetRecord();
	if(pRecord)
	{
		CTRSInsertRiderDlg dlg;
		dlg.m_strCompany = m_lstNonRegRider.GetItemText(pRecord, 0);
		dlg.m_strRNo = m_lstNonRegRider.GetItemText(pRecord, 1);
		dlg.m_strRName = m_lstNonRegRider.GetItemText(pRecord, 2);
		if(dlg.DoModal() == IDOK)
		{
			long nRCompany = m_lstNonRegRider.GetItemLong(pRecord);
			long nRNo = m_lstNonRegRider.GetItemLong2(pRecord);

			CString strExten = dlg.m_strExten;
			CString strPhone = LF->GetNoneDashNumber(dlg.m_strPhone);
			CString strPW = dlg.m_strPW;

			if(strExten.GetLength() <= 0 || strPhone.GetLength() <= 0
				|| !LF->IsPhoneNumber(strPhone) || strPW.GetLength() <= 0)
			{
				MessageBox("내선번호, 핸드폰번호, 비밀번호가 잘못입력되었습니다.\n확인해주세요", "확인", MB_ICONEXCLAMATION);
				return;
			}
			
			CMkRecordset rs(m_pMkDb);
			CMkCommand cmd(m_pMkDb, "insert_trs_message_telserver_extension");
			cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
			cmd.AddParameter(nRCompany);
			cmd.AddParameter(nRNo);
			cmd.AddParameter(strExten);
			cmd.AddParameter(strPhone);
			cmd.AddParameter(strPW);
			cmd.AddParameter(m_ui.nCompany);
			cmd.AddParameter(m_ui.nWNo);
			cmd.AddParameter(m_ui.strName);
			CMkParameter *parInsertID = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

			if(!rs.Execute(&cmd))
				return;

			long nInsertID = 0;
			parInsertID->GetValue(nInsertID);
			if(nInsertID > 0)
			{
				MessageBox("서버에 저장되었습니다.\n텔서버 재시작시 적용됩니다.", "확인", MB_ICONEXCLAMATION);
			}
			else
				MessageBox("서버에 저장되지 않았습니다.", "확인", MB_ICONEXCLAMATION);

		}
	}
}

void CTRSRiderMsgDlg::OnTRSReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstTRSMsg, pt);
}

void CTRSRiderMsgDlg::OnBnClickedRefreshNonRegRider()
{
	RefreshNonRegRiderList();
}

void CTRSRiderMsgDlg::OnBnClickedRefreshTRSMsg()
{
	RefreshTRSMsgList();
}

void CTRSRiderMsgDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect, rcAddressList;
	m_lstTRSMsg.GetWindowRect(&rect);

	if(rect.PtInRect(point))
	{
		CXTPGridSelectedRows *pRows = m_lstTRSMsg.GetSelectedRows();

		if(pRows == NULL)
			return; 
		else if(pRows->GetCount() == ZERO)
			return;

		CXTPGridRecord *pRecord = (CXTPGridRecord*)pRows->GetAt(ZERO)->GetRecord();

		if(pRecord == NULL)
			return;

		CString strRName = m_lstTRSMsg.GetItemText(pRecord, 2);

		CMenu *pMenu = new CMenu;
		pMenu->CreatePopupMenu();
		pMenu->AppendMenu(MF_BYCOMMAND, ID_TRS_RIDER_DELETE, strRName + " TRS 작업 삭제");
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}
}

void CTRSRiderMsgDlg::OnDeleteTRSRider()
{

}

void CTRSRiderMsgDlg::OnEnChangeNonRegSearchEdit()
{
	NonRegSearchRecord();
}

void CTRSRiderMsgDlg::NonRegSearchRecord()
{
	CString strSearch;
	m_edtNonRegRiderSearch.GetWindowText(strSearch);

	CXTPGridRecord* pRecord;
	for(int i = 0; i < m_lstNonRegRider.GetRecords()->GetCount(); i++)
	{
		pRecord = m_lstNonRegRider.GetRecords()->GetAt(i);

		CString strRNo = m_lstNonRegRider.GetItemText(pRecord, 1);
		CString strRName =  m_lstNonRegRider.GetItemText(pRecord, 2);

		if(strRNo.Find(strSearch) < 0 && strRName.Find(strSearch) < 0)
			pRecord->SetVisible(FALSE);
		else
			pRecord->SetVisible(TRUE);
	}

	m_lstNonRegRider.Populate();
}

void CTRSRiderMsgDlg::OnEnChangeTRSMsgSearchEdit()
{
	TRSMsgSearchRecord();
}

void CTRSRiderMsgDlg::TRSMsgSearchRecord()
{
	CString strSearch;
	m_edtTRSMsgSearch.GetWindowText(strSearch);

	CXTPGridRecord* pRecord;
	for(int i = 0; i < m_lstTRSMsg.GetRecords()->GetCount(); i++)
	{
		pRecord = m_lstTRSMsg.GetRecords()->GetAt(i);

		CString strRNo = m_lstTRSMsg.GetItemText(pRecord, 1);
		CString strRName =  m_lstTRSMsg.GetItemText(pRecord, 2);
		CString strExten =  m_lstTRSMsg.GetItemText(pRecord, 3);
		CString strPhone =  m_lstTRSMsg.GetItemText(pRecord, 4);
		CString strUpdateWName =  m_lstTRSMsg.GetItemText(pRecord, 7);
		CString strWName =  m_lstTRSMsg.GetItemText(pRecord, 9);

		if(strRNo.Find(strSearch) < 0 && strRName.Find(strSearch) < 0 && strExten.Find(strSearch) < 0
			&& strPhone.Find(strSearch) < 0 && strUpdateWName.Find(strSearch) && strWName.Find(strSearch))
			pRecord->SetVisible(FALSE);
		else
			pRecord->SetVisible(TRUE);
	}

	m_lstTRSMsg.Populate();
}