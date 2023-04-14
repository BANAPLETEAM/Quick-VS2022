// NewConnListDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "NewConnListDlg.h"
#include "MessageRecord.h"
#include "MyReportPaintManager.h"
#include "MkMessenger.h"
#include "MsgPowerDlg.h"
#include "NewMsgDlg.h"
#include "ReportMultilinePaintManager.h"
#include "MsgNoteDlg.h"
#include "SelectMsgSendTypeDlg.h"
#include "MkLock.h"

enum { BULK_SEND_LIST = 0, BULK_SEND_SELECTED = 1, BULK_SEND_SHARECODE = 2, BULK_SEND_COMPANY = 3 };

long CNewConnListRecord::m_nMyCompany = 0;
long CNewConnListRecord::m_nMyWNo = 0;

CNewConnListRecord::CNewConnListRecord(COleDateTime dtLog, 
								   long nCompany,
								   long nWNo,
								   CString strName, 
								   CString strCompany, 
								   long nCompany2,
								   long nWNo2, 
								   CString strName2, 
								   CString strCompany2, 
								   CString strMsg,
								   int nClientType, 
								   int nClientType2)
{
	CString strTarget;

	AddItem(new CXTPGridRecordItemText(dtLog.Format("%m-%d %H:%M:%S")));

	m_strMsg = strMsg;
	m_dtLog = dtLog;

	if(m_nMyCompany == nCompany && m_nMyWNo == nWNo)
	{
		m_nType = 0;

		if(m_nMyCompany == nCompany2 && strName != "전체")
			strTarget = strName2;
		else 
			strTarget = strName2.IsEmpty() ? strCompany2 : strCompany2 + "(" + strName2 + ")";

		m_nTCompany = nCompany2;
		m_nTWNo = nWNo2;
		m_nTClientType = nClientType2;
		m_strTCompany = strCompany2;
		m_strTName = strName2;
	}
	else
	{
		m_nType = 1;

		if(m_nMyCompany == nCompany && strName != "전체")
			strTarget = strName;
		else 
			strTarget = strName.IsEmpty() ? strCompany : strCompany + "(" + strName + ")";

		m_nTCompany = nCompany;
		m_nTWNo = nWNo;
		m_nTClientType = nClientType;
		m_strTCompany = strCompany;
		m_strTName = strName;
	}

	AddItem(new CXTPGridRecordItemText(m_nType == 0 ? ">" : "<"));
	AddItem(new CXTPGridRecordItemText(strTarget));
	AddItem(new CXTPGridRecordItemText(strMsg));
}

void CNewConnListRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	if(pDrawArgs->pColumn && pDrawArgs->pRow)
	{
		int nCol = pDrawArgs->pColumn->GetItemIndex();
		int nRow = pDrawArgs->pRow->GetIndex();
		CNewConnListRecord *pRecord = ((CNewConnListRecord*)pDrawArgs->pRow->GetRecord());

		if(pRecord->m_nType == 1)
		{
			pItemMetrics->clrBackground = RGB(200, 255, 200);
		}
	}
}



// CNewConnListDlg 대화 상자입니다.


IMPLEMENT_DYNAMIC(CNewConnListDlg, CMyResizeDialog)

CNewConnListDlg::CNewConnListDlg(CWnd* pParent /*=NULL*/)
: CMyResizeDialog(CNewConnListDlg::IDD, pParent)
{
	m_pParentWnd = pParent;
	m_bRequestMode = FALSE;
	m_nRequestType = 0;
	m_bQueryChargeMode = FALSE; 
	m_bCloseMode = FALSE;
	m_nFindCompany = 0;
	m_nFindRNo = 0;
	m_bRcpCopyData = FALSE;
	m_pszRcpCopyData = NULL;
	m_bFirstRefresh = TRUE;
	m_pMsgDb = NULL;
	m_hExitHandle = NULL;
	m_hThreadDiedHandle = NULL;
}

CNewConnListDlg::~CNewConnListDlg()
{
	MKLOCK(m_csList);

	if(m_hExitHandle)
	{
		SetEvent(m_hExitHandle);
		WaitForSingleObject(m_hThreadDiedHandle, 2000);
		CloseHandle(m_hExitHandle);
		CloseHandle(m_hThreadDiedHandle);
	}

	/* m_pMsgDb == m_pMkDb 라서 삭제하면 안될듯.. choi
	if(m_pMsgDb)
	{
		m_pMsgDb->Close();
		delete m_pMsgDb;
		m_pMsgDb = NULL;
	}
	*/
}

void CNewConnListDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORTCTRL, m_wndReportCtrl);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_SearchEdit);
	DDX_Control(pDX, IDC_POWER_BTN, m_PowerBtn);
	DDX_Control(pDX, IDC_SHOW_INTERCALL_CHECK, m_chkShowIntercall);
	DDX_Control(pDX, IDC_MY_COMPANY_CHECK, m_chkMyCompany);

	DDX_Control(pDX, IDC_SHOW_TYPE_COMBO, m_cmbShowType);
	DDX_Control(pDX, IDC_SEARCH_HISTORY_EDIT, m_edtSearchHistory);
	DDX_Control(pDX, IDC_DATEFROM, m_dtpFrom);
	DDX_Control(pDX, IDC_DATETO, m_dtpTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_HISTORY_REPORT, m_lstHistory);

	DDX_Control(pDX, IDC_BRANCH_EDIT, m_edtBranch);
	DDX_Control(pDX, IDC_OPEN_BRANCH_BTN, m_btnOpenBranch);
	DDX_Control(pDX, IDC_SEND_EDIT, m_edtSend);
	DDX_Control(pDX, IDC_SHOW_ONLY_ONLINE_CHECK, m_chkShowOnlyOnline);
	DDX_Control(pDX, IDC_HISTORY_RICH_EDIT, m_edtHistoryRich);
}


BEGIN_MESSAGE_MAP(CNewConnListDlg, CMyResizeDialog)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_NOTIFY(NM_CLICK, IDC_REPORTCTRL, OnReportItemClick)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORTCTRL, OnReportItemDblClick)
	ON_BN_CLICKED(IDC_POWER_BTN, &CNewConnListDlg::OnBnClickedPowerBtn)
	ON_BN_CLICKED(IDC_SHOW_INTERCALL_CHECK, OnBnClickedShowIntercallCheck)
	ON_BN_CLICKED(IDC_MY_COMPANY_CHECK, OnBnClickedMyCompanyCheck)
	ON_BN_CLICKED(IDC_REFRESH_HISTORY_BTN, &CNewConnListDlg::OnBnClickedRefreshHistoryBtn)
	ON_CBN_SELCHANGE(IDC_SHOW_TYPE_COMBO, &CNewConnListDlg::OnCbnSelchangeShowTypeCombo)
	ON_EN_CHANGE(IDC_SEARCH_HISTORY_EDIT, &CNewConnListDlg::OnEnChangeSearchHistoryEdit)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CNewConnListDlg::OnEnChangeSearchEdit)
	ON_BN_CLICKED(IDC_SEND_MSG_BTN, &CNewConnListDlg::OnBnClickedSendMsgBtn)
	ON_BN_CLICKED(IDC_SEND_NOTE_MSG_BTN, &CNewConnListDlg::OnBnClickedSendNoteMsgBtn)
	ON_CBN_SELCHANGE(IDC_MAIN_COMBO, &CNewConnListDlg::OnCbnSelchangeMainCombo)
	ON_BN_CLICKED(IDC_SEND_SELECT_BTN, &CNewConnListDlg::OnBnClickedSendSelectBtn)
	ON_BN_CLICKED(IDC_SEND_SEARCH_BTN, &CNewConnListDlg::OnBnClickedSendSearchBtn)
	ON_BN_CLICKED(IDC_SHOW_ONLY_ONLINE_CHECK, &CNewConnListDlg::OnBnClickedShowOnlyOnlineCheck)
	ON_NOTIFY(NM_CLICK, IDC_HISTORY_REPORT, &CNewConnListDlg::OnReportItemHistoryClick)
	ON_NOTIFY(NM_DBLCLK, IDC_HISTORY_REPORT, &CNewConnListDlg::OnReportItemHistoryDblClick)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CNewConnListDlg 메시지 처리기입니다.

