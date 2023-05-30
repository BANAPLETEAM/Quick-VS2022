#pragma once
/*
class CXTPChartPoint : public CXTPChartSeriesPoint
{	
public:
	CXTPChartPoint(const CXTPChartString& strArgument, double dValue1, double dValue2):CXTPChartSeriesPoint(strArgument, dValue1, dValue2)
	{
		bToolTip = FALSE;
	}

	CXTPChartPoint(double dArgument, double dValue1, double dValue2):CXTPChartSeriesPoint(dArgument, dValue1, dValue2)
	{
		bToolTip = FALSE;
	}

	BOOL GetToolTipCheck()
	{
		return bToolTip;
	}
	void UseToolTip()
	{
		bToolTip = TRUE;
	}

	bool bToolTip;

	void SetArg(CString sArg)
	{
		m_strArgument = sArg;
	}

	void SetDoubleArg(double dArg)
	{
		m_dArgument = dArg;
		m_dInternalArgument = dArg;
	}

	void SetIndex(int n)
	{
		m_nIndex = n;
	}

	void SetLength(int n)
	{
		m_nLength = n;
	}
	void SetPaletteIndex(int n)
	{
		m_nPaletteIndex = n;
	}
};*/

enum{
	POINT_CHART_STYLE,
	LINE_CHART_STYLE,
	SPLINE_CHART_STYLE,
	BAR_CHART_STYLE,
	PERCENT_BAR_CHART_STYLE,
	STACKEDBAR_CHART_STYLE,
	AREA_CHART_STYLE,
	SPLINE_AREA_CHART_STYLE,
	BUBBLE_CHART_STYLE,
	PIE_CHART_STYLE,
	DOUGHNUT_CHART_STYLE
};

enum {
	WEEK_SUNDAY,
	WEEK_MONDAY,
	WEEK_TUESDAY,
	WEEK_WEDNSDAY,
	WEEK_THURSDAY,
	WEEK_FRIDAY,
	WEEK_SATURDAY,
	WEEK_ALLDAY
};

class CXTPChartLogi :
	public CXTPChartControl
{
public:
	CXTPChartLogi(void);
	~CXTPChartLogi(void);

	CString m_strTitle;
	int m_nSeriesCount;
	int m_nChartStyle;
	CString m_strTooltipText;

	BOOL m_bShowLabel;
	BOOL m_bShowLegend;
	BOOL m_bUseZoom;
	BOOL m_bUseScroll;
	BOOL m_bShowMarker;

	map<int, CString> map_Legend;

	void ChartCreate(CString strTitle, int nChartStyle = 3, int nSeriesCount = 1, BOOL bShowLabel = FALSE, BOOL bShowLegend = FALSE, BOOL bUseZoom = FALSE, BOOL bUseScroll = FALSE);
	void SetTitle(CString strTitle)					{ m_strTitle = strTitle;		ChangeChartStyle();	};
	void SetTooltipText(CString strToolTipText)		{ m_strTooltipText = strToolTipText;				};
	void SetChartStyle(int nChartStyle)				{ m_nChartStyle = nChartStyle;	ChangeChartStyle();	};
	void SetShowLabel(BOOL bShowLabel)				{ m_bShowLabel = bShowLabel;	ChangeChartStyle();	};
	void SetShowLegend(BOOL bShowLegend)			{ m_bShowLegend = bShowLegend;	ChangeChartStyle();	};
	void SetLegendFormat(CString strLegendFormat, int nSeriesIndex);
	CString GetLegendFormat(int nSeriesIndex);
	void SetUseZoom(BOOL bUseZoom)					{ m_bUseZoom = bUseZoom;		ChangeChartStyle();	};
	void SetUseScroll(BOOL bUseScroll)				{ m_bUseScroll = bUseScroll;	ChangeChartStyle();	};
	void SetShowMarker(BOOL bShow)					{ m_bShowMarker = bShow;		ChangeChartStyle();	};
	void SetChartXAxisLabel(CString strLabel);
	void SetChartYAxisLabel(CString strLabel);
	void SetAngle(int nAngle);
	void SetShowZeroLevel(BOOL bShow);
	void SetInitChartYAxisRange();
	void SetChartYAxisRange(double dMin, double dMax);
	void SetChartYAxisNumberType();
	void SetChartYAxisGeneralType();
	void SetChartYAxisLabelFormat(CString strFormat);

	void ChangeChartStyle();
	void SetSeriesVisible(BOOL bType, int nSeriesIndex);
	void SetAllSeriesVisible(BOOL bType);
	CString GetToolTipText(CPoint pPoint);

	void Sort(int nSeriesNumber);
	void QuickSort(double dData[], CString strTitle[], CString strTooltipText[], int nBegin, int nEnd);
	
	//일반 For문 이용
	void ClearChart();
	void SetChartItem(CString strTitle, CString strText, int nSeriesNumber, int nIndex);
	void SetChartItem(CString strTitle, int nValue, int nSeriesNumber, int nIndex);
	void SetWeekChartItem(CString strTitle, CString strText, int nSeriesNumber, int nIndex);
	void SetDateChartItem(CString strTitle, int nValue, int nSeriesNumber, int nIndex, COleDateTime dtDate);
	void SetPieChartItem(CString strTitle, CString strText, int nSeriesNumber, int nIndex, COLORREF clrText);

	map<int, CString> map_AxisLabel;
	void ChangeSizeCustomLabel();
};