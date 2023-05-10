// Report3.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MainFrm.h"
#include "StaffPage17.h"
#include "WorkStopMemoDlg.h"
#include "RiderMsgDlg.h"
#include "RcpView.h"
#include "RiderOrderLogDlg.h"

#define MAX_DAY 100

// CStaffPage17 대화 상자입니다.

IMPLEMENT_DYNCREATE(CStaffPage17, CMyFormView)
CStaffPage17::CStaffPage17()
: CMyFormView(CStaffPage17::IDD)
{
	m_nLastCompanyCount = 0;
}

CStaffPage17::~CStaffPage17()
{

}

void CStaffPage17::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_DateTimeCtrl(pDX, IDC_DTP_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DTP_TO, m_dtTo);

	DDX_Control(pDX, IDC_LIST_REPORT, m_XTPList);
	DDX_Control(pDX, IDC_INFO_STATIC, m_stcInfo);
	DDX_Control(pDX, IDC_DTP_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DTP_TO, m_ToDT);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_btnRefresh);
	DDX_Control(pDX, IDC_INCRESE_COL_BTN, m_btnIncreaseCol);
	DDX_Control(pDX, IDC_NOT_WORK_CHECK, m_chkNotWork);
}


BEGIN_MESSAGE_MAP(CStaffPage17, CMyFormView)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_COMMAND(ID_WORK_STOP, OnWorkStop)
	ON_COMMAND(ID_WORK_OK, OnWorkOk)
	ON_COMMAND(ID_SEND_MSG, OnMenuMsg)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_BN_CLICKED(IDC_INCRESE_COL_BTN, OnBnClickedIncreseColBtn)
	ON_NOTIFY(LVN_DELETEALLITEMS, IDC_LIST_REPORT, OnLvnDeleteallitemsListReport)
	ON_NOTIFY(NM_CLICK, IDC_LIST_REPORT, OnNMClickListReport)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_REPORT, OnNMDblclkListReport)
	//ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DTP_FROM, OnDtnDatetimechangeDtpFrom)
	ON_BN_CLICKED(IDC_NOT_WORK_CHECK, OnBnClickedNotWorkCheck)
END_MESSAGE_MAP()


// CStaffPage17 메시지 처리기입니다.


void CStaffPage17::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuToday();

	m_stcInfo.SetWindowText("* 단말기 접속기준");

	m_XTPList.InsertColumn(0, "기사번호", LVCFMT_LEFT, 50);
	m_XTPList.InsertColumn(1,"소속",LVCFMT_LEFT, 50);
	m_XTPList.InsertColumn(2, "기사명", LVCFMT_LEFT, 60);
	m_XTPList.InsertColumn(3, "출근율", LVCFMT_RIGHT, 40);
	m_XTPList.SetFreezeColumnsCount(4);
	m_XTPList.GetPaintManager()->SetFreezeColsDividerStyle(0);
	m_XTPList.GetReportHeader()->AllowColumnReorder(FALSE);
	m_XTPList.Populate();

	MonthInit();

	SetResize(IDC_LIST_REPORT, sizingRightBottom);

}

void CStaffPage17::MonthInit(void)
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();
	COleDateTime dtTo = COleDateTime::GetCurrentTime();

	if(dtFrom.GetHour() < BASE_HOUR) {
		dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtFrom = dtTo - COleDateTimeSpan(1, 0, 0, 0);
	}
	else {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtTo = dtFrom + COleDateTimeSpan(1, 0, 0, 0);
	}

	dtFrom = dtFrom - COleDateTimeSpan(30, 0, 0, 0);
	m_FromDT.SetTime(dtFrom);

	//dtTo = dtTo + COleDateTimeSpan(1, 0, 0, 0); 
	m_ToDT.SetTime(dtTo);
}


void CStaffPage17::OnMenuMsg()
{
	if(!POWER_CHECK(1200, "기사공지창 보기", TRUE))
		return;

	int nSelItem = m_XTPList.GetNextItem(-1, LVNI_SELECTED);

	CRiderMsgDlg dlg;
	dlg.m_nRNo = atol(m_XTPList.GetItemText(nSelItem, 0));
	dlg.DoModal();
}

