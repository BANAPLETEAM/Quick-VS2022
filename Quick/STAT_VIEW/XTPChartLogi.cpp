#include "StdAfx.h"
#include "XTPChartLogi.h"
#include <math.h>

CXTPChartLogi::CXTPChartLogi(void)
{
	m_strTitle = "";
	m_nSeriesCount = 2;
	m_nChartStyle = 3;

	m_bShowLabel = TRUE;
	m_bShowLegend = FALSE;
	m_bUseZoom = FALSE;
	m_bUseScroll = FALSE;
	m_bShowMarker = TRUE;

	map_AxisLabel.clear();
	//m_nRemoveIndex = 0;
}

CXTPChartLogi::~CXTPChartLogi(void)
{
}

void CXTPChartLogi::ChartCreate(CString strTitle, int nChartStyle /* = BAR_CHART_STYLE */, int nSeriesCount /* = 1 */, BOOL bShowLabel /* = FALSE */, BOOL bShowLegend /* = FALSE */, BOOL bUseZoom /* = FALSE */, BOOL bUseScroll /* = FALSE */)
{
	m_strTitle = strTitle;
	m_nChartStyle = nChartStyle;
	m_nSeriesCount = nSeriesCount;
	m_bShowLabel = bShowLabel;
	m_bShowLegend = bShowLegend;
	m_bUseZoom = bUseZoom;
	m_bUseScroll = bUseScroll;

	CXTPChartContent* pContent = GetContent();
	pContent->GetLegend()->SetVisible(m_bShowLegend);

	CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	pTitle->SetText(strTitle);

	CXTPChartSeries* pSeries;
	for (int i = 0 ; i < m_nSeriesCount ; i++)
	{
		pSeries = pContent->GetSeries()->Add(new CXTPChartSeries());
	}

	//ChangeChartStyle();
}

