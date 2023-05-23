#include "stdafx.h"
#include "resource.h"
#include "RcpPageRecordFileForm.h"
#include "RcpView.h"

// CRcpPageMemoForm

IMPLEMENT_DYNCREATE(CRcpPageRecordFileForm, CMyFormView)

CRcpPageRecordFileForm::CRcpPageRecordFileForm()
: CMyFormView(CRcpPageRecordFileForm::IDD)
{
	//m_dtLast = EI()->dtTodayBound;
	COleDateTime dtDate = COleDateTime::GetCurrentTime();
	m_dtLast.SetDateTime(dtDate.GetYear(), dtDate.GetMonth(), dtDate.GetDay(), 7, 0, 0);
	m_bTodayRefresh = TRUE;
}

CRcpPageRecordFileForm::~CRcpPageRecordFileForm()
{
}

void CRcpPageRecordFileForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_List);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_dtpFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_dtpTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_LIST_TYPE_COMBO, m_cmbBoundType);
	DDX_Control(pDX, IDC_ORDER_CHECK, m_chkOrderCheck);
}

BEGIN_MESSAGE_MAP(CRcpPageRecordFileForm, CMyFormView)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_FROM, OnDtnDatetimechangeDatetimepicker)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_TO, OnDtnDatetimechangeDatetimepicker)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefresh)
	ON_BN_CLICKED(IDC_REFRESH_TODAY_BTN, OnBnClickedRefreshToday)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_LIST, OnReportItemClick)
	ON_CBN_SELCHANGE(IDC_LIST_TYPE_COMBO, OnCbnSelchangeBoundType)
	ON_BN_CLICKED(IDC_ORDER_CHECK, OnBnClickedOrderCheck)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CRcpPageMemoForm 진단입니다.

#ifdef _DEBUG
void CRcpPageRecordFileForm::AssertValid() const
{
	CFormView::AssertValid();
}

void CRcpPageRecordFileForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CRcpPageMemoForm 메시지 처리기입니다.

void CRcpPageRecordFileForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_btnDate.InitDateButton(&m_dtpFrom, &m_dtpTo);
	m_btnDate.OnMenuYesterday();

	CXTPGridColumn *pCol0 = m_List.AddColumn(new CXTPGridColumn(0, "일자", 100, TRUE));
	CXTPGridColumn *pCol1 = m_List.AddColumn(new CXTPGridColumn(1, "시간", 70, TRUE));
	CXTPGridColumn *pCol2 = m_List.AddColumn(new CXTPGridColumn(2, "지사", 100, TRUE));
	CXTPGridColumn *pCol3 = m_List.AddColumn(new CXTPGridColumn(3, "오더번호", 100, TRUE));
	CXTPGridColumn *pCol4 = m_List.AddColumn(new CXTPGridColumn(4, "내선번호", 70, TRUE));
	CXTPGridColumn *pCol5 = m_List.AddColumn(new CXTPGridColumn(5, "직원이름", 70, TRUE));
	CXTPGridColumn *pCol6 = m_List.AddColumn(new CXTPGridColumn(6, "전화번호", 100, TRUE));
	CXTPGridColumn *pCol7 = m_List.AddColumn(new CXTPGridColumn(7, "타입", 80, TRUE));
	CXTPGridColumn *pCol8 = m_List.AddColumn(new CXTPGridColumn(8, "응대시간", 70, TRUE));
	CXTPGridColumn *pCol9 = m_List.AddColumn(new CXTPGridColumn(9, "전화기듣기", 70, TRUE));
	CXTPGridColumn *pCol10 = m_List.AddColumn(new CXTPGridColumn(10, "다운로드", 70, TRUE));
	
	pCol0->SetAlignment(DT_CENTER);
	pCol1->SetAlignment(DT_CENTER);
	pCol2->SetAlignment(DT_CENTER);
	//pCol3->SetAlignment(DT_RIGHT);
	//pCol4->SetAlignment(DT_RIGHT);
	//pCol5->SetAlignment(DT_RIGHT);
	//pCol6->SetAlignment(DT_RIGHT);
	//pCol7->SetAlignment(DT_RIGHT);
	pCol8->SetAlignment(DT_CENTER);
	pCol9->SetAlignment(DT_CENTER);
	pCol10->SetAlignment(DT_CENTER);

	m_List.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_List.GetReportHeader()->AllowColumnRemove(FALSE);
	m_List.GetReportHeader()->AllowColumnResize(TRUE);
	m_List.GetReportHeader()->AllowColumnSort(TRUE);
	m_List.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_List.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_List.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);	
	m_List.SetGridColor(RGB(180, 180, 200));
	m_List.Populate();

	m_List.GetColumns()->SetSortColumn(pCol1, FALSE);

	m_edtSearch.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtSearch.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "전번/통화자", FALSE, FALSE);

	//SetResize(IDC_REPORT_LIST, sizingRightBottom);

	m_cmbBoundType.AddString("전체");
	m_cmbBoundType.AddString("아웃바운드");
	m_cmbBoundType.AddString("인바운드");
	m_cmbBoundType.SetCurSel(AfxGetApp()->GetProfileInt("RcpRecordFileName", "BoundType", 0));
	m_chkOrderCheck.SetCheck(AfxGetApp()->GetProfileInt("RcpRecordFileName", "OrderCheck", 0));

	RefreshListToday();
	//SetTimer(0, 30000, 0);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void CRcpPageRecordFileForm::OnSize(UINT nType, int cx, int cy)
{
	CMyFormView::OnSize(nType, cx, cy);

	if(m_List.GetSafeHwnd())
	{
		CRect rc, rcList; 
		GetClientRect(rc);
		m_List.GetWindowRect(rcList);
		ScreenToClient(rcList);

		rcList.right = rc.right - 5;
		rcList.bottom = rc.bottom - 5;

		m_List.MoveWindow(rcList);
	}
}


void CRcpPageRecordFileForm::RefreshList()
{
	UpdateData(TRUE);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_record_file_name");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);

	if(!rs.Execute(&cmd)) return;

	m_List.GetRecords()->RemoveAll();
	if (m_bTodayRefresh == TRUE)
	{
		m_bTodayRefresh = FALSE;
		COleDateTime dtDate = COleDateTime::GetCurrentTime();

		if(dtDate.GetHour() < 7)
			dtDate = dtDate - COleDateTimeSpan(1, 0, 0, 0);

		m_dtLast.SetDateTime(dtDate.GetYear(), dtDate.GetMonth(), dtDate.GetDay(), 7, 0, 0);
	}


	CString strDate, strDay, strTime, strKeyPhoneID, strTellNumber, strFileName, strBound, strOperator, strDID;
	int nCompany = 0, nTNo = 0, nBound = 0, nStartMiliSec, nEndMiliSec, nInsertType;
	COleDateTime dtDate;
	BOOL bShowTimeColumn = FALSE;

	for (int nRecordCount = 0 ; nRecordCount < rs.GetRecordCount() ; nRecordCount++)
	{
		rs.GetFieldValue("nCompany", nCompany);
		rs.GetFieldValue("dtRegister", dtDate);
		rs.GetFieldValue("nTNo", nTNo);
		rs.GetFieldValue("sKeyPhoneID", strKeyPhoneID);
		rs.GetFieldValue("sTellNumber", strTellNumber);
		rs.GetFieldValue("sFileName", strFileName);
		rs.GetFieldValue("nBound", nBound);
		rs.GetFieldValue("sOperator", strOperator);
		rs.GetFieldValue("sDID", strDID);
		rs.GetFieldValue("nStartMiliSec", nStartMiliSec);
		rs.GetFieldValue("nEndMiliSec", nEndMiliSec);
		rs.GetFieldValue("nInsertType", nInsertType); 
		//insertType 0 구버전 행업시 테이블등록, 1 통화중 등록, 통화완료후 시간 업데이트, 2 행업 등록

		CString strBranch;
		if(nStartMiliSec > 0 || nInsertType != 0)
		{
			bShowTimeColumn = TRUE;
			CBranchInfo *pBi2 = LU->SearchLineGroup((LPSTR)(LPCTSTR)strDID);
			if(pBi2)
			{
				CBranchInfo *pBi = m_ba.GetCount() > 1 ? pBi2 : 0;
				if(pBi)
					strBranch = pBi->strBranchName;
			}
		}
		else
			strBranch = LF->GetBranchInfo(nCompany)->strBranchName;

		if(nInsertType == 0 && nStartMiliSec > 0 && nEndMiliSec >= 0)
			dtDate = dtDate - COleDateTimeSpan(0, 0, 0, nStartMiliSec / 1000);

		m_List.AddRecord(new CXTPRecFileRecord(dtDate, strBranch, LF->RemoveZero(nTNo), strKeyPhoneID
			, strOperator, strTellNumber, nBound, nStartMiliSec, nEndMiliSec, strFileName));

		rs.MoveNext();
	}

	CXTPGridColumn *pCol8 = m_List.GetColumns()->GetAt(8);
	pCol8->SetVisible(bShowTimeColumn);

	rs.Close();

	OnEnChangeSearchEdit();
}

