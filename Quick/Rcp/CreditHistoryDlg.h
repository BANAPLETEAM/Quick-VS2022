#pragma once


#include "WindowMagnetic.h"

class CRcpDlg;

class CCreditHistoryDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCreditHistoryDlg)

public:
	CCreditHistoryDlg(CWnd* pParent);   // 표준 생성자입니다.
	virtual ~CCreditHistoryDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CREDIT_HISTORY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnEnChangeSearchStartEdit();
	afx_msg void OnEnChangeSearchDestEdit();
	afx_msg void OnEnChangeSearchEtcEdit();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnChangeSearchManagerEdit();
	afx_msg void OnViewExcel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	void OnReportColumnChangeChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	void RefreshList();
	void DeleteAllItems();
	void ListFilter();
	long GetListRowCount() { return m_nRecordCount; }

	CRcpDlg *m_pRcpDlg;
	CWnd *m_pwndParent;
	CXTPListCtrl2 m_wndReport;

	CWindowMagnetic m_Magnetic;

	long m_nOGNo;
	long m_nOCNo;
	long m_nCompany;
	long m_nRecordCount;

	CButton m_btnCancel;

	CStatic m_stcInfo;
	CFlatEdit2 m_edtSearchStart;
	CFlatEdit2 m_edtSearchDest;
	CFlatEdit2 m_edtSearchEtc;
	CFlatEdit2 m_edtSearchManager;
};
