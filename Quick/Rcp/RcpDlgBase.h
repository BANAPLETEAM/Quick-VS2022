#pragma once

#include "MyStatic.h"
#include "FlatComboBoxInsung.h"
// CRcpDlgBase ��ȭ �����Դϴ�.

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
	CRcpDlgBase(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRcpDlgBase();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = 0 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
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
