#pragma once



class CFlatButtonTheme : public CXTPButtonTheme
{
public:
	CFlatButtonTheme(void);
	~CFlatButtonTheme(void);

protected:
	virtual void DrawButton(CDC* pDC, CXTPButton* pButton);
	virtual void DrawButtonBackground(CDC* pDC, CXTPButton* pButton);
	virtual void DrawPushButtonText(CDC* pDC, CXTPButton* pButton);
	virtual	void DrawRadioButtonMark(CDC* pDC, CXTPButton* pButton);
	virtual void DrawCheckBoxMark(CDC* pDC, CXTPButton* pButton);
	virtual void DrawButtonText(CDC* pDC, CXTPButton* pButton);

};
