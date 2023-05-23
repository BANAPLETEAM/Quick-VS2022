// CompanyBranchListDlg1.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CompanyBranchListDlg1.h"
#include "MoveOrderPaintManager.h"

#define BUTTON_WIDTH_SIZE 82
#define BUTTON_HEGIHT_SIZE 42
#define MAX_ROW_COUNT 20

// CCompanyBranchListDlg1 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCompanyBranchListDlg1, CMyDialog)
CCompanyBranchListDlg1::CCompanyBranchListDlg1(CWnd* pParent /*=NULL*/)
: CMyDialog(CCompanyBranchListDlg1::IDD, pParent)
, m_bCopy(FALSE)
{
	m_pBi = NULL;
	m_bCorpOrder = FALSE;
}

CCompanyBranchListDlg1::~CCompanyBranchListDlg1()
{
}

void CCompanyBranchListDlg1::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_Report);
	DDX_Check(pDX, IDC_CHECK1, m_bCopy);
	DDX_Control(pDX, IDC_CHECK1, m_chkCopy);
}


BEGIN_MESSAGE_MAP(CCompanyBranchListDlg1, CMyDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT, OnReportItemDblClick)
	ON_WM_SIZE()
END_MESSAGE_MAP()


void CCompanyBranchListDlg1::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	if(m_bCorpOrder && m_chkCopy.GetCheck() == BST_CHECKED )
	{
		LF->MsgBox("법인오더는 고객을 복사하실수 없습니다. 체크를 풀어주세요");
		return;
	}

	
	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	CXTPGridRecord *pRecord = pItemNotify->pRow->GetRecord();

	CBranchStateRecordItem* pRecordItem = (CBranchStateRecordItem*)pRecord->GetItem(nCol);
	if(pRecordItem)
	{
		m_pBi = pRecordItem->pBi;	

		if(m_pBi)
		{
			if(m_pBi->nCustomerTable != m_pBi->nCompanyCode)
				m_chkCopy.SetCheck(FALSE);

			UpdateData(TRUE);
			OnOK();
		}
	}
}

void CCompanyBranchListDlg1::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

BOOL CCompanyBranchListDlg1::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	if(!m_bCorpOrder) // 법인이 아니라면
		m_chkCopy.SetCheck(TRUE);

	

	m_MyPaintManager = new CMoveOrderPaintManager;
	m_Report.SetPaintManager(m_MyPaintManager);
	m_Report.SetTreeIndent(10);
	m_Report.GetPaintManager()->m_strNoItems = "";
	m_Report.GetReportHeader()->AllowColumnRemove(FALSE);
	m_Report.GetReportHeader()->AllowColumnResize(FALSE);
	m_Report.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_Report.AllowEdit(FALSE);
	m_Report.FocusSubItems(FALSE);
	m_Report.GetPaintManager()->SetGridStyle(FALSE, xtpGridNoLines);
	m_Report.SetGridColor(RGB(150, 150, 180));
	m_Report.ShowHeader(FALSE);
	m_Report.GetPaintManager()->m_bHideSelection = TRUE; 

	RefreshList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCompanyBranchListDlg1::RefreshList()
{
	//Clear();

	m_Report.GetColumns()->Clear();
	m_Report.GetRows()->Clear();
	m_Report.GetRecords()->RemoveAll();
	m_Report.Populate();

	long nColumnCount = GetColumnCount();

	for(int i=0; i<nColumnCount; i++)
		m_Report.AddColumn(new CXTPGridColumn(i, "", BUTTON_WIDTH_SIZE, FALSE));

	CXTPGridRecord *pRecord[MAX_ROW_COUNT];

	for(int i=0; i<m_nOneColumnAbleCount; i++)
	{
		pRecord[i] = new CXTPGridRecord();
	}

	long nItem = 0;

	for(int i=1; i<m_ba.GetCount() ; i++)
	{
		CBranchStateRecordItem *pRecordItem = new CBranchStateRecordItem("");
		pRecordItem->pBi = m_ba.GetAt(i);

		if(i==1)
			pRecord[0]->AddItem(pRecordItem);
		else
			pRecord[(i-1) % m_nOneColumnAbleCount]->AddItem(pRecordItem);
	}

	for(int i=0; i<m_nOneColumnAbleCount; i++)
	{		
		pRecord[i] = m_Report.AddRecord(pRecord[i]);
	}

	m_Report.Populate();
}

long CCompanyBranchListDlg1::GetColumnCount()
{
	CRect rcList; m_Report.GetClientRect(rcList);

	long nBranchCount = m_ba.GetCount() - 1;
	m_nOneColumnAbleCount = rcList.Height() / BUTTON_HEGIHT_SIZE;

	if(m_nOneColumnAbleCount >= nBranchCount)
		m_nRowCount = nBranchCount;
	else
	{
		m_nRowCount = (nBranchCount / m_nOneColumnAbleCount) + 1;
	}

	return max((nBranchCount / m_nOneColumnAbleCount) + 1, 1);
}

void CCompanyBranchListDlg1::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CCompanyBranchListDlg1::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	CRect rc;

	CWnd *pWnd = (CWnd*)GetDlgItem(IDC_REPORT);

	if(pWnd != NULL)
	{
		pWnd->GetWindowRect(rc);
		ScreenToClient(rc);

		rc.right = cx - 5;
		rc.bottom = cy - 5;

		if((rc.Width() < BUTTON_WIDTH_SIZE) ||
			rc.Height() < BUTTON_HEGIHT_SIZE)
			return;

		pWnd->MoveWindow(rc, TRUE);
		RefreshList();
	}
}