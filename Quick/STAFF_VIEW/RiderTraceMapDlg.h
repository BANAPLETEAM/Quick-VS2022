#pragma once


// CRiderTraceMapDlg 대화 상자입니다.


#include "RiderTraceCtrl.h"

class CRiderTraceMapDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderTraceMapDlg)

public:
	CRiderTraceMapDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderTraceMapDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_TRACE_MAP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	void MoveRider();
	void RefreshList();

	long m_nCompany;
	long m_nRNo;
	CLogiMapNew *GetMap() { return &m_wndMap; }

	void UpdateOrderStatic();
	CXTPListCtrl2 m_lstOrder;

protected:
	CRiderTraceCtrl m_wndMap;
};
