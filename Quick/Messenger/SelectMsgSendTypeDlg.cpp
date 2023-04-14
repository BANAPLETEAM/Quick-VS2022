// SelectMsgSendTypeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "SelectMsgSendTypeDlg.h"


// CSelectMsgSendTypeDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSelectMsgSendTypeDlg, CMyDialog)

CSelectMsgSendTypeDlg::CSelectMsgSendTypeDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSelectMsgSendTypeDlg::IDD, pParent)
{
	m_nSelectedType = -1;
}

CSelectMsgSendTypeDlg::~CSelectMsgSendTypeDlg()
{
}

void CSelectMsgSendTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_CTRL, m_lstSelect);
}


BEGIN_MESSAGE_MAP(CSelectMsgSendTypeDlg, CMyDialog)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_CTRL, OnReportItemClick)
END_MESSAGE_MAP()


// CSelectMsgSendTypeDlg �޽��� ó�����Դϴ�.

BOOL CSelectMsgSendTypeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	
	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetWindowText(m_strTitle);

	m_lstSelect.InsertColumn(0,"",LVCFMT_LEFT, 20);
	m_lstSelect.InsertColumn(1,"",LVCFMT_LEFT, 120);
	m_lstSelect.InsertColumn(2,"",LVCFMT_LEFT, 300);
	m_lstSelect.GetPaintManager()->m_bHideSelection = TRUE;
	m_lstSelect.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_lstSelect.GetReportHeader()->AllowColumnSort(FALSE);
	m_lstSelect.GetReportHeader()->AllowColumnResize(FALSE);
	m_lstSelect.GetReportHeader()->AllowColumnReorder(FALSE);
	m_lstSelect.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstSelect.ShowHeader(FALSE);
	//m_lstSelect.ShowCountDisplay(FALSE);
	
	int nItem = 0;
	m_lstSelect.InsertItem(nItem, "1");
	m_lstSelect.SetItemText(nItem, 1, "�˻��� ���");
	m_lstSelect.SetItemText(nItem++, 2, "�Ʒ��� ����Ʈ�� ��Ÿ�� �ִ� ���(Ÿ����������)");

	m_lstSelect.InsertItem(nItem, "2");
	m_lstSelect.SetItemText(nItem, 1, "���õ� ���");
	m_lstSelect.SetItemText(nItem++, 2, "�Ʒ��� ����Ʈ���� ���õǾ� �ִ� ���(�������ð���)");

	m_lstSelect.InsertItem(nItem, "3");
	m_lstSelect.SetItemText(nItem, 1, "�������� ��ü�޽���");
	m_lstSelect.SetItemText(nItem++, 2, "��Ʈ���� ǥ�õǾ��� ��� ������� ���");

	m_lstSelect.InsertItem(nItem, "4");
	m_lstSelect.SetItemText(nItem, 1, "�������� ��ü�޽���");
	m_lstSelect.SetItemText(nItem++, 2, "��Ʈ���� �ֻ�ܿ� �ִ� ������ ���");

	m_lstSelect.Populate();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CSelectMsgSendTypeDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	if(pItemNotify->pRow->GetIndex() >= 0)
	{
		m_nSelectedType = pItemNotify->pRow->GetIndex(); 
		OnOK();
	}
}