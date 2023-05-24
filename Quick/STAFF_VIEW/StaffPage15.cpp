// StaffPage15.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "StaffPage15.h"


// CStaffPage15

IMPLEMENT_DYNCREATE(CStaffPage15, CMyFormView)

CStaffPage15::CStaffPage15()
	: CMyFormView(CStaffPage15::IDD)
{

}

CStaffPage15::~CStaffPage15()
{
}

void CStaffPage15::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REPORT, m_lstReport);
	DDX_Control(pDX, IDC_LIST_ORDER_REPORT, m_lstOtherReport);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_SEARCH_OTHER_EDIT, m_edtSearchOther);
	DDX_Control(pDX, IDC_HELP_STATIC, m_stcHelp);
}

BEGIN_MESSAGE_MAP(CStaffPage15, CMyFormView)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &CStaffPage15::OnBnClickedDeleteButton)
	ON_BN_CLICKED(IDC_REFRESH_LIST_BUTTON, &CStaffPage15::OnBnClickedRefreshListButton)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CStaffPage15::OnEnChangeSearchEdit)
	ON_EN_CHANGE(IDC_SEARCH_OTHER_EDIT, &CStaffPage15::OnEnChangeSearchOtherEdit)
	
	ON_BN_CLICKED(IDC_SHARE_RIDER_BUTTON, &CStaffPage15::OnBnClickedShareRiderButton)
END_MESSAGE_MAP()


// CStaffPage15 진단입니다.

#ifdef _DEBUG
void CStaffPage15::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStaffPage15::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStaffPage15 메시지 처리기입니다.

