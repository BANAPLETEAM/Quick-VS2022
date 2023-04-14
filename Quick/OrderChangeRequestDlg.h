#pragma once
#include "afxwin.h"


// COrderChangeRequestDlg 대화 상자입니다.

class COrderChangeRequestDlg : public CMyDialog
{
	DECLARE_DYNAMIC(COrderChangeRequestDlg)

public:
	COrderChangeRequestDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COrderChangeRequestDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ORDER_CHANGE_REQUEST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	CXTPListCtrl2 m_lstReport;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtpFrom;
	CDateTimeCtrl m_dtpTo;
	CDateButton m_btnData;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeStateCombo();

	void ChangeItemState(long nID, long nResult);
	CComboBox m_cmbState;
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	afx_msg void OnComplete();
	afx_msg void OnNotComplete();
	afx_msg void OnCancelItem();
	void RefreshList();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
