#pragma once


enum { NOT_ATTACH = 0, ATTACH_LEFT = 1, ATTACH_RIGHT = 2};


class CWindowMagnetic
{
public:
	CWindowMagnetic(void);
	virtual ~CWindowMagnetic(void);

protected:
	CWnd *m_pWndTo;
	CWnd *m_pWndThis;
	CString m_strSaveName;
	int m_nAttachType;
	int m_nAttachPosX;
	int m_nAttachPosY;

public:
	void SetInfo(CWnd *pThis, CWnd *pTo, CString strSaveName);
	void PosChanging(WINDOWPOS* lpwndpos);
	void AttachTo();
};