void CRcpPageRecordFileForm::RefreshListToday()
{
	UpdateData(TRUE);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_record_file_name_today");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	CMkParameter *parRestartDate = cmd.AddParameter(typeDate, typeOutput, sizeof(COleDateTime), m_dtLast);

	if(!rs.Execute(&cmd)) return;

	parRestartDate->GetValue(m_dtLast);

	if (m_bTodayRefresh == FALSE)
	{
		m_List.GetRecords()->RemoveAll();
		m_bTodayRefresh = TRUE;
	}

	CString strDate, strDay, strTime, strKeyPhoneID, strTellNumber, strFileName, strBound, strOperator, strDID;
	int nCompany = 0, nTNo = 0, nBound = 0, nStartMiliSec, nEndMiliSec, nInsertType;
	COleDateTime dtDate;
	BOOL bShowTimeColumn = FALSE;

	for (int nRecordCount = 0 ; nRecordCount < rs.GetRecordCount() ; nRecordCount++)
	{
		rs.GetFieldValue("nCompany", nCompany);
		rs.GetFieldValue("dtRegister", dtDate);
		rs.GetFieldValue("nTNo", nTNo);
		rs.GetFieldValue("sKeyPhoneID", strKeyPhoneID);
		rs.GetFieldValue("sTellNumber", strTellNumber);
		rs.GetFieldValue("sFileName", strFileName);
		rs.GetFieldValue("nBound", nBound);
		rs.GetFieldValue("sOperator", strOperator);
		rs.GetFieldValue("sDID", strDID);
		rs.GetFieldValue("nStartMiliSec", nStartMiliSec);
		rs.GetFieldValue("nEndMiliSec", nEndMiliSec);
		rs.GetFieldValue("nInsertType", nInsertType); 
		//insertType 0 구버전 행업시 테이블등록, 1 통화중 등록, 통화완료후 시간 업데이트, 2 행업 등록

		CString strBranch;
		if(nStartMiliSec > 0 || nInsertType != 0)
		{
			bShowTimeColumn = TRUE;
			CBranchInfo *pBi2 = LU->SearchLineGroup((LPSTR)(LPCTSTR)strDID);
			if(pBi2)
			{
				CBranchInfo *pBi = m_ba.GetCount() > 1 ? pBi2 : 0;
				if(pBi)
					strBranch = pBi->strBranchName;
			}
		}
		else
			strBranch = LF->GetBranchInfo(nCompany)->strBranchName;

		if(nInsertType == 0 && nStartMiliSec > 0 && nEndMiliSec >= 0)
			dtDate = dtDate - COleDateTimeSpan(0, 0, 0, nStartMiliSec / 1000);

		m_List.AddRecord(new CXTPRecFileRecord(dtDate, strBranch, LF->RemoveZero(nTNo), strKeyPhoneID
			, strOperator, strTellNumber, nBound, nStartMiliSec, nEndMiliSec, strFileName));

		rs.MoveNext();
	}

	CXTPGridColumn *pCol8 = m_List.GetColumns()->GetAt(8);
	pCol8->SetVisible(bShowTimeColumn);

	rs.Close();

	OnEnChangeSearchEdit();
}

