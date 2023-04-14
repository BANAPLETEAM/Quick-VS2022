// GroupChatDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "GroupChatDlg.h"
#include "MyMkMessenger.h"
#include "NewConnListDlg.h"

// CGroupChatDlg

IMPLEMENT_DYNCREATE(CGroupChatDlg, CMyFormView)

CGroupChatDlg::CGroupChatDlg()
	: CMyFormView(CGroupChatDlg::IDD)
{
	m_dwLastSend = GetTickCount();
}

CGroupChatDlg::~CGroupChatDlg()
{
}

void CGroupChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_EDIT, m_edtText);
	DDX_Control(pDX, IDC_MENT_EDIT, m_edtMent);
	DDX_Control(pDX, IDC_SEND_BUTTON, m_btnSend);
	DDX_Control(pDX, IDC_CLEAR_BUTTON, m_btnClear);
}

BEGIN_MESSAGE_MAP(CGroupChatDlg, CMyFormView)
	ON_BN_CLICKED(IDC_SEND_BUTTON, &CGroupChatDlg::OnBnClickedSendButton)
	ON_BN_CLICKED(IDC_CLEAR_BUTTON, &CGroupChatDlg::OnBnClickedClearButton)	
	ON_WM_SIZE()
END_MESSAGE_MAP()



void CGroupChatDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyFormView::OnSize(nType, cx, cy);

	if(m_edtText.GetSafeHwnd())
	{
		CRect rcText, rcMent, rcClear, rcSend;

		m_edtText.GetWindowRect(rcText); ScreenToClient(rcText);
		m_edtMent.GetWindowRect(rcMent); ScreenToClient(rcMent);
		m_btnClear.GetWindowRect(rcClear); ScreenToClient(rcClear);
		m_btnSend.GetWindowRect(rcSend); ScreenToClient(rcSend);

		long nHeight = rcSend.Height();

		rcClear.bottom = cy - 2;
		rcClear.top = rcClear.bottom - nHeight;

		rcSend.bottom = rcClear.top - 2;
		rcSend.top = rcSend.bottom - nHeight;

		rcMent.top = rcSend.top;
		rcMent.bottom = rcClear.bottom;

		rcText.bottom = rcMent.top - 2; 

		m_edtText.MoveWindow(rcText);
		m_edtMent.MoveWindow(rcMent);
		m_btnClear.MoveWindow(rcClear);
		m_btnSend.MoveWindow(rcSend);	
	}
}
// CGroupChatDlg 진단입니다.

#ifdef _DEBUG
void CGroupChatDlg::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CGroupChatDlg::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGroupChatDlg 메시지 처리기입니다.

void CGroupChatDlg::OnBnClickedClearButton()
{
	m_edtText.SetWindowText("");
}

void CGroupChatDlg::OnBnClickedSendButton()
{
	DWORD dw = GetTickCount();

	if(dw - m_dwLastSend < 2000)
		return;

	CString strText;
	m_edtMent.GetWindowText(strText);

	BOOL bSend = FALSE;

	if(strText.GetLength() > 0)
	{
		CMkRecordset rs(m_pMkDb);
		CMkCommand cmd(m_pMkDb, "select_msg_list_for_group_chatting");
		cmd.AddParameter(m_ci.m_nShareCode1);

		if(!rs.Execute(&cmd))  
			return;

		long nCompany, nMNo;
		CString strName;

		char szChar[1024];
		szChar[0] = 0;
		STRCAT2("^&", szChar, "$$%GROUP_CHAT", strText, VL_END);

		CNewConnListDlg dlg(LU->m_pMsg);
		if(dlg.GetMsgDatabase())
		{
			for(int i=0;i<rs.GetRecordCount(); i++)
			{
				rs.GetFieldValue("nCompany", nCompany);
				rs.GetFieldValue("nMNo", nMNo);
				rs.GetFieldValue("sName", strName);

				dlg.SendMsgForGroupChating(nCompany, nMNo, strName, szChar);
				bSend = TRUE;
				rs.MoveNext();
			}
		}
	}

	m_dwLastSend = GetTickCount();

	if(bSend)
	{
		CMkCommand cmd(m_pMkDb, "insert_group_chat_log");
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ui.strName);
		cmd.AddParameter(m_ci.m_nShareCode1);
		cmd.AddParameter(strText);
		cmd.Execute();

		m_edtMent.SetWindowText("");
	}

	m_edtMent.SetFocus();
}

void CGroupChatDlg::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	LU->SetGroupChatPane(this);

	m_edtText.SetFont(m_FontManager.GetFont("맑은 고딕", 17));
	m_edtMent.SetFont(m_FontManager.GetFont("맑은 고딕", 18));

	RefreshEdit();
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

BOOL CGroupChatDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{	
		if(pMsg->hwnd == m_edtMent.GetSafeHwnd()) 
		{
				OnBnClickedSendButton();
		}
	}

	return CMyFormView::PreTranslateMessage(pMsg);
}

void CGroupChatDlg::GetDataTextSub(CString strName, CString strText, COleDateTime dtDate)
{
	CString strPreData;
	m_edtText.GetWindowText(strPreData);

	CString strTemp = "";
	strTemp.Format("[%s, %s]\r\n    %s\r\n", strName, dtDate.Format("%H:%M:%S"), strText);

	m_edtText.SetWindowText(strPreData + strTemp);

	long nLen = m_edtText.GetWindowTextLength();
	m_edtText.SetSel(nLen, nLen);

}

void CGroupChatDlg::GetDataText(CString strName, CString strText)
{
	GetDataTextSub(strName, strText, COleDateTime::GetCurrentTime());
} 

void CGroupChatDlg::RefreshEdit()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_group_chat_log");
	cmd.AddParameter(m_ci.m_nShareCode1);

	if(!rs.Execute(&cmd))
		return;

	CString strName, strText;
	COleDateTime dtGenerate;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("sName", strName);
		rs.GetFieldValue("sText", strText);
		rs.GetFieldValue("dtGenerate", dtGenerate);

		GetDataTextSub(strName, strText, dtGenerate);
		rs.MoveNext();
	}	
}