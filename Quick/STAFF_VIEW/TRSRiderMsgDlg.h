#pragma once

#include "afxwin.h"

// CShowRiderInfoDlg 대화 상자입니다.

class CTRSRiderMsgDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CTRSRiderMsgDlg)

public:
	CTRSRiderMsgDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTRSRiderMsgDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TRS_RIDER_MSG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNonRegRiderReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	//afx_msg void OnNonRegRiderReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	//afx_msg void OnTRSReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnTRSReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedRefreshNonRegRider();
	afx_msg void OnBnClickedRefreshTRSMsg();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnEnChangeNonRegSearchEdit();
	afx_msg void OnEnChangeTRSMsgSearchEdit();

	void RefreshNonRegRiderList();
	void RefreshTRSMsgList();
	void NonRegSearchRecord();
	void TRSMsgSearchRecord();

public:
	CXTPListCtrl2 m_lstNonRegRider;
	CXTPListCtrl2 m_lstTRSMsg;
	CFlatEdit2 m_edtNonRegRiderSearch;
	CFlatEdit2 m_edtTRSMsgSearch;
};
