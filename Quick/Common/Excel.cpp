#include "StdAfx.h"
#include "Excel.h"
#include "Excel9.h"
#include "MkRecordset.h"

COleVariant CMyExcel::_OV_TRUE=COleVariant((short)TRUE);
COleVariant CMyExcel::_OV_FALSE=COleVariant((short)FALSE);
COleVariant CMyExcel::_OV_OPTIONAL=COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

CMyExcel::CMyExcel()
{

}

 
void CMyExcel::ToExcel(CMkRecordset *pRs, const CString& filename, bool border)
{
/*//by mksong (2010-05-26 오후 10:29)
	if(m_ci.m_bNotUseExcel)
	{
		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
		pFrame->m_bNoQueryExit = TRUE;
		pFrame->OnClose();	
	}
*/
	CoInitialize(NULL);

	long nRowCount = pRs->GetRecordCount() + 1;
	long nColumnCount = pRs->GetFiledCount();

	COleSafeArray sa;
	unsigned long elements[] = { static_cast<unsigned long>(nRowCount), static_cast<unsigned long>(nColumnCount) };
	sa.Create(VT_VARIANT, 2, elements);

	long nID = 0;

	for(int i = 0; i < nColumnCount; i++)
	{
		long index[] = {nID, i};
		VARIANT v;
		VariantInit(&v);
		CString str;

		str = pRs->GetFieldName(i);

		v.vt = VT_BSTR;
		v.bstrVal = str.AllocSysString();
		sa.PutElement(index, &v);
		SysFreeString(v.bstrVal);
	}


	for(int r = 1; r < nRowCount; r++)
	{
		for(int c = 0; c < nColumnCount; c++)
		{
			long index[] = {r, c};
			VARIANT v;
			VariantInit(&v);
			CString str;

			pRs->GetFieldValue(c, str);

			v.vt= VT_BSTR;
			v.bstrVal = str.AllocSysString();
			sa.PutElement(index, &v);
			SysFreeString(v.bstrVal);

			VariantClear(&v);
		} 

		pRs->MoveNext();
	}

	ToExcel(sa, nColumnCount, nRowCount);

}
void CMyExcel::ToExcel(CXTPGridControl *pReport, const CString& filename, bool border, long nDateCol) // filename="", border=true
{
/*//by mksong (2010-05-26 오후 10:29)
	if(m_ci.m_bNotUseExcel)
	{
		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
		pFrame->m_bNoQueryExit = TRUE;
		pFrame->OnClose();	
	}
*/

	CoInitialize(NULL);

	//long rows = pReport->GetRecords()->GetCount() + 1;
	long rows = pReport->GetRows()->GetCount() + 1;
	long cols = pReport->GetColumns()->GetVisibleColumnsCount();

	COleSafeArray sa;
	unsigned long elements[] = { static_cast<unsigned long>(rows), static_cast<unsigned long>(cols) };
	sa.Create(VT_VARIANT, 2, elements);

	CXTPGridColumn *pColumn = NULL;

	for(int r = 0; r < rows; r++)
	{
		for(int c = 0; c < cols; c++)
		{
			long index[] = {r, c};
			VARIANT v;
			VariantInit(&v);
			CString str;

			if(r == 0)
			{
				CXTPGridColumn *pCol = pReport->GetColumns()->GetVisibleAt(c);
				str = pCol->GetCaption();
				v.vt = VT_BSTR;
				v.bstrVal = str.AllocSysString();
				sa.PutElement(index, &v);
				SysFreeString(v.bstrVal);
			}
			else
			{
				CXTPGridColumn *pCol = pReport->GetColumns()->GetVisibleAt(c);
				//CXTPGridRecord *pRecord =  (CXTPGridRecord *)pReport->GetRecords()->GetAt(r-1);
				CXTPGridRecord *pRecord =  (CXTPGridRecord *) pReport->GetRows()->GetAt(r-1)->GetRecord();
				CXTPGridRecordItem *pItem =  pRecord->GetItem(pCol);
				//CXTPGridRecordItem *pItem = pRecord->GetItem(c);

				//if(!pCol->IsVisible())
				//	continue;

				if(pItem != NULL )
					str = pItem->GetCaption(pCol);
				else
					str = "";

				//str = ((CXTPGridRecordItemText*)pReport->GetRecords()->GetAt(r-1)->GetItem(c))->GetCaption(pCol);
				//str = ((CXTPGridRecordItemText*)pReport->GetRecords()->GetAt(r-1)->GetItem(c))->GetCaption(pColumn);

				if(str.GetLength() > 0 && str.Left(1) == "=")
					str.Remove('=');

				if(nDateCol >= 0 && c == nDateCol)
					str = "'" + str;
				//else if(::IsDate(str))
				//	str = "'" + str;

				v.vt= VT_BSTR;
				v.bstrVal = str.AllocSysString();
				sa.PutElement(index, &v);
				SysFreeString(v.bstrVal);

			}
			VariantClear(&v);
		}
	}
	ToExcel(sa, cols, rows);
}