void CXTPChartLogi::ChangeChartStyle()
{
	CXTPChartContent* pContent = GetContent();
	pContent->GetLegend()->SetVisible(m_bShowLegend);

	CXTPChartTitle* pTitle = pContent->GetTitles()->GetAt(0);
	pTitle->SetText(m_strTitle);

	for (int i = 0 ; i < GetContent()->GetSeries()->GetCount() ; i++)
	{
		CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(i);
		switch (m_nChartStyle)
		{
		case POINT_CHART_STYLE:
			{
				pSeries->SetStyle(new CXTPChartPointSeriesStyle());
				CXTPChartPointSeriesStyle* pStyle = (CXTPChartPointSeriesStyle*)pSeries->GetStyle();
				pStyle->GetMarker()->SetVisible(m_bShowMarker);
				pStyle->GetMarker()->SetSize(3);
			}
			break;
		case LINE_CHART_STYLE:
			{
				pSeries->SetStyle(new CXTPChartLineSeriesStyle());
				CXTPChartLineSeriesStyle* pStyle = (CXTPChartLineSeriesStyle*)pSeries->GetStyle();
				pStyle->GetMarker()->SetVisible(m_bShowMarker);
				pStyle->GetMarker()->SetSize(4);
				pStyle->GetLineStyle()->SetThickness(4);
			}
			break;
		case SPLINE_CHART_STYLE:
			{
				pSeries->SetStyle(new CXTPChartSplineSeriesStyle());
				CXTPChartSplineSeriesStyle* pStyle = (CXTPChartSplineSeriesStyle*)pSeries->GetStyle();
				pStyle->GetMarker()->SetVisible(m_bShowMarker);
				pStyle->GetMarker()->SetSize(4);
				pStyle->GetLineStyle()->SetThickness(4);
			}
			break;
		case BAR_CHART_STYLE:
			{
				pSeries->SetStyle(new CXTPChartBarSeriesStyle());
				CXTPChartBarSeriesStyle* pStyle = (CXTPChartBarSeriesStyle*)pSeries->GetStyle();
				pStyle->SetBarWidth(0.8);
			}
			break;
		case PERCENT_BAR_CHART_STYLE:
			{
				pSeries->SetStyle(new CXTPChartBarSeriesStyle());
				CXTPChartBarSeriesStyle* pStyle = (CXTPChartBarSeriesStyle*)pSeries->GetStyle();
				pStyle->SetBarWidth(0.8);

				CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());

				pDiagram->GetAxisY()->GetRange()->SetAutoRange(FALSE);
				pDiagram->GetAxisY()->GetRange()->SetMinValue(0);
				pDiagram->GetAxisY()->GetRange()->SetMaxValue(100);
			}
			break;
		case STACKEDBAR_CHART_STYLE:
			{
				pSeries->SetStyle(new CXTPChartStackedBarSeriesStyle());
				CXTPChartStackedBarSeriesStyle* pStyle = (CXTPChartStackedBarSeriesStyle*)pSeries->GetStyle();
				pStyle->SetBarWidth(0.8);
				//pStyle->SetStackGroup(i);
			}
			break;
		case AREA_CHART_STYLE:
			{
				pSeries->SetStyle(new CXTPChartAreaSeriesStyle());
				CXTPChartAreaSeriesStyle* pStyle = (CXTPChartAreaSeriesStyle*)pSeries->GetStyle();
				pStyle->GetMarker()->SetVisible(m_bShowMarker);
				pStyle->GetMarker()->SetSize(3);
			}
			break;
		case SPLINE_AREA_CHART_STYLE:
			{
				pSeries->SetStyle(new CXTPChartSplineAreaSeriesStyle());
				CXTPChartSplineAreaSeriesStyle* pStyle = (CXTPChartSplineAreaSeriesStyle*)pSeries->GetStyle();
				pStyle->GetMarker()->SetVisible(m_bShowMarker);
				pStyle->GetMarker()->SetSize(3);
			}
			break;
		case BUBBLE_CHART_STYLE:
			pSeries->SetStyle(new CXTPChartBubbleSeriesStyle());
			break;
		case PIE_CHART_STYLE:
			pSeries->SetStyle(new CXTPChartPieSeriesStyle());
			break;
		case DOUGHNUT_CHART_STYLE:
			{
				CXTPChartPieSeriesStyle* pPieStyle = (CXTPChartPieSeriesStyle*)pSeries->SetStyle(new CXTPChartPieSeriesStyle());
				pPieStyle->SetHolePercent(40);
				pPieStyle->SetRotation(20);
			}
			break;
		}

		pSeries->SetName(GetLegendFormat(i));

		if (i == 0)
			pSeries->GetStyle()->SetColor(CXTPChartColor::Blue);
		else if (i == 1)
			pSeries->GetStyle()->SetColor(CXTPChartColor::Coral);
		else if (i == 2)
			pSeries->GetStyle()->SetColor(CXTPChartColor::IndianRed);
		else if (i == 3)
			pSeries->GetStyle()->SetColor(CXTPChartColor::Orange);
		else if (i == 4)
			pSeries->GetStyle()->SetColor(CXTPChartColor::Violet);
		else if (i == 5)
			pSeries->GetStyle()->SetColor(CXTPChartColor::SeaGreen);
		else if (i == 6)
			pSeries->GetStyle()->SetColor(CXTPChartColor::Red);
		else
			pSeries->GetStyle()->SetColor(CXTPChartColor::LemonChiffon);

		//pSeries->SetArgumentScaleType(xtpChartScaleNumerical);

		CXTPChartBarSeriesStyle* pStyle = (CXTPChartBarSeriesStyle*)pSeries->GetStyle();
		pStyle->GetLabel()->SetVisible(m_bShowLabel);

		// pStyle->SetColorEach(TRUE); 그래프마다 색 다 다르게

		//pDiagram->GetAxisX()->GetGridLines()->SetMinorVisible(FALSE);
		//pDiagram->GetAxisX()->GetGridLines()->SetVisible(FALSE);
		//pDiagram->GetAxisX()->SetInterlaced(FALSE);
		//pDiagram->GetAxisX()->GetRange()->SetSideMargins(FALSE);

		if (m_nChartStyle != PIE_CHART_STYLE && m_nChartStyle != DOUGHNUT_CHART_STYLE)
		{
			CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());
			pDiagram->SetAllowZoom(m_bUseZoom);
			pDiagram->SetAllowScroll(m_bUseScroll);

			//pDiagram->GetAxisY()->GetLabel()->GetFormat()->SetCategory(xtpChartNumber);
			//pDiagram->GetAxisY()->GetLabel()->GetFormat()->SetDecimalPlaces(0);	//소수점제거
		}
		
	}
}

