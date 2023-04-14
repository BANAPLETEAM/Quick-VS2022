// XTPListCtrl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "XTPListCtrl2.h"
#include "MyReportPaintManager.h"

CFont* CXTPListCtrl2::m_pfntBold = NULL;

/*
#ifndef IDC_XTPLISTCTRL_COMBO
	#define IDC_XTPLISTCTRL_COMBO	15000
#endif

#ifndef IDC_XTPLISTCTRL_EDIT
	#define IDC_XTPLISTCTRL_EDIT	15001
#endif

#ifndef IDC_XTPLISTCTRL_TYPE_COMBO
	#define IDC_XTPLISTCTRL_TYPE_COMBO	15002
#endif
*/

SORT_TYPE_MAP CXTPListCtrl2::m_mapSortType;



// CXTPListCtrl

IMPLEMENT_DYNAMIC(CXTPListCtrl2, CXTPGridControl)

//column coloring
void CXTPListCtrlRecord2::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nCol = pDrawArgs->pColumn->GetItemIndex();
	int nRow = pDrawArgs->pRow->GetIndex();

	if(((CXTPListCtrl2*)pDrawArgs->pControl)->GetOrderIndexCol() == nCol)
	{
		//char buffer[10];
		//pDrawArgs->pRow->GetRecord()->GetItem(nCol)->SetCaption(ltoa(nRow+1, buffer, 10));
		pItemMetrics->strText.Format("%d", nRow + 1);
		pItemMetrics->clrForeground = RGB(80, 80, 80);
		pItemMetrics->clrBackground = RGB(255, 255, 255);
	}
}
CXTPListCtrl2::CXTPListCtrl2()
{
	bInit = FALSE;
	m_pFilterCombo = NULL;
	m_bInsertSearchAll = FALSE;
	m_pTypeCombo = NULL;
	m_pFilterEdit = NULL;
	m_bInsertTypeFilter = FALSE;
	m_nTypeTargetCol = -1;
	m_bItemData = FALSE;

	m_bSelect = FALSE;
	pSelectedRows = NULL;
	m_nOrderIndexCol = -1;

	m_nDayCount = 0;
	m_strFooterMessage = "";
	m_bDrawCount = TRUE;
	m_bPrintFooterMessage = FALSE;
}

CXTPListCtrl2::~CXTPListCtrl2()
{
}

void CXTPListCtrl2::ReSortRows()
{	
	CheckCurColumnSortType();
	SetRowsCompareFunc(CompareRows);
	CXTPGridControl::ReSortRows();
}


void CXTPListCtrl2::CheckCurColumnSortType()
{
	m_mapSortType.clear();

	int nSortCnt = GetColumns()->GetSortOrder()->GetCount();
	for(int nSortOrder = 0; nSortOrder < nSortCnt; nSortOrder++)
	{
		BOOL bIsStringSort = FALSE;
		CXTPGridColumn* pColumn = GetColumns()->GetSortOrder()->GetAt(nSortOrder);

		CXTPGridRecords *pRecords = GetRecords();
		
		int nCount = pRecords->GetCount();
		for(int i = 0; i < nCount; i++)
		{
			CXTPGridRecord *pRecord = pRecords->GetAt(i);

			if(((CXTPListCtrlRecord2*)pRecord)->m_bNoSort)
				continue;

			CXTPGridRecordItem* pItem = pRecord->GetItem(pColumn);
			CString strCaption = pItem->GetCaption(pColumn);
			if(!IsStringDigitWithComma(strCaption))
			{
				m_mapSortType[nSortOrder] = MY_SORT_STRING;
				bIsStringSort = TRUE;
				break;
			}
		}

		if(GetRecords()->GetCount() > 1 && !bIsStringSort)
			m_mapSortType[nSortOrder] = MY_SORT_NUM;
		else
			m_mapSortType[nSortOrder] = MY_SORT_STRING;
	}
}

BEGIN_MESSAGE_MAP(CXTPListCtrl2, CXTPGridControl)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CXTPListCtrl 메시지 처리기입니다.

void CXTPListCtrl2::AddFooterRows()
{
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)GetFooterRecords()->Add(new CXTPListCtrlRecord2("", 0, 0, 0, 0));
	FooterRowsEnableSelection(FALSE);
	ShowFooterRows(TRUE);
	PinFooterRows(FALSE);
	GetPaintManager()->SetFooterRowsDividerStyle(xtpGridFixedRowsDividerOutlook);
	GetPaintManager()->m_clrFooterRowsDivider = RGB(0,0,255);
	//SetGridColor(RGB(255, 255, 255));

	m_bPrintFooterMessage = TRUE;
}



void CXTPListCtrl2::InitControl()	//한번만 실행한다.
{
	if(m_pfntBold == NULL)
		m_pfntBold = m_FontManager.GetFont("돋움", 12, FW_BOLD);

	if(!bInit)
	{
		ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);
		GetReportHeader()->AllowColumnResize(TRUE);
		GetReportHeader()->SetAutoColumnSizing(FALSE);
		GetReportHeader()->AllowColumnSort(TRUE);
		GetReportHeader()->AllowColumnRemove(FALSE);
		SetPaintManager(new CMyReportPaintManager());
		GetPaintManager()->m_strNoItems = "표시할 정보가 없거나, 조건에 해당하는 자료가 존재하지 않음";
		GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
		SetGridStyle(TRUE, xtpGridSolid);
		SetGridColor(RGB(212, 208, 200));
		AllowEdit(FALSE);

/*
		CWnd *pWnd = GetOwner();
		m_pFilterCombo = (CComboBox*)pWnd->GetDlgItem(IDC_XTPLISTCTRL_COMBO);
		m_pFilterEdit = (CEdit*)pWnd->GetDlgItem(IDC_XTPLISTCTRL_EDIT);
		if(m_pFilterCombo->GetSafeHwnd())
		{
			int nItem = m_pFilterCombo->AddString("전체검색");
			m_pFilterCombo->SetItemData(nItem, 999);
			m_pFilterCombo->SetCurSel(0);
		}

		m_pTypeCombo = (CComboBox*)pWnd->GetDlgItem(IDC_XTPLISTCTRL_TYPE_COMBO);
*/
	}

	bInit = TRUE;
}