void CMyExcel::ToExcel(const CListCtrl &listCtrl, const CString& filename, bool border) // filename="", border=true
{
/*//by mksong (2010-05-26 오후 10:29)
	if(m_ci.m_bNotUseExcel)
	{
		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
		pFrame->m_bNoQueryExit = TRUE;
		pFrame->OnClose();	
	}
*/

	CoInitialize(NULL);

	LV_COLUMN lvCol;
	char szTitle[100];

	lvCol.mask=LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvCol.fmt=LVCFMT_LEFT;
	lvCol.pszText=szTitle;
	lvCol.cchTextMax=99;

	long rows=listCtrl.GetItemCount()+1, cols=0;
	while(listCtrl.GetColumn(cols, &lvCol)) cols++;

// creates a 1 dimensional safearray of type VT_I1 
// with size 5 elements, with the index starting at 2
//	SAFEARRAYBOUND rgsabounds[] = { {5, 2} };
	COleSafeArray sa;

	unsigned long elements[] = { static_cast<unsigned long>(rows), static_cast<unsigned long>(cols) };
	sa.Create(VT_VARIANT, 2, elements);

	for(long r=0; r<rows; r++)
	{
		for(long c=0; c<cols; c++)
		{
			long index[]={r, c};
			VARIANT v;
			VariantInit(&v);
			CString str;

			//헤드컬럼인 경우
			if(r==0)
			{
				v.vt=VT_BSTR;

				listCtrl.GetColumn(c, &lvCol);
				str=szTitle;

				v.bstrVal=str.AllocSysString();
				sa.PutElement(index, &v);
				SysFreeString(v.bstrVal);
			}
			else 
			{
/*				case VT_I4:
					str = listCtrl.GetItemText(r-1, c);
					str.Remove(',');
					v.vt = VT_I4;
					v.lVal= atol(str);
					sa.PutElement(index, &v);
					break;
*/
				str = listCtrl.GetItemText(r-1, c);
				if(str.GetLength() > 0 && str.Left(1) == "=")
					str.Remove('=');
	
				v.vt= VT_BSTR;
				v.bstrVal = str.AllocSysString();
				sa.PutElement(index, &v);
				SysFreeString(v.bstrVal);

			}
			VariantClear(&v);
		}
	}

	_Application app=NULL;
	Workbooks books=NULL;
	_Workbook book=NULL;
	Worksheets sheets=NULL;
	_Worksheet sheet=NULL;
	try
	{
		if(!app.CreateDispatch("Excel.Application"))
		{
			MessageBox(NULL, "엑셀구동시 오류가 발생했습니다.", "엑셀변환 실패", MB_ICONEXCLAMATION);
			return;
		}
		books=app.GetWorkbooks();
		book=books.Add(_OV_OPTIONAL);
		sheets=book.GetWorksheets();
		sheet=sheets.GetItem(COleVariant((short)1));
		//app.InputBox(
		//book.Protect("kkk",book.GetProtectStructure(),book.GetWindows());
		Range range=sheet.GetRange(COleVariant("A1"), COleVariant("A1"));
		range=range.GetResize(COleVariant(rows), COleVariant(cols));
		range.SetValue(COleVariant(sa));
		sa.Detach();
		Range colRange(range.GetColumns());
		colRange.AutoFit();

		if(border)
		{
			Borders borders=range.GetBorders();
			// xlEdgeLeft=7, xlEdgeTop=8, xlEdgeBottom=9, xlEdgeRight=10, xlInsideVertical=11, xlInsideHorizontal=12
			for(int b=7; b<=12; b++)
			{
				if((b==11 && cols<2) || (b==12 && rows<2)) continue;
				Border boder=borders.GetItem(b);
				boder.SetLineStyle(COleVariant((short)1)); // xlContinuous
				boder.SetWeight(COleVariant((short)2)); // xlThin=2
			}
		}

		if(filename.GetLength()<1) 
				app.SetVisible(TRUE);
		else
		{
			//book.GetHasPassword()
			
			book.SaveAs(COleVariant(filename), _OV_OPTIONAL, _OV_OPTIONAL, _OV_OPTIONAL, _OV_OPTIONAL, _OV_OPTIONAL, 0, _OV_OPTIONAL, _OV_OPTIONAL, _OV_OPTIONAL, _OV_OPTIONAL); // 파일크기가 커진다.
			book.Close(_OV_FALSE, _OV_OPTIONAL, _OV_OPTIONAL);
			app.Quit();
		}
	}
	catch(COleException *ex)
	{
		char buf[1024];
		sprintf(buf, "COleException. SCODE: %08lx.", (long)ex->m_sc);
		AfxMessageBox(buf);
		if(book!=NULL) book.Close(_OV_FALSE, _OV_OPTIONAL, _OV_OPTIONAL);
		app.Quit();
	}
	catch(COleDispatchException *ex)
	{
		char buf[1024];
		sprintf(buf, "COleDispatchException. SCODE: %08lx, Description: \"%s\".",
				(long)ex->m_wCode, (char *)ex->m_strDescription.GetBuffer(512));
		AfxMessageBox(buf);
		if(book!=NULL) book.Close(_OV_FALSE, _OV_OPTIONAL, _OV_OPTIONAL);
		app.Quit();
	}
	catch(...)
	{
		AfxMessageBox("엑셀 인터페이스시 알수 없는 예외가 발생하였습니다.");
		if(book!=NULL) book.Close(_OV_FALSE, _OV_OPTIONAL, _OV_OPTIONAL);
		app.Quit();
	}

	CoUninitialize();
}