BOOL CNewConnListDlg::OnInitDialog()
{
	CMyResizeDialog::OnInitDialog();


#ifndef _SYSMANAGER
	if(POWER_CHECK(1402, "메신저 권한 설정")) {
		m_PowerBtn.ShowWindow(SW_SHOW);
	}
#endif

	CenterWindow();

	m_nMyCompany = ((CMkMessenger*)m_pParentWnd)->GetUserInfo()->nCompanyCode;
	m_nMyWNo = ((CMkMessenger*)m_pParentWnd)->GetUserInfo()->nUserCode;
	m_strMyName = ((CMkMessenger*)m_pParentWnd)->GetUserInfo()->strUserName;
	m_strMyCompanyName = ((CMkMessenger*)m_pParentWnd)->GetUserInfo()->strCompanyName;
	m_strMyBranchName = ((CMkMessenger*)m_pParentWnd)->GetUserInfo()->strBranchName;
	m_nMyShareCode1 = ((CMkMessenger*)m_pParentWnd)->GetUserInfo()->nShareCode1;

	CNewConnListRecord::m_nMyCompany = m_nMyCompany;
	CNewConnListRecord::m_nMyWNo = m_nMyWNo;

	CXTPGridColumn* pCol0 = m_lstHistory.AddColumn(new CXTPGridColumn(0, _T("일자"), 70));
	CXTPGridColumn* pCol1 = m_lstHistory.AddColumn(new CXTPGridColumn(1, _T("타입"), 10));
	CXTPGridColumn* pCol2 = m_lstHistory.AddColumn(new CXTPGridColumn(2, _T("대상"), 105));
	CXTPGridColumn* pCol3 = m_lstHistory.AddColumn(new CXTPGridColumn(3, _T("메시지"), 155));

	pCol0->SetAlignment(DT_LEFT);
	pCol1->SetAlignment(DT_CENTER);
	pCol2->SetAlignment(DT_LEFT);
	pCol3->SetAlignment(DT_LEFT);

	m_lstHistory.SetPaintManager(new CReportMultilinePaintManager);
	m_lstHistory.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_lstHistory.GetPaintManager()->m_strNoItems = "";
	m_lstHistory.ShowHeader(FALSE);
	m_lstHistory.SetTreeIndent(10);
	m_lstHistory.AllowEdit(FALSE);
	m_lstHistory.FocusSubItems(FALSE);
	m_lstHistory.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_lstHistory.SetGridColor(RGB(222, 222, 222));
	m_lstHistory.GetPaintManager()->m_bHideSelection = TRUE;
	m_lstHistory.EnableToolTips(FALSE);
	m_lstHistory.Populate();

	m_cmbShowType.SetCurSel(AfxGetApp()->GetProfileInt("Messenger", "ShowType", 0));
	m_chkMyCompany.SetCheck(AfxGetApp()->GetProfileInt("Messenger", "MyCompany", 0));
	m_chkShowOnlyOnline.SetCheck(AfxGetApp()->GetProfileInt("Messenger", "OnlyOnline", 0));
	m_chkShowIntercall.SetCheck(AfxGetApp()->GetProfileInt("Messenger", "ShowIntercall", 0));

	if(m_chkMyCompany.GetCheck())
	{
		m_edtBranch.EnableWindow(TRUE);
		m_btnOpenBranch.EnableWindow(TRUE);
	}
	
	m_dtpFrom.SetFormat("yyyy-MM-dd HH:00");
	m_dtpTo.SetFormat("yyyy-MM-dd HH:00");

	m_btnDate.InitDateButton((CDateTimeCtrl*)&m_dtpFrom, (CDateTimeCtrl*)&m_dtpTo);
	m_btnDate.OnMenuDayIncludeToday(2);


	CBitmap bmp;
	VERIFY(m_ilIcons.Create(16,16, ILC_COLOR24|ILC_MASK, 0, 1));
	VERIFY(bmp.LoadBitmap(IDB_MSN_STATUS));
	m_ilIcons.Add(&bmp, RGB(255, 0, 255));

	m_wndReportCtrl.SetImageList(&m_ilIcons);
	m_wndReportCtrl.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReportCtrl.SetPaintManager(new CMyReportPaintManager());

	CXTPGridColumn* pColumn = m_wndReportCtrl.AddColumn(new CXTPGridColumn(0, _T("지사명"), 160, FALSE));
	pColumn->SetTreeColumn(1);
	m_wndReportCtrl.AddColumn(new CXTPGridColumn(1, _T("사번"), 30));
	m_wndReportCtrl.AddColumn(new CXTPGridColumn(2, _T("이름"), 80));
	m_wndReportCtrl.AddColumn(new CXTPGridColumn(3, _T("상태"), 30));
	//m_wndReportCtrl.AddColumn(new CXTPGridColumn(4, _T("상태"), 0));

	m_wndReportCtrl.SetTreeIndent(10);
	m_wndReportCtrl.SetGridColor(RGB(222, 222, 222));
	m_wndReportCtrl.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_wndReportCtrl.GetReportHeader()->AllowColumnSort(TRUE);
	m_wndReportCtrl.EnableToolTips(FALSE);	//쓰레드에서 reportctrl쓸때 이거 안하면 다이됨
	m_wndReportCtrl.Populate();

	m_edtHistoryRich.SetAutoURLDetect(1);

	// Set control resizing.
	SetResize(IDC_REPORTCTRL, SZ_TOP_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_HISTORY_REPORT, SZ_TOP_LEFT, SZ_TOP_RIGHT);
	SetResize(IDC_HISTORY_RICH_EDIT, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_SEND_EDIT, SZ_BOTTOM_LEFT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_SEND_SELECT_BTN, SZ_BOTTOM_LEFT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_SEND_SEARCH_BTN, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);


	if(m_bRequestMode || m_bQueryChargeMode || m_bRcpCopyData)
	{ 
		RefreshRequestCompanyList();
		if(m_bCloseMode)
		{
			DirectSendMsg();
			OnOK();
		}
		SetWindowText("담당자 더블클릭 바랍니다.");
	}
	else
	{
		DWORD dwThreadID1;
		HANDLE hThread1=::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) staticRefreshProc, 
			(LPVOID) this, 0, &dwThreadID1);
		CloseHandle(hThread1);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNewConnListDlg::DirectSendMsg()
{
	char buffer[20];

	BOOL bSend = FALSE;

	for(int i=0; i<m_wndReportCtrl.GetRecords()->GetCount();i++)	
	{
		CXTPGridRecord *pRecord = m_wndReportCtrl.GetRecords()->GetAt(i);

		if(pRecord->HasChildren())
		{
			CXTPGridRecords *pChildRecords = pRecord->GetChilds();
			for(int k = 0; k < pChildRecords->GetCount(); k++)
			{
				CMessageRecord *pMsgRecord = (CMessageRecord*)pChildRecords->GetAt(k);

				if(m_nFindCompany == pMsgRecord->m_nCompany && m_nFindRNo == pMsgRecord->m_nMNo)
				{
					CNewMsgDlg *pNewMsgDlg = ((CMkMessenger*)m_pParentWnd)->ShowMsgDlg(
						this,
						"요금문의",  
						ltoa(pMsgRecord->m_nCompany, buffer, 10),
						ltoa(pMsgRecord->m_nMNo, buffer, 10),
						ltoa(pMsgRecord->m_nClientType, buffer, 10),
						pMsgRecord->m_strCompanyName,
						pMsgRecord->m_strName, 
						TRUE);

					g_bana_log->Print(m_szQueryCharge);
					pNewMsgDlg->SendMsg(m_szQueryCharge, TRUE);
					bSend = TRUE;
					break;
				}
			}
		}
	}

	if(bSend)
		OnOK();
	else
		OnCancel();
}

