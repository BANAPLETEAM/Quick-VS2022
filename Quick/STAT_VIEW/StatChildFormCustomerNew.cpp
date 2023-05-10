// Report4.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "StatChildFormCustomerNew.h"

// CStatChildFormCustomerNew 대화 상자입니다.


IMPLEMENT_DYNCREATE(CStatChildFormCustomerNew, CMyFormView)
CStatChildFormCustomerNew::CStatChildFormCustomerNew()
	: CMyFormView(CStatChildFormCustomerNew::IDD)
	, m_ptBaseWndPos(0,30)
{
	//m_pBaseForm = NULL;
	m_bDivisionView = FALSE;
}

CStatChildFormCustomerNew::~CStatChildFormCustomerNew()
{
}

void CStatChildFormCustomerNew::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_Control(pDX,		IDC_REPORT_LIST,			m_List);
	DDX_DateTimeCtrl(pDX,	IDC_DATETIMEPICKER_FROM,	m_dtFrom);
	DDX_DateTimeCtrl(pDX,	IDC_DATETIMEPICKER_TO,		m_dtTo);
	DDX_Control(pDX,		IDC_XTP_CHART,				m_Chart);
	DDX_Control(pDX,		IDC_DATETIMEPICKER_FROM,	m_dtpFrom);	
	DDX_Control(pDX,		IDC_DATETIMEPICKER_TO,		m_dtpTo);
	DDX_Control(pDX,		IDC_DATE_BTN,				m_btnDate);
	DDX_Control(pDX,		IDC_REFRESH_BTN,			m_btnRefresh);
	DDX_Control(pDX,		IDC_LIST_TYPE_COMBO,		m_cmbListType);
	DDX_Control(pDX,		IDC_CHART_FIELD_COMBO,		m_cmbChartField);
	DDX_Control(pDX,		IDC_WEEKDAY_COMBO,			m_cmbWeekDay);
	DDX_Control(pDX,		IDC_LIST_ITEM_TYPE_COMBO,	m_cmbListItemType);
}



BEGIN_MESSAGE_MAP(CStatChildFormCustomerNew, CMyFormView)
	//ON_WM_TIMER()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL,				OnViewExcel)
	ON_BN_CLICKED(IDC_REFRESH_BTN,			OnBnClickedRefreshBtn)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_FROM, OnDtnDatetimechangeDatetimepicker)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_TO, OnDtnDatetimechangeDatetimepicker)
	ON_BN_CLICKED(IDC_GRAPH_BTN, OnBnClickedGraphBtn)
	ON_NOTIFY (UDM_TOOLTIP_DISPLAY, NULL,	NotifyDisplayTooltip)
	ON_CBN_SELCHANGE(IDC_LIST_TYPE_COMBO, OnCbnSelchangeListTypeCombo)
	ON_CBN_SELCHANGE(IDC_CHART_FIELD_COMBO, OnCbnSelchangeChartFieldCombo)
	ON_CBN_SELCHANGE(IDC_WEEKDAY_COMBO, OnCbnSelchangeWeekDayCombo)
	ON_CBN_SELCHANGE(IDC_LIST_ITEM_TYPE_COMBO, OnCbnSelchangeListItemTypeCombo)
	ON_WM_SIZE()
	
END_MESSAGE_MAP()


// CStatChildFormCustomerNew 메시지 처리기입니다.

