#include "stdafx.h"
#include "resource.h"
#include "DataBox.h"
#include "MyReportPaintManager.h"
#include "MainFrm.h"
#include "MyXTPReportView.h"
#include "TaskFrame.h"
#include "ViewPrintPreview.h"

//------------------------------------------------>




CMyXTPGridRecord::CMyXTPGridRecord()
{
	//this->m_pChildren->m_arrRecords;
	m_nMyRecordItemCount = 0;

	m_pObject = NULL;

	m_pDWORD = NULL;
	m_nDataLong =0;
	m_bDirtyFlag = FALSE;
	m_nTreeParentNo = 0;
	m_sTreeRef = "";

	m_lData = 0;
	m_lData2 = 0;
	m_lData3 = 0;
	m_lData4 = 0;
	m_sData = "";
	m_sData2 = "";
	m_sData3 = "";
	m_dtData = COleDateTime::GetCurrentTime();	
	m_dtData2 = COleDateTime::GetCurrentTime();
}

CMyXTPGridRecord* CMyXTPGridRecord::MySubAddItem(int niValue)
{	
	CLMyXTPGridRecordItemNumber *pRecordItem = new CLMyXTPGridRecordItemNumber(niValue);
	AddItem(pRecordItem);	


	m_nMyRecordItemCount++;
	return this;
}

CMyXTPGridRecord* CMyXTPGridRecord::MySubAddItem(long nlValue)
{
	CLMyXTPGridRecordItemNumber *pRecordItem = new CLMyXTPGridRecordItemNumber(nlValue);
	AddItem(pRecordItem);
	m_nMyRecordItemCount++;
	return this;
}
CMyXTPGridRecord* CMyXTPGridRecord::MySubAddItem(COleDateTime dtValue, CString sFormat)
{

	CXTPGridRecordItemDateTime *pRecordItem =(CXTPGridRecordItemDateTime *)AddItem(new CXTPGridRecordItemDateTime(dtValue));
	pRecordItem->SetFormatString(sFormat);
	m_nMyRecordItemCount++;

	return this;

}

CMyXTPGridRecord* CMyXTPGridRecord::MySubAddItem(CString sValue)
{
	CLMyXTPGridRecordItemText *pRecordItem = (CLMyXTPGridRecordItemText *)AddItem(new CLMyXTPGridRecordItemText(sValue));	
	//this->AddItem(pRecordItem);	
	m_nMyRecordItemCount++;
	return this;
}




CMyXTPGridRecord* CMyXTPGridRecord::MySubComboAddItem(CStringArray &sArray,CUIntArray &nArray, int nValue)
{

	CMyComboRecordItem *pRecordItem = (CMyComboRecordItem *)AddItem(new CMyComboRecordItem( sArray, nArray, nValue));	
	m_nMyRecordItemCount++;
	return this;
}

CMyXTPGridRecord* CMyXTPGridRecord::MySubCheckAddItem( BOOL bDefaluValue)
{
	CMyCheckRecordItem *pRecordItem = (CMyCheckRecordItem *)AddItem(new CMyCheckRecordItem(bDefaluValue, this));
	//this->AddItem(pRecordItem);
	m_nMyRecordItemCount++;
	return this;

}



long  CMyXTPGridRecord::GetItemlValue(int nCol)
{
	CXTPGridRecordItem *pItem =GetItem(nCol);
	if(pItem)
	{
		CRuntimeClass *p = pItem->GetRuntimeClass();
		CString sClassName = "";
		sClassName = p->m_lpszClassName;
		if(sClassName.Find("CXTPGridRecordItemNumber") >= 0)
		{
			long nVal = 0; CString sVal = "";
			CLMyXTPGridRecordItemNumber* pItemNumber = (CLMyXTPGridRecordItemNumber*)pItem;

			return (long)pItemNumber->GetValue();
		}
	}
	return 0;

}

CString  CMyXTPGridRecord::GetItemSValue(int nCol)
{

	CXTPGridRecordItem *pItem =GetItem(nCol);
	if(pItem)
	{
		CRuntimeClass *p = pItem->GetRuntimeClass();
		CString sClassName = "";
		sClassName = p->m_lpszClassName;
		if(sClassName.Find("CXTPGridRecordItemText") >= 0)
		{
			long nVal = 0; CString sVal = "";
			CLMyXTPGridRecordItemText* pItemNumber = (CLMyXTPGridRecordItemText*)pItem;

			return pItemNumber->GetValue();
		}
	}
	return "";
}


//////////////////////////////////////////////////////////////////////////////////////////////
// DataBox Start...

#define ID_TEST_FIELDCHOOSER_CUSTOMER	WM_USER + 700
#define ID_TEST_FILTERWINDOW			WM_USER + 200

CDataBox::CDataBox():CXTPGridControl()
{
	m_bTreeItem = FALSE;
	m_pMainRecord = new CMyXTPGridRecord;
	m_pBodyRecords = this->GetRecords(); // 현재 메인의 레코드 수이다 단지 this->GetRecords()
	m_nColumnCount = 0;
	m_nRecordCount = 0;
	m_bHeader = FALSE;
	m_bCListCtrlInit = FALSE;



	this->GetPaintManager()->m_strNoItems = "해당사항없음";	
	m_bFilterEditCreate = FALSE;
	m_bColumnSelectCreate = FALSE;
	m_pTemplate = NULL;
	m_bPrintPreview = FALSE;
	m_pTaskFrame = FALSE;
	m_pRs = NULL;
	m_pCmd = NULL;
	m_bInsertSearchAll = FALSE;


}

CDataBox::~CDataBox()
{

	//if(m_pMainRecord)
	//	delete m_pMainRecord;
}

//
//int CDataBox::InsertColumn(int nCol, CString strHearName,  int nWidth,int nAlignment,
//						   BOOL bAllowEdit,BOOL bTreeColumn )
//{
//
//	CXTPGridColumn *pCol = AddColumn(new CXTPGridColumn(nCol, strHearName, nWidth));
//	m_nColumnCount = nCol;
//	pCol->SetAlignment(nAlignment);
//	pCol->SetTreeColumn(bTreeColumn);	
//	pCol->SetEditable(bAllowEdit);
//
//	return 0;
//}
int CDataBox::DeleteItem(int nIndex, BOOL bRefresh )
{
	this->GetRecords()->RemoveAt(nIndex);
	if(bRefresh)
		this->Populate();
	return 0;
}

void CDataBox::SetSelectedRow(long nRow)
{
	CXTPGridRows *pRows = GetRows();
	CXTPGridRow *pRow = pRows->GetAt(nRow);

	GetSelectedRows()->Select(pRow);
}
int CDataBox::GetSelectedCount()
{	
	if(GetSelectedRows()->GetCount() > 0)
		return GetSelectedRows()->GetCount();
	else
		return 0;
}
CXTPGridRow* CDataBox::GetSelectedRow()
{	
	if(GetSelectedRows()->GetCount() > 0)
		return GetSelectedRows()->GetAt(0);
	else
		return FALSE;
}
CMyXTPGridRecord* CDataBox::GetSelectedRecord()
{	
	if(GetSelectedRows()->GetCount() > 0)
		return (CMyXTPGridRecord*)GetSelectedRows()->GetAt(0)->GetRecord();
	else
		return FALSE;
}




CMyXTPGridRecord * CDataBox::GetSelectedRecord(int i)
{

	if(GetSelectedRows()->GetCount() == 0 && GetSelectedRows()->GetCount() < i )
		return NULL;


	CXTPGridRow *pRow = GetSelectedRows()->GetAt(i);
	if(pRow)
		return (CMyXTPGridRecord*)pRow->GetRecord();
	else
		return  NULL;
}

int CDataBox::GetNextItem(int nIndex, int nType)
{
	POSITION pos = GetSelectedRows()->GetFirstSelectedRowPosition();

	while(pos != NULL)
	{
		int nCur = GetSelectedRows()->GetNextSelectedRow(pos)->GetIndex();
		if(nCur >= nIndex)
			return nCur;
	}

	return -1;
}




void CDataBox::ToExcel(CString strTitle)
{
	CoInitialize(NULL);

	long rows = GetRows()->GetCount() + 1;
	long cols = GetColumns()->GetVisibleColumnsCount();

	COleSafeArray sa;
	unsigned long elements[] = { static_cast<unsigned long>(rows), static_cast<unsigned long>(cols) };
	sa.Create(VT_VARIANT, 2, elements);

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
				CXTPGridColumn *pCol = GetColumns()->GetVisibleAt(c);
				str = pCol->GetCaption();
				v.vt = VT_BSTR;
				v.bstrVal = str.AllocSysString();
				sa.PutElement(index, &v);
				SysFreeString(v.bstrVal);
			}
			else
			{
				CXTPGridColumn *pColumn = NULL;
				str = ((CXTPGridRecordItemText*)(GetRows()->GetAt(r-1)->GetRecord()->GetItem(c)))->GetCaption(pColumn);
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

	CMyExcel::ToExcel(sa, cols, rows);
} 

/* CListCtrl 형식 */



int CDataBox::InsertColumn(int nCol, CString strHearderName,int nAlignment,int nWidth,
						   BOOL bAllowEdit,BOOL bTreeColumn )
{	

	CXTPGridColumn *pCol =  ColumnInit(nCol,strHearderName,nWidth,bAllowEdit,nAlignment);


	pCol->SetAlignment(nAlignment);
	pCol->SetTreeColumn(bTreeColumn);	
	pCol->SetEditable(bAllowEdit);

	return 0;

}

CImageList* CDataBox::SetImageList(CImageList* pImageList, int nImageListType)
{
	CImageList *pReturnImage = NULL;	

	CXTPGridControl::SetImageList(pImageList);
	InitControl();
	return pImageList;	
}
//
void CDataBox::SetExtendedStyle(DWORD dwNewStyle)
{
	InitControl();
}

DWORD_PTR CDataBox::GetItemData(int nItem)
{
	if(GetRecords()->GetCount() <= 0 )
		return NULL;

	if(GetRecords()->GetCount() - 1 < nItem)
		return NULL;

	CMyXTPGridRecord *pRecord = NULL;
	DWORD_PTR pValue = NULL;
	if(GetRecords()->GetAt(nItem))
	{
		pRecord = (CMyXTPGridRecord *)GetRecords()->GetAt(nItem);
		pValue = pRecord->GetItemData();
		if(pValue != NULL)
			return pValue;
	}
	return pValue;	
}


void CDataBox::SetItemData(int nItem, DWORD_PTR pValue)
{
	if(nItem == GetRecords()->GetCount())
		m_pMainRecord->SetItemData(pValue);
	else
	{
		if(GetRecords()->GetAt(nItem))
			((CMyXTPGridRecord*)GetRecords()->GetAt(nItem))->SetItemData(pValue);
	}

}


BOOL CDataBox::ModifyStyle(HWND hWnd, DWORD dwRemove, DWORD dwAdd,  UINT nFlags)
{	
	InitControl();

	return TRUE;//CXTPGridControl::ModifyStyle(hWnd, dwRemove, dwAdd, nFlags);	
	//ModifyStyle(hWnd, dwRemove, dwAdd, nFlags);	
}

void CDataBox::InitControl()
{

	if(!m_bCListCtrlInit)
	{
		GetReportHeader()->SetAutoColumnSizing(FALSE);
		GetReportHeader()->AllowColumnSort(TRUE);
		GetReportHeader()->AllowColumnRemove(FALSE);
		GetReportHeader()->AllowColumnResize(TRUE);
		GetPaintManager()->SetColumnStyle(xtpGridColumnResource);	
		GetPaintManager()->m_strNoItems = "해당사항없음";
		GetPaintManager()->SetGridStyle(TRUE,xtpGridSolid);
		SetGridColor(RGB(212, 208, 200));
		m_bHeader = TRUE;

	}
	m_bCListCtrlInit = TRUE;

}

int CDataBox::GetSelectionMark()
{
	if(GetRecords()->GetCount() == 0)
		return -1;

	return GetSelectedRow()->GetIndex();

}
void CDataBox::DeleteAllItems()
{
	DeleteAllItem();

}
void CDataBox::InsertItem(int nItem, CString strItem, int nImage, BOOL NoEndItemAndRandoInsert)
{	
	if(NoEndItemAndRandoInsert )
		m_pMainRecord = new CMyXTPGridRecord();

	for(int i = 0; i < GetColumns()->GetCount(); i++)
	{
		if(i == 0)
			m_pMainRecord->MySubAddItem(strItem);
		else
			m_pMainRecord->MySubAddItem("");
	}	



	CXTPGridRecord *pNewRecord = AddRecord(m_pMainRecord);

	/*if(GetRecords()->GetCount() > 0)
	{
	CXTPGridRecord *pOldRecord = (CXTPGridRecord *)GetRecords()->GetAt(GetRecords()->GetCount() -1);
	for(int i = 0; i < pOldRecord->GetItemCount(); i++)
	{			
	pNewRecord->AddItem(pOldRecord->GetItem(i));
	}
	}*/
	/*if(nItem == GetRecords()->GetCount())
	MyAddItem(strItem);
	else
	{


	}*/

}

