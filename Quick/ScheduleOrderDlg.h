#pragma once
#include "afxwin.h"


// CScheduleOrderDlg 대화 상자입니다.


class CScheduleOrderDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CScheduleOrderDlg)

public:
	CScheduleOrderDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CScheduleOrderDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SCHEDULE_ORDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDeleteBtn();
	afx_msg void OnBnClickedOk();

	BOOL m_bDay1;
	BOOL m_bDay2;
	BOOL m_bDay3;
	BOOL m_bDay4;
	BOOL m_bDay5;
	BOOL m_bDay6;
	BOOL m_bDay7;
	BOOL m_bPause;
	BOOL m_bScheduleOrder;
	int m_nNextWeekAdvance;
	BOOL m_bEdit;
	CButton m_btnNextWeekAdvance;
	COleDateTime m_dtReserveTime;
	COleDateTime m_dtEndDate;

	long m_nSrcTNo;
	long m_nCompany;

	afx_msg void OnBnClickedMakeBtn();
	virtual BOOL OnInitDialog();
	CButton m_chkReserveToRcp;
};
