#pragma once
#include "afxwin.h"


// CChargeForRiderLogDlg ��ȭ �����Դϴ�.

class CChargeForRiderLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeForRiderLogDlg)

public:
	CChargeForRiderLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CChargeForRiderLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHARGE_FOR_RIDER_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
