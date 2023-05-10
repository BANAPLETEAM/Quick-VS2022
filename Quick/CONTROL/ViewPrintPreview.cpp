// ViewPrintPreview.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ViewPrintPreview.h"
#include "DataBox.h"
#include "TaskFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BOOL CALLBACK _AfxMyPreviewCloseProc(CFrameWnd* pFrameWnd);

/////////////////////////////////////////////////////////////////////////////
// CWrapperView

IMPLEMENT_DYNCREATE(CWrapperView, CScrollView)

CWrapperView::CWrapperView()
{
	m_pFrameWnd = NULL;
	m_nMapMode = MM_TEXT; //default
}

CWrapperView::~CWrapperView()
{
}


BEGIN_MESSAGE_MAP(CWrapperView, CScrollView)
	//{{AFX_MSG_MAP(CWrapperView)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CWrapperView::OnDraw(CDC *pDC)
{
	if(pDC)
	{
	}
}
/////////////////////////////////////////////////////////////////////////////
// CWrapperView diagnostics

#ifdef _DEBUG
void CWrapperView::AssertValid() const
{
	CView::AssertValid();
}

void CWrapperView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWrapperView message handlers

BOOL CALLBACK _AfxMyPreviewCloseProc(CFrameWnd* pFrameWnd)
{
	ASSERT_VALID(pFrameWnd);

	CMyPreviewView* pView = (CMyPreviewView*) pFrameWnd->GetDlgItem(AFX_IDW_PANE_FIRST);
	ASSERT_KINDOF(CPreviewView, pView);

	pView->OnPreviewClose();
	return FALSE;
}

BOOL CWrapperView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWrapperView::OnFilePrintPreview(CFrameWnd *pFrame)
{
	// In derived classes, implement special window handling here
	// Be sure to Unhook Frame Window close if hooked.
	m_pFrameWnd = pFrame;

	// must not create this on the frame.  Must outlive this function
	CPrintPreviewState* pState = new CPrintPreviewState;
	pState->lpfnCloseProc = _AfxMyPreviewCloseProc;

	// DoPrintPreview's return value does not necessarily indicate that
	// Print preview succeeded or failed, but rather what actions are necessary
	// at this point.  If DoPrintPreview returns TRUE, it means that
	// OnEndPrintPreview will be (or has already been) called and the
	// pState structure will be/has been deleted.
	// If DoPrintPreview returns FALSE, it means that OnEndPrintPreview
	// WILL NOT be called and that cleanup, including deleting pState
	// must be done here.

	if (!DoPrintPreview(AFX_IDD_PREVIEW_TOOLBAR, this,
		RUNTIME_CLASS(CMyPreviewView), pState))
	{
		// In derived classes, reverse special window handling here for
		// Preview failure case

		TRACE0("Error: DoPrintPreview failed.\n");
		AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
		delete pState;      // preview failed to initialize, delete State now
	}
}

BOOL CWrapperView::DoPrintPreview(UINT nIDResource, CView* pPrintView,
								  CRuntimeClass* pPreviewViewClass, CPrintPreviewState* pState)
{
	ASSERT_VALID_IDR(nIDResource);
	ASSERT_VALID(pPrintView);
	ASSERT(pPreviewViewClass != NULL);
	ASSERT(pPreviewViewClass->IsDerivedFrom(RUNTIME_CLASS(CPreviewView)));
	ASSERT(pState != NULL);

	ASSERT(m_pFrameWnd != NULL);
	CFrameWnd* pParent = m_pFrameWnd; //STATIC_DOWNCAST(CFrameWnd, AfxGetMainWnd()); //
	ASSERT_VALID(pParent);

	CCreateContext context;
	context.m_pCurrentFrame = pParent;
	context.m_pCurrentDoc = GetDocument();
	context.m_pLastView = this;

	// Create the preview view object
	CMyPreviewView* pView = (CMyPreviewView*)pPreviewViewClass->CreateObject();
	if (pView == NULL)
	{
		TRACE0("Error: Failed to create preview view.\n");
		return FALSE;
	}
	ASSERT_KINDOF(CPreviewView, pView);
	pView->m_pPreviewState = pState;        // save pointer

	pParent->OnSetPreviewMode(TRUE, pState);    // Take over Frame Window

	// Create the toolbar from the dialog resource
	pView->m_pToolBar = new CDialogBar;
	if (!pView->m_pToolBar->Create(pParent, MAKEINTRESOURCE(nIDResource),
		CBRS_TOP, AFX_IDW_PREVIEW_BAR))
	{
		TRACE0("Error: Preview could not create toolbar dialog.\n");
		pParent->OnSetPreviewMode(FALSE, pState);   // restore Frame Window
		delete pView->m_pToolBar;       // not autodestruct yet
		pView->m_pToolBar = NULL;
		pView->m_pPreviewState = NULL;  // do not delete state structure
		delete pView;
		return FALSE;
	}
	pView->m_pToolBar->m_bAutoDelete = TRUE;    // automatic cleanup

	// Create the preview view as a child of the App Main Window.  This
	// is a sibling of this view if this is an SDI app.  This is NOT a sibling
	// if this is an MDI app.

	if (!pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0,0,0,0), pParent, AFX_IDW_PANE_FIRST, &context))
	{
		TRACE0("Error: couldn't create preview view for frame.\n");
		pParent->OnSetPreviewMode(FALSE, pState);   // restore Frame Window
		pView->m_pPreviewState = NULL;  // do not delete state structure
		delete pView;
		return FALSE;
	}

	// Preview window shown now

	pState->pViewActiveOld = pParent->GetActiveView();
	CWrapperView* pActiveView = (CWrapperView*)pParent->GetActiveFrame()->GetActiveView();
	if (pActiveView != NULL)
		pActiveView->OnActivateView(FALSE, pActiveView, pActiveView);

	if (!pView->SetPrintView(pPrintView))
	{
		pView->OnPreviewClose();
		return TRUE;            // signal that OnEndPrintPreview was called
	}

	pParent->SetActiveView(pView);  // set active view - even for MDI

	// update toolbar and redraw everything
	pView->m_pToolBar->SendMessage(WM_IDLEUPDATECMDUI, (WPARAM)TRUE);
	pParent->RecalcLayout();            // position and size everything
	pParent->UpdateWindow();

	return TRUE;
}