void CStatChildFormCustomerNew::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();
	if(FALSE == m_bInitialUpdateCalled) return;

	InitLayoutRight();

	m_btnDate.InitDateButton(&m_dtpFrom, &m_dtpTo);
	m_btnDate.OnMenuMonth();

	m_List.InsertColumn(DATE,			"일자",				LVCFMT_LEFT,	100);
	m_List.InsertColumn(TOTALCUSTOMER,	"총고객",			LVCFMT_RIGHT,	60);
	m_List.InsertColumn(TODAYCUSTOMER,	"총신규고객",		LVCFMT_RIGHT,	95);
	m_List.InsertColumn(TOTALCOMPLETE,	"이용고객",			LVCFMT_RIGHT,	60);
	m_List.InsertColumn(TODAYCOMPLTE,	"당일신규이용고객",	LVCFMT_RIGHT,	95);
	m_List.InsertColumn(MONTH_3,		"3개월 전 고객",	LVCFMT_RIGHT,	90);
	m_List.InsertColumn(MONTH_6,		"6개월 전 고객",	LVCFMT_RIGHT,	90);
	m_List.InsertColumn(YEAR_1,			"1년 전 고객",		LVCFMT_RIGHT,	80);
	m_List.InsertColumn(YEAR_2,			"2년 전 고객",		LVCFMT_RIGHT,	80);
	m_List.InsertColumn(YEAR_3,			"3년 전 고객",		LVCFMT_RIGHT,	80);

	m_List.GetReportHeader()->AllowColumnSort(FALSE);
	m_List.GetPaintManager()->m_strNoItems = "";
	m_List.SetFreezeColumnsCount(1);
	m_List.GetPaintManager()->SetFreezeColsDividerStyle(0);
	m_List.Populate();

	m_nListType = AfxGetApp()->GetProfileInt("Stat", "NewCustomer_ListType", 0);
	m_cmbListType.AddString("일별조회");
	m_cmbListType.AddString("주별조회");
	m_cmbListType.AddString("월별조회");
	m_cmbListType.SetCurSel(m_nListType);

	m_nChartField = AfxGetApp()->GetProfileInt("Stat", "NewCustomer_ChartField", 0);
	m_cmbChartField.AddString("총고객");
	m_cmbChartField.AddString("총신규고객");
	m_cmbChartField.AddString("이용고객");
	m_cmbChartField.AddString("당일신규이용고객");
	m_cmbChartField.AddString("3개월전");
	m_cmbChartField.AddString("6개월전");
	m_cmbChartField.AddString("1년전");
	m_cmbChartField.AddString("2년전");
	m_cmbChartField.AddString("3년전");
	m_cmbChartField.SetCurSel(m_nChartField);

	m_nWeekDay = AfxGetApp()->GetProfileInt("Stat", "NewCustomer_WeekDayType", WEEK_ALLDAY);
	m_cmbWeekDay.SetCurSel(m_nWeekDay);

	m_nListItemType = AfxGetApp()->GetProfileInt("Stat", "NewCustomer_ListItemType", PERCENT_ITEM_TYPE);
	m_cmbListItemType.AddString("신규고객율");
	m_cmbListItemType.AddString("신규고객수");
	m_cmbListItemType.SetCurSel(m_nListItemType);

	CString str;
	m_cmbChartField.GetLBText(m_nChartField, str);

	m_Chart.ChartCreate("", BAR_CHART_STYLE, 7);
	m_Chart.SetTooltipText(str);
	m_Chart.SetLegendFormat("일", 0);
	m_Chart.SetLegendFormat("월", 1);
	m_Chart.SetLegendFormat("화", 2);
	m_Chart.SetLegendFormat("수", 3);
	m_Chart.SetLegendFormat("목", 4);
	m_Chart.SetLegendFormat("금", 5);
	m_Chart.SetLegendFormat("토", 6);
	m_Chart.SetShowLegend(TRUE);

	if (0 == m_nChartField)
		m_Chart.SetChartYAxisGeneralType();
	else
		m_Chart.SetChartYAxisLabelFormat("%%");

	OnCbnSelchangeListTypeCombo();

	m_tooltip.Create(this, FALSE);
	m_tooltip.SetBehaviour(PPTOOLTIP_MULTIPLE_SHOW);
	m_tooltip.SetNotify();
	m_tooltip.SetTransparency(30);

	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_INITIAL, 100);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_AUTOPOP, 50000);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEIN, 10);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEOUT, 10);

	m_tooltip.AddTool(&m_Chart, "");
	m_tooltip.SetColorBk(RGB(255,255,0));
	//SetTimer(100, 1000, NULL);

}

void CStatChildFormCustomerNew::InitDivisionDate()
{
	if (m_bDivisionView == TRUE)
	{
		m_dtpTo.GetTime(m_dtTo);
		m_dtpFrom.GetTime(m_dtFrom);
		COleDateTimeSpan dtsDay = m_dtTo - m_dtFrom;
	
		m_dtFrom -= dtsDay.GetDays() + 1;
		m_dtTo -= dtsDay.GetDays() + 1;
		UpdateData(FALSE);

		SetDlgCtrlID(9999);
	}
}

