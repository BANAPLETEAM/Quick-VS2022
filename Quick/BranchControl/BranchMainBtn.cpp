
#include "stdafx.h"
#include "resource.h"
#include "BranchMainBtn.h"
#include "BranchSel.h"

// CBranchMainBtn

IMPLEMENT_DYNAMIC(CBranchMainBtn, CButton)

CBranchMainBtn::CBranchMainBtn()
{	
}

CBranchMainBtn::~CBranchMainBtn()
{
}


BEGIN_MESSAGE_MAP(CBranchMainBtn, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &CBranchMainBtn::OnBnClicked)
END_MESSAGE_MAP()



void CBranchMainBtn::OnBnClicked()
{
	m_pParent->OpenMainListDlg();
}
