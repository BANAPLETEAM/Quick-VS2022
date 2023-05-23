// SmartCallBoardDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "SmartCallBoardDlg.h"
#include "SmartCallBoardAddDlg.h"
#include "SmartCallEventReqLogDlg.h"


// CSmartCallBoardDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSmartCallBoardDlg, CMyDialog)

CSmartCallBoardDlg::CSmartCallBoardDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSmartCallBoardDlg::IDD, pParent)
{

}

CSmartCallBoardDlg::~CSmartCallBoardDlg()
{
}

void CSmartCallBoardDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_lstReport);
}


BEGIN_MESSAGE_MAP(CSmartCallBoardDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CSmartCallBoardDlg::OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_INSERT_BTN, &CSmartCallBoardDlg::OnBnClickedInsertBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CSmartCallBoardDlg::OnBnClickedCloseBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_LIST, OnReportItemDblClick)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_DELETE, OnDelete)
	ON_COMMAND(ID_LOG, OnLog)
END_MESSAGE_MAP()


// CSmartCallBoardDlg �޽��� ó�����Դϴ�.

BOOL CSmartCallBoardDlg::OnInitDialog()
{ 
	CMyDialog::OnInitDialog();

	m_lstReport.InsertColumn(0, "�۹�ȣ", LVCFMT_CENTER, 45);
	m_lstReport.InsertColumn(1, "�����", LVCFMT_CENTER, 100);
	m_lstReport.InsertColumn(2, "����", LVCFMT_LEFT, 150);
	m_lstReport.InsertColumn(3, "����", LVCFMT_LEFT, 220);
	m_lstReport.InsertColumn(4, "url", LVCFMT_LEFT, 0);
	m_lstReport.InsertColumn(5, "�������ϸ���", LVCFMT_RIGHT, 80);
	m_lstReport.InsertColumn(6, "�ּһ��Ƚ��", LVCFMT_RIGHT, 80);
	m_lstReport.InsertColumn(7, "�������", LVCFMT_LEFT, 80);	
	m_lstReport.InsertColumn(8, "���", LVCFMT_CENTER, 50);
	m_lstReport.Populate();

	m_lstReport.GetColumns()->GetAt(4)->SetVisible(FALSE);

	if(!m_bEventBoard)
	{
		m_lstReport.GetColumns()->GetAt(5)->SetVisible(FALSE);
		m_lstReport.GetColumns()->GetAt(6)->SetVisible(FALSE);
		m_lstReport.GetColumns()->GetAt(7)->SetVisible(FALSE);
		m_lstReport.GetColumns()->GetAt(8)->SetVisible(FALSE);
	}


	RefreshList();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CSmartCallBoardDlg::RefreshList()
{ 
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_smart_call_board");
	cmd.AddParameter(m_nBoardIndex);

	if(!rs.Execute(&cmd))
		return;

	m_lstReport.GetRecords()->RemoveAll();

	long nID, nSubMileage, nMinUseCount, nOrderInsertType;
	CString strTitle, strBody, strEventImageUrl;
	COleDateTime dtRegister;
	BOOL bPlaying;

	for(long i = 0; i < rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("sTitle", strTitle);
		rs.GetFieldValue("sBody", strBody);
		rs.GetFieldValue("dtRegister", dtRegister);
		rs.GetFieldValue("sEventImageUrl", strEventImageUrl);
		rs.GetFieldValue("nSubMileage", nSubMileage);
		rs.GetFieldValue("nMinUseCount", nMinUseCount);
		rs.GetFieldValue("nOrderInsertType", nOrderInsertType);
		rs.GetFieldValue("bPlaying", bPlaying);

		m_lstReport.InsertItem(i, LF->GetStringFromLong(nID));
		m_lstReport.SetItemText(i, 1, dtRegister.Format("%Y-%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 2, strTitle);
		m_lstReport.SetItemText(i, 3, strBody);
		m_lstReport.SetItemText(i, 4, strEventImageUrl);
		m_lstReport.SetItemText(i, 5, LF->GetMyNumberFormat(nSubMileage));
		m_lstReport.SetItemText(i, 6, LF->GetMyNumberFormat(nMinUseCount));
		m_lstReport.SetItemText(i, 7, GetOrderInsertType(nOrderInsertType));
		m_lstReport.SetItemText(i, 8, bPlaying == TRUE ? "��" : "");
		m_lstReport.SetItemLong(i, nID);
		m_lstReport.SetItemLong2(i, nOrderInsertType);

		rs.MoveNext();
	}

	m_lstReport.Populate();
}

CString CSmartCallBoardDlg::GetOrderInsertType(long nOrderInsertType)
{
	if(nOrderInsertType == 0) return "";
	if(nOrderInsertType == 1) return "���ε��";
	if(nOrderInsertType == 2) return "���Ƿε��";

	return "N/A";
}

void CSmartCallBoardDlg::OnBnClickedRefreshBtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	RefreshList();
}

void CSmartCallBoardDlg::OnBnClickedInsertBtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	InsertBoard(NULL);
}

void CSmartCallBoardDlg::InsertBoard(CXTPGridRecord *pRecord)
{
	CString strTitle = "";
	CString strBody = "";
	CString strUrl = "";
	CString strMileage = "";
	CString strPlaying = "";
	CString strMinUseCount = "";
	long nIndex = 0;

	CSmartCallBoardAddDlg dlg;
	dlg.m_bEventBoard = m_bEventBoard;

	if(pRecord != NULL)  
	{
		strTitle = pRecord->GetItem(2)->GetCaption(NULL);
		strBody = pRecord->GetItem(3)->GetCaption(NULL);
		strUrl = pRecord->GetItem(4)->GetCaption(NULL);
		strMileage = pRecord->GetItem(5)->GetCaption(NULL);
		strMinUseCount = pRecord->GetItem(6)->GetCaption(NULL);
		strPlaying = pRecord->GetItem(8)->GetCaption(NULL);

		nIndex = m_lstReport.GetItemLong(pRecord);
	}

	dlg.m_strTitle = strTitle;
	dlg.m_strBody = strBody;
	dlg.m_strUrl = strUrl;
	dlg.m_strMileage = strMileage;
	dlg.m_nMinUseCount = atoi(strMinUseCount);
	dlg.m_nOrderInsertType = pRecord ? m_lstReport.GetItemLong2(pRecord) : 0;
	dlg.m_bPlaying = strPlaying.IsEmpty() == FALSE ? TRUE : FALSE;

 	if(dlg.DoModal() == IDOK)
 	{
 		CMkCommand cmd(m_pMkDb, "update_smart_call_board_write_3");
 		cmd.AddParameter(m_nCompany);
 		cmd.AddParameter(m_nBoardIndex);
 		cmd.AddParameter(nIndex); 
 		cmd.AddParameter(dlg.m_strTitle);
 		cmd.AddParameter(dlg.m_strBody);
 		cmd.AddParameter(dlg.m_strUrl);
 		dlg.m_strMileage.Replace(",", "");
 		cmd.AddParameter(atoi(dlg.m_strMileage));
 		cmd.AddParameter(dlg.m_nMinUseCount);
 		cmd.AddParameter(dlg.m_nOrderInsertType);
 		cmd.AddParameter(dlg.m_bPlaying);
 		cmd.AddParameter(m_ui.nCompany);
 		cmd.AddParameter(m_ui.nWNo);
 		cmd.AddParameter(m_ui.strName);
 
 		if(cmd.Execute())
 		{
 			if(nIndex == 0) 
 				RefreshList();
 			else
 			{
 				m_lstReport.SetItemText(pRecord, 2, dlg.m_strTitle);
 				m_lstReport.SetItemText(pRecord, 3, dlg.m_strBody);
 				m_lstReport.SetItemText(pRecord, 4, dlg.m_strUrl);
 				m_lstReport.SetItemText(pRecord, 5, LF->GetMyNumberFormat(dlg.m_strMileage));
 				m_lstReport.SetItemText(pRecord, 6, LF->GetMyNumberFormat(dlg.m_nMinUseCount));
 				m_lstReport.SetItemText(pRecord, 7, GetOrderInsertType(dlg.m_nOrderInsertType));
 				m_lstReport.SetItemText(pRecord, 8, dlg.m_bPlaying == TRUE ? "��" : "");
 				m_lstReport.SetItemLong2(pRecord, dlg.m_nOrderInsertType);
 				m_lstReport.RedrawControl();
 			}
 		}
 	}
}

void CSmartCallBoardDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

void CSmartCallBoardDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridRecord *pRecord = GetFirstSelectRecord();

	if(pRecord != NULL)
		InsertBoard(pRecord);
}
void CSmartCallBoardDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU_1);
	CMenu *pRMenu = rMenu.GetSubMenu(13);

	if(!m_bEventBoard)
		pRMenu->RemoveMenu(ID_LOG, MF_BYCOMMAND);

	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CSmartCallBoardDlg::OnDelete()
{
	CXTPGridRecord *pRecord = GetFirstSelectRecord();

	if(!pRecord)
		return;

	long nID = m_lstReport.GetItemLong(pRecord);

	if(MessageBox("�۹�ȣ [" + LF->GetStringFromLong(nID) +"]�� ���� �Ͻðڽ��ϱ�", "Ȯ��", MB_OKCANCEL) != IDOK)
		return;

	CMkCommand cmd(m_pMkDb, "delete_smart_call_board_write");
	cmd.AddParameter(nID);

	if(cmd.Execute())
		RefreshList();
}

void CSmartCallBoardDlg::OnLog()
{
	CXTPGridRecord *pRecord = GetFirstSelectRecord();

	if(!pRecord)
		return;

	CSmartCallEventReqLogDlg dlg;
	dlg.m_nBoardID = m_lstReport.GetItemLong(pRecord);
	dlg.DoModal();
}

CXTPGridRecord* CSmartCallBoardDlg::GetFirstSelectRecord()
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL) return NULL;
	if(pRows->GetCount() == 0) return NULL;

	return pRows->GetAt(0)->GetRecord();
}