#pragma once

class CRiderReportOrderDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderReportOrderDlg)

public:
	CRiderReportOrderDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRiderReportOrderDlg();
 
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RIDER_REPORT_ORDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl28 m_ReportOrderList;
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	CString GetType(long nShareCode1, long nRiderShareCode1, long nPayType);

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	long m_nRiderCompany;
	long m_nRNo;
	CString m_sRName;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCloseBtn();

	long m_nMyCashApplyCharge;
	long m_nOtherCashApplyCharge;
	long m_nMyCreditApplyCharge;
	long m_nOtherCreditApplyCharge;
	long m_nMyOnlineApplyCharge;
	long m_nOtherOnlineApplyChare;

	CString GetApply(CString sType, long nCharge, BOOL bGiveChargeToRider);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);

};
