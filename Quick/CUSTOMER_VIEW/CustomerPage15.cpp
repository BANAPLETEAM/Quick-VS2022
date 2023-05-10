// CustomerPage15.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "CustomerPage15.h"
#include "SumCNoNewDlg.h"
#include <math.h>
#include "RcpPlaceInfo.h"
#include "CustomerDlg.h"


// CCustomerPage15

IMPLEMENT_DYNCREATE(CCustomerPage15, CMyFormView)

CCustomerPage15::CCustomerPage15()
: CMyFormView(CCustomerPage15::IDD)
{
	m_pCustomerDlg = NULL;
	m_bDragMode = FALSE;
}

CCustomerPage15::~CCustomerPage15()
{
	if(!m_pCustomerDlg)
	{
		delete m_pCustomerDlg;
		m_pCustomerDlg = NULL;
	}
}

void CCustomerPage15::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_CUSTOMER_LIST, m_lstCustomer);
}

BEGIN_MESSAGE_MAP(CCustomerPage15, CMyFormView)

	ON_NOTIFY(NM_DBLCLK, IDC_CUSTOMER_LIST, OnCustomerReportItemDblClick)
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CCustomerPage15::OnBnClickedSearchBtn)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CCustomerPage15::OnEnChangeSearchEdit)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_CUSTOMER_LIST, OnReportBeginDrag)
	ON_WM_MOUSEMOVE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
END_MESSAGE_MAP()

void CCustomerPage15::OnCustomerReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridRecord *pRecord = m_lstCustomer.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	if(m_pCustomerDlg == NULL)
	{
		m_pCustomerDlg = new CCustomerDlg(this);
		m_pCustomerDlg->Create(CCustomerDlg::IDD, this);
	}

	m_pCustomerDlg->m_strKeyword = ::GetStringFromLong(m_lstCustomer.GetItemLong(pRecord));
	m_pCustomerDlg->m_nCNo = m_lstCustomer.GetItemLong(pRecord);
	m_pCustomerDlg->m_nSearchType = ST_CNO;
	m_pCustomerDlg->m_bGroup = FALSE;	
	m_pCustomerDlg->m_nTempCNo =0;
	m_pCustomerDlg->InitDialog();
	m_pCustomerDlg->CenterWindow(AfxGetMainWnd());
	m_pCustomerDlg->ShowWindow(SW_SHOW);

	//m_pPlace->SearchCustomer(m_lstCustomer.GetItemLong(pRecord), ST_CNO);
}

void CCustomerPage15::OnReportBeginDrag(NMHDR * pNotifyStruct, LRESULT * result)
{
	if(m_bClicking)
	{
		m_bDragMode = TRUE;
		m_ptDrag.x = -1;
		m_ptDrag.y = -1;
		SetCursor( m_hcMoveHold );
		SetCapture();

	}

}
// CCustomerPage15 진단입니다.

#ifdef _DEBUG
void CCustomerPage15::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCustomerPage15::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCustomerPage15 메시지 처리기입니다.

void CCustomerPage15::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_CUSTOMER_LIST, sizingRightBottom);

	m_hcArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_hcNo = AfxGetApp()->LoadStandardCursor(IDC_NO);
	m_hcMoveHold = AfxGetApp()->LoadCursor(IDC_MOVEHOLD);

	m_lstCustomer.InsertColumn(0, "고객번호", LVCFMT_CENTER, 50);
	m_lstCustomer.InsertColumn(1, "고객명", LVCFMT_LEFT, 110);
	m_lstCustomer.InsertColumn(2, "전화번호", LVCFMT_LEFT, 100);
	m_lstCustomer.InsertColumn(3, "중복건수", LVCFMT_LEFT, 60);
	m_lstCustomer.InsertColumn(4, "등록일", LVCFMT_LEFT, 110);
	m_lstCustomer.InsertColumn(5, "마지막사용일", LVCFMT_LEFT, 110);
	m_lstCustomer.InsertColumn(6, "주소", LVCFMT_LEFT, 300);
	m_lstCustomer.Populate();


	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void CCustomerPage15::OnBnClickedSearchBtn()
{
	RefreshList();
}


