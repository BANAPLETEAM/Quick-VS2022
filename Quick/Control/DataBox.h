#pragma once


class CTaskFrame;



class CMyXTPGridRecord : public CXTPGridRecord
{
public:
	CMyXTPGridRecord();
	~CMyXTPGridRecord(){}
public:
	long m_nMyRecordItemCount;
	CXTPGridRecord *m_pSubRecord;

	CMyXTPGridRecord* MySubAddItem(int niValue);
	CMyXTPGridRecord* MySubAddItem(long nlValue);
	CMyXTPGridRecord* MySubAddItem(COleDateTime dtValue, CString sFormat = "%Y-%m-%d");
	CMyXTPGridRecord* MySubAddItem(CString sValue);

	CMyXTPGridRecord* MySubCheckAddItem( BOOL bDefaluValue);
	CMyXTPGridRecord* MySubComboAddItem(CStringArray &sArray,CUIntArray &nArray, int nValue);

	CObject *m_pObject;
	BOOL m_bData;
	int m_nData;
	long m_nDataLong;
	long m_lData;
	long m_lData2;
	long m_lData3;
	long m_lData4;
	CString m_sData;
	CString m_sData2;
	CString m_sData3;
	COleDateTime m_dtData;	
	COleDateTime m_dtData2;	
	DWORD_PTR m_pDWORD;


	long m_nTreeParentNo;
	CString m_sTreeRef;

public:
	BOOL m_bDirtyFlag;

	void SetItemData( DWORD_PTR pValue){m_pDWORD = pValue; }
	void SetItemDataBool(BOOL bVal){m_bData = bVal;}	
	void SetItemDataInt(int iVal){m_nData = iVal;}
	void SetItemDataLong(long lVal){m_lData = lVal;}
	void SetItemDataLong2(long lVal){m_lData2 = lVal;}
	void SetItemDataLong3(long lVal){m_lData3 = lVal;}
	void SetItemDataLong4(long lVal){m_lData4 = lVal;}

	void SetItemDataString(CString str){m_sData = str;}
	void SetItemDataString2(CString str){m_sData2 = str;}
	void SetItemDataString3(CString str){m_sData3 = str;}

	void SetItemDataDateTime(COleDateTime dt){m_dtData =dt;}
	void SetItemDataDateTime2(COleDateTime dt){m_dtData2 =dt;}
	void SetItemDataObject(CObject *pObject){m_pObject = pObject;} 



	DWORD_PTR GetItemData(){return m_pDWORD; }
	BOOL GetItemDataBool(){ return m_bData;}
	int GetItemDataInt(){return m_nData;}
	long GetItemDataLong(){return m_lData;}
	long GetItemDataLong2(){return m_lData2;}
	long GetItemDataLong3(){return m_lData3;}
	long GetItemDataLong4(){return m_lData4;}


	CString GetItemDataString(){return m_sData;}
	CString GetItemDataString2(){return m_sData2;}
	CString GetItemDataString3(){return m_sData3;}
	COleDateTime GetItemDateTime(){return m_dtData;}
	COleDateTime GetItemDateTime2(){return m_dtData2;}
	CObject* GetItemDataObject(){ return m_pObject;}

	
	long GetItemlValue(int nCol);
	CString GetItemSValue(int nCol);
};

class CLMyXTPGridRecordItemNumber : public CXTPGridRecordItemNumber 
{
public:
	CLMyXTPGridRecordItemNumber(double nValue = 0):CXTPGridRecordItemNumber(nValue){m_bItemDirtyFlag = FALSE;}
	BOOL m_bItemDirtyFlag;
protected:
	virtual void OnEditChanged(	XTP_REPORTRECORDITEM_ARGS* pItemArgs, 	LPCTSTR szText		)
	{
		CString sNewValue(szText);
		if(sNewValue.GetLength() ==0) sNewValue = "0";

		long nNewValue = atol(sNewValue);
		long nOriginalValue = (long)GetValue();
		if(nOriginalValue != nNewValue)
		{
			CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)pItemArgs->pRow->GetRecord();
			m_bItemDirtyFlag = pRecord->m_bDirtyFlag = TRUE;
			this->m_bBoldText = TRUE;
			this->m_clrBackground = RGB(235,238,237);
			SetValue(nNewValue);
		}
	}
};