int CDataBox::SetItemText(int nIndex, int nCol , CString strText, int nImage ,BOOL bRefresh)
{
	int nRecordCount = GetRecords()->GetCount();
	if(nRecordCount == nIndex)  // 지금 신규인서트 일때
	{
		//MyAddItem(strText);
		CXTPGridRecordItem *pItem = m_pMainRecord->GetItem(nCol);
		if(pItem == NULL)
		{
			CMyXTPGridRecord *pOldRecord = NULL;
			pOldRecord = (CMyXTPGridRecord*)GetRecords()->GetAt(0);
			if(pOldRecord)
			{
				int nApplyCol = max(pOldRecord->GetItemCount() , nCol);
				for(int i = 0; i <= nApplyCol; i++)
				{
					CXTPGridRecordItem *pItem = m_pMainRecord->GetItem(i);
					if(pItem != NULL && i <= nCol)
						continue;						
					else
					{
						m_pMainRecord->InternalAddRef();
						m_pMainRecord->AddItem(new CXTPGridRecordItemText());
					}
				}			

			}
			else
			{
				for(int i = 0; i <= nCol; i++)
				{
					if(m_pMainRecord->GetItem(i) == NULL)
					{
						m_pMainRecord->InternalAddRef();
						m_pMainRecord->AddItem(new CXTPGridRecordItemText());
					}
				}

			}
		}

		if(m_pMainRecord->GetItem(nCol))
			m_pMainRecord->GetItem(nCol)->SetCaption(strText);
		else
			m_pMainRecord->MySubAddItem(strText);
	}
	else
	{
		CMyXTPGridRecord *pRecord = NULL;
		pRecord = (CMyXTPGridRecord*)GetRecords()->GetAt(nIndex);
		if(pRecord)
		{
			CXTPGridRecordItemText *pItem = (CXTPGridRecordItemText *)pRecord->GetItem(nCol);
			if(pItem == NULL)
			{
				if(GetRecords()->GetCount() > 0)
				{
					CXTPGridRecord *pOldRecord = GetRecords()->GetAt(0);
					for(int i= 0; i < max(pOldRecord->GetItemCount(),nCol); i++)
					{
						if(pOldRecord->GetItemCount() >= nCol)
						{
							CXTPGridRecordItem *pItem = (CXTPGridRecordItem *)pRecord->GetItem(i);

							if(pRecord->GetItem(i) == NULL && i <= nCol )
								pRecord->AddItem(pOldRecord->GetItem(i));
							else
								pRecord->AddItem(new CXTPGridRecordItemText());
						}
						else
							pOldRecord->AddItem(new CXTPGridRecordItemText());

					}
				}
			}
			((CXTPGridRecordItemText*)(pRecord->GetItem(nCol)))->SetCaption(strText);
		}
	}

	if(nImage >= 0)		
		this->GetRecords()->GetAt(nIndex)->GetItem(0)->SetIconIndex(nImage);		

	if(bRefresh)
		Populate();



	return 0;
}
CString CDataBox::GetItemText(int nItem, int nCol)
{
	CXTPGridRows *pRows = GetRows();
	if(pRows->GetCount() > 0)
	{
		CXTPGridRow *pRow = pRows->GetAt(nItem);
		CXTPGridColumn* pColumn = NULL;
		CMyXTPGridRecord *pRecord = (CMyXTPGridRecord*)pRow->GetRecord();
		return ((CXTPGridRecordItemText*)(pRecord->GetItem(nCol)))->GetCaption(pColumn);
	}
	return "";

}


/* CListCtrl 형식 */

/*
void CDataBox::SetItemDataString(CString sData)
{
if(m_bTreeItem)
m_pSubTarGetRecord->SetItemDataString(sData);	
else
m_pMainRecord->SetItemDataString(sData);


}


CString CDataBox::GetItemDataString()
{
CString sData = "";
if(m_bTreeItem)
sData = m_pSubTarGetRecord->GetItemDataString();
else
sData = m_pMainRecord->GetItemDataString();

return sData;
}
void CDataBox::SetItemDataString2(CString sData)
{
if(m_bTreeItem)
m_pSubTarGetRecord->SetItemDataString2(sData);	
else
m_pMainRecord->SetItemDataString2(sData);


}


CString CDataBox::GetItemDataString2()
{
CString sData = "";
if(m_bTreeItem)
sData = m_pSubTarGetRecord->GetItemDataString2();
else
sData = m_pMainRecord->GetItemDataString2();

return sData;
}

void CDataBox::SetItemDataDate(COleDateTime dt)
{
if(m_bTreeItem)
m_pSubTarGetRecord->SetItemDataDateTime(dt);
else
m_pMainRecord->SetItemDataDateTime(dt);
}
COleDateTime CDataBox::GetItemDataDate(int nItem)
{
return ((CMyXTPGridRecord*)GetRows()->GetAt(nItem)->GetRecord())->GetItemDataDate();
}



void CDataBox::SetItemDataLong(long nData)
{
if(m_bTreeItem)
m_pSubTarGetRecord->SetItemDataLong(nData);
else
m_pMainRecord->SetItemDataLong(nData);
}

void CDataBox::SetItemDataLong2(long nData)
{
if(m_bTreeItem)
m_pSubTarGetRecord->SetItemDataLong2(nData);
else
m_pMainRecord->SetItemDataLong2(nData);
}

void CDataBox::SetItemDataRecordLong(int nRoportRecord, long nData)
{
CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)GetRecords()->GetAt(nRoportRecord);
if(pRecord)
pRecord->SetItemDataLong(nData);

}
void CDataBox::SetItemDataRecordLong2(int nRoportRecord, long nData)
{
CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)GetRecords()->GetAt(nRoportRecord);
if(pRecord)
pRecord->SetItemDataLong2(nData);
}
void CDataBox::SetItemDataLong(int nRoportRow, long nData)
{
CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)GetRows()->GetAt(nRoportRow)->GetRecord();
if(pRecord)
pRecord->SetItemDataLong(nData);

}
void CDataBox::SetItemDataLong2(int nRoportRow, long nData)
{
CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)GetRows()->GetAt(nRoportRow)->GetRecord();
if(pRecord)
pRecord->SetItemDataLong2(nData);
}


long CDataBox::GetItemDataLong(int nReportRow)
{
return ((CMyXTPGridRecord*)GetRows()->GetAt(nReportRow)->GetRecord())->GetItemDataLong();
}

long CDataBox::GetItemDataLong2(int nReportRow)
{
return ((CMyXTPGridRecord*)GetRows()->GetAt(nReportRow)->GetRecord())->GetItemDataLong2();
}

long CDataBox::GetItemDataRecordLong(int nRecordRow)
{
return ((CMyXTPGridRecord*)GetRecords()->GetAt(nRecordRow)->GetItemDataLong();
}

long CDataBox::GetItemDataRecordLong2(int nRecordRow)
{
return ((CMyXTPGridRecord*)GetRecords()->GetAt(nRecordRow)->GetItemDataLong2();
}


*/

///////////////////////////////////// object
void  CDataBox::InsertItemData(DWORD_PTR pValue)
{
	if(m_bTreeItem)
		m_pSubTarGetRecord->SetItemData(pValue);
	else
		m_pMainRecord->SetItemData(pValue);

}




///////////////////////////////////// long, int
void CDataBox::InsertItemDataLong(long nData)
{
	if(m_bTreeItem)
		m_pSubTarGetRecord->SetItemDataLong(nData);
	else
		m_pMainRecord->SetItemDataLong(nData);
}
void CDataBox::InsertItemDataLong2(long nData)
{
	if(m_bTreeItem)
		m_pSubTarGetRecord->SetItemDataLong2(nData);
	else
		m_pMainRecord->SetItemDataLong2(nData);
}

void CDataBox::InsertItemDataLong3(long nData)
{
	if(m_bTreeItem)
		m_pSubTarGetRecord->SetItemDataLong3(nData);
	else
		m_pMainRecord->SetItemDataLong3(nData);
}

void CDataBox::SetItemDataLong(int nReportRow, long nData)
{
	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)GetRows()->GetAt(nReportRow)->GetRecord();
	if(pRecord)
		pRecord->SetItemDataLong(nData);
}
void CDataBox::SetItemDataLong2(int nReportRow,long nData)
{
	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)GetRows()->GetAt(nReportRow)->GetRecord();
	if(pRecord)
		pRecord->SetItemDataLong2(nData);
}

void CDataBox::SetItemDataLong3(int nReportRow,long nData)
{
	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)GetRows()->GetAt(nReportRow)->GetRecord();
	if(pRecord)
		pRecord->SetItemDataLong3(nData);
}


long CDataBox::GetItemDataLong(int nReportRow)
{

	return ((CMyXTPGridRecord*)GetRows()->GetAt(nReportRow)->GetRecord())->GetItemDataLong();
}

long CDataBox::GetItemDataLong(CMyXTPGridRecord *pRecord)
{
	if(pRecord)
		return pRecord->GetItemDataLong();

	return NULL;
}

long CDataBox::GetItemDataLong2(int nReportRow)
{

	return ((CMyXTPGridRecord*)GetRows()->GetAt(nReportRow)->GetRecord())->GetItemDataLong2();
}
long CDataBox::GetItemDataLong3(int nReportRow)
{

	return ((CMyXTPGridRecord*)GetRows()->GetAt(nReportRow)->GetRecord())->GetItemDataLong3();
}
void CDataBox::SetItemDataRecordLong(int nRoportRecord, long nData)
{

	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)GetRecords()->GetAt(nRoportRecord);
	if(pRecord)
		pRecord->SetItemDataLong(nData);
}
void CDataBox::SetItemDataRecordLong2(int nRoportRecord, long nData)
{
	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)GetRecords()->GetAt(nRoportRecord);
	if(pRecord)
		pRecord->SetItemDataLong2(nData);

}
void CDataBox::SetItemDataRecordLong3(int nRoportRecord, long nData)
{
	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)GetRecords()->GetAt(nRoportRecord);
	if(pRecord)
		pRecord->SetItemDataLong3(nData);
}
long CDataBox::GetItemDataRecordLong(int nRecordRow)
{
	return ((CMyXTPGridRecord*)GetRecords()->GetAt(nRecordRow))->GetItemDataLong();
}
long CDataBox::GetItemDataRecordLong2(int nRecordRow)
{
	return ((CMyXTPGridRecord*)GetRecords()->GetAt(nRecordRow))->GetItemDataLong2();
}
long CDataBox::GetItemDataRecordLong3(int nRecordRow)
{
	return ((CMyXTPGridRecord*)GetRecords()->GetAt(nRecordRow))->GetItemDataLong3();
}

///////////////////////////////////// long, int

///////////////////////////////////// CString
void CDataBox::InsertItemDataString(CString sData)
{
	if(m_bTreeItem)
		m_pSubTarGetRecord->SetItemDataString(sData);
	else
		m_pMainRecord->SetItemDataString(sData);
}
void CDataBox::InsertItemDataString2(CString sData)
{
	if(m_bTreeItem)
		m_pSubTarGetRecord->SetItemDataString2(sData);
	else
		m_pMainRecord->SetItemDataString2(sData);
}

void CDataBox::SetItemDataString(int nReportRow, CString sData)
{
	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)GetRows()->GetAt(nReportRow)->GetRecord();
	if(pRecord)
		pRecord->SetItemDataString(sData);
}
void CDataBox::SetItemDataString2(int nReportRow,CString sData)
{
	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)GetRows()->GetAt(nReportRow)->GetRecord();
	if(pRecord)
		pRecord->SetItemDataString2(sData);
}
CString CDataBox::GetItemDataString(int nReportRow)
{
	return ((CMyXTPGridRecord*)GetRows()->GetAt(nReportRow)->GetRecord())->GetItemDataString();
}
CString CDataBox::GetItemDataString2(int nReportRow)
{
	return ((CMyXTPGridRecord*)GetRows()->GetAt(nReportRow)->GetRecord())->GetItemDataString2();
}
void CDataBox::SetItemDataRecordString(int nRoportRecord, CString sData)
{

	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)GetRecords()->GetAt(nRoportRecord);
	if(pRecord)
		pRecord->SetItemDataString(sData);
}
void CDataBox::SetItemDataRecordString2(int nRoportRecord, CString sData)
{
	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)GetRecords()->GetAt(nRoportRecord);
	if(pRecord)
		pRecord->SetItemDataString2(sData);

}
CString CDataBox::GetItemDataRecordString(int nRecordRow)
{
	return ((CMyXTPGridRecord*)GetRecords()->GetAt(nRecordRow))->GetItemDataString();
}
CString CDataBox::GetItemDataRecordString2(int nRecordRow)
{
	return ((CMyXTPGridRecord*)GetRecords()->GetAt(nRecordRow))->GetItemDataString2();
}

/////////////////////////////////////CString


///////////////////////////////////// COleDateTime
void CDataBox::InsertItemDataDate(COleDateTime dt)
{
	if(m_bTreeItem)
		m_pSubTarGetRecord->SetItemDataDateTime(dt);
	else
		m_pMainRecord->SetItemDataDateTime(dt);
}
void CDataBox::InsertItemDataDate2(COleDateTime dt)
{
	if(m_bTreeItem)
		m_pSubTarGetRecord->SetItemDataDateTime2(dt);
	else
		m_pMainRecord->SetItemDataDateTime2(dt);
}

void CDataBox::SetItemDataDate(int nReportRow, COleDateTime dt)
{
	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)GetRows()->GetAt(nReportRow)->GetRecord();
	if(pRecord)
		pRecord->SetItemDataDateTime(dt);
}
void CDataBox::SetItemDataDate2(int nReportRow,COleDateTime dt)
{
	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)GetRows()->GetAt(nReportRow)->GetRecord();
	if(pRecord)
		pRecord->SetItemDataDateTime2(dt);
}
COleDateTime CDataBox::GetItemDataDate(int nReportRow)
{

	return ((CMyXTPGridRecord*)GetRows()->GetAt(nReportRow)->GetRecord())->GetItemDateTime();
}
COleDateTime CDataBox::GetItemDataDate2(int nReportRow)
{

	return ((CMyXTPGridRecord*)GetRows()->GetAt(nReportRow)->GetRecord())->GetItemDateTime2();
}
void CDataBox::SetItemDataRecordDate(int nRoportRecord, COleDateTime dt)
{

	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)GetRecords()->GetAt(nRoportRecord);
	if(pRecord)
		pRecord->SetItemDataDateTime(dt);
}
void CDataBox::SetItemDataRecordDate2(int nRoportRecord, COleDateTime dt)
{
	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)GetRecords()->GetAt(nRoportRecord);
	if(pRecord)
		pRecord->SetItemDataDateTime2(dt);

}
COleDateTime CDataBox::GetItemDataRecordDate(int nRecordRow)
{
	return ((CMyXTPGridRecord*)GetRecords()->GetAt(nRecordRow))->GetItemDateTime();
}
COleDateTime CDataBox::GetItemDataRecordDate2(int nRecordRow)
{
	return ((CMyXTPGridRecord*)GetRecords()->GetAt(nRecordRow))->GetItemDateTime2();
}