void CXTPChartLogi::SetLegendFormat(CString strLegendFormat, int nSeriesIndex)
{
	if (nSeriesIndex > 7)		return;
	
	map_Legend[nSeriesIndex] = strLegendFormat;

	ChangeChartStyle();
}

CString CXTPChartLogi::GetLegendFormat(int nSeriesIndex)
{
	if (nSeriesIndex > 7)		return "";

	map<int, CString>::iterator it = map_Legend.find(nSeriesIndex);
	if (it == map_Legend.end())
	{
		return "";
	}
	return it->second;
}

void CXTPChartLogi::SetChartXAxisLabel(CString strLabel)
{
	CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(0);

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());

	pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisX()->GetTitle()->SetText(strLabel);
}

void CXTPChartLogi::SetChartYAxisLabel(CString strLabel)
{
	CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(0);

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());

	pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisY()->GetTitle()->SetText(strLabel);
}

void CXTPChartLogi::SetChartYAxisNumberType()
{
	CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(0);
	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());

	pDiagram->GetAxisY()->GetLabel()->GetFormat()->SetCategory(xtpChartNumber);
	pDiagram->GetAxisY()->GetLabel()->GetFormat()->SetDecimalPlaces(0);	//소수점제거
	pDiagram->GetAxisY()->GetLabel()->SetFormat("{V}");
}

void CXTPChartLogi::SetChartYAxisGeneralType()
{
	CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(0);
	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());

	pDiagram->GetAxisY()->GetLabel()->GetFormat()->SetCategory(xtpChartGeneral);
	pDiagram->GetAxisY()->GetLabel()->SetFormat("{V}");
}

void CXTPChartLogi::SetChartYAxisLabelFormat(CString strFormat)
{
	CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(0);

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());

	CString strTemp;
	if (strFormat == "%%")
		pDiagram->GetAxisY()->GetLabel()->SetFormat("{V}%%");
	else
	{
		strTemp.Format("{V}%s", strFormat);
		pDiagram->GetAxisY()->GetLabel()->SetFormat(strTemp);
	}

	//pStyle->GetLabel()->SetFormat(_T("{V} Million"));
}

void CXTPChartLogi::SetAngle(int nAngle)
{
	CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(0);

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());

	pDiagram->GetAxisX()->GetLabel()->SetAngle(nAngle);
}

void CXTPChartLogi::SetShowZeroLevel(BOOL bShow)
{
	CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(0);

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());

	pDiagram->GetAxisY()->GetRange()->SetShowZeroLevel(bShow);
	pDiagram->GetAxisY()->GetRange()->SetAutoRange(bShow);
}