//class CLMyXTPGridRecordItemText : public CXTPGridRecordItemText
//{
//public:
//	CLMyXTPGridRecordItemText(CString sValue = ""):CXTPGridRecordItemText(sValue){ 
//
//		m_bItemDirtyFlag = FALSE;
//		m_bNotValueSpace = FALSE;
//		m_bDirectChange = TRUE;
//		m_sOldValue = "";
//	}
//	BOOL m_bItemDirtyFlag;
//	BOOL m_bNotValueSpace;
//	BOOL m_bDirectChange;
//	CString m_sOldValue;
//
//	void OldValueChange()
//	{
//		DirectValueView();
//
//		if(!m_bNotValueSpace)
//			SetValue(m_sOldValue);
//		else if(m_bNotValueSpace && m_sOldValue.GetLength() == 0)
//			SetValue("");
//		else
//			SetValue(m_sOldValue);			
//
//		SetCaption(m_sOldValue);
//
//	}
//protected:
//
//	void SetChangeView(BOOL bTrue = TRUE, CMyXTPGridRecord *pRecord = NULL)
//	{
//		m_bItemDirtyFlag = TRUE;
//		if(pRecord)
//			pRecord->m_bDirtyFlag = TRUE;
//
//		m_clrBackground = RGB(235,238,237);
//		m_bBoldText = TRUE;
//
//	}
//	void DirectValueView()
//	{
//		m_clrBackground = RGB(255,255,255);
//		m_bBoldText = FALSE;
//	}
//
//
//	virtual void OnEditChanged(	XTP_REPORTRECORDITEM_ARGS* pItemArgs, 	LPCTSTR szText		)
//	{
//		CString sNewValue(szText);
//		m_sOldValue = GetCaption(pItemArgs->pColumn);
//		CString str = GetValue();
//		CString str1 = pItemArgs->pItem->GetCaption(pItemArgs->pColumn);
//		CString str2 = ((CLMyXTPGridRecordItemText*)pItemArgs->pItem)->GetValue();
//		if(sNewValue.GetLength() == 0 && m_sOldValue.GetLength() > 0)
//			return;	
//
//
//
//		if(m_sOldValue.Compare(sNewValue) != 0)
//		{
//			CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)pItemArgs->pRow->GetRecord();
//
//			if(m_bDirectChange)
//				DirectValueView();			
//			else
//				SetChangeView(TRUE, pRecord);					
//
//			if(!m_bNotValueSpace)
//				SetValue(sNewValue);
//			else if(m_bNotValueSpace && sNewValue.GetLength() == 0)
//				SetValue("");
//			else
//				SetValue(sNewValue);			
//
//			SetCaption(sNewValue);
//		}		
//	}
//};

class CMyCheckRecordItem : public CXTPGridRecordItem
{
public:
	CMyCheckRecordItem(BOOL bCheck, CMyXTPGridRecord *pRecord)
	{
		this->HasCheckbox(TRUE);
		SetChecked(bCheck);

		m_pRecord = pRecord;
	}
	virtual BOOL OnLButtonDown(	XTP_REPORTRECORDITEM_CLICKARGS* pClickArgs)
	{
		long nCol = pClickArgs->pRow->GetRecord()->GetIndex();
		CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)pClickArgs->pRow->GetRecord();
		pRecord->m_bDirtyFlag = TRUE;		
		return FALSE;
	}


	BOOL GetCheck()
	{
		BOOL bCheck = IsChecked();
		return bCheck;
	}
	CMyXTPGridRecord *m_pRecord;

};

class CMyComboRecordItem : public CXTPGridRecordItem
{
public:

	CMyComboRecordItem( CStringArray	&sArray, CUIntArray &nArray, int nCurrntValue = 0)
	{		
		m_nValue = nCurrntValue;

		//m_pRecord = (CMyXTPGridRecord*)pCol->GetControl();
		for(int i = 0; i < sArray.GetCount(); i++)
			GetEditOptions(NULL)->AddConstraint(_T(sArray.GetAt(i)), nArray.GetAt(i));

		GetEditOptions(NULL)->m_bConstraintEdit = FALSE;
		GetEditOptions(NULL)->m_bAllowEdit = TRUE;
		GetEditOptions(NULL)->m_bExpandOnSelect = TRUE;
		GetEditOptions(NULL)->AddComboButton();
		m_bDirtyFlag = FALSE;			
	}

	CString GetCaption(CXTPGridColumn* /*pColumn*/)	
	{
		CXTPGridRecordItemConstraint* pConstraint = GetEditOptions(NULL)->FindConstraint(m_nValue);		

		//	ASSERT(pConstraint);
		if(pConstraint == NULL)
			return "";
		return pConstraint->m_strConstraint;
	}

	virtual void OnConstraintChanged(XTP_REPORTRECORDITEM_ARGS* pItemArgs, CXTPGridRecordItemConstraint* pConstraint)
	{
		m_nValue = (long)pConstraint->m_dwData;		
		long nCol = pItemArgs->pRow->GetRecord()->GetIndex();
		CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)pItemArgs->pRow->GetRecord();
		pRecord->m_bDirtyFlag = TRUE;
		this->m_bDirtyFlag = TRUE;
	}
	long GetValue()
	{
		return m_nValue;
	}

	void SetValue(int nValue)
	{
		m_nValue = nValue;

		SetGroupPriority(nValue);		
		SetSortPriority(GetGroupPriority());		
	}
protected:
	long m_nValue;
	CMyXTPGridRecord *m_pRecord;
public:
	BOOL m_bDirtyFlag;
};



#define HEADER_HEIGHT       2    // For printing
#define FOOTER_HEIGHT       2
#define LEFT_MARGIN         4
#define RIGHT_MARGIN        4
#define TOP_MARGIN          1
#define BOTTOM_MARGIN       1 
#define GAP                 1



typedef struct{
	BOOL bView;
	CString sFieldName;
	CString sColumnName;
	int		nColumnSize;
	int		nAlign;
	int		nCol;
	BOOL	bSetItemData;
	BOOL	bSetItemData2;
}oData;
typedef map<CString,oData> MapData;


#define ID_SEARCH_EDIT                  1490


#define  ALL_TYPE_COLUMN			-1
#define IDD_FIELDCHOOSER                611

typedef map<long, long> SEARCH_ALL_COLUMN_DATA;

class CDataBox : public CXTPGridControl
{
public:
	CDataBox();   // 표준 생성자입니다.
	virtual ~CDataBox();


	long m_nRecordItemCount;	
	CXTPGridRecords *m_pBodyRecords;	
	CMyXTPGridRecord *m_pSubTarGetRecord;
	CMyXTPGridRecord *m_pMainRecord;
	long m_nRecordCount;

public:
	BOOL m_bTreeItem;
	BOOL m_bHeader;
	DWORD m_dwData;
	long	m_nColumnCount;
	BOOL m_bCListCtrlInit;		

	int InsertColumn(int nCol, CString strHearName , int nAlignment = DT_LEFT, int nWidth =0,BOOL bAllowEdit = FALSE,BOOL bTreeColumn = FALSE );
	int DeleteItem(int nIndex, BOOL bRefresh = FALSE);	

	CMyXTPGridRecord * GetRecordsGetAt(int i)
	{
		return (CMyXTPGridRecord *)GetRecords()->GetAt(i);
	}	
	CMyXTPGridRecord * GetSelectedRowsGetAtGetRecord(int nSelectedRow)
	{
		return (CMyXTPGridRecord *)this->GetSelectedRows()->GetAt(nSelectedRow)->GetRecord();
	}	


	///////////////////////////////////// object
	void InsertItemData(DWORD_PTR obData);
	//DWORD_PTR GetItemData(int nReportRow);

	///////////////////////////////////// long, int
	void InsertItemDataLong(long nData);
	void InsertItemDataLong2(long nData);
	void InsertItemDataLong3(long nData);