void CXTPListCtrl2::SetExternalControl(CWnd *pFilterCombo, CWnd *pFilterEdit, CWnd *pTypeCombo)
{
	m_pFilterCombo = (CComboBox*)pFilterCombo;
	m_pFilterEdit = (CEdit*)pFilterEdit;
	m_pTypeCombo = (CComboBox*)pTypeCombo;

	if(m_pFilterCombo)
	{
		int nItem = m_pFilterCombo->AddString("전체검색");
		m_pFilterCombo->SetItemData(nItem, 999);
		m_pFilterCombo->SetCurSel(0);
	}
}


int CXTPListCtrl2::InsertColumn(int nCol, CString strColumnHeading, int nAlignment, int nWidth)
{
	InitControl();

	//LVCFMT_RIGHT -> DT_RIGHT, LVCFMT_CENTER -> DT_CENTER
	if(nAlignment == 0x02) 
		nAlignment = 0x01;
	else if(nAlignment == 0x01)
		nAlignment = 0x02;


	CXTPGridColumn *p1 = AddColumn(new CXTPGridColumn(nCol, strColumnHeading, nWidth, TRUE));
	p1->SetAlignment(nAlignment);
	if(m_pFilterCombo)
	{
		int nItem = m_pFilterCombo->AddString(strColumnHeading);
		m_pFilterCombo->SetItemData(nItem, nCol);
	}

	return 0;
}

CXTPGridColumn * CXTPListCtrl2::InsertColumnReturn(int nCol, CString strColumnHeading, int nAlignment, int nWidth)
{
	InitControl();

	//LVCFMT_RIGHT -> DT_RIGHT, LVCFMT_CENTER -> DT_CENTER
	if(nAlignment == 0x02) 
		nAlignment = 0x01;
	else if(nAlignment == 0x01)
		nAlignment = 0x02;


	CXTPGridColumn *p1 = AddColumn(new CXTPGridColumn(nCol, strColumnHeading, nWidth, TRUE));
	p1->SetAlignment(nAlignment);
	if(m_pFilterCombo)
	{
		int nItem = m_pFilterCombo->AddString(strColumnHeading);
		m_pFilterCombo->SetItemData(nItem, nCol);
	}

	return p1;
}

CXTPGridColumn* CXTPListCtrl2::InsertColumn1(int nCol, CString strColumnHeading, int nAlignment, int nWidth)
{
	InitControl();

	//LVCFMT_RIGHT -> DT_RIGHT, LVCFMT_CENTER -> DT_CENTER
	if(nAlignment == 0x02) 
		nAlignment = 0x01;
	else if(nAlignment == 0x01)
		nAlignment = 0x02;


	CXTPGridColumn *p1 = AddColumn(new CXTPGridColumn(nCol, strColumnHeading, nWidth, TRUE));
	p1->SetAlignment(nAlignment);
	if(m_pFilterCombo)
	{
		int nItem = m_pFilterCombo->AddString(strColumnHeading);
		m_pFilterCombo->SetItemData(nItem, nCol);
	}

	return p1;
}
 
void CXTPListCtrl2::SetImageList(CImageList *pImageList, int nType)
{
	ASSERT(pImageList != NULL);

	InitControl();
	CXTPGridControl::SetImageList(pImageList);
}


void CXTPListCtrl2::SetExtendedStyle(int nStyle)
{
	InitControl();
	//CListCtrl의 ExtendedStyle속성을 반영하지는 않고, 그냥 바디만 있는 것임	
}

CXTPGridRecord* CXTPListCtrl2::InsertItemReturn(int nItem, CString strItem, int nImage, int nColNum1, int nColNum2, BOOL bCheckBox)
{
	CXTPGridColumns *pColumns = GetColumns();
	if(pColumns == NULL) return NULL;

	long nTotalCol = GetColumns()->GetCount();
	CXTPListCtrlLogiRecord *pRecord = (CXTPListCtrlLogiRecord*)AddRecord(new CXTPListCtrlLogiRecord(strItem, nTotalCol, nImage, nColNum1, nColNum2, bCheckBox));

	return pRecord;
}

CXTPGridRecord* CXTPListCtrl2::InsertItem(int nItem, CString strItem, int nImage, int nColNum1, int nColNum2)
{
	long nTotalCol = GetColumns()->GetCount();
	return (CXTPListCtrlRecord2*)AddRecord(new CXTPListCtrlRecord2(strItem, nTotalCol, nImage, nColNum1, nColNum2));
}

void CXTPListCtrl2::InsertCheckItem(int nItem, CString strItem, int nImage, BOOL bChecked)
{
	long nTotalCol = GetColumns()->GetCount();
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)AddRecord(new CXTPListCtrlRecord2(strItem, nTotalCol, nImage, bChecked));
}

void CXTPListCtrl2::SetItemTextMyNumberFormat(int nItem, int nSubItem, long nValue, int nImage)
{
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nItem);
    ((CXTPGridRecordItemNumber*)(pRecord->GetItem(nSubItem)))->SetValue(nValue);
	((CXTPGridRecordItemText*)(pRecord->GetItem(nSubItem)))->SetCaption(::GetMyNumberFormat(nValue));

	if(nImage >= 0)
	{
		((CXTPGridRecordItemText*)(pRecord->GetItem(nSubItem)))->SetIconIndex(nImage);
	}
}