void CXTPChartLogi::SetChartYAxisRange(double dMin, double dMax)
{
	if (dMin == 0)	return;
	
	CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(0);

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());
	ASSERT (pDiagram);
	
	CString strMin, strMax;
	strMin.Format("%.0f", dMin);
	strMax.Format("%.0f", dMax);

	int nMinLen = strMin.GetLength();
	int nMaxLen = strMax.GetLength();

	int nMinTenLen = 0, nMaxTenLen = 0;
	if (nMinLen > 3)		nMinTenLen = nMinLen - 3;
	else if (nMinLen != 0)	nMinTenLen = nMinLen - 1;

	if (nMaxLen > 3)		nMaxTenLen = nMaxLen - 3;
	else if (nMaxLen != 0)	nMaxTenLen = nMaxLen - 1;
	

	double dTempMin = atof(strMin.Left(nMinLen - nMinTenLen)) * pow(10, nMinTenLen);
	double dTempMax = (atof(strMax.Left(nMaxLen - nMaxTenLen)) + 1) * pow(10, nMaxTenLen);

	//pDiagram->GetAxisY()->GetRange()->SetViewAutoRange(FALSE);
	//pDiagram->GetAxisY()->GetRange()->SetViewMinValue(dTempMin);
	//pDiagram->GetAxisY()->GetRange()->SetViewMaxValue(dTempMax);

	pDiagram->GetAxisY()->GetRange()->SetAutoRange(FALSE);
	pDiagram->GetAxisY()->GetRange()->SetMinValue(dTempMin);
	pDiagram->GetAxisY()->GetRange()->SetMaxValue(dTempMax);
}


void CXTPChartLogi::SetInitChartYAxisRange()
{
	for (int i = 0 ; i < GetContent()->GetSeries()->GetCount() ; i++)
	{
		CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(i);

		CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());

		pDiagram->GetAxisY()->GetRange()->SetAutoRange(TRUE);
	}
}


void CXTPChartLogi::SetSeriesVisible(BOOL bType, int nSeriesCount)
{
	CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(nSeriesCount);
	pSeries->SetVisible(bType);
}

void CXTPChartLogi::SetAllSeriesVisible(BOOL bType)
{
	CXTPChartSeriesCollection* pSeriesCollect = GetContent()->GetSeries();
	CXTPChartSeries* pSeries = pSeriesCollect->GetAt(0);
	pSeries->SetVisible(TRUE);
	for (int i = 1 ; i < pSeriesCollect->GetCount() ; i++)
	{
		pSeries = pSeriesCollect->GetAt(i);
		pSeries->SetVisible(bType);
	}
}

CString CXTPChartLogi::GetToolTipText(CPoint pPoint)
{
	CObject *pObject = HitTest(pPoint);
	
	if(pObject != NULL)
	{
		if(pObject->IsKindOf(RUNTIME_CLASS(CXTPChartSeriesPoint)))
		{
			CXTPChartSeriesPoint* pChartPoint = (CXTPChartSeriesPoint*)pObject;
			CXTPChartString strText = pChartPoint->GetTooltipText();
			return strText;
		}
	}

	/*CXTPChartSeriesPoint* pChartPoint = (CXTPChartSeriesPoint*)HitTest(pPoint);
	if (pChartPoint != NULL)
	{
		//pChartPoint->m_bSpecial;
		if (pChartPoint->GetPaletteIndex() == 0 &&  pChartPoint->GetInternalArgumentValue() >= 0 && pChartPoint->m_bSpecial == FALSE)
		{
			CXTPChartString strText = pChartPoint->GetTooltipText();
			return strText;
		}
	}*/
	return "";
}

void CXTPChartLogi::ClearChart()
{
	CXTPChartSeriesCollection* pSeriesCollect = GetContent()->GetSeries();
	for (int i = 0 ; i < pSeriesCollect->GetCount() ; i++)
	{
		CXTPChartSeries* pSeries = pSeriesCollect->GetAt(i);
		pSeries->GetPoints()->RemoveAll();
	}

	map_AxisLabel.clear();
}