	void SetItemDataLong(int nReportRow, long nData);
	void SetItemDataLong2(int nReportRow,long nData);
	void SetItemDataLong3(int nReportRow,long nData);
	long GetItemDataLong(int nReportRow);
	long GetItemDataLong(CMyXTPGridRecord *pRecord);
	long GetItemDataLong2(int nReportRow);
	long GetItemDataLong3(int nReportRow);

	void SetItemDataRecordLong(int nRoportRecord, long nData);
	void SetItemDataRecordLong2(int nRoportRecord, long nData);	
	void SetItemDataRecordLong3(int nRoportRecord, long nData);	
	long GetItemDataRecordLong(int nRecordRow);
	long GetItemDataRecordLong2(int nRecordRow);
	long GetItemDataRecordLong3(int nRecordRow);

	///////////////////////////////////// String, WString
	void InsertItemDataString(CString sData);
	void InsertItemDataString2(CString sData);

	void SetItemDataString(int nReportRow, CString sData);
	void SetItemDataString2(int nReportRow,CString sData);
	CString GetItemDataString(int nReportRow);
	CString GetItemDataString2(int nReportRow);

	void SetItemDataRecordString(int nRoportRecord, CString sData);
	void SetItemDataRecordString2(int nRoportRecord, CString sData);	
	CString GetItemDataRecordString(int nRecordRow);
	CString GetItemDataRecordString2(int nRecordRow);


	///////////////////////////////////// COleDateTime
	void InsertItemDataDate(COleDateTime dt);
	void InsertItemDataDate2(COleDateTime dt);

	void SetItemDataDate(int nReportRow, COleDateTime dt);
	void SetItemDataDate2(int nReportRow,COleDateTime dt);
	COleDateTime GetItemDataDate(int nReportRow);
	COleDateTime GetItemDataDate2(int nReportRow);

	void SetItemDataRecordDate(int nRoportRecord, COleDateTime dt);
	void SetItemDataRecordDate2(int nRoportRecord, COleDateTime dt);	
	COleDateTime GetItemDataRecordDate(int nRecordRow);
	COleDateTime GetItemDataRecordDate2(int nRecordRow);

	/////////////////////////////////////////////////






	void SetSelectedRow(long nRow);
	int GetItemCount();
	CXTPGridRow*  GetSelectedRow();
	CMyXTPGridRecord* GetSelectedRecord();	
	int GetSelectedCount();

	void SetItemCheck(int nReportRow, int nCol, BOOL bCheck);	
	BOOL GetItemCheck(int nReportRow, int nCol);	
	BOOL GetItemRecordRowCheck(int nRecord, int nCol);	
	void SetItemRecordRowCheck(int nRecord, int nCol, BOOL bCheck);	

	long GetItemComboValue(int nRow, int nCol)
	{
		CMyComboRecordItem *pItem = (CMyComboRecordItem*)(GetRecords()->GetAt(nRow)->GetItem(nCol));		
		return pItem->GetValue();

	}
	CMyXTPGridRecord * GetSelectedRecord(int i);	
public:

	CMyXTPGridRecord* MyAddItem(int niValue);
	CMyXTPGridRecord* MyAddItem(long nlValue);
	CMyXTPGridRecord* MyAddItem(COleDateTime dtValue, CString sFormat = "%Y-%m-%d");	
	CMyXTPGridRecord* MyAddItem(CString sValue);


	void TreeChildAddItem(int nCol,COleDateTime sValue,  CString sColName,int nColWidth,BOOL bEdit,int nAlignment);
	void TreeChildAddItem(int nCol,long sValue,  CString sColName,int nColWidth,BOOL bEdit,int nAlignment);
	void TreeChildAddItem(int nCol,CString sValue, CString sColName,int nColWidth,BOOL bEdit,int nAlignment);


	void TreeChildDepthAddItem(int nCol,CString sRef,long nParentNo, CString sValue,		CString sColName,int nColWidth,BOOL bEdit,int nAlignment);
	void TreeChildDepthAddItem(int nCol,CString sRef,long nParentNo, int iValue,			CString sColName,int nColWidth,BOOL bEdit,int nAlignment);
	void TreeChildDepthAddItem(int nCol,CString sRef,long nParentNo, long nValue,			CString sColName,int nColWidth,BOOL bEdit,int nAlignment);
	void TreeChildDepthAddItem(int nCol,CString sRef,long nParentNo, COleDateTime dtValue,  CString sColName,int nColWidth,BOOL bEdit,int nAlignment);


