// ImageViewDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "ImageViewDlg.h"
#include "ImageHtmlView.h"


// CImageViewDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CImageViewDlg, CMyDialog)

CImageViewDlg::CImageViewDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CImageViewDlg::IDD, pParent)
{
	m_pView = NULL;
}

CImageViewDlg::~CImageViewDlg()
{
}

void CImageViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CImageViewDlg, CMyDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CImageViewDlg 메시지 처리기입니다.
BOOL CImageViewDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	//CenterWindow();

	m_context.m_pNewViewClass = RUNTIME_CLASS(CImageHtmlView);
	m_pView = (CImageHtmlView*)((CFrameWnd*)this)->CreateView(&m_context);
	ASSERT(m_pView);

	CRect rc;
	GetWindowRect(rc);	ScreenToClient(rc);

	rc.top += 20;

	m_pView->m_strUrl = m_strUrl;
	m_pView->OnInitialUpdate();
	m_pView->ShowWindow(SW_NORMAL);
	m_pView->MoveWindow(&rc);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CImageViewDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(m_pView)
	{
		CRect rc;
		GetWindowRect(rc);	ScreenToClient(rc);
		rc.top += 20;

		m_pView->MoveWindow(&rc);
	}

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}