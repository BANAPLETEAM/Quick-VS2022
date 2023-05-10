// BillDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "BillDlg.h"
#include "MainFrm.h"


// CBillDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CBillDlg, CMyDialog)
CBillDlg::CBillDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CBillDlg::IDD, pParent)
{
	m_dtDate = COleDateTime::GetCurrentTime();
}

CBillDlg::~CBillDlg()
{
}

void CBillDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BILL_LIST, m_BillList);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DateDT);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtDate);
}


BEGIN_MESSAGE_MAP(CBillDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, OnDtnDatetimechangeDatetimepicker1)
	ON_NOTIFY(NM_DBLCLK, IDC_BILL_LIST, OnNMDblclkBillList)
END_MESSAGE_MAP()


// CBillDlg 메시지 처리기입니다.

BOOL CBillDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	GetDesktopWindow()->CenterWindow();

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BRANCH_ARRAY);
	m_imgList.Create(16,18,ILC_COLOR8,1,1); 
	m_imgList.Add(&bitmap,RGB(255,0,255));

	m_BillList.SetImageList(&m_imgList,LVSIL_SMALL); 
	m_BillList.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_BillList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
				LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);
	m_BillList.InsertColumn(0,"No.",LVCFMT_LEFT, 50);
	m_BillList.InsertColumn(1,"구분",LVCFMT_LEFT, 160);
	m_BillList.InsertColumn(2,"금액",LVCFMT_RIGHT, 80);
	m_BillList.InsertColumn(3,"비고",LVCFMT_LEFT, 240);

	m_DateDT.SetFormat("yyyy년 MM월");
	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CBillDlg::RefreshList()
{
	char buffer[20];
	int nMonth = atol(m_dtDate.Format("%Y%m"));
	m_BillList.DeleteAllItems();
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_bill_data");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nMonth);
	if(pRs.Execute(&pCmd)) {
		long nCompany, nMonth, nType;
		CString strDescribe;
		long nCharge;
		CString strEtc;
		int nItem = 0;

		while(!pRs.IsEOF())	{
			pRs.GetFieldValue("nCompany", nCompany);
			pRs.GetFieldValue("nMonth", nMonth);
			pRs.GetFieldValue("nType", nType);
			pRs.GetFieldValue("sDescribe", strDescribe);
			pRs.GetFieldValue("nCharge", nCharge);
			pRs.GetFieldValue("sEtc", strEtc); 
	
			if(nType == 90) {
				m_BillList.InsertItem(nItem, "---");
				m_BillList.SetItemText(nItem, 1, "-----------------------"); 
				m_BillList.SetItemText(nItem, 2, "----------"); 
				m_BillList.SetItemText(nItem++, 3, "---------------------------"); 
				m_BillList.InsertItem(nItem, "+");
			}
			else {
				m_BillList.InsertItem(nItem, ltoa(nItem + 1, buffer, 10));
			}
			m_BillList.SetItemData(nItem, (DWORD)nType);
			m_BillList.SetItemText(nItem, 1, strDescribe); 
			m_BillList.SetItemText(nItem, 2, GetMyNumberFormat(ltoa(nCharge, buffer, 10))); 
			m_BillList.SetItemText(nItem++, 3, strEtc); 
			pRs.MoveNext();
		}

		m_BillList.InsertItem(nItem, "*");
		m_BillList.SetItemText(nItem, 1, "입금계좌"); 
		m_BillList.SetItemText(nItem, 2, "기업은행"); 
		m_BillList.SetItemText(nItem++, 3, "633-000310-04-057 바나플유한회사"); 
		//m_BillList.SetItemText(nItem++, 3, "861901-04-001568 송민기(로지소프트)"); 
	}
}

void CBillDlg::OnBnClickedOk()
{
	OnOK();
}

void CBillDlg::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	UpdateData(TRUE);
	RefreshList();
	*pResult = 0;
}


void CBillDlg::OnNMDblclkBillList(NMHDR *pNMHDR, LRESULT *pResult)
{
/* ###
	int nItem;
	if((nItem = m_BillList.GetNextItem(-1, LVNI_SELECTED)) >= 0) 
	{
		int nType = m_BillList.GetItemData(nItem);
		if(nType == 10) {
			CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
			CQuickPropSheet *pSheet = (CQuickPropSheet*)pFrame->m_pStaffView->m_pSheet; 
			pFrame->SwitchView(STAFF_VIEW);
			pSheet->SetActivePage(1);
		}
		else if(nType == 50) {
		
			CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
			CQuickPropSheet *pSheet = (CQuickPropSheet*)pFrame->m_pReportView->m_pSheet;
			pFrame->SwitchView(REPORT_VIEW);
			pSheet->SetActivePage(8);
		}
	}
*/
	*pResult = 0;
}