	CMyXTPGridRecord * ChildSearchRecord(CXTPGridRecords *pRecords,CString sTreeRef, int nLevel);


	CMyXTPGridRecord* MyComboAddItem(int nCol,CStringArray &sArray,CUIntArray &nArray,  CString sColName,int nColWidth,int nArignMent, int nDefaultValue);
	CMyXTPGridRecord* MyCheckAddItem(int nCol, BOOL bDefaultValue ,CString sColName,int nColWidth,int nArignMent , BOOL bCheckBox = TRUE);



	CMyXTPGridRecord* MyAddItem(int nCol,int niValue, CString sColName, int nColWidth,BOOL bEdit,int nAlignment);
	CMyXTPGridRecord* MyAddItem(int nCol,CString sValue, CString sColName, int nColWidth,BOOL bEdit,int nAlignment);
	CMyXTPGridRecord* MyAddItem(int nCol,COleDateTime sValue, CString sColName, int nColWidth,BOOL bEdit,int nAlignment);
	CMyXTPGridRecord* MyAddItem(int nCol,long sValue, CString sColName, int nColWidth,BOOL bEdit,int nAlignment);



	void MyAddItem(int nCol,CMkRecordset &pRs, CString sFieldName);	
	void MyAddItem(CMkRecordset &pRs, BOOL bAutoColumns = FALSE);
	CXTPGridColumn* ColumnInit(int nCol,CString sColName,int nColWidth, BOOL bEdit, int nAlignment);
	void EndItem();
	void DeleteAllItem();
	void HideRow(CXTPGridRow *pRow);	
	void HideRow(int nItem);
	void ShowAllRow();

	void ToExcel(CString strTitle = "");


	/*CListCtrl 형식*/


protected:


public:
	void InitControl();
	void SetExtendedStyle(DWORD dwNewStyle);
	CImageList* SetImageList(CImageList* pImageList, int nImageListType = -1);
	BOOL ModifyStyle(HWND hWnd = 0, DWORD dwRemove = 0, DWORD dwAdd = 0,  UINT nFlags = 0);


	CString GetItemText(int nItem, int nSubItem);
	int GetNextItem(int nIndex, int nType);
	void SetItemData(int nItem, DWORD_PTR pValue);
	DWORD_PTR GetItemData(int nItem);
	int GetSelectionMark();
	void DeleteAllItems();

	void InsertItem(int nItem, CString strItem, int nImage = -1, BOOL NoEndItemAndRandoInsert = TRUE);
	int SetItemText(int nIndex, int nCol , CString strText,int nImage =-1, BOOL bRefresh = FALSE);
	/*CListCtrl 형식*/


	void MySetItemData(CObject *pObject){m_pMainRecord->m_pObject = pObject;}	
	void MySetItemData(BOOL bVal){m_pMainRecord->m_bData = bVal;}
	void MySetItemData(long lVal){m_pMainRecord->m_lData = lVal;}
	void MySetItemData(CString str){m_pMainRecord->m_sData =str;}
	void MySetItemData(COleDateTime dt){m_pMainRecord->m_dtData =dt;}


	//void MySetItemData(int iVal){m_pMainRecord->m_nData = iVal;}


	void MyGetItemData(CObject *pObject){ pObject = m_pMainRecord->m_pObject;}
	void MyGetItemData(BOOL &bVal){ bVal =m_pMainRecord->m_bData;}	
	void MyGetItemData(long &lVal){lVal = m_pMainRecord->m_lData;}
	void MyGetItemData(CString &sVal){sVal = m_pMainRecord->m_sData;}
	void MyGetItemData(COleDateTime &dt){dt = m_pMainRecord->m_dtData;}	
	//void MyGetItemData(int &iVal){iVal =m_pMainRecord->m_nData;}	