/////////////////////////////////////COleDateTime





int CDataBox::GetItemCount()
{
	return m_pBodyRecords->GetCount();
}

void CDataBox::EndItem()
{

	m_pMainRecord->m_nMyRecordItemCount = 0;
	if(m_bTreeItem)
		m_pMainRecord->GetChilds()->Add(m_pSubTarGetRecord);	
	else
		AddRecord(m_pMainRecord);


	m_pMainRecord = new CMyXTPGridRecord();
	m_bTreeItem = FALSE;
	m_nColumnCount = 0;
	m_bHeader = TRUE;	
	//qsLog.Print( "Enditem() --> \n");

	InitControl();
	/*if(m_pBodyRecords->GetCount() <= 1)
	{
	qsLog.Print("  init enditem() \n");
	this->GetReportHeader()->SetAutoColumnSizing(TRUE);
	this->GetReportHeader()->AllowColumnRemove(FALSE);
	this->GetReportHeader()->AllowColumnResize(TRUE);

	this->GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	this->GetPaintManager()->m_strNoItems = "해당사항없음";
	this->GetPaintManager()->SetGridStyle(TRUE,xtpGridSolid);

	}*/

}

void CDataBox::TreeChildAddItem(int nCol,CString sValue,CString sColName,int nColWidth,BOOL bEdit,int nAlignment)
{
	try			
	{
		if(m_pBodyRecords->GetCount() == 0 )
		{
			this->MyAddItem(nCol,sValue, sColName,nColWidth, bEdit, nAlignment);
			this->GetReportHeader()->GetControl()->GetColumns()->GetAt(nCol)->SetTreeColumn(TRUE);

			return ;
		}

		CString sText;
		if(m_pBodyRecords->GetCount() > 0){

			for(int i = 0; i < m_pBodyRecords->GetCount(); i++)
			{			
				//CXTPGridColumn *pCol = NULL;
				CXTPGridColumn *pCol = GetColumns()->GetAt(nCol);				
				sText = m_pBodyRecords->GetAt(i)->GetItem(nCol)->GetCaption(pCol);
				if(sText == sValue )
				{					

					CXTPGridRecords *pChildRecords = m_pBodyRecords->GetAt(i)->GetChilds();										
					m_pSubTarGetRecord = (CMyXTPGridRecord*)pChildRecords->Add(new CMyXTPGridRecord());										

					m_pSubTarGetRecord->MySubAddItem(sValue);					
					m_bTreeItem = TRUE;


					return ;
				}
			}
		}

		m_pMainRecord->MySubAddItem(sValue);	

		return ;
	}
	catch (char* e)
	{
		UNUSED_ALWAYS(e);
		//e;
		//MessageBox(e, "확인",MB_ICONINFORMATION);
		//qsLog.Print(e);
	}


}

void  CDataBox::TreeChildAddItem(int nCol,COleDateTime dtValue,  CString sColName,int nColWidth,BOOL bEdit,int nAlignment)
{
	try			
	{
		if(m_pBodyRecords->GetCount() == 0 )
		{
			this->MyAddItem(nCol,dtValue, sColName,nColWidth, bEdit, nAlignment);
			this->GetReportHeader()->GetControl()->GetColumns()->GetAt(nCol)->SetTreeColumn(TRUE);

			return ;
		}

		COleDateTime dt;
		if(m_pBodyRecords->GetCount() > 0){

			for(int i = 0; i < m_pBodyRecords->GetCount(); i++)
			{			
				//CXTPGridColumn *pCol = NULL;
				CXTPGridColumn *pCol = GetColumns()->GetAt(nCol);				
				m_pBodyRecords->GetAt(i)->GetItem(nCol)->GetCaption(pCol);
				CString sDataVal;
				CString sdt = pCol->GetCaption();
				sdt.Format("%Y-%m-%d %H:%M%:%S");
				sDataVal = dtValue.Format("%Y-%m-%d %H:%M%:%S");
				if(sdt == sDataVal )
				{					
					CXTPGridRecords *pChildRecords = m_pBodyRecords->GetAt(i)->GetChilds();								
					m_pSubTarGetRecord = (CMyXTPGridRecord*)pChildRecords->Add(new CMyXTPGridRecord());										
					m_pSubTarGetRecord->MySubAddItem(dtValue);					
					m_bTreeItem = TRUE;
					return ;
				}
			}
		}

		m_pMainRecord->MySubAddItem(dtValue);	
		return ;

	}
	catch (char* e)
	{
		UNUSED_ALWAYS(e);
		//e;
		//MessageBox(e, "확인",MB_ICONINFORMATION);
		//qsLog.Print(e);
	}


}

void CDataBox::TreeChildAddItem(int nCol,long nValue,  CString sColName,int nColWidth,BOOL bEdit,int nAlignment)
{
	try			
	{
		if(m_pBodyRecords->GetCount() == 0 )
		{
			MyAddItem(nCol,nValue, sColName,nColWidth, bEdit, nAlignment);		
			GetReportHeader()->GetControl()->GetColumns()->GetAt(nCol)->SetTreeColumn(TRUE);

			return ;
		}

		CString sVal;
		char buffer[10];
		if(m_pBodyRecords->GetCount() > 0){

			for(int i = 0; i < m_pBodyRecords->GetCount(); i++)
			{			
				//CXTPGridColumn *pCol = NULL;
				CXTPGridColumn *pCol = GetColumns()->GetAt(nCol);				
				sVal = m_pBodyRecords->GetAt(i)->GetItem(nCol)->GetCaption(pCol);
				if(sVal == ltoa(nValue, buffer,10) )
				{					
					CXTPGridRecords *pChildRecords = m_pBodyRecords->GetAt(i)->GetChilds();
					m_pSubTarGetRecord = (CMyXTPGridRecord*)pChildRecords->Add(new CMyXTPGridRecord());					
					m_pSubTarGetRecord->MySubAddItem(nValue);					
					m_bTreeItem = TRUE;
					return ;
				}
			}
		}

		this->MyAddItem(nValue);	
		return ;
	}
	catch (char* e)
	{
		UNUSED_ALWAYS(e);

		//e;
		//MessageBox(e, "확인",MB_ICONINFORMATION);
		//qsLog.Print(e);
	}


}

void CDataBox::TreeChildDepthAddItem(int nCol,CString sRef,long nParentNo, CString sValue,  CString sColName,int nColWidth,BOOL bEdit,int nAlignment)
{
	try			
	{
		if(m_pBodyRecords->GetCount() == 0 && !m_bHeader )
		{

			CXTPGridColumn *pCol = ColumnInit(nCol,sColName, nColWidth,bEdit,nAlignment );	
			pCol->SetTreeColumn(TRUE);
		}
		if(!GetColumns()->GetAt(nCol)->IsTreeColumn())
			GetColumns()->GetAt(nCol)->SetTreeColumn(TRUE);

		/*
		if(GetRecords()->GetCount() == 0 )
		{
		CMyXTPGridRecord *pRecord;
		pRecord = MyAddItem(sValue, sColName,nColWidth, bEdit, nAlignment);		
		GetColumns()->GetAt(nCol)->SetTreeColumn(TRUE);			


		pRecord->m_sTreeRef = sRef;
		pRecord->m_nTreeParentNo = nParentNo;
		return;
		}
		*/

		if(sRef.GetLength() == 0)
		{
			CMyXTPGridRecord *pRecord = MyAddItem(sValue);			

			pRecord->m_nTreeParentNo = nParentNo;
			pRecord->m_sTreeRef = sRef;			 
		}
		else
		{		
			int nLen = sRef.GetLength();			
			//qsLog.Print("레코드수%d 회 1\n" , GetRecords()->GetCount());
			for(int i= 0; i < GetRecords()->GetCount(); i++)
			{
				CMyXTPGridRecord *pAllRecord = (CMyXTPGridRecord *)GetRecords()->GetAt(i);
				if(pAllRecord->m_nTreeParentNo == nParentNo && pAllRecord->m_sTreeRef.GetLength() ==0)
				{
					CMyXTPGridRecord *pTempRecord = pAllRecord;
					BOOL bFind = FALSE;
					//qsLog.Print("childs %d, sRef : %s ", pTempRecord->GetChilds()->GetCount(), sRef);
					for(int nStep = 1; nStep <= nLen; nStep++)
					{					
						if(pTempRecord->HasChildren())
						{							
							pTempRecord =  ChildSearchRecord(pTempRecord->GetChilds(), sRef, nStep);
							if(nStep == nLen && pTempRecord->m_sTreeRef == sRef )
							{
								m_pSubTarGetRecord = (CMyXTPGridRecord*)pTempRecord->GetChilds()->Add(new CMyXTPGridRecord);
								m_pSubTarGetRecord->MySubAddItem(sValue);
								//qsLog.Print("%d 회 1\n" , nCount2++);
								m_pSubTarGetRecord->m_sTreeRef = sRef;
								m_pSubTarGetRecord->m_nTreeParentNo =  nParentNo;
								m_bTreeItem = TRUE;
								bFind = TRUE;
								return;
							}


						}		


					}
					// 해당 Ref 가 없으면 새로 넣는다...
					if(pTempRecord == pAllRecord)
					{
						m_pSubTarGetRecord = (CMyXTPGridRecord*)pAllRecord->GetChilds()->Add(new CMyXTPGridRecord());
						m_pSubTarGetRecord->SetExpanded(TRUE);
						//qsLog.Print("%d 회 2\n" , nCount2++);
					}					
					else if(bFind == FALSE && pTempRecord != NULL)
					{
						m_pSubTarGetRecord = (CMyXTPGridRecord*)pTempRecord->GetChilds()->Add(new CMyXTPGridRecord());						
						m_pSubTarGetRecord->SetExpanded(TRUE);
						//qsLog.Print("%d 회 3\n" , nCount2++);
					}

					m_pSubTarGetRecord->MySubAddItem(sValue);
					m_pSubTarGetRecord->m_sTreeRef = sRef;
					m_pSubTarGetRecord->m_nTreeParentNo =  nParentNo;
					m_bTreeItem = TRUE;
				}


			}			
		}
	}
	catch (char* e)
	{
		UNUSED_ALWAYS(e);

		//e;
		//MessageBox(e, "확인",MB_ICONINFORMATION);
		//qsLog.Print(e);
	}

}

