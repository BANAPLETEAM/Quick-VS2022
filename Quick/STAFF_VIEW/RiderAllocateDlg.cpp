// RiderAllocateDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderAllocateDlg.h"
#include ".\riderallocatedlg.h"
#include "RiderAdviceDlg2010.h"

// CRiderAllocateDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderAllocateDlg, CMyDialog)
CRiderAllocateDlg::CRiderAllocateDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CRiderAllocateDlg::IDD, pParent)
{
	m_nSearchType = 0;
	m_nGetRiderCompany = 0;
	m_nGetRNo = 0;
	m_strGetRName = "";
}

CRiderAllocateDlg::~CRiderAllocateDlg()
{
}

void CRiderAllocateDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM1, m_List);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}


BEGIN_MESSAGE_MAP(CRiderAllocateDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_CUSTOM1, OnNMDblclkList1)
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CRiderAllocateDlg::OnBnClickedSearchBtn)
END_MESSAGE_MAP()


// CRiderAllocateDlg 메시지 처리기입니다.

void CRiderAllocateDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

BOOL CRiderAllocateDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	//CDataBox m_List;


	m_List.InsertColumn(0, "순번", DT_CENTER, 40);
	m_List.InsertColumn(1, "회사명", DT_LEFT, 110);
	m_List.InsertColumn(2, "지사명", DT_LEFT, 90);
	m_List.InsertColumn(3, "상황실", DT_LEFT, 90);
	m_List.InsertColumn(4, "대표번호", DT_LEFT, 90);
	m_List.InsertColumn(5, "사번", DT_LEFT, 55);
	m_List.InsertColumn(6, "아이디", DT_LEFT, 110);
	m_List.InsertColumn(7, "핸드폰", DT_LEFT, 110);
	m_List.InsertColumn(8, "이름", DT_LEFT, 90);
	m_List.SetOrderIndexCol(0);

	m_List.Populate();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CRiderAllocateDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM* pNMListView = (XTP_NM_REPORTRECORDITEM*)pNMHDR;

	if(pNMListView->pRow == NULL)
		return;

	long nRow = pNMListView->pRow->GetIndex();
	long nCol = pNMListView->pColumn->GetItemIndex();

	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)pNMListView->pRow->GetRecord();

	//CXTPGridRow *pRow = m_List.GetSelectedRows()->GetAt(pNMListView->pRow->GetIndex());
	//CMyXTPGridRecord *pReocrd = (CMyXTPGridRecord *)pRow->GetRecord();
	long nCompany = m_List.GetItemLong(pRecord);
	long nRNo = m_List.GetItemLong2(pRecord);
	CString strRName = m_List.GetItemString(pRecord);

	m_nGetRiderCompany = nCompany;
	m_nGetRNo = nRNo;
	m_strGetRName = strRName;
	OnOK();		
}


void CRiderAllocateDlg::OnEnChangeSearchEdit()
{
}

BOOL CRiderAllocateDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN &&pMsg->wParam == VK_RETURN 
		&& ::GetDlgCtrlID(pMsg->hwnd) == IDC_SEARCH_EDIT)	
	{

		SearchRiderList();		
		return FALSE;
	}
	return CMyDialog::PreTranslateMessage(pMsg);
}


void CRiderAllocateDlg::SearchRiderList()
{
	CString strSearch = "", strType = "";
	m_edtSearch.GetWindowText(strSearch);

	if(strSearch.GetLength() <= 0)
		return;

	strSearch.Replace("-", "");	
	int nType = 0;
	
	if(strSearch.IsEmpty())
	{
		LF->MsgBox("검색어를 입력하세요");
		return;
	}

	if(LF->IsNumber(strSearch) == FALSE)
	{
		LF->MsgBox("사번 조회만 가능합니다");
		return;
	}

	m_List.DeleteAllItems();
 
	CMkCommand cmd(m_pMkDb, "select_other_allocate_rider_new_2");
	CMkRecordset rs(m_pMkDb);
	cmd.AddParameter(m_ci.m_nCompanyCode);
	cmd.AddParameter(strSearch);

	if(!rs.Execute(&cmd)) return;
	int nCount = 0;
	while(!rs.IsEOF())
	{
		int nMNo, nCompany;
		CString strBranchName, strCompanyName, strCompanyTel, strOfficePhone, strID, strHp, strName;

		rs.GetFieldValue("nID", nCompany);
		rs.GetFieldValue("nMNo", nMNo);
		rs.GetFieldValue("sID", strID);
		rs.GetFieldValue("sHp", strHp);
		rs.GetFieldValue("sName", strName);	

		m_List.InsertItem(nCount, "");
		m_List.SetItemText(nCount, 1, m_ci.GetShareCompanyName(nCompany));
		m_List.SetItemText(nCount, 2, m_ci.GetShareCompanyBranchName(nCompany));
		m_List.SetItemText(nCount, 3, m_ci.GetShareCompanyOfficePhone(nCompany));
		m_List.SetItemText(nCount, 4, m_ci.GetShareCompanyPhone(nCompany));
		m_List.SetItemText(nCount, 5, LF->GetStringFromLong(nMNo));
		m_List.SetItemText(nCount, 6, strID);
		m_List.SetItemText(nCount, 7, LF->GetDashPhoneNumber(strHp));
		m_List.SetItemText(nCount, 8, strName);

		m_List.SetItemLong(nCount, nCompany);
		m_List.SetItemLong2(nCount, nMNo);
		m_List.SetItemString(nCount, strName);

		nCount++;
		rs.MoveNext();	

	}
	rs.Close();


	m_List.Populate();

}

void CRiderAllocateDlg::SetOnlyRiderSearch()
{
}


void CRiderAllocateDlg::OnBnClickedSearchBtn()
{
	SearchRiderList();
}
