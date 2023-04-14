#pragma once


#include "FocusEditCtrl2.h"

// CFlatEdit2

class CFlatEdit2 : public CFocusEditCtrl2
{
	//DECLARE_DYNAMIC(CFlatEdit2)

public:
	CFlatEdit2();
	virtual ~CFlatEdit2();
	virtual void PreSubclassWindow();

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	DECLARE_MESSAGE_MAP()
public:
	void SetWindowTextNoNotify(LPCTSTR lpszString);
	void SetWindowText(LPCTSTR lpszString);
	int GetWindowText(_Out_z_cap_post_count_(nMaxCount, return + 1) LPTSTR lpszStringBuf, _In_ int nMaxCount);
	void GetWindowText(CString& rString);
};



class CFlatMemoEdit2 : public CFocusEditCtrl2
{
	//DECLARE_DYNAMIC(CFlatMemoEdit2)

public:
	CFlatMemoEdit2();
	virtual ~CFlatMemoEdit2();
	virtual void PreSubclassWindow();

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
protected:
	DECLARE_MESSAGE_MAP()

public:
	void SetWindowText(LPCTSTR lpszString);
	int GetWindowText(_Out_z_cap_post_count_(nMaxCount, return + 1) LPTSTR lpszStringBuf, _In_ int nMaxCount);
	void GetWindowText(CString& rString);

};

