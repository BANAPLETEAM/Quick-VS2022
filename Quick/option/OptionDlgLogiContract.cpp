// OptionDlgCID.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "OptionDlgLogiContract.h"
#include "MainOptionDlg2011.h"
// COptionDlgLogiContract

UINT _nControl[] = {IDC_STATIC1, IDC_STATIC2, IDC_STATIC3, IDC_STATIC4, IDC_STATIC5,
	IDC_STATIC6, IDC_STATIC7, IDC_STATIC8, IDC_CONTRACT_COMPANY_NAME_EDIT, IDC_CONTRACT_COMPANY_BIZ_NO_EDIT,
	IDC_CONTRACT_COMPANY_OWNER_EDIT, IDC_CONTRACT_COMPANY_TEL_EDIT, IDC_CONTRACT_COMPANY_LOCATION_EDIT, IDC_STATIC9};

IMPLEMENT_DYNCREATE(COptionDlgLogiContract, CMyFormView)

COptionDlgLogiContract::COptionDlgLogiContract()
	: CMyFormView(COptionDlgLogiContract::IDD)
{
}

COptionDlgLogiContract::~COptionDlgLogiContract()
{
}

void COptionDlgLogiContract::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_CONTRACT_COMPANY_NAME_EDIT, m_strContractCompanyName);
	DDX_Text(pDX, IDC_CONTRACT_COMPANY_BIZ_NO_EDIT, m_strContractBizNo);
	DDX_Text(pDX, IDC_CONTRACT_COMPANY_OWNER_EDIT, m_strContractCompanyOwner);
	DDX_Text(pDX, IDC_CONTRACT_COMPANY_TEL_EDIT, m_strContractCompanyTel);
	DDX_Text(pDX, IDC_CONTRACT_COMPANY_LOCATION_EDIT, m_strContractCompanyLocation);
}
 
BEGIN_MESSAGE_MAP(COptionDlgLogiContract, CMyFormView)
END_MESSAGE_MAP()


// COptionDlgLogiContract 진단입니다.

#ifdef _DEBUG
void COptionDlgLogiContract::AssertValid() const
{
	CMyFormView::AssertValid();
}

void COptionDlgLogiContract::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// COptionDlgLogiContract 메시지 처리기입니다.
void COptionDlgLogiContract::OnInitialUpdate()
{	
	CMyFormView::OnInitialUpdate();


}

void COptionDlgLogiContract::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CMyFormView::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

int COptionDlgLogiContract::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return TRUE;
//	return CMyFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void COptionDlgLogiContract::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CMyFormView::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void COptionDlgLogiContract::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CMyFormView::OnVScroll(nSBCode, nPos, pScrollBar);
	//if(nSBCode == SB_ENDSCROLL)
	//	Invalidate(TRUE); 
}

BOOL COptionDlgLogiContract::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CMyFormView::OnMouseWheel(nFlags, zDelta, pt);

	//if(nFlags == SB_ENDSCROLL)
	//	Invalidate(TRUE);
	return TRUE;
}

void COptionDlgLogiContract::OnPaint()
{ 
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CMyFormView::OnPaint()을(를) 호출하지 마십시오.
}

void COptionDlgLogiContract::RefreshData(CMkRecordset *pRs)
{
	if(pRs->GetRecordCount() == 0)
		return;

	pRs->GetFieldValue("sContractCompanyName", m_strContractCompanyName);
	pRs->GetFieldValue("sContractCompanyBizNo", m_strContractBizNo);
	pRs->GetFieldValue("sContractCompanyOwner", m_strContractCompanyOwner);
	pRs->GetFieldValue("sContractCompanyTel", m_strContractCompanyTel);
	pRs->GetFieldValue("company_location", m_strContractCompanyLocation);	
	

	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent();

	BOOL bRcpIntMode1 = m_ci.GetRcpIntMode1(pDlg->GetSelCompanyCode());
	

	long nCount = sizeof(_nControl) / sizeof(long);

	for(int i=0; i<nCount; i++)
		GetDlgItem(_nControl[i])->ShowWindow(bRcpIntMode1);
	
	GetDlgItem(IDC_STATIC_TITLE)->ShowWindow(bRcpIntMode1);
	GetDlgItem(IDC_STATIC_TITLE2)->ShowWindow(!bRcpIntMode1);

	UpdateData(FALSE);
}