void CRcpPageRecordFileForm::OnBnClickedRefresh()
{
	CXTPGridColumn * pCol = m_List.GetColumns()->GetAt(0);
	m_List.GetColumns()->SetSortColumn(pCol, FALSE);
	RefreshList();
}

void CRcpPageRecordFileForm::OnBnClickedRefreshToday()
{
	CXTPGridColumn * pCol = m_List.GetColumns()->GetAt(1);
	m_List.GetColumns()->SetSortColumn(pCol, FALSE);
	RefreshListToday();
}

void CRcpPageRecordFileForm::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	if (nCol == 9 || nCol == 10)
	{
		CXTPRecFileRecord* pRecord = (CXTPRecFileRecord*)m_List.GetRows()->GetAt(nRow)->GetRecord();
		CString strFileName = pRecord->GetItemFileName();
		CString strOperator = pRecord->GetItem(5)->GetCaption(NULL);
		if(strFileName.GetLength() == 0)
			return;

		if(!LF->POWER_CHECK(1951, "파일 재생"))
		{
			if(strOperator == m_ui.strName)
			{
				if(!LF->POWER_CHECK(1953, "본인 파일 재생", TRUE))
					return;
			}
			else
			{
				MessageBox("녹취 파일듣기 권한이 없습니다.", "확인", MB_ICONINFORMATION);
				return;
			}
		}

		if(nCol == 9)			//전화기 듣기
		{
			CString strFolderDate = LF->GetFolderDate(strFileName);
			strFolderDate.Format("%s-%s-%s", strFolderDate.Left(4), strFolderDate.Mid(4, 2), strFolderDate.Right(2));
			if(LU->GetRcpView())
				LU->GetRcpView()->PlayRecordFile(strFolderDate, strFileName);
		}		
		else if(nCol == 10)		//접수플 듣기
		{
			if(MessageBox("파일을 다운로드 하시겠습니까?", "확인", MB_OKCANCEL) != IDOK)
				return;

			LU->PlayRecFile(pRecord->GetItemDate(), LF->GetFolderDate(strFileName), pRecord->GetItem(4)->GetCaption(NULL)
				, pRecord->GetItem(6)->GetCaption(NULL), strFileName, pRecord->GetItemBound());
		}
	}
}

void CRcpPageRecordFileForm::OnEnChangeSearchEdit()
{
	m_edtSearch.GetWindowText(m_strSearchNumber);
	BOOL bVisible = TRUE;

	if (m_strSearchNumber.GetLength() >= 3)	bVisible = FALSE;
	else
	{
		bVisible = TRUE;
		m_strSearchNumber = "";
	}

	SearchRecord(bVisible);
}