void CXTPChartLogi::SetChartItem(CString strTitle, CString strText, int nSeriesNumber, int nIndex)
{
	CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(nSeriesNumber);
	CXTPChartSeriesPoint* pPoint;

	if (!pSeries)
	{
		return;
	}

	if (nSeriesNumber == 0)
	{
		pPoint = new CXTPChartSeriesPoint(strTitle, atof(LF->RemoveComma(strText)), atof(LF->RemoveComma(strText)));
		pPoint->SetInternalArgumentValue(nIndex + 100);
	}
	else
	{

		CXTPChartSeriesPoint* pOriginPoint = GetContent()->GetSeries()->GetAt(0)->GetPoints()->GetAt(nIndex);
		double dTemp = pOriginPoint->GetArgumentValue();
		pPoint = new CXTPChartSeriesPoint(strTitle, atof(LF->RemoveComma(strText)), atof(LF->RemoveComma(strText)));
	}

	CXTPChartString strString;
	strString.Format("%s\n%s\n%s", m_strTooltipText, strTitle, strText);
	pPoint->SetTooltipText(strString);

	pSeries->GetPoints()->Add(pPoint);

	map_AxisLabel[nIndex] = strTitle;
}

void CXTPChartLogi::SetChartItem(CString strTitle, int nValue, int nSeriesNumber, int nIndex)
{
	CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(nSeriesNumber);
	CXTPChartSeriesPoint* pPoint;

	if (!pSeries)
	{
		return;
	}

	if (nSeriesNumber == 0)
	{
		pPoint = new CXTPChartSeriesPoint(strTitle, nValue, nValue);
		pPoint->SetInternalArgumentValue(nIndex + 100);
	}
	else
	{
		CXTPChartSeriesPoint* pOriginPoint = GetContent()->GetSeries()->GetAt(0)->GetPoints()->GetAt(nIndex);
		double dTemp = pOriginPoint->GetArgumentValue();
		pPoint = new CXTPChartSeriesPoint(strTitle, nValue, nValue);
	}

	CXTPChartString strString;
	strString.Format("%s\n%s\n%d", GetLegendFormat(nSeriesNumber), strTitle, nValue);
	pPoint->SetTooltipText(strString);

	pSeries->GetPoints()->Add(pPoint);

	map_AxisLabel[nIndex] = strTitle;
}

void CXTPChartLogi::SetDateChartItem(CString strTitle, int nValue, int nSeriesNumber, int nIndex, COleDateTime dtDate)
{
	CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(nSeriesNumber);
	CXTPChartSeriesPoint* pPoint;

	if(!pSeries)
	{
		//GetLog()->Print("CXTPChartLogi::SetDateChartItem null pSeries");
		return;
	}

	if (nSeriesNumber == 0)
	{
		CString strTemp;
		strTemp.Format("%d-%02d-%02d", dtDate.GetYear(), dtDate.GetMonth(), dtDate.GetDay());
		pPoint = new CXTPChartSeriesPoint(strTemp, nValue, nValue);
	}
	else
	{
		CXTPChartSeriesPoint* pOriginPoint = GetContent()->GetSeries()->GetAt(0)->GetPoints()->GetAt(nIndex);	
		double dTemp = pOriginPoint->GetArgumentValue();
		pPoint = new CXTPChartSeriesPoint(strTitle, nValue, nValue);
	}

	CXTPChartString strString;
	strString.Format("%s\n%d\n%d-%02d-%02d", GetLegendFormat(nSeriesNumber), nValue, dtDate.GetYear(), dtDate.GetMonth(), dtDate.GetDay());
	pPoint->SetTooltipText(strString);
	
	pSeries->GetPoints()->Add(pPoint);
}

