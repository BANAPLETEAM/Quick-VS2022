#pragma once

class CBranchSel;
// CFlatBranchEdit

class CFlatBranchEdit : public CFlatEdit2
{
	DECLARE_DYNAMIC(CFlatBranchEdit)

public:
	CFlatBranchEdit();
	virtual ~CFlatBranchEdit();

protected:
	DECLARE_MESSAGE_MAP()

public:
	CBranchSel *m_pParent;
	afx_msg void OnEnChange();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEnKillfocus();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


