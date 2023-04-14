#pragma once

class CMakeBranchCombo;

// CMainBranchCombo

class CMainBranchCombo : public CComboBox
{
	DECLARE_DYNAMIC(CMainBranchCombo)

public:
	CMainBranchCombo();
	virtual ~CMainBranchCombo();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchange();
	void SetParent(CMakeBranchCombo *pWnd);
	CMakeBranchCombo *m_pMakeBranchCombo;
};