void CDataBox::TreeChildDepthAddItem(int nCol,CString sRef,long nParentNo, long nValue, CString sColName,int nColWidth,BOOL bEdit,int nAlignment)
{
	try			
	{
		if(m_pBodyRecords->GetCount() == 0 && !m_bHeader )
		{
			CXTPGridColumn *pCol = ColumnInit(nCol,sColName, nColWidth,bEdit,nAlignment );	
			pCol->SetTreeColumn(TRUE);
		}
		if(!GetColumns()->GetAt(nCol)->IsTreeColumn())
			GetColumns()->GetAt(nCol)->SetTreeColumn(TRUE);
		/*
		if(GetRecords()->GetCount() == 0 )
		{
		CMyXTPGridRecord *pRecord;
		pRecord = MyAddItem(nValue, sColName,nColWidth, bEdit, nAlignment);		
		GetColumns()->GetAt(nCol)->SetTreeColumn(TRUE);			
		pRecord->m_sTreeRef = sRef;
		pRecord->m_nTreeParentNo = nParentNo;
		return;
		}
		*/

		if(sRef.GetLength() == 0)
		{
			CMyXTPGridRecord *pRecord = MyAddItem(nValue);			 
			pRecord->m_nTreeParentNo = nParentNo;
			pRecord->m_sTreeRef = sRef;			 

		}
		else
		{		
			int nLen = sRef.GetLength();			
			//qsLog.Print("레코드수%d 회 1\n" , GetRecords()->GetCount());
			for(int i= 0; i < GetRecords()->GetCount(); i++)
			{
				CMyXTPGridRecord *pAllRecord = (CMyXTPGridRecord *)GetRecords()->GetAt(i);
				if(pAllRecord->m_nTreeParentNo == nParentNo && pAllRecord->m_sTreeRef.GetLength() ==0)
				{
					CMyXTPGridRecord *pTempRecord = pAllRecord;
					BOOL bFind = FALSE;
					//qsLog.Print("childs %d, sRef : %s ", pTempRecord->GetChilds()->GetCount(), sRef);
					for(int nStep = 1; nStep <= nLen; nStep++)
					{					
						if(pTempRecord->HasChildren())
						{							
							pTempRecord =  ChildSearchRecord(pTempRecord->GetChilds(), sRef, nStep);
							if(nStep == nLen && pTempRecord->m_sTreeRef == sRef )
							{
								m_pSubTarGetRecord = (CMyXTPGridRecord*)pTempRecord->GetChilds()->Add(new CMyXTPGridRecord);
								m_pSubTarGetRecord->MySubAddItem(nValue);
								//qsLog.Print("%d 회 1\n" , ++);
								m_pSubTarGetRecord->m_sTreeRef = sRef;
								m_pSubTarGetRecord->m_nTreeParentNo =  nParentNo;
								m_bTreeItem = TRUE;
								bFind = TRUE;
								return;
							}
						}		


					}

					if(pTempRecord == pAllRecord)
					{
						m_pSubTarGetRecord = (CMyXTPGridRecord*)pAllRecord->GetChilds()->Add(new CMyXTPGridRecord());					
						//qsLog.Print("%d 회 2\n" , nCount2++);
					}					
					else if(bFind == FALSE && pTempRecord != NULL)
					{
						m_pSubTarGetRecord = (CMyXTPGridRecord*)pTempRecord->GetChilds()->Add(new CMyXTPGridRecord());						
						//qsLog.Print("%d 회 3\n" , nCount2++);
					}

					m_pSubTarGetRecord->MySubAddItem(nValue);
					m_pSubTarGetRecord->m_sTreeRef = sRef;
					m_pSubTarGetRecord->m_nTreeParentNo =  nParentNo;
					m_bTreeItem = TRUE;
				}
				return;

			}			
		}
	}
	catch (char* e)
	{
		UNUSED_ALWAYS(e);

		//e;
		//MessageBox(e, "확인",MB_ICONINFORMATION);
		//qsLog.Print(e);
	}

}
void CDataBox::TreeChildDepthAddItem(int nCol,CString sRef,long nParentNo, COleDateTime dtValue,  CString sColName,int nColWidth,BOOL bEdit,int nAlignment)
{
	try			
	{
		if(m_pBodyRecords->GetCount() == 0 && !m_bHeader )
		{
			CXTPGridColumn *pCol = ColumnInit(nCol,sColName, nColWidth,bEdit,nAlignment );	
			pCol->SetTreeColumn(TRUE);
		}
		if(!GetColumns()->GetAt(nCol)->IsTreeColumn())
			GetColumns()->GetAt(nCol)->SetTreeColumn(TRUE);
		/*
		if(GetRecords()->GetCount() == 0 )
		{
		CMyXTPGridRecord *pRecord;
		pRecord = MyAddItem(dtValue, sColName,nColWidth, bEdit, nAlignment);		
		GetColumns()->GetAt(nCol)->SetTreeColumn(TRUE);			
		pRecord->m_sTreeRef = sRef;
		pRecord->m_nTreeParentNo = nParentNo;
		return;
		}
		*/

		if(sRef.GetLength() == 0)
		{
			// m_bTreeItem =기본적으로 TRUE 이다  EndItem 에서 TRUE로 처리됨 m_pMainRecord 

			CMyXTPGridRecord *pRecord = MyAddItem(dtValue);			 
			pRecord->m_nTreeParentNo = nParentNo;
			pRecord->m_sTreeRef = sRef;			 
		}
		else
		{		
			// 이밑에선 m_pSubTarGetRecord 로 뽑아서 처리한다
			int nLen = sRef.GetLength();			
			//qsLog.Print("레코드수%d 회 1\n" , GetRecords()->GetCount());
			for(int i= 0; i < GetRecords()->GetCount(); i++)
			{
				CMyXTPGridRecord *pAllRecord = (CMyXTPGridRecord *)GetRecords()->GetAt(i);
				if(pAllRecord->m_nTreeParentNo == nParentNo && pAllRecord->m_sTreeRef.GetLength() ==0)
				{
					CMyXTPGridRecord *pTempRecord = pAllRecord;
					BOOL bFind = FALSE;
					//qsLog.Print("childs %d, sRef : %s ", pTempRecord->GetChilds()->GetCount(), sRef);
					for(int nStep = 1; nStep <= nLen; nStep++)
					{					
						if(pTempRecord->HasChildren())
						{							
							pTempRecord =  ChildSearchRecord(pTempRecord->GetChilds(), sRef, nStep);
							if(nStep == nLen && pTempRecord->m_sTreeRef == sRef )
							{
								m_pSubTarGetRecord = (CMyXTPGridRecord*)pTempRecord->GetChilds()->Add(new CMyXTPGridRecord);
								m_pSubTarGetRecord->MySubAddItem(dtValue);
								//qsLog.Print("%d 회 1\n" , nCount2++);
								m_pSubTarGetRecord->m_sTreeRef = sRef;
								m_pSubTarGetRecord->m_nTreeParentNo =  nParentNo;
								m_bTreeItem = TRUE;
								bFind = TRUE;
								return;
							}
						}		


					}

					if(pTempRecord == pAllRecord)
					{
						m_pSubTarGetRecord = (CMyXTPGridRecord*)pAllRecord->GetChilds()->Add(new CMyXTPGridRecord());					
						//qsLog.Print("%d 회 2\n" , nCount2++);
					}					
					else if(bFind == FALSE && pTempRecord != NULL)
					{
						m_pSubTarGetRecord = (CMyXTPGridRecord*)pTempRecord->GetChilds()->Add(new CMyXTPGridRecord());						
						//qsLog.Print("%d 회 3\n" , nCount2++);
					}

					m_pSubTarGetRecord->MySubAddItem(dtValue);
					m_pSubTarGetRecord->m_sTreeRef = sRef;
					m_pSubTarGetRecord->m_nTreeParentNo =  nParentNo;
					m_bTreeItem = TRUE;
				}
				return;

			}			
		}
	}
	catch (char* e)
	{
		UNUSED_ALWAYS(e);
		//e;
		//MessageBox(e, "확인",MB_ICONINFORMATION);
		//qsLog.Print(e);
	}

}

void CDataBox::TreeChildDepthAddItem(int nCol,CString sRef,long nParentNo, int iValue,  CString sColName,int nColWidth,BOOL bEdit,int nAlignment)
{
	try			
	{
		if(m_pBodyRecords->GetCount() == 0 && !m_bHeader )
		{
			CXTPGridColumn *pCol = ColumnInit(nCol,sColName, nColWidth,bEdit,nAlignment );	
			pCol->SetTreeColumn(TRUE);
		}
		if(!GetColumns()->GetAt(nCol)->IsTreeColumn())
			GetColumns()->GetAt(nCol)->SetTreeColumn(TRUE);
		/*
		if(GetRecords()->GetCount() == 0 )
		{
		CMyXTPGridRecord *pRecord;
		pRecord = MyAddItem(iValue, sColName,nColWidth, bEdit, nAlignment);		
		GetColumns()->GetAt(nCol)->SetTreeColumn(TRUE);			
		pRecord->m_sTreeRef = sRef;
		pRecord->m_nTreeParentNo = nParentNo;
		return;
		}
		*/
		if(sRef.GetLength() == 0)
		{
			CMyXTPGridRecord *pRecord = MyAddItem(iValue);			 
			pRecord->m_nTreeParentNo = nParentNo;
			pRecord->m_sTreeRef = sRef;			 
		}
		else
		{		
			int nLen = sRef.GetLength();			
			//qsLog.Print("레코드수%d 회 1\n" , GetRecords()->GetCount());
			for(int i= 0; i < GetRecords()->GetCount(); i++)
			{
				CMyXTPGridRecord *pAllRecord = (CMyXTPGridRecord *)GetRecords()->GetAt(i);
				if(pAllRecord->m_nTreeParentNo == nParentNo && pAllRecord->m_sTreeRef.GetLength() ==0)
				{
					CMyXTPGridRecord *pTempRecord = pAllRecord;
					BOOL bFind = FALSE;
					//qsLog.Print("childs %d, sRef : %s ", pTempRecord->GetChilds()->GetCount(), sRef);
					for(int nStep = 1; nStep <= nLen; nStep++)
					{					
						if(pTempRecord->HasChildren())
						{							
							pTempRecord =  ChildSearchRecord(pTempRecord->GetChilds(), sRef, nStep);
							if(nStep == nLen && pTempRecord->m_sTreeRef == sRef )
							{
								m_pSubTarGetRecord = (CMyXTPGridRecord*)pTempRecord->GetChilds()->Add(new CMyXTPGridRecord);
								m_pSubTarGetRecord->MySubAddItem(iValue);
								//qsLog.Print("%d 회 1\n" , nCount2++);
								m_pSubTarGetRecord->m_sTreeRef = sRef;
								m_pSubTarGetRecord->m_nTreeParentNo =  nParentNo;
								m_bTreeItem = TRUE;
								bFind = TRUE;
								return;
							}
						}		


					}

					if(pTempRecord == pAllRecord)
					{
						m_pSubTarGetRecord = (CMyXTPGridRecord*)pAllRecord->GetChilds()->Add(new CMyXTPGridRecord());					
						//qsLog.Print("%d 회 2\n" , nCount2++);
					}					
					else if(bFind == FALSE && pTempRecord != NULL)
					{
						m_pSubTarGetRecord = (CMyXTPGridRecord*)pTempRecord->GetChilds()->Add(new CMyXTPGridRecord());						
						//qsLog.Print("%d 회 3\n" , nCount2++);
					}

					m_pSubTarGetRecord->MySubAddItem(iValue);
					m_pSubTarGetRecord->m_sTreeRef = sRef;
					m_pSubTarGetRecord->m_nTreeParentNo =  nParentNo;
					m_bTreeItem = TRUE;
				}
				return;

			}			
		}
	}
	catch (char* e)
	{
		UNUSED_ALWAYS(e);

	//e;
		//MessageBox(e, "확인",MB_ICONINFORMATION);
		//qsLog.Print(e);
	}

}

CMyXTPGridRecord* CDataBox::ChildSearchRecord(CXTPGridRecords *pRecords,CString sTreeRef, int nStep)
{

	CMyXTPGridRecord *pFindRecord = NULL;
	CString sSearchWord, sListWord;
	//qsLog.Print("내부 %s, %d", sTreeRef  ,nStep);
	for(int nFind =  0; nFind < pRecords->GetCount(); nFind++)
	{
		pFindRecord = (CMyXTPGridRecord *)pRecords->GetAt(nFind);
		sListWord = pFindRecord->m_sTreeRef;
		sSearchWord = sTreeRef.Left(nStep);
		if(sListWord.Compare(sSearchWord) ==0) //pFindRecord->m_sTreeRef == sTreeRef.Left(nStep) )
			return pFindRecord;


	}
	pFindRecord = (CMyXTPGridRecord*)pRecords->GetOwnerRecord();

	return pFindRecord;

}





void CDataBox::MyAddItem(CMkRecordset &pRs, BOOL bAutoColumns)
{	

	CString sFieldName;
	int j = 0;

	//if(this->GetReportHeader()->GetControl()->GetColumns()->GetCount() == 0)
	if(m_bHeader == FALSE )
	{

		for( j=0;bAutoColumns && j < pRs.GetFiledCount(); j++)		
		{				
			sFieldName = pRs.GetFieldName(j);
			CXTPGridColumn *pCol = this->AddColumn(new CXTPGridColumn(j,sFieldName,50));
			pCol->GetEditOptions()->m_bAllowEdit = FALSE;

		}
		this->GetReportHeader()->SetAutoColumnSizing(TRUE);
		this->GetReportHeader()->AllowColumnRemove(FALSE);
		this->GetReportHeader()->AllowColumnResize(TRUE);

		this->GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
		this->GetPaintManager()->m_strNoItems = "해당사항없음";
		this->GetPaintManager()->SetGridStyle(TRUE,xtpGridSolid);
		this->AllowEdit(FALSE);

		if(m_wndSubList)
			GetColumns()->GetReportHeader()->SetSubListCtrl(&m_wndSubList);
		if(m_wndFilterEdit)
			GetColumns()->GetReportHeader()->SetFilterEditCtrl(&m_wndFilterEdit);
		m_bHeader = TRUE;
	}



	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{		
		for(j = 0; j < pRs.GetFiledCount(); j++)
		{
			sFieldName = pRs.GetFieldName(j);				
			this->MyAddItem(j,pRs,sFieldName);
		}		
		pRs.MoveNext();
		EndItem();	

	}	


}
void CDataBox::MyAddItem(int nCol,CMkRecordset &pRs, CString sFieldName)
{
	//typeInt = 2,
	//typeLong = 3,
	//typeBool = 11,
	//typeDate = 7,
	//typeString = 202,
	//typeWStr = 203
	int nType = 0;
	int niValue; long nlValue; BOOL bValue; COleDateTime dtValue; CString sValue; 
	nType = pRs.GetFieldType(nCol);

	switch(nType)
	{
	case 2:
		pRs.GetFieldValue(sFieldName,niValue);
		this->MyAddItem(nCol,niValue,sFieldName,50, FALSE,0);
		break;
	case 3:
		pRs.GetFieldValue(sFieldName,nlValue);
		this->MyAddItem(nCol,nlValue,sFieldName,50, FALSE,0);
		break;
	case 11:
		pRs.GetFieldValue(sFieldName,(int)bValue);
		this->MyAddItem(nCol,bValue ? TRUE : FALSE,sFieldName,50, FALSE,0);
		//this->MyAddItem(bValue,sFieldName);
		break;
	case 7:
		pRs.GetFieldValue(sFieldName,dtValue);
		this->MyAddItem(nCol,dtValue,sFieldName,50, FALSE,0);
		break;
	case 202:
		pRs.GetFieldValue(sFieldName,sValue);
		this->MyAddItem(nCol,sValue,sFieldName,50, FALSE,0);
		break;
	case 203:
		pRs.GetFieldValue(sFieldName,sValue);
		this->MyAddItem(nCol,sValue,sFieldName,50, FALSE,0);
		break;
	}

}

CXTPGridColumn* CDataBox::ColumnInit(int nCol, CString sColName,int nColWidth, BOOL bEdit, int nAlignment)
{	
	CXTPGridColumn *pCol= AddColumn(new CXTPGridColumn(nCol,sColName,nColWidth));	
	pCol->GetEditOptions()->m_bAllowEdit = bEdit;
	pCol->SetAlignment(nAlignment);	
	return pCol;	

}