void CNewConnListDlg::OnDestroy() 
{
	CXTResizeDialog::OnDestroy();

	// Save window placement

}

void CNewConnListDlg::RefreshConnList(BOOL bBackground)
{
	CMkRecordset pRs(m_pMsgDb);
	CMkCommand pCmd(m_pMsgDb, "select_msg_conn_list4", 0, bBackground);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nMyCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nMyWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_chkShowIntercall.GetCheck());
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), FALSE);

	if(pRs.Execute(&pCmd)) 
	{
		ClearExistFlag();
		{
			MKLOCK(m_csList);
			while(!pRs.IsEOF()) 
			{
				BOOL bIdle;
				long nCompanyCode, nMNo, nShareCode1;
				CString strCompanyName, strBranchName, strName, strLogin;
				COleDateTime dtLogin;
				int nClientType = 0;

				pRs.GetFieldValue("nCompany", nCompanyCode);
				pRs.GetFieldValue("nMNo", nMNo);
				pRs.GetFieldValue("nShareCode1", nShareCode1);
				pRs.GetFieldValue("bIdle", bIdle);
				pRs.GetFieldValue("sCompanyName", strCompanyName);
				pRs.GetFieldValue("sBranchName", strBranchName);
				pRs.GetFieldValue("sName", strName);
				pRs.GetFieldValue("dtLogin", dtLogin);
				pRs.GetFieldValue("nClientType", nClientType);

				if(m_nMyCompany == nCompanyCode && m_nMyWNo == nMNo)
				{
					pRs.MoveNext();
					continue;
				}

				UpdateUser(nShareCode1, nCompanyCode, nMNo,
					strCompanyName, strBranchName, strName, dtLogin, bIdle ? MSG_STATUS_IDLE : MSG_STATUS_NORMAL,
					nClientType, m_bFirstRefresh && m_ci.IsChildCompany(nCompanyCode));

				pRs.MoveNext();
			}
		}

		CheckExistFlagForDeleting();

#ifndef _SYSMANAGER
		if(!m_chkShowOnlyOnline.GetCheck())
			RefreshAllStaffList();
#endif

		ReportFilter();
		RefreshReport();
		m_bFirstRefresh = FALSE;
		pRs.Close();
	}	
}


void CNewConnListDlg::RefreshRequestCompanyList()
{
	CMkRecordset pRs(m_pMsgDb);
	CMkCommand pCmd(m_pMsgDb, "select_msg_conn_list_request3");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nRequestCompany);
	if(pRs.Execute(&pCmd)) 
	{
		{
			MKLOCK(m_csList);
			
			while(!pRs.IsEOF()) 
			{
				BOOL bIdle;
				BOOL bTakeChargeRequest;
				long nCompanyCode, nMNo, nShareCode1;
				CString strCompanyName, strBranchName, strName, strLogin;
				COleDateTime dtLogin;
				int nClientType = 0;

				pRs.GetFieldValue("nCompany", nCompanyCode);
				pRs.GetFieldValue("nMNo", nMNo);
				pRs.GetFieldValue("nShareCode1", nShareCode1);
				pRs.GetFieldValue("bIdle", bIdle);
				pRs.GetFieldValue("sCompanyName", strCompanyName);
				pRs.GetFieldValue("sBranchName", strBranchName);
				pRs.GetFieldValue("sName", strName);
				pRs.GetFieldValue("dtLogin", dtLogin);
				pRs.GetFieldValue("bTakeChargeRequest", bTakeChargeRequest);
				pRs.GetFieldValue("nClientType", nClientType);

				if(m_nMyCompany == nCompanyCode && m_nMyWNo == nMNo)
				{
					pRs.MoveNext();
					continue;
				}

				if((m_bRequestMode == TRUE) && (bTakeChargeRequest))
				{
					pRs.MoveNext();
					continue;				
				}

				UpdateUser(nShareCode1, nCompanyCode, nMNo,
					strCompanyName, strBranchName, strName, dtLogin, bIdle ? 1 : 0,
					nClientType, TRUE);

				pRs.MoveNext();
			}
		}

		RefreshReport();
		pRs.Close();
	}	
}

void CNewConnListDlg::UpdateUserStatus(long nCompany, long nMNo, int nClientType, int nStatus)
{
	for(int i = 0; i < m_wndReportCtrl.GetRecords()->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = m_wndReportCtrl.GetRecords()->GetAt(i);
		if(pRecord->HasChildren())
		{
			CXTPGridRecords *pChildRecords = pRecord->GetChilds();
			for(int k = 0; k < pChildRecords->GetCount(); k++)
			{
				CMessageRecord *pMsgRecord = (CMessageRecord*)pChildRecords->GetAt(k);
				if(pMsgRecord->CheckUser(nCompany, nMNo, nClientType))
				{
					pMsgRecord->SetStatus(nStatus);
					m_wndReportCtrl.RedrawControl();
					return;
				}
			}
		}
	}
}


void CNewConnListDlg::UpdateUser(long nShareCode1, long nCompany, long nMNo, 
								 CString strCompany, CString strBranch, CString strName, 
								 COleDateTime dtTime, int nStatus, int nClientType, 
								 BOOL bExpand, BOOL bAlreadyExistSkip)
{
	CMessageTitleRecord *pInserted = NULL;

	for(int i = 0; i < m_wndReportCtrl.GetRecords()->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = m_wndReportCtrl.GetRecords()->GetAt(i);
		if(pRecord->HasChildren())
		{
			CMessageTitleRecord *pTitleRecord = (CMessageTitleRecord*)pRecord;
			if(pTitleRecord->CheckShareCode(nShareCode1, nClientType))
			{
				pInserted = pTitleRecord;
			}

			CXTPGridRecords *pChildRecords = pRecord->GetChilds();
			for(int k = 0; k < pChildRecords->GetCount(); k++)
			{
				CMessageRecord *pMsgRecord = (CMessageRecord*)pChildRecords->GetAt(k);
				if(pMsgRecord->CheckUser(nCompany, nMNo, nClientType))
				{
					if(!bAlreadyExistSkip)
					{
						UpdateUserInfo(pMsgRecord, nShareCode1, nCompany, nMNo, strCompany, 
							strBranch, strName, dtTime, nStatus, nClientType);
					}
					return;
				}

			}
		}
	}

	if(!pInserted)
	{
		CString strTemp = strCompany;
		if(nClientType == 1)
			strTemp = "인터콜 고객";
		else if(nClientType == 2)
			strTemp = "인터콜 임시고객";

		pInserted = (CMessageTitleRecord*)InsertSite(nShareCode1, 
			strTemp, nClientType);

		if(bExpand)
			pInserted->SetExpanded(TRUE);
	}

	InsertUser(pInserted, nShareCode1, nCompany, nMNo, strCompany, strBranch, strName, dtTime, nStatus, nClientType);
}

void CNewConnListDlg::UpdateUserInfo(CMessageRecord *pMsgRecord, long nShareCode1, long nCompany, long nMNo, 
									 CString strCompany, CString strBranch, CString strName, 
									 COleDateTime dtTime, int nStatus, int nClientType)
{
	char buffer[15];

	if(nClientType == 0)
	{
		pMsgRecord->GetItem(COL_BRANCH)->SetCaption(strBranch);
		pMsgRecord->GetItem(COL_MNO)->SetCaption(ltoa(nShareCode1 == 200 || nClientType >= 1 ? 0 : nMNo, buffer, 10));
		pMsgRecord->GetItem(COL_NAME_MSG)->SetCaption(strName);
		//pMsgRecord->GetItem(COL_CONN_TIME)->SetCaption(nStatus == MSG_STATUS_NORMAL ? "온라인" : "오프");
	}
	else
	{
		CString strTemp = strBranch;
		if(strName.GetLength() > 0)
			strTemp = strBranch + "/" + strName;

		pMsgRecord->GetItem(COL_BRANCH)->SetCaption(strCompany);
		pMsgRecord->GetItem(COL_MNO)->SetCaption(ltoa(nShareCode1 == 200 || nClientType >= 1 ? 0 : nMNo, buffer, 10));
		pMsgRecord->GetItem(COL_NAME_MSG)->SetCaption(strTemp);
		//pMsgRecord->GetItem(COL_CONN_TIME)->SetCaption(nStatus == MSG_STATUS_NORMAL ? "온라인" : "오프");
	}

	pMsgRecord->SetStatus(nStatus);
	pMsgRecord->m_nShareCode1 = nShareCode1;
	pMsgRecord->m_nCompany = nCompany;
	pMsgRecord->m_nMNo = nMNo;
	pMsgRecord->m_nClientType = nClientType;
	pMsgRecord->SetExistFlag();
}

