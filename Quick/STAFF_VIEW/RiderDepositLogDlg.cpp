// RiderDepositLogDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "RiderDepositLogDlg.h"
#include "IncomeForm5.h"

// CRiderDepositLogDlg ��ȭ �����Դϴ�.

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

// CRiderDepositLogDlg �޽��� ó�����Դϴ�.

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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