void CStaffPage15::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_lstReport.InsertColumn(0, "NO", LVCFMT_CENTER, 35);
	m_lstReport.InsertColumn(1, "오더소속", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(2, "기사소속", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(3, "사번", LVCFMT_RIGHT, 45);
	m_lstReport.InsertColumn(4, "성 명", LVCFMT_LEFT, 65);	
	m_lstReport.InsertColumn(5, "아이디",	LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(6, "등록일",LVCFMT_CENTER, 90);
	m_lstReport.InsertColumn(7, "주민번호", LVCFMT_CENTER, 90);
	m_lstReport.SetOrderIndexCol(0);

	m_lstOtherReport.InsertColumn(0, "NO", LVCFMT_CENTER, 35);
	m_lstOtherReport.InsertColumn(1, "오더소속", LVCFMT_LEFT, 80);
	m_lstOtherReport.InsertColumn(2, "대표번호",	LVCFMT_LEFT, 90);
	m_lstOtherReport.InsertColumn(3, "상황실",	LVCFMT_LEFT, 90);
	m_lstOtherReport.InsertColumn(4, "기사소속", LVCFMT_LEFT, 80);
	m_lstOtherReport.InsertColumn(5, "사번", LVCFMT_RIGHT, 45);
	m_lstOtherReport.InsertColumn(6, "성 명", LVCFMT_LEFT, 65);	
	m_lstOtherReport.InsertColumn(7, "아이디",	LVCFMT_LEFT, 90);
	m_lstOtherReport.InsertColumn(8, "등록일",LVCFMT_CENTER, 90);
	m_lstOtherReport.InsertColumn(9, "등록자",	LVCFMT_LEFT, 60);
	m_lstOtherReport.InsertColumn(10, "주민번호", LVCFMT_CENTER, 90);
	m_lstOtherReport.SetOrderIndexCol(0);


	m_lstReport.Populate();
	m_lstOtherReport.Populate();

	SetResize(IDC_LIST_REPORT, sizingBottom);
	SetResize(IDC_LIST_ORDER_REPORT, sizingRightBottom);
}

void CStaffPage15::RefreshList()
{
	RefreshListMyLimit();
	RefreshListOtherLimit();
	
}

void CStaffPage15::RefreshListMyLimit()
{
	char buffer[10]; 
	m_lstReport.DeleteAllItems();

	long nID, nRNo, nCount = ZERO; 
	CString strRiderCompany, strRName,strOrderCompany, strID, strJumin, strRJumin;
	COleDateTime dtPrevent; 

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_refusal_rider_auto_3");
	pCmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(TRUE);
	CMkParameter *parOut = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(pRs.Execute(&pCmd) == FALSE)
		return;

	parOut->GetValue(nCount);

	for(int i=ZERO; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nID", nID);

		pRs.GetFieldValue("sOrderCompany", strOrderCompany);
		pRs.GetFieldValue("sRiderCompany", strRiderCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sRName", strRName);
		pRs.GetFieldValue("sID", strID);
		pRs.GetFieldValue("dtPrevent", dtPrevent);
		pRs.GetFieldValue("sjumin", strJumin);

		strRJumin = strJumin;

		if(strJumin.GetLength() > 10)
			strJumin = "**" + strJumin.Mid(2,4);
		else
			strJumin = "";

		m_lstReport.InsertItem(i, "");
		m_lstReport.SetItemText(i, 1, strOrderCompany);
		m_lstReport.SetItemText(i, 2, strRiderCompany);
		m_lstReport.SetItemText(i, 3, itoa(nRNo, buffer, 10));
		m_lstReport.SetItemText(i, 4, strRName);
		m_lstReport.SetItemText(i, 5, strID);
		m_lstReport.SetItemText(i, 6, dtPrevent.Format("%Y-%m-%d"));
		m_lstReport.SetItemText(i, 7, strJumin);
		m_lstReport.SetItemLong(i, nID);
		m_lstReport.SetItemString(i, strRJumin);

		pRs.MoveNext();
	}

	m_lstReport.Populate();

	if(nCount > 0)
	{
		return;
		CString strTemp;
		strTemp.Format("즉시공유기사 %d명", nCount);
		m_stcHelp.SetWindowText(strTemp);
	}
}

void CStaffPage15::RefreshListOtherLimit()
{
	char buffer[10]; 
	m_lstOtherReport.DeleteAllItems();

	long nID, nRNo, nCount = ZERO; 
	CString strRiderCompany,strOrderCompany, strRName, strID, strJumin, strRJumin, strOtherCompanyTel, strOtherCompanyOffice, strOtherWName;
	COleDateTime dtPrevent; 

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_refusal_rider_auto_3");
	pCmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(FALSE);
	CMkParameter *parOut = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(pRs.Execute(&pCmd) == FALSE)
		return;

	parOut->GetValue(nCount);

	for(int i=ZERO; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("sOrderCompany", strOrderCompany);
		pRs.GetFieldValue("sRiderCompany", strRiderCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sRName", strRName);
		pRs.GetFieldValue("sID", strID);
		pRs.GetFieldValue("dtPrevent", dtPrevent);
		pRs.GetFieldValue("sjumin", strJumin);
		pRs.GetFieldValue("sOtherCompanyTel", strOtherCompanyTel);
		pRs.GetFieldValue("sOtherCompanyOffice", strOtherCompanyOffice);
		pRs.GetFieldValue("sOtherWName", strOtherWName);

		strRJumin = strJumin;

		m_lstOtherReport.InsertItem(i, "");
		m_lstOtherReport.SetItemText(i, 1, strOrderCompany);
		m_lstOtherReport.SetItemText(i, 2, strOtherCompanyTel);
		m_lstOtherReport.SetItemText(i, 3, strOtherCompanyOffice);
		m_lstOtherReport.SetItemText(i, 4, strRiderCompany);
		m_lstOtherReport.SetItemText(i, 5, itoa(nRNo, buffer, 10));
		m_lstOtherReport.SetItemText(i, 6, strRName);
		m_lstOtherReport.SetItemText(i, 7, strID);
		m_lstOtherReport.SetItemText(i, 8, dtPrevent.Format("%Y-%m-%d"));
		m_lstOtherReport.SetItemText(i, 9, strOtherWName);
		m_lstOtherReport.SetItemText(i, 10, strJumin);
		m_lstOtherReport.SetItemLong(i, nID);
		m_lstOtherReport.SetItemString(i, strRJumin);

		pRs.MoveNext();
	}

	m_lstOtherReport.Populate();

	if(nCount > 0)
	{
		return;
		CString strTemp;
		strTemp.Format("즉시공유기사 %d명", nCount);
		m_stcHelp.SetWindowText(strTemp);
	}
}

void CStaffPage15::OnBnClickedDeleteButton()
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == ZERO) return;

	CString strTemp; strTemp.Format("%d명의 기사님을 배차제한 해지 하시겠습니까?", pRows->GetCount());

	if(MessageBox(strTemp, "확인", MB_OKCANCEL) != IDOK)
		return;

	BOOL bDelete = FALSE;

	for(int i=ZERO; i<pRows->GetCount(); i++)
	{
		long nID = m_lstReport.GetItemLong(pRows->GetAt(i)->GetRecord());
		BOOL bAllDelete = FALSE;

		CMkCommand pCmd(m_pMkDb, "delete_share_refusal_rider");
		pCmd.AddParameter(nID);
		pCmd.AddParameter(bAllDelete);
		pCmd.AddParameter(m_ui.nCompany);
		pCmd.AddParameter(m_ui.nWNo);
		pCmd.AddParameter(m_ui.strName);

		if(pCmd.Execute())
			bDelete = TRUE;
		else
			return;
	}

	if(bDelete)
		RefreshListMyLimit();
}

void CStaffPage15::OnBnClickedRefreshListButton()
{
	RefreshListMyLimit();
	RefreshListOtherLimit();
}


void CStaffPage15::OnEnChangeSearchOtherEdit()
{
	CString strSearch; m_edtSearchOther.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstOtherReport.GetRecords();

	for(int i=ZERO; i<pRecords->GetCount(); i++)
	{ 
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString strRNo = pRecord->GetItem(THREE)->GetCaption(NULL);
		CString strRName = pRecord->GetItem(FOUR)->GetCaption(NULL);
		CString strID = pRecord->GetItem(FOUR)->GetCaption(NULL);
		CString strJumin = m_lstOtherReport.GetItemString(pRecord);

		if(strRNo.Find(strSearch) >= ZERO ||
			strRName.Find(strSearch) >= ZERO ||
			strID.Find(strSearch) >= ZERO ||
			strJumin.Find(strSearch) >= ZERO)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstOtherReport.Populate();		
}
void CStaffPage15::OnEnChangeSearchEdit()
{
	CString strSearch; m_edtSearch.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=ZERO; i<pRecords->GetCount(); i++)
	{ 
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString strRNo = pRecord->GetItem(THREE)->GetCaption(NULL);
		CString strRName = pRecord->GetItem(FOUR)->GetCaption(NULL);
		CString strID = pRecord->GetItem(FIVE)->GetCaption(NULL);
		CString strJumin = m_lstReport.GetItemString(pRecord);

		if(strRNo.Find(strSearch) >= ZERO ||
			strRName.Find(strSearch) >= ZERO ||
			strID.Find(strSearch) >= ZERO ||
			strJumin.Find(strSearch) >= ZERO)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstReport.Populate();		
}

void CStaffPage15::OnBnClickedShareRiderButton()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_share_count");
	pCmd.AddParameter(m_ci.m_nCompanyCode);

	if(pRs.Execute(&pCmd) == FALSE)
		return;

	CString strCompanyName, strTemp = "";
	long nCount;

	for(int i=ZERO; i<pRs.GetRecordCount(); i++)
	{
		CString strTemp1;
		pRs.GetFieldValue("sCompanyName", strCompanyName);
		pRs.GetFieldValue("nCount", nCount);

		strTemp1.Format("%s  %d명\r\n", strCompanyName, nCount);
		strTemp += strTemp1;

		pRs.MoveNext();
	}

	if(strTemp.IsEmpty())
		strTemp = "즉시공유 기사가 없습니다";
	
	MessageBox(strTemp, "확인", MB_ICONINFORMATION);	
}
