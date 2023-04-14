#pragma once

#include "MyStatic.h"
#include "FlatComboBoxInsung.h"
// CRcpDlgBase 대화 상자입니다.

typedef struct{
	CComboBox *pCombo;
	CComboBox combo;
	CFlatComboBoxInsung comboInsung;
} ST_COMBO;


class CRcpView;

class CRcpDlgBase : public CMyDialog
{
	DECLARE_DYNAMIC(CRcpDlgBase)

public:
	CRcpDlgBase(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRcpDlgBase();

// 대화 상자 데이터입니다.
	enum { IDD = 0 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	BOOL IsInsungDlg();
	CRcpView *m_pRcpView;
	CMyStatic m_stcTitle;
	COLORREF m_crOriBack;
	CRect m_rcBackPaint;
	COLORREF m_crText;
	COLORREF m_crBack;
	CString m_strRcpTitle;
	CString m_strRcpTitleTime;
	CString m_strGrade;

	int m_nInitItem;
	CBranchInfo *m_pBi;
	COleDateTime m_dtRcpTime;
	COleDateTimeSpan m_dtsDBTime;
	//CComboBox m_cmbBranch;
	ST_COMBO m_CMB_BRANCH;
	CWnd *m_pFocusControl;

	afx_msg void OnBnClickedMiniSizeBtn();
	afx_msg void OnBnClickedSearchRcpViewBtn();
	afx_msg void OnBnClickedNewRcpDlgBtn();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LONG OnMyStaticClick(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void DrawTop(CDC *pDC);
	//HBRUSH DrawTopControlColor(CDC *pDC);
	void SetTitleInfo(CString strText);
	void SetTitleTime();
	void MakeBranchCombo();
	void SetGrade(long nGrade);
};
