// SelectMsgSendTypeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SelectMsgSendTypeDlg.h"


// CSelectMsgSendTypeDlg 대화 상자입니다.

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


// CSelectMsgSendTypeDlg 메시지 처리기입니다.

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
	m_lstSelect.SetItemText(nItem, 1, "검색된 멤버");
	m_lstSelect.SetItemText(nItem++, 2, "아래의 리스트에 나타나 있는 멤버(타사직원제외)");

	m_lstSelect.InsertItem(nItem, "2");
	m_lstSelect.SetItemText(nItem, 1, "선택된 멤버");
	m_lstSelect.SetItemText(nItem++, 2, "아래의 리스트에서 선택되어 있는 멤버(복수선택가능)");

	m_lstSelect.InsertItem(nItem, "3");
	m_lstSelect.SetItemText(nItem, 1, "지사포함 전체메시지");
	m_lstSelect.SetItemText(nItem++, 2, "네트웍에 표시되어진 모든 지사들의 멤버");

	m_lstSelect.InsertItem(nItem, "4");
	m_lstSelect.SetItemText(nItem, 1, "지사제외 전체메시지");
	m_lstSelect.SetItemText(nItem++, 2, "네트웍의 최상단에 있는 메인의 멤버");

	m_lstSelect.Populate();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
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