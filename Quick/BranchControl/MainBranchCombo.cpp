// MainBranchCombo.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MainBranchCombo.h"
#include "MakeBranchCombo.h"


// CMainBranchCombo

IMPLEMENT_DYNAMIC(CMainBranchCombo, CComboBox)

CMainBranchCombo::CMainBranchCombo()
{	
	m_pMakeBranchCombo = NULL;
}

CMainBranchCombo::~CMainBranchCombo()
{
}


BEGIN_MESSAGE_MAP(CMainBranchCombo, CComboBox)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, &CMainBranchCombo::OnCbnSelchange)
END_MESSAGE_MAP()



// CMainBranchCombo 메시지 처리기입니다.



void CMainBranchCombo::OnCbnSelchange()
{
	m_pMakeBranchCombo->OnMainSelChange();	
}

void CMainBranchCombo::SetParent(CMakeBranchCombo *pWnd)
{
	m_pMakeBranchCombo = pWnd;	
}