void CXTPChartLogi::SetPieChartItem(CString strTitle, CString strText, int nSeriesNumber, int nIndex, COLORREF clrText)
{
	CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(nSeriesNumber);
	CXTPChartSeriesPoint* pPoint;

	if(!pSeries)
	{
		//GetLog()->Print("CXTPChartLogi::SetPieChartItem null pSeries");
		return;
	}

	if (nSeriesNumber == 0)
	{
		pPoint = new CXTPChartSeriesPoint(strTitle, atof(LF->RemoveComma(strText)), atof(LF->RemoveComma(strText)));
	}
	else
	{
		CXTPChartSeriesPoint* pOriginPoint = GetContent()->GetSeries()->GetAt(0)->GetPoints()->GetAt(nIndex);	
		double dTemp = pOriginPoint->GetArgumentValue();
		pPoint = new CXTPChartSeriesPoint(strTitle, atof(LF->RemoveComma(strText)), atof(LF->RemoveComma(strText)));
	}

	CXTPChartString strString;
	strString.Format("%s\n%s", strTitle, strText);
	pPoint->SetTooltipText(strString);
	pPoint->SetLabelText(strText);

	pSeries->GetPoints()->Add(pPoint);
}

void CXTPChartLogi::SetWeekChartItem(CString strTitle, CString strText, int nSeriesNumber, int nIndex)
{
	CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(nSeriesNumber);
	CXTPChartSeriesPoint* pPoint;

	if (!pSeries)
	{
		return;
	}

	pPoint = new CXTPChartSeriesPoint(strTitle, atof(LF->RemoveComma(strText)), atof(LF->RemoveComma(strText)));

	CXTPChartString strString;
	strString.Format("%s %s\n%s\n%s", m_strTooltipText, GetLegendFormat(nSeriesNumber), strText, strTitle);
	pPoint->SetTooltipText(strString);
	pPoint->SetInternalArgumentValue(nIndex + 100);

	pSeries->GetPoints()->Add(pPoint);

	map_AxisLabel[nIndex] = strTitle;
}

void CXTPChartLogi::Sort(int nSeriesNumber)
{
	CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(nSeriesNumber);
	CXTPChartSeriesPointCollection* pPoints = pSeries->GetPoints();

	int nCount = pPoints->GetCount();

	if (nCount ==  0)	return;	

	double dTempValue[200];
	CString strTempTitle[200];
	CString strTooltipText[200];

	//double *dTempValue;
	//dTempValue = new double(nCount);

	map_AxisLabel.clear();
	CXTPChartSeriesPoint* pPoint;
	for (int i = 0 ; i < nCount ; i++)
	{
		pPoint = pPoints->GetAt(i);
		dTempValue[i] = pPoint->GetValue(0);
		strTempTitle[i] = pPoint->GetArgument();
		strTooltipText[i] = pPoint->GetTooltipText();
	}

	QuickSort(dTempValue, strTempTitle, strTooltipText, 0, nCount);

	pSeries->GetPoints()->RemoveAll();

	for (int j = 0; j < nCount; j++)
	{
		pPoint = new CXTPChartSeriesPoint(strTempTitle[j], dTempValue[j], dTempValue[j]);
		pPoint->SetInternalArgumentValue(100 + j);
		pPoint->SetTooltipText(strTooltipText[j]);
		pSeries->GetPoints()->Add(pPoint);
		map_AxisLabel[j] = strTempTitle[j];
	}


	//delete dTempValue;
}

void CXTPChartLogi::QuickSort(double dData[], CString strTitle[], CString strTooltipText[], int nBegin, int nEnd)
{
	if (nBegin + 1 >= nEnd)	return;
	
	double dIndexData = dData[nBegin];
	double dTmpData;

	CString strTmpData, strTmpTooltip;

	int i = 0, j = 0;

	while (true)
	{
		for (i = nBegin + 1 ; i < nEnd ; i++)
		{
			if (dData[i] < dIndexData)	break;
		}
		for (j = nEnd - 1 ; j > nBegin ; j--)
		{
			if (dData[j] > dIndexData)	break;
		}

		if (i >= j)	break;
		
		dTmpData = dData[i];
		dData[i] = dData[j];
		dData[j] = dTmpData;

		strTmpData = strTitle[i];
		strTitle[i] = strTitle[j];
		strTitle[j] = strTmpData;

		strTmpTooltip = strTooltipText[i];
		strTooltipText[i] = strTooltipText[j];
		strTooltipText[j] = strTmpTooltip;
	}

	dTmpData = dData[j];
	dData[j] = dData[nBegin];
	dData[nBegin] = dTmpData;

	strTmpData = strTitle[j];
	strTitle[j] = strTitle[nBegin];
	strTitle[nBegin] = strTmpData;

	strTmpTooltip = strTooltipText[j];
	strTooltipText[j] = strTooltipText[nBegin];
	strTooltipText[nBegin] = strTmpTooltip;

	QuickSort(dData, strTitle, strTooltipText, nBegin, j);
	QuickSort(dData, strTitle, strTooltipText, j+1, nEnd);
}

