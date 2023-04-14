// CustomerDlgSub3.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "CustomerDlgSub3.h"
#include "CustomerDlg.h"


// CCustomerDlgSub3

IMPLEMENT_DYNCREATE(CCustomerDlgSub3, CMyFormView)

CCustomerDlgSub3::CCustomerDlgSub3()
	: CMyFormView(CCustomerDlgSub3::IDD)
{
	m_pCustomerDlg = NULL;
}

CCustomerDlgSub3::~CCustomerDlgSub3()
{
}

void CCustomerDlgSub3::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_P_BIZ_NO_EDIT, m_edtPBizNo);
	DDX_Control(pDX, IDC_P_BIZ_ADDRESS_EDIT, m_edtPBizAddress);
	DDX_Control(pDX, IDC_P_BIZ_CORP_NAME_EDIT, m_edtPBizCorpName);
	DDX_Control(pDX, IDC_P_BIZ_NAME_EDIT, m_edtPBizName);
	DDX_Control(pDX, IDC_P_BIZ_TYPE1_EDIT, m_edtPBizType1);
	DDX_Control(pDX, IDC_P_BIZ_TYPE2_EDIT, m_edtPBizType2);
}

BEGIN_MESSAGE_MAP(CCustomerDlgSub3, CMyFormView)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCustomerDlgSub3 진단입니다.

#ifdef _DEBUG
void CCustomerDlgSub3::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCustomerDlgSub3::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CCustomerDlgSub3::RefreshDlg()
{
	SetTimer(0, 500, NULL);
}

BOOL CCustomerDlgSub3::UpdatePBizInfo()
{
	CMkCommand cmd(m_pMkDb, "update_customer_print_info");
	cmd.AddParameter(m_pCustomerDlg->m_nCNo);
	cmd.AddParameter(m_pCustomerDlg->m_nCompanyCode);
	cmd.AddParameter(::GetStringFromEdit(&m_edtPBizNo));
	cmd.AddParameter(::GetStringFromEdit(&m_edtPBizAddress));
	cmd.AddParameter(::GetStringFromEdit(&m_edtPBizCorpName));
	cmd.AddParameter(::GetStringFromEdit(&m_edtPBizName));
	cmd.AddParameter(::GetStringFromEdit(&m_edtPBizType1));
	cmd.AddParameter(::GetStringFromEdit(&m_edtPBizType2));

	return cmd.Execute();
}

void CCustomerDlgSub3::RefreshDlgSub()
{
	BOOL bHasData = FALSE;

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_customer_print_info");
	cmd.AddParameter(m_pCustomerDlg->m_nCNo);

	if(!rs.Execute(&cmd))
		return;

	CString strPBizNo = "", strPBizAddress = "", strPBizCorpName = "", strPBizName = "", strPBizType1 = "", strPBizType2 = "";

	if(rs.GetRecordCount() > 0)
	{
		rs.GetFieldValue("sPBizNo", strPBizNo);
		rs.GetFieldValue("sPBizAddress", strPBizAddress);
		rs.GetFieldValue("sPBizCorpName", strPBizCorpName);
		rs.GetFieldValue("sPBizName", strPBizName);
		rs.GetFieldValue("sPBizType1", strPBizType1);
		rs.GetFieldValue("sPBizType2", strPBizType2);		
	}

	m_edtPBizNo.SetWindowText(strPBizNo);
	m_edtPBizAddress.SetWindowText(strPBizAddress);
	m_edtPBizCorpName.SetWindowText(strPBizCorpName);
	m_edtPBizName.SetWindowText(strPBizName);
	m_edtPBizType1.SetWindowText(strPBizType1);
	m_edtPBizType2.SetWindowText(strPBizType2);	
}

// CCustomerDlgSub3 메시지 처리기입니다.

void CCustomerDlgSub3::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 0)
	{
		KillTimer(0);
		RefreshDlgSub();
	}
	
	CMyFormView::OnTimer(nIDEvent);
}
