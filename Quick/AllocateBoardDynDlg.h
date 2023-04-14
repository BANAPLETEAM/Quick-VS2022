#pragma once

//#include "AllocateBoardDlg.h"
#include "AllocateReportPaintManager.h"

// CAllocateBoardDynDlg ��ȭ �����Դϴ�.


class CAllocateBoardDynDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAllocateBoardDynDlg)

public:
	CAllocateBoardDynDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAllocateBoardDynDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ALLOCATE_BOARD_DYN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	CXTPGridControl m_wndReport;
	CAllocateReportPaintManager *m_pRPM;
	CWnd *m_pParentWnd;
	ALLOCATE_BOARD_RIDER_INFO *m_pRiderInfo;

	long m_nDisplayCount;
	long m_nOpaqueValue;

	BOOL m_bAlterBkColor;

	void *m_pMyDlg;

	CRect m_rcBase;
	CRect m_rcInit;
	static CRect m_rcSave;

	BOOL m_bFindProperRider;
	BOOL m_bShowPosName;
	BOOL m_bMove;
	BOOL m_bLButtonDown;
	BOOL m_bFirstBox;

	CPoint m_ptInit;

	CButton m_btnCloseAll;
	CButton m_btnRiderInfo;
	CButton m_btnRiderPos;
	CButton m_btnAllocate;

	void RefreshList();
	void MakeTransparentWindow(HWND hWnd, int Opaque);

	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	afx_msg void OnBnClickedCloseAllBtn();
	afx_msg void OnBnClickedRiderInfoBtn();
	afx_msg void OnBnClickedRiderPosBtn();
	afx_msg void OnBnClickedAllocateBtn();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
};
