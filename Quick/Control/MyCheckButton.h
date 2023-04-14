#pragma once

#include "MacButtons.h"

// CMyCheckButton

class CMyCheckButton : public CMacCheckBox
{
	//DECLARE_DYNAMIC(CMyCheckButton)

public:
	CMyCheckButton();
	virtual ~CMyCheckButton();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnGetCheck(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetCheck(WPARAM wParam, LPARAM lParam);
};


