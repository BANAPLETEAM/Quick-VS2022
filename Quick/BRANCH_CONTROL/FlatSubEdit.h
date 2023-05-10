#pragma once

class CBranchSel;
// CFlatSubEdit

class CFlatSubEdit : public CFlatEdit2
{
	DECLARE_DYNAMIC(CFlatSubEdit)

public:
	CFlatSubEdit();
	virtual ~CFlatSubEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CBranchSel *m_pParent;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


