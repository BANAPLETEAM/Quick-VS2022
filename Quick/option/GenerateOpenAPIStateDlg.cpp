// EtcDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Resource.h"
#include "GenerateOpenAPIStateDlg.h"
#include "GeneralOpenAPIRegisterDlg.h"


// CGenerateOpenAPIStateDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGenerateOpenAPIStateDlg, CMyDialog)

CGenerateOpenAPIStateDlg::CGenerateOpenAPIStateDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CGenerateOpenAPIStateDlg::IDD, pParent)
{
}

CGenerateOpenAPIStateDlg::~CGenerateOpenAPIStateDlg()
{
}

void CGenerateOpenAPIStateDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_CTRL, m_lstReport);
}


BEGIN_MESSAGE_MAP(CGenerateOpenAPIStateDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_ADD_BTN, OnBnClickedAddBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_CTRL, OnReportItemDbClick)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CGenerateOpenAPIStateDlg 메시지 처리기입니다.

void CGenerateOpenAPIStateDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CGenerateOpenAPIStateDlg::RefreshList()
{
	m_lstReport.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_openapi_register");
	cmd.AddParameter(m_ci.GetShareCode1());

	if(!rs.Execute(&cmd))
		return;

	long nIndex, nCompany, nState;
	CString strBizNumber, strMainTel;
	COleDateTime dtUserRegister, dtConfirm;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nIndex", nIndex);
		rs.GetFieldValue("nState", nState); 
		rs.GetFieldValue("nCompany", nCompany); 
		rs.GetFieldValue("sBizNumber", strBizNumber);
		rs.GetFieldValue("dtUserRegister", dtUserRegister);
		rs.GetFieldValue("dtConfirm", dtConfirm);

		if(nCompany == 0)
			m_lstReport.InsertItem(i, "");
		else
			m_lstReport.InsertItem(i, m_ci.GetBranchName(nCompany));

		CString strTemp = "";
		if(nState == 1) strTemp = "신청중";
		else if(nState == 2) strTemp = "등록";

		m_lstReport.SetItemText(i, 1, strTemp);
		m_lstReport.SetItemText(i, 2, strBizNumber);
		m_lstReport.SetItemText(i, 3, dtUserRegister.Format("%y-%m-%d %H:%M"));

		if(dtConfirm.m_status != 2)
			m_lstReport.SetItemText(i, 4, dtConfirm.Format("%y-%m-%d %H:%M"));
		else
			m_lstReport.SetItemText(i, 4, "");

		m_lstReport.SetItemText(i, 5, m_ci.GetShareCompanyPhone(nCompany));
		
		m_lstReport.SetItemLong(i, nIndex);

		rs.MoveNext();		
	}

	m_lstReport.Populate();
}

BOOL CGenerateOpenAPIStateDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_lstReport.InsertColumn(0, "API 등록지사", LVCFMT_LEFT, 120);
	m_lstReport.InsertColumn(1, "상태", LVCFMT_LEFT, 50);
	m_lstReport.InsertColumn(2, "사업자등록증", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(3, "신청일", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(4, "API 등록일", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(5, "대표번호", LVCFMT_LEFT, 90);
	
	m_lstReport.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CGenerateOpenAPIStateDlg::OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	CXTPGridRecord *pRecord = GetFirstSelectRecord();

	if(pRecord == NULL)
		return;

	long nIndex = m_lstReport.GetItemLong(pRecord);

	CGenerateOpenAPIRegisterDlg dlg;
	dlg.m_nIndex =	nIndex;

	if(dlg.DoModal() == IDOK)
		RefreshList();
}

void CGenerateOpenAPIStateDlg::OnBnClickedAddBtn()
{
	CGenerateOpenAPIRegisterDlg dlg;
	dlg.m_nIndex = 0;

	if(dlg.DoModal() == IDOK)
		RefreshList();
}
void CGenerateOpenAPIStateDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(m_lstReport.GetSafeHwnd() != NULL)
	{
		CRect rc;
		m_lstReport.GetWindowRect(rc);
		ScreenToClient(rc);

		rc.right = cx - 5;
		rc.bottom = cy - 5;

		m_lstReport.MoveWindow(rc, TRUE);
	}
}

CXTPGridRecord* CGenerateOpenAPIStateDlg::GetFirstSelectRecord()
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL) return NULL;
	if(pRows->GetCount() == 0) return NULL;

	return pRows->GetAt(0)->GetRecord();
}