#pragma once
 
#include "MyDialogDef.h"

// CMyResizeDialog 대화 상자입니다.

class CMyResizeDialog : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CMyResizeDialog)

public:
	explicit CMyResizeDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	explicit CMyResizeDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);	
	virtual ~CMyResizeDialog();
	virtual BOOL OnInitDialog();

// 대화 상자 데이터입니다.
	enum { IDD = 0 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();

	MAP_WND_BRUSH m_mapWnd;

	template<class CMyDlg>
	void CreateModalessDlg(CWnd *pwndParent, CMyDlg** pOriPointer, BOOL bAutoDelete = TRUE);
/*	
	template<class CMyDlg>
	void CreateModalessDlgNoFunc(CWnd *pwndParent, CMyDlg** pOriPointer, BOOL bAutoDelete = TRUE);
	template<class CMyDlg>
	void CreateModalessDlg(CWnd *pwndParent, CMyDlg** pOriPointer, void (*pfInit)(CMyDlg*), BOOL bAutoDelete = TRUE);
	template<class CMyDlg, class CMyDlg2>
	void CreateModalessDlg2(CWnd *pwndParent, CMyDlg** pOriPointer, CMyDlg2 *pSubClass, 
		void (*pfInit)(CMyDlg*, CMyDlg2*), BOOL bAutoDelete = TRUE);
*/
protected:
	virtual void OnOK();
	virtual void OnCancel();
	void DeleteModaless();

	BOOL m_bCreatedAsModaless;
	UINT m_nIDTemplate;
	BOOL m_bModalessAutoDelete;
	void **m_pOriPointer;
};


template<class CMyDlg>
AFX_INLINE void CMyResizeDialog::CreateModalessDlg(CWnd *pwndParent, CMyDlg **pOriPointer, BOOL bAutoDelete)
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
AFX_INLINE void CMyResizeDialog::CreateModalessDlgNoFunc(CWnd *pwndParent, CMyDlg **pOriPointer, BOOL bAutoDelete)
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


template<class CMyDlg>
AFX_INLINE void CMyResizeDialog::CreateModalessDlg(CWnd *pwndParent, CMyDlg **pOriPointer, void (*pfInit)(CMyDlg*), BOOL bAutoDelete)
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
AFX_INLINE void CMyResizeDialog::CreateModalessDlg2(CWnd *pwndParent, CMyDlg **pOriPointer, CMyDlg2 *pSubClass,
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