void CStatChildFormCustomerNew::RefreshListWeek()
{
	CMyFormView::RefreshList();
	UpdateData(TRUE);
	m_mapRecordData.clear();
	
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_new_customer_increase_week_1");

	cmd.AddParameter(GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);

	if(!rs.Execute(&cmd)) return;

	m_List.GetRecords()->RemoveAll();
	m_Chart.SetAllSeriesVisible(FALSE);
	m_Chart.SetShowLegend(FALSE);

	COleDateTime dtStartDate, dtDestDate;
	CString strTitle, strStartDate, strDestDate;

	for (int nRecordCount = 0 ; nRecordCount < rs.GetRecordCount() ; nRecordCount++)
	{
		ST_RECORD_DATA stNew;

		rs.GetFieldValue("sStartDate", strStartDate);
		rs.GetFieldValue("sDestDate", strDestDate);

		rs.GetFieldValue("nTotalCustomer", stNew.nTotalCustomer);
		rs.GetFieldValue("nTotalComplete", stNew.nTotalComplete);
		rs.GetFieldValue("nNewTodayCustomer", stNew.nNewTodayCustomer);
		rs.GetFieldValue("nTodayComplete", stNew.nTodayComplete);
		rs.GetFieldValue("nNew3MonthCount", stNew.nNew3MonthCount);
		rs.GetFieldValue("nNew6MonthCount", stNew.nNew6MonthCount);
		rs.GetFieldValue("nNew1YearCount", stNew.nNew1YearCount);
		rs.GetFieldValue("nNew2YearCount", stNew.nNew2YearCount);
		rs.GetFieldValue("nNew3YearCount", stNew.nNew3YearCount);

		dtStartDate.SetDate(atoi(strStartDate.Left(4)), atoi(strStartDate.Mid(4,2)), atoi(strStartDate.Right(2)));
		dtDestDate.SetDate(atoi(strDestDate.Left(4)), atoi(strDestDate.Mid(4,2)), atoi(strDestDate.Right(2)));
		strTitle.Format("%d/%02d(%s) - %02d(%s)", dtStartDate.GetMonth(), dtStartDate.GetDay(), ::GetDay(dtStartDate), dtDestDate.GetDay(), ::GetDay(dtDestDate));

		m_List.InsertItem(nRecordCount, strTitle);

		m_mapRecordData[nRecordCount] = stNew;

		rs.MoveNext();
	}

	rs.Close();

	RefreshListItem();
}

