#pragma once

#include "afxwin.h"

// CShowRiderInfoDlg 대화 상자입니다.

class CTRSRiderDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CTRSRiderDlg)

public:
	CTRSRiderDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTRSRiderDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TRS_RIDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRiderReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnRiderReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedRefresh();
	afx_msg void OnBnClickedTRSMsg();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnEnChangeSearchEdit();
	
	void RefreshList();
	void SearchRecord();

public:
	CXTPListCtrl2 m_lstRider;
	CXTPListCtrl2 m_lstNearRider;
	CFlatEdit2 m_edtRiderSearch;
};