void CXTPListCtrl2::SetItemTextMyNumberFormat(CXTPGridRecord *pRecord, int nSubItem, long nValue, int nImage)
{
	((CXTPGridRecordItemNumber*)(pRecord->GetItem(nSubItem)))->SetValue(nValue);
	((CXTPGridRecordItemText*)(pRecord->GetItem(nSubItem)))->SetCaption(::GetMyNumberFormat(nValue));

	if(nImage >= 0)
	{
		((CXTPGridRecordItemText*)(pRecord->GetItem(nSubItem)))->SetIconIndex(nImage);
	}
}


void CXTPListCtrl2::SetItemTextLong(CXTPGridRecord *pRecord, int nSubItem, long nValue, int nImage)
{
	char buffer[20];

	((CXTPGridRecordItemNumber*)(pRecord->GetItem(nSubItem)))->SetValue(nValue);
	((CXTPGridRecordItemText*)(pRecord->GetItem(nSubItem)))->SetCaption(itoa(nValue, buffer, 10));

	if(nImage >= 0)
	{
		((CXTPGridRecordItemText*)(pRecord->GetItem(nSubItem)))->SetIconIndex(nImage);
	}

}

void CXTPListCtrl2::SetItemTextLong(int nItem, int nSubItem, long nValue, int nImage)
{
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nItem);

	char buffer[20];

	((CXTPGridRecordItemNumber*)(pRecord->GetItem(nSubItem)))->SetValue(nValue);
	((CXTPGridRecordItemText*)(pRecord->GetItem(nSubItem)))->SetCaption(itoa(nValue, buffer, 10));

	if(nImage >= 0)
	{
		((CXTPGridRecordItemText*)(pRecord->GetItem(nSubItem)))->SetIconIndex(nImage);
	}
}


void CXTPListCtrl2::SetItemText(CXTPGridRecord *pRecord, int nSubItem, CString strItem, int nImage)
{
	((CXTPGridRecordItemText*)(((CXTPListCtrlRecord2*)pRecord)->GetItem(nSubItem)))->SetCaption(strItem);
	if(nImage >= 0)
	{
		((CXTPGridRecordItemText*)(pRecord->GetItem(nSubItem)))->SetIconIndex(nImage);
	}
}

void CXTPListCtrl2::SetItemText(int nItem, int nSubItem, CString strItem, int nImage)
{
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nItem);
	((CXTPGridRecordItemText*)(pRecord->GetItem(nSubItem)))->SetCaption(strItem);
	((CXTPGridRecordItemText*)(pRecord->GetItem(nSubItem)))->SetValue(strItem);
	if(nImage >= 0)
	{
		((CXTPGridRecordItemText*)(pRecord->GetItem(nSubItem)))->SetIconIndex(nImage);
	}
}


void CXTPListCtrl2::SetItemText(int nItem, int nSubItem, long nNumber, int nImage)
{
	
//	SetItemText(nItem, nSubItem, ltoa(nNumber, buffer, 10), nImage);
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nItem);
	((CXTPGridRecordItemNumber*)(pRecord->GetItem(nSubItem)))->SetValue(nNumber);
	if(nImage >= 0)
	{
		((CXTPGridRecordItemText*)(pRecord->GetItem(nSubItem)))->SetIconIndex(nImage);
	}
}

void CXTPListCtrl2::SetItemTextHyperLink(int nItem, int nSubItem, CString strItem, int nImage)
{
	CXTPGridRecords* pReocrds = GetRecords();

	if(pReocrds == NULL)
		return;

	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nItem);

	if(pRecord)
	{

		((CXTPGridRecordItemText*)(pRecord->GetItem(nSubItem)))->SetValue(strItem);
		CXTPGridRecordItem *pItem = pRecord->GetItem(nSubItem);
		if(pItem)
		{
			pItem->AddHyperlink(new CXTPGridHyperlink(0, 0xFFFF));
		}

		if(nImage >= 0)
		{
			((CXTPGridRecordItemText*)(pRecord->GetItem(nSubItem)))->SetIconIndex(nImage);
		}
	}
}

void CXTPListCtrl2::SetItemData(int nItem, DWORD dwData)
{
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nItem);
	pRecord->m_dwData = dwData;
}

void CXTPListCtrl2::SetItemData(CXTPGridRecord *pRecord, DWORD dwData)
{
	((CXTPListCtrlRecord2*)pRecord)->m_dwData = dwData;
}

void CXTPListCtrl2::SetItemLong(int nItem, long nData)
{
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nItem);
	pRecord->m_nLong = nData;
}

void CXTPListCtrl2::SetItemLong(CXTPGridRecord *pRecord, long nData)
{
	((CXTPListCtrlRecord2*)pRecord)->m_nLong = nData;
}

void CXTPListCtrl2::SetItemLong2(int nItem, long nData)
{
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nItem);
	pRecord->m_nLong2 = nData;
}

void CXTPListCtrl2::SetItemLong2(CXTPGridRecord *pRecord, long nData)
{
	((CXTPListCtrlRecord2*)pRecord)->m_nLong2 = nData;
}

void CXTPListCtrl2::SetItemLong3(int nItem, long nData)
{
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nItem);
	pRecord->m_nLong3 = nData;
}

void CXTPListCtrl2::SetItemLong3(CXTPGridRecord *pRecord, long nData)
{
	((CXTPListCtrlRecord2*)pRecord)->m_nLong3 = nData;
}

void CXTPListCtrl2::SetItemDate(CXTPGridRecord *pRecord, COleDateTime dtDate)
{
	((CXTPListCtrlRecord2*)pRecord)->m_dtDate = dtDate;
}

void CXTPListCtrl2::SetItemDate(int nItem, COleDateTime dtDate)
{
	CXTPGridRecords *pRecords = GetRecords();
	if(pRecords == NULL) return;
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nItem);
	pRecord->m_dtDate = dtDate;
}

void CXTPListCtrl2::SetItemDataText(int nItem, CString sData)
{
	CXTPGridRecords *pRecords = GetRecords();
	if(pRecords == NULL) return;
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nItem);
	pRecord->m_strText = sData;
}

