// IncomeForm11.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "IncomeForm11.h"


// CIncomeForm11

IMPLEMENT_DYNCREATE(CIncomeForm11, CMyFormView)

CIncomeForm11::CIncomeForm11()
	: CMyFormView(CIncomeForm11::IDD)
{

}

CIncomeForm11::~CIncomeForm11()
{
}

void CIncomeForm11::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);

	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtpFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtpTo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnData);
	DDX_Control(pDX, IDC_LIST, m_lstReport);
}

BEGIN_MESSAGE_MAP(CIncomeForm11, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CIncomeForm11::OnBnClickedRefreshBtn)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CIncomeForm11::OnEnChangeSearchEdit)
END_MESSAGE_MAP()


// CIncomeForm11 진단입니다.

#ifdef _DEBUG
void CIncomeForm11::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CIncomeForm11::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIncomeForm11 메시지 처리기입니다.

void CIncomeForm11::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_btnData.InitDateButton(&m_dtpFrom, &m_dtpTo);
	m_btnData.OnMenuMonth();

	SetResize(IDC_LIST, sizingRightBottom);

	m_lstReport.InsertColumn(0, "날짜", LVCFMT_CENTER, 130);
	m_lstReport.InsertColumn(1, "입금은행명", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(2, "입금자명", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(3, "가상계좌번호", LVCFMT_LEFT, 120);
	m_lstReport.InsertColumn(4, "은행입금액", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(5, "기사충전금", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(6, "공동정산충전금", LVCFMT_RIGHT, 90);
	m_lstReport.InsertColumn(7, "사번", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(8, "기사명", LVCFMT_LEFT, 80);

	m_lstReport.Populate();

}

void CIncomeForm11::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CIncomeForm11::RefreshList()
{
	UpdateData(TRUE); 
	m_lstReport.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rider_vraccount_income_log");
	cmd.AddParameter(typeLong, typeInput, sizeof(int), GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(typeBool, typeInput, sizeof(int), GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	cmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);

	if(!rs.Execute(&cmd))
		return;

	COleDateTime dtDate;
	CString strBankName, strAccountOwner, strName, strVraccount;
	long nRNo, nChargeRider, nChargeCompany, nCharge;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{ 
		rs.GetFieldValue("dtDate", dtDate);
		rs.GetFieldValue("sBankName", strBankName);
		rs.GetFieldValue("sAccountOwner", strAccountOwner);
		rs.GetFieldValue("sName", strName);
		rs.GetFieldValue("nRNo", nRNo); 
		rs.GetFieldValue("nChargeRider", nChargeRider); 
		rs.GetFieldValue("nChargeCompany", nChargeCompany);
		rs.GetFieldValue("nCharge", nCharge);
		rs.GetFieldValue("sVrAccount", strVraccount);

		m_lstReport.InsertItem(i, dtDate.Format("%Y-%m-%d %H:%M:%S") + "(" + ::GetDay(dtDate) + ")");
		m_lstReport.SetItemText(i, 1, strBankName);
		m_lstReport.SetItemText(i, 2, strAccountOwner);
		m_lstReport.SetItemText(i, 3, strVraccount);
		m_lstReport.SetItemText(i, 4, ::GetMyNumberFormat(nCharge));
		m_lstReport.SetItemText(i, 5, ::GetMyNumberFormat(nChargeRider));
		m_lstReport.SetItemText(i, 6, ::GetMyNumberFormat(nChargeCompany));
		m_lstReport.SetItemText(i, 7, ::GetStringFromLong(nRNo));
		m_lstReport.SetItemText(i, 8, strName);

		rs.MoveNext();
	}

	OnEnChangeSearchEdit();
}

void CIncomeForm11::OnEnChangeSearchEdit()
{
	CString strSearch; m_edtSearch.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strBank = pRecord->GetItem(1)->GetCaption(NULL);
		CString strOwner = pRecord->GetItem(2)->GetCaption(NULL);
		CString strAccount = pRecord->GetItem(3)->GetCaption(NULL);
		CString strRNo = pRecord->GetItem(7)->GetCaption(NULL);
		CString strName = pRecord->GetItem(8)->GetCaption(NULL);

		if(strBank.Find(strSearch) >= 0 ||
			strOwner.Find(strSearch) >= 0 ||
			strAccount.Find(strSearch) >= 0 ||
			strRNo.Find(strSearch) >= 0 ||
			strName.Find(strSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstReport.Populate();
}