CXTPGridRecord* CNewConnListDlg::InsertSite(long nShareCode1, CString strSiteName, int nClientType)
{
	CXTPGridRecord* pRecordControl = m_wndReportCtrl.AddRecord(
		new CMessageTitleRecord(nShareCode1, strSiteName, nClientType));

	if(m_bRequestMode || m_bQueryChargeMode || m_bRcpCopyData)
		pRecordControl->SetExpanded(TRUE);
	return pRecordControl;
}


void CNewConnListDlg::InsertUser(CXTPGridRecord *pInserted, 
								 long nShareCode1, long nCompany, long nMNo, 
								 CString strCompany, CString strBranch, CString strName, 
								 COleDateTime dtTime, int nStatus, int nClientType)
{
	pInserted->GetChilds()->Add(
		new CMessageRecord(nShareCode1, nCompany, nMNo, strCompany, strBranch, strName, dtTime, nStatus, nClientType));
}

void CNewConnListDlg::ClearExistFlag()
{
	MKLOCK(m_csList);

	for(int i = 0; i < m_wndReportCtrl.GetRecords()->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = m_wndReportCtrl.GetRecords()->GetAt(i);
		if(pRecord->HasChildren())
		{
			CXTPGridRecords *pChildRecords = pRecord->GetChilds();
			for(int k = 0; k < pChildRecords->GetCount(); k++)
			{
				CMessageRecord *pMsgRecord = (CMessageRecord*)pChildRecords->GetAt(k);
				pMsgRecord->ClearExistFlag();
			}
		}
	}
}


void CNewConnListDlg::CheckExistFlagForDeleting()
{
	MKLOCK(m_csList);

	for(int i = 0; i < m_wndReportCtrl.GetRecords()->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = m_wndReportCtrl.GetRecords()->GetAt(i);
		if(pRecord->HasChildren())
		{
			CXTPGridRecords *pChildRecords = pRecord->GetChilds();
			for(int k = 0; k < pChildRecords->GetCount(); k++)
			{
				CMessageRecord *pMsgRecord = (CMessageRecord*)pChildRecords->GetAt(k);

				if(!pMsgRecord->GetExistFlag())
				{
					if(m_ci.IsChildCompany(pMsgRecord->m_nCompany))
					{
						pMsgRecord->SetStatus(MSG_STATUS_PROTECTED);
					}
					else
					{
						pChildRecords->RemoveAt(k);
						if(pChildRecords->GetCount() == 0)
						{
							m_wndReportCtrl.GetRecords()->RemoveAt(i);
							break;
						}
						k--;
					}
				}

			}
		}
	}
}

void CNewConnListDlg::OnClose()
{
//	if(!m_bRequestMode && !m_bQueryChargeMode && !m_bRcpCopyData) {
//		m_pParentWnd->PostMessage(WM_CLOSE_MSG_CONN_LIST_DLG, 0, 0);
//	}

	SavePlacement(_T("CNewConnListDlg"));
	ShowWindow(SW_HIDE);
//	CXTResizeDialog::OnClose();
}

void CNewConnListDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify =
		(XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if(pItemNotify->pRow)
	{
		CMessageRecord* pRecord = (CMessageRecord*)pItemNotify->pRow->GetRecord();
		RefreshHistoryRich(pRecord->m_nCompany, pRecord->m_nMNo, pRecord->m_nClientType);
	}
}

void CNewConnListDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	char buffer[20];

	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if(pItemNotify->pRow)
	{
		CMessageRecord* pRecord = (CMessageRecord*)pItemNotify->pRow->GetRecord();
		if(!pRecord->HasChildren())
		{
			if(m_bRequestMode)
			{
				CNewMsgDlg *pNewMsgDlg = ((CMkMessenger*)m_pParentWnd)->ShowMsgDlg(
					this,
					m_nRequestType == REQUEST_CANCEL ? "자동취소요청" : "자동재접수요청",  
					ltoa(pRecord->m_nCompany, buffer, 10),
					ltoa(pRecord->m_nMNo, buffer, 10),
					ltoa(pRecord->m_nClientType, buffer, 10),
					pRecord->m_strCompanyName,
					pRecord->m_strName);

				CString strMsg;
				strMsg.Format("수고하십니다!\n오더번호 [%d] 에 대해서 %s 처리 부탁드립니다.", 
					m_nRequestTNo, m_nRequestType == REQUEST_CANCEL ? "취소" : "재접수");
				pNewMsgDlg->SendMsg(strMsg);
				OnOK();
			}
			else if(m_bQueryChargeMode)
			{
				CNewMsgDlg *pNewMsgDlg = ((CMkMessenger*)m_pParentWnd)->ShowMsgDlg(
					this,
					"요금문의",  
					ltoa(pRecord->m_nCompany, buffer, 10),
					ltoa(pRecord->m_nMNo, buffer, 10),
					ltoa(pRecord->m_nClientType, buffer, 10),
					pRecord->m_strCompanyName,
					pRecord->m_strName, 
					TRUE);

				g_bana_log->Print(m_szQueryCharge);
				pNewMsgDlg->SendMsg(m_szQueryCharge, TRUE);
				OnOK();
			}
			else if(m_bRcpCopyData && m_pszRcpCopyData)
			{
				CNewMsgDlg *pNewMsgDlg = ((CMkMessenger*)m_pParentWnd)->ShowMsgDlg(
					this,
					"카피데이터",  
					ltoa(pRecord->m_nCompany, buffer, 10),
					ltoa(pRecord->m_nMNo, buffer, 10),
					ltoa(pRecord->m_nClientType, buffer, 10),
					pRecord->m_strCompanyName,
					pRecord->m_strName, 
					TRUE);

				g_bana_log->Print(m_pszRcpCopyData);
				pNewMsgDlg->SendMsg(m_pszRcpCopyData, TRUE);
				OnOK();
			}
			else if(pRecord->GetStatus() == MSG_STATUS_PROTECTED)
			{
				ShowNoteMsgDlg(pRecord->m_nCompany, pRecord->m_nMNo, pRecord->m_nClientType, 
							pRecord->m_strCompanyName, pRecord->m_strName);	
			}
			else
			{
				((CMkMessenger*)m_pParentWnd)->ShowMsgDlg(
					this, 
					"", 
					ltoa(pRecord->m_nCompany, buffer, 10),
					ltoa(pRecord->m_nMNo, buffer, 10),
					ltoa(pRecord->m_nClientType, buffer, 10),
					pRecord->m_strCompanyName,
					pRecord->m_strName);
			}
		}
	}
}

void CNewConnListDlg::SendMsgForGroupChating(long nCompany, long nMNo, CString strName, char *szMsg)
{
	char buffer[10];

	CNewMsgDlg *pNewMsgDlg = ((CMkMessenger*)m_pParentWnd)->ShowMsgDlg(
		this,
		"그룹채팅",  
		ltoa(nCompany, buffer, 10),
		ltoa(nMNo, buffer, 10),
		ltoa(0, buffer, 10),
		m_ci.m_strName,
		strName, 
		TRUE);

	g_bana_log->Print(szMsg);
	pNewMsgDlg->SendMsg(szMsg, TRUE);
}