// OnEndPrintPreview is here for swap tuning reasons
//  (see viewprev.cpp for complete preview mode implementation)
void CWrapperView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo,
									 POINT, CMyPreviewView* pView)
{
	ASSERT_VALID(pDC);
	ASSERT_VALID(pView);
	ASSERT(m_pFrameWnd != NULL);

	if (pView->m_pPrintView != NULL)
		OnEndPrinting(pDC, pInfo);

	CFrameWnd* pParent = m_pFrameWnd;
	ASSERT_VALID(pParent);

	// restore the old main window
	pParent->OnSetPreviewMode(FALSE, pView->m_pPreviewState);

	// Force active view back to old one
	pParent->SetActiveView(pView->m_pPreviewState->pViewActiveOld);
	if (pParent != GetParentFrame())
		OnActivateView(TRUE, this, this);   // re-activate view in real frame
	pView->DestroyWindow();     // destroy preview view
	// C++ object will be deleted in PostNcDestroy

	// restore main frame layout and idle message
	pParent->RecalcLayout();
	pParent->SendMessage(WM_SETMESSAGESTRING, (WPARAM)AFX_IDS_IDLEMESSAGE, 0L);
	pParent->UpdateWindow();
}

void CWrapperView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CView::OnEndPrinting(pDC, pInfo);
}



//-----------------------------------------------------------------------------






IMPLEMENT_DYNCREATE(CMyPreviewView, CPreviewView)

CMyPreviewView::CMyPreviewView()
{
}

CMyPreviewView::~CMyPreviewView()
{
}

BEGIN_MESSAGE_MAP(CMyPreviewView, CPreviewView)
	//{{AFX_MSG_MAP(CMyPreviewView)
	ON_COMMAND(AFX_ID_PREVIEW_CLOSE, OnPreviewClose)
	ON_COMMAND(AFX_ID_PREVIEW_PRINT, OnPreviewPrint)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPreviewView drawing

void CMyPreviewView::OnDraw(CDC* pDC)
{
	CPreviewView::OnDraw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CMyPreviewView diagnostics

#ifdef _DEBUG
void CMyPreviewView::AssertValid() const
{

}

void CMyPreviewView::Dump(CDumpContext& dc) const
{

}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyPreviewView message handlers

void CMyPreviewView::OnActivateView(BOOL bActivate, CView* pView1, CView *pView2)
{
	CPreviewView::OnActivateView(bActivate, pView1, pView2);
}

void CMyPreviewView::OnPreviewClose()
{
	m_pToolBar->DestroyWindow();
	m_pToolBar = NULL;

	m_pPreviewInfo->m_nCurPage = m_nCurrentPage;
	((CWrapperView*)m_pOrigView)->OnEndPrintPreview(m_pPreviewDC, m_pPreviewInfo,
		CPoint(0, 0), this);
}

void CMyPreviewView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	// TODO: Add your specialized code here and/or call the base class

	CPreviewView::OnEndPrintPreview(pDC, pInfo, point, pView);
}

