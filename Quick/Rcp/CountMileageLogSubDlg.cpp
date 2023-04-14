// CountMileageLogSubDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CountMileageLogSubDlg.h"

#define BUTTON_WIDTH_SIZE 102
#define BUTTON_HEGIHT_SIZE 62
#define MAX_ROW_COUNT 20
// CCountMileageLogSubDlg

IMPLEMENT_DYNCREATE(CCountMileageLogSubDlg, CMyFormView)

CCountMileageLogSubDlg::CCountMileageLogSubDlg()
	: CMyFormView(CCountMileageLogSubDlg::IDD)
{
	m_nCMCount = 0;
	m_nCMCharge = 0;
	m_nColCount = 0;
	m_nRowCount = 0;

	m_nOneRowAbleCount = 0;

}

CCountMileageLogSubDlg::~CCountMileageLogSubDlg()
{
}

void CCountMileageLogSubDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MILEAGE_LOG_LIST, m_List);
}

BEGIN_MESSAGE_MAP(CCountMileageLogSubDlg, CMyFormView)
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CCountMileageLogSubDlg 진단입니다.

#ifdef _DEBUG
void CCountMileageLogSubDlg::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCountMileageLogSubDlg::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCountMileageLogSubDlg 메시지 처리기입니다.

int CCountMileageLogSubDlg::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return 0;
	return CMyFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CCountMileageLogSubDlg::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_MyPaintManager = new CMyPaintManager;
	m_List.SetPaintManager(m_MyPaintManager);

	m_List.SetTreeIndent(10);
	m_List.GetPaintManager()->m_strNoItems = "";
	m_List.GetReportHeader()->AllowColumnRemove(FALSE);
	m_List.GetReportHeader()->AllowColumnResize(FALSE);
	m_List.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_List.AllowEdit(FALSE);
	m_List.FocusSubItems(FALSE);
	m_List.GetPaintManager()->SetGridStyle(FALSE, xtpGridNoLines);
	m_List.SetGridColor(RGB(150, 150, 180));
	m_List.ShowHeader(FALSE);
	m_List.GetPaintManager()->m_bHideSelection = TRUE; 

	m_List.Populate();
}

void CCountMileageLogSubDlg::RefreshList()
{
	m_List.GetColumns()->Clear();
	m_List.GetRows()->Clear();
	m_List.GetRecords()->RemoveAll();
	m_List.Populate();

	long nColumnCount = GetColumnCount();

	if(nColumnCount == 0)
		return;

	for(int i=0; i<nColumnCount; i++)
		m_List.AddColumn(new CXTPGridColumn(i, "", BUTTON_WIDTH_SIZE, FALSE));

	CXTPGridRecord *pRecord[MAX_ROW_COUNT];

	for(int i=0; i<m_nRowCount; i++)
	{
		pRecord[i] = new CXTPGridRecord();
	}

	long nItem = 0;

	for(int i=0; i<m_nCMCount; i++)
	{
		MAP_COUNT_MILE::iterator it = m_pMap->find(i);
		CStateRecordItem *pRecordItem = new CStateRecordItem("");

		if(it != m_pMap->end())
		{
			pRecordItem->m_bApply = FALSE;
			pRecordItem->m_nTNo = it->second->nTNo;
			pRecordItem->m_dt1 = it->second->dt1;
		}

		pRecordItem->m_nDay = i+1;
		
		if(i==0)
			pRecord[i]->AddItem(pRecordItem);
		else
			pRecord[i/nColumnCount]->AddItem(pRecordItem);

	}

	for(int i=0; i<m_nRowCount; i++)
	{		
		pRecord[i] = m_List.AddRecord(pRecord[i]);
	}

	m_List.Populate();
}

long CCountMileageLogSubDlg::GetColumnCount()
{
	CRect rcList; m_List.GetClientRect(rcList);

	m_nOneRowAbleCount = (rcList.Width() - 20) / BUTTON_WIDTH_SIZE; 

	if(m_nOneRowAbleCount == 0)
		return 0 ;

	if(m_nOneRowAbleCount >= m_nCMCount)
		m_nRowCount = 1;
	else
	{
		m_nRowCount = (m_nCMCount / m_nOneRowAbleCount) + 1;
	}

	return m_nOneRowAbleCount;
}

void CCountMileageLogSubDlg::MoveControl()
{
	if(m_List.GetSafeHwnd() == NULL) return;

	CRect rcClient, rcList; 

	this->GetWindowRect(rcClient);
	m_List.GetWindowRect(rcList);

	ScreenToClient(rcClient);
	ScreenToClient(rcList);

	rcList.right = rcClient.right - 5; 
	rcList.bottom = rcClient.bottom - 5;
	m_List.MoveWindow(rcList);

	RefreshList();
}