void CNewConnListDlg::OnBnClickedPowerBtn()
{
	CREATE_MODALESS(CMsgPowerDlg, this);
	pDlg->m_pDB = m_pMsgDb;
	SHOW_MODALESS(CMsgPowerDlg, this);
}

void CNewConnListDlg::OnBnClickedSearchBtn()
{
	CString strKeyword;
	m_SearchEdit.GetWindowText(strKeyword);
	SearchUser(strKeyword);
}

void CNewConnListDlg::SearchUser(CString strKeyword)
{
	if(strKeyword.GetLength() < 2)
		return;

	MKLOCK(m_csList);

	for(int i = 0; i < m_wndReportCtrl.GetRecords()->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = m_wndReportCtrl.GetRecords()->GetAt(i);
		if(pRecord->HasChildren())
		{
			CXTPGridRecords *pChildRecords = pRecord->GetChilds();
			for(int k = 0; k < pChildRecords->GetCount(); k++)
			{
				CMessageRecord *pMsgRecord = (CMessageRecord*)pChildRecords->GetAt(k);
				if(pMsgRecord->m_strCompanyName.Find(strKeyword) >= 0 ||
					pMsgRecord->m_strBranchName.Find(strKeyword) >= 0 ||
					pMsgRecord->m_strName.Find(strKeyword) >= 0)
				{
					pRecord->SetExpanded(TRUE);
					m_wndReportCtrl.Populate();

					CXTPGridRows *pRows = m_wndReportCtrl.GetRows();
					for(int a = 0; a < pRows->GetCount(); a++)
					{
						CXTPGridRow *pRow = pRows->GetAt(a);
						if((CXTPGridRecord*)pMsgRecord == pRow->GetRecord())
						{
							m_wndReportCtrl.EnsureVisible(pRow);
							m_wndReportCtrl.GetSelectedRows()->Select(pRow);
							return;
						}
					}
				}
			}
		}
	}
}

BOOL CNewConnListDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{	
		if(pMsg->hwnd == m_SearchEdit.GetSafeHwnd()) 
		{
			OnBnClickedSearchBtn();
			return TRUE;
		}
/*
		if(pMsg->hwnd == m_edtSend.GetSafeHwnd()) 
		{
			OnBnClickedSendSearchMemberBtn();
			return TRUE;
		}
*/
	}

	return CXTResizeDialog::PreTranslateMessage(pMsg);
}

void CNewConnListDlg::OnBnClickedShowIntercallCheck()
{
	AfxGetApp()->WriteProfileInt("Messenger", "ShowIntercall", m_chkShowIntercall.GetCheck());
	RefreshConnList();
}

void CNewConnListDlg::OnBnClickedMyCompanyCheck()
{
	BOOL bEnable = m_chkMyCompany.GetCheck();

	AfxGetApp()->WriteProfileInt("Messenger", "MyCompany", m_chkMyCompany.GetCheck());

	m_edtBranch.EnableWindow(bEnable);
	m_btnOpenBranch.EnableWindow(bEnable);

	ReportFilter();
	RefreshReport();
}

void CNewConnListDlg::OnBnClickedRefreshHistoryBtn()
{
	RefreshHistory();
}

void CNewConnListDlg::OnCbnSelchangeShowTypeCombo()
{
	AfxGetApp()->WriteProfileInt("Messenger", "ShowType", m_cmbShowType.GetCurSel());
	RefreshHistory();
}

void CNewConnListDlg::OnEnChangeSearchHistoryEdit()
{
}

void CNewConnListDlg::RefreshHistory()
{
	m_lstHistory.GetRecords()->RemoveAll();

	CString strSearch;
	COleDateTime dtFrom, dtTo;
	m_dtpFrom.GetTime(dtFrom);
	m_dtpTo.GetTime(dtTo);
	m_edtSearchHistory.GetWindowText(strSearch);

	CMkRecordset pRs(m_pMsgDb);
	CMkCommand pCmd(m_pMsgDb, "select_msg_history");
	pCmd.AddParameter(m_nMyCompany);
	pCmd.AddParameter(m_nMyWNo);
	pCmd.AddParameter(m_cmbShowType.GetCurSel());
	pCmd.AddParameter(dtFrom);
	pCmd.AddParameter(dtTo);
	pCmd.AddParameter(strSearch);
	if(pRs.Execute(&pCmd)) 
	{
		long nItem = 0;
		while(!pRs.IsEOF()) 
		{
			COleDateTime dtLog;
			long nCompany, nMNo, nCompany2, nMNo2;
			CString strMsg, strCompany, strName, strCompany2, strName2;
			long nClientType, nClientType2;

			pRs.GetFieldValue("nCompany", nCompany);
			pRs.GetFieldValue("nMNo", nMNo);
			pRs.GetFieldValue("nCompany2", nCompany2);
			pRs.GetFieldValue("nMNo2", nMNo2);
			pRs.GetFieldValue("dtLog", dtLog);
			pRs.GetFieldValue("sMsg", strMsg);
			pRs.GetFieldValue("sCompany", strCompany);
			pRs.GetFieldValue("sName", strName);
			pRs.GetFieldValue("sCompany2", strCompany2);
			pRs.GetFieldValue("sName2", strName2);
			pRs.GetFieldValue("nClientType", nClientType);
			pRs.GetFieldValue("nClientType2", nClientType2);

			m_lstHistory.AddRecord(new CNewConnListRecord(dtLog, 
				nCompany, nMNo, strName, strCompany, 
				nCompany2, nMNo2, strName2, strCompany2, 
				strMsg, nClientType, nClientType2));

			pRs.MoveNext();
		}

		m_lstHistory.Populate();
	}
}

BOOL CNewConnListDlg::GetMsgDatabase()
{
	if(!m_pMsgDb)
	{
#ifdef _QUICK
		m_pMsgDb = m_pMkDb;
		return TRUE;
#else
		m_pMsgDb = new CMkDatabase(g_bana_log);

		BYTE nXorKey = (m_pMsgDb->GetXorKey() + 3) % 128;
		BYTE des_key_new[] = {29,44,2,83,32,98,10,8};
		BYTE nXoredKey[8];

		for(int i = 0; i < 8; i++)
			nXoredKey[i] = des_key_new[i] ^ ((nXorKey + i) % 128);
		m_pMsgDb->SetServerKey(nXoredKey);
		if(m_pMsgDb->Open(m_si.strMsgServerAddr, m_si.nMsgServerPort + 1))
			return TRUE;

		MessageBox("메신저 서버에 접속할 수 없습니다.\n재시도 바랍니다.", "확인", MB_ICONINFORMATION);
#endif
		return FALSE;
	}
	return TRUE;
}

#ifndef _SYSMANAGER
void CNewConnListDlg::RefreshAllStaffList()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_staff_list_for_messenger");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nMyCompany);

	if(pRs.Execute(&pCmd)) 
	{
		MKLOCK(m_csList);

		while(!pRs.IsEOF())
		{
			long nCompany, nMNo, nShareCode1;
			CString strName, strCompanyName, strBranchName;
			int nClientType = 0;
			COleDateTime dtLogin(2000, 1, 1, 1, 1, 1);

			pRs.GetFieldValue("nShareCode1", nShareCode1);
			pRs.GetFieldValue("lCode", nCompany);
			pRs.GetFieldValue("nMNo", nMNo);
			pRs.GetFieldValue("sName", strName);
			pRs.GetFieldValue("sCompanyName", strCompanyName);
			pRs.GetFieldValue("sBranchName", strBranchName);

			if(m_nMyCompany == nCompany && m_nMyWNo == nMNo)
			{
				pRs.MoveNext();
				continue;
			}

			UpdateUser(nShareCode1, nCompany, nMNo,
				strCompanyName, strBranchName, strName, 
				dtLogin, MSG_STATUS_PROTECTED, nClientType,
				m_bFirstRefresh && m_ci.IsChildCompany(nCompany), TRUE);

			pRs.MoveNext();
		}
	}
}
#endif


