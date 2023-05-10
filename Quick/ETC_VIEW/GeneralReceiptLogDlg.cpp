// BillDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "GeneralReceiptLogDlg.h"
#include "GeneralRecepitDlg.h"


// CGeneralReceiptLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGeneralReceiptLogDlg, CMyDialog)
CGeneralReceiptLogDlg::CGeneralReceiptLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CGeneralReceiptLogDlg::IDD, pParent)
{
}

CGeneralReceiptLogDlg::~CGeneralReceiptLogDlg()
{
}

void CGeneralReceiptLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_GENERAL, m_lstReport);
}


BEGIN_MESSAGE_MAP(CGeneralReceiptLogDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, OnBnClickedRefresh)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_GENERAL, OnNMDblclkList)
	ON_WM_SIZE()
END_MESSAGE_MAP()


void CGeneralReceiptLogDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(!pRecord)
		return;


	CGeneralReceiptDlg dlg;
	dlg.m_nID = m_lstReport.GetItemLong(pRecord);
	dlg.DoModal();

}

// CGeneralReceiptLogDlg 메시지 처리기입니다.

BOOL CGeneralReceiptLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	CenterWindow();

	m_lstReport.InsertColumn(0, "신청일", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(1, "신청인", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(2, "업체명", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(3, "대표자명", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(4, "의뢰자명", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(5, "배송주소", LVCFMT_LEFT, 200);
	m_lstReport.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CGeneralReceiptLogDlg::OnBnClickedRefresh()
{
	RefreshList();
}

void CGeneralReceiptLogDlg::RefreshList()
{
	m_lstReport.DeleteAllItems(); 

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_general_receipt_subscript_company");
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);

	if(!rs.Execute(&cmd))
		return;

	long nID;
	CString strCompanyName, strWName, strCompanyOwner, strOName, strOAddress;
	COleDateTime dtInsert;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("sWName", strWName);
		rs.GetFieldValue("sCompanyName", strCompanyName);
		rs.GetFieldValue("sCompanyOwner", strCompanyOwner);
		rs.GetFieldValue("sOName", strOName);
		rs.GetFieldValue("sOAddress", strOAddress);
		rs.GetFieldValue("dtInsert", dtInsert);
		
		m_lstReport.InsertItem(i, dtInsert.Format("%Y-%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 1, strWName);
		m_lstReport.SetItemText(i, 2, strCompanyName);
		m_lstReport.SetItemText(i, 3, strCompanyOwner);
		m_lstReport.SetItemText(i, 4, strOName);
		m_lstReport.SetItemText(i, 5, strOAddress);
		m_lstReport.SetItemLong(i, nID);

		rs.MoveNext();
	}

	m_lstReport.Populate();
}

void CGeneralReceiptLogDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);


	if(IsWindow(m_lstReport.GetSafeHwnd()))
	{
		CRect rcDlg, rcList;
		GetClientRect(rcDlg);
		m_lstReport.GetWindowRect(rcList);
		ScreenToClient(rcList);

		rcList.right = rcDlg.right - 1;
		rcList.bottom = rcDlg.bottom - 1; 

		m_lstReport.MoveWindow(rcList);
	}
}