void CXTPListCtrl2::SetItemDataText2(int nItem, CString sData)
{
	CXTPGridRecords *pRecords = GetRecords();
	if(pRecords == NULL) return;
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nItem);
	pRecord->m_strText2 = sData;
}


void CXTPListCtrl2::SetItemDataText3(int nItem, CString sData)
{
	CXTPGridRecords *pRecords = GetRecords();
	if(pRecords == NULL) return;
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nItem);
	pRecord->m_strText3 = sData;
}

void CXTPListCtrl2::SetItemDataText(CXTPGridRecord *pRecord, CString sData)
{	
	((CXTPListCtrlRecord2*)pRecord)->m_strText = sData;
}

void CXTPListCtrl2::SetItemDataText2(CXTPGridRecord *pRecord, CString sData)
{	
	((CXTPListCtrlRecord2*)pRecord)->m_strText2 = sData;
}

void CXTPListCtrl2::SetItemDataText3(CXTPGridRecord *pRecord, CString sData)
{	
	((CXTPListCtrlRecord2*)pRecord)->m_strText3 = sData;
}

COleDateTime CXTPListCtrl2::GetItemDate(int nItem)
{
	CXTPGridRows *pRows = GetRows();
	CXTPGridRow *pRow = pRows->GetAt(nItem);
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)pRow->GetRecord();
	return pRecord->m_dtDate;
}

COleDateTime CXTPListCtrl2::GetItemDate(CXTPGridRecord *pRecord)
{
	return ((CXTPListCtrlRecord2*)pRecord)->m_dtDate;
}

CXTPGridRecord* CXTPListCtrl2::GetItemRecord(int nItem)
{
	CXTPGridRows *pRows = GetRows();
	CXTPGridRow *pRow = pRows->GetAt(nItem);
	return (CXTPListCtrlRecord2*)pRow->GetRecord();
}


DWORD CXTPListCtrl2::GetItemData(int nItem)
{
	CXTPGridRows *pRows = GetRows();
	CXTPGridRow *pRow = pRows->GetAt(nItem);
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)pRow->GetRecord();
	return pRecord->m_dwData;
}


DWORD CXTPListCtrl2::GetItemData(CXTPGridRecord *pRecord)
{
	return ((CXTPListCtrlRecord2*)pRecord)->m_dwData;
}

long CXTPListCtrl2::GetItemLong(int nItem)
{
	CXTPGridRows *pRows = GetRows();
	CXTPGridRow *pRow = pRows->GetAt(nItem);
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)pRow->GetRecord();
	return pRecord->m_nLong;
}

long CXTPListCtrl2::GetItemLong(CXTPGridRecord *pRecord)
{
	return ((CXTPListCtrlRecord2*)pRecord)->m_nLong;
}

long CXTPListCtrl2::GetItemLong2(int nItem)
{
	CXTPGridRows *pRows = GetRows();
	CXTPGridRow *pRow = pRows->GetAt(nItem);
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)pRow->GetRecord();
	return pRecord->m_nLong2;
}

long CXTPListCtrl2::GetItemLong2(CXTPGridRecord *pRecord)
{
	return ((CXTPListCtrlRecord2*)pRecord)->m_nLong2;
}

long CXTPListCtrl2::GetItemLong3(int nItem)
{
	CXTPGridRows *pRows = GetRows();
	CXTPGridRow *pRow = pRows->GetAt(nItem);
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)pRow->GetRecord();
	return pRecord->m_nLong3;
}

long CXTPListCtrl2::GetItemLong3(CXTPGridRecord *pRecord)
{
	return ((CXTPListCtrlRecord2*)pRecord)->m_nLong3;
}

CString CXTPListCtrl2::GetItemDataText(CXTPGridRecord *pRecord)
{
	return ((CXTPListCtrlRecord2*)pRecord)->m_strText;
}

CString CXTPListCtrl2::GetItemDataText2(CXTPGridRecord *pRecord)
{
	return ((CXTPListCtrlRecord2*)pRecord)->m_strText2;
}

CString CXTPListCtrl2::GetItemDataText3(CXTPGridRecord *pRecord)
{
	return ((CXTPListCtrlRecord2*)pRecord)->m_strText3;
}

CString CXTPListCtrl2::GetItemDataText(int nItem)
{
	CXTPGridRows *pRows = GetRows();
	CXTPGridRow *pRow = pRows->GetAt(nItem);
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)pRow->GetRecord();
	return pRecord->m_strText;
}

CString CXTPListCtrl2::GetItemDataText2(int nItem)
{
	CXTPGridRows *pRows = GetRows();
	CXTPGridRow *pRow = pRows->GetAt(nItem);
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)pRow->GetRecord();
	return pRecord->m_strText2;
}

CString CXTPListCtrl2::GetItemDataText3(int nItem)
{
	CXTPGridRows *pRows = GetRows();
	CXTPGridRow *pRow = pRows->GetAt(nItem);
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)pRow->GetRecord();
	return pRecord->m_strText3;
}

int CXTPListCtrl2::GetItemCount()
{
	return GetRecords()->GetCount();
}

BOOL CXTPListCtrl2::GetChecked(int nRow, int nCol)
{
	CXTPGridRows *pRows = GetRows();
	CXTPGridRow *pRow = pRows->GetAt(nRow);
	
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)pRow->GetRecord();

	return pRecord->GetChecked(nCol);
}

BOOL CXTPListCtrl2::GetChecked(CXTPGridRecord *pRecord, int nCol)
{
	return ((CXTPListCtrlRecord2*)pRecord)->GetChecked(nCol);
}

void CXTPListCtrl2::SetChecked(int nRow, int nCol, BOOL bCheck)
{
	CXTPGridRows *pRows = GetRows();
	CXTPGridRow *pRow = pRows->GetAt(nRow);

	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)pRow->GetRecord();

	(pRecord->GetItem(nCol))->SetChecked(bCheck);
}