CMyXTPGridRecord* CDataBox::MyComboAddItem(int nCol,CStringArray &sArray,CUIntArray &nArray,  CString sColName,int nColWidth,int nArignMent, int nDefaultValue)
{
	CXTPGridColumn *pCol = NULL;

	if(m_pBodyRecords->GetCount() == 0 && !m_bHeader )
		pCol = ColumnInit(nCol, sColName, nColWidth,FALSE,nArignMent );	


	if(pCol == NULL)
		pCol = GetColumns()->GetAt(nCol);
	for(int i = 0; i < sArray.GetCount(); i++)
		pCol->GetEditOptions()->AddConstraint(_T(sArray.GetAt(i)), nArray.GetAt(i));

	pCol->GetEditOptions()->m_bConstraintEdit = FALSE;
	pCol->GetEditOptions()->m_bAllowEdit = FALSE;		
	pCol->GetEditOptions()->AddComboButton();



	if(pCol == NULL)
		LF->MsgBox("콤보컬럼 입력안됨");

	if(m_bTreeItem)
		m_pSubTarGetRecord->MySubComboAddItem(sArray, nArray, nDefaultValue );		
	else
		m_pMainRecord->MySubComboAddItem(sArray, nArray, nDefaultValue );


	return m_bTreeItem ? m_pMainRecord : m_pSubTarGetRecord;
}

CMyXTPGridRecord* CDataBox::MyCheckAddItem(int nCol,BOOL bDefaultValue ,CString sColName,int nColWidth,int nArignMent ,BOOL bCheckBox)
{
	CXTPGridColumn *pCol = NULL;
	if(m_pBodyRecords->GetCount() == 0 && !m_bHeader )
		pCol = ColumnInit(nCol,sColName, nColWidth,FALSE,nArignMent );

	if(bCheckBox)
	{	
		if(m_bTreeItem)
			m_pSubTarGetRecord->MySubCheckAddItem(bDefaultValue);
		else
			m_pMainRecord->MySubCheckAddItem(bDefaultValue );
	}
	else
	{
		if(m_bTreeItem)
			m_pSubTarGetRecord->MySubAddItem("");
		else
			m_pMainRecord->MySubAddItem("");

	}



	return m_bTreeItem ? m_pMainRecord : m_pSubTarGetRecord;
}
CMyXTPGridRecord* CDataBox::MyAddItem(int nCol,int niValue, CString sColName, int nColWidth,BOOL bEdit,int nAlignment)
{	
	if(m_pBodyRecords->GetCount() == 0 && !m_bHeader  )
		ColumnInit(nCol,sColName, nColWidth,bEdit,nAlignment );

	return MyAddItem(niValue);	

}
CMyXTPGridRecord* CDataBox::MyAddItem(int nCol,long nlValue, CString sColName, int nColWidth,BOOL bEdit,int nAlignment)
{	
	if(m_pBodyRecords->GetCount() == 0 && !m_bHeader  )
		ColumnInit(nCol,sColName, nColWidth,bEdit,nAlignment);

	return MyAddItem(nlValue);			
}
CMyXTPGridRecord* CDataBox::MyAddItem(int nCol,COleDateTime dtValue, CString sColName, int nColWidth,BOOL bEdit,int nAlignment)
{	
	if(m_pBodyRecords->GetCount() == 0  && !m_bHeader )
		ColumnInit(nCol,sColName, nColWidth,bEdit,nAlignment  );

	return MyAddItem(dtValue);		
}
CMyXTPGridRecord* CDataBox::MyAddItem(int nCol,CString sValue, CString sColName, int nColWidth,BOOL bEdit,int nAlignment)
{	
	if(m_pBodyRecords->GetCount() == 0  && !m_bHeader  )
		ColumnInit(nCol,sColName, nColWidth,bEdit,nAlignment  );

	return MyAddItem(sValue);	
}


CMyXTPGridRecord* CDataBox::MyAddItem(int niValue)
{	
	if(m_bTreeItem)	
		m_pSubTarGetRecord->MySubAddItem(niValue);
	else
		m_pMainRecord->MySubAddItem(niValue);

	return m_bTreeItem ? m_pSubTarGetRecord: m_pMainRecord;
}

CMyXTPGridRecord* CDataBox::MyAddItem(long nlValue)
{
	if(m_bTreeItem)
		m_pSubTarGetRecord->MySubAddItem(nlValue);
	else
		m_pMainRecord->MySubAddItem(nlValue);


	return m_bTreeItem ? m_pSubTarGetRecord: m_pMainRecord;
}
CMyXTPGridRecord* CDataBox::MyAddItem(COleDateTime dtValue,CString sFormat)
{
	if(m_bTreeItem)
		m_pSubTarGetRecord->MySubAddItem(dtValue,sFormat);
	else
		m_pMainRecord->MySubAddItem(dtValue,sFormat);

	return m_bTreeItem ? m_pSubTarGetRecord: m_pMainRecord;

}
CMyXTPGridRecord* CDataBox::MyAddItem(CString sValue)
{
	//qsLog.Print("%s", sValue);
	if(m_bTreeItem)
		m_pSubTarGetRecord->MySubAddItem(sValue);
	else
		m_pMainRecord->MySubAddItem(sValue);

	return m_bTreeItem ? m_pSubTarGetRecord: m_pMainRecord;

}


BOOL CDataBox::GetItemCheck(int nReportRow, int nCol)
{
	CMyXTPGridRecord *pRecord  = (CMyXTPGridRecord *)GetRows()->GetAt(nReportRow)->GetRecord();
	if(pRecord == NULL)
	{
		MessageBox("체크중에 문제가 있습니다.");
		return FALSE;
	}
	CXTPGridRecordItem *pItem =  pRecord->GetItem(nCol);
	if(!pItem->GetHasCheckbox())
		return FALSE;

	CMyCheckRecordItem *pCheckItem = (CMyCheckRecordItem *)pItem;
	return pCheckItem->GetCheck();
}
BOOL CDataBox::GetItemRecordRowCheck(int nRecord, int nCol)
{
	CMyXTPGridRecord *pRecord  = (CMyXTPGridRecord *)GetRecords()->GetAt(nRecord);
	if(pRecord == NULL)
	{
		MessageBox("체크중에 문제가 있습니다.");
		return FALSE;
	}
	CXTPGridRecordItem *pItem =  pRecord->GetItem(nCol);
	if(!pItem->GetHasCheckbox())
		return FALSE;

	CMyCheckRecordItem *pCheckItem = (CMyCheckRecordItem *)pItem;
	return pCheckItem->GetCheck();
}
void CDataBox::SetItemRecordRowCheck(int nRecord, int nCol,BOOL bCheck)
{
	CMyXTPGridRecord *pRecord  = (CMyXTPGridRecord *)GetRecords()->GetAt(nRecord);
	CMyCheckRecordItem *pItem =  (CMyCheckRecordItem *)pRecord->GetItem(nCol);
	if(pItem->GetHasCheckbox())
	{
		CMyCheckRecordItem *pCheckItem = (CMyCheckRecordItem *)pItem;
		pCheckItem->SetChecked(bCheck);
		pRecord->m_bDirtyFlag = TRUE;
	}
	else
	{
		MessageBox("체크박스가 아니거나 오류입니다.", "확인", MB_ICONINFORMATION);
		return;
	}

}

void CDataBox::SetItemCheck(int nReportRow, int nCol,BOOL bCheck)
{
	CMyXTPGridRecord *pRecord  = (CMyXTPGridRecord *)GetRows()->GetAt(nReportRow)->GetRecord();
	CMyCheckRecordItem *pItem =  (CMyCheckRecordItem *)pRecord->GetItem(nCol);
	if(pItem->GetHasCheckbox())
	{


		CMyCheckRecordItem *pCheckItem = (CMyCheckRecordItem *)pItem;
		pCheckItem->SetChecked(bCheck);
		pRecord->m_bDirtyFlag = TRUE;
	}
	else
	{
		MessageBox("체크박스가 아니거나 오류입니다.", "확인", MB_ICONINFORMATION);
		return;
	}

}



void CDataBox::DeleteAllItem()
{
	//this->ResetContent();	
	this->GetRecords()->RemoveAll();
	//this->InternalAddRef();

}
void CDataBox::ShowRow(CXTPGridRow *pRow)
{
	pRow->GetRecord()->SetVisible(TRUE);
}

void CDataBox::ShowRow(int nItem)
{
	ShowRow(GetRows()->GetAt(nItem));
}

void CDataBox::HideRow(CXTPGridRow *pRow)
{
	pRow->GetRecord()->SetVisible(FALSE);
}

void CDataBox::HideRow(int nItem)
{
	HideRow(GetRows()->GetAt(nItem));
}

void CDataBox::HideRecord(int nItem)
{
	GetRecords()->GetAt(nItem)->SetVisible(FALSE);
}
void CDataBox::HideRecord(CMyXTPGridRecord *pRecord)
{
	pRecord->SetVisible(FALSE);
}
void CDataBox::ShowRecord(int nItem)
{
	GetRecords()->GetAt(nItem)->SetVisible(TRUE);
}
void CDataBox::ShowRecord(CMyXTPGridRecord *pRecord)
{
	pRecord->SetVisible(TRUE);
}

void CDataBox::ShowAllRow()
{
	CXTPGridRecords *pRecords = GetRecords();		

	for(int i = 0; i < pRecords->GetCount(); i++)
	{
		pRecords->GetAt(i)->SetVisible(TRUE);
	}

	Populate();
}

/// Control 관련 Popup

void CDataBox::LoadReportState()
{
#ifdef XML_STATE
	CXTPPropExchangeXMLNode px(TRUE, 0, _T("ReportControl"));
	if (!px.LoadFromFile(_T("c:\\ReportControl.xml")))
		return;

	this->DoPropExchange(&px);

#else	
	UINT nBytes = 0;
	LPBYTE pData = 0;
	CString sParentWindowName = "";
	int nID = this->GetParent()->GetDlgCtrlID();
	this->GetParent()->GetWindowText(sParentWindowName);
	sParentWindowName.Format("%s_%d",sParentWindowName, nID);

	//if (!AfxGetApp()->GetProfileBinary(_T("ReportControl"), _T("State"), &pData, &nBytes))
	if (!AfxGetApp()->GetProfileBinary(_T("ReportControl"), sParentWindowName, &pData, &nBytes))
		return;

	CMemFile memFile(pData, nBytes);
	CArchive ar (&memFile,CArchive::load);

	try
	{
		this->SerializeState(ar);

	}
	catch (COleException* pEx)
	{
		pEx->Delete ();
	}
	catch (CArchiveException* pEx)
	{
		pEx->Delete ();
	}

	ar.Close();
	memFile.Close();
	delete[] pData;
#endif
}
void CDataBox::SaveReportState()
{

#ifdef XML_STATE

	CXTPPropExchangeXMLNode px(FALSE, 0, _T("ReportControl"));
	this->DoPropExchange(&px);
	px.SaveToFile(_T("c:\\ReportControl.xml"));

#else
	CMemFile memFile;
	CArchive ar (&memFile,CArchive::store);

	this->SerializeState(ar);

	ar.Flush();

	DWORD nBytes = (DWORD)memFile.GetPosition();
	LPBYTE pData = memFile.Detach();

	CString sParentWindowName = "";
	int nID = this->GetParent()->GetDlgCtrlID();
	this->GetParent()->GetWindowText(sParentWindowName);
	sParentWindowName.Format("%s_%d",sParentWindowName, nID);
	AfxGetApp()->WriteProfileBinary(_T("ReportControl"), sParentWindowName, pData, nBytes);

	ar.Close();
	memFile.Close();
	free(pData);
#endif

}



#define ID_REMOVE_ITEM								1
#define ID_SORT_ASC									2
#define ID_SORT_DESC								3
#define ID_GROUP_BYTHIS								4
#define ID_SHOW_GROUPBOX							5
#define ID_SHOW_FIELDCHOOSER						6
#define ID_COLUMN_BESTFIT							7
#define ID_COLUMN_ARRANGEBY							100
#define ID_COLUMN_ALIGMENT							200
#define ID_COLUMN_ALIGMENT_LEFT		ID_COLUMN_ALIGMENT + 1
#define ID_COLUMN_ALIGMENT_RIGHT    ID_COLUMN_ALIGMENT + 2
#define ID_COLUMN_ALIGMENT_CENTER   ID_COLUMN_ALIGMENT + 3
#define ID_COLUMN_SHOW								500

