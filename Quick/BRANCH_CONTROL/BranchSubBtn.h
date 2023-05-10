#pragma once

class CBranchSel;

// CBranchSubBtn

class CBranchSubBtn : public CButton
{
	DECLARE_DYNAMIC(CBranchSubBtn)

public:
	CBranchSubBtn();
	virtual ~CBranchSubBtn();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClicked();
	CBranchSel *m_pParent;
};