void CXTPListCtrl2::SetChecked(CXTPGridRecord *pRecord, int nCol, BOOL bCheck)
{
	(((CXTPListCtrlRecord2*)pRecord)->GetItem(nCol))->SetChecked(bCheck);
}


void CXTPListCtrl2::EnsureVisibleEx(int nItem)
{
	CXTPGridRows *pRows = GetRows();
	if(pRows)
	{
		CXTPGridRow *pRow = pRows->GetAt(nItem);
		if(pRow)
		{
			CXTPGridRow *pRow2 = pRows->GetAt(min(pRow->GetIndex() + 10, pRows->GetCount() - 1));

			if(pRow2)
				EnsureVisible(pRow2);

			GetSelectedRows()->Select(pRow);	
		}
	}
}
void CXTPListCtrl2::SetSelectedRow(long nRow)
{
	CXTPGridRows *pRows = GetRows();
	CXTPGridRow *pRow = pRows->GetAt(nRow);

	GetSelectedRows()->Select(pRow);
}


CString CXTPListCtrl2::GetItemText(int nItem, int nSubItem)
{
	CXTPGridRows *pRows = GetRows();
	CXTPGridRow *pRow = pRows->GetAt(nItem);
	CXTPGridColumn* pColumn = NULL;
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)pRow->GetRecord();
	return ((CXTPGridRecordItemText*)(pRecord->GetItem(nSubItem)))->GetCaption(pColumn);
}

CString CXTPListCtrl2::GetItemText(CXTPGridRecord *pRecord, int nSubItem)	
{
	CXTPGridColumn* pColumn = NULL;
	CXTPListCtrlRecord2 *pRecord2 = (CXTPListCtrlRecord2*)pRecord;
	return ((CXTPGridRecordItemText*)(pRecord2->GetItem(nSubItem)))->GetCaption(pColumn);
}


int CXTPListCtrl2::GetNextItem(int nIndex, int nType)
{
	CXTPGridSelectedRows *pRows = GetSelectedRows();
	if(pRows == NULL)
		return -1;
	//if(GetSelectedRows()->GetCount() == 0)
	//	return -1;

	POSITION pos = GetSelectedRows()->GetFirstSelectedRowPosition();

	while(pos != NULL)
	{
		int nCur = GetSelectedRows()->GetNextSelectedRow(pos)->GetIndex();
		if(nCur >= nIndex)
			return nCur;
	}

	return -1;
}

void CXTPListCtrl2::HideRow(CXTPGridRow *pRow)
{
	pRow->GetRecord()->SetVisible(FALSE);
}

void CXTPListCtrl2::HideRow(int nItem)
{
	HideRow(GetRows()->GetAt(nItem));
}

void CXTPListCtrl2::ShowAllRow()
{
	CXTPGridRecords *pRecords = GetRecords();		

	for(int i = 0; i < pRecords->GetCount(); i++)
	{
		pRecords->GetAt(i)->SetVisible(TRUE);
	}

	Populate();
}

void CXTPListCtrl2::Filter(CString strFilter, int nFilterCol, int nTypeData)
{
	if(nFilterCol < 0 && nTypeData < 0)
		return;

	int nCol = nFilterCol - 1;
	CXTPGridRecords *pRecords = GetRecords();		
	CXTPGridColumn* pColumn = NULL;
	CXTPGridColumns *pCols = GetColumns();
	BOOL bDigit = FALSE;
	BOOL bNoFilter = FALSE; 

	if(IsStringDigit(strFilter) && strFilter.GetLength() < 4)
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
				}
			}
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

			if(m_bInsertTypeFilter)
			{
				if(nTypeData == ALL_TYPE_COL)
				{
					bFound2 = TRUE;
				}
				else if(m_bItemData)
				{
					if(m_dwTypeItemData[nTypeData] == ((CXTPListCtrlRecord2*)pRecords->GetAt(i))->m_dwData)
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
		{
			pRecords->GetAt(i)->SetVisible(FALSE);
		}
	}

	Populate();
}


void CXTPListCtrl2::InsertSearchAllColumn(int nCol)
{
	m_bInsertSearchAll = TRUE;
	m_sac.insert(SEARCH_ALL_COLUMN::value_type(nCol+1, nCol+1));
}


void CXTPListCtrl2::DeleteAllItems()
{
	GetRecords()->RemoveAll();

//	if(m_pFilterEdit->GetSafeHwnd())
//		m_pFilterEdit->SetWindowText("");
}

BOOL CXTPListCtrl2::IsStringDigit(CString &strText)
{
	for(int i = 0; i < strText.GetLength() ; i++) 
		if(!isdigit((::byte)strText.GetAt(i))) 
			return FALSE;
	return TRUE;

}


int CXTPListCtrl2::GetSelectedItem()
{
	POSITION pos = GetSelectedRows()->GetFirstSelectedRowPosition();

	if(pos)
		return GetSelectedRows()->GetNextSelectedRow(pos)->GetIndex();
	else
		return -1;
}

CXTPGridRecord* CXTPListCtrl2::GetFirstSelectedRecord()
{
	CXTPGridSelectedRows *pRows = GetSelectedRows();

	if(pRows == NULL) return NULL;
	if(pRows->GetCount() == 0) return NULL;

	return pRows->GetAt(0)->GetRecord();
}


