// AllocGroupListDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "AllocGroupListDlg.h"
#include "ConnListDlg2.h"

// CAllocGroupListDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAllocGroupListDlg, CMyDialog)

CAllocGroupListDlg::CAllocGroupListDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAllocGroupListDlg::IDD, pParent)
{
	m_pParent = pParent;
}

CAllocGroupListDlg::~CAllocGroupListDlg()
{
}

void CAllocGroupListDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALLOC_REPORT, m_lstAlloc);
} 


BEGIN_MESSAGE_MAP(CAllocGroupListDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CAllocGroupListDlg::OnBnClickedCloseBtn)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CAllocGroupListDlg::OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_CLICK, IDC_ALLOC_REPORT, OnReportItemClick)
END_MESSAGE_MAP()


// CAllocGroupListDlg 메시지 처리기입니다.

BOOL CAllocGroupListDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	SetForegroundWindow();

	m_lstAlloc.AddColumn(new CXTPGridColumn(0, "", 15));
	m_lstAlloc.AddColumn(new CXTPGridColumn(1, "", 80));
	m_lstAlloc.ShowHeader(FALSE);
	m_lstAlloc.Populate();


	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAllocGroupListDlg::OnBnClickedCloseBtn()
{
	ShowWindow(FALSE);
}

void CAllocGroupListDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CAllocGroupListDlg::RefreshList()
{
	m_lstAlloc.GetRecords()->RemoveAll();

	m_lstAlloc.AddRecord(new CAllocGroupRecord(-1, TRUE, "전체"));

	MAP_ALLOCATE_GROUP::iterator it;

	for(it = LU->m_mapAllocateGroup.begin(); it != LU->m_mapAllocateGroup.end(); it++)
	{
		m_lstAlloc.AddRecord(new CAllocGroupRecord(it->first, TRUE, it->second));
	}

	m_lstAlloc.Populate();
}


void CAllocGroupListDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	long nIndex = pItemNotify->pRow->GetIndex();
 
	CAllocGroupRecord *pRecord = (CAllocGroupRecord*)pItemNotify->pRow->GetRecord();

	BOOL bCheck = pRecord->GetCheck();
	pRecord->SetCheck(!bCheck);

	if(nIndex == 0)
	{
		CXTPGridRecords *pRecords = m_lstAlloc.GetRecords();

		for(int i=1; i<pRecords->GetCount()-1; i++)
		{
			((CAllocGroupRecord*)(pRecords->GetAt(i)))->SetCheck(!bCheck);						
		}
	}
	else
	{
		BOOL bAllCheck = FALSE;

		CXTPGridRecords *pRecords = m_lstAlloc.GetRecords();

		for(int i=1; i<pRecords->GetCount(); i++)
		{
			bAllCheck = ((CAllocGroupRecord*)(pRecords->GetAt(i)))->GetCheck();

			if(bAllCheck == FALSE)
				break;
		}

		((CAllocGroupRecord*)(pRecords->GetAt(0)))->SetCheck(bAllCheck);
	}

	m_lstAlloc.Populate();

	if(m_pParent)
		((CConnListDlg2*)m_pParent)->FilterList(); 
}