void CMyExcel::PrintExcel(const CListCtrl &listCtrl, bool border) // border=true
{
/*//by mksong (2010-05-26 오후 10:29)
	if(m_ci.m_bNotUseExcel)
	{
		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
		pFrame->m_bNoQueryExit = TRUE;
		pFrame->OnClose();	
	}
*/


	CoInitialize(NULL);

	LV_COLUMN lvCol;
	char szTitle[100];
	lvCol.mask=LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvCol.fmt=LVCFMT_LEFT;
	lvCol.pszText=szTitle;
	lvCol.cchTextMax=99;

	long rows=listCtrl.GetItemCount()+1, cols=0;
	while(listCtrl.GetColumn(cols, &lvCol)) cols++;

	COleSafeArray sa;
	unsigned long elements[]={ static_cast<unsigned long>(rows), static_cast<unsigned long>(cols) };
	sa.Create(VT_BSTR, 2, elements);
	for(long r=0; r<rows; r++)
	{
		for(long c=0; c<cols; c++)
		{
			VARIANT v;
			VariantInit(&v);
			v.vt=VT_BSTR;
			CString str;
			if(r==0)
			{
				listCtrl.GetColumn(c, &lvCol);
				str=szTitle;
			}
			else str=listCtrl.GetItemText(r-1, c);
			//AfxMessageBox(str);
			v.bstrVal=str.AllocSysString();
			long index[]={r, c};
			sa.PutElement(index, v.bstrVal);
			SysFreeString(v.bstrVal);
			VariantClear(&v);
		}
	}

	_Application app=NULL;
	Workbooks books=NULL;
	_Workbook book=NULL;
	Worksheets sheets=NULL;
	_Worksheet sheet=NULL;
	try
	{
		if(!app.CreateDispatch("Excel.Application"))
		{
			AfxMessageBox("엑셀구동시 오류가 발생했습니다.");
			return;
		}
		books=app.GetWorkbooks();
		book=books.Add(_OV_OPTIONAL);
		sheets=book.GetWorksheets();
		sheet=sheets.GetItem(COleVariant((short)1));

		Range range=sheet.GetRange(COleVariant("A1"), COleVariant("A1"));
		range=range.GetResize(COleVariant(rows), COleVariant(cols));
		range.SetValue(COleVariant(sa));
		sa.Detach();
		Range colRange(range.GetColumns());
		colRange.AutoFit();

		PageSetup pageSetup=sheet.GetPageSetup();
		pageSetup.SetCenterHorizontally(TRUE);
		//From, To, Copies, Preview, ActivePrinter, PrintToFile, Collate, PrToFileName
		
		sheet.PrintOut(_OV_OPTIONAL, _OV_OPTIONAL, COleVariant((short)1), _OV_FALSE, _OV_OPTIONAL, _OV_OPTIONAL, _OV_OPTIONAL, _OV_OPTIONAL);
		book.Close(_OV_FALSE, _OV_OPTIONAL, _OV_OPTIONAL);
		app.Quit();
		
	}
	catch(COleException *ex)
	{
		char buf[1024];
		sprintf(buf, "COleException. SCODE: %08lx.", (long)ex->m_sc);
		AfxMessageBox(buf);
		if(book!=NULL) book.Close(_OV_FALSE, _OV_OPTIONAL, _OV_OPTIONAL);
		app.Quit();
	}
	catch(COleDispatchException *ex)
	{
		char buf[1024];
		sprintf(buf, "COleDispatchException. SCODE: %08lx, Description: \"%s\".",
				(long)ex->m_wCode, (char *)ex->m_strDescription.GetBuffer(512));
		AfxMessageBox(buf);
		if(book!=NULL) book.Close(_OV_FALSE, _OV_OPTIONAL, _OV_OPTIONAL);
		app.Quit();
	}
	catch(...)
	{
		AfxMessageBox("엑셀 인터페이스시 알수 없는 예외가 발생하였습니다.");
		if(book!=NULL) book.Close(_OV_FALSE, _OV_OPTIONAL, _OV_OPTIONAL);
		app.Quit();
	}

	CoUninitialize();
}



