#pragma once
class CBranchSel;
// CFlatMainEdit

class CFlatMainEdit : public CFlatEdit2
{
	DECLARE_DYNAMIC(CFlatMainEdit)

public:
	CFlatMainEdit();
	virtual ~CFlatMainEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CBranchSel *m_pParent;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