//
//ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
//ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
//ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
//
//ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
void CDataBox::ReportColumnSetting(NMHDR * pNotifyStruct)
{




	if(!m_bColumnSelectCreate)
		CreateColumnSelect();

	if(!m_bFilterEditCreate)
		FilterEditCreate();

	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	ASSERT(pItemNotify->pColumn);
	CPoint ptClick = pItemNotify->pt;

	CMenu menu;
	VERIFY(menu.CreatePopupMenu());

	//menu.AppendMenu(MF_STRING, ID_SORT_ASC, LoadResourceString(IDS_SORTASC));
	//menu.AppendMenu(MF_STRING, ID_SORT_DESC, LoadResourceString(IDS_SORTDESC));
	//menu.AppendMenu(MF_STRING, ID_REMOVE_ITEM, LoadResourceString(IDS_REMOVECOL));
	//menu.AppendMenu(MF_STRING, ID_SHOW_FIELDCHOOSER, LoadResourceString(IDS_FIELDCHOOSER));


	menu.AppendMenu(MF_STRING, ID_SORT_ASC, "위아래정렬");
	menu.AppendMenu(MF_STRING, ID_SORT_ASC, "컬럼오름차순");

	menu.AppendMenu(MF_STRING, ID_SORT_DESC, "컬럼내림차순");
	menu.AppendMenu(MF_SEPARATOR, (UINT)-1, (LPCTSTR)NULL);

	menu.AppendMenu(MF_STRING, ID_SEARCH_EDIT, "내용검색");
	menu.AppendMenu(MF_SEPARATOR, (UINT)-1, (LPCTSTR)NULL);

	menu.AppendMenu(MF_STRING, ID_REMOVE_ITEM, "컬럼지우기");	
	menu.AppendMenu(MF_STRING, ID_SHOW_FIELDCHOOSER, "컬럼선택창");
	menu.AppendMenu(MF_SEPARATOR, (UINT)-1, (LPCTSTR)NULL);

	menu.AppendMenu(MF_STRING, ID_COLUMN_BESTFIT, "적정사이즈");
	menu.AppendMenu(MF_SEPARATOR, (UINT)-1, (LPCTSTR)NULL);

	menu.AppendMenu(MF_STRING, ID_FILE_PRINT_DIRECT, "프린트");
	menu.AppendMenu(MF_STRING, ID_FILE_PRINT_PREVIEW, "미리보기");
	menu.AppendMenu(MF_STRING, ID_FILE_PRINT_SETUP, "프린트셋팅");


	CXTPGridColumns* pColumns = GetColumns();
	CXTPGridColumn* pColumn = pItemNotify->pColumn;

	// create arrange by items
	CMenu menuArrange;
	VERIFY(menuArrange.CreatePopupMenu());
	int nColumnCount = pColumns->GetCount();
	int nColumn = 0;
	for (nColumn = 0; nColumn < nColumnCount; nColumn++)
	{
		CXTPGridColumn* pCol = pColumns->GetAt(nColumn);
		if (pCol && pCol->IsVisible())
		{
			CString sCaption = pCol->GetCaption();
			if (!sCaption.IsEmpty())
				menuArrange.AppendMenu(MF_STRING, ID_COLUMN_ARRANGEBY + nColumn, sCaption);
		}
	}

	menuArrange.AppendMenu(MF_SEPARATOR, 60, (LPCTSTR)NULL);
	//menuArrange.AppendMenu(MF_STRING, ID_COLUMN_ARRANGEBY + nColumnCount,	LoadResourceString(IDS_SHOWINGROUPS));

	menuArrange.CheckMenuItem(ID_COLUMN_ARRANGEBY + nColumnCount,
		MF_BYCOMMAND | ((GetReportHeader()->IsShowItemsInGroups()) ? MF_CHECKED : MF_UNCHECKED)  );
	//menu.InsertMenu(0, MF_BYPOSITION | MF_POPUP, (UINT_PTR) menuArrange.m_hMenu,LoadResourceString(IDS_ARRANGEBY));
	menu.InsertMenu(0, MF_BYPOSITION | MF_POPUP, (UINT_PTR) menuArrange.m_hMenu,"컬럼정렬");
	// create columns items
	CMenu menuColumns;
	VERIFY(menuColumns.CreatePopupMenu());
	for (nColumn = 0; nColumn < nColumnCount; nColumn++)
	{
		CXTPGridColumn* pCol = pColumns->GetAt(nColumn);
		CString sCaption = pCol->GetCaption();
		//if (!sCaption.IsEmpty())
		menuColumns.AppendMenu(MF_STRING, ID_COLUMN_SHOW + nColumn, sCaption);
		menuColumns.CheckMenuItem(ID_COLUMN_SHOW + nColumn,
			MF_BYCOMMAND | (pCol->IsVisible() ? MF_CHECKED : MF_UNCHECKED) );
	}

	//menu.InsertMenu(0, MF_BYPOSITION | MF_POPUP, (UINT_PTR) menuColumns.m_hMenu,LoadResourceString(IDS_COLUMNS));
	menu.InsertMenu(0, MF_BYPOSITION | MF_POPUP, (UINT_PTR) menuColumns.m_hMenu,"컬럼선택");



	//create Text alignment submenu
	CMenu menuAlign;
	VERIFY(menuAlign.CreatePopupMenu());

	//menuAlign.AppendMenu(MF_STRING, ID_COLUMN_ALIGMENT_LEFT,	LoadResourceString(IDS_ALIGNLEFT));
	//menuAlign.AppendMenu(MF_STRING, ID_COLUMN_ALIGMENT_RIGHT,	LoadResourceString(IDS_ALIGNRIGHT));
	//menuAlign.AppendMenu(MF_STRING, ID_COLUMN_ALIGMENT_CENTER,	LoadResourceString(IDS_ALIGNCENTER));
	menuAlign.AppendMenu(MF_STRING, ID_COLUMN_ALIGMENT_LEFT,	"왼쪽정렬");
	menuAlign.AppendMenu(MF_STRING, ID_COLUMN_ALIGMENT_RIGHT,	"오른쪽정렬");
	menuAlign.AppendMenu(MF_STRING, ID_COLUMN_ALIGMENT_CENTER,	"중앙정렬");

	int nAlignOption = 0;
	switch (pColumn->GetAlignment())
	{
	case DT_LEFT :
		nAlignOption = ID_COLUMN_ALIGMENT_LEFT;
		break;
	case DT_RIGHT :
		nAlignOption = ID_COLUMN_ALIGMENT_RIGHT;
		break;
	case DT_CENTER :
		nAlignOption = ID_COLUMN_ALIGMENT_CENTER;
		break;
	}

	menuAlign.CheckMenuItem(nAlignOption, MF_BYCOMMAND | MF_CHECKED);
	//menu.InsertMenu(11, MF_BYPOSITION | MF_POPUP, (UINT_PTR) menuAlign.m_hMenu,	LoadResourceString(IDS_ALIGNMENT));
	menu.InsertMenu(11, MF_BYPOSITION | MF_POPUP, (UINT_PTR) menuAlign.m_hMenu,	"수평정렬");

	// track menu
#ifndef _XTP_INCLUDE_COMMANDBARS
	int nMenuResult = menu.TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN |TPM_RIGHTBUTTON, ptClick.x, ptClick.y, this, NULL);
#else
	int nMenuResult = CXTPCommandBars::TrackPopupMenu(&menu, TPM_NONOTIFY | TPM_RETURNCMD | TPM_LEFTALIGN |TPM_RIGHTBUTTON, ptClick.x, ptClick.y, this, NULL);
#endif


	//arrange by items
	if (nMenuResult >= ID_COLUMN_ARRANGEBY && nMenuResult < ID_COLUMN_ALIGMENT)
	{
		for (int nColumn = 0; nColumn < nColumnCount; nColumn++)
		{
			CXTPGridColumn* pCol = pColumns->GetAt(nColumn);
			if (pCol && pCol->IsVisible())
			{
				if (nMenuResult == ID_COLUMN_ARRANGEBY + nColumn)
				{
					nMenuResult = ID_SORT_ASC;
					pColumn = pCol;
					break;
				}
			}
		}
		// group by item
		if (ID_COLUMN_ARRANGEBY + nColumnCount == nMenuResult)
		{
			GetReportHeader()->ShowItemsInGroups(
				!GetReportHeader()->IsShowItemsInGroups());
		}
	}

	//process Alignment options
	if (nMenuResult > ID_COLUMN_ALIGMENT && nMenuResult < ID_COLUMN_SHOW)
	{
		switch (nMenuResult)
		{
		case ID_COLUMN_ALIGMENT_LEFT :
			pColumn->SetAlignment(DT_LEFT);
			break;
		case ID_COLUMN_ALIGMENT_RIGHT :
			pColumn->SetAlignment(DT_RIGHT);
			break;
		case ID_COLUMN_ALIGMENT_CENTER  :
			pColumn->SetAlignment(DT_CENTER);
			break;
		}
	}

	// process column selection item
	if (nMenuResult >= ID_COLUMN_SHOW)
	{
		CXTPGridColumn* pCol = pColumns->GetAt(nMenuResult - ID_COLUMN_SHOW);
		if (pCol)
		{
			pCol->SetVisible(!pCol->IsVisible());
		}
	}
	//CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	//CWinApp *pFrame = (CWinApp *)AfxGetApp();
	//CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	//	CRcpView *pView = pFrame->GetRcpView();
	CWnd *pWnd = GetParent();
	CWnd *pWndParent = pWnd->GetParent();
	CWnd *pWndParent2 = pWndParent->GetParent();


	CReportView *pView = (CReportView *)pWndParent2;

	// other general items
	switch (nMenuResult)
	{
	case ID_REMOVE_ITEM:
		pColumn->SetVisible(FALSE);
		Populate();
		break;
	case ID_SORT_ASC:
	case ID_SORT_DESC:
		if (pColumn && pColumn->IsSortable())
		{
			pColumns->SetSortColumn(pColumn, nMenuResult == ID_SORT_ASC);
			Populate();
		}
		break;
	case ID_SEARCH_EDIT:
		{
			OnShowSearchWord();
		}
		break;
	case ID_GROUP_BYTHIS:
		if (pColumns->GetGroupsOrder()->IndexOf(pColumn) < 0)
		{
			pColumns->GetGroupsOrder()->Add(pColumn);
		}
		ShowGroupBy(TRUE);
		Populate();
		break;
	case ID_SHOW_GROUPBOX:
		ShowGroupBy(!IsGroupByVisible());
		break;
	case ID_SHOW_FIELDCHOOSER:
		//OnShowFieldChooser();
		OnShowFieldChooser();
		break;
	case ID_COLUMN_BESTFIT:
		GetColumns()->GetReportHeader()->BestFit(pColumn);
		break;

	case ID_FILE_PRINT_DIRECT:		
		MyPrint();	
		break;

	case ID_FILE_PRINT_PREVIEW:
		MyPrintPreview();	
		break;
	case ID_FILE_PRINT_SETUP:

		break;

	}

}


void CDataBox::MyPrint()
{





	//if (m_pTaskFrame)
	//{
	//	m_pTaskFrame->ActivateFrame(SW_SHOW);
	//	return;
	//}
	//CCreateContext contextT;	
	//// currently selected client if possible.
	//contextT.m_pLastView       = NULL;
	//contextT.m_pCurrentFrame   = NULL;
	//contextT.m_pNewDocTemplate = NULL;
	//contextT.m_pCurrentDoc     = NULL;
	//contextT.m_pNewViewClass   = RUNTIME_CLASS(CK2ReportView);


	//m_pTaskFrame = new CTaskFrame(this);	
	//DWORD dwStyle = WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE;	
	//m_pTaskFrame->LoadFrame(IDR_MAINFRAME, dwStyle, 0, &contextT);		
	//m_pTaskFrame->InitialUpdateFrame(NULL, FALSE);

	//m_pTaskFrame->ShowWindow(SW_SHOW);
	//CK2ReportView *pView = (CK2ReportView *)m_pTaskFrame->GetActiveView();





	//for(int i = 0; i < this->GetColumns()->GetCount(); i++)
	//{
	//	CXTPGridColumn *pOldCol = this->GetColumns()->GetAt(i);

	//	CXTPGridColumn *pCol = new CXTPGridColumn(i,pOldCol->GetCaption(),pOldCol->GetWidth(),pOldCol->IsAutoSize(),
	//		pOldCol->GetIconID(),pOldCol->IsSortable(),pOldCol->IsVisible());
	//	pView->GetDataCtrl().AddColumn(pCol);
	//	//pView->GetDataCtrl().AddColumn(new CXTPGridColumn(i,pOldCol->GetCaption(),pOldCol->GetWidth()));

	//}

	//pView->SendMessage(ID_FILE_PRINT, (WPARAM)pView->GetSafeHwnd());
	//pView->SendMessage(ID_FILE_PRINT_PREVIEW,(WPARAM)pView->GetSafeHwnd());
	//pView->SendMessage(ID_FILE_PRINT_SETUP,(WPARAM)pView->GetSafeHwnd());






}
void CDataBox::MyPrintPreview()
{			
	/*if (m_pTaskFrame)
	{
	m_pTaskFrame->ShowWindow(SW_SHOW);
	return;
	}*/
//	CCreateContext contextT;	
	// currently selected client if possible.
	//contextT.m_pLastView       = NULL;
	//contextT.m_pCurrentFrame   = NULL;
	//contextT.m_pNewDocTemplate = NULL;
	//contextT.m_pCurrentDoc     = NULL;	
	//contextT.m_pNewViewClass   = RUNTIME_CLASS(CViewPrintPreview);

	//m_pTaskFrame = new CTaskFrame(this);	
	//DWORD dwStyle = WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE;	
	//m_pTaskFrame->LoadFrame(IDR_MAINFRAME, dwStyle, 0, &contextT);		
	//m_pTaskFrame->InitialUpdateFrame(NULL, FALSE);
	//CViewPrintPreview *pView = (CViewPrintPreview *)m_pTaskFrame->GetActiveView();	
	//pView->m_pDataBox = this;

	//pView->OnFilePrintPreview(m_pTaskFrame);

	//m_pTaskFrame->ShowWindow(SW_SHOW);	


}


void CDataBox::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{

	ASSERT(m_aPageStart.GetSize() == 0);
	m_aPageStart.Add(0);
	ASSERT(m_aPageStart.GetSize() > 0);


}
void CDataBox::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{

	UINT nPage = pInfo->m_nCurPage;
	ASSERT(nPage <= (UINT)m_aPageStart.GetSize());
	UINT nIndex = m_aPageStart[nPage-1];

	// print as much as possible in the current page.
	nIndex = PrintPage(pDC, pInfo, pInfo->m_rectDraw, nIndex );

	// update pagination information for page just printed
	if (nPage == (UINT)m_aPageStart.GetSize())
	{
		if ((int)nIndex < GetRows()->GetCount())
			m_aPageStart.Add(nIndex);
	}
	else
	{
		ASSERT(nPage < (UINT)m_aPageStart.GetSize());
		m_aPageStart[nPage] = nIndex;
	}

}
void CDataBox::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	m_aPageStart.RemoveAll();
}

void CDataBox::Print(CDC* pDC, CPrintInfo* pInfo)
{


}




long CDataBox::PrintPage(CDC* pDC, CPrintInfo* pInfo, CRect rcPage, long nIndexStart)
{
	rcPage.DeflateRect(20, 20);

	pDC->Draw3dRect(rcPage, 0, 0);

	int nHeaderHeight = GetPaintManager()->GetHeaderHeight();

	CRect rcHeader(rcPage.left + 1, rcPage.top + 1, rcPage.right - 1, rcPage.top + 1 + nHeaderHeight);

	PrintHeader(pDC, rcHeader);

	CRect rcRows(rcHeader.left, rcHeader.bottom, rcHeader.right, rcPage.bottom - 1);
	nIndexStart = PrintRows(pDC, rcRows, nIndexStart);

	CRect rcFooter(rcPage.left, rcPage.bottom, rcPage.right, rcPage.bottom + 20);
	PrintFooter(pDC, pInfo, rcFooter);


	return nIndexStart;
}

void CDataBox::PrintHeader(CDC* pDC, CRect rcHeader)
{
	GetPaintManager()->FillHeaderControl(pDC, rcHeader);

	int x = rcHeader.left;

	CXTPGridColumns* pColumns = GetColumns();

	for (int i = 0; i < pColumns->GetCount(); i ++)
	{
		CXTPGridColumn* pColumn = pColumns->GetAt(i);
		if (!pColumn->IsVisible())
			continue;

		int nWidth = GetColumnWidth(pColumn, rcHeader.Width());
		CRect rcItem(x, rcHeader.top, x + nWidth, rcHeader.bottom);

		GetPaintManager()->DrawColumn(pDC, pColumn, GetReportHeader(), rcItem);

		x += nWidth;
	}
}


int CDataBox::GetColumnWidth(CXTPGridColumn* pColumnTest, int nTotalWidth)
{
	CXTPGridColumns* pColumns = GetColumns();

	int nColumnsWidth = 0;
	CXTPGridColumn* pLastAutoColumn = NULL;

	for (int nColumn = 0; nColumn < pColumns->GetCount(); nColumn ++)
	{
		CXTPGridColumn* pColumn = pColumns->GetAt(nColumn);
		if (!pColumn->IsVisible())
			continue;

		if (pColumn->IsAutoSize())
		{
			pLastAutoColumn = pColumn;
			nColumnsWidth += pColumn->GetWidth();
		}
		else
		{
			nTotalWidth -= pColumn->GetWidth();
		}
	}

	for (int i = 0; i < pColumns->GetCount(); i ++)
	{
		CXTPGridColumn* pColumn = pColumns->GetAt(i);
		if (!pColumn->IsVisible())
			continue;

		int nWidth = pColumn->GetWidth();

		if (pColumn->IsAutoSize())
		{
			if (pColumn == pLastAutoColumn)
			{
				nWidth = max(nTotalWidth, pColumn->GetMinWidth());
			}
			else
			{
				nColumnsWidth = max(1, nColumnsWidth);

				nWidth =
					max(int(pColumn->GetWidth() * nTotalWidth / nColumnsWidth), pColumn->GetMinWidth());

				nTotalWidth -= nWidth;
				nColumnsWidth -= pColumn->GetWidth();
			}
		}

		if (pColumn == pColumnTest)
			return nWidth;
	}

	return 0;
}


int CDataBox::PrintRows(CDC* pDC, CRect rcClient, long nIndexStart)
{
	int y = rcClient.top;
	CXTPGridRows* pRows = GetRows();

	for (; nIndexStart < pRows->GetCount(); nIndexStart++)
	{
		CXTPGridRow* pRow = pRows->GetAt(nIndexStart);

		int nHeight = pRow->GetHeight(pDC, 0);	//xtp업데이트 과정에서, 0이 추가되었다.(0은 프린트할경우에만 유효함)
		if (pRow->IsPreviewVisible())
		{
			CXTPGridRecordItemPreview* pItem = pRow->GetRecord()->GetItemPreview();
			nHeight+= pItem->GetPreviewHeight(pDC, pRow, rcClient.Width());
		}

		CRect rcRow(rcClient.left, y, rcClient.right, y + nHeight);

		if (rcRow.bottom > rcClient.bottom)
			break;

		PrintRow(pDC, pRow, rcRow);

		y += rcRow.Height();
	}
	return nIndexStart;

}

void CDataBox::PrintRow(CDC* pDC, CXTPGridRow* pRow, CRect rcRow)
{
	if (pRow->IsGroupRow())
	{
		GetPaintManager()->DrawGroupRow(pDC, (CXTPGridGroupRow*)pRow, rcRow, NULL); //xtp업데이트과정에서 NULL추가함
		return;
	}


	XTP_GRIDRECORDITEM_DRAWARGS drawArgs;
	drawArgs.pDC = pDC;
	drawArgs.pControl = this;
	drawArgs.pRow = pRow;
	int nIndentWidth = this->GetHeaderIndent();
	CXTPGridPaintManager* pPaintManager = GetPaintManager();

	CXTPGridColumns* pColumns = GetColumns();
	int nColumnCount = pColumns->GetCount();

	// paint row background
	pPaintManager->FillRow(pDC, pRow, rcRow);

	CRect rcItem(rcRow);
	rcItem.bottom = rcItem.top + pPaintManager->GetRowHeight(pDC, pRow);

	CXTPGridRecord* pRecord = pRow->GetRecord();
	if (pRecord) // if drawing record, not group
	{
		int x = rcRow.left;
		// paint record items
		for (int nColumn = 0; nColumn < nColumnCount; nColumn++)
		{
			CXTPGridColumn* pColumn = pColumns->GetAt(nColumn);
			if (pColumn && pColumn->IsVisible() && pRow->IsItemsVisible())
			{
				rcItem.left = x;
				x = rcItem.right = rcItem.left + GetColumnWidth(pColumn, rcRow.Width());
				if (nColumn == 0)
					rcItem.left += nIndentWidth;

				CRect rcGridItem(rcItem);
				rcGridItem.left--;

				CXTPGridRecordItem* pItem = pRecord->GetItem(pColumn);

				if (pItem)
				{

					// draw item
					drawArgs.pColumn = pColumn;
					drawArgs.rcItem = rcItem;
					drawArgs.nTextAlign = pColumn->GetAlignment();
					drawArgs.pItem = pItem;
					// draw item
					pItem->Draw(&drawArgs);
				}

				pPaintManager->DrawGrid(pDC, xtpGridOrientationHorizontal, rcGridItem);
			}
		}

		if (nIndentWidth > 0)
		{
			// draw indent column
			CRect rcIndent(rcRow);
			rcIndent.right = rcRow.left + nIndentWidth;
			pPaintManager->FillIndent(pDC, rcIndent);
		}

		if (pRow->IsPreviewVisible())
		{
			CXTPGridRecordItemPreview* pItem = pRecord->GetItemPreview();
			int nPreviewHeight = pItem->GetPreviewHeight(pDC, pRow, rcRow.Width());

			CRect rcPreviewItem(rcRow);
			rcPreviewItem.DeflateRect(nIndentWidth, rcPreviewItem.Height() - nPreviewHeight, 0, 0);

			drawArgs.rcItem = rcPreviewItem;
			drawArgs.nTextAlign = DT_LEFT;
			drawArgs.pItem = pItem;
			drawArgs.pColumn = NULL;

			drawArgs.pItem->Draw(&drawArgs);
		}
	}

	BOOL bGridVisible = pPaintManager->IsGridVisible(FALSE);

	CRect rcFocus(rcRow.left, rcRow.top, rcRow.right, rcRow.bottom - (bGridVisible? 1: 0));

	if (pRow->GetIndex() < GetRows()->GetCount() - 1 && nIndentWidth > 0)
	{
		CXTPGridRow* pNextRow = GetRows()->GetAt(pRow->GetIndex() + 1);
		ASSERT(pNextRow);
		rcFocus.left = rcRow.left +  min(nIndentWidth, pPaintManager->m_nTreeIndent * pNextRow->GetTreeDepth());
	}

	pPaintManager->DrawGrid(pDC, xtpGridOrientationHorizontal, rcFocus);
}

void CDataBox::PrintFooter(CDC* pDC, CPrintInfo* pInfo, CRect rcFooter)
{
	CFont* pOldFont = pDC->SelectObject(&GetPaintManager()->m_fontText);

	CString strPage;
	strPage.Format(_T("%i"), pInfo->m_nCurPage);
	pDC->SetTextColor(0);
	pDC->DrawText(strPage, rcFooter, DT_CENTER|DT_SINGLELINE|DT_NOPREFIX);

	pDC->SelectObject(pOldFont);
}




void CDataBox::CreateColumnSelect()
{
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();

	//////////////// 컬럼
	if (!m_wndFieldChooserCustomer.Create(pFrame, IDD_FIELDCHOOSER,
		CBRS_LEFT|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE, ID_TEST_FIELDCHOOSER_CUSTOMER))
		return;      // fail to create


	m_wndFieldChooserCustomer.EnableDocking(0);
	m_wndFieldChooserCustomer.SetWindowText(_T("컬럼 선택창"));
	pFrame->ShowControlBar(&m_wndFieldChooserCustomer, FALSE, FALSE);
	pFrame->FloatControlBar(&m_wndFieldChooserCustomer, CPoint(100, GetSystemMetrics(SM_CYSCREEN) / 3));
	if(m_wndSubList.GetSafeHwnd() == NULL)
		m_wndSubList.SubclassDlgItem(IDC_COLUMNLIST, &m_wndFieldChooserCustomer);

	m_bColumnSelectCreate = TRUE;




}
void CDataBox::FilterEditCreate()
{
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();

	if (!m_wndFilterEditDialogBar.Create(pFrame, IDD_FILTEREDIT,
		CBRS_LEFT|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE, ID_TEST_FILTERWINDOW))
		return ;      // fail to create
	m_wndFilterEditDialogBar.EnableDocking(CBRS_ALIGN_TOP);
	m_wndFilterEditDialogBar.SetWindowText(_T("Filter text"));

	pFrame->ShowControlBar(&m_wndFilterEditDialogBar, FALSE, FALSE);
	pFrame->FloatControlBar(&m_wndFilterEditDialogBar, CPoint(400, GetSystemMetrics(SM_CYSCREEN) / 3));	
	if (m_wndFilterEdit.GetSafeHwnd() == NULL)	
		m_wndFilterEdit.SubclassDlgItem(IDC_FILTEREDIT, &m_wndFilterEditDialogBar);

	m_bFilterEditCreate = TRUE;


}
void CDataBox::OnShowSearchWord()
{
	if(m_wndFilterEditDialogBar.GetSafeHwnd() == NULL)
		FilterEditCreate();

	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();	

	BOOL bShow = !this->m_wndFilterEditDialogBar.IsVisible();
	pMainFrm->ShowControlBar(&m_wndFilterEditDialogBar, bShow, FALSE);

}
void CDataBox::OnShowFieldChooser()
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();	
	BOOL bShow = !m_wndFieldChooserCustomer.IsVisible();
	pMainFrm->ShowControlBar(&m_wndFieldChooserCustomer, bShow, FALSE);
}

void CDataBox::CreateRsSetQuery(CString sQuery)
{
	m_pRs = new CMkRecordset(m_pMkDb);
	m_pCmd = new CMkCommand(m_pMkDb, sQuery);	

	/*CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "insert_chargetype_name_2008");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nPayTable);
	pCmd.AddParameter(typeString, typeInput, sChargeName.GetLength(), sChargeName);
	pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(!pRs.Execute(&pCmd)) return;
	pPar->GetValue(nReturnValue);*/


}

void CDataBox::AddHeader(int nCol,BOOL bView, CString sFieldName, CString sColumnName, int nColumnSize , int nAlign, BOOL bEdit, BOOL bSetItemData, BOOL bSetItemData2)
{
	m_HeadData[sFieldName].bView =bView;
	m_HeadData[sFieldName].sFieldName = sFieldName;
	m_HeadData[sFieldName].sColumnName = sColumnName;
	m_HeadData[sFieldName].nColumnSize = nColumnSize;
	m_HeadData[sFieldName].nAlign = nAlign;	
	m_HeadData[sFieldName].nCol = nCol;
	m_HeadData[sFieldName].bSetItemData = bSetItemData;
	m_HeadData[sFieldName].bSetItemData2 = bSetItemData2;
	if(bView && nCol >= 0)
		this->ColumnInit(nCol,sColumnName,nColumnSize,bEdit,nAlign);

}

CMkParameter * CDataBox::AddOutPutParameter(int iValue)
{
	CMkParameter *pPar =m_pCmd->AddParameter(typeInt,typeOutput,sizeof(int) ,iValue);
	return pPar;
}
CMkParameter * CDataBox::AddOutPutParameter(long lValue)
{
	CMkParameter *pPar =m_pCmd->AddParameter(typeLong,typeOutput,sizeof(long) ,lValue);

	return pPar;
}

void CDataBox::AddParameter(int iValue)
{	
	m_pCmd->AddParameter(iValue);
}
void CDataBox::AddParameter(long nValue)
{	
	m_pCmd->AddParameter(nValue);
}
void CDataBox::AddParameter(BOOL bValue, int nType)
{	
	m_pCmd->AddParameter(bValue);
}
void CDataBox::AddParameter(COleDateTime dtValue)
{	
	m_pCmd->AddParameter(dtValue);

}
void CDataBox::AddParameter(CString sValue)
{	
	m_pCmd->AddParameter(sValue);
}

CMkRecordset* CDataBox::Excute()
{

	if(!m_pRs->Execute(m_pCmd)) 
	{
		LF->MsgBox("실행중 에러가 발생되었습니다.");

		return NULL;
	}
	else
		return m_pRs;
}

void CDataBox::RecordSetCloseRelease(CMkRecordset *pRs)
{
	if(pRs)
	{
		if(pRs == m_pRs)
		{
			delete m_pRs;
			m_pRs = NULL;	
		}
		else
		{
			delete pRs;
			pRs = NULL;
		}		
	}
	if(m_pCmd)
	{
		delete m_pCmd;
		m_pCmd = NULL;
	}

}

