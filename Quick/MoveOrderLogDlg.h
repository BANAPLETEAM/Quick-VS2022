#pragma once

#include "PPTooltip.h"

typedef struct{
    long nTNo;
	COleDateTime dt1;
	COleDateTime dtFinal;
	CString sStart;
	CString sDest;
	long nChare;
	long nRNo;
	long nRiderCompany;
	long nState;
}MOVE_ORDER_STRUCT;

typedef map<long, MOVE_ORDER_STRUCT> MOVE_ORDER_MAP;

class CMoveOrderLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMoveOrderLogDlg)

public:
	CMoveOrderLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMoveOrderLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MOVE_ORDER_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	MOVE_ORDER_MAP m_map;
	CDateButton m_DateBtn;
	CXTPListCtrl2 m_wndReport;
	CDateTimeCtrl m_FromDtCtl;
	CDateTimeCtrl m_ToDtCtl;

	CPPToolTip m_tooltip;

	virtual BOOL OnInitDialog();
	afx_msg void NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result);
	afx_msg void OnBnClickedRefreshBtn();
	void RefreshList();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	COleDateTime m_FromDt;
	COleDateTime m_ToDt;
};
