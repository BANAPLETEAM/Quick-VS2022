#pragma once

// CMyDialog 대화 상자입니다.

#include "MyDialogDef.h"
 
class CMyDialog : public CDialog
{
	DECLARE_DYNAMIC(CMyDialog)

public:
	explicit CMyDialog(CWnd* pParentWnd = NULL);   // 표준 생성자입니다.
	explicit CMyDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	virtual ~CMyDialog();
	virtual BOOL OnInitDialog();

// 대화 상자 데이터입니다.
	enum { IDD = 0 };

	DECLARE_MESSAGE_MAP()

	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	MAP_WND_BRUSH m_mapWnd;
	BOOL m_bPainted;

	COLORREF m_clrTop;
	COLORREF m_clrBottom;
	UINT m_nIDTemplate;
	BOOL m_bModalessAutoDelete;
	void **m_pOriPointer;

public:
	BOOL m_bCreatedAsModaless;
	static CString m_strLastDialog;
	void SetBottomColor(COLORREF clr);

	template<class CMyDlg>
	void CreateModalessDlg(CWnd *pwndParent, CMyDlg** pOriPointer, BOOL bAutoDelete = TRUE);
/*
	template<class CMyDlg>
	void CreateModalessDlg(CWnd *pwndParent, CMyDlg** pOriPointer, void (*pfInit)(CMyDlg*), BOOL bAutoDelete = TRUE);

	template<class CMyDlg, class CMyDlg2>
	void CreateModalessDlg2(CWnd *pwndParent, CMyDlg** pOriPointer, CMyDlg2 *pSubClass, 
							void (*pfInit)(CMyDlg*, CMyDlg2*), BOOL bAutoDelete = TRUE);

	template<class CMyDlg, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
	void CreateModalessDlg10(CWnd *pwndParent, CMyDlg** pOriPointer, T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
		void (*pfInit)(CMyDlg*, T1, T2, T3, T4, T5, T6, T7, T8, T9), BOOL bAutoDelete = TRUE);
*/

protected:
	virtual void OnOK();
	virtual void OnCancel();
	void DeleteModaless();

};



template<class CMyDlg>
AFX_INLINE void CMyDialog::CreateModalessDlg(CWnd *pwndParent, CMyDlg **pOriPointer, BOOL bAutoDelete)
{
	if(!m_bCreatedAsModaless)
	{
		m_pOriPointer = (void**)pOriPointer;
		m_bModalessAutoDelete = bAutoDelete;
		m_bCreatedAsModaless = TRUE;
		Create(m_nIDTemplate, pwndParent);
		ShowWindow(SW_SHOW);
		CenterWindow();
	}
	else
	{
		WINDOWPLACEMENT wndpl;
		wndpl.length = sizeof(WINDOWPLACEMENT);
		(this)->GetWindowPlacement(&wndpl);

		if(wndpl.showCmd == SW_SHOWMINIMIZED)
		{
			ShowWindow(SW_RESTORE);
		}
		else
		{
			ShowWindow(SW_SHOW);
			SetForegroundWindow();
			SetFocus();
		}
	}
}

/*
template<class CMyDlg>
AFX_INLINE void CMyDialog::CreateModalessDlg(CWnd *pwndParent, CMyDlg **pOriPointer, void (*pfInit)(CMyDlg*), BOOL bAutoDelete)
{
	if(!m_bCreatedAsModaless)
	{
		m_pOriPointer = (void**)pOriPointer;
		m_bModalessAutoDelete = bAutoDelete;
		m_bCreatedAsModaless = TRUE;
		Create(m_nIDTemplate, pwndParent);
		if(pfInit) (*pfInit)((CMyDlg*)this);
		ShowWindow(SW_SHOW);
		CenterWindow();
	}
	else
	{
		WINDOWPLACEMENT wndpl;
		wndpl.length = sizeof(WINDOWPLACEMENT);
		(this)->GetWindowPlacement(&wndpl);

		if(wndpl.showCmd == SW_SHOWMINIMIZED)
		{
			ShowWindow(SW_RESTORE);
		}
		else
		{
			ShowWindow(SW_SHOW);
			SetForegroundWindow();
			SetFocus();
		}
	}
}


template<class CMyDlg, class CMyDlg2>
AFX_INLINE void CMyDialog::CreateModalessDlg2(CWnd *pwndParent, CMyDlg **pOriPointer, CMyDlg2 *pSubClass,
											   void (*pfInit)(CMyDlg*, CMyDlg2*), BOOL bAutoDelete)
{
	if(!m_bCreatedAsModaless)
	{
		m_pOriPointer = (void**)pOriPointer;
		m_bModalessAutoDelete = bAutoDelete;
		m_bCreatedAsModaless = TRUE;
		Create(m_nIDTemplate, pwndParent);
		if(pfInit) (*pfInit)((CMyDlg*)this, pSubClass);
		ShowWindow(SW_SHOW);
		CenterWindow();
	}
	else
	{
		WINDOWPLACEMENT wndpl;
		wndpl.length = sizeof(WINDOWPLACEMENT);
		(this)->GetWindowPlacement(&wndpl);

		if(wndpl.showCmd == SW_SHOWMINIMIZED)
		{
			ShowWindow(SW_RESTORE);
		}
		else
		{
			ShowWindow(SW_SHOW);
			SetForegroundWindow();
			SetFocus();
		}
	}
}
*/