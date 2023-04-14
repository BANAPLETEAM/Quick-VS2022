// MsgNoteDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MsgNoteDlg.h"
#include "NewConnListDlg.h"
#include "MkMessenger.h"
#include "NewMsgDlg.h"


// CMsgNoteDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMsgNoteDlg, CMyResizeDialog)

CMsgNoteDlg::CMsgNoteDlg(CWnd* pParent /*=NULL*/)
	: CMyResizeDialog(CMsgNoteDlg::IDD, pParent)
{
	m_nCompany = 0;
	m_nMNo = 0;
	m_nClientType = 0;
	m_strTitle = "쪽지 보내기";
	m_bInstanceMsg = FALSE;
}

CMsgNoteDlg::~CMsgNoteDlg()
{
}

void CMsgNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SEND_STATIC, m_strDescript);
	DDX_Text(pDX, IDC_TARGET_STATIC, m_strTarget);
	DDX_Text(pDX, IDC_SEND_EDIT, m_strSend);
}


BEGIN_MESSAGE_MAP(CMsgNoteDlg, CMyResizeDialog)
	ON_BN_CLICKED(IDC_SEND_MSG_BTN, &CMsgNoteDlg::OnBnClickedSendMsgBtn)
END_MESSAGE_MAP()


// CMsgNoteDlg 메시지 처리기입니다.

BOOL CMsgNoteDlg::OnInitDialog()
{
	CMyResizeDialog::OnInitDialog(); 

	SetWindowText(m_strTitle);

	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetResize(IDC_SEND_EDIT, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_TARGET_STATIC, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_SEND_MSG_BTN, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMsgNoteDlg::OnBnClickedSendMsgBtn()
{
	UpdateData(TRUE);
	if(m_strSend.GetLength() == 0)
	{
		MessageBox("보낼 내용을 입력하시기 바랍니다.", "확인", MB_ICONINFORMATION);
	}
	else
	{
		if(SendMsg())
		{
			CDialog::OnCancel();
		}
	}
}

void CMsgNoteDlg::AddMultiMember(long nCompany, long nWNo, CString strCompany, CString strName)
{
	MSG_MEMBER member;
	member.nCompany = nCompany;
	member.nWNo = nWNo;
	member.strCompany = strCompany;
	member.strName = strName;
	m_vecMsgMember.push_back(member);
}

BOOL CMsgNoteDlg::SendMsg()
{
	CNewConnListDlg *pConnListDlg = (CNewConnListDlg*)m_pParent;

	if(!m_bInstanceMsg)
	{
		if(m_vecMsgMember.size() > 0)
		{
			MSG_MEMBER_VECTOR::iterator it;
			for(it = m_vecMsgMember.begin(); it != m_vecMsgMember.end(); it++)
			{
				if(!pConnListDlg->InsertNoteMsg(it->nCompany, 
					it->nWNo, m_strSend, it->strCompany, it->strName))
					return FALSE;
			}
		}
		else
		{
			if(!pConnListDlg->InsertNoteMsg(m_nCompany, 
				m_nMNo, m_strSend, m_strCompanyName, m_strName))
				return FALSE;
		}
	}
	else
	{
		MSG_MEMBER_VECTOR::iterator it;
		for(it = m_vecMsgMember.begin(); it != m_vecMsgMember.end(); it++)
		{
			char buffer[10];
			CNewMsgDlg *pNewMsgDlg = ((CMkMessenger*)pConnListDlg->GetParentWnd())->ShowMsgDlg(
				pConnListDlg,
				"",  
				ltoa(it->nCompany, buffer, 10),
				ltoa(it->nWNo, buffer, 10),
				"0",
				m_ci.m_strBranchName,
				m_ui.strName,
				FALSE,
				TYPE_SINGLE,
				0,
				TRUE);

			if(pNewMsgDlg)
				pNewMsgDlg->SendMsg(m_strSend);
		}
	}

	return TRUE;
}


