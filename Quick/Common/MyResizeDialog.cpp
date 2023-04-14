// MyResizeDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MyResizeDialog.h"


// CMyResizeDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMyResizeDialog, CXTResizeDialog)

CMyResizeDialog::CMyResizeDialog(CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CMyResizeDialog::IDD, pParent)
{
	m_bCreatedAsModaless = FALSE;
}

CMyResizeDialog::CMyResizeDialog(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(nIDTemplate, pParent)
{
	m_bCreatedAsModaless = FALSE;
	m_nIDTemplate = nIDTemplate;
	m_bModalessAutoDelete = FALSE;
	m_pOriPointer = NULL;
}

CMyResizeDialog::~CMyResizeDialog()
{
}

void CMyResizeDialog::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyResizeDialog, CXTResizeDialog)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMyResizeDialog 메시지 처리기입니다.

BOOL CMyResizeDialog::OnInitDialog()
{
	SetFlag(xtResizeNoSizeIcon);
	g_bana_log->Print("\nCMyResizeDialog OPEN = ### %s ###\n\n",  GetRuntimeClass()->m_lpszClassName);
	CMyDialog::m_strLastDialog = GetRuntimeClass()->m_lpszClassName;
	CXTResizeDialog::OnInitDialog();
	return TRUE;
}

void CMyResizeDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	LF->FillBackground(&dc, this);
}

HBRUSH CMyResizeDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CXTResizeDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	HBRUSH hUserBrush;
	if(pWnd != this)
		if(LF->OnMyCtlColor(pDC, pWnd, nCtlColor, hUserBrush))
			return hUserBrush;
		

	return hbr;
}

void CMyResizeDialog::OnOK()
{
	CXTResizeDialog::OnOK();
	DeleteModaless();
}

void CMyResizeDialog::OnCancel()
{
	CXTResizeDialog::OnCancel();	
	DeleteModaless();
}

void CMyResizeDialog::OnClose()
{
	CXTResizeDialog::OnClose();
	DeleteModaless();
}

void CMyResizeDialog::DeleteModaless()
{
	if(m_bCreatedAsModaless && m_bModalessAutoDelete)
	{
		if(m_pOriPointer)
			(*m_pOriPointer) = NULL;
		delete this;
	}
}