void CStatChildFormCustomerNew::RefreshListItem()
{
	CString strPer;
	map<int, ST_RECORD_DATA>::iterator it;
	for(it = m_mapRecordData.begin() ; it != m_mapRecordData.end() ; it++)
	{
		if (m_nListItemType == PERCENT_ITEM_TYPE)
		{
			m_List.SetItemText(it->first, TOTALCUSTOMER, ::GetMyNumberFormat(it->second.nTotalCustomer));
			m_List.SetItemText(it->first, TODAYCUSTOMER, ::GetMyNumberFormat(it->second.nNewTodayCustomer));
			m_List.SetItemText(it->first, TOTALCOMPLETE, ::GetMyNumberFormat(it->second.nTotalComplete));
			strPer.Format("%.2f%%", it->second.nTotalComplete == 0 ? 0 : ((double)it->second.nTodayComplete / (double)it->second.nTotalComplete) * 100.0);
			m_List.SetItemText(it->first, TODAYCOMPLTE, strPer);
			strPer.Format("%.2f%%", it->second.nTotalComplete == 0 ? 0 : ((double)it->second.nNew3MonthCount / (double)it->second.nTotalComplete) * 100.0);
			m_List.SetItemText(it->first, MONTH_3, strPer);
			strPer.Format("%.2f%%", it->second.nTotalComplete == 0 ? 0 : ((double)it->second.nNew6MonthCount / (double)it->second.nTotalComplete) * 100.0);
			m_List.SetItemText(it->first, MONTH_6, strPer);
			strPer.Format("%.2f%%", it->second.nTotalComplete == 0 ? 0 : ((double)it->second.nNew1YearCount / (double)it->second.nTotalComplete) * 100.0);
			m_List.SetItemText(it->first, YEAR_1, strPer);
			strPer.Format("%.2f%%", it->second.nTotalComplete == 0 ? 0 : ((double)it->second.nNew2YearCount / (double)it->second.nTotalComplete) * 100.0);
			m_List.SetItemText(it->first, YEAR_2, strPer);
			strPer.Format("%.2f%%", it->second.nTotalComplete == 0 ? 0 : ((double)it->second.nNew3YearCount / (double)it->second.nTotalComplete) * 100.0);
			m_List.SetItemText(it->first, YEAR_3, strPer);
		}
		else if (m_nListItemType == COUNT_ITEM_TYPE)
		{
			m_List.SetItemText(it->first, TOTALCUSTOMER, ::GetMyNumberFormat(it->second.nTotalCustomer));
			m_List.SetItemText(it->first, TODAYCUSTOMER, ::GetMyNumberFormat(it->second.nNewTodayCustomer));
			m_List.SetItemText(it->first, TOTALCOMPLETE, ::GetMyNumberFormat(it->second.nTotalComplete));
			m_List.SetItemText(it->first, TODAYCOMPLTE, ::GetMyNumberFormat(it->second.nTodayComplete));
			m_List.SetItemText(it->first, MONTH_3, ::GetMyNumberFormat(it->second.nNew3MonthCount));
			m_List.SetItemText(it->first, MONTH_6, ::GetMyNumberFormat(it->second.nNew6MonthCount));
			m_List.SetItemText(it->first, YEAR_1, ::GetMyNumberFormat(it->second.nNew1YearCount));
			m_List.SetItemText(it->first, YEAR_2, ::GetMyNumberFormat(it->second.nNew2YearCount));
			m_List.SetItemText(it->first, YEAR_3, ::GetMyNumberFormat(it->second.nNew3YearCount));
		}
	}

	m_List.Populate();

	OnCbnSelchangeChartFieldCombo();
}
////////////////////////////////////

void CStatChildFormCustomerNew::ListChart()
{
	m_Chart.ClearChart();

	CXTPGridRecord *pRecord;
	CString strTitle, strValue, strTemp, strPrevTitle;
	int nDayChartIndex = -1;
	COleDateTime dtDate;
	for (int i = 0 ; i < m_List.GetRecords()->GetCount() ; i++)
	{
		pRecord = m_List.GetRecords()->GetAt(i);

		if (m_nChartField == 0)
			strValue = m_List.GetItemText(pRecord, TOTALCUSTOMER);
		else if (m_nChartField == 1)
			strValue = m_List.GetItemText(pRecord, TODAYCUSTOMER);
		else if (m_nChartField == 2)
			strValue = m_List.GetItemText(pRecord, TOTALCOMPLETE);
		else if (m_nChartField == 3)
			strValue = m_List.GetItemText(pRecord, TODAYCOMPLTE);
		else if (m_nChartField == 4)
			strValue = m_List.GetItemText(pRecord, MONTH_3);
		else if (m_nChartField == 5)
			strValue = m_List.GetItemText(pRecord, MONTH_6);
		else if (m_nChartField == 6)
			strValue = m_List.GetItemText(pRecord, YEAR_1);
		else if (m_nChartField == 7)
			strValue = m_List.GetItemText(pRecord, YEAR_2);
		else if (m_nChartField == 8)
			strValue = m_List.GetItemText(pRecord, YEAR_3);

		if (m_nListType == DAY_LIST_TYPE)
		{
			strTemp = m_List.GetItemText(pRecord, 0);
			dtDate.SetDate(atoi(strTemp.Left(4)), atoi(strTemp.Mid(5,2)), atoi(strTemp.Mid(8, 2)));
			strTitle = ::GetWeekChartTitle(dtDate);

			if (strTitle != strPrevTitle)
			{
				nDayChartIndex++;
				strPrevTitle = strTitle;
			}

			m_Chart.SetWeekChartItem(strTitle, strValue, dtDate.GetDayOfWeek() - 1, nDayChartIndex);
		}
		else if (m_nListType == WEEK_LIST_TYPE)
		{
			strTitle = m_List.GetItemText(pRecord, 0);

			m_Chart.SetChartItem(strTitle, strValue, 0, i);
		}
		else if (m_nListType == MONTH_LIST_TYPE)
		{
			strTitle = m_List.GetItemText(pRecord, 0);

			m_Chart.SetChartItem(strTitle, strValue, 0, i);
		}
	}

	m_Chart.ChangeSizeCustomLabel();
}

