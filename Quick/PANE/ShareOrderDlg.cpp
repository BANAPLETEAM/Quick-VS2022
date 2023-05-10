// ShareOrderDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareOrderDlg.h"

#include "MainFrm.h"

// CShareOrderDlg 대화 상자입니다.
IMPLEMENT_DYNCREATE(CShareOrderDlg, CMyFormView)
CShareOrderDlg::CShareOrderDlg()
: CMyFormView(CShareOrderDlg::IDD)
{
	m_dwLastRefreshList = 0;
}

CShareOrderDlg::~CShareOrderDlg()
{
}

void CShareOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CShareOrderDlg, CMyFormView)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)
END_MESSAGE_MAP()


// CShareOrderDlg 메시지 처리기입니다.

void CShareOrderDlg::OnInitialUpdate()
{
	if(m_bInitialUpdateCalled) return;

	CMyFormView::OnInitialUpdate();

	this->GetParentFrame()->GetActiveFrame()->ShowWindow(SW_HIDE);
	this->GetParentFrame()->ShowWindow(SW_HIDE);
	m_pBi = m_ba.GetAt(0);
	this->SetTimer(100,3000,NULL);

	SetResize(IDC_LIST, sizingRightBottom);
}


void CShareOrderDlg::RefreshList()
{
	CWaitCursor wait;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_client_share_order2_1");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_pBi->nCompanyCode);
	if(pRs.Execute(&pCmd))
	{
		long nItem = 0;
		long nCompany = 0;
		long nShareCode1 = 0;
		m_List.DeleteAllItems();
		while(!pRs.IsEOF())
		{
			char buffer[10];
			CString strStart;
			pRs.GetFieldValue("sSDong", strStart);
			pRs.GetFieldValue("nShareCode1", nShareCode1);
			pRs.GetFieldValue("nCompany", nCompany);

			if(nShareCode1 == m_pBi->nShareCode1 )
				strStart = CString(ltoa(nItem+1, buffer, 10)) + ". " +  strStart 
				+ "[1차" + m_ci.GetName(nCompany) + "]";
			else
				strStart = CString(ltoa(nItem+1, buffer, 10)) + ". " +  strStart;
			m_List.InsertItem(nItem++, strStart);
			pRs.MoveNext();
		}

		CString strTitle;
		strTitle.Format("공유콜(%s 기준) - %d개", m_pBi->strBranchName, nItem);
		SetWindowText(strTitle);

	}
}


void CShareOrderDlg::OnTimer(UINT nIDEvent)
{
	if(100 == nIDEvent)
	{
		KillTimer(nIDEvent);

		if( this->IsWindowVisible() && (::GetTickCount() - m_dwLastRefreshList) > 10*1000)
		{
			RefreshList();
			this->Invalidate();
			m_dwLastRefreshList = GetTickCount();
		}

		SetTimer(nIDEvent,1000,NULL);
	}

	CMyFormView::OnTimer(nIDEvent);
}

int CShareOrderDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMyFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	ModifyStyle( 0, WS_CLIPSIBLINGS|WS_CLIPCHILDREN );

	return 0;
}

void CShareOrderDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
