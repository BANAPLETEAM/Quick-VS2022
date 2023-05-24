// SearchRiderDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SearchRiderDlg.h"


// CSearchRiderDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSearchRiderDlg, CMyDialog)

CSearchRiderDlg::CSearchRiderDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSearchRiderDlg::IDD, pParent)
{
	m_strSearch = "";
	m_strRName = "";
	m_nRiderCompany = 0;
	m_nRNo = 0;
}

CSearchRiderDlg::~CSearchRiderDlg()
{
}

void CSearchRiderDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_lstReport);
	DDX_Control(pDX, IDC_RNO_EDIT, m_edtRNo);
}


BEGIN_MESSAGE_MAP(CSearchRiderDlg, CMyDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_LIST, OnReportItemDblClick)
	ON_BN_CLICKED(IDOK, &CSearchRiderDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CSearchRiderDlg::OnBnClickedSearchBtn)
END_MESSAGE_MAP()


// CSearchRiderDlg 메시지 처리기입니다.

BOOL CSearchRiderDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_lstReport.InsertColumn(0, "회사명", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(1, "기사", LVCFMT_LEFT, 100);

	CXTPGridColumn *pCol = m_lstReport.AddColumn(new CXTPGridColumn(2, _T("0"), 0, FALSE));
	pCol->SetVisible(FALSE);
 
	m_lstReport.Populate();

	m_edtRNo.SetWindowText(m_strSearch);
	RefreshList();

	return TRUE;
}

void CSearchRiderDlg::RefreshList()
{
	char buffer[10];
	CString strSearch;
	m_edtRNo.GetWindowText(strSearch);

	if(strSearch.GetLength() == 0)
	{
		MessageBox("검색어 (사번, 기사명)을 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_for_board");

	pCmd.AddParameter(m_ci.GetShareCode1());
	pCmd.AddParameter(m_ci.GetShareCode2());
	pCmd.AddParameter(m_ci.GetShareCode3());
	pCmd.AddParameter(m_ci.GetShareCode4());
	pCmd.AddParameter(m_ci.GetShareCode5());
	pCmd.AddParameter(strSearch);

	if(!pRs.Execute(&pCmd))
		return;

	m_lstReport.DeleteAllItems();

	long nCompany, nRNo;
	CString strRName, strCompanyName;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sRName", strRName);
		pRs.GetFieldValue("sCompanyName", strCompanyName);

		m_lstReport.InsertItem(i, strCompanyName);
		m_lstReport.SetItemText(i, 1, CString(itoa(nRNo, buffer, 10)) + "/" + strRName);
		m_lstReport.SetItemText(i, 2, strRName);

		m_lstReport.SetItemLong(i, nCompany);
		m_lstReport.SetItemLong2(i, nRNo);

		pRs.MoveNext();
	}

	m_lstReport.Populate();
}

void CSearchRiderDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	SaveItem();
}

void CSearchRiderDlg::SaveItem()
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();
	
	BOOL bOk = TRUE;
	if(pRows == NULL) bOk = FALSE;
	if(pRows->GetCount() == 0) bOk = FALSE;

	if(bOk == FALSE)
	{
		MessageBox("등록할 기사를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

	m_nRiderCompany = m_lstReport.GetItemLong(pRecord);
	m_nRNo = m_lstReport.GetItemLong2(pRecord);
	m_strRName = m_lstReport.GetItemText(pRecord, 2);

	OnOK(); 
}

void CSearchRiderDlg::OnBnClickedOk()
{
	if(m_lstReport.GetItemCount() == 1)
	{
		CXTPGridRows *pRows = m_lstReport.GetRows();
		m_lstReport.GetSelectedRows()->Select(pRows->GetAt(0));
	}

	SaveItem();
}

BOOL CSearchRiderDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if(pMsg->hwnd == m_edtRNo.GetSafeHwnd())
			RefreshList();
 
		return TRUE;
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CSearchRiderDlg::OnBnClickedSearchBtn()
{
	RefreshList();
}
