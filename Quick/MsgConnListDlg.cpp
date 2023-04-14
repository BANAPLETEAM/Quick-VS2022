// MsgConnListDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MsgConnListDlg.h"

#include "NewMsgDlg.h"
#include "MkMessenger.h"



// CMsgConnListDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMsgConnListDlg, CMyDialog)
CMsgConnListDlg::CMsgConnListDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMsgConnListDlg::IDD, pParent)
{
	m_pParentWnd = pParent;
	m_pSocket = NULL;
	m_nConnListType = NULL;
}

CMsgConnListDlg::~CMsgConnListDlg()
{
	SetEvent(m_hKillEvent);
}

void CMsgConnListDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_REFRESH_CHECK, m_RefreshCheck);
}


BEGIN_MESSAGE_MAP(CMsgConnListDlg, CMyDialog)
//	ON_BN_CLICKED(IDC_COMM_BTN, OnBnClickedCommBtn)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnLvnItemchangedList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnNMClickList1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMsgConnListDlg 메시지 처리기입니다.

BOOL CMsgConnListDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );

	m_List.SetImageList(&ImageList,LVSIL_SMALL); 
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_List.InsertColumn(0,"소속", LVCFMT_CENTER, 100);
	m_List.InsertColumn(1,"No.", LVCFMT_LEFT, 80);
	m_List.InsertColumn(2,"성명", LVCFMT_LEFT, 100);

	CenterWindow(GetDesktopWindow());
	SetTimer(0, 5000, NULL);
	m_RefreshCheck.SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMsgConnListDlg::OnBnClickedCommBtn()
{
}

void CMsgConnListDlg::RefreshConnList()
{
	if(m_pSocket)
	{
		if(m_pSocket->IsConnected()) 
		{
			if(m_nConnListType == 1)
				m_pSocket->SendCommand(PT_REQUEST, PST_MSG_CONN_LIST2);
			else
				m_pSocket->SendCommand(PT_REQUEST, PST_MSG_CONN_LIST);
		}
	}
}

void CMsgConnListDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
}

void CMsgConnListDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	char buffer[20];

	if(nItem >= 0)
	{
		((CMkMessenger*)m_pParentWnd)->ShowMsgDlg("", 
				ltoa((long)m_List.GetItemData(nItem), buffer, 10),
				"",
				m_List.GetItemText(nItem, 1),
				m_List.GetItemText(nItem, 0),
				m_List.GetItemText(nItem, 2));
	}
	*pResult = 0;
}

void CMsgConnListDlg::OnClose()
{
	m_pParentWnd->PostMessage(WM_CLOSE_MSG_CONN_LIST_DLG, 0, 0);
	CMyDialog::OnClose();
}

void CMsgConnListDlg::OnBnClickedCancel()
{
	m_pParentWnd->PostMessage(WM_CLOSE_MSG_CONN_LIST_DLG, 0, 0);
	OnCancel();
}

//소켓 쓰레드
UINT CMsgConnListDlg::RefreshProc(LPVOID lParam)
{

/*	while(1)
	{
		DWORD nRet = WaitForSingleObject(m_hKillEvent, 5000);
		if(nRet == WAIT_OBJECT_0)
			break;

		CMainFrame *pFrame = (CMainFrame*)lParam;
		if(pFrame->GetSafeHwnd())
		{
			if(pFrame->m_pMsgClient->GetSafeHwnd())
			{
				CQSocket *pSocket = pFrame->m_pMsgClient->GetSocket();
				if(pSocket)
				{
					if(pSocket->IsConnected()) 
					    pSocket->SendCommand(PT_REQUEST, PST_MSG_CONN_LIST);
				}
			}
		}
	}
*/
	return 0;
}
void CMsgConnListDlg::OnTimer(UINT nIDEvent)
{
	KillTimer(0);

	if(m_RefreshCheck.GetCheck())
		RefreshConnList();

	SetTimer(0, 5000, NULL);
	CMyDialog::OnTimer(nIDEvent);
}