void CXTPListCtrl2::ToExcel(CString strTitle)
{
	CoInitialize(NULL);

	long rows = GetRows()->GetCount() + 1;
	long cols = GetColumns()->GetVisibleColumnsCount();

	COleSafeArray sa;
	unsigned long elements[] = {rows, cols};
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

void CXTPListCtrl2::InsertTypeList(CString strTitle, int nTypeTargetCol, CString strKeyword, long dwItemData)
{
	if(m_pTypeCombo)
	{
		m_bInsertTypeFilter = TRUE;

		int nItem = 0;

		if(m_pTypeCombo->GetCount() == 0)
		{
			nItem = m_pTypeCombo->AddString("전체");
			m_pTypeCombo->SetItemData(nItem, ALL_TYPE_COL);
			m_nTypeTargetCol = ALL_TYPE_COL;
		}


		if(dwItemData >= 0)
		{
			nItem = m_pTypeCombo->AddString(strTitle);
			m_pTypeCombo->SetItemData(nItem, nItem);
			m_dwTypeItemData[nItem] = dwItemData;
			m_nTypeTargetCol = nItem;
			m_bItemData = TRUE;
		}
		else 
		{
			nItem = m_pTypeCombo->AddString(strTitle);
			m_pTypeCombo->SetItemData(nItem, nItem);
			strcpy(m_szTypeString[nItem], (LPSTR)(LPCTSTR)strKeyword);
			m_nTypeTargetCol = nTypeTargetCol;

			//g_bana_log->Print("%d %s]%s %s %d\n", nItem, m_szTypeString[nItem], strTitle, strKeyword, dwItemData);
		}

		m_pTypeCombo->SetCurSel(0);
	}
}



void CXTPListCtrl2::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CPoint pt = point;
	ScreenToClient(&pt);
	GetParent()->PostMessage(WM_CONTEXTMENU, NULL, MAKELPARAM(point.x, point.y));
}


int CXTPListCtrl2::GetVisibleItemCount()
{
	return GetRows()->GetCount();
}

void CXTPListCtrl2::OnDraw(CDC *pDC)
{
	CXTPGridControl::OnDraw(pDC);

	if(m_bDrawCount == FALSE)
		return;

	CRect rcFoot = GetFooterRowsRect(); 

	if(m_bPrintFooterMessage)
	{
		pDC->FillSolidRect(rcFoot, RGB(255, 255, 255));
	} 

	CRect rc, rcSame;
	GetClientRect(rc);
	rcSame = rc;
	rc.left = rc.right - 50;
	rc.top = rc.bottom - 12;

	rcSame.top = rc.top;

	CFont* pOldFont = NULL;
 
	if(m_bPrintFooterMessage) 
	{ 
		rcFoot.left += 20;  
		pOldFont = pDC->SelectObject(m_FontManager.GetFont("맑은 고딕", 17));

		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->DrawText(m_strFooterMessage, rcFoot, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	}

	if(pOldFont) pDC->SelectObject(pOldFont);
}

void CXTPListCtrl2::SaveReportOrder(CString sClass, CString sReport)
{
	CString sNewOrder = "";
	CString sNewOrderWidth = "";
	CString sNewOrderVisible = "";
	char buffer[20];


	for(int i=0; i<GetColumns()->GetCount(); i++)
	{
		long nIndex  = GetColumns()->GetAt(i)->GetItemIndex();
		sNewOrder += CString(itoa(nIndex, buffer, 10)) + ";";

		long nWidth = GetColumns()->GetAt(i)->GetWidth();
		sNewOrderWidth += CString(itoa(nWidth, buffer, 10)) + ";";

		BOOL bVisible = GetColumns()->GetAt(i)->IsVisible();
		sNewOrderVisible += CString(itoa(bVisible, buffer, 10)) + ";";
	}

	AfxGetApp()->WriteProfileString(sClass, sReport, sNewOrder);
	AfxGetApp()->WriteProfileString(sClass, sReport + "A", sNewOrderWidth);
	AfxGetApp()->WriteProfileString(sClass, sReport + "B", sNewOrderVisible);
} 

void CXTPListCtrl2::LoadReportOrder(CString sClass, CString sReport)
{
	CString sNewOrder = AfxGetApp()->GetProfileString(sClass, sReport, "");
	CString sNewOrderWidth = AfxGetApp()->GetProfileString(sClass, sReport + "A", "");
	CString sNewOrderVisible = AfxGetApp()->GetProfileString(sClass, sReport + "B", "");

	if(sNewOrder == "") return;
	if(sNewOrderWidth == "") return;
	if(sNewOrderVisible == "") return;

	if(::GetCommaCount(sNewOrder) == 0) return;

	long a = GetColumns()->GetCount();
	long b = ::GetCommaCount(sNewOrder);

	if(::GetCommaCount(sNewOrder) != (GetColumns()->GetCount())) return;


	long nFirstFind = 0;
	long nFirstFindWidth = 0;
	long nFirstFindVisible = 0;

	typedef map<long, long> COLMAP;
	COLMAP pMap;
	COLMAP pMapWidth;
	COLMAP pMapVisible;

	for(int i=0; i<GetColumns()->GetCount(); i++)
	{ 
		long nSecondFind = sNewOrder.Find(";", nFirstFind);
		long nSecondFindWidth = sNewOrderWidth.Find(";", nFirstFindWidth);
		long nSecondFindVisible = sNewOrderVisible.Find(";", nFirstFindVisible);

		long nNew = _ttoi(sNewOrder.Mid(nFirstFind, nSecondFind - nFirstFind));
		long nNewWidth = _ttoi(sNewOrderWidth.Mid(nFirstFindWidth, nSecondFindWidth - nFirstFindWidth));
		long nNewVisible = _ttoi(sNewOrderVisible.Mid(nFirstFindVisible, nSecondFindVisible - nFirstFindVisible));

		long nIndex = GetColumns()->GetAt(i)->GetItemIndex();
		CString sIndex = GetColumns()->GetAt(i)->GetCaption();

		pMap[i] = nNew;
		pMapWidth[i] = nNewWidth;
		pMapVisible[i] = nNewVisible;
		//pMap[nNew] = i;
		//pMap[i] = nNew;

		nFirstFind = nSecondFind + 1;
		nFirstFindWidth = nSecondFindWidth + 1;
		nFirstFindVisible = nSecondFindVisible + 1;
	}


	COLMAP::iterator it;
	long nItem = 0;

	for(it = pMap.begin(); it !=pMap.end(); it++)
	{
		long nIdex = GetItemRealIndex(it->second);

		long nFirst = it->first;
		long nSecond = it->second;
		long nNewIndex = GetColumns()->ChangeColumnOrder(it->first, nIdex);

		GetColumns()->GetAt(nItem)->SetWidth(pMapWidth[nItem]);
		GetColumns()->GetAt(nItem)->SetVisible(pMapVisible[nItem]);
		nItem++;
		//GetColumns()->ChangeColumnOrder(it->second, it->first);
	}
}

long CXTPListCtrl2::GetItemRealIndex(long nIdex)
{
	for(int i=0; i<GetColumns()->GetCount(); i++)
	{
		CXTPGridColumn *pCol = GetColumns()->GetAt(i);

		if(nIdex == pCol->GetItemIndex())
			return i;		
	}

	return -1;
}

void CXTPListCtrl2::SetItemNoSort(int nItem, BOOL bNoSort)
{
	CXTPGridRecords *pRecords = GetRecords();
	if(pRecords == NULL) return;
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nItem);
	pRecord->m_bNoSort = bNoSort;
}

