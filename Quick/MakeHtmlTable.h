#pragma once

class CMakeHtmlTable
{
public:
	CMakeHtmlTable(void);
	virtual ~CMakeHtmlTable(void);

public:
	void AddCol(CString strValue, int nWidth = 0);
	void AddCol(int nValue, int nWidth = 0);
	void AddImageList(int nID, CString strValue, int nWidth = 0);
    void AddRow();
	CString GetHtmlTable();
	void SetTableBorder(int nBorder) { m_nBorder = nBorder;}
	void SetTitle(CString strTitle) { m_strTitle = strTitle; }

protected:
	void MakeCol(CString strValue, int nWidth);

	CString m_strHtml;
	CString m_strTitle;
	long m_nRow;
	long m_nCol;
	long m_nTotalRow;
	long m_nTotalCol;
	long m_nBorder;
	BOOL m_bAddRow;
};
