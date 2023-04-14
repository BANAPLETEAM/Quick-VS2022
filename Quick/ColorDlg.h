#pragma once
#include "afxwin.h"


// CColorDlg ��ȭ �����Դϴ�.

class CColorDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CColorDlg)

public:
	CColorDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CColorDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COLOR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	CXTColorPicker  m_cpColor;
	COLORREF m_clrColor;
	long m_nColor;
	CXTColorPicker  m_cpTextColor;
	COLORREF m_clrTextColor;
	long m_nTextColor;

	long m_nCarType;
	long m_nRNo;
	CString m_sRName;
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	CStatic m_Stc;
	afx_msg void OnBnClickedTextColorBtn();
	afx_msg void OnBnClickedColorBtn();
	virtual BOOL OnInitDialog();

	void OnSelEndOkTextClr();
	void OnSelEndOkBackClr();

	void UpdateChangeColor();
};