void CStatChildFormCustomerNew::RefreshListDay()	
{
	CMyFormView::RefreshList();
	UpdateData(TRUE);
	m_mapRecordData.clear();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_new_customer_increase_day_2");

	cmd.AddParameter(GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);

	if(!rs.Execute(&cmd)) return;

	m_List.GetRecords()->RemoveAll();
	m_Chart.SetAllSeriesVisible(TRUE);
	m_Chart.SetShowLegend(TRUE);

	CString strDate, strDay;
	int nWeekDay = WEEK_SUNDAY;

	for (int nRecordCount = 0 ; nRecordCount < rs.GetRecordCount() ; nRecordCount++)
	{
		ST_RECORD_DATA stNew;

		rs.GetFieldValue("sDate", strDate);
		rs.GetFieldValue("sDay", strDay);

		rs.GetFieldValue("nTotalCustomer", stNew.nTotalCustomer);
		rs.GetFieldValue("nTotalComplete", stNew.nTotalComplete);
		rs.GetFieldValue("nNewTodayCustomer", stNew.nNewTodayCustomer);
		rs.GetFieldValue("nTodayComplete", stNew.nTodayComplete);
		rs.GetFieldValue("nNew3MonthCount", stNew.nNew3MonthCount);
		rs.GetFieldValue("nNew6MonthCount", stNew.nNew6MonthCount);
		rs.GetFieldValue("nNew1YearCount", stNew.nNew1YearCount);
		rs.GetFieldValue("nNew2YearCount", stNew.nNew2YearCount);
		rs.GetFieldValue("nNew3YearCount", stNew.nNew3YearCount);

		if (strDay == "일요일")			nWeekDay = WEEK_SUNDAY;
		else if (strDay == "월요일")	nWeekDay = WEEK_MONDAY;
		else if (strDay == "화요일")	nWeekDay = WEEK_TUESDAY;
		else if (strDay == "수요일")	nWeekDay = WEEK_WEDNSDAY;
		else if (strDay == "목요일")	nWeekDay = WEEK_THURSDAY;
		else if (strDay == "금요일")	nWeekDay = WEEK_FRIDAY;
		else if (strDay == "토요일")	nWeekDay = WEEK_SATURDAY;

		strDate.Insert(4,'-');
		strDate.Insert(7,'-');
		strDate += "(" + strDay.Left(2) + ")";
		m_List.InsertItem(nRecordCount, strDate);

		m_List.SetItemData(nRecordCount, nWeekDay);

		m_mapRecordData[nRecordCount] = stNew;

		rs.MoveNext();
	}

	rs.Close();

	RefreshListItem();

	RefreshListWeekDay();
}

void CStatChildFormCustomerNew::RefreshListMonth()
{
	CMyFormView::RefreshList();
	UpdateData(TRUE);
	m_mapRecordData.clear();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_new_customer_increase_month_1");

	cmd.AddParameter(GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo); 

	if(!rs.Execute(&cmd)) return;

	m_List.GetRecords()->RemoveAll();
	m_Chart.SetAllSeriesVisible(FALSE);
	m_Chart.SetShowLegend(FALSE);

	CString strDate;

	for (int nRecordCount = 0 ; nRecordCount < rs.GetRecordCount() ; nRecordCount++)
	{
		ST_RECORD_DATA stNew;

		rs.GetFieldValue("sDate", strDate);
		
		rs.GetFieldValue("nTotalCustomer", stNew.nTotalCustomer);
		rs.GetFieldValue("nTotalComplete", stNew.nTotalComplete);
		rs.GetFieldValue("nNewTodayCustomer", stNew.nNewTodayCustomer);
		rs.GetFieldValue("nTodayComplete", stNew.nTodayComplete);
		rs.GetFieldValue("nNew3MonthCount", stNew.nNew3MonthCount);
		rs.GetFieldValue("nNew6MonthCount", stNew.nNew6MonthCount);
		rs.GetFieldValue("nNew1YearCount", stNew.nNew1YearCount);
		rs.GetFieldValue("nNew2YearCount", stNew.nNew2YearCount);
		rs.GetFieldValue("nNew3YearCount", stNew.nNew3YearCount);

		strDate.Insert(4,'-');
		m_List.InsertItem(nRecordCount, strDate);

		m_mapRecordData[nRecordCount] = stNew;

		rs.MoveNext();
	}

	rs.Close();

	RefreshListItem();
}