void CStaffPage17::RefreshList()
{	
	CMyFormView::RefreshList();
	UpdateData(TRUE);

	//금일 이후 테이터는 존재하지 않는다.
	COleDateTime dtToday = COleDateTime::GetCurrentTime() + COleDateTimeSpan(1, 0, 0, 0);
	COleDateTime dtTomorrow(dtToday.GetYear(), dtToday.GetMonth(), dtToday.GetDay(), 7, 0, 0);
	if(m_dtTo > dtTomorrow)
	{
		m_dtTo = m_dtTo - COleDateTimeSpan(1, 0, 0, 0);
		m_ToDT.SetTime(m_dtTo);
	}

	COleDateTimeSpan span = m_dtTo - m_dtFrom;
	long nDays = span.GetTotalDays();

	if(nDays > MAX_DAY)
	{ 
		MessageBox("100일이상 조회 하실 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CreateHeader();
	//		CreateHeader(1); 1일부터 31일적용

	m_XTPList.DeleteAllItems();
	m_RiderInfo.clear();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_driver_device_login_1");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime),m_dtFrom );
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime),m_dtTo );
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL),  m_chkNotWork.GetCheck());
	pCmd.Execute();
	
	int nDayTotAttend[MAX_DAY];

	for(int m = 0; m < MAX_DAY; m++)
		nDayTotAttend[m] = 0;

	if(pRs.Execute(&pCmd))
	{
		int nRNo, nCompany, nWorkState, nCount, nRecordIndex, nFindDay;
		COleDateTime dtDate;	
		COleDateTimeSpan dtSpan;
		CString strName, strRiderName, strTotal, strPercent, strTemp;
		RIDER_ATTEND2::iterator iter;
		float fResult = 0;
		nRNo = nCompany = nWorkState = nCount = nFindDay = 0;
		nRecordIndex = -1;

		while(!pRs.IsEOF()) 
		{
			pRs.GetFieldValue("nCompany", nCompany);
			pRs.GetFieldValue("nRNo", nRNo);
			pRs.GetFieldValue("dtDate", dtDate);
			pRs.GetFieldValue("sRName", strName);
			pRs.GetFieldValue("sRiderName", strRiderName);
			pRs.GetFieldValue("nWorkState", nWorkState);

			pair<CString, pair<int, int>> tempPair = make_pair(strName.GetLength() > 0 ? strName : strRiderName, make_pair(nCompany, nRNo));
			iter = m_RiderInfo.find(tempPair);
			if(iter == m_RiderInfo.end())
			{
				if(nRecordIndex != -1)
				{
					fResult = (float)(nCount * 100) / nDays;
					strPercent.Format("%2.1f",fResult);
					m_XTPList.SetItemText(nRecordIndex,3,strPercent);

					strTotal = ::GetStringFromLong(nCount);
					strTotal += "일";
					m_XTPList.SetItemText(nRecordIndex, nDays + 4, strTotal);
					for(int i = nFindDay + 1; i < nDays + 4; i++)
					{
						m_XTPList.SetItemText(nRecordIndex, i, "X");
						m_XTPList.ChangeItemBackColor(nRecordIndex, i, RGB(255, 100, 100));
						m_XTPList.ChangeItemTextColor(nRecordIndex, i, RGB(255, 255, 255));
					}
				}

				nRecordIndex++;
				m_RiderInfo.insert(RIDER_ATTEND2::value_type(tempPair, nRecordIndex));

				m_XTPList.InsertItem(nRecordIndex, GetStringFromLong(nRNo));
				m_XTPList.SetItemText(nRecordIndex, 1, m_ci.GetName(nCompany));
				m_XTPList.SetItemText(nRecordIndex, 2, strName.GetLength() > 0 ? strName : strRiderName);
				if(nWorkState == 1)
				{
					m_XTPList.ChangeItemBackColor(nRecordIndex, 0, RGB(255,196,196));
					m_XTPList.ChangeItemBackColor(nRecordIndex, 1, RGB(255,196,196));
				}
				m_XTPList.SetItemData(nRecordIndex, nCompany);

				nCount = 0;
			}
			else
				nRecordIndex = iter->second;

			COleDateTimeSpan dtGap(0,0,10,0); // 자동생성 06: 50분
			dtSpan = dtDate - (m_dtFrom - dtGap);			
			nFindDay = dtSpan.GetDays() + 4; 

			m_XTPList.SetItemText(nRecordIndex, nFindDay, "O");  // -1 어제
			m_XTPList.ChangeItemBackColor(nRecordIndex, nFindDay, RGB(100, 255, 100));
			m_XTPList.ChangeItemTextColor(nRecordIndex, nFindDay, RGB(255, 255, 255));
			nDayTotAttend[nFindDay - 4]++;
			m_XTPList.SetItemText(nRecordIndex, m_nLastCompanyCount, GetStringFromLong(nCompany));
			
			nCount++;
			pRs.MoveNext();			
		}

		pRs.Close();

		if(nCount > 0)
		{
			fResult = (float)(nCount * 100) / nDays;
			strPercent.Format("%2.1f",fResult);
			m_XTPList.SetItemText(nRecordIndex, 3, strPercent);

			m_XTPList.SetItemText(nRecordIndex, nDays + 4, ::GetStringFromLong(nCount) + "일");
			for(int i = nFindDay + 1; i < nDays + 4; i++)
			{
				m_XTPList.SetItemText(nRecordIndex, i, "X");
				m_XTPList.ChangeItemBackColor(nRecordIndex, i, RGB(255, 100, 100));
				m_XTPList.ChangeItemTextColor(nRecordIndex, i, RGB(255, 255, 255));
			}
		}

		m_XTPList.InsertItem(nRecordIndex, "합계");
		int nAllTotalAttend = 0;
		for(int n = 0; n < nDays; n++)
		{
			nAllTotalAttend += nDayTotAttend[n];
			m_XTPList.SetItemText(m_XTPList.GetRecords()->GetCount() - 1, n + 4, ::GetStringFromLong(nDayTotAttend[n]));
		}
		if(nAllTotalAttend != 0)
			m_XTPList.SetItemText(m_XTPList.GetRecords()->GetCount() - 1, nDays + 4, ::GetStringFromLong(nAllTotalAttend));
	}

	m_XTPList.Populate();
}

