#pragma once


// CBitmapButtonEdit

class CBitmapButtonEdit : public CEdit
{
	DECLARE_DYNAMIC(CBitmapButtonEdit)

public:
	CBitmapButtonEdit();
	virtual ~CBitmapButtonEdit();

protected:
	DECLARE_MESSAGE_MAP()

public:
	CWnd *m_pMsgWnd;
	void MakeButton(CWnd *pMsgWnd, UINT nImage, long nMargin = 0);
	CBitmapButton m_btnImage;
	//CButton m_btnImage;

	void ChangeImage(UINT nImage);
	void ShowButton(BOOL bShow);

};