	XTP_GRIDRECORDITEM_DRAWARGS *m_pDrawArgs;
	XTP_GRIDRECORDITEM_METRICS *m_pMetrics;



	void ShowRow(CXTPGridRow *pRow);
	void ShowRow(int nItem);

	void HideRecord(int nItem);
	void HideRecord(CMyXTPGridRecord *pRecord);
	void ShowRecord(int nItem);
	void ShowRecord(CMyXTPGridRecord *pRecord);






	/// Control 관련 Popup
protected:



	CDialogBar m_wndFieldChooserCustomer; 
	CDialogBar m_wndFilterEditDialogBar;
	CXTPGridSubListControl m_wndSubList;
	CXTPGridFilterEditControl m_wndFilterEdit;


	BOOL m_bFilterEditCreate;
	BOOL m_bColumnSelectCreate;

public:
	void SaveReportState();
	void LoadReportState();
	void ReportColumnSetting(NMHDR * pNotifyStruct);
	void OnShowFieldChooser();
	void OnShowSearchWord();
	void FilterEditCreate();
	void CreateColumnSelect();

	/// print 관련
	CSingleDocTemplate* m_pTemplate;
	BOOL m_bPrintPreview;
	CUIntArray m_aPageStart;        // Printed indexes.

	CTaskFrame *m_pTaskFrame;	

	void MyPrint();
	void MyPrintPreview();

	void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	void OnPrint(CDC* pDC, CPrintInfo* pInfo); 
	void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	//OnPrint 내부함수
	long PrintPage(CDC* pDC, CPrintInfo* pInfo, CRect rcPage, long nIndexStart);
	//PrintPage 내부함수
	void PrintHeader(CDC* pDC, CRect rcHeader);
	//PrintHeader 내부함수
	int GetColumnWidth(CXTPGridColumn* pColumnTest, int nTotalWidth);

	int PrintRows(CDC* pDC, CRect rcClient, long nIndexStart);
	//PrintRows 내부함수
	void PrintRow(CDC* pDC, CXTPGridRow* pRow, CRect rcRow);
	void PrintFooter(CDC* pDC, CPrintInfo* pInfo, CRect rcFooter);

	//BOOL CDataBox::PaginateTo(CDC* pDC, CPrintInfo* pInfo)
	void Print(CDC* pDC, CPrintInfo* pInfo);


	//  // 데이터 관련

	CString m_sQuery;
	MapData m_HeadData;
	CMkRecordset *m_pRs;
	CMkCommand *m_pCmd;	

	void AddHeader(int nCol,BOOL bView, CString sFieldName, CString sColumnName, int nColumnSize = 0 , int nAlign = DT_LEFT, BOOL bEdit = FALSE, BOOL bSetItemData = FALSE, BOOL bSetItemData2 = FALSE);	
	void CreateRsSetQuery(CString sQuery);	
	void AddParameter(int	iValue);
	void AddParameter(long nValue);
	void AddParameter(BOOL bValue, int nType );
	void AddParameter(COleDateTime dtValue);
	void AddParameter(CString sValue);	
	CMkParameter * AddOutPutParameter(long lValue);
	CMkParameter * AddOutPutParameter(int iValue);
	CMkRecordset* Excute();
	void ExcuteBinding(BOOL bRefresh = FALSE);
	void CreateComandSetQuery(CString sql);
	BOOL ExcuteCmd(BOOL bRefresh = FALSE);


	void RecordSetCloseRelease(CMkRecordset *pRs);
	BOOL IsRowSelectCheck(CString strMsg = "");

	// Virtual list
	//void GetItemMetrics (XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
	// 필터관련
	void Filter(CString strFilter, int nFilterCol = 0, int nTypeData = ALL_TYPE_COLUMN,  CString sReplaceData = "",BOOL bNotAllSearchWord = TRUE);
	void Filter2(CString strFilter, int nFilterCol, CString strFilter2, int nFilterCol2);
	BOOL m_bInsertSearchAll;
	void InsertSearchAllColumn(int nCol);
	SEARCH_ALL_COLUMN_DATA m_sac;

	void DeleteAllColumns();

};