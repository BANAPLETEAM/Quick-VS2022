#pragma once

#ifdef _XTPListCtrl2
	#define NM_LISTVIEW		XTP_NM_REPORTRECORDITEM
	#define	iSubItem		pColumn->GetItemIndex()
	#define	iItem			pRow->GetIndex()
#endif

#define ONE_YEAR 365

#define ALL_TYPE_COL		-1
#define ITEM_DATA_COL		999

typedef map<long, long> SEARCH_ALL_COLUMN;
typedef map<long, long> SORT_TYPE_MAP;

enum { MY_SORT_STRING = 0, MY_SORT_NUM = 1}; 

class CXTPListCtrl2;

class CXTPListCtrlRecord2 : public CXTPGridRecord
{
public:
	CXTPListCtrlRecord2()
	{
		m_bNoSort = 0;
	}

	CXTPListCtrlRecord2(CString strItem, int nTotalCol, int nIconIndex, int nColNum1, int nColNum2)
	{
		m_bNoSort = 0;
		m_nLong = 0;
		m_nLong2 = 0;
		m_nLong3 = 0;
		m_dwData = 0;
		m_strString = "";
		int nColIndex=0;

		if(nTotalCol > 0)
		{
			CXTPGridRecordItem* pItem;

			if(nColNum1!=-1 && nColIndex==nColNum1)
				pItem = AddItem(new CXTPGridRecordItemNumber(atol(strItem)));
			else
				pItem = AddItem(new CXTPGridRecordItemText(strItem));

			if(nIconIndex >= 0)
				pItem->SetIconIndex(nIconIndex);

			nTotalCol--;
			nColIndex++;

			while(nTotalCol > 0)
			{
				if(nColNum1!=-1 && nColIndex==nColNum1)
					AddItem(new CXTPGridRecordItemNumber(0));
				else if(nColNum2!=-1 && nColIndex==nColNum2)
					AddItem(new CXTPGridRecordItemNumber(0));
				else
					AddItem(new CXTPGridRecordItemText(""));

				nTotalCol--;
				nColIndex++;
			}
		}
	}

	class CCheckRecord : public CXTPGridRecordItem
	{
	public:
		CCheckRecord(BOOL bCheck)
		{
			HasCheckbox(TRUE);
			SetChecked(bCheck);
		}

	};

	CXTPListCtrlRecord2(CString strItem, int nTotalCol, int nIconIndex, BOOL bCheck)
	{ 
		m_nLong = 0;
		m_nLong2 = 0;
		m_nLong3 = 0;
		m_dwData = 0;
		m_strString = "";

		if(nTotalCol > 0)
		{
			CXTPGridRecordItem* pItem = AddItem(new CCheckRecord(bCheck));
			if(nIconIndex >= 0)
				pItem->SetIconIndex(nIconIndex);

			nTotalCol--;

			while(nTotalCol > 0)
			{
				AddItem(new CXTPGridRecordItemText(""));
				nTotalCol--;
			}
		}
	}


public:
	DWORD m_dwData;
	long m_nLong;
	long m_nLong2;
	long m_nLong3;
	CString m_strString;
	CString m_strText;
	CString m_strText2;
	CString m_strText3;
	BOOL m_bNoSort;
	COleDateTime m_dtDate;

	virtual void CXTPListCtrlRecord2::GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
	long GetChecked(long nCol)	{return ((CCheckRecord*)GetItem(nCol))->IsChecked(); }
};



class CXTPListCtrl2 : public CXTPGridControl
{
	DECLARE_DYNAMIC(CXTPListCtrl2)

public:
	CXTPListCtrl2();
	virtual ~CXTPListCtrl2();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	BOOL bInit;
	CComboBox *m_pFilterCombo;
	CComboBox *m_pTypeCombo;
	CEdit *m_pFilterEdit;
	SEARCH_ALL_COLUMN m_sac;
	BOOL m_bInsertSearchAll;
	
	BOOL m_bInsertTypeFilter;
	char m_szTypeString[50][50];
	DWORD m_dwTypeItemData[50];
	int m_nTypeTargetCol;
	BOOL m_bItemData;

	static CFont *m_pfntBold;
	BOOL m_bSelect;
	CXTPGridSelectedRows * pSelectedRows;

