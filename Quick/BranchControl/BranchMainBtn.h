#pragma once

class CBranchSel;
// CBranchMainBtn

class CBranchMainBtn : public CButton
{
	DECLARE_DYNAMIC(CBranchMainBtn)

public:
	CBranchMainBtn();
	virtual ~CBranchMainBtn();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClicked();
	CBranchSel *m_pParent;
};
