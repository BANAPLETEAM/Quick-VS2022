// RecvCidDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RecvCidDlg.h"
#include "RcpView.h"

// CRecvCidDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRecvCidDlg, CMyDialog)
CRecvCidDlg::CRecvCidDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRecvCidDlg::IDD, pParent)
{
	m_pParentWnd = pParent;
	InitializeCriticalSection(&m_csListLock);
}

CRecvCidDlg::~CRecvCidDlg()
{
}

void CRecvCidDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(CRecvCidDlg, CMyDialog)
	ON_WM_CLOSE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnLvnItemchangedList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CRecvCidDlg 메시지 처리기입니다.

BOOL CRecvCidDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	
	CImageList m_ImageList; 
	m_ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&m_ImageList,LVSIL_SMALL); 
	
	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
				LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);

	m_List.InsertColumn(1,"시각",LVCFMT_LEFT,100);
	m_List.InsertColumn(2,"전화번호",LVCFMT_LEFT,100);
	m_List.InsertColumn(3,"지사",LVCFMT_CENTER, 0);
	m_List.InsertColumn(4,"채널",LVCFMT_CENTER, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRecvCidDlg::OnClose()
{
	m_pParentWnd->PostMessage(WM_CLOSE_RECV_CID_DLG, 0, 0);
	CMyDialog::OnClose();
}

void CRecvCidDlg::OnOK()
{
	m_pParentWnd->PostMessage(WM_CLOSE_RECV_CID_DLG, 0, 0);
	CMyDialog::OnOK();
}

void CRecvCidDlg::OnCancel()
{
	m_pParentWnd->PostMessage(WM_CLOSE_RECV_CID_DLG, 0, 0);
	CMyDialog::OnCancel();
}

void CRecvCidDlg::AddRecvCid(CString strPhone, DWORD dwData)
{
	char buffer[10];

	ST_CID_INFO *pCIDInfo = (ST_CID_INFO*)dwData;

	EnterCriticalSection(&m_csListLock);
	if(pCIDInfo->nGroupID == -100)
	{
	}
	else
	{
		if(strPhone != "PRIVATE")
		{
			int nItem = m_List.GetItemCount();
			COleDateTime dt = COleDateTime::GetCurrentTime();
			m_List.InsertItem(nItem, dt.Format("%m-%d %H:%M:%S"));
			m_List.SetItemText(nItem, 1, LF->GetDashPhoneNumber(pCIDInfo->strPhone));
			m_List.SetItemText(nItem, 2, ltoa(pCIDInfo->nGroupID, buffer, 10));
			m_List.SetItemText(nItem, 3, pCIDInfo->strChannel);
			m_List.SetItemData(nItem, (DWORD)pCIDInfo);
		}
		else 
		{
			pCIDInfo->strPhone = "";
			int nItem = m_List.GetItemCount();
			COleDateTime dt = COleDateTime::GetCurrentTime();
			m_List.InsertItem(nItem, dt.Format("%m-%d %H:%M:%S"));
			m_List.SetItemText(nItem, 1, "");
			m_List.SetItemText(nItem, 2, ltoa(pCIDInfo->nGroupID, buffer, 10));
			m_List.SetItemText(nItem, 3, pCIDInfo->strChannel);
			m_List.SetItemData(nItem, (DWORD)pCIDInfo);		
		}
	}
	LeaveCriticalSection(&m_csListLock);
}


void CRecvCidDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

void CRecvCidDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	EnterCriticalSection(&m_csListLock);

	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {

		ST_CID_INFO *pCIDInfo = (ST_CID_INFO*)m_List.GetItemData(nItem);
		CWnd *pWnd = (CWnd*)LU->m_pRcpView;

		if(pWnd != NULL)
		{
			WINDOWPLACEMENT wndpl;
			wndpl.length = sizeof(WINDOWPLACEMENT);
			GetWindowPlacement(&wndpl);

			if(wndpl.showCmd == SW_SHOWMINIMIZED)
				ShowWindow(SW_RESTORE);

			SetForegroundWindow();
			SetFocus();

			int nGroup = atol(m_List.GetItemText(nItem, 2));
			pWnd->PostMessage(WM_RECV_CID, (WPARAM)pCIDInfo, 0);				
		}
		else
		{
			delete pCIDInfo;
		}

		char data[255] = {0,};
		STRCPY(data, "D",VL_END); 
		STRCAT(data, (LPSTR)(LPCTSTR) LF->GetDashPhoneNumber( m_List.GetItemText(nItem, 1) ),VL_END); //번호
		STRCAT(data, (LPSTR)(LPCTSTR) m_List.GetItemText(nItem, 2),VL_END); //채널
		LU->SendCopyDataToTelClient(data);

		m_List.DeleteItem(nItem);
	}
	*pResult = 0;
	LeaveCriticalSection(&m_csListLock);
	/*
	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {
		CString *strNumber = new CString;
		
		if(m_List.GetItemData(nItem))
		{
			*strNumber = m_List.GetItemText(nItem, 1);
		}
		else {
			*strNumber = "";
		}

		CString strLog, strDashNumber;
		
		CWnd *pWnd = (CWnd*)((CMainFrame*)AfxGetMainWnd())->m_pRcpView;

		if(pWnd != NULL)
		{
			WINDOWPLACEMENT wndpl;
			wndpl.length = sizeof(WINDOWPLACEMENT);
			GetWindowPlacement(&wndpl);

			if(wndpl.showCmd == SW_SHOWMINIMIZED)
				ShowWindow(SW_RESTORE);

			SetForegroundWindow();
			SetFocus();

			int nGroup = atol(m_List.GetItemText(nItem, 2));
			if(nGroup > 0)
				pWnd->PostMessage(WM_RECV_CID, (WPARAM)strNumber, (LPARAM)nGroup);				
			else 
				pWnd->PostMessage(WM_RECV_CID, (WPARAM)strNumber, 0);				
		}
		else
			delete strNumber;

		m_List.DeleteItem(nItem);
	}
	*pResult = 0;
	*/
}

void CRecvCidDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}

void CRecvCidDlg::RemoveRecvCid(CString strPhone, CString strGroup, CString strChannel)
{
	EnterCriticalSection(&m_csListLock);
	int nItem = 0;

	strPhone = LF->GetDashPhoneNumber(strPhone);
	int nItemCount =  m_List.GetItemCount();


	for(int nItem = 0;nItem < nItemCount ;nItem++)
	{
		if( strPhone == m_List.GetItemText(nItem, 1) )
		{
			ST_CID_INFO *pCIDInfo = (ST_CID_INFO*)m_List.GetItemData(nItem);
			if(pCIDInfo)
				delete pCIDInfo;

			m_List.DeleteItem(nItem);
		}
		else
		{
			nItem++;
		}
	}
	LeaveCriticalSection(&m_csListLock);
}