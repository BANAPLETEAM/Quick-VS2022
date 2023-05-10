// BranchSubBtn.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "BranchSubBtn.h"
#include "BranchSel.h"


// CBranchSubBtn

IMPLEMENT_DYNAMIC(CBranchSubBtn, CButton)

CBranchSubBtn::CBranchSubBtn()
{	
}

CBranchSubBtn::~CBranchSubBtn()
{
}


BEGIN_MESSAGE_MAP(CBranchSubBtn, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &CBranchSubBtn::OnBnClicked)
END_MESSAGE_MAP()



void CBranchSubBtn::OnBnClicked()
{
	m_pParent->CloseMainListDlg();
	m_pParent->OpenSubListDlg();
}
