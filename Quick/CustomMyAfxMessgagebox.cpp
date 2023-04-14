// CustomMyAfxMessgagebox.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "CustomMyAfxMessgagebox.h"


// CCustomMyAfxMessgagebox 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCustomMyAfxMessgagebox, CMyDialog)

CCustomMyAfxMessgagebox::CCustomMyAfxMessgagebox(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCustomMyAfxMessgagebox::IDD, pParent)
{
	m_bCustomMode = FALSE;
}

CCustomMyAfxMessgagebox::~CCustomMyAfxMessgagebox()
{
}

void CCustomMyAfxMessgagebox::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLE_STC, m_stcTitle);
	DDX_Control(pDX, IDC_DESC_STC, m_stcDescription1);
	DDX_Control(pDX, IDC_DESC_STC2, m_stcDescription2);

	if(m_bCustomMode)
	{
		m_stcTitle.SetWindowText(m_strTitle);
		m_stcDescription2.SetWindowText(m_strSecondDesc);
		(GetDlgItem(IDC_CANCLE_BTN))->ShowWindow(SW_HIDE);
		CMenu* pSysMenu = GetSystemMenu(FALSE);
		if(pSysMenu)
			pSysMenu->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED);
	}
}


BEGIN_MESSAGE_MAP(CCustomMyAfxMessgagebox, CMyDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_YES_BTN, &CCustomMyAfxMessgagebox::OnBnClickedYesBtn)
	ON_BN_CLICKED(IDC_NO_BTN, &CCustomMyAfxMessgagebox::OnBnClickedNoBtn)
	ON_BN_CLICKED(IDC_CANCLE_BTN, &CCustomMyAfxMessgagebox::OnBnClickedCancleBtn)
	ON_STN_CLICKED(IDC_DESC_STC, &CCustomMyAfxMessgagebox::OnStnClickedDescStc)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCustomMyAfxMessgagebox 메시지 처리기입니다.

void CCustomMyAfxMessgagebox::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnClose();
}

void CCustomMyAfxMessgagebox::OnBnClickedYesBtn()
{
	m_nType = 0;
	OnOK();
}

void CCustomMyAfxMessgagebox::OnBnClickedNoBtn()
{
	m_nType = 1;
	OnOK();
}

void CCustomMyAfxMessgagebox::OnBnClickedCancleBtn()
{
	OnCancel();
}

void CCustomMyAfxMessgagebox::OnStnClickedDescStc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

HBRUSH CCustomMyAfxMessgagebox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	if(pWnd->GetDlgCtrlID() == IDC_DESC_STC2)
		pDC->SetTextColor(RGB(255, 0, 0));
	pDC->SetBkMode(TRANSPARENT);
	//return hbr;
	return (HBRUSH)GetStockObject(NULL_BRUSH);
}

void CCustomMyAfxMessgagebox::SetTitle(CString strTitle)
{
	m_strTitle = strTitle;
}

void CCustomMyAfxMessgagebox::SetFirstDesc(CString strText)
{
	m_strFirstDesc = strText;
}

void CCustomMyAfxMessgagebox::SetSecondDesc(CString strText)
{
	m_strSecondDesc = strText;
}