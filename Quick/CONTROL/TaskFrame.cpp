// TaskFrame.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "TaskFrame.h"


// CTaskFrame



static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
		ID_INDICATOR_CAPS,
		ID_INDICATOR_NUM,
		ID_INDICATOR_SCRL,
};

#define COLUMN_TYPE             0
#define COLUMN_IMPORTANCE       1
#define COLUMN_ATTACHMENT       2
#define COLUMN_STATUS           3
#define COLUMN_SUBJECT          4
#define COLUMN_DUE_DATE         5
#define COLUMN_COMPLETE         6
#define COLUMN_CATEGORIES       7

IMPLEMENT_DYNCREATE(CTaskFrame, CFrameWnd)

CTaskFrame::CTaskFrame()
{

}
CTaskFrame::CTaskFrame(CXTPListCtrl2 *pDataBox)
{
	m_pParentWnd =  pDataBox;
	
}

CTaskFrame::~CTaskFrame()
{
}


BEGIN_MESSAGE_MAP(CTaskFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CTaskFrame 메시지 처리기입니다.
#define  ID_FILE_PRINT 10002
#define  ID_FILE_PRINT_PREVIEW 10003

int CTaskFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}


#ifdef _XTP_INCLUDE_COMMANDBARS

	if (!InitCommandBars())
		return -1;

	CMenu menu;
	//menu.CreateObject();	
	VERIFY(menu.CreatePopupMenu());
	
	
	menu.AppendMenu(MF_STRING, ID_FILE_PRINT, "프린트");
	menu.AppendMenu(MF_STRING, ID_FILE_PRINT_PREVIEW, "미리보기");
	
	CXTPCommandBars* pCommandBars = GetCommandBars();
 	pCommandBars->SetMenu("메뉴바", IDR_QFORMVIEW_TMPL   );
	pCommandBars->GetMenuBar()->EnableAutomation();
	//CWnd *pWnd = pCommandBars->GetMenuBar()->Set
	//pWnd->EnableWindow(TRUE);


	CXTPMenuBar *pMenuBar = pCommandBars->GetMenuBar();
	pMenuBar->SetMenu(&menu);	
	
	pMenuBar->RefreshMenu();
	

#endif

	return 0;
}

void CTaskFrame::OnDestroy()
{
	//((CMyXTPGridView*)m_pOwnerView)->m_pTaskFrame = NULL;

	//((CK2ReportView*)m_pOwnerView)->m_pTaskFrame = NULL;
	CFrameWnd::OnDestroy();
}