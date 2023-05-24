// SmallTalkEditDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SmallTalkEditDlg.h"
#include "RiderShareBoardDlg.h"

// CSmallTalkEditDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSmallTalkEditDlg, CMyDialog)

CSmallTalkEditDlg::CSmallTalkEditDlg(CWnd* pParent)
: CMyDialog(CSmallTalkEditDlg::IDD, pParent)
{
	m_pParent = pParent;
	m_bUpdate = FALSE;
	m_nParentID = 0;
	m_bHomeForm = FALSE;
}

CSmallTalkEditDlg::~CSmallTalkEditDlg()
{
}

void CSmallTalkEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_EDIT, m_edtText);
	DDX_Text(pDX, IDC_TEXT_EDIT, m_strText);
	DDX_Control(pDX, IDC_INSERT_BTN, m_btnInsert);
	DDX_Control(pDX, IDC_CANCEL_BTN, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CSmallTalkEditDlg, CMyDialog)
	ON_BN_CLICKED(IDC_INSERT_BTN, &CSmallTalkEditDlg::OnBnClickedInsertBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CSmallTalkEditDlg::OnBnClickedCancelBtn)
END_MESSAGE_MAP()


// CSmallTalkEditDlg 메시지 처리기입니다.

void CSmallTalkEditDlg::OnBnClickedInsertBtn()
{
	UpdateData(TRUE);

	if(m_strText.GetLength() < 5)
	{
		MessageBox("5자이상으로 입력하여 주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	BOOL nRet = FALSE;

	if(m_bUpdate)
	{
		nRet = CRiderShareBoardDlg::UpdateTwitter(m_nParentID, m_strText);
		
		m_pParent->SendMessage(WM_TWITTER_UPDATE, (WPARAM)nRet, (LPARAM)0);
	}
	else
	{
		nRet = CRiderShareBoardDlg::WriteTwitter(m_nParentID, m_strText);

		m_pParent->SendMessage(WM_TWITTER_WRITE, (WPARAM)nRet, (LPARAM)0);
	}

	this->ShowWindow(FALSE);
}

void CSmallTalkEditDlg::OnBnClickedCancelBtn()
{
	this->ShowWindow(FALSE);
}

void CSmallTalkEditDlg::MoveControl()
{
	CRect rc, rcEdit, rcInsert, rcCancel;

	if(m_nParentID == -1)
		m_btnInsert.EnableWindow(FALSE);
	else
		m_btnInsert.EnableWindow(TRUE);

	GetWindowRect(rc);
	m_edtText.GetWindowRect(rcEdit);
	m_btnInsert.GetWindowRect(rcInsert);
	m_btnCancel.GetWindowRect(rcCancel);

	ScreenToClient(rc);
	ScreenToClient(rcEdit);
	ScreenToClient(rcInsert);
	ScreenToClient(rcCancel);

	long nWidth = rcInsert.Width();

	rcInsert.right = rc.right - 3;	rcInsert.left = rcInsert.right - nWidth;
	rcCancel.right = rc.right - 3;	rcCancel.left = rcCancel.right - nWidth;
	rcEdit.right = rcCancel.left - 3;

	m_edtText.MoveWindow(rcEdit);
	m_btnInsert.MoveWindow(rcInsert);
	m_btnCancel.MoveWindow(rcCancel);
}

BOOL CSmallTalkEditDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN)
		{
			if(pMsg->hwnd == m_btnInsert.GetSafeHwnd())
			{
				OnBnClickedInsertBtn();
			}

			return FALSE;
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}
