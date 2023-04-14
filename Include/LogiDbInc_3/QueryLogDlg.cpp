// QueryLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "QueryLogDlg.h"
#include "MkCommand.h"

// CQueryLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CQueryLogDlg, CMyDialog)

CQueryLogDlg::CQueryLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CQueryLogDlg::IDD, pParent)
{

}

CQueryLogDlg::~CQueryLogDlg()
{
}

void CQueryLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstQuery);
}


BEGIN_MESSAGE_MAP(CQueryLogDlg, CMyDialog)
	ON_BN_CLICKED(IDC_COPY_CLIP_BTN, &CQueryLogDlg::OnBnClickedCopyClipBtn)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CQueryLogDlg::OnBnClickedRefreshBtn)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CQueryLogDlg 메시지 처리기입니다.

BOOL CQueryLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CImageList ImgList; 
	ImgList.Create(1,17,ILC_COLOR,1,1); 
	m_lstQuery.SetImageList(&ImgList, LVSIL_SMALL); 
	m_lstQuery.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_lstQuery.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	CRect rc;
	m_lstQuery.GetClientRect(rc);
	m_lstQuery.InsertColumn(0,"",LVCFMT_LEFT, rc.Width() - 20);
	m_lstQuery.ShowHeader(FALSE);
	m_lstQuery.Populate();

	RefreshList();

	//SetResize(IDC_LIST1, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_BOTTOMRIGHT);

	return TRUE;
}

void CQueryLogDlg::RefreshList()
{
	m_lstQuery.DeleteAllItems();
	for(int i = 0; i < CMkCommand::m_saExecute.GetCount(); i++)
		m_lstQuery.InsertItem(0, CMkCommand::m_saExecute.GetAt(i));

	m_lstQuery.Populate();
}

void CQueryLogDlg::AddQuery(CString strQuery)
{
	m_strQuery = strQuery;
	SetTimer(0, 1, NULL);
}

void CQueryLogDlg::OnBnClickedCopyClipBtn()
{
	int index = m_lstQuery.GetNextItem(-1,LVNI_SELECTED);
	if(index >= 0)
	{
		CString strQuery = m_lstQuery.GetItemText(index, 0);
		if(::OpenClipboard(GetSafeHwnd()))
		{
			HGLOBAL clipbuffer;
			char *buffer;
			::EmptyClipboard();
			clipbuffer = GlobalAlloc(GMEM_DDESHARE, strQuery.GetLength()+1);
			buffer = (char*)GlobalLock(clipbuffer);
			strcpy(buffer, LPCSTR(strQuery));
			GlobalUnlock(clipbuffer);
			::SetClipboardData(CF_TEXT,clipbuffer); 
			::CloseClipboard(); 
		}
	}
}

void CQueryLogDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CQueryLogDlg::OnTimer(UINT_PTR nIDEvent)
{
	m_lstQuery.InsertItem(0, m_strQuery);
	m_lstQuery.Populate();
	KillTimer(nIDEvent);

	CMyDialog::OnTimer(nIDEvent);
}