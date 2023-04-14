#pragma once


#include "FlatButtonTheme.h"

// CFlatButton

class CFlatButton : public CXTPButton
{
	DECLARE_DYNAMIC(CFlatButton)

public:
	CFlatButton();
	virtual ~CFlatButton();
	virtual void OnDraw(CDC* pDC);

	void SetFont(CFont *pFont);
	CFont* GetMyFont() const;

	COLORREF m_crPushText;
	COLORREF m_crPushBack;
	COLORREF m_crPushBorder;
	COLORREF m_crPushHotBorder;
	COLORREF m_crCheckText;
	COLORREF m_crCheckSelectedText;
	COLORREF m_crCheckBack;
	COLORREF m_crCheckBorder;
	COLORREF m_crCheckHotBorder;
	COLORREF m_crCheckSelected;	//���ýÿ� üũ�ڽ� �ȿ� �׷����� ����� ����
	COLORREF m_crCheckTextBack;	//üũ�ڽ� ���ںκ��� ����
	BOOL m_bHasTextBackColor;

	void SetPushColor(COLORREF crText, COLORREF crBack = RGB(84, 96, 110), COLORREF crBorder = RGB(51, 58, 66), COLORREF crHotBorder = RGB(0, 198, 255));
	void SetPushColorAll(COLORREF crAll) { SetPushColor(crAll, crAll, crAll, crAll); }
	void SetCheckColor(COLORREF crText = -1, COLORREF crBack = -1, COLORREF crSelected = -1);
	void SetCheckTextBackColor(COLORREF crText, COLORREF crBack);
	void SetCheckSelectedColor(COLORREF crText, COLORREF crSelected);

	CString GetText();
	long GetTextLong();
	void SetWindowTextLong(long nNumber, BOOL bThousandsSep = FALSE);

protected:
	DECLARE_MESSAGE_MAP()

	CFont *m_pFont;
};