void CStatChildFormCustomerNew::RefreshListWeekDay()
{
	m_List.ShowAllRow();

	if (m_nWeekDay != WEEK_ALLDAY)
	{
		CXTPGridRecord* pRecord;
		for (int i = 0 ; i < m_List.GetItemCount() ; i++)
		{
			pRecord = m_List.GetRecords()->GetAt(i);
			if (pRecord != NULL)
			{
				DWORD dwItemData = m_List.GetItemData(pRecord);
				if(dwItemData != m_nWeekDay)
					pRecord->SetVisible(FALSE);

				m_List.ChangeRecordBackColor(pRecord, RGB(255,255,255));
			}
		}

		for (int i = 0 ; i < 7 ; i++)
		{
			if (m_nWeekDay != i)
				m_Chart.SetSeriesVisible(FALSE, i);
			else
				m_Chart.SetSeriesVisible(TRUE, i);
		}
	}
	else
	{
		CXTPGridRecord* pRecord;
		COleDateTime dtFrom, dtPrev, dtTemp;
		CString strDate;
		BOOL bRecordColor = FALSE;

		for (int i = 0 ; i < m_List.GetItemCount() ; i++)
		{
			pRecord = m_List.GetRecords()->GetAt(i);
			if (pRecord != NULL)
			{
				strDate = m_List.GetItemText(pRecord, 0);
				dtFrom.SetDate(atoi(strDate.Left(4)), atoi(strDate.Mid(5, 2)), atoi(strDate.Mid(8,2)));
				
				if (i == 0)
				{
					if (dtFrom.GetDayOfWeek() == 1)
						dtPrev = dtFrom + COleDateTimeSpan(7, 0, 0, 0);
					else
					{
						dtTemp = dtFrom;
						while(dtTemp.GetDayOfWeek() != 1)
							dtTemp -= COleDateTimeSpan(1, 0, 0, 0);
						dtPrev = dtTemp + COleDateTimeSpan(7, 0, 0, 0);
					}
				}

				DWORD dwItemData = m_List.GetItemData(pRecord);
				if (dtFrom > dtPrev || (dwItemData == WEEK_SUNDAY && i != 0))
				{
					bRecordColor = !bRecordColor;
					if (dtFrom.GetDayOfWeek() == 1)
						dtPrev = dtFrom + COleDateTimeSpan(7, 0, 0, 0);
					else
					{
						dtTemp = dtFrom;
						while(dtTemp.GetDayOfWeek() != 1)
							dtTemp -= COleDateTimeSpan(1, 0, 0, 0);
						dtPrev = dtTemp + COleDateTimeSpan(7, 0, 0, 0);
					}
				}

				if (bRecordColor == TRUE)
					m_List.ChangeRecordBackColor(pRecord, RGB(255,255,240));
			}
		}

		m_Chart.SetAllSeriesVisible(TRUE);
	}

	m_List.Populate();
}


void CStatChildFormCustomerNew::OnBnClickedRefreshBtn()
{
	if (m_nListType == DAY_LIST_TYPE)			RefreshListDay();
	else if (m_nListType == MONTH_LIST_TYPE)	RefreshListMonth();
	else if (m_nListType == WEEK_LIST_TYPE)		RefreshListWeek();
}

void CStatChildFormCustomerNew::OnCbnSelchangeListTypeCombo()
{
	CString str;
	int nSel = m_cmbListType.GetCurSel();
	if(nSel < 0 || nSel >= m_cmbListType.GetCount())
		return;

	m_cmbListType.GetLBText(nSel,str);
	if( "" == str )
		return;

	m_nListType = nSel;
	AfxGetApp()->WriteProfileInt("Stat", "NewCustomer_ListType", m_nListType);

	m_cmbWeekDay.EnableWindow(FALSE);

	if (nSel == DAY_LIST_TYPE)	//일별
	{
		m_btnDate.OnMenuMonth();
		InitDivisionDate();

		m_cmbWeekDay.EnableWindow(TRUE);
	}
	else if (nSel == WEEK_LIST_TYPE)	//주별
	{
		m_btnDate.OnMenuYear();
		InitDivisionDate();
	}
	else if (nSel == MONTH_LIST_TYPE)	//월별
	{
		m_btnDate.OnMenu4Years();
		InitDivisionDate();
	}

	OnBnClickedRefreshBtn();
}

