// ImageViewDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "ImageViewDlg.h"
#include "ImageHtmlView.h"


// CImageViewDlg ��ȭ �����Դϴ�.

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


// CImageViewDlg �޽��� ó�����Դϴ�.
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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}