#include "StdAfx.h"
#include "Quick.h"
#include "StatTelserverRouteLog.h"
#include "TelserverDIDRouteDlg.h"
#include "RcpView.h"
#include "RcpPageCTIForm.h"

IMPLEMENT_DYNCREATE(CStatTelserverRouteLog, CMyFormView)

CStatTelserverRouteLog::CStatTelserverRouteLog()
: CMyFormView(CStatTelserverRouteLog::IDD)
{

}

CStatTelserverRouteLog::~CStatTelserverRouteLog()
{
}

void CStatTelserverRouteLog::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFromCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_LIST_REPORT, m_lstReport);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}

BEGIN_MESSAGE_MAP(CStatTelserverRouteLog, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_WM_CONTEXTMENU()
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
	ON_BN_CLICKED(IDC_DIDROUTE_SETTING_BTN, OnBnClickedDIDRoute)
	
END_MESSAGE_MAP()


// CStatTelserverRouteLog 진단입니다.

#ifdef _DEBUG
void CStatTelserverRouteLog::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStatTelserverRouteLog::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStatForm9 메시지 처리기입니다.

void CStatTelserverRouteLog::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_LIST_REPORT, sizingRightBottom);

	m_DateBtn.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_DateBtn.OnMenuWeek();

	m_lstReport.InsertColumn(0, "일자", LVCFMT_CENTER, 100);
	m_lstReport.InsertColumn(1, "수신DID", LVCFMT_RIGHT, 90);
	m_lstReport.InsertColumn(2, "지사", LVCFMT_RIGHT, 90);
	m_lstReport.InsertColumn(3, "수신번호", LVCFMT_RIGHT, 90);
	m_lstReport.InsertColumn(4, "전환번호", LVCFMT_RIGHT, 90);
	m_lstReport.InsertColumn(5, "타입", LVCFMT_RIGHT, 70);
	m_lstReport.Populate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void CStatTelserverRouteLog::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CStatTelserverRouteLog::RefreshList()
{
	UpdateData(TRUE);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_New_Telserver_Stat_Route");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	//cmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);

	if(!rs.Execute(&cmd))
		return;

	m_lstReport.DeleteAllItems();

	COleDateTime dtDate;
	CString strDID, strPhoneNumber, strToLine;
	int nType = 0;

	for(int nRecordCount = 0 ; nRecordCount < rs.GetRecordCount() ; nRecordCount++)
	{
		rs.GetFieldValue("dtLastedit", dtDate);
		rs.GetFieldValue("sDID", strDID);
		rs.GetFieldValue("sPhoneNumber", strPhoneNumber);
		rs.GetFieldValue("sToLine", strToLine);
		rs.GetFieldValue("nType", nType);

		m_lstReport.InsertItem(nRecordCount, dtDate.Format("%m-%d %H:%M:%S"));
		m_lstReport.SetItemText(nRecordCount, 1, "070" + strDID);
		CBranchInfo *pBi2 = LU->SearchLineGroup((LPSTR)(LPCTSTR)strDID);
		if(pBi2)
		{
			CBranchInfo *pBi = m_ba.GetCount() > 1 ? pBi2 : 0;
			if(pBi)
				m_lstReport.SetItemText(nRecordCount, 2, pBi->strBranchName);
		}
		m_lstReport.SetItemText(nRecordCount, 3, strPhoneNumber);
		m_lstReport.SetItemText(nRecordCount, 4, strToLine);
		m_lstReport.SetItemText(nRecordCount, 5, nType == 1 ? "콜라우팅" : "DID착신");

		rs.MoveNext();
	}

	rs.Close();
	m_lstReport.Populate();
}


void CStatTelserverRouteLog::OnEnChangeSearchEdit()
{
	m_edtSearch.GetWindowText(m_strSearchNumber);
	BOOL bVisible = TRUE;

	if(m_strSearchNumber.GetLength() >= 3)
		bVisible = FALSE;
	else
	{
		bVisible = TRUE;
		m_strSearchNumber = "";
	}

	SearchRecord(bVisible);
}

void CStatTelserverRouteLog::SearchRecord(BOOL bVisible)
{
	int nCount = m_lstReport.GetRecords()->GetCount();
	CXTPGridRecord* pRecord;
	CString strDID, strTellNumber;
	int nBound = 0;
	for(int i = 0 ; i < nCount; i++)
	{
		pRecord = m_lstReport.GetRecords()->GetAt(i);
		if(pRecord != NULL)
		{
			BOOL bShow = TRUE;

			strDID = m_lstReport.GetItemText(pRecord, 1);
			strTellNumber = m_lstReport.GetItemText(pRecord, 3);

			if(strDID.Find(m_strSearchNumber) < 0 && strTellNumber.Find(m_strSearchNumber) < 0)
				bShow = FALSE;

			pRecord->SetVisible(bShow);
		}
	}

	m_lstReport.Populate();
}

void CStatTelserverRouteLog::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point))
		return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CStatTelserverRouteLog::OnBnClickedDIDRoute()
{
	if(!(LU->m_pRcpView))
	{
		MessageBox("접수창 이동후 텔서버에 접속시켜주세요.", "확인", MB_ICONINFORMATION);
		return;
	}
	else if(!(LU->m_pRcpView->m_pCTIForm))
	{
		MessageBox("접수창 이동후 텔서버에 접속시켜주세요.", "확인", MB_ICONINFORMATION);
		return;
	}

	CTelserverDIDRouteDlg dlg;
	dlg.DoModal();
}