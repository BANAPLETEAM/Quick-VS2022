// PSListCtrl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "PSListCtrl.h"


// CPSListCtrl

//IMPLEMENT_DYNAMIC(CPSListCtrl, gxListCtrl)
CPSListCtrl::CPSListCtrl()
{
	m_bDirty = FALSE;
}

CPSListCtrl::~CPSListCtrl()
{
}


BEGIN_MESSAGE_MAP(CPSListCtrl, gxListCtrl)
END_MESSAGE_MAP()



// CPSListCtrl 메시지 처리기입니다.

BOOL CPSListCtrl::EndLabelEdit(LV_ITEM *plvItem)
{
	if(plvItem->iSubItem == 2)
	{
		if(!IsStringDigit(CString(plvItem->pszText)))
		{
			SetItemText(plvItem->iItem, plvItem->iSubItem, "");
			return TRUE;
		}

	}

	//g_bana_log->Print("End Label Edit = %d\n", plvItem->iSubItem);

	m_bDirty = TRUE;

	return FALSE;
}
