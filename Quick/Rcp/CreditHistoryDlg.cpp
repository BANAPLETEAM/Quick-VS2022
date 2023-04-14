
#include "stdafx.h"
#include "resource.h"
#include "RcpDlg.h"
#include "CreditHistoryDlg.h"

#define ID_SIZE_DOWN	100
#define ID_SIZE_UP		101

// CCreditHistoryDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCreditHistoryDlg, CMyDialog)
CCreditHistoryDlg::CCreditHistoryDlg(CWnd* pParent)
: CMyDialog(CCreditHistoryDlg::IDD, pParent)
{
	m_nOGNo = 0;
	m_nOCNo = 0;
	m_pwndParent = pParent;
	m_nRecordCount = 0;
}

CCreditHistoryDlg::~CCreditHistoryDlg()
{
	m_wndReport.SaveReportOrder("CCreditHistoryDlg", "m_List_q");

	DeleteAllItems();
}

void CCreditHistoryDlg::DeleteAllItems()
{
	m_nRecordCount = 0;
	m_wndReport.DeleteAllItems();
	m_wndReport.Populate();
}

void CCreditHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INFO_STATIC, m_stcInfo);
	DDX_Control(pDX, IDC_REPORT_LIST, m_wndReport);
	DDX_Control(pDX, IDC_CANCEL_BTN, m_btnCancel);
	DDX_Control(pDX, IDC_SEARCH_START_EDIT, m_edtSearchStart);
	DDX_Control(pDX, IDC_SEARCH_DEST_EDIT, m_edtSearchDest);
	DDX_Control(pDX, IDC_SEARCH_ETC_EDIT, m_edtSearchEtc);
	DDX_Control(pDX, IDC_SEARCH_MANAGER_EDIT, m_edtSearchManager);
}


BEGIN_MESSAGE_MAP(CCreditHistoryDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_EN_CHANGE(IDC_SEARCH_START_EDIT, OnEnChangeSearchStartEdit)
	ON_EN_CHANGE(IDC_SEARCH_DEST_EDIT, OnEnChangeSearchDestEdit)
	ON_EN_CHANGE(IDC_SEARCH_ETC_EDIT, OnEnChangeSearchEtcEdit)
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_SEARCH_MANAGER_EDIT, OnEnChangeSearchManagerEdit)
	ON_NOTIFY(XTP_NM_GRID_COLUMNORDERCHANGED, IDC_REPORT_LIST, OnReportColumnChangeChanged)
END_MESSAGE_MAP()


// CCreditHistoryDlg 메시지 처리기입니다.

void CCreditHistoryDlg::OnReportColumnChangeChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	m_wndReport.SaveReportOrder("CCreditHistoryDlg", "m_List_q");
}

