#pragma once
#include "afxwin.h"


// CChargeForRiderLogDlg 대화 상자입니다.

class CChargeForRiderLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeForRiderLogDlg)

public:
	CChargeForRiderLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChargeForRiderLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHARGE_FOR_RIDER_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRefreshBtn();
	virtual BOOL OnInitDialog();

	CXTPListCtrl2 m_lstReport;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;
	CDateButton m_btnDate;
	CButton m_btnRefresh;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void RefreshList();
	CComboBox m_cmbType;
	afx_msg void OnCbnSelchangeTypeCombo();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	void OnRequestStop();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
};