void CStatChildFormCustomerNew::OnCbnSelchangeWeekDayCombo()
{
	CString str;
	int nSel = m_cmbWeekDay.GetCurSel();
	if(nSel < 0 || nSel >= m_cmbWeekDay.GetCount())
		return;

	m_cmbWeekDay.GetLBText(nSel, str);
	if( "" == str )
		return;

	m_nWeekDay = nSel;
	AfxGetApp()->WriteProfileInt("Stat", "NewCustomer_WeekDayType", m_nWeekDay);

	RefreshListWeekDay();
}

void CStatChildFormCustomerNew::OnCbnSelchangeChartFieldCombo()
{
	CString str;
	int nSel = m_cmbChartField.GetCurSel();
	if(nSel < 0 || nSel >= m_cmbChartField.GetCount())
		return;

	m_cmbChartField.GetLBText(nSel,str);
	if( "" == str )
		return;

	m_Chart.SetTooltipText(str);

	m_nChartField = nSel;
	AfxGetApp()->WriteProfileInt("Stat", "NewCustomer_ChartField", m_nChartField);

	if (m_nChartField < 3)
	{
		m_Chart.SetChartStyle(BAR_CHART_STYLE);
		m_Chart.SetChartYAxisGeneralType();
		m_Chart.SetInitChartYAxisRange();
	}
	else if (m_nListItemType == PERCENT_ITEM_TYPE)
	{
		m_Chart.SetChartStyle(PERCENT_BAR_CHART_STYLE);
		m_Chart.SetChartYAxisLabelFormat("%%");
	}
	else
	{
		m_Chart.SetChartStyle(BAR_CHART_STYLE);
		m_Chart.SetChartYAxisGeneralType();
		m_Chart.SetInitChartYAxisRange();
	}
		
	ListChart();
}

void CStatChildFormCustomerNew::OnCbnSelchangeListItemTypeCombo()
{
	CString str;
	int nSel = m_cmbListItemType.GetCurSel();
	if(nSel < 0 || nSel >= m_cmbListItemType.GetCount())
		return;

	m_cmbListItemType.GetLBText(nSel,str);
	if( "" == str )
		return;

	m_nListItemType = nSel;
	AfxGetApp()->WriteProfileInt("Stat", "NewCustomer_ListItemType", m_nListItemType);

	RefreshListItem();
}

void CStatChildFormCustomerNew::OnDtnDatetimechangeDatetimepicker(NMHDR *pNMHDR, LRESULT *pResult)
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

void CStatChildFormCustomerNew::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CStatChildFormCustomerNew::OnViewExcel()
{
	if(!POWER_CHECK(8900, "통계 엑셀변환", TRUE))
		return;	

	::AddSecurityLog(GetCurBranchInfo()->nCompanyCode, 610, m_List.GetRecords()->GetCount());  
	CMyExcel::ToExcel(&m_List);
}

BOOL CStatChildFormCustomerNew::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->hwnd == m_Chart.GetSafeHwnd())
	{
		m_tooltip.RelayEvent(pMsg);
	}

	if(pMsg->message == WM_SIZE)
	{
		AfxMessageBox("I got it");
	}
	return CMyFormView::PreTranslateMessage(pMsg);
}

void CStatChildFormCustomerNew::NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result)
{
	*result = 0;
	NM_PPTOOLTIP_DISPLAY * pNotify = (NM_PPTOOLTIP_DISPLAY*)pNMHDR;

	if (NULL == pNotify->hwndTool)
	{
		//Order to update a tooltip for a current Tooltip Help
		//He has not a handle of the window
		//If you want change tooltip's parameter than make it's here
	}
	else
	{
		UINT nID = CWnd::FromHandle(pNotify->hwndTool)->GetDlgCtrlID();
		CPoint pt = *pNotify->pt;
		CPoint pPoint, pCliPoint;
		GetCursorPos(&pPoint);
		pCliPoint = pPoint;

		CString strToolTip;
		if (nID == IDC_XTP_CHART)
		{
			m_Chart.ScreenToClient(&pCliPoint);
			strToolTip = m_Chart.GetToolTipText(pCliPoint);
		}

		if (strToolTip.IsEmpty() == FALSE)
		{
			pNotify->ti->sTooltip = strToolTip;
			pt = *pNotify->pt;
			pt.x += 5;
			pt.y += 20;
			*pNotify->pt = pt;
		}
	}
}

