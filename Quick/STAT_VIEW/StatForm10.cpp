// StatForm10.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "StatForm10.h"


// CStatForm10

IMPLEMENT_DYNCREATE(CStatForm10, CMyFormView)

CStatForm10::CStatForm10()
	: CMyFormView(CStatForm10::IDD)
{

}

CStatForm10::~CStatForm10()
{
}

void CStatForm10::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFromCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);

	DDX_Control(pDX, IDC_LIST_REPORT, m_lstReport);
}

BEGIN_MESSAGE_MAP(CStatForm10, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CStatForm10::OnBnClickedRefreshBtn)
END_MESSAGE_MAP()


// CStatForm10 진단입니다.

#ifdef _DEBUG
void CStatForm10::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStatForm10::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStatForm10 메시지 처리기입니다.

void CStatForm10::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_LIST_REPORT, sizingRightBottom);

	m_DateBtn.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_DateBtn.OnMenuWeek();

	m_lstReport.InsertColumn(0, "일자", LVCFMT_CENTER, 80);
	m_lstReport.InsertColumn(1, "총건수", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(2, "완료건수", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(3, "취소건수", LVCFMT_RIGHT, 70);
	m_lstReport.Populate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void CStatForm10::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CStatForm10::RefreshList()
{
	UpdateData(TRUE);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rcp_type_openapi_log");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	cmd.AddParameter(LF->GetCurBranchInfo()->bIntegrated);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);

	if(!rs.Execute(&cmd))
		return;

	m_lstReport.DeleteAllItems();

	CString strDate;
	long nCount, nCompleteCount;
	
	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("sDate", strDate);
		rs.GetFieldValue("nCount", nCount);
		rs.GetFieldValue("nCompleteCount", nCompleteCount);
		
		m_lstReport.InsertItem(i, strDate);
		m_lstReport.SetItemText(i, 1, LF->RemoveZero(LF->GetMyNumberFormat(nCount)));
		m_lstReport.SetItemText(i, 2, LF->RemoveZero(LF->GetMyNumberFormat(nCompleteCount)));
		m_lstReport.SetItemText(i, 3, LF->RemoveZero(LF->GetMyNumberFormat(nCount - nCompleteCount)));
		
		rs.MoveNext();
	}

	m_lstReport.Populate();
}