void CStaffPage17::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_XTPList.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	int nItem = m_XTPList.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {
		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(2);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}
}

void CStaffPage17::OnViewExcel()
{
	if(!POWER_CHECK(5900, "엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nCompanyCode, 404, m_XTPList.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_XTPList);
}

void CStaffPage17::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CStaffPage17::CreateHeader()
{	
	COleDateTime dtRecentDay = m_dtFrom;

	DeleteColumn();

	COleDateTime dtFrom, dtTo;
	dtFrom = m_dtFrom;
	dtTo = m_dtTo - COleDateTimeSpan(1, 0, 0, 0);

	int nCol = 4;
	m_XTPList.InsertColumn( nCol++, m_dtFrom.Format("%m-%d"), LVCFMT_CENTER, 35);
	dtFrom = dtFrom + COleDateTimeSpan(1, 0, 0, 0);
	while(dtFrom <= dtTo)
	{
		if(dtFrom.GetDay() == 1)
			m_XTPList.InsertColumn( nCol++, dtFrom.Format("%m-%d"), LVCFMT_CENTER, 35);
		else
			m_XTPList.InsertColumn( nCol++, dtFrom.Format("%d"), LVCFMT_CENTER, 30);
		dtFrom = dtFrom + COleDateTimeSpan(1, 0, 0, 0);
	}
	m_XTPList.InsertColumn(nCol++, "합계", LVCFMT_CENTER, 40);
	m_nLastCompanyCount = nCol;
	m_XTPList.InsertColumn(nCol++, "0", LVCFMT_LEFT, 0);

	m_XTPList.Populate();
}

/*
void CStaffPage17::SetRiderInfo(void) //기사정보
{
	//CWaitCursor wait;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_driver_attend_registerlist3");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(m_chkNotWork.GetCheck());
	pCmd.Execute();

	if(pRs.Execute(&pCmd))
	{
		int nMNo, iCount, nSubItem, lCode, nItem, nWorkState;
		CString sName, strCompanyMNo;
		COleDateTime dtWorkStateDate;
		COleDateTimeSpan dtSpan;
		nMNo = iCount = nSubItem = lCode = nItem = nWorkState = 0;
		m_RiderInfo.clear();

		while(!pRs.IsEOF()) 
		{
			nSubItem = 1;
			pRs.GetFieldValue(0, nMNo);
			pRs.GetFieldValue(1, sName);			
			pRs.GetFieldValue(2, lCode);
			pRs.GetFieldValue(3, nWorkState);			
			pRs.GetFieldValue(4, dtWorkStateDate);

			RIDER_ATTEND_INFO2 rider;//= new RIDER_ATTEND_INFO2;			

			strCompanyMNo = ::GetStringFromLong(lCode);
			rider.strCompanyCode = strCompanyMNo;

			strCompanyMNo += ::GetStringFromLong(nMNo);
			rider.nRow = iCount;

			m_XTPList.InsertItem(nItem, ::GetStringFromLong(nMNo));
			if(nWorkState == 1)
			{
				m_XTPList.SetItemData(nItem,nWorkState);
				m_XTPList.ChangeItemBackColor(nItem, 0, RGB(255,196,196));
				m_XTPList.ChangeItemBackColor(nItem, 1, RGB(255,196,196));

				// DB에서 가져올 때dtWorkStateDate값이 NULL 일 경우가 있고 이 경우 오류남
				if( dtWorkStateDate.GetStatus() == COleDateTime::valid)
				{
					dtSpan = dtWorkStateDate - m_dtFrom;
					m_XTPList.SetItemText(nItem, 0, "★");
				}
			}

			m_XTPList.SetItemText(nItem, nSubItem++, m_ci.GetName(lCode));
			m_XTPList.SetItemText(nItem, nSubItem++, sName);

			m_RiderInfo.insert(RIDER_ATTEND2::value_type(strCompanyMNo,rider));  

			iCount++;
			nItem++;
			pRs.MoveNext();
		}

		m_XTPList.InsertItem(nItem, "합계");
		pRs.Close();
	}
	m_XTPList.Populate();
}

void CStaffPage17::SetRiderState(void) //출근상태
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_driver_device_login");  
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime),m_dtFrom );
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime),m_dtTo );
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL),  m_chkNotWork.GetCheck());

	COleDateTimeSpan span = m_dtTo - m_dtFrom;
	long nDays = span.GetTotalDays();

	int nDayTotAttend[MAX_DAY];

	for(int m = 0; m < MAX_DAY; m++)
		nDayTotAttend[m] = 0;

	if(pRs.Execute(&pCmd))
	{
		int nRNo, iCount, nCompany, nWorkState, nCount, nItem, nFindDay;
		COleDateTime dt10;	
		COleDateTimeSpan dtSpan;
		CString strName, strTotal, strPercent, strCompanyRno, strTempRno;
		RIDER_ATTEND2::iterator iter;
		float fResult = 0;
		nRNo = iCount = nCompany = nWorkState = nCount = nItem = nFindDay = 0;
		strTempRno = "초기화";

		while(!pRs.IsEOF()) 
		{
			pRs.GetFieldValue(0,nCompany );
			pRs.GetFieldValue(1,nRNo );
			pRs.GetFieldValue(2,strName );
			pRs.GetFieldValue(3,nWorkState);
			pRs.GetFieldValue(4,dt10);

			strCompanyRno = ::GetStringFromLong(nCompany);
			strCompanyRno += GetStringFromLong(nRNo);

			if(strTempRno != strCompanyRno)
			{
				if(strTempRno != "초기화")
				{
					fResult = (float)(nCount * 100) / nDays;
					strPercent.Format("%2.1f",fResult);
					m_XTPList.SetItemText(nItem,3,strPercent);

					strTotal = ::GetStringFromLong(nCount);
					strTotal += "일";
					m_XTPList.SetItemText(nItem, nDays + 4, strTotal);
					for(int i = nFindDay + 1; i < nDays + 4; i++)
					{
						if(m_XTPList.GetItemText(nItem, i) != "★")
						{
							m_XTPList.SetItemText(nItem, i, "X");
							m_XTPList.ChangeItemBackColor(nItem, i, RGB(255, 100, 100));
							m_XTPList.ChangeItemTextColor(nItem, i, RGB(255, 255, 255));
						}
						else if(m_XTPList.GetItemText(nItem, i) == "★")
						{
							m_XTPList.ChangeItemBackColor(nItem, 0, RGB(255, 196, 196));
							m_XTPList.ChangeItemBackColor(nItem, 1, RGB(255, 196, 196));
						}
					}
				}

				iter = m_RiderInfo.find(strCompanyRno);

				strTempRno = strCompanyRno; // 기사가 바뀌면
				nCount = 0; // 초기화
			}
			nItem = iter->second.nRow;			

			COleDateTimeSpan dtGap(0,0,10,0); // 자동생성 06: 50분
			dtSpan = dt10 - (m_dtFrom - dtGap);			
			nFindDay = dtSpan.GetDays() + 4; 

			m_XTPList.SetItemText(nItem, nFindDay, "O");  // -1 어제
			m_XTPList.ChangeItemBackColor(nItem, nFindDay, RGB(100, 255, 100));
			m_XTPList.ChangeItemTextColor(nItem, nFindDay, RGB(255, 255, 255));
			nDayTotAttend[nFindDay - 4]++;
			m_XTPList.SetItemText(nItem, m_nLastCompanyCount,iter->second.strCompanyCode);
			m_XTPList.SetItemData(nItem, _ttoi(iter->second.strCompanyCode));

			nCount++;
			pRs.MoveNext();			
		}

		pRs.Close();

		if(nCount > 0)
		{
			fResult = (float)(nCount * 100) / nDays;
			strPercent.Format("%2.1f",fResult);
			m_XTPList.SetItemText(nItem, 3, strPercent);

			m_XTPList.SetItemText(nItem, nDays + 4, ::GetStringFromLong(nCount) + "일");
			for(int i = nFindDay + 1; i < nDays + 4; i++)
			{
				if(m_XTPList.GetItemText(nItem, i) != "★")
				{
					m_XTPList.SetItemText(nItem, i, "X");
					m_XTPList.ChangeItemBackColor(nItem, i, RGB(255, 100, 100));
					m_XTPList.ChangeItemTextColor(nItem, i, RGB(255, 255, 255));
				}

				else if(m_XTPList.GetItemText(nItem, i) == "★")
				{
					m_XTPList.ChangeItemBackColor(nItem, 0, RGB(255, 196, 196));
					m_XTPList.ChangeItemBackColor(nItem, 1, RGB(255, 196, 196));
				}
			}
		}
		
		int nAllTotalAttend = 0;
		for(int n = 0; n < nDays; n++)
		{
			nAllTotalAttend += nDayTotAttend[n];
			m_XTPList.SetItemText(m_XTPList.GetRows()->GetCount() - 1, n + 4, ::GetStringFromLong(nDayTotAttend[n]));
		}
		if(nAllTotalAttend != 0)
			m_XTPList.SetItemText(m_XTPList.GetRows()->GetCount() - 1, nDays + 4, ::GetStringFromLong(nAllTotalAttend));

	}
	m_XTPList.Populate();
}*/

void CStaffPage17::DeleteColumn(void)
{
	int nCount = m_XTPList.GetColumns()->GetCount();
	for(int i = 0; i < nCount; i++)
	{
		CXTPGridColumn *pColum = m_XTPList.GetColumns()->GetAt(4);
		m_XTPList.GetColumns()->Remove(pColum);
	}
}

void CStaffPage17::OnWorkStop()
{
	UINT i, uSelectedCount = m_XTPList.GetRows()->GetCount();
	int  nItem = -1;

	// Update all of the selected items.
	if(uSelectedCount > 0)
	{
		CString strWorkTitle = "";
		CString strWorkMemo = "";
		CWorkStopMemoDlg dlg;
		if(dlg.DoModal() == IDOK)
		{
			for (i = 0;i < uSelectedCount; i++)
			{
				nItem = m_XTPList.GetNextItem(nItem, LVNI_SELECTED);
				if(nItem < 0) break;

				if(!ChangeRiderWorkState(GetCurBranchInfo()->nCompanyCode, 
					atol(m_XTPList.GetItemText(nItem, 0)),  
					GetCurBranchInfo()->bIntegrated,
					dlg.m_strWorkStopMemo,  
					dlg.m_strContent,
					TRUE))
				{
					MessageBox("일괄작업중에 에러발생", "확인", MB_ICONERROR);
					return;
				}
			}
		}
	}
	else {
		MessageBox("직원을 선택하십시오!", "확인", MB_ICONINFORMATION);
	}

	RefreshList();
}

void CStaffPage17::OnWorkOk()
{
	UINT i, uSelectedCount = m_XTPList.GetRows()->GetCount();
	int  nItem = -1;

	// Update all of the selected items.
	if(uSelectedCount > 0)
	{
		CString strWorkTitle = "";
		CString strWorkMemo = "";
		CWorkStopMemoDlg dlg;
		if(dlg.DoModal() == IDOK)
		{
			for (i = 0;i < uSelectedCount; i++)
			{
				nItem = m_XTPList.GetNextItem(nItem, LVNI_SELECTED);
				if(nItem < 0) break;

				if(!ChangeRiderWorkState(GetCurBranchInfo()->nCompanyCode, 
					atol(m_XTPList.GetItemText(nItem, 0)),  
					GetCurBranchInfo()->bIntegrated,
					dlg.m_strWorkStopMemo,  
					dlg.m_strContent,
					FALSE))
				{
					MessageBox("일괄작업중에 에러발생", "확인", MB_ICONERROR);
					return;
				}
			}
		}
	}
	else {
		MessageBox("직원을 선택하십시오!", "확인", MB_ICONINFORMATION);
	}

	RefreshList();
}

void CStaffPage17::OnBnClickedIncreseColBtn()
{
	for(int c = 4; c < m_XTPList.GetColumns()->GetCount() -1; c++)
	{
		CXTPGridColumn *pColum = m_XTPList.GetColumns()->GetAt(c);
		pColum->SetWidth(pColum->GetWidth() + 6);
	}
}

void CStaffPage17::OnLvnDeleteallitemsListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	m_RiderInfo.clear();	


	*pResult = 0;
}

void CStaffPage17::OnNMClickListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	//NMITEMACTIVATE * pNMIA = (NMITEMACTIVATE*) pNMHDR;
	XTP_NM_REPORTRECORDITEM *pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNMHDR;

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_XTPList.GetNextItem(-1, LVNI_SELECTED);
	int nColumn = pItemNotify->pColumn->GetIndex();

	if(pItemNotify == NULL)
		return;

	if(nColumn>1 || index == -1) //굵은 글씨 이상
		return;

	if(m_XTPList.GetItemText(index, 0) == "★")
		return;

	long nCompany = (long)m_XTPList.GetItemData(index);
	long nRNo = _ttoi(m_XTPList.GetItemText(index, 0));

	LU->ShowRiderInfoDlg(nCompany, nRNo);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

void CStaffPage17::OnNMDblclkListReport(NMHDR *pNMHDR, LRESULT *pResult)
{ 
	long index = m_XTPList.GetNextItem(-1, LVNI_SELECTED);

	CString str = m_XTPList.GetItemText(index, 1);

	if(str == "")
		return;

	CRiderOrderLogDlg dlg;
	//dlg.m_nRiderCompany = _ttoi(m_List.GetItemText(index, m_nLastCompanyCount));
	dlg.m_nRiderCompany = (long)m_XTPList.GetItemData(index);
	dlg.m_nRNo = _ttoi(m_XTPList.GetItemText(index, 0));
	dlg.m_strRName = m_XTPList.GetItemText(index, 2);

	dlg.DoModal();
	
	*pResult = 0;
}
/*
void CStaffPage17::OnDtnDatetimechangeDtpFrom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	COleDateTime dtFrom; m_FromDT.GetTime(dtFrom);
	COleDateTimeSpan span(30, 0, 0, 0);
	COleDateTime dtTo = dtFrom + span;
	
	dtTo.SetDateTime(dtTo.GetYear(), dtTo.GetMonth(), dtTo.GetDay(), 23, 59, 59);
	m_ToDT.SetTime(dtTo);

	*pResult = 0;
}
*/
void CStaffPage17::OnBnClickedNotWorkCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