void CMyPreviewView::OnPreviewPrint()
{
	
	m_pPrintView->SendMessage(WM_COMMAND, ID_FILE_PRINT_DIRECT);
	//m_pPrintView->SendMessage(WM_COMMAND, ID_FILE_PRINT);
	OnPreviewClose();               // force close of Preview

	// cause print (can be overridden by catching the command)
	//CWnd* pMainWnd = AfxGetThread()->m_pMainWnd;
	//ASSERT_VALID(pMainWnd);
	//pMainWnd->SendMessage(WM_COMMAND, ID_FILE_PRINT);
}













//-----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// CViewPrintPreview

IMPLEMENT_DYNCREATE(CViewPrintPreview, CView)

CViewPrintPreview::CViewPrintPreview()
{
	
}

CViewPrintPreview::~CViewPrintPreview()
{
}


BEGIN_MESSAGE_MAP(CViewPrintPreview, CView)
	//{{AFX_MSG_MAP(CViewPrintPreview)
	
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewPrintPreview drawing

void CViewPrintPreview::OnDraw(CDC* pDC)
{
//	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CViewPrintPreview diagnostics

#ifdef _DEBUG
void CViewPrintPreview::AssertValid() const
{
	CView::AssertValid();
}

void CViewPrintPreview::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
// CViewPrintPreview message handlers






void CViewPrintPreview::OnFilePrintPreview(CTaskFrame *pFrame)
{

	CWrapperView::OnFilePrintPreview(pFrame);
}

void CViewPrintPreview::OnFilePrint()
{
	CView::OnFilePrint();
	
}


BOOL CViewPrintPreview::OnPreparePrinting(CPrintInfo* pInfo) 
{
	return DoPreparePrinting(pInfo);
}

void CViewPrintPreview::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	m_pDataBox->OnBeginPrinting(pDC,pInfo);
	
	CWrapperView::OnBeginPrinting(pDC,pInfo);
}

void CViewPrintPreview::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	m_pDataBox->OnPrint(pDC, pInfo);	
	CWrapperView::OnPrint(pDC,pInfo);
}

void CViewPrintPreview::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	m_pDataBox->OnEndPrinting(pDC, pInfo);	
	//CWrapperView::OnEndPrinting(pDC, pInfo);
}

void CViewPrintPreview::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	
	// Show the original frame
	
	m_pDataBox->m_bPrintPreview = FALSE;

	ASSERT_VALID(pDC);
	ASSERT_VALID(pView);

	CWrapperView::OnEndPrinting(pDC,pInfo);
	return;
	

}

BOOL CViewPrintPreview::PaginateTo(CDC* pDC, CPrintInfo* pInfo)
// attempts pagination to pInfo->m_nCurPage, TRUE == success
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);

	CRect rectSave = pInfo->m_rectDraw;
	UINT nPageSave = pInfo->m_nCurPage;
	ASSERT(nPageSave > 1);
	ASSERT(nPageSave >= (UINT)m_pDataBox->m_aPageStart.GetSize());
	VERIFY(pDC->SaveDC() != 0);
	pDC->IntersectClipRect(0, 0, 0, 0);
	pInfo->m_nCurPage = (UINT)m_pDataBox->m_aPageStart.GetSize();
	while (pInfo->m_nCurPage < nPageSave)
	{
		ASSERT(pInfo->m_nCurPage == (UINT)m_pDataBox->m_aPageStart.GetSize());
		OnPrepareDC(pDC, pInfo);
		ASSERT(pInfo->m_bContinuePrinting);
		pInfo->m_rectDraw.SetRect(0, 0,
			pDC->GetDeviceCaps(HORZRES), pDC->GetDeviceCaps(VERTRES));
		pDC->DPtoLP(&pInfo->m_rectDraw);
		OnPrint(pDC, pInfo);
		if (pInfo->m_nCurPage == (UINT)m_pDataBox->m_aPageStart.GetSize())
			break;
		++pInfo->m_nCurPage;
	}
	BOOL bResult = pInfo->m_nCurPage == nPageSave;
	pDC->RestoreDC(-1);
	pInfo->m_nCurPage = nPageSave;
	pInfo->m_rectDraw = rectSave;
	ASSERT_VALID(this);
	return bResult;
}

void CViewPrintPreview::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	if(pInfo == NULL)
	{
		//((CTaskFrame*)GetParent())->m_pS>GetActiveView() = this;
		return;
	}

	//ASSERT(pInfo != NULL);  // overriding OnPaint -- never get this.

	if (pInfo->m_nCurPage > (UINT)m_pDataBox->m_aPageStart.GetSize() &&
		!PaginateTo(pDC, pInfo))
	{
		// can't paginate to that page, thus cannot print it.
		pInfo->m_bContinuePrinting = FALSE;
	}
	pDC->SetMapMode(MM_ANISOTROPIC);

	pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX),
		pDC->GetDeviceCaps(LOGPIXELSY));

	pDC->SetWindowExt(100, 100);

	// ptOrg is in logical coordinates
	pDC->OffsetWindowOrg(0, 0);
}