BOOL CNewConnListDlg::InsertNoteMsg(long nCompany, long nMNo, 
								CString strSend, CString strCompany, 
								CString strName)
{
	BOOL bRet = FALSE;
	CWaitCursor wait;
	CMkCommand pCmd(m_pMsgDb, "insert_messenger_msg2");
	pCmd.AddParameter(m_nMyCompany);
	pCmd.AddParameter(m_nMyWNo);
	pCmd.AddParameter(nCompany);
	pCmd.AddParameter(nMNo);
	pCmd.AddParameter(strSend);
	pCmd.AddParameter(TRUE);
	pCmd.AddParameter(m_strMyName);
	pCmd.AddParameter(strCompany);
	pCmd.AddParameter(strName);
	pCmd.AddParameter("");
	return pCmd.Execute();
}

CMsgNoteDlg* CNewConnListDlg::ShowNoteMsgDlg(long nCompany, long nMNo, long nClientType, 
						CString strCompanyName, CString strName,
						CString strTitle, CString strDescript, 
						CMsgNoteDlg *pMsgDlgInstance)
{
	CMsgNoteDlg *pMsgDlg;
	if(pMsgDlgInstance)
		pMsgDlg = pMsgDlgInstance;
	else 	
		pMsgDlg = new CMsgNoteDlg(this);

	pMsgDlg->m_nCompany = nCompany;
	pMsgDlg->m_nMNo = nMNo;
	pMsgDlg->m_nClientType = nClientType;
	pMsgDlg->m_strCompanyName = strCompanyName;
	pMsgDlg->m_strName = strName;
	
	if(pMsgDlg->GetMultiMemberCount() > 1)
		pMsgDlg->m_strTarget.Format("%d명 에게 동시전송함", pMsgDlg->GetMultiMemberCount());	
	else
		pMsgDlg->m_strTarget.Format("%s/%s 에게", strCompanyName, strName);

	if(strTitle.GetLength() > 0)
		pMsgDlg->m_strTitle = strTitle;
	
	if(strDescript.GetLength() > 0)
		pMsgDlg->m_strDescript = strDescript;
	
	pMsgDlg->m_pParent = this;
	pMsgDlg->Create(IDD_MSG_NOTE_DLG, this);
	pMsgDlg->ShowWindow(SW_SHOW);
	pMsgDlg->SetWindowPos(&CWnd::wndTopMost, 0,0,0,0, SWP_NOSIZE | SWP_NOMOVE);
	return pMsgDlg;
}

void CNewConnListDlg::ReportFilter()
{
	CString strSearch;
	BOOL bMyCompany = m_chkMyCompany.GetCheck();
	BOOL bOnlyOnline = m_chkShowOnlyOnline.GetCheck();
	BOOL bIntegrated = 0;

	MKLOCK(m_csList);

	m_SearchEdit.GetWindowText(strSearch);

	for(int i = 0; i < m_wndReportCtrl.GetRecords()->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = m_wndReportCtrl.GetRecords()->GetAt(i);
		if(pRecord->HasChildren())
		{
			CMessageTitleRecord *pTitleRecord = (CMessageTitleRecord*)pRecord;
			
			int nVisibleCount = 0;
			CXTPGridRecords *pChildRecords = pRecord->GetChilds();
			for(int k = 0; k < pChildRecords->GetCount(); k++)
			{
				CMessageRecord *pMsgRecord = (CMessageRecord*)pChildRecords->GetAt(k);
				pMsgRecord->SetVisible(TRUE);

				if(strSearch.GetLength() > 0)
				{
					if(pMsgRecord->m_strCompanyName.Find(strSearch) < 0 &&
						pMsgRecord->m_strName.Find(strSearch) < 0 &&
						pMsgRecord->m_strBranchName.Find(strSearch) < 0 &&
						pTitleRecord->m_strCompanyName.Find(strSearch) < 0)
					{
						pMsgRecord->SetVisible(FALSE);
						continue;
					}
				}

				if(bMyCompany)
				{
					if(!m_ci.IsChildCompany(pMsgRecord->m_nCompany))
					{
						pMsgRecord->SetVisible(FALSE);
						continue;
					}
/*
					if(!bIntegrated)
					{
						CString strCompanyCode;
						strCompanyCode.Format("%d,", pMsgRecord->m_nCompany);

						if(nVirtualCompany != pMsgRecord->m_nCompany &&
							strCodeList.Find(strCompanyCode) < 0)
						{
							pMsgRecord->SetVisible(FALSE);
						}
					}
*/
				}

				if(bOnlyOnline && pMsgRecord->GetStatus() != MSG_STATUS_NORMAL && 
						pMsgRecord->GetStatus() != MSG_STATUS_IDLE)
				{
					pMsgRecord->SetVisible(FALSE);
					continue;					
				}

				if(pMsgRecord->IsVisible())
					nVisibleCount++;
			}

			pTitleRecord->SetVisible(nVisibleCount > 0);
		}
	}
}
void CNewConnListDlg::OnEnChangeSearchEdit()
{
	ReportFilter();
	RefreshReport();
}

void CNewConnListDlg::OnBnClickedSendMsgBtn()
{
	CSelectMsgSendTypeDlg dlg;
	dlg.m_strTitle = "실시간 메시지 전송(접속자만)";
	if(dlg.DoModal() == IDOK)
	{
		if(dlg.m_nSelectedType >= 0)
		{
			SendBulkMsg(TRUE, dlg.m_nSelectedType);
		}
	}
}

void CNewConnListDlg::OnBnClickedSendNoteMsgBtn()
{
	CSelectMsgSendTypeDlg dlg;
	dlg.m_strTitle = "쪽지 전송(오프라인은 로그인시 알림, 몇초 지연확인됨)";
	if(dlg.DoModal() == IDOK)
	{
		if(dlg.m_nSelectedType >= 0)
		{
			MKLOCK(m_csList);
			SendBulkMsg(FALSE, dlg.m_nSelectedType);
		}
	}
}

