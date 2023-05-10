// RiderDepositLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "RiderDepositLogDlg.h"
#include "IncomeForm5.h"

// CRiderDepositLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderDepositLogDlg, CDialog)

CRiderDepositLogDlg::CRiderDepositLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRiderDepositLogDlg::IDD, pParent)
{
	m_bOk = FALSE;
}

CRiderDepositLogDlg::~CRiderDepositLogDlg()
{
}

void CRiderDepositLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_stc1);
}


BEGIN_MESSAGE_MAP(CRiderDepositLogDlg, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CRiderDepositLogDlg::RefreshOneRider(long nCompany, long nRNo)
{
	m_bOk = TRUE;
	m_pIncomeView->RefreshOneRider(nCompany, nRNo);
}

// CRiderDepositLogDlg 메시지 처리기입니다.

BOOL CRiderDepositLogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rc; 
	m_stc1.GetWindowRect(rc);
	ScreenToClient(rc);

	m_context.m_pNewViewClass = RUNTIME_CLASS(CIncomeForm5);
	m_pIncomeView = (CIncomeForm5*)((CFrameWnd*)this)->CreateView(&m_context);
	ASSERT(m_pIncomeView);

	m_pIncomeView->OnInitialUpdate();
	m_pIncomeView->ShowWindow(SW_NORMAL);
	m_pIncomeView->MoveWindow(&rc);
	//m_pSearchView->SetMsgWnd(this);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRiderDepositLogDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if(m_bOk == TRUE)
	{
		if(m_pIncomeView)
		{
			CRect rcDlg, rcList;
			GetClientRect(rcDlg);
			m_stc1.GetWindowRect(rcList);
			ScreenToClient(rcList);
 
			rcList.right = rcDlg.right - 1;
			rcList.bottom = rcDlg.bottom - 1; 

			m_stc1.MoveWindow(rcList);
			m_pIncomeView->MoveWindow(rcList); 
			m_pIncomeView->SendMessage(WM_SIZE, (WPARAM)SIZE_RESTORED, MAKELPARAM(cx, cy));
		}

	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
