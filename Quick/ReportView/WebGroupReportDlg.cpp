// WebGroupReportDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "WebGroupReportDlg.h"
#include "WebGroupReportDetailDlg.h"

// CWebGroupReportDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CWebGroupReportDlg, CMyDialog)
CWebGroupReportDlg::CWebGroupReportDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CWebGroupReportDlg::IDD, pParent)
{
	m_nCount = 0;
}

CWebGroupReportDlg::~CWebGroupReportDlg()
{
}

void CWebGroupReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWebGroupReportDlg, CMyDialog)

	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()



BOOL CWebGroupReportDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	

	CRect rtSTATIC_OPTION;
	this->GetDlgItem(IDC_DRAW_STATIC)->GetWindowRect(rtSTATIC_OPTION);
	this->ScreenToClient(rtSTATIC_OPTION);
	this->GetDlgItem(IDC_DRAW_STATIC)->ShowWindow(SW_HIDE);

	LU->CreateFormViewTabControl(this, &m_wndTabControl, rtSTATIC_OPTION);

	CString strName;

	//���� �ٲ�� �ȵ�
	for(int i=0; i<m_nCount; i++)
	{
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CWebGroupReportDetailDlg), m_strTitle.GetAt(i), 0);
	}
	
	for(int i=0; i<m_nCount; i++)
	{
		CXTPTabManagerItem* pXTPTabManagerItem =  m_wndTabControl.GetItem(i);

		CWnd* pWnd =  FromHandle(pXTPTabManagerItem->GetHandle());
		CWebGroupReportDetailDlg *pDlg = (CWebGroupReportDetailDlg*)pWnd;

		pDlg->m_nID = _ttoi(m_strID.GetAt(i));
		pDlg->m_nGNo = _ttoi(m_strGNo.GetAt(i));
		pDlg->m_strTitle = m_strTitle.GetAt(i);

		pDlg->InitControl();
		pDlg->Refresh();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

int CWebGroupReportDlg::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return 0;
	return CMyDialog::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CWebGroupReportDlg::OnCancel()
{
	CMyDialog::OnCancel();
}