void CNewConnListDlg::SendBulkMsg(BOOL bInstanceMsg, int nSendType)
{
	if(nSendType == BULK_SEND_LIST)
	{
		CMsgNoteDlg *pDlg = new CMsgNoteDlg;
		pDlg->m_bInstanceMsg = bInstanceMsg;

		try
		{
			{
				MKLOCK(m_csList);

				for(int i = 0; i < m_wndReportCtrl.GetRows()->GetCount(); i++)
				{
					CXTPGridRow *pRow = m_wndReportCtrl.GetRows()->GetAt(i);
					if(pRow->HasChildren())
					{
						CXTPGridRows *pChildRows = pRow->GetChilds();
						for(int k = 0; k < pChildRows->GetCount(); k++)
						{
							CXTPGridRow *pChildRow = pChildRows->GetAt(k);
							if(pChildRow->IsItemsVisible())
							{
								CMessageRecord *pMsgRecord = (CMessageRecord*)pChildRow->GetRecord();

								if(!bInstanceMsg || (bInstanceMsg && pMsgRecord->GetStatus() == MSG_STATUS_NORMAL))
								{
									if(!m_ci.IsChildCompany(pMsgRecord->m_nCompany))
										throw "동시 전송시 타회사 멤버는 포함시킬 수 없습니다.";

									pDlg->AddMultiMember(pMsgRecord->m_nCompany, pMsgRecord->m_nMNo,
												pMsgRecord->m_strBranchName, pMsgRecord->m_strName);
								}
							}
						}
					}
				}
			}

			if(bInstanceMsg)
			{
				if(pDlg->GetMultiMemberCount() == 0)
					throw "전송 대상이 존재하지 않거나, 오프라인 상태입니다.";
				else if(pDlg->GetMultiMemberCount() == 1)
					throw "전송대상이 1명인 경우에(오프라인 제외), 해당멤버를 더블클릭하셔서 전송하시기 바랍니다.";
			}
			else
			{
				if(pDlg->GetMultiMemberCount() == 0)
					throw "전송 대상이 존재하지 않습니다.";
				else if(pDlg->GetMultiMemberCount() == 1)
					throw "전송대상이 1명인 경우에, 해당멤버를 더블클릭하셔서 전송하시기 바랍니다.";
			}
		}
		catch(char *szMsg)
		{
			MessageBox(szMsg, "확인", MB_ICONINFORMATION);
			delete pDlg;
			return;
		}

		ShowNoteMsgDlg(0, 0, 0, m_strMyBranchName, m_strMyName, 
					bInstanceMsg ? "실시간 메시지 전송" : "", "", pDlg);
	}
	else if(nSendType == BULK_SEND_SELECTED)
	{
		CMsgNoteDlg *pDlg = new CMsgNoteDlg;
		pDlg->m_bInstanceMsg = bInstanceMsg;

		try
		{
			{
				MKLOCK(m_csList);

				for(int i = 0; i < m_wndReportCtrl.GetSelectedRows()->GetCount(); i++)
				{
					CXTPGridRow *pRow = m_wndReportCtrl.GetSelectedRows()->GetAt(i);
					if(!pRow->HasChildren() && pRow->IsItemsVisible())
					{
						CMessageRecord *pMsgRecord = (CMessageRecord*)pRow->GetRecord();
						
						if(!bInstanceMsg || (bInstanceMsg && pMsgRecord->GetStatus() == MSG_STATUS_NORMAL))
						{
							if(!m_ci.IsChildCompany(pMsgRecord->m_nCompany))
								throw "동시 전송시 타회사 멤버는 포함시킬 수 없습니다.";

							pDlg->AddMultiMember(pMsgRecord->m_nCompany, pMsgRecord->m_nMNo,
									pMsgRecord->m_strBranchName, pMsgRecord->m_strName);
						}
					}
				}
			}

	
			if(bInstanceMsg)
			{
				if(pDlg->GetMultiMemberCount() == 0)
					throw "전송 대상이 존재하지 않거나, 오프라인 상태입니다.";
				else if(pDlg->GetMultiMemberCount() == 1)
					throw "전송대상이 1명인 경우에(오프라인 제외), 해당멤버를 더블클릭하셔서 전송하시기 바랍니다.";
			}
			else
			{
				if(pDlg->GetMultiMemberCount() == 0)
					throw "전송 대상이 존재하지 않습니다.";
				else if(pDlg->GetMultiMemberCount() == 1)
					throw "전송대상이 1명인 경우에, 해당멤버를 더블클릭하셔서 전송하시기 바랍니다.";
			}
		}
		catch(char *szMsg)
		{
			MessageBox(szMsg, "확인", MB_ICONINFORMATION);
			delete pDlg;
			return;
		}

		ShowNoteMsgDlg(0, 0, 0, m_strMyBranchName, m_strMyName, 
						bInstanceMsg ? "실시간 메시지 전송" : "", "", pDlg);
	}
	else if(nSendType == BULK_SEND_SHARECODE ||
			nSendType == BULK_SEND_COMPANY)
	{
		if(bInstanceMsg)
		{
			char buffer[20];
			((CMkMessenger*)m_pParentWnd)->ShowMsgDlg(this,
				"", 
				ltoa(m_nMyShareCode1, buffer, 10), 
				ltoa(m_nMyWNo, buffer, 10), "0",
				m_strMyBranchName,
				m_strMyName,
				FALSE,
				(nSendType == BULK_SEND_SHARECODE) ? TYPE_SHARECODE : TYPE_COMPANY);
		}
		else
		{
			CMsgNoteDlg *pDlg = new CMsgNoteDlg;

			try
			{
				{
					MKLOCK(m_csList);
					for(int i = 0; i < m_wndReportCtrl.GetRecords()->GetCount(); i++)
					{
						CXTPGridRecord *pRecord = m_wndReportCtrl.GetRecords()->GetAt(i);
						if(pRecord->HasChildren())
						{
							CXTPGridRecords *pChildRecords = pRecord->GetChilds();
							for(int k = 0; k < pChildRecords->GetCount(); k++)
							{
								CMessageRecord *pMsgRecord = (CMessageRecord*)pChildRecords->GetAt(k);

								if(nSendType == BULK_SEND_SHARECODE)
								{
									if(m_ci.IsChildCompany(pMsgRecord->m_nCompany))
										pDlg->AddMultiMember(pMsgRecord->m_nCompany, pMsgRecord->m_nMNo,
												pMsgRecord->m_strBranchName, pMsgRecord->m_strName);
								}
								else
								{
									if(m_nMyCompany == pMsgRecord->m_nCompany)
										pDlg->AddMultiMember(pMsgRecord->m_nCompany, pMsgRecord->m_nMNo,
												pMsgRecord->m_strBranchName, pMsgRecord->m_strName);
								}
							}
						}
					}
				}

				if(pDlg->GetMultiMemberCount() == 0)
					throw "전송 대상이 존재하지 않습니다.";
			}
			catch(char *szMsg)
			{
				MessageBox(szMsg, "확인", MB_ICONINFORMATION);
				delete pDlg;
				return;
			}

			ShowNoteMsgDlg(0, 0, 0, m_strMyBranchName, m_strMyName, "", "", pDlg);
		}
	}
}

void CNewConnListDlg::OnCbnSelchangeMainCombo()
{
	ReportFilter();
	RefreshReport();
}

void CNewConnListDlg::OnBnClickedSendSelectBtn()
{
	try
	{
		MKLOCK(m_csList);
		CString strSend;
		m_edtSend.GetWindowText(strSend);	
		if(strSend.GetLength() == 0)
			throw "보내실 내용을 입력하신 후에, 전송하여 주시기 바랍니다.";

		for(int i = 0; i < m_wndReportCtrl.GetSelectedRows()->GetCount(); i++)
		{
			CXTPGridRow *pRow = m_wndReportCtrl.GetSelectedRows()->GetAt(i);
			if(!pRow->HasChildren() && pRow->IsItemsVisible())
			{
				CMessageRecord *pMsgRecord = (CMessageRecord*)pRow->GetRecord();

				if(!m_ci.IsChildCompany(pMsgRecord->m_nCompany))
					throw "동시 전송시 타회사 멤버는 포함시킬 수 없습니다.";

				if(!InsertNoteMsg(pMsgRecord->m_nCompany, pMsgRecord->m_nMNo, strSend,
					pMsgRecord->m_strBranchName, pMsgRecord->m_strName))
					throw "쪽지 전송이 일부 실패되었습니다.\n재시도 하시기 바랍니다.";				
			}
		}

		m_btnDate.OnMenuWeekIncludeToday();
	}
	catch(char *szMsg)
	{
		MessageBox(szMsg, "확인", MB_ICONINFORMATION);
	}

	RefreshHistory();
}

void CNewConnListDlg::OnBnClickedSendSearchBtn()
{
	try
	{
		MKLOCK(m_csList);
		CString strSend;
		m_edtSend.GetWindowText(strSend);	
		if(strSend.GetLength() == 0)
			throw "보내실 내용을 입력하신 후에, 전송하여 주시기 바랍니다.";

		for(int i = 0; i < m_wndReportCtrl.GetRows()->GetCount(); i++)
		{
			CXTPGridRow *pRow = m_wndReportCtrl.GetRows()->GetAt(i);
			if(pRow->HasChildren())
			{
				CXTPGridRows *pChildRows = pRow->GetChilds();
				for(int k = 0; k < pChildRows->GetCount(); k++)
				{
					CXTPGridRow *pChildRow = pChildRows->GetAt(k);
					if(pChildRow->IsItemsVisible())
					{
						CMessageRecord *pMsgRecord = (CMessageRecord*)pChildRow->GetRecord();

						if(!m_ci.IsChildCompany(pMsgRecord->m_nCompany))
							throw "동시 전송시 타회사 멤버는 포함시킬 수 없습니다.";

						if(!InsertNoteMsg(pMsgRecord->m_nCompany, pMsgRecord->m_nMNo, strSend,
							pMsgRecord->m_strBranchName, pMsgRecord->m_strName))
							throw "쪽지 전송이 일부 실패되었습니다.\n재시도 하시기 바랍니다.";				
						
					}
				}
			}
		}

		m_btnDate.OnMenuWeekIncludeToday();
	}
	catch(char *szMsg)
	{
		MessageBox(szMsg, "확인", MB_ICONINFORMATION);
	}

	RefreshHistory();
}