	int m_nOrderIndexCol;
	CString m_strFooterMessage;
	BOOL m_bDrawCount;
	BOOL m_bPrintFooterMessage;
protected:
	void InitControl();	//LIST관련 초기화 함수 호출시 한번만 실행된다.


public:
	void SetDrawCount(BOOL bDrawCount){m_bDrawCount = bDrawCount;}
	static SORT_TYPE_MAP m_mapSortType;
	void SetExternalControl(CWnd *pFilterCombo, CWnd *pFilterEdit, CWnd *pTypeCombo = NULL);
	static int _cdecl CompareRows(const CXTPGridRow** pRow1, const CXTPGridRow** pRow2);
	static int Compare(CXTPGridColumn *pColumn, CXTPGridRecordItem* pItem1, CXTPGridRecordItem* pItem2);
	static int GetSortType(int nSortOrder);

	//void LoadListInfo();

	int GetSelectedItem();
	int GetNextItem(int nIndex, int nType = 0);
	BOOL IsStringDigitWithComma(CString &strText);

	CXTPGridRecord *InsertItem(int nItem, CString strItem, int nImage = -1, int nColNum1 = -1, int nColNum2 = -1);
	CXTPGridRecord *InsertItemReturn(int nItem, CString strItem, int nImage = -1, int nColNum1 = -1, int nColNum2 = -1, BOOL bCheckBox = FALSE);
	void InsertCheckItem(int nItem, CString strItem, int nImage = -1, BOOL bChecked = FALSE);
	void SetItemNoSort(int nItem, BOOL bNoSort = TRUE);
	void SetItemNoSort(CXTPGridRecord *pRecord, BOOL bNoSort = TRUE);
	void ReSortRows();

	int InsertColumn(int nCol, CString strColumnHeading, int nAlignment, int nWidth);
	CXTPGridColumn* InsertColumn1(int nCol, CString strColumnHeading, int nAlignment, int nWidth);
	void SetImageList(CImageList *pImageList, int nType);
	void SetExtendedStyle(int nStyle);
	void CheckCurColumnSortType();

	void SetItemText(int nItem, int nSubItem, CString strItem, int nImage = -1);
	void SetItemText(int nItem, int nSubItem, long nNumber, int nImage = -1);
	void SetItemText(CXTPGridRecord *pRecord, int nSubItem, CString strItem, int nImage = -1);

	void SetItemTextHyperLink(int nItem, int nSubItem, CString strItem, int nImage = -1);

	void SetItemTextLong(int nItem, int nSubItem, long nValue, int nImage = -1);
	void SetItemTextLong(CXTPGridRecord *pRecord, int nSubItem, long nValue, int nImage = -1);
	void SetItemTextMyNumberFormat(int nItem, int nSubItem, long nValue, int nImage = -1);
	void SetItemTextMyNumberFormat(CXTPGridRecord *pRecord, int nSubItem, long nValue, int nImage = -1);

	CString GetItemText(int nItem, int nSubItem);
	CString GetItemText(CXTPGridRecord *pRecord, int nSubItem);

	void SetItemData(CXTPGridRecord *pRecord, DWORD dwData);
	void SetItemData(int nItem, DWORD dwData);
	void SetItemLong(CXTPGridRecord *pRecord, long nData);
	void SetItemLong(int nItem, long nData);
	void SetItemLong2(CXTPGridRecord *pRecord, long nData);
	void SetItemLong2(int nItem, long nData);
	void SetItemLong3(CXTPGridRecord *pRecord, long nData);
	void SetItemLong3(int nItem, long nData);
	void SetItemDate(int nItem, COleDateTime nData);
	void SetItemDate(CXTPGridRecord *pRecord, COleDateTime dtDate);
	void SetItemDataText(int nItem, CString sData);
	void SetItemDataText2(int nItem, CString sData);
	void SetItemDataText3(int nItem, CString sData);
	void SetItemDataText(CXTPGridRecord *pRecord, CString strData);
	void SetItemDataText2(CXTPGridRecord *pRecord, CString sData);
	void SetItemDataText3(CXTPGridRecord *pRecord, CString sData);

	
	CXTPGridRecord* GetItemRecord(int nItem);
	DWORD GetItemData(int nItem);
	DWORD GetItemData(CXTPGridRecord *pRecord);
	COleDateTime GetItemDate(int nItem);
	COleDateTime GetItemDate(CXTPGridRecord *pRecord);
	CString GetItemDataText(CXTPGridRecord *pRecord);
	CString GetItemDataText2(CXTPGridRecord *pRecord);
	CString GetItemDataText3(CXTPGridRecord *pRecord);
	CString GetItemDataText(int nItem);
	CString GetItemDataText2(int nItem);
	CString GetItemDataText3(int nItem);


