#pragma once
#include "GdipButton.h"

#define WM_CLICKED_BUTTON 3210

class CGdipCheckBtn :
	public CGdipButton
{
	DECLARE_DYNAMIC(CGdipCheckBtn)

protected:

	DECLARE_MESSAGE_MAP()

private:
	CWnd *m_pMsgWnd;

public:
	CGdipCheckBtn(void);
	virtual ~CGdipCheckBtn(void);
	//afx_msg void OnBnClicked();

	virtual BOOL LoadAltImage(UINT id, LPCTSTR pType, HMODULE hInst = NULL);

	void SetCheckImage(UINT nIDUncheck, UINT nIDCheck, LPCTSTR pType = "PNG", CWnd *pWnd = NULL);
	int GetCheck() const;
	void SetCheck(int nCheck);
};