BOOL CXTPListCtrl2::GetItemNoSort(long nItem)
{
	CXTPGridRecords *pRecords = GetRecords();
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nItem);
	return pRecord->m_bNoSort;
}

BOOL CXTPListCtrl2::GetItemNoSort(CXTPGridRecord *pRecord)
{
	return ((CXTPListCtrlRecord2*)pRecord)->m_bNoSort;
}

BOOL CXTPListCtrl2::IsStringDigitWithComma(CString &strText)
{
	for(int i = 0; i < strText.GetLength() ; i++) 
		if(!isdigit((::byte)strText.GetAt(i)) && strText.GetAt(i) != ',' && strText.GetAt(i) != ' ' && strText.GetAt(i) != '-') 
			return FALSE;
	return TRUE;
}


int _cdecl CXTPListCtrl2::CompareRows(const CXTPGridRow** ppRow1, const CXTPGridRow** ppRow2)
{ 
	CXTPGridColumns* pColumns = (**ppRow1).GetControl()->GetColumns();

	CXTPGridRecord* pRecord1 = (**ppRow1).GetRecord();
	CXTPGridRecord* pRecord2 = (**ppRow2).GetRecord();

	ASSERT(pColumns);
	ASSERT(pRecord1 && pRecord2 || !pRecord1 && !pRecord2);

	if (pRecord1 == pRecord2 && pRecord1)
		return 0;

	if (!pRecord1 && !pRecord2)
	{
		// compare groupRows by its first not group child rows
		if ((*ppRow1)->HasChildren() && (*ppRow2)->HasChildren())
		{
			CXTPGridRow* pRow1a = (CXTPGridRow*)(*ppRow1);
			CXTPGridRow* pRow2a = (CXTPGridRow*)(*ppRow2);

			if (pRow1a->GetChilds() && pRow1a->GetChilds()->GetCount() &&
				pRow2a->GetChilds() && pRow2a->GetChilds()->GetCount())
			{
				pRow1a = pRow1a->GetChilds()->GetAt(0);
				pRow2a = pRow2a->GetChilds()->GetAt(0);

				return CompareRows((const CXTPGridRow**)&pRow1a, (const CXTPGridRow**)&pRow2a);
			}
		}
	}

	if (!pRecord1 || !pRecord2)
	{
		ASSERT(FALSE);
		return 0;
	}

	for (int nGroupOrder = 0; nGroupOrder < pColumns->GetGroupsOrder()->GetCount(); nGroupOrder++)
	{
		CXTPGridColumn* pColumn = pColumns->GetGroupsOrder()->GetAt(nGroupOrder);
		if (!pColumn->IsAutoSortWhenGrouped())
			continue;

		BOOL bIncreasing = pColumn->IsSortedIncreasing();

		CXTPGridRecordItem* pItem1 = pRecord1->GetItem(pColumn);
		CXTPGridRecordItem* pItem2 = pRecord2->GetItem(pColumn);

		if (!pItem1 || !pItem2)
			continue;

		int nCompareResult = pItem1->CompareGroupCaption(pColumn, pItem2);

		if (nCompareResult != 0)
			return nCompareResult * (bIncreasing ? 1 : -1);
	}


	if(((CXTPListCtrlRecord2*)pRecord1)->m_bNoSort &&
		((CXTPListCtrlRecord2*)pRecord2)->m_bNoSort)
	{
		return pRecord1->GetIndex() > pRecord2->GetIndex() ? 1 : -1;
	}

	if(((CXTPListCtrlRecord2*)pRecord1)->m_bNoSort)
		return 1;

	if(((CXTPListCtrlRecord2*)pRecord2)->m_bNoSort)
		return -1;

	for (int nSortOrder = 0; nSortOrder < pColumns->GetSortOrder()->GetCount(); nSortOrder++)
	{
		CXTPGridColumn* pColumn = pColumns->GetSortOrder()->GetAt(nSortOrder);
		BOOL bIncreasing = pColumn->IsSortedIncreasing();

		CXTPGridRecordItem* pItem1 = pRecord1->GetItem(pColumn);
		CXTPGridRecordItem* pItem2 = pRecord2->GetItem(pColumn);

		if (!pItem1 || !pItem2)
			continue;

		int nCompareResult;
		if(GetSortType(nSortOrder) == MY_SORT_STRING)
			nCompareResult = pItem1->Compare(pColumn, pItem2);
		else
			nCompareResult = Compare(pColumn, pItem1, pItem2);

		if (nCompareResult != 0)
			return nCompareResult * (bIncreasing ? 1 : -1);
	}

	return pRecord1->GetIndex() > pRecord2->GetIndex() ? 1 : -1;

	return 0;
}

