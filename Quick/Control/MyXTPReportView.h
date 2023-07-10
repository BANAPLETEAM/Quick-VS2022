
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define   XTP_ID_REPORT_CONTROL3  100

class   CK2ReportView : public CView 
{
	DECLARE_DYNCREATE(CK2ReportView)
protected:

	
	CK2ReportView();
	
public:

	CXTPListCtrl2&  GetDataCtrl();	
	CXTPGridPaintManager* GetPaintManager();


protected:

	
	~CK2ReportView();

protected:

	virtual long PrintPage (CDC* pDC, CPrintInfo* pInfo, CRect rcPage, long nIndexStart);	
	virtual void PrintHeader(CDC* pDC, CRect rcHeader);
	virtual int PrintRows(CDC* pDC, CRect rcRows, long nIndexStart);
	virtual void PrintRow(CDC* pDC, CXTPGridRow* pRow, CRect rcRow);
	virtual void PrintFooter(CDC* pDC, CPrintInfo* pInfo, CRect rcFooter);
	int GetColumnWidth(CXTPGridColumn* pColumn, int nTotalWidth);

protected:


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	DECLARE_MESSAGE_MAP()

	
	virtual BOOL PaginateTo(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

	
	

	/*virtual void OnActivateView(BOOL, CView*, CView*);
	virtual void OnActivateFrame(UINT, CFrameWnd*);*/
	BOOL SaveFocusControl();    // updates m_hWndFocus
	HWND m_hWndFocus; 
	void SetPaintManager(CXTPGridPaintManager *pManager);

	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnPaint();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	
	CXTPListCtrl2 m_Data;  // Child report control window.
	
protected:
	

	CUIntArray m_aPageStart;        // Printed indexes.
public:
	void PrintPreview();

};