void CStatChildFormCustomerNew::OnBnClickedGraphBtn()
{
	if( GetDlgItem(IDC_GRAPH_BTN) == NULL)
	{
		return;
	}

	m_dtpTo.GetTime(m_dtTo);
	m_dtpFrom.GetTime(m_dtFrom);

	CString str;
	GetDlgItem(IDC_GRAPH_BTN)->GetWindowText(str);

	if( str == "그래프 옆으로")
	{
		GetDlgItem(IDC_GRAPH_BTN)->SetWindowText("그래프 아래로");
		m_nArrangeType = 2;
	}
	else if( str == "그래프 아래로")
	{
		GetDlgItem(IDC_GRAPH_BTN)->SetWindowText("그래프 감추기");
		m_nArrangeType = 1;
	}
	else if( str == "그래프 감추기")
	{
		GetDlgItem(IDC_GRAPH_BTN)->SetWindowText("그래프 옆으로");
		m_nArrangeType = 0;
	}
	UpdateData(FALSE);

	RefreshSize();
}

void CStatChildFormCustomerNew::RefreshSize()
{
	if (m_nArrangeType == 0)
		RearrangeControlsForHideGraph();
	else if (m_nArrangeType == 1)
		RearrangeControlsForBottomGraph();
	else if (m_nArrangeType == 2)
		RearrangeControlsForRightGraph();

	m_Chart.ChangeSizeCustomLabel();
}

void CStatChildFormCustomerNew::InitLayoutRight()
{
	if(NULL != GetDlgItem(IDC_GRAPH_BTN))
		GetDlgItem(IDC_GRAPH_BTN)->SetWindowText("그래프 아래로");

	m_nArrangeType = 2;
}

void CStatChildFormCustomerNew::RearrangeControlsForBottomGraph()
{
	CRect rc;
	GetClientRect(&rc);

	CRect rcList = rc;
	rcList.top = m_ptBaseWndPos.y;
	rcList.bottom = (int)(rc.Height() * 0.6);
	m_List.MoveWindow(&rcList);

	CRect rcGraph = rc;
	rcGraph.top = rcList.bottom + 5;

	m_Chart.MoveWindow(&rcGraph);

	SetResizeVer(IDC_REPORT_LIST, IDC_XTP_CHART);
}

void CStatChildFormCustomerNew::RearrangeControlsForHideGraph()
{
	CRect rc;
	GetClientRect(&rc);

	CRect rcList = rc;
	rcList.top = m_ptBaseWndPos.y;
	rcList.right = rc.Width() - 5;
	m_List.MoveWindow(&rcList);

	CRect rcGraph(0,0,0,0);

	m_Chart.MoveWindow(&rcGraph);

	//SetResize(IDC_REPORT_LIST, sizingRightBottom);
}

void CStatChildFormCustomerNew::RearrangeControlsForRightGraph()
{
	CRect rc;
	GetClientRect(&rc);

	CRect rcList = rc;
	rcList.top =  m_ptBaseWndPos.y;
	rcList.right = (int)(rc.Width() * 0.5);
	m_List.MoveWindow(&rcList);

	CRect rcGraph = rc;
	rcGraph.top = rcList.top;
	rcGraph.left = rcList.right + 5;

	m_Chart.MoveWindow(&rcGraph);

	SetResizeHori(IDC_REPORT_LIST, IDC_XTP_CHART);
}

void CStatChildFormCustomerNew::OnSize(UINT nType, int cx, int cy)
{
	CMyFormView::OnSize(nType, cx, cy);

	if (m_Chart.GetSafeHwnd() != NULL &&
		m_List.GetSafeHwnd() != NULL)
		RefreshSize();
}