void CMyExcel::ToExcel(COleSafeArray &sa, long cols, long rows, const CString& filename, bool border) // filename="", border=true
{
/*//by mksong (2010-05-26 오후 10:29)
	if(m_ci.m_bNotUseExcel)
	{
		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
		pFrame->m_bNoQueryExit = TRUE;
		pFrame->OnClose();	
	}
*/

	_Application app=NULL;
	Workbooks books=NULL;
	_Workbook book=NULL;
	Worksheets sheets=NULL;
	_Worksheet sheet=NULL;
	try
	{
		if(!app.CreateDispatch("Excel.Application"))
		{
			MessageBox(NULL, "엑셀구동시 오류가 발생했습니다.", "엑셀변환 실패", MB_ICONEXCLAMATION);
			return;
		}
		books=app.GetWorkbooks();
		book=books.Add(_OV_OPTIONAL);
		sheets=book.GetWorksheets();
		sheet=sheets.GetItem(COleVariant((short)1));

		Range range=sheet.GetRange(COleVariant("A1"), COleVariant("A1"));
		range=range.GetResize(COleVariant(rows), COleVariant(cols));
		range.SetValue(COleVariant(sa));
		sa.Detach();
		Range colRange(range.GetColumns());
		colRange.AutoFit();
		
		if(border)
		{
			Borders borders=range.GetBorders();
			// xlEdgeLeft=7, xlEdgeTop=8, xlEdgeBottom=9, xlEdgeRight=10, xlInsideVertical=11, xlInsideHorizontal=12
			for(int b=7; b<=12; b++)
			{
				if((b==11 && cols<2) || (b==12 && rows<2)) continue;
				Border boder=borders.GetItem(b);
				boder.SetLineStyle(COleVariant((short)1)); // xlContinuous
				boder.SetWeight(COleVariant((short)2)); // xlThin=2
			}
		}

		if(filename.GetLength()<1) app.SetVisible(TRUE);
		else
		{
			book.SaveAs(COleVariant(filename), _OV_OPTIONAL, _OV_OPTIONAL, _OV_OPTIONAL, _OV_OPTIONAL, _OV_OPTIONAL, 0, _OV_OPTIONAL, _OV_OPTIONAL, _OV_OPTIONAL, _OV_OPTIONAL); // 파일크기가 커진다.
			book.Close(_OV_FALSE, _OV_OPTIONAL, _OV_OPTIONAL);
			app.Quit();
		}
	}
	catch(COleException *ex)
	{
		char buf[1024];
		sprintf(buf, "COleException. SCODE: %08lx.", (long)ex->m_sc);
		AfxMessageBox(buf);
		if(book!=NULL) book.Close(_OV_FALSE, _OV_OPTIONAL, _OV_OPTIONAL);
		app.Quit();
	}
	catch(COleDispatchException *ex)
	{
		char buf[1024];
		sprintf(buf, "COleDispatchException. SCODE: %08lx, Description: \"%s\".",
			(long)ex->m_wCode, (char *)ex->m_strDescription.GetBuffer(512));
		AfxMessageBox(buf);
		if(book!=NULL) book.Close(_OV_FALSE, _OV_OPTIONAL, _OV_OPTIONAL);
		app.Quit();
	}
	catch(...)
	{
		AfxMessageBox("엑셀 인터페이스시 알수 없는 예외가 발생하였습니다.");
		if(book!=NULL) book.Close(_OV_FALSE, _OV_OPTIONAL, _OV_OPTIONAL);
		app.Quit();
	}

	CoUninitialize();
}
