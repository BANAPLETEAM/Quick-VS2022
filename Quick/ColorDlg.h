#pragma once
#include "afxwin.h"


// CColorDlg 대화 상자입니다.

class CColorDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CColorDlg)

public:
	CColorDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CColorDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_COLOR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