void CNewConnListDlg::OnBnClickedShowOnlyOnlineCheck()
{
	AfxGetApp()->WriteProfileInt("Messenger", "OnlyOnline", m_chkShowOnlyOnline.GetCheck());
	RefreshConnList();
}


void CNewConnListDlg::OnReportItemHistoryClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify =
		(XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if(pItemNotify->pRow && pItemNotify->pColumn)
	{
		CNewConnListRecord *pMessageRecord = ((CNewConnListRecord*)pItemNotify->pRow->GetRecord());
		if(pMessageRecord)
			RefreshHistoryRich(pMessageRecord->m_nTCompany, pMessageRecord->m_nTWNo, pMessageRecord->m_nTClientType);
	}
}

void CNewConnListDlg::OnReportItemHistoryDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify =
		(XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if(pItemNotify->pRow && pItemNotify->pColumn)
	{
		if(pItemNotify->pColumn->GetIndex() <= 2)
		{
			CNewConnListRecord *pMessageRecord = ((CNewConnListRecord*)pItemNotify->pRow->GetRecord());
			if(pMessageRecord)
				FindAfterShowMsgDlg(pMessageRecord->m_nTCompany, pMessageRecord->m_nTWNo);
		}
		else
		{
			CXTPGridColumn *pCol = NULL;
			m_edtSend.SetWindowText(pItemNotify->pRow->GetRecord()->GetItem(3)->GetCaption(pCol));
		}
	}
}

UINT CNewConnListDlg::RefreshProc(LPVOID lParam)
{
	m_hExitHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hThreadDiedHandle = CreateEvent(NULL, FALSE, FALSE, NULL);

	RefreshConnList(TRUE);
	RefreshHistory();

	while(1)
	{	
		DWORD dwWaitResult = WaitForSingleObject(m_hExitHandle, 5000);

		if(dwWaitResult == WAIT_OBJECT_0)
			break;

		if(this->IsWindowVisible())
			RefreshConnList(TRUE);
	}

	SetEvent(m_hThreadDiedHandle);
	return 0;
}

void CNewConnListDlg::FindAfterShowMsgDlg(long nCompany, long nMNo, CString strMsg)
{
	MKLOCK(m_csList);
	for(int i=0; i<m_wndReportCtrl.GetRecords()->GetCount();i++)	
	{
		CXTPGridRecord *pRecord = m_wndReportCtrl.GetRecords()->GetAt(i);

		if(pRecord->HasChildren())
		{
			CXTPGridRecords *pChildRecords = pRecord->GetChilds();
			for(int k = 0; k < pChildRecords->GetCount(); k++)
			{
				CMessageRecord *pMsgRecord = (CMessageRecord*)pChildRecords->GetAt(k);

				if(nCompany == pMsgRecord->m_nCompany && nMNo == pMsgRecord->m_nMNo)
				{
					MKLOCK_RELEASE();

					char buffer[20];

					CNewMsgDlg *pNewMsgDlg = ((CMkMessenger*)m_pParentWnd)->ShowMsgDlg(
						this,
						"",  
						ltoa(pMsgRecord->m_nCompany, buffer, 10),
						ltoa(pMsgRecord->m_nMNo, buffer, 10),
						ltoa(pMsgRecord->m_nClientType, buffer, 10),
						pMsgRecord->m_strCompanyName,
						pMsgRecord->m_strName);

					if(strMsg.GetLength() > 0)
						pNewMsgDlg->SendMsg(strMsg);
					return;
				}
			}
		}
	}

	MessageBox("상대방이 오프라인 상태이므로, 대화창를 시작 할 수 없습니다.", "확인", 
				MB_ICONINFORMATION);
}

void CNewConnListDlg::RefreshHistoryRich(long nCompany, long nMNo, long nClientType)
{
	static int nLastCompany = 0, nLastMNo = 0, nLastClientType = 0;

	if(m_nMyCompany == nCompany && m_nMyWNo == nMNo && nClientType == 0)
	{
		m_edtHistoryRich.SetWindowText("");
		return;
	}

	if(nLastCompany == nCompany && nLastMNo == nMNo && nLastClientType == nClientType)
		return;

	nLastCompany = nCompany;
	nLastMNo = nMNo;
	nLastClientType = nClientType;

	m_edtHistoryRich.SetWindowText("");

	long nCount = 0;
	CString strName;
	COleDateTime dtLast;
	dtLast.SetStatus(COleDateTime::null);
	int n = 0;
	for(n = 0; n < m_lstHistory.GetRows()->GetCount(); n++)
	{
		CNewConnListRecord *pRecord = (CNewConnListRecord*)m_lstHistory.GetRows()->GetAt(n)->GetRecord();
		if(nCompany == pRecord->m_nTCompany &&
			nMNo == pRecord->m_nTWNo &&
			nClientType == pRecord->m_nTClientType)
		{
			if(++nCount > 30)
				break;
		}
	}

	for(int i = n - 1; i >= 0; i--)
	{
		CNewConnListRecord *pRecord = (CNewConnListRecord*)m_lstHistory.GetRows()->GetAt(i)->GetRecord();
		if(nCompany == pRecord->m_nTCompany &&
			nMNo == pRecord->m_nTWNo &&
			nClientType == pRecord->m_nTClientType)
		{
			if(dtLast.GetStatus() != COleDateTime::null)
			{
				COleDateTimeSpan dtSpan = pRecord->m_dtLog - dtLast;
				if(dtSpan.GetTotalMinutes() >= 5)
					m_edtHistoryRich.AddMsg(CString("\r\n-----새로운 대화 시작-----\r\n"), RGB(180, 180, 30), 0 , 1);
			}
			
			dtLast = pRecord->m_dtLog;

			if(pRecord->m_nType == 0)
			{
				strName.Format("%s: [%s]\r\n", m_strMyName, pRecord->m_dtLog.Format("%m-%d %H:%M:%S"));
				m_edtHistoryRich.AddName(strName, RGB(130, 130, 130));
				m_edtHistoryRich.AddText(pRecord->m_strMsg + "\r\n", RGB(0, 0, 255));		
			}
			else
			{
				strName.Format("%s 님의 말: [%s]\r\n", pRecord->m_strTName, pRecord->m_dtLog.Format("%m-%d %H:%M:%S"));
				m_edtHistoryRich.AddName(strName, RGB(130, 130, 130));
				m_edtHistoryRich.AddText(pRecord->m_strMsg + "\r\n", RGB(128, 0, 128));
			}
		}
	}
 
	m_edtHistoryRich.AddMsg(CString("-- 이전 대화 내역입니다. (최대 30건만 표시함) --"), RGB(180, 180, 30), 0 , 1);
}

void CNewConnListDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyResizeDialog::OnSize(nType, cx, cy);

	if(m_lstHistory.GetSafeHwnd())
	{
		CRect rcList;
		m_lstHistory.GetClientRect(rcList);

		CXTPGridColumn *pCol3 = m_lstHistory.GetColumns()->GetAt(3);
		int nHeaderWidth = m_lstHistory.GetReportHeader()->GetWidth();
		int nColWidth = pCol3->GetWidth();
		pCol3->SetWidth(max(155, (nColWidth + rcList.Width() - nHeaderWidth)) - 1);
	}
}

void CNewConnListDlg::RefreshReport() 
{ 
	MKLOCK(m_csList);
	m_wndReportCtrl.Populate(); 
}
