#pragma once

// CPSListCtrl
#include "ListCtrl.h"


class CPSListCtrl : public gxListCtrl
{
	//DECLARE_DYNAMIC(CPSListCtrl)

public:
	CPSListCtrl();
	virtual ~CPSListCtrl();
	virtual BOOL EndLabelEdit(LV_ITEM *plvItem);

protected:
	DECLARE_MESSAGE_MAP()

	BOOL m_bDirty;


public:
	void ResetDirtyFlag() { m_bDirty = FALSE;}
	BOOL GetDirtyFlag() { return m_bDirty; }

};