BOOL CCreditHistoryDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_wndReport.InsertColumn(0, "ⓝ", LVCFMT_LEFT,  20);
	m_wndReport.InsertColumn(1, "오더번호", LVCFMT_LEFT,  70);
	m_wndReport.InsertColumn(2, "접수회사", LVCFMT_LEFT,  72);
	m_wndReport.InsertColumn(3, "날짜", LVCFMT_LEFT,  82);
	m_wndReport.InsertColumn(4, "출발동", LVCFMT_LEFT, 80);
	m_wndReport.InsertColumn(5, "도착동", LVCFMT_LEFT, 80);
	m_wndReport.InsertColumn(6, "부서", LVCFMT_LEFT,  80);
	m_wndReport.InsertColumn(7, "담당자", LVCFMT_LEFT, 60);
	m_wndReport.InsertColumn(8, "탁송", LVCFMT_LEFT,  45);
	m_wndReport.InsertColumn(9, "금액", LVCFMT_LEFT, 45);
	m_wndReport.InsertColumn(10, "정산시DC금액", LVCFMT_LEFT,  45);
	m_wndReport.InsertColumn(11, "입금", LVCFMT_LEFT, 50);
	m_wndReport.InsertColumn(12, "적요", LVCFMT_LEFT,  110);
	m_wndReport.Populate();

	RefreshList();

	m_edtSearchStart.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtSearchDest.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtSearchEtc.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtSearchManager.SetMyFont("맑은 고딕", 15, FW_BOLD);

	m_edtSearchStart.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "출발지");
	m_edtSearchDest.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "도착지");
	m_edtSearchEtc.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "적 요");
	m_edtSearchManager.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "담 당");

	m_wndReport.LoadReportOrder("CCreditHistoryDlg", "m_List_q");

	m_Magnetic.SetInfo(this, m_pwndParent, "CreditHistoryDlg");
	m_Magnetic.AttachTo();

	ShowWindow(SW_SHOW);
	OnSize(0xFF, 0, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCreditHistoryDlg::RefreshList()
{
	DeleteAllItems();
	m_wndReport.Populate();

	if(m_nOCNo < 1)
		return;
 
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_credit_order_for_customer");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nOGNo == 0 ? m_nOCNo : m_nOGNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nOGNo == 0 ? FALSE : TRUE);

	if(!pRs.Execute(&pCmd))
		return;

	long nTNo, nCompany, nOCNo, nPayType, nChargeSum, nChargeTrans, nTransferState, nChargeDisAfter;
	CString strSDong, strDDong, strEtc, strODepart, strOManager, strOName;
	COleDateTime dt1;

	m_nRecordCount = pRs.GetRecordCount();
	for(int i = 0; i < m_nRecordCount; i++)
	{
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nOCNo", nOCNo);
		pRs.GetFieldValue("nPayType", nPayType);
		pRs.GetFieldValue("nChargeSum", nChargeSum);
		pRs.GetFieldValue("nChargeTrans", nChargeTrans);
		pRs.GetFieldValue("nTransferState", nTransferState);
		pRs.GetFieldValue("sSDong", strSDong);
		pRs.GetFieldValue("sDDong", strDDong);
		pRs.GetFieldValue("dt1", dt1);
		pRs.GetFieldValue("nChargeDisAfter", nChargeDisAfter);
		pRs.GetFieldValue("sEtc", strEtc);
		pRs.GetFieldValue("sODepart", strODepart);
		pRs.GetFieldValue("sOManager", strOManager);
		pRs.GetFieldValue("sOName", strOName);

// 		m_wndReport.InsertColumn(0, "ⓝ", LVCFMT_LEFT,  20);
// 		m_wndReport.InsertColumn(1, "오더번호", LVCFMT_LEFT,  72);
// 		m_wndReport.InsertColumn(2, "접수회사", LVCFMT_LEFT,  72);
// 		m_wndReport.InsertColumn(3, "날짜", LVCFMT_LEFT,  82);
// 		m_wndReport.InsertColumn(4, "출발동", LVCFMT_LEFT, 80);
// 		m_wndReport.InsertColumn(5, "도착동", LVCFMT_LEFT, 80);
// 		m_wndReport.InsertColumn(6, "부서", LVCFMT_LEFT,  110);
// 		m_wndReport.InsertColumn(7, "담당자", LVCFMT_LEFT, 90);
// 		m_wndReport.InsertColumn(8, "탁송", LVCFMT_LEFT,  70);
// 		m_wndReport.InsertColumn(9, "금액", LVCFMT_LEFT, 45);
// 		m_wndReport.InsertColumn(10, "정산시DC금액", LVCFMT_LEFT,  38);
// 		m_wndReport.InsertColumn(11, "입금", LVCFMT_LEFT, 80);
// 		m_wndReport.InsertColumn(12, "적요", LVCFMT_LEFT,  110);

		m_wndReport.InsertItem(i, GetStringFromLong(i + 1), FALSE); 
		m_wndReport.SetItemText(i, 1, GetStringFromLong(nTNo));
		m_wndReport.SetItemText(i, 2, m_ci.GetBranchName(nCompany));
		m_wndReport.SetItemText(i, 3, dt1.Format("%m-%d %H:%M"));
		m_wndReport.SetItemText(i, 4, strSDong);
		m_wndReport.SetItemText(i, 5, strDDong);
		m_wndReport.SetItemText(i, 6, strODepart);
		m_wndReport.SetItemText(i, 7, strOManager);
		m_wndReport.SetItemText(i, 8, ::GetMyNumberFormat(nChargeTrans));
		m_wndReport.SetItemText(i, 9, ::GetMyNumberFormat(nChargeSum));
		m_wndReport.SetItemText(i, 10, ::GetMyNumberFormat(nChargeDisAfter == 0 ? nChargeSum : nChargeDisAfter));
		m_wndReport.SetItemText(i, 11, ::GetPayTypeFromLong(nPayType));
		m_wndReport.SetItemText(i, 12, strEtc);

		pRs.MoveNext();
	}

	pRs.Close();
	m_wndReport.Populate();
	m_stcInfo.SetWindowText(CString("의뢰자 - ") + strOName);

	ListFilter();
}

void CCreditHistoryDlg::OnBnClickedCancelBtn()
{
	this->ShowWindow(SW_HIDE);
}

void CCreditHistoryDlg::OnEnChangeSearchStartEdit()
{
	ListFilter();
}

void CCreditHistoryDlg::OnEnChangeSearchDestEdit()
{
	ListFilter();
}

void CCreditHistoryDlg::OnEnChangeSearchEtcEdit()
{
	ListFilter();
}

void CCreditHistoryDlg::ListFilter()
{ 
	CString strSearchStart; m_edtSearchStart.GetWindowText(strSearchStart);
	CString strSearchDest; m_edtSearchDest.GetWindowText(strSearchDest);
	CString strSearchEtc; m_edtSearchEtc.GetWindowText(strSearchEtc);
	CString strSearchManager; m_edtSearchManager.GetWindowText(strSearchManager);

	CXTPGridColumn *pColumn = NULL;
	CXTPGridRecords *pRecords = m_wndReport.GetRecords();
	CString sStartGugun = "", sDestGugun = "";
	for(int i=0; i<pRecords->GetCount(); i++)
	{
	    CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString strStart = pRecord->GetItem(4)->GetCaption(pColumn);
		CString strDest = pRecord->GetItem(5)->GetCaption(pColumn);
		CString strEtc = pRecord->GetItem(12)->GetCaption(pColumn);
		CString strManager = pRecord->GetItem(7)->GetCaption(pColumn);

		BOOL bVisible = TRUE;

		if((strStart.Find(strSearchStart) < 0) && (strSearchStart != "") )
			bVisible = FALSE;

		if((strDest.Find(strSearchDest) < 0) && (strSearchDest != "") )
			bVisible = FALSE;

		if((strEtc.Find(strSearchEtc) < 0) && (strSearchEtc != ""))
			bVisible = FALSE;

		if((strManager.Find(strSearchManager) < 0) && (strSearchManager != ""))
			bVisible = FALSE;

		pRecord->SetVisible(bVisible);
	}

	m_wndReport.Populate();
}


BOOL CCreditHistoryDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->hwnd == this->GetSafeHwnd())
	{

	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CCreditHistoryDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CMyDialog::OnWindowPosChanging(lpwndpos);
	m_Magnetic.PosChanging(lpwndpos);
}

void CCreditHistoryDlg::OnSize(UINT nType, int cx, int cy)
{  
	if(nType != 0xFF)
		CMyDialog::OnSize(nType, cx, cy);

	if(IsWindow(m_wndReport.GetSafeHwnd()))
	{
		CRect rcDlg, rcList;
		GetClientRect(rcDlg);
		m_wndReport.GetWindowRect(rcList);
		ScreenToClient(rcList);

		rcList.right = rcDlg.right - 1;
		rcList.bottom = rcDlg.bottom - 1; 

		m_wndReport.MoveWindow(rcList);
	}
}

void CCreditHistoryDlg::OnEnChangeSearchManagerEdit()
{
	ListFilter();
}

void CCreditHistoryDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CMyDialog::OnLButtonDown(nFlags, point);
}
