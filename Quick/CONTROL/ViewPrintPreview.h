#pragma once


// CViewPrintPreview ºäÀÔ´Ï´Ù.

#include "TaskFrame.h"


#if !defined(AFX_VIEWPRINTPREVIEW_H__137FC880_1607_11D3_9317_8F51A5F9742F__INCLUDED_)
#define AFX_VIEWPRINTPREVIEW_H__137FC880_1607_11D3_9317_8F51A5F9742F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ViewPrintPreview.h : header file
//





#include <afxpriv.h>

/////////////////////////////////////////////////////////////////////////////
// CMyPreviewView view

class CMyPreviewView : public CPreviewView
{
protected:
	CMyPreviewView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyPreviewView)

	// Attributes
public:

	// Operations
public:
	friend class CWrapperView;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPreviewView)
protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	//}}AFX_VIRTUAL

	// Implementation
protected:
	virtual ~CMyPreviewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual void OnActivateView(BOOL bActivate,
		CView* pActivateView, CView* pDeactiveView);

	// Generated message map functions
	//{{AFX_MSG(CMyPreviewView)
	afx_msg void OnPreviewClose();
	afx_msg void OnPreviewPrint();
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	friend BOOL CALLBACK _AfxMyPreviewCloseProc(CFrameWnd* pFrameWnd);

	DECLARE_MESSAGE_MAP()
};


class CWrapperView : public CScrollView
{
protected:
	DECLARE_DYNCREATE(CWrapperView)

	CFrameWnd *m_pFrameWnd;

	// Attributes
public:

	// Operations
public:
	CWrapperView();
	virtual ~CWrapperView();

	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	void OnFilePrintPreview(CFrameWnd *pFrame);

	BOOL DoPrintPreview(UINT nIDResource, CView* pPrintView,
		CRuntimeClass* pPreviewViewClass, CPrintPreviewState* pState);

	void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo,
		POINT, CMyPreviewView* pView);
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWrapperView)
protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

	// Implementation
protected:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CWrapperView)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CDataBox;

/////////////////////////////////////////////////////////////////////////////
// CViewPrintPreview view


class CViewPrintPreview : public CWrapperView
{
protected:
	CViewPrintPreview();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewPrintPreview)

	// Attributes
public:
	
	CDataBox	*m_pDataBox;
	

	// Operations
public:
	
	virtual void OnFilePrintPreview(CTaskFrame *pFrame);
	void OnFilePrint();
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewPrintPreview)
protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);

	void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);
	BOOL PaginateTo(CDC* pDC, CPrintInfo* pInfo);
	
	//}}AFX_VIRTUAL

	

	// Implementation
protected:
	virtual ~CViewPrintPreview();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewPrintPreview)
	
	//}}AFX_MSG
	friend BOOL CALLBACK _AfxMyPreviewCloseProc(CFrameWnd* pFrameWnd);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWPRINTPREVIEW_H__137FC880_1607_11D3_9317_8F51A5F9742F__INCLUDED_)

