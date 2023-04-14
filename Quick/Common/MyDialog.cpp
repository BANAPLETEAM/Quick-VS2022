// MyDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MyDialog.h"


CString CMyDialog::m_strLastDialog;


// CMyDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMyDialog, CDialog)

CMyDialog::CMyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDialog::IDD, pParent)
{
	m_bPainted = FALSE;
	m_bCreatedAsModaless = FALSE;
}


CMyDialog::CMyDialog(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{
	m_bPainted = FALSE;
	m_bCreatedAsModaless = FALSE;
	m_nIDTemplate = nIDTemplate;
	m_bModalessAutoDelete = FALSE;
	m_pOriPointer = NULL;
}

CMyDialog::~CMyDialog()
{
	m_bCreatedAsModaless = FALSE;
	m_bModalessAutoDelete = FALSE;
	m_pOriPointer = NULL;
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMyDialog 메시지 처리기입니다.
BOOL CMyDialog::OnInitDialog()
{	m_clrTop = COLOR_DEFAULT_TOP_WND;
	m_clrBottom = COLOR_DEFAULT_DOWN_WND;

	g_bana_log->Print("\nCMyDialog OPEN = ### %s ###\n\n",  GetRuntimeClass()->m_lpszClassName);
	CMyDialog::m_strLastDialog = GetRuntimeClass()->m_lpszClassName;
	CDialog::OnInitDialog();
/*
	CWnd *pWnd = GetWindow(GW_CHILD);
	while(pWnd != NULL && pWnd->GetSafeHwnd() && pWnd->GetDlgCtrlID() != 0)
	{
		g_bana_log->Print("%d\n", pWnd->GetDlgCtrlID());
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}
*/
	return TRUE;
}

void CMyDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	LF->FillBackground(&dc, this, m_clrTop, m_clrBottom);
	m_bPainted = TRUE;
}

HBRUSH CMyDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	HBRUSH hUserBrush;
	
	if(pWnd != this)
		if(LF->OnMyCtlColor(pDC, pWnd, nCtlColor, hUserBrush))
			return hUserBrush;
			

	return hbr;
}

void CMyDialog::SetBottomColor(COLORREF clr)
{
	m_clrBottom = clr;
	Invalidate(TRUE);
}


void CMyDialog::OnOK()
{
	CDialog::OnOK();
	DeleteModaless();
}

void CMyDialog::OnCancel()
{
	CDialog::OnCancel();	
	DeleteModaless();
}

void CMyDialog::OnClose()
{
	CDialog::OnClose();
	DeleteModaless();
}

void CMyDialog::DeleteModaless()
{
	if(m_bCreatedAsModaless && m_bModalessAutoDelete)
	{
		if(m_pOriPointer)
			(*m_pOriPointer) = NULL;
		delete this;
	}
}