void CDataBox::ExcuteBinding(BOOL bRefresh)
{
	CString sFieldName;
	int nType = 0, nCol=0;
	int niValue; long nlValue; BOOL bValue; COleDateTime dtValue; CString sValue; 
	if(!m_pRs->Execute(m_pCmd)) return;

	CMyXTPGridRecord *pRecord = NULL;
	for(int i = 0; i < m_pRs->GetRecordCount(); i++)
	{		
		for(int nCol = 0; nCol < m_pRs->GetFiledCount(); nCol++)
		{
			sFieldName = m_pRs->GetFieldName(nCol);			
			//qsLog.Print("%s ->fieldName\n", sFieldName);							
			nType = m_pRs->GetFieldType(nCol);
			if(m_HeadData[sFieldName].sFieldName.Compare(sFieldName) != 0)
				continue;
			switch(nType)
			{
			case 2:
				m_pRs->GetFieldValue(sFieldName,niValue);		
				/*if(m_HeadData[sFieldName].bChange)				
				{
				MyChangeValue(niValue);	
				continue;
				}
				else
				{*/
				//}
				if(m_HeadData[sFieldName].bView)
				{
					if(!m_bHeader)						
						pRecord = MyAddItem(nCol,niValue,m_HeadData[sFieldName].sColumnName,
						m_HeadData[sFieldName].nColumnSize, FALSE,	m_HeadData[sFieldName].nAlign );
					else
						pRecord = MyAddItem(niValue);

				}					

				if(m_HeadData[sFieldName].bSetItemData )
					InsertItemDataLong(niValue);
				else if(m_HeadData[sFieldName].bSetItemData2 )
					InsertItemDataLong2(niValue);	

				break;
			case 3:
				m_pRs->GetFieldValue(sFieldName,nlValue);
				if(m_HeadData[sFieldName].bView)
				{
					if(!m_bHeader)							
						pRecord= MyAddItem(nCol,nlValue,m_HeadData[sFieldName].sColumnName,
						m_HeadData[sFieldName].nColumnSize, FALSE,m_HeadData[sFieldName].nAlign );
					else
						pRecord= MyAddItem(nlValue);
				}

				if(m_HeadData[sFieldName].bSetItemData )
					InsertItemDataLong(nlValue);
				else if(m_HeadData[sFieldName].bSetItemData2)
					InsertItemDataLong2(nlValue);

				break;
			case 11:
				m_pRs->GetFieldValue(sFieldName,(int)bValue);	
				if(m_HeadData[sFieldName].bView)
				{
					if(!m_bHeader)							
						pRecord = MyAddItem(nCol,bValue ? TRUE : FALSE,m_HeadData[sFieldName].sColumnName,
						m_HeadData[sFieldName].nColumnSize, FALSE,m_HeadData[sFieldName].nAlign );
					else
						pRecord = MyAddItem(bValue ? TRUE : FALSE);
				}

				if(m_HeadData[sFieldName].bSetItemData)
					InsertItemDataLong((long)bValue);
				else if(m_HeadData[sFieldName].bSetItemData2 )
					InsertItemDataLong2((long)bValue);

				break;
			case 7:
				m_pRs->GetFieldValue(sFieldName,dtValue);
				if(m_HeadData[sFieldName].bView)
				{
					if(!m_bHeader)							
						pRecord = MyAddItem(nCol,dtValue,m_HeadData[sFieldName].sColumnName,
						m_HeadData[sFieldName].nColumnSize, FALSE,m_HeadData[sFieldName].nAlign );
					else
						pRecord = MyAddItem(dtValue);
				}

				if(m_HeadData[sFieldName].bSetItemData )
					this->InsertItemDataDate(dtValue);
				else if(m_HeadData[sFieldName].bSetItemData2 )
					InsertItemDataDate2(dtValue);


				break;
			case 202:
				m_pRs->GetFieldValue(sFieldName,sValue);
				if(m_HeadData[sFieldName].bView)
				{
					if(!m_bHeader)						
						pRecord = MyAddItem(nCol,sValue,m_HeadData[sFieldName].sColumnName,
						m_HeadData[sFieldName].nColumnSize, FALSE,m_HeadData[sFieldName].nAlign );
					else
						pRecord = MyAddItem(sValue);
				}

				if(m_HeadData[sFieldName].bSetItemData )
					this->InsertItemDataString(sValue);
				else if(m_HeadData[sFieldName].bSetItemData2 )
					InsertItemDataString2(sValue);

				break;
			case 203:
				m_pRs->GetFieldValue(sFieldName,sValue);
				if(m_HeadData[sFieldName].bView)
				{
					if(!m_bHeader)						
						pRecord = MyAddItem(nCol,sValue,m_HeadData[sFieldName].sColumnName,
						m_HeadData[sFieldName].nColumnSize, FALSE,m_HeadData[sFieldName].nAlign );
					else
						pRecord = MyAddItem(sValue);
				}

				if(m_HeadData[sFieldName].bSetItemData )
					InsertItemDataString(sValue);
				else if(m_HeadData[sFieldName].bSetItemData )
					InsertItemDataString2(sValue);
				break;
			}

			//qsLog.Print("%d col \n", nCol);
		}		
		this->EndItem();	
		m_pRs->MoveNext();

		//qsLog.Print("%d  row\n", i);
	}			
	m_pRs->Close();

	if(bRefresh)
		Populate();

	if(m_pRs)
	{
		delete m_pRs;
		m_pRs = NULL;
	}
	if(m_pCmd)
	{
		delete m_pCmd;
		m_pCmd = NULL;
	}

}

void CDataBox::CreateComandSetQuery(CString sql)
{
	m_pCmd = new CMkCommand(m_pMkDb, sql);	
}
BOOL CDataBox::ExcuteCmd(BOOL bRefresh)
{
	BOOL bSuccess = m_pCmd->Execute();

	if(!bSuccess)
		LF->MsgBox("작업중 오류가 났습니다. 다시시도 하시거나 로지소프트로 문의하세요");

	if(m_pCmd)
	{
		delete m_pCmd;
		m_pCmd = NULL;
	}
	return bSuccess;
}


BOOL CDataBox::IsRowSelectCheck(CString strMsg)
{

	if(GetSelectedCount() <= 0)
	{
		if(strMsg.GetLength() == 0)
		{
			MessageBox("리스트의 아이템을 한개라도 선택해주세요");
			return FALSE;
		}
		else
		{
			MessageBox(strMsg);
			return FALSE;

		}
	}
	return TRUE;

}



/*

void CDataBox::GetItemMetrics (XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
{
CXTPGridColumnOrder* pSortOrder = pDrawArgs->pControl->GetColumns()->GetSortOrder();
//CString strColumn = pDrawArgs->pColumn->GetCaption();
int nRow = pDrawArgs->pRow->GetIndex();
int nCount = pDrawArgs->pControl->GetRows()->GetCount();
int nCol = pDrawArgs->pColumn->GetIndex();
int nItemCol = pDrawArgs->pColumn->GetItemIndex();
//int nMNo = m_bUseFilter ? m_Index[m_filter[m_arrange[nRow]]] : m_Index[m_arrange[nRow]];

//pDrawArgs->nTextAlign = header_align2[nItemCol];

if(nCol > 2)
{
//pItemMetrics->strText = m_m
}


}
*/

void CDataBox::Filter2(CString strFilter, int nFilterCol, CString strFilter2, int nFilterCol2)
{
	if(nFilterCol < 0 )
		return;

	int nCol = nFilterCol - 1;
	int nCol2 = nFilterCol2 - 1;

	CXTPGridRecords *pRecords = GetRecords();		
	CXTPGridColumn* pColumn = NULL; CXTPGridColumn* pColumn2 = NULL;
	CXTPGridColumns *pCols = GetColumns();
	BOOL bDigit = FALSE;
	BOOL bNoFilter = FALSE;


	if(LF->IsStringDigit(strFilter) && strFilter.GetLength() < 4)	//3글자이하의 숫자인 경우에 전체단어일치
		bDigit = TRUE;

	if(strFilter == "")
		bNoFilter = TRUE;


	for(int i = 0; i < pRecords->GetCount(); i++)
	{
		BOOL bFound = FALSE;

		if(!bNoFilter)
		{
			if(nCol < 0)
			{
				for(int k = 0; k < pCols->GetCount(); k++)
				{
					if(m_bInsertSearchAll)
					{
						if(m_sac[k+1] != k+1)
							continue;
					}

					CXTPGridRecordItemText *pItem = (CXTPGridRecordItemText*)pRecords->GetAt(i)->GetItem(k);
					CString strItem = pItem->GetCaption(pColumn);


					if(bDigit)
					{
						if(strItem == strFilter)
						{
							bFound = TRUE;
							break;
						}
					}
					else
					{
						if(strItem.Find(strFilter) >= 0)
						{
							bFound = TRUE;
							break;
						}
					}
				} // for
			} // if(nCol < 0)
			else
			{
				CXTPGridRecordItemText *pItem = (CXTPGridRecordItemText*)pRecords->GetAt(i)->GetItem(nCol);
				CXTPGridRecordItemText *pItem2 = (CXTPGridRecordItemText*)pRecords->GetAt(i)->GetItem(nCol2);
				CString strItem = pItem->GetCaption(pColumn);
				CString strItem2 = pItem2->GetCaption(pColumn2);

				if(bDigit)
				{
					if(strItem == strFilter && strItem2 == strFilter2)
					{
						bFound = TRUE;
					}
				}
				else
				{
					if(strItem.Find(strFilter) >= 0 && strItem2.Find(strFilter2) >= 0  )
					{
						bFound = TRUE;
					}
				}
			}
		}
		else
		{
			bFound = TRUE;
		}

		if(bFound)
		{
			BOOL bFound2 = FALSE;


			pRecords->GetAt(i)->SetVisible(TRUE);
		}
		else
			pRecords->GetAt(i)->SetVisible(FALSE);

	}

	Populate();
}

void CDataBox::Filter(CString strFilter, int nFilterCol, int nTypeData, CString sReplaceData, BOOL bNotAllSearchWord)
{
	if(nFilterCol < 0 && nTypeData < 0)
		return;

	int nCol = nFilterCol - 1;
	CXTPGridRecords *pRecords = GetRecords();		
	CXTPGridColumn* pColumn = NULL;
	CXTPGridColumns *pCols = GetColumns();
	BOOL bDigit = FALSE;
	BOOL bNoFilter = FALSE;


	if(LF->IsStringDigit(strFilter) && strFilter.GetLength() < 4)	//3글자이하의 숫자인 경우에 전체단어일치
		bDigit = TRUE;

	if(strFilter == "")
		bNoFilter = TRUE;


	for(int i = 0; i < pRecords->GetCount(); i++)
	{
		BOOL bFound = FALSE;

		if(!bNoFilter)
		{
			if(nCol < 0)
			{
				for(int k = 0; k < pCols->GetCount(); k++)
				{
					if(m_bInsertSearchAll)
					{
						if(m_sac[k+1] != k+1)
							continue;
					}
					CString strItem = "";

					CXTPGridRecordItemText *pItem = (CXTPGridRecordItemText*)pRecords->GetAt(i)->GetItem(k);
					if(pItem)
						strItem = pItem->GetCaption(pColumn);

					

					if(sReplaceData.GetLength() > 0)
						strItem.Replace(sReplaceData, "");

					if(bDigit && bNotAllSearchWord)
					{
						if(strItem == strFilter)
						{
							bFound = TRUE;
							break;
						}
					}
					else
					{
						if(strItem.Find(strFilter) >= 0)
						{
							bFound = TRUE;
							break;
						}
					}
				} // for
			} // if(nCol < 0)
			else
			{
				CXTPGridRecordItemText *pItem = (CXTPGridRecordItemText*)pRecords->GetAt(i)->GetItem(nCol);
				CString strItem = pItem->GetCaption(pColumn);

				if(bDigit)
				{
					if(strItem == strFilter)
					{
						bFound = TRUE;
					}
				}
				else
				{
					if(strItem.Find(strFilter) >= 0)
					{
						bFound = TRUE;
					}
				}
			}
		}
		else
		{
			bFound = TRUE;
		}

		if(bFound)
		{
			BOOL bFound2 = FALSE;

			/*	if(m_bInsertTypeFilter)
			{
			if(nTypeData == ALL_TYPE_COL)
			{
			bFound2 = TRUE;
			}
			else if(m_bItemData)
			{
			if(m_dwTypeItemData[nTypeData] == ((CXTPListCtrlRecord*)pRecords->GetAt(i))->m_dwData)
			{
			bFound2 = TRUE;
			}
			}
			else 
			{
			CXTPGridRecordItemText *pItem = (CXTPGridRecordItemText*)pRecords->GetAt(i)->GetItem(m_nTypeTargetCol);
			CString strItem = pItem->GetCaption(pColumn);

			if(strItem.Find(m_szTypeString[nTypeData]) >= 0)
			{
			bFound2 = TRUE;
			}
			}

			if(bFound2)
			pRecords->GetAt(i)->SetVisible(TRUE);
			else
			pRecords->GetAt(i)->SetVisible(FALSE);
			}
			else
			{

			pRecords->GetAt(i)->SetVisible(TRUE);
			}
			}
			else
			{*/
			pRecords->GetAt(i)->SetVisible(TRUE);
		}
		else
			pRecords->GetAt(i)->SetVisible(FALSE);

	}

	Populate();
}

void CDataBox::InsertSearchAllColumn(int nCol)
{
	m_bInsertSearchAll = TRUE;
	m_sac.insert(SEARCH_ALL_COLUMN_DATA::value_type(nCol+1, nCol+1));
}

void CDataBox::DeleteAllColumns()
{
	int nColumnCount = GetColumns()->GetCount();
	for(int i=0;i < nColumnCount;i++)
	{
		CXTPGridColumn *pColumn = GetColumns()->GetAt(0);
		GetColumns()->Remove(pColumn);
	}
	m_bHeader = FALSE;
}

