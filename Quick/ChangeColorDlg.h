#pragma once
#include "afxwin.h"

#if !defined(AFX_ColorPickerDLG_H__13DCC50F_7B0D_47BC_9FD4_B36DE8D69963__INCLUDED_)
#define AFX_ColorPickerDLG_H__13DCC50F_7B0D_47BC_9FD4_B36DE8D69963__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CChangeColorDlg 대화 상자입니다.


class CChangeColorDlg : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CChangeColorDlg)

public:
	CChangeColorDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChangeColorDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHANGE_COLOR_DLG };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	CBranchInfo *m_pBi;

	int m_nCompany;
	CEdit m_TitleEdt;
	CRect m_rect;
	BOOL m_bMoreColors;
	CComboBox m_comboBox;

	COLORREF m_clrText;
	COLORREF m_clrBack;

	CXTColorPicker  m_cpTextColor;
	CXTColorPicker  m_cpBackColor;

	CString m_sTitle;
	virtual BOOL OnInitDialog();
	afx_msg void OnChkMorecolors();
	afx_msg void OnSelEndOkTextClr();
	afx_msg void OnSelEndOkBackClr();
	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedDefaultColorBtn();
};
#endif