	int GetVisibleItemCount();

	long GetItemLong(int nItem);
	long GetItemLong(CXTPGridRecord *pRecord);
	long GetItemLong2(int nItem);
	long GetItemLong2(CXTPGridRecord *pRecord);
	long GetItemLong3(int nItem);
	long GetItemLong3(CXTPGridRecord *pRecord);
	CString GetItemString(CXTPGridRecord *pRecord);
	CString GetItemString(int nItem);
	void SetItemString(CXTPGridRecord *pRecord, CString strData);
	void SetItemString(int nItem, CString strData);
	void SetSelectedRow(long nRow);

	int GetItemCount();
	void EnsureVisibleEx(int nItem); 

	void HideRow(CXTPGridRow *pRow);
	void HideRow(int nItem);

	void ShowAllRow();
	
	//void Filter(CString strFilter, int nFilterCol, int nTypeData);
	void Filter(CString strFilter, int nFilterCol = 0, int nTypeData = ALL_TYPE_COL);
	void InsertSearchAllColumn(int nCol);

	void DeleteAllItems();

	void InsertTypeList(CString strTitle, int nCol, CString strKeyword, long dwItemData = -1);	
	CXTPGridColumn *InsertColumnReturn(int nCol, CString strColumnHeading, int nAlignment, int nWidth);

	long m_nColor[ONE_YEAR];
	long m_nDayCount;
	//column coloring
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics) 
	{
		if(pDrawArgs->pColumn == NULL || pDrawArgs->pRow == NULL)
			return;

		int nCol = pDrawArgs->pColumn->GetItemIndex();
		int nRow = pDrawArgs->pRow->GetIndex();

		for(int i=0; i<m_nDayCount; i++)
		{			
			if(m_nColor[i] == nCol)
			{
				pItemMetrics->clrBackground = RGB(200, 255, 200);
				pItemMetrics->clrForeground = RGB(0, 0, 0);
			}
		}

		/*
		CString strFormat = GetItemText(nRow, 1);

		if(strFormat.Find("합계") > 1)
		{
			pItemMetrics->clrBackground = RGB(200, 200, 255);
		}
		*/
	}

	void ToExcel(CString strTitle = "");
	BOOL GetChecked(int nRow, int nCol);
	BOOL GetChecked(CXTPGridRecord *pRecord, int nCol);
	void SetChecked(int nRow, int nCol, BOOL bCheck);
	void SetChecked(CXTPGridRecord *pRecord, int nCol, BOOL bCheck);
	virtual void OnDraw(CDC *pDC);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);

	void SaveReportOrder(CString sClass, CString sReport);
	void LoadReportOrder(CString sClass, CString sReport);
	long GetItemRealIndex(long nIdex);
	BOOL GetItemNoSort(long nItem);
	BOOL GetItemNoSort(CXTPGridRecord *pRecord);

	void SetOrderIndexCol(int nCol) {m_nOrderIndexCol = nCol;};
	int GetOrderIndexCol() { return m_nOrderIndexCol; }	
	CXTPGridRecord* GetFirstSelectedRecord();

	void SetFooterMessage(CString strFooterMessage) {m_strFooterMessage = strFooterMessage;}; 
	void AddFooterRows();

	void ChangeItemTextColor(int nRecordCount, int nItemIndex, COLORREF rgb);
	void ChangeItemBackColor(int nRecordCount, int nItemIndex, COLORREF rgb);
	void ChangeRecordTextColor(int nRecordCount, COLORREF rgb);
	void ChangeRecordBackColor(int nRecordCount, COLORREF rgb);
	void ChangeRecordTextColor(CXTPGridRecord *pRecord, COLORREF rgb);
	void ChangeRecordBackColor(CXTPGridRecord *pRecord, COLORREF rgb);
	void ChangeItemTextBold(int nRecordCount, int nItemIndex, BOOL bEnable);
	void ChangeRecordTextBold(int nRecordCount, BOOL bEnable);
	void ChangeRecordTextBold(CXTPGridRecord *pRecord, BOOL bEnable);
};




class CXTPListCtrlLogiRecord : public CXTPGridRecord
{
public:
	CXTPListCtrlLogiRecord(CString strItem, int nTotalCol, int nIconIndex, int nColNum1, int nColNum2, BOOL bHasCheckBox)
	{
		m_bNoSort = 0;
		m_nLong = 0;
		m_dwData = 0;
		m_strString = "";
		int nColIndex=0;

		if(nTotalCol > 0)
		{
			CXTPGridRecordItem* pItem;

			if(nColNum1!=-1 && nColIndex==nColNum1)
				pItem = AddItem(new CXTPGridRecordItemNumber(atol(strItem)));
			else
				pItem = AddItem(new CXTPGridRecordItemText(strItem));

			if(bHasCheckBox)
				pItem->HasCheckbox(bHasCheckBox);

			if(nIconIndex >= 0)
				pItem->SetIconIndex(nIconIndex);

			nTotalCol--;
			nColIndex++;

			while(nTotalCol > 0)
			{
				if(nColNum1!=-1 && nColIndex==nColNum1)
					AddItem(new CXTPGridRecordItemNumber(0));
				else if(nColNum2!=-1 && nColIndex==nColNum2)
					AddItem(new CXTPGridRecordItemNumber(0));
				else
					AddItem(new CXTPGridRecordItemText(""));

				nTotalCol--;
				nColIndex++;
			}
		}
	}

	class CCheckRecord : public CXTPGridRecordItem
	{
	public:
		CCheckRecord(BOOL bCheck)
		{
			HasCheckbox(TRUE);
			SetChecked(bCheck);
		}

	};

	CXTPListCtrlLogiRecord(CString strItem, int nTotalCol, int nIconIndex, BOOL bCheck)
	{ 
		m_nColumnTerm = 0;
		m_nStartColumn = 0;
		m_bColumnColor = FALSE;
		m_nLong = 0;
		m_nLong2 = 0;
		m_nLong3 = 0;
		m_nLong4 = 0;
		m_dwData = 0;
		m_strString = "";

		if(nTotalCol > 0)
		{
			CXTPGridRecordItem* pItem = AddItem(new CCheckRecord(bCheck));
			if(nIconIndex >= 0)
				pItem->SetIconIndex(nIconIndex);

			nTotalCol--;

			while(nTotalCol > 0)
			{
				AddItem(new CXTPGridRecordItemText(""));
				nTotalCol--;
			}
		}
	}

	//column coloring
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		if(pDrawArgs == NULL || pItemMetrics == NULL)
			return;

		if(!pDrawArgs->pColumn || !pDrawArgs->pRow)
			return;

		int nCol = pDrawArgs->pColumn->GetItemIndex();
		int nRow = pDrawArgs->pRow->GetIndex();

		if(((CXTPListCtrl2*)pDrawArgs->pControl)->GetOrderIndexCol() == nCol)
		{
			//
			//pDrawArgs->pRow->GetRecord()->GetItem(nCol)->SetCaption(ltoa(nRow+1, buffer, 10));
			pItemMetrics->strText.Format("%d", nRow + 1);
			pItemMetrics->clrForeground = RGB(80, 80, 80);
			pItemMetrics->clrBackground = RGB(255, 255, 255);
		}

		long nIndex = pDrawArgs->pItem->GetIconIndex();

		if(nIndex > 0)
			pDrawArgs->pItem->SetIconIndex(nIndex);

		if (m_bColumnColor == TRUE)
		{
			if (m_nColumnTerm != 0 && nCol >= m_nStartColumn)
			{
				//if ((((nCol - 1) / m_nColumnTerm) % 2) == 1)
				if (((((nCol - m_nStartColumn) - 1) / m_nColumnTerm) % 2) == 1)
					pItemMetrics->clrBackground = RGB(255, 240, 240);
			}
		}
	}

public:
	DWORD m_dwData;
	long m_nLong;
	long m_nLong2;
	long m_nLong3;
	long m_nLong4;
	CString m_strString;
	CString m_strText;
	CString m_strText2;
	CString m_strText3;
	BOOL m_bNoSort;
	BOOL m_bFooterRecord;
	int m_nColumnTerm;
	int m_nStartColumn;
	BOOL m_bColumnColor;
	COleDateTime m_dtDate;
	COleDateTime m_dtDate2;

	long GetChecked(long nCol)	{return ((CCheckRecord*)GetItem(nCol))->IsChecked(); }
	void SetChecked(long nCol, BOOL bCheck) {((CCheckRecord*)GetItem(0))->SetChecked(bCheck); }
};