int CXTPListCtrl2::GetSortType(int nSortOrder)
{
	SORT_TYPE_MAP::iterator it = m_mapSortType.find(nSortOrder);
	if(it == m_mapSortType.end())
		return MY_SORT_STRING;
	return m_mapSortType[nSortOrder];
}


int CXTPListCtrl2::Compare(CXTPGridColumn *pColumn, CXTPGridRecordItem* pItem1, CXTPGridRecordItem* pItem2)
{
	if (!pItem1 || !pItem2)
		return 0;

	if (pItem1->GetSortPriority() != -1 || pItem2->GetSortPriority() != -1)
		return pItem1->GetSortPriority() - pItem2->GetSortPriority();

	CString strCaption1 = pItem1->GetCaption(pColumn);
	CString strCaption2 = pItem2->GetCaption(pColumn);

	strCaption1.Replace(",", "");
	strCaption2.Replace(",", "");

	int nNum1 = atol(strCaption1);
	int nNum2 = atol(strCaption2);

	if(nNum1 == nNum2)
		return 0;
	else if(nNum1 < nNum2)
		return -1;
	else 
		return 1;
}

void CXTPListCtrl2::SetItemNoSort(CXTPGridRecord *pRecord, BOOL bNoSort)
{
	((CXTPListCtrlRecord2*)pRecord)->m_bNoSort = bNoSort;
}

void CXTPListCtrl2::SetItemString(int nItem, CString strData)
{
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nItem);
	pRecord->m_strString = strData;
}

void CXTPListCtrl2::SetItemString(CXTPGridRecord *pRecord, CString strData)
{
	((CXTPListCtrlRecord2*)pRecord)->m_strString = strData;
}

CString CXTPListCtrl2::GetItemString(int nItem)
{
	CXTPGridRows *pRows = GetRows();
	CXTPGridRow *pRow = pRows->GetAt(nItem);
	CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)pRow->GetRecord();
	return pRecord->m_strString;
}

CString CXTPListCtrl2::GetItemString(CXTPGridRecord *pRecord)
{
	return ((CXTPListCtrlRecord2*)pRecord)->m_strString;
}

void CXTPListCtrl2::ChangeItemTextColor(int nRecordCount, int nItemIndex, COLORREF rgb)
{
	if (nRecordCount < GetRecords()->GetCount() && nItemIndex < GetColumns()->GetCount())
	{
		CXTPListCtrlRecord2* pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nRecordCount);
		CXTPGridRecordItem* pItem = pRecord->GetItem(nItemIndex);
		pItem->SetTextColor(rgb);
	}
}

void CXTPListCtrl2::ChangeItemBackColor(int nRecordCount, int nItemIndex, COLORREF rgb)
{
	if (nRecordCount < GetRecords()->GetCount() && nItemIndex < GetColumns()->GetCount())
	{
		CXTPListCtrlRecord2* pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nRecordCount);
		CXTPGridRecordItem* pItem = pRecord->GetItem(nItemIndex);
		pItem->SetBackgroundColor(rgb);
	}
}

void CXTPListCtrl2::ChangeRecordTextColor(int nRecordCount, COLORREF rgb)
{
	if (nRecordCount < GetRecords()->GetCount())
	{
		CXTPListCtrlRecord2* pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nRecordCount);
		for (int i = 0 ; i < pRecord->GetItemCount() ; i++)
		{
			CXTPGridRecordItem* pItem = pRecord->GetItem(i);
			pItem->SetTextColor(rgb);
		}
	}
}

void CXTPListCtrl2::ChangeRecordBackColor(int nRecordCount, COLORREF rgb)
{
	if (nRecordCount < GetRecords()->GetCount())
	{
		CXTPListCtrlRecord2* pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nRecordCount);
		for (int i = 0 ; i < pRecord->GetItemCount() ; i++)
		{
			CXTPGridRecordItem* pItem = pRecord->GetItem(i);
			pItem->SetBackgroundColor(rgb);
		}
	}
}

void CXTPListCtrl2::ChangeRecordTextColor(CXTPGridRecord *pRecord, COLORREF rgb)
{
	for (int i = 0 ; i < pRecord->GetItemCount() ; i++)
	{
		CXTPGridRecordItem* pItem = pRecord->GetItem(i);
		pItem->SetTextColor(rgb);
	}
}

void CXTPListCtrl2::ChangeRecordBackColor(CXTPGridRecord *pRecord, COLORREF rgb)
{
	for (int i = 0 ; i < pRecord->GetItemCount() ; i++)
	{
		CXTPGridRecordItem* pItem = pRecord->GetItem(i);
		pItem->SetBackgroundColor(rgb);
	}
}

void CXTPListCtrl2::ChangeRecordTextBold(int nRecordCount, BOOL bEnable)
{
	if (nRecordCount < GetRecords()->GetCount())
	{
		CXTPListCtrlRecord2* pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nRecordCount);
		for (int i = 0 ; i < pRecord->GetItemCount() ; i++)
		{
			CXTPGridRecordItem* pItem = pRecord->GetItem(i);
			pItem->SetBold(bEnable);
		}
	}
}

void CXTPListCtrl2::ChangeRecordTextBold(CXTPGridRecord *pRecord, BOOL bEnable)
{
	for (int i = 0 ; i < pRecord->GetItemCount() ; i++)
	{
		CXTPGridRecordItem* pItem = pRecord->GetItem(i);
		pItem->SetBold(bEnable);
	}
}

void CXTPListCtrl2::ChangeItemTextBold(int nRecordCount, int nItemIndex, BOOL bEnable)
{
	if (nRecordCount < GetRecords()->GetCount())
	{
		CXTPListCtrlRecord2* pRecord = (CXTPListCtrlRecord2*)GetRecords()->GetAt(nRecordCount);
		CXTPGridRecordItem* pItem = pRecord->GetItem(nItemIndex);
		pItem->SetBold(bEnable);
	}
}