void CCustomerPage15::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstCustomer.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CCustomerPage15::OnViewExcel()
{
	if(!POWER_CHECK(6900, "고객 엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nCustomerTable, 212, m_lstCustomer.GetItemCount());  
	CMyExcel::ToExcel(&m_lstCustomer);
}

void CCustomerPage15::RefreshList()
{
	CMyFormView::RefreshList();

	m_lstCustomer.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_dup_customer");
	cmd.AddParameter(::GetCurBranchInfo()->nCompanyCode);

	if(!rs.Execute(&cmd))
		return;

	long nCNo, nID, nDupCount;
	CString strCompany, strTel, strLocation;
	COleDateTime dtRegister, dtLastUse;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nCNo", nCNo);
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("nDupCount", nDupCount);
		rs.GetFieldValue("sCompany", strCompany);
		rs.GetFieldValue("sTel", strTel);
		rs.GetFieldValue("sLocation", strLocation);
		rs.GetFieldValue("dtRegister", dtRegister);
		rs.GetFieldValue("dtLastUse", dtLastUse);

		m_lstCustomer.InsertItem(i, ::GetStringFromLong(nID));
		m_lstCustomer.SetItemText(i, 1, strCompany);
		m_lstCustomer.SetItemText(i, 2, ::GetDashPhoneNumber(strTel));
		m_lstCustomer.SetItemText(i, 3, ::GetStringFromLong(nDupCount));
		m_lstCustomer.SetItemText(i, 4, dtRegister.m_status != 2 ? dtRegister.Format("%Y-%m-%d %H:%M") : "");
		m_lstCustomer.SetItemText(i, 5, dtLastUse.m_status != 2 ? dtLastUse.Format("%Y-%m-%d %H:%M") : "");
		m_lstCustomer.SetItemText(i, 6, strLocation);
		m_lstCustomer.SetItemLong(i, nCNo);

		rs.MoveNext();
	}

	OnEnChangeSearchEdit();
}

void CCustomerPage15::OnEnChangeSearchEdit()
{
	CString strSearch;
	m_edtSearch.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstCustomer.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strName = pRecord->GetItem(1)->GetCaption(NULL);
		CString strPhone = pRecord->GetItem(2)->GetCaption(NULL);
		strPhone = ::GetNoneDashNumber(strPhone);

		if(strName.Find(strSearch) >= 0 ||
			strPhone.Find(strSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstCustomer.Populate();
}

BOOL CCustomerPage15::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_LBUTTONUP )
	{
		if(m_bDragMode) 
		{
			//CRect rect;
			//m_List.GetWindowRect(&rect);

			CPoint pt;
			::GetCursorPos(&pt);

			//if(!SumCustomer(pt))
			//	MessageBox("고객이 선택되지 않았습니다", "확인", MB_ICONINFORMATION);
			long nStartPoint , nNowPoint = pt.y, nDistance = 0;
			nStartPoint = (m_DragStartPoint.y  < 0) ? m_DragStartPoint.y * -1 : m_DragStartPoint.y;
			nNowPoint = (nNowPoint < 0 ) ? nNowPoint * -1 : nNowPoint;
			nDistance = nStartPoint - nNowPoint;
			nDistance = nDistance < 0 ? nDistance * -1 : nDistance;

			if(nDistance > 8 && m_DragStartPoint.x > 0 && m_DragStartPoint.y > 0)
			{
				SetCursor(m_hcArrow); 
				::ReleaseCapture(); 
				SumCustomer(pt);
			}
			else
			{
				SetCursor(m_hcArrow);
				m_bDragMode = FALSE; //순서에 주의 할것 - 참고 OnLButtonUp에서도 m_bRefreshOK = TRUE를 설정한다.
				m_bClicking = FALSE;
				::ReleaseCapture();
				return FALSE;
			}
			m_DragStartPoint.x = m_DragStartPoint.y = 0;


			return TRUE;
		}
		else
		{
			m_bClicking = FALSE; 
			m_bDragMode = FALSE;

			return CMyFormView::PreTranslateMessage(pMsg); 
		}
	}

	if(pMsg->message == WM_LBUTTONDOWN && pMsg->hwnd == m_lstCustomer.GetSafeHwnd())
	{
		m_DragStartPoint = pMsg->pt;
		m_bClicking = TRUE;
	}

	return CMyFormView::PreTranslateMessage(pMsg);
}

void CCustomerPage15::OnMouseMove(UINT nFlags, CPoint point)
{
	if(TRUE == m_bDragMode)
	{
		SetCursor( m_hcMoveHold );

		if(m_ptDrag.x == -1)
		{
			m_ptDrag.x = point.x;
			m_ptDrag.y = point.y;
		}

		double lDistance = (m_ptDrag.x-point.x)*(m_ptDrag.x-point.x)  + (m_ptDrag.y-point.y)*(m_ptDrag.y-point.y);

		if( sqrt( lDistance  ) > 250.0)
		{
			SetCursor(m_hcArrow);
			m_bDragMode = FALSE; //순서에 주의 할것 - 참고 OnLButtonUp에서도 m_bRefreshOK = TRUE를 설정한다.
			m_bClicking = FALSE;
			::ReleaseCapture();
		}
	}

	CMyFormView::OnMouseMove(nFlags, point);
}


BOOL CCustomerPage15::SumCustomer(CPoint pt)
{
	if (m_bDragMode) // In Drag&Drop mode ?
	{
		m_bDragMode = FALSE;
		m_bClicking = FALSE;

		//UINT uFlags;
		m_lstCustomer.ScreenToClient(&pt);
		//int nHoverItem = m_List.HitTest(pt, &uFlags); 
		CXTPGridRow *pRow = m_lstCustomer.HitTest(pt);

		if(pRow == NULL)
		{
			MessageBox("고객이 선택되지 않았습니다", "확인", MB_ICONINFORMATION);			
			return FALSE;
		}

		CXTPGridRecord *pRecordDel = m_lstCustomer.GetFirstSelectedRecord();
		CXTPGridRecord *pRecordSum = pRow->GetRecord();

		long nDelCNo = m_lstCustomer.GetItemLong(pRecordDel);
		long nSumCNo = m_lstCustomer.GetItemLong(pRecordSum);

		if(nDelCNo == nSumCNo)
		{
			MessageBox("합치려는 고객이 같습니다", "확인", MB_ICONINFORMATION);
			return FALSE;
		}

		CSumCNoNewDlg dlg;
		dlg.m_nDelCNo = nDelCNo;
		dlg.m_nSumCNo = nSumCNo;

		if(dlg.DoModal() != IDOK) 
			return FALSE;

		//CWaitCursor wait;		
		CString strDeleteEtc = "고객통합[중복고객탭] 삭제";
		CMkCommand pCmd(m_pMkDb, "Integrated_customer_alone_3");
		pCmd.AddParameter(::GetCurBranchInfo()->nCompanyCode);		//nCompany
		pCmd.AddParameter(nDelCNo);
		pCmd.AddParameter(nSumCNo);
		pCmd.AddParameter(m_ui.nWNo);
		pCmd.AddParameter(m_ui.nCompany);						
		pCmd.AddParameter(strDeleteEtc);

		pCmd.Execute();
		RefreshList();
		return TRUE;
	}

	return FALSE;
}