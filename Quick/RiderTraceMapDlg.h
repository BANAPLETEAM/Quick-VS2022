#pragma once


// CRiderTraceMapDlg ��ȭ �����Դϴ�.


#include "RiderTraceCtrl.h"

class CRiderTraceMapDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderTraceMapDlg)

public:
	CRiderTraceMapDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRiderTraceMapDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RIDER_TRACE_MAP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
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