void CXTPChartLogi::ChangeSizeCustomLabel()
{
	CRect rc;
	GetClientRect(&rc);

	map<int, CString>::iterator it = map_AxisLabel.begin();
	int nMapCount = map_AxisLabel.size();
	double dLabelsize = 1.0;
	if (nMapCount > 0)
	{
		dLabelsize = it->second.GetLength();
		if (dLabelsize > 7) dLabelsize = 1;
		else if (dLabelsize > 4) dLabelsize = 0.7;
		else if (dLabelsize > 2) dLabelsize = 0.4;
	}

	int nRe = nMapCount == 0 ? 100 : (int)(rc.right / (nMapCount * dLabelsize));
	int nLabelCount = 0;

	if (0 < nRe && nRe <= 4)		nLabelCount = 36;
	else if (4 < nRe && nRe <= 8)		nLabelCount = 25;
	else if (8 < nRe && nRe <= 10)		nLabelCount = 16;
	else if (10 < nRe && nRe <= 15)		nLabelCount = 8;
	else if (15 < nRe && nRe <= 20)		nLabelCount = 5;
	else if (20 < nRe && nRe <= 30)		nLabelCount = 4;
	else if (30 < nRe && nRe <= 40)		nLabelCount = 3;
	else if (40 < nRe && nRe <= 50)		nLabelCount = 2;
	else if (50 < nRe && nRe <= 60)		nLabelCount = 2;
	else if (60 < nRe && nRe <= 70)		nLabelCount = 1;
	else if (70 < nRe && nRe <= 80)		nLabelCount = 1;
	else if (80 < nRe && nRe <= 90)		nLabelCount = 1;
	else if (90 < nRe && nRe < 100)		nLabelCount = 1;

	CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(0);
	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries->GetDiagram());

	pDiagram->GetAxisX()->GetCustomLabels()->RemoveAll();

	
	for (int i = 0 ; i < nMapCount ; i = i + 1 + nLabelCount)
	{
		//it = map_AxisLabel.find(i + m_nRemoveIndex);
		it = map_AxisLabel.find(i);

		if (it != map_AxisLabel.end())
		{
			CXTPChartAxisCustomLabel* pLabel = new CXTPChartAxisCustomLabel();
			pLabel->SetAxisValue(it->second);//원래거
			pLabel->SetText(it->second);		//변경할거

			pDiagram->GetAxisX()->GetCustomLabels()->Add(pLabel);
		}
	}
}
/*
void CXTPChart::RemoveFirstZeroData()
{	
	CXTPChartSeries* pSeries = GetContent()->GetSeries()->GetAt(0);
	CXTPChartSeriesPointCollection* pPoints = pSeries->GetPoints();
	CXTPChartSeriesPoint* pPoint;

	m_nRemoveIndex = 0;
	CString strTitle;
	int nCount = pSeries->GetPoints()->GetCount();
	for (int i = 0 ; i < nCount ; i++, m_nRemoveIndex++)
	{
		pPoint = pPoints->GetAt(i);
		if (pPoint->GetValue(0) == 0)
		{
			pPoints->RemoveAt(i);
			i -= 1;
			nCount -= 1;
			map_AxisLabel.erase(m_nRemoveIndex);
		}
		else
		{
			break;
		}
	}
}
*/