// MsgDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MsgDlg.h"
#include "NotifierContainer.h"

// CMsgDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMsgDlg, CMyDialog)
CMsgDlg::CMsgDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMsgDlg::IDD, pParent)
{
	m_pParentWnd = pParent;
	m_ptrItemData = NULL;
}

CMsgDlg::~CMsgDlg()
{
}

void CMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RECV_EDIT, m_strRecv);
	DDX_Text(pDX, IDC_SEND_EDIT, m_strSend);
	DDX_Control(pDX, IDC_RECV_EDIT, m_RecvEdit);
	DDX_Control(pDX, IDC_SEND_EDIT, m_SendEdit);
}


BEGIN_MESSAGE_MAP(CMsgDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SEND_MSG, OnBnClickedSendMsg)
	ON_BN_CLICKED(IDC_CALLING_BTN, OnBnClickedCallingBtn)
END_MESSAGE_MAP()


// CMsgDlg 메시지 처리기입니다.

BOOL CMsgDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	
	CenterWindow(GetDesktopWindow());

	CRect rc;
	m_RecvEdit.GetClientRect(&rc);
	rc.DeflateRect(2, 3);
	m_RecvEdit.SetRect(&rc);

	m_SendEdit.GetClientRect(&rc);
	rc.DeflateRect(2, 3);
	m_SendEdit.SetRect(&rc);

	SetWindowText(m_strTitle);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMsgDlg::OnBnClickedSendMsg()
{
	UpdateData(TRUE);

	NOTIFIER_ITEM *pNItem = (NOTIFIER_ITEM*)m_ptrItemData;
	pNItem->type = NFI_SEND_MESSAGE;
	pNItem->strCName = m_ci.m_strName + "/" + m_ui.strName;
	pNItem->strMsg = m_strSend;

	m_pParentWnd->PostMessage(WM_NOTIFIER_CLICKED, (WPARAM)pNItem, (LPARAM)this); 
}

void CMsgDlg::OnBnClickedCallingBtn()
{
	UpdateData(TRUE);

	NOTIFIER_ITEM *pNItem = (NOTIFIER_ITEM*)m_ptrItemData;
	pNItem->type = NFI_SEND_MESSAGE;
	pNItem->strCName = m_ci.m_strName + "/" + m_ui.strName;
	pNItem->strMsg = "상담원이 고객님에게 전화를 거는 중입니다.";

	m_pParentWnd->PostMessage(WM_NOTIFIER_CLICKED, (WPARAM)pNItem, (LPARAM)this); 	
}
