#pragma once

#define WM_CLICKED_BUTTON 3210
// CCheckBitmap

class CCheckBitmap : public CBitmapButton
{
	DECLARE_DYNAMIC(CCheckBitmap)

public:

	CCheckBitmap();
	virtual ~CCheckBitmap();
	void SetImage(long nCheck, long nNotCheck, CWnd *pWnd = NULL) 
	{
		m_pMsgWnd = pWnd;
		LoadBitmaps(nNotCheck);
		m_nCheckImage = nCheck; 
		m_nNotCheckImage = nNotCheck;
		SetCheck(FALSE);
		ChangeImage();
	}

protected:
	DECLARE_MESSAGE_MAP()

private:
	CWnd *m_pMsgWnd;
	BOOL m_bCheck;
	long m_nCheckImage;
	long m_nNotCheckImage;
public:
	void SetCheck(int nCheck);
	BOOL GetCheck();
	void ChangeImage();
	afx_msg void OnBnClicked();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


