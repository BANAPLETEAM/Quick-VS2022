#pragma once

class CMkRecordset;
class CFpspread1;
class CXTPGridControl;

class CMyExcel
{
public:
	static COleVariant _OV_TRUE;
	static COleVariant _OV_FALSE;
	static COleVariant _OV_OPTIONAL;

public:
	static void ToExcel(const CListCtrl &listCtrl, const CString& filename = "", bool border = TRUE);
	static void ToExcel(CXTPGridControl *pReport, const CString& filename = "", bool border = TRUE, long nDateCol = -1);

	static void ToExcel(COleSafeArray &sa, long cols, long rows, const CString& filename = "", bool border = TRUE);
	static void PrintExcel(const CListCtrl &listCtrl, bool border=true);
	static void ToExcel(CMkRecordset *pRs, const CString& filename = "", bool border = TRUE);

private:
	CMyExcel();
};
