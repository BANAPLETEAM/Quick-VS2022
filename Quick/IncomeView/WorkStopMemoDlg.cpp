// WorkStopMemoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "WorkStopMemoDlg.h"



// CWorkStopMemoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CWorkStopMemoDlg, CMyDialog)
CWorkStopMemoDlg::CWorkStopMemoDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CWorkStopMemoDlg::IDD, pParent)
, m_strWorkStopMemo(_T(""))
, m_strContent(_T(""))
{
}

CWorkStopMemoDlg::~CWorkStopMemoDlg()
{
}

void CWorkStopMemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_CBString(pDX, IDC_WORKSTOP_MEMO_COMBO, m_strWorkStopMemo);
	DDX_Text(pDX, IDC_CONTENT_EDIT, m_strContent);
	DDX_Control(pDX, IDC_WORKSTOP_MEMO_COMBO, m_cmbWorkStopMemo);
	DDX_Control(pDX, IDC_CONTENT_EDIT, m_edtContent);
}


BEGIN_MESSAGE_MAP(CWorkStopMemoDlg, CMyDialog)
	ON_BN_CLICKED(IDC_WORKSTOP_BUTTON, OnBnClickedWorkstopButton)
	ON_BN_CLICKED(IDC_CANCEL_BUTTON, OnBnClickedCancelButton)
	ON_BN_CLICKED(IDC_WORKSTOP_BUTTON2, OnBnClickedWorkstopButton2)
END_MESSAGE_MAP()


// CWorkStopMemoDlg 메시지 처리기입니다.

void CWorkStopMemoDlg::OnBnClickedWorkstopButton()
{
	UpdateData();
	/*
	if(m_strWorkStopMemo.GetLength() <= 0)
	{
		MessageBox("제목을 기입하여주세요","확인",MB_ICONINFORMATION);
		return;
	}
	*/
		OnOK();
}

BOOL CWorkStopMemoDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{	
		if(pMsg->hwnd == m_cmbWorkStopMemo.GetSafeHwnd() ) {
			m_edtContent.SetFocus();
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CWorkStopMemoDlg::OnBnClickedCancelButton()
{
	OnCancel();
}

void CWorkStopMemoDlg::OnBnClickedWorkstopButton2()
{
	UpdateData();
	OnOK();
}
