// StaffForm24.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "StaffForm27.h"
#include "EmployMentInsuranceDlg.h"

// CStaffForm27

IMPLEMENT_DYNCREATE(CStaffForm27, CMyFormView)

CStaffForm27::CStaffForm27()
	: CMyFormView(CStaffForm27::IDD)
{

}

CStaffForm27::~CStaffForm27()
{
}

void CStaffForm27::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_lstReport);
}

BEGIN_MESSAGE_MAP(CStaffForm27, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CStaffForm27::OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT, OnNMDblClickListReport)
	ON_NOTIFY(NM_CLICK, IDC_REPORT, OnNMClickListReport)
	ON_BN_CLICKED(IDC_SEND_SMS_BTN, &CStaffForm27::OnBnClickedSendSmsBtn)
END_MESSAGE_MAP()


// CStaffForm27 진단입니다.

#ifdef _DEBUG
void CStaffForm27::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStaffForm27::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CStaffForm27::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();
	SetResize(IDC_REPORT, sizingRightBottom);
	
	m_lstReport.InsertColumn(0, "순번", LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(1, "지사명", LVCFMT_LEFT, 150);
	m_lstReport.InsertColumn(2, "대표번호", LVCFMT_LEFT, 120);
	m_lstReport.InsertColumn(3, "사업자번호(주민번호)", LVCFMT_LEFT, 160);
	m_lstReport.InsertColumn(4, "대표자주민번호", LVCFMT_LEFT, 160);
	m_lstReport.InsertColumn(5, "대표자", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(6, "전화번호", LVCFMT_LEFT, 110);
	m_lstReport.InsertColumn(7, "상호명", LVCFMT_LEFT, 110);
	m_lstReport.InsertColumn(8, "사업장주소", LVCFMT_LEFT, 250);
	m_lstReport.InsertColumn(9, "첨부파일", LVCFMT_CENTER, 80);
	m_lstReport.SetOrderIndexCol(0);
	m_lstReport.Populate();

	OnBnClickedRefreshBtn();
}

void CStaffForm27::OnBnClickedRefreshBtn()
{
	m_lstReport.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_company_info_empins_biz_no_branch_1");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	
	int col_index = 0;

	if(rs.Execute(&cmd)) {
		while (!rs.IsEOF()) {
			long nCompany;
			CString strBizNo, strBizName, strOwnerSSN, stBizOwner, strBizAddress, strTel, strImageUrl;

			rs.GetFieldValue("nCompany", nCompany);
			rs.GetFieldValue("sBizNo", strBizNo);
			rs.GetFieldValue("sBizName", strBizName);
			rs.GetFieldValue("sBizOwner", stBizOwner);
			rs.GetFieldValue("sOwnerSSN", strOwnerSSN);
			rs.GetFieldValue("sBizAddress", strBizAddress);
			rs.GetFieldValue("sTel", strTel);
			rs.GetFieldValue("sImageUrl", strImageUrl);

			if (strOwnerSSN.GetLength() == 13) {
				strOwnerSSN = strOwnerSSN.Left(6) + "-" + strOwnerSSN.Right(7);
			}

			m_lstReport.InsertItem(col_index, "");
			m_lstReport.SetItemText(col_index, 1, m_ci.GetBranchName(nCompany));
			m_lstReport.SetItemText(col_index, 2, m_ci.GetPhone(nCompany));
			m_lstReport.SetItemText(col_index, 3, strBizNo);
			m_lstReport.SetItemText(col_index, 4, strOwnerSSN);
			m_lstReport.SetItemText(col_index, 5, stBizOwner);
			m_lstReport.SetItemText(col_index, 6, strTel);
			m_lstReport.SetItemText(col_index, 7, strBizName);
			m_lstReport.SetItemText(col_index, 8, strBizAddress);
			m_lstReport.SetItemText(col_index, 9, strImageUrl.IsEmpty() ? "없음" : "보기");

			if(!strImageUrl.IsEmpty())
				m_lstReport.ChangeItemTextColor(col_index, 8, RGB(0, 0, 255));

			m_lstReport.SetItemLong(col_index, nCompany);
			m_lstReport.SetItemDataText(col_index++, strImageUrl);

			rs.MoveNext();
		}
	}	

	m_lstReport.Populate();
}

void CStaffForm27::OnNMDblClickListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedSendSmsBtn();
}

void CStaffForm27::OnNMClickListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM* pNMListView = (XTP_NM_REPORTRECORDITEM*)pNMHDR;

	if(pNMListView->pRow == NULL)
		return;

	if(pNMListView->pColumn->GetItemIndex() == 8) {
		CXTPGridRecord *record = m_lstReport.GetFirstSelectedRecord();

		if(record) {
			CString image = m_lstReport.GetItemDataText(record);

			if(!image.IsEmpty())
				ShellExecute(NULL, "open", "msedge.exe", image, "", SW_SHOW); 
		}
	}
}

void CStaffForm27::OnBnClickedSendSmsBtn()
{
	CXTPGridRecord *record = m_lstReport.GetFirstSelectedRecord();

	if(record) {
		CEmployMentInsuranceDlg dlg;
		dlg.company_code_ = m_lstReport.GetItemLong(record);
		
		if(dlg.DoModal() == IDOK)
			OnBnClickedRefreshBtn();			
	}
}
