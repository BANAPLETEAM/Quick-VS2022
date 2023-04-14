// EnterNotifyEdit.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EnterNotifyEdit.h"


// CEnterNotifyEdit

//IMPLEMENT_DYNAMIC(CEnterNotifyEdit, CFocusEditCtrl)
CEnterNotifyEdit::CEnterNotifyEdit()
{
}

CEnterNotifyEdit::~CEnterNotifyEdit()
{
} 


BEGIN_MESSAGE_MAP(CEnterNotifyEdit, CFocusEditCtrl)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CEnterNotifyEdit message handlers


void CEnterNotifyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar == VK_RETURN) {
		GetParent()->SendMessage(WM_ENTER_NOTIFY, GetDlgCtrlID(), 0L);
		return;
	}

	CFocusEditCtrl::OnChar(nChar, nRepCnt, nFlags);
}


