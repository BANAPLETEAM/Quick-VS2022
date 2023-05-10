#include "stdafx.h"
#include "MakeHtmlTable.h"

CMakeHtmlTable::CMakeHtmlTable(void)
{
	m_strHtml = "";
	m_nRow = 0;
	m_nCol = 0;
	m_nTotalRow = 0;
	m_nTotalCol = 0;
	m_nBorder = 1;
	m_bAddRow = TRUE;
}

CMakeHtmlTable::~CMakeHtmlTable(void)
{
}


void CMakeHtmlTable::MakeCol(CString strValue, int nWidth)
{
	CString col;


	if(m_bAddRow)
	{
		col += "<tr>";
		m_bAddRow = FALSE;
	}

	if(nWidth > 0)
	{
		CString temp;
		temp.Format("<td width = %d>", nWidth);
		col += temp;
	}
	else
	{
		col += "<td>";
	}

	col += strValue;
	col += "</td>";

	m_strHtml += col;
}

void CMakeHtmlTable::AddCol(CString strValue, int nWidth)
{
	strValue.Replace("<", "[");
	strValue.Replace(">", "]");
	MakeCol(strValue, nWidth);
}

void CMakeHtmlTable::AddCol(int nValue, int nWidth)
{
	char buffer[20];
	MakeCol(ltoa(nValue, buffer, 10), nWidth);
}


void CMakeHtmlTable::AddImageList(int nID, CString strValue, int nWidth)
{
	strValue.Replace("<", "[");
	strValue.Replace(">", "]");

	CString temp;
	temp.Format("<ilst index = %d>%s", nID, strValue);
	MakeCol(temp, nWidth);
}


void CMakeHtmlTable::AddRow()
{
	m_strHtml += "</tr>";
	m_bAddRow = TRUE;
}


CString CMakeHtmlTable::GetHtmlTable() 
{
	CString strTitle, strHeader, strTail;
	strHeader.Format("<table border=%d bordercolor=#D0D0FF>", m_nBorder);

	if(m_strTitle.GetLength() > 0)
		strTitle.Format("<center><h2>%s</h2></center>", m_strTitle); 

	if(m_strHtml.Right(4) != "</tr>")
		strTail = "</tr></table>";
	else
		strTail = "</table>";

	return strTitle + strHeader + m_strHtml + strTail; 
}