void CRcpPageRecordFileForm::SearchRecord(BOOL bVisible)
{
	int nCount = m_List.GetRecords()->GetCount();
	CXTPRecFileRecord* pRecord;
	CString strKeyPhone, strOperator, strTellNumber, strOrderNumber;
	int nBound = 0;
	for (int i = 0 ; i < nCount; i++)
	{
		pRecord = (CXTPRecFileRecord*)m_List.GetRecords()->GetAt(i);
		if (pRecord != NULL)
		{
			if (m_strSearchNumber == "")
				pRecord->SetVisible(TRUE);

			nBound = pRecord->GetItemBound();
			if (m_cmbBoundType.GetCurSel() == ALL_BOUND_CALL || nBound == m_cmbBoundType.GetCurSel())
			{
				strOrderNumber = pRecord->GetItem(3)->GetCaption(NULL);
				if (strOrderNumber.GetLength() == 0)
					pRecord->SetVisible(!m_chkOrderCheck.GetCheck());
				else
					pRecord->SetVisible(TRUE);

				if (strOrderNumber.Find(m_strSearchNumber) == -1)
				{
					strKeyPhone = pRecord->GetItem(4)->GetCaption(NULL);
					strOperator = pRecord->GetItem(5)->GetCaption(NULL);		//직원 이름 체크
					strTellNumber = pRecord->GetItem(6)->GetCaption(NULL);

					if (strKeyPhone.Find(m_strSearchNumber) < 0 &&
						strOperator.Find(m_strSearchNumber) < 0 &&
						strTellNumber.Find(m_strSearchNumber) < 0 &&
						pRecord->IsVisible() != bVisible)
					{
						pRecord->SetVisible(bVisible);
					}
				}

			}
			else
				pRecord->SetVisible(FALSE);
		}
	}

	m_List.Populate();
}

void CRcpPageRecordFileForm::OnCbnSelchangeBoundType()
{
	int nSel = m_cmbBoundType.GetCurSel();
	if(nSel < 0 || nSel >= m_cmbBoundType.GetCount())
		return;

	CString str;
	m_cmbBoundType.GetLBText(nSel,str);
	if( "" == str )
		return;

	AfxGetApp()->WriteProfileInt("RcpRecordFileName", "BoundType", nSel);
	OnEnChangeSearchEdit();
}

void CRcpPageRecordFileForm::OnBnClickedOrderCheck()
{
	AfxGetApp()->WriteProfileInt("RcpRecordFileName", "OrderCheck", m_chkOrderCheck.GetCheck());
	OnEnChangeSearchEdit();
}

BOOL CRcpPageRecordFileForm::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_SIZE)
	{
		AfxMessageBox("I got it");
	}
	return CMyFormView::PreTranslateMessage(pMsg);
}

void CRcpPageRecordFileForm::OnDtnDatetimechangeDatetimepicker(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	COleDateTime dtDate = COleDateTime::GetCurrentTime();
	if (pNMHDR->idFrom == IDC_DATETIMEPICKER_FROM)
	{
		COleDateTime dtFrom;
		m_dtpFrom.GetTime(dtFrom);
		dtDate.SetDateTime(dtDate.GetYear(), dtDate.GetMonth(), dtDate.GetDay(), 7, 0, 0);
		if (dtDate < dtFrom)
		{
			m_dtpFrom.SetTime(dtDate);
			dtFrom = dtDate;
		}
		m_dtFrom = dtFrom;
		m_dtpTo.GetTime(m_dtTo);
	}
	else
	{
		COleDateTime dtTo;
		m_dtpTo.GetTime(dtTo);
		dtDate.SetDateTime(dtDate.GetYear(), dtDate.GetMonth(), dtDate.GetDay(), 7, 0, 0);
		COleDateTimeSpan dtSpan(1,0,0,0);
		dtDate += dtSpan;
		if (dtDate < dtTo)
		{
			m_dtpTo.SetTime(dtDate);
			dtTo = dtDate;
		}
		m_dtTo = dtTo;
		m_dtpFrom.GetTime(m_dtFrom);
	}

	*pResult = 0;
	UpdateData(FALSE);
}

void CRcpPageRecordFileForm::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;


	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CRcpPageRecordFileForm::OnViewExcel()
{
	if(!LF->POWER_CHECK(1952, "녹취파일 엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 105,m_List.GetRecords()->GetCount());  
	CMyExcel::ToExcel(